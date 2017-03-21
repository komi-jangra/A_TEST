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

Output        : I_U8 *sccpTimerConfigPtrToPtr 
*************************************************************/

I_S32  GetSccpTimerConfigData(OamScmSccpTimerConfig  **sccpTimerConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S32 i = 0;
   I_S32 dbSts;
   *count = 0;
   void *sccpTimerTblPtr=NULL;
   sSccpTimerTableApi *sccpTimerPtr=NULL;
   OamScmSccpTimerConfig *sccpTimerConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SSCCPTIMERDAO_ID,
               (I_PVoid *)&sccpTimerTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      sccpTimerConfigPtr = calloc (rowCount,sizeof(OamScmSccpTimerConfig));
      *sccpTimerConfigPtrToPtr = sccpTimerConfigPtr; 
      while (rowCount)
      {
         sccpTimerPtr = (sSccpTimerTableApi*)(sccpTimerTblPtr + i*rowSize);  
         sccpTimerConfigPtr[i].sccpTimerstatInfo = sccpTimerPtr->sccpTimerstatInfo;
         sccpTimerConfigPtr[i].sccpTimercoordChg = sccpTimerPtr->sccpTimercoordChg;
         sccpTimerConfigPtr[i].sccpTimerig0reSST = sccpTimerPtr->sccpTimerig0reSST;
         sccpTimerConfigPtr[i].sccpTimerrtgStatInfor = sccpTimerPtr->sccpTimerrtgStatInfo;
         sccpTimerConfigPtr[i].sccpTimerconn = sccpTimerPtr->sccpTimerconn;
         sccpTimerConfigPtr[i].sccpTimerrelease = sccpTimerPtr->sccpTimerrelease;
         sccpTimerConfigPtr[i].sccpTimerreset = sccpTimerPtr->sccpTimerreset;
         sccpTimerConfigPtr[i].sccpTimerias = sccpTimerPtr->sccpTimerias;
         sccpTimerConfigPtr[i].sccpTimeriar = sccpTimerPtr->sccpTimeriar;
         sccpTimerConfigPtr[i].sccpTimerguard = sccpTimerPtr->sccpTimerguard;
         sccpTimerConfigPtr[i].sccpTimerreassembly = sccpTimerPtr->sccpTimerreassembly;
         sccpTimerConfigPtr[i].sccpTimerinterval = sccpTimerPtr->sccpTimerinterval;
         sccpTimerConfigPtr[i].sccpTimerrepeatRelease = sccpTimerPtr->sccpTimerrepeatRelease;
         rowCount--; 
         i++;
      }         
         free(sccpTimerTblPtr);
         return 0;
   }
   else
   {
     return dbSts;  
   } 

}

/********************End Of File *******************************************/
