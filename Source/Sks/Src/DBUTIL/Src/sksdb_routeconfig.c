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

Output        : I_U8 *OamScmSs7RouteConfig 
*************************************************************/
I_S32  GetSS7RouteConfigData(OamScmSs7RouteConfig **ss7RouteConfigPtrToPtr, I_U8 *count)
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0, i = 0;
   I_S32 dbSts;
   *count = 0;
   void *sS7RouteTblPtr=NULL;
   //SS7RouteTbl *sS7RoutePtr=NULL;
   Ss7RouteTableApi *sS7RoutePtr=NULL;
   OamScmSs7RouteConfig *ss7RouteConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SCM_DAO_SS7ROUTETABLE,
               (I_PVoid *)&sS7RouteTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   SCM_printf (SCM_DEBUG, "dbSts: %d, ....Db call dump", dbSts);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0, (rowCount * sizeof(Ss7RouteTableApi)), (unsigned char* )sS7RouteTblPtr, 15);
      *count = rowCount;
      ss7RouteConfigPtr = calloc (rowCount,sizeof(OamScmSs7RouteConfig));
      *ss7RouteConfigPtrToPtr = ss7RouteConfigPtr;
      while (rowCount)
      {
         sS7RoutePtr = (Ss7RouteTableApi*)(sS7RouteTblPtr + i*rowSize); 
         ss7RouteConfigPtr[i].destinationPointCode = sS7RoutePtr->dpc;
         ss7RouteConfigPtr[i].linkSetId = sS7RoutePtr->linksetID;
         ss7RouteConfigPtr[i].style = (unsigned char)sS7RoutePtr->style;
         ss7RouteConfigPtr[i].sio = (unsigned char)sS7RoutePtr->sio;
         ss7RouteConfigPtr[i].rssn = (unsigned char)sS7RoutePtr->rssn;
         ss7RouteConfigPtr[i].lssn = (unsigned char)sS7RoutePtr->lssn;
         ss7RouteConfigPtr[i].sstTestOn = (unsigned char)sS7RoutePtr->sstTestOn;
         ss7RouteConfigPtr[i].networkIndicator = (unsigned char)sS7RoutePtr->networkIndicator;
         rowCount--;
         i++;

      }
         free(sS7RouteTblPtr);
         return 0;
   }
   else
   {
     return dbSts;
   }

}



/********************End Of File *******************************************/
