/***********************************File Header ***************************
  File Name        : oamscfg_consistancy_check.h
Purpose          : This file contains functions definitions for CFG
Consistency checks methods.
Project          :  BSC OAM
Subsystem        : Oams
Author           : Aricent 
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef _OAMCFG_CONSISTANCY_CHECK_H_
#define _OAMCFG_CONSISTANCY_CHECK_H_


I_U32 doConsistencyChecksOnSetOnRaTable(RaTableApi  *receivedMsgPtr);
I_U32 doConsistencyChecksOnSetOnLepInfoTable(LepInfoTableApi  *receivedMsgPtr, I_Bool isAdd);
I_U32 doConsistencyChecksOnSetOnRepInfoTable(RepInfoTableApi  *receivedMsgPtr, I_Bool isAdd);
I_U32 doConsistencyChecksOnSetOnNsvcTable(NsvcTableApi  *receivedMsgPtr, I_Bool isAdd);
I_U32 doConsistencyChecksOnSetOnFrLinkTable(FrLinkTableApi  *receivedMsgPtr, I_Bool isAdd);
I_U32 doConsistencyChecksOnSetOnGbInterfaceTable(GbInterfaceTableApi *rcvdMsgPtr);

/* This method checks whether the given e1Id and timeslot are present in the MlpppConfig table row in any of the 16 pairs*/
I_Bool isMlpppConfigExistsForE1Ts(I_U16 e1Id, I_U8 timeSlot);

/********************************* Change History ***************************
  Release     Patch       Author         Description
  PCU R2.5                Aricent       Initial Revision for consistency Checks

 ************************************** End *********************************/


#endif /*_OAMCFG_CONSISTANCY_CHECK_H_ */ 
