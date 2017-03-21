
/*se ts=2************************************File Source*****
File Name		:	  sksdb_sksgenconfig.c 
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

Output        :   *sksGenConfigptr
*************************************************************/
I_S32  GetSksGenConfigData( sksGenConfig **sksGenConfigptrToPtr12, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S32 i = 0;
   I_S32 dbSts;
   sksGenConfig  *sksGenConfigptr=NULL;
   void           *sksGenTblPtr=NULL;
   SksGenConfigTbl *sksGenPtr=NULL;

   dbSts = clib_dump((I_S32)SKSGENCONFIGDAO_ID,
               (I_PVoid *)&sksGenTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      sksGenConfigptr = (sksGenConfig*)calloc(rowCount, sizeof(sksGenConfig));
      //sksGenPtr = calloc(rowCount, rowSize);
      while (rowCount)
      {
         
         sksGenPtr =(SksGenConfigTbl*) (sksGenTblPtr + i*rowSize);
	 sksGenConfigptr[i].sksGenCfgstackType = sksGenPtr->sksGenCfgstackType;
         sksGenConfigptr[i].sksGenCfgTraceLevel = sksGenPtr->sksGenCfgtraceLevel;
         sksGenConfigptr[i].sksGenCfgtraceOutput = sksGenPtr->sksGenCfgtraceOutput;
         sksGenConfigptr[i].sksGenCfgtraceOnOff = sksGenPtr->sksGenCfgtraceOnOff;
         rowCount--;
         i++; 

      }         
         *sksGenConfigptrToPtr12 = sksGenConfigptr; 
         free(sksGenTblPtr);
         return 0;
   }
   else
   {
     return dbSts;  
   } 

}



/********************End Of File *******************************************/
