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

Output        : I_U8 *isupTimerConfigPtrToPtr 
*************************************************************/

I_S32  GetIsupTimerConfigData(OamScmIsupTimerConfig  **isupTimerConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S32 i = 0;
   I_S32 dbSts;
   *count = 0;
   void *isupTimerTblPtr=NULL;
   sIsupTimerTableApi *isupTimerPtr=NULL;
   OamScmIsupTimerConfig *isupTimerConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SISUPTIMERDAO_ID,
               (I_PVoid *)&isupTimerTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      isupTimerConfigPtr = calloc (rowCount,sizeof(OamScmIsupTimerConfig));
      *isupTimerConfigPtrToPtr = isupTimerConfigPtr; 
      while (rowCount)
      {
         isupTimerPtr = (sIsupTimerTableApi*)(isupTimerTblPtr + i*rowSize);
         isupTimerConfigPtr[i].isupTimerT1 = isupTimerPtr->isupTimerT1;
         isupTimerConfigPtr[i].isupTimerT2 = isupTimerPtr->isupTimerT2;
         isupTimerConfigPtr[i].isupTimerT3 = isupTimerPtr->isupTimerT3;
         isupTimerConfigPtr[i].isupTimerT4 = isupTimerPtr->isupTimerT4;
         isupTimerConfigPtr[i].isupTimerT5 = isupTimerPtr->isupTimerT5;
         isupTimerConfigPtr[i].isupTimerT6 = isupTimerPtr->isupTimerT6;
         isupTimerConfigPtr[i].isupTimerT7 = isupTimerPtr->isupTimerT7;
         isupTimerConfigPtr[i].isupTimerT8 = isupTimerPtr->isupTimerT8;
         isupTimerConfigPtr[i].isupTimerT9 = isupTimerPtr->isupTimerT9;
         isupTimerConfigPtr[i].isupTimerT10 = isupTimerPtr->isupTimerT10;
         isupTimerConfigPtr[i].isupTimerT11 = isupTimerPtr->isupTimerT11;
         isupTimerConfigPtr[i].isupTimerT12 = isupTimerPtr->isupTimerT12;
         isupTimerConfigPtr[i].isupTimerT13 = isupTimerPtr->isupTimerT13;
         isupTimerConfigPtr[i].isupTimerT14 = isupTimerPtr->isupTimerT14;
         isupTimerConfigPtr[i].isupTimerT15 = isupTimerPtr->isupTimerT15;
         isupTimerConfigPtr[i].isupTimerT16 = isupTimerPtr->isupTimerT16;
         isupTimerConfigPtr[i].isupTimerT17 = isupTimerPtr->isupTimerT17;
         isupTimerConfigPtr[i].isupTimerT18 = isupTimerPtr->isupTimerT18;
         isupTimerConfigPtr[i].isupTimerT19 = isupTimerPtr->isupTimerT19;
         isupTimerConfigPtr[i].isupTimerT20 = isupTimerPtr->isupTimerT20;
         isupTimerConfigPtr[i].isupTimerT21= isupTimerPtr->isupTimerT21;
         isupTimerConfigPtr[i].isupTimerT22 = isupTimerPtr->isupTimerT22;
         isupTimerConfigPtr[i].isupTimerT23 = isupTimerPtr->isupTimerT23;
         isupTimerConfigPtr[i].isupTimerT24 = isupTimerPtr->isupTimerT24;
         isupTimerConfigPtr[i].isupTimerT25 = isupTimerPtr->isupTimerT25;
         isupTimerConfigPtr[i].isupTimerT26 = isupTimerPtr->isupTimerT26;
         isupTimerConfigPtr[i].isupTimerT27 = isupTimerPtr->isupTimerT27;
         isupTimerConfigPtr[i].isupTimerT28 = isupTimerPtr->isupTimerT28;
         isupTimerConfigPtr[i].isupTimerT29 = isupTimerPtr->isupTimerT29;
         isupTimerConfigPtr[i].isupTimerT30 = isupTimerPtr->isupTimerT30;
         isupTimerConfigPtr[i].isupTimerT31 = isupTimerPtr->isupTimerT31;
         isupTimerConfigPtr[i].isupTimerT32 = isupTimerPtr->isupTimerT32;
         isupTimerConfigPtr[i].isupTimerT33 = isupTimerPtr->isupTimerT33;
         isupTimerConfigPtr[i].isupTimerT34 = isupTimerPtr->isupTimerT34;
         isupTimerConfigPtr[i].isupTimerT35 = isupTimerPtr->isupTimerT35;
         isupTimerConfigPtr[i].isupTimerT36 = isupTimerPtr->isupTimerT36;
         isupTimerConfigPtr[i].isupTimerT37 = isupTimerPtr->isupTimerT37;
         isupTimerConfigPtr[i].isupTimerT38 = isupTimerPtr->isupTimerT38;
         isupTimerConfigPtr[i].isupTimerT39 = isupTimerPtr->isupTimerT39;
         rowCount--; 
         i++;

      }         
         free(isupTimerTblPtr);
         return 0;
   }
   else
   {
     return dbSts;  
   } 

}

/********************End Of File *******************************************/
