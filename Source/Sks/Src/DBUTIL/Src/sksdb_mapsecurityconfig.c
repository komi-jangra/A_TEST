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

Output        : I_U8 mapSecurityConfigPtrToPtr 
*************************************************************/
I_S32  GetMapSecurityConfigData(OamScmMapSecurityConfig  **mapSecurityConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S32 i = 0;
   I_S32 dbSts;
   *count = 0;
   void *mapPlmnTblPtr=NULL;
   MapPlmnSATbl *mapPlmnPtr=NULL;
   OamScmMapSecurityConfig *mapSecurityConfigPtr=NULL;

   dbSts = clib_dump((I_S32)MAPPLMNSADAO_ID,
               (I_PVoid *)&mapPlmnTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   if(dbSts == DB_SUCCESS)
   {
      *count = rowCount;
      mapSecurityConfigPtr = calloc (rowCount,sizeof(OamScmMapSecurityConfig));
      *mapSecurityConfigPtrToPtr = mapSecurityConfigPtr; 
      while (rowCount)
      {
         mapPlmnPtr = (MapPlmnSATbl*)(mapPlmnTblPtr + i*rowSize);
         memset(mapSecurityConfigPtr[i].srcPlmnId, 0 , 20);
         strcpy(mapSecurityConfigPtr[i].srcPlmnId, mapPlmnPtr->srcPlmnId); 
         memset(mapSecurityConfigPtr[i].dstPlmnId, 0 , 20);
         strcpy(mapSecurityConfigPtr[i].dstPlmnId, mapPlmnPtr->dstPlmnId); 
         mapSecurityConfigPtr[i].fallBackAllowedFlag = mapPlmnPtr->fallBackAllowedFlag;
         mapSecurityConfigPtr[i].plmnSecureFlag = mapPlmnPtr->plmnSecureFlag;
         mapSecurityConfigPtr[i].spi = mapPlmnPtr->spi;
         mapSecurityConfigPtr[i].mea = mapPlmnPtr->mea;
         memset(mapSecurityConfigPtr[i].mek, 0 , 20);
         strcpy(mapSecurityConfigPtr[i].mek,  mapPlmnPtr->mek);
         mapSecurityConfigPtr[i].mia = mapPlmnPtr->mia;
         memset(mapSecurityConfigPtr[i].mik, 0 , 20);
         strcpy(mapSecurityConfigPtr[i].mik,  mapPlmnPtr->mik);
         mapSecurityConfigPtr[i].pPri = mapPlmnPtr->pPri;
         mapSecurityConfigPtr[i].pPi = mapPlmnPtr->pPi;
         memset(mapSecurityConfigPtr[i].hardExpiryTimer, 0 , 20);
         strcpy(mapSecurityConfigPtr[i].hardExpiryTimer, mapPlmnPtr->hardExpiryTimer);
         memset(mapSecurityConfigPtr[i].softExpiryTimer, 0 , 20);
         strcpy(mapSecurityConfigPtr[i].softExpiryTimer, mapPlmnPtr->softExpiryTimer);
         rowCount--; 
         i++;
      }         
         free(mapPlmnTblPtr);
         return 0;
   }
   else
   {
     return dbSts;  
   } 

}


/********************End Of File *******************************************/
