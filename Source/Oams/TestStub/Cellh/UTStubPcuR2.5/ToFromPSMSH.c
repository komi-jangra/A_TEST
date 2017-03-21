/*se ts=2************************************File Header*****
File Name      :    ToFromPSMSH.c
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
#include<psappxxx_datastruct.h>//NEW
#include<psappxxx_msgstruct.h>//NEW
#include</home/gur13353/22-Dec-09/PCU/Source/Csapp/Inc/csapp_msgstruct.h>

I_PVoid Build_PsappPsmshGrhmMsResAllocReq(I_S32 *);
I_PVoid Build_PsappPsmshGrhmMsEstInd(I_S32 *);
I_PVoid Build_PsappPsmshGrhmMsResumeReq(I_S32 *);
I_PVoid Build_PsappPsmshGrhmMsRelInd(I_S32 *);
I_PVoid Build_PsappPsmshGrhmMsRelAck(I_S32 *);
I_PVoid Build_PsappPsmshGrhmMsAbnRelInd(I_S32 *);
I_PVoid Build_PsappPsmshGrhmMsTbfClassInd(I_S32 *);
I_PVoid Build_PsappPsmshGrhmMsReorgAck(I_S32 *);
I_PVoid Build_ExecRralUdcInd(I_S32 *);

void ReceiveData();

main()
{
   I_S32 srcId,result=0,size=0;
   int choice ;
   I_U8 tei;
   I_SL32 priority;
   I_S8 buffer[100];
   I_PVoid bufferPtr;
   I_U32 ch=0 ;

   srcId = (int)ENT_PSAPP_PSMSH ;

   if(RegisterWithIpcFrmwrk((int)ENT_PSAPP_PSMSH, (I_S8 *)"ENT_PSAPP_PSMSH")!=0)
   {
      fprintf(stderr,"Counld not register with framework\n");
   }

   while(1)
   {
      fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------------- \n");
      fprintf(stderr, "-------->> 1.To Send PSAPP_PSMSH_GRHM_MS_RES_ALLOC_REQ  \n");
      fprintf(stderr, "-------->> 2.To Send PSAPP_PSMSH_GRHM_MS_EST_IND        \n");
      fprintf(stderr, "-------->> 3.To Send PSAPP_PSMSH_GRHM_MS_RESUME_REQ     \n");
      fprintf(stderr, "-------->> 4.To Send PSAPP_PSMSH_GRHM_MS_REL_IND        \n");
      fprintf(stderr, "-------->> 5.To Send PSAPP_PSMSH_GRHM_MS_REL_ACK        \n");
      fprintf(stderr, "-------->> 6.To Send PSAPP_PSMSH_GRHM_MS_ABN_REL_IND    \n");
      fprintf(stderr, "-------->> 7.To Send PSAPP_PSMSH_GRHM_MS_TBF_CLASS_IND  \n");
      fprintf(stderr, "-------->> 8.To Send PSAPP_PSMSH_GRHM_MS_REORG_ACK      \n");
      fprintf(stderr, "-------->> 9.To Send EXEC_RRAL_UDC_IND                  \n");
      fprintf(stderr, "-------->> 10.To Receive data                           \n");

      scanf("%d", &choice);
      switch(choice)
      {
      
         case 1 :
                 bufferPtr = Build_PsappPsmshGrhmMsResAllocReq(&size);                                  
                 ch = 1;
                 break;  
         case 2 :
                 bufferPtr = Build_PsappPsmshGrhmMsEstInd(&size);                                  
                 ch = 1;
                 break;  
         case 3 :
                 bufferPtr = Build_PsappPsmshGrhmMsResumeReq(&size);                                  
                 ch = 1;
                 break;  
         case 4 :
                 bufferPtr = Build_PsappPsmshGrhmMsRelInd(&size);                                  
                 ch = 1;
                 break;  
         case 5 :
                 bufferPtr = Build_PsappPsmshGrhmMsRelAck(&size);                                  
                 ch = 1;
                 break;  
         case 6 :
                 bufferPtr = Build_PsappPsmshGrhmMsAbnRelInd(&size);                                  
                 ch = 1;
                 break;  
         case 7 :
                 bufferPtr = Build_PsappPsmshGrhmMsTbfClassInd(&size);                                  
                 ch = 1;
                 break;  
         case 8 :
                 bufferPtr = Build_PsappPsmshGrhmMsReorgAck(&size);                                  
                 ch = 1;
                 break;
         case 9 :
                 bufferPtr = Build_ExecRralUdcInd(&size);                                  
                 ch = 1;
                 break;
         case 10 :
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

}// main


void ReceiveData()
{
    I_PVoid         rcvPtr ;
    I_S32           msgSize;
    I_U16           msgType ;
    I_PVoid         bufferPtr ;
    I_U8            entId;
    while(1)
    {
       rcvPtr = (I_PVoid)RecvMsg((int)(ENT_PSAPP_PSMSH), &msgSize);
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
       case CSAPP_GRHM_PSMSH_MS_RES_ALLOC_ACK :
            fprintf(stderr,"MS RES ALLOC ACK received from GRHM\n") ;
            break ;
    
       case CSAPP_GRHM_PSMSH_MS_RES_ALLOC_NACK : 
            fprintf(stderr,"MS RES ALLOC NACK received from GRHM\n") ;
            break; 
 
       case CSAPP_GRHM_PSMSH_MS_RESUME_ACK :     
            fprintf(stderr,"MS RESUME ACK received from GRHM\n") ;
            break; 
        
       case CSAPP_GRHM_PSMSH_MS_RESUME_NACK :    
            fprintf(stderr,"MS RESUME NACK received from GRHM\n") ;
            break; 

       case CSAPP_GRHM_PSMSH_MS_REORG_REQ :     
            fprintf(stderr,"MS REORG REQ received from GRHM\n") ;
            break; 

       case CSAPP_GRHM_PSMSH_MS_REL_REQ :   
            fprintf(stderr,"MS REL REQ received from GRHM\n") ;
              break; 
       
       default:
              fprintf(stderr,"Invalid message received from SIM\n") ;

    }
    if (rcvPtr != NULL)
       DalocMsgBuf(rcvPtr) ;
}



I_PVoid Build_PsappPsmshGrhmMsResAllocReq(I_S32 *size)
{
   PsappPsmshGrhmMsResAllocReq *ptr;
   I_U16 len=0; 
   SyspcuMsId msId=1;
   SyspcuMsEstCause reqReason=0;
   CellIndex cellIndex=5;
   SyspcuMultislotClass msMultislotClass = 0;
   SyspcuOptFlag isMsMultislotClassPresent;
 
   fprintf(stderr, "-------->>Enter MSID, for which  RES_ALLOC_REQ is -     \n ");
   scanf("%u",&msId);
   fprintf(stderr, "-------->>Enter REQ REASON,for which RES_ALLOC_REQ is  -  \n");
   scanf("%u",&reqReason); 
   fprintf(stderr, "-------->>Enter CELL INDEX ,for which RES_ALLOC_REQ is  -  \n");
   scanf("%u",&cellIndex); 
   fprintf(stderr, "-------->>Enter DO MS MULTI SLOTCLASS PRESENT   ,for which RES_ALLOC_REQ is  -  \n");
   scanf("%u",&isMsMultislotClassPresent);
   if(isMsMultislotClassPresent)
   {
      fprintf(stderr, "-------->>Enter MS MULTI SLOTCLASS  ,for which RES_ALLOC_REQ is  -  \n");
      scanf("%u",&msMultislotClass);
   }  
   len = sizeof(PsappPsmshGrhmMsResAllocReq);
   if((ptr = (PsappPsmshGrhmMsResAllocReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)        
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   
   ptr->msId             = msId; 
   ptr->reqReason        = reqReason;
   ptr->cellIndex        = cellIndex;
   ptr->isMsMultislotClassPresent = 1;//isMsMultislotClassPresent;
   if(ptr->isMsMultislotClassPresent)
   {
      ptr->msMultislotClass = 1;//msMultislotClass;
   } 
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_PSMSH_GRHM_MS_RES_ALLOC_REQ, 1,PRCR_CP, ENT_PSAPP_PSMSH,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

}//Build_PsappPsmshGrhmMsResAllocReq


I_PVoid Build_PsappPsmshGrhmMsEstInd(I_S32 *size)
{
   PsappPsmshGrhmMsEstInd *ptr;
   I_U16                     len=0;
   SyspcuMsId                msId;
   SyspcuOptFlag             isMsMultislotClassPresent;
   SyspcuMultislotClass      msMultislotClass=0;
   SyspcuOptFlag             isTbfClassIndUlPresent;
   SyspcuTbfClassInd         tbfClassIndUl=0;

   fprintf(stderr, "-------->>Enter MSID, for which  MS_RES_ALLOC_REQ is -     \n ");
   scanf("%d",&msId);
   fprintf(stderr, "-------->>Enter DO MS MULTI SLOTCLASS PRESENT   ,for which MS_EST_IND is  -  \n");
   scanf("%d",&isMsMultislotClassPresent);
   if(isMsMultislotClassPresent)
   {
      fprintf(stderr, "-------->>Enter MS MULTI SLOTCLASS  ,for which MS_EST_IND is  -  \n");
      scanf("%d",&msMultislotClass);
   }
   fprintf(stderr, "-------->>Enter DO UL TBF CLASS IND PRESENT   ,for which MS_EST_IND is  -  \n");
   scanf("%d",&isTbfClassIndUlPresent);
   if(isTbfClassIndUlPresent)
   {
      fprintf(stderr, "-------->>Enter TBF CLASS IND UL  ,for which MS_RES_ALLOC_REQ is  -  \n");
      scanf("%d",&tbfClassIndUl);
   }
   len = sizeof(PsappPsmshGrhmMsEstInd);
   if((ptr = (PsappPsmshGrhmMsEstInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   
   ptr->msId             = msId;
   
   ptr->isMsMultislotClassPresent = isMsMultislotClassPresent;
   if(ptr->isMsMultislotClassPresent)
   { 
      ptr->msMultislotClass = msMultislotClass;
   }
   
   ptr->isTbfClassIndUlPresent = isTbfClassIndUlPresent;
   if(ptr->isTbfClassIndUlPresent)
   {
      ptr->tbfClassIndUl = tbfClassIndUl;
   }

   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_PSMSH_GRHM_MS_EST_IND, 1,PRCR_CP, ENT_PSAPP_PSMSH,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

}//Build_PsappPsmshGrhmMsEstInd



I_PVoid Build_PsappPsmshGrhmMsResumeReq(I_S32 *size)
{
   PsappPsmshGrhmMsResumeReq *ptr;
   I_U16                     len=0;
   SyspcuMsId                msId;
   SyspcuMsEstCause          reqReason;
   SyspcuOptFlag             isMsMultislotClassPresent;
   SyspcuMultislotClass      msMultislotClass;
   
   fprintf(stderr, "-------->>Enter MSID, for which  MS_RESUME_IND is -     \n ");
   scanf("%d",&msId);
   fprintf(stderr, "-------->>Enter REQ REASON,for which MS_RESUME_IND is  -  \n");
   scanf("%d",&reqReason); 
   fprintf(stderr, "-------->>Enter DO MS MULTI SLOTCLASS PRESENT   ,for which MS_RESUME_IND is  -  \n");
   scanf("%d",&isMsMultislotClassPresent);
   if(isMsMultislotClassPresent)
   {
      fprintf(stderr, "-------->>Enter MS MULTI SLOTCLASS  ,for which MS_RESUME_IND is  -  \n");
      scanf("%d",&msMultislotClass);
   }
  
   len = sizeof(PsappPsmshGrhmMsResumeReq);
   if((ptr = (PsappPsmshGrhmMsResumeReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   ptr->msId             =1; 
   ptr->isMsMultislotClassPresent = isMsMultislotClassPresent;
   if(ptr->isMsMultislotClassPresent)
   { 
      ptr->msMultislotClass = msMultislotClass;
   }
   ptr->reqReason        = reqReason;
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_PSMSH_GRHM_MS_RESUME_REQ, 1,PRCR_CP, ENT_PSAPP_PSMSH,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

}//Build_PsappPsmshGrhmMsResumeReq
   


I_PVoid Build_PsappPsmshGrhmMsRelInd(I_S32 *size)
{
   PsappPsmshGrhmMsRelInd *ptr;
   I_U16                     len=0;
   SyspcuMsId                msId;
     
   fprintf(stderr, "-------->>Enter MSID, for which  MS_REL_IND is -     \n ");
   scanf("%d",&msId);
   len = sizeof(PsappPsmshGrhmMsRelInd);
   if((ptr = (PsappPsmshGrhmMsRelInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   ptr->msId             = msId;
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_PSMSH_GRHM_MS_REL_IND, 1,PRCR_CP, ENT_PSAPP_PSMSH,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

}//Build_PsappPsmshGrhmMsRelInd



I_PVoid Build_PsappPsmshGrhmMsRelAck(I_S32 *size)
{
   PsappPsmshGrhmMsRelAck *ptr;
   I_U16                     len=0;
   SyspcuMsId                msId;
     
   fprintf(stderr, "-------->>Enter MSID, for which  MS_REL_ACK is -     \n ");
   scanf("%d",&msId);
   len = sizeof(PsappPsmshGrhmMsRelAck);
   if((ptr = (PsappPsmshGrhmMsRelAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   ptr->msId             = msId;
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_PSMSH_GRHM_MS_REL_ACK, 1,PRCR_CP, ENT_PSAPP_PSMSH,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

}//Build_PsappPsmshGrhmMsRelAck
  

 
I_PVoid Build_PsappPsmshGrhmMsAbnRelInd(I_S32 *size)
{
   PsappPsmshGrhmMsAbnRelInd *ptr;
   I_U16                     len=0;
   SyspcuMsId                msId;
   SyspcuOptFlag             isAbnTbfPresent;
   SyspcuAbnTbf              abnTbf;
   SyspcuMsRelCause          cause;
 
   fprintf(stderr, "-------->>Enter MSID, for which  MS_EST_IND is -     \n ");
   scanf("%d",&msId);
   fprintf(stderr, "-------->>Enter DO ABN TBF PRESENT   ,for which MS_ABN_REL_IND is  -  \n");
   scanf("%d",&isAbnTbfPresent);
   if(isAbnTbfPresent)
   {
      fprintf(stderr, "-------->>Enter ABN TBF ,for which MS_ABN_REL_IND is  -  \n");
      scanf("%d",&abnTbf);
   }
   fprintf(stderr, "-------->>Enter THE CAUSE   ,for which MS_ABN_REL_IND is  -  \n");
   scanf("%d",&cause);
   len = sizeof(PsappPsmshGrhmMsAbnRelInd);
   if((ptr = (PsappPsmshGrhmMsAbnRelInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   ptr->msId             = 1;
   ptr->isAbnTbfPresent  = 1;
   ptr->abnTbf           = 1;
   ptr->cause            = cause;
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_PSMSH_GRHM_MS_ABN_REL_IND, 1,PRCR_CP, ENT_PSAPP_PSMSH,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

}//Build_PsappPsmshGrhmMsAbnRelInd
  

I_PVoid Build_PsappPsmshGrhmMsTbfClassInd(I_S32 *size)
{
   PsappPsmshGrhmMsTbfClassInd *ptr;
   I_U16                     len=0;
   SyspcuMsId                msId;
   SyspcuMsTbfClassInfo      msTbfClassInfo;
  
   fprintf(stderr, "-------->>Enter MSID, for which  MS_TBF_CLASS_IND is -     \n ");
   scanf("%d",&msId);
   msTbfClassInfo.numElemDlList = 1;
   msTbfClassInfo.dlList[1]     = 1;
   msTbfClassInfo.isTbfClassIndUlPresent = 1;
   if(msTbfClassInfo.isTbfClassIndUlPresent) 
   {
      msTbfClassInfo.tbfClassIndUl = 1;
   }
   msTbfClassInfo.isTbfClassIndDlPresent = 1;
   if(msTbfClassInfo.isTbfClassIndDlPresent) 
   {
      msTbfClassInfo.tbfClassIndDl = 1;
   }
   msTbfClassInfo.isMsMultislotClassPresent = 1;
   if(msTbfClassInfo.isMsMultislotClassPresent)
   {
      msTbfClassInfo.msMultislotClass = 1;
   }
   
   len = sizeof(PsappPsmshGrhmMsTbfClassInd);
   if((ptr = (PsappPsmshGrhmMsTbfClassInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   ptr->msId   = msId;
   ptr->msTbfClassInfo.numElemDlList   = msTbfClassInfo.numElemDlList;
   ptr->msTbfClassInfo.dlList[1]       = msTbfClassInfo.dlList[1];
   ptr->msTbfClassInfo.isTbfClassIndUlPresent = msTbfClassInfo.isTbfClassIndUlPresent;
   if(ptr->msTbfClassInfo.isTbfClassIndUlPresent)
   {
      ptr->msTbfClassInfo.tbfClassIndUl = msTbfClassInfo.tbfClassIndUl; 
   }
   ptr->msTbfClassInfo.isTbfClassIndDlPresent = msTbfClassInfo.isTbfClassIndDlPresent;
   if(ptr->msTbfClassInfo.isTbfClassIndDlPresent)
   {
      ptr->msTbfClassInfo.tbfClassIndDl =  msTbfClassInfo.tbfClassIndDl;
   }
   ptr->msTbfClassInfo.isMsMultislotClassPresent = msTbfClassInfo.isMsMultislotClassPresent;
   if(ptr->msTbfClassInfo.isMsMultislotClassPresent)
   {
     ptr->msTbfClassInfo.msMultislotClass = msTbfClassInfo.msMultislotClass;
   }
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_PSMSH_GRHM_MS_TBF_CLASS_IND, 1,PRCR_CP, ENT_PSAPP_PSMSH,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

}//Build_PsappPsmshGrhmMsAbnRelInd


I_PVoid Build_PsappPsmshGrhmMsReorgAck(I_S32 *size)
{
   PsappPsmshGrhmMsReorgAck *ptr;
   I_U16                     len=0;
   SyspcuMsId                msId;
     
   fprintf(stderr, "-------->>Enter MSID, for which  MS_REORG_ACK is -     \n ");
   scanf("%d",&msId);
   len = sizeof(PsappPsmshGrhmMsReorgAck);
   if((ptr = (PsappPsmshGrhmMsReorgAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   ptr->msId             = msId;
   *size = len;
   FILL_SYS_HDR(&(ptr->sysHdr),PSAPP_PSMSH_GRHM_MS_REORG_ACK, 1,PRCR_CP, ENT_PSAPP_PSMSH,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

}//Build_PsappPsmshGrhmMsReorgAck
 

I_PVoid Build_ExecRralUdcInd(I_S32 *size)
{
   RralUdcInd *ptr;
   I_U16      len=0;
   len = sizeof(RralUdcInd);
   if((ptr = (RralUdcInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   *size = len;
   strcpy(ptr->udcString,"UDC123");
   FILL_SYS_HDR(&(ptr->sysHdr),EXEC_RRAL_UDC_IND, 1,PRCR_CP, ENT_PSAPP_PSMSH,0,PRCR_CP, ENT_CSAPP_GRHM,0);
   fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
   return ptr;

}//Build_ExecRralUdcInd
 
