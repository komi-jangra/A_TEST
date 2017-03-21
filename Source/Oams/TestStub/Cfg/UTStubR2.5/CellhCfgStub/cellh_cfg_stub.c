#include <oamscfg_includes.h>
#include "cfg_stub_cellh.h"

SysHdr*    sysHdrPtr;
I_S32 srcId;           /* SrcId for the CFG */
void *cfgMsgBuf;       /* Message Pointer for the received message */
I_U32 recvMsgSize;  /* received message size */

void sendCellEnabletoCFG() 
{
    I_Void * msgBuffer;
    I_S32 msgSize;
    I_U16 cellId;
    I_U16 lac;
    printf("Enter CellId and Lac for Enabled Cell\n");
    scanf("%u %u",&cellId,&lac);
    msgSize = sizeof(OamsCellhCfgAlarmInd);
    msgBuffer = AlocMsgBuf(msgSize);
    memset(msgBuffer, 0,msgSize);
    ((OamsCellhCfgAlarmInd *) msgBuffer)->sysAlarm.sysalarmId = ALARM_CELL_ENABLED ;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.alarmSeqNo = 0;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.alarmTime =  0;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.alarmReason =0;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.key1 = lac;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.key2 = cellId;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.info3 = OAMS_OBJTYPE_CELL;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.infoStrLen = 0;
   printf("sending Enable for Cell Id :: %d , lac :: %d\n",cellId,lac);
   cfgCellhStubSendMessage((OamsCellhCfgAlarmInd *)msgBuffer, sizeof(OamsCellhCfgAlarmInd), ENT_OAMS_CELLH,
       ENT_OAMS_CFG, OAMS_CELLH_CFG_ALARM_IND,0);
}

void sendCellDisabletoCFG() 
{    
    I_Void * msgBuffer;
    I_S32 msgSize;
    I_U16 cellId;
    I_U16 lac;
    printf("Enter CellId and Lac for Disabled Cell\n");
    scanf("%u%u", &cellId,&lac);
    msgSize = sizeof(OamsCellhCfgAlarmInd);
    msgBuffer = AlocMsgBuf(msgSize);
    memset(msgBuffer, 0,msgSize);
    ((OamsCellhCfgAlarmInd *) msgBuffer)->sysAlarm.sysalarmId = ALARM_CELL_DISABLED ;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.alarmSeqNo = 0;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.alarmTime =  0;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.alarmReason =0;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.key1 = lac;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.key2 = cellId;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.info3 = OAMS_OBJTYPE_CELL;
    ((OamsCellhCfgAlarmInd *)msgBuffer)->sysAlarm.infoStrLen = 0;
    printf("sending Enable for Cell Id :: %d , lac :: %d\n",cellId,lac);
    cfgCellhStubSendMessage((OamsCellhCfgAlarmInd *)msgBuffer, sizeof(OamsCellhCfgAlarmInd), ENT_OAMS_CELLH, 
       ENT_OAMS_CFG, OAMS_CELLH_CFG_ALARM_IND,0);
}

void cfgFrmwrkInit(I_S32 srcId)
{
   I_S8 retVal;
   printf("\nCFG: Calling function cfgFrmwrkInit()");
   retVal = RegisterWithIpcFrmwrk(srcId, (I_S8*)"CFG_CELLH_STUB");
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
   int choice ;
   I_U32 i=0;
   printf("CELLH CFG Stub \n");
   printf("\n CELLH Configured \n");
   cfgFrmwrkInit(ENT_OAMS_CELLH);
  
   while(1)
     {
     fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------- \n");
     fprintf(stderr, "-------->> 1.To Send Cell Enable  to CFG ----------------- \n");
     fprintf(stderr, "-------->> 2.To Send Cell Disable to CFG ----------------- \n");
     fprintf(stderr, "<<-------- 3.To_Receive data \n");
     fprintf(stderr, "<<-------- 4.EXIT \n");
     
     scanf("%d", &choice);
     switch(choice)
     {

        case 1 :
               sendCellEnabletoCFG();
               break;    
        case 2 :
               sendCellDisabletoCFG();
               break;    
      	case 3 :
                cellhReqHandler();
               break;  
        case 4 :
               exit(0);
                
        default :
               fprintf(stderr, "\n INVALID CHOICE \n");
 
      }
  continue ;
  //return 0;
    }
   return 1;
}

void cellhReqHandler()
{
   while(1)
   {
      cfgMsgBuf = (void *)RecvMsg(ENT_OAMS_CELLH, &recvMsgSize);
      if (cfgMsgBuf == NULL)
      {
         continue;
      }
      sysHdrPtr =  (SysHdr *) cfgMsgBuf;
      switch( sysHdrPtr->msgType)
      {
      	case OAMS_CFG_CELLH_UNLOCK_REQ:
            printf("Received Msg : OAMS_CFG_CELLH_UNLOCK_REQ");
	         unlockReqHandler();
      	   break;
	      case OAMS_CFG_CELLH_LOCK_REQ:
	         printf("Recieved Msg : OAMS_CFG_CELLH_LOCK_REQ");
	         lockReqHandler();
	         break;
	      case OAMS_CFG_CELLH_E1_UNLOCK_REQ:
	         printf("Received Msg : OAMS_CFG_CELLHH_E1_UNLOCK_REQ");
      	   e1UnlockReqHandler();
	         break;
	      case OAMS_CFG_CELLH_E1_LOCK_REQ:
	         printf("Received Msg : OAMS_CFG_CELLH_E1_LOCK_REQ");
	         e1LockReqHandler();
	         break;
              case OAMS_CFG_CELLH_BLOCK_IND :
                  printf("Received Msg : OAMS_CFG_CELLH_SHUTDOWN_IND");
                  break;

      }
      DalocMsgBuf(cfgMsgBuf);
   }
   
}




void e1UnlockReqHandler() 
{
   OamsCfgCellhAbisE1UnlockReq *oamsCfgCellhAbisE1UnlockReqPtr = NULL;
   OamsCellhCfgAbisE1UnlockResp oamsCellhCfgAbisE1UnlockResp;
   oamsCfgCellhAbisE1UnlockReqPtr = (OamsCfgCellhAbisE1UnlockReq *) cfgMsgBuf;
   printf("Cellh E1 Unlock Request\n");
   printf("E1 Num :: %d , Cell Id :: %d , lac :: %d\n" , oamsCfgCellhAbisE1UnlockReqPtr->e1Id, oamsCfgCellhAbisE1UnlockReqPtr->objId,oamsCfgCellhAbisE1UnlockReqPtr->lac);
   oamsCellhCfgAbisE1UnlockResp.lac = oamsCfgCellhAbisE1UnlockReqPtr->lac;
   oamsCellhCfgAbisE1UnlockResp.objId = oamsCfgCellhAbisE1UnlockReqPtr->objId;
   oamsCellhCfgAbisE1UnlockResp.e1Id = oamsCfgCellhAbisE1UnlockReqPtr->e1Id;
   printf("Press enter to send E1 Unlock Response \n");
   getchar();
   cfgCellhStubSendMessage(&oamsCellhCfgAbisE1UnlockResp, sizeof(OamsCellhCfgAbisE1UnlockResp), ENT_OAMS_CELLH, ENT_OAMS_CFG, OAMS_CELLH_CFG_E1_UNLOCK_RESP,0);
}

void e1LockReqHandler() 
{
   OamsCfgCellhAbisE1LockReq *oamsCfgCellhAbisE1LockReqPtr = NULL;
   OamsCellhCfgAbisE1LockResp oamsCellhCfgAbisE1LockResp;
   oamsCfgCellhAbisE1LockReqPtr = (OamsCfgCellhAbisE1LockReq *) cfgMsgBuf;
   printf("Cellh E1 Lock Request\n");
   printf("E1 Num :: %d , Cell Id :: %d , lac :: %d\n" , oamsCfgCellhAbisE1LockReqPtr->e1Id, oamsCfgCellhAbisE1LockReqPtr->objId,oamsCfgCellhAbisE1LockReqPtr->lac);
   oamsCellhCfgAbisE1LockResp.lac = oamsCfgCellhAbisE1LockReqPtr->lac;
   oamsCellhCfgAbisE1LockResp.objId = oamsCfgCellhAbisE1LockReqPtr->objId;
   oamsCellhCfgAbisE1LockResp.e1Id = oamsCfgCellhAbisE1LockReqPtr->e1Id;
   printf("Press enter to send E1 Lock Response \n");
   getchar();
   cfgCellhStubSendMessage(&oamsCellhCfgAbisE1LockResp, sizeof(OamsCellhCfgAbisE1LockResp), ENT_OAMS_CELLH, ENT_OAMS_CFG, OAMS_CELLH_CFG_E1_LOCK_RESP,0);
}

void unlockReqHandler() 
{
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr = NULL;
   OamsCellhCfgUnlockResp oamsCellhCfgUnlockResp;
   oamsCfgCellhUnlockReqPtr = (OamsCfgCellhUnlockReq *) cfgMsgBuf;
   printf("Cellh Unlock Request\n");
   printf("Cell Id :: %u , lac :: %u\n" , oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);
   oamsCellhCfgUnlockResp.lac = oamsCfgCellhUnlockReqPtr->lac;
   oamsCellhCfgUnlockResp.objId = oamsCfgCellhUnlockReqPtr->objId;
//   printf("Press enter to send E1 Unlock Response \n");
//   getchar();
   cfgCellhStubSendMessage(&oamsCellhCfgUnlockResp, sizeof(OamsCellhCfgUnlockResp), ENT_OAMS_CELLH, ENT_OAMS_CFG, OAMS_CELLH_CFG_UNLOCK_RESP,0);
}

void lockReqHandler() 
{
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr = NULL;
   OamsCellhCfgLockResp oamsCellhCfgLockResp;
   oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *) cfgMsgBuf;
   printf("Cellh Lock Request\n");
   printf("Cell Id :: %d , lac :: %d\n" , oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
   oamsCellhCfgLockResp.lac = oamsCfgCellhLockReqPtr->lac;
   oamsCellhCfgLockResp.objId = oamsCfgCellhLockReqPtr->objId;
   printf("Press enter to send Lock Response \n");
   getchar();
   cfgCellhStubSendMessage(&oamsCellhCfgLockResp, sizeof(OamsCellhCfgLockResp), ENT_OAMS_CELLH, ENT_OAMS_CFG, OAMS_CELLH_CFG_LOCK_RESP,0);
}

I_S32 cfgCellhStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;
   sndMsgSize = 0;
   printf("\n\t Calling cfgCellhStubSendMessage().....");

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