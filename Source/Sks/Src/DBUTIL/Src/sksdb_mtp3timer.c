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

Output        : *mtp3TimerConfigPtrToPtr 
*************************************************************/

I_S32  GetMtp3TimerConfigData(OamScmMtp3TimerConfig  **mtp3TimerConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize  = 0;
   I_S32 rowCount = 0;
   I_S32 i = 0;
   I_S32 dbSts;
   *count = 0;
   void *mtp3TimerTblPtr=NULL;
   sMtp3TimerTableApi *mtp3TimerPtr=NULL;
   OamScmMtp3TimerConfig *mtp3TimerConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SMTP3TIMERDAO_ID,
               (I_PVoid *)&mtp3TimerTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      mtp3TimerConfigPtr = calloc (rowCount,sizeof(OamScmMtp3TimerConfig));
      *mtp3TimerConfigPtrToPtr = mtp3TimerConfigPtr; 
      while (rowCount)
      {
         mtp3TimerPtr = (sMtp3TimerTableApi*)(mtp3TimerTblPtr + i*rowSize); 
         mtp3TimerConfigPtr[i].mtp3TimerT1 = mtp3TimerPtr->mtp3Timermtp3_T1;
         mtp3TimerConfigPtr[i].mtp3TimerT2 = mtp3TimerPtr->mtp3Timermtp3_T2;
         mtp3TimerConfigPtr[i].mtp3TimerT3 = mtp3TimerPtr->mtp3Timermtp3_T3;
         mtp3TimerConfigPtr[i].mtp3TimerT4 = mtp3TimerPtr->mtp3Timermtp3_T4;
         mtp3TimerConfigPtr[i].mtp3TimerT5 = mtp3TimerPtr->mtp3Timermtp3_T5;
         mtp3TimerConfigPtr[i].mtp3TimerT6 = mtp3TimerPtr->mtp3Timermtp3_T6;
         mtp3TimerConfigPtr[i].mtp3TimerT7 = mtp3TimerPtr->mtp3Timermtp3_T7;
         mtp3TimerConfigPtr[i].mtp3TimerT8 = mtp3TimerPtr->mtp3Timermtp3_T8;
         mtp3TimerConfigPtr[i].mtp3TimerT9 = mtp3TimerPtr->mtp3Timermtp3_T9;
         mtp3TimerConfigPtr[i].mtp3TimerT10 = mtp3TimerPtr->mtp3Timermtp3_T10;
         mtp3TimerConfigPtr[i].mtp3TimerT11 = mtp3TimerPtr->mtp3Timermtp3_T11;
         mtp3TimerConfigPtr[i].mtp3TimerT12 = mtp3TimerPtr->mtp3Timermtp3_T12;
         mtp3TimerConfigPtr[i].mtp3TimerT13 = mtp3TimerPtr->mtp3Timermtp3_T13;
         mtp3TimerConfigPtr[i].mtp3TimerT14 = mtp3TimerPtr->mtp3Timermtp3_T14;
         mtp3TimerConfigPtr[i].mtp3TimerT15 = mtp3TimerPtr->mtp3Timermtp3_T15;
         mtp3TimerConfigPtr[i].mtp3TimerT16 = mtp3TimerPtr->mtp3Timermtp3_T16;
         mtp3TimerConfigPtr[i].mtp3TimerT17 = mtp3TimerPtr->mtp3Timermtp3_T17;
         mtp3TimerConfigPtr[i].mtp3TimerT18 = mtp3TimerPtr->mtp3Timermtp3_T18;
         mtp3TimerConfigPtr[i].mtp3TimerT19 = mtp3TimerPtr->mtp3Timermtp3_T19;
         mtp3TimerConfigPtr[i].mtp3TimerT20 = mtp3TimerPtr->mtp3Timermtp3_T20;
         mtp3TimerConfigPtr[i].mtp3TimerT21 = mtp3TimerPtr->mtp3Timermtp3_T21;
         mtp3TimerConfigPtr[i].mtp3TimerT22 = mtp3TimerPtr->mtp3Timermtp3_T22;
         mtp3TimerConfigPtr[i].mtp3TimerT23 = mtp3TimerPtr->mtp3Timermtp3_T23;
         mtp3TimerConfigPtr[i].mtp3TimerT24 = mtp3TimerPtr->mtp3Timermtp3_T24;
         mtp3TimerConfigPtr[i].mtp3TimerT25 = mtp3TimerPtr->mtp3Timermtp3_T25;
         mtp3TimerConfigPtr[i].mtp3TimerT26 = mtp3TimerPtr->mtp3Timermtp3_T26;
         mtp3TimerConfigPtr[i].mtp3TimerT27 = mtp3TimerPtr->mtp3Timermtp3_T27;
         mtp3TimerConfigPtr[i].mtp3TimerT28 = mtp3TimerPtr->mtp3Timermtp3_T28;
         mtp3TimerConfigPtr[i].mtp3TimerT29 = mtp3TimerPtr->mtp3Timermtp3_T29;
         mtp3TimerConfigPtr[i].mtp3TimerT30 = mtp3TimerPtr->mtp3Timermtp3_T30;
         mtp3TimerConfigPtr[i].mtp3TimerT31 = mtp3TimerPtr->mtp3Timermtp3_T31;
         mtp3TimerConfigPtr[i].mtp3TimerT32 = mtp3TimerPtr->mtp3Timermtp3_T32;
         mtp3TimerConfigPtr[i].mtp3TimerT33 = mtp3TimerPtr->mtp3Timermtp3_T33;
         mtp3TimerConfigPtr[i].mtp3TimerT34 = mtp3TimerPtr->mtp3Timermtp3_T34;
         rowCount--; 
         i++;
      }         
         free(mtp3TimerTblPtr);
         return 0;
   }
   else
   {
     return dbSts;  
   } 

}

/********************End Of File *******************************************/
