/************************************************************* File Header ***
File Name      : oamscfg_ccuh_handler.c
Purpose        : This file contains function defintions required for handling
                 of ccu related requests.
Project        : BSC
Subsystem      : OAMS 
Author         : Aricent 
CSCI id        :
Version        :
 ******************************************************************** End ***/

#include "oamscfg_includes.h"

/******************************* Function  Header*****************************
   Function Name :    setCcConfigTable()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Set CcConfigTable request from OMC/CLI
Other Note    : Added For BSC CS4.0 CCU
*****************************************************************************/
I_Void  setCcConfigTable()
{
  CcConfigTableApi *receiveMsgPtr = NULL;
  CcConfigTableApi *ccConfigTableDbPtr = NULL;
  CcConfigTableIndices ccConfigTableIndex;
  I_Bool statusRange = FALSE;
  BicStatusTableIndices bicStatusTableIndex;
  BicStatusTableApi *bicStatusDbPtr = NULL;
  I_U32 bicId ;
  I_U32 applTei;
  I_U8 chasisFrameId,slotId;
  I_U32 swStatus;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  OamsCfgCcuhBicSetCcCfgReq bicSetCcCfgBuff ;

  
  memset(&bicSetCcCfgBuff,0,sizeof(OamsCfgCcuhBicSetCcCfgReq));
  receiveMsgPtr = (CcConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
  ccConfigTableIndex.ccuId = receiveMsgPtr->ccuId;
  if(CLIB_SUCCESS != getCcConfigTable(&ccConfigTableIndex, &ccConfigTableDbPtr))
  {
      LOG_PRINT(LOG_INFO, "No row exists in CcConfigTable Table ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
  }
  free(ccConfigTableDbPtr);
  LOG_PRINT(LOG_INFO, "Going to Check Range ");
  /* Perform Range Check on received Parameters */
  statusRange = ccConfigRangeChk(receiveMsgPtr); 
  if(!statusRange)
  {
       LOG_PRINT(LOG_INFO, "Send Nack to CM Range Check Fail ");
       cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
       return; 
  }
  
  /*Wrapper to get Bic Id on Basis of ccuId */
  LOG_PRINT(LOG_INFO, "Get BicId From BicCcInfoTable ");
  if(CLIB_SUCCESS != getBicIdFromBicCcInfoTable(receiveMsgPtr->ccuId,&bicId))
  {
      LOG_PRINT(LOG_INFO, "No row exists in BicCcInfoTable ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
  } 
  LOG_PRINT(LOG_INFO, "Received BicId From BicCcInfoTable : %d ",bicId);
  bicStatusTableIndex.bicId = bicId; 
 /* Check Bic Id is Connect or Not */
  LOG_PRINT(LOG_INFO, "Going to Check BIC is Connected or Not ");
  if(CLIB_SUCCESS != getBicStatusTable(&bicStatusTableIndex, &bicStatusDbPtr))
  {
      LOG_PRINT(LOG_INFO, "No row exists in BicStatusTable ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
  }
  if(bicStatusDbPtr->lapdLinkStatus != CONNECTED)
  { 
    LOG_PRINT(LOG_INFO, "Send Nack to CM BicId Not Connected ");
    cfgSendNackToCm(CM_ERR_BTS_NOT_CONNECTED);
    free(bicStatusDbPtr);
    return; 
  } 
  LOG_PRINT(LOG_INFO, "BicId is Connected ");
  free(bicStatusDbPtr);
  /* Get Active ChasisFrameId and SlotId */
    LOG_PRINT(LOG_INFO, "Going to get Active ChasisFrameId and SlotId ");
   if (getActiveIccSlotId(&chasisFrameId,&slotId)!=CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_CRITICAL,"getActive ChasisFrameId and slotId DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
   }
   /* Get Status of Bic From SwMNode Table */
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_BIC;
   sApiSwMNodeTableIndices.nodeIdentity = bicId;
   if (CLIB_SUCCESS == getSwStatusFromSwMNodeTable(sApiSwMNodeTableIndices,&swStatus))
   {
    LOG_PRINT(LOG_INFO,"get S/w Status DB call is getting SuccessFul.");
    if((swStatus == SW_ACTIVATION_IN_PROGRESS)||(swStatus == SW_DOWNLOAD_IN_PROGRESS))
    {
      LOG_PRINT(LOG_DEBUG,"Either Download or Activation is in progress ");
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
    }
    LOG_PRINT(LOG_INFO, "Either Download or Activation is not in progress ");

   }
    LOG_PRINT(LOG_INFO, "Going to get Tei Value ");
    
  /* Get Tei Value For Bic */
  if (getApplTei(SYS_NODE_TYPE_BIC,bicId,&applTei) !=CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"getApplTei DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
    LOG_PRINT(LOG_INFO, "Received Tei Value : %d ",applTei);
 
   /* Fill Structure to send Data */
   bicSetCcCfgBuff.bicId = bicId;
   bicSetCcCfgBuff.ccuId = receiveMsgPtr->ccuId;
   bicSetCcCfgBuff.applTei = applTei;
   bicSetCcCfgBuff.ccSocAlarmThresh = receiveMsgPtr->ccSocAlarmthreshold;
   bicSetCcCfgBuff.ccBatteryAgingAlarmLevel = receiveMsgPtr->batteryAgingAlarmLevel;
   bicSetCcCfgBuff.ccAgingBatNewBat = receiveMsgPtr->newBatteryInstalled;
   bicSetCcCfgBuff.ccHighTempLevel = receiveMsgPtr->highTempAlarmLevel;
   bicSetCcCfgBuff.ccNightModeLevel = receiveMsgPtr->nightModeLevel;
    LOG_PRINT(LOG_INFO, "Send Message to CCUH");
   
   cfgSendMessage((I_Void *)&bicSetCcCfgBuff, sizeof(OamsCfgCcuhBicSetCcCfgReq),
         ENT_OAMS_CCUH, OAMS_CFG_CCUH_BIC_SET_CC_CFG_REQ, 0);

  /*send SET Ack message to OMC */
  cfgSendAckToCm();
}



/******************************* Function  Header*****************************
  Function Name : ccConfigRangeChk()
Parameters    : CcConfigTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_CCCONFIGTABLE.
Other Note    : Added For BSC CS4.0 CCU
 *****************************************************************************/
I_Bool ccConfigRangeChk(CcConfigTableApi *receivedMsgPtr)
{
   LOG_PRINT(LOG_INFO, "ccConfigRangeChk : Entering in Function ");
   if((receivedMsgPtr->ccSocAlarmthreshold < 20) || (receivedMsgPtr->ccSocAlarmthreshold > 50))
   {
      LOG_PRINT(LOG_DEBUG,"ccConfigRangeChk : Range Check Failed - ccSocAlarmthreshold : %d",
            receivedMsgPtr->ccSocAlarmthreshold);
      return FALSE;
   }
   if((receivedMsgPtr->batteryAgingAlarmLevel < 80) || (receivedMsgPtr->batteryAgingAlarmLevel > 100))
   {
      LOG_PRINT(LOG_DEBUG,"ccConfigRangeChk : Range Check Failed - batteryAgingAlarmLevel : %d",
            receivedMsgPtr->batteryAgingAlarmLevel);
      return FALSE;
   }
   if((receivedMsgPtr->newBatteryInstalled != FALSE) && (receivedMsgPtr->newBatteryInstalled != TRUE))
   {
      LOG_PRINT(LOG_DEBUG,"ccConfigRangeChk : Range Check Failed - newBatteryInstalled : %d",
            receivedMsgPtr->newBatteryInstalled);
      return FALSE;
   }
   if((receivedMsgPtr->highTempAlarmLevel < 45) || (receivedMsgPtr->highTempAlarmLevel > 70))
   {
      LOG_PRINT(LOG_DEBUG,"ccConfigRangeChk : Range Check Failed - highTempAlarmLevel : %d",
            receivedMsgPtr->highTempAlarmLevel);
      return FALSE;
   }
   if((receivedMsgPtr->nightModeLevel < 20) || (receivedMsgPtr->nightModeLevel > 40))
   {
      LOG_PRINT(LOG_DEBUG,"ccConfigRangeChk : Range Check Failed - nightModeLevel : %d",
            receivedMsgPtr->nightModeLevel);
      return FALSE;
   }
   LOG_PRINT(LOG_INFO, "ccConfigRangeChk : Exiting in Function ");
   return TRUE;
}

/******************************* Function  Header*****************************
   Function Name :    setCcDataReqTable()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Set CcDataReqTable request from OMC/CLI
Other Note    : Added For BSC CS4.0 CCU
*****************************************************************************/
I_Void  setCcDataReqTable()
{
  CcDataReqTableApi *receiveMsgPtr = NULL;
  CcDataReqTableApi *ccDataReqTableDbPtr = NULL;
  CcDataReqTableIndices ccDataReqTableIndex;
  I_Bool statusRange = FALSE;
  BicStatusTableIndices bicStatusTableIndex;
  BicStatusTableApi *bicStatusDbPtr = NULL;
  I_U32 bicId ;
  I_U32 applTei;
  I_U8 chasisFrameId,slotId;
  I_U32 swStatus;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  OamsCfgCcuhBicCcDataReq bicSetCcDataBuff ;

  
  memset(&bicSetCcDataBuff,0,sizeof(OamsCfgCcuhBicCcDataReq));
  receiveMsgPtr = (CcDataReqTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
  ccDataReqTableIndex.ccuId = receiveMsgPtr->ccuId;
  if(CLIB_SUCCESS != getCcDataReqTable(&ccDataReqTableIndex, &ccDataReqTableDbPtr))
  {
      LOG_PRINT(LOG_INFO, "No row exists in CcDataReqTable ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
  }
  free(ccDataReqTableDbPtr);
  /* Perform Range Check on received Parameters */
  statusRange = ccDataReqRangeChk(receiveMsgPtr); 
  if(!statusRange)
  {
       cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
       return; 
  }
  
  /*Wrapper to get Bic Id on Basis of ccuId */
  if(CLIB_SUCCESS != getBicIdFromBicCcInfoTable(receiveMsgPtr->ccuId,&bicId))
  {
      LOG_PRINT(LOG_INFO, "No row exists in BicCcInfoTable ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
  }  
  LOG_PRINT(LOG_INFO, "Received BicId From BicCcInfoTable : %d ",bicId);
  bicStatusTableIndex.bicId = bicId; 
 /* Check Bic Id is Connect or Not */
  if(CLIB_SUCCESS != getBicStatusTable(&bicStatusTableIndex, &bicStatusDbPtr))
  {
      LOG_PRINT(LOG_INFO, "No row exists in BicStatusTable ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
  }
  if(bicStatusDbPtr->lapdLinkStatus != CONNECTED)
  { 
    LOG_PRINT(LOG_INFO, "Bic is Not Connected ");
    cfgSendNackToCm(CM_ERR_BTS_NOT_CONNECTED);
    free(bicStatusDbPtr);
    return; 
  } 
  LOG_PRINT(LOG_INFO, "Bic is Connected ");
  free(bicStatusDbPtr);
  /* Get Active ChasisFrameId and SlotId */
   if (getActiveIccSlotId(&chasisFrameId,&slotId)!=CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_CRITICAL,"getActive ChasisFrameId and slotId DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
   }
   /* Get Status of Bic From SwMNode Table */
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_BIC;
   sApiSwMNodeTableIndices.nodeIdentity = bicId;
   if (CLIB_SUCCESS == getSwStatusFromSwMNodeTable(sApiSwMNodeTableIndices,&swStatus))
   {
    LOG_PRINT(LOG_INFO,"get S/w Status DB call is getting SuccessFul.");
    if((swStatus == SW_ACTIVATION_IN_PROGRESS)||(swStatus == SW_DOWNLOAD_IN_PROGRESS))
    {
      LOG_PRINT(LOG_DEBUG,"Either Download or Activation is in progress ");
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
    }

   }


  /* Get Tei Value For Bic */
  if (getApplTei(SYS_NODE_TYPE_BIC,bicId,&applTei) !=CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"getApplTei DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
    LOG_PRINT(LOG_INFO, "Received Tei Value : %d ",applTei);

 
   /* Fill Structure to send Data */
   bicSetCcDataBuff.bicId = bicId;
   bicSetCcDataBuff.ccuId = receiveMsgPtr->ccuId;
   bicSetCcDataBuff.applTei = applTei;
   bicSetCcDataBuff.ccDataSetId = receiveMsgPtr->dataSetId;
   bicSetCcDataBuff.ccSampleInterv = receiveMsgPtr->sampleInterv;
   bicSetCcDataBuff.ccReportInterv = receiveMsgPtr->numChargeDataSets;
   bicSetCcDataBuff.ccPeriodicReporting = receiveMsgPtr->periodicReporting;
      
   cfgSendMessage((I_Void *)&bicSetCcDataBuff, sizeof(OamsCfgCcuhBicCcDataReq),
         ENT_OAMS_CCUH, OAMS_CFG_CCUH_BIC_CC_DATA_REQ, 0);

  /*send SET Ack message to OMC */
  cfgSendAckToCm();
}

/******************************* Function  Header*****************************
  Function Name : ccDataReqRangeChk()
Parameters    : CcConfigTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_CCDATAREQTABLE.
Other Note    : Added For BSC CS4.0 CCU
 *****************************************************************************/
I_Bool ccDataReqRangeChk(CcDataReqTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->sampleInterv < 1) || (receivedMsgPtr->sampleInterv > 720))
   {
      LOG_PRINT(LOG_DEBUG,"ccDataReqRangeChk : Range Check Failed - sampleInterv : %d",
            receivedMsgPtr->sampleInterv);
      return FALSE;
   }
   if((receivedMsgPtr->numChargeDataSets < 1) || (receivedMsgPtr->numChargeDataSets >24))
   {
      LOG_PRINT(LOG_DEBUG,"ccDataReqRangeChk : Range Check Failed - numChargeDataSets : %d",
            receivedMsgPtr->numChargeDataSets);
      return FALSE;
   }
   if((receivedMsgPtr->periodicReporting != START) && (receivedMsgPtr->periodicReporting != STOP))
   {
      LOG_PRINT(LOG_DEBUG,"ccDataReqRangeChk : Range Check Failed - periodicReporting : %d",
            receivedMsgPtr->periodicReporting);
      return FALSE;
   }

   return TRUE;
}

/*BSC R2.0 Changes Starts*/
#if 0
/******************************* Function  Header*****************************
   Function Name :    setBicPowerOrderTable()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Set BicPowerOrderTable request from OMC/CLI
Other Note    : Added For BSC CS4.0 CCU
*****************************************************************************/
I_Void  setBicPowerOrderTable()
{
  BicPowerOrderTableApi *receiveMsgPtr = NULL;
  BicPowerOrderTableApi *bicPowerOrderTableDbPtr = NULL;
  BicPowerOrderTableIndices bicPowerOrderTableIndex;
  I_Bool statusRange = FALSE;
  BicStatusTableIndices bicStatusTableIndex;
  BicStatusTableApi *bicStatusDbPtr = NULL;
  I_U32 ccuId ;
  I_U8 chasisFrameId,slotId;
  I_U32 swStatus;
  I_S32 status;
  I_U32 applTei;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  OamsCfgBichBicPowerOrderReq bicPowerOrderDataBuff ;

  memset(&bicPowerOrderDataBuff,0,sizeof(OamsCfgBichBicPowerOrderReq));
  receiveMsgPtr = (BicPowerOrderTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
     
  bicStatusTableIndex.bicId = receiveMsgPtr->bicId; 
 /* Check Bic Id is Connect or Not */

  LOG_PRINT(LOG_INFO, "Going to Get BicID from BicStatusTable ");
  if(CLIB_SUCCESS != getBicStatusTable(&bicStatusTableIndex, &bicStatusDbPtr))
  {
      LOG_PRINT(LOG_INFO, "No row exists in BicStatusTable ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
  }
#if 0
  if(bicStatusDbPtr->connectionState != CONNECTED)
  { 
    LOG_PRINT(LOG_INFO, "Bic is Not Connected ");
    cfgSendNackToCm(CM_ERR_BTS_NOT_CONNECTED);
    free(bicStatusDbPtr);
    return; 
  } 
  LOG_PRINT(LOG_INFO, "Bic is Connected ");
#endif
  free(bicStatusDbPtr);
  /* Get Active ChasisFrameId and SlotId */
   if (getActiveIccSlotId(&chasisFrameId,&slotId)!=CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_CRITICAL,"getActive ChasisFrameId and slotId DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
   }
   /* Get Status of Bic From SwMNode Table */
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_BIC;
   sApiSwMNodeTableIndices.nodeIdentity = receiveMsgPtr->bicId;
   if (CLIB_SUCCESS == getSwStatusFromSwMNodeTable(sApiSwMNodeTableIndices,&swStatus))
   {
    LOG_PRINT(LOG_INFO,"get S/w Status DB call is getting SuccessFul.");
    if((swStatus == SW_ACTIVATION_IN_PROGRESS)||(swStatus == SW_DOWNLOAD_IN_PROGRESS))
    {
      LOG_PRINT(LOG_DEBUG,"Either Download or Activation is in progress ");
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
    }

   }

   /* Perform Range Check on received Parameters */
  statusRange = bicPowerOrderRangeChk(receiveMsgPtr); 
  if(!statusRange)
  {
       cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
       return; 
  }

   bicPowerOrderTableIndex.bicId = receiveMsgPtr->bicId;
  status = getBicPowerOrderTable(&bicPowerOrderTableIndex, &bicPowerOrderTableDbPtr); 
  if(CLIB_SUCCESS != status)
  {
      LOG_PRINT(LOG_INFO, "No row exists in BicPowerOrderTable ");
      LOG_PRINT(LOG_INFO, " Insert Row in DB ");
      if(CLIB_SUCCESS != insertBicPowerOrderTable(receiveMsgPtr))
      {
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
         return;
      }
  }
  else if (CLIB_SUCCESS == status)
  {
    LOG_PRINT(LOG_INFO, "Row exists in BicPowerOrderTable ");
    free(bicPowerOrderTableDbPtr);
    LOG_PRINT(LOG_INFO, " Update Row in DB ");
    if(CLIB_SUCCESS != updateBicPowerOrderTable(receiveMsgPtr))
    {
       cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
       return;
   }
  }


   /* Get Tei Value For Bic */
  if (getApplTei(SYS_NODE_TYPE_BIC,receiveMsgPtr->bicId,&applTei) !=CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"getApplTei DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
    LOG_PRINT(LOG_INFO, "Received Tei Value : %d ",applTei);

     /* Fill Structure to send Data */
   bicPowerOrderDataBuff.bicId =receiveMsgPtr->bicId;
   bicPowerOrderDataBuff.bicTei =applTei;
   bicPowerOrderDataBuff.pwrActionType = receiveMsgPtr->pwrAction;
   bicPowerOrderDataBuff.pwrEntity = receiveMsgPtr->pwrEntity;
   cfgSendMessage((I_Void *)&bicPowerOrderDataBuff, sizeof(OamsCfgBichBicPowerOrderReq),
         ENT_OAMS_BICH, OAMS_CFG_BICH_BIC_PWR_ORD_DATA_REQ, 0);
   /*send SET Ack message to OMC */

   cfgSendAckToCm();
}

/******************************* Function  Header*****************************
  Function Name : bicPowerOrderRangeChk()
Parameters    : BicPowerOrderTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_BICPOWERORDERTABLE.
Other Note    : Added For BSC CS4.0 CCU
 *****************************************************************************/
I_Bool bicPowerOrderRangeChk(BicPowerOrderTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->bicId < 1) || (receivedMsgPtr->bicId > 4294967295))
   {
      LOG_PRINT(LOG_DEBUG,"bicPowerOrderRangeChk : Range Check Failed - bicId : %d",
            receivedMsgPtr->bicId);
      return FALSE;
   }
   if((receivedMsgPtr->pwrAction != POWER_OFF) && (receivedMsgPtr->pwrAction != POWER_ON))
   {
      LOG_PRINT(LOG_DEBUG,"bicPowerOrderRangeChk : Range Check Failed - pwrAction : %d",
            receivedMsgPtr->pwrAction);
      return FALSE;
   }
   if((receivedMsgPtr->pwrEntity != ALL_TRX) && (receivedMsgPtr->pwrEntity != WHOLE_SITE_EXCEPT_BIC_N_TRANSMISSION) && (receivedMsgPtr->pwrEntity != WHOLE_SITE_EXCEPT_BIC))
   {
      LOG_PRINT(LOG_DEBUG,"bicPowerOrderRangeChk : Range Check Failed - pwrEntity : %d",
            receivedMsgPtr->pwrEntity);
      return FALSE;
   }

   return TRUE;
}

#endif
/*BSC R2.0 Changes Ends*/

/******************************* Function  Header*****************************
   Function Name :    setCcPowerOrderTable()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Set CcPowerOrderTable request from OMC/CLI
Other Note    : Added For BSC CS4.0 CCU
*****************************************************************************/
I_Void  setCcPowerOrderTable()
{
  CcPowerOrderTableApi *receiveMsgPtr = NULL;
  CcPowerOrderTableApi *ccPowerOrderTableDbPtr = NULL;
  CcPowerOrderTableIndices ccPowerOrderTableIndex;
  I_Bool statusRange = FALSE;
  BicStatusTableIndices bicStatusTableIndex;
  BicStatusTableApi *bicStatusDbPtr = NULL;
  I_U32 bicId ;
  I_U8 chasisFrameId,slotId;
  I_U32 swStatus;
  I_U32 applTei;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  OamsCfgCcuhBicCcPwrOrderReq ccPowerOrderDataBuff ;

  
  memset(&ccPowerOrderDataBuff,0,sizeof(OamsCfgCcuhBicCcPwrOrderReq));
  receiveMsgPtr = (CcPowerOrderTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
  /*Wrapper to get Bic Id on Basis of ccuId */
  LOG_PRINT(LOG_INFO, "Get Bic ID From BicCcInfoTable ");
  if(CLIB_SUCCESS != getBicIdFromBicCcInfoTable(receiveMsgPtr->ccuId,&bicId))
  {
      LOG_PRINT(LOG_INFO, "No row exists in BicCcInfoTable ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
  }  
   
  LOG_PRINT(LOG_INFO, "Received BicId From BicCcInfoTable : %d ",bicId);
  bicStatusTableIndex.bicId = bicId; 
 /* Check Bic Id is Connect or Not */
  if(CLIB_SUCCESS != getBicStatusTable(&bicStatusTableIndex, &bicStatusDbPtr))
  {
      LOG_PRINT(LOG_INFO, "No row exists in BicStatusTable ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
  }
  if(bicStatusDbPtr->lapdLinkStatus != CONNECTED)
  { 
    LOG_PRINT(LOG_INFO,"Bic Is Not Connected");
    cfgSendNackToCm(CM_ERR_BTS_NOT_CONNECTED);
    free(bicStatusDbPtr);
    return; 
  } 
  LOG_PRINT(LOG_INFO,"Bic Is Connected");
  free(bicStatusDbPtr);
  /* Get Active ChasisFrameId and SlotId */
   if (getActiveIccSlotId(&chasisFrameId,&slotId)!=CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_CRITICAL,"getActive ChasisFrameId and slotId DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
   }
   /* Get Status of Bic From SwMNode Table */
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_BIC;
   sApiSwMNodeTableIndices.nodeIdentity = bicId;
   if (CLIB_SUCCESS == getSwStatusFromSwMNodeTable(sApiSwMNodeTableIndices,&swStatus))
   {
    LOG_PRINT(LOG_INFO,"get S/w Status DB call is getting SuccessFul.");
    if((swStatus == SW_ACTIVATION_IN_PROGRESS)||(swStatus == SW_DOWNLOAD_IN_PROGRESS))
    {
      LOG_PRINT(LOG_DEBUG,"Either Download or Activation is in progress ");
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
    }

   }

   /* Perform Range Check on received Parameters */
  statusRange = ccPowerOrderRangeChk(receiveMsgPtr); 
  if(!statusRange)
  {
       cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
       return; 
  }
  
   /* Get Tei Value For Bic */
  if (getApplTei(SYS_NODE_TYPE_BIC,bicId,&applTei) !=CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"getApplTei DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
    LOG_PRINT(LOG_INFO, "Received Tei Value : %d ",applTei);
 
     /* Fill Structure to send Data */
   ccPowerOrderDataBuff.ccuId = receiveMsgPtr->ccuId;
   ccPowerOrderDataBuff.applTei = applTei;
   ccPowerOrderDataBuff.pwrRestartTime = receiveMsgPtr->pwrRestartTime;
   
   cfgSendMessage((I_Void *)&ccPowerOrderDataBuff, sizeof(OamsCfgCcuhBicCcPwrOrderReq),
         ENT_OAMS_CCUH, OAMS_CFG_CCUH_BIC_CC_PWR_ORDER_REQ, 0);
   /*send SET Ack message to OMC */
   cfgSendAckToCm();
}

/******************************* Function  Header*****************************
  Function Name : ccPowerOrderRangeChk()
Parameters    : CcPowerOrderTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_CCPOWERORDERTABLE.
Other Note    : Added For BSC CS4.0 CCU
 *****************************************************************************/
I_Bool ccPowerOrderRangeChk(CcPowerOrderTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->ccuId < 1) || (receivedMsgPtr->ccuId > 4294967295))
   {
      LOG_PRINT(LOG_DEBUG,"ccPowerOrderRangeChk : Range Check Failed - ccuId : %d",
            receivedMsgPtr->ccuId);
      return FALSE;
   }
   if((receivedMsgPtr->pwrRestartTime < 0 ) || (receivedMsgPtr->pwrRestartTime >7200 ))
   {
      LOG_PRINT(LOG_DEBUG,"ccPowerOrderRangeChk : Range Check Failed - pwrRestartTime : %d",
            receivedMsgPtr->pwrRestartTime);
      return FALSE;
   }
   
   return TRUE;
}
