#include <includes.h>

#define PRINT_TRUNKPORTTABLE(pTbl) do {\
          LOG_PRINT(INFO,"ChasisFrameId                = %d",pTbl->chasisFrameId); \
          LOG_PRINT(INFO,"SlotId                       = %d",pTbl->slotId);\
          LOG_PRINT(INFO,"TrunkPortId                  = %d",pTbl->trunkPortId);\
          LOG_PRINT(INFO,"TrunkType                    = %d",pTbl->trunkType);\
          LOG_PRINT(INFO,"TrunkFramingOption           = %d",pTbl->trunkFramingOption);\
          LOG_PRINT(INFO,"EncodeType                   = %d",pTbl->encodeType); \
          LOG_PRINT(INFO,"SigStrength                  = %d",pTbl->sigStrength);\
          LOG_PRINT(INFO,"LoopType                     = %d",pTbl->loopType);\
          LOG_PRINT(INFO,"Loopback                     = %d",pTbl->loopback); \
          LOG_PRINT(INFO,"AdminState                   = %d",pTbl->adminState);\
          LOG_PRINT(INFO,"UsageType                    = %d",pTbl->usageType); \
          LOG_PRINT(INFO,"OperatorControlledTrunkState = %d",pTbl->operatorControlledTrunkState);\
        } while (0)


CLEANDBTABLEIMPLEMENTATION(BicE1TeiMapTable)
CLEANDBTABLEIMPLEMENTATION(BicTable)

/*----------------------------------TC1---------------------------------------------*/
I_Void  fTPSrcCfgPreTC1() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;

  /* Populate Data in MccLinkResource Table */
  CALLCLEANDBTABLE(TrunkPortTable);
  CALLCLEANDBTABLE(MccLinkResourceTable);
  CALLCLEANDBTABLE(AbisTimeSlotPerTable);
  CALLCLEANDBTABLE(BicE1TeiMapTable);
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC1()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC1()
{
  return ;
}

I_Void fTPSrcCfgTC1(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC1();
  fTPSrcCfgStepsTC1();
  fTPSrcCfgPostTC1();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC2---------------------------------------------*/
I_Void  fTPSrcCfgPreTC2() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);
  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_NONE;
 
  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7;

  /* Populate Data in MccLinkResource Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  CALLCLEANDBTABLE(AbisTimeSlotPerTable);
  CALLCLEANDBTABLE(BicE1TeiMapTable);
  populateMccLinkResourceTable(50);
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC2()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC2()
{
  TrunkPortTableIndices inData = { 0 };
  TrunkPortTableApi *outData;
  E1PerTableApi      e1Data = {0};
  LOG_PRINT(INFO,"%s:",__func__);

  inData.chasisFrameId = 1;
  inData.slotId        = 3;
  inData.trunkPortId   = 0;

  if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) ) {
    PRINT_TRUNKPORTTABLE(outData);
    if (outData->usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7)
        TEST_RESULT =1;

    /* Revert Back UsageType In E1PerTable */
    e1Data.mapAction  = 2;
    e1Data.e1Category = 1;
    if(updateE1PerTable(&e1Data) != DBLIB_SUCCESS) 
    {
       LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
       return;
    }
    free(outData);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable fails",__func__);
  }
  return ;
}

I_Void fTPSrcCfgTC2(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC2();
  fTPSrcCfgStepsTC2();
  fTPSrcCfgPostTC2();
  return ;
}
/*-----------------------------------------------------------------------*/


/*----------------------------------TC3----------------------------------*/
I_Void  fTPSrcCfgPreTC3() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

  CALLCLEANDBTABLE(TrunkPortTable);

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->adminState    = 1;
  indata->usageType     = SYS_E1_USAGE_NONE;
 
  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7;
   
  /* CLEAN Data from MccLinkResource and AbisTimeSlotPer Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  CALLCLEANDBTABLE(AbisTimeSlotPerTable);
  CALLCLEANDBTABLE(BicE1TeiMapTable);

  /* Populate Data in MccLinkResource Table */
  populateMccLinkResourceTable(14);

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC3()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC3()
{
  return ;
}

I_Void fTPSrcCfgTC3(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC3();
  fTPSrcCfgStepsTC3();
  fTPSrcCfgPostTC3();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC4----------------------------------*/
I_Void  fTPSrcCfgPreTC4() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_NONE;
 
  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7;
   
  /* CLEAN Data from MccLinkResource and AbisTimeSlotPer Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  CALLCLEANDBTABLE(AbisTimeSlotPerTable);
  CALLCLEANDBTABLE(BicE1TeiMapTable);

  /* Populate Data in MccLinkResource Table */
  populateMccLinkResourceTable(5);

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC4()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC4()
{
  return ;
}

I_Void fTPSrcCfgTC4(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC4();
  fTPSrcCfgStepsTC4();
  fTPSrcCfgPostTC4();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC5----------------------------------*/
I_Void  fTPSrcCfgPreTC5() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);
  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_NONE;
 
  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7;
   
  /* CLEAN Data from MccLinkResource and AbisTimeSlotPer Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  CALLCLEANDBTABLE(AbisTimeSlotPerTable);
  CALLCLEANDBTABLE(BicE1TeiMapTable);

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC5()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC5()
{
  return ;
}

I_Void fTPSrcCfgTC5(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC5();
  fTPSrcCfgStepsTC5();
  fTPSrcCfgPostTC5();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC6----------------------------------*/
I_Void  fTPSrcCfgPreTC6() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);
  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_NONE;
 
  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7;
   
  /* CLEAN Data from MccLinkResource and AbisTimeSlotPer Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  CALLCLEANDBTABLE(AbisTimeSlotPerTable);
  CALLCLEANDBTABLE(BicE1TeiMapTable);

  /* Populate Data in MccLinkResource Table */
  populateMccLinkResourceTable(10);

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC6()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC6()
{
  return ;
}

I_Void fTPSrcCfgTC6(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC6();
  fTPSrcCfgStepsTC6();
  fTPSrcCfgPostTC6();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC7----------------------------------*/
I_Void  fTPSrcCfgPreTC7() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);
  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_NONE;
 
  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4;
   
  /* CLEAN Data from MccLinkResource and AbisTimeSlotPer Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  CALLCLEANDBTABLE(AbisTimeSlotPerTable);
  CALLCLEANDBTABLE(BicE1TeiMapTable);

  /* Populate Data in MccLinkResource Table */
  populateMccLinkResourceTable(15);

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC7()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC7()
{
  return ;
}

I_Void fTPSrcCfgTC7(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC7();
  fTPSrcCfgStepsTC7();
  fTPSrcCfgPostTC7();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC8----------------------------------*/
I_Void  fTPSrcCfgPreTC8() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  E1PerTableApi       e1Data = {0};
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

    /***** Update UsageType In E1PerTable*******/
    e1Data.usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7; 
    e1Data.mapAction  = 2;
    e1Data.e1Category = 1;
    if(updateE1PerTable(&e1Data) != DBLIB_SUCCESS) 
    {
       LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
       return;
    }
    /******************************************/

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_NONE;
   
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC8()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC8()
{
  TrunkPortTableIndices inData = { 0 };
  TrunkPortTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);

  inData.chasisFrameId = 1;
  inData.slotId        = 3;
  inData.trunkPortId   = 0;

  if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) ) {
    PRINT_TRUNKPORTTABLE(outData);
    if (outData->usageType = SYS_E1_USAGE_NONE)
        TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable fails",__func__);
  }

  return ;
}

I_Void fTPSrcCfgTC8(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC8();
  fTPSrcCfgStepsTC8();
  fTPSrcCfgPostTC8();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC9----------------------------------*/
I_Void  fTPSrcCfgPreTC9() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->adminState    = 1;
  indata->usageType     = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7;
  
  dbStatus = updateTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
 
  indata->usageType = SYS_E1_USAGE_NONE;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC9()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC9()
{
  return ;
}

I_Void fTPSrcCfgTC9(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC9();
  fTPSrcCfgStepsTC9();
  fTPSrcCfgPostTC9();
  return ;
}
/*-----------------------------------------------------------------------*/


/*----------------------------------TC10----------------------------------*/
I_Void  fTPSrcCfgPreTC10() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  BicTableApi         bicData;
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

  bicData.bicId  = 1;
  bicData.numTrx = 2;
  bicData.e1Id = 0;
  bicData.adminState = 1;

  dbStatus = insertBicTable( &bicData);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
 
  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType = SYS_E1_USAGE_NONE;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC10()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC10()
{
  CALLCLEANDBTABLE(BicTable);
  return ;
}

I_Void fTPSrcCfgTC10(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC10();
  fTPSrcCfgStepsTC10();
  fTPSrcCfgPostTC10();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC13----------------------------------*/
I_Void  fTPSrcCfgPreTC13() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  E1PerTableApi       e1Data = {0};
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

    /***** Update UsageType In E1PerTable*******/
    e1Data.mapAction  = 2;
    e1Data.e1Category = 1;
    e1Data.usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7; 
    if(updateE1PerTable(&e1Data) != DBLIB_SUCCESS) 
    {
       LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
       return;
    }
    /******************************************/

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC13()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC13()
{
  TrunkPortTableIndices inData = { 0 };
  TrunkPortTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);

  inData.chasisFrameId = 1;
  inData.slotId        = 3;
  inData.trunkPortId   = 0;

  if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) ) {
    PRINT_TRUNKPORTTABLE(outData);
    if (outData->usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4)
        TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable fails",__func__);
  }
  return ;
}

I_Void fTPSrcCfgTC13(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC13();
  fTPSrcCfgStepsTC13();
  fTPSrcCfgPostTC13();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC14----------------------------------*/
I_Void  fTPSrcCfgPreTC14() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  E1PerTableApi        e1Data = {0};
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

    /***** Update UsageType In E1PerTable*******/
    e1Data.mapAction  = 2;
    e1Data.e1Category = 1;
    e1Data.usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7; 
    if(updateE1PerTable(&e1Data) != DBLIB_SUCCESS) 
    {
       LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
       return;
    }
    /******************************************/

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->adminState    = 1;
  indata->usageType     = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7;
  
  dbStatus = updateTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }

  indata->usageType     = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC14()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC14()
{
  return ;
}

I_Void fTPSrcCfgTC14(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC14();
  fTPSrcCfgStepsTC14();
  fTPSrcCfgPostTC14();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC15----------------------------------*/
I_Void  fTPSrcCfgPreTC15() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  BicTableApi         bicData;
  E1PerTableApi       e1Data = {0};
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

    /***** Update UsageType In E1PerTable*******/
    e1Data.mapAction  = 2;
    e1Data.e1Category = 1;
    e1Data.usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7; 
    if(updateE1PerTable(&e1Data) != DBLIB_SUCCESS) 
    {
       LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
       return;
    }
    /******************************************/

  bicData.bicId  = 1;
  bicData.numTrx = 2;
  bicData.e1Id = 0;
  bicData.adminState = 1;

  dbStatus = insertBicTable( &bicData);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC15()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC15()
{
  CALLCLEANDBTABLE(BicTable);
  return ;
}

I_Void fTPSrcCfgTC15(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC15();
  fTPSrcCfgStepsTC15();
  fTPSrcCfgPostTC15();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC18----------------------------------*/
I_Void  fTPSrcCfgPreTC18() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  BicTableApi         bicData;
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_NONE;

  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_AIF;

  /* Populate Data in MccLinkResource Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  populateMccLinkResourceTableMTP2(10);
 
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC18()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC18()
{
  TrunkPortTableIndices inData = { 0 };
  TrunkPortTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);

  inData.chasisFrameId = 1;
  inData.slotId        = 3;
  inData.trunkPortId   = 0;

  if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) ) {
    PRINT_TRUNKPORTTABLE(outData);
    if (outData->usageType = SYS_E1_USAGE_AIF)
        TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable fails",__func__);
  }


  return ;
}

I_Void fTPSrcCfgTC18(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC18();
  fTPSrcCfgStepsTC18();
  fTPSrcCfgPostTC18();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC19----------------------------------*/
I_Void  fTPSrcCfgPreTC19() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  BicTableApi         bicData;
  E1PerTableApi       e1Data = {0};
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

    /***** Update UsageType In E1PerTable*******/
    e1Data.mapAction  = 2;
    e1Data.e1Category = 1;
    e1Data.usageType = SYS_E1_USAGE_NONE; 
    if(updateE1PerTable(&e1Data) != DBLIB_SUCCESS) 
    {
       LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
       return;
    }
    /******************************************/

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->adminState    = 1;
  indata->usageType     = SYS_E1_USAGE_NONE;

  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_AIF;

  /* Populate Data in MccLinkResource Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  populateMccLinkResourceTableMTP2(10);
 
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC19()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC19()
{
  return ;
}

I_Void fTPSrcCfgTC19(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC19();
  fTPSrcCfgStepsTC19();
  fTPSrcCfgPostTC19();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC23----------------------------------*/
I_Void  fTPSrcCfgPreTC23() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  BicTableApi         bicData;
  E1PerTableApi       e1Data = {0};
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

    /***** Update UsageType In E1PerTable*******/
    e1Data.mapAction  = 2;
    e1Data.e1Category = 1;
    e1Data.usageType = SYS_E1_USAGE_AIF; 
    if(updateE1PerTable(&e1Data) != DBLIB_SUCCESS) 
    {
       LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
       return;
    }
    /******************************************/

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->adminState    = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;

  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_NONE;

  /* Populate Data in MccLinkResource Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  populateMccLinkResourceTableMTP2(10);
 
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC23()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC23()
{
  TrunkPortTableIndices inData = { 0 };
  TrunkPortTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);

  inData.chasisFrameId = 1;
  inData.slotId        = 3;
  inData.trunkPortId   = 0;

  if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) ) {
    PRINT_TRUNKPORTTABLE(outData);
    if (outData->usageType = SYS_E1_USAGE_NONE)
        TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable fails",__func__);
  }

  return ;
}

I_Void fTPSrcCfgTC23(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC23();
  fTPSrcCfgStepsTC23();
  fTPSrcCfgPostTC23();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC24----------------------------------*/
I_Void  fTPSrcCfgPreTC24() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  BicTableApi         bicData;
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->adminState    = 1;
  indata->usageType     = SYS_E1_USAGE_AIF;

  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_NONE;

  /* Populate Data in MccLinkResource Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  populateMccLinkResourceTableMTP2(10);
 
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC24()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC24()
{
  return ;
}

I_Void fTPSrcCfgTC24(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC24();
  fTPSrcCfgStepsTC24();
  fTPSrcCfgPostTC24();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC25----------------------------------*/
I_Void  fTPSrcCfgPreTC25() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  BicTableApi         bicData;
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->adminState    = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;

  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_NONE;
  indata->adminState    = 1;

  /* Populate Data in MccLinkResource Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  populateMccLinkResourceTableMTP2(10);
 
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC25()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC25()
{
  return ;
}

I_Void fTPSrcCfgTC25(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC25();
  fTPSrcCfgStepsTC25();
  fTPSrcCfgPostTC25();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC26----------------------------------*/
I_Void  fTPSrcCfgPreTC26() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  BicTableApi         bicData;
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->adminState    = 0;
  indata->usageType     = SYS_E1_USAGE_NONE;

  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->adminState    = 1;

  /* Populate Data in MccLinkResource Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  populateMccLinkResourceTableMTP2(10);
 
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC26()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC26()
{
  return ;
}

I_Void fTPSrcCfgTC26(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC26();
  fTPSrcCfgStepsTC26();
  fTPSrcCfgPostTC26();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC27----------------------------------*/
I_Void  fTPSrcCfgPreTC27() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  LinkTableApi         linkTbl = {0};
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  /* Insert Row in linkTable */
  linkTbl.e1Num = 0;
  dbStatus = insertLinkTable(&linkTbl);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }

  /* Insert Row in TrunkPortTable */
  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->adminState    = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;

  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_NONE;

  /* Populate Data in MccLinkResource Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  populateMccLinkResourceTableMTP2(10);
 
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC27()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC27()
{
  CALLCLEANDBTABLE(LinkTable);
  return ;
}

I_Void fTPSrcCfgTC27(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC27();
  fTPSrcCfgStepsTC27();
  fTPSrcCfgPostTC27();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC28----------------------------------*/
I_Void  fTPSrcCfgPreTC28() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  TrunkTableApi         trunkTbl = {0};
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  CALLCLEANDBTABLE(TrunkPortTable);

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  /* Insert Row in TrunkTable */
  trunkTbl.e1Num = 0;
  dbStatus = insertTrunkTable(&trunkTbl);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }

  /* Insert Row in TrunkPortTable */
  indata = (TrunkPortTableApi *)(CmMsgPtr+1);

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->adminState    = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;

  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->usageType = SYS_E1_USAGE_NONE;

  /* Populate Data in MccLinkResource Table */
  CALLCLEANDBTABLE(MccLinkResourceTable);
  populateMccLinkResourceTableMTP2(10);
 
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC28()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC28()
{
  CALLCLEANDBTABLE(TrunkTable);
  return ;
}

I_Void fTPSrcCfgTC28(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC28();
  fTPSrcCfgStepsTC28();
  fTPSrcCfgPostTC28();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC29----------------------------------*/
I_Void  fTPSrcCfgPreTC29() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  TrunkTableApi         trunkTbl = {0};
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4;

  /* Populate Data in MccLinkResource Table */
  populateMccLinkResourceTable(30);
  CALLCLEANDBTABLE(AbisTimeSlotPerTable);
  CALLCLEANDBTABLE(BicE1TeiMapTable);
  CALLCLEANDBTABLE(LinkTable);
  CALLCLEANDBTABLE(TrunkTable);
 
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC29()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC29()
{
  TrunkPortTableIndices inData = { 0 };
  TrunkPortTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);

  inData.chasisFrameId = 1;
  inData.slotId        = 3;
  inData.trunkPortId   = 0;

  if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) ) {
    PRINT_TRUNKPORTTABLE(outData);
    if (outData->usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4)
        TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable fails",__func__);
  }
  return ;
}

I_Void fTPSrcCfgTC29(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC29();
  fTPSrcCfgStepsTC29();
  fTPSrcCfgPostTC29();
  return ;
}
/*-----------------------------------------------------------------------*/

/*----------------------------------TC30----------------------------------*/
I_Void  fTPSrcCfgPreTC30() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  E1PerTableApi        e1Data = {0};
  I_U32               dbStatus = 0;
   
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

    /***** Update UsageType In E1PerTable*******/
    e1Data.mapAction  = 2;
    e1Data.e1Category = 1;
    e1Data.usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7; 
    if(updateE1PerTable(&e1Data) != DBLIB_SUCCESS) 
    {
       LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
       return;
    }
    /******************************************/

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;

  /* Populate Data in MccLinkResource Table */
  populateMccLinkResourceTableMTP2(10);
 
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPSrcCfgStepsTC30()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPSrcCfgPostTC30()
{
  TrunkPortTableIndices inData = { 0 };
  TrunkPortTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);

  inData.chasisFrameId = 1;
  inData.slotId        = 3;
  inData.trunkPortId   = 0;

  if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) ) 
  {
    PRINT_TRUNKPORTTABLE(outData);
    if (outData->usageType = SYS_E1_USAGE_AIF)
        TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable fails",__func__);
  }

  return ;
}

I_Void fTPSrcCfgTC30(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPSrcCfgPreTC30();
  fTPSrcCfgStepsTC30();
  fTPSrcCfgPostTC30();
  return ;
}
/*-----------------------------------------------------------------------*/

I_PU8 TpUsgTestCaseDescription(I_U32 testCaseId) {
  switch (testCaseId) {
     case TEST_CASE1_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC1";
 
     case TEST_CASE2_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC2";

     case TEST_CASE3_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC3";

     case TEST_CASE4_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC4";

     case TEST_CASE5_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC5";

     case TEST_CASE6_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC6";

     case TEST_CASE7_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC7";

     case TEST_CASE8_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC8";

     case TEST_CASE9_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC9";

     case TEST_CASE10_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC10";

     case TEST_CASE11_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC11";

     case TEST_CASE12_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC12";

     case TEST_CASE13_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC13";

     case TEST_CASE14_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC14";

     case TEST_CASE15_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC15";

     case TEST_CASE16_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC16";

     case TEST_CASE17_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC17";

     case TEST_CASE18_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC18";

     case TEST_CASE19_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC19";

     case TEST_CASE20_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC20";

     case TEST_CASE21_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC21";
     case TEST_CASE22_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC22";
     case TEST_CASE23_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC23";
     case TEST_CASE24_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC24";
     case TEST_CASE25_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC25";
     case TEST_CASE26_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC26";
     case TEST_CASE27_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC27";
     case TEST_CASE28_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC28";
     case TEST_CASE29_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC29";
     case TEST_CASE30_TP_USG_CHG_CFG:
      return "Trunk Port Usage TC30";
     default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
  }
  return NULL;
}

I_Void ExecuteTpUsgGroup(I_U32 testCaseId) 
{
  switch (testCaseId)
  {
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
   case TEST_CASE_TP_USG_CHG_CFG_ALL: 
   case TEST_CASE1_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE1_TP_USG_CHG_CFG;
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC1();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE2_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE2_TP_USG_CHG_CFG;
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC2();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE3_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE3_TP_USG_CHG_CFG;
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC3();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE4_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE4_TP_USG_CHG_CFG;
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC4();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE5_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE5_TP_USG_CHG_CFG;
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC5();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE6_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE6_TP_USG_CHG_CFG;
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC6();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE7_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE7_TP_USG_CHG_CFG;
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC7();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE8_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE8_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC2();
      TEST_RESULT = 0;
      fTPSrcCfgTC8();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE9_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE9_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC2();
      TEST_RESULT = 0;
      fTPSrcCfgTC9();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE10_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE10_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC2();
      TEST_RESULT = 0;
      fTPSrcCfgTC10();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE11_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE11_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC2();
      TEST_RESULT = 0;
//      fTPSrcCfgTC11();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE12_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE12_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC2();
      TEST_RESULT = 0;
//      fTPSrcCfgTC12();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE13_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE13_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC2();
      TEST_RESULT = 0;
      fTPSrcCfgTC13();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE14_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE14_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC2();
      TEST_RESULT = 0;
      fTPSrcCfgTC14();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE15_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE15_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC2();
      TEST_RESULT = 0;
      fTPSrcCfgTC15();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE16_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE16_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fTPSrcCfgTC16();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE17_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE17_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fTPSrcCfgTC17();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE18_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE18_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC18();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE19_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE19_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC19();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE20_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE20_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
     // fTPSrcCfgTC20();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE21_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE21_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
     // fTPSrcCfgTC21();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE22_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE22_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
    //  fTPSrcCfgTC22();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE23_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE23_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC23();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE24_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE24_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC24();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE25_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE25_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC25();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE26_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE26_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC26();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE27_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE27_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC27();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE28_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE28_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC28();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE29_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE29_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC18();
      TEST_RESULT = 0;
      fTPSrcCfgTC29();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE30_TP_USG_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE30_TP_USG_CHG_CFG;
      TEST_RESULT = 0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPSrcCfgTC2();
      TEST_RESULT = 0;
      fTPSrcCfgTC30();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_USG_CHG_CFG_ALL != testCaseId ) {
        break;
      }
  }
  return ;
}

