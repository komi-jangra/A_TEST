/********************************************************************************************************
#  Date :27 Dec 06
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
#  ... Devloping started from 27 Dec06
#  ... Testing finalized on  
#
#   changes related to             Date                by
#
#     1.
#
#     2.
#
********************************************************************************************************/



#include <stdio.h>
#include "Coder.h"
#define SCCP_MAX_GTT_SEG_DATA  140

int
MandFix_Decoder(ITS_EVENT event ,ITS_OCTET **mandptr)	
{
 ITS_OCTET msgtype;
  msgtype=event.data[0];
   
  if (msgtype==SCCP_MSG_NOTICE || msgtype==SCCP_MSG_UDTS)
  	{
            *mandptr=&event.data[SCCP_HEADER];
  	}
}  














 /*****************************************************************************
 *  Purpose:
 *      This function Decoder of Args towards TCAP.
 *
 *  Input Parameters:
 *      ITS_EVENT *ev
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      If the decode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  --------------------------------------------------------------------------

*****************************************************************************/
int
Args_Decoder(ITS_EVENT event,ITS_OCTET *nmargs)
 {
  ITS_OCTET msgtype;

       msgtype=event.data[0];
    if (msgtype==SCCP_MSG_UDT||msgtype==SCCP_MSG_NOTICE || msgtype==SCCP_MSG_UDTS)
     {
         *nmargs=1;
     }
    else if(msgtype==SCCP_MSG_XUDT||msgtype==SCCP_MSG_LUDT)
     {
         *nmargs=2;
     }
 }





 /*****************************************************************************
 *  Purpose:
 *      This function Decoder of Called party towards TCAP.
 *
 *  Input Parameters:
 *      ITS_EVENT *ev
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      If the decode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  --------------------------------------------------------------------------

*****************************************************************************/

extern"C"
{
int
CDA_Decoder(ITS_EVENT event ,ITS_OCTET **cdaptr)

 {
  ITS_OCTET offset;
  ITS_OCTET nmargs;
  ITS_OCTET msgtype;
  ITS_OCTET *b;
  ITS_OCTET len;

   msgtype=event.data[0];

   Args_Decoder(event,&nmargs);
 
   offset=event.data[SCCP_HEADER+nmargs];

  if (msgtype==SCCP_MSG_LUDT)
   {
     
       *cdaptr=&event.data[SCCP_HEADER+nmargs+offset+1];  

   }
  else
   {
       *cdaptr=&event.data[SCCP_HEADER+nmargs+offset];    
   }

 }

 /*****************************************************************************
 *  Purpose:
 *      This function Decoder of Calling party towards TCAP.
 *
 *  Input Parameters:
 *      ITS_EVENT *ev
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      If the decode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  --------------------------------------------------------------------------

*****************************************************************************/
int
CPA_Decoder(ITS_EVENT event ,ITS_OCTET **cpaptr)
 {
 
  ITS_OCTET *noffset;
  ITS_OCTET *offset;
  ITS_OCTET nmargs;
  ITS_OCTET msgtype;
  ITS_OCTET *b=0;

   msgtype=event.data[0];

   Args_Decoder(event,&nmargs);

   noffset=&event.data[SCCP_HEADER+nmargs];

  if (msgtype==SCCP_MSG_LUDT)
   {
      offset=noffset+2;
     *cpaptr=&event.data[SCCP_HEADER+nmargs+(*offset+2)+1];

   /*add 2 due to previous called party offset of two byte */

   }
  else
   {
   /*condition for XUDT and UDT messages */

      offset=noffset+1;
     *cpaptr=&event.data[SCCP_HEADER+nmargs+(*offset+1)];

   /*add 2 due to previous called party offset of two byte */
   }


 }



 /*****************************************************************************
 *  Purpose:
 *      This function Decoder of User data towards TCAP.
 *
 *  Input Parameters:
 *      ITS_EVENT *ev
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      If the decode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  --------------------------------------------------------------------------

*****************************************************************************/
int
Userdata_Decoder(ITS_EVENT event ,ITS_OCTET **Usrdatptr)

 {
  ITS_OCTET *noffset=0;
  ITS_OCTET offset=0;
  ITS_OCTET nmargs;
  ITS_OCTET msgtype;
  ITS_OCTET *b=0;
  ITS_USHORT len=0;

    msgtype=event.data[0];

    Args_Decoder(event,&nmargs);

    noffset=&event.data[SCCP_HEADER+nmargs];

  if (msgtype==SCCP_MSG_LUDT)
   {
       noffset=noffset+4;
       offset=*noffset;

       *Usrdatptr=&event.data[SCCP_HEADER+nmargs+(offset+4)+1];
   
     /*add 4 due to previous called and calling party offset have two byte each*/ 

   }
  else
   {
       noffset=noffset+2;
       offset=*noffset;

       *Usrdatptr=&event.data[SCCP_HEADER+nmargs+(offset+2)];

     /*add 4 due to previous called and calling party offset have two byte each*/ 
   }


 }


 /*****************************************************************************
 *  Purpose:
 *      This function used as  Decoder of optinal parameter,message towards TCAP.
 *
 *  Input Parameters:
 *      ITS_EVENT *ev
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      If the decode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  --------------------------------------------------------------------------

*****************************************************************************/

int
OP_Decoder(ITS_EVENT event ,ITS_OCTET **OPptr,ITS_OCTET *noargs)
 {
  ITS_OCTET *noffset=0;
// ITS_OCTET offset;
  ITS_OCTET OFF[2];
  ITS_USHORT offset;
  ITS_OCTET nmargs;
  ITS_OCTET msgtype;
  ITS_OCTET i=0;
  ITS_OCTET EOP=1;
  ITS_OCTET *p=0;

   *noargs=0;
   msgtype=event.data[0];

   Args_Decoder(event,&nmargs);

   noffset=&event.data[SCCP_HEADER+nmargs];

   if (msgtype==SCCP_MSG_LUDT)
    {
        noffset=noffset+6;
       /*due to 3 offset after the pointer noffset and every offset has two byte*/


        OFF[0]=noffset[0];/*taken 1 byte of offset*/ 
        OFF[1]=noffset[1];/*taken 2 byte of offset*/
        offset=noffset[0]|noffset[1]<<8;       

        p=&event.data[SCCP_HEADER+nmargs+(offset+6)+1];

         OPptr[*noargs]=p;

    /*add 6 due two three previuos offset and addtion 1 due to two byte of offset*/
    
   while (EOP!=0)
    { 
        (*noargs)++;
             OPptr[*noargs]=p+p[1]+2;  /*  13-02-07 */
             p=OPptr[*noargs];
            // printf("\np[0]=%d",p[0]);      


    /*In 3 ,2 stand for op length and 1 for paramid*/ 

             EOP=*OPptr[*noargs];
    
   }
  } /*end of if*/

 else if (msgtype==SCCP_MSG_XUDT)
  {
       noffset=noffset+3 ;

    /*due to 3 offset after the pointer noffset*/

      offset=*noffset;

      p=&event.data[SCCP_HEADER+nmargs+(offset+3)];

      OPptr[*noargs]=p;

    /*addtion due to two byte of offset*/
    
   while (EOP!=0)
    {
      (*noargs)++;

          OPptr[*noargs]=p+p[1]+2;    /* 13-02-07 */
          p=OPptr[*noargs];

    /*In Add  3 ,2 stand for op length and 1 for paramid*/

      EOP=*OPptr[*noargs];

   }
  } /*end of esle*/

 }



 /*****************************************************************************
 *  Purpose:
 *      This function Encodes the event towards TCAP.
 *
 *  Input Parameters:
 *      ITS_EVENT *ev
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      If the decode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  --------------------------------------------------------------------------

*****************************************************************************/

int
EVENT_Encoder(ITS_OCTET *cdaptr ,ITS_OCTET *cpaptr ,ITS_OCTET *Usrdatptr,ITS_OCTET **OPptr ,ITS_OCTET msgtype,ITS_EVENT *event,ITS_OCTET *noargs,ITS_OCTET *mandptr)

 {
  ITS_OCTET cdamsg;
  ITS_OCTET cpamsg;
  ITS_OCTET UsrDatmsg;
  ITS_OCTET i;
  ITS_USHORT length=0;
  ITS_USHORT len=0;
  ITS_USHORT Usrdatlen;
  ITS_OCTET cpalen;
  ITS_OCTET cdalen;
  ITS_EVENT ev;
  ITS_OCTET totalsegment=0;
  ITS_OCTET value=0;
 
   if (msgtype==SCCP_MSG_UDT)
    {
          length =TCAP_HEADER+(*cdaptr+2)+(*cpaptr+2)+(*Usrdatptr+2);

          /*addtion of two shows len of every parameter conatin two byte*/ 
    }
   else if((msgtype==SCCP_MSG_NOTICE) || (msgtype==SCCP_MSG_UDTS))
    {
     length =TCAP_HEADER+1+(*cdaptr+2)+(*cpaptr+2)+(*Usrdatptr+2);

    }
   else if (msgtype==SCCP_MSG_XUDT)
   {
	 // length =TCAP_HEADER+(*cdaptr+2)+(*cpaptr+2)+(*Usrdatptr+2)+(*(OPptr[0]+1)+3);
          length =TCAP_HEADER+(*cdaptr+2)+(*cpaptr+2)+(*Usrdatptr+2);
                
          for (i=0;i<(*noargs);i++)
          {
           length+=(*(OPptr[i]+1)+3);

           if (*(OPptr[i])==0x10)
             {
             length-=3;
             }

          }

   }

  else if (msgtype==SCCP_MSG_LUDT)
   {
	/*  13-02-07 */
       ITS_USHORT Usrdatptr_new[2];
           Usrdatptr_new[0]= Usrdatptr[0];
           Usrdatptr_new[1]= Usrdatptr[1];

         /*In case of UDT len will be greater than 1 bytes so we will take another variable */
        /*  Usrdatlen=(Usrdatptr[1]|Usrdatptr[0]<<8)+2;*/

          Usrdatlen=(Usrdatptr_new[1]|Usrdatptr_new[0]<<8)+2;
           if(cdaptr[1] & SCCP_CPA_ROUTE_SSN)
           {
                value=0;
           }
          else
           {
              value=1;
           }


         Segment(Usrdatlen,&totalsegment,value); /*to calculate the total no of segment based upon the Usr data len*/

	 // printf("Usrdatptr[1]=%d",Usrdatptr[1]);
         // printf("\nUsrdatptr[0]=%d",Usrdatptr[0]);
         // printf("\nUsrdatptr_new[1]=%d",Usrdatptr_new[1]);
         // printf("\nUsrdatptr_new[0]=%d",Usrdatptr_new[0]);


          cpalen=cpaptr[0]+2;
          cdalen=cdaptr[0]+2;
       
//          length =TCAP_HEADER+cdalen+cpalen+Usrdatlen+(*(OPptr[0]+1)+3);
          length =TCAP_HEADER+cdalen+cpalen+Usrdatlen;
           for (i=0;i<(*noargs);i++)
             {
               length+=(*(OPptr[i]+1)+3);

               if (*(OPptr[i])==0x10)
                {
                 length-=3;
                }
            }

           /*addtion of two shows len of every parameter
                conatin two byte abd 1 extra in OP due to paramid */ 
   }
 ITS_OCTET offset;
   if((msgtype==SCCP_MSG_NOTICE) || (msgtype==SCCP_MSG_UDTS))
   {
     offset=1;
   }
   else
   {
     offset=0;

   }

   ITS_OCTET args=0;
   ITS_USHORT new_offset=0;

  if (*noargs)
   {
     args=3+(*noargs); /*in *noargs EOP are include so we have substarct -1*/
   }
 else
  {
      if((msgtype==SCCP_MSG_NOTICE)||( msgtype==SCCP_MSG_UDTS))
 	{
         args=3+1;/*due to three mand var and fixed mand*/
 	}
       else 
        {
          args=3;
        }
   }

   ITS_EVENT_INIT(event,ITS_TCAP_SRC ,length*sizeof(ITS_OCTET));

     if ((msgtype==SCCP_MSG_NOTICE)||( msgtype==SCCP_MSG_UDTS))
    {
       event->data[0]=0xb4;                                     /*api id*/
    }
    else
    {
      event->data[0]=0xb3;                                     /*api id*/
    }
      event->data[1]=0x01;                                      /*ver */
      event->data[2]=args;                                     /*number of ele*/
      event->data[3]=(length)&0xff;                            /*len*/
      event->data[4]=((length&0xff00)>>8 );
      if ((msgtype==SCCP_MSG_NOTICE)||(msgtype==SCCP_MSG_UDTS))
      {
       event->data[5]=*mandptr;                                     /*api id*/
      }
    
      event->data[5+offset]=*cdaptr;
      event->data[5+offset+1]=cdaptr[0]<<8;
      memcpy(&event->data[5+offset+2],&cdaptr[1],*cdaptr);
      offset=offset+(*cdaptr)+2;

      /*add of two due to length have two byte */


      event->data[5+offset]=*cpaptr;
      event->data[5+offset+1]=(cpaptr[0])<<8;
      memcpy(&event->data[5+offset+2],&cpaptr[1],*cpaptr);
      offset=offset+(*cpaptr)+2;

      /*2 means len have 2 byte*/

     if (msgtype==SCCP_MSG_LUDT)
      {
	/*  13-02-07 */ 
         ITS_USHORT Usrdatptr_New[2];
         Usrdatptr_New[0]= Usrdatptr[0];
         Usrdatptr_New[1]= Usrdatptr[1];

        event->data[5+offset]=Usrdatptr[1]; /*change the byte posiiton form SCCP to TCAP*/
        event->data[5+offset+1]=Usrdatptr[0];
        len=Usrdatptr_New[1]|Usrdatptr_New[0]<<8;

         // printf("\nUsrdatptr_new[1]=%d",Usrdatptr_New[1]);
         // printf("\nUsrdatptr_new[0]=%d",Usrdatptr_New[0]);

        memcpy(&event->data[5+offset+2],&Usrdatptr[2],len);
      } 

      else
      {   

        event->data[5+offset]=Usrdatptr[0];
        event->data[5+offset+1]=0;
        len=Usrdatptr[0];

        memcpy(&event->data[5+offset+2],&Usrdatptr[1],len);
      }

      new_offset=offset+len+2;

    /*2 means len have 2 byte*/


     if (msgtype==SCCP_MSG_LUDT||msgtype==SCCP_MSG_XUDT||SCCP_MSG_UDT)
     {

        for(i=0;i<(*noargs);i++)
         {
          if (*OPptr[i]==0)
           {
             break;
           }
          if (*OPptr[i]==0x10)
            {
             *OPptr[i]=0x23;

              event->data[5+new_offset]=*OPptr[i];/*param id of OP paramater*/
              event->data[5+new_offset+1]=1;
              event->data[5+new_offset+2]=0;
             //  event->data[5+new_offset+3]=*(OPptr[i]+2)&0x0f;/*remaining segment*/
              event->data[5+new_offset+3]=totalsegment;   /*total segment*/

 
             // memcpy(&event->data[5+new_offset+3],(OPptr[i]+2),*(OPptr[i]+1));
            new_offset+=4;
            }
          else
            {
 
              event->data[5+new_offset]=*OPptr[i];/*param id of OP paramater*/
              event->data[5+new_offset+1]=*(OPptr[i]+1);
              event->data[5+new_offset+2]=*(OPptr[i]+1)<<8;

              memcpy(&event->data[5+new_offset+3],(OPptr[i]+2),*(OPptr[i]+1));
             new_offset+=*OPptr[i]+3;
            } 
             //  offset+=*OPptr[i]+3;

       /*In offset, addtion of 3 means paramid and paramlen*/

         } 

     }


 }/*end of Event_decoder function*/

int
 Segment(ITS_USHORT len ,ITS_OCTET *Segment,ITS_OCTET value)

  {
    ITS_OCTET allowedseg=0;
    if ((len > 230 && value==0)||(len > 160 && value ==1))

     {
       if(len > 230 && value ==0)
         {
             allowedseg=SCCP_MAX_SEG_DATA;
         }
       else if(len > 160 && value ==1)
         {
             allowedseg=SCCP_MAX_GTT_SEG_DATA;
         }

       *Segment = len / allowedseg;
        if (len % allowedseg)
          {
                (*Segment)++;
          }
     }
    else
    {
        *Segment=0;
    }


  }



}/*end of extern"C"*/




