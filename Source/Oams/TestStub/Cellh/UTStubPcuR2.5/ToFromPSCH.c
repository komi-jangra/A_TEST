/****************************File Header*********************
File Name      :    ToFromPSCH.c
Purpose        :                 
Project        :    GSM
Subsystem      :    IPC 
Author         :    
CSCI id        :
Version        :    V0.1
*************************************************************/

/*******************************************Change History***
S.No.   Release        Patch        Author        Description
1.      Rel0.0         None         xxxxx         Creation
*************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<sysxxx_macro.h>
#include<sysxxx_hashdefs.h>
#include<sysxxx_typedef.h>
#include<sysxxx_msgopcode.h>
#include<sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include<sysinst_hashdefs.h>
#include<sysxxx_msgstruct.h>
#include<ipcfrm_syslog.h>
#include<ipcfrm_msgqueue.h>
#include<ipcfrm_extern.h>
#include<ipcinst_dbstruct.h>
#include<ipcinst_extern.h>
#include <dbsxxx_commondefs.h>
#include<csappxxx_common_datastruct.h>
#include<oamxxx_hashdefs.h>
#include<oamsxxx_typedef.h>
#include<oamsxxx_hashdef.h>
#include<oamxxx_datastruct.h>
#include<oamxxx_msgstruct.h>
#include<oams_msgstruct.h>
#include<oamsxxx_msgstruct.h>
#include<syspcu_typedefs.h>//NEW
#include<syspcu_datastruct.h>//NEW

I_PVoid Build_OamsPschCellhPsCellEnabled(I_S32 *);
I_PVoid Build_OamsPschCellhPsCellDisabled(I_S32 *);
I_PVoid Build_OamsPschGrhmCrsInd(I_S32 *);
I_PVoid Build_OamsPschTrxhPsAttrChangeInd(I_S32 *);
void ReceiveData();

main()
{
   I_S32 srcId,result=0,size=0;
   int choice ;
   I_SL32 priority;
   I_S8 buffer[100];
   I_PVoid bufferPtr;
   I_U32 ch=0 ;
   
   srcId = (int)ENT_OAMS_PSCH;
   if(RegisterWithIpcFrmwrk((int)ENT_OAMS_PSCH, (I_S8 *)"ENT_OAMS_PSCH")!=0)
   {
      fprintf(stderr,"Counld not register with framework\n");
   }

   while(1)
   {
      fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------------- \n");
      fprintf(stderr, "-------->> 1.To Send OAMS_PSCH_CELLH_PS_CELL_ENABLED    \n");
      fprintf(stderr, "-------->> 2.To Send OAMS_PSCH_CELLH_PS_CELL_DISABLED   \n");
      fprintf(stderr, "-------->> 3.To Send OAMS_PSCH_GRHM_CRS_IND             \n");
      fprintf(stderr, "-------->> 4.To Send OAMS_PSCH_TRXH_PS_ATTR_CHANGE_IND  \n");
      fprintf(stderr, "-------->> 5.To Receive data                            \n");
      
      scanf("%d", &choice);
      switch(choice)
      {

         case 1 :
                 bufferPtr = Build_OamsPschCellhPsCellEnabled(&size);
                 ch = 1;
                 break;
         case 2 :
                bufferPtr = Build_OamsPschCellhPsCellDisabled(&size);
                 ch = 1;
                 break;
         case 3 :
                bufferPtr = Build_OamsPschGrhmCrsInd(&size);
                 ch = 1;
                 break;
         case 4 :
                bufferPtr = Build_OamsPschTrxhPsAttrChangeInd(&size);
                 ch = 1;
                 break;
         case 5 :
                ReceiveData() ;
                ch = 0 ;
                break ;
         default :
                fprintf(stderr, "\n INVALID CHOICE \n");
                continue ;

      }// switch choice
      if(ch==1)
      {
         if (bufferPtr != NULL && size > 0)
         {
            if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
            {
               exit(0);
            }
          }
       }

   }// while(1)

}//Main                                                                                 

void ReceiveData()
{
    I_PVoid         rcvPtr ;
    I_S32           msgSize;
    I_U16           msgType ;
    I_PVoid         bufferPtr ;
    I_U8            entId;
    while(1)
    {
       rcvPtr = (I_PVoid)RecvMsg((int)(ENT_OAMS_PSCH), &msgSize);
       fprintf(stderr,"No of Bytes received = [%d]\n",msgSize);
       if(msgSize <= 0)
       {
          continue ;
       }
       else
       {
           break ;
       }
    }
    if(rcvPtr == NULL)
    {
       fprintf(stderr,"Could not read from Framework\n") ;
       return ;
    }

    msgType = ((SysHdr *)rcvPtr)->msgType ;
    entId = ((SysHdr *) rcvPtr)->dest.entity ;
    fprintf(stderr,"Received msg with msgType [%d]\n",msgType) ;
    fprintf(stderr,"Received msg with EntityId [%d]\n",entId) ;

    switch (msgType)
    {
       case CSAPP_GRHM_PSCH_ACT_PDCH_IND:
            fprintf(stderr," ACT PDCH IND received from GRHM\n") ;
            break;     
       case OAMS_TRXH_PSCH_PS_ALLOWED :        
            fprintf(stderr," PS ALLOWED received from TRXH\n") ;
            break;     
       case OAMS_TRXH_PSCH_PS_NOT_ALLOWED :        
            fprintf(stderr," PS NOT ALLOWED received from TRXH\n") ;
            break;     
       default:
              fprintf(stderr,"Invalid message received from SIM\n") ;

    }
    if (rcvPtr != NULL)
       DalocMsgBuf(rcvPtr) ;
}//ReceiveData()


I_PVoid Build_OamsPschCellhPsCellEnabled(I_S32 *size)
{

   OamsPschCellhPsCellEnabled *ptr;
   I_U16      lac=3000;
   I_U16      cellId=3500;
   I_U16      len=0;
   
   fprintf(stderr, "-------->>Enter LAC, for which PS_CELL_ENABLED is - \n ");
   scanf("%d",&lac);
   fprintf(stderr, "-------->>Enter CELL ID, for which PS_CELL_ENABLED is -  \n");            
   scanf("%d",&cellId);
   len = sizeof(OamsPschCellhPsCellEnabled);
   if((ptr = (OamsPschCellhPsCellEnabled *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   ptr->lac    = lac;
   ptr->cellId = cellId;
   fprintf(stderr,"Initial Msg (lac = %d : cellId = %d) \n", lac, cellId);
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),OAMS_PSCH_CELLH_PS_CELL_ENABLED, 1,PRCR_CP, ENT_OAMS_PSCH,0,PRCR_CP, ENT_OAMS_CELLH,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;
}//Build_OamsPschCellhPsCellEnabled


I_PVoid Build_OamsPschCellhPsCellDisabled(I_S32 *size)
{

   OamsPschCellhPsCellDisabled *ptr;
   I_U16      lac=0;
   I_U16      cellId=0;
   I_U16      len=0;

   fprintf(stderr, "-------->>Enter LOCATION AREA CODE, for which PS_CELL_ENABLED is - \n ");
   scanf("%d",&lac);
   fprintf(stderr, "-------->>Enter CELL ID, for which PS_CELL_ENABLED is -  \n");         
   scanf("%d",&cellId);
   len = sizeof(OamsPschCellhPsCellDisabled);
   if((ptr = (OamsPschCellhPsCellDisabled *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   ptr->lac    = lac;
   ptr->cellId = cellId;
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),OAMS_PSCH_CELLH_PS_CELL_DISABLED, 1,PRCR_CP, ENT_OAMS_PSCH,0,PRCR_CP, ENT_OAMS_CELLH,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;
}//Build_OamsPschCellhPsCellDisabled



I_PVoid Build_OamsPschGrhmCrsInd(I_S32 *size)
{

   OamsPschGrhmCrsInd *ptr;
   OamsCellIndex    cellIndex;
   I_U16      len=0,lac=0,cellId=0;
   I_U8       availPS=1,relPS=0,cause=0,maxNumPDCH=0;
   I_U8       isMaxNumPdchPresent=0,isRelPsValid=0,isCausePresent=0;
   
   fprintf(stderr, "-------->>Enter LOCATION AREA CODE, for which CRS_IND is - \n ");
   scanf("%u",&lac);
   fprintf(stderr, "-------->>Enter CELL ID, for which CRS_IND is -  \n");         
   scanf("%u",&cellId);
   fprintf(stderr, "-------->>Enter CELL INDEX, for which CRS_IND is -  \n");         
   scanf("%u",&cellIndex);
   fprintf(stderr, "-------->>Enter AVAIL PS(0/1), for which CRS_IND is -  \n");         
   scanf("%u",&availPS);
   fprintf(stderr, "-------->>Enter REL PS(0/1), for which CRS_IND is -  \n");         
   scanf("%u",&relPS);
   fprintf(stderr, "-------->>Enter CAUSE, for which CRS_IND is -  \n");         
   scanf("%u",&cause);
   fprintf(stderr, "-------->>Enter MAX NUM PDCH, for which CRS_IND is -  \n");         
   scanf("%u",&maxNumPDCH);
   len = sizeof(OamsPschGrhmCrsInd);
   if((ptr = (OamsPschGrhmCrsInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   ptr->lac        = lac;
   ptr->cellId     = cellId;
   ptr->cellIndex  = cellIndex;
   ptr->availPS    = availPS;
   ptr->relPS      = relPS;
   ptr->cause      = cause;
   ptr->maxNumPDCH = maxNumPDCH;   
   if(availPS)
   { 
     isMaxNumPdchPresent = 1;
   }
   else
   {
     isRelPsValid = 1;
   } 
   if(relPS)
    isCausePresent = 1;
 
   ptr->isMaxNumPdchPresent = isMaxNumPdchPresent;
   ptr->isRelPsValid        = isRelPsValid;
   ptr->isCausePresent      = isCausePresent;     

   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),OAMS_PSCH_GRHM_CRS_IND, 1,PRCR_CP, ENT_OAMS_PSCH,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;
}//Build_OamsPschGrhmCrsInd
   

I_PVoid Build_OamsPschTrxhPsAttrChangeInd(I_S32 *size)
{

   OamsPschTrxhPsAttrChangeInd *ptr;
   I_U8       temp;
   I_U32      ptrxId=0;
   I_U16      cbl=5;
   I_U16      len=0;

   fprintf(stderr, "-------->>Enter CBL, for which PS_ATTR_CHANGE_IND is -  \n");         
   scanf("%u",&cbl);
   
   fprintf(stderr, "-------->>Enter PTRXID, for which PS_ATTR_CHANGE_IND is - \n ");
   scanf("%u",&ptrxId);

   len = sizeof(OamsPschTrxhPsAttrChangeInd);
   if((ptr = (OamsPschTrxhPsAttrChangeInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   ptr->ptrxId    = ptrxId;
   ptr->cbl = (I_U8)cbl;
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),OAMS_PSCH_TRXH_PS_ATTR_CHANGE_IND, 1,PRCR_CP, ENT_OAMS_PSCH,0,PRCR_CP, ENT_OAMS_TRXH,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);

   fprintf(stderr,"ptrxId = %d : cbl=%d) \n", ptr->ptrxId, ptr->cbl);
   return ptr;
}//Build_PS_ATTR_CHANGE_IND
