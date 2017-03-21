/***********************************File Header ***************************
File Name        : oamsbich_abis_chain_mgr.h
Purpose          : This file contains functions declaration for Abis Chain Mgr.
Project          : BSC CS2.2
Subsystem        : Oams
Author           : Aricent
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef __OAMSBICH_ABIS_CHAIN_MGR_H
#define __OAMSBICH_ABIS_CHAIN_MGR_H

#include <oamsbich_includes.h>

extern OamsBichContext *gOamsBichContextPtr;
void  initAbisChain(I_PVoid sndPtr);
void addBicInAbisChain(I_PVoid sndPtr);
void deleteBicFromAbisChain(I_PVoid sndPtr);
I_U8 getAbisChainStatus(BicTei bicTei);
void updateAbisChainStatus(BicTei bicTei,I_U8 status);
I_U32 getFirstBicFromTei(BicTei bicTei);
void prepareSlotConnect(I_PVoid sndPtr);
OamsList *getabisChainList();
AbisE1Node *allocateAbisE1Node(I_U32 e1Id);
void freeAbisE1Node(AbisE1Node *abisE1);
AbisE1Node *searchAbisE1Tei(OamsList *abisChainList, BicTei bicTei);
AbisE1Node *searchAbisE1Id(OamsList *abisChainList, I_U8 e1Id);
BicNode *allocateBicNode(BicIdentifier bicId);
BicNode *findBicInTree(OamsTree *rootnode,BicIdentifier bicId);
BicNode *searchBic(BicIdentifier bicId,BicTei bicTei);
void sendSlotConnectMsg(BicIdentifier forbicId,BicIdentifier toBicId,BicIdentifier dsBicId,\
I_U8 trxCount,BicTei bicTei,I_U8 *lapdTs,I_U8 *startTs, I_U8 *firstTsTraffic, I_U8 *secondTsTraffic);

void buildUpStreamSlotConnMap(OamsTree *ptr,BicIdentifier forbicId,BicIdentifier toBicId,\
BicIdentifier dsBicId,I_U8 trxCount,BicTei bicTei,I_U8 *lapdTs,I_U8 *firstTsTraffic, I_U8 *secondTsTraffic);

void sendSlotDisconnMsg(BicIdentifier forbicId,BicIdentifier toBicId,BicIdentifier dsBicId,\
I_U8 trxCount,BicTei bicTei,I_U8 *lapdTs);

void buildSlotDisconnectMap(OamsTree *ptr,BicIdentifier forBicId,I_U8 trxCount,\
BicIdentifier dsBicId,BicTei bicTei,I_U8 *lapdTs);

void prepareDisconnectedChildList(BicIdentifier parentbicid,BicIdentifier bicId,\
BicTei bicTei,void (*sendBicParentNotAvail)(I_U32));

I_U8 getLapdTs(I_U32 *ptrxId,I_U8 trxCount,I_U8 *lapdTs);
I_U8 getStartTs(I_U32 *ptrxId,I_U8 trxCount,I_U8 *startTs);
void slotDisconnectForChild(BicIdentifier forBicId,BicIdentifier parentBicId,\
BicIdentifier dsBicId,BicTei bicTei);
I_U32 getFirstDsBicFromBicList(I_PVoid rcvPtr);

void prepareSlotDisConnect(I_PVoid sndPtr,void (*sendBicParentNotAvail)(I_U32));

AbisE1TsNode *allocateTsNode(I_U32 timeSlot,I_U32 bicTei);

I_S32 getE1IdFromTei(OamsList *abisChainList,BicTei tei);

void initializeChain();
AbisE1TsNode *searchTsNodeOnTimeSlot(I_U8 e1Id,I_U8 timeSlot);
AbisE1TsNode *searchTsNodeOnTei(I_U8 e1Id,I_U8 bicTei);

/* CS4.0: HA changes Start */
I_Void cardStateChangeHandler(struct sAisParam *);
I_Void activeInProgressStateHandler();
I_Void findLocalPidForEachBic(I_U32 *lclPidPtr, I_S32 *instId, I_U32 bicId);
I_Void freeE1Node(I_U32 e1Id);
I_Void freeE1TsNode(I_U32 e1Id);
I_Void freeAllE1AndTimeSlotNode();
I_Void  activeStateHandler();
I_Void findLclPidPtr ( I_U32 refId, I_U8 classId, I_U32 *lclPidPtr, I_U8 entId);
I_U32 getCountAllocatedInst ( I_U32 instCount );
I_Bool addTsNodeInAbisChain(I_PVoid rcvPtr);
I_Void delTsNodeFromAbisChain(OamsBichContext *rcvPtr);
/* CS4.0: HA changes End */

#endif /*__OAMSBICH_ABIS_CHAIN_MGR_H*/





