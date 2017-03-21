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

/************************************************************
Return Values : = 0 for Success
                <> 0  for failure 

Output        : I_U8 *mapTImerConfigPtrToPtr
************************************************************/ 

I_S32  GetMapTimerConfigData(OamScmMapTimerConfig  **mapTImerConfigPtrToPtr, I_U8 *count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void        *maptimerTblPtr=NULL;
   MapTimerTbl *maptimerPtr=NULL;
   OamScmMapTimerConfig *maptimerConfigPtr=NULL;

   dbSts = clib_dump((I_S32)MAPTIMERDAO_ID,
               (I_PVoid *)&maptimerTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      maptimerConfigPtr = calloc (rowCount,sizeof(OamScmMapTimerConfig));
      *mapTImerConfigPtrToPtr = maptimerConfigPtr;
      while (rowCount)
      {
        maptimerPtr = (MapTimerTbl*)(maptimerTblPtr +  i*rowSize);
        maptimerConfigPtr[i].mapTimerSmall = maptimerPtr[i].mapTimerSmall;
        maptimerConfigPtr[i].mapTimerMedium =  maptimerPtr[i].mapTimerMedium;
        maptimerConfigPtr[i].mapTimerMediumLarge = maptimerPtr[i].mapTimerMediumLarge;
        maptimerConfigPtr[i].mapTimerLarge = maptimerPtr[i].mapTimerLarge;
        rowCount--;
        i++;
      }
         free(maptimerTblPtr);
         return 0;
   }
   else
   {
     return dbSts;
   }
}




/********************End Of File *******************************************/
