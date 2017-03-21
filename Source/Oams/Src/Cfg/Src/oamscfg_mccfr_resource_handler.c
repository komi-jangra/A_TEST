
/***********************************File Header ***************************
File Name        : oamscfg_mccfr_resouce_handler.c
Purpose          : This file contains CFG Nsvc Handler implementation
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent
CSCI ID          :
Version          :
 ************************************* End **********************************/
#include <oamscfg_includes.h>

                         /* Array that will be used to store all the 
                          * data related to Fr Mcc Resources */
static MccFrResource     gMccFrResourceMap[MAX_NUM_MCC_FR_TIMESLOTS]; 
static I_U8              gNumElemMccFrResourceMap; /* Number of valid Resources in Fr Mcc Resources */
static I_U8              gNumFreeTsMccFrResourceMap; /* Number of valid Free Resources in Fr Mcc Resources */

/********************************* Function  Header********************************
Function Name:       initMccFrResourceMap()
Parameters:          I_Void
Return type:         I_Void
Purpose:             Initializes gMccFrResourceMap and fill with all the Fr Mcc Resorces
                     fetched from MccLinkResource Table 
Other Note:
 ************************************************************************************/

I_Void initMccFrResourceMap(I_Void)
{
   E1StreamMapTableIndices  e1StreamMapTableIndicesBuff;
   MccLinkResourceTableApi *mccLinkResourceTablePtr      = NULL;
   MccLinkResourceTableApi *mccLinkResourceTableAllPtr   = NULL;
   E1StreamMapTableApi     *e1StreamMapTableApiPtr       = NULL;
   I_S32                    dbStatus                     = CLIB_SUCCESS;
   I_U32                    mccLinkType                  = SYS_TS_USAGE_FR;
   I_U32                    i                            = 0;
   I_U32                    rowCount                     = 0;
   I_U16                    outSize                      = 0;
   I_U8                     chasisFrameId                = 0xFF;
   I_U8                     slotId                       = 0xFF;

   LOG_PRINT(LOG_INFO, "Entering initMccFrResourceMap");
   
   for( i = 0; i < MAX_NUM_MCC_FR_TIMESLOTS; i++)
   {
      gMccFrResourceMap[i].isValid = FALSE;
      gMccFrResourceMap[i].isAllocated = FALSE;
      gMccFrResourceMap[i].mccE1 = CFG_INVALID_E1;
      gMccFrResourceMap[i].mccE1Ts = CFG_INVALID_E1_TS;
      gMccFrResourceMap[i].cardNum = ZERO;
      gMccFrResourceMap[i].mccStrmId = CFG_INVALID_E1;
      gMccFrResourceMap[i].mccStrmTs = CFG_INVALID_E1_TS;
      gMccFrResourceMap[i].frE1 = CFG_INVALID_E1;
      gMccFrResourceMap[i].frE1Ts = CFG_INVALID_E1_TS;
   }
 
   gNumElemMccFrResourceMap = 0;
   gNumFreeTsMccFrResourceMap = 0;
   
   dbStatus = getActiveIccSlotId(&chasisFrameId, &slotId);
   if(CLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_MAJOR,"No Active card is there. So Mcc Resource cannot be Fethched");
   }
 
   /* Get All MCC FR timeslots from DB */
   dbStatus = getMccLinkRowsOfLinkType(mccLinkType, slotId, &mccLinkResourceTableAllPtr, &rowCount, &outSize);

   if(dbStatus != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR, "DB call getMccResourceForLinkType failed: errCode: %d", dbStatus);
      return;
   }

   gNumElemMccFrResourceMap = rowCount;  /* number of rows returned from DB */
   gNumFreeTsMccFrResourceMap = gNumElemMccFrResourceMap; /* initially all the resources will be free */ 
   
   LOG_PRINT(LOG_INFO, "No of Fr Mcc Resources found in MccLinkResource Table = [%u], dbStatus = [%d]" , gNumElemMccFrResourceMap, dbStatus);
   
   for ( i = 0; i < rowCount; i++)
   {
      mccLinkResourceTablePtr = (MccLinkResourceTableApi *) (((I_U8 *)mccLinkResourceTableAllPtr + (outSize * i)));
      
      /*Mark all the Fr timeslots in Mcc Link Resource Table as FREE */
      dbStatus = updateMccLinkStatus(mccLinkResourceTablePtr->mccTrunkNum, mccLinkResourceTablePtr->mccTrunkTs, slotId, SYS_TS_FREE);
      
      if(dbStatus != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR, "DB call updateMccLinkStatus failed: errCode: %d", dbStatus);
         return;
      }
      
      gMccFrResourceMap[i].isValid = TRUE;
      gMccFrResourceMap[i].mccE1   = mccLinkResourceTablePtr->mccTrunkNum;
      gMccFrResourceMap[i].mccE1Ts = mccLinkResourceTablePtr->mccTrunkTs;
      gMccFrResourceMap[i].cardNum = mccLinkResourceTablePtr->cardNum;

      e1StreamMapTableIndicesBuff.e1Num = mccLinkResourceTablePtr->mccTrunkNum;
      e1StreamMapTableIndicesBuff.e1Ts  = mccLinkResourceTablePtr->mccTrunkTs;

      dbStatus = getE1StreamMapTable(&e1StreamMapTableIndicesBuff, &e1StreamMapTableApiPtr);
      
      if (CLIB_SUCCESS != dbStatus) 
      {
         LOG_PRINT(LOG_MAJOR, "Could not find mcccE1Id[%u] and mccE1Ts[%u]] from E1StreamMap Table, Error Code = [%d]",
                   e1StreamMapTableIndicesBuff.e1Num, e1StreamMapTableIndicesBuff.e1Ts, dbStatus);
         free(mccLinkResourceTableAllPtr);
         return;
      }
     
      gMccFrResourceMap[i].mccStrmId = e1StreamMapTableApiPtr->strmNum;
      gMccFrResourceMap[i].mccStrmTs = e1StreamMapTableApiPtr->strmTs;


      free(e1StreamMapTableApiPtr);
   }

   free(mccLinkResourceTableAllPtr);
   
   /* Sort the gMccFrResourceMap based on mccStrmTs */
   sortMccFrResourceMap();
   
   LOG_PRINT(LOG_INFO, "Exiting initMccFrResourceMap");
   
}

/********************************* Function  Header********************************
Function Name:       getNumAvailableMccFrTs()
Parameters:          I_Void
Return type:         I_U8
Purpose:             returns number of Free Fr Mcc Resources (Valid only in case of Fr; 
                     In case of IP, this is not valid) 
Other Note:
 ************************************************************************************/
I_U8 getNumAvailableMccFrTs(I_Void)
{
   LOG_PRINT(LOG_INFO, "gNumFreeTsMccFrResourceMap = [%u]", gNumFreeTsMccFrResourceMap);
   return gNumFreeTsMccFrResourceMap;
}

/********************************* Function  Header********************************
Function Name:       getNumElemMccFrResource()
Parameters:          I_Void
Return type:         I_U8
Purpose:             returns number of Fr Mcc Resources  
Other Note:
 ************************************************************************************/
I_U8 getNumElemMccFrResource(I_Void)
{
   LOG_PRINT(LOG_INFO, "gNumElemMccFrResourceMap = [%u]", gNumElemMccFrResourceMap);
   return gNumElemMccFrResourceMap;
}

/********************************* Function  Header***********************************
Function Name:       sortMccFrResourceMap()
Parameters:          I_Void
Return type:         I_Void
Purpose:             sorts the gMccFrResourceMap on the basis of Mcc E1Id and Mcc E1Ts
Other Note:
 ************************************************************************************/
I_Void sortMccFrResourceMap(I_Void)
{
   I_U32 i   = 0;
   I_U32 j   = 0;
   
   LOG_PRINT(LOG_INFO, "Entering sortMccFrResourceMap");
   for (i = 0; i < gNumElemMccFrResourceMap; i++)
   {
      for( j = i + 1; j < gNumElemMccFrResourceMap; j++)
      {
         /* if mccE1 at j index is less than mccE1 at i index 
          * then swap these values
          */
         if (gMccFrResourceMap[j].mccStrmTs < gMccFrResourceMap[i].mccStrmTs)
         {
            swapgMccFrResourceMapElems(i,j);
         }
      }/* End of inner for */
   } /* End of outer for */
   LOG_PRINT(LOG_INFO, "Exiting sortMccFrResourceMap");
}

/********************************* Function  Header***********************************
Function Name:       swapgMccFrResourceMapElems()
Parameters:          indices i and j elements at which are to be swapped 
Return type:         I_Void
Purpose:             This function swaps the elements at indices i and j in   
                     gMccFrResourceMap
Other Note:
 ************************************************************************************/
I_Void swapgMccFrResourceMapElems(int i, int j)
{
   MccFrResource temp;
   memcpy(&temp, &gMccFrResourceMap[i], sizeof(MccFrResource));
   memcpy(&gMccFrResourceMap[i], &gMccFrResourceMap[j], sizeof(MccFrResource));
   memcpy(&gMccFrResourceMap[j], &temp, sizeof(MccFrResource));
}
/********************************* Function  Header***********************************
Function Name:       areContiguousNumMccFrTs()
Parameters:          I_U8 numTs: Number of requested contiguous Fr Mcc timeslots
Return type:         I_S8:   index of gMccFrResourceMap from where numTs contiguously 
                             available
                             -1 if numTs 
Purpose:             This function searches contiguous Fr Mcc timeslots in 
                     gMccFrResourceMap
Other Note:
 ************************************************************************************/
I_S8 areContiguousNumMccFrTs(I_U8 numTs)
{
   I_U8  tempNumTs = numTs;
   I_U8 i          = 0;
   I_S8 startIdx   = 0;
   
   LOG_PRINT(LOG_INFO, "Entering areContiguousNumMccFrTs, numTs = [%u]", numTs);
   
   for (i = 0; i < gNumElemMccFrResourceMap; i++)
   {
      if (TRUE == gMccFrResourceMap[i].isAllocated)
      {
         tempNumTs = numTs;
         startIdx  = i + 1;
      }
      else
      {
         tempNumTs--;
         if (ZERO == tempNumTs)
         {
             LOG_PRINT(LOG_INFO, "Contiguous [%u] timeslots found from index [%d] in gMccFrResourceMap", numTs, startIdx);
             LOG_PRINT(LOG_INFO, "Exiting areContiguousNumMccFrTs");
             return startIdx;
         }
      }
   }
   LOG_PRINT(LOG_INFO, "Contiguous [%u] timeslots not found", numTs);
   LOG_PRINT(LOG_INFO, "Exiting areContiguousNumMccFrTs");
   return -1;
}

/********************************* Function  Header***********************************
Function Name:       allocateContiguousNumMccFrTs()
Parameters:          I_U16 frChnId: Fr Channel Identifier
                     I_U16 e1Id: Fr E1 Id
                     I_U8 startTs: start E1 Timeslot for Fr Channel
                     I_U8 numTs: Number of E1 timeslot for Fr Channel
Return type:         I_Bool: TRUE if numTs contiguously available
                             FALSE otherwise
Purpose:             This function does the following
                     1. searches contiguous Fr Mcc timeslots in gMccFrResourceMap 
                     2. and if found it allocates them to Fr in MccLinkResource Table by 
                        setting mccLinkStatus to SYS_TS_ALLOCATED
                     3. updates gMccFrResourceMap 
                     4. insert rows in FrLinkExtE1TsMccE1TsMapTable for each Fr timeslots
                     5. sends SwitchDisconnect to GRHM
Other Note:
 ************************************************************************************/
I_Bool allocateContiguousNumMccFrTs(I_U16  frChnId, I_U16 e1Id, I_U8 startTs, I_U8 numTs)
{
   I_U32  i             = 0;
   I_S32  startIdx      = 0;
   I_S32  dbStatus      = CLIB_SUCCESS;
   I_U8   tempStartTs   = startTs;
   I_U8   chasisFrameId = 0xFF;
   I_U8   slotId        = 0xFF;
 
   FrLinkExtE1TsMccE1TsMapTableApi frLinkExtE1TsMccE1TsMapBuff;
   
   LOG_PRINT(LOG_INFO, "Entering allocateContiguousNumMccFrTs");
   LOG_PRINT(LOG_INFO, " frChnId = [%u], e1Id = [%u], startTs = [%u], numTs = [%u]", 
             frChnId, e1Id, startTs, numTs); 
   LOG_PRINT(LOG_INFO, "Before allocation gNumFreeTsMccFrResourceMap  = [%u]", gNumFreeTsMccFrResourceMap);
  
   startIdx =  areContiguousNumMccFrTs(numTs); 

   if (0 <= startIdx)
   {
       dbStatus = getActiveIccSlotId(&chasisFrameId, &slotId);
      
       if(CLIB_SUCCESS != dbStatus)
       {
          LOG_PRINT(LOG_MAJOR,"No Active card is there. So Mcc Resource cannot be updated");
       }

       for (i = startIdx; i < (startIdx + numTs); i++)
       {

         LOG_PRINT(LOG_INFO, "Updating MccLinkResourceTable marking mccE1 = [%u], mccE1Ts = [%u] as allocated", 
                   gMccFrResourceMap[i].mccE1, gMccFrResourceMap[i].mccE1Ts);
                   
         /* update updateMccLinkResourceTable mark mccLink as allocated */
         dbStatus = updateMccLinkStatus (gMccFrResourceMap[i].mccE1, gMccFrResourceMap[i].mccE1Ts, slotId, SYS_TS_ALLOCATED);
         
         if (CLIB_SUCCESS != dbStatus)
         {
            LOG_PRINT (LOG_MAJOR,"DB call updateMccLinkStatus failed, Error Code = [%d]", dbStatus);
            return I_FALSE;
         }

         gMccFrResourceMap[i].isAllocated = TRUE;
         gMccFrResourceMap[i].frChnId = frChnId;
         gMccFrResourceMap[i].frE1 = e1Id;
         gMccFrResourceMap[i].frE1Ts = tempStartTs;

         frLinkExtE1TsMccE1TsMapBuff.frChnId = frChnId;
         frLinkExtE1TsMccE1TsMapBuff.e1Id = e1Id;
         frLinkExtE1TsMccE1TsMapBuff.e1Ts = tempStartTs;
           
         frLinkExtE1TsMccE1TsMapBuff.mccE1Id = gMccFrResourceMap[i].mccE1;
         frLinkExtE1TsMccE1TsMapBuff.mccE1Ts = gMccFrResourceMap[i].mccE1Ts;
         
         frLinkExtE1TsMccE1TsMapBuff.mccStrmTs = gMccFrResourceMap[i].mccStrmTs;
         
         LOG_PRINT(LOG_INFO, "Inserting into FrLinkExtE1TsMccE1TsMapTable frChnId = [%u], e1Id = [%u], e1Ts = [%u], mccE1Id = [%u], mccE1Ts = [%u] as allocated", 
                   frChnId, e1Id, tempStartTs, gMccFrResourceMap[i].mccE1, gMccFrResourceMap[i].mccE1Ts);
        
         dbStatus = insertFrLinkExtE1TsMccE1TsMapTable(&frLinkExtE1TsMccE1TsMapBuff);
         if (CLIB_SUCCESS != dbStatus)
         {
            LOG_PRINT (LOG_MAJOR,"DB call insertFrLinkExtE1TsMccE1TsMapTable failed, Error Code = [%d]", dbStatus);
            return I_FALSE;
         }

          /* send switch connect to GRHM */ 
          LOG_PRINT(LOG_INFO, "Sending  SwitchConnect to GRHM");
          sendSwitchConnect2Grhm(e1Id, tempStartTs, gMccFrResourceMap[i].mccE1, gMccFrResourceMap[i].mccE1Ts);
         
          tempStartTs++;
      }/*End of for*/
      gNumFreeTsMccFrResourceMap -= numTs;
   }
   else
   {
      return I_FALSE;
   }
   LOG_PRINT(LOG_INFO, "After allocation gNumFreeTsMccFrResourceMap = [%u]", gNumFreeTsMccFrResourceMap);
   LOG_PRINT(LOG_INFO, "Exiting allocateContiguousNumMccFrTs");
   return I_TRUE;
}

/********************************* Function  Header***********************************
Function Name:       deallocateContiguousNumMccFrTs()
Parameters:          I_U16 frChnId: Fr Channel Identifier
Return type:         I_Void
Purpose:             This function does the following
                     1. fetches all the rows from FrLinkExtE1TsMccE1TsMap Table
                     2. for each row which which has the same frChnId and It sends 
                        switchDisconnect to GRHM.
                     3. deallocate MccLinkResource Table by setting mccLinkStatus 
                        to SYS_TS_FREE
                     4. updates gMccFrResourceMap 
                     5. delete rows from FrLinkExtE1TsMccE1TsMapTable for each Fr timeslots
Other Note:
 ************************************************************************************/
 
I_Void deallocateContiguousNumMccFrTs(I_U16 frChnId)
{
   
   FrLinkExtE1TsMccE1TsMapTableIndices frLinkExtE1TsMccE1TsMapTableIndicesBuff;
   I_U32 i         = 0;
   I_S32 dbStatus  = CLIB_SUCCESS;
   I_U8   chasisFrameId = 0xFF;
   I_U8   slotId        = 0xFF;
 
   LOG_PRINT(LOG_INFO, "Entering deallocateContiguousNumMccFrTs, frChnId = [%u]", frChnId);
 
   dbStatus = getActiveIccSlotId(&chasisFrameId, &slotId);
   if(CLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_MAJOR,"No Active card is there. So Mcc Resource cannot be updated");
   }
 
   for(i = 0; i < gNumElemMccFrResourceMap; i++)
   {
      
      if (TRUE == gMccFrResourceMap[i].isAllocated && frChnId == gMccFrResourceMap[i].frChnId)
      {
         /* send switch disconnect to GRHM */ 
         
         LOG_PRINT(LOG_INFO, "Sending  SwitchDisconnect to GRHM");
         sendSwitchDisconnect2Grhm(gMccFrResourceMap[i].frE1, gMccFrResourceMap[i].frE1Ts, 
                                   gMccFrResourceMap[i].mccE1, gMccFrResourceMap[i].mccE1Ts);
         
          LOG_PRINT(LOG_INFO, "frChnId = [%u], e1Id = [%u], e1Ts = [%u], mccE1Id = [%u], mccE1Ts = [%u] to be deallocated", 
                    frChnId, gMccFrResourceMap[i].frE1, gMccFrResourceMap[i].frE1Ts, 
                    gMccFrResourceMap[i].mccE1, gMccFrResourceMap[i].mccE1Ts);
                
         /* deallocate the timeslots from MccLinkResource table */
         
         LOG_PRINT(LOG_INFO, "Updating MccLinkResourceTable marking mccE1 = [%u], mccE1Ts = [%u] as deallocated", 
                   gMccFrResourceMap[i].mccE1, gMccFrResourceMap[i].mccE1Ts);

         dbStatus = updateMccLinkStatus(gMccFrResourceMap[i].mccE1, gMccFrResourceMap[i].mccE1Ts, slotId, SYS_TS_FREE);   

         if (CLIB_SUCCESS != dbStatus)
         {
            LOG_PRINT(LOG_MAJOR,"Db Call updateMccLinkStatus() failed , Error Code = [%d] ", dbStatus);
            return;
         }
      
         /*Delete from FrLinkExtE1TsMccE1TsMap table*/
         frLinkExtE1TsMccE1TsMapTableIndicesBuff.frChnId = gMccFrResourceMap[i].frChnId;
         frLinkExtE1TsMccE1TsMapTableIndicesBuff.e1Id = gMccFrResourceMap[i].frE1;
         frLinkExtE1TsMccE1TsMapTableIndicesBuff.e1Ts = gMccFrResourceMap[i].frE1Ts;
         LOG_PRINT(LOG_INFO, "deleting row for frChnId[%u], e1Id = [%u], timeslot [%u] from FrLinkExtE1TsMccE1TsMap table",
                   gMccFrResourceMap[i].frChnId, gMccFrResourceMap[i].frE1, gMccFrResourceMap[i].frE1Ts);
         LOG_PRINT(LOG_INFO, "deleting row from FrLinkExtE1TsMccE1TsMapTable");
         dbStatus = deleteFrLinkExtE1TsMccE1TsMapTable(&frLinkExtE1TsMccE1TsMapTableIndicesBuff);
         if (CLIB_SUCCESS != dbStatus)
         {
            LOG_PRINT(LOG_MAJOR,"Db Call deleteFrLinkExtE1TsMccE1TsMapTable() failed , Error Code = [%d] ", dbStatus);
            return;
         }

         /* update gMccFrResourceMap */
         gMccFrResourceMap[i].isAllocated = FALSE;
         gMccFrResourceMap[i].frChnId = ZERO;
         gMccFrResourceMap[i].frE1 = CFG_INVALID_E1;
         gMccFrResourceMap[i].frE1Ts = CFG_INVALID_E1_TS;
         gNumFreeTsMccFrResourceMap++;     
      }/*end of if (TRUE == gMccFrResourceMap[i].isAllocated && frChnId == gMccFrResourceMap[i].frChnId)*/
   }/*End of for*/
   LOG_PRINT(LOG_INFO, "After deallocation gNumFreeTsMccFrResourceMap = [%u]", gNumFreeTsMccFrResourceMap);
   LOG_PRINT(LOG_INFO, "Exiting deallocateContiguousNumMccFrTs");
}

