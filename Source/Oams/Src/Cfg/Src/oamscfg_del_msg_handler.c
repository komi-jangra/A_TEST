/***********************************File Header ***************************
   File Name        : oamscfg_del_msg_handler.c
Purpose          : This file contains  CM DEL request message implementation
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/
#include <oamscfg_includes.h>


/********************************* Function  Header********************************
   Function Name:       delBssTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from BSC table 
Other Note:
 ************************************************************************************/
void delBssTableHandler()
{
   /****************************************************************
      As BSC table has only one row and rows of a table which has exactly only
      one row can't be deleted. CFG will send CM_API_APP_RESPONSE with
      status= CM_ERR_END to the CM.
    ***************************************************************/ 
   LOG_PRINT(LOG_INFO,"delBssTableHandler: Row can't be deleted, Sending Nack");
   cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);

} /* end of delBssTableHandler */

/********************************* Function  Header********************************
   Function Name:      delCsPwrCtrlTablehandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from Cell table 
Other Note:
 ************************************************************************************/
void  delCsPwrCtrlTableHandler()
{

   CsPwrCtrlTableApi* receivedMsgPtr = ( CsPwrCtrlTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   CsPwrCtrlTableIndices apiPwrCtrlIndex = {0};
   CellTableApi* cellTableApiPtr = PNULL;
   CellTableIndices apiCellIndex = {0};        

   apiPwrCtrlIndex.cellId =  receivedMsgPtr->cellId;
   apiPwrCtrlIndex.lac = receivedMsgPtr->lac;

   LOG_PRINT(LOG_INFO,"In delCsPwrCtrlTableHandler()");

   /* Check for key={cellid, lac} to be deleted, cell is in locked state */
   apiCellIndex.cellId =  receivedMsgPtr->cellId;
   apiCellIndex.lac = receivedMsgPtr->lac;

   if (CLIB_SUCCESS == getCellTable(&apiCellIndex, &cellTableApiPtr))
   {
      if (cellTableApiPtr->adminState == LOCK)  
      {
         if (deleteCsPwrCtrlTable(&apiPwrCtrlIndex) == CLIB_SUCCESS)
         {
            free(cellTableApiPtr);
            LOG_PRINT(LOG_INFO,"delCsPwrCtrlTablehandler(): CsPwrCtrl Table successfully deleted");
            cfgSendAckToCm();
            return;
         }
         else
         {
            free(cellTableApiPtr);
            LOG_PRINT(LOG_CRITICAL,"delCsPwrCtrlTablehandler(): DB del operation Failed");
            cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
            return;
         }
      }
      else
      {
         free(cellTableApiPtr);
         LOG_PRINT(LOG_INFO,"delCsPwrCtrlTablehandler(): Cell is Unlocked Can't Delete");    
         cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
         return;
      }     
   }
   else
   {
      LOG_PRINT(LOG_INFO,"delCsPwrCtrlTablehandler(): Row corresponding to key = {cellid= 0x%x, lac=0x%x} not found in CellTable",receivedMsgPtr->cellId,receivedMsgPtr->lac);
      cfgSendNackToCm(CM_ERR_CELL_NOT_FOUND);
      return;
   }
}/* end of delCellTableHandler */

/********************************* Function  Header********************************
   Function Name:       delCellTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from Cell table 
Other Note:
 ************************************************************************************/
void delCellTableHandler()
{
   CellPerTableApi* receivedMsgPtr = ( CellPerTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   CellPerTableApi* cellTableApiPtr = PNULL;
   CellPerTableIndices apiCellIndex = {0};        
   CellNonPerTableIndices apiNonPerCellIndex = {0};        
   /*CS3.0 Changes : Start */
   HoCtrlTableApi *hoCtrlTablePtr = PNULL;
   HoCtrlTableIndices hoCtrlTableIndex;
   CsPwrCtrlTableIndices apiPwrCtrlIndex;
   CsPwrCtrlTableApi *csPwrCtrlTableApiPtr = PNULL;
   I_S32 ret = CM_FAILURE;
   OamsCfgMrhmCellDelete oamsCellDeleteInd;
   ChnGrpTableSecIndices  chnGrpSecIndex;
   ChnGrpTableApi         *chnGrpData = NULL;
   I_U32                  outCount;
   I_U16                  outSize;
   /*CS3.0 Changes : End */
/*Changes PCU R2.5 Aricent -- START*/
   PsCellTableApi* psCellTableApiPtr = NULL;
   PsCellTableIndices apiPsCellIndex;        
/*Changes PCU R2.5 Aricent -- END*/
   LOG_PRINT(LOG_INFO,"In delCellTableHandler");
   LOG_PRINT(LOG_INFO,"cellId = %u, lac = %u", receivedMsgPtr->cellId, receivedMsgPtr->lac);

   /* Check if entry to be deleted is present in DB or not */
   apiCellIndex.cellId =  receivedMsgPtr->cellId;
   apiCellIndex.lac = receivedMsgPtr->lac;
   apiNonPerCellIndex.cellId = receivedMsgPtr->cellId;
   apiNonPerCellIndex.lac = receivedMsgPtr->lac;

   if (CLIB_SUCCESS == getCellPerTable(&apiCellIndex, &cellTableApiPtr))
   {
      if (cellTableApiPtr->adminState == LOCK)  /* Cell Row can be deleted if Cell is Locked */ 
      {

         /* Check if row for key {cellid, lac} exist in CsPwrCtrlTable 
             if exists, it must be deleted before cell is deleted.
             Added for cs2.5
             */
         apiPwrCtrlIndex.cellId = receivedMsgPtr->cellId;
         apiPwrCtrlIndex.lac = receivedMsgPtr->lac;
         /*Changes PCU R2.5 Aricent -- START*/
         apiPsCellIndex.cellId = receivedMsgPtr->cellId;
         apiPsCellIndex.lac = receivedMsgPtr->lac;
         ret = getPsCellTable(&apiPsCellIndex, &psCellTableApiPtr);
         if (CLIB_SUCCESS == ret)
         {
            free(psCellTableApiPtr);
            LOG_PRINT(LOG_DEBUG,"delCellTableHandler(): Entry already exists for Key {CellID : 0%x, LAC : 0%x }",apiPsCellIndex.cellId,apiPsCellIndex.lac);
            cfgSendNackToCm(CM_ERR_OBJECT_REFERENCED_BY_OTHER_OBJECT);
            return;
         }
         /*Changes PCU R2.5 Aricent -- END*/
         ret = getCsPwrCtrlTable (&apiPwrCtrlIndex, &csPwrCtrlTableApiPtr);
         if (csPwrCtrlTableApiPtr  != PNULL)
         {
            free(csPwrCtrlTableApiPtr);
	    free(cellTableApiPtr);
            LOG_PRINT(LOG_DEBUG,"delCellTableHandler(): CsPwrCtrl Table Exists for Key {CellID : 0%x, LAC : 0%x }",apiPwrCtrlIndex.cellId,apiPwrCtrlIndex.lac);
            cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
            return;
         }
         /*CS3.0 Changes : Start */
         hoCtrlTableIndex.lac = receivedMsgPtr->lac;
         hoCtrlTableIndex.cellId = receivedMsgPtr->cellId;
         ret = getHoCtrlTable(&hoCtrlTableIndex,&hoCtrlTablePtr);
         if(hoCtrlTablePtr != NULL)
         {
            LOG_PRINT(LOG_DEBUG,"Handover control parameter are present in HoCtrl Table for the given Cell");
            free(hoCtrlTablePtr);
	    free(cellTableApiPtr);
            cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
            return;
         }
	 
	 /* On The Fly Changes : Start */
	 if(TRUE == isCellReferenceByNeighbours(receivedMsgPtr->cellId, receivedMsgPtr->lac, 0, 0))
	 {
	    /* CellId & Lac has reference in CsNeighCellsTable. Send Nack To CM */
	    cfgSendNackToCm(CM_ERR_OBJECT_REFERENCED_BY_OTHER_OBJECTS);
	    free(cellTableApiPtr);
	    return;
	 }
	 /* On The Fly Changes : End */
         /*CS3.0 Changes : End */

         /* R2.4 Changes Start */
         chnGrpSecIndex.lac = receivedMsgPtr->lac;
         chnGrpSecIndex.cellId = receivedMsgPtr->cellId;
         ret = retrieveSpecifiedChnGrpRow(&chnGrpSecIndex, &chnGrpData , &outCount, &outSize);
         if(ret == CLIB_SUCCESS)
         {
             LOG_PRINT(LOG_DEBUG,"delCellTableHandler(): ChnGrp Table Exists for Key {CellID : 0%x, LAC : 0%x }",chnGrpSecIndex.cellId,chnGrpSecIndex.lac);
            free(chnGrpData);
	    free(cellTableApiPtr);
            cfgSendNackToCm(CM_ERR_OBJECT_REFERENCED_BY_OTHER_OBJECTS);
            return;
         }
         /* R2.4 Changes End */

        ret = deleteCellPerTable(&apiCellIndex);
        if (CLIB_SUCCESS == ret)
        {
            free(cellTableApiPtr);
            LOG_PRINT(LOG_INFO," In delCellTableHandler: Cell is CLIB_SUCCESSfully deleted, sending Ack");

	    /* Fixed Mantis #4249 : Start */
            /* cfgCellObjectHandlerInit(); */
	    resetCellDataStruct(apiCellIndex.cellId, apiCellIndex.lac);
	    /* Fixed Mantis #4249 : End */

            ret = deleteCellNonPerTable(&apiNonPerCellIndex);
            if(CLIB_SUCCESS == ret)
            {
                LOG_PRINT(LOG_INFO,"In delNonPerCellTableHandler: Cell is CLIB_SUCCESSfully deleted");
            }
            else
            {
               LOG_PRINT(LOG_INFO,"In delNonPerCellTableHandler: Cell is not deleted Error Code = [%d]", ret);
            }
            cfgSendAckToCm();
        /*Changes  Start for KPI PHASE II implementation */
        /* cell is deleted so updating Cell down End time in RadioNwAvalabilityTable */
            updateRadioNwAvlbltyTblAtCellEnableUnbarred(receivedMsgPtr->cellId,
                (I_U32)receivedMsgPtr->lac);
        /*Changes  Ends for KPI PHASE II implementation */
              /* Mantis 15944 starts                        */
	    if(PS_ALLOWED == cellTableApiPtr->psAllowed)
        {
            updateDataAvlbltyTblAtPsCellEnableUnbarred(receivedMsgPtr->cellId,
                (I_U32)receivedMsgPtr->lac);
        }
        
              /* Mantis 15944 ends                        */
        
        /* On The Fly Changes : Start */
	    oamsCellDeleteInd.cellId = receivedMsgPtr->cellId;
	    oamsCellDeleteInd.lac    = receivedMsgPtr->lac;
	    LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_MRHM_CELL_DELETE Msg to MRHM");
               cfgSendMessage(&oamsCellDeleteInd, sizeof(OamsCfgMrhmCellDelete),
                        ENT_CSAPP_MRHM, OAMS_CFG_MRHM_CELL_DELETE, 0);
	    /* On The Fly Changes : End */
         }
         else
         {
            free(cellTableApiPtr);
            LOG_PRINT(LOG_CRITICAL,"In delCellTableHandler: DB del operation Failed Error Code = [%d], sending Nack", ret);
            cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED); 
         }
      }
      else
      {
         free(cellTableApiPtr);
         LOG_PRINT(LOG_INFO," In delCellTableHandler: Cell is Unlocked, sending Nack");    
         cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
      }     
   }     
   else
   {
      LOG_PRINT(LOG_INFO," In delCellTableHandler: Cell requested is not in DB, sending Nack");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
   }
}/* end of delCellTableHandler */


/********************************* Function  Header********************************
   Function Name:       delPsCellTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from PsCell table 
Other Note:
 ************************************************************************************/
void delPsCellTableHandler()
{
   PsCellTableApi* receivedMsgPtr = ( PsCellTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   PsCellTableApi* psCellTableApiPtr = PNULL;
   PsCellTableIndices apiPsCellIndex = {0};
   CellPerTableApi* cellTableApiPtr = PNULL;       
   CellPerTableIndices apiCellIndex = {0};
/*Changes PCU R2.5 Aricent -- START*/
   PsCellStatusTableIndices psCellStatusTableIndicesBuff;
/*Changes PCU R2.5 Aricent -- END*/
   I_S32  ret = CM_FAILURE;

   LOG_PRINT(LOG_INFO,"In delPsCellTableHandler");
   LOG_PRINT(LOG_INFO,"cellid = %u, lac = %u", receivedMsgPtr->cellId, receivedMsgPtr->lac) ;

   /* Check if entry to be deleted is present in DB or not */
   apiPsCellIndex.cellId =  receivedMsgPtr->cellId;
   apiPsCellIndex.lac = receivedMsgPtr->lac;
   ret = getPsCellTable(&apiPsCellIndex, &psCellTableApiPtr);
   if (CLIB_SUCCESS == ret)
   {        
      apiCellIndex.cellId =  receivedMsgPtr->cellId;
      apiCellIndex.lac = receivedMsgPtr->lac;

      ret = getCellPerTable(&apiCellIndex, &cellTableApiPtr);      
      if (ret != CLIB_SUCCESS)
      {
         free(psCellTableApiPtr);
         LOG_PRINT(LOG_MAJOR,"delPsCellTableHandler: getCellTable failed, sending Nack");    
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
         return;      
      } 
      if (cellTableApiPtr->adminState != LOCK)
      {
         free(cellTableApiPtr);
         free(psCellTableApiPtr);
         LOG_PRINT(LOG_MAJOR,"delPsCellTableHandler: Cell is Unlocked, sending Nack");     
         cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);
         return;       
      }
      ret = deletePsCellTable(&apiPsCellIndex);
      if (CLIB_SUCCESS == ret)
      {
/*Changes PCU R2.5 Aricent -- START*/
          /* Delete rows from Cell level PS Performance Counters for this cell */
         deleteRowFromPsPerformanceCounterTablesForCell(receivedMsgPtr->cellId, receivedMsgPtr->lac);

         /*Delete PS Cell Status Table*/
         psCellStatusTableIndicesBuff.cellId = apiPsCellIndex.cellId;
         psCellStatusTableIndicesBuff.lac = apiPsCellIndex.lac;
         ret = deletePsCellStatusTable(&psCellStatusTableIndicesBuff);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_CRITICAL, "Requested Entry could not be deleted. Error Code = [%d], Sanding Nack", ret);
            cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
            free(cellTableApiPtr);
            free(psCellTableApiPtr);
            return;
         }
/*Changes PCU R2.5 Aricent -- END*/         
         free(psCellTableApiPtr);
         free(cellTableApiPtr);
         LOG_PRINT(LOG_INFO," delPsCellTableHandler: PsCell is deleted, sending Ack");      
         cfgSendAckToCm();
      }
      else
      {
         free(cellTableApiPtr);
         free(psCellTableApiPtr);
         LOG_PRINT(LOG_CRITICAL,"delPsCellTableHandler: deletePsCellTable failed, Error Code = [%d] sending Nack", ret);      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"delPsCellTableHandler: PsCell requested is not in Table, sending Nack");
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
   }     

} /* end of delPsCellTableHandler */


/********************************* Function  Header********************************
   Function Name:       delCsExternalCellTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from CsExternalCell table 
Other Note:
 ************************************************************************************/
void delCsExternalCellTableHandler()
{
   CsExternalCellTableApi* receivedMsgPtr = ( CsExternalCellTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   CsExternalCellTableApi* csExternalCellTableApiPtr = PNULL;
   CsExternalCellTableIndices apiCsExCellIndex = {0};
   OamsCfgMrhmCellDelete oamsCellDeleteInd;
   I_S32  ret = 1;

   LOG_PRINT(LOG_INFO," In delCsExternalCellTableHandler");

   /* Check if entry to be deleted is present in DB or not */
   apiCsExCellIndex.csExtCellId =  receivedMsgPtr->csExtCellId;
   apiCsExCellIndex.lac =  receivedMsgPtr->lac;
   apiCsExCellIndex.mnc =  receivedMsgPtr->mnc;
   apiCsExCellIndex.mcc =  receivedMsgPtr->mcc;

   ret = getCsExternalCellTable(&apiCsExCellIndex, &csExternalCellTableApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delCsExternalCellTableHandler: Cell requested is not in Table, sending Nack");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;  
   }

   if(TRUE == isCellReferenceByNeighbours(receivedMsgPtr->csExtCellId, receivedMsgPtr->lac, 
					  receivedMsgPtr->mcc, receivedMsgPtr->mnc
					 )
     )
   {
      /* CellId & Lac has reference in CsNeighCellsTable. Send Nack To CM */
      cfgSendNackToCm(CM_ERR_OBJECT_REFERENCED_BY_OTHER_OBJECTS);
      free(csExternalCellTableApiPtr);
      return;
   }
   /* On The Fly Changes : End */

   /* delete CsExternalCell from table */
   if (deleteCsExternalCellTable(&apiCsExCellIndex) == CLIB_SUCCESS)
   {
      free(csExternalCellTableApiPtr);
      LOG_PRINT(LOG_INFO," csExternalCell is deleted, sending Ack");   
      cfgSendAckToCm();
      /* On The Fly Changes : Start */
      /* Send CellDelete Msg to MRHM */
      oamsCellDeleteInd.cellId = receivedMsgPtr->csExtCellId;
      oamsCellDeleteInd.lac    = receivedMsgPtr->lac;
      LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_MRHM_CELL_DELETE Msg to MRHM");
      cfgSendMessage(&oamsCellDeleteInd, sizeof(OamsCfgMrhmCellDelete),
                      ENT_CSAPP_MRHM, OAMS_CFG_MRHM_CELL_DELETE, 0); 
      /* On The Fly Changes : End */
   } 
   else
   {
      free(csExternalCellTableApiPtr);
      LOG_PRINT(LOG_INFO," deleteCsExternalCellTable failed, sending Nack");   
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }
} /* end of delCsExternalCellTableHandler */


/********************************* Function  Header********************************
   Function Name:       delLaTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from La table 
Other Note:
 ************************************************************************************/
void delLaTableHandler()
{
   LaTableApi* receivedMsgPtr = ( LaTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   LaTableApi* laTableApiPtr = PNULL;
   LaTableIndices apiLaIndex = {0};
   I_S32  ret = CM_FAILURE;
   CellPerTableTerIndices cellPerTableTerIndex;
   CellPerTableApi *cellPerTblPtr;

   /*Changes PCU R2.5 Aricent --START*/
   RaTableApi* raTableApiPtr = PNULL;
   RaTableApi* raTableApiAllPtr = PNULL;
   I_U32  outRows = 0;
   I_U16  outSize = 0;
   I_U32  i = 0;
   /*Changes PCU R2.5 Aricent --END*/

   LOG_PRINT(LOG_INFO,"In delLaTableHandler");
   LOG_PRINT(LOG_INFO,"lac = %u", receivedMsgPtr->lac);

	 /*Fix for MantisId:11357 Starts*/ 
   cellPerTableTerIndex.lac = receivedMsgPtr->lac;
   ret = isLacExistInCellTable(&cellPerTableTerIndex,&cellPerTblPtr, &outRows, &outSize);
   if(ret == CLIB_SUCCESS)
   {
       LOG_PRINT(DEBUG,"LAC is referenced by CellId:%d",cellPerTblPtr->cellId);
       free(cellPerTblPtr);
       cfgSendNackToCm(CM_ERR_OBJECT_REFERENCED_BY_OTHER_OBJECT);
       return;
   }
   
   /*Fix for MantisId:11357 Ends*/ 

   /* Check if entry to be deleted is present in DB or not */
   apiLaIndex.lac =  receivedMsgPtr->lac;

   ret = getLaTable(&apiLaIndex, &laTableApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"Requested Entry is not in Table Error Code = [%d], sending Nack", ret);   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
/* Mantis id 26059 Starts */
#if 0
   /* Check if BSS Admin State is LOCK or not */ 
   if (UNLOCK == bssLock())
   {
      free(laTableApiPtr);
      LOG_PRINT(LOG_INFO,"BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
#endif
/* Mantis Id 26059 ends */
   /*Changes PCU R2.5 Aricent --START*/
   ret =  getallRaTable(&raTableApiAllPtr, &outRows, &outSize);
   if(CLIB_SUCCESS == ret)
   {
      for(i = 0; i < outRows; i++)
      {
         raTableApiPtr = (RaTableApi*)(((I_U8*)raTableApiAllPtr + i * outSize));
         if (raTableApiPtr->lac == receivedMsgPtr->lac)
         {
            LOG_PRINT(LOG_INFO,"LAC %u is referenced by RAC, rac = [%u] in RaTable. Sending Nack",
                      raTableApiPtr->lac, raTableApiPtr->rac);
            free(raTableApiAllPtr);
            cfgSendNackToCm(CM_ERR_OBJECT_REFERENCED_BY_OTHER_OBJECT);
            return;
         }
      }
   }
   /*Changes PCU R2.5 Aricent --END*/
   
   ret = deleteLaTable(&apiLaIndex);
   if (CLIB_SUCCESS == ret)
   {
      free(laTableApiPtr);
      LOG_PRINT(LOG_INFO,"Requested Entry is deleted, sending Ack");   
      cfgSendAckToCm();
   } 
   else
   {
      free(laTableApiPtr);
      LOG_PRINT(LOG_CRITICAL,"deleteLaTable failed, Error Code = [%d] sending Nack", ret);   
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }
} /* end of delLaTableHandler */


/********************************* Function  Header********************************
   Function Name:       delRaTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from Ra table 
Other Note:
 ************************************************************************************/
void delRaTableHandler()
{
   RaTableApi               *receivedMsgPtr       = (RaTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   RaTableApi               *raTableApiPtr        = NULL;
   RaTableIndices           apiRaIndex;
   I_S32                    ret                   = CM_FAILURE;
/*Changes R2.5 Aricent -- Start*/
   PsCellTableApi           *psCellTableApiPtr    = NULL;
   PsCellTableApi           *tmpPsCellTableApiPtr = NULL;
   I_U32                    outRows = 0;
   I_U32                    i                     = 0;
   I_U16                    outSize = 0;
/*Changes R2.5 Aricent -- End*/

   LOG_PRINT(LOG_INFO,"In delRaTableHandler");
   LOG_PRINT(LOG_INFO,"lac = %u, rac = %u", receivedMsgPtr->lac, receivedMsgPtr->rac);


   /* Check if entry to be deleted is present in DB or not */
   apiRaIndex.lac =  receivedMsgPtr->lac;
   apiRaIndex.rac =  receivedMsgPtr->rac;

   ret = getRaTable(&apiRaIndex, &raTableApiPtr);   
   if (CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_INFO,"Requested Entry is not in Table Error Code = [%d] , sending Nack", ret);   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }


/*Changes R2.5 Aricent -- Start*/
   /*Check if lac has any reference in PsCellTable*/
   ret =  getallPsCellTable(&psCellTableApiPtr, &outRows, &outSize);
   if(CLIB_SUCCESS == ret)
   {
      for(i = 0; i < outRows; i++)
      {
         tmpPsCellTableApiPtr = (PsCellTableApi*)(((I_U8*)psCellTableApiPtr + i * sizeof(PsCellTableApi)));
		 /* Mantis 13885 start*/
         if (tmpPsCellTableApiPtr->lac == receivedMsgPtr->lac && tmpPsCellTableApiPtr->rac == receivedMsgPtr->rac)
		 /* Mantis 13885 end*/
         {
            LOG_PRINT(LOG_INFO,"LAC %u is referenced by cell cellId = [%u] , lac = [%u] in PsCellTable. Sending Nack",
                      tmpPsCellTableApiPtr->lac, tmpPsCellTableApiPtr->cellId, tmpPsCellTableApiPtr->lac);
            free(psCellTableApiPtr);
            free(raTableApiPtr);
            cfgSendNackToCm(CM_ERR_OBJECT_REFERENCED_BY_OTHER_OBJECT);
            return;
         }
      }
   }
/*Changes R2.5 Aricent -- End*/
   ret = deleteRaTable(&apiRaIndex);
   if (CLIB_SUCCESS == ret)
   {
      free(psCellTableApiPtr);
      free(raTableApiPtr);
      LOG_PRINT(LOG_INFO,"Requested Entry is deleted, sending Ack");   
      cfgSendAckToCm();
      return;
   }
   else
   {
      free(psCellTableApiPtr);
      free(raTableApiPtr);
      LOG_PRINT(LOG_MAJOR,"DB call deleteRaTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      return;
   }
} /* end of delRaTableHandler */


/********************************* Function  Header********************************
   Function Name:       delChnGrpTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from ChnGrp table 
Other Note:
 ************************************************************************************/
void delChnGrpTableHandler()
{
   ChnGrpTableApi* receivedMsgPtr = ( ChnGrpTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   ChnGrpTableApi* chnGrpTblApiPtr = PNULL;
   ChnGrpTableIndices apiChnGrpIndex = {0};
   CellPerTableApi* cellTableApiPtr = PNULL;

   CellPerTableIndices apiCellIndex = {0};
   I_S32  ret = CM_FAILURE; 

   LOG_PRINT(LOG_INFO,"In delChnGrpTableHandler");
   LOG_PRINT(LOG_INFO,"cellId = %u, lac = %u, ChnGrpId = %u", receivedMsgPtr->cellId, receivedMsgPtr->lac, receivedMsgPtr->chnGrpId);

   /* Check if entry to be deleted is present in DB or not */
   apiChnGrpIndex.chnGrpId =  receivedMsgPtr->chnGrpId;
   apiChnGrpIndex.cellId =  receivedMsgPtr->cellId;
   apiChnGrpIndex.lac = receivedMsgPtr->lac;

   ret = getChnGrpTable(&apiChnGrpIndex, &chnGrpTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }

   /* Check if Cell Admin State is LOCK or not */
   apiCellIndex.cellId =  receivedMsgPtr->cellId;
   apiCellIndex.lac = receivedMsgPtr->lac;
   ret = getCellPerTable(&apiCellIndex, &cellTableApiPtr);

   if (cellTableApiPtr == PNULL)
   {
      free(chnGrpTblApiPtr);
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;
   }    

   if (cellTableApiPtr->adminState == UNLOCK)
   {
      free(cellTableApiPtr);
      free(chnGrpTblApiPtr);
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;
   }

   if (deleteChnGrpTable(&apiChnGrpIndex) == CLIB_SUCCESS)
   {
      /* R2.4 change Start */
     
      if (chnGrpTblApiPtr->cbch == TRUE )
      {
         sendDelCbCellToCbsh( receivedMsgPtr->cellId, receivedMsgPtr->lac);
      }
      free(chnGrpTblApiPtr);
      /* R2.4 change End */
      free(cellTableApiPtr);
      LOG_PRINT(LOG_INFO,"Requested Entry is deleted, sending Ack");   
      cfgSendAckToCm();
   }
   else
   {
      free(chnGrpTblApiPtr);
      free(cellTableApiPtr);
      LOG_PRINT(LOG_CRITICAL,"deleteChnGrpTable failed, sending Nack");
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
   }       
} /* end of delChnGrpTableHandler */


/********************************* Function  Header********************************
   Function Name:       delPtrxTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from Ptrx table 
Other Note:
 ************************************************************************************/
void delPtrxTableHandler()
{
   LOG_PRINT(LOG_INFO," delPtrxTableHandler: Row can't be deleted, Sending Nack");
   cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);

} /* end of delPtrxTableHandler */

/********************************* Function  Header********************************
   Function Name:       delE1TableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from E1 table 
Other Note:
 ************************************************************************************/
void delE1TableHandler()
{
   LOG_PRINT(LOG_INFO," delE1TableHandler: Row can't be deleted, Sending Nack");
   cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);

} /* end of delE1TableHandler */


/********************************* Function  Header********************************
   Function Name:       delTimeSlotTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from TimeSlot table 
Other Note:
 ************************************************************************************/
void delTimeSlotTableHandler()
{
   LOG_PRINT(LOG_INFO," delTimeSlotTableHandler: Row can't be deleted, Sending Nack");
   cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);

} /* end of delTimeSlotTableHandler */


/********************************* Function  Header********************************
   Function Name:       delCsNeighCellTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from CsNeighCell table 
Other Note:
 ************************************************************************************/
void delCsNeighCellTableHandler()
{
   CsNeighCellsTableApi* receivedMsgPtr = (CsNeighCellsTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   CsNeighCellsTableApi* csNeighCellTblApiPtr = PNULL;
   CsNeighCellsTableIndices apiCsNeighCellIndex = {0};
   I_S32  ret = -1;
   I_U16 cellIndex = 0;
   CellPerTableIndices cellTableInd;
   CellPerTableApi *cellTableApiPtr = NULL;
   OamsCfgCellhCsNeighCellsChange csNeighChangePtr;

   LOG_PRINT(LOG_INFO," In delCsNeighCellTableHandler");

   /* Check if entry to be deleted is present in DB or not */
   /* On The Fly Changes : Start */
   apiCsNeighCellIndex.lac 		=  receivedMsgPtr->lac;
   apiCsNeighCellIndex.cellId 		=  receivedMsgPtr->cellId;
   apiCsNeighCellIndex.neighborMcc 	=  receivedMsgPtr->neighborMcc;
   apiCsNeighCellIndex.neighborMnc 	=  receivedMsgPtr->neighborMnc;
   apiCsNeighCellIndex.neighborLac	=  receivedMsgPtr->neighborLac;
   apiCsNeighCellIndex.neighborCellId 	=  receivedMsgPtr->neighborCellId;
   /* On The Fly Changes : End */

   ret = getCsNeighCellsTable(&apiCsNeighCellIndex, &csNeighCellTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   /* Added For WCDMA-GSM HO Feature : Start */
   if(csNeighCellTblApiPtr->radioAccessType == WCDMA_FDD)
   {
     cellTableInd.cellId = receivedMsgPtr->cellId;
     cellTableInd.lac    = receivedMsgPtr->lac;
     ret = getCellPerTable(&cellTableInd, &cellTableApiPtr);
     if(ret != DBLIB_SUCCESS)
     {
        LOG_PRINT(LOG_INFO,"Cell is Not Configured at BSC");
     }
     else
     {
       if(  cellTableApiPtr->adminState != LOCKED )
       {
             LOG_PRINT(LOG_INFO,"WCDMA_FDD neighbour deletion is not allowed in Cell Unlocked state");
             cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
             free(csNeighCellTblApiPtr);
             return;
       }  
     }
   }  
   /* Added For WCDMA-GSM HO Feature : End */
   free(csNeighCellTblApiPtr);
   if (deleteCsNeighCellsTable(&apiCsNeighCellIndex) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
      cfgSendAckToCm();
      /* On The Fly Changes : Start */
      /* Send Neighbour Change Msg to CELLH if Cell is Unlocked */
      cellTableInd.cellId = receivedMsgPtr->cellId;
      cellTableInd.lac    = receivedMsgPtr->lac;
      ret = getCellPerTable(&cellTableInd, &cellTableApiPtr);
      if(ret != DBLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"Cell is Not Configured at BSC");
      }
      else if(cellTableApiPtr->adminState == UNLOCKED)
      {
         free(cellTableApiPtr);
         getCellIndex(receivedMsgPtr->lac, receivedMsgPtr->cellId, &cellIndex);
         csNeighChangePtr.cellId = receivedMsgPtr->cellId;
         csNeighChangePtr.lac    = receivedMsgPtr->lac;
         csNeighChangePtr.cellIndex    = cellIndex;
         LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE Msg to CELLH");
         cfgSendMessage(&csNeighChangePtr, sizeof(OamsCfgCellhCsNeighCellsChange),
                        ENT_OAMS_CELLH, OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE, 0);
      }
      else
      {
         LOG_PRINT(LOG_INFO,"Cell is Locked. Not send OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE Msg to CELLH");
         free(cellTableApiPtr);
      }
      /* On The Fly Changes : End */
   }
   else
   {
      LOG_PRINT(LOG_CRITICAL," deleteCsNeighCellTable failed, sending Nack");         
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }
} /* end of delCsNeighCellTableHandler */


/********************************* Function  Header********************************
   Function Name:       delArfcnListTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from ArfcnList table 
Other Note:
 ************************************************************************************/
void delArfcnListTableHandler()
{
   ArfcnListTableApi* receivedMsgPtr = ( ArfcnListTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   ArfcnListTableApi* arfcnListTblApiPtr = PNULL;
   ArfcnListTableIndices apiArfcnListIndex = {0};
   I_S32 ret = 1;

   LOG_PRINT(LOG_INFO," In delArfcnListTableHandler");

   /* Check if entry to be deleted is present in DB or not */      
   apiArfcnListIndex.band =  receivedMsgPtr->band;
   apiArfcnListIndex.arfcn =  receivedMsgPtr->arfcn;

   ret = getArfcnListTable(&apiArfcnListIndex, &arfcnListTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }

   #if 0
   /* Check if BSS Admin State is LOCK or not */ 
   if (UNLOCK == bssLock())
   {
      free(arfcnListTblApiPtr);
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   #endif

   /* Check that Arfcn to be deleted is not used at BSC */
   if(TRUE == isArfcnPresInChnGrpTable(receivedMsgPtr->arfcn))
   {
      LOG_PRINT(LOG_MAJOR,"Received Arfcn is in Use at BSC");
      free(arfcnListTblApiPtr);
      cfgSendNackToCm(CM_ERR_OBJECT_REFERENCED_BY_OTHER_OBJECTS);
      return;
   }

   if (deleteArfcnListTable(&apiArfcnListIndex) == CLIB_SUCCESS)
   {
      free(arfcnListTblApiPtr);
      LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
      cfgSendAckToCm();
   }
   else
   {
      free(arfcnListTblApiPtr);
      LOG_PRINT(LOG_CRITICAL," deleteArfcnListTable failed, sending Nack");         
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }
} /* end of delArfcnListTableHandler */


/********************************* Function  Header********************************
   Function Name:       delAInterfaceTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from AInterface table 
Other Note:
 ************************************************************************************/
void delAInterfaceTableHandler()
{
   /**************************************************************
      CFG will send CM_ERR_END message to CM as all the attributes are
      "Read-Only" in this table.

    *************************************************************/ 
   LOG_PRINT(LOG_INFO," In delAInterfaceTableHandler");
   LOG_PRINT(LOG_INFO," delAInterfaceTableHandler: Sending nack as Read-Only Table");
   cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
   return;

} /* end of delAInterfaceTableHandler */

#if 0 /* CS4.0 HA Stack Changes */
/********************************* Function  Header********************************
   Function Name:       delMtp3LinksetTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from Mtp3Linkset table 
Other Note:
 ************************************************************************************/
void delMtp3LinksetTableHandler()
{
   Mtp3LinksetTableIndices* receivedMsgPtr = ( Mtp3LinksetTableIndices* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   Mtp3LinksetTableApi* mtp3LinksetTblApiPtr = PNULL;
   I_PVoid scmMessagePtr = PNULL;
   I_S32  ret = CLIB_SUCCESS;

   LOG_PRINT(LOG_INFO," In delMtp3LinksetTableHandler");

   /* Check if BSS Admin State is LOCK or not */     
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }

   /* Check if entry to be deleted is present in DB or not */
   ret = getMtp3LinksetTable(receivedMsgPtr, &mtp3LinksetTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   else
   {
      gStoredMsgBufPtr = AlocOrdBuf(sizeof(Mtp3LinksetTableIndices));
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         free(mtp3LinksetTblApiPtr);
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy((I_U8 *)gStoredMsgBufPtr, (I_U8*)receivedMsgPtr,sizeof(Mtp3LinksetTableIndices));

      scmMessagePtr= AlocOrdBuf((sizeof(Mtp3LinksetTableApi)+sizeof(sCmMsg)));
      if(PNULL == scmMessagePtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         free(mtp3LinksetTblApiPtr);
         DalocOrdBuf(gStoredMsgBufPtr);
         return;  
      }
      memcpy((I_U8 *)(scmMessagePtr+sizeof(sCmMsg)), (I_U8*)mtp3LinksetTblApiPtr,sizeof(Mtp3LinksetTableApi));

      cfgSendCmMessage((void * )scmMessagePtr, (sizeof(Mtp3LinksetTableApi)+sizeof(sCmMsg)),                                                       ENT_OAM_OIL, BSC_API_DEL_MTP3LINKSETTABLE,0);
      DalocOrdBuf(scmMessagePtr);
      free(mtp3LinksetTblApiPtr);
      cfgStartTimer();
   }
}

void delMtp3LinksetTableHandlerScmAck()
{
   Mtp3LinksetTableIndices* receivedMsgPtr = ( Mtp3LinksetTableIndices* )gStoredMsgBufPtr;
   Mtp3LinksetStsTableIndices mtp3LinksetStsTableIndices;

   cfgStopTimer();
   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delete Mtp3LinksetTableApi failed, as SCM sent  Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
      if(receivedMsgPtr != NULL)
         DalocOrdBuf(gStoredMsgBufPtr);
      return ;
   }

   if (receivedMsgPtr != NULL )
   {
      if (deleteMtp3LinksetTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
         cfgSendAckToCm(CM_SUCCESS);
         /* CCB #20 Delete from Mtp3LinksetStsTableApi */
         mtp3LinksetStsTableIndices.MTP3LinksetlinksetID = receivedMsgPtr->MTP3LinksetlinksetID;
         if (deleteMtp3LinksetStsTable(&mtp3LinksetStsTableIndices) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_MAJOR," deleteMtp3LinksetStsTable FAILED");
         }
      }
      else
      {
         LOG_PRINT(LOG_INFO," deleteMtp3LinksetTable failed, sending Nack");      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
      DalocOrdBuf(gStoredMsgBufPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO," deleteMtp3LinksetTable failed, sending Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
   }

} /* end of delMtp3LinksetTableHandler */



/********************************* Function  Header********************************
   Function Name:       delMtp3RouteTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from Mtp3Route table 
Other Note:
 ************************************************************************************/
void delMtp3RouteTableHandler()
{
   Mtp3RouteTableIndices* receivedMsgPtr = ( Mtp3RouteTableIndices* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   Mtp3RouteTableApi* mtp3RouteTblApiPtr = PNULL;
   I_PVoid scmMessagePtr = PNULL;
   I_S32  ret = CLIB_SUCCESS;

   LOG_PRINT(LOG_INFO," In delMtp3RouteTableHandler");
   /* Check if BSS Admin State is LOCK or not */     
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }

   /* Check if entry to be deleted is present in DB or not */
   ret = getMtp3RouteTable(receivedMsgPtr, &mtp3RouteTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   else
   {
      gStoredMsgBufPtr = AlocOrdBuf(sizeof(Mtp3RouteTableIndices));
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         free(mtp3RouteTblApiPtr);
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy(((I_U8 *)gStoredMsgBufPtr),(I_U8*)receivedMsgPtr,sizeof(Mtp3RouteTableIndices));

      scmMessagePtr = AlocOrdBuf(sizeof(Mtp3RouteTableApi)+sizeof(sCmMsg));
      if(PNULL == scmMessagePtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         DalocOrdBuf(gStoredMsgBufPtr);
         free(mtp3RouteTblApiPtr);
         return;  
      }
      memcpy((I_U8 *)(scmMessagePtr+sizeof(sCmMsg)),(I_U8*)mtp3RouteTblApiPtr,sizeof(Mtp3RouteTableApi));

      cfgSendCmMessage((void * )scmMessagePtr,(sizeof(Mtp3RouteTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL, BSC_API_DEL_MTP3ROUTETABLE,0);
      DalocOrdBuf(scmMessagePtr);
      free(mtp3RouteTblApiPtr);
      cfgStartTimer();
   }
}

void delMtp3RouteTableHandlerScmAck()
{
   Mtp3RouteTableIndices* receivedMsgPtr = ( Mtp3RouteTableIndices* )gStoredMsgBufPtr;

   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delete Mtp3RouteTableApi failed, as SCM sent  Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
      if(gStoredMsgBufPtr != NULL )
         DalocOrdBuf(gStoredMsgBufPtr);
      return ;
   }

   if (receivedMsgPtr != NULL )
   {
      /* Check if entry to be deleted is present in DB or not */
      if (deleteMtp3RouteTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
         cfgSendAckToCm(CM_SUCCESS);
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," Mtp3RouteTableIndices failed, sending Nack");      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
      DalocOrdBuf(gStoredMsgBufPtr);
   }
   else
   {
      LOG_PRINT(LOG_CRITICAL," Mtp3RouteTableIndices failed, sending Nack");      
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }
} /* end of delMtp3RouteTableHandler */


/********************************* Function  Header********************************
   Function Name:       delMtp3LinkSetAdminStateTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from Mtp3LinkSetAdminState table 
Other Note:
 ************************************************************************************/

void delMtp3LinksetStsTableHandler()
{
   Mtp3LinksetStsTableIndices* receivedMsgPtr = ( Mtp3LinksetStsTableIndices* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   Mtp3LinksetStsTableApi* mtp3LinkSetAdminStateTblApiPtr = PNULL;
   I_PVoid scmMessagePtr = PNULL;
   I_S32  ret = CLIB_SUCCESS;

   LOG_PRINT(LOG_INFO," In delMtp3LinksetStsTableHandler");

   /* Check if BSS Admin State is LOCK or not */     
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }

   /* Check if entry to be deleted is present in DB or not */
   ret = getMtp3LinksetStsTable(receivedMsgPtr, &mtp3LinkSetAdminStateTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   else
   {
      gStoredMsgBufPtr = AlocOrdBuf(sizeof(Mtp3LinksetStsTableIndices));
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         free(mtp3LinkSetAdminStateTblApiPtr);
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy(((I_U8 *)gStoredMsgBufPtr),
            (I_U8*)receivedMsgPtr,sizeof(Mtp3LinksetStsTableIndices));

      scmMessagePtr = AlocOrdBuf(sizeof(Mtp3LinksetStsTableApi)+sizeof(sCmMsg));
      if(PNULL == scmMessagePtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         DalocOrdBuf(gStoredMsgBufPtr);
         free(mtp3LinkSetAdminStateTblApiPtr);
         return;  
      }
      memcpy((I_U8 *)(scmMessagePtr+sizeof(sCmMsg)),
            (I_U8*)mtp3LinkSetAdminStateTblApiPtr,sizeof(Mtp3LinksetStsTableApi));

      cfgSendCmMessage((void * )scmMessagePtr, 
            (sizeof(Mtp3LinksetStsTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL, BSC_API_DEL_MTP3LINKSETSTSTABLE,0);
      DalocOrdBuf(scmMessagePtr);
      free(mtp3LinkSetAdminStateTblApiPtr);
      cfgStartTimer();
   }
}
void delMtp3LinksetStsTableHandlerScmAck()
{
   Mtp3LinksetStsTableIndices* receivedMsgPtr = ( Mtp3LinksetStsTableIndices* )gStoredMsgBufPtr;

   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delete Mtp3LinksetStsTableApi failed, as SCM sent  Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
      if( receivedMsgPtr != NULL)
         DalocOrdBuf(gStoredMsgBufPtr);
      return ;
   }

   if (receivedMsgPtr != NULL )
   {
      /* Check if entry to be deleted is present in DB or not */
      if (deleteMtp3LinksetStsTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
         cfgSendAckToCm(CM_SUCCESS);
      }
      else
      {
         LOG_PRINT(LOG_INFO," Mtp3LinksetStsTableIndices failed, sending Nack");      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
      DalocOrdBuf(gStoredMsgBufPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO," Mtp3LinksetStsTableIndices failed, sending Nack");      
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }

} /* end of delMtp3LinksetStsTableHandler */


/********************************* Function  Header********************************
   Function Name:       delMtp3LinkTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from Mtp3Link table 
Other Note:
 ************************************************************************************/
void delMtp3LinkTableHandler()
{
   Mtp3LinkTableIndices* receivedMsgPtr = ( Mtp3LinkTableIndices* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   Mtp3LinkTableApi* mtp3LinkTblApiPtr = PNULL;
   I_PVoid scmMessagePtr = PNULL;
   I_S32  ret = CLIB_SUCCESS;

   LOG_PRINT(LOG_INFO," In delMtp3LinkTableHandler");
   /* Check if BSS Admin State is LOCK or not */     
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   /* Check if entry to be deleted is present in DB or not */
   ret = getMtp3LinkTable(receivedMsgPtr, &mtp3LinkTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   else
   {
      gStoredMsgBufPtr = AlocOrdBuf(sizeof(Mtp3LinkTableIndices));
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         free(mtp3LinkTblApiPtr);
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy(((I_U8 *)gStoredMsgBufPtr),(I_U8*)receivedMsgPtr,sizeof(Mtp3LinkTableIndices));

      scmMessagePtr = AlocOrdBuf(sizeof(Mtp3LinkTableApi)+sizeof(sCmMsg));
      if(PNULL == scmMessagePtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         DalocOrdBuf(gStoredMsgBufPtr);
         free(mtp3LinkTblApiPtr);
         return;  
      }
      memcpy((I_U8 *)(scmMessagePtr+sizeof(sCmMsg)),(I_U8*)mtp3LinkTblApiPtr,sizeof(Mtp3LinkTableApi));
      cfgSendCmMessage((void * )scmMessagePtr, sizeof(Mtp3LinkTableApi)+sizeof(sCmMsg),
            ENT_OAM_OIL, BSC_API_DEL_MTP3LINKTABLE,0);
      DalocOrdBuf(scmMessagePtr);
      free(mtp3LinkTblApiPtr);
      cfgStartTimer();
   }
}

void delMtp3LinkTableHandlerScmAck()
{
   Mtp3LinkTableIndices* receivedMsgPtr = ( Mtp3LinkTableIndices* )gStoredMsgBufPtr;
   Mtp3LinkStsTableIndices mtp3LinkStsTableInd;

   cfgStopTimer();
   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delete Mtp3LinkTableApi failed, as SCM sent  Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
      if(receivedMsgPtr != NULL)
         DalocOrdBuf(gStoredMsgBufPtr);
      return ;
   }
   if (receivedMsgPtr != NULL )
   {
      /* Check if entry to be deleted is present in DB or not */
      if (deleteMtp3LinkTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
         cfgSendAckToCm(CM_SUCCESS);
	 /* Delete Data from Mtp3LinkStsTable */
	 mtp3LinkStsTableInd.MTP3LinklinksetID  =  receivedMsgPtr->mtp3LinklinksetID;
	 mtp3LinkStsTableInd.MTP3Linklinkcode   =  receivedMsgPtr->mtp3LinklinkCode;
	 if(deleteMtp3LinkStsTable(&mtp3LinkStsTableInd) != CLIB_SUCCESS)
	 {
	    LOG_PRINT(LOG_MAJOR,"Delete on Mtp3LinkStsTable Failed");
	 }
      }
      else
      {
         LOG_PRINT(LOG_INFO," Mtp3LinkTableIndices failed, sending Nack");      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
      DalocOrdBuf(gStoredMsgBufPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO," Mtp3LinkTableIndices failed, sending Nack");      
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }
} /* end of delMtp3LinkTableHandler */


/********************************* Function  Header********************************
   Function Name:       delSccpSsnConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from SccpSsnConfig table 
Other Note:
 ************************************************************************************/
void delSccpSsnConfigTableHandler()
{
   SccpSsnConfigTableIndices* receivedMsgPtr = ( SccpSsnConfigTableIndices* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   SccpSsnConfigTableApi* sccpSsnConfigApiPtr = PNULL;
   I_PVoid scmMessagePtr = PNULL; 
   I_S32  ret = CLIB_SUCCESS;

   LOG_PRINT(LOG_INFO," In delSccpSsnConfigTableHandler");

   /* Check if BSS Admin State is LOCK or not */     
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   /* Check if entry to be deleted is present in DB or not */
   ret = getSccpSsnConfigTable(receivedMsgPtr, &sccpSsnConfigApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   else
   {
      gStoredMsgBufPtr = AlocOrdBuf(sizeof(SccpSsnConfigTableIndices));
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         free(sccpSsnConfigApiPtr);
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy(((I_U8 *)gStoredMsgBufPtr),(I_U8*)receivedMsgPtr,sizeof(SccpSsnConfigTableIndices));

      scmMessagePtr= AlocOrdBuf((sizeof(SccpSsnConfigTableApi)+sizeof(sCmMsg)));
      if(PNULL == scmMessagePtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         DalocOrdBuf(gStoredMsgBufPtr);
         free(sccpSsnConfigApiPtr);
         return;  
      }
      memcpy((I_U8 *)(scmMessagePtr+sizeof(sCmMsg)), (I_U8*)sccpSsnConfigApiPtr,sizeof(SccpSsnConfigTableApi));

      cfgSendCmMessage((void * )scmMessagePtr, sizeof(SccpSsnConfigTableApi)+sizeof(sCmMsg),
            ENT_OAM_OIL, BSC_API_DEL_SCCPSSNCONFIGTABLE,0);
      DalocOrdBuf(scmMessagePtr);
      free(sccpSsnConfigApiPtr);
      cfgStartTimer();
   }
}


void delSccpSsnConfigTableHandlerScmAck()
{
   SccpSsnConfigTableIndices* receivedMsgPtr = ( SccpSsnConfigTableIndices* )gStoredMsgBufPtr;

   cfgStopTimer();
   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delete SccpSsnConfigTableApi failed, as SCM sent  Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
      if(receivedMsgPtr != NULL)
         DalocOrdBuf(gStoredMsgBufPtr);
      return ;
   }

   if (receivedMsgPtr != NULL )
   {
      /* Check if entry to be deleted is present in DB or not */
      if (deleteSccpSsnConfigTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
         cfgSendAckToCm(CM_SUCCESS);
         SccpSsnStsTableIndices sccpSsnStsTableIndices;
         sccpSsnStsTableIndices.sccpSsnConfigssn = receivedMsgPtr->sccpSsnConfigssn;
         sccpSsnStsTableIndices.sccpSsnConfigpc = receivedMsgPtr->sccpSsnConfigpc;
         sccpSsnStsTableIndices.sccpSsnConfigni = receivedMsgPtr->sccpSsnConfigni;
         sccpSsnStsTableIndices.sccpSsnConfigisLocal = receivedMsgPtr->sccpSsnConfigisLocal;
         if( deleteSccpSsnStsTable(&sccpSsnStsTableIndices) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_MAJOR, "deleteSccpSsnStsTable FAILED");
         }
      }
      else
      {
         LOG_PRINT(LOG_INFO," SccpSsnConfigTableIndices failed, sending Nack");      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
      DalocOrdBuf(gStoredMsgBufPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO," SccpSsnConfigTableIndices failed, sending Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
   }

} /* end of delSccpSsnConfigTableHandler */

/********************************* Function  Header********************************
   Function Name:       delSccpCSSNConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from SccpCssnConfig table 
Other Note:
 ************************************************************************************/
void delSccpCSSNConfigTableHandler()
{
   SccpCSSNConfigTableIndices* receivedMsgPtr = ( SccpCSSNConfigTableIndices* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   SccpCSSNConfigTableApi* sccpCssnConfigApiPtr = PNULL;
   I_PVoid scmMessagePtr = PNULL;
   I_S32  ret = CLIB_SUCCESS;

   LOG_PRINT(LOG_INFO," In delSccpCSSNConfigTableHandler");

   /* Check if BSS Admin State is LOCK or not */     
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }

   /* Check if entry to be deleted is present in DB or not */
   ret = getSccpCSSNConfigTable(receivedMsgPtr, &sccpCssnConfigApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   else
   {
      gStoredMsgBufPtr= AlocOrdBuf(sizeof(SccpCSSNConfigTableIndices));
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         free(sccpCssnConfigApiPtr);
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy((I_U8 *)gStoredMsgBufPtr, (I_U8*)receivedMsgPtr,sizeof(SccpCSSNConfigTableIndices));

      scmMessagePtr = AlocOrdBuf(sizeof(SccpCSSNConfigTableApi)+sizeof(sCmMsg));
      if(PNULL == scmMessagePtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         DalocOrdBuf(gStoredMsgBufPtr);
         free(sccpCssnConfigApiPtr);
         return;  
      }
      /* Mantis ID 1625 fixed here  */
      memcpy((I_U8*)(scmMessagePtr+sizeof(sCmMsg)),(I_U8*)sccpCssnConfigApiPtr, sizeof(SccpCSSNConfigTableApi));

      cfgSendCmMessage((void * )scmMessagePtr,sizeof(SccpCSSNConfigTableApi)+sizeof(sCmMsg),
            ENT_OAM_OIL, BSC_API_DEL_SCCPCSSNCONFIGTABLE,0);
      DalocOrdBuf(scmMessagePtr);
      free(sccpCssnConfigApiPtr);
      cfgStartTimer();
   }
}

void delSccpCSSNConfigTableHandlerScmAck()
{
   SccpCSSNConfigTableIndices* receivedMsgPtr = ( SccpCSSNConfigTableIndices* )gStoredMsgBufPtr;
   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delete SccpCSSNConfigTableApi failed, as SCM sent  Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
      return ;
   }

   if (receivedMsgPtr != NULL )
   {
      /* Check if entry to be deleted is present in DB or not */
      if (deleteSccpCSSNConfigTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
         cfgSendAckToCm(CM_SUCCESS);
      }
      else
      {
         LOG_PRINT(LOG_INFO," SccpCSSNConfigTableIndices failed, sending Nack");      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
      DalocOrdBuf(gStoredMsgBufPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO," SccpCSSNConfigTableIndices failed, sending Nack");      
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }

} /* end of delSccpCSSNConfigTableHandler */
#endif

/********************************* Function  Header********************************
   Function Name:       delNsvcTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from NSVC table 
Other Note:
 ************************************************************************************/
void delNsvcTableHandler()
{
   NsvcTableApi *receivedMsgPtr = ( NsvcTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   NsvcTableApi *NsvcTableApiPtr =PNULL;
/*Changes PCU R2.5 Aricent -- START*/
   NsvcStatusTableIndices  nsvcStatusTableIndicesBuff;
/*Changes PCU R2.5 Aricent -- END*/
   I_S32 ret = CM_FAILURE;
   NsvcTableIndices NsvcTableIndicesBuff;

   LOG_PRINT(LOG_INFO,"In del NSVC TableHandler");
   LOG_PRINT(LOG_INFO,"nsvcId = %u", receivedMsgPtr->nsvcId);

   NsvcTableIndicesBuff.nsvcId = receivedMsgPtr->nsvcId;

   ret = getNsvcTable(&NsvcTableIndicesBuff, &NsvcTableApiPtr);
   if (CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_MAJOR,"%s:: DB call getNsvcTable failed for NSVC ID[%u] Error Code = %d. Sending Nack",__FUNCTION__,NsvcTableIndicesBuff.nsvcId, ret);
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }

   /* nsvc adminState is checked in nsvcObjectHandler (as delNsvcTableHandler() 
    * is called from nsvcObjectHandler from locked state only 
    * so no need to check adminState here 
    */  

   /* Delete Requested Entry from Table */
   ret = deleteNsvcTable(&NsvcTableIndicesBuff);
   if (CLIB_SUCCESS == ret)
   {
/*Changes PCU R2.5 Aricent -- START*/
      resetNsvcDataStruct(NsvcTableApiPtr->nsvcId);
      /*Delete from NSVCStatus table*/
      nsvcStatusTableIndicesBuff.nsvcId = NsvcTableApiPtr->nsvcId;
      ret = deleteNsvcStatusTable(&nsvcStatusTableIndicesBuff);
      if (CLIB_SUCCESS != ret)
      {
         free(NsvcTableApiPtr);
         LOG_PRINT(LOG_MAJOR, "Requested Entry with NSVC ID [%u] could not be deleted from NSVCStatus Table Error Code = %d. Sanding Nack",
                   nsvcStatusTableIndicesBuff.nsvcId, ret);
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
         return;
      }
      cfgSendAckToCm(); 
/*Changes PCU R2.5 Aricent -- END*/
   }
   else
   {
      free(NsvcTableApiPtr);
      LOG_PRINT(LOG_MAJOR,"DB call deleteNsvcTable returned [%d] :%s line:%d", ret, __FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
      return;
   }
} /* end of delNsvcTableHandler */


/********************************* Function  Header********************************
   Function Name:       delFrLinkTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from FrLink table 
Other Note:
 ************************************************************************************/
void delFrLinkTableHandler()
{
   FrLinkTableApi                *receivedMsgPtr              = ( FrLinkTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   FrLinkTableApi                *frLinkTblApiPtr             = NULL;
   FrLinkTableIndices            apiFrLinkIndex;
/*Changes PCU R2.5 Aricent -- START*/
   FrLinkStatusTableIndices      frLinkStatusTableIndicesBuff;
   NsvcTableApi                  *nsvcTableApiPtr             = NULL;
   I_U32                         outRows = 0;
   I_U16                         outSize = 0;
/*Changes PCU R2.5 Aricent -- END*/
   I_S32                         ret                          = CM_FAILURE;

   LOG_PRINT(LOG_INFO,"In delFrLinkTableHandler");
   LOG_PRINT(LOG_INFO,"frChnId = %u", receivedMsgPtr->frChnId);

   /* Check if entry is present in DB or not */
   apiFrLinkIndex.frChnId = receivedMsgPtr->frChnId;

   ret = getFrLinkTable(&apiFrLinkIndex, &frLinkTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"Requested Entry for FrChnId [%u] is not in present in FrLink Table, sending Nack",
                apiFrLinkIndex.frChnId);   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }

/*Changes R2.5 Aricent -- Start*/
   /*Check if FrChnId has any reference in NsvcTable*/
   ret = getNsvcForFrChannel(receivedMsgPtr->frChnId, &nsvcTableApiPtr,&outRows, &outSize);
   if(CLIB_SUCCESS == ret)
   {
      free(nsvcTableApiPtr);
      free(frLinkTblApiPtr);
      LOG_PRINT(LOG_MAJOR,"Entry corresponding to FrChnId: %u exist in NsvcTable. Sending Nack", receivedMsgPtr->frChnId);
      cfgSendNackToCm(CM_ERR_OBJECT_REFERENCED_BY_OTHER_OBJECT);
      return;
   }
/*Chnages R2.5 Aricent -- End*/

   /* Delete Requested Entry from Table */
   ret = deleteFrLinkTable(&apiFrLinkIndex); 
   if (CLIB_SUCCESS == ret)
   {
/*Changes PCU R2.5 Aricent -- START*/
      /*Delete from Fr Link Status table*/
      frLinkStatusTableIndicesBuff.frChnId = frLinkTblApiPtr->frChnId;
      ret = deleteFrLinkStatusTable(&frLinkStatusTableIndicesBuff);
      if (CLIB_SUCCESS != ret)
      {
         free(frLinkTblApiPtr);
         LOG_PRINT(LOG_MAJOR, "Requested Entry could not be deleted Error Code = [%d], Sanding Nack", ret);
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
         return;
      }
/*Changes PCU R2.5 Aricent -- END*/
      free(frLinkTblApiPtr);
      LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
      cfgSendAckToCm();
   }
   else
   {
      free(frLinkTblApiPtr);
      LOG_PRINT(LOG_MAJOR,"DB call deleteFrLinkTable returned [%u] :%s line:%d", ret, __FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      return;
   }

} /* end of delFrLinkTableHandler */


/********************************* Function  Header********************************
   Function Name:       delLepInfoTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from Lep table 
Other Note:
 ************************************************************************************/
 /*Changes PCU R2.5 Aricent -- START*/
void delLepInfoTableHandler()
{
   LepInfoTableApi* receivedMsgPtr = (LepInfoTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   LepInfoTableApi* lepInfoTblApiPtr = PNULL;
   GbInterfaceTableApi* gbInterfaceTablePtr = PNULL;
   LepInfoTableIndices apiLepInfoIndex;
   I_S32  ret = CM_FAILURE;
   I_U32 outCountGb = 0;
   I_U16 outSizeGb = 0;

   LOG_PRINT(LOG_INFO,"In delLepInfoTableHandler");

   /* Check if entry to be deleted is present in DB or not */   
   /*apiLepInfoIndex.lep = receivedMsgPtr->lep;*/
   strncpy(apiLepInfoIndex.lep, receivedMsgPtr->lep, OAMS_CFG_LEP_LENGTH);
   ret = getLepInfoTable(&apiLepInfoIndex, &lepInfoTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }

   ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outCountGb, &outSizeGb);
   if ( CLIB_SUCCESS == ret)
   {
      if (FR != gbInterfaceTablePtr->transportType)
      {
         /* Check if BSS Admin State is LOCK or not */     
         if(LOCKED != bssLock())
         {
            LOG_PRINT(LOG_MAJOR,"Transport type is IP and BSS is not LOCKED so operation on Lep table not allowed");
            free(gbInterfaceTablePtr);
            free(lepInfoTblApiPtr);
            cfgSendNackToCm(CM_ERR_BSS_UNLOCKED);
            return;
         }
      } 
      free(gbInterfaceTablePtr);
   }
   
   ret = deleteLepInfoTable(&apiLepInfoIndex);
   if (CLIB_SUCCESS == ret)
   {
      free(lepInfoTblApiPtr);
      LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
      cfgSendAckToCm();
   }
   else
   {
      free(lepInfoTblApiPtr);
      LOG_PRINT(LOG_CRITICAL," deleteLepTable failed, sending Nack");   
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }
} /* end of delLepInfoTableHandler */
/*Changes PCU R2.5 Aricent -- END*/

/********************************* Function  Header********************************
   Function Name:       delRepInfoTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from Rep table 
Other Note:
 ************************************************************************************/
/*Changes PCU R2.5 Aricent -- START*/
void delRepInfoTableHandler()
{
   RepInfoTableApi* receivedMsgPtr = (RepInfoTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   RepInfoTableApi* repInfoTblApiPtr = PNULL;
   GbInterfaceTableApi* gbInterfaceTablePtr = PNULL;
   RepInfoTableIndices apiRepInfoIndex;
   I_S32 ret = CM_FAILURE;
   I_U32 outCountGb = 0;
   I_U16 outSizeGb = 0;

   LOG_PRINT(LOG_INFO,"In delRepInfoTableHandler");
   /* Mantis 14769 --Start*/
   LOG_PRINT(LOG_INFO,"repInfoTableIndex = %u", receivedMsgPtr->repInfoTableIndex);
   LOG_PRINT(LOG_INFO,"rep = %s, repPort = %u", receivedMsgPtr->rep, receivedMsgPtr->repPort);
   /* Mantis 14769 --End*/

   /* Check if entry to be deleted is present in DB or not */     
   /*apiRepInfoIndex.rep = receivedMsgPtr->rep;*/
   /* Mantis 14769 --Start*/
   apiRepInfoIndex.repInfoTableIndex = receivedMsgPtr->repInfoTableIndex;
   /*strncpy(apiRepInfoIndex.rep, receivedMsgPtr->rep, OAMS_CFG_REP_LENGTH);*/
   /*apiRepInfoIndex.ipType = receivedMsgPtr->ipType;*/
   /* Mantis 14769 --End*/

   ret = getRepInfoTable(&apiRepInfoIndex, &repInfoTblApiPtr);   
   if (CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_INFO,"Requested Entry is not in RepInfo Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }

   ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outCountGb, &outSizeGb);
   if ( CLIB_SUCCESS == ret)
   {
      if (FR != gbInterfaceTablePtr->transportType)
      {
         /* Check if BSS Admin State is LOCK or not */     
         if(LOCKED != bssLock())
         {
            LOG_PRINT(LOG_MAJOR,"Transport type is IP and BSS is not LOCKED so operation on Lep table not allowed");
            free(gbInterfaceTablePtr);
            free(repInfoTblApiPtr);
            cfgSendNackToCm(CM_ERR_BSS_UNLOCKED);
            return;
         }
      } 
      free(gbInterfaceTablePtr);
   }

   ret = deleteRepInfoTable(&apiRepInfoIndex);
   if (CLIB_SUCCESS == ret)
   {
      free(repInfoTblApiPtr);
      LOG_PRINT(LOG_INFO,"Requested Entry is deleted, sending Ack");   
      cfgSendAckToCm();
      return;
   }
   else
   {
      free(repInfoTblApiPtr);
      LOG_PRINT(LOG_MAJOR,"DB call deleteRepInfoTable returned [%d] :%s line:%d", ret, __FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      return;
   }
} /* end of delRepInfoTableHandler */

/*Changes PCU R2.5 Aricent -- END*/

#if 0 /* CS4.0 HA Stack Chnages */
/********************************* Function  Header********************************
   Function Name:       delSksCommonTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from SksCommon table 
Other Note:
 ************************************************************************************/
void delSksCommonTableHandler()
{
   SksCommonTableIndices* receivedMsgPtr = ( SksCommonTableIndices* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   SksCommonTableApi* sksCommonTblApiPtr = PNULL;
   I_PVoid scmMessagePtr = PNULL;
   I_S32  ret = CLIB_SUCCESS;

   LOG_PRINT(LOG_INFO," In delSksCommonTableHandler");

   /* Check if BSS Admin State is LOCK or not */     
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }

   /* Check if entry to be deleted is present in DB or not */
   ret = getSksCommonTable(receivedMsgPtr, &sksCommonTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   else
   {
      gStoredMsgBufPtr= AlocOrdBuf(sizeof(SksCommonTableIndices));
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         free(sksCommonTblApiPtr);
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy((I_U8 *)gStoredMsgBufPtr, (I_U8*)receivedMsgPtr,sizeof(SksCommonTableIndices));

      scmMessagePtr =  AlocOrdBuf(sizeof(SksCommonTableApi)+sizeof(sCmMsg));
      if(PNULL == scmMessagePtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         DalocOrdBuf(gStoredMsgBufPtr);
         free(sksCommonTblApiPtr);
         return;  
      }
      memcpy((I_U8*)(scmMessagePtr+sizeof(sCmMsg)),(I_U8*)sksCommonTblApiPtr,sizeof(SksCommonTableApi));

      cfgSendCmMessage((void * )scmMessagePtr, sizeof(SksCommonTableApi)+sizeof(sCmMsg),
            ENT_OAM_OIL, BSC_API_DEL_SKSCOMMONTABLE,0);
      DalocOrdBuf(scmMessagePtr);
      free(sksCommonTblApiPtr);
      cfgStartTimer();
   }
}
void delSksCommonTableHandlerScmAck()
{
   SksCommonTableIndices* receivedMsgPtr = ( SksCommonTableIndices* )gStoredMsgBufPtr;
   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delete SksCommonTableApi failed, as SCM sent  Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
      if(gStoredMsgBufPtr != NULL)
         DalocOrdBuf(gStoredMsgBufPtr);
      return ;
   }

   if (receivedMsgPtr != NULL )
   {
      /* Check if entry to be deleted is present in DB or not */
      if (deleteSksCommonTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
         cfgSendAckToCm(CM_SUCCESS);
      }
      else
      {
         LOG_PRINT(LOG_INFO," SksCommonTableIndices failed, sending Nack");      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
      DalocOrdBuf(gStoredMsgBufPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO," SksCommonTableIndices failed, sending Nack");
      cfgSendNackToCm(CM_ERR_UNKNOWN);
   }
} /* end of delSksCommonTableHandler */

/********************************* Function  Header********************************
   Function Name:       delSksLinkstartTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from SksLinkStart table 
Other Note:
 ************************************************************************************/
void delSksLinkstartTableHandler()
{
   SksLinkstartTableIndices* receivedMsgPtr = ( SksLinkstartTableIndices* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   SksLinkstartTableApi* sksLinkstartTblApiPtr = PNULL;
   I_PVoid scmMessagePtr = PNULL;
   I_S32  ret = CLIB_SUCCESS;

   LOG_PRINT(LOG_INFO," In SksLinkstartTableIndices");

   /* Check if BSS Admin State is LOCK or not */     
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   /* Check if entry to be deleted is present in DB or not */
   ret = getSksLinkstartTable(receivedMsgPtr, &sksLinkstartTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   else
   {
      gStoredMsgBufPtr= AlocOrdBuf(sizeof(SksLinkstartTableIndices));
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         free(sksLinkstartTblApiPtr);
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy(((I_U8 *)gStoredMsgBufPtr),(I_U8*)receivedMsgPtr,sizeof(SksLinkstartTableIndices));

      scmMessagePtr = AlocOrdBuf(sizeof(SksLinkstartTableApi)+sizeof(sCmMsg));
      if(PNULL == scmMessagePtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         DalocOrdBuf(gStoredMsgBufPtr);
         free(sksLinkstartTblApiPtr);
         return;  
      }
      memcpy((I_U8*)(scmMessagePtr+sizeof(sCmMsg)),(I_U8*)sksLinkstartTblApiPtr,sizeof(SksLinkstartTableApi));
      cfgSendCmMessage((void * )scmMessagePtr, (sizeof(SksLinkstartTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL, BSC_API_DEL_SKSLINKSTARTTABLE,0);
      free(sksLinkstartTblApiPtr);
      DalocOrdBuf(scmMessagePtr);
      cfgStartTimer();
   }
}

void delSksLinkstartTableHandlerScmAck()
{
   SksLinkstartTableIndices* receivedMsgPtr = ( SksLinkstartTableIndices* )gStoredMsgBufPtr;
   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delete SksLinkstartTableApi failed, as SCM sent  Nack");      
      DalocOrdBuf(gStoredMsgBufPtr);
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
      return ;
   }

   if (receivedMsgPtr != NULL )
   {
      /* Check if entry to be deleted is present in DB or not */
      if (deleteSksLinkstartTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
         cfgSendAckToCm(CM_SUCCESS);
      }
      else
      {
         LOG_PRINT(LOG_INFO," SksLinkstartTableIndices failed, sending Nack");      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
      DalocOrdBuf(gStoredMsgBufPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO," SksLinkstartTableIndices failed, sending Nack");      
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }

} /* end of SksLinkstartTableIndices */
#endif

#if 0 /* CS4.0 HA Stack Changes */
/********************************* Function  Header********************************
   Function Name:       delSksGenCfgTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from SksGenConfig Table
Other Note:
 ************************************************************************************/
void delSksGenCfgTableHandler()
{
   SksGenConfigTableIndices* receivedMsgPtr = ( SksGenConfigTableIndices* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   SksGenConfigTableApi* sksGenCfgTblApiPtr = PNULL;
   I_PVoid scmMessagePtr = PNULL;
   I_S32  ret = CLIB_SUCCESS;

   LOG_PRINT(LOG_INFO," In SksGenConfigTableIndices");

   /* Check if BSS Admin State is LOCK or not */     
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }
   /* Check if entry to be deleted is present in DB or not */
   ret = getSksGenConfigTable(receivedMsgPtr, &sksGenCfgTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   else
   {
      gStoredMsgBufPtr= AlocOrdBuf(sizeof(SksGenConfigTableIndices));
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         free(sksGenCfgTblApiPtr);
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy((I_U8 *)gStoredMsgBufPtr,(I_U8*)receivedMsgPtr,sizeof(SksGenConfigTableIndices));

      scmMessagePtr = AlocOrdBuf(sizeof(SksGenConfigTableApi)+sizeof(sCmMsg));
      if(PNULL == scmMessagePtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         DalocOrdBuf(gStoredMsgBufPtr);
         free(sksGenCfgTblApiPtr);
         return;  
      }
      memcpy((I_U8*)(scmMessagePtr+sizeof(sCmMsg)),(I_U8*)sksGenCfgTblApiPtr,sizeof(SksGenConfigTableApi));

      cfgSendCmMessage((void * )scmMessagePtr,(sizeof(SksGenConfigTableApi)+sizeof(sCmMsg)),
            ENT_OAM_OIL, BSC_API_DEL_SKSGENCONFIGTABLE,0);
      free(sksGenCfgTblApiPtr);
      DalocOrdBuf(scmMessagePtr);
      cfgStartTimer();
   }
}

void delSksGenCfgTableHandlerScmAck()
{
   SksGenConfigTableIndices* receivedMsgPtr = ( SksGenConfigTableIndices* )gStoredMsgBufPtr;
   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," delete SksGenConfigTableApi failed, as SCM sent  Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
      DalocOrdBuf(gStoredMsgBufPtr);
      return ;
   }

   if (receivedMsgPtr != NULL )
   {
      /* Check if entry to be deleted is present in DB or not */
      if (deleteSksGenConfigTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
         cfgSendAckToCm(CM_SUCCESS);
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," SksGenConfigTableApi failed, sending Nack");      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
      DalocOrdBuf(gStoredMsgBufPtr);
   }
   else
   {
      LOG_PRINT(LOG_CRITICAL," SksGenConfigTableApi failed, sending Nack");      
      cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }

} /* end of SksGenConfigTableIndices */

/******************   Change History ********************************************
   Release         Patch           Author                  Description
   1.0                                 Pooja Mittal         DB Del Methods for Tables

 *****************************************************************************/
void delBssapPcSsnConfigTableHandler()
{
   BssapPcSsnConfigTableIndices* receivedMsgPtr =
      ( BssapPcSsnConfigTableIndices* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   BssapPcSsnConfigTableApi* bssapPcSsnCfgTblApiPtr = PNULL;
   I_PVoid scmMessagePtr = PNULL; 
   I_S32 ret = CLIB_SUCCESS;

   LOG_PRINT(LOG_INFO," In delBssapPcSsnConfigTableHandler");

   /* Check if BSS Admin State is LOCK or not */     
   if (UNLOCK == bssLock())
   {
      LOG_PRINT(LOG_INFO," BSS is unlocked: Precondition Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARENT_OBJ_NOT_LOCKED);
      return;    
   }

   /* Check if entry to be deleted is present in DB or not */
   ret = getBssapPcSsnConfigTable(receivedMsgPtr, &bssapPcSsnCfgTblApiPtr);   
   if (ret != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," Requested Entry is not in Table, sending Nack");   
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;   
   }
   else
   {
      gStoredMsgBufPtr = AlocOrdBuf( sizeof(BssapPcSsnConfigTableIndices));
      if(PNULL == gStoredMsgBufPtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         free(bssapPcSsnCfgTblApiPtr);
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         return;  
      }
      memcpy(((I_U8 *)gStoredMsgBufPtr),
            (I_U8*)receivedMsgPtr, sizeof(BssapPcSsnConfigTableIndices));

      scmMessagePtr = AlocOrdBuf(sizeof(BssapPcSsnConfigTableApi)+sizeof(sCmMsg));
      if(PNULL == scmMessagePtr) /* NULL check added during fix of Mantis 2284*/
      {
         LOG_PRINT(LOG_CRITICAL," Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
         cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
         DalocOrdBuf(gStoredMsgBufPtr);
         free(bssapPcSsnCfgTblApiPtr);
         return;  
      }
      memcpy((I_U8*)(scmMessagePtr+sizeof(sCmMsg)),(I_U8*)bssapPcSsnCfgTblApiPtr,sizeof(BssapPcSsnConfigTableApi));
      cfgSendCmMessage((void * )scmMessagePtr,
            (sizeof(BssapPcSsnConfigTableApi) + sizeof(sCmMsg)),
            ENT_OAM_OIL, BSC_API_DEL_BSSAPPCSSNCONFIGTABLE,0);
      DalocOrdBuf(scmMessagePtr);
      free(bssapPcSsnCfgTblApiPtr);
      cfgStartTimer();
   }
} /* end of delBssapPcSsnConfigTableHandler */

void delBssapPcSsnConfigTableHandlerScmAck()
{
   BssapPcSsnConfigTableIndices* receivedMsgPtr =
      ( BssapPcSsnConfigTableIndices* )gStoredMsgBufPtr;
   cfgStopTimer();

   if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
   {
      LOG_PRINT(LOG_INFO," deleteBssapPcSsnConfigTable failed, as SCM sent  Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
      DalocOrdBuf(gStoredMsgBufPtr);
      return ;
   }

   if (receivedMsgPtr != NULL )
   {
      if (deleteBssapPcSsnConfigTable(receivedMsgPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," Requested Entry is deleted, sending Ack");   
         cfgSendAckToCm(CM_SUCCESS);
      }
      else
      {
         LOG_PRINT(LOG_INFO," deleteBssapPcSsnConfigTable failed, sending Nack");      
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
      DalocOrdBuf(gStoredMsgBufPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO," deleteBssapPcSsnConfigTable failed, sending Nack");      
      cfgSendNackToCm(CM_ERR_UNKNOWN);  
   }

} /* end of delBssapPcSsnConfigTableHandlerScmAck */
#endif

/********************************* Function  Header*****************************
   Function Name   : delBicTableHandler()
Parameters   : None
Return type   : I_Void
Purpose      : Handler delete BIC request from OMC/CLI
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void delBicTableHandler()
{
   I_S32 dbStatus = -1;
   I_Bool isTrxsAssociatedWithBic = TRUE;
   BicTableApi* receivedMsgPtr = ( BicTableApi* )(((I_U8 *)gCfgMsgBuf ) + 
         sizeof(sCmMsg));
   BicTableApi* bicTableApiPtr = PNULL;
   BicTableIndices bicTableIndices;
   OamsCfgBichDelBicReq oamsCfgBichDelBicReq;
   I_U32 i;
   /*Changes For R2.2 :Start */

   LOG_PRINT(LOG_INFO,"Entering Function : delBicTableHandler");
   LOG_PRINT(LOG_DEBUG,"delBicTableHandler : Delete BIC Request is received \
         for bicId = %d",receivedMsgPtr->bicId); 

      /* Check bicId received in DEL request is Configured or Not */
      bicTableIndices.bicId = receivedMsgPtr->bicId;
   dbStatus = getBicTable(&bicTableIndices, &bicTableApiPtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
      /* BIC is not Configured at BSC. Sending NACK to OMC/CLI */
      LOG_PRINT(LOG_MAJOR,"delBicTableHandler : bicId = %d is not Configured \
            at BSC",receivedMsgPtr->bicId);
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
   }
   else
   {
      /* CS4.0 E1 UsageType Changes : Start*/
      if (bicTableApiPtr->adminState != LOCKED)
      {
         LOG_PRINT(LOG_DEBUG,"delBicTableHandler : Bic deletion allowed in Locked State only");
         cfgSendNackToCm(CM_ERR_BTS_NOT_LOCKED_IN_DB);
         free(bicTableApiPtr);
         return;
      }
      free(bicTableApiPtr);
      if(getIndex(receivedMsgPtr->bicId,&i) == CFG_FAILURE)
      {
          LOG_PRINT(LOG_DEBUG,"delBicTableHandler : getIndex failed");
          cfgSendNackToCm(CM_ERR_BTS_NOT_FOUND);
          return;
      }
      if( gBtsData[i].btsState == unlockInProgress)
      {
        LOG_PRINT(LOG_DEBUG,"delBicTableHandler : DELETE Only Allowed in LOCKED State");
        cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
        return;
      }
      if( gBtsData[i].btsState == lockInProgress)
      {
         LOG_PRINT(LOG_DEBUG,"delBicTableHandler : DELETE Only Allowed in LOCKED State");
         cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
         return;
      }
      if( gBtsData[i].btsState == unlocked)
      {
        LOG_PRINT(LOG_DEBUG,"delBicTableHandler : DELETE Only Allowed in LOCKED State");
        cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);
        return;
      }

    //if( (gBtsData[i].btsType!=R3_BTS)&& (gBtsData[i].btsType!=R2_BTS_IP) )
    //{/*Changes for R2.8 starts*/
      /* CS4.0 E1 UsageType Changes : End*/
      /* BIC is configured at BSC.
       * Check Is there any TRX associated with BIC. */
      /*CS3.0 Changes: Start */
      SwMNodeTableIndices swMNodeTableIndex;
      I_U8 slotId;
      I_U8 chasisFrameId;
      I_U32 swStatus;
      /*Retrieve swStatus from SwMNode Table */
      if ( ( dbStatus = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
      {
         LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",dbStatus);
         return;
      }
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

      if (gBtsData[i].btsType == BIC)
          swMNodeTableIndex.nodeType = SYS_NODE_TYPE_BIC;
      else if (gBtsData[i].btsType == R2_BTS)
          swMNodeTableIndex.nodeType = SYS_NODE_TYPE_R2_BTS;
      else if (gBtsData[i].btsType == R2_BTS_IP)
          swMNodeTableIndex.nodeType = SYS_NODE_TYPE_R2_BTS_IP;
      else if (gBtsData[i].btsType == R3_BTS)
          swMNodeTableIndex.nodeType = SYS_NODE_TYPE_R3_BTS;
      swMNodeTableIndex.nodeIdentity = receivedMsgPtr->bicId;
      swMNodeTableIndex.chasisFrameId = chasisFrameId;
      swMNodeTableIndex.slotId = slotId;
      if(getSwStatusFromSwMNodeTable(swMNodeTableIndex,&swStatus) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"getSwStatusFromSwMNodeTable DB call is getting failed..");
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         return;
      }
      if(swStatus == SW_ACTIVATION_IN_PROGRESS || swStatus == SW_DOWNLOAD_IN_PROGRESS)
      {
         LOG_PRINT(LOG_DEBUG,"Software activation/download is in progress for the BIC");
         cfgSendNackToCm(CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS);
         return;
      }
      /*CS3.0 Changes: End */
    //}/*Changes for R2.8 starts*/
      isTrxsAssociatedWithBic = isTrxAssociatedWithBic(receivedMsgPtr->bicId);
      if(FALSE == isTrxsAssociatedWithBic)
      {
         /* There is no TRX associated with BIC.So BIC can be deleted */
         LOG_PRINT(LOG_INFO,"delBicTableHandler : No TRX is currently \
               associated with BIC");
         oamsCfgBichDelBicReq.bicId = receivedMsgPtr->bicId;
         cfgSendMessage(&oamsCfgBichDelBicReq, sizeof(OamsCfgBichDelBicReq), 
               ENT_OAMS_BICH, OAMS_CFG_BICH_DEL_BIC_REQ , 0);
      }
      else
      {
         /* There are some TRXs associated with BIC. So BIC can't be deleted.
          * Sending NACK to OMC/CLI  */
         LOG_PRINT(LOG_DEBUG,"delBicTableHandler : Some TRXs are associated \
               with bicId = %d.Rejecting Delete BIC request",\
               receivedMsgPtr->bicId);
         cfgSendNackToCm(CM_ERR_TRX_ASSOCIATED_WITH_BTS);
      }
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : delBicTableHandler");
}
/*Changes For R2.2 :End */


/********************************* Function  Header*****************************
   Function Name   : delTrxTableHandler()
Parameters   : None
Return type   : I_Void
Purpose      : It handle delete TrxTable request received from OMC/CLI
Other Note   : Added For BSC CS2.2
 *******************************************************************************/
I_Void delTrxTableHandler()
{
   I_S32 dbStatus = -1;
   TrxTableApi* receivedMsgPtr = ( TrxTableApi* )(((I_U8 *)gCfgMsgBuf ) + 
         sizeof(sCmMsg));
   TrxTableApi* trxTableApiPtr = NULL;
   TrxTableIndices trxTableIndices;
   BicTableIndices bicTableIndexPtr;
   BicTableApi* bicTableApiPtr = PNULL;
   objectState state;

   LOG_PRINT(LOG_INFO,"Entering Function : delTrxTableHandler");

   /* Check TRX is configured at BSC or not */
   trxTableIndices.ptrxId = receivedMsgPtr->ptrxId;
   dbStatus = getTrxTable(&trxTableIndices, &trxTableApiPtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
      /* TRX is not configured at BSC. Sending NACK to OMC/CLI */
      LOG_PRINT(LOG_DEBUG,"delTrxTableHandler : ptrxId : %d is Not Configured \
            at BSC",receivedMsgPtr->ptrxId);
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
   }
   else
   {
      /* Mantis Fix : 8983 Start */
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
      /* Mantis Fix : 8983 End */

    if( (trxTableApiPtr->trxLocation!=TRX_LOCATION_R2_BTS_IP)&& 
        (trxTableApiPtr->trxLocation!=TRX_LOCATION_R3_BTS) )
    {/*Changes done for R2.8 */ 
      /*CS3.0 Changes: Start */
      SwMNodeTableIndices swMNodeTableIndex;
      I_U32 swStatus;
      I_U8 slotId;
      I_U8 chasisFrameId;
      /*Retrieve swStatus from SwMNode Table */
      if ( ( dbStatus = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
      {
         LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",dbStatus);
         return;
      }
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

      if (trxTableApiPtr->trxLocation == TRX_LOCATION_R2_BTS )
      {
 	       swMNodeTableIndex.nodeType = SYS_NODE_TYPE_R2_BTS;
      	 swMNodeTableIndex.nodeIdentity = trxTableApiPtr->bicId;
      }
      else 
      {
	       swMNodeTableIndex.nodeType = SYS_NODE_TYPE_TRX;
         swMNodeTableIndex.nodeIdentity = receivedMsgPtr->ptrxId;
      }
      swMNodeTableIndex.chasisFrameId = chasisFrameId;
      swMNodeTableIndex.slotId = slotId;

      if(getSwStatusFromSwMNodeTable(swMNodeTableIndex,&swStatus) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"getSwStatusFromSwMNodeTable DB call is getting failed..");
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         free(trxTableApiPtr);
         return;
      }
      if(swStatus == SW_ACTIVATION_IN_PROGRESS || swStatus == SW_DOWNLOAD_IN_PROGRESS)
      {
         LOG_PRINT(LOG_DEBUG,"Software activation/download is in progress for the TRX");
         cfgSendNackToCm(CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS);
         free(trxTableApiPtr);
         return;
      }
      /*CS3.0 Changes: End */
    }
      /* Check TRX must be Locked at BSC */
      if(LOCKED != trxTableApiPtr->adminState)
      {
         /* TRX is Not Locked at BSC. Rejecting Request.
          * Sending NACK to OMC/CLI */
         LOG_PRINT(LOG_DEBUG,"delTrxTableHandler : ptrxId : %d is Not Locked \
               at BSC",receivedMsgPtr->ptrxId);
         cfgSendNackToCm(CM_ERR_OBJECT_NOT_LOCKED);
         free(trxTableApiPtr);
         return;
      }
      else if(TRX_LOCATION_BIC == trxTableApiPtr->trxLocation || TRX_LOCATION_R2_BTS == trxTableApiPtr->trxLocation ||TRX_LOCATION_R3_BTS == trxTableApiPtr->trxLocation ||TRX_LOCATION_R2_BTS_IP == trxTableApiPtr->trxLocation)/*Changes for R2.8*/
      {
         /* Check BIC is not connected */
	       bicTableIndexPtr.bicId=trxTableApiPtr->bicId;
        dbStatus = getBicTable(&bicTableIndexPtr, &bicTableApiPtr);
        if(DBLIB_SUCCESS != dbStatus)
        {
           /* bicId received in Add TrxTable Request is not Added at BSC.
           * Sending NACK to OMC/CLI  */
           LOG_PRINT(LOG_MAJOR,"delTrxTableHandler: bicId : %d Received in Add \
              Trx Request is not Added at BSC",receivedMsgPtr->bicId);
           cfgSendNackToCm(CM_ERR_REFERENCED_OBJECT_NOT_FOUND);
           free(trxTableApiPtr);
           return;
        }
	      if (bicTableApiPtr->adminState != LOCKED)
        {
            LOG_PRINT(LOG_DEBUG,"delTrxTableHandler:Trx Deletion is not allowed while parent Bts is in Unlock State");
            cfgSendNackToCm(CM_ERR_BTS_NOT_LOCKED_IN_DB);
            free(bicTableApiPtr);
            free(trxTableApiPtr);
           return;
        }
      	free(bicTableApiPtr);
      }
      if(TRX_LOCATION_BIC == trxTableApiPtr->trxLocation || TRX_LOCATION_IN_FRAME == trxTableApiPtr->trxLocation )
      {
         /* Send Switch Disconnect to GRHM */
	       prepAndSndSwitchDisConForTrx(trxTableApiPtr->ptrxId); 
         /* Req is received for In-Frame Trx */
      }
      /* Send del trx req to TRXH */
      sendDelTrxReq(trxTableApiPtr->ptrxId);
      free(trxTableApiPtr);
   } 
}

/*CS3.0 Changes : Start */
/********************************* Function  Header********************************
   Function Name:       delHoCtrlTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from HoCtrl table 
Other Note:          Added for CS3.0
 ************************************************************************************/
void delHoCtrlTableHandler()
{
   HoCtrlTableApi* receivedMsgPtr = NULL;
   receivedMsgPtr = ( HoCtrlTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   HoCtrlTableIndices hoCtrlTableIndex;
   hoCtrlTableIndex.cellId = receivedMsgPtr->cellId;
   hoCtrlTableIndex.lac = receivedMsgPtr->lac;
   I_U32 cellAdminState,bssAdminState,cellOprState;
   LOG_PRINT(LOG_INFO," In delHoCtrlTableHandler");

   /*Retrieve adminState and OprState from CellTable */
   if(getCellAdminStateAndOprState(receivedMsgPtr->lac,receivedMsgPtr->cellId,
            &cellAdminState,&cellOprState) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getCellAdminStateAndOprState Failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;     
   }
   /*Retrieve adminState of BSS*/
   if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getBssAdminState DB call is geting failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;     
   }

   if ((cellAdminState == LOCKED) || 
         ((cellOprState == DISABLED) && 
          (bssAdminState == LOCKED)))   
   {
      if (deleteHoCtrlTable(&hoCtrlTableIndex) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO," In delHoCtrlTableHandler: Row is successfully deleted, sending Ack");
         cfgSendAckToCm();
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL," In delHoCtrlTableHandler: DB del operation Failed, sending Nack");
         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"In delHoCtrlTableHandler: Either Cell is Unlocked/Disabled or Bss is Unlocked, sending Nack");    
      LOG_PRINT(LOG_INFO,"Deletion not allowed for cellId: %d and lac : %d",receivedMsgPtr->cellId,receivedMsgPtr->lac);
      cfgSendNackToCm(CM_ERR_DEL_OBJ_NOT_ALLOWED);
   }        
}/* end of delHoCtrlTableHandler */
/*CS3.0 Changes : End */

/*Changes for TsGroup Start */
/********************************* Function  Header********************************
   Function Name:       delTsGroupConfigTableHandler()
Parameters:          void
Return type:         void
Purpose:             To delete a particular row from TsGroupConfig table 
Other Note:          Added for TsGroup 
 ************************************************************************************/
void delTsGroupConfigTableHandler()
{
   TsGroupConfigTableApi* receivedMsgPtr = NULL;
   receivedMsgPtr = ( TsGroupConfigTableApi* )(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   TsGroupConfigTableIndices tsGroupConfigTableIndex;
   TsGroupConfigTableApi *tsGroupConfigTablePtr;
   TsGroupMapTableIndices tsGroupMapTableIndex;
   TsGroupMapTableApi *tsGroupMapTableApiPtr;
   I_S32 retStatus,dbStatus;
   I_U32 trunkUsageType1,trunkUsageType2;
   I_U32 trunkType1,trunkType2;
   I_U32 tsMap1,tsMap2;
   I_U32 numTs;
   I_U16 trunkPortId1,trunkPortId2;
   I_U8 tsArray1[MAX_E1_TS],tsArray2[MAX_E1_TS];

   LOG_PRINT(LOG_INFO," Entering function %s with tsGroupId(%d)",__FUNCTION__,receivedMsgPtr->tsGroupId);

   tsGroupConfigTableIndex.tsGroupId=receivedMsgPtr->tsGroupId;
   dbStatus=getTsGroupConfigTable(&tsGroupConfigTableIndex,&tsGroupConfigTablePtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
     LOG_PRINT(DEBUG,"Get on TsGroupConfig Failed for tsGroupId(%d)",receivedMsgPtr->tsGroupId); 
     cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
     return;
   }
   trunkPortId1=tsGroupConfigTablePtr->trunkPortId1;
   trunkPortId2=tsGroupConfigTablePtr->trunkPortId2;
   numTs=tsGroupConfigTablePtr->numTS;
   free(tsGroupConfigTablePtr);

   retStatus=getTrunkUsageType(trunkPortId1,&trunkUsageType1);
   if(retStatus!=CM_SUCCESS)
   {
     cfgSendNackToCm(retStatus);
     return;
   }

   retStatus=getTrunkUsageType(trunkPortId2,&trunkUsageType2);
   if(retStatus!=CM_SUCCESS)
   {
     cfgSendNackToCm(retStatus);
     return;
   }
   LOG_PRINT(LOG_INFO,"Sending Switch Disconnect for TsGroup Map");
   tsGroupMapTableIndex.tsGroupId=receivedMsgPtr->tsGroupId;
   dbStatus=getTsGroupMapTable(&tsGroupMapTableIndex,&tsGroupMapTableApiPtr);
   if(dbStatus !=DBLIB_SUCCESS)
   {
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         return;
   }

   tsMap1=tsGroupMapTableApiPtr->timeSlotMap1;
   tsMap2=tsGroupMapTableApiPtr->timeSlotMap2;
   free(tsGroupMapTableApiPtr);
   memset(tsArray1,0,MAX_E1_TS);
   memset(tsArray2,0,MAX_E1_TS);

  convertTsBitMapToArray(numTs,tsMap1,tsArray1);
  convertTsBitMapToArray(numTs,tsMap2,tsArray2);

   retStatus=prepAndSndSwitchDisconnForTsGroup(trunkPortId1,tsArray1,trunkPortId2,tsArray2,numTs);

     if(trunkUsageType1 == SYS_E1_USAGE_ABISIF)
     {
       retStatus=updateAbisTimeSlotforTsGroup(trunkPortId1,numTs,tsArray1,SYS_TS_USAGE_ABIS_FREE);
       if(retStatus!=CM_SUCCESS)
       {
         cfgSendNackToCm(retStatus);
         return;
       }
     } 

     if(trunkUsageType2 == SYS_E1_USAGE_ABISIF)
     {
       retStatus=updateAbisTimeSlotforTsGroup(trunkPortId2,numTs,tsArray2,SYS_TS_USAGE_ABIS_FREE);
       if(retStatus!=CM_SUCCESS)
       {
         cfgSendNackToCm(retStatus);
         return;
       }
     }

   dbStatus=deleteTsGroupMapTable(&tsGroupMapTableIndex);
   if(CLIB_SUCCESS == dbStatus)
   {
     LOG_PRINT(LOG_INFO," TsGroupMap Row is successfully deleted");
   }
   else
   {
     LOG_PRINT(LOG_CRITICAL," DB del operation Failed on TsGroupMapTable, sending Nack");
     cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
     return;
   }

   tsGroupConfigTableIndex.tsGroupId=receivedMsgPtr->tsGroupId;
   dbStatus=deleteTsGroupConfigTable(&tsGroupConfigTableIndex);
   if(CLIB_SUCCESS == dbStatus)
   {
     LOG_PRINT(LOG_INFO," Row is successfully deleted, sending Ack");
     cfgSendAckToCm();
   }
   else
   {
     LOG_PRINT(LOG_CRITICAL," DB del operation Failed on TsGroupConfigTable, sending Nack");
     cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);  
   }
   LOG_PRINT(LOG_INFO," Exiting function %s",__FUNCTION__);

   return;
}/* end of delTsGroupConfigTableHandler */
/*Changes for TsGroup End */

/********************************* Change History ***************************
   Release   Patch   Author      Description
   BSC CS2.2         Kapil Tyagi    Added function delBicTableHandler &
   delTrxTableHandler.   
   BSC R2.5.5         Gaurav Jain   Added function delTsGroupConfigTableHandler

************************************** End *********************************/
