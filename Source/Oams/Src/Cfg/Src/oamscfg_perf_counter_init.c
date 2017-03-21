/***********************************File Header ***************************
File Name        : oamscfg_perf_counter_init.c
Purpose          : This file contains implementation for 
                   initialization/cleanup of Peformance Counter tables 
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent
CSCI ID          :
Version          :
************************************** End ********************************/
#include <oamscfg_includes.h>


/********************************* Function  Header********************************
Function Name:       psPerformanceCounterTableIntialization()
Parameters:          
Return type:         void
Purpose:             To initialize Ps Performance Counter Tables.
Other Note:
 ************************************************************************************/
I_Void psPerformanceCounterTableIntialization()
{
   initializePsappCellAndGbBssGpStackCellTable();
   initializePsPerformanceCounterTablesForBss();
   initializePsPerfCounterTableForTrx();
}

/********************************* Function  Header********************************
Function Name:       insertRowInPsPerformanceCounterTablesForCell()
Parameters:          I_U16 cellId: Cell Idetifier
                     I_U16 lac: Location Area Code
Return type:         void
Purpose:             To insert a row in  PsAppCellPmTable and GbBssGpStackCellPmTable
                     for  given cellId and lac
Other Note:
 ************************************************************************************/
void insertRowInPsPerformanceCounterTablesForCell(I_U16 cellId, I_U16 lac)
{
    PsAppCellPmTableApi psAppCellPmTableApiBuff;
    GbBssGpStackCellPmTableApi gbBssGpStackCellPmTableApiBuff;
    I_S32 dbStatus = DBLIB_SUCCESS;
    
    memset(&psAppCellPmTableApiBuff, 0, sizeof(PsAppCellPmTableApi));
    memset(&gbBssGpStackCellPmTableApiBuff, 0, sizeof(GbBssGpStackCellPmTableApi));
    psAppCellPmTableApiBuff.cellId = cellId;
    psAppCellPmTableApiBuff.lac = lac;

    dbStatus = insertPsAppCellPmTable(&psAppCellPmTableApiBuff);
    if (DBLIB_SUCCESS != dbStatus)
    {
       LOG_PRINT(LOG_MAJOR,"Db call insertPsAppCellPmTable failed, Error Code = [%d]", dbStatus);
    }

    gbBssGpStackCellPmTableApiBuff.cellId = cellId;
    gbBssGpStackCellPmTableApiBuff.lac = lac;

    dbStatus = insertGbBssGpStackCellPmTable(&gbBssGpStackCellPmTableApiBuff);

    if (DBLIB_SUCCESS != dbStatus)
    {
       LOG_PRINT(LOG_MAJOR,"Db call insertPsAppCellPmTable failed, Error Code = [%d]", dbStatus);
    }

} /* end of insertRowInPsPerformanceCounterTablesForCell*/

/********************************* Function  Header********************************
Function Name:       deleteRowFromPsPerformanceCounterTablesForCell()
Parameters:          I_U16 cellId: Cell Idetifier
                     I_U16 lac: Location Area Code
Return type:         void
Purpose:             To delete a row from PsAppCellPmTable and GbBssGpStackCellPmTable
                     for  given cellId and lac
Other Note:
 ************************************************************************************/
void deleteRowFromPsPerformanceCounterTablesForCell(I_U16 cellId, I_U16 lac)
{
    PsAppCellPmTableIndices psAppCellPmTableIndicesBuff;
    GbBssGpStackCellPmTableIndices gbBssGpStackCellPmTableIndicesBuff;
    I_S32 dbStatus = DBLIB_SUCCESS;
 
    psAppCellPmTableIndicesBuff.cellId = cellId;
    psAppCellPmTableIndicesBuff.lac = lac;

    dbStatus = deletePsAppCellPmTable(&psAppCellPmTableIndicesBuff);
    if (DBLIB_SUCCESS != dbStatus)
    {
       LOG_PRINT(LOG_MAJOR,"Db call deleteRowFromPsPerformanceCounterTablesForCell failed, Error Code = [%d]", dbStatus);
    }

    gbBssGpStackCellPmTableIndicesBuff.cellId = cellId;
    gbBssGpStackCellPmTableIndicesBuff.lac = lac;

    dbStatus = deleteGbBssGpStackCellPmTable(&gbBssGpStackCellPmTableIndicesBuff);

    if (DBLIB_SUCCESS != dbStatus)
    {
       LOG_PRINT(LOG_MAJOR,"Db call deleteRowFromPsPerformanceCounterTablesForCell failed, Error Code = [%d]", dbStatus);
    }

} /* end of deleteRowFromPsPerformanceCounterTablesForCell*/

/********************************* Function  Header********************************
Function Name:       insertRowInPsPerfCounterTablesForTrx()
Parameters:          I_U32 ptrxId: Ptrx Idetifier
Return type:         void
Purpose:             To insert a row in RlcMacStackPmTable
                     for  given ptrxId
Other Note:
 ************************************************************************************/
void insertRowInPsPerfCounterTableForTrx(I_U32 ptrxId)
{
    RlcMacStackPmTableApi rlcMacStackPmTableApiBuff;
    I_S32 dbStatus = DBLIB_SUCCESS;

    memset(&rlcMacStackPmTableApiBuff, 0, sizeof(RlcMacStackPmTableApi));
    rlcMacStackPmTableApiBuff.ptrxId = ptrxId;

    dbStatus = insertRlcMacStackPmTable(&rlcMacStackPmTableApiBuff);
    if (DBLIB_SUCCESS != dbStatus)
    {
       LOG_PRINT(LOG_MAJOR,"Db call insertRlcMacConfigTable failed, Error Code = [%d]", dbStatus);
    }

} /* end of insertRowInPsPerfCounterTableForTrx*/

/********************************* Function  Header********************************
Function Name:       deleteRowFromPsPerfCounterTableForTrx()
Parameters:          I_U32 ptrxId: Ptrx Idetifier
Return type:         void
Purpose:             To delete a row from RlcMacStackPmTable
                     for  given ptrxId
Other Note:
 ************************************************************************************/
void deleteRowFromPsPerfCounterTableForTrx(I_U32 ptrxId)
{
    RlcMacStackPmTableIndices rlcMacStackPmTableIndicesBuff;
    I_S32 dbStatus = DBLIB_SUCCESS;

    rlcMacStackPmTableIndicesBuff.ptrxId = ptrxId;

    dbStatus = deleteRlcMacStackPmTable(&rlcMacStackPmTableIndicesBuff);
    if (DBLIB_SUCCESS != dbStatus)
    {
       LOG_PRINT(LOG_MAJOR,"Db call deleteRowFromPsPerformanceCounterTableForTrx failed, Error Code = [%d]", dbStatus);
    }
} /* end of deleteRowFromPsPerfCounterTableForTrx*/

/********************************* Function  Header********************************
Function Name:       initializePsappCellAndGbBssGpStackCellTable()
Parameters:          void
Return type:         void
Purpose:             To populate PsAppCellPmTable and GbBssGpStackCellPmTable 
Other Note:
 ************************************************************************************/
void initializePsappCellAndGbBssGpStackCellTable()
{
   I_U32 outRows =0;
   I_U16 outSize = 0;
   I_S32 dbStatus = DBLIB_SUCCESS;
   I_U32 i = 0;

   CellPerTableApi *cellPerTableApiAllPtr = NULL;
   CellPerTableApi *cellPerTableApiPtr = NULL;

   LOG_PRINT(LOG_INFO,"initializePsappCellAndGbBssGpStackCellTable: Entering function");

   dbStatus = getallCellPerTable(&cellPerTableApiAllPtr, &outRows, &outSize);

   if(DBLIB_SUCCESS == dbStatus)
   {
      LOG_PRINT(LOG_INFO,"GetAll from CellPerTable successfull");
      
      for (i = 0; i < outRows; i++)
      {
         cellPerTableApiPtr = (CellPerTableApi *) (((I_U8 *)cellPerTableApiAllPtr) + (outSize * i));
         if (ALLOWED == cellPerTableApiPtr->psAllowed)
         { 
            insertRowInPsPerformanceCounterTablesForCell(cellPerTableApiPtr->cellId, cellPerTableApiPtr->lac);
         }
      }
      free(cellPerTableApiAllPtr);	
   }
} /* end of initializePsappCellAndGbBssGpStackCellTable*/


/********************************* Function  Header********************************
Function Name:       initializePsPerfCounterTableForTrx()
Parameters:          void
Return type:         void
Purpose:             To populate RlcMacStackPmTable 
Other Note:
 ************************************************************************************/
void initializePsPerfCounterTableForTrx()
{
   I_U32 outRows =0;
   I_U16 outSize = 0;
   I_S32 dbStatus = DBLIB_SUCCESS;
   I_U32 i = 0;

   PtrxTableApi  *ptrxTableApiAllPtr = NULL;
   PtrxTableApi  *ptrxTableApiPtr = NULL;

   LOG_PRINT(LOG_INFO,"initializePsPerfCounterTableForTrx: Entering function");

   dbStatus = getallPtrxTable(&ptrxTableApiAllPtr, &outRows, &outSize);

   if(DBLIB_SUCCESS == dbStatus)
   {
      LOG_PRINT(LOG_INFO,"GetAll from PtrxTable successfull");
      
      for (i = 0; i < outRows; i++)
      {
         ptrxTableApiPtr = (PtrxTableApi *) (((I_U8 *)ptrxTableApiAllPtr) + (outSize * i));
         if (1 == ptrxTableApiPtr->gprsCapability)
         { 
            insertRowInPsPerfCounterTableForTrx(ptrxTableApiPtr->ptrxId);
         }
      }
      free(ptrxTableApiAllPtr);	
   }
} /* end of initializePsPerfCounterTableForTrx*/

/********************************* Function  Header********************************
Function Name:       initializePsPerformanceCounterTablesForBss()
Parameters:          void
Return type:         void
Purpose:             To insert a row in PS Performance Table for BSS
Other Note:
 ************************************************************************************/
void initializePsPerformanceCounterTablesForBss()
{
   I_U32 outRows =0;
   I_U16 outSize = 0;
   I_S32 dbStatus = DBLIB_SUCCESS;

   BssPsPreConfigTableApi *bssPsPreConfigTableApiPtr = NULL;

   LOG_PRINT(LOG_INFO,"initializePsPerformanceCounterTablesForBss: Entering function");

   dbStatus = getallBssPsPreConfigTable(&bssPsPreConfigTableApiPtr,&outRows,&outSize);

   if(dbStatus == DBLIB_SUCCESS)
   {
        LOG_PRINT(LOG_INFO,"GetAll from BssPsPreConfigTable successfull");
        insertRowInPsPerformanceCounterTablesForBss();
        free(bssPsPreConfigTableApiPtr);
   }
   else
   {
        LOG_PRINT(LOG_MAJOR, "Get All from BssPsPreConfigTable Unsuccessfull. DB Status =%x", dbStatus);
   }

}

/********************************* Function  Header********************************
Function Name:       insertRowInPsPerformanceCounterTablesForBss()
Parameters:          void
Return type:         void
Purpose:             To insert a row in GbNsStackPm and GbBssGpStackPm Table
Other Note:
 ************************************************************************************/
void insertRowInPsPerformanceCounterTablesForBss()
{
   I_S32 dbStatus = DBLIB_SUCCESS;

   GbNsStackPmTableApi gbNsStackPmTableApiBuff;
   GbBssGpStackPmTableApi gbBssGpStackPmTableApiBuff;
   
   memset(&gbNsStackPmTableApiBuff, 0, sizeof(GbNsStackPmTableApi));
   memset(&gbBssGpStackPmTableApiBuff, 0, sizeof(GbBssGpStackPmTableApi));
   gbNsStackPmTableApiBuff.dummyIndex = ONE;
   gbBssGpStackPmTableApiBuff.dummyIndex = ONE;

   dbStatus = insertGbNsStackPmTable(&gbNsStackPmTableApiBuff);

   if(dbStatus == DBLIB_SUCCESS)
   {
        LOG_PRINT(LOG_MAJOR, "Insert into GbNsStackPmTable successfull");
   }
   else
   {
        LOG_PRINT(LOG_MAJOR, "Insert into GbNsStackPmTable Unsuccessfull. DB Status =%x", dbStatus);
   }

   dbStatus = insertGbBssGpStackPmTable(&gbBssGpStackPmTableApiBuff);

   if(dbStatus == DBLIB_SUCCESS)
   {
        LOG_PRINT(LOG_INFO, "Insert into GbBssGpStackPmTable successfull");
   }
   else
   {
        LOG_PRINT(LOG_MAJOR, "Insert into GbBssGpStackPmTable Unsuccessfull. DB Status =%x", dbStatus);
   }
}
