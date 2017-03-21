/***********************************File Header ***************************
File Name        : oamscfg_perf_counter_init.h
Purpose          : This file contains Performance Counter declarations
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef _OAMSCFG_PERF_COUNTER_INIT_H_
#define _OAMSCFG_PERF_COUNTER_INIT_H_

I_Void insertRowInPsPerformanceCounterTablesForCell(I_U16 cellId, I_U16 lac);
I_Void deleteRowFromPsPerformanceCounterTablesForCell(I_U16 cellId, I_U16 lac);
I_Void insertRowInPsPerfCounterTableForTrx(I_U32 ptrxId);
I_Void deleteRowFromPsPerfCounterTableForTrx(I_U32 ptrxId);
I_Void initializePsappCellAndGbBssGpStackCellTable();
I_Void initializePsPerformanceCounterTablesForBss();
I_Void initializePsPerfCounterTableForTrx();
I_Void insertRowInPsPerformanceCounterTablesForBss();

#endif

