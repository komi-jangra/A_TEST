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

Output        : I_U8 *OamScmBssapTimerConfig 
*************************************************************/
I_S32  GetBssapTimerConfigData(OamScmBssapTimerConfig  **bssapTimerConfigPtrToPtr, I_U8 *count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   *count = 0;
  void *BssapTimerTableApi=NULL;
  sBssapTimerTableApi *BssapTimerApi=NULL;
  OamScmBssapTimerConfig *bssapTimerConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SBSSAPTIMERDAO_ID,
               (I_PVoid *)&BssapTimerTableApi,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      bssapTimerConfigPtr = calloc (rowCount,sizeof(OamScmBssapTimerConfig));
      *bssapTimerConfigPtrToPtr = bssapTimerConfigPtr;
      while (rowCount)
      {
         BssapTimerApi = (sBssapTimerTableApi*)(BssapTimerTableApi + i*rowSize ); 
#ifdef MSC
         bssapTimerConfigPtr[i].bssapTimerT2 = BssapTimerApi->bssapTimerT2;
         bssapTimerConfigPtr[i].bssapTimerT5 = BssapTimerApi->bssapTimerT5;
         bssapTimerConfigPtr[i].bssapTimerT6 = BssapTimerApi->bssapTimerT6;
         bssapTimerConfigPtr[i].bssapTimerT7 = BssapTimerApi->bssapTimerT7;
         bssapTimerConfigPtr[i].bssapTimerT8 = BssapTimerApi->bssapTimerT8;
         bssapTimerConfigPtr[i].bssapTimerT10 = BssapTimerApi->bssapTimerT10;
         bssapTimerConfigPtr[i].bssapTimerT12 = BssapTimerApi->bssapTimerT12;
         bssapTimerConfigPtr[i].bssapTimerT16 = BssapTimerApi->bssapTimerT16;
         bssapTimerConfigPtr[i].bssapTimerT21 = BssapTimerApi->bssapTimerT21;
         bssapTimerConfigPtr[i].bssapTimerT22 = BssapTimerApi->bssapTimerT22;
#else
         bssapTimerConfigPtr[i].bssapTimerT1 = BssapTimerApi->bssapTimerT1;
         bssapTimerConfigPtr[i].bssapTimerT4 = BssapTimerApi->bssapTimerT4;
         bssapTimerConfigPtr[i].bssapTimerT10 = BssapTimerApi->bssapTimerT10;
         bssapTimerConfigPtr[i].bssapTimerT11 = BssapTimerApi->bssapTimerT11;
         bssapTimerConfigPtr[i].bssapTimerT13 = BssapTimerApi->bssapTimerT13;
         bssapTimerConfigPtr[i].bssapTimerT17 = BssapTimerApi->bssapTimerT17;
         bssapTimerConfigPtr[i].bssapTimerT18 = BssapTimerApi->bssapTimerT18;
         bssapTimerConfigPtr[i].bssapTimerT19 = BssapTimerApi->bssapTimerT19;
         bssapTimerConfigPtr[i].bssapTimerT20 = BssapTimerApi->bssapTimerT20;
#endif

         rowCount--;
         i++;
      }
         free(BssapTimerTableApi);
         return 0;
   }
   else
  {
     return dbSts;
   }

}




/********************End Of File *******************************************/
