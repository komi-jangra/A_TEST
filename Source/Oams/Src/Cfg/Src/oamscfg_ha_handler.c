/***********************************File Header ***************************
File Name        : oamscfg_ha_handler.c
Purpose          : This file contains functions that fill global data 
                   after swtichover
Project          : R2.9 BSC
Subsystem        : Oams
Author           : Rishabh Garg
CSCI ID          :
Version          :
 ************************************* End **********************************/
#include <oamscfg_includes.h>

/********************************* Function  Header********************************
Function Name:       fillTrxGlobalData()
Parameters:          void
Return type:         void
Purpose:             To fill global TRxh Data 
Other Note:
 ************************************************************************************/
I_Void fillTrxGlobalData()
{
    TrxTableApi* trxTableApiPtr = NULL;
    I_U32 outRow = ZERO;
    I_U16 outSz = ZERO;
    I_S32 dbStatus = -1;
    I_U32 index = ZERO;
    I_PVoid origPtr = NULL;

    dbStatus = getallTrxTable(&trxTableApiPtr, &outRow, &outSz);

    if(DBLIB_SUCCESS != dbStatus)
    {
        LOG_PRINT(LOG_INFO,"fillTrxGlobalData: No TRX Configured");
    }
    else
    {
        origPtr = (I_PVoid)trxTableApiPtr;
        for(index = 0; index < outRow; index++)
        {
            trxTableApiPtr = (TrxTableApi *)(((I_U8 *)(origPtr)) + (index * outSz));
            /* Initialize Trx Data Structure */
            gPtrxData[trxTableApiPtr->ptrxId].PTRXID = trxTableApiPtr->ptrxId;
            if(trxTableApiPtr->adminState == ZERO)
	          {
                gPtrxData[trxTableApiPtr->ptrxId].ptrxState = locked;   
	          }
            else
	          {
                gPtrxData[trxTableApiPtr->ptrxId].ptrxState = unlocked;
	          }
        }
    }
}

/********************************* Function  Header********************************
Function Name:       fillBichGlobalData()
Parameters:          void
Return type:         void
Purpose:             To fill global BICH Data 
Other Note:
 ************************************************************************************/
I_Void fillBichGlobalData()
{
    I_S32 dbStatus = -1;
    I_U32 index;
    BicTableApi *bicTableApiPtr = NULL;
    BicTableApi *tempBicTableApiPtr = NULL;
    I_U32 noOfBicCount = ZERO;
    I_U16 outSize = 0;
    

    dbStatus = getallBicTable(&bicTableApiPtr,&noOfBicCount,&outSize);
    if(DBLIB_SUCCESS != dbStatus)
    {
        LOG_PRINT(LOG_MAJOR,"fillBichGlobalData : Get From BicTable Failed");
    }
    for ( index = 0; index < CFG_MAX_NUM_BTS; index++ )
    {
        if ( noOfBicCount )
        {
            tempBicTableApiPtr =(BicTableApi*)((I_U8*)bicTableApiPtr+(index*outSize));             
            if ( tempBicTableApiPtr->adminState == LOCKED )
                gBtsData[index].btsState = locked;
            else if ( tempBicTableApiPtr->adminState == UNLOCKED )
            {
                gBtsData[index].btsState = unlocked;
            }
            gBtsData[index].BTSID = tempBicTableApiPtr->bicId;
            gBtsData[index].btsType = tempBicTableApiPtr->btsType;
            gBtsData[index].connectivityState = tempBicTableApiPtr->btsConnectivityState;
            noOfBicCount--;
        }
        else
        {
            gBtsData[index].BTSID = INVALID_BTS;
            gBtsData[index].btsType = 0;
            gBtsData[index].connectivityState = none;
            gBtsData[index].btsState = none;
        }
   }
   if(bicTableApiPtr  != NULL)
      free(bicTableApiPtr);
}
/********************************* Function  Header********************************
Function Name:       fillCellData()
Parameters:          void
Return type:         void
Purpose:             To fill global Cell Data 
Other Note:
 ************************************************************************************/
I_Void fillCellData()
{
   LOG_PRINT(LOG_INFO,"Entering fillCellData()");
   I_U32 index,i;
   CellPerTableApi *CellTableApiPtr=NULL;
   CellPerTableApi *tempCellTableApiPtr=NULL;
   I_U32 noOfCellCount=0;
   I_U16  outSize=0;
   CellNonPerTableIndices cellNonPerTableInd;
   CellNonPerTableApi *cellNonPerTableApiPtr = NULL;
   
   memset (&gCellData[0],0,sizeof( CellDataStruct ) *CFG_MAX_NUM_CELLS);
   
   for ( index = 0; index < CFG_MAX_NUM_CELLS;index++ )
   {
         gCellData[index].Availlability = TRUE;
         gCellData[index].CellState = locked;
         gCellData[index].lac = 0;
         gCellData[index].CellID = 0;
         gCellData[index].reqType = 0;
         gCellData[index].adminState = LOCKED;
         gCellData[index].opState = DISABLED;
   }
   if(getallCellPerTable(&CellTableApiPtr,&noOfCellCount,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"fillCellData : No Cells in DB");
   }
   else
   {
      for(i=0; i<noOfCellCount; i++ )
      {
         tempCellTableApiPtr =(CellPerTableApi*)((I_U8*)CellTableApiPtr+(i*outSize));
         cellNonPerTableInd.lac = tempCellTableApiPtr->lac;
         cellNonPerTableInd.cellId = tempCellTableApiPtr->cellId;
         getCellNonPerTable(&cellNonPerTableInd,&cellNonPerTableApiPtr);
         index = cellNonPerTableApiPtr->cellIndex;
         gCellData[index].Availlability = FALSE;
         gCellData[index].reqType = 0;         
         if ( tempCellTableApiPtr->adminState == LOCKED )
         {  
            gCellData[index].CellState = locked;
         } 
         else if ( tempCellTableApiPtr->adminState == UNLOCKED )
         {
             if(gDbBssTableApiStorage.adminState == LOCKED)
             {
                gCellData[index].CellState = unlockedDisabled;
                gCellData[index].reqType = OAMS_RSN_PARENTOBJECTLOCKED;
             }
             else
             {
                gCellData[index].CellState = unlockedEnabled;
             }
         }
         gCellData[index].CellID = tempCellTableApiPtr->cellId;
         gCellData[index].adminState = tempCellTableApiPtr->adminState;
         gCellData[index].lac = tempCellTableApiPtr->lac;
         gCellData[index].isReqSentForPS = FALSE;
         
      }
   }
   if(CellTableApiPtr  != NULL)
      free(CellTableApiPtr);

   LOG_PRINT(LOG_INFO,"Exiting fillCellData()");
}

/********************************* Function  Header********************************
Function Name:       fillE1TimeSlotData()
Parameters:          void
Return type:         void
Purpose:             To fill global E1 Time Slot Data 
Other Note:
 ************************************************************************************/
I_Void fillE1TimeSlotData()
{
    AbisTimeSlotPerTableApi *pTimeSlotTableApi = NULL;
    AbisTimeSlotPerTableApi *pTempTimeSlotApi = NULL;
    I_U16  rowSize = 0;
    I_U32  noOfRows = 0;
    I_U32  index;
    LinkTableApi *linkTablePtr = NULL;
    LinkTableApi *tempLinkPtr = NULL;
    CicTableApi *cicTablePtr = NULL;
    CicTableApi *tempCicPtr = NULL;

    if (getallAbisTimeSlotPerTable(&pTimeSlotTableApi,&noOfRows,&rowSize) == CLIB_SUCCESS)
    {
        LOG_PRINT(LOG_INFO,"fillE1TimeSlotData : TimeSlot DB SUCCESS");
        for ( index = 0; index < noOfRows; index++ )
        {
            pTempTimeSlotApi =(AbisTimeSlotPerTableApi*)((I_U8*)pTimeSlotTableApi + (index *rowSize));
            gE1TimeslotData[pTempTimeSlotApi->e1Num][pTempTimeSlotApi->tsNum].e1Number=pTempTimeSlotApi->e1Num;
            gE1TimeslotData[pTempTimeSlotApi->e1Num][pTempTimeSlotApi->tsNum].e1TimeslotID=pTempTimeSlotApi->tsNum;
            if(pTempTimeSlotApi->adminState == 0)
                gE1TimeslotData[pTempTimeSlotApi->e1Num][pTempTimeSlotApi->tsNum].e1TimeslotState = locked;
            else
                gE1TimeslotData[pTempTimeSlotApi->e1Num][pTempTimeSlotApi->tsNum].e1TimeslotState = unlocked;
        }
        free(pTimeSlotTableApi);
    }
    else
      LOG_PRINT(LOG_INFO,"fillE1TimeSlotData :  No rows in TimeSlot table ");
    
    /* fill the E1 timeslot data */
    if (getallLinkTable(&linkTablePtr, &noOfRows, &rowSize) == CLIB_SUCCESS)
    {
        for (index = 0; index <noOfRows; index++)
        {
            tempLinkPtr = (LinkTableApi *)((I_U8*)linkTablePtr + (index *rowSize));
            gE1TimeslotData[tempLinkPtr->e1Num][tempLinkPtr->timeSlot].e1Number=tempLinkPtr->timeSlot;
            gE1TimeslotData[tempLinkPtr->e1Num][tempLinkPtr->timeSlot].e1TimeslotID=tempLinkPtr->timeSlot;
            if(tempLinkPtr->adminState == LOCKED)
                gE1TimeslotData[tempLinkPtr->e1Num][tempLinkPtr->timeSlot].e1TimeslotState = locked;
            else
	              gE1TimeslotData[tempLinkPtr->e1Num][tempLinkPtr->timeSlot].e1TimeslotState = unlocked;
        }
        free(linkTablePtr); 
    }
    else
        LOG_PRINT(LOG_INFO,"fillE1TimeSlotData :  No rows in Link table ");
   
    if (getallCicTable(&cicTablePtr, &noOfRows, &rowSize) == CLIB_SUCCESS)
    {
        for (index = 0; index <noOfRows; index++)
        {
            tempCicPtr = (CicTableApi *)((I_U8*)cicTablePtr + (index *rowSize));
            gE1TimeslotData[tempCicPtr->e1Num][tempCicPtr->timeSlot].e1Number=tempCicPtr->timeSlot;
            gE1TimeslotData[tempCicPtr->e1Num][tempCicPtr->timeSlot].e1TimeslotID=tempCicPtr->timeSlot;
            if(tempCicPtr->adminState == LOCKED)
                gE1TimeslotData[tempCicPtr->e1Num][tempCicPtr->timeSlot].e1TimeslotState = locked;
            else
                gE1TimeslotData[tempCicPtr->e1Num][tempCicPtr->timeSlot].e1TimeslotState = unlocked;
        }
        free(cicTablePtr); 
   }
   else
       LOG_PRINT(LOG_INFO,"fillE1TimeSlotData :  No rows in Cic table ");
}

/********************************* Function  Header********************************
Function Name:       fillE1Data()
Parameters:          void
Return type:         void
Purpose:             To fill global E1 Data 
Other Note:
 ************************************************************************************/
I_Void fillE1Data()
{
    TrunkTableApi *pE1TableApi=NULL;
    TrunkTableApi *t=NULL;
    I_U32 noOfE1Count;
    I_U16 E1OutSize=0;
    I_U32 index;
    I_U32 trunkSt = 0;
    
    if (getallTrunkTable(&pE1TableApi,&noOfE1Count,&E1OutSize) == CLIB_SUCCESS)
    {
        LOG_PRINT(LOG_INFO,"fillE1Data : E1 DB SUCCESS");
        for ( index = 0; index < noOfE1Count;index++ )
        {
            t =(TrunkTableApi*)((I_U8*)pE1TableApi + (index *E1OutSize));
             gE1Data[t->e1Num].e1Number=t->e1Num;
             if(t->adminState == 0)
             {
                 gE1Data[t->e1Num].e1State=locked;
             }
             else
             {
                 gE1Data[t->e1Num].e1State=unlocked;
             }
             gE1Data[t->e1Num].usageType=t->usageType;
             gE1Data[t->e1Num].waitingForCellUnlockRespCounter=0;
             gE1Data[t->e1Num].e1CellLockReqSent=0;
             gE1Data[t->e1Num].e1CellUnlockReqSent=0;
             gE1Data[t->e1Num].LOS_Active = FALSE;
             gE1Data[t->e1Num].LOS_Active_In_Progress = FALSE;
             gE1Data[t->e1Num].LOS_Active_Pending = FALSE;
             gE1Data[t->e1Num].LOS_Clear_In_Progress = FALSE;
             gE1Data[t->e1Num].LOS_Clear_Pending = FALSE;
             gE1Data[t->e1Num].LOS_Frame = FALSE;
             gE1Data[t->e1Num].LOS_Signal = FALSE;
             gE1Data[t->e1Num].LOS_Signal_detect = FALSE;

             if(t->e1Category == INTERNAL_E1)
             {
                LOG_PRINT(DEBUG,"Initiliazing trunkstate as Enabled for e1Num(%d)",t->e1Num); 
                gE1Data[t->e1Num].trunkState= Enabled;
             }
             else if(t->e1Category == EXTERNAL_E1)
             {
                if(getTrunkStateForE1(t->e1Num, &trunkSt) != CLIB_SUCCESS)
                {
                    LOG_PRINT(LOG_CRITICAL,"fillE1Data : Trunk State for E1 is not found."
                      " DB query failed. Making TrunkState disbaled. for e1Num(%d)",t->e1Num);
                    gE1Data[t->e1Num].trunkState= Disabled;
                }
                else
                {
                    if(trunkSt == ENABLED)
                    { 
                        gE1Data[t->e1Num].trunkState= Enabled;
                        LOG_PRINT(DEBUG,"Initiliazing trunkstate as Enabled for e1Num(%d)",t->e1Num); 
                    }
                    else
                    {
                        gE1Data[t->e1Num].trunkState= Disabled;
                        LOG_PRINT(DEBUG,"Initiliazing trunkstate as disabled for e1Num(%d)",t->e1Num); 
                    } 
                }
            }
            else
            {
                LOG_PRINT(LOG_CRITICAL," fillE1Data : Unknown E1 Ctaegory ");   
            }
        }
        free(pE1TableApi);
    }
    else
       LOG_PRINT(LOG_CRITICAL," fillE1Data : No rows in E1 table ");
}
/********************************* Function  Header********************************
Function Name:       fillDspData()
Parameters:          void
Return type:         void
Purpose:             To fill global E1 Data 
Other Note:
 ************************************************************************************/
I_Void fillDspData()
{
  LOG_PRINT(LOG_INFO,"Entering fillDspData()");
  I_U32 i;
  I_U16  rowSize=0;
  I_U32 noOfRows = 0;
  DspInfoTableApi *pDspInfoTbl=NULL;
  DspInfoTableApi *pTempDspInfoTbl=NULL; 

  if(getallDspInfoTable(&pDspInfoTbl, &noOfRows, &rowSize) == CLIB_SUCCESS)
  {
    for(i = 0; i< noOfRows; i++)
    {
      pTempDspInfoTbl = (DspInfoTableApi*)((I_U8*)pDspInfoTbl+(i*rowSize)); 
      gDspData[pTempDspInfoTbl->dspId].dspId = pTempDspInfoTbl->dspId;
      if (pTempDspInfoTbl->adminState == LOCKED)
      {
        gDspData[pTempDspInfoTbl->dspId].dspState = locked;
      }
      else
      {
        gDspData[pTempDspInfoTbl->dspId].dspState = unlocked;
      }
      LOG_PRINT(LOG_INFO,"fillDspData: DspId %d DspState %d",pTempDspInfoTbl->dspId,gDspData[pTempDspInfoTbl->dspId].dspState);
    }
  }

  if(pDspInfoTbl != NULL)
     free(pDspInfoTbl); 

  LOG_PRINT(LOG_INFO,"Exiting fillDspData()");
}

/********************************* Function  Header********************************
Function Name:       fillNsvcData()
Parameters:          void
Return type:         void
Purpose:             To fill global Nsvc Data 
Other Note:
 ************************************************************************************/
I_Void fillNsvcData()
{
   NsvcTableApi *pNsvcTab = NULL;
   NsvcTableApi *pTempNsvcTab = NULL;
   NsvcStatusTableApi  nsvcStatusTabStruct;
   I_U32 NsvcCount = 0;
   I_U16 NsvcOutSize = 0;
   I_U32 i;
   I_S32 retVal;

   retVal = getallNsvcTable(&pNsvcTab,&NsvcCount,&NsvcOutSize);
   if(CLIB_SUCCESS != retVal && 0 == NsvcCount)
   {
      //LOG_PRINT(LOG_INFO, "cfgObjectHandlerInit : No rows in Nsvc table, Error Code = [%d] ", retVal); Merger for Mantis #31470
      LOG_PRINT(LOG_INFO, "fillNsvcData : No rows in Nsvc table, Error Code = [%d] ", retVal);
   }

   for(i = 0; i < OAMS_CFG_MAX_NUM_NSVCS; i++)
   {
      if ( NsvcCount )
      {
         pTempNsvcTab =(NsvcTableApi*)((I_U8*)pNsvcTab+(i*NsvcOutSize));
         gNsvcData[i].availability = FALSE;
         if ( pTempNsvcTab->adminState == LOCKED )
            gNsvcData[i].nsvcState = locked;
         else if ( pTempNsvcTab->adminState == UNLOCKED )
         {
            gNsvcData[i].nsvcState = unlockedDisabled;
         }
         gNsvcData[i].nsvcId = pTempNsvcTab->nsvcId;
         NsvcCount--;

         /* Inserting Nsvc Status Table */
         nsvcStatusTabStruct.nsvcId = gNsvcData[i].nsvcId;
         nsvcStatusTabStruct.oprState = DISABLED;
         retVal = insertNsvcStatusTable(&nsvcStatusTabStruct);
         if (CLIB_SUCCESS != retVal)
         {
            /*LOG_PRINT(LOG_MAJOR,"Db Operation failed,NSVC ID[%u] could not be added into the DB Error code = [%d]", 
                      nsvcStatusTabStruct.nsvcId, retVal );*/ //Merger for Mantis #31470
            LOG_PRINT(LOG_MAJOR,"Db Operation failed,NSVC ID[%u] could not be "
                                "added into the DB Error code = [%d]", 
                                nsvcStatusTabStruct.nsvcId, retVal );
         }
      }
      else
      {
         gNsvcData[i].availability = TRUE;
         gNsvcData[i].nsvcState = locked;
         gNsvcData[i].nsvcId = 0;
      }
   }
}
I_Void  fillFrLinkStatusData()
{
   FrLinkTableApi *pFrLinkTabData = PNULL;
   FrLinkTableApi *pTempFrLinkTabData = PNULL;
   FrLinkStatusTableApi frLinkStatusTab;
   I_U32 outCount;
   I_U32 outSize;
   I_U32 count;
   I_S32  ret = CM_FAILURE;
  
   ret = getallFrLinkTable (&pFrLinkTabData, &outCount, &outSize);

   if(ret == CLIB_SUCCESS)
   {
     for (count=0; count< outCount; count++)
     {
       pTempFrLinkTabData = (FrLinkTableApi *)((I_U8 *)pFrLinkTabData + count*outSize);

       frLinkStatusTab.frChnId = pTempFrLinkTabData->frChnId;
       frLinkStatusTab.oprState = DISABLED;
       LOG_PRINT(LOG_DEBUG,"Inserting frLinkStatus table for chnId %d",
           frLinkStatusTab.frChnId);
       ret = insertFrLinkStatusTable(&frLinkStatusTab);
       if (CLIB_SUCCESS != ret)
       {
          LOG_PRINT(LOG_MAJOR,"Db Operation failed, Error Code = [%d] ", ret);
       }
     }
     free(pFrLinkTabData);
   }
}
/*Merger for Mantis #31470*/
I_Void fillNseiData()
{
   I_U32 outCount;
   I_U32 outSize;
   I_U32 count;
   I_S32  ret = CM_FAILURE;
   GbInterfaceTableApi* gbIfTblApiPtr = PNULL;

  LOG_PRINT(LOG_INFO,"Entering fillNseiData()");
   
   ret = getallGbInterfaceTable(&gbIfTblApiPtr, &outCount, &outSize);
   if (ret == DBLIBERR_PTOPAGE_HAS_NO_ROWS)
   {
      LOG_PRINT(LOG_MAJOR, "No rows present in gb Interface Table");
	  return;
   }
   gNseiData.nsei = gbIfTblApiPtr->nsei;
   if(gbIfTblApiPtr->adminState == UNLOCKED)
   {
	 gNseiData.nseiState=unlocked;
   }
   else
   {
	 gNseiData.nseiState=locked;
   }
   LOG_PRINT(LOG_INFO,"Exiting fillNseiData()");
}
/*Merger for Mantis #31470*/

/********************************* Function  Header********************************
Function Name:       fillGlobalDataAfterSwitchover()
Parameters:          void
Return type:         void
Purpose:             To fill global Data 
Other Note:
 ************************************************************************************/
I_Void fillGlobalDataAfterSwitchover()
{
  I_S32 oprStateAInterface;
  I_S32  ret = CM_FAILURE;
  GbInterfaceTableApi *pGbInterfaceTab = PNULL;
  I_U32 outCountGb;
  I_U32 outSizeGb;
  /* To fill gDbBssTalbeApiStorage*/
  getDbBssTable();
  if(gDbBssTableApiStorage.adminState == LOCKED)
  {
    gBssState = locked;
  }
  else
  {
    gBssState = unlocked;
  }
  ret = getallGbInterfaceTable(&pGbInterfaceTab,&outCountGb, &outSizeGb);
  if ( CLIB_SUCCESS == ret)
  {
    gGbTransportType = pGbInterfaceTab->transportType;
  }
  if(gGbTransportType != FR)
  {
    if(gDbBssTableApiStorage.gprsEnabled == ENABLED)
    {
       gGbUnlockReqSent = TRUE;
    }
  }
  fillTrxGlobalData();
  fillBichGlobalData();
  fillCellData();
  fillE1TimeSlotData();
  fillE1Data();
  fillDspData();
  /*Merger for Mantis #31470*/
  fillNseiData();
  /*Merger for Mantis #31470*/
  /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   initGlobalDsForAspStatusAtStartup();
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/


  if (getAInterfaceOprState(&oprStateAInterface) != CLIB_SUCCESS)
  {
     LOG_PRINT(LOG_CRITICAL,"getAInterfaceOprState Failed");
  }
  else if(oprStateAInterface == ENABLED)
  {
     gSSAReceived = TRUE;
  }
  gCfgState = CFG_READY;
   //Mantis 31749
  /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
   LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: fillGlobalDataAfterSwitchover : Before updating gCardPlatformType [%d]",gCardPlatformType);
   updateCardPlatformTypeInContext();
   LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: fillGlobalDataAfterSwitchover : After updating gCardPlatformType [%d]",gCardPlatformType);
  /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
   //Mantis 31749
}


I_U8 checkOamProcedure()
{
    LOG_PRINT(LOG_INFO,"Entering checkOamProcedure");
    AbisTimeSlotPerTableApi *pTimeSlotTableApi = NULL;
    AbisTimeSlotPerTableApi *pTempTimeSlotApi = NULL;
    I_U16  rowSize = 0;
    I_U32  noOfRows = 0;
    I_U32  index;
    LinkTableApi *linkTablePtr = NULL;
    LinkTableApi *tempLinkPtr = NULL;
    CicTableApi *cicTablePtr = NULL;
    CicTableApi *tempCicPtr = NULL;
    I_S32 dbStatus = -1;
    BicTableApi *bicTableApiPtr = NULL;
    BicTableApi *tempBicTableApiPtr = NULL;
    I_U32 noOfBicCount = ZERO;

    if(gBssState != locked && gBssState !=unlocked)
    {
      LOG_PRINT(DEBUG,"Bss Procedure in Progress");
      return I_FALSE;
    }
    
    for ( index = 0; index < CFG_MAX_NUM_CELLS;index++ )
    {
        if(gCellData[index].CellState != locked && gCellData[index].CellState != unlockedEnabled && gCellData[index].CellState !=unlockedDisabled)
        {
            LOG_PRINT(DEBUG,"Cell = %d lock/unlock/block Produre in Progress ",gCellData[index].CellID);
            return I_FALSE;
        }
    }
    dbStatus = getallBicTable(&bicTableApiPtr,&noOfBicCount,&rowSize);
    if(dbStatus == DBLIB_SUCCESS)
    {
        for ( index = 0; index < noOfBicCount; index++ )
        {
            if (gBtsData[index].btsState != unlocked && gBtsData[index].btsState != locked)
            {
                LOG_PRINT(DEBUG,"Bts = %d lock/unlock Produre in Progress ",gBtsData[index].BTSID);
                return I_FALSE;
            }
        }
    }
    for(index = 0 ; index < MAX_NUM_TRX_PER_BSS; index++)
    {
        if(gPtrxData[index].ptrxState != locked && gPtrxData[index].ptrxState != unlocked)
        {
             LOG_PRINT(DEBUG,"Trxid = %d lock/unlock/block Produre in Progress ",gPtrxData[index].PTRXID);
             return I_FALSE;
        }
    }
    for(index = 0 ; index < CFG_MAX_NUM_E1 ; index++)
    {
        if(gE1Data[index].e1State != locked && gE1Data[index].e1State !=unlocked)
        {
            LOG_PRINT(DEBUG,"E1 = %d lock/unlock Produre in Progress ",gE1Data[index].e1Number);
            return I_FALSE;
        }
        if(gE1Data[index].trunkState != Enabled && gE1Data[index].trunkState !=Disabled)
        {
            LOG_PRINT(DEBUG,"E1 = %d Activate/Deactivate Produre in Progress ",gE1Data[index].e1Number);
            return I_FALSE;
        }
    }

    if (getallLinkTable(&linkTablePtr, &noOfRows, &rowSize) == CLIB_SUCCESS)
    {
        for (index = 0; index <noOfRows; index++)
        {
            tempLinkPtr = (LinkTableApi *)((I_U8*)linkTablePtr + (index *rowSize));
            if (gE1TimeslotData[tempLinkPtr->e1Num][tempLinkPtr->timeSlot].e1TimeslotState != locked &&
                gE1TimeslotData[tempLinkPtr->e1Num][tempLinkPtr->timeSlot].e1TimeslotState != unlocked)
            {
                LOG_PRINT(DEBUG,"LinkId = %d lock/unlock Produre in Progress ",tempLinkPtr->linkId);
                if (linkTablePtr != NULL)
                  free(linkTablePtr);
                
                return I_FALSE;
            }
        }
    }
    if (getallCicTable(&cicTablePtr, &noOfRows, &rowSize) == CLIB_SUCCESS)
    {
        for (index = 0; index <noOfRows; index++)
        {
            tempCicPtr = (CicTableApi *)((I_U8*)cicTablePtr + (index *rowSize));
            if (gE1TimeslotData[tempCicPtr->e1Num][tempCicPtr->timeSlot].e1TimeslotState != locked &&
                gE1TimeslotData[tempCicPtr->e1Num][tempCicPtr->timeSlot].e1TimeslotState != unlocked)
            {
                LOG_PRINT(DEBUG,"cicId = %d lock/unlock Produre in Progress ",tempCicPtr->cicId);
                if (cicTablePtr != NULL)
                  free(cicTablePtr); 
                
                return I_FALSE;
            }
        }
   }
   else
       LOG_PRINT(LOG_INFO,"fillE1TimeSlotData :  No rows in Cic table ");
   for (index = 0; index < MAX_DSP; index++)
   {
     LOG_PRINT(DEBUG,"DspId = %d gDspData[%d].dspState = %d",index,index,gDspData[index].dspState);
     if(gDspData[index].dspState != locked && gDspData[index].dspState != unlocked)
     {
        LOG_PRINT(DEBUG,"DspId = %d lock/unlock/reset Produre in Progress ",index);
        return I_FALSE;
     }
   }
   LOG_PRINT(LOG_INFO,"Exiting checkOamProcedure");
   return I_TRUE;
}
  
I_Void gbOverFrSwitchoverHandling()
{
   I_U32 i;
   I_S32 ret;
   I_U32 noOfE1Count;
   I_U16 E1OutSize=0;
   I_U16  outSize=0;
   I_S32 retVal=0;
   I_U16 e1Id;
   TrunkTableIndices trunkTableInidcesBuff;
   TrunkTableApi *pTrunkTab;
   CellPerTableIndices cellPerTableIndices;
   CellPerTableApi *pCellTab;

   initMccFrResourceMap();

   for ( i = 0; i < OAMS_CFG_MAX_NUM_NSVCS;i++ )
   {
      if (FALSE == gNsvcData[i].availability && unlockedDisabled == gNsvcData[i].nsvcState)
      {
         ret = getE1IdForNsvcId(gNsvcData[i].nsvcId, &e1Id);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_INFO, "No E1 present for NsvcId %u, Error Code = [%d]",
                                 gNsvcData[i].nsvcId, ret);
            return;
         }
         trunkTableInidcesBuff.e1Num = e1Id;
         ret = getTrunkTable(&trunkTableInidcesBuff, &pTrunkTab);
         if(CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_INFO, "DB call getTrunkTable failed, returned Error "
                                "Code = [%d]",ret);
            return;
         }
         LOG_PRINT(LOG_INFO, "E1Id = %u for NsvcId %u", e1Id, gNsvcData[i].nsvcId);
         if(LOCKED != pTrunkTab->adminState) 
         {
            /*Send Unlock Request To Nsvc*/
            gNsvcData[i].nsvcState = unlockOrEnableInProgress;
            gNsvcData[i].reqType = OAMS_RSN_PARENTOBJECTLOCKED;
   
            LOG_PRINT(LOG_INFO, "calling nsvcUnlockReq()");
            nsvcUnlockReq(gNsvcData[i].nsvcId, OAMS_RSN_PARENTOBJECTLOCKED);
         }
      }
   }
   for ( i = 0; i < CFG_MAX_NUM_CELLS;i++ )
   {
      if ( (gCellData[i].Availlability == I_FALSE) && (gCellData[i].adminState == UNLOCKED) )
      {
         cellPerTableIndices.cellId = gCellData[i].CellID;
         cellPerTableIndices.lac = gCellData[i].lac;
         if(getCellPerTable(&cellPerTableIndices,&pCellTab) == CLIB_SUCCESS)
         {
            if ((PS_ALLOWED == pCellTab->psAllowed) && 
                (ENABLED == gDbBssTableApiStorage.gprsEnabled) )
            {
               sendPsCellUnlockReq(gCellData[i].CellID, pCellTab->lac,
                                   OAMS_RSN_PARENTOBJECTLOCKED, i);
               updateCellDataStruct(pCellTab->cellId, pCellTab->lac, 
                          unlockOrEnableInProgress, OAMS_RSN_PARENTOBJECTLOCKED);
               gCellEnableSent++;
            }
         }
      }
   }
}
