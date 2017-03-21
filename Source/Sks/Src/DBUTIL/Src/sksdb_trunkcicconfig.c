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

Output        : I_U8 *mscId (Ascii Digit String Null Terminated) 
*************************************************************/
I_S32  GetInterfaceConfigDataWithTgpId(OamScmTrunkCicConfig  *trunkCicConfigPtr, I_U16 tgpid);


 
I_S32  GetTrunkCicConfigData(OamScmTrunkCicConfig  **trunkCicConfigPtrToPtr, I_U8 *count) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S16 i = 0, t =0;
   I_S32 dbSts;
   *count = 0;
   I_U16 tgpId=0;
   *count = 0;
   void *trunkTblPtr=NULL;
   //TrunkTbl *trunkCicTblPtr=NULL;
    AiftrunkTableApi *trunkCicTblPtr=NULL;
   OamScmTrunkCicConfig *trunkCicConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SCM_DAO_AIFTRUNKTABLE,
               (I_PVoid *)&trunkTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   SCM_printf (SCM_DEBUG, "dbSts: %d, ....Db call dump", dbSts);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0, (rowCount * sizeof( AiftrunkTableApi)), (unsigned char* )trunkTblPtr, 15);
      //*count = rowCount;
      trunkCicConfigPtr = calloc (rowCount,sizeof(OamScmTrunkCicConfig));
      *trunkCicConfigPtrToPtr = trunkCicConfigPtr; 
      while (rowCount)
      {
        trunkCicTblPtr = ( AiftrunkTableApi*)(trunkTblPtr + i*rowSize);
        /*  StartCic */
         trunkCicConfigPtr[t].startCic = (unsigned int)trunkCicTblPtr->startCic;
        /*  EndCic */
         trunkCicConfigPtr[t].endCic = (unsigned int)trunkCicTblPtr->endCic;

        /*  tgpId */
         tgpId = (unsigned short)trunkCicTblPtr->tgpId;
         if(tgpId != INVALID_TGP)
         { 
           dbSts= GetInterfaceConfigDataWithTgpId(&trunkCicConfigPtr[t],  tgpId);

           if((dbSts != DB_SUCCESS) && (t == 0))
            {
              free(trunkTblPtr);
     	        return dbSts;  
            }	 
           else
            {
            if(dbSts != DB_SUCCESS)
             {
              free(trunkTblPtr);
              *count = t;
              return 0;
             }
            }
          t++;
          *count = t; 
         }
          i++;
          rowCount--; 
      }         
     free(trunkTblPtr);
     if(t == 0)
     {
      return -1;
     }
     return 0;
   }
   else
   {
     return dbSts;  
   } 

}

I_S32  GetInterfaceConfigDataWithTgpId(OamScmTrunkCicConfig  *trunkCicConfigPtr, I_U16 tgpid) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S16 i = 0;
   //InterfaceTbl *interfaceTblPtr=NULL;
   AifInterfaceTableApi *interfaceTblPtr=NULL;
   AifInterfaceTableIndices aifIndex;
   AifInterfaceTableApi *aifTablePtr = NULL;
   //TrunkGroupTbl *trunkGroupTblPtr =NULL;
   TrunkGroupTableApi *trunkGroupTblPtr =NULL;
   TrunkGroupTableSecIndices trunkGroupIndex;
   trunkGroupIndex.tgpId = tgpid; 
   I_U16 interfaceId=0;
   I_S32 dbSts;

        dbSts = clib_get((I_S32)SCM_DAO_TRUNKGROUPTABLE, SCM_MET_GET_SEC_TRUNKGROUPTABLE,
                    (I_PVoid)&trunkGroupIndex,sizeof(TrunkGroupTableSecIndices),(I_PVoid*)&trunkGroupTblPtr,(I_S16 *)&rowSize,&rowCount);
        if(dbSts != CLIB_SUCCESS)
         {
        	return dbSts;
         } 

         if ( rowCount != 1)
          {
              free(trunkGroupTblPtr);
               return -1;
          } 
                    /*  InterfaceId */
          interfaceId = (TrunkGroupTableApi*)trunkGroupTblPtr->interfaceId;
          free(trunkGroupTblPtr);
              
        aifIndex.interfaceId = interfaceId;
        dbSts = clib_get((I_S32)INTERFACEDAO_ID, MSC_MET_GET,
                    (I_PVoid)&(aifIndex),sizeof(AifInterfaceTableIndices),(I_PVoid*)&interfaceTblPtr,(I_S16 *)&rowSize,&rowCount);
        if(dbSts == CLIB_SUCCESS)
         {
           if ( rowCount != 1)
             {
               free(interfaceTblPtr);
                return -1;
             } 
                    /*  PointCode */
             trunkCicConfigPtr->pointCode = (unsigned int)interfaceTblPtr->dpc;
                   /*  InterfaceType */
             trunkCicConfigPtr->interfaceType = interfaceTblPtr->interfaceType;
                  /*  InterfaceId */
             trunkCicConfigPtr->interfaceId = interfaceTblPtr->interfaceId;
             free(interfaceTblPtr);
             return dbSts;  // SUCCESS
         }
         else
            return dbSts;
}
/********************End Of File *******************************************/
