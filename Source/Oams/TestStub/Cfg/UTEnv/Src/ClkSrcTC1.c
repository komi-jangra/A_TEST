#include <includes.h>
#if 0
#define FILL_SYS_HDR(m , o, s, sp, se, si , dp, de, di) {\
((SysHdr *)(m)) ->msgType = o;\
((SysHdr *)(m)) ->subType = s;\
((SysHdr *)(m)) ->src.prcr = sp;\
((SysHdr *)(m)) ->src.entity = (I_U8)se;\
((SysHdr *)(m)) ->src.clsId = 1;\
((SysHdr *)(m)) ->src.rfu = 0;\
((SysHdr *)(m)) ->src.inst = (I_S32)si;\
((SysHdr *)(m)) ->dest.prcr = dp;\
((SysHdr *)(m)) ->dest.entity = (I_U8)de;\
((SysHdr *)(m)) ->dest.clsId = 1;\
((SysHdr *)(m)) ->dest.rfu = 0;\
((SysHdr *)(m)) ->dest.inst = (I_S32)di;\
}
#endif 

#define FILL_CLKSOURCECONFIGTABLE(pTbl,FrmId,Num,s1,t1,p1,s2,t2,p2,s3,t3,p3,s4,t4,p4,s5,t5,p5) do {\
          pTbl->index          = 0;\
          pTbl->chasisFrameId  = FrmId; \
          pTbl->totalNumClkSrc = Num;\
          pTbl->slotId1        =s1 ;\
          pTbl->trunkPortId1   =t1;\
          pTbl->clkPriority1   =p1;\
          pTbl->slotId2        =s2;\
          pTbl->trunkPortId2   =t2;\
          pTbl->clkPriority2   =p2;\
          pTbl->slotId3        =s3;\
          pTbl->trunkPortId3   =t3;\
          pTbl->clkPriority3   =p3;\
          pTbl->slotId4        =s4;\
          pTbl->trunkPortId4   =t4;\
          pTbl->clkPriority4   =p4;\
          pTbl->slotId5        =s5;\
          pTbl->trunkPortId5   =t5;\
          pTbl->clkPriority5   =p5;\
        } while (0)

#define PRINT_CLKSOURCECONFIGTABLE(pTbl) do {\
          LOG_PRINT(INFO,"index = %d",pTbl->index) ;\
          LOG_PRINT(INFO,"chasisFrameId = %d",pTbl->chasisFrameId); \
          LOG_PRINT(INFO,"totalNumClkSrc = %d",pTbl->totalNumClkSrc);\
          LOG_PRINT(INFO,"slotId1 = %d",pTbl->slotId1);\
          LOG_PRINT(INFO,"trunkPortId1 = %d",pTbl->trunkPortId1);\
          LOG_PRINT(INFO,"clkPriority1 = %d",pTbl->clkPriority1); \
          LOG_PRINT(INFO,"slotId2 = %d",pTbl->slotId2);\
          LOG_PRINT(INFO,"trunkPortId2 = %d",pTbl->trunkPortId2);\
          LOG_PRINT(INFO,"clkPriority2 = %d",pTbl->clkPriority2); \
          LOG_PRINT(INFO,"slotId3 = %d",pTbl->slotId3);\
          LOG_PRINT(INFO,"trunkPortId3 = %d",pTbl->trunkPortId3);\
          LOG_PRINT(INFO,"clkPriority3 = %d",pTbl->clkPriority3); \
          LOG_PRINT(INFO,"slotId4 = %d",pTbl->slotId4);\
          LOG_PRINT(INFO,"trunkPortId4 = %d",pTbl->trunkPortId4);\
          LOG_PRINT(INFO,"clkPriority4 = %d",pTbl->clkPriority4); \
          LOG_PRINT(INFO,"slotId5 = %d",pTbl->slotId5);\
          LOG_PRINT(INFO,"trunkPortId5 = %d",pTbl->trunkPortId5);\
          LOG_PRINT(INFO,"clkPriority5 = %d",pTbl->clkPriority5); \
        } while (0)

CLEANDBTABLEIMPLEMENTATION(ClkSourceConfigTable)

I_Void  clean_trunk_port_talbe(I_Void)
{
  TrunkPortTableApi *outData;
  I_U32 outRows, i; 
  I_U16 outSize;
  TrunkPortTableIndices key;
  
  if (CLIB_SUCCESS == getallTrunkPortTable(&outData,&outRows,&outSize) ) {
    for (i=0 ; i < outRows; i++ ) {
      key.chasisFrameId = ((TrunkPortTableApi *) (outData + i*outSize))->chasisFrameId;
      key.slotId = ((TrunkPortTableApi *) (outData + i*outSize))->slotId;
      key.trunkPortId = ((TrunkPortTableApi *) (outData + i*outSize))->trunkPortId;
      deleteTrunkPortTable(&key);
    }
    free(outData);
  }   
  return;
}

I_Void fill_trunk_port_talbe(I_U8 clean_req, I_U16 trunkPortId, I_U32 trunkType, I_U32 operatorControlledTrunkState)
{
  TrunkPortTableApi TrunkPortTable;
 
  if (clean_req) clean_trunk_port_talbe();
  
  TrunkPortTable.chasisFrameId = 0;
  TrunkPortTable.slotId = 0;
  TrunkPortTable.trunkPortId = trunkPortId;
  TrunkPortTable.trunkType = trunkType;
  TrunkPortTable.trunkFramingOption = 0;
  TrunkPortTable.encodeType = 0;
  TrunkPortTable.sigStrength = 0;
  TrunkPortTable.operatorControlledTrunkState = operatorControlledTrunkState;

  if ( CLIB_SUCCESS != insertTrunkPortTable(&TrunkPortTable) ) {
    LOG_PRINT(CRITICAL,"%s:insertTrunkPortTable fails",__func__);
  }
  return;  
}

I_Void cleanMappingTrunk2E1()
{
  E1PerTableApi *E1PerTable;
  I_U32 i;
  
  for (i=0; i < 4; i++) {
    E1PerTableIndices Key = { i };
    if (CLIB_SUCCESS == getE1PerTable( &Key, &E1PerTable) ) {
      E1PerTable->trunkPortId= 0xFF;
      updateE1PerTable(E1PerTable);
      free(E1PerTable);
    }
    else 
    {
      LOG_PRINT(CRITICAL,"%s:getE1PerTable fails",__func__);    
    }
  }
}
I_Void  createMappingTrunk2E1(I_U16 TrunkPortId, I_U32 E1Num)
{
  E1PerTableApi *E1PerTable;
  E1PerTableIndices Key = { E1Num };
  I_U32 i;
  if (CLIB_SUCCESS == getE1PerTable( &Key, &E1PerTable) ) {
    E1PerTable->trunkPortId = TrunkPortId;
    updateE1PerTable(E1PerTable);
    free(E1PerTable);
  }
  else 
  {
    LOG_PRINT(CRITICAL,"%s:getE1PerTable fails",__func__);    
  }
}

/*----------------------------------TC1---------------------------------------------*/

// Send Clock Sources which Exceeds the number of supported Clock Sources
I_Void fClkSrcCfgPreTC1(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,6,0,0,0,0,1,1,0,2,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC1(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_CLK_SRC_CFG_COUNT_INVALID) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC1(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void fClkSrcCfgTC1(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC1();
  fClkSrcCfgStepsTC1();
  fClkSrcCfgPostTC1();
  return ;
}


/*----------------------------------TC2---------------------------------------------*/
//Send Clock Source which does not exits in TrunkPort Table
I_Void fClkSrcCfgPreTC2(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC2(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_TRUNK_ID_NOT_PRESENT_IN_DB) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC2(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void fClkSrcCfgTC2(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC2();
  fClkSrcCfgStepsTC2();
  fClkSrcCfgPostTC2();
  return ;
}


/*----------------------------------TC3---------------------------------------------*/
//Send Clock Source for which mapping does not exits
I_Void fClkSrcCfgPreTC3(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  cleanMappingTrunk2E1(); 
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC3(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_E1_MAP_NOT_CREATED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC3(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void fClkSrcCfgTC3(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC3();
  fClkSrcCfgStepsTC3();
  fClkSrcCfgPostTC3();
  return ;
}

/*----------------------------------TC4---------------------------------------------*/
//Send Clock Source which is mapped to Abis Interface E1

I_Void fClkSrcCfgPreTC4(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,2/*E1Num*/); //MAP to Abis E1Num
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC4(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_E1_IS_NOT_A_INTERFACE_TYPE) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC4(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void fClkSrcCfgTC4(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC4();
  fClkSrcCfgStepsTC4();
  fClkSrcCfgPostTC4();
  return ;
}

/*----------------------------------TC5---------------------------------------------*/
//Clock Source configuration is rejected by the platform

I_Void fClkSrcCfgPreTC5(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,1/*E1Num*/); 
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC5(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status != CM_SUCCESS) {
          TEST_RESULT=0;
        }
        break;
      case OAMS_CFG_OIL_SET_CLK_SRC_REQ:
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_OIL_SET_CLK_SRC_REQ [%d] ", OAMS_CFG_OIL_SET_CLK_SRC_REQ);
        ExecuteOilAction(RCVD_MSG_PTR);
      break;  
      case OAMS_CFG_AFH_ALARM_IND :
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_AFH_ALARM_IND[%d] ", OAMS_CFG_AFH_ALARM_IND);        
        if ( ((OamsCfgAfhSysAlarm *)RCVD_MSG_PTR)->sysAlarm.sysalarmId == EVENT_CLOCK_SRC_CFG_FAILED) {
          TEST_RESULT = 1;
        }
        return ;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC5(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void fClkSrcCfgTC5(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC5();
  fClkSrcCfgStepsTC5();
  fClkSrcCfgPostTC5();
  return ;
}

/*----------------------------------TC6---------------------------------------------*/
//Send Clock Source Configuration and it is accepted by the platform
I_Void fClkSrcCfgPreTC6(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,1/*E1Num*/);
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC6(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status != CM_SUCCESS) {
          TEST_RESULT=0;
        }
        break;
      case OAMS_CFG_OIL_SET_CLK_SRC_REQ:
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_OIL_SET_CLK_SRC_REQ [%d] ", OAMS_CFG_OIL_SET_CLK_SRC_REQ);
        ExecuteOilAction(RCVD_MSG_PTR);
      break;  
      case OAMS_CFG_AFH_ALARM_IND :
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_AFH_ALARM_IND[%d] ", OAMS_CFG_AFH_ALARM_IND);        
        if ( ((OamsCfgAfhSysAlarm *)RCVD_MSG_PTR)->sysAlarm.sysalarmId == EVENT_CLOCK_SRC_CFG_SUCCESSFUL) {
          TEST_RESULT = 1;
        }
        else {
          TEST_RESULT = 0;
        }
        return ;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC6(I_Void)
{
  ClkSourceConfigTableIndices inData = { 0 };
  ClkSourceConfigTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);
  if (CLIB_SUCCESS == getClkSourceConfigTable( &inData, &outData) ) {
    PRINT_CLKSOURCECONFIGTABLE(outData);
    if (outData->totalNumClkSrc = 1) TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    TEST_RESULT=0;
    LOG_PRINT(CRITICAL," [%s]:getClkSourceConfigTable fails",__func__);
  }
  return ;
}

I_Void fClkSrcCfgTC6(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC6();
  fClkSrcCfgStepsTC6();
  fClkSrcCfgPostTC6();
  return ;
}


/*----------------------------------TC7---------------------------------------------*/
//Send 2 Clock Sources one is OK Clock Source and One Clock Source does not exists in DB
I_Void fClkSrcCfgPreTC7(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,2,0,1,1,0,2,2,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC7(I_Void)
{
  I_U32 alarm_count = 0;
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status != CM_SUCCESS) {
          TEST_RESULT=0;
        }
        break;
      case OAMS_CFG_OIL_SET_CLK_SRC_REQ:
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_OIL_SET_CLK_SRC_REQ [%d] ", OAMS_CFG_OIL_SET_CLK_SRC_REQ);
        ExecuteOilAction(RCVD_MSG_PTR);
      break;  
      case OAMS_CFG_AFH_ALARM_IND :
        alarm_count++;
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_AFH_ALARM_IND[%d] ", OAMS_CFG_AFH_ALARM_IND);        
        if ( ((OamsCfgAfhSysAlarm *)RCVD_MSG_PTR)->sysAlarm.sysalarmId == EVENT_CLOCK_SRC_CFG_SUCCESSFUL) {
          TEST_RESULT = TEST_RESULT;
        }
        if (alarm_count == 2) {
          return ;
        }
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC7(I_Void)
{
  ClkSourceConfigTableIndices inData = { 0 };
  ClkSourceConfigTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);
  if (CLIB_SUCCESS == getClkSourceConfigTable( &inData, &outData) ) {
    PRINT_CLKSOURCECONFIGTABLE(outData);
    if (outData->totalNumClkSrc = 1) TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    TEST_RESULT = 0;
    LOG_PRINT(CRITICAL," [%s]:getClkSourceConfigTable fails",__func__);
  }
  return ;
}

I_Void fClkSrcCfgTC7(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC7();
  fClkSrcCfgStepsTC7();
  fClkSrcCfgPostTC7();
  return ;
}

/*----------------------------------TC8---------------------------------------------*/
//Configure 2 Clock Sources and both are OK

I_Void fClkSrcCfgPreTC8(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  fill_trunk_port_talbe(FALSE, 2 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,2,0,1,1,0,2,3,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC8(I_Void)
{
  I_U32 alarm_count = 0;
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status != CM_SUCCESS) {
          TEST_RESULT=0;
        }
        break;
      case OAMS_CFG_OIL_SET_CLK_SRC_REQ:
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_OIL_SET_CLK_SRC_REQ [%d] ", OAMS_CFG_OIL_SET_CLK_SRC_REQ);
        ExecuteOilAction(RCVD_MSG_PTR);
      break;  
      case OAMS_CFG_AFH_ALARM_IND :
        alarm_count++;
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_AFH_ALARM_IND[%d] ", OAMS_CFG_AFH_ALARM_IND);        
        if ( ((OamsCfgAfhSysAlarm *)RCVD_MSG_PTR)->sysAlarm.sysalarmId == EVENT_CLOCK_SRC_CFG_SUCCESSFUL) {
           TEST_RESULT = TEST_RESULT;
        }
        if (alarm_count == 2) {
          return ;
        }  
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC8(I_Void)
{
  ClkSourceConfigTableIndices inData = { 0 };
  ClkSourceConfigTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);
  if (CLIB_SUCCESS == getClkSourceConfigTable( &inData, &outData) ) {
    PRINT_CLKSOURCECONFIGTABLE(outData);
    if (outData->totalNumClkSrc = 2) TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    TEST_RESULT =0;
    LOG_PRINT(CRITICAL," [%s]:getClkSourceConfigTable fails",__func__);
  }
  return ;
}

I_Void fClkSrcCfgTC8(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC8();
  fClkSrcCfgStepsTC8();
  fClkSrcCfgPostTC8();
  return ;
}

/*----------------------------------TC9---------------------------------------------*/
//Send 2 Clock Sources with one is OK and second is NOK from Platform
I_Void fClkSrcCfgPreTC9(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  fill_trunk_port_talbe(FALSE, 2 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,2,0,1,1,0,2,2,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC9(I_Void)
{
  I_U32 alarm_count = 0;
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status != CM_SUCCESS) {
          TEST_RESULT=0;
        }
        break;
      case OAMS_CFG_OIL_SET_CLK_SRC_REQ:
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_OIL_SET_CLK_SRC_REQ [%d] ", OAMS_CFG_OIL_SET_CLK_SRC_REQ);
        ExecuteOilAction(RCVD_MSG_PTR);
      break;  
      case OAMS_CFG_AFH_ALARM_IND :
        alarm_count++;
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_AFH_ALARM_IND[%d] ", OAMS_CFG_AFH_ALARM_IND);        
        if ( ((OamsCfgAfhSysAlarm *)RCVD_MSG_PTR)->sysAlarm.sysalarmId == EVENT_CLOCK_SRC_CFG_SUCCESSFUL) {
          TEST_RESULT = TEST_RESULT;
        }
        if (alarm_count == 2) { return ; }
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC9(I_Void)
{
  ClkSourceConfigTableIndices inData = { 0 };
  ClkSourceConfigTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);
  if (CLIB_SUCCESS == getClkSourceConfigTable( &inData, &outData) ) {
    PRINT_CLKSOURCECONFIGTABLE(outData);
    if (outData->totalNumClkSrc = 2) TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getClkSourceConfigTable fails",__func__);
  }
  return ;
}

I_Void fClkSrcCfgTC9(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC9();
  fClkSrcCfgStepsTC9();
  fClkSrcCfgPostTC9();
  return ;
}

/*----------------------------------TC10---------------------------------------------*/
//Send 2 Clock Sources and both are rejected by the platform 
I_Void fClkSrcCfgPreTC10(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  fill_trunk_port_talbe(FALSE, 2 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,2,0,1,1,0,2,2,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC10(I_Void)
{
  I_U32 alarm_count = 0;
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status != CM_SUCCESS) {
          TEST_RESULT=0;
        }
        break;
      case OAMS_CFG_OIL_SET_CLK_SRC_REQ:
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_OIL_SET_CLK_SRC_REQ [%d] ", OAMS_CFG_OIL_SET_CLK_SRC_REQ);
        ExecuteOilAction(RCVD_MSG_PTR);
      break;  
      case OAMS_CFG_AFH_ALARM_IND :
        alarm_count++;
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_AFH_ALARM_IND[%d] ", OAMS_CFG_AFH_ALARM_IND);        
        if ( ((OamsCfgAfhSysAlarm *)RCVD_MSG_PTR)->sysAlarm.sysalarmId == EVENT_CLOCK_SRC_CFG_SUCCESSFUL) {
          TEST_RESULT = TEST_RESULT;
        }
        if ( alarm_count == 2) { return ; }
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC10(I_Void)
{
  ClkSourceConfigTableIndices inData = { 0 };
  ClkSourceConfigTableApi *outData;
  LOG_PRINT(INFO,"%s:",__func__);
  if (CLIB_SUCCESS == getClkSourceConfigTable( &inData, &outData) ) {
    PRINT_CLKSOURCECONFIGTABLE(outData);
    if (outData->totalNumClkSrc = 2) TEST_RESULT =1;
    free(outData);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getClkSourceConfigTable fails",__func__);
  }
  return ;
}

I_Void fClkSrcCfgTC10(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC10();
  fClkSrcCfgStepsTC10();
  fClkSrcCfgPostTC10();
  return ;
}

/*----------------------------------TC11---------------------------------------------*/
//Send second Clock Source Configuration request before the first is completed
I_Void fClkSrcCfgPreTC11(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  fill_trunk_port_talbe(FALSE, 2 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,2,0,1,1,0,2,2,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC11(I_Void)
{
  I_U32 alarm_count = 0;
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_CLK_SRC_CFG_IN_PROGRESS) {
          TEST_RESULT=1;            
        }  
        break;
      case OAMS_CFG_OIL_SET_CLK_SRC_REQ:
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_OIL_SET_CLK_SRC_REQ [%d] ", OAMS_CFG_OIL_SET_CLK_SRC_REQ);
        // Send the Clock Configuration Request 
        fClkSrcCfgPreTC11();
        ExecuteOilAction(RCVD_MSG_PTR);
      break;  
      case OAMS_CFG_AFH_ALARM_IND :
        alarm_count++;
        LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_AFH_ALARM_IND[%d] ", OAMS_CFG_AFH_ALARM_IND);        
        if ( ((OamsCfgAfhSysAlarm *)RCVD_MSG_PTR)->sysAlarm.sysalarmId == EVENT_CLOCK_SRC_CFG_FAILED) {
          TEST_RESULT = TEST_RESULT;
        }
        if ( alarm_count == 2) { return ; }      
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC11(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void fClkSrcCfgTC11(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC11();
  fClkSrcCfgStepsTC11();
  fClkSrcCfgPostTC11();
  return ;
}

/*----------------------------------TC12---------------------------------------------*/
//Send Clock Source Configuration with Duplicated Trunk Port 
I_Void fClkSrcCfgPreTC12(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  fill_trunk_port_talbe(FALSE, 2 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,2,0,1,1,0,1,2,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC12(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_CLK_DUPLICATE_TRUNKPORT) {
          TEST_RESULT=1;
          return;
        }
        break;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC12(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void fClkSrcCfgTC12(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC12();
  fClkSrcCfgStepsTC12();
  fClkSrcCfgPostTC12();
  return ;
}

/*----------------------------------TC13---------------------------------------------*/
//Send Clock Source Configuration with Duplicated  Priority
I_Void fClkSrcCfgPreTC13(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  fill_trunk_port_talbe(FALSE, 2 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,2,0,1,1,0,2,1,0,0,0,0,0,0,0,0,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC13(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_CLK_DUPLICATE_PRIORITY) {
          TEST_RESULT=1;
          return;
        }
        break;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC13(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void fClkSrcCfgTC13(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC13();
  fClkSrcCfgStepsTC13();
  fClkSrcCfgPostTC13();
  return ;
}

/*----------------------------------TC14---------------------------------------------*/
//Send second ROW for Clock Sources (Only one row is supported in the Clock Souce Table)
I_Void fClkSrcCfgPreTC14(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *ClkSourceConfigTableApiBuf = {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0};     
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  fill_trunk_port_talbe(FALSE, 2 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  CALLCLEANDBTABLE(ClkSourceConfigTable);

  if (CLIB_SUCCESS != insertClkSourceConfigTable( &ClkSourceConfigTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertClkSourceConfigTable Fail",__func__);  
  }
  
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,2,0,1,1,0,2,2,0,0,0,0,0,0,0,0,0);
  //Change the Index 
  pClkSrcCfgTblApiRcvdPtr->index = 1;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC14(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_REQUEST) {
          TEST_RESULT=1;
          return;
        }
        break;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC14(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  CALLCLEANDBTABLE(ClkSourceConfigTable);  
  return ;
}

I_Void fClkSrcCfgTC14(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC14();
  fClkSrcCfgStepsTC14();
  fClkSrcCfgPostTC14();
  return ;
}

/*----------------------------------TC15---------------------------------------------*/
//Same Clock Source is configured again 
I_Void fClkSrcCfgPreTC15(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi ClkSourceConfigTableApiBuf = {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0};     
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  fill_trunk_port_talbe(FALSE, 2 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  CALLCLEANDBTABLE(ClkSourceConfigTable);

  if (CLIB_SUCCESS != insertClkSourceConfigTable( &ClkSourceConfigTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertClkSourceConfigTable Fail",__func__);  
  }
  
  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,1,0,1,1,0,0,0,0,0,0,2,2,0,5,5,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC15(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
          return;
        }
        break;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC15(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  CALLCLEANDBTABLE(ClkSourceConfigTable);  
  return ;
}

I_Void fClkSrcCfgTC15(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC15();
  fClkSrcCfgStepsTC15();
  fClkSrcCfgPostTC15();
  return ;
}

/*----------------------------------TC16---------------------------------------------*/
//Send Clock Source Configuration with invalid priority 
I_Void fClkSrcCfgPreTC16(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  fill_trunk_port_talbe(FALSE, 2 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  CALLCLEANDBTABLE(ClkSourceConfigTable);

  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,1,1,1,7,0,0,0,0,0,0,2,2,0,5,5,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC16(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_CLK_INVALID_PRIORITY) {
          TEST_RESULT=1;
          return;
        }
        break;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC16(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void fClkSrcCfgTC16(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC16();
  fClkSrcCfgStepsTC16();
  fClkSrcCfgPostTC16();
  return ;
}

/*----------------------------------TC17---------------------------------------------*/
//Send Clock Source Configuration with invalid priority 
I_Void fClkSrcCfgPreTC17(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  // Fill Trunk Port Table 
  fill_trunk_port_talbe(TRUE, 1 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  fill_trunk_port_talbe(FALSE, 2 ,E1_TRUNK_TYPE , OPERATOR_DISABLE);
  
  CALLCLEANDBTABLE(ClkSourceConfigTable);

  cleanMappingTrunk2E1();
  createMappingTrunk2E1(1/*TrunkPortId*/,0/*E1Num*/);
  createMappingTrunk2E1(2/*TrunkPortId*/,1/*E1Num*/);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_CLKSOURCECONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  FILL_CLKSOURCECONFIGTABLE(pClkSrcCfgTblApiRcvdPtr,1,0,1,1,7,0,0,0,0,0,0,2,2,0,5,5,0);
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(ClkSourceConfigTableApi) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void fClkSrcCfgStepsTC17(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE [%d]" , CM_API_APP_RESPONSE);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ATLEAST_ONE_CLK_SRC_IS_NEEDED) {
          TEST_RESULT=1;
          return;
        }
        break;
      default :;
    }  
  }
  return ;
}

I_Void fClkSrcCfgPostTC17(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void fClkSrcCfgTC17(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fClkSrcCfgPreTC17();
  fClkSrcCfgStepsTC17();
  fClkSrcCfgPostTC17();
  return ;
}

/*-----------------------------------------------------------------------*/
I_PU8 clkSrcTestCaseDescription(I_U32 testCaseId) {
  switch (testCaseId) {
    case TEST_CASE_CLK_SRC_CFG_ALL:
      return "ALL CLK SRC CFG TCs";
    case TEST_CASE1_CLK_SRC_CFG:
      return "CLK SRC CFG TC 1";
    case TEST_CASE2_CLK_SRC_CFG:
      return "CLK SRC CFG TC 2";
    case TEST_CASE3_CLK_SRC_CFG:
      return "CLK SRC CFG TC 3";
    case TEST_CASE4_CLK_SRC_CFG:
      return "CLK SRC CFG TC 4";      
    case TEST_CASE5_CLK_SRC_CFG:
      return "CLK SRC CFG TC 5"; 
    case TEST_CASE6_CLK_SRC_CFG:
      return "CLK SRC CFG TC 6";    
    case TEST_CASE7_CLK_SRC_CFG:
      return "CLK SRC CFG TC 7";    
    case TEST_CASE8_CLK_SRC_CFG:
      return "CLK SRC CFG TC 8";        
    case TEST_CASE9_CLK_SRC_CFG:
      return "CLK SRC CFG TC 9";    
    case TEST_CASE10_CLK_SRC_CFG:
      return "CLK SRC CFG TC10";     
    case TEST_CASE11_CLK_SRC_CFG:
      return "CLK SRC CFG TC11";        
    case TEST_CASE12_CLK_SRC_CFG:
      return "CLK SRC CFG TC12";     
    case TEST_CASE13_CLK_SRC_CFG:
      return "CLK SRC CFG TC13";     
    case TEST_CASE14_CLK_SRC_CFG:
      return "CLK SRC CFG TC14";     
    case TEST_CASE15_CLK_SRC_CFG:
      return "CLK SRC CFG TC15";   
    case TEST_CASE16_CLK_SRC_CFG:
      return "CLK SRC CFG TC16";        
    case TEST_CASE17_CLK_SRC_CFG:
      return "CLK SRC CFG TC17";        
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
    
  }
  return NULL;
}

I_Void ExecuteClkGroup(I_U32 testCaseId) 
{
  switch (testCaseId) {
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
    case TEST_CASE_CLK_SRC_CFG_ALL:
    case TEST_CASE1_CLK_SRC_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE1_CLK_SRC_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);      
      fClkSrcCfgTC1();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE2_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE2_CLK_SRC_CFG;  
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC2();    
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE3_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE3_CLK_SRC_CFG;   
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC3();
      
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }      
    case TEST_CASE4_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE4_CLK_SRC_CFG;    
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC4();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }       
    case TEST_CASE5_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE5_CLK_SRC_CFG;
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC5();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }    
    case TEST_CASE6_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE6_CLK_SRC_CFG;    
      TEST_RESULT=0;   
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC6();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }      
    case TEST_CASE7_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE7_CLK_SRC_CFG;  
      TEST_RESULT=0; 
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC7();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }        
    case TEST_CASE8_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE8_CLK_SRC_CFG;  
      TEST_RESULT=0;   
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC8();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE9_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE9_CLK_SRC_CFG;   
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC9();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }      
    case TEST_CASE10_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE10_CLK_SRC_CFG;    
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC10();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE11_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE11_CLK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC11();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }       
     case TEST_CASE12_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE12_CLK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC12();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }      
     case TEST_CASE13_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE13_CLK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC13();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }      
     case TEST_CASE14_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE14_CLK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC14();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      } 
     case TEST_CASE15_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE15_CLK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC15();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }       
     case TEST_CASE16_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE16_CLK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC16();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }   
     case TEST_CASE17_CLK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE17_CLK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fClkSrcCfgTC17();
      PRINT_TEST_RESULT();
      if (TEST_CASE_CLK_SRC_CFG_ALL != testCaseId ) {
        break;
      }         
  }
  return ;
}

