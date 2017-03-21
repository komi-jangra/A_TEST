/***********************************File Header ***************************
File Name        : amscfg_mccfr_resource_handler.h
Purpose          : This file contains Mcc Fr Resource Handler declarations
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef _OAMSCFG_MCC_FR_RESOURCE_HANDLER_H_
#define _OAMSCFG_MCC_FR_RESOURCE_HANDLER_H_ 

I_Void initMccFrResourceMap();
I_U8 getNumAvailableMccFrTs(I_Void);
I_U8 getNumElemMccFrResource(I_Void);
I_Void sortMccFrResourceMap(I_Void);
I_Void swapgMccFrResourceMapElems(int i, int j);
I_S8 areContiguousNumMccFrTs(I_U8 numTs);
I_Bool allocateContiguousNumMccFrTs(I_U16  frChnId, I_U16 e1Id, I_U8 startTs, I_U8 numTs);
I_Void deallocateContiguousNumMccFrTs(I_U16 frChnId);
#endif

