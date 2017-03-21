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
I_S32 GetTrunkConfigDataWithTrunkAndTimeslot(OamScmLinkConfig*, I_U16, I_U8);

I_S32  GetLinkConfigData(OamScmLinkConfig  **linkConfigPtrToPtr, I_U8 *count)
 {
   I_S16 rowSize = 0;
   I_S16 i = 0, t =0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   *count = 0;
   void       *linkTblPtr=NULL;
   //LinkTbl    *linkPtr=NULL;
   LinkTableApi *linkPtr=NULL;
   OamScmLinkConfig *linkConfigPtr=NULL;

   dbSts = clib_dump((I_S32)SCM_DAO_LINKTABLE,
               (I_PVoid *)&linkTblPtr,
                 (I_S16 *)&rowSize,&rowCount);
   SCM_printf (SCM_DEBUG, "dbSts: %d, ....Db call dump", dbSts);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0, (rowCount * sizeof(LinkTableApi)), (unsigned char* )linkTblPtr, 15);
      //*count = rowCount;
      linkConfigPtr = calloc (rowCount,sizeof(OamScmLinkConfig));
      *linkConfigPtrToPtr = linkConfigPtr; 
      while (rowCount)
      {
         linkPtr = (LinkTableApi*)(linkTblPtr + i*rowSize);
         i++;
        /*  LinkId */
         linkConfigPtr[t].linkId = linkPtr->linkId;
        /*  LinkSetId */
         linkConfigPtr[t].linkSetId = linkPtr->linksetID;
        /*  TrunkNum */
        // linkConfigPtr[i].trunkNum = linkPtr[0].trunkNum;
        /*  TimeSlot */
         //linkConfigPtr[i].timeSlot = linkPtr[0].timeSlot;
          
        /*  CardNum */
         linkConfigPtr[t].cardNum = linkPtr->cardNum;
        /*  crcFlag */
         linkConfigPtr[t].crcFlag = (unsigned char)linkPtr->crcFlag;
         dbSts= GetTrunkConfigDataWithTrunkAndTimeslot(&linkConfigPtr[t],
                                              linkPtr->e1Num, linkPtr->timeSlot);
         if((dbSts != DB_SUCCESS) && (i == rowCount) && (t == 0))
           {
             free(linkTblPtr);
             return dbSts;
           }
         else
           {
           if(dbSts == DB_SUCCESS)
            {
              t++;
              *count = t;
              //return 0;
            }
           }
         rowCount--;
      }
       free(linkTblPtr);
       return 0;
   }
   else
   {
     return dbSts;  
   } 

}


I_S32 GetTrunkConfigDataWithTrunkAndTimeslot(OamScmLinkConfig *linkConfigPtr,I_U16 trunkNum, I_U8 timeSlot)
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *LinkResourceTblPtr=NULL;
   void       *tmpptr=NULL;
   //MccLinkResourceTbl    *MccLinkResourcePtr;
   //ExtTrNumTrTs keySrcTrunkNumTs;
   //keySrcTrunkNumTs.extTrunkNum = trunkNum;
   //keySrcTrunkNumTs.extTrunkTs   = timeSlot;
   MccLinkResourceTableTerIndices mccLinkTerIndex;
   MccLinkResourceTableApi *mccLinkTablePtr = NULL;
   mccLinkTerIndex.extTrunkNum =  trunkNum;
   mccLinkTerIndex.extTrunkTs  =  timeSlot;
   dbSts = clib_get((I_S32)SCM_DAO_MCCLINKRESOURCETABLE, GET_EXTTRUNKNUM_EXTTRUNKTS, 
                    (I_PVoid)&mccLinkTerIndex, sizeof(MccLinkResourceTableTerIndices), 
                    (I_PVoid*)&mccLinkTablePtr,(I_S16 *)&rowSize,&rowCount);
 
  if(dbSts != CLIB_SUCCESS)
   {
     return dbSts;
   } 

  /*if ( rowCount != 1)
     {
       free(LinkResourceTblPtr);
       return -1;
     }*/
  
   //MccLinkResourcePtr = (MccLinkResourceTableApi*)(mccLinkTablePtr); 
  /* DST TrunkNum &  time slot*/
   linkConfigPtr->trunkNum = (unsigned short)mccLinkTablePtr->mccTrunkNum;
   linkConfigPtr->timeSlot = (unsigned char)mccLinkTablePtr->mccTrunkTs;
   free(mccLinkTablePtr);
   return dbSts; 
} 






/********************End Of File *******************************************/
