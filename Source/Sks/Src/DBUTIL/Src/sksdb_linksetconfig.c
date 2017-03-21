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


I_S32  GetLinksetConfigData(OamScmLinkSetConfig  **linksetConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   *count = 0;
   void       *linkSetTblPtr=NULL;
   //LinkSetTbl *linkSetPtr=NULL;
   LinksetTableApi *linkSetPtr=NULL;
   OamScmLinkSetConfig *linksetConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SCM_DAO_LINKSETTABLE,
               (I_PVoid *)&linkSetTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, ....Db call dump", dbSts, rowSize);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(LinksetTableApi)), (unsigned char* )linkSetTblPtr, 15);
      *count = rowCount;
      linksetConfigPtr = calloc (rowCount,sizeof(OamScmLinkSetConfig));
      *linksetConfigPtrToPtr = linksetConfigPtr; 
      while (rowCount)
      {
         linkSetPtr = (LinksetTableApi*)(linkSetTblPtr + i*rowSize);
         linksetConfigPtr[i].linkSetId = (unsigned short)linkSetPtr->linksetID;
         linksetConfigPtr[i].adjacentPointCode = (unsigned short)linkSetPtr->adjacentPointCode;
         linksetConfigPtr[i].networkIndicator = (unsigned char)linkSetPtr->networkIndicator;
         rowCount--; 
         i++;

      }         
         free(linkSetTblPtr);
         return 0;
   }
   else
   {
     return dbSts;  
   } 
}



/********************End Of File *******************************************/
