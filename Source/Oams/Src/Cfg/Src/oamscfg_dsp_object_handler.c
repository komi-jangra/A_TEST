/********************************File Header ***********************
File Name        : oamscfg_dsp_object_handler.c
Purpose          : This file contains function defintions for DSP Object Handling.
Project          : BSC
Subsystem        : OAMS
Author           : Gaurav Jain 
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h> 

/********************************* Function  Header********************************
Function Name:       sendDspLockReqToDsph()
Parameters:          dspId,cause 
Return type:         void
Purpose:             To Send Dsp Lock Req message to DSPH.  
Other Note:
 ************************************************************************************/

I_Void sendDspLockReqToDsph(I_U8 frameId, I_U8 slotId, I_U8 dspId, I_U8 reason)
{
  OamsCfgDsphDspLockReq sndMsgBuff;
  sndMsgBuff.frameId = frameId;
  sndMsgBuff.slotId = slotId;
  sndMsgBuff.dspId = dspId;
  sndMsgBuff.reason = reason;	
  gDspData[dspId].dspState = lockInProgress;
  cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgDsphDspLockReq), 
					ENT_OAMS_DSPH, OAMS_CFG_DSPH_DSP_LOCK_REQ, 0);	
  return;		
}//sendDspLockReqToDsph

/********************************* Function  Header********************************
Function Name:       sendDspUnlockReqToDsph()
Parameters:          dspId,cause 
Return type:         void
Purpose:             To Send Dsp Lock Req message to DSPH.  
Other Note:
 ************************************************************************************/

I_Void sendDspUnlockReqToDsph(I_U8 frameId, I_U8 slotId, I_U8 dspId, I_U8 reason)
{
  OamsCfgDsphDspUnlockReq sndMsgBuff;
  sndMsgBuff.frameId = frameId;
  sndMsgBuff.slotId = slotId;
  sndMsgBuff.dspId = dspId;
  sndMsgBuff.reason = reason;	
  gDspData[dspId].dspState = unlockInProgress;
  cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgDsphDspUnlockReq), 
					ENT_OAMS_DSPH, OAMS_CFG_DSPH_DSP_UNLOCK_REQ, 0);	
  return;		
}

/********************************* Function  Header********************************
Function Name:       sendDspResetReqToDsph()
Parameters:          dspId,cause 
Return type:         void
Purpose:             To Send Dsp Lock Req message to DSPH.  
Other Note:
 ************************************************************************************/

I_Void sendDspResetReqToDsph(DspInfoTableApi *dspInfoPtr)
{
  OamsCfgDsphDspResetReq sndMsgBuff;
  sndMsgBuff.frameId = dspInfoPtr->chasisFrameId;
  sndMsgBuff.slotId = dspInfoPtr->slotId;

	if(sndMsgBuff.slotId == ICCSELFCARD ||
			sndMsgBuff.slotId == ICCMATECARD)
  {	
  	sndMsgBuff.cardType = CARD_TYPE_ICC;
	}
	else
  {
  	sndMsgBuff.cardType = CARD_TYPE_EIC;
	}
  sndMsgBuff.dspId = dspInfoPtr->dspId;
  gDspData[dspInfoPtr->dspId].dspState = resetInProgress;
  cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgDsphDspResetReq), 
					ENT_OAMS_DSPH, OAMS_CFG_DSPH_DSP_RESET_REQ, 0);	
  return;		
}

/********************************* Function  Header********************************
Function Name:       setDspTable()
Parameters:          void
Return type:         void
Purpose:             To  handle BSC_API_SET_DSPTABLE message for Lock/Unlock/Reset DSP.
Other Note:
 ************************************************************************************/

void   setDspTable()
{ 
  DspInfoTableApi *dspObjPtr; /* Pointer to point Reveved Message.*/
  sCmMsg* receivedCmMsgPtr = 0;
  receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
  dspObjPtr = (DspInfoTableApi *)( ((I_U8 *)receivedCmMsgPtr)+sizeof(sCmMsg)); /* pointing to the recieved message*/
  /*Pointers to Point the Database objects..*/
  DspInfoTableApi *dspObjFromDbPtr;/*To point the e1 Object from DB.*/
  DspStatusTableApi *dspStsTblPtr;
  DspInfoTableIndices dspTableIndices;
  DspStatusTableIndices dspStsTblIndices;
  
  /*read DspTable.. */
  dspTableIndices.chasisFrameId = dspObjPtr->chasisFrameId ;
  dspTableIndices.slotId = dspObjPtr->slotId ;
  dspTableIndices.dspId = dspObjPtr->dspId;

  dspStsTblIndices.chasisFrameId = dspObjPtr->chasisFrameId ;
  dspStsTblIndices.slotId = dspObjPtr->slotId ;
  dspStsTblIndices.dspId = dspObjPtr->dspId;

  if (getDspInfoTable(&dspTableIndices,&dspObjFromDbPtr) != CLIB_SUCCESS)
  {
      LOG_PRINT(LOG_CRITICAL,"DspObjHandler: readDspTable() Failed");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
  }
	  
  if (getDspStatusTable(&dspStsTblIndices,&dspStsTblPtr) != CLIB_SUCCESS)
  {
      LOG_PRINT(LOG_CRITICAL,"DspObjHandler: readDspTable() Failed");
      free(dspObjFromDbPtr);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
  }
	  
  if(dspStsTblPtr->physicalPresenceState == NOT_PRESENT)
  {
     LOG_PRINT(LOG_CRITICAL,"setDspTable: DSP is not PRESENT physically");
     free(dspObjFromDbPtr);
     free(dspStsTblPtr);
     cfgSendNackToCm(CM_ERR_DSP_PHYSICALLY_NOT_PRESENT);
     return;
  }

	switch(dspObjFromDbPtr->adminState)
	{
		case UNLOCKED:
			if(LOCK == dspObjPtr->adminState)
			{
				sendDspLockReqToDsph(dspObjPtr->chasisFrameId, dspObjPtr->slotId, 
					dspObjPtr->dspId,OAMS_RSN_OPERATORINITIATED);
			}
			else if(DSP_RESET == dspObjPtr->dspReset)
			{
      	cfgSendNackToCm(CM_ERR_DSP_UNLOCKED);
			}
			else if(UNLOCKED == dspObjPtr->adminState)
			{
      	cfgSendNackToCm(CM_ERR_DSP_ALREADY_UNLOCKED);
			}
      else
      {
         cfgSendNackToCm(CM_ERR_DSP_INVALID_REQUEST);
      }
		break;

		case LOCKED:
			if(UNLOCK == dspObjPtr->adminState)
			{
				sendDspUnlockReqToDsph(dspObjPtr->chasisFrameId, dspObjPtr->slotId,
          dspObjPtr->dspId,OAMS_RSN_OPERATORINITIATED);
			}
			else if(DSP_RESET == dspObjPtr->dspReset)
			{
				sendDspResetReqToDsph(dspObjPtr);
			}
			else if(LOCKED == dspObjPtr->adminState)
			{
      	cfgSendNackToCm(CM_ERR_DSP_ALREADY_LOCKED);
			}
      else
      {
         cfgSendNackToCm(CM_ERR_DSP_INVALID_REQUEST);
      }

		break;

		default:
			LOG_PRINT(MAJOR,"Invalid Dsp AdminState in Db for dspId(%d)",dspObjFromDbPtr->dspId);
      cfgSendNackToCm(CM_ERR_DB_FAILED);
		break;
	}


}//setDspTable

/********************************* Function  Header********************************
Function Name:       setDspObjectHandler()
Parameters:          void
Return type:         void
Purpose:             To Handle Dsp Enable/Disable Procedure
Other Note:
 ************************************************************************************/
void setDspObjectHandler()
{
   DspInfoTableApi *receivedMsgPtr = ( DspInfoTableApi * )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   DspInfoTableApi*     dspInfoTableApiPtr     = PNULL;
   DspStatusTableApi*   dspStsPtr        = PNULL;
   DspInfoTableIndices  apiDspInfoIndex        = {0} ;
   DspStatusTableIndices dspStsIndex = {0};
   I_S32                  ret                      = 1; 
   I_Bool                 flag                     = FALSE;
   I_U32 cardOperState = 0;

   LOG_PRINT(LOG_INFO," In DspInfoTableHandler");

   apiDspInfoIndex.chasisFrameId   = receivedMsgPtr->chasisFrameId;
   apiDspInfoIndex.slotId          = receivedMsgPtr->slotId;
   apiDspInfoIndex.dspId           = receivedMsgPtr->dspId;


   if(gDspData[apiDspInfoIndex.dspId].dspState != locked && gDspData[apiDspInfoIndex.dspId].dspState != unlocked)
   {
      LOG_PRINT(LOG_INFO," Received dspId %d  OAM procedure in progress:: SET_DSP_API PROCEDURE ENDS",apiDspInfoIndex.dspId);
      cfgSendNackToCm(CM_ERR_OAM_OPERATION_IN_PROGRESS);
      return;   
   }

   ret = getDspInfoTable(&apiDspInfoIndex, &dspInfoTableApiPtr);

   // Check if received dspId is in Db or not  
   if (PNULL == dspInfoTableApiPtr)
   {
      LOG_PRINT(LOG_INFO," Received dspId not present in DB :: SET_DSP_API PROCEDURE ENDS");
      cfgSendNackToCm(CM_ERR_DSP_ID_NOT_PRESENT_IN_DB);
      return;   
   }
   else // Store the data fetched from DB for further use in the flow
   {

      // Check if received dspId details are same as in Database
      flag = compareRcvdMsgAndDbEntry((void*)receivedMsgPtr,(void*)dspInfoTableApiPtr,sizeof(DspInfoTableApi));
      if( FALSE == flag )
      {
         LOG_PRINT(LOG_INFO," No DspInfo parameter is being changed");
         cfgSendAckToCm(CM_SUCCESS);
         free(dspInfoTableApiPtr);
         return;
      }
   }

   dspStsIndex.chasisFrameId   = receivedMsgPtr->chasisFrameId;
   dspStsIndex.slotId          = receivedMsgPtr->slotId;
   dspStsIndex.dspId           = receivedMsgPtr->dspId;

   ret = getDspStatusTable(&dspStsIndex,&dspStsPtr); 

   if (PNULL == dspStsPtr)
   {
      LOG_PRINT(LOG_INFO," Received dspId not present in DB :: SET_DSP_API PROCEDURE ENDS");
      cfgSendNackToCm(CM_ERR_DSP_ID_NOT_PRESENT_IN_DB);
      free(dspInfoTableApiPtr);
      return;   
   }
   else
   {
      if(dspStsPtr->physicalPresenceState == NOT_PRESENT) 
      {
         LOG_PRINT(LOG_INFO," Received dspId not present in System ::SET_DSP_API PROCEDURE ENDS");
         cfgSendNackToCm(CM_ERR_DSP_PHYSICALLY_NOT_PRESENT); 
         free(dspStsPtr);
         free(dspInfoTableApiPtr);
         return;   
      } 
      free(dspStsPtr);
   }
   // Check if RO parameter are being modified
   if( receivedMsgPtr->dspType != dspInfoTableApiPtr->dspType || \
        receivedMsgPtr->trauResource != dspInfoTableApiPtr->trauResource )
   {
      LOG_PRINT(LOG_INFO," RO parameter is being modified::SET_DSP_INFO PROCEDURE ENDS");
      cfgSendNackToCm(CM_ERR_DSP_INVALID_REQUEST);
      free(dspInfoTableApiPtr);
      return;   
   }


   /*Check Bss Admin State*/
   if( gBssState == lockInProgress)
   {
      cfgSendNackToCm(CM_ERR_BSS_LOCK_IN_PROGRESS);
      free(dspInfoTableApiPtr);
      return;   
   }

   if( gBssState == unlockInProgress )
   {
      cfgSendNackToCm(CM_ERR_BSS_UNLOCK_IN_PROGRESS);
      free(dspInfoTableApiPtr);
      return;   
   }
  
    /*BSC-R2.5.5 Diagnostics changes Starts*/
    ret = getCardOperState(receivedMsgPtr->chasisFrameId,receivedMsgPtr->slotId,&cardOperState);
    if(ret != CLIB_SUCCESS)
    {
       LOG_PRINT(DEBUG,"getCardOperState failed err:%d", ret); 
       cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
       free(dspInfoTableApiPtr);
       return;   
    }
    else
    {
       if(cardOperState == CARDSTATE_DIAGNOSTIC) 
       {
          LOG_PRINT(DEBUG,"action can not be performed as card in DIAGNOSTIC state"); 
          cfgSendNackToCm(CM_ERR_DIAGNOS_OPR_IN_PROGRESS);
          free(dspInfoTableApiPtr);
          return;   
       }
    }

    if(I_TRUE == isDiagInProgressForDsp(receivedMsgPtr->chasisFrameId,
                      receivedMsgPtr->slotId,receivedMsgPtr->dspId))
    {
       LOG_PRINT(DEBUG,"action can not be performed as dsp in DIAGNOSTIC state"); 
       cfgSendNackToCm(CM_ERR_DIAGNOS_OPR_IN_PROGRESS);
       return;   
    }
    /*BSC-R2.5.5 Diagnostics changes Ends*/

   /* Check if the request is for change in Admin State only */
   if (( dspInfoTableApiPtr != PNULL) && 
         ( receivedMsgPtr->adminState != dspInfoTableApiPtr->adminState ) )
   {
      /* If any other parameter is being modified, then NACK the request */
      if( receivedMsgPtr->dspReset != dspInfoTableApiPtr->dspReset) 
      {
         LOG_PRINT(LOG_INFO," Too many RW parameters being modified :: Lock/Unlock DspInfo");
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         free(dspInfoTableApiPtr);
         return;   
      }
      else /* Proceed with the procedure for change in Admin state */
      {
         setDspTable();
      }

   }
   else if (( dspInfoTableApiPtr != PNULL) && 
         ( receivedMsgPtr->dspReset != dspInfoTableApiPtr->dspReset ) )
   {
      setDspTable();
   }
   free(dspInfoTableApiPtr);
}//setDspObjectHandler


/********************************* Function  Header********************************
Function Name:       dspBootAlarmHandler()
Parameters:          void
Return type:         void
Purpose:             To Handle Dsp Boot Alarm
Other Note:
 ************************************************************************************/
void dspBootAlarmHandler()
{
   OamOilCfgDspBootInfo * receivePtr = (OamOilCfgDspBootInfo *)gCfgMsgBuf;
   I_U8 j=0;/*changes for R2.8 */

#if 0  
   DspInfoTableApi*     dspInfoTableApiPtr     = PNULL;
   DspStatusTableApi*   dspStsTableApiPtr        = PNULL;
   DspInfoTableIndices  dspInfoIndex        = {0} ;
   DspStatusTableIndices dspStsIndex = {0};
   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
   I_S32                  ret                      = 1; 
#endif
   sDspObjInfo dspBootInfo;
   
   dspBootInfo.frameID =  receivePtr->dspNodeInfo.chasisFrameId;
   dspBootInfo.slotID =  receivePtr->dspNodeInfo.dspSlotId;
   dspBootInfo.dspId =  receivePtr->dspNodeInfo.dspId;
   dspBootInfo.isDspPresent =  BPM_TRUE;
   dspBootInfo.operationalState =  BPM_DSP_ENABLED;
   //memcpy(&(dspBootInfo.dspInfo.bscInfo),&(receivePtr->dspInfo),sizeof(OamOilCfgDspInfo));
   dspBootInfo.dspInfo.bscInfo.dspId = receivePtr->dspInfo.dspId ;
   dspBootInfo.dspInfo.bscInfo.bootTestResult = receivePtr->dspInfo.bootTestResult ;
   dspBootInfo.dspInfo.bscInfo.failureInfo = receivePtr->dspInfo.failureInfo ;
   dspBootInfo.dspInfo.bscInfo.trauResource_core0 = receivePtr->dspInfo.trauResource_core0 ;
   dspBootInfo.dspInfo.bscInfo.abisTsResource_core0 = receivePtr->dspInfo.abisTsResource_core0 ;
   dspBootInfo.dspInfo.bscInfo.trauResource_core1 = receivePtr->dspInfo.trauResource_core1 ;
   dspBootInfo.dspInfo.bscInfo.abisTsResource_core1 = receivePtr->dspInfo.abisTsResource_core1 ;
   dspBootInfo.dspInfo.bscInfo.trauResource_core2 = receivePtr->dspInfo.trauResource_core2 ;
   dspBootInfo.dspInfo.bscInfo.abisTsResource_core2 = receivePtr->dspInfo.abisTsResource_core2 ;
   dspBootInfo.dspInfo.bscInfo.trauResource_core3 = receivePtr->dspInfo.trauResource_core3 ;
   dspBootInfo.dspInfo.bscInfo.abisTsResource_core3 = receivePtr->dspInfo.abisTsResource_core3 ;
   dspBootInfo.dspInfo.bscInfo.activeChannels = receivePtr->dspInfo.activeChannels;
   dspBootInfo.dspInfo.bscInfo.swVerInfo[0] = receivePtr->dspInfo.swVerInfo[0];
   dspBootInfo.dspInfo.bscInfo.swVerInfo[1] = receivePtr->dspInfo.swVerInfo[1];
   dspBootInfo.dspInfo.bscInfo.swVerInfo[2] = receivePtr->dspInfo.swVerInfo[2];
   dspBootInfo.dspInfo.bscInfo.swIdInfo[0] = receivePtr->dspInfo.swIdInfo[0];
   dspBootInfo.dspInfo.bscInfo.swIdInfo[1] = receivePtr->dspInfo.swIdInfo[1];
   dspBootInfo.dspInfo.bscInfo.swIdInfo[2] = receivePtr->dspInfo.swIdInfo[2];
   for(j=0;j<=MAX_CORE_PER_DSP;j++)/*changes for R2.8 */
   {  
   dspBootInfo.dspInfo.bscInfo.dspCoreIpAddr[j].addr1 = receivePtr->dspInfo.dspCoreIpAddr[j].AAA;
   dspBootInfo.dspInfo.bscInfo.dspCoreIpAddr[j].addr2 = receivePtr->dspInfo.dspCoreIpAddr[j].BBB;
   dspBootInfo.dspInfo.bscInfo.dspCoreIpAddr[j].addr3 = receivePtr->dspInfo.dspCoreIpAddr[j].CCC;
   dspBootInfo.dspInfo.bscInfo.dspCoreIpAddr[j].addr4 = receivePtr->dspInfo.dspCoreIpAddr[j].DDD;
   }
   memcpy(&(gDspInfo[receivePtr->dspInfo.dspId]),&dspBootInfo,sizeof(sDspObjInfo));
   
   /*Fix for Mantis:10912 Starts*/
   if((gCfgState == CFG_READY) ||(gCfgState == CFG_BPM_SW_QUERY) )
   {
      updateDspObjDetails(&dspBootInfo,1);  
   } 
   else if ( (dspBootInfo.slotID !=ICCSELFCARD) && (dspBootInfo.slotID !=ICCMATECARD)&&
         (gDspBootInfoSent[dspBootInfo.dspId] !=1)) /*Changes done for R2.8*/
   {
    LOG_PRINT(DEBUG,"calling updateDspObjDetails for dspId %d ,CFG is in %d state", dspBootInfo.dspId,gCfgState);
      updateDspObjDetails(&dspBootInfo,1);  
   }
   else
   {
    LOG_PRINT(DEBUG,"not sending boot info for dspId %d as CFG is in %d state", dspBootInfo.dspId,gCfgState);
   }  
#if 0
   dspInfoIndex.chasisFrameId  =  receivePtr->dspNodeInfo.chasisFrameId;
   dspInfoIndex.slotId         =  receivePtr->dspNodeInfo.dspSlotId;
   dspInfoIndex.dspId          = receivePtr->dspNodeInfo.dspId;
  
   dspStsIndex.chasisFrameId  =  receivePtr->dspNodeInfo.chasisFrameId;
   dspStsIndex.slotId         = receivePtr->dspNodeInfo.dspSlotId;
   dspStsIndex.dspId          =  receivePtr->dspNodeInfo.dspId;

   LOG_PRINT(LOG_DEBUG,"INFO_DSP_BOOT Alarm rcvd for Frameid(%d) slotId(%d) dspId(%d)",
         dspInfoIndex.chasisFrameId,dspInfoIndex.slotId,dspInfoIndex.dspId);

   LOG_PRINT(DEBUG,"swVerInfo[0]: %d", receivePtr->dspInfo.swVerInfo[0]);
   LOG_PRINT(DEBUG,"swVerInfo[1]: %d", receivePtr->dspInfo.swVerInfo[1]);
   LOG_PRINT(DEBUG,"swVerInfo[2]: %d", receivePtr->dspInfo.swVerInfo[2]);

   LOG_PRINT(DEBUG,"swIdInfo[0]: %d", receivePtr->dspInfo.swIdInfo[0]);
   LOG_PRINT(DEBUG,"swIdInfo[1]: %d", receivePtr->dspInfo.swIdInfo[1]);
   LOG_PRINT(DEBUG,"swIdInfo[2]: %d", receivePtr->dspInfo.swIdInfo[2]);

   if((gCfgState == CFG_READY) ||(gCfgState == CFG_BPM_SW_QUERY) )
   {
      LOG_PRINT(DEBUG,"sending boot info as CFG is in %d state", gCfgState);
      if(getDspStatusTable(&dspStsIndex,&dspStsTableApiPtr) != CLIB_SUCCESS)
      {
          LOG_PRINT(LOG_MAJOR,"getDspStsTbl Failed for dspId(%d)",dspStsIndex.dspId );   
          return; 
      }

      if(dspStsTableApiPtr->physicalPresenceState == NOT_PRESENT)
      {
        dspStsTableApiPtr->physicalPresenceState = PRESENT;

        //Send Dsp Available Sts to Dsph
        sendDsphAvailSts(dspStsTableApiPtr); 
     
        //Send Bss Admin State for dspId 
        sendDsphBssAdminStateInd(dspStsTableApiPtr); 

        free(dspStsTableApiPtr);
      }
    
      if(getDspInfoTable(&dspInfoIndex,&dspInfoTableApiPtr) != CLIB_SUCCESS)
      {
          LOG_PRINT(LOG_MAJOR,"getDspInfoTbl Failed for dspId(%d)",dspInfoIndex.dspId );   
          return; 
      }
      
      //dspInfoTableApiPtr->dspType = *((I_U32 *)(receivePtr->dspInfo.swIdInfo));
      dspInfoTableApiPtr->dspType  = receivePtr->dspInfo.swIdInfo[0];
      dspInfoTableApiPtr->dspType |= (receivePtr->dspInfo.swIdInfo[1] << 4);
      dspInfoTableApiPtr->dspType |= receivePtr->dspInfo.swIdInfo[2] ;

      dspInfoTableApiPtr->trauResource = receivePtr->dspInfo.trauResource_core0 + 
                                         receivePtr->dspInfo.trauResource_core1 +
                                         receivePtr->dspInfo.trauResource_core2 +
                                         receivePtr->dspInfo.trauResource_core3 ;

     if(updateDspInfoTable(dspInfoTableApiPtr) != CLIB_SUCCESS)
     {
        LOG_PRINT(LOG_CRITICAL,"updateDspObjDetails: DspObj Details updtion failed dspid(%d)!!!",  
           dspInfoTableApiPtr->dspId);
        free(dspInfoTableApiPtr);
        return;
     } 
   
     sendDsphBootInfo(&(dspBootInfo));
     free(dspInfoTableApiPtr); 
      
   }//if( gCfgState == CFG_READY)
   else
   {
      LOG_PRINT(DEBUG,"not sending boot info as CFG is in %d state", gCfgState);
   }

   /*Send Alarm To OMC*/
   sendDspBootInfoAlarm(); 
#endif
   /*Fix for Mantis:10912 Ends*/
}//dspBootAlarmHandler

/********************************* Function  Header********************************
Function Name:       dspDownAlarmHandler()
Parameters:          void
Return type:         void
Purpose:             To Handle Dsp Down Alarm
Other Note:
 ************************************************************************************/
void dspDownAlarmHandler()
{
   OamsCfgDsphDspDownInfo sndMsgBuff;
   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};

   sndMsgBuff.frameId        = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key1;
   sndMsgBuff.slotId         = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2;
   sndMsgBuff.dspId          = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key3;
   sndMsgBuff.cause          = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4;

   gDspBootInfoSent[sndMsgBuff.dspId] = 0;
 
   LOG_PRINT(DEBUG,"gDspBootInfoSent for DspId:%d is set as 0",sndMsgBuff.dspId);
      
   if((gCfgState == CFG_READY) ||(gCfgState == CFG_BPM_SW_QUERY) )
   {
      LOG_PRINT(LOG_DEBUG,"InfoBpmDspDown rcvd for frameId(%d) slotId(%d) dspId(%d) cause(%d) subCause(%d)",
                   sndMsgBuff.frameId,sndMsgBuff.slotId,sndMsgBuff.dspId,
                   sndMsgBuff.cause, (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->info1 );

      cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgDsphDspDownInfo),
         ENT_OAMS_DSPH, OAMS_CFG_DSPH_DSP_DOWN_INFO, 0);
  
      memcpy(&OamsCfgAfhSysAlarmBuff.sysAlarm,(gCfgMsgBuf+sizeof(SysHdr)),sizeof(SysAlarm));

      FillObjTypeFromSlotId(sndMsgBuff.slotId,
                                 OamsCfgAfhSysAlarmBuff.sysAlarm.info3  );

      OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = 
                  sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,
                            "Info DspDown ChasisId[%d],SlotId[%d],dspId[%d],cause[%d]",
                             sndMsgBuff.frameId,sndMsgBuff.slotId,
                             sndMsgBuff.dspId,sndMsgBuff.cause);

      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

   }//if( gCfgState == CFG_READY)
   else
   {
      gDspInfo[sndMsgBuff.dspId].operationalState = BPM_DSP_DISABLED;
   }
}//dspDownAlarmHandler

/********************************* Function  Header********************************
Function Name:       dspResetFailAlarmHandler()
Parameters:          void
Return type:         void
Purpose:             To Handle Dsp Reset Fail Alarm
Other Note:
 ************************************************************************************/
void dspResetFailAlarmHandler()
{

   OamsCfgDsphDspResetFailInfo sndMsgBuff;
   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};

   sndMsgBuff.frameId        = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key1;
   sndMsgBuff.slotId         = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2;
   sndMsgBuff.dspId          = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key3;
   sndMsgBuff.cause          = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4;

   gDspBootInfoSent[sndMsgBuff.dspId] = 0;

   if((gCfgState == CFG_READY) ||(gCfgState == CFG_BPM_SW_QUERY) )
   {
      LOG_PRINT(LOG_DEBUG,"InfoBpmDspRestFail rcvd for frameId(%d) slotId(%d) dspId(%d) cause(%d)",
                  sndMsgBuff.frameId,sndMsgBuff.slotId,sndMsgBuff.dspId,
                  sndMsgBuff.cause  );

      cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgDsphDspResetFailInfo),
         ENT_OAMS_DSPH, OAMS_CFG_DSPH_RESET_FAIL_INFO, 0);

      memcpy(&OamsCfgAfhSysAlarmBuff.sysAlarm,(gCfgMsgBuf+sizeof(SysHdr)),sizeof(SysAlarm));

      FillObjTypeFromSlotId(sndMsgBuff.slotId,
                                 OamsCfgAfhSysAlarmBuff.sysAlarm.info3  );

      OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = 
                  sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,
                            "Info DspResetFailure ChasisId[%d],SlotId[%d],dspId[%d],cause[%d]",
                             sndMsgBuff.frameId,sndMsgBuff.slotId,
                             sndMsgBuff.dspId,sndMsgBuff.cause);
      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }//if( gCfgState == CFG_READY)
   else
   {
      gDspInfo[sndMsgBuff.dspId].operationalState = BPM_DSP_DISABLED;
   }
}//dspResetFailAlarmHandler

