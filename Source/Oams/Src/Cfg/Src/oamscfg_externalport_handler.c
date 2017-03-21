/***********************************File Header ***************************
File Name        : oamscfg_externalport_handler.c
Purpose          : This file contains CFG External Alarm implementation 
Project          : BSC OAM
Subsystem        : Oams
Author           : Gaurav Jain
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h>


/********************************* Function  Header********************************
Function Name:       setExternalInputPortConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             To handle External Input Port Configuration 
                     from OMC.
Other Note:
 ************************************************************************************/
void setExternalInputPortConfigTableHandler()
{
   ExternalInputPortConfigTableApi *receivedMsgPtr = (ExternalInputPortConfigTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));  
   ExternalInputPortConfigTableApi *extInputPortConfigTableApiPtr=NULL;
   sCmMsg* receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   I_PVoid tmpPtr = receivedCmMsgPtr;
   I_S32 dbStatus;
   I_U32 res=0,retStatus;
   ExternalInputPortConfigTableIndices extInputPortConfigIndex;
   I_Bool flagParamChange;
   ExternalInputPortStatusTableApi externalInputPortStatusTable;
   /*Mantis 24748 Start*/
   ActiveAlarmListTableIndices activeAlarmTableIndex;
   I_U32 raiseAlarmId,clearAlarmId;
   /*Mantis 24748 End*/

   LOG_PRINT(INFO,"Entering func setExternalInputPortConfigTableHandler");
   LOG_PRINT(LOG_INFO,"setExternalInputPortConfigTableHandler:extInputPortId %d extAlarmText %s extAlarmSeverity %d \
       extInputPortAlarmCondition %d assignedState %d",receivedMsgPtr->extInputPortId,
       receivedMsgPtr->extAlarmText,receivedMsgPtr->extAlarmSeverity,
       receivedMsgPtr->extInputPortAlarmCondition,receivedMsgPtr->assignedState);

  extInputPortConfigIndex.extInputPortId=receivedMsgPtr->extInputPortId;
  dbStatus = getExternalInputPortConfigTable(&extInputPortConfigIndex, &extInputPortConfigTableApiPtr);

  /* Case: Addition of New ExternalInputPortConfig in Table */
  if (DBLIB_SUCCESS != dbStatus)
  {
    LOG_PRINT(DEBUG,"setExternalInputPortConfigTableHandler:Addition of a new ExternalInputPort");
    retStatus=extInputPortConfigTableRangeCheck(receivedMsgPtr);
    if(retStatus!=CM_SUCCESS)
    {
      LOG_PRINT(MAJOR,"setExternalInputPortConfigTableHandler:range Check Failed");
      cfgSendNackToCm(retStatus);
      return;
    }


    dbStatus=insertExternalInputPortConfigTable(receivedMsgPtr);
    if(CLIB_SUCCESS != dbStatus)
    {
      LOG_PRINT(LOG_INFO,"setExternalInputPortConfigTableHandler:insertExternalInputPortConfigTable Failed, sending Nack");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      return;
    }
    externalInputPortStatusTable.extInputPortId=receivedMsgPtr->extInputPortId;
    externalInputPortStatusTable.extInputPortState=EXT_INPUT_PORT_STATE_UNDEFINED;
    dbStatus=insertExternalInputPortStatusTable(&externalInputPortStatusTable);
    if(CLIB_SUCCESS != dbStatus)
    {
      LOG_PRINT(LOG_INFO,"setExternalInputPortConfigTableHandler:insertExternalInputPortStatusTable Failed");
    }
    else
    {
      LOG_PRINT(LOG_INFO,"setExternalInputPortConfigTableHandler:insertExternalInputPortStatusTable Success");
    }


    if(receivedMsgPtr->assignedState == EXT_PORT_ASSIGN)
    {
      if((res = sendExternalPortConfigReqToBpm(EXT_INPUT_PORT,receivedMsgPtr->extInputPortId,
              receivedMsgPtr->assignedState )) == CFG_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"setExternalInputPortConfigTableHandler:External Input Config reported to Platform");
      } 
      else
      {
        LOG_PRINT(LOG_MAJOR,"setExternalInputPortConfigTableHandler:External Input Config could not be reported to Platform");
      }
    }
    cfgSendAckToCm();
  }
  else
  {
      /* Modifying ExternalInputPortConfig Table */
         LOG_PRINT(LOG_INFO,"setExternalInputPortConfigTableHandler: Modifying \
             externalInputPortConfig Table. Calling compare");
         flagParamChange = compareRcvdMsgAndDbEntry((void*) receivedMsgPtr,
               (void*) extInputPortConfigTableApiPtr,
               sizeof(ExternalInputPortConfigTableApi));

         if (flagParamChange)
         {
           retStatus=extInputPortConfigTableRangeCheck(receivedMsgPtr);
           if (CM_SUCCESS != retStatus)
           {
             LOG_PRINT(MAJOR,"setExternalInputPortConfigTableHandler:range Check Failed,Sending Nack");
             cfgSendNackToCm(retStatus);
             free(extInputPortConfigTableApiPtr);
             return;
           }

           dbStatus=updateExternalInputPortConfigTable(receivedMsgPtr);
           if(CLIB_SUCCESS != dbStatus)
           {
             LOG_PRINT(MAJOR,"setExternalInputPortConfigTableHandler:updateExternalInputPortConfigTable Failed,Sending Nack");
             cfgSendNackToCm(retStatus);
             free(extInputPortConfigTableApiPtr);
             return;
           }

           if(receivedMsgPtr->assignedState != extInputPortConfigTableApiPtr->assignedState)
           {
             LOG_PRINT(INFO,"setExternalInputPortConfigTableHandler:Port Assignment State Change , needs to be reported to Platform");
             if((res = sendExternalPortConfigReqToBpm(EXT_INPUT_PORT,receivedMsgPtr->extInputPortId,
                     receivedMsgPtr->assignedState)) == CFG_SUCCESS)
             {
               LOG_PRINT(LOG_INFO,"setExternalInputPortConfigTableHandler:External Input Config \
                   reported to Platform");
             } 
             else
             {
               LOG_PRINT(LOG_MAJOR,"setExternalInputPortConfigTableHandler:External Input Config \
                   could not be reported to Platform");
             }
             /*Mantis 24748 Start*/
             if(receivedMsgPtr->assignedState == EXT_PORT_FREE)
             {
             DELETE_EXTERNAL_ACTIVE_ALARM(receivedMsgPtr->extInputPortId)
             }
             /*Mantis 24748 End*/
           }
           cfgSendAckToCm();
           free(extInputPortConfigTableApiPtr);
           
         } 
         else
         {
            LOG_PRINT(LOG_INFO,"setExternalInputConfigTableHandler: Same parameter values in DB, sending Ack");
            free(extInputPortConfigTableApiPtr);
            cfgSendAckToCm();
            return;    
         } 
    
  }
    


   LOG_PRINT(INFO,"Exiting func setExternalInputPortConfigTableHandler");
}

/********************************* Function  Header********************************
Function Name:       sendAllValidExtInputAssignmentToBPM
Parameters:          None 
Return type:         void
Purpose:             sends all external port configuration to platform 
Other Note:
 ************************************************************************************/
I_U32 sendAllValidExtInputAssignmentToBPM()
{
  I_S32 dbStatus;
  I_U32 res=0;
  I_U32 rowsCount = 0,ctr=0;
  I_U16 outSize = 0;
  ExternalInputPortConfigTableApi *externalInputPortConfigTableApiPtr=PNULL,
                                  *tmpExternalInputPortConfigTableApiPtr=PNULL;
  ExternalInputPortStatusTableApi externalInputPortStatusTable;

  LOG_PRINT(LOG_DEBUG,"Entering Function sendAllValidExtInputAssignmentToBPM");
  dbStatus=getallExternalInputPortConfigTable(&externalInputPortConfigTableApiPtr,&rowsCount,&outSize);
  if(CLIB_SUCCESS == dbStatus)
  {
    for(ctr=0;ctr<rowsCount;ctr++)
    {
      tmpExternalInputPortConfigTableApiPtr=(ExternalInputPortConfigTableApi*)((I_U8*)externalInputPortConfigTableApiPtr + ctr*outSize);
   LOG_PRINT(LOG_INFO,"sendAllValidExtInputAssignmentToBPM:Processing for extInputPortId %d \
       extInputPortAlarmCondition %d assignedState %d",tmpExternalInputPortConfigTableApiPtr->extInputPortId,
       tmpExternalInputPortConfigTableApiPtr->extInputPortAlarmCondition,tmpExternalInputPortConfigTableApiPtr->assignedState);

      if(tmpExternalInputPortConfigTableApiPtr->assignedState == EXT_PORT_ASSIGN)
      {
        if((res = sendExternalPortConfigReqToBpm(EXT_INPUT_PORT,
                tmpExternalInputPortConfigTableApiPtr->extInputPortId,
                tmpExternalInputPortConfigTableApiPtr->assignedState )) == CFG_SUCCESS)
        {
          LOG_PRINT(LOG_INFO,"sendAllValidExtInputAssignmentToBPM:External Input Config reported to Platform");
        } 
        else
        {
          LOG_PRINT(LOG_MAJOR,"sendAllValidExtInputAssignmentToBPM:External Input Config could not be reported to Platform");
        }
      }
      externalInputPortStatusTable.extInputPortId=tmpExternalInputPortConfigTableApiPtr->extInputPortId;
      externalInputPortStatusTable.extInputPortState=EXT_INPUT_PORT_STATE_UNDEFINED;
      dbStatus=insertExternalInputPortStatusTable(&externalInputPortStatusTable);

    }
    free(externalInputPortConfigTableApiPtr);
  }
 
 LOG_PRINT(LOG_DEBUG,"Exiting Function sendAllValidExtInputAssignmentToBPM");

 return CFG_SUCCESS; 
}

/********************************* Function  Header********************************
Function Name:       extInputPortConfigTableRangeCheck
Parameters:          Pointer to ExternalInputPortConfigTableApi
Return type:         error or CM_SUCCESS 
Purpose:             validation of externalInputPortConfig received 
                     from OMC.
Other Note:
 ************************************************************************************/
I_U32 extInputPortConfigTableRangeCheck(ExternalInputPortConfigTableApi* extInputPortConfigTableApiPtr)
{

  LOG_PRINT(LOG_DEBUG,"Entering Function extInputPortConfigTableRangeCheck");
  if((extInputPortConfigTableApiPtr->extInputPortId<EXT_INPUT_PORT1) || 
      (extInputPortConfigTableApiPtr->extInputPortId>EXT_INPUT_PORT4))
  {
    LOG_PRINT(CRITICAL,"extInputPortConfigTableRangeCheck:ExtInputPortId should be one \
        of (%d, %d, %d, %d)",EXT_INPUT_PORT1,EXT_INPUT_PORT2,EXT_INPUT_PORT3,
        EXT_INPUT_PORT4);
    return CM_ERR_EXT_INPUT_PORT_INVALID; 
  }

  if(strlen(extInputPortConfigTableApiPtr->extAlarmText)==0)
  {
    LOG_PRINT(CRITICAL,"extInputPortConfigTableRangeCheck:Alarm Text cannot be null");
    return CM_ERR_EXT_ALARM_TEXT_INVALID; 
  }

  if((extInputPortConfigTableApiPtr->extAlarmSeverity<EXT_SEVERITY_INFORMATION) || 
      (extInputPortConfigTableApiPtr->extAlarmSeverity>EXT_SEVERITY_CRITICAL))
  {
    LOG_PRINT(CRITICAL,"extInputPortConfigTableRangeCheck:ExtAlarmSeverity should be one \
        of (%d, %d, %d, %d, %d)",EXT_SEVERITY_INFORMATION,EXT_SEVERITY_WARNING,EXT_SEVERITY_MINOR,
        EXT_SEVERITY_MAJOR,EXT_SEVERITY_CRITICAL);
    return CM_ERR_EXT_ALARM_SEVERITY_INVALID; 
  }

  if(extInputPortConfigTableApiPtr->extInputPortAlarmCondition>EXT_INPUT_PORT_STATE_CLOSE)
  {
    LOG_PRINT(CRITICAL,"extInputPortConfigTableRangeCheck:ExtInputPortAlarmCondition should \
        be one of (%d, %d)", EXT_INPUT_PORT_STATE_OPEN,EXT_INPUT_PORT_STATE_CLOSE);
    return CM_ERR_EXT_INPUT_PORT_ALARM_CONDITION_INVALID; 
  }
  
  if(extInputPortConfigTableApiPtr->assignedState>EXT_PORT_ASSIGN)
  {
    LOG_PRINT(CRITICAL,"extInputPortConfigTableRangeCheck:Assigned State should be one \
        of (%d, %d)", EXT_PORT_FREE,EXT_PORT_ASSIGN);
    return CM_ERR_EXT_ASSIGNED_STATE_INVALID; 
  }

  LOG_PRINT(LOG_DEBUG,"Exiting Function extInputPortConfigTableRangeCheck");
  return CM_SUCCESS;
}

/********************************* Function  Header********************************
Function Name:       setExternalOutputPortConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             To handle External Output Port Configuration 
                     from OMC.
Other Note:
 ************************************************************************************/
void setExternalOutputPortConfigTableHandler()
{
   ExternalOutputPortConfigTableApi *receivedMsgPtr = (ExternalOutputPortConfigTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));  
   ExternalOutputPortConfigTableApi *extOutputPortConfigTableApiPtr=NULL;
   sCmMsg* receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   I_PVoid tmpPtr = receivedCmMsgPtr;
   I_S32 dbStatus;
   I_U32 res,retStatus;
   ExternalOutputPortConfigTableIndices extOutputPortConfigIndex;
   I_Bool flagParamChange;
   
   LOG_PRINT(INFO,"Entering func setExternalOutputPortConfigTableHandler");
   LOG_PRINT(LOG_INFO,"setExternalOutputPortConfigTableHandler:extOutputPortId %d \
       extAlarmText %s extAlarmSeverity %d extOutputPortStateChange %d \
       assignedState %d",receivedMsgPtr->extOutputPortId,
       receivedMsgPtr->extEventText,receivedMsgPtr->extEventSeverity,
       receivedMsgPtr->extOutputPortStateChange,receivedMsgPtr->assignedState);

  extOutputPortConfigIndex.extOutputPortId=receivedMsgPtr->extOutputPortId;
  dbStatus = getExternalOutputPortConfigTable(&extOutputPortConfigIndex, &extOutputPortConfigTableApiPtr);

  /* Case: Addition of New ExternalOutputPortConfig in Table */
  if (DBLIB_SUCCESS != dbStatus)
  {
    LOG_PRINT(DEBUG,"setExternalOutputPortConfigTableHandler:Addition of a new ExternalOutputPort");
    retStatus=extOutputPortConfigTableRangeCheck(receivedMsgPtr);
    if(retStatus!=CM_SUCCESS)
    {
      LOG_PRINT(MAJOR,"setExternalOutputPortConfigTableHandler:range Check Failed");
      cfgSendNackToCm(retStatus);
      return;
    }


    dbStatus=insertExternalOutputPortConfigTable(receivedMsgPtr);
    if(CLIB_SUCCESS != dbStatus)
    {
      LOG_PRINT(LOG_INFO,"setExternalOutputPortConfigTableHandler:insertExternalOutputPortConfigTable \
          Failed, sending Nack");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      return;
    }

    if(receivedMsgPtr->assignedState == EXT_PORT_ASSIGN)
    {
      if((res = sendExternalPortConfigReqToBpm(EXT_OUTPUT_PORT,receivedMsgPtr->extOutputPortId,
              receivedMsgPtr->assignedState)) == CFG_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"setExternalOutputPortConfigTableHandler:External Output Config reported to Platform");
        if((res = sendExternalPortStateChangeReqToBpm(receivedMsgPtr->extOutputPortId,
                receivedMsgPtr->extOutputPortStateChange))!=CFG_SUCCESS)
        {
          cfgSendNackToCm(CM_ERR_EXT_PORT_STATE_CHANGE_NOT_REPORTED_BPM);
          LOG_PRINT(LOG_INFO,"setExternalOutputPortConfigTableHandler:External Output Port State Change not reported to Platform");
        }
        else
        {
          cfgSendAckToCm();
          LOG_PRINT(LOG_INFO,"External Output Port State Change reported to Platform");
          sendExtOutputEventToOMC(receivedMsgPtr->extOutputPortId,
              receivedMsgPtr->extOutputPortStateChange,receivedMsgPtr->extEventText,receivedMsgPtr->extEventSeverity);
          return;
        }
      } 
      else
      {
        LOG_PRINT(LOG_MAJOR,"External Output Config could not be reported to Platform");
      }
    }
    else
    {
      cfgSendAckToCm();
    }
  }
  else
  {
      /* Modifying ExternalOutputPortConfig Table */
         LOG_PRINT(LOG_INFO,"setExternalOutputPortConfigTableHandler: Modifying externalOutputPortConfig Table. Calling compare");
         flagParamChange = compareRcvdMsgAndDbEntry((void*) receivedMsgPtr,
               (void*) extOutputPortConfigTableApiPtr,
               sizeof(ExternalOutputPortConfigTableApi));

         if (flagParamChange)
         {
           retStatus=extOutputPortConfigTableRangeCheck(receivedMsgPtr);
           if (CM_SUCCESS != retStatus)
           {
             LOG_PRINT(MAJOR,"setExternalOutputPortConfigTableHandler:range Check Failed,Sending Nack");
             cfgSendNackToCm(retStatus);
             free(extOutputPortConfigTableApiPtr);
             return;
           }

           dbStatus=updateExternalOutputPortConfigTable(receivedMsgPtr);
           if(CLIB_SUCCESS != dbStatus)
           {
             LOG_PRINT(MAJOR,"setExternalOutputPortConfigTableHandler:updateExternalOutputPortConfigTable Failed,Sending Nack");
             cfgSendNackToCm(retStatus);
             free(extOutputPortConfigTableApiPtr);
             return;
           }

           if(receivedMsgPtr->assignedState != extOutputPortConfigTableApiPtr->assignedState)
           {
             if((res = sendExternalPortConfigReqToBpm(EXT_OUTPUT_PORT,receivedMsgPtr->extOutputPortId,
                     receivedMsgPtr->assignedState)) == CFG_SUCCESS)
             {
               LOG_PRINT(LOG_INFO,"setExternalOutputPortConfigTableHandler:External Output Config reported to Platform");

              /*If port is to be assigned , send Turnoff/Turnon to BPM*/ 
               if(receivedMsgPtr->assignedState == EXT_PORT_ASSIGN && 
                   receivedMsgPtr->extOutputPortStateChange == \
                   extOutputPortConfigTableApiPtr->extOutputPortStateChange)
               {
                 if((res = sendExternalPortStateChangeReqToBpm(receivedMsgPtr->extOutputPortId,receivedMsgPtr->extOutputPortStateChange))!=CFG_SUCCESS)
                 {
                   cfgSendNackToCm(CM_ERR_EXT_PORT_STATE_CHANGE_NOT_REPORTED_BPM);
                   LOG_PRINT(LOG_INFO,"setExternalOutputPortConfigTableHandler:External Output Port State Change not reported to Platform");
                 }
                 else
                 {
                   LOG_PRINT(LOG_INFO,"setExternalOutputPortConfigTableHandler:External Output Port State Change reported to Platform");
                   cfgSendAckToCm();
                   sendExtOutputEventToOMC(receivedMsgPtr->extOutputPortId,
                       receivedMsgPtr->extOutputPortStateChange,receivedMsgPtr->extEventText,receivedMsgPtr->extEventSeverity);
                 }
               }
               else
               {
                 /*If assignedState is changed to FREE*/
                 /*Mantis 24798 Start*/
                 cfgSendAckToCm();
                 /*Mantis 24798 End*/
               }
             } 
             else
             {
               LOG_PRINT(LOG_MAJOR,"setExternalOutputPortConfigTableHandler:External Output Config could not be reported to Platform");
             cfgSendNackToCm(CM_ERR_EXT_PORT_NOT_CONFIGURED);
             }
           }
           else if(receivedMsgPtr->assignedState == EXT_PORT_ASSIGN && 
               receivedMsgPtr->extOutputPortStateChange != \
               extOutputPortConfigTableApiPtr->extOutputPortStateChange)
           {
             if((res = sendExternalPortStateChangeReqToBpm(receivedMsgPtr->extOutputPortId,receivedMsgPtr->extOutputPortStateChange))!=CFG_SUCCESS)
             {
               cfgSendNackToCm(CM_ERR_EXT_PORT_STATE_CHANGE_NOT_REPORTED_BPM);
               LOG_PRINT(LOG_INFO,"setExternalOutputPortConfigTableHandler:External Output Port State Change not reported to Platform");
             }
             else
             {
               LOG_PRINT(LOG_INFO,"setExternalOutputPortConfigTableHandler:External Output Port State Change reported to Platform");
               cfgSendAckToCm();
               sendExtOutputEventToOMC(receivedMsgPtr->extOutputPortId,
              receivedMsgPtr->extOutputPortStateChange,receivedMsgPtr->extEventText,receivedMsgPtr->extEventSeverity);
             }
           }
           else
           {
             /*Mantis 24691 Start*/
             /*If portAssignedState has not been changed and only parameters except portStateChange are modified*/
             cfgSendAckToCm();
             /*Mantis 24691 End*/
           }
           free(extOutputPortConfigTableApiPtr);
           
         } 
         else
         {
            LOG_PRINT(LOG_INFO,"setExternalOutputConfigTableHandler: Same parameter values in DB, sending Ack");
            free(extOutputPortConfigTableApiPtr);
            cfgSendAckToCm();
            return;    
         } 
    
  }
    


   LOG_PRINT(INFO,"Exiting func setExternalOutputPortConfigTableHandler");
}

/********************************* Function  Header********************************
Function Name:       extOutputPortConfigTableRangeCheck
Parameters:          Pointer to ExternalOutputPortConfigTableApi
Return type:         void
Purpose:             validation of externalOutputPortConfig received 
                     from OMC.
Other Note:
 ************************************************************************************/
I_U32 extOutputPortConfigTableRangeCheck(ExternalOutputPortConfigTableApi* extOutputPortConfigTableApiPtr)
{

  LOG_PRINT(LOG_DEBUG,"Entering Function extOutputPortConfigTableRangeCheck");
  if((extOutputPortConfigTableApiPtr->extOutputPortId<EXT_OUTPUT_PORT1) || 
      (extOutputPortConfigTableApiPtr->extOutputPortId>EXT_OUTPUT_PORT2))
  {
    LOG_PRINT(CRITICAL,"extOutputPortConfigTableRangeCheck:ExtOutputPortId should be \
        one of (%d, %d)", EXT_OUTPUT_PORT1,EXT_OUTPUT_PORT2);
    return CM_ERR_EXT_OUTPUT_PORT_INVALID; 
  }

  if(strlen(extOutputPortConfigTableApiPtr->extEventText)==0)
  {
    LOG_PRINT(CRITICAL,"extOutputPortConfigTableRangeCheck:Event Text cannot be null");
    return CM_ERR_EXT_EVENT_TEXT_INVALID; 
  }

  if((extOutputPortConfigTableApiPtr->extEventSeverity<EXT_SEVERITY_INFORMATION) || 
      (extOutputPortConfigTableApiPtr->extEventSeverity>EXT_SEVERITY_CRITICAL))
  {
    LOG_PRINT(CRITICAL,"extOutputPortConfigTableRangeCheck:ExtEventSeverity should be \
        one of (%d, %d, %d, %d, %d)", EXT_SEVERITY_INFORMATION,EXT_SEVERITY_WARNING,
        EXT_SEVERITY_MINOR,EXT_SEVERITY_MAJOR,EXT_SEVERITY_CRITICAL);
    return CM_ERR_EXT_EVENT_SEVERITY_INVALID; 
  }

  if(extOutputPortConfigTableApiPtr->extOutputPortStateChange>EXT_OUTPUT_PORT_TURN_ON)
  {
    LOG_PRINT(CRITICAL,"extOutputPortConfigTableRangeCheck:ExtOutputPortStateChange should \
        be one of (%d, %d)",EXT_OUTPUT_PORT_TURN_OFF,EXT_OUTPUT_PORT_TURN_ON);
    return CM_ERR_EXT_OUTPUT_PORT_STATE_CHANGE_INVALID; 
  }
  
  if(extOutputPortConfigTableApiPtr->assignedState>EXT_PORT_ASSIGN)
  {
    LOG_PRINT(CRITICAL,"extOutputPortConfigTableRangeCheck:Assigned State should be one \
        of (%d, %d)", EXT_PORT_FREE,EXT_PORT_ASSIGN);
    return CM_ERR_EXT_ASSIGNED_STATE_INVALID; 
  }

  LOG_PRINT(LOG_DEBUG,"Exiting Function extOutputPortConfigTableRangeCheck");
  return CM_SUCCESS;
}

/********************************* Function  Header********************************
Function Name:       sendAllValidExtOutputAssignmentToBPM
Parameters:          None 
Return type:         void
Purpose:             send port assignment to BPM for all Assigned 
                     External Output Port
Other Note:
 ************************************************************************************/
I_U32 sendAllValidExtOutputAssignmentToBPM()
{
  I_S32 dbStatus;
  I_U32 res=0;
  I_U32 rowsCount = 0,ctr=0;
  I_U16 outSize = 0;
  ExternalOutputPortConfigTableApi *externalOutputPortConfigTableApiPtr=PNULL,
                                  *tmpExternalOutputPortConfigTableApiPtr=PNULL;

  LOG_PRINT(LOG_DEBUG,"Entering Function sendAllValidExtOutputAssignmentToBPM");
  dbStatus=getallExternalOutputPortConfigTable(&externalOutputPortConfigTableApiPtr,&rowsCount,&outSize);
  if(CLIB_SUCCESS == dbStatus)
  {
    for(ctr=0;ctr<rowsCount;ctr++)
    {
      tmpExternalOutputPortConfigTableApiPtr=(ExternalOutputPortConfigTableApi*)((I_U8*)externalOutputPortConfigTableApiPtr + ctr*outSize);
   LOG_PRINT(LOG_INFO,"sendAllValidExtOutputAssignmentToBPM:Processing for extOutputPortId %d \
       assignedState %d",tmpExternalOutputPortConfigTableApiPtr->extOutputPortId,
       tmpExternalOutputPortConfigTableApiPtr->assignedState);

      if(tmpExternalOutputPortConfigTableApiPtr->assignedState == EXT_PORT_ASSIGN)
      {
        if((res = sendExternalPortConfigReqToBpm(EXT_OUTPUT_PORT,
                tmpExternalOutputPortConfigTableApiPtr->extOutputPortId,
                tmpExternalOutputPortConfigTableApiPtr->assignedState )) == CFG_SUCCESS)
        {
          LOG_PRINT(LOG_INFO,"sendAllValidExtOutputAssignmentToBPM:External Output Config reported to Platform");
          /*If port is to be assigned , send Turnoff/Turnon to BPM*/ 
          if(tmpExternalOutputPortConfigTableApiPtr->assignedState == EXT_PORT_ASSIGN) 
          {
            if((res = sendExternalPortStateChangeReqToBpm(tmpExternalOutputPortConfigTableApiPtr->extOutputPortId,tmpExternalOutputPortConfigTableApiPtr->extOutputPortStateChange))!=CFG_SUCCESS)
            {
              LOG_PRINT(LOG_INFO,"sendAllValidExtOutputAssignmentToBPM:External Output Port State Change not reported to Platform");
            }
            else
            {
              LOG_PRINT(LOG_INFO,"sendAllValidExtOutputAssignmentToBPM:External Output Port State Change reported to Platform");
              sendExtOutputEventToOMC(tmpExternalOutputPortConfigTableApiPtr->extOutputPortId,
                  tmpExternalOutputPortConfigTableApiPtr->extOutputPortStateChange,tmpExternalOutputPortConfigTableApiPtr->extEventText,tmpExternalOutputPortConfigTableApiPtr->extEventSeverity);
            }
          }
        } 
        else
        {
          LOG_PRINT(LOG_MAJOR,"sendAllValidExtOutputAssignmentToBPM:External Output Config could not be reported to Platform");
        }

      }/*if (tmpExternalOutputPortConfigTableApiPtr->assignedState==EXT_PORT_ASSIGN)*/

    }/*for */
    free(externalOutputPortConfigTableApiPtr);
  }
 
 LOG_PRINT(LOG_DEBUG,"Exiting Function sendAllValidExtOutputAssignmentToBPM");

 return CFG_SUCCESS; 
}
 
/********************************* Function  Header********************************
Function Name:       sendExternalPortConfigReqToBpm 
Parameters:          external Port Type :EXT_INPUT_PORT/EXT_OUTPUT_PORT
                     external Port Id
                     assignState: EXT_PORT_FREE/EXT_PORT_ASSIGN
Return type:         CFG_SUCCESS on success
                     CFG_FAILURE on failure
Purpose:             send External Port Assignment to BPM via OIL 
Other Note:
 ************************************************************************************/
I_U32 sendExternalPortConfigReqToBpm(I_U8 extPortType,I_U8 extPortId, I_U8 assignState)
{
  OamsCfgOilExtPortAssignmentReq oamsCfgOilextPortAssignReq;

  LOG_PRINT(INFO,"Entering func sendExternalPortConfigReqToBpm");
  oamsCfgOilextPortAssignReq.extPortType=extPortType;
  oamsCfgOilextPortAssignReq.extPortId=extPortId;
  oamsCfgOilextPortAssignReq.extPortAssignState=assignState;


  cfgSendMessage(&oamsCfgOilextPortAssignReq, 
                    sizeof(OamsCfgOilExtPortAssignmentReq), 
                    ENT_OAM_OIL, 
                    OAMS_CFG_OIL_EXT_PORT_ASSIGN_REQ, 
                    0);
  LOG_PRINT(INFO,"Exiting func sendExternalPortConfigReqToBpm");

  return CFG_SUCCESS;
}

/********************************* Function  Header********************************
Function Name:       sendExternalPortStateChangeReqToBpm 
Parameters:          external Port Id:EXT_OUTPUT_PORT1/EXT_OUTPUT_PORT2 
                     extOutputPortStateChange: EXT_OUTPUT_TURN_OFF/EXT_OUTPUT_TURN_ON
Return type:         CFG_SUCCESS on success
                     CFG_FAILURE on failure
Purpose:             send External Port Assignment to BPM via OIL 
Other Note:
 ************************************************************************************/
I_U32 sendExternalPortStateChangeReqToBpm(I_U8 extPortId, I_U8 extOutputPortStateChange)
{
  OamsCfgOilExtPortStateChangeReq oamsCfgOilextPortStateChangeReq;

  LOG_PRINT(INFO,"Entering func sendExternalPortStateChangeReqToBpm");
  oamsCfgOilextPortStateChangeReq.extPortType=EXT_OUTPUT_PORT;
  oamsCfgOilextPortStateChangeReq.extPortId=extPortId;
  oamsCfgOilextPortStateChangeReq.extPortStateChange=extOutputPortStateChange;


  cfgSendMessage(&oamsCfgOilextPortStateChangeReq, 
                    sizeof(OamsCfgOilExtPortStateChangeReq), 
                    ENT_OAM_OIL, 
                    OAMS_CFG_OIL_EXT_PORT_STATE_CHANGE_REQ, 
                    0);
  LOG_PRINT(INFO,"Exiting func sendExternalPortStateChangeReqToBpm");
  return CFG_SUCCESS;
}


/********************************* Function  Header********************************
Function Name:       sendExtOutputEventToOMC
Parameters:          external Out Port Id:EXT_OUTPUT_PORT1/EXT_OUTPUT_PORT2 
                     extOutputPortStateChange: EXT_OUTPUT_TURN_OFF/EXT_OUTPUT_TURN_ON
                     extEventText : Pointer to Event Text                     
                     extEventSeverity : EXT_SEVERITY_INFORMATION/EXT_SEVERITY_WARNING/
                     EXT_SEVERITY_MINOR/EXT_SEVERITY_MAJOR/EXT_SEVERITY_CRITICAL
Return type:         CFG_SUCCESS on success
                     CFG_FAILURE on failure
Purpose:             send External Output Event to OMC via AFH 
Other Note:
 ************************************************************************************/
I_U32 sendExtOutputEventToOMC(I_U8 extOutputPortId,I_U8 extOutputPortStateChange,const I_CHAR *extEventText,I_U8 extEventSeverity)
{
  OamAfhAlarmInd oam_alarm_ind;
  I_U8 extStateString[EXT_PORT_STATE_STRING_LEN];

  LOG_PRINT(INFO,"Entering func sendExtOutputEventToOMC");
  memset(extStateString,0,EXT_PORT_STATE_STRING_LEN);
  memset (&oam_alarm_ind, 0, sizeof (OamAfhAlarmInd));
  if(extOutputPortId == EXT_OUTPUT_PORT1)
  {
    oam_alarm_ind.sysAlarm.sysalarmId = EVENT_EXT_OUT_PORT1;
  }
  else if(extOutputPortId == EXT_OUTPUT_PORT2)
  {
    oam_alarm_ind.sysAlarm.sysalarmId = EVENT_EXT_OUT_PORT2;
  }
  else
  {
    LOG_PRINT(CRITICAL,"sendExtOutputEventToOMC:External Output Port not valid");
    return CFG_FAILURE;
  }

  if(extOutputPortStateChange == EXT_OUTPUT_PORT_TURN_ON)
  {
    strcpy(extStateString,"TURN ON");
  }
  else if(extOutputPortStateChange == EXT_OUTPUT_PORT_TURN_OFF)
  {
    strcpy(extStateString,"TURN OFF");
  }
  else 
  {
    LOG_PRINT(CRITICAL,"sendExtOutputEventToOMC:External Output Port State Change not valid");
    return CFG_FAILURE;
  }
  
  oam_alarm_ind.sysAlarm.alarmReason = OAMS_EXT_OUTPUT_PORT_STATECHG;
  oam_alarm_ind.sysAlarm.alarmLevel = extEventSeverity;
  oam_alarm_ind.sysAlarm.info3 = OAMS_OBJTYPE_EXT_OUTPUT_PORT;
  oam_alarm_ind.sysAlarm.infoStrLen =	sprintf (((char *) oam_alarm_ind.sysAlarm.infoString),
      "%s StateChange %s",extEventText,extStateString);
  oam_alarm_ind.sysAlarm.key1=extOutputPortId;
  
  cfgSendMessage(&oam_alarm_ind, 
                    sizeof(OamAfhAlarmInd), 
                    ENT_OAM_AFH, 
                    OAMS_CFG_AFH_ALARM_IND, 
                    0);
  LOG_PRINT(INFO,"Exiting func sendExtOutputEventToOMC");
  return CFG_SUCCESS;
}

/********************************* Function  Header********************************
Function Name:       sendExtInputAlarmToOMC
Parameters:          external Input Port Id:EXT_INPUT_PORT1/EXT_INPUT_PORT2/
                     EXT_INPUT_PORT3/EXT_INPUT_PORT4 
                     extInputPortState: EXT_INPUT_PORT_STATE_OPEN/
                     EXT_INPUT_PORT_STATE_CLOSE
                     extInputPortAlarmCondition: EXT_INPUT_PORT_STATE_OPEN/
                     EXT_INPUT_PORT_STATE_CLOSE
                     extAlarmText : Pointer to Alarm Text                     
                     extAlarmSeverity : EXT_SEVERITY_INFORMATION/EXT_SEVERITY_WARNING/
                     EXT_SEVERITY_MINOR/EXT_SEVERITY_MAJOR/EXT_SEVERITY_CRITICAL
Return type:         CFG_SUCCESS on success
                     CFG_FAILURE on failure
Purpose:             send External Output Event to OMC via AFH 
Other Note:
 ************************************************************************************/
I_U32 sendExtInputAlarmToOMC(I_U8 extInputPortId,I_U8 extInputPortState,
    I_U8 extInputAlarmCondition,const I_CHAR *extAlarmText,I_U8 extAlarmSeverity)
{
  OamAfhAlarmInd oam_alarm_ind;
  I_U32 raiseAlarmId,clearAlarmId;
  I_S32 dbStatus;
  /*Mantis 24774 Start*/
  ActiveAlarmListTableIndices activeAlarmTableIndex;
  ActiveAlarmListTableApi *activeAlarmTableApiPtr;
  /*Mantis 24774 End*/

  LOG_PRINT(INFO,"Entering func sendExtInputAlarmToOMC");
  memset (&oam_alarm_ind, 0, sizeof (OamAfhAlarmInd));

  COMPUTE_RAISE_CLEAR_ALARM_ID(extInputPortId)
 
   if(raiseAlarmId == 0 && clearAlarmId == 0)
   {
     LOG_PRINT(CRITICAL,"sendExtInputAlarmToOMC:No Alarm can be \
         raised as ext input port is invalid");
     return CFG_FAILURE;
   }

  oam_alarm_ind.sysAlarm.alarmReason = OAMS_EXT_INPUT_PORT_STATECHG;
  oam_alarm_ind.sysAlarm.info3 = OAMS_OBJTYPE_EXT_INPUT_PORT;
  oam_alarm_ind.sysAlarm.key1= extInputPortId;
    
   if(extInputAlarmCondition == extInputPortState)
   {
      oam_alarm_ind.sysAlarm.sysalarmId = raiseAlarmId;
      oam_alarm_ind.sysAlarm.alarmLevel = extAlarmSeverity;
      oam_alarm_ind.sysAlarm.infoStrLen =	sprintf (((char *) oam_alarm_ind.sysAlarm.infoString),
      "%s",extAlarmText);

      cfgSendMessage(&oam_alarm_ind, 
          sizeof(OamAfhAlarmInd), 
          ENT_OAM_AFH, 
          OAMS_CFG_AFH_ALARM_IND, 
          0);
    }
    else
    {
      oam_alarm_ind.sysAlarm.sysalarmId = clearAlarmId;
      oam_alarm_ind.sysAlarm.alarmLevel = EXT_SEVERITY_CLEAR;
      oam_alarm_ind.sysAlarm.infoStrLen =	sprintf (((char *) oam_alarm_ind.sysAlarm.infoString),
      "%s  %s",extAlarmText,"CLEARED");

      /*Mantis 24774 Start*/
      memset((I_PVoid)&activeAlarmTableIndex,0,sizeof(ActiveAlarmListTableIndices));
      activeAlarmTableIndex.sysalarmId=raiseAlarmId;
      activeAlarmTableIndex.key1=extInputPortId;
      dbStatus=getActiveAlarmListTable(&activeAlarmTableIndex,&activeAlarmTableApiPtr);
      if(DBLIB_SUCCESS == dbStatus)
      {
      free(activeAlarmTableApiPtr);
      cfgSendMessage(&oam_alarm_ind, 
          sizeof(OamAfhAlarmInd), 
          ENT_OAM_AFH, 
          OAMS_CFG_AFH_ALARM_IND, 
          0);
      }
      else
      {
        LOG_PRINT(DEBUG,"No raise alarm in activeAlarmTable for ExtInputPortId %d",extInputPortId);
      }
      /*Mantis 24774 End*/
    }

  LOG_PRINT(INFO,"Exiting func sendExtInputAlarmToOMC");
  return CFG_SUCCESS;
}

/********************************* Function  Header********************************
Function Name:       sendAllExtInputPortStatusReq
Parameters:          None 
Return type:         CFG_SUCCESS on success
                     CFG_FAILURE on failure
Purpose:             send External Port Status Req to PDC 
Other Note:
 ************************************************************************************/
I_U32 sendAllExtInputPortStatusReq()
{
  OamsCfgPdcExtInputPortStatusReq cfgPdcExtInputPortStateReq;
  I_S32 dbStatus;
  I_U32 res=0;
  I_U32 rowsCount = 0,ctr=0;
  I_U16 outSize = 0;
  ExternalInputPortConfigTableApi *externalInputPortConfigTableApiPtr=PNULL,
                                  *tmpExternalInputPortConfigTableApiPtr=PNULL;

  LOG_PRINT(LOG_DEBUG,"Entering Function sendAllExtInputPortStatusReq");
  dbStatus=getallExternalInputPortConfigTable(&externalInputPortConfigTableApiPtr,&rowsCount,&outSize);
  if(CLIB_SUCCESS == dbStatus)
  {
    for(ctr=0;ctr<rowsCount;ctr++)
    {
      tmpExternalInputPortConfigTableApiPtr=(ExternalInputPortConfigTableApi*)((I_U8*)externalInputPortConfigTableApiPtr + ctr*outSize);

      LOG_PRINT(LOG_INFO,"sendAllExtInputPortStatusReq:Processing for portId %d",tmpExternalInputPortConfigTableApiPtr->extInputPortId);
      if(tmpExternalInputPortConfigTableApiPtr->assignedState == EXT_PORT_ASSIGN)
      {
        cfgPdcExtInputPortStateReq.extPortId=tmpExternalInputPortConfigTableApiPtr->extInputPortId;
        cfgSendMessage(&cfgPdcExtInputPortStateReq, 
                    sizeof(OamsCfgPdcExtInputPortStatusReq), 
                    ENT_OAM_PDC, 
                    OAMS_CFG_PDC_EXT_INPUT_PORT_STATUS_REQ, 
                    0);
        
      }

    }
    free(externalInputPortConfigTableApiPtr);
  }
 
  LOG_PRINT(LOG_DEBUG,"Exiting Function sendAllExtInputPortStatusReq");

 return CFG_SUCCESS; 
}

/********************************* Function  Header********************************
Function Name:       delExternalInputPortConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from ExternalInputPortConfig table 
Other Note:          Added for External Alarm 
 ************************************************************************************/
void delExternalInputPortConfigTableHandler()
{
   ExternalInputPortConfigTableApi* receivedMsgPtr = NULL;
   receivedMsgPtr = ( ExternalInputPortConfigTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   ExternalInputPortConfigTableIndices extInputPortConfigTableIndex;
   ExternalInputPortStatusTableIndices extInputPortStatusTableIndex;
   ExternalInputPortConfigTableApi *extInputPortConfigTablePtr;
   ActiveAlarmListTableIndices activeAlarmTableIndex;
   I_S32 retStatus,dbStatus;
   I_U32 raiseAlarmId,clearAlarmId;

   LOG_PRINT(LOG_INFO," Entering function %s with extInputPortId(%d)",__FUNCTION__,receivedMsgPtr->extInputPortId);

   extInputPortConfigTableIndex.extInputPortId=receivedMsgPtr->extInputPortId;
   dbStatus=getExternalInputPortConfigTable(&extInputPortConfigTableIndex,&extInputPortConfigTablePtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
     LOG_PRINT(DEBUG,"Get on ExternalInputPortConfig Failed for extInputPortId(%d)",receivedMsgPtr->extInputPortId); 
     cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
     return;
   }
   else
   {
     if(extInputPortConfigTablePtr->assignedState != EXT_PORT_FREE)
     {
       LOG_PRINT(DEBUG,"Assigned State is Not FREE,cannot delete"); 
       cfgSendNackToCm(CM_ERR_EXT_ASSIGNED_STATE_NOT_FREE);
       free(extInputPortConfigTablePtr);
       return;
     }
     free(extInputPortConfigTablePtr);
   }

   extInputPortStatusTableIndex.extInputPortId=receivedMsgPtr->extInputPortId;
   dbStatus=deleteExternalInputPortStatusTable(&extInputPortStatusTableIndex);
   if(CLIB_SUCCESS == dbStatus)
   {
     LOG_PRINT(LOG_INFO,"ExternalInputStatus Row is successfully deleted");
   }
   else
   {
     LOG_PRINT(LOG_INFO,"ExternalInputStatus Row could not be deleted");
     cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
     return;
   }

   dbStatus=deleteExternalInputPortConfigTable(&extInputPortConfigTableIndex);
   if(CLIB_SUCCESS == dbStatus)
   {
     LOG_PRINT(LOG_INFO,"ExternalInputConfig Row is successfully deleted");
     cfgSendAckToCm();
   }
   else
   {
     LOG_PRINT(LOG_CRITICAL," DB del operation Failed on ExternalInputConfigTable, sending Nack");
     cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
     return;
   }

   LOG_PRINT(LOG_INFO," Exiting function %s",__FUNCTION__);

   return;
}/* end of delExternalInputPortConfigTableHandler*/

/********************************* Function  Header********************************
Function Name:       delExternalOutputPortConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from ExternalOutputPortConfig table 
Other Note:          Added for External Alarm 
 ************************************************************************************/
void delExternalOutputPortConfigTableHandler()
{
   ExternalOutputPortConfigTableApi* receivedMsgPtr = NULL;
   receivedMsgPtr = ( ExternalOutputPortConfigTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   ExternalOutputPortConfigTableIndices extOutputPortConfigTableIndex;
   ExternalOutputPortConfigTableApi *extOutputPortConfigTablePtr;
   I_S32 retStatus,dbStatus;

   LOG_PRINT(LOG_INFO," Entering function %s with extOutputPortId(%d)",__FUNCTION__,receivedMsgPtr->extOutputPortId);

   extOutputPortConfigTableIndex.extOutputPortId=receivedMsgPtr->extOutputPortId;
   dbStatus=getExternalOutputPortConfigTable(&extOutputPortConfigTableIndex,&extOutputPortConfigTablePtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
     LOG_PRINT(DEBUG,"Get on ExternalOutputPortConfig Failed for extOutputPortId(%d)",receivedMsgPtr->extOutputPortId); 
     cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
     return;
   }
   else
   {
     if(extOutputPortConfigTablePtr->assignedState != EXT_PORT_FREE)
     {
       LOG_PRINT(DEBUG,"Assigned State is Not FREE,cannot delete"); 
       cfgSendNackToCm(CM_ERR_EXT_ASSIGNED_STATE_NOT_FREE);
       free(extOutputPortConfigTablePtr);
       return;
     }
     free(extOutputPortConfigTablePtr);
   }

   dbStatus=deleteExternalOutputPortConfigTable(&extOutputPortConfigTableIndex);
   if(CLIB_SUCCESS == dbStatus)
   {
     LOG_PRINT(LOG_INFO,"ExternalOutputConfig Row is successfully deleted");
     cfgSendAckToCm();
   }
   else
   {
     LOG_PRINT(LOG_CRITICAL," DB del operation Failed on ExternalOutputConfigTable, sending Nack");
     cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
     return;
   }

   LOG_PRINT(LOG_INFO," Exiting function %s",__FUNCTION__);

   return;
}/* end of delExternalOutputPortConfigTableHandler*/
/********************************* Change History ******************************
   Release     Patch       Author            Description
   R2.8                    Grvjn             Added this file for External Alarm 
                                             handling
 ************************************** End ************************************/
