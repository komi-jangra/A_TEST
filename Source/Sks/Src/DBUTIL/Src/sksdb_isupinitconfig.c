
/*se ts=2************************************File Source*****
File Name		:	  sksdb_isupinitconfig.c 
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

Output        :  isupInitConfigPtr
*************************************************************/
I_S32  GetIsupInitConfigData(sIsupInitConfigTableApi  **isupInitConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S32 i = 0;
   I_S32 dbSts;
   IsupInitConfigTbl *isupInitTblPtr=NULL;
   IsupInitConfigTbl *isupInitPtr=NULL;
   sIsupInitConfigTableApi *isupInitConfigPtr=NULL;

   dbSts = clib_dump((I_S32)ISUPINITCONFIGDAO_ID,
               (I_PVoid *)&isupInitTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      isupInitConfigPtr = calloc (rowCount,sizeof(sIsupInitConfigTableApi));
      *isupInitConfigPtrToPtr = isupInitConfigPtr; 
      while (rowCount)
      {
         isupInitPtr = (isupInitTblPtr + i*rowCount);
         isupInitConfigPtr[i].isupInitConfigstackType = isupInitPtr->isupInitConfigstackType;
         isupInitConfigPtr[i].isupInitConfigredundSt = isupInitPtr->isupInitConfigredundSt;
         isupInitConfigPtr[i].isupInitConfigsubService = isupInitPtr->isupInitConfigsubService;
         isupInitConfigPtr[i].isupInitConfigmaxDpc = isupInitPtr->isupInitConfigmaxDpc;
         isupInitConfigPtr[i].isupInitConfigmaxOpcDpcPair = isupInitPtr->isupInitConfigmaxOpcDpcPair;
         isupInitConfigPtr[i].isupInitConfigmaxCicPerOpcDpcPair = isupInitPtr->isupInitConfigmaxCicPerOpcDpcPair;
         isupInitConfigPtr[i].isupInitConfigmaxCic = isupInitPtr->isupInitConfigmaxCic;
         isupInitConfigPtr[i].isupInitConfigmacCktGrp = isupInitPtr->isupInitConfigmacCktGrp;
         isupInitConfigPtr[i].isupInitConfigmaxCicFilter = isupInitPtr->isupInitConfigmaxCicFilter;
         isupInitConfigPtr[i].isupInitConfigmaxCdpnFilter = isupInitPtr->isupInitConfigmaxCdpnFilter;
         isupInitConfigPtr[i].isupInitConfigmaxCgpnFilter = isupInitPtr->isupInitConfigmaxCgpnFilter;
         rowCount--; 
         i++;
      }         
         free(isupInitTblPtr);
         return 0;
   }
   else
   {
     return dbSts;  
   } 

}



/********************End Of File *******************************************/
