/********************************File Header ***********************
  File Name        : oamscfg_tsgroup_object_handler.h
Purpose          : This file contains function declarations for tsGroup 
                   Object Handling.
Project          : BSC
Subsystem        : OAMS
Author           : VNL
CSCI ID          :
Version          :
 ************************************* End **********************************/
#ifndef _OAMSCFG_TSGROUP_OBJECT_HANDLER_H_
#define _OAMSCFG_TSGROUP_OBJECT_HANDLER_H_



I_U32 getTrunkUsageType(I_U16 trunkId,I_U32 *trunkUsageType);
I_U32 fillTSMapForTrunk(I_U32 busyTSMap,I_U32 numTs,I_U32 *tsMap);
I_S32 prepAndSndSwitchConForTsGroup(I_U16 firstTrunk, I_U8 *tsArray1,
    I_U16 secondTrunk, I_U8 *tsArray2,I_U32 numTs);
I_S32 prepAndSndSwitchDisconnForTsGroup(I_U16 firstTrunk, I_U8 *tsArray1,
    I_U16 secondTrunk, I_U8 *tsArray2,I_U32 numTs);
I_Void sndSwtConnForAllTsGroupMaps();
I_U32 allocateTSforTsGroup(I_U16 firstTrunk,I_U16 secondTrunk,I_U32 numTs,
    I_U32 *tsMap1,I_U32 *tsMap2,I_U32 usageType1,I_U32 usageType2);
I_U32 AreTimeSlotsNotUsedForTsGroup(I_U16 e1Id,I_U32 tsMap);
I_Void convertTsBitMapToArray(I_U32 numTs,I_U32 tsMap,I_U8* tsAllocatedArray);
#endif

/********************************* Change History ***************************
  Release     Patch       Author         Description
  BSC R2.5.5              Gaurav Jain               
 ************************************** End *********************************/

