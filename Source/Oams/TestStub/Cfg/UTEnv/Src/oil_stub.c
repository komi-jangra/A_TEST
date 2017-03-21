#include <includes.h>
#undef SendMsg
#undef StartTimerFrmwrk 
#undef StopTimerFrmwrk 
I_U32 scmRespAction;

I_S32 cfgStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;

   sndMsgSize = 0;

   LOG_PRINT(LOG_INFO,"\n\t Calling cfgStubSendMessage().....");

   if (bufPtr != NULL)
      sndMsgSize = size;
   else
      sndMsgSize = sizeof(SysHdr);

   if ((sndPtr = (SysHdr *)AlocMsgBuf(sndMsgSize)) == NULL)
   {
      LOG_PRINT(LOG_INFO,"CFG_SEND_ALLOC_FAIL");
      return -1; 
   }

   memset(sndPtr,0,sndMsgSize) ;
   if (bufPtr != NULL)
      memcpy(((I_U8 *)sndPtr), (I_U8*)bufPtr, size);

   sndPtr->msgType = msgType;
   sndPtr->src.entity = SrcEntId;
   /* sndPtr->dest.entity = DestEntId;
   */
   sndPtr->dest.entity = ENT_OAMS_CFG;


   LOG_PRINT(LOG_INFO,"\n sndPtr->msgType = %d", sndPtr->msgType);
   LOG_PRINT(LOG_INFO,"\n sndPtr->sHdr.src.entity = %d", sndPtr->src.entity);
   LOG_PRINT(LOG_INFO,"\n sndPtr->sHdr.dest.entity = %d", sndPtr->dest.entity);

   LOG_PRINT(LOG_INFO,"\n Sending message ...........");

   fflush(stdin);
   if (SendMsg(sndPtr, 1, sndMsgSize) < 0)
   {
      LOG_PRINT(LOG_INFO,"\nCFG: In func cfgSendMessage() - msg sending failed");
      DalocMsgBuf((I_PVoid) sndPtr);
      return(-1);
   }
   return(1);
}

I_U32 convertMsgOpCodeFromReq2Resp(I_U32 req_opcode)
{
   switch ( req_opcode ) {
      case OAM_SCM_SS7_STACK_CONFIG:
        LOG_PRINT(INFO,"Received OAM_SCM_SS7_STACK_CONFIG..");
        return SCM_OAM_SS7_STACK_CONFIG_RESP;
      case OAM_SCM_INTERFACE_CONFIG:
        LOG_PRINT(INFO,"Received OAM_SCM_INTERFACE_CONFIG..");
        return SCM_OAM_INTERFACE_CONFIG_RESP;
      case OAM_SCM_LINKSET_CONFIG:  
        LOG_PRINT(INFO,"Received OAM_SCM_LINKSET_CONFIG..");
        return SCM_OAM_LINKSET_CONFIG_RESP;
      case OAM_SCM_LINK_CONFIG:   
        LOG_PRINT(INFO,"Received OAM_SCM_LINK_CONFIG..");
         return SCM_OAM_LINK_CONFIG_RESP;
      case OAM_SCM_TRUNK_CIC_CONFIG:   
        LOG_PRINT(INFO,"Received OAM_SCM_TRUNK_CIC_CONFIG..");
         return SCM_OAM_TRUNK_CIC_CONFIG_RESP;
      case OAM_SCM_SS7ROUTE_CONFIG:
        LOG_PRINT(INFO,"Received OAM_SCM_SS7ROUTE_CONFIG..");
         return SCM_OAM_SS7ROUTE_CONFIG_RESP;
      case OAM_SCM_MTP3_TIMER_CONFIG:
        LOG_PRINT(INFO,"Received OAM_SCM_MTP3_TIMER_CONFIG..");
         return SCM_OAM_MTP3_TIMER_CONFIG_RESP;
      case OAM_SCM_SCCP_TIMER_CONFIG:
        LOG_PRINT(INFO,"Received OAM_SCM_SCCP_TIMER_CONFIG..");
         return SCM_OAM_SCCP_TIMER_CONFIG_RESP;
      case OAM_SCM_BSSAP_TIMER_CONFIG:  
        LOG_PRINT(INFO,"Received OAM_SCM_BSSAP_TIMER_CONFIG..");
         return SCM_OAM_BSSAP_TIMER_CONFIG_RESP;
      case OAM_SCM_LAPDTIMER_CONFIG:  
        LOG_PRINT(INFO,"Received OAM_SCM_LAPDTIMER_CONFIG..");
        return SCM_OAM_LAPDTIMER_CONFIG_RESP;
      case OAM_SCM_LINK_ADMIN_CONFIG:   
        LOG_PRINT(INFO,"Received OAM_SCM_LINK_ADMIN_CONFIG..");
         return SCM_OAM_LINK_ADMIN_CONFIG_RESP;
      case OAM_SCM_SS7ROUTE_TESTON_CONFIG:
        LOG_PRINT(INFO,"Received OAM_SCM_SS7ROUTE_TESTON_CONFIG..");
         return SCM_OAM_SS7ROUTE_TESTON_CONFIG_RESP;
      case OAM_SCM_ALARM_MODIFY:
        LOG_PRINT(INFO,"Received OAM_SCM_ALARM_MODIFY..");
         return SCM_OAM_ALARM_MODIFY_RESP;
      default: 
         return BASE_OPCODE_SCM;  // This will not match to exiting codes.
   }
   return BASE_OPCODE_SCM;
}

I_Void sendScmResp()
{
  ScmOamResponse *ScmOamRespPtr = NULL;
  SysHdr *SysHdrPtr = NULL;
   
  if ( NULL == (SysHdrPtr = AlocMsgBuf(sizeof(ScmOamResponse) + sizeof(SysHdr) )) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ;       
  }
  ScmOamRespPtr = (ScmOamResponse *)(SysHdrPtr + 1);
  ScmOamRespPtr->scmhdr = *(ScmHdr *)((SysHdr *)(RCVD_MSG_PTR) + 1); 
  ScmOamRespPtr->scmhdr.opcode = convertMsgOpCodeFromReq2Resp(ScmOamRespPtr->scmhdr.opcode);
  ScmOamRespPtr->erro_code = (scmRespAction == ALL_OK ? 0 : 1);

  FILL_SYS_HDR( SysHdrPtr, 
                OAM_OIL_CFG_SCM_MSG_RESP, 
                0, 
                0, 
                ENT_OAM_OIL, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );

  SendMsgToIPC( 
                (I_PVoid)SysHdrPtr,
                sizeof(ScmOamResponse) + sizeof(SysHdr), 
                "OAM_OIL_CFG_SCM_MSG_RESP"
              );
}

I_Void sendClockSourceResp(OamsCfgOilSetClkSrcReq *oamsCfgOilSetClkSrcReq)
{
   I_U32 count;
   OamOilCfgSetClkSrcResp oamOilCfgSetClkSrcResp;
   I_U32 maxClkConfig;
   I_U32 frameId;
   I_U32 slotId;
   I_U32 trunkPortId;
   I_U32 priority;
   
   printf("\nSending Clock Source Resp");
   while(1)
   {
      printf("\nEnter number of Clock Source (<= 5):: "); 
      scanf("%d" , &maxClkConfig);
      oamOilCfgSetClkSrcResp.maxClkConfig = maxClkConfig;
      if(oamOilCfgSetClkSrcResp.maxClkConfig <= 5)
         break;
      else
         printf("\nInvalid Input");
   
   }
   oamOilCfgSetClkSrcResp.result = 0;
   for(count = 0 ; count < oamOilCfgSetClkSrcResp.maxClkConfig ; count++)
   {
      printf("\nEnter Frame Id::  ");
      scanf("%d" ,&frameId );
      oamOilCfgSetClkSrcResp.clkSrcPriorityResult[count].frameId =frameId;
      printf("\nEnter Slot Id::  ");
      scanf("%d" ,&slotId );
      oamOilCfgSetClkSrcResp.clkSrcPriorityResult[count].slotId =slotId;
      printf("\nEnter Trunk Port Id::  ");
      scanf("%d" ,&trunkPortId );
      oamOilCfgSetClkSrcResp.clkSrcPriorityResult[count].trunkPortId =trunkPortId;
      printf("\nEnter Priority::  ");
      scanf("%d" ,&priority );
      oamOilCfgSetClkSrcResp.clkSrcPriorityResult[count].priority =priority;
      oamOilCfgSetClkSrcResp.clkSrcPriorityResult[count].result = 0;
   }
   cfgStubSendMessage(&oamOilCfgSetClkSrcResp, sizeof(OamOilCfgSetClkSrcResp),ENT_OAM_OIL,OAM_OIL_CFG_SET_CLK_SRC_RESP,0);
   
}
I_Void sendTrunkStateChangeResp(OamsCfgOilE1EnableReq *oamsCfgOilE1EnableReq)
{
   OamOilCfgE1EnableResp oamOilCfgE1EnableResp;
   OamAfhAlarmInd    alarmInd = {0};
   I_U32 count;
   printf("\nTrunk State Change Resp.........");

   if( oamsCfgOilE1EnableReq->portDetail[0].operatorControlledTrunkState == ENABLED)
   alarmInd.sysAlarm.sysalarmId = ALARM_E1_ENABLE_SUCCESS;

   if( oamsCfgOilE1EnableReq->portDetail[0].operatorControlledTrunkState == DISABLED)
   alarmInd.sysAlarm.sysalarmId = ALARM_E1_DISABLE_SUCCESS;

   cfgStubSendMessage(&alarmInd, sizeof(OamAfhAlarmInd),ENT_OAM_OIL,OAM_OIL_CFG_ALARM_IND,0);

   oamOilCfgE1EnableResp.numPorts = oamsCfgOilE1EnableReq->numPorts;
   oamOilCfgE1EnableResp.transactionId = oamsCfgOilE1EnableReq->transactionId;
   oamOilCfgE1EnableResp.result = 0;
   for(count = 0 ; count < oamsCfgOilE1EnableReq->numPorts ; count++)
   {
      oamOilCfgE1EnableResp.portResult[count].frameId = oamsCfgOilE1EnableReq->portDetail[count].frameId;
      oamOilCfgE1EnableResp.portResult[count].slotId = oamsCfgOilE1EnableReq->portDetail[count].slotId;
      oamOilCfgE1EnableResp.portResult[count].trunkPortId = oamsCfgOilE1EnableReq->portDetail[count].trunkPortId;
      oamOilCfgE1EnableResp.portResult[count].result = 0;
   }
   cfgStubSendMessage(&oamOilCfgE1EnableResp, sizeof(OamOilCfgE1EnableResp),ENT_OAM_OIL,OAM_OIL_CFG_TRUNK_STATE_CHANGE_RESP,0);
   /* Send Alarm */
   

}

I_Void cleanSystemTypeDetails(I_Void)
{
    SystemTypeTableApi *outData;
    I_U32 outRows;
    I_U32 index;
    I_U16 outSize;
    if ( getallSystemTypeTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) {
       for (index=0;index<outRows;index++) {
          if ( deleteSystemTypeTable( (SystemTypeTableIndices *)((I_U8 *)outData + (index*outSize))) 
               != CLIB_SUCCESS) {
            LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call Failed");
          }  
       }
    } 
    LOG_PRINT(LOG_INFO,"Initialisation of SystemTypeTableApi OK ");  
}

I_Void sendSystemTypeDetails()
{
   OamOilCfgSystemTypeDetails oamOilCfgSystemTypeDetails;
   oamOilCfgSystemTypeDetails.systemType = 1;
   printf("\nSystem Type Details.........");
   cfgStubSendMessage(&oamOilCfgSystemTypeDetails, sizeof(OamOilCfgSystemTypeDetails),ENT_OAM_OIL,OAM_OIL_CFG_SYSTEM_TYPE_DETAILS,0);
}
       
I_Void cleanChasisFrameDetails(I_Void)
{
    ChasisFrameIdTableApi *outData;
    I_U32 outRows;
    I_U32 index;
    I_U16 outSize;
    if ( getallChasisFrameIdTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) {
       for (index=0;index<outRows;index++) {
          if ( deleteChasisFrameIdTable( (ChasisFrameIdTableIndices *)((I_U8 *)outData + (index*outSize))) 
               != CLIB_SUCCESS) {
            LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call Failed");
          }  
       }
    } 
    LOG_PRINT(LOG_INFO,"Initialisation of SystemTypeTableApi OK ");  
}
       
I_Void sendChasisFrameDetails()
{
   OamOilCfgChasisFrameDetails oamOilCfgChasisFrameDetails;
   printf("\nChasis Frame Details.........");
   oamOilCfgChasisFrameDetails.chasisFrameId = 1;
   oamOilCfgChasisFrameDetails.totalNumCards = 2;
   oamOilCfgChasisFrameDetails.numRemoteCards = 2;
   cfgStubSendMessage(&oamOilCfgChasisFrameDetails, sizeof(OamOilCfgChasisFrameDetails),ENT_OAM_OIL,OAM_OIL_CFG_CHASIS_FRAME_DETAILS,0);
}

I_Void cleanTrunkPortDetails(I_Void)
{
    TrunkPortTableApi *outData;
    I_U32 outRows;
    I_U32 index;
    I_U16 outSize;
    if ( getallTrunkPortTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) {
       for (index=0;index<outRows;index++) {
          if ( deleteTrunkPortTable( (TrunkPortTableIndices *)((I_U8 *)outData + (index*outSize))) 
               != CLIB_SUCCESS) {
            LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call Failed");
          }  
       }
    } 
    LOG_PRINT(LOG_INFO,"Initialisation of SystemTypeTableApi OK ");  
}

I_Void sendTrunkPortDetails()
{
   OamOilCfgTrunkPortDetails oamOilCfgTrunkPortDetails;
   I_U32 count=0;
   I_U32 numPorts = 1;
   I_U32 slotId = 1;
   I_U32 frameId = 1;
   I_U32 trunkId =1 ;
   
   oamOilCfgTrunkPortDetails.numPorts = numPorts;
   oamOilCfgTrunkPortDetails.portDetail[count].operatorControlledTrunkState = 1;
   oamOilCfgTrunkPortDetails.portDetail[count].trunkPortId = trunkId;
   oamOilCfgTrunkPortDetails.portDetail[count].slotId = slotId;
   oamOilCfgTrunkPortDetails.portDetail[count].frameId = frameId;
   oamOilCfgTrunkPortDetails.portDetail[count].trunkType = 1;
   oamOilCfgTrunkPortDetails.portDetail[count].loopType = 1;
   oamOilCfgTrunkPortDetails.portDetail[count].loopback = 1;
   oamOilCfgTrunkPortDetails.portDetail[count].trunkFrameOption = 1;
   oamOilCfgTrunkPortDetails.portDetail[count].encodeType = 1;
   oamOilCfgTrunkPortDetails.portDetail[count].sigStrength = 1;
   cfgStubSendMessage(&oamOilCfgTrunkPortDetails, sizeof(OamOilCfgTrunkPortDetails),ENT_OAM_OIL,OAM_OIL_CFG_TRUNK_PORT_DETAILS,0);
}

I_Void cleanSystemClockDetails(I_Void)
{
    SystemClkInfoTableApi *outData;
    I_U32 outRows;
    I_U32 index;
    I_U16 outSize;
    if ( getallSystemClkInfoTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) {
       for (index=0;index<outRows;index++) {
          if ( deleteSystemClkInfoTable( (SystemClkInfoTableIndices *)((I_U8 *)outData + (index*outSize))) 
               != CLIB_SUCCESS) {
            LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call Failed");
          }  
       }
    } 
    LOG_PRINT(LOG_INFO,"Initialisation of SystemTypeTableApi OK ");  
}

I_Void sendSystemClockDetails()
{
   OamOilCfgSystemClockDetails oamOilCfgSystemClockDetails;
   printf("\nSystem Clock Details.........");
   oamOilCfgSystemClockDetails.clockReference = 0;
   oamOilCfgSystemClockDetails.clockPortId = 1;   
   cfgStubSendMessage(&oamOilCfgSystemClockDetails, sizeof(OamOilCfgSystemClockDetails),ENT_OAM_OIL,OAM_OIL_CFG_SYSTEM_CLOCK_DETAILS,0);

}



I_Void cleanDspObjDetails(I_Void)
{
    DspInfoTableApi *outData;
    I_U32 outRows;
    I_U32 index;
    I_U16 outSize;
    if ( getallDspInfoTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) {
       for (index=0;index<outRows;index++) {
          if ( deleteDspInfoTable( (DspInfoTableIndices *)((I_U8 *)outData + (index*outSize))) 
               != CLIB_SUCCESS) {
            LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call Failed");
          }  
       }
    } 
    LOG_PRINT(LOG_INFO,"Initialisation of SystemTypeTableApi OK ");  
}

I_Void sendDspObjDetails()
{
   OamOilCfgDspObjDetails oamOilCfgDspObjDetails;
   printf("\nDSP OBJ Details.........");
   oamOilCfgDspObjDetails.frameId = 1;
   oamOilCfgDspObjDetails.slotId = 1;
   oamOilCfgDspObjDetails.trauResource = 1;
   cfgStubSendMessage(&oamOilCfgDspObjDetails, sizeof(OamOilCfgDspObjDetails),ENT_OAM_OIL,OAM_OIL_CFG_DSP_OBJ_DETAILS,0);
      
}

I_Void cleanEicCardsDetails(I_Void)
{
    EicCardInfoTableApi *outData;
    I_U32 outRows;
    I_U32 index;
    I_U16 outSize;
    if ( getallEicCardInfoTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) {
       for (index=0;index<outRows;index++) {
          if ( deleteEicCardInfoTable( (EicCardInfoTableIndices *)((I_U8 *)outData + (index*outSize))) 
               != CLIB_SUCCESS) {
            LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call Failed");
          }  
       }
    } 
    LOG_PRINT(LOG_INFO,"Initialisation of SystemTypeTableApi OK ");  
}

I_Void sendEic1CardDetails()
{
   OamOilCfgEicCardDetail oamOilCfgEicCardDetail;
   printf("\nEIC Card 1 Details.........");
   oamOilCfgEicCardDetail.frameId = 1;
   oamOilCfgEicCardDetail.slotId  = 1;
   oamOilCfgEicCardDetail.cardType  = 1;
   memcpy(oamOilCfgEicCardDetail.cardSerialNumber, "abcd" ,20);
   oamOilCfgEicCardDetail.cardOperState = 1 ;
   oamOilCfgEicCardDetail.peerCardState = 1 ;
   oamOilCfgEicCardDetail.peerCardPresence = 1 ;
   oamOilCfgEicCardDetail.numTrunkPort = 1 ;
   oamOilCfgEicCardDetail.cpldVersionMajor  = 1 ;
   oamOilCfgEicCardDetail.cpldVersionMinor  = 1 ;
   oamOilCfgEicCardDetail.cpldVersionRevision   = 1 ;
   oamOilCfgEicCardDetail.ucVersionMajor   = 1;
   oamOilCfgEicCardDetail.ucVersionMinor  = 1 ;
   oamOilCfgEicCardDetail.ucVersionRevision   = 1;
   oamOilCfgEicCardDetail.kernelVersionMajor  = 1 ;
   oamOilCfgEicCardDetail.kernelVersionMinor = 1  ;
   oamOilCfgEicCardDetail.kernelVersionRevision  = 1 ;
   oamOilCfgEicCardDetail.uBootVersionMajor = 1  ;
   oamOilCfgEicCardDetail.uBootVersionMinor  = 1 ;
   oamOilCfgEicCardDetail.uBootVersionRevision  = 1 ;
   oamOilCfgEicCardDetail.RamdiskVersionMajor = 1  ;
   oamOilCfgEicCardDetail.RamdiskVersionMinor = 1  ;
   oamOilCfgEicCardDetail.RamdiskVersionRevision  = 1 ;
   oamOilCfgEicCardDetail.activeSwVersionMajor  = 1 ;
   oamOilCfgEicCardDetail.activeSwVersionMinor  = 1 ;
   oamOilCfgEicCardDetail.activeSwVersionRevision   = 1;
   oamOilCfgEicCardDetail.backupSwVersionMajor = 1  ;
   oamOilCfgEicCardDetail.backupSwVersionMinor  = 1 ;
   oamOilCfgEicCardDetail.backupSwVersionRevision  = 1 ;
   oamOilCfgEicCardDetail.downloadedSwVersionMajor  = 1 ;
   oamOilCfgEicCardDetail.downloadedSwVersionMinor  = 1 ;
   oamOilCfgEicCardDetail.downloadedSwVersionRevision  = 1 ;
   cfgStubSendMessage(&oamOilCfgEicCardDetail, sizeof(OamOilCfgEicCardDetail),ENT_OAM_OIL,OAM_OIL_CFG_EIC_CARD_DETAILS,0);
   
}

I_Void sendEic2CardDetails()
{
   OamOilCfgEicCardDetail oamOilCfgEicCardDetail;
   printf("\nEIC Card 2 Details.........");
   oamOilCfgEicCardDetail.frameId = 2;
   oamOilCfgEicCardDetail.slotId  = 2;
   oamOilCfgEicCardDetail.cardType  = 2;
   memcpy(oamOilCfgEicCardDetail.cardSerialNumber, "wxyz" ,20);
   oamOilCfgEicCardDetail.cardOperState = 1 ;
   oamOilCfgEicCardDetail.peerCardState = 1 ;
   oamOilCfgEicCardDetail.peerCardPresence = 1 ;
   oamOilCfgEicCardDetail.numTrunkPort = 2 ;
   oamOilCfgEicCardDetail.cpldVersionMajor  = 2 ;
   oamOilCfgEicCardDetail.cpldVersionMinor  = 2 ;
   oamOilCfgEicCardDetail.cpldVersionRevision   = 2 ;
   oamOilCfgEicCardDetail.ucVersionMajor   = 2;
   oamOilCfgEicCardDetail.ucVersionMinor  = 2 ;
   oamOilCfgEicCardDetail.ucVersionRevision   = 2;
   oamOilCfgEicCardDetail.kernelVersionMajor  = 2 ;
   oamOilCfgEicCardDetail.kernelVersionMinor = 2  ;
   oamOilCfgEicCardDetail.kernelVersionRevision  = 2 ;
   oamOilCfgEicCardDetail.uBootVersionMajor = 2  ;
   oamOilCfgEicCardDetail.uBootVersionMinor  = 2 ;
   oamOilCfgEicCardDetail.uBootVersionRevision  = 2 ;
   oamOilCfgEicCardDetail.RamdiskVersionMajor = 2  ;
   oamOilCfgEicCardDetail.RamdiskVersionMinor = 2  ;
   oamOilCfgEicCardDetail.RamdiskVersionRevision  = 2 ;
   oamOilCfgEicCardDetail.activeSwVersionMajor  = 2 ;
   oamOilCfgEicCardDetail.activeSwVersionMinor  = 2 ;
   oamOilCfgEicCardDetail.activeSwVersionRevision   = 2;
   oamOilCfgEicCardDetail.backupSwVersionMajor = 2  ;
   oamOilCfgEicCardDetail.backupSwVersionMinor  = 2 ;
   oamOilCfgEicCardDetail.backupSwVersionRevision  = 2 ;
   oamOilCfgEicCardDetail.downloadedSwVersionMajor  = 2 ;
   oamOilCfgEicCardDetail.downloadedSwVersionMinor  = 2 ;
   oamOilCfgEicCardDetail.downloadedSwVersionRevision  = 2 ;
   cfgStubSendMessage(&oamOilCfgEicCardDetail, sizeof(OamOilCfgEicCardDetail),ENT_OAM_OIL,OAM_OIL_CFG_EIC_CARD_DETAILS,0);
   
}


I_Void cleanIccCardsDetails(I_Void)
{
    IccCardInfoTableApi *outData;
    I_U32 outRows;
    I_U32 index;
    I_U16 outSize;
    if ( getallIccCardInfoTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) {
       for (index=0;index<outRows;index++) {
          if ( deleteIccCardInfoTable( (IccCardInfoTableIndices *)((I_U8 *)outData + (index*outSize))) 
               != CLIB_SUCCESS) {
            LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call Failed");
          }  
       }
    } 
    LOG_PRINT(LOG_INFO,"Initialisation of SystemTypeTableApi OK ");  
}

I_Void sendIccSelfCardDetails()
{
   OamOilCfgIccCardResp oamOilCfgIccCardResp;
   printf("\nICC Self Card Details.........");
   oamOilCfgIccCardResp.chasisFrameId = 1 ;
   oamOilCfgIccCardResp.slotId= 1  ;
   oamOilCfgIccCardResp.cardType= 1  ;
   memcpy(oamOilCfgIccCardResp.cardSerialNumber, "abcd" ,20);
   oamOilCfgIccCardResp.cardOperationalState = 73  ;
   oamOilCfgIccCardResp.peerCardState = 1  ;
   oamOilCfgIccCardResp.peerCardPresence = 1  ;
   oamOilCfgIccCardResp.oneP2PowerModuleVoltageStatus= 1 ;
   oamOilCfgIccCardResp.twoP5PowerModuleVoltageStatus= 1 ;
   oamOilCfgIccCardResp.oneP2DSPVoltageStatus = 1;
   oamOilCfgIccCardResp.twoP5PowerModuleTemperatureStatus= 1 ;
   oamOilCfgIccCardResp.threeP3PowerModuleTemperatureStatus = 1;
   oamOilCfgIccCardResp.hotSwapPowerGood1Status = 1 ;
   oamOilCfgIccCardResp.hotSwapPowerGood3Status = 1  ;
   oamOilCfgIccCardResp.cpldVersionMajor = 1 ;
   oamOilCfgIccCardResp.cpldVersionMinor = 1 ;
   oamOilCfgIccCardResp.cpldVersionRevision = 1 ;
   oamOilCfgIccCardResp.ucVersionMajor = 1 ;
   oamOilCfgIccCardResp.ucVersionMinor= 1  ;
   oamOilCfgIccCardResp.ucVersionRevision = 1 ;
   oamOilCfgIccCardResp.activeKernelVersionMajor = 1;
   oamOilCfgIccCardResp.activeKernelVersionMinor = 1 ;
   oamOilCfgIccCardResp.activeKernelVersionRevision= 1  ;
   oamOilCfgIccCardResp.backupKernelVersionMajor= 1  ;
   oamOilCfgIccCardResp.backupKernelVersionMinor= 1  ;
   oamOilCfgIccCardResp.backupKernelVersionRevision = 1 ;
   oamOilCfgIccCardResp.activeSwVersionMajor = 1 ;
   oamOilCfgIccCardResp.activeSwVersionMinor = 1 ;
   oamOilCfgIccCardResp.activeSwVersionRevision = 1 ;
   oamOilCfgIccCardResp.backupSwVersionMajor= 1  ;
   oamOilCfgIccCardResp.backupSwVersionMinor= 1  ;
   oamOilCfgIccCardResp.backupSwVersionRevision = 1 ;
   oamOilCfgIccCardResp.downloadedSwVersionMajor = 1 ;
   oamOilCfgIccCardResp.downloadedSwVersionMinor = 1 ;
   oamOilCfgIccCardResp.downloadedSwVersionRevision= 1  ;
   cfgStubSendMessage(&oamOilCfgIccCardResp, sizeof(OamOilCfgIccCardResp),ENT_OAM_OIL,OAM_OIL_CFG_ICC_CARD_DETAILS,0);
}

I_Void sendIccMateCardDetails()
{
   OamOilCfgIccCardResp oamOilCfgIccCardResp;
   printf("\nICC Mate Card Details.........");
   oamOilCfgIccCardResp.chasisFrameId = 2 ;
   oamOilCfgIccCardResp.slotId= 2  ;
   oamOilCfgIccCardResp.cardType= 2  ;
   memcpy(oamOilCfgIccCardResp.cardSerialNumber, "wxyz" ,20);
   oamOilCfgIccCardResp.cardOperationalState = 1  ;
   oamOilCfgIccCardResp.peerCardState = 1  ;
   oamOilCfgIccCardResp.peerCardPresence = 1  ;
   oamOilCfgIccCardResp.oneP2PowerModuleVoltageStatus= 2 ;
   oamOilCfgIccCardResp.twoP5PowerModuleVoltageStatus= 2 ;
   oamOilCfgIccCardResp.oneP2DSPVoltageStatus = 2;
   oamOilCfgIccCardResp.twoP5PowerModuleTemperatureStatus= 2 ;
   oamOilCfgIccCardResp.threeP3PowerModuleTemperatureStatus = 2;
   oamOilCfgIccCardResp.hotSwapPowerGood1Status = 2 ;
   oamOilCfgIccCardResp.hotSwapPowerGood3Status = 2  ;
   oamOilCfgIccCardResp.cpldVersionMajor = 2 ;
   oamOilCfgIccCardResp.cpldVersionMinor = 2 ;
   oamOilCfgIccCardResp.cpldVersionRevision = 2 ;
   oamOilCfgIccCardResp.ucVersionMajor = 2 ;
   oamOilCfgIccCardResp.ucVersionMinor= 2  ;
   oamOilCfgIccCardResp.ucVersionRevision = 2 ;
   oamOilCfgIccCardResp.activeKernelVersionMajor = 2;
   oamOilCfgIccCardResp.activeKernelVersionMinor = 2 ;
   oamOilCfgIccCardResp.activeKernelVersionRevision= 2  ;
   oamOilCfgIccCardResp.backupKernelVersionMajor= 2  ;
   oamOilCfgIccCardResp.backupKernelVersionMinor= 2  ;
   oamOilCfgIccCardResp.backupKernelVersionRevision = 2 ;
   oamOilCfgIccCardResp.activeSwVersionMajor = 2 ;
   oamOilCfgIccCardResp.activeSwVersionMinor = 2 ;
   oamOilCfgIccCardResp.activeSwVersionRevision = 2 ;
   oamOilCfgIccCardResp.backupSwVersionMajor= 2  ;
   oamOilCfgIccCardResp.backupSwVersionMinor= 2  ;
   oamOilCfgIccCardResp.backupSwVersionRevision = 2 ;
   oamOilCfgIccCardResp.downloadedSwVersionMajor = 2 ;
   oamOilCfgIccCardResp.downloadedSwVersionMinor = 2 ;
   oamOilCfgIccCardResp.downloadedSwVersionRevision= 2  ;
   cfgStubSendMessage(&oamOilCfgIccCardResp, sizeof(OamOilCfgIccCardResp),ENT_OAM_OIL,OAM_OIL_CFG_ICC_CARD_DETAILS,0);
}


I_Void sendClkSrcRespToCfg(I_U8 RespMode)
{
  I_U8 i ;
  OamOilCfgSetClkSrcResp *OamOilCfgSetClkSrcRespPtr = NULL;
  ClkSrcPortPriorityResult *ClkSrcPortPriorityResultPtr = NULL;
  OamsCfgOilSetClkSrcReq *OamsCfgOilSetClkSrcReqPtr = NULL;
  ClkSrcPortPriority *ClkSrcPortPriorityPtr = NULL;
  

  OamsCfgOilSetClkSrcReqPtr = ( OamsCfgOilSetClkSrcReq * ) RCVD_MSG_PTR;   
  ClkSrcPortPriorityPtr = OamsCfgOilSetClkSrcReqPtr->clkSrcPriority;
  
  
  if ( NULL == (OamOilCfgSetClkSrcRespPtr = AlocMsgBuf(sizeof(OamOilCfgSetClkSrcResp) )) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }
  ClkSrcPortPriorityResultPtr = OamOilCfgSetClkSrcRespPtr->clkSrcPriorityResult;
  
  OamOilCfgSetClkSrcRespPtr->maxClkConfig = OamsCfgOilSetClkSrcReqPtr->maxClkConfig;

  if ( ALL_FAIL == RespMode ) {
    OamOilCfgSetClkSrcRespPtr->result = ERR_CLOCK_CONFIG_FAIL_OTHERS;
  }
  else 
  {
    OamOilCfgSetClkSrcRespPtr->result = ERR_CLOCK_CONFIG_FAIL_OTHERS + 1;    
  }
  for (i=0; i < OamOilCfgSetClkSrcRespPtr->maxClkConfig; i++) {
    ClkSrcPortPriorityResultPtr[i].result       = ERR_CLOCK_CONFIG_FAIL_OTHERS + 1;
    switch ( RespMode ) {
      case PARTIAL_OK:
        if (i == 1) ClkSrcPortPriorityResultPtr[i].result       = ERR_CLOCK_CONFIG_FAIL_OTHERS;
      break;
      case ALL_FAIL:
        ClkSrcPortPriorityResultPtr[i].result       = ERR_CLOCK_CONFIG_FAIL_OTHERS;
      break;
    }  
    ClkSrcPortPriorityResultPtr[i].frameId      = ClkSrcPortPriorityPtr[i].frameId;
    ClkSrcPortPriorityResultPtr[i].slotId       = ClkSrcPortPriorityPtr[i].slotId;
    ClkSrcPortPriorityResultPtr[i].trunkPortId  = ClkSrcPortPriorityPtr[i].trunkPortId;
  }

  FILL_SYS_HDR( OamOilCfgSetClkSrcRespPtr, 
                OAM_OIL_CFG_SET_CLK_SRC_RESP, 
                0, 
                0, 
                ENT_OAM_OIL, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );

  SendMsgToIPC( 
                (I_PVoid)OamOilCfgSetClkSrcRespPtr,
                sizeof(OamOilCfgSetClkSrcResp), 
                "OAM_OIL_CFG_SET_CLK_SRC_RESP"
              );
  
}

I_U8 ExecuteOilAction(I_PVoid rcvPtr)
{
   static int count=1;
   //I_U32 msgSize;
	 I_S32 choice;
   //I_S8 err;
   I_U32 msgType = 0 ;
   //I_S32 dbStatus;
   //I_U32 index;
   EicCardInfoTableApi eicData;

   memset(&eicData,0,sizeof(EicCardInfoTableApi));
#if 0
   for(index=0;index<2;index++)
   {
      eicData.chasisFrameId=1;
      eicData.slotId=index;
      dbStatus=insertEicCardInfoTable(&eicData);
      if(dbStatus!=CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"Insertion in EicCardInfoTable failed ");
      }
   }
   const I_U32 SelfId = (int)ENT_OAM_OIL;
   err=RegisterWithIpcFrmwrk(SelfId, (I_S8 *)"OIL_STUB") ;
   if(err < 0)
   {
      printf("\nOIL_STUB : Unable to Register itself with IPC FrameWork : Exiting\n");
      printf("\nerr=%d\n",err);
      exit(EXIT_FAILURE);
   }
#endif

         msgType = ((SysHdr *)(rcvPtr))->msgType;

         LOG_PRINT(LOG_INFO,"scmRespAction: %d",scmRespAction);
         switch(msgType)
         {
            case OAMS_CFG_OIL_SCM_MSG_REQ:
                LOG_PRINT(LOG_INFO,"Received OAMS_CFG_OIL_SCM_MSG_REQ..");
                sendScmResp();
            break;  
            case OAMS_CFG_OIL_SET_CLK_SRC_REQ : 
              switch (TEST_GROUP_ID) {
                case TEST_GROUP_CLK_SRC_CFG:
                  switch ( TEST_CASE_ID ) {
                    case TEST_CASE5_CLK_SRC_CFG:
                      // Send ALL Negative Respose From Oil                      
                      sendClkSrcRespToCfg(ALL_FAIL);
                    break;
                    case TEST_CASE6_CLK_SRC_CFG:
                      // Send ALL_OK Response From Oil
                      sendClkSrcRespToCfg(ALL_OK);
                    break;
                    case TEST_CASE7_CLK_SRC_CFG:
                      // Send ALL_OK Response From Oil
                      sendClkSrcRespToCfg(ALL_OK);
                    break;
                    case TEST_CASE8_CLK_SRC_CFG:
                      // Send ALL_OK Response From Oil
                      sendClkSrcRespToCfg(ALL_OK);
                    break;
                    case TEST_CASE9_CLK_SRC_CFG:
                      // Send ALL_OK Response From Oil
                      sendClkSrcRespToCfg(ALL_FAIL);
                    break;  
                    case TEST_CASE10_CLK_SRC_CFG:
                      // Send ALL_OK Response From Oil
                      sendClkSrcRespToCfg(PARTIAL_OK);
                    break;      
                    case TEST_CASE11_CLK_SRC_CFG:
                      // Send ALL_OK Response From Oil
                      sendClkSrcRespToCfg(ALL_FAIL);
                    break;                      
                  }  
                break;  
              }
            break;
            case BSC_API_GET_ICCCARDINFOTABLE :
               {
                  IccCardInfoTableApi CardInfoTableApiBuff={0};
                  LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
                  cfgStubSendMessage(&CardInfoTableApiBuff,
                                     sizeof(IccCardInfoTableApi),
                                     ENT_OAM_OIL,BSC_API_GET_ICCCARDINFOTABLE,0);
                  break;
               }

            case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
               {
                  count++;
                  LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:\n");
                  OamsCfgOilAvailableReleasesReq *AvailRelReqPtr =NULL;
                  AvailRelReqPtr = (OamsCfgOilAvailableReleasesReq *)rcvPtr;
                  OamOilCfgAvailableReleasesResp availRelRespBuff;
                  OamOilCfgInfoAvailableVersion bpmAvailVersion;
                  I_U32 ch = 3;
                  strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[0],"");
                  strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[1],"");
                  strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[2],"");

                  LOG_PRINT(LOG_INFO," Recieved NodeType: %d", AvailRelReqPtr->nodeType);
                  if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_EIC || 
                     AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BIC || 
                     AvailRelReqPtr->nodeType == SYS_NODE_TYPE_TRX || 
                     AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BSC
                    )
                  {
                     bpmAvailVersion.nodeInfo.chasisFrameId = 1;
                     bpmAvailVersion.nodeInfo.slotId = 0;
                     bpmAvailVersion.nodeInfo.nodeType = AvailRelReqPtr->nodeType;
#if 0                     
                     printf("\n\nEnter choice for No. of releases:\n(1) All the three versions\n(2) Only Two Versions\n(3) Only one Verison\n"); 
                     scanf("%d",&ch);
#endif
                     ch=1;
                     availRelRespBuff.nodeType = AvailRelReqPtr->nodeType;
                     availRelRespBuff.numVersion = 3;
                     if(  AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BIC || 
                          AvailRelReqPtr->nodeType == SYS_NODE_TYPE_TRX
                       )
                        availRelRespBuff.numVersion = 0;
                     if( ch == 1 || ch == 2 || ch == 3)
                     {
                        strcpy(availRelRespBuff.availSwVersions[0],"123.78.120");
                        memcpy(availRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
                        strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[0],"123.78.120");
                        memcpy(bpmAvailVersion.swMAvailResp.availSwBinaryPath[0],"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
                        if( ch == 1 || ch == 2)
                        {
                           strcpy(availRelRespBuff.availSwVersions[1],"123.0.201");
                           memcpy(availRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-1.0.7",CMD_PARAM_MAX_SIZE);
                           strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[1],"123.0.201");
                           memcpy(bpmAvailVersion.swMAvailResp.availSwBinaryPath[1],"/home/SoftRelease/Rel-1.0.7",CMD_PARAM_MAX_SIZE);
                           if( ch == 1)
                           {
                              strcpy(availRelRespBuff.availSwVersions[2],"123.211.0");
                              memcpy(availRelRespBuff.availSwBinaryPath[2],"/home/SoftRelease/Rel-1.0.6",CMD_PARAM_MAX_SIZE);
                              strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[2],"123.211.0");
                              memcpy(bpmAvailVersion.swMAvailResp.availSwBinaryPath[2],"/home/SoftRelease/Rel-1.0.6",CMD_PARAM_MAX_SIZE);
                           }
                        }
                     }
                     else
                     {
                        printf("Invalid Choice");
                        break;
                     }
                     cfgStubSendMessage(&availRelRespBuff,
                                        sizeof(OamOilCfgAvailableReleasesResp),
                                        ENT_OAM_OIL,
                                        OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,
                                        0);
                     bpmAvailVersion.moduleName = NODE_TYPE_BSC;
                     bpmAvailVersion.alarmLevel = TRAP_SEVERITY_INFORMATION;
                     bpmAvailVersion.alarmId = NODE_TYPE_BSC;
                     bpmAvailVersion.swMAvailResp.nodeType = AvailRelReqPtr->nodeType;
                     bpmAvailVersion.swMAvailResp.numVersion = 3;
                     if(  AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BIC || 
                          AvailRelReqPtr->nodeType == SYS_NODE_TYPE_TRX
                       )
                        bpmAvailVersion.swMAvailResp.numVersion = 0;
                        cfgStubSendMessage(&bpmAvailVersion,
                                           sizeof(OamOilCfgInfoAvailableVersion),
                                           ENT_OAM_OIL,
                                           OAM_OIL_CFG_INFO_AVAILABLE_VERSION,
                                           0);
                  }
                  else
                  {                  
                     LOG_PRINT(LOG_MAJOR,"Invalid NodeId received in OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ");   
                  }
                  if ( AvailRelReqPtr->nodeType == SYS_NODE_TYPE_EIC )
                  {
                    return 1;
                  }  
                  break;
               }

            case OAMS_CFG_OIL_SW_OFFER_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_OFFER_REQ from Cfg..\n");
                  OamsCfgOilSwOfferReq *swOfferReqPtr = (OamsCfgOilSwOfferReq *)rcvPtr;
                  OamOilCfgInfoSwDwnldResult bpmDwnldResult;
                  
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_OFFER_RESP..");
                  cfgStubSendMessage(NULL,sizeof(SysHdr),ENT_OAM_OIL,OAM_OIL_CFG_SW_OFFER_RESP,0);
                  LOG_PRINT(LOG_INFO,"Sending INFO_BPM_SW_UPGRADE_OFFER.. Software Offer is in progress...");
                  bpmDwnldResult.nodeInfo.chasisFrameId = 1;
                  bpmDwnldResult.nodeInfo.slotId = 0;
                  bpmDwnldResult.nodeInfo.nodeType = swOfferReqPtr->nodeType;
                  bpmDwnldResult.moduleName = NODE_TYPE_BSC;
                  bpmDwnldResult.alarmId = EVENT_SW_UPGRADE_OFFER_COMPLETED;
                  bpmDwnldResult.alarmLevel = TRAP_SEVERITY_INFORMATION;

                  bpmDwnldResult.swMOfferResp.nodeType = swOfferReqPtr->nodeType;
                  strcpy(bpmDwnldResult.swMOfferResp.upgradeVersion,swOfferReqPtr->upgradeVersion);
                  cfgStubSendMessage(&bpmDwnldResult,
                                     sizeof(OamOilCfgInfoSwDwnldResult),
                                     ENT_OAM_OIL,
                                     OAM_OIL_CFG_INFO_SW_UPGRADE_OFFER,
                                     0);

                  bpmDwnldResult.moduleName = NODE_TYPE_BSC;

                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  if(choice ==1)
                  {
                     bpmDwnldResult.swMOfferResp.upgradeOfferResult = UPGRADE_OFFER_SUCCESSFUL;
                     bpmDwnldResult.alarmId = EVENT_SW_UPGRADE_OFFER_COMPLETED;
                     bpmDwnldResult.alarmLevel = TRAP_SEVERITY_INFORMATION;

                  }
                  else
		              {
                      printf("\nERROR CAUSE\tSpace unavailable (1)/ Error Writing to flash (2)");
                      printf("\nEnter your choice : ");
		                  scanf("%d", &choice);
                      if(choice == 1)
                         bpmDwnldResult.swMOfferResp.upgradeOfferResult = ERROR_SPACE_UNAVAILABLE;
                      else
                         bpmDwnldResult.swMOfferResp.upgradeOfferResult = ERROR_WRITING_TO_FLASH;
                     bpmDwnldResult.alarmId = EVENT_SW_UPGRADE_OFFER_FAILED;
                     bpmDwnldResult.alarmLevel = TRAP_SEVERITY_MAJOR;
                  }
                  bpmDwnldResult.swMOfferResp.nodeType = swOfferReqPtr->nodeType;
                  strcpy(bpmDwnldResult.swMOfferResp.upgradeVersion,swOfferReqPtr->upgradeVersion);
                  memcpy(bpmDwnldResult.swMOfferResp.binaryPath,
                         "/home/geetanjali/Sw_Rel_SI/Bic/bic321.tar",
                         CMD_PARAM_MAX_SIZE);
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_INFOSW_UPGRADE_OFFER..");
                  cfgStubSendMessage(&bpmDwnldResult,
                                     sizeof(OamOilCfgInfoSwDwnldResult),
                                     ENT_OAM_OIL,
                                     OAM_OIL_CFG_INFO_SW_DWNLD_RESULT,
                                     0);
                  break;
               }

            case OAMS_CFG_OIL_SW_ACT_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_ACT_REQ from Cfg..");
                  OamsCfgOilSwActReq *swActReqPtr = (OamsCfgOilSwActReq *)rcvPtr;
                  OamOilCfgInfoSwActResult bpmActResult;


                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_ACT_RESP..");
                  cfgStubSendMessage(NULL,sizeof(SysHdr),ENT_OAM_OIL,OAM_OIL_CFG_SW_ACT_RESP,0);
                 
                  bpmActResult.nodeInfo.chasisFrameId = 1;
                  bpmActResult.nodeInfo.slotId = 0;
                  bpmActResult.nodeInfo.nodeType = swActReqPtr->nodeType;

                  bpmActResult.moduleName = NODE_TYPE_BSC;
                  bpmActResult.alarmId = EVENT_SW_ACT_STARTED;
                  bpmActResult.alarmLevel = TRAP_SEVERITY_INFORMATION;

                  bpmActResult.swMActResp.nodeType = swActReqPtr->nodeType;
                  strcpy(bpmActResult.swMActResp.actVersion,swActReqPtr->actVersion);

                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_INFO_BPM_SW_ACT_STARTED..");
                  cfgStubSendMessage(&bpmActResult,
                                     sizeof(OamOilCfgInfoSwActResult),
                                     ENT_OAM_OIL,
                                     OAM_OIL_CFG_INFO_SW_ACT_STARTED,
                                     0);
        
                  bpmActResult.moduleName = NODE_TYPE_BSC;

                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  if(choice ==1)
                  {
		                 bpmActResult.swMActResp.actResult = ACTIVATION_SUCCESSFUL;
                     bpmActResult.alarmLevel = TRAP_SEVERITY_INFORMATION;
                     bpmActResult.alarmId = EVENT_SW_ACT_COMPLETED;
                  }

                  else
                  {
                      printf("\nERROR CAUSE\tUnable to activate (1)/ Error Activation Failure (2)");
                      printf("\nEnter your choice : ");
		                  scanf("%d", &choice);
                      if(choice == 1)
                         bpmActResult.swMActResp.actResult = UNABLE_TO_ACTIVATE;
                      else
                         bpmActResult.swMActResp.actResult = ERROR_ACTIVATION_FAILURE;
                     bpmActResult.alarmLevel = TRAP_SEVERITY_MAJOR;
                     bpmActResult.alarmId = EVENT_SW_ACT_FAILED;
                  }

	                bpmActResult.swMActResp.nodeType = swActReqPtr->nodeType;
                  strcpy(bpmActResult.swMActResp.actVersion,swActReqPtr->actVersion);
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_INFO_BPM_SW_ACT_SUCCESS..");
                  cfgStubSendMessage(&bpmActResult,
                                     sizeof(OamOilCfgInfoSwActResult),
                                     ENT_OAM_OIL,
                                     OAM_OIL_CFG_INFO_SW_ACT_RESULT,
                                     0);
                  break;
               }

            case OAMS_CFG_OIL_SW_DEL_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_DEL_REQ from Cfg..");
                  OamsCfgOilSwDelReq *swDelReqPtr = (OamsCfgOilSwDelReq *)rcvPtr;
                  OamOilCfgSwDelResp swDelRespBuff;
                  OamOilCfgInfoDelResult bpmDelResult;
                  LOG_PRINT(LOG_INFO,"NodeType:%d",swDelReqPtr->nodeType);
                  LOG_PRINT(LOG_INFO,"NodeType:%s",swDelReqPtr->delVersion);
                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  bpmDelResult.nodeInfo.chasisFrameId = 1;
                  bpmDelResult.nodeInfo.slotId = 0;
                  bpmDelResult.nodeInfo.nodeType = swDelReqPtr->nodeType;

                  bpmDelResult.moduleName = NODE_TYPE_BSC;
                  if(choice ==1)
                  {
                     swDelRespBuff.versionDelResult = DELETE_SUCCESSFUL;
                     bpmDelResult.alarmLevel = TRAP_SEVERITY_INFORMATION;
                     bpmDelResult.alarmId = EVENT_SW_DEL_COMPLETED;
                     bpmDelResult.swMDelResp.versionDelResult = DELETE_SUCCESSFUL;
                  }
                  else
                  {
                     swDelRespBuff.versionDelResult = ERROR_CONNECTING_UA_CP;
                     bpmDelResult.alarmLevel = TRAP_SEVERITY_MAJOR;
                     bpmDelResult.alarmId = EVENT_SW_DEL_FAILED;
                     bpmDelResult.swMDelResp.versionDelResult = ERROR_CONNECTING_UA_CP;
                  }
                  swDelRespBuff.nodeType = swDelReqPtr->nodeType;
                  bpmDelResult.swMDelResp.nodeType = swDelReqPtr->nodeType;
                  strcpy(swDelRespBuff.delVersion,swDelReqPtr->delVersion);
                  strcpy(bpmDelResult.swMDelResp.delVersion,swDelReqPtr->delVersion);
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_DEL_RESP..");
                  cfgStubSendMessage(&swDelRespBuff,
                                     sizeof(OamOilCfgSwDelResp),
                                     ENT_OAM_OIL,
                                     OAM_OIL_CFG_SW_DEL_RESP,
                                     0);
                  cfgStubSendMessage(&bpmDelResult,
                                     sizeof(OamOilCfgInfoDelResult),
                                     ENT_OAM_OIL,
                                     OAM_OIL_CFG_INFO_DEL_VERSION_RESULT,
                                     0);
                  break;
               }
                        /*BSC CS4.0 : Init Changes starts*/
            case OAMS_CFG_OIL_BPM_DB_INITIALIZED:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_BPM_DB_INITIALIZED from Cfg..");
               LOG_PRINT(LOG_INFO,"Sending  OAM_OIL_CFG_SYSTEM_TYPE_DETAILS from Cfg..");
               cleanSystemTypeDetails();   
               sendSystemTypeDetails();
               LOG_PRINT(LOG_INFO,"Sending  OAM_OIL_CFG_CHASIS_FRAME_DETAILS from Cfg..");
               cleanChasisFrameDetails();
               sendChasisFrameDetails();
               LOG_PRINT(LOG_INFO,"Sending  OAM_OIL_CFG_TRUNK_PORT_DETAILS from Cfg..");
               cleanTrunkPortDetails();
               sendTrunkPortDetails();
               LOG_PRINT(LOG_INFO,"Sending  OAM_OIL_CFG_SYSTEM_CLOCK_DETAILS from Cfg..");
               cleanSystemClockDetails();
               sendSystemClockDetails();
               LOG_PRINT(LOG_INFO,"Sending  OAM_OIL_CFG_EIC_CARD_DETAILS1 from Cfg..");
               cleanEicCardsDetails();
               sendEic1CardDetails();
               LOG_PRINT(LOG_INFO,"Sending  OAM_OIL_CFG_EIC_CARD_DETAILS2 from Cfg..");
               sendEic2CardDetails();
               LOG_PRINT(LOG_INFO,"Sending  OAM_OIL_CFG_ICC_CARD_DETAILS(Self) from Cfg..");
               cleanIccCardsDetails();
               sendIccSelfCardDetails();
               LOG_PRINT(LOG_INFO,"Sending  OAM_OIL_CFG_ICC_CARD_DETAILS(Mate) from Cfg..");
               sendIccMateCardDetails();
               LOG_PRINT(LOG_INFO,"Sending  OAM_OIL_CFG_DSP_OBJ_DETAILS from Cfg..");
               cleanDspObjDetails();
               sendDspObjDetails();
               break;
            }
            case OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ:
            {

               OamsCfgOilE1EnableReq *oamsCfgOilE1EnableReq = (OamsCfgOilE1EnableReq *)rcvPtr;

               sendTrunkStateChangeResp(oamsCfgOilE1EnableReq);
               break;
            }
                        /*BSC CS4.0 : Init Changes Ends*/

            default:
               {
                  LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",
                            (((SysHdr*) rcvPtr)->msgType)
                           );
                  break;
               }
         }//switch
         return 0;
}   

