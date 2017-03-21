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

Output        : I_U8 *OamScmSs7GttConfig 
*************************************************************/
I_S32  GetSS7GttConfigData(OamScmSs7GttConfig **ss7GttConfigPtrToPtr, I_U8 *count)
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0, i = 0;
   I_S32 dbSts;
   *count = 0;
   void *sS7GttTblPtr=NULL;
   GTTTbl *sS7GttPtr=NULL;
   OamScmSs7GttConfig *ss7GttConfigPtr=NULL;

   dbSts = clib_dump((I_S32)GTTDAO_ID,
               (I_PVoid *)&sS7GttTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      ss7GttConfigPtr = calloc (rowCount,sizeof(OamScmSs7GttConfig));
      *ss7GttConfigPtrToPtr = ss7GttConfigPtr;
      while (rowCount)
      {
         sS7GttPtr = (GTTTbl*)(sS7GttTblPtr + i*rowSize);
         memset(&ss7GttConfigPtr[i].digitString[0], 0, 20);  
         strncpy((char*)&ss7GttConfigPtr[i].digitString[0], (char*)&sS7GttPtr->digitString[0], 20);  
         ss7GttConfigPtr[i].priDestPc = sS7GttPtr->primaryDpc;
         ss7GttConfigPtr[i].ssn = sS7GttPtr->ssn;
         ss7GttConfigPtr[i].routeOn = sS7GttPtr->routeOn;
         rowCount--;
         i++;

      }
         free(sS7GttTblPtr);
         return 0;
   }
   else
   {
     return dbSts;
   }

}



/********************End Of File *******************************************/
