/***********************************File Header ***************************
File Name        : oamscfg_externalport_handler.h
Purpose          : This file contains CFG External Alarm function declaration
                   and hashdefines
Project          : BSC OAM
Subsystem        : Oams
Author           : Gaurav Jain
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef __OAMSCFG_EXTERNALPORT_HANDLER_H
#define __OAMSCFG_EXTERNALPORT_HANDLER_H

#if 0
/*Port Type*/
#define EXT_INPUT_PORT 1
#define EXT_OUTPUT_PORT 2

#define EXT_INPUT_PORT1 1
#define EXT_INPUT_PORT2 2
#define EXT_INPUT_PORT3 3
#define EXT_INPUT_PORT4 4

#define EXT_OUTPUT_PORT1 1
#define EXT_OUTPUT_PORT2 2

/*Port Assignment*/
#define EXT_PORT_FREE 0
#define EXT_PORT_ASSIGN 1

#define EXT_PORT_STATE_STRING_LEN 12

/*Output Port State Action*/
#define EXT_OUTPUT_PORT_TURN_OFF 0
#define EXT_OUTPUT_PORT_TURN_ON  1

/*External Severity*/
#define EXT_SEVERITY_CLEAR       0
#define EXT_SEVERITY_INFORMATION 1
#define EXT_SEVERITY_WARNING     2 
#define EXT_SEVERITY_MINOR       3
#define EXT_SEVERITY_MAJOR       4
#define EXT_SEVERITY_CRITICAL    5
#endif

#define COMPUTE_RAISE_CLEAR_ALARM_ID(extInputPortId){\
  if(extInputPortId == EXT_INPUT_PORT1) \
  { \
    raiseAlarmId=ALARM_EXT_INP_PORT1_RAISE;\
    clearAlarmId=ALARM_EXT_INP_PORT1_CLEAR;\
  }\
  if(extInputPortId == EXT_INPUT_PORT2) \
  { \
    raiseAlarmId=ALARM_EXT_INP_PORT2_RAISE;\
    clearAlarmId=ALARM_EXT_INP_PORT2_CLEAR;\
  }\
  if(extInputPortId == EXT_INPUT_PORT3) \
  { \
    raiseAlarmId=ALARM_EXT_INP_PORT3_RAISE;\
    clearAlarmId=ALARM_EXT_INP_PORT3_CLEAR;\
  }\
  if(extInputPortId == EXT_INPUT_PORT4) \
  { \
    raiseAlarmId=ALARM_EXT_INP_PORT4_RAISE;\
    clearAlarmId=ALARM_EXT_INP_PORT4_CLEAR;\
  }\
}

#define DELETE_EXTERNAL_ACTIVE_ALARM(portId){\
   memset(&activeAlarmTableIndex,0,sizeof(ActiveAlarmListTableIndices));\
   COMPUTE_RAISE_CLEAR_ALARM_ID(portId)\
   activeAlarmTableIndex.sysalarmId=raiseAlarmId;\
   activeAlarmTableIndex.key1=portId;\
   dbStatus=deleteActiveAlarmListTable(&activeAlarmTableIndex);\
   if(DBLIB_SUCCESS != dbStatus)\
   {\
     LOG_PRINT(DEBUG,"Delete Alarm on ExternalInputPortConfig Failed for extInputPortId(%d)",receivedMsgPtr->extInputPortId); \
   }\
   else \
   {\
     LOG_PRINT(DEBUG,"Delete Alarm on ExternalInputPortConfig Success for extInputPortId(%d)",receivedMsgPtr->extInputPortId); \
   }\
}
void setExternalInputPortConfigTableHandler();
I_U32 extInputPortConfigTableRangeCheck(ExternalInputPortConfigTableApi* extInputPortConfigTableApiPtr);
void setExternalOutputPortConfigTableHandler();
I_U32 extOutputPortConfigTableRangeCheck(ExternalOutputPortConfigTableApi* extOutputPortConfigTableApiPtr);
I_U32 sendExternalPortConfigReqToBpm(I_U8 extPortType,I_U8 extPortId, I_U8 assignState);
I_U32 sendExternalPortStateChangeReqToBpm(I_U8 extPortId, I_U8 extOutputPortStateChange);
I_U32 sendExtOutputEventToOMC(I_U8 extOutputPortId,I_U8 extOutputPortStateChange,
    const I_CHAR *extEventText,I_U8 extEventSeverity);
I_U32 sendExtInputAlarmToOMC(I_U8 extInputPortId,I_U8 extInputPortState,
    I_U8 extInputAlarmCondition,const I_CHAR *extAlarmText,I_U8 extAlarmSeverity);
void delExternalInputPortConfigTableHandler();
void delExternalOutputPortConfigTableHandler();

#endif
/********************************* Change History ******************************
   Release     Patch       Author            Description
   R2.8                    Grvjn             Added this file for External Alarm 
                                             handling
 ************************************** End ************************************/
