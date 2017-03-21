/***********************************File Header ***************************
   File Name        : oamcfg_initialization.c
Purpose          : This file contains functions definitions for CFG 
initialization methods.
Project          : BSC
Subsystem        : OAMS
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h>
static timer_t     tid;      /* Change For CS2.2 */
      /*BSC CS4.0 : Init changes start*/
#if BPM_PRESENT == 0
#define bpmRespondToAis(a,b) while(0){}   
#endif
#if 0
void sendFetchreqBcardInfo()
{
#if BPM_PRESENT == 1
   LOG_PRINT(LOG_INFO,"Entering function sendFetchreqBcardInfo");
   CardInfoTableApi cardinfotableapibuff;
   cfgSendMessage(&cardinfotableapibuff,sizeof(CardInfoTableApi),ENT_OAM_OIL,BSC_API_GET_CARDINFOTABLE, 0);
   LOG_PRINT(LOG_INFO,"BSC_API_GET_CARDINFOTABLE has been sent...");
   /*SPR - */
   /* Start timer ...*/
   /***************************************************************************/
   SysAddr slfAddr;
   TmrPayLoad tmrPayLoad;
   slfAddr.entity= ENT_OAMS_CFG;
   strcpy(tmrPayLoad.payLoad,"BPM_STARTUP");
   LOG_PRINT(LOG_INFO,"BPM STARTUP Timer Started...(60 secs)... Waiting for BSC_API_GET_CARDINFOTABLE");
   StartTimerFrmwrk(&slfAddr,BPM_STARTUP_TIMER,&tmrPayLoad,&bpmTimerId);
   /***************************************************************************/ 


#endif
}
#endif

I_Void sendBpmDbInitialized()
{
   OamsCfgOilBpmDbInit oamsCfgOilBpmDbInit;
   LOG_PRINT(LOG_INFO,"sendBpmDbInitialized: Entering in function");
   cfgSendMessage(&oamsCfgOilBpmDbInit, sizeof(OamsCfgOilBpmDbInit), ENT_OAM_OIL, OAMS_CFG_OIL_BPM_DB_INITIALIZED, 0);
   LOG_PRINT(LOG_INFO,"sendBpmDbInitialized: Exiting from function");
}
      /*BSC CS4.0 : Init changes ends*/

void startInitializeMGS()
{

   MgsuSmmSmmInitTrigger   MgsuSmmSmmInitTriggerBuff={0};
   MgsuSmmSmmInitTriggerBuff.messageId = MGS_SMM_INIT_TRIGGER;
   MgsuSmmSmmInitTriggerBuff.hdr.DestId = MGS_DEST_SMM;
   MgsuSmmSmmInitTriggerBuff.hdr.TotalLength = 2;
   MgsuSmmSmmInitTriggerBuff.initReason = 0; /* currently keep it as 0-startup 
                                                                      later need to be modified to appropriate enums*/
   /* Protect by Gaurd Timer */
   gMgsWaitForRspFlg= MGS_NO_WAIT;
   gMgsSmmTsiRspFlag=TRUE; /* wait for two messages then only stop the timer */
   gMgsSmmDspBootFlag = TRUE;
   gMgsOprSts = TRUE;
   /*BSC CS4.0: HA CHanges Starts*/
//   startMgsTimer(); /* Change For CS2.2 */
   cfgStartTimer("TSI_TRAU_INIT");
   /*BSC CS4.0: HA CHanges Ends*/
   cfgSendMessage(&MgsuSmmSmmInitTriggerBuff, sizeof(MgsuSmmSmmInitTrigger), ENT_IPC_TSMIF, EXT_TSM_MSG,0);
   LOG_PRINT(LOG_INFO,"MGS_SMM_INIT_TRIGGER has been sent...");

}

#if 0 /* CS4.0 HA Stack Changes */
void cfgPopulateLinkAdminStateTable()
{
   AbisTimeSlotPerTableApi *timeSlotObjPtr=NULL;
   AbisTimeSlotPerTableApi *t=NULL;   
   LinkAdminStateTableIndices LinkAdminStateTableIndicesBuff;
   LinkAdminStateTableApi *LinkAdminStateTableApiPtr=NULL;

   I_U32 count=0;
   I_U16 outSize = 0;
   I_U32 i=0;
   LOG_PRINT(LOG_INFO,"Entering cfgPopulateLinkAdminStateTable");

   if (getallAbisTimeSlotPerTable(&timeSlotObjPtr,&count,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "INITcfgPopulateLinkAdminStateTable : readTimeSlotPer Table() Failed");
      return;
   }



   for (i = 0; i < count; i++)
   {
      t = (AbisTimeSlotPerTableApi*)((char*)timeSlotObjPtr + (i *outSize));
      if(t->usageType == SYS_TS_USAGE_MTP2) 
      {
         /* LinkAdminStateTableIndicesBuff.linkAdminlinkCode= M_GET_LINKCODE(t->usingEntity);
         LinkAdminStateTableIndicesBuff.linkAdminlinksetID= M_GET_LINKSET(t->usingEntity); */
         if ( getLinkAdminStateTable(&LinkAdminStateTableIndicesBuff, &LinkAdminStateTableApiPtr) == CLIB_SUCCESS)
         {
            LinkAdminStateTableApiPtr->linkAdminadminState = timeSlotObjPtr->adminState;
            if ( updateLinkAdminStateTable(LinkAdminStateTableApiPtr) != CLIB_SUCCESS )
            {
               LOG_PRINT(LOG_CRITICAL, "INIT :updateLinkAdminStateTable() Failed");
            }
            else
            {
               LOG_PRINT(LOG_INFO, "INIT :updateLinkAdminStateTable() Success");
            } 
         }
         else
         {
            /* Insert , Default AdminState as per the TimeSlot Adminstate  */
            LinkAdminStateTableApi LinkAdminStateTableApiBuff;
            LinkAdminStateTableApiBuff.linkAdminadminState = timeSlotObjPtr->adminState ;
            LinkAdminStateTableApiBuff.linkAdminlinkCode = LinkAdminStateTableIndicesBuff.linkAdminlinkCode;
            LinkAdminStateTableApiBuff.linkAdminlinksetID = LinkAdminStateTableIndicesBuff.linkAdminlinksetID;

            if ( insertLinkAdminStateTable(&LinkAdminStateTableApiBuff) != CLIB_SUCCESS )
            {
               LOG_PRINT(LOG_CRITICAL, "INIT :insertLinkAdminStateTable() Failed");
            }
            else
            {
               LOG_PRINT(LOG_INFO, "INIT :insertLinkAdminStateTable() Success");

            }

         }
      } 
   }
   free(timeSlotObjPtr);
   LOG_PRINT(LOG_INFO,"Exiting cfgPopulateLinkAdminStateTable");

}
#endif

void   cfgObjectHandlerInit()
{

   LOG_PRINT(LOG_INFO,"Entering cfgObjectHandlerInit()");
   I_U32 i;
   CellPerTableApi *CellTableApiPtr=NULL;
   CellPerTableApi *tempCellTableApiPtr=NULL;
   TrunkTableApi *E1TableApiPtr=NULL;
   AbisTimeSlotPerTableApi *TimeSlotTableApiPtr=NULL;
   AbisTimeSlotPerTableApi *timeSlotptr=NULL;
   I_U32 noOfTimeSlotCount;
   I_U16 TimeSlotOutSize;
   I_U32 noOfCellCount=0;
   TrunkTableApi *t=NULL;
   I_U32 noOfE1Count;
   I_U16 E1OutSize=0;
   I_U16  outSize=0;
   I_S32 retVal=0;
   gCellLockDisProcForBssLock= FALSE;
   gCellEnableSent =0;
   gMsgSentForE1Num = 0xff;  
   gMsgSentForE1TSNum = 0xff;
   E1StatusTableApi e1StatusApi;
   I_U32 trunkSt = 0;
   BicTableApi *bicTableApiPtr=NULL;
   BicTableApi *tempBicTableApiPtr=NULL;
   I_U32 noOfBicCount=0;
   
   /*Changes PCU R2.5 Aricent -- START*/
   NsvcTableApi* nsvcTableApiPtr = NULL;
   NsvcTableApi* tempNsvcTableApiPtr = NULL;
   I_U32 NsvcCount = 0;
   I_U16 NsvcOutSize = 0;
   gGbUnlockReqSent = FALSE;
   /*Changes PCU R2.5 Aricent -- End*/
   /****************************/ 
   /*MANTIS 16723 CHANGES START */
   CellNonPerTableApi *CellNonTableApiPtr=NULL;
   CellNonPerTableIndices CellNonPerTableInData;
   I_U16 cellIndex=0;
   /*MANTIS 16723 CHANGES ENDS */

   DspInfoTableApi *pDspInfoTbl=NULL;
   DspInfoTableApi *pTempDspInfoTbl=NULL;
  
   gBssState = locked;
   gBssSubState = initBssSubState;
   
   if(I_TRUE != gCfgStandbyToActive)
 {    
   if(getallCellPerTable(&CellTableApiPtr,&noOfCellCount,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"cfgObjectHandlerInit : No Cells in CellPerTable in DB");
   }
	 LOG_PRINT(LOG_DEBUG,"Total Cells  = %d",noOfCellCount);
   /* Change For CS2.2 : Start */
   for ( i = 0; i < CFG_MAX_NUM_CELLS; i++ )
      /* Change For CS2.2 : End */
   {
      if ( noOfCellCount )
      {
         tempCellTableApiPtr =(CellPerTableApi*)((I_U8*)CellTableApiPtr+(i*outSize));             
         gCellData[i].Availlability = FALSE;
         if ( tempCellTableApiPtr->adminState == LOCKED )
         {  
            gCellData[i].CellState = locked;
         }
         /**** FIXED FOR  SPR #141  ****************************/
         else if ( tempCellTableApiPtr->adminState == UNLOCKED )
         {
            gCellData[i].CellState = unlockedDisabled;
         }
         /**** FIXED FOR  SPR #141  ****************************/
         gCellData[i].CellID = tempCellTableApiPtr->cellId;
         gCellData[i].adminState = tempCellTableApiPtr->adminState;
         gCellData[i].lac = tempCellTableApiPtr->lac;
         gCellData[i].reqType = 0;         
         gCellData[i].isReqSentForPS = FALSE;        

         noOfCellCount--;
      }
      else
      {
         gCellData[i].Availlability = TRUE;
         gCellData[i].CellState = locked;
         gCellData[i].lac = 0;
         gCellData[i].CellID = 0;
         gCellData[i].reqType = 0;
         gCellData[i].adminState = LOCKED;
         gCellData[i].opState = DISABLED;
         gCellData[i].isReqSentForPS = FALSE;        
      }
   }
   if(CellTableApiPtr  != NULL)
      free(CellTableApiPtr);
 }
   /*MANTIS 16723 CHANGES START */
 else
 {
   if(getallCellPerTable(&CellTableApiPtr,&noOfCellCount,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"cfgObjectHandlerInit : No Cells in CellPerTable in DB");
   }
	 LOG_PRINT(LOG_DEBUG,"SO case:Total Cells configured = %d",noOfCellCount);
     for (i = 0;i<CFG_MAX_NUM_CELLS; i++)/*Changes for Matnis 22741 Starts*/
     { 
       if(noOfCellCount)
       {  
         tempCellTableApiPtr =(CellPerTableApi*)((I_U8*)CellTableApiPtr+(i*outSize));        
         CellNonPerTableInData.cellId=tempCellTableApiPtr->cellId;
         CellNonPerTableInData.lac=tempCellTableApiPtr->lac;
         if(getCellNonPerTable(&CellNonPerTableInData,&CellNonTableApiPtr)!= CLIB_SUCCESS)
         {
         LOG_PRINT(LOG_MAJOR,"cfgObjectHandlerInit :getCellNonPerTable failed");
         } 
         else
         {  
           gCellData[(CellNonTableApiPtr->cellIndex)].Availlability = FALSE;
           if ( tempCellTableApiPtr->adminState == LOCKED )
           {  
            gCellData[(CellNonTableApiPtr->cellIndex)].CellState = locked;
           }
           /**** FIXED FOR  SPR #141  ****************************/
           else if ( tempCellTableApiPtr->adminState == UNLOCKED )
           {
            gCellData[(CellNonTableApiPtr->cellIndex)].CellState = unlockedDisabled;
           }
           /**** FIXED FOR  SPR #141  ****************************/
           gCellData[(CellNonTableApiPtr->cellIndex)].CellID = tempCellTableApiPtr->cellId;
           gCellData[(CellNonTableApiPtr->cellIndex)].adminState = tempCellTableApiPtr->adminState;
           gCellData[(CellNonTableApiPtr->cellIndex)].lac = tempCellTableApiPtr->lac;
           gCellData[(CellNonTableApiPtr->cellIndex)].reqType = 0;         
           gCellData[(CellNonTableApiPtr->cellIndex)].isReqSentForPS = FALSE;        
           if(CellNonTableApiPtr  != NULL)
           free(CellNonTableApiPtr);
          }
         
          noOfCellCount--;
         }
         else
         {
         gCellData[i].Availlability = TRUE;
         gCellData[i].CellState = locked;
         gCellData[i].lac = 0;
         gCellData[i].CellID = 0;
         gCellData[i].reqType = 0;
         gCellData[i].adminState = LOCKED;
         gCellData[i].opState = DISABLED;
         gCellData[i].isReqSentForPS = FALSE;        
         
         }    
     }
   if(CellTableApiPtr  != NULL)
      free(CellTableApiPtr);
   
 } /*Changes for Matnis 22741 Ends*/ 
   /*MANTIS 16723 CHANGES ENDS */
   if ((retVal=getallTrunkTable(&E1TableApiPtr,&noOfE1Count,&E1OutSize)) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"cfgObjectHandlerInit : E1 DB SUCCESS");
      for ( i = 0; i < noOfE1Count;i++ )
      {
         t =(TrunkTableApi*)((I_U8*)E1TableApiPtr + (i *E1OutSize));
         gE1Data[t->e1Num].e1Number=t->e1Num;
         if(t->adminState == 0)
         {
            gE1Data[t->e1Num].e1State=locked;
            e1StatusApi.state = LOCKED;
         }
         else
         {
            gE1Data[t->e1Num].e1State=unlocked;
            e1StatusApi.state = UNLOCKED;
         }
         /*Changes for CS4.0 : Abis E1 Lock/Unlock Start*/
         gE1Data[t->e1Num].usageType=t->usageType;
         gE1Data[t->e1Num].waitingForCellUnlockRespCounter=0;
         gE1Data[t->e1Num].e1CellLockReqSent=0;
         gE1Data[t->e1Num].e1CellUnlockReqSent=0;
         if(t->e1Category == INTERNAL_E1)
         {
            LOG_PRINT(DEBUG,"Initiliazing trunkstate as Enabled for e1Num(%d)",t->e1Num); 
            gE1Data[t->e1Num].trunkState= Enabled;
         }
         else if(t->e1Category == EXTERNAL_E1)
         {
             
            if(getTrunkStateForE1(t->e1Num, &trunkSt) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_CRITICAL,"cfgObjectHandlerInit : Trunk State for E1 is not found. DB query failed. Making TrunkState disbaled. for e1Num(%d)",t->e1Num);
               gE1Data[t->e1Num].trunkState= Disabled;
               LOG_PRINT(DEBUG,"Initiliazing trunkstate as disabled for e1Num(%d)",t->e1Num); 
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
            LOG_PRINT(LOG_CRITICAL," cfgObjectHandlerInit : Unknown E1 Ctaegory ");   
         }
         e1StatusApi.e1Id = t->e1Num;
         LOG_PRINT(DEBUG,"Going To insert E1StatusTable for E1(%d) TrunkState(%d) ", e1StatusApi.e1Id, e1StatusApi.state );

         if(gCfgStandbyToActive != I_TRUE )
         { 
            if(insertE1StatusTable(&e1StatusApi) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_CRITICAL," cfgObjectHandlerInit : Update operation on E1Status Table failed ");
            }
         }  
         /*Changes for CS4.0 : Abis E1 Lock/Unlock Ends*/
      }

      free(E1TableApiPtr);
   }
   else
      LOG_PRINT(LOG_CRITICAL," cfgObjectHandlerInit : No rows in E1 table ");


/*Changes PCU R2.5 Aricent -- START*/
   retVal = getallNsvcTable(&nsvcTableApiPtr,&NsvcCount,&NsvcOutSize);
   if(CLIB_SUCCESS != retVal && 0 == NsvcCount)
   {
      LOG_PRINT(LOG_INFO, "cfgObjectHandlerInit : No rows in Nsvc table, Error Code = [%d] ", retVal);
   }

   for(i = 0; i < OAMS_CFG_MAX_NUM_NSVCS; i++)
   {
      if ( NsvcCount )
      {
         tempNsvcTableApiPtr =(NsvcTableApi*)((I_U8*)nsvcTableApiPtr+(i*NsvcOutSize));
         gNsvcData[i].availability = FALSE;
         if ( tempNsvcTableApiPtr->adminState == LOCKED )
            gNsvcData[i].nsvcState = locked;
         else if ( tempNsvcTableApiPtr->adminState == UNLOCKED )
         {
            gNsvcData[i].nsvcState = unlockedDisabled;
         }
         gNsvcData[i].nsvcId = tempNsvcTableApiPtr->nsvcId;
         NsvcCount--;
      }
      else
      {
         gNsvcData[i].availability = TRUE;
         gNsvcData[i].nsvcState = locked;
         gNsvcData[i].nsvcId = 0;
      }
   }
   /*initialize gMccFrResourceMap*/   
   initMccFrResourceMap();
/*Changes PCU R2.5 Aricent -- End*/

   if ((retVal=getallAbisTimeSlotPerTable(&TimeSlotTableApiPtr,&noOfTimeSlotCount,&TimeSlotOutSize)) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"cfgObjectHandlerInit : TimeSlot DB SUCCESS");
      for ( i = 0; i < noOfTimeSlotCount;i++ )
      {
         timeSlotptr =(AbisTimeSlotPerTableApi*)((I_U8*)TimeSlotTableApiPtr + (i *TimeSlotOutSize));
         gE1TimeslotData[timeSlotptr->e1Num][timeSlotptr->tsNum].e1Number=timeSlotptr->e1Num;
         gE1TimeslotData[timeSlotptr->e1Num][timeSlotptr->tsNum].e1TimeslotID=timeSlotptr->tsNum;
         if(timeSlotptr->adminState == 0)
            gE1TimeslotData[timeSlotptr->e1Num][timeSlotptr->tsNum].e1TimeslotState = locked;
         else
            gE1TimeslotData[timeSlotptr->e1Num][timeSlotptr->tsNum].e1TimeslotState = unlocked;
      }
      free(TimeSlotTableApiPtr);
   }
   else
      LOG_PRINT(LOG_INFO,"cfgObjectHandlerInit :  No rows in TimeSlot table ");

   /* CS4.0 HA Stack Changes : Start */
   LinkTableApi *linkTablePtr = NULL;
   LinkTableApi *tempLinkPtr = NULL;
   CicTableApi *cicTablePtr = NULL;
   CicTableApi *tempCicPtr = NULL;
   I_U32 noOfRows = 0;
   I_U16 rowSize = 0;
   if (getallLinkTable(&linkTablePtr, &noOfRows, &rowSize) == CLIB_SUCCESS)
   {
      for (i = 0; i <noOfRows; i++)
      {
         tempLinkPtr = (LinkTableApi *)((I_U8*)linkTablePtr + (i *rowSize));
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
      LOG_PRINT(LOG_INFO,"cfgObjectHandlerInit :  No rows in Link table ");
   
   if (getallCicTable(&cicTablePtr, &noOfRows, &rowSize) == CLIB_SUCCESS)
   {
      for (i = 0; i <noOfRows; i++)
      {
         tempCicPtr = (CicTableApi *)((I_U8*)cicTablePtr + (i *rowSize));
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
      LOG_PRINT(LOG_INFO,"cfgObjectHandlerInit :  No rows in Cic table ");

   /* CS4.0 HA Stack Changes : End */
 
   /* Change For R2.2 : Start */
   if(getallBicTable(&bicTableApiPtr,&noOfBicCount,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"cfgObjectHandlerInit : No Bts in DB");
   }
   for ( i = 0; i < CFG_MAX_NUM_BTS; i++ )
   {
      if ( noOfBicCount )
      {
         tempBicTableApiPtr =(BicTableApi*)((I_U8*)bicTableApiPtr+(i*outSize));             
         if ( tempBicTableApiPtr->adminState == LOCKED )
            gBtsData[i].btsState = locked;
         else if ( tempBicTableApiPtr->adminState == UNLOCKED )
         {
            gBtsData[i].btsState = unlocked;
         }
         gBtsData[i].BTSID = tempBicTableApiPtr->bicId;
         gBtsData[i].btsType = tempBicTableApiPtr->btsType;
         gBtsData[i].connectivityState = none;
         noOfBicCount--;
      }
      else
      {
         gBtsData[i].BTSID = INVALID_BTS;
         gBtsData[i].btsType = 0;
         gBtsData[i].connectivityState = none;
         gBtsData[i].btsState = none;
      }
   }
   if(bicTableApiPtr  != NULL)
      free(bicTableApiPtr);
/* Change For R2.2 :End */
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
      }
   }

   if(pDspInfoTbl != NULL)
     free(pDspInfoTbl);
/*Merger for Mantis #31470*/
   fillNseiData();
/*Merger for Mantis #31470*/

   LOG_PRINT(LOG_INFO,"Exiting cfgObjectHandlerInit()");
}
/*Changes PCU R2.5 Aricent --START*/ 
I_Void populateCellIndices()
{
    /*Populating cellIndex in CellNonperTable*/ 
    CellNonPerTableApi cellNonPerTableApiBuff;
    I_S32 ret = CLIB_SUCCESS;
    I_U32 i = 0;

    for ( i = 0; i < CFG_MAX_NUM_CELLS; i++ )
    {
       if(FALSE == gCellData[i].Availlability )
       {
          memset(&cellNonPerTableApiBuff, 0 ,sizeof(CellNonPerTableApi));
          cellNonPerTableApiBuff.lac = gCellData[i].lac;
          cellNonPerTableApiBuff.cellId = gCellData[i].CellID;
          cellNonPerTableApiBuff.cellIndex = i;
          cellNonPerTableApiBuff.oprState = DISABLED;
          ret = updateCellNonPerTable(&cellNonPerTableApiBuff);
          if ( CLIB_SUCCESS != ret )
          {
             LOG_PRINT(LOG_MAJOR," udpation for cellIndex in CellNonPer table failed for cellId %d and lac %d, Error Code = [%d] ", cellNonPerTableApiBuff.cellId, cellNonPerTableApiBuff.lac, ret);
          }
       }
    }
}
/*Changes PCU R2.5 Aricent --End*/ 
/* This function will populate transient tables used by SCM - CCB #20*/
void cfgPopulateSksTransTables()
{
/* CS4.0 HA Stack Changes : Start */
   LinksetTableApi       *linksetPtr=NULL;
   LinksetTableApi       *tmpLinksetPtr=NULL;
   LinksetStatusTableApi  linksetStsTable;
   LinkTableApi       *linkPtr=NULL;
   LinkTableApi       *tmpLinkPtr=NULL;
   LinkStatusTableApi  linkStsTable;
   Ss7RouteTableApi *ss7RoutePtr =NULL;
   Ss7RouteTableApi *tmpSs7RoutePtr =NULL;
   Ss7RouteStatusTableApi ss7RouteStatusTable;
   I_U32 outRows = 0, i;
   I_U16 outSize = 0;
   
   LOG_PRINT(LOG_INFO, " Start populating LinksetStatusTable"); 
   if (getallLinksetTable(&linksetPtr,&outRows,&outSize) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO, "Number of rows returned by API getallLinksetTable = %d", outRows);
      for (i = 0; i < outRows; i++)
      {
         tmpLinksetPtr = (LinksetTableApi *)((char*)linksetPtr + (i *outSize));

         linksetStsTable.linksetID = tmpLinksetPtr->linksetID;
         linksetStsTable.oprState = DISABLED;

         if ( insertLinksetStatusTable(&linksetStsTable) != CLIB_SUCCESS )
         {
            LOG_PRINT(LOG_MAJOR, "INIT :insertLinksetStatusTable() Failed for Linkset = %d", tmpLinksetPtr->linksetID);
         }
      }
      free(linksetPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO, "INIT : read getallLinksetTable() Failed");
   }
   LOG_PRINT(LOG_INFO, " End populating LinksetStatusTable");

   LOG_PRINT(LOG_INFO, " Start populating LinkStatusTable");
   if (getallLinkTable(&linkPtr,&outRows,&outSize) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO, "Number of rows returned by API getallLinkTable = %d", outRows);
      for (i = 0; i < outRows; i++)
      {
         tmpLinkPtr = (LinkTableApi *)((char*)linkPtr + (i *outSize));

         linkStsTable.linksetID = tmpLinkPtr->linksetID;
         linkStsTable.linkId = tmpLinkPtr->linkId;
         linkStsTable.oprState = DISABLED;

         if ( insertLinkStatusTable(&linkStsTable) != CLIB_SUCCESS )
         {
            LOG_PRINT(LOG_MAJOR, "INIT :insertLinkStatusTable() Failed for Link = %d", tmpLinkPtr->linkId);
         }
      }
      free(linkPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO, "INIT : read getallLinkTable() Failed");
   }
   LOG_PRINT(LOG_INFO, " End populating LinkStatusTable");

   LOG_PRINT(LOG_INFO, " Start populating Ss7RouteStatusTable");
   if (getallSs7RouteTable(&ss7RoutePtr,&outRows,&outSize) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO, "Number of rows returned by API getallSs7RouteTable = %d", outRows);
      for (i = 0; i < outRows; i++)
      {
         tmpSs7RoutePtr = (Ss7RouteTableApi *)((char*)ss7RoutePtr + (i *outSize));

         ss7RouteStatusTable.linksetID = tmpSs7RoutePtr->linksetID;
         ss7RouteStatusTable.routeID = tmpSs7RoutePtr->routeID;
         ss7RouteStatusTable.oprState = DISABLED;

         if ( insertSs7RouteStatusTable(&ss7RouteStatusTable) != CLIB_SUCCESS )
         {
            LOG_PRINT(LOG_MAJOR, "INIT :insertSs7RouteStatusTable() Failed for routeID = %d", tmpSs7RoutePtr->routeID);
         }
      }
      free(ss7RoutePtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO, "INIT : read getallSs7RouteTable() Failed");
   }
   LOG_PRINT(LOG_INFO, " End populating Ss7RouteStatusTable");

/* CS4.0 HA Stack Changes : End */

#if 0   /* CS4.0 HA Stack Changes */
   SccpSsnConfigTableApi *sccpSsnConfigPtr=NULL;
   SccpSsnConfigTableApi *tmprSccpSsnConfigPtr=NULL;
   SccpSsnStsTableApi     sccpSsnStsTable;

   Mtp3LinksetTableApi       *mtp3LinksetPtr=NULL;
   Mtp3LinksetTableApi       *tmpMtp3LinksetPtr=NULL;
   Mtp3LinksetStsTableApi     mtp3LinksetStsTable;


   Mtp3LinkTableApi	*mtp3LinkPtr		= NULL;
   Mtp3LinkTableApi     *tmpMtp3LinkPtr		= NULL;
   Mtp3LinkStsTableApi  mtp3LinkStsTableInd;
  
   I_U32    count = 0;
   I_U16   outSize = 0;
   I_U32    i = 0;

   LOG_PRINT(LOG_INFO,"Entering cfgPopulateSksTransTables()");

   LOG_PRINT(LOG_INFO, " Start populating SccpSsnStsTable");
   /* populate SccpSsnStsTableApi*/   
   if (getallSccpSsnConfigTable(&sccpSsnConfigPtr,&count,&outSize) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG, "Number of rows returned by API getallSccpSsnConfigTable = %d", count);
      for (i = 0; i < count; i++)
      {
         tmprSccpSsnConfigPtr = (SccpSsnConfigTableApi*)((char*)sccpSsnConfigPtr + (i *outSize));

         sccpSsnStsTable.sccpSsnConfigssn = tmprSccpSsnConfigPtr->sccpSsnConfigssn;
         sccpSsnStsTable.sccpSsnConfigpc = tmprSccpSsnConfigPtr->sccpSsnConfigpc;
         sccpSsnStsTable.sccpSsnConfigni = tmprSccpSsnConfigPtr->sccpSsnConfigni;
         sccpSsnStsTable.sccpSsnConfigisLocal = tmprSccpSsnConfigPtr->sccpSsnConfigisLocal;
         sccpSsnStsTable.sccpSsnConfigstatus = DISABLED;

         if ( insertSccpSsnStsTable(&sccpSsnStsTable) != CLIB_SUCCESS )
         {
            LOG_PRINT(LOG_MAJOR, "INIT :insertSccpSsnStsTable() Failed");
            LOG_PRINT(LOG_DEBUG, "INIT :insertSccpSsnStsTable() Failed for ssn = %d", sccpSsnStsTable.sccpSsnConfigssn);
         }
         else
         {
            LOG_PRINT(LOG_DEBUG, "INIT :insertSccpSsnStsTable() Success for ssn = %d", sccpSsnStsTable.sccpSsnConfigssn);
         }
      }
      if (count > 0)
         free(sccpSsnConfigPtr);

   }
   else
   {
      LOG_PRINT(LOG_INFO, "INIT SccpSsnStsTable : read SccpSsnConfigTable() Failed");
   }
   LOG_PRINT(LOG_INFO, " End populating SccpSsnStsTable");


   LOG_PRINT(LOG_INFO,"Entering cfgPopulateSksTransTables()");

   LOG_PRINT(LOG_INFO, " Start populating Mtp3LinksetStsTable");
   /* populate Mtp3LinksetStsTableApi*/   
   if (getallMtp3LinksetTable(&mtp3LinksetPtr,&count,&outSize) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG, "Number of rows returned by API getallMtp3LinksetTable = %d", count);
      for (i = 0; i < count; i++)
      {
         tmpMtp3LinksetPtr = (Mtp3LinksetTableApi*)((char*)mtp3LinksetPtr + (i *outSize));

         mtp3LinksetStsTable.MTP3LinksetlinksetID = tmpMtp3LinksetPtr->MTP3LinksetlinksetID;
         mtp3LinksetStsTable.oprState = DISABLED;

         if ( insertMtp3LinksetStsTable(&mtp3LinksetStsTable) != CLIB_SUCCESS )
         {
            LOG_PRINT(LOG_MAJOR, "INIT :insertMtp3LinksetStsTable() Failed");
            LOG_PRINT(LOG_DEBUG, "INIT :insertMtp3LinksetStsTable() Failed for Linkset = %d", mtp3LinksetStsTable.MTP3LinksetlinksetID);
         }
         else
         {
            LOG_PRINT(LOG_DEBUG, "INIT :insertMtp3LinksetStsTable() Success for Linkset = %d", mtp3LinksetStsTable.MTP3LinksetlinksetID);
         }
      }
      if (count > 0)
         free(mtp3LinksetPtr);

   }
   else
   {
      LOG_PRINT(LOG_INFO, "INIT : read getallMtp3LinksetTable() Failed");
   }

   LOG_PRINT(LOG_INFO, " End populating Mtp3LinksetStsTable");

   LOG_PRINT(LOG_INFO,"Start Populating Mtp3LinkStsTable");
   if(getallMtp3LinkTable(&mtp3LinkPtr,&count,&outSize) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG,"Number of Rows = %d", count);
      for (i = 0; i < count; i++)
      {
         tmpMtp3LinkPtr = (Mtp3LinkTableApi*)((I_U8*)mtp3LinkPtr + (i*outSize));

         mtp3LinkStsTableInd.MTP3LinklinksetID	 =  tmpMtp3LinkPtr->mtp3LinklinksetID;
         mtp3LinkStsTableInd.MTP3Linklinkcode 	 =  tmpMtp3LinkPtr->mtp3LinklinkCode;
         mtp3LinkStsTableInd.oprState		 =  DISABLED;

         if(insertMtp3LinkStsTable(&mtp3LinkStsTableInd) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_DEBUG,"Insert on Mtp3LinkStsTable Failed for Linkset = %d, Linkcode = %d",
				mtp3LinkStsTableInd.MTP3LinklinksetID,
				mtp3LinkStsTableInd.MTP3Linklinkcode);
         }
         else
         {
            LOG_PRINT(LOG_DEBUG,"Insert on Mtp3LinkStsTable Success for Linkset = %d, LinkCode = %d",
				mtp3LinkStsTableInd.MTP3LinklinksetID,
				mtp3LinkStsTableInd.MTP3Linklinkcode);
         }
      }
      free(mtp3LinkPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Get on Mtp3LinkTable Failed");
   }
   LOG_PRINT(LOG_INFO,"End Populating Mtp3LinkStsTable");

   LOG_PRINT(LOG_INFO,"Exiting cfgPopulateSksTransTables");
#endif
}

void cfgInit()
{
   /* initialize the cfg state machine */
   cfgHistInit();
   cfgSigInit();
   cfgObjectHandlerInit();
   cfgInitAinterfaceTable();
   //cfgInitTrauTable();
   //cfgPopulateLinkAdminStateTable();  /* CS4.0 HA Stack Changes */

   /* CCB #20 */
   cfgPopulateSksTransTables();

   /* Changes For CS2.2 : Start */
   //initAbisE1TsList();
   /*BSC R2.2 Changes*/
   sendingInitAbisE1();
   //populateBicTeiE1MapTable();
   //initGlobalMaxCellNumVar();
   /* Changes For CS2.2 : End */

   /* Fixed Mantis #5384 : Start */
   gLacOfRcvReq = ZERO;
   gCellIdOfRcvReq = ZERO;
   /* Fixed Mantis #5384 : End */

   LOG_PRINT(LOG_INFO," end of cfgInit()");

}

void cfgInitAinterfaceTable()
{

   AInterfaceTableApi aInterfaceTableApiBuf;
   AifInterfaceTableApi *aifInterfaceTablePtr=NULL;
   I_U32 outRows=0;
   I_U16 outSize=0;



   aInterfaceTableApiBuf.dummyIndex = 0;
   aInterfaceTableApiBuf.oprState = DISABLED;
   if(insertAInterfaceTable(&aInterfaceTableApiBuf) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"Insert of A Interface table is failed");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Insert of A Interface table is successful");
   }

   if(I_FALSE == gCfgStandbyToActive )
   {
      /* Updating AifInterfaceTable status to DISABLED fix for mantis 7986*/
      
      if (getallAifInterfaceTable(&aifInterfaceTablePtr,
               &outRows, &outSize) == CLIB_SUCCESS )
      {
         aifInterfaceTablePtr->operationalState =  DISABLED;
         if( updateAifInterfaceTable(aifInterfaceTablePtr) 
               != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_CRITICAL," udpation AifInterfaceTableApi failed ");
         }
         free(aifInterfaceTablePtr);
      }
      else
      {
         LOG_PRINT(LOG_DEBUG," getallAifInterfaceTable failed ");   
      }
   }
}


/*BSC R2.0 Changes Starts*/
#if 0 
void cfgInitTrauTable()
{
   TrauOprStsTableApi trauOprStsTableApiBuf;

   trauOprStsTableApiBuf.trauId = TRAU_ID;
   trauOprStsTableApiBuf.oprStatus = DISABLED;
   if(insertTrauOprStsTable(&trauOprStsTableApiBuf) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"Insert TrauOprStsTable of  table is failed");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Insert of TrauOprStsTableApi table is successful");
   }
}
#endif
/*BSC R2.0 Changes Ends*/

void bpmAisCallbackFunc(struct sAisParam* param)
{
   /* Reference: cs2.5-3306
    * Problem: Healthcheck is periodic.
    *          Thus, this print fills the log file with hardly useful information.
    *  Solution: Commented out enter, exit and HealthCheck info logging.
    */

   /* See reference: cs2.5-3306
       LOG_PRINT(LOG_INFO,"*****  Entering CALLBACK FUNCTION bpmAisCallbackFunc **************"); */
   switch(param->messageId)
   {
      case BPM_HEALTHCHECK_MESSAGE:
//          LOG_PRINT(LOG_INFO,"   **** HealthCheck Callback Function by OH ****  "); 

         bpmRespondToAis (param->invocation,OK);
//               LOG_PRINT(LOG_DEBUG," Sending OK Notification for BPM_HEALTHCHECK_MESSAGE");
         break;

      case BPM_SELFCARD_STATE_CHANGE:
         LOG_PRINT(LOG_INFO,"SelfCard State Change Callback called");
         LOG_PRINT(LOG_INFO,"Sending StateChange Request Message to RM");
         /* Added for BPM Integration*/
         /*BSC CS4.0 HA Changes Starts*/
         switch(param->cardState)
         {

            case  CARDSTATE_INIT:
               LOG_PRINT(LOG_INFO," CARDSTATE_INIT");
               gCurrentCardState = CARDSTATE_INIT;
               gNextCardState = CARDSTATE_INVALID;
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               bpmRespondToAis (param->invocation,OK);
               LOG_PRINT(LOG_DEBUG," Sending OK Notification for CARDSTATE_INIT");
               break;
            case CARDSTATE_PLATFORM_INS:
               LOG_PRINT(LOG_INFO," CARDSTATE_PLATFORM_INS");
               gNextCardState = CARDSTATE_PLATFORM_INS;
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               LOCK_MUTEX;
         sendStateChangeReqToRm(param->cardState);
//               sendMessageToCfg();
               // Lock and Wait Mutex
               if(LOCK_MUTEX_AND_WAIT != MUTEX_WAIT_COMPLETE)
               {
                  bpmRespondToAis (param->invocation,OK);
               LOG_PRINT(LOG_DEBUG,"Sending OK Notification for CARDSTATE_PLATFORM_INS");
               }
               RELEASE_MUTEX;
               gCurrentCardState = CARDSTATE_PLATFORM_INS;
               gNextCardState = CARDSTATE_INVALID;
               break;
            case CARDSTATE_IN_SERVICE:
               g_card_in_recovery_mode = FALSE;
               LOG_PRINT(LOG_INFO,"CARDSTATE_IN_SERVICE");
               gNextCardState = CARDSTATE_IN_SERVICE;
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               LOCK_MUTEX;
         sendStateChangeReqToRm(param->cardState);
//               sendMessageToCfg();
               // Lock and Wait Mutex
               if(LOCK_MUTEX_AND_WAIT != MUTEX_WAIT_COMPLETE)
               {
                  bpmRespondToAis (param->invocation,OK);
               LOG_PRINT(LOG_DEBUG,"Sending OK Notification for CARDSTATE_IN_SERVICE");
               }
               RELEASE_MUTEX;
               gCurrentCardState = CARDSTATE_IN_SERVICE;
               gNextCardState = CARDSTATE_INVALID;
               break;
            case CARDSTATE_ACTIVE:
               LOG_PRINT(LOG_INFO,"CARDSTATE_ACTIVE");
               gNextCardState = CARDSTATE_ACTIVE;
               g_card_in_standby_mode = FALSE;
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               LOCK_MUTEX;
         sendStateChangeReqToRm(param->cardState);
               if(LOCK_MUTEX_AND_WAIT != MUTEX_WAIT_COMPLETE)
               {
                  bpmRespondToAis (param->invocation,OK);
                  LOG_PRINT(LOG_DEBUG," Sending OK Notification for CARDSTATE_ACTIVE");
               }
               RELEASE_MUTEX;
               //gCurrentCardState = CARDSTATE_ACTIVE; Moved To INFO_CARD_STATE_CHANGE Alarm
						#if 0
							 /*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
								 if( gSwicthoverCloudTrigger == 1)
									{
               			 LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA::gSwicthoverCloudTrigger(%d) Matched Going for HaConf After Switchover",gSwicthoverCloudTrigger);
										 initiateSwitchoverProcForCloudBscStack();	
										 gSwicthoverCloudTrigger=0;//resetting it to zero again	
									}	
							 /*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
						#endif
               gNextCardState = CARDSTATE_INVALID;

               break;
            case CARDSTATE_ACTIVE_IN_PROGRESS:
               LOG_PRINT(LOG_INFO,"CARDSTATE_ACTIVE_IN_PROGRESS");
               gNextCardState = CARDSTATE_ACTIVE_IN_PROGRESS;
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
#if 0  
//Not required now for Redundancy 05-09-2016 Gaurav Sinha
							 /*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
								if((gCurrentCardState == CARDSTATE_STANDBY) && (gNextCardState == CARDSTATE_ACTIVE_IN_PROGRESS))
								{
								  gSwicthoverCloudTrigger = 1;	
               		LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA::CASE of SWITCHOVER flag:: gSwicthoverCloudTrigger(%d)updated:: SBY->AIP",gSwicthoverCloudTrigger);
								}
							 /*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
//Not required now for Redundancy 05-09-2016 Gaurav Sinha
#endif
               LOCK_MUTEX;
         sendStateChangeReqToRm(param->cardState);
               //sendMessageToCfg();
               
               //OK NOTIFICATION
               //Lock the mutex for completion of BPM DB Initialize Query
               if(LOCK_MUTEX_AND_WAIT != MUTEX_WAIT_COMPLETE)
               {
                  bpmRespondToAis (param->invocation,OK);
               LOG_PRINT(LOG_DEBUG," Sending OK Notification for CARDSTATE_ACTIVE_IN_PROGRESS");
               }
               RELEASE_MUTEX;
               gCurrentCardState = CARDSTATE_ACTIVE_IN_PROGRESS;
               gNextCardState = CARDSTATE_INVALID;
               break;
            case CARDSTATE_STANDBY:
               LOG_PRINT(LOG_INFO,"CARDSTATE_STANDBY");
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               gNextCardState = CARDSTATE_STANDBY;
               if(gCurrentCardState == CARDSTATE_IN_SERVICE)
               {
                  gCfgState = CFG_STANDBY;
                  sendSlotIdQueryToRm();
               }
               // CS Harsh will be checked during E1 Enable/Disable Procedure
               g_card_in_standby_mode = TRUE;
               // CS Harsh
               sendNeipReq();
               gCurrentCardState = CARDSTATE_STANDBY;
               gNextCardState = CARDSTATE_INVALID;
               bpmRespondToAis (param->invocation,OK);
               LOG_PRINT(LOG_DEBUG," Sending OK Notification for CARDSTATE_STANDBY");
               break;
            case CARDSTATE_OUT_OF_SERVICE:
               LOG_PRINT(LOG_INFO,"CARDSTATE_OUT_OF_SERVICE");
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               LOCK_MUTEX;
               sendStateChangeReqToRm(param->cardState);
               //sendMessageToCfg();
               
               //OK NOTIFICATION
               //Lock the mutex for completion of BPM DB Initialize Query
               if(LOCK_MUTEX_AND_WAIT != MUTEX_WAIT_COMPLETE)
               {
                  bpmRespondToAis (param->invocation,OK);
                  LOG_PRINT(LOG_DEBUG," Sending OK Notification for CARDSTATE_OUT_OF_SERVICE");
               }

               gCurrentCardState = CARDSTATE_OUT_OF_SERVICE;
               gNextCardState = CARDSTATE_INVALID;
               break;
            case CARDSTATE_RECOVERY:
               LOG_PRINT(LOG_INFO,"CARDSTATE_RECOVERYE");
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               LOCK_MUTEX;
               sendStateChangeReqToRm(param->cardState);
               //sendMessageToCfg();
               
               //OK NOTIFICATION
               //Lock the mutex for completion of BPM DB Initialize Query
               if(LOCK_MUTEX_AND_WAIT != MUTEX_WAIT_COMPLETE)
               {
                  bpmRespondToAis (param->invocation,OK);
                  LOG_PRINT(LOG_DEBUG," Sending OK Notification for CARDSTATE_RECOVERY");
               }

               g_card_in_recovery_mode = TRUE;
               gCurrentCardState = CARDSTATE_RECOVERY;
               gCfgState = CFG_INIT;
               gNextCardState = CARDSTATE_INVALID;
               break;
            case CARDSTATE_FAIL:
               LOG_PRINT(LOG_INFO,"CARDSTATE_FAILED");
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               gCurrentCardState = CARDSTATE_FAIL;
               gNextCardState = CARDSTATE_INVALID;
               bpmRespondToAis (param->invocation,OK);
               LOG_PRINT(LOG_DEBUG," Sending OK Notification for CARDSTATE_FAIL");
               break;
            case CARDSTATE_DIAGNOSTIC :
               LOG_PRINT(LOG_INFO,"CARDSTATE_DIAGNOSTIC");
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               gCurrentCardState = CARDSTATE_DIAGNOSTIC;
               gNextCardState = CARDSTATE_INVALID;
               bpmRespondToAis (param->invocation,OK);
               LOG_PRINT(LOG_DEBUG," Sending OK Notification for CARDSTATE_DIAGNOSTIC");
               break;
            case CARDSTATE_ABSENT:
               LOG_PRINT(LOG_INFO,"CARDSTATE_ABSENT");
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               gCurrentCardState = CARDSTATE_ABSENT;
               gNextCardState = CARDSTATE_INVALID;
               bpmRespondToAis (param->invocation,OK);
               LOG_PRINT(LOG_DEBUG," Sending OK Notification for CARDSTATE_ABSENT");
               break;
            case CARDSTATE_UPGRADE:
               LOG_PRINT(LOG_INFO,"CARDSTATE_UPGRADE");
               LOG_PRINT(LOG_DEBUG," gCurrentCardState : [%d], gNextCardState : [%d]" , gCurrentCardState, gNextCardState);
               //gCurrentCardState = CARDSTATE_UPGRADE;
               //gNextCardState = CARDSTATE_INVALID;
               bpmRespondToAis (param->invocation,OK);
               LOG_PRINT(LOG_DEBUG," Sending OK Notification for CARDSTATE_UPGRADE");
               break;
         } 
         /*BSC CS4.0 HA Changes Ends*/

//         bpmRespondToAis (param->invocation,OK);
         break;

      case BPM_PEERCARD_STATE_CHANGE:
         LOG_PRINT(LOG_INFO,"....PeerCard State Change Callback called....");
         LOG_PRINT(LOG_DEBUG," Sending OK Notification for BPM_PEERCARD_STATE_CHANGE");
         bpmRespondToAis (param->invocation,OK);
         break;

      case BPM_MSG_ACK_PEER_HEALTH_BAD:
         LOG_PRINT(LOG_INFO,"BPM_MSG_ACK_PEER_HEALTH_BAD ");
         break;

      case BPM_MSG_ACK_CONFIGURE:
         LOG_PRINT(LOG_INFO,"BPM_MSG_ACK_CONFIGURE ");
         break;
      case BPM_MSG_ACK_CONFIGURE_RESET:
         LOG_PRINT(LOG_INFO,"BPM_MSG_ACK_CONFIGURE_RESET ");
         break;
      case BPM_SHUTDOWN:
         LOG_PRINT(LOG_INFO,"BPM_SHUTDOWN received from platform");
         exit(1);
         break;
      default:
         break;
   }
   /* See reference: cs2.5-3306
       LOG_PRINT(LOG_INFO,"*****  Exiting CALLBACK FUNCTION bpmAisCallbackFunc **************"); */   

} /* End of function bpmAisCallbackFunc() */

#if BPM_PRESENT == 1
void cfgBpmInit()
{
   LOG_PRINT(LOG_INFO,"CFG: Calling function cfgBpmInit()");
   LOG_PRINT(LOG_INFO,"CFG: Registering with Real BPM");
   bpmGetComponentRegister( bpmAisCallbackFunc, APPID_OAMS_CFG);
   bpmComponentConfigure();
} /* End of function cfgBpmInit() */
#else
void cfgBpmInit()
{
   LOG_PRINT(LOG_INFO,"CFG: Calling function cfgBpmInit()");
   LOG_PRINT(LOG_INFO,"CFG: Registering with BPM Stub");
   //bpmGetComponentReg(ENT_OAMS_CFG_STUB,&bpmAisCallbackFunc );
   bpmGetComponentReg(ENT_OAMS_CFG_STUB,&bpmAisCallbackFunc );
}
#endif /* BPM_PRESENT */

/*BSC-R2.5.5 Diagnostic Changes Start*/
void cfgDiagInit()
{
   I_U32 ret;
   LOG_PRINT(DEBUG,"calling function initDiagLib"); 
   ret = initDiagLibrary();
  /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
 if(DIAG_LIBINIT_SUCCESS ==  ret)
 {
    gCfgInitDiagLibSucc = I_TRUE; 
 }
 else 
 {
    gCfgInitDiagLibSucc = I_FALSE; 
 }
  /*Changed for 1U BSC DIAGNOSTICS 19 Oct 2016 Gaurav Sinha*/
} 
/*BSC-R2.5.5 Diagnostic Changes End*/


void cfgFrmwrkInit()
{
   I_S8 retVal;
   LOG_PRINT(LOG_INFO,"CFG: Calling function cfgFrmwrkInit()");
   gSrcId = ENT_OAMS_CFG;
   retVal = RegisterWithIpcFrmwrk(gSrcId, (I_S8*)"CFG");
   LOG_PRINT(LOG_INFO,"Return Value of IPC Registration: %d",retVal);
   if (retVal < ZERO)
      cfgPanic(CFG_REGD_IPC_FAIL);
   LOG_PRINT(LOG_INFO,"CFG: Calling function cfgFrmwrkInit() Exiting");
} /* End of function cfgFrmwrkInit() */

void cfgHistInit()
{
   gHistBufPtr = NULL;
   gHistRunPtr = NULL;
} /* End of function cfgHistInit() */
void cfgDbInit()
{
   LOG_PRINT(LOG_INFO," Calling DB Connect");
   dbConnect();
   LOG_PRINT(LOG_INFO," after DB Connect Call ");

} /* End of function cfgDbInit() */

void cfgSigInit()
{
   /* Ignore the signals */
   LOG_PRINT(LOG_INFO,"Iam In cfgSigInit()");
   signal(SIGINT, (sighandler_t )cfgSigintHandler);
   signal(SIGQUIT, (sighandler_t )cfgSigquitHandler);
   signal(SIGSTOP, (sighandler_t )cfgSigstopHandler);
   signal(SIGUSR1, SIG_IGN);
   signal(SIGUSR2, SIG_IGN);
   signal(SIGTERM, SIG_IGN);
   signal(SIGALRM, (sighandler_t )cfgSigalrmHandler);
   reg_sig_hndlr();
//   signal(SIGSEGV, (sighandler_t )cfgSigsegvHandler);
   signal(SIGBUS,(sighandler_t ) cfgSigbusHandler);
   signal(SIGILL,(sighandler_t ) cfgSigillHandler);
//   signal(SIGFPE,(sighandler_t ) cfgSigfpeHandler);
   LOG_PRINT(LOG_INFO," Iam exiting cfgSigInit()");
} /* End of function cfgSigInit() */


void cfgOpenErrLog()
{
   I_CHAR *errFname; 
   struct stat  statBuf; /* stat buffer */

   /* Mark the log flag as failure */
   gLogFlag = 0;
   /* Error file name creation */
   errFname =(I_CHAR *) malloc(LOG_FILE_NAME_SIZE);
   memset(errFname,0,10);
   memcpy(errFname, "oamcfg.log", LOG_FILE_NAME_SIZE); 
   /* check if the file exists */
   if (stat(errFname, &statBuf) != -1)
   {
      /* if the file size is greater than the threshold,
          then create a new error log file */
      if (statBuf.st_size >= MAX_ERR_LOG_FL_SZ)
      {
         /* save the current error log file as backup log file */
         unlink("oamcfg.bak");
         link(errFname, "oamcfg.bak");
         unlink(errFname);
      } /* end of if stat() == UNIXERR */
   } /* end of if stat() == UNIXERR */

   /* create the error log file */
   gErrFname = fopen("oamcfg.log", "a+");

   /* open stdout as log file */
   freopen(errFname, "a+", stdout);
   /* if (freopen(err_fnam, "a+", stdout) != NULL)
       gLogFlag |= LOG_ERR_FILE; */
   /* Open console for error logging */
   errFname = "/dev/console";
   /* Open console for error logging */
   freopen(errFname, "a+", stderr);
   /* if (freopen(err_fnam, "a+", stderr) != NULL)
       gLogFlag |= LOG_CONSOLE; */
} /* End of function cfgOpenErrLog() */



void cfgPanic(I_S8 err)
{
   LOG_PRINT(LOG_CRITICAL," .. Panic ..............");
   /* Do Nothing ...*/
}
void   cfgCellObjectHandlerInit()
{

   LOG_PRINT(LOG_INFO,"Entering cfgCellObjectHandlerInit()");
   I_U32 i;
   CellPerTableApi *CellTableApiPtr=NULL;
   CellPerTableApi *tempCellTableApiPtr=NULL;
   I_U32 noOfCellCount=0;
   I_U16  outSize=0;
   memset (&gCellData[0],0,sizeof( CellDataStruct ) *CFG_MAX_NUM_CELLS);
   if(getallCellPerTable(&CellTableApiPtr,&noOfCellCount,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"cfgObjectHandlerInit : No Cells in DB");
   }
   for ( i = 0; i < CFG_MAX_NUM_CELLS;i++ )
   {
      if ( noOfCellCount )
      {
         tempCellTableApiPtr =(CellPerTableApi*)((I_U8*)CellTableApiPtr+(i*outSize));             
         gCellData[i].Availlability = FALSE;
         if ( tempCellTableApiPtr->adminState == LOCKED )
         {  
            gCellData[i].CellState = locked;
         } 
         /**** FIXED FOR  SPR #141  ****************************/
         else if ( tempCellTableApiPtr->adminState == UNLOCKED )
         {
            gCellData[i].CellState = unlockedDisabled;
         }
         /**** FIXED FOR  SPR #141  ****************************/
         gCellData[i].CellID = tempCellTableApiPtr->cellId;
         gCellData[i].adminState = tempCellTableApiPtr->adminState;
         gCellData[i].lac = tempCellTableApiPtr->lac;
         gCellData[i].reqType = 0;         
         noOfCellCount--;
      }
      else
      {
         gCellData[i].Availlability = TRUE;
         gCellData[i].CellState = locked;
         gCellData[i].lac = 0;
         gCellData[i].CellID = 0;
         gCellData[i].reqType = 0;
         gCellData[i].adminState = LOCKED;
         gCellData[i].opState = DISABLED;
      }
   }
   if(CellTableApiPtr  != NULL)
      free(CellTableApiPtr);


   LOG_PRINT(LOG_INFO,"Exiting cfgCellObjectHandlerInit()");
}

I_Void sendCfgReadyIndToTB() 
{
   OamsCfgTbReadyStateInd sndPtr;
   LOG_PRINT(LOG_INFO,"Entering sendCfgReadyIndToTB()");

   cfgSendMessage(&sndPtr, sizeof(OamsCfgTbReadyStateInd),ENT_PSAPP_TBBSC, OAMS_CFG_TBBSC_READY_STATE_IND, 0);
   LOG_PRINT(LOG_INFO,"Exiting sendCfgReadyIndToTB()");
}


/********************************* Function  Header********************************
Function Name:       cfgSendAifdhmLclsInd
Parameters:          localSwitchingSupport,bscId
Return type:         retVal
Purpose:             To send LCLS ind message to AIFDHM
Other Note:
 ************************************************************************************/
I_S32 cfgSendAifdhmLclsInd(I_Bool localSwitchingSupport,I_U32 bscId)
{
  OamsCfgAifdhmLclsInd   sndMsgBuff; 
  I_S32                  retVal = 0;
  LOG_PRINT(LOG_INFO,"Entering cfgSendAifdhmLclsInd()");

  sndMsgBuff.bssLclsSupport = localSwitchingSupport;
  sndMsgBuff.bscId = bscId;
  LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_AIFDHM_LCLS_IND with LclsSupp: %u, BscId: %u",
      sndMsgBuff.bssLclsSupport, sndMsgBuff.bscId);
  retVal = cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgAifdhmLclsInd), 
					ENT_CSAPP_AIFDHM, OAMS_CFG_AIFDHM_LCLS_IND, 0);

  LOG_PRINT(LOG_INFO,"Exiting cfgSendAifdhmLclsInd()");
  return retVal;
}

/*Latest changes merged for CLOUD R2-BSC ROOT BRANCH GAURAV SINHA 22 DEC 2015*/
/********************************* Function  Header********************************
Function Name:       cfgSendCphmBssUnlockInd
Parameters:          None
Return type:         retVal
Purpose:             To send OAMS_CFG_CPHM_BSS_UNLOCK_IND message to AIFDHM
Other Note:
 ************************************************************************************/
I_S32 cfgSendCphmBssUnlockInd()
{
  OamsCfgCphmBssUnlockInd   sndMsgBuff; 
  I_S32                     retVal = 0;
  LOG_PRINT(LOG_INFO,"Entering cfgSendCphmBssUnlockInd()");

  LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_CPHM_BSS_UNLOCK_IND");
  retVal = cfgSendMessage(&sndMsgBuff, sizeof(OamsCfgCphmBssUnlockInd), 
					ENT_CSAPP_CPHM, OAMS_CFG_CPHM_BSS_UNLOCK_IND, 0);

  LOG_PRINT(LOG_INFO,"Exiting cfgSendCphmBssUnlockInd()");
  return retVal;
}
/*Latest changes merged for CLOUD R2-BSC ROOT BRANCH GAURAV SINHA 22 DEC 2015*/
/********************************* Function  Header*****************************
   Function Name   : goToReadyState()
Parameters   : None
Return type   : I_Void
Purpose      : It set state of CFG as Ready and If Bss state is currently 
unlock then  start Bss Unlock procedure.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void goToReadyState()
{
   LOG_PRINT(LOG_INFO,"Entering Function : goToReadyState");

   gCfgState = CFG_READY;
   LOG_PRINT(LOG_INFO,"CFG is in READY STATE");
   gCfgAlarmIdRcvd = 0;

   /* Added for R-2.8 */
   /* Send CFGH_RADY to TB */
   sendCfgReadyIndToTB();

   /* Send LCLS IND to AIFDHM */
   getDbBssTable();
   //cfgSendAifdhmLclsInd(gDbBssTableApiStorage.localSwitchingSupport, gDbBssTableApiStorage.bscId); Commenented for CLOUD 
		/*Latest changes merged for CLOUD R2-BSC ROOT BRANCH GAURAV SINHA 22 DEC 2015*/
   if ( gDbBssTableApiStorage.adminState == UNLOCKED)
   {
      if(I_FALSE == gCfgStandbyToActive)
      {
          SysAddr slfAddr;
          TmrPayLoad tmrPayLoad;
          slfAddr.entity= ENT_OAMS_CFG;
          strcpy((I_S8 *)tmrPayLoad.payLoad,"SYSTEM_STARTUP");
          LOG_PRINT(LOG_INFO,"SYSTEM STARTUP Timer Started...(20 secs)...");
          StartTimerFrmwrk(&slfAddr,SYSTEM_STARTUP_TIMER,&tmrPayLoad,&tid);
      }
      else
      {
          gBssState = unlockInProgress;
          gBssSubState = aIfUnlockInProgress; 
          //if (gDbBssTableApiStorage.gprsEnabled) //Merger for Mantis #31470
          if (gDbBssTableApiStorage.gprsEnabled && gNseiData.nseiState == unlocked)
          {
             /* UNLOCK GB interface towards GB interface */
             sendPsscmUnlockReq(OAMS_RSN_OPERATORINITIATED);	    
          }  
          else
          {
             /* CFG will execute Unlock (Enabled) Cell procedure
                for all the Unlocked and Disabled cells */
             generateResetAfterSwitchOver();  
             gCellEnableSent = 0;
             initiateCellUnlockEnableforUnlcokedDisabledCells();
             //sendCellEnableToCbsh();/*Changes for Mantis 16678 */
             //informCellUnLockEnableforUnlockDisabledCellsToBss();
             if(0 == gCellEnableSent)
             {
                gCfgStandbyToActive = I_FALSE;
             } 
          }
      }   
   }
   else
   { 
      if(gCfgStandbyToActive == I_TRUE) 
      {
          gBssState = lockInProgress;
          gBssSubState = aIfLockInProgress; 
          
          LOG_PRINT(LOG_INFO, "BSS is locked in switch over hence Calling bssObjectSendLinkAdminStateTableToScm");
          bssObjectSendLinkAdminStateTableToScm(UNLOCKED,LOCKED);
      } 
   } 
   LOG_PRINT(LOG_INFO,"Exiting Function : goToReadyState");
}


/********************************* Function  Header*****************************
   Function Name   : stopMgsTimer()
Parameters   : None
Return type   : I_Void
Purpose      : Stops timer which is started for MGS 
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
#if 0 //R2.0 changes
I_Void stopMgsTimer()
{
   LOG_PRINT(LOG_INFO,"Stopping MGS Timer");
   StopTimerFrmwrk(tid);
   tid = 0;
}
#endif

/********************************* Function  Header*****************************
   Function Name   : startMgsTimer()
Parameters   : None
Return type   : I_Void
Purpose      : Start timer for MGS 
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void startMgsTimer()
{
   SysAddr slfAddr;
   TmrPayLoad tmrPayLoad;
   LOG_PRINT(LOG_INFO,"Starting MGS Timer");
   slfAddr.entity= ENT_OAMS_CFG;
   strcpy(tmrPayLoad.payLoad,"TSI_TRAU_INIT");
   StartTimerFrmwrk(&slfAddr, SCM_CFG_RESP_TIMER, &tmrPayLoad, &tid);
}


/********************************* Function  Header*****************************
   Function Name   : initGlobalMaxCellNumVar()
Parameters   : None
Return type   : I_Void
Purpose      : It initialize gMaxCellsNum global variable with the maximum 
possible number of cells at BSC which is calculated using
preconfig data.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
#if 0
I_Void initGlobalMaxCellNumVar()
{
   InFrameTrxE1TsTableApi* inFrameTrxTablePtr = NULL;
   I_U32 outRows = ZERO;
   I_U16 outSz = ZERO;
   I_S32 dbStatus = -1;

   LOG_PRINT(LOG_INFO,"Entering Function : initGlobalMaxCellNumVar");

   gMaxCellsNum = ZERO;

   gMaxCellsNum = getMaxTrxNumFrmAbisList();

   dbStatus = getallInFrameTrxE1TsTable(&inFrameTrxTablePtr, &outRows, &outSz);
   if(DBLIB_SUCCESS == dbStatus)
   {
      gMaxCellsNum += outRows;
      free(inFrameTrxTablePtr);
   }

   if(gMaxCellsNum > CFG_MAX_NUM_CELLS)
   {
      gMaxCellsNum = CFG_MAX_NUM_CELLS;
   }

   LOG_PRINT(LOG_DEBUG,"initGlobalMaxCellNumVar : gMaxCellsNum : %d", 
         gMaxCellsNum);
   LOG_PRINT(LOG_INFO,"Exiting Function : initGlobalMaxCellNumVar");
}
#endif

/********************************* Function  Header*****************************
   Function Name   : freeGlobalVarForMgs()
Parameters   : None
Return type   : I_Void
Purpose      : It free the memory allocated for global varibles used to store 
response from MGS.
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void freeGlobalVarForMgs()
{
   if(gStoredTsiDriverStatusMsg != NULL)
   {
      DalocOrdBuf(gStoredTsiDriverStatusMsg);
      gStoredTsiDriverStatusMsg = NULL;
      LOG_PRINT(LOG_INFO,"freeGlobalVarForMgs : Dalocating - gStoredTsiDriverStatusMsg");
   }
   if(gStoredDspBootMsg != NULL)
   {
      DalocOrdBuf(gStoredDspBootMsg);
      gStoredDspBootMsg = NULL;
      LOG_PRINT(LOG_INFO,"freeGlobalVarForMgs : Dalocating - gStoredDspBootMsg");
   }
}

/*BSC CS4.0 HA Changes Starts*/

/********************************* Function  Header*****************************
Function Name   : cfgCleanUpResources()
Parameters      : None
Return type     : I_Void
Purpose         : This function will free all the memor allocated to global 
                  variables and structures. 
Other Note   : Added For BSC CS4.0 HA Feature
 *******************************************************************************/

I_Void cfgCleanUpResources()
{
   LOG_PRINT(LOG_INFO,"cfgCleanUpResources : Entering in function");

   LOG_PRINT(LOG_DEBUG,"cfgCleanUpResources : Cleaning Buffer Pointers");
   cfgCleanBuffer();
   
   /*
   LOG_PRINT(LOG_DEBUG,"cfgCleanUpResources : Cleaning AbisE1Ts List");
   cfgCleanAbisE1TsList();*/

   LOG_PRINT(LOG_DEBUG,"cfgCleanUpResources : Cleaning Global Data");
   cfgCleanGlobalData();
   
   LOG_PRINT(LOG_DEBUG,"cfgCleanUpResources : Cleaning Path Name Resources");
   cfgFreePathNameResources();
   
//   LOG_PRINT(LOG_DEBUG,"cfgCleanUpResources : Cleaning Transient Tables");
//   cfgCleanTransientTable();

   LOG_PRINT(LOG_INFO,"cfgCleanUpResources : Exiting from function");
   
}


/********************************* Function  Header*****************************
Function Name   : cfgCleanTransientTable()
Parameters      : None
Return type     : I_Void
Purpose         : This function will delete all the rows of all transient table owned by CFG. 
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/

I_Void cfgCleanTransientTable()
{
   I_U16 i;
   I_U32 oprStateAInterface = 0;
   OamsCfgGrhmLockReq OamsCfgGrhmLockReqBuff={0};
   OamsCfgGrhmUnlockReq OamsCfgGrhmUnlockReqBuff={0};

   LOG_PRINT(LOG_INFO,"cfgCleanTransientTable : Entering in function");

   //LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning TrauOprStsTable");
   //CALLCLEANDBTABLE(TrauOprStsTable);
   
   /*Newly Added Starts R2.3*/
   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning DspTrauAbisResourceConfigTable");
   CALLCLEANDBTABLE(DspTrauAbisResourceConfigTable);

   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning DspTrauPcmResourceConfigTable");
   CALLCLEANDBTABLE(DspTrauPcmResourceConfigTable);

   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning DspTrauResourceMapTable");
   CALLCLEANDBTABLE(DspTrauResourceMapTable);

   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning TrauChannelUsageTable");
   CALLCLEANDBTABLE(TrauChannelUsageTable);

//   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning SwmNodeTable");
//   CALLCLEANDBTABLE(SwMNodeTable);

   
   //LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning LAPDOperationalStatus Table");
   //CALLCLEANDBTABLE(LapdOperationalStatusTable);

   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning IccCardInfo Table");
   CALLCLEANDBTABLE(IccCardInfoTable);

   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning SystemClkInfo Table");
   CALLCLEANDBTABLE(SystemClkInfoTable);

   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning CardStateChange Table");
   CALLCLEANDBTABLE(CardStateChangeTable);

   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning SwMOffer Table");
   CALLCLEANDBTABLE(SwMOfferTable);
   
   //LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning SwMOfferIp Table");
   //CALLCLEANDBTABLE(SwMOfferIpTable);//Veena

   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning Mlppp Channel Status Table");
   CALLCLEANDBTABLE(MlpppChannelStatusTable);

   /*BSC R2.0 Changes Starts*/
   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning ClkSourceStatusTable"); 
   CALLCLEANDBTABLE(ClkSourceConfigStatusTable);
   /*BSC R2.0 Changes Ends*/
   /* R2.4 Changes Start */
   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning CbsStatusTableApi Table");
   CALLCLEANDBTABLE(CbsStatusTable);
   /* R2.4 changes End */

   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning NsvcStatus Table");
   CALLCLEANDBTABLE(NsvcStatusTable);
   
   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning FrLinkStatus Table");
   CALLCLEANDBTABLE(FrLinkStatusTable);
  
   LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning FrLinkExtE1TsMccE1TsMapTable Table");
   CALLCLEANDBTABLE(FrLinkExtE1TsMccE1TsMapTable);
   
   if(gCfgStandbyToActive != I_TRUE) 
   {
     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning SwMTable");
     CALLCLEANDBTABLE(SwMTable);//Rishabh

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning E1NonPerTable");
     CALLCLEANDBTABLE(E1NonPerTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning AbisTimeSlotNonPerTable");
     CALLCLEANDBTABLE(AbisTimeSlotNonPerTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning LinksetStatus Table");
     CALLCLEANDBTABLE(LinksetStatusTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning LinkStatus Table");
     CALLCLEANDBTABLE(LinkStatusTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning SS7RouteStatusTable");
     CALLCLEANDBTABLE(Ss7RouteStatusTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning TrxTsTeiTable");
     CALLCLEANDBTABLE(TrxTsTeiTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning BicE1TeiMapTable");
     CALLCLEANDBTABLE(BicE1TeiMapTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning Ainterface Table");
     CALLCLEANDBTABLE(AInterfaceTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning PtrxTable");
     CALLCLEANDBTABLE(PtrxTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning LtrxTable");
     CALLCLEANDBTABLE(LtrxTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning BicStatusTable");
     CALLCLEANDBTABLE(BicStatusTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning CellNonPerTable");
     CALLCLEANDBTABLE(CellNonPerTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning TrxHCreatedChnTable");
     CALLCLEANDBTABLE(TrxHCreatedChnTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning RadioTimeslotTable");
     CALLCLEANDBTABLE(RadioTimeslotTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning ChannelParamsTable");
     CALLCLEANDBTABLE(ChannelParamsTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning ChannelUsageTable");
     CALLCLEANDBTABLE(ChannelUsageTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning E1StatusTable");
     CALLCLEANDBTABLE(E1StatusTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning TrunkPortStatusTable"); 
     CALLCLEANDBTABLE(TrunkPortStatusTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning PowerSupplyInfoTable");
     CALLCLEANDBTABLE(PowerSupplyInfoTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning SystemType Table");
     CALLCLEANDBTABLE(SystemTypeTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning ChasisFrame Table");
     CALLCLEANDBTABLE(ChasisFrameIdTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning EicCardInfoTable");
     CALLCLEANDBTABLE(EicCardInfoTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning FanTrayInfoTableApi Table");
     CALLCLEANDBTABLE(FanTrayInfoTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning FanInfoTableApi Table");
     CALLCLEANDBTABLE(FanInfoTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning DspStatusTableApi Table");
     CALLCLEANDBTABLE(DspStatusTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning GbIfStatus Table");
     CALLCLEANDBTABLE(GbIfStatusTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning PsCellStatus Table");
     CALLCLEANDBTABLE(PsCellStatusTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning PsAppCellPmTable PS Performance Counter Table");
     CALLCLEANDBTABLE(PsAppCellPmTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning GbBssGpStackCellPmTable PS Performance Counter Table");
     CALLCLEANDBTABLE(GbBssGpStackCellPmTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning GbBssGpStackPmTable PS Performance Counter Table");
     CALLCLEANDBTABLE(GbBssGpStackPmTable);

     LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning GbNsStackPmTable PS Performance Counter Table");
     CALLCLEANDBTABLE(GbNsStackPmTable);
     /*Mantis 22060 + 23337  + 23682 Changes Start*/
     // LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning RadioNwAvailabilityTable");
     // CALLCLEANDBTABLE(RadioNwAvalabilityPMTable);

     // LOG_PRINT(LOG_DEBUG,"cfgCleanTransientTable : Cleaning DataAvailabilityTable");
     // CALLCLEANDBTABLE(DataAvalabilityPMTable);
     /*Mantis 22060 + 23337  + 23682 Changes End*/
   }
   else
   {
      for(i= 0; i< 8; i++)
      {
        if(gAipLinkAlarmData[i].flag == TRUE)
        {
           updateOrInsertLinkStatusTable(gAipLinkAlarmData[i].linkSetId,
                      gAipLinkAlarmData[i].linkId, gAipLinkAlarmData[i].oprState);   
        }
        else
        {
           break;
        }  
      }
      memset(gAipLinkAlarmData,0,sizeof(AipLinkAlarmData) * 8);

      if(gAipLinkSetAlarmData.flag == TRUE) 
      {
         updateOrInsertLinkSetStatusTable(gAipLinkSetAlarmData.linkSetId,
                  gAipLinkSetAlarmData.oprState);
         memset(&gAipLinkSetAlarmData,0,sizeof(AipLinkSetAlarmData));
      }

      if(gAipResumeRcvd == TRUE) 
      {
         updateOrInsertSs7RouteStatusTable(gAipResumeRcvdPc,ENABLED);
      }
      else if(gAipPauseRcvd)
      {
         updateOrInsertSs7RouteStatusTable(gAipResumeRcvdPc,DISABLED);
      }
      /* R2.9 Changes */
      if (gAipSSPRcvd == TRUE)
      {
         gSSAReceived = FALSE;
         getAInterfaceOprState(&oprStateAInterface);
         if(oprStateAInterface == ENABLED)
         {
            /* Send OAMS_CFG_GRHM_LOCK_REQ */
            setAinterfaceTableOperationalState(DISABLED);
            OamsCfgGrhmLockReqBuff.objectId=0;
            OamsCfgGrhmLockReqBuff.objType = OAMS_OBJTYPE_AINTERFACE;
            OamsCfgGrhmLockReqBuff.reason = OAMS_RSN_AINTERFACEDOWN;
            cfgSendMessage(&OamsCfgGrhmLockReqBuff, sizeof(OamsCfgGrhmLockReq), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_LOCK_REQ, 0);
            gAifMsgSentToGrhm = OAMS_CFG_GRHM_LOCK_REQ;
         }
         else
         {
             LOG_PRINT(LOG_INFO,"A interface is already Disabled");               
         }
      }
      if(gAipSSARcvd == TRUE)
      {
         gSSAReceived = TRUE;
         OamsCfgGrhmUnlockReqBuff.objectId=0;
         OamsCfgGrhmUnlockReqBuff.objType = OAMS_OBJTYPE_AINTERFACE;
         OamsCfgGrhmUnlockReqBuff.reason = OAMS_RSN_AINTERFACEUP;
         cfgSendMessage(&OamsCfgGrhmUnlockReqBuff, sizeof(OamsCfgGrhmUnlockReq), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_UNLOCK_REQ, 0);
         gAifMsgSentToGrhm = OAMS_CFG_GRHM_UNLOCK_REQ;
      }
   }

   LOG_PRINT(LOG_INFO,"cfgCleanTransientTable : Exiting from function");
/*Changes PCU R2.5 Aricent -- END*/
}

CLEANDBTABLEIMPLEMENTATION(RadioNwAvalabilityPMTable);
CLEANDBTABLEIMPLEMENTATION(DataAvalabilityPMTable);
//CLEANDBTABLEIMPLEMENTATION(TrauOprStsTable)
CLEANDBTABLEIMPLEMENTATION(CellNonPerTable)
/*New Tables Added for BSC R2.3 Starts*/
CLEANDBTABLEIMPLEMENTATION(PtrxTable);
CLEANDBTABLEIMPLEMENTATION(PowerSupplyInfoTable);
CLEANDBTABLEIMPLEMENTATION(BicStatusTable);
CLEANDBTABLEIMPLEMENTATION(RadioTimeslotTable);
CLEANDBTABLEIMPLEMENTATION(LtrxTable);
CLEANDBTABLEIMPLEMENTATION(DspTrauAbisResourceConfigTable);
CLEANDBTABLEIMPLEMENTATION(DspTrauPcmResourceConfigTable);
CLEANDBTABLEIMPLEMENTATION(DspTrauResourceMapTable);
CLEANDBTABLEIMPLEMENTATION(ChannelParamsTable);
CLEANDBTABLEIMPLEMENTATION(ChannelUsageTable);
CLEANDBTABLEIMPLEMENTATION(TrauChannelUsageTable);
CLEANDBTABLEIMPLEMENTATION(TrxHCreatedChnTable);
CLEANDBTABLEIMPLEMENTATION(E1StatusTable);
/*New Tables Added for BSC R2.3 Ends*/
CLEANDBTABLEIMPLEMENTATION(E1NonPerTable)
CLEANDBTABLEIMPLEMENTATION(AbisTimeSlotNonPerTable)
CLEANDBTABLEIMPLEMENTATION(SwMNodeTable)
CLEANDBTABLEIMPLEMENTATION(SwMTable)
CLEANDBTABLEIMPLEMENTATION(LinksetStatusTable)
CLEANDBTABLEIMPLEMENTATION(LinkStatusTable)
CLEANDBTABLEIMPLEMENTATION(Ss7RouteStatusTable)
//CLEANDBTABLEIMPLEMENTATION(LapdOperationalStatusTable)
CLEANDBTABLEIMPLEMENTATION(SystemTypeTable)
CLEANDBTABLEIMPLEMENTATION(ChasisFrameIdTable)
CLEANDBTABLEIMPLEMENTATION(IccCardInfoTable)
CLEANDBTABLEIMPLEMENTATION(EicCardInfoTable)
CLEANDBTABLEIMPLEMENTATION(DspInfoTable)
CLEANDBTABLEIMPLEMENTATION(SystemClkInfoTable)
CLEANDBTABLEIMPLEMENTATION(CardStateChangeTable)
CLEANDBTABLEIMPLEMENTATION(TrxTsTeiTable)
CLEANDBTABLEIMPLEMENTATION(BicE1TeiMapTable)
CLEANDBTABLEIMPLEMENTATION(SwMOfferTable)
CLEANDBTABLEIMPLEMENTATION(AInterfaceTable)
CLEANDBTABLEIMPLEMENTATION(MlpppChannelStatusTable)
CLEANDBTABLEIMPLEMENTATION(ClkSourceConfigStatusTable)
CLEANDBTABLEIMPLEMENTATION(TrunkPortStatusTable)
CLEANDBTABLEIMPLEMENTATION(DspStatusTable)
CLEANDBTABLEIMPLEMENTATION(CbsStatusTable)
CLEANDBTABLEIMPLEMENTATION(FanTrayInfoTable)
CLEANDBTABLEIMPLEMENTATION(FanInfoTable)
/*Changes PCU R2.5 Aricent -- START*/
CLEANDBTABLEIMPLEMENTATION(PsCellStatusTable)
CLEANDBTABLEIMPLEMENTATION(NsvcStatusTable)
CLEANDBTABLEIMPLEMENTATION(GbIfStatusTable)
CLEANDBTABLEIMPLEMENTATION(FrLinkStatusTable)
CLEANDBTABLEIMPLEMENTATION(FrLinkExtE1TsMccE1TsMapTable)

CLEANDBTABLEIMPLEMENTATION(PsAppCellPmTable)
CLEANDBTABLEIMPLEMENTATION(GbBssGpStackCellPmTable)
CLEANDBTABLEIMPLEMENTATION(GbBssGpStackPmTable)
CLEANDBTABLEIMPLEMENTATION(GbNsStackPmTable)
/*Changes PCU R2.5 Aricent -- END*/



/********************************* Function  Header*****************************
Function Name   : cfgCleanGlobalData()
Parameters      : None
Return type     : I_Void
Purpose         : This function will free all the global data and initialized them to NULL. 
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/

I_Void cfgCleanGlobalData()
{
   I_U32 trx;
   I_U32 e1;
   I_U32 ts;
   I_U32 cell;
   I_U32 bts;  /* Change for R2.2 */
   I_U32 nsvc; /* Change for PCU R2.5 */
   I_U32 cbs;  /* Change for R2.4 */
   I_U32 dsp;
   
   LOG_PRINT(LOG_INFO,"cfgCleanGlobalData : Entering in function");
   gRecvMsgSize = 0;
   gCellLockDisProcForBssLock= FALSE;
   gCellUnLockEnableProcForBssUnLock= FALSE;
   memset(&gDbBssTableApiStorage,0,sizeof(BssTableApi));
   gAinterfaceUPDownFlag = FALSE;
   gFirstBSSTableStorageUpdation = FALSE;
   gPsUnlockCellsProgressFlgForBSS = FALSE;
   gCellEnableSent =0;
   gCellDisableSent =0;
   gStoredMsgBufPtr=NULL;
   gMlpppStoredMsgBufPtr = NULL;
   gMgsWaitForRspFlg= MGS_NO_WAIT;
   gMgsSmmTsiRspFlag=TRUE;
   gMgsSmmDspBootFlag = TRUE;
   gStoredTsiDriverStatusMsg=NULL;
   gStoredDspBootMsg=NULL;
   gTimerId=0;
   gCbsTimerId=0;
   breakRespAwaited=FALSE;
   gCmTrasId=0;
   memset(&gThreadParams,0,sizeof(Params));
   gBssState = locked;
   gMsgSentForE1Num = 0xff;
   gMsgSentForE1TSNum = 0xff;
   gIsTimerRunning = FALSE;
   gSSAReceived=FALSE;
   gAifMsgSentToGrhm=FALSE;
   g_card_in_standby_mode = FALSE;
   g_card_in_recovery_mode = FALSE;
   gAvailReleaseRspFlag = ZERO;
   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) initialized to zero in cfgCleanGlobalData()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS
   gBssNcc=0;
   //gFirstEicAvailResp = FALSE;
   gFirstDspAvailResp = FALSE;
   updateEicDetail = FALSE;
   updateDspDetail = FALSE;
   gIsAllLinkUnlockReqd = FALSE;
   gIsAllLinkLockReqd = FALSE;
   /* Changes For E1-T1 */
   gBscTrunkType = 0;

/*Changes PCU R2.5 Aricent -- START*/
   for(trx = 0 ; trx < MAX_NUM_TRX_PER_BSS; trx++)
   {
      memset(&gPtrxData[trx] , 0 , sizeof(PtrxDataStruct));
   }
   
   for(cell = 0 ; cell < MAX_NUM_CELL_PER_BSS; cell++)
	{
      memset(&gCellData[cell] , 0 , sizeof(CellDataStruct));
   }

   for(e1 = 0 ; e1 < CFG_MAX_NUM_E1 ; e1++)
   {
	   memset(&(gE1Data[e1]),0,sizeof(E1DataStruct));
   }

   for(e1 = 0 ; e1 < CFG_MAX_NUM_E1 ; e1++)
      for(ts = 0 ; ts < CFG_MAX_NUM_E1_TS ; ts++)
      {   
         memset(&gE1TimeslotData[e1][ts],0,sizeof(E1TimeslotDataStruct));
      }
/*Changes PCU R2.5 Aricent -- End*/
   for(bts = 0 ; bts < CFG_MAX_NUM_BTS ; bts++)
   {
      memset(&gBtsData[bts] , 0 , sizeof(BtsDataStruct));
   }
/*Changes PCU R2.5 Aricent -- START*/   
   for(nsvc = 0; nsvc < OAMS_CFG_MAX_NUM_NSVCS; nsvc++)
   {
      memset(&gNsvcData[nsvc], 0, sizeof(NsvcDataStruct));
   }
/*Changes PCU R2.5 Aricent -- End*/
   for(dsp = 0;dsp< MAX_NUM_DSP_TOTAL;dsp++)
   {
     memset(&gDspData[dsp],0,sizeof(DspDataStruct));
   }

   gSentAddBicReqAtInitNum=0;
   gSentAddTrxReqAtInitNum=0;
   gMgsOprSts=FALSE;
   gLacOfRcvReq=0;
   gCellIdOfRcvReq=0;
   gCfgAlarmBuf = NULL;
   gCurrentConnectivityMode = NO_MODE;
   gMlpppLinkStatus = MLPPP_LINK_DISABLED;

   gIsListCreated = FALSE;
   memset(&gclkSrcCfgData,0,sizeof(clkSrcCfgData));

   memset(gDspInfo,0,MAX_DSP * sizeof(sDspObjInfo));

   memset(gDspBootInfoSent,0,MAX_DSP);

   for(cbs = 0 ; cbs < MAX_CBS_SERVER ; cbs++)
   {
      memset(&cbsRespTimer[cbs] , 0xFF , sizeof(CbsRespTimer));
      memset(&cbsRepeatTimer[cbs] , 0xFF , sizeof(CbsRepeatTimer));
   }

   bzero(&gSwActBuff, sizeof(gSystemDetails));
   gSendSwActReq = I_FALSE;
   gSwActReqSent = I_FALSE;
   LOG_PRINT(DEBUG,"gSendSwActReq flag is reset");

   gTrunkPortStsReqSent = 0;
   gEnabledEicSlotId = 0;
   gCfgStandbySlotId = 0;
   gSetNeIpRcvd = I_FALSE;
   gSetOmcIpReqSent = I_FALSE;
   gdummyIndexRNATbl=ZERO;
   gdummyIndexDataATbl=ZERO;
/*BSC-R2.5.5 Diagnostic Changes Start*/
   bzero(&gCfgDiagData,sizeof(DiagDataStruct));
   /* mantis 0019784, 0024546 start */
   gCfgDiagData.diagCmdState  = 0xFF;
   /* mantis 0019784, 0024546 end */
   LOG_PRINT(DEBUG,"Value of gCfgDiagData.diagCmdState now set to = %d", gCfgDiagData.diagCmdState);

   gCfgDiagBpmRespTimerId = 0;
   gCfgDiagIntervalTimerId = 0; 
   gCfgDiagTimerRunning = DIAG_NO_TIMER_RUNNING;
/*BSC-R2.5.5 Diagnostic Changes End*/

   bzero(gAipLinkAlarmData, sizeof(AipLinkAlarmData) * 8);
   bzero(&gAipLinkSetAlarmData, sizeof(AipLinkSetAlarmData));
   gAipPauseRcvd = 0;
   gAipResumeRcvd = 0;
   gAipSSARcvd = 0;
   gAipSSPRcvd = 0;
   gAipResumeRcvdPc = 0;  
   //Mantis 31749
   /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
   LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: cfgCleanGLobalData : Before resetting gCardPlatformType [%d]",gCardPlatformType);
   gCardPlatformType=0;
   LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: cfgCleanGLobalData : After resetting gCardPlatformType [%d]",gCardPlatformType);
   /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
   //Mantis 31749
   LOG_PRINT(LOG_INFO,"cfgCleanGLobalData : Exiting from function");
}

/********************************* Function  Header*****************************
Function Name   : cfgCleanBuffer()
Parameters      : None
Return type     : I_Void
Purpose         : This function will free all the Buffer pointers and initialized them to NULL. 
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/

I_Void cfgCleanBuffer()
{
   LOG_PRINT(LOG_INFO,"cfgCleanBuffer : Entering in function");
   LOG_PRINT(LOG_DEBUG,"cfgCleanBuffer : Cleaning gCfgMsgBuf");
/*   if(gCfgMsgBuf != NULL)
   {
      DalocMsgBuf((I_Void *) gCfgMsgBuf);
      gCfgMsgBuf = NULL;
   }*/

   LOG_PRINT(LOG_DEBUG,"cfgCleanBuffer : Cleaning gCfgAlarmBuf");
   if(gCfgAlarmBuf != NULL)
   {
      DalocOrdBuf(gCfgAlarmBuf);
      gCfgAlarmBuf = NULL;
   }

   LOG_PRINT(LOG_DEBUG,"cfgCleanBuffer : Cleaning gStoredTsiDriverStatusMsg");
   if(gStoredTsiDriverStatusMsg != NULL)
   {
      DalocOrdBuf(gStoredTsiDriverStatusMsg);
      gStoredTsiDriverStatusMsg = NULL;
   }

   LOG_PRINT(LOG_DEBUG,"cfgCleanBuffer : Cleaning gStoredMsgBufPtr");
   if(gStoredMsgBufPtr != NULL)
   {
      DalocOrdBuf(gStoredMsgBufPtr);
      gStoredMsgBufPtr = NULL;
   }
   
   if(gMlpppStoredMsgBufPtr != NULL)
   {
      DalocOrdBuf(gMlpppStoredMsgBufPtr);
      gMlpppStoredMsgBufPtr = NULL;
   }
   LOG_PRINT(LOG_DEBUG,"cfgCleanBuffer : Cleaning gStoredDspBootMsg");
   if(gStoredDspBootMsg != NULL)
   {
      DalocOrdBuf(gStoredDspBootMsg);
      gStoredDspBootMsg = NULL;
   }

   LOG_PRINT(LOG_DEBUG,"cfgCleanBuffer : Cleaning gSystemDetails");
   if(gSystemDetails != NULL)
   {
      DalocOrdBuf(gSystemDetails);
      gSystemDetails = NULL;
   }
   LOG_PRINT(LOG_INFO,"cfgCleanBuffer : Exiting from function");
}

//Mantis 31749
/********************************* Function  Header*****************************
Function Name   : updateCardPlatformTypeInContext()
Parameters      : None
Return type     : I_Void
Purpose         : This function will get the PlatformType from DB and initialize 
                  context 
Other Note   : Added For OMC SWITCHOVER of IP_BSC/1U_BSC
*******************************************************************************/
I_Void updateCardPlatformTypeInContext()
{
 LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: Entering into : updateCardPlatformTypeInContext");
 SysOmcRegisterTableIndices indata;
 SysOmcRegisterTableApi     *outData = NULL;
 indata.sysOmcIndex = SYS_OMC_INDEX;
 if(getSysOmcRegisterTable(&indata,&outData) == CLIB_SUCCESS)
 {
   LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: getSysOmcRegisterTable() SUCCESS");
   if(strcmp(outData->sysOmcRegisterprodId,"6004") == ZERO)
   {
      LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: PRODUCT ID is [IP_BSC] [6004] gCardPlatformType remains [%d]",gCardPlatformType);
   }
   else if(strcmp(outData->sysOmcRegisterprodId,"6005") == ZERO)
   {
      gCardPlatformType=1;
      LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: PRODUCT ID is [1U_BSC] [6005] gCardPlatformType changed to [%d]",gCardPlatformType);
   }
   else
   {
      LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: PRODUCT ID is INVALID in SysOmcRegisterTable :: gCardPlatformType remains [%d]",gCardPlatformType);
   } 
 free(outData); 
 }
 LOG_PRINT(LOG_DEBUG,"Exiting  from : updateCardPlatformTypeInContext");
}
//Mantis 31749

/********************************* Function  Header*****************************
Function Name   : cfgInitAfterDbRw()
Parameters      : None
Return type     : I_Void
Purpose         : This function will Initialize the DB after receiving DBRw notifiation from RM. 
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void cfgInitAfterDbRw()
{
   LOG_PRINT(LOG_INFO,"cfgInitAfterDbRw : Entering in function");

   LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRwcfgCleanBuffer : Initializing Object Handlers");
   cfgObjectHandlerInit();
   
   LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Initializing AInterface Table");
   cfgInitAinterfaceTable();
   
    /*BSC R2.0 Changes Starts*/
   //LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Initializing Trau Table");
   //cfgInitTrauTable();
   
   LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Initializing Stack Table");
   cfgPopulateSksTransTables();

   LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Initializing csTransient Table");
   csTransientTableIntialization();
   LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Initializing psTransient Table");
   psTransientTableIntialization();
   
   LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Initializing PS PerformanceCounters Table");
   psPerformanceCounterTableIntialization();

/* Changes for R2.2 : Start */
/*
   LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Initializing AbisE1-Timeslot List");
   initAbisE1TsList();

   LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Initializing Global Max Cell Number");
   initGlobalMaxCellNumVar();
*/

   if(I_TRUE != gCfgStandbyToActive)
   {
      LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Sending AbisE1Init message");
      sendingInitAbisE1();

      LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Populating Cell Indices");
      populateCellIndices(); 
   }
/* Changes for R2.2 : End */

   LOG_PRINT(LOG_DEBUG,"cfgInitAfterDbRw : Initializing MLPPP Channel Status Table");
   insertMlpppChannelStatusforAllRows();
   gLacOfRcvReq = ZERO;
   gCellIdOfRcvReq = ZERO;
   /*IP_BSC_STACK: Initializing SigtranLocalAspConfigTable OperationalState Gaurav Sinha 29-09-2016*/
   LOG_PRINT(DEBUG,"IP_BSC_STACK: Initializing Operational State of SigtranM3uaLAspConfigTableApi to DISABLED at STARTUP");
   initSigtranM3UALocalAspOperStateAtStartUp();
   /*IP_BSC_STACK: Initializing SigtranLocalAspConfigTable OperationalState Gaurav Sinha 29-09-2016*/
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   initGlobalDsForAspStatusAtStartup();
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   LOG_PRINT(LOG_INFO,"cfgInitAfterDbRw : Exiting from function");
}

/********************************* Function  Header*****************************
Function Name   : sendStateChangeReqToRm()
Parameters      : I_S8 cardState
Return type     : I_Void
Purpose         : This function will send the State Change Request message to RM 
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/

I_Void sendStateChangeReqToRm(I_S8 cardState)
{
   RmCardStateNotification rmCardStateNotification;
   LOG_PRINT(LOG_INFO,"sendStateChangeReqToRm : Entering in function");
   LOG_PRINT(LOG_INFO,"sendStateChangeReqToRm : Card State Sent to RM [%d]" , cardState);
   rmCardStateNotification.cardState = cardState;
   cfgSendMessage(&rmCardStateNotification , sizeof(RmCardStateNotification) , ENT_OAMS_RM , BPM_SELFCARD_STATE_CHANGE, 0);
   LOG_PRINT(LOG_INFO,"sendStateChangeReqToRm : Exiting from function");
}


/********************************* Function  Header*****************************
Function Name   : sendSlotIdQueryToRm()
Parameters      : None
Return type     : I_Void
Purpose         : This function will send the query message to RM to know about the slot id.  
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void sendSlotIdQueryToRm()
{
#if 0
   OamsCfgRmSlotIdReq oamsCfgRmSlotIdReq;
   LOG_PRINT(LOG_INFO,"sendSlotIdQueryToRm : Entering in function");
   cfgSendMessage(&oamsCfgRmSlotIdReq , sizeof(OamsCfgRmSlotIdReq) , ENT_OAMS_RM , OAMS_CFG_RM_SLOTID_REQ, 0);
   LOG_PRINT(LOG_INFO,"sendSlotIdQueryToRm : Exiting from function");
#endif
}

/*BSC CS4.0 HA Changes Starts*/

/********************************* Function  Header*****************************
Function Name: generateResetAfterSwitchOver()
Parameters   : None
Return type  : I_Void
Purpose      : Generate Reset on A-IF after switchover
Other Note   : Added For BSC HA 
 *******************************************************************************/
I_Void generateResetAfterSwitchOver()
{
   I_S32 res;
   AifInterfaceTableApi *aifTblPtr;
   LinkTableApi *linkTblPtr;
   LinkTableApi *tmplinkTblPtr;
   LinkStatusTableApi *linkStsTblPtr;
   LinkStatusTableIndices linkStsTblIndex;
   I_U32 outRows = 0, outRows1 = 0 , i =0;
   I_U16 outSize = 0, outSize1 = 0;
   I_U8 chasisFrameId = 0;
   I_U8 slotId = 0;
   LOG_PRINT(LOG_INFO,"Entering function: generateResetAfterSwitchOver");
 
   if ( ( res = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",res);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

   res = getallLinkTable(&linkTblPtr,&outRows1, &outSize1);
   if(res != CLIB_SUCCESS)
   {
       LOG_PRINT(DEBUG,"getallLinkTable ret err:%d",res);
       return;
   }

   for(i = 0 ; i < outRows1; i++)
   {
      tmplinkTblPtr = (LinkTableApi *)( (I_U8 *)linkTblPtr + i * outSize1);
      if( slotId == tmplinkTblPtr->cardNum)   
      {
         linkStsTblIndex.linksetID = tmplinkTblPtr->linksetID;
         linkStsTblIndex.linkId = tmplinkTblPtr->linkId;
         LOG_PRINT(DEBUG,"Link configured for this card : lsId:%d lnId:%d",
								linkStsTblIndex.linksetID,linkStsTblIndex.linkId)
         res = getLinkStatusTable(&linkStsTblIndex, &linkStsTblPtr);
         if(res == CLIB_SUCCESS)
         {
            if(linkStsTblPtr->oprState == ENABLED)
            {
                LOG_PRINT(DEBUG,"Link is UP for this card ");
                res = getallAifInterfaceTable(&aifTblPtr,&outRows, &outSize);
                if(res == CLIB_SUCCESS)
                {
                   LOG_PRINT(DEBUG,"getallAifInterfaceTable ret Aif OprState:%d",aifTblPtr->operationalState);
                   
                   if(aifTblPtr->operationalState == ENABLED)
                   {  
                      if(gAipSSPRcvd == FALSE)
                         {    
                          gSSAReceived = TRUE;
                          bssObjectHandlerForSSAllowed(); 
                         }
                      else
                         {
                          gSSAReceived = TRUE;
                          bssObjectHandlerForSSProhibit();
                         }
                   }
                   else
                   {
                      if(gAipSSPRcvd == FALSE)
                      {
                      LOG_PRINT(DEBUG,"Sending Unlock Request To Grhm After SO: In case SSA was rcvd on previous card");                  gSSAReceived = TRUE;
                      bssObjectHandlerForSSAllowed(); 
                      }
                   }
                   free(aifTblPtr);
                }
            } 
            free(linkStsTblPtr);
         }
      }
   }//for 
   free(linkTblPtr);

#if 0
   res = getallAifInterfaceTable(&aifTblPtr,&outRows, &outSize);
   if(res == CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"getallAifInterfaceTable ret Aif OprState:%d",aifTblPtr->operationalState);
      if(aifTblPtr->operationalState == ENABLED)
      {
         if(gAipSSPRcvd == FALSE)
         {    
            gSSAReceived = TRUE;
            bssObjectHandlerForSSAllowed(); 
         }  
         else if(gAipSSPRcvd == TRUE)
         {
            gSSAReceived = TRUE;
            bssObjectHandlerForSSProhibit();
         }
      }
      else if(aifTblPtr->operationalState == DISABLED)
      {
         if(gAipSSARcvd == TRUE) 
         {
            gSSAReceived = TRUE;
            bssObjectHandlerForSSAllowed(); 
         }
         else
         {
            gSSAReceived = FALSE;
         } 
      } 
      free(aifTblPtr);
   }
#endif  
   LOG_PRINT(LOG_INFO,"Exiting function: generateResetAfterSwitchOver");
}


/********************************* Function  Header*****************************
Function Name: sendCellEnableToCbsh()
Parameters   : None
Return type  : I_Void
Purpose      : Generate Reset on A-IF after switchover
Other Note   : Added For BSC HA 
 *******************************************************************************/
I_Void sendCellEnableToCbsh()
{
   I_S32 res;
   CellNonPerTableApi * cellNonPerTblPtr;
   CellNonPerTableApi * tmpPtr;
   I_U32 outRows =0 ;
   I_U16 outSize = 0, i =0;
 
   res = getallCellNonPerTable( &cellNonPerTblPtr, &outRows,&outSize); 

   if(res == CLIB_SUCCESS)
   {
      for(i =0 ; i< outRows; i++)
      {
         tmpPtr = (CellNonPerTableApi *)((I_U8 *)cellNonPerTblPtr + i*outSize );
         if(tmpPtr->oprState == ENABLED)
         {
            sendCellOprStateToCbsh(tmpPtr->cellId, tmpPtr->lac, CAUSE_CELL_ENABLED);   
            LOG_PRINT(DEBUG,"Cell Enabled sent for lac:%d, cellId:%d",tmpPtr->lac,tmpPtr->cellId);
         }
         else
         {
            LOG_PRINT(DEBUG,"Cell is Disabled for lac:%d, cellId:%d",tmpPtr->lac,tmpPtr->cellId);
         }
      }
      free(cellNonPerTblPtr);
   }
   else
   {
      LOG_PRINT(DEBUG,"No Row Found in CellNonPerTable res:%d", res);
   }
}
/********************************* Change History ***************************
   Release     Patch       Author         Description
   CS2                     Pratibha       Enum Removal Change
   BSC CS2.2       Kapil Tyagi     Changes for CS2.2
 ************************************** End *********************************/
