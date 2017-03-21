/******************************************************************************
 FILE NAME         :  oamscellh_mapltrxptrxent.h
 PURPOSE           :  Header file for Mapping Entity include files,function
                      declarations and HashDefs.
 PROJECT           :  BSS
 SUBSYSTEM         :  OAM 
 AUTHOR            :  ARICENT
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/


#ifndef __OAMSCELLH_MAPLTRXPTRENT_H
#define __OAMSCELLH_MAPLTRXPTRENT_H



#define MSG_SUCCESS 1
#define MAX_PRIORITY 1000000

#define MAX_POWER_REDUCTION 12
#define MIN_POWER_REDUCTION 0

/* Mapping Status */
#define UNMAPINITIATED 2

/* Defining Invalid Ptrx to be filled in LtrxRecord when it is unmapped  */
#define INVALID_PTRXID 0


#define CREATE_IN_PROGRESS 6
#define DELETE_IN_PROGRESS 5
#ifdef CPLUSPLUS
EXTERN "C"
{
#endif

I_S32 CreateMsgMapentCellhDelMapResp(I_U32 ltrxId);

I_S32 CreateMsgMapentTrxhCreLtrxPtrxMappingReq(LtrxTableApi* ltrxRec, 
                                               ChnGrpTableApi *chnGrpTableRec);

I_S32 CreateMsgMapentTrxhDelLtrxPtrxMappingReq(I_U32 ptrxId, 
                                               LtrxTableApi* ltrxRec);

I_Bool FindNotMappableButMappedPtrx (I_U32 *ptrxId);

I_Bool FindSuitableUnmappedPtrxWithMapAllowed (I_U32 *ptrxId, 
                                              LtrxTableApi *ltrxRec,
                                              ChnGrpTableApi *chnGrpTableRec);

I_S32 GetPtrxSuitability( I_U32 ptrxId,
                          LtrxTableApi *ltrxRec,
                          ChnGrpTableApi *chnGrpTableRec );

I_Bool FindGenUnmappedLtrxWithHighestPriority ( LtrxTableApi *ltrxRec);
 
I_Bool FindGenMappedLowestPriorityLtrxRecord (LtrxTableApi *ltrxCurrRec,
                                           LtrxTableApi* ltrxLowerPriorityRec, 
                                           ChnGrpTableApi *chnGrpTableRec );

I_Bool FindMappedCleaningDownLtrx (LtrxTableApi* ltrxRec );

I_S32 IscleaningDown( I_U32 ltrxId );

I_Bool GetAssociatedLtrx(I_U32 ptrxId, LtrxTableApi **ltrxRec);

I_Bool MappingLtrxPtrxEntity(I_U16 invocationMode, I_PVoid dataPtr);

I_Bool GetSortedGenUnmappedLtrxList( LtrxTableApi **sortedGenUnmappedLtrxList,I_U32 *totalSortedGenUnMappedLtrxRecs );

I_Bool FindLtrxWithSuitablePtrx ( I_U32 *ptrxID, LtrxTableApi *ltrxRec,LtrxTableApi **lowerPrtLtrxRec,ChnGrpTableApi **chnGrpTableRec,I_Bool *IsUnmappedPtrx );

I_Bool IsDemappingAlreadyInitiated(LtrxTableApi *ltrxRec,ChnGrpTableApi *chnGrpTableRec);

/* CS4.0 : Abis E1 Lock/Unlock Changes : Starts */
I_Bool ValidateE1OfPtrx(I_U32 ptrxId);
/* CS4.0 : Abis E1 Lock/Unlock Changes : Ends */

#ifdef CPLUSPLUS
}
#endif


#endif 

