
/*********************************************************************************************************
#  Date :25 Dec 06
#  Owner:Ashutosh Singh
#                     Copy right permission to IMR Pvt Ltd 
#                                 2006-07
#                                                                      
#   This product and related documentation is protected by copyright and   
#   distributed under licenses restricting its use, copying, distribution  
#   and decompilation.  No part of this product or related documentation   
#   may be reproduced in any form by any means without prior written       
#   authorization ofIMR Pvt Ltd and its licensors, if any.    
#
#
# ...  Devloping started from 25 Dec06  
# ...  Finalized testing on 27 Dec
#   changes related to             Date                by
#                  
#     1.
#
#     2.
#
********************************************************************************************************/



#include <stdio.h>
#include "Coder.h"

#define ISIL_TRACE_DEBUG   0x01
#define ISIL_TRACE_ERROR   0x02
#define ISIL_TRACE_WARNING 0x03
#define MSG_LEN  (272 - 5 - 3 - 8 - 3 + 4 - 3 ) /*MSU - MTP3Hdr - MFixed - ptrto param - mv len field +seq control - mtp2 hdr*/ 
extern "C"
{
void  ISIL_TRACE(int trace ,const char *ftstring, ...);

}
extern ITS_USHORT gtt_opc;
extern ITS_OCTET  gtt_ni;

/*Patch:Itika:8-june-10:Updated for ANSI:SCCP CL*/
#ifdef CCITT 
#define ISILgethdr ISILgethdr_CCITT
#endif
#ifdef ANSI
#define ISILgethdr ISILgethdr_ANSI
#endif
/*Updated for ANSI:SCCP CL End*/



/*****************************************************************************
 *  Purpose:
 *      This function Decodes ISIL event.
 *
 *  Input Parameters:
 *      ITS_EVENT *ev
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ISIL _IE *ies
 *
 *  Return Value:
 *      If the decode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  --------------------------------------------------------------------------

*****************************************************************************/


int
ISIL_Decode(ITS_EVENT* event,ISIL_IE*ie,ISIL_ARGS *args)

{
  ITS_OCTET *ptr; 
  ITS_OCTET i,j;

  ITS_OCTET noargs; 
  ITS_OCTET nmargs; 
// ITS_OCTET nvargs=3;
  ITS_OCTET nvargs= MAX_VAR_ARGS;
  ITS_OCTET totalargs;
  ITS_OCTET M[DEFAULT_OFFSET]={CDA_DATA ,CPA_DATA ,USER_DATA};
  ITS_OCTET value=0;
  ITS_UINT CPA_LEN=0,CDA_LEN=0 ;
  ITS_UINT  Len=0;

  memset(ie, 0, sizeof(ISIL_IE));

  totalargs=event->data[2];
  noargs=totalargs - nvargs;
 
  args->total=totalargs;


 // ptr=&event->data[5];                  /*pointer to called party adress length*/  
  ptr=&event->data[TCAP_HEADER];         /*pointer to called party adress length*/  

  for (i=0;i<nvargs;i++)
  {
      ie[i].paramlength=(ptr[1]<<MAX_OFFSET|ptr[0]);  
      Len+=ie[i].paramlength;
      if ((ie[i].paramlength < MAX_USERDATA_LEN && value==0 )
            ||(ie[i].paramlength <= (MSG_LEN - CDA_LEN - CPA_LEN) && value==1))
       {
           ie[i].paramid=M[i];
           memcpy(ie[i].param_data.userdata.data,&ptr[2],ie[i].paramlength);

           if (ie[i].paramid==CDA_DATA)
            {
              CDA_LEN=ie[i].paramlength;
              if(ie[i].param_data.userdata.data[0] & 0x40)
               {
                   value=0;
                   ISIL_TRACE(ISIL_TRACE_DEBUG,"SCLCHandleAPPMsg: GTT are not  Present\n");
               }
               else
               {
                  value=1;
                  ISIL_TRACE(ISIL_TRACE_DEBUG,"SCLCHandleAPPMsg: GTT are Present\n");
               }

           }
         else if(ie[i].paramid==CPA_DATA)
           {
             CPA_LEN=ie[i].paramlength;
           }

       }
      else
      {
         ie[i].paramid=LONG_DATA;
         memcpy(ie[i].param_data.longData.data,&ptr[2],ie[i].paramlength);

     }

    ptr+=((ie[i].paramlength)+FIXEDLEN_OFFSET);
 }

    
  for (i=0;i<noargs;i++)
  {

     ie[i+ nvargs].paramid=*ptr;   
     ptr++;

     ie[i+nvargs].paramlength=(ptr[1]<<MAX_OFFSET|ptr[0]);
    
     memcpy(&ie[i+nvargs].param_data.userdata.data[0],&ptr[2],ie[i+nvargs].paramlength);  
 
     ptr+=ie[i+nvargs].paramlength+FIXEDLEN_OFFSET;
  }

     
}/*end of functio Decoder*/



/*****************************************************************************
 *  Purpose:
 *      This function Encoeds ISIL event.
 *
 *  Input Parameters:
 *      ITS_EVENT *ev
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ISIL _IE *ies
 *
 *  Return Value:
 *      If the decode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  --------------------------------------------------------------------------

*****************************************************************************/

int
ISIL_Encoder(ITS_EVENT*event,ISIL_IE*ie,ISIL_ARGS args)

{
  ITS_OCTET msgtype;
  ITS_OCTET noargs; 
  ITS_OCTET nmargs; 
  ITS_OCTET totalargs; 
  ITS_OCTET nvargs= MAX_VAR_ARGS;
  ITS_OCTET noffset=0;
  ITS_OCTET offset=0;
  ITS_OCTET mandoffset=0;
  ITS_OCTET cntr=0;
  ITS_OCTET a[2];
  ITS_USHORT length=0;
  ITS_OCTET i,j=0,Chk=0;
  ITS_OCTET sls=0,sio;
  ITS_OCTET b[MAX_OFFSET];    /*fill the offset pointer value by myself*/
  /*Patch:Itika:16-june-10:Fix in ANSI & ITU: updated for ANSI SCCP CL*/
  ITS_UINT opc = 0,dpc = 0;
  /*End: updated for ANSI SCCP CL*/
  ITS_OCTET nicda=MTP3_NIC_INTERNATIONAL,nicpa=MTP3_NIC_INTERNATIONAL;
  ITS_OCTET c=0,x=0;
  ITS_OCTET Seq_chk=0;
  ITS_OCTET pc_chk=0;
  ITS_OCTET Param_chk=0;
  ITS_OCTET Sequence_chk=0;
  totalargs=args.total;

  noargs=totalargs-nvargs;

  /*get opc ,dpc ,sio value form configuration*/
  ISILgethdr(ie,&opc,&dpc,&sio,&nicda,&nicpa);


 /*1.Length of fixed 8 byte header*/
  length+=SCCP_HEADER;


 /*2.find the msgtype depends upon length of datafield */
 for (i=0;i<nvargs;i++)
  {
    if (ie[i].paramid==LONG_DATA) 
     {
          nmargs=MAND_ARGS_2;
          msgtype=SCCP_MSG_LUDT;    
          noffset=ISIL_UDT_OFFSET_4;
          for (Chk=0;Chk<noargs;Chk++)
          {
              if( (ie[Chk+nvargs].paramid ==ISIL_RETURNOPT_OP) && ie[Chk+nvargs].param_data.userdata.data[0]==0x01)
              {
                a[mandoffset++]=0x80|ISIL_PROTOCOLCLASS_1;   /*value of protocol class */
              }
              else if((ie[Chk+nvargs].paramid ==ISIL_RETURNOPT_OP) && ie[Chk+nvargs].param_data.userdata.data[0]==0x00)
              {
                a[mandoffset++]=ISIL_PROTOCOLCLASS_1;   /*value of protocol class */
              }   
 
              if( ie[Chk+nvargs].paramid ==ISIL_SEQCONTRL_OP)
              {
                 sls=ie[Chk+nvargs].param_data.userdata.data[0];
              }
          }  
        //  a[mandoffset++]=ISIL_PROTOCOLCLASS_1;   /*value of protocol class */
          a[mandoffset]=ISIL_DFLT_HOPCTR;         /*value of hop counter*/

     length+=2*noffset;                           /*8 for LUDT messages*/
     }

    else if (ie[i].paramid==USER_DATA) 
     {
        for (Chk=0;Chk<noargs;Chk++)
        {
      	  if (ie[Chk+nvargs].paramid==ISIL_SEQCONTRL_OP || ie[Chk+nvargs].paramid ==ISIL_RETURNOPT_OP)
       	  {
              ISIL_TRACE(ISIL_TRACE_DEBUG,"USELESS  PARAM\n");
              if( ie[Chk+nvargs].paramid ==ISIL_RETURNOPT_OP)
              {
                 Seq_chk=1;
              }
              if( ie[Chk+nvargs].paramid ==ISIL_SEQCONTRL_OP)
              {
                 Sequence_chk=1;
                 sls=ie[Chk+nvargs].param_data.userdata.data[0];
              }

          }
         else 
          {
             ISIL_TRACE(ISIL_TRACE_DEBUG,"USE OP PARAM  PRESENT\n");
              Param_chk=1;
          }

        }

        if ((noargs) && (Param_chk==1))    /*check for XUDT Message */
        {
           nmargs=MAND_ARGS_2;
           msgtype=SCCP_MSG_XUDT;
           noffset=ISIL_UDT_OFFSET_4;
           if(Seq_chk==1)
           {
                 a[mandoffset++]=0x80|ISIL_PROTOCOLCLASS_0;    /*value fo protocol class*/
           }
           else
           {
                a[mandoffset++]=ISIL_PROTOCOLCLASS_0;    /*value fo protocol class*/
           }
           a[mandoffset]=ISIL_DFLT_HOPCTR;          /*value fo hop counter*/

        }
       else                                         /*check for UDT message*/
        {
           nmargs=MAND_ARGS_1;
           msgtype=SCCP_MSG_UDT;
           noffset=ISIL_UDT_OFFSET_3;
           if(Seq_chk==1)
           {
               if(Sequence_chk==1)
                {
                   a[mandoffset]=0x80|ISIL_PROTOCOLCLASS_1;
                }
               else
                {
                  a[mandoffset]=0x80|ISIL_PROTOCOLCLASS_0;
                }
           }
           else
           {   if(Sequence_chk==1) 
               {
                 a[mandoffset]=ISIL_PROTOCOLCLASS_1;
               }
              else
               {
                 a[mandoffset]=ISIL_PROTOCOLCLASS_0;
               }

           } 
        }
    length+=noffset;                            

    }
  }
  
 /*3.length of madatory fixed parameter*/
  for (i=0;i<nmargs;i++)
  {
      length+=sizeof(ITS_OCTET);                  /*one for UDT and 2 for XUDT*/
  }
 
 
  /*4.length of madatory variables parameter*/
  for (i=0;i<nvargs;i++)
  {
    if (ie[i].paramid==LONG_DATA)
     {
        length++;                     /*due to one extra byte for Usre data length into 2 bytes */
     }
       length+=ie[i].paramlength+sizeof(ITS_OCTET);
  }
   
  /*5.length of madatory variables Parameter*/

  for (i=0;i<noargs;i++)
  { 
 	if (ie[i+nvargs].paramid==ISIL_RETURNOPT_OP )
       {
         /*This will be used for PC*/
       }
      else if(ie[i+nvargs].paramid==ISIL_SEQCONTRL_OP)
       {
        /*This will not be in case of Single XUDT*/
       }
      else
       {  
        length+=ie[i+nvargs].paramlength+sizeof(ITS_OCTET)+sizeof(ITS_OCTET);
        /*1 for length and one for optional parameterid*/

       }
                       
  }


  /*find the offset pointer for nvargs and first oargs depends upon length of datafield */

  ITS_USHORT pointer=0;
  ITS_OCTET k=0;
  if ((noargs) && ((msgtype==SCCP_MSG_LUDT) ||( msgtype==SCCP_MSG_XUDT)))
  {
      length++;                                            /*one for EOP */
      x=ISIL_DFLT_NOOPT;
  }


  for (i=0;i<(nvargs+x);i++)
  {
   if (msgtype==SCCP_MSG_LUDT)
    {
       k=2*i;
      if (i<=2)
      {

         b[k]=(7-2*i)+pointer+i;
         b[k+1]=((7-2*i)+pointer+i)>>MAX_OFFSET; 

      }
      else if(i>2)
      {
        /*extra 2 added due to userdata will take two bytes */

        b[k]=(7-2*i)+pointer+i+1;
        b[k+1]=((7-2*i)+pointer+i+1)>>MAX_OFFSET;

     }
   }
  else if (msgtype==SCCP_MSG_XUDT)
   {
      
          b[i]=(4-i)+pointer+i;
   }
  else if (msgtype==SCCP_MSG_UDT)
   {

       b[i]=(3-i)+pointer+i;
   }
   pointer+=ie[i].paramlength;

  /*encode the complete messages towards the SCCP*/

 }/*end of offset encoding*/

ISIL_TRACE(ISIL_TRACE_DEBUG,"ISIL:: OPC %d DPC %d SIO %d \n",opc,dpc,sio);

   /*Encode the Event for SCCP*/

  ITS_EVENT_INIT(event,ITS_TCAP_SRC,length*sizeof(ITS_OCTET));

  event->data[cntr++]=msgtype;
  event->data[cntr++]=0;/*header context info*/
  event->data[cntr++]=0;/*header context info*/
  event->data[cntr++]=0;/*header context info*/
  event->data[cntr++]=0;/*header context info*/
#ifdef CCITT
  /*Patch:Itika:8-june-10:ANSI MTP3 Routing label:SCCP CL*/
  event->data[cntr++]=sio;
  event->data[cntr++]=(char)dpc;
  /*Second Octet of MTP3 Header*/
  event->data[cntr] &=~0x3F;
  event->data[cntr]|=(unsigned char)((dpc>>8)&0x3F);
  event->data[cntr] &=~0xC0;
  event->data[cntr]|=(unsigned char)((opc<<6)& 0xC0);
  cntr++;
  /* Third Byte of Header*/
  event->data[cntr]=(unsigned char)((opc>>2)&0xFF);
  cntr++;
  /*Fourth Byte of Header*/

  event->data[cntr] &=~0x0F;
  event->data[cntr]|=(unsigned char)((opc>>10)&0x0F);
  event->data[cntr] &=~0xF0;
  event->data[cntr]|=(unsigned char)((sls<<4)&0xF0);
  cntr++;
#endif
 
#ifdef ANSI
  /*Patch:Itika:8-june-10:ANSI MTP3 Routing label:SCCP CL*/
  event->data[cntr++]=sio;
  event->data[cntr++]=dpc;
  event->data[cntr++]=dpc>>8;
  event->data[cntr++]=dpc>>16;
  event->data[cntr++]=opc;
  event->data[cntr++]=opc>>8;
  event->data[cntr++]=opc>>16;
  event->data[cntr++]=0x1F&sls;
#endif  
/*Updated for ANSI:SCCP CL End*/
    memcpy(&event->data[SCCP_HEADER],&a[0],nmargs*sizeof(ITS_OCTET));



   /* encoding of number of offset for mandatory and first optional parameter arguments*/ 

  for (i=0;i<noffset;i++)
  {
    /*offset has single byte in case of XUDT and UDT messages */
     if (msgtype==SCCP_MSG_XUDT||msgtype==SCCP_MSG_UDT)
      {
           offset=noffset;
           memcpy(&event->data[SCCP_HEADER+nmargs+i],&b[i],sizeof(ITS_OCTET)); 
      }

     /*offset has two byte in case of LUDT message*/
     else
     {     
          offset=2*noffset;
          memcpy(&event->data[SCCP_HEADER+nmargs+2*i],&b[j],sizeof(ITS_USHORT)); 
          j=j+2;/*due to 2 bytes for every offset*/ 
    }
 }
 

 
   /* encoding of no of mandatory  variable arguments*/ 

   ITS_USHORT len=0;
  for (i=0;i<nvargs;i++)
  {
    if (ie[i].paramid==LONG_DATA)
     {
             event->data[SCCP_HEADER+nmargs+offset+i]=ie[i].paramlength>>8 ;
             event->data[SCCP_HEADER+nmargs+offset+i+1]=ie[i].paramlength;
             memcpy(&event->data[SCCP_HEADER+nmargs+offset+i+2],&ie[i].param_data.longData.data[0],ie[i].paramlength); 
      
             len=(offset)+ie[i].paramlength+1;
             /*addtion of 1 byte for OP due to user data has two bytes for User data len*/    

    }
   else
    {
            event->data[SCCP_HEADER+nmargs+offset+i]=ie[i].paramlength;
            memcpy(&event->data[SCCP_HEADER+nmargs+offset+i+1],&ie[i].param_data.userdata.data[0],ie[i].paramlength);

           /*Changes the Add Indicator according the NI value on STACKS*/
            if (ie[i].paramid==CDA_DATA)
             {
                if ((nicda==MTP3_NIC_INTERNATIONAL) || (nicda==MTP3_NIC_SPARE))
                 {
                   c=0;
                 }
                else if ((nicda==MTP3_NIC_NATIONAL)||(nicda==MTP3_NIC_RESERVED))
                 { 
                   c=1;
                   event->data[SCCP_HEADER+nmargs+offset+i+1]|=c<<7;
                 } 
             }

             else if (ie[i].paramid==CPA_DATA)

             {
                if ((nicda==MTP3_NIC_INTERNATIONAL) || (nicda==MTP3_NIC_SPARE))

                 {
                   c=0;
                 }
                else if ((nicda==MTP3_NIC_NATIONAL)||(nicda==MTP3_NIC_RESERVED))
                 {
                   c=1;
                   event->data[SCCP_HEADER+nmargs+offset+i+1]|=c<<7;
                 } 

             }
                    
 
            offset+=ie[i].paramlength;

   }/*end if */
    
  }/*end of for*/



  /* encoding of no of optional arguments*/ 
  for (i=0;i<noargs;i++)
  {
    if (msgtype==SCCP_MSG_LUDT)
      {
	  if (ie[i+nvargs].paramid==ISIL_RETURNOPT_OP)
       	  {
              ISIL_TRACE(ISIL_TRACE_DEBUG,"RETURN OPTION is not supported By SCCP\n");
          }
          else
          {
             if (ie[i+nvargs].paramid==ISIL_SEQCONTRL_OP)
              {
         //       ie[i+nvargs].paramid=ISIL_SEGMNT_OP;
                   continue;
              }

           event->data[SCCP_HEADER+nmargs+nvargs+len+i]=ie[i+nvargs].paramid;
           event->data[SCCP_HEADER+nmargs+nvargs+len+i+1]=ie[i+nvargs].paramlength;
           memcpy(&event->data[SCCP_HEADER+nmargs+nvargs+len+i+2],&ie[i+nvargs].param_data.userdata.data[0],ie[i+nvargs].paramlength);     
           len+=ie[i+nvargs].paramlength+1;/*addtion of 1 byte for paramid of OP */
       }
     }
     else if(msgtype==SCCP_MSG_XUDT)
     {
            if (ie[i+nvargs].paramid==ISIL_RETURNOPT_OP)
            {
              ISIL_TRACE(ISIL_TRACE_DEBUG,"RETURN OPTION is not supported By SCCP\n");
            }
            else
            {
             if (ie[i+nvargs].paramid==ISIL_SEQCONTRL_OP)
              {
                 continue;
              }

              event->data[SCCP_HEADER+nmargs+nvargs+offset+i]=ie[i+nvargs].paramid;
              event->data[SCCP_HEADER+nmargs+nvargs+offset+i+1]=ie[i+nvargs].paramlength;
              memcpy(&event->data[SCCP_HEADER+nmargs+nvargs+offset+i+2],&ie[i+nvargs].param_data.userdata.data[0],ie[i+nvargs].paramlength);
              offset+=ie[i+nvargs].paramlength;
          
           }
     }     /*end of check for XUDT */
  }/*end of optinal parameter encoding*/


  /*End of the optional parameter*/

  if (msgtype==SCCP_MSG_LUDT || msgtype==SCCP_MSG_XUDT)
   {
        event->data[length-1]=SCCP_PRM_EOP; 
   }


} /*end of encoding function*/
#ifdef ANSI
/*Patch:Itika:8-june-10:Updated for ANSI:SCCP CL*/
int
ISILgethdr_ANSI(ISIL_IE *ie ,ITS_UINT* opc ,ITS_UINT* dpc,ITS_OCTET* sio ,ITS_OCTET *niCda ,ITS_OCTET *niCpa)
{
  ITS_OCTET i,addInCda,addInCpa,ssnCda,ssnCpa,d,a;
  ITS_OCTET *ptr,*tmp;
  ITS_BOOLEAN isAllowed;
  /*Patch:Itika:16-june-10:Fix in ANSI & ITU: updated for ANSI SCCP CL*/
  *opc = 0;/*initializing opc & dpc */
  *dpc = 0;
  /*End: updated for ANSI SCCP CL*/
 /*
  ptr=&event->data[5];
  tmp=ptr+*ptr+2;
  */
  ISIL_TRACE(ISIL_TRACE_DEBUG,"ENTER:ANSI ISILgethdr_ANSI OPC %d DPC %d\n",*opc,*dpc);
    ptr=&ie[0].param_data.userdata.data[0];
    tmp=&ie[1].param_data.userdata.data[0];

    /*called party adrress*/


  ISIL_TRACE(ISIL_TRACE_DEBUG,"ANSI ISILgethdr_ANSI  CALLED PARTY AddrInd 0x%x \n",ptr[0]);
     /*if dpc is present*/
   if((ptr[0]& 0x02)== 2)
     { 
  ISIL_TRACE(ISIL_TRACE_DEBUG,"ANSI ISILgethdr_ANSI  DPC PRESENT \n");
        *dpc=ptr[2]|ptr[3]<<8|ptr[4]<<16;
        ISIL_TRACE(ISIL_TRACE_DEBUG,"dpc=%d\n",*dpc);
         /*ssn is present*/
        if(ptr[0]&0x01==1)
         {
  ISIL_TRACE(ISIL_TRACE_DEBUG,"ANSI ISILgethdr_ANSI  SSN PRESENT \n");
             ssnCda=ptr[1];
              ISIL_TRACE(ISIL_TRACE_DEBUG,"ssnCda =%d\n",ssnCda);

             if (ROUTE_GetRouteContextStatus((*dpc), &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          ssnCda,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                             ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
              {
                 if (ROUTE_GetRouteContextStatus(*dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),ssnCda,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                 {
                    if (ROUTE_GetRouteContextStatus(*dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),ssnCda,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                     {
                         if (ROUTE_GetRouteContextStatus(*dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,
                                               (MTP3_NIC_RESERVED | MTP3_SIO_SCCP),ssnCda,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                          {
                                  //printf("SET SSN FAIL");
                                 *niCda=gtt_ni;
                                  ISIL_TRACE(ISIL_TRACE_DEBUG,"niCda=%d\n",*niCda);
                          }
                         else
                          {
                                *niCda=MTP3_NIC_RESERVED;
                                ISIL_TRACE(ISIL_TRACE_DEBUG,"niCda=%d\n",*niCda);
                          }
                     }
                     else
                     {
                          *niCda=MTP3_NIC_NATIONAL;
                          ISIL_TRACE(ISIL_TRACE_DEBUG,"niCda=%d\n",*niCda);
                     }
                  }
                 else
                  {
                      *niCda=MTP3_NIC_SPARE;
                      ISIL_TRACE(ISIL_TRACE_DEBUG,"niCda=%d\n",*niCda);
                  }
                }
               else
                {
                     *niCda=MTP3_NIC_INTERNATIONAL;
                     ISIL_TRACE(ISIL_TRACE_DEBUG,"niCda=%d\n",*niCda);

                }

          }
        else
          {
           *dpc=0;
          }  
    
    }
     
  ISIL_TRACE(ISIL_TRACE_DEBUG,"ANSI ISILgethdr_ANSI  CALLING PARTY AddrInd 0x%x \n",tmp[0]);
     /*if dpc is present*/
   if((tmp[0]& 0x02)== 2)
     { 
      /*calling party */
       *opc=tmp[2]|tmp[3]<<8|tmp[4]<<16;
        ISIL_TRACE(ISIL_TRACE_DEBUG,"opc=%d\n",*opc);
 
        if(tmp[0]&0x01==1)    ssnCpa=tmp[1];
        ISIL_TRACE(ISIL_TRACE_DEBUG,"ssnCpa =%d\n",ssnCpa);
             if (ROUTE_GetRouteContextStatus(*opc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          ssnCpa,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                             ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
              {
                 if (ROUTE_GetRouteContextStatus(*opc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),ssnCpa,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                 {
                    if (ROUTE_GetRouteContextStatus(*opc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),ssnCpa,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                     {
                         if (ROUTE_GetRouteContextStatus(*opc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,
                                               (MTP3_NIC_RESERVED |MTP3_SIO_SCCP ),ssnCpa,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                          {
                                 //printf("SET SSN FAIL");
                                 *niCpa=gtt_ni;
                                  ISIL_TRACE(ISIL_TRACE_DEBUG,"niCpa=%d\n",*niCpa);
                          }
                         else
                          {
                                *niCpa=MTP3_NIC_RESERVED;
                                ISIL_TRACE(ISIL_TRACE_DEBUG,"niCpa=%d\n",*niCpa);
                          }
                     }
                     else
                     {
                          *niCpa=MTP3_NIC_NATIONAL;
                          ISIL_TRACE(ISIL_TRACE_DEBUG,"niCpa=%d\n",*niCpa);
                     }
                  }
                 else
                  {
                      *niCpa=MTP3_NIC_SPARE;
                      ISIL_TRACE(ISIL_TRACE_DEBUG,"niCpa=%d\n",*niCpa);
                  }
                }
               else
                {
                     *niCpa=MTP3_NIC_INTERNATIONAL;
                     ISIL_TRACE(ISIL_TRACE_DEBUG,"niCpa=%d\n",*niCpa);

                }

        }
      else
       {
         *opc=gtt_opc;
       }
  


      *sio=(*niCda)|MTP3_SIO_SCCP;

}
#endif
#ifdef CCITT
/*Updated for ANSI:SCCP CL End*/



int
ISILgethdr_CCITT(ISIL_IE *ie ,ITS_UINT* opc ,ITS_UINT* dpc,ITS_OCTET* sio ,ITS_OCTET *niCda ,ITS_OCTET *niCpa)
{
  ITS_OCTET i,addInCda,addInCpa,ssnCda,ssnCpa,d,a;
  ITS_OCTET *ptr,*tmp;
  ITS_BOOLEAN isAllowed;
 /*
  ptr=&event->data[5];
  tmp=ptr+*ptr+2;
  */
    ptr=&ie[0].param_data.userdata.data[0];
    tmp=&ie[1].param_data.userdata.data[0];

    /*called party adrress*/


     /*if dpc is present*/
   if(ptr[0]&0x01==1)
     { 
        *dpc=ptr[1]|ptr[2]<<8;
				ISIL_TRACE(ISIL_TRACE_DEBUG,"dpc=%d\n",*dpc);
        ISIL_TRACE(ISIL_TRACE_DEBUG,"ssnId=%d\n",(ptr[0]&0x02));
         /*ssn is present*/
        if((ptr[0]&0x02)==2)
         {
             ssnCda=ptr[3];

             if (ROUTE_GetRouteContextStatus((*dpc), &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ITU,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          ssnCda,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                             ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
              {
                 if (ROUTE_GetRouteContextStatus(*dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ITU,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),ssnCda,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                 {
                    if (ROUTE_GetRouteContextStatus(*dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ITU,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),ssnCda,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                     {
                         if (ROUTE_GetRouteContextStatus(*dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ITU,
                                               (MTP3_NIC_RESERVED | MTP3_SIO_SCCP),ssnCda,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                          {
                                  printf("SET SSN FAIL");
                                 *niCda=gtt_ni;
                                  ISIL_TRACE(ISIL_TRACE_DEBUG,"niCda=%d\n",*niCda);
                          }
                         else
                          {
                                *niCda=MTP3_NIC_RESERVED;
                                ISIL_TRACE(ISIL_TRACE_DEBUG,"niCda=%d\n",*niCda);
                          }
                     }
                     else
                     {
                          *niCda=MTP3_NIC_NATIONAL;
                          ISIL_TRACE(ISIL_TRACE_DEBUG,"niCda=%d\n",*niCda);
                     }
                  }
                 else
                  {
                      *niCda=MTP3_NIC_SPARE;
                      ISIL_TRACE(ISIL_TRACE_DEBUG,"niCda=%d\n",*niCda);
                  }
                }
               else
                {
                     *niCda=MTP3_NIC_INTERNATIONAL;
                     ISIL_TRACE(ISIL_TRACE_DEBUG,"niCda=%d\n",*niCda);

                }

          }
        else
          {
           *dpc=0;
          }  
    }
     /*if dpc is present*/
   if(tmp[0]&0x01==1)
     { 
      /*calling party */
       *opc=tmp[1]|tmp[2]<<8;
        ISIL_TRACE(ISIL_TRACE_DEBUG,"opc=%d\n",*opc);
 
        if(tmp[0]&0x02==0x02)  ssnCpa=tmp[3];
             if (ROUTE_GetRouteContextStatus(*opc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ITU,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          ssnCpa,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                             ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
              {
                 if (ROUTE_GetRouteContextStatus(*opc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ITU,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),ssnCpa,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                 {
                    if (ROUTE_GetRouteContextStatus(*opc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ITU,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),ssnCpa,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                     {
                         if (ROUTE_GetRouteContextStatus(*opc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ITU,
                                               (MTP3_NIC_RESERVED |MTP3_SIO_SCCP ),ssnCpa,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                          {
                                  printf("SET SSN FAIL");
                                 *niCpa=gtt_ni;
                                  ISIL_TRACE(ISIL_TRACE_DEBUG,"niCpa=%d\n",*niCpa);
                          }
                         else
                          {
                                *niCda=MTP3_NIC_RESERVED;
                                ISIL_TRACE(ISIL_TRACE_DEBUG,"niCpa=%d\n",*niCpa);
                          }
                     }
                     else
                     {
                          *niCpa=MTP3_NIC_NATIONAL;
                          ISIL_TRACE(ISIL_TRACE_DEBUG,"niCpa=%d\n",*niCpa);
                     }
                  }
                 else
                  {
                      *niCpa=MTP3_NIC_SPARE;
                      ISIL_TRACE(ISIL_TRACE_DEBUG,"niCpa=%d\n",*niCpa);
                  }
                }
               else
                {
                     *niCpa=MTP3_NIC_INTERNATIONAL;
                     ISIL_TRACE(ISIL_TRACE_DEBUG,"niCpa=%d\n",*niCpa);
                }
       }
      else
       {
         *opc=gtt_opc;
       }
  


      *sio=(*niCda)|MTP3_SIO_SCCP;

}
#endif
