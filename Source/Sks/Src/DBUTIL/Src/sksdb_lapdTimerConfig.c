/*se ts=2************************************File Source*****
File Name		:	  sksdb_lapdTimerConfig.c 
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
1.      Rel0.0         None         anand singh         Creation
*************************************************************/


#include <sksdb_include.h>

/************************************************************
Return Values : = 0 for Success
                <> 0  for failure 

Output        : I_U8 *lapdTimerConfigPtrToPtr
************************************************************/ 

I_S32  GetLapdTimerConfigData(OamScmLapdTimerConfig  **lapdTimerConfigPtrToPtr, I_U8 *count)
{
#ifdef anand
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void        *lapdTimerTblPtr=NULL;
   sLapdTimerTableApi *lapdTimerPtr=NULL;
   OamScmLapdTimerConfig *lapdTimerConfigPtr=NULL;

   dbSts = clib_dump((I_S32)LAPDTIMERDAO_ID,
               (I_PVoid *)&lapdTimerTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      lapdTimerConfigPtr = calloc (rowCount,sizeof(OamScmLapdTimerConfig));
      *lapdTimerConfigPtrToPtr = lapdTimerConfigPtr;
      while (rowCount)
      {
        lapdTimerPtr = (sLapdTimerTableApi*)(lapdTimerTblPtr +  i*rowSize);
        lapdTimerConfigPtr[i].lapdTimerT200 = lapdTimerPtr->lapdTimerT200;
        lapdTimerConfigPtr[i].lapdTimerT203 = lapdTimerPtr->lapdTimerT203;
        lapdTimerConfigPtr[i].N200 = lapdTimerPtr->N200;
        rowCount--;
        i++;
      }
         free(lapdTimerTblPtr);
         return 0;
   }
   else
   {
     return dbSts;
   }
#endif
}




/********************End Of File *******************************************/
