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

Output        : I_U8 *InterfaceConfig 
*************************************************************/
I_S32  GetInterfaceConfigData(OamScmInterfaceConfig  **interfaceConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   *count = 0;
   void         *interfaceTblPtr=NULL;
   //InterfaceTbl *interfacePtr=NULL;
   AifInterfaceTableApi *interfacePtr=NULL;
   OamScmInterfaceConfig *inerfaceConfigPtr=NULL;

   dbSts = clib_dump((I_S32)INTERFACEDAO_ID,
               (I_PVoid *)&interfaceTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   SCM_printf (SCM_DEBUG, "dbSts: %d, ....Db call dump", dbSts);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount * sizeof(AifInterfaceTableApi)), (unsigned char* )interfaceTblPtr, 15);
      *count = rowCount;
      inerfaceConfigPtr = calloc (rowCount,sizeof(OamScmInterfaceConfig));
      *interfaceConfigPtrToPtr = inerfaceConfigPtr; 
      while (rowCount)
      {
       interfacePtr = (AifInterfaceTableApi*)(interfaceTblPtr + i*rowSize);
        /*  InterfaceType */
         inerfaceConfigPtr[i].interfaceType = interfacePtr->interfaceType;
        /*  InterfaceId */
         inerfaceConfigPtr[i].interfaceId = interfacePtr->interfaceId;
        /*  PointCode */
         inerfaceConfigPtr[i].pointCode = (unsigned int)interfacePtr->dpc;
         rowCount--; 
         i++;
      }         
         free(interfaceTblPtr);
         return 0;
   }
   else
   {
     return dbSts;  
   } 
}


/********************End Of File *******************************************/
