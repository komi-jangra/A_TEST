/*se ts=2************************************File Header*****
File Name      :    toFromAbihm.c
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
#include<sysxxx_prcr.h>
#include<sysinst_hashdefs.h>
#include<sysxxx_msgstruct.h>
#include<ipcfrm_syslog.h>
#include<ipcfrm_msgqueue.h>
#include<ipcfrm_extern.h>
#include<ipcinst_dbstruct.h>
#include<ipcinst_extern.h>
#include<dbsxxx_commondefs.h>
#include<csappxxx_common_datastruct.h>
#include<oamxxx_hashdefs.h>
#include<oamsxxx_typedef.h>
#include<oamsxxx_hashdef.h>
#include<oamxxx_msgstruct.h>
#include<oams_msgstruct.h>
#include<oamsxxx_msgstruct.h>

I_PVoid Build_CsappAbihmSwmhLoadDataInitAck(I_S32 *, I_U32, I_U32, I_U32) ;
I_PVoid Build_CsappAbihmSwmhLoadDataInitNack(I_S32 *, I_U32, I_U32, I_U32) ;
I_PVoid Build_CsappAbihmSwmhLoadDataSegAck(I_S32 *, I_U32, I_U32, I_U32) ;
I_PVoid Build_CsappAbihmSwmhLoadDataEndAck(I_S32 *, I_U32, I_U32, I_U32) ;
I_PVoid Build_CsappAbihmSwmhLoadDataEndNack(I_S32 *, I_U32, I_U32, I_U32) ;
I_PVoid Build_CsappAbihmSwmhLoadDataAbort(I_S32 *, I_U32, I_U32, I_U32) ;
I_PVoid Build_CsappAbihmSwmhActSwNack(I_S32 *, I_U32, I_U32, I_U32) ;
I_PVoid Build_CsappAbihmSwmhSwActivatedReport(I_S32 *, I_U32, I_U32, I_U32) ; 


void ReceiveData() ;

I_U16 srcinstG ;
I_U16 CallRef ;

main()
{
   I_S32 count = 0 ;
   I_S32 size  = 0 ;
   I_S32 i     = 0 ;
   I_S32 srcId ;    
   I_S32 dstId ;
   I_S32 interval ;
   I_SL32 priority ;
   I_S8 buffer[100] ;
   I_PVoid bufferPtr ;
   int choice     = 0 ;
   I_U32 nodeId   = 0 ;
   I_U32 nodeType = 0 ;
   I_U32 applTei  = 0 ;

   srcId = (int)ENT_CSAPP_ABIHM ;

   if (RegisterWithIpcFrmwrk(srcId, (I_S8 *)"ENT_CSAPP_ABIHM")!=0)
   {
      fprintf(stderr,"Could not register with framework\n") ;
   }
   LOG_PRINT(INFO, "ABIHM Registered with IPC FRMWRK with entity ID = %d\n", ENT_CSAPP_ABIHM ) ;
   fprintf(stderr, "ABIHM Registered with IPC FRMWRK with entity ID = %d\n", ENT_CSAPP_ABIHM) ;
   while (1)
   {
      fprintf (stderr, "\n---------------- ENTER UR CHOICE -------------- \n") ;
      fprintf (stderr, "-------->> 1.To Send CSAPP_ABIHM_SWMH_LOAD_DATA_INIT_ACK \n") ;
      fprintf (stderr, "-------->> 2.To Send CSAPP_ABIHM_SWMH_LOAD_DATA_INIT_NACK \n") ;
      fprintf (stderr, "-------->> 3.To Send CSAPP_ABIHM_SWMH_LOAD_DATA_SEG_ACK \n") ;
      fprintf (stderr, "-------->> 4.To Send CSAPP_ABIHM_SWMH_LOAD_DATA_END_ACK \n") ;
      fprintf (stderr, "-------->> 5.To Send CSAPP_ABIHM_SWMH_LOAD_DATA_END_NACK \n") ;
      fprintf (stderr, "-------->> 6.To Send CSAPP_ABIHM_SWMH_LOAD_DATA_ABORT \n") ;
      fprintf (stderr, "-------->> 7.To Send CSAPP_ABIHM_SWMH_ACT_SW_NACK \n") ;
      fprintf (stderr, "-------->> 8.To Send CSAPP_ABIHM_SWMH_SW_ACTIVATED_REPORT \n") ;
      fprintf (stderr, "-------->> 9.To Receive Message \n") ;
      fprintf (stderr, "<<--------Enter choice \n") ;

      scanf("%d", &choice);    
     
      if( choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7 || choice == 8)
      {
         fprintf(stderr, "nodeType, nodeId, applTei\n");
         scanf ("%d %d %d", &nodeType, &nodeId, &applTei);
      }
     
      fprintf (stderr, " Given Choice = %d\t, NodeType =%d\t,NodeIdentity = %d\t applTei = %d\n" , choice,nodeType, nodeId, applTei);
      fprintf(stderr, "Entering into switch in ABIHM: \n") ;

      switch(choice)
      {
         case 1 :
                   bufferPtr = Build_CsappAbihmSwmhLoadDataInitAck(&size, nodeType, nodeId, applTei ) ;
                   fprintf(stderr, "Called function Build_CsappAbihmSwmhLoadDataInitAck\n") ;
                   break ;

         case 2 :
                   bufferPtr = Build_CsappAbihmSwmhLoadDataInitNack(&size, nodeType, nodeId, applTei) ;
                   fprintf(stderr, "Called function Build_CsappAbihmSwmhLoadDataInitNack\n");
                   break ;

         case 3 :
                   bufferPtr = Build_CsappAbihmSwmhLoadDataSegAck(&size, nodeType, nodeId, applTei) ;
                   fprintf(stderr, "Called functon Build_CsappAbihmSwmhLoadDataSegAck\n ");
                   break ;
         case 4 :
                   bufferPtr = Build_CsappAbihmSwmhLoadDataEndAck(&size, nodeType, nodeId, applTei) ;
                   fprintf(stderr, "Called function Build_CsappAbihmSwmhLoadDataEndAck\n");   
                   break ;
         case 5 :
                   bufferPtr = Build_CsappAbihmSwmhLoadDataEndNack(&size, nodeType, nodeId, applTei) ;
                   fprintf(stderr, "Called function Build_CsappAbihmSwmhLoadDataEndNack\n");
                   break ;
         case 6 :
                   bufferPtr = Build_CsappAbihmSwmhLoadDataAbort(&size, nodeType, nodeId, applTei) ;
                   fprintf(stderr, "Called function Build_CsappAbihmSwmhLoadDataAbort\n");
                   break ;
         case 7 :
                   bufferPtr = Build_CsappAbihmSwmhActSwNack(&size, nodeType, nodeId, applTei) ;
                   fprintf(stderr,"Called function Build_CsappAbihmSwmhActSwNack\n");
                   break ;
         case 8 :
                   bufferPtr = Build_CsappAbihmSwmhSwActivatedReport(&size, nodeType, nodeId, applTei) ;
                   fprintf(stderr,"Called function Build_CsappAbihmSwmhSwActivatedReport");
                   break ;

         case 9 :
                   fprintf(stderr, "Calling ReceiveData in ABIHM :\n") ;
                   ReceiveData() ;
                   fprintf(stderr, "Returning from ReceiveData in ABIHM :\n") ;
                   break ;
         default :
                   fprintf(stderr, "\n INVALID CHOICE \n") ;
      } /* end of switch */
 
      if( choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7 || choice == 8)
      {
         if (bufferPtr != NULL && size > 0)
         {
            if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
            {
               exit(0) ;
            }
         }
      }
   } /* end of while (1) */

} /* end of main */

void ReceiveData()
{
   I_PVoid         rcvPtr ;
   I_S32           msgSize ;
   I_U16           msgType ;

   LOG_PRINT(INFO, " Enterd into ReceiveData in ABIHM :\n") ;
   fprintf(stderr, "Entered into ReceiveData in ABIHM :\n") ;

   while(1)
   {
      rcvPtr = (I_PVoid)RecvMsg((int)(ENT_CSAPP_ABIHM), &msgSize) ;
      fprintf(stderr,"No of Bytes received = [%d]\n", msgSize) ;
      LOG_PRINT(INFO,"No of Bytes received = [%d]\n", msgSize );
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
   printf("\n Received message =%d\n ", msgType);
   switch (msgType)
   {
      case OAMS_SWMH_ABIHM_LOAD_DATA_INIT:
           fprintf(stderr,"OAMS_SWMH_ABIHM_LOAD_DATA_INIT received from SWMH\n") ;
           LOG_PRINT(INFO, "OAMS_SWMH_ABIHM_LOAD_DATA_INIT received from SWMH\n") ;
      break ;

      case OAMS_SWMH_ABIHM_LOAD_DATA_SEG:
           fprintf(stderr,"OAMS_SWMH_ABIHM_LOAD_DATA_SEG received from SWMH\n") ;
           LOG_PRINT(INFO, "OAMS_SWMH_ABIHM_LOAD_DATA_SEG received from SWMH\n") ;
      break ;

      case OAMS_SWMH_ABIHM_LOAD_DATA_END:
           fprintf(stderr,"OAMS_SWMH_ABIHM_LOAD_DATA_END received from SWMH\n") ;
           LOG_PRINT(INFO, "OAMS_SWMH_ABIHM_LOAD_DATA_END received from SWMH\n") ;
      break ;

      case OAMS_SWMH_ABIHM_ACT_SW:
           fprintf(stderr,"OAMS_SWMH_ABIHM_ACT_SW received from SWMH\n") ;
           LOG_PRINT(INFO, "OAMS_SWMH_ABIHM_ACT_SW received from SWMH\n") ;
      break ;

      case OAMS_SWMH_ABIHM_LOAD_DATA_ABORT:
           fprintf(stderr,"OAMS_SWMH_ABIHM_LOAD_DATA_ABORT from SWMH\n") ;
           LOG_PRINT(INFO, "OAMS_SWMH_ABIHM_LOAD_DATA_ABORT from SWMH\n") ;
      break ;

      default:
           fprintf(stderr,"Invalid message received from SWMH\n") ;
           LOG_PRINT(INFO, "Invalid message received from SWMH\n") ;
   }
   if (rcvPtr != NULL)
   DalocMsgBuf(rcvPtr) ;
}

I_PVoid Build_CsappAbihmSwmhLoadDataInitAck(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   CsappAbihmSwmhLoadDataInitAck    *loadDataInitAck ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(CsappAbihmSwmhLoadDataInitAck);
   if((loadDataInitAck = (CsappAbihmSwmhLoadDataInitAck *)AlocMsgBuf(len) ) == (I_PVoid)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   loadDataInitAck->tei = applTei ;
   loadDataInitAck->placementInd = PLACEMENT_IND ;
   loadDataInitAck->seqNum = SEQ_NO ;
   if(nodeType == 3)
   loadDataInitAck->objClass = OBJ_CLASS_BIC ; /* for Bic use [[OBJ_CLASS_BIC]] */
   else
   {
      if(nodeType == 6)
      {
         loadDataInitAck->objClass = OBJ_CLASS_BM;
      }
      else
      {
          loadDataInitAck->objClass = OBJ_CLASS_TRX ;
      } 
   }
   loadDataInitAck->objInstance.btsNum = OBJ_INSTANCE_BTS_NUM ; 
   loadDataInitAck->objInstance.baseBandNum = BASE_BAND_NUM ;
   loadDataInitAck->objInstance.timeSlotNum = TIME_SLOT_NUM ;
   loadDataInitAck->windowSize = 3 ;
   strcpy(loadDataInitAck->swDes.fileVer, "20.10.3") ;
   loadDataInitAck->swDes.len = 7 ;
   loadDataInitAck->bicId = nodeId ; /* if objClass is Bic */
  

//LOG_PRINT(DEBUG,"NodeType =%d\t,NodeIdentity = %d\t applTei = %d\n" ,nodeType, nodeId, applTei\n");

   *size = len ;

   FILL_SYS_HDR(&(loadDataInitAck->sysHdr), CSAPP_ABIHM_SWMH_LOAD_DATA_INIT_ACK , 1, PRCR_CP, ENT_CSAPP_ABIHM, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   LOG_PRINT(INFO,"Sending CSAPP_ABIHM_SWMH_LOAD_DATA_INIT_ACK\n") ;
   return  loadDataInitAck ;

} /* Build_CsappAbihmSwmhLoadDataInitAck() */

I_PVoid Build_CsappAbihmSwmhLoadDataInitNack(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   CsappAbihmSwmhLoadDataInitNack    *loadDataInitNack ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(CsappAbihmSwmhLoadDataInitNack);
   if((loadDataInitNack = (CsappAbihmSwmhLoadDataInitNack *)AlocMsgBuf(len) ) == (I_PVoid)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   loadDataInitNack->tei = applTei ;
   loadDataInitNack->placementInd = PLACEMENT_IND ;
   loadDataInitNack->seqNum = SEQ_NO ;
   if(nodeType == 3)
   loadDataInitNack->objClass = OBJ_CLASS_BIC ; /* for Bic use [[OBJ_CLASS_BIC]] */
   else
   {
      if(nodeType == 6)
      {
         loadDataInitNack->objClass = OBJ_CLASS_BM;
      } 
      else
      {

	      loadDataInitNack->objClass = OBJ_CLASS_TRX ;
       
      } 
   }
	      loadDataInitNack->objInstance.btsNum = OBJ_INSTANCE_BTS_NUM ; 
	      loadDataInitNack->objInstance.baseBandNum = BASE_BAND_NUM ;
	      loadDataInitNack->objInstance.timeSlotNum = TIME_SLOT_NUM ;
	      loadDataInitNack->windowSize = 3 ;
	      strcpy(loadDataInitNack->swDes.fileVer, "20.10.3") ;
	      loadDataInitNack->swDes.len = 7 ;
	      loadDataInitNack->bicId = nodeId; /* if objClass is Bic */
	      loadDataInitNack->nackCause = 0x01 ; /* To be filled accordingly from the 9 causes mentioned */
       
  
   *size = len ;

   FILL_SYS_HDR(&(loadDataInitNack->sysHdr), CSAPP_ABIHM_SWMH_LOAD_DATA_INIT_NACK , 1, PRCR_CP, ENT_CSAPP_ABIHM, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;
   LOG_PRINT(INFO,"Sending CSAPP_ABIHM_SWMH_LOAD_DATA_INIT_NACK\n") ;

   return  loadDataInitNack ;

} /* Build_CsappAbihmSwmhLoadDataInitNack() */

I_PVoid Build_CsappAbihmSwmhLoadDataSegAck(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   CsappAbihmSwmhLoadDataSegAck    *loadDataSegAck ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(CsappAbihmSwmhLoadDataSegAck);
   if((loadDataSegAck = (CsappAbihmSwmhLoadDataSegAck *)AlocMsgBuf(len) ) == (I_PVoid)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   loadDataSegAck->tei = applTei ;
   loadDataSegAck->placementInd = PLACEMENT_IND ;
   loadDataSegAck->seqNum = SEQ_NO ;
   if(nodeType == 3)
   loadDataSegAck->objClass = OBJ_CLASS_BIC ; /* for Bic use [[OBJ_CLASS_BIC]] */
   else
   {
      if(nodeType == 6)
      {
	      loadDataSegAck->objClass = OBJ_CLASS_BM;
      } 
      else
      {
	      loadDataSegAck->objClass = OBJ_CLASS_TRX ;
      }
}
	      loadDataSegAck->objInstance.btsNum = OBJ_INSTANCE_BTS_NUM ; 
	      loadDataSegAck->objInstance.baseBandNum = BASE_BAND_NUM ;
	      loadDataSegAck->objInstance.timeSlotNum = TIME_SLOT_NUM ;
	      loadDataSegAck->bicId = nodeId ; /* if objClass is Bic */
       

   *size = len ;

   FILL_SYS_HDR(&(loadDataSegAck->sysHdr), CSAPP_ABIHM_SWMH_LOAD_DATA_SEG_ACK , 1, PRCR_CP, ENT_CSAPP_ABIHM, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;
   LOG_PRINT(INFO,"Sending CSAPP_ABIHM_SWMH_LOAD_DATA_SEG_ACK\n") ;

   return  loadDataSegAck ;

} /* Build_CsappAbihmSwmhLoadDataSegAck() */


I_PVoid Build_CsappAbihmSwmhLoadDataEndAck(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   CsappAbihmSwmhLoadDataEndAck    *loadDataEndAck ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(CsappAbihmSwmhLoadDataEndAck);
   if((loadDataEndAck = (CsappAbihmSwmhLoadDataEndAck *)AlocMsgBuf(len) ) == (I_PVoid)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   loadDataEndAck->tei = applTei ;
   loadDataEndAck->placementInd = PLACEMENT_IND ;
   loadDataEndAck->seqNum = SEQ_NO ;
   if(nodeType == 3)
   loadDataEndAck->objClass = OBJ_CLASS_BIC ; /* for Bic use [[OBJ_CLASS_BIC]] */
   else
   {
      if(nodeType == 6)
      {
	      loadDataEndAck->objClass = OBJ_CLASS_BM;
      } 
      else
      {
	      loadDataEndAck->objClass = OBJ_CLASS_TRX ;
      }
   }
	      loadDataEndAck->objInstance.btsNum = OBJ_INSTANCE_BTS_NUM ; 
	      loadDataEndAck->objInstance.baseBandNum = BASE_BAND_NUM ;
	      loadDataEndAck->objInstance.timeSlotNum = TIME_SLOT_NUM ;
	      strcpy(loadDataEndAck->swDes.fileVer, "20.10.3") ;
	      loadDataEndAck->swDes.len = 7;
	      loadDataEndAck->bicId = nodeId; /* if objClass is Bic */
      

      *size = len ;

      FILL_SYS_HDR(&(loadDataEndAck->sysHdr), CSAPP_ABIHM_SWMH_LOAD_DATA_END_ACK , 1, PRCR_CP, ENT_CSAPP_ABIHM, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;
   LOG_PRINT(INFO,"Sending CSAPP_ABIHM_SWMH_LOAD_DATA_END_ACK\n") ;

   return  loadDataEndAck ;

} /* Build_CsappAbihmSwmhLoadDataEndAck() */



I_PVoid Build_CsappAbihmSwmhLoadDataEndNack(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   CsappAbihmSwmhLoadDataEndNack    *loadDataEndNack ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(CsappAbihmSwmhLoadDataEndNack);
   if((loadDataEndNack = (CsappAbihmSwmhLoadDataEndNack *)AlocMsgBuf(len) ) == (I_PVoid)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   loadDataEndNack->tei = applTei ;
   loadDataEndNack->placementInd = PLACEMENT_IND ;
   loadDataEndNack->seqNum = SEQ_NO ;
   if (nodeType == 3)
   loadDataEndNack->objClass = OBJ_CLASS_BIC ; /* for Bic use [[OBJ_CLASS_BIC]] */
   else
  {
      if(nodeType == 6)
      {
         loadDataEndNack->objClass = OBJ_CLASS_BM;
      } 
      else
      {

	      loadDataEndNack->objClass = OBJ_CLASS_TRX ;
       
      } 
   }
   loadDataEndNack->objInstance.btsNum = OBJ_INSTANCE_BTS_NUM ; 
   loadDataEndNack->objInstance.baseBandNum = BASE_BAND_NUM ;
   loadDataEndNack->objInstance.timeSlotNum = TIME_SLOT_NUM ;
   strcpy(loadDataEndNack->swDes.fileVer, "20.10.3") ;
   loadDataEndNack->swDes.len = 7;
   loadDataEndNack->bicId = nodeId ; /* if objClass is Bic */
   loadDataEndNack->nackCause = 0x01 ; /* To be filled accordingly from the 9 causes mentioned */

   *size = len ;

   FILL_SYS_HDR(&(loadDataEndNack->sysHdr), CSAPP_ABIHM_SWMH_LOAD_DATA_END_NACK , 1, PRCR_CP, ENT_CSAPP_ABIHM, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;
LOG_PRINT(INFO,"Sending CSAPP_ABIHM_SWMH_LOAD_DATA_END_NACK\n") ;

   return  loadDataEndNack ;

} /* Build_CsappAbihmSwmhLoadDataEndNack() */

I_PVoid Build_CsappAbihmSwmhActSwNack(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   CsappAbihmSwmhActSwNack    *actSwNack ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(CsappAbihmSwmhActSwNack);
   if((actSwNack = (CsappAbihmSwmhActSwNack *)AlocMsgBuf(len) ) == (I_PVoid)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   actSwNack->tei = applTei ;
   actSwNack->placementInd = PLACEMENT_IND ;
   actSwNack->seqNum = SEQ_NO ;
   if (nodeType == 3)
   actSwNack->objClass = OBJ_CLASS_BIC ; /* for Bic use [[OBJ_CLASS_BIC]] */
   else
  {
      if(nodeType == 6)
      {
         actSwNack->objClass = OBJ_CLASS_BM;
      } 
      else
      {

	      actSwNack->objClass = OBJ_CLASS_TRX ;
       
      } 
   }
   actSwNack->objInstance.btsNum = OBJ_INSTANCE_BTS_NUM ; 
   actSwNack->objInstance.baseBandNum = BASE_BAND_NUM ;
   actSwNack->objInstance.timeSlotNum = TIME_SLOT_NUM ;
   strcpy(actSwNack->swDes.fileVer, "20.10.3") ;
   actSwNack->swDes.len = 7;
   actSwNack->bicId = nodeId ; /* if objClass is Bic */
   actSwNack->nackCause = 0x01 ; /* To be filled accordingly from the 9 causes mentioned */

   *size = len ;

   FILL_SYS_HDR(&(actSwNack->sysHdr), CSAPP_ABIHM_SWMH_ACT_SW_NACK , 1, PRCR_CP, ENT_CSAPP_ABIHM, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;
   LOG_PRINT(INFO,"Sending CSAPP_ABIHM_SWMH_ACT_SW_NACK\n") ;

   return  actSwNack ;

} /* Build_CsappAbihmSwmhActSwNack() */

I_PVoid Build_CsappAbihmSwmhSwActivatedReport(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   CsappAbihmSwmhSwActivatedReport    *swActivateRep ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(CsappAbihmSwmhActSwNack);
   if((swActivateRep = (CsappAbihmSwmhSwActivatedReport *)AlocMsgBuf(len) ) == (I_PVoid)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   swActivateRep->tei = applTei ;
   swActivateRep->placementInd = PLACEMENT_IND ;
   swActivateRep->seqNum = SEQ_NO ;
   if (nodeType == 3)
   swActivateRep->objClass = OBJ_CLASS_BIC ; /* for Bic use [[OBJ_CLASS_BIC]] */
   else
  {
      if(nodeType == 6)
      {
         swActivateRep->objClass = OBJ_CLASS_BM;
      } 
      else
      {

	     swActivateRep->objClass = OBJ_CLASS_TRX ;
       
      } 
   }
   swActivateRep->objInstance.btsNum = OBJ_INSTANCE_BTS_NUM ; 
   swActivateRep->objInstance.baseBandNum = BASE_BAND_NUM ;
   swActivateRep->objInstance.timeSlotNum = TIME_SLOT_NUM ;
   strcpy(swActivateRep->swDes.fileVer, "20.10.3") ;
   swActivateRep->swDes.len = 7;
   swActivateRep->bicId = nodeId ; /* if objClass is Bic */
   
   *size = len ;

   FILL_SYS_HDR(&(swActivateRep->sysHdr), CSAPP_ABIHM_SWMH_SW_ACTIVATED_REPORT , 1, PRCR_CP, ENT_CSAPP_ABIHM, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;
   LOG_PRINT(INFO,"Sending CSAPP_ABIHM_SWMH_SW_ACTIVATED_REPORT\n") ;
 
   return  swActivateRep ;

} /* Build_CsappAbihmSwmhSwActivatedReport */



I_PVoid Build_CsappAbihmSwmhLoadDataAbort(I_S32 *size, I_U32 nodeType, I_U32 nodeId, I_U32 applTei) 
{
   CsappAbihmSwmhLoadDataAbort    *loadDataAbort ;

   I_U16 len = 0 ;
   I_U16 pathLen = 0 ;
   len = sizeof(CsappAbihmSwmhLoadDataAbort);
   if((loadDataAbort = (CsappAbihmSwmhLoadDataAbort *)AlocMsgBuf(len) ) == (I_PVoid)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }
   loadDataAbort->tei = applTei ;
   loadDataAbort->placementInd = PLACEMENT_IND ;
   loadDataAbort->seqNum = SEQ_NO ;
   if (nodeType == 3)
   loadDataAbort->objClass = OBJ_CLASS_BIC ; /* for Bic use [[OBJ_CLASS_BIC]] */
   else
  {
      if(nodeType == 6)
      {
         loadDataAbort->objClass = OBJ_CLASS_BM;
      } 
      else
      {

	      loadDataAbort->objClass = OBJ_CLASS_TRX ;
       
      } 
   }
   loadDataAbort->objInstance.btsNum = OBJ_INSTANCE_BTS_NUM ; 
   loadDataAbort->objInstance.baseBandNum = BASE_BAND_NUM ;
   loadDataAbort->objInstance.timeSlotNum = TIME_SLOT_NUM ;
   loadDataAbort->bicId = nodeId ; /* if objClass is Bic */
   *size = len ;

   FILL_SYS_HDR(&(loadDataAbort->sysHdr), CSAPP_ABIHM_SWMH_LOAD_DATA_ABORT , 1, PRCR_CP, ENT_CSAPP_ABIHM, 0, PRCR_CP, ENT_OAMS_SWMH, 0) ;

   return  loadDataAbort ;

} /* Build_CsappAbihmSwmhLoadDataAbort() */

