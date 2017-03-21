/*se ts=2************************************File Source*****
File Name		:	  sksdb_mtp3timer.c 
Purpose			:		This file has utility function to retrive 
                     system configuraion values from DB.
Project			:		GSM
Subsystem		:	  Db	
Author			:		
CSCI id			:
Version			:		V0.1
*************************************************************/

/*******************************************Change History***
S.No.   Release        Patch        Author        Description
1.      Rel0.0         None         xxxxx         Creation
*************************************************************/


#include <sksdb_include.h>


/*************************************************************
Return Values : = 0 for Success
                <> 0  for failure 

Output        : I_U8 *cssfTimerConfigPtrToPtr 
*************************************************************/

I_S32  GetCssfTimerConfigData(OamScmCssfTimerConfig **cssfTimerConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S32 i = 0;
   I_S32 dbSts;
   *count = 0;
   void *cssfTimerTblPtr=NULL;
   sCssfTimerTableApi *cssfTimerPtr=NULL;
   OamScmCssfTimerConfig *cssfTimerConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SCSSFTIMERDAO_ID,
               (I_PVoid *)&cssfTimerTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      cssfTimerConfigPtr = calloc (rowCount,sizeof(OamScmCssfTimerConfig));
      *cssfTimerConfigPtrToPtr = cssfTimerConfigPtr; 
      while (rowCount)
      {
       cssfTimerPtr = (sCssfTimerTableApi*)(cssfTimerTblPtr + i*rowSize); 
       cssfTimerConfigPtr[i].cssfTimerNonUi = cssfTimerPtr->cssfTimerNonUi;
       cssfTimerConfigPtr[i].cssfTimerUi = cssfTimerPtr->cssfTimerUi;
       cssfTimerConfigPtr[i].cssfTimerTccd = cssfTimerPtr->cssfTimerTccd;
       cssfTimerConfigPtr[i].cssfTimerOperAcr = cssfTimerPtr->cssfTimerOperAcr;
       cssfTimerConfigPtr[i].cssfTimerOperCirReport = cssfTimerPtr->cssfTimerOperCirReport;
       cssfTimerConfigPtr[i]. cssfTimerOperEventReport= cssfTimerPtr->cssfTimerOperEventReport;
       cssfTimerConfigPtr[i].cssfTimerOperInitialDp = cssfTimerPtr->cssfTimerOperInitialDp;
       cssfTimerConfigPtr[i].cssfTimerOperSpecResourceReport = cssfTimerPtr->cssfTimerOperSpecResourceReport;
       cssfTimerConfigPtr[i].cssfTimerSmsOperEventReport = cssfTimerPtr->cssfTimerSmsOperEventReport;
       cssfTimerConfigPtr[i].cssfTimerSmsOperInitialDp = cssfTimerPtr->cssfTimerSmsOperInitialDp;
       cssfTimerConfigPtr[i].cssfTimerSmsTssf = cssfTimerPtr->cssfTimerSmsTssf;
       rowCount--; 
       i++;
      }         
       free(cssfTimerTblPtr);
       return 0;
   }
   else
   {
     return dbSts;  
   } 

}

/********************End Of File *******************************************/
