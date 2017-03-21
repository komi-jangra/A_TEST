/***********************************File Header ***************************
       File Name        : oamscfg_e1timeslot_object_handler.h
       Purpose          : This file contains functions definitions for CFG
                          Timeslot Object Handler  methods.
       Project          :  BSC OAM
       Subsystem        : Oams
       Author           :  Aricent Bangalore
       CSCI ID          :
       Version          :
************************************* End **********************************/
#ifndef __OAMSCFG_E1TIMESLOT_OBJECT_HANDLER_H
#define __OAMSCFG_E1TIMESLOT_OBJECT_HANDLER_H

#define SET_BIT( var, bit ) var |= (1<<bit)
#define lBYtes 0
#define hBytes 16

/*
If usageType=MTP2:
Octet 1-2: link code
Octet 3-4: link set Id 
*/
#define M_GET_LINKSET(usingEntity) (usingEntity >> 16)
#define M_GET_LINKCODE(usingEntity) (usingEntity & 0x00ff)

void e1TimeSlotObjectHandler();
objectState getTimeSlotObjectState(I_U16 e1Num, I_U16 TsNum);
objectState getStateTimeSlot();
void timeSlotUnlockInProgressHandler();
void timeSlotLockInProgressHandler();
void setTimeSlotTable();
I_Bool sendTimeSlotMessageToSCM(I_U16 reqType);
void sendTimeSlotMessageToGRHM(I_U16 reqType);
void sendTimeSlotMessageToPSSCM(I_U16 reqType);
void setTimeSlot();
void scmUnlockRespTimeSlot();
void csappGrhmCfgUnlockRespTimeSlot();
void scmLockRespTimeSlot();
void csappGrhmCfgLockRespTimeSlot();
void scmCfgAlarmInd();
void csappGrhmCfgAlarmInd();
I_U32 maskBits(I_U32 var,I_U32 value,int bitCount);
void unMaskBits(I_U32  n ,I_U16 * a, I_U16 *b);
/* CS4.0 HA Stack Changes : Start */
//void e1SendLinkAdminTableToScm(AbisTimeSlotPerTableApi *e1TimeSlotObjPtr, I_U32 admStateReqst);
void e1SendLinkAdminTableToScm(LinkTableApi *linkTablePtr, I_U32 admStateReqst);
/* CS4.0 HA Stack Changes : End */
void updateOprStatusOfTimeSlotsForE1(I_U32 e1Num, I_U32 oprStatus);
I_Bool  e1TimeSlotSendLinkAdminTableToScm(AbisTimeSlotPerTableApi *e1TimeSlotObjPtr, I_U32 admStateReqst);

/********************************* Change History ***************************
   Release     Patch       Author         Description

************************************** End *********************************/
#endif/* __OAMSCFG_E1TIMESLOT_OBJECT_HANDLER_H */

