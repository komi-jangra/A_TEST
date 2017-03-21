
/*se ts=2************************************File Source*****
File Name		:	  sksdb_mapinitconfig.c 
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

Output        :    mapInitConfigPtr
*************************************************************/
I_S32  GetMapInitConfigData(mapInitConfig  **mapInitConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S32 i = 0;
   I_S32 dbSts;
   *count = 0; 
   void *mapInitTblPtr=NULL;
   MapInitConfigTbl *mapInitPtr=NULL;
   mapInitConfig *mapInitConfigPtr=NULL;

   dbSts = clib_dump((I_S32)MAPINITCONFIGDAO_ID,
               (I_PVoid *)&mapInitTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      mapInitConfigPtr = calloc (rowCount,sizeof(mapInitConfig));
      *mapInitConfigPtrToPtr = mapInitConfigPtr; 
      while (rowCount)
      {
         mapInitPtr = (MapInitConfigTbl*)(mapInitTblPtr + i*rowSize); 
         mapInitConfigPtr[i].mapInitConfigstackType = mapInitPtr->mapInitConfigstackType;
         mapInitConfigPtr[i].mapInitConfignumofDsm = mapInitPtr->mapInitConfignumofDsm;
         mapInitConfigPtr[i].mapInitConfignumofSSM = mapInitPtr->mapInitConfignumofSSM;
         mapInitConfigPtr[i].mapInitConfigmaxDialogueAge = mapInitPtr->mapInitConfigmaxDialogueAge;
         rowCount--; 
         i++;

      }         
         free(mapInitTblPtr);
         return 0;
   }
   else
   {
     return dbSts;  
   } 

}



/********************End Of File *******************************************/
