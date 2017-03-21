#include <oamcfg_includes.h>

extern int gTestCaseCompleted ;
extern BssTableApi gBssTableApiBuff;

I_U16 e1Id = 1;
I_U16 frChnId = 1;
I_U16 nsvcId = 1;


void CfgE1ObjHndlr1()
{
   static int testInitiation =1;

   TrunkTableApi *trunkTableApiPtr = NULL;
   TrunkTableIndices trunkTableIndicesBuff;


   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      removeFromE1Table(e1Id);
      insertIntoE1Table(e1Id, LOCKED);
     
      removeAllFromFrLinkTable();
      removeAllFromNsvcTable();
      removeAllFromFrLinkExtE1TsMccE1TsMapTable();

      insertIntoFrLinkTable(frChnId, e1Id);
      insertIntoNsvcTable(frChnId, nsvcId, LOCKED);
      insertIntoFrLinkExtE1TsMccE1TsMapTable(frChnId, e1Id, 2);
 

      /* Now Send BSS UNLOCK to the CFG message */
      //gBssTableApiBuff.adminState = UNLOCKED;  
      //cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
      CellTableApi cellTableApiBuff;
      cfgStubSendCmMessage(&cellTableApiBuff, sizeof(CellTableApi), BSC_API_UNLOCK_BSS);
      trunkTableIndicesBuff.e1Num = e1Id; 
      if ( getTrunkTable(&trunkTableIndicesBuff, &trunkTableApiPtr) == CLIB_SUCCESS ) 
      { 
         trunkTableApiPtr->adminState = UNLOCKED; 
         cfgStubSendCmMessage(trunkTableApiPtr,sizeof(TrunkTableApi),BSC_API_SET_TRUNKPERTABLE); 
      } 
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
         {
            printf("Test Case 1 :Received Ack Successfully\n");
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Test Case 1:Nack Receieved \n");
            }
            else
            {
               printf("Test Case 1:Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }  
      }
   }
}

void CfgE1ObjHndlr2()
{
   static int testInitiation =1;

   TrunkTableApi *trunkTableApiPtr = NULL;
   TrunkTableIndices trunkTableIndicesBuff;


   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      removeFromE1Table(e1Id);
      insertIntoE1Table(e1Id, LOCKED);
     
      removeAllFromFrLinkTable();
      removeAllFromNsvcTable();
      removeAllFromFrLinkExtE1TsMccE1TsMapTable();

      insertIntoFrLinkTable(frChnId, e1Id);
      insertIntoNsvcTable(frChnId, nsvcId, LOCKED);
      insertIntoFrLinkExtE1TsMccE1TsMapTable(frChnId, e1Id, 2);
 

      /* Now Send BSS LOCK to the CFG message */
      //gBssTableApiBuff.adminState = LOCKED;  
      //cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

      CellTableApi cellTableApiBuff;
      cfgStubSendCmMessage(&cellTableApiBuff, sizeof(CellTableApi), BSC_API_LOCK_BSS);
      trunkTableIndicesBuff.e1Num = e1Id; 
      if ( getTrunkTable(&trunkTableIndicesBuff, &trunkTableApiPtr) == CLIB_SUCCESS ) 
      { 
         trunkTableApiPtr->adminState = UNLOCKED; 
         cfgStubSendCmMessage(trunkTableApiPtr,sizeof(TrunkTableApi),BSC_API_SET_TRUNKPERTABLE); 
      } 
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
         {
            printf("Test Case 1 :Received Ack Successfully\n");
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Test Case 1:Nack Receieved \n");
            }
            else
            {
               printf("Test Case 1:Ack Receieved \n");
            }
            gTestCaseCompleted = 1; 
            break;
         }  
      }
   }
}


void CfgE1ObjHndlr3()
{
   static int testInitiation =1;

   TrunkTableApi *trunkTableApiPtr = NULL;
   TrunkTableIndices trunkTableIndicesBuff;


   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      removeFromE1Table(e1Id);
      insertIntoE1Table(e1Id, UNLOCKED);
     
      removeAllFromFrLinkTable();
      removeAllFromNsvcTable();
      removeAllFromFrLinkExtE1TsMccE1TsMapTable();

      insertIntoFrLinkTable(frChnId, e1Id);
      insertIntoNsvcTable(frChnId, nsvcId, LOCKED);
      insertIntoFrLinkExtE1TsMccE1TsMapTable(frChnId, e1Id, 2);
 

      /* Now Send BSS UNLOCK to the CFG message */
      CellTableApi cellTableApiBuff;
      cfgStubSendCmMessage(&cellTableApiBuff, sizeof(CellTableApi), BSC_API_UNLOCK_BSS);
//      gBssTableApiBuff.adminState = UNLOCKED;  
//      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

      trunkTableIndicesBuff.e1Num = e1Id; 

      if ( getTrunkTable(&trunkTableIndicesBuff, &trunkTableApiPtr) == CLIB_SUCCESS ) 
      { 
         trunkTableApiPtr->adminState = LOCKED; 
         cfgStubSendCmMessage(trunkTableApiPtr,sizeof(TrunkTableApi),BSC_API_SET_TRUNKPERTABLE); 
      } 
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
         {
            printf("Test Case 1 :Received Ack Successfully\n");
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Test Case 1:Nack Receieved \n");
            }
            else
            {
               printf("Test Case 1:Ack Receieved \n");
            }
            gTestCaseCompleted = 1;
            break;
         }  
      }
   }
}

void CfgE1ObjHndlr4()
{
   static int testInitiation =1;

   TrunkTableApi *trunkTableApiPtr = NULL;
   TrunkTableIndices trunkTableIndicesBuff;

   void *ptr = (void*)malloc(sizeof(void));
   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      removeFromE1Table(e1Id);
      insertIntoE1Table(e1Id, UNLOCKED);
     
      removeAllFromFrLinkTable();
      removeAllFromNsvcTable();
      removeAllFromFrLinkExtE1TsMccE1TsMapTable();

      insertIntoFrLinkTable(frChnId, e1Id);
      insertIntoNsvcTable(frChnId, nsvcId, LOCKED);
      insertIntoFrLinkExtE1TsMccE1TsMapTable(frChnId, e1Id, 2);
 

      /* Now Send BSS LOCK to the CFG message */
      CellTableApi cellTableApiBuff;
      cfgStubSendCmMessage(&cellTableApiBuff, sizeof(CellTableApi), BSC_API_LOCK_BSS);
      //gBssTableApiBuff.adminState = LOCKED;  
      //cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

      trunkTableIndicesBuff.e1Num = e1Id; 
      if ( getTrunkPerTable(&trunkTableIndicesBuff, &trunkTableApiPtr) == CLIB_SUCCESS ) 
      { 
         trunkTableApiPtr->adminState = LOCKED; 
         cfgStubSendCmMessage(trunkTableApiPtr,sizeof(TrunkTableApi),BSC_API_SET_TRUNKPERTABLE); 
      } 
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
         {
            printf("Test Case 1 :Received Ack Successfully\n");
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("Test Case 1:Nack Receieved \n");
            }
            else
            {
               printf("Test Case 1:Ack Receieved \n");
            }
            gTestCaseCompleted = 1; 
            break;
         }  
      }
   }
}

void setUsageTypeInE1Table(I_U16 e1Id, I_U32 usageType)
{
   TrunkTableApi trunkTableApiBuff;
   trunkTableApiBuff.e1Num = e1Id;
   trunkTableApiBuff.usageType = usageType;
   if(CLIB_SUCCESS == updateTrunkTable(&trunkTableApiBuff))
   {
     printf("\nUpdate into Trunk Table Successful"); 
   }
   else
   {
     printf("\nUpdate into Trunk Table Unsuccessful"); 
   }
}
void insertIntoE1Table( I_U16 e1Id, I_U32 adminState)
{
   
   TrunkTableApi trunkTableApiBuff;
   E1NonPerTableApi e1NonPerTableApiBuff;

   trunkTableApiBuff.e1Num = e1Id;
   trunkTableApiBuff.adminState = adminState;
   trunkTableApiBuff.usageType = SYS_E1_USAGE_AIF;
   trunkTableApiBuff.usingEntity = 0;
   trunkTableApiBuff.trunkPortId = 1;
   trunkTableApiBuff.mapAction = DEFAULT_ACTION;
   trunkTableApiBuff.e1Category = EXTERNAL_E1;
   if(CLIB_SUCCESS == insertTrunkTable(&trunkTableApiBuff))
   {
      printf("Insert Trunk Table Successfull\n");
      e1NonPerTableApiBuff.e1Num = e1Id;
      e1NonPerTableApiBuff.oprState = DISABLED;
      if(CLIB_SUCCESS == insertE1NonPerTable(&e1NonPerTableApiBuff))
      {
         printf("Insert Trunk Status Table Successfull\n");
      }
      else
      {
         printf("Insert Trunk Status Table Unsuccessful\n");
      }
   }
   else
   {
      printf("Insert Trunk Table Unsuccessful\n");
   }
}

void removeFromE1Table(I_U16 e1Id)
{
   TrunkTableIndices trunkTableIndicesBuff;
   E1NonPerTableIndices e1NonPerTableIndicesBuff;

   trunkTableIndicesBuff.e1Num = e1Id;
   e1NonPerTableIndicesBuff.e1Num = e1Id;

   if(CLIB_SUCCESS == deleteTrunkTable(&trunkTableIndicesBuff))
   {
      printf("Delete trunk Table successful\n");
      if(CLIB_SUCCESS == deleteE1NonPerTable(&e1NonPerTableIndicesBuff))
      {
         printf("Delete Trunk Status Table successful\n");
      }
      else
      {
         printf("Delete Trunk Status Table Unsuccessful\n");
      }
   }
   else
   {
      printf("Delete Trunk Table Unsuccessful\n");
   }
}
