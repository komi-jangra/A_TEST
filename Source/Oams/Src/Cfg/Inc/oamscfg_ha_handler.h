/***********************************File Header ***************************
File Name        : oamscfg_ha_handler.h
Purpose          : This file contains functions that fill global data 
                   after swtichover
Project          : R2.9 BSC
Subsystem        : Oams
Author           : Rishabh Garg
CSCI ID          :
Version          :
 ************************************* End **********************************/

I_Void fillTrxGlobalData();
I_Void fillBichGlobalData();
I_Void fillCellData();
I_Void fillE1TimeSlotData();
I_Void fillE1Data();
I_Void fillDspData();
I_Void fillGlobalDataAfterSwitchover();
I_U8 checkOamProcedure();
/*Merger for Mantis #31470*/
I_Void fillNseiData();
/*Merger for Mantis #31470*/
