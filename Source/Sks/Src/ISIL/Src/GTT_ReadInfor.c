/*********************************************************************************************************
#  Date :07 Feb 07
#  Owner:Ashutosh Singh
#                     Copy right permission to IMR Pvt Ltd
#                                 2007-08
#
#   This product and related documentation is protected by copyright and
#   distributed under licenses restricting its use, copying, distribution
#   and decompilation.  No part of this product or related documentation
#   may be reproduced in any form by any means without prior written
#   authorization ofIMR Pvt Ltd and its licensors, if any.
#
#
# ...  Devloping started from 07 Feb 07
# ...  Finalized testing on
#   changes related to             Date                by
#
#     1.
#
#     2.
#
********************************************************************************************************/



#include <stdio.h>
#include "GTT_ReadInfor.h"
#include "trace.h"

#include <itu/sccp.h>
static int index;
char ISIL_ADDENTRY;
char ISIL_DELENTRY;
char ISIL_FREEENTRY;

ISIL_GTT_LIST *gtt_list;
#ifdef CCITT
#define SSNROUTE_CHECK  SSNROUTE_CHECK_CCITT 
#endif
#ifdef ANSI
#define SSNROUTE_CHECK  SSNROUTE_CHECK_ANSI
#endif
/*****************************************************************************
 *  Purpose:
 *      This function read the local database    
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *

*****************************************************************************/
int
ISIL_Console_CCITT(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    int ret=0,retn=0;
    int rtflag=0;
    int dpc_1=0,dpc_2=0,ssn=0;
    ITS_UINT i=0;
    char tmp[ITS_PATH_MAX] ,test[ITS_PATH_MAX],*tmp1=0 ;
    ISIL_gttInfo gttInfo;
    int len=0;

    memset(tmp ,0 ,ITS_PATH_MAX);
    memset(&gttInfo ,0 ,sizeof(ISIL_gttInfo));

   if (DBC_Cmd(dbc, "isil_set_dpc_ssn_table", "ISIL Set Dpc and SSN Table ","<gtai><dpc><ssn>","<gtaistring><pointcode><subsytem>"))
      {
          ret = sscanf(cmdLine, "%s %s %d %d %d %d", buf,tmp,&dpc_1,&dpc_2,&ssn,&rtflag);
          if (ret!=6)
           {
              sprintf(buf, "**** Invalid Command Arguments *******\n");
              DBC_AppendText(dbc, buf);
              return;
           }
          len=strlen(tmp);
          memcpy(gttInfo.str,tmp,len);
          gttInfo.primarydpc=dpc_1;
          gttInfo.secondarydpc=dpc_2;
          gttInfo.ssn=ssn;
          gttInfo.routeflag=rtflag;

      //    memcpy(gttInfo.gttstring,tmp,len);
            for(i=0;i<strlen(tmp);i++)
            {
               gttInfo.gttstring[i]=tmp[i]-48;
                 
            }

         gttInfo.gttstring[i]='\0'; 
         retn=ISIL_setgttentry(&gttInfo);

         if (retn==IMR_ENTRYADDSUCC)
           {
                sprintf(buf, "****Set Entry in DPC TAble Succesfully *******\n");
           }
         else if (retn==IMR_ENALRDYEXIST)
           { 
               sprintf(buf, "****Set Entry in DPC TAble Already Exist *******\n");
           }
         else if (retn==IMR_ENTRYADDFAIL)
           { 
               sprintf(buf, "****Set Entry in DPC TAble fail *******\n");
           }

         DBC_AppendText(dbc, buf);

      }

    else if (DBC_Cmd(dbc, "isil_rem_dpc_ssn_table", "ISIL Set Dpc and SSN Table ", "<gtai><dpc><ssn>","<gtaistring><pointcode><subsytemnumber>"))
     {
          ret = sscanf(cmdLine,"%s %s %d %d %d", buf,tmp,&dpc_1,&dpc_2,&ssn);
          if (ret!=5)
           {
              sprintf(buf, "**** Invalid Command Arguments *******\n");
              DBC_AppendText(dbc, buf);
              return;
           }
           
          len=strlen(tmp);
          memcpy(gttInfo.str,tmp,len);
          gttInfo.primarydpc=dpc_1;
          gttInfo.secondarydpc=dpc_2;
          gttInfo.ssn=ssn;

      //    memcpy(gttInfo.gttstring,tmp,len);
            for(i=0;i<strlen(tmp);i++)
            {
               gttInfo.gttstring[i]=tmp[i]-48;
                 
            }
         retn=ISIL_remgttentry(&gttInfo);
         if (retn==IMR_ENTRYREMSUCC)
           {
            sprintf(buf, "****Rem Entry in DPC TAble Succesfully *******\n");
           }
         else if (retn==IMR_ENTRYNOFOUND)
           { 
             sprintf(buf, "****Rem Entry in DPC TAble Not Found *******\n");
           }
         else if (retn==IMR_ENTRYREMFAIL)
           { 
             sprintf(buf, "****Rem Entry in DPC TAble fail *******\n");
           }
          DBC_AppendText(dbc,buf);

     }

}
#ifdef CCITT
/*****************************************************************************
 *  Purpose:
 *      This function init the Tree Structure for database   
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
******************************************************************************/
ITS_INT
SSNROUTE_CHECK_CCITT(ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_BOOLEAN isAllowed;
    ITS_INT ret=ITS_SUCCESS;
    ITS_OCTET ni=0;


    if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ITU,
                                    (ROUTE_SIO_SCCP |MTP3_NIC_INTERNATIONAL) ,
                                    ssn,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
      {
            if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                         ROUTE_DPC_SIO_SSN,
                                         FAMILY_ITU,
                                         (ROUTE_SIO_SCCP |MTP3_NIC_SPARE) ,
                                         ssn,
                                         ITS_SS7_DEFAULT_LINK_SET,
                                         ITS_SS7_DEFAULT_LINK_CODE,
                                         ITS_SS7_DEFAULT_PRI,
                                         ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                            ROUTE_DPC_SIO_SSN,
                                            FAMILY_ITU,
                                            (ROUTE_SIO_SCCP |MTP3_NIC_NATIONAL) ,
                                            ssn,
                                            ITS_SS7_DEFAULT_LINK_SET,
                                            ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,
                                            ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                    {
                          if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                                    ROUTE_DPC_SIO_SSN,
                                                    FAMILY_ITU,
                                                    (ROUTE_SIO_SCCP |MTP3_NIC_RESERVED) ,
                                                    ssn,
                                                    ITS_SS7_DEFAULT_LINK_SET,
                                                    ITS_SS7_DEFAULT_LINK_CODE,
                                                    ITS_SS7_DEFAULT_PRI,
                                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                             {
                                 ISIL_ERROR_TRACE(("SSN NOT CONFIGURED \n"));
                                 return (!ITS_SUCCESS);
                             }

                    } 

           }


      }
        return (ITS_SUCCESS);

}
#endif
#ifdef ANSI
/*****************************************************************************
 *  Purpose:
 *      This function init the Tree Structure for database   
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
******************************************************************************/
ITS_INT
SSNROUTE_CHECK_ANSI(ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_BOOLEAN isAllowed;
    ITS_INT ret=ITS_SUCCESS;
    ITS_OCTET ni=0;


    if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                    ROUTE_DPC_SIO_SSN,
                                    FAMILY_ANSI,
                                    (ROUTE_SIO_SCCP |MTP3_NIC_INTERNATIONAL) ,
                                    ssn,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE,
                                    ITS_SS7_DEFAULT_PRI,
                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
      {
            if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                         ROUTE_DPC_SIO_SSN,
                                         FAMILY_ANSI,
                                         (ROUTE_SIO_SCCP |MTP3_NIC_SPARE) ,
                                         ssn,
                                         ITS_SS7_DEFAULT_LINK_SET,
                                         ITS_SS7_DEFAULT_LINK_CODE,
                                         ITS_SS7_DEFAULT_PRI,
                                         ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                            ROUTE_DPC_SIO_SSN,
                                            FAMILY_ANSI,
                                            (ROUTE_SIO_SCCP |MTP3_NIC_NATIONAL) ,
                                            ssn,
                                            ITS_SS7_DEFAULT_LINK_SET,
                                            ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,
                                            ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                    {
                          if (ROUTE_GetRouteContextStatus(pc, &isAllowed,
                                                    ROUTE_DPC_SIO_SSN,
                                                    FAMILY_ANSI,
                                                    (ROUTE_SIO_SCCP |MTP3_NIC_RESERVED) ,
                                                    ssn,
                                                    ITS_SS7_DEFAULT_LINK_SET,
                                                    ITS_SS7_DEFAULT_LINK_CODE,
                                                    ITS_SS7_DEFAULT_PRI,
                                                    ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                             {
                                 ISIL_ERROR_TRACE(("SSN NOT CONFIGURED \n"));
                                 return (!ITS_SUCCESS);
                             }

                    } 

           }


      }
        return (ITS_SUCCESS);

}


#endif



/*****************************************************************************
 *  Purpose:
 *      This function init the Tree Structure for database   
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
******************************************************************************/
int
ISIL_initTree()
{
 gtt_list=(ISIL_GTT_LIST *)calloc(10,sizeof(ISIL_GTT_LIST));
 if(gtt_list==NULL)
 {
    ISIL_DEBUG_TRACE(("Init Tree for GTT Failed\n"));
 }

}


/*****************************************************************************
 *  Purpose:
 *      This function set the local database  from main database   
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
******************************************************************************/
 static int index;
int
ISIL_setgttentry(ISIL_gttInfo *gttInfo)
{
 ISIL_GTT_LIST *gtt=NULL;
 
 if(gtt_list== NULL) 
 {
   ISIL_DEBUG_TRACE(("Check Init Tree for GTT \n"));
   return (IMR_FALSE);
 }
 gtt=ISIL_BuildTree(&gtt_list[(gttInfo->gttstring[index])],gttInfo);
 if(gtt==NULL)
 {
   return IMR_ENTRYADDFAIL;

 }
 index=0;
// printf("Flag=%d",ISIL_ADDENTRY);
 if(ISIL_ADDENTRY == IMR_FALSE)
 {
   ISIL_DEBUG_TRACE((" GTT Entry Already Present \n"));
   return IMR_ENALRDYEXIST;
 }
 else
 {
 //  ISIL_DEBUG_TRACE((" GTT Entry Add Success \n"));
   return IMR_ENTRYADDSUCC;
 }

}

ISIL_GTT_LIST *ISIL_BuildTree(ISIL_GTT_LIST *gttentry,ISIL_gttInfo *gttInfo)
{

 int len=0;
 int i=0; 
 char *str=NULL;
 char temp[4];
 ISIL_DPC_SSN *dpc_ssn;

  len=strlen(gttInfo->str);

  if(len > 16)
   {
       ISIL_DEBUG_TRACE((" GTT Received String len is greater than max define len  \n"));
       return (NULL);
   }

  if(gttentry == NULL)
   {
        gttentry=(ISIL_GTT_LIST *)calloc(1,sizeof(ISIL_GTT_LIST));
       // ISIL_DEBUG_TRACE(("GTT next Ptr %x :\n",gttentry));
        if(gttentry==NULL)
        {
        } 
     //   ISIL_DEBUG_TRACE(("GTT_1:: index=%d len=%d :\n",index,len));

        if((index+1)==len)
        {
           dpc_ssn=(ISIL_DPC_SSN *)calloc(1,sizeof(ISIL_DPC_SSN));
           dpc_ssn->primarydpc=gttInfo->primarydpc;
           dpc_ssn->secondarydpc=gttInfo->secondarydpc;
           dpc_ssn->ssn=gttInfo->ssn;
           dpc_ssn->routeflag=gttInfo->routeflag;
           if((SSNROUTE_CHECK(gttInfo->primarydpc,gttInfo->ssn)==ITS_SUCCESS))
            {
                dpc_ssn->primaryssnflag=SSNALLOW;
                ISIL_DEBUG_TRACE(("GTT :SSN is allowed with dpc_1 \n"));
            }
          else
            {
                dpc_ssn->primaryssnflag=NOSSNALLOW;
                ISIL_DEBUG_TRACE(("GTT :SSN is not allowed with dpc_1 \n"));
            }
 
           if((SSNROUTE_CHECK(gttInfo->secondarydpc,gttInfo->ssn)==ITS_SUCCESS))
           {
               dpc_ssn->secondaryssnflag=SSNALLOW;
               ISIL_DEBUG_TRACE(("GTT :SSN is allowed with dpc_2 \n"));
           }
          else
           {
               dpc_ssn->secondaryssnflag=NOSSNALLOW;
               ISIL_DEBUG_TRACE(("GTT :SSN is not allowed with dpc_2 \n"));
           } 

            gttentry->Entry=dpc_ssn;
            ISIL_WARNING_TRACE((" GTT=%s\tdpc1=%d\tdpc_2=%d\tssn=%d\tssnflag=%d\n",gttInfo->str,dpc_ssn->primarydpc,dpc_ssn->secondarydpc,dpc_ssn->ssn,dpc_ssn->primaryssnflag));

           ISIL_ADDENTRY=IMR_TRUE;
         //  printf("Flag=%d\n",ISIL_ADDENTRY);
           return (gttentry);
      }
      // printf("Flag=%d\n",ISIL_ADDENTRY);
       index++;
      // ISIL_DEBUG_TRACE(("GTT next Ptr %x :\n",gttentry));
       if(gttInfo->gttstring[index]==0x0A)
       {
        ISIL_DEBUG_TRACE(("\nValue in GTT is 0 "));
         gttentry->next[0]= ISIL_BuildTree(gttentry->next[0],gttInfo);
       }
       else
       {
       gttentry->next[(gttInfo->gttstring[index])]
           =ISIL_BuildTree(gttentry->next[(gttInfo->gttstring[index])],gttInfo);
       }
   }
  else 
   {
       index++;
     //  ISIL_DEBUG_TRACE(("GTT_2:: index=%d len=%d :\n",index,len));
       if((index)==len)
       {
          if(gttentry->Entry)
          {
              ISIL_ADDENTRY=IMR_FALSE;
               return (gttentry);
          }
          dpc_ssn=(ISIL_DPC_SSN *)calloc(1,sizeof(ISIL_DPC_SSN));

          dpc_ssn->primarydpc=gttInfo->primarydpc;
          dpc_ssn->secondarydpc=gttInfo->secondarydpc;
          dpc_ssn->ssn=gttInfo->ssn;
          dpc_ssn->routeflag=gttInfo->routeflag;

          if((SSNROUTE_CHECK(gttInfo->primarydpc,gttInfo->ssn)==ITS_SUCCESS))
          {
               dpc_ssn->primaryssnflag=SSNALLOW;
               ISIL_DEBUG_TRACE(("GTT :SSN is allowed with dpc_1 \n"));
          }
          else
          {
               dpc_ssn->primaryssnflag=NOSSNALLOW;
               ISIL_DEBUG_TRACE(("GTT :SSN is not allowed with dpc_1 \n"));
          } 
          if((SSNROUTE_CHECK(gttInfo->secondarydpc,gttInfo->ssn)==ITS_SUCCESS))
  
          {
               dpc_ssn->secondaryssnflag=SSNALLOW;
               ISIL_DEBUG_TRACE(("GTT :SSN is allowed with dpc_2 \n"));
          }
          else
          {
               dpc_ssn->secondaryssnflag=NOSSNALLOW;
               ISIL_DEBUG_TRACE(("GTT :SSN is not allowed with dpc_2 \n"));
          }
 
           gttentry->Entry=dpc_ssn;
            ISIL_DEBUG_TRACE((" GTT=%s\tdpc1=%d\tdpc_2=%d\tssn=%d\tssnflag=%d\n",gttInfo->str,dpc_ssn->primarydpc,dpc_ssn->secondarydpc,dpc_ssn->ssn,dpc_ssn->primaryssnflag));

        
         ISIL_ADDENTRY=IMR_TRUE;
         return (gttentry);
       }

       ISIL_ADDENTRY=IMR_FALSE;
       if(gttInfo->gttstring[index]==0x0A)
       {
        ISIL_DEBUG_TRACE(("\nValue in GTT is 0 "));
         gttentry->next[0]= ISIL_BuildTree(gttentry->next[0],gttInfo);
       }
       else
       {
         gttentry->next[(gttInfo->gttstring[index])]= ISIL_BuildTree(gttentry->next[(gttInfo->gttstring[index])],gttInfo);
 
       }
     //  printf("Flag=%d\n",ISIL_ADDENTRY);


   }
  return (gttentry);

}



int
ISIL_remgttentry(ISIL_gttInfo *gttInfo)
{
  char Ind=0;
  ISIL_GTT_LIST *gtt=NULL; 
  if(gtt_list== NULL) 
  {
      ISIL_DEBUG_TRACE(("Check Init Tree for GTT \n"));
      return (IMR_FALSE);
  }
  gtt=ISIL_DeleteTree(&gtt_list[(gttInfo->gttstring[Ind])],gttInfo,Ind);
  if(gtt==NULL)
   {
      return (IMR_ENTRYREMFAIL);

   }

  Ind=0;
 // printf("Flag=%d",ISIL_DELENTRY);

  if(ISIL_DELENTRY == IMR_FALSE)
  {
     ISIL_DEBUG_TRACE((" GTT Entry not Present \n"));
     return IMR_ENTRYNOFOUND;
  }
  else
  {
     ISIL_DEBUG_TRACE((" GTT Entry DEL Success \n"));
     return IMR_ENTRYREMSUCC;
  }

}


ISIL_GTT_LIST *ISIL_DeleteTree(ISIL_GTT_LIST *gttentry,ISIL_gttInfo *gttInfo,char Ind)
{
  int len=0;
  int i=0; 
  char lineartraverse=0;

  len=strlen(gttInfo->str);
  if(len > 16)
  {
      ISIL_DEBUG_TRACE((" GTT Received String len is greater than max define len  \n"));
      return (NULL);
  }

  if(gttentry==NULL || len == Ind )
  {
      ISIL_DEBUG_TRACE((" End of GTT Entry  \n"));
      return gttentry;
  }
 else
  {
       Ind++;
       ISIL_DELENTRY=IMR_FALSE;
       gttentry->next[(gttInfo->gttstring[Ind])]=
            ISIL_DeleteTree(gttentry->next[(gttInfo->gttstring[Ind])],gttInfo,Ind);

     //  printf("index=%d,string digit %d \n",Ind,gttInfo->gttstring[Ind]);
     //  printf("GTTentry=%x\n",gttentry);

       if(gttentry->next[(gttInfo->gttstring[Ind])]==NULL)
       {
            ISIL_DEBUG_TRACE((" GTT Entry  last  Found \n"));
	    if(gttentry->Entry!=NULL && gttInfo->gttstring[Ind]=='\0' )
            {
                 ISIL_DEBUG_TRACE((" GTT Entry  Found and Free\n"));
                 ISIL_DELENTRY=IMR_TRUE;
                 free(gttentry->Entry);
                 gttentry->Entry=NULL;

                 while(lineartraverse < 10)
                 {
                     if(gttentry->next[lineartraverse]==NULL)
                      {
                          lineartraverse++;
                          ISIL_FREEENTRY=IMR_TRUE;
                      }
                    else
                      {
                          ISIL_FREEENTRY=IMR_FALSE;
                          break;
                      }
                }

               if(ISIL_FREEENTRY==IMR_TRUE)
                {
                   ISIL_DEBUG_TRACE((" last Free Entry=%x\n",gttentry));
                   free(gttentry);
                   gttentry=NULL;
                }             
           }
 
       }
   return gttentry; 
 }

}
