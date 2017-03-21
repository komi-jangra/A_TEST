#include "bpmDiaglib.h"
#include "bpmInclude.h"
/* lib global paramters */
sLibGlobalParam libGlobalParam;
sParamKeySet paramKeySet[MAX_TCT_ID][MAX_TEST_ID];
FILE *filePtr;
I_U8 gTestFail;
I_U8 gTestRunning = 0;
time_t t_start, t_end;
/* *** */

void addDiagReqParm(sDiagnosticRequest *diagnosticRequest);

I_U8* formBpmDiagMsg(I_U16 ApiId,  void *mibptr, I_U32 *respLen,  I_U32 fileAction)
{
  I_U32 i, t;
  I_U8 paramBits;
  I_U8 *buff;
  IccDiagReq *iccDiagReq;
  EicDiagReq *eicDiagReq;
  PwrSupDiagReq *pwrSupDiagReq;
  FanTrayDiagReq *fanTrayDiagReq;
  ObmDiagReq *obmDiagReq;
  ObfDiagReq *obfDiagReq;

  sDiagnosticRequest diagnosticRequest;

  if(mibptr == NULL)
  {
      LOG_PRINT(CRITICAL,"formBpmDiagMsg: mibptr NULL");
      return NULL;
  }

  if((buff = (I_U8 *)malloc(sizeof(sDiagnosticRequest))) == NULL)
  {
      LOG_PRINT(CRITICAL,"formBpmDiagMsg: malloc() sDiagnosticRequest Failed");
      return NULL;
  }

  if(gTestRunning == 0)
  {
      /* Get current time and save for future use */
      gTestRunning = 1;
      t_start = time(NULL);
      LOG_PRINT(CRITICAL,"t_start after read[%ld]",(long)t_start);
  }

  *respLen  = sizeof(sDiagnosticRequest);

  libGlobalParam.fileAction = fileAction;
  libGlobalParam.ApiId      = ApiId;  

  switch(ApiId)
  {
    case OAMS_OBJTYPE_ICC :
      iccDiagReq = (IccDiagReq*)mibptr; 
      libGlobalParam.repititionCnt      = iccDiagReq->args[8];  
      libGlobalParam.suppress      = iccDiagReq->args[10];  
      paramBits = paramKeySet[iccDiagReq->iccTestType][iccDiagReq->iccTestId].paramBits;

      diagnosticRequest.frameID = iccDiagReq->chassisFrameId; 
      diagnosticRequest.slotID  = iccDiagReq->slotId;
      diagnosticRequest.testRef = iccDiagReq->testReference;
      diagnosticRequest.testType= iccDiagReq->iccTestType;
      diagnosticRequest.testID = iccDiagReq->iccTestId;
      diagnosticRequest.repititions = 0;
      diagnosticRequest.action = iccDiagReq->action;
      diagnosticRequest.intr = iccDiagReq->args[9];
      diagnosticRequest.sup  = iccDiagReq->args[10];
      for(i=0, t=0; t < MAX_ARGS; t++ )
      {
        if(((paramBits >> t) & 0x01))
        {
          diagnosticRequest.args[i] = iccDiagReq->args[t];
	  LOG_PRINT(CRITICAL,"args[%d]=%d ",i,diagnosticRequest.args[i]);
          i++;
        }
      }
      diagnosticRequest.numArgs  = i;//iccDiagReq->numArg;
      addDiagReqParm(&diagnosticRequest);
      break;

    case OAMS_OBJTYPE_EIC :
      eicDiagReq = (EicDiagReq*)mibptr; 
      libGlobalParam.repititionCnt      = eicDiagReq->args[6];
      libGlobalParam.suppress      = eicDiagReq->args[8];
      paramBits = paramKeySet[eicDiagReq->eicTestType][eicDiagReq->eicTestId].paramBits;

      diagnosticRequest.frameID = eicDiagReq->chassisFrameId; 
      diagnosticRequest.slotID  = eicDiagReq->slotId;
      diagnosticRequest.testRef = eicDiagReq->testReference;
      diagnosticRequest.testType= eicDiagReq->eicTestType;
      diagnosticRequest.testID = eicDiagReq->eicTestId;
      diagnosticRequest.repititions = 0; 
      diagnosticRequest.action = eicDiagReq->action;
      diagnosticRequest.intr = eicDiagReq->args[7];
      diagnosticRequest.sup  = eicDiagReq->args[8];
      for(i=0, t=0; t < MAX_ARGS; t++ )
      {
        if(((paramBits >> t) & 0x01))
        {
          diagnosticRequest.args[i] = eicDiagReq->args[t];
	  LOG_PRINT(CRITICAL,"args[%d]=%d ",i,diagnosticRequest.args[i]);
          i++;
        }
      }
      diagnosticRequest.numArgs  = i;//iccDiagReq->numArg;
      addDiagReqParm(&diagnosticRequest);
      break;
      
    case OAMS_OBJTYPE_PSU :
      pwrSupDiagReq = (PwrSupDiagReq*)mibptr; 
      libGlobalParam.repititionCnt      = pwrSupDiagReq->args[0];
      libGlobalParam.suppress      = pwrSupDiagReq->args[2];
      paramBits = paramKeySet[pwrSupDiagReq->psuTestType][pwrSupDiagReq->psuTestId].paramBits;

      diagnosticRequest.frameID = pwrSupDiagReq->chassisFrameId; 

      /* Convert CFG SlotID CFG(1,2) to PSU(E,F) */
      if(pwrSupDiagReq->slotId == 1)
      {
	  diagnosticRequest.slotID  = PSU0;
      }
      else if(pwrSupDiagReq->slotId == 2)
      {
	  diagnosticRequest.slotID  = PSU1;
      }
      diagnosticRequest.testRef = pwrSupDiagReq->testReference;
      diagnosticRequest.testType= pwrSupDiagReq->psuTestType;
      diagnosticRequest.testID = pwrSupDiagReq->psuTestId;
      diagnosticRequest.repititions = 0;
      diagnosticRequest.action = pwrSupDiagReq->action;
      diagnosticRequest.numArgs  = pwrSupDiagReq->numArg;
      diagnosticRequest.intr = pwrSupDiagReq->args[1];
      diagnosticRequest.sup  = pwrSupDiagReq->args[2];
      for(i=0, t=0; t < MAX_ARGS; t++ )
      {
        if(((paramBits >> t) & 0x01))
        {
          diagnosticRequest.args[i] = pwrSupDiagReq->args[t];
	  LOG_PRINT(CRITICAL,"args[%d]=%d ",i,diagnosticRequest.args[i]);
          i++;
        }
      }
      diagnosticRequest.numArgs  = i;//iccDiagReq->numArg;
      addDiagReqParm(&diagnosticRequest);
      break;

    case OAMS_OBJTYPE_FANTRAY :
      fanTrayDiagReq = (FanTrayDiagReq*)mibptr;
      libGlobalParam.repititionCnt      = fanTrayDiagReq->args[0];
      libGlobalParam.suppress      = fanTrayDiagReq->args[2];
      paramBits = paramKeySet[fanTrayDiagReq->fanTrayTestType][fanTrayDiagReq->fanTrayTestId].paramBits;

      diagnosticRequest.frameID = fanTrayDiagReq->chassisFrameId; 
      if(fanTrayDiagReq->fanTrayId == FAN_TRAY_NORTH)
      {
	  diagnosticRequest.slotID  = 1;
      }
      else if(fanTrayDiagReq->fanTrayId == FAN_TRAY_SOUTH)
      {
	  diagnosticRequest.slotID  = 2;
      }
      else
      {
	  LOG_PRINT(CRITICAL,"Invalid FanTrayId recv from CFG");
      }
      diagnosticRequest.testRef = fanTrayDiagReq->testReference;
      diagnosticRequest.testType= fanTrayDiagReq->fanTrayTestType;
      diagnosticRequest.testID = fanTrayDiagReq->fanTrayTestId;
      diagnosticRequest.repititions = 0;
      diagnosticRequest.action = fanTrayDiagReq->action;
      diagnosticRequest.intr = fanTrayDiagReq->args[1];
      diagnosticRequest.sup  = fanTrayDiagReq->args[2];
      for(i=0, t=0; t < MAX_ARGS; t++ )
      {
        if(((paramBits >> t) & 0x01))
        {
          diagnosticRequest.args[i] = fanTrayDiagReq->args[t];
	  LOG_PRINT(CRITICAL,"args[%d]=%d ",i,diagnosticRequest.args[i]);
          i++;
        }
      }
      diagnosticRequest.numArgs  = i;//iccDiagReq->numArg;
      addDiagReqParm(&diagnosticRequest);
      break;

    case OAMS_OBJTYPE_OBM :
      obmDiagReq = (ObmDiagReq*)mibptr; //IccDiagReq
      libGlobalParam.repititionCnt      = obmDiagReq->args[8];  
      libGlobalParam.suppress      = obmDiagReq->args[10];  
      paramBits = paramKeySet[obmDiagReq->obmTestType][obmDiagReq->obmTestId].paramBits;

      diagnosticRequest.frameID = obmDiagReq->chassisFrameId; 
      diagnosticRequest.slotID  = obmDiagReq->slotId;
      diagnosticRequest.testRef = obmDiagReq->testReference;
      diagnosticRequest.testType= obmDiagReq->obmTestType;
      diagnosticRequest.testID = obmDiagReq->obmTestId;
      diagnosticRequest.repititions = 0;
      diagnosticRequest.action = obmDiagReq->action;
      diagnosticRequest.intr = obmDiagReq->args[9];
      diagnosticRequest.sup  = obmDiagReq->args[10];
      for(i=0, t=0; t < MAX_ARGS; t++ )
      {
        if(((paramBits >> t) & 0x01))
        {
          diagnosticRequest.args[i] = obmDiagReq->args[t];
	  LOG_PRINT(CRITICAL,"args[%d]=%d ",i,diagnosticRequest.args[i]);
          i++;
        }
      }
      diagnosticRequest.numArgs  = i;//obmDiagReq->numArg;
      addDiagReqParm(&diagnosticRequest);
      break;

    case OAMS_OBJTYPE_OBF :
      obfDiagReq = (ObfDiagReq*)mibptr; //IccDiagReq
      libGlobalParam.repititionCnt      = obfDiagReq->args[8];  
      libGlobalParam.suppress      = obfDiagReq->args[10];  
      paramBits = paramKeySet[obfDiagReq->obfTestType][obfDiagReq->obfTestId].paramBits;

      diagnosticRequest.frameID = obfDiagReq->chassisFrameId; 
      diagnosticRequest.slotID  = obfDiagReq->slotId;
      diagnosticRequest.testRef = obfDiagReq->testReference;
      diagnosticRequest.testType= obfDiagReq->obfTestType;
      diagnosticRequest.testID = obfDiagReq->obfTestId;
      diagnosticRequest.repititions = 0;
      diagnosticRequest.action = obfDiagReq->action;
      diagnosticRequest.intr = obfDiagReq->args[9];
      diagnosticRequest.sup  = obfDiagReq->args[10];
      for(i=0, t=0; t < MAX_ARGS; t++ )
      {
        if(((paramBits >> t) & 0x01))
        {
          diagnosticRequest.args[i] = obfDiagReq->args[t];
	  LOG_PRINT(CRITICAL,"args[%d]=%d ",i,diagnosticRequest.args[i]);
          i++;
        }
      }
      diagnosticRequest.numArgs  = i;//obfDiagReq->numArg;
      addDiagReqParm(&diagnosticRequest);
      break;

    default : 
      LOG_PRINT(CRITICAL,"Test case fail wrong apiId 'object type'");
        *respLen = 0;
      freeLibDiagPtr((void *)buff);
      return NULL;
  }
  memcpy(buff, &diagnosticRequest, sizeof(sDiagnosticRequest));
  //LOG_PRINT(CRITICAL,"testType[%d], testID[%d], numArgs[%d]",diagnosticRequest.testType,diagnosticRequest.testID,diagnosticRequest.numArgs);
  return buff;
}

sDiagnosticTestResult* parseBpmDiagResp(void *BpmRespPtr, I_U32 action)
{
  I_U8 testResult = TEST_COMPLETE;
  sDiagnosticTestResult *diagnosticTestResult;

  
  if(BpmRespPtr == NULL)
  {
      LOG_PRINT(CRITICAL,"parseBpmDiagResp: BpmRespPtr NULL");
      return NULL;
  }

  if((diagnosticTestResult = (sDiagnosticTestResult*)malloc(sizeof(sDiagnosticTestResult))) == NULL)
  {
      LOG_PRINT(CRITICAL,"parseBpmDiagResp: malloc() sDiagnosticTestResult Failed");
      return NULL;
  }

  diagnosticTestResult->testType =  ((sDiagnosticResult*)BpmRespPtr)->testType ;
  diagnosticTestResult->testID =  ((sDiagnosticResult*)BpmRespPtr)->testID ;
  diagnosticTestResult->frameID =  ((sDiagnosticResult*)BpmRespPtr)->frameID ;
  diagnosticTestResult->testRef =  ((sDiagnosticResult*)BpmRespPtr)->testRef ;

  /* Convert BPM SlotID PSU(E,F) to CFG(1,2) */
  if(((sDiagnosticResult*)BpmRespPtr)->slotID == PSU0)
  {
      diagnosticTestResult->slotID =  1 ;
  }
  else if(((sDiagnosticResult*)BpmRespPtr)->slotID == PSU1)
  {
      diagnosticTestResult->slotID =  2 ;
  }
  else
  {
      diagnosticTestResult->slotID =  ((sDiagnosticResult*)BpmRespPtr)->slotID ;
  }

  /* Extract ApiId from BpmRespPtr in case user call parse without form */
  if((((sDiagnosticResult*)BpmRespPtr)->testType >= E_ICC_GEN) &&
      (((sDiagnosticResult*)BpmRespPtr)->testType <= E_ICC_TSI))
  {
      libGlobalParam.ApiId      = OAMS_OBJTYPE_ICC;  
  }
  else if((((sDiagnosticResult*)BpmRespPtr)->testType >= E_EIC_FRAMER) &&
	        (((sDiagnosticResult*)BpmRespPtr)->testType <= E_EIC_CPLD))
  {
      libGlobalParam.ApiId      = OAMS_OBJTYPE_EIC;  
  }
  else if(((sDiagnosticResult*)BpmRespPtr)->testType == E_PSU_TEST)
  {
      libGlobalParam.ApiId      = OAMS_OBJTYPE_PSU;  
  }
  else if(((sDiagnosticResult*)BpmRespPtr)->testType == E_FAN_TEST)
  {
      libGlobalParam.ApiId      = OAMS_OBJTYPE_FANTRAY;  
  }
  else if((((sDiagnosticResult*)BpmRespPtr)->testType >= E_OBM_GEN) &&
      (((sDiagnosticResult*)BpmRespPtr)->testType <= E_OBM_FAN))
  {
      libGlobalParam.ApiId      = OAMS_OBJTYPE_OBM;  
  }
  else if(((sDiagnosticResult*)BpmRespPtr)->testType == E_OBF)
  {
      libGlobalParam.ApiId      = OAMS_OBJTYPE_OBF;  
  }
  else
  {
      LOG_PRINT(CRITICAL,"parseBpmDiagResp: Invalid TestType");
      freeLibDiagPtr((void *)diagnosticTestResult);
      return NULL;
  }

  if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
  {
    libGlobalParam.errCode = ((sDiagnosticResult*)BpmRespPtr)->errCode;
  }

  if(((sDiagnosticResult*)BpmRespPtr)->testResult == TEST_CANCELED)
  {
    diagnosticTestResult->testResult =  DIAG_CMD_CANCEL;
    testResult = TEST_CANCEL;
  }
  else if(((sDiagnosticResult*)BpmRespPtr)->testResult == TEST_ABORTED)
  {
    diagnosticTestResult->testResult =  DIAG_CMD_ABORTED;
    testResult = TEST_ABORT;
  }
  else if(libGlobalParam.fileAction == DIAG_FILE_APPEND)
  {
    diagnosticTestResult->testResult =  DIAG_CMD_AWAITED;
  }
  else 
  {
    diagnosticTestResult->testResult =  DIAG_CMD_COMPLETE;
  }

  strcpy((char *)diagnosticTestResult->testReportPath, (char *)libGlobalParam.filePath);
  /* Update Test Details in File */
  if(doFileOperation(BpmRespPtr, testResult, action) == 1)
  {
    strcpy((char *)diagnosticTestResult->testReportFileName, (char *)libGlobalParam.fileName); 

    if((diagnosticTestResult->testResult == DIAG_CMD_CANCEL) ||
	    (diagnosticTestResult->testResult == DIAG_CMD_ABORTED) ||
	    (action == E_ACTION_DIAG_TEST_CANCEL))
    {
	gTestRunning = 0;
	t_start = t_end = 0;
	strcpy((char *)libGlobalParam.fileName, "NULL");
	libGlobalParam.errCode = 0;
    }
    else if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
    {
      /* Get current time and calculate and update the total Test Execution time in Report File */
      gTestRunning = 0;
      t_end = time(NULL);
      LOG_PRINT(CRITICAL,"t_end after read[%ld] t_start[%ld]",(long)t_end,(long)t_start);
      libGlobalParam.duration = (long)t_end - (long)t_start;
      t_start = t_end = 0;
      if(libGlobalParam.duration == 0)
      {
        /* If duration is less than 1 sec then set it as 1 */
        libGlobalParam.duration = 1;
      }
      /* If any of the repetition is Fail then make Summary Result as Fail */
      doFileResultManipulation(diagnosticTestResult->slotID, diagnosticTestResult->frameID);
      strcpy((char *)libGlobalParam.fileName, "NULL");
      libGlobalParam.errCode = 0;
    }
    return diagnosticTestResult; /* ptr */
  }
  else
  {
    freeLibDiagPtr((void *)diagnosticTestResult);
    return NULL;
  }
}

void freeLibDiagPtr(void *ptr)
{
  if(ptr != NULL)
  {
    free(ptr);
  }
  return;
}

/*
 * Function to add Parameters not supplied by MIB but required by BPM,
 * this function will add those parameters towards last args[] and 
 * set default Hard coded values for those parameters 
 */
void addDiagReqParm(sDiagnosticRequest *diagnosticRequest)
{
    I_U32 temp = 0;
    /* Add size args in E_ICC_CP_RAM */
    if(diagnosticRequest->testType == E_ICC_CP_RAM)
    {
	if(diagnosticRequest->testID == TEST_ID_ICC_CP_RAM_ALL)
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = DATA_PATTERN;
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
	else if((diagnosticRequest->testID == TEST_ID_ICC_CP_RAM_2) || 
		(diagnosticRequest->testID == TEST_ID_ICC_CP_RAM_3) || 
		(diagnosticRequest->testID == TEST_ID_ICC_CP_RAM_4))
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
    }
    /* Add size args in E_ICC_CP_FLASHDISK */
    if(diagnosticRequest->testType == E_ICC_CP_FLASHDISK)
    {
	if(diagnosticRequest->testID == TEST_ID_ICC_CP_FD_ALL)
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_PATTERN;
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
	else if((diagnosticRequest->testID == TEST_ID_ICC_CP_FD_2) || 
		(diagnosticRequest->testID == TEST_ID_ICC_CP_FD_3))
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
    }
    /* Add Eth portId args in E_ICC_PP_ETH */
    if(diagnosticRequest->testType == E_ICC_PP_ETH)
    {
	if(diagnosticRequest->testID == TEST_ID_ICC_PP_ETH_ALL)
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = PORTID_ALL;
	}
    }
    /* Add size args in E_ICC_PP_RAM*/
    if(diagnosticRequest->testType == E_ICC_PP_RAM)
    {
	if(diagnosticRequest->testID == TEST_ID_ICC_PP_RAM_ALL)
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = DATA_PATTERN;
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
	else if((diagnosticRequest->testID == TEST_ID_ICC_PP_RAM_2) || 
		(diagnosticRequest->testID == TEST_ID_ICC_PP_RAM_3) || 
		(diagnosticRequest->testID == TEST_ID_ICC_PP_RAM_4))
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
    }
    /* Add size args in E_ICC_PP_FLASHDISK */
    if(diagnosticRequest->testType == E_ICC_PP_FLASHDISK)
    {
	if(diagnosticRequest->testID == TEST_ID_ICC_PP_FD_ALL) 
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_PATTERN;
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
	else if((diagnosticRequest->testID == TEST_ID_ICC_PP_FD_2) || 
		(diagnosticRequest->testID == TEST_ID_ICC_PP_FD_3))
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
    }
    /* Add portId args in E_ICC_I2C */
    if(diagnosticRequest->testType == E_ICC_I2C)
    {
	if(diagnosticRequest->testID == TEST_ID_ICC_I2C_ALL)
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = ICC_I2C_REG;
	}
    }
    /* Add chanNum args in E_ICC_DSP */
    if(diagnosticRequest->testType == E_ICC_DSP)
    {
	if((diagnosticRequest->testID == TEST_ID_ICC_DSP_ALL) || 
		(diagnosticRequest->testID == TEST_ID_ICC_DSP_4))
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = DSP_CHAN_NUM; //ChanNum
	}
    }
    /* Map OMC TSI Stream Id to BPM TSI StreamId for E_ICC_TSI */
    if(diagnosticRequest->testType == E_ICC_TSI)
    {
	if(diagnosticRequest->testID == TEST_ID_ICC_TSI_ALL)
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = ICC_DSP_STRM_ID; //StreamId
	}
	if((diagnosticRequest->testID >= TEST_ID_ICC_TSI_2) && 
		(diagnosticRequest->testID <= TEST_ID_ICC_TSI_5))
	{
	    switch(diagnosticRequest->args[diagnosticRequest->numArgs - 1])
	    {
		case STREAM_ID_ICC_DSP:
		    diagnosticRequest->args[diagnosticRequest->numArgs - 1] = ICC_DSP_STRM_ID;
		    LOG_PRINT(CRITICAL,"TSI Stream Mapping %d -> %d",STREAM_ID_ICC_DSP,diagnosticRequest->args[diagnosticRequest->numArgs - 1]);
		    break;
		case STREAM_ID_ICC_PP:
		    diagnosticRequest->args[diagnosticRequest->numArgs - 1] = ICC_PP_STRM_ID;
		    LOG_PRINT(CRITICAL,"TSI Stream Mapping %d -> %d",STREAM_ID_ICC_PP,diagnosticRequest->args[diagnosticRequest->numArgs - 1]);
		    break;
		case STREAM_ID_ICC_FRAMER:
		    diagnosticRequest->args[diagnosticRequest->numArgs - 1] = ICC_FRAMER_STRM_ID;
		    LOG_PRINT(CRITICAL,"TSI Stream Mapping %d -> %d",STREAM_ID_ICC_FRAMER,diagnosticRequest->args[diagnosticRequest->numArgs - 1]);
		    break;
		case STREAM_ID_MATE_TSI:
		    diagnosticRequest->args[diagnosticRequest->numArgs - 1] = ICC_PP_MATE_PP_STRM_ID;
		    LOG_PRINT(CRITICAL,"TSI Stream Mapping %d -> %d",STREAM_ID_MATE_TSI,diagnosticRequest->args[diagnosticRequest->numArgs - 1]);
		    break;
		default:
		    LOG_PRINT(CRITICAL,"Invalid TSI StreamID[%d] recv from CFG",diagnosticRequest->args[diagnosticRequest->numArgs - 1]);
		    break;
	    }
	}
    }
    /* Add dspId args in E_EIC_DSP */
    if(diagnosticRequest->testType == E_EIC_DSP)
    {
	if(diagnosticRequest->testID == TEST_ID_EIC_DSP_ALL)
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = EIC_DSP0;//dspId
	}
	if((diagnosticRequest->testID >= TEST_ID_EIC_DSP_1) &&
	    (diagnosticRequest->testID <= TEST_ID_EIC_DSP_4))
	{
	    switch(diagnosticRequest->args[diagnosticRequest->numArgs -1])
	    {
		case EIC0_DSP0:
		case EIC1_DSP0:
		    LOG_PRINT(CRITICAL,"DSP Id Mapping %d -> %d",diagnosticRequest->args[diagnosticRequest->numArgs - 1],EIC_DSP0);
		    diagnosticRequest->args[diagnosticRequest->numArgs - 1] = EIC_DSP0;
		    break;
		case EIC0_DSP1:
		case EIC1_DSP1:
		    LOG_PRINT(CRITICAL,"DSP Id Mapping %d -> %d",diagnosticRequest->args[diagnosticRequest->numArgs - 1],EIC_DSP1);
		    diagnosticRequest->args[diagnosticRequest->numArgs - 1] = EIC_DSP1;
		    break;
		default:
		    LOG_PRINT(CRITICAL,"Invalid DSP Id[%d] from CFG",diagnosticRequest->args[diagnosticRequest->numArgs - 1]);
		    break;
	    }
	}
    }
    /* Add portNUm args in E_EIC_SW_ETH */
    if(diagnosticRequest->testType == E_EIC_SW_ETH)
    {
	if(diagnosticRequest->testID == TEST_ID_EIC_SW_ETH_3)
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = EIC_EXT_IFC_PORT;// portNum
	}
    }
    /* Add FanSpeed args in E_FAN_TEST*/
    if(diagnosticRequest->testType == E_FAN_TEST)
    {
	if((diagnosticRequest->testID == TEST_ID_FAN_ALL) || (diagnosticRequest->testID == TEST_ID_FAN_1))
	{
     //diagnosticRequest->args[diagnosticRequest->numArgs++] = 2;
    
    /* Fan Speed Set to Maximum at 4385 RPM */
    diagnosticRequest->args[diagnosticRequest->numArgs++] = DUTY_CYCLE_93P3;
	}
    }
    /* NOTE:- Interchange the chanNum and ChanType to map the sequence between OAM and BPM */
    if(diagnosticRequest->testType == E_ICC_MCC)
    {
	temp = diagnosticRequest->args[0];
	diagnosticRequest->args[0] = diagnosticRequest->args[1];
	diagnosticRequest->args[1] = temp;
    }

    /* Add size args in E_OBM_CP_RAM */
    if(diagnosticRequest->testType == E_OBM_RAM)
    {
	if(diagnosticRequest->testID == TEST_ID_OBM_RAM_ALL)
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = DATA_PATTERN;
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
	else if((diagnosticRequest->testID == TEST_ID_OBM_RAM_2) || 
		(diagnosticRequest->testID == TEST_ID_OBM_RAM_3) || 
		(diagnosticRequest->testID == TEST_ID_OBM_RAM_4))
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
    }
    /* Add size args in E_OBM_FLASHDISK */
    if(diagnosticRequest->testType == E_OBM_FLASHDISK)
    {
	if(diagnosticRequest->testID == TEST_ID_OBM_FD_ALL)
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_PATTERN;
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
	else if((diagnosticRequest->testID == TEST_ID_OBM_FD_2) || 
		(diagnosticRequest->testID == TEST_ID_OBM_FD_3))
	{
	    diagnosticRequest->args[diagnosticRequest->numArgs++] = FLASH_DATA_SIZE;
	}
    }
    /* Add FanSpeed args in E_FAN_TEST*/
    if(diagnosticRequest->testType == E_OBM_FAN)
    {
	if((diagnosticRequest->testID == TEST_ID_OBM_FAN_ALL) || (diagnosticRequest->testID == TEST_ID_OBM_FAN_1))
	{
     //diagnosticRequest->args[diagnosticRequest->numArgs++] = 2;
    
    /* Fan Speed Set to Maximum at 4385 RPM */
    //diagnosticRequest->args[diagnosticRequest->numArgs++] = DUTY_CYCLE_93P3;
    //Changed for 1U Diagnostics
    diagnosticRequest->args[diagnosticRequest->numArgs++] = DUTY_CYCLE_100;
    //Changed for 1U Diagnostics
	}
    }

    return;
}

