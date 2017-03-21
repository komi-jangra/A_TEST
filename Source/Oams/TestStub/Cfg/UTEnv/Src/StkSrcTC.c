#include <includes.h>

CLEANDBTABLEIMPLEMENTATION(AifInterfaceTable)
CLEANDBTABLEIMPLEMENTATION(BssTable)
CLEANDBTABLEIMPLEMENTATION(Ss7StackConfigTable)
CLEANDBTABLEIMPLEMENTATION(LinksetTable)
CLEANDBTABLEIMPLEMENTATION(LinkTable)
CLEANDBTABLEIMPLEMENTATION(TrunkTable)
CLEANDBTABLEIMPLEMENTATION(TrunkGroupTable)
CLEANDBTABLEIMPLEMENTATION(CicTable)
CLEANDBTABLEIMPLEMENTATION(Ss7RouteTable)

/*----------------------------------TC1---------------------------------------------*/
#if 0
I_Void  fStkSrcCfgPreTC1() 
{
  sCmMsg* CmMsgPtr = NULL;
  AbisInterfaceTableIndices *pAbisInterfaceTableIndicesPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(AbisInterfaceTable);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(AbisInterfaceTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_ABISINTERFACETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(AbisInterfaceTableIndices);

  pAbisInterfaceTableIndicesPtr = (AbisInterfaceTableIndices *)(CmMsgPtr+1);
  pAbisInterfaceTableIndicesPtr->interfaceId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(AbisInterfaceTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}

I_Void  fStkSrcCfgStepsTC1()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_DEL_OBJ_NOT_ALLOWED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }

  return ;
}
I_Void  fStkSrcCfgPostTC1()
{
  return ;
}
I_Void fStkSrcCfgTC1(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  LOG_PRINT(INFO,"AbisInterface Table is not supported in CS40"); 
  fStkSrcCfgPreTC1();
  fStkSrcCfgStepsTC1();
  fStkSrcCfgPostTC1();
  return ;
}
/*----------------------------------TC2---------------------------------------------*/
I_Void  fStkSrcCfgPreTC2() 
{
  sCmMsg* CmMsgPtr = NULL;
  AbisInterfaceTableApi AbisInterfaceTableApiBuff;
  AbisInterfaceTableIndices *pAbisInterfaceTableIndicesPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(AbisInterfaceTable);
  
  AbisInterfaceTableApiBuff.interfaceId = 0;
  AbisInterfaceTableApiBuff.bicId = 1; /*valid bic*/
  AbisInterfaceTableApiBuff.interfaceNameString[20];
  AbisInterfaceTableApiBuff.interfaceType = 2; /* Abis*/
  AbisInterfaceTableApiBuff.adminState = 0; /*locked*/

  if (CLIB_SUCCESS != insertAbisInterfaceTable( &AbisInterfaceTableApiBuff) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAbisInterfaceTable Fail",__func__);  
  }
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(AbisInterfaceTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_ABISINTERFACETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(AbisInterfaceTableIndices);

  pAbisInterfaceTableIndicesPtr = (AbisInterfaceTableIndices *)(CmMsgPtr+1);
  pAbisInterfaceTableIndicesPtr->interfaceId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(AbisInterfaceTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}
I_Void  fStkSrcCfgStepsTC2()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_DEL_OBJ_NOT_ALLOWED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkSrcCfgPostTC2()
{
  return ;
}
I_Void fStkSrcCfgTC2(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC2();
  fStkSrcCfgStepsTC2();
  fStkSrcCfgPostTC2();
  return ;
}

/*----------------------------------TC3---------------------------------------------*/
I_Void  fStkSrcCfgPreTC3() 
{
  sCmMsg* CmMsgPtr = NULL;
  AbisInterfaceTableApi AbisInterfaceTableApiBuff;
  AbisInterfaceTableIndices *pAbisInterfaceTableIndicesPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(AbisInterfaceTable);
  
  AbisInterfaceTableApiBuff.interfaceId = 0;
  AbisInterfaceTableApiBuff.bicId = ~0; /*invalid bic*/
  AbisInterfaceTableApiBuff.interfaceNameString[20];
  AbisInterfaceTableApiBuff.interfaceType = 2; /* Abis*/
  AbisInterfaceTableApiBuff.adminState = 0; /*locked*/

  if (CLIB_SUCCESS != insertAbisInterfaceTable( &AbisInterfaceTableApiBuff) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAbisInterfaceTable Fail",__func__);  
  }
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(AbisInterfaceTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_ABISINTERFACETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(AbisInterfaceTableIndices);

  pAbisInterfaceTableIndicesPtr = (AbisInterfaceTableIndices *)(CmMsgPtr+1);
  pAbisInterfaceTableIndicesPtr->interfaceId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(AbisInterfaceTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  
  return ;
}
I_Void  fStkSrcCfgStepsTC3()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_DEL_OBJ_NOT_ALLOWED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC3()
{
    AbisInterfaceTableApi *outData;     
    I_U32 outRows;                  
    I_U32 index;                    
    I_U16 outSize;                  
    if ( getallAbisInterfaceTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) { 
      LOG_PRINT(INFO, "AbisInterface Table is not empty " );    
      TEST_RESULT=0; 
    }
}
I_Void fStkSrcCfgTC3(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC3();
  fStkSrcCfgStepsTC3();
  //fStkSrcCfgPostTC3();
  return ;
}
#endif
/*----------------------------------TC4---------------------------------------------*/
I_Void  fStkSrcCfgPreTC4() 
{
  sCmMsg* CmMsgPtr = NULL;
  Ss7StackConfigTableIndices *pSs7StackConfigTableIndices;
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(Ss7StackConfigTable);

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(Ss7StackConfigTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_SS7STACKCONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(Ss7StackConfigTableIndices);

  pSs7StackConfigTableIndices = (Ss7StackConfigTableIndices *)(CmMsgPtr+1);
  pSs7StackConfigTableIndices->index = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(Ss7StackConfigTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}
I_Void  fStkSrcCfgStepsTC4()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkSrcCfgPostTC4()
{
  return ;
}
I_Void fStkSrcCfgTC4(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC4();
  fStkSrcCfgStepsTC4();
  fStkSrcCfgPostTC4();
  return ;
}

/*----------------------------------TC5---------------------------------------------*/
I_Void  fStkSrcCfgPreTC5() 
{
  sCmMsg* CmMsgPtr = NULL;
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf = {0,1,1,1};
  AifInterfaceTableApi AifInterfaceTableApiBuf = {0,"AIFINTERFACE",1/*AIF*/,1,1,0,0};
  Ss7StackConfigTableIndices *pSs7StackConfigTableIndices;
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(Ss7StackConfigTable);
  CALLCLEANDBTABLE(AifInterfaceTable);
   
  if (CLIB_SUCCESS != insertSs7StackConfigTable( &Ss7StackConfigTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSs7StackConfigTable Fail",__func__);  
  }
  
  if (CLIB_SUCCESS != insertAifInterfaceTable( &AifInterfaceTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSs7StackConfigTable Fail",__func__);  
  }
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(Ss7StackConfigTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_SS7STACKCONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(Ss7StackConfigTableIndices);

  pSs7StackConfigTableIndices = (Ss7StackConfigTableIndices *)(CmMsgPtr+1);
  pSs7StackConfigTableIndices->index = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(Ss7StackConfigTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fStkSrcCfgStepsTC5()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_AIFINTERFACE_OBJ_EXISTS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkSrcCfgPostTC5()
{
  return ;
}
I_Void fStkSrcCfgTC5(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC5();
  fStkSrcCfgStepsTC5();
  fStkSrcCfgPostTC5();
  return ;
}

/*----------------------------------TC6---------------------------------------------*/
I_Void  fStkSrcCfgPreTC6() 
{
  sCmMsg* CmMsgPtr = NULL;
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf = {0,1,1,1};
  Ss7StackConfigTableIndices *pSs7StackConfigTableIndices;
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(Ss7StackConfigTable);
  CALLCLEANDBTABLE(AifInterfaceTable);
   
  if (CLIB_SUCCESS != insertSs7StackConfigTable( &Ss7StackConfigTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSs7StackConfigTable Fail",__func__);  
  }
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(Ss7StackConfigTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_SS7STACKCONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(Ss7StackConfigTableIndices);

  pSs7StackConfigTableIndices = (Ss7StackConfigTableIndices *)(CmMsgPtr+1);
  pSs7StackConfigTableIndices->index = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(Ss7StackConfigTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fStkSrcCfgStepsTC6()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;

}
I_Void  fStkSrcCfgPostTC6()
{
  return ;
}
I_Void fStkSrcCfgTC6(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC6();
  fStkSrcCfgStepsTC6();
  fStkSrcCfgPostTC6();
  return ;
}

/*----------------------------------TC7---------------------------------------------*/
I_Void  fStkSrcCfgPreTC7() 
{
  sCmMsg* CmMsgPtr = NULL;
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf = {0,1,1,1};
  Ss7StackConfigTableIndices *pSs7StackConfigTableIndices;
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(Ss7StackConfigTable);
  CALLCLEANDBTABLE(AifInterfaceTable);
   
  if (CLIB_SUCCESS != insertSs7StackConfigTable( &Ss7StackConfigTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSs7StackConfigTable Fail",__func__);  
  }
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(Ss7StackConfigTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_SS7STACKCONFIGTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(Ss7StackConfigTableIndices);

  pSs7StackConfigTableIndices = (Ss7StackConfigTableIndices *)(CmMsgPtr+1);
  pSs7StackConfigTableIndices->index = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(Ss7StackConfigTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}
I_Void  fStkSrcCfgStepsTC7()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
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
I_Void  fStkSrcCfgPostTC7()
{
    Ss7StackConfigTableApi *outData;     
    I_U32 outRows;                  
    I_U32 index;                    
    I_U16 outSize;                  
    if ( getallSs7StackConfigTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) { 
      LOG_PRINT(INFO, "getallSs7StackConfigTable Table is not empty " );    
      TEST_RESULT=0; 
    }
}

I_Void fStkSrcCfgTC7(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC7();
  fStkSrcCfgStepsTC7();
  fStkSrcCfgPostTC7();
  return ;
}

/*----------------------------------TC8---------------------------------------------*/
I_Void  fStkSrcCfgPreTC8() 
{
  sCmMsg* CmMsgPtr = NULL;
  AifInterfaceTableIndices *pAifInterfaceTableIndices;
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(AifInterfaceTable);

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(AifInterfaceTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_AIFINTERFACETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(AifInterfaceTableIndices);

  pAifInterfaceTableIndices = (AifInterfaceTableIndices *)(CmMsgPtr+1);
  pAifInterfaceTableIndices->interfaceId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(AifInterfaceTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}
I_Void  fStkSrcCfgStepsTC8()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;

}
I_Void  fStkSrcCfgPostTC8()
{
  return ;
}
I_Void fStkSrcCfgTC8(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC8();
  fStkSrcCfgStepsTC8();
  fStkSrcCfgPostTC8();
  return ;
}

/*----------------------------------TC9---------------------------------------------*/
I_Void  fStkSrcCfgPreTC9() 
{
  sCmMsg* CmMsgPtr = NULL;
  AifInterfaceTableApi AifInterfaceTableApiBuf = {0,"AIFINTERFACE",1/*AIF*/,1,1,0,0};
  LinksetTableApi LinksetTableApiBuf = {0,"LINKSET0",0,1,0,0};
  AifInterfaceTableIndices *pAifInterfaceTableIndices;

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(AifInterfaceTable);
  CALLCLEANDBTABLE(LinksetTable);

  if (CLIB_SUCCESS != insertAifInterfaceTable( &AifInterfaceTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAifInterfaceTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertLinksetTable( &LinksetTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinksetTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(AifInterfaceTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_AIFINTERFACETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(AifInterfaceTableIndices);

  pAifInterfaceTableIndices = (AifInterfaceTableIndices *)(CmMsgPtr+1);
  pAifInterfaceTableIndices->interfaceId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(AifInterfaceTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}
I_Void  fStkSrcCfgStepsTC9()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_LINKSET_OBJ_EXISTS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC9()
{
  return ;
}

I_Void fStkSrcCfgTC9(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC9();
  fStkSrcCfgStepsTC9();
  fStkSrcCfgPostTC9();
  return ;
}
/*----------------------------------TC10---------------------------------------------*/
I_Void  fStkSrcCfgPreTC10() 
{
  sCmMsg* CmMsgPtr = NULL;
  AifInterfaceTableApi AifInterfaceTableApiBuf = {0,"AIFINTERFACE",1/*AIF*/,1,1,0,0};
  TrunkTableApi TrunkTableApiBuf = {0,1,1,1,30,1,0,1,0,10};
  AifInterfaceTableIndices *pAifInterfaceTableIndices;

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(AifInterfaceTable);
  CALLCLEANDBTABLE(LinksetTable);

  if (CLIB_SUCCESS != insertAifInterfaceTable( &AifInterfaceTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAifInterfaceTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertTrunkTable( &TrunkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(AifInterfaceTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_AIFINTERFACETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(AifInterfaceTableIndices);

  pAifInterfaceTableIndices = (AifInterfaceTableIndices *)(CmMsgPtr+1);
  pAifInterfaceTableIndices->interfaceId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(AifInterfaceTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fStkSrcCfgStepsTC10()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_TRUNK_OBJ_EXISTS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC10()
{
  return ;
}
I_Void fStkSrcCfgTC10(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC10();
  fStkSrcCfgStepsTC10();
  fStkSrcCfgPostTC10();
  return ;
}
/*----------------------------------TC11---------------------------------------------*/
I_Void  fStkSrcCfgPreTC11() 
{
  sCmMsg* CmMsgPtr = NULL;
  AifInterfaceTableApi AifInterfaceTableApiBuf = {0,"AIFINTERFACE",1/*AIF*/,1,1,0,0};
  TrunkTableApi TrunkTableApiBuf = {0,1,1,1,30,1,0,1,0,10};
  AifInterfaceTableIndices *pAifInterfaceTableIndices;

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(AifInterfaceTable);
  CALLCLEANDBTABLE(LinksetTable);
  CALLCLEANDBTABLE(TrunkTable);

  if (CLIB_SUCCESS != insertAifInterfaceTable( &AifInterfaceTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAifInterfaceTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(AifInterfaceTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_AIFINTERFACETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(AifInterfaceTableIndices);

  pAifInterfaceTableIndices = (AifInterfaceTableIndices *)(CmMsgPtr+1);
  pAifInterfaceTableIndices->interfaceId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(AifInterfaceTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC11()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC11()
{
  return ;
}

I_Void fStkSrcCfgTC11(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC11();
  fStkSrcCfgStepsTC11();
  fStkSrcCfgPostTC11();
  return ;
}

/*----------------------------------TC12---------------------------------------------*/
I_Void  fStkSrcCfgPreTC12() 
{
  sCmMsg* CmMsgPtr = NULL;
  AifInterfaceTableApi AifInterfaceTableApiBuf = {0,"AIFINTERFACE",1/*AIF*/,1,1,0,0};
  TrunkTableApi TrunkTableApiBuf = {0,1,1,1,30,1,0,1,0,10};
  AifInterfaceTableIndices *pAifInterfaceTableIndices;

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(AifInterfaceTable);
  CALLCLEANDBTABLE(LinksetTable);
  CALLCLEANDBTABLE(TrunkTable);

  if (CLIB_SUCCESS != insertAifInterfaceTable( &AifInterfaceTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAifInterfaceTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(AifInterfaceTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_AIFINTERFACETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(AifInterfaceTableIndices);

  pAifInterfaceTableIndices = (AifInterfaceTableIndices *)(CmMsgPtr+1);
  pAifInterfaceTableIndices->interfaceId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(AifInterfaceTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC12()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_DELETE_DB_OPER_FAILED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC12()
{
  return;                                                     
}

I_Void fStkSrcCfgTC12(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC12();
  fStkSrcCfgStepsTC12();
  fStkSrcCfgPostTC12();
  return ;
}

/*----------------------------------TC13---------------------------------------------*/
I_Void  fStkSrcCfgPreTC13() 
{
  sCmMsg* CmMsgPtr = NULL;
  AifInterfaceTableApi AifInterfaceTableApiBuf = {0,"AIFINTERFACE",1/*AIF*/,1,1,0,0};
  TrunkTableApi TrunkTableApiBuf = {0,1,1,1,30,1,0,1,0,10};
  TrunkGroupTableApi TrunkGroupTableApiBuf = { 0,1,0,1};
  AifInterfaceTableIndices *pAifInterfaceTableIndices;

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(AifInterfaceTable);
  CALLCLEANDBTABLE(LinksetTable);
  CALLCLEANDBTABLE(TrunkTable);
  CALLCLEANDBTABLE(TrunkGroupTable);

  if (CLIB_SUCCESS != insertTrunkGroupTable( &TrunkGroupTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkGroupTable Fail",__func__);  
  }
  
  if (CLIB_SUCCESS != insertAifInterfaceTable( &AifInterfaceTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAifInterfaceTable Fail",__func__);  
  }
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(AifInterfaceTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_AIFINTERFACETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(AifInterfaceTableIndices);

  pAifInterfaceTableIndices = (AifInterfaceTableIndices *)(CmMsgPtr+1);
  pAifInterfaceTableIndices->interfaceId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(AifInterfaceTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC13()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
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

I_Void  fStkSrcCfgPostTC13()
{
  ISTABLEEMPTY(AifInterfaceTable);     
  ISTABLEEMPTY(TrunkGroupTable);   
  return ;
}

I_Void fStkSrcCfgTC13(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC13();
  fStkSrcCfgStepsTC13();
  fStkSrcCfgPostTC13();
  return ;
}

/*----------------------------------TC14---------------------------------------------*/
I_Void  fStkSrcCfgPreTC14() 
{
  sCmMsg* CmMsgPtr = NULL;
  LinksetTableIndices *pLinkSetTableIndices;

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(LinksetTable);

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(LinksetTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_LINKSETTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(LinksetTableIndices);

  pLinkSetTableIndices = (LinksetTableIndices *)(CmMsgPtr+1);
  pLinkSetTableIndices->linksetID = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(LinksetTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC14()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC14()
{
  return ;
}

I_Void fStkSrcCfgTC14(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC14();
  fStkSrcCfgStepsTC14();
  fStkSrcCfgPostTC14();
  return ;
}

/*----------------------------------TC15---------------------------------------------*/
I_Void  fStkSrcCfgPreTC15() 
{
  sCmMsg* CmMsgPtr = NULL;
  LinksetTableIndices *pLinkSetTableIndices;
  LinksetTableApi LinksetTableApiBuf = {0,"AIF",0,1,1,0};
  LinkTableApi LinkTableApiBuf = {0,0,1,1,1,1,1,0};

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(LinksetTable);
  CALLCLEANDBTABLE(LinkTable);
  
  if (CLIB_SUCCESS != insertLinksetTable( &LinksetTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinksetTable Fail",__func__);  
  }
  
  if (CLIB_SUCCESS != insertLinkTable( &LinkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinkTable Fail",__func__);  
  }
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(LinksetTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_LINKSETTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(LinksetTableIndices);

  pLinkSetTableIndices = (LinksetTableIndices *)(CmMsgPtr+1);
  pLinkSetTableIndices->linksetID = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(LinksetTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC15()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_LINK_OBJ_EXISTS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC15()
{
  return ;
}

I_Void fStkSrcCfgTC15(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC15();
  fStkSrcCfgStepsTC15();
  fStkSrcCfgPostTC15();
  return ;
}

/*----------------------------------TC16---------------------------------------------*/
I_Void  fStkSrcCfgPreTC16() 
{
  sCmMsg* CmMsgPtr = NULL;
  LinksetTableIndices *pLinkSetTableIndices;
  LinksetTableApi LinksetTableApiBuf = {0,"AIF",0,1,1,0};

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(LinksetTable);
  CALLCLEANDBTABLE(LinkTable);
  
  if (CLIB_SUCCESS != insertLinksetTable( &LinksetTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinksetTable Fail",__func__);  
  }
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(LinksetTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_LINKSETTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(LinksetTableIndices);

  pLinkSetTableIndices = (LinksetTableIndices *)(CmMsgPtr+1);
  pLinkSetTableIndices->linksetID = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(LinksetTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC16()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC16()
{
  return ;
}

I_Void fStkSrcCfgTC16(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC16();
  fStkSrcCfgStepsTC16();
  fStkSrcCfgPostTC16();
  return ;
}

/*----------------------------------TC17---------------------------------------------*/
I_Void  fStkSrcCfgPreTC17() 
{
  sCmMsg* CmMsgPtr = NULL;
  LinksetTableIndices *pLinkSetTableIndices;
  LinksetTableApi LinksetTableApiBuf = {0,"AIF",0,1,1,0};

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(LinksetTable);
  CALLCLEANDBTABLE(LinkTable);
  
  if (CLIB_SUCCESS != insertLinksetTable( &LinksetTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinksetTable Fail",__func__);  
  }
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(LinksetTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_LINKSETTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(LinksetTableIndices);

  pLinkSetTableIndices = (LinksetTableIndices *)(CmMsgPtr+1);
  pLinkSetTableIndices->linksetID = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(LinksetTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC17()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
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

I_Void  fStkSrcCfgPostTC17()
{
  ISTABLEEMPTY(LinksetTable);     
  return ;
}

I_Void fStkSrcCfgTC17(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC17();
  fStkSrcCfgStepsTC17();
  fStkSrcCfgPostTC17();
  return ;
}

/*----------------------------------TC18---------------------------------------------*/
I_Void  fStkSrcCfgPreTC18() 
{
  sCmMsg* CmMsgPtr = NULL;
  LinkTableIndices *pLinkTableIndices;

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(LinkTable);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(LinkTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_LINKTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(LinkTableIndices);

  pLinkTableIndices = (LinkTableIndices *)(CmMsgPtr+1);
  pLinkTableIndices->linksetID = 0;
  pLinkTableIndices->linkId = 0;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(LinkTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC18()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC18()
{
  return ;
}

I_Void fStkSrcCfgTC18(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC18();
  fStkSrcCfgStepsTC18();
  fStkSrcCfgPostTC18();
  return ;
}

/*----------------------------------TC19---------------------------------------------*/
I_Void  fStkSrcCfgPreTC19() 
{
  sCmMsg* CmMsgPtr = NULL;
  LinkTableIndices *pLinkTableIndices;
  LinkTableApi LinkTableApiBuf = {0,0,1,1,1,1,1,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(LinkTable);
  
  if (CLIB_SUCCESS != insertLinkTable( &LinkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinkTable Fail",__func__);  
  }
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(LinkTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_LINKTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(LinksetTableIndices);

  pLinkTableIndices = (LinkTableIndices *)(CmMsgPtr+1);
  pLinkTableIndices->linksetID = 0;
  pLinkTableIndices->linkId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(LinkTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC19()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OBJECT_NOT_LOCKED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC19()
{
  return ;
}

I_Void fStkSrcCfgTC19(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC19();
  fStkSrcCfgStepsTC19();
  fStkSrcCfgPostTC19();
  return ;
}

/*----------------------------------TC20---------------------------------------------*/
I_Void  fStkSrcCfgPreTC20() 
{
  sCmMsg* CmMsgPtr = NULL;
  LinkTableIndices *pLinkTableIndices;
  LinkTableApi LinkTableApiBuf = {0,0,1,1,1,1,1,LOCKED};
  MccLinkResourceTableApi MccLinkResourceTableApiBuf = {1,1,1,1,1,1,1 } ;
 
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(LinkTable);
  CALLCLEANDBTABLE(MccLinkResourceTable);
  
  
  if (CLIB_SUCCESS != insertLinkTable( &LinkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinkTable Fail",__func__);  
  }
  
  if (CLIB_SUCCESS != insertMccLinkResourceTable( &MccLinkResourceTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:MccLinkResourceTableApi Fail",__func__);  
  }
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(LinkTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_LINKTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(LinksetTableIndices);

  pLinkTableIndices = (LinkTableIndices *)(CmMsgPtr+1);
  pLinkTableIndices->linksetID = 0;
  pLinkTableIndices->linkId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(LinkTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC20()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC20()
{
  return ;
}

I_Void fStkSrcCfgTC20(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC20();
  fStkSrcCfgStepsTC20();
  fStkSrcCfgPostTC20();
  return ;
}

/*----------------------------------TC21---------------------------------------------*/
I_Void  fStkSrcCfgPreTC21() 
{
  sCmMsg* CmMsgPtr = NULL;
  LinkTableIndices *pLinkTableIndices;
  LinkTableApi LinkTableApiBuf = {0,0,1,1,1,1,1,LOCKED};
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(LinkTable);
  CALLCLEANDBTABLE(MccLinkResourceTable);
  
  if (CLIB_SUCCESS != insertLinkTable( &LinkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinkTable Fail",__func__);  
  }
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(LinkTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_LINKTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(LinksetTableIndices);

  pLinkTableIndices = (LinkTableIndices *)(CmMsgPtr+1);
  pLinkTableIndices->linksetID = 0;
  pLinkTableIndices->linkId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(LinkTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC21()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_GET_DB_OPER_FAILED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC21()
{
  return ;
}

I_Void fStkSrcCfgTC21(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC21();
  fStkSrcCfgStepsTC21();
  fStkSrcCfgPostTC21();
  return ;
}

/*----------------------------------TC22---------------------------------------------*/
I_Void  fStkSrcCfgPreTC22() 
{
  sCmMsg* CmMsgPtr = NULL;
  TrunkTableIndices *pTrunkTableIndices;
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(TrunkTable);
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_TRUNKTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkTableIndices);

  pTrunkTableIndices = (TrunkTableIndices *)(CmMsgPtr+1);
  pTrunkTableIndices->interfaceId = 0;
  pTrunkTableIndices->tgpId       = 1;
  pTrunkTableIndices->e1Num       = 0;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC22()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC22()
{
  return ;
}

I_Void fStkSrcCfgTC22(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC22();
  fStkSrcCfgStepsTC22();
  fStkSrcCfgPostTC22();
  return ;
}

/*----------------------------------TC23---------------------------------------------*/
I_Void  fStkSrcCfgPreTC23() 
{
  sCmMsg* CmMsgPtr = NULL;
  TrunkTableApi TrunkTableApiBuf = {0,1,0,1,30,1,0,0,0,21};
  TrunkTableIndices *pTrunkTableIndices;
  CicTableApi CicTableApiBuf1 = {0,1,0,1,1,1,locked,1};
  CicTableApi CicTableApiBuf2 = {0,1,0,2,2,1,unlocked,1};

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(CicTable);
  CALLCLEANDBTABLE(TrunkTable);

  if (CLIB_SUCCESS != insertTrunkTable( &TrunkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertCicTable( &CicTableApiBuf1) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertCicTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertCicTable( &CicTableApiBuf2) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertCicTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_TRUNKTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkTableIndices);

  pTrunkTableIndices = (TrunkTableIndices *)(CmMsgPtr+1);
  pTrunkTableIndices->interfaceId = 0;
  pTrunkTableIndices->tgpId       = 1;
  pTrunkTableIndices->e1Num       = 0;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC23()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OBJECT_NOT_LOCKED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC23()
{
  return ;
}

I_Void fStkSrcCfgTC23(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC23();
  fStkSrcCfgStepsTC23();
  fStkSrcCfgPostTC23();
  return ;
}

/*----------------------------------TC24---------------------------------------------*/
I_Void  fStkSrcCfgPreTC24() 
{
  sCmMsg* CmMsgPtr = NULL;
  TrunkTableApi TrunkTableApiBuf = {0,1,0,1,30,1,0,0,0,21};
  TrunkTableIndices *pTrunkTableIndices;
  CicTableApi CicTableApiBuf1 = {0,1,0,1,1,1,locked,1};
  CicTableApi CicTableApiBuf2 = {0,1,0,2,2,1,locked,1};

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(CicTable);
  CALLCLEANDBTABLE(TrunkTable);
  CALLCLEANDBTABLE(AifInterfaceTable);

  if (CLIB_SUCCESS != insertTrunkTable( &TrunkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertCicTable( &CicTableApiBuf1) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertCicTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertCicTable( &CicTableApiBuf2) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertCicTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_TRUNKTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkTableIndices);

  pTrunkTableIndices = (TrunkTableIndices *)(CmMsgPtr+1);
  pTrunkTableIndices->interfaceId = 0;
  pTrunkTableIndices->tgpId       = 1;
  pTrunkTableIndices->e1Num       = 0;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC24()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_GET_DB_OPER_FAILED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC24()
{
  return ;
}

I_Void fStkSrcCfgTC24(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC24();
  fStkSrcCfgStepsTC24();
  fStkSrcCfgPostTC24();
  return ;
}

/*----------------------------------TC25---------------------------------------------*/
I_Void  fStkSrcCfgPreTC25() 
{
  sCmMsg* CmMsgPtr = NULL;
  TrunkTableApi TrunkTableApiBuf = {0,1,0,1,2,1,0,0,0,21};
  TrunkTableIndices *pTrunkTableIndices;
  AifInterfaceTableApi AifInterfaceTableApiBuf = {0,"AIFINTERFACE",1/*AIF*/,1,1,0,0};
  CicTableApi CicTableApiBuf1 = {0,1,0,1,1,1,locked,1};
  CicTableApi CicTableApiBuf2 = {0,1,0,2,2,1,locked,1};

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(CicTable);
  CALLCLEANDBTABLE(TrunkTable);
  CALLCLEANDBTABLE(AifInterfaceTable);

  if (CLIB_SUCCESS != insertTrunkTable( &TrunkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertAifInterfaceTable( &AifInterfaceTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertCicTable( &CicTableApiBuf1) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertCicTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertCicTable( &CicTableApiBuf2) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertCicTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_TRUNKTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkTableIndices);

  pTrunkTableIndices = (TrunkTableIndices *)(CmMsgPtr+1);
  pTrunkTableIndices->interfaceId = 0;
  pTrunkTableIndices->tgpId       = 1;
  pTrunkTableIndices->e1Num       = 0;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC25()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC25()
{
  return ;
}

I_Void fStkSrcCfgTC25(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC25();
  fStkSrcCfgStepsTC25();
  fStkSrcCfgPostTC25();
  return ;
}

/*----------------------------------TC26---------------------------------------------*/
I_Void  fStkSrcCfgPreTC26() 
{
  sCmMsg* CmMsgPtr = NULL;
  TrunkTableApi TrunkTableApiBuf = {0,1,0,1,2,1,0,0,0,21};
  TrunkTableIndices *pTrunkTableIndices;
  AifInterfaceTableApi AifInterfaceTableApiBuf = {0,"AIFINTERFACE",1/*AIF*/,1,1,0,0};
  CicTableApi CicTableApiBuf1 = {0,1,0,1,1,1,locked,1};
  CicTableApi CicTableApiBuf2 = {0,1,0,2,2,1,locked,1};

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(CicTable);
  CALLCLEANDBTABLE(TrunkTable);
  CALLCLEANDBTABLE(AifInterfaceTable);

  if (CLIB_SUCCESS != insertTrunkTable( &TrunkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertAifInterfaceTable( &AifInterfaceTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertCicTable( &CicTableApiBuf1) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertCicTable Fail",__func__);  
  }

  if (CLIB_SUCCESS != insertCicTable( &CicTableApiBuf2) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertCicTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_TRUNKTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkTableIndices);

  pTrunkTableIndices = (TrunkTableIndices *)(CmMsgPtr+1);
  pTrunkTableIndices->interfaceId = 0;
  pTrunkTableIndices->tgpId       = 1;
  pTrunkTableIndices->e1Num       = 0;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC26()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
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

I_Void  fStkSrcCfgPostTC26()
{
  ISTABLEEMPTY(TrunkTable);     
  ISTABLEEMPTY(CicTable);     
  return ;
}

I_Void fStkSrcCfgTC26(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC26();
  fStkSrcCfgStepsTC26();
  fStkSrcCfgPostTC26();
  return ;
}

/*----------------------------------TC27---------------------------------------------*/
I_Void  fStkSrcCfgPreTC27() 
{
  sCmMsg* CmMsgPtr = NULL;
  Ss7RouteTableIndices *pSs7RouteTableIndices;

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(Ss7RouteTable);

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(Ss7RouteTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_SS7ROUTETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(Ss7RouteTableIndices);

  pSs7RouteTableIndices = (Ss7RouteTableIndices *)(CmMsgPtr+1);
  pSs7RouteTableIndices->linksetID = 0;
  pSs7RouteTableIndices->routeID   = 0;
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(Ss7RouteTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC27()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC27()
{
  return ;
}

I_Void fStkSrcCfgTC27(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC27();
  fStkSrcCfgStepsTC27();
  fStkSrcCfgPostTC27();
  return ;
}
/*----------------------------------TC28---------------------------------------------*/
I_Void  fStkSrcCfgPreTC28() 
{
  sCmMsg* CmMsgPtr = NULL;
  Ss7RouteTableApi Ss7RouteTableApiBuf = {0};
  Ss7RouteTableIndices *pSs7RouteTableIndices;
  LinkTableApi LinkTableApiBuf = {0,0,1,1,1,1,1,unlocked};
  

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(Ss7RouteTable);
  CALLCLEANDBTABLE(LinkTable);

  if (CLIB_SUCCESS != insertLinkTable( &LinkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinkTable Fail",__func__);  
  }
  
  if (CLIB_SUCCESS != insertSs7RouteTable( &Ss7RouteTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSs7RouteTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(Ss7RouteTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_SS7ROUTETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(Ss7RouteTableIndices);

  pSs7RouteTableIndices = (Ss7RouteTableIndices *)(CmMsgPtr+1);
  pSs7RouteTableIndices->linksetID = 0;
  pSs7RouteTableIndices->routeID   = 0;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(Ss7RouteTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fStkSrcCfgStepsTC28()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OBJECT_NOT_LOCKED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC28()
{
  return ;
}

I_Void fStkSrcCfgTC28(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC28();
  fStkSrcCfgStepsTC28();
  fStkSrcCfgPostTC28();
  return ;
}
/*----------------------------------TC29---------------------------------------------*/
I_Void  fStkSrcCfgPreTC29() 
{
  sCmMsg* CmMsgPtr = NULL;
  Ss7RouteTableApi Ss7RouteTableApiBuf = {0};
  Ss7RouteTableIndices *pSs7RouteTableIndices;
  LinkTableApi LinkTableApiBuf = {0,0,1,1,1,1,1,locked};
  

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(Ss7RouteTable);
  CALLCLEANDBTABLE(LinkTable);

  if (CLIB_SUCCESS != insertLinkTable( &LinkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinkTable Fail",__func__);  
  }
  
  if (CLIB_SUCCESS != insertSs7RouteTable( &Ss7RouteTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSs7RouteTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(Ss7RouteTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_SS7ROUTETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(Ss7RouteTableIndices);

  pSs7RouteTableIndices = (Ss7RouteTableIndices *)(CmMsgPtr+1);
  pSs7RouteTableIndices->linksetID = 0;
  pSs7RouteTableIndices->routeID   = 0;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(Ss7RouteTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC29()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC29()
{
  return ;
}

I_Void fStkSrcCfgTC29(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC29();
  fStkSrcCfgStepsTC29();
  fStkSrcCfgPostTC29();
  return ;
}
/*----------------------------------TC30---------------------------------------------*/
I_Void  fStkSrcCfgPreTC30() 
{
  sCmMsg* CmMsgPtr = NULL;
  Ss7RouteTableApi Ss7RouteTableApiBuf = {0};
  Ss7RouteTableIndices *pSs7RouteTableIndices;
  LinkTableApi LinkTableApiBuf = {0,0,1,1,1,1,1,locked};
  

  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(Ss7RouteTable);
  CALLCLEANDBTABLE(LinkTable);

  if (CLIB_SUCCESS != insertLinkTable( &LinkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinkTable Fail",__func__);  
  }
  
  if (CLIB_SUCCESS != insertSs7RouteTable( &Ss7RouteTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSs7RouteTable Fail",__func__);  
  }

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(Ss7RouteTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_SS7ROUTETABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(Ss7RouteTableIndices);

  pSs7RouteTableIndices = (Ss7RouteTableIndices *)(CmMsgPtr+1);
  pSs7RouteTableIndices->linksetID = 0;
  pSs7RouteTableIndices->routeID   = 0;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(Ss7RouteTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC30()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
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

I_Void  fStkSrcCfgPostTC30()
{
  ISTABLEEMPTY(Ss7RouteTable);     
  return ;
}

I_Void fStkSrcCfgTC30(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC30();
  fStkSrcCfgStepsTC30();
  fStkSrcCfgPostTC30();
  return ;
}

/*----------------------------------TC31---------------------------------------------*/
I_Void  fStkSrcCfgPreTC31() 
{
  sCmMsg* CmMsgPtr = NULL;
  LinkTableIndices *pLinkTableIndices;
  LinkTableApi LinkTableApiBuf = {0,0,1,1,1,1,1,LOCKED};
  MccLinkResourceTableApi MccLinkResourceTableApiBuf = {0,0,1,1,1,1,1};
  LOG_PRINT(INFO,"%s:",__func__);

  CALLCLEANDBTABLE(LinkTable);
  CALLCLEANDBTABLE(MccLinkResourceTable);
  
  if (CLIB_SUCCESS != insertLinkTable( &LinkTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinkTable Fail",__func__);  
  }
  
  if (CLIB_SUCCESS != insertMccLinkResourceTable( &MccLinkResourceTableApiBuf) ) {
      LOG_PRINT(LOG_CRITICAL,"%s:insertMccLinkResourceTable Fail",__func__);  
  }
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(LinkTableIndices)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_DEL_LINKTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(LinksetTableIndices);

  pLinkTableIndices = (LinkTableIndices *)(CmMsgPtr+1);
  pLinkTableIndices->linksetID = 0;
  pLinkTableIndices->linkId = 0;
  
  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(LinkTableIndices) + sizeof(sCmMsg)), 
                ""
              );
  return ;

}

I_Void  fStkSrcCfgStepsTC31()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE:CM_SUCCESS " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void  fStkSrcCfgPostTC31()
{
  ISTABLEEMPTY(LinkTable);
  return ;
}

I_Void fStkSrcCfgTC31(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkSrcCfgPreTC31();
  fStkSrcCfgStepsTC31();
  fStkSrcCfgPostTC31();
  return ;
}

/*-----------------------------------------------------------------------*/
I_PU8 stkSrcTestCaseDescription(I_U32 testCaseId) {
  switch (testCaseId) {
    case TEST_CASE_STK_SRC_CFG_ALL:
      return "ALL HA STK CFG TCs";
    case TEST_CASE1_STK_SRC_CFG:
      return "HA STK CFG TC 1";
    case TEST_CASE2_STK_SRC_CFG:
      return "HA STK CFG TC 2";
    case TEST_CASE3_STK_SRC_CFG:
      return "HA STK CFG TC 3";
    case TEST_CASE4_STK_SRC_CFG:
      return "HA STK CFG TC 4";      
    case TEST_CASE5_STK_SRC_CFG:
      return "HA STK CFG TC 5"; 
    case TEST_CASE6_STK_SRC_CFG:
      return "HA STK CFG TC 6";    
    case TEST_CASE7_STK_SRC_CFG:
      return "HA STK CFG TC 7";    
    case TEST_CASE8_STK_SRC_CFG:
      return "HA STK CFG TC 8";        
    case TEST_CASE9_STK_SRC_CFG:
      return "HA STK CFG TC 9";    
    case TEST_CASE10_STK_SRC_CFG:
      return "HA STK CFG TC10";     
    case TEST_CASE11_STK_SRC_CFG:
      return "HA STK CFG TC11";        
    case TEST_CASE12_STK_SRC_CFG:
      return "HA STK CFG TC12";     
    case TEST_CASE13_STK_SRC_CFG:
      return "HA STK CFG TC13";         
    case TEST_CASE14_STK_SRC_CFG:
      return "HA STK CFG TC14";         
    case TEST_CASE15_STK_SRC_CFG:
      return "HA STK CFG TC15";         
    case TEST_CASE16_STK_SRC_CFG:
      return "HA STK CFG TC16";         
    case TEST_CASE17_STK_SRC_CFG:
      return "HA STK CFG TC17";         
     case TEST_CASE18_STK_SRC_CFG:
      return "HA STK CFG TC18";       
    case TEST_CASE19_STK_SRC_CFG:
      return "HA STK CFG TC19";   
    case TEST_CASE20_STK_SRC_CFG:
      return "HA STK CFG TC20";   
    case TEST_CASE21_STK_SRC_CFG:
      return "HA STK CFG TC21";         
    case TEST_CASE22_STK_SRC_CFG:
      return "HA STK CFG TC22";         
    case TEST_CASE23_STK_SRC_CFG:
      return "HA STK CFG TC23";         
    case TEST_CASE24_STK_SRC_CFG:
      return "HA STK CFG TC24";         
    case TEST_CASE25_STK_SRC_CFG:
      return "HA STK CFG TC25";      
    case TEST_CASE26_STK_SRC_CFG:
      return "HA STK CFG TC26";   
    case TEST_CASE27_STK_SRC_CFG:
      return "HA STK CFG TC27";   
    case TEST_CASE28_STK_SRC_CFG:
      return "HA STK CFG TC28";   
    case TEST_CASE29_STK_SRC_CFG:
      return "HA STK CFG TC29";   
    case TEST_CASE30_STK_SRC_CFG:
      return "HA STK CFG TC30";  
    case TEST_CASE31_STK_SRC_CFG:
      return "HA STK CFG TC31";         
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
  }
  return NULL;
}

I_Void ExecuteStkGroup(I_U32 testCaseId) 
{
  switch (testCaseId) {
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
    case TEST_CASE_STK_SRC_CFG_ALL:
    case TEST_CASE1_STK_SRC_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE1_STK_SRC_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);      
      //fStkSrcCfgTC1();
      //PRINT_TEST_RESULT();      
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE2_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE2_STK_SRC_CFG;  
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkSrcCfgTC2();    
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE3_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE3_STK_SRC_CFG;   
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkSrcCfgTC3();
      
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }      
    case TEST_CASE4_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE4_STK_SRC_CFG;    
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC4();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }       
    case TEST_CASE5_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE5_STK_SRC_CFG;
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC5();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }    
    case TEST_CASE6_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE6_STK_SRC_CFG;    
      TEST_RESULT=0;   
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC6();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }      
    case TEST_CASE7_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE7_STK_SRC_CFG;  
      TEST_RESULT=0; 
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC7();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }        
    case TEST_CASE8_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE8_STK_SRC_CFG;  
      TEST_RESULT=0;   
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC8();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE9_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE9_STK_SRC_CFG;   
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC9();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }      
    case TEST_CASE10_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE10_STK_SRC_CFG;    
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC10();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE11_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE11_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC11();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }   
    case TEST_CASE12_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE12_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC12();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }   
    case TEST_CASE13_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE13_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC13();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }    
    case TEST_CASE14_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE14_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC14();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      } 
    case TEST_CASE15_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE15_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC15();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      } 
    case TEST_CASE16_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE16_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC16();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      } 
    case TEST_CASE17_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE17_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC17();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE18_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE18_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC18();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }  
    case TEST_CASE19_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE19_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC19();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }  
    case TEST_CASE20_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE20_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC20();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }  
    case TEST_CASE21_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE21_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC21();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }        
    case TEST_CASE22_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE22_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC22();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }        
    case TEST_CASE23_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE23_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkSrcCfgTC23();
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }        
    case TEST_CASE24_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE24_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC24();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }        
    case TEST_CASE25_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE25_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC25();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }   
    case TEST_CASE26_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE26_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC26();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }     
     case TEST_CASE27_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE27_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC27();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE28_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE28_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkSrcCfgTC28();
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE29_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE29_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC29();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE30_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE30_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC30();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE31_STK_SRC_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE31_STK_SRC_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkSrcCfgTC31();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_SRC_CFG_ALL != testCaseId ) {
        break;
      }       
  }
  return ;
}

