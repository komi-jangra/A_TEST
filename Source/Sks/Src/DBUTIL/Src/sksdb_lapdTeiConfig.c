/*se ts=2************************************File Source*****
File Name		:	  sksdb_lapdTeiConfig.c 
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

Output        : I_U8 *lapdTeiConfigPtrToPtr
************************************************************/ 

I_S32  GetLapdTeiConfigData(OamScmLapdTEIConfig  **lapdTeiConfigPtrToPtr, I_U8 *count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void        *lapdTeiTblPtr=NULL;
   LapdTEIConfigTableApi *lapdTeiPtr=NULL;
   OamScmLapdTEIConfig *lapdTeiConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SCM_DAO_LAPDTEICONFIGTABLE,
               (I_PVoid *)&lapdTeiTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      lapdTeiConfigPtr = calloc (rowCount,sizeof(OamScmLapdTEIConfig));
      *lapdTeiConfigPtrToPtr = lapdTeiConfigPtr;
      while (rowCount)
      {
        lapdTeiPtr = (LapdTEIConfigTableApi*)(lapdTeiTblPtr +  i*rowSize);
        lapdTeiConfigPtr[i].lapdtimeslot = lapdTeiPtr->lapdtimeslot;
        lapdTeiConfigPtr[i].lapdTei = lapdTeiPtr->lapdTei;
        lapdTeiConfigPtr[i].applTei = lapdTeiPtr->applTei;
        rowCount--;
        i++;
      }
         free(lapdTeiTblPtr);
         return 0;
   }
   else
   {
     return dbSts;
   }
}




/********************End Of File *******************************************/
