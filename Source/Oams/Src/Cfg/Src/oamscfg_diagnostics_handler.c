/***********************************File Header ***************************
File Name        : oamscfg_diagnostics_handler.c
Purpose          : This file contains CFG Diagnostics implementation 
Project          : BSC OAM
Subsystem        : Oams
Author           : Grvjn
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h>

/********************************* Function  Header********************************
Function Name:       sendDiagnosticsReqToBpm()
Parameters:          void
Return type:         I_S32 0=Success/else=Fail
Purpose:             To send Diagnostics request to BPM. 
Other Note:
 ************************************************************************************/
I_S32 sendDiagnosticsReqToBpm(I_U16 action)
{
   I_PVoid respPtr; 
   OamsCfgOilDiagnosticReq *oilReqPtr;
   I_U32 respLen = 0, msgSz = 0, fileAction = 0;
   I_U32 objType = 0;

   if(  (gCfgDiagData.repetition == 1 ) || 
        ( gCfgDiagData.diagCmdState == cancelInProgress)  ||
        (gCfgDiagData.diagCmdState == abortInProgress)  )
     fileAction = DIAG_FILE_CLOSE;
   else 
     fileAction = DIAG_FILE_APPEND;

   FILLOBJTYPE(objType,gCfgDiagData.apiId);

   respPtr = formBpmDiagMsg(objType,
                 &(gCfgDiagData.rcvdDiagApi),&respLen,fileAction);

   if( (NULL == respPtr) || ( 0 == respLen ) )
   {
      LOG_PRINT(DEBUG,"formBpmDiagMsg has returned err.. ");  
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return -1;
   }
 
   LOG_PRINT(DEBUG,"formBpmDiagMsg ret respLen:%d", respLen);
   msgSz = sizeof(OamsCfgOilDiagnosticReq) + respLen - 1;
   oilReqPtr = (OamsCfgOilDiagnosticReq *)AlocOrdBuf(msgSz); 
   if(NULL == oilReqPtr)
   {
      LOG_PRINT(MAJOR,"AlocOrdBuf failed for sz:%d", msgSz);
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return -2;
   } 
   oilReqPtr->size = respLen;
   oilReqPtr->action = action;
   memcpy(oilReqPtr->data,respPtr,respLen);
   freeLibDiagPtr(respPtr);

	 cfgSendMessage(oilReqPtr, msgSz,ENT_OAM_OIL, OAM_CFG_OIL_DIAGNOSTIC_REQ, 0);

   DalocOrdBuf(oilReqPtr);
   return 0;
}

/********************************* Function  Header********************************
Function Name:       setDiagnosticsHandler()
Parameters:          void
Return type:         void
Purpose:             To handle Diagnostics request received 
                     from OMC.
Other Note:
 ************************************************************************************/
void setDiagnosticsHandler()
{
   I_PVoid receivedMsgPtr = (IccDiagTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));  
   sCmMsg* receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   I_PVoid tmpPtr = receivedCmMsgPtr;
   DiagStatusTableApi diagStsTbl;
   I_U16 action;
   I_S32 res = 0;
   LOG_PRINT(INFO,"Entering func setDiagnosticsHandler");

   gCfgDiagData.apiId = receivedCmMsgPtr->sHdr.msgType; 

   res = validateDiagnosTcData(receivedMsgPtr,receivedCmMsgPtr->sHdr.msgType);
   if(res != CM_SUCCESS)
   {
      LOG_PRINT(DEBUG,"validateDiagnosTcData failed... err:%d", res);  
      cfgSendNackToCm(res);
      return;
   }

   switch(receivedCmMsgPtr->sHdr.msgType)
   {
      case BSC_API_SET_ICCDIAGTABLE :
        action =  ((IccDiagTableApi *)receivedMsgPtr)->action;
        gCfgRepCnt = &(gCfgDiagData.rcvdDiagApi.iccDiagApi.rep); 
        diagStsTbl.testReference = ((IccDiagTableApi *)receivedMsgPtr)->testReference;
        if(   ((  ( (IccDiagTableApi *)receivedMsgPtr)->iccTestType == DIAGNOS_TCT_ICC_TSI) &&
               (  ( (IccDiagTableApi *)receivedMsgPtr)->iccTestId == DIAGNOS_TCID_ICC_TSI_All))   ||
              ((  ( (IccDiagTableApi *)receivedMsgPtr)->iccTestType == DIAGNOS_TCT_ICC_TSI) &&
               (  ( (IccDiagTableApi *)receivedMsgPtr)->iccTestId == DIAGNOS_TCID_ICC_TSI_4))   ||
              ((  ( (IccDiagTableApi *)receivedMsgPtr)->iccTestType == DIAGNOS_TCT_ICC_FRAMER) &&
               (  ( (IccDiagTableApi *)receivedMsgPtr)->iccTestId == DIAGNOS_TCID_EIC_FRAMER_3))   ||
              ((  ( (IccDiagTableApi *)receivedMsgPtr)->iccTestType == DIAGNOS_TCT_ICC_FRAMER) &&
               (  ( (IccDiagTableApi *)receivedMsgPtr)->iccTestId == DIAGNOS_TCID_EIC_FRAMER_5))  
               )
        {
           LOG_PRINT(DEBUG,"ICC_TSI/FRAMER Test_All/Test_3/Test_5 case Timer Val:%d",DIAG_BPM_ICC_TSI_RESP_TIMER);
           gCfgDiagData.bpmRespTimer = DIAG_BPM_ICC_TSI_RESP_TIMER;
        } 
        else
        {
           gCfgDiagData.bpmRespTimer = DIAG_BPM_RESP_TIMER;
        }
        gCfgDiagData.repetition = ((IccDiagTableApi *)receivedMsgPtr)->rep;
        memcpy(&(gCfgDiagData.rcvdDiagApi),receivedMsgPtr,sizeof(IccDiagTableApi) );
        if(DIAG_CMD_RUN == action)
        { 
           res = insertIccDiagTable(receivedMsgPtr);
           if(res != CLIB_SUCCESS)
           {
               LOG_PRINT(DEBUG,"insertIccDiagTable failed res:%d", res);  
           }
        }
      break;
 
      case BSC_API_SET_EICDIAGTABLE :
        action =  ((EicDiagTableApi *)receivedMsgPtr)->action;
        gCfgRepCnt = &(gCfgDiagData.rcvdDiagApi.eicDiagApi.rep); 
        diagStsTbl.testReference = ((EicDiagTableApi *)receivedMsgPtr)->testReference;
        LOG_PRINT(DEBUG,"EIC TestCase Type Rcvd:%d, TestId:%d",( (EicDiagTableApi *)receivedMsgPtr)->eicTestType,
                  ( (EicDiagTableApi *)receivedMsgPtr)->eicTestId );
        if( ((  ( (EicDiagTableApi *)receivedMsgPtr)->eicTestType == DIAGNOS_TCT_EIC_FRAMER) &&
            (  ( (EicDiagTableApi *)receivedMsgPtr)->eicTestId == DIAGNOS_TCID_EIC_FRAMER_3))   ||
            ((  ( (EicDiagTableApi *)receivedMsgPtr)->eicTestType == DIAGNOS_TCT_EIC_FRAMER) &&
            (  ( (EicDiagTableApi *)receivedMsgPtr)->eicTestId == DIAGNOS_TCID_EIC_FRAMER_5))   
          ) 
        {
           LOG_PRINT(DEBUG,"ICC_TSI/FRAMER Test_All/Test_3/Test_5 case Timer Val:%d",DIAG_BPM_ICC_TSI_RESP_TIMER);
           gCfgDiagData.bpmRespTimer = DIAG_BPM_ICC_TSI_RESP_TIMER;
        }
        else
        {
           gCfgDiagData.bpmRespTimer = DIAG_BPM_RESP_TIMER;
        } 
        gCfgDiagData.repetition = ((EicDiagTableApi *)receivedMsgPtr)->rep;
        memcpy(&(gCfgDiagData.rcvdDiagApi),receivedMsgPtr,sizeof(EicDiagTableApi) );
        if(DIAG_CMD_RUN == action)
        { 
           res = insertEicDiagTable(receivedMsgPtr);
           if(res != CLIB_SUCCESS)
           {
               LOG_PRINT(DEBUG,"insertEicDiagTable failed res:%d", res);  
           }
        }
      break;
 
      case BSC_API_SET_PWRSUPDIAGTABLE :
        action =  ((PwrSupDiagTableApi *)receivedMsgPtr)->action;
        gCfgRepCnt = &(gCfgDiagData.rcvdDiagApi.pwrSupDiagApi.rep); 
        diagStsTbl.testReference = ((PwrSupDiagTableApi *)receivedMsgPtr)->testReference;
        gCfgDiagData.bpmRespTimer = DIAG_BPM_RESP_TIMER;
        gCfgDiagData.repetition = ((PwrSupDiagTableApi *)receivedMsgPtr)->rep;
        memcpy(&(gCfgDiagData.rcvdDiagApi),receivedMsgPtr,sizeof(PwrSupDiagTableApi) );
        if(DIAG_CMD_RUN == action)
        { 
           res = insertPwrSupDiagTable(receivedMsgPtr);
           if(res != CLIB_SUCCESS)
           {
               LOG_PRINT(DEBUG,"insertPwrSupDiagTable failed res:%d", res);  
           }
        }  
      break;

      case BSC_API_SET_FANTRAYDIAGTABLE :
        action =  ((FanTrayDiagTableApi *)receivedMsgPtr)->action;
        diagStsTbl.testReference = ((FanTrayDiagTableApi *)receivedMsgPtr)->testReference;
        gCfgDiagData.bpmRespTimer = DIAG_BPM_RESP_TIMER;
        gCfgDiagData.repetition = ((FanTrayDiagTableApi *)receivedMsgPtr)->rep;
        gCfgRepCnt = &(gCfgDiagData.rcvdDiagApi.fantrayDiagApi.rep); 
        memcpy(&(gCfgDiagData.rcvdDiagApi),receivedMsgPtr,sizeof(FanTrayDiagTableApi) );
        if(DIAG_CMD_RUN == action)
        { 
           res = insertFanTrayDiagTable(receivedMsgPtr);
           if(res != CLIB_SUCCESS)
           {
               LOG_PRINT(DEBUG,"insertFanTrayDiagTable failed res:%d", res);  
           }
        }
      break;
      /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
      case BSC_API_SET_OBMDIAGTABLE:
        action =  ((ObmDiagTableApi *)receivedMsgPtr)->action;
        gCfgRepCnt = &(gCfgDiagData.rcvdDiagApi.obmDiagApi.rep); 
        diagStsTbl.testReference = ((ObmDiagTableApi *)receivedMsgPtr)->testReference;
        gCfgDiagData.bpmRespTimer = DIAG_BPM_RESP_TIMER;
        gCfgDiagData.repetition = ((ObmDiagTableApi *)receivedMsgPtr)->rep;
        memcpy(&(gCfgDiagData.rcvdDiagApi),receivedMsgPtr,sizeof(ObmDiagTableApi) );
        if(DIAG_CMD_RUN == action)
        { 
           res = insertObmDiagTable(receivedMsgPtr);
           if(res != CLIB_SUCCESS)
           {
               LOG_PRINT(DEBUG,"insertObmDiagTable failed res:%d", res);  
           }
        }
      break;
      case BSC_API_SET_OBFDIAGTABLE:
        action =  ((ObfDiagTableApi *)receivedMsgPtr)->action;
        gCfgRepCnt = &(gCfgDiagData.rcvdDiagApi.obfDiagApi.rep); 
        diagStsTbl.testReference = ((ObfDiagTableApi *)receivedMsgPtr)->testReference;
        gCfgDiagData.bpmRespTimer = DIAG_BPM_RESP_TIMER;
        gCfgDiagData.repetition = ((ObfDiagTableApi *)receivedMsgPtr)->rep;
        memcpy(&(gCfgDiagData.rcvdDiagApi),receivedMsgPtr,sizeof(ObmDiagTableApi) );
        if(DIAG_CMD_RUN == action)
        { 
           res = insertObfDiagTable(receivedMsgPtr);
           if(res != CLIB_SUCCESS)
           {
               LOG_PRINT(DEBUG,"insertObfDiagTable failed res:%d", res);  
           }
        }
      break;
      /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
      default : 
        LOG_PRINT(DEBUG,"No case matched in Rcvd Diagnostic type : %d",receivedCmMsgPtr->sHdr.msgType);
        diagStsTbl.testReference = 0; 
      break;
   }

   if(action == DIAG_CMD_RUN)
   {
      *gCfgRepCnt = 1;
      gCfgDiagData.diagCmdState = runInProgress;
      diagStsTbl.status = DIAG_CMD_AWAITED;  
      if( (res = insertDiagStatusTable(&diagStsTbl)) != CLIB_SUCCESS ) 
      {
         LOG_PRINT(DEBUG,"insertDiagStatusTable failed... err:%d", res); 
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
         return;
      }
   }
   else if(action == DIAG_CMD_CANCEL)
   {
      gCfgDiagData.diagCmdState = cancelInProgress;
      if(DIAG_INTERVAL == gCfgDiagTimerRunning)
      {
         LOG_PRINT(DEBUG,"Cancel Req Rcvd while interval timer running");
         StopTimerFrmwrk(gCfgDiagIntervalTimerId); 
         gCfgDiagTimerRunning = DIAG_NO_TIMER_RUNNING;
         abortDiagnostics(TEST_CANCELED);
         cfgSendAckToCm();
         return;
      }
      else if(DIAG_BPM_RESP == gCfgDiagTimerRunning)
      {
         StopTimerFrmwrk(gCfgDiagBpmRespTimerId); 
         gCfgDiagTimerRunning = DIAG_NO_TIMER_RUNNING;
      }
      else
      {
         LOG_PRINT(DEBUG,"No Diag Timer running Err"); 
         cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
         return;
      }  
   }
 
   cfgSendAckToCm();

   if((res = sendDiagnosticsReqToBpm(action)) == 0)
   {
      if( gCfgDiagData.diagCmdState == runInProgress) 
      { 
         gCfgDiagData.repetition--; 
         (*gCfgRepCnt)++; 
         LOG_PRINT(DEBUG,"Value of rep:%d", *gCfgRepCnt);
      }
      startDiagBpmRespTimer();
   } 
   else
   {
      LOG_PRINT(DEBUG,"sendDiagnosticsReqToBpm has returned err:%d", res);
      abortDiagnostics(TEST_ABORTED);
   } 
   LOG_PRINT(INFO,"Exiting func setDiagnosticsHandler");
}

/********************************* Function  Header********************************
Function Name:       sendFtpReqToPdd()
Parameters:          void *bpmRespPtr
Return type:         I_S32
Purpose:             To send ftp req to PDD
Other Note:
 ************************************************************************************/
I_S32 sendFtpReqToPdd(sDiagnosticTestResult * respPtr)
{
   I_S32 msgSz;
   OamsCfgPddFtpReq *pddReqPtr;
   if(respPtr != NULL)
   {
      msgSz = sizeof(OamsCfgPddFtpReq) + strlen((CONST I_S8 *)(respPtr->testReportFileName)) + 1;
   }
   else
   {
     msgSz = sizeof(OamsCfgPddFtpReq) + 1;
   } 
   pddReqPtr = (OamsCfgPddFtpReq *)AlocOrdBuf( msgSz);
   if(NULL == pddReqPtr)
   {
      LOG_PRINT(MAJOR,"AlocOrdBuf failed for sz:%d", msgSz);
      return -1;
   } 

   if(respPtr != NULL)
   {
      memcpy(pddReqPtr->FileName,respPtr->testReportFileName,strlen((CONST I_S8 *)(respPtr->testReportFileName)) + 1);
   }
   else
   {
      strcpy(pddReqPtr->FileName,"\0");
   }
	 cfgSendMessage(pddReqPtr, msgSz,ENT_OAM_PDD, OAMS_CFG_PDD_START_FTP, 0);
   DalocOrdBuf(pddReqPtr);
   return 0;
}

/********************************* Function  Header********************************
Function Name:       bpmDiagnosticsRespHandler()
Parameters:          void
Return type:         void
Purpose:             To handle Diagnostics response received
                     from OIL.
Other Note:
 ************************************************************************************/
void bpmDiagnosticsRespHandler()
{
   OamOilCfgDiagnosticResp * receivedMsgPtr = (OamOilCfgDiagnosticResp *)gCfgMsgBuf ;  
   sDiagnosticTestResult * respPtr;
   I_U32 action;
   I_U32 msgSz = 0;
   
   LOG_PRINT(INFO,"Entering func bpmDiagnosticsRespHandler rcvdLen:%d ",receivedMsgPtr->size );

   if(receivedMsgPtr->size == 0)
   {
      LOG_PRINT(MAJOR,"Resp Len rcvd in OamOilCfgDiagnosticResp is zero"); 
      return;
   }
   
   action = receivedMsgPtr->action;

   //switch(respPtr->testResult)
   switch(action)
   {
      #if 0
      case DIAG_CMD_ABORTED :
        LOG_PRINT(DEBUG,"parseBpmDiagResp testResult: ABORTED");
        gCfgDiagData.diagCmdState = aborted;
        StopTimerFrmwrk(gCfgDiagBpmRespTimerId);
      break;
      #endif
      
      case DIAG_CMD_CANCEL :
        LOG_PRINT(DEBUG,"parseBpmDiagResp testResult: CANCELLED");
        gCfgDiagData.diagCmdState = cancelled;
        StopTimerFrmwrk(gCfgDiagBpmRespTimerId);
        gCfgDiagTimerRunning = DIAG_NO_TIMER_RUNNING;
      break;

      //case DIAG_CMD_COMPLETE :
      case DIAG_CMD_RUN :
        if(  (runInProgress != gCfgDiagData.diagCmdState) || 
             (DIAG_NO_TIMER_RUNNING == gCfgDiagTimerRunning)  )  
        {
           LOG_PRINT(DEBUG,"Dropping Bpm Response(Completed) as Cancel/Abort/ Or No Diag opr Inprogress"); 
           return; 
        }
      break; 

      #if 0
      case DIAG_CMD_AWAITED :
        LOG_PRINT(DEBUG,"parseBpmDiagResp testResult: AWAITED ");
        gCfgDiagData.diagCmdState = runInProgress;
        StopTimerFrmwrk(gCfgDiagBpmRespTimerId);
      break;
      #endif 

      default:
        LOG_PRINT(MAJOR,"parseBpmDiagResp No Type Matched for action:%d",action);
      break;
   }

   respPtr = (sDiagnosticTestResult *)parseBpmDiagResp(receivedMsgPtr->data, action);  

   if(respPtr == NULL)
   {
      LOG_PRINT(MAJOR,"parseBpmDiagResp has returned NULL ptr");
      return;
   }

   if( DIAG_CMD_RUN == action )
   {
      switch(respPtr->testResult)
      {
         case DIAG_CMD_COMPLETE :    
           LOG_PRINT(DEBUG,"parseBpmDiagResp testResult: COMPLETE");
           if(gCfgDiagData.repetition == 0)  
           {
              LOG_PRINT(DEBUG,"Setting DiagCmdState as Completed and Stopping Bpm response timer");
              gCfgDiagData.diagCmdState = completed;
              StopTimerFrmwrk(gCfgDiagBpmRespTimerId);
              gCfgDiagTimerRunning = DIAG_NO_TIMER_RUNNING;
           }
         break;  
         case DIAG_CMD_AWAITED :
           LOG_PRINT(DEBUG,"parseBpmDiagResp testResult: AWAITED ");
           gCfgDiagData.diagCmdState = runInProgress;
           StopTimerFrmwrk(gCfgDiagBpmRespTimerId);
           gCfgDiagTimerRunning = DIAG_NO_TIMER_RUNNING;
         break;
         case DIAG_CMD_ABORTED :
           LOG_PRINT(DEBUG,"parseBpmDiagResp testResult: ABORTED");
           gCfgDiagData.diagCmdState = aborted;
           StopTimerFrmwrk(gCfgDiagBpmRespTimerId);
           gCfgDiagTimerRunning = DIAG_NO_TIMER_RUNNING;
         break;
         default:
           LOG_PRINT(MAJOR,"No case mached for testResult:%d", respPtr->testResult); 
         break;  
      }
   }
   if(runInProgress == gCfgDiagData.diagCmdState )
   {
      LOG_PRINT(DEBUG,"Starting diagnostics interval timer");
      startDiagIntervalTimer(); 
   } 
   else 
   { 
      if(sendFtpReqToPdd(respPtr) != 0)
      {
         LOG_PRINT(DEBUG,"sendFtpReqToPdd has returned err"); 
         gCfgDiagData.diagCmdState = aborted;
         sendDiagAlarmToOmcAndDeleteDiagStsTbl();
      }
   }
   freeLibDiagPtr(respPtr);
   LOG_PRINT(INFO,"Exiting func bpmDiagnosticsRespHandler");
}

/********************************* Function  Header********************************
Function Name:       sendDiagAlarmToOmcAndDeleteDiagStsTbl()
Parameters:          void
Return type:         void
Purpose:             To send diagnostic alarm to AFH and 
                     delete row from Diagnostic status table. 
Other Note:
 ************************************************************************************/
I_Void sendDiagAlarmToOmcAndDeleteDiagStsTbl()
{
   OamsCfgAfhSysAlarm oamsCfgAfhSysAlarm;
   DiagStatusTableIndices diagStsTblIndx;
   I_S32 dbSts;

   bzero(&oamsCfgAfhSysAlarm, sizeof(OamsCfgAfhSysAlarm));
   if( (gCfgDiagData.apiId == BSC_API_SET_ICCDIAGTABLE) ||
       (gCfgDiagData.apiId == BSC_API_SET_EICDIAGTABLE) ||
       (gCfgDiagData.apiId == BSC_API_SET_PWRSUPDIAGTABLE) )
   { 
      oamsCfgAfhSysAlarm.sysAlarm.key1 = gCfgDiagData.rcvdDiagApi.iccDiagApi.chasisFrameId;
      oamsCfgAfhSysAlarm.sysAlarm.key2 = gCfgDiagData.rcvdDiagApi.iccDiagApi.slotId;
      oamsCfgAfhSysAlarm.sysAlarm.key3 = gCfgDiagData.rcvdDiagApi.iccDiagApi.testReference;
      oamsCfgAfhSysAlarm.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
      
      switch(gCfgDiagData.diagCmdState)
      {
         case completed :
              oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_COMPLETED; 
              oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                    oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case has been completed on\
                    FrameId:%d SlotId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                    oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3);
         break;  

         case aborted :
         case abortInProgress:
              oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_ABORTED ; 
              oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                    oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case execution aborted on\
                    FrameId:%d SlotId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                    oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3);
         break;  

         case cancelled :
         case cancelInProgress:
              oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_CANCELLED ; 
              oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                    oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case execution cancelled on\
                    FrameId:%d SlotId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                    oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3);
         break;  
       
         default:
            LOG_PRINT(MAJOR,"InValid cmdState:%d for Icc/Eic/PwrSup Diag ", gCfgDiagData.diagCmdState);
         break; 
      }
      diagStsTblIndx.testReference = gCfgDiagData.rcvdDiagApi.iccDiagApi.testReference;
   }  
   else if(gCfgDiagData.apiId == BSC_API_SET_FANTRAYDIAGTABLE)
   { 
      oamsCfgAfhSysAlarm.sysAlarm.key1 = gCfgDiagData.rcvdDiagApi.fantrayDiagApi.chasisFrameId;
      oamsCfgAfhSysAlarm.sysAlarm.key2 = gCfgDiagData.rcvdDiagApi.fantrayDiagApi.fanTrayId;
      oamsCfgAfhSysAlarm.sysAlarm.key3 = gCfgDiagData.rcvdDiagApi.fantrayDiagApi.fanId;
      oamsCfgAfhSysAlarm.sysAlarm.key4 = gCfgDiagData.rcvdDiagApi.fantrayDiagApi.testReference;
      oamsCfgAfhSysAlarm.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
      
      switch(gCfgDiagData.diagCmdState)
      {
         case completed :
                oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_FANTRAY_COMPLETED;
                oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                      oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case has been completed on\
                      FrameId:%d FanTrayId:%d FanId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                      oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3,
                      oamsCfgAfhSysAlarm.sysAlarm.key4);
         break; 

         case aborted :
                oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_FANTRAY_ABORTED;
                oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                      oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case execution aborted on\
                      FrameId:%d FanTrayId:%d FanId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                      oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3,
                      oamsCfgAfhSysAlarm.sysAlarm.key4);
         break; 

         case cancelled :
                oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_FANTRAY_CANCELLED;
                oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                      oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case execution cancelled on\
                      FrameId:%d FanTrayId:%d FanId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                      oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3,
                      oamsCfgAfhSysAlarm.sysAlarm.key4);
         break; 

         default :
            LOG_PRINT(MAJOR,"InValid cmdState:%d for Icc/Eic/PwrSup Diag ", gCfgDiagData.diagCmdState);
         break; 
      }
      diagStsTblIndx.testReference = gCfgDiagData.rcvdDiagApi.fantrayDiagApi.testReference;
   }
   /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
   else if(gCfgDiagData.apiId == BSC_API_SET_OBMDIAGTABLE)
   {
      oamsCfgAfhSysAlarm.sysAlarm.key1 = gCfgDiagData.rcvdDiagApi.obmDiagApi.chassisFrameID;
      oamsCfgAfhSysAlarm.sysAlarm.key2 = gCfgDiagData.rcvdDiagApi.obmDiagApi.slotID;
      oamsCfgAfhSysAlarm.sysAlarm.key3 = gCfgDiagData.rcvdDiagApi.obmDiagApi.testReference;
      oamsCfgAfhSysAlarm.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
      
      switch(gCfgDiagData.diagCmdState)
      {
         case completed :
              oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_COMPLETED; 
              oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                    oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case has been completed on\
                    FrameId:%d SlotId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                    oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3);
         break;  

         case aborted :
         case abortInProgress:
              oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_ABORTED ; 
              oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                    oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case execution aborted on\
                    FrameId:%d SlotId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                    oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3);
         break;  

         case cancelled :
         case cancelInProgress:
              oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_CANCELLED ; 
              oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                    oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case execution cancelled on\
                    FrameId:%d SlotId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                    oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3);
         break;  
       
         default:
            LOG_PRINT(MAJOR,"InValid cmdState:%d for Icc/Eic/PwrSup Diag ", gCfgDiagData.diagCmdState);
         break; 
      }
      diagStsTblIndx.testReference = gCfgDiagData.rcvdDiagApi.iccDiagApi.testReference;
   }
   else if(gCfgDiagData.apiId == BSC_API_SET_OBFDIAGTABLE)
   {
      oamsCfgAfhSysAlarm.sysAlarm.key1 = gCfgDiagData.rcvdDiagApi.obfDiagApi.chassisFrameID;
      oamsCfgAfhSysAlarm.sysAlarm.key2 = gCfgDiagData.rcvdDiagApi.obfDiagApi.slotID;
      oamsCfgAfhSysAlarm.sysAlarm.key3 = gCfgDiagData.rcvdDiagApi.obfDiagApi.testReference;
      oamsCfgAfhSysAlarm.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
      
      switch(gCfgDiagData.diagCmdState)
      {
         case completed :
              oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_COMPLETED; 
              oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                    oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case has been completed on\
                    FrameId:%d SlotId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                    oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3);
         break;  

         case aborted :
         case abortInProgress:
              oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_ABORTED ; 
              oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                    oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case execution aborted on\
                    FrameId:%d SlotId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                    oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3);
         break;  

         case cancelled :
         case cancelInProgress:
              oamsCfgAfhSysAlarm.sysAlarm.sysalarmId = EVENT_DIAGNOSTICS_CANCELLED ; 
              oamsCfgAfhSysAlarm.sysAlarm.infoStrLen = sprintf(
                    oamsCfgAfhSysAlarm.sysAlarm.infoString,"Test Case execution cancelled on\
                    FrameId:%d SlotId:%d TestReference:%d",oamsCfgAfhSysAlarm.sysAlarm.key1,
                    oamsCfgAfhSysAlarm.sysAlarm.key2,oamsCfgAfhSysAlarm.sysAlarm.key3);
         break;  
       
         default:
            LOG_PRINT(MAJOR,"InValid cmdState:%d for Icc/Eic/PwrSup Diag ", gCfgDiagData.diagCmdState);
         break; 
      }
      diagStsTblIndx.testReference = gCfgDiagData.rcvdDiagApi.iccDiagApi.testReference;
   }
   /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/

   /*Fill Object Type*/
   FILLOBJTYPE(oamsCfgAfhSysAlarm.sysAlarm.info3,gCfgDiagData.apiId); 

   cfgSendMessage(&oamsCfgAfhSysAlarm, sizeof(OamsCfgAfhSysAlarm), \
              ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

   dbSts = deleteDiagStatusTable(&diagStsTblIndx);  
   if(CLIB_SUCCESS != dbSts) 
   {
      LOG_PRINT(MAJOR,"deleteDiagStatusTable failed.. err:%d",dbSts);
   }

   switch(gCfgDiagData.apiId)
   {
      case  BSC_API_SET_ICCDIAGTABLE :
          dbSts = deleteIccDiagTable(&(gCfgDiagData.rcvdDiagApi.iccDiagApi));
          if(dbSts != CLIB_SUCCESS)
          {
             LOG_PRINT(DEBUG,"deleteIccDiagTable failed :%d", dbSts);
          }

          #if 0
          /**Testing Patch To be removed After Testing**/
          OamsCfgOilSetCardOperState oamsCfgOilSetOperConStateReq;
          oamsCfgOilSetOperConStateReq.slotId = gCfgDiagData.rcvdDiagApi.iccDiagApi.slotId; 
          oamsCfgOilSetOperConStateReq.cardType = BPM_CARD_ICC; 
          oamsCfgOilSetOperConStateReq.cardState = CARDSTATE_STANDBY;
          
          cfgSendMessage(&oamsCfgOilSetOperConStateReq, sizeof(OamsCfgOilSetCardOperState), 
                ENT_OAM_OIL, OAMS_CFG_OIL_SET_OPER_CON_STATE_REQ , 0);
          /**Testing Patch To be removed After Testing**/
          #endif
      break;
      
      case BSC_API_SET_EICDIAGTABLE :
          dbSts = deleteEicDiagTable(&(gCfgDiagData.rcvdDiagApi.eicDiagApi));
          if(dbSts != CLIB_SUCCESS)
          {
             LOG_PRINT(DEBUG,"deleteEicDiagTable failed :%d", dbSts);
          }
      break;
      
      case BSC_API_SET_PWRSUPDIAGTABLE :
          dbSts = deletePwrSupDiagTable(&(gCfgDiagData.rcvdDiagApi.pwrSupDiagApi));
          if(dbSts != CLIB_SUCCESS)
          {
             LOG_PRINT(DEBUG,"deletePwrSupDiagTable failed :%d", dbSts);
          }
      break; 
 
      case BSC_API_SET_FANTRAYDIAGTABLE :
          dbSts = deleteFanTrayDiagTable(&(gCfgDiagData.rcvdDiagApi.fantrayDiagApi));
          if(dbSts != CLIB_SUCCESS)
          {
             LOG_PRINT(DEBUG,"deleteFanTrayDiagTable failed :%d", dbSts);
          }
      break;
      /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
      case BSC_API_SET_OBMDIAGTABLE:
          dbSts = deleteObmDiagTable(&(gCfgDiagData.rcvdDiagApi.obmDiagApi));
          if(dbSts != CLIB_SUCCESS)
          {
             LOG_PRINT(DEBUG,"deleteObmDiagTable failed :%d", dbSts);
          }
      break;
      
      case BSC_API_SET_OBFDIAGTABLE:
          dbSts = deleteObfDiagTable(&(gCfgDiagData.rcvdDiagApi.obfDiagApi));
          if(dbSts != CLIB_SUCCESS)
          {
             LOG_PRINT(DEBUG,"deleteObfDiagTable failed :%d", dbSts);
          }
      break;
      /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/

      default:
          LOG_PRINT(MAJOR, "ERR case no api type matched:%d",gCfgDiagData.apiId);
      break;      
   }
   bzero(&gCfgDiagData,sizeof(DiagDataStruct)); 
}

/********************************* Function  Header********************************
Function Name:       pddMsgHandler()
Parameters:          void
Return type:         void
Purpose:             To handle ftp response received from OIL.
Other Note:
 ************************************************************************************/
I_Void pddMsgHandler()
{
   OamPddCfgFtpComp *receivedMsgPtr = (OamPddCfgFtpComp *)gCfgMsgBuf;
   LOG_PRINT(INFO,"Entering func pddMsghandler ");  
   switch (((SysHdr*) gCfgMsgBuf)->msgType) 
   {
      case OAM_PDD_CFG_FTP_COMPLETE :
         if(receivedMsgPtr->result  == PDD_FILE_TRANSFER_SUCC )
         {
             LOG_PRINT(DEBUG,"PDD has successfully trnsefered the file");
             /*Send Alarm to OMC*/
             sendDiagAlarmToOmcAndDeleteDiagStsTbl();  
         }
         else
         {
             LOG_PRINT(MAJOR,"File Transfer for Diagnostic Test Report failed at PDD err :%d",
                     receivedMsgPtr->result );
              gCfgDiagData.diagCmdState = aborted; 
             /*Send Alarm to OMC*/
             sendDiagAlarmToOmcAndDeleteDiagStsTbl();  
         }
      break; 
 
      case OAM_PDD_CFG_FTP_START :
          if( completed == gCfgDiagData.diagCmdState)
          {
             sendFtpReqToPdd(NULL);
          }  
          else if( runInProgress == gCfgDiagData.diagCmdState)
          {
             LOG_PRINT(DEBUG,"Diag is run in progress so doing nothing in FTP_START");
          }  
          else
          {  
             cfgCleanupDiagnosticStsTable();
          } 
      break;
  }
 
   LOG_PRINT(INFO,"Exiting func pddMsghandler ");  
}

/********************************* Function  Header********************************
Function Name:       startDiagBpmRespTimer()
Parameters:          void
Return type:         void
Purpose:             To start guard Timer for Bpm 
                     Diagnostics resp.
Other Note:
 ************************************************************************************/
void startDiagBpmRespTimer()
{
   SysAddr slfAddr;
   TmrPayLoad tmrPayLoad;
   LOG_PRINT(LOG_INFO,"Entering startDiagBpmRespTimer()");
   LOG_PRINT(LOG_INFO,"Value of diag bpm resp Timer - %d",gCfgDiagData.bpmRespTimer);
   slfAddr.entity= ENT_OAMS_CFG;
   tmrPayLoad.payLoad[0] = DIAG_BPM_RESP;
   StartTimerFrmwrk(&slfAddr,gCfgDiagData.bpmRespTimer,&tmrPayLoad,&gCfgDiagBpmRespTimerId);
   gCfgDiagTimerRunning = DIAG_BPM_RESP;
   LOG_PRINT(LOG_INFO,"Exiting startDiagBpmRespTimer()");
}


/********************************* Function  Header********************************
Function Name:       startDiagIntervalTimer()
Parameters:          void
Return type:         void
Purpose:             To start inetrval Timer between two Diag req 
                     towards bpm. 
Other Note:
 ************************************************************************************/
void startDiagIntervalTimer()
{
   SysAddr slfAddr;
   TmrPayLoad tmrPayLoad;
   I_U32 diagIntervalTimer;
   LOG_PRINT(LOG_INFO,"Entering startWaitForBpmRespTimer()");
   
   diagIntervalTimer = DIAG_INTERVAL_TIMER;
   LOG_PRINT(LOG_INFO,"Value of diag interval Timer - %d",diagIntervalTimer);
   slfAddr.entity= ENT_OAMS_CFG;
   tmrPayLoad.payLoad[0] = DIAG_INTERVAL;
   StartTimerFrmwrk(&slfAddr,diagIntervalTimer,&tmrPayLoad,&gCfgDiagIntervalTimerId);
   gCfgDiagTimerRunning = DIAG_INTERVAL;
   LOG_PRINT(LOG_INFO,"Exiting startWaitForBpmRespTimer()");
}

/********************************* Function  Header********************************
Function Name:       abortDiagnostics()
Parameters:          void
Return type:         void
Purpose:             To abort any diagnostics running 
Other Note:
 ************************************************************************************/
I_Void abortDiagnostics(I_U32 testResult)
{
   sDiagnosticResult bpmReqBuf;
   sDiagnosticTestResult * respPtr;
   I_U32 msgSz = 0;

   LOG_PRINT(INFO,"Entering func abortDiagnostics");
   switch(gCfgDiagData.apiId)
   {
      case BSC_API_SET_ICCDIAGTABLE :
      {
         bpmReqBuf.testType = gCfgDiagData.rcvdDiagApi.iccDiagApi.iccTestType; 
         bpmReqBuf.testID =  gCfgDiagData.rcvdDiagApi.iccDiagApi.iccTestId;
         bpmReqBuf.frameID = gCfgDiagData.rcvdDiagApi.iccDiagApi.chasisFrameId;
         bpmReqBuf.slotID =  gCfgDiagData.rcvdDiagApi.iccDiagApi.slotId;
         bpmReqBuf.testRef = gCfgDiagData.rcvdDiagApi.iccDiagApi.testReference;
         //bpmReqBuf.repititions =  gCfgDiagData.rcvdDiagApi.iccDiagApi.rep;
         bpmReqBuf.errCode =  0;
         bpmReqBuf.testResult = (I_U8)testResult; 
         bpmReqBuf.data[0] = 0;
      } 
      break;     

      case BSC_API_SET_EICDIAGTABLE :
      {
         bpmReqBuf.testType = gCfgDiagData.rcvdDiagApi.eicDiagApi.eicTestType; 
         bpmReqBuf.testID =  gCfgDiagData.rcvdDiagApi.eicDiagApi.eicTestId;
         bpmReqBuf.frameID = gCfgDiagData.rcvdDiagApi.eicDiagApi.chasisFrameId;
         bpmReqBuf.slotID =  gCfgDiagData.rcvdDiagApi.eicDiagApi.slotId;
         bpmReqBuf.testRef = gCfgDiagData.rcvdDiagApi.eicDiagApi.testReference;
         //bpmReqBuf.repititions =  gCfgDiagData.rcvdDiagApi.eicDiagApi.rep;
         bpmReqBuf.errCode =  0;
         bpmReqBuf.testResult = (I_U8)testResult; 
         bpmReqBuf.data[0] = 0;
      }
      break;     

      case BSC_API_SET_PWRSUPDIAGTABLE :
      {
         bpmReqBuf.testType = gCfgDiagData.rcvdDiagApi.pwrSupDiagApi.psuTestType; 
         bpmReqBuf.testID =  gCfgDiagData.rcvdDiagApi.pwrSupDiagApi.psuTestId;
         bpmReqBuf.frameID = gCfgDiagData.rcvdDiagApi.pwrSupDiagApi.chasisFrameId;
         bpmReqBuf.slotID =  gCfgDiagData.rcvdDiagApi.pwrSupDiagApi.slotId;
         bpmReqBuf.testRef = gCfgDiagData.rcvdDiagApi.pwrSupDiagApi.testReference;
         //bpmReqBuf.repititions =  gCfgDiagData.rcvdDiagApi.pwrSupDiagApi.rep;
         bpmReqBuf.errCode =  0;
         bpmReqBuf.testResult = (I_U8)testResult; 
         bpmReqBuf.data[0] = 0;
      }
      break;     

      case BSC_API_SET_FANTRAYDIAGTABLE :
      {
         bpmReqBuf.testType = gCfgDiagData.rcvdDiagApi.fantrayDiagApi.fanTrayTestType; 
         bpmReqBuf.testID =  gCfgDiagData.rcvdDiagApi.fantrayDiagApi.fanTrayTestId;
         bpmReqBuf.frameID = gCfgDiagData.rcvdDiagApi.fantrayDiagApi.chasisFrameId;
         bpmReqBuf.slotID =  gCfgDiagData.rcvdDiagApi.fantrayDiagApi.fanTrayId;
         bpmReqBuf.testRef = gCfgDiagData.rcvdDiagApi.fantrayDiagApi.testReference;
         //bpmReqBuf.repititions =  gCfgDiagData.rcvdDiagApi.fantrayDiagApi.rep;
         bpmReqBuf.errCode =  0;
         bpmReqBuf.testResult = (I_U8)testResult; 
         bpmReqBuf.data[0] = 0;
      }
      break;    
      /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
      case BSC_API_SET_OBMDIAGTABLE:
      {
         bpmReqBuf.testType = gCfgDiagData.rcvdDiagApi.obmDiagApi.obmTestType; 
         bpmReqBuf.testID =  gCfgDiagData.rcvdDiagApi.obmDiagApi.obmTestId;
         bpmReqBuf.frameID = gCfgDiagData.rcvdDiagApi.obmDiagApi.chassisFrameID;
         bpmReqBuf.slotID =  gCfgDiagData.rcvdDiagApi.obmDiagApi.slotID;
         bpmReqBuf.testRef = gCfgDiagData.rcvdDiagApi.obmDiagApi.testReference;
         bpmReqBuf.errCode =  0;
         bpmReqBuf.testResult = (I_U8)testResult; 
         bpmReqBuf.data[0] = 0;
      }
      break;
      
      case BSC_API_SET_OBFDIAGTABLE:
      {
         bpmReqBuf.testType = gCfgDiagData.rcvdDiagApi.obfDiagApi.obfTestType; 
         bpmReqBuf.testID =  gCfgDiagData.rcvdDiagApi.obfDiagApi.obfTestId;
         bpmReqBuf.frameID = gCfgDiagData.rcvdDiagApi.obfDiagApi.chassisFrameID;
         bpmReqBuf.slotID =  gCfgDiagData.rcvdDiagApi.obfDiagApi.slotID;
         bpmReqBuf.testRef = gCfgDiagData.rcvdDiagApi.obfDiagApi.testReference;
         bpmReqBuf.errCode =  0;
         bpmReqBuf.testResult = (I_U8)testResult; 
         bpmReqBuf.data[0] = 0;
      }
      break;
      /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/ 

      default :
          LOG_PRINT(MAJOR,"No case matched for gCfgDiagDat. apiId:%d",gCfgDiagData.apiId);
      break; 
   } 

   respPtr = (sDiagnosticTestResult *)parseBpmDiagResp(&bpmReqBuf, testResult);  
   if(respPtr == NULL)
   {
      LOG_PRINT(MAJOR,"parseBpmDiagResp has returned NULL ptr");
      return;
   }

   if(TEST_CANCELED == testResult)
   {
      gCfgDiagData.diagCmdState = cancelled; 
   }
   else
   {
      gCfgDiagData.diagCmdState = aborted; 
   }

   if(sendFtpReqToPdd(respPtr) != 0)
   {
      LOG_PRINT(DEBUG,"sendFtpReqToPdd has returned err"); 
      sendDiagAlarmToOmcAndDeleteDiagStsTbl();
   }

   freeLibDiagPtr(respPtr);
   LOG_PRINT(INFO,"Exiting func abortDiagnostics");
}

/********************************* Function  Header********************************
Function Name:       getDiagnosticsData()
Parameters:          I_U16 referenceNumber 
Return type:         I_S32 CFG_SUCCESS/CFG_FAILURE
Purpose:             To get Diagnostics complete Data on the basis
                     of reference.  
Other Note:
 ************************************************************************************/
I_S32 getDiagnosticsData(I_U16 testRef, I_U16 action)
{
   I_S32 dbSts = 0, res = 0;
   I_U16 outSize = 0;
   I_U32 outRows = 0;
   I_PVoid outData;
   
   dbSts = getallIccDiagTable(&outData, &outRows, &outSize);
   if(dbSts == CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"Data Found in Icc Diagnostic Table"); 
      if(testRef == ((IccDiagTableApi *)outData)->testReference)
      {  
        gCfgDiagData.apiId = BSC_API_SET_ICCDIAGTABLE;
        gCfgDiagData.repetition = ((IccDiagTableApi *)outData)->rep;
        memcpy(&(gCfgDiagData.rcvdDiagApi.iccDiagApi),outData,sizeof(IccDiagTableApi)); 
        gCfgDiagData.rcvdDiagApi.iccDiagApi.action = action; 
        gCfgDiagData.rcvdDiagApi.iccDiagApi.rep = 0; 
        free(outData);
        return CFG_SUCCESS;
      }
      else
      {
        LOG_PRINT(MAJOR,"ERROR Case ... Test Ref mismatched in diagStsTbl and IccDiagTbl\
                : Deleting Row from ICC DIAG Table");
        if(deleteIccDiagTable(outData) != CLIB_SUCCESS)
        {
            LOG_PRINT(DEBUG,"deleteIccDiagTable failed...")
        }
        free(outData);
      } 
   }

   dbSts = getallEicDiagTable(&outData, &outRows, &outSize);
   if(dbSts == CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"Data Found in Eic Diagnostic Table"); 
      if(testRef == ((EicDiagTableApi *)outData)->testReference)
      {  
        gCfgDiagData.apiId = BSC_API_SET_EICDIAGTABLE;
        gCfgDiagData.repetition = ((EicDiagTableApi *)outData)->rep;
        memcpy(&(gCfgDiagData.rcvdDiagApi.eicDiagApi),outData,sizeof(EicDiagTableApi)); 
        gCfgDiagData.rcvdDiagApi.eicDiagApi.action = action; 
        gCfgDiagData.rcvdDiagApi.eicDiagApi.rep = 0; 
        free(outData);
        return CFG_SUCCESS;
      }
      else
      {
        LOG_PRINT(MAJOR,"ERROR Case ... Test Ref mismatched in diagStsTbl and EicDiagTbl\
                : Deleting Row from EIC DIAG Table");
        if(deleteEicDiagTable(outData) != CLIB_SUCCESS)
        {
            LOG_PRINT(DEBUG,"deleteEicDiagTable failed...")
        }
        free(outData);
      } 
   }
   
   dbSts = getallPwrSupDiagTable(&outData, &outRows, &outSize);
   if(dbSts == CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"Data Found in PSU Diagnostic Table"); 
      if(testRef == ((PwrSupDiagTableApi *)outData)->testReference)
      {  
        gCfgDiagData.apiId = BSC_API_SET_PWRSUPDIAGTABLE;
        gCfgDiagData.repetition = ((PwrSupDiagTableApi *)outData)->rep;
        memcpy(&(gCfgDiagData.rcvdDiagApi.pwrSupDiagApi),outData,sizeof(PwrSupDiagTableApi)); 
        gCfgDiagData.rcvdDiagApi.pwrSupDiagApi.action = action; 
        gCfgDiagData.rcvdDiagApi.pwrSupDiagApi.rep = 0; 
        free(outData);
        return CFG_SUCCESS;
      }
      else
      {
        LOG_PRINT(MAJOR,"ERROR Case ... Test Ref mismatched in diagStsTbl and PsuDiagTbl\
                : Deleting Row from PSU DIAG Table");
        if(deletePwrSupDiagTable(outData) != CLIB_SUCCESS)
        {
            LOG_PRINT(DEBUG,"deletePwrSupDiagTable failed...")
        }
        free(outData);
      } 
   }   

   dbSts = getallFanTrayDiagTable(&outData, &outRows, &outSize);
   if(dbSts == CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"Data Found in Fan Tray Diagnostic Table"); 
      if(testRef == ((FanTrayDiagTableApi *)outData)->testReference)
      {  
        gCfgDiagData.apiId = BSC_API_SET_FANTRAYDIAGTABLE;
        gCfgDiagData.repetition = ((FanTrayDiagTableApi *)outData)->rep;
        memcpy(&(gCfgDiagData.rcvdDiagApi.fantrayDiagApi),outData,sizeof(FanTrayDiagTableApi)); 
        gCfgDiagData.rcvdDiagApi.fantrayDiagApi.action = action; 
        gCfgDiagData.rcvdDiagApi.fantrayDiagApi.rep = 0; 
        free(outData);
        return CFG_SUCCESS;
      }
      else
      {
        LOG_PRINT(MAJOR,"ERROR Case ... Test Ref mismatched in diagStsTbl and FanTrayDiagTbl\
                : Deleting Row from FANTRAY DIAG Table");
        if(deleteFanTrayDiagTable(outData) != CLIB_SUCCESS)
        {
            LOG_PRINT(DEBUG,"deleteFanTrayDiagTable failed...")
        }
        free(outData);
      } 
   }
  
   return CFG_FAILURE;
}

/********************************* Function  Header********************************
Function Name:       cfgCleanupDiagnosticStsTable()
Parameters:          void
Return type:         void
Purpose:             To abort any diagnostics running before switchover
Other Note:
 ************************************************************************************/
I_Void cfgCleanupDiagnosticStsTable()
{
   I_S32 dbSts = 0, res = 0;
   I_U16 outSize = 0;
   I_U32 outRows = 0;
   I_U16 action = 0; 
   DiagStatusTableApi *diagStsTbl;
   
   action = DIAG_CMD_ABORTED;
   dbSts = getallDiagStatusTable(&diagStsTbl, &outRows, &outSize);
  
   if(dbSts != CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"No Diagnostics running prior to switchover");
      return;
   }
   LOG_PRINT(DEBUG,"Going To abort Diagnostics running prior to switchover TestReference:%d",
              diagStsTbl->testReference);
   
    if( getDiagnosticsData(diagStsTbl->testReference, action) == CFG_SUCCESS)
    { 
      gCfgDiagData.diagCmdState = abortInProgress;
      //res = sendDiagnosticsReqToBpm( action);
      abortDiagnostics(TEST_ABORTED);
    } 
    free(diagStsTbl);
}
/********************************* Change History ***************************
   Release     Patch       Author            Description
   R2.5.5                  Grvjn             Added this file for Diagnostics
                                             handling
 ************************************** End *********************************/
