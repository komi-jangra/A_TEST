/*se ts=2************************************File Source*****
File Name		:	  sksdb_trunkcicconfig.c 
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

Output        :  
*************************************************************/
I_S32 GetDstStreamTsConfigDataWithTrunkAndTimeslot( I_U8 *timeSlot, I_U8 dst_trunk_no, I_U8 dsTimeSlot)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *TrunkStreamMapTblPtr=NULL;
   //TrunkStrmMapTbl    *TrunkStreamMapPtr = NULL;
   E1StreamMapTableApi    *TrunkStreamMapPtr = NULL;
   //KeyTrunkNumTrunkTs keyTrunkNumTrunkTs;
   E1StreamMapTableIndices keyTrunkNumTrunkTs;
   keyTrunkNumTrunkTs.e1Num = dst_trunk_no;
   keyTrunkNumTrunkTs.e1Ts = dsTimeSlot;

   dbSts = clib_get((I_S32)SCM_DAO_E1STREAMMAPTABLE, SCM_MET_GET_E1STREAMMAPTABLE, (I_PVoid)&keyTrunkNumTrunkTs, 
                     sizeof(E1StreamMapTableIndices),(I_PVoid*)&TrunkStreamMapTblPtr,(I_S16 *)&rowSize,&rowCount);
     
  SCM_printf (SCM_DEBUG, "dbSts: %d, ....Db call dump", dbSts);
  if(dbSts != CLIB_SUCCESS)
     {
       	return dbSts;
     } 

  if ( rowCount != 1)
     {
       free(TrunkStreamMapTblPtr);
       return -1;
     }  
   SCM_DUMP(0, sizeof(E1StreamMapTableApi), (unsigned char* )TrunkStreamMapTblPtr, 15);
   TrunkStreamMapPtr = (E1StreamMapTableApi*)(TrunkStreamMapTblPtr); 
  /* DST TrunkNum &  time slot*/
   *timeSlot = (unsigned char)TrunkStreamMapPtr[0].strmTs;
   return dbSts; 
} 






/********************End Of File *******************************************/
