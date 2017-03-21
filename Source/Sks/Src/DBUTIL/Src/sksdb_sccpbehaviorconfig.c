
/*se ts=2************************************File Source*****
File Name		:	  sksdb_sccpbehaviorconfig.c 
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

Output        :  *sccpBehaviorConfigPtr
*************************************************************/
I_S32  GetSccpBehaviorConfigData(sSccpBehaviorConfigTableApi  **sccpBehaviorConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S32 i = 0;
   I_S32 dbSts;
   *count = 0;
   void                        *sccpBehaviorTblPtr=NULL;
   SccpBehaviorConfigTbl        *sccpBehaviorPtr = NULL;
   sSccpBehaviorConfigTableApi *sccpBehaviorConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SCCPBEHAVIORCONFIGDAO_ID,
               (I_PVoid *)&sccpBehaviorTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      sccpBehaviorConfigPtr = calloc (rowCount,sizeof(sSccpBehaviorConfigTableApi));
      *sccpBehaviorConfigPtrToPtr = sccpBehaviorConfigPtr; 
      while (rowCount)
      {
         sccpBehaviorPtr = (SccpBehaviorConfigTbl*)(sccpBehaviorTblPtr + i*rowSize);
         sccpBehaviorConfigPtr[i].sccpBehaviorConfigps = sccpBehaviorPtr->sccpBehaviorConfigps;
         sccpBehaviorConfigPtr[i].sccpBehaviorConfigus = sccpBehaviorPtr->sccpBehaviorConfigus;
         sccpBehaviorConfigPtr[i].sccpBehaviorConfigpi = sccpBehaviorPtr->sccpBehaviorConfigpi;
         sccpBehaviorConfigPtr[i].sccpBehaviorConfigpe = sccpBehaviorPtr->sccpBehaviorConfigpe;
         rowCount--; 
         i++;

      }         
         free(sccpBehaviorTblPtr);
         return 0;
   }
   else
   {
     return dbSts;  
   } 

}



/********************End Of File *******************************************/
