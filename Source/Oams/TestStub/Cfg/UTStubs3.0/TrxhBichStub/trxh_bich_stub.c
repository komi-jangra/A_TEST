#include <oamscfg_includes.h>
#include "cfg_stub_sa.h"

SysHdr*    sysHdrPtr;
I_S32 srcId;           /* SrcId for the CFG */
void *cfgMsgBuf;       /* Message Pointer for the received message */
I_U32 recvMsgSize;  /* received message size */

void cfgFrmwrkInit(I_S32 srcId)
{
   I_S8 retVal;
   printf("\nCFG: Calling function cfgFrmwrkInit()");
   retVal = RegisterWithIpcFrmwrk(srcId, (I_S8*)"CFG_SA_STUB");
   printf("\nReturn Value of IPC Registration: %d\n",retVal);
   if (retVal < ZERO)
   {
      printf("Registration failed " );
      exit(0);
   }
   printf("\nCFG: Calling function cfgFrmwrkInit() Exiting");
} /* End of function cfgFrmwrkInit() */

int main()
{
   I_U32 choice;
   printf("CFG Stub \n");
   printf("1:: BIC Handler \n");
   printf("2:: TRX Handler \n");
   printf("3:: GRHM \n");
   printf("Enter your choice:: ");
   scanf("%d" , &choice);
   switch(choice)
   {
      case 1:
	 printf("\n BICH Configured \n");
	 bichReqHandler();
	 break;
      case 2:
	 printf("\n TRXH Configure\n");
	 trxhReqHandler();
	 break;
      case 3:
	 printf("\n TRXH Configure\n");
	 grhmReqHandler();
	 break;
      default:
	 printf("Sorry!!! Wrong choice \n EXITING");
	 exit(0);
   }
}

void grhmReqHandler()
{
   cfgFrmwrkInit(ENT_CSAPP_GRHM);
   while(1)
   {
      cfgMsgBuf = (void *)RecvMsg(ENT_CSAPP_GRHM, &recvMsgSize);
      if(cfgMsgBuf == NULL)
      {
	 continue;
      }
      sysHdrPtr = (SysHdr *) cfgMsgBuf;
      switch(sysHdrPtr->msgType)
      {
	 case OAMS_CFG_GRHM_SWITCH_CONNECT:
	    printf("Received Msg : OAMS_CFG_GRHM_SWITCH_CONNECT");
	    switchConnectHandler();
	    break;
      }
      DalocMsgBuf (cfgMsgBuf);
   }
}

void trxhReqHandler()
{
   cfgFrmwrkInit(ENT_OAMS_TRXH);
   while(1)
   {
      cfgMsgBuf = (void *)RecvMsg(ENT_OAMS_TRXH, &recvMsgSize);
      if (cfgMsgBuf == NULL)
      {
         continue;
      }
      sysHdrPtr =  (SysHdr *) cfgMsgBuf;
      switch( sysHdrPtr->msgType)
      {
	 case OAMS_CFG_TRXH_ADD_TRX_REQ:
            printf("Received Msg : OAMS_CFG_TRXH_ADD_TRX_REQ");
	    addTrxReqHandler();
	    break;
	 case OAMS_CFG_TRXH_DEL_TRX_REQ:
	    printf("Recieved Msg : OAMS_CFG_TRXH_DEL_TRX_REQ");
	    deleteTrxReqHandler();
	    break;
	 case OAMS_CFG_TRXH_UNLOCK_REQ:
	    printf("Received Msg : OAMS_CFG_TRXH_UNLOK_REQ");
	    unlockTrxReqHandler();
	    break;
	 case OAMS_CFG_TRXH_LOCK_REQ:
	    printf("Received Msg : OAMS_CFG_TRXH_LOCK_REQ");
	    lockTrxReqHandler();
	    break;
      }
      DalocMsgBuf(cfgMsgBuf);
   }
   
}

#if 1
void unlockTrxReqHandler() /* For Successfull Result */
{
   OamsCfgTrxhUnlockReq *oamsCfgTrxhUnlockReqPtr = NULL;
   OamsTrxhCfgUnlockResp oamsTrxhCfgUnlockResp;
   oamsCfgTrxhUnlockReqPtr = (OamsCfgTrxhUnlockReq *) cfgMsgBuf;
   printf("E1 Num (from Cfg):: %d \n" , oamsCfgTrxhUnlockReqPtr->e1Num);
   oamsTrxhCfgUnlockResp.objType = oamsCfgTrxhUnlockReqPtr->objType;
   oamsTrxhCfgUnlockResp.objId = oamsCfgTrxhUnlockReqPtr->objId;
   oamsTrxhCfgUnlockResp.e1Num = oamsCfgTrxhUnlockReqPtr->e1Num;
   cfgBichStubSendMessage(&oamsTrxhCfgUnlockResp, sizeof(OamsTrxhCfgUnlockResp), ENT_OAMS_TRXH, ENT_OAMS_CFG, OAMS_TRXH_CFG_UNLOCK_RESP,0);
}
#endif

#if 1
void lockTrxReqHandler() /* For Successfull Result */
{
   OamsCfgTrxhLockReq *oamsCfgTrxhLockReqPtr = NULL;
   OamsTrxhCfgLockResp oamsTrxhCfgLockResp;
   oamsCfgTrxhLockReqPtr = (OamsCfgTrxhLockReq *) cfgMsgBuf;
   printf("E1 Num (from Cfg):: %d \n" , oamsCfgTrxhLockReqPtr->e1Num);
   oamsTrxhCfgLockResp.objType = oamsCfgTrxhLockReqPtr->objType;
   oamsTrxhCfgLockResp.objId = oamsCfgTrxhLockReqPtr->objId;
   oamsTrxhCfgLockResp.e1Num = oamsCfgTrxhLockReqPtr->e1Num;
   cfgBichStubSendMessage(&oamsTrxhCfgLockResp, sizeof(OamsTrxhCfgLockResp), ENT_OAMS_TRXH, ENT_OAMS_CFG, OAMS_TRXH_CFG_LOCK_RESP,0);
}
#endif

void bichReqHandler()
{
   cfgFrmwrkInit(ENT_OAMS_BICH);
   while(1)
   {
      cfgMsgBuf = (void *)RecvMsg(ENT_OAMS_BICH, &recvMsgSize);
      if (cfgMsgBuf == NULL)
      {
         continue;
      }
      sysHdrPtr =  (SysHdr *) cfgMsgBuf;
      switch( sysHdrPtr->msgType)
      {
	 case OAMS_CFG_BICH_ADD_BIC_REQ:
	    printf("Received Msg : OAMS_CFG_BICH_ADD_BIC_REQ");
	    addBicReqHandler();
	    break;
	 case OAMS_CFG_BICH_DEL_BIC_REQ:
	    printf("Received Msg : OAMS_CFG_BICH_DEL_BIC_REQ");
	    deleteBicReqHandler();
	    break;
      }
      DalocMsgBuf(cfgMsgBuf);
   }
	
}
void switchConnectHandler()
{
   OamsCfgGrhmSwitchConnect *oamsCfgGrhmSwitchConnectPtr = NULL;
   CsappGrhmCfgSwitchConnectAck csappGrhmCfgSwitchConnectAck;
   CsappGrhmCfgSwitchConnectNack csappGrhmCfgSwitchConnectNack;
   oamsCfgGrhmSwitchConnectPtr = (OamsCfgGrhmSwitchConnect *) cfgMsgBuf;
   printf("First E1 Num [%d]\n First TimeSLot [%d] \n Second E1 Num [%d] \n Second TimeSlot [%d]" , oamsCfgGrhmSwitchConnectPtr->firstE1Num , oamsCfgGrhmSwitchConnectPtr->firstTimeSlotNum ,  oamsCfgGrhmSwitchConnectPtr->secondE1Num, oamsCfgGrhmSwitchConnectPtr->secondTimeSlotNum);

#if 1     /* For ACK */
   csappGrhmCfgSwitchConnectAck.firstE1Num = oamsCfgGrhmSwitchConnectPtr->firstE1Num;
   csappGrhmCfgSwitchConnectAck.firstTimeSlotNum = oamsCfgGrhmSwitchConnectPtr->firstTimeSlotNum;
   cfgBichStubSendMessage(&csappGrhmCfgSwitchConnectAck , sizeof(CsappGrhmCfgSwitchConnectAck),ENT_CSAPP_GRHM , ENT_OAMS_CFG,CSAPP_GRHM_CFG_SWITCH_CONNECT_ACK ,0);
#endif

#if 0	/* For NACK */
   csappGrhmCfgSwitchConnectNack.firstE1Num = oamsCfgGrhmSwitchConnectPtr->firstE1Num;
   csappGrhmCfgSwitchConnectNack.firstTimeSlotNum = oamsCfgGrhmSwitchConnectPtr->firstTimeSlotNum;
   csappGrhmCfgSwitchConnectNack.cause = 4;
   cfgBichStubSendMessage(&csappGrhmCfgSwitchConnectNack , sizeof(CsappGrhmCfgSwitchConnectNack), ENT_CSAPP_GRHM, ENT_OAMS_CFG, CSAPP_GRHM_CFG_SWITCH_CONNECT_NACK,0);
#endif

}

#if 1
void addBicReqHandler()	/* For Successfull Result */
{
   OamsCfgBichAddBicReq *oamsCfgBichAddBicReqPtr = NULL;
   OamsBichCfgAddBicResp oamsBichCfgAddBicResp;
   oamsCfgBichAddBicReqPtr = (OamsCfgBichAddBicReq *) cfgMsgBuf;
   printf("BIC Id (from Cfg):: %d \n" , oamsCfgBichAddBicReqPtr->bicId);
   oamsBichCfgAddBicResp.bicId = oamsCfgBichAddBicReqPtr->bicId;
   oamsBichCfgAddBicResp.result = OAMS_RSLT_SUCCESS;
   oamsBichCfgAddBicResp.e1Id = oamsCfgBichAddBicReqPtr->e1Id;
   oamsBichCfgAddBicResp.e1Ts = oamsCfgBichAddBicReqPtr->e1Ts;
   cfgBichStubSendMessage(&oamsBichCfgAddBicResp, sizeof(OamsBichCfgAddBicResp), ENT_OAMS_BICH, ENT_OAMS_CFG, OAMS_BICH_CFG_ADD_BIC_RESP,0);
}
#endif

#if 1
void deleteBicReqHandler() /* For Successfull Result */
{
   OamsCfgBichDelBicReq *oamsCfgBichDelBicReqPtr = NULL;
   OamsBichCfgDelBicResp oamsBichCfgDelBicResp;
   oamsCfgBichDelBicReqPtr = (OamsCfgBichDelBicReq *) cfgMsgBuf ;
   printf("BIC Id (from Cfg):: %d \n" , oamsCfgBichDelBicReqPtr->bicId);
   oamsBichCfgDelBicResp.bicId = oamsCfgBichDelBicReqPtr->bicId;
   oamsBichCfgDelBicResp.result = OAMS_RSLT_SUCCESS;
   cfgBichStubSendMessage(&oamsBichCfgDelBicResp, sizeof(OamsBichCfgDelBicResp), ENT_OAMS_BICH, ENT_OAMS_CFG, OAMS_BICH_CFG_DEL_BIC_RESP,0);
}
#endif

#if 1
void addTrxReqHandler()	/* For Successfull Result */
{
   OamsCfgTrxhAddTrxReq *oamsCfgTrxhAddTrxReqPtr = NULL;
   OamsTrxhCfgAddTrxResp oamsTrxhCfgAddTrxResp;
   oamsCfgTrxhAddTrxReqPtr = (OamsCfgTrxhAddTrxReq *) cfgMsgBuf;
   printf("Ptrx Id (from Cfg):: %d \n" , oamsCfgTrxhAddTrxReqPtr->ptrxId);
   oamsTrxhCfgAddTrxResp.ptrxId = oamsCfgTrxhAddTrxReqPtr->ptrxId;
   oamsTrxhCfgAddTrxResp.result = OAMS_RSLT_SUCCESS;
   cfgBichStubSendMessage(&oamsTrxhCfgAddTrxResp, sizeof(OamsTrxhCfgAddTrxResp), ENT_OAMS_TRXH, ENT_OAMS_CFG, OAMS_TRXH_CFG_ADD_TRX_RESP,0);
}
#endif

#if 1
void deleteTrxReqHandler()	/* For Successfull Result */
{
   OamsCfgTrxhDelTrxReq *oamsCfgTrxhDelTrxReqPtr = NULL;
   OamsTrxhCfgDelTrxResp oamsTrxhCfgDelTrxResp;
   oamsCfgTrxhDelTrxReqPtr = (OamsCfgTrxhDelTrxReq *) cfgMsgBuf ;
   printf("Ptrx Id (from Cfg):: %d \n" , oamsCfgTrxhDelTrxReqPtr->ptrxId);
   oamsTrxhCfgDelTrxResp.ptrxId = oamsCfgTrxhDelTrxReqPtr->ptrxId;
   oamsTrxhCfgDelTrxResp.result = OAMS_RSLT_SUCCESS;
   cfgBichStubSendMessage(&oamsTrxhCfgDelTrxResp, sizeof(OamsTrxhCfgDelTrxResp), ENT_OAMS_TRXH, ENT_OAMS_CFG, OAMS_TRXH_CFG_DEL_TRX_RESP,0);
}
#endif

#if 0
void addBicReqHandler()	/* For Failure Result */
{
   OamsCfgBichAddBicReq *oamsCfgBichAddBicReqPtr = NULL;
   OamsBichCfgAddBicResp oamsBichCfgAddBicResp;
   oamsCfgBichAddBicReqPtr = (OamsCfgBichAddBicReq *) cfgMsgBuf;
   printf("BIC Id (from Cfg):: %d \n" , oamsCfgBichAddBicReqPtr->bicId);
   oamsBichCfgAddBicResp.bicId = oamsCfgBichAddBicReqPtr->bicId;
   oamsBichCfgAddBicResp.result = OAMS_RSLT_FAILURE;
   oamsBichCfgAddBicResp.cause = 4;
   cfgBichStubSendMessage(&oamsBichCfgAddBicResp, sizeof(OamsBichCfgAddBicResp), ENT_OAMS_BICH, ENT_OAMS_CFG, OAMS_BICH_CFG_ADD_BIC_RESP,0);
}
#endif

#if 0
void deleteBicReqHandler()	/* For Failure Result */
{
   OamsCfgBichDelBicReq *oamsCfgBichDelBicReqPtr = NULL;
   OamsBichCfgDelBicResp oamsBichCfgDelBicResp;
   oamsCfgBichDelBicReqPtr = (OamsCfgBichDelBicReq *) cfgMsgBuf ;
   printf("BIC Id (from Cfg):: %d \n" , oamsCfgBichDelBicReqPtr->bicId);
   oamsBichCfgDelBicResp.bicId = oamsCfgBichDelBicReqPtr->bicId;
   oamsBichCfgDelBicResp.result = OAMS_RSLT_FAILURE;
   oamsBichCfgDelBicResp.cause = 4;
   cfgBichStubSendMessage(&oamsBichCfgDelBicResp, sizeof(OamsBichCfgDelBicResp), ENT_OAMS_BICH, ENT_OAMS_CFG, OAMS_BICH_CFG_DEL_BIC_RESP,0);
}
#endif

#if 0
void addTrxReqHandler()	/* For Failure Result */
{
   OamsCfgTrxhAddTrxReq *oamsCfgTrxhAddTrxReqPtr = NULL;
   OamsTrxhCfgAddTrxResp oamsTrxhCfgAddTrxResp;
   oamsCfgTrxhAddTrxReqPtr = (OamsCfgTrxhAddTrxReq *) cfgMsgBuf;
   printf("Ptrx Id (from Cfg):: %d \n" , oamsCfgTrxhAddTrxReqPtr->ptrxId);
   oamsTrxhCfgAddTrxResp.ptrxId = oamsCfgTrxhAddTrxReqPtr->ptrxId;
   oamsTrxhCfgAddTrxResp.result = OAMS_RSLT_FAILURE;
   oamsTrxhCfgAddTrxResp.cause = 4;
   cfgBichStubSendMessage(&oamsTrxhCfgAddTrxResp, sizeof(OamsTrxhCfgAddTrxResp), ENT_OAMS_TRXH, ENT_OAMS_CFG, OAMS_TRXH_CFG_ADD_TRX_RESP,0);
}
#endif

#if 0
void deleteTrxReqHandler()	/* For Failure Result */
{
   OamsCfgTrxhDelTrxReq *oamsCfgTrxhDelTrxReqPtr = NULL;
   OamsTrxhCfgDelTrxResp oamsTrxhCfgDelTrxResp;
   oamsCfgTrxhDelTrxReqPtr = (OamsCfgTrxhDelTrxReq *) cfgMsgBuf ;
   printf("Ptrx Id (from Cfg):: %d \n" , oamsCfgTrxhDelTrxReqPtr->ptrxId);
   oamsTrxhCfgDelTrxResp.ptrxId = oamsCfgTrxhDelTrxReqPtr->ptrxId;
   oamsTrxhCfgDelTrxResp.result = OAMS_RSLT_FAILURE;
   oamsTrxhCfgDelTrxResp.cause = 4;
   cfgBichStubSendMessage(&oamsTrxhCfgDelTrxResp, sizeof(OamsTrxhCfgDelTrxResp), ENT_OAMS_TRXH, ENT_OAMS_CFG, OAMS_TRXH_CFG_DEL_TRX_RESP,0);
}
#endif

I_S32 cfgBichStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;
   sndMsgSize = 0;
   printf("\n\t Calling cfgBichStubSendMessage().....");

   if (bufPtr != NULL)
      sndMsgSize = size;
   else
      sndMsgSize = sizeof(SysHdr);

   if ((sndPtr = (SysHdr *)AlocMsgBuf(sndMsgSize)) == NULL)
   {
      printf("CFG_SEND_ALLOC_FAIL");
      return -1; 
   }

   memset(sndPtr,0,sndMsgSize) ;
   if (bufPtr != NULL)
      memcpy(((I_U8 *)sndPtr), (I_U8*)bufPtr, size);

   sndPtr->msgType = msgType;
   sndPtr->src.entity = SrcEntId;
   sndPtr->dest.entity = DestEntId;
    
   //sndPtr->dest.entity = DESTINATION;


   printf("\n sndPtr->msgType = %d", sndPtr->msgType);
   printf("\n sndPtr->sHdr.src.entity = %d", sndPtr->src.entity);
   printf("\n sndPtr->sHdr.dest.entity = %d", sndPtr->dest.entity);
   printf("\n Sending message ...........");

   fflush(stdin);
   if (SendMsg(sndPtr, 1, sndMsgSize) < 0)
   {
      printf("\nCFG: In func cfgSendMessage() - msg sending failed");
      DalocMsgBuf((I_PVoid) sndPtr);
      return(-1);
   }
   return(1);
}
