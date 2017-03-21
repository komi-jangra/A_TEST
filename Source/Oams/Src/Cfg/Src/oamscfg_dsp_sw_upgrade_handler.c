/************************************************************* File Header ***
File Name      : oamscfg_dsp_sw_upgrade_handler.c
Purpose        : This file contains function defintions required for handling 
								 of DSP SW Download and Activation.
Project        : BSC-R2.0
Subsystem      : OAMS 
Author         : R2.0 Team 
CSCI id        :
Version        :
 ******************************************************************** End ***/

#include "oamscfg_includes.h"

#define convertNodeType(nodeType,intValue) \
if(intValue == SYS_NODE_TYPE_BSC) \
strcpy(nodeType,"BSC"); \
else if(intValue == SYS_NODE_TYPE_EIC) \
strcpy(nodeType,"EIC"); \
else if(intValue == SYS_NODE_TYPE_BIC) \
strcpy(nodeType,"BIC"); \
else if(intValue == SYS_NODE_TYPE_TRX) \
strcpy(nodeType,"TRX"); \
else if(intValue == SYS_NODE_TYPE_DSP) \
strcpy(nodeType,"DSP");

extern I_Void sendRequestForEicDspAvailableReleases();
extern I_Void sendRequestForDspAvailableReleases();
/******************************* Function  Header*****************************
   Function Name : dspSwDeletionRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw deletion response recieved from OIL
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void dspSwDeletionRespHandler()
{
   OamOilCfgSwDelResp *swDelRespPtr = NULL;
   OamOilCfgNodeInfo *nodeInfo = NULL;
   OamOilCfgInfoDelResult *bpmSwDel = (OamOilCfgInfoDelResult *)gCfgMsgBuf;
   nodeInfo =  (OamOilCfgNodeInfo*)(&(bpmSwDel->nodeInfo));
   swDelRespPtr = (OamOilCfgSwDelResp*)(&(bpmSwDel->swMDelResp));

   OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
   SwMNodeTableApi *swMNodeTableDbPtr = NULL;
   SwMTableIndices sApiSwMTableIndices;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   I_U32 dspId[MAX_DSP];
   I_U8 noOfDsp;
   I_U8 string[MAX_STRING_LENGTH];
   I_U32 index = ZERO;
   I_U8 type[4];

   LOG_PRINT(LOG_INFO,"Recieved Deletion Response");
   LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swDelRespPtr->delVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",swDelRespPtr->nodeType);
   LOG_PRINT(LOG_INFO,"FrameId: %d ",swDelRespPtr->frameId);
   LOG_PRINT(LOG_INFO,"SlotId: %d ",swDelRespPtr->slotId);
   LOG_PRINT(LOG_INFO,"Result: %d ",swDelRespPtr->versionDelResult);

   sApiSwMTableIndices.nodeType = swDelRespPtr->nodeType;
   sApiSwMTableIndices.chasisFrameId = swDelRespPtr->frameId;
   sApiSwMTableIndices.slotId = swDelRespPtr->slotId;
   strcpy(sApiSwMTableIndices.swVersion,swDelRespPtr->delVersion);

   if (getDspIdFromSwMNodeTable(dspId, &noOfDsp) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getDspId call is getting failed..");
      return;
   }

   if (swDelRespPtr->versionDelResult == DELETE_SUCCESSFUL)
   {
      /*Delete the record of the requested sw version from T2 Table */
      if (deleteSwMTable(&sApiSwMTableIndices) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call is getting failed..");
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"deleteSwMTable Success");

      /*Check if deletion request comes for DSP */
      if (swDelRespPtr->nodeType == SYS_NODE_TYPE_DSP)
      {
        if(swDelRespPtr->slotId == 3 || swDelRespPtr->slotId == 4)
        { 
          for (index=0; index<noOfDsp; index++)
          {
            sApiSwMNodeTableIndices.nodeType = swDelRespPtr->nodeType;
            sApiSwMNodeTableIndices.nodeIdentity = dspId[index];
            sApiSwMNodeTableIndices.chasisFrameId = swDelRespPtr->frameId;
            //sApiSwMNodeTableIndices.slotId = eicId[index];
            if (dspId[index] >1){
              break;
            }
            if(dspId[index] == 0)
            {
              sApiSwMNodeTableIndices.slotId = 3;
            }
            if(dspId[index] == 1)
            {
              sApiSwMNodeTableIndices.slotId = 4;
            }
            if (getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr) != 
                CLIB_SUCCESS)
            {
              LOG_PRINT(LOG_CRITICAL,"getSwMNodeTable DB call Failed");
              return;
            }

            /*Check if deleted version is Inactive Sw Version */
            if (strcmp(swMNodeTableDbPtr->swVersionInactive,
                  swDelRespPtr->delVersion) == ZERO )
            {
              LOG_PRINT(LOG_DEBUG,"Deletion response recieved for Inactive SwVersion");
              if (swMNodeTableDbPtr != NULL)
                free(swMNodeTableDbPtr);
              return;
            }

            /*Update Downloaded Version in SwMNode Table if deleted version is downloaded Version */
            if (strcmp(swMNodeTableDbPtr->swVersionDownloaded,
                  swDelRespPtr->delVersion) == ZERO )
            {
              if (updateVersionDownloadedInSwMNodeTable(sApiSwMNodeTableIndices
                    ,"") != CLIB_SUCCESS)
              {
                LOG_PRINT(LOG_CRITICAL,"updateVersionDownloadedInSwMNodeTable Failed for dspId: %d", dspId[index] );
                if (swMNodeTableDbPtr != NULL)
                  free(swMNodeTableDbPtr);
                return;
              }
              else
                LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success");
            }
            if (swMNodeTableDbPtr != NULL)
              free(swMNodeTableDbPtr);
          }
        }//if icc card
        else if(swDelRespPtr->slotId == 5 || swDelRespPtr->slotId == 6)
        { 
          for (index=0; index<noOfDsp; index++)
          {
            sApiSwMNodeTableIndices.nodeType = swDelRespPtr->nodeType;
            sApiSwMNodeTableIndices.nodeIdentity = dspId[index];
            sApiSwMNodeTableIndices.chasisFrameId = swDelRespPtr->frameId;
            //sApiSwMNodeTableIndices.slotId = eicId[index];
            if (dspId[index] <2){
              continue;
            }
            if((dspId[index] == 2) || (dspId[index] == 3))
            {
              sApiSwMNodeTableIndices.slotId = 5;
            }
            if((dspId[index] == 4) || (dspId[index] == 5))
            {
              sApiSwMNodeTableIndices.slotId = 6;
            }
            if (getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr) != 
                CLIB_SUCCESS)
            {
              LOG_PRINT(LOG_CRITICAL,"getSwMNodeTable DB call Failed");
              return;
            }

            /*Check if deleted version is Inactive Sw Version */
            if (strcmp(swMNodeTableDbPtr->swVersionInactive,
                  swDelRespPtr->delVersion) == ZERO )
            {
              LOG_PRINT(LOG_DEBUG,"Deletion response recieved for Inactive SwVersion");
              if (swMNodeTableDbPtr != NULL)
                free(swMNodeTableDbPtr);
              return;
            }

            /*Update Downloaded Version in SwMNode Table if deleted version is downloaded Version */
            if (strcmp(swMNodeTableDbPtr->swVersionDownloaded,
                  swDelRespPtr->delVersion) == ZERO )
            {
              if (updateVersionDownloadedInSwMNodeTable(sApiSwMNodeTableIndices
                    ,"") != CLIB_SUCCESS)
              {
                LOG_PRINT(LOG_CRITICAL,"updateVersionDownloadedInSwMNodeTable Failed for dspId: %d", dspId[index] );
                if (swMNodeTableDbPtr != NULL)
                  free(swMNodeTableDbPtr);
                return;
              }
              else
                LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success");
            }
            if (swMNodeTableDbPtr != NULL)
              free(swMNodeTableDbPtr);
          }
        }//if icc card
      }

      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending Success Alarm: INFO_BPM_DEL_VERSION_SUCCESS");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmSwDel->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel = bpmSwDel->alarmLevel;
      sysAlarmBuff.sysAlarm.alarmReason = swDelRespPtr->versionDelResult;
      convertNodeType(type,swDelRespPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = 
         sprintf(sysAlarmBuff.sysAlarm.infoString,
               "Sw Del for SwVer [%s],NodeType [%s] is Completed at ChasisFrameId [%d],SlotId [%d]",
               swDelRespPtr->delVersion,type,nodeInfo->chasisFrameId,nodeInfo->slotId); 
      cfgSendMessage((I_Void *)&sysAlarmBuff, sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }
   else
   {
      /*Update the swAction value as swDelete in SwM Table */
      if (updateDelStatusInSwMTable(sApiSwMTableIndices,I_FALSE) !=CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"updateDelStatusInSwMTable Failed");
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"updateDelStatusInSwMTable Success");

      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending Failure Alarm: INFO_BPM_DEL_VERSION_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmSwDel->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel = bpmSwDel->alarmLevel;
      sysAlarmBuff.sysAlarm.alarmReason = swDelRespPtr->versionDelResult;
      getStringForSwDelErrorCause(swDelRespPtr->versionDelResult,
            swDelRespPtr->delVersion,swDelRespPtr->nodeType,string,nodeInfo->chasisFrameId,nodeInfo->slotId);
      sysAlarmBuff.sysAlarm.infoStrLen = 
         sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   } 
}
/******************************* Function  Header*****************************
   Function Name : cfgInitDspSwMNodeTable()
Parameters    : None
Return type   : I_Void
Purpose       : Initialize SwMNode Table with the DSP present in the 
system.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void cfgInitDspSwMNodeTable()
{
   SwMNodeTableApi swMNodeTableBuf;
   SwMNodeTableIndices swmNodeTableIndices;
   SwMNodeTableApi *swMNodeTableData = NULL;
   I_U8 dspId[MAX_DSP];
   I_U8 noOfDsp= 0;
   I_U32 idx = ZERO,outCount = 0;
   I_S32 ret = ZERO;
	 I_U16 i;
	 DspInfoTableApi *outDspData,*tmpPtr=NULL;
	 I_U16 outSize;
   I_U32 swStatus, swAction;
   I_U8 chasisFrameId, slotId;
    
   noOfDsp = MAX_DSP;
   
   #if 0
   /*Retrieve Dsp's Ids from DspInfoTable */
	 if (getDspId(dspId,&noOfDsp) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG,"No row present in dspInfoTable");
      return;
   }
	 
	  if(getallDspInfoTable( &outDspData, &outCount, &outSize) != CLIB_SUCCESS)
	   {
	     LOG_PRINT(LOG_CRITICAL,"getDspIdChasisId call is getting failed..");
		   return;
		 }
		 LOG_PRINT(DEBUG,"No Of Dsp returned = %d",noOfDsp);
   #endif
   swAction = SW_NO_ACTION;
   swStatus = SW_NO_LAST_ACTION;
   if (   getActiveIccSlotId( &chasisFrameId, &slotId) == CLIB_SUCCESS ) 
   { 
      swmNodeTableIndices.chasisFrameId =  chasisFrameId;
      swmNodeTableIndices.slotId = slotId;
			swmNodeTableIndices.nodeType = SYS_NODE_TYPE_DSP;
      if(slotId == ICCSELFCARD)        
         swmNodeTableIndices.nodeIdentity = 0; 
      else
         swmNodeTableIndices.nodeIdentity = 1; 
         
      if ( getSwMNodeTable( &swmNodeTableIndices, &swMNodeTableData) == CLIB_SUCCESS )
      {
         LOG_PRINT(LOG_INFO,"cfgInitDspSwMNodeTable: NodeType: %d and NodeIdentity: %d already exists in SwMNodeTable",swmNodeTableIndices.nodeType, swmNodeTableIndices.nodeIdentity);
         swAction = swMNodeTableData->swAction;
         swStatus = swMNodeTableData->swStatus;
      }
   }

   /*Insert 6 record's in SwMNode table for DSP */
   for(idx=0; idx<noOfDsp; idx++)
   {   
      /* changes for card eject case start */
      //tmpPtr = (DspInfoTableApi *)(((I_U8 *)outDspData) + (idx * outSize)); 
      
					LOG_PRINT(DEBUG,"idx = %d",idx);
    PRINT_HEX_DUMP(LOG_DEBUG, &(gDspInfo[idx]), sizeof(sDspObjInfo));
     
     if(gDspInfo[idx].isDspPresent == PRESENT)
      {
          /* changes for card eject case end */
          swMNodeTableBuf.chasisFrameId =  gDspInfo[idx].frameID; 
          swMNodeTableBuf.slotId =  gDspInfo[idx].slotID;
          swMNodeTableBuf.nodeIdentity = gDspInfo[idx].dspId; 
          swMNodeTableBuf.nodeType = SYS_NODE_TYPE_DSP;
          swMNodeTableBuf.e1Num = E1_INVALID;
          swMNodeTableBuf.lapdTs = TS_INVALID;
          sprintf(swMNodeTableBuf.swVersionActive,"%d.%d.%d",gDspInfo[idx].activeDspVer.major,
             gDspInfo[idx].activeDspVer.minor,gDspInfo[idx].activeDspVer.revision	);
					LOG_PRINT(DEBUG,"idx = %d activeDspVer = %s",idx, swMNodeTableBuf.swVersionActive);

          if(gDspInfo[idx].backupDspVer.major != 0)
            sprintf(swMNodeTableBuf.swVersionInactive,"%d.%d.%d",gDspInfo[idx].backupDspVer.major,
               gDspInfo[idx].backupDspVer.minor,gDspInfo[idx].backupDspVer.revision	);
          else
            strcpy(swMNodeTableBuf.swVersionInactive,"");
					LOG_PRINT(DEBUG,"idx = %d activeDspVer = %s",idx, swMNodeTableBuf.swVersionInactive);

          if(gDspInfo[idx].downloadDspVer.major != 0)
             sprintf(swMNodeTableBuf.swVersionDownloaded,"%d.%d.%d",gDspInfo[idx].downloadDspVer.major,
                gDspInfo[idx].downloadDspVer.minor,gDspInfo[idx].downloadDspVer.revision	);
          else
            strcpy(swMNodeTableBuf.swVersionDownloaded,"");
					LOG_PRINT(DEBUG,"idx = %d activeDspVer = %s",idx, swMNodeTableBuf.swVersionDownloaded);
               
          strcpy(swMNodeTableBuf.swVersionNew,"");
          swMNodeTableBuf.swAction = swAction;
          swMNodeTableBuf.swStatus = swStatus;

              
          if (updateSwMNodeTable(&swMNodeTableBuf) != CLIB_SUCCESS)
          {
              LOG_PRINT(DEBUG,"updateSwMNodeTable failed for NotPresent dspId:%d",
              swmNodeTableIndices.nodeIdentity);
             /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
             /* if (insertSwMNodeTable(&swMNodeTableBuf) != CLIB_SUCCESS)
              {
                    LOG_PRINT(LOG_CRITICAL,"insertSwMNodeTable DB call Failed in function cfgInitDspSwMNodeTable");
                     return;
              }
              else
              {
                LOG_PRINT(LOG_INFO,"insertSwMNodeTable Successfull");
              }//if insert success*/
             /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
          }//if update not success
      }//if present
      else
      {
          swmNodeTableIndices.chasisFrameId =  gDspInfo[idx].frameID;
          swmNodeTableIndices.slotId =  gDspInfo[idx].slotID;
          swmNodeTableIndices.nodeIdentity = gDspInfo[idx].dspId; 
					swmNodeTableIndices.nodeType = SYS_NODE_TYPE_DSP;
          //swmNodeTableIndices.nodeIdentity = dspId[idx];
          //swmNodeTableIndices.slotId = slotId;
					LOG_PRINT(DEBUG,"getSwmNodeTable For nodeIdentity");
          if ( getSwMNodeTable( &swmNodeTableIndices, &swMNodeTableData) == CLIB_SUCCESS )
          {
             LOG_PRINT(LOG_INFO,"cfgInitDspSwMNodeTable: NodeType: %d and NodeIdentity: %d already exists in SwMNodeTable",swmNodeTableIndices.nodeType, swmNodeTableIndices.nodeIdentity);
             if(deleteSwMNodeTable(&swmNodeTableIndices) != CLIB_SUCCESS)
             {
                 LOG_PRINT(DEBUG,"deleteSwMNodeTable failed for NotPresent dspId:%d",
                  swmNodeTableIndices.nodeIdentity);
             }
          }
      } 
   }//for
}
/******************************* Function  Header*****************************
Function Name : dspDelSwMTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles DSP software deletion procedure
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void dspDelSwMTableHandler()
{
  SwMTableApi *swMTableDbPtr =NULL;
  SwMTableApi *receiveMsgPtr =NULL;
  SwMNodeTableApi *swMNodeDbPtr =NULL;
  SwMTableIndices SwMTableIndex;
  SwMOfferTableApi *swMOfferBuff = NULL;
  I_U32 outCount = ZERO;
  I_U16 outSize = ZERO;
  I_U8 slotId;
  I_U8 chasisFrameId;
  I_U32 dspId[MAX_DSP];
  I_U8 noOfDsp = ZERO;
  I_S32 ret = ONE;
  I_U32 tokenNum;
  I_U32 token[MAX_DIGITS];
  I_U32 errCause;
  I_U32 index = ZERO;
  I_S32 actionInProgress = I_FALSE;
  I_U32 nodeType = 0, failType =0, swStatus = 0;


  receiveMsgPtr = (SwMTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

  /* In case of Dsp Activation ActiveICC frameId and SlotId will be used */
  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
  chasisFrameId = receiveMsgPtr->chasisFrameId; 
  slotId = receiveMsgPtr->slotId;

  SwMTableIndex.nodeType = receiveMsgPtr->nodeType;
  SwMTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
  SwMTableIndex.slotId =receiveMsgPtr->slotId;
  strcpy(SwMTableIndex.swVersion,receiveMsgPtr->swVersion);

  LOG_PRINT(LOG_INFO,"dspDelSwMTableHandler: Enter function");
  LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->swVersion);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",receiveMsgPtr->nodeType);
  LOG_PRINT(LOG_INFO,"Received FrameId: %d ",receiveMsgPtr->chasisFrameId);
  LOG_PRINT(LOG_INFO,"Received slotId: %d ",receiveMsgPtr->slotId);

  if (convertInputStringToNumber(receiveMsgPtr->swVersion,&tokenNum,
        token,&errCause) == SW_VER_SUCCESS)
  {
    if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255))        
    {
      LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
      cfgSendNackToCm(CM_ERR_SW_VERSION_TOKENS_EXCEEDS_RANGE);
      return;
    }         
  }
  else
  {
    LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
    cfgSendNackToCm(errCause);
    return;
  }

  /* FIX for Mantis: 6130 start */
  /* Check if upgrade Offer is ongoing */
  ret = getallSwMOfferTable( &swMOfferBuff, &outCount, &outSize);
  if ( ret == CLIB_SUCCESS )
  {
    LOG_PRINT(LOG_DEBUG,"Software Offer is on going on BSC");
    free(swMOfferBuff);
    cfgSendNackToCm(CM_ERR_SW_OFFER_IN_PROGRESS);
    return;
  }
  /* check if activation is in progress for BSC/EIC */
  actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx( &nodeType, &swStatus );
  if ( actionInProgress == I_TRUE )
  {
    LOG_PRINT(LOG_DEBUG,"Activation is in progress for nodeType:%d", nodeType);
    fillFailTypeFromNodeType(nodeType, failType)
      cfgSendNackToCm(failType);
    return;
  }
  /* check if deletion is in progress for BSC/EIC/BIC/TRX/DSP */
  actionInProgress = isDeletionInProgress();
  if ( actionInProgress == I_TRUE )
  {
    LOG_PRINT(LOG_DEBUG,"Deletion is in progress for BSC or EIC or DSP or other");
    cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
    return;
  }
  /* FIX for Mantis: 6130 end */

  /*Check if for the requested sw version, there is an entry in SwM table*/
  ret = getSwMTable(&SwMTableIndex,&swMTableDbPtr);
  if (swMTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"Requested software version is not present on BSC");
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  else if (swMTableDbPtr->deletionInProgress == I_TRUE)
  {
    LOG_PRINT(LOG_DEBUG,"Deletion is in progress for req sw version");
    if (swMTableDbPtr != NULL)
      free(swMTableDbPtr);
    cfgSendNackToCm(CM_ERR_SW_DEL_ALREADY_IN_PROGRESS);
    return;
  }
  if (swMTableDbPtr != NULL)
    free(swMTableDbPtr);

  /*Check if deletion recieved for DSP*/
  if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_DSP)
  {
    SwMNodeTableIndices sApiSwMNodeTableIndices;
    /* Retrieve dspId from SwmNode Table */
    LOG_PRINT(DEBUG,"GetDspIdFromSwmNodeTbale Called");
    if (getDspIdFromSwMNodeTable(dspId,&noOfDsp) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"getDspId call is getting failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
    }

    /*Retrieve active version and swStatus from SwMNode Table */
    if(receiveMsgPtr->slotId == 3 || receiveMsgPtr->slotId == 4)
    {
      for( index=0; index<noOfDsp; index++)
      {
        sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_DSP;
        sApiSwMNodeTableIndices.nodeIdentity = dspId[index];
        sApiSwMNodeTableIndices.chasisFrameId = receiveMsgPtr->chasisFrameId;
        //sApiSwMNodeTableIndices.slotId = slotId;
        if (dspId[index] >1){
          break;
        }
        if(dspId[index] == 0)
        {
          sApiSwMNodeTableIndices.slotId = 3;
        }
        if(dspId[index] == 1)
        {
          sApiSwMNodeTableIndices.slotId = 4;
        }

        LOG_PRINT(DEBUG,"Fet SwmNodeTable For NodeTyep  = %d   NodeID=  %d  FrameId = %d  slot Id = %d",sApiSwMNodeTableIndices.nodeType,sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.chasisFrameId,sApiSwMNodeTableIndices.slotId);

        if (getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeDbPtr) != CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_CRITICAL,"getSwMNodeTable Failed ..");
          cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
          return;
        }

        /*Check if requested Sw Version is the Active SwVersion for DSP */ 
        if (strcmp(receiveMsgPtr->swVersion,swMNodeDbPtr->swVersionActive) == ZERO)
        {
          LOG_PRINT(LOG_INFO,"Req. Sw Version is currently the Active SwVersion for dspId %d",dspId[index]);
          if (swMNodeDbPtr != NULL)
            free(swMNodeDbPtr);
          cfgSendNackToCm(CM_ERR_ACTIVE_SW);
          return;
        }

        /*Check if requested Sw Version is the Inactive SwVersion for EIC */ 
        if (strcmp(receiveMsgPtr->swVersion,swMNodeDbPtr->swVersionInactive) == ZERO)
        {
          LOG_PRINT(LOG_INFO,"Deletion not allowed for Inactive SwVersion for DSP %d",dspId[index]);
          if (swMNodeDbPtr != NULL)
            free(swMNodeDbPtr);
          cfgSendNackToCm(CM_ERR_INACTIVE_SW);
          return;
        }

        /*Check if requested Sw Version is activation in progress */ 
        if (swMNodeDbPtr->swStatus == SW_ACTIVATION_IN_PROGRESS)
        {
          LOG_PRINT(LOG_INFO,"Activation is in progress for req. Sw version for dspId %d",dspId[index]);
          if (swMNodeDbPtr != NULL)
            free(swMNodeDbPtr);
          cfgSendNackToCm(CM_ERR_SW_ACT_IN_PROGRESS);
          return;
        }                   
        if (swMNodeDbPtr != NULL)
          free(swMNodeDbPtr);
      }
    }//if icc
    else if(receiveMsgPtr->slotId == 5 || receiveMsgPtr->slotId == 6)
    {
      for( index=0; index<noOfDsp; index++)
      {
        if (dspId[index] < 2 ){
          continue;
        }
        sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_DSP;
        sApiSwMNodeTableIndices.nodeIdentity = dspId[index];
        sApiSwMNodeTableIndices.chasisFrameId = receiveMsgPtr->chasisFrameId;
        //sApiSwMNodeTableIndices.slotId = slotId;
        if((dspId[index] == 2) || (dspId[index] == 3))
        {
          sApiSwMNodeTableIndices.slotId = 5;
        }
        if((dspId[index] == 4) || (dspId[index] == 5))
        {
          sApiSwMNodeTableIndices.slotId = 6;
        }

        LOG_PRINT(DEBUG,"Fet SwmNodeTable For NodeTyep  = %d   NodeID=  %d  SlotId = %d  Frame Id = %d",sApiSwMNodeTableIndices.nodeType,sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.chasisFrameId,sApiSwMNodeTableIndices.slotId);

        if (getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeDbPtr) != CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_CRITICAL,"getSwMNodeTable Failed ..");
          cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
          return;
        }

        /*Check if requested Sw Version is the Active SwVersion for DSP */ 
        if (strcmp(receiveMsgPtr->swVersion,swMNodeDbPtr->swVersionActive) == ZERO)
        {
          LOG_PRINT(LOG_INFO,"Req. Sw Version is currently the Active SwVersion for dspId %d",dspId[index]);
          if (swMNodeDbPtr != NULL)
            free(swMNodeDbPtr);
          cfgSendNackToCm(CM_ERR_ACTIVE_SW);
          return;
        }

        /*Check if requested Sw Version is the Inactive SwVersion for EIC */ 
        if (strcmp(receiveMsgPtr->swVersion,swMNodeDbPtr->swVersionInactive) == ZERO)
        {
          LOG_PRINT(LOG_INFO,"Deletion not allowed for Inactive SwVersion for DSP %d",dspId[index]);
          if (swMNodeDbPtr != NULL)
            free(swMNodeDbPtr);
          cfgSendNackToCm(CM_ERR_INACTIVE_SW);
          return;
        }

        /*Check if requested Sw Version is activation in progress */ 
        if (swMNodeDbPtr->swStatus == SW_ACTIVATION_IN_PROGRESS)
        {
          LOG_PRINT(LOG_INFO,"Activation is in progress for req. Sw version for dspId %d",dspId[index]);
          if (swMNodeDbPtr != NULL)
            free(swMNodeDbPtr);
          cfgSendNackToCm(CM_ERR_SW_ACT_IN_PROGRESS);
          return;
        }                   
        if (swMNodeDbPtr != NULL)
          free(swMNodeDbPtr);
      }
    }//if eic dsp
  }
  /*Update the swAction value as swDelete in SwM Table */
  if (updateDelStatusInSwMTable(SwMTableIndex,I_TRUE) !=CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"updateDelStatusInSwMTable Failed..");
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"updateDelStatusInSwMTable Success");
  /*send SET Ack message to OMC */
  cfgSendAckToCm();

  /*Send Delete request to Platform*/
  LOG_PRINT(LOG_INFO,"Sending Deletion request");

  sendSwDeletionRequest(chasisFrameId,slotId,receiveMsgPtr->nodeType,receiveMsgPtr->swVersion);
  LOG_PRINT(LOG_INFO,"dspDelSwMTableHandler: Exit function");
}

/******************************* Function  Header*****************************
Function Name : deleteDspRowsFromSwmNodeTable()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Deletes Rows from SwMNodeTable if the PRESENT_CARD_INFO_RESP 
does not contain those slotId                
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void deleteDspRowsFromSwmNodeTable()
{
   OamOilCfgPresentCardInfoResp   *oamOilCfgPresentCardInfoRespPtr = NULL;
   SwMNodeTableIndices           swMNodeIndices;
   I_U32                         dspId[MAX_DSP];
   I_U8                          chasisId[MAX_DSP];
   I_U8                          count =ZERO; 
   I_S32                         retCode = ONE;
   I_U16                         index = ZERO;
   I_U16                         index1 = ZERO;
   I_U32                         isFound = I_FALSE;
	 I_U8														chasisFrameId,slotId;
   I_S32 ret = ZERO;

   LOG_PRINT(LOG_INFO,"deleteDspRowsFromSwmNodeTable: Entering in function");
   oamOilCfgPresentCardInfoRespPtr = (OamOilCfgPresentCardInfoResp *)((I_U8 *)gCfgMsgBuf);

   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }

   if ( ( retCode = getDspIdChasisIdFromSwMNodeTable(chasisId, dspId, &count) ) != CLIB_SUCCESS ) 
   {
      LOG_PRINT(LOG_INFO,"SwMNodeTable is Empty");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"SwMNodeTable contains %d rows",count);
      for ( index = 0; index < count; index++ )
      {  
         for ( index1= ZERO; index1 < MAX_DSP; index1++ )
         {
            if ( dspId[index] == oamOilCfgPresentCardInfoRespPtr->cardInfo.dspInfo[index1].dspId )
            {
               if(oamOilCfgPresentCardInfoRespPtr->cardInfo.dspInfo[index1].isDspPresent == BPM_TRUE) 
               { 
                  isFound = I_TRUE;
                  break;
               }
            }
         }
         if ( isFound == I_FALSE )
         {
            swMNodeIndices.nodeType = SYS_NODE_TYPE_DSP;
            swMNodeIndices.nodeIdentity = dspId[index];
            swMNodeIndices.chasisFrameId = chasisId[index];
            //swMNodeIndices.slotId = slotId;
						if(dspId[index] == 0)
						{
						swMNodeIndices.slotId = 3;
						}
						if(dspId[index] == 1)
						{
						swMNodeIndices.slotId = 4;
						}
						if((dspId[index] == 2) || (dspId[index] == 3))
						{
						swMNodeIndices.slotId = 5;
						}
						if((dspId[index] == 4) || (dspId[index] == 5))
						{
						swMNodeIndices.slotId = 6;
						}

            LOG_PRINT(LOG_DEBUG," Deleting row from SwMNodeTable for NodeType: %d NodeIdentity: %d FrameId: %d SlotId: %d as this data does not exist in PRESENT_CARD_INFO_RESP", swMNodeIndices.nodeType, swMNodeIndices.nodeIdentity, swMNodeIndices.chasisFrameId , swMNodeIndices.slotId);  
            if ( (retCode = deleteSwMNodeTable ( &swMNodeIndices ) ) != CLIB_SUCCESS ) 
            {
               LOG_PRINT(LOG_CRITICAL,"deleteSwMNodeTable call is getting failed..");
            }
         }
         isFound = I_FALSE;
      }
   }
    LOG_PRINT(LOG_INFO,"deleteRowsFromSwmNodeTable: Exiting from function");
}

/********************************* Function  Header********************************
  Function Name:       insertDspDetails()
Parameters:          void
Return type:         void
Purpose:             To insert DSP Card details for which alarm was received.
Other Note:          Added for CS4.0
 ************************************************************************************/
I_Void insertDspDetails()
{
   OamOilCfgPresentCardInfoResp *oamOilCfgPresentCardInfoRespPtr =NULL;
   I_U32 index;
   LOG_PRINT(LOG_INFO,"insertDspDetails: Entering in function");
   oamOilCfgPresentCardInfoRespPtr = (OamOilCfgPresentCardInfoResp *)((I_U8 *)gCfgMsgBuf);

   //deleteRowsFromEicCardInfo();
   deleteDspRowsFromSwmNodeTable();


	 updateDspObjDetails(oamOilCfgPresentCardInfoRespPtr->cardInfo.dspInfo,MAX_DSP);
   /* inserting EIC details in SwMNodeTable */

   //cfgInitEicSwMNodeTable();
   //cfgInitDspSwMNodeTable();
   if (gFirstDspAvailResp == SW_ACTIVATION_IN_PROGRESS )
      gFirstDspAvailResp = TRUE;
   else
      gFirstDspAvailResp = FALSE; /* To update only downloaded verison of SwMNodeTable */

   sendRequestForDspAvailableReleases();
   sendRequestForEicDspAvailableReleases();

   LOG_PRINT(LOG_INFO,"insertEicDetails: Exiting From function");

}
/******************************* Function  Header*****************************
Function Name : dspSwActivationRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw activation response recieved from OIL
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void dspSwActivationRespHandler()
{
   OamOilCfgSwActResp *swActRespPtr = NULL;
   OamOilCfgNodeInfo *nodeInfo = NULL;
   OamOilCfgInfoSwActResult *bpmSwAct = (OamOilCfgInfoSwActResult *)gCfgMsgBuf;
   I_U32 i;
   swActRespPtr = (OamOilCfgSwActResp*)(&(bpmSwAct->swMActResp));
   nodeInfo =  (OamOilCfgNodeInfo*)(&(bpmSwAct->nodeInfo));

   OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
   I_U8 string[MAX_STRING_LENGTH];
   I_U8 type[4];
   
   LOG_PRINT(LOG_INFO,"Entering dspSwActivationRespHandler");
   LOG_PRINT(LOG_INFO,"Recieved Sw Activation Response");
   LOG_PRINT(LOG_INFO,"Recieved NodeType: %d",swActRespPtr->nodeType);
   LOG_PRINT(LOG_INFO,"Recieved SwActVersion: %s",swActRespPtr->actVersion);
   LOG_PRINT(LOG_INFO,"Result: %d ",swActRespPtr->actResult);
   LOG_PRINT(LOG_INFO,"FrameId: %d ",swActRespPtr->frameId);
   LOG_PRINT(LOG_INFO,"SlotId: %d ",swActRespPtr->slotId);
   LOG_PRINT(LOG_INFO,"RevertVersion: %s ",swActRespPtr->revVersion);

   //if (swActRespPtr->actResult == ACTIVATION_SUCCESSFUL)
   //{
       LOG_PRINT(LOG_INFO,"Preparing Success Alarm: INFO_BPM_SW_ACT_SUCCESS");
       sysAlarmBuff.sysAlarm.sysalarmId = bpmSwAct->alarmId;
       sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; 
       sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
       sysAlarmBuff.sysAlarm.key2 =  swActRespPtr->slotId;
       sysAlarmBuff.sysAlarm.key3 = swActRespPtr->nodeType;
       sysAlarmBuff.sysAlarm.alarmLevel = bpmSwAct->alarmLevel; 
       sysAlarmBuff.sysAlarm.alarmReason = swActRespPtr->actResult;
       //convertNodeType(type,swActRespPtr->nodeType);
       //sysAlarmBuff.sysAlarm.infoStrLen = 
       //sprintf(sysAlarmBuff.sysAlarm.infoString,
       //        "Sw Act for SwVer [%s] is Completed for NodeType [%s],ChasisFrameId [%d],SlotId [%d]",
       //         swActRespPtr->actVersion,type, nodeInfo->chasisFrameId,nodeInfo->slotId); 
       makeCopyOfActAlarm(&sysAlarmBuff);
   //}
   #if 0
   else
   {
       /* Sending Alarm */
       LOG_PRINT(LOG_INFO,"Sending Failure Alarm: INFO_BPM_SW_ACT_FAIL");
       sysAlarmBuff.sysAlarm.sysalarmId = bpmSwAct->alarmId; 
       sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC /*OAMS_OBJTYPE_DSP*/;
       sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
       sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
       sysAlarmBuff.sysAlarm.alarmLevel = bpmSwAct->alarmLevel;
       sysAlarmBuff.sysAlarm.alarmReason = swActRespPtr->actResult;
       getStringForSwActErrorCause(swActRespPtr->nodeType,swActRespPtr->actResult,
                                   swActRespPtr->actVersion,nodeInfo->chasisFrameId,nodeInfo->slotId,string);
       sysAlarmBuff.sysAlarm.infoStrLen = 
       sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
       makeCopyOfActAlarm(&sysAlarmBuff);
/*   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);*/
   
   }
   #endif
   //gFirstDspAvailResp = SW_ACTIVATION_IN_PROGRESS;
   updateDspDetail = TRUE;
   sendPresentCardInfoReq();
   LOG_PRINT(LOG_INFO,"dspSwActivationRespHandler : Exit Function");
} 




/******************************* Function  Header*****************************

   Function Name : DspSwOfferRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw Offer respose recieved from OIL
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void dspSwOfferRespHandler()
{
  OamOilCfgSwOfferResp *swOfferRespPtr = NULL;
  OamOilCfgNodeInfo *nodeInfo = NULL;
  OamOilCfgInfoSwDwnldResult *bpmOfferResp = (OamOilCfgInfoSwDwnldResult*)gCfgMsgBuf;
  swOfferRespPtr = (OamOilCfgSwOfferResp*)(&(bpmOfferResp->swMOfferResp));
  nodeInfo =  (OamOilCfgNodeInfo*)(&(bpmOfferResp->nodeInfo));
  OamsCfgAfhSysAlarm sysAlarmBuff = {0};
  SwMOfferTableIndices swMOfferTableIndex;
  SwMNodeTableIndices swMNodeTableIndex;
  SwMOfferTableApi *swMOfferBuff = NULL;
  I_U32 dspId[MAX_DSP] ;
  I_U8 noOfDsp = ZERO;
  I_U8 string[MAX_STRING_LENGTH];
  I_S32 status = -1;
  I_U8 cpBinaryPath[OAMS_CMD_PARAM_MAX_SIZE];
  I_U32 index = ZERO;
  I_U8 type[4];

  swMOfferTableIndex.nodeType = swOfferRespPtr->nodeType;
  swMOfferTableIndex.chasisFrameId = swOfferRespPtr->frameId;
  swMOfferTableIndex.slotId = swOfferRespPtr->slotId;
  strcpy(swMOfferTableIndex.upgradeVersion,swOfferRespPtr->upgradeVersion);

  LOG_PRINT(LOG_INFO,"dspSwOfferRespHandler : Enter Function");
  LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swOfferRespPtr->upgradeVersion);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",swOfferRespPtr->nodeType);
  LOG_PRINT(LOG_INFO,"FrameId: %d ",swOfferRespPtr->frameId);
  LOG_PRINT(LOG_INFO,"SlotId: %d ",swOfferRespPtr->slotId);
  LOG_PRINT(LOG_INFO,"BinaryPath: %s",swOfferRespPtr->binaryPath);
  LOG_PRINT(LOG_INFO,"Result: %d ",swOfferRespPtr->upgradeOfferResult);

  /* Retrieve dspId's from SwmNodeTable */
  /*Implement a query to Fetch SlotId from SwmNode Table*/
  if (getDspIdFromSwMNodeTable(dspId, &noOfDsp) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"getDspIdFromSwMNodeTable call is getting failed..");
    return;
  }
  if (getSwMOfferTable( &swMOfferTableIndex, &swMOfferBuff) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_DEBUG,"Upgrade Version mismatch in DSP SW offer request and response");
    LOG_PRINT(LOG_DEBUG,"Version received in offer Response %s",swOfferRespPtr->upgradeVersion );
  }
  else
  {
    free (swMOfferBuff); 
  }

  /*Check if Upgrade Offer is successful */
  if (swOfferRespPtr->upgradeOfferResult == UPGRADE_OFFER_SUCCESSFUL)
  {
    LOG_PRINT(DEBUG,"Got Success Response From BPM");		 
    /*Insert a record in SwM Table for the given software version */
    SwMTableApi swMTableBuf;
    swMTableBuf.nodeType = swOfferRespPtr->nodeType;
    swMTableBuf.chasisFrameId = swOfferRespPtr->frameId;
    swMTableBuf.slotId = swOfferRespPtr->slotId;
    strcpy(swMTableBuf.swVersion,swOfferRespPtr->upgradeVersion);

    /*Changes for copying from PP to CP: To be commented after SWMH moved to PP :Start*/
    LOG_PRINT(DEBUG,"Copy Rel from PP to CP");
    status = copyReleaseFromPPToCP(swOfferRespPtr->binaryPath,swOfferRespPtr->upgradeVersion,
        swOfferRespPtr->nodeType,cpBinaryPath);
    if (status != I_TRUE)
    {
      LOG_PRINT(DEBUG,"Send SW Deletion Request as Status FALSE");		
      sendSwDeletionRequest(swOfferRespPtr->frameId,swOfferRespPtr->slotId,swOfferRespPtr->nodeType,swOfferRespPtr->upgradeVersion);
      return;
    }
    memcpy(swMTableBuf.binaryPath,cpBinaryPath,OAMS_CMD_PARAM_MAX_SIZE);
    /*Changes for copying from PP to CP: End*/

    /*Changes for copying from PP to CP: Uncomment this part of code :Start*/
    /*memcpy(swMTableBuf.binaryPath,swOfferRespPtr->binaryPath,OAMS_CMD_PARAM_MAX_SIZE); */
    /*Changes for copying from PP to CP: End*/
    swMTableBuf.swDownloadCount = 0;
    swMTableBuf.deletionInProgress = I_FALSE;

    /*Delete record from SwMOffer Table */
    LOG_PRINT(DEBUG,"Delete Entry From SwmOffer Table");
    if (deleteSwMOfferTable(&swMOfferTableIndex) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"deleteSwMOfferTable DB call is getting failed");
      return;
    }
    else
      LOG_PRINT(LOG_INFO,"deleteSwMOfferTable Success");
    LOG_PRINT(DEBUG,"Insert Entry in Swm Table");

    if (insertSwMTable(&swMTableBuf) !=CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"insertSwMTable DB call is getting failed..");
      return;
    }
    else
      LOG_PRINT(LOG_INFO,"insertSwMTable Success");

    if ((swOfferRespPtr->nodeType == SYS_NODE_TYPE_DSP)  && (swOfferRespPtr->slotId == 3 || swOfferRespPtr->slotId == 4))
    {
      for( index=0; index<noOfDsp; index++ )
      {
        /*Update the upgraded version recieved as downloaded version 
         * in SwMNode Table for all the Dsp's*/
        swMNodeTableIndex.nodeType = swOfferRespPtr->nodeType;
        swMNodeTableIndex.nodeIdentity = dspId[index];
        swMNodeTableIndex.chasisFrameId = swOfferRespPtr->frameId;
        //   swMNodeTableIndex.slotId = swOfferRespPtr->slotId;

        if (dspId[index] >1){
          break;
        }
        if(dspId[index] == 0 )
        {
          swMNodeTableIndex.slotId = 3;
        }			 
        if(dspId[index] == 1 )
        {
          swMNodeTableIndex.slotId = 4;
        }			 

        LOG_PRINT(DEBUG,"UPDATING SWMNODE TABLE with Data NodeType = %d, Node Id = %d, FrameId = %d, SlotId = %d",swMNodeTableIndex.nodeType,swMNodeTableIndex.nodeIdentity,swMNodeTableIndex.chasisFrameId,swMNodeTableIndex.slotId);

        if (updateVersionDownloadedInSwMNodeTable(swMNodeTableIndex,
              swOfferRespPtr->upgradeVersion) != CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_CRITICAL,"updateVersionDownloadedInSwMNodeTable Failed for DspId: %d",dspId[index]);
          return;
        }
        else
          LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success for dspId %d", dspId[index]);


        if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
              SW_DOWNLOAD_SUCCESS) !=CLIB_SUCCESS)  
        {
          LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
        }
      }//for
      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending Success ALARM: INFO_BPM_SW_DWNLD_SUCCESS");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmOfferResp->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel = bpmOfferResp->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swOfferRespPtr->upgradeOfferResult;
      convertNodeType(type,swOfferRespPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
          "Sw Offer for SwVer [%s],NodeType [%s] is Completed at Chasis [%d],Slot [%d]",
          swOfferRespPtr->upgradeVersion,type,nodeInfo->chasisFrameId,nodeInfo->slotId); 
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
          ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    }
    else if ((swOfferRespPtr->nodeType == SYS_NODE_TYPE_DSP)  && (swOfferRespPtr->slotId == 5 || swOfferRespPtr->slotId == 6))
    {
      for( index=0; index<noOfDsp; index++ )
      {
        /*Update the upgraded version recieved as downloaded version 
         * in SwMNode Table for all the Dsp's*/
        swMNodeTableIndex.nodeType = swOfferRespPtr->nodeType;
        swMNodeTableIndex.nodeIdentity = dspId[index];
        swMNodeTableIndex.chasisFrameId = swOfferRespPtr->frameId;
        //   swMNodeTableIndex.slotId = swOfferRespPtr->slotId;
          if (dspId[index] <2){
            continue;
          }

        if(((dspId[index] == 2) || (dspId[index] == 3)) )
        {
          swMNodeTableIndex.slotId = 5;
        }			 
        if((dspId[index] == 4) || (dspId[index] == 5))
        {
          swMNodeTableIndex.slotId = 6;
        }			 

        LOG_PRINT(DEBUG,"UPDATING SWMNODE TABLE with Data NodeType = %d, Node Id = %d, FrameId = %d, SlotId = %d",swMNodeTableIndex.nodeType,swMNodeTableIndex.nodeIdentity,swMNodeTableIndex.chasisFrameId,swMNodeTableIndex.slotId);

        if (updateVersionDownloadedInSwMNodeTable(swMNodeTableIndex,
              swOfferRespPtr->upgradeVersion) != CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_CRITICAL,"updateVersionDownloadedInSwMNodeTable Failed for DspId: %d",dspId[index]);
          return;
        }
        else
          LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success for dspId %d", dspId[index]);


        if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
              SW_DOWNLOAD_SUCCESS) !=CLIB_SUCCESS)  
        {
          LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
        }
      }//for
      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending Success ALARM: INFO_BPM_SW_DWNLD_SUCCESS");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmOfferResp->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_EIC;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel = bpmOfferResp->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swOfferRespPtr->upgradeOfferResult;
      convertNodeType(type,swOfferRespPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
          "Sw Offer for SwVer [%s],NodeType [%s] is Completed at Chasis [%d],Slot [%d]",
          swOfferRespPtr->upgradeVersion,type,nodeInfo->chasisFrameId,nodeInfo->slotId); 
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
          ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    } // else if eic dsp
  }//UPGRADE_OFFER_SUCCESSFUL
  else
  {
    LOG_PRINT(DEBUG,"Received Result = FAILED from BPM");
    /*Delete record from SwMOffer Table */
    if (deleteSwMOfferTable(&swMOfferTableIndex) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"deleteSwMOfferTable DB call is getting failed");
      return;
    }
    else
      LOG_PRINT(LOG_INFO,"deleteSwMOfferTable Success");
    
    if ((swOfferRespPtr->slotId == 3 || swOfferRespPtr->slotId == 4))
    {
      for( index=0; index<noOfDsp; index++ )
      {
        /*Update the upgraded version recieved as downloaded version 
         * in SwMNode Table for all the Dsp's*/
        swMNodeTableIndex.nodeType = swOfferRespPtr->nodeType;
        swMNodeTableIndex.nodeIdentity = dspId[index];
        swMNodeTableIndex.chasisFrameId = swOfferRespPtr->frameId;
        //   swMNodeTableIndex.slotId = swOfferRespPtr->slotId;

          if (dspId[index] >1){
            break;
          }
        if(dspId[index] == 0)
        {
          swMNodeTableIndex.slotId = 3;
        }			 
        if(dspId[index] == 1)
        {
          swMNodeTableIndex.slotId = 4;
        }			 

        if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
              SW_DOWNLOAD_FAILED) !=CLIB_SUCCESS)  
        {
          LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
        }
      }//for
      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending failure ALARM: INFO_BPM_SW_DWNLD_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmOfferResp->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel =  bpmOfferResp->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swOfferRespPtr->upgradeOfferResult;
      getStringForSwOfferErrorCause(swOfferRespPtr->upgradeOfferResult,
          swOfferRespPtr->upgradeVersion,swOfferRespPtr->nodeType,string,nodeInfo->chasisFrameId,nodeInfo->slotId);
      sysAlarmBuff.sysAlarm.infoStrLen = 
        sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
          ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    }
    else if ((swOfferRespPtr->slotId == 5 || swOfferRespPtr->slotId == 6))
    {
      for( index=0; index<noOfDsp; index++ )
      {
        /*Update the upgraded version recieved as downloaded version 
         * in SwMNode Table for all the Dsp's*/
        swMNodeTableIndex.nodeType = swOfferRespPtr->nodeType;
        swMNodeTableIndex.nodeIdentity = dspId[index];
        swMNodeTableIndex.chasisFrameId = swOfferRespPtr->frameId;
        //   swMNodeTableIndex.slotId = swOfferRespPtr->slotId;

          if (dspId[index] <2){
            continue;
          }
        if(((dspId[index] == 2) || (dspId[index] == 3)) )
        {
          swMNodeTableIndex.slotId = 5;
        }			 
        if((dspId[index] == 4) || (dspId[index] == 5))
        {
          swMNodeTableIndex.slotId = 6;
        }			 
        if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
              SW_DOWNLOAD_FAILED) !=CLIB_SUCCESS)  
        {
          LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
        }
      }//for
      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending failure ALARM: INFO_BPM_SW_DWNLD_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmOfferResp->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_EIC;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel =  bpmOfferResp->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swOfferRespPtr->upgradeOfferResult;
      getStringForSwOfferErrorCause(swOfferRespPtr->upgradeOfferResult,
          swOfferRespPtr->upgradeVersion,swOfferRespPtr->nodeType,string,nodeInfo->chasisFrameId,nodeInfo->slotId);
      sysAlarmBuff.sysAlarm.infoStrLen = 
        sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
          ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    }
  } 
  LOG_PRINT(LOG_INFO,"dspSwOfferRespHandler : Exit Function");
}
/******************************* Function  Header*****************************
Function Name : performDspSwActivationOperation()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Handles DSP software activation procedure
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void performDspSwActivationOperation(SwMNodeTableApi *receiveMsgPtr)
{
  SwMTableApi *swMTableDbPtr = NULL;
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  SwMNodeTableIndices swMNodeTableIndex;
  SwMTableIndices swMTableIndex;
  OamsCfgOilSwActReq swActBuff;
  SwMOfferTableApi *swMOfferBuff = NULL;
  I_U32 outCount = ZERO;
  I_U8 count = ZERO;
  I_U16 outSize = ZERO;
  I_S32 ret = ONE;
  I_U32 bscId = ZERO;
  I_U32 dspId[MAX_DSP];
  I_U8 noOfDsp = ZERO;
  I_U32 index = ZERO;
  I_S32 actionInProgress = I_FALSE;
  I_U32 swStatus[TWO]={ZERO};
  //I_U8 slotId;
  //I_U8 chasisFrameId;
  I_U32 nodeType =0, failType =0, swStatus_o = 0;
/*
  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: ChasisFrameId[%d] SlotId[%d]",chasisFrameId,slotId);
*/

  swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
  swMNodeTableIndex.nodeIdentity = receiveMsgPtr->nodeIdentity;
  swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId; 
  swMNodeTableIndex.slotId =  receiveMsgPtr->slotId;

  swMTableIndex.nodeType = receiveMsgPtr->nodeType;
  swMTableIndex.chasisFrameId =receiveMsgPtr->chasisFrameId;
  swMTableIndex.slotId = receiveMsgPtr->slotId ;
  strcpy(swMTableIndex.swVersion,receiveMsgPtr->swVersionNew);

  LOG_PRINT(LOG_INFO,"performDspSwActivationOperation : Entering function");

  /*Check if swAction is SW_ACTIVATE */
  if (receiveMsgPtr->swAction != SW_ACTIVATE)
  {
    LOG_PRINT(LOG_DEBUG,"Invalid request recieved for DSP");
    cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
    return;
  }
  LOG_PRINT(LOG_INFO,"Recieved DSP Sw Activation Request");

  if (gBssState == unlocked)
  {
    LOG_PRINT(LOG_DEBUG,"BSS is in UnLocked state");
    cfgSendNackToCm(CM_ERR_BSS_UNLOCKED);
    return;
  }
  else if (gBssState == unlockInProgress)
  {
    LOG_PRINT(LOG_DEBUG,"BSS is UnLock in Progress state");
    cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
    return;
  }
  else if (gBssState == lockInProgress)
  {
    LOG_PRINT(LOG_DEBUG,"BSS is Lock in Progress state");
    cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"BSS is in Locked state");

  /* Check if upgrade Offer is ongoing */
  ret = getallSwMOfferTable( &swMOfferBuff, &outCount, &outSize);
  if ( ret == CLIB_SUCCESS )
  {
    LOG_PRINT(LOG_DEBUG,"Software Offer is on going on BSC");
    free(swMOfferBuff);
    cfgSendNackToCm(CM_ERR_SW_OFFER_IN_PROGRESS);
    return;
  }
  /* FIX for Mantis: 6130 start */
  /* check if deletion is in progress for BSC/EIC/BIC/TRX */
  actionInProgress = isDeletionInProgress();
  if ( actionInProgress == I_TRUE )
  {
    LOG_PRINT(LOG_DEBUG,"Deletion is in progress for BSC or EIC or DSP");
    cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
    return;
  }
  /* FIX for Mantis: 6130 End */

  /*Check if requested sw version of DSP is present in SWM table */
  ret = getSwMTable(&swMTableIndex,&swMTableDbPtr);
  if (swMTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"Software version is not present with platform");
    cfgSendNackToCm(CM_ERR_VERSION_NOT_FOUND);
    return;
  }
  /*Check if deletion is in progress for requested sw version in SwMTable*/ 
  else if (swMTableDbPtr->deletionInProgress == I_TRUE)
  {
    LOG_PRINT(LOG_DEBUG,"Delete is in progress for the required Sw version");
    if (swMTableDbPtr != NULL)
      free(swMTableDbPtr);
    cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
    return;
  }

  if (swMTableDbPtr != NULL)
    free(swMTableDbPtr);
  /*Check if for the nodeId and nodeType, there is a record in T2 table */
  LOG_PRINT(DEBUG,"Going To Search SwmNodeTable For NodeType = %d NodeId = %d slotId = %d",swMNodeTableIndex.nodeType,swMNodeTableIndex.nodeIdentity,swMNodeTableIndex.slotId);
  ret = getSwMNodeTable(&swMNodeTableIndex,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  /*Check if req Sw version is not active SwVersion of DSP in SwMNode Table*/
  else if (strcmp(swMNodeTableDbPtr->swVersionActive,receiveMsgPtr->swVersionNew) == ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Requested Sw version is the Active SwVersion of DSP");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_VERSION_ALREADY_ACTIVATE);
    return;
  }
  /*Check if req Sw version is present in inactive/downloaded SwVersion list
   *  of DSP in SwMNode Table*/
  else if (strcmp(swMNodeTableDbPtr->swVersionInactive,receiveMsgPtr->swVersionNew) != ZERO && 
      strcmp(swMNodeTableDbPtr->swVersionDownloaded,receiveMsgPtr->swVersionNew) != ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Requested Sw version is not present in inactive/downloaded SwVersion List of DSP");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_VERSION_NOT_AVAILABLE_FOR_ACT);
    return;
  }
  /*Check if in SwMNode table,the status is NOT swDownloadInProgress or 
   * swActivationInProgress */
  else if (swMNodeTableDbPtr->swStatus == SW_DOWNLOAD_IN_PROGRESS || 
      swMNodeTableDbPtr->swStatus == SW_ACTIVATION_IN_PROGRESS )
  {
    LOG_PRINT(LOG_DEBUG,"Either Download or Activation is in progress for the node");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
    return;
  }
  if (swMNodeTableDbPtr != NULL)
    free(swMNodeTableDbPtr);

  /* check if activation is in progress for BSC/EIC */
  actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx( &nodeType, &swStatus_o);
  if ( actionInProgress == I_TRUE )
  {
    LOG_PRINT(LOG_DEBUG,"Activation is in progress for nodeType:%d", nodeType);
    fillFailTypeFromNodeType(nodeType, failType)
      cfgSendNackToCm(failType);
    return;
  }

  /*Check if in SwMNodeTable, the status of the other DSP is not swActivationInProgress */ 
  /* Retrieve DspId's from eicCardInfoTable */
  if (getDspIdFromSwMNodeTable(dspId, &noOfDsp) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"getDspId call is getting failed.."); 
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
  if(receiveMsgPtr->slotId == 3 || receiveMsgPtr->slotId == 4) 
  {

    for( index=0; index<noOfDsp; index++ )
    { 
      swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
      swMNodeTableIndex.nodeIdentity = dspId[index];
      swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
      swMNodeTableIndex.slotId =  receiveMsgPtr->slotId;

      if (dspId[index] >1){
        break;
      }
      if(dspId[index] == 0)
      {
        swMNodeTableIndex.slotId = 3;
      }			 
      if(dspId[index] == 1)
      {
        swMNodeTableIndex.slotId = 4;
      }			 
      /*Update record in SwMNode table for both the DSP's indicating sw activation is in progress */
      if (updateSwStatusActionVersionInSwMNodeTable(swMNodeTableIndex,
            SW_ACTIVATION_IN_PROGRESS,SW_ACTIVATE,receiveMsgPtr->swVersionNew) != 
          CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed for dspId: %d", dspId[index]);
        cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
        return;
      }
      else
        LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");
    }
  }//if icc dsp 
  else if(receiveMsgPtr->slotId == 5 || receiveMsgPtr->slotId == 6) 
  {

      for( index=0; index<noOfDsp; index++ )
    { 
      swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
      swMNodeTableIndex.nodeIdentity = dspId[index];
      swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
      swMNodeTableIndex.slotId =  receiveMsgPtr->slotId;

          if (dspId[index] <2){
            continue;
          }
      if((dspId[index] == 2) || (dspId[index] == 3))
      {
        swMNodeTableIndex.slotId = 5;
      }			 
      if((dspId[index] == 4) || (dspId[index] == 5))
      {
        swMNodeTableIndex.slotId = 6;
      }			 
      /*Update record in SwMNode table for both the DSP's indicating sw activation is in progress */
      if (updateSwStatusActionVersionInSwMNodeTable(swMNodeTableIndex,
            SW_ACTIVATION_IN_PROGRESS,SW_ACTIVATE,receiveMsgPtr->swVersionNew) != 
          CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed for dspId: %d", dspId[index]);
        cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
        return;
      }
      else
        LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");
    }
  }//else if  eic slots 

  /*send SET Ack message to OMC */
  cfgSendAckToCm();

  /*Send the DSP software activation request to Platform */
  LOG_PRINT(LOG_INFO,"Sending DSP Sw Activation request");
  /* In case of Dsp Activation ActiveICC frameId and SlotId will be used */
  //if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  //{
  // LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
  // return;
  // }
  // LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: ChasisFrameId[%d] SlotId[%d]",chasisFrameId,slotId);

  swActBuff.frameId = receiveMsgPtr->chasisFrameId;
  swActBuff.slotId = receiveMsgPtr->slotId;
  swActBuff.nodeType = receiveMsgPtr->nodeType;
  swActBuff.cardState = ZERO; /* No need to set cardState as OOS */
  strcpy(swActBuff.actVersion,receiveMsgPtr->swVersionNew);
  LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_SW_ACT_REQ to Oil");
  cfgSendMessage((I_Void *)&swActBuff, sizeof(OamsCfgOilSwActReq), ENT_OAM_OIL,
      OAMS_CFG_OIL_SW_ACT_REQ , 0);
  LOG_PRINT(LOG_INFO,"performDspSwActivationOperation : Exiting function");
}




/******************************* Function  Header*****************************
   Function Name :    setDspSwMOfferTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Dsp Sw Upgrade Offer request from OMC/CLI
Other Note    : Added For BSCR2.0
*****************************************************************************/
I_Void setDspSwMOfferTableHandler()
{
   SwMOfferTableApi *receiveMsgPtr = NULL;
   SwMOfferTableApi *swMOfferTableDbPtr = NULL;
   
   receiveMsgPtr = (SwMOfferTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   SwMOfferTableIndices swMOfferTableindex;
   SwMTableApi *swMTableDbPtr = NULL;
   SwMTableIndices swMTableindex;
   I_S32 actionInProgress = I_FALSE;
   I_S32 ret = ONE;
   I_U32 rowCount = ZERO;
   I_U32 tokenNum;
   I_U32 token[MAX_DIGITS];
   I_U32 errCause;
   I_CHAR logPasswdChSum[OAMS_NAME_SIZE + 1]; 
   I_U8 chasisFrameId;
   I_U8 slotId;
   I_U32 nodeType = 0, failType = 0, swStatus = 0;

/*
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
   if ( ( receiveMsgPtr->slotId != slotId ) && (receiveMsgPtr->slotId != 0xFF ))
   {
      LOG_PRINT(LOG_INFO,"Invalid SlotId Passed");
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return;
   }
*/
   
   swMOfferTableindex.nodeType = receiveMsgPtr->nodeType;
   swMOfferTableindex.chasisFrameId = receiveMsgPtr->chasisFrameId;
   swMOfferTableindex.slotId = receiveMsgPtr->slotId ;
   strcpy(swMOfferTableindex.upgradeVersion,receiveMsgPtr->upgradeVersion);
   swMTableindex.nodeType = receiveMsgPtr->nodeType;
   swMTableindex.chasisFrameId = chasisFrameId;
   swMTableindex.slotId = receiveMsgPtr->slotId ;
   strcpy(swMTableindex.swVersion,receiveMsgPtr->upgradeVersion);

   LOG_PRINT(LOG_INFO,"setDspSwMOfferTableHandler : Entering function");
   LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->upgradeVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",receiveMsgPtr->nodeType);
   LOG_PRINT(LOG_INFO,"slotId: %d ",receiveMsgPtr->slotId);
   LOG_PRINT(LOG_INFO,"ftpServerAddress: %u",receiveMsgPtr->ftpServerAddress);
   memset(logPasswdChSum,(I_S32)NULL,OAMS_NAME_SIZE + 1);
   memcpy(logPasswdChSum,receiveMsgPtr->loginName,OAMS_NAME_SIZE);
   LOG_PRINT(LOG_INFO,"loginName: %s ",logPasswdChSum);
   memset(logPasswdChSum,(I_S32)NULL,OAMS_NAME_SIZE + 1);
   memcpy(logPasswdChSum,receiveMsgPtr->password,OAMS_NAME_SIZE);
   LOG_PRINT(LOG_INFO,"password: %s",logPasswdChSum);
   memset(logPasswdChSum,(I_S32)NULL,OAMS_NAME_SIZE + 1);
   memcpy(logPasswdChSum,receiveMsgPtr->checksum,OAMS_NAME_SIZE);
   LOG_PRINT(LOG_INFO,"checksum: %s",logPasswdChSum);
   LOG_PRINT(LOG_INFO,"size: %u",receiveMsgPtr->size);

   /*Check Sw Version is in correct format*/
   if (convertInputStringToNumber(receiveMsgPtr->upgradeVersion,&tokenNum,
            token,&errCause) == SW_VER_SUCCESS)
   {
      if ((token[0] == 0) || (token[0] > 255) || (token[1] > 255) || (token[2] > 255))        
      {
         LOG_PRINT(LOG_DEBUG,"Recieved Sw Version format incorrect ");
         cfgSendNackToCm(CM_ERR_SW_VERSION_TOKENS_EXCEEDS_RANGE);
         return;
      }         
   }
   else
   {
      LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
      cfgSendNackToCm(errCause);
      return;
   }

   /*Retrieve count of number of rows present in SwMOffer Table */ 
   if (getCountOfSwUpgradeOfferTable(&rowCount) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG,"No row present in SwMOffer Table");
   }
   else
   {
      /*Check if already maximum allowed upgrade offer is in progress */
      if (rowCount == MAX_SW_UPGRADE_OFFER_IN_PARALLEL)
      {
         LOG_PRINT(LOG_DEBUG,"Already Max allowed swUpgradeOffer is in progress");
         cfgSendNackToCm(CM_ERR_MAX_SW_UPGRADE_OFFER_ALREADY_RUNNING);
         return;
      }

      /*Check if entry exists in SwMOffer table for req swVersion */
      ret = getSwMOfferTable(&swMOfferTableindex,&swMOfferTableDbPtr);
      if (swMOfferTableDbPtr != NULL)
      {
         LOG_PRINT(LOG_DEBUG,"Platform has already started download procedure");
         cfgSendNackToCm(CM_ERR_DWNLD_ALREADY_INITIATED);
         free(swMOfferTableDbPtr);
         return;
      }
   }
   /* check if activation is in progress for BSC/EIC */
   actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx( &nodeType, &swStatus );
   if ( actionInProgress == I_TRUE )
   {
      LOG_PRINT(LOG_DEBUG,"Activation is in progress for nodeType:%d", nodeType);
      fillFailTypeFromNodeType(nodeType, failType)
      cfgSendNackToCm(failType);
      return;
   }
   /* FIX for Mantis: 6130 start */
   /* check if deletion is in progress for BSC/EIC/BIC/TRX */
   actionInProgress = isDeletionInProgress();
   if ( actionInProgress == I_TRUE )
   {
      LOG_PRINT(LOG_DEBUG,"Deletion is in progress for BSC or EIC");
      cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
      return;
   }
   /* FIX for Mantis: 6130 End */

   /*Check if for the requested sw version, there is an entry in SwM table */
   ret = getSwMTable(&swMTableindex,&swMTableDbPtr);
   if (swMTableDbPtr != NULL)
   {
      LOG_PRINT(LOG_DEBUG,"Software version is already present with platform");
      cfgSendNackToCm(CM_ERR_SW_VERSION_ALREADY_DWNLDED);
      free(swMTableDbPtr);
      return;
   }

   /*Insert record in SwMOffer Table indicating download is in process for 
    * requested sw version */
   /* as the dsp version is different for EIC and ICC */ 
   //receiveMsgPtr->chasisFrameId = chasisFrameId;
   //receiveMsgPtr->slotId = slotId;

   if (insertSwMOfferTable(receiveMsgPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"insertSwMOfferTable DB call is getting failed.");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"insertSwMOfferTable Successful");

   /*Send Ack of Set command */
   cfgSendAckToCm();

   /*Send Software Offer Request to Platform */
   LOG_PRINT(LOG_INFO,"Sending Upgrade Offer Request");
   sendSwUpgradeOfferRequest(receiveMsgPtr);
   LOG_PRINT(LOG_INFO,"setDspSwMOfferTableHandler : Exiting function");
}



/******************************* Function  Header*****************************
Function Name : setDspSwMNodeTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles EIC software activation 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setDspSwMNodeTableHandler()
{
   SwMNodeTableApi *receiveMsgPtr = NULL;
   receiveMsgPtr = (SwMNodeTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   I_U32 tokenNum;
   I_U32 token[MAX_DIGITS];
   I_U32 errCause;

   LOG_PRINT(LOG_INFO,"setDspSwMNodeTableHandler : Entering function");
   LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->swVersionNew);
   LOG_PRINT(LOG_INFO,"NodeType: %d NodeId: %u",receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity);
   LOG_PRINT(LOG_INFO,"FrameId: %d",receiveMsgPtr->chasisFrameId);
   LOG_PRINT(LOG_INFO,"Slotd: %d",receiveMsgPtr->slotId);
   LOG_PRINT(LOG_INFO,"SwAction: %d",receiveMsgPtr->swAction);

   /*Check Sw Version is in correct format*/
   if (convertInputStringToNumber(receiveMsgPtr->swVersionNew,&tokenNum,
            token,&errCause) == SW_VER_SUCCESS)
   {
      if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255))        
      {
         LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
         cfgSendNackToCm(CM_ERR_SW_VERSION_TOKENS_EXCEEDS_RANGE);
         return;
      }         
   }
   else
   {
      LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
      cfgSendNackToCm(errCause);
      return;
   }

   if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_DSP)
   {
      performDspSwActivationOperation(receiveMsgPtr);
   }
   LOG_PRINT(LOG_INFO,"setDspSwMNodeTableHandler : Exiting function");
}


/******************************* Function  Header*****************************
   Function Name : sendRequestForDspAvailableReleases()
Parameters    : None
Return type   : I_Void
Purpose       : Sends request for Dsp available releases present on BSC platform
for EIC
Other Note    : Added For BSC R2.0
 *****************************************************************************/
I_Void sendRequestForDspAvailableReleases()
{
   OamsCfgOilAvailableReleasesReq  availableReleasesReqBuff;  
   I_U8 chasisFrameId;
   I_U8 slotId;
   I_S32 ret = ZERO;
 
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

   availableReleasesReqBuff.frameId = chasisFrameId;
   availableReleasesReqBuff.slotId = slotId;
   availableReleasesReqBuff.nodeType = SYS_NODE_TYPE_DSP;
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ DSP for ChasisFrameId[%d],SlotId[%d]",chasisFrameId,slotId);
   cfgSendMessage((I_Void *)&availableReleasesReqBuff, 
                 sizeof(OamsCfgOilAvailableReleasesReq), ENT_OAM_OIL, 
                 OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ, 0);       
   gAvailReleaseRspFlag++;
   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d)incremented in sendRequestForDspAvailableReleases()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS
   //LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag.. %d",gAvailReleaseRspFlag);
}//sendRequestForDspAvailableReleases

/******************************* Function  Header*****************************
   Function Name : sendRequestForEicDspAvailableReleases()
Parameters    : None
Return type   : I_Void
Purpose       : Sends request for Dsp available releases present on BSC platform
for EIC
Other Note    : Added For BSC R2.0
 *****************************************************************************/
I_Void sendRequestForEicDspAvailableReleases()
{
   OamsCfgOilAvailableReleasesReq  availableReleasesReqBuff;  
   //I_U8 chasisFrameId;
   //I_U8 slotId;
   I_S32 ret = ZERO;
   I_U8 eicId[MAX_EIC];
   I_U8 chasisFrameId[MAX_EIC];
   I_U8 noOfEic=0;
    /*replaced with  query for eic active card   
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
   */
   if (getEicIdChasisId(eicId, chasisFrameId, &noOfEic) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getEicIdChasisId call is getting failed.."); 
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveEicSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",eicId[0],chasisFrameId[0]);
   if(noOfEic > 0)
   {
     availableReleasesReqBuff.frameId = chasisFrameId;
     availableReleasesReqBuff.slotId = eicId[0]; 
     availableReleasesReqBuff.nodeType = SYS_NODE_TYPE_DSP;
     LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ DSP of EIC for ChasisFrameId[%d],SlotId[%d]",chasisFrameId[0],eicId[0]);

     cfgSendMessage((I_Void *)&availableReleasesReqBuff, 
         sizeof(OamsCfgOilAvailableReleasesReq), ENT_OAM_OIL, 
         OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ, 0);       
     gAvailReleaseRspFlag++;
    // LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag.. %d",gAvailReleaseRspFlag);
   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) incremented in sendRequestForEicDspAvailableReleases()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS
   }
   else
   {
     return;
   }
}//sendRequestForDspAvailableReleases
/******************************* Function  Header*****************************
   Function Name : dspAvailableReleasesRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : populate SwM table with releases recieved from platform
for DSP
Other Note    : Added For BSC CS4.0
 *****************************************************************************/

I_Void dspAvailableReleasesRespHandler()
{
  OamOilCfgAvailableReleasesResp *availableReleasesRespPtr = NULL;
  OamOilCfgInfoAvailableVersion *bpmAvailVersion = (OamOilCfgInfoAvailableVersion *)gCfgMsgBuf;
  availableReleasesRespPtr = (OamOilCfgAvailableReleasesResp*)(&(bpmAvailVersion->swMAvailResp));
  SwMTableApi swMTableBuff;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  I_U32 count = 0 ;
  I_U8 dspId[MAX_DSP];
  I_U8 chasisFrameId[MAX_DSP];
  I_U16 outSize;
  I_U8 noOfDsp = 0, outCnt =0;
  I_U32 index = ZERO;
  I_U32 i,nodeType =0;
  I_S32 ret=0;
  I_U8 chasisFrameId1,slotId;
  I_U32 iccDspCount =2 ;
  I_U32 eicDspStart =2 ;

  LOG_PRINT(LOG_INFO,"Received DSP AvailableReleasesResp for NodeType[%d], ChasisFrameId[%d], SlotId[%d]",availableReleasesRespPtr->nodeType,availableReleasesRespPtr->frameId,availableReleasesRespPtr->slotId);

  LOG_PRINT(LOG_INFO,"gFirstDspAvailResp = [%d]",gFirstDspAvailResp);
  gAvailReleaseRspFlag--;
   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) decremented in dspAvailableReleasesRespHandler()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS

  LOG_PRINT(DEBUG,"Num of Available versions %d for nodetype %d",
      availableReleasesRespPtr->numVersion,availableReleasesRespPtr->nodeType );

  if (availableReleasesRespPtr->numVersion == ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"No version present on the BSC Card for NodeType: %d",
        availableReleasesRespPtr->nodeType );
  }

  if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_DSP  && availableReleasesRespPtr->availVersionResult == OPERATION_SUCCESS)
  {
    nodeType = availableReleasesRespPtr->nodeType;
    if (gFirstDspAvailResp == FALSE)
    {
      if(deleteDataForNodeTypeFromSwMTable(&nodeType) != CLIB_SUCCESS)
      {
        LOG_PRINT(DEBUG,"deleteDataForNodeTypeFromSwMTable failed");
      }
    }

    for (count = 0;count < 3;count++)
    { 
      LOG_PRINT(INFO,"Recieved swVersion: %s",availableReleasesRespPtr->availSwVersions[count]);    
      if (strlen(availableReleasesRespPtr->availSwVersions[count]) == ZERO)
      {
        LOG_PRINT(INFO,"No DSP release present for count: %d",count + 1);    
      }
      else
      {
        swMTableBuff.nodeType = availableReleasesRespPtr->nodeType;
        swMTableBuff.chasisFrameId = availableReleasesRespPtr->frameId;
        swMTableBuff.slotId = availableReleasesRespPtr->slotId;
        strcpy(swMTableBuff.swVersion,
            availableReleasesRespPtr->availSwVersions[count]);
        memcpy(swMTableBuff.binaryPath,availableReleasesRespPtr->availSwBinaryPath[count],
            OAMS_CMD_PARAM_MAX_SIZE); 
        swMTableBuff.swDownloadCount = ZERO;
        swMTableBuff.deletionInProgress = I_FALSE;
        /*Not Required at BSC-DB/OMC 27 Sept 2016*/
        /*if (insertSwMTable(&swMTableBuff) != CLIB_SUCCESS)
        {
          if ( updateSwMTable(&swMTableBuff ) != CLIB_SUCCESS )
            LOG_PRINT(LOG_MAJOR,"updateSwMTable DB call is getting failed..");
        }
        else
          LOG_PRINT(LOG_INFO,"insertSwMTable Successful");           
        */
        /*Not Required at BSC-DB/OMC 27 Sept 2016*/
      }

    }
    if (availableReleasesRespPtr->slotId == 3 || availableReleasesRespPtr->slotId == 4)
    {
      for( index=0; index<MAX_DSP; index++)
      {
        if(index >1)
        {
          break;
        }

        if(gDspInfo[index].isDspPresent == PRESENT)
        {
          sApiSwMNodeTableIndices.nodeIdentity = gDspInfo[index].dspId;
          sApiSwMNodeTableIndices.chasisFrameId = gDspInfo[index].frameID;
          sApiSwMNodeTableIndices.slotId = gDspInfo[index].slotID;
          //sApiSwMNodeTableIndices.slotId = slotId;
          sApiSwMNodeTableIndices.nodeType = availableReleasesRespPtr->nodeType;
          //if ( gFirstDspAvailResp == FALSE )
          // {
          //    LOG_PRINT(DEBUG,"GOING TO update DWLD version in  SWMNODE TABLE with Node Iden = %d SlotId = %d",sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.slotId);
          //    if (updateVersionDownloadedInSwMNodeTable( sApiSwMNodeTableIndices,
          //          availableReleasesRespPtr->availSwVersions[2]) != CLIB_SUCCESS)
          //    {
          //        LOG_PRINT(LOG_MAJOR,"updateVersionDownloadedInSwMNodeTable Failed for dspId[%d]",
          //           sApiSwMNodeTableIndices.nodeIdentity);
          //     }
          //     else
          //        LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success"); 

          /*if ( index == noOfDsp-1)
            gFirstDspAvailResp = TRUE;*/
          //}
          //else
          // {
          LOG_PRINT(DEBUG,"GOING TO update Act Inact DWNLD  SWMNODE TABLE with Node Iden = %d SlotId = %d",sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.slotId);
          if (updateVersionActiveInactiveDnldedInSwMNodeTable(
                sApiSwMNodeTableIndices,
                availableReleasesRespPtr->availSwVersions[0],
                availableReleasesRespPtr->availSwVersions[1],
                availableReleasesRespPtr->availSwVersions[2]) != CLIB_SUCCESS)
          {
            LOG_PRINT(LOG_MAJOR,"updateVersionActiveInactiveDnldedInSwMNodeTable Failed for dspId[%d]",availableReleasesRespPtr->slotId);
          }
          else
            LOG_PRINT(LOG_INFO,"updateVersionActiveInactiveDnldedInSwMNodeTable Success");
          //}
        }
      }//for

      gFirstDspAvailResp = TRUE;
      if ( (gCfgActAlarmBuf != NULL) && (((OamsCfgAfhSysAlarm*)gCfgActAlarmBuf)->sysAlarm.key2 == 3 || ((OamsCfgAfhSysAlarm*)gCfgActAlarmBuf)->sysAlarm.key2 == 4)  )
      { 
        LOG_PRINT(DEBUG,"gCfgActAlarmBuf NOT NULL -- Update Status as Activated");
        sendActivationAlarm(availableReleasesRespPtr);
      }
    }
    else if (availableReleasesRespPtr->slotId == 5 || availableReleasesRespPtr->slotId == 6)
    {
      for( index=0; index<MAX_DSP; index++)
      {
        if(index <2)
        {
          continue;
        }
        if(gDspInfo[index].isDspPresent == PRESENT)
        {
          sApiSwMNodeTableIndices.nodeIdentity = gDspInfo[index].dspId;
          sApiSwMNodeTableIndices.chasisFrameId = gDspInfo[index].frameID;
          sApiSwMNodeTableIndices.slotId = gDspInfo[index].slotID;
          //sApiSwMNodeTableIndices.slotId = slotId;
          sApiSwMNodeTableIndices.nodeType = availableReleasesRespPtr->nodeType;
          //if ( gFirstDspAvailResp == FALSE )
          // {
          //    LOG_PRINT(DEBUG,"GOING TO update DWLD version in  SWMNODE TABLE with Node Iden = %d SlotId = %d",sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.slotId);
          //    if (updateVersionDownloadedInSwMNodeTable( sApiSwMNodeTableIndices,
          //          availableReleasesRespPtr->availSwVersions[2]) != CLIB_SUCCESS)
          //    {
          //        LOG_PRINT(LOG_MAJOR,"updateVersionDownloadedInSwMNodeTable Failed for dspId[%d]",
          //           sApiSwMNodeTableIndices.nodeIdentity);
          //     }
          //     else
          //        LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success"); 

          /*if ( index == noOfDsp-1)
            gFirstDspAvailResp = TRUE;*/
          //}
          //else
          // {
          LOG_PRINT(DEBUG,"GOING TO update Act Inact DWNLD  SWMNODE TABLE with Node Iden = %d SlotId = %d",sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.slotId);
          if (updateVersionActiveInactiveDnldedInSwMNodeTable(
                sApiSwMNodeTableIndices,
                availableReleasesRespPtr->availSwVersions[0],
                availableReleasesRespPtr->availSwVersions[1],
                availableReleasesRespPtr->availSwVersions[2]) != CLIB_SUCCESS)
          {
            LOG_PRINT(LOG_MAJOR,"updateVersionActiveInactiveDnldedInSwMNodeTable Failed for dspId[%d]",availableReleasesRespPtr->slotId);
          }
          else
            LOG_PRINT(LOG_INFO,"updateVersionActiveInactiveDnldedInSwMNodeTable Success");
          //}
        }
      }//for

      gFirstDspAvailResp = FALSE;
      if ( gCfgActAlarmBuf != NULL && (((OamsCfgAfhSysAlarm*)gCfgActAlarmBuf)->sysAlarm.key2 == 5 || ((OamsCfgAfhSysAlarm*)gCfgActAlarmBuf)->sysAlarm.key2 == 6)  )
      { 
        LOG_PRINT(DEBUG,"gCfgActAlarmBuf NOT NULL -- Update Status as Activated");

        if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
        {
          LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
          return;
        }
        ((OamsCfgAfhSysAlarm*)gCfgActAlarmBuf)->sysAlarm.key2 = slotId; 
          sendActivationAlarm(availableReleasesRespPtr);
      }
    }//else if eic DSP
    
  }
  else if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_DSP  && availableReleasesRespPtr->availVersionResult != OPERATION_SUCCESS)
  {
    LOG_PRINT(LOG_MAJOR,"Available Release Query Response returned Failure");
  }
  sendUpgradeAlarm();

   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) gCfgState(%d) in dspAvailableReleasesRespHandler()",gAvailReleaseRspFlag,gCfgState); //CLOUD TMP PRINTS
  if (gAvailReleaseRspFlag == ZERO && gCfgState == CFG_BPM_SW_QUERY)
  {
    goToReadyState();
  }
}

/******************************* Function  Header*****************************
   Function Name : dspEicAvailableReleasesRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : populate SwM table with releases recieved from platform
for DSP
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
#if 0
I_Void dspEicAvailableReleasesRespHandler()
{
   OamOilCfgAvailableReleasesResp *availableReleasesRespPtr = NULL;
   OamOilCfgInfoAvailableVersion *bpmAvailVersion = (OamOilCfgInfoAvailableVersion *)gCfgMsgBuf;
   availableReleasesRespPtr = (OamOilCfgAvailableReleasesResp*)(&(bpmAvailVersion->swMAvailResp));
   SwMTableApi swMTableBuff;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   I_U32 count = 0 ;
   I_U8 dspId[MAX_DSP];
   I_U8 chasisFrameId[MAX_DSP];
   I_U16 outSize;
   I_U8 noOfDsp = 0, outCnt =0;
   I_U32 index = ZERO;
	 I_U32 i,nodeType =0;
	 I_S32 ret=0;
	 I_U8 chasisFrameId1,slotId;
   I_U32 eicDspStart =2 ;

   LOG_PRINT(LOG_INFO,"Received DSP AvailableReleasesResp for NodeType[%d], ChasisFrameId[%d], SlotId[%d]",availableReleasesRespPtr->nodeType,availableReleasesRespPtr->frameId,availableReleasesRespPtr->slotId);

   gAvailReleaseRspFlag--;

   LOG_PRINT(DEBUG,"Num of Available versions %d for nodetype %d",
         availableReleasesRespPtr->numVersion,availableReleasesRespPtr->nodeType );

   if (availableReleasesRespPtr->numVersion == ZERO)
   {
      LOG_PRINT(LOG_DEBUG,"No version present on the BSC Card for NodeType: %d",
            availableReleasesRespPtr->nodeType );
   }

   if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_DSP  && availableReleasesRespPtr->availVersionResult == OPERATION_SUCCESS)
   {
      nodeType = availableReleasesRespPtr->nodeType;

      if(deleteDataForNodeTypeFromSwMTable(&nodeType) != CLIB_SUCCESS)
      {
         LOG_PRINT(DEBUG,"deleteDataForNodeTypeFromSwMTable failed");
      }
 
      for (count = 0;count < 3;count++)
      { 
         LOG_PRINT(INFO,"Recieved swVersion: %s",availableReleasesRespPtr->availSwVersions[count]);    
         if (strlen(availableReleasesRespPtr->availSwVersions[count]) == ZERO)
         {
            LOG_PRINT(INFO,"No DSP release present for count: %d",count + 1);    
         }
         else
         {
            swMTableBuff.nodeType = availableReleasesRespPtr->nodeType;
            swMTableBuff.chasisFrameId = availableReleasesRespPtr->frameId;
            swMTableBuff.slotId = availableReleasesRespPtr->slotId;
            strcpy(swMTableBuff.swVersion,
                  availableReleasesRespPtr->availSwVersions[count]);
            memcpy(swMTableBuff.binaryPath,availableReleasesRespPtr->availSwBinaryPath[count],
                  OAMS_CMD_PARAM_MAX_SIZE); 
            swMTableBuff.swDownloadCount = ZERO;
            swMTableBuff.deletionInProgress = I_FALSE;
            if (insertSwMTable(&swMTableBuff) != CLIB_SUCCESS)
            {
               if ( updateSwMTable(&swMTableBuff ) != CLIB_SUCCESS )
                  LOG_PRINT(LOG_MAJOR,"updateSwMTable DB call is getting failed..");
            }
            else
               LOG_PRINT(LOG_INFO,"insertSwMTable Successful");           
         }

      }

      for( index=eicDspStart; index<MAX_DSP; index++)
      {
         if(gDspInfo[index].isDspPresent == PRESENT)
         {
				    sApiSwMNodeTableIndices.nodeIdentity = gDspInfo[index].dspId;
            sApiSwMNodeTableIndices.chasisFrameId = gDspInfo[index].frameID;
            sApiSwMNodeTableIndices.slotId = gDspInfo[index].slotID;
            //sApiSwMNodeTableIndices.slotId = slotId;
            sApiSwMNodeTableIndices.nodeType = availableReleasesRespPtr->nodeType;
            //if ( gFirstDspAvailResp == FALSE )
           // {
           //    LOG_PRINT(DEBUG,"GOING TO update DWLD version in  SWMNODE TABLE with Node Iden = %d SlotId = %d",sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.slotId);
           //    if (updateVersionDownloadedInSwMNodeTable( sApiSwMNodeTableIndices,
            //          availableReleasesRespPtr->availSwVersions[2]) != CLIB_SUCCESS)
           //    {
          //        LOG_PRINT(LOG_MAJOR,"updateVersionDownloadedInSwMNodeTable Failed for dspId[%d]",
          //           sApiSwMNodeTableIndices.nodeIdentity);
          //     }
          //     else
          //        LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success"); 
            
               /*if ( index == noOfDsp-1)
                  gFirstDspAvailResp = TRUE;*/
            //}
            //else
           // {
				     	LOG_PRINT(DEBUG,"GOING TO update Act Inact DWNLD  SWMNODE TABLE with Node Iden = %d SlotId = %d",sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.slotId);
               if (updateVersionActiveInactiveDnldedInSwMNodeTable(
                  sApiSwMNodeTableIndices,
                  availableReleasesRespPtr->availSwVersions[0],
                  availableReleasesRespPtr->availSwVersions[1],
                  availableReleasesRespPtr->availSwVersions[2]) != CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_MAJOR,"updateVersionActiveInactiveDnldedInSwMNodeTable Failed for dspId[%d]",availableReleasesRespPtr->slotId);
               }
               else
                  LOG_PRINT(LOG_INFO,"updateVersionActiveInactiveDnldedInSwMNodeTable Success");
          //}
        }
      }//for

      gFirstDspAvailResp = FALSE;
      if ( gCfgActAlarmBuf != NULL )
      { 
         LOG_PRINT(DEBUG,"gCfgActAlarmBuf NOT NULL -- Update Status as Activated");
         sendActivationAlarm(availableReleasesRespPtr);
      }
   }
   else if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_DSP  && availableReleasesRespPtr->availVersionResult != OPERATION_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"Available Release Query Response returned Failure");
   }
   sendUpgradeAlarm();

   if (gAvailReleaseRspFlag == ZERO && gCfgState == CFG_BPM_SW_QUERY)
   {
      goToReadyState();
   }
}
#endif
