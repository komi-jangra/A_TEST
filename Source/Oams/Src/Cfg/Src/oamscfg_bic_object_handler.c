
/***********************************File Header ********************************
   File Name        : oamscfg_bic_object_handler.c
Purpose          : This file contains functions definition required for the 
handling of BIC object 
Project          : BSC OAM
Subsystem        : Oams
Author           : Kapil Tyagi 
CSCI ID          :
Version          :
 ************************************* End *************************************/

#include <oamscfg_includes.h>



I_S32 allocateApplTei(I_U8 appTeiUser ,I_U32 userId, I_U8 *applTei)
{
   ApplTeiPoolTableIndices applTeiIndex;
   ApplTeiPoolTableApi applTeiApiBuf;
   ApplTeiPoolTableApi *applTeiApiPtr;
   ApplTeiPoolTableApi *tmpApplTeiApiPtr;
   I_U32 outRows,i;
   I_U16 outSize;
   I_S32 ret;
   
   
   LOG_PRINT(LOG_INFO,"Entering Function : allocateApplTei");
   LOG_PRINT(LOG_DEBUG,"allocateApplTei:  appTeiUser %d userId %d",appTeiUser,userId);
  
      ret = getallApplTeiPoolTable(&applTeiApiPtr, &outRows, &outSize);
      if(ret == CLIB_SUCCESS)
      {
         for(i=0;i<outRows;i++)
         {
            tmpApplTeiApiPtr = (ApplTeiPoolTableApi *)(((I_U8 *)applTeiApiPtr) + (i * outSize));
            if(appTeiUser == TEI_USR_BTS)
            { 
              if ((tmpApplTeiApiPtr->applTei < (CFG_TRX_APP_TEI_START_INDEX+ONE)) &&(tmpApplTeiApiPtr->status == TEI_NOT_ALLOCATED))
                 {
                 *applTei =  tmpApplTeiApiPtr->applTei;
                 break; 
                 }
            }
            else if (appTeiUser == TEI_USR_TRX)
            {
              if ((tmpApplTeiApiPtr->applTei > CFG_TRX_APP_TEI_START_INDEX)&&(tmpApplTeiApiPtr->status == TEI_NOT_ALLOCATED))
                 {
                 *applTei =  tmpApplTeiApiPtr->applTei;
                 break; 
                 }
            
            }  
         }
         free(applTeiApiPtr);
         if(i == outRows)
         {
            LOG_PRINT(MAJOR,"No Proper Free Entry found in ApplTeiPoolTable to allocate for BTS/TRX"); 
            return -1;
         }  
         applTeiApiBuf.applTei = *applTei; 
         applTeiApiBuf.status = TEI_ALLOCATED;
         applTeiApiBuf.applTeiUser = appTeiUser;
         applTeiApiBuf.userId = userId;
      }
      else
      {
      LOG_PRINT(LOG_MAJOR,"allocateApplTei: getallApplTeiPoolTable failed with err %s",ret);
	    return -1;
      }  

    ret = updateApplTeiPoolTable(&applTeiApiBuf); 
    if(ret != CLIB_SUCCESS)
    {
       LOG_PRINT(MAJOR,"updateApplTeiPoolTable failed err:%d", ret); 
    }
    else
    {
   LOG_PRINT(LOG_DEBUG,"allocateApplTei: Allocated App Tei %d for appTeiUser %d userId %d",*applTei,appTeiUser,userId);
    }  
    return ret;
}


I_S32 deAllocateApplTei(I_U16 applTei)
{
   ApplTeiPoolTableApi applTeiApiBuf;
   I_S32 ret;
  
   applTeiApiBuf.applTei = applTei;
   applTeiApiBuf.status = TEI_NOT_ALLOCATED;
   applTeiApiBuf.applTeiUser = TEI_USR_INVALID;
   applTeiApiBuf.userId = TEI_USRID_INVALID;

   ret = updateApplTeiPoolTable(&applTeiApiBuf); 
   if(ret != CLIB_SUCCESS)
   {
      LOG_PRINT(MAJOR,"updateApplTeiPoolTable failed err:%d", ret); 
   }
   else
   {
   LOG_PRINT(LOG_DEBUG,"deAllocateApplTei: DeAllocated App Tei %d ",applTei);
   }  
   return ret;
}


/********************************* Function  Header*****************************
   Function Name   : addBicTableHandler()
Parameters   : None
Return type   : I_Void
Purpose      : Handler add BIC request from OMC/CLI
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void addBicTableHandler()
{
   I_S32 dbStatus = -1;
   I_S32 ret = -1;
   I_U32 allocatedBicTs = ZERO;
   I_U32 *tsNum, outCount , totalTsRqrd;
   BicTableApi* receivedMsgPtr = ( BicTableApi* )(((I_U8 *)gCfgMsgBuf ) + 
         sizeof(sCmMsg));
   TrunkTableApi* e1TableApiPtr = PNULL;
   TrunkTableIndices e1TableIndicesPtr;
   I_U32 retStatus;
   I_U8 applTei;
   I_U32 e1Num=0xFFFFFFFF;
   I_U32 e1Ts=0xFFFFFFFF;
   OamsCfgBichAddBicReq                oamsCfgBichAddBicReq;
   I_U32 i=0;
   BicE1TeiMapTableApi                 bicE1TeiMapTable;
   BicTableIndices                     bicTableIndices; 
   LOG_PRINT(LOG_INFO,"Entering Function : addBicTableHandler");
   LOG_PRINT(LOG_DEBUG,"addBicTableHandler : Add BIC Request Received For bicId : %d btsType %d,e1Id %u",receivedMsgPtr->bicId,receivedMsgPtr->btsType,receivedMsgPtr->e1Id);

   /* Performed Range Check on received request of add BicTable */
   if(FALSE == bicTableRangeChk(receivedMsgPtr))
   {
      /* Range Check on Table BicTable for Add BIC request is failed. 
       * Sending NACK to OMC/CLI */
      LOG_PRINT(LOG_MAJOR,"addBicTableHandler : Range Check of Received Add \
            BicTable Request is Failed");
      //cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
   }
   else
   {
     /* CS4.0 E1 UsageType Changes : Start*/
     if (receivedMsgPtr->adminState != LOCKED)
     {
       LOG_PRINT(LOG_DEBUG,"addBicTableHandler: Bic addition allowed  in Locked State only");
       cfgSendNackToCm(CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE);
       return;
     }
     /* CS4.0 E1 UsageType Changes : End*/
     /* Check e1Id in BicTable is of type ABISIF* */
     if ((receivedMsgPtr->btsType!=R3_BTS) &&(receivedMsgPtr->btsType!=R2_BTS_IP) )/*R2.8*/
     {
       e1TableIndicesPtr.e1Num = receivedMsgPtr->e1Id;
       dbStatus = getTrunkTable(&e1TableIndicesPtr, &e1TableApiPtr);
       if(DBLIB_SUCCESS != dbStatus)
       {
         /* e1Id received in add BIC request is not configured at BSC. 
          * Sending NACK to OMC/CLI */ 
         LOG_PRINT(LOG_DEBUG,"addBicTableHandler : E1 = %d Received in BicTable\
             Request is Not Configured at BSC",receivedMsgPtr->e1Id);
         cfgSendNackToCm(CM_ERR_E1_NOT_PRESENT_IN_DB);
         return ; 
       }
       else if(SYS_E1_USAGE_ABISIF == e1TableApiPtr->usageType) 
         /*Changes For R2.2 : Start */
       {
         free(e1TableApiPtr);

         numofTsForBic(receivedMsgPtr->btsType, receivedMsgPtr->numTrx,totalTsRqrd);

         ret = isTimeSlotAvailable(receivedMsgPtr->e1Id,totalTsRqrd);  
         if(ret != I_TRUE)
         {
           LOG_PRINT(DEBUG,"isTimeSlotAvailable ret:%d: No Time Slot Available for bic on E1:%d",
               ret,receivedMsgPtr->e1Id);
           cfgSendNackToCm(CM_ERR_NO_FREE_TS_IN_TRUNKPORT);  
           return; 
         }  

         /* Check for Free entries in AbisTimeSlotPerTable For SELF CARD */
         dbStatus = getTsNumTimeSlotPerTable(receivedMsgPtr->e1Id, SYS_TS_USAGE_ABIS_FREE, 
             &tsNum, &outCount);
         if( (dbStatus != DBLIB_SUCCESS) || (outCount < ONE) )
         {
           LOG_PRINT(LOG_MAJOR,"addBicTableHandler: No Free entries found in AbisTimeSlotTable Table. ");
           cfgSendNackToCm(CM_ERR_NO_FREE_TS_IN_TRUNKPORT);  
           return ; 
         }
         allocatedBicTs = *tsNum;
         LOG_PRINT(LOG_INFO,"addBicTableHandler : TimeSlot : %d find in AbisTimeSlotPerTable ",
             allocatedBicTs);
         free(tsNum);
         /*BSC R2.0 Changes Starts*/
         if(CFG_FAILURE == allocateMccLinkResourceForBic(receivedMsgPtr->e1Id,allocatedBicTs ))
         { 
           LOG_PRINT(MAJOR,"allocateMccLinkResourceForBic ret err");
           return;   
         } 

         /*BSC R2.0 Changes Ends*/
       }
       else
       {
         /* E1 in Add BicTable Request cann't be used for ABIS. Rejecting 
          * Add BIC Request. Sending NACK to OMC/CLI */
         free(e1TableApiPtr);
         LOG_PRINT(LOG_DEBUG,"addBicTableHandler : E1 = %d is not Configured \
             for ABIS",receivedMsgPtr->e1Id);
         cfgSendNackToCm(CM_ERR_INVALID_E1_TYPE);
       }
     }
     else
     { /*btsType=R3_BTS/R2_BTS_IP */
       if(allocateApplTei(TEI_USR_BTS,receivedMsgPtr->bicId, &applTei) != CLIB_SUCCESS)
       {
         LOG_PRINT(DEBUG,"applTei allocation Failed");
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         return;
       }
       dbStatus = cfgInsertSwMNodeTableForIpBts(receivedMsgPtr->bicId,receivedMsgPtr->btsType); 
       if(DBLIB_SUCCESS != dbStatus)
       {
         LOG_PRINT(LOG_MAJOR,"addBicTableHandler :  SwMNodeTable Insertion in DB Failed");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
         return CFG_FAILURE;
       }
       /* Add BTS Request is Valid. Going to Add BTS in DB*/

       dbStatus = insertBicTable(receivedMsgPtr);
       if(dbStatus != DBLIB_SUCCESS )
       {
         /* BicTable Insertion in DB Failed */
         LOG_PRINT(LOG_MAJOR,"addBicTableHandler : BicTable Insertion in DB Failed");
         dbStatus=deAllocateApplTei((I_U16)applTei);
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
         return CFG_FAILURE;
       }
       /* Add Row in BicE1TeiMap Table  Changes for R2.8*/
       bicE1TeiMapTable.bicTei = (I_U32)applTei ;
       bicE1TeiMapTable.e1Id = 0xFFFFFFFF;
       bicE1TeiMapTable.e1Ts = 0xFFFFFFFF;
       bicE1TeiMapTable.btsId = receivedMsgPtr->bicId;
       LOG_PRINT(LOG_MAJOR,"addBicTableHandler:insertBicE1TeiMapTable for apptei %d",bicE1TeiMapTable.bicTei);
       dbStatus = insertBicE1TeiMapTable(&bicE1TeiMapTable);
       if(DBLIB_SUCCESS != dbStatus)
       { 
         LOG_PRINT(LOG_MAJOR,"BicTableHandler:insertBicE1TeiMapTableFailed for bicid %d apptei %d",                      receivedMsgPtr->bicId,(I_U32)applTei);
         bicTableIndices.bicId=receivedMsgPtr->bicId;
         dbStatus=deleteBicTable( &bicTableIndices);
         dbStatus=deAllocateApplTei((I_U16)applTei);

         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
         return CFG_FAILURE;
       }

       /* Update BtsData Struct */
       if(getIndex(INVALID_BTS,&i) != CFG_FAILURE)
       {
         gBtsData[i].BTSID = receivedMsgPtr->bicId;
         if(receivedMsgPtr->adminState == 0)
           gBtsData[i].btsState=locked ;
         else
           gBtsData[i].btsState=unlocked ;
         gBtsData[i].btsType= receivedMsgPtr->btsType;
         gBtsData[i].connectivityState= none;
         LOG_PRINT(LOG_DEBUG,"addBicTableHandler : Values of Internal Data : \
             BtsId : %d, btsState : %d, btsType : %d, ConnectivityState : %d",
             gBtsData[i].BTSID,gBtsData[i].btsState,gBtsData[i].btsType,
             gBtsData[i].connectivityState);
         cfgSendAckToCm();
         oamsCfgBichAddBicReq.bicId = receivedMsgPtr->bicId;
         oamsCfgBichAddBicReq.e1Id = e1Num;
         oamsCfgBichAddBicReq.e1Ts = e1Ts;
         oamsCfgBichAddBicReq.btsType = receivedMsgPtr->btsType;
         oamsCfgBichAddBicReq.adminState = receivedMsgPtr->adminState;
         oamsCfgBichAddBicReq.applTei = applTei;
         cfgSendMessage(&oamsCfgBichAddBicReq, sizeof(OamsCfgBichAddBicReq),
             ENT_OAMS_BICH, OAMS_CFG_BICH_ADD_BIC_REQ , 0);
       }
       else
       {
         LOG_PRINT(LOG_MAJOR,"addBicTableHandler : BtsData Structure is full");
         bicTableIndices.bicId=receivedMsgPtr->bicId;
         dbStatus=deleteBicTable( &bicTableIndices);
         dbStatus=deAllocateApplTei((I_U16)applTei);
         cfgSendNackToCm(CM_ERR_MAX_NUM_BTS_EXCEED);
         return CFG_FAILURE;
       } 
     }  
     LOG_PRINT(LOG_INFO,"Exiting Function : addBicTableHandler");
   }   
   
}


/********************************* Function  Header*****************************
   Function Name   : getBicNumConfiguredForE1()
Parameters   : e1Id :: I_U32
Return type   : I_U8
Purpose      : It returns the number of BICs configured for an E1.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_U8 getBicNumConfiguredForE1(I_U32 e1Id)
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   I_U8 retVal = ZERO;
   BicTableApi* bicTableApiPtr = NULL;

   LOG_PRINT(LOG_INFO,"Entering Function : getBicNumConfiguredForE1");
   LOG_PRINT(LOG_DEBUG,"getBicNumConfiguredForE1 : Received e1Id : %d", e1Id);

   dbStatus = getSecBicTable(e1Id, &bicTableApiPtr, &outRow, &outSz);
   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_INFO,"getBicNumConfiguredForE1 : No BIC is Configured For \
            Received e1Id");
   }
   else
   {
      retVal = outRow;
      LOG_PRINT(LOG_DEBUG,"getBicNumConfiguredForE1 : Number of BICs \
            Configured For e1Id %d are %d", e1Id, retVal);
      free(bicTableApiPtr);
   }

   LOG_PRINT(LOG_DEBUG,"getBicNumConfiguredForE1 : Number of BICs \
         Configured For e1Id %d are %d", e1Id, retVal);

   LOG_PRINT(LOG_INFO,"Exiting Function : getBicNumConfiguredForE1");
   return retVal;
}



/********************************* Function  Header*****************************
   Function Name   : isTrxAssociatedWithBic()
Parameters   : bicId :: I_U32
Return type   : I_Bool
Purpose      : It checks whether any TRX is associated with the received 
bicId. It returns TRUE if any TRX is associated with bicId, 
otherwise it returns FALSE.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Bool isTrxAssociatedWithBic(I_U32 bicId)
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   I_Bool retVal = TRUE;
   TrxTableApi* trxTableApiPtr = NULL;

   LOG_PRINT(LOG_INFO,"Entering Function : isTrxAssociatedWithBic");
   LOG_PRINT(LOG_DEBUG,"isTrxAssociatedWithBic : Received bicId : %d", bicId);

   dbStatus = getSecTrxTable(bicId, &trxTableApiPtr, &outRow, &outSz);
   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_INFO,"isTrxAssociatedWithBic : No TRX is Configured For \
            Received bicId");
      retVal = FALSE;
   }
   else
   {
      LOG_PRINT(LOG_DEBUG,"isTrxAssociatedWithBic : Number of TRXs \
            Configured For bicId %d are %d", bicId, outRow);
      free(trxTableApiPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : isTrxAssociatedWithBic");
   return retVal;
}


/********************************* Function  Header*****************************
   Function Name   : getNumConfiguredTrxForBic()
Parameters   : bicId :: I_U32
Return type   : I_U8
Purpose      : It returns the number of TRXs configured for received bicId.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_U8 getNumConfiguredTrxForBic(I_U32 bicId) 
{
   I_S32 dbStatus = -1;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   I_U8 retVal = ZERO;
   TrxTableApi* trxTableApiPtr = NULL;

   LOG_PRINT(LOG_INFO,"Entering Function : getNumConfiguredTrxForBic");
   LOG_PRINT(LOG_DEBUG,"getNumConfiguredTrxForBic : Received bicId : %d", bicId);

   dbStatus = getSecTrxTable(bicId, &trxTableApiPtr, &outRow, &outSz);
   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_INFO,"getNumConfiguredTrxForBic : No TRX is Configured For \
            Received bicId");
   }
   else
   {
      free(trxTableApiPtr);
      retVal = outRow;
   }
   LOG_PRINT(LOG_DEBUG,"getNumConfiguredTrxForBic : Number of TRXs \
         Configured For bicId %d are %d", bicId, retVal);

   LOG_PRINT(LOG_INFO,"Exiting Function : getNumConfiguredTrxForBic");
   return retVal;
}


/********************************* Function  Header*****************************
   Function Name   : addConfiguredBics()
Parameters   : None
Return type   : I_Void
Purpose      : It add all BICs in BSC those configured in BicTable at the 
time OAM Startup.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void addConfiguredBics()
{
   I_S32                               dbStatus = -1;
   I_U32                               outRow = ZERO,outRow1 = ZERO,outRow2=ZERO,outRow3=ZERO;
   I_U16                               outSz = ZERO,outSz1 = ZERO,outSz2=ZERO,outSz3=ZERO;
   I_U32                               index = ZERO, i = ZERO,tempIndex=ZERO;
   I_PVoid                             origPtr = NULL;
   I_PVoid                             origPtr1 = NULL;
   I_PVoid                             origPtr2 = NULL;
   I_S32                               retVal = CFG_FAILURE;
   BicTrxTimeslotUsageTableApi         *bicTrxTimeslotUsageTablePtr = NULL;
   BicTrxTimeslotUsageTableApi         *tempBicTrxTimeslotUsageTablePtr = NULL;
   OamsCfgBichAddBicReq                oamsCfgBichAddBicReq;
   I_U16                               applTei = ZERO;
   BicE1TeiMapTableApi                 bicE1TeiMapTable;
   LapdTEIConfigTableApi*              lapdTeiConfigTableApiPtr = PNULL;
   LapdTEIConfigTableIndices           lapdTeiConfigTableIndicesPtr;
   BicE1TeiMapTableApi                 bicE1TeiMapTable1;
   BicE1TeiMapTableApi                 bicE1TeiMapTable2;
   LapdTEIConfigTableApi*              lapdTeiConfigTableApiPtr1 = PNULL;
   LapdTEIConfigTableIndices           lapdTeiConfigTableIndicesPtr1;
   BicTableIndices                     bicTableIndexPtr ;
   BicTableIndices                     bicTableIndexPtr1 ;
   BicTableApi*                        bicTableApiPtr   = PNULL;
   BicTableApi*                        bicTableApiPtr1   = PNULL;
   E1StreamMapTableApi*                e1StreamMapTableApiPtr = PNULL;
   E1StreamMapTableApi*                e1StreamMapTableApiPtr1 = PNULL;
   E1StreamMapTableIndices             e1StreamMapTableIndicesPtr;
   E1StreamMapTableIndices             e1StreamMapTableIndicesPtr1;
   MccLinkResourceTableApi             *mccLinkTablePtrSelf = NULL;
   MccLinkResourceTableApi             *mccLinkTablePtrSelf1 = NULL;
   I_U32                               rowsSelf  = 0, rowsSelf1 = 0;
   I_U16                               sizeSelf = 0, sizeSelf1 = 0;
   ApplTeiPoolTableSecIndices          applTeiPoolTableSecIndices;
   ApplTeiPoolTableApi*                applTeiPoolTableOutData =PNULL;
   ApplTeiPoolTableApi*                applTeiPoolTable1 =PNULL;

   LOG_PRINT(LOG_INFO,"Entering Function : addConfiguredBics");
   gSentAddBicReqAtInitNum = ZERO;

   dbStatus = getTerBicTrxTimeslotUsageTable(TS_USAGE_BIC, &bicTrxTimeslotUsageTablePtr,
         &outRow, &outSz);
   if(DBLIB_SUCCESS != dbStatus)
   {
      /* No BIC Configured in DB */
      LOG_PRINT(LOG_INFO,"addConfiguredBics : No BIC Configured");
   }
   else
   {
      /* Send Add Bic Request for all bicIds */
      origPtr = bicTrxTimeslotUsageTablePtr;
      for(index = 0; index < outRow; index++)
      {
         bicTrxTimeslotUsageTablePtr = (BicTrxTimeslotUsageTableApi *)(((I_U8 *)(origPtr)) + 
               (index * outSz));
         bicTableIndexPtr.bicId  = bicTrxTimeslotUsageTablePtr->bicOrTrxId;

         if( ( getBicTable(&bicTableIndexPtr, &bicTableApiPtr) ) != CLIB_SUCCESS )
         {
            LOG_PRINT(LOG_INFO,"addConfiguredBics : Bic Not Configured in BicTable for Bic Id =%d",                                                         bicTrxTimeslotUsageTablePtr->bicOrTrxId);
         }
         else
         {
            /* Update BtsData Struct */
            if (getIndex(bicTrxTimeslotUsageTablePtr->bicOrTrxId,&i) != CFG_FAILURE)
            {
#if 0
                 if(bicTableApiPtr->adminState == 0)
                   gBtsData[i].btsState=locked ;
                 else
                   gBtsData[i].btsState=unlocked ;
                 gBtsData[i].btsType= bicTableApiPtr->btsType;
                 gBtsData[i].connectivityState= none;
#endif
                 LOG_PRINT(LOG_DEBUG,"Values of Internal Data : BtsId : %d, btsState : %d, \
                             btsType : %d, ConnectivityState : %d",gBtsData[i].BTSID,
                             gBtsData[i].btsState,gBtsData[i].btsType,gBtsData[i].connectivityState);
                 dbStatus = getFreeMccTrunkNumTsFromMccLinkTable(ICCSELFCARD,SYS_TS_USAGE_ABIS_FREE,bicTrxTimeslotUsageTablePtr->e1Id,bicTrxTimeslotUsageTablePtr->lapdTs,SYS_TS_ALLOCATED, &mccLinkTablePtrSelf, &rowsSelf, &sizeSelf);
                 if(dbStatus != DBLIB_SUCCESS)
                 {
                      LOG_PRINT(LOG_MAJOR,"addConfiguredBics: Require entries not found in MccLinkResource Table. ");
                 }
                 else
                 {
                    /* Get entry from E1StreamMap Table on the basis of mccE1 & mccTS */
                     e1StreamMapTableIndicesPtr.e1Num = mccLinkTablePtrSelf->mccTrunkNum;
                     e1StreamMapTableIndicesPtr.e1Ts = mccLinkTablePtrSelf->mccTrunkTs;
                     dbStatus = getE1StreamMapTable(&e1StreamMapTableIndicesPtr, &e1StreamMapTableApiPtr);
                     if(DBLIB_SUCCESS != dbStatus)
                     {
                          /* Sending NACK to OMC/CLI */ 
                          LOG_PRINT(LOG_DEBUG,"addConfiguredBics : mccTrunkNum = %d and mccTrunkTs = %d \
                                is not found in E1StreamMapTable at BSC",
                                mccLinkTablePtrSelf->mccTrunkNum,mccLinkTablePtrSelf->mccTrunkTs);
                          free(mccLinkTablePtrSelf);
                     }
                     else
                     {

                        /* get applTei from LapdTeiConfigTable on the basis of lapdTimeSlot and lapdTei */
                        free(mccLinkTablePtrSelf);
                        lapdTeiConfigTableIndicesPtr.lapdtimeslot = e1StreamMapTableApiPtr->strmTs;;
                        free(e1StreamMapTableApiPtr);
                        if (bicTableApiPtr->btsType == BIC)
                          lapdTeiConfigTableIndicesPtr.lapdTei = ONE;
                        else  
                          lapdTeiConfigTableIndicesPtr.lapdTei = ZERO;
                        dbStatus = getLapdTEIConfigTable(&lapdTeiConfigTableIndicesPtr, &lapdTeiConfigTableApiPtr);
                        if(DBLIB_SUCCESS != dbStatus)
                        {
                           /* applTei is not found at BSC.*/ 
                           LOG_PRINT(LOG_DEBUG,"addConfiguredBics : lapdTimeslot = %d and lapdTei \
                               is not found in LapdTEIConfigTable at BSC",
                               lapdTeiConfigTableIndicesPtr.lapdtimeslot,lapdTeiConfigTableIndicesPtr.lapdTei);
                        }
                        else
                        {
                           applTei = lapdTeiConfigTableApiPtr->applTei;
                           free(lapdTeiConfigTableApiPtr); 
                           /* Add Row in BicE1TeiMap Table */
                           bicE1TeiMapTable.bicTei = applTei ;
                           bicE1TeiMapTable.e1Id = bicTrxTimeslotUsageTablePtr->e1Id;
                           bicE1TeiMapTable.e1Ts = bicTrxTimeslotUsageTablePtr->lapdTs;
                           /*Changes R2.5 Aricent -- START*/
                           bicE1TeiMapTable.btsId = bicTrxTimeslotUsageTablePtr->bicOrTrxId;
                           /*Changes R2.5 Aricent -- END*/
                           dbStatus = insertBicE1TeiMapTable(&bicE1TeiMapTable);
                           if(DBLIB_SUCCESS != dbStatus)
                           { 
                              LOG_PRINT(LOG_DEBUG,"addConfiguredBics : insert in BicE1TeiMapTableFailed");
                           }
                           else
                           {

                               /* Prepare & Send Add Bic Request */
                               oamsCfgBichAddBicReq.bicId = bicTrxTimeslotUsageTablePtr->bicOrTrxId;
                               oamsCfgBichAddBicReq.e1Id = bicTrxTimeslotUsageTablePtr->e1Id;
                               oamsCfgBichAddBicReq.e1Ts = bicTrxTimeslotUsageTablePtr->lapdTs;
                               oamsCfgBichAddBicReq.btsType = bicTableApiPtr->btsType;
                               oamsCfgBichAddBicReq.adminState = bicTableApiPtr->adminState;
                               oamsCfgBichAddBicReq.applTei = applTei;
         
                               LOG_PRINT(LOG_DEBUG,"addConfiguredBics : Added BIC : %d",
                                  bicTrxTimeslotUsageTablePtr->bicOrTrxId);
                               retVal = cfgSendMessage(&oamsCfgBichAddBicReq, 
                                  sizeof(OamsCfgBichAddBicReq), ENT_OAMS_BICH, 
                                  OAMS_CFG_BICH_ADD_BIC_REQ , 0);
                               if(CFG_SUCCESS == retVal)
                               {
                                  gSentAddBicReqAtInitNum++;
                               }
                           }
                        }
                     }
                 }
            }
            else
            {
                  LOG_PRINT(LOG_MAJOR,"addConfiguredBics : BtsData Structure is full");
            } 
                 /* Mantis 7843 */
            free(bicTableApiPtr);
         }
         /* Mantis 7843 */

      }
      free(origPtr);
   }
   /* Change For R2.2 : Start Here */
   dbStatus = getTerBicTrxTimeslotUsageTable(TS_USAGE_BTS, &tempBicTrxTimeslotUsageTablePtr,&outRow1, &outSz1);
   if(DBLIB_SUCCESS != dbStatus)
   {
      /* No BIC Configured in DB */
      LOG_PRINT(LOG_INFO,"addConfiguredBics : No BTS Configured");
   }
   else
   {
      /* Send Add Bic Request for all bicIds */
      origPtr1 = tempBicTrxTimeslotUsageTablePtr;
      for(index = 0; index < outRow1; index++)
      {
         tempBicTrxTimeslotUsageTablePtr = (BicTrxTimeslotUsageTableApi *)(((I_U8 *)(origPtr1)) + 
               (index * outSz1));
           bicTableIndexPtr1.bicId  = tempBicTrxTimeslotUsageTablePtr->bicOrTrxId;

         if( ( getBicTable(&bicTableIndexPtr1, &bicTableApiPtr1) ) != CLIB_SUCCESS )
         {
            LOG_PRINT(LOG_INFO,"addConfiguredBics : Bic Not Configured in BicTable for Bic Id =%d",bicTrxTimeslotUsageTablePtr->bicOrTrxId);
         }
         else
         {
            /* Update BtsData Struct */
            if (getIndex(tempBicTrxTimeslotUsageTablePtr->bicOrTrxId,&i) != CFG_FAILURE)
            {
#if 0
                 if(bicTableApiPtr1->adminState == 0)
                   gBtsData[i].btsState=locked ;
                 else
                   gBtsData[i].btsState=unlocked ;
                 gBtsData[i].btsType= bicTableApiPtr1->btsType;
                 gBtsData[i].connectivityState= none;
#endif
                 LOG_PRINT(LOG_DEBUG,
										"Values of Internal Data : BtsId : %d, btsState : %d,btsType : %d, ConnectivityState : %d",
                             gBtsData[i].BTSID,gBtsData[i].btsState,
                             gBtsData[i].btsType,gBtsData[i].connectivityState);

                 dbStatus = getFreeMccTrunkNumTsFromMccLinkTable(ICCSELFCARD,SYS_TS_USAGE_ABIS_FREE,tempBicTrxTimeslotUsageTablePtr->e1Id,tempBicTrxTimeslotUsageTablePtr->lapdTs,SYS_TS_ALLOCATED, &mccLinkTablePtrSelf1, &rowsSelf1, &sizeSelf1);
                 if(dbStatus != DBLIB_SUCCESS) 
                 {
                      LOG_PRINT(LOG_MAJOR,"addConfiguredBics: Require entries not found in MccLinkResource Table. ");
                 }
                 else
                 {
                    /* Get entry from E1StreamMap Table on the basis of mccE1 & mccTS */
                     e1StreamMapTableIndicesPtr1.e1Num = mccLinkTablePtrSelf1->mccTrunkNum;
                     e1StreamMapTableIndicesPtr1.e1Ts = mccLinkTablePtrSelf1->mccTrunkTs;
                     dbStatus = getE1StreamMapTable(&e1StreamMapTableIndicesPtr1, &e1StreamMapTableApiPtr1);
                     if(DBLIB_SUCCESS != dbStatus)
                     {
                          /* Sending NACK to OMC/CLI */ 
                          LOG_PRINT(LOG_DEBUG,"addConfiguredBics : mccTrunkNum = %d and mccTrunkTs = %d \
                                is not found in E1StreamMapTable at BSC",
                                mccLinkTablePtrSelf1->mccTrunkNum,mccLinkTablePtrSelf1->mccTrunkTs);
                          free(mccLinkTablePtrSelf1);
                     }
                     else
                     {
                          /* get applTei from LapdTeiConfigTable on the basis of lapdTimeSlot and lapdTei */
                          free(mccLinkTablePtrSelf1);
                          lapdTeiConfigTableIndicesPtr1.lapdtimeslot = e1StreamMapTableApiPtr1->strmTs;
                          free(e1StreamMapTableApiPtr1);
                          if (bicTableApiPtr1->btsType == BIC)
                               lapdTeiConfigTableIndicesPtr1.lapdTei = ONE;
                          else  
                               lapdTeiConfigTableIndicesPtr1.lapdTei = ZERO;
                          dbStatus = getLapdTEIConfigTable(&lapdTeiConfigTableIndicesPtr1, &lapdTeiConfigTableApiPtr1);
                          if(DBLIB_SUCCESS != dbStatus)
                          {
                             /* applTei is not found at BSC.*/ 
                             LOG_PRINT(LOG_DEBUG,"addConfiguredBics : lapdTimeslot = %d and lapdTei %d \
                              is not found in LapdTEIConfigTable at BSC",
                              lapdTeiConfigTableIndicesPtr1.lapdtimeslot,lapdTeiConfigTableIndicesPtr1.lapdTei);
                           }
                           else
                           {
                              applTei = lapdTeiConfigTableApiPtr1->applTei;
                              free(lapdTeiConfigTableApiPtr1); 
                              /* Add Row in BicE1TeiMap Table */
                              bicE1TeiMapTable1.bicTei = applTei ;
                              bicE1TeiMapTable1.e1Id = tempBicTrxTimeslotUsageTablePtr->e1Id;
                              bicE1TeiMapTable1.e1Ts = tempBicTrxTimeslotUsageTablePtr->lapdTs;
                              /*Changes R2.5 Aricent -- START*/
                              bicE1TeiMapTable1.btsId = tempBicTrxTimeslotUsageTablePtr->bicOrTrxId;
                              /*Changes R2.5 Aricent -- END*/
                              dbStatus = insertBicE1TeiMapTable(&bicE1TeiMapTable1);
                              if(DBLIB_SUCCESS != dbStatus)
                              { 
                                 LOG_PRINT(LOG_DEBUG,"addConfiguredBics : insert in BicE1TeiMapTableFailed");
                              }
                              else
                              {
                                 /* Premapare & Send Add Bic Request */
                                 oamsCfgBichAddBicReq.bicId = tempBicTrxTimeslotUsageTablePtr->bicOrTrxId;
                                 oamsCfgBichAddBicReq.e1Id = tempBicTrxTimeslotUsageTablePtr->e1Id;
                                 oamsCfgBichAddBicReq.e1Ts = tempBicTrxTimeslotUsageTablePtr->lapdTs;
                                 oamsCfgBichAddBicReq.btsType = bicTableApiPtr1->btsType;
                                 oamsCfgBichAddBicReq.adminState = bicTableApiPtr1->adminState;
                                 oamsCfgBichAddBicReq.applTei = applTei;
          
                                 LOG_PRINT(LOG_DEBUG,"addConfiguredBics : Added BIC : %d",
                                    tempBicTrxTimeslotUsageTablePtr->bicOrTrxId);
                                 retVal = cfgSendMessage(&oamsCfgBichAddBicReq, 
                                      sizeof(OamsCfgBichAddBicReq), ENT_OAMS_BICH, 
                                      OAMS_CFG_BICH_ADD_BIC_REQ , 0);
                                 if(CFG_SUCCESS == retVal)
                                 {
                                    gSentAddBicReqAtInitNum++;
                                 }
                              }
                           }
                     }
                 }
            }
            else
            {
                  LOG_PRINT(LOG_MAJOR,"addConfiguredBics : BtsData Structure is not Correct");
            } 
 
         /* Mantis 7843 */
        
            free(bicTableApiPtr1);
         }
            
      }
      free(origPtr1);
   }

/* Changes for R2.8 Starts*/
    bicTableApiPtr   = PNULL;
    dbStatus = getallBicTable(&bicTableApiPtr,&outRow2,&outSz2);
    if(DBLIB_SUCCESS != dbStatus)
    {
       LOG_PRINT(LOG_MAJOR,"addConfiguredBics: Get Form BicTable Failed");
       return; 
    }

    origPtr2= bicTableApiPtr;
    for(tempIndex=0;tempIndex <outRow2;tempIndex++)
    {
       bicTableApiPtr1 = (BicTableApi *)((I_U8 *)origPtr2 + (tempIndex * outSz2));
        
       LOG_PRINT(LOG_INFO,"addConfiguredBts :Index %d,btsType %d,outCount %d bicId %d",tempIndex,
           bicTableApiPtr1->btsType,outRow2,bicTableApiPtr1->bicId);
       if((bicTableApiPtr1->btsType ==R2_BTS_IP)||(bicTableApiPtr1->btsType ==R3_BTS) )   
       {
            if (getIndex(bicTableApiPtr1->bicId,&i) != CFG_FAILURE)
               {
               applTeiPoolTableSecIndices.applTeiUser=(I_U8)TEI_USR_BTS;
               applTeiPoolTableSecIndices.userId=bicTableApiPtr1->bicId; 
               applTeiPoolTableOutData=PNULL; 
               dbStatus = getSecApplTeiPoolTable(&applTeiPoolTableSecIndices, &applTeiPoolTableOutData,
                          &outRow3, &outSz3);
               if(DBLIB_SUCCESS != dbStatus)
                  {
                   LOG_PRINT(LOG_MAJOR,"addConfiguredBics: Get appTei failed for Bic Id %d btsType %d",
                   bicTableApiPtr1->bicId,bicTableApiPtr1->btsType);
                  }
                 else
                  {              
                   applTeiPoolTable1=(ApplTeiPoolTableApi*)((I_U8 *)(applTeiPoolTableOutData) +(ZERO));
                   LOG_PRINT(LOG_INFO,"getSecApplTeiPoolTable :Index %d,btsType %d,bicId %d, applTei %d",tempIndex,
           bicTableApiPtr1->btsType,bicTableApiPtr1->bicId,applTeiPoolTable1->applTei);
                   
                    /* Add Row in BicE1TeiMap Table  Changes for R2.8*/
                    bicE1TeiMapTable2.bicTei = (I_U32)applTeiPoolTable1->applTei ;
                    bicE1TeiMapTable2.e1Id = 0xFFFFFFFF;
                    bicE1TeiMapTable2.e1Ts = 0xFFFFFFFF;
                    bicE1TeiMapTable2.btsId = bicTableApiPtr1->bicId;
                    
       LOG_PRINT(LOG_INFO,"insertBicE1TeiMapTable :Index %d,btsType %d,bicId %d, applTei %u",tempIndex,
           bicTableApiPtr1->btsType,bicE1TeiMapTable2.btsId,bicE1TeiMapTable2.bicTei);
                    dbStatus = insertBicE1TeiMapTable(&bicE1TeiMapTable2);
                    if(DBLIB_SUCCESS != dbStatus)
                      { 
                      LOG_PRINT(LOG_MAJOR,"insertBicE1TeiMapTableFailed for bicid %d, ApplTei %u",                      bicTableApiPtr1->bicId,bicE1TeiMapTable2.bicTei);
                      }
                      else
                      {  
                      /* Premapare & Send Add Bic Request */
                                 oamsCfgBichAddBicReq.bicId = bicTableApiPtr1->bicId;
                                 oamsCfgBichAddBicReq.e1Id = 0xFFFFFFFF;
                                 oamsCfgBichAddBicReq.e1Ts = 0xFFFFFFFF;
                                 oamsCfgBichAddBicReq.btsType = bicTableApiPtr1->btsType;
                                 oamsCfgBichAddBicReq.adminState = bicTableApiPtr1->adminState;
                                 oamsCfgBichAddBicReq.applTei = applTeiPoolTable1->applTei;
          
                                 LOG_PRINT(LOG_DEBUG,"addConfiguredBics : Added BIC : %d, applTei %d",
                                    bicTableApiPtr1->bicId ,oamsCfgBichAddBicReq.applTei);
                                 retVal = cfgSendMessage(&oamsCfgBichAddBicReq, 
                                      sizeof(OamsCfgBichAddBicReq), ENT_OAMS_BICH, 
                                      OAMS_CFG_BICH_ADD_BIC_REQ , 0);
                                 if(CFG_SUCCESS == retVal)
                                 {
                                    gSentAddBicReqAtInitNum++;
                                 }
                      }
                 free(applTeiPoolTableOutData);  
                 }
                 
               }
               else
               {
               LOG_PRINT(LOG_MAJOR,"addConfiguredBics: Get CFG index failed for Bic Id %d btsType %d",
                   bicTableApiPtr1->bicId,bicTableApiPtr1->btsType);
               }  

       }
    }
  free(origPtr2);  
/* Changes for R2.8 Ends*/
   LOG_PRINT(LOG_INFO,"Exiting Function : addConfiguredBics");
}


/********************************* Function  Header*****************************
   Function Name   : sndSwitchConForBicsAtInit()
Parameters   : None
Return type   : I_Void
Purpose      : It calculate first E1 & TS and then call function 
prepAndSndSwitchConForBic that prepare & send Switch Connect 
to GRHM.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void sndSwitchConForBicsAtInit()
{
    I_S32 dbStatus = -1;
    I_U32 outRow = ZERO, index = ZERO;
    I_U16 outSz;
    I_U32 tsUser = ZERO;
    I_U32 e1Id = ZERO, e1Ts = ZERO, i = ZERO;
    I_S32 status = ZERO;
    BicTableApi *bicTableApiPtr = NULL;
    I_PVoid origPtr = NULL;
     /*Changes For R2.2 :Start */

    LOG_PRINT(LOG_INFO,"Entering Function : sndSwitchConForBicsAtInit");
    dbStatus = getallBicTable(&bicTableApiPtr,&outRow,&outSz);
    if(DBLIB_SUCCESS != dbStatus)
    {
        LOG_PRINT(LOG_MAJOR,"sndSwitchConForBicsAtInit : Get Form BicTable Failed");
    }
    else
    {
        origPtr =  bicTableApiPtr;
        for(index = 0; index < outRow; index++)
        {
            bicTableApiPtr = (BicTableApi *)(((I_U8 *)(origPtr)) + (index * outSz));
            if((bicTableApiPtr->btsType==R2_BTS_IP) ||(bicTableApiPtr->btsType==R3_BTS))
            continue;  
            status=getIndex(bicTableApiPtr->bicId,&i);
            if(CFG_FAILURE == status)
            {
                LOG_PRINT(LOG_MAJOR,"sndSwitchConForBicsAtInit :getIndex  Failed");
                continue;
            }
            if (gBtsData[i].btsType == BIC)
                tsUser =  TS_USAGE_BIC;
            else if(gBtsData[i].btsType == R2_BTS)
                tsUser =  TS_USAGE_BTS;

            status = getE1TsFromBicTrxTimeslotUsageTable(tsUser, 
                    bicTableApiPtr->bicId, &e1Id, &e1Ts);
            if(CFG_FAILURE == status)
            {
                LOG_PRINT(LOG_MAJOR,"sndSwitchConForBicsAtInit : Get Form \
                        BicTrxTimeSlotUsageTable Failed");
                continue;
            }
            if(bicTableApiPtr->btsConnectivityState == BTS_CONNECT)
            {
                if(CFG_FAILURE == prepAndSndSwitchConForBic(e1Id,e1Ts))
                {
                    LOG_PRINT(LOG_MAJOR,"Switch Connect Failed");
                    continue;
                }
                else
                {
                    gBtsData[i].connectivityState = none;
                }
            }
            if(bicTableApiPtr->btsConnectivityState == BTS_DISCONNECT)
            {
                if(CFG_FAILURE == prepAndSndSwitchDisConForBic(e1Id,e1Ts))
                {
                    LOG_PRINT(LOG_MAJOR,"Switch DisConnect Failed");
                    continue;
                }
            }
            /*Changes For R2.2 :End */

        }
        free(origPtr);

    }


    LOG_PRINT(LOG_INFO,"Exiting Function : sndSwitchConForBicsAtInit");
}


/********************************* Function  Header*****************************
   Function Name   : prepAndSndSwitchConForBic()
Parameters   : firstE1 :: I_U32
firstTs :: I_U32
Return type   : I_S32
Purpose      : It calculate second E1 & TS corresponding to the received
first E1 & Ts and send Switch Connect message to GRHM.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_S32 prepAndSndSwitchConForBic(I_U32 firstE1, I_U32 firstTs)
{
   I_U32 status = CFG_FAILURE;
   I_U32 secE1 = ZERO;
   I_U32 secTs = ZERO;
   OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnect;

   LOG_PRINT(LOG_INFO,"Entering Function : prepAndSndSwitchConForBic");
   LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchConForBic : Received firstE1 : %d, \
         firstTs : %d ",firstE1, firstTs);

   /* Get second E1 & Ts */ 
   status = getMccE1Ts(firstE1, firstTs, &secE1, &secTs);
   if(CFG_FAILURE == status)
   {
      /* Mcc E1 or Ts not configured */
      LOG_PRINT(LOG_INFO,"prepAndSndSwitchConForBic : Mcc E1 & Ts not \
            Configured");
   }
   else
   {
      oamsCfgGrhmSwitchConnect.firstE1Num = firstE1;
      oamsCfgGrhmSwitchConnect.firstTimeSlotNum = firstTs;
      oamsCfgGrhmSwitchConnect.secondE1Num = secE1;
      oamsCfgGrhmSwitchConnect.secondTimeSlotNum = secTs;
      LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchConForBic : First E1 : %d, \
            First Ts : %d, SecE1 : %d, SecTs : %d",\
            firstE1, firstTs, secE1, secTs);

      cfgSendMessage(&oamsCfgGrhmSwitchConnect, sizeof(OamsCfgGrhmSwitchConnect),
            ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0);
   }

   /*Changes for HA-R2.5.5*/ 
   if(CFG_READY == gCfgState || gCfgState == CFG_BPM_SW_QUERY)
   {
      if(gCfgStandbySlotId != 0)
      { 
          sendLapdSwitchReqToPeerCfg(firstE1, firstTs,CFG_MAKE_SWITCH,CFG_SWITCH_BTS_ADD_DEL);
      }
   }
   /*Changes for HA-R2.5.5*/ 

   LOG_PRINT(LOG_INFO,"Exiting Function : prepAndSndSwitchConForBic");
   return status;
}


/********************************* Function  Header*****************************
   Function Name   : prepAndSndSwitchDisConForBic()
Parameters   : firstE1 :: I_U32
firstTs :: I_U32
Return type   : I_S32
Purpose      : It calculate second E1 & TS corresponding to the received 
first E1 & Ts and send Switch DisConnect message to GRHM.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_S32 prepAndSndSwitchDisConForBic(I_U32 firstE1, I_U32 firstTs)
{
   I_U32 status = CFG_FAILURE;
   I_U32 secE1 = ZERO;
   I_U32 secTs = ZERO;
   OamsCfgGrhmSwitchDisconnect oamsCfgGrhmSwitchDisconnect;

   LOG_PRINT(LOG_INFO,"Entering Function : prepAndSndSwitchDisConForBic");
   LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchDisConForBic : Received firstE1 : %d, \
         firstTs : %d ",firstE1, firstTs);

   /* Get second E1 & Ts */ 
   status = getMccE1Ts(firstE1, firstTs, &secE1, &secTs);
   if(CFG_FAILURE == status)
   {
      /* Mcc E1 or Ts not configured */
      LOG_PRINT(LOG_INFO,"prepAndSndSwitchDisConForBic : Mcc E1 & Ts not \
            Configured");
   }
   else
   {
      oamsCfgGrhmSwitchDisconnect.firstE1Num = firstE1;
      oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum = firstTs;
      oamsCfgGrhmSwitchDisconnect.secondE1Num = secE1;
      oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum = secTs;
      LOG_PRINT(LOG_DEBUG,"prepAndSndSwitchDisConForBic : First E1 : %d, \
            First Ts : %d, SecE1 : %d, SecTs : %d",\
            firstE1, firstTs, secE1, secTs);

      cfgSendMessage(&oamsCfgGrhmSwitchDisconnect, sizeof(OamsCfgGrhmSwitchDisconnect),
            ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_DISCONNECT, 0);
   }
   /*Changes for HA-R2.5.5*/ 
   if(CFG_READY == gCfgState || gCfgState == CFG_BPM_SW_QUERY)
   {
      if(gCfgStandbySlotId != 0)
      { 
          sendLapdSwitchReqToPeerCfg(firstE1, firstTs,CFG_BREAK_SWITCH,CFG_SWITCH_BTS_ADD_DEL);
      }
   }
   /*Changes for HA-R2.5.5*/ 

   LOG_PRINT(LOG_INFO,"Exiting Function : prepAndSndSwitchDisConForBic");
   return status;
}

/********************************* Function  Header*****************************
 Function Name   : getE1TsFromBicTrxTimeslotUsageTable()
Parameters   : tsUser :: I_U32
bicOrTrxId :: I_U32
e1Id :: I_U32*
e1Ts :: I_U8*
Return type   : I_S32
Purpose      : It get e1Id and timeslot from BicTrxTimeslotUsageTable
according to the received tsUser and bicOrTrxId values.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_S32 getE1TsFromBicTrxTimeslotUsageTable(I_U32 tsUser, I_U32 bicOrTrxId, I_U32 *e1Id, I_U32 *e1Ts)
{
   I_S32 dbStatus = -1;
   I_S32 retVal = CFG_FAILURE;
   BicTrxTimeslotUsageTableApi* bicTrxTimeslotUsageTablePtr = NULL;
   BicTrxTimeslotUsageTableIndices bicTrxTimeslotUsageTableInd;

   LOG_PRINT(LOG_INFO,"Entering Function : getE1TsFromBicTrxTimeslotUsageTable");
   LOG_PRINT(LOG_DEBUG,"getE1TsFromBicTrxTimeslotUsageTable : Received tsUser : %d, bicOrTrxId : %d",
         tsUser, bicOrTrxId);

   bicTrxTimeslotUsageTableInd.tsUser = tsUser;
   bicTrxTimeslotUsageTableInd.bicOrTrxId = bicOrTrxId;
   dbStatus = getBicTrxTimeslotUsageTable(&bicTrxTimeslotUsageTableInd, &bicTrxTimeslotUsageTablePtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_INFO,"getE1TsFromBicTrxTimeslotUsageTable : Get on Table BicTrxTimeslotUsageTable Failed");
   }
   else
   {
      *e1Id = bicTrxTimeslotUsageTablePtr->e1Id;
      *e1Ts = bicTrxTimeslotUsageTablePtr->lapdTs;/* Change for R2.2*/
      retVal = CFG_SUCCESS;
      free(bicTrxTimeslotUsageTablePtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : getE1TsFromBicTrxTimeslotUsageTable");
   return retVal;
}

/* CS4.0 E1 UsageType Changes : Start*/
/********************************* Function  Header*****************************
  Function Name   : bicLockUnlockHandler()
Parameters   : 
Return type  : I_Void
Purpose      : To perform validity checks for performing bic Lock/Unlock operation.
Other Note   : Added For BSC CS4.0
 *******************************************************************************/
I_Void  bicLockUnlockHandler()
{
   TrunkTableApi *e1TablePtr = NULL;
   TrunkTableIndices e1TableIndices;
   I_U32 i = ZERO;

   BicTableApi* receivedMsgPtr =(BicTableApi*)(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));
   LOG_PRINT(LOG_INFO,"bicLockUnlockHandler : Enter in Function ");

   LOG_PRINT(LOG_INFO,"bicLockUnlockHandler : Received BicId %u, E1Id: %u",receivedMsgPtr->bicId,receivedMsgPtr->e1Id);
   LOG_PRINT(LOG_INFO,"bicLockUnlockHandler : AdminState: %u",receivedMsgPtr->adminState);
   /*Changes For R2.2 :Start */
   
   if (receivedMsgPtr->adminState != LOCKED &&
         receivedMsgPtr->adminState != UNLOCKED)
   {
      LOG_PRINT(LOG_DEBUG,"bicLockUnlockHandler : Invalid adminState received");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
      return;
   }
if( (receivedMsgPtr->btsType!=R3_BTS)&& (receivedMsgPtr->btsType!=R2_BTS_IP) )
 {/*Changes for R2.8 */
   
   e1TableIndices.e1Num = receivedMsgPtr->e1Id;
   if(CLIB_SUCCESS != getTrunkTable(&e1TableIndices, &e1TablePtr))
   {
      LOG_PRINT(LOG_MAJOR,"bicLockUnlockHandler : e1Id : %d Received in Request is Not Configured at BSC",
            receivedMsgPtr->e1Id);
      cfgSendNackToCm(CM_ERR_E1_NOT_PRESENT_IN_DB);
      return;
   }
   free(e1TablePtr);
   if(gE1Data[receivedMsgPtr->e1Id].e1State == unlockInProgress )
   {
       LOG_PRINT(LOG_INFO,"bicLockUnlockHandler : Abis E1 Unlock in progress. Can not lock/unlock Bic/Bts. ");
       cfgSendNackToCm(CM_ERR_E1_UNLOCK_IN_PROGRESS);
       return;
   }
   else if(gE1Data[receivedMsgPtr->e1Id].e1State == lockInProgress)
   {
       LOG_PRINT(LOG_INFO,"bicLockUnlockHandler : Abis E1 Lock in progress. Can not lock/unlock Bic/Bts. ");
       cfgSendNackToCm(CM_ERR_E1_LOCK_IN_PROGRESS);
       return;
   }
 } 
   if (getIndex(receivedMsgPtr->bicId,&i)!=CFG_FAILURE)
   {
     if ((gBtsData[i].btsState) == unlockInProgress)
     {
       LOG_PRINT(LOG_DEBUG,"bicLockUnlockHandler : Bic is Unlock In Progress");
       cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
       return;
     }
     if (gBtsData[i].btsState == lockInProgress)
     {
       LOG_PRINT(LOG_DEBUG,"bicLockUnlockHandler : Bic is lock In Progress");
       cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
       return;
     }
   }
   else
   {
     LOG_PRINT(LOG_MAJOR,"bicLockUnlockHandler : BIC is not find in BtsData");
     cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
       return;
   }
   /*Changes For R2.2 :Start */
   if (receivedMsgPtr->adminState == LOCKED)
   {
      bicLockProcedure(receivedMsgPtr->bicId);
   }
   else if (receivedMsgPtr->adminState == UNLOCKED)
   {
      bicUnlockProcedure(receivedMsgPtr->bicId);
   }
   LOG_PRINT(LOG_INFO,"bicLockUnlockHandler : Exiting Function ");
}

/********************************* Function  Header*****************************
  Function Name   : bicLockProcedure()
Parameters   : I_U32 bicId
Return type  : I_Void
Purpose      : To perform Bic Lock Procedure 
Other Note   : Added For BSC CS4.0
 *******************************************************************************/
I_Void bicLockProcedure(I_U32 bicId)
{
   I_U32 i;
   OamsCfgBichLockReq oamsCfgBichLockReq;
   oamsCfgBichLockReq.bicId = bicId;
   /*Changes For R2.2 :Start */
   LOG_PRINT(LOG_INFO,"bicLockProcedure : Enter in Function ");
   if (getIndex(bicId,&i) != CFG_FAILURE )
   {
     gBtsData[i].btsState = lockInProgress;
     cfgSendMessage(&oamsCfgBichLockReq, sizeof(OamsCfgBichLockReq),
                  ENT_OAMS_BICH, OAMS_CFG_BICH_LOCK_REQ , 0);
     cfgSendAckToCm(); 
   }
   else
   {
     LOG_PRINT(LOG_MAJOR,"bicLockProcedure : BIC is not find in BtsData");
     cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
   }    
   LOG_PRINT(LOG_INFO,"bicLockProcedure : Exiting Function ");
   /*Changes For R2.2 :End */
    
}

/********************************* Function  Header*****************************
  Function Name   : bicUnlockProcedure()
Parameters   : I_U32 bicId
Return type  : I_Void
Purpose      : To perform Bic Unlock Procedure 
Other Note   : Added For BSC CS4.0
 *******************************************************************************/
I_Void bicUnlockProcedure(I_U32 bicId)
{
   OamsCfgBichUnlockReq oamsCfgBichUnlockReq;
   I_U8 chasisFrameId,slotId;
   I_U32 swStatus,i;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   BicTableIndices bicTblIndx;
   BicTableApi *outData;
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   I_U32 counter = 0;
   TrxTableApi *trxTableApiPtr = NULL,*trxTempApiPtr = NULL;
   CellPerTableApi *pCellData=NULL;

   LOG_PRINT(LOG_INFO,"bicUnlockProcedure : Enter in Function ");

    /*Changes For R2.2 :Start */

   /* Get Active ChasisFrameId and SlotId */
   LOG_PRINT(LOG_INFO, "bicUnlockProcedure : Going to get Active ChasisFrameId and SlotId ");
   if (getActiveIccSlotId(&chasisFrameId,&slotId)!=CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_CRITICAL,"bicUnlockProcedure : getActive ChasisFrameId and slotId DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
   }
   /* Get Status of Bic From SwMNode Table */
   if (getIndex(bicId,&i) == CFG_FAILURE)
   {
       LOG_PRINT(LOG_MAJOR,"bicUnlockProcedure : BIC is not find in BtsData");
       cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
       return;
   }

//if( (gBtsData[i].btsType!=R3_BTS)&& (gBtsData[i].btsType!=R2_BTS_IP) )
 // {/*Changes for R2.8*/   
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   if(gBtsData[i].btsType == R2_BTS)
      sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_R2_BTS;
   if(gBtsData[i].btsType == BIC)
      sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_BIC;
   if(gBtsData[i].btsType == R2_BTS_IP)
      sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_R2_BTS_IP;
   if(gBtsData[i].btsType == R3_BTS)
      sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_R3_BTS;
   sApiSwMNodeTableIndices.nodeIdentity = bicId;
   if (CLIB_SUCCESS == getSwStatusFromSwMNodeTable(sApiSwMNodeTableIndices,&swStatus))
   {
    LOG_PRINT(LOG_INFO,"bicUnlockProcedure : get S/w Status DB call is getting SuccessFul.");
    if((swStatus == SW_ACTIVATION_IN_PROGRESS)||(swStatus == SW_DOWNLOAD_IN_PROGRESS))
    {
      LOG_PRINT(LOG_DEBUG,"bicUnlockProcedure : Either Download or Activation is in progress ");
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
    }
    LOG_PRINT(LOG_INFO, "bicUnlockProcedure : Either Download or Activation is not in progress ");

   }
 //}
   /*R2.9 Changes manits 27741 starts*/   
   bicTblIndx.bicId = bicId;
   if(getBicTable(&bicTblIndx,&outData) != CLIB_SUCCESS)
   {
      LOG_PRINT(MAJOR,"getBicTable failed for bicId:%d",bicId);
      cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
      return ; 
   }
   else
   {
      if(getSecTrxTable(bicId, &trxTableApiPtr, &outRow, &outSz) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"bicUnlockProcedure : No TRX is Configured For \
            bicId %d",bicId);
      }
      else
      {
         for(counter = 0;counter<outRow;counter++)
         {
           trxTempApiPtr = (TrxTableApi *)((I_U8 *)trxTableApiPtr + counter*(sizeof(TrxTableApi)));
           if(getCellIdLacCellIdxFromCellPerTable(trxTempApiPtr->antennaID,&pCellData) != CLIB_SUCCESS)
           {
              LOG_PRINT(LOG_INFO,"bicUnlockProcedure : No Cell is Configured with \
                antennaId %d",trxTempApiPtr->antennaID);
           }
           else
           {
             if(pCellData->bcchPwr > outData->maxRfPwrConf)
             {  
                LOG_PRINT(LOG_CRITICAL,"BcchPwr in Cell %d > RfMaxPwr %d in trx %d",
                        pCellData->bcchPwr,outData->maxRfPwrConf);
                cfgSendNackToCm(CM_ERR_CELL_BCCH_PWR_WRONG);
                free(pCellData);
                free(outData);
                free(trxTableApiPtr);
                return ; 
             }
             free(pCellData);
           }
         }
         free(trxTableApiPtr);
      }
      free(outData);
   }
   /*R2.9 Changes manits 27741 end*/   

      oamsCfgBichUnlockReq.bicId = bicId;
      gBtsData[i].btsState = unlockInProgress;
      cfgSendMessage(&oamsCfgBichUnlockReq, sizeof(OamsCfgBichUnlockReq),
                  ENT_OAMS_BICH, OAMS_CFG_BICH_UNLOCK_REQ , 0);
      cfgSendAckToCm(); 
   
   
  /*Changes For R2.2 :End */
       
   LOG_PRINT(LOG_INFO,"bicUnlockProcedure : Exiting Function ");
}

/********************************* Function  Header*****************************
  Function Name   : updateStateAndSendBicLockAlarm()
Parameters   : I_U32 bicId
Return type  : I_Void
Purpose      : To update adminState in DB and sending Bic Lock alarm 
Other Note   : Added For BSC CS4.0
 *******************************************************************************/
I_Void updateStateAndSendBicLockAlarm(I_U32 bicId)
{
   OamsCfgAfhSysAlarm sysAlarmBuff ;
   I_U32 i;
   memset(&sysAlarmBuff,0,sizeof(OamsCfgAfhSysAlarm));
   LOG_PRINT(LOG_INFO,"updateStateAndSendBicLockAlarm : Entering Function ");
   if(updateBicAdminState(bicId,LOCKED) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"updateStateAndSendBicLockAlarm : Updation of AdminState in BicTable Failed For BicId: %d",bicId);
      return;
   }
   /*Changes For R2.2 :Start */
   if (getIndex(bicId,&i) != CFG_FAILURE )
   {
      gBtsData[i].btsState = locked;
   /*Changes For R2.2 :End */

     /*Sending the Alarm...*/
      LOG_PRINT(LOG_INFO,"updateStateAndSendBicLockAlarm : Sending ALARM: ALARM_BIC_LOCK_COMPLETED");
      sysAlarmBuff.sysAlarm.sysalarmId = ALARM_BIC_LOCK_COMPLETED;
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
      sysAlarmBuff.sysAlarm.key1 = bicId; 
      sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
      sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
         "Bts Lock for BtsId: %u is successfully completed",bicId);
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
          ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"updateStateAndSendBicLockAlarm : Bts is not find in BtsData Structure");
   }
   LOG_PRINT(LOG_INFO,"updateStateAndSendBicLockAlarm : Exiting Function ");
}

/********************************* Function  Header*****************************
  Function Name   : updateStateAndSendBicUnlockAlarm()
Parameters   : I_U32 bicId
Return type  : I_Void
Purpose      : To update adminState in DB and sending Bic Unlock alarm 
Other Note   : Added For BSC CS4.0
 *******************************************************************************/
I_Void updateStateAndSendBicUnlockAlarm(I_U32 bicId)
{
   OamsCfgAfhSysAlarm sysAlarmBuff ;
   I_U32 i = ZERO;
   LOG_PRINT(LOG_INFO,"updateStateAndSendBicUnlockAlarm : Entering Function ");
   memset(&sysAlarmBuff,0,sizeof(OamsCfgAfhSysAlarm));

   if(updateBicAdminState(bicId,UNLOCKED) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"updateStateAndSendBicUnlockAlarm : Updation of AdminState in BicTable Failed For BicId: %d",bicId);
      return;
   }
   /*Changes For R2.2 :Start */
   if( getIndex(bicId,&i) != CFG_FAILURE)
   {
      gBtsData[i].btsState = unlocked;
   /*Changes For R2.2 :End */

      /*Sending the Alarm...*/
      LOG_PRINT(LOG_INFO,"updateStateAndSendBicUnlockAlarm : Sending ALARM: ALARM_BIC_UNLOCK_COMPLETED");
      sysAlarmBuff.sysAlarm.sysalarmId = ALARM_BIC_UNLOCK_COMPLETED;
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
      sysAlarmBuff.sysAlarm.key1 = bicId; 
      sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
      sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
           "Bts Unlock for BtsId: %u is successfully completed",bicId);
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
           ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"updateStateAndSendBicUnlockAlarm : Bts is not find in BtsData Structure");
   }
   LOG_PRINT(LOG_INFO,"updateStateAndSendBicUnlockAlarm : Exiting Function ");

}

/* CS4.0 E1 UsageType Changes : End*/

/*BSC R2.0 Changes Starts*/
#if 0
I_Void revertChangesOnAddBicFailure(I_U8 rev)
{
  LOG_PRINT(DEBUG,"Entering In revertChangesOnAddBicFailure");
  switch(rev)
  {
     case 4:
     case 3:
            dbStatus = deleteBicTeiMapTableTer(receivedMsgPtr->e1Id,allocatedBicTs);
            if(DBLIB_SUCCESS != dbStatus)
            {
               LOG_PRINT(LOG_MAJOR,"Db wrapper deleteBicTeiMapTableTer Fails");
            }
     case 2:
       dbStatus=freeMccLinkResourceTablebyExternalE1Ts(receivedMsgPtr->e1Id,allocatedBicTs,
                         INVALID_E1,INVALID_TS,SYS_TS_FREE);
       if(DBLIB_SUCCESS != dbStatus)
       {
          LOG_PRINT(LOG_MAJOR,"Db wrapper freeMccLinkResourceTablebyExternalE1Ts Fails");
       } 
     case 1:
     break;
   
     default:
        LOG_PRINT(DEBUG,"revertChangesOnAddBicFailure: Wrong value passed in rev:%d", rev);    
     break;  
  }
  LOG_PRINT(DEBUG,"Exiting revertChangesOnAddBicFailure");
}
#endif

I_S32 allocateMccLinkResourceForBic(I_U32 e1Num,I_U32 e1Ts)
{
   MccLinkResourceTableApi *mccLinkTablePtrSelf = NULL;
   MccLinkResourceTableApi updateDbMccLinkResTableApiPtr ;
   BicE1TeiMapTableApi bicE1TeiMapTableApi;
   E1StreamMapTableIndices e1StreamMapTableIndices;
   E1StreamMapTableApi     *e1StreamMapTableApiPtr = NULL;
   LapdTEIConfigTableApi*         lapdTeiConfigTableApiPtr = NULL;
   LapdTEIConfigTableIndices      lapdTeiConfigTableIndicesPtr; 
   BicTrxTimeslotUsageTableApi    bicTrxTimeslotUsageTable;
   BicE1TeiMapTableApi            bicE1TeiMapTable;
   OamsCfgBichAddBicReq           oamsCfgBichAddBicReq;

   BicTableApi* receivedMsgPtr = (BicTableApi *)(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg)); 
   
   bzero(&updateDbMccLinkResTableApiPtr, sizeof(MccLinkResourceTableApi));

   I_U16 sizeSelf = 0;
   I_U16 outSize = 0;
   I_U16 applTei = ZERO;
   I_S32 dbStatus = -1;
   I_U32 rowsSelf = 0, i=0;
   I_U32 mccE1 = 0;
   I_U32 mccTs = 0;
   I_U32 strmTs = 0;
   I_U32 tmpE1= 0;
   I_U32 tmpTs = 0;
   I_U32 linkStatus = 0;

   tmpE1 = INVALID_E1;
   tmpTs = INVALID_TS;
   linkStatus = SYS_TS_FREE;
   
 
   LOG_PRINT(DEBUG,"Entering function allocateMccLinkResourceForBic");
   dbStatus = getFreeMccTrunkNumTsFromMccLinkTable(ICCSELFCARD,SYS_TS_USAGE_ABIS_FREE,
               tmpE1,tmpTs,linkStatus, &mccLinkTablePtrSelf,&rowsSelf, &sizeSelf);
   if( (dbStatus != DBLIB_SUCCESS) || (rowsSelf == ZERO) )
   {
      LOG_PRINT(LOG_MAJOR,"allocateMccLinkResourceForBic: No Free entries found in MccLinkResource Table. ");
      cfgSendNackToCm(CM_ERR_NO_FREE_MCC_TRUNKNUM_TRUNKTS);
      return CFG_FAILURE; 
   }

   memcpy(&updateDbMccLinkResTableApiPtr, &(mccLinkTablePtrSelf[0]) ,sizeSelf);
   free(mccLinkTablePtrSelf);

   mccE1 = updateDbMccLinkResTableApiPtr.mccTrunkNum;
   mccTs = updateDbMccLinkResTableApiPtr.mccTrunkTs;

   updateDbMccLinkResTableApiPtr.extTrunkNum   = e1Num;
   updateDbMccLinkResTableApiPtr.extTrunkTs    = e1Ts;
   updateDbMccLinkResTableApiPtr.mccLinkStatus = SYS_TS_ALLOCATED;

   LOG_PRINT(DEBUG,"MccE1:%d MccTs:%d is allocated on selfCard extE1%d extTs%d",
            mccE1, mccTs ,
            updateDbMccLinkResTableApiPtr.extTrunkNum, updateDbMccLinkResTableApiPtr.extTrunkTs);

   LOG_PRINT(DEBUG,"Going To Add Bic Data in BicTeiE1MapTable");
     
   e1StreamMapTableIndices.e1Num = mccE1;
   e1StreamMapTableIndices.e1Ts  = mccTs;
   if(getE1StreamMapTable(&e1StreamMapTableIndices, &e1StreamMapTableApiPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"addE1DataBicTeiE1MapTable : No rows in E1StreamMap table");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }
   strmTs                    = e1StreamMapTableApiPtr->strmTs;
	 free(e1StreamMapTableApiPtr);

   /* get applTei from LapdTeiConfigTable on the basis of lapdTimeSlot and lapdTei */
   LOG_PRINT(LOG_INFO,"addBicTableHandler : StreamTs : %d find in E1StreamMapTable ",
           strmTs);

   lapdTeiConfigTableIndicesPtr.lapdtimeslot = strmTs;
   if (receivedMsgPtr->btsType == BIC)
       lapdTeiConfigTableIndicesPtr.lapdTei = ONE;
   else  
       lapdTeiConfigTableIndicesPtr.lapdTei = ZERO;

   dbStatus = getLapdTEIConfigTable(&lapdTeiConfigTableIndicesPtr, &lapdTeiConfigTableApiPtr);
   if(dbStatus != DBLIB_SUCCESS)
   {
      /* applTei is not found at BSC. 
       * Sending NACK to OMC/CLI */ 
      LOG_PRINT(LOG_DEBUG,"addBicTableHandler : lapdTimeslot = %d and lapdTei \
              is not found in LapdTEIConfigTable at BSC",
              lapdTeiConfigTableIndicesPtr.lapdtimeslot,lapdTeiConfigTableIndicesPtr.lapdTei);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }

   applTei = lapdTeiConfigTableApiPtr->applTei;
   LOG_PRINT(LOG_INFO,"addBicTableHandler : applTei : %d find in LapdTEIConfigTable ",applTei);
   free(lapdTeiConfigTableApiPtr); 
   
   LOG_PRINT(LOG_INFO,"addBicTableHandler : BicTable Updated in Db Successfully");
   /* update mccLinkResourceTable  On self card*/
   dbStatus = updateMccLinkResourceTable(&updateDbMccLinkResTableApiPtr);
   if(dbStatus != DBLIB_SUCCESS )
   {
      /* MccLinkResourceTable Updation in DB Failed */
      LOG_PRINT(LOG_MAJOR,"addBicTableHandler : MccLinkResourceTable Updation in DB Failed for self card");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
	    return CFG_FAILURE;
   }

   /* update mccLinkResourceTable on mate card*/
   updateDbMccLinkResTableApiPtr.cardNum = ICCMATECARD;
 
   dbStatus = updateMccLinkResourceTable(&updateDbMccLinkResTableApiPtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_MAJOR,"allocateMccLinkResourceForBic: Updation fails in MccLinkResourceTable for Mate Card");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return CFG_FAILURE;
   }   

   LOG_PRINT(LOG_INFO,"addBicTableHandler : MccLinkResourceTable Updated in Db Successfully");
   /* Update AbisTimeSlotPerTable */
   dbStatus = updateRowAbisTimeSlotPerTable(e1Num, e1Ts,SYS_TS_USAGE_LAPD_BIC);
   if(DBLIB_SUCCESS != dbStatus)
   {
      /* AbisTimeSlotPerTable Updation in DB Failed */
      LOG_PRINT(LOG_MAJOR,"addBicTableHandler : AbisTimeSlotPerTable Updation in DB Failed");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
			return CFG_FAILURE;
   }

   /* Add a row in BicTrxTimeslotUsageTable */
   if (receivedMsgPtr->btsType == BIC)
       bicTrxTimeslotUsageTable.tsUser = TS_USAGE_BIC;
   else 
       bicTrxTimeslotUsageTable.tsUser = TS_USAGE_BTS;
   bicTrxTimeslotUsageTable.bicOrTrxId = receivedMsgPtr->bicId;
   bicTrxTimeslotUsageTable.e1Id = e1Num;
   bicTrxTimeslotUsageTable.lapdTs = e1Ts;
   bicTrxTimeslotUsageTable.trafficTrxTs1 = INVALID_TS;
   bicTrxTimeslotUsageTable.trafficTrxTs2 = INVALID_TS;
   bicTrxTimeslotUsageTable.numTs = ONE;
   dbStatus = insertBicTrxTimeslotUsageTable(&bicTrxTimeslotUsageTable);
   if(DBLIB_SUCCESS != dbStatus)
   {
      /* BicTrxTimeslotUsageTable Insertion in DB Failed */
      LOG_PRINT(LOG_MAJOR,"addBicTableHandler :  BicTrxTimeslotUsageTable Insertion in DB Failed");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
			return CFG_FAILURE;
   }

   /* BicTrxTimeslotUsageTable Inserted in DB Successfully.
    * Send Ack to OMC/CLI & Send Add BIC request to BICH */
   LOG_PRINT(LOG_INFO,"addBicTableHandler : BicTrxTimeslotUsageTable \
           Updated in Db Successfully");
   dbStatus = cfgInsertSwMNodeTableForBic(receivedMsgPtr->bicId,e1Num,
           e1Ts,receivedMsgPtr->btsType); 
   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_MAJOR,"addBicTableHandler :  SwMNodeTable Insertion in DB Failed");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
			return CFG_FAILURE;
   }

   /* Add Row in BicE1TeiMap Table */
   bicE1TeiMapTable.bicTei = applTei ;
   bicE1TeiMapTable.e1Id = e1Num;
   bicE1TeiMapTable.e1Ts = e1Ts;
   bicE1TeiMapTable.btsId = receivedMsgPtr->bicId;

   LOG_PRINT(LOG_DEBUG,"addE1DataBicTeiE1MapTable : e1Id = [%d], e1Ts = [%d], bicTei = [%d], btsId:%d",
	      bicE1TeiMapTableApi.e1Id,bicE1TeiMapTableApi.e1Ts,bicE1TeiMapTableApi.bicTei,
        bicE1TeiMapTable.btsId);

   dbStatus = insertBicE1TeiMapTable(&bicE1TeiMapTable);
   if(DBLIB_SUCCESS != dbStatus)
   { 
      LOG_PRINT(LOG_MAJOR,"addBicTableHandler : BicE1TeiTable Insertion in DB Failed");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
			return CFG_FAILURE;
   } 

   /* Add BIC Request is Valid. Going to Add BIC in DB*/
   dbStatus = insertBicTable(receivedMsgPtr);
   if(dbStatus != DBLIB_SUCCESS )
   {
      /* BicTable Insertion in DB Failed */
      LOG_PRINT(LOG_MAJOR,"addBicTableHandler : BicTable Insertion in DB Failed");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
	    return CFG_FAILURE;
   }

   /* Update BtsData Struct */
   if(getIndex(INVALID_BTS,&i) != CFG_FAILURE)
   {
       gBtsData[i].BTSID = receivedMsgPtr->bicId;
       if(receivedMsgPtr->adminState == 0)
           gBtsData[i].btsState=locked ;
       else
           gBtsData[i].btsState=unlocked ;
       gBtsData[i].btsType= receivedMsgPtr->btsType;
       gBtsData[i].connectivityState= none;
       LOG_PRINT(LOG_DEBUG,"addBicTableHandler : Values of Internal Data : \
               BtsId : %d, btsState : %d, btsType : %d, ConnectivityState : %d",
               gBtsData[i].BTSID,gBtsData[i].btsState,gBtsData[i].btsType,
               gBtsData[i].connectivityState);
       if(receivedMsgPtr->btsConnectivityState != BTS_CONNECT)
       { 
           cfgSendAckToCm();
       }
       oamsCfgBichAddBicReq.bicId = receivedMsgPtr->bicId;
       oamsCfgBichAddBicReq.e1Id = e1Num;
       oamsCfgBichAddBicReq.e1Ts = e1Ts;
       oamsCfgBichAddBicReq.btsType = receivedMsgPtr->btsType;
       oamsCfgBichAddBicReq.adminState = receivedMsgPtr->adminState;
       oamsCfgBichAddBicReq.applTei = applTei;
       cfgSendMessage(&oamsCfgBichAddBicReq, sizeof(OamsCfgBichAddBicReq),
               ENT_OAMS_BICH, OAMS_CFG_BICH_ADD_BIC_REQ , 0);
       if(sendScmLapdTimerConfigReq(receivedMsgPtr->bicId,receivedMsgPtr->satFlag,receivedMsgPtr->btsType) == I_TRUE)
       {
          LOG_PRINT(DEBUG,"sendScmLapdTimerConfigReq return failure");      
       }  
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"addBicTableHandler : BtsData Structure is full");
      cfgSendNackToCm(CM_ERR_MAX_NUM_BTS_EXCEED);
			return CFG_FAILURE;
   } 

   LOG_PRINT(DEBUG,"Exiting function allocateMccLinkResourceForBic");
   return CFG_SUCCESS;
}
/*BSC R2.0 Changes Ends*/

/********************************* Function  Header*****************************
Function Name   : updateRowAbisTimeSlotPerTable()
Parameters   : AbisTimeSlotPerTableApi abisRow I_U32 usageType
Return type   : I_Void
Purpose      : update AbisTimeSlotPer Table
Other Note   : Added For BSC R2.2 
 *******************************************************************************/

I_S32 updateRowAbisTimeSlotPerTable(I_U32 e1Id,I_U32 tsNum, I_U32 usageType)
{
   
   AbisTimeSlotPerTableApi updateRow ;
   LOG_PRINT(LOG_INFO,"updateRowAbisTimeSlotPerTable: Entering in Function");
   updateRow.e1Num= e1Id;
   updateRow.tsNum= tsNum;
   updateRow.adminState= UNLOCK;
   updateRow.usageType= usageType;
   if(updateAbisTimeSlotPerTable (&updateRow) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"updateRowAbisTimeSlotPerTable: Update Operation FAILED on AbisTimeSlotPer Table");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }
   
   LOG_PRINT(LOG_INFO,"updateRowAbisTimeSlotPerTable: Exiting from Function");
   return CFG_SUCCESS;
}


   /*Changes For R2.2 :Start */

/********************************* Function  Header*****************************
Function Name   : btsResetHandler()
Parameters   : 
Return type   : I_Void
Purpose      : To reset the BTS corresponding to the 
received bicId.
Other Note   : Added For BSC R2.2
 *******************************************************************************/
I_Void btsResetHandler()
{
  BicStatusTableIndices bicStatusTableIndex;
  BicStatusTableApi *bicStatusDbPtr = NULL;
  OamsCfgBichBtsReset oamsCfgBichBtsReset;
  I_U8 chasisFrameId,slotId;
  I_U32 swStatus, i = ZERO;
  I_U32  *trxId;
  I_U32  count;
  I_U32  index;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  BicTableApi* receivedMsgPtr =(BicTableApi*)(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));
   LOG_PRINT(LOG_INFO,"btsResetHandler : Entering from Function");

  LOG_PRINT(LOG_INFO,"btsResetHandler : Received BicId %u, E1Id: %u",receivedMsgPtr->bicId,receivedMsgPtr->e1Id);
  LOG_PRINT(LOG_INFO,"btsResetHandler : AdminState: %u",receivedMsgPtr->adminState);
  
  if(getIndex(receivedMsgPtr->bicId,&i) == CFG_FAILURE)
  {
     LOG_PRINT(LOG_DEBUG,"btsResetHandler : getIndex failed");
     cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
     return;
  }
  #if 0
  if( gBtsData[i].btsType != R2_BTS)
  {
     LOG_PRINT(LOG_DEBUG,"btsResetHandler : RESET not allowed for BIC");
     cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
     return;
  }
  #endif
  if( gBtsData[i].btsState == unlockInProgress)
  {
     LOG_PRINT(LOG_DEBUG,"btsResetHandler : RESET Only Allowed in LOCKED State.State is unLockinProgress");
     cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
     return;
  }
  if( gBtsData[i].btsState == lockInProgress)
  {
     LOG_PRINT(LOG_DEBUG,"btsResetHandler : RESET Only Allowed in LOCKED State.State is LockinProgress");
     cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
     return;
  }
  if( gBtsData[i].btsState == unlocked)
  {
     LOG_PRINT(LOG_DEBUG,"btsResetHandler : RESET Only Allowed in LOCKED State.State is unLock");
     cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);
     return;
  }

    bicStatusTableIndex.bicId = receivedMsgPtr->bicId; 
   /* Check Bic Id is Connect or Not */
   LOG_PRINT(LOG_INFO, "btsResetHandler : Going to Check BIC is Connected or Not ");
   if(CLIB_SUCCESS != getBicStatusTable(&bicStatusTableIndex, &bicStatusDbPtr))
   {
       LOG_PRINT(LOG_INFO, "btsResetHandler : No row exists in BicStatusTable ");
       cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
       return;
   }
   if((receivedMsgPtr->btsType !=R2_BTS_IP) && (receivedMsgPtr->btsType !=R3_BTS))/* Change For R2.8*/
   { 
    if(bicStatusDbPtr->lapdLinkStatus != CONNECTED)/* Change For R2.2*/
     { 
     LOG_PRINT(LOG_INFO, "btsResetHandler : Send Nack to CM BicId Not Connected ");
     cfgSendNackToCm(CM_ERR_BTS_LAPD_NOT_ESTABLISHED);
     free(bicStatusDbPtr);
     return; 
     }
   }
   else/* Change For R2.8*/
   {
    if(bicStatusDbPtr->btsIpLinkStatus!=ABIS_IP_UP )/* Change For R2.8*/
     { 
     LOG_PRINT(LOG_INFO, "btsResetHandler : Send Nack to CM BicId Not Connected ");
     cfgSendNackToCm(CM_ERR_BTS_LAPD_NOT_ESTABLISHED);
     free(bicStatusDbPtr);
     return; 
     }
   
   }
   
   LOG_PRINT(LOG_INFO, "btsResetHandler : BicId is Connected ");
   free(bicStatusDbPtr);
   /* Get Active ChasisFrameId and SlotId */
   LOG_PRINT(LOG_INFO, "btsResetHandler : Going to get Active ChasisFrameId and SlotId ");
   if (getActiveIccSlotId(&chasisFrameId,&slotId)!=CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_CRITICAL,"btsResetHandler : getActive ChasisFrameId and slotId DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
   }
   /* Get Status of Bic From SwMNode Table */
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   if(gBtsData[i].btsType == R2_BTS)
      sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_R2_BTS;
   if(gBtsData[i].btsType == BIC)
      sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_BIC;
   if(gBtsData[i].btsType == R2_BTS_IP)
      sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_R2_BTS_IP;
   if(gBtsData[i].btsType == R3_BTS)
      sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_R3_BTS;
   sApiSwMNodeTableIndices.nodeIdentity = receivedMsgPtr->bicId;
   if (CLIB_SUCCESS == getSwStatusFromSwMNodeTable(sApiSwMNodeTableIndices,&swStatus))
   {
    LOG_PRINT(LOG_INFO,"btsResetHandler : get S/w Status DB call is getting SuccessFul.");
    if((swStatus == SW_ACTIVATION_IN_PROGRESS)||(swStatus == SW_DOWNLOAD_IN_PROGRESS))
    {
      LOG_PRINT(LOG_DEBUG,"btsResetHandler : Either Download or Activation is in progress ");
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
    }
    LOG_PRINT(LOG_INFO, "btsResetHandler : Either Download or Activation is not in progress ");

   }
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_TRX;
   if( CLIB_SUCCESS != getAllPtrxTrxTable( receivedMsgPtr->bicId, &trxId, &count))
   {
      LOG_PRINT(LOG_INFO, "bicResetHandler : No Trx attached with Bic ");
   }
   sApiSwMNodeTableIndices.nodeIdentity = receivedMsgPtr->bicId;
   if (CLIB_SUCCESS == getSwStatusFromSwMNodeTable(sApiSwMNodeTableIndices,&swStatus))
   {
    LOG_PRINT(LOG_INFO,"btsResetHandler : get S/w Status DB call is getting SuccessFul.");
    if((swStatus == SW_ACTIVATION_IN_PROGRESS)||(swStatus == SW_DOWNLOAD_IN_PROGRESS))
    {
      LOG_PRINT(LOG_DEBUG,"btsResetHandler : Either Download or Activation is in progress ");
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
    }
    LOG_PRINT(LOG_INFO, "btsResetHandler : Either Download or Activation is not in progress ");

   }
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_TRX;
   if( CLIB_SUCCESS != getAllPtrxTrxTable( receivedMsgPtr->bicId, &trxId, &count))
   {
      LOG_PRINT(LOG_INFO, "bicResetHandler : No Trx attached with Bic ");
   }
   for (index=0; index<count; index++)
   {
      sApiSwMNodeTableIndices.nodeIdentity = trxId[index];
      if (CLIB_SUCCESS == getSwStatusFromSwMNodeTable(sApiSwMNodeTableIndices,&swStatus))
      {
         LOG_PRINT(LOG_INFO,"bicResetHandler : get S/w Status DB call is getting SuccessFul.");
         if((swStatus == SW_ACTIVATION_IN_PROGRESS)||(swStatus == SW_DOWNLOAD_IN_PROGRESS))
         {
            LOG_PRINT(LOG_DEBUG,"bicResetHandler : Either Download or Activation is in progress for TrxId: [%d]",trxId[index] );
            cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
            free (trxId);
            return;
         }
         LOG_PRINT(LOG_INFO, "bicResetHandler : Either Download or Activation is not in progress ");
      }
   }
   if ( count>0 )
      free(trxId);

   oamsCfgBichBtsReset.bicId = receivedMsgPtr->bicId;
   cfgSendMessage(&oamsCfgBichBtsReset, sizeof(OamsCfgBichBtsReset),
                  ENT_OAMS_BICH, OAMS_CFG_BICH_BTS_RESET , 0);
   cfgSendAckToCm();
   LOG_PRINT(LOG_INFO,"btsResetHandler : Exiting from Function");
 
}

/********************************* Function  Header*****************************
   Function Name   : btsConnectDisConnectHandler()
Parameters   : BicTableApi *bicTableDbPtr
Return type   : I_Void
Purpose      : To connect/disconnect the BTS corresponding to the 
received bicId.
Other Note   : Added For BSC R2.2
 *******************************************************************************/

I_Void btsConnectDisConnectHandler(BicTableApi *bicTableDbPtr)
{
   I_U8 chasisFrameId,slotId;
   I_U32 swStatus,i;
   TrunkTableApi *e1TablePtr = NULL;
   TrunkTableIndices e1TableIndices;
   SwMNodeTableIndices sApiSwMNodeTableIndices;

   BicTableApi* receivedMsgPtr =(BicTableApi*)(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));
  LOG_PRINT(LOG_INFO, "btsConnectDisConnectHandler : Entering Function ");

   LOG_PRINT(LOG_INFO,"btsConnectDisConnectHandler : Received BicId %u, E1Id: %u",receivedMsgPtr->bicId,receivedMsgPtr->e1Id);
   LOG_PRINT(LOG_INFO,"btsConnectDisConnectHandler : AdminState: %u",receivedMsgPtr->adminState);
    
      
   if (receivedMsgPtr->btsConnectivityState == bicTableDbPtr->btsConnectivityState)
   {
      LOG_PRINT(LOG_DEBUG,"btsConnectDisConnectHandler : Received same parameters as in DB");
      cfgSendAckToCm();
      return;
   }
   e1TableIndices.e1Num = receivedMsgPtr->e1Id;
   if(CLIB_SUCCESS != getTrunkTable(&e1TableIndices, &e1TablePtr))
   {
      LOG_PRINT(LOG_MAJOR,"btsConnectDisConnectHandler : e1Id : %d Received in Request is Not Configured at BSC",
            receivedMsgPtr->e1Id);
      cfgSendNackToCm(CM_ERR_E1_NOT_PRESENT_IN_DB);
      return;
   }
   free(e1TablePtr);


  if (receivedMsgPtr->btsConnectivityState != BTS_CONNECT &&
         receivedMsgPtr->btsConnectivityState != BTS_DISCONNECT)
  {
      LOG_PRINT(LOG_DEBUG,"btsConnectDisConnectHandler : Invalid BtsConnectivityState received");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
      return;
  }
  /* Get Active ChasisFrameId and SlotId */
   LOG_PRINT(LOG_INFO, "btsConnectDisConnectHandler : Going to get Active ChasisFrameId and SlotId ");
   if (getActiveIccSlotId(&chasisFrameId,&slotId)!=CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_CRITICAL,"btsConnectDisConnectHandler : getActive ChasisFrameId and slotId DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
   }
   /* Get Status of Bic From SwMNode Table */
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   if(getIndex(receivedMsgPtr->bicId,&i) == CFG_FAILURE)
   {
      LOG_PRINT(LOG_MAJOR,"btsConnectDisConnectHandler : BIC is not find in BtsData");
      cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
      return;
   }
      
   if(gBtsData[i].btsType == R2_BTS)
      sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_R2_BTS;
   if(gBtsData[i].btsType == BIC)
      sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_BIC;
   sApiSwMNodeTableIndices.nodeIdentity = receivedMsgPtr->bicId;
   if (CLIB_SUCCESS == getSwStatusFromSwMNodeTable(sApiSwMNodeTableIndices,&swStatus))
   {
    LOG_PRINT(LOG_INFO,"btsConnectDisConnectHandler : get S/w Status DB call is getting SuccessFul.");
    if((swStatus == SW_ACTIVATION_IN_PROGRESS)||(swStatus == SW_DOWNLOAD_IN_PROGRESS))
    {
      LOG_PRINT(LOG_DEBUG,"btsConnectDisConnectHandler : Either Download or Activation is in progress ");
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
    }
    LOG_PRINT(LOG_INFO, "btsConnectDisConnectHandler : Either Download or Activation is not in progress ");

   }
 
  if (receivedMsgPtr->btsConnectivityState == BTS_CONNECT)
  {
     btsConnectProcedure(receivedMsgPtr->bicId);
  }
  else if (receivedMsgPtr->btsConnectivityState == BTS_DISCONNECT)
  {
     btsDisConnectProcedure(receivedMsgPtr->bicId);
  }
  LOG_PRINT(LOG_INFO, "btsConnectDisConnectHandler : Exiting Function ");
 
}

/********************************* Function  Header*****************************
  Function Name   : btsConnectProcedure()
Parameters   : I_U32 bicId
Return type  : I_Void
Purpose      : To perform Bic Lock Procedure 
Other Note   : Added For BSC CS4.0
 *******************************************************************************/
I_Void btsConnectProcedure(I_U32 bicId)
{
      I_U32 tsUser = ZERO;
      I_U32 e1Id = ZERO, e1Ts = ZERO, i = ZERO;
      I_S32 status = ZERO;
      LOG_PRINT(LOG_INFO, "btsConnectProcedure : Entering Function ");
      
      if (getIndex(bicId,&i) == CFG_FAILURE)
      {
         cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
         return;
      }
      if (gBtsData[i].btsType == BIC)
         tsUser =  TS_USAGE_BIC;
      else if(gBtsData[i].btsType == R2_BTS)
         tsUser =  TS_USAGE_BTS;
                    
      status = getE1TsFromBicTrxTimeslotUsageTable(tsUser, 
               bicId, &e1Id, &e1Ts);
      if(CFG_FAILURE == status)
      {
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         return;
      }
      if(CFG_FAILURE == prepAndSndSwitchConForBic(e1Id,e1Ts))
      {
         LOG_PRINT(LOG_MAJOR,"btsConnectProcedure : Switch Connect Failed");
         cfgSendNackToCm(CM_ERR_INVALID_OR_MISSING_PRECONFIGDATA);
         return;
      }
      gBtsData[i].connectivityState = connectInProgress;
      LOG_PRINT(LOG_INFO, "btsConnectProcedure : Exiting Function ");
}



/********************************* Function  Header*****************************
  Function Name   : btsDisConnectProcedure()
Parameters   : I_U32 bicId
Return type  : I_Void
Purpose      : To perform Bic Lock Procedure 
Other Note   : Added For BSC CS4.0
 *******************************************************************************/
I_Void btsDisConnectProcedure(I_U32 bicId)
{
      I_U32 tsUser = ZERO;
      I_U32 e1Id = ZERO, e1Ts = ZERO, i = ZERO ;
      I_S32 status = ZERO;
      LOG_PRINT(LOG_INFO, "btsConnectProcedure : Entering Function ");
      
      if (getIndex(bicId,&i) == CFG_FAILURE)
      {
         cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
         return;
      }
      if( gBtsData[i].btsState != locked)
      {
         LOG_PRINT(LOG_DEBUG,"btsConnectProcedure : BTS Connectivity State Change must be in LOCKED State");
         cfgSendNackToCm(CM_ERR_BTS_NOT_LOCKED_IN_DB);
         return;
      }
 
      if (gBtsData[i].connectivityState == connectInProgress)
      {
         LOG_PRINT(LOG_MAJOR,"btsConnectProcedure : ConnectivityState-CONNECT is already in Progress");
         cfgSendNackToCm(CM_ERR_BTS_CONNECT_ALREADY_IN_PROGRESS);
         return;
      }
      if (gBtsData[i].btsType == BIC)
         tsUser =  TS_USAGE_BIC;
      else if(gBtsData[i].btsType == R2_BTS)
         tsUser =  TS_USAGE_BTS;
                    
      status = getE1TsFromBicTrxTimeslotUsageTable(tsUser, 
               bicId, &e1Id, &e1Ts);
      if(CFG_FAILURE == status)
      {
         LOG_PRINT(LOG_MAJOR,"btsConnectProcedure : Get Failed");
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         return;
      }
      
      if(CFG_FAILURE == prepAndSndSwitchDisConForBic(e1Id,e1Ts))
      {
          LOG_PRINT(LOG_MAJOR,"btsConnectProcedure : Switch DisConnect Failed");
          cfgSendNackToCm(CM_ERR_INVALID_OR_MISSING_PRECONFIGDATA);
          return;
      }
      if(CLIB_SUCCESS != updateBtsConnectivityState(bicId,BTS_DISCONNECT))
      {
        cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
        return;
      }
        cfgSendAckToCm();
      LOG_PRINT(LOG_INFO, "btsConnectProcedure : Exiting Function ");
}

/********************************* Function  Header*****************************
Function Name	: getIndex()
Parameters   	: I_U32 : value
Return type   	: I_U32
Purpose      	: This function return the index related to value.
Other Note   	: 
********************************************************************************/

I_U32 getIndex(I_U32 value,I_U32 *index)
{
   I_U32 counter;
   LOG_PRINT(LOG_INFO,"getIndex : Entering Function");
   for ( counter = 0; counter < CFG_MAX_NUM_BTS;counter++ )
   {
      if (gBtsData[counter].BTSID == value)
      {
         LOG_PRINT(LOG_DEBUG,"getIndex : Value of Index : %d",counter);
         *index = counter;
	       return CFG_SUCCESS;
      }
   }
   LOG_PRINT(LOG_INFO,"getIndex : Exiting Function");
   return CFG_FAILURE;
}
   /*Changes For R2.2 :End */

/********************************* Function  Header*****************************
Function Name	: isTimeSlotAvailable()
Parameters   	: I_U32 :e1Num,I_U32 totalTsReqrd
Return type   	: I_S32
Purpose      	: This function checks whether e1 has timeslot left for a new bic 
Other Note   	: 
********************************************************************************/
I_S32 isTimeSlotAvailable(I_U32 e1Num,I_U32 totalTsRqrd)
{
    I_S32 dbStatus = -1;
    I_U32 outRow = ZERO, index = ZERO, totalBusyTsonE1 = 0, tmpTs = 0;
    I_U16 outSz;
    BicTableApi *bicTableApiPtr = NULL;
    BicTableApi *tmpPtr = NULL;
    I_U32 maxTrunkTS;

    LOG_PRINT(DEBUG,"Entering in func isTimeSlotAvailable e1Num:%d, totalTsRqrd:%d", 
        e1Num, totalTsRqrd);

    if(gBscTrunkType==BPM_TRUNK_TYPE_T1)
    {
      maxTrunkTS=MAX_T1_TS;
    }
    else
    {
      maxTrunkTS=MAX_E1_TS;
    }

    dbStatus = getallBicTable(&bicTableApiPtr,&outRow,&outSz);
    if(DBLIB_SUCCESS != dbStatus)
    {
       LOG_PRINT(LOG_MAJOR,"isTimeSlotAvailable: Get Form BicTable Failed");
       return I_TRUE; 
    }

    for(index =0; index< outRow;index++)
    {
       tmpPtr = (BicTableApi *)((I_U8 *)bicTableApiPtr + index * outSz);
       if(tmpPtr->e1Id == e1Num)   
       {
          numofTsForBic(tmpPtr->btsType,tmpPtr->numTrx,tmpTs);
          totalBusyTsonE1 += tmpTs;
          tmpTs = 0;
       } 
    }
    free(bicTableApiPtr);

    if(totalTsRqrd <= (maxTrunkTS - totalBusyTsonE1 -1) ) 
    {
        LOG_PRINT(DEBUG,"isTimeSlotAvailable:Ts sre available on E1 returning true totalRqrdTs:%d leftTs:%d on E1:%d", 
            totalTsRqrd, (maxTrunkTS - totalBusyTsonE1-1), e1Num);
        return I_TRUE;
    }
    else
    {
        LOG_PRINT(DEBUG,"isTimeSlotAvailable:Ts NOT available on E1 returning false totalRqrdTs:%d leftTs:%d on E1:%d", 
            totalTsRqrd, (maxTrunkTS - totalBusyTsonE1-1), e1Num);
        return I_FALSE;
    }
}

/*BSC R2.3.4 Changes Starts*/
/********************************* Function  Header*****************************
Function Name   : btsSetSatFlagHandler()
Parameters   : 
Return type   : I_U8
Purpose      : To set the sat flag the BTS corresponding to the 
received bicId.
Other Note   : Added For BSC R2.2
 *******************************************************************************/
I_U8 btsSetSatFlagHandler(BicTableApi *pBtsTable)
{
   I_U32  index,i=0;
   I_U32 sndSize;
   sndSize = sizeof(OamScmLapdTimerConfig) ;
   BicTableApi* receivedMsgPtr =(BicTableApi*)(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));

   LOG_PRINT(LOG_INFO,"btsSetSatFlagHandler:Entering from Function");
   
   LOG_PRINT(LOG_INFO,"btsSetSatFlagHandler:Received BicId %u, E1Id: %u",receivedMsgPtr->bicId,receivedMsgPtr->e1Id);
   LOG_PRINT(LOG_INFO,"btsSetSatFlagHandler:AdminState: %u",receivedMsgPtr->adminState);
   
   if(getIndex(receivedMsgPtr->bicId,&i) == CFG_FAILURE)
   {
      LOG_PRINT(LOG_DEBUG,"btsSetSatFlagHandler : getIndex failed");
      cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
      return I_FALSE;
   }
   #if 0
   if( gBtsData[i].btsType != R2_BTS)
   {
      LOG_PRINT(LOG_DEBUG,"btsSetSatFlagHandler : setSatFlag not allowed for BIC");
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      return;
   }
   #endif
   if( gBtsData[i].btsState == unlockInProgress)
   {
      LOG_PRINT(LOG_DEBUG,"btsSetSatFlagHandler : RESET Only Allowed in LOCKED State.State is unLockinProgress");
      cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
      return I_FALSE;
   }
   if( gBtsData[i].btsState == lockInProgress)
   {
      LOG_PRINT(LOG_DEBUG,"btsSetSatFlagHandler : RESET Only Allowed in LOCKED State.State is LockinProgress");
      cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
      return I_FALSE;
   }
   if( gBtsData[i].btsState == unlocked)
   {
      LOG_PRINT(LOG_DEBUG,"btsSetSatFlagHandler : RESET Only Allowed in LOCKED State.State is unLock");
      cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);
      return I_FALSE;
   }
   
   if ((receivedMsgPtr->btsType != R2_BTS_IP) && (receivedMsgPtr->btsType != R3_BTS))
   {
     if(sendScmLapdTimerConfigReq(receivedMsgPtr->bicId,receivedMsgPtr->satFlag,receivedMsgPtr->btsType) != I_TRUE)
     {
       LOG_PRINT(DEBUG,"sendScmLapdTimerConfigReq return failure");      
       cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
       return I_FALSE;
     }
   }
   else
   {
      pBtsTable->satFlag = receivedMsgPtr->satFlag;
      if(updateBicTable(pBtsTable) != CLIB_SUCCESS) 
      {
         LOG_PRINT(MAJOR,"btsSetSatFlagHandler: updateBicTable failed "
                         "for bicId:%d",receivedMsgPtr->bicId);
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         return I_FALSE; 
       }
   }
   cfgSendAckToCm();
   LOG_PRINT(LOG_INFO,"btsSetSatFlagHandler : Exiting from Function");
   return I_TRUE;
}

/********************************* Function  Header*****************************
Function Name   : btsSetClusterIdHandler()
Parameters   : 
Return type   : I_U8
Purpose      : To set the cluster Id value of Bts
Other Note   : Added For LCLS feature
 *******************************************************************************/
I_U8 btsSetClusterIdHandler()
{
    I_S32                 retVal;
    ClusterTableIndices   clusterInd;
    ClusterTableApi       *pClusterTable;
    BicTableApi* receivedMsgPtr =(BicTableApi*)(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg)); 
   
    LOG_PRINT(LOG_INFO,"btsSetClusterIdHandler:Entering Function");
    if (((receivedMsgPtr->btsType == BIC) || (receivedMsgPtr->btsType == R2_BTS))
        && (receivedMsgPtr->clusterId != ZERO))
    {
      LOG_PRINT(LOG_DEBUG,"btsSetClusterIdHandler : Valid ClusterId value Valid only for IP Bts");
      cfgSendNackToCm(CM_ERR_INVALID_CLUSTER_ID_BTS_TYPE);
      return I_FALSE;
    }
    else if(receivedMsgPtr->clusterId > CLUSTER_ID_RANGE)
    {
      cfgSendNackToCm(CM_ERR_INVALID_CLUSTER_ID_VALUE);
      return I_FALSE;
    }
    clusterInd.clusterId = receivedMsgPtr->clusterId;
    retVal = getClusterTable(&clusterInd, &pClusterTable);
    if((retVal == DBLIB_SUCCESS) || (receivedMsgPtr->clusterId == 0))
    {
      updateClusterIdBicTable(receivedMsgPtr->bicId, receivedMsgPtr->clusterId);
      if (retVal == DBLIB_SUCCESS)
      {
        free(pClusterTable);
      }
    }
    else
    {
      LOG_PRINT(DEBUG,"btsSetClusterIdHandler : ClusterId %d not found in DB",
                       receivedMsgPtr->clusterId);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return I_FALSE;
    }
    cfgSendAckToCm();
    LOG_PRINT(LOG_INFO,"btsSetClusterIdHandler : Exiting from Function");
    return I_TRUE;
}

/********************************* Function  Header*****************************
Function Name   : btsSetMaxRfPwrConfHandler()
Parameters   : 
Return type   : I_U8
Purpose      : To set the MaxRfPwrConf Id value of Bts
Other Note   : Added to run BTS on Reduced Power feature
 *******************************************************************************/
I_U8 btsSetMaxRfPwrConfHandler(BicTableApi *pBtsTable)
{
    I_S32                 retVal;
    BicTableApi* receivedMsgPtr =(BicTableApi*)(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg)); 
   
    LOG_PRINT(LOG_INFO,"btsSetMaxRfPwrConfHandler: Entering Function");
    //if (receivedMsgPtr->btsType != R2_BTS_IP) /*Changes merged from R2.9 Issue #31185 Gaurav Sinha*/
    if ((receivedMsgPtr->btsType != R2_BTS_IP) && (receivedMsgPtr->btsType != R3_BTS))
    {
      //LOG_PRINT(LOG_DEBUG,"btsSetMaxRfPwrConfHandler : Update of MaxRfPwrConf is applicable only for R2-IP Bts"); /*Changes merged from R2.9 Issue #31185 Gaurav Sinha*/
      LOG_PRINT(LOG_DEBUG,"btsSetMaxRfPwrConfHandler : Update of MaxRfPwrConf is applicable only for IP Bts");
      cfgSendNackToCm(CM_ERR_INVALID_CLUSTER_ID_BTS_TYPE);
      return I_FALSE;
    }
    if ((receivedMsgPtr->maxRfPwrConf < 0) || (receivedMsgPtr->maxRfPwrConf > 127))
    {
      cfgSendNackToCm(CM_ERR_INVALID_CLUSTER_ID_VALUE);
      return I_FALSE;
    }

    pBtsTable->maxRfPwrConf = receivedMsgPtr->maxRfPwrConf;
    if(updateBicTable(pBtsTable) != CLIB_SUCCESS) 
    {
      LOG_PRINT(MAJOR,"btsSetMaxRfPwrConfHandler: updateBicTable failed for bicId:%d",receivedMsgPtr->bicId);
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return I_FALSE; 
    }

    cfgSendAckToCm();
    LOG_PRINT(LOG_INFO,"btsSetMaxRfPwrConfHandler : Exiting from Function");
    return I_TRUE;
}

/********************************* Function  Header*****************************
Function Name   : sendScmLapdTimerConfigReq()
Parameters   : 
Return type   : I_Void
Purpose      : To send the Lapd Timer Config request to SCM
Other Note   : Added For BSC R2.2
 *******************************************************************************/
I_U8 sendScmLapdTimerConfigReq(I_U32 bicId , I_U32 satFlag,I_U32 btsType)
{
   BicTrxTimeslotUsageTableIndices bicTrxTsUsagetblIndx;
   BicTrxTimeslotUsageTableApi *outData;
   OamScmLapdTimerConfig scmLapdConfigMsg = {0};
   LapdTimerTableApi *lapdTimerTblPtr = NULL;
   LapdTimerTableApi *tmpLapdTimerTblPtr = NULL;
   MccLinkResourceTableApi *mccLinkResourcePtr = NULL;
   E1StreamMapTableIndices e1StreamMapTblIndx;
   E1StreamMapTableApi *e1StreamTblPtr = NULL;
   I_U32 outRows = 0,i=0;
   I_U16 outSize = 0;

   LOG_PRINT(DEBUG,"sendScmLapdTimerConfigReq: Entering in function");
   if(btsType == R2_BTS)
   {
      bicTrxTsUsagetblIndx.tsUser = TS_USAGE_BTS;
   }
   else
   {
      bicTrxTsUsagetblIndx.tsUser = TS_USAGE_BIC;
   } 

   bicTrxTsUsagetblIndx.bicOrTrxId = bicId;
   if(getBicTrxTimeslotUsageTable(&bicTrxTsUsagetblIndx,&outData) != CLIB_SUCCESS)
   {
      LOG_PRINT(MAJOR,"getBicTrxTimeslotUsageTable failed for tsUser:%d bicId:%d",
           bicTrxTsUsagetblIndx.tsUser,bicTrxTsUsagetblIndx.bicOrTrxId); 
      return I_FALSE;
   } 

   if(getallLapdTimerTable(&lapdTimerTblPtr,&outRows,&outSize) != CLIB_SUCCESS)
   {
       LOG_PRINT(MAJOR,"getallLapdTimerTable failed");
       free(outData); 
       return I_FALSE;
   }
   if(outRows != 2)
   {
       LOG_PRINT(MAJOR,"getallLapdTimerTable failed as outrows:%d",outRows);
       free(outData); 
       return I_FALSE;
   }

   for(i=0;i<outRows;i++)
   {
      tmpLapdTimerTblPtr = (LapdTimerTableApi *)((I_U8 *)lapdTimerTblPtr + i * outSize );
      if(tmpLapdTimerTblPtr->satFlag == I_TRUE )
      {
          scmLapdConfigMsg.lapdTimerSatellite.lapdTimerT200 = tmpLapdTimerTblPtr->lapdTimerT200; 
          scmLapdConfigMsg.lapdTimerSatellite.lapdTimerT203 = tmpLapdTimerTblPtr->lapdTimerT203; 
          scmLapdConfigMsg.lapdTimerSatellite.N200 = tmpLapdTimerTblPtr->lapdTimerN200; 
      }
      else
      {
          scmLapdConfigMsg.lapdTimerDefault.lapdTimerT200 = tmpLapdTimerTblPtr->lapdTimerT200; 
          scmLapdConfigMsg.lapdTimerDefault.lapdTimerT203 = tmpLapdTimerTblPtr->lapdTimerT203; 
          scmLapdConfigMsg.lapdTimerDefault.N200 = tmpLapdTimerTblPtr->lapdTimerN200; 
      }
   }
   free(lapdTimerTblPtr);

   if(getMccTrunkNumTsUsingExtTrunkNumTs(outData->e1Id,outData->lapdTs,&mccLinkResourcePtr,&outRows,&outSize)
      != CLIB_SUCCESS)   
   {
      LOG_PRINT(DEBUG,"getMccTrunkNumTsUsingExtTrunkNumTs failed for e1Id:%d timeslot:%d",
          outData->e1Id,outData->lapdTs); 
      return I_FALSE; 
   }  
   e1StreamMapTblIndx.e1Num = mccLinkResourcePtr->mccTrunkNum;
   e1StreamMapTblIndx.e1Ts = mccLinkResourcePtr->mccTrunkTs;
   free(mccLinkResourcePtr); 
   if(getE1StreamMapTable(&e1StreamMapTblIndx,&e1StreamTblPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"getE1StreamMapTable failed for MccE1:%d MccTs:%d",
         e1StreamMapTblIndx.e1Num,e1StreamMapTblIndx.e1Ts); 
      return I_FALSE; 
   }
   scmLapdConfigMsg.lpdTsdetail->ts = e1StreamTblPtr->strmTs;  
   scmLapdConfigMsg.lpdTsdetail->satFlag = satFlag;  
   free(e1StreamTblPtr);
   scmLapdConfigMsg.noOfLapdTs = 1;
   setStackObject(BSC_API_SET_BSSTABLE, SCM_MODIFY, OAM_SCM_LAPDTIMER_CONFIG);
   if (cfgSendStackMessage((I_Void *)&scmLapdConfigMsg, sizeof(OamScmLapdTimerConfig) ) == CFG_SUCCESS) 
   {
      LOG_PRINT(LOG_INFO,"sendScmLapdTimerConfigReq: Sending OAM_SCM_LAPDTIMER_CONFIG for numTs[%u] to Oil..",
              scmLapdConfigMsg.noOfLapdTs);
      gReqSentToScm =1;
      updateSatFlagBicTable(bicId,satFlag);
   }
   LOG_PRINT(DEBUG,"sendScmLapdTimerConfigReq: Exiting from function");
   return I_TRUE;  
}


/********************************* Function  Header*****************************
Function Name   : updateSatFlagBicTable()
Parameters   : 
Return type   : I_Void
Purpose      : To modify the values of satellite flag in database
Other Note   : Added For BSC R2.3.4
 *******************************************************************************/
I_U8 updateSatFlagBicTable(I_U32 bicId , I_U32 satFlag)
{
   BicTableIndices bicTblIndx;
   BicTableApi *outData;
   I_U32 outRows = 0;
   I_U16 outSize = 0;

   LOG_PRINT(DEBUG,"updateSatFlagBicTable: Entering In func");
   bicTblIndx.bicId = bicId;
  
   if(getBicTable(&bicTblIndx,&outData) != CLIB_SUCCESS)
   {
      LOG_PRINT(MAJOR,"updateSatFlagBicTable: getBicTable failed for bicId:%d",bicId);
      return I_FALSE; 
   }
    
   outData->satFlag =  satFlag;
   
   if(updateBicTable(outData) != CLIB_SUCCESS) 
   {
      LOG_PRINT(MAJOR,"updateSatFlagBicTable: updateBicTable failed for bicId:%d",bicId);
      return I_FALSE; 
   }
  
   free(outData);
   LOG_PRINT(DEBUG,"updateSatFlagBicTable: Exiting from func");
   return I_TRUE; 
}

/*BSC R2.3.4 Changes Ends*/
/********************************* Function  Header*****************************
Function Name   : updateClusterIdBicTable()
Parameters   : 
Return type   : I_Void
Purpose      : To modify the values of clusterId in database
Other Note   : Added For LCLS
 *******************************************************************************/
I_U8 updateClusterIdBicTable(I_U32 bicId, I_U16 clusterId)
{
   BicTableIndices bicTblIndx;
   BicTableApi *outData;
   I_U32 outRows = 0;
   I_U16 outSize = 0;

   LOG_PRINT(DEBUG,"updateClusterIdBicTable: Entering In func");
   bicTblIndx.bicId = bicId;
  
   if(getBicTable(&bicTblIndx,&outData) != CLIB_SUCCESS)
   {
      LOG_PRINT(MAJOR,"updateClusterIdBicTable: getBicTable failed for bicId:%d",bicId);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return I_FALSE; 
   }
    
   outData->clusterId =  clusterId;
   
   if(updateBicTable(outData) != CLIB_SUCCESS) 
   {
      LOG_PRINT(MAJOR,"updateClusterIdBicTable: updateBicTable failed for bicId:%d",bicId);
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return I_FALSE; 
   }
  
   free(outData);
   LOG_PRINT(DEBUG,"updateClusterIdBicTable: Exiting from func");
   return I_TRUE; 
}

/********************************* Change History ***************************
   Release   Author      Description
   BSC CS2.2       Kapil Tyagi     Initial Draft   

 ************************************** End *********************************/
