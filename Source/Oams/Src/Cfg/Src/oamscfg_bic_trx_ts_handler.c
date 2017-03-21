/***********************************File Header ***************************
File Name        : oamscfg_bic_trx_ts_handler.c  
Purpose          : This file contains switching implementation of BIC and TRX
Project          : BSC OAM
Subsystem        : Oams CFG
Author           : Aricent Gurgaon
CSCI ID          :
Version          :
 ************************************* End **********************************/
#include <oamscfg_includes.h>
/* Changes for R2.2 : Start */
//static OamsList head;
/* Changes for R2.2 : End  */
//static LapdTEIConfigTableApi *LapdTEIConfigTableApiPtr;
//I_U32 lapdTeiRecCount = 0;
I_U16 lapdTeiRecSz = 0;

/********************************* Function  Header********************************
Function Name	: isTeiAllocated()
Parameters	: lapdTeiConfigTblIndx :: LapdTEIConfigTableIndices
Return type	: I_S32 (I_TRUE/I_FALSE)
Purpose		: To  search if  Tei is allocated.	
Other Note	:
 ************************************************************************************/
I_S32 isTeiAllocated(LapdTEIConfigTableIndices *lapdTeiConfigTblIndex,I_U32 * applTei_o)  
{
   LapdTEIConfigTableApi *LapdTEIConfigTableApiPtr;
   TrxTsTeiTableApi *trxTsTeiTablePtr;
   TrxTsTeiTableSecIndices trxTsTeiTableSecIndices;
   I_S32 retVal = CFG_FAILURE;
   I_U32 recCnt = 0;
   I_U16 recSz = 0;  
   I_U32 trxTei;

   retVal = getLapdTEIConfigTable(lapdTeiConfigTblIndex,&LapdTEIConfigTableApiPtr);       
   if(retVal != DBLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"initAbisE1TsList : No Row for Ts:%d, Tei:%d in LapdTEIConfigTable",
         lapdTeiConfigTblIndex->lapdtimeslot,lapdTeiConfigTblIndex->lapdTei);
      return I_TRUE;
   }

   trxTei = LapdTEIConfigTableApiPtr->applTei;
   *applTei_o = LapdTEIConfigTableApiPtr->applTei;

   if( CLIB_SUCCESS != getSecTrxTsTeiTable(trxTei,&trxTsTeiTablePtr,&recCnt,&recSz))
   {
      LOG_PRINT(DEBUG,"getSecTrxTsTeiTable failed for trxTei:%d", trxTei);
      free(LapdTEIConfigTableApiPtr);
      return I_FALSE;
   }
   free(LapdTEIConfigTableApiPtr);
   free(trxTsTeiTablePtr);
   return I_TRUE;
}

/********************************* Function  Header********************************
Function Name	: populateTrxTsTeiTable()
Parameters	: trxId   :: I_U32
		  trxType :: I_U8
		  bicId   :: I_U32
Return type	: I_S32
Purpose		: To populate TrxTsTeiTable.	
Other Note	:
 ************************************************************************************/
I_S32 populateTrxTsTeiTable(TrxTableApi* trxTablePtr,I_U32 e1Id, I_U32 *allocatedTs)  
{
   TrxTsTeiTableApi trxTsTeiTableApi;
   LapdTEIConfigTableApi *tmpLapdTeiConfigPtr = NULL;
   E1StreamMapTableIndices e1StreamMapTableIndices;
   E1StreamMapTableApi *E1StreamMapTableApiPtr = NULL; 
   BicTrxTimeslotUsageTableIndices bicTrxTimeSlotInd;
   BicTrxTimeslotUsageTableApi bicTrxTimeSlotUsageTableBuff;
   BicTrxTimeslotUsageTableApi *bicTrxTimeSlotUsageTablePtr;
   LapdTEIConfigTableApi *LapdTEIConfigTableApiPtr;
   LapdTEIConfigTableIndices lapdTeiConfigTblIndex;
   I_U32 lapdTeiRecCount = 0;
   I_U32 mccE1 = 0;
   I_U32 mccTs = 0;
   I_S32 retVal = CFG_FAILURE;
   I_U32 count = ZERO;
   I_U32 *tmpTs=allocatedTs;
   I_U32 lapdTs;
   I_U32 applTei;
   
   LOG_PRINT(LOG_INFO,"populateTrxTsTeiTable : Entering in the function");
   LOG_PRINT(LOG_DEBUG,"populateTrxTsTeiTable : Received ptrxId : %d, trxLocation : %d, bicId : %d",
					trxTablePtr->ptrxId, trxTablePtr->trxLocation, trxTablePtr->bicId);
      /* Get E1 & Ts Used by TRX */
   if(TRX_LOCATION_BIC == trxTablePtr->trxLocation)
   {
        bicTrxTimeSlotUsageTableBuff.tsUser = TS_USAGE_BICTRX;
   	bicTrxTimeSlotUsageTableBuff.bicOrTrxId = trxTablePtr->ptrxId;
   	bicTrxTimeSlotUsageTableBuff.e1Id = e1Id;
   	bicTrxTimeSlotUsageTableBuff.numTs= THREE;
   	bicTrxTimeSlotUsageTableBuff.lapdTs = *tmpTs;
	lapdTs= bicTrxTimeSlotUsageTableBuff.lapdTs ;
	tmpTs++;
   	bicTrxTimeSlotUsageTableBuff.trafficTrxTs1= *tmpTs;
	tmpTs++;
   	bicTrxTimeSlotUsageTableBuff.trafficTrxTs2= *tmpTs;
	
	if(insertBicTrxTimeslotUsageTable(&bicTrxTimeSlotUsageTableBuff) != DBLIB_SUCCESS)
   	{
      	   LOG_PRINT(LOG_INFO,"insertRowInBicTrxTimeslotUsageTable: No row inserted in BicTrxTimeslotUsgaeTable");
           return CFG_FAILURE;
   	}
   }
   else if(TRX_LOCATION_R2_BTS == trxTablePtr->trxLocation)
   {
	bicTrxTimeSlotInd.tsUser=TS_USAGE_BTS;	
	bicTrxTimeSlotInd.bicOrTrxId=trxTablePtr->bicId;	
	if(getBicTrxTimeslotUsageTable(&bicTrxTimeSlotInd,&bicTrxTimeSlotUsageTablePtr) != DBLIB_SUCCESS)
	{
      	   LOG_PRINT(LOG_INFO,"getBicTrxTimeslotUsageTable: Failed");
           return CFG_FAILURE;
	}

    bicTrxTimeSlotUsageTableBuff.tsUser = TS_USAGE_BTS_TRX;
   	bicTrxTimeSlotUsageTableBuff.bicOrTrxId = trxTablePtr->ptrxId;
   	bicTrxTimeSlotUsageTableBuff.e1Id = e1Id;
   	bicTrxTimeSlotUsageTableBuff.numTs= THREE;
   	bicTrxTimeSlotUsageTableBuff.lapdTs = bicTrxTimeSlotUsageTablePtr->lapdTs;
	lapdTs= bicTrxTimeSlotUsageTableBuff.lapdTs ;
   	bicTrxTimeSlotUsageTableBuff.trafficTrxTs1= *tmpTs;
	tmpTs++;
   	bicTrxTimeSlotUsageTableBuff.trafficTrxTs2= *tmpTs;
	
	if(insertBicTrxTimeslotUsageTable(&bicTrxTimeSlotUsageTableBuff) != DBLIB_SUCCESS)
   	{
      	   LOG_PRINT(LOG_INFO,"insertRowInBicTrxTimeslotUsageTable: No row inserted in BicTrxTimeslotUsgaeTable");
           free(bicTrxTimeSlotUsageTablePtr);
	   return CFG_FAILURE;
   	}
        free(bicTrxTimeSlotUsageTablePtr);
   }
   else
   {
	 retVal = getE1TsForInFrameTrx(trxTablePtr->ptrxId, &e1Id, &lapdTs);
      	 if(CFG_FAILURE == retVal)
      	 {
           return retVal;
         }
   }
   if(getMccE1Ts(e1Id, lapdTs, &mccE1, &mccTs) == CFG_FAILURE)
   {
      LOG_PRINT(LOG_MAJOR,"populateTrxTsTeiTable : No mccE1 and mccTs for E1 :%d, Ts :%d",
							 e1Id, lapdTs);
      return CFG_FAILURE;	
   }
   
   e1StreamMapTableIndices.e1Num = mccE1;
   e1StreamMapTableIndices.e1Ts = mccTs;
   if(getE1StreamMapTable(&e1StreamMapTableIndices , &E1StreamMapTableApiPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"populateTrxTsTeiTable : No rows in E1StreamMap table");
      return CFG_FAILURE;
   }
   
   LOG_PRINT(LOG_INFO,"populateTrxTsTeiTable : strmTs are :%d", E1StreamMapTableApiPtr->strmTs);

   /* Populate Table TrxTsTeiTable */
   trxTsTeiTableApi.ptrxId = trxTablePtr->ptrxId;

	 if (trxTablePtr->trxLocation == TRX_LOCATION_R2_BTS)
   {
      lapdTeiConfigTblIndex.lapdtimeslot = E1StreamMapTableApiPtr->strmTs;
      lapdTeiConfigTblIndex.lapdTei = TRX_POSITION_1;
  
      if(isTeiAllocated(&lapdTeiConfigTblIndex,&applTei) == I_TRUE)
      {
         lapdTeiConfigTblIndex.lapdTei = TRX_POSITION_2;
         if(isTeiAllocated(&lapdTeiConfigTblIndex, &applTei) == I_TRUE)
         {
            LOG_PRINT(LOG_MAJOR,"NO applTei could be allocated for given lapdTs:%d", lapdTeiConfigTblIndex.lapdtimeslot);
            return CFG_FAILURE;
         } 
      }  
       
      LOG_PRINT(DEBUG,"Alloacated Tei is :%d",applTei);
	    trxTsTeiTableApi.trxTei = applTei;
      free (E1StreamMapTableApiPtr); 
       
   }
   else
   {
       /*Initializing LapdTeiConfigTable Data */
       retVal = getallLapdTEIConfigTable(&LapdTEIConfigTableApiPtr, &lapdTeiRecCount, &lapdTeiRecSz);
       if(retVal != DBLIB_SUCCESS)
       {
          LOG_PRINT(LOG_MAJOR,"initAbisE1TsList : No Rows in LapdTEIConfigTable");
          return CFG_FAILURE;
       }
       
       tmpLapdTeiConfigPtr = LapdTEIConfigTableApiPtr;
       for(count = 0; count < lapdTeiRecCount; count++)
       {
          /* Fixed Mantis : #4818 : Start */
          tmpLapdTeiConfigPtr = ( LapdTEIConfigTableApi *)(((I_U8 *)( LapdTEIConfigTableApiPtr)) + 
	      					(count * lapdTeiRecSz));
          /* Fixed Mantis : #4818 : End */
          if(tmpLapdTeiConfigPtr->lapdtimeslot == E1StreamMapTableApiPtr->strmTs)
          {
	     if (trxTablePtr->trxLocation==TRX_LOCATION_BIC && tmpLapdTeiConfigPtr->lapdTei == ONE)
	     {
	        trxTsTeiTableApi.trxTei = tmpLapdTeiConfigPtr->applTei;
	        break;
	     }
       #if 0
	     else if (trxTablePtr->trxLocation==TRX_LOCATION_R2_BTS && tmpLapdTeiConfigPtr->lapdTei == trxTablePtr->trxPos)
	     {
	        trxTsTeiTableApi.trxTei = tmpLapdTeiConfigPtr->applTei;
	        break;
	     }
       #endif
	     else if (trxTablePtr->trxLocation==TRX_LOCATION_IN_FRAME && tmpLapdTeiConfigPtr->lapdTei == ONE)//A6 inframe change for LapdTei
	     {
	        trxTsTeiTableApi.trxTei = tmpLapdTeiConfigPtr->applTei;
	        break;
	     }
          }	
       }
       free(LapdTEIConfigTableApiPtr);
       free (E1StreamMapTableApiPtr); 
       if(count == lapdTeiRecCount)
       {
          LOG_PRINT(LOG_MAJOR," populateTrxTsTeiTable : TimeSlot Mismatch ");
          return CFG_FAILURE;
       }
   }
   if(trxTablePtr->trxLocation==TRX_LOCATION_IN_FRAME )
   {  
      trxTsTeiTableApi.e1Id = e1Id;
      trxTsTeiTableApi.lapdTs = lapdTs;
      trxTsTeiTableApi.lapdLinkStatus = ZERO; 
      trxTsTeiTableApi.firstTsTraffic = lapdTs + 1;
      trxTsTeiTableApi.secondTsTraffic= lapdTs + 2;
   }
   else
   {  
      trxTsTeiTableApi.e1Id = e1Id;
      trxTsTeiTableApi.lapdTs = lapdTs;
      trxTsTeiTableApi.lapdLinkStatus = ZERO; 
      trxTsTeiTableApi.firstTsTraffic = bicTrxTimeSlotUsageTableBuff.trafficTrxTs1;
      trxTsTeiTableApi.secondTsTraffic= bicTrxTimeSlotUsageTableBuff.trafficTrxTs2;
   }
   retVal = insertTrxTsTeiTable(&trxTsTeiTableApi);
   if(retVal != DBLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"populateTrxTsTeiTable : Insert in DB failed" );
      return CFG_FAILURE;
   }
   LOG_PRINT(LOG_INFO,"populateTrxTsTeiTable : Exiting from the function "); 
   return  retVal;
}

/********************************* Function  Header********************************
Function Name	: populateTrxTsTeiTableOnReboot()
Parameters	: trxId   :: I_U32
		  trxType :: I_U8
		  bicId   :: I_U32
Return type	: I_S32
Purpose		: To populate TrxTsTeiTable at reboot time.	
Other Note	:
 ************************************************************************************/


I_S32 populateTrxTsTeiTableOnReboot(TrxTableApi* trxTablePtr)  
{
   TrxTsTeiTableApi trxTsTeiTableApi;
   LapdTEIConfigTableApi *tmpLapdTeiConfigPtr = NULL;
   E1StreamMapTableIndices e1StreamMapTableIndices;
   E1StreamMapTableApi *E1StreamMapTableApiPtr = NULL; 
   BicTrxTimeslotUsageTableIndices bicTrxTimeSlotInd;
   BicTrxTimeslotUsageTableApi bicTrxTimeSlotUsageTableBuff;
   BicTrxTimeslotUsageTableApi *bicTrxTimeSlotUsageTablePtr;
   LapdTEIConfigTableApi *LapdTEIConfigTableApiPtr;
   LapdTEIConfigTableIndices lapdTeiConfigTblIndex;
   I_U32 lapdTeiRecCount = 0;
   I_U32 mccE1 = 0;
   I_U32 mccTs = 0;
   I_S32 retVal = CFG_FAILURE;
   I_U32 count = ZERO;
   I_U32 e1Id,lapdTs;
   I_U32 applTei;
   
   LOG_PRINT(LOG_INFO,"populateTrxTsTeiTable : Entering in the function");
   LOG_PRINT(LOG_DEBUG,"populateTrxTsTeiTable : Received ptrxId : %d, trxLocation : %d, bicId : %d",
					trxTablePtr->ptrxId, trxTablePtr->trxLocation, trxTablePtr->bicId);
   
   if(TRX_LOCATION_BIC == trxTablePtr->trxLocation)
   {
      bicTrxTimeSlotInd.tsUser=TS_USAGE_BICTRX;	
      bicTrxTimeSlotInd.bicOrTrxId=trxTablePtr->ptrxId;	
      if(getBicTrxTimeslotUsageTable(&bicTrxTimeSlotInd,&bicTrxTimeSlotUsageTablePtr) != DBLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"getBicTrxTimeslotUsageTable: Failed");
         return CFG_FAILURE;
      }
      e1Id = bicTrxTimeSlotUsageTablePtr->e1Id;
      lapdTs= bicTrxTimeSlotUsageTablePtr->lapdTs;
   }
   else if(TRX_LOCATION_R2_BTS == trxTablePtr->trxLocation)
   {
      bicTrxTimeSlotInd.tsUser=TS_USAGE_BTS_TRX;	
      bicTrxTimeSlotInd.bicOrTrxId=trxTablePtr->ptrxId;	
      if(getBicTrxTimeslotUsageTable(&bicTrxTimeSlotInd,&bicTrxTimeSlotUsageTablePtr) != DBLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"getBicTrxTimeslotUsageTable: Failed");
         return CFG_FAILURE;
      }
      e1Id = bicTrxTimeSlotUsageTablePtr->e1Id;
      lapdTs= bicTrxTimeSlotUsageTablePtr->lapdTs;
   } 
   else
   {
      retVal = getE1TsForInFrameTrx(trxTablePtr->ptrxId, &e1Id, &lapdTs);
      if(CFG_FAILURE == retVal)
      {
          return retVal;
      }
   }

   if(getMccE1Ts(e1Id, lapdTs, &mccE1, &mccTs) == CFG_FAILURE)
   {
      LOG_PRINT(LOG_MAJOR,"populateTrxTsTeiTable : No mccE1 and mccTs for E1 :%d, Ts :%d",
							 e1Id, lapdTs);
      if(TRX_LOCATION_IN_FRAME != trxTablePtr->trxLocation)
      free(bicTrxTimeSlotUsageTablePtr);
      return CFG_FAILURE;	
   }
   
   e1StreamMapTableIndices.e1Num = mccE1;
   e1StreamMapTableIndices.e1Ts = mccTs;
   if(getE1StreamMapTable(&e1StreamMapTableIndices , &E1StreamMapTableApiPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"populateTrxTsTeiTable : No rows in E1StreamMap table");
      if(TRX_LOCATION_IN_FRAME != trxTablePtr->trxLocation)
      free(bicTrxTimeSlotUsageTablePtr);
      return CFG_FAILURE;
   }
   
   LOG_PRINT(LOG_INFO,"populateTrxTsTeiTable : strmTs are :%d", E1StreamMapTableApiPtr->strmTs);

   /* Populate Table TrxTsTeiTable */
   trxTsTeiTableApi.ptrxId = trxTablePtr->ptrxId;

	 if (trxTablePtr->trxLocation == TRX_LOCATION_R2_BTS)
   {
      lapdTeiConfigTblIndex.lapdtimeslot = E1StreamMapTableApiPtr->strmTs;
      lapdTeiConfigTblIndex.lapdTei = TRX_POSITION_1;
  
      if(isTeiAllocated(&lapdTeiConfigTblIndex,&applTei) == I_TRUE)
      {
         lapdTeiConfigTblIndex.lapdTei = TRX_POSITION_2;
         if(isTeiAllocated(&lapdTeiConfigTblIndex, &applTei) == I_TRUE)
         {
            LOG_PRINT(LOG_MAJOR,"NO applTei could be allocated for given lapdTs:%d", lapdTeiConfigTblIndex.lapdtimeslot);
            free(bicTrxTimeSlotUsageTablePtr);
            return CFG_FAILURE;
           
         } 
      }  
       
      LOG_PRINT(DEBUG,"Alloacated Tei is :%d",applTei);
	    trxTsTeiTableApi.trxTei = applTei;
      free (E1StreamMapTableApiPtr); 
       
   }
   else
   {
      /*Initializing LapdTeiConfigTable Data */
      retVal = getallLapdTEIConfigTable(&LapdTEIConfigTableApiPtr, &lapdTeiRecCount, &lapdTeiRecSz);
      if(retVal != DBLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"initAbisE1TsList : No Rows in LapdTEIConfigTable");
         if(TRX_LOCATION_IN_FRAME != trxTablePtr->trxLocation)
         free(bicTrxTimeSlotUsageTablePtr);
         free(E1StreamMapTableApiPtr);
         return CFG_FAILURE;
      }
      
      tmpLapdTeiConfigPtr = LapdTEIConfigTableApiPtr;
      for(count = 0; count < lapdTeiRecCount; count++)
      {
         /* Fixed Mantis : #4818 : Start */
         tmpLapdTeiConfigPtr = ( LapdTEIConfigTableApi *)(((I_U8 *)( LapdTEIConfigTableApiPtr)) + 
	     					(count * lapdTeiRecSz));
         /* Fixed Mantis : #4818 : End */
         if(tmpLapdTeiConfigPtr->lapdtimeslot == E1StreamMapTableApiPtr->strmTs)
         {
	    if (trxTablePtr->trxLocation==TRX_LOCATION_BIC && tmpLapdTeiConfigPtr->lapdTei == ONE)
	    {
	       trxTsTeiTableApi.trxTei = tmpLapdTeiConfigPtr->applTei;
	       break;
	    }
      #if 0
	    else if (trxTablePtr->trxLocation==TRX_LOCATION_R2_BTS && tmpLapdTeiConfigPtr->lapdTei == trxTablePtr->trxPos)
	    {
	       trxTsTeiTableApi.trxTei = tmpLapdTeiConfigPtr->applTei;
	       break;
	    }
      #endif
	    else if (trxTablePtr->trxLocation==TRX_LOCATION_IN_FRAME && tmpLapdTeiConfigPtr->lapdTei == ONE)//A6 inframe change for lapdTei
	    {
	       trxTsTeiTableApi.trxTei = tmpLapdTeiConfigPtr->applTei;
	       break;
	    }
         }	
      }
      free(LapdTEIConfigTableApiPtr);
      free (E1StreamMapTableApiPtr); 
      if(count == lapdTeiRecCount)
      {
         LOG_PRINT(LOG_MAJOR," populateTrxTsTeiTable : TimeSlot Mismatch ");
         if(TRX_LOCATION_IN_FRAME != trxTablePtr->trxLocation)
         free(bicTrxTimeSlotUsageTablePtr);
         return CFG_FAILURE;
      }
   }
   if(trxTablePtr->trxLocation==TRX_LOCATION_IN_FRAME )
   {  
      trxTsTeiTableApi.e1Id = e1Id;
      trxTsTeiTableApi.lapdTs = lapdTs;
      trxTsTeiTableApi.lapdLinkStatus = ZERO; 
      trxTsTeiTableApi.firstTsTraffic = lapdTs + 1;
      trxTsTeiTableApi.secondTsTraffic= lapdTs + 2;
   }
   else
   {  
      trxTsTeiTableApi.e1Id = bicTrxTimeSlotUsageTablePtr->e1Id;
      trxTsTeiTableApi.lapdTs = bicTrxTimeSlotUsageTablePtr->lapdTs;
      trxTsTeiTableApi.lapdLinkStatus = ZERO; 
      trxTsTeiTableApi.firstTsTraffic = bicTrxTimeSlotUsageTablePtr->trafficTrxTs1;
      trxTsTeiTableApi.secondTsTraffic= bicTrxTimeSlotUsageTablePtr->trafficTrxTs2;
   }
   if(TRX_LOCATION_IN_FRAME != trxTablePtr->trxLocation)
   free(bicTrxTimeSlotUsageTablePtr);
   retVal = insertTrxTsTeiTable(&trxTsTeiTableApi);
   if(retVal != DBLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"populateTrxTsTeiTable : Insert in DB failed" );
      return CFG_FAILURE;
   }
   LOG_PRINT(LOG_INFO,"populateTrxTsTeiTable : Exiting from the function "); 
   return  retVal;
}
/********************************* Function  Header********************************
Function Name:       insertRowInBicTrxTimeslotUsageTable()
Parameters:          I_U32 trxId, I_U32 e1Id, I_U32 startTs
Return type:         I_S32
Purpose:             To insert a row in BicTrxTimeslotUsage table.	
Other Note:
************************************************************************************/
#if 0
I_S32 insertRowInBicTrxTimeslotUsageTable(I_U32 trxId, I_U32 e1Id, I_U32 startTs)
{
   BicTrxTimeslotUsageTableApi bicTrxTimeSlotUsageTableApi;

   LOG_PRINT(LOG_INFO,"insertRowInBicTrxTimeslotUsageTable: Entering in to funtion");
   LOG_PRINT(LOG_DEBUG,"insertRowInBicTrxTimeslotUsageTable: Received ptrxId : %d, e1Id : %d, startTs : %d",
								trxId, e1Id, startTs);
   bicTrxTimeSlotUsageTableApi.tsUser = TS_USAGE_BICTRX;
   bicTrxTimeSlotUsageTableApi.bicOrTrxId = trxId;
   bicTrxTimeSlotUsageTableApi.e1Id = e1Id;
   bicTrxTimeSlotUsageTableApi.startTs = startTs;
   bicTrxTimeSlotUsageTableApi.numTs = 3;
   if(insertBicTrxTimeslotUsageTable(&bicTrxTimeSlotUsageTableApi) != DBLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertRowInBicTrxTimeslotUsageTable: No row inserted in BicTrxTimeslotUsgaeTable");
      return CFG_FAILURE;
   }

   LOG_PRINT(LOG_INFO,"insertRowInBicTrxTimeslotUsageTable: Exiting from function");
   return CFG_SUCCESS;
}
#endif

/********************************* Function  Header********************************
Function Name:       populateBicTeiE1MapTable()
Parameters:          void
Return type:         void
Purpose:             To populate BicTeiE1MapTable.	
Other Note:
 ************************************************************************************/
#if 0
I_Void populateBicTeiE1MapTable() 
{
   LOG_PRINT(LOG_INFO , "populateBicTeiE1MapTable : Entering in the function");
   
   fetchE1AndInsertInBicTeiMapTable(SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10);
   fetchE1AndInsertInBicTeiMapTable(SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1);
   fetchE1AndInsertInBicTeiMapTable(SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4);
   fetchE1AndInsertInBicTeiMapTable(SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7);

   LOG_PRINT(LOG_INFO , "populateBicTeiE1MapTable : Exiting from the function"); 
   return;
}
#endif

/********************************* Function  Header********************************
Function Name:       fetchE1AndInsertInBicTeiMapTable()
Parameters:          e1Type :: I_U8
Return type:         I_Void
Purpose:             To fetch E1 from E1 table and insert a row in BicTeiE1MapTable.
Other Note:
************************************************************************************/
#if 0
I_Void fetchE1AndInsertInBicTeiMapTable(I_U8 e1Type)
{
   I_U32 *tmpE1Id = NULL;
   I_S32 retVal;
   I_U16 count =0;
   I_U32 e1RecCount = 0;

   LOG_PRINT(LOG_INFO, "fetchE1AndInsertInBicTeiMapTable: Entering in the function");

   if(getE1NumTrunkTable(e1Type, &tmpE1Id, &e1RecCount) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG,"fetchE1AndInsertInBicTeiMapTable : There is no E1 for the usage type [%d]", e1Type); 
      return;
   }
   for(count = 0 ; count < e1RecCount ; count++)
   {
      retVal = addE1DataBicTeiE1MapTable(tmpE1Id[count]);
   }   

   free(tmpE1Id);
   LOG_PRINT(LOG_INFO, "fetchE1AndInsertInBicTeiMapTable: Exiting from the function");
}

#endif
/********************************* Function  Header********************************
Function Name	: initAbisE1TsList()
Parameters	: None
Return type	: I_Void
Purpose		: It create AbisE1Ts list at the time of CFG initialization.
Other Note	:
************************************************************************************/
#if 0
I_Void initAbisE1TsList() 
{
   I_U32 *e1Num = NULL;
   I_U32 e1RecCount = ZERO;
   I_U32 i = ZERO;
   I_S32 retVal = -1;
   OamsCfgBichInitAbisE1 oamsCfgBichInitAbisE1;

   LOG_PRINT(LOG_INFO,"initAbisE1TsList : Entering in the function");
   gIsListCreated = TRUE;
   INIT_OAMS_LIST(&head);

   /* Initializing LapdTeiConfigTable Data */	
   retVal = getallLapdTEIConfigTable(&LapdTEIConfigTableApiPtr, &lapdTeiRecCount, &lapdTeiRecSz); 
   if(retVal != DBLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"initAbisE1TsList : No Rows in LapdTEIConfigTable");
      return ;
   }

   /* Populating AbisE1TsList */	
   if(getE1NumTrunkTable(SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10, &e1Num, &e1RecCount) == DBLIB_SUCCESS)
   {
      for(i = 0; i < e1RecCount; i++)
      {
	 retVal = addE1InAbisE1TsList(e1Num[i], SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10);
	 addE1DataBicTeiE1MapTable(e1Num[i]);
	 oamsCfgBichInitAbisE1.e1Id = e1Num[i];
	 if(CFG_SUCCESS == retVal)
	    cfgSendMessage(&oamsCfgBichInitAbisE1, sizeof(OamsCfgBichInitAbisE1), ENT_OAMS_BICH,
							OAMS_CFG_BICH_INIT_ABIS_E1,0);
      }
      free(e1Num);
   }
   if(getE1NumTrunkTable(SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1, &e1Num, &e1RecCount) == DBLIB_SUCCESS)
   {
      for(i = 0; i < e1RecCount; i++)
      {
	 retVal = addE1InAbisE1TsList(e1Num[i], SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1);
	 addE1DataBicTeiE1MapTable(e1Num[i]);
	 oamsCfgBichInitAbisE1.e1Id = e1Num[i];
	 if(CFG_SUCCESS == retVal)
	    cfgSendMessage(&oamsCfgBichInitAbisE1, sizeof(OamsCfgBichInitAbisE1), ENT_OAMS_BICH,
							OAMS_CFG_BICH_INIT_ABIS_E1,0);
      }
      free(e1Num);
   }
   if(getE1NumTrunkTable(SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4, &e1Num, &e1RecCount) == DBLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"getE1NumTrunkTable ret SUCCESS count(%d)",e1RecCount);
      for(i = 0; i < e1RecCount; i++)
      {
	        retVal = addE1InAbisE1TsList(e1Num[i], SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4);
	        addE1DataBicTeiE1MapTable(e1Num[i]);
          oamsCfgBichInitAbisE1.e1Id = e1Num[i];
       	  if(CFG_SUCCESS == retVal)
        	    cfgSendMessage(&oamsCfgBichInitAbisE1, sizeof(OamsCfgBichInitAbisE1), ENT_OAMS_BICH,
				        	OAMS_CFG_BICH_INIT_ABIS_E1,0);
      }
      free(e1Num);
   }
   if(getE1NumTrunkTable(SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7, &e1Num, &e1RecCount) == DBLIB_SUCCESS)
   {
      for(i = 0; i < e1RecCount; i++)
      {
	 retVal = addE1InAbisE1TsList(e1Num[i], SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7);
	 addE1DataBicTeiE1MapTable(e1Num[i]);
	 oamsCfgBichInitAbisE1.e1Id = e1Num[i];
	 if(CFG_SUCCESS == retVal)
	    cfgSendMessage(&oamsCfgBichInitAbisE1, sizeof(OamsCfgBichInitAbisE1), ENT_OAMS_BICH,
							OAMS_CFG_BICH_INIT_ABIS_E1,0);
      }
      free(e1Num);
   }
   
   LOG_PRINT(LOG_INFO,"initAbisE1TsList : Exiting from the function");
   return ;
}
#endif

/********************************* Function  Header********************************
Function Name:       delTrxTsTeiTable()
Parameters:          ptrxId :: I_U32 
Return type:         I_Void
Purpose:             To free timeslot and remove row from TrxTsTeiTable.	
Other Note:
************************************************************************************/
I_Void delTrxTsTeiTable(I_U32 ptrxId) 
{
   TrxTsTeiTableIndices trxTsTeiTableIndices;

   LOG_PRINT(LOG_INFO,"delTrxTsTeiTable : Entering in the function");
   LOG_PRINT(LOG_DEBUG,"delTrxTsTeiTable : Received ptrxId [%d]", ptrxId);

   trxTsTeiTableIndices.ptrxId = ptrxId;

   if(deleteTrxTsTeiTable( &trxTsTeiTableIndices) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delTrxTsTeiTable : No row deleted for trx Id [%d]" , ptrxId);	
      return ; 
   }

   LOG_PRINT(LOG_INFO , "delTrxTsTeiTable : Exiting from the function");
   return ;		
}

/********************************* Function  Header********************************
Function Name:       markFreeAbisTimeSlotTable()
Parameters:          ptrxId :: I_U32 
Return type:         I_S32
Purpose:             To free timeslot from AbisTimeSlot Table for Lapd & Traffic 
Other Note:
************************************************************************************/
I_S32 markFreeAbisTimeSlotTable(I_U32 ptrxId) 
{
   TrxTsTeiTableIndices trxTsTeiTableIndices;
   TrxTsTeiTableApi*    trxTsTeiTableDbPtr;
   TrxTableIndices      trxTableInd;
   TrxTableApi*		trxTableDbPtr;
   LOG_PRINT(LOG_INFO,"updateAbisTimeSlotTable: Entering in the function");
   LOG_PRINT(LOG_DEBUG,"updateAbisTimeSlotTable: Received ptrxId [%d]", ptrxId);

   trxTableInd.ptrxId=ptrxId;
   if(getTrxTable(&trxTableInd,&trxTableDbPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"DB Call : getTrxTable failed");
      return CFG_FAILURE;
   }
  
   trxTsTeiTableIndices.ptrxId = ptrxId;
   if(getTrxTsTeiTable(&trxTsTeiTableIndices,&trxTsTeiTableDbPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"DB Call : getTrxTsTeiTable failed");
      free(trxTableDbPtr); 
      return CFG_FAILURE;
   }
   
   if (trxTableDbPtr->trxLocation == TRX_LOCATION_BIC || trxTableDbPtr->trxLocation == TRX_LOCATION_IN_FRAME) //A6 inframe changes
   {
     /* Update Lapd Time Slot as free only in case of Bic */
     LOG_PRINT(INFO,"DEL_TRX_RESP :updateRowAbisTimeSlotPerTable : E1Id :%d ,LapdTs: %d",trxTsTeiTableDbPtr->e1Id,trxTsTeiTableDbPtr->lapdTs);
     if (updateRowAbisTimeSlotPerTable(trxTsTeiTableDbPtr->e1Id,trxTsTeiTableDbPtr->lapdTs,SYS_TS_USAGE_ABIS_FREE) != CFG_SUCCESS)
    {
	LOG_PRINT(LOG_INFO,"Error in updating Lapd Timeslot for Ptrx Id : %d",ptrxId);
        free(trxTableDbPtr);
   	free(trxTsTeiTableDbPtr);
	return CFG_FAILURE;
    }
   }

/*Update Traffic timeslots for R1-BIC-TRX/R2-BIC-TRX both */
   LOG_PRINT(INFO,"DEL_TRX_RESP :updateRowAbisTimeSlotPerTable : E1Id :%d ,firstTrafficTs: %d,secondTrafficTs:%d",trxTsTeiTableDbPtr->e1Id,trxTsTeiTableDbPtr->firstTsTraffic,trxTsTeiTableDbPtr->secondTsTraffic);
   if (updateRowAbisTimeSlotPerTable(trxTsTeiTableDbPtr->e1Id,trxTsTeiTableDbPtr->firstTsTraffic,SYS_TS_USAGE_ABIS_FREE) != CFG_SUCCESS)
   {
        LOG_PRINT(LOG_INFO,"Error in updating Traffic  Timeslot for Ptrx Id : %d",ptrxId);
        free(trxTableDbPtr);
   	free(trxTsTeiTableDbPtr);
        return CFG_FAILURE;
   }
   if (updateRowAbisTimeSlotPerTable(trxTsTeiTableDbPtr->e1Id,trxTsTeiTableDbPtr->secondTsTraffic,SYS_TS_USAGE_ABIS_FREE) != CFG_SUCCESS)
   {
        LOG_PRINT(LOG_INFO,"Error in updating Traffic  Timeslot for Ptrx Id : %d",ptrxId);
        free(trxTableDbPtr);
   	free(trxTsTeiTableDbPtr);
        return CFG_FAILURE;
   }
   free(trxTableDbPtr);
   free(trxTsTeiTableDbPtr);

   LOG_PRINT(LOG_INFO , "updateAbisTimeSlotTable: Exiting from the function");
   return CFG_SUCCESS;		
}

/********************************* Function  Header********************************
Function Name:       isTimeslotAvailable()
Parameters:          I_U32 e1Id I_U8 tsType
Return type:         I_Bool
Purpose:             To check whther any timeslot for e1 is avaliable 	
Other Note:
************************************************************************************/
#if 0
I_Bool isTimeslotAvailable(I_U32 e1Id, I_U8 tsType)
{
   I_U32 i;
   I_Bool result = FALSE;
   I_Bool flag = FALSE;
   OamsList *ptr;
   OamsList *tmpPtr;
   E1TimeSlot *e1TimeSlot = NULL;

   LOG_PRINT(LOG_INFO , "isTimeSlotAvailable : Entering in the function");
   LOG_PRINT(LOG_DEBUG, "isTimeSlotAvailable : Received e1Id : %d, tsUsageType : %d", e1Id, tsType);

   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if(e1TimeSlot->e1Id == e1Id)
      {
	       flag = TRUE;
      	 for(i = 0; i < e1TimeSlot->numTs; i++)
	       {
	           if(e1TimeSlot->timeSlotUsage[i].status == TIMESLOT_STATUS_FREE && 
                 e1TimeSlot->timeSlotUsage[i].tsType == tsType )
	           {
	              result = TRUE;
        	      break;
        	   }	
	       }
      	 if(i == e1TimeSlot->numTs)
      	 {
	          LOG_PRINT(LOG_INFO,"isTimeSlotAvailable : No Timeslot Free"); 
      	    result = FALSE;
      	 }
      }
   }

   if(flag == FALSE)
   {
      LOG_PRINT(LOG_INFO,"isTimeSlotAvailable : E1 Mismatch ");	
      return FALSE;
   }

   LOG_PRINT(LOG_INFO ,"isTimeSlotAvailable : Exiting from the function");
   return result;
}
#endif

/********************************* Function  Header********************************
Function Name:       getMccE1Ts()
Parameters:          I_U32 firstE1, I_U32 firstTs, I_U32 secondE1, I_U32 secondTs
Return type:         I_U8
Purpose:             To get mccE1 and mccTs from DB.	
Other Note:
************************************************************************************/
I_S32 getMccE1Ts(I_U32 firstE1, I_U32 firstTs, I_U32 *secondE1, I_U32 *secondTs) 
{
/*
   AbisE1TsMccE1TsMapTableIndices abisE1TsMccE1TsMapIndices;
   AbisE1TsMccE1TsMapTableApi *AbisE1TsMccE1TsTableApiPtr = NULL;
   abisE1TsMccE1TsMapIndices.abisE1Id = firstE1;
   abisE1TsMccE1TsMapIndices.abisE1Ts = firstTs;
*/
   MccLinkResourceTableApi *mccLinkResourceTableApiPtr = NULL;
   I_U32 outCount = 0;
   I_U16 outSize = 0;

   LOG_PRINT(LOG_INFO,"getMccE1Ts : Entering in the function");
   LOG_PRINT(LOG_DEBUG,"getMccE1Ts : Received firstE1 : %d, firstTs : %d",firstE1, firstTs);

   if(getMccTrunkNumTsUsingExtTrunkNumTs(firstE1,firstTs,&mccLinkResourceTableApiPtr,&outCount,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"getMccE1Ts : There is no MCC time slot for e1Id [%d]", firstE1);
      return CFG_FAILURE;
   }

   *secondE1 = mccLinkResourceTableApiPtr->mccTrunkNum; 
   *secondTs = mccLinkResourceTableApiPtr->mccTrunkTs;

   LOG_PRINT(LOG_DEBUG,"getMccE1Ts : secondE1 : %d, secondTs : %d",mccLinkResourceTableApiPtr->mccTrunkNum,mccLinkResourceTableApiPtr->mccTrunkTs);
   free (mccLinkResourceTableApiPtr);
   LOG_PRINT(LOG_INFO , "getMccE1Ts : Exiting from the function");
   return CFG_SUCCESS;
}

/********************************* Function  Header********************************
Function Name:       getNumTrxPerE1()
Parameters:          I_U32 E1Id, I_U8 tsType
Return type:         I_U32
Purpose:             To get number of TRX for e1
Other Note:
************************************************************************************/
#if 0
I_U32 getNumTrxPerE1(I_U32 E1Id)
{
   I_U32 numTs = 0;
   I_U32 countTs = 0;
   I_U32 retVal;
   I_Bool flag = FALSE;
   OamsList *ptr;
   OamsList *tmpPtr;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U16 count;
   LOG_PRINT(LOG_INFO , "getNumTrxPerE1 : Entering in the function");
   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if(e1TimeSlot->e1Id == E1Id)
      {
	 flag = TRUE;
         numTs = e1TimeSlot->numTs;
         for(count = 0 ; count < e1TimeSlot->numTs; count++ )
         {
            if(e1TimeSlot->timeSlotUsage[count].tsType == TS_USAGE_LAPD_BIC)
            {
               countTs ++;
            }
         }
      }
   }
   if(flag == FALSE)
   {
      LOG_PRINT(LOG_INFO," getNumTrxPerE1 : E1 Mismatch ");	
      return ZERO; 
   }

   retVal = numTs - countTs;

   LOG_PRINT(LOG_INFO , "getNumtrxPerE1 : Exiting from the function");
   return retVal;
}
#endif

/********************************* Function  Header********************************
Function Name:       addE1DataBicTeiE1MapTable()
Parameters:          I_U32 E1Id
Return type:         I_S32
Purpose:             To add a row in BicTeiE1MapTable.	
Other Note:
************************************************************************************/
#if 0
I_S32 addE1DataBicTeiE1MapTable(I_U32 E1Id)
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;   
   I_Bool flag = FALSE;
   I_U16 count = 0;
   I_U16 count1 = 0;
   I_U32 mccE1 = 0;
   I_U32 mccTs = 0;
   I_U32 strmTs = 0;
   I_U32 e1Ts = 0;
   I_U32 retVal;
   LapdTEIConfigTableApi *tmpLapdTeiConfigPtr = NULL;
   BicE1TeiMapTableApi bicE1TeiMapTableApi;
   /* Bug Fixed - Mantis#6185 : Start */
   E1StreamMapTableIndices e1StreamMapTableIndices;
   E1StreamMapTableApi     *e1StreamMapTableApiPtr = NULL;
   /* Bug Fixed - Mantis#6185 : End */

   LOG_PRINT(LOG_INFO, "addE1DataBicTeiE1MapTable : Entering in the function");

   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if(e1TimeSlot->e1Id == E1Id)
      {
         flag = TRUE;
         for(count = 0 ; count < e1TimeSlot->numTs ; count++)
         {
            if(e1TimeSlot->timeSlotUsage[count].tsType == TS_USAGE_LAPD_BIC)
            {
               e1Ts = e1TimeSlot->timeSlotUsage[count].timeSlot;
               if(getMccE1Ts(E1Id, e1Ts, &mccE1, &mccTs) == CFG_FAILURE)
               {
                  LOG_PRINT(LOG_MAJOR,"addE1DataBicTeiE1MapTable : No mccE1 and mccTs for E1 [%d] and allocatedTs [%d]" , E1Id, e1Ts)
                  return CFG_FAILURE;
               }
               /* Bug Fixed - Mantis#6185 : Start */
               e1StreamMapTableIndices.e1Num = mccE1;
               e1StreamMapTableIndices.e1Ts  = mccTs;
               if(getE1StreamMapTable(&e1StreamMapTableIndices, &e1StreamMapTableApiPtr) != CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_MAJOR,"addE1DataBicTeiE1MapTable : No rows in E1StreamMap table");
                  return CFG_FAILURE;
               }
               bicE1TeiMapTableApi.e1Id = E1Id;
               bicE1TeiMapTableApi.e1Ts = e1Ts;
               strmTs                    = e1StreamMapTableApiPtr->strmTs;
	       free(e1StreamMapTableApiPtr);
               /* Bug Fixed - Mantis#6185 : End */
               tmpLapdTeiConfigPtr = LapdTEIConfigTableApiPtr;
               for(count1 = 0; count1 < lapdTeiRecCount ; count1++)
               {
                  tmpLapdTeiConfigPtr = (LapdTEIConfigTableApi *)(((I_U8 *)(LapdTEIConfigTableApiPtr)) + (count1 * lapdTeiRecSz));
                  if(tmpLapdTeiConfigPtr->lapdtimeslot == strmTs)
                  {
                     bicE1TeiMapTableApi.bicTei = tmpLapdTeiConfigPtr->applTei;
                     break;
                  }
               }
               if(count1 == lapdTeiRecCount)
               {
                  LOG_PRINT(LOG_MAJOR, "addE1DataBicTeiE1MapTable : Mcc Timeslot Mismatch");
                  return CFG_FAILURE;
               }

               LOG_PRINT(LOG_DEBUG,"addE1DataBicTeiE1MapTable : e1Id = [%d], e1Ts = [%d], bicTei = [%d]",
					 bicE1TeiMapTableApi.e1Id, bicE1TeiMapTableApi.e1Ts, 
								bicE1TeiMapTableApi.bicTei);
               retVal = insertBicE1TeiMapTable(&bicE1TeiMapTableApi);
            }
         }
      }
   }
   if(flag == FALSE)
   {
      LOG_PRINT(LOG_MAJOR,"addE1DataBicTeiE1MapTable : E1 Id [%d] Mismatch" , E1Id);
      return CFG_FAILURE;
   }

   LOG_PRINT(LOG_INFO, "addE1DataBicTeiE1MapTable : Exiting from the function");
   return CFG_SUCCESS;
}
#endif

/********************************* Function  Header********************************
Function Name:       deleteE1DataBicTeiE1MapTable()
Parameters:          I_U32 E1Id
Return type:         I_Void
Purpose:             To delete a row in BicTeiE1MapTable.	
Other Note:
************************************************************************************/
#if 0
I_Void deleteE1DataBicTeiE1MapTable(I_U32 E1Id)
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U16 count = 0;
   I_Bool flag = FALSE;
   
   LOG_PRINT(LOG_INFO, "deleteE1DataBicTeiE1MapTable: Entering in the function");
   LOG_PRINT(LOG_DEBUG,"deleteE1DataBicTeiE1MapTable : Received e1Id : %d", E1Id);

   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if(e1TimeSlot->e1Id == E1Id)
      {
         flag=TRUE;
         for(count =0; count < e1TimeSlot->numTs ; count++)
         {
            if(e1TimeSlot->timeSlotUsage[count].tsType == TS_USAGE_LAPD_BIC)
            {
   	       deleteBicTeiMapTableTer(E1Id, e1TimeSlot->timeSlotUsage[count].timeSlot);
            }
         }
      }
   }
   if(flag == FALSE)
   {
      LOG_PRINT(LOG_MAJOR, "deleteE1DataBicTeiE1MapTable: E1 Id [%d] mismatch" , E1Id);
   }

   LOG_PRINT(LOG_INFO, "deleteE1DataBicTeiE1MapTable : Exiting from the function");
}
#endif

/********************************* Function  Header********************************
Function Name:       allocateTsForBic()
Parameters:          I_U32 E1Id, I_U8 e1UsageType
Return type:         I_U32
Purpose:             To Allocate time slot for BIC.       
Other Note:
************************************************************************************/
#if 0
I_U32 allocateTsForBic(I_U32 E1Id, I_U8 e1UsageType)
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U16 count = 0;
   I_U32 e1Ts = 0;
   I_Bool flag = FALSE;

   LOG_PRINT(LOG_INFO,"allocateTsForBic: Entering in the function");
   LOG_PRINT(LOG_DEBUG,"allocateTsForBic: Received e1Id : %d, e1UsageType : %d", 
								E1Id, e1UsageType);
   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if(e1TimeSlot->e1Id == E1Id)
      {
         flag = TRUE;
         for(count = 0 ; count < e1TimeSlot->numTs ; count++)
         {
            if(e1TimeSlot->timeSlotUsage[count].tsType == TS_USAGE_LAPD_BIC &&
                  e1TimeSlot->timeSlotUsage[count].status == TIMESLOT_STATUS_FREE)
            {
               e1TimeSlot->timeSlotUsage[count].status = TIMESLOT_STATUS_BUSY;
               e1Ts = e1TimeSlot->timeSlotUsage[count].timeSlot;
               break;
            }
            else if(e1TimeSlot->timeSlotUsage[count].tsType == TS_USAGE_LAPD_BIC &&
                    e1UsageType == SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10
		   )
            {
               e1Ts = e1TimeSlot->timeSlotUsage[count].timeSlot;
               break;
            }
         }
         if(count == e1TimeSlot->numTs)
         {
            LOG_PRINT(LOG_MAJOR,"allocateTsForBic : No timeslot available for E1 Id [%d] " , E1Id);
            return ZERO;   
         }
      }
   }
   if(flag == FALSE)
   {
      LOG_PRINT(LOG_MAJOR,"allocateTsForBic : E1 Id [%d] Mismatch" , E1Id);
      return ZERO;
   }

   LOG_PRINT(LOG_INFO,"allocateTsForBic : Exiting from the function");
   return e1Ts;
}
#endif
/********************************* Function  Header********************************
Function Name	: addE1InAbisE1TsList()
Parameters	: I_U32 : e1Id
		  I_U8  : e1UsageType
Return type	: I_S32
Purpose		: It add e1 in AbisE1TsList dynamically.
Other Note	:
************************************************************************************/
#if 0
I_S32 addE1InAbisE1TsList(I_U32 e1Id, I_U8 e1UsageType) 
{
   E1TimeSlot *e1TimeSlot = NULL;
   I_U32 *lapdTs = NULL, *temp = NULL;
   I_U32 rowCount = ZERO, trxTsNum = ZERO, i = ZERO, rowNumLapdTs = ZERO;
   I_U32 maxTsNum = ZERO, bicTsNum = ZERO, tsCount = ZERO;
   I_U32 lapdTsTrx[MAX_LAPD_BIC_IN_E1], lapdTsBic[MAX_LAPD_BIC_IN_E1]; 
   I_S32 retVal = CFG_FAILURE;
 
   LOG_PRINT(LOG_INFO,"addE1InAbisE1TsList : Entering in the function");
   LOG_PRINT(LOG_DEBUG,"addE1InAbisE1TsList : Received e1Id : %d, e1UsageType : %d",
								e1Id, e1UsageType);
   	
   if(getTsNumTimeSlotPerTable(e1Id, SYS_TS_USAGE_LAPD_TRX, &lapdTs, &rowNumLapdTs) == DBLIB_SUCCESS)
   {
      maxTsNum = rowNumLapdTs;
   }
   if(getTsNumTimeSlotPerTable(e1Id, SYS_TS_USAGE_LAPD_BIC, &temp, &rowCount) == DBLIB_SUCCESS)
   {
      bicTsNum = rowCount;
      for(i = 0; i < rowCount; i++)
      {
         lapdTsBic[i] = temp[i];
      }
      free(temp);
   }
   if(getTsNumTimeSlotPerTable(e1Id, SYS_TS_USAGE_ABIS_GENERIC, &temp, &rowCount) == DBLIB_SUCCESS)
   {
      free(temp);
      if((SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10 == e1UsageType) ||
         (SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1 == e1UsageType)
        )
      {
	 trxTsNum = 2;
	 lapdTsTrx[0] = 2;
	 lapdTsTrx[1] = 5;
      }
      else if(SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4 == e1UsageType)
      {
	 trxTsNum = 1;
	 for(i = 0; i < 3; i++)
	 {
	    lapdTsBic[bicTsNum] = (i + 2);
	    bicTsNum++;
	 }
	 lapdTsTrx[0] = 5;
      }
      else if(SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7 == e1UsageType)
      {
	 for(i = 0; i < 6; i++)
	 {
	    lapdTsBic[bicTsNum] = i + 2;
	    bicTsNum++;
	 }
      }
   }
  
   if(ZERO == maxTsNum)
   {
      LOG_PRINT(LOG_DEBUG,"addE1InAbisE1TsList : No LAPD_TRX TimeSlot in E1 : %d" ,e1Id);
      if(lapdTs != NULL)
      {
         free(lapdTs);
      }
      return retVal;
   }
   if(ZERO == bicTsNum)
   {
      LOG_PRINT(LOG_DEBUG,"addE1InAbisE1TsList : No LAPD_BIC TimeSlot in E1 : %d" ,e1Id);
      if(lapdTs != NULL)
      {
         free(lapdTs);
      }
      return retVal;
   }

   maxTsNum += (bicTsNum + trxTsNum);
   LOG_PRINT(LOG_DEBUG,"addE1InAbisE1TsList : maxTsNum : %d", maxTsNum);

   e1TimeSlot = (E1TimeSlot*)MALLOC(sizeof(E1TimeSlot) + (sizeof(TimeSlotUsage) * maxTsNum));
   LOG_PRINT(LOG_DEBUG,"addE1InAbisE1TsList : Memory Allocated : %p", e1TimeSlot);

   if(e1TimeSlot == NULL)
   {
      LOG_PRINT(LOG_MAJOR,"addE1InAbisE1TsList : Memory Allocation Failed"); 
      if(lapdTs != NULL)
      {
         free(lapdTs);
      }
      return retVal;
   }

   INIT_OAMS_LIST(&(e1TimeSlot->e1List));

   e1TimeSlot->e1Id = e1Id;
   e1TimeSlot->numTs = maxTsNum;
   e1TimeSlot->e1Type = e1UsageType;
   e1TimeSlot->isSharedAbisTsSwitched = FALSE;

   for(i = ZERO; i < bicTsNum; i++)
   {
      LOG_PRINT(LOG_DEBUG,"addE1InAbisE1TsList : E1 : %d, Ts : %d",e1Id, lapdTsBic[i]);
      e1TimeSlot->timeSlotUsage[tsCount].timeSlot = lapdTsBic[i];
      e1TimeSlot->timeSlotUsage[tsCount].status = TIMESLOT_STATUS_FREE;
      e1TimeSlot->timeSlotUsage[tsCount].tsType = TS_USAGE_LAPD_BIC;
      tsCount++;
   }
   for(i = ZERO; i < trxTsNum; i++)
   {
      LOG_PRINT(LOG_DEBUG,"addE1InAbisE1TsList : E1 : %d, Ts : %d",e1Id, lapdTsTrx[i]);
      e1TimeSlot->timeSlotUsage[tsCount].timeSlot = lapdTsTrx[i];
      e1TimeSlot->timeSlotUsage[tsCount].status = TIMESLOT_STATUS_FREE;
      e1TimeSlot->timeSlotUsage[tsCount].tsType = TS_USAGE_LAPD_TRX;
      tsCount++;
   }
   for(i = ZERO; i < rowNumLapdTs; i++)
   {
      LOG_PRINT(LOG_DEBUG,"addE1InAbisE1TsList : E1 : %d, Ts : %d",e1Id,lapdTs[i]);
      e1TimeSlot->timeSlotUsage[tsCount].timeSlot = lapdTs[i];
      e1TimeSlot->timeSlotUsage[tsCount].status = TIMESLOT_STATUS_FREE;
      e1TimeSlot->timeSlotUsage[tsCount].tsType = TS_USAGE_LAPD_TRX;
      tsCount++;
   }

   OAMS_LIST_ADD(&(e1TimeSlot->e1List) , &head);
   if(lapdTs != NULL)
   {
      free(lapdTs);
   }

   LOG_PRINT(LOG_INFO,"addE1InAbisE1TsList : Exiting from function");
   return CFG_SUCCESS;
}
#endif


/********************************* Function  Header********************************
Function Name	: delE1InAbisE1TsList()
Parameters	: I_U32 : e1Id
Return type	: I_Void
Purpose		: It delete e1 from AbisE1TsList dynamically           
Other Note	:
************************************************************************************/
#if 0
I_Void delE1InAbisE1TsList(I_U32 e1Id)
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;

   LOG_PRINT(LOG_INFO,"delE1InAbisE1TsList : Entering in the function");
   LOG_PRINT(LOG_DEBUG,"delE1InAbisE1TsList : Received e1Id : %d",e1Id);

   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      LOG_PRINT(LOG_INFO, "delE1InAbisE1TsList : Loop Running for e1Id [%d]", e1Id);
      e1TimeSlot = OAMS_LIST_ENTRY(ptr, E1TimeSlot, e1List);

      LOG_PRINT(LOG_INFO, "delE1InAbisE1TsList : e1TimeSlot->e1Id [%d]", e1TimeSlot->e1Id);
      if(e1TimeSlot->e1Id == e1Id)
      {
         LOG_PRINT(LOG_INFO, "delE1InAbisE1TsList : Memory Deallocated [%p]", e1TimeSlot);
         OAMS_LIST_DEL_N_FREE(&(e1TimeSlot->e1List),E1TimeSlot,e1List,free)
	   
      }
   }

   LOG_PRINT(LOG_INFO,"delE1InAbisE1TsList : Exiting from function");
}
#endif

/********************************* Function  Header********************************
Function Name	: getUsedLapdBicTsForE1()
Parameters	: e1Id        :: I_U32
		  e1TsList    :: I_U32*
	 	  tsListCount :: I_U32*
Return type	: I_S32
Purpose		: It prepare a list of all timeslots of type LAPD_BIC those have 
		  timeslot status as busy.
Other Note	:
************************************************************************************/
#if 0 
I_S32 getUsedLapdBicTsForE1(I_U32 e1Id, I_U32 *e1TsList, I_U32 *tsListCount)
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U16 count = 0;
   I_U32 e1Count = 0;
   I_Bool flag = FALSE;

   LOG_PRINT(LOG_INFO,"getUsedLapdBicTsForE1 : Entering in the function");
   LOG_PRINT(LOG_DEBUG,"getUsedLapdBicTsForE1 : Received e1Id = :%d", e1Id);

   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr, E1TimeSlot, e1List);
      if(e1TimeSlot->e1Id == e1Id)
      {
         for(count = 0 ; count < e1TimeSlot->numTs ; count++)
         {
            if(e1TimeSlot->timeSlotUsage[count].tsType == TS_USAGE_LAPD_BIC &&
                  e1TimeSlot->timeSlotUsage[count].status == TIMESLOT_STATUS_BUSY)
            {
               flag = TRUE;
               e1TsList[e1Count] = e1TimeSlot->timeSlotUsage[count].timeSlot;
	       e1Count++;
            }
         }
      }
   }
   if(flag == FALSE)
   {
      LOG_PRINT(LOG_INFO, "getUsedLapdBicTsForE1 : No Busy TimeSlot of Type LAPD_BIC in E1 : %d", e1Id);
      return CFG_FAILURE;
   }

   *tsListCount = e1Count;

   LOG_PRINT(LOG_INFO, "getUsedLapdBicTsForE1 : Exiting from the function");
   return CFG_SUCCESS;
}
#endif
/********************************* Function  Header********************************
Function Name:       markE1TsBusyInAbisList()
Parameters:          I_U32 E1Id, I_U8 startTs, I_U32 usage
Return type:         I_S32
Purpose:             To allocate timeslot at init.       
Other Note:          
************************************************************************************/
#if 0
I_S32 markE1TsBusyInAbisList(I_U32 E1Id, I_U8 startTs, I_U32 usage)
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U16 count = 0;
   I_Bool flag = FALSE;

   LOG_PRINT(LOG_INFO,"markE1TsBusyInAbisList: Entering in the function");
   LOG_PRINT(LOG_DEBUG,"markE1TsBusyInAbisList: Received e1Id : %d, e1Ts : %d",E1Id, startTs);

   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if(e1TimeSlot->e1Id == E1Id)
      {
         flag = TRUE;
         for(count = 0 ; count < e1TimeSlot->numTs ; count++)
         {
            if(e1TimeSlot->timeSlotUsage[count].timeSlot == startTs &&
                  e1TimeSlot->timeSlotUsage[count].status == TIMESLOT_STATUS_FREE)
            {
               e1TimeSlot->timeSlotUsage[count].status = TIMESLOT_STATUS_BUSY;
               break;
            }
	    else if(e1TimeSlot->e1Type == SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10 && 
		    e1TimeSlot->timeSlotUsage[count].status == TIMESLOT_STATUS_BUSY &&
            usage == TS_USAGE_LAPD_BIC
	           )
	    {
	       break;
	    }
	
         }
         if(count == e1TimeSlot->numTs)
         {
            LOG_PRINT(LOG_CRITICAL,"markE1TsBusyInAbisList : No timeslot available for E1 Id [%d] " , E1Id);
            return CFG_FAILURE;   
         }
      }
   }
   if(flag == FALSE)
   {
      LOG_PRINT(LOG_CRITICAL,"markE1TsBusyInAbisList : E1 Id [%d] Mismatch" , E1Id);
      return CFG_FAILURE;
   }

   LOG_PRINT(LOG_INFO,"markE1TsBusyInAbisList : Exiting from the function");
   return CFG_SUCCESS;
}
#endif

/********************************* Function  Header********************************
Function Name:       getE1TsForTrx()
Parameters:          I_U32 ptrxId, I_U8 trxType, I_U32 bicId, I_U32* e1Id, I_U32* e1Ts
Return type:         I_S32
Purpose:             It calculate firstE1 and firstTs used to populated TrxTsTeiTable       
Other Note:          
************************************************************************************/
#if 0
I_S32 getE1TsForTrx(I_U32 ptrxId, I_U8 trxType, I_U32 bicId, I_U32* e1Id, I_U32* e1Ts)
{
   E1TimeSlot *e1TimeSlot = NULL;
   I_U32 tmpE1Id = 0;
   I_U32 allocatedTs = 0;
   I_S32 retVal = CFG_FAILURE;
   I_Bool flag = FALSE;
   OamsList *ptr, *tmpPtr;
   I_U32 i;
   
   LOG_PRINT(LOG_INFO,"getE1TsForTrx : Entering in the function"); 

   if(trxType == TRX_LOCATION_BIC)
   {
      if(getE1IdBicTable(bicId , &tmpE1Id) != CLIB_SUCCESS)
      {
	 LOG_PRINT(LOG_CRITICAL,"getE1TsForTrx : No E1 for this BIC [%d] ", bicId);
	 return CFG_FAILURE;
      }
      LOG_PRINT(LOG_DEBUG,"getE1TsForTrx : E1 Id for Bic Id [%d] = %d",bicId,tmpE1Id);

      OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
      {
	 e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
	 if(e1TimeSlot->e1Id == tmpE1Id)
	 {
	    flag = TRUE;
	    for(i = 0 ; i < e1TimeSlot->numTs ; i++)
	    {
	       if(e1TimeSlot->timeSlotUsage[i].status == TIMESLOT_STATUS_FREE && 
                     e1TimeSlot->timeSlotUsage[i].tsType == TS_USAGE_LAPD_TRX)
	       {
                /* Mantis Fixed Starts- 7271 */
//		  e1TimeSlot->timeSlotUsage[i].status = TIMESLOT_STATUS_BUSY;
                /* Mantis Fixed Ends- 7271 */
		  allocatedTs = e1TimeSlot->timeSlotUsage[i].timeSlot;
		  break;
	       }
	    }
	    if(i == e1TimeSlot->numTs)
	    {
	       LOG_PRINT(LOG_MAJOR,"getE1TsForTrx : No timeslot available for E1 Id [%d] " , tmpE1Id);
	       return CFG_FAILURE;
	    }
	 }
      }
      if(flag == FALSE)
      {
	 LOG_PRINT(LOG_MAJOR,"getE1TsForTrx : E1 Id [%d] Mismatch" , tmpE1Id);
	 return CFG_FAILURE;
      }
   }
   else if(trxType == TRX_LOCATION_IN_FRAME)
   {
      retVal = getE1TsForInFrameTrx(ptrxId, &tmpE1Id, &allocatedTs);
      if(CFG_FAILURE == retVal)
	 return CFG_FAILURE;
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"getE1TsForTrx : trxType mismatch "); 
      return CFG_FAILURE;
   }

   *e1Id = tmpE1Id;
   *e1Ts = allocatedTs;

   LOG_PRINT(LOG_INFO,"getE1TsForTrx : Exiting from function");
   return CFG_SUCCESS;
}
#endif
/********************************* Function  Header********************************
Function Name:       getE1TsForInFrameTrx()
Parameters:          I_U32 ptrxId, I_U32* e1Id, I_U32* e1Ts
Return type:         I_S32
Purpose:             It calculate firstE1 & firstTs for In-Frame Trx.
Other Note:          
************************************************************************************/
I_S32 getE1TsForInFrameTrx(I_U32 ptrxId, I_U32* e1Id, I_U32* e1Ts)
{
   InFrameTrxE1TsTableIndices inFrameTrxE1TsTableIndices;
   InFrameTrxE1TsTableApi *inFrameTrxE1TsTableApiPtr = NULL;
   I_U16 trxPos = ZERO;

   LOG_PRINT(LOG_INFO,"getE1TsForInFrameTrx : Entering function");

   if(getTrxPosTrxTable(ptrxId, &trxPos) != DBLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"getE1TsForInFrameTrx : TRX Pos not Configured for ptrxId : %d", ptrxId);
      return CFG_FAILURE;
   }

   inFrameTrxE1TsTableIndices.trxPos = trxPos;
   if(getInFrameTrxE1TsTable(&inFrameTrxE1TsTableIndices , &inFrameTrxE1TsTableApiPtr) != DBLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"getE1TsForInFrameTrx : E1/TimeSlot Not Configured for Trx Pos : %d",
									 trxPos);
      return CFG_FAILURE;
   }

   *e1Id = inFrameTrxE1TsTableApiPtr->e1Id;
   *e1Ts = inFrameTrxE1TsTableApiPtr->startTs;

   free(inFrameTrxE1TsTableApiPtr);

   LOG_PRINT(LOG_INFO,"getE1TsForInFrameTrx : Exiting from function");
   return CFG_SUCCESS;
}

/********************************* Function  Header********************************
Function Name	: traverseAbisList()
Parameters	:        
Return type	: I_Void
Purpose		: Temporary function just for debugging purpose.       
Other Note	: Should be ommitted after SSI   
************************************************************************************/
#if 0
I_Void traverseAbisList()
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U32 i = 0;

   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if (e1TimeSlot->e1Id == 0) {
        i++;
      }
   }
}
#endif
/********************************* Function  Header********************************
Function Name	: getListValue()
Parameters	:        
Return type	: I_Void
Purpose		: Temporary function just for debugging purpose.       
Other Note	: Should be ommitted after SSI   
************************************************************************************/
#if 0
I_Void getListValue()
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U16 count = 0;
   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      LOG_PRINT(LOG_DEBUG,"E1Id :: %d ", e1TimeSlot->e1Id);
      LOG_PRINT(LOG_DEBUG,"numTs :: %d ", e1TimeSlot->numTs);
      LOG_PRINT(LOG_DEBUG,"e1Type :: %d ", e1TimeSlot->e1Type);
      LOG_PRINT(LOG_DEBUG,(e1TimeSlot->isSharedAbisTsSwitched==TRUE?"isSharedAbisTsSwitched :: TRUE":"isSharedAbisTsSwitched :: FALSE"));
      for(count = 0 ; count < e1TimeSlot->numTs ; count++)  
      {
         LOG_PRINT(LOG_DEBUG,"timeSlot :: %d ", e1TimeSlot->timeSlotUsage[count].timeSlot);
         LOG_PRINT(LOG_DEBUG,(e1TimeSlot->timeSlotUsage[count].tsType == TS_USAGE_LAPD_BIC?
			      "usageType :: TS_USAGE_LAPD_BIC" : "usageType :: TS_USAGE_LAPD_TRX"));
         LOG_PRINT(LOG_DEBUG,(e1TimeSlot->timeSlotUsage[count].status==TIMESLOT_STATUS_FREE?
                              "status :: TIMESLOT_STATUS_FREE":"status :: TIMESLOT_STATUS_BUSY"));
      }
   }
}
#endif
/********************************* Function  Header********************************
Function Name	: getTimeslotUsage()
Parameters	: I_U32 e1Id, I_U8 e1Ts
Return type	: I_U8
Purpose		: To get usage type of a timeslot for a e1. It return 0 if No 
		  timeslot found in AbisList.
Other Note	:          
************************************************************************************/
#if 0

I_U8 getTimeslotUsage(I_U32 e1Id, I_U8 e1Ts)
{
   OamsList *ptr = NULL;   
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U16 count =0;
   I_U8 tsType = ZERO;
   I_Bool flag = FALSE;

   LOG_PRINT(LOG_INFO, "getTimeslotUsage : Enetring in the function");

   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if(e1TimeSlot->e1Id == e1Id)
      {
         flag = TRUE;
         for(count = 0 ; count < e1TimeSlot->numTs ; count++)
         {
            if(e1TimeSlot->timeSlotUsage[count].timeSlot == e1Ts)
            {
               tsType = e1TimeSlot->timeSlotUsage[count].tsType;
               break;
            }
         }
	 /* Bug Fixed - Mantis#3866 : Start */
	 if(count == e1TimeSlot->numTs)
	 {
	    LOG_PRINT(LOG_INFO,"getTimeslotUsage : No TimeSlot Found in AbisList");
	    tsType = ZERO;
	 }
	 /* Bug Fixed - Mantis#3866 : End */
      }
   }
   LOG_PRINT(LOG_INFO, "getTimeslotUsage : Exiting from the function");
   return tsType;
}
#endif
/********************************* Function  Header********************************
Function Name	: getE1TypeFrmAbisList()
Parameters	: I_U32 e1Id
Return type	: I_U8
Purpose		: To get usage type of a e1.       
Other Note	:          
************************************************************************************/
#if 0
I_U8 getE1TypeFrmList(I_U32 e1Id)
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U8 e1Type = ZERO;
   LOG_PRINT(LOG_INFO, "getE1TypeFrmList : Entering in the function");
   
   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      LOG_PRINT(LOG_INFO, "getE1TypeFrmList : Loop Running for e1Id [%d]", e1Id);
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      LOG_PRINT(LOG_INFO, "getE1TypeFrmList : e1TimeSlot->e1Id [%d]", e1TimeSlot->e1Id);
      if(e1TimeSlot->e1Id == e1Id)
      {
         e1Type = e1TimeSlot->e1Type;
         break;
      }
   }
   LOG_PRINT(LOG_INFO, "getE1TypeFrmList : Exiting from the function");
   return e1Type;
}
#endif
/********************************* Function  Header********************************
Function Name	: isSharedAbisTsSwitched()
Parameters	: I_U32 e1Id
Return type	: I_Bool
Purpose		: To check whether switching for shared e1Id is done.       
Other Note	:          
************************************************************************************/
#if 0
I_Bool isSharedAbisTsSwitched(I_U32 e1Id)
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_Bool retVal = FALSE;
   
   LOG_PRINT(LOG_INFO, "isSharedAbisTsSwitched : Entering in the function");
   
   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if(e1TimeSlot->e1Id == e1Id)
      {
         retVal = e1TimeSlot->isSharedAbisTsSwitched;
         break;
      }
   }
   LOG_PRINT(LOG_INFO, "isSharedAbisTsSwitched : Exiting from the function");
   return retVal;
}
#endif
/********************************* Function  Header********************************
Function Name	: toggleSharedAbisTsSwitchedVar()
Parameters	: I_U32 e1Id
Return type	: I_Void
Purpose		: To toggle the value of isSharedAbisTsSwitched variable between TRUE and FALSE.
Other Note	:          
************************************************************************************/
#if 0
I_Void toggleSharedAbisTsSwitchedVar(I_U32 e1Id)
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   
   LOG_PRINT(LOG_INFO, "toggleSharedAbisTsSwitched: Entering in the function");
   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if(e1TimeSlot->e1Id == e1Id)
      {
         if(e1TimeSlot->isSharedAbisTsSwitched == TRUE)   
         {
            e1TimeSlot->isSharedAbisTsSwitched = FALSE;
         }
         else
         {
            e1TimeSlot->isSharedAbisTsSwitched = TRUE;
         }
         break;
      }
   }

   LOG_PRINT(LOG_DEBUG, "toggleSharedAbisTsSwitched: Value of isSharedAbisTsSwitched Variable for E1 : %d is %d", 
					e1Id, e1TimeSlot->isSharedAbisTsSwitched);

   LOG_PRINT(LOG_INFO, "toggleSharedAbisTsSwitched: Exiting from the function");
   return;
}
#endif

/********************************* Function  Header********************************
Function Name	: markTsStatusFreeInAbisList()
Parameters	: I_U32 e1Id, I_U32 e1Ts
Return type	: I_Void
Purpose		: It marks the status of received timeslot as FREE in AbisList.
Other Note	:          
************************************************************************************/
#if 0
I_Void markTsStatusFreeInAbisList(I_U32 e1Id, I_U32 e1Ts)
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U32 i = ZERO;

   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      if(e1TimeSlot->e1Id == e1Id)
      {
	 for(i = 0; i < e1TimeSlot->numTs; i++)
	 {
	    if(e1TimeSlot->timeSlotUsage[i].timeSlot == e1Ts) 
	    {
	       e1TimeSlot->timeSlotUsage[i].status = TIMESLOT_STATUS_FREE;
	       break;
	    }	
	 }
      } 
   }
}
#endif

/********************************* Function  Header********************************
Function Name	: getMaxTrxNumFrmAbisList()
Parameters	: None
Return type	: I_U32
Purpose		: It calculates the total numbers of timeslots available in AbisList 
		  of type LAPD_TRX.
Other Note	:          
************************************************************************************/
#if 0
I_U32 getMaxTrxNumFrmAbisList()
{
   OamsList *ptr = NULL;
   OamsList *tmpPtr = NULL;
   E1TimeSlot *e1TimeSlot = NULL;
   I_U32 i = ZERO, tsNum = ZERO;

   OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
   {
      e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
      for(i = 0; i < e1TimeSlot->numTs; i++)
      {
         if(e1TimeSlot->timeSlotUsage[i].tsType == TS_USAGE_LAPD_TRX)
         {
            tsNum++;
	 }
      } 
   }
   return tsNum;
}
#endif

/********************************* Function  Header*****************************
Function Name   : cfgCleanAbisE1TsList()
Parameters      : None
Return type     : I_Void
Purpose         : This function will free AbisE1Ts List. 
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/

#if 0
I_Void cfgCleanAbisE1TsList()
{
   I_U32 count;

   LOG_PRINT(LOG_INFO,"cfgCleanAbisE1TsList : Entering in function");
   
   for(count = 0; count < CFG_MAX_NUM_E1 ; count++)
   {
      if((gE1Data[count].usageType == SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10) ||
         (gE1Data[count].usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1) ||
         (gE1Data[count].usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4) ||
         (gE1Data[count].usageType == SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_7)
        )
      {
         LOG_PRINT(LOG_INFO,"cfgCleanAbisE1TsList : Deleting Abis E1 [%d] in List" , gE1Data[count].e1Number );
         delE1InAbisE1TsList(gE1Data[count].e1Number);
      }
   }
   LOG_PRINT(LOG_INFO,"cfgCleanAbisE1TsList : Exiting from function");
}
#endif

/********************************* Function  Header********************************
Function Name	: populateMccTableForTrx()
Parameters	: None
Return type	: I_U32
Purpose		: 
Other Note	:          
************************************************************************************/
#if 0
I_S32 populateMccTableForTrx(I_U32 ptrxId, I_U8 trxType, I_U32 bicId,MccLinkResourceTableApi *outMccLinkResourcePtr)
{
   E1TimeSlot *e1TimeSlot = NULL;
   I_U32 tmpE1Id = 0;
   I_U32 allocatedTs = 0;
   I_S32 retVal = CFG_FAILURE;
   I_Bool flag = FALSE;
   OamsList *ptr, *tmpPtr;
   I_U32 i;
   MccLinkResourceTableApi inMccLinkResourceData;
   LOG_PRINT(LOG_INFO,"getE1TsForTrx : Entering in the function");

   if(trxType == TRX_LOCATION_BIC)
   {
      if(getE1IdBicTable(bicId , &tmpE1Id) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"getE1TsForTrx : No E1 for this BIC [%d] ", bicId);
         return CFG_FAILURE;
      }
      LOG_PRINT(LOG_DEBUG,"getE1TsForTrx : E1 Id for Bic Id [%d] = %d",bicId,tmpE1Id);

      OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
      {
         e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
         if(e1TimeSlot->e1Id == tmpE1Id)
         {
            flag = TRUE;
            for(i = 0 ; i < e1TimeSlot->numTs ; i++)
            {
               if(e1TimeSlot->timeSlotUsage[i].status == TIMESLOT_STATUS_FREE &&
                     e1TimeSlot->timeSlotUsage[i].tsType == TS_USAGE_LAPD_TRX)
               {
		  allocatedTs = e1TimeSlot->timeSlotUsage[i].timeSlot;
                  break;
               }
            }
            if(i == e1TimeSlot->numTs)
            {
               LOG_PRINT(LOG_MAJOR,"getE1TsForTrx : No timeslot available for E1 Id [%d] " , tmpE1Id);
               return CFG_FAILURE;
            }
         }
      }
      if(flag == FALSE)
      {
         LOG_PRINT(LOG_MAJOR,"getE1TsForTrx : E1 Id [%d] Mismatch" , tmpE1Id);
         return CFG_FAILURE;
      }
   }
   else if(trxType == TRX_LOCATION_IN_FRAME)
   {
      retVal = getE1TsForInFrameTrx(ptrxId, &tmpE1Id, &allocatedTs);
      if(CFG_FAILURE == retVal)
         return CFG_FAILURE;
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"getE1TsForTrx : trxType mismatch ");
      return CFG_FAILURE;
   }

   inMccLinkResourceData.mccTrunkNum = outMccLinkResourcePtr->mccTrunkNum;
   inMccLinkResourceData.mccTrunkTs = outMccLinkResourcePtr->mccTrunkTs;
   inMccLinkResourceData.mccLinkType = outMccLinkResourcePtr->mccLinkType;
   inMccLinkResourceData.mccLinkStatus=SYS_TS_ALLOCATED;
   inMccLinkResourceData.cardNum= outMccLinkResourcePtr->cardNum;
   inMccLinkResourceData.extTrunkNum=tmpE1Id;
   inMccLinkResourceData.extTrunkTs= allocatedTs;
   LOG_PRINT(LOG_DEBUG,"Mark Busy MccTrunkNum =%d Ts =%d",outMccLinkResourcePtr->mccTrunkNum,outMccLinkResourcePtr->mccTrunkTs); 
   if (updateExtTrunkNumTsInMccLinkTable(&inMccLinkResourceData,1,sizeof(MccLinkResourceTableApi)) != CLIB_SUCCESS)
   {
        LOG_PRINT(LOG_MAJOR, "getE1TsForTrx: updateExtTrunkNumTsInMccLinkTable Failed..");
        return CFG_FAILURE;
   }
   free(outMccLinkResourcePtr);

   LOG_PRINT(LOG_INFO,"getE1TsForTrx : Exiting from function");
   return CFG_SUCCESS;

}
#endif

/********************************* Function  Header********************************
Function Name	: getLapdTsForTrx()
Parameters	: None
Return type	: I_U32
Purpose		: 
Other Note	:          
************************************************************************************/
#if 0 
I_S32 getLapdTsForTrx(I_U32 *trxLapdTs)
{
   E1TimeSlot *e1TimeSlot = NULL;
   I_U32 tmpE1Id = 0;
   I_U32 allocatedTs = 0;
   I_S32 retVal = CFG_FAILURE;
   I_Bool flag = FALSE;
   OamsList *ptr, *tmpPtr;
   I_U32 i;

   LOG_PRINT(LOG_INFO,"getLapdTsForTrx : Entering in the function");

   TrxTableApi* receivedMsgPtr = ( TrxTableApi* )(((I_U8 *)gCfgMsgBuf ) + sizeof(sCmMsg));

   if(receivedMsgPtr->trxLocation == TRX_LOCATION_BIC)
   {
      if(getE1IdBicTable(receivedMsgPtr->bicId , &tmpE1Id) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"getLapdTsForTrx : No E1 for this BIC [%d] ", receivedMsgPtr->bicId);
         return CFG_FAILURE;
      }
      LOG_PRINT(LOG_DEBUG,"getLapdTsForTrx : E1 Id for Bic Id [%d] = %d",receivedMsgPtr->bicId,tmpE1Id);

      OAMS_LIST_FOR_EACH(ptr,tmpPtr,&head)
      {
         e1TimeSlot = OAMS_LIST_ENTRY(ptr,E1TimeSlot,e1List);
         if(e1TimeSlot->e1Id == tmpE1Id)
         {
            flag = TRUE;
            for(i = 0 ; i < e1TimeSlot->numTs ; i++)
            {
               if(e1TimeSlot->timeSlotUsage[i].status == TIMESLOT_STATUS_FREE &&
                     e1TimeSlot->timeSlotUsage[i].tsType == TS_USAGE_LAPD_TRX)
               {
		  allocatedTs = e1TimeSlot->timeSlotUsage[i].timeSlot;
                  break;
               }
            }
            if(i == e1TimeSlot->numTs)
            {
               LOG_PRINT(LOG_MAJOR,"getLapdTsForTrx : No timeslot available for E1 Id [%d] " , tmpE1Id);
               return CFG_FAILURE;
            }
         }
      }
      if(flag == FALSE)
      {
         LOG_PRINT(LOG_MAJOR,"getLapdTsForTrx : E1 Id [%d] Mismatch" , tmpE1Id);
         return CFG_FAILURE;
      }
   }
   else if(receivedMsgPtr->trxLocation == TRX_LOCATION_IN_FRAME)
   {
      retVal = getE1TsForInFrameTrx(receivedMsgPtr->ptrxId, &tmpE1Id, &allocatedTs);
      if(CFG_FAILURE == retVal)
         return CFG_FAILURE;
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"getLapdTsForTrx : trxType mismatch ");
      return CFG_FAILURE;
   }
 
   *trxLapdTs = allocatedTs;

   LOG_PRINT(LOG_INFO,"getLapdTsForTrx : Exiting from function");
   return CFG_SUCCESS;

}
#endif
/********************************* Change History ******************************
  Release     	Patch   Author         		  Description
  BSC CS2.2		Gaurav 		Initial Draft
  BSC CS2.2		Kapil 		UT Changes
  BSC CS2.2		Kapil		Bug Fixed : CS2.2_SSI_013
  BSC CS2.2		Gaurav		Bug Fixed : CS2.2_SSI_015
 ************************************** End ***********************************/

