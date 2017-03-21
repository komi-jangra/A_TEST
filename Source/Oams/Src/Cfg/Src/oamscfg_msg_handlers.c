/***********************************File Header *************************** 
  File Name        : oamcfg_msg_handler.c 
Purpose          : This file contains function definitions for message
handlers for different CFG interfaces. 
Project          : BSC 
Subsystem        : OAMS 
Author           : Aricent Bangalore 
CSCI ID          : 
Version          : 
 ************************************* End **********************************/ 
#include <oamscfg_includes.h> 
#ifdef CFG_UT
#define BSC_API_SET_CELLDATASTRUCT 0
#define BSC_API_SET_NSVCDATASTRUCT 1
#define BSC_API_LOCK_BSS 2
#define BSC_API_UNLOCK_BSS 3
#define BSC_API_UNLOCKINPROGRESS_BSS 4
#define BSC_API_LOCKINPROGRESS_BSS 5
#endif 
/**** SPR- Start*********/
/* static timer_t     tid; */               // timer ID for timer

/**** SPR- End *********/
void dispachToObjectHandler(I_U8  objectTypeRecvd); 

void cmMsgHandler() 
{ 
  sCmMsg* receivedCmMsgPtr = 0; 
  /* CS4.0: SwM Changes start */ 
  SwMOfferTableApi *offerRecievedMsgPtr = NULL;
  SwMNodeTableApi *nodeRecievedMsgPtr = NULL;
  SwMTableApi *swMRecievedMsgPtr = NULL;
  OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
  I_U8 chasisFrameId = 0xFF;
  I_U8 slotId = 0xFF;
#ifdef CFG_UT
  CellDataStruct *cellDataStructPtr;
  CellPerTableApi *CellTableApiPtr = NULL;
  I_U32 rowCount = ZERO;
  I_U16 outSize = ZERO;
  I_U8 index = 0;
  NsvcDataStruct *nsvcDataStructPtr;
  NsvcTableApi *nsvcTableApiPtr = NULL;
#endif
  /* CS4.0: SwM Changes End */ 
  /* Changes for OMCIP */
  receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf; 
  if(receivedCmMsgPtr->sHdr.msgType == OAM_CM_CFG_SET_IP_ADDRESS_RESP)
  {
    LOG_PRINT(LOG_INFO,"Recieved OAM_CM_CFG_SET_IP_ADDRESS_RESP from CM..");
    LOG_PRINT(LOG_DEBUG,"Result Received %d" ,((OamCmCfgSetIpAddressResp*)receivedCmMsgPtr)->result);
    return;
  }
  if(receivedCmMsgPtr->sHdr.msgType == OAM_OMCINTF_CM_UP)
  {
    LOG_PRINT(INFO,"Received OMCINTF_CM_UP from CM");
    LOG_PRINT(INFO,"Sending OMC_UP Alarm to AFH");
    if(getActiveIccSlotId(&chasisFrameId, &slotId) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"No Active card is there. Key1, Key2 will be Inavlid");
    }
    OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = EVENT_OMC_CONNECTION_UP;
    OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    //OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_ICC;
    OamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BSSNODE; //Cloud Changes
    OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = chasisFrameId;
    OamsCfgAfhSysAlarmBuff.sysAlarm.key2 = slotId; 
    LOG_PRINT(DEBUG,"1U: EVENT_OMC_CONNECTION_UP::OBJECT_TYPE changed from OAMS_OBJTYPE_ICC ==>> OAMS_OBJTYPE_BSS & slotId changed from [%d] ==>> [%d]",slotId,slotId-2);
    OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"OMC Connection Up on ChasisId [%u],  SlotId[%u]", chasisFrameId, slotId-2);
    cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

    return;
  } 

  if(receivedCmMsgPtr->sHdr.msgType == OAM_OMCINTF_CM_DOWN)
  {
    LOG_PRINT(INFO,"Received OMCINTF_CM_DOWN from CM");
    LOG_PRINT(INFO,"Sending OMC_DOWN Alarm to AFH");
    if(getActiveIccSlotId(&chasisFrameId, &slotId) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"No Active card is there. Key1, Key2 will be Inavlid");
    }
    OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = EVENT_OMC_CONNECTION_DOWN;
    OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    //OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_ICC;
    OamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BSSNODE;  //Cloud Changes
    OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = chasisFrameId;
    OamsCfgAfhSysAlarmBuff.sysAlarm.key2 = slotId; 
    LOG_PRINT(DEBUG,"1U: EVENT_OMC_CONNECTION_DOWN::OBJECT_TYPE changed from OAMS_OBJTYPE_ICC ==>> OAMS_OBJTYPE_BSS & slotId changed from [%d] ==>> [%d]",slotId,slotId-2);
    OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"OMC Connection Down on ChasisId [%u], SlotId [%u]", chasisFrameId, slotId-2);
    cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

    /* R2.4 changes start */
    sendIntfDownForInternalCbsToCbsh();
    /* R2.4 changes end */
    return;
  }
  /* R2.4 Change Start */
  if(receivedCmMsgPtr->sHdr.msgType == OAM_CM_CFG_ADD_NODE_SUCCESS_IND)
  {
    LOG_PRINT(INFO,"Received OAM_CM_CFG_ADD_NODE_SUCCESS_IND");
    sendIntfUpForInternalCbsToCbsh();
    return;
  }

  /* R2.4 Change End */

  if ( gCfgState != CFG_READY )
  {
    LOG_PRINT(LOG_CRITICAL,"CFG is not in Ready State ");  
    cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
    return ;
  }    
  LOG_PRINT(LOG_DEBUG," cmHdr.size  = %d ",receivedCmMsgPtr->cmHdr.size);
  gCmTrasId = receivedCmMsgPtr->cmHdr.txnId;
  resetStackObject();            /* CS4.0 HA Stack Changes */
  switch (receivedCmMsgPtr->sHdr.msgType) 
  {
    /*BSC CS4.0 HA Changes Starts*/
    /*   case OAM_CM_CFG_SET_OMC_IP_ADDRESS_RESP:
         LOG_PRINT(LOG_INFO,"Recieved OAM_CM_CFG_SET_OMC_IP_ADDRESS_RESP from CM..");

         break;*/
    case BSC_API_SET_MLPPPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_MLPPPCONFIGTABLE from CM..");
      setMlpppConfigTableHandler();
      break;

    case BSC_API_SET_CARDSTATECHANGETABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_CARDSTATECHANGETABLE from CM..");
      setCardStateChangeTableHandler();
      break;
      /*BSC CS4.0 HA Changes Ends*/
      /* Changes For CS2.2 : Starts */ 
    case BSC_API_SET_BTSTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_BTSTABLE from CM..");
      setBicTableHandler();
      break;
    case BSC_API_DEL_BTSTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_BTSTABLE from CM..");
      delBicTableHandler();
      break;
    case BSC_API_SET_TRXTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_TRXTABLE from CM..");
      setTrxTableHandler();
      break;
    case BSC_API_DEL_TRXTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_TRXTABLE from CM..");
      delTrxTableHandler();
      break;
      /* Changes For CS2.2 : Ends */

    case BSC_API_SET_BSSTABLE: 
      setBssTableHandler(); 
      break; 

    case BSC_API_SET_CELLPERTABLE: 
      setCellTableHandler(); 
      break;  

    case BSC_API_SET_TRUNKPERTABLE: 
      setE1TableHandler(); 
      break;          
      /* Changes for R2.2 : Start */
#if 0

    case BSC_API_SET_ABISTIMESLOTPERTABLE: 
      setTimeSlotTableHandler(); 
      break;          
#endif
      /* Changes for R2.2 : End */

    case BSC_API_SET_PSCELLTABLE: 
      /* setPsCellTableHandler(); */
      cellObjectHandler(); 
      break; 

    case BSC_API_SET_CSEXTERNALCELLTABLE: 
      setCsExternalCellTableHandler(); 
      break;           
    case BSC_API_SET_LATABLE: 
      setLaTableHandler(); 
      break;          

    case BSC_API_SET_PTDCCONFIGTABLE: 
      setPtdcConfigTableHandler(); 
      break;          
    case BSC_API_DEL_PTDCCONFIGTABLE: 
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
      break;          

    case BSC_API_SET_RATABLE: 
      setRaTableHandler(); 
      break;          

    case BSC_API_SET_CHNGRPTABLE: 
      setChnGrpTableHandler(); 
      break;          

    case BSC_API_SET_CSNEIGHCELLSTABLE: 
      setCsNeighCellsTableHandler(); 
      break;                

    case BSC_API_SET_ARFCNLISTTABLE: 
      setArfcnListTableHandler(); 
      break;          

    case BSC_API_SET_AINTERFACETABLE: 
      setAInterfaceTableHandler(); 
      break;          

#if 0 /* CS4.0 HA Stack Changes */
    case BSC_API_SET_SCCPSSNCONFIGTABLE: 
      setSccpSsnConfigTableHandler(); 
      break;    

    case BSC_API_SET_SCCPCSSNCONFIGTABLE: 
      setSccpCssnConfigTableHandler(); 
      break;       
    case BSC_API_SET_MTP3LINKSETTABLE:
      {
        setMtp3LinksetTableHandler();
      }
      break;       

    case BSC_API_SET_MTP3ROUTETABLE:
      setMtp3RouteTableHandler();
      break;       

    case BSC_API_SET_MTP3LINKSETSTSTABLE:
      setMtp3LinkSetStsTableHandler();
      break;
    case BSC_API_SET_MTP3LINKTABLE:
      setMtp3LinkTableHandler();
      break;          
#endif

    case BSC_API_SET_LEPINFOTABLE: 
      setLepInfoTableHandler(); 
      break; 

    case BSC_API_SET_REPINFOTABLE: 
      setRepInfoTableHandler(); 
      break;          

    case BSC_API_SET_GBINTERFACETABLE: 
      setGbInterfaceTableHandler(); 
      break;          

    case BSC_API_SET_NSVCTABLE: 
      LOG_PRINT(LOG_INFO,"Message Type : %d",receivedCmMsgPtr->sHdr.msgType); 
      setNsvcTableHandler(); 
      break;          

    case BSC_API_SET_FRLINKTABLE: 
      setFrLinkTableHandler(); 
      break;          
      /*Changes PCU R2.5 Aricent -- START*/
    case BSC_API_SET_BSSPSTABLE:
      setBssPsTableHandler();
      break;
      /*Changes PCU R2.5 Aricent -- END*/
#if 0 /* CS4.0 HA Stack Changes */ 
    case BSC_API_SET_SKSCOMMONTABLE: 
      setSksCommonTableHandler(); 
      break;          

    case BSC_API_SET_SKSLINKSTARTTABLE: 
      setSksLinkstartTableHandler();
      break;       
    case BSC_API_SET_BSSAPPCSSNCONFIGTABLE:
      setBssapPcSsnConfigTableHandler();
      break;
    case BSC_API_SET_SKSGENCFGTABLE: 
#endif
    case BSC_API_SET_SYSOMCREGISTERTABLE:
      setSysOmcRegisterTableHandler();
      break;   
    case BSC_API_SET_SYSOMCCONFIGTABLE:         
      setSysOmcConfigTableHandler();
      break;
    case BSC_API_SET_CSPWRCTRLTABLE:
      setCsPwrCtrlTableHandler();
      break;
    case BSC_API_DEL_CSPWRCTRLTABLE:
      delCsPwrCtrlTableHandler();
      break;
      /* CS3.0 Changes : Start  */
      /* CS4.0: SwM Changes start */ 
    case BSC_API_SET_SWMOFFERTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_SWMOFFERTABLE from CM..");
      offerRecievedMsgPtr = (SwMOfferTableApi *)(((I_U8 *)gCfgMsgBuf) + sizeof(sCmMsg));
      LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",offerRecievedMsgPtr->upgradeVersion);
      LOG_PRINT(LOG_INFO,"NodeType: %d ",offerRecievedMsgPtr->nodeType);
      LOG_PRINT(LOG_INFO,"slotId: %d ",offerRecievedMsgPtr->slotId);
      LOG_PRINT(LOG_INFO,"ftpServerAddress: %u",offerRecievedMsgPtr->ftpServerAddress);
      if (offerRecievedMsgPtr->nodeType == SYS_NODE_TYPE_EIC)
        //setEicSwMOfferTableHandler();
        /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
        cfgSendNackToCm(CM_ERR_INVALID_REQUEST); 
      else if (offerRecievedMsgPtr->nodeType == SYS_NODE_TYPE_DSP)
        //setDspSwMOfferTableHandler(); //BSCR2.0
        /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
        cfgSendNackToCm(CM_ERR_INVALID_REQUEST); 
      else
        setSwMOfferTableHandler();
      break;
    case BSC_API_SET_SWMNODETABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_SWMNODETABLE from CM..");
      nodeRecievedMsgPtr = (SwMNodeTableApi *)(((I_U8 *)gCfgMsgBuf) + sizeof(sCmMsg));
      if (nodeRecievedMsgPtr->nodeType == SYS_NODE_TYPE_EIC)
        cfgSendNackToCm(CM_ERR_INVALID_REQUEST); 
        /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
        //setEicSwMNodeTableHandler();
      else if (nodeRecievedMsgPtr->nodeType == SYS_NODE_TYPE_DSP)//BSCR2.0
      {
        cfgSendNackToCm(CM_ERR_INVALID_REQUEST); 
        /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
        //setDspSwMNodeTableHandler();
      }
      else
        setSwMNodeTableHandler();
      break;
      /* CS4.0: SwM Changes End */
    case BSC_API_SET_HOCTRLTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_HOCTRLTABLE from CM..");
      setHoCtrlTableHandler();
      break; 
      /* R2.2 Changes
         case BSC_API_SET_TRAUULFRAMESTATUSTABLE:
         LOG_PRINT(LOG_INFO,"Received BSC_API_SET_TRAUULFRAMESTATUSTABLE from SNMP..");
         updateTrauUlFrameStatus();
         break;
       */   
      /* CS3.0 Changes : End  */
    case BSC_API_DEL_SYSOMCREGISTERTABLE:
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
      break;   
    case BSC_API_DEL_SYSOMCCONFIGTABLE:         
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
      break;
    case BSC_API_DEL_BSSTABLE: 
      delBssTableHandler(); 
      break;          
    case BSC_API_DEL_CELLPERTABLE: 
      /*Changes PCU R2.5 Aricent -- START*/
      cellObjectHandler();
      /*Changes PCU R2.5 Aricent -- END*/
      break;          

    case BSC_API_DEL_TRUNKPERTABLE: 
      delE1TableHandler(); 
      break;          

    case BSC_API_DEL_ABISTIMESLOTPERTABLE: 
      delTimeSlotTableHandler(); 
      break;          

    case BSC_API_DEL_PSCELLTABLE: 
      /* delPsCellTableHandler(); */
      cellObjectHandler(); 
      break;       

    case BSC_API_DEL_CSEXTERNALCELLTABLE: 
      delCsExternalCellTableHandler(); 
      break;          

    case BSC_API_DEL_LATABLE: 
      delLaTableHandler(); 
      break;    

    case BSC_API_DEL_RATABLE: 
      delRaTableHandler(); 
      break;       

    case BSC_API_DEL_CHNGRPTABLE: 
      delChnGrpTableHandler(); 
      break;          

    case BSC_API_DEL_CSNEIGHCELLSTABLE: 
      delCsNeighCellTableHandler(); 
      break;          

    case BSC_API_DEL_ARFCNLISTTABLE: 
      delArfcnListTableHandler(); 
      break;          

    case BSC_API_DEL_AINTERFACETABLE: 
      delAInterfaceTableHandler(); 
      break;          
#if 0 /* CS4.0 HA Stack Changes */ 
    case BSC_API_DEL_SCCPSSNCONFIGTABLE: 
      delSccpSsnConfigTableHandler();
      break;          
    case BSC_API_DEL_SCCPCSSNCONFIGTABLE: 
      delSccpCSSNConfigTableHandler();
      break;       

    case BSC_API_DEL_MTP3LINKSETTABLE: 
      delMtp3LinksetTableHandler(); 
      break;    

    case BSC_API_DEL_MTP3ROUTETABLE: 
      delMtp3RouteTableHandler();
      break;       

    case BSC_API_DEL_MTP3LINKSETSTSTABLE:
      delMtp3LinksetStsTableHandler();
      break;

    case BSC_API_DEL_MTP3LINKTABLE: 
      delMtp3LinkTableHandler();
      break;    
#endif

    case BSC_API_DEL_LEPINFOTABLE: 
      delLepInfoTableHandler(); 
      break;       

    case BSC_API_DEL_REPINFOTABLE: 
      delRepInfoTableHandler(); 
      break; 
    case BSC_API_DEL_NSVCTABLE: 
      nsvcObjectHandler(); 
      break;          

    case BSC_API_DEL_FRLINKTABLE: 
      delFrLinkTableHandler(); 
      break;          

#if 0 /* CS4.0 HA Stack Changes */ 
    case BSC_API_DEL_SKSCOMMONTABLE: 
      delSksCommonTableHandler();
      break;          
    case BSC_API_DEL_SKSLINKSTARTTABLE: 
      delSksLinkstartTableHandler();
      break;    
    case BSC_API_DEL_BSSAPPCSSNCONFIGTABLE:
      delBssapPcSsnConfigTableHandler();
      break;
    case BSC_API_DEL_SKSGENCFGTABLE: 
#endif
      /*CS3.0 changes : Start */
      /* CS4.0: SwM Changes Start */
    case BSC_API_DEL_SWMTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_SWMTABLE from CM..");
      swMRecievedMsgPtr = (SwMTableApi *)(((I_U8 *)gCfgMsgBuf) + sizeof(sCmMsg));
      if (swMRecievedMsgPtr->nodeType == SYS_NODE_TYPE_EIC)
        /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
        cfgSendNackToCm(CM_ERR_INVALID_REQUEST); 
        //eicDelSwMTableHandler();
      if (swMRecievedMsgPtr->nodeType == SYS_NODE_TYPE_DSP)
      {		 
        LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_SWMTABLE for DSP..");
        /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
        cfgSendNackToCm(CM_ERR_INVALID_REQUEST); 
        //dspDelSwMTableHandler();
      }
      else
        delSwMTableHandler();
      break;
      /* CS4.0: SwM Changes End */
    case BSC_API_DEL_HOCTRLTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_HOCTRLTABLE from CM..");
      delHoCtrlTableHandler();
      break; 

      /*CS3.0 changes : End */
      /* Handling SET/DEL for preconfigued tables is not allowed*/
      /* CS4.0 HA Stack Changes :Start */
      /* case BSC_API_SET_PPRESOURCEPRECONFIGUREDTABLE:
         case BSC_API_SET_NAILUPTABLE:  
         case BSC_API_SET_BSSAPCICCONFIGTABLE: 
         case BSC_API_SET_TRXVERSIONTABLE: 
         case BSC_API_SET_SCCPGTTDPCSSNCONFIGTABLE:
         case BSC_API_SET_SCCPGTTDPCCONFIGTABLE:
         case BSC_API_SET_SCCPGTTSSNCONFIGTABLE:
         case BSC_API_SET_SCCPGTTENABLETABLE: 
         case BSC_API_SET_MTP3TIMERTABLE:
         case BSC_API_SET_BSSAPTIMERTABLE:
         case BSC_API_SET_SCCPTIMERTABLE:
         case BSC_API_SET_LAPDTIMERTABLE: */
      /* CS4.0 HA Stack Changes :End */
    case BSC_API_SET_DSPTRAURESOURCEMAPTABLE : 
    case BSC_API_SET_MCCLINKRESOURCETABLE:
    case BSC_API_SET_TRAUCONFIGTABLE:
    case BSC_API_SET_E1STREAMMAPTABLE:
    case BSC_API_SET_SIPRECONFIGTABLE:
    case BSC_API_SET_NSTIMERTABLE:
    case BSC_API_SET_BSSGPTIMERTABLE:
      /* Changes for R2.2 : Start */
      //      case BSC_API_SET_LAPDSAPICONFIGTABLE:
      //      case BSC_API_SET_LAPDTSCONFIGTABLE:
      /* Changes for R2.2 : End */
    case BSC_API_SET_LAPDTEICONFIGTABLE:
      //case BSC_API_SET_SCCPBEHAVIORCONFIGTABLE:
    case BSC_API_SET_STATICALARMCONFIGURATIONTABLE:
    case BSC_API_SET_BSSCSPRECONFIGTABLE:
    case BSC_API_SET_BSSPSPRECONFIGTABLE:
    case BSC_API_SET_CSPWRCTRLPRECONFIGTABLE:
    case BSC_API_SET_SWMPRECONFIGTABLE:
    case BSC_API_SET_HOCTRLPRECONFIGTABLE:
    case BSC_API_SET_PTRXTABLE:
    case BSC_API_SET_TRUNKGROUPTABLE:
    case BSC_API_SET_SKSGENCONFIGTABLE: 
      cfgSendNackToCm(CM_ERR_SET_OBJ_NOT_ALLOWED);
      break;
    case BSC_API_DEL_TRAUCONFIGTABLE:
    case BSC_API_DEL_DSPTRAURESOURCEMAPTABLE:
      /* CS4.0 HA Stack Changes :Start */
      /* case BSC_API_DEL_PPRESOURCEPRECONFIGUREDTABLE:
         case BSC_API_DEL_NAILUPTABLE:
         case BSC_API_DEL_BSSAPCICCONFIGTABLE:
         case BSC_API_DEL_SCCPGTTDPCSSNCONFIGTABLE:
         case BSC_API_DEL_SCCPGTTDPCCONFIGTABLE:
         case BSC_API_DEL_SCCPGTTSSNCONFIGTABLE:
         case BSC_API_DEL_SCCPGTTENABLETABLE: */
    case BSC_API_DEL_MCCLINKRESOURCETABLE:
    case BSC_API_DEL_E1STREAMMAPTABLE:
    case BSC_API_DEL_SIPRECONFIGTABLE:
    case BSC_API_DEL_SCCPTIMERTABLE:
    case BSC_API_DEL_MTP3TIMERTABLE:
    case BSC_API_DEL_BSSGPTIMERTABLE:
    case BSC_API_DEL_NSTIMERTABLE :
    case BSC_API_DEL_LAPDTIMERTABLE:
      /* Changes for R2.2 : Start */
      // case BSC_API_DEL_LAPDSAPICONFIGTABLE:
      // case BSC_API_DEL_LAPDTSCONFIGTABLE:
      /* Changes for R2.2 : End */
    case BSC_API_DEL_LAPDTEICONFIGTABLE:
      //case BSC_API_DEL_SCCPBEHAVIORCONFIGTABLE:
    case BSC_API_DEL_BSSAPTIMERTABLE:
    case BSC_API_DEL_STATICALARMCONFIGURATIONTABLE:
    case BSC_API_DEL_BSSCSPRECONFIGTABLE:
    case BSC_API_DEL_BSSPSPRECONFIGTABLE:
    case BSC_API_DEL_PTRXTABLE:
    case BSC_API_DEL_CSPWRCTRLPRECONFIGTABLE:
    case BSC_API_DEL_SWMPRECONFIGTABLE:
    case BSC_API_DEL_HOCTRLPRECONFIGTABLE:
    case BSC_API_DEL_GBINTERFACETABLE:        /* CCB Pcu# 6 */
    case BSC_API_DEL_TRUNKGROUPTABLE:
    case BSC_API_DEL_SKSGENCONFIGTABLE: 
      /*Changes PCU R2.5 Aricent -- START*/
    case BSC_API_DEL_BSSPSTABLE:
      /*Changes PCU R2.5 Aricent -- END*/ 
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
      break;
    case BSC_API_SET_TRUNKPORTTABLE: // CS4.0 Enable/Disable 
      setTrunkPortTableHandler(); // CS4.0 Enable/Disable 
      break;
      /*BB, Start , CS4.0 , Clock Source Configuration */   
    case BSC_API_SET_CLKSOURCECONFIGTABLE: 
      setClkSrcTblHdlr();
      break;
    case BSC_API_DEL_CLKSOURCECONFIGTABLE: 
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
      break;         
      /*BB, End , CS4.0 , Clock Source Configuration */

      /* CS4.0 HA Stack Changes : Start */
    case BSC_API_SET_SS7STACKCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_SS7STACKCONFIGTABLE from CM..");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST); 
      /*if (gStackStatus == SS7_STACK_UP) IP_BSC_STACK
        setSs7StackTableHandler();  
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      break;
    case BSC_API_DEL_SS7STACKCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_SS7STACKCONFIGTABLE from CM..");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST); 
      /*if (gStackStatus == SS7_STACK_UP) IP_BSC_STACK
        delSs7StackTableHandler(); 
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      break;
    case BSC_API_SET_AIFINTERFACETABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_AIFINTERFACETABLE from CM..");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST); 
      /*if (gStackStatus == SS7_STACK_UP) IP_BSC_STACK 
        setAifInterfaceTableHandler();
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      break;
    case BSC_API_DEL_AIFINTERFACETABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_AIFINTERFACETABLE from CM..");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST); 
      /*if (gStackStatus == SS7_STACK_UP) IP_BSC_STACK
        delAifInterfaceTableHandler(); 
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      break;
#if 0 /* Abis Interface is removed */
    case BSC_API_SET_ABISINTERFACETABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_ABISINTERFACETABLE from CM..");
      setAbisInterfaceTableHandler();
      break;
    case BSC_API_DEL_ABISINTERFACETABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_ABISINTERFACETABLE from CM..");
      delAbisInterfaceTableHandler();
      break;
#endif
    case BSC_API_SET_AIFTRUNKTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_AIFTRUNKTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
        setTrunkTableHandler();
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
      break;
    case BSC_API_DEL_AIFTRUNKTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_AIFTRUNKTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
        delTrunkTableHandler(); 
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
      break;
    case BSC_API_SET_CICTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_CICTABLE from CM..");
      setCicTableHandler();
      break;
    case BSC_API_SET_LINKSETTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_LINKSETTABLE from CM..");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST); /*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
      /*if (gStackStatus == SS7_STACK_UP)
        setLinkSetTableHandler();
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      break;
    case BSC_API_DEL_LINKSETTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_LINKSETTABLE from CM..");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST); /*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
      /*if (gStackStatus == SS7_STACK_UP)
        delLinkSetTableHandler(); 
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      break;
    case BSC_API_SET_LINKTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_LINKTABLE from CM..");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST); /*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
      /*if (gStackStatus == SS7_STACK_UP)
        setLinkTableHandler();
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      break;
    case BSC_API_DEL_LINKTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_LINKTABLE from CM..");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST); /*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
      /*if (gStackStatus == SS7_STACK_UP)
        delLinkTableHandler();
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      break;
    case BSC_API_SET_SS7ROUTETABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_SS7ROUTETABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
        setSs7RouteTableHandler();
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
      break;
    case BSC_API_DEL_SS7ROUTETABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_SS7ROUTETABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
        delSs7RouteTableHandler(); 
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
      break;
    case BSC_API_SET_MTP3TIMERTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_MTP3TIMERTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
        setMtp3TimerTable();
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
      break;
    case BSC_API_SET_SCCPTIMERTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_SCCPTIMERTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
        setSccpTimerTable();
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
      break;
    case BSC_API_SET_BSSAPTIMERTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_BSSAPTIMERTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
        setBssapTimerTable();
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
      break;
    case BSC_API_SET_LAPDTIMERTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_LAPDTIMERTABLE from CM..Not Allowed");
#if 0
      if (gStackStatus == SS7_STACK_UP)
        setLapdTimerTable();
      else 
      {
        LOG_PRINT(DEBUG,"Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
#endif 
      break;

      /* CS4.0 HA Stack Changes : End */
      /* Change For CS4.0 CCU : Start */
    case BSC_API_SET_CCCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_CCCONFIGTABLE from CM..");
      setCcConfigTable();
      break;
    case BSC_API_SET_CCDATAREQTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_CCDATAREQTABLE from CM..");
      setCcDataReqTable();
      break;
      /*BSC R2.0 Changes Starts*/
#if 0
    case BSC_API_SET_BICCCPOWERORDERTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_BICCCPOWERORDERTABLE from CM..");
      setBicPowerOrderTable();
      break;
#endif
      /*BSC R2.0 Changes Ends*/
    case BSC_API_SET_CCPOWERORDERTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_CCPOWERORDERTABLE from CM..");
      setCcPowerOrderTable();
      break; 
      /* Change For CS4.0 CCU : End */

      /*BSC R2.0 Changes Starts*/
    case BSC_API_SET_DSPINFOTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_DSPINFOTABLE from CM..");
      //setDspObjectHandler();
	 /*Above function commented for cloud as DSP LOCK_UNLOCK FEATURE not supported in CLOUD BSC 13 Jan 2016 Gaurav Sinha*/
      LOG_PRINT(LOG_INFO,"DSP LOCK/UNLOCK procedure not supported in CLOUD-BSC ... Sending NACK..");
			cfgSendNackToCm(CM_ERR_DSP_INVALID_REQUEST);
      break;  

    case BSC_API_SET_BSCDATETIMETABLE :
      LOG_PRINT(DEBUG,"Received BSC_API_SET_BSCDATETIMETABLE from CM..");
      setBscDateTimeTableHandler(); 
      break; 
      /* R2.4 changes start */
    case BSC_API_SET_CBSCONFIGURATIONTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_CBSCONFIGURATIONTABLE from CM..");
      setCbsConfigurationHandler();
      break; 
    case BSC_API_DEL_CBSCONFIGURATIONTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_CBSCONFIGURATIONTABLE from CM..");
      delCbsConfigurationHandler();
      break; 
      /* R2.4 changes End */


#ifdef CFG_UT
      /*For Testing R2.5 Start*/
    case BSC_API_SET_CELLDATASTRUCT:
      cellDataStructPtr = (CellDataStruct*)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
      index = getCellDataStruct(cellDataStructPtr->CellID,cellDataStructPtr->lac);        
      if (index == CFG_MAX_NUM_CELLS)
      {
        if(DBLIB_SUCCESS != getallCellPerTable(&CellTableApiPtr, &rowCount, &outSize))
        {
          LOG_PRINT(LOG_INFO,"DB CALL getallCellPerTable failed or No Row Exist in CellTable");
        }
        else
        {
          if(rowCount != 0)
          {
            LOG_PRINT(LOG_INFO, "Updating CELL Data Struct at index = %u", rowCount-1);
            gCellData[rowCount - 1].Availlability     =  cellDataStructPtr->Availlability;
            gCellData[rowCount - 1].CellState         =  cellDataStructPtr->CellState;
            gCellData[rowCount - 1].CellID            =  cellDataStructPtr->CellID;;
            gCellData[rowCount - 1].adminState        =  cellDataStructPtr->adminState;
            gCellData[rowCount - 1].lac               =  cellDataStructPtr->lac;
            gCellData[rowCount - 1].reqType           =  cellDataStructPtr->reqType;
            free(CellTableApiPtr);
          }
          else
          {
            gCellData[rowCount].Availlability     =  cellDataStructPtr->Availlability;
            gCellData[rowCount].CellState         =  cellDataStructPtr->CellState;
            gCellData[rowCount].CellID            =  cellDataStructPtr->CellID;;
            gCellData[rowCount].adminState        =  cellDataStructPtr->adminState;
            gCellData[rowCount].lac               =  cellDataStructPtr->lac;
            gCellData[rowCount].reqType           =  cellDataStructPtr->reqType;
            free(CellTableApiPtr);
          }
        } 
      }
      else
      {
        gCellData[index].CellState = cellDataStructPtr->CellState;
      }
      break;
    case BSC_API_SET_NSVCDATASTRUCT:
      nsvcDataStructPtr = (NsvcDataStruct*)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
      index = getNsvcDataStruct(nsvcDataStructPtr->nsvcId);
      rowCount = 0;
      if (index == OAMS_CFG_MAX_NUM_NSVCS)
      {
        if (DBLIB_SUCCESS != getallNsvcTable(&nsvcTableApiPtr, &rowCount, &outSize))
        {
          LOG_PRINT(LOG_INFO, "No entry in DB");
        }
        if (rowCount != 0)
        {
          LOG_PRINT(LOG_INFO, "Updating NSVC Data Struct at index = %u", rowCount-1);
          gNsvcData[rowCount - 1].nsvcState    = nsvcDataStructPtr->nsvcState;
          gNsvcData[rowCount - 1].availability = nsvcDataStructPtr->availability;
          gNsvcData[rowCount - 1].nsvcId       = nsvcDataStructPtr->nsvcId;
          gNsvcData[rowCount - 1].reqType      = nsvcDataStructPtr->reqType;
          free(nsvcTableApiPtr);
        }
        else
        {
          gNsvcData[rowCount].nsvcState    = nsvcDataStructPtr->nsvcState;
          gNsvcData[rowCount].availability = nsvcDataStructPtr->availability;
          gNsvcData[rowCount].nsvcId       = nsvcDataStructPtr->nsvcId;
          gNsvcData[rowCount].reqType      = nsvcDataStructPtr->reqType;
          free(nsvcTableApiPtr);
        }
      }
      else
      {
        gNsvcData[index].nsvcState = nsvcDataStructPtr->nsvcState; 
      }
      break;
    case BSC_API_LOCK_BSS:
      LOG_PRINT(LOG_INFO, "Setting BSS LOCK");
      gBssState = locked;
      break;
    case BSC_API_UNLOCK_BSS:
      LOG_PRINT(LOG_INFO, "Setting BSS UNLOCK");
      gBssState = unlocked;
      break;
    case BSC_API_UNLOCKINPROGRESS_BSS:
      LOG_PRINT(LOG_INFO, "Setting BSS UNLOCK In Progress");
      gBssState = unlockInProgress;
      break;
    case BSC_API_LOCKINPROGRESS_BSS:
      LOG_PRINT(LOG_INFO, "Setting BSS LOCK In Progress");
      gBssState = lockInProgress;
      break;
      /*For Testing R2.5 End*/
#endif

      /*Changes for DIAGNOSTICS R2.5.5 Start*/
    case BSC_API_SET_ICCDIAGTABLE :
    case BSC_API_SET_EICDIAGTABLE :
    case BSC_API_SET_PWRSUPDIAGTABLE :
    case BSC_API_SET_FANTRAYDIAGTABLE :
    /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
    case BSC_API_SET_OBMDIAGTABLE:
    case BSC_API_SET_OBFDIAGTABLE:
    /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_XXXDIAGTABLE from CM..");
      if(I_TRUE != gCfgInitDiagLibSucc) 
      {
        LOG_PRINT(DEBUG,"Diagnostic feature is not supported as initDiagLibrary failed");
        cfgSendNackToCm(CM_ERR_DIAGNOSTIC_FEATURE_NOT_SUPPORTED); 
      }
      else
      { 
        setDiagnosticsHandler();
      } 
      break; 
      /*Changes for DIAGNOSTICS R2.5.5 End*/
      /*Changes for TsGroup Start */
    case BSC_API_SET_TSGROUPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_TSGROUPCONFIGTABLE from CM..");
      setTsGroupConfigTableHandler();
      break;
    case BSC_API_DEL_TSGROUPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_TSGROUPCONFIGTABLE from CM..");
      delTsGroupConfigTableHandler();
      break; 
      /*Changes for TsGroup End */
    case BSC_API_SET_EXTERNALINPUTPORTCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_EXTERNALINPUTPORTCONFIGTABLE from CM..");
      setExternalInputPortConfigTableHandler();
      break;
    case BSC_API_DEL_EXTERNALINPUTPORTCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_EXTERNALINPUTPORTCONFIGTABLE from CM..");
      delExternalInputPortConfigTableHandler();
      break; 
    case BSC_API_SET_EXTERNALOUTPUTPORTCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_EXTERNALOUTPUTPORTCONFIGTABLE from CM..");
      setExternalOutputPortConfigTableHandler();
      break;
    case BSC_API_DEL_EXTERNALOUTPUTPORTCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_EXTERNALOUTPUTPORTCONFIGTABLE from CM..");
      delExternalOutputPortConfigTableHandler();
      break; 
    case BSC_API_SET_CLUSTERTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_CLUSTERTABLE from CM..");
      setClusterTableHandler();
      break;
    case BSC_API_DEL_CLUSTERTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_DEL_CLUSTERTABLE from CM..");
      delClusterTableHandler();
      break; 
    case  BSC_API_SET_CALLENDTIMERCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"Recieved BSC_API_SET_CALLENDTIMERCONFIGTABLE from CM..");
      setCallEndTimerConfigTable();
      break; 
/*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
    case BSC_API_SET_BSSAPINTFCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_BSSAPINTFCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
			{
        BssapIntfConfigTableApi *bssapIntfConfigTableApi=NULL;
      	bssapIntfConfigTableApi = (BssapIntfConfigTableApi *)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
		    setBssapInterfaceTable(bssapIntfConfigTableApi);	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_BSSAPINTFCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_BSSAPINTFCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
      {
        BssapIntfConfigTableApi *bssapIntfConfigTableApi=NULL;
      	bssapIntfConfigTableApi = (BssapIntfConfigTableApi *)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
		  	delBssapInterfaceTable(bssapIntfConfigTableApi);	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_SET_SIGTRANSCCPSPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANSCCPSPCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
      {
        SigtranSccpSPConfigTableApi *sigtranSccpSPConfigTableApi=NULL;
      	sigtranSccpSPConfigTableApi = (SigtranSccpSPConfigTableApi *)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
		  	setSccpSpConfigTable(sigtranSccpSPConfigTableApi);	
			}
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANSCCPSPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANSCCPSPCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
      {
        SigtranSccpSPConfigTableApi *sigtranSccpSPConfigTableApi=NULL;
      	sigtranSccpSPConfigTableApi = (SigtranSccpSPConfigTableApi *)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
		  	delSccpSpConfigTable(sigtranSccpSPConfigTableApi);	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_SET_SIGTRANSCCPSSCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANSCCPSSCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
      {
        SigtranSccpSSConfigTableApi *sigtranSccpSSConfigTableApi=NULL;
      	sigtranSccpSSConfigTableApi = (SigtranSccpSSConfigTableApi *)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
		  	setSccpSsConfigTable(sigtranSccpSSConfigTableApi);	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANSCCPSSCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANSCCPSSCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
      {
        SigtranSccpSSConfigTableApi *sigtranSccpSSConfigTableApi=NULL;
      	sigtranSccpSSConfigTableApi = (SigtranSccpSSConfigTableApi *)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
		  	delSccpSsConfigTable(sigtranSccpSSConfigTableApi);	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_SET_SIGTRANSCCPCSSCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANSCCPCSSCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
      {
        SigtranSccpCSSConfigTableApi *sigtranSccpCSSConfigTableApi=NULL;
      	sigtranSccpCSSConfigTableApi = (SigtranSccpCSSConfigTableApi *)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
		    setSccpCssConfigTable(sigtranSccpCSSConfigTableApi);	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANSCCPCSSCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANSCCPCSSCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
      {
        SigtranSccpCSSConfigTableApi *sigtranSccpCSSConfigTableApi=NULL;
      	sigtranSccpCSSConfigTableApi = (SigtranSccpCSSConfigTableApi *)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
		    delSccpCssConfigTable(sigtranSccpCSSConfigTableApi);	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_SET_SIGTRANSCCPCSPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANSCCPCSPCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
      {
        SigtranSccpCSPConfigTableApi *sigtranSccpCSPConfigTableApi=NULL;
      	sigtranSccpCSPConfigTableApi = (SigtranSccpCSPConfigTableApi *)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
		    setSccpCspConfigTable(sigtranSccpCSPConfigTableApi);	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANSCCPCSPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANSCCPCSPCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
      {
        SigtranSccpCSPConfigTableApi *sigtranSccpCSPConfigTableApi=NULL;
      	sigtranSccpCSPConfigTableApi = (SigtranSccpCSPConfigTableApi *)(((I_U8*)receivedCmMsgPtr + sizeof(sCmMsg)));
		    delSccpCspConfigTable(sigtranSccpCSPConfigTableApi);	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_SET_SIGTRANM3UALASPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANM3UALASPCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP) /*Also modifyable - Admin State Only (LOCK/UNLOCK)*/
      {
		    setM3uaLocalAspConfigTable();
      }	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANM3UALASPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANM3UALASPCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP){
		  delM3uaLocalAspConfigTable();	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_SET_SIGTRANM3UARASPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANM3UARASPCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP){
		  setM3uaRemoteAspConfigTable();
      }	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANM3UARASPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANM3UARASPCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP){
		  delM3uaRemoteAspConfigTable();	
      }
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_SET_SIGTRANM3UALASCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANM3UALASCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
		  setM3uaLocalAsConfigTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANM3UALASCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANM3UALASCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
		  delM3uaLocalAsConfigTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_SET_SIGTRANM3UARASCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANM3UARASCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
		  setM3uaRemoteAsConfigTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANM3UARASCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANM3UARASCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
		  delM3uaRemoteAsConfigTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_SET_SIGTRANSCTPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANSCTPCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
		  setSctpConfigTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANSCTPCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANSCTPCONFIGTABLE from CM..");
      /*if (gStackStatus == SS7_STACK_UP)
		  delSctpConfigTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
			break;
/*IP_BSC_STACK - CONFIGURABLE STACK TIMERS - BSSAP/SCCP/M3UA/SCTP */
    case BSC_API_SET_BSSAPTMRCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_BSSAPTMRCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
		  setSigtranBssapTimerTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_BSSAPTMRCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_BSSAPTMRCONFIGTABLE from CM..");
      /*if (gStackStatus == SS7_STACK_UP)
		  delSigtranBssapTimerTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
			break;
    case BSC_API_SET_SIGTRANSCCPTIMERTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANSCCPTIMERTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
		  setSigtranSccpTimerTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANSCCPTIMERTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANSCCPTIMERTABLE from CM..");
      /*if (gStackStatus == SS7_STACK_UP)
		  delSigtranSccpTimerTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
			break;
    case BSC_API_SET_M3UATMRCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_M3UATMRCONFIGTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
		  setSigtranM3uaTimerTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_M3UATMRCONFIGTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_M3UATMRCONFIGTABLE from CM..");
      /*if (gStackStatus == SS7_STACK_UP)
		  delSigtranM3uaTimerTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
			break;
    case BSC_API_SET_SIGTRANSCTPTIMERTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_SET_SIGTRANSCTPTIMERTABLE from CM..");
      if (gStackStatus == SS7_STACK_UP)
		  setSigtranSctpTimerTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }
			break;
    case BSC_API_DEL_SIGTRANSCTPTIMERTABLE:
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Recieved BSC_API_DEL_SIGTRANSCTPTIMERTABLE from CM..");
      /*if (gStackStatus == SS7_STACK_UP)
		  delSigtranSctpTimerTable();	
      else 
      {
        LOG_PRINT(DEBUG,"IP_BSC_STACK: Operation not permitted: Ss7 Stack status is Down");
        cfgSendNackToCm(CM_ERR_SS7_STACK_STATUS_DOWN); 
      }*/
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
			break;
/*IP_BSC_STACK - CONFIGURABLE STACK TIMERS - BSSAP/SCCP/M3UA/SCTP */
/*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
    default :
      /* cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED); */
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
      LOG_PRINT(LOG_CRITICAL,"Invalid message received from CM..");   
      break; 
  } 
} /*cmMsgHandler */    

/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/	  
I_Void send1UCardInfoReqToOil()
{ 
	LOG_PRINT(LOG_INFO,"1U : Entering send1UCardInfoReqToOil()");
  OamsCfgOil1UCardInfoReq oamsCfgOil1UCardInfoReq;
	LOG_PRINT(LOG_INFO,"Going to send OAMS_CFG_OIL_1U_CARD_INFO_REQ");
	cfgSendMessage(&oamsCfgOil1UCardInfoReq, sizeof(oamsCfgOil1UCardInfoReq), ENT_OAM_OIL, OAMS_CFG_OIL_1U_CARD_INFO_REQ, 0);
	LOG_PRINT(LOG_INFO,"1U : Exiting send1UCardInfoReqToOil()");
}
/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/	  
void oilMsgHandler() 
{ 
  /* CS4.0: SwM Changes Start */ 
  OamOilCfgSwDelResp *delRespRecievedMsgPtr = NULL;
  OamOilCfgSwOfferResp *offerRespRecievedMsgPtr = NULL;
  OamOilCfgAvailableReleasesResp *releaseRespRecievedMsgPtr = NULL;
  OamOilCfgSwActResp *actRespRecievedMsgPtr = NULL;
  SwMNodeTableIndices indices;
  OamOilCfgEicEnableDisableLoad *eicLoad;
  OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
  IccCardInfoTableIndices iccCardInfoTableIndices;
  I_S32 res;
  I_U8 frameId,slotId;
  EicCardInfoTableIndices eicCardInfoTableIndices;
  I_U32 cardState;

  I_U8 chasisFrameId;
  I_U8 actslotId;


  /* CS4.0: SwM Changes End */ 

  switch (((SysHdr*) gCfgMsgBuf)->msgType) 
  {
    /*BSC CS4.0 MLPPP Changes starts*/
    case OAM_OIL_CFG_MLPPP_CONFIG_RESP:
      mlpppConfigRespHandler();
      break;
      /*BSC CS4.0 MLPPP Changes Ends*/
      /*BB Start Bss Reset, 12-06-09::13:13 */
    case OAM_OIL_CFG_BSS_RESET_RESP:
      if ( ( (OamOilCfgBssResetResp *)((I_U8 *)gCfgMsgBuf))->result == OPERATION_SUCCESS) {
        LOG_PRINT(LOG_INFO,
            "Received OAM_OIL_CFG_BSS_RESET_RESP result:[%s] frame:[%u] slot:[%u] ",
            "OPERATION_SUCCESS",
            ( (OamOilCfgBssResetResp *)((I_U8 *)gCfgMsgBuf))->frameId,
            ( (OamOilCfgBssResetResp *)((I_U8 *)gCfgMsgBuf))->slotId
            );
        cfgSendAckToCm();         
      }
      else {
        LOG_PRINT(LOG_INFO,
            "Received OAM_OIL_CFG_BSS_RESET_RESP result:[%s] frame:[%u] slot:[%u] ",
            "OPERATION_FAIL",
            ( (OamOilCfgBssResetResp *)((I_U8 *)gCfgMsgBuf))->frameId,
            ( (OamOilCfgBssResetResp *)((I_U8 *)gCfgMsgBuf))->slotId
            );
        cfgSendNackToCm(CM_ERR_BPM_OPERATION_FAILS);         
      }
      break;
      /*BB End Bss Reset, 12-06-09::13:13 */

    case OAM_OIL_CFG_BSS_SHUTDOWN_RESP:
      if ( ( (OamOilCfgBssShutdownResp *)((I_U8 *)gCfgMsgBuf))->result == OPERATION_SUCCESS) {
        LOG_PRINT(LOG_INFO,
            "Received OAM_OIL_CFG_BSS_SHUTDOWN_RESP result:[%s] frame:[%u] slot:[%u] ",
            "OPERATION_SUCCESS",
            ( (OamOilCfgBssShutdownResp *)((I_U8 *)gCfgMsgBuf))->frameId,
            ( (OamOilCfgBssShutdownResp *)((I_U8 *)gCfgMsgBuf))->slotId
            );
        iccCardInfoTableIndices.chasisFrameId =  ((OamOilCfgBssShutdownResp *)((I_U8 *)gCfgMsgBuf))->frameId;
        iccCardInfoTableIndices.slotId        =   ( (OamOilCfgBssShutdownResp *)((I_U8 *)gCfgMsgBuf))->slotId;
        updateIccCardState(&iccCardInfoTableIndices,CARDSTATE_SHUTDOWN);
        cfgSendAckToCm();         
      }
      else {
        LOG_PRINT(LOG_INFO,
            "Received OAM_OIL_CFG_BSS_SHUTDOWN_RESP result:[%s] frame:[%u] slot:[%u] ",
            "OPERATION_FAIL",
            ( (OamOilCfgBssShutdownResp *)((I_U8 *)gCfgMsgBuf))->frameId,
            ( (OamOilCfgBssShutdownResp *)((I_U8 *)gCfgMsgBuf))->slotId
            );
        cfgSendNackToCm(CM_ERR_BPM_OPERATION_FAILS);         
      }
      break;      
      /*BSC CS4.0  HA changes start*/
    case OAM_OIL_CFG_NEIP_ADDRESS_RESP:
      //Handle the NEIP Address
      if((((OamOilCfgSetNeipAddrResp *)((I_U8 *)gCfgMsgBuf))->result) == OPERATION_FAIL ){
        LOG_PRINT(LOG_INFO,"Received Set NeIpAddress Response with the result OPERATION_FAIL");
      }
      else
      {
        LOG_PRINT(LOG_INFO,"Received Set NeIpAddress Response with the result OPERATION_SUCCESS");
      }
      gSetNeIpRcvd = I_TRUE;	

      /* Mantis  12264 START*/
      if((((OamOilCfgSetNeipAddrResp *)((I_U8 *)gCfgMsgBuf))->result) == OPERATION_SUCCESS)
      {
        if(getActiveIccSlotId(&chasisFrameId, &actslotId) != CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_INFO,"sendSetOmcIpUsingMlpppConfig: Card is not in Active state");
          if(sendSetOmcIpUsingMlpppConfig() == CFG_FAILURE)
            gSetOmcIpReqSent = I_FALSE;
        }
        else
        {
          if(gSetOmcIpReqSent == I_FALSE)
          {
            sendSetOmcipAddressReqToCmInActive();
            gSetOmcIpReqSent = I_TRUE;
          }
        }	
      }
      /*12264 END*/

      break;
    case OAM_OIL_CFG_BPM_DB_INIT_RESP:
      LOG_PRINT(DEBUG,"OAM_OIL_CFG_DB_INIT_RESP received");
      copySystemDetails();
      gMyFrameId = ((sSystemCardInfo *)gSystemDetails)->selfInfo.frameID;
      gMySlotId = ((sSystemCardInfo *)gSystemDetails)->selfInfo.slotID;
      if(gCfgStandbyToActive == I_TRUE)
      {
        fillGlobalDataAfterSwitchover();

      }
      RELEASE_MUTEX;
      if(gCfgState == CFG_BPM_INIT)
      {
        /*Changes for TsGroup Start */
        sndSwtConnForAllTsGroupMaps();
        /*Changes for TsGroup End */
        if (gCfgStandbyToActive == I_FALSE)
        {
          sendNeipReq();
        }
        //         if(gNextCardState == CARDSTATE_ACTIVE_IN_PROGRESS && gCurrentCardState == CARDSTATE_IN_SERVICE)
        //       {

        //           gMySlotId = ((sSystemCardInfo *)gSystemDetails)->mateInfo.slotID;
        //           gPeerSlotId = ((sSystemCardInfo *)gSystemDetails)->selfInfo.slotID;
        if(gCfgStandbyToActive == I_FALSE)  
        { 
          LOG_PRINT(LOG_DEBUG,"Sending Switch Connect to GRHM for slot Id [%d]",
              ((sSystemCardInfo *)gSystemDetails)->selfInfo.slotID);
          sendSwitchConForSelf(((sSystemCardInfo *)gSystemDetails)->selfInfo.slotID);
        }   
        //              LOG_PRINT(LOG_DEBUG,"Sending Switch Connect to RM for slot Id [%d]", ((sSystemCardInfo *)gSystemDetails)->mateInfo.slotID);
        //              sendSwitchConForMate(((sSystemCardInfo *)gSystemDetails)->mateInfo.slotID);
        //       }
      }
			/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
      //Mantis #0031749
      if(gCardPlatformType == 1)  
		  {
			   LOG_PRINT(LOG_INFO,"1U: Sending send1UCardInfoReqToOil() as gCardPlatformType [%d] IMX",gCardPlatformType);	
         send1UCardInfoReqToOil();	
      }
      else
      {
			  LOG_PRINT(LOG_INFO,"1U: send1UCardInfoReqToOil() NOT SENT as gCardPlatformType [%d] HOST",gCardPlatformType);	
      }
      //Mantis #0031749
			/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/	  
      break;
      /*BSC CS4.0  HA changes ends*/

      /*BSC CS4.0 : Alarm Handling changes start*/
    case OAM_OIL_CFG_PRESENT_CARD_INFO_RESP:
      LOG_PRINT(DEBUG,"OAM_OIL_CFG_PRESENT_CARD_INFO_RESP received");
      updatePresentCardDetails();
      break;
      /*BSC CS4.0 : Alarm Handling changes End*/
      /*BSC CS4.0 : Init changes start*/
#if 0      
    case OAM_OIL_CFG_SYSTEM_TYPE_DETAILS:
      updateSystemTypeDetails();
      break;  
    case OAM_OIL_CFG_CHASIS_FRAME_DETAILS:
      updateChasisFrameDetails();
      break;  
    case OAM_OIL_CFG_SYSTEM_CLOCK_DETAILS:
      updateSystemClockDetails();
      break;  
    case OAM_OIL_CFG_DSP_OBJ_DETAILS:
#if BPM_PRESENT == 1
      RELEASE_MUTEX;
#else
      //Only for Host Testing
      if(gCfgState == CFG_BPM_INIT)
      {
        LOG_PRINT(LOG_DEBUG,"bpmAisCallbackFun: CFG is in CFG_BPM_INIT state");
        //Send TrunkPort State Change Request
        if(sendTrunkStateChangeReq() == CFG_FAILURE)
        {
          LOG_PRINT(LOG_DEBUG,"bpmAisCallbackFun: No Trunk is in Enable state. Sending ClkSrcConfig");
          if(sendClockSourceConfigReq() == CFG_FAILURE)
          {
            LOG_PRINT(LOG_DEBUG,"bpmAisCallbackFun: No ClockSource Avaibale . Initialization Process continues");
            cfgInit();
            startInitializeMGS();
            gCfgState = CFG_INIT_TSI;
            addConfiguredBics();
            addConfiguredTrxs();
            cfgInitSwMNodeTable();
            getListValue();
          }
        }
      }

#endif
      break;  
    case OAM_OIL_CFG_TRUNK_PORT_DETAILS:
      updateTrunkPortDetails();
      break;  
    case OAM_OIL_CFG_EIC_CARD_DETAILS:
      updateEicCardDetails();
      break;  
    case OAM_OIL_CFG_ICC_CARD_DETAILS:
      updateIccCardDetails();
      break;  
#endif
    case OAM_OIL_CFG_TRUNK_STATE_CHANGE_RESP:
      LOG_PRINT(DEBUG,"OAM_OIL_CFG_TRUNK_STATE_CHANGE_RESP rcvd in Cfg State %d",gCfgState);
      if(gCfgState == CFG_BPM_INIT)
      {
        if(checkTrunkStateChangeResp() == CFG_SUCCESS) 
        {
          if(sendClockSourceConfigReq() == CFG_FAILURE)
          {
            LOG_PRINT(LOG_DEBUG,"oilMsgHandler: No ClockSource Avaibale . Initialization Process continues");
            // cfgInit();
            cfgInitAfterDbRw();
            if(gCfgStandbyToActive == I_FALSE)
            { 
              addConfiguredBics();
              addConfiguredTrxs();
            } 
            cfgInitSwMNodeTable();
            /*Bsc R2.0 Changes Starts*/
            if((ZERO == gSentAddBicReqAtInitNum) && 
                (FALSE == gMgsOprSts)  )
            {
              /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
              sndSwitchConForBicsAtInit(); 
              if(gCfgStandbyToActive == I_TRUE)
              { 
                sndSwitchConForTrxsAtSwitchOver();
              }
              sendRequestForAvailableReleases(); 
              gCfgState = CFG_BPM_SW_QUERY;
              LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
            }   
            else
            { 
              LOG_PRINT(DEBUG,"Val Of gSentAddBicReqAtInitNum = %d,gMgsOprSts = %d ",
                  gSentAddBicReqAtInitNum, gMgsOprSts);
            } 

            /*Bsc R2.0 Changes Ends*/
#if 0  //R2.0 Changes
            gCfgState = CFG_START_TRAU;
            sendTrauStartMsg();
#endif
          }
        }
        else
        {
          //cfgInit();
          cfgInitAfterDbRw();
          if(gCfgStandbyToActive == I_FALSE)
          { 
            addConfiguredBics();
            addConfiguredTrxs();
          } 
          cfgInitSwMNodeTable();
          /*Bsc R2.0 Changes Starts*/
          if((ZERO == gSentAddBicReqAtInitNum) && 
              (FALSE == gMgsOprSts)  )
          {
            sndSwitchConForBicsAtInit(); 
            if(gCfgStandbyToActive == I_TRUE)
            { 
              sndSwitchConForTrxsAtSwitchOver();
            }
            sendRequestForAvailableReleases(); 
            gCfgState = CFG_BPM_SW_QUERY;
            LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
          }   
          /*Bsc R2.0 Changes Ends*/
#if 0  //R2.0 Changes
          gCfgState = CFG_START_TRAU;
          sendTrauStartMsg();
#endif
        }
      }
      /*BSC R2.0 Changes Starts*/
      else if(  (gCfgState == CFG_READY) && 
          (gCfgAlarmIdRcvd ==INFO_BPM_EIC_ENABLED) )
      {
        if(checkTrunkStateChangeResp() == CFG_SUCCESS) 
        {

          //if((gEnabledEicSlotId != 0) && (isClkConfiguredOnSlotId(gEnabledEicSlotId) == TRUE) ) 
          //{
          if(sendClockSourceConfigReq() == CFG_FAILURE)
            gCfgAlarmIdRcvd = 0; 
          //} 
          //else
          //{
          //   gCfgAlarmIdRcvd = 0; 
          //} 
        }   
        else 
        {
          gCfgAlarmIdRcvd = 0;
        }  
        //cfgInitSwMNodeTable(); ---- veena
        gCfgStandbyToActive = I_FALSE;
      }
      /*BSC R2.0 Changes Ends*/
      else
      {
        TrunkPortObjectHandler();
      }
      break; 
    case OAM_OIL_CFG_TRUNK_PORT_STATUS_RESP:
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_TRUNK_PORT_STATUS_RESP from Oil..");
      trunkPortStatusRespHandler();
      gTrunkPortStsReqSent--;
      if(gCfgState == CFG_BPM_INIT)
      {
        if(gTrunkPortStsReqSent == 0)
        {
          if(sendTrunkStateChangeReq() == CFG_FAILURE)
          {
            LOG_PRINT(LOG_DEBUG,"Sts Resp: No Trunk is in Enable state.Sending ClkSrcConfig");
            if(sendClockSourceConfigReq() == CFG_FAILURE)
            {
              LOG_PRINT(LOG_DEBUG,"Sts Resp: No ClockSource Avaibale.");
              cfgInitAfterDbRw();
              if(gCfgStandbyToActive == I_FALSE)
              { 
                addConfiguredBics();
                addConfiguredTrxs();
              } 
              cfgInitSwMNodeTable();
              /*Bsc R2.0 Changes Starts*/
              if((ZERO == gSentAddBicReqAtInitNum) && 
                  (FALSE == gMgsOprSts)  )
              {
                sndSwitchConForBicsAtInit(); 
                if(gCfgStandbyToActive == I_TRUE)
                { 
                  sndSwitchConForTrxsAtSwitchOver();
                }
                sendRequestForAvailableReleases(); 
                gCfgState = CFG_BPM_SW_QUERY;
                LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
              }   
              /*Bsc R2.0 Changes Ends*/
#if 0//R2.0 changes	
              gCfgState = CFG_START_TRAU;
              sendTrauStartMsg();
#endif
            }
          }
        }
      } 
      else if( (gCfgState == CFG_READY)  && 
          (gCfgAlarmIdRcvd == INFO_BPM_EIC_ENABLED)  )
      {
        if(sendTrunkStateChangeReq() == CFG_FAILURE)
        {
          LOG_PRINT(LOG_DEBUG,"initializingCfg: No Trunk is in Enable state. Sending ClkSrcConfig for slotid:%d",
              gEnabledEicSlotId);
          //if((gEnabledEicSlotId != 0) && (isClkConfiguredOnSlotId(gEnabledEicSlotId) == TRUE) ) 
          //{
          if(sendClockSourceConfigReq() == CFG_FAILURE)
            gCfgAlarmIdRcvd = 0; 
          //} 
          //else
          //{
          //   gCfgAlarmIdRcvd = 0; 
          //} 
          gEnabledEicSlotId = 0;
        }
      }
      if(gCfgStandbyToActive == I_TRUE)
      {
        if(gTrunkPortStsReqSent == 0)
        {
          if(sendTrunkStateChangeReq() == CFG_FAILURE)
          {
            sendClockSourceConfigReq();
            gCfgStandbyToActive = I_FALSE;
            LOG_PRINT(LOG_INFO,"initializingCfg: gCfgStandbyToActive = %d",I_FALSE);
          }
        }
      }
      break;  

      /*BSC CS4.0 : Init changes end*/
    case CM_API_APP_RESPONSE:       
      break;  
#if 0 /* CS4.0 HA Stack Changes */  
    case BSC_API_SET_LINKADMINSTATETABLE:
#endif
    case OAMS_SCM_CFG_ALARM_IND: 
      scmMsgHandler(); 
      break; 

    case OAMS_BPM_CFG_ALARM_IND: 
    case OAM_OIL_CFG_ALARM_IND: 
      cfgAlarmHandler(); 
      break; 
#if 0 /* CS4.0 HA Stack Changes */  
    case BSC_API_SET_MTP3LINKSETTABLE: 
      setMtp3LinksetTableHandlerScmAck(); 
      break; 
    case BSC_API_DEL_BSSAPPCSSNCONFIGTABLE:
      delBssapPcSsnConfigTableHandlerScmAck();
      break;
    case BSC_API_SET_MTP3ROUTETABLE: 
      setMtp3RouteTableHandlerScmAck(); 
      break; 
    case BSC_API_SET_MTP3LINKTABLE: 
      setMtp3LinkTableHandlerScmAck(); 
      break; 
      /*case BSC_API_SET_MTP3REMOTEPOINTCODETABLE: 
        setMtp3RemotePointCodeTableHandlerScmAck(); 
        break; */ 
    case BSC_API_SET_SCCPSSNCONFIGTABLE: 
      setSccpSsnConfigTableHandlerScmAck(); 
      break; 
    case BSC_API_SET_SCCPCSSNCONFIGTABLE: 
      setSccpCssnConfigTableHandlerScmAck(); 
      break; 
    case BSC_API_SET_SKSCOMMONTABLE: 
      setSksCommonTableHandlerScmAck(); 
      break; 
    case BSC_API_SET_SKSLINKSTARTTABLE: 
      setSksLinkstartTableHandlerScmAck(); 
      break; 
    case BSC_API_SET_MTP3LINKSETSTSTABLE:
      setMtp3LinkSetStsTableHandlerScmAck();
      break;
    case BSC_API_SET_BSSAPPCSSNCONFIGTABLE:
      setBssapPcSsnConfigTableHandlerScmAck();
      break;
    case BSC_API_DEL_MTP3LINKSETTABLE: 
      delMtp3LinksetTableHandlerScmAck(); 
      break; 
    case BSC_API_DEL_MTP3ROUTETABLE: 
      delMtp3RouteTableHandlerScmAck(); 
      break;  
    case BSC_API_DEL_MTP3LINKTABLE: 
      delMtp3LinkTableHandlerScmAck(); 
      break; 
      /*case BSC_API_DEL_MTP3REMOTEPOINTCODETABLE: 
        delMtp3RemotePointCodeTableHandlerScmAck(); 
        break; */
    case BSC_API_DEL_SCCPSSNCONFIGTABLE: 
      delSccpSsnConfigTableHandlerScmAck(); 
      break; 
    case BSC_API_DEL_SCCPCSSNCONFIGTABLE: 
      delSccpCSSNConfigTableHandlerScmAck(); 
      break;
    case BSC_API_DEL_SKSCOMMONTABLE: 
      delSksCommonTableHandlerScmAck(); 
      break; 
    case BSC_API_DEL_SKSLINKSTARTTABLE: 
      delSksLinkstartTableHandlerScmAck(); 
      break; 
    case BSC_API_DEL_MTP3LINKSETSTSTABLE:
      delMtp3LinksetStsTableHandlerScmAck(); 
      break; 
    case BSC_API_SET_SKSGENCONFIGTABLE: 
      setSksGenCfgTableHandlerScmAck(); 
      break;
    case BSC_API_DEL_SKSGENCONFIGTABLE: 
      delSksGenCfgTableHandlerScmAck(); 
      break;
#endif
      /*CS3.0 changes : Start */ 
      /*CS4.0: SwM changes Start */ 
    case OAM_OIL_CFG_SW_OFFER_RESP:
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_SW_OFFER_RESP from Oil..");
      swOfferAckNackHandler();
      break;
    case OAM_OIL_CFG_SW_ACT_RESP:
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_SW_ACT_RESP from Oil..");
      break;
    case OAM_OIL_CFG_SW_DEL_RESP:
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_SW_DEL_RESP from Oil..");
      break;
    case OAM_OIL_CFG_AVAILABLE_RELEASES_RESP:
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_AVAILABLE_RELEASES_RESP from Oil..");
      break;
      /* CS3.0 changes : End */ 
      /*  New Alarms added for Software upgrade CS4.0  */
    case OAM_OIL_CFG_INFO_AVAILABLE_VERSION:
      releaseRespRecievedMsgPtr = (OamOilCfgAvailableReleasesResp*)(&(((OamOilCfgInfoAvailableVersion*)gCfgMsgBuf)->swMAvailResp));
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_INFO_AVAILABLE_VERSION from Oil for NodeType: %d",releaseRespRecievedMsgPtr->nodeType);
      if (releaseRespRecievedMsgPtr->nodeType == SYS_NODE_TYPE_EIC)
      {				 
        LOG_PRINT(INFO,"OAM_OIL_CFG_INFO_AVAILABLE_VERSION: Received For EIC");
        eicAvailableReleasesRespHandler();
      }
      else if (releaseRespRecievedMsgPtr->nodeType == SYS_NODE_TYPE_DSP)
      {
        LOG_PRINT(INFO,"OAM_OIL_CFG_INFO_AVAILABLE_VERSION: Received For DSP");
        dspAvailableReleasesRespHandler();
      }
      else
      {
        LOG_PRINT(INFO,"OAM_OIL_CFG_INFO_AVAILABLE_VERSION: Received For OTHER");		 
        availableReleasesRespHandler();
      }
      break;
    case OAM_OIL_CFG_INFO_SW_UPGRADE_OFFER: 
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_INFO_SW_UPGRADE_OFFER from Oil.."); 
      sendUpgradeAlarm(); 
      break;
    case OAM_OIL_CFG_INFO_SW_DWNLD_RESULT:
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_INFO_SW_DWNLD_RESULT from Oil..");
      offerRespRecievedMsgPtr = (OamOilCfgSwOfferResp*)(&(((OamOilCfgInfoSwDwnldResult*)gCfgMsgBuf)->swMOfferResp));
      if (offerRespRecievedMsgPtr->nodeType == SYS_NODE_TYPE_EIC)
        eicSwOfferRespHandler();
      if (offerRespRecievedMsgPtr->nodeType == SYS_NODE_TYPE_DSP)
        dspSwOfferRespHandler();
      else
        swOfferRespHandler();
      break;
    case OAM_OIL_CFG_INFO_SW_ACT_STARTED: 
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_INFO_SW_ACT_STARTED from Oil.."); 
      sendUpgradeAlarm(); 
      break;
    case OAM_OIL_CFG_INFO_SW_ACT_RESULT:
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_INFO_SW_ACT_RESULT from Oil..");
      gSwActReqSent = I_FALSE;
      actRespRecievedMsgPtr = (OamOilCfgSwActResp*)(&(((OamOilCfgInfoSwActResult*)gCfgMsgBuf)->swMActResp));
      if (actRespRecievedMsgPtr->nodeType == SYS_NODE_TYPE_EIC)
        eicSwActivationRespHandler();
      else if (actRespRecievedMsgPtr->nodeType == SYS_NODE_TYPE_DSP)
      {
        LOG_PRINT(DEBUG,"SW_ACT_RESULT for DSP");
        dspSwActivationRespHandler();
      }
      else
        swActivationRespHandler();
      break;
    case OAM_OIL_CFG_INFO_DEL_VERSION_RESULT:
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_INFO_DEL_VERSION_RESULT from Oil..");
      delRespRecievedMsgPtr = (OamOilCfgSwDelResp*)(&(((OamOilCfgInfoDelResult*)gCfgMsgBuf)->swMDelResp));
      if (delRespRecievedMsgPtr->nodeType == SYS_NODE_TYPE_EIC)
        eicSwDeletionRespHandler();
      if (delRespRecievedMsgPtr->nodeType == SYS_NODE_TYPE_DSP)
        dspSwDeletionRespHandler();
      else
        swDeletionRespHandler();
      break;
    case OAM_OIL_CFG_SET_OPER_CON_STATE_RESULT:
      LOG_PRINT(LOG_INFO,"Recieved OAMS_OIL_CFG_SET_OPER_CON_STATE_RESULT from Oil..");
      OamOilCfgSetCardOperStateResult *oamOilCfgSetOperConStateRespPtr = NULL;
      oamOilCfgSetOperConStateRespPtr = (OamOilCfgSetCardOperStateResult *)((I_U8 *)gCfgMsgBuf);
      cardSetOperConStateRespHandler(oamOilCfgSetOperConStateRespPtr->slotId,
          oamOilCfgSetOperConStateRespPtr->cardState,oamOilCfgSetOperConStateRespPtr->result);
      break;
    case OAM_OIL_CFG_INFO_EIC_CONNECT:
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_INFO_EIC_CONNECT from Oil..");
      updateEicDataOnEicConnect();
      break;
    case OAM_OIL_CFG_INFO_EIC_ENABLE_DISABLE:
      eicLoad = (OamOilCfgEicEnableDisableLoad*)gCfgMsgBuf;
      frameId =  eicLoad->chasisFrameId;
      slotId =  eicLoad->iccSlotId;
      eicCardInfoTableIndices.chasisFrameId = eicLoad->chasisFrameId;  
      eicCardInfoTableIndices.slotId = eicLoad->slotId;

      res = ChkActiveCardAlarm(frameId,slotId);
      if(res == TRUE)
      {
        gCfgAlarmIdRcvd =  eicLoad->alarmId;
        gEnabledEicSlotId = eicLoad->slotId;
        if ( (eicLoad->alarmId) == INFO_BPM_EIC_ENABLED )
        {
          LOG_PRINT(LOG_INFO,"Recieved INFO_BPM_EIC_ENABLED chasisFrameId [%d] SlotId [%d]",eicLoad->chasisFrameId, eicLoad->slotId);
          updateEicDataOnEicEnableDisable();
          cardState = BPM_EIC_ENABLE; 
        }
        else if ( eicLoad->alarmId == INFO_BPM_EIC_DISABLED )
        {
          LOG_PRINT(LOG_INFO,"Recieved INFO_BPM_EIC_DISABLED chasisFrameId [%d] SlotId [%d]",eicLoad->chasisFrameId, eicLoad->slotId);
          indices.chasisFrameId = eicLoad->chasisFrameId;
          indices.slotId = eicLoad->slotId;
          indices.nodeType = SYS_NODE_TYPE_EIC;
          indices.nodeIdentity = eicLoad->slotId;
          if ( deleteSwMNodeTable( &indices ) != CLIB_SUCCESS )
          {
            LOG_PRINT(LOG_CRITICAL,"deleteSwMNodeTable Failed..");  
          }
          sendUpgradeAlarm();
          cardState = BPM_EIC_DISABLE; 
        }
        LOG_PRINT(DEBUG,"Going To update Eic State as :%d frameId:%d slotId:%d",
            cardState,eicCardInfoTableIndices.chasisFrameId,eicCardInfoTableIndices.slotId );
        if(updateEicCardState(&eicCardInfoTableIndices, cardState) == CLIB_SUCCESS)
        {
          LOG_PRINT(DEBUG,"updateEicCardState success on EIC_ENABLE"); 
        } 
      }
      else 
      {
        LOG_PRINT(DEBUG,"EIC_ENABLE/DISABLE alarm is not for active card thus discarding it");
      }
      break;

      /*CS4.0: SwM changes : End */ 

      /*BB, Start , CS4.0 Clock Source Configuration */   
    case OAM_OIL_CFG_SET_CLK_SRC_RESP :
      LOG_PRINT(LOG_INFO,"Recieved OAM_OIL_CFG_SET_CLK_SRC_RESP from Oil..");
      if(gCfgState == CFG_BPM_INIT)
      {
        if(checkClockSourceResp() == CFG_FAILURE)  
        {
          LOG_PRINT(LOG_CRITICAL,"oilMsgHandler: Deleting ClkSrcConfig from DB");
        }
        cfgInitAfterDbRw();
        if(gCfgStandbyToActive == I_FALSE)
        { 
          addConfiguredBics();
          addConfiguredTrxs();
        } 
        cfgInitSwMNodeTable();
        /*Bsc R2.0 Changes Starts*/
        if((ZERO == gSentAddBicReqAtInitNum) && 
            (FALSE == gMgsOprSts)  )
        {
          sndSwitchConForBicsAtInit(); 
          if(gCfgStandbyToActive == I_TRUE)
          { 
            sndSwitchConForTrxsAtSwitchOver();
          }
          sendRequestForAvailableReleases(); 
          gCfgState = CFG_BPM_SW_QUERY;
          LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
        }   
        /*Bsc R2.0 Changes Ends*/
#if 0   //R2.0 Changes
        gCfgState = CFG_START_TRAU;
        sendTrauStartMsg();
#endif
      }
      /*BSC R2.0 Changes Starts*/
      else if(  (gCfgState == CFG_READY) && 
          (gCfgAlarmIdRcvd ==INFO_BPM_EIC_ENABLED) )
      {
        LOG_PRINT(DEBUG,"EIC is inserted thus clk Configuration req was given");
        if(checkClockSourceResp() == CFG_FAILURE)  
        {
          LOG_PRINT(LOG_CRITICAL,"oilMsgHandler: Deleting ClkSrcConfig from DB");
        }
        gEnabledEicSlotId = 0;   
        gCfgAlarmIdRcvd = 0;
      }
      /*BSC R2.0 Changes Ends*/
      else
      {
        setOilClkSrcRespHldr();
      }
      break;
      /*BB, End , CS4.0 Clock Source Configuration */
      /* CS4.0 HA Stack Changes : Start */  
    case OAM_OIL_CFG_SCM_MSG_RESP: 
      {
        I_U32 outRows=0;
        I_U16 outSize=0;
        //LinkTableApi *linkPtr=NULL;
        SigtranM3uaLAspConfigTableApi* sigtranM3uaLAspConfigTableApi = NULL; //IP_BSC_STACK

        LOG_PRINT(LOG_INFO,"IP_BSC_STACK: OAM_OIL_CFG_SCM_MSG_RESP has been received..");
        ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);
        if ((convertMsgOpCodeFromResp2Req() == OAM_SCM_LINK_ADMIN_CONFIG)||(convertMsgOpCodeFromResp2Req() == OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG))
        {
          LOG_PRINT(LOG_INFO,"IP_BSC_STACK: OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG has been received..");
          ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);
          if (isStackRespOK(ScmOamRespPtr->erro_code))  
          {
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received Success from SCM");
            setFailCauseInStackObj(CM_SUCCESS);
          }
          else
          {
            LOG_PRINT(LOG_MAJOR,"IP_BSC_STACK: Received Error from SCM(error: %d)",ScmOamRespPtr->erro_code);
            //Mantis #9191 #8595 #8873 start
            if(ScmOamRespPtr->erro_code == ERROR_PREVIOUS_CMD_IN_PROGRESS)
            {
              OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = EVENT_STACK_PREVIOUS_CMD_IN_PROGRES;
              OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
              OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_BSSNODE;
              OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen =
                sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Previous command is in progress on stack");
              cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
            }
            //End
						/*Change done for mantis #32181 Gaurav Sinha 20 Oct 2016*/
            if((ScmOamRespPtr->scmhdr.operation == SCM_UNLOCK || ScmOamRespPtr->scmhdr.operation == SCM_LOCK))
            {
              LOG_PRINT(LOG_MAJOR,"IP_BSC_STACK: ERROR in case of SCM LOCK/UNLOCK operation:: Resetting Global variables");
							SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApiInt = (SigtranM3uaLAspConfigTableApi *)gStoredMsgBufPtr;
							setStatusAspLocal(sigtranM3uaLAspConfigTableApiInt->localAspId,(I_U16)ZERO,STK_FAILURE);
            }
						/*Change done for mantis #32181 Gaurav Sinha 20 Oct 2016*/
          }

          if ( gBssState == unlockInProgress ) 
          {

            LOG_PRINT(LOG_INFO,"Bss is Unlock-In-Progres State");
            //if (getallLinkTable(&linkPtr,&outRows,&outSize) == CLIB_SUCCESS)
            if(CLIB_SUCCESS == getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outRows,&outSize))
            {
              if (gLinkMsgSentForBss != outRows)
              {
                if ((gIsAllLinkUnlockReqd = checkAndSendLinkActivationRequest()) != TRUE)
                {
                  //LOG_PRINT(LOG_INFO,"Link Activation cannot be send");
                  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ASP Activation cannot be send");
                  gIsAllLinkUnlockReqd = FALSE; /* Set Flag for Link Unlock required to FALSE */
                }
              }
              else
              {
                gIsAllLinkUnlockReqd = FALSE; /* Set Flag for Link Unlock required to FALSE */
              }

              if (gIsAllLinkUnlockReqd == FALSE)	
              {
                /*Changes for Mantis Id 9617 Starts*/                 
                if (gDbBssTableApiStorage.gprsEnabled)
                {
                  /*Changes for Sending PsscmUnlockReq only if AdminState in Unlocked in gbInterfaceTable 05-Aug-2016 Mantis #31633 #31634 #31639*/
                  GbInterfaceTableApi *gbInterfaceTableApi = NULL,*tmpGbInterfaceTableApi = NULL;
                  I_U32 outRows = ZERO,i=ZERO;
                  I_U16 outSize = ZERO;
                  if(CLIB_SUCCESS == getallGbInterfaceTable(&gbInterfaceTableApi, &outRows, &outSize))
									{
										for(i = 0; i < outRows; ++i)
										 {
											 tmpGbInterfaceTableApi = (GbInterfaceTableApi *)((I_U8 *)gbInterfaceTableApi + i * outSize);

											 if(tmpGbInterfaceTableApi->adminState == UNLOCKED)
												{
													LOG_PRINT(DEBUG,"GB_LOCK_UNLOCK: GbInterfaceTableApi adminState is Unlocked will send PsscmUnlockReq");
                          sendPsscmUnlockReq(OAMS_RSN_OPERATORINITIATED);	    
												}
                        else
						            {
													LOG_PRINT(DEBUG,"GB_LOCK_UNLOCK: GbInterfaceTableApi adminState is Locked will not send PsscmUnlockReq : WILL proceed for CELL CONF");
                          initiateCellUnlockEnableforUnlcokedDisabledCells();
                        }
										}
										free(gbInterfaceTableApi);
									}
                  else
                  {
										LOG_PRINT(DEBUG,"GB_LOCK_UNLOCK: DB CALL failed for GbInterfaceTableApi  will not send PsscmUnlockReq");
                    initiateCellUnlockEnableforUnlcokedDisabledCells();
                  }
                  /*Changes for Sending PsscmUnlockReq only if AdminState in Unlocked in gbInterfaceTable 05-Aug-2016 Mantis #31633 #31634 #31639*/
                  /* UNLOCK GB interface towards GB interface */
                  //sendPsscmUnlockReq(OAMS_RSN_OPERATORINITIATED);	    Commented for above Change  05-Aug-2016
#if 0
                  LOG_PRINT(LOG_INFO,"UNLOCK GB interface towards GB interface");
                  /* UNLOCK GB interface towards GB interface */
                  OamsCfgPsscmUnlockReqBuff.lengthOfList=0;
                  OamsCfgPsscmUnlockReqBuff.objectIdList[0]= 0;
                  OamsCfgPsscmUnlockReqBuff.ObjType = OAMS_OBJTYPE_GBINTERFACE;
                  cfgSendMessage((void *)&OamsCfgPsscmUnlockReqBuff, sizeof(OamsCfgPsscmUnlockReq), ENT_OAM_OIL, OAMS_CFG_PSSCM_UNLOCK_REQ, 0);
#endif
                  return;
                }
                else
                {
                  /* CFG will execute Unlock (Enabled) Cell procedure
                     for all the Unlocked and Disabled cells */
                  initiateCellUnlockEnableforUnlcokedDisabledCells();
                  return;   
                }
                /*Changes for Mantis Id 9617 Ends*/                 

                if(gSSAReceived == TRUE)
                {
                  bssObjectHandlerForSSAllowed(); 
                } 
              }   
              //free(linkPtr);
              free(sigtranM3uaLAspConfigTableApi);
            }
            /* Just consume it */
          }

          /* Changes for Mantis 8120 start */
          if (( gBssState == unlocked ) && (gIsAllLinkUnlockReqd == TRUE))
          {
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Bss is in Unlocked State & gIsAllLinkUnlockReqd is TRUE");
            //if (getallLinkTable(&linkPtr,&outRows,&outSize) == CLIB_SUCCESS)
            if(CLIB_SUCCESS == getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outRows,&outSize)) //IP_BSC_STACK:
            {
              if (gLinkMsgSentForBss != outRows)
              {
                /* Changes for Mantis 8589 start */
                if ((gIsAllLinkUnlockReqd = checkAndSendLinkActivationRequest()) != TRUE)
                {
                  //LOG_PRINT(LOG_INFO,"Link Activation cannot be send");
                  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ASP Activation cannot be send");  //IP_BSC_STACK
                  gIsAllLinkUnlockReqd = FALSE; /* Set Flag for Link Unlock required to FALSE */
                }
                /* Changes for Mantis 8589 end */
              }
              else 
              {
                gIsAllLinkUnlockReqd = FALSE; /* Set Flag for Link Unlock required to FALSE */
                LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:gIsAllLinkUnlockReqd is set to False");
              }
              //free(linkPtr);
              free(sigtranM3uaLAspConfigTableApi);
            }
            /* Just consume it */
          }
          /* Changes for Mantis 8120 end */

          /* Changes for Mantis 8161 start */
          else if ( gBssState == lockInProgress )
          {
            LOG_PRINT(LOG_INFO,"Bss is Lock-In-Progres State");
            //if (getallLinkTable(&linkPtr,&outRows,&outSize) == CLIB_SUCCESS)
            if(CLIB_SUCCESS == getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outRows,&outSize)) //IP_BSC_STACK:
            {
              if (gLinkLockMsgSentForBss != outRows)
              {
                if ((gIsAllLinkLockReqd = checkAndSendLinkDeactivationRequest()) != TRUE) 
                {
                  if(gCfgStandbyToActive != I_TRUE)
                  { 
                    LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Link Deactivation cannot be send");
                    bssObjectHandlerForSSProhibit();
                  }
                  else
                  {
                    gCfgStandbyToActive = I_FALSE;    
                    gBssState = locked;
                    gBssSubState = noneBssSubState;  
                  }  
                }
              }
              else
              {
                gIsAllLinkLockReqd = FALSE; /* Set Flag for Link Unlock required to FALSE */
                if(gCfgStandbyToActive != I_TRUE)
                { 
                  LOG_PRINT(LOG_DEBUG,"gIsAllLinkLockReqd is set to False");
                  bssObjectHandlerForSSProhibit();
                } 
                else
                {
                  gCfgStandbyToActive = I_FALSE;    
                  gBssState = locked;
                  gBssSubState = noneBssSubState;  
                }  
              }
              //free(linkPtr);
              free(sigtranM3uaLAspConfigTableApi);
            }
          }
          /* Changes for Mantis 8161 end */
          /* Changes for Mantis 8161 start */
#if 0
          else if ( gBssState == lockInProgress )
          {
            LOG_PRINT(LOG_INFO,"Bss is Lock-In-Progres State");  
            gLinkMsgSentForBss--;
            if (gLinkMsgSentForBss == 0)
            {
              bssObjectHandlerForSSProhibit();
            }
          }
#endif
          /* Changes for Mantis 8161 end */
          /*Changes Specific to IP_BSC_STACK 21 JULY 2016 Gaurav Sinha*/
          else if((ScmOamRespPtr->scmhdr.operation == SCM_UNLOCK || ScmOamRespPtr->scmhdr.operation == SCM_LOCK))
          {
   					LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: LOCK/UNLOCK OAM Condition matched going to enter aspLockUnlockHandler()");
            aspLockUnlockHandler();
          }
          /*Changes Specific to IP_BSC_STACK 21 JULY 2016 Gaurav Sinha*/
          else
          {
            if ( gMsgSentForE1Num != 0xff )
            {
              I_U32 state = getE1ObjectState(gMsgSentForE1Num);

              if ( state == unlockInProgress)  
              {
                if (checkAndSendLinkActivationRequestForE1(UNLOCKED) != TRUE) 
                {
                  LOG_PRINT(LOG_INFO,"Link Activation cannot be send");
                  cfgScmUnlockLinkAdmStTblResp();
                  if ( gE1Data[gMsgSentForE1Num].msgsSentForE1 == 0)
                    gMsgSentForE1Num = 0xff;
                }
                else 
                {
                  cfgScmUnlockLinkAdmStTblResp();
                }
              }
              else if  ( state == lockInProgress)
              {
                if (checkAndSendLinkActivationRequestForE1(LOCKED) != TRUE) 
                {
                  LOG_PRINT(LOG_INFO,"Link Activation cannot be send");
                  cfgScmLockLinkAdmStTblResp();
                  if ( gE1Data[gMsgSentForE1Num].msgsSentForE1 == 0)
                    gMsgSentForE1Num = 0xff;
                }
                else 
                {
                  cfgScmLockLinkAdmStTblResp();
                }
              }
              else
              {
                LOG_PRINT(LOG_MAJOR," No Match found for E1 object state");   
              } 
            }
            else if ( gMsgSentForE1TSNum != 0xff )
            {
              linkLockUnlockScmRespHandler();
            }
          }            
        }
        else if (convertMsgOpCodeFromResp2Req() == OAM_SCM_LAPDTIMER_CONFIG)
        {
          LOG_PRINT(LOG_INFO,"OAM_SCM_LAPDTIMER_CONFIG has been received..");
          ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);
          if (isStackRespOK(ScmOamRespPtr->erro_code))  
          {
            LOG_PRINT(LOG_INFO,"Received Success from SCM");
            setFailCauseInStackObj(CM_SUCCESS);
          }
          else
          {
            LOG_PRINT(LOG_MAJOR,"Received Error from SCM(error: %d)",ScmOamRespPtr->erro_code);
            //Mantis #9191 #8595 #8873 start
            if(ScmOamRespPtr->erro_code == ERROR_PREVIOUS_CMD_IN_PROGRESS)
            {
              OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = EVENT_STACK_PREVIOUS_CMD_IN_PROGRES;
              OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
              OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_BSSNODE;
              OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen =
                sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Previous command is in progress on stack");
              cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm),
                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
            }
            //End
          }

          if ( gBssState == unlockInProgress ) 
          {
            LOG_PRINT(LOG_INFO,"Bss is Unlock-In-Progres State");
            bssObjectSendLinkAdminStateTableToScm(UNLOCKED,UNLOCKED);
          }
          else if ( gBssState == unlocked ) 
          {
            LOG_PRINT(DEBUG,"OAM_SCM_LAPDTIMER_CONFIG received in unlocked state"); 
          } 
        } 
        else 
          ScmRespHandler();
      }
      break;
      /* CS4.0 HA Stack Changes : End */  

      /*BSC R2.0 Changes Starts*/
    case OAM_OIL_CFG_DSP_BOOT_INFO:
      LOG_PRINT(LOG_DEBUG,"OAM_OIL_CFG_DSP_BOOT_INFO Received");
      dspBootAlarmHandler();
      break;
    case OAM_OIL_CFG_RTP_DSP_BOOT_INFO:/*Changes for R2.8 */
      LOG_PRINT(LOG_DEBUG,"OAM_OIL_CFG_RTP_DSP_BOOT_INFO  Msg Received");
      dspBootAlarmHandler();
      break;
      /*BSC R2.0 Changes Ends*/

    case OAM_OIL_CFG_SET_SYSTEM_TIME_RESP :
      LOG_PRINT(LOG_DEBUG,"OAM_OIL_CFG_SET_SYSTEM_TIME_RESP Received");
      setSystmeTimeRespHandler();
      break;

    case OAMS_OIL_CFG_SWITCH_INFO_RESP :
      LOG_PRINT(LOG_DEBUG,"OAMS_OIL_CFG_SWITCH_INFO_RESP Received");
      peerSwitchInfoRespHandler();
      break;

    case OAM_OIL_CFG_PEER_TRUNK_STATE_CHANGE_RESP :
      LOG_PRINT(LOG_DEBUG,"OAM_OIL_CFG_PEER_TRUNK_STATE_CHANGE_RESP Received");
      break;

    case OAM_OIL_CFG_DIAGNOSTTC_RESP :
      LOG_PRINT(INFO,"OAM_OIL_CFG_DIAGNOSTTC_RESP received"); 
      bpmDiagnosticsRespHandler(); 
      //StopTimerFrmwrk(gCfgDiagBpmRespTimerId);
      //gCfgDiagTimerRunning = DIAG_NO_TIMER_RUNNING;
      //abortDiagnostics(TEST_ABORTED); 
      break; 

    case OAM_OIL_CFG_EXT_PORT_ASSIGN_RESP:
      LOG_PRINT(INFO,"OAM_OIL_CFG_EXT_PORT_ASSIGN_RESP received"); 
      OamOilCfgExtPortAssignmentResp *oilCfgExtPortAssignRespPtr;
      oilCfgExtPortAssignRespPtr=((OamOilCfgExtPortAssignmentResp*) gCfgMsgBuf);
      if((oilCfgExtPortAssignRespPtr->extPortAssignState==EXT_PORT_ASSIGN) && (oilCfgExtPortAssignRespPtr->extResp==EXT_PORT_ACK))
      {
        LOG_PRINT(INFO,"PortType(%d) PortId(%d) AssignState(%s) EXT_PORT_ASSIGN Response (%s) EXT_PORT_ACK ",oilCfgExtPortAssignRespPtr->extPortType,oilCfgExtPortAssignRespPtr->extPortId,"EXT_PORT_ASSIGN","EXT_PORT_ACK");
      }
      else
      {          
        LOG_PRINT(INFO,"PortType(%d) PortId(%d) AssignState(%s) EXT_PORT_FREE Response (%s) EXT_PORT_NACK ",oilCfgExtPortAssignRespPtr->extPortType,oilCfgExtPortAssignRespPtr->extPortId,"EXT_PORT_FREE","EXT_PORT_NACK");
      }
      break; 

    case OAM_OIL_CFG_EXT_PORT_STATE_CHANGE_RESP:
      LOG_PRINT(INFO,"OAM_OIL_CFG_EXT_PORT_STATE_CHANGE_RESP received"); 
      OamOilCfgExtPortStateChangeResp *oilCfgExtPortStateChangeRespPtr;
      oilCfgExtPortStateChangeRespPtr=((OamOilCfgExtPortAssignmentResp*) gCfgMsgBuf);
      if((oilCfgExtPortStateChangeRespPtr->extPortStateChange==EXT_OUTPUT_PORT_TURN_ON) && (oilCfgExtPortStateChangeRespPtr->extResp==EXT_PORT_ACK))
      {

        LOG_PRINT(INFO,"PortType(%d) PortId(%d) AssignState(%s) EXT_OUTPUT_PORT_TURN_ON  Response EXT_PORT_ACK (%s)", oilCfgExtPortStateChangeRespPtr->extPortType,oilCfgExtPortStateChangeRespPtr->extPortId,"EXT_OUTPUT_PORT_TURN_ON", "EXT_PORT_ACK");

      }
      else
      {

        LOG_PRINT(INFO,"PortType(%d) PortId(%d) AssignState(%s) EXT_OUTPUT_PORT_TURN_OFF  Response EXT_PORT_NACK (%s)", oilCfgExtPortStateChangeRespPtr->extPortType,oilCfgExtPortStateChangeRespPtr->extPortId,"EXT_OUTPUT_PORT_TURN_OFF","EXT_PORT_NACK" );
      }
      break; 
			
			/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/	 
     case OAM_OIL_CFG_1U_CARD_INFO_RESP:
			{
      		LOG_PRINT(INFO,"1U: OAM_OIL_CFG_1U_CARD_INFO_RESP received going to call updateSystemDetails1U()");
					copySystemDetails1U();
					//if(gCurrentCardState == CARDSTATE_ACTIVE)
					//{
					updateSystemDetails1U();
					//} 
			}
		 break;
			/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/	 
    default: 
      break; 
  } 
}/* oilMsgHandler*/          

void grhmMsgHandler() 
{ 
  I_U32 index; 
  /* Trx Block Feature : Starts */	
  OamsCfgTrxhLockReq lockBuff;
  I_U32 ptrxId;
  I_S32 rVal; 
  /* Trx Block Feature : Ends */    
  /* Major changes made in this function for Mantis 2284*/
  switch (((SysHdr*) gCfgMsgBuf)->msgType) 
  {    
    /* Trx Block Feature : Starts */
    case CSAPP_GRHM_CFG_STOP_CHAN_ALLOC_ACK: 
      { 
        LOG_PRINT(LOG_INFO,"Received CSAPP_GRHM_CFG_STOP_CHAN_ALLOC_ACK  from GRHM ..");
        if((( CsappGrhmCfgStopChanAllocAck* )gCfgMsgBuf)->result == TCH_FREE )
        {
          ptrxId = (( CsappGrhmCfgStopChanAllocAck* )gCfgMsgBuf)->ptrxId ;
          StopTimerFrmwrk(gTimerId);   /* Stop the Timer for Trx Block */
          {
            /* Send Trx Lock Request*/ 
            lockBuff.sysHdr.msgType = OAMS_CFG_TRXH_LOCK_REQ;
            lockBuff.objId = ptrxId;
            lockBuff.objType = OAMS_OBJTYPE_PTRX;
            lockBuff.reason = OAMS_RSN_OPERATORINITIATED;

            LOG_PRINT(LOG_INFO," Sending Trx Lock Request");
            rVal = cfgSendMessage(&lockBuff,sizeof(OamsCfgTrxhLockReq), ENT_OAMS_TRXH, OAMS_CFG_TRXH_LOCK_REQ,0);
            if (rVal == CFG_FAILURE)
            {
              LOG_PRINT(LOG_CRITICAL, " OAMS_CFG_TRXH_LOCK_REQ send Failed");
            }/*End of if*/
            if (rVal == CFG_SUCCESS)
            {
              LOG_PRINT(LOG_INFO," OAMS_CFG_TRXH_LOCK_REQ  send SUCCESS");
              gPtrxData[ptrxId].ptrxState = lockInProgress; 
            } /*End of if*/ 
          }               
        }
        else
        {
          LOG_PRINT(LOG_INFO,"TCH are Busy, so TRX LOCK will execute after Timer Expiry.....");
        }
        break;
      } 
      /* Trx Block Feature : Ends */

    case CSAPP_GRHM_CFG_LOCK_RESP: 
      LOG_PRINT(LOG_INFO,"Received CSAPP_GRHM_CFG_LOCK_RESP  from GRHM ..");

      // CS4.0
      // Check if the message received is in response to lOS Active
      if((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->reason == OAMS_RSN_LOS_ACTIVE_ALARM_RCVD )
      {
        // Call TrunkPortObjectHandler
        TrunkPortObjectHandler();
      } //CS 4.0
      else if(((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->objType == OAMS_OBJTYPE_AINTERFACE) &&  (gBssState == lockInProgress ))
        dispachToObjectHandler((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->objType ); 
      else if( (( CsappGrhmCfgLockResp* )gCfgMsgBuf)->objType == OAMS_OBJTYPE_AINTERFACE)
        /* KPI PHASE-II Changes Starts*/
      {
        updateRadioNwAvlbltyTblAtAifDown();
        sendCellBarAccessToCells(LockProcedure,OAMS_RSN_AINTERFACEDOWN);
      }
      /* KPI PHASE-II Changes Ends*/
      /* CS4.0 HA Stack Changes : Start*/
      else if ((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->objType == OAMS_OBJTYPE_CIC) 
        cicLockRespHandler(); 
      /* CS4.0 HA Stack Changes : End*/ 
      else 
        dispachToObjectHandler((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->objType ); 
      break;

    case CSAPP_GRHM_CFG_UNLOCK_RESP:
      LOG_PRINT(LOG_INFO,"Received CSAPP_GRHM_CFG_UNLOCK_RESP  from GRHM ..");   

      if((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->reason == OAMS_RSN_LOS_CLEAR_ALARM_RCVD  )
      {
        // CS4.0 
        // Call TrunkPortObjectHandler
        TrunkPortObjectHandler();

      }
      /* CS4.0 HA Stack Changes: Start */
      else if ((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->reason == OAMS_RSN_UNBLOCKCICS)
      { 
        unblockCicsRespHandler();
      }
      /* CS4.0 HA Stack Changes: End */
      else if(((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objType == OAMS_OBJTYPE_AINTERFACE) &&  (gBssState == unlockInProgress ))
        dispachToObjectHandler((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objType );
      else if((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objType == OAMS_OBJTYPE_AINTERFACE)
      {
        setAinterfaceTableOperationalState(ENABLED); /* Mantis 2284 - moved from SS_ALLWED case to here*/
        /* KPI PHASE-II Changes Starts*/
        updateRadioNwAvlbltyTblAtAifUp();
        /* KPI PHASE-II Changes Ends*/
        sendCellBarAccessToCells(UnlockProcedure,OAMS_RSN_AINTERFACEUP);
      }
      /* CS4.0 HA Stack Changes : Start*/
      else if ((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objType == OAMS_OBJTYPE_CIC) 
        cicUnlockRespHandler(); 
      /* CS4.0 HA Stack Changes : End*/ 
      else if(gSSAReceived == FALSE)
      {
        LOG_PRINT(LOG_INFO,"CSAPP_GRHM_CFG_ULOCK_RESP Message Droped");
      }
      else
        dispachToObjectHandler((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objType ); 
      break; 
    case CSAPP_GRHM_CFG_UNLOCK_FAIL: 
      {
        LOG_PRINT(LOG_INFO,"CSAPP_GRHM_CFG_UNLOCK_FAIL Received from GRHM ..");   
        LOG_PRINT(LOG_DEBUG,"Value of gSSAReceived = %d",gSSAReceived);   
        if((( CsappGrhmCfgUnlockFail* )gCfgMsgBuf)->objType != OAMS_OBJTYPE_AINTERFACE)
        {
          LOG_PRINT(LOG_MAJOR,"CSAPP_GRHM_CFG_UNLOCK_FAIL  from GRHM is only expected for A interface object");   
        }
        else if ( gSSAReceived == TRUE )
        {
          bssObjectHandlerForSSAllowed();
        }
      } 
      break; 

    case CSAPP_GRHM_CFG_ALARM_IND: 
      LOG_PRINT(LOG_INFO,"Received CSAPP_GRHM_CFG_ALARM_IND  from GRHM ..");   
      cfgAlarmHandler();
      break;          
      /* Changes For CS2.2 : Start */
    case CSAPP_GRHM_CFG_SWITCH_CONNECT_ACK:
      {
        CsappGrhmCfgSwitchConnectAck* switchConnectAckPtr = 
          (CsappGrhmCfgSwitchConnectAck *)(gCfgMsgBuf);

        LOG_PRINT(LOG_INFO,"Received CSAPP_GRHM_CFG_SWITCH_CONNECT_ACK from GRHM");
        LOG_PRINT(LOG_DEBUG,"E1 : %d, Ts : %d",switchConnectAckPtr->firstE1Num,
            switchConnectAckPtr->firstTimeSlotNum);

        if(gCurrentCardState == CARDSTATE_STANDBY)
        {
          LOG_PRINT(DEBUG,"SWITCH CONNECT ACK rcvd in standby State");
          return;
        }

        /* CS4.0 HA Stack Changes: Start */
        if (getScmSubProcState() == OAMS_CFG_GRHM_SWITCH_CONNECT)
        {
          linkSwitchConnectAckHandler();
          return;
        }
        /* CS4.0 HA Stack Changes: End */
        /* If Switch Connect Ack is received for LAPD_BIC type, then change 
         * its state to Unlock & Update in DB & Raise Alarm */
        /*Mantix 6673 Fixed Starts- Gaurav Bhatnagar*/

        //            if(switchConnectAckPtr->firstE1Num >= CFG_MAX_NUM_E1)
        if(isE1Inframe(switchConnectAckPtr->firstE1Num) == CFG_SUCCESS)
        {
          LOG_PRINT(INFO,"E1 rcvd is internal");   
          /* For In-Frame Trx, No need to check state of TimeSlot */
          //break; BSC R2.0 Changes
        }
        /*Mantix 6673 Fixed Ends- Gaurav Bhatnagar*/

        /* Update Connectivity State of Bic Table */
        //else //A6 inframe changes
        //{
        if(getInFrameTrxE1TsTableOnSecIndices(switchConnectAckPtr->firstE1Num,switchConnectAckPtr->firstTimeSlotNum) == CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_INFO,"No need to update BicTrxTsUsageTable in case of Inframe trx for E1 %d,Ts %d ",switchConnectAckPtr->firstE1Num,switchConnectAckPtr->firstTimeSlotNum);

        }
        else
        {
          BicTrxTimeslotUsageTableApi *bicTrxTimeslotPtr = NULL;
          if (getBicTrxTimeslotUsingE1Ts(switchConnectAckPtr->firstE1Num,switchConnectAckPtr->firstTimeSlotNum,&bicTrxTimeslotPtr) == CLIB_SUCCESS)
          {
            if(getIndex(bicTrxTimeslotPtr->bicOrTrxId,&index)!= CFG_FAILURE)
            {  
              LOG_PRINT(LOG_DEBUG,
                  "Values of Internal Data : BtsId : %d, btsState : %d,btsType : %d, ConnectivityState : %d",
                  gBtsData[index].BTSID,gBtsData[index].btsState,
                  gBtsData[index].btsType,gBtsData[index].connectivityState); 
              if(connectInProgress == gBtsData[index].connectivityState)
              {
                updateBtsConnectivityState(bicTrxTimeslotPtr->bicOrTrxId,BTS_CONNECT);
                gBtsData[index].connectivityState = none; 
                cfgSendAckToCm();
                free(bicTrxTimeslotPtr); 
                return;
              }
            }
            free(bicTrxTimeslotPtr); 
          }
        }
        break;
      }
        case CSAPP_GRHM_CFG_SWITCH_CONNECT_NACK:
      {
        /* Raise SWITCHING_FAILED Alarm */
        OamsCfgAfhSysAlarm oamsCfgAfhSysAlarm;
        CsappGrhmCfgSwitchConnectNack* switchConnectNack = 
          (CsappGrhmCfgSwitchConnectNack *)(gCfgMsgBuf);
        LOG_PRINT(LOG_INFO,"Received CSAPP_GRHM_CFG_SWITCH_CONNECT_NACK \
            from GRHM");

        /* CS4.0 HA Stack Changes: Start */
        if (getScmSubProcState() == OAMS_CFG_GRHM_SWITCH_CONNECT)
        {
          linkSwitchConnectNackHandler();
        }
        /* CS4.0 HA Stack Changes: End */
        /*Mantix 6673 Fixed Starts- Gaurav Bhatnagar*/
        //            if(switchConnectNack->firstE1Num < CFG_MAX_NUM_E1)
        if(isE1Inframe(switchConnectNack->firstE1Num) == CFG_FAILURE)
        {
          /*Mantix 6673 Fixed Ends- Gaurav Bhatnagar*/
          if(unlockInProgress == 
              gE1TimeslotData[switchConnectNack->firstE1Num][switchConnectNack->
              firstTimeSlotNum].e1TimeslotState
            )
          {
            cfgSendNackToCm(CM_ERR_UNKNOWN);
            gE1TimeslotData[switchConnectNack->firstE1Num][
              switchConnectNack->firstTimeSlotNum].
              e1TimeslotState = locked;
          }
        } //A6 Inframe changes
        if(getInFrameTrxE1TsTableOnSecIndices(switchConnectNack->firstE1Num,switchConnectNack->firstTimeSlotNum) == CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_INFO,"No need to update BicTrxTsUsageTable in case of Inframe trx for E1 %d,Ts %d ",switchConnectNack->firstE1Num,switchConnectNack->firstTimeSlotNum);

        }

        else 
        {
          /* Update Connectivity State of Bic Table */
          BicTrxTimeslotUsageTableApi *bicTrxTimeslotPtr = NULL;
          if (getBicTrxTimeslotUsingE1Ts(switchConnectNack->firstE1Num,switchConnectNack->firstTimeSlotNum,&bicTrxTimeslotPtr) == CLIB_SUCCESS)
          {
            if(getIndex(bicTrxTimeslotPtr->bicOrTrxId,&index) != CFG_FAILURE)
            {
              LOG_PRINT(LOG_DEBUG,
                  "Values of Internal Data : BtsId : %d, btsState : %d,btsType : %d, ConnectivityState : %d",
                  gBtsData[index].BTSID,gBtsData[index].btsState,
                  gBtsData[index].btsType,gBtsData[index].connectivityState); 
              if(connectInProgress == gBtsData[index].connectivityState)
              {
                cfgSendNackToCm(CM_ERR_LAPD_SWITCHING_FAILED);
                gBtsData[index].connectivityState = none;
              }
            } 
            free(bicTrxTimeslotPtr); 
          } 
        } 

        oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_LAPD_SWITCHING_FAILED;
        oamsCfgAfhSysAlarm.sysAlarm.key1 = switchConnectNack->firstE1Num;
        oamsCfgAfhSysAlarm.sysAlarm.key2 = switchConnectNack->firstTimeSlotNum;
        oamsCfgAfhSysAlarm.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;

        oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
            oamsCfgAfhSysAlarm.sysAlarm.infoString,"Abis Lapd Ts Switching with MCC Failed \
            for E1 %d TimeSlot %d",oamsCfgAfhSysAlarm.sysAlarm.key1,
            oamsCfgAfhSysAlarm.sysAlarm.key2);

        cfgSendMessage(&oamsCfgAfhSysAlarm, sizeof(OamsCfgAfhSysAlarm), \
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
        break;
      }
      /* Changes For CS2.2 : End */
        default : 
      break; 
      } 
  } /*grhmMsgHandler */          

  void trxhMsgHandler() 
  { 
    /* Changes For CS2.2 : Start */
    OamsTrxhCfgAddTrxResp* oamsTrxhCfgAddTrxResp = 
      (OamsTrxhCfgAddTrxResp *)(gCfgMsgBuf);
    OamsTrxhCfgDelTrxResp* oamsTrxhCfgDelTrxResp = 
      (OamsTrxhCfgDelTrxResp *)(gCfgMsgBuf);
    I_S32 dbStatus = -1;
    I_U8 chasisFrameId;
    I_U8 slotId;
    TrxTableIndices trxTableIndices;
    BicTrxTimeslotUsageTableIndices bicTrxTimeslotUsageTableIndices;
    TrxTableApi *trxTableApi;
    /* Changes For CS2.2 : End */

    switch (((SysHdr*) gCfgMsgBuf)->msgType) 
    { 
      case OAMS_TRXH_CFG_UNLOCK_RESP: 
        LOG_PRINT(LOG_INFO,"Received OAMS_TRXH_CFG_UNLOCK_RESP  from TRXH ..");   
        dispachToObjectHandler((( OamsTrxhCfgUnlockResp* )gCfgMsgBuf)->objType ); 
        break; 
      case OAMS_TRXH_CFG_LOCK_RESP:    
        LOG_PRINT(LOG_INFO,"Received OAMS_TRXH_CFG_LOCK_RESP  from TRXH ..");   
        dispachToObjectHandler((( OamsTrxhCfgLockResp* )gCfgMsgBuf)->objType ); 
        break; 
        /*Changes R2.5.2. TRX Block: Start*/ 
      case OAMS_TRXH_CFG_BLOCK_RESP:    
        LOG_PRINT(LOG_INFO,"Received OAMS_TRXH_CFG_BLOCK_RESP  from TRXH ..");   
        dispachToObjectHandler((( OamsTrxhCfgBlockResp* )gCfgMsgBuf)->objType ); 
        break;
        /*Changes R2.5.2. TRX Block: End*/ 
      case OAMS_TRXH_CFG_ALARM_IND:    
        LOG_PRINT(LOG_INFO,"Received OAMS_TRXH_CFG_ALARM_IND  from TRXH ..");   
        cfgAlarmHandler(); 
        break;             
        /* Changes For CS2.2 : Starts */
      case OAMS_TRXH_CFG_ADD_TRX_RESP:
        {
          LOG_PRINT(LOG_INFO,"Received OAMS_TRXH_CFG_ADD_TRX_RESP from TRXH");
          LOG_PRINT(LOG_DEBUG,"Received ptrxId : %d",oamsTrxhCfgAddTrxResp->ptrxId);
          if(OAMS_RSLT_SUCCESS == oamsTrxhCfgAddTrxResp->result)
          {
            /* Send Switch Connect Msg to GRHM */
            trxTableIndices.ptrxId=oamsTrxhCfgAddTrxResp->ptrxId;
            dbStatus=getTrxTable(&trxTableIndices,&trxTableApi);
            if(dbStatus != CLIB_SUCCESS )
            {
              LOG_PRINT(LOG_INFO,"getTrxTable Db call failed ErrorCause: %d",dbStatus);
              cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
              return;
            }
            if(dbStatus == CLIB_SUCCESS && (trxTableApi->trxLocation == TRX_LOCATION_BIC || 
                  trxTableApi->trxLocation == TRX_LOCATION_IN_FRAME))
            {
              if(  !( (gCfgState == CFG_BPM_INIT) && (gCfgStandbyToActive == I_TRUE) )  )
              {
                prepAndSndSwitchConForTrx(oamsTrxhCfgAddTrxResp->ptrxId);
              } 

#if 0 
              if(CFG_READY == gCfgState || gCfgState == CFG_BPM_SW_QUERY)
              {
                if(gCfgStandbySlotId != 0)
                { 
                  sendBpmSwitchInfoForPeerCard(gCfgStandbySlotId);
                } 
              } 
#endif
            }
            /* Changes for R2.2 : Start */
            if (trxTableApi->trxLocation != TRX_LOCATION_IN_FRAME && gCfgState == CFG_READY )
            {
              sendIndicationToBic(trxTableApi);
            }
            /* Changes for R2.2 : End */
            free(trxTableApi);
            gSentAddTrxReqAtInitNum--;
            if(gCfgState == CFG_BPM_INIT)
            {
              if(gSentAddTrxReqAtInitNum == 0)
              {
                //gCfgState = CFG_START_TRAU;
                //sendTrauStartMsg();
              }
            }
          }
          else
          {
            LOG_PRINT(LOG_CRITICAL,"TRX Add Operation Failed at TRXH. Cause \
                : %d",oamsTrxhCfgAddTrxResp->cause);
          }
          break;
        }
      case OAMS_TRXH_CFG_DEL_TRX_RESP:
        {

          ApplTeiPoolTableSecIndices          applTeiPoolTableSecIndices;
          ApplTeiPoolTableApi*                applTeiPoolTableOutData =PNULL;
          ApplTeiPoolTableApi*                applTeiPoolTable1 =PNULL;
          I_U32                               tmpTrxLocation=ZERO;
          I_U32 outRow=0;
          I_U16 outsz=0;
          LOG_PRINT(LOG_INFO,"Received OAMS_TRXH_CFG_DEL_TRX_RESP from TRXH");
          LOG_PRINT(LOG_DEBUG,"Received ptrxId : %d",oamsTrxhCfgDelTrxResp->ptrxId);
          if(OAMS_RSLT_SUCCESS == oamsTrxhCfgDelTrxResp->result)
          {
            trxTableIndices.ptrxId=oamsTrxhCfgDelTrxResp->ptrxId;
            dbStatus=getTrxTable(&trxTableIndices,&trxTableApi);
            if(dbStatus != CLIB_SUCCESS )
            {
              LOG_PRINT(LOG_INFO,"getTrxTable Db call failed ErrorCause: %d",dbStatus);
              cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
              return;
            }
            tmpTrxLocation=trxTableApi->trxLocation;/* Changes for R2.8*/ 
            if(trxTableApi->trxLocation != TRX_LOCATION_IN_FRAME )
            {
              sendIndicationToBic(trxTableApi);
            }
            if (trxTableApi->trxLocation != TRX_LOCATION_R2_BTS && trxTableApi->trxLocation != TRX_LOCATION_R2_BTS_IP && trxTableApi->trxLocation != TRX_LOCATION_R3_BTS )
            {
              if ( ( dbStatus = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
              {
                LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",dbStatus);
                cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
                free(trxTableApi);
                return;
              }
              LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
              SwMNodeTableIndices swMNodeTableIndex;
              swMNodeTableIndex.nodeType = SYS_NODE_TYPE_TRX;
              swMNodeTableIndex.nodeIdentity = oamsTrxhCfgDelTrxResp->ptrxId;
              swMNodeTableIndex.chasisFrameId = chasisFrameId;
              swMNodeTableIndex.slotId = slotId;
              if(deleteSwMNodeTable(&swMNodeTableIndex) != CLIB_SUCCESS)
              {
                LOG_PRINT(LOG_MAJOR,"deleteSwMNodeTable DB call is geting Failed");
                cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
                free(trxTableApi);
                return;  
              }
              else
              {
                LOG_PRINT(LOG_INFO,"deleteSwMNodeTable Successfull");
              } 
            }
            if((trxTableApi->trxLocation != TRX_LOCATION_R2_BTS_IP) && (trxTableApi->trxLocation != TRX_LOCATION_R3_BTS))/*Changes for R2.8*/
            {  
              if (trxTableApi->trxLocation == TRX_LOCATION_R2_BTS )
                bicTrxTimeslotUsageTableIndices.tsUser = TS_USAGE_BTS_TRX;
              else
                bicTrxTimeslotUsageTableIndices.tsUser = TS_USAGE_BICTRX;

              bicTrxTimeslotUsageTableIndices.bicOrTrxId = oamsTrxhCfgDelTrxResp->ptrxId;
              dbStatus = deleteBicTrxTimeslotUsageTable(&bicTrxTimeslotUsageTableIndices);
              free(trxTableApi);

              /* Delete Row From TrxTable */   
              if(markFreeAbisTimeSlotTable(oamsTrxhCfgDelTrxResp->ptrxId)!=CFG_SUCCESS)
              {
                LOG_PRINT(LOG_INFO,"Updation of AbisTimeSlot table in DB failed");
                cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
                return;
              }

#if 0
              /*BSC HA changes*/
              if(gCfgStandbySlotId != 0)
              { 
                sendBpmSwitchInfoForPeerCard(gCfgStandbySlotId);
              } 
#endif
            } 
            trxTableIndices.ptrxId = oamsTrxhCfgDelTrxResp->ptrxId;
            dbStatus = deleteTrxTable(&trxTableIndices);
            if(DBLIB_SUCCESS != dbStatus)
            {
              LOG_PRINT(LOG_MAJOR,"Deletion of TrxTable in DB Failed");
              cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
              return;
            }
            else
            {
              LOG_PRINT(LOG_INFO,"Deletion of TrxTable in DB is done Successfully");
              delTrxTsTeiTable(oamsTrxhCfgDelTrxResp->ptrxId);

              if( (tmpTrxLocation==TRX_LOCATION_R2_BTS_IP)||(tmpTrxLocation==TRX_LOCATION_R3_BTS) )
              {
                applTeiPoolTableSecIndices.applTeiUser=(I_U8)TEI_USR_TRX;
                applTeiPoolTableSecIndices.userId=oamsTrxhCfgDelTrxResp->ptrxId;  
                dbStatus = getSecApplTeiPoolTable(&applTeiPoolTableSecIndices, &applTeiPoolTableOutData,
                    &outRow, &outsz);
                if(DBLIB_SUCCESS != dbStatus)
                {
                  LOG_PRINT(LOG_MAJOR,"addConfiguredBics: Get appTei failed for Trx Id %d trxLocation                     %d",oamsTrxhCfgDelTrxResp->ptrxId,tmpTrxLocation);
                }
                else
                {  
                  applTeiPoolTable1=(ApplTeiPoolTableApi*)((I_U8 *)applTeiPoolTableOutData);
                  dbStatus=deAllocateApplTei((I_U16)applTeiPoolTable1->applTei); 
                } 
              }
              cfgSendAckToCm();
            }
          }
          else
          {
            LOG_PRINT(LOG_DEBUG,"TRX Delete Operation Failed at TRXH. Cause \
                : %d",oamsTrxhCfgDelTrxResp->cause);
            cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
          }
          break;
        }
        /* Changes For CS2.2 : Ends */
        /* Changes For R2.2 : Start */
      case OAMS_TRXH_CFG_TRX_RESET_ACK: 
        {
          OamsTrxhCfgTrxResetAck* oamsTrxhCfgTrxResetAck =
            (OamsTrxhCfgTrxResetAck*)(gCfgMsgBuf);
          LOG_PRINT(LOG_INFO,"Received OAMS_TRXH_CFG_TRX_RESET_ACK from TRXH");
          LOG_PRINT(LOG_DEBUG,"Received ptrxId : %d",oamsTrxhCfgTrxResetAck->objId);
          cfgSendAckToCm();/*Send CM_APPI_RESPONSE with status = CM_SUCCESS to CM*/
          break;
        }
      case OAMS_TRXH_CFG_TRX_RESET_NACK: 
        {
          OamsTrxhCfgTrxResetNack* oamsTrxhCfgTrxResetNack =
            (OamsTrxhCfgTrxResetNack*)(gCfgMsgBuf);
          LOG_PRINT(LOG_INFO,"Received OAMS_TRXH_CFG_TRX_RESET_NACK from TRXH");
          LOG_PRINT(LOG_DEBUG,"Received ptrxId : %d",oamsTrxhCfgTrxResetNack->objId);
          if (oamsTrxhCfgTrxResetNack->cause == ERR_TIMEOUT)
            cfgSendNackToCm(CM_ERR_TIMEOUT);/*Send CM_APPI_RESPONSE with status = CM_SUCCESS to CM*/
          if (oamsTrxhCfgTrxResetNack->cause == ERR_LAPD_DOWN)
            cfgSendNackToCm(CM_ERR_BTS_LAPD_NOT_ESTABLISHED);
          if (oamsTrxhCfgTrxResetNack->cause == ERR_DB_OPER_FAIL)
            cfgSendNackToCm(CM_ERR_DB_FAILED);
          if (oamsTrxhCfgTrxResetNack->cause == ERR_MEM_FAILURE)
            cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
          break;
        }
        /* Changes For R2.2 : End */
      default : 
        break; 
    } 

  } /*trxhMsgHandler*/          

  void cellhMsgHandler() 
  { 

    switch (((SysHdr*) gCfgMsgBuf)->msgType) 
    { 
      case OAMS_CELLH_CFG_UNLOCK_RESP: 
      case OAMS_CELLH_CFG_LOCK_RESP:    
        dispachToObjectHandler (OAMS_OBJTYPE_CELL); 
        break;
        /*BSC CS4.0 : Abis E1 Lock/Unlock changes Starts*/

      case OAMS_CELLH_CFG_E1_UNLOCK_RESP:
        e1UnlockRespHandler();
        break;

      case OAMS_CELLH_CFG_E1_LOCK_RESP:
        e1LockRespHandler();
        break;
        /*BSC CS4.0 : Abis E1 Lock/Unlock changes Starts*/

      case OAMS_CELLH_CFG_ALARM_IND: 
        LOG_PRINT(LOG_INFO,"Received  OAMS_CELLH_CFG_ALARM_IND  from CELLH ..");   
        cfgAlarmHandler(); 
        break;                      
      default : 
        break; 
    } 
  } /* cellhMsgHandler */          


  void scmMsgHandler() 
  { 
    switch (((SysHdr*) gCfgMsgBuf)->msgType) 
    {
#if 0 /* CS4.0 HA Stack Changes */  
      case BSC_API_SET_LINKADMINSTATETABLE:     
        LOG_PRINT(LOG_INFO,"Received BSC_API_SET_LINKADMINSTATETABLE  from SCM via OIL..");   
        if (( gBssState == unlockInProgress ) || 
            ( gBssState == lockInProgress ))
        {
          bssObjectHandler();
        }
        else
        {
          I_U32 state ;

          if ( gMsgSentForE1Num != 0xff )
          {
            state = getE1ObjectState(gMsgSentForE1Num);

            if (( state == unlockInProgress ) || 
                ( state == lockInProgress ))
            {
              e1ObjectHandler();
              if ( gE1Data[gMsgSentForE1Num].msgsSentForE1 == 0)
                gMsgSentForE1Num = 0xff;
            }
            else
            {
              LOG_PRINT(LOG_CRITICAL," No Match found for E1 object state ");   
            }            
          }
          else 
            if ( gMsgSentForE1TSNum != 0xff)
            {
              I_U32 e1Num;   
              I_U32 tsNum;   

              e1Num = (gMsgSentForE1TSNum >> 16);
              tsNum = (gMsgSentForE1TSNum & 0x00ff);

              state = getTimeSlotObjectState(e1Num,tsNum);  
              gMsgSentForE1TSNum = 0xff;
              if (( state == unlockInProgress ) || 
                  ( state == lockInProgress ))
              {
                e1TimeSlotObjectHandler();
              }
              else
              {
                LOG_PRINT(LOG_CRITICAL," No Match found for Timeslot object State ");   
              }            

            }
            else
            {
              LOG_PRINT(LOG_CRITICAL," Unexpected Message ");   
            }
        }
        break;      
#endif 
      case OAMS_SCM_CFG_ALARM_IND: 
        LOG_PRINT(LOG_INFO,"Received OAMS_SCM_CFG_ALARM_IND  from SCM via OIL..");   
        cfgAlarmHandler(); 
        break; 
      default : 
        break;       
    } 
  }/* scmMsgHandler */          

  void psscmMsgHandler() 
  { 
    /*Merger for #Mantis 31470*/
    GbInterfaceTableApi* gbIfTblApiPtr = PNULL;
    I_S32  ret = CM_FAILURE;
    I_U32 outRows = 0;
    I_U16 outSize = 0;
    /*Merger for #Mantis 31470*/


    switch (((SysHdr*) gCfgMsgBuf)->msgType) 
    { 
      /*Changes PCU R2.5 Aricent -- START*/
      case OAMS_PSSCM_CFG_LOCK_RESP: 
        LOG_PRINT(LOG_INFO,"Received OAMS_PSSCM_CFG_LOCK_RESP  from PSSCM.");   
        //bssObjectHandler(); //Merger for Mantis #31470
 //Merger for Mantis #31470
        if (gNseLockUnlockProc == I_TRUE)
        {
		     gNseLockUnlockProc = I_FALSE;
		     gNseiData.nseiState = locked;
		     ret = getallGbInterfaceTable(&gbIfTblApiPtr, &outRows, &outSize);
         if (ret == DBLIBERR_PTOPAGE_HAS_NO_ROWS)
         {
           LOG_PRINT(LOG_MAJOR, "No rows present in gb Interface Table, sending Nack");
         }
		     else
		     {
			     gbIfTblApiPtr->adminState = LOCKED;
           ret = updateGbInterfaceTable(gbIfTblApiPtr);
           if (ret == CLIB_SUCCESS)      
           {
             LOG_PRINT(LOG_INFO,"Update DB Successful");
		       }
			     sendNseLockUnlockAlarm (gbIfTblApiPtr->nsei,gbIfTblApiPtr->adminState);
			     free (gbIfTblApiPtr);
		     }
		   }
		   else
		   {
         bssObjectHandler();
		   }
 //Merger for Mantis #31470
        break; 
      case OAMS_PSSCM_CFG_UNLOCK_RESP: 
        LOG_PRINT(LOG_INFO,"Received OAMS_PSSCM_CFG_UNLOCK_RESP  from PSSCM.");   
        if ((gGbTransportType == FR) && (gCfgStandbyToActive == I_TRUE) )
        {
          gbOverFrSwitchoverHandling();
        }
        //else //Merger for Mantis #31470
        //Merger for Mantis #31470
        else if (gNseLockUnlockProc == I_TRUE)
        {
		      sendPschNseUnlockReq(gNseiData.nsei);
        }
        else
        {
           bssObjectHandler();
        }
        //Merger for Mantis #31470
        break; 
      case OAMS_NSVCH_CFG_UNLOCK_RESP:
        LOG_PRINT(LOG_INFO,"Received OAMS_NSVCH_CFG_UNLOCK_RESP from NSVCH.");   
        nsvcObjectHandler();
        break;
      case OAMS_NSVCH_CFG_LOCK_RESP:
        LOG_PRINT(LOG_INFO,"Received OAMS_NSVCH_CFG_LOCK_RESP from NSVCH.");   
        nsvcObjectHandler();
        break;
      case OAMS_NSVCH_CFG_ALARM_IND:
        LOG_PRINT(LOG_INFO,"Received OAMS_NSVCH_CFG_ALARM_IND from NSVCH.");   
        cfgAlarmHandler();
        break;      
      case OAMS_PSSCM_CFG_ALARM_IND:
        LOG_PRINT(LOG_INFO,"Received OAMS_PSSCM_CFG_ALARM_IND from PSSCM.");   
        cfgAlarmHandler();
        break;      
        /*Changes PCU R2.5 Aricent -- END*/     
      default : 
        break;          
    }

  } /* psscmMsgHandler */    

  void frMsgHandler()
  {
    switch (((SysHdr*) gCfgMsgBuf)->msgType)
    {
      /*Changes PCU R2.5 Aricent -- START*/
      case PSSKS_FR_CFG_ALARM_IND:
        LOG_PRINT(LOG_INFO,"Received PSSKS_FR_CFG_ALARM_IND from FR");
        cfgAlarmHandler();
        break;
      default : 
        break;         
    } 
  }

  void mgsMsgHandler()
  {
    LOG_PRINT(LOG_INFO,"Message Received in mgsMsgHandler from TSM(MGS)..");
    tHdr *tsmHdr = (tHdr*)(gCfgMsgBuf + sizeof(SysHdr));
    if (tsmHdr->DestId == MGS_DEST_TSI_APP)
    {
      LOG_PRINT(LOG_INFO,"Received MGS_DEST_TSI_APP from TSM(MGS)..");
      if((*(I_U8*)(gCfgMsgBuf + sizeof(SysHdr) + sizeof(tHdr))) == MGS_TSM_TSI_DRIVER_INIT_STS)
      {
        LOG_PRINT(LOG_INFO,"Received MGS_TSM_TSI_DRIVER_INIT_STS  from TSM(MGS)..");   
        gMgsSmmTsiRspFlag = FALSE;
        gMgsOprSts = FALSE;

        cfgStopTimer();
        //       stopMgsTimer();
        cfgTsiDriverInitRespHandler((DSmmMgsuDriverInitStatus *)gCfgMsgBuf);

        RELEASE_MUTEX;
        gCfgState = CFG_BPM_INIT;
        LOG_PRINT(LOG_DEBUG,"gCfgState: [CFG_BPM_INIT] i.e. [%d]", gCfgState);

#if 0 //R2.0 	
        if ( gMgsSmmDspBootFlag == FALSE) 
        {
          cfgStopTimer();
          //            stopMgsTimer();
          cfgTsiDriverInitRespHandler((DSmmMgsuDriverInitStatus *)gCfgMsgBuf);
          cfgDspInitWtRspHandler(gStoredDspBootMsg);
          DalocOrdBuf(gStoredDspBootMsg);
          gStoredDspBootMsg = NULL;
        }
        else
        {
          gStoredTsiDriverStatusMsg=(DSmmMgsuDriverInitStatus *)AlocOrdBuf(sizeof(DSmmMgsuDriverInitStatus));
          if(PNULL == gStoredTsiDriverStatusMsg)
          {
            LOG_PRINT(LOG_CRITICAL,"Memory allocation using AlocOrdBuf");   
          }
          memcpy(gStoredTsiDriverStatusMsg,gCfgMsgBuf,sizeof(DSmmMgsuDriverInitStatus));
        }
#endif
      }
    }
    else if (tsmHdr->DestId == MGS_DEST_TRAU_APP)
    {
      message_hdr_t *trauHdr = (message_hdr_t *)(gCfgMsgBuf + sizeof(SysHdr) + sizeof(tHdr));
      LOG_PRINT(LOG_INFO,"Wrong Messgae Received from MGS for MGS_DEST_TRAU_APP, msgId(%d)",
          trauHdr->Msg_Id);

#if 0 //R2.0 	
      switch (trauHdr->MessageID)
      {
        case  DSP_BOOT_MSG_ID:
          {
            LOG_PRINT(LOG_INFO,"Received MGS_DSP_BOOT  from TSM(MGS)..");   
            gMgsSmmDspBootFlag = FALSE;
            if ( gMgsSmmTsiRspFlag == FALSE) 
            {
              cfgStopTimer();
              //                  stopMgsTimer();
              cfgTsiDriverInitRespHandler(gStoredTsiDriverStatusMsg);
              cfgDspInitWtRspHandler((DSmmMgsBootMsg *)gCfgMsgBuf);
              DalocOrdBuf(gStoredTsiDriverStatusMsg);
              gStoredTsiDriverStatusMsg = NULL;
            }
            else
            {
              gStoredDspBootMsg=(DSmmMgsBootMsg*)AlocOrdBuf(sizeof(DSmmMgsBootMsg));
              if(PNULL == gStoredDspBootMsg)
              {
                LOG_PRINT(LOG_CRITICAL,"Memory allocation using AlocOrdBuf");   
                break; 
              } 
              memcpy(gStoredDspBootMsg,gCfgMsgBuf,sizeof(DSmmMgsBootMsg));
              LOG_PRINT(LOG_DEBUG,"Trau Channels After Getting Boot Test Message : %d",gStoredDspBootMsg->max_num_trau);
            }
          }
          break;
        case DSP_INIT :
          {
            DSmmDspInitResMsg *DspInitResBuff = (DSmmDspInitResMsg *)(gCfgMsgBuf); /* Fixed For Mantis# 3783 */
            //DSmmTrauStartReqMsg TrauStartReqBuff;
            cfgStopTimer();
            //               stopMgsTimer();

            if (DspInitResBuff->response==DSP_SUCCESS)
            {
            }
            else 
            {
              gMgsWaitForRspFlg = MGS_NO_WAIT;
              gMgsOprSts = FALSE;
              LOG_PRINT(LOG_INFO,"Getting DSP_FAILURE in DSP_INIT response message");

#if 0
              OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
              OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId =TRAU_INITIALIZATION_FAILED;
              OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
              OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_BSS;
              OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = gDbBssTableApiStorage.bscId;
              OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Trau Init Failed on BSC Id [%d]",OamsCfgAfhSysAlarmBuff.sysAlarm.key1);

              cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, 
                  OAMS_CFG_AFH_ALARM_IND, 0);
              if((ZERO == gSentAddBicReqAtInitNum))
              {
                /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
                sndSwitchConForBicsAtInit();
                /* CS3.0 Changes : Start */
                if(gCfgState == CFG_INIT_TSI)
                {
                  sendRequestForAvailableReleases(); 
                  gCfgState = CFG_BPM_SW_QUERY;
                  LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
                }
                /* CS3.0 Changes : End */
              }

#endif
            }
            RELEASE_MUTEX;
            gCfgState = CFG_BPM_INIT;
            LOG_PRINT(LOG_DEBUG,"gCfgState: [CFG_BPM_INIT] i.e. [%d]", gCfgState);
          }
          break;   
        case TRAU_START :
          {
            DSmmTrauStartResMsg *TrauStartResBuff = (DSmmTrauStartResMsg *)(gCfgMsgBuf); /*Fixed For Mantis# 3783*/
            gMgsOprSts = FALSE;
            cfgStopTimer();
            //               stopMgsTimer();

            if(TrauStartResBuff->response==DSP_SUCCESS)
            {
              TrauOprStsTableApi TrauOprStsTableApiBuf;
              gMgsWaitForRspFlg = MGS_NO_WAIT;
              LOG_PRINT(LOG_INFO,"Received MGS_TRAU_START_RESP  from TSM(MGS)..");   
              OamsCfgGrhmStartChanAlloc  oamscfgGrhmbuff;
              memset(&oamscfgGrhmbuff,0,sizeof(OamsCfgGrhmStartChanAlloc));  
              oamscfgGrhmbuff.reason=OAMS_RSN_TRAUUP;

              cfgSendMessage(&oamscfgGrhmbuff,sizeof(OamsCfgGrhmStartChanAlloc), ENT_CSAPP_GRHM, 
                  OAMS_CFG_GRHM_START_CHAN_ALLOC ,0);
              LOG_PRINT(LOG_INFO,"OAMS_CFG_GRHM_START_CHAN_ALLOC has been Sent.."); 
              TrauOprStsTableApiBuf.trauId = TRAU_ID;
              TrauOprStsTableApiBuf.oprStatus = ENABLED;
              if( updateTrauOprStsTable(&TrauOprStsTableApiBuf) == CLIB_SUCCESS)
              {
                LOG_PRINT(LOG_INFO, "Update for TrauConfigTable is successful");
              }
              if((ZERO == gSentAddBicReqAtInitNum) && 
                  (FALSE == gMgsOprSts)
                )
              {
                /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
                sndSwitchConForBicsAtInit();
                /* CS3.0 Changes : Start */
                /* goToReadyState(); */
                if(gCfgState == CFG_START_TRAU)
                {
                  sendRequestForAvailableReleases(); 
                  gCfgState = CFG_BPM_SW_QUERY;
                  LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
                }
                /* CS3.0 Changes : End */
              }
            }
            else 
            {
              LOG_PRINT(LOG_INFO, "Gettign DSP_FAILURE in DSP_TRAU_START response message");
              if((ZERO == gSentAddBicReqAtInitNum) && 
                  (FALSE == gMgsOprSts)
                )
              {
                /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
                sndSwitchConForBicsAtInit();
                /* CS3.0 Changes : Start */
                /* gCfgState = CFG_READY; */
                /* LOG_PRINT(LOG_INFO,"CFG is in Ready State"); */
                if(gCfgState == CFG_START_TRAU)
                {
                  sendRequestForAvailableReleases(); 
                  gCfgState = CFG_BPM_SW_QUERY;
                  LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
                }
                /* CS3.0 Changes : End */
              }
            }

          }
          break;
        case MGS_TRAU_ERROR_IND:
          {
            if (gCfgState == CFG_READY  || gCfgState == CFG_BPM_SW_QUERY)
            {
              TrauOprStsTableApi TrauOprStsTableApiBuf;
              OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff;
              cfgSendMessage(NULL,0, ENT_CSAPP_GRHM, OAMS_CFG_GRHM_STOP_CHAN_ALLOC  ,0); 
              TrauOprStsTableApiBuf.trauId = TRAU_ID;
              TrauOprStsTableApiBuf.oprStatus = DISABLED;

              if ( updateTrauOprStsTable(&TrauOprStsTableApiBuf) == CLIB_SUCCESS)
              {
                LOG_PRINT(LOG_INFO, "Update for TrauOprStsTableApi is successful");
              }

              OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = TRAU_DOWN_ALM;
              OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
              OamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_TRAU;
              OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = TRAU_ID;
              cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, 
                  OAMS_CFG_AFH_ALARM_IND, 0);

            }
            else
            {
              LOG_PRINT(LOG_MAJOR," Received MGS_TRAU_ERROR_IND in the wrong state");
            }
          }
          break;         
      }
#endif
    }
  } /* mgsMsgHandler */

  I_S32 cfgSendCmMessage(void *bufPtr, I_U32 size, I_S32 entId,I_U16 msgType, I_U8 subType) 
  { 
    sCmMsg   *sndPtr; 
    I_S16  sndMsgSize; 
    sndMsgSize = 0; 
    LOG_PRINT(LOG_INFO,"\t Calling cfgSendCMMessage()....."); 
    if (bufPtr != NULL) 
      sndMsgSize = size; 
    else
      sndMsgSize = sizeof(sCmMsg); 
    if ((sndPtr = (sCmMsg *)AlocMsgBuf(sndMsgSize)) == NULL) 
    { 
      LOG_PRINT(LOG_CRITICAL,"CFG_SEND_ALLOC_FAIL"); 
      return CFG_FAILURE; 
    } 
    memset(sndPtr,0,sndMsgSize) ; 
    /* Passed Pointer may contain the sys header */ 
    if (bufPtr != NULL) 
      memcpy(((I_U8 *)sndPtr), (I_U8*)bufPtr, size); 
    sndPtr->sHdr.msgType = msgType; 
    sndPtr->sHdr.src.entity = ENT_OAMS_CFG; 
    sndPtr->sHdr.dest.entity = entId; 
    /* Fix SPR 62 Starts */
    ((sCmMsg *)sndPtr)->cmHdr.size = sndMsgSize - sizeof(sCmMsg);
    /* Fixed SPR 62 */

    LOG_PRINT(LOG_INFO," Sending message, sndMsgSize = %d, sizeof(sCmMsg) = %d,cmHdr.size = %d", sndMsgSize , sizeof(sCmMsg), ((sCmMsg *)sndPtr)->cmHdr.size); 
    fflush(stdin); 
    if (SendMsg(sndPtr, 1, sndMsgSize) < 0) 
    { 
      LOG_PRINT(LOG_CRITICAL,"CFG: In func cfgSendMessage() - msg sending failed"); 
      DalocMsgBuf((I_PVoid) sndPtr); 
      return(CFG_FAILURE); 
    } 
    return(CFG_SUCCESS); 
  } /* cfgSendCmMessage */ 

  I_S32 cfgSendMessage(void *bufPtr, I_U32 size, I_S32 entId,I_U16 msgType, I_U8 subType) 
  { 
    SysHdr   *sndPtr; 
    I_S16  sndMsgSize; 
    sndMsgSize = 0; 
    LOG_PRINT(LOG_INFO,"\t Entering  cfgSendMessage...."); 
    if (bufPtr != NULL) 
      sndMsgSize = size; 
    else 
      sndMsgSize = sizeof(SysHdr);  
    if ((sndPtr = (SysHdr *)AlocMsgBuf(sndMsgSize)) == NULL) 
    { 
      LOG_PRINT(LOG_CRITICAL,"CFG_SEND_ALLOC_FAIL"); 
      return CFG_FAILURE;  
    } 

    memset(sndPtr,0,sndMsgSize) ; 
    /* Passed Pointer may contain the sys header */ 
    if (bufPtr != NULL) 
      memcpy(((I_U8 *)sndPtr), (I_U8*)bufPtr, size); 

    sndPtr->msgType = msgType; 
    sndPtr->src.entity = ENT_OAMS_CFG; 
    sndPtr->dest.entity = entId; 
    /* Changes PCU R2.5 Aricent -- START*/

    /* Processor id for CFG is PRCR_CP */
    sndPtr->src.prcr = PRCR_CP;

    switch (sndPtr->dest.entity)
    {
      /* Processor Id for GBH, PSCH, PSSCM, PSMSH, TBBSC, ABIHM, GSAL, FRU is PRCR_PP*/
      case ENT_OAMS_GBH:
      case ENT_OAMS_PSCH:
      case ENT_OAMS_PSSCM:
      case ENT_PSAPP_PSMSH:
      case ENT_PSAPP_TBBSC:
      case ENT_CSAPP_ABIHM:
      case ENT_PSSKS_GSAL:
      case ENT_PSSKS_FRU:
        sndPtr->dest.prcr = PRCR_PP; 
        break;
      case ENT_OAMS_CFG:
        sndPtr->dest.prcr = PRCR_PEER_CP; 
        break; 
      default:
        /* Processor Id for modules other than GBH, PSCH, PSSCM, PSMSH, TBBSC, ABIHM, GSAL, FRU is PRCR_CP*/
        sndPtr->dest.prcr = PRCR_CP; 
        break;
    }

    /* Changes PCU R2.5 Aricent -- END*/

    LOG_PRINT(LOG_DEBUG," sndPtr->msgType = %d, sndPtr->sHdr.src.entity = %d, sndPtr->sHdr.dest.entity = %d", sndPtr->msgType,sndPtr->src.entity,sndPtr->dest.entity); 

    fflush(stdin); 

    PRINT_HEX_DUMP(LOG_DEBUG, sndPtr, sndMsgSize);
    if (SendMsg(sndPtr, 1, sndMsgSize) < 0) 
    { 
      LOG_PRINT(LOG_CRITICAL,"CFG: In func cfgSendMessage() - msg sending failed"); 
      DalocMsgBuf((I_PVoid) sndPtr); 
      return(CFG_FAILURE); 
    } 
    return(CFG_SUCCESS); 
  } /* cfgSendMessage */ 

  void initiateBssUnlock() 
  { 
    getDbBssTable();
    /*Mantis Issue 6197 Fix by Gaurav Bhatnagar*/
    gBssState = unlockInProgress;
    gBssSubState = aIfUnlockInProgress; 
    /*Changes Starts for R2.3.4 Starts*/ 
    if(bssObjectSendLapdTimerConfigToScm() != I_TRUE)
    {
      bssObjectSendLinkAdminStateTableToScm(UNLOCKED,UNLOCKED);
    }
    /*Changes Starts for R2.3.4 Ends*/ 
    //   gBssState = unlockInProgress;
  } /* initiateBssUnlock */ 

#if 0
  void cfgDspInitWtRspHandler( DSmmMgsBootMsg* DspMgsuBootPtr)
  {
    LOG_PRINT(LOG_DEBUG,"Trau Channels After Getting Boot Test Message in cfgDspInitWtRspHandler function : %d",
        DspMgsuBootPtr->max_num_trau);
    if (DspMgsuBootPtr->response==DSP_SUCCESS)
    {
      cfgDspBootHandler();
    }
    else
    {
      LOG_PRINT(LOG_MAJOR,"Getting DSP_FAILURE in BootTest Message");
#if 0
      OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
      OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId =TRAU_INITIALIZATION_FAILED;
      OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
      OamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BSS;
      OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = gDbBssTableApiStorage.bscId;
      OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Trau Init Failed on BSC Id [%d]",OamsCfgAfhSysAlarmBuff.sysAlarm.key1);
      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
      gMgsOprSts = FALSE;
      if(gCfgState == CFG_INIT_TSI)
      {
        RELEASE_MUTEX;
        gCfgState = CFG_BPM_INIT;
        LOG_PRINT(LOG_INFO,"CFG is in BPM INIT STATE");
      }
      else if((ZERO == gSentAddBicReqAtInitNum)
          )
      {
        /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
        sndSwitchConForBicsAtInit();
        /* CS3.0 Changes : Start */
        /* gCfgState = CFG_READY; */
        /* LOG_PRINT(LOG_INFO,"CFG is in Ready State"); */
        if(gCfgState == CFG_START_TRAU)
        {
          sendRequestForAvailableReleases(); 
          gCfgState = CFG_BPM_SW_QUERY;
          LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
        }
        /* CS3.0 Changes : End */
      }
#endif
    }
  }
#endif


  void cfgDspBootHandler()
  {
#if 0
    DSmmDspInitReqMsg  DspInitReqBuff; 
    OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff;
    TrauOprStsTableApi TrauOprStsTableApiBuf;

    TrauOprStsTableApiBuf.trauId = TRAU_ID;
    TrauOprStsTableApiBuf.oprStatus = ENABLED;

    if ( gCfgState == CFG_READY || gCfgState == CFG_BPM_SW_QUERY)
    {
      /* During Run time */
      cfgSendMessage(NULL,0, ENT_CSAPP_GRHM, OAMS_CFG_GRHM_START_CHAN_ALLOC ,0);
      if ( updateTrauOprStsTable(&TrauOprStsTableApiBuf) == CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO, "Update for TrauOprStsTableApi is successful ");
      }

      OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId =TRAU_UP_ALM;
      OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
      OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_TRAU;
      OamsCfgAfhSysAlarmBuff.sysAlarm.key1 =TRAU_ID;

      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    }
    else
    {
      TrauConfigTableApi *trauConfigTableApiPtr=NULL;
      I_U32 outRows = 0;
      I_U16 outSize = 0;
      if ( getallTrauConfigTable(&trauConfigTableApiPtr,&outRows,&outSize)!= CLIB_SUCCESS )

      {
        LOG_PRINT(LOG_CRITICAL, "getallTrauConfigTable is unsuccessful ");
        return;
      }


      DspInitReqBuff.hdr.DestId          = MGS_DEST_TRAU;
      DspInitReqBuff.hdr.TotalLength       = DSP_INIT_SIZE;

      DspInitReqBuff.trauHdr.TransactionID = 1;
      DspInitReqBuff.trauHdr.ApplicationID = ENT_MGS_TSM;
      DspInitReqBuff.trauHdr.MessageType   = DSP_COM_MSG_BCAST;
      DspInitReqBuff.trauHdr.ServiceType   = DSP_ALL_SERVICE;
      DspInitReqBuff.trauHdr.Index         = DSP_ALL_INDEX;
      DspInitReqBuff.trauHdr.MessageID     = DSP_INIT ;
      DspInitReqBuff.trauHdr.MessageSize   = DSP_INIT_SIZE;
      DspInitReqBuff.law         = trauConfigTableApiPtr->trauCodingFormat;
      DspInitReqBuff.hbDuration   = 2;
      cfgSendMessage(&DspInitReqBuff, sizeof(DSmmDspInitReqMsg), ENT_IPC_TSMIF, EXT_TSM_MSG, 0);
      gMgsWaitForRspFlg =MGS_WT_FOR_MGS_DSP_INIT_RESP;
      cfgStartTimer("TSI_TRAU_INIT") ;
      //      startMgsTimer();
      free(trauConfigTableApiPtr);
    }
#endif
  }

  void cfgTsiDriverInitRespHandler(DSmmMgsuDriverInitStatus *DSmmMgsuDriverInitStatusPtr)
  {
    gMgsWaitForRspFlg= MGS_NO_WAIT;

    if ( DSmmMgsuDriverInitStatusPtr->tsiStatus == MGS_SMM_SUCCESS )
    {
      LOG_PRINT(LOG_INFO,"CFG:TSI Driver Init SUCCESS");
      //      cfgSendMessage(NULL, 0, ENT_CSAPP_GRHM, OAMS_CFG_GRHM_START_STATIC_SWITCHING, 0);

    }
    else
    {
      LOG_PRINT(LOG_INFO,"CFG:TSI Driver Init FAILURE");
#if 0
      OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
      OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId =TSI_INITIALIZATION_FAILED;
      OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
      OamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BSS;
      OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = gDbBssTableApiStorage.bscId;
      OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"TSI Init Failed on BSC Id [%d]",OamsCfgAfhSysAlarmBuff.sysAlarm.key1);
      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
      /* Change For CS2.2 */
      /* gCfgState = CFG_READY; */
      gMgsOprSts = FALSE;
      if(gCfgState == CFG_INIT_TSI)
      {
        RELEASE_MUTEX;
        gCfgState = CFG_BPM_INIT;
        LOG_PRINT(LOG_INFO,"CFG is in BPM INIT STATE");
      }
      else if((ZERO == gSentAddBicReqAtInitNum)
          )
      {
        /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
        sndSwitchConForBicsAtInit();
        /* CS3.0 Changes : Start */
        /* gCfgState = CFG_READY; */
        /* LOG_PRINT(LOG_INFO,"CFG is in Ready State"); */
        if(gCfgState == CFG_START_TRAU)
        {
          sendRequestForAvailableReleases(); 
          gCfgState = CFG_BPM_SW_QUERY;
          LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
        }
        /* CS3.0 Changes : End */
      }
#endif
      /* Change For CS2.2 : End */

    }

  } /* cfgTsiDriverInitRespHandler */

  void dispachToObjectHandler(I_U8  objectTypeRecvd) 
  { 
    switch (objectTypeRecvd) 
    { 
      case OAMS_OBJTYPE_CELL: 
        cellObjectHandler(); 
        break; 

      case OAMS_OBJTYPE_PTRX: 
        trxObjectHandler(); 
        break;    

      case OAMS_OBJTYPE_GBINTERFACE: 
      case OAMS_OBJTYPE_AINTERFACE: 
      case OAMS_OBJTYPE_BSS:    
        bssObjectHandler(); 
        break; 

      case OAMS_OBJTYPE_E1: 
        e1ObjectHandler(); 
        break;       

      case OAMS_OBJTYPE_TIMESLOT: 
        e1TimeSlotObjectHandler(); 
        break;   
      default : 
        LOG_PRINT(LOG_INFO,"dispachToObjectHandler: invalid objectType = %d rxd from TRHX ",objectTypeRecvd);
        /* log Error */ 
        break; 
    }    
  } /*dispachToObjectHandler  */

  void timerMsgHandler()
  {
    ApplTimer *applTimer=NULL;
    /* Trx Block Feature : Starts */   
    I_U32 ptrxId;
    /* Trx Block Feature : Ends */   
    I_U8 cellIndex;
    I_U32 cmdStatus;
    I_U16 cbcId;
    I_U16 action = 0;
    I_S32 res =0;
    LOG_PRINT(LOG_INFO,"CFG:Got Timer Message");
    gIsTimerRunning = FALSE;
    applTimer = (ApplTimer *) gCfgMsgBuf;
    /*SPR - Start*/
    if(strcmp(applTimer->tmrPayLoad.payLoad,"SYSTEM_STARTUP") == 0)
      StartUpTimerTimeoutHandler();
    /*SPR - End*/
    else if(strcmp(applTimer->tmrPayLoad.payLoad,"BPM_STARTUP") == 0)
      timerTimeoutForBpmCardInfo();  
    else if(strcmp(applTimer->tmrPayLoad.payLoad,"TSI_TRAU_INIT") == 0)
      cfgTimeOutHandler();
    else if(strcmp(applTimer->tmrPayLoad.payLoad,"SCM_CONFIG") == 0)
      scmConfigTimeOutHandler();
    //else if((applTimer->tmrPayLoad.payLoad[0] >= 0) &&  (applTimer->tmrPayLoad.payLoad[0] < 45))
    //   cellObjectHandler();   
    else
    {
      cmdStatus = applTimer->tmrPayLoad.payLoad[0];
      LOG_PRINT(LOG_INFO,"CmdStatus - %d",cmdStatus);  /* CELL_BLOCK - (2), TRX_BLOCK - (1)*/
      /* Trx Block Feature : Starts */         

      switch(cmdStatus)
      {  
        case TRX_BLOCK:
          {
            memcpy(&ptrxId,&(applTimer->tmrPayLoad.payLoad[1]),sizeof(I_U32));
            LOG_PRINT(LOG_INFO,"PtrxId - %d",ptrxId);
            trxObjectHandler();
          }
          break;
          /* Trx Block Feature : Ends */		  
        case CELL_BLOCK :
          {
            memcpy(&cellIndex,&(applTimer->tmrPayLoad.payLoad[1]),sizeof(I_U8));
            LOG_PRINT(LOG_INFO,"CellIndex - %d",cellIndex);
            cellObjectHandler();
          }
          break;  
          /* R.4 changes start */
        case CBS_BIND_RESP :
          {
            memcpy(&cbcId,&(applTimer->tmrPayLoad.payLoad[1]),sizeof(I_U16));
            LOG_PRINT(LOG_INFO,"CbcId - %d",cbcId);
            cbsBindRespTimeOutHandler(cbcId);
          }
          break;
        case CBS_BIND_REPEAT :
          {
            memcpy(&cbcId,&(applTimer->tmrPayLoad.payLoad[1]),sizeof(I_U16));
            LOG_PRINT(LOG_INFO,"CbcId - %d",cbcId);
            cbsBindRepeatTimeOutHandler(cbcId);
          }
          break;

          /*BSC-2.5.5 Diagnostics Changes Start*/
        case DIAG_BPM_RESP :
          {
            if(DIAG_BPM_RESP == gCfgDiagTimerRunning)
            {
              LOG_PRINT(MAJOR,"WaitForBpmDiagResp Timer Expired:: ABORTING Diagnostics");   
              gCfgDiagTimerRunning = DIAG_NO_TIMER_RUNNING;
              abortDiagnostics(TEST_ABORTED); 
            }
            else
            {
              LOG_PRINT(DEBUG,"Unexpected: Diag Bpm Resp Timer Expiry Rcvd");
            }
          }  
          break; 

        case DIAG_INTERVAL :
          {
            if(DIAG_INTERVAL == gCfgDiagTimerRunning)
            {
              LOG_PRINT(DEBUG,"Diag Interval Timer Expired:: sending Diagnostics req to Bpm");   
              gCfgDiagTimerRunning = DIAG_NO_TIMER_RUNNING;
              action = DIAG_CMD_RUN;
              if((res = sendDiagnosticsReqToBpm(action)) == 0)
              {
                gCfgDiagData.repetition--; 
                (*gCfgRepCnt)++; 
                LOG_PRINT(DEBUG,"Value of rep:%d", *gCfgRepCnt);
                startDiagBpmRespTimer();
              } 
            }
            else
            {
              LOG_PRINT(DEBUG,"Unexpected: Diag Interval Timer Expiry Rcvd");
            }
          }
          break; 

        default:
          LOG_PRINT(LOG_INFO,"Unknown Message Received");
      }
    } 
  }

  /* CS4.0 HA Stack Changes */
  /* I_Bool getTimeSlotTableFromLinkCodeAndLinkset(LinkAdminStateTableApi *linkAdminStateTableApiPtr,AbisTimeSlotPerTableApi *currentAbisTimeSlotPerTableApiPtr)
     {
     AbisTimeSlotPerTableApi* timeSlotTableApiPtr=NULL;
     AbisTimeSlotPerTableApi* tempAbisTimeSlotPerTableApiPtr=NULL;   
     I_U32  outRows=0;
     I_U16  outSize=0;
     I_U32 tsUsageEntity=0;
     I_U16 i=0;

     tsUsageEntity =linkAdminStateTableApiPtr->linkAdminlinksetID;
     tsUsageEntity = ((tsUsageEntity<<16 )|
     (linkAdminStateTableApiPtr->linkAdminlinkCode));
     if ( getallTimeSlotTable(&timeSlotTableApiPtr, &outRows,&outSize) == CLIB_SUCCESS )
     {
     for ( i = 0; i < outRows;i++ )
     {
     tempAbisTimeSlotPerTableApiPtr =(AbisTimeSlotPerTableApi*)
     ((I_U8*)timeSlotTableApiPtr + (i *outSize));

     if (tsUsageEntity == tempAbisTimeSlotPerTableApiPtr->usingEntity )
     {
     memcpy(currentAbisTimeSlotPerTableApiPtr,
     tempAbisTimeSlotPerTableApiPtr,sizeof(AbisTimeSlotPerTableApi));
     free( timeSlotTableApiPtr);
     return TRUE;
     }


     }   
     free( timeSlotTableApiPtr);
     return FALSE; 
     }
     else
     {
     LOG_PRINT(LOG_CRITICAL," getallTimeSlotTable failed ");   
     return FALSE; 
     }
     } */

#if 0 /* CS4.0 HA Stack Changes */
  void sendLinkAdminStateTableReqToScm(LinkAdminStateTableApi *LinkAdminStateTableApiPtr)
  {
    BscApiSetLinkAdminStateTable BscApiSetLinkAdminStateTableBuff={0};

    memcpy(&(BscApiSetLinkAdminStateTableBuff.tblObject),
        LinkAdminStateTableApiPtr,sizeof(LinkAdminStateTableApi));
    LOG_PRINT(DEBUG,"Size of Payload LinkAdminStateTableApi = %d", sizeof(LinkAdminStateTableApi));      
    cfgSendCmMessage(&BscApiSetLinkAdminStateTableBuff, 
        sizeof(sCmMsg) + sizeof(LinkAdminStateTableApi), 
        ENT_OAM_OIL, 
        BSC_API_SET_LINKADMINSTATETABLE, 0);
  }
#endif 
  /** SPR - */
  void StartUpTimerTimeoutHandler()
  {
    getDbBssTable();
    if(gDbBssTableApiStorage.adminState == UNLOCKED)
    {
      printf("Invoking initiateBssUnlock function after timer expiry");
      initiateBssUnlock();
    }
  }


  /********************************* Function  Header*****************************
    Function Name   : bichMsgHandler()
Parameters   : None
Return type   : I_Void
Purpose      : Handle messages received from BICH
Other Note   : Added for BSC CS2.2
   *******************************************************************************/
  I_Void bichMsgHandler()
  {
    OamsBichCfgDelBicResp*                oamsBichCfgDelBicResp =
      (OamsBichCfgDelBicResp* )(gCfgMsgBuf );
    OamsBichCfgAddBicResp*                oamsBichCfgAddBicResp =
      (OamsBichCfgAddBicResp* )(gCfgMsgBuf );
    OamsBichCfgLockResp*                  oamsBichCfgLockResp =
      (OamsBichCfgLockResp* )(gCfgMsgBuf );
    OamsBichCfgUnlockResp*                oamsBichCfgUnlockResp =
      (OamsBichCfgUnlockResp* )(gCfgMsgBuf );
    BicTableIndices                       bicTableIndices;
    BicTableApi*                          bicTableApiPtr = NULL;
    BicTrxTimeslotUsageTableIndices       bicTrxTimeslotUsageTableIndices;
    I_S32                                 dbStatus = -1, status = CFG_FAILURE;
    I_U32                                 tsUser = ZERO, index = ZERO, i = ZERO;
    I_U8                                  chasisFrameId;
    I_U8                                  slotId;
    I_U32                                 outRow=ZERO;
    I_U16                                 outsz=ZERO;


    LOG_PRINT(LOG_INFO,"Entering Function : bichMsgHandler");

    switch(((SysHdr*) gCfgMsgBuf)->msgType)
    {
      case OAMS_BICH_CFG_ADD_BIC_RESP : 
        {
          /* Check add BIC Response status */
          LOG_PRINT(LOG_INFO,"bichMsgHandler : Received Msg : OAMS_BICH_CFG_ADD_BIC_RESP");
          LOG_PRINT(LOG_DEBUG,"bichMsgHandler : Received BicId : %d",oamsBichCfgAddBicResp->bicId);
          if(OAMS_RSLT_SUCCESS != oamsBichCfgAddBicResp->result)
          {
            /* Add BIC operation failed */
            LOG_PRINT(LOG_CRITICAL,"bichMsgHandler : Add BIC Opreration Failed at BICH due to Cause : %d",
                oamsBichCfgAddBicResp->cause);
          }
          else
          {
            gSentAddBicReqAtInitNum--;

            if(CFG_READY == gCfgState || gCfgState == CFG_BPM_SW_QUERY)
            {
              /* Changes For R2.2 :Start */
              bicTableIndices.bicId  = oamsBichCfgAddBicResp->bicId;
              if( ( getBicTable(&bicTableIndices, &bicTableApiPtr) ) != CLIB_SUCCESS)
              {
                LOG_PRINT(LOG_INFO,"addConfiguredBics : Bic Not Configured \
                    in BicTable for Bic Id =%d",
                    oamsBichCfgAddBicResp->bicId);
              }
              else
              {
                if((bicTableApiPtr->btsType !=R3_BTS)&& (bicTableApiPtr->btsType !=R2_BTS_IP)&& 
                    (bicTableApiPtr->btsConnectivityState  == BTS_CONNECT) )/* R2.8 Changes */
                {
                  LOG_PRINT(LOG_INFO,"addConfiguredBics :BIC is in \
                      Connect state send  switching \
                      for Bic Id =%d",
                      oamsBichCfgAddBicResp->bicId);

                  if(CFG_FAILURE == prepAndSndSwitchConForBic
                      (oamsBichCfgAddBicResp->e1Id,
                       oamsBichCfgAddBicResp->e1Ts) )
                  {
                    LOG_PRINT(LOG_MAJOR,"addConfiguredBics :Switch\
                        Disconnect Failed");
                  }
                  else
                  {  
                    getIndex(oamsBichCfgAddBicResp->bicId,&index);
                    gBtsData[index].connectivityState = 
                      connectInProgress;
                  }
                }
                free(bicTableApiPtr);
                /* Changes For R2.2 :End */
              }
            }
            else if((ZERO == gSentAddBicReqAtInitNum) && 
                (FALSE == gMgsOprSts)
                )
            {
              /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
              sndSwitchConForBicsAtInit(); 
              if(gCfgStandbyToActive == I_TRUE)
              { 
                sndSwitchConForTrxsAtSwitchOver();
              }
              /*BSC R2.0 Changes Starts*/ 
              sendRequestForAvailableReleases(); 
              gCfgState = CFG_BPM_SW_QUERY;
              LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
              /*BSC R2.0 Changes Ends*/ 

              /* CS3.0 Changes : Start */
              /* goToReadyState(); */
              //if(gCfgState == CFG_START_TRAU)
              //{
              //   sendRequestForAvailableReleases(); 
              //   gCfgState = CFG_BPM_SW_QUERY;
              //   LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
              //}
              /* CS3.0 Changes : End */
            }
          }
          break;
        }
      case OAMS_BICH_CFG_DEL_BIC_RESP :
        {  

          ApplTeiPoolTableSecIndices          applTeiPoolTableSecIndices;
          ApplTeiPoolTableApi*                applTeiPoolTableOutData =PNULL;
          ApplTeiPoolTableApi*                applTeiPoolTable1 =PNULL;
          BicE1TeiMapTableApi*                bicE1TeiPtr=PNULL;
          BicE1TeiMapTableApi*                bicE1TeiPtr1=PNULL;
          BicE1TeiMapTableIndices             bicE1TeiInData;
          I_U32 e1Id = ZERO, e1Ts = ZERO,index = ZERO;
          LOG_PRINT(LOG_INFO,"bichMsgHandler : Received Msg : OAMS_BICH_CFG_DEL_BIC_RESP");
          LOG_PRINT(LOG_DEBUG,"bichMsgHandler : Received BicId : %d",oamsBichCfgDelBicResp->bicId);
          /* Check if status received is SUCCESS then send ACK to OMC/CLI else 
           * send NACK to OMC/CLI */
          if(OAMS_RSLT_SUCCESS != oamsBichCfgDelBicResp->result)
          {
            /* Delete BIC operation failed */
            LOG_PRINT(LOG_INFO,"bichMsgHandler : Delete BIC Opreration Failed \
                at BICH due to Cause : %d",oamsBichCfgDelBicResp->cause);
            cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
          }
          else
          {
            /*Changes For R2.2 :Start */
            if(getIndex(oamsBichCfgDelBicResp->bicId,&index) == CFG_FAILURE)
            {
              LOG_PRINT(LOG_INFO,"bichMsgHandler : Delete BIC Opreration Failed \
                  at BICH due to Cause : %d",oamsBichCfgDelBicResp->cause);
              cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
              return;  
            }

            if( (gBtsData[index].btsType!=R3_BTS)&& (gBtsData[index].btsType!=R2_BTS_IP) )
            {/*Changes for R2.8 starts*/
              if (gBtsData[index].btsType == BIC)
                tsUser =  TS_USAGE_BIC;
              else if(gBtsData[index].btsType == R2_BTS)
                tsUser =  TS_USAGE_BTS;

              status = getE1TsFromBicTrxTimeslotUsageTable(tsUser, 
                  oamsBichCfgDelBicResp->bicId, &e1Id, &e1Ts);
              if(CFG_FAILURE == status)
              {
                cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
                break;
              }
              /* Send Switch Disconnect to GRHM */
              if(CFG_FAILURE == prepAndSndSwitchDisConForBic(e1Id,e1Ts) )
              {
                LOG_PRINT(LOG_MAJOR,"bichMsgHandler :Switch Disconnect Send Failed");
                cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
                return;
              }
              /* Update Row in AbisTimeSlotPerTable  */
#if 0
              abisTimeSlotPerTableIndicesPtr.e1Num = e1Id;  
              abisTimeSlotPerTableIndicesPtr.tsNum = e1Ts;
              dbStatus = getAbisTimeSlotPerTable(&abisTimeSlotPerTableIndicesPtr,&abisTimeSlotPerTablePtr);
              if(DBLIB_SUCCESS != dbStatus)
              {
                LOG_PRINT(LOG_INFO,"bichMsgHandler : Get Operation Failed for AbisTimeSlotTable");
                cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
                return;
              }
              memcpy(&abisTimeSlotPerTableStruct,abisTimeSlotPerTablePtr,sizeof(AbisTimeSlotPerTableApi));
              free(abisTimeSlotPerTablePtr);
#endif
              dbStatus = updateRowAbisTimeSlotPerTable(e1Id, e1Ts, SYS_TS_USAGE_ABIS_FREE);
              if(DBLIB_SUCCESS != dbStatus)
              {
                LOG_PRINT(LOG_INFO,"addBicTableHandler : AbisTimeSlotTable Updated in Db failed");
                cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
                return;
              }

              /*BSC R2.0 Changes Starts*/ 
              /*Mark MccLinkResource Free*/
              dbStatus=freeMccLinkResourceTablebyExternalE1Ts(e1Id,e1Ts,INVALID_E1,INVALID_TS,SYS_TS_FREE);
              if(DBLIB_SUCCESS != dbStatus)
              {
                LOG_PRINT(LOG_MAJOR,"Db wrapper freeMccLinkResourceTablebyExternalE1Ts Fails");
                cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
                return;
              } 

              dbStatus =getAllTerBicTeiMapTable(e1Id,e1Ts,&bicE1TeiPtr);
              if(DBLIB_SUCCESS != dbStatus)
              {
                LOG_PRINT(LOG_MAJOR,"Db wrapper getAllTerBicTeiMapTable Failed with err %d for E1Id %d,E1 TS %d",dbStatus,e1Id,e1Ts);
                cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
                return;
              }  
              bicE1TeiPtr1=(BicE1TeiMapTableApi*)((I_U8 *)bicE1TeiPtr);
              bicE1TeiInData.bicTei=bicE1TeiPtr1->bicTei;  
              dbStatus = deleteBicE1TeiMapTable(&bicE1TeiInData);
              if(DBLIB_SUCCESS != dbStatus)
              {
                LOG_PRINT(LOG_MAJOR,"Db call deleteBicE1TeiMapTable Failed with err %d for BicTei %d",                  dbStatus,bicE1TeiInData.bicTei);
                cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
                if(bicE1TeiPtr!=NULL)
                  free(bicE1TeiPtr);  
                return;
              }
              if(bicE1TeiPtr!=NULL)
                free(bicE1TeiPtr);  

              /*BSC R2.0 Changes Ends*/ 

              /* Deleting Row From BicTrxTimeslotUsageTable */
              bicTrxTimeslotUsageTableIndices.tsUser = tsUser;
              bicTrxTimeslotUsageTableIndices.bicOrTrxId = oamsBichCfgDelBicResp->bicId;
              dbStatus = deleteBicTrxTimeslotUsageTable(&bicTrxTimeslotUsageTableIndices);
              if(DBLIB_SUCCESS != dbStatus)
              {
                LOG_PRINT(LOG_INFO,"bichMsgHandler : Delete Operation Failed for BicTrxTimeslotUsageTable");
                cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
                break;
              }

            }/*Changes for R2.8 Ends*/   
            if ( ( dbStatus = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
            {
              LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",dbStatus);
              cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
              return;
            }
            LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
            SwMNodeTableIndices swMNodeTableIndex;
            if (gBtsData[index].btsType == BIC)
              swMNodeTableIndex.nodeType = SYS_NODE_TYPE_BIC;
            else if(gBtsData[index].btsType == R2_BTS)
              swMNodeTableIndex.nodeType = SYS_NODE_TYPE_R2_BTS;
            else if(gBtsData[index].btsType == R3_BTS)
              swMNodeTableIndex.nodeType = SYS_NODE_TYPE_R3_BTS;
            else if(gBtsData[index].btsType == R2_BTS_IP)
              swMNodeTableIndex.nodeType = SYS_NODE_TYPE_R2_BTS_IP;
            swMNodeTableIndex.nodeIdentity = oamsBichCfgDelBicResp->bicId;
            swMNodeTableIndex.chasisFrameId = chasisFrameId;
            swMNodeTableIndex.slotId = slotId;
            if(deleteSwMNodeTable(&swMNodeTableIndex) != CLIB_SUCCESS)
            {
              LOG_PRINT(LOG_MAJOR,"deleteSwMNodeTable DB call is geting Failed");
              cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
              return ;
            }
            else
            {
              LOG_PRINT(LOG_INFO,"deleteSwMNodeTable Successfull");
            }

            /* Deleting Row From BicTable */
            bicTableIndices.bicId = oamsBichCfgDelBicResp->bicId;
            dbStatus = deleteBicTable(&bicTableIndices);
            if(DBLIB_SUCCESS != dbStatus)
            {
              LOG_PRINT(LOG_INFO,"bichMsgHandler : Delete Operation Failed for BicTable");
              cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
              return ;
            }
            else
            {
              if( (gBtsData[index].btsType==R3_BTS)||(gBtsData[index].btsType==R2_BTS_IP) )
              {
                applTeiPoolTableSecIndices.applTeiUser=(I_U8)TEI_USR_BTS;
                applTeiPoolTableSecIndices.userId=oamsBichCfgDelBicResp->bicId;  
                LOG_PRINT(LOG_INFO,"Veena *** TeiUser %d userId %d",applTeiPoolTableSecIndices.applTeiUser, applTeiPoolTableSecIndices.userId);
                dbStatus = getSecApplTeiPoolTable(&applTeiPoolTableSecIndices, &applTeiPoolTableOutData,
                    &outRow, &outsz);
                if(DBLIB_SUCCESS != dbStatus)
                {
                  LOG_PRINT(LOG_MAJOR,"addConfiguredBics: Get appTei failed for Bic Id %d btsType %d"                    ,oamsBichCfgDelBicResp->bicId,gBtsData[index].btsType);
                }
                else
                {  
                  applTeiPoolTable1=(ApplTeiPoolTableApi*)((I_U8 *)applTeiPoolTableOutData);
                  dbStatus=deAllocateApplTei((I_U16)applTeiPoolTable1->applTei);
                  bicE1TeiInData.bicTei=(I_U32)applTeiPoolTable1->applTei;  
                  dbStatus = deleteBicE1TeiMapTable(&bicE1TeiInData);
                  if(DBLIB_SUCCESS != dbStatus)
                  {
                    LOG_PRINT(LOG_MAJOR,"Db call deleteBicE1TeiMapTable Failed with err %d for BicTei %d",                  dbStatus,bicE1TeiInData.bicTei);
                  }
                  if(applTeiPoolTableOutData!=NULL)
                    free(applTeiPoolTableOutData);
                }
              }  
              gBtsData[index].BTSID = INVALID_BTS;
              gBtsData[index].btsState = none;
              gBtsData[index].btsType = ZERO;
              gBtsData[index].connectivityState = none;
              cfgSendAckToCm();
            }
            /*Changes For R2.2 :End */
          }
          break;
        }
      case OAMS_BICH_CFG_ALARM_IND:    
        {
          LOG_PRINT(LOG_INFO,"bichMsgHandler : Received Msg : OAMS_BICH_CFG_ALARM_IND");   
          cfgAlarmHandler(); 
          break;             
        }
      case OAMS_BICH_CFG_LOCK_RESP:
        {
          LOG_PRINT(LOG_INFO,"bichMsgHandler : Received Msg : OAMS_BICH_CFG_LOCK_RESP");   
          if(OAMS_RSLT_SUCCESS != oamsBichCfgLockResp->result)
          {
            /* Delete BIC operation failed */
            LOG_PRINT(LOG_INFO,"bichMsgHandler : Lock BIC Opreration Failed \
                at BICH due to Cause : %d",oamsBichCfgLockResp->cause);
            if (getIndex(oamsBichCfgLockResp->bicId,&i) != CFG_FAILURE )
            {
              gBtsData[i].btsState = unlocked;
            }

          }
          else
          {     
            updateStateAndSendBicLockAlarm(oamsBichCfgLockResp->bicId);
          }
          break;             
        }
      case OAMS_BICH_CFG_UNLOCK_RESP:
        {
          LOG_PRINT(LOG_INFO,"bichMsgHandler : Received Msg : OAMS_BICH_CFG_UNLOCK_RESP");
          if(OAMS_RSLT_SUCCESS != oamsBichCfgUnlockResp->result)
          {
            /* Delete BIC operation failed */
            LOG_PRINT(LOG_INFO,"bichMsgHandler : Unlock BIC Opreration Failed \
                at BICH due to Cause : %d",oamsBichCfgUnlockResp->cause);
            if (getIndex(oamsBichCfgLockResp->bicId,&i) != CFG_FAILURE )
            {
              gBtsData[i].btsState = locked;
            }

          }
          else
          {   
            updateStateAndSendBicUnlockAlarm(oamsBichCfgUnlockResp->bicId);  
          } 
          break;             
        }
      default :
        {
          LOG_PRINT(LOG_INFO,"bichMsgHandler : Unknown Msg Received From BICH");
        }
    }

    LOG_PRINT(LOG_INFO,"Exiting Function : bichMsgHandler");
  }

  /*CS3.0 changes : Start */
  void swmhMsgHandler()
  {
    switch (((SysHdr*) gCfgMsgBuf)->msgType)
    {
      case OAMS_SWMH_CFG_SW_DNLD_ACK:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_SW_DNLD_ACK from Swmh..");
        swDownloadSuccessHandler();
        break;
      case OAMS_SWMH_CFG_SW_DNLD_NACK:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_SW_DNLD_NACK from Swmh..");
        swDownloadFailureHandler();
        break;
      case OAMS_SWMH_CFG_SW_ACT_ACK:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_SW_ACT_ACK from Swmh..");
        swActivationSuccessHandler();
        break;
      case OAMS_SWMH_CFG_SW_ACT_NACK:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_SW_ACT_NACK from Swmh..");
        swActivationFailureHandler();
        break;
      case OAMS_SWMH_CFG_ALARM_IND:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_ALARM_IND from Swmh..");
        cfgAlarmHandler();
        break;
      case OAMS_SWMH_CFG_SW_INSTALL_ACK:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_SW_INSTALL_ACK from Swmh..");
        swInstallAckHandler();
        break;
      case OAMS_SWMH_CFG_SW_INSTALL_NACK:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_SW_INSTALL_NACK from Swmh..");
        swInstallNackHandler();
        break;
      case OAMS_SWMH_CFG_SW_INSTALL_SUCCESS:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_SW_INSTALL_SUCCESS from Swmh..");
        swInstallSuccessHandler();
        break;
      case OAMS_SWMH_CFG_SW_INSTALL_FAILURE:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_SW_INSTALL_FAILURE from Swmh..");
        swInstallFailureHandler();
        break;
      case OAMS_SWMH_CFG_CV_ACT_NACK:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_SW_ACT_NACK from Swmh..");
        cvActivationNackHandler();
        break;
      case OAMS_SWMH_CFG_CV_STATUS_REPORT:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_CV_STATUS_REPORT from Swmh..");
        cvActivationStatusReport();
        break;
      case OAMS_SWMH_CFG_CV_COMMIT_IND:
        LOG_PRINT(LOG_INFO,"Recieved OAMS_SWMH_CFG_SW_ACT_ACK from Swmh..");
        cvActivationCommitInd();
        break;
      default :
        break;
    }
  }  /* swmhMsgHandler */

  void mrhmMsgHandler()
  {

    switch (((SysHdr*) gCfgMsgBuf)->msgType)
    {
      case CSAPP_MRHM_CFG_ALARM_IND:
        {
          cfgAlarmHandler();
          break;
        }
      default:
        break;
    }
  }

  /*Change PCU R2.5 Aricent -- START*/
  /********************************* Function  Header*****************************
    Function Name   : gbhMsgHandler()
Parameters      :
Return type     : void
Purpose         : It handles the messaged received from GBH.
Other Note      : 
   ********************************************************************************/
  void gbhMsgHandler()
  {
    switch (((SysHdr*) gCfgMsgBuf)->msgType)
    {
      case OAMS_GBH_CFG_ALARM_IND:
        cfgAlarmHandler();
        break;
      default:
        break;
    }

  }



  /********************************* Function  Header*****************************
    Function Name   : pschMsgHandler()
Parameters      :
Return type     : void
Purpose         : It handles the messaged received from PSCH.
Other Note      : 
   ********************************************************************************/
  void pschMsgHandler()
  {
    //Merger for Mantis #31470
    I_U32 i;
    CellPerTableIndices cellPerTableIndices;
    CellPerTableApi *pCellTab;
    GbInterfaceTableApi* gbIfTblApiPtr = PNULL;
    I_S32  ret = CM_FAILURE;
    I_U32 outRows = 0;
    I_U16 outSize = 0;
    //Merger for Mantis #31470
    switch (((SysHdr*) gCfgMsgBuf)->msgType)
    {
      /* call cellObjectHandler in following two cases */
      case OAMS_PSCH_CFG_UNLOCK_RESP:
      case OAMS_PSCH_CFG_LOCK_RESP:
        cellObjectHandler();
        break;
    //Merger for Mantis #31470
      case OAMS_PSCH_CFG_NSE_UNLOCK_RESP:
	  {
        LOG_PRINT(LOG_INFO,"Received OAMS_PSCH_CFG_NSE_UNLOCK_RESP from PSCH.");   
         //Commented for Mantis #31633 & #31634 & #31639
     /*    for ( i = 0; i < CFG_MAX_NUM_CELLS;i++ )
		 {
            if ( (gCellData[i].Availlability == I_FALSE) && (gCellData[i].adminState == UNLOCKED) )
            {
               cellPerTableIndices.cellId = gCellData[i].CellID;
               cellPerTableIndices.lac = gCellData[i].lac;
               if(getCellPerTable(&cellPerTableIndices,&pCellTab) == CLIB_SUCCESS)
               {
                  if ((PS_ALLOWED == pCellTab->psAllowed) && 
                      (ENABLED == gDbBssTableApiStorage.gprsEnabled) )
                  {
                     updateCellDataStruct(pCellTab->cellId, pCellTab->lac, 
                                unlockedEnabled, OAMS_RSN_PARENTOBJECTUNLOCKED);
                  }
               }
            }
		 }*/
     //Commented for Mantis #31633 & #31634 #31639
         gNseiData.nseiState = unlocked;
         gNseLockUnlockProc = I_FALSE;
		 ret = getallGbInterfaceTable(&gbIfTblApiPtr, &outRows, &outSize);
         if (ret == DBLIBERR_PTOPAGE_HAS_NO_ROWS)
         {
            LOG_PRINT(LOG_MAJOR, "No rows present in gb Interface Table, sending Nack");
         }
		 else
		 {
		    gbIfTblApiPtr->adminState = UNLOCKED;
            ret = updateGbInterfaceTable(gbIfTblApiPtr);
            if (ret == CLIB_SUCCESS)      
            {
                LOG_PRINT(LOG_INFO,"Update DB Successful");
		    }
			sendNseLockUnlockAlarm (gbIfTblApiPtr->nsei,gbIfTblApiPtr->adminState);
			free (gbIfTblApiPtr);
		 }
	     break;	  
	  }
	  case OAMS_PSCH_CFG_NSE_LOCK_RESP:
	  {	  
         LOG_PRINT(LOG_INFO,"Received OAMS_PSCH_CFG_NSE_LOCK_RESP from PSCH.");   
         //Commented for Mantis #31633 & #31634 & #31639
     /*    for ( i = 0; i < CFG_MAX_NUM_CELLS;i++ )
		 {
            if ( (gCellData[i].Availlability == I_FALSE) && (gCellData[i].adminState == UNLOCKED) )
            {
               cellPerTableIndices.cellId = gCellData[i].CellID;
               cellPerTableIndices.lac = gCellData[i].lac;
               if(getCellPerTable(&cellPerTableIndices,&pCellTab) == CLIB_SUCCESS)
               {
                  if ((PS_ALLOWED == pCellTab->psAllowed) && 
                      (ENABLED == gDbBssTableApiStorage.gprsEnabled) )
                  {
        							*Commented for Mantis #31633 & 31634 & #31639*/
                     /*updateCellDataStruct(pCellTab->cellId, pCellTab->lac, 
                                unlockedDisabled, OAMS_RSN_PARENTOBJECTLOCKED);*
        						 *Commented for Mantis #31633 & 31634 & #31639*
                  }
               }
            }
		 }*/
         sendPsscmLockReq(OAMS_RSN_OPERATORINITIATED);
		 break;
	  }
    //Merger for Mantis #31470
      case OAMS_PSCH_CFG_ALARM_IND:
        cfgAlarmHandler();
        break;
      default:
        break; 
    } 
  }
  /*Change PCU R2.5 Aricent -- END*/


  /********************************* Function  Header*****************************
    Function Name   : sendTrauUlStatusUpdateReq()
Parameters       : I_U16   trauChannelId,I_U32   action
Return type       : I_Void
Purpose          : It sends message to PDC to update when action field in the
TrauULStatus table is updated.
Other Note        : Added For BSC CS3.0
   *******************************************************************************/
  I_Void sendTrauUlStatusUpdateReq(I_U16 trauChannelId,I_U32 action)
  {
    CfgPdcTrauUlFrameStatus oamsCfgTrauULFrameStatus;

    LOG_PRINT(LOG_INFO,"Entering Function : sendTrauUlStatusUpdateReq");
    LOG_PRINT(LOG_DEBUG,"sendTrauUlStatusUpdateReq :trauChannelId(%d),action(%d)", trauChannelId,action);

    /* Prepare & Send Trau UL update request to PDC */
    oamsCfgTrauULFrameStatus.trauChannelId = trauChannelId;
    oamsCfgTrauULFrameStatus.action = action;
    cfgSendMessage(&oamsCfgTrauULFrameStatus, sizeof(oamsCfgTrauULFrameStatus),
        ENT_OAM_PDC,OAMS_CFG_PDC_TRAU_UL_FRAMESTATUS, 0);
    LOG_PRINT(LOG_INFO,"Exiting Function : sendTrauUlStatusUpdateReq");
  }


  /********************************* Function  Header********************************
    Function Name:       updateTrauUlFrameStatus()
Parameters:          void
Return type:         void
Purpose:             To update the action field of the TrauUlFrameStatus table
Other Note:          Added for CS3.0
   ************************************************************************************/
  void updateTrauUlFrameStatus()
  {
    TrauUlFrameStatusTableApi* receivedMsgPtr = NULL;
    I_S32 dbStatus = -1;
    //I_S32 retVal = CFG_FAILURE;
    TrauUlFrameStatusTableApi* trauUlFrameStatusTablePtr = NULL;
    TrauUlFrameStatusTableIndices trauUlFrameStatusTableInd;

    receivedMsgPtr = ( TrauUlFrameStatusTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
    LOG_PRINT(LOG_INFO," In updateTrauUlFrameStatus");

    trauUlFrameStatusTableInd.dummyIndex = receivedMsgPtr->dummyIndex;

    dbStatus = getTrauUlFrameStatusTable(&trauUlFrameStatusTableInd, &trauUlFrameStatusTablePtr);
    if(DBLIB_SUCCESS != dbStatus)
    {
      LOG_PRINT(LOG_INFO,"getTrauUlFrameStatusTable : Get on Table TrauUlFrameStatusTable Failed");
      if(trauUlFrameStatusTablePtr != NULL)
        free(trauUlFrameStatusTablePtr);
      return;
    }
    else
    {
      /* check for matching channel id */
      if(receivedMsgPtr->trauChannelId != trauUlFrameStatusTablePtr->trauChannelId)
      {
        if(trauUlFrameStatusTablePtr->action == TRAU_MON_STOP && receivedMsgPtr->action == TRAU_MON_START)
        {
          dbStatus = -1;
          /* update the db with the new value for the action field */
          trauUlFrameStatusTablePtr->action = receivedMsgPtr->action;
          trauUlFrameStatusTablePtr->trauChannelId = receivedMsgPtr->trauChannelId;
          dbStatus = updateTrauUlFrameStatusTable( trauUlFrameStatusTablePtr);
          if(DBLIB_SUCCESS != dbStatus)
          {
            LOG_PRINT(LOG_INFO,"updateTrauUlFrameStatusTable : Update on Table TrauUlFrameStatusTable Failed");
            return;
          }
          else
          {
            sendTrauUlStatusUpdateReq(trauUlFrameStatusTablePtr->trauChannelId,trauUlFrameStatusTablePtr->action);
            LOG_PRINT(LOG_INFO,"updateTrauUlFrameStatus:DB update successfully and msg sent to PDC, sending Ack");
            cfgSendAckToCm();
          }
        }
        else
        {
          cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
          return;
        }
      }
      else
      {
        /* if the value in the action field is same in the db and the received request */
        /* then send nack */
        if(receivedMsgPtr->action == trauUlFrameStatusTablePtr->action)
        {
          LOG_PRINT(LOG_INFO,"updateTrauUlFrameStatus:Received action request and entry in DB is same = %d ",receivedMsgPtr->action);
          cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
          return;
        }
        dbStatus = -1;
        /* update the db with the new value for the action field */
        trauUlFrameStatusTablePtr->action = receivedMsgPtr->action;
        dbStatus = updateTrauUlFrameStatusTable( trauUlFrameStatusTablePtr);
        if(DBLIB_SUCCESS != dbStatus)
        {
          LOG_PRINT(LOG_INFO,"updateTrauUlFrameStatusTable : Update on Table TrauUlFrameStatusTable Failed");
          return;
        }
        /* prepare and send message to PDC */
        sendTrauUlStatusUpdateReq(trauUlFrameStatusTablePtr->trauChannelId,trauUlFrameStatusTablePtr->action);
        LOG_PRINT(LOG_INFO,"updateTrauUlFrameStatus:DB update successfully and msg sent to PDC, sending Ack");
        cfgSendAckToCm();
        free(trauUlFrameStatusTablePtr);
      }
    }
  }

  /*CS3.0 changes : End */


  /*BSC CS4.0 : Init changes start*/

  /********************************* Function  Header********************************
    Function Name:       updateSystemTypeDetails()
Parameters:          void
Return type:         void
Purpose:             To update the System Type Details in SystemTypeTable
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/
#if 0
  I_Void updateSystemTypeDetails()
  {
    OamOilCfgSystemTypeDetails *oamOilCfgSystemTypeDetailsPtr = NULL;
    SystemTypeTableApi systemTypeTable;
    LOG_PRINT(LOG_INFO,"updateSystemTypeDetails:Entering in Function");
    oamOilCfgSystemTypeDetailsPtr = (OamOilCfgSystemTypeDetails* )((I_U8 *)gCfgMsgBuf );
    systemTypeTable.systemType = oamOilCfgSystemTypeDetailsPtr->systemType;
    if(insertSystemTypeTable(&systemTypeTable) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"updateSystemTypeDetails: Initialization Failed....SystemType Details can not be updated!!!");
      return;
    }
    LOG_PRINT(LOG_INFO,"updateSystemTypeDetails:Exiting from Function");
  }

#endif
  /********************************* Function  Header********************************
    Function Name:       updateChasisFrameDetails()
Parameters:          void
Return type:         void
Purpose:             To update the Chasis Frame Details in ChasisFrameTable
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/
#if 0
  I_Void updateChasisFrameDetails()
  {
    OamOilCfgChasisFrameDetails *oamOilCfgChasisFrameDetailsPtr = NULL;
    ChasisFrameIdTableApi chasisFrameIdTable ;
    LOG_PRINT(LOG_INFO,"updateChasisFrameDetails:Entering in Function");
    oamOilCfgChasisFrameDetailsPtr = (OamOilCfgChasisFrameDetails *)((I_U8 *)gCfgMsgBuf);
    chasisFrameIdTable.chasisFrameId = oamOilCfgChasisFrameDetailsPtr->chasisFrameId;
    chasisFrameIdTable.totalNumCards = oamOilCfgChasisFrameDetailsPtr->totalNumCards;
    chasisFrameIdTable.totalNumRemoteCards = oamOilCfgChasisFrameDetailsPtr->numRemoteCards;
    if(insertChasisFrameIdTable(&chasisFrameIdTable) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"updateChasisFrameDetails: Initialization Failed....ChasisFrame Details can not be updated!!!");
      return;
    }

    LOG_PRINT(LOG_INFO,"updateChasisFrameDetails:Exiting from Function");

  }
#endif
  /********************************* Function  Header********************************
    Function Name:       updateSystemClockDetails()
Parameters:          void
Return type:         void
Purpose:             To update the System Clock Details in SystemClockInfoTable
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/
  I_Void updateSystemClockDetails()
  {
    OamOilCfgSystemClockDetails *oamOilCfgSystemClockDetailsPtr = NULL;
    I_U8 slotId;
    I_U8 chasisFrameId;
    I_U32 outRow  = 0;
    I_U16 outSize = 0;
    SystemClkInfoTableApi systemClockInfoTableApi;
    SystemClkInfoTableApi *clkInfoTblPtr;
    //ClkSourceConfigTableApi *clkSrcCfgTableApiDbPtr;   
    ClkSourceConfigStatusTableIndices clkSrcCfg;
    ClkSourceConfigStatusTableApi *outData;

    LOG_PRINT(LOG_INFO,"updateSystemClockDetails: Entering in Function");

    if ( INFO_CLOCK_CHANGE_PM_OAM == (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->sysalarmId) {
      LOG_PRINT( LOG_DEBUG,"INFO_CLOCK_CHANGE_PM_OAM: ChassisFrameId[%d] Slot[%d] Ref[%d] TrunkPort[%d]",
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key1,
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2,
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key3,
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4
          );   
      if( ((( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key3 == REFERENCE_INTERNAL_CLK)
          &&
          (getallSystemClkInfoTable(&clkInfoTblPtr, &outRow, &outSize) == CLIB_SUCCESS) )
      {
        if(clkInfoTblPtr->clkReference == REFERENCE_EXTERNAL_CLK)
        {
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2 = clkInfoTblPtr->slotId;
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4 = clkInfoTblPtr->trunkPortId;
        } 
        free(clkInfoTblPtr); 
      }

      systemClockInfoTableApi.chasisFrameId  = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key1;
      systemClockInfoTableApi.slotId         = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2;
      systemClockInfoTableApi.clkReference   = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key3;
      systemClockInfoTableApi.trunkPortId    = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4;
      /*Mantis 6125 Fix - Gaurav Bhatnagar*/
      if(systemClockInfoTableApi.clkReference == REFERENCE_INTERNAL_CLK)
      {
        LOG_PRINT(LOG_DEBUG,"updateSystemClockDetails: ClockSource is Internal");
        systemClockInfoTableApi.chasisFrameId = 0xFF;
        systemClockInfoTableApi.slotId = 0xFF;
        /*Mantis 6751 Fix - Gaurav Bhatnagar*/
        systemClockInfoTableApi.trunkPortId = INVALID_TRUNK_ID ;
      }

      /*Fixed Mantis 6164/6424 by Gaurav Bhatnagar/BB 10-04-09::18:05*/
      systemClockInfoTableApi.index = 0 ;
      if(updateSystemClkInfoTable(&systemClockInfoTableApi) != CLIB_SUCCESS)
      {
        if(insertSystemClkInfoTable(&systemClockInfoTableApi) != CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_CRITICAL,"updateSystemClockDetails: Initialization Failed....SystemClock Details can not be updated!!!");
          return;
        }
      }
    }
    else if ( INFO_CLOCK_FAIL_PM_OAM == (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->sysalarmId)
    {
      LOG_PRINT( LOG_DEBUG,"INFO_CLOCK_FAIL_PM_OAM: ChassisFrameId[%d] Slot[%d] Ref[%d] TrunkPort[%d]",
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key1,
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2,
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key3,
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4
          );   

      systemClockInfoTableApi.chasisFrameId  = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key1;
      systemClockInfoTableApi.slotId         = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2;
      systemClockInfoTableApi.clkReference   = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key3;
      systemClockInfoTableApi.trunkPortId    = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4;
      /*BSC R2.3 Clock Changes Starts*/ 
      clkSrcCfg.chasisFrameId = (I_U8)(( SysAlarm*)(gCfgMsgBuf+sizeof(SysHdr)))->key1;
      clkSrcCfg.slotId = (I_U8)(( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2;
      clkSrcCfg.trunkPortId = (I_U16)(( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4;
      LOG_PRINT(DEBUG,"Going to get ClkSrcCfgSts for frame:%d,slot:%d,port:%d",
          clkSrcCfg.chasisFrameId,clkSrcCfg.slotId,clkSrcCfg.trunkPortId);
      if(CLIB_SUCCESS == getClkSourceConfigStatusTable(&clkSrcCfg,&outData))
      {
        if( outData->clkConfigStatus != PENDING) 
        {
          outData->clkConfigStatus = PENDING;
          updateClkSourceConfigStatusTable(outData);
          sendClkSourcePendingAlarm(outData->chasisFrameId,outData->slotId,
              outData->trunkPortId,ZERO);
        }
        free(outData);
      }
      /*BSC R2.3 Clock Changes Ends*/ 
    }
    else if ( INFO_CLOCK_RECOVERED_PM_OAM == (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->sysalarmId) {
      LOG_PRINT( LOG_DEBUG,"INFO_CLOCK_RECOVERED_PM_OAM: ChassisFrameId[%d] Slot[%d] Ref[%d] TrunkPort[%d]",
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key1,
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2,
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key3,
          (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4
          );   

      systemClockInfoTableApi.chasisFrameId  = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key1;
      systemClockInfoTableApi.slotId         = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2;
      systemClockInfoTableApi.clkReference   = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key3;
      systemClockInfoTableApi.trunkPortId    = (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4;
      /*BSC R2.3 Clock Changes Starts*/ 
      clkSrcCfg.chasisFrameId = (I_U8)(( SysAlarm*)(gCfgMsgBuf+sizeof(SysHdr)))->key1;
      clkSrcCfg.slotId = (I_U8)(( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key2;
      clkSrcCfg.trunkPortId = (I_U16)(( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)))->key4;
      LOG_PRINT(DEBUG,"Going to get ClkSrcCfgSts for frame:%d,slot:%d,port:%d",
          clkSrcCfg.chasisFrameId,clkSrcCfg.slotId,clkSrcCfg.trunkPortId);
      if(CLIB_SUCCESS == getClkSourceConfigStatusTable(&clkSrcCfg,&outData))
      {
        if( outData->clkConfigStatus != APPLIED) 
        {
          outData->clkConfigStatus = APPLIED;
          updateClkSourceConfigStatusTable(outData);
          sendClkSourceAppliedAlarm(outData->chasisFrameId,outData->slotId,
              outData->trunkPortId,ZERO);
        }
        free(outData);
      }
      /*BSC R2.3 Clock Changes Ends*/ 
    }
    else
    {
      oamOilCfgSystemClockDetailsPtr = (OamOilCfgSystemClockDetails *)((I_U8 *)gCfgMsgBuf);
      if(oamOilCfgSystemClockDetailsPtr->clockReference != REFERENCE_INTERNAL_CLK)
      {
        if ( getChasisSlotIdTrunkTable(oamOilCfgSystemClockDetailsPtr->clockPortId, &chasisFrameId, &slotId ) 
            != CLIB_SUCCESS) 
        {
          LOG_PRINT(LOG_CRITICAL,
              "updateSystemClockDetails: FrameId and SlotId for ClockPort:: %d is not found. Failed" , 
              oamOilCfgSystemClockDetailsPtr->clockPortId);
          return;
        }
        systemClockInfoTableApi.clkReference = oamOilCfgSystemClockDetailsPtr->clockReference ;
        systemClockInfoTableApi.chasisFrameId = chasisFrameId ;
        systemClockInfoTableApi.slotId = slotId ;
        systemClockInfoTableApi.trunkPortId = oamOilCfgSystemClockDetailsPtr->clockPortId ;
      }
      else
      {
        /*Mantis 6651 Fix - Gaurav Bhatnagar*/
        systemClockInfoTableApi.clkReference = REFERENCE_INTERNAL_CLK;
      }
    }


    LOG_PRINT(LOG_INFO,"updateSystemClockDetails: Exiting from Function");
  }


  /********************************* Function  Header********************************
    Function Name:       GetTrunkPortStateFromSystemDetails()
Parameters:          I_U16 TrunkPortId
Return type:         TrunkState
Purpose:             Check Bpm TrunkPortDetails for Given Port and send the TrunkState
   ************************************************************************************/

  I_U32 GetTrunkPortStateFromSystemDetails(I_U16 TrunkPortId)
  {
    sTrunkPortDetails      *TrunkPortDetailsBpmPtr = &((sSystemCardInfo *)gSystemDetails)->portInfo;
    I_U32 i = ZERO;

    if (!gSystemDetails) {
      LOG_PRINT(LOG_INFO,"%s: gSystemDetails=NULL",__func__);
      return ;
    }

    for (i=0; i < MAX_PORT; i++) {
      if (TrunkPortDetailsBpmPtr->portInfo[i].portID == TrunkPortId) {
        return TrunkPortDetailsBpmPtr->portInfo[i].trunkOperStatus;
      }
    }
    LOG_PRINT(LOG_INFO,"%s: TrunkPortId[%u] not found in SystemDetails send by BPM",__func__,TrunkPortId);
    return 2; //Invalid value
  }
  /*BSC R2.0 Changes Starts*/
  /********************************* Function  Header********************************
    Function Name:       GetTrunkPortPhysicalStateFromSystemDetails()
Parameters:          I_U16 TrunkPortId
Return type:         TrunkState
Purpose:             Check Bpm TrunkPortDetails for Given Port and send the Trunk PhysicalState
   ************************************************************************************/

  I_U32 GetTrunkPortPhysicalStateFromSystemDetails(I_U16 TrunkPortId)
  {
    sTrunkPortDetails      *TrunkPortDetailsBpmPtr = &((sSystemCardInfo *)gSystemDetails)->portInfo;
    I_U32 i = ZERO;

    if (!gSystemDetails) {
      LOG_PRINT(LOG_INFO,"%s: gSystemDetails=NULL",__func__);
      return ;
    }

    for (i=0; i < MAX_PORT; i++)
    {
      if (TrunkPortDetailsBpmPtr->portInfo[i].portID == TrunkPortId) 
      {
        if(TrunkPortDetailsBpmPtr->portInfo[i].isPortPresent == BPM_TRUE)
          return PRESENT;
        else
          return NOT_PRESENT; 
      }
    }
    LOG_PRINT(LOG_INFO,"%s: TrunkPortId[%u] not found in SystemDetails send by BPM",__func__,TrunkPortId);
    return 3; //Invalid value
  }
  /*BSC R2.0 Changes Ends*/

  /********************************* Function  Header********************************
    Function Name:       sendTrunkStateChangeReq()
Parameters:          void
Return type:         void
Purpose:             To send TrunkPort State change Request to OIL
In switchover cases it is possbile that trunkstate does not match with the state in DB
In this functions the DB state is reapply to all the configured TrunkPorts
DB State             BPM State              Action
TrunkState Enable -> TrunkState Enable   => NoAction
TrunkState Disable-> TrunkState Enable   => Disable
TrunkState Disable-> TrunkState Disable  => NoAction
TrunkState Enable -> TrunkState Disable  => Enable
BB, 15-06-09::14:59
Other Note:          Added for CS4.0 Init Part

   ************************************************************************************/
  I_Bool sendTrunkStateChangeReq()
  {
    OamsCfgOilE1EnableReq          oamsCfgOilE1EnableReqBuf = {0};
    TrunkPortTableApi              *trunkPortTableApiDbPtr = NULL;
    TrunkPortTableApi              *trunkPortTableApiDbTmpPtr = NULL;
    I_U32 outRows                  = ZERO;
    I_U16 outSize                  = ZERO;
    I_U32 i=0,c=0                    ;
    I_Bool mismatchFound                 ;

    LOG_PRINT(LOG_INFO,"%s: Enter",__func__);

    if (!gSystemDetails) {
      LOG_PRINT(LOG_INFO,"%s: gSystemDetails=NULL",__func__);
      return ;
    }

    if(getallTrunkPortTable(&trunkPortTableApiDbPtr,&outRows, &outSize) !=CLIB_SUCCESS) {
      LOG_PRINT(LOG_INFO,"%s: getallTrunkPortTable failed",__func__);
      return CFG_FAILURE;
    }

    for (c=0,i=0; i < outRows; i++)
    {
      trunkPortTableApiDbTmpPtr = (TrunkPortTableApi *) (((I_U8 *)trunkPortTableApiDbPtr + i*outSize));
      mismatchFound = FALSE;
      if(GetTrunkPortPhysicalStateFromSystemDetails(trunkPortTableApiDbTmpPtr->trunkPortId) ==
          PRESENT )
      {
        switch ( trunkPortTableApiDbTmpPtr->physicalTrunkPortState ) 
        {
          case ACTIVATED:
            //Check mismatch case 
            if ( GetTrunkPortStateFromSystemDetails(trunkPortTableApiDbTmpPtr->trunkPortId) == 
                BPM_TRUNK_DISABLE ) 
            {
              oamsCfgOilE1EnableReqBuf.portDetail[c].operatorControlledTrunkState =ACTIVATED;
              mismatchFound = TRUE;
              LOG_PRINT(LOG_INFO,"%s: TrunkPort[%u] State Mismatch BPM:DIS, DB:EN",
                  __func__,trunkPortTableApiDbTmpPtr->trunkPortId);
            }
#if 0
            else
            {
              if(gE1Data[trunkPortTableApiDbTmpPtr->trunkPortId].LOS_Active != TRUE) 
              {  
                trunkPortStsTbl.chasisFrameId = trunkPortTableApiDbTmpPtr->chasisFrameId;
                trunkPortStsTbl.slotId = trunkPortTableApiDbTmpPtr->slotId;
                trunkPortStsTbl.trunkPortId = trunkPortTableApiDbTmpPtr->trunkPortId;
                trunkPortStsTbl.oprStatus = ENABLED;
                trunkPortStsTbl.physicalPresenceState = PRESENT;
                if(updateTrunkPortStatusTable(&trunkPortStsTbl) != CLIB_SUCCESS)
                {
                  insertTrunkPortStatusTable(&trunkPortStsTbl);
                }
              }
            }
#endif
            break;
          case DEACTIVATED:
            //Check mismatch case 
            if ( GetTrunkPortStateFromSystemDetails(trunkPortTableApiDbTmpPtr->trunkPortId) == 
                BPM_TRUNK_ENABLE)
            {
              oamsCfgOilE1EnableReqBuf.portDetail[c].operatorControlledTrunkState = DEACTIVATED;
              mismatchFound = TRUE;
              LOG_PRINT(LOG_INFO,"%s: TrunkPort[%u] State Mismatch BPM:EN, DB:DIS",
                  __func__,trunkPortTableApiDbTmpPtr->trunkPortId);
            }     
            break;
        }
        if(mismatchFound == TRUE) 
        {
          LOG_PRINT(DEBUG,"mismatch found for frame%d slot%d portId%d index%d",
              trunkPortTableApiDbTmpPtr->chasisFrameId, trunkPortTableApiDbTmpPtr->slotId,
              trunkPortTableApiDbTmpPtr->trunkPortId,c); 
          oamsCfgOilE1EnableReqBuf.portDetail[c].frameId          = trunkPortTableApiDbTmpPtr->chasisFrameId ;
          oamsCfgOilE1EnableReqBuf.portDetail[c].slotId           = trunkPortTableApiDbTmpPtr->slotId ;
          oamsCfgOilE1EnableReqBuf.portDetail[c].trunkPortId      = trunkPortTableApiDbTmpPtr->trunkPortId ;
          //oamsCfgOilE1EnableReqBuf.portDetail[c].physicalTrunkPortState filled above
          oamsCfgOilE1EnableReqBuf.portDetail[c].trunkType        = trunkPortTableApiDbTmpPtr->trunkType ;
          oamsCfgOilE1EnableReqBuf.portDetail[c].loopType         =  trunkPortTableApiDbTmpPtr->loopType;
          oamsCfgOilE1EnableReqBuf.portDetail[c].loopback         = trunkPortTableApiDbTmpPtr->loopback ;
          oamsCfgOilE1EnableReqBuf.portDetail[c].trunkFrameOption = trunkPortTableApiDbTmpPtr->trunkFramingOption ;
          oamsCfgOilE1EnableReqBuf.portDetail[c].encodeType       = trunkPortTableApiDbTmpPtr->encodeType ;
          oamsCfgOilE1EnableReqBuf.portDetail[c].sigStrength      = trunkPortTableApiDbTmpPtr->sigStrength ;
          LOG_PRINT(DEBUG,"CfgOilReq buffer filled for frame%d slot%d portId%d index%d",
              oamsCfgOilE1EnableReqBuf.portDetail[c].frameId,oamsCfgOilE1EnableReqBuf.portDetail[c].slotId,
              oamsCfgOilE1EnableReqBuf.portDetail[c].trunkPortId,c); 
          c++;
        }
      }//if TrunkPort Present
    }

    free(trunkPortTableApiDbPtr);

    oamsCfgOilE1EnableReqBuf.numPorts = c ;

    LOG_PRINT(DEBUG,"Total Number of TrunkPorts Change Req send for %d",c); 
    if(c != 0) { 
      LOG_PRINT(LOG_DEBUG,"%s: Send OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ to Oil",__func__);
      cfgSendMessage(&oamsCfgOilE1EnableReqBuf, 
          sizeof(OamsCfgOilE1EnableReq), 
          ENT_OAM_OIL, 
          OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ, 
          0);
    }                 

    //DalocOrdBuf((I_Void *)gSystemDetails); //BSC R2.0 Changes
    //gSystemDetails = NULL;

    LOG_PRINT(LOG_INFO,"%s: Exit",__func__);
    if (c != 0) {
      return CFG_SUCCESS;
    }
    else {
      return CFG_FAILURE;
    }
  }

  /********************************* Function  Header********************************
    Function Name:       sendTrunkStateChangeFailAlarm()
Parameters:          void
Return type:         void
Purpose:             To Send alarm if Trunk state change response fails.
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/
  I_Void sendTrunkStateChangeFailAlarm(I_U8 frameId, I_U8 slotId, I_U16 trunkPortId)
  {
    OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};

    LOG_PRINT(LOG_INFO,"sendTrunkStateChangeFailAlarm: Entering from Function");

    OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = ALARM_E1_ENABLE_FAILURE;
    OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;

    OamsCfgAfhSysAlarmBuff.sysAlarm.info3      =  OAMS_OBJTYPE_TRUNKPORT;
    OamsCfgAfhSysAlarmBuff.sysAlarm.key1       =  frameId;
    OamsCfgAfhSysAlarmBuff.sysAlarm.key2       =  slotId;
    OamsCfgAfhSysAlarmBuff.sysAlarm.key3       =  trunkPortId;

    OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"\
        Enable failed for Trunk Port [%d] ",trunkPortId);

    cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

    LOG_PRINT(LOG_INFO,"sendTrunkStateChangeFailAlarm: Extiting from Function");
  }
  /********************************* Function  Header********************************
    Function Name:       checkTrunkStateChangeResp()
Parameters:          void
Return type:         void
Purpose:             To Check Trunk State Change resp Failure (if Any).
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/
  I_Bool checkTrunkStateChangeResp()
  {
    OamOilCfgE1EnableResp *oamOilCfgE1EnableRespPtr = NULL;
    I_U32 count = 0;
    TrunkPortStatusTableApi trunkPortStsTbl;
    TrunkPortTableIndices trunkPortTblIndx;
    TrunkPortTableApi *outData;	
    I_S32 res;
    LOG_PRINT(LOG_INFO,"checkTrunkStateChangeResp: Entering in Function");
    oamOilCfgE1EnableRespPtr = (OamOilCfgE1EnableResp *)((I_U8*) gCfgMsgBuf);

    LOG_PRINT(DEBUG,"Total Number Of Ports for which State change resp rcvd is %d",
        oamOilCfgE1EnableRespPtr->numPorts);

    if(oamOilCfgE1EnableRespPtr->result != OPERATION_SUCCESS)   
    {
      LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: Trunk State Change failed at BPM.failType(%d)",oamOilCfgE1EnableRespPtr->result);
      for(count = 0 ; count < oamOilCfgE1EnableRespPtr->numPorts ; count++)
      {
        LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: CFG is marking TrunkState as DISBALED in DB for Trunk Port Id [%d]" , oamOilCfgE1EnableRespPtr->portResult[count].trunkPortId);
        sendTrunkStateChangeFailAlarm(oamOilCfgE1EnableRespPtr->portResult[count].frameId, 
            oamOilCfgE1EnableRespPtr->portResult[count].slotId,
            oamOilCfgE1EnableRespPtr->portResult[count].trunkPortId);
        trunkPortStsTbl.chasisFrameId = oamOilCfgE1EnableRespPtr->portResult[count].frameId;
        trunkPortStsTbl.slotId = oamOilCfgE1EnableRespPtr->portResult[count].slotId;
        trunkPortStsTbl.trunkPortId = oamOilCfgE1EnableRespPtr->portResult[count].trunkPortId;
        trunkPortStsTbl.oprStatus = DISABLED;
        trunkPortStsTbl.physicalPresenceState = PRESENT;
        if(updateTrunkPortStatusTable(&trunkPortStsTbl) !=CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: Trunk State Change Can not be changed. DB Error");
        }

      }
      LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: Initialization failed. ");
      return CFG_FAILURE; 
    }
    else
    {
      for(count = 0 ; count < oamOilCfgE1EnableRespPtr->numPorts ; count++)
      {
        if(oamOilCfgE1EnableRespPtr->portResult[count].result != OPERATION_SUCCESS)
        {
          LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: TrunkStateChange Failed for TrunkPortId::%d failtype(%d)", 
              oamOilCfgE1EnableRespPtr->portResult[count].trunkPortId,oamOilCfgE1EnableRespPtr->portResult[count].result);
          LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: CFG is marking TrunkState as DISBALED in DB");
          sendTrunkStateChangeFailAlarm(oamOilCfgE1EnableRespPtr->portResult[count].frameId, 
              oamOilCfgE1EnableRespPtr->portResult[count].slotId,
              oamOilCfgE1EnableRespPtr->portResult[count].trunkPortId);
          trunkPortStsTbl.chasisFrameId = oamOilCfgE1EnableRespPtr->portResult[count].frameId;
          trunkPortStsTbl.slotId = oamOilCfgE1EnableRespPtr->portResult[count].slotId;
          trunkPortStsTbl.trunkPortId = oamOilCfgE1EnableRespPtr->portResult[count].trunkPortId;
          trunkPortStsTbl.oprStatus = DISABLED;
          trunkPortStsTbl.physicalPresenceState = PRESENT;
          if(updateTrunkPortStatusTable(&trunkPortStsTbl) !=CLIB_SUCCESS)
          {
            LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: Trunk State Change Can not be changed, DB Error.");
          }
        }
        else
        {
          LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: TrunkStateChange Success for TrunkPort Id::  %d", oamOilCfgE1EnableRespPtr->portResult[count].trunkPortId);
          //sendTrunkStateChangeFailAlarm(oamOilCfgE1EnableRespPtr->portResult[count].frameId, 
          //      oamOilCfgE1EnableRespPtr->portResult[count].slotId,
          //      oamOilCfgE1EnableRespPtr->portResult[count].trunkPortId);
          trunkPortStsTbl.chasisFrameId = oamOilCfgE1EnableRespPtr->portResult[count].frameId;
          trunkPortStsTbl.slotId = oamOilCfgE1EnableRespPtr->portResult[count].slotId;
          trunkPortStsTbl.trunkPortId = oamOilCfgE1EnableRespPtr->portResult[count].trunkPortId;

          trunkPortTblIndx.chasisFrameId = oamOilCfgE1EnableRespPtr->portResult[count].frameId;
          trunkPortTblIndx.slotId = oamOilCfgE1EnableRespPtr->portResult[count].slotId;
          trunkPortTblIndx.trunkPortId = oamOilCfgE1EnableRespPtr->portResult[count].trunkPortId;

          res = getTrunkPortTable(&trunkPortTblIndx,&outData); 
          if(res != CLIB_SUCCESS)
          {
            LOG_PRINT(DEBUG,"getTrunkPortTable failed res(%d) for frameId(%d)slotId(%d)trunkPortId(%d)",
                res,trunkPortTblIndx.chasisFrameId,trunkPortTblIndx.slotId,trunkPortTblIndx.trunkPortId);  
            return CFG_FAILURE; 
          }

          if(  (outData->physicalTrunkPortState == ACTIVATED) &&
              (gE1Data[outData->trunkPortId].LOS_Active != TRUE)  )
          {	
            trunkPortStsTbl.oprStatus = ENABLED;
            LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: CFG is marking TrunkState as ENABLED in DB");
          }
          else
          {	
            trunkPortStsTbl.oprStatus = DISABLED;
            LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: CFG is marking TrunkState as DISABLED in DB");
          }

          free(outData);  

          trunkPortStsTbl.physicalPresenceState = PRESENT;
          if(updateTrunkPortStatusTable(&trunkPortStsTbl) !=CLIB_SUCCESS)
          {
            LOG_PRINT(LOG_CRITICAL,"checkTrunkStateChangeResp: Trunk State Change Can not be changed, DB Error.");
          }
        }
      }
    }
    LOG_PRINT(LOG_INFO,"checkTrunkStateChangeResp: Exiting from Function");

    return CFG_SUCCESS;
  }


  /********************************* Function  Header********************************
    Function Name:       updateCardDetails()
Parameters:          void
Return type:         void
Purpose:             To update the Card Details if any alrm comes from OIL
Other Note:          Added for CS4.0
   ************************************************************************************/

  I_Void updateCardDetails()
  {
    EicCardInfoTableIndices eicCardInfoTableIndices;
    IccCardInfoTableIndices iccCardInfoTableIndices;
    I_U32 cardState;

    SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

    LOG_PRINT(LOG_INFO,"updateCardDetails: Entering in Function");
    LOG_PRINT(LOG_INFO,"updateCardDetails: Card State Change for ChasisFrameId [%d] and SlotId [%d]", recAlarmPtr->key1, recAlarmPtr->key2);
    eicCardInfoTableIndices.chasisFrameId = (I_U8) (recAlarmPtr->key1);
    eicCardInfoTableIndices.slotId = (I_U8) (recAlarmPtr->key2);
    iccCardInfoTableIndices.chasisFrameId = (I_U8) (recAlarmPtr->key1);
    iccCardInfoTableIndices.slotId = (I_U8) (recAlarmPtr->key2);
    cardState = recAlarmPtr->key4;
    if(recAlarmPtr->sysalarmId == INFO_PEER_CARDSTATE_CHANGE_PM_OAM)
    {
      iccCardInfoTableIndices.slotId 
        = ( (iccCardInfoTableIndices.slotId == ICCSELFCARD) ? ICCMATECARD : ICCSELFCARD );
    }
    if(updateEicCardState(&eicCardInfoTableIndices, cardState) == CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"updateCardDetails: EicCardInfoTable updated");
      recAlarmPtr->info3 = OAMS_OBJTYPE_EIC;
    }
    else if(updateIccCardState(&iccCardInfoTableIndices, cardState) == CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"updateCardDetails: IccCardInfoTable updated");
      recAlarmPtr->info3 = OAMS_OBJTYPE_ICC;
    } 
    else
    {
      LOG_PRINT(LOG_INFO,"updateCardDetails: Wrong Chasis FrameID or Slot ID Received. Failed");
    }
    LOG_PRINT(LOG_INFO,"updateCardDetails: Exiting from Function");

  }
  /********************************* Function  Header********************************
    Function Name:       deleteEicCardDetails()
Parameters:          void
Return type:         void
Purpose:             To delete EIC Card details
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void deleteEicCardDetails()
  {
    EicCardInfoTableIndices eicCardInfoTableIndices;
    SwMNodeTableIndices swMNodeIndices;
    I_U8 frameId;
    I_U8 slotId;
    I_S32 res,i;
    SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

    LOG_PRINT(LOG_INFO,"deleteEicCardDetails: Entering in Function");
    eicCardInfoTableIndices.chasisFrameId = recAlarmPtr->key1;
    eicCardInfoTableIndices.slotId = recAlarmPtr->key2;
#if 0
    if(deleteEicCardInfoTable(&eicCardInfoTableIndices) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"deleteEicCardDetails: Frame Id:: %d and Slot Id:: %d does not exist",eicCardInfoTableIndices.chasisFrameId , eicCardInfoTableIndices.slotId);

    }
#endif
    /* Deleting entries from swMNodeTable */
    LOG_PRINT(LOG_INFO,"deleteing entries from SwMNodeTable for EIC....");
    swMNodeIndices.nodeType = SYS_NODE_TYPE_EIC;
    swMNodeIndices.nodeIdentity = recAlarmPtr->key2; 
    swMNodeIndices.chasisFrameId = recAlarmPtr->key1;
    swMNodeIndices.slotId = recAlarmPtr->key2;
    if(deleteSwMNodeTable(&swMNodeIndices) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"deleteEicCardDetails: NodeType:: %d and NodeIdentity:: %d does not exist in SwmNodeTable",swMNodeIndices.nodeType , swMNodeIndices.nodeIdentity);

    }
    for(i=0;i<2;i++)
    {
      LOG_PRINT(LOG_INFO,"deleteing entries from SwMNodeTable for EIC DSP....");
      swMNodeIndices.nodeType = SYS_NODE_TYPE_DSP;
      swMNodeIndices.chasisFrameId = recAlarmPtr->key1;
      swMNodeIndices.slotId = recAlarmPtr->key2;
      if(recAlarmPtr->key2 == EIC0_CARD)
        swMNodeIndices.nodeIdentity = 2+i; 
      else
        swMNodeIndices.nodeIdentity = 4+i; 

      gDspInfo[swMNodeIndices.nodeIdentity].isDspPresent = NOT_PRESENT; 
      gDspBootInfoSent[swMNodeIndices.nodeIdentity] = 0;
      if(deleteSwMNodeTable(&swMNodeIndices) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"deleteEicCardDetails: NodeType:: %d and NodeIdentity:: %d does not exist in SwmNodeTable",
            swMNodeIndices.nodeType , swMNodeIndices.nodeIdentity);
      }
    } 
    frameId =  recAlarmPtr->key1;
    slotId =  recAlarmPtr->key2;

    /*BSC R2.0 Changes Starts*/
    switch (recAlarmPtr->sysalarmId)
    { 
      case INFO_CARD_EJECTED_PM_OAM :
        LOG_PRINT(DEBUG,"Ejected EIC card is frameId:%d slotId:%d",frameId,slotId);
        res = markEicCardNotPresent(frameId, slotId); 
        res = markEicTrunkPortsNotPresentDisabled(frameId, slotId);
        res = markEicClockSourcePending(frameId, slotId);
        res = markDspNotPresent(frameId, slotId); 
        break;

      case INFO_BPM_EIC_DISCONNECTED :
        LOG_PRINT(DEBUG,"Disconncetd EIC card is frameId:%d slotId:%d",frameId, slotId);
        res = markEicCardDisable(frameId, slotId); 
        res = markEicTrunkPortDisabled(frameId, slotId);
        res = markDspDisabled(frameId, slotId);
        break;

      default:
        LOG_PRINT(MAJOR,"deleteEicCardDetails: no case matched for AlarmId:%d",recAlarmPtr->sysalarmId);
        break; 
    }


    LOG_PRINT(LOG_INFO,"deleteEicCardDetails: Exiting from Function");

  }

  /*BSC R2.0 Changes Starts*/
  /******************************* Function  Header*****************************
    Function Name : markIccCardNotPresent()
Parameters    : IccCardInfoTableIndices * 
Return type   : I_S32 
Purpose       : Mark IccCard NOT_PRESENT in IccCardInfoTable if the PRESENT_CARD_INFO_RESP 
does not contain those chasisFrameId and slotId                
Other Note    : Added For BSC R2.0
   *****************************************************************************/
  I_S32 markIccCardNotPresent(IccCardInfoTableIndices *iccCardIndex)
  {
    IccCardInfoTableApi *outData;
    if( getIccCardInfoTable(iccCardIndex,&outData) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getIccCardInfoTable failed for frameid(%d) slotid(%d)",
          iccCardIndex->chasisFrameId, iccCardIndex->slotId );
      return 1;
    } 

    outData->physicalPresenceState = NOT_PRESENT;
    /* Mantis 9956 */
    outData->cardOperationalState = CARDSTATE_ABSENT;
    /*Mantis 9956 End */

    if(updateIccCardInfoTable(outData) != CLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"updateIccCardInfoTable failed for frameid(%d) slotid(%d)",
          iccCardIndex->chasisFrameId, iccCardIndex->slotId );
      free(outData);
      return 2;
    }

    free(outData);
    return 0;
  }

  /******************************* Function  Header*****************************
    Function Name : markEicCardNotPresent()
Parameters    : I_U8 frameId, I_U8 slotId 
Return type   : I_S32 
Purpose       : Mark EicCard NOT_PRESENT in EicCardInfoTable if the PRESENT_CARD_INFO_RESP 
does not contain those chasisFrameId and slotId                
Other Note    : Added For BSC R2.0
   *****************************************************************************/
  I_S32 markEicCardNotPresent(I_U8 frameId, I_U8 slotId)
  {
    EicCardInfoTableIndices eicCardIndex;
    EicCardInfoTableApi *outData;

    LOG_PRINT(DEBUG,"markEicCardNotPresent: Entering In func");
    eicCardIndex.chasisFrameId = frameId;
    eicCardIndex.slotId = slotId;


    if( getEicCardInfoTable(&eicCardIndex,&outData) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getEicCardInfoTable failed for frameid(%d) slotid(%d)",
          eicCardIndex.chasisFrameId, eicCardIndex.slotId );
      return CFG_FAILURE;
    } 

    outData->physicalPresenceState = NOT_PRESENT;
    outData->cardOperationalState = BPM_CARDSTATE_ABSENT;

    if(updateEicCardInfoTable(outData) != CLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"updateEicCardInfoTable failed for frameid(%d) slotid(%d)",
          eicCardIndex.chasisFrameId, eicCardIndex.slotId );
      free(outData);
      return CFG_FAILURE;
    }

    free(outData);
    LOG_PRINT(DEBUG,"markEicCardNotPresent: Exiting from func");
    return CFG_SUCCESS;
  }


  /******************************* Function  Header*****************************
    Function Name : markEicTrunkPortsNotPresentDisabled()
Parameters    : I_U8 frameId, I_U8 slotId 
Return type   : I_S32 
Purpose       :
Other Note    : Added For BSC R2.0
   *****************************************************************************/
  I_S32 markEicTrunkPortsNotPresentDisabled(I_U8 frameId, I_U8 slotId)
  {
    TrunkPortStatusTableApi *outData, *tmpPtr ;
    I_U32 outRows = 0, i = 0;
    I_U16 outSize = 0;

    LOG_PRINT(DEBUG,"markEicTrunkPortsNotPresentDisabled: Entering In func");

    if( getallTrunkPortStatusTable(&outData,&outRows,&outSize) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getallTrunkPortStatusTable failed ");
      return CFG_FAILURE;
    } 

    for(i = 0; i < outRows; i++)
    {
      tmpPtr = (TrunkPortStatusTableApi *)(((I_U8 *) outData) + i * outSize);
      if(tmpPtr->chasisFrameId == frameId && 
          tmpPtr->slotId == slotId &&
          tmpPtr->physicalPresenceState == PRESENT)
      {
        if(tmpPtr->oprStatus == ENABLED)
        {
          tmpPtr->oprStatus = DISABLED;
          SendTrunkPortDisableAlarm(tmpPtr->chasisFrameId,tmpPtr->slotId,tmpPtr->trunkPortId); 
        } 
        tmpPtr->physicalPresenceState = NOT_PRESENT;
        if(updateTrunkPortStatusTable(tmpPtr) != CLIB_SUCCESS)
        {
          LOG_PRINT(DEBUG,"updateTrunkPortStatusTable failed for frameid(%d) slotid(%d) portId(%d)",
              tmpPtr->chasisFrameId,tmpPtr->slotId,tmpPtr->trunkPortId);
        }
      } 
    }

    free(outData);
    LOG_PRINT(DEBUG,"markEicTrunkPortsNotPresentDisabled: Exiting from func");
    return CFG_SUCCESS;
  }

  /******************************* Function  Header*****************************
    Function Name : markEicClockSourcePending()
Parameters    : I_U8 frameId, I_U8 slotId 
Return type   : I_S32 
Purpose       : 
Other Note    : Added For BSC R2.0
   *****************************************************************************/
  I_S32 markEicClockSourcePending(I_U8 frameId, I_U8 slotId)
  {
    ClkSourceConfigStatusTableApi *outData, *tmpPtr ;
    I_U32 outRows = 0, i = 0;
    I_U16 outSize = 0;

    LOG_PRINT(DEBUG,"markEicClockSourcePending: Entering In func");

    if( getallClkSourceConfigStatusTable(&outData,&outRows,&outSize) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getallClkSourceConfigStatusTable failed ");
      return CFG_FAILURE;
    } 

    for(i = 0; i < outRows; i++)
    {
      tmpPtr = (ClkSourceConfigStatusTableApi *)(((I_U8 *) outData) + i * outSize);
      if(tmpPtr->chasisFrameId == frameId && 
          tmpPtr->slotId == slotId)
      {
        tmpPtr->clkConfigStatus = PENDING;
        if(updateClkSourceConfigStatusTable(tmpPtr) != CLIB_SUCCESS)
        {
          LOG_PRINT(DEBUG,"updateClkSourceConfigStatusTable failed for frameid(%d) slotid(%d) portId(%d)",
              tmpPtr->chasisFrameId,tmpPtr->slotId,tmpPtr->trunkPortId);
        }
        sendClkSourcePendingAlarm(tmpPtr->chasisFrameId,tmpPtr->slotId,tmpPtr->trunkPortId,ZERO); 
      } 
    }

    free(outData);
    LOG_PRINT(DEBUG,"markEicClockSourcePending: Exiting from func");
    return CFG_SUCCESS;
  }

  /******************************* Function  Header*****************************
    Function Name : markDspNotPresent()
Parameters    : I_U8 frameId, I_U8 slotId 
Return type   : I_S32 
Purpose       : 
Other Note    : Added For BSC R2.0
   *****************************************************************************/
  I_S32 markDspNotPresent(I_U8 frameId, I_U8 slotId)
  {
    DspStatusTableApi *outData, *tmpPtr ;
    I_U32 outRows = 0, i = 0;
    I_U16 outSize = 0;

    LOG_PRINT(DEBUG,"markDspNotPresent: Entering In func");

    if( getallDspStatusTable(&outData,&outRows,&outSize) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getallClkSourceConfigStatusTable failed ");
      return CFG_FAILURE;
    } 

    for(i = 0; i < outRows; i++)
    {
      tmpPtr = (DspStatusTableApi *)(((I_U8 *) outData) + i * outSize);

      if(tmpPtr->chasisFrameId == frameId && 
          tmpPtr->slotId == slotId &&
          tmpPtr->physicalPresenceState == PRESENT)
      {
        tmpPtr->oprStatus = DISABLED;
        tmpPtr->physicalPresenceState = NOT_PRESENT;
        gDspInfo[tmpPtr->dspId].isDspPresent = NOT_PRESENT;
        gDspBootInfoSent[tmpPtr->dspId] = 0;
        sendDsphAvailSts(tmpPtr);
      } 
    }

    free(outData);
    LOG_PRINT(DEBUG,"markDspNotPresent: Exiting from func");
    return CFG_SUCCESS;
  }

  /******************************* Function  Header*****************************
    Function Name : markEicTrunkPortDisabled()
Parameters    : I_U8 frameId, I_U8 slotId 
Return type   : I_S32 
Purpose       :
Other Note    : Added For BSC R2.0
   *****************************************************************************/
  I_S32 markEicTrunkPortDisabled(I_U8 frameId, I_U8 slotId)
  {
    TrunkPortStatusTableApi *outData, *tmpPtr ;
    I_U32 outRows = 0, i = 0;
    I_U16 outSize = 0;

    LOG_PRINT(DEBUG,"markEicTrunkPortDisabled: Entering In func");

    if( getallTrunkPortStatusTable(&outData,&outRows,&outSize) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getallTrunkPortStatusTable failed ");
      return CFG_FAILURE;
    } 

    for(i = 0; i < outRows; i++)
    {
      tmpPtr = (TrunkPortStatusTableApi *)(((I_U8 *) outData) + i * outSize);
      if(tmpPtr->chasisFrameId == frameId && 
          tmpPtr->slotId == slotId &&
          tmpPtr->physicalPresenceState == PRESENT && 
          tmpPtr->oprStatus == ENABLED )
      {
        tmpPtr->oprStatus = DISABLED;
        LOG_PRINT(DEBUG,"updateTrunkPortStatusTable called for frameid(%d) slotid(%d) portId(%d)",
            tmpPtr->chasisFrameId,tmpPtr->slotId,tmpPtr->trunkPortId);
        if(updateTrunkPortStatusTable(tmpPtr) != CLIB_SUCCESS)
        {
          LOG_PRINT(DEBUG,"updateTrunkPortStatusTable failed for frameid(%d) slotid(%d) portId(%d)",
              tmpPtr->chasisFrameId,tmpPtr->slotId,tmpPtr->trunkPortId);
        }
        SendTrunkPortDisableAlarm(tmpPtr->chasisFrameId,tmpPtr->slotId,tmpPtr->trunkPortId); 
      } 
    }

    free(outData);
    LOG_PRINT(DEBUG,"markEicTrunkPortDisabled: Exiting from func");
    return CFG_SUCCESS;
  }

  /******************************* Function  Header*****************************
    Function Name : markDspDisabled()
Parameters    : I_U8 frameId, I_U8 slotId 
Return type   : I_S32 
Purpose       : 
Other Note    : Added For BSC R2.0
   *****************************************************************************/
  I_S32 markDspDisabled(I_U8 frameId, I_U8 slotId)
  {
    DspStatusTableApi *outData, *tmpPtr ;
    I_U32 outRows = 0, i = 0;
    I_U16 outSize = 0;

    LOG_PRINT(DEBUG,"markDspDisabled: Entering In func");

    if( getallDspStatusTable(&outData,&outRows,&outSize) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getallClkSourceConfigStatusTable failed ");
      return CFG_FAILURE;
    } 

    for(i = 0; i < outRows; i++)
    {
      tmpPtr = (DspStatusTableApi *)(((I_U8 *) outData) + i * outSize);

      if(tmpPtr->chasisFrameId == frameId && 
          tmpPtr->slotId == slotId &&
          tmpPtr->physicalPresenceState == PRESENT)
      {
        tmpPtr->oprStatus = DISABLED;
        gDspBootInfoSent[tmpPtr->dspId] = 0;
        sendDsphDspDown(tmpPtr,0);
        //sendDsphDspDown(tmpPtr, DSP_EIC_DISCONNECTED);
      } 
    }

    free(outData);
    LOG_PRINT(DEBUG,"markDspDisabled: Exiting from func");
    return CFG_SUCCESS;
  }

  I_Void sendDsphDspDown(DspStatusTableApi *dspStsPtr ,I_U32 cause )
  {
    OamsCfgDsphDspDownInfo sndMsgBuff;

    sndMsgBuff.frameId =  dspStsPtr->chasisFrameId ;
    sndMsgBuff.slotId  =  dspStsPtr->slotId ;
    sndMsgBuff.dspId   =  dspStsPtr->dspId ;
    sndMsgBuff.cause   =  cause ;

    LOG_PRINT(LOG_DEBUG,"InfoBpmDspDown rcvd for frameId(%d) slotId(%d) dspId(%d) cause(%d) ",
        sndMsgBuff.frameId,sndMsgBuff.slotId,sndMsgBuff.dspId,
        sndMsgBuff.cause );

    cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgDsphDspDownInfo),
        ENT_OAMS_DSPH, OAMS_CFG_DSPH_DSP_DOWN_INFO, 0);

  }

  /*BSC R2.0 Changes Ends*/

  /********************************* Function  Header********************************
    Function Name:       deleteIccCardDetails()
Parameters:          void
Return type:         void
Purpose:             To delete ICC Card details
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void deleteIccCardDetails()
  {
    IccCardInfoTableIndices iccCardInfoTableIndices;
    IccCardInfoTableApi *iccCardInfoTableApiPtr = NULL;
    IccCardInfoTableApi *tmpIccCardPtr = NULL;
    SwMNodeTableIndices swMNodeIndices;
    SwMNodeTableApi *swMData = NULL;
    SwMTableIndices swMIndices;
    I_U32 bscId;
    I_U32 outRows;
    I_U16 outSize;
    I_U32 index;
    SysAlarm *sysAlarm = NULL;
    sysAlarm = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

    LOG_PRINT(LOG_INFO,"deleteIccCardDetails: Entering in Function");

    if(getallIccCardInfoTable(&iccCardInfoTableApiPtr, &outRows, &outSize) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"deleteIccCardDetails: No Row in Icc Card Info Table");
      return;
    }
    if(outRows == 1)
    {
      LOG_PRINT(LOG_INFO,"deleteIccCardDetails: Exiting from function");
      free(iccCardInfoTableApiPtr);
      return;
    }
    if(iccCardInfoTableApiPtr->slotId != sysAlarm->key2)
    {
      LOG_PRINT(LOG_DEBUG,"deleteIccCardDetails: Slot Id:: %d in firstRow",iccCardInfoTableApiPtr->slotId);
      iccCardInfoTableIndices.slotId = iccCardInfoTableApiPtr->slotId;
    }
    else
    {
      tmpIccCardPtr = (IccCardInfoTableApi *)((I_U8 *)iccCardInfoTableApiPtr + outSize);
      LOG_PRINT(LOG_DEBUG,"deleteIccCardDetails: Slot Id:: %d in secondRow",tmpIccCardPtr->slotId);
      iccCardInfoTableIndices.slotId = tmpIccCardPtr->slotId;

    }
    iccCardInfoTableIndices.chasisFrameId = sysAlarm->key1;
    LOG_PRINT(LOG_INFO,"deleteIccCardDetails:To be deleted Frame Id:: %d and Slot Id:: %d ",iccCardInfoTableIndices.chasisFrameId , iccCardInfoTableIndices.slotId);
    //if(deleteIccCardInfoTable(&iccCardInfoTableIndices) != CLIB_SUCCESS)
    /*HA Changes Starts*/
    gCfgStandbySlotId = 0;
    if(markIccCardNotPresent(&iccCardInfoTableIndices) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"markIccCardNotPresent: Frame Id:: %d and Slot Id:: %d does not exist",
          iccCardInfoTableIndices.chasisFrameId ,iccCardInfoTableIndices.slotId);

    }

    if(markDspNotPresent(iccCardInfoTableIndices.chasisFrameId,iccCardInfoTableIndices.slotId) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"markDspNotPresent : Frame Id:: %d and Slot Id:: %d does not exist",
          iccCardInfoTableIndices.chasisFrameId ,iccCardInfoTableIndices.slotId);
    }  

    /* Deleting Entry from Card StateChangeTable */
    /*   LOG_PRINT(LOG_INFO,"deleteIccCardDetails: deleteing entries from CardStateChangeTable....");
         cardStateChangeTableIndices.chasisFrameId = iccCardInfoTableIndices.chasisFrameId;
         cardStateChangeTableIndices.slotId = iccCardInfoTableIndices.slotId;
         if(deleteCardStateChangeTable(&cardStateChangeTableIndices) != CLIB_SUCCESS)
         {
         LOG_PRINT(LOG_INFO,"deleteEicCardDetails: Deletion in CardStateChange Table failed");

         }
     */
    /* Deleting Entry from SwMNodeTable */
    LOG_PRINT(LOG_INFO,"deleteing entries from SwMNodeTable....");
    if (getBscId(&bscId) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_DEBUG,"No row present in BSS Table");
      swMNodeIndices.nodeIdentity = 0; 
    }
    else
    {
      swMNodeIndices.nodeIdentity = bscId; 
    }
    swMNodeIndices.nodeType = SYS_NODE_TYPE_BSC;
    swMNodeIndices.chasisFrameId = iccCardInfoTableIndices.chasisFrameId;
    swMNodeIndices.slotId = iccCardInfoTableIndices.slotId;
    if ( getSwMNodeTable(&swMNodeIndices, &swMData) != CLIB_SUCCESS )
    {
      LOG_PRINT(LOG_INFO,"deleteIccCardDetails: NodeType:: %d and NodeIdentity:: %d does not exist in SwmNodeTable",swMNodeIndices.nodeType,swMNodeIndices.nodeIdentity);
      free(iccCardInfoTableApiPtr);
      return;
    }
    if(deleteSwMNodeTable(&swMNodeIndices) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"deleteIccCardDetails: NodeType:: %d and NodeIdentity:: %d does not exist in SwmNodeTable",swMNodeIndices.nodeType , swMNodeIndices.nodeIdentity);

    }
    swMIndices.nodeType = SYS_NODE_TYPE_BSC;
    swMIndices.chasisFrameId = iccCardInfoTableIndices.chasisFrameId;
    swMIndices.slotId = iccCardInfoTableIndices.slotId;
    for ( index = 1; index <= 3; index++)
    { 
      if ( index == 1 && ( strlen(swMData->swVersionActive) != ZERO ))
      {
        strcpy(swMIndices.swVersion, swMData->swVersionActive) ;
      }
      else if ( index == 2 && ( strlen(swMData->swVersionInactive) != ZERO ))
      {
        strcpy(swMIndices.swVersion, swMData->swVersionInactive) ;
      }
      else if ( index == 3 && ( strlen(swMData->swVersionDownloaded) != ZERO ))
      {
        strcpy(swMIndices.swVersion, swMData->swVersionDownloaded) ;
      }
      else
      {
        continue;
      }
      if ( deleteSwMTable(&swMIndices) != CLIB_SUCCESS )
      {
        LOG_PRINT(LOG_INFO,"deleteIccCardDetails: ChasisFrameId:: %d and SlotId:: %d Version:: %s does not exist in SwmTable",swMIndices.chasisFrameId , swMIndices.slotId , swMIndices.swVersion);

      }
      else
      {
        LOG_PRINT(LOG_INFO,"deleteIccCardDetails:  Deleting ChasisFrameId:: %d and SlotId:: %d Version:: %s from SwmTable",swMIndices.chasisFrameId , swMIndices.slotId , swMIndices.swVersion);
      }
    }

    swMNodeIndices.nodeType = SYS_NODE_TYPE_DSP;
    swMNodeIndices.chasisFrameId = iccCardInfoTableIndices.chasisFrameId;
    swMNodeIndices.slotId = iccCardInfoTableIndices.slotId;
    if(iccCardInfoTableIndices.slotId == ICCSELFCARD)
      swMNodeIndices.nodeIdentity = 0; 
    else
      swMNodeIndices.nodeIdentity = 1; 


    if(deleteSwMNodeTable(&swMNodeIndices) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"deleteIccCardDetails: NodeType:: %d and NodeIdentity:: %d does not exist in SwmNodeTable",swMNodeIndices.nodeType , swMNodeIndices.nodeIdentity);

    }

    free(iccCardInfoTableApiPtr);
    free(swMData);
    LOG_PRINT(LOG_INFO,"deleteIccCardDetails: Exiting from Function");
  }

  /********************************* Function  Header********************************
    Function Name:       sendPresentCardInfoReq()
Parameters:          void
Return type:         void
Purpose:             To send Present Card Info Request
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void sendPresentCardInfoReq()
  {
    OamsCfgOilPresentCardInfoReq oamsCfgOilPresentCardInfoReq;

    LOG_PRINT(LOG_INFO,"sendCardInfoReq: Entering in Function");
    cfgSendMessage(&oamsCfgOilPresentCardInfoReq, sizeof(OamsCfgOilPresentCardInfoReq), ENT_OAM_OIL, OAMS_CFG_OIL_PRESENT_CARD_INFO_REQ, 0);

    LOG_PRINT(LOG_INFO,"sendCardInfoReq: Exiting from Function");


  }

  /********************************* Function  Header********************************
    Function Name:       sendAlarmToPDC()
Parameters:          void
Return type:         void
Purpose:             To send Alarm to PDC 
Other Note:          
   ************************************************************************************/
  I_Void sendAlarmToPDC(I_U16 msgType)
  {
    OamsCfgPdcAlarmMsg pdcAlarmMsg;

    pdcAlarmMsg.alarmType = msgType;
    LOG_PRINT(LOG_INFO,"sendAlarmtoPDC: Entering in Function");
    cfgSendMessage(&pdcAlarmMsg, sizeof(OamsCfgPdcAlarmMsg),ENT_OAM_PDC,OAMS_CFG_PDC_ALARM_MSG, 0);

    LOG_PRINT(LOG_INFO,"sendAlarmtoPDC: Exiting from Function");

  }
  /********************************* Function  Header********************************
    Function Name:       makeCopyOfAlarm()
Parameters:          void
Return type:         void
Purpose:             To Preserve the alarm. This alarm will be sent after updating DB.
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void makeCopyOfAlarm()
  {
    LOG_PRINT(LOG_INFO,"makeCopyOfAlarm: Entering in function");
    if ( gCfgAlarmBuf != NULL )
    {
      DalocOrdBuf((I_Void *)gCfgAlarmBuf);
      gCfgAlarmBuf = NULL;
    }
    gCfgAlarmBuf =(I_PVoid) AlocOrdBuf(sizeof(SysAlarm)+sizeof(SysHdr));
    if(gCfgAlarmBuf == NULL) 
    {
      LOG_PRINT(MAJOR,"AlocOrdBuf Failed for size:%d",sizeof(SysAlarm)+sizeof(SysHdr) );
      return;
    }
    memcpy(gCfgAlarmBuf , gCfgMsgBuf, sizeof(SysAlarm)+sizeof(SysHdr));
		/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
   	SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgAlarmBuf+sizeof(SysHdr));
		if(recAlarmPtr->sysalarmId == INFO_CARD_STATE_CHANGE_PM_OAM)
		{
    	LOG_PRINT(DEBUG,"1U: ALARM rcvd is INFO_CARD_STATE_CHANGE_PM_OAM");
			recAlarmPtr->sysalarmId = INFO_OBM_SELF_CARD_STATE_CHANGE;
			recAlarmPtr->key2 			= (recAlarmPtr->key2 - 2);
			recAlarmPtr->info3 			= OAMS_OBJTYPE_OBM;
    	LOG_PRINT(DEBUG,"1U: ALARM changed to INFO_OBM_SELF_CARD_STATE_CHANGE for SlotId [%d] for ObjectType[%d] OBM",recAlarmPtr->key2,recAlarmPtr->info3);
		}
		if(recAlarmPtr->sysalarmId == INFO_PEER_CARDSTATE_CHANGE_PM_OAM)
		{
    	LOG_PRINT(DEBUG,"1U: ALARM rcvd is INFO_PEER_CARDSTATE_CHANGE_PM_OAM");
			recAlarmPtr->sysalarmId = INFO_OBM_PEER_CARD_STATE_CHANGE;
			recAlarmPtr->key2 = (recAlarmPtr->key2 - 2);
			recAlarmPtr->info3 = OAMS_OBJTYPE_OBM;
    	LOG_PRINT(DEBUG,"1U: ALARM changed to INFO_OBM_PEER_CARD_STATE_CHANGE for SlotId [%d] for ObjectType[%d] OBM",recAlarmPtr->key2,recAlarmPtr->info3);
		}
		/*Added for 1U BSC Gaurav Sinha 05-07-2016*/	
    LOG_PRINT(LOG_INFO,"makeCopyOfAlarm: Exiting from function");
  }

  /********************************* Function  Header********************************
    Function Name:       updatePresentCardDetails()
Parameters:          void
Return type:         void
Purpose:             To Update Present Card details for which alarm was received.
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void updatePresentCardDetails()
  {
    I_U32 sendAlarm = ZERO,i=0;
    SysAlarm *sysAlarm = NULL;
    sysAlarm = gCfgAlarmBuf + sizeof(SysHdr);
    sFanTrayObjInfo fanTrayObjInfo;

    LOG_PRINT(LOG_INFO,"updatePresentCardDetails: Entering in function");
    if(gCfgAlarmBuf != NULL)
    {
      switch(sysAlarm->sysalarmId)
      {
        case INFO_CARD_EJECTED_PM_OAM:
          LOG_PRINT(LOG_DEBUG,"updatePresentCardDetails: Alarm Received INFO_CARD_EJECTED_PM_OAM.");
          sysAlarm->info3 = OAMS_OBJTYPE_EIC;
          insertEicDetails();
          sendAlarm = ONE;
          break;
        case INFO_CARD_INSERTED_PM_OAM:
          LOG_PRINT(LOG_DEBUG,"updatePresentCardDetails: Alarm Received INFO_CARD_INSERTED_PM_OAM.");
          LOG_PRINT(LOG_DEBUG,"updatePresentCardDetails: CFG will insert EIC Card entry.");
          sysAlarm->info3 = OAMS_OBJTYPE_EIC;
          insertEicDetails();
          sendAlarm = ONE;
          break;
        case INFO_PEER_EJECTED_PM_OAM:
          LOG_PRINT(LOG_DEBUG,"updatePresentCardDetails: Alarm Received INFO_PEER_EJECTED_PM_OAM.");
          sysAlarm->info3 = OAMS_OBJTYPE_ICC;
          sendAlarm = ONE;
          break;

        case INFO_PEER_CARDSTATE_CHANGE_PM_OAM:
          LOG_PRINT(LOG_DEBUG,"updatePresentCardDetails: Alarm Received INFO_PEER_CARDSTATE_CHANGE_PM_OAM.");
          LOG_PRINT(LOG_DEBUG,"updatePresentCardDetails: CFG will Insert ICC Mate Card entry.");
          sysAlarm->info3 = OAMS_OBJTYPE_ICC;
          insertIccMateCardDetails();
          sendAlarm = ONE;
          break;

        case INFO_PEER_INSERTED_PM_OAM:
          LOG_PRINT(LOG_DEBUG,"updatePresentCardDetails: Alarm Received INFO_PEER_INSERTED_PM_OAM.");
          LOG_PRINT(LOG_DEBUG,"updatePresentCardDetails: CFG will Insert ICC Mate Card entry.");
          sysAlarm->info3 = OAMS_OBJTYPE_ICC;
          insertIccMateCardDetails();
          sendAlarm = ONE;
          break;
      }
      LOG_PRINT(LOG_DEBUG,"updatePresentCardDetails: CFG will update Trunk Port Details.");
      updateChasisFrameTbl();
      updateTrunkPorts();  
      updateDspInfo();
      /* Commented in issue #27963*/
      //updateDspInfo();

      if ( (sendAlarm == ONE)  && (gCfgAlarmBuf != NULL))
      {
        cfgSendMessage(gCfgAlarmBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
        DalocOrdBuf((I_Void *)gCfgAlarmBuf);
        gCfgAlarmBuf = NULL;
      }
    }
    else
    {
      LOG_PRINT(LOG_INFO,"updatePresentCardDetails: No Alarm was received ");
    }

    /*BSC R2.0 Changes Starts*/
    if( (gCfgState == CFG_READY)  && 
        ( (gCfgAlarmIdRcvd == INFO_BPM_EIC_ENABLED) ||
          (gCfgAlarmIdRcvd == INFO_PEER_CARDSTATE_CHANGE_PM_OAM) ||
          (updateEicDetail == TRUE) )  ) 
    {
      copySystemDetails();
#if 0
      /*Temp Changes for marking EIC-ENABLE as BPM is not sending correct State*/  
      if(gCfgAlarmIdRcvd == INFO_BPM_EIC_ENABLED)
      { 
        slotId = (I_U8)gEnabledEicSlotId;
        LOG_PRINT(DEBUG,"Temp Changes for marking EIC-ENABLE : stored slot:%d ",slotId );    
        if(gSystemDetails->eicInfo[0].slotID == slotId)
        {
          gSystemDetails->eicInfo[0].cardOperState = BPM_EIC_ENABLE;
          LOG_PRINT(DEBUG,"Temp Changes for marking EIC-ENABLE : marking slot:%d as enable", slotId );    
        } 
        else
        {
          LOG_PRINT(DEBUG,"Temp Changes for marking EIC-ENABLE : marking slot:%d as enable", gSystemDetails->eicInfo[1].slotID );    
          gSystemDetails->eicInfo[1].cardOperState = BPM_EIC_ENABLE;
        }    
      }
      /*Temp Changes for marking EIC-ENABLE as BPM is not sending correct State*/  
#endif
      updateSystemDetails();  
      /* Commented in issue #27963*/
      //updateDspInfo();
      if(gCfgAlarmIdRcvd == INFO_PEER_CARDSTATE_CHANGE_PM_OAM)
      { 
        LOG_PRINT(DEBUG,"INFO_PEER_CARDSTATE_CHANGE_PM_OAM rcvd going to insert Mate details"); 
        insertIccMateCardDetails();
      }
      else
      {  
        LOG_PRINT(DEBUG,"EIC Enable rcvd going to send trunk state change req.");   
        //insertEicDetails();
        sendBpmIccEicTrunkPortStsReq(gEnabledEicSlotId);
#if 0 
        if(sendTrunkStateChangeReq() == CFG_FAILURE)
        {
          LOG_PRINT(LOG_DEBUG,"initializingCfg: No Trunk is in Enable state. Sending ClkSrcConfig for slotid:%d",
              gEnabledEicSlotId);
          if((gEnabledEicSlotId != 0) && (isClkConfiguredOnSlotId(gEnabledEicSlotId) == TRUE) ) 
          {
            if(sendClockSourceConfigReq() == CFG_FAILURE)
              gCfgAlarmIdRcvd = 0; 
          } 
          else
          {
            gCfgAlarmIdRcvd = 0; 
          } 
          gEnabledEicSlotId = 0;
        }
#endif
      }
      /*Mantis id 28856 start */
      if ( updateDspDetail == TRUE )
      {
        LOG_PRINT(DEBUG,"Going to update DSP details as SW_ACT_SUCC rcvd for DSP");
        insertDspDetails();
        updateDspDetail = FALSE;
      }
      else
      {  
        sendRequestForDspAvailableReleases();
        sendRequestForEicDspAvailableReleases();
      }
      /*Mantis id 28856 Ends */
    }
    /*Changes for R2.3.4 Starts*/
    else if((gCfgState == CFG_READY)  && 
        (gCfgAlarmIdRcvd == INFO_FAN_TRAY_INSERTED) )
    {
      LOG_PRINT(DEBUG,"Going Tp update Fan Tray Details as FanTray inserted Alarm received"); 
      copySystemDetails();
      for(i = 0; i< MAX_NUM_FAN_TRAY; i++)
      {  
        fanTrayObjInfo = gSystemDetails->fanTrayInfo[i];
        insertFanTrayDetails(fanTrayObjInfo); 
      }
      gCfgAlarmIdRcvd = 0; 
      DalocOrdBuf((I_Void *)gSystemDetails);
      gSystemDetails = NULL;
    }
    else if((gCfgState == CFG_READY)  && 
        (gCfgAlarmIdRcvd == INFO_PSU_CARD_INSERTED) )
    {
      LOG_PRINT(DEBUG,"Going Tp update Psu card Details as PsuCard inserted Alarm received"); 
      copySystemDetails();
      insertPsuCardDetails(gSystemDetails->psuInfo[0]);
      if(gSystemDetails->psuInfo[0].peerCardPresence != I_TRUE)
      {
        gSystemDetails->psuInfo[1].frameID = gSystemDetails->psuInfo[0].frameID;
        if(gSystemDetails->psuInfo[0].slotID == PSU0_SLOTID)
          gSystemDetails->psuInfo[1].slotID = PSU1_SLOTID;
        else
          gSystemDetails->psuInfo[1].slotID = PSU0_SLOTID;

        gSystemDetails->psuInfo[1].cardOperState = CARDSTATE_ABSENT;
      }
      insertPsuCardDetails(gSystemDetails->psuInfo[1]);
      gCfgAlarmIdRcvd = 0; 
      DalocOrdBuf((I_Void *)gSystemDetails);
      gSystemDetails = NULL;
    } 
    /*Changes for R2.3.4 Ends*/

    /*BSC R2.0 Changes Ends*/

#if 0
    if ( updateEicDetail == TRUE )
    {
      LOG_PRINT(DEBUG,"Going to update EIC details as SW_ACT_SUCC rcvd for EIC");
      updateChasisFrameTbl();
      insertEicDetails();
      updateTrunkPorts();
      updateDspInfo();
      updateEicDetail = FALSE;
    }
#endif

    /*Changes for Mantis 11329 start */
    if(updateEicDetail == TRUE)
    {
      LOG_PRINT(DEBUG,"Sending Request For EIC Available Releases");
      sendRequestForEicAvailableReleases();
      //insertEicDetails();
      updateEicDetail = FALSE;
    }

    /*Changes for Mantis 11329 END */

    if ( updateDspDetail == TRUE )
    {
      LOG_PRINT(DEBUG,"Going to update DSP details as SW_ACT_SUCC rcvd for DSP");
      insertDspDetails();
      updateDspDetail = FALSE;
    }
    LOG_PRINT(LOG_INFO,"updatePresentCardDetails: Exiting from function");
  }

  /********************************* Function  Header********************************
    Function Name:       updateTrunkPorts()
Parameters:          void
Return type:         void
Purpose:             To update the Trunk Port Details in TrunkPortTable
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/
  I_Void updateTrunkPorts()
  {
    OamOilCfgPresentCardInfoResp *oamOilCfgPresentCardInfoRespPtr = NULL;

    LOG_PRINT(LOG_INFO,"updateTrunkPorts: Entering from Function");
    oamOilCfgPresentCardInfoRespPtr = (OamOilCfgPresentCardInfoResp *)((I_U8 *)gCfgMsgBuf);
    updateTrunkPortDetails(oamOilCfgPresentCardInfoRespPtr->cardInfo.portInfo);
    LOG_PRINT(LOG_INFO,"updateTrunkPorts: Exiting from Function");

  }


  /********************************* Function  Header********************************
    Function Name:       updateTrunkPortDetails()
Parameters:          sTrunkPortDetails portInfo
Return type:         void
Purpose:             To update the Trunk Port Details in TrunkPortTable
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/
  I_Void updateTrunkPortDetails(sTrunkPortDetails portInfo)
  {
    TrunkPortTableApi trunkPortTable;
    TrunkPortTableApi *outTrunkPortData = NULL;
    TrunkPortTableApi *t = NULL;
    TrunkPortTableIndices trunkPortTableIndices;
    I_U16 outSize = 0;
    I_U32 outRows = 0;
    I_U16 outEicSize = 0;
    I_U32 outEicRows = 0;
    I_U32 count = 0;
    I_U32 rowCount = 0;
    I_S32 retVal = 0;
    EicCardInfoTableApi *eicCardInfoTableApiPtr=NULL;
    /*BSC R2.0 Changes Starts*/
    TrunkPortStatusTableApi trunkPortStsTbl;
    TrunkPortStatusTableApi *outTrunkPortStsData = NULL;
    TrunkPortStatusTableApi *tSts = NULL;
    TrunkPortStatusTableIndices trunkPortStsIndcs;
    I_U16 outStsSize = 0;
    I_U32 outStsRows = 0;
    I_U8 chasisFrameId = 0;
    I_U8 slotId = 0;
    I_S32 ret;
    /*BSC R2.0 Changes Ends*/

    LOG_PRINT(LOG_INFO,"updateTrunkPortDetails: Entering from Function");
    retVal =getallTrunkPortTable(&outTrunkPortData, &outRows, &outSize);
    //Update data received from OIL
    if(retVal == CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"updateTrunkPortDetails: Get All on TrunkPort Table is succeded. CFG is updating data from in Table");
    }
    else if (retVal == DBLIBERR_PTOPAGE_HAS_NO_ROWS)
    {
      LOG_PRINT(LOG_MAJOR,"updateTrunkPortDetails: Get All on TrunkPort Table is failed(No ROW Exist in DB).      This Should happen only in case of system startup just after installation, CFG will insert data in DB");
    }
    else
    {
      LOG_PRINT(LOG_CRITICAL,"updateTrunkPortDetails:getallTrunkPortTable failed DB returned error [%d] :%s line:%d", retVal, __FUNCTION__,__LINE__);
    }  
    retVal =getallTrunkPortStatusTable(&outTrunkPortStsData, &outStsRows, &outStsSize);
    //Update data received from OIL
    if(retVal == CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"updateTrunkPortDetails:getallTrunkPortStatusTable: CFG is updating data from in Table");
    }
    else
    {
      LOG_PRINT(LOG_INFO,"updateTrunkPortDetails: getallTrunkPortStatusTable. CFG is inserting fresh data");
    }
#ifdef EIC_6670 
    /*Mantis 6670 Fixed: Gaurav Bhatnagar*/
    if(getallEicCardInfoTable(&eicCardInfoTableApiPtr, &outEicRows, &outEicSize) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"updateTrunkPortDetails: There is no EIC Card Details Present in DB");
    }
#endif
    if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
    {
      LOG_PRINT(LOG_MAJOR,"getActiveIccSlotId Db call failed ErrorCause: %d",ret); 
    }

    LOG_PRINT(LOG_DEBUG,"updateTrunkPortDetails: Received numPorts:: %d" , portInfo.numOfPort);

    for(count = 0 ; count <  MAX_PORT ; count++)
    {
      LOG_PRINT(LOG_DEBUG,"updateTrunkPortDetails: Received FrameId:: %d, SlotId:: %d, PortId:: %d" , portInfo.portInfo[count].frameID, portInfo.portInfo[count].slotID, portInfo.portInfo[count].portID);

      trunkPortTable.chasisFrameId = portInfo.portInfo[count].frameID ;   
      trunkPortTable.slotId = portInfo.portInfo[count].slotID ;   
      trunkPortTable.trunkPortId = portInfo.portInfo[count].portID ;   
      /* Changes For E1-T1 : Start */ 
      if(gBscTrunkType == BPM_TRUNK_TYPE_E1)
      { 
        LOG_PRINT(INFO,"TrunkType :%d",BPM_TRUNK_TYPE_E1); 
        trunkPortTable.trunkType = BPM_TRUNK_TYPE_E1 ;  
      }
      else
      {
        LOG_PRINT(INFO,"TrunkType :%d",BPM_TRUNK_TYPE_T1); 
        trunkPortTable.trunkType = BPM_TRUNK_TYPE_T1 ;  
      }  
      /* Changes For E1-T1 : End */ 
      trunkPortTable.trunkFramingOption = portInfo.portInfo[count].trunkFramingOption ;   
      trunkPortTable.encodeType = portInfo.portInfo[count].encodeType ;   
      trunkPortTable.sigStrength = portInfo.portInfo[count].sigStrength ;   
      trunkPortTable.physicalTrunkPortState = DEACTIVATED; 
      trunkPortTable.loopback = BPM_REMOTE_LOOPBACK  ;
      trunkPortTable.loopType = BPM_TRUNK_LOOPBACK_DISABLE ;

      /* Trunk UsageType Changes : Start  */
      trunkPortTable.usageType = SYS_E1_USAGE_NONE ;   
      /* Trunk UsageType Changes : End   */

      /*BSC R2.0 Changes Starts*/
      trunkPortStsTbl.chasisFrameId = portInfo.portInfo[count].frameID;
      trunkPortStsTbl.slotId = portInfo.portInfo[count].slotID;
      trunkPortStsTbl.trunkPortId = portInfo.portInfo[count].portID ;
      trunkPortStsTbl.oprStatus = DISABLED; 

      if(portInfo.portInfo[count].isPortPresent == BPM_TRUE)
      {
        trunkPortStsTbl.physicalPresenceState = PRESENT; 
      }
      else 
      {
        if(trunkPortStsTbl.chasisFrameId == 0 ||
            trunkPortStsTbl.slotId == 0)
        {
          trunkPortTable.chasisFrameId = chasisFrameId ;   
          trunkPortStsTbl.chasisFrameId = chasisFrameId;
          if((count >= 0) && (count <= 7))
          { 
            trunkPortTable.slotId = slotId;
            trunkPortStsTbl.slotId = slotId;
          }
          else if((count >= 8) && (count <= 23))  
          {
            trunkPortTable.slotId = EIC0_CARD;
            trunkPortStsTbl.slotId = EIC0_CARD;
          } 
          else if((count >= 24) && (count <= 39))  
          {  
            trunkPortTable.slotId = EIC1_CARD;
            trunkPortStsTbl.slotId = EIC1_CARD;
          } 
          LOG_PRINT(LOG_CRITICAL,"updateTrunkPortDetails: Received all ZERO data in Hw Inventory from BPM \            for trunkport no %d FrameId:: %d, SlotId:: %d, PortId:: %d" , count,portInfo.portInfo[count].frameID, portInfo.portInfo[count].slotID, portInfo.portInfo[count].portID);
          trunkPortTable.trunkPortId = count ;   
          trunkPortStsTbl.trunkPortId = count;
          portInfo.portInfo[count].portID=count;
          portInfo.portInfo[count].slotID=trunkPortTable.slotId;
          portInfo.portInfo[count].frameID=chasisFrameId;
        }
        trunkPortStsTbl.physicalPresenceState = NOT_PRESENT; 
      }
      /*BSC R2.0 Changes Ends*/

      if(outTrunkPortData != NULL)
      {
        for(rowCount = 0 ; rowCount < outRows ; rowCount++)
        {
          t = (TrunkPortTableApi *)((I_U8 *)outTrunkPortData + (rowCount * outSize));

          if(t->trunkPortId == portInfo.portInfo[count].portID)
          {
            LOG_PRINT(LOG_DEBUG,"updateTrunkPortDetails: TrunkPort already exist, Updating Entry with DB:: ");
            trunkPortTable.physicalTrunkPortState = t->physicalTrunkPortState ;   
            trunkPortTable.trunkFramingOption = t->trunkFramingOption ;   
            trunkPortTable.encodeType = t->encodeType ;   
            trunkPortTable.sigStrength = t->sigStrength ;
            trunkPortTable.loopback = t->loopback ;
            trunkPortTable.loopType = t->loopType ;

            /* Trunk UsageType Changes : Start  */
            trunkPortTable.usageType = t->usageType ;   
            /* Trunk UsageType Changes : End   */
            LOG_PRINT(LOG_DEBUG,"updateTrunkPortDetails:PhyTrunkPortSts:%d,framingOpt:%d,encodeType:%d,usageType:%d",
                t->physicalTrunkPortState,t->trunkFramingOption,t->encodeType, t->usageType );
          }
        }//for
      }  

      if(outTrunkPortStsData != NULL)
      {
        for(rowCount = 0 ; rowCount < outStsRows ; rowCount++)
        {
          tSts = (TrunkPortStatusTableApi *)((I_U8 *)outTrunkPortStsData + (rowCount * outStsSize));

          if(tSts->trunkPortId == portInfo.portInfo[count].portID)
          {
            LOG_PRINT(LOG_DEBUG,"updateTrunkPortSts : TrunkPort already exist, Updating Entry with DB:: ");
            trunkPortStsTbl.oprStatus = tSts->oprStatus;
          }
        }
      } 

      LOG_PRINT(LOG_INFO,"updateTrunkPortDetails:Inserted in TrunkPort Table for TrunkPortId:%d PhyTrunkPortSts:%d",
          trunkPortTable.trunkPortId,trunkPortTable.physicalTrunkPortState );

      if( updateTrunkPortTable(&trunkPortTable) != CLIB_SUCCESS  )
      {
        if(insertTrunkPortTable(&trunkPortTable) != CLIB_SUCCESS)
          LOG_PRINT(DEBUG,"updateTrunkPortDetails: Can not insert in TrunkPort Table."); 
      }
      /*BSC R2.0 Changes Starts*/
      if( updateTrunkPortStatusTable(&trunkPortStsTbl) != CLIB_SUCCESS  )
      {
        if(insertTrunkPortStatusTable(&trunkPortStsTbl) != CLIB_SUCCESS)
          LOG_PRINT(LOG_CRITICAL,"updateTrunkPortDetails: Can not insert in TrunkPort Table. Initialization Failed");
      }
      /*BSC R2.0 Changes Ends*/
    }//for numoOfPorts

    if(outTrunkPortData != NULL)
    {
      if(getActiveIccSlotId( &chasisFrameId, &slotId) == CLIB_SUCCESS)
      {
        if(slotId == ICCSELFCARD)
          slotId = ICCMATECARD; 
        else
          slotId = ICCSELFCARD; 
        /*Delete the data from TrunkPortTable*/
        for(rowCount = 0 ; rowCount < 8 ; rowCount++)
        {
          trunkPortTableIndices.chasisFrameId = chasisFrameId ;
          trunkPortTableIndices.slotId = slotId ;
          trunkPortTableIndices.trunkPortId =  rowCount;

          trunkPortStsIndcs.chasisFrameId = chasisFrameId ;
          trunkPortStsIndcs.slotId = slotId ;
          trunkPortStsIndcs.trunkPortId =  rowCount;

          LOG_PRINT(LOG_INFO,"updateTrunkPortDetails: Entry will be deleted from TrunkPort Table for TrunkPort Id:: %d Slot Id %d ",rowCount,slotId);
          if(deleteTrunkPortTable(&trunkPortTableIndices) != CLIB_SUCCESS)
          {
            LOG_PRINT(LOG_CRITICAL,"updateTrunkPortDetails: Can not Delete row from TrunkPort Table");
#ifdef EIC_6670
            if(eicCardInfoTableApiPtr != NULL)
            {
              free(eicCardInfoTableApiPtr);
            }
#endif

            if(outTrunkPortData != NULL)
            {
              free(outTrunkPortData);
            }
            if(outTrunkPortStsData != NULL)
            {
              free(outTrunkPortStsData);
            }
            return;
          }
          if(deleteTrunkPortStatusTable(&trunkPortStsIndcs) != CLIB_SUCCESS)
          {
            LOG_PRINT(LOG_CRITICAL,"updateTrunkPortDetails: Can not Delete row from TrunkPortsts Table. Initialization Failed");
          } 
        }/*for loop of Delete the data from TrunkPortTable Ends*/

      }
    }
    if(outTrunkPortData != NULL)
    {
      free(outTrunkPortData);
    }
    if(outTrunkPortStsData != NULL)
    {
      free(outTrunkPortStsData);
    }
#ifdef EIC_6670
    if(eicCardInfoTableApiPtr != NULL)
    {
      free(eicCardInfoTableApiPtr);
    }
#endif  
    LOG_PRINT(LOG_INFO,"updateTrunkPortDetails: Exiting from Function");

  }

  /********************************* Function  Header********************************
    Function Name:       insertEicDetails()
Parameters:          void
Return type:         void
Purpose:             To insert EIC Card details for which alarm was received.
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void insertEicDetails()
  {
    OamOilCfgPresentCardInfoResp *oamOilCfgPresentCardInfoRespPtr =NULL;
    I_U8 slotId; 
    LOG_PRINT(LOG_INFO,"insertEicDetails: Entering in function");
    oamOilCfgPresentCardInfoRespPtr = (OamOilCfgPresentCardInfoResp *)((I_U8 *)gCfgMsgBuf);

    deleteRowsFromEicCardInfo();
    deleteRowsFromSwmNodeTable();

    LOG_PRINT(INFO,"Num of Remote Cards: %d", oamOilCfgPresentCardInfoRespPtr->cardInfo.numRemoteCards);
    /*BSC R2.0 Changes Starts*/
#if 0
    for ( index = ZERO; index < oamOilCfgPresentCardInfoRespPtr->cardInfo.numRemoteCards; index++ )
    {
      insertEicCardDetails(oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[index]);
    }
#endif 
    LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating Eic Card Detail [%d]",0);
    if( oamOilCfgPresentCardInfoRespPtr->cardInfo.numRemoteCards == 0 )
    {
      oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[0].frameID = 
        oamOilCfgPresentCardInfoRespPtr->cardInfo.selfInfo.frameID;
      oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[0].slotID = EIC0_CARD ; 
      oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[0].cardOperState = CARDSTATE_ABSENT;

      oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[1].frameID = 
        oamOilCfgPresentCardInfoRespPtr->cardInfo.selfInfo.frameID;
      oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[1].slotID = EIC1_CARD ; 
      oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[1].cardOperState = CARDSTATE_ABSENT;
    }
    slotId = (I_U8) gEnabledEicSlotId;
#if 0
    if(oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[0].slotID == slotId)
    {
      oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[0].cardOperState = BPM_EIC_ENABLE;
    }
#endif
    insertEicCardDetails(oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[0]); 

    LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating Eic Card Detail [%d]",1);
    if( oamOilCfgPresentCardInfoRespPtr->cardInfo.numRemoteCards == 1 )
    {
      oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[1].frameID = 
        oamOilCfgPresentCardInfoRespPtr->cardInfo.selfInfo.frameID;

      if(oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[0].slotID == EIC1_CARD)
        oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[1].slotID = EIC0_CARD ; 
      else
        oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[1].slotID = EIC1_CARD ; 

      oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[1].cardOperState = CARDSTATE_ABSENT;
    }
#if 0
    if(oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[1].slotID == slotId)
    {
      oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[1].cardOperState = BPM_EIC_ENABLE;
    }
#endif
    insertEicCardDetails(oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[1]);
    /*BSC R2.0 Changes Ends*/

    /* inserting EIC details in SwMNodeTable */

    //cfgInitEicSwMNodeTable();
    //cfgInitDspSwMNodeTable();
#if 0
    if (gFirstEicAvailResp == SW_ACTIVATION_IN_PROGRESS )
      gFirstEicAvailResp = TRUE;
    else
      gFirstEicAvailResp = FALSE; /* To update only downloaded verison of SwMNodeTable */
#endif
    sendRequestForEicAvailableReleases();

    LOG_PRINT(LOG_INFO,"insertEicDetails: Exiting From function");

  }

  /********************************* Function  Header********************************
    Function Name:       insertIccMateCardDetails()
Parameters:          void
Return type:         void
Purpose:             To insert ICC Mate Card details for which alarm was received.
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void insertIccMateCardDetails()
  {
    OamOilCfgPresentCardInfoResp *oamOilCfgPresentCardInfoRespPtr =NULL;
    LOG_PRINT(LOG_INFO,"insertIccMateCardDetails: Entering in function");

    oamOilCfgPresentCardInfoRespPtr = (OamOilCfgPresentCardInfoResp *)((I_U8 *)gCfgMsgBuf);

    //   updateCardStateChange(oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo.frameID, oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo.slotID, oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo.cardOperState);
    if(  (oamOilCfgPresentCardInfoRespPtr->cardInfo.totalNumCards - oamOilCfgPresentCardInfoRespPtr->cardInfo.numRemoteCards)  == 1)
    {
      oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo.frameID = oamOilCfgPresentCardInfoRespPtr->cardInfo.selfInfo.frameID;
      if(oamOilCfgPresentCardInfoRespPtr->cardInfo.selfInfo.slotID == ICCSELFCARD)
        oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo.slotID = ICCMATECARD;
      else
        oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo.slotID = ICCSELFCARD;

      if(oamOilCfgPresentCardInfoRespPtr->cardInfo.selfInfo.peerCardPresence != I_TRUE)
        oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo.cardOperState = CARDSTATE_ABSENT;       
      else
        oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo.cardOperState = CARDSTATE_SHUTDOWN;       
    } 
    insertIccCardDetails(oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo);

    if(oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo.cardOperState != CARDSTATE_ABSENT)
    {
      /* Populating SwMNodeTable */
      cfgInsertIccDetails(oamOilCfgPresentCardInfoRespPtr->cardInfo.mateInfo);
    }

    LOG_PRINT(LOG_INFO,"insertIccMateCardDetails: Exiting From function");
  }

  /********************************* Function  Header********************************
    Function Name:       insertIccSelfCardDetails()
Parameters:          void
Return type:         void
Purpose:             To insert ICC Self Card details for which alarm was received.
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void insertIccSelfCardDetails()
  {
    OamOilCfgPresentCardInfoResp *oamOilCfgPresentCardInfoRespPtr =NULL;
    LOG_PRINT(LOG_INFO,"insertIccSelfCardDetails: Entering in function");

    oamOilCfgPresentCardInfoRespPtr = (OamOilCfgPresentCardInfoResp *)((I_U8 *)gCfgMsgBuf);
    insertIccCardDetails(oamOilCfgPresentCardInfoRespPtr->cardInfo.selfInfo);

    LOG_PRINT(LOG_INFO,"insertIccSelfCardDetails: Exiting From function");

  }

  /********************************* Function  Header********************************
    Function Name:       insertIccCardDetails()
Parameters:          sCardObjInfo cardObjInfo
Return type:         void
Purpose:             To insert ICC Card details for which alarm was received.
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void insertIccCardDetails(sCardObjInfo cardObjInfo)
  {
    IccCardInfoTableApi iccCardInfoTableApi;

    bzero(&iccCardInfoTableApi,sizeof(IccCardInfoTableApi));

    LOG_PRINT(LOG_INFO,"insertIccCardDetails: Entering in function");
    LOG_PRINT(LOG_INFO,"insertIccCardDetails: FrameId [%d], SlotId [%d]", cardObjInfo.frameID, cardObjInfo.slotID);

    iccCardInfoTableApi.chasisFrameId = cardObjInfo.frameID ;
    iccCardInfoTableApi.slotId = cardObjInfo.slotID ;

    if(cardObjInfo.cardOperState == CARDSTATE_ABSENT)
    {
      iccCardInfoTableApi.physicalPresenceState = NOT_PRESENT;
      iccCardInfoTableApi.cardType = BPM_CARD_ICC; 
      iccCardInfoTableApi.cardOperationalState = cardObjInfo.cardOperState ;
    }
    else if(cardObjInfo.cardOperState ==  CARDSTATE_SHUTDOWN)
    {
      iccCardInfoTableApi.physicalPresenceState = PRESENT;
      iccCardInfoTableApi.cardType = BPM_CARD_ICC; 
      iccCardInfoTableApi.cardOperationalState = cardObjInfo.cardOperState ;
    } 
    else
    {
      LOG_PRINT(LOG_INFO,"Inserting ICC Details Value iccCardInfoTableApi.physicalPresenceState = %d iccCardInfoTableApi.cardOperationalState= %d",iccCardInfoTableApi.physicalPresenceState,iccCardInfoTableApi.cardOperationalState);

      iccCardInfoTableApi.cardType = cardObjInfo.cardType ;
      memcpy(iccCardInfoTableApi.cardSerialNumber , cardObjInfo.cardSerialNumber ,20);
      /*BSc R2.0 Changes Starts*/
      iccCardInfoTableApi.physicalPresenceState = PRESENT;
      /*BSc R2.0 Changes Ends*/
      iccCardInfoTableApi.cardOperationalState = cardObjInfo.cardOperState ;
      iccCardInfoTableApi.oneP2PowerModuleVoltageStatus = cardObjInfo.oneP2PowerModuleVoltageStatus ;
      iccCardInfoTableApi.twoP5PowerModuleVoltageStatus  = cardObjInfo.twoP5PowerModuleVoltageStatus ;
      iccCardInfoTableApi.oneP2DSPVoltageStatus  = cardObjInfo.oneP2DSPVoltageStatus ;
      iccCardInfoTableApi.twoP5PowerModuleTemperatureStatus = cardObjInfo.twoP5PowerModuleTempStatus ;
      iccCardInfoTableApi.threeP3PowerModuleTemperatureStatus = cardObjInfo.threeP3PowerModuleTempStatus;
      iccCardInfoTableApi.hotSwapPowerGood1Status = cardObjInfo.hotSwapPowerGood1  ;
      iccCardInfoTableApi.hotSwapPowerGood3Status  = cardObjInfo.hotSwapPowerGood3  ;
      iccCardInfoTableApi.cpldVersionMajor = cardObjInfo.cpldVersion.major  ;
      iccCardInfoTableApi.cpldVersionMinor = cardObjInfo.cpldVersion.minor  ;
      iccCardInfoTableApi.cpldVersionRevision = cardObjInfo.cpldVersion.revision  ;
      iccCardInfoTableApi.ucVersionMajor = cardObjInfo.uCVersion.major  ;
      iccCardInfoTableApi.ucVersionMinor = cardObjInfo.uCVersion.minor  ;
      iccCardInfoTableApi.ucVersionRevision = cardObjInfo.uCVersion.revision  ;
      iccCardInfoTableApi.activeKernelVersionMajor= cardObjInfo.activeKernelVersion.major ;
      iccCardInfoTableApi.activeKernelVersionMinor = cardObjInfo.activeKernelVersion.minor  ;
      iccCardInfoTableApi.activeKernelVersionRevision = cardObjInfo.activeKernelVersion.revision  ;
      iccCardInfoTableApi.backupKernelVersionMajor = cardObjInfo.backUpKernelVersionInfo.major  ;
      iccCardInfoTableApi.backupKernelVersionMinor = cardObjInfo.backUpKernelVersionInfo.minor  ;
      iccCardInfoTableApi.backupKernelVersionRevision = cardObjInfo.backUpKernelVersionInfo.revision  ;
      iccCardInfoTableApi.uBootVersionMajor = cardObjInfo.uBootVersion.major  ;
      iccCardInfoTableApi.uBootVersionMinor = cardObjInfo.uBootVersion.minor  ;
      iccCardInfoTableApi.uBootVersionRevision = cardObjInfo.uBootVersion.revision  ;
      iccCardInfoTableApi.activeRamdiskVersionMajor = cardObjInfo.activeRamDiskVersion.major  ;
      iccCardInfoTableApi.backupRamdiskVersionMinor = cardObjInfo.backUpRamDiskVersion.minor  ;
      iccCardInfoTableApi.backupRamdiskVersionRevision = cardObjInfo.backUpRamDiskVersion.revision  ;
      iccCardInfoTableApi.backupRamdiskVersionMajor = cardObjInfo.backUpRamDiskVersion.major  ;
      iccCardInfoTableApi.activeRamdiskVersionMinor = cardObjInfo.activeRamDiskVersion.minor  ;
      iccCardInfoTableApi.activeRamdiskVersionRevision = cardObjInfo.activeRamDiskVersion.revision  ;
      iccCardInfoTableApi.activeSwVersionMajor = cardObjInfo.activeRelVersion.major  ;
      iccCardInfoTableApi.activeSwVersionMinor = cardObjInfo.activeRelVersion.minor  ;
      iccCardInfoTableApi.activeSwVersionRevision = cardObjInfo.activeRelVersion.revision  ;
      iccCardInfoTableApi.backupSwVersionMajor = cardObjInfo.backUpRelVersion.major  ;
      iccCardInfoTableApi.backupSwVersionMinor = cardObjInfo.backUpRelVersion.minor  ;
      iccCardInfoTableApi.backupSwVersionRevision = cardObjInfo.backUpRelVersion.revision  ;
      iccCardInfoTableApi.downloadedSwVersionMajor = cardObjInfo.downLoadedRelVersion.major  ;
      iccCardInfoTableApi.downloadedSwVersionMinor = cardObjInfo.downLoadedRelVersion.minor  ;
      iccCardInfoTableApi.downloadedSwVersionRevision = cardObjInfo.downLoadedRelVersion.revision  ;
    }
    if(updateIccCardInfoTable(&iccCardInfoTableApi) != CLIB_SUCCESS)
    {
      if(insertIccCardInfoTable(&iccCardInfoTableApi) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"insertIccCardDetails: Can not insert in IccCardInfo Table. ");
        return;
      }
    }
    LOG_PRINT(LOG_INFO,"insertIccCardDetails: Exiting from function");

  }


  /********************************* Function  Header********************************
    Function Name:       insertEicCardDetails()
Parameters:          sEicObjInfo cardObjInfo
Return type:         void
Purpose:             To insert EIC Card details for which alarm was received.
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void insertEicCardDetails(sEicObjInfo cardObjInfo)
  {
    EicCardInfoTableApi eicCardInfoTableApi;
    EicCardInfoTableIndices inData;
    EicCardInfoTableApi *outData;
    LOG_PRINT(LOG_INFO,"insertEicCardDetails: Entering in function");

    inData.chasisFrameId = cardObjInfo.frameID ;
    inData.slotId = cardObjInfo.slotID ;

    bzero(&eicCardInfoTableApi,sizeof(EicCardInfoTableApi));

    eicCardInfoTableApi.chasisFrameId = cardObjInfo.frameID ;
    eicCardInfoTableApi.slotId = cardObjInfo.slotID ;
    if(cardObjInfo.cardOperState == CARDSTATE_ABSENT)
    {
      eicCardInfoTableApi.physicalPresenceState = NOT_PRESENT;
      eicCardInfoTableApi.cardType = BPM_CARD_EIC;
      eicCardInfoTableApi.cardOperationalState = BPM_EIC_DISABLE;
    }
    else
    {
      eicCardInfoTableApi.cardType = cardObjInfo.cardType ;
      memcpy(eicCardInfoTableApi.cardSerialNumber ,cardObjInfo.cardSerialNumber ,20);
      /*Temp Changes for Eic operState*/
      //eicCardInfoTableApi.cardOperationalState = cardObjInfo.cardOperState ;
      eicCardInfoTableApi.cardOperationalState = BPM_EIC_ENABLE; 
      /*Temp Changes for Eic operState*/
      /*BSc R2.0 Changes Starts*/
      eicCardInfoTableApi.physicalPresenceState = PRESENT;
      /*BSc R2.0 Changes Ends*/
      eicCardInfoTableApi.numTrunkPort = cardObjInfo.numTrunkPort ;
      eicCardInfoTableApi.cpldVersionMajor = cardObjInfo.cpldVersion.major  ;
      eicCardInfoTableApi.cpldVersionMinor = cardObjInfo.cpldVersion.minor  ;
      eicCardInfoTableApi.cpldVersionRevision  = cardObjInfo.cpldVersion.revision   ;
      eicCardInfoTableApi.ucVersionMajor = cardObjInfo.uCVersion.major  ;
      eicCardInfoTableApi.ucVersionMinor = cardObjInfo.uCVersion.minor  ;
      eicCardInfoTableApi.ucVersionRevision = cardObjInfo.uCVersion.revision  ;
      eicCardInfoTableApi.kernelVersionMajor = cardObjInfo.kernelVersion.major  ;
      eicCardInfoTableApi.kernelVersionMinor = cardObjInfo.kernelVersion.minor  ;
      eicCardInfoTableApi.kernelVersionRevision = cardObjInfo.kernelVersion.revision  ;
      eicCardInfoTableApi.uBootVersionMajor = cardObjInfo.uBootVersion.major;
      eicCardInfoTableApi.uBootVersionMinor = cardObjInfo.uBootVersion.minor  ;
      eicCardInfoTableApi.uBootVersionRevision = cardObjInfo.uBootVersion.revision  ;
      eicCardInfoTableApi.ramDiskVersionMajor = cardObjInfo.ramDiskVersion.major  ;
      eicCardInfoTableApi.ramDiskVersionMinor = cardObjInfo.ramDiskVersion.minor  ;
      eicCardInfoTableApi.ramDiskVersionRevision = cardObjInfo.ramDiskVersion.revision  ;
      eicCardInfoTableApi.activeSwVersionMajor = cardObjInfo.activeRelVersion.major  ;
      eicCardInfoTableApi.activeSwVersionMinor = cardObjInfo.activeRelVersion.minor  ;
      eicCardInfoTableApi.activeSwVersionRevision = cardObjInfo.activeRelVersion.revision  ;
      eicCardInfoTableApi.backupSwVersionMajor = cardObjInfo.backUpRelVersion.major  ;
      eicCardInfoTableApi.backupSwVersionMinor = cardObjInfo.backUpRelVersion.minor  ;
      eicCardInfoTableApi.backupSwVersionRevision = cardObjInfo.backUpRelVersion.revision  ;
      eicCardInfoTableApi.downloadedSwVersionMajor = cardObjInfo.downLoadedRelVersion.major  ;
      eicCardInfoTableApi.downloadedSwVersionMinor = cardObjInfo.downLoadedRelVersion.minor  ;
      eicCardInfoTableApi.downloadedSwVersionRevision = cardObjInfo.downLoadedRelVersion.revision  ;
    }

    if(getEicCardInfoTable(&inData,&outData) == CLIB_SUCCESS)
    { 
      eicCardInfoTableApi.cardOperationalState = outData->cardOperationalState;

      if(updateEicCardInfoTable(&eicCardInfoTableApi) == CLIB_SUCCESS)
      {
        LOG_PRINT(DEBUG,"updateEicCardInfoTable is success");
      }
    }
    else
    {
      if(insertEicCardInfoTable(&eicCardInfoTableApi) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"updateEicCardDetails: Can not update EicCardInfo Table. Initialization failed");
        return;
      }
    } 

    LOG_PRINT(LOG_INFO,"insertEicCardDetails: Exiting from function");
  }
  /*BSC CS4.0 : Init changes Ends*/

  /*BSC CS4.0 HA changes Starts*/

#if 0  //R2.0 Changes

  /********************************* Function  Header********************************
    Function Name:       sendTrauStartMsg()
Parameters:          void
Return type:         void
Purpose:             To send Trau Start Message to Trau.
Other Note:          Added for CS4.0
   ************************************************************************************/

  I_Void sendTrauStartMsg()
  {
    LOG_PRINT(LOG_INFO,"sendTrauStartMsg: Entering in function");
    DSmmTrauStartReqMsg TrauStartReqBuff;
    cfgStopTimer();
    //   stopMgsTimer();

    if (gCfgState == CFG_START_TRAU)
    {
      TrauStartReqBuff.hdr.DestId =MGS_DEST_TRAU;
      TrauStartReqBuff.hdr.TotalLength =TRAU_START_SIZE;

      TrauStartReqBuff.trauHdr.ApplicationID = ENT_MGS_TSM;
      TrauStartReqBuff.trauHdr.MessageType   = DSP_COM_MSG_BCAST;
      TrauStartReqBuff.trauHdr.ServiceType   = DSP_TRAU;
      TrauStartReqBuff.trauHdr.Index         = DSP_ALL_INDEX;
      TrauStartReqBuff.trauHdr.MessageID     = TRAU_START;
      TrauStartReqBuff.trauHdr.MessageSize   = TRAU_START_SIZE;

      cfgSendMessage(&TrauStartReqBuff, sizeof(DSmmTrauStartReqMsg), ENT_IPC_TSMIF, EXT_TSM_MSG, 0);
      gMgsWaitForRspFlg =MGS_WT_FOR_MGS_TRAU_START_RESP;

      cfgStartTimer("TSI_TRAU_INIT") ;
      //      startMgsTimer();
    }
    else
    {
      LOG_PRINT(LOG_INFO,"sendTrauStartMsg: Can not start Trau. Failed");
    }
    LOG_PRINT(LOG_INFO,"sendTrauStartMsg: Exiting from function");
  }
#endif


  /********************************* Function  Header*****************************
    Function Name   : rmMsgHandler()
Parameters       : I_Void
Return type       : I_Void
Purpose          : It Handles the messages from RM.
Other Note        : Added For BSC CS4.0 HA Implementation
   *******************************************************************************/
  I_Void rmMsgHandler()
  {
    LOG_PRINT(LOG_INFO,"rmMsgHandler: Entering in function ");

    switch (((SysHdr*) gCfgMsgBuf)->msgType)
    {
      case BPM_SELFCARD_STATE_CHANGE:
        stateChangeNotificationHandler();
        break;

      case OAMS_RM_CFG_PEER_SWITCH_CONNECT_ACK:
        if(gNextCardState == CARDSTATE_ACTIVE_IN_PROGRESS && gCurrentCardState == CARDSTATE_IN_SERVICE)
        {
        }
        else
        {
          if (getScmSubProcState() == OAMS_CFG_GRHM_SWITCH_CONNECT)
          {
            linkSwitchConnectAckHandler();
          }
        }
        break;
      case OAMS_RM_CFG_PEER_SWITCH_CONNECT_NACK:
        if(gNextCardState == CARDSTATE_ACTIVE_IN_PROGRESS && gCurrentCardState == CARDSTATE_IN_SERVICE)
        {
        }
        else
        {
          if (getScmSubProcState() == OAMS_CFG_GRHM_SWITCH_CONNECT)
          {
            linkSwitchConnectNackHandler();
          }
        }
        break;
      case OAMS_RM_CFG_SLOTID_REQ:
        selfSlotIdReqHandler();   
        break;

      case OAMS_RM_CFG_SLOTID_RESP:
        selfSlotIdRespHandler();   
        break;
      default:
        break;
    }
    LOG_PRINT(LOG_INFO,"rmMsgHandler: Exiting from function ");
  }

  /* Change For CS4.0 CCU : Start */

  /********************************* Function  Header*****************************
    Function Name   : ccuMsgHandler()
Parameters       : Void
Return type       : Void
Purpose          : It Handles the messages from CCUH.
Other Note        : Added For BSC CS4.0 CCU Implementation
   *******************************************************************************/

  void ccuMsgHandler() 
  {
    LOG_PRINT(LOG_INFO,"ccuMsgHandler: Entering in Function ");

    switch (((SysHdr*) gCfgMsgBuf)->msgType) 
    {
      case OAMS_CCUH_CFG_ALARM_IND: 
        {

          LOG_PRINT(LOG_INFO,"Calling cfgAlarmHandler ");
          cfgAlarmHandler(); 
        }
        break;
      default :
        LOG_PRINT(LOG_INFO,"Not Calling cfgAlarmHandler ");
        break;  
    }      

    LOG_PRINT(LOG_INFO,"ccuMsgHandler: Exiting from function ");

  }


  /* Change For CS4.0 CCU : End */

  /*Changes for R2.0 Starts*/
  void dsphMsgHandler() 
  {
    I_U8 reason;
    I_U32 errCause; 
    DspInfoTableIndices dspInfoTblIndx;
    DspInfoTableApi     *pDspInfoTable;
    OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
    I_U8 activeSlotId = 0;
    LOG_PRINT(LOG_INFO,"dsphMsgHandler: Entering in Function ");
    switch (((SysHdr*) gCfgMsgBuf)->msgType) 
    {
      case OAMS_DSPH_CFG_DSP_LOCK_RESP :
        LOG_PRINT(LOG_DEBUG,"OAMS_DSPH_CFG_DSP_LOCK_RESP received");
        reason = ((OamsDsphCfgDspLockResp *)gCfgMsgBuf)->reason;
        dspInfoTblIndx.chasisFrameId = ((OamsDsphCfgDspLockResp *)gCfgMsgBuf)->frameId;
        dspInfoTblIndx.slotId = ((OamsDsphCfgDspLockResp *)gCfgMsgBuf)->slotId;
        dspInfoTblIndx.dspId = ((OamsDsphCfgDspLockResp *)gCfgMsgBuf)->dspId;
        if(((OamsDsphCfgDspLockResp *)gCfgMsgBuf)->result == OAMS_RSLT_SUCCESS)
        {
          LOG_PRINT(DEBUG,"OAMS_RSLT_SUCCESS in DSP_LOCK_RESP");
          /* MantisId 0028121 Starts */  
          gDspData[dspInfoTblIndx.dspId].dspState = locked;
          /* MantisId 0028121 Starts */  
          if(reason == OAMS_RSN_OPERATORINITIATED )
          {
            LOG_PRINT(DEBUG,"Reason received is OPERATOR INIT in DSP_LOCK_RESP");
            updateDspAdminState(&dspInfoTblIndx,LOCKED);
            cfgSendAckToCm();         
          } 	        
        }
        else
        {
          gDspData[dspInfoTblIndx.dspId].dspState = unlocked;
          errCause = ((OamsDsphCfgDspLockResp *)gCfgMsgBuf)->errCause;
          LOG_PRINT(LOG_MAJOR,"DSPH has given error(%d) in LOCK_RESP",errCause);	
          cfgSendNackToCm(errCause);
        }
        break; 

      case OAMS_DSPH_CFG_DSP_UNLOCK_RESP :
        LOG_PRINT(LOG_DEBUG,"OAMS_DSPH_CFG_DSP_UNLOCK_RESP received");
        reason = ((OamsDsphCfgDspUnlockResp *)gCfgMsgBuf)->reason;
        dspInfoTblIndx.chasisFrameId = ((OamsDsphCfgDspLockResp *)gCfgMsgBuf)->frameId;
        dspInfoTblIndx.slotId = ((OamsDsphCfgDspLockResp *)gCfgMsgBuf)->slotId;
        dspInfoTblIndx.dspId = ((OamsDsphCfgDspLockResp *)gCfgMsgBuf)->dspId;
        if(((OamsDsphCfgDspUnlockResp *)gCfgMsgBuf)->result == OAMS_RSLT_SUCCESS)
        {
          /* MantisId 0028121 Starts */  
          gDspData[dspInfoTblIndx.dspId].dspState = unlocked;
          /* MantisId 0028121 Starts */  
          if(reason == OAMS_RSN_OPERATORINITIATED )
          {
            LOG_PRINT(DEBUG,"Reason received is OPERATOR INIT in DSP_UNLOCK_RESP");
            updateDspAdminState(&dspInfoTblIndx,UNLOCKED);
            cfgSendAckToCm();         
          } 	        
        }
        else
        {
          gDspData[dspInfoTblIndx.dspId].dspState = locked;
          errCause = ((OamsDsphCfgDspUnlockResp *)gCfgMsgBuf)->errCause;
          LOG_PRINT(LOG_MAJOR,"DSPH has given error(%d) in UNLOCK_RESP",errCause);	
          cfgSendNackToCm(errCause);
        }
        break; 

      case OAMS_DSPH_CFG_DSP_RESET_RESP :
        LOG_PRINT(LOG_DEBUG,"OAMS_DSPH_CFG_DSP_RESET_RESP received");

        dspInfoTblIndx.chasisFrameId = ((OamsDsphCfgDspResetResp *)gCfgMsgBuf)->frameId;
        dspInfoTblIndx.slotId = ((OamsDsphCfgDspResetResp *)gCfgMsgBuf)->slotId;
        dspInfoTblIndx.dspId = ((OamsDsphCfgDspResetResp *)gCfgMsgBuf)->dspId;

        if(((OamsDsphCfgDspResetResp *)gCfgMsgBuf)->result == DSP_SUCCESS)
        {
          cfgSendAckToCm();         
        }
        else
        {
          LOG_PRINT(LOG_MAJOR,"dspId(%d) in RESET_RESP Sending NACK",((OamsDsphCfgDspResetResp *)gCfgMsgBuf)->dspId);	
          if(gDspData[((OamsDsphCfgDspResetResp *)gCfgMsgBuf)->dspId].dspState == resetInProgress)
          {
            getDspInfoTable(&dspInfoTblIndx,&pDspInfoTable);
            if (pDspInfoTable->adminState == LOCKED)
            {
              gDspData[dspInfoTblIndx.dspId].dspState = locked;
            }
            else
            {
              gDspData[dspInfoTblIndx.dspId].dspState = unlocked;
            }
            if(pDspInfoTable != NULL)
            {
              free(pDspInfoTable);
            }
          }

          errCause = ((OamsDsphCfgDspResetResp *)gCfgMsgBuf)->errCause;
          LOG_PRINT(LOG_MAJOR,"DSPH has given error(%d) in RESET_RESP",errCause);	
          cfgSendNackToCm(errCause);
        }
        /*MantisId 0028088 Starts */  
        if(getActiveIccSlotId( &dspInfoTblIndx.chasisFrameId, &activeSlotId) == CLIB_SUCCESS )
        {
          if(dspInfoTblIndx.slotId != 5 && dspInfoTblIndx.slotId != 6 && dspInfoTblIndx.slotId != activeSlotId)
          {

            if(gDspData[dspInfoTblIndx.dspId].dspState == resetInProgress)
            {

              LOG_PRINT(LOG_MAJOR,"Resetting state of Standby Card in global param to locked/unlocked from "
                  "resetInProgress for dspId (%d) ",dspInfoTblIndx.dspId);	
              getDspInfoTable(&dspInfoTblIndx,&pDspInfoTable);
              if (pDspInfoTable->adminState == LOCKED)
              {
                gDspData[dspInfoTblIndx.dspId].dspState = locked;
              }
              else
              {
                gDspData[dspInfoTblIndx.dspId].dspState = unlocked;
              }
              if(pDspInfoTable != NULL)
              {
                free(pDspInfoTable);
              }
            }
          }
        }
        /*MantisId 0028088 ends */  
        break; 

      case OAMS_DSPH_CFG_DSP_INIT_TRAU_SUCCESS :
        LOG_PRINT(LOG_DEBUG,"OAMS_DSPH_CFG_DSP_INIT_TRAU_SUCCESS received");
        LOG_PRINT(LOG_DEBUG,"for frameId:%d slotId:%d dspId:%d",((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->frameId,
            ((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->slotId,((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->dspId  );
        OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = INFO_DSP_TRAU_INIT_SUCCES;
        OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
        OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = ((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->frameId ;
        OamsCfgAfhSysAlarmBuff.sysAlarm.key2 = ((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->slotId ;
        OamsCfgAfhSysAlarmBuff.sysAlarm.key3 = ((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->dspId ;

        FillObjTypeFromSlotId(((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->slotId,
            OamsCfgAfhSysAlarmBuff.sysAlarm.info3);

        OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = 
          sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,
              "TrauInitSuccess ChasisId[%d],SlotId[%d],dspId[%d]",
              ((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->frameId,
              ((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->slotId, 
              ((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->dspId);
        if(gDspData[((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->dspId].dspState == resetInProgress)
        {
          dspInfoTblIndx.chasisFrameId = ((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->frameId;
          dspInfoTblIndx.slotId = ((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->slotId;
          dspInfoTblIndx.dspId = ((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->dspId;

          getDspInfoTable(&dspInfoTblIndx,&pDspInfoTable);

          if (pDspInfoTable->adminState == LOCKED)
          {
            gDspData[((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->dspId].dspState = locked;
          }
          else
          {
            gDspData[((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->dspId].dspState = unlocked;
          }
          free(pDspInfoTable);
        }

        //cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0); //1U Specific Changes

        break; 

      case OAMS_DSPH_CFG_DSP_INIT_TRAU_FAIL :
        LOG_PRINT(LOG_DEBUG,"OAMS_DSPH_CFG_DSP_INIT_TRAU_FAIL received");
        OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = INFO_DSP_TRAU_INIT_FAIL;
        OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
        OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = ((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->frameId ;
        OamsCfgAfhSysAlarmBuff.sysAlarm.key2 = ((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->slotId ;
        OamsCfgAfhSysAlarmBuff.sysAlarm.key3 = ((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->dspId ;
        OamsCfgAfhSysAlarmBuff.sysAlarm.key4 = ((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->cause ;

        FillObjTypeFromSlotId(((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->slotId,
            OamsCfgAfhSysAlarmBuff.sysAlarm.info3);

        OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = 
          sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,
              "TrauInitFailed ChasisId[%d],SlotId[%d],dspId[%d]",
              ((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->frameId,
              ((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->slotId, 
              ((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->dspId);

        if(gDspData[((OamsDsphCfgDspInitTrauSucc *)gCfgMsgBuf)->dspId].dspState == resetInProgress)
        {
          dspInfoTblIndx.chasisFrameId = ((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->frameId;
          dspInfoTblIndx.slotId = ((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->slotId;
          dspInfoTblIndx.dspId = ((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->dspId;

          getDspInfoTable(&dspInfoTblIndx,&pDspInfoTable);
          if (pDspInfoTable->adminState == LOCKED)
          {
            gDspData[((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->dspId].dspState = locked;
          }
          else
          {
            gDspData[((OamsDsphCfgDspInitTrauFail *)gCfgMsgBuf)->dspId].dspState = unlocked;
          }
          free(pDspInfoTable);
        }

        //cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0); //1U Specific Changes

        break; 

      case OAMS_DSPH_CFG_ALARM_IND :
        if( (( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)) )->sysalarmId == ALARM_DSP_ENABLED  )
        {
          LOG_PRINT(DEBUG,"ALARM_DSP_ENABLED received for FrameId(%d)slotId(%d)dspId(%d) NOT FORWARDING THIS ALARM",
              ((SysAlarm *)(gCfgMsgBuf+sizeof(SysHdr)) )->key1,
              ((SysAlarm *)(gCfgMsgBuf+sizeof(SysHdr)) )->key2,
              ((SysAlarm *)(gCfgMsgBuf+sizeof(SysHdr)) )->key3);
        }  
        else if((( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr)) )->sysalarmId == ALARM_DSP_DISABLED)
        {
          LOG_PRINT(DEBUG,"ALARM_DSP_DISABLED received for FrameId(%d)slotId(%d)dspId(%d) NOT FORWARDING THIS ALARM",
              ((SysAlarm *)(gCfgMsgBuf+sizeof(SysHdr)) )->key1,
              ((SysAlarm *)(gCfgMsgBuf+sizeof(SysHdr)) )->key2,
              ((SysAlarm *)(gCfgMsgBuf+sizeof(SysHdr)) )->key3);
        }
				//Changes done for mantis #31077 Gaurav Sinha 28-12-2016 CLOUD BSC These alarms not to be forwarded at DSP is not a supervisoned object
				#if 0 
        FillObjTypeFromSlotId(((SysAlarm *)(gCfgMsgBuf+sizeof(SysHdr)) )->key2,
            ((SysAlarm *)(gCfgMsgBuf+sizeof(SysHdr)) )->info3);

        cfgSendMessage(gCfgMsgBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
				#endif
				//Changes done for mantis #31077 Gaurav Sinha 28-12-2016 CLOUD BSC

        break; 

      default: 
        LOG_PRINT(LOG_MAJOR,"Unknown Message(%d) received from DSPH",((SysHdr*) gCfgMsgBuf)->msgType);
        break;
    }
  }//dsphMsgHandler	
  /*Changes for R2.0 Ends*/

  /* R2.4 changes start */

  /********************************* Function  Header*****************************
    Function Name   : cbsifMsgHandler()
Parameters       : Void
Return type       : Void
Purpose          : It Handles the messages from CBSIF.
Other Note        : Added For BSC R2.4
   *******************************************************************************/

  void cbsifMsgHandler() 
  {
    LOG_PRINT(LOG_INFO,"cbsifMsgHandler: Entering in Function ");

    switch (((SysHdr*) gCfgMsgBuf)->msgType) 
    {
      case CSAPP_CBSIF_CFG_CONNECTION_DOWN:
        {
          LOG_PRINT(LOG_INFO," Message CSAPP_CBSIF_CFG_CONNECTION_DOWN received from CBSIF");
          cbsifConnectionDownHandler();   
          break;
        }
      case CSAPP_CBSIF_CFG_DELETE_CONFIG_CBS_RESP:
        {
          LOG_PRINT(LOG_INFO," Message CSAPP_CBSIF_CFG_DELETE_CONFIG_CBS_RESP received from CBSIF");
          cbsifDeleteConfigCbsResp();   
          break;
        }
      case CSAPP_CBSIF_CFG_CONNECTION_UP:
        {
          LOG_PRINT(LOG_INFO," Message CSAPP_CBSIF_CFG_CONNECTION_UP received from CBSIF");
          cbsifConnectionUpHandler();   
          break;
        }
      case CSAPP_CBSIF_CFG_DATA_IND:
        {
          I_PVoid       outputMsg = NULL;
          I_U32         outMsgLen; 
          DecodeStatus  decodeStatus;
          DecodeCbshMsgAsn(((CsappCbsifCfgDataInd*) gCfgMsgBuf)->payLoad ,((CsappCbsifCfgDataInd*) gCfgMsgBuf)->size,                             &outputMsg, &outMsgLen, &decodeStatus);
          if ( decodeStatus.statusCode != I_TRUE)
          {
            LOG_PRINT(LOG_CRITICAL," DecodeCbshMsgAsn failed.."); 
            return ;  
          }
          switch(((SysHdr*)outputMsg)->msgType)
          {
            case SMSCB_BIND_CONFIRM:
              {
                LOG_PRINT(LOG_INFO," Message SMSCB_BIND_CONFIRM received from CBSIF");
                ((CsappCbsifCfgBindConfirm*)outputMsg)->cbsId =  ((CsappCbsifCfgDataInd*)gCfgMsgBuf)->cbsId;  
                cbsifBindConfirmHandler(outputMsg);   
                break;
              }
            case SMSCB_BIND_FAILURE:
              {
                LOG_PRINT(LOG_INFO," Message SMSCB_BIND_FAILURE received from CBSIF");
                ((OamsCbsifCfgBindFail*)outputMsg)->cbsId =  ((CsappCbsifCfgDataInd*)gCfgMsgBuf)->cbsId;
                cbsifBindFailHandler(outputMsg);   
                break;
              }
            case SMSCB_UNBIND:
              {
                LOG_PRINT(LOG_INFO," Message SMSCB_UNBIND received from CBSIF");
                ((CsappCbsifCfgUnbind*)outputMsg)->cbsId =  ((CsappCbsifCfgDataInd*)gCfgMsgBuf)->cbsId;
                cbsifUnBindHandler(outputMsg);   
                break;
              }
            default: 
              {
                LOG_PRINT(LOG_MAJOR,"Unknown Message(%d) received from CBSIF",((SysHdr*) gCfgMsgBuf)->msgType);
                break;
              }
          }
          break;
        }
      default: 
        {
          LOG_PRINT(LOG_MAJOR,"Unknown Message(%d) received from CBSIF",((SysHdr*) gCfgMsgBuf)->msgType);
          break;
        }


    }
  }

  /********************************* Function  Header*****************************
    Function Name   : stateChangeNotificationHandler()
Parameters       : I_Void
Return type       : I_Void
Purpose          : It Handles the messages from CFG itself.
Other Note        : Added For BSC CS4.0 HA Implementation
   *******************************************************************************/
  I_Void stateChangeNotificationHandler()
  {
    RmCardStateNotification *rmCardStateNotification = NULL;
    I_S32 retCode = CFG_FAILURE;
    BssCsPreConfigTableApi *bssCsConfigTablePtr = NULL;
    I_U16 outSize = 0;
    I_U32 outRow = 0;
    rmCardStateNotification = (RmCardStateNotification *)((I_U8 *)gCfgMsgBuf);
    LOG_PRINT(LOG_INFO,"stateChangeNotificationHandler: Entering in function gCurrentCardState [%d] cardState[%d]",gCurrentCardState,rmCardStateNotification->cardState);
    //   if(gNextCardState == CARDSTATE_IN_SERVICE)
    if(rmCardStateNotification->cardState == CARDSTATE_IN_SERVICE)
    {
      if(gCurrentCardState == CARDSTATE_INIT )
      {
        LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: gCurrentCardState: [CARDSTATE_INIT] and gNextCardState: [CARDSTATE_IN_SERVICE]");
        cfgCleanGlobalData();
        cfgSigInit();
        cfgDbInit();
        /* R2.4 Changes Start */
        if (initEnv() == 0 )
        {
          LOG_PRINT(LOG_CRITICAL,"CbshCodec Library initialization failed ...");
        }
        /* R2.4 Changes End */
        /* EIC Software upgrade changes start */ 
        if ( (retCode = checkPlatformInstFile()) == CFG_SUCCESS )
        {
          LOG_PRINT(LOG_INFO,"NOT SENDING OK NOTIFICATION FOR INSERVICE AS EIC ACTIVATION WAS IN PROGRESS ");
          return;
        }
        /* EIC Software upgrade changes end */ 
        startInitializeMGS();
        gCfgState = CFG_INIT_TSI;
        LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: gCfgState: [CFG_INIT_TSI] i.e. [%d]", gCfgState);
      }
      else if(gCurrentCardState == CARDSTATE_ACTIVE)
      {
        LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: gCurrentCardState: [CARDSTATE_ACTIVE] and gNextCardState: [CARDSTATE_IN_SERVICE]");
        if(gIsTimerRunning == TRUE)
        {
          cfgStopTimer();
        }
        cfgCleanUpResources();
        sendBreakOmcipAddressReqToCm();
        /* Changes for R2.4 Start */
        sendBreakCbsipAddressReqForAllServerToCbsIf();
        /* Changes for R2.4 End */
        gCurrentCardState = CARDSTATE_IN_SERVICE;
        gNextCardState = CARDSTATE_INVALID;
        RELEASE_MUTEX;
      }
      else if( (gCurrentCardState == CARDSTATE_RECOVERY) ||
          (gCurrentCardState == CARDSTATE_DIAGNOSTIC) )
      {
        LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler:\
            gCurrentCardState: [CARDSTATE_RECOVERY/DIAGNOSTICS] and gNextCardState: [CARDSTATE_IN_SERVICE]");
        if(gIsTimerRunning == TRUE)
        {
          cfgStopTimer();
        }
        cfgCleanUpResources();
        startInitializeMGS();
        gCfgState = CFG_INIT_TSI;
        gCurrentCardState = CARDSTATE_INIT;
        gNextCardState = CARDSTATE_INVALID;
      }
    }
    //   else if(gNextCardState == CARDSTATE_ACTIVE_IN_PROGRESS)
    else if(rmCardStateNotification->cardState == CARDSTATE_ACTIVE_IN_PROGRESS  )
    {
      gCfgStandbyToActive = I_FALSE;
      gCfgStandbyToActiveforCbsh=I_FALSE;
      if(gCurrentCardState == CARDSTATE_STANDBY)
      {
        gCfgStandbyToActive = I_TRUE;
        gCfgStandbyToActiveforCbsh=I_TRUE;
        LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: gCurrentCardState: [CARDSTATE_STANDBY] and gNextCardState: [CARDSTATE_ACTIVE_IN_PROGRESS]");
        cfgCleanUpResources();
        //         LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: Sending Switch Connect to GRHM for My slot Id [%d]", gMySlotId);
        //         sendSwitchConForSelf(gMySlotId);
        //         LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: Sending Switch Connect to RM for Peer slot Id [%d]", gPeerSlotId);
        //         sendSwitchConForMate(gPeerSlotId);
        //         sendNeipReq();
        sendBpmDbInitialized();
        //gCfgState = CFG_BPM_INIT; //R2.9
        gCurrentCardState = CARDSTATE_ACTIVE_IN_PROGRESS;
        gNextCardState = CARDSTATE_INVALID;
      }
      else if(gCurrentCardState == CARDSTATE_IN_SERVICE)
      {
        LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: gCurrentCardState: [CARDSTATE_IN_SERVICE] and gNextCardState: [CARDSTATE_ACTIVE_IN_PROGRESS]");
        //         sendNeipReq();
        sendBpmDbInitialized();
        gCfgState = CFG_BPM_INIT;
        //Mantis #0031749
				/*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
				LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: stateChangeNotificationHandler: : Before updating gCardPlatformType [%d]",gCardPlatformType);
				updateCardPlatformTypeInContext();
				LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: stateChangeNotificationHandler: : After updating gCardPlatformType [%d]",gCardPlatformType);
				/*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
        //Mantis #0031749
      }

      //Send Mcc LinkResource Switching
    }//CARDSTATE_ACTIVE_IN_PROGRESS
    else if (rmCardStateNotification->cardState == CARDSTATE_RECOVERY)
    {
      if(gCurrentCardState == CARDSTATE_ACTIVE)
      {
        LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: gCurrentCardState: [CARDSTATE_ACTIVE] and gNextCardState: [CARDSTATE_RECOVERY]");
        sendBreakOmcipAddressReqToCm();
        /* Changes for R2.4 Start */
        sendBreakCbsipAddressReqForAllServerToCbsIf();
        exitEnv();
        /* Changes for R2.4 End */
      }
      gCurrentCardState = CARDSTATE_RECOVERY;
      gNextCardState = CARDSTATE_INVALID;
      RELEASE_MUTEX;
    }
    else if (rmCardStateNotification->cardState == CARDSTATE_PLATFORM_INS)
    {
      LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: gNextCardState: [CARDSTATE_PLATFORM_INS]");
      if ( (retCode = handlingPlatformInst()) == CFG_FAILURE)
      {
        LOG_PRINT(LOG_INFO,"NOT SENDING OK NOTIFICATION FOR INSERVICE AS EIC ACTIVATION WAS IN PROGRESS ");
        return;
      }
      RELEASE_MUTEX;
    }
    else if (rmCardStateNotification->cardState == CARDSTATE_OUT_OF_SERVICE)
    {
      if(gCurrentCardState == CARDSTATE_ACTIVE)
      {
        LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: gCurrentCardState: [CARDSTATE_ACTIVE] and gNextCardState: [CARDSTATE_OUT_OF_SERVICE]");
        sendBreakOmcipAddressReqToCm();
        /* Changes for R2.4 Start */
        sendBreakCbsipAddressReqForAllServerToCbsIf();
        exitEnv();
        /* Changes for R2.4 End */
      }
      RELEASE_MUTEX;
    }
    else if (rmCardStateNotification->cardState == CARDSTATE_ACTIVE)
    {
      LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: gCurrentCardState: [CARDSTATE_ACTIVE_IN_PROGRESS] and gNextCardState: [CARDSTATE_ACTIVE]");
      cfgCleanTransientTable();
      /* Changes For E1-T1 : Start */
      if(getallBssCsPreConfigTable(&bssCsConfigTablePtr,&outRow,&outSize) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL," No Row Found in BSCCSPRCONFIGTABLE");
        exit(0);
      }  
      gBscTrunkType = bssCsConfigTablePtr->bscTrunkType;
      free(bssCsConfigTablePtr);
      if(gGbTransportType == FR)
      {
         fillNsvcData();
         fillFrLinkStatusData();
      }
      /* Changes For E1-T1 : End */
      updateSystemDetails();
			/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
      //LOG_PRINT(INFO,"1U: going to call updateSystemDetails1U() at STARTUP");
      //updateSystemDetails1U();
			/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
      cfgInitSwMNodeTableDelBicTrx();
      fillIpBtsInSWMTableAtInit(); // Veena 
      RELEASE_MUTEX;
      chkNupdateMccLinkResourceTable();
      //sendBpmTrunkPortStsReq();
      /* R2.9 changes */
      if (gCfgStandbyToActive == I_FALSE)
      {
        LOG_PRINT(LOG_DEBUG," Sending OK Start Static switching to GRHM");
        cfgSendMessage(NULL, 0, ENT_CSAPP_GRHM, OAMS_CFG_GRHM_START_STATIC_SWITCHING, 0);
      }
      else if((gGbTransportType == FR) && (LOCKED != bssLock()) 
             && (gDbBssTableApiStorage.gprsEnabled == ENABLED))
      {
        sendPsscmUnlockReq(OAMS_RSN_OPERATORINITIATED);
      }
      if((gSetOmcIpReqSent == I_FALSE) && (gCfgStandbyToActive == I_TRUE))
      {
        sendSetOmcipAddressReqToCmInActive();
        gSetOmcIpReqSent = I_TRUE;
      }
      

      /* 
         if(gCfgState == CFG_BPM_INIT)
         {
         LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: CFG is in CFG_BPM_INIT state");
      //Send TrunkPort State Change Request
      if(sendTrunkStateChangeReq() == CFG_FAILURE)
      {
      LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: No Trunk is in Enable state. Sending ClkSrcConfig");
      if(sendClockSourceConfigReq() == CFG_FAILURE)
      {
      LOG_PRINT(LOG_DEBUG,"stateChangeNotificationHandler: No ClockSource Avaibale . Initialization Process continues");
      cfgInitAfterDbRw();
      addConfiguredBics();
      addConfiguredTrxs();
      cfgInitSwMNodeTable();
      getListValue();
      gCfgState = CFG_START_TRAU;
      sendTrauStartMsg();
      }
      }
      }
       */
    }
    LOG_PRINT(LOG_INFO,"stateChangeNotificationHandler: Exiting from function ");
  }

  /*BSC R2.0 Changes Starts*/
  /********************************* Function  Header*****************************
    Function Name     : printSystemDetails()
Parameters        :  sSystemCardInfo *
Return type       : I_Void
Purpose           : It prints complete card info received from bpm.
Other Note        : Added For BSC R2.0 Implementation
   *******************************************************************************/
  I_Void printSystemDetails(sSystemCardInfo *sysDetailPtr)
  {
    I_U8 i = 0,j =0;

    LOG_PRINT(LOG_DEBUG,"Going To print rcvd system details");
    LOG_PRINT(LOG_DEBUG,"systemType = 0x%x",sysDetailPtr->systemType);  
    LOG_PRINT(LOG_DEBUG,"numTrunkPort = 0x%x",sysDetailPtr->numTrunkPort);  
    LOG_PRINT(LOG_DEBUG,"totalNumCards = 0x%x",sysDetailPtr->totalNumCards);  
    LOG_PRINT(LOG_DEBUG,"numRemoteCards = 0x%x",sysDetailPtr->numRemoteCards );  

    LOG_PRINT(LOG_DEBUG,"selfInfo.frameID = 0x%x",sysDetailPtr->selfInfo.frameID);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.slotID = 0x%x",sysDetailPtr->selfInfo.slotID);  
    LOG_PRINT(LOG_DEBUG,"selfInfoi.cardType = 0x%x",sysDetailPtr->selfInfo.cardType);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.cardOperState = 0x%x",sysDetailPtr->selfInfo.cardOperState);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.peerCardState = 0x%x",sysDetailPtr->selfInfo.peerCardState);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.peerCardPresence = 0x%x",sysDetailPtr->selfInfo.peerCardPresence);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.oneP2PowerModuleVoltageStatus = 0x%x",sysDetailPtr->selfInfo.oneP2PowerModuleVoltageStatus);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.twoP5PowerModuleVoltageStatus = 0x%x",sysDetailPtr->selfInfo.twoP5PowerModuleVoltageStatus);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.oneP2DSPVoltageStatus = 0x%x",sysDetailPtr->selfInfo.oneP2DSPVoltageStatus);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.twoP5PowerModuleTempStatus = 0x%x",sysDetailPtr->selfInfo.twoP5PowerModuleTempStatus);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.threeP3PowerModuleTempStatus = 0x%x",sysDetailPtr->selfInfo.threeP3PowerModuleTempStatus);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.hotSwapPowerGood1 = 0x%x",sysDetailPtr->selfInfo.hotSwapPowerGood1);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.hotSwapPowerGood3 = 0x%x",sysDetailPtr->selfInfo.hotSwapPowerGood3 );  
    LOG_PRINT(LOG_DEBUG,"selfInfo.cardSerialNumber = ");  
    PRINT_HEX_DUMP(LOG_DEBUG, sysDetailPtr->selfInfo.cardSerialNumber ,20);

    LOG_PRINT(LOG_DEBUG,"selfInfo.cpldVersion.major = 0x%x",sysDetailPtr->selfInfo.cpldVersion.major);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.cpldVersion.minor = 0x%x",sysDetailPtr->selfInfo.cpldVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.cpldVersion.revision = 0x%x",sysDetailPtr->selfInfo.cpldVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"selfInfo.uCVersion.major = 0x%x",sysDetailPtr->selfInfo.uCVersion.major);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.uCVersion.minor = 0x%x",sysDetailPtr->selfInfo.uCVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.uCVersion.revision = 0x%x",sysDetailPtr->selfInfo.uCVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"selfInfo.activeKernelVersion.major = 0x%x",sysDetailPtr->selfInfo.activeKernelVersion.major);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.activeKernelVersion.minor = 0x%x",sysDetailPtr->selfInfo.activeKernelVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.activeKernelVersion.revision = 0x%x",sysDetailPtr->selfInfo.activeKernelVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"selfInfo.backUpKernelVersionInfo.major = 0x%x",sysDetailPtr->selfInfo.backUpKernelVersionInfo.major);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.backUpKernelVersionInfo.minor = 0x%x",sysDetailPtr->selfInfo.backUpKernelVersionInfo.minor);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.backUpKernelVersionInfo.revision = 0x%x",sysDetailPtr->selfInfo.backUpKernelVersionInfo.revision);  

    LOG_PRINT(LOG_DEBUG,"selfInfo.activeRamDiskVersion.major = 0x%x",sysDetailPtr->selfInfo.activeRamDiskVersion.major);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.activeRamDiskVersion.minor = 0x%x",sysDetailPtr->selfInfo.activeRamDiskVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.activeRamDiskVersion.revision = 0x%x",sysDetailPtr->selfInfo.activeRamDiskVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"selfInfo.backUpRamDiskVersion.major = 0x%x",sysDetailPtr->selfInfo.backUpRamDiskVersion.major);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.backUpRamDiskVersion.minor = 0x%x",sysDetailPtr->selfInfo.backUpRamDiskVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.backUpRamDiskVersion.revision = 0x%x",sysDetailPtr->selfInfo.backUpRamDiskVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"selfInfo.uBootVersion.major = 0x%x",sysDetailPtr->selfInfo.uBootVersion.major);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.uBootVersion.minor = 0x%x",sysDetailPtr->selfInfo.uBootVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.uBootVersion.revision = 0x%x",sysDetailPtr->selfInfo.uBootVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"selfInfo.activeRelVersion.major = 0x%x",sysDetailPtr->selfInfo.activeRelVersion.major);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.activeRelVersion.minor = 0x%x",sysDetailPtr->selfInfo.activeRelVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.activeRelVersion.revision = 0x%x",sysDetailPtr->selfInfo.activeRelVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"selfInfo.backUpRelVersion.major = 0x%x",sysDetailPtr->selfInfo.backUpRelVersion.major);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.backUpRelVersion.minor = 0x%x",sysDetailPtr->selfInfo.backUpRelVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.backUpRelVersion.revision = 0x%x",sysDetailPtr->selfInfo.backUpRelVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"selfInfo.downLoadedRelVersion.major = 0x%x",sysDetailPtr->selfInfo.downLoadedRelVersion.major);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.downLoadedRelVersion.minor = 0x%x",sysDetailPtr->selfInfo.downLoadedRelVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"selfInfo.downLoadedRelVersion.revision = 0x%x",sysDetailPtr->selfInfo.downLoadedRelVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"selfInfo.pfsReleaseVersion = ");  
    PRINT_HEX_DUMP(LOG_DEBUG, sysDetailPtr->selfInfo.pfsReleaseVersion ,24);

    LOG_PRINT(LOG_DEBUG,"mateInfo.frameID = 0x%x",sysDetailPtr->mateInfo.frameID);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.slotID = 0x%x",sysDetailPtr->mateInfo.slotID);  
    LOG_PRINT(LOG_DEBUG,"mateInfoi.cardType = 0x%x",sysDetailPtr->mateInfo.cardType);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.cardOperState = 0x%x",sysDetailPtr->mateInfo.cardOperState);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.peerCardState = 0x%x",sysDetailPtr->mateInfo.peerCardState);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.peerCardPresence = 0x%x",sysDetailPtr->mateInfo.peerCardPresence);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.oneP2PowerModuleVoltageStatus = 0x%x",sysDetailPtr->mateInfo.oneP2PowerModuleVoltageStatus);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.twoP5PowerModuleVoltageStatus = 0x%x",sysDetailPtr->mateInfo.twoP5PowerModuleVoltageStatus);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.oneP2DSPVoltageStatus = 0x%x",sysDetailPtr->mateInfo.oneP2DSPVoltageStatus);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.twoP5PowerModuleTempStatus = 0x%x",sysDetailPtr->mateInfo.twoP5PowerModuleTempStatus);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.threeP3PowerModuleTempStatus = 0x%x",sysDetailPtr->mateInfo.threeP3PowerModuleTempStatus);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.hotSwapPowerGood1 = 0x%x",sysDetailPtr->mateInfo.hotSwapPowerGood1);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.hotSwapPowerGood3 = 0x%x",sysDetailPtr->mateInfo.hotSwapPowerGood3 );  
    LOG_PRINT(LOG_DEBUG,"mateInfo.cardSerialNumber = ");  
    PRINT_HEX_DUMP(LOG_DEBUG, sysDetailPtr->mateInfo.cardSerialNumber ,20);

    LOG_PRINT(LOG_DEBUG,"mateInfo.cpldVersion.major = 0x%x",sysDetailPtr->mateInfo.cpldVersion.major);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.cpldVersion.minor = 0x%x",sysDetailPtr->mateInfo.cpldVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.cpldVersion.revision = 0x%x",sysDetailPtr->mateInfo.cpldVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"mateInfo.uCVersion.major = 0x%x",sysDetailPtr->mateInfo.uCVersion.major);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.uCVersion.minor = 0x%x",sysDetailPtr->mateInfo.uCVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.uCVersion.revision = 0x%x",sysDetailPtr->mateInfo.uCVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"mateInfo.activeKernelVersion.major = 0x%x",sysDetailPtr->mateInfo.activeKernelVersion.major);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.activeKernelVersion.minor = 0x%x",sysDetailPtr->mateInfo.activeKernelVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.activeKernelVersion.revision = 0x%x",sysDetailPtr->mateInfo.activeKernelVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"mateInfo.backUpKernelVersionInfo.major = 0x%x",sysDetailPtr->mateInfo.backUpKernelVersionInfo.major);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.backUpKernelVersionInfo.minor = 0x%x",sysDetailPtr->mateInfo.backUpKernelVersionInfo.minor);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.backUpKernelVersionInfo.revision = 0x%x",sysDetailPtr->mateInfo.backUpKernelVersionInfo.revision);  

    LOG_PRINT(LOG_DEBUG,"mateInfo.activeRamDiskVersion.major = 0x%x",sysDetailPtr->mateInfo.activeRamDiskVersion.major);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.activeRamDiskVersion.minor = 0x%x",sysDetailPtr->mateInfo.activeRamDiskVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.activeRamDiskVersion.revision = 0x%x",sysDetailPtr->mateInfo.activeRamDiskVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"mateInfo.backUpRamDiskVersion.major = 0x%x",sysDetailPtr->mateInfo.backUpRamDiskVersion.major);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.backUpRamDiskVersion.minor = 0x%x",sysDetailPtr->mateInfo.backUpRamDiskVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.backUpRamDiskVersion.revision = 0x%x",sysDetailPtr->mateInfo.backUpRamDiskVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"mateInfo.uBootVersion.major = 0x%x",sysDetailPtr->mateInfo.uBootVersion.major);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.uBootVersion.minor = 0x%x",sysDetailPtr->mateInfo.uBootVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.uBootVersion.revision = 0x%x",sysDetailPtr->mateInfo.uBootVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"mateInfo.activeRelVersion.major = 0x%x",sysDetailPtr->mateInfo.activeRelVersion.major);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.activeRelVersion.minor = 0x%x",sysDetailPtr->mateInfo.activeRelVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.activeRelVersion.revision = 0x%x",sysDetailPtr->mateInfo.activeRelVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"mateInfo.backUpRelVersion.major = 0x%x",sysDetailPtr->mateInfo.backUpRelVersion.major);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.backUpRelVersion.minor = 0x%x",sysDetailPtr->mateInfo.backUpRelVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.backUpRelVersion.revision = 0x%x",sysDetailPtr->mateInfo.backUpRelVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"mateInfo.downLoadedRelVersion.major = 0x%x",sysDetailPtr->mateInfo.downLoadedRelVersion.major);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.downLoadedRelVersion.minor = 0x%x",sysDetailPtr->mateInfo.downLoadedRelVersion.minor);  
    LOG_PRINT(LOG_DEBUG,"mateInfo.downLoadedRelVersion.revision = 0x%x",sysDetailPtr->mateInfo.downLoadedRelVersion.revision);  

    LOG_PRINT(LOG_DEBUG,"mateInfo.pfsReleaseVersion = ");  
    PRINT_HEX_DUMP(LOG_DEBUG, sysDetailPtr->mateInfo.pfsReleaseVersion ,24);
    for(i=0; i < MAX_DSP ;i++)
    {
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].frameID = 0x%x",i,sysDetailPtr->dspInfo[i].frameID);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].slotID = 0x%x",i,sysDetailPtr->dspInfo[i].slotID);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspId = 0x%x",i,sysDetailPtr->dspInfo[i].dspId);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].isDspPresent = 0x%x",i,sysDetailPtr->dspInfo[i].isDspPresent);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].operationalState = 0x%x",i,sysDetailPtr->dspInfo[i].operationalState);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.dspId = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.dspId);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.bootTestResult = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.bootTestResult);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.failureInfo = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.failureInfo);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.trauResource_core0 = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.trauResource_core0);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.abisTsResource_core0 = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.abisTsResource_core0);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.trauResource_core1 = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.trauResource_core1);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.abisTsResource_core1 = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.abisTsResource_core1);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.trauResource_core2 = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.trauResource_core2);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.abisTsResource_core2 = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.abisTsResource_core2);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.trauResource_core3 = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.trauResource_core3);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.abisTsResource_core3 = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.abisTsResource_core3);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.activeChannels = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.activeChannels);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.swVerInfo[0] = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.swVerInfo[0]);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.swVerInfo[1] = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.swVerInfo[1]);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.swVerInfo[2] = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.swVerInfo[2]);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.swIdInfo[0] = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.swIdInfo[0]);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.swIdInfo[1] = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.swIdInfo[1]);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspInfo.bscInfo.swIdInfo[2] = 0x%x",i,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.swIdInfo[2]);  

      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].activeDspVer.major = 0x%x",i,sysDetailPtr->dspInfo[i].activeDspVer.major);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].activeDspVer.minor = 0x%x",i,sysDetailPtr->dspInfo[i].activeDspVer.minor);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].activeDspVer.revision = 0x%x",i,sysDetailPtr->dspInfo[i].activeDspVer.revision);  

      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].backupDspVer.major = 0x%x",i,sysDetailPtr->dspInfo[i].backupDspVer.major);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].backupDspVer.minor = 0x%x",i,sysDetailPtr->dspInfo[i].backupDspVer.minor);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].backupDspVer.revision = 0x%x",i,sysDetailPtr->dspInfo[i].backupDspVer.revision);  

      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].downloadDspVer.major = 0x%x",i,sysDetailPtr->dspInfo[i].downloadDspVer.major);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].downloadDspVer.minor = 0x%x",i,sysDetailPtr->dspInfo[i].downloadDspVer.minor);  
      LOG_PRINT(LOG_DEBUG,"dspInfo[%d].downloadDspVer.revision = 0x%x",i,sysDetailPtr->dspInfo[i].downloadDspVer.revision);  
      for (j=0;j<MAX_CORE_PER_DSP;j++)/*changes for R2.8 */
      {
        LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspCoreIpAddr[%d].addr1 =%d",i,j,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.dspCoreIpAddr[j].addr1);  
        LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspCoreIpAddr[%d].addr2 =%d",i,j,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.dspCoreIpAddr[j].addr2);  
        LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspCoreIpAddr[%d].addr3 =%d",i,j,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.dspCoreIpAddr[j].addr3);  
        LOG_PRINT(LOG_DEBUG,"dspInfo[%d].dspCoreIpAddr[%d].addr4 =%d",i,j,sysDetailPtr->dspInfo[i].dspInfo.bscInfo.dspCoreIpAddr[j].addr4);  
      }
    }

    LOG_PRINT(LOG_DEBUG,"portInfo.numOfPort = 0x%x",sysDetailPtr->portInfo.numOfPort);  
    for(i = 0; i < MAX_PORT ; i++)
    {
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].frameID = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].frameID);  
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].slotID = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].slotID);  
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].portID = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].portID);  
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].isPortPresent = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].isPortPresent);  
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].trunkOperStatus = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].trunkOperStatus);  
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].trunkType = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].trunkType);  
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].loopback = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].loopback);  
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].loopType = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].loopType);  
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].trunkFramingOption = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].trunkFramingOption);  
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].encodeType = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].encodeType);  
      LOG_PRINT(LOG_DEBUG,"portInfo.portInfo[%d].sigStrength = 0x%x",i,sysDetailPtr->portInfo.portInfo[i].sigStrength);  
    }
    LOG_PRINT(LOG_DEBUG,"sysClkInfo.frameID = 0x%x",sysDetailPtr->sysClkInfo.frameID);  
    LOG_PRINT(LOG_DEBUG,"sysClkInfo.slotID = 0x%x",sysDetailPtr->sysClkInfo.slotID);  
    LOG_PRINT(LOG_DEBUG,"sysClkInfo.clockReference = 0x%x",sysDetailPtr->sysClkInfo.clockReference );  
    LOG_PRINT(LOG_DEBUG,"sysClkInfo.clockPortId = 0x%x",sysDetailPtr->sysClkInfo.clockPortId );  

    for(i = 0; i < MAX_EIC; i++)
    {
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].frameID = 0x%x",i,sysDetailPtr->eicInfo[i].frameID);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].slotID = 0x%x",i,sysDetailPtr->eicInfo[i].slotID);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].cardType = 0x%x",i,sysDetailPtr->eicInfo[i].cardType);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].cardOperState = 0x%x",i,sysDetailPtr->eicInfo[i].cardOperState);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].peerCardState = 0x%x",i,sysDetailPtr->eicInfo[i].peerCardState);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].peerCardPresence = 0x%x",i,sysDetailPtr->eicInfo[i].peerCardPresence);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].cardSerialNumber = ",i);  
      PRINT_HEX_DUMP(LOG_DEBUG,sysDetailPtr->eicInfo[i].cardSerialNumber ,20);

      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].numTrunkPort = 0x%x",i,sysDetailPtr->eicInfo[i].numTrunkPort);  

      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].cpldVersion.major = 0x%x",i,sysDetailPtr->eicInfo[i].cpldVersion.major);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].cpldVersion.minor = 0x%x",i,sysDetailPtr->eicInfo[i].cpldVersion.minor);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].cpldVersion.revision = 0x%x",i,sysDetailPtr->eicInfo[i].cpldVersion.revision);  

      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].uCVersion.major = 0x%x",i,sysDetailPtr->eicInfo[i].uCVersion.major);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].uCVersion.minor = 0x%x",i,sysDetailPtr->eicInfo[i].uCVersion.minor);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].uCVersion.revision = 0x%x",i,sysDetailPtr->eicInfo[i].uCVersion.revision);  

      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].kernelVersion.major = 0x%x",i,sysDetailPtr->eicInfo[i].kernelVersion.major);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].kernelVersion.minor =  0x%x",i,sysDetailPtr->eicInfo[i].kernelVersion.minor);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].kernelVersion.revision = 0x%x",i,sysDetailPtr->eicInfo[i].kernelVersion.revision);  

      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].ramDiskVersion.major = 0x%x",i,sysDetailPtr->eicInfo[i].ramDiskVersion.major);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].ramDiskVersion.minor = 0x%x",i,sysDetailPtr->eicInfo[i].ramDiskVersion.minor);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].ramDiskVersion.revision = 0x%x",i,sysDetailPtr->eicInfo[i].ramDiskVersion.revision);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].uBootVersion.major = 0x%x",i,sysDetailPtr->eicInfo[i].uBootVersion.major);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].uBootVersion.minor = 0x%x",i,sysDetailPtr->eicInfo[i].uBootVersion.minor);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].uBootVersion.revision = 0x%x",i,sysDetailPtr->eicInfo[i].uBootVersion.revision);  

      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].activeRelVersion.major = 0x%x",i,sysDetailPtr->eicInfo[i].activeRelVersion.major);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].activeRelVersion.minor = 0x%x",i,sysDetailPtr->eicInfo[i].activeRelVersion.minor);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].activeRelVersion.revision = 0x%x",i,sysDetailPtr->eicInfo[i].activeRelVersion.revision);  

      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].backUpRelVersion.major = 0x%x",i,sysDetailPtr->eicInfo[i].backUpRelVersion.major);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].backUpRelVersion.minor = 0x%x",i,sysDetailPtr->eicInfo[i].backUpRelVersion.minor);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].backUpRelVersion.revision = 0x%x",i,sysDetailPtr->eicInfo[i].backUpRelVersion.revision);  

      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].downLoadedRelVersion.major = 0x%x",i,sysDetailPtr->eicInfo[i].downLoadedRelVersion.major);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].downLoadedRelVersion.minor = 0x%x",i,sysDetailPtr->eicInfo[i].downLoadedRelVersion.minor);  
      LOG_PRINT(LOG_DEBUG,"eicInfo[%d].downLoadedRelVersion.revision = 0x%x",i,sysDetailPtr->eicInfo[i].downLoadedRelVersion.revision);  

    }

    /*Changes for R2.3.4 Starts*/  
    for(i = 0; i < MAX_PSU; i++)
    {
      LOG_PRINT(LOG_DEBUG,"PowerSupplyInfo[%d].frameID = 0x%x",i,sysDetailPtr->psuInfo[i].frameID);  
      LOG_PRINT(LOG_DEBUG,"PowerSupplyInfo[%d].slotID = 0x%x",i,sysDetailPtr->psuInfo[i].slotID);  
      LOG_PRINT(LOG_DEBUG,"PowerSupplyInfo[%d].cardType = 0x%x",i,sysDetailPtr->psuInfo[i].cardType);  
      LOG_PRINT(LOG_DEBUG,"PowerSupplyInfo[%d].cardOperState = 0x%x",i,sysDetailPtr->psuInfo[i].cardOperState);  
      LOG_PRINT(LOG_DEBUG,"PowerSupplyInfo[%d].cardSerialNumber = ",i);  
      PRINT_HEX_DUMP(LOG_DEBUG,sysDetailPtr->psuInfo[i].cardSerialNumber ,20);
      LOG_PRINT(LOG_DEBUG,"psuInfo[%d].uCVersion.major = 0x%x",i,sysDetailPtr->psuInfo[i].uCVersion.major);  
      LOG_PRINT(LOG_DEBUG,"psuInfo[%d].uCVersion.minor = 0x%x",i,sysDetailPtr->psuInfo[i].uCVersion.minor);  
      LOG_PRINT(LOG_DEBUG,"psuInfo[%d].uCVersion.revision = 0x%x",i,sysDetailPtr->psuInfo[i].uCVersion.revision);  
      LOG_PRINT(LOG_DEBUG,"psuInfo[%d].peerCardPresence = 0x%x",i,sysDetailPtr->psuInfo[i].peerCardPresence);  
    }

    for(i = 0; i < MAX_NUM_FAN_TRAY; i++)
    {
      LOG_PRINT(LOG_DEBUG,"fanTrayInfo[%d].frameID = 0x%x",i,sysDetailPtr->fanTrayInfo[i].frameID);  
      LOG_PRINT(LOG_DEBUG,"fanTrayInfo[%d].fanTrayID = 0x%x",i,sysDetailPtr->fanTrayInfo[i].fanTrayID);  
      LOG_PRINT(LOG_DEBUG,"fanTrayInfo[%d].physicalPresenceStatus = 0x%x",i,sysDetailPtr->fanTrayInfo[i].physicalPresenceStatus);  

      for(j=0; j < MAX_FANS_IN_TRAY;j++)
      {
        LOG_PRINT(LOG_DEBUG,"fanInfo[%d].frameID = 0x%x",j,sysDetailPtr->fanTrayInfo[i].fanInfo[j].frameID);  
        LOG_PRINT(LOG_DEBUG,"fanInfo[%d].fanTrayID = 0x%x",j,sysDetailPtr->fanTrayInfo[i].fanInfo[j].fanTrayID);  
        LOG_PRINT(LOG_DEBUG,"fanInfo[%d].fanId= 0x%x",j,sysDetailPtr->fanTrayInfo[i].fanInfo[j].fanId);  
        LOG_PRINT(LOG_DEBUG,"fanInfo[%d].physicalFanPresence= 0x%x",j,sysDetailPtr->fanTrayInfo[i].fanInfo[j].physicalFanPresence);  
        LOG_PRINT(LOG_DEBUG,"fanInfo[%d].fanSpeed = 0x%x",j,sysDetailPtr->fanTrayInfo[i].fanInfo[j].fanSpeed);  
        LOG_PRINT(LOG_DEBUG,"fanInfo[%d].fanStatus= 0x%x",j,sysDetailPtr->fanTrayInfo[i].fanInfo[j].fanStatus);  
      } 
    }
    /*Changes for R2.3.4 Ends*/  

  }//printSystemDetails
  /*BSC R2.0 Changes Ends*/
  /********************************* Function  Header*****************************
    Function Name     : copySystemDetails()
Parameters        : I_Void
Return type       : I_Void
Purpose           : It makes a copy of System details which is received from BPM.
Other Note        : Added For BSC CS4.0 HA Implementation
   *******************************************************************************/
  I_Void copySystemDetails()
  {
    I_U32 dspId;
    I_U8 tmpCnt;
    OamOilCfgBpmDbInitResp *oamOilCfgBpmDbInitResp = (OamOilCfgBpmDbInitResp*)(gCfgMsgBuf);
    LOG_PRINT(LOG_INFO,"copySystemDetails: Entering in function ");
    //PRINT_HEX_DUMP(LOG_DEBUG, oamOilCfgBpmDbInitResp, sizeof(OamOilCfgBpmDbInitResp));
    gSystemDetails = (sSystemCardInfo *) AlocOrdBuf(sizeof (sSystemCardInfo));
    memcpy(gSystemDetails, &(oamOilCfgBpmDbInitResp->cardInfo), sizeof(sSystemCardInfo));
    LOG_PRINT(DEBUG,"DB_INIT Details " );
    printSystemDetails(gSystemDetails);
    //Copying Dsp Details in gDspInfo
    for(tmpCnt=0;tmpCnt < MAX_DSP; tmpCnt++)
    {
      dspId = gSystemDetails->dspInfo[tmpCnt].dspId;
      memcpy(&(gDspInfo[dspId]),&(gSystemDetails->dspInfo[tmpCnt]),sizeof(sDspObjInfo));
      LOG_PRINT(DEBUG,"Dsp Deatils for DspId(%d) - size = %d",dspId, sizeof(sDspObjInfo));
      //PRINT_HEX_DUMP(LOG_DEBUG, &(gDspInfo[dspId]), sizeof(sDspObjInfo));
    }
    LOG_PRINT(LOG_INFO,"copySystemDetails: Exiting from function ");
  }

 /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
  /********************************* Function  Header*****************************
    Function Name     : copySystemDetails1U()
Parameters        : I_Void
Return type       : I_Void
Purpose           : It makes a copy of System details for 1U which is received from BPM.
Other Note        : Added for 1U CLOUD BSC 
   *******************************************************************************/
  I_Void copySystemDetails1U()
  {
    LOG_PRINT(LOG_INFO,"1U :copySystemDetails1U: Entering in function ");
    OamOilCfg1UCardInfoResp *oamOilCfg1UCardInfoResp = (OamOilCfg1UCardInfoResp *)(gCfgMsgBuf);
    PRINT_HEX_DUMP(LOG_DEBUG, oamOilCfg1UCardInfoResp, sizeof(OamOilCfg1UCardInfoResp));
		gCloudCardInfo = (sCloudCardInfo *) AlocOrdBuf(sizeof (sCloudCardInfo));
    memcpy(gCloudCardInfo, &(oamOilCfg1UCardInfoResp->cardInfo1U), sizeof(sCloudCardInfo));
    LOG_PRINT(DEBUG,"1U: 1U card  Details " );
    printSystemDetails1U(gCloudCardInfo);
    LOG_PRINT(LOG_INFO,"1U :copySystemDetails1U: Exiting from function ");
  }
  /********************************* Function  Header*****************************
Function Name     : printSystemDetails1U()
Parameters        :  *sCloudCardInfo
Return type       : I_Void
Purpose           : It prints complete card info received from bpm.
Other Note        : Added For 1U CLOUD BSC 
   *******************************************************************************/
  I_Void printSystemDetails1U(sCloudCardInfo *sysDetailPtr1U)
  {
    I_U8 i = 0;

    LOG_PRINT(LOG_DEBUG,"1U :Going To print rcvd system details for 1U card");
    LOG_PRINT(LOG_DEBUG,"1U :SELF chasisFrameId = 0x%x",sysDetailPtr1U->obmSelfCardInfo.chasisFrameId);
    LOG_PRINT(LOG_DEBUG,"1U :SELF slotID = 0x%x",sysDetailPtr1U->obmSelfCardInfo.slotID);
    LOG_PRINT(LOG_DEBUG,"1U :SELF cardType = 0x%x",sysDetailPtr1U->obmSelfCardInfo.cardType);
    LOG_PRINT(LOG_DEBUG,"1U :SELF cardSerialNumber = ");
		PRINT_HEX_DUMP(LOG_DEBUG,sysDetailPtr1U->obmSelfCardInfo.cardSerialNumber ,20);
    LOG_PRINT(LOG_DEBUG,"1U :SELF physicalPresenceState = 0x%x",sysDetailPtr1U->obmSelfCardInfo.physicalPresenceState);
    LOG_PRINT(LOG_DEBUG,"1U :SELF cardOperationalState = 0x%x",sysDetailPtr1U->obmSelfCardInfo.cardOperationalState);
    LOG_PRINT(LOG_DEBUG,"1U :SELF leftFanStatus = 0x%x",sysDetailPtr1U->obmSelfCardInfo.leftFanStatus);
    LOG_PRINT(LOG_DEBUG,"1U :SELF rightFanStatus = 0x%x",sysDetailPtr1U->obmSelfCardInfo.rightFanStatus);
    LOG_PRINT(LOG_DEBUG,"1U :SELF FacePlateTemp = 0x%x",sysDetailPtr1U->obmSelfCardInfo.facePlateTemp);
    LOG_PRINT(LOG_DEBUG,"1U :SELF PowerModuleTemp = 0x%x",sysDetailPtr1U->obmSelfCardInfo.powerModuleTemp);
		LOG_PRINT(LOG_DEBUG,"1U :SELF activeKernelVersionMajor  = 0x%x",sysDetailPtr1U->obmSelfCardInfo.activeKernelVersionMajor);
		LOG_PRINT(LOG_DEBUG,"1U :SELF activeKernelVersionMinor = 0x%x",sysDetailPtr1U->obmSelfCardInfo.activeKernelVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :SELF activeKernelVersionRevision = 0x%x",sysDetailPtr1U->obmSelfCardInfo.activeKernelVersionRevision);
		LOG_PRINT(LOG_DEBUG,"1U :SELF backupKernelVersionMajor = 0x%x",sysDetailPtr1U->obmSelfCardInfo.backupKernelVersionMajor);
		LOG_PRINT(LOG_DEBUG,"1U :SELF backupKernelVersionMinor = 0x%x",sysDetailPtr1U->obmSelfCardInfo.backupKernelVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :SELF backupKernelVersionRevision = 0x%x",sysDetailPtr1U->obmSelfCardInfo.backupKernelVersionRevision);
		LOG_PRINT(LOG_DEBUG,"1U :SELF uBootVersionMajor = 0x%x",sysDetailPtr1U->obmSelfCardInfo.uBootVersionMajor);
		LOG_PRINT(LOG_DEBUG,"1U :SELF uBootVersionMinor = 0x%x",sysDetailPtr1U->obmSelfCardInfo.uBootVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :SELF uBootVersionRevision = 0x%x",sysDetailPtr1U->obmSelfCardInfo.uBootVersionRevision);
		LOG_PRINT(LOG_DEBUG,"1U :SELF activeRamdiskVersionMajor = 0x%x",sysDetailPtr1U->obmSelfCardInfo.activeRamdiskVersionMajor);
		LOG_PRINT(LOG_DEBUG,"1U :SELF activeRamdiskVersionMinor = 0x%x",sysDetailPtr1U->obmSelfCardInfo.activeRamdiskVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :SELF activeRamdiskVersionRevision = 0x%x",sysDetailPtr1U->obmSelfCardInfo.activeRamdiskVersionRevision);
		LOG_PRINT(LOG_DEBUG,"1U :SELF backupRamdiskVersionMajor = 0x%x",sysDetailPtr1U->obmSelfCardInfo.backupRamdiskVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :SELF backupRamdiskVersionMinor = 0x%x",sysDetailPtr1U->obmSelfCardInfo.backupRamdiskVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :SELF backupRamdiskVersionRevision = 0x%x",sysDetailPtr1U->obmSelfCardInfo.backupRamdiskVersionRevision);
		/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
		LOG_PRINT(LOG_DEBUG,"1U :SELF boardId = 0x%x",sysDetailPtr1U->obmSelfCardInfo.boardId);
		LOG_PRINT(LOG_DEBUG,"1U :SELF powerStatus = 0x%x",sysDetailPtr1U->obmSelfCardInfo.powerStatus);
		LOG_PRINT(LOG_DEBUG,"1U :SELF leftFanSpeed = 0x%x",sysDetailPtr1U->obmSelfCardInfo.leftFanSpeed);
		LOG_PRINT(LOG_DEBUG,"1U :SELF rightFanSpeed = 0x%x",sysDetailPtr1U->obmSelfCardInfo.rightFanSpeed);
		LOG_PRINT(LOG_DEBUG,"1U :SELF imxTemp = 0x%x",sysDetailPtr1U->obmSelfCardInfo.imxTemp);
		/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
    LOG_PRINT(LOG_DEBUG,"1U :MATE chasisFrameId = 0x%x",sysDetailPtr1U->obmMateCardInfo.chasisFrameId);
    LOG_PRINT(LOG_DEBUG,"1U :MATE slotID = 0x%x",sysDetailPtr1U->obmMateCardInfo.slotID);
    LOG_PRINT(LOG_DEBUG,"1U :MATE cardType = 0x%x",sysDetailPtr1U->obmMateCardInfo.cardType);
    LOG_PRINT(LOG_DEBUG,"1U :MATE cardSerialNumber = ");
		PRINT_HEX_DUMP(LOG_DEBUG,sysDetailPtr1U->obmMateCardInfo.cardSerialNumber ,20);
    LOG_PRINT(LOG_DEBUG,"1U :MATE physicalPresenceState = 0x%x",sysDetailPtr1U->obmMateCardInfo.physicalPresenceState);
    LOG_PRINT(LOG_DEBUG,"1U :MATE cardOperationalState = 0x%x",sysDetailPtr1U->obmMateCardInfo.cardOperationalState);
    LOG_PRINT(LOG_DEBUG,"1U :MATE leftFanStatus = 0x%x",sysDetailPtr1U->obmMateCardInfo.leftFanStatus);
    LOG_PRINT(LOG_DEBUG,"1U :MATE rightFanStatus = 0x%x",sysDetailPtr1U->obmMateCardInfo.rightFanStatus);
    LOG_PRINT(LOG_DEBUG,"1U :MATE FacePlateTemp = 0x%x",sysDetailPtr1U->obmMateCardInfo.facePlateTemp);
    LOG_PRINT(LOG_DEBUG,"1U :MATE PowerModuleTemp = 0x%x",sysDetailPtr1U->obmMateCardInfo.powerModuleTemp);
		LOG_PRINT(LOG_DEBUG,"1U :MATE activeKernelVersionMajor  = 0x%x",sysDetailPtr1U->obmMateCardInfo.activeKernelVersionMajor);
		LOG_PRINT(LOG_DEBUG,"1U :MATE activeKernelVersionMinor = 0x%x",sysDetailPtr1U->obmMateCardInfo.activeKernelVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :MATE activeKernelVersionRevision = 0x%x",sysDetailPtr1U->obmMateCardInfo.activeKernelVersionRevision);
		LOG_PRINT(LOG_DEBUG,"1U :MATE backupKernelVersionMajor = 0x%x",sysDetailPtr1U->obmMateCardInfo.backupKernelVersionMajor);
		LOG_PRINT(LOG_DEBUG,"1U :MATE backupKernelVersionMinor = 0x%x",sysDetailPtr1U->obmMateCardInfo.backupKernelVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :MATE backupKernelVersionRevision = 0x%x",sysDetailPtr1U->obmMateCardInfo.backupKernelVersionRevision);
		LOG_PRINT(LOG_DEBUG,"1U :MATE uBootVersionMajor = 0x%x",sysDetailPtr1U->obmMateCardInfo.uBootVersionMajor);
		LOG_PRINT(LOG_DEBUG,"1U :MATE uBootVersionMinor = 0x%x",sysDetailPtr1U->obmMateCardInfo.uBootVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :MATE uBootVersionRevision = 0x%x",sysDetailPtr1U->obmMateCardInfo.uBootVersionRevision);
		LOG_PRINT(LOG_DEBUG,"1U :MATE activeRamdiskVersionMajor = 0x%x",sysDetailPtr1U->obmMateCardInfo.activeRamdiskVersionMajor);
		LOG_PRINT(LOG_DEBUG,"1U :MATE activeRamdiskVersionMinor = 0x%x",sysDetailPtr1U->obmMateCardInfo.activeRamdiskVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :MATE activeRamdiskVersionRevision = 0x%x",sysDetailPtr1U->obmMateCardInfo.activeRamdiskVersionRevision);
		LOG_PRINT(LOG_DEBUG,"1U :MATE backupRamdiskVersionMajor = 0x%x",sysDetailPtr1U->obmMateCardInfo.backupRamdiskVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :MATE backupRamdiskVersionMinor = 0x%x",sysDetailPtr1U->obmMateCardInfo.backupRamdiskVersionMinor);
		LOG_PRINT(LOG_DEBUG,"1U :MATE backupRamdiskVersionRevision = 0x%x",sysDetailPtr1U->obmMateCardInfo.backupRamdiskVersionRevision);
		/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
		LOG_PRINT(LOG_DEBUG,"1U :MATE boardId = 0x%x",sysDetailPtr1U->obmSelfCardInfo.boardId);
		LOG_PRINT(LOG_DEBUG,"1U :MATE powerStatus = 0x%x",sysDetailPtr1U->obmSelfCardInfo.powerStatus);
		LOG_PRINT(LOG_DEBUG,"1U :MATE leftFanSpeed = 0x%x",sysDetailPtr1U->obmSelfCardInfo.leftFanSpeed);
		LOG_PRINT(LOG_DEBUG,"1U :MATE rightFanSpeed = 0x%x",sysDetailPtr1U->obmSelfCardInfo.rightFanSpeed);
		LOG_PRINT(LOG_DEBUG,"1U :MATE imxTemp = 0x%x",sysDetailPtr1U->obmSelfCardInfo.imxTemp);
		/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
		for(i=0;i<MAX_PWR_SUPPLY;i++)
		{
				LOG_PRINT(LOG_DEBUG,"1U :obmPwrSupplyInfo : [%d] chasisFrameId = 0x%x",i,sysDetailPtr1U->obmPwrSupplyInfo[i].chasisFrameId);
				LOG_PRINT(LOG_DEBUG,"1U :obmPwrSupplyInfo : [%d] slotID = 0x%x",i,sysDetailPtr1U->obmPwrSupplyInfo[i].slotID);
				LOG_PRINT(LOG_DEBUG,"1U :obmPwrSupplyInfo : [%d] cardType = 0x%x",i,sysDetailPtr1U->obmPwrSupplyInfo[i].cardType);
				LOG_PRINT(LOG_DEBUG,"1U :obmPwrSupplyInfo : [%d] physicalPresenceState = 0x%x",i,sysDetailPtr1U->obmPwrSupplyInfo[i].physicalPresenceState);
				LOG_PRINT(LOG_DEBUG,"1U :obmPwrSupplyInfo : [%d] powerSupplyStatus = 0x%x",i,sysDetailPtr1U->obmPwrSupplyInfo[i].powerSupplyStatus);
		}
		for(i=0;i<MAX_FAN_FILTER;i++)
		{
				LOG_PRINT(LOG_DEBUG,"1U :obmFanFilterInfo : [%d] chasisFrameId = 0x%x",i,sysDetailPtr1U->obmFanFilterInfo[i].chasisFrameId);
				LOG_PRINT(LOG_DEBUG,"1U :obmFanFilterInfo : [%d] FanFilterId = 0x%x",i,sysDetailPtr1U->obmFanFilterInfo[i].fanFilterId);
				LOG_PRINT(LOG_DEBUG,"1U :obmFanFilterInfo : [%d] physicalPresenceState = 0x%x",i,sysDetailPtr1U->obmFanFilterInfo[i].physicalPresenceState);
		}
    LOG_PRINT(LOG_INFO,"1U :printSystemDetails1U :: Exiting from function ");
	}

/********************************* Function  Header*****************************
Function Name     : UpdateOrInsertObmCardInfoTableApi(sObmCardInfo var)  
Parameters        : sObmCardInfo *ptrr 
Return type       : I_Void
Purpose           : It makes a update System details  for UpdateOrInsertObmCardInfoTableApi 1U after receiving Active Notification from BPM.
Other Note        : Added For 1U CLOUD BSC 
*******************************************************************************/
I_Void UpdateOrInsertObmCardInfoTableApi(sObmCardInfo var)
{
  LOG_PRINT(LOG_DEBUG,"1U: Entering UpdateOrInsertObmCardInfoTableApi()");
	if((var.slotID != SLOTID_1_1U) && (var.slotID != SLOTID_2_1U))
	{
		LOG_PRINT(LOG_DEBUG,"1U: INVALID slotId[%d] rcvd from PLATFORM, skipping",var.slotID);
		return;
	}
	if(var.chasisFrameId != 1) 
	{
		LOG_PRINT(LOG_DEBUG,"1U: INVALID chassisId[%d] rcvd from PLATFORM, skipping",var.chasisFrameId);
		return;
	}
	/*if(var.cardType != CARD_TYPE_OBM) 
	{
		LOG_PRINT(LOG_DEBUG,"1U: INVALID cardType[%d] rcvd from PLATFORM, skipping",var.cardType);
		return;
  }*/
	ObmCardInfoTableApi obmCardInfoTableApi;
	memcpy(&obmCardInfoTableApi,&var,sizeof(ObmCardInfoTableApi));
	
	LOG_PRINT(DEBUG,"1U: Going for update for ChassisId[%d] slotId[%d] in ObmCardInfoTableApi",obmCardInfoTableApi.chasisFrameId,obmCardInfoTableApi.slotID);
	if(updateObmCardInfoTable(&obmCardInfoTableApi) == CLIB_SUCCESS)
	{
			LOG_PRINT(LOG_DEBUG,"1U: Update for ObmCardInfoTableApi for chassisId[%d] slotId[%d] SUCCESS",obmCardInfoTableApi.chasisFrameId,obmCardInfoTableApi.slotID);
	}
	else
	{
		LOG_PRINT(LOG_DEBUG,"1U: Update FAILED :::: Going to INSERT ObmCardInfoTableApi ChassisId[%d] slotId[%d]",obmCardInfoTableApi.chasisFrameId,obmCardInfoTableApi.slotID);
		if(insertObmCardInfoTable(&obmCardInfoTableApi) == CLIB_SUCCESS)
		{
				LOG_PRINT(LOG_DEBUG,"1U: Insert for ObmCardInfoTableApi SUCCESS");
		}
		else
		{
				LOG_PRINT(LOG_DEBUG,"1U: Insert for ObmCardInfoTableApi Table FAILED");
		}
	}	
  LOG_PRINT(LOG_DEBUG,"1U: Exiting UpdateOrInsertObmCardInfoTableApi()");
}
/********************************* Function  Header*****************************
Function Name     : UpdateOrInsertPowerSupplyTable(sPowerSupplyInfo var)
Parameters        : sPowerSupplyInfo var 
Return type       : I_Void
Purpose           : It makes a update data in PowerSupplyInfoTable for 1U after receiving Active Notification from BPM.
Other Note        : Added For 1U CLOUD BSC 
*******************************************************************************/
I_Void UpdateOrInsertPowerSupplyTable(sPowerSupplyInfo var)
{
	LOG_PRINT(DEBUG,"1U: Entering in function UpdateOrInsertPowerSupplyTable()");
	if((var.slotID != SLOTID_1_1U) && (var.slotID != SLOTID_2_1U))
	{
		LOG_PRINT(LOG_DEBUG,"1U: INVALID slotId[%d] rcvd from PLATFORM, skipping",var.slotID);
		return;
	}
	if(var.chasisFrameId != 1) 
	{
		LOG_PRINT(LOG_DEBUG,"1U: INVALID chassisId[%d] rcvd from PLATFORM, skipping",var.chasisFrameId);
		return;
	}
	/*if(var.cardType != CARD_TYPE_OBF) 
	{
		LOG_PRINT(LOG_DEBUG,"1U: INVALID cardType[%d] rcvd from PLATFORM, skipping",var.cardType);
		return;
  }*/
	PowerSupplyTableApi powerSupplyTableApi; 
	//memcpy(&powerSupplyTableApi,&var,sizeof(PowerSupplyTableApi));
	powerSupplyTableApi.chasisFrameId = var.chasisFrameId;
	powerSupplyTableApi.slotID = var.slotID;
	powerSupplyTableApi.cardType = var.cardType;
	powerSupplyTableApi.physicalPresenceState = var.physicalPresenceState;
	powerSupplyTableApi.powerSupplyStatus = (I_U32)var.powerSupplyStatus;
	LOG_PRINT(DEBUG,"1U: Going for update for ChassisId[%d] slotId[%d] in PowerSupplyTableApi",powerSupplyTableApi.chasisFrameId,powerSupplyTableApi.slotID);
	if(updatePowerSupplyTable(&powerSupplyTableApi) == CLIB_SUCCESS)
	{
			LOG_PRINT(LOG_DEBUG,"1U: Update for PowerSupplyTableApi for SUCCESS");
	}
	else
	{
		LOG_PRINT(LOG_DEBUG,"1U: Now row present for chassidId[%d] slotID[%d] in PowerSupplyTableApi Going to INSERT it",powerSupplyTableApi.chasisFrameId,powerSupplyTableApi.slotID);
		if(insertPowerSupplyTable(&powerSupplyTableApi) == CLIB_SUCCESS) 
		{
				LOG_PRINT(LOG_DEBUG,"1U: Insert for PowerSupplyTableApi is SUCCESS");
		}
		else
		{
				LOG_PRINT(LOG_DEBUG,"1U: Insert for PowerSupplyTableApi is FAILED");
		}
	}
	LOG_PRINT(DEBUG,"1U: Exiting from function UpdateOrInsertPowerSupplyTable()");
} 

/********************************* Function  Header*****************************
Function Name     : UpdateOrInsertFanFilterIdTableApi(sFanFilterInfo var)
Parameters        : sFanFilterInfo var 
Return type       : I_Void
Purpose           : It makes a update data in FanFilterInfoTable for 1U after receiving Active Notification from BPM.
Other Note        : Added For 1U CLOUD BSC 
*******************************************************************************/
I_Void UpdateOrInsertFanFilterIdTableApi(sFanFilterInfo var)
{
	LOG_PRINT(DEBUG,"1U: Entering in function UpdateOrInsertFanFilterIdTableApi()");
	if((var.fanFilterId != SLOTID_1_1U) && (var.fanFilterId != SLOTID_2_1U))
	{
		LOG_PRINT(LOG_DEBUG,"1U: INVALID slotId[%d] rcvd from PLATFORM, skipping",var.fanFilterId);
		return;
	}
	if(var.chasisFrameId != 1) 
	{
		LOG_PRINT(LOG_DEBUG,"1U: INVALID chassisId[%d] rcvd from PLATFORM, skipping",var.chasisFrameId);
		return;
	}
	FanFilterIdTableApi fanFilterIdTableApi; 
	memcpy(&fanFilterIdTableApi,&var,sizeof(FanFilterIdTableApi));
	LOG_PRINT(DEBUG,"1U: Going for update for ChassisId[%d] FanFilterId[%d] in FanFilterIdTableApi",fanFilterIdTableApi.chasisFrameId,fanFilterIdTableApi.fanFilterId);
	if(updateFanFilterIdTable(&fanFilterIdTableApi) == CLIB_SUCCESS)
	{
			LOG_PRINT(LOG_DEBUG,"1U: Update for FanFilterIdTableApi for row SUCCESS");
	}
	else
	{
		LOG_PRINT(DEBUG,"1U: No Row exist for ChassisId[%d] FanFilterId[%d] in FanFilterIdTableApi now Going INSERT",fanFilterIdTableApi.chasisFrameId,fanFilterIdTableApi.fanFilterId);
		if(insertFanFilterIdTable(&fanFilterIdTableApi) == CLIB_SUCCESS)
		{
				LOG_PRINT(LOG_DEBUG,"1U: Insert for FanFilterIdTableApi is SUCCESS");
		}
		else
		{
				LOG_PRINT(LOG_DEBUG,"1U: Insert for FanFilterIdTableApi is FAILED");
		}
	}
	LOG_PRINT(DEBUG,"1U: Exiting from function UpdateOrInsertFanFilterIdTableApi()");
}
/********************************* Function  Header*****************************
Function Name     : UpdateOrInsertChasisFrameTableApi()
Parameters        : I_Void
Return type       : I_Void
Purpose           : It makes a update data in ChasisFrameTableApi for 1U after receiving Active Notification from BPM.
Other Note        : Added For 1U CLOUD BSC 
*******************************************************************************/
I_Void UpdateOrInsertChasisFrameTableApi()
{
	LOG_PRINT(DEBUG,"1U: Entering in function UpdateOrInsertChasisFrameTableApi()");
	I_U32 noOfObmCard=ZERO;
	I_U32 noOfObfCard=ZERO;
  I_U32 i=ZERO;
  if(gCloudCardInfo->obmSelfCardInfo.physicalPresenceState == PRESENT)
	{
		noOfObmCard++;
	}	
  if(gCloudCardInfo->obmMateCardInfo.physicalPresenceState == PRESENT)
	{
		noOfObmCard++;
	}
	for(i=ZERO;i<MAX_PWR_SUPPLY;i++)
	{
  	if(gCloudCardInfo->obmPwrSupplyInfo[i].physicalPresenceState == PRESENT)
		{
			noOfObfCard++;
		}
	}
	ChasisFrameTableApi chasisFrameTableApi;
	chasisFrameTableApi.chasisFrameId = gCloudCardInfo->obmSelfCardInfo.chasisFrameId;
	chasisFrameTableApi.totalNumObmCard = noOfObmCard;
	chasisFrameTableApi.totalNumObfCard = noOfObfCard;
	LOG_PRINT(DEBUG,"1U: Going for update for ChassisId[%d] totalNumObmCard[%d] totalNumObfCard[%d] in ChasisFrameTableApi",chasisFrameTableApi.chasisFrameId,chasisFrameTableApi.totalNumObmCard,chasisFrameTableApi.totalNumObfCard);
	if(updateChasisFrameTable(&(chasisFrameTableApi)) == CLIB_SUCCESS)
	{
			LOG_PRINT(LOG_DEBUG,"1U: Update for ChasisFrameTableApi for row SUCCESS");
	}
	else
	{
		LOG_PRINT(DEBUG,"1U: No Row exist for ChassisId[%d] totalNumObmCard[%d] totalNumObfCard[%d] in ChasisFrameTableApi now Going INSERT",chasisFrameTableApi.chasisFrameId,chasisFrameTableApi.totalNumObmCard,chasisFrameTableApi.totalNumObfCard);
		if(insertChasisFrameTable(&(chasisFrameTableApi)) == CLIB_SUCCESS)
		{
				LOG_PRINT(LOG_DEBUG,"1U: Insert for ChasisFrameTableApi is SUCCESS");
		}
		else
		{
				LOG_PRINT(LOG_DEBUG,"1U: Insert for ChasisFrameTableApi is FAILED");
		}
	}
	LOG_PRINT(DEBUG,"1U: Exiting from function UpdateOrInsertChasisFrameTableApi()");
}
/********************************* Function  Header*****************************
Function Name     : updateSystemDetails1U()
Parameters        : I_Void
Return type       : I_Void
Purpose           : It makes a update System details  for 1U after receiving Active Notification from BPM.
Other Note        : Added For 1U CLOUD BSC 
*******************************************************************************/
I_Void updateSystemDetails1U()
{
	LOG_PRINT(DEBUG,"1U: Entering in function updateSystemDetails1U()");
	I_U32 i=ZERO;
	if(gCloudCardInfo == NULL)	
	{
      LOG_PRINT(LOG_CRITICAL,"1U: updateSystemDetails1U: NO System Details Available System may not behave properly");
	}
	else
	{
      LOG_PRINT(LOG_DEBUG,"1U: updateSystemDetails: Updating/Inserting System Details for 1U Inventory Objects");
			UpdateOrInsertObmCardInfoTableApi(gCloudCardInfo->obmSelfCardInfo);
			UpdateOrInsertObmCardInfoTableApi(gCloudCardInfo->obmMateCardInfo);
			for(i=ZERO;i<MAX_PWR_SUPPLY;i++)
			{
					UpdateOrInsertPowerSupplyTable(gCloudCardInfo->obmPwrSupplyInfo[i]);
			}
			for(i=ZERO;i<MAX_FAN_FILTER;i++)
			{
					UpdateOrInsertFanFilterIdTableApi(gCloudCardInfo->obmFanFilterInfo[i]);
			}
			UpdateOrInsertChasisFrameTableApi();
	}
	LOG_PRINT(DEBUG,"1U: Exiting from function updateSystemDetails1U()");
}
/********************************* Function  Header*****************************
Function Name     : updateFanStatusInObmCardInfoTableApi(SysAlarm* recAlarmPtr,I_U8 value)
Parameters        : SysAlarm* recAlarmPtr & I_U8 value
Return type       : I_Void
Purpose           : It makes a update System details after receiving Active Notification from BPM.
Other Note        : Added For 1U CLOUD BSC 
*******************************************************************************/
I_Void updateFanStatusInObmCardInfoTableApi(SysAlarm* recAlarmPtr,I_U8 value)
{
	LOG_PRINT(DEBUG,"1U: Entering function updateFanStatusInObmCardInfoTableApi()");
	ObmCardInfoTableIndices obmCardInfoTableIndices;
	ObmCardInfoTableApi *obmCardInfoTableApi =  NULL;
	obmCardInfoTableIndices.chasisFrameId = recAlarmPtr->key1;
	obmCardInfoTableIndices.slotID = recAlarmPtr->key2;
  if(getObmCardInfoTable(&obmCardInfoTableIndices,&obmCardInfoTableApi) == CLIB_SUCCESS)
	{
	   if(recAlarmPtr->key3 == SLOTID_1_1U) 
		 {
		   obmCardInfoTableApi->leftFanStatus = value;	
       LOG_PRINT(DEBUG,"1U: Update rcvd for LEFT FAN");
		   /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
		   obmCardInfoTableApi->leftFanSpeed = recAlarmPtr->key4;	
       LOG_PRINT(DEBUG,"1U: FAN SPEED rcvd for LEFT FAN is [%d] rpm",obmCardInfoTableApi->leftFanSpeed);
		   /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
		 }
		 else
		 {
		   obmCardInfoTableApi->rightFanStatus = value;	
       LOG_PRINT(DEBUG,"1U: Update rcvd for RIGHT FAN");
		 	 /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
		   obmCardInfoTableApi->rightFanSpeed = recAlarmPtr->key4;	
       LOG_PRINT(DEBUG,"1U: FAN SPEED rcvd for RIGHT FAN is [%d] rpm",obmCardInfoTableApi->rightFanSpeed);
		 	 /*Added for 1U BSC Gaurav Sinha 05-07-2016*/
		 }
		 if(updateObmCardInfoTable(obmCardInfoTableApi) == CLIB_SUCCESS)
			{
				LOG_PRINT(LOG_DEBUG,"1U: Update for ObmCardInfoTableApi for chassisId[%d] slotId[%d] SUCCESS",obmCardInfoTableApi->chasisFrameId,obmCardInfoTableApi->slotID);
			}
			else
			{
				LOG_PRINT(LOG_DEBUG,"1U: Update FAILED :::: ObmCardInfoTableApi ChassisId[%d] slotId[%d]",obmCardInfoTableApi->chasisFrameId,obmCardInfoTableApi->slotID);
			}
	  free(obmCardInfoTableApi);
	}
	else
	{
			LOG_PRINT(DEBUG,"1U: Get failed for ObmCardInfoTableApi");
	}
	LOG_PRINT(DEBUG,"1U: Exiting function updateFanStatusInObmCardInfoTableApi()");

}
/********************************* Function  Header*****************************
Function Name     : updatePhysicalPresenceStateInObmCardInfoTableApi (SysAlarm* recAlarmPtr)
Parameters        : SysAlarm* recAlarmPtr 
Return type       : I_Void
Purpose           : It makes a update System details after receiving Active Notification from BPM.
Other Note        : Added For 1U CLOUD BSC
*******************************************************************************/
I_Void updatePhysicalPresenceStateInObmCardInfoTableApi(SysAlarm *recAlarmPtr)
{
	LOG_PRINT(DEBUG,"1U: Entering function updatePhysicalPresenceStateInObmCardInfoTableApi()");
	ObmCardInfoTableApi *obmCardInfoTableApi = NULL;
	ObmCardInfoTableApi *tmpObmCardInfoTableApi = NULL;
	ObmCardInfoTableIndices obmCardInfoTableIndices;
	I_U16 outRows=ZERO;
	I_U32 outSize=ZERO;
	I_U32 cntVar=ZERO;
	if(getallObmCardInfoTable(&obmCardInfoTableApi,&outRows,&outSize) != CLIB_SUCCESS)
	{
	  LOG_PRINT(LOG_INFO,"1U: No Row in ObmCardInfoTableApi");
    return;
	}
	else
	{
		 if(outRows == 1)
    {
      LOG_PRINT(LOG_INFO,"1U: Exiting from updatePhysicalPresenceStateInObmCardInfoTableApi");
      free(obmCardInfoTableApi);
      return;
    }
		if(obmCardInfoTableApi->slotID != recAlarmPtr->key2)
    {
      LOG_PRINT(LOG_DEBUG,"1U:  Updation for Slot Id: %d in firstRow",obmCardInfoTableApi->slotID);
			obmCardInfoTableApi->physicalPresenceState = PRESENT;
			if(updateObmCardInfoTable(obmCardInfoTableApi) == CLIB_SUCCESS)
			{
				LOG_PRINT(LOG_DEBUG,"1U: Update for ObmCardInfoTableApi for chassisId[%d] slotId[%d] SUCCESS",obmCardInfoTableApi->chasisFrameId,obmCardInfoTableApi->slotID);
				cntVar++;
			}
			else
			{
				LOG_PRINT(LOG_DEBUG,"1U: Update FAILED :::: ObmCardInfoTableApi ChassisId[%d] slotId[%d]",obmCardInfoTableApi->chasisFrameId,obmCardInfoTableApi->slotID);
        free(obmCardInfoTableApi);
				return;
			}
    }
    else
    {
			tmpObmCardInfoTableApi = (ObmCardInfoTableApi *)((I_U8 *)obmCardInfoTableApi + outSize);
      LOG_PRINT(LOG_DEBUG,"1U: Updation for Slot Id:: %d in secondRow",tmpObmCardInfoTableApi->slotID);
			tmpObmCardInfoTableApi->physicalPresenceState = PRESENT;
			if(updateObmCardInfoTable(tmpObmCardInfoTableApi) == CLIB_SUCCESS)
			{
				LOG_PRINT(LOG_DEBUG,"1U: Update for ObmCardInfoTableApi for chassisId[%d] slotId[%d] SUCCESS",tmpObmCardInfoTableApi->chasisFrameId,tmpObmCardInfoTableApi->slotID);
				cntVar++;
			}
			else
			{
				LOG_PRINT(LOG_DEBUG,"1U: Update FAILED :::: ObmCardInfoTableApi ChassisId[%d] slotId[%d]",tmpObmCardInfoTableApi->chasisFrameId,tmpObmCardInfoTableApi->slotID);
        free(obmCardInfoTableApi);
				return;
			}
    }
	 if(NULL != obmCardInfoTableApi)
	 {
     free(obmCardInfoTableApi);
	 }
	 if(cntVar>ZERO)
	 {
		ChasisFrameTableIndices chasisFrameTableIndices;
		ChasisFrameTableApi *chasisFrameTableApi = NULL;
		chasisFrameTableIndices.chasisFrameId  = recAlarmPtr->key1; 
		if(getChasisFrameTable(&chasisFrameTableIndices,&chasisFrameTableApi) == CLIB_SUCCESS)
		{
		  LOG_PRINT(DEBUG,"get SUCCESS for ChasisFrameTableApi for chassId[%d] incrementing totalNumObmCard",chasisFrameTableIndices.chasisFrameId);
			chasisFrameTableApi->totalNumObmCard = chasisFrameTableApi->totalNumObmCard + 1;
			if(updateChasisFrameTable(chasisFrameTableApi) == CLIB_SUCCESS)
			{
		    LOG_PRINT(DEBUG,"UPDATE SUCCESS for ChasisFrameTableApi totalNumObmCard [%d] after updation",chasisFrameTableApi->totalNumObmCard);
			}
			else
			{
		    LOG_PRINT(DEBUG,"UPDATE FAILED for ChasisFrameTableApi ");
				free (chasisFrameTableApi);
			}
		}
		else
		{
		  LOG_PRINT(DEBUG,"get FAILED for ChasisFrameTableApi for chassId[%d]",chasisFrameTableIndices.chasisFrameId);
		}
	 }
	 if(NULL != obmCardInfoTableApi)
	 {
		 free(obmCardInfoTableApi);
	 }
	}
	LOG_PRINT(DEBUG,"1U: Exiting function updatePhysicalPresenceStateInObmCardInfoTableApi()");
}
/********************************* Function  Header*****************************
Function Name     : deleteEntryFromObmCardInfoTableApi (SysAlarm* recAlarmPtr)
Parameters        : SysAlarm* recAlarmPtr 
Return type       : I_Void
Purpose           : It makes a update System details after receiving Active Notification from BPM.
Other Note        : Added For 1U CLOUD BSC
*******************************************************************************/
I_Void deleteEntryFromObmCardInfoTableApi(SysAlarm *recAlarmPtr)
{
	LOG_PRINT(DEBUG,"1U: Entering function deleteEntryFromObmCardInfoTableApi()");
	ObmCardInfoTableApi *obmCardInfoTableApi = NULL;
	ObmCardInfoTableApi *tmpObmCardInfoTableApi = NULL;
	ObmCardInfoTableIndices obmCardInfoTableIndices;
	I_U16 outRows=ZERO;
	I_U32 outSize=ZERO;
	if(getallObmCardInfoTable(&obmCardInfoTableApi,&outRows,&outSize) != CLIB_SUCCESS)
	{
	  LOG_PRINT(LOG_INFO,"1U: No Row in ObmCardInfoTableApi");
    return;
	}
	else
	{
		 if(outRows == 1)
    {
      LOG_PRINT(LOG_INFO,"1U: Exiting from deleteEntryFromObmCardInfoTableApi");
      free(obmCardInfoTableApi);
      return;
    }
    obmCardInfoTableIndices.chasisFrameId = recAlarmPtr->key1;
		if(obmCardInfoTableApi->slotID != recAlarmPtr->key2)
    {
      LOG_PRINT(LOG_DEBUG,"1U:  deletion for Slot Id: %d in firstRow",obmCardInfoTableApi->slotID);
      obmCardInfoTableIndices.slotID = obmCardInfoTableApi->slotID;
    }
    else
    {
			tmpObmCardInfoTableApi = (ObmCardInfoTableApi *)((I_U8 *)obmCardInfoTableApi + outSize);
      LOG_PRINT(LOG_DEBUG,"1U: deletion for Slot Id:: %d in secondRow",tmpObmCardInfoTableApi->slotID);
      obmCardInfoTableIndices.slotID = tmpObmCardInfoTableApi->slotID;
    }
		if(deleteObmCardInfoTable(&obmCardInfoTableIndices) == CLIB_SUCCESS)
		{
      LOG_PRINT(LOG_DEBUG,"1U: Deletion SUCCESS for Slot Id[%d] Going to update ChasisFrameTableApi ",obmCardInfoTableApi->slotID);
			ChasisFrameTableIndices chasisFrameTableIndices;
			ChasisFrameTableApi *chasisFrameTableApi = NULL;
			chasisFrameTableIndices.chasisFrameId  = recAlarmPtr->key1; 
			if(getChasisFrameTable(&chasisFrameTableIndices,&chasisFrameTableApi) == CLIB_SUCCESS)
			{
				LOG_PRINT(DEBUG,"get SUCCESS for ChasisFrameTableApi for chassId[%d] decrementing totalNumObmCard",chasisFrameTableIndices.chasisFrameId);
				chasisFrameTableApi->totalNumObmCard = chasisFrameTableApi->totalNumObmCard - 1;
				if(updateChasisFrameTable(chasisFrameTableApi) == CLIB_SUCCESS)
				{
					LOG_PRINT(DEBUG,"UPDATE SUCCESS for ChasisFrameTableApi totalNumObmCard [%d] after updation",chasisFrameTableApi->totalNumObmCard);
				}
				else
				{
					LOG_PRINT(DEBUG,"UPDATE FAILED for ChasisFrameTableApi ");
				}
			  if(chasisFrameTableApi != NULL)
			  {
				 free(chasisFrameTableApi);
			  }
			}
			else
			{
				LOG_PRINT(DEBUG,"get FAILED for ChasisFrameTableApi for chassId[%d]",chasisFrameTableIndices.chasisFrameId);
			}
		}
		else
		{
      LOG_PRINT(LOG_DEBUG,"1U: Deletion FAILED for Slot Id:: %d ",tmpObmCardInfoTableApi->slotID);
		}
	  if(NULL != obmCardInfoTableApi)
	  {
     free(obmCardInfoTableApi);
	  }
	}
	LOG_PRINT(DEBUG,"1U: Exiting function deleteEntryFromObmCardInfoTableApi()");
}
/********************************* Function  Header*****************************
Function Name     : updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi(SysAlarm *recAlarmPtr,I_U8 value)
Parameters        : SysAlarm *recAlarmPtr,I_U8 value 
Return type       : I_Void
Purpose           : It makes a update System details after receiving Active Notification from BPM.
Other Note        : Added For 1U CLOUD BSC 
*******************************************************************************/
I_Void updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi(SysAlarm *recAlarmPtr,I_U8 value)
{
	LOG_PRINT(DEBUG,"1U: Entering function updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi()");
	PowerSupplyTableIndices powerSupplyTableIndices;
	PowerSupplyTableApi *powerSupplyTableApi = NULL;
	ChasisFrameTableIndices chasisFrameTableIndices;
	ChasisFrameTableApi *chasisFrameTableApi = NULL;
	I_U8 countToUpdate = I_FALSE;
	powerSupplyTableIndices.chasisFrameId = recAlarmPtr->key1;
	powerSupplyTableIndices.slotID = recAlarmPtr->key2;
	if((recAlarmPtr->sysalarmId == INFO_OBF_PRESENT_PM_OAM) || (recAlarmPtr->sysalarmId == INFO_OBF_ABSENT_PM_OAM))
	{
		chasisFrameTableIndices.chasisFrameId  = recAlarmPtr->key1; 
		if(getChasisFrameTable(&chasisFrameTableIndices,&chasisFrameTableApi) == CLIB_SUCCESS)
		{
			LOG_PRINT(DEBUG,"get SUCCESS for ChasisFrameTableApi for chassId[%d] ",chasisFrameTableIndices.chasisFrameId);
			countToUpdate = I_TRUE;
		}
		else
		{
			LOG_PRINT(DEBUG,"get FAILED for ChasisFrameTableApi for chassId[%d] ",chasisFrameTableIndices.chasisFrameId);
		  return;	
		}
	}
  if(value == ONE)
	{
	  LOG_PRINT(DEBUG,"1U: UPDATE for chassisFrameId[%d] slotID[%d]",powerSupplyTableIndices.chasisFrameId,powerSupplyTableIndices.slotID);
	  if(getPowerSupplyTable(&powerSupplyTableIndices,&powerSupplyTableApi) == CLIB_SUCCESS)
		{
			LOG_PRINT(DEBUG,"1U: Row present :: Going for Upadate of PhysicalPresenceState");
			//powerSupplyTableApi->physicalPresenceState = PRESENT;
			if(recAlarmPtr->sysalarmId == INFO_POWER_FEED_PRESNT_PM_OAM)
			{
			  powerSupplyTableApi->powerSupplyStatus = PRESENT;	
			}
			else if(recAlarmPtr->sysalarmId == INFO_POWER_FEED_ABSENT_PM_OAM)
			{
			  powerSupplyTableApi->powerSupplyStatus = NOT_PRESENT;	
			}
			if(updatePowerSupplyTable(powerSupplyTableApi) == CLIB_SUCCESS)
			{
					LOG_PRINT(LOG_DEBUG,"1U: Update for PowerSupplyTableApi for SUCCESS");
				  if(countToUpdate == I_TRUE)
					{
						LOG_PRINT(DEBUG,"Going to Increment totalNumObfCard in ChasisFrameTableApi[%d]",chasisFrameTableIndices.chasisFrameId);
						chasisFrameTableApi->totalNumObfCard = chasisFrameTableApi->totalNumObfCard + 1;
					}	
			}
			else
			{
				LOG_PRINT(LOG_DEBUG,"1U: UPDATE FAILED chassidId[%d] slotID[%d] in PowerSupplyTableApi ",powerSupplyTableApi->chasisFrameId,powerSupplyTableApi->slotID);
				free(powerSupplyTableApi);
				if(NULL != chasisFrameTableApi)
				{
					free(chasisFrameTableApi);
					chasisFrameTableApi = NULL;
				}
				return;
			}
      /*Commented for Mantis #0031729 Gaurav Sinha 23 Aug 2016 double-free of the *ptr*/
		  /*if(NULL !=powerSupplyTableApi)
			{
				free(powerSupplyTableApi);
			}*/
      /*Commented for Mantis #0031729 Gaurav Sinha 23 Aug 2016 double-free of the *ptr*/
		}
		else
		{
			LOG_PRINT(DEBUG,"1U: Row not present :: exiting from updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi");
			if(NULL != chasisFrameTableApi)
			{
				free(chasisFrameTableApi);
				chasisFrameTableApi = NULL;
			}
			return;
		}
	}
	else if(value == TWO)
	{
	  LOG_PRINT(DEBUG,"1U: DELETE for chassisFrameId[%d] slotID[%d]",powerSupplyTableIndices.chasisFrameId,powerSupplyTableIndices.slotID);
		if(deletePowerSupplyTable(&powerSupplyTableIndices) == CLIB_SUCCESS)
		{
			LOG_PRINT(DEBUG,"1U: DELETE SUCCESS");
			if(countToUpdate == I_TRUE)
			{
				LOG_PRINT(DEBUG,"Going to decrement totalNumObfCard in ChasisFrameTableApi[%d]",chasisFrameTableIndices.chasisFrameId);
				chasisFrameTableApi->totalNumObfCard = chasisFrameTableApi->totalNumObfCard - 1;
			}	
		}
		else
		{
			LOG_PRINT(DEBUG,"1U: DELETE FAILED ");
		}
	}
  if(value == THREE)
	{
		countToUpdate = I_FALSE;
	  LOG_PRINT(DEBUG,"1U: UPDATE for chassisFrameId[%d] slotID[%d]",powerSupplyTableIndices.chasisFrameId,powerSupplyTableIndices.slotID);
	  if(getPowerSupplyTable(&powerSupplyTableIndices,&powerSupplyTableApi) == CLIB_SUCCESS)
		{
			LOG_PRINT(DEBUG,"1U: Row present :: Going for Upadate of PhysicalPresenceState");
			if(recAlarmPtr->sysalarmId == INFO_OBF_PRESENT_PM_OAM)
			{
			  //powerSupplyTableApi->powerSupplyStatus = PRESENT;	
			  powerSupplyTableApi->physicalPresenceState = PRESENT;
			}
			else if(recAlarmPtr->sysalarmId == INFO_OBF_ABSENT_PM_OAM)
			{
			  powerSupplyTableApi->powerSupplyStatus = NOT_PRESENT;	
			  powerSupplyTableApi->physicalPresenceState = NOT_PRESENT;
			}
			if(updatePowerSupplyTable(powerSupplyTableApi) == CLIB_SUCCESS)
			{
					LOG_PRINT(LOG_DEBUG,"1U: Update for PowerSupplyTableApi for SUCCESS");
				  if(countToUpdate == I_TRUE)
					{
						LOG_PRINT(DEBUG,"Going to Increment totalNumObfCard in ChasisFrameTableApi[%d]",chasisFrameTableIndices.chasisFrameId);
					}	
			}
			else
			{
				LOG_PRINT(LOG_DEBUG,"1U: UPDATE FAILED chassidId[%d] slotID[%d] in PowerSupplyTableApi ",powerSupplyTableApi->chasisFrameId,powerSupplyTableApi->slotID);
				free(powerSupplyTableApi);
				if(NULL != chasisFrameTableApi)
				{
					free(chasisFrameTableApi);
					chasisFrameTableApi = NULL;
				}
				return;
			}
		}
		else
		{
			LOG_PRINT(DEBUG,"1U: Row not present :: exiting from updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi");
			if(NULL != chasisFrameTableApi)
			{
				free(chasisFrameTableApi);
				chasisFrameTableApi = NULL;
			}
			return;
		}
	}
	else
	{
			LOG_PRINT(DEBUG,"1U: INVALID CASE");
	}
  if(countToUpdate == I_TRUE)
	{
		LOG_PRINT(DEBUG,"1U: Going for update for ChassisId[%d] totalNumObmCard[%d] totalNumObfCard[%d] in ChasisFrameTableApi",chasisFrameTableApi->chasisFrameId,chasisFrameTableApi->totalNumObmCard,chasisFrameTableApi->totalNumObfCard);
		if(updateChasisFrameTable(chasisFrameTableApi) == CLIB_SUCCESS)
		{
				LOG_PRINT(LOG_DEBUG,"1U: Update for ChasisFrameTableApi for row SUCCESS");
		}
		else
		{
				LOG_PRINT(LOG_DEBUG,"1U: Update for ChasisFrameTableApi for row FAILED");
		}

	}
	if(NULL !=chasisFrameTableApi)
	{
		free(chasisFrameTableApi);
		chasisFrameTableApi = NULL;
	}
	if(NULL !=powerSupplyTableApi)
	{
		free(powerSupplyTableApi);
	}
	LOG_PRINT(DEBUG,"1U: Exiting function updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi()");
}
/********************************* Function  Header*****************************
Function Name     : UpdateFanFilterIdTableApi(SysAlarm *recAlarmPtr)
Parameters        : SysAlarm *recAlarmPtr,I_U8 value 
Return type       : I_Void
Purpose           : It makes a update System details after receiving Active Notification from BPM.
Other Note        : Added For 1U CLOUD BSC 
*******************************************************************************/
I_Void UpdateFanFilterIdTableApi(SysAlarm *recAlarmPtr)
{
	LOG_PRINT(DEBUG,"1U: Entering function UpdateFanFilterIdTableApi()");
	FanFilterIdTableIndices fanFilterIdTableIndices;
	FanFilterIdTableApi *fanFilterIdTableApi = NULL;
	fanFilterIdTableIndices.chasisFrameId = recAlarmPtr->key1; 
	fanFilterIdTableIndices.fanFilterId = recAlarmPtr->key2;
	if(getFanFilterIdTable(&fanFilterIdTableIndices,&fanFilterIdTableApi) == CLIB_SUCCESS) 
	{
	  if(recAlarmPtr->sysalarmId == INFO_FAN_FILTER_PRESENT_PM_OAM)
		{
			fanFilterIdTableApi->physicalPresenceState = PRESENT;
			LOG_PRINT(DEBUG,"1U: Updating physicalPresenceState as PRESENT for chassisId[%d] fanFilterId[%d]",fanFilterIdTableIndices.chasisFrameId,fanFilterIdTableIndices.fanFilterId);
		}
		else if(recAlarmPtr->sysalarmId == INFO_FAN_FILTER_ABSENT_PM_OAM)
		{
			fanFilterIdTableApi->physicalPresenceState = NOT_PRESENT;
			LOG_PRINT(DEBUG,"1U: Updating physicalPresenceState as NOT_PRESENT for chassisId[%d] fanFilterId[%d]",fanFilterIdTableIndices.chasisFrameId,fanFilterIdTableIndices.fanFilterId);
		}
		if(updateFanFilterIdTable(fanFilterIdTableApi) == CLIB_SUCCESS)
		{
			LOG_PRINT(LOG_DEBUG,"1U: Update for FanFilterIdTableApi for row SUCCESS");
		}
		else
		{
			LOG_PRINT(LOG_DEBUG,"1U: Update for FanFilterIdTableApi for row FAILED");
		}
	  if(NULL !=fanFilterIdTableApi)
		{
			free(fanFilterIdTableApi);
		}
	}
	else
	{
		LOG_PRINT(DEBUG,"1U: row not present in FanFilterIdTableApi for chassisId[%d] fanFilterId[%d]",fanFilterIdTableIndices.chasisFrameId,fanFilterIdTableIndices.fanFilterId);
	}
	LOG_PRINT(DEBUG,"1U: Exiting function UpdateFanFilterIdTableApi()");
}
 /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
/********************************* Function  Header*****************************
Function Name     : UpdatePowerStatusObmMateCard
Parameters        : SysAlarm *recAlarmPtr,I_U8 value 
Return type       : I_Void
Purpose           : It updates power Status of Mate Obm Card in DB 
Other Note        : Added For 1U CLOUD BSC 
*******************************************************************************/
I_Void UpdatePowerStatusObmMateCard(SysAlarm *recAlarmPtr,I_U8 value)
{
	LOG_PRINT(DEBUG,"1U: Entering function UpdatePowerStatusObmMateCard()");
	ObmCardInfoTableIndices obmCardInfoTableIndices;
	ObmCardInfoTableApi *obmCardInfoTableApi =  NULL;
	obmCardInfoTableIndices.chasisFrameId = recAlarmPtr->key1;
	obmCardInfoTableIndices.slotID = recAlarmPtr->key2;
  if(getObmCardInfoTable(&obmCardInfoTableIndices,&obmCardInfoTableApi) == CLIB_SUCCESS)
	{
	   if(value  == FAIL) 
		 {
		   obmCardInfoTableApi->powerStatus = FAIL;	
       LOG_PRINT(DEBUG,"1U: Updated Power Status of Mate OBM card as FAIL in DB");
		 }
		 else
		 {
		   obmCardInfoTableApi->powerStatus = GOOD;	
       LOG_PRINT(DEBUG,"1U: Updated Power Status of Mate OBM card as GOOD in DB");
		 }
		 if(updateObmCardInfoTable(obmCardInfoTableApi) == CLIB_SUCCESS)
			{
				LOG_PRINT(LOG_DEBUG,"1U: Update for ObmCardInfoTableApi for chassisId[%d] slotId[%d] SUCCESS",obmCardInfoTableApi->chasisFrameId,obmCardInfoTableApi->slotID);
			}
			else
			{
				LOG_PRINT(LOG_DEBUG,"1U: Update FAILED :::: ObmCardInfoTableApi ChassisId[%d] slotId[%d]",obmCardInfoTableApi->chasisFrameId,obmCardInfoTableApi->slotID);
			}
	  free(obmCardInfoTableApi);
	}
	else
	{
			LOG_PRINT(DEBUG,"1U: Get failed for ObmCardInfoTableApi");
	}
	LOG_PRINT(DEBUG,"1U: Exiting function UpdatePowerStatusObmMateCard()");
}
/********************************* Function  Header*****************************
Function Name     : UpdateTemperatureObmCard
Parameters        : SysAlarm *recAlarmPtr,I_U8 MODULE 
Return type       : I_Void
Purpose           : It updates Temperature of Mate Obm Card in DB for different modules
Other Note        : Added For 1U CLOUD BSC 
*******************************************************************************/
I_Void UpdateTemperatureObmCard(SysAlarm *recAlarmPtr,I_U8 module)
{
	LOG_PRINT(DEBUG,"1U: Entering function UpdateTemperatureObmCard()");
	ObmCardInfoTableIndices obmCardInfoTableIndices;
	ObmCardInfoTableApi *obmCardInfoTableApi =  NULL;
	obmCardInfoTableIndices.chasisFrameId = recAlarmPtr->key1;
	obmCardInfoTableIndices.slotID = recAlarmPtr->key2;
  if(getObmCardInfoTable(&obmCardInfoTableIndices,&obmCardInfoTableApi) == CLIB_SUCCESS)
	{
	   if(module == INLET_MODULE) 
		 {
		   obmCardInfoTableApi->powerModuleTemp = recAlarmPtr->key3;	
       LOG_PRINT(DEBUG,"1U: Updated Temperature of powerModuleTemp(INLET) with [%d] degree Celsius",obmCardInfoTableApi->powerModuleTemp);
		 }
		 else if(module == OUTLET_MODULE)
		 {
		   obmCardInfoTableApi->facePlateTemp = recAlarmPtr->key3;	
       LOG_PRINT(DEBUG,"1U: Updated Temperature of facePlateTemp(OUTLET) with [%d] degree Celsius",obmCardInfoTableApi->facePlateTemp);
		 }
		 else if(module == IMX_MODULE)
		 {
		   obmCardInfoTableApi->imxTemp = recAlarmPtr->key3;	
       LOG_PRINT(DEBUG,"1U: Updated Temperature of imxTemp(IMX) with [%d] degree Celsius",obmCardInfoTableApi->imxTemp);
		 }
		 else
		 {
       LOG_PRINT(DEBUG,"1U: INVALID MODULE recvd in ALARM:: returning without DB updation");
			 return;
		 }
		 if(updateObmCardInfoTable(obmCardInfoTableApi) == CLIB_SUCCESS)
			{
				LOG_PRINT(LOG_DEBUG,"1U: Update for ObmCardInfoTableApi for chassisId[%d] slotId[%d] SUCCESS",obmCardInfoTableApi->chasisFrameId,obmCardInfoTableApi->slotID);
			}
			else
			{
				LOG_PRINT(LOG_DEBUG,"1U: Update FAILED :::: ObmCardInfoTableApi ChassisId[%d] slotId[%d]",obmCardInfoTableApi->chasisFrameId,obmCardInfoTableApi->slotID);
			}
	  free(obmCardInfoTableApi);
	}
	else
	{
			LOG_PRINT(DEBUG,"1U: Get failed for ObmCardInfoTableApi");
	}
	LOG_PRINT(DEBUG,"1U: Exiting function UpdateTemperatureObmCard()");
}
/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
/********************************* Function  Header*****************************
Function Name     : updateSystemDetails()
Parameters        : I_Void
Return type       : I_Void
Purpose           : It makes a update System details after receiving Active Notification from BPM.
Other Note        : Added For BSC CS4.0 HA Implementation
*******************************************************************************/
  I_Void updateSystemDetails()
  {
    I_U32 i=0;
    I_U16 totalNumOfCards =0;
    sFanTrayObjInfo fanTrayObjInfo;
    LOG_PRINT(LOG_INFO,"updateSystemDetails: Entering in function ");
    if(gSystemDetails == NULL)
    {
      LOG_PRINT(LOG_CRITICAL,"updateSystemDetails: NO System Details Available.System may not behave properlly");
    }
    else
    {
      LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating SystemType Details");
      updateSystemTypeDetails(gSystemDetails->systemType);

      totalNumOfCards = gSystemDetails->totalNumCards;
      if(  (gSystemDetails->selfInfo.peerCardPresence == I_TRUE) && 
          ((totalNumOfCards - gSystemDetails->numRemoteCards) == 1)  )
        totalNumOfCards++;

      LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating ChasisFrameDetails with TotalNumCard:%d", totalNumOfCards);
      updateChasisFrameDetails(totalNumOfCards, gSystemDetails->numRemoteCards, gSystemDetails->selfInfo.frameID );

      /*Insert Card Details foe EIC-0*/
      LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating Eic Card Detail [%d]",0);
      if( gSystemDetails->numRemoteCards == 0 )
      {
        gSystemDetails->eicInfo[0].frameID = gSystemDetails->selfInfo.frameID;
        gSystemDetails->eicInfo[0].slotID = EIC0_CARD ; 
        gSystemDetails->eicInfo[0].cardOperState = CARDSTATE_ABSENT;

        gSystemDetails->eicInfo[1].frameID = gSystemDetails->selfInfo.frameID;
        gSystemDetails->eicInfo[1].slotID = EIC1_CARD ; 
        gSystemDetails->eicInfo[1].cardOperState = CARDSTATE_ABSENT;
      }
      insertEicCardDetails(gSystemDetails->eicInfo[0]); 

      /*Insert Card Details foe EIC-1*/
      LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating Eic Card Detail [%d]",1);
      if( gSystemDetails->numRemoteCards == 1 )
      {
        gSystemDetails->eicInfo[1].frameID = gSystemDetails->selfInfo.frameID;

        if(gSystemDetails->eicInfo[0].slotID == EIC1_CARD)
          gSystemDetails->eicInfo[1].slotID = EIC0_CARD ; 
        else
          gSystemDetails->eicInfo[1].slotID = EIC1_CARD ; 

        gSystemDetails->eicInfo[1].cardOperState = CARDSTATE_ABSENT;
      }
      insertEicCardDetails(gSystemDetails->eicInfo[1]);

      LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating Self Card Info");
      gSystemDetails->selfInfo.cardOperState = CARDSTATE_ACTIVE;

      if((gSystemDetails->selfInfo.slotID == ICCSELFCARD)||(gSystemDetails->selfInfo.slotID == ICCMATECARD))
      {
        insertIccCardDetails(gSystemDetails->selfInfo);
      }
      else
      {
        LOG_PRINT(LOG_CRITICAL,"updateSystemDetails: Wrong SelfCard Slot Id %d is rcvd from BPM ",gSystemDetails->selfInfo.slotID);
      }  
      /*      if(gCfgAlarmBuf != NULL)
              {
              LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Populating CardStateChange Table");
              populateCardStateChangeTable(gCfgAlarmBuf + sizeof(SysHdr));
              }
       */

      LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating Mate Card Info");
      if((((sSystemCardInfo *)gSystemDetails)->totalNumCards) - (((sSystemCardInfo *)gSystemDetails)->numRemoteCards) == 1)  
      {
        gSystemDetails->mateInfo.frameID = gSystemDetails->selfInfo.frameID;
        if(gSystemDetails->selfInfo.slotID == ICCSELFCARD)
          gSystemDetails->mateInfo.slotID = ICCMATECARD; 
        else
          gSystemDetails->mateInfo.slotID = ICCSELFCARD; 

        if(gSystemDetails->selfInfo.peerCardPresence != I_TRUE)
          gSystemDetails->mateInfo.cardOperState = CARDSTATE_ABSENT;
        else
          gSystemDetails->mateInfo.cardOperState = CARDSTATE_SHUTDOWN;
      }
      insertIccCardDetails(gSystemDetails->mateInfo);

      /*Changes for R2.3.4 Starts*/
      /*Fix for MantisId 12780 starts*/
#if 0
      insertPsuCardDetails(gSystemDetails->psuInfo[0]);
      if(gSystemDetails->psuInfo[0].peerCardPresence != I_TRUE)
      {
        gSystemDetails->psuInfo[1].frameID = gSystemDetails->psuInfo[0].frameID;
        if(gSystemDetails->psuInfo[0].slotID == PSU0_SLOTID)
          gSystemDetails->psuInfo[1].slotID = PSU1_SLOTID;
        else
          gSystemDetails->psuInfo[1].slotID = PSU0_SLOTID;

        gSystemDetails->psuInfo[1].cardOperState = CARDSTATE_ABSENT;
      }
      insertPsuCardDetails(gSystemDetails->psuInfo[1]);
#endif
      for(i=0;i < MAX_PSU ; i++)
      {
        insertPsuCardDetails(gSystemDetails->psuInfo[i]);
      }

      /*Fix for MantisId 12780 ends*/
      for(i = 0; i< MAX_NUM_FAN_TRAY; i++)
      {  
        fanTrayObjInfo = gSystemDetails->fanTrayInfo[i];
        insertFanTrayDetails(fanTrayObjInfo); 
      }
      /*Changes for R2.3.4 Ends*/

      cfgInitEicSwMNodeTable();
      LOG_PRINT(DEBUG,"UPDATING System Details : CfgInitDspSwmNodeTable");
      cfgInitDspSwMNodeTable();

      LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating TrunkPort Details");
      updateTrunkPortDetails(gSystemDetails->portInfo);

      LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating System Clock Details");
      updateSystemClock(gSystemDetails->sysClkInfo);

      //LOG_PRINT(LOG_DEBUG,"updateSystemDetails: Updating DSP Object Details");
      //updateDspObjDetails(gDspInfo);

      //LOG_PRINT(LOG_DEBUG,"[%s]:updSlotIdInClkSrcCfg",__func__);
      //updSlotIdInClkSrcCfg();
    }
    LOG_PRINT(LOG_INFO,"updateSystemDetails: Exiting from function ");
  }


  /********************************* Function  Header********************************
    Function Name:       updateSystemTypeDetails()
Parameters:          I_U8 systemType
Return type:         void
Purpose:             To update the System Type Details in SystemTypeTable
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/

  I_Void updateSystemTypeDetails(I_U8 systemType)
  {
    SystemTypeTableApi systemTypeTable;
    LOG_PRINT(LOG_INFO,"updateSystemTypeDetails:Entering in Function");
    LOG_PRINT(LOG_DEBUG,"updateSystemTypeDetails: SystemType [%d]" , systemType);
    systemTypeTable.systemType = systemType;
    if(insertSystemTypeTable(&systemTypeTable) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"updateSystemTypeDetails: Initialization Failed....SystemType Details can not be updated!!!");
      return;
    }
    LOG_PRINT(LOG_INFO,"updateSystemTypeDetails:Exiting from Function");
  }

  /********************************* Function  Header********************************
    Function Name:       updateChasisFrameTbl()
Parameters:          void 
Return type:         void
Purpose:             To update the Chasis Frame Details in ChasisFrameTable
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/
  I_Void updateChasisFrameTbl()
  {
    OamOilCfgPresentCardInfoResp *oamOilCfgPresentCardInfoRespPtr =NULL;
    oamOilCfgPresentCardInfoRespPtr = (OamOilCfgPresentCardInfoResp *)((I_U8 *)gCfgMsgBuf);

    LOG_PRINT(LOG_INFO,"updateChasisFrameTbl:Entering in Function");

    updateChasisFrameDetails(oamOilCfgPresentCardInfoRespPtr->cardInfo.totalNumCards, oamOilCfgPresentCardInfoRespPtr->cardInfo.numRemoteCards, oamOilCfgPresentCardInfoRespPtr->cardInfo.selfInfo.frameID );

    LOG_PRINT(LOG_INFO,"updateChasisFrameTbl:Exiting from Function");

  }
  /********************************* Function  Header********************************
    Function Name:       updateChasisFrameDetails()
Parameters:          I_U16 totalNumCards, I_U16 numRemoteCards, I_U8 chasisFrameId
Return type:         void
Purpose:             To update the Chasis Frame Details in ChasisFrameTable
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/
  I_Void updateChasisFrameDetails(I_U16 totalNumCards, I_U16 numRemoteCards, I_U8 chasisFrameId)
  {
    ChasisFrameIdTableApi chasisFrameIdTable ;
    LOG_PRINT(LOG_INFO,"updateChasisFrameDetails:Entering in Function");
    LOG_PRINT(LOG_DEBUG,"updateChasisFrameDetails: ChasisFrameId [%d]" , chasisFrameId);
    LOG_PRINT(LOG_DEBUG,"updateChasisFrameDetails: TotalNumCards [%d]" , totalNumCards);
    LOG_PRINT(LOG_DEBUG,"updateChasisFrameDetails: NumRemoteCards [%d]" , numRemoteCards);
    chasisFrameIdTable.chasisFrameId = chasisFrameId;
    chasisFrameIdTable.totalNumCards = totalNumCards;
    chasisFrameIdTable.totalNumRemoteCards = numRemoteCards;
    if(updateChasisFrameIdTable(&chasisFrameIdTable) != CLIB_SUCCESS)
    {
      if(insertChasisFrameIdTable(&chasisFrameIdTable) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"updateChasisFrameDetails: Initialization Failed....ChasisFrame Details can not be updated!!!");
        return;
      }
    }

    LOG_PRINT(LOG_INFO,"updateChasisFrameDetails:Exiting from Function");

  }
  /********************************* Function  Header********************************
    Function Name:       updateSystemClock()
Parameters:          sSysClockInfo sysClkInfo
Return type:         void
Purpose:             To update the System Clock Details in SystemClockInfoTable
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/

  I_Void updateSystemClock(sSysClockInfo sysClkInfo)
  {
    I_U8 slotId;
    I_U8 chasisFrameId;
    SystemClkInfoTableApi systemClockInfoTableApi;
    LOG_PRINT(LOG_INFO,"updateSystemClock: Entering in Function for Refrence:%d",sysClkInfo.clockReference);

    if(sysClkInfo.clockReference == 74)
    {

      LOG_PRINT(LOG_DEBUG,"updateSystemClock: System ClockReference is [%d] REFERENCE_INTERNAL_CLK",sysClkInfo.clockReference);

    }
    else
      LOG_PRINT(LOG_DEBUG,"updateSystemClock: System ClockReference is [%d] REFERENCE_EXTERNAL_CLK",sysClkInfo.clockReference);

    if( !(  (sysClkInfo.clockReference == REFERENCE_INTERNAL_CLK) ||
          (sysClkInfo.clockReference == REFERENCE_EXTERNAL_CLK)  )  )  
    {
      LOG_PRINT(DEBUG,"wrong clk reference:%d received fropm BPM",sysClkInfo.clockReference);
      sysClkInfo.clockReference = REFERENCE_INTERNAL_CLK; 
    }

    if(sysClkInfo.clockReference != REFERENCE_INTERNAL_CLK)
    {
      if ( getChasisSlotIdTrunkTable(sysClkInfo.clockPortId, &chasisFrameId, &slotId ) 
          != CLIB_SUCCESS) 
      {
        LOG_PRINT(LOG_CRITICAL,
            "updateSystemClock: FrameId and SlotId for ClockPort:: %d is not found. Failed" , 
            sysClkInfo.clockPortId);
        return;
      }
      systemClockInfoTableApi.clkReference = sysClkInfo.clockReference ;
      systemClockInfoTableApi.chasisFrameId = chasisFrameId ;
      systemClockInfoTableApi.slotId = slotId ;
      systemClockInfoTableApi.trunkPortId = sysClkInfo.clockPortId ;
    }
    if(sysClkInfo.clockReference == REFERENCE_INTERNAL_CLK)
    {
      LOG_PRINT(LOG_DEBUG,"updateSystemClock: ClockSource is Internal");
      systemClockInfoTableApi.clkReference = sysClkInfo.clockReference ;
      systemClockInfoTableApi.chasisFrameId = 0xFF;
      systemClockInfoTableApi.slotId = 0xFF;
      systemClockInfoTableApi.trunkPortId =  INVALID_TRUNK_ID;
    }
    systemClockInfoTableApi.index = 0 ;
    if(updateSystemClkInfoTable(&systemClockInfoTableApi) != CLIB_SUCCESS)
    {
      if(insertSystemClkInfoTable(&systemClockInfoTableApi) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"updateSystemClock: Initialization Failed....SystemClock Details can not be updated!!!");
        return;
      }
    }
    LOG_PRINT(LOG_INFO,"updateSystemClock: Exiting from Function");
  }

  /*BSC R2.0 Changes Starts*/
  /********************************* Function  Header********************************
    Function Name:       updateDspObjDetails()
Parameters:          sDspObjInfo       dspInfo , I_U32 dspCount
Return type:         void
Purpose:             To update the Dsp Object Details in DspInfoTable
Other Note:          Added for CS4.0 Init Part
   ************************************************************************************/

  I_Void updateDspObjDetails(sDspObjInfo *dspInfo, I_U8 dspCount)
  {
    DspInfoTableApi dspInfoTableApi;
    DspInfoTableApi *outDspData = NULL;
    DspStatusTableApi dspStsTableApi; 
    DspStatusTableApi *outDspStsData = NULL;
    I_U8 tmpCnt=0,j=0;
    I_S32 retVal = 0;
    I_U16 outSize = 0,outStsSize=0;
    I_U32 outRows = 0, outStsRows = 0;
    I_S32 updateBootSts = 0, updatePresenceSts = 0;
    I_U32 dspIp = 0;
    I_U8 dspIpArrAddr[4], isValidDspIp;

    LOG_PRINT(LOG_INFO,"updateDspObjDetails: Entering in Function");

    retVal =getallDspInfoTable(&outDspData, &outRows, &outSize);
    //Update data received from OIL
    if(retVal == CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"updateDspObjDetails : Get All on DspInfo Table is succeded. CFG is updating data from in Table");
      retVal = getallDspStatusTable(&outDspStsData,&outStsRows,&outStsSize);
      if(retVal == CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"updateDspObjDetails :getAllDspStsTable is succeded.");
      }
      else
      {
        LOG_PRINT(LOG_INFO,"updateDspObjDetails :getAllDspStsTable is failed.");
      }
    }
    else
    {
      LOG_PRINT(LOG_INFO,"updateDspObjDetails : Get All on DspInfo Table is failed. CFG is inserting fresh data");

    }

    for(tmpCnt=0;tmpCnt<dspCount ;tmpCnt++)
    {	
      updateBootSts = 0; 
      updatePresenceSts =0;

      bzero(&dspInfoTableApi,sizeof(DspInfoTableApi));
      bzero(&dspStsTableApi,sizeof(DspStatusTableApi));
      dspStsTableApi.chasisFrameId = dspInfo[tmpCnt].frameID ;
      dspStsTableApi.slotId = dspInfo[tmpCnt].slotID ;
      dspStsTableApi.dspId = dspInfo[tmpCnt].dspId; 

      LOG_PRINT(DEBUG,"Val of tmpCnt%d dspId%d", tmpCnt,dspStsTableApi.dspId  );
      PRINT_HEX_DUMP(DEBUG,dspInfo,sizeof(sDspObjInfo));

      dspStsTableApi.oprStatus = DISABLED; 

      if(dspInfo[tmpCnt].isDspPresent == BPM_TRUE)
        dspStsTableApi.physicalPresenceState = PRESENT;
      else
        dspStsTableApi.physicalPresenceState = NOT_PRESENT;

      if(outDspStsData != NULL)
      {
        for(j=0;j<outStsRows ; j++)
        {
          if(dspStsTableApi.dspId  == outDspStsData[j].dspId)
          {
            LOG_PRINT(DEBUG,"Entry found in DbSts table for dspId:%d PreseneceState:%d rcvdPresenceState:%d",
                outDspStsData[j].dspId,outDspStsData[j].physicalPresenceState,
                dspStsTableApi.physicalPresenceState);
            dspStsTableApi.oprStatus = outDspStsData[j].oprStatus;
            if(dspStsTableApi.physicalPresenceState == outDspStsData[j].physicalPresenceState)
              updatePresenceSts = 1; //do not send availSts to Dsph
            break;
          } 
        }  
      }

      dspInfoTableApi.chasisFrameId = dspInfo[tmpCnt].frameID ;
      dspInfoTableApi.slotId = dspInfo[tmpCnt].slotID;
      dspInfoTableApi.dspId = dspInfo[tmpCnt].dspId;
      dspInfoTableApi.dspReset = DSP_NO_RESET; 
      dspInfoTableApi.adminState = UNLOCKED;

      if(dspInfo[tmpCnt].isDspPresent == BPM_TRUE )
      {
        //dspInfoTableApi.dspType = *((I_U32 *)(dspInfo[tmpCnt].dspInfo.bscInfo.swIdInfo));
        dspInfoTableApi.dspType  = dspInfo[tmpCnt].dspInfo.bscInfo.swIdInfo[0];
        dspInfoTableApi.dspType |= (dspInfo[tmpCnt].dspInfo.bscInfo.swIdInfo[1] << 4);
        dspInfoTableApi.dspType |= dspInfo[tmpCnt].dspInfo.bscInfo.swIdInfo[2] ;

        if(dspInfoTableApi.dspType == DSP8122_R2)
        {
          LOG_PRINT(DEBUG,"DspType Received correctly as DSP8122"); 
        } 
        else
        { 
          LOG_PRINT(MAJOR,"DspType NOT Received correctly as DSP8122"); 
        }

        dspInfoTableApi.trauResource = dspInfo[tmpCnt].dspInfo.bscInfo.trauResource_core0 + 
          dspInfo[tmpCnt].dspInfo.bscInfo.trauResource_core1 +
          dspInfo[tmpCnt].dspInfo.bscInfo.trauResource_core2 +
          dspInfo[tmpCnt].dspInfo.bscInfo.trauResource_core3 ;

        dspInfoTableApi.activeTs = dspInfo[tmpCnt].dspInfo.bscInfo.activeChannels;
      } 

      if(outDspData != NULL)
      {
        for(j=0;j<outRows ; j++)
        {
          if(dspInfoTableApi.dspId  == outDspData[j].dspId)
          {
            LOG_PRINT(DEBUG,"Entry found in DbInfo table for dspId:%d AdminState:%d ",
                outDspData[j].dspId,outDspData[j].adminState);
            dspInfoTableApi.adminState = outDspData[j].adminState;
            updateBootSts = 1;
            break;
          } 
        }  
      }
      isValidDspIp == 0;
      for(j=0;j<MAX_CORE_PER_DSP;j++)
      {
        dspIpArrAddr[0] = dspInfo[tmpCnt].dspInfo.bscInfo.dspCoreIpAddr[j].addr1;
        dspIpArrAddr[1] = dspInfo[tmpCnt].dspInfo.bscInfo.dspCoreIpAddr[j].addr2;
        dspIpArrAddr[2] = dspInfo[tmpCnt].dspInfo.bscInfo.dspCoreIpAddr[j].addr3;
        dspIpArrAddr[3] = dspInfo[tmpCnt].dspInfo.bscInfo.dspCoreIpAddr[j].addr4;

        dspIp = (dspIpArrAddr[0] << 24) | (dspIpArrAddr[1] << 16) | (dspIpArrAddr[2] << 8) | dspIpArrAddr[3];

        isValidDspIp = isValidDspIp || dspIp;
        switch(j)
        {
          case 3:
            dspInfoTableApi.CoreId3Ip = dspIp;
            break;
          case 2:
            dspInfoTableApi.CoreId2Ip = dspIp;
            break;
          case 1:
            dspInfoTableApi.CoreId1Ip = dspIp;
            break;
          case 0:
            dspInfoTableApi.CoreId0Ip = dspIp;
            break;
        }
      }
      if((isValidDspIp == 0) &&
          (dspInfoTableApi.dspId > 1) )
      {
        updateBootSts = 0;
      }
      if(updateBootSts == 1)
      {
        if(updateDspInfoTable(&dspInfoTableApi) != CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_CRITICAL,"updateDspObjDetails: DspObj Details updtion failed dspid(%d)!!!",  
              dspInfoTableApi.dspId);
          if(outDspData != NULL)
          {
            free(outDspData);
          } 
          if(outDspStsData != NULL) 
          {
            free(outDspStsData);  
          } 
          return;
        } 
      }
      else if(insertDspInfoTable(&dspInfoTableApi) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"updateDspObjDetails: Initialization Failed....DspObj Details can not be inserted!!!");
        if(outDspData != NULL)
        {
          free(outDspData);
        } 
        if(outDspStsData != NULL) 
        {
          free(outDspStsData);  
        } 
        return;
      }

      LOG_PRINT(DEBUG,"Val of updatePresenceSts:%d ",updatePresenceSts); 

      if((updatePresenceSts == 0) && 
          (gDspBootInfoSent[dspInfoTableApi.dspId] == 0) ) 
      {
        //Send Dsp Available Sts to Dsph
        LOG_PRINT(DEBUG,"sending DSP_AVAIL_STATUS for dspId %d", dspStsTableApi.dspId); 
        sendDsphAvailSts(&dspStsTableApi); 

        //Send Bss Admin State for dspId only if dsp is present 
        if(dspStsTableApi.physicalPresenceState == PRESENT)
        {
          LOG_PRINT(DEBUG,"sending BSS_ADMIN_STATE for dspId %d", dspStsTableApi.dspId); 
          sendDsphBssAdminStateInd(&dspStsTableApi); 
        } 
      }
      if( (dspInfo[tmpCnt].isDspPresent == BPM_TRUE) &&
          (dspInfo[tmpCnt].operationalState == BPM_DSP_ENABLED) &&
          (gDspBootInfoSent[dspInfoTableApi.dspId] == 0) && 
          ((gCfgStandbyToActive == I_FALSE) || (dspInfo[tmpCnt].dspId == 0) || (dspInfo[tmpCnt].dspId == 1)) )
      {
        LOG_PRINT(DEBUG,"sending DSP_BOOT_INFO for dspId %d", dspInfo[tmpCnt].dspId); 
        /* Changes For E1-T1 :Start */
        if(FALSE ==  checkBscTrunkTypeAndDspTrauCoding())
        {
          LOG_PRINT(CRITICAL,"DspTrauCodingFormat is not compatible with BSCTrunkType");
          exit(0); 
        }  
        /* Changes For E1-T1 :End */
        sendDsphBootInfo(&(dspInfo[tmpCnt]));
          LOG_PRINT(DEBUG,"DSP BOOT INFO ALARM received :::::: NOT FORWARDING THIS ALARM");
        //sendDspBootInfoAlarm(&(dspInfo[tmpCnt])); /*Changes done for disabling alarms for dsp*/
				//Changes done for CLOUD BSC Gaurav Sinha 13-may-2016  These alarms not to be forwarded at DSP is not a supervisoned object
        gDspBootInfoSent[dspInfoTableApi.dspId] = 1;
      }
    }//for

    LOG_PRINT(LOG_INFO,"updateDspObjDetails: Exiting from Function");

    if(outDspData != NULL)
    {
      free(outDspData);
    } 
    if(outDspStsData != NULL) 
    {
      free(outDspStsData);  
    } 
  }

  /*BSC R2.0 Changes Ends*/


  /********************************* Function  Header********************************
    Function Name:       sendSwitchConForSelf()
Parameters:          void
Return type:         void
Purpose:             To send switch connect for allocated timeslot on Self Card.
Other Note:          Added for CS4.0
   *************************************************************************************/
  I_Void sendSwitchConForSelf(I_U8 slotId)
  {
    MccLinkResourceTableApi *mccLinkResourceTableApiPtr = NULL;
    MccLinkResourceTableApi *tmpMccLinkResourceTableApiPtr = NULL;
    OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnect;
    I_U32 outRows = 0;
    I_U16 outSize = 0;
    I_U32 count = 0 ;
    LOG_PRINT(LOG_INFO,"sendSwitchConForSelf: Entering from function");
    if(getTrunkNumTsMccLinkTable( SYS_TS_USAGE_MTP2, SYS_TS_ALLOCATED, slotId, &mccLinkResourceTableApiPtr, &outRows, &outSize) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"sendSwitchConForSelf: No Record found for Slot Id [%d], Switching Failed" , slotId);
      return;
    }
    for(count = 0 ; count < outRows ; count++)
    {
      tmpMccLinkResourceTableApiPtr = (MccLinkResourceTableApi *)((I_U8 *)mccLinkResourceTableApiPtr + (count * outSize));
      oamsCfgGrhmSwitchConnect.firstE1Num = tmpMccLinkResourceTableApiPtr->mccTrunkNum;
      oamsCfgGrhmSwitchConnect.firstTimeSlotNum = tmpMccLinkResourceTableApiPtr->mccTrunkTs;
      oamsCfgGrhmSwitchConnect.secondE1Num = tmpMccLinkResourceTableApiPtr->extTrunkNum;
      oamsCfgGrhmSwitchConnect.secondTimeSlotNum = tmpMccLinkResourceTableApiPtr->extTrunkTs;
      LOG_PRINT(LOG_DEBUG,"sendSwitchConForSelf : First E1 : %d, First Ts : %d, SecE1 : %d, SecTs : %d", 
          oamsCfgGrhmSwitchConnect.firstE1Num, oamsCfgGrhmSwitchConnect.firstTimeSlotNum,
          oamsCfgGrhmSwitchConnect.secondE1Num, oamsCfgGrhmSwitchConnect.secondTimeSlotNum
          );
      cfgSendMessage(&oamsCfgGrhmSwitchConnect, sizeof(OamsCfgGrhmSwitchConnect),
          ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0);

    }
    free(mccLinkResourceTableApiPtr);
    LOG_PRINT(LOG_INFO,"sendSwitchConForSelf: Exiting from function");

  }

  /********************************* Function  Header********************************
    Function Name:       sendSwitchConForMate()
Parameters:          void
Return type:         void
Purpose:             To send switch connect for allocated timeslot on Mate Card.
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void sendSwitchConForMate(I_U8 slotId)
  {
    MccLinkResourceTableApi *mccLinkResourcePtr_mtp2 = NULL;
    MccLinkResourceTableApi *tmpMccLinkResourceTableApiPtr = NULL;
    OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnect;
    CfgCfgSwitchInfoMsg *cfgCfgSwitchInfo;
    I_U32 outRows_mtp2 = 0;
    I_U16 outSize_mtp2 = 0;
    I_U32 msgSz = 0;
    I_U32 i = 0 ;
    I_U32 count = 0 ;
    I_S32 res =0 ;

    LOG_PRINT(LOG_INFO,"sendSwitchConForMate: Entering from function");

    res = getTrunkNumTsMccLinkTable( SYS_TS_USAGE_MTP2, SYS_TS_ALLOCATED, slotId,
        &mccLinkResourcePtr_mtp2, &outRows_mtp2, &outSize_mtp2);
    if(CLIB_SUCCESS != res)
    {
      LOG_PRINT(LOG_MAJOR,"sendBpmSwitchInfoForPeerCard: getTrunkNumTsMccLinkTable failed for Mtp2 err:%d ",
          res);
      return; 
    }
    else
    {
      LOG_PRINT(DEBUG,"getTrunkNumTsMccLinkTable ret %d rows for mtp2",outRows_mtp2);
    }

    msgSz = sizeof(CfgCfgSwitchInfoMsg) + sizeof(SwitchingInfo) * (outRows_mtp2 - 1);

    cfgCfgSwitchInfo = (CfgCfgSwitchInfoMsg *)AlocOrdBuf(msgSz);

    if(cfgCfgSwitchInfo == NULL)
    {
      LOG_PRINT(DEBUG,"AlocOrdBuf ret NULL for size:%d", msgSz); 
      free(mccLinkResourcePtr_mtp2); 
      return ; 
    }

    cfgCfgSwitchInfo->count = outRows_mtp2; 

    for(count=0,i= 0 ; i < outRows_mtp2 ; i++)
    {
      tmpMccLinkResourceTableApiPtr = (MccLinkResourceTableApi *)((I_U8 *)mccLinkResourcePtr_mtp2 + (i * outSize_mtp2));
      oamsCfgGrhmSwitchConnect.firstE1Num = tmpMccLinkResourceTableApiPtr->extTrunkNum;
      oamsCfgGrhmSwitchConnect.firstTimeSlotNum = tmpMccLinkResourceTableApiPtr->extTrunkTs;
      oamsCfgGrhmSwitchConnect.secondE1Num = tmpMccLinkResourceTableApiPtr->peerTrunkNum;
      oamsCfgGrhmSwitchConnect.secondTimeSlotNum = tmpMccLinkResourceTableApiPtr->peerTrunkTs;
      LOG_PRINT(LOG_DEBUG,"sendSwitchConForMate :  GrhmSwitchCon: First E1 : %d, First Ts : %d, SecE1 : %d, SecTs : %d", 
          oamsCfgGrhmSwitchConnect.firstE1Num , oamsCfgGrhmSwitchConnect.firstTimeSlotNum,
          oamsCfgGrhmSwitchConnect.secondE1Num,oamsCfgGrhmSwitchConnect.secondTimeSlotNum);
      cfgSendMessage(&oamsCfgGrhmSwitchConnect, sizeof(OamsCfgGrhmSwitchConnect),
          ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0);

      /*Fill Cfg Cfg Connect Info*/
      cfgCfgSwitchInfo->switchingInfo[count].srcStreamId = tmpMccLinkResourceTableApiPtr->mccTrunkNum;
      cfgCfgSwitchInfo->switchingInfo[count].srcTsId = tmpMccLinkResourceTableApiPtr->mccTrunkTs;
      cfgCfgSwitchInfo->switchingInfo[count].dstStreamId = tmpMccLinkResourceTableApiPtr->peerTrunkNum;
      cfgCfgSwitchInfo->switchingInfo[count].dstTsId = tmpMccLinkResourceTableApiPtr->peerTrunkTs;
      cfgCfgSwitchInfo->switchingInfo[count].direction = CFG_SWITCH_BI_DIRECTN;
      cfgCfgSwitchInfo->switchingInfo[count].action = CFG_MAKE_SWITCH;
      count++;

      LOG_PRINT(LOG_INFO,"sendSwitchConForMate: sendSwitchReqToPeerCfg : First E1 : %d, \
          First Ts : %d, SecE1 : %d, SecTs : %d",
          tmpMccLinkResourceTableApiPtr->mccTrunkNum,tmpMccLinkResourceTableApiPtr->mccTrunkTs,
          tmpMccLinkResourceTableApiPtr->peerTrunkNum,tmpMccLinkResourceTableApiPtr->peerTrunkTs);
    }

    free(mccLinkResourcePtr_mtp2);

    cfgSendMessage(cfgCfgSwitchInfo, msgSz,ENT_OAMS_CFG, CFG_PEERCFG_SWITCH_INFO,CFG_SWITCH_AT_INIT);
    DalocOrdBuf(cfgCfgSwitchInfo);

    /*Send Bpm switching information for peer card*/ 
    sendBpmSwitchInfoForPeerCard(slotId);
    LOG_PRINT(LOG_INFO,"sendSwitchConForMate: Exiting from function");
  }
  /********************************* Function  Header********************************
    Function Name:       cardSetOperConStateRespHandler()
Parameters:          void
Return type:         void
Purpose:             To Handle Card State Change Response.
Other Note:          Added for CS4.0
   ************************************************************************************/

  I_Void cardSetOperConStateRespHandler(I_U8 slotId, I_U32 cardState, I_U16 result)
  {
    OamsCfgAfhSysAlarm alarmBuff = {0};
    IccCardInfoTableApi *iccCardDetails = NULL;
    SwMNodeTableIndices sApiSwMNodeTableIndices;
    SwMNodeTableApi *swMNodeTableApiPtr;
    IccCardInfoTableIndices iccCardInfoTableIndices;
    I_U32 outRows;
    I_U16 outSize;
    I_U32 bscId;
    LOG_PRINT(LOG_INFO,"cardSetOperConStateRespHandler: Entering in function");
    I_U8 updateSwMTbl = I_FALSE;

    if(getallIccCardInfoTable(&iccCardDetails, &outRows, &outSize) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"cardSetOperConStateRespHandler: No Entry in Icc Card Info Table. Not sending alarm");
      return;
    }

    iccCardInfoTableIndices.chasisFrameId = iccCardDetails->chasisFrameId; 
    iccCardInfoTableIndices.slotId =  slotId; 
    LOG_PRINT(DEBUG,"cardSetOperConStateRespHandler: for slotid:%d",
        slotId);

    if (getBscId(&bscId) == CLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"getBscId success for BscId:%d",bscId); 
      sApiSwMNodeTableIndices.chasisFrameId = iccCardDetails->chasisFrameId;
      sApiSwMNodeTableIndices.slotId = slotId;
      sApiSwMNodeTableIndices.nodeType = (I_U32)SYS_NODE_TYPE_BSC;
      sApiSwMNodeTableIndices.nodeIdentity = bscId;
      LOG_PRINT(LOG_CRITICAL,"SwmNodeTbl Index frameId:%d slotId:%d nodeType:%d bscId:%d..", 
          sApiSwMNodeTableIndices.chasisFrameId,sApiSwMNodeTableIndices.slotId,
          sApiSwMNodeTableIndices.nodeType, sApiSwMNodeTableIndices.nodeIdentity);

      if(getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableApiPtr) == CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"getSwMNodeTable call is successful swSts:%d..", swMNodeTableApiPtr->swStatus);
        if(swMNodeTableApiPtr->swStatus == SW_ACTIVATION_IN_PROGRESS)
        {
          LOG_PRINT(DEBUG,"SW_ACTIVATION_IN_PROGRESS for slotId:%d",swMNodeTableApiPtr->slotId ); 
          gSwActBuff.frameId = swMNodeTableApiPtr->chasisFrameId; 
          gSwActBuff.slotId = swMNodeTableApiPtr->slotId; 
          gSwActBuff.nodeType = swMNodeTableApiPtr->nodeType; 
          strcpy(gSwActBuff.actVersion,swMNodeTableApiPtr->swVersionNew) ; 
          updateSwMTbl = I_TRUE;
        }
        free(swMNodeTableApiPtr); 
      }
      else
      {
        LOG_PRINT(LOG_CRITICAL,"getSwMNodeTable call is getting failed..");
      }
    }
    else
    {
      LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed..");
    }

    if(result == OPERATION_SUCCESS)
    {

      alarmBuff.sysAlarm.sysalarmId = EVENT_CARDSTATE_CHANGE_SUCCESS;

      if(BPM_CARDSTATE_STANDBY == cardState)
      {
        alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,
            "CardState change to STANDBY req success for SlotId [%d]", slotId);
      }  
      else if(BPM_CARDSTATE_DIAGNOSTIC == cardState)
      {
        alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,
            "CardState change to DIAGNOSTIC req success for SlotId [%d]", slotId);
      }
      else if(cardState == BPM_CARDSTATE_OUT_OF_SERVICE)
      {
        alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,
            "CardState change to OUT_OF_SERVICE req success for SlotId [%d]", slotId);
        if(updateSwMTbl == I_TRUE)
        {  
          gSwActBuff.cardState = BPM_CARDSTATE_OUT_OF_SERVICE;
          if(CARDSTATE_ACTIVE_IN_PROGRESS == gCurrentCardState)
          { 
            LOG_PRINT(LOG_INFO,"Current CardState is AIP so storing the ActReq");
            gSendSwActReq = I_TRUE; 
            LOG_PRINT(DEBUG,"gSendSwActReq flag is set");    
          }
          else if(gSwActReqSent != I_TRUE)
          {
            LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_SW_ACT_REQ to Oil");
            LOG_PRINT(LOG_INFO,"Values: slotId = %d nodeType = %d ACT Ver[0] = %d ACT Ver[1] = %d ACT Ver[2] = %d",
                gSwActBuff.slotId,gSwActBuff.nodeType,gSwActBuff.actVersion[0],
                gSwActBuff.actVersion[1],gSwActBuff.actVersion[2]);
            cfgSendMessage((I_Void *)&gSwActBuff, sizeof(OamsCfgOilSwActReq), ENT_OAM_OIL,OAMS_CFG_OIL_SW_ACT_REQ , 0);
            bzero(&gSwActBuff, sizeof(gSystemDetails));
            gSwActReqSent = I_TRUE; 
          }   
        }
      }				
    }
    else
    {
      alarmBuff.sysAlarm.sysalarmId = EVENT_CARDSTATE_CHANGE_FAILED;
      if(BPM_CARDSTATE_STANDBY == cardState)
      {
        alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,
            "CardState change to STANDBY req failed for SlotId [%d]", slotId);
      }  
      else if(BPM_CARDSTATE_DIAGNOSTIC == cardState)
      {
        alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,
            "CardState change to DIAGNOSTIC req failed for SlotId [%d]", slotId);
      }
      else if(cardState == BPM_CARDSTATE_OUT_OF_SERVICE)
      {
        alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,
            "CardState change to OUT_OF_SERVICE req failed for SlotId [%d]", slotId);
        if(updateSwMTbl == I_TRUE)
        {  
          if (updateSwStatusInSwMNodeTable(sApiSwMNodeTableIndices,SW_ACTIVATION_FAILED) !=CLIB_SUCCESS)
          {
            LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
            gSwActStatus = SW_ACTIVATION_FAILED;
          }
          else
          {
            LOG_PRINT(LOG_DEBUG,"SW_ACT FAILED UPDATION SUCC");				
          }			
        }
      }																												
    }

    alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    alarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
    alarmBuff.sysAlarm.key1 = ((IccCardInfoTableApi *)iccCardDetails)->chasisFrameId;
    alarmBuff.sysAlarm.key2 = slotId ;
    free(iccCardDetails);

    cfgSendMessage(&alarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0); 

    LOG_PRINT(LOG_INFO,"cardSetOperConStateRespHandler: Exiting from function");
  }

  /********************************* Function  Header********************************
    Function Name:       sendNeipReq()
Parameters:          void
Return type:         void
Purpose:             To Send Set Neip Request to OIL.
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void sendNeipReq()
  {
    OamsCfgOilSetNeipAddrReq oamsCfgOilSetNeipAddrReq;
    SetNeIpAddressTableApi *setNeIpAddressTableApiPtr;
    I_U32 outRows;
    I_U16 outSize;
    LOG_PRINT(LOG_INFO,"sendNeipReq: Entering in function");
    if(getallSetNeIpAddressTable(&setNeIpAddressTableApiPtr, &outRows,&outSize) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"sendNeipReq: Get All failed on SetNeIpAddressTable ");
      return;
    }

    memcpy(oamsCfgOilSetNeipAddrReq.neipAddress, setNeIpAddressTableApiPtr->nodeIpAddr, MAX_IP_ADDR_LEN);
    oamsCfgOilSetNeipAddrReq.nodeIpPort = setNeIpAddressTableApiPtr->nodeIpPort;

    cfgSendMessage(&oamsCfgOilSetNeipAddrReq, sizeof(OamsCfgOilSetNeipAddrReq), ENT_OAM_OIL, OAMS_CFG_OIL_NEIP_ADDRESS_REQ, 0); 
    free(setNeIpAddressTableApiPtr);
    LOG_PRINT(LOG_INFO,"sendNeipReq: Exiting from function");

  }
  /********************************* Function  Header********************************
    Function Name:       sendSetOmcipAddressReqToCm()
Parameters:          void
Return type:         void
Purpose:             To Send Set Omcip Request to CM.
Other Note:          Added for CS4.0 HA. 
   ************************************************************************************/

  I_Void sendSetOmcipAddressReqToCm( I_S8 *ipAddr, I_U32 port)
  {

    OamsCfgCmSetIpAddress oamsCfgCmSetIpAddress;
    OamsCfgAfhConModeIndi oamsCfgAfhConModeIndi;
    SetNeIpAddressTableApi *neipRow = NULL;
    I_S8 *config_cp_ip;
    I_U32 count;
    I_U16 size;

    LOG_PRINT(LOG_INFO,"sendSetOmcipAddressReqToCm: Entering in function");
    gCurrentConnectivityMode = ETHERNET_MODE;
    config_cp_ip = getenv("config_CP_IP");
    LOG_PRINT(LOG_INFO,"sendSetOmcipAddressReqToCm: configCP_IP [%s]" , config_cp_ip);
    LOG_PRINT(LOG_INFO,"sendSetOmcipAddressReqToCm: OMC_IP [%s]" , ipAddr);
    LOG_PRINT(LOG_INFO,"sendSetOmcipAddressReqToCm: OMC_PORT [%d]" , port);
    memcpy(oamsCfgCmSetIpAddress.neipAddress, config_cp_ip, MAX_IP_ADDR_LEN);
    oamsCfgCmSetIpAddress.neipPort = CONFIG_CP_PORT;
    memcpy(oamsCfgCmSetIpAddress.omcipAddress, ipAddr, MAX_IP_ADDR_LEN);
    oamsCfgCmSetIpAddress.omcPort = port;

    cfgSendMessage(&oamsCfgCmSetIpAddress, sizeof(OamsCfgCmSetIpAddress), ENT_OAM_CM, OAMS_CFG_CM_SET_IP_ADDRESS_REQ, 0); 
    /*Sending Mode Indication to Afh*/
    if(getallSetNeIpAddressTable(&neipRow, &count, &size) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"sendSetOmcipAddressReqToCm: No Data in Neip Table");
      LOG_PRINT(LOG_INFO,"sendSetOmcipAddressReqToCm: Exiting from function");
      return;
    }
    memcpy(oamsCfgAfhConModeIndi.nodeipAddress, neipRow->nodeIpAddr, MAX_IP_ADDR_LEN);
    memcpy(oamsCfgAfhConModeIndi.omcipAddress, oamsCfgCmSetIpAddress.omcipAddress, MAX_IP_ADDR_LEN);
    oamsCfgAfhConModeIndi.connectivityMode = ETHERNET_MODE;
    LOG_PRINT(LOG_INFO,"sendSetOmcipAddressReqToCm: NodeIpAddress to Afh [%s]", oamsCfgAfhConModeIndi.nodeipAddress);

    cfgSendMessage(&oamsCfgAfhConModeIndi, sizeof(OamsCfgAfhConModeIndi), ENT_OAM_AFH, OAMS_CFG_AFH_CON_MODE_INDICATION, 0); 
    free(neipRow) ;
    LOG_PRINT(LOG_INFO,"sendSetOmcipAddressReqToCm: Exiting from function");

  }

  /********************************* Function  Header********************************
    Function Name:       sendSetOmcipAddressReqToCmInActive()
Parameters:          void
Return type:         void
Purpose:             To Send Set Omcip Request to CM
Other Note:          Added for CS4.0 HA. 
   ************************************************************************************/

  I_Void sendSetOmcipAddressReqToCmInActive()
  {
    SetOmcIpAddressTableApi *setOmcIpAddressTableApiPtr = NULL;
    I_U32 outRows;
    I_U16 outSize;
    LOG_PRINT(LOG_INFO,"sendSetOmcipAddressReqToCmInActive: Entering in function");

    if(getallSetOmcIpAddressTable(&setOmcIpAddressTableApiPtr, &outRows,&outSize) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"sendSetOmcipAddressReqToCmInActive: Get All failed on SetOmcIpAddressTable ");
      return;
    }
    sendSetOmcipAddressReqToCm(setOmcIpAddressTableApiPtr->omcIpAddr, setOmcIpAddressTableApiPtr->omcIpPort);
    free(setOmcIpAddressTableApiPtr);

    LOG_PRINT(LOG_INFO,"sendSetOmcipAddressReqToCmInActive: Exiting from function");

  }
  /********************************* Function  Header********************************
    Function Name:       sendBreakOmcipAddressReqToCm()
Parameters:          void
Return type:         void
Purpose:             To Send  Omcip Request to CM to break the connection
Other Note:          Added for CS4.0 HA. 
   ************************************************************************************/

  I_Void sendBreakOmcipAddressReqToCm()
  {
    LOG_PRINT(LOG_INFO,"sendBreakOmcipAddressReqToCm: Entering in function");

    sendSetOmcipAddressReqToCm(INVALID_IP , INVALID_PORT);

    LOG_PRINT(LOG_INFO,"sendBreakOmcipAddressReqToCmInActive: Exiting from function");

  }

  /********************************* Function  Header********************************
    Function Name:       poplateCardStateChangeTable()
Parameters:          void
Return type:         void
Purpose:             To PopulateCardStateChange Table.
Other Note:          Added for CS4.0 HA. 
   ************************************************************************************/

  I_Void populateCardStateChangeTable(SysAlarm *alarmBuf)
  {
    CardStateChangeTableApi cardStateChangeTableApi;
    IccCardInfoTableIndices iccCardInfoTable;
    IccCardInfoTableApi *iccCardInfoTableApiPtr;
    LOG_PRINT(LOG_INFO,"populateCardStateChangeTable: Entering from function");
    CALLCLEANDBTABLE(CardStateChangeTable);
    iccCardInfoTable.chasisFrameId = alarmBuf->key1;
    iccCardInfoTable.slotId = alarmBuf->key2;
    if(getIccCardInfoTable(&iccCardInfoTable, &iccCardInfoTableApiPtr) == CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"populateCardStateChangeTable: Card is ICC. Updating CardStateChangeTable");

      cardStateChangeTableApi.chasisFrameId = alarmBuf->key1;
      //Mantis #0031749
      /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
      //cardStateChangeTableApi.slotId = alarmBuf->key2;
      cardStateChangeTableApi.slotId = alarmBuf->key2-2;
      if(gCardPlatformType == 1)
      {
        cardStateChangeTableApi.cardType = CARD_TYPE_OBM;
      }
      else
      {
       //cardStateChangeTableApi.cardType = CARD_TYPE_ICC;
       cardStateChangeTableApi.cardType = CARD_TYPE_HOST;
      }
      LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: Insert/Update CardStateChangeTable slotId [%d] cardType [%d] ",cardStateChangeTableApi.slotId,cardStateChangeTableApi.cardType);
      /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
      //Mantis #0031749
      cardStateChangeTableApi.cardOperationalState = alarmBuf->key4;
      if(updateCardStateChangeTable(&cardStateChangeTableApi) != CLIB_SUCCESS)
      {
        if(insertCardStateChangeTable(&cardStateChangeTableApi) != CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_CRITICAL,"populateCardStateChangeTable: Db Operation on CardStateChangeTable failed");
          free(iccCardInfoTableApiPtr);
          return;

        }
      }
    }
    else
    {
      LOG_PRINT(LOG_INFO,"populateCardStateChangeTable: Card is EIC. No updation on CardStateChangeTable is equired");
      return;
    }
    free(iccCardInfoTableApiPtr);
    LOG_PRINT(LOG_INFO,"populateCardStateChangeTable: Exiting from function");

  }

  /********************************* Function  Header********************************
    Function Name:       selfSlotIdReqHandler()
Parameters:          void
Return type:         void
Purpose:             To Handle the request of Slef Slot Id query.
Other Note:          Added for CS4.0 HA. 
   ************************************************************************************/

  I_Void selfSlotIdReqHandler()
  {
#if 0
    OamsCfgRmSlotIdResp oamsCfgRmSlotIdResp;
    LOG_PRINT(LOG_INFO,"selfSlotIdReqHandler: Entering in function");
    oamsCfgRmSlotIdResp.mySlotId = gMySlotId;
    oamsCfgRmSlotIdResp.peerSlotId = gPeerSlotId;
    cfgSendMessage(&oamsCfgRmSlotIdResp , sizeof(OamsCfgRmSlotIdResp) , ENT_OAMS_RM , OAMS_CFG_RM_SLOTID_RESP, 0);
    LOG_PRINT(LOG_INFO,"selfSlotIdReqHandler: Exiting from function");
#endif
  }

  /********************************* Function  Header********************************
    Function Name:       selfSlotIdRespHandler()
Parameters:          void
Return type:         void
Purpose:             To Handle the response of Self Slot Id query.
Other Note:          Added for CS4.0 HA. 
   ************************************************************************************/

  I_Void selfSlotIdRespHandler()
  {
#if 0
    OamsRmCfgSlotIdResp *oamsRmCfgSlotIdResp;
    LOG_PRINT(LOG_INFO,"selfSlotIdRespHandler: Entering in function");
    oamsRmCfgSlotIdResp = (OamsRmCfgSlotIdResp *)((I_U8 *)gCfgMsgBuf);
    gMySlotId = oamsRmCfgSlotIdResp->mySlotId;
    gPeerSlotId = oamsRmCfgSlotIdResp->peerSlotId;
    LOG_PRINT(LOG_INFO,"selfSlotIdRespHandler: gMySlotId [%d] gPeerSlotId [%d] from RM", gMySlotId, gPeerSlotId);
    LOG_PRINT(LOG_INFO,"selfSlotIdReqHandler: Exiting from function");
#endif
  }


  /*Mantix 6673 Fixed Starts- Gaurav Bhatnagar*/
  /********************************* Function  Header********************************
    Function Name:       isE1InFrame()
Parameters:          I_U32 e1Num
Return type:         I_S32
Purpose:             To Check whether E1 is Inframe.
Other Note:          Added for CS4.0
   ************************************************************************************/

  I_S32 isE1Inframe(I_U32 e1Num)
  {
    TrunkTableIndices e1PerTableIndices;
    TrunkTableApi *e1PerTableApiPtr = NULL;
    LOG_PRINT(LOG_INFO,"isE1Inframe: Entering in function");
    e1PerTableIndices.e1Num = e1Num;
    I_S32 retVal;
    if(getTrunkTable(&e1PerTableIndices, &e1PerTableApiPtr) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"isE1Inframe: E1Id not found. getTrunkTable Query failed");
      return CFG_SUCCESS;
    }

    if(e1PerTableApiPtr->e1Category == INTERNAL_E1)
    {
      LOG_PRINT(LOG_INFO,"isE1Inframe: e1Id [%d] is INTERNAL" , e1Num);
      retVal = CFG_SUCCESS;
    }
    else
    {
      LOG_PRINT(LOG_INFO,"isE1Inframe: e1Id [%d] is EXTERNAL" , e1Num);
      retVal = CFG_FAILURE;
    }
    free(e1PerTableApiPtr);
    LOG_PRINT(LOG_INFO,"isE1Inframe: Exiting from function");
    return retVal;

  }
  /*Mantix 6673 Fixed Ends- Gaurav Bhatnagar*/

  /********************************* Function  Header********************************
    Function Name:       initializingCfg()
Parameters:          I_Void
Return type:         I_Void
Purpose:             To Initialize Cfg .
Other Note:          Added for CS4.0
   ************************************************************************************/

  I_Void initializingCfg()
  {
    LOG_PRINT(LOG_DEBUG,"initializingCfg: Entering in Function");
    if(gCfgState == CFG_BPM_INIT)
    {
      LOG_PRINT(LOG_DEBUG,"initializingCfg: CFG is in CFG_BPM_INIT state");
      /* BSC R2 Changes Starts*/
      //sendDsphAvailSts();
      //sendDsphBssAdminStateInd(); 
      //sendDsphBootInfo();
      /*BSC R2.0 Sw Activation changes starts*/
      LOG_PRINT(DEBUG,"Va of gSendSwActReq:%d",gSendSwActReq); 
      if(gSendSwActReq == I_TRUE)
      {
        LOG_PRINT(LOG_INFO,"Sending stored SW_ACT_REQ to Oil as card is now active");
        LOG_PRINT(LOG_INFO,"Values: slotId = %d nodeType = %d ACT Ver[0] = %d ACT Ver[1] = %d ACT Ver[2] = %d",
            gSwActBuff.slotId,gSwActBuff.nodeType,gSwActBuff.actVersion[0],
            gSwActBuff.actVersion[1],gSwActBuff.actVersion[2]);
        cfgSendMessage((I_Void *)&gSwActBuff, sizeof(OamsCfgOilSwActReq), ENT_OAM_OIL,OAMS_CFG_OIL_SW_ACT_REQ , 0);
        bzero(&gSwActBuff, sizeof(gSystemDetails));
        gSendSwActReq = I_FALSE;
      } 
      /*BSC R2.0 Sw Activation changes ends*/

      /* BSC R2 Changes Ends*/
      //Send TrunkPort State Change Request
      /* Changes for R2.4 Start */
      //sendConfigCbsReqForAllServerToCbsIf( OAMS_CFG_CBSIF_CONFIG_CBS );
      sendAddCbServerForAllServersToCbsh();//Rishabh
      sendAddCbCellForAllCellsToCbsh();//Rishabh
      /* Changes for R2.4 End */
      /* Changes for KPI PAHSE-II Start */
      /*Mantis Fix: 15409 start*/ 
      if(gCfgStandbyToActive != I_TRUE)
      { 
        updateRadioNwAvlbltyTblAtSysStartup();
        updateDataAvlbltyTblAtSysStartup();
      }
      /*Mantis Fix: 15409 End*/ 
      /* Changes for  KPI PAHSE-II End  */

      if(gTrunkPortStsReqSent == 0)
      {
        if(sendTrunkStateChangeReq() == CFG_FAILURE)
        {
          LOG_PRINT(LOG_DEBUG,"initializingCfg: No Trunk is in Enable state. Sending ClkSrcConfig");
          if(sendClockSourceConfigReq() == CFG_FAILURE)
          {
            LOG_PRINT(LOG_DEBUG,"initializingCfg: No ClockSource Avaibale.Initialization Process continues");
            if(gCfgStandbyToActive == I_FALSE)
            { 
              cfgInitAfterDbRw();
              addConfiguredBics();
              addConfiguredTrxs();
            } 
            cfgInitSwMNodeTable();
            /*Bsc R2.0 Changes Starts*/
            if((ZERO == gSentAddBicReqAtInitNum) && 
                (FALSE == gMgsOprSts)  )
            {
              /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
              sndSwitchConForBicsAtInit(); 
              if(gCfgStandbyToActive == I_TRUE)
              { 
                sndSwitchConForTrxsAtSwitchOver();
              }
              else
              {
                sendRequestForAvailableReleases(); 
                gCfgState = CFG_BPM_SW_QUERY;
                LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
              }
            }   
            /*Bsc R2.0 Changes Ends*/
#if 0//R2.0 changes	
            gCfgState = CFG_START_TRAU;
            sendTrauStartMsg();
#endif
          }
        }
      }
    }
    LOG_PRINT(LOG_DEBUG,"initializingCfg: Exiting from Function");
  }

  /*BSC CS4.0 : Stack changes Starts*/

  /********************************* Function  Header********************************
    Function Name:       sendSwitchConForMccLinkResource()
Parameters:          void
Return type:         void
Purpose:             To send switch connect for allocated timeslot.
Other Note:          Added for CS4.0
   ************************************************************************************/
  I_Void sendSwitchConForMccLinkResource()
  {
    MccLinkResourceTableApi *mccLinkResourceTableApiPtr = NULL;
    MccLinkResourceTableApi *tmpMccLinkResourceTableApiPtr = NULL;
    OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnect;
    I_U32 outRows;
    I_U16 outSize;
    I_U32 count;

    LOG_PRINT(LOG_INFO,"sendSwitchConForMccLinkResource: Entering from function");
    if(getallMccLinkResourceTable(&mccLinkResourceTableApiPtr , &outRows, &outSize) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"sendSwitchConForMccLinkResource: Get All Failed on MccLinkResource Table");
      return;
    }

    for(count = 0 ; count < outRows ; count++)
    {
      tmpMccLinkResourceTableApiPtr = (MccLinkResourceTableApi *)((I_U8 *)mccLinkResourceTableApiPtr + (count * outSize));
      if(tmpMccLinkResourceTableApiPtr->mccLinkStatus == SYS_TS_ALLOCATED)
      {
        oamsCfgGrhmSwitchConnect.firstE1Num = tmpMccLinkResourceTableApiPtr->extTrunkNum;
        oamsCfgGrhmSwitchConnect.firstTimeSlotNum = tmpMccLinkResourceTableApiPtr->extTrunkTs;
        oamsCfgGrhmSwitchConnect.secondE1Num = tmpMccLinkResourceTableApiPtr->mccTrunkNum;
        oamsCfgGrhmSwitchConnect.secondTimeSlotNum = tmpMccLinkResourceTableApiPtr->mccTrunkTs;
        LOG_PRINT(LOG_INFO,"sendSwitchConForMccLinkResource : First E1 : %d, \
            First Ts : %d, SecE1 : %d, SecTs : %d",
            oamsCfgGrhmSwitchConnect.firstE1Num, oamsCfgGrhmSwitchConnect.firstTimeSlotNum,
            oamsCfgGrhmSwitchConnect.secondE1Num, oamsCfgGrhmSwitchConnect.secondTimeSlotNum);
        cfgSendMessage(&oamsCfgGrhmSwitchConnect, sizeof(OamsCfgGrhmSwitchConnect),
            ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0);
      }
    }
    free(mccLinkResourceTableApiPtr);
    LOG_PRINT(LOG_INFO,"sendSwitchConForMccLinkResource: Exiting from function");

  }
  /*BSC CS4.0 : Stack changes Ends*/

  /********************************* Function  Header********************************
    Function Name:       updateCardStateChange()
Parameters:          void
Return type:         void
Purpose:             To Update CardStateChange Table.
Other Note:          Added for CS4.0 HA. 
   ************************************************************************************/

  I_Void updateCardStateChange(I_U8 frameId, I_U8 slotId, I_U32 operState)
  {
    CardStateChangeTableApi cardStateChangeTableApi;
    LOG_PRINT(LOG_INFO,"updateCardStateChange: Entering from function");
    cardStateChangeTableApi.chasisFrameId = frameId;
    //Mantis #0031749
    /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
    //cardStateChangeTableApi.slotId = slotId;
    cardStateChangeTableApi.slotId = slotId-2;
    //cardStateChangeTableApi.cardType = CARD_TYPE_ICC;
    if(gCardPlatformType == 1)
    {
      cardStateChangeTableApi.cardType = CARD_TYPE_OBM;
    }
    else
    {
     //cardStateChangeTableApi.cardType = CARD_TYPE_ICC;
     cardStateChangeTableApi.cardType = CARD_TYPE_HOST;
    }
    LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: Insert/Update CardStateChangeTable slotId [%d] cardType [%d] ",cardStateChangeTableApi.slotId,cardStateChangeTableApi.cardType);
    /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
    //Mantis #0031749
    cardStateChangeTableApi.cardOperationalState = operState;
    LOG_PRINT(LOG_INFO,"updateCardStateChange: SlotId [%d], OperState [%d]", slotId, operState);
    if(updateCardStateChangeTable(&cardStateChangeTableApi) != CLIB_SUCCESS)
    {
      if(insertCardStateChangeTable(&cardStateChangeTableApi) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"updateCardStateChange: Db Operation on CardStateChangeTable failed");
        return;
      }
    }
    LOG_PRINT(LOG_INFO,"updateCardStateChange: Exiting from function");

  }

  /********************************* Function  Header********************************
    Function Name:       sendBpmIccEicTrunkPortStsReq()
Parameters:           
Return type:         void
Purpose:             Shall send Trunk Port Status Request towards BPM 
Other Note:          Added for CS4.0 HA oart 
   ************************************************************************************/
  I_Void sendBpmIccEicTrunkPortStsReq(I_U8 slotId_i)
  {
    OamsCfgOilTrunkPortStatusReq oamsCfgOilTrunkPortStatusReq;
    EicCardInfoTableApi  *eicCardInfoTable;
    IccCardInfoTableApi  *iccCardInfoTable;
    EicCardInfoTableIndices eicCardInfoTableIndices;
    IccCardInfoTableIndices iccCardInfoTableIndices;
    I_U8 chasisFrameId;
    I_U8 activeSlotId;
    I_S32 dbStatus = -1;

    LOG_PRINT(LOG_INFO,"Framing message Trunk Port Status Request towards BPM");
    if ( ( dbStatus = getActiveIccSlotId( &chasisFrameId, &activeSlotId) != CLIB_SUCCESS ) )
    {
      LOG_PRINT(LOG_MAJOR,"getActiveIccSlotId Db call failed ErrorCause: %d",dbStatus);
      return;
    }

    if( (slotId_i == ICCSELFCARD) || 
        (slotId_i == ICCMATECARD) )
    {
      iccCardInfoTableIndices.chasisFrameId = chasisFrameId;
      iccCardInfoTableIndices.slotId = activeSlotId;
      if(getIccCardInfoTable(&iccCardInfoTableIndices,&iccCardInfoTable) == CLIB_SUCCESS)
      {
        if(iccCardInfoTable->physicalPresenceState == PRESENT) 
        {
          oamsCfgOilTrunkPortStatusReq.frameId = chasisFrameId;
          oamsCfgOilTrunkPortStatusReq.slotId = activeSlotId; 
          oamsCfgOilTrunkPortStatusReq.cardType = BPM_CARD_ICC; 
          cfgSendMessage(&oamsCfgOilTrunkPortStatusReq, 
              sizeof(OamsCfgOilTrunkPortStatusReq), ENT_OAM_OIL, OAMS_CFG_OIL_TRUNK_PORT_STATUS_REQ, 0);
          gTrunkPortStsReqSent += 1;
        } 
        free(iccCardInfoTable); 
      }
    }
    else
    { 
      eicCardInfoTableIndices.chasisFrameId = chasisFrameId;
      eicCardInfoTableIndices.slotId = slotId_i;
      if(getEicCardInfoTable(&eicCardInfoTableIndices,&eicCardInfoTable) == CLIB_SUCCESS)
      {
        if(eicCardInfoTable->physicalPresenceState == PRESENT) 
        {
          oamsCfgOilTrunkPortStatusReq.frameId = chasisFrameId;
          oamsCfgOilTrunkPortStatusReq.slotId = slotId_i;
          oamsCfgOilTrunkPortStatusReq.cardType = BPM_CARD_EIC; 
          cfgSendMessage(&oamsCfgOilTrunkPortStatusReq, 
              sizeof(OamsCfgOilTrunkPortStatusReq), ENT_OAM_OIL, OAMS_CFG_OIL_TRUNK_PORT_STATUS_REQ, 0);
          gTrunkPortStsReqSent += 1;
        } 
        free(eicCardInfoTable); 
      }
    }
  }





  /********************************* Function  Header********************************
    Function Name:       chkNupdateMccLinkResourceTable()
Parameters:          void 
Return type:         void
Purpose:             Shall check for row with FREE status and Valid E1 & Timeslot from DB for MccLinkResourceTable and update  this E1 & Timeslot as INVALID. 
Other Note:          Added for CS4.0 for Mantis 7509 
   ************************************************************************************/

  I_Void chkNupdateMccLinkResourceTable()
  {
    MccLinkResourceTableApi *mccLinkResourcePtr = NULL;
    MccLinkResourceTableApi *tempMccTableApiPtr = NULL;
    I_U32 noOfMccCount = 0;
    I_U16 mccSize = 0;
    I_U32 mccRecords = 0;


    /*  Find row in MccLinkResourceTable with free Status with Valid E1 & Timeslot */
    if ( getallMccLinkResourceTable( &mccLinkResourcePtr, &noOfMccCount, &mccSize) == CLIB_SUCCESS)
    {
      for ( mccRecords =0; mccRecords < noOfMccCount; mccRecords++ )
      {
        tempMccTableApiPtr = (MccLinkResourceTableApi*)((I_U8 *)mccLinkResourcePtr + (mccRecords *mccSize));


        if ((tempMccTableApiPtr->mccLinkStatus == SYS_TS_FREE) && (tempMccTableApiPtr->extTrunkNum != INVALID_E1 || tempMccTableApiPtr->extTrunkTs != INVALID_TS))
        {
          /* Update extTrunkNum & extTrunkTs as INVALID in DB */
          LOG_PRINT(LOG_MAJOR, "Invalid entry found with exTrunkNum: %d & extTrunkTs: %d in MccLinkResourceTable",tempMccTableApiPtr->extTrunkNum,tempMccTableApiPtr->extTrunkTs );

          tempMccTableApiPtr->extTrunkNum = INVALID_E1;
          tempMccTableApiPtr->extTrunkTs  = INVALID_TS;
          if(updateMccLinkResourceTable(tempMccTableApiPtr) != CLIB_SUCCESS)
            LOG_PRINT(LOG_MAJOR, "DB updation failed for Function: %s Line:%d",__FUNCTION__,__LINE__);

        } 
      }
      free(mccLinkResourcePtr);
    }
  }

  /*BSC CS4.0 HA changes Ends*/

  /*BSC R2.0 Changes Starts*/

  /********************************* Function  Header********************************
    Function Name:       sendDsphAvailSts
Parameters:           
Return type:         void
Purpose:             To send inforamation to dsph about physically present Dsps.
Other Note:          Added for R2.0 
   ************************************************************************************/

  I_Void sendDsphAvailSts(DspStatusTableApi *dspStsPtr)
  {
    OamsCfgDsphDspAvailStatus sndMsgBuff;
    sndMsgBuff.frameId = dspStsPtr->chasisFrameId;
    sndMsgBuff.slotId = dspStsPtr->slotId;
    sndMsgBuff.dspId = dspStsPtr->dspId;
    sndMsgBuff.physicalPresenceState =  dspStsPtr->physicalPresenceState;

    cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgDsphDspAvailStatus),
        ENT_OAMS_DSPH, OAMS_CFG_DSPH_DSP_AVAIL_STATUS, 0);
  }//sendDsphAvailSts


  /********************************* Function  Header********************************
    Function Name:       sendDsphBootInfo()
Parameters:           
Return type:         void
Purpose:             To send bootinfo of dsp to dsph which has come up at startup.
Other Note:          Added for R2.0 
   ************************************************************************************/

  I_Void sendDsphBootInfo(sDspObjInfo *dspInfoPtr)
  {
    I_U16 j=0; 
    if((dspInfoPtr->slotID==ICCSELFCARD)|| (dspInfoPtr->slotID==ICCMATECARD))/*Changes for R2.8*/
    { 
      OamsCfgDsphDspBootInfo sndMsgBuff;
      sndMsgBuff.frameId = dspInfoPtr->frameID;
      sndMsgBuff.slotId  = dspInfoPtr->slotID;
      sndMsgBuff.dspId   = dspInfoPtr->dspId;
      sndMsgBuff.dspBootInfo = dspInfoPtr->dspInfo;
      LOG_PRINT(DEBUG,"sending  OAMS_CFG_DSPH_DSP_BOOT_INFO msg for SlotId %d ,dspId %d",sndMsgBuff.slotId,
          sndMsgBuff.dspId);
      cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgDsphDspBootInfo),
          ENT_OAMS_DSPH, OAMS_CFG_DSPH_DSP_BOOT_INFO, 0);
    }
    else
    {
      for(j=0;j<MAX_CORE_PER_DSP;j++)  
      {/* Added Check for R2.8 changes*/

        LOG_PRINT(MAJOR,"\n Ip for dspId %d Core %d  addr1 :[%x],addr2:[%x], addr3 [%x]:, addr4:[%x] \n", 
            dspInfoPtr->dspId,j,dspInfoPtr->dspInfo.bscInfo.dspCoreIpAddr[j].addr1,dspInfoPtr->dspInfo.bscInfo.dspCoreIpAddr[j].addr2,dspInfoPtr->dspInfo.bscInfo.dspCoreIpAddr[j].addr3,dspInfoPtr->dspInfo.bscInfo.dspCoreIpAddr[j].addr4);

        if((dspInfoPtr->dspInfo.bscInfo.dspCoreIpAddr[j].addr1==ZERO)&&(dspInfoPtr->dspInfo.bscInfo.dspCoreIpAddr[j].addr2==ZERO)&&(dspInfoPtr->dspInfo.bscInfo.dspCoreIpAddr[j].addr3==ZERO)&&(dspInfoPtr->dspInfo.bscInfo.dspCoreIpAddr[j].addr4==ZERO))
        { 
          LOG_PRINT(MAJOR,"core IP is zero ,Hence Not Sending OAMS_CFG_DSPH_RTP_DSP_BOOT_INFO  msg for SlotId %d ,dspId %d core Id %d",
              dspInfoPtr->slotID,dspInfoPtr->dspId,j);
          return; 
        } 
      }  
      OamsCfgDsphRtpDspBootInfo sndMsgBuff;
      sndMsgBuff.frameId = dspInfoPtr->frameID;
      sndMsgBuff.slotId  = dspInfoPtr->slotID;
      sndMsgBuff.dspId   = dspInfoPtr->dspId;
      sndMsgBuff.dspBootInfo = dspInfoPtr->dspInfo;
      LOG_PRINT(DEBUG,"sending OAMS_CFG_DSPH_RTP_DSP_BOOT_INFO  msg for SlotId %d ,dspId %d",
          sndMsgBuff.slotId,sndMsgBuff.dspId);
      cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgDsphRtpDspBootInfo),
          ENT_OAMS_DSPH,OAMS_CFG_DSPH_RTP_DSP_BOOT_INFO, 0);
    }  
  }//sendDsphBootInfo

  /********************************* Function  Header********************************
    Function Name:       sendDsphBssAdminStateInd()
Parameters:          DspStatusTableApi *dspStsPtr 
Return type:         void
Purpose:             To inform adminState of BSS to dsph.
Other Note:          Added for R2.0 
   ************************************************************************************/

  I_Void sendDsphBssAdminStateInd(DspStatusTableApi *dspStsPtr)
  {
    OamsCfgDsphBssAdminStateInd sndMsgBuff;
    I_U32 adminState;
    if(getBssAdminState(&adminState) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"getBssAdminState DB call is geting failed..");
      return;
    }
    if((adminState == UNLOCKED) && (gBssState != lockInProgress))
    {
      sndMsgBuff.frameId = dspStsPtr->chasisFrameId;
      sndMsgBuff.slotId = dspStsPtr->slotId;
      sndMsgBuff.dspId = dspStsPtr->dspId;
      sndMsgBuff.bssAdminState = UNLOCKED;
      cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgDsphBssAdminStateInd),
          ENT_OAMS_DSPH, OAMS_CFG_DSPH_BSS_ADMINSTATE_IND, 0);
      LOG_PRINT(DEBUG,"BSS_ADMIN_STATE sent for dspId",dspStsPtr->dspId);
    }
  }//sendDsphBssAdminStateInd

  /********************************* Function  Header********************************
    Function Name:       updateDspInfo()
Parameters:          
Return type:         void
Purpose:             To update DspInfo 
Other Note:          Added for R2.0 
   ************************************************************************************/

  I_Void updateDspInfo()
  {
    OamOilCfgPresentCardInfoResp *oamOilCfgPresentCardInfoRespPtr = NULL;

    LOG_PRINT(LOG_INFO,"updateDspInfo: Entering from Function");
    oamOilCfgPresentCardInfoRespPtr = (OamOilCfgPresentCardInfoResp *)((I_U8 *)gCfgMsgBuf);
    updateDspObjDetails(oamOilCfgPresentCardInfoRespPtr->cardInfo.dspInfo,MAX_DSP);
    LOG_PRINT(LOG_INFO,"updateDspInfo: Exiting from Function");
  }

  /********************************* Function  Header********************************
    Function Name:       swOfferAckNackHandler()
Parameters:          
Return type:         void
Purpose:             To  handle SW_OFFER RESP given by BPM. 
Other Note:          Added for R2.0 
   ************************************************************************************/
  I_Void swOfferAckNackHandler()
  {
    OamOilCfgSwUpgradeOfferResult *oamOilCfgSwUpgradeOfferResult; 
    oamOilCfgSwUpgradeOfferResult = (OamOilCfgSwUpgradeOfferResult *)gCfgMsgBuf;
    SwMOfferTableIndices swMOfferTableIndex;
    SwMNodeTableIndices swMNodeTableIndex;
    OamsCfgAfhSysAlarm sysAlarmBuff = {0};
    I_U8 string[MAX_STRING_LENGTH];
    I_U32 dspId[MAX_DSP] ;
    I_U8 noOfDsp = ZERO;
    I_U32 index = ZERO;
    I_U8 noOfEic = ZERO;
    I_U32 eicId[MAX_EIC] ;
    I_U32 bscId = ZERO;

    swMOfferTableIndex.nodeType = oamOilCfgSwUpgradeOfferResult->nodeType;
    swMOfferTableIndex.chasisFrameId = oamOilCfgSwUpgradeOfferResult->frameId;
    swMOfferTableIndex.slotId = oamOilCfgSwUpgradeOfferResult->slotId;
    strcpy(swMOfferTableIndex.upgradeVersion,oamOilCfgSwUpgradeOfferResult->upgradeVersion);

    if (oamOilCfgSwUpgradeOfferResult->upgradeOfferResult != OPERATION_IN_PROGRESS)
    {
      /*Delete record from SwMOffer Table */
      if (deleteSwMOfferTable(&swMOfferTableIndex) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"deleteSwMOfferTable DB call is getting failed");
        return;
      }
      else
        LOG_PRINT(LOG_INFO,"deleteSwMOfferTable Success");

      LOG_PRINT(LOG_INFO,"Sending failure ALARM: INFO_BPM_SW_DWNLD_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_DWNLD_FAIL; 
      /* CS4.0 changes start */
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; 
      sysAlarmBuff.sysAlarm.key1 = oamOilCfgSwUpgradeOfferResult->frameId; 
      sysAlarmBuff.sysAlarm.key2 = oamOilCfgSwUpgradeOfferResult->slotId; 
      sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR ; 
      sysAlarmBuff.sysAlarm.alarmReason = oamOilCfgSwUpgradeOfferResult->upgradeOfferResult;
      getStringForSwOfferErrorCause(oamOilCfgSwUpgradeOfferResult->upgradeOfferResult,
          oamOilCfgSwUpgradeOfferResult->upgradeVersion,oamOilCfgSwUpgradeOfferResult->nodeType,
          string,oamOilCfgSwUpgradeOfferResult->frameId,oamOilCfgSwUpgradeOfferResult->slotId);
      /* CS4.0 changes End */
      sysAlarmBuff.sysAlarm.infoStrLen = 
        sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
      /*Mantis Fix: 11303 Starts*/
      FillObjTypeFromNodeType(oamOilCfgSwUpgradeOfferResult->nodeType,sysAlarmBuff.sysAlarm.info3);
      /*Mantis Fix: 11303 Ends*/

      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
          ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    }
    else
    {
      LOG_PRINT(DEBUG,"SW_UPGRADE - OPERATION_IN_PROGRESS...");
    }

    if (oamOilCfgSwUpgradeOfferResult->nodeType == SYS_NODE_TYPE_DSP)
    { 
      if (getDspIdFromSwMNodeTable(dspId, &noOfDsp) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"getDspIdFromSwMNodeTable call is getting failed..");
        return;
      }
      if (oamOilCfgSwUpgradeOfferResult->slotId == 3 || oamOilCfgSwUpgradeOfferResult->slotId == 4)
      { 
        for( index=0; index<noOfDsp; index++ )
        {
          /*Update the upgraded version recieved as downloaded version 
           * in SwMNode Table for all the Dsp's*/
          swMNodeTableIndex.nodeType = oamOilCfgSwUpgradeOfferResult->nodeType;
          swMNodeTableIndex.nodeIdentity = dspId[index];
          swMNodeTableIndex.chasisFrameId = oamOilCfgSwUpgradeOfferResult->frameId;
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

          if (oamOilCfgSwUpgradeOfferResult->upgradeOfferResult != OPERATION_IN_PROGRESS)
          {
            if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                  SW_DOWNLOAD_FAILED) !=CLIB_SUCCESS)  
            {
              LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
            }
          }
          else
          {  
            if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                  SW_DOWNLOAD_IN_PROGRESS) !=CLIB_SUCCESS)  
            {
              LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
            }
          }
        }
      }//icccard
      else if (oamOilCfgSwUpgradeOfferResult->slotId == 5 || oamOilCfgSwUpgradeOfferResult->slotId == 6)
      { 
        for( index=0; index<MAX_DSP; index++ )
        {
          /*Update the upgraded version recieved as downloaded version 
           * in SwMNode Table for all the Dsp's*/
          swMNodeTableIndex.nodeType = oamOilCfgSwUpgradeOfferResult->nodeType;
          swMNodeTableIndex.nodeIdentity = dspId[index];
          swMNodeTableIndex.chasisFrameId = oamOilCfgSwUpgradeOfferResult->frameId;
          //   swMNodeTableIndex.slotId = swOfferRespPtr->slotId;

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

          if (oamOilCfgSwUpgradeOfferResult->upgradeOfferResult != OPERATION_IN_PROGRESS)
          {
            if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                  SW_DOWNLOAD_FAILED) !=CLIB_SUCCESS)  
            {
              LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
            }
          }
          else
          {  
            if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                  SW_DOWNLOAD_IN_PROGRESS) !=CLIB_SUCCESS)  
            {
              LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
            }
          }
        }//for
      }//eic - card
    }//NODE_TYPE_DSP
#if 0 
    if (oamOilCfgSwUpgradeOfferResult->nodeType == SYS_NODE_TYPE_DSP)
    { 
      if (getDspIdFromSwMNodeTable(dspId, &noOfDsp) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"getDspIdFromSwMNodeTable call is getting failed..");
        return;
      }
      for( index=0; index<noOfDsp; index++ )
      {
        /*Update the upgraded version recieved as downloaded version 
         * in SwMNode Table for all the Dsp's*/
        swMNodeTableIndex.nodeType = oamOilCfgSwUpgradeOfferResult->nodeType;
        swMNodeTableIndex.nodeIdentity = dspId[index];
        swMNodeTableIndex.chasisFrameId = oamOilCfgSwUpgradeOfferResult->frameId;
        //   swMNodeTableIndex.slotId = swOfferRespPtr->slotId;

        if(dspId[index] == 0)
        {
          swMNodeTableIndex.slotId = 3;
        }			 
        if(dspId[index] == 1)
        {
          swMNodeTableIndex.slotId = 4;
        }			 
        if((dspId[index] == 2) || (dspId[index] == 3))
        {
          swMNodeTableIndex.slotId = 5;
        }			 
        if((dspId[index] == 4) || (dspId[index] == 5))
        {
          swMNodeTableIndex.slotId = 6;
        }			 

        if (oamOilCfgSwUpgradeOfferResult->upgradeOfferResult != OPERATION_IN_PROGRESS)
        {
          if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                SW_DOWNLOAD_FAILED) !=CLIB_SUCCESS)  
          {
            LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
          }
        }
        else
        {  
          if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                SW_DOWNLOAD_IN_PROGRESS) !=CLIB_SUCCESS)  
          {
            LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
          }
        }
      }//for
    }//NODE_TYPE_DSP
#endif 
    if (oamOilCfgSwUpgradeOfferResult->nodeType == SYS_NODE_TYPE_EIC)
    {
      if (getEicIdFromSwMNodeTable(eicId, &noOfEic) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"getEicIdFromSwMNodeTable call is getting failed..");
        return;
      }
      for( index=0; index<noOfEic; index++ )
      {
        /*Update the upgraded version recieved as downloaded version 
         * in SwMNode Table for both the EIC's*/
        swMNodeTableIndex.nodeType = oamOilCfgSwUpgradeOfferResult->nodeType;
        swMNodeTableIndex.nodeIdentity = eicId[index];
        swMNodeTableIndex.chasisFrameId = oamOilCfgSwUpgradeOfferResult->frameId;
        swMNodeTableIndex.slotId = eicId[index];

        if (oamOilCfgSwUpgradeOfferResult->upgradeOfferResult != OPERATION_IN_PROGRESS)
        {
          if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                SW_DOWNLOAD_FAILED) !=CLIB_SUCCESS)  
          {
            LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
          }
        }
        else
        {  
          if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                SW_DOWNLOAD_IN_PROGRESS) !=CLIB_SUCCESS)  
          {
            LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
          }
        }
      }//for
    }//NODE_TYPE_EIC
    if (oamOilCfgSwUpgradeOfferResult->nodeType == SYS_NODE_TYPE_BSC)
    {
      /* Retrieve bscId from BSS Table */
      if (getBscId(&bscId) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed..");
        return;
      }
      swMNodeTableIndex.nodeType = oamOilCfgSwUpgradeOfferResult->nodeType;
      swMNodeTableIndex.nodeIdentity = bscId;
      swMNodeTableIndex.chasisFrameId = oamOilCfgSwUpgradeOfferResult->frameId;
      swMNodeTableIndex.slotId = oamOilCfgSwUpgradeOfferResult->slotId;
      if (oamOilCfgSwUpgradeOfferResult->upgradeOfferResult != OPERATION_IN_PROGRESS)
      {
        if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
              SW_DOWNLOAD_FAILED) !=CLIB_SUCCESS)  
        {
          LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
        }
      }
      else
      {  
        if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
              SW_DOWNLOAD_IN_PROGRESS) !=CLIB_SUCCESS)  
        {
          LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
        }
      }
    }
  }

  /********************************* Function  Header********************************
    Function Name:       trunkPortStatusRespHandler()
Parameters:          
Return type:         void
Purpose:             To update trunkPortStatus on receiving TrunkPortStatus Resp. 
Other Note:          Added for R2.0 
   ************************************************************************************/
  I_Void  trunkPortStatusRespHandler()
  {
    OamOilCfgTrunkPortStatusResp * oamOilCfgTrunkPortStatusResp;
    IccPortStatus * iccPortSts ;
    IccPortStatus * tmpPortSts ;
    TrunkPortStatusTableApi *outData;
    I_U32 maxCount,i;
    TrunkPortStatusTableIndices trunkPortStsTblIndx;
    oamOilCfgTrunkPortStatusResp = (OamOilCfgTrunkPortStatusResp *)gCfgMsgBuf;
    iccPortSts = (IccPortStatus *)(oamOilCfgTrunkPortStatusResp->portStatus);
    trunkPortStsTblIndx.chasisFrameId = oamOilCfgTrunkPortStatusResp->frameId;
    trunkPortStsTblIndx.slotId = oamOilCfgTrunkPortStatusResp->slotId;
    if(oamOilCfgTrunkPortStatusResp->result != OPERATION_SUCCESS)
    {
      LOG_PRINT(DEBUG,"OPERATION_NOT_SUCCESS received in TrunkPortStatusResp");
      return; 
    }
    if(  (oamOilCfgTrunkPortStatusResp->slotId == ICCSELFCARD) || 
        (oamOilCfgTrunkPortStatusResp->slotId == ICCMATECARD) )
    {
      maxCount = MAX_PORT_ICC;
      LOG_PRINT(DEBUG,"TrunkState Response Rcvd for ICC card slot:%d",oamOilCfgTrunkPortStatusResp->slotId );  
    }
    else
    {
      maxCount = MAX_PORT_EIC;
      LOG_PRINT(DEBUG,"TrunkState Response Rcvd for EIC card slot:%d",oamOilCfgTrunkPortStatusResp->slotId );  
    }

    for(i=0;i<maxCount;i++)
    {
      tmpPortSts = (IccPortStatus *)((I_U8 *)iccPortSts + (i * sizeof(IccPortStatus) ) );
      trunkPortStsTblIndx.trunkPortId = tmpPortSts->portID;
      if(getTrunkPortStatusTable(&trunkPortStsTblIndx,&outData) != CLIB_SUCCESS)
      {
        LOG_PRINT(DEBUG,"getTrunkPortStatusTable failed for frameId:%d,slotId:%d,portId:%d",
            trunkPortStsTblIndx.chasisFrameId,trunkPortStsTblIndx.slotId,trunkPortStsTblIndx.trunkPortId );  
        continue; 
      }
      LOG_PRINT(DEBUG,"Val of portId:%d,PresentState:%d,isPortUp:%d,oprSts:%d",
          tmpPortSts->portID,outData->physicalPresenceState,
          tmpPortSts->isPortUp, outData->oprStatus);
      if(outData->physicalPresenceState == PRESENT)
      {
        if( (tmpPortSts->isPortUp == BPM_TRUE )  &&
            (outData->oprStatus != ENABLED)  && 
            (gE1Data[outData->trunkPortId].LOS_Active != TRUE)   ) 
        {
          LOG_PRINT(DEBUG,"going to update oprState as enabled for port:%d",outData->trunkPortId); 
          outData->oprStatus = ENABLED;
          if(updateTrunkPortStatusTable(outData) != CLIB_SUCCESS)
          {
            LOG_PRINT(DEBUG,"updateTrunkPortStatusTable failed "); 
          }  
        }
        /* Mantis 27947 , 28158*/
        else if (outData->oprStatus != ENABLED)
        {
          gE1Data[outData->trunkPortId].LOS_Active = TRUE;  
          if(tmpPortSts->isLIULossOfSignal == BPM_TRUE) 
            gE1Data[outData->trunkPortId].LOS_Signal = TRUE;

          if(tmpPortSts->isRLossOfSignal == BPM_TRUE) 
            gE1Data[outData->trunkPortId].LOS_Signal_detect = TRUE; 

          if(tmpPortSts->isRLossOfFrame == BPM_TRUE) 
            gE1Data[outData->trunkPortId].LOS_Frame = TRUE;
        }
      }
      else
      {
        LOG_PRINT(DEBUG,"TrunkPort:%d Not present physically", trunkPortStsTblIndx.trunkPortId);
      }
      free(outData);
    }
  }

#if 0
  /********************************* Function  Header********************************
    Function Name:       isClkConfiguredOnSlotId()
Parameters:          I_U8 slotId;
Return type:         I_S32
Purpose:             To find whether clock is configured on given slot 
Other Note:          Added for R2.0 
   ************************************************************************************/
  I_S32 isClkConfiguredOnSlotId(I_U8 slotId) 
  {
    ClkSourceConfigStatusTableApi *clkSourceConfigStsTable ;
    ClkSourceConfigStatusTableApi *tmpPtr;
    I_U32 outRow = 0;
    I_U16 outSize = 0;
    I_U8 i=0;

    if(getallClkSourceConfigStatusTable(&clkSourceConfigStsTable , &outRow, &outSize) !=CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"isClkConfiguredOnSlotId : No ClockSource configured");
    }
    else
    {
      for(i=0;i<outRow;i++)
      {
        tmpPtr = (ClkSourceConfigStatusTableApi *)((I_U8 *)clkSourceConfigStsTable + i* outSize);
        if(slotId == tmpPtr->slotId)
        {
          LOG_PRINT(DEBUG,"ClockSource is configured for slotid:%d", slotId);
          return TRUE;
        } 
      }  
    }
    LOG_PRINT(DEBUG,"No Clock Source is configured on sloId:%d", slotId);
    return FALSE;
  }
#endif

  /******************************* Function  Header*****************************
    Function Name : markEicCardDisable()
Parameters    : I_U8 frameId, I_U8 slotId 
Return type   : I_S32 
Purpose       : Mark EicCard NOT_PRESENT in EicCardInfoTable if the PRESENT_CARD_INFO_RESP 
does not contain those chasisFrameId and slotId                
Other Note    : Added For BSC R2.0
   *****************************************************************************/
  I_S32 markEicCardDisable(I_U8 frameId, I_U8 slotId)
  {
    EicCardInfoTableIndices eicCardIndex;
    EicCardInfoTableApi *outData;

    LOG_PRINT(DEBUG,"markEicCardDisable: Entering In func");
    eicCardIndex.chasisFrameId = frameId;
    eicCardIndex.slotId = slotId;


    if( getEicCardInfoTable(&eicCardIndex,&outData) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getEicCardInfoTable failed for frameid(%d) slotid(%d)",
          eicCardIndex.chasisFrameId, eicCardIndex.slotId );
      return CFG_FAILURE;
    } 

    //outData->physicalPresenceState = NOT_PRESENT;
    outData->cardOperationalState = BPM_EIC_DISABLE;

    if(updateEicCardInfoTable(outData) != CLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"updateEicCardInfoTable failed for frameid(%d) slotid(%d)",
          eicCardIndex.chasisFrameId, eicCardIndex.slotId );
      free(outData);
      return CFG_FAILURE;
    }

    free(outData);
    LOG_PRINT(DEBUG,"markEicCardDisable: Exiting from func");
    return CFG_SUCCESS;
  }

  /*BSC R2.0 Changes Ends*/

  /********************************* Function  Header********************************
    Function Name:       setSystmeTimeRespHandler()
Parameters:          
Return type:         void
Purpose:             To update systemTimeTable on receiving setSystemTime Resp. 
Other Note:          Added for R2.0 
   ************************************************************************************/
  I_Void  setSystmeTimeRespHandler()
  {
    OamOilCfgSetTimeResp * oamOilCfgSetTimeResp;
    oamOilCfgSetTimeResp = (OamOilCfgSetTimeResp *)gCfgMsgBuf;
    if(oamOilCfgSetTimeResp->result != OPERATION_SUCCESS)
    {
      LOG_PRINT(DEBUG,"OPERATION_NOT_SUCCESS received in TrunkPortStatusResp");
      cfgSendNackToCm(CM_ERR_BPM_OPERATION_FAILS);
      return; 
    }

    cfgSendAckToCm();         
    return;
  }


  /*Changes for R2.3.4 Starts*/


  /********************************* Function  Header********************************
    Function Name:       insertPsuCardDetails()
Parameters:          sPowerSupplyObjInfo cardObjInfo
Return type:         void
Purpose:             To insert PSU Card details for which alarm was received.
Other Note:          Added for R2.3.4
   ************************************************************************************/
  I_Void insertPsuCardDetails(sPowerSupplyObjInfo cardObjInfo)
  {
    PowerSupplyInfoTableApi psuCardInfoTableApi;

    bzero(&psuCardInfoTableApi,sizeof(PowerSupplyInfoTableApi));

    LOG_PRINT(LOG_INFO,"insertPsuCardDetails: Entering in function");
    LOG_PRINT(LOG_INFO,"insertPsuCardDetails: FrameId [%d], SlotId [%d]", cardObjInfo.frameID, cardObjInfo.slotID);

    psuCardInfoTableApi.chasisFrameId = cardObjInfo.frameID ;
    if(cardObjInfo.slotID == PSU0_SLOTID)
    { 
      psuCardInfoTableApi.slotId = PSU0_CARD;
    }
    else
    {
      psuCardInfoTableApi.slotId = PSU1_CARD;
    }  

    if(cardObjInfo.cardOperState == BPM_POWERSUPPLY_DISABLE)
    {
      psuCardInfoTableApi.physicalPresenceState = NOT_PRESENT;
      psuCardInfoTableApi.cardType = BPM_CARD_POWER_SUPPLY; 
      psuCardInfoTableApi.cardOperationalState = BPM_POWERSUPPLY_DISABLE;
      psuCardInfoTableApi.peerCardPresence = cardObjInfo.peerCardPresence;
    }
    else
    {
      LOG_PRINT(LOG_INFO,"Inserting PSU Details Value psuCardInfoTableApi.physicalPresenceState = %d psuCardInfoTableApi.cardOperationalState= %d",psuCardInfoTableApi.physicalPresenceState,psuCardInfoTableApi.cardOperationalState);

      psuCardInfoTableApi.cardType = cardObjInfo.cardType ;
      memcpy(psuCardInfoTableApi.cardSerialNumber , cardObjInfo.cardSerialNumber ,20);
      psuCardInfoTableApi.physicalPresenceState = PRESENT;
      psuCardInfoTableApi.cardOperationalState = cardObjInfo.cardOperState ;
      psuCardInfoTableApi.ucVersionMajor = cardObjInfo.uCVersion.major  ;
      psuCardInfoTableApi.ucVersionMinor = cardObjInfo.uCVersion.minor  ;
      psuCardInfoTableApi.ucVersionRevision = cardObjInfo.uCVersion.revision  ;
      psuCardInfoTableApi.peerCardPresence = cardObjInfo.peerCardPresence  ;
    }
    if(updatePowerSupplyInfoTable(&psuCardInfoTableApi) != CLIB_SUCCESS)
    {
      if(insertPowerSupplyInfoTable(&psuCardInfoTableApi) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"insertPsuCardDetails: Can not insert in PowerSupplyInfoTable. ");
        return;
      }
    }
    LOG_PRINT(LOG_INFO,"insertPsuCardDetails: Exiting from function");

  }


  /********************************* Function  Header********************************
    Function Name:       insertFanTrayDetails()
Parameters:          sFanTrayObjInfo fanTrayObjInfo
Return type:         void
Purpose:             To insert Fan Tray details for which alarm was received.
Other Note:          Added for R2.3.4
   ************************************************************************************/
  I_Void insertFanTrayDetails(sFanTrayObjInfo fanTrayObjInfo)
  {
    FanTrayInfoTableApi fanTrayInfoTableApi;
    FanInfoTableApi     fanInfoTableApi; 
    I_U32 i; 

    bzero(&fanTrayInfoTableApi,sizeof(FanTrayInfoTableApi));

    LOG_PRINT(LOG_INFO,"insertFanTrayDetails: Entering in function");
    LOG_PRINT(LOG_INFO,"insertFanTrayDetails: FrameId [%d], fanTray [%d]", fanTrayObjInfo.frameID, fanTrayObjInfo.fanTrayID);

    fanTrayInfoTableApi.chasisFrameId = fanTrayObjInfo.frameID ;
    fanTrayInfoTableApi.fanTrayId = fanTrayObjInfo.fanTrayID;

    if(fanTrayObjInfo.physicalPresenceStatus == BPM_FALSE)
    {
      fanTrayInfoTableApi.physicalPresenceState = NOT_PRESENT;
    }
    else
    {
      fanTrayInfoTableApi.physicalPresenceState = PRESENT;
    } 
    LOG_PRINT(LOG_INFO,"Inserting FanTray Details Value fanTrayInfoTableApi.physicalPresenceState = %d",
        fanTrayInfoTableApi.physicalPresenceState);

    for(i=0;i<MAX_FANS_IN_TRAY ; i++) 
    {
      if(  (fanTrayObjInfo.fanInfo[i].frameID == 0) ||
          (fanTrayObjInfo.fanInfo[i].fanTrayID == 0)   ) 
      {
        continue;
      } 
      fanInfoTableApi.chasisFrameId = fanTrayObjInfo.fanInfo[i].frameID; 
      fanInfoTableApi.fanTrayId = fanTrayObjInfo.fanInfo[i].fanTrayID; 
      fanInfoTableApi.fanId = fanTrayObjInfo.fanInfo[i].fanId; 
      fanInfoTableApi.fanSpeed = fanTrayObjInfo.fanInfo[i].fanSpeed; 

      if(fanTrayObjInfo.fanInfo[i].fanStatus == FAN_WORKING)
        fanInfoTableApi.fanStatus = FAN_RUNNING; 
      else
        fanInfoTableApi.fanStatus = FAN_FAILED; 

      if(fanTrayObjInfo.fanInfo[i].physicalFanPresence == BPM_FALSE)
        fanInfoTableApi.physicalPresenceState = NOT_PRESENT;
      else
        fanInfoTableApi.physicalPresenceState = PRESENT;

      if(updateFanInfoTable(&fanInfoTableApi) != CLIB_SUCCESS)
      {
        if(insertFanInfoTable(&fanInfoTableApi) != CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_INFO,"insertFanDetails: Can not insert in FanInfoTable. ");
          return;
        }
      }
    }
    if(updateFanTrayInfoTable(&fanTrayInfoTableApi) != CLIB_SUCCESS)
    {
      if(insertFanTrayInfoTable(&fanTrayInfoTableApi) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"insertFanTrayDetails: Can not insert in FanTrayInfoTable. ");
        return;
      }
    }
    LOG_PRINT(LOG_INFO,"insertFanTrayDetails: Exiting from function");
  }


  /********************************* Function  Header********************************
    Function Name:       deletePsuCardDetails()
Parameters:          void
Return type:         void
Purpose:             To delete PSU Card details
Other Note:          Added for R2.3.4
   ************************************************************************************/
  I_Void deletePsuCardDetails()
  {
    PowerSupplyInfoTableIndices psuCardInfoTableIndices;
    PowerSupplyInfoTableIndices psuCardInfoTableIndicesAct;
    PowerSupplyInfoTableApi *psuCardInfoTableApiPtr = NULL;
    PowerSupplyInfoTableApi *tmpPsuCardPtr = NULL;
    I_U32 outRows;
    I_U16 outSize;
    SysAlarm *sysAlarm = NULL;
    sysAlarm = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

    LOG_PRINT(LOG_INFO,"deletePsuCardDetails: Entering in Function");

    if(getallPowerSupplyInfoTable(&psuCardInfoTableApiPtr, &outRows, &outSize) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"deletePsuCardDetails: No Row in Psu Card Info Table");
      return;
    }
    if(outRows == 1)
    {
      LOG_PRINT(LOG_INFO,"deletePsuCardDetails: Exiting from function");
      free(psuCardInfoTableApiPtr);
      return;
    }
    //if(psuCardInfoTableApiPtr->slotId != sysAlarm->key2)
    if(psuCardInfoTableApiPtr->slotId == sysAlarm->key2)
    {
      psuCardInfoTableIndices.slotId = psuCardInfoTableApiPtr->slotId;
      tmpPsuCardPtr = (PowerSupplyInfoTableApi *)((I_U8 *)psuCardInfoTableApiPtr + outSize);
      psuCardInfoTableIndicesAct.slotId = tmpPsuCardPtr->slotId;
      LOG_PRINT(LOG_DEBUG,"deletePsuCardDetails 1: Self Slot Id:: %d Peer Slot Id:: %d",psuCardInfoTableApiPtr->slotId, psuCardInfoTableIndicesAct.slotId);
    }
    else
    {
      psuCardInfoTableIndicesAct.slotId = psuCardInfoTableApiPtr->slotId;
      tmpPsuCardPtr = (PowerSupplyInfoTableApi *)((I_U8 *)psuCardInfoTableApiPtr + outSize);
      psuCardInfoTableIndices.slotId = tmpPsuCardPtr->slotId;
      LOG_PRINT(LOG_DEBUG,"deletePsuCardDetails 2: Self Slot Id:: %d Peer Slot Id:: %d",psuCardInfoTableApiPtr->slotId, psuCardInfoTableIndicesAct.slotId);
    }
    free(psuCardInfoTableApiPtr);
    psuCardInfoTableIndices.chasisFrameId = sysAlarm->key1;
    psuCardInfoTableIndicesAct.chasisFrameId = sysAlarm->key1;
    LOG_PRINT(LOG_INFO,"deletePsuCardDetails:To be deleted Frame Id:: %d and Slot Id:: %d ",psuCardInfoTableIndices.chasisFrameId , psuCardInfoTableIndices.slotId);
    if(markPsuCardNotPresent(&psuCardInfoTableIndices,0) != CLIB_SUCCESS) /*0 for updating self status i.e. ejected card*/
    {
      LOG_PRINT(LOG_INFO,"markPsuCardNotPresent 1: Frame Id:: %d and Slot Id:: %d does not exist",
          psuCardInfoTableIndices.chasisFrameId ,psuCardInfoTableIndices.slotId);
    }
    if(markPsuCardNotPresent(&psuCardInfoTableIndicesAct,1) != CLIB_SUCCESS) /*1 for updating peer status i.e. peer card*/
    {
      LOG_PRINT(LOG_INFO,"markPsuCardNotPresent 2: Frame Id:: %d and Slot Id:: %d does not exist",
          psuCardInfoTableIndicesAct.chasisFrameId ,psuCardInfoTableIndicesAct.slotId);
    }
    LOG_PRINT(LOG_INFO,"deletePsuCardDetails: Exiting from Function");
  }

  /******************************* Function  Header*****************************
    Function Name : markPsuCardNotPresent()
Parameters    : PsuCardInfoTableIndices * , I_U8 flag
Return type   : I_S32 
Purpose       : Mark PsuCard NOT_PRESENT in PsuCardInfoTable if the PRESENT_CARD_INFO_RESP 
does not contain those chasisFrameId and slotId                
Other Note    : Added For BSC R2.3.4
   *****************************************************************************/
  I_S32 markPsuCardNotPresent(PowerSupplyInfoTableIndices *psuCardIndex, I_U8 flag)
  {
    PowerSupplyInfoTableApi *outData;
    if( getPowerSupplyInfoTable(psuCardIndex,&outData) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getPowerSupplyInfoTable failed for frameid(%d) slotid(%d)",
          psuCardIndex->chasisFrameId, psuCardIndex->slotId );
      return 1;
    } 
    if(flag) 
    {
      outData->peerCardPresence = NOT_PRESENT;
    }
    else
    {
      outData->physicalPresenceState = NOT_PRESENT;
      outData->cardOperationalState = BPM_POWERSUPPLY_DISABLE;
      outData->ucVersionMajor = 0;
      outData->ucVersionMinor = 0;
      outData->ucVersionRevision = 0;
      memset(outData->cardSerialNumber,0,20);  
    }

    if(updatePowerSupplyInfoTable(outData) != CLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"updatePowerSupplyInfoTable failed for frameid(%d) slotid(%d)",
          psuCardIndex->chasisFrameId, psuCardIndex->slotId );
      free(outData);
      return 2;
    }

    free(outData);
    return 0;
  }

  /********************************* Function  Header********************************
    Function Name:       deleteFanTrayDetails()
Parameters:          void
Return type:         void
Purpose:             To delete Fan Tray details
Other Note:          Added for R2.3.4
   ************************************************************************************/
  I_Void deleteFanTrayDetails()
  {
    FanTrayInfoTableIndices fanTrayInfoTableIndices;
    FanTrayInfoTableApi *fanTrayInfoTableApiPtr = NULL;
    FanTrayInfoTableApi *tmpFanTrayPtr = NULL;
    I_U32 outRows;
    I_U16 outSize;
    SysAlarm *sysAlarm = NULL;
    sysAlarm = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

    LOG_PRINT(LOG_INFO,"deleteFanTrayDetails: Entering in Function");

    if(getallFanTrayInfoTable(&fanTrayInfoTableApiPtr, &outRows, &outSize) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"deleteFanTrayDetails: No Row in Fan Tray Info Table");
      return;
    }
    if(outRows == 1)
    {
      LOG_PRINT(LOG_INFO,"deleteFanTrayDetails: Exiting from function");
      free(fanTrayInfoTableApiPtr);
      return;
    }
    /*if(fanTrayInfoTableApiPtr->fanTrayId != sysAlarm->key2)*/
    if(fanTrayInfoTableApiPtr->fanTrayId == sysAlarm->key2)
    {
      LOG_PRINT(LOG_DEBUG,"deleteFanTrayDetails: FanTrayId:: %d in firstRow",fanTrayInfoTableApiPtr->fanTrayId);
      fanTrayInfoTableIndices.fanTrayId = fanTrayInfoTableApiPtr->fanTrayId;
    }
    else
    {
      tmpFanTrayPtr = (FanTrayInfoTableApi *)((I_U8 *)fanTrayInfoTableApiPtr + outSize);
      LOG_PRINT(LOG_DEBUG,"deleteFanTrayDetails: FanTrayId:: %d in secondRow",tmpFanTrayPtr->fanTrayId);
      fanTrayInfoTableIndices.fanTrayId = tmpFanTrayPtr->fanTrayId;

    }
    fanTrayInfoTableIndices.chasisFrameId = sysAlarm->key1;
    LOG_PRINT(LOG_INFO,"deleteFanTrayDetails:To be deleted FrameId:: %d and fanTrayId:: %d ",
        fanTrayInfoTableIndices.chasisFrameId , fanTrayInfoTableIndices.fanTrayId);
    if(markFanTrayNotPresent(&fanTrayInfoTableIndices) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_INFO,"markFanTrayNotPresent: Frame Id:: %d and fanTrayId:: %d does not exist",
          fanTrayInfoTableIndices.chasisFrameId ,fanTrayInfoTableIndices.fanTrayId);

    }
    LOG_PRINT(LOG_INFO,"deleteFanTrayDetails: Exiting from Function");
  }

  /******************************* Function  Header*****************************
    Function Name : markFanTrayNotPresent()
Parameters    : FanTrayInfoTableIndices * 
Return type   : I_S32 
Purpose       : Mark Fan Tray NOT_PRESENT in PsuCardInfoTable if the PRESENT_CARD_INFO_RESP 
does not contain those chasisFrameId and fantrayId 
Other Note    : Added For BSC R2.3.4
   *****************************************************************************/
  I_S32 markFanTrayNotPresent(FanTrayInfoTableIndices *fanTrayIndex)
  {
    FanTrayInfoTableApi *outData;
    FanInfoTableApi *fanInfoTablePtr;
    FanInfoTableApi *tmpFanInfoTablePtr;
    I_U32 outRows,i = 0;
    I_U16 outSize;

    if( getFanTrayInfoTable(fanTrayIndex,&outData) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getFanTrayInfoTable failed for frameid(%d) fanTrayId(%d)",
          fanTrayIndex->chasisFrameId, fanTrayIndex->fanTrayId );
      return 1;
    } 

    outData->physicalPresenceState = NOT_PRESENT;

    if(updateFanTrayInfoTable(outData) != CLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"updateFanTrayInfoTable failed for frameid(%d) fanTray(%d)",
          fanTrayIndex->chasisFrameId, fanTrayIndex->fanTrayId);
      free(outData);
      return 2;
    }

    if( getallFanInfoTable(&fanInfoTablePtr,&outRows,&outSize) == CLIB_SUCCESS) 
    {
      for(i= 0; i< outRows; i++)
      {  
        tmpFanInfoTablePtr = (FanInfoTableApi *)((I_U8 *)fanInfoTablePtr + i*outSize);
        if( fanTrayIndex->fanTrayId == tmpFanInfoTablePtr->fanTrayId)  
        {
          LOG_PRINT(DEBUG,"Going to mark fanTrayId:%d NOT_PRESENT", fanTrayIndex->fanTrayId); 
          tmpFanInfoTablePtr->physicalPresenceState = NOT_PRESENT;
          tmpFanInfoTablePtr->fanSpeed = 0;
          tmpFanInfoTablePtr->fanStatus = FAN_FAILED;
          if(updateFanInfoTable(tmpFanInfoTablePtr) != CLIB_SUCCESS)
          {
            LOG_PRINT(DEBUG,"updateFanInfoTable failed for frameid(%d) fan(%d)",
                tmpFanInfoTablePtr->chasisFrameId, tmpFanInfoTablePtr->fanId);
          }
        }
      }
      free(fanInfoTablePtr);
    }     
    else
    {
      LOG_PRINT(DEBUG,"getallFanInfoTable failed ");
    }
    free(outData);
    return 0;
  }

  /********************************* Function  Header********************************
    Function Name:       markFanFailed()
Parameters:          void
Return type:         void
Purpose:             To mark Fan failed
Other Note:          Added for R2.3.4
   ************************************************************************************/
  I_S32 markFanFailed()
  {
    FanInfoTableIndices fanInfoTblIndex;
    FanInfoTableApi *fanInfoTblPtr = NULL;
    SysAlarm *sysAlarm = NULL;
    sysAlarm = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

    LOG_PRINT(LOG_INFO,"markFanFailed: Entering in Function");

    fanInfoTblIndex.chasisFrameId = sysAlarm->key1;
    fanInfoTblIndex.fanTrayId = sysAlarm->key2;
    fanInfoTblIndex.fanId = sysAlarm->key3;

    if( getFanInfoTable(&fanInfoTblIndex,&fanInfoTblPtr) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getFanInfoTable failed for frameid(%d) fanTrayId(%d) fanId(%d)",
          fanInfoTblIndex.chasisFrameId,fanInfoTblIndex.fanTrayId,fanInfoTblIndex.fanId );
      return 1;
    } 

    fanInfoTblPtr->fanStatus = FAN_FAILED;

    if(updateFanInfoTable(fanInfoTblPtr) != CLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"updateFanInfoTable failed for frameid(%d) fanTrayId(%d) fanId(%d)",
          fanInfoTblPtr->chasisFrameId,fanInfoTblPtr->fanTrayId,fanInfoTblPtr->fanId);
      free(fanInfoTblPtr);
      return 2;
    }
    free(fanInfoTblPtr);
    LOG_PRINT(LOG_INFO,"markFanFailed: Exiting from Function");
    return 0; 
  }

  /********************************* Function  Header********************************
    Function Name:       markPsuCardFailed()
Parameters:          void
Return type:         void
Purpose:             To mark Fan failed
Other Note:          Added for R2.3.4
   ************************************************************************************/
  I_S32 markPsuCardFailed()
  {
    PowerSupplyInfoTableIndices psuInfoTblIndex;
    PowerSupplyInfoTableApi *psuInfoTblPtr = NULL;
    SysAlarm *sysAlarm = NULL;
    sysAlarm = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

    LOG_PRINT(LOG_INFO,"markPsuCardFailed: Entering in Function");

    psuInfoTblIndex.chasisFrameId = sysAlarm->key1;
    psuInfoTblIndex.slotId = sysAlarm->key2;

    if( getPowerSupplyInfoTable(&psuInfoTblIndex,&psuInfoTblPtr) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getPowerSupplyInfoTable failed for frameid(%d) slotId(%d)",
          psuInfoTblIndex.chasisFrameId,psuInfoTblIndex.slotId);
      return 1;
    } 

    psuInfoTblPtr->cardOperationalState = BPM_POWERSUPPLY_DISABLE;

    if(updatePowerSupplyInfoTable(psuInfoTblPtr) != CLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"updatePowerSupplyInfoTable failed for frameid(%d) slotId(%d)", 
          psuInfoTblPtr->chasisFrameId,psuInfoTblPtr->slotId);
      free(psuInfoTblPtr);
      return 2;
    }
    free(psuInfoTblPtr);
    LOG_PRINT(LOG_INFO,"markPsuCardFailed: Exiting from Function");
    return 0; 
  }

  /********************************* Function  Header********************************
    Function Name:       markFanRunning()
Parameters:          void
Return type:         void
Purpose:             To mark Fan runing
Other Note:          Added for R2.3.4
   ************************************************************************************/
  I_S32 markFanRunning()
  {
    FanInfoTableIndices fanInfoTblIndex;
    FanInfoTableApi *fanInfoTblPtr = NULL;
    SysAlarm *sysAlarm = NULL;
    sysAlarm = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

    LOG_PRINT(LOG_INFO,"markFanRuning: Entering in Function");

    fanInfoTblIndex.chasisFrameId = sysAlarm->key1;
    fanInfoTblIndex.fanTrayId = sysAlarm->key2;
    fanInfoTblIndex.fanId = sysAlarm->key3;

    if( getFanInfoTable(&fanInfoTblIndex,&fanInfoTblPtr) != CLIB_SUCCESS) 
    {
      LOG_PRINT(DEBUG,"getFanInfoTable failed for frameid(%d) fanTrayId(%d) fanId(%d)",
          fanInfoTblIndex.chasisFrameId,fanInfoTblIndex.fanTrayId,fanInfoTblIndex.fanId );
      return 1;
    } 

    fanInfoTblPtr->fanStatus = FAN_RUNNING;

    if(updateFanInfoTable(fanInfoTblPtr) != CLIB_SUCCESS)
    {
      LOG_PRINT(DEBUG,"updateFanInfoTable failed for frameid(%d) fanTrayId(%d) fanId(%d)",
          fanInfoTblPtr->chasisFrameId,fanInfoTblPtr->fanTrayId,fanInfoTblPtr->fanId);
      free(fanInfoTblPtr);
      return 2;
    }
    free(fanInfoTblPtr);
    LOG_PRINT(LOG_INFO,"markFanRuning: Exiting from Function");
    return 0; 
  }

  /*Changes for R2.3.4 Starts*/


  /*Fix for MantisId: 10912 Starts */
  /********************************* Function  Header********************************
    Function Name:       sendDspBootInfoAlarm()
Parameters:           
Return type:         void
Purpose:             To send bootinfo Alarm for dsps.
Other Note:           
   ************************************************************************************/

  I_Void sendDspBootInfoAlarm(sDspObjInfo *dspInfoPtr)
  {
    OamsCfgAfhSysAlarm sysAlarmBuff = {0};

    LOG_PRINT(DEBUG,"Entering in sendDspBootInfoAlarm func");
    sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_DSP_BOOT;
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION; 
    sysAlarmBuff.sysAlarm.key1 =  dspInfoPtr->frameID;
    sysAlarmBuff.sysAlarm.key2 =  dspInfoPtr->slotID;
    sysAlarmBuff.sysAlarm.key3 =  dspInfoPtr->dspId;

    LOG_PRINT(DEBUG,"sendDspBootInfoAlarm: sending BOOT alarm for frameId:%d slotId:%d dspId:%d",
        dspInfoPtr->frameID,dspInfoPtr->slotID,dspInfoPtr->dspId);

    FillObjTypeFromSlotId(dspInfoPtr->slotID,sysAlarmBuff.sysAlarm.info3);

    sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString,
          "DspBootInfo Received ChasisId[%d],SlotId[%d],dspId[%d]",
          dspInfoPtr->frameID,
          dspInfoPtr->slotID, 
          dspInfoPtr->dspId); 

    cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    LOG_PRINT(DEBUG,"Exiting from sendDspBootInfoAlarm func");
  }
  /*Fix for MantisId: 10912 Ends*/


  /******************************* Function  Header*****************************
    Function Name : cpCpifMsgHandler()
Parameters    : 
Return type   : I_Void
Purpose       : 
Other Note    : Added For BSC HA  
   *****************************************************************************/
  void cpCpifMsgHandler() 
  { 

#if 0 //Syns issue with bpm
    if(gCurrentCardState != CARDSTATE_STANDBY)
    {
      LOG_PRINT(DEBUG,"Present cardstate is not standby hence discarding the msg:0x%x rcvd from PEER CFG",
          ((SysHdr*) gCfgMsgBuf)->msgType );
      return;
    }
#endif

    switch (((SysHdr*) gCfgMsgBuf)->msgType) 
    { 
      case CFG_PEERCFG_SWITCH_INFO : 
        LOG_PRINT(LOG_INFO,"Received CFG_PEERCFG_SWITCH_INFO from Peer Cfg.");   
        cfgPeerCfgSwitchInfoHandler();
        break; 
      default : 
        break;          
    }

  } /*cpCpifMsgHandler*/    

  /******************************* Function  Header*****************************
    Function Name : cfgPeerCfgSwitchInfoHandler()
Parameters    : 
Return type   : I_Void
Purpose       : 
Other Note    : Added For BSC HA  
   *****************************************************************************/
  void cfgPeerCfgSwitchInfoHandler()
  {
    CfgCfgSwitchInfoMsg * cfgCfgSwitchInfoMsg;
    OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnect;
    OamsCfgGrhmSwitchDisconnect oamsCfgGrhmSwitchDisconnect;
    I_U32 i;

    LOG_PRINT(DEBUG,"Entering in func:cfgPeerCfgSwitchInfoHandler");
    cfgCfgSwitchInfoMsg = (CfgCfgSwitchInfoMsg *)gCfgMsgBuf; 

    for(i = 0; i < cfgCfgSwitchInfoMsg->count; i++)
    {
      if(cfgCfgSwitchInfoMsg->switchingInfo[i].action == CFG_MAKE_SWITCH)
      { 
        oamsCfgGrhmSwitchConnect.firstE1Num = cfgCfgSwitchInfoMsg->switchingInfo[i].srcStreamId;
        oamsCfgGrhmSwitchConnect.firstTimeSlotNum = cfgCfgSwitchInfoMsg->switchingInfo[i].srcTsId;
        oamsCfgGrhmSwitchConnect.secondE1Num = cfgCfgSwitchInfoMsg->switchingInfo[i].dstStreamId;
        oamsCfgGrhmSwitchConnect.secondTimeSlotNum = cfgCfgSwitchInfoMsg->switchingInfo[i].dstTsId;
        LOG_PRINT(LOG_INFO,"sendSwitchConForMccLinkResource : First E1 : %d, \
            First Ts : %d, SecE1 : %d, SecTs : %d",
            oamsCfgGrhmSwitchConnect.firstE1Num, oamsCfgGrhmSwitchConnect.firstTimeSlotNum,
            oamsCfgGrhmSwitchConnect.secondE1Num, oamsCfgGrhmSwitchConnect.secondTimeSlotNum);
        cfgSendMessage(&oamsCfgGrhmSwitchConnect, sizeof(OamsCfgGrhmSwitchConnect),
            ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0);
      }
      else if(cfgCfgSwitchInfoMsg->switchingInfo[i].action == CFG_BREAK_SWITCH)
      {
        oamsCfgGrhmSwitchDisconnect.firstE1Num = cfgCfgSwitchInfoMsg->switchingInfo[i].srcStreamId;
        oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum = cfgCfgSwitchInfoMsg->switchingInfo[i].srcTsId;
        oamsCfgGrhmSwitchDisconnect.secondE1Num = cfgCfgSwitchInfoMsg->switchingInfo[i].dstStreamId;
        oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum = cfgCfgSwitchInfoMsg->switchingInfo[i].dstTsId;
        LOG_PRINT(LOG_INFO,"oamsCfgGrhmSwitchDisconnectPeer : First E1 : %d, \
            First Ts : %d, SecE1 : %d, SecTs : %d",
            oamsCfgGrhmSwitchDisconnect.firstE1Num, oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum,
            oamsCfgGrhmSwitchDisconnect.secondE1Num, oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum);

        cfgSendMessage(&oamsCfgGrhmSwitchDisconnect, sizeof(OamsCfgGrhmSwitchConnect),
            ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_DISCONNECT, 0);
      }
    }

    LOG_PRINT(DEBUG,"Exiting from func:cfgPeerCfgSwitchInfoHandler");
  }


  /********************************* Function  Header********************************
    Function Name:       peerSwitchInfoRespHandler()
Parameters:          
Return type:         void
Purpose:             To update systemTimeTable on receiving setSystemTime Resp. 
Other Note:          Added for R2.0 
   ************************************************************************************/
  I_Void  peerSwitchInfoRespHandler()
  {
    OamsOilCfgSwitchInfoResp * oamsOilCfgSwitchInfoResp;
    I_U32 i =0;
    oamsOilCfgSwitchInfoResp = (OamsOilCfgSwitchInfoResp *)gCfgMsgBuf;
    LOG_PRINT(DEBUG,"Entering In Func : peerSwitchInfoRespHandler");
    LOG_PRINT(DEBUG,"switchInforesult : slotId:%d",oamsOilCfgSwitchInfoResp->switchInforesult.slotID);
    for(i=0;i<oamsOilCfgSwitchInfoResp->switchInforesult.switchingCount; i++)
    {
      if(oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].result != OAM_BPM_RESULT_SUCCESS)
      {
        LOG_PRINT(DEBUG,"switchInforesult : failed err:%d for srcE1:%d srcTs:%d dstE1:%d dstTs:%d",
            oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].errorCode,
            oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].srcStreamId,
            oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].srcTsId,
            oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].dstStreamId,
            oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].dstTsId);
      }
      else
      {
        LOG_PRINT(DEBUG,"switchInforesult : Success err:%d for srcE1:%d srcTs:%d dstE1:%d dstTs:%d",
            oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].errorCode,
            oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].srcStreamId,
            oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].srcTsId,
            oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].dstStreamId,
            oamsOilCfgSwitchInfoResp->switchInforesult.switchMatrixResult[i].dstTsId);
      }  
    }
    LOG_PRINT(DEBUG,"Exiting from Func : peerSwitchInfoRespHandler");
    return;
  }

  /********************************* Function  Header********************************
    Function Name:       sendPeerTrunkStateChangeReq()
Parameters:          void
Return type:         void
Purpose:             To send TrunkPort State change Request to OIL
In switchover cases it is possbile that trunkstate does not match with the state in DB
In this functions the DB state is reapply to all the configured TrunkPorts
DB State             BPM State              Action
TrunkState Enable -> TrunkState Enable   => NoAction
TrunkState Disable-> TrunkState Enable   => Disable
TrunkState Disable-> TrunkState Disable  => NoAction
TrunkState Enable -> TrunkState Disable  => Enable
BB, 15-06-09::14:59
Other Note:          Added for CS4.0 Init Part

   ************************************************************************************/
  I_Bool sendPeerTrunkStateChangeReq()
  {
    OamsCfgOilPeerE1EnableReq          oamsCfgOilE1EnableReqBuf = {0};
    TrunkPortTableApi              *trunkPortTableApiDbPtr = NULL;
    TrunkPortTableApi              *trunkPortTableApiDbTmpPtr = NULL;
    I_U32 outRows                  = ZERO;
    I_U16 outSize                  = ZERO;
    I_U32 i=0,c=0                    ;
    I_S32 dbStatus=0;
    I_U8 chasisFrameId = 0;
    I_U8 activeSlotId = 0;  

    LOG_PRINT(LOG_INFO,"%s: Enter",__func__);

    if(getallTrunkPortTable(&trunkPortTableApiDbPtr,&outRows, &outSize) !=CLIB_SUCCESS) {
      LOG_PRINT(LOG_INFO,"%s: getallTrunkPortTable failed",__func__);
      return CFG_FAILURE;
    }

    if ( ( dbStatus = getActiveIccSlotId( &chasisFrameId, &activeSlotId) != CLIB_SUCCESS ) )
    {
      LOG_PRINT(LOG_MAJOR,"getActiveIccSlotId Db call failed ErrorCause: %d",dbStatus);
      return CFG_FAILURE;
    }


    for (c=0,i=0; i < outRows; i++)
    {
      trunkPortTableApiDbTmpPtr = (TrunkPortTableApi *) (((I_U8 *)trunkPortTableApiDbPtr + i*outSize));
      /* START : Fix for Mantis Id : 23810 */
      if(trunkPortTableApiDbTmpPtr->slotId == activeSlotId)
      {
        /* END : Fix for Mantis Id : 23810 */

        switch ( trunkPortTableApiDbTmpPtr->physicalTrunkPortState ) 
        {
          case ACTIVATED :
            {
              oamsCfgOilE1EnableReqBuf.portDetail[c].operatorControlledTrunkState =ACTIVATED;
              LOG_PRINT(DEBUG,"activated port found for frame%d slot%d portId%d index%d",
                  trunkPortTableApiDbTmpPtr->chasisFrameId, trunkPortTableApiDbTmpPtr->slotId,
                  trunkPortTableApiDbTmpPtr->trunkPortId,c); 
              oamsCfgOilE1EnableReqBuf.portDetail[c].frameId          = trunkPortTableApiDbTmpPtr->chasisFrameId ;
              if(trunkPortTableApiDbTmpPtr->slotId == activeSlotId)
              {
                oamsCfgOilE1EnableReqBuf.portDetail[c].slotId        = gCfgStandbySlotId;
              }
              else 
              {
                oamsCfgOilE1EnableReqBuf.portDetail[c].slotId        = trunkPortTableApiDbTmpPtr->slotId ;
              }
              oamsCfgOilE1EnableReqBuf.portDetail[c].trunkPortId      = trunkPortTableApiDbTmpPtr->trunkPortId ;
              //oamsCfgOilE1EnableReqBuf.portDetail[c].physicalTrunkPortState filled above
              oamsCfgOilE1EnableReqBuf.portDetail[c].trunkType        = trunkPortTableApiDbTmpPtr->trunkType ;
              oamsCfgOilE1EnableReqBuf.portDetail[c].loopType         =  trunkPortTableApiDbTmpPtr->loopType;
              oamsCfgOilE1EnableReqBuf.portDetail[c].loopback         = trunkPortTableApiDbTmpPtr->loopback ;
              oamsCfgOilE1EnableReqBuf.portDetail[c].trunkFrameOption = trunkPortTableApiDbTmpPtr->trunkFramingOption ;
              oamsCfgOilE1EnableReqBuf.portDetail[c].encodeType       = trunkPortTableApiDbTmpPtr->encodeType ;
              oamsCfgOilE1EnableReqBuf.portDetail[c].sigStrength      = trunkPortTableApiDbTmpPtr->sigStrength ;
              LOG_PRINT(DEBUG,"CfgOilPeerReq buffer filled for frame%d slot%d portId%d index%d",
                  oamsCfgOilE1EnableReqBuf.portDetail[c].frameId,oamsCfgOilE1EnableReqBuf.portDetail[c].slotId,
                  oamsCfgOilE1EnableReqBuf.portDetail[c].trunkPortId,c); 
              c++;
            }
            break;
          case DEACTIVATED:
            {
              LOG_PRINT(LOG_INFO,"%s: TrunkPort[%u] State DEACTIVATED ", 
                  __func__,trunkPortTableApiDbTmpPtr->trunkPortId);
            }     
            break;
        }
        /* START : Fix for Mantis Id : 23810 */
      }//if(trunkPortTableApiDbTmpPtr->slotId == activeSlotId)
      /* END : Fix for Mantis Id : 23810 */  
    }

    free(trunkPortTableApiDbPtr);

    oamsCfgOilE1EnableReqBuf.numPorts = c ;

    LOG_PRINT(DEBUG,"Total Number of TrunkPorts Change Req send for %d",c); 
    LOG_PRINT(LOG_DEBUG,"%s: Send OAMS_CFG_OIL_PEER_TRUNK_STATE_CHANGE_REQ to Oil",__func__);
    cfgSendMessage(&oamsCfgOilE1EnableReqBuf, 
        sizeof(OamsCfgOilPeerE1EnableReq), 
        ENT_OAM_OIL, 
        OAMS_CFG_OIL_PEER_TRUNK_STATE_CHANGE_REQ, 
        0);

    LOG_PRINT(LOG_INFO,"%s: Exit",__func__);
    return CFG_SUCCESS;
  }

  /********************************* Function  Header*****************************
    Function Name   : sendLapdSwitchingInfoToPeerCfg()
Parameters   : None
Return type   : I_Void
Purpose      : 
Other Note   : Added For BSC HA 2.5.5
   *******************************************************************************/
  I_Void sendLapdSwitchingInfoToPeerCfg()
  {
    I_S32 dbStatus = -1;
    I_U32 outRow_bic = ZERO, index = ZERO, outRow_trx = 0;
    I_U16 outSz_bic = 0, outSz_trx = 0;
    I_U32 tsUser = ZERO;
    I_U32 e1Id = ZERO, e1Ts = ZERO, i = ZERO;
    I_S32 status = ZERO;
    BicTableApi *bicTableApiPtr = NULL;
    TrxTableApi *trxTableApiPtr = NULL;
    TrxTsTeiTableApi* trxTsTeiTableApiPtr = NULL;
    TrxTsTeiTableIndices trxTsTeiTableIndices;
    I_PVoid origPtr = NULL;
    SwitchingInfo switchingInfo[100];
    I_U32 recCount = 0;
    I_U32 firstE1 = ZERO;
    I_U32 firstTs = ZERO;
    I_U32 secE1 = ZERO;
    I_U32 secTs = ZERO ,msgSz;
    CfgCfgSwitchInfoMsg *cfgCfgSwitchInfo;

    LOG_PRINT(LOG_INFO,"Entering Function : sendLapdSwitchingInfoToPeerCfg");
    memset(switchingInfo,0,sizeof(SwitchingInfo) * 100);
    dbStatus = getallBicTable(&bicTableApiPtr,&outRow_bic,&outSz_bic);
    if(DBLIB_SUCCESS != dbStatus)
    {
      LOG_PRINT(LOG_MAJOR,"sendLapdSwitchingInfoToPeerCfg : Get Form BicTable Failed");
    }
    else
    {
      origPtr =  bicTableApiPtr;
      for(index = 0; index < outRow_bic; index++)
      {
        bicTableApiPtr = (BicTableApi *)(((I_U8 *)(origPtr)) + (index * outSz_bic));
        status=getIndex(bicTableApiPtr->bicId,&i);
        if(CFG_FAILURE == status)
        {
          LOG_PRINT(LOG_MAJOR,"sendLapdSwitchingInfoToPeerCfg :getIndex  Failed");
          continue;
        }
        if (gBtsData[i].btsType == BIC)
          tsUser =  TS_USAGE_BIC;
        else if(gBtsData[i].btsType == R2_BTS)
          tsUser =  TS_USAGE_BTS;

        status = getE1TsFromBicTrxTimeslotUsageTable(tsUser, 
            bicTableApiPtr->bicId, &e1Id, &e1Ts);
        if(CFG_FAILURE == status)
        {
          LOG_PRINT(LOG_MAJOR,"sendLapdSwitchingInfoToPeerCfg : Get Form \
              BicTrxTimeSlotUsageTable Failed");
          continue;
        }
        firstE1 = e1Id;
        firstTs = e1Ts;  
        if(bicTableApiPtr->btsConnectivityState == BTS_CONNECT)
        {
          /* Get second E1 & Ts */ 
          status = getMccE1Ts(firstE1, firstTs, &secE1, &secTs);
          if(CFG_FAILURE == status)
          {
            LOG_PRINT(LOG_INFO,"sendLapdSwitchingInfoToPeerCfg : Mcc E1 & Ts not Configured");
            continue;
          }
          else
          {
            switchingInfo[recCount].srcStreamId = firstE1;
            switchingInfo[recCount].srcTsId = firstTs;
            switchingInfo[recCount].dstStreamId = secE1;
            switchingInfo[recCount].dstTsId = secTs;
            switchingInfo[recCount].direction = CFG_SWITCH_BI_DIRECTN;
            switchingInfo[recCount].action = CFG_MAKE_SWITCH;
            recCount++;
            LOG_PRINT(LOG_DEBUG,"sendLapdSwitchingInfoToPeerCfg : First E1 : %d, \
                First Ts : %d, SecE1 : %d, SecTs : %d",\
                firstE1, firstTs, secE1, secTs);

          }
        }
        else if(bicTableApiPtr->btsConnectivityState == BTS_DISCONNECT)
        {
#if 0
          /* Get second E1 & Ts */ 
          status = getMccE1Ts(firstE1, firstTs, &secE1, &secTs);
          if(CFG_FAILURE == status)
          {
            LOG_PRINT(LOG_INFO,"prepAndSndSwitchConForBic : Mcc E1 & Ts not Configured");
            continue;
          }
          else
          {
            switchingInfo[recCount].srcStreamId = firstE1;
            switchingInfo[recCount].srcTsId = firstTs;
            switchingInfo[recCount].dstStreamId = secE1;
            switchingInfo[recCount].dstTsId = secTs;
            switchingInfo[recCount].direction = CFG_SWITCH_BI_DIRECTN;
            switchingInfo[recCount].action = CFG_BREAK_SWITCH;
            recCount++;
            LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchDisConForBic : First E1 : %d, \
                First Ts : %d, SecE1 : %d, SecTs : %d",\
                firstE1, firstTs, secE1, secTs);

          }
#endif
          continue; /*Not Sending Switch Discon Req for DISCONNECTED BIC*/ 
        }
      }
      free(origPtr);
    }

    dbStatus = getallTrxTable(&trxTableApiPtr,&outRow_trx,&outSz_trx);
    if(DBLIB_SUCCESS != dbStatus)
    {
      LOG_PRINT(LOG_MAJOR,"sendLapdSwitchingInfoToPeerCfg : Get Form BicTable Failed");
    }
    else
    {
      origPtr =  trxTableApiPtr;
      for(index = 0; index < outRow_trx; index++)
      {
        trxTableApiPtr = (TrxTableApi *)(((I_U8 *)(origPtr)) + (index * outSz_trx));

        if(  (trxTableApiPtr->trxLocation == TRX_LOCATION_BIC) || 
            (trxTableApiPtr->trxLocation == TRX_LOCATION_IN_FRAME)  )
        {
          /* Get first E1 & Ts corresponding to the received ptrxId */
          trxTsTeiTableIndices.ptrxId = trxTableApiPtr->ptrxId;
          dbStatus = getTrxTsTeiTable(&trxTsTeiTableIndices, &trxTsTeiTableApiPtr);
          if(DBLIB_SUCCESS != dbStatus) 
          {
            /* TrxTsTeiTable is not populated for ptrxId received */
            LOG_PRINT(LOG_DEBUG,"sendLapdSwitchingInfoToPeerCfg : TrsTsTeiTable not \
                populated for ptrxId : %d",trxTableApiPtr->ptrxId);
          }
          else
          {
            firstE1 = trxTsTeiTableApiPtr->e1Id;
            firstTs = trxTsTeiTableApiPtr->lapdTs;
            free(trxTsTeiTableApiPtr); 
            /* Get second E1 & Ts */ 
            status = getMccE1Ts(firstE1, firstTs, &secE1, &secTs);
            if(CFG_FAILURE == status)
            {
              /* Mcc E1 or Ts not configured */
              LOG_PRINT(LOG_INFO,"sendLapdSwitchingInfoToPeerCfg : Mcc E1 & Ts not Configured");
            }
            else
            {
              switchingInfo[recCount].srcStreamId = firstE1;
              switchingInfo[recCount].srcTsId = firstTs;
              switchingInfo[recCount].dstStreamId = secE1;
              switchingInfo[recCount].dstTsId = secTs;
              switchingInfo[recCount].direction = CFG_SWITCH_BI_DIRECTN;
              switchingInfo[recCount].action = CFG_MAKE_SWITCH;
              recCount++;
              LOG_PRINT(LOG_DEBUG,"sendLapdSwitchingInfoToPeerCfg: First E1 : %d, \
                  First Ts : %d, SecE1 : %d, SecTs : %d",\
                  firstE1, firstTs, secE1, secTs);

            }
          }
        }//if(trx == INFRAME or BIC)
      }//for
      free(origPtr);
    }//else(DB_SUCCESS)   

    if(recCount == 0)
    {
      LOG_PRINT(DEBUG,"No Bic or Trx is added hence not sending any switching req...");
      return; 
    }

    msgSz = sizeof(CfgCfgSwitchInfoMsg) + sizeof(SwitchingInfo) * (recCount - 1);

    cfgCfgSwitchInfo = (CfgCfgSwitchInfoMsg *)AlocOrdBuf(msgSz);

    if(cfgCfgSwitchInfo == NULL)
    {
      LOG_PRINT(DEBUG,"AlocOrdBuf ret NULL for size:%d", msgSz); 
      return ; 
    }

    cfgCfgSwitchInfo->count = recCount; 
    memcpy(cfgCfgSwitchInfo->switchingInfo,switchingInfo, sizeof(SwitchingInfo)* recCount);
    cfgSendMessage(cfgCfgSwitchInfo, msgSz,ENT_OAMS_CFG, CFG_PEERCFG_SWITCH_INFO,CFG_SWITCH_AT_INIT);
    DalocOrdBuf(cfgCfgSwitchInfo);

    LOG_PRINT(LOG_INFO,"Exiting Function : sendLapdSwitchingInfoToPeerCfg");
  }

  /********************************* Function  Header*****************************
    Function Name   : checkBscTrunkTypeAndDspTrauCoding()
Parameters   : None
Return type   : I_S32
Purpose      : 
Other Note   : Added For BSC 2.5.5 E1-T1
   *******************************************************************************/
  I_S32 checkBscTrunkTypeAndDspTrauCoding()
  {
    TrauConfigTableApi *trauConfigPtr = NULL;
    I_U32 outRow;
    I_U16 outSize;
    I_S32 dbStatus;
    LOG_PRINT(LOG_INFO,"%s:Entering",__func__); 
    dbStatus = getallTrauConfigTable(&trauConfigPtr,&outRow,&outSize);
    if(dbStatus != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_MAJOR,"checkBscTrunkTypeAndDspTrauCoding :getallTrauConfigTable  Failed");
      return FALSE;
    }  
    if(((gBscTrunkType == BPM_TRUNK_TYPE_E1) && (trauConfigPtr->trauCodingFormat != TRAU_A_LAW)) 
        || ((gBscTrunkType == BPM_TRUNK_TYPE_T1) && (trauConfigPtr->trauCodingFormat != TRAU_MU_LAW)))
    {
      LOG_PRINT(LOG_MAJOR,"checkBscTrunkTypeAndDspTrauCoding :TrauCodingFormat: %d and BscTrunkType: %d is mismatched",trauConfigPtr->trauCodingFormat,gBscTrunkType);
      free(trauConfigPtr);
      return FALSE;
    }  
    free(trauConfigPtr);
    LOG_PRINT(LOG_INFO,"%s:Exiting",__func__);  
    return TRUE;
  }  

  void pdcMsgHandler() 
  { 
    OamPdcCfgExtInputPortStatusResp *extInputPortStatusResp;
    ExternalInputPortConfigTableApi *extInputPortConfigTableApiPtr=PNULL;
    ExternalInputPortConfigTableIndices extInputPortConfigIndex;
    I_S32 dbStatus;



    if(((SysHdr*)(gCfgMsgBuf))->msgType == OAM_PDC_CFG_EXT_INPUT_PORT_STATUS_RESP)
    {
      LOG_PRINT(LOG_INFO,"Recieved OAM_PDC_CFG_EXT_INPUT_PORT_STATUS_RESP from PDC..");
      extInputPortStatusResp=(OamPdcCfgExtInputPortStatusResp*)gCfgMsgBuf;
      LOG_PRINT(LOG_DEBUG,"Port %d Status %d" ,extInputPortStatusResp->extPortId,extInputPortStatusResp->extPortState);
      extInputPortConfigIndex.extInputPortId=extInputPortStatusResp->extPortId;
      dbStatus = getExternalInputPortConfigTable(&extInputPortConfigIndex, &extInputPortConfigTableApiPtr);
      if(DBLIB_SUCCESS == dbStatus)
      {
        sendExtInputAlarmToOMC(extInputPortConfigTableApiPtr->extInputPortId,extInputPortStatusResp->extPortState,
            extInputPortConfigTableApiPtr->extInputPortAlarmCondition,extInputPortConfigTableApiPtr->extAlarmText,extInputPortConfigTableApiPtr->extAlarmSeverity);
        free(extInputPortConfigTableApiPtr);
      }
      else
      {
        LOG_PRINT(LOG_CRITICAL,"External Input Port is not present in DB");
      }
      return;
    }
  }
    //Merger for Mantis #31470
/********************************* Function  Header********************************	   
Function Name:       sendNseLockUnlockAlarm()
Parameters:          NSEI - nsei value of NSE
					 adminState- nsei state locked/unlocked
Return type:         void
Purpose:             To Send alarm When NSE is locked / unlocked.
Other Note:          
************************************************************************************/
I_Void sendNseLockUnlockAlarm(I_U16 nsei, I_U32 adminState)
{
    OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};

    LOG_PRINT(LOG_INFO,"sendNseLockUnlockAlarm: Entering from Function");

    OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;

    OamsCfgAfhSysAlarmBuff.sysAlarm.info3      =  OAMS_OBJTYPE_GBINTERFACE;
    OamsCfgAfhSysAlarmBuff.sysAlarm.key1       =  nsei;

	if (adminState == UNLOCKED)
	{
        OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = EVENT_NSE_UNLOCKED;
        OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,\
        "Nsei [%d] Unlocked",nsei);
	}
	else
	{
        OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = EVENT_NSE_LOCKED;
        OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,\
        "Nsei [%d] Locked",nsei);
	}

    cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

    LOG_PRINT(LOG_INFO,"sendNseLockUnlockAlarm: Extiting from Function");
}
    //Merger for Mantis #31470

  /********************************* Change History ***************************
    Release     Patch       Author         Description
    CS2                     Pratibha       Enum Removal Change
    CS2.2           Kapil Tyagi    Added Function bichMsgHandler

   ************************************** End *********************************/
