/*se ts=2************************************File Source*****
File Name		:	  sksdb_initconfig.c 
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
I_S32  GetInitConfigData(OamScmSs7StackConfig  *initConfigPtr) 
{
   I_S16 rowSize = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void *initConfigTblPtr=NULL;
  Ss7StackConfigTableApi *initConfigTPtr;
  //Ss7StackConfigTbl *initConfigTPtr;
  dbSts = clib_dump((I_S32)SCM_DAO_SS7STACKCONFIGTABLE,
               (I_PVoid *)&initConfigTblPtr,
                 (short *)&rowSize,&rowCount);
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowSize: %d, ....Db call dump", dbSts, rowSize);

   if(dbSts == DB_SUCCESS)
   {
      if(rowCount > 0)
      {
        SCM_DUMP(0, sizeof(Ss7StackConfigTableApi), (unsigned char* )initConfigTblPtr, 15);
        initConfigTPtr = (Ss7StackConfigTableApi*)initConfigTblPtr;
        /*  Family */
         initConfigPtr->family = (unsigned char)initConfigTPtr->sksCommonfamily;
        /*  SelfPointCode */
         initConfigPtr->selfPointCode = initConfigTPtr->sksCommonopc;
        /*  AlaramLevel */
         initConfigPtr->alarmLevel = initConfigTPtr->alarmLevel;
         return 0;
      }
      else
      {
       free(initConfigTblPtr);
       return dbSts;
      }/*else rowCount*/
   }
   else
   {
     return dbSts;
   }
}/*GetinitConfigData*/



/********************End Of File *******************************************/
