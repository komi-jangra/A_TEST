#include <oamcfg_includes.h>

#define BSC_API_SET_NSVCDATASTRUCT 1

extern int gTestCaseCompleted;
//extern objectState gBssState;

void nsvcObjHandler1()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 1: NSVC Object Handler: Locked\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 0; /*Locked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 1: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 0; /*Locked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 1: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 1: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();
      sleep(1);
      nsvcDataStructBuff.nsvcState    = locked;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 0;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);

      //gBssState = unlocked;     
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_UNLOCK_BSS);
      nsvcTableApiPtr->adminState = 1; /*Unlocked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
         case OAMS_CFG_AFH_ALARM_IND:
         {
            printf("Received OAMS_CFG_AFH_ALARM_IND\n");
            gTestCaseCompleted = 1;
            break;
         }
         case OAMS_CFG_GRHM_SWITCH_CONNECT:
         {
            printf("Received OAMS_CFG_GRHM_SWITCH_CONNECT\n");
            break;
         }
         case OAMS_CFG_NSVCH_UNLOCK_REQ:
         {
            printf("Received OAMS_CFG_NSVCH_UNLOCK_REQ\n");
            OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
            oamsCfgNsvchUnlockReqPtr = (OamsCfgNsvchUnlockReq*)gCfgMsgBuf;
            cfgStubSendNsvchCfgUnlockResp(oamsCfgNsvchUnlockReqPtr->nsvcId);
            break;
         }

      }      
   }
}


void nsvcObjHandler2()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 2: NSVC Object Handler: Locked\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 0; /*Locked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 2: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 0; /*Locked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 2: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 2: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();
      setBssPsPreConfigTable();

      sleep(1);
      nsvcDataStructBuff.nsvcState    = locked;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 0;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 0; /*locked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}



void nsvcObjHandler3()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 3: NSVC Object Handler: Locked\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 0; /*Locked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 3: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 0; /*Locked*/
         nsvcTableApiPtr->frChnId      = 1;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 3: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 3: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();

      sleep(1);
      nsvcDataStructBuff.nsvcState    = locked;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 0;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 0; /*locked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_DEL_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}



void nsvcObjHandler4()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 4: NSVC Object Handler: UnlockedOrEnableInProgress\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Locked*/
         nsvcTableApiPtr->frChnId      =  OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 4: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 1; /*Locked*/
         nsvcTableApiPtr->frChnId      =  OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 4: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 4: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();

      sleep(1);
      nsvcDataStructBuff.nsvcState    = unlockOrEnableInProgress;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 0;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 0; /*Unlocked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}


void nsvcObjHandler5()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 5: NSVC Object Handler: UnlockOrEnableInProgress\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 0; /*Locked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 5: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 0; /*Locked*/
         nsvcTableApiPtr->frChnId      = 1;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 5: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 5: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */

      sleep(1);
      nsvcDataStructBuff.nsvcState    = unlockOrEnableInProgress;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 0;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 0; /*locked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_DEL_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}



void nsvcObjHandler6()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 6: NSVC Object Handler: Unlocked Disabled\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 6: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 6: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 6: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */

      sleep(1);
      nsvcDataStructBuff.nsvcState    = unlockedDisabled;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 1;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 0; /*locked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}



void nsvcObjHandler7()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 7: NSVC Object Handler: Unlocked-Disabled\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Unlocked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 7: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = 1;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 7: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 7: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */

      sleep(1);
      nsvcDataStructBuff.nsvcState    = unlockedDisabled;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 1;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 1; /*Unlocked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}


void nsvcObjHandler8()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 8: NSVC Object Handler: Locked\n");
      nsvcTableIndicesBuff.nsvcId = 1;
      //deleteNsvcTable(&nsvcTableIndicesBuff);
      //nsvcTableIndicesBuff.nsvcId = 1;
      //deleteNsvcTable(&nsvcTableIndicesBuff);
      //nsvcTableIndicesBuff.nsvcId = 2;
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Unlocked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 8: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = 1;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 8: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 8: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */

      sleep(1);
      nsvcDataStructBuff.nsvcState    = unlockedDisabled;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 1;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 1; /*unlocked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_DEL_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}


void nsvcObjHandler9()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 9: NSVC Object Handler: Unlocked-Enabled\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 9: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 9: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 9: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();

      sleep(1);
      nsvcDataStructBuff.nsvcState    = unlockedEnabled;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 1;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_UNLOCK_BSS);
      nsvcTableApiPtr->adminState = 0; /*locked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
         case OAMS_CFG_NSVCH_LOCK_REQ:
         {
            printf("Received OAMS_CFG_NSVCH_LOCK_REQ\n");
            OamsCfgNsvchLockReq *oamsCfgNsvchLockReqPtr;
            oamsCfgNsvchLockReqPtr = (OamsCfgNsvchLockReq*)gCfgMsgBuf;
            cfgStubSendNsvchCfgLockResp(oamsCfgNsvchLockReqPtr->nsvcId);
            break;
         }
         case OAMS_CFG_GRHM_SWITCH_DISCONNECT:
         {
           printf("Received OAMS_CFG_GRHM_SWITCH_DISCONNECT\n");
           break;
         }
         case OAMS_CFG_AFH_ALARM_IND:
         {
            printf("Received OAMS_CFG_AFH_ALARM_IND\n");
            gTestCaseCompleted = 1;
            break;
         }

      }      
   }
}


void nsvcObjHandler10()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 10: NSVC Object Handler: Unlocked-Enabled\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Unlocked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 10: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = 1;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 10: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 10: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();

      sleep(1);
      nsvcDataStructBuff.nsvcState    = unlockedEnabled;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 1;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 1; /*Unlocked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}


void nsvcObjHandler11()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 11: NSVC Object Handler: Unlocked-Enabled\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Unlocked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 11: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 11: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 11: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();

      sleep(1);
      nsvcDataStructBuff.nsvcState    = unlockedEnabled;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 1;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 1; /*Unlocked*/
//      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE);
     SysAlarm sysAlarm;
     sysAlarm.sysalarmId = 1;
     sysAlarm.key1 = nsvcDataStructBuff.nsvcId; 
     cfgStubSendNsvchCfgAlarmInd(sysAlarm);
     sysAlarm.sysalarmId = 3;
     cfgStubSendPsscmCfgAlarmInd(sysAlarm);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_AFH_ALARM_IND:
         {
            printf("Received OAMS_CFG_AFH_ALARM_IND\n");
            testInitiation--;
            if (testInitiation == -2)
               gTestCaseCompleted = 1;
            break;
         }

      }      
   }
}

void nsvcObjHandler12()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 12: NSVC Object Handler: Locked\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 0; /*Locked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 12: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 0; /*Locked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 12: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 12: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();
      sleep(1);
      nsvcDataStructBuff.nsvcState    = locked;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 0;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);

      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_LOCK_BSS);
      nsvcTableApiPtr->adminState = 1; /*Unlocked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
         case OAMS_CFG_AFH_ALARM_IND:
         {
            printf("Received OAMS_CFG_AFH_ALARM_IND\n");
            break;
         }
      }      
   }
}

void nsvcObjHandler13()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 13: NSVC Object Handler: Unlocked-Enabled\n");
      nsvcTableIndicesBuff.nsvcId = 3;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Unlocked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 13: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 3;
         nsvcTableApiPtr->adminState   = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 13: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 13: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();

      sleep(1);
      nsvcDataStructBuff.nsvcState    = unlockedEnabled;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 3;
      //nsvcDataStructBuff.adminState   = 1;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 1; /*Unlocked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_DEL_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}


void nsvcObjHandler14()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 14: NSVC Object Handler: Unlocked Disabled\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Unlocked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 14: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 14: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 14: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();

      sleep(1);
      nsvcDataStructBuff.nsvcState    = lockeOrDisableInProgress;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 1;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 0; /*locked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}


void nsvcObjHandler15()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 15: NSVC Object Handler: Unlocked Disabled\n");
      nsvcTableIndicesBuff.nsvcId = 1;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Unlocked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 15: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 1;
         nsvcTableApiPtr->adminState   = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 15: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 15: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */
      setFrLinkTable();
      setGbInterfaceTable();

      sleep(1);
      nsvcDataStructBuff.nsvcState    = lockeOrDisableInProgress;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 1;
      //nsvcDataStructBuff.adminState   = 1;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 0; /*locked*/
      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_DEL_NSVCTABLE); 

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Nack Receieved \n");
            }
            else
            {
               printf("Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }
      }      
   }
}


void nsvcObjHandler16()
{
   static int testInitiation =1;
   NsvcTableIndices      nsvcTableIndicesBuff;
   NsvcTableApi          *nsvcTableApiPtr;
   SysAlarm              *sysAlarm;
   BssTableApi           *bssTableApiPtr;
   OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
   OamsCfgNsvchLockReq   *oamsCfgNsvchLockReqPtr;
   NsvcDataStruct        nsvcDataStructBuff;
   I_U32 rowCount;
   I_U16 rowSize;

   if (testInitiation)
   {
      testInitiation = 0;
      printf("Scenario 16: NSVC Object Handler \n");
      nsvcTableIndicesBuff.nsvcId = 3;
 
      if (getNsvcTable(&nsvcTableIndicesBuff, &nsvcTableApiPtr) == CLIB_SUCCESS)
      {
         nsvcTableApiPtr->adminState = 1; /*Unlocked*/
         updateNsvcTable(nsvcTableApiPtr);
         printf("Scenario 16: Update Nsvc Table Successfull::NSVC ID : %d", nsvcTableIndicesBuff.nsvcId);
      }
      else
      {
         nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
         nsvcTableApiPtr->nsvcId       = 3;
         nsvcTableApiPtr->adminState   = 1; /*Unlocked*/
         nsvcTableApiPtr->frChnId      = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci         = 20; 
         if (insertNsvcTable(nsvcTableApiPtr) == CLIB_SUCCESS)
         {
            printf("Scenario 16: Insert Nsvc Table Successfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
         else
         {
            printf("Scenario 16: Insert Nsvc Table Unsuccessfull:: NSVC Id : %d", nsvcTableApiPtr->nsvcId);
         }
      }

      /*Here we need to add entries to different tables */

      sleep(1);
      nsvcDataStructBuff.nsvcState    = lockeOrDisableInProgress;/*As required*/ 
      nsvcDataStructBuff.availability = FALSE;
      nsvcDataStructBuff.nsvcId       = 3;
      //nsvcDataStructBuff.adminState   = 1;
      nsvcDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&nsvcDataStructBuff, sizeof(NsvcDataStruct), BSC_API_SET_NSVCDATASTRUCT);
     
      nsvcTableApiPtr->adminState = 1; /*Unlocked*/
//      cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE);
     SysAlarm sysAlarm;
     sysAlarm.sysalarmId = 1;
     sysAlarm.key1 = nsvcDataStructBuff.nsvcId; 
     cfgStubSendNsvchCfgAlarmInd(sysAlarm);
     sysAlarm.sysalarmId = 3;
     cfgStubSendPsscmCfgAlarmInd(sysAlarm);
     sysAlarm.sysalarmId = 1182;
     cfgStubSendPsscmCfgAlarmInd(sysAlarm);
     sysAlarm.sysalarmId = 1183;
     cfgStubSendPsscmCfgAlarmInd(sysAlarm);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_AFH_ALARM_IND:
         {
            printf("Received OAMS_CFG_AFH_ALARM_IND\n");
            testInitiation--;
            if (testInitiation == -2)
               gTestCaseCompleted = 1;
            break;
         }

      }      
   }
}
