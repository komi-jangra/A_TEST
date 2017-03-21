/***********************************File Header ***************************
   File Name      : oamcfg_setmsghandler.c
Purpose        : Source file to define methods to Set Tables
Project        : BSC
Subsystem       : OAMS
Author         : Aricent Bangalore
CSCI ID        :
Version        :
 ************************************* End **********************************/
#include <oamscfg_includes.h>
#include <sysinst_hashdefs.h>
//#include <oamscfg_globals.h>

/********************************* Function  Header********************************
   Function Name:       bssLock()
Parameters:          void
Return type:         I_S32
Purpose:             Checks if BSS is Locked or Unlocked.
Returns 0, if Lock; otherwise 1 
Other Note:
 ************************************************************************************/
I_Bool bssLock()
{
   BssTableApi* bssTableApiPtr = PNULL;
   I_U32 i = 0;
   I_S32 ret = 1;
   I_U16 outSize;      
   /* Check if BSS Admin State is LOCK or not */    
   ret = getallBssTable( &bssTableApiPtr, &i, &outSize);

   /* Check if BSS Table is empty or not */
   if (PNULL == bssTableApiPtr)
   {
      LOG_PRINT(LOG_INFO,"No entry in BSS table");
      return(1);
   }

   /* Check if BSS is locked or not */
   if (UNLOCK == bssTableApiPtr->adminState)
   {
      free(bssTableApiPtr);
      LOG_PRINT(LOG_INFO,"Pre-Condition Failed- BSS Table is Unlocked");
      return(UNLOCK);
   }
   else
   {
      free(bssTableApiPtr);
      LOG_PRINT(LOG_INFO,"BSS Table is Locked");
      return(LOCK);
   }
} /* end of bssLock */


/********************************* Function  Header********************************
   Function Name:       setBssTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
For Locking BSS Object
For Unlocking BSS Object
For Modifying BSS Object parameters
Addition of BSS

Other Note:
 ************************************************************************************/
void setBssTableHandler()
{
   BssTableApi* receivedMsgPtr = ( BssTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   BssTableApi* bssTableApiPtr = PNULL;
   BssPsPreConfigTableApi* psPreConfigTablePtr = PNULL; /* Change For CS2.2 */
   I_Bool flagParamChange = FALSE;  /* Flag is Set if any attribute value in BSS Table is to be changed */
   I_Bool statusRange = FALSE;
   I_S32  ret = 1; 
   I_U32 rowsCount = 0;
   I_U16 outSize = 0;
   I_U16 count = 0;
   I_U32 outCount = 0;
   I_U8 iccId[MAX_ICC];
   I_U8 chasisId[MAX_ICC];
   I_U32 index = ZERO;


   LOG_PRINT(LOG_INFO,"In setBssTableHandler");

   ret = getallBssTable(&bssTableApiPtr, &rowsCount, &outSize);

   if(rowsCount > 1) 
   {
      LOG_PRINT(LOG_INFO,"More than one BSS table can not be present in DB");   
      cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      free(bssTableApiPtr);
      return;
   }
   /*There should be only one row in Bss Table..*/
   if(bssTableApiPtr != PNULL)
      if((receivedMsgPtr->bscId != bssTableApiPtr->bscId))
      {
         LOG_PRINT(LOG_INFO ,"There is already a row exist in Bss table "); 
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
         free(bssTableApiPtr);
         return; 
      }

    LOG_PRINT(DEBUG,"bssReset value:%d",receivedMsgPtr->bssReset);
      /*Check if the request if Request is for Reboot, 11-06-09::17:30 */
    if(bssTableApiPtr != PNULL)
    {
      if( 
          ( ACTIVE_ICC_CARD_RESET_CMD == receivedMsgPtr->bssReset ) 
                                   || 
          (STANDBY_ICC_CARD_RESET_CMD == receivedMsgPtr->bssReset ) 
        ) {
        if ( LOCK == bssTableApiPtr->adminState ) {
          bssResetReqHandler(receivedMsgPtr->bssReset);
        }
        else {
          LOG_PRINT(LOG_INFO ,"RESET Reject cause CM_ERR_OBJECT_NOT_LOCKED"); 
          cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);
        }
        free(bssTableApiPtr);
        return;
      }
      if(  (ACTIVE_ICC_CARD_SHUTDOWN_CMD == receivedMsgPtr->bssReset) 
                                   || 
           (STANDBY_ICC_CARD_SHUTDOWN_CMD == receivedMsgPtr->bssReset)  )
      {
        if ( LOCK == bssTableApiPtr->adminState ) 
        {
          bssResetReqHandler(receivedMsgPtr->bssReset);
        }
        else 
        {
          LOG_PRINT(LOG_INFO ,"SHUTDOWN Reject cause CM_ERR_OBJECT_NOT_LOCKED"); 
          cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);
        }
        free(bssTableApiPtr);
        return;
      }
    }
   /* Change For CS2.2 : Start */
   /* Checks if GPRS is enabled in Set BssTable request then 
    * BssPsPreConfigTable must be configured already */
   ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &rowsCount, &outSize);
   if((DBLIB_SUCCESS != ret) && (receivedMsgPtr->gprsEnabled == TRUE))
   {
      LOG_PRINT(LOG_MAJOR,"GPRS is Enabled in Received Request but \
            BssPsPreConfigTable is not configured at BSC");
      cfgSendNackToCm(CM_ERR_GPRS_NOT_ALLOWED);
      free(bssTableApiPtr);
      return;
   }
   else
   {
      free(psPreConfigTablePtr);
   }
   /* Change For CS2.2 : End */

   /* Case: BSS Lock and BSS Unlock */
   /* BSC CS 4.0 changes starts*/
   /* Abis E1 Lock\Unlock should not be in progress*/
   for(count = 0 ; count < CFG_MAX_NUM_E1 ; count++)
   {
      if(gE1Data[count].usageType == SYS_E1_USAGE_ABISIF )
      {
         if(gE1Data[count].e1State == lockInProgress)
         {
            LOG_PRINT(LOG_INFO,"setBssTableHandler : Abis E1 Lock in progress. Can not lock/unlock BSS. ");
            cfgSendNackToCm(CM_ERR_E1_LOCK_IN_PROGRESS);
          if(bssTableApiPtr != PNULL)
            free(bssTableApiPtr);
            return;
         }
         else if(gE1Data[count].e1State == unlockInProgress)
         {
            LOG_PRINT(LOG_INFO,"setBssTableHandler : Abis E1 Unlock in progress. Can not lock/unlock BSS. ");
            cfgSendNackToCm(CM_ERR_E1_UNLOCK_IN_PROGRESS);
           if(bssTableApiPtr != PNULL)
            free(bssTableApiPtr);
            return;
         }
      }
   }
   /* BSC CS 4.0 changes ends*/
   if ((bssTableApiPtr != PNULL) && (receivedMsgPtr->bscId == bssTableApiPtr->bscId) &&
         ((receivedMsgPtr->adminState != bssTableApiPtr->adminState)))
   {
      free(bssTableApiPtr);
      LOG_PRINT(LOG_INFO,"Calling bssObjectHandler");    
      /* gSSAReceived = FALSE; */   /* Fixed Mantis#2768 */
      bssObjectHandler();
      return; 
   }
   /* Fixed Mantis#2768 : Start */
   else if((bssTableApiPtr != PNULL) && (bssTableApiPtr->adminState == LOCK) && 
         (gBssState == unlockInProgress)) 
   {
      LOG_PRINT(LOG_INFO,"setBssTableHandler: Lock Request Received when Unlock is in Progess. Going to Lock BSS"); 
      free(bssTableApiPtr);
      bssObjectHandler();
      return;
   }
   /* Fixed Mantis#2768 : End */
   else if((bssTableApiPtr != PNULL) && (bssTableApiPtr->adminState == UNLOCK) && 
         (gBssState == lockInProgress)) 
   {
      LOG_PRINT(LOG_INFO,"setBssTableHandler: Unlock Request Received when Lock is in Progess. Sending Nack"); 
      free(bssTableApiPtr);
      cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
      return;
   }

   /* Addition of Row */
   if (PNULL == bssTableApiPtr)
   {
      LOG_PRINT(LOG_INFO,"setBssTableHandler: Addition of row in BSS Table");
      if(receivedMsgPtr->adminState == LOCKED)
      {
         statusRange = bssTableRangeChk(receivedMsgPtr);

         if (statusRange)
         {  
            LOG_PRINT(LOG_INFO,"setBssTableHandler: RangeChk passed, calling insertBssTable");
            ret = insertBssTable(receivedMsgPtr);
            if (ret == CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_INFO,"setBssTableHandler: new BSS added successfully, sending Ack");
               getDbBssTable();            
               gBssState = locked;
               gBssSubState = noneBssSubState;
	             gBssNcc = receivedMsgPtr->ncc;
               /*CS3.0 changes: Start */
               /*CS4.0 HA changes: Start */
              
               if (getIccIdChasisId( iccId, chasisId, &outCount ) != CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_CRITICAL,"getIccIdChasisId call is getting failed.."); 
                  return;
               }
               for( index = 0; index < outCount; index++ )
               { 
                  if (updateBscIdInSwMNodeTable(chasisId[index],iccId[index],0,receivedMsgPtr->bscId) != CLIB_SUCCESS)
                  {
                     LOG_PRINT(LOG_MAJOR,"setBssTableHandler: updateBssIdInSwMNodeTable Failed");
                  }
               }
               /*CS4.0 HA changes: End */
               /*CS3.0 changes: End */
               cfgSendAckToCm();
               return;
            }
            else
            {
               LOG_PRINT(LOG_INFO,"setBssTableHandlor: insertBssTable Failed, sending Nack");
               cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
               return;
            }
         }
         else
         {
            LOG_PRINT(LOG_INFO,"setBssTableHandler: RangeChk failed, sending Nack");  
            cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
            return; 
         } /* end of else of if (statusRange) */
      } /* end of if (AdminState) */
      else
      {
         LOG_PRINT(LOG_INFO,"setBssTableHandler: AdminState not Locked in received message, sending Nack");  
         cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         return; 
      } /* end of else of if (AdminState) */
   } /* end of Addition of Row */       

   /* Case: Modifying BSS Table */
   if (bssTableApiPtr != PNULL)
   {
      if((bssTableApiPtr->adminState == LOCK)) 
      {
         LOG_PRINT(LOG_INFO,"setBssTableHandler: Modifying BSS Table. Calling compare"); 
         flagParamChange = compareRcvdMsgAndDbEntry((void*) receivedMsgPtr,
               (void*) bssTableApiPtr, sizeof(BssTableApi));
         if (flagParamChange)
         {
            /* Bug Fixed - Manits #4996 : Start */
            /* Consistency Check - BcchArfcn+Bsic must be unique for a Neighbourhood */
	          if(receivedMsgPtr->ncc != gBssNcc)
            {
	             gBssNcc = receivedMsgPtr->ncc;
               statusRange = chkArfcnBsicForNccChange();
               if(TRUE == statusRange)
               {
                  /* bcchArfcn & BSIC is already configured */
                  LOG_PRINT(LOG_MAJOR,"setBssTableHandler : Consistency Check Failed - BcchArfcn+Bsic is Already Configured for Neighbours");
                  cfgSendNackToCm(CM_ERR_BSS_CONSIST_CHECK_FAILED);
                  free(bssTableApiPtr);    
                  return;
               }
            }
            /* Bug Fixed - Manits #4996 : End */

            /* Fixed Mantis #6033 : Start */
            if(FALSE == isCgiUnqInBss(receivedMsgPtr->mcc, receivedMsgPtr->mnc))
            {
               LOG_PRINT(LOG_MAJOR,"setBssTableHandler : Consistency Check Fail");
	             cfgSendNackToCm(CM_ERR_BSS_CONSIST_CHECK_FAILED);
               free(bssTableApiPtr);    
               return;
            } 
            /* Fixed Mantis #6033 : End */

            /* EGPRS Changes Starts */

            if ((FALSE == receivedMsgPtr->gprsEnabled) && (TRUE == receivedMsgPtr->egprsEnabled))

            {
              LOG_PRINT(LOG_MAJOR,"setBssTableHandler : Consistency Check Failed - Egprs Enabled : %d and Ps Enabled : %d in BssTable", receivedMsgPtr->egprsEnabled,receivedMsgPtr->gprsEnabled);
              cfgSendNackToCm(CM_ERR_BSS_CONSIST_CHECK_FAILED);
              free(bssTableApiPtr);
              return;
            }

            /* EGPRS Changes Ends */
                        

            statusRange = bssTableRangeChk(receivedMsgPtr);
            if (statusRange)
            {  
               LOG_PRINT(LOG_INFO,"setBssTableHandler: RangeChk passed, calling bssObjectHandler");
               bssObjectHandler();
               free(bssTableApiPtr);    
               return;     
            }
            else
            {
               LOG_PRINT(LOG_INFO,"setBssTableHandler: RangeChk failed, sending Nack");  
               cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
               free(bssTableApiPtr);    
               return;     
            } /* end of else of -if (statusRange) */
         }
         else
         {
            LOG_PRINT(LOG_INFO,"Same parameter values as in DB, Sending ack");  
            cfgSendAckToCm();
            free(bssTableApiPtr);    
            return;    
         } /*end of else of -if (flagParamChange) */ 
      } /*End of Case: Modifying BSS Table */
      else
      {
         if ((bssTableApiPtr->tWaitCellBlock != receivedMsgPtr->tWaitCellBlock) ||
             (bssTableApiPtr->tWaitTrxBlock != receivedMsgPtr->tWaitTrxBlock)) 
         {
               /* Range Check */  
               if ((receivedMsgPtr->tWaitCellBlock < 30) || (receivedMsgPtr->tWaitCellBlock > 1800))
               {
                  LOG_PRINT(LOG_DEBUG," bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
                  cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
                  free(bssTableApiPtr);    
                  return;
               }
               if ((receivedMsgPtr->tWaitTrxBlock < 30) || (receivedMsgPtr->tWaitTrxBlock > 1800))
               {
                  LOG_PRINT(LOG_DEBUG," bssTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
                  cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
                  free(bssTableApiPtr);    
                  return;
               }
               /* Update Bss Table */
               bssTableApiPtr->tWaitTrxBlock = receivedMsgPtr->tWaitTrxBlock ;
               bssTableApiPtr->tWaitCellBlock = receivedMsgPtr->tWaitCellBlock ;
               if ( (updateBssTable(bssTableApiPtr))!=CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_INFO,"DB Failure");
                  cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
                  free(bssTableApiPtr);    
               }
               else
               {
                  cfgSendAckToCm();
                  free(bssTableApiPtr);    
               } 
          } 
          else
          {
             free(bssTableApiPtr);
             LOG_PRINT(LOG_INFO," Bss AdminState Unlocked in DB & recvd param, sending Nack");      
             // Mantis 7217
             //cfgSendNackToCm(CM_ERR_OBJ_ALREADY_UNLOCKED); /* Case: Abnormal Condition Handling */
      
             //Mantis 15571
             cfgSendAckToCm();
          } 
          return; 
      }/*End of else */
   }
}/* end of setBssTableHandler */


/********************************* Function  Header********************************
   Function Name:       setCellTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
For Locking Cell Object
For Unlocking Cell Object
For Modifying Cell Object parameters
Addition of Cell

Other Note:
 ************************************************************************************/
void setCellTableHandler()
{
   CellPerTableApi* receivedMsgPtr = ( CellPerTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   CellPerTableApi* cellTableApiPtr = PNULL;
   CellPerTableApi* tempCellTablePtr = PNULL; 
   CellPerTableIndices apiCellIndex;       
   CellPerTableSecIndices apiCellSecIndex;
   CellNonPerTableApi cellNonPerBuff;
   memset(&cellNonPerBuff,0,sizeof(CellNonPerTableApi)); 
   I_Bool flagParamChange = FALSE;  /* Set if any field value in Cell Table is changed */
   I_Bool statusRange = FALSE;
   I_S32  ret = 0; 
   I_U32 rowsCount = 0;
   I_U32 outSz = 0;
   I_U16 outSize;
   I_U8 index;
   I_U16 cellArrayIndex=0;  
   /* Bug Fix - Mantis#4683 : Start */
   ChnGrpTableApi *chnGrpTableApiPtr = NULL;
   ChnGrpTableApi *tmpChnGrpTablePtr = NULL;
   I_U32 i = ZERO;
   /* Bug Fix - Mantis#4683 : End */
   ArfcnListTableIndices arfcnTableInd;
   ArfcnListTableApi*    arfcnTableApiPtr = NULL;
   I_U32 *e1Id = NULL;
   I_U32 count = 0;
   /* Mantis 15944 starts                        */
   I_U8 psAlowedInTable = PS_NOT_ALLOWED; 
   /* Mantis 15944 ends                        */
   LOG_PRINT(LOG_INFO,"In setCellTableHandler");
   LOG_PRINT(LOG_INFO,"cellId = %u, lac = %u",receivedMsgPtr->cellId, receivedMsgPtr->lac );

   apiCellIndex.cellId =  receivedMsgPtr->cellId;
   apiCellIndex.lac = receivedMsgPtr->lac;
   
   /*Changes PCU R2.5 Aricent -- START*/
   BssPsPreConfigTableApi* psPreConfigTablePtr = NULL;
   /*Changes PCU R2.5 Aricent -- END*/

   ret = getCellPerTable(&apiCellIndex, &cellTableApiPtr);
   /* Case: Addition of Cell in Cell Table */
   if (cellTableApiPtr == PNULL)
   {
      I_U16 instCount = ZERO;

      LOG_PRINT(LOG_INFO,"setcellTableHandler: Addition of Cell, Calling RangeChk"); 
      /*Check Maxmimum No Of Cell resources supported */
      if (INST_SUCCESS != GetInstCount(ENT_OAMS_CELLH, CELLHM_HANDLER, &instCount)) {
         LOG_PRINT(LOG_INFO,"[%s] GetInstCount call failed",__func__);
         cfgSendNackToCm(CM_ERR_DB_FAILED);
         return ;
      }   

      /* Fixed Mantis #4188 : Start */
      /* Change For CS2.2 : Start */
      /* Check that Maximum allowed cells are already added or not */
      ret = getallCellPerTable(&cellTableApiPtr, &rowsCount, &outSize);
      //if((DBLIB_SUCCESS == ret) && (rowsCount >= gMaxCellsNum))
      if((DBLIB_SUCCESS == ret) && (rowsCount >= instCount))
      {
         LOG_PRINT(LOG_MAJOR,"setcellTableHandler : Max Entry in CellTable Already Exists");
         free(cellTableApiPtr);
         cfgSendNackToCm(CM_ERR_MAX_NUM_CELL_EXCEED);
         //cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
         return;
      }
      else if(DBLIB_SUCCESS == ret)
      {
         free(cellTableApiPtr);
      }
      /* Change For CS2.2 : End */
      /* Fixed Mantis #4188 : End */
   /* Mantis 15944 starts                        */
      psAlowedInTable =  PS_NOT_ALLOWED;
   /* Mantis 15944 ends                        */
      apiCellSecIndex.antennaId = receivedMsgPtr->antennaId;
      ret = clib_get(SCM_DAO_CELLPERTABLE, SCM_MET_GET_SEC_CELLPERTABLE, (I_PVoid)&apiCellSecIndex,
             sizeof(CellPerTableSecIndices), (I_PVoid)&tempCellTablePtr, &outSize , &rowsCount);
      if(DBLIB_SUCCESS == ret)
      {
        LOG_PRINT(LOG_MAJOR,"setcellTableHandler : AntennaId already present in another cell");
        free(tempCellTablePtr);
        cfgSendNackToCm(CM_ERR_ANTENNA_ID_IN_CELL_ALREADY_EXIST);
        return;
      }
      else
      {
        free(tempCellTablePtr);
      }
      /* Consistency Check whether bcchArfcn is present in ArfcnListTable or not */
      arfcnTableInd.band = receivedMsgPtr->freqBandBcch;
      arfcnTableInd.arfcn = receivedMsgPtr->bcchArfcn;
      ret = getArfcnListTable(&arfcnTableInd, &arfcnTableApiPtr);
      if(ret == DBLIB_SUCCESS)
      {
         free(arfcnTableApiPtr);
      }
      else
      {
         /* bcchArfcn in Received request is not present in ArfcnListTable */
         LOG_PRINT(LOG_MAJOR,"setCellTableHandler : Consistency Check Failed - bcchArfcn : %d is Not Present in ArfcnListTable", receivedMsgPtr->bcchArfcn);
         cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
         return;
      }

      /* Fixed Mantis #6033 : Start */
      if(FALSE == isCgiUnqInExtAndIntCellTable(receivedMsgPtr, INTERNAL))
      {
         LOG_PRINT(LOG_MAJOR,"setCellTableHandler : Consistency Check Fail");
	       cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
	       return;
      } 
      /* Fixed Mantis #6033 : End */

/*Changes PCU R2.5 Aricent -- START*/
     if (PS_ALLOWED == receivedMsgPtr->psAllowed)
     {
         ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &rowsCount, &outSize);
         if(DBLIB_SUCCESS == ret && ZERO < rowsCount)
         {
            free(psPreConfigTablePtr);
         }
         else
         {
            LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC, Error Code = [%d] sending Nack", ret);
            cfgSendNackToCm(CM_ERR_GPRS_NOT_ALLOWED);
            return;
         }
     }
            /* EGPRS Changes Starts */

            if ((PS_NOT_ALLOWED == receivedMsgPtr->psAllowed) && (EGPRS_ALLOWED == receivedMsgPtr->egprsAllowed))            {
              LOG_PRINT(LOG_MAJOR,"setCellTableHandler : Consistency Check Failed - Egprs Allowed : %d and Ps Allowed : %d in CellTable", receivedMsgPtr->egprsAllowed,receivedMsgPtr->psAllowed);              
              cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
              return;
            }

            /* EGPRS Changes Ends */
/*Changes PCU R2.5 Aricent -- END*/
      if (receivedMsgPtr->adminState == LOCKED)
      {
         statusRange = cellTableRangeChk(receivedMsgPtr);
         if(!statusRange)
         {
            LOG_PRINT(LOG_INFO,"setCellTableHandler: Out of Range Value, sending Nack");
            cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
            return;
         }

         ret = getallCellPerTable(&tempCellTablePtr, &rowsCount, &outSize);

	       if(ret == DBLIB_SUCCESS)
	          free(tempCellTablePtr);

         if (rowsCount < CFG_MAX_NUM_CELLS)
         {
            /* Fixed Mantis #4052 : Start */
            ret = insertCellPerTable(receivedMsgPtr ); 
            if (ret == CLIB_SUCCESS)
            { 
               /*  Adding row to Non per Cell Table */ 
              
               /*MANTIS 16723 CHANGES STARTS*/
	             initCellDataStruct(receivedMsgPtr->cellId, receivedMsgPtr->lac,&cellArrayIndex);
               cellNonPerBuff.cellId =  receivedMsgPtr->cellId;    
               cellNonPerBuff.lac =  receivedMsgPtr->lac;   
               cellNonPerBuff.cellIndex = cellArrayIndex;
	             ret = insertCellNonPerTable(&cellNonPerBuff);
            }
            /*MANTIS 16723 CHANGES ENDS*/
            /* Fixed Mantis #4052 : End */
         
            if (ret == CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_INFO,"setCellTableHandler: new Cell added successfully, sending Ack");
	       /* Fixed Mantis #4249 : Start */
               /* cfgCellObjectHandlerInit(); */
	       /* Fixed Mantis #4249 : End */

               cfgSendAckToCm();
              /* KPI PHASE-II Changes Starts*/
             /* Calling function as newly added Cell will be in Disabled State*/
               updateRadioNwAvlbltyTblAtCellDisable(receivedMsgPtr->cellId,
               (I_U32)(receivedMsgPtr->lac));
             /* KPI PHASE-II Changes Ends*/
                /* Mantis 15944 starts                        */
              if ( (PS_NOT_ALLOWED == psAlowedInTable) && (PS_ALLOWED == receivedMsgPtr->psAllowed )) 
              {
                updateDataAvlbltyTblAtPsCellDisable(receivedMsgPtr->cellId,
                (I_U32)(receivedMsgPtr->lac));//adding a new entry in table 
              }
              
                /* Mantis 15944 ends                        */
               return;     
            }
            else
            {
               LOG_PRINT(LOG_INFO,"setCellTableHandler: insertCellTable Failed, sending Nack");
               cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
               resetCellDataStruct(receivedMsgPtr->cellId, receivedMsgPtr->lac);//MANTIS 16723 CHANGES
               return;     
            } 
         } 
         else
         {
            LOG_PRINT(LOG_INFO,"setCellTableHandler: status check failed or max row exceeded in Cell table, sending Nack");
            cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
            return;
         }
      }
      else
      {
         LOG_PRINT(LOG_INFO,"setCellTableHandler: AdminState not Locked in received message, sending Nack");  
         cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         return; 
      } /* end of else of if (AdminState) */   
   }  

   index = getCellDataState();

   switch (gCellData[index].CellState)
   {
      case unlockOrEnableInProgress:
         LOG_PRINT(LOG_DEBUG,"Request can not be proceed as CELL is in Unlock In  Progress");
         cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
	 return;
         break;
      case lockeOrDisableInProgress:
         LOG_PRINT(LOG_DEBUG,"Request can not be proceed as CELL is in Lock In  Progress");
         cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
	 return;
         break;
      default:
         break;
   }


   /* Case: Cell Lock and Cell Unlock */
   if ((cellTableApiPtr != PNULL) && ((receivedMsgPtr->adminState != cellTableApiPtr->adminState)))
   {
      free(cellTableApiPtr);
                  /*Changes for CS4.0 : Abis E1 Lock/Unlock Start*/
      /* Abis E1 Lock\Unlock should not be in progress*/
      LOG_PRINT(LOG_INFO,"setCellTableHandler: Lock/Unlock Request for Lac Id [%d], CellId[%d]", receivedMsgPtr->lac, receivedMsgPtr->cellId );
      if(getE1ForCell(receivedMsgPtr->lac,receivedMsgPtr->cellId, &e1Id, &outSz) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"setCellTableHandler: E1's for this Cell Not found. ");   
      }
      
      if(outSz != 0)
      {
         LOG_PRINT(LOG_DEBUG,"setCellTableHandler: Total E1d Found [%d]", outSz );
         for(count = 0 ; count < outSz ; count++)
         {
            LOG_PRINT(LOG_DEBUG,"setCellTableHandler: E1d [%d] Found for Id Lac Id [%d], CellId[%d]", e1Id[count], receivedMsgPtr->lac, receivedMsgPtr->cellId );
            if(gE1Data[e1Id[count]].e1State == lockInProgress)
            {
               LOG_PRINT(LOG_CRITICAL,"setCellTableHandler: e1 lock in progress. Can not Lock/Unlock this Cell ");
               cfgSendNackToCm(CM_ERR_E1_LOCK_IN_PROGRESS);
               free(e1Id);
               return;
            }
            else if(gE1Data[e1Id[count]].e1State == unlockInProgress)
            {
               LOG_PRINT(LOG_CRITICAL,"setCellTableHandler: e1 unlock in progress. Can not Lock/Unlock this Cell ");
               cfgSendNackToCm(CM_ERR_E1_UNLOCK_IN_PROGRESS);
               free(e1Id);
               return;
         
            }
         }
         free(e1Id);
      }
      else 
      {
         if(e1Id != NULL)
         {
            free(e1Id);
         } 
      } 

       /*Changes for CS4.0 : Abis E1 Lock/Unlock Ends*/
      LOG_PRINT(LOG_INFO,"setCellTableHandler: calling cellObjectHandler");
      cellObjectHandler();
      
      return;     
   }

   /*Changes for cell lock allowed during cell block in progress*/
   if( gCellData[index].CellState ==  blockInProgress)
   {
       LOG_PRINT(LOG_DEBUG,"Request can not be proceed as CELL is in ShutDown In  Progress");
       cfgSendNackToCm(CM_ERR_SHUTDOWN_IN_PROGRESS);
	     return;
   }

   if (cellTableApiPtr != PNULL)
   {
      /* Case: Modifying Cell Table */
/*Changes R2.5.2: START*/
    /*  if (cellTableApiPtr->adminState == LOCK) 
      {*/
/*Changes R2.5.2: END*/
         LOG_PRINT(LOG_INFO,"setCellTableHandler: Modifying Cell Table. Calling compare");
         flagParamChange = compareRcvdMsgAndDbEntry((void*) receivedMsgPtr,
               (void*) cellTableApiPtr,
               sizeof(CellPerTableApi));
         if (flagParamChange)
         {
              apiCellSecIndex.antennaId = receivedMsgPtr->antennaId;
              ret = clib_get(SCM_DAO_CELLPERTABLE, SCM_MET_GET_SEC_CELLPERTABLE, (I_PVoid)&apiCellSecIndex,
                    sizeof(CellPerTableSecIndices), (I_PVoid)&tempCellTablePtr, &outSize , &rowsCount);
              if((DBLIB_SUCCESS == ret) && (!( (tempCellTablePtr->cellId == receivedMsgPtr->cellId) && 
                                               (tempCellTablePtr->lac == receivedMsgPtr->lac)) ))
              {
                LOG_PRINT(LOG_MAJOR,"setcellTableHandler : AntennaId already present in another cell");
                free(tempCellTablePtr);
                cfgSendNackToCm(CM_ERR_ANTENNA_ID_IN_CELL_ALREADY_EXIST);
                return;
              }
              else
              {
                free(tempCellTablePtr);
              }
              /* Mantis 15944 starts                        */
              psAlowedInTable = cellTableApiPtr->psAllowed;
              if ( (PS_ALLOWED == psAlowedInTable) && (PS_NOT_ALLOWED == receivedMsgPtr->psAllowed ))
              {
                updateDataAvlbltyTblAtPsCellEnableUnbarred(receivedMsgPtr->cellId,
                (I_U32)(receivedMsgPtr->lac)); //closing the entry 
              }
              else if ( (PS_NOT_ALLOWED == psAlowedInTable) && (PS_ALLOWED == receivedMsgPtr->psAllowed )) 
              {
                LOG_PRINT(LOG_INFO,"adding entry to the table for cellId = %d lac= %d" ,receivedMsgPtr->cellId, receivedMsgPtr->lac);
                LOG_PRINT(LOG_INFO,"adding entry to the table psAlowedInTable = %d , receivedMsgPtr->psAllowed =%d",psAlowedInTable, receivedMsgPtr->psAllowed );
                updateDataAvlbltyTblAtPsCellDisable(receivedMsgPtr->cellId,
                (I_U32)(receivedMsgPtr->lac));//adding a new entry in table 
              }
              /* Mantis 15944 ends                        */
         
         LOG_PRINT(LOG_INFO,"Modifying Cell Table. Calling RangeChk");
	    /* Fixed Manits #5384 : Start */
	    gLacOfRcvReq    = receivedMsgPtr->lac;
	    gCellIdOfRcvReq = receivedMsgPtr->cellId;
	    /* Fixed Manits #5384 : End */
	    /* Bug Fix - Mantis#4683 : Start */
	    /* Consistency Check maxTxPwr in ChnGrpTable <= bcchPwr in CellPerTable */
  	    ret = getAllChnGrpForCellH(receivedMsgPtr->cellId, receivedMsgPtr->lac,
					&chnGrpTableApiPtr, &rowsCount, &outSize);
	    if(DBLIB_SUCCESS == ret)
	    {
	       /* ChnGrp is Present for receivd cellId & lac. Performing consistency check
		* maxTxPwr in ChnGrpTable <= bcchPwr in CellPerTable */
	       for(i = 0; i < rowsCount; i++)
	       {
		  tmpChnGrpTablePtr = (ChnGrpTableApi *)(((I_U8 *)(chnGrpTableApiPtr)) + (i * outSize));
		  if((tmpChnGrpTablePtr->maxTxPwr) > (receivedMsgPtr->bcchPwr))
		  {
		     LOG_PRINT(LOG_MAJOR,"setCellTableHandler : Consistency Check Failed - maxTxPwr in ChnGrpTable <= bcchPwr in CellPerTable");
		     free(chnGrpTableApiPtr);
		     free(cellTableApiPtr);
		     cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
		     return;
		  }
	       }
	       free(chnGrpTableApiPtr);
	    }
 	    /* Bug Fix - Mantis#4683 : End */

	    /* Consistency Check whether bcchArfcn is present in ArfcnListTable or not */
            arfcnTableInd.band = receivedMsgPtr->freqBandBcch;
            arfcnTableInd.arfcn = receivedMsgPtr->bcchArfcn;
	    ret = getArfcnListTable(&arfcnTableInd, &arfcnTableApiPtr);
	    if(ret == DBLIB_SUCCESS)
	    {
	       free(arfcnTableApiPtr);
	    }
	    else
	    {
	       /* bcchArfcn in Received request is not present in ArfcnListTable */
	       LOG_PRINT(LOG_MAJOR,"setCellTableHandler : Consistency Check Failed - bcchArfcn : %d is Not Present in ArfcnListTable", receivedMsgPtr->freqBandBcch);
               free(cellTableApiPtr);
	       cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
	       return;
 	    }

            /* Bug Fixed - Manits #4996 : Start */
            /* Consistency Check - BcchArfcn+Bsic must be unique for a Neighbourhood */
            statusRange = isArfcnBsicFoundInNeighTable(receivedMsgPtr, ZERO, FALSE);
	    gLacOfRcvReq    = ZERO;
	    gCellIdOfRcvReq = ZERO;
            if(TRUE == statusRange)
            {
               /* bcchArfcn & BSIC is already configured */
               LOG_PRINT(LOG_MAJOR,"setCellTableHandler : Consistency Check Failed - BcchArfcn+Bsic is Already Configured for Neighbours");
               cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
               free(cellTableApiPtr);
               return;
            }
            /* Bug Fixed - Manits #4996 : End */
/*Changes PCU R2.5 Aricent -- START*/
            if (PS_ALLOWED == receivedMsgPtr->psAllowed)
            {
               ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &rowsCount, &outSize);
               if(DBLIB_SUCCESS == ret && 0 < rowsCount)
               {
                  free(psPreConfigTablePtr);
               }
               else
               {
                  LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC Error Code = [%d] , Sending Nack", ret);
                  cfgSendNackToCm(CM_ERR_GPRS_NOT_ALLOWED);
                  free(cellTableApiPtr);
                  return;
               }
            }
/*Changes PCU R2.5 Aricent -- END*/


            /* EGPRS Changes Starts */

            if ((PS_NOT_ALLOWED == receivedMsgPtr->psAllowed) && (EGPRS_ALLOWED == receivedMsgPtr->egprsAllowed))            {
              LOG_PRINT(LOG_MAJOR,"setCellTableHandler : Consistency Check Failed - Egprs Allowed : %d and Ps Allowed : %d in CellTable", receivedMsgPtr->egprsAllowed,receivedMsgPtr->psAllowed);               free(cellTableApiPtr);
              cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
              return;
            }

            /* EGPRS Changes Ends */

            statusRange = cellTableRangeChk(receivedMsgPtr);
            free(cellTableApiPtr);

            if (statusRange)
            {  
               LOG_PRINT(LOG_INFO,"setCellTableHandler: RangeChk passed, calling cellObjectHandler");
               cellObjectHandler();
               return;    
            } /* End of - if (statusRange) */
            else
            {
               LOG_PRINT(LOG_INFO,"setCellTableHandler: RangeChk failed, sending Nack");
               cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
               return;    
            }
         } /* End of - if (flagParamChange) */       
         else
         {
            LOG_PRINT(LOG_INFO,"setCellTableHandler: Same parameter values in DB, sending Ack");
            free(cellTableApiPtr);
            cfgSendAckToCm();
            return;    
         } /* End of - if (cellTableApiPtr != PNULL) */         
/*Changes R2.5.2: START*/
      /*}
      else
      {
         free(cellTableApiPtr);
         LOG_PRINT(LOG_INFO,"setCellTableHandler: Cell AdminState Unlocked in DB & recvd param, sending Nack");    
         // Mantis 7217
         cfgSendNackToCm(CM_ERR_OBJ_ALREADY_UNLOCKED);  //Case: Abnormal Condition Handling 
         return;
      }*/ 
/*Changes R2.5.2: END*/
   }  
}/* end of setCellTableHandler */


/********************************* Function  Header********************************
   Function Name:       setE1TableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
For Locking E1 Object
For Unlocking E1 Object
Other Note:
 ************************************************************************************/
void setE1TableHandler()
{
   TrunkTableApi* receivedMsgPtr = ( TrunkTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   TrunkTableApi* e1TableApiPtr = PNULL;
   NsvcTableApi * nsvcTableApiAllPtr = PNULL;
   NsvcTableApi * nsvcTableApiPtr = PNULL;
   TrunkPortTableApi     *TrunkPortTableApiDbPtr   = NULL;
   TrunkPortTableApi     *TrunkPortTableApiDbTmpPtr= NULL;
   TrunkTableIndices apiE1Index ={0} ;
   I_U32 rowCount = 0;
   I_U32 index = 0;
   I_U16 rowSize = 0;
   I_S32  ret = 1; 
   I_U32 *tmpTs = NULL;
   I_U32 recCount = 0;
	 I_U32 outRows  = 0;
 	 I_U16 outSize  = 0;
	 I_U32 i = 0;

   LOG_PRINT(LOG_INFO,"In setE1TableHandler");
   apiE1Index.e1Num = receivedMsgPtr->e1Num;

   //Mantis -8719 only one trunkport operation must be allowed
	if(getallTrunkPortTable(&TrunkPortTableApiDbPtr,&outRows, &outSize) !=CLIB_SUCCESS) {
			  LOG_PRINT(LOG_INFO,"setE1TableHandler :getallTrunkPortTable failed");
			  cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
           return;
	}
   else {
	      LOG_PRINT(LOG_INFO," setE1TableHandler :getallTrunkPortTable success");
    	   for (i=0; i < outRows; i++) {
			   TrunkPortTableApiDbTmpPtr = (TrunkPortTableApi *) (((I_U8 *)TrunkPortTableApiDbPtr + i*outSize));
			   if ((receivedMsgPtr->trunkPortId != TrunkPortTableApiDbTmpPtr->trunkPortId) && 
					((gE1Data[TrunkPortTableApiDbTmpPtr->trunkPortId].e1State == lockInProgress) || 
					(gE1Data[TrunkPortTableApiDbTmpPtr->trunkPortId].e1State == unlockInProgress)||
					(gE1Data[TrunkPortTableApiDbTmpPtr->trunkPortId].trunkState == EnableInProgress) ||
					(gE1Data[TrunkPortTableApiDbTmpPtr->trunkPortId].trunkState == DisableInProgress)))
					{
							  LOG_PRINT(LOG_INFO,"Simultaneous procedure on more than one trunkport are not allowed");
							  free(TrunkPortTableApiDbPtr);
							  cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
							  return;
					}
	       }
			  free(TrunkPortTableApiDbPtr);

     	}
	//End

   ret = getTrunkTable(&apiE1Index, &e1TableApiPtr);

   /* Check if received entry is in Db or not */ 
   if ( ret != CLIB_SUCCESS || PNULL == e1TableApiPtr)
   {
      LOG_PRINT(LOG_INFO,"No Entry in E1 table for the received E1num");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }

   // CS4.0 Create Map/Delete Map

   // Check if RO parameters added in CS4.0 are being modified
   if( e1TableApiPtr->e1Category != receivedMsgPtr->e1Category ) 
   {
      LOG_PRINT(LOG_INFO,"setE1TableHandler:Modification of E1 Cataegory not allowed");
      cfgSendNackToCm(CM_ERR_E1_INVALID_REQUEST);
      free(e1TableApiPtr);
      return;
   }

   if( e1TableApiPtr->usageType != receivedMsgPtr->usageType ) 
   {
      LOG_PRINT(LOG_INFO,"E1 parameter modification is not allowed, Sending Nack");
      LOG_PRINT(DEBUG,"Rcvd usageType is:%d while current UsageType is :%d for e1:%d",
           receivedMsgPtr->usageType,e1TableApiPtr->usageType,receivedMsgPtr->e1Num);
      free(e1TableApiPtr);   
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      return;
   }

   // Check if the request is to Create & Delete Map only
   if( e1TableApiPtr->usageType == receivedMsgPtr->usageType && \
       (receivedMsgPtr->adminState == e1TableApiPtr->adminState) && ( receivedMsgPtr->mapAction != DEFAULT_ACTION ) )
   {
      // Mantis 6742
      if( gE1Data[receivedMsgPtr->e1Num].e1State == unlockInProgress )
      {
         LOG_PRINT(LOG_CRITICAL,"CreateMap/DeleteMap: E1 in unlock in progress state, sending NACK");
         cfgSendNackToCm(CM_ERR_E1_UNLOCK_IN_PROGRESS);
         free(e1TableApiPtr);
         return;
      }
      if( gE1Data[receivedMsgPtr->e1Num].e1State == lockInProgress )
      {
         LOG_PRINT(LOG_CRITICAL,"CreateMap/DeleteMap: E1 in lock in progress state, sending NACK");
         cfgSendNackToCm(CM_ERR_E1_LOCK_IN_PROGRESS);
         free(e1TableApiPtr);
         return;
      }
      if( receivedMsgPtr->adminState == UNLOCKED )
      {
         LOG_PRINT(LOG_CRITICAL,"CreateMap/DeleteMap: E1 in unlocked state, sending NACK");
         cfgSendNackToCm(CM_ERR_E1_IN_UNLOCKED_STATE);
         free(e1TableApiPtr);
         return;
      }

      // Add code to create or delete mapping here
      E1TrunkMap( receivedMsgPtr, e1TableApiPtr ); 
      free(e1TableApiPtr);
      
   }
   else if( ( ( e1TableApiPtr->usageType != receivedMsgPtr->usageType) || \
              (receivedMsgPtr->adminState != e1TableApiPtr->adminState) || (receivedMsgPtr->trunkPortId != e1TableApiPtr->trunkPortId ) ) && ( receivedMsgPtr->mapAction != DEFAULT_ACTION ) )
   {
      LOG_PRINT(LOG_INFO,"setE1TableHandler: mapAction Set:: Modification of other RW parameters not allowed");
      cfgSendNackToCm(CM_ERR_E1_INVALID_REQUEST);
      free(e1TableApiPtr);
      return;
   } // CS4.0 Create Map/Delete Map
   else // Proceed with the E1 Lock/Unlock procedure :: Else Added for Create/Delete Map
   {

      /* Mantis 7005 
      // Check if E1 is external Trunk Port & is in DISABLED state
      if( receivedMsgPtr->e1Category == EXTERNAL_E1 && ( gE1Data[receivedMsgPtr->e1Num].trunkState == Disabled\
           || gE1Data[receivedMsgPtr->e1Num].trunkState == DisableInProgress ) )
      {
         LOG_PRINT(LOG_INFO," setE1TableHandler: Trunk Port in Disabled State");
         cfgSendNackToCm(CM_ERR_TRUNKPORT_DISABLED);
         return;
      }
      */

     
   /* Case: E1 Lock and E1 Unlock */
   if ((e1TableApiPtr != PNULL) && 
         ((receivedMsgPtr->adminState != e1TableApiPtr->adminState)))
   {
      LOG_PRINT(LOG_INFO,"setE1TableHandler: calling e1ObjectHandler");
      free(e1TableApiPtr);
      /* Fixed Manits #3833 : Start */
      if((receivedMsgPtr->adminState != LOCK) &&
         (receivedMsgPtr->adminState != UNLOCK)
        )
      {
         LOG_PRINT(LOG_DEBUG,"setE1TableHandler : Received Wrong adminState value from Operator : %d",
                                                        receivedMsgPtr->adminState);         
	      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;
      }
      /* Fixed Manits #3833 : End */
   
      /*Fix Mantis Id 9720 Starts*/
      if(e1TableApiPtr->usageType  == SYS_E1_USAGE_NONE )
      {
         LOG_PRINT(LOG_DEBUG,"setE1TableHandler : Received Lock/Unlock for E1 usage type free");
                                                        
	      cfgSendNackToCm(CM_ERR_E1_INVALID_REQUEST);
         return;
      } 
      /*Changes PCU R2.5 Aricent --START*/
      /* if NSVCs for this E1 is lockinProgress or unlockInProgress 
       * send Nack
       */
      getNsvcsForE1Id(receivedMsgPtr->e1Num, &nsvcTableApiAllPtr, &rowCount, &rowSize);
      for(i = 0; i < rowCount; i++)
      {
         nsvcTableApiPtr = (NsvcTableApi *) (((char *) nsvcTableApiAllPtr ) + (rowSize * i));
         index = getNsvcDataStruct(nsvcTableApiPtr->nsvcId);
         if (lockeOrDisableInProgress == gNsvcData[index].nsvcState) 
         {
            LOG_PRINT(LOG_CRITICAL,"NSVC [%u] in lock in progress state, sending NACK", nsvcTableApiPtr->nsvcId);
            cfgSendNackToCm(CM_ERR_NSVC_LOCK_IN_PROGRESS);

         }
         else if (unlockOrEnableInProgress == gNsvcData[index].nsvcState) 
         {
            LOG_PRINT(LOG_CRITICAL,"NSVC [%u] in Unlock in progress state, sending NACK", nsvcTableApiPtr->nsvcId);
            cfgSendNackToCm(CM_ERR_NSVC_UNLOCK_IN_PROGRESS);
         }
      } /* End of for */
      free(nsvcTableApiAllPtr);
      /*Changes PCU R2.5 Aricent -- END*/

      /* Fixed Manits #3833 : End */
      e1ObjectHandler();
      return;   
   } /* End of Case: E1 Lock and E1 Unlock */
   /*Mantis 6013 Fix- Gaurav Bhatnagar*/
   if(gE1Data[receivedMsgPtr->e1Num].e1State == unlockInProgress )
   {
      LOG_PRINT(LOG_INFO,"setE1TableHandler: E1 Unlock is in Progress. Can not process the request for e1Id:: %d" , receivedMsgPtr->e1Num);
      cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
   /*Mantis 6584 Fix- Gaurav Bhatnagar*/
      free(e1TableApiPtr);
      return;
      
   }
   if(gE1Data[receivedMsgPtr->e1Num].e1State == lockInProgress )
   {
      LOG_PRINT(LOG_INFO,"setE1TableHandler: E1 Lock is in Progress. Can not process the request for e1Id:: %d" , receivedMsgPtr->e1Num);
      cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
   /*Mantis 6584 Fix- Gaurav Bhatnagar*/
      free(e1TableApiPtr);
      return;
      
   }
   /* Case: Modify E1 Table */

  #if 0
   /*Mantis 6271- Fixed*/
   if((SYS_E1_USAGE_ABISIF_INFRAME == e1TableApiPtr->usageType) ||
         (SYS_E1_USAGE_AIF == e1TableApiPtr->usageType) ||
         (SYS_E1_USAGE_AIF == receivedMsgPtr->usageType) ||
         (receivedMsgPtr->usingEntity != e1TableApiPtr->usingEntity)
      )
   {
      LOG_PRINT(LOG_INFO,"E1 parameter modification is not allowed, Sending Nack");
      free(e1TableApiPtr);   
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      return;
   }
   else
   {
   #endif  
      /*Mantis 6585: Fixed*/
      if( receivedMsgPtr->usageType == e1TableApiPtr->usageType)
      {
         LOG_PRINT(LOG_INFO,"Usage type is same in Received Message and DB. Nothing to modified. Sending Ack");
         #if 0
         /*Mantis Fix : 11195 starts*/
         if( receivedMsgPtr->adminState == UNLOCKED)
           cfgSendNackToCm(CM_ERR_OBJ_ALREADY_UNLOCKED);
         else 
           cfgSendNackToCm(CM_ERR_OBJ_ALREADY_LOCKED);
         /*Mantis Fix : 11195 Ends*/
         #endif
         /*Mantis fix : 0015378 start*/
         cfgSendAckToCm();
         /*Mantis fix : 0015378 end*/
         free(e1TableApiPtr);
         return;
      }
      /* Check that All timeslots in E1 are in Unlocked state */
      ret = getE1LockedTimeslot(e1TableApiPtr->e1Num, LOCKED, &tmpTs, &recCount);
      if(ret == DBLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"E1 of ABISIF* Type has Locked Timeslots. Rejecting E1 Update Request");
         free(tmpTs);
         free(e1TableApiPtr);
         cfgSendNackToCm(CM_ERR_LOCKED_E1_TIMESLOTS);
         return ;
      }
      updateTrunkTableHandler();
      free(e1TableApiPtr);
   #if 0
   }
   #endif 
   } // Else of Create-Map/Delete-Map
} /* End of setE1TableHandler */

// CS4.0 Create Map/Delete Map
/********************************* Function  Header********************************
Function Name:       E1TrunkMap()
Parameters:          Pointer to received message & pointer to TrunkTableApi 
Return type:         void
Purpose:             This can be for following:
For Creating the mapping between Trunk Port Id & E1 Number
For Deleting the mapping between Trunk Port Id & E1 Number
Other Note:
 ************************************************************************************/
void E1TrunkMap( TrunkTableApi *receivedMsgPtr, TrunkTableApi *e1TableApiPtr ) 
{

   I_U32     adminstate = 0;
    
   // Check for the type of E1:: If Internal NACK the request
   if( e1TableApiPtr->e1Category != EXTERNAL_E1 ) 
   {
      LOG_PRINT(LOG_INFO,"E1 Type is Internal:Mapping not supported :: E1 & TRUNKPORT MAPPING PROCEDURE ENDS");
      cfgSendNackToCm(CM_ERR_E1_TYPE_NOT_EXTERNAL);
      return;
   }

   // Check in DB if Trunk Id is present
   //if( (  findTrunkIdTrunkPortTable(receivedMsgPtr->trunkId)) != CLIB_SUCCESS )
   if( receivedMsgPtr->trunkPortId != INVALID_TRUNK_ID )
   if( ( findTrunkIdTrunkPortTable(receivedMsgPtr->trunkPortId, &adminstate ) ) != I_TRUE )
   {
      LOG_PRINT(LOG_INFO,"Received Trunk Port Id not present in DB :: E1 & TRUNKPORT MAPPING PROCEDURE ENDS");
      cfgSendNackToCm(CM_ERR_TRUNK_ID_NOT_PRESENT_IN_DB);
      return;
   }

   // Check if Card state is ongoing or Recovery:: If yes, NACK the request
   if( g_card_in_standby_mode || g_card_in_recovery_mode )
   {
      LOG_PRINT(LOG_INFO,"Card State Change In Progress:: Discarding Create/Delete Map Request");
      cfgSendNackToCm(CM_ERR_CARD_STATE_CHANGE_IN_PROGRESS);
      return;
   }

   // Now check if the request is for Create Map/Delete Map
   if( receivedMsgPtr->mapAction ==  CREATE_MAP ) // Request to create mapping
   {
      // Nack the request if Trunk Id is in Enabled state

      // Check if Mapping of E1 Number Already exists 
      if( e1TableApiPtr->trunkPortId != INVALID_TRUNK_ID )
      {
         LOG_PRINT(LOG_INFO,"E1 Mapping exists:: Discarding Create/Delete Map Request");
         cfgSendNackToCm(CM_ERR_E1_MAPPING_ALREADY_EXISTS);
         return;
      }
      // Check if Mapping of Trunk Id Already exists 
      #if 0 //BSC R2.0 Changes TBA-GRV
      if( ( findTrunkIdInTrunkTable(receivedMsgPtr->trunkPortId) ) == I_TRUE )
      {
         LOG_PRINT(LOG_INFO," Trunk Id Mapping Exists:: Discarding Create/Delete Map Request");
         cfgSendNackToCm(CM_TRUNK_ID_MAPPING_ALREADY_EXISTS);
         return;
         
      }
      #endif
      if( adminstate == ENABLED )
      {
         LOG_PRINT(LOG_INFO,"Trunk Port in Enabled State:: Discarding Create/Delete Map Request");
         cfgSendNackToCm(CM_ERR_TRUNKPORT_ENABLED);
         return;
      }

      // If all the above checks pass, update the mapping in DB
      if( ( updateMappingTrunkTable(receivedMsgPtr->e1Num,  receivedMsgPtr->trunkPortId) ) == CLIB_SUCCESS )
      {
         LOG_PRINT(LOG_INFO," E1 & Trunk Id Mapping Updated in DB");
         cfgSendAckToCm(CM_SUCCESS);
         return;
      }
      else
      {
         LOG_PRINT(LOG_INFO," E1 & Trunk Id Mapping Updation Failed in DB");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         return;
      }
      
   }
   else if( receivedMsgPtr->mapAction ==  DELETE_MAP ) // Request to delete mapping
   {
   
      // Nack the request if Trunk Id is in Enabled state

      if( adminstate == ENABLED )
      {
         LOG_PRINT(LOG_INFO,"Trunk Port in Enabled State:: Discarding Create/Delete Map Request");
         cfgSendNackToCm(CM_ERR_TRUNKPORT_ENABLED);
         return;
      }

      // Check if Mapping of E1 Number exists 
      if( e1TableApiPtr->trunkPortId == INVALID_TRUNK_ID )
      {
         LOG_PRINT(LOG_INFO,"E1 Mapping does not exists:: Discarding Create/Delete Map Request");
         cfgSendNackToCm(CM_ERR_E1_MAP_NOT_CREATED);
         return;
      }

      // Delete the mapping in DB
      if( ( updateMappingTrunkTable(receivedMsgPtr->e1Num,  INVALID_TRUNK_ID ) ) == CLIB_SUCCESS )
      {
         LOG_PRINT(LOG_INFO," E1 & Trunk Id Mapping Deleted in DB");
         cfgSendAckToCm(CM_SUCCESS);
         return;
      }
      else
      {
         LOG_PRINT(LOG_INFO," E1 & Trunk Id Mapping Updation Failed in DB");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         return;
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Invalid Map Action:: Discarding Create/Delete Map Request");
      cfgSendNackToCm(CM_ERR_E1_INVALID_REQUEST);
      return;
   }

}
// CS4.0 Create Map/Delete Map


// CS4.0 Enable/Disable
/********************************* Function  Header********************************
   Function Name:       setTrunkPortTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To Enable TrunkPort Object
To Disable TrunkPort Object
Other Note:
 ************************************************************************************/
void setTrunkPortTableHandler()
{
   TrunkPortTableApi*     receivedMsgPtr           = ( TrunkPortTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   TrunkPortTableApi*     trunkPortTableApiPtr     = PNULL;
   TrunkPortStatusTableApi *trunkPortStsPtr        = PNULL;
   //E1PerTableApi*         E1PerTableApiPtr         = PNULL;
   //E1PerTableApi*         E1PerTableAddr           = PNULL;
   TrunkPortTableIndices  apiTrunkPortIndex        = {0} ;
   I_S32                  ret                      = 1; 
   I_U32                  rowsCount                = 0;
   I_U32                  i                        = 0;
   I_U16                  outSize                  = 0;
   I_Bool                 flag                     = FALSE;
   /*BSC R2.0 Changes Starts*/
   TrunkTableApi*         trunkTableApiPtr         = PNULL; 
   TrunkTableApi*         trunkTableAddr           = PNULL;
   TrunkPortStatusTableIndices trunkPortStsIndex = {0};
   TrunkPortStatusTableApi * trunkPortStsTbl = PNULL;
   /*BSC R2.0 Changes Ends*/
   I_U32 cardOperState;

   LOG_PRINT(LOG_INFO," In TrunkPortTableHandler");
   LOG_PRINT(LOG_INFO," TrunkPortTableHandler: Req Rcvd for FrameId(%d) slotId(%d) portId(%d)",
      receivedMsgPtr->chasisFrameId,
      receivedMsgPtr->slotId,
      receivedMsgPtr->trunkPortId);

   apiTrunkPortIndex.chasisFrameId   = receivedMsgPtr->chasisFrameId;
   apiTrunkPortIndex.slotId          = receivedMsgPtr->slotId;
   apiTrunkPortIndex.trunkPortId     = receivedMsgPtr->trunkPortId;
  
   trunkPortStsIndex.chasisFrameId   = receivedMsgPtr->chasisFrameId;
   trunkPortStsIndex.slotId          = receivedMsgPtr->slotId;
   trunkPortStsIndex.trunkPortId     = receivedMsgPtr->trunkPortId;
  
   gE1NumberMapToTrunk = receivedMsgPtr->trunkPortId;

  
   ret = getTrunkPortStatusTable(&trunkPortStsIndex, &trunkPortStsTbl);
   if(ret != CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"getTrunkPortStatusTable failed");
   }
   else if(trunkPortStsTbl->physicalPresenceState == NOT_PRESENT)
   {
      LOG_PRINT(DEBUG,"Requested TrunkPort is not physically present"); 
      free(trunkPortStsTbl);
      cfgSendNackToCm(CM_ERR_TRUNKPORT_PHYSICALLY_NOT_PRESENT);
      return;   
   }
   
   free(trunkPortStsTbl);

   ret = getTrunkPortTable(&apiTrunkPortIndex, &trunkPortTableApiPtr);

   // Check if received Trunk Port Id is in Db or not  
   if (PNULL == trunkPortTableApiPtr)
   {
      LOG_PRINT(LOG_INFO,"Received Trunk Port Id not present in DB :: TRUNK PORT ACTIVATE/DEACTIVATE PROCEDURE ENDS");
      cfgSendNackToCm(CM_ERR_TRUNK_ID_NOT_PRESENT_IN_DB);
      return;   
   }
   else // Store the data fetched from DB for further use in the flow
   {
      gTrunkAdminStateinDB = trunkPortTableApiPtr->physicalTrunkPortState;
      memcpy( &g_TrunkPortDb, trunkPortTableApiPtr, sizeof(g_TrunkPortDb) );

      if( gE1Data[gE1NumberMapToTrunk].trunkState == DisableInProgress )
      {
         LOG_PRINT(LOG_INFO,"Disable Procedure in Progress:: Discarding Enable Request");
         cfgSendNackToCm(CM_ERR_TRUNKPORT_DISABLE_IN_PROGRESS);
	       free(trunkPortTableApiPtr);
         return;   
      }
      if( gE1Data[gE1NumberMapToTrunk].trunkState == EnableInProgress )
      {
         LOG_PRINT(LOG_INFO,"Enable Procedure in Progress:: Discarding Disable Request");
         cfgSendNackToCm(CM_ERR_TRUNKPORT_ENABLE_IN_PROGRESS);
	       free(trunkPortTableApiPtr);
         return;   
      }

      // Check if received trunk port details are same as in Database
      flag = compareRcvdMsgAndDbEntry((void*)receivedMsgPtr,(void*)trunkPortTableApiPtr,sizeof(TrunkPortTableApi));
      if( FALSE == flag )
      {
         LOG_PRINT(LOG_INFO,"No Trunk Port parameter is being changed");
         cfgSendAckToCm(CM_SUCCESS);
	       free(trunkPortTableApiPtr);
         return;
      }
   }

   /*BSC-R2.5.5 Diagnostics changes Starts*/
   ret = getCardOperState(receivedMsgPtr->chasisFrameId,receivedMsgPtr->slotId,&cardOperState);
   if(ret != CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"getCardOperState failed err:%d", ret); 
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
	    free(trunkPortTableApiPtr);
      return;   
   }
   else
   {
      if(cardOperState == CARDSTATE_DIAGNOSTIC) 
      {
         LOG_PRINT(DEBUG,"action can not be performed as card in DIAGNOSTIC state"); 
         cfgSendNackToCm(CM_ERR_DIAGNOS_OPR_IN_PROGRESS);
	       free(trunkPortTableApiPtr);
         return;   
      }
   }

   if(I_TRUE == isDiagInProgressForPort(receivedMsgPtr->chasisFrameId,
                    receivedMsgPtr->slotId,receivedMsgPtr->trunkPortId) ) 
   {
      LOG_PRINT(DEBUG,"action can not be performed as port in DIAGNOSTIC state"); 
      cfgSendNackToCm(CM_ERR_DIAGNOS_OPR_IN_PROGRESS);
	    free(trunkPortTableApiPtr);
      return;   
   }
   /*BSC-R2.5.5 Diagnostics changes Ends*/
   
   // Check if RO parameter are being modified
   if( receivedMsgPtr->trunkType != trunkPortTableApiPtr->trunkType || \
        receivedMsgPtr->sigStrength != trunkPortTableApiPtr->sigStrength )
   {
      LOG_PRINT(LOG_INFO,"RO parameter is being modified::TRUNK PORT ENABLE/DISABLE PROCEDURE ENDS");
      cfgSendNackToCm(CM_ERR_E1_INVALID_REQUEST);
	    free(trunkPortTableApiPtr);
      return;   
   }

   /*BSC R2.0 Changes Starts*/

   // Check if received Trunk Id is mapped to Logical E1 Number  
   //ret = getallE1PerTable(&E1PerTableApiPtr, &rowsCount, &outSize);
   ret = getallTrunkTable(&trunkTableApiPtr, &rowsCount, &outSize);
   if (ret == CLIB_SUCCESS && PNULL != trunkTableApiPtr )
   {
      if( rowsCount > 0 )
      {
         for(i = 0; i < rowsCount; i++)
         {
            trunkTableAddr = (TrunkTableApi *) (((char *) trunkTableApiPtr ) + (outSize * i));

            if( trunkTableAddr->trunkPortId == receivedMsgPtr->trunkPortId )
            {
               LOG_PRINT(LOG_INFO," Mapping Found for received Trunk Id with portId %d", trunkTableAddr->e1Num);
               // Store the E1 Number for further use in the flow & loop ends.
               gE1NumberMapToTrunk = trunkTableAddr->e1Num;
               if(trunkTableAddr->adminState == UNLOCKED)
               {
                  cfgSendNackToCm(CM_ERR_E1_IN_UNLOCKED_STATE);
                  free(trunkTableApiPtr);
                  free(trunkPortTableApiPtr);   
                  return;
               } 
               break;
            }

            if( i == rowsCount - 1 )
            {
               LOG_PRINT(LOG_INFO," Mapping Not Found for received Trunk Id :: TRUNK PORT ENABLE/DISABLE PROCEDURE ENDS");
               //cfgSendNackToCm(CM_ERR_E1_MAP_NOT_CREATED);
               //free(E1PerTableApiPtr);
               //free(trunkPortTableApiPtr);   
               //return;
            }
         }
      }
      else
      {
         LOG_PRINT(LOG_INFO,"No rows present in TrunkTable :: TRUNK PORT ENABLE/DISABLE PROCEDURE ENDS");
         cfgSendNackToCm(CM_ERR_ROWS_NOT_PRESENT);
         free(trunkPortTableApiPtr);   
         return;   
      }

      free(trunkTableApiPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Get All operation failed on E1PerTable :: TRUNK PORT ENABLE/DISABLE PROCEDURE ENDS");
      cfgSendNackToCm(CM_ERR_GET_ALL_OPERATION_FAILED);
      free(trunkPortTableApiPtr);   
      return;   
   }

   /* CS40 PH-2 Changes ::PreConfig to Config - Starts */
 
   /*BSC R2.0 Changes Starts*/
   #if 0

   /* Check if the request is for change in Admin State only */
   if (( trunkPortTableApiPtr != PNULL) && 
         ( receivedMsgPtr->adminState != trunkPortTableApiPtr->adminState ) )
   {
      /* If any other parameter is being modified, then NACK the request */
      if( (receivedMsgPtr->physicalTrunkPortState != trunkPortTableApiPtr->physicalTrunkPortState) ||
          (receivedMsgPtr->usageType != trunkPortTableApiPtr->usageType) ||
          (receivedMsgPtr->trunkFramingOption != trunkPortTableApiPtr->trunkFramingOption) ||
          (receivedMsgPtr->encodeType != trunkPortTableApiPtr->encodeType) ||
          (receivedMsgPtr->loopType != trunkPortTableApiPtr->loopType) ||
          (receivedMsgPtr->loopback != trunkPortTableApiPtr->loopback) )
      {
         LOG_PRINT(LOG_INFO," Too many RW parameters being modified :: Lock/Unlock TrunkPort");
         free(trunkPortTableApiPtr);   
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         return;
      }
      else /* Proceed with the procedure for change in Admin state */
      {
         if( trunkPortTableApiPtr->usageType == SYS_E1_USAGE_NONE )
         {
            LOG_PRINT(LOG_INFO,"Cannot LOCK/UNLOCK the Trunkport when UsageType of TrunkPort is NONE ");
            free(trunkPortTableApiPtr);   
            cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);  
            return;            
         } 
 
         free(trunkPortTableApiPtr);         

         /* Prepare E1PerTable pointer from TrunkPortTable pointer which is to be used in existing 
            E1 lock & unlock implementation */     
         prepareE1Tblptr(receivedMsgPtr->adminState);
         return; 
      }

   }
   else if (( trunkPortTableApiPtr != PNULL) && 
   #endif
   if (( trunkPortTableApiPtr != PNULL) && 
         ( receivedMsgPtr->usageType != trunkPortTableApiPtr->usageType ) )
   {
      /* If any other parameter is being modified, then NACK the request */
      //if( (receivedMsgPtr->physicalTrunkPortState != trunkPortTableApiPtr->physicalTrunkPortState) ||
      //    //(receivedMsgPtr->adminState != trunkPortTableApiPtr->adminState) ||
      //    (receivedMsgPtr->trunkFramingOption != trunkPortTableApiPtr->trunkFramingOption) ||
      //    (receivedMsgPtr->loopType != trunkPortTableApiPtr->loopType) ||
      //    (receivedMsgPtr->encodeType != trunkPortTableApiPtr->encodeType)||
      //    (receivedMsgPtr->loopback != trunkPortTableApiPtr->loopback) )

      //{
      //   LOG_PRINT(LOG_INFO," Too many RW parameters being modified in TrunkPort Table");
      //   free(trunkPortTableApiPtr);   
      //   cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      //   return;
      //}
      //else /* Proceed with the procedure for change in Usage Type */
      //{
         ret = E1UsageTypeChangeHandler(trunkPortTableApiPtr);     
         LOG_PRINT(DEBUG,"E1UsageTypeChangeHandler retuned err %d", ret); 
         if( ret == CFG_FAILURE)
         {
            free(trunkPortTableApiPtr);   
            return;
         }  
         else if(  (ret == CFG_SUCCESS) && 
               (receivedMsgPtr->physicalTrunkPortState == trunkPortTableApiPtr->physicalTrunkPortState) )
         {
             LOG_PRINT(DEBUG,"Value of RcvdTrunkPortPhyState %d and dbTrunkPortPhyState %d is same",
                 receivedMsgPtr->physicalTrunkPortState,trunkPortTableApiPtr->physicalTrunkPortState); 
            /*Send Ack To CM*/ 
            cfgSendAckToCm();
            free(trunkPortTableApiPtr);   
            return;
         }  
      //   free(trunkPortTableApiPtr);         
      //   return; 
      //}
   }/* CS40 PH-2 Changes ::PreConfig to Config - Ends */

   // Enable or Disable TrunkPort 
   if (( trunkPortTableApiPtr != PNULL) && 
         (receivedMsgPtr->physicalTrunkPortState != trunkPortTableApiPtr->physicalTrunkPortState))
   {
      LOG_PRINT(LOG_INFO,"setE1TableHandler: calling e1ObjectHandler :: Enable/Disable TrunkPort");

      // Check if the value of physicalTrunkPortState is other than Enable/Disable
      if((receivedMsgPtr->physicalTrunkPortState != ACTIVATED) &&
         (receivedMsgPtr->physicalTrunkPortState != DEACTIVATED)
        )
      {
         LOG_PRINT(LOG_DEBUG," Inside setTrunkPortTableHandler : Received Wrong physicalTrunkPortState value from \
         Operator : %d", receivedMsgPtr->physicalTrunkPortState );         
	       cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         free(trunkPortTableApiPtr);   
         return;
      }
      /*MLPPP Changes starts*/
      if(receivedMsgPtr->physicalTrunkPortState == DEACTIVATED)     
      {
         if(checkForMlpppConfig(receivedMsgPtr->trunkPortId)==CFG_FAILURE)
         {
            LOG_PRINT(LOG_INFO,"Mlppp is configured on this port. Change the configuration First");
   	        cfgSendNackToCm(CM_ERR_MLPPP_IS_CONFIGURED);
            free(trunkPortTableApiPtr);   
            return;
         }
         /*MLPPP Changes Ends*/
         if(getBusyTsMapForTsGroup(receivedMsgPtr->trunkPortId)!=ZERO)
         {
           LOG_PRINT(LOG_DEBUG,"E1Id[%u] has one or more TsGroup configured",receivedMsgPtr->trunkPortId);
           cfgSendNackToCm(CM_ERR_TSGROUP_CONFIGURED_ON_E1);
            free(trunkPortTableApiPtr);   
           return ;
         }
         /*BSC R2.0 Changes Starts*/
         // Check if clock source is configured on the port on which Disable request is received
         if(TRUE == IsTrunkPortConfiguredAsClkSrc(receivedMsgPtr->trunkPortId))
         {
            LOG_PRINT(LOG_INFO,"Clock source configured on Trunk port:: Discarding Disable Request");
            cfgSendNackToCm(CM_ERR_CLK_SRC_CONFIGURED_ON_TRUNKPORT);
            free(trunkPortTableApiPtr);   
            return;
         }
			   /*BSC R2.0 Changes Ends*/
      }

      free(trunkPortTableApiPtr);   

      TrunkPortObjectHandler();

      return;   
   } // End If::Enable/Disable TrunkPort
/*   else if( gE1Data[gE1NumberMapToTrunk].trunkState == DisableInProgress )
   {
      LOG_PRINT(LOG_INFO,"Disable Procedure in Progress:: Discarding Enable Request");
      cfgSendNackToCm(CM_ERR_TRUNKPORT_DISABLE_IN_PROGRESS);
   }
   else if( gE1Data[gE1NumberMapToTrunk].trunkState == EnableInProgress )
   {
      LOG_PRINT(LOG_INFO,"Enable Procedure in Progress:: Discarding Disable Request");
      cfgSendNackToCm(CM_ERR_TRUNKPORT_ENABLE_IN_PROGRESS);
   } */
   else if( receivedMsgPtr->physicalTrunkPortState == DEACTIVATED)
   {
      if(receivedMsgPtr->trunkFramingOption == trunkPortTableApiPtr->trunkFramingOption && \
            receivedMsgPtr->encodeType == trunkPortTableApiPtr->encodeType)
      {
         LOG_PRINT(LOG_INFO,"Trunk Port Already DISABLED , Sending Nack");
         free(trunkPortTableApiPtr);   
         cfgSendNackToCm(CM_ERR_TRUNKPORT_ALREADY_DISABLED);
         return;
      }
      else
      {
          // Perform range check & update TrunkPort Details in DB

          if( receivedMsgPtr->trunkFramingOption != BPM_TRUNK_FRAMING_OPT_T1_D4 && receivedMsgPtr->trunkFramingOption != \
                BPM_TRUNK_FRAMING_OPT_T1_ESF && receivedMsgPtr->trunkFramingOption != BPM_TRUNK_FRAMING_OPT_E1_CRC4 &&\
                receivedMsgPtr->trunkFramingOption != BPM_TRUNK_FRAMING_OPT_E1_NOCRC4 )
          {
             receivedMsgPtr->trunkFramingOption = BPM_TRUNK_FRAMING_OPT_INVALID; 
          }
          
          if( receivedMsgPtr->encodeType != BPM_TRUNK_ENCODE_OPT_T1_E1_AMI && receivedMsgPtr->encodeType != \
                BPM_TRUNK_ENCODE_OPT_T1_B8ZS && receivedMsgPtr->encodeType != BPM_TRUNK_ENCODE_OPT_E1_HDB3 )
          {
             receivedMsgPtr->encodeType = BPM_TRUNK_ENCODE_TYPE_INVALID; 
          }
          
          // Perform Range check for loop type
          if( receivedMsgPtr->loopType != BPM_REMOTE_LOOPBACK  && \
              receivedMsgPtr->loopType != BPM_LOCAL_LOOPBACK &&\
              receivedMsgPtr->loopType != BPM_PAYLOAD_LOOPBACK && \
              receivedMsgPtr->loopType != BPM_FRAMER_LOOPBACK &&\
              receivedMsgPtr->loopType != BPM_ANALOG_LOOPBACK )
          {
             receivedMsgPtr->loopType = BPM_LOOPBACK_INVALID; 
          }
          
          // Perform range check for loop back value
          if( receivedMsgPtr->loopback != BPM_TRUNK_LOOPBACK_ENABLE  && \
              receivedMsgPtr->loopback != BPM_TRUNK_LOOPBACK_DISABLE )
          {
             LOG_PRINT(LOG_INFO,"Invalid loop back value::Enable/Disable Procedure ends");
             cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
             return;
          }
          // Update in DB Trunk Details
          ret =updateTrunkDetails( receivedMsgPtr->trunkPortId, 
                   receivedMsgPtr->trunkFramingOption, receivedMsgPtr->encodeType,
                   receivedMsgPtr->loopType, receivedMsgPtr->loopback);
          if( ret != CLIB_SUCCESS )
          {
             LOG_PRINT(LOG_INFO,"Enable/Disable:: Trunk Details not updated");
             cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
          }  
          else
          { 
            /*Send Ack To CM*/ 
            cfgSendAckToCm();
          }
      } 
   }
   else if( receivedMsgPtr->physicalTrunkPortState == ACTIVATED && \
            receivedMsgPtr->trunkFramingOption == trunkPortTableApiPtr->trunkFramingOption && \
            receivedMsgPtr->encodeType == trunkPortTableApiPtr->encodeType )
   {
      LOG_PRINT(LOG_INFO,"Trunk Port Already ENABLED , Sending Nack");
      free(trunkPortTableApiPtr);   
      //cfgSendNackToCm(CM_ERR_TRUNKPORT_ALREADY_ENABLED);
      cfgSendAckToCm();
      return;
   }
   else
   {
      LOG_PRINT(LOG_INFO,"TrunkPortTable parameter modification not allowed, Sending Nack");
      free(trunkPortTableApiPtr);   
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      return;
   }

} /* End of setTrunkPortTableHandler*/
// CS4.0 Enable/Disable



/********************************* Function  Header********************************
   Function Name:       setTimeSlotTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
For Locking TimeSlot Object
For Unlocking TimeSlot Object
Other Note:
 ************************************************************************************/
void setTimeSlotTableHandler()
{
   TrunkTableApi* e1TableApiPtr = PNULL;
   TrunkTableIndices apiE1Index ={0} ;

   AbisTimeSlotPerTableApi* receivedMsgPtr = (AbisTimeSlotPerTableApi*)(((I_U8*)gCfgMsgBuf )+ sizeof (sCmMsg));
   AbisTimeSlotPerTableApi* timeSlotTableApiPtr = PNULL;
   AbisTimeSlotPerTableIndices apiTimeSlotIndex = {0};
   I_S32  ret = 1; 
   

   LOG_PRINT(LOG_INFO,"In setTimeSlotTableHandler");
   apiTimeSlotIndex.e1Num = receivedMsgPtr->e1Num;
   apiTimeSlotIndex.tsNum = receivedMsgPtr->tsNum;

   ret = getAbisTimeSlotPerTable(&apiTimeSlotIndex, &timeSlotTableApiPtr);

   /* Check if received entry is in Db or not */ 
   if (PNULL == timeSlotTableApiPtr)
   {
      LOG_PRINT(LOG_INFO,"No Entry in Timeslot table for the received E1num+TSNum");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   /* Case: TimeSlot Lock and TimeSlot Unlock or Parameter Modification*/
   if (timeSlotTableApiPtr != PNULL)
   {
      // CS 4.0 Enable/Disable
      // Fetch the E1 from TimeslotPerTable
      apiE1Index.e1Num = receivedMsgPtr->e1Num;

      ret = getTrunkTable(&apiE1Index, &e1TableApiPtr);

      if( ret == CLIB_SUCCESS && e1TableApiPtr != NULL )
      {
         // Check if E1 is external Trunk Port & is in DISABLED state
         if( e1TableApiPtr->e1Category == EXTERNAL_E1 && ( gE1Data[e1TableApiPtr->e1Num].trunkState == Disabled\
             || gE1Data[e1TableApiPtr->e1Num].trunkState == DisableInProgress ) )
         {
            LOG_PRINT(LOG_INFO,"setTimeslotTableHandler: E1 in Disabled State");
            cfgSendNackToCm(CM_ERR_TRUNKPORT_DISABLED);
            free(e1TableApiPtr);
            return;
         }
         free(e1TableApiPtr);
      }
      else
      {
         LOG_PRINT(LOG_INFO," setTimeslotTableHandler: getTrunkTable fails ");
         cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
         return;
      }

      // CS 4.0 Enable/Disable


      LOG_PRINT(LOG_INFO,"calling e1TimeSlotObjectHandler...");  
      free(timeSlotTableApiPtr);
      /* Fixed Manits #3833 : Start */
      if((receivedMsgPtr->adminState != LOCK) &&
         (receivedMsgPtr->adminState != UNLOCK)
        )
      {
         LOG_PRINT(LOG_DEBUG,"e1TimeSlotObjectHandler : Received Wrong adminState value from Operator : %d",
                                                        receivedMsgPtr->adminState);         
	       cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      }
      /* Fixed Manits #3833 : End */

      e1TimeSlotObjectHandler();
      return;
   } /* End of Case: TimeSlot Lock and TimeSlot Unlock */

} /* end of setTimeSlotTableHandler */


/********************************* Function  Header********************************
   Function Name:       setPsCellTableHandler()
Parameters:          void
Return type:         void
Purpose:              This can be for following:
To add new entry in PSCell table
To Modify the parameters in the PSCell table
Other Note:
 ************************************************************************************/
void setPsCellTableHandler()
{
   PsCellTableApi* receivedMsgPtr = ( PsCellTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   PsCellTableApi* psCellTableApiPtr = PNULL; 
   PsCellTableApi* tempPsCellTablePtr = PNULL; 
   PsCellTableIndices apiPsCellIndex;
   CellPerTableApi* cellTableApiPtr = PNULL;       
   CellPerTableIndices apiCellIndex;      
   I_Bool statusRange = FALSE;
   I_S32  ret = CM_FAILURE;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;
   BssPsPreConfigTableApi* psPreConfigTablePtr = PNULL; 
/*Changes PCU R2.5 Aricent -- START*/
   PsCellStatusTableApi psCellStatusTableApiBuff;
/*Changes PCU R2.5 Aricent -- END*/
   LOG_PRINT(LOG_INFO,"In setPsCellTableHandler");
   LOG_PRINT(LOG_INFO,"cellId = %u, lac = %u", receivedMsgPtr->cellId, receivedMsgPtr->lac);

   /* Checks BssPsPreConfigTable must be configured already */
   ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &rowsCount, &outSize);
   if(DBLIB_SUCCESS == ret && 0 < rowsCount)
   {
      /*Do Nothing*/
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC. DB Call getallBssPsPreConfigTable returned [%u]",ret);
      cfgSendNackToCm(CM_ERR_GPRS_NOT_ALLOWED);
      return;
   }

   apiCellIndex.cellId =  receivedMsgPtr->cellId;
   apiCellIndex.lac = receivedMsgPtr->lac;

   ret = getCellPerTable(&apiCellIndex, &cellTableApiPtr);


   LOG_PRINT(LOG_INFO,"ret = %d :: CM_SUCCESS = %d :: cellTableApiPtr = %u", ret,CM_SUCCESS,cellTableApiPtr);    
   if (CLIB_SUCCESS != ret || PNULL == cellTableApiPtr)
   {
      LOG_PRINT(LOG_INFO,"setPsCellTableHandler: Cell with CellId[%u] is not in DB, sending Nack", receivedMsgPtr->cellId);    
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      free(psPreConfigTablePtr);
      return;      
   }

   /* Check if corresponding Cell entry is Lock or not */
   if ((PNULL != cellTableApiPtr) && (cellTableApiPtr->adminState != LOCK))
   {
      LOG_PRINT(LOG_INFO,"Cell with CellId[%u] is unlocked, Sending Nack",cellTableApiPtr->cellId);     
      free(cellTableApiPtr);
      free(psPreConfigTablePtr);
      cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);
      return;       
   }
   if(PNULL != cellTableApiPtr)
   {
      free(cellTableApiPtr);
   }   
   /* Check if entry is present in DB or not */
   apiPsCellIndex.cellId =  receivedMsgPtr->cellId;
   apiPsCellIndex.lac = receivedMsgPtr->lac;

   ret = getPsCellTable(&apiPsCellIndex, &psCellTableApiPtr);   

   if(PNULL == psCellTableApiPtr)
      ret = doConsistencyChecksOnSetOnPSCellTable(receivedMsgPtr, TRUE);
   else
      ret = doConsistencyChecksOnSetOnPSCellTable(receivedMsgPtr, FALSE);

   if( CM_SUCCESS != ret )
   {
       LOG_PRINT(LOG_MAJOR,"doConsistencyChecksOnSetOnPSCellTable failed :: Sending Nack:Error Code[%d]",ret);
       cfgSendNackToCm(ret);
       return;
   }

   /* Case: Addition of PsCell in PsCell Table */
   if (psCellTableApiPtr == PNULL)
   {
      statusRange = psCellTableRangeChk(receivedMsgPtr);
      if (statusRange)
      {
         rowsCount = 0;
         outSize = 0;
         ret = getallPsCellTable(&tempPsCellTablePtr, &rowsCount, &outSize);

         if(CLIB_SUCCESS == ret)
         {
            /* Free temporary variable tempCellTablePtr */
            free(tempPsCellTablePtr);
         }

         /* Check if Max no of Rows are inserted in PsCell Table or not */
         if (rowsCount < CFG_MAX_NUM_CELLS)
         {
            ret = insertPsCellTable(receivedMsgPtr ); 
            if (ret == CLIB_SUCCESS)
            {
/*Changes PCU R2.5 Aricent -- START*/

               /* Add row in Cell level PS Performance Counter tables for this cell */
               insertRowInPsPerformanceCounterTablesForCell(receivedMsgPtr->cellId, receivedMsgPtr->lac);
               
               psCellStatusTableApiBuff.cellId = apiPsCellIndex.cellId;
               psCellStatusTableApiBuff.lac  = apiPsCellIndex.lac;
               psCellStatusTableApiBuff.oprState = DISABLED;
               ret = insertPsCellStatusTable(&psCellStatusTableApiBuff); 
               if (CLIB_SUCCESS != ret)
               {
                  LOG_PRINT(LOG_CRITICAL,"Db Operation failed in PsCellStatusTable Error Code = [%u]", ret);
                  cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
                  free(psPreConfigTablePtr);
                  return;
               }
/*Changes PCU R2.5 Aricent -- END*/
               LOG_PRINT(LOG_INFO,"Insert DB Successful, Sending Ack");
               cfgSendAckToCm();
               free(psPreConfigTablePtr);
               return;      
            }
            else
            {
               LOG_PRINT(LOG_MAJOR,"Insert DB Failed in PsCellTable Error Code =  [%u]", ret);
               cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED); 
               free(psPreConfigTablePtr);
               return;      
            } 
         } /* End of- if (rowsCount < NUM_OF_CELL_OBJECT_INSTANCES) */ 
         else
         {
            LOG_PRINT(LOG_INFO,"setPsCellTableHandler: Max Row exceeded in PsCell table, sending Nack");
            cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
            free(psPreConfigTablePtr);
            return;
         }
      } /* End of- if (statusRange) */
      else
      {
         LOG_PRINT(LOG_INFO,"Insert Row Operation with out of range value, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         free(psPreConfigTablePtr);
         return;    
      }  
   }/* End of Case: Addition of PsCell in PsCell Table */  

   /* Case: Modification of PsCell in Cell Table */
   if (psCellTableApiPtr != PNULL)
   {
      LOG_PRINT(LOG_INFO,"Calling RangeChk");
      statusRange = psCellTableRangeChk(receivedMsgPtr);
      free(psCellTableApiPtr);       

/*Changes PCU R2.5 Aricent -- START*/
      if(receivedMsgPtr->maxNumTbfPdch > psPreConfigTablePtr->maxNumTbfPerPdch)
      {
         LOG_PRINT(LOG_MAJOR,"maxNumTbfPdch [%u] is greater than the maxNumTbfPdch in BssPsPreConfigTable [%u]",
                   receivedMsgPtr->maxNumTbfPdch, psPreConfigTablePtr->maxNumTbfPerPdch);
         cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
         free(psPreConfigTablePtr);
         return;
      }
      else
      {
         free(psPreConfigTablePtr);
      }
/*Changes PCU R2.5 Aricent -- END*/

      if (statusRange)
      {  
         ret = updatePsCellTable(receivedMsgPtr ); 
         if (ret == CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_INFO,"Update DB Successful, Sending Ack");
            cfgSendAckToCm();
            return;      
         }
         else
         {
            LOG_PRINT(LOG_CRITICAL,"Update DB Failed, Sending Nack");
            cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
            return;      
         } 
      } /* End of- if (statusRange) */
      else
      {
         LOG_PRINT(LOG_INFO,"Modification Request with out of range value, sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;   
      }
   }/* End of Case: Modification of PsCell in Cell Table */ 

}/* end of setPsCellTableHandler */


/********************************* Function  Header********************************
   Function Name:       setCsExternalCellTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in CsExternalCell table
To Modify the parameters in the CsExternalCell table
Other Note:
 ************************************************************************************/
void setCsExternalCellTableHandler()
{

   CsExternalCellTableApi* receivedMsgPtr =
      ( CsExternalCellTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   CsExternalCellTableApi* csExtnCellTblApiPtr = PNULL; 
   CsExternalCellTableIndices apiCsExCellIndex = {0};
   I_Bool flagParamChange = FALSE; /* Set if any field value in CsExternalCellTable is changed */
   I_Bool statusRange = FALSE;
   I_S32  ret = 1; 
   I_U32 outRow = ZERO;
   I_U16 outSz = ZERO;
   CellTableIndices cellTableInd = {0};
   CellTableApi*    cellTableApi = PNULL;
   I_U8 statusWcdma = FALSE;
   CsExternalCellTableSecIndices apiSecCsExCellIndex = {0};
   CsExternalCellTableApi* csExtnCellTblApi = PNULL; 
   CsExternalCellTableApi* tmpExtnCellTblApi = PNULL; 
   I_U32 outCount = ZERO;
   I_U16 outDataSize = ZERO;
   I_U32 i = ZERO;

   LOG_PRINT(LOG_INFO," In setCsExternalCellTableHandler");
   apiCsExCellIndex.csExtCellId =  receivedMsgPtr->csExtCellId;
   apiCsExCellIndex.lac =  receivedMsgPtr->lac;
   apiCsExCellIndex.mnc =  receivedMsgPtr->mnc;
   apiCsExCellIndex.mcc =  receivedMsgPtr->mcc;

   ret = getCsExternalCellTable(&apiCsExCellIndex, &csExtnCellTblApiPtr);   

   /* Case: Addition of Row in CS External Cell Table */
   if (csExtnCellTblApiPtr == PNULL)
   {
      statusRange = csExternalCellTableRangeChk(receivedMsgPtr);
      if (statusRange)
      {
         /* Fixed Mantis #6033 : Start */
         if(FALSE == isCgiUnqInExtAndIntCellTable(receivedMsgPtr, EXTERNAL))
         {
            LOG_PRINT(LOG_MAJOR,"setCsExternalCellTableHandler : Consistency Check Fail");
	    cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
	    return;
         } 
         /* Fixed Mantis #6033 : End */

	 /* Bug Fixed - Mantis #4939 : Start */
	 /* Check whether Maximum Entries are already Configured or Not */
	 ret = getallCsExternalCellTable(&csExtnCellTblApiPtr, &outRow, &outSz);
	 if(DBLIB_SUCCESS == ret)
	 {
	    free(csExtnCellTblApiPtr);
	 }
	 if(outRow >= (CFG_MAX_NUM_CELLS * CFG_MAX_NEIGHBOUR_CELLS))
	 {
	    LOG_PRINT(LOG_MAJOR,"setCsExternalCellTableHandler : Max Entries are Already Present");
       cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
       return;
	 }
	 /* Bug Fixed - Mantis #4939 : End */
        apiSecCsExCellIndex.bcchArfcn =  receivedMsgPtr->bcchArfcn;
         ret = getSecCsExternalCellTable(&apiSecCsExCellIndex, &csExtnCellTblApi,&outCount,&outDataSize); 
         if(DBLIB_SUCCESS == ret)
	       {
             LOG_PRINT(LOG_INFO," OutCount %d",outCount );
             LOG_PRINT(LOG_INFO," OutSize %d",outDataSize );
             LOG_PRINT(LOG_INFO," the same ARFCN exist %d",receivedMsgPtr->bcchArfcn );
        //Bug fix for  Mantis - 26171
         for(i = 0; i < outCount; i++)
         {
           tmpExtnCellTblApi = (CsExternalCellTableApi *) (((char *) csExtnCellTblApi ) + (outDataSize * i));
           if ( tmpExtnCellTblApi->radioAccessType == WCDMA_FDD )
           {
             if (( tmpExtnCellTblApi->scrambling_Code == receivedMsgPtr->scrambling_Code ) &&
                 ( tmpExtnCellTblApi->diversity == receivedMsgPtr->diversity ))
             {
               LOG_PRINT(LOG_INFO," the scambling code %d and diversity %d exist for same ARFCN",receivedMsgPtr->scrambling_Code, receivedMsgPtr->diversity );
               cfgSendNackToCm(CM_ERR_ARFCN_SCRAMBLING_CODE_DIVERSITY_ALREADY_EXIST);
               free(csExtnCellTblApi);
               return;
             } 
             if(outCount >= CFG_MAX_NUM_SCRAMBLING_CODE_PER_ARFCN)
             {
               LOG_PRINT(LOG_MAJOR,"setCsExternalCellTableHandler : Max Entries For Scramblin Code Per arfcn are Already Present");
               cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES_PER_WCDMA_FDD_ARFCN);
               free(csExtnCellTblApi);
               return;
           }  
           } /*if  tmpExtnCellTblApi->radioAccessType == WCDMA_FDD  */ 
#if 0   
           /* Commented for Mantis 28599; Different external cells can be added 
            * with same BCC and NCC, but those cells cannot be neighbor of same cell
            */
           else
           { //Rat_Type = 2g
             if(( tmpExtnCellTblApi->bcc == receivedMsgPtr->bcc) &&
                 ( tmpExtnCellTblApi->ncc == receivedMsgPtr->ncc))
             {
               LOG_PRINT(LOG_INFO," the BCC %d and NCC %d exist for same ARFCN",receivedMsgPtr->bcc, receivedMsgPtr->ncc );
               cfgSendNackToCm(CM_ERR_ARFCN_BCC_NCC_ALREADY_EXIST); // new error code for mantis 26171
               free(csExtnCellTblApi);
               return;
             }
           }
#endif
         }/* end for loop outCount*/
        
         /*if(outCount >= CFG_MAX_NUM_SCRAMBLING_CODE_PER_ARFCN)
           {
	           LOG_PRINT(LOG_MAJOR,"setCsExternalCellTableHandler : Max Entries For Scramblin Code Per arfcn are Already Present");
             cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES_PER_WCDMA_FDD_ARFCN);
	           free(csExtnCellTblApi);
             return;
           }  */
	          free(csExtnCellTblApi);
	       }/*end if ret */

        //Bug fix for  Mantis - 26171 end
         ret = insertCsExternalCellTable(receivedMsgPtr ); 
         if (ret == CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_INFO," setCsExternalCellTableHandler: Insert DB Successful, Sending Ack");
            cfgSendAckToCm();
            return;
         }
         else
         {
            LOG_PRINT(LOG_CRITICAL," setCsExternalCellTableHandler: Insert DB Failed, Sending Nack");
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return;
         } 
      } /* end of if (statusRange) */
      else
      {
         LOG_PRINT(LOG_INFO," Insert Row Operation with out of range value, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      }   
   }/* End of Case: Addition of Row in CS External Cell Table */  

   /* Case: Modify CS External Cell Table */
   if (csExtnCellTblApiPtr != PNULL)   
   {
      LOG_PRINT(LOG_INFO," setCsExternalCellTableHandler: Calling compare");
      flagParamChange = compareRcvdMsgAndDbEntry((void*) receivedMsgPtr,
            (void*) csExtnCellTblApiPtr,
            sizeof(CsExternalCellTableApi));
      if (flagParamChange)
      {
         if ( csExtnCellTblApiPtr->radioAccessType == WCDMA_FDD ) 
            { 
              statusWcdma = isChangesAllowedForWcdmaCell(csExtnCellTblApiPtr->csExtCellId, 
                  csExtnCellTblApiPtr->lac,csExtnCellTblApiPtr->mcc, csExtnCellTblApiPtr->mnc);
              if ( statusWcdma == TRUE ) 
              {
                  LOG_PRINT(LOG_MAJOR,"3setCsExternalCellTableHandler : Consistency Check Failed - ");
                  cfgSendNackToCm(CM_ERR_WCDMA_OPR_NOT_ALLOW_IN_CELL_UNLOCK_STATE);/* New Error Code will be added*/
                  free(csExtnCellTblApiPtr);       
                  return;
              }  
            }
         /* Bug Fix - Mantis #24980 : Start */
         /* Combination of arfcn+scrambling_code to be unique for each external cell */
         if(receivedMsgPtr->radioAccessType == WCDMA_FDD)
         {
            apiSecCsExCellIndex.bcchArfcn =  receivedMsgPtr->bcchArfcn;
            ret = getSecCsExternalCellTable(&apiSecCsExCellIndex, &csExtnCellTblApi,&outCount,&outDataSize); 
            if(DBLIB_SUCCESS == ret)
	          {
               for(i = 0; i < outCount; i++)
               {
                  tmpExtnCellTblApi = (CsExternalCellTableApi *) (((char *) csExtnCellTblApi ) + (outDataSize * i));
            
                  if(( tmpExtnCellTblApi->scrambling_Code == receivedMsgPtr->scrambling_Code ) &&
                  ( tmpExtnCellTblApi->diversity == receivedMsgPtr->diversity ))
                  {
                     LOG_PRINT(LOG_CRITICAL," the scambling code %d and diversity %d already exist for ARFCN %d in externalCell %d",
                         receivedMsgPtr->scrambling_Code, receivedMsgPtr->diversity, receivedMsgPtr->bcchArfcn, tmpExtnCellTblApi->csExtCellId);
                     cfgSendNackToCm(CM_ERR_ARFCN_SCRAMBLING_CODE_DIVERSITY_ALREADY_EXIST);
                     free(csExtnCellTblApi);
                     return;
                  } 
               } 
            }
         }
         /* Bug Fix - Manits #24980 : End */

         /* Bug Fixed - Manits #4996 : Start */
         /* Consistency Check - BcchArfcn+Bsic must be unique for a Neighbourhood */
         statusRange = isArfcnBsicFoundInNeighTable(receivedMsgPtr, ONE, FALSE);
         if(TRUE == statusRange)
         {
            /* bcchArfcn & BSIC is already configured */
            LOG_PRINT(LOG_MAJOR,"setCsExternalCellTableHandler : Consistency Check Failed - BcchArfcn+Bsic is Already Configured for Neighbours");
            cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
            free(csExtnCellTblApiPtr);       
            return;
         }
         /* Bug Fixed - Manits #4996 : End */

         statusRange = csExternalCellTableRangeChk(receivedMsgPtr);
         if (statusRange)
         {  
            LOG_PRINT(LOG_INFO," Modification Request");
            ret = updateCsExternalCellTable(receivedMsgPtr ); 
            if (ret == CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
               cfgSendAckToCm();
   	       /* On The Fly Changes : Start */
	       if((csExtnCellTblApiPtr->bcc != receivedMsgPtr->bcc) ||
		         (csExtnCellTblApiPtr->ncc != receivedMsgPtr->ncc) ||
		         (csExtnCellTblApiPtr->bcchArfcn != receivedMsgPtr->bcchArfcn))
           {
		         sndCsNeighCellChangeMsgToCellh(csExtnCellTblApiPtr->csExtCellId, csExtnCellTblApiPtr->lac,csExtnCellTblApiPtr->mcc, csExtnCellTblApiPtr->mnc);
	         }
   	       /* On The Fly Changes : End */
               free(csExtnCellTblApiPtr);       
               return;      
            }
            else
            {
               LOG_PRINT(LOG_CRITICAL," Update DB Failed, Sending Nack");
               cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
               free(csExtnCellTblApiPtr);       
               return;      
            }
         } /* End of- if (statusRange) */ 
         else
         {
            LOG_PRINT(LOG_INFO," Modification Request with out of range value, sending Nack");
            cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
            free(csExtnCellTblApiPtr);       
            return;   
         }
      } /* end of if (flagParamChange) */
      else
      {
         free(csExtnCellTblApiPtr);
         LOG_PRINT(LOG_INFO," Modification Request with same value as in DB, sending ack");
         cfgSendAckToCm();
      }
   }/* End of Case: Modification of PsCell in Cell Table */       

} /* end of setCsExternalCellTableHandler */


/********************************* Function  Header********************************
   Function Name:       setLaTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in LA table
To Modify the parameters in the LA table 
Other Note:
 ************************************************************************************/
void setLaTableHandler()
{
   LaTableApi* receivedMsgPtr = 
      ( LaTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   LaTableApi* laTblApiPtr = PNULL;
   LaTableApi* laTblApiAllPtr = PNULL;
   LaTableIndices apiLaIndex;

   /* Flag is Set if any attribute value in LA Cell Table is to be changed */
   I_Bool statusRange = FALSE;
   I_S32  ret = CM_FAILURE;
   I_U32  outRows = 0;
   I_U16  outSize = 0;
   
   LOG_PRINT(LOG_INFO,"In setLaTableHandler");
   LOG_PRINT(LOG_INFO,"lac = %u", receivedMsgPtr->lac);
   
#if 0
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
#endif
   apiLaIndex.lac =  receivedMsgPtr->lac;
   ret = getLaTable(&apiLaIndex, &laTblApiPtr);


   /* Case: Addition of Row in LA Table */
   if (laTblApiPtr == PNULL)
   {
      LOG_PRINT(LOG_INFO,"Insertion in La Table");
      ret = getallLaTable(&laTblApiAllPtr, &outRows, &outSize);
      if (ret == CLIB_SUCCESS)
      {
         if (MAX_NUM_CELL_PER_BSS == outRows)
         {
            LOG_PRINT(LOG_MAJOR, "Max allowed Rows [%u] in LaTable already exists. No more rows can be added, Sending Nack", MAX_NUM_CELL_PER_BSS);
            cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
            free(laTblApiAllPtr);
            return;
         }
         free(laTblApiAllPtr);
      }

      statusRange = laTableRangeChk(receivedMsgPtr);                
      if (statusRange)
      {
         ret = insertLaTable(receivedMsgPtr ); 
         if (ret == CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_INFO,"Insert DB Successful, Sending Ack");
            cfgSendAckToCm();
            return;
         }
         else
         {
            LOG_PRINT(LOG_CRITICAL,"Insert DB Failed, Sending Nack");
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return;
         } 
      }
      else
      {
         LOG_PRINT(LOG_INFO,"Insert Row Operation with out of range value, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;    
      }      
   } 
   else
   {
      LOG_PRINT(LOG_INFO,"La Table can't be modified, sending Nack");
      cfgSendNackToCm(CM_ERR_SET_OBJ_NOT_ALLOWED);
      free(laTblApiPtr);
      return;    
   }       

} /* end of setLaTableHandler */

/********************************* Function  Header********************************
   Function Name:       setRaTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in RA table
To Modify the parameters in the RA table 
Other Note:
 ************************************************************************************/
void setRaTableHandler()
{
   RaTableApi* receivedMsgPtr = 
      ( RaTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   RaTableApi* raTblApiPtr = PNULL;
   RaTableApi* raTblApiAllPtr = PNULL;
   RaTableIndices apiRaIndex;

   /* Flag is Set if any attribute value in RA Cell Table is to be changed */
   I_Bool statusRange = FALSE;
   I_S32  ret = CM_FAILURE;
   I_U32  outRows = 0;
   I_U16  outSize = 0;

   LOG_PRINT(LOG_INFO,"In setRaTableHandler");
   LOG_PRINT(LOG_INFO,"rac = %u, lac = %u", receivedMsgPtr->rac, receivedMsgPtr->lac);

    
/*Changes PCU R2.5 Aricent -- START*/  
   ret = doConsistencyChecksOnSetOnRaTable(receivedMsgPtr);

   if( CM_SUCCESS != ret )
   {
       LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnRaTable failed:: Sending Nack:ErrorCode [%d]", ret);
       cfgSendNackToCm(ret);
       return;
   }
/*Changes PCU R2.5 Aricent -- END*/

   apiRaIndex.rac =  receivedMsgPtr->rac;
   apiRaIndex.lac =  receivedMsgPtr->lac;
   ret = getRaTable(&apiRaIndex, &raTblApiPtr);  
   /* Case: Addition of Row in RA Table */
   if (PNULL == raTblApiPtr)
   {
      ret = getallRaTable(&raTblApiAllPtr, &outRows, &outSize);
      if (ret == CLIB_SUCCESS)
      {
         if (MAX_NUM_CELL_PER_BSS == outRows)
         {
            LOG_PRINT(LOG_MAJOR, "Max allowed Rows [%u] in RaTable already exists. No more rows can be added, Sending Nack", MAX_NUM_CELL_PER_BSS);
            cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
            free(raTblApiAllPtr);
            return;
         }
         free(raTblApiAllPtr);
      }

      LOG_PRINT(LOG_INFO,"Insertion in Ra Table");
      statusRange = raTableRangeChk(receivedMsgPtr);                
      if (statusRange)
      {
         ret = insertRaTable(receivedMsgPtr ); 

         if (CLIB_SUCCESS == ret)
         {
            LOG_PRINT(LOG_INFO,"Insert DB Successful, Sending Ack");
            cfgSendAckToCm();
            return;
         }
         else
         {
            LOG_PRINT(LOG_CRITICAL,"Insert DB Failed Error Code = [%d] , Sending Nack", ret);
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return;
         } 
      } /* end of if (statusRange) */
      else
      {
         LOG_PRINT(LOG_INFO,"Insert Row Operation with out of range value, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;    
      }  
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Ra Table can't be modified, sending Nack");
      cfgSendNackToCm(CM_ERR_SET_OBJ_NOT_ALLOWED);
      free(raTblApiPtr);
      return;    
   } 
} /* end of setRaTableHandler */

/********************************* Function  Header********************************
   Function Name:       setChnGrpTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in ChnGrp table
To Modify the parameters in the ChnGrp table 
Other Note:
 ************************************************************************************/
void setChnGrpTableHandler()
{
   ChnGrpTableApi* receivedMsgPtr = 
      ( ChnGrpTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   ChnGrpTableApi* chnGrpTblApiPtr = PNULL;
   ChnGrpTableIndices apiChnGrpIndex;
   CellPerTableApi* cellTableApiPtr = PNULL;
   CellPerTableIndices apiCellIndex; 
   /* Flag is Set if any attribute value in ChnGrp Table is to be changed */
   I_Bool statusRange = FALSE;
   I_S32  ret = CM_FAILURE; 

   LOG_PRINT(LOG_INFO,"In setChnGrpTableHandler");
   LOG_PRINT(LOG_INFO,"cellId = %u, lac = %u, ChnGrpId = %u", receivedMsgPtr->cellId, receivedMsgPtr->lac,  receivedMsgPtr->chnGrpId);

   apiCellIndex.cellId =  receivedMsgPtr->cellId;
   apiCellIndex.lac = receivedMsgPtr->lac;
   if(getCellPerTable(&apiCellIndex, &cellTableApiPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Pre-Condition Failed- Cell is not present for this channel group");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;  
   }
   if   (cellTableApiPtr->adminState == UNLOCK)
   {
      free(cellTableApiPtr);
      LOG_PRINT(LOG_INFO," Pre-Condition Failed- Cell Table is Unlocked");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;
   }

   /* Bug Fixed - 4683 : Start */
   /* Consistency Check : maxTxPwr in ChnGrpTable <=  bcchPwr in CellPerTable */
   if((receivedMsgPtr->maxTxPwr) > (cellTableApiPtr->bcchPwr))
   {
      free(cellTableApiPtr);
      LOG_PRINT(LOG_MAJOR,"Consistency Failed : maxTxPwr[%u] in ChnGrpTable >  bcchPwr[%u] in CellPerTable",receivedMsgPtr->maxTxPwr,cellTableApiPtr->bcchPwr);
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return;
   }
   /* Bug Fixed - 4683 : End */
   /* R2.4 change Start */ 
   if ( (receivedMsgPtr->cbch == 1) && ( (receivedMsgPtr->bcchCcchSdcch4 == 0) && ( receivedMsgPtr->bcchCcch == 0) ) )
   {
       LOG_PRINT(LOG_MAJOR,"Consistency Failed : CBCH allowed only in BCCH ChnGrp");
      cfgSendNackToCm(CM_ERR_CBCH_NOT_ALLOWED_IN_NONBCCH_CHNGRP);
      return;
   }
   if ( (receivedMsgPtr->cbch == 1) && ( receivedMsgPtr->bcchCcch == 1) && ( receivedMsgPtr->sdcch8 == 0)  &&  (receivedMsgPtr->bcchCcchSdcch4 == 0) )
   {
      LOG_PRINT(LOG_MAJOR,"Consistency Failed : CBCH allowed only if sdcch8 also configured with bcchCcch");
      cfgSendNackToCm(CM_ERR_CBCH_NOT_ALLOWED_WITHOUT_SDCCH);
      return;
   }
 /*  if ( (receivedMsgPtr->cbch == 1) && (receivedMsgPtr->bcchCcchSdcch4 == 1 ) && ( receivedMsgPtr->sdcch8 >= 1 ) )
   {
      LOG_PRINT(LOG_MAJOR,"Consistency Failed : CBCH allowed only with either sdcch8 or sdcch4 configured with bcchCcch");
      cfgSendNackToCm(CM_ERR_CBCH_NOT_ALLOWED_WITH_BOTH_SDCCH8_AND_SDCCH4);
      return;
   }
   if ( (receivedMsgPtr->cbch == 1) && ( receivedMsgPtr->bcchCcch == 1) && ( receivedMsgPtr->sdcch8 > 1 ) )
   {
      LOG_PRINT(LOG_MAJOR,"Consistency Failed : CBCH allowed only with either sdcch8 equals to 1");
      cfgSendNackToCm(CM_ERR_CBCH_ALLOWED_WITH_ONE_SDCCH8_ONLY);
      return;
   }
*/
   /* R2.4 change End */ 
   free(cellTableApiPtr);
   
   apiChnGrpIndex.chnGrpId =  receivedMsgPtr->chnGrpId;
   apiChnGrpIndex.cellId =  receivedMsgPtr->cellId;
   apiChnGrpIndex.lac = receivedMsgPtr->lac;
   ret = getChnGrpTable(&apiChnGrpIndex, &chnGrpTblApiPtr);
   LOG_PRINT(LOG_INFO,"DB call getChnGrpTable failed. Returned [%d]. Request is for addtion",ret);
   /* Case: Addition of Row in ChnGrp Table */
   if (chnGrpTblApiPtr == PNULL)
   {
      statusRange = chnGrpTableRangeChk(receivedMsgPtr);                
      if (statusRange)
      {
         ret = insertChnGrpTable(receivedMsgPtr ); 
         if (ret == CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
            /* R2.4 change start */
            if ( receivedMsgPtr->cbch == 1 )
            {
               sendAddCbCellToCbsh(receivedMsgPtr->cellId, receivedMsgPtr->lac);
            }
            /* R2.4 change start */
			cfgSendAckToCm();
            return;    
         }
         else
         {
            LOG_PRINT(LOG_CRITICAL," Insert DB Failed, Sending Nack");
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return;    
         } 
      }/* end of if (statusRange) */
      else
      {
         LOG_PRINT(LOG_INFO," Insert Row Operation with out of range value, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;    
      }   
   }  

   /* Case: Modify ChnGrp Table */
   if (chnGrpTblApiPtr != PNULL)   
   {
      free(chnGrpTblApiPtr);          
      statusRange = chnGrpTableRangeChk(receivedMsgPtr);
      if (statusRange)
      {  
         LOG_PRINT(LOG_INFO," Modification Request, calling  updateChnGrpTable");
            /*R2.4 change Start */
            if ( (receivedMsgPtr->cbch == TRUE) && (chnGrpTblApiPtr->cbch == FALSE) )
            {
               LOG_PRINT(LOG_INFO,"CBCH Configured in ChnGrp");
               sendAddCbCellToCbsh(receivedMsgPtr->cellId, receivedMsgPtr->lac);
            }
            else if ( (receivedMsgPtr->cbch == FALSE) && (chnGrpTblApiPtr->cbch == TRUE) )
            {
               LOG_PRINT(LOG_INFO,"CBCH Deconfigured in ChnGrp");
               sendDelCbCellToCbsh(receivedMsgPtr->cellId, receivedMsgPtr->lac);
            }
            /*R2.4 change End */
         ret = updateChnGrpTable(receivedMsgPtr);
         if (ret == CLIB_SUCCESS)      
         {
            LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
            cfgSendAckToCm();
            return;   
         }
         else
         {
            LOG_PRINT(LOG_CRITICAL," update Failed , sending Nack");
            cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
            return;   
         }         
      } /* end of  if (statusRange) */
      else
      {
         LOG_PRINT(LOG_INFO," Modification Request with out of range value, sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;   
      }
   } /* End of Case: Modify ChnGrp Table*/    

} /* end of setChnGrpTableHandler */


/********************************* Function  Header********************************
Function Name	:  setCsNeighCellsTableHandler()
Parameters	:  void
Return type	:  void
Purpose		:  This function do following:
		   1. To add new entry in CsNeighCells table
		   2. To Modify the parameters in the CsNeighCells table 
Other Note	:  Function rewritten for On The Fly Changes
 ************************************************************************************/
void setCsNeighCellsTableHandler()
{
   CsNeighCellsTableApi* receivedMsgPtr = 
      ( CsNeighCellsTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   CsNeighCellsTableIndices apiCsNeighCellIndex = {0};
   CellPerTableIndices cellTableInd;
   CsNeighCellsTableApi* csNeighCellTblApiPtr = PNULL;
   CellPerTableApi *cellTableApiPtr = NULL;

   /* Flag is Set if any attribute value in CSNeighCell Table is to be changed */
   I_Bool flagParamChange = FALSE;  
   I_Bool statusRange = FALSE;
   I_S32  ret = 1;
   I_U32 rowsCount = 0;
   I_U32 numNeighbours = 0;
   I_U16 outSize;
   I_U16 cellIndex;
   OamsCfgCellhCsNeighCellsChange csNeighChangePtr;

   LOG_PRINT(LOG_INFO,"Entering Function : setCsNeighCellsTableHandler");

   /* Check if entry is present in DB or not */
   apiCsNeighCellIndex.lac            =  receivedMsgPtr->lac;
   apiCsNeighCellIndex.cellId         =  receivedMsgPtr->cellId;
   apiCsNeighCellIndex.neighborMcc    =  receivedMsgPtr->neighborMcc;
   apiCsNeighCellIndex.neighborMnc    =  receivedMsgPtr->neighborMnc;
   apiCsNeighCellIndex.neighborLac    =  receivedMsgPtr->neighborLac;
   apiCsNeighCellIndex.neighborCellId =  receivedMsgPtr->neighborCellId;

   ret = getCsNeighCellsTable(&apiCsNeighCellIndex, &csNeighCellTblApiPtr);   

   if (csNeighCellTblApiPtr != PNULL)
   {
      if( (receivedMsgPtr->cellType != csNeighCellTblApiPtr->cellType) ||
	        (receivedMsgPtr->relationType != csNeighCellTblApiPtr->relationType) ||
          (receivedMsgPtr->radioAccessType != csNeighCellTblApiPtr->radioAccessType) )
      {
         flagParamChange = TRUE;
      }

      if(flagParamChange)
      {
         LOG_PRINT(LOG_INFO,"setCsNeighCellsTableHandler : Change in Read-Only Attributes. Sending Nack");
         free(csNeighCellTblApiPtr);
         cfgSendNackToCm(CM_ERR_CHANGE_IN_ROSC_PARAM);
         return;
      }
      else
      {
         if(  (receivedMsgPtr->rxLevMinN == csNeighCellTblApiPtr->rxLevMinN) &&
            (receivedMsgPtr->hoMarginN == csNeighCellTblApiPtr->hoMarginN)  )
	       {
            free(csNeighCellTblApiPtr);
            LOG_PRINT(LOG_INFO,"setCsNeighCellsTableHandler : Modification Request with same value as in DB, sending Ack");
            cfgSendAckToCm();
	          return;
	       }
       	 else
       	 {
            free(csNeighCellTblApiPtr);
   	        statusRange = csNeighCellsTableRangeChk(receivedMsgPtr);    
            if(!statusRange)
            {
               LOG_PRINT(LOG_INFO,"Range Check Failed");
               cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
               return;
            }
       	    /* Consistency Check - IRxLevDIH(HoCtrlTable) < rxLevMinN */
	          statusRange = chkCnstForHoCtrlTable(receivedMsgPtr);
            if(statusRange)
   	        {
      	        LOG_PRINT(LOG_MAJOR,"setCsNeighCellsTableHandler : Consistency Check Failed - IRxLevDIH(HoCtrlTable) < rxLevMinN");
      	        cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
      	        return;
   	        }

            ret = updateCsNeighCellsTable(receivedMsgPtr);
            if(ret != DBLIB_SUCCESS)
	          {  
      	       LOG_PRINT(LOG_INFO,"Update Failed, Sending Nack");
               cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
               return;
	          }
      	    else
	          {
       	       LOG_PRINT(LOG_INFO,"setCsNeighCellsTableHandler : Update Successfull. Sending Ack to CM");
	             cfgSendAckToCm();
       	       return;
	          }
	       }
      }
   }

   statusRange = csNeighCellsTableRangeChk(receivedMsgPtr);
   if(!statusRange)
   {
      LOG_PRINT(LOG_INFO,"setCsNeighCellsTableHandler : Range Check Failed");
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return;
   }    

   statusRange = chkConsistencyForCsNeighCellTable(receivedMsgPtr);
   if(!statusRange)
   {
      LOG_PRINT(LOG_INFO,"setCsNeighCellsTableHandler : Consistency Check Failed");
      //cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
      return;
   }

   /* Consistency Check - IRxLevDIH(HoCtrlTable) < rxLevMinN */
   statusRange = chkCnstForHoCtrlTable(receivedMsgPtr);
   if(statusRange)
   {
      LOG_PRINT(LOG_MAJOR,"setCsNeighCellsTableHandler : Consistency Check Failed - IRxLevDIH(HoCtrlTable) < rxLevMinN");
      cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
      return;
   }

   /* Bug Fixed - Mantis #4996 : Start */
   statusRange = isRefFoundForArfcnBsicOfNeigh(receivedMsgPtr);
   if(TRUE == statusRange)
   {
      LOG_PRINT(LOG_INFO,"setCsNeighCellsTableHandler : Consistency Check Failed");
      cfgSendNackToCm(CM_ERR_CSNEIGHCELLS_CONSIST_CHECK_FAILED);
      return;
   }
   /* Bug Fixed - Mantis #4996 : End */

	 /* Send Neighbour Change Msg to CELLH if Cell is Unlocked */
	 cellTableInd.cellId = receivedMsgPtr->cellId;
	 cellTableInd.lac    = receivedMsgPtr->lac;
	 ret = getCellPerTable(&cellTableInd, &cellTableApiPtr);
	 if(ret != DBLIB_SUCCESS)
	 {
	    LOG_PRINT(LOG_INFO,"Cell is Not Configured at BSC");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
	 }
	 else if(cellTableApiPtr->adminState == UNLOCKED)
	 {
      if (
           receivedMsgPtr->radioAccessType == WCDMA_FDD
         )
         {
           free(cellTableApiPtr);
           LOG_PRINT(LOG_CRITICAL,"Neighbours belonging to WCDMA_FDD, addition is not allowed in Cell Unlock state");
           cfgSendNackToCm(CM_ERR_WCDMA_OPR_NOT_ALLOW_IN_CELL_UNLOCK_STATE);
           return;
         }
         else
         {  
	          free(cellTableApiPtr);
            getCellIndex(receivedMsgPtr->lac,receivedMsgPtr->cellId, &cellIndex);
	          csNeighChangePtr.cellId = receivedMsgPtr->cellId;
      	    csNeighChangePtr.lac    = receivedMsgPtr->lac;
	          csNeighChangePtr.cellIndex    = cellIndex;

          ret = insertCsNeighCellsTable(receivedMsgPtr);
          if(ret != DBLIB_SUCCESS)
          {
             LOG_PRINT(LOG_CRITICAL,"Insert in DB Failed, Sending Nack");
             cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
             return;
          }
          else
          {
	            LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE Msg to CELLH");
	            cfgSendMessage(&csNeighChangePtr, sizeof(OamsCfgCellhCsNeighCellsChange),
                             ENT_OAMS_CELLH, OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE, 0);

              LOG_PRINT(LOG_INFO,"Sending Ack to CM");
              cfgSendAckToCm();
           }
         }
	 }
	 else
	 {
					 free(cellTableApiPtr);
					 ret = insertCsNeighCellsTable(receivedMsgPtr);
					 if(ret != DBLIB_SUCCESS)
					 {
									 LOG_PRINT(LOG_CRITICAL,"Insert in DB Failed, Sending Nack");
									 cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
									 return;
					 }
					 cfgSendAckToCm();
					 LOG_PRINT(LOG_INFO,"Cell is Locked. Not send OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE Msg to CELLH");
	 }
   return;    
}

/********************************* Function  Header********************************
   Function Name:       setArfcnListTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in ArfcnList table
To Modify the parameters in the ArfcnList table 
Other Note:
 ************************************************************************************/
void setArfcnListTableHandler()
{
   ArfcnListTableApi* receivedMsgPtr = 
      ( ArfcnListTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   ArfcnListTableApi* arfcnListTblApiPtr = PNULL;
   ArfcnListTableIndices apiArfcnListIndex = {0};

   /* Flag is Set if any attribute value in ArfcnList Table is to be changed */
   I_Bool flagParamChange = FALSE;  
   I_Bool statusRange = FALSE;
   I_S32  ret = 1;
   I_U32  outRow = ZERO;
   I_U16  outSz = ZERO;

   LOG_PRINT(LOG_INFO," In setArfcnListTableHandler");

   /* Check if entry is present in DB or not */
   apiArfcnListIndex.band =  receivedMsgPtr->band;
   apiArfcnListIndex.arfcn =  receivedMsgPtr->arfcn;

   ret = getArfcnListTable(&apiArfcnListIndex, &arfcnListTblApiPtr);

   /* Case: Addition of Row in ArfcnList Table */
   if (arfcnListTblApiPtr == PNULL)
   {
      statusRange = arfcnListTableRangeChk(receivedMsgPtr);                
      if (statusRange)
      {
	       /* Check that Max Arfcns are already configured or not */
	       ret = getallArfcnListTable(&arfcnListTblApiPtr, &outRow, &outSz);
	       if(ret == DBLIB_SUCCESS)
	       {
	          free(arfcnListTblApiPtr);
	       }
	       if(outRow >= MAX_CONFIGURABLE_ARFCNS)
	       {
	          LOG_PRINT(LOG_MAJOR,"Maximum Arfcns are already Configured at BSC");
                  cfgSendAckToCm(CM_ERR_MAX_ENTRY_PRES);
                  return;
	       }

         ret = insertArfcnListTable(receivedMsgPtr ); 
         if (ret == CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
            cfgSendAckToCm();
            return;        
         }
         else
         {
            LOG_PRINT(LOG_DEBUG," Insert DB Failed, Sending Nack");
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return; 
         } 
      } /* end of if (statusRange) */
      else
      {
         LOG_PRINT(LOG_INFO," Range Chk Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }   
   }  /* end of Case: Addition of Row in ArfcnList Table */   
   else
   {
      flagParamChange = compareRcvdMsgAndDbEntry((void*) receivedMsgPtr,
            (void*) arfcnListTblApiPtr,
            sizeof(ArfcnListTableApi));
      free(arfcnListTblApiPtr);
      if (flagParamChange)
      {

         statusRange = arfcnListTableRangeChk(receivedMsgPtr);
         if (statusRange)
         {
            ret = updateArfcnListTable(receivedMsgPtr );
            if (ret == CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
               cfgSendAckToCm();
               return;
            }
            else
            {
               LOG_PRINT(LOG_CRITICAL," Update DB Failed, Sending Nack");
               cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
               return;
            }
         } /* end of if (statusRange) */
         else
         {
            LOG_PRINT(LOG_INFO," Range Chk Failed, Sending Nack");
            cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
            return;
         }
      }   
      else
      {
         LOG_PRINT(LOG_INFO," No Change in Params , Send Ack");
         cfgSendAckToCm();
         return;
      }
   }

} /* end of setArfcnListTableHandler */


/********************************* Function  Header********************************
   Function Name:       setAInterfaceTablehandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To handle Set Request for AInterface table

Other Note:
 ************************************************************************************/
void setAInterfaceTableHandler()
{
   /**************************************************************
      CFG will send 0 message to CM as all the attributes are
      "Read-Only" in this table.
    ***************************************************************/ 
   LOG_PRINT(LOG_INFO," In setAInterfaceTableHandler");
   LOG_PRINT(LOG_INFO," setAInterfaceHandler: Sending nack as Read-Only Table");
   cfgSendNackToCm(CM_ERR_SET_OBJ_NOT_ALLOWED);
   return; 

} /* end of setAinterfaceStackTraceConfigTableHandler */

#if 0 /* CS4.0 HA Stack Changes */
/********************************* Function  Header********************************
   Function Name:       setMtp3LinksetTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in Mtp3Linkset table
To Modify the parameters in the Mtp3Linkset table
Other Note:
 ************************************************************************************/
void setMtp3LinksetTableHandler()
{
   Mtp3LinksetTableApi* receivedMsgPtr = ( Mtp3LinksetTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   /* Flag is Set if any attribute value in Mtp3Linkset Table is to be changed */
   I_Bool status = FALSE;

   LOG_PRINT(LOG_INFO," In setMtp3LinksetTableHandler");
   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }

   {/* CCB Chnage Start - Change in BSC SW to NACK modification request of stack tables : Mantis Id-3198  */
      Mtp3LinksetTableApi  *mtp3LinksetTableDbPtr;
      Mtp3LinksetTableIndices mtp3LinksetTableIndices;
      mtp3LinksetTableIndices.MTP3LinksetlinksetID = receivedMsgPtr->MTP3LinksetlinksetID;
      if(CLIB_SUCCESS == getMtp3LinksetTable(&mtp3LinksetTableIndices, &mtp3LinksetTableDbPtr))
      {
         LOG_PRINT(LOG_MAJOR, "Modification on  Mtp3LinksetTable is not allowed");
         LOG_PRINT(LOG_INFO, "Mtp3LinkSet linksetId [%u] already configured",
            			mtp3LinksetTableIndices.MTP3LinksetlinksetID);
         LOG_PRINT(LOG_MAJOR, "Sending Failure to OMC/CLI with error code [%d]",
            					CM_ERR_OPERATION_NOT_ALLOWED);
         free(mtp3LinksetTableDbPtr);
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         return;
      }
   } /* CCB Change End */

   /* Send the message to the OIL */
   {
      Mtp3LinksetTableApi *mtp3LinksetTablePtr;
      mtp3LinksetTablePtr= AlocOrdBuf(sizeof(Mtp3LinksetTableApi));
      gStoredMsgBufPtr = (void*)mtp3LinksetTablePtr;
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284. Also unnecessary DB get removed*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy(((I_U8 *)mtp3LinksetTablePtr),
            (I_U8*)receivedMsgPtr,sizeof(Mtp3LinksetTableApi));
      status = cfgSendCmMessage((void * )gCfgMsgBuf, (sizeof(Mtp3LinksetTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL, BSC_API_SET_MTP3LINKSETTABLE,0);                
      cfgStartTimer();
   }
}
void setMtp3LinksetTableHandlerScmAck()
{
   Mtp3LinksetTableApi* receivedMsgPtr = ( Mtp3LinksetTableApi* )gStoredMsgBufPtr;
   Mtp3LinksetTableApi* mtp3LinksetTblApiPtr = PNULL;
   Mtp3LinksetTableIndices apiMtp3LinksetIndex = {0};
   I_S32  ret = 1;
   I_U32  intVal;
   Mtp3LinksetStsTableApi mtp3LinksetStsTable;
   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      DalocOrdBuf(gStoredMsgBufPtr);
      gStoredMsgBufPtr=NULL;
      return ;    

   }

   apiMtp3LinksetIndex.MTP3LinksetlinksetID = receivedMsgPtr->MTP3LinksetlinksetID;
   ret = getMtp3LinksetTable(&apiMtp3LinksetIndex, &mtp3LinksetTblApiPtr);
   if (mtp3LinksetTblApiPtr == PNULL)
   {
      ret = insertMtp3LinksetTable(receivedMsgPtr ); 
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
         cfgSendAckToCm();
         /*CCB #20 - insert row in Mtp3LinksetStsTableApi */
         mtp3LinksetStsTable.MTP3LinksetlinksetID = receivedMsgPtr->MTP3LinksetlinksetID;
         mtp3LinksetStsTable.oprState = DISABLED;
         intVal =  mtp3LinksetStsTable.MTP3LinksetlinksetID;
         LOG_PRINT(LOG_DEBUG, " Linkset = %d, operStatus = %d", intVal,  mtp3LinksetStsTable.oprState);
         if(insertMtp3LinksetStsTable(&mtp3LinksetStsTable) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_MAJOR,"insertMtp3LinksetStsTableApi FAILED");
         }
         DalocOrdBuf(gStoredMsgBufPtr);
         gStoredMsgBufPtr=NULL;
         return; 
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," Insert DB Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
         DalocOrdBuf(gStoredMsgBufPtr);
         gStoredMsgBufPtr=NULL;
         return; 
      } 
   } 
   else
   { 

      /* Case: Modify Mtp3Linkset Table */
      LOG_PRINT(LOG_INFO," updateMtp3LinksetTable ...");
      free(mtp3LinksetTblApiPtr);
      ret = updateMtp3LinksetTable(receivedMsgPtr);
      if (ret == CLIB_SUCCESS)      
      {
         LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
         cfgSendAckToCm();
         DalocOrdBuf(gStoredMsgBufPtr);
         gStoredMsgBufPtr=NULL;
         return;     
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," update Failed , sending Nack");
         DalocOrdBuf(gStoredMsgBufPtr);
         gStoredMsgBufPtr=NULL;
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         return; 
      }
   }/* end of Case: Modify Mtp3Linkset Table */   

}/* end of setMtp3LinkSetTableHandler */


/********************************* Function  Header********************************
   Function Name:       setMtp3RouteTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in Mtp3Route table
To Modify the parameters in the Mtp3Route table
Other Note:
 ************************************************************************************/
void        setMtp3RouteTableHandler()
{
   Mtp3RouteTableApi* receivedMsgPtr = ( Mtp3RouteTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   /* Flag is Set if any attribute value in Mtp3Route Table is to be changed */
   I_Bool status = FALSE;

   LOG_PRINT(LOG_INFO," In setMtp3RouteTableHandler");
   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }

   { /* CCB Chnage Start - Change in BSC SW to NACK modification request of stack tables : Mantis Id-3198  */
      Mtp3RouteTableApi *mtp3RouteTableDbPtr;
      Mtp3RouteTableIndices mtp3RouteTableIndices;
      mtp3RouteTableIndices.mtp3RouterouteID = receivedMsgPtr->mtp3RouterouteID;
      if (CLIB_SUCCESS == getMtp3RouteTable(&mtp3RouteTableIndices, &mtp3RouteTableDbPtr))
      {
         LOG_PRINT(LOG_MAJOR, "Modification on  Mtp3RouteTable is not allowed");
         LOG_PRINT(LOG_INFO, "Mtp3Route RouteId [%u] already configured",
            			mtp3RouteTableIndices.mtp3RouterouteID);
         LOG_PRINT(LOG_MAJOR, "Sending Failure to OMC/CLI with error code [%d]",
         				   CM_ERR_OPERATION_NOT_ALLOWED);
         free(mtp3RouteTableDbPtr);
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         return;
      }
   }/*CCB Change End*/

   {  

      /* Send the message to the OIL */  
      Mtp3RouteTableApi *mtp3RouteTablePtr=NULL;
      mtp3RouteTablePtr = (Mtp3RouteTableApi *)AlocOrdBuf(sizeof(Mtp3RouteTableApi));
      gStoredMsgBufPtr = (void*)mtp3RouteTablePtr;
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284. Also unnecessary DB get removed*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      /* Store the buffer for processing of OIL response  */


      memcpy((((I_U8 *)mtp3RouteTablePtr)),
            (I_U8*)receivedMsgPtr,sizeof(Mtp3RouteTableApi));
      status = cfgSendCmMessage((void * )gCfgMsgBuf, 
            (sizeof(Mtp3RouteTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL, BSC_API_SET_MTP3ROUTETABLE,0);
      cfgStartTimer("TSI_TRAU_INIT");
   }
}
void copyAndFreeStoredMsgBuff( void *ptr, I_U32 size )
{
   LOG_PRINT(LOG_INFO,"Entering copyAndFreeStoredMsgBuff function");
   memcpy(ptr,gStoredMsgBufPtr,size);
   if (gStoredMsgBufPtr!=NULL)
   {
      DalocOrdBuf(gStoredMsgBufPtr);
      gStoredMsgBufPtr= NULL;
   }
   LOG_PRINT(LOG_INFO,"exiting copyAndFreeStoredMsgBuff function");
}

void        setMtp3RouteTableHandlerScmAck()
{

   Mtp3RouteTableApi storedBuff ;
   Mtp3RouteTableApi* mtp3RouteTblApiPtr = PNULL;
   Mtp3RouteTableIndices apiMtp3RouteIndex = {0};

   I_S32  ret = 1;

   copyAndFreeStoredMsgBuff(&storedBuff,sizeof(Mtp3RouteTableApi));

   cfgStopTimer();
   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   { 
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return ;

   }

   apiMtp3RouteIndex.mtp3RouterouteID = storedBuff.mtp3RouterouteID;
   ret = getMtp3RouteTable(&apiMtp3RouteIndex, &mtp3RouteTblApiPtr);   


   if ((mtp3RouteTblApiPtr) == PNULL)
   {
      ret = insertMtp3RouteTable(&storedBuff);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," Insert DB Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {

      /* Case: Modify Mtp3Linkset Table */
      LOG_PRINT(LOG_INFO," update mtp3RouteTblApi...");
      ret = updateMtp3RouteTable(&storedBuff);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," update Failed , sending Nack");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
      free(mtp3RouteTblApiPtr);
   }/* end of Case: Modify Mtp3Linkset Table */
}

/********************************* Function  Header********************************
   Function Name:       setMtp3LinkSetStsTableHandler()
Parameters:          void
Return type:         void
Purpose:             To send request to SCM via OIL for adding/modify entry
in Mtp3LinkSetAdminState Table
Other Note:
 ************************************************************************************/
void          setMtp3LinkSetStsTableHandler()
{
   Mtp3LinksetStsTableApi* receivedMsgPtr =
      ( Mtp3LinksetStsTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   Mtp3LinksetStsTableApi *mtp3LinkSetStsTblPtr=NULL;

   /* flagParamChange is Set if any field in Mtp3LinkSetAdminState Table is changed */
   I_Bool status = FALSE;

   LOG_PRINT(LOG_INFO," In setMtp3LinkSetStsTableHandler");

   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }

   /* Send the message to the OIL */  
   mtp3LinkSetStsTblPtr = (Mtp3LinksetStsTableApi *)AlocOrdBuf(sizeof(Mtp3LinksetStsTableApi));
   gStoredMsgBufPtr = (void*)mtp3LinkSetStsTblPtr;
   if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284. Also unnecessary DB get removed*/
   {
      LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
      cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
      return;  
   }
   /* Store the buffer for processing of OIL response  */
   memcpy((((I_U8 *)mtp3LinkSetStsTblPtr)),
         (I_U8*)receivedMsgPtr,sizeof(Mtp3LinksetStsTableApi));

   status = cfgSendCmMessage((void * )gCfgMsgBuf,
         (sizeof(Mtp3LinksetStsTableApi)+sizeof(sCmMsg)),
         ENT_OAM_OIL, BSC_API_SET_MTP3LINKSETSTSTABLE,0);
   cfgStartTimer("TSI_TRAU_INIT");

} /* End of setMtp3LinkSetStsTableHandler */

/********************************* Function  Header********************************
   Function Name:       setMtp3LinkSetStsTableHandlerScmAck()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in Mtp3LinkSetAdminState table
To Modify the parameters in the Mtp3LinkSetAdminState table
Other Note:
 ************************************************************************************/
void setMtp3LinkSetStsTableHandlerScmAck()
{

   Mtp3LinksetStsTableApi* mtp3LnkAdminTblApiPtr = (Mtp3LinksetStsTableApi *) gStoredMsgBufPtr;
   Mtp3LinksetStsTableIndices apiLnkAdminIndex = {0};

   I_S32  ret = 1;

   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      DalocOrdBuf(gStoredMsgBufPtr);
      gStoredMsgBufPtr = NULL;
      return ;
   }

   apiLnkAdminIndex.MTP3LinksetlinksetID = mtp3LnkAdminTblApiPtr->MTP3LinksetlinksetID;
   /*unnecessary memcpy removed during changes for Mantis 2284*/
   ret = getMtp3LinksetStsTable(&apiLnkAdminIndex, &mtp3LnkAdminTblApiPtr);   

   if ((mtp3LnkAdminTblApiPtr) == PNULL)
   {
      ret = insertMtp3LinksetStsTable(mtp3LnkAdminTblApiPtr);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_INFO," Insert DB Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {

      /* Case: Modify Mtp3Linkset Table */
      LOG_PRINT(LOG_INFO," update mtp3linkAdmin...");
      ret = updateMtp3LinksetStsTable(mtp3LnkAdminTblApiPtr);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," update Failed , sending Nack");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
      free(mtp3LnkAdminTblApiPtr);
   }/* end of Case: Modify Mtp3Linkset Table */

   DalocOrdBuf(gStoredMsgBufPtr);
   gStoredMsgBufPtr = NULL; 
} /* end of setMtp3LinkSetAdminStateTableHandlerScmAck */

/********************************* Function  Header********************************
   Function Name:       setMtp3LinkTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in Mtp3Link table
To Modify the parameters in the Mtp3Link table
Other Note:
 ************************************************************************************/
void          setMtp3LinkTableHandler()
{
   Mtp3LinkTableApi* receivedMsgPtr =
      ( Mtp3LinkTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   /* Flag is Set if any attribute value in Mtp3LinkSetAdminState Table is to be changed */
   I_Bool status = FALSE;

   LOG_PRINT(LOG_INFO," In setMtp3LinkSetAdminStateTableHandler");

   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   { /* CCB Chnage Start - Change in BSC SW to NACK modification request of stack tables : Mantis Id-3198  */
      Mtp3LinkTableApi *mtp3LinkTableDbPtr;
      Mtp3LinkTableIndices mtp3LinkTableIndices;
      mtp3LinkTableIndices.mtp3LinklinkCode = receivedMsgPtr->mtp3LinklinkCode;
      mtp3LinkTableIndices.mtp3LinklinksetID = receivedMsgPtr->mtp3LinklinksetID;
      if (CLIB_SUCCESS == getMtp3LinkTable(&mtp3LinkTableIndices, &mtp3LinkTableDbPtr))
      {
         LOG_PRINT(LOG_MAJOR, "Modification on  Mtp3LinkTable is not allowed");
         LOG_PRINT(LOG_INFO, "Mtp3Link LinkCode [%u] and LinksetId [%u] already configured",
         	   		mtp3LinkTableIndices.mtp3LinklinkCode, 
				mtp3LinkTableIndices.mtp3LinklinksetID);
         LOG_PRINT(LOG_MAJOR, "Sending Failure to OMC/CLI with error code [%d]",
            				CM_ERR_OPERATION_NOT_ALLOWED);
         free(mtp3LinkTableDbPtr);
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         return;
      }
   }/*CCB Change End*/

   {
      /* Send the message to the OIL */  
      Mtp3LinkTableApi *mpt3LinkTblPtr=NULL;
      mpt3LinkTblPtr = (Mtp3LinkTableApi *)AlocOrdBuf(sizeof(Mtp3LinkTableApi));
      /* Store the buffer for processing of OIL response  */
      gStoredMsgBufPtr = (void*)mpt3LinkTblPtr;
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284. Also unnecessary DB get removed*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy((((I_U8 *)mpt3LinkTblPtr)),
            (I_U8*)receivedMsgPtr,sizeof(Mtp3LinkTableApi));

      status = cfgSendCmMessage((void * )gCfgMsgBuf,
            (sizeof(Mtp3LinkTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL,BSC_API_SET_MTP3LINKTABLE,0);

      cfgStartTimer("TSI_TRAU_INIT");
   }
}

void        setMtp3LinkTableHandlerScmAck()
{

   Mtp3LinkTableApi storedBuff ;
   Mtp3LinkTableApi* mtp3LnkTablePtr = PNULL;
   Mtp3LinkTableIndices apiLinkTblIndex = {0};
   Mtp3LinkStsTableApi mtp3LinkStsTableInd;

   I_S32  ret = 1;

   if ( gStoredMsgBufPtr == NULL )
   {
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return ;
   }


   copyAndFreeStoredMsgBuff(&storedBuff,sizeof(Mtp3LinkTableApi));

   cfgStopTimer();
   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return ;

   }

   apiLinkTblIndex.mtp3LinklinkCode = storedBuff.mtp3LinklinkCode;
   apiLinkTblIndex.mtp3LinklinksetID = storedBuff.mtp3LinklinksetID;

   ret = getMtp3LinkTable(&apiLinkTblIndex, &mtp3LnkTablePtr);   

   if ((mtp3LnkTablePtr) == PNULL)
   {
      ret = insertMtp3LinkTable(&storedBuff );
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
         cfgSendAckToCm();
	 /* Data added for table Mtp3LinkStsTable*/
	 mtp3LinkStsTableInd.MTP3LinklinksetID  = storedBuff.mtp3LinklinksetID;
	 mtp3LinkStsTableInd.MTP3Linklinkcode   = storedBuff.mtp3LinklinkCode;
	 mtp3LinkStsTableInd.oprState	        = DISABLED;
	 ret = insertMtp3LinkStsTable(&mtp3LinkStsTableInd);
	 if(ret != DBLIB_SUCCESS)
	 {
	     LOG_PRINT(LOG_MAJOR,"Insert in Mtp3LinkStsTable Failed");
	 }
      }
      else
      {
         LOG_PRINT(LOG_INFO," Insert DB Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {

      /* Case: Modify Mtp3Linkset Table */
      LOG_PRINT(LOG_INFO," update mtp3linkAdmin...");
      ret = updateMtp3LinkTable(&storedBuff);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," update Failed , sending Nack");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
      free(mtp3LnkTablePtr);
   }/* end of Case: Modify Mtp3Linkset Table */
} 


/********************************* Function  Header********************************
   Function Name:       setSccpSsnConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in SccpSsnConfig table
To Modify the parameters in the SccpSsnConfig table
Other Note:
 ************************************************************************************/
void          setSccpSsnConfigTableHandler()
{
   SccpSsnConfigTableApi* receivedMsgPtr =
      ( SccpSsnConfigTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   I_Bool status = FALSE;

   LOG_PRINT(LOG_INFO," In SccpSsnConfigTableApi");

   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   { /* CCB Chnage Start - Change in BSC SW to NACK modification request of stack tables : Mantis Id-3198  */
      SccpSsnConfigTableApi *sccpSsnConfigTableDbPtr;
      SccpSsnConfigTableIndices sccpSsnConfigTableIndices;
      sccpSsnConfigTableIndices.sccpSsnConfigssn = receivedMsgPtr->sccpSsnConfigssn;
      sccpSsnConfigTableIndices.sccpSsnConfigpc = receivedMsgPtr->sccpSsnConfigpc;
      sccpSsnConfigTableIndices.sccpSsnConfigni = receivedMsgPtr->sccpSsnConfigni;
      sccpSsnConfigTableIndices.sccpSsnConfigisLocal = receivedMsgPtr->sccpSsnConfigisLocal;
      if (CLIB_SUCCESS ==getSccpSsnConfigTable(&sccpSsnConfigTableIndices, &sccpSsnConfigTableDbPtr))
      {
         LOG_PRINT(LOG_MAJOR, "Modification on  SccpSsnConfigTable is not allowed");
         LOG_PRINT(LOG_INFO, "SccpSsnConfig Ssn [%u] ,Pc [%d] ,Ni [%u] and IsLocal [%u] already configured",
                sccpSsnConfigTableIndices.sccpSsnConfigssn,sccpSsnConfigTableIndices.sccpSsnConfigpc,
               sccpSsnConfigTableIndices.sccpSsnConfigni,sccpSsnConfigTableIndices.sccpSsnConfigisLocal);
         LOG_PRINT(LOG_MAJOR, "Sending Failure to OMC/CLI with error code [%d]",
         					   CM_ERR_OPERATION_NOT_ALLOWED);
         free(sccpSsnConfigTableDbPtr);
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         return;
      }
   }/*CCB Change End*/

   {
      /* Send the message to the OIL */  
      SccpSsnConfigTableApi *sccpSsnCfgPtr=NULL;
      sccpSsnCfgPtr = (SccpSsnConfigTableApi *)AlocOrdBuf(sizeof(SccpSsnConfigTableApi));
      /* Store the buffer for processing of OIL response  */
      gStoredMsgBufPtr = (void*)sccpSsnCfgPtr;
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284. Also unnecessary DB get removed*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy((((I_U8 *)sccpSsnCfgPtr)),
            (I_U8*)receivedMsgPtr,sizeof(SccpSsnConfigTableApi));

      status = cfgSendCmMessage((void * )gCfgMsgBuf,
            (sizeof(SccpSsnConfigTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL,BSC_API_SET_SCCPSSNCONFIGTABLE,0);

      cfgStartTimer("TSI_TRAU_INIT");
   }
}

void        setSccpSsnConfigTableHandlerScmAck()
{

   SccpSsnConfigTableApi storedBuff ;
   SccpSsnConfigTableApi* sccpSsnCfgTblPtr = PNULL;
   SccpSsnConfigTableIndices apiSccpSsnTblIndex = {0};
   SccpSsnStsTableApi  sccpSsnStsTable;

   I_S32  ret = 1;

   copyAndFreeStoredMsgBuff(&storedBuff,sizeof(SccpSsnConfigTableApi));

   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return ;

   }

   apiSccpSsnTblIndex.sccpSsnConfigssn = storedBuff.sccpSsnConfigssn;
   apiSccpSsnTblIndex.sccpSsnConfigpc = storedBuff.sccpSsnConfigpc;
   apiSccpSsnTblIndex.sccpSsnConfigni = storedBuff.sccpSsnConfigni;
   apiSccpSsnTblIndex.sccpSsnConfigisLocal = storedBuff.sccpSsnConfigisLocal;

   ret = getSccpSsnConfigTable(&apiSccpSsnTblIndex, &sccpSsnCfgTblPtr);   


   if ((sccpSsnCfgTblPtr) == PNULL)
   {
      ret = insertSccpSsnConfigTable(&storedBuff);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
         /*CCB #20 */
         sccpSsnStsTable.sccpSsnConfigssn = storedBuff.sccpSsnConfigssn; 
         sccpSsnStsTable.sccpSsnConfigpc = storedBuff.sccpSsnConfigpc; 
         sccpSsnStsTable.sccpSsnConfigni = storedBuff.sccpSsnConfigni; 
         sccpSsnStsTable.sccpSsnConfigisLocal = storedBuff.sccpSsnConfigisLocal; 
         sccpSsnStsTable.sccpSsnConfigstatus = DISABLED;
         if (insertSccpSsnStsTable(&sccpSsnStsTable) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_MAJOR,"insertSccpSsnStsTable FAILED");
         }
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_INFO," Insert DB Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {

      LOG_PRINT(LOG_INFO," update SccpSsnConfigTableApi...");
      ret = updateSccpSsnConfigTable(&storedBuff);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_INFO," update Failed , sending Nack");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
      free(sccpSsnCfgTblPtr);
   }
} 



/********************************* Function  Header********************************
   Function Name:       setSccpCssnConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in SccpCssnConfig table
To Modify the parameters in the SccpCssnConfig table
Other Note:
 ************************************************************************************/
void          setSccpCssnConfigTableHandler()
{
   SccpCSSNConfigTableApi* receivedMsgPtr =
      ( SccpCSSNConfigTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   I_Bool status = FALSE;

   LOG_PRINT(LOG_INFO," In SccpCSSNConfigTableApi");
   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   { /* CCB Chnage Start - Change in BSC SW to NACK modification request of stack tables : Mantis Id-3198  */
      SccpCSSNConfigTableApi *sccpCSSNConfigTableDbPtr;
      SccpCSSNConfigTableIndices sccpCSSNConfigTableIndices;
      sccpCSSNConfigTableIndices.sccpCSsnConfigssn = receivedMsgPtr->sccpCSsnConfigssn;
      sccpCSSNConfigTableIndices.sccpCSsnConfigpc = receivedMsgPtr->sccpCSsnConfigpc ;
      sccpCSSNConfigTableIndices.sccpCSsnConfigni = receivedMsgPtr->sccpCSsnConfigni;
      sccpCSSNConfigTableIndices.sccpCSsnConfigcssn = receivedMsgPtr->sccpCSsnConfigcssn;
      if (CLIB_SUCCESS == getSccpCSSNConfigTable(&sccpCSSNConfigTableIndices, &sccpCSSNConfigTableDbPtr))
      {
         LOG_PRINT(LOG_MAJOR, "Modification on  SccpCSSNConfigTable is not allowed");
         LOG_PRINT(LOG_INFO, "SccpCSsnConfig Ssn [%u] ,Pc [%d] ,Ni [%u] and CSsn [%u] already configured",
              sccpCSSNConfigTableIndices.sccpCSsnConfigssn,sccpCSSNConfigTableIndices.sccpCSsnConfigpc ,
              sccpCSSNConfigTableIndices.sccpCSsnConfigni,sccpCSSNConfigTableIndices.sccpCSsnConfigcssn);
         LOG_PRINT(LOG_MAJOR, "Sending Failure to OMC/CLI with error code [%d]",
         					   CM_ERR_OPERATION_NOT_ALLOWED);
         free(sccpCSSNConfigTableDbPtr);
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         return;
      }
   }/*CCB Change End*/

   {

      /* Send the message to the OIL */  
      SccpCSSNConfigTableApi *sccpSsnCfgPtr=NULL;
      sccpSsnCfgPtr = (SccpCSSNConfigTableApi *)AlocOrdBuf(sizeof(SccpCSSNConfigTableApi));
      /* Store the buffer for processing of OIL response  */
      gStoredMsgBufPtr = (void*)sccpSsnCfgPtr;
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284. Also unnecessary DB get removed*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy((((I_U8 *)sccpSsnCfgPtr)),
            (I_U8*)receivedMsgPtr,sizeof(SccpCSSNConfigTableApi));

      status = cfgSendCmMessage((void * )gCfgMsgBuf,
            (sizeof(SccpCSSNConfigTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL,BSC_API_SET_SCCPCSSNCONFIGTABLE,0);

      cfgStartTimer("TSI_TRAU_INIT");
   }
}

void        setSccpCssnConfigTableHandlerScmAck()
{

   SccpCSSNConfigTableApi storedBuff ;
   SccpCSSNConfigTableApi* sccpSsnCfgTblPtr = PNULL;
   SccpCSSNConfigTableIndices apiSccpSsnTblIndex = {0};

   I_S32  ret = 1;

   copyAndFreeStoredMsgBuff(&storedBuff,sizeof(SccpCSSNConfigTableApi));

   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return ;

   }

   apiSccpSsnTblIndex.sccpCSsnConfigssn = storedBuff.sccpCSsnConfigssn;
   apiSccpSsnTblIndex.sccpCSsnConfigpc = storedBuff.sccpCSsnConfigpc;
   apiSccpSsnTblIndex.sccpCSsnConfigni = storedBuff.sccpCSsnConfigni;
   apiSccpSsnTblIndex.sccpCSsnConfigcssn = storedBuff.sccpCSsnConfigcssn;

   ret = getSccpCSSNConfigTable(&apiSccpSsnTblIndex, &sccpSsnCfgTblPtr);   
   if ((sccpSsnCfgTblPtr) == PNULL)
   {
      ret = insertSccpCSSNConfigTable(&storedBuff );
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_INFO," Insert DB Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {

      LOG_PRINT(LOG_INFO," update SccpCSSNConfigTableApi...");
      ret = updateSccpCSSNConfigTable(&storedBuff);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," update Failed , sending Nack");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
      free(sccpSsnCfgTblPtr);
   }
} 
#endif
#if 0
/********************************* Function  Header********************************
   Function Name:       setGbInterfaceTableHandler()
Parameters:          void
Return type:         void
Purpose:             This function will be used to Modify the parameters in the GbInterface table  
Other Note:
************************************************************************************/
void setGbInterfaceTableHandler()
{
   GbInterfaceTableApi* receivedMsgPtr = ( GbInterfaceTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   GbInterfaceTableApi* gbIfTblApiPtr = PNULL;
   BssPsPreConfigTableApi* psPreConfigTablePtr = PNULL;
   /*Merger for Mantis #31470*/
   I_U32 i;
   CellPerTableIndices cellPerTableIndices;
   CellPerTableApi *pCellTab;
   I_Bool statusChangeVal = FALSE;
   /*Merger for Mantis #31470*/
   RepInfoTableApi *repInfoTableApiPtr = PNULL;
 
   I_Bool statusRange = FALSE;
   I_S32  ret = CM_FAILURE;
   I_U32 outRows = 0;
   I_U16 outSize = 0;

   LOG_PRINT(LOG_INFO,"In setGbInterfaceTableHandler");
   LOG_PRINT(LOG_INFO,"GbIfIndex = %u", receivedMsgPtr->gbIfIndex);

   
   /* Checks BssPsPreConfigTable must be configured already */
   ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &outRows, &outSize);
   if(DBLIB_SUCCESS == ret && 0 < outRows)
   {
      free(psPreConfigTablePtr);
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC. DB Call getallBssPsPreConfigTable returned [%d]",ret);
      cfgSendNackToCm(CM_ERR_GPRS_NOT_ALLOWED);
      return;
   }
/*
   * Check if BSS Admin State is LOCK or not * 
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO,"BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
*/   
   ret = getallGbInterfaceTable(&gbIfTblApiPtr, &outRows, &outSize);
   if (ret == DBLIBERR_PTOPAGE_HAS_NO_ROWS)
   {
      LOG_PRINT(LOG_MAJOR, "No rows present in gb Interface Table, sending Nack");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }

   /* Check if entry is present in DB or not */
   /* Case: Addition of Row in GbInterface Table */
   if (gbIfTblApiPtr->gbIfIndex != receivedMsgPtr->gbIfIndex)
   {
      LOG_PRINT(LOG_MAJOR,"Insert Operation not allowed in GbInterface Table");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES); 
      return;
   }/* End of Case: Addition of Row in GbInterface Table */  

   /* Case: Modify GbInterface Table */
   LOG_PRINT(LOG_INFO,"Updation in GbInterface Table");
   /*Changes PCU R2.5 Aricent -- START*/
   ret = doConsistencyChecksOnSetOnGbInterfaceTable(receivedMsgPtr);

   if( CM_SUCCESS != ret )
   {
      LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOngbInterfaceTable failed :: Sending Nack: Error Code [%d]", ret);
      cfgSendNackToCm(ret);
      free(gbIfTblApiPtr);
      return;
   }

   if (receivedMsgPtr->maxNumLeps != gbIfTblApiPtr->maxNumLeps)
   {
      LOG_PRINT(LOG_INFO,"setGbInterfaceTableHandler: Read only param- maxNumLeps is modified, sending Nack");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_CHANGE_IN_RO_PARAM);
      return;    
   }
   if (receivedMsgPtr->maxNumNsvcsOverFr != gbIfTblApiPtr->maxNumNsvcsOverFr)
   {
      LOG_PRINT(LOG_MAJOR,"setGbInterfaceTableHandler: Read only param- maxNumNsvcsOverFr is modified, sending Nack");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_CHANGE_IN_RO_PARAM);
      return;    
   }
   if (receivedMsgPtr->maxNumNsvcsOverIp != gbIfTblApiPtr->maxNumNsvcsOverIp)
   {
      LOG_PRINT(LOG_MAJOR,"setGbInterfaceTableHandler: Read only param- maxNumNsvcsOverIp is modified, sending Nack");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_CHANGE_IN_RO_PARAM);
      return;    
   }
/*Changes PCU R2.5 Aricent -- END*/
   if (receivedMsgPtr->maxNumReps != gbIfTblApiPtr->maxNumReps)
   {
      LOG_PRINT(LOG_INFO,"setGbInterfaceTableHandler: Read only param- maxNumReps is modified, sending Nack");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_CHANGE_IN_RO_PARAM);
      return;    
   }
   free(gbIfTblApiPtr);  
 
   statusRange = gbInterfaceTableRangeChk(receivedMsgPtr);
   if (statusRange)
   {  
      LOG_PRINT(LOG_INFO,"RangeChk passed, calling update");
      ret = updateGbInterfaceTable(receivedMsgPtr);
      if (ret == CLIB_SUCCESS)      
      {
         LOG_PRINT(LOG_INFO,"Update DB Successful, Sending Ack");
         sendBssUpdateInd2Psmsh();
         cfgSendAckToCm();
         return;      
      }
      else
      {
         LOG_PRINT(LOG_INFO,"update Failed , sending Nack");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         return; 
      } /* End of -if (statusRange) */
   } 
   else
   {                   
      LOG_PRINT(LOG_INFO,"Modification Request with out of range value, sending Nack");
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return;       
   }                   

} /* end of setGbInterfaceTableHandler */
#endif

   /*Merger for Mantis #31470 Funtion copied from R2-Code Base Multiple Changes in Function*/
void setGbInterfaceTableHandler()
{
   GbInterfaceTableApi* receivedMsgPtr = ( GbInterfaceTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   GbInterfaceTableApi* gbIfTblApiPtr = PNULL;
   BssPsPreConfigTableApi* psPreConfigTablePtr = PNULL;
   RepInfoTableApi *repInfoTableApiPtr = PNULL;
   
   I_U32 i;
   CellPerTableIndices cellPerTableIndices;
   CellPerTableApi *pCellTab;

 
   I_Bool statusRange = FALSE;
   I_Bool statusChangeVal = FALSE;
   I_S32  ret = CM_FAILURE;
   I_U32 outRows = 0;
   I_U16 outSize = 0;

   LOG_PRINT(LOG_INFO,"In setGbInterfaceTableHandler");
   LOG_PRINT(LOG_INFO,"GbIfIndex = %u", receivedMsgPtr->gbIfIndex);

   
   /* Checks BssPsPreConfigTable must be configured already */
   ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &outRows, &outSize);
   if(DBLIB_SUCCESS == ret && 0 < outRows)
   {
      free(psPreConfigTablePtr);
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC. DB Call getallBssPsPreConfigTable returned [%d]",ret);
      cfgSendNackToCm(CM_ERR_GPRS_NOT_ALLOWED);
      return;
   }
/*
   //Check if BSS Admin State is LOCK or not  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO,"BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
*/   
   ret = getallGbInterfaceTable(&gbIfTblApiPtr, &outRows, &outSize);
   if (ret == DBLIBERR_PTOPAGE_HAS_NO_ROWS)
   {
      LOG_PRINT(LOG_MAJOR, "No rows present in gb Interface Table, sending Nack");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }

   /* Check if entry is present in DB or not */
   /* Case: Addition of Row in GbInterface Table */
   if (gbIfTblApiPtr->gbIfIndex != receivedMsgPtr->gbIfIndex)
   {
      LOG_PRINT(LOG_MAJOR,"Insert Operation not allowed in GbInterface Table");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES); 
      return;
   }/* End of Case: Addition of Row in GbInterface Table */  

   /* Case: Modify GbInterface Table */
   LOG_PRINT(LOG_INFO,"Updation in GbInterface Table");
   /*Changes PCU R2.5 Aricent -- START*/
   ret = doConsistencyChecksOnSetOnGbInterfaceTable(receivedMsgPtr);

   if( CM_SUCCESS != ret )
   {
      LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOngbInterfaceTable failed :: Sending Nack: Error Code [%d]", ret);
      cfgSendNackToCm(ret);
      free(gbIfTblApiPtr);
      return;
   }

   if (receivedMsgPtr->maxNumLeps != gbIfTblApiPtr->maxNumLeps)
   {
      LOG_PRINT(LOG_INFO,"setGbInterfaceTableHandler: Read only param- maxNumLeps is modified, sending Nack");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_CHANGE_IN_RO_PARAM);
      return;    
   }
   if (receivedMsgPtr->maxNumNsvcsOverFr != gbIfTblApiPtr->maxNumNsvcsOverFr)
   {
      LOG_PRINT(LOG_MAJOR,"setGbInterfaceTableHandler: Read only param- maxNumNsvcsOverFr is modified, sending Nack");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_CHANGE_IN_RO_PARAM);
      return;    
   }
   if (receivedMsgPtr->maxNumNsvcsOverIp != gbIfTblApiPtr->maxNumNsvcsOverIp)
   {
      LOG_PRINT(LOG_MAJOR,"setGbInterfaceTableHandler: Read only param- maxNumNsvcsOverIp is modified, sending Nack");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_CHANGE_IN_RO_PARAM);
      return;    
   }
/*Changes PCU R2.5 Aricent -- END*/
   if (receivedMsgPtr->maxNumReps != gbIfTblApiPtr->maxNumReps)
   {
      LOG_PRINT(LOG_INFO,"setGbInterfaceTableHandler: Read only param- maxNumReps is modified, sending Nack");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_CHANGE_IN_RO_PARAM);
      return;    
   }
   if ((gbIfTblApiPtr->transportType != receivedMsgPtr->transportType) && (LOCKED != bssLock()))
   {
      LOG_PRINT(LOG_INFO,"setGbInterfaceTableHandler: Lock Bsc to change TransportType");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_BSS_UNLOCKED);
      return;    
   }
   /*
   if (gbIfTblApiPtr->adminState != receivedMsgPtr->adminState) 
   {
      LOG_PRINT(LOG_INFO,"setGbInterfaceTableHandler: Lock Unlock not handled");
      free(gbIfTblApiPtr);
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      return;    
   }*/

 
   statusRange = gbInterfaceTableRangeChk(receivedMsgPtr);
   if (statusRange != TRUE)
   {                   
      LOG_PRINT(LOG_INFO,"Modification Request with out of range value, sending Nack");
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return;       
   }                   
   if ( (gbIfTblApiPtr->nsei != receivedMsgPtr->nsei) || 
		(gbIfTblApiPtr->tFcC != receivedMsgPtr->tFcC) ||
		(gbIfTblApiPtr->tFcTh != receivedMsgPtr->tFcTh) ||
		(gbIfTblApiPtr->nMaxFcRep != receivedMsgPtr->nMaxFcRep) ||
        (gbIfTblApiPtr->transportType != receivedMsgPtr->transportType) ||
		(gbIfTblApiPtr->tWaitConfig != receivedMsgPtr->tWaitConfig) )
   {
	 statusChangeVal = TRUE;
   }
   /* Check whether any change is rxd for params */
   if (gbIfTblApiPtr->adminState != receivedMsgPtr->adminState) 
   {
      if (statusChangeVal == TRUE)
      {
         LOG_PRINT(LOG_INFO," Either change adminState or change the status");
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         free(gbIfTblApiPtr);
	     return;	 
      }
      if ((LOCKED != bssLock()))
	  {
	     if (receivedMsgPtr->adminState == LOCKED)
	     {
            gNseLockUnlockProc = I_TRUE;
         //Commented for Mantis #31633 & #31634 & #31639
        /*    for ( i = 0; i < CFG_MAX_NUM_CELLS;i++ )
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
                        *updateCellDataStruct(pCellTab->cellId, pCellTab->lac, 
                                lockeOrDisableInProgress, OAMS_RSN_PARENTOBJECTLOCKED);
                     }
                  free(pCellTab);
                  }
               }
	        }*/
         //Commented for Mantis #31633 & #31634 & #31639
		     sendPschNseLockReq(receivedMsgPtr->nsei);
			   gNseiData.nseiState = lockInProgress;
		 }
	     else if (receivedMsgPtr->adminState == UNLOCKED)
	     {
				gNseLockUnlockProc = I_TRUE;
				sendPsscmUnlockReq(OAMS_RSN_OPERATORINITIATED);
			  gNseiData.nseiState = unlockInProgress;
	     }
	  }
      else
	  {
	     ret = updateGbInterfaceTable(receivedMsgPtr);
         if (ret == CLIB_SUCCESS)      
         {
            LOG_PRINT(LOG_INFO,"Update DB Successful, Sending Ack");
			if (receivedMsgPtr->adminState == UNLOCKED)
			{
			  gNseiData.nseiState = unlocked;
              sendNseLockUnlockAlarm (receivedMsgPtr->nsei,receivedMsgPtr->adminState);
			}
			else
			{
			  gNseiData.nseiState = locked;
              sendNseLockUnlockAlarm (receivedMsgPtr->nsei,receivedMsgPtr->adminState);
			}
         }
         else
         {
            LOG_PRINT(LOG_INFO,"update Failed , sending Nack");
            cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
            free(gbIfTblApiPtr);
	        return;	 
         }
      }
   }
   else if ((statusChangeVal == TRUE) && (gbIfTblApiPtr->adminState == LOCKED))
   {
      LOG_PRINT(LOG_INFO,"RangeChk passed, calling update");
      ret = updateGbInterfaceTable(receivedMsgPtr);
      if (ret == CLIB_SUCCESS)      
      {
         LOG_PRINT(LOG_INFO,"Update DB Successful, Sending Ack");
         sendBssUpdateInd2Psmsh();
         gNseiData.nsei = receivedMsgPtr->nsei;
      }
      else
      {
         LOG_PRINT(LOG_INFO,"update Failed , sending Nack");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         free(gbIfTblApiPtr);
	     return;	 
      }
   }
   cfgSendAckToCm();
   free(gbIfTblApiPtr);  
} /* end of setGbInterfaceTableHandler */
   /*Merger for Mantis #31470*/

/********************************* Function  Header********************************
   Function Name:       setNsvcTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in NSVC table
To Modify the parameters in the NSVC table  
Other Note:
 ************************************************************************************/
/*Changes PCU R2.5 Aricent -- START*/
void setNsvcTableHandler()
{
   NsvcTableApi        *receivedMsgPtr = 
                                ( NsvcTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   NsvcTableApi        *nsvcTblApiPtr = NULL;
   NsvcTableIndices    apiNsvcIndex;
   NsvcStatusTableApi  nsvcStatusTableApiBuff;
   I_Bool              statusRange = FALSE;
   I_S32               ret = CM_FAILURE;
   I_U16               e1Id = 0;


   LOG_PRINT(LOG_INFO,"In setNsvcTableHandler");

   PRINT_HEX_DUMP(LOG_DEBUG, gCfgMsgBuf + sizeof(sCmMsg), sizeof(NsvcTableApi));

   LOG_PRINT(LOG_INFO,"Received NSVC ID : %u ", receivedMsgPtr->nsvcId);
   LOG_PRINT(LOG_INFO,"Received admin state : %u ", receivedMsgPtr->adminState);
   LOG_PRINT(LOG_INFO,"Received frChnId : %u ", receivedMsgPtr->frChnId);
   LOG_PRINT(LOG_INFO,"Received dlci : %u ", receivedMsgPtr->dlci);

  
   /* Check if entry is present in DB or not */
   apiNsvcIndex.nsvcId = receivedMsgPtr->nsvcId;

   ret = getNsvcTable(&apiNsvcIndex, &nsvcTblApiPtr);   
   
   /* Case: Addition of Row in NSVC Table */
   if (nsvcTblApiPtr == NULL)
   {
      LOG_PRINT(LOG_INFO,"Insertion in NSVC Table");
      ret = doConsistencyChecksOnSetOnNsvcTable(receivedMsgPtr, TRUE);

      if( CM_SUCCESS != ret )
      {
          LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnNsvcTable failed :: Sending Nack: Error Code [%d]", ret);
          cfgSendNackToCm(ret);
          return;
      }
      if (LOCKED != receivedMsgPtr->adminState)
      {
          LOG_PRINT(LOG_MAJOR, "nsvc id [%u] is not locked :: Sending Nack", receivedMsgPtr->nsvcId);
          cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);
          return;
      }
      statusRange = nsvcTableRangeChk(receivedMsgPtr);                
      if (statusRange)
      {
         ret = insertNsvcTable(receivedMsgPtr ); 
         if (CLIB_SUCCESS == ret)
         {
            initNsvcDataStruct(receivedMsgPtr->nsvcId);
            /*Adding in NSVC Status Table*/
            nsvcStatusTableApiBuff.nsvcId = receivedMsgPtr->nsvcId;
            nsvcStatusTableApiBuff.oprState = DISABLED;
            ret = insertNsvcStatusTable(&nsvcStatusTableApiBuff);
            if (CLIB_SUCCESS != ret)
            {
               LOG_PRINT(LOG_MAJOR,"Db Operation failed,NSVC ID[%u] could not be added into the DB Error code = [%d]", 
                         nsvcStatusTableApiBuff.nsvcId, ret );
               cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
               return;
            }
            cfgSendAckToCm();
            return; 
         } /* end of if (ret == CLIB_SUCCESS) */
         else
         {
            LOG_PRINT(LOG_MAJOR,"Insert DB Failed, Error Code = [%d], Sending Nack", ret);
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return;       
         }
      } /* end of if (statusRange) */
      else
      {
         LOG_PRINT(LOG_MAJOR,"Insert Row Operation with out of range value, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;    
      }   
   }/* End of Case: Addition of Row in NSVC Table */  
   else /* Modify Nsvc Table */
   {
      LOG_PRINT(LOG_INFO,"Calling nsvcObjectHandler()");
  
      /* If request is for NSVC Lock/Unlock and E1 coreesponding to that 
       * NSVC is LockInProgress or unlockInProgress send Nack*/
      if(nsvcTblApiPtr->adminState != receivedMsgPtr->adminState)
      {
         /* If Bss is in Lock in Prgress and request is for NSVC Lock/Unlock then send Nack */
         if (lockInProgress == gBssState)
         {
            cfgSendNackToCm(CM_ERR_BSS_LOCK_IN_PROGRESS);
            free(nsvcTblApiPtr);
            return;
         }
         /* If E1 for this Nsvc is in Lock in Progress or Unlock in progress send Nack */
         ret = getE1IdForNsvcId(nsvcTblApiPtr->nsvcId, &e1Id);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_INFO, "No E1 present for NsvcId %u, Error Code = [%d]", nsvcTblApiPtr->nsvcId, ret);
            free(nsvcTblApiPtr);
            return;
         }
         if(gE1Data[e1Id].e1State == unlockInProgress )
         {
            LOG_PRINT(LOG_INFO,"setNsvcTableHandler: Abis E1 Unlock in progress. Can not lock/unlock TRX. ");
            cfgSendNackToCm(CM_ERR_E1_UNLOCK_IN_PROGRESS);
            free(nsvcTblApiPtr);
            return;
         }
         else if(gE1Data[e1Id].e1State == lockInProgress)
         {
            LOG_PRINT(LOG_INFO,"setNsvcTableHandler: Abis E1 Lock in progress. Can not lock/unlock TRX. ");
            cfgSendNackToCm(CM_ERR_E1_LOCK_IN_PROGRESS);
            free(nsvcTblApiPtr);
            return;
         }
      }
      free(nsvcTblApiPtr);
      nsvcObjectHandler();
  }
} /* end of setNsvcTableHandler */
/*Changes PCU R2.5 Aricent -- END*/    

/********************************* Function  Header********************************
   Function Name:       setFrLinkTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in FRLink table
To Modify the parameters in the FRLink table 
Other Note:
 ************************************************************************************/
/*Changes PCU R2.5 Aricent -- START*/
void setFrLinkTableHandler()
{
   FrLinkTableApi *receivedMsgPtr = (FrLinkTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   FrLinkTableApi *frLinkTblApiPtr = NULL;
   FrLinkTableIndices apiFrLinkIndex;
   FrLinkStatusTableApi frLinkStatusTableApiBuff;
   I_Bool statusRange = FALSE;
   I_S32 ret = CM_FAILURE;
   
   LOG_PRINT(LOG_INFO,"In setFrLinkTableHandler");

   /* Check if entry is present in DB or not */
   apiFrLinkIndex.frChnId = receivedMsgPtr->frChnId;

   LOG_PRINT(LOG_INFO,"Received frChnId : %d ", receivedMsgPtr->frChnId);
   
   ret = getFrLinkTable(&apiFrLinkIndex, &frLinkTblApiPtr);
 
   /* Case: Addition of Row in FrLink Table */
   if (frLinkTblApiPtr == NULL)
   {
      
      LOG_PRINT(LOG_INFO,"Insertion on frLink table");
      statusRange = frLinkTableRangeChk(receivedMsgPtr);                
      if (!statusRange)
      {
         LOG_PRINT(LOG_MAJOR,"Attempting to perform insert Row Operation with out of range value, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;    
      }   
      ret = doConsistencyChecksOnSetOnFrLinkTable(receivedMsgPtr,TRUE);
      if( CM_SUCCESS != ret )
      {
         LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnFrLinkTable failed :: Sending Nack: Error Code [%d]", ret);
         cfgSendNackToCm(ret);
         return;
      }

      ret = insertFrLinkTable(receivedMsgPtr); 
      if (CLIB_SUCCESS == ret)
      {
         /*Adding in FR Link Status Table*/
         frLinkStatusTableApiBuff.frChnId = receivedMsgPtr->frChnId;
         frLinkStatusTableApiBuff.oprState = DISABLED;
         ret = insertFrLinkStatusTable(&frLinkStatusTableApiBuff);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_MAJOR,"Db Operation failed, Error Code = [%d] ", ret);
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return;
         }
         LOG_PRINT(LOG_INFO,"Insert DB Successful, Sending Ack");
         cfgSendAckToCm();
         return;       
      }
      else
      {
         LOG_PRINT(LOG_MAJOR,"Insert DB Failed, Error Code = [%d], Sending Nack", ret);
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
         return;       
      } 
   }/* End of Case: Addition of Row in FrLink Table */  

   /* Case: Modify FrLink Table */
   if (frLinkTblApiPtr != PNULL)  
   {
      
      LOG_PRINT(LOG_INFO,"Updation on frLink table");
      statusRange = frLinkTableRangeChk(receivedMsgPtr);                
      if (!statusRange)
      {
         LOG_PRINT(LOG_MAJOR,"Attempting to perform Update Row Operation with out of range value, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         free(frLinkTblApiPtr);
         return;    
      }   
      ret = doConsistencyChecksOnSetOnFrLinkTable(receivedMsgPtr,I_FALSE);
      if( CM_SUCCESS != ret )
      {
         LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnFrLinkTable failed :: Sending Nack: Error Code [%d]", ret);
         cfgSendNackToCm(ret);
         free(frLinkTblApiPtr);
         return;
      }
      ret = updateFrLinkTable(receivedMsgPtr);
      if(CLIB_SUCCESS != ret)
      {
         LOG_PRINT(LOG_MAJOR,"Update DB call updateFrLinkTable failed. Returned Error Code = [%u]", ret)
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED); 
         free(frLinkTblApiPtr);
         return;
      }
      
      LOG_PRINT(LOG_INFO,"updateFrLinkTable Successful, Sending Ack");
      cfgSendAckToCm();
      free(frLinkTblApiPtr);
   }/* End of Case: Modify FrLinkTable */ 

} /* end of setFrLinkTableHandler */
/*Changes PCU R2.5 Aricent -- END*/



/*Changes PCU R2.5 Aricent -- START*/
/********************************* Function  Header********************************
   Function Name:       setBssPsTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in BssPs table
To Modify the parameters in the BssPs table 
Other Note:
 ************************************************************************************/
void setBssPsTableHandler()
{
   BssPsTableApi *receivedMsgPtr = (BssPsTableApi*)(((I_U8 *)gCfgMsgBuf) + sizeof(sCmMsg));
   BssPsTableApi *bssPsTableApiPtr = PNULL;
   I_U32 outRows = 0;
   I_U16 outSize = 0;
   I_S32 ret = CM_FAILURE;
   BssPsPreConfigTableApi* psPreConfigTablePtr = PNULL; 
   
   LOG_PRINT(LOG_INFO,"In setBssPsTableHandler");
   LOG_PRINT(LOG_INFO,"bsspsId = %u",receivedMsgPtr->bssPsId );
   
   /* Checks BssPsPreConfigTable must be configured already */
   ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &outRows, &outSize);
   if(DBLIB_SUCCESS == ret && 0 < outRows)
   {
      /*Do Nothing*/
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC. DB Call getallBssPsPreConfigTable returned [%d]",ret);
      cfgSendNackToCm(CM_ERR_GPRS_NOT_ALLOWED);
      return;
   }
   
   if (LOCKED != bssLock())
   {
      LOG_PRINT(LOG_MAJOR, "Bss is not locked. Row cannot be modified");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;
   }
 
   ret = getallBssPsTable(&bssPsTableApiPtr, &outRows, &outSize);
   if (ret == CLIB_SUCCESS)
   {
      if (bssPsTableApiPtr->bssPsId != receivedMsgPtr->bssPsId)
      {
         LOG_PRINT(LOG_MAJOR, "bssPsId received in the message is not the same as present in DB, Sending Nack");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
         free(bssPsTableApiPtr);
         return;
      }
      free(bssPsTableApiPtr);
   }
   /* row addition */
   if (NULL == bssPsTableApiPtr)
   {
      LOG_PRINT(LOG_MAJOR,"Row insertion is not allowed, sending Nack", ret)
      cfgSendNackToCm(CM_ERR_ROWS_NOT_PRESENT);
      return;
   } 
   /*Perform Range Check*/
   if (TRUE != (bssPsTableRangeChk(receivedMsgPtr)))
   {
      LOG_PRINT(LOG_MAJOR,"Update Operation on BssPsTable with out of range value, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return;    
   }
   /*Perform Update Operation*/
   ret = updateBssPsTable(receivedMsgPtr);
   if (CLIB_SUCCESS == ret)
   {
      LOG_PRINT(LOG_INFO,"Update DB Successful, Sending Ack");
      cfgSendAckToCm();
      sendBssUpdateInd2GrhmAndPsmsh();
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"DB call updateBssPsTable failed. Returned Error Code = [%u]", ret)
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
   }
}/* end of setBssPsTableHandler */

/********************************* Function  Header********************************
   Function Name:       sendBssUpdateInd2GrhmAndPsmsh()
Parameters:          void
Return type:         void
Purpose:             This function sends 
                     OAMS_CFG_GRHM_BSS_INFO_UPD_IND to GRHM and 
                     OAMS_CFG_PSMSH_BSS_INFO_UPD_IND to PSMSH

Other Note:
 ************************************************************************************/
I_Void sendBssUpdateInd2GrhmAndPsmsh()
{
   OamsCfgGrhmBssInfoUpdInd oamsCfgGrhmBssInfoUpdIndBuff;
   OamsCfgPsmshBssInfoUpdInd oamsCfgPsmshBssInfoUpdIndBuff;
      
   LOG_PRINT(LOG_INFO,"Sending message OAMS_CFG_GRHM_BSS_INFO_UPD_IND to GRHM");
   cfgSendMessage(&oamsCfgGrhmBssInfoUpdIndBuff, sizeof(OamsCfgGrhmBssInfoUpdInd), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_BSS_INFO_UPD_IND, 0);
   LOG_PRINT(LOG_INFO,"Sending message OAMS_CFG_PSMSH_BSS_INFO_UPD_IND to PSMSH");
   cfgSendMessage(&oamsCfgPsmshBssInfoUpdIndBuff, sizeof(OamsCfgPsmshBssInfoUpdInd), ENT_PSAPP_PSMSH, OAMS_CFG_PSMSH_BSS_INFO_UPD_IND, 0);
}


/********************************* Function  Header********************************
Function Name:       sendBssUpdateInd2Psmsh()
Parameters:          void
Return type:         void
Purpose:             This function sends 
                     OAMS_CFG_PSMSH_BSS_INFO_UPD_IND to PSMSH

Other Note:
 ************************************************************************************/
I_Void sendBssUpdateInd2Psmsh()
{
   OamsCfgPsmshBssInfoUpdInd oamsCfgPsmshBssInfoUpdIndBuff;
      
   LOG_PRINT(LOG_INFO,"Sending message OAMS_CFG_PSMSH_BSS_INFO_UPD_IND to PSMSH");
   cfgSendMessage(&oamsCfgPsmshBssInfoUpdIndBuff, sizeof(OamsCfgPsmshBssInfoUpdInd), ENT_PSAPP_PSMSH, OAMS_CFG_PSMSH_BSS_INFO_UPD_IND, 0);
}
/*Changes PCU R2.5 Aricent -- END*/


/********************************* Function  Header********************************
   Function Name:       setLepInfoTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in LepInfo table
To Modify the parameters in the LepInfo table 
Other Note:
 ************************************************************************************/
/*Changes PCU R2.5 Aricent -- START*/
void setLepInfoTableHandler()
{
   LepInfoTableApi *receivedMsgPtr = (LepInfoTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   LepInfoTableApi *lepInfoTblApiPtr = PNULL;
   LepInfoTableIndices apiLepInfoIndex;

   I_Bool statusRange = FALSE;
   I_S32 ret = CM_FAILURE;
   I_Bool isAdd = FALSE;

   LOG_PRINT(LOG_INFO,"In setlepInfoTableHandler");
   /*LOG_PRINT(LOG_INFO,"lep = %u",receivedMsgPtr->lep);*/
   LOG_PRINT(LOG_INFO,"lep = %s",receivedMsgPtr->lep);
  
   /*apiLepInfoIndex.lep = receivedMsgPtr->lep;*/
   strncpy(apiLepInfoIndex.lep, receivedMsgPtr->lep, OAMS_CFG_LEP_LENGTH);
   /*apiLepInfoIndex.ipType = receivedMsgPtr->ipType;*/
   ret = getLepInfoTable(&apiLepInfoIndex, &lepInfoTblApiPtr);

   /* Case: Addition of Row in LepInfo Table */
   if (NULL == lepInfoTblApiPtr)
   {
      LOG_PRINT(LOG_INFO,"Insertion in Lepinfo Table");
      isAdd = TRUE;
      ret = doConsistencyChecksOnSetOnLepInfoTable(receivedMsgPtr, isAdd);

      if( CM_SUCCESS != ret )
      {
          LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnLepInfoTable :: Sending Nack: Error Code [%d]", ret);
          cfgSendNackToCm(ret);
          return;
      }
      statusRange = lepInfoTableRangeChk(receivedMsgPtr);                
      if (statusRange)
      {
         ret = insertLepInfoTable(receivedMsgPtr ); 
         if (ret == CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_MAJOR,"Insert DB Successful, Sending Ack");
            cfgSendAckToCm();
            return;       
         }
         else
         {
            LOG_PRINT(LOG_MAJOR,"Insert DB Failed, Error Code = [%d], Sending Nack", ret);
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return;       
         } 
      } /* end of if (statusRange) */
      else
      {
         LOG_PRINT(LOG_MAJOR,"Insert Row Operation with out of range value, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;    
      }   
   }  /* End Case: Addition of Row in LepInfo Table */

   if (NULL != lepInfoTblApiPtr)   /* Case: Modify LepInfo Table */
   {
      LOG_PRINT(LOG_INFO,"Updation in LepInfo Table");
      isAdd = FALSE;

      ret = doConsistencyChecksOnSetOnLepInfoTable(receivedMsgPtr, isAdd);

      if( CM_SUCCESS != ret )
      {
         LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnLepInfoTable :: Sending Nack: Error Code [%d]", ret);
         free(lepInfoTblApiPtr);
         cfgSendNackToCm(ret);
         return;
      }
      free(lepInfoTblApiPtr);   

      statusRange = lepInfoTableRangeChk(receivedMsgPtr);
      if (statusRange)
      {  
         LOG_PRINT(LOG_INFO,"RangeChk passed, calling update");
         ret = updateLepInfoTable(receivedMsgPtr);
         if (ret == CLIB_SUCCESS)      
         {
            LOG_PRINT(LOG_INFO,"Update DB Successful, Sending Ack");
            cfgSendAckToCm();
            return;      
         }
         else
         {
            LOG_PRINT(LOG_MAJOR,"DB call updateLepInfoTable failed. Returned Error Code = [%u]", ret)
            cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
            return; 
         } /* End of -if (statusRange) */
      } 
      else
      {
         LOG_PRINT(LOG_INFO,"Modification Request with out of range value, sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;       
      }                   
   }/* End of Case: Modify LepInfoTable */ 
   return;
} /* end of setLepInfoTableHandler */
/*Changes PCU R2.5 Aricent -- END*/

/********************************* Function  Header********************************
   Function Name:       setRepInfoTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in RepInfo table
To Modify the parameters in the RepInfo table 
Other Note:
 ************************************************************************************/
/*Changes PCU R2.5 Aricent -- START*/
void setRepInfoTableHandler()
{
   RepInfoTableApi *receivedMsgPtr = (RepInfoTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   RepInfoTableApi *repInfoTblApiPtr = PNULL;
   RepInfoTableIndices apiRepInfoIndex;
   I_Bool statusRange = FALSE;
   I_S32 ret = CM_FAILURE;
   I_Bool isAdd = FALSE;

   LOG_PRINT(LOG_INFO,"In setRepInfoTableHandler");
   /* Mantis 14769 --Start*/
   LOG_PRINT(LOG_INFO,"repInfoTableIndex = %u", receivedMsgPtr->repInfoTableIndex);
   LOG_PRINT(LOG_INFO,"rep = %s, repPort = %u", receivedMsgPtr->rep, receivedMsgPtr->repPort);
   /* Mantis 14769 --End*/

   
   /* Mantis 14769 --Start*/
   apiRepInfoIndex.repInfoTableIndex = receivedMsgPtr->repInfoTableIndex;
   /*strncpy(apiRepInfoIndex.rep, receivedMsgPtr->rep, OAMS_CFG_REP_LENGTH);*/
   /* Mantis 14769 --End*/
   /*apiRepInfoIndex.ipType = receivedMsgPtr->ipType; */
   ret = getRepInfoTable(&apiRepInfoIndex, &repInfoTblApiPtr);    

   /* Case: Addition of Row in RepInfo Table */
   if (NULL == repInfoTblApiPtr)
   {
      LOG_PRINT(LOG_INFO,"Insertion in RepInfo Table");
      isAdd = TRUE;

      ret = doConsistencyChecksOnSetOnRepInfoTable(receivedMsgPtr, isAdd);

      if( CM_SUCCESS != ret )
      {
         LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnRepInfoTable :: Sending Nack: Error Code [%d]", ret);
         cfgSendNackToCm(ret);
         return;
      }

      statusRange = repInfoTableRangeChk(receivedMsgPtr);                
      if (statusRange)
      {
         ret = insertRepInfoTable(receivedMsgPtr ); 
         if (ret == CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_INFO,"Insert DB Successful, Sending Ack");
            cfgSendAckToCm();
            return; 
         }
         else if (ret == DBLIBERR_DIO_UNIQUENESS_FAILED)
         {
            /* get data on the primary key if success then the rep ip and port combo has failed 
                else primary key failure veena 
            */
            apiRepInfoIndex.repInfoTableIndex = receivedMsgPtr->repInfoTableIndex ;
            
            if (CLIB_SUCCESS == getRepInfoTable(&apiRepInfoIndex, &repInfoTblApiPtr))
            {
                LOG_PRINT(LOG_MAJOR,"Insert DB Failed, Error Code = [%d], Sending Nack", ret);
                cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            }
            else 
            {
                LOG_PRINT(LOG_MAJOR,"Insert DB Failed, Secondary Key violation , Sending Nack", ret);
                cfgSendNackToCm(CM_ERR_INS_REP_PORT_COMB_NOT_UNIQ);
                if (NULL != repInfoTblApiPtr)
                {
                    free(repInfoTblApiPtr);
                    repInfoTblApiPtr = NULL;
                }
            }
            return; 
         }
         else 
         {
            LOG_PRINT(LOG_MAJOR,"Insert DB Failed, Error Code = [%d], Sending Nack", ret);
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            return;      
         } 
      } /* end of if (statusRange) */
      else
      {
         LOG_PRINT(LOG_MAJOR,"Insert Row Operation with out of range value, Sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;    
      }  
   }  /* End of Case: Addition of Row in LepInfo Table */

   if (NULL != repInfoTblApiPtr)   /* Case: Modify RepInfo Table */
   {
      LOG_PRINT(LOG_INFO,"Updation in RepInfo Table");
      isAdd = FALSE;

      ret = doConsistencyChecksOnSetOnRepInfoTable(receivedMsgPtr, isAdd);

      if( CM_SUCCESS != ret )
      {
         LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnRepInfoTable :: Sending Nack: Error Code [%d]", ret);
         cfgSendNackToCm(ret);
         free(repInfoTblApiPtr);
         return;
      }
       
      free(repInfoTblApiPtr);      
      
      statusRange = repInfoTableRangeChk(receivedMsgPtr);
      if (statusRange)
      {  
         LOG_PRINT(LOG_INFO,"RangeChk passed, calling update");
         ret = updateRepInfoTable(receivedMsgPtr);
         if (ret == CLIB_SUCCESS)      
         {
            LOG_PRINT(LOG_INFO,"Update DB Successful, Sending Ack");
            cfgSendAckToCm();
            return;      
         }
         else
         {
            LOG_PRINT(LOG_MAJOR,"DB call updateRepInfoTable failed. Returned Error Code = [%u]", ret)
            cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
            return; 
         } /* End of -if (statusRange) */
      } 
      else
      {
         LOG_PRINT(LOG_MAJOR,"Modification Request with out of range value, sending Nack");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;       
      }                   
   }/* End of Case: Modify RepInfoTable */ 

} /* end of setRepInfoTableHandler */
/*Changes PCU R2.5 Aricent -- END*/

#if 0 /* CS4.0 HA Stack Changes */
/********************************* Function  Header********************************
   Function Name:       setSksCommonTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in SksCommon table
To Modify the parameters in the SksCommon table
Other Note:
 ************************************************************************************/
void          setSksCommonTableHandler()
{
   SksCommonTableApi* receivedMsgPtr =
      ( SksCommonTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   I_Bool status = FALSE;

   LOG_PRINT(LOG_INFO," In SksCommonTableApi");

   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   {

      /* Send the message to the OIL */  
      SksCommonTableApi *sksCmTblPtr=NULL;
      sksCmTblPtr = (SksCommonTableApi *)AlocOrdBuf(sizeof(SksCommonTableApi));
      /* Store the buffer for processing of OIL response  */
      gStoredMsgBufPtr = (void*)sksCmTblPtr;
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284. Also unnecessary DB get removed*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy((((I_U8 *)sksCmTblPtr)),
            (I_U8*)receivedMsgPtr,sizeof(SksCommonTableApi));

      status = cfgSendCmMessage((void * )gCfgMsgBuf,
            (sizeof(SksCommonTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL,BSC_API_SET_SKSCOMMONTABLE,0);

      cfgStartTimer();
   }
}

void        setSksCommonTableHandlerScmAck()
{

   SksCommonTableApi storedBuff ;
   SksCommonTableApi* sksCommonTablePtr = PNULL;
   SksCommonTableIndices sksCommonTableIndex = {0};

   I_S32  ret = 1;

   copyAndFreeStoredMsgBuff(&storedBuff,sizeof(SksCommonTableApi));
   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return ;

   }

   sksCommonTableIndex.sksCommonopc = storedBuff.sksCommonopc;

   ret = getSksCommonTable(&sksCommonTableIndex, &sksCommonTablePtr);   

   if ((sksCommonTablePtr) == PNULL)
   {
      ret = insertSksCommonTable(&storedBuff );
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_INFO," Insert DB Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {

      LOG_PRINT(LOG_INFO," update SksCommonTableApi...");
      ret = updateSksCommonTable(&storedBuff);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_INFO," update Failed , sending Nack");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
      free(sksCommonTablePtr);
   }
} 


/********************************* Function  Header********************************
   Function Name:       setSksLinkstartTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in sksLinkStart table
Other Note:
 ************************************************************************************/


void          setSksLinkstartTableHandler()
{
   SksLinkstartTableApi* receivedMsgPtr =
      ( SksLinkstartTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   I_Bool status = FALSE;

   LOG_PRINT(LOG_INFO," In SksLinkstartTableApi");
   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   {

      /* Send the message to the OIL */  
      SksLinkstartTableApi *sksCmTblPtr=NULL;
      sksCmTblPtr = (SksLinkstartTableApi *)AlocOrdBuf(sizeof(SksLinkstartTableApi));
      /* Store the buffer for processing of OIL response  */
      gStoredMsgBufPtr = (void*)sksCmTblPtr;
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284. Also unnecessary DB get removed*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy((((I_U8 *)sksCmTblPtr)),
            (I_U8*)receivedMsgPtr,sizeof(SksLinkstartTableApi));

      status = cfgSendCmMessage((void * )gCfgMsgBuf,
            (sizeof(SksLinkstartTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL,BSC_API_SET_SKSLINKSTARTTABLE,0);

      cfgStartTimer("TSI_TRAU_INIT");
   }

}

void        setSksLinkstartTableHandlerScmAck()
{

   SksLinkstartTableApi storedBuff ;
   SksLinkstartTableApi* sksLinkStartTblPtr = PNULL;
   SksLinkstartTableIndices apiSksLinkstartIndex = {0};

   I_S32  ret = 1;

   copyAndFreeStoredMsgBuff(&storedBuff,sizeof(SksLinkstartTableApi));

   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return ;

   }

   apiSksLinkstartIndex.sksLinkStartLink = storedBuff.sksLinkStartLink;

   ret = getSksLinkstartTable(&apiSksLinkstartIndex, &sksLinkStartTblPtr);   

   if ((sksLinkStartTblPtr) == PNULL)
   {
      ret = insertSksLinkstartTable(&storedBuff );
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_INFO," Insert DB Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {

      LOG_PRINT(LOG_INFO," update SksLinkstartTableApi...");
      ret = updateSksLinkstartTable(&storedBuff);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," update Failed , sending Nack");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
      free(sksLinkStartTblPtr);
   }
}
#endif

void setSysOmcRegisterTableHandler()
{
   SysOmcRegisterTableApi* receivedMsgPtr = ( SysOmcRegisterTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   SysOmcRegisterTableApi* sysOmcRegTblApiPtr = PNULL;
   I_U32 outRows;
   I_U16 outSize;

   LOG_PRINT(LOG_INFO,"Inside setSysOmcRegisterTableHandler function");
   if ( getallSysOmcRegisterTable(&sysOmcRegTblApiPtr,&outRows,&outSize) == CLIB_SUCCESS ) 
   {
      if(outRows == 1)
      {   
         if(sysOmcRegTblApiPtr->sysOmcIndex == receivedMsgPtr->sysOmcIndex)
         {
            LOG_PRINT(LOG_CRITICAL,"Index in recevied message has matched with index present in DB");
            if(updateSysOmcRegisterTable(receivedMsgPtr) == CLIB_SUCCESS)  
            {
               LOG_PRINT(LOG_INFO,"Updation of SysOmcRegisterTable is successfull");
               cfgSendAckToCm();
            }
            else
            {
               LOG_PRINT(LOG_CRITICAL,"Updation of SysOmcRegisterTable is failed");
               cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
            }
         }
         else
         {
            LOG_PRINT(LOG_CRITICAL,"Index in recevied message is not matching with index present in DB");
            cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
         }
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL,"More than one row present in DB");
         cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      }
   }
   else
   {
      if(insertSysOmcRegisterTable(receivedMsgPtr) == CLIB_SUCCESS)  
      {
         LOG_PRINT(LOG_INFO,"Inseration of SysOmcRegisterTable is successful");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL,"Inseration of SysOmcRegisterTable is failed");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      }
   }
}

void setSysOmcConfigTableHandler()
{
   SysOmcConfigTableApi* receivedMsgPtr = ( SysOmcConfigTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   SysOmcConfigTableApi* sysOmcConfigTblApiPtr = PNULL;
   I_U32 outRows;
   I_U16 outSize;

   LOG_PRINT(LOG_INFO,"Inside setSysOmcConfigTableHandler finction");
   if ( getallSysOmcConfigTable(&sysOmcConfigTblApiPtr,&outRows,&outSize) == CLIB_SUCCESS ) 
   {
      if(outRows == 1)
      { 
         if(memcmp(sysOmcConfigTblApiPtr->sysOmcConfigactiveCardHwId,receivedMsgPtr->sysOmcConfigactiveCardHwId,20) == 0)
         {
            if(updateSysOmcConfigTable(receivedMsgPtr) == CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_INFO,"updation of SysOmcConfigTable is successful");
               cfgSendAckToCm();
            }
            else
            {
               LOG_PRINT(LOG_CRITICAL,"updation of SysOmcConfigTable is failed");
               cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
            }
         }
         else
         {
            LOG_PRINT(LOG_CRITICAL,"Index in received is message is not matching with index in DB"); 
            cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
         }
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL,"More than one row present in DB");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      }
   }
   else
   {
      if(insertSysOmcConfigTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"Inseration of SysOmcConfigTable is successful");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL,"Inseration of SysOmcConfigTable is failed");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
}

void setPtdcConfigTableHandler() 
{
   PtdcConfigTableApi* receivedMsgPtr = ( PtdcConfigTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   PtdcConfigTableApi* PtdcConfigTableApiPtr = PNULL;
   I_U32 outRows;
   I_U16 outSize;

   LOG_PRINT(LOG_INFO," In setPtdcConfigTableHandler");

   /* Bug Fixed - Mantis# 5621 : Start */
   #if 0
   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_CRITICAL," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   #endif
   /* Bug Fixed - Mantis# 5621 : End */

   if(getallPtdcConfigTable(&PtdcConfigTableApiPtr,&outRows,&outSize)  == CLIB_SUCCESS)  
   {
      if(outRows == 1)
      {
         if(receivedMsgPtr->ptdcCfgCfgIndex == PtdcConfigTableApiPtr->ptdcCfgCfgIndex)
         {
            if(ptdcCfgTableRangeChk(receivedMsgPtr) == TRUE)
            {
               if( (receivedMsgPtr->pdcCfgPeriodicCSAppTimer != receivedMsgPtr->pdcCfgPeriodicPSAppTimer) ||
                   (receivedMsgPtr->pdcCfgPeriodicCSAppTimer != receivedMsgPtr->pdcCfgPeriodicCSStackTimer) ||
                   (receivedMsgPtr->pdcCfgPeriodicCSAppTimer != receivedMsgPtr->pdcCfgPeriodicPSStackTimer) || 
                   (receivedMsgPtr->pdcCfgPeriodicCSAppTimer != receivedMsgPtr->pdcCfgPeriodicPlatformTimer ) ||
                   (receivedMsgPtr->pdcCfgPeriodicCSAppTimer != receivedMsgPtr->pdcCfgPeriodicCERTimer) ) 
               {
                  LOG_PRINT(LOG_CRITICAL,"Value of All Performance Timer and CER timer is not same");
                  cfgSendNackToCm(CM_ERR_CONSISTENCY_CHECK_FAILED);
               } 
               else if ((receivedMsgPtr->pdcCfgPeriodicCSAppTimer % 300) != 0)
               {
                  LOG_PRINT(LOG_CRITICAL,"Value of All Performance Timer and CER timer is not in multiple of 300(5 mins.)");
                  cfgSendNackToCm(CM_ERR_CONSISTENCY_CHECK_FAILED);
               } 
               else if(updatePtdcConfigTable(receivedMsgPtr) == CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_INFO,"Updation of PtdcConfigTable is successful");
                  cfgSendAckToCm();
               }
               else
               {
                  LOG_PRINT(LOG_CRITICAL,"Updation of PtdcConfigTable is failed");
                  cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
               }
            }
            else
            {
               LOG_PRINT(LOG_CRITICAL,"Range check failed for recevied message");
               cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
            }
         }
         else
         {
            LOG_PRINT(LOG_CRITICAL,"Index in recevied message is not matching with index present in DB");
            cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
         }
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL,"More than one entry present in DB");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      }
   }
   else
   {
      /* Bug Fixed - Mantis#5763 : Start */
      LOG_PRINT(LOG_MAJOR,"Insert On PtdcConfigTable is Not Allowed");
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      #if 0
      if(ptdcCfgTableRangeChk(receivedMsgPtr) == TRUE)
      {
         if(insertPtdcConfigTable(receivedMsgPtr) == CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_INFO,"Inseration of PtdcConfigTable is successful");
            cfgSendAckToCm();
         }
         else
         {
            LOG_PRINT(LOG_CRITICAL,"Inseration of PtdcConfigTable is failed");
            cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
         }
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL,"Range check failed for received message");
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      }
      #endif
      /* Bug Fixed - Mantis#5763 : End */
   }
}

#if 0 /* CS4.0 HA Stack Changes */
/********************************* Function  Header********************************
   Function Name:       setSksGenCfgTableHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in SksGenConfig table
To Modify the parameters in the SksGenConfig table
Other Note:
 ************************************************************************************/


void          setSksGenCfgTableHandler()
{
   SksGenConfigTableApi* receivedMsgPtr =
      ( SksGenConfigTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   I_Bool status = FALSE;

   LOG_PRINT(LOG_INFO," In SksGenConfigTableApi");
   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   {

      /* Send the message to the OIL */  
      SksGenConfigTableApi *sksCmTblPtr=NULL;
      sksCmTblPtr = (SksGenConfigTableApi *)AlocOrdBuf(sizeof(SksGenConfigTableApi));
      /* Store the buffer for processing of OIL response  */
      gStoredMsgBufPtr = (void*)sksCmTblPtr;
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284. Also unnecessary DB get removed*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy((((I_U8 *)sksCmTblPtr)),
            (I_U8*)receivedMsgPtr,sizeof(SksGenConfigTableApi));

      status = cfgSendCmMessage((void * )gCfgMsgBuf,
            (sizeof(SksGenConfigTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL,BSC_API_SET_SKSGENCONFIGTABLE,0);

      cfgStartTimer("TSI_TRAU_INIT");
   }
}

void        setSksGenCfgTableHandlerScmAck()
{

   SksGenConfigTableApi storedBuff ;
   SksGenConfigTableApi* sksGenPtr = PNULL;
   SksGenConfigTableIndices apiSksGenCfgIndex = {0};

   I_S32  ret = 1;

   copyAndFreeStoredMsgBuff(&storedBuff,sizeof(SksGenConfigTableApi));

   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return ;

   }

   apiSksGenCfgIndex.stackType = storedBuff.stackType;
   //apiSksGenCfgIndex.sksGenCfgstackIndex = storedBuff.sksGenCfgstackIndex;

   ret = getSksGenConfigTable(&apiSksGenCfgIndex, &sksGenPtr);   

   if ((sksGenPtr) == PNULL)
   {
      ret = insertSksGenConfigTable(&storedBuff );
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," Insert DB Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {

      LOG_PRINT(LOG_INFO," update SksGenConfigTableApi...");
      ret = updateSksGenConfigTable(&storedBuff);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_INFO," update Failed , sending Nack");
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
      free(sksGenPtr);
   }
} 

void setBssapPcSsnConfigTableHandler()
{
   BssapPcSsnConfigTableApi* receivedMsgPtr =
      ( BssapPcSsnConfigTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   /* Flag is Set if any attribute value BssapPcSsnConfig in Table is to be changed */
   I_Bool status = FALSE;

   LOG_PRINT(LOG_INFO," In setBssapPcSsnConfigTableHandler");

   /* Check if BSS Admin State is LOCK or not */  
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   { /* CCB Chnage Start - Change in BSC SW to NACK modification request of stack tables : Mantis Id-3198  */
      BssapPcSsnConfigTableApi *bssapPcSsnConfigTableDbPtr;
      BssapPcSsnConfigTableIndices bssapPcSsnConfigTableIndices;
      bssapPcSsnConfigTableIndices.bssapPcSsnConfignwID = receivedMsgPtr->bssapPcSsnConfignwID;
      if (CLIB_SUCCESS == getBssapPcSsnConfigTable(&bssapPcSsnConfigTableIndices, &bssapPcSsnConfigTableDbPtr))
      {
         LOG_PRINT(LOG_MAJOR, "Modification on  BssapPcSsnConfigTable is not allowed");
         LOG_PRINT(LOG_INFO, "BssapPcSsnConfig NwID [%u] already configured",
         		   bssapPcSsnConfigTableIndices.bssapPcSsnConfignwID );
         LOG_PRINT(LOG_MAJOR, "Sending Failure to OMC/CLI with error code [%d]",
         			   CM_ERR_OPERATION_NOT_ALLOWED);
         free(bssapPcSsnConfigTableDbPtr);
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         return;
      }
   }/*CCB Change End*/

   /* Send the message to the OIL */
   {
      BssapPcSsnConfigTableApi *bssapPcSsnConfigTablePtr;
      bssapPcSsnConfigTablePtr = AlocOrdBuf( sizeof(BssapPcSsnConfigTableApi));
      gStoredMsgBufPtr = (void*)bssapPcSsnConfigTablePtr;
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284. Also unnecessary DB get removed*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }

      memcpy(((I_U8 *)bssapPcSsnConfigTablePtr),
            (I_U8*)receivedMsgPtr, sizeof(BssapPcSsnConfigTableApi));
      status = cfgSendCmMessage((void * )gCfgMsgBuf,
            (sizeof(BssapPcSsnConfigTableApi) + sizeof(sCmMsg)),
            ENT_OAM_OIL, BSC_API_SET_BSSAPPCSSNCONFIGTABLE,0);                
      cfgStartTimer();
   }
} /* end of setBssapPcSsnConfigTableHandler */


void setBssapPcSsnConfigTableHandlerScmAck()
{
   BssapPcSsnConfigTableApi* receivedMsgPtr =
      ( BssapPcSsnConfigTableApi* )gStoredMsgBufPtr;
   BssapPcSsnConfigTableApi* bssapPcSsnCfgTblApiPtr = PNULL;
   BssapPcSsnConfigTableIndices apiBssapPcSsnCfgIndex = {0};
   I_S32  ret = 1;

   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      DalocOrdBuf(gStoredMsgBufPtr);
      gStoredMsgBufPtr=NULL;
      return ;    
   }

   apiBssapPcSsnCfgIndex.bssapPcSsnConfignwID =  receivedMsgPtr->bssapPcSsnConfignwID;
   ret = getBssapPcSsnConfigTable(&apiBssapPcSsnCfgIndex, &bssapPcSsnCfgTblApiPtr);

   if (bssapPcSsnCfgTblApiPtr == PNULL)
   {
      ret = insertBssapPcSsnConfigTable(receivedMsgPtr); 
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Insert DB Successful, Sending Ack");
         cfgSendAckToCm();
         DalocOrdBuf(gStoredMsgBufPtr);
         gStoredMsgBufPtr=NULL;
         return; 
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," Insert DB Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
         DalocOrdBuf(gStoredMsgBufPtr);
         gStoredMsgBufPtr=NULL;
         return; 
      } 
   } 
   else
   { 

      /* Case: Modify BssapPcSsnConfig Table */
      LOG_PRINT(LOG_INFO," updateBssapPcSsnConfigTable ...");
      free(bssapPcSsnCfgTblApiPtr);
      ret = updateBssapPcSsnConfigTable(receivedMsgPtr);
      if (ret == CLIB_SUCCESS)      
      {
         LOG_PRINT(LOG_INFO," Update DB Successful, Sending Ack");
         cfgSendAckToCm();
         DalocOrdBuf(gStoredMsgBufPtr);
         gStoredMsgBufPtr=NULL;
         return;     
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," update Failed , sending Nack");
         DalocOrdBuf(gStoredMsgBufPtr);
         gStoredMsgBufPtr=NULL;
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         return; 
      }
   }/* end of Case: Modify BssapPcSsnConfig Table */   
}/* end of setBssapPcSsnConfigTableHandlerScmAck */
#endif

void copyAndFreeStoredMsgBuff(void *ptr, I_U32 size)
{
   LOG_PRINT(LOG_INFO,"Entering copyAndFreeStoredMsgBuff function");
   memcpy(ptr,gStoredMsgBufPtr,size);
   if (gStoredMsgBufPtr!=NULL)
      DalocOrdBuf(gStoredMsgBufPtr);
   gStoredMsgBufPtr= NULL;
   LOG_PRINT(LOG_INFO,"exiting copyAndFreeStoredMsgBuff function");
}

/* CS3.0 Changes : Start */
/********************************* Function  Header**************************
   Function Name:       setHoCtrlHandler()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
For Modifying HO Control parameters
Addition of HO Control parameters

Other Note: Added for CS3.0
 ****************************************************************************/
void setHoCtrlTableHandler()
{
   HoCtrlTableApi* receivedMsgPtr = NULL;
   receivedMsgPtr = ( HoCtrlTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   HoCtrlTableApi* hoCtrlTableApiPtr = PNULL;
   HoCtrlTableIndices hoCtrlTableIndex;
   CellPerTableApi *cellPerTablePtr = PNULL;
   CellPerTableIndices cellPerTableIndex;
   I_Bool flagParamChange = FALSE;  
   I_Bool statusRange = FALSE;
   I_S32  ret = 1; 
   I_U32 adminStateOfCell = UNLOCKED;

   LOG_PRINT(LOG_INFO," In setHoCtrlTableHandler");

   cellPerTableIndex.lac = receivedMsgPtr->lac;
   cellPerTableIndex.cellId = receivedMsgPtr->cellId;
   ret = getCellPerTable(&cellPerTableIndex, &cellPerTablePtr);

   if(cellPerTablePtr == PNULL)
   {
      LOG_PRINT(LOG_INFO ,"There is no entry in CellTable for the given cell"); 
      cfgSendNackToCm(CM_ERR_CELL_NOT_FOUND);
      return;
   }

   adminStateOfCell = cellPerTablePtr->adminState;
   free(cellPerTablePtr);

   statusRange = hoCtrlTableRangeChk(receivedMsgPtr);

   if(!statusRange)
   {
      LOG_PRINT(LOG_INFO," setHoCtrlTableHandler: RangeChk failed, sending Nack");  
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return; 
   }

   if ( !hoCtrlTablePerformConsistencyCheck(receivedMsgPtr))
   {
     LOG_PRINT(LOG_CRITICAL,"hoCtrlTablePerformConsistencyCheck : consistancy failed.");
     cfgSendNackToCm(CM_ERR_HOCTRL_CONSIST_CHK_FAILED);
      return ;
   }

   hoCtrlTableIndex.cellId = receivedMsgPtr->cellId;
   hoCtrlTableIndex.lac = receivedMsgPtr->lac;
   ret = getHoCtrlTable(&hoCtrlTableIndex,&hoCtrlTableApiPtr);

   /* Addition of Row */
   if (PNULL == hoCtrlTableApiPtr)
   {
      LOG_PRINT(LOG_INFO," setHoCtrlTableHandler: Addition of row in HoCtrl Table");
      ret = insertHoCtrlTable(receivedMsgPtr);
      if (ret == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," setHoCtrlTableHandler: new row added successfully, sending Ack");
         cfgSendAckToCm();
         return;
      }
      else
      {
         LOG_PRINT(LOG_INFO," setHoCtrlTableHandler: insertHoCtrlTable Failed, sending Nack");
         cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
         return;
      }
   } /* end of Addition of Row */       

   /* Case: Modifying HoCtrl Table */
   if (hoCtrlTableApiPtr != PNULL)
   {
      LOG_PRINT(LOG_INFO," setHoCtrlTableHandler: Modifying HoCtrl Table. Calling compare"); 
      flagParamChange = compareRcvdMsgAndDbEntry((void*)receivedMsgPtr,(void*)hoCtrlTableApiPtr,sizeof(HoCtrlTableApi));
      if (flagParamChange)
      {
         if(((receivedMsgPtr->multibandReporting != hoCtrlTableApiPtr->multibandReporting) ||
             (receivedMsgPtr->qSearch_I != hoCtrlTableApiPtr->qSearch_I) ||
             (receivedMsgPtr->qSearch_C_Initial != hoCtrlTableApiPtr->qSearch_C_Initial) ||
             (receivedMsgPtr->fddQmin != hoCtrlTableApiPtr->fddQmin) ||
             (receivedMsgPtr->fddQminOffset != hoCtrlTableApiPtr->fddQminOffset)) &&
             (adminStateOfCell == UNLOCKED))
         {
            LOG_PRINT(LOG_DEBUG," setHoCtrlTableHandler: Cell should be Locked to modify multibandReporting, qSearch_I, qSearch_C_Initial, fddQmin and fddQminOffset in HoCtrl Table");
            free(hoCtrlTableApiPtr);
            cfgSendNackToCm(CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE);
            return;
         }
 
         ret = updateHoCtrlTable(receivedMsgPtr);
         if (ret == CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_INFO," setHoCtrlTableHandler: row updated successfully, sending Ack");
            cfgSendAckToCm();
            free(hoCtrlTableApiPtr);
            return;
         }
         else
         {
            LOG_PRINT(LOG_INFO," setHoCtrlTableHandler: updateHoCtrlTable Failed, sending Nack");
            cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
            free(hoCtrlTableApiPtr);
            return;
         }
      }
      else
      {
         LOG_PRINT(LOG_INFO," Same parameter values as in DB, Sending ack");  
         cfgSendAckToCm();
         free(hoCtrlTableApiPtr);
         return;    
      } /*end of else of -if (flagParamChange) */ 
   } /*End of Case: Modifying Table */
}/* end of sethoCtrlTableHandler */

/********************************* Function  Header*****************************
   Function Name   : setBicTableHandler()
Parameters   : None
Return type   : I_Void
Purpose      : Handle Set Request message received from OMC/CLI
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void setBicTableHandler()
{
   BicTableApi*          receivedMsgPtr = ( BicTableApi* )(((I_U8 *)gCfgMsgBuf ) + 
                            sizeof(sCmMsg));
   BicTableIndices       bicTableIndexPtr;
   BicTableApi*          bicTableApiPtr = PNULL;
   I_S32                 dbStatus = -1;
   I_U32                 i=ZERO;

   LOG_PRINT(LOG_INFO,"Entering Function : setBicTableHandler");
/*Changes For R2.2 : Start */
   /* Check BIC is already added or not */
   bicTableIndexPtr.bicId = receivedMsgPtr->bicId;
   dbStatus = getBicTable(&bicTableIndexPtr, &bicTableApiPtr);

   if(DBLIB_SUCCESS == dbStatus)
   {
      if(getIndex(receivedMsgPtr->bicId,&i) == CFG_FAILURE)
      {
        LOG_PRINT(LOG_MAJOR,"setBicTableHandler : getIndex failed for Bic Id %d",receivedMsgPtr->bicId);
        cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
        free(bicTableApiPtr);
        return;
      }
      if( gBtsData[i].btsState == unlockInProgress)
      {
         LOG_PRINT(LOG_DEBUG,"setBicTableHandler : UNLOCK IN PROGRESS State");
         cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
         free(bicTableApiPtr);
         return;
      }
      if( gBtsData[i].btsState == lockInProgress)
      {
         LOG_PRINT(LOG_DEBUG,"setBicTableHandler : LOCK IN PROGRESS State");
         cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
         free(bicTableApiPtr);
         return;
      }
      

      /* Modification request received for BIC */
      LOG_PRINT(LOG_DEBUG,"setBicTableHandler : Modification request for \
            btsId : %d",receivedMsgPtr->bicId);
      if (!(compareRcvdMsgAndDbEntry((void*)receivedMsgPtr,
               (void*)bicTableApiPtr,sizeof(BicTableApi))))
      {
         LOG_PRINT(LOG_INFO,"setBicTableHandler : Received parameter values are same as in DB");
         cfgSendAckToCm();
         free(bicTableApiPtr);
         return;
      }

      if(((receivedMsgPtr->adminState != bicTableApiPtr->adminState) 
          && (receivedMsgPtr->btsConnectivityState != bicTableApiPtr->btsConnectivityState)) 
        ||((receivedMsgPtr->adminState != bicTableApiPtr->adminState) 
          && (receivedMsgPtr->btsReset == RESET))
        || ((receivedMsgPtr->btsConnectivityState != bicTableApiPtr->btsConnectivityState) 
          && (receivedMsgPtr->btsReset == RESET)))
      {
       LOG_PRINT(LOG_DEBUG,"setBicTableHandler : Simultaneous Request are not Allowed");
       cfgSendNackToCm(CM_ERR_SIMULTANOUS_OPERATION_NOT_ALLOWED);
       free(bicTableApiPtr);
       return;
      }
      if (receivedMsgPtr->numTrx != bicTableApiPtr->numTrx ||
         receivedMsgPtr->e1Id != bicTableApiPtr->e1Id ||
         receivedMsgPtr->btsType != bicTableApiPtr->btsType ||
         strcmp(receivedMsgPtr->btsName, bicTableApiPtr->btsName) != 0) 
      {
         LOG_PRINT(LOG_DEBUG,"setBicTableHandler : Modification not allowed on RO-SC parameter");
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         free(bicTableApiPtr);
         return;
      }
      /*if (receivedMsgPtr->btsClockSource != bicTableApiPtr->btsClockSource)
      {
        LOG_PRINT(LOG_DEBUG,"setBicTableHandler:btsClockSource Modification not allowed as RO parameter");
        cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
        free(bicTableApiPtr);
      }
      if (receivedMsgPtr->localSwitchingSupport != bicTableApiPtr->localSwitchingSupport)
      {
        LOG_PRINT(LOG_DEBUG,"setBicTableHandler: localSwitchingSupport Modification not allowed as RO parameter");
        cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
        free(bicTableApiPtr);
      }
      if (receivedMsgPtr->maxStepSize != bicTableApiPtr->maxStepSize)
      {
        LOG_PRINT(LOG_DEBUG,"setBicTableHandler:maxStepSize Modification not allowed as RO parameter");
        cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
        free(bicTableApiPtr);
      }
    */
      if(receivedMsgPtr->adminState != bicTableApiPtr->adminState) 
      {
         bicLockUnlockHandler();
      }
      else if(receivedMsgPtr->btsConnectivityState != bicTableApiPtr->btsConnectivityState)
      {
        if ((receivedMsgPtr->btsType==R2_BTS_IP)||(receivedMsgPtr->btsType==R3_BTS))
        {
           LOG_PRINT(LOG_DEBUG,"setBicTableHandler : Modification not allowed in btsConnectivityState \
           for R2_BTS_IP/R3 BTS with bic Id %d",receivedMsgPtr->bicId);
           cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
           free(bicTableApiPtr);
           return;
        } 
        btsConnectDisConnectHandler(bicTableApiPtr); 
      } 
      else if(receivedMsgPtr->btsReset == RESET)
      {
        if (receivedMsgPtr->btsType==R3_BTS)
        {
           LOG_PRINT(LOG_DEBUG,"setBicTableHandler : for R3 BTS with bic Id Reset is not Allowed %d",
           receivedMsgPtr->bicId);
           cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
           free(bicTableApiPtr);
           return;
        } 

        btsResetHandler(); 
      } 
      /*Changes for BSC R2.3.4 Starts*/ 
      else
      {
          if(receivedMsgPtr->satFlag != bicTableApiPtr->satFlag)
          {
             if(btsSetSatFlagHandler(bicTableApiPtr) == I_FALSE)
             {
               free(bicTableApiPtr);
               return;
             } 
          } 
      /*Changes for BSC R2.3.4 Ends*/ 
          if (receivedMsgPtr->clusterId != bicTableApiPtr->clusterId)
          {
            if(btsSetClusterIdHandler() == I_FALSE)
            {
               free(bicTableApiPtr);
               return;
            }
          }
          if (receivedMsgPtr->maxRfPwrConf != bicTableApiPtr->maxRfPwrConf)
          {
            if(btsSetMaxRfPwrConfHandler(bicTableApiPtr) == I_FALSE)
            {
               free(bicTableApiPtr);
               return;
            }
          }
      }
      
      free(bicTableApiPtr);
/*Changes For R2.2 : End */
   }
   else
   {
      I_U16 instCount = ZERO;
      I_U32 noOfBicCount = ZERO;
      I_U16 outSize = ZERO;
      I_S32 dbStatus ;
      BicTableApi *bicTableApiPtr;
      /*Check Maxmimum No Of BIC/BTS resources supported */
      if (INST_SUCCESS != GetInstCount(ENT_OAMS_BICH, BICHM_ACT_CLID, &instCount)) {
         LOG_PRINT(LOG_INFO,"[%s] GetInstCount call failed",__func__);
         cfgSendNackToCm(CM_ERR_DB_FAILED);
         return ;
      }
      dbStatus = getallBicTable(&bicTableApiPtr,&noOfBicCount,&outSize);
      if(CLIB_SUCCESS != dbStatus  && DBLIBERR_PTOPAGE_HAS_NO_ROWS != dbStatus) {
         LOG_PRINT(LOG_INFO,"[%s] getallBicTable call failed",__func__);
         cfgSendNackToCm(CM_ERR_DB_FAILED);
         return ;
      }
      free(bicTableApiPtr);
      if (noOfBicCount >= instCount) {
         LOG_PRINT(LOG_INFO,"[%s] MAX BIC/BTS count reached [Bic/Bts:%u][Ins:%u]",__func__,noOfBicCount,instCount);
         cfgSendNackToCm(CM_ERR_MAX_NUM_BTS_EXCEED);
         return ;
      }
      /* BIC is not added already. Going to add new BIC at BSC*/
      LOG_PRINT(LOG_INFO,"setBicTableHandler : Going to Add New BIC for \
            btsId : %d btsType %d at BSC",receivedMsgPtr->bicId,receivedMsgPtr->btsType);/* R2.8*/
      addBicTableHandler();

      LOG_PRINT(LOG_INFO,"setBicTableHandler : After Adding Bic ");
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : setBicTableHandler");
}


/********************************* Function  Header*****************************
   Function Name   : setTrxTableHandler()
Parameters   : None
Return type   : I_Void
Purpose      : It handle set request received from OMC/CLI
Other Note   : Added for BSC CS2.2
 *******************************************************************************/
I_Void setTrxTableHandler()
{
   TrxTableApi* receivedMsgPtr = ( TrxTableApi* )(((I_U8 *)gCfgMsgBuf ) + 
         sizeof(sCmMsg));
   TrxTableIndices trxTableIndexPtr;
   TrxTableApi* trxTableApiPtr = PNULL;
   objectState state;
   

   I_S32  dbStatus = -1;
   I_U32 e1Id;
   I_U32 i;

   LOG_PRINT(LOG_INFO,"Entering Function : setTrxTableHandler");
   LOG_PRINT(LOG_DEBUG,"setTrxTableHandler : Set Request is Received for \
         ptrxId : %d trx Location %d ",receivedMsgPtr->ptrxId,receivedMsgPtr->trxLocation);

   /* Check TRX is already added or not */
   trxTableIndexPtr.ptrxId = receivedMsgPtr->ptrxId;
   dbStatus = getTrxTable(&trxTableIndexPtr, &trxTableApiPtr);

   if(DBLIB_SUCCESS != dbStatus)
   {
      /* TRX is not added already. Going to add new TRX at BSC*/
      I_U16 instCount = ZERO;
      I_U32 noOfTrxCount = ZERO;
      I_U16 outSize = ZERO;
      I_S32 dbStatus ;
      TrxTableApi* trxTableApiPtr = PNULL;
      /*Check Maxmimum No Of BIC/BTS resources supported */
      if (INST_SUCCESS != GetInstCount(ENT_OAMS_TRXH, TRXH_ACT_CLID, &instCount)) {
         LOG_PRINT(LOG_INFO,"[%s] GetInstCount call failed",__func__);
         cfgSendNackToCm(CM_ERR_DB_FAILED);
         return;
      }
      dbStatus = getallTrxTable(&trxTableApiPtr,&noOfTrxCount,&outSize);
      if(CLIB_SUCCESS != dbStatus  && DBLIBERR_PTOPAGE_HAS_NO_ROWS != dbStatus) {
         LOG_PRINT(LOG_INFO,"[%s] getallTrxTable call failed",__func__);
         cfgSendNackToCm(CM_ERR_DB_FAILED);
         return ;
      }
      free(trxTableApiPtr);
      if (noOfTrxCount >= instCount) {
         LOG_PRINT(LOG_INFO,"[%s] MAX TRX count reached [Trx:%u][Ins:%u]",__func__,noOfTrxCount,instCount);
         cfgSendNackToCm(CM_ERR_MAX_NUM_TRX_EXCEED);
         return ;
      }
      LOG_PRINT(LOG_INFO,"setTrxTableHandler : Going to Add New TRX at BSC");
      if(UNLOCKED != receivedMsgPtr->adminState)
      {
         addTrxTableHandler();
      }
      else
      {
         /* Received Request has adminState Unlocked. Rejecting request */
         LOG_PRINT(LOG_INFO,"setTrxTableHandler : Add TrxTable Request \
               has adminState as UNLOCK");
         cfgSendNackToCm(CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE);
      }
   }
   else
   {
       state=getPtrxState();
       if (state == lockInProgress ) 
       {
	          LOG_PRINT(LOG_INFO,"Received message cannot be handled in LOCK-IN-PROGRESS State");
            cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
	          free(trxTableApiPtr);
	          return;
       }
       if (state == unlockInProgress ) 
       {
	          LOG_PRINT(LOG_INFO,"Received message cannot be handled in UNLOCK-IN-PROGRESS State");
            cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
	          free(trxTableApiPtr);
	          return;
       }

      /* TRX is already added. 
       * Check request is for Updation of TrxTable or Lock/Unlock */
/* Changes for R2.2 : Start */
      if((trxTableApiPtr != PNULL) && 
            (  receivedMsgPtr->adminState == trxTableApiPtr->adminState &&
	       receivedMsgPtr->trxReset == trxTableApiPtr->trxReset &&
	       receivedMsgPtr->trxPwrAction == trxTableApiPtr->trxPwrAction
	    )
/* Changes for R2.2 : End  */
	)
      {
         /* Received Request is to update TrxTable */
         if(UNLOCKED == receivedMsgPtr->adminState)
         {
            /* Before Updating a Table its adminState must be LOCKED.
             * Sending NACK to OMC/CLI */
            LOG_PRINT(LOG_INFO,"setTrxTableHandler : Update TrxTable Request has adminState as UNLOCK");
            /***Mantis 15378 : Fix Start***/ 
            //cfgSendNackToCm(CM_ERR_OBJ_ALREADY_UNLOCKED); // Mantis 7217
            cfgSendAckToCm(); 
            /***Mantis 15378 : Fix End***/ 
         }
         else
         {
            LOG_PRINT(LOG_INFO,"setTrxTableHandler : Going to Update TrxTable");
            updateTrxTableHandler(trxTableApiPtr);
         }
      }
/* Changes for R2.2 : Start */
      else if((trxTableApiPtr != PNULL) && 
            (  receivedMsgPtr->adminState != trxTableApiPtr->adminState &&
               receivedMsgPtr->trxReset   == trxTableApiPtr->trxReset &&
               receivedMsgPtr->trxPwrAction == trxTableApiPtr->trxPwrAction
	    ))
/* Changes for R2.2 : End  */
	    
      {
        /* Mantis 27791 starts */
        if(getIndex(receivedMsgPtr->bicId,&i) == CFG_FAILURE)
        {
          LOG_PRINT(LOG_MAJOR,"setTrxTableHandler : getIndex failed for Bic Id %d",receivedMsgPtr->bicId);
          cfgSendNackToCm(CM_ERR_PARENT_OBJ_DOES_NOT_EXISTS);
          free(trxTableApiPtr);
          return;
        }
        if(( gBtsData[i].btsState == unlockInProgress) || ( gBtsData[i].btsState == lockInProgress))
        {
          LOG_PRINT(LOG_DEBUG,"setBicTableHandler : LOCK/UNLOCK IN PROGRESS State");
          cfgSendNackToCm(CM_ERR_PARENT_OPERATION_IN_PROGRESS);
          free(trxTableApiPtr);
          return;
        }
        /* Mantis 27791 ends */

        if((receivedMsgPtr->trxLocation!=TRX_LOCATION_R2_BTS_IP)&&(receivedMsgPtr->trxLocation!=TRX_LOCATION_R3_BTS))/*changes for R2.8*/
        {   
          /* Received Request is for Trx Lock/Unlock  */ 
          /*Changes for CS4.0 : Abis E1 Lock/Unlock Start*/
          /* Abis E1 Lock\Unlock should not be in progress*/
          if(getE1ForTRX(receivedMsgPtr->ptrxId, &e1Id)!= CLIB_SUCCESS)
          {
            LOG_PRINT(LOG_INFO,"setTrxTableHandler : DB query getE1ForTRX Failed. ");
            cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
            free(trxTableApiPtr);
            return;
          }
          if(gE1Data[e1Id].e1State == unlockInProgress )
          {
            LOG_PRINT(LOG_INFO,"setTrxTableHandler : Abis E1 Unlock in progress. Can not lock/unlock TRX. ");
            cfgSendNackToCm(CM_ERR_E1_UNLOCK_IN_PROGRESS);
          }
          else if(gE1Data[e1Id].e1State == lockInProgress)
          {
            LOG_PRINT(LOG_INFO,"setTrxTableHandler : Abis E1 Lock in progress. Can not lock/unlock TRX. ");
            cfgSendNackToCm(CM_ERR_E1_LOCK_IN_PROGRESS);
          }
          /*Changes for CS4.0 :Abis E1 Lock/Unlock Ends*/
          else
          {
            /* Received Request is for Lock or Unlock TRX */    
            LOG_PRINT(LOG_INFO,"setTrxTableHandler : Handling TRX Lock or Unlock");
            trxObjectHandler();
          }
        }
        else
        {
          /* Received Request is for Lock or Unlock TRX */    
          LOG_PRINT(LOG_INFO,"setTrxTableHandler : Handling TRX Lock or Unlock for R2_BTS_IP/R3_BTS");
          trxObjectHandler();
        }   
      }
      else if((trxTableApiPtr != PNULL) && 
               (  receivedMsgPtr->trxPwrAction != trxTableApiPtr->trxPwrAction &&
                receivedMsgPtr->trxReset   == trxTableApiPtr->trxReset &&
		receivedMsgPtr->adminState == trxTableApiPtr->adminState
	    ))
	    
      {
 	/* Code will be added for Trx Shut Down */
	 LOG_PRINT(DEBUG,"TRX Power Action is not supoprted Yet");
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      }
      else if((trxTableApiPtr != PNULL) && 
               ( receivedMsgPtr->trxReset   != trxTableApiPtr->trxReset &&
                 receivedMsgPtr->trxPwrAction == trxTableApiPtr->trxPwrAction &&
		receivedMsgPtr->adminState == trxTableApiPtr->adminState
	    ))
      {
        
         /* Received Request is for TRX Reset */    
	  
        if(receivedMsgPtr->trxLocation!=TRX_LOCATION_IN_FRAME) //A6 inframe changes
        {
          trxResetHandler();	
        }
        else
        {
          LOG_PRINT(DEBUG,"Operation not supported for INFRAME TRX (TRX Location %d)",receivedMsgPtr->trxLocation);
          cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
        }      
        
      }
      else
      {
          LOG_PRINT(DEBUG,"Simultanous operation are not supported")
          cfgSendNackToCm(CM_ERR_SIMULTANOUS_OPERATION_NOT_ALLOWED);	
      }

      free(trxTableApiPtr);
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : setTrxTableHandler");
}

/********************************* Function  Header********************************
   Function Name:       hoCtrlTablePerformConsistencyCheck()
Parameters:          HoCtrlTableApi *recieveMsgPtr
Return type:         void
Purpose:             Perform consistancy checks for HoCtrl Table
Other Note: Added for CS3.0
 ************************************************************************************/
I_Bool hoCtrlTablePerformConsistencyCheck(HoCtrlTableApi *recieveMsgPtr)
{
   CsPwrCtrlPreconfigTableApi *csPwrCtrlPreconfigTablePtr = NULL; 
   I_S32 rowsCount = 0;
   I_U16 outSize = 0;
   I_S32 dbStatus = -1;
 /* Mantis 4115 */
   CsPwrCtrlTableApi *csPwrCtrlTablePtr=PNULL;
   CsPwrCtrlTableIndices csPwrCtrlTableIndex;
 /* Mantis 4115 */

   if(getallCsPwrCtrlPreconfigTable(&csPwrCtrlPreconfigTablePtr,&rowsCount,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getallCsPwrCtrlPreconfigTable DB call is geting failed..")
         return FALSE;
   }

   if(csPwrCtrlPreconfigTablePtr->windowSizeRxLevP > recieveMsgPtr->windowSizeRxLevH)
   {
      LOG_PRINT(LOG_DEBUG,"windowSizeRxLevP of CsPwrCtrlPreconfig Table is greater than windowSizeRxLevH of HoCtrl Table")
         free(csPwrCtrlPreconfigTablePtr);
      return FALSE; 
   } 
   if(recieveMsgPtr->windowSizeNcell > recieveMsgPtr->windowSizeRxLevH)
   {
      LOG_PRINT(LOG_DEBUG,"windowSizeNcell is greater than windowSizeRxLevH of HoCtrl Table")
         free(csPwrCtrlPreconfigTablePtr);
      return FALSE; 
   } 
   if(csPwrCtrlPreconfigTablePtr->windowSizeRxQualP > recieveMsgPtr->windowSizeRxQualH)
   {
      LOG_PRINT(LOG_DEBUG,"windowSizeRxQualP of CsPwrCtrlPreconfig Table is greater than windowSizeRxQualH of HoCtrl Table")
         free(csPwrCtrlPreconfigTablePtr);
      return FALSE; 
   } 
   if(recieveMsgPtr->windowSizeNcell > recieveMsgPtr->windowSizeRxQualH)
   {
      LOG_PRINT(LOG_DEBUG,"windowSizeNcell is greater than windowSizeRxQualH of HoCtrl Table")
         free(csPwrCtrlPreconfigTablePtr);
      return FALSE; 
   }
   
   free(csPwrCtrlPreconfigTablePtr);
    
   /* Mantis 4115 */
   csPwrCtrlTableIndex.cellId = recieveMsgPtr->cellId;
   csPwrCtrlTableIndex.lac = recieveMsgPtr->lac;
   
   if(getCsPwrCtrlTable(&csPwrCtrlTableIndex,&csPwrCtrlTablePtr) != CLIB_SUCCESS) 
   {
      LOG_PRINT(LOG_INFO,"getCsPwrCtrlTable DB call is geting failed..");
      return TRUE;
   }
   
   if(!(recieveMsgPtr->lRxLevUlH < csPwrCtrlTablePtr->lRxLevUlP))
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed: lRxLevUlH(HoCtrlTable) is not lesser than lRxLevUlP(CsPwrCtrlTable)");
      free(csPwrCtrlTablePtr);
      return FALSE;
   }
   if(!(recieveMsgPtr->lRxLevDlH < csPwrCtrlTablePtr->lRxLevDlP))
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed: lRxLevDlH(HoCtrlTable) is not lesser than lRxLevDlP(CsPwrCtrlTable)");
      free(csPwrCtrlTablePtr);
      return FALSE;
   }
   if(!(recieveMsgPtr->lRxQualUlH > csPwrCtrlTablePtr->lRxQualUlP))
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed: lRxQualUlH(HoCtrlTable) is not greater than lRxQualUlP(CsPwrCtrlTable)");
      free(csPwrCtrlTablePtr);
      return FALSE;
   }
   if(!(recieveMsgPtr->lRxQualDlH > csPwrCtrlTablePtr->lRxQualDlP))
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed: lRxQualDlH(HoCtrlTable) is not greater than lRxQualDlP(CsPwrCtrlTable)");
      free(csPwrCtrlTablePtr);
      return FALSE;
   }
   free(csPwrCtrlTablePtr);
   /* Mantis 4115 */
   /* Fixed Mantis #5356 : Start */
   CsNeighCellsTableApi* csNeighCellTableApiPtr = NULL;
   I_U8 *tmpPtr = NULL;
   I_U32 i = ZERO;
   dbStatus = getallCsNeighCellsTable(&csNeighCellTableApiPtr, &rowsCount,&outSize);
   if(DBLIB_SUCCESS == dbStatus)
   {
      tmpPtr = (I_U8 *)(csNeighCellTableApiPtr);
      for(i = 0; i < rowsCount; i++)
      {
         csNeighCellTableApiPtr = (CsNeighCellsTableApi *)(tmpPtr + (i * outSize));
         if((csNeighCellTableApiPtr->lac == recieveMsgPtr->lac) &&
	    (csNeighCellTableApiPtr->cellId == recieveMsgPtr->cellId) &&
      (csNeighCellTableApiPtr->radioAccessType!=WCDMA_FDD) &&
	    (recieveMsgPtr->lRxLevDlH >= csNeighCellTableApiPtr->rxLevMinN)
	   )
	 {
       LOG_PRINT(LOG_MAJOR,"Consistancy failed: lRxLevDlH(HoCtrlTable) is not less than rxLevMinN(CsNeighCellsTable)");
       free(tmpPtr);
       return FALSE;
	 }
      }
      free(tmpPtr);
   }
   /* Fixed Mantis #5356 : End */

   return TRUE;
}

/* CS3.0 Changes : End */
/********************************* Function  Header********************************
Function Name:       setCsPwrCtrlTablehandler()
Parameters:          void
Return type:         void
Purpose:             1. Checks consistency of CsPwrCtrlTable parameters.
                     2. Called when set() is called on CsPwrCtrl Table.
           3. If parameters are consistent, they are updated to DB.
Other Note:          1. Introduced in CS2.5
                     2. Consistency of parameters across tables is comprehensively checked.
**********************************************************************************/

void setCsPwrCtrlTableHandler()
{
   
   CsPwrCtrlTableApi* receivedMsgPtr = (CsPwrCtrlTableApi*)(((I_U8 *)gCfgMsgBuf)+ sizeof (sCmMsg));
   CsPwrCtrlTableApi* csPwrCtrlTableApiPtr = PNULL;
   CsPwrCtrlTableIndices apiPwrCtrlIndex = {0};       
   CellTableApi* cellTableApiPtr = PNULL;
   CellTableIndices apiCellIndex = {0};
   I_Bool statusRange = FALSE;
   I_S32  ret = 0; 
   I_U8 consistency_check_flag = OAMS_RSLT_FAILURE;

   /** 1. For CsPwrCtrl Table to be updated, cell should exist.
           Checking if cell exists or not.
       key={cellId, lac}
   */
   apiCellIndex.cellId = receivedMsgPtr->cellId;
   apiCellIndex.lac = receivedMsgPtr->lac;
   ret = getCellTable(&apiCellIndex, &cellTableApiPtr);
/* Mantis Fixed - 7744 Starts */
   if( ret != CLIB_SUCCESS )
   {
     LOG_PRINT(LOG_INFO,"setCsPwrCtrlTableHandler(): Cell not defined in Cell Table for key { cellid = 0x%x, lac = 0x%x }",receivedMsgPtr->cellId,receivedMsgPtr->lac);
     cfgSendNackToCm(CM_ERR_CELL_NOT_FOUND);
     return;
   }
/* Mantis Fixed - 7744 Ends */
   
   /* cell parameters are not needed further.
     The intent was only to check that cell exists.
   */
   free(cellTableApiPtr);

   /* 2. Range check on CsPwrCtrl Table   */
   statusRange = csPwrCtrlTableRangeChk(receivedMsgPtr);
   if(statusRange != FALSE)
   {
     LOG_PRINT(LOG_INFO,"setCsPwrCtrlTableHandler(): RangeChk passed.");
   }
   else
   {
     LOG_PRINT(LOG_INFO,"setCsPwrCtrlTableHandler(): RangeChk failed.");
     cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
     return;    
   }

   /* 3. Checking the consistency of the CsPwrCtrl table parameters
    key = {cellId, lac } 
   */
   consistency_check_flag = validateCsPwrCtrlparameters(receivedMsgPtr);
   if(consistency_check_flag == OAMS_RSLT_FAILURE)
   {
     cfgSendNackToCm(CM_ERR_PWRCTRL_CONSIST_CHK_FAILED);
     return;     
   } 

   apiPwrCtrlIndex.cellId =  receivedMsgPtr->cellId;
   apiPwrCtrlIndex.lac = receivedMsgPtr->lac;
   ret = getCsPwrCtrlTable(&apiPwrCtrlIndex, &csPwrCtrlTableApiPtr);

   /* 4. case 1: There is nothing in DB for particular key.
    case 2: There is entry for key in DB.
            key = {cellID, lac}  
   */
   if (csPwrCtrlTableApiPtr == PNULL)   /* case 1 */
   {
   /* No need to check if Cell is in locked state as Cell can't be in unlock
      state if its entry in CsPwrCtrlTable doesnot exists.
        */
        ret = insertCsPwrCtrlTable(receivedMsgPtr ); 
        if(ret == CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_INFO,"setCsPwrCtrlTableHandler(): new Row added successfully");
          cfgSendAckToCm();
          return;     
        }
        else
        {
          LOG_PRINT(LOG_INFO,"setCsPwrCtrlTableHandler(): insertCsPwrCtrlTable Failed");
          cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
          return;     
        } 
   }   
   else   /* case 2 */
   {
      /* update of CsPwrCtrlTable is independent of cell locked/unlocked state */
      free(csPwrCtrlTableApiPtr);
      ret = updateCsPwrCtrlTable(receivedMsgPtr ); 
      if (ret == CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_INFO,"setCsPwrCtrlTableHandler(): Row updated successfully");
        cfgSendAckToCm();
        return;     
      }
      else
      {
        LOG_PRINT(LOG_INFO,"setCsPwrCtrlTableHandler(): updateCsPwrCtrlTable Failed");
        cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
        return;     
      } 
   } /* End of Else */         
}

/*BSC CS4.0 Changes Starts*/
   
/********************************* Function  Header********************************
Function Name:       setCardStateChangeTableHandler()
Parameters:          void
Return type:         void
Purpose:             1. Checks consistency of CardStateChange Table parameters.
                     2. Called when set() is called on CardStateChange Table.
                     3. If parameters are consistent, Request will be sent towards BPM.
Other Note:          
**********************************************************************************/
I_Void setCardStateChangeTableHandler()
{
   CardStateChangeTableApi* receivedMsgPtr = (CardStateChangeTableApi*)(((I_U8 *)gCfgMsgBuf)+ sizeof (sCmMsg));
   IccCardInfoTableApi *iccCardInfoTableApiPtr = NULL;
   EicCardInfoTableApi *eicCardInfoTableApiPtr = NULL;
   OamsCfgOilSetCardOperState oamsCfgOilSetOperConStateReq;
   SwMOfferTableApi *swmOfferTableApi = NULL;
   I_U32 outRow = 0;
   I_U16 outSize = 0;
   I_U32 cardOperState = 0;
   I_U32 peerCardOperState = 0;
   I_U8 peerSlotId;
   I_S32 res = 0;
   I_U8 inProgressState = I_FALSE;

   LOG_PRINT(LOG_INFO,"setCardStateChangeTableHandler: Entering in function");
   //Mantis 31749
   /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
   LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: setCardStateChangeTableHandler : Before updating slotId[%d]",receivedMsgPtr->slotId);
   receivedMsgPtr->slotId = receivedMsgPtr->slotId + 2;
   LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: setCardStateChangeTableHandler : After updating slotId[%d]",receivedMsgPtr->slotId);
   /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
   //Mantis 31749
   
   res = getCardOperState(receivedMsgPtr->chasisFrameId,receivedMsgPtr->slotId,&cardOperState); 
   if(res != CLIB_SUCCESS)
   {
      LOG_PRINT(MAJOR,"chasisFrameId[%d],SlotId[%d] is invalid Card err:%d",
               receivedMsgPtr->chasisFrameId,receivedMsgPtr->slotId,res);
      cfgSendNackToCm(CM_ERR_INVALID_CARD);
      return; 
   }

   if( (receivedMsgPtr->slotId == ICC0_SLOTID) ||
       (receivedMsgPtr->slotId == ICC1_SLOTID) )
   {
      if(getallSwMOfferTable( &swmOfferTableApi, &outRow, &outSize) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"setCardStateChangeTableHandler: SW Offer is in Progress. Reject the request");
         cfgSendNackToCm(CM_ERR_SW_OFFER_IN_PROGRESS);
         free(swmOfferTableApi);
         return; 
      }

      inProgressState = checkOamProcedure();
      if(inProgressState == I_FALSE)
      {
         cfgSendNackToCm(CM_ERR_OAM_OPERATION_IN_PROGRESS);
         return; 
      }

      switch(receivedMsgPtr->cardOperationalState)
      {
         case CARDSTATE_STANDBY :
           LOG_PRINT(DEBUG,"CardState Change Req rcvd for IccCard To STANDBY state");
           if(   (cardOperState != CARDSTATE_ACTIVE)  &&
                (cardOperState != CARDSTATE_DIAGNOSTIC)   )
           {
              LOG_PRINT(MAJOR,"Card with FrameId[%d],SlotId[%d] is not in Active/Diagnostic State",
                    receivedMsgPtr->chasisFrameId, receivedMsgPtr->slotId);
              cfgSendNackToCm(CM_ERR_CARDSTATE_NOT_ACTIVE);
              return; 
           }
           if(getallIccCardInfoTable( &iccCardInfoTableApiPtr, &outRow, &outSize) != CLIB_SUCCESS)
           {
              LOG_PRINT(LOG_CRITICAL,"Get All Query Failed on Icc Card Info Table");
              cfgSendNackToCm(CM_ERR_INVALID_CARD);
              return; 
           }
           if(outRow == 1)
           {
              LOG_PRINT(LOG_CRITICAL," Operation is not allowed on  One Icc Card.State Change Operation Failed");
              cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
              free(iccCardInfoTableApiPtr);
              return; 
           }
           free(iccCardInfoTableApiPtr);
         
           if(ICC0_SLOTID == receivedMsgPtr->slotId)
              peerSlotId = ICC1_SLOTID;
           else
              peerSlotId = ICC0_SLOTID;  

           res = getCardOperState(receivedMsgPtr->chasisFrameId,peerSlotId,&peerCardOperState); 
           if(res != CLIB_SUCCESS)
           {
              LOG_PRINT(MAJOR,"chasisFrameId[%d],SlotId[%d] is invalid Card err:%d",
                       receivedMsgPtr->chasisFrameId,receivedMsgPtr->slotId,res);
              cfgSendNackToCm(CM_ERR_INVALID_PEER_CARDSTATE);
              return; 
           }
           if(  (peerCardOperState != CARDSTATE_STANDBY)  && 
                 (peerCardOperState != CARDSTATE_ACTIVE)  ) 
           {
              LOG_PRINT(MAJOR,"chasisFrameId[%d],SlotId[%d] is in invalid CardState:%d",
                       receivedMsgPtr->chasisFrameId,peerSlotId,peerCardOperState);
              cfgSendNackToCm(CM_ERR_INVALID_PEER_CARDSTATE);
              return; 
           }  
         break;

         case CARDSTATE_DIAGNOSTIC :
           LOG_PRINT(DEBUG,"CardState Change Req rcvd for IccCard To DIAGNOSTICS state");
           if(cardOperState != CARDSTATE_STANDBY)
           {
              LOG_PRINT(DEBUG,"Diagnostic state change req rcvd for non-standby card");  
              cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
              return; 
           }  
           if(areAllDspLockedOnCard(receivedMsgPtr->slotId) != I_TRUE) 
           {
              LOG_PRINT(DEBUG,"All Dsps are not locked on slotId:%d",receivedMsgPtr->slotId);
              cfgSendNackToCm(CM_ERR_DSP_UNLOCKED);
              return; 
           } 
         break;

         #if 0
         case CARDSTATE_IN_SERVICE :
           LOG_PRINT(DEBUG,"CardState Change Req rcvd for IccCard To IN_SERVICE state");
           if(cardOperState != CARDSTATE_DIAGNOSTIC)
           {
              LOG_PRINT(DEBUG,"IN_SERVICE state change req rcvd for non-Diagnostic card");  
              cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
              return; 
           }  
         break;
         #endif
      
         default:
           LOG_PRINT(DEBUG,"Invalid CardState:%d Change Req rcvd for IccCard",
                  receivedMsgPtr->cardOperationalState);
           cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
           return;
         break;
      }
   }
   else if( (receivedMsgPtr->slotId == EIC0_SLOTID) ||
       (receivedMsgPtr->slotId == EIC1_SLOTID) )
   {
      if(I_TRUE == isSwActivationInProgressForcEic())  
      {
         LOG_PRINT(MAJOR,"setCardStateChangeTableHandler: SW Activation is in Progress. Reject the request");
         cfgSendNackToCm(CM_ERR_SW_EIC_ACT_IN_PROGRESS);
         return; 
      }
 
      switch(receivedMsgPtr->cardOperationalState)
      {
         case CARDSTATE_DIAGNOSTIC :
           LOG_PRINT(DEBUG,"CardState Change Req rcvd for EicCard To DIAGNOSTICS state");
           if(cardOperState != BPM_EIC_ENABLE)
           {
              LOG_PRINT(MAJOR,"Card with FrameId[%d],SlotId[%d] is not in EnableState",
                    receivedMsgPtr->chasisFrameId, receivedMsgPtr->slotId);
              cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
              return; 
           }
           if(getallEicCardInfoTable( &eicCardInfoTableApiPtr, &outRow, &outSize) != CLIB_SUCCESS)
           {
              LOG_PRINT(LOG_CRITICAL,"Get All Query Failed on Eic Card Info Table");
              cfgSendNackToCm(CM_ERR_INVALID_CARD);
              return; 
           }
           if(outRow == 1)
           {
              LOG_PRINT(LOG_CRITICAL," Operation is not allowed on  One Eic Card.State Change Operation Failed");
              cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
              free(eicCardInfoTableApiPtr);
              return; 
           }
           free(eicCardInfoTableApiPtr);
         break;
         
         case CARDSTATE_IN_SERVICE :
           LOG_PRINT(DEBUG,"CardState Change Req rcvd for EicCard To IN_SERVICE state");
           if(cardOperState != CARDSTATE_DIAGNOSTIC)
           {
              LOG_PRINT(DEBUG,"IN_SERVICE state change req rcvd for non-Diagnostic card");  
              cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
              return; 
           }  
         break;

         default:
           LOG_PRINT(DEBUG,"Invalid CardState:%d Change Req rcvd for EicCard",
                  receivedMsgPtr->cardOperationalState);
           cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
           return;
         break;  
      }
   }
   else 
   {
      LOG_PRINT(MAJOR,"Invalid Card slotId Rcvd:%d",receivedMsgPtr->slotId );
      cfgSendNackToCm(CM_ERR_INVALID_CARD);
      return; 
   }

   cfgSendAckToCm();

   oamsCfgOilSetOperConStateReq.slotId = receivedMsgPtr->slotId; 
   //Mantis 31749
   /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
   //oamsCfgOilSetOperConStateReq.cardType = receivedMsgPtr->cardType;
   LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: setCardStateChangeTableHandler : Before updating cardType[%d] slotId[%d]",receivedMsgPtr->cardType,oamsCfgOilSetOperConStateReq.slotId);
   receivedMsgPtr->cardType = CARD_TYPE_ICC; 
   oamsCfgOilSetOperConStateReq.cardType = receivedMsgPtr->cardType; 
   LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: setCardStateChangeTableHandler : After updating cardType[%d] slotId[%d]",oamsCfgOilSetOperConStateReq.cardType,oamsCfgOilSetOperConStateReq.slotId);
   oamsCfgOilSetOperConStateReq.cardState = receivedMsgPtr->cardOperationalState;
   LOG_PRINT(LOG_DEBUG,"OMC-SWICTHOVER: setCardStateChangeTableHandler : cardType[%d] slotId[%d]",oamsCfgOilSetOperConStateReq.cardType,oamsCfgOilSetOperConStateReq.slotId); 
   /*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
   //Mantis 31749
   cfgSendMessage(&oamsCfgOilSetOperConStateReq, sizeof(OamsCfgOilSetCardOperState), 
         ENT_OAM_OIL, OAMS_CFG_OIL_SET_OPER_CON_STATE_REQ , 0);
   
   LOG_PRINT(LOG_INFO,"setCardStateChangeTableHandler: Exiting from function");
   return; 
}
/*BSC CS4.0 Changes Ends*/

// CS40 PH-2 Changes ::PreConfig to Config

/********************************* Function  Header********************************
   Function Name:       prepareE1Tblptr()
Parameters:          e1number, adminState & UsageType received in TrunkPort Table
Return type:         void
Purpose:             Used for changing gCfgMsgBuf to TrunkTable pointer type
Other Note:
 ************************************************************************************/
void prepareE1Tblptr( I_U32 adminState )
{
   I_S32  ret                   = 1; 
   TrunkTableApi* e1TableApiPtr = PNULL;
   TrunkTableIndices apiE1Index = {0} ;
   I_PVoid tempPtr              = NULL;

   // Store the address of pointer having Trunk Port table data in a temporary variable
   tempPtr = gCfgMsgBuf;

   // Copy header portion received in TrunkPortTable request in this structure
   memcpy( &g_e1tbl.msg, (sCmMsg *)gCfgMsgBuf, sizeof (sCmMsg) );

   // Set the msg type from BSC_API_SET_TRUNKPORTTABLE to BSC_API_SET_TRUNKPERTABLE
   g_e1tbl.msg.sHdr.msgType = BSC_API_SET_TRUNKPERTABLE; 

   apiE1Index.e1Num = gE1NumberMapToTrunk;
   ret = getTrunkTable(&apiE1Index, &e1TableApiPtr);

   if( ret == CLIB_SUCCESS && e1TableApiPtr != NULL )
   {
      // Fill the details present in DB for the particular E1 in g_e1tbl
      memcpy( &g_e1tbl.e1tbl, e1TableApiPtr, sizeof(TrunkTableApi) );
      free(e1TableApiPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO," prepareE1Tblptr: getTrunkTable fails ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }

   // Fill the admin state received in TrunkPort table in TrunkTable
   g_e1tbl.e1tbl.adminState = adminState;

   // Provide the address of the structure filled to gCfgMsgBuf
   gCfgMsgBuf = &g_e1tbl;

   // Execute E1 Lock & Unloclk Implementation
   setE1TableHandler();

   // Point gCfgMsgBuf back to the Trunk data which should be released
   gCfgMsgBuf = tempPtr;
   
}

// CS40 PH-2 Changes ::PreConfig to Config
/********************************* Function  Header********************************
Function Name:       setMlpppConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             1. Checks consistency of MlpppConfig Table parameters.
                     2. Called when set() is called on MlpppCpnfig Table.
                     3. If parameters are consistent, Request will be sent towards BPM.
Other Note:          
**********************************************************************************/
I_Void setMlpppConfigTableHandler()
{
   MlpppConfigTableApi * receivedMsgPtr = (MlpppConfigTableApi*)(((I_U8 *)gCfgMsgBuf)+ sizeof (sCmMsg));
   MlpppConfigTableApi *mlpppConfigTableApiPtr = NULL;
   I_U32 outRows = 0;
   I_U16 outSize = 0;
   LOG_PRINT(LOG_INFO,"setMlpppConfigTableHandler: Entering in Function");
   if(getallMlpppConfigTable(&mlpppConfigTableApiPtr, &outRows, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"setMlpppConfigTableHandler: No Entry found in MlpppConfigTable.");
      LOG_PRINT(LOG_INFO,"setMlpppConfigTableHandler: Request is to add the row in Table");
      addMlpppConfigTableHandler();
      return;
   }
   else /* Request received for modification */
   {
      if (mlpppConfigTableApiPtr->mlpppLinkId == receivedMsgPtr->mlpppLinkId)
      {
         LOG_PRINT(LOG_INFO, "Modification request received for MlppConfigTable");
         modifyMlppConfigTable(receivedMsgPtr, mlpppConfigTableApiPtr);
      }
      else
      {
         LOG_PRINT(LOG_INFO, "Row already exists in MlpppConfig Table");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
         free(mlpppConfigTableApiPtr);
      }
      LOG_PRINT(LOG_INFO,"setMlpppConfigTableHandler: Exiting from Function");
      return;
   }
}

/********************************* Function  Header********************************
Function Name:       sndOamCfgOilSetTimeReq()
Parameters:          I_U32 * inputTimeStamp
Return type:         void
Purpose:             1. To Send SetTimeRequest To OIL                  
Other Note:          
**********************************************************************************/
I_Void sndOamCfgOilSetTimeReq(I_U32 *timeStamp_i)
{
  OamsCfgOilSetTimeReq sndMsg;
  sndMsg.timeStamp = *timeStamp_i;
	cfgSendMessage(&sndMsg, sizeof(OamsCfgOilSetTimeReq),
          ENT_OAM_OIL,OAM_CFG_OIL_SET_SYSTEM_TIME_REQ, 0);
  return;
}

/********************************* Function  Header********************************
Function Name:       setBscDateTimeTableHandler()
Parameters:          void
Return type:         void
Purpose:             1. Checks validity of BscDateTime Table parameters.
                     2. Called when set() is called on BscDateTime Table.
                     3. If parameters are consistent, Request will be sent towards BPM.
Other Note:          
**********************************************************************************/
I_Void setBscDateTimeTableHandler( )
{
   sBscDateTimeTableApi * receivedMsgPtr = (sBscDateTimeTableApi *)(((I_U8 *)gCfgMsgBuf)+ sizeof (sCmMsg));
   BscDateTimeTableApi bscDateTimeTbl;
   I_U32 timeStamp;
   struct tm time_i;
   time_t retVal;

   LOG_PRINT(LOG_INFO,"setBscDateTimeTableHandler : Entering in Function");
   
   bscDateTimeTbl.dateIndx = 1;
   bscDateTimeTbl.year = receivedMsgPtr->year;
   bscDateTimeTbl.month = receivedMsgPtr->month;
   bscDateTimeTbl.day = receivedMsgPtr->day; 
   bscDateTimeTbl.hours = receivedMsgPtr->hours;  
   bscDateTimeTbl.min = receivedMsgPtr->min;
   bscDateTimeTbl.sec  = receivedMsgPtr->sec;

   if(insertBscDateTimeTable(&bscDateTimeTbl) != CLIB_SUCCESS)
   {
       if(updateBscDateTimeTable(&bscDateTimeTbl) != CLIB_SUCCESS)	
       {
          LOG_PRINT(MAJOR,"updateBscDateTimeTable failed");    
       } 
   }
   else
   {
      LOG_PRINT(DEBUG,"insertBscDateTimeTable succ");   
   }  
   
   time_i.tm_sec = receivedMsgPtr->sec;
   time_i.tm_min = receivedMsgPtr->min;
   time_i.tm_hour = receivedMsgPtr->hours;
   time_i.tm_mday = receivedMsgPtr->day;
   time_i.tm_mon = receivedMsgPtr->month  - 1;
   time_i.tm_year =receivedMsgPtr->year - 1900 ;
   time_i.tm_wday = 0;
   time_i.tm_yday	 = 0;
   time_i.tm_isdst = 0;
   retVal = mktime(&time_i);
	 LOG_PRINT(DEBUG,"retVal = 0x%x", retVal);
   timeStamp = (I_U32)retVal;
   sndOamCfgOilSetTimeReq(&timeStamp);
   LOG_PRINT(LOG_INFO,"setBscDateTimeTableHandler : Exiting from Function");
   return;
}    

/********************************* Function  Header********************************
Function Name:       areAllDspLockedOnCard()
Parameters:          I_U8  slotId
Return type:         I_S32 I_TRUE/I_FALSE
Purpose:             1. Checks if all dsps on given slotId are locked or not. 
Other Note:          
**********************************************************************************/
I_S32 areAllDspLockedOnCard(I_U8 slotId)
{
   DspInfoTableApi *dspInfoTbl;
   DspInfoTableApi *tmpPtr;
   I_U32 outRows = 0,i=0;
   I_U16 outSize = 0;
   LOG_PRINT(LOG_INFO,"areAllDspLockedOnCard : Entering in Function");
   if(getallDspInfoTable(&dspInfoTbl, &outRows, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"No Entry found in dspInfoTable.");
      return I_FALSE;
   }
   else 
   {
      for(i=0;i<outRows;i++)
      {
        tmpPtr = (DspInfoTableApi *)((I_U8 *)dspInfoTbl + i*outSize);
        if( (tmpPtr->adminState == UNLOCKED) && 
            (tmpPtr->slotId == slotId) )
        {
           LOG_PRINT(DEBUG,"DSP:%d is UNLOCKED", tmpPtr->dspId);
           return I_FALSE;
        }
      }
      free(dspInfoTbl); 
   }
   return I_TRUE;
}

/*Changes for TsGroup Start */
/********************************* Function  Header********************************
Function Name:       setTsGroupConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             1. Checks validity of TsGroupConfig Table parameters.
                     2. Called when set() is called on TsGroupConfig Table.
                     3. If parameters are consistent,timeslot group will be 
                        generated and switching will be done for the same. 
Other Note:          
**********************************************************************************/
I_Void setTsGroupConfigTableHandler( )
{
  TsGroupConfigTableIndices apiTsGroupConfigIndex;       
  TsGroupConfigTableApi *tsGroupConfigTableApiPtr=PNULL;
  TsGroupMapTableApi tsGroupMapTableApi;
  I_U32 retStatus;
  I_S32 dbStatus;
  I_U32 maxTrunkTs=0,tsMap1=0,tsMap2=0;
  I_U32 trunkUsageType1,trunkUsageType2;
  I_U16 numTs;
  TsGroupConfigTableApi *receivedMsgPtr=PNULL;
  I_U8 tsAllocated1[MAX_E1_TS],tsAllocated2[MAX_E1_TS];

  LOG_PRINT(LOG_DEBUG,"Entering in Function %s",__FUNCTION__);
  receivedMsgPtr = (TsGroupConfigTableApi *)(((I_U8 *)gCfgMsgBuf)+ sizeof (sCmMsg));
  apiTsGroupConfigIndex.tsGroupId=receivedMsgPtr->tsGroupId; 

  memset(tsAllocated1,0,MAX_E1_TS);
  memset(tsAllocated2,0,MAX_E1_TS);
  dbStatus = getTsGroupConfigTable(&apiTsGroupConfigIndex, &tsGroupConfigTableApiPtr);

  /* Case: Addition of New TsGroupConfig in Table */
  if (DBLIB_SUCCESS != dbStatus)
  {
    LOG_PRINT(DEBUG,"Addition of a new TSGroup");
    retStatus=tsGroupConfigTableRangeCheck(receivedMsgPtr);
    if(retStatus!=CM_SUCCESS)
    {
      cfgSendNackToCm(retStatus);
      return;
    }

    retStatus=getTrunkUsageType(receivedMsgPtr->trunkPortId1,&trunkUsageType1);

    if(retStatus!=CM_SUCCESS)
    {
      cfgSendNackToCm(retStatus);
      return ;
    }

    retStatus=getTrunkUsageType(receivedMsgPtr->trunkPortId2,&trunkUsageType2);

    if(retStatus!=CM_SUCCESS)
    {
      cfgSendNackToCm(retStatus);
      return ;
    }

    numTs=receivedMsgPtr->numTS;
    retStatus=allocateTSforTsGroup(receivedMsgPtr->trunkPortId1,receivedMsgPtr->trunkPortId2,numTs,&tsMap1,&tsMap2,trunkUsageType1,trunkUsageType2);

    if(CM_SUCCESS!=retStatus)
    {
      cfgSendNackToCm(retStatus);
      return;
    }

    convertTsBitMapToArray(numTs,tsMap1,tsAllocated1);
    convertTsBitMapToArray(numTs,tsMap2,tsAllocated2);

    if(trunkUsageType1 == SYS_E1_USAGE_ABISIF)
    {
      retStatus=updateAbisTimeSlotforTsGroup(receivedMsgPtr->trunkPortId1,numTs,tsAllocated1,SYS_TS_USAGE_TSGROUP);
      if(retStatus!=CM_SUCCESS)
      {
        cfgSendNackToCm(retStatus);
        return;
      }
    } 

    if(trunkUsageType2 == SYS_E1_USAGE_ABISIF)
    {
      retStatus=updateAbisTimeSlotforTsGroup(receivedMsgPtr->trunkPortId2,numTs,tsAllocated2,SYS_TS_USAGE_TSGROUP);
      if(retStatus!=CM_SUCCESS)
      {
        cfgSendNackToCm(retStatus);
        return;
      }
    }

    dbStatus=insertTsGroupConfigTable(receivedMsgPtr);
    if(CLIB_SUCCESS != dbStatus)
    {
      LOG_PRINT(LOG_INFO,"insertTsGroupConfigTable Failed, sending Nack");
      if(trunkUsageType1 == SYS_E1_USAGE_ABISIF)
      {
        retStatus=updateAbisTimeSlotforTsGroup(receivedMsgPtr->trunkPortId1,numTs,tsAllocated1,SYS_TS_USAGE_ABIS_FREE);
      }

      if(trunkUsageType2 == SYS_E1_USAGE_ABISIF)
      {
        retStatus=updateAbisTimeSlotforTsGroup(receivedMsgPtr->trunkPortId2,numTs,tsAllocated2,SYS_TS_USAGE_ABIS_FREE);
      }

      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      return;
    }

    tsGroupMapTableApi.tsGroupId=receivedMsgPtr->tsGroupId;
    tsGroupMapTableApi.numTS=numTs;
    tsGroupMapTableApi.trunkPortId1=receivedMsgPtr->trunkPortId1;
    tsGroupMapTableApi.trunkPortId2=receivedMsgPtr->trunkPortId2;
    tsGroupMapTableApi.timeSlotMap1=tsMap1;
    tsGroupMapTableApi.timeSlotMap2=tsMap2;

    dbStatus=insertTsGroupMapTable(&tsGroupMapTableApi);
    if(CLIB_SUCCESS != dbStatus)
    {
      LOG_PRINT(LOG_INFO,"insertTsGroupMapTable Failed, sending Nack");
      if(trunkUsageType1 == SYS_E1_USAGE_ABISIF)
      {
        retStatus=updateAbisTimeSlotforTsGroup(receivedMsgPtr->trunkPortId1,numTs,tsAllocated1,SYS_TS_USAGE_ABIS_FREE);
      }

      if(trunkUsageType2 == SYS_E1_USAGE_ABISIF)
      {
        retStatus=updateAbisTimeSlotforTsGroup(receivedMsgPtr->trunkPortId2,numTs,tsAllocated2,SYS_TS_USAGE_ABIS_FREE);
      }

      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      return;
    }

    retStatus=prepAndSndSwitchConForTsGroup(receivedMsgPtr->trunkPortId1,tsAllocated1,receivedMsgPtr->trunkPortId2,tsAllocated2,numTs);
    cfgSendAckToCm();

  }
  else
  {
    free(tsGroupConfigTableApiPtr);
    LOG_PRINT(MAJOR,"Modification to TsGroupConfig not allowed");
    cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
    return;
  }

  LOG_PRINT(LOG_DEBUG,"Exiting in Function %s",__FUNCTION__);
  return;
}    
/*Changes for TsGroup End */


/*Changes for setCallEndTimerConfigTable Start */
/********************************* Function  Header********************************
  Function Name:       setCallEndTimerConfigTable()
Parameters:          void
Return type:         void
Purpose:             This can be for following:
To add new entry in CallEndTimerConfigTable table
To Modify the parameters in the CallEndTimerConfigTable table 
Other Note:          
 **********************************************************************************/
I_Void setCallEndTimerConfigTable()
{
  CallEndTimerConfigTableApi* receivedMsgPtr= (CallEndTimerConfigTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
  CallEndTimerConfigTableIndices apiCallEndIndex;
  CallEndTimerConfigTableApi* pCallEndTimerConfigTableApi = NULL;
  I_Bool statusRange = FALSE;

  LOG_PRINT(LOG_INFO,"Entering in setCallEndTimerConfigTable");
   /* Check if BSS Admin State is LOCK or not */ 
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO,"BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }

  apiCallEndIndex.callEndIndex = receivedMsgPtr->callEndIndex; 

  getCallEndTimerConfigTable(&apiCallEndIndex, &pCallEndTimerConfigTableApi); 

  if(pCallEndTimerConfigTableApi != NULL)
  {
    /*Check range*/
    statusRange = callEndTableTimerRangeCheck(receivedMsgPtr);

    if(statusRange)
    {
      if( receivedMsgPtr->callEndTimer != pCallEndTimerConfigTableApi->callEndTimer )
      {
        if ((updateCallEndTimerConfigTable(receivedMsgPtr))!=CLIB_SUCCESS)
        {
          LOG_PRINT(LOG_INFO,"DB Failure");
          cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
          free(pCallEndTimerConfigTableApi);
          if(receivedMsgPtr != NULL)
          {
            DalocMsgBuf(receivedMsgPtr);
            receivedMsgPtr = NULL;
          }          
          LOG_PRINT(LOG_INFO,"Exiting in setCallEndTimerConfigTable");
          return;
        }
        else
        {
          cfgSendAckToCm();
          free(pCallEndTimerConfigTableApi);
          if(receivedMsgPtr != NULL)
          {
            DalocMsgBuf(receivedMsgPtr);
            receivedMsgPtr = NULL;
          }
          LOG_PRINT(LOG_INFO,"Exiting in setCallEndTimerConfigTable");
          return;
        }
      }
      else
      {
        /*Timer is already Configured with the same value*/
        cfgSendNackToCm(CM_ERR_CONSISTENCY_CHECK_FAILED);
        free(pCallEndTimerConfigTableApi);
        if(receivedMsgPtr != NULL)
        {
          DalocMsgBuf(receivedMsgPtr);
          receivedMsgPtr = NULL;
        }
        LOG_PRINT(LOG_INFO,"Exiting in setCallEndTimerConfigTable");
        return;
      } 

    }
    else
    {
      /*Invalid Range sending NACK*/
      LOG_PRINT(LOG_DEBUG," CallEndTimerConfigTable Rangecheck failed in function:%s line:%d",__FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      free(pCallEndTimerConfigTableApi);
      if(receivedMsgPtr != NULL)
      {
        DalocMsgBuf(receivedMsgPtr);
        receivedMsgPtr = NULL;
      }
      LOG_PRINT(LOG_INFO,"Exiting in setCallEndTimerConfigTable");
      return;
    }

  }
  else
  {
    LOG_PRINT(LOG_DEBUG," CallEndTimerConfigTable needed to be preconfigured:%s line:%d",__FUNCTION__,__LINE__);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    if(receivedMsgPtr != NULL)
    {
      DalocMsgBuf(receivedMsgPtr);
      receivedMsgPtr = NULL;
    }
    LOG_PRINT(LOG_INFO,"Exiting in setCallEndTimerConfigTable");
    return;
  }
}
/*Changes for setCallEndTimerConfigTable End */

/******************   Change History ********************************************
   Release       Patch      Author              Description
   1.0                    Pooja Mittal      DB Set Methods for Tables
   BSC CS2.2       Kapil Tyagi      Added Function:
   - setBicTableHandler 
   - setTrxTableHandler 
 *****************************************************************************/
