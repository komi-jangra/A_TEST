#include <oamcfg_includes.h>

#define BSC_API_SET_CELLDATASTRUCT 0
extern int gTestCaseCompleted;

BssTableApi  gBssTableApiBuff;

void nsvcTableRangeChkTest()
{
   static int testInitiation =1;
  
   NsvcTableApi *nsvcTableApiPtr;
   NsvcTableIndices nsvcTableIndicesBuff;
   //printf("-------------%s :: Testing nsvcTableRangeChk--------------- \n");

   if (testInitiation != 1)
   {
     switch (((SysHdr*) gCfgMsgBuf)->msgType)
     {
         case CM_API_APP_RESPONSE :
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("nsvcTableRangeChk:TestCase %d:Nack Receieved\n \n",testInitiation-1);
            }
            else
            {
               printf("nsvcTableRangeChk:TestCase %d:Ack Receieved\n \n",testInitiation-1);
            }
         }
         break;
      }
   }
   else
   {
      setFrLinkTable();
      setBssPsPreConfigTable();
      setGbInterfaceTable();
   }
   removeNsvcTable(1000);
   removeNsvcStatusTable(1000);
   removeNsvcConnIdMapTable(1000);
   nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
   switch (testInitiation)
   {
      case 1:
      {
         printf("-----%s :: Testing Boundary Condition for dlci-----\n",__FUNCTION__);
         nsvcTableApiPtr->nsvcId     = 1000;
         nsvcTableApiPtr->adminState = LOCKED;
         nsvcTableApiPtr->frChnId    = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci       = 16;
         cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi),BSC_API_SET_NSVCTABLE);
         testInitiation++;
         break;
      }
      case 2:
      {
         printf("-----%s :: Testing Range Check for dlci-----\n",__FUNCTION__);
         nsvcTableApiPtr->nsvcId     = 1000;
         nsvcTableApiPtr->adminState = LOCKED;
         nsvcTableApiPtr->frChnId    = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci       = 15;
         cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi),BSC_API_SET_NSVCTABLE);
         testInitiation++;
         break;
      }
      case 3:
      {
         printf("-----%s :: Testing Boundary Condition for dlci-----\n",__FUNCTION__);
         nsvcTableApiPtr->nsvcId     = 1000;
         nsvcTableApiPtr->adminState = LOCKED;
         nsvcTableApiPtr->frChnId    = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci       = 991;
         cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi),BSC_API_SET_NSVCTABLE);
         testInitiation++;
         break;
      }
      case 4:
      {
         printf("-----%s :: Testing Range Check for dlci-----\n",__FUNCTION__);
         nsvcTableApiPtr->nsvcId     = 1000;
         nsvcTableApiPtr->adminState = LOCKED;
         nsvcTableApiPtr->frChnId    = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
         nsvcTableApiPtr->dlci       = 992;
         cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi),BSC_API_SET_NSVCTABLE);
         testInitiation++;
         break;
      }
      case 5:
      {
         printf("-----%s :: Testing Sunny-Day condition for NsvcTableRangeChk-----\n",__FUNCTION__);
         nsvcTableApiPtr->nsvcId     = 1000;
         nsvcTableApiPtr->adminState = LOCKED;
         nsvcTableApiPtr->frChnId    = OAMS_CFG_FR_CHN_ID_MAX_VALUE -2;
         nsvcTableApiPtr->dlci       = 17;
         cfgStubSendCmMessage(nsvcTableApiPtr,sizeof(NsvcTableApi),BSC_API_SET_NSVCTABLE);
         testInitiation++;
         break;
      }
      default:
      {
         testInitiation = 1;
         gTestCaseCompleted = 1;
      }
   }
}

void frLinkTableRangeChkTest()
{
   static int testInitiation =1;

   FrLinkTableApi *frLinkTableApiPtr;
   FrLinkTableIndices frLinkTableIndicesBuff;

   if (testInitiation != 1)
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("FrLinkTableRangeChk:TestCase %d:Nack Receieved\n \n",testInitiation-1);
            }
            else
            {
               printf("FrLinkTableRangeChk:TestCase %d:Ack Receieved\n \n",testInitiation-1);
            }
         }
         break;
      }
   }
   else
   {
      setBssPsPreConfigTable();
      setE1PerTable();
      
   }
   frLinkTableApiPtr = (FrLinkTableApi*)calloc(1, sizeof(FrLinkTableApi));
   switch (testInitiation)
   {
      case 1:
      {
         printf("-----%s :: Testing Boundary Condition for FrChnId-----\n",__FUNCTION__);
         frLinkTableApiPtr->frChnId       = 1;
         frLinkTableApiPtr->e1Id          = 1;
         frLinkTableApiPtr->startTs       = 1;
         frLinkTableApiPtr->numTs         = 2;
         removeFrLinkTable(frLinkTableApiPtr->frChnId);
         removeFrLinkStatusTable(frLinkTableApiPtr->frChnId);
         cfgStubSendCmMessage(frLinkTableApiPtr,sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 2:
      {
         printf("-----%s :: Testing Range Check for FrChnId-----\n",__FUNCTION__);
         frLinkTableApiPtr->frChnId       = 0;
         frLinkTableApiPtr->e1Id          = 1;
         frLinkTableApiPtr->startTs       = 1;
         frLinkTableApiPtr->numTs         = 2;
         removeFrLinkTable(frLinkTableApiPtr->frChnId);
         removeFrLinkStatusTable(frLinkTableApiPtr->frChnId);
         cfgStubSendCmMessage(frLinkTableApiPtr,sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 3:
      {
         printf("-----%s :: Testing Boundary Condition for FrChnId-----\n",__FUNCTION__);
         frLinkTableApiPtr->frChnId       = 16;
         frLinkTableApiPtr->e1Id          = 1;
         frLinkTableApiPtr->startTs       = 1;
         frLinkTableApiPtr->numTs         = 2;
         removeFrLinkTable(frLinkTableApiPtr->frChnId);
         removeFrLinkStatusTable(frLinkTableApiPtr->frChnId);
         cfgStubSendCmMessage(frLinkTableApiPtr,sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 4:
      {
         printf("-----%s :: Testing Range Check for FrChnId-----\n",__FUNCTION__);
         frLinkTableApiPtr->frChnId       = 17;
         frLinkTableApiPtr->e1Id          = 1;
         frLinkTableApiPtr->startTs       = 1;
         frLinkTableApiPtr->numTs         = 2;
         removeFrLinkTable(frLinkTableApiPtr->frChnId);
         removeFrLinkStatusTable(frLinkTableApiPtr->frChnId);
         cfgStubSendCmMessage(frLinkTableApiPtr,sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 5:
      {
         printf("-----%s :: Testing Boundary Condition for StartTs-----\n",__FUNCTION__);
         frLinkTableApiPtr->frChnId       = 1;//12;
         frLinkTableApiPtr->e1Id          = 1;
         frLinkTableApiPtr->startTs       = 0;
         frLinkTableApiPtr->numTs         = 2;
         removeFrLinkTable(frLinkTableApiPtr->frChnId);
         removeFrLinkStatusTable(frLinkTableApiPtr->frChnId);
         cfgStubSendCmMessage(frLinkTableApiPtr,sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 6:
      {
         printf("-----%s :: Testing Range check for StartTs and numTs-----\n",__FUNCTION__);
         frLinkTableApiPtr->frChnId       = 1;//12;
         frLinkTableApiPtr->e1Id          = 1;
         frLinkTableApiPtr->startTs       = 10;
         frLinkTableApiPtr->numTs         = 21;
         removeFrLinkTable(frLinkTableApiPtr->frChnId);
         removeFrLinkStatusTable(frLinkTableApiPtr->frChnId);
         cfgStubSendCmMessage(frLinkTableApiPtr,sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 7:
      {
         printf("-----%s :: Testing Range check for StartTs and numTs-----\n",__FUNCTION__);
         frLinkTableApiPtr->frChnId       = 1;//12;
         frLinkTableApiPtr->e1Id          = 1;
         frLinkTableApiPtr->startTs       = 10;
         frLinkTableApiPtr->numTs         = 22;
         removeFrLinkTable(frLinkTableApiPtr->frChnId);
         removeFrLinkStatusTable(frLinkTableApiPtr->frChnId);
         cfgStubSendCmMessage(frLinkTableApiPtr,sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 8:
      {
         printf("-----%s :: Testing Sunny-Day Condition for FrLinkTableRangeChk-----\n",__FUNCTION__);
         frLinkTableApiPtr->frChnId       = 1;//12;
         frLinkTableApiPtr->e1Id          = 1;
         frLinkTableApiPtr->startTs       = 10;
         frLinkTableApiPtr->numTs         = 2;
         removeFrLinkTable(frLinkTableApiPtr->frChnId);
         removeFrLinkStatusTable(frLinkTableApiPtr->frChnId);
         cfgStubSendCmMessage(frLinkTableApiPtr,sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      default:
      {
         testInitiation = 1;
         gTestCaseCompleted = 1;
      }
   }
}

void repInfoTableRangeChkTest()
{
   static int testInitiation =1;

   RepInfoTableApi *repInfoTableApiPtr;

   if (testInitiation != 1)
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("repInfoTableRangeChk:TestCase %d:Nack Receieved\n \n",testInitiation-1);
            }
            else
            {
               printf("repInfoTableRangeChk:TestCase %d:Ack Receieved\n \n",testInitiation-1);
            }
         }
         break;
      }
   }
   else
   {
      setBssPsPreConfigTable();
      setGbInterfaceTable();
      insertIntoBssTable(1, LOCKED);
   }

   repInfoTableApiPtr = (RepInfoTableApi*)calloc(1, sizeof(RepInfoTableApi));
   switch (testInitiation)
   {
#if 0
      case 1:
      {
         printf("-----%s :: Testing Boundary Condition for FrChnId-----\n",__FUNCTION__);
         repInfoTableApiPtr->rep          = 255;
         //repInfoTableApiPtr->ipType       = 0;
         repInfoTableApiPtr->repPort      = 1;
         repInfoTableApiPtr->signallingWt = 0;
         repInfoTableApiPtr->dataWt       = 0;
         removeRepInfoTable(repInfoTableApiPtr->rep);
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 2:
      {
         printf("-----%s :: Testing Range Check for FrChnId-----\n",__FUNCTION__);
         repInfoTableApiPtr->rep          = 256;
         //repInfoTableApiPtr->ipType       = 0;
         repInfoTableApiPtr->repPort      = 1;
         repInfoTableApiPtr->signallingWt = 0;
         repInfoTableApiPtr->dataWt       = 0;
         removeRepInfoTable(repInfoTableApiPtr->rep);
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 3:
      {
         printf("-----%s :: Testing Range Check for ipType-----\n",__FUNCTION__);
         repInfoTableApiPtr->rep          = 100;
         //repInfoTableApiPtr->ipType       = 2;
         repInfoTableApiPtr->repPort      = 1;
         repInfoTableApiPtr->signallingWt = 0;
         repInfoTableApiPtr->dataWt       = 0;
         removeRepInfoTable(repInfoTableApiPtr->rep, repInfoTableApiPtr->ipType);
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
#endif
      case 1:
      {
         printf("-----%s :: Testing Boundary Condition for repPort-----\n",__FUNCTION__);
         strncpy(repInfoTableApiPtr->rep, "10.100.211.72", 25);         
         //repInfoTableApiPtr->ipType       = 1;
         repInfoTableApiPtr->repPort      = 1024;
         repInfoTableApiPtr->signallingWt = 0;
         repInfoTableApiPtr->dataWt       = 0;
         removeRepInfoTable(repInfoTableApiPtr->rep);
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 2:
      {
         printf("-----%s :: Testing Boundary Condition for repPort-----\n",__FUNCTION__);
         strncpy(repInfoTableApiPtr->rep, "10.100.211.72", 25);
         //repInfoTableApiPtr->ipType       = 1;
         repInfoTableApiPtr->repPort      = 65535;
         repInfoTableApiPtr->signallingWt = 0;
         repInfoTableApiPtr->dataWt       = 0;
         removeRepInfoTable(repInfoTableApiPtr->rep);
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 3:
      {
         printf("-----%s :: Testing Range Check Condition for repPort-----\n",__FUNCTION__);
         strncpy(repInfoTableApiPtr->rep, "10.100.211.72", 25);
         //repInfoTableApiPtr->ipType       = 1;
         repInfoTableApiPtr->repPort      = 1000;
         repInfoTableApiPtr->signallingWt = 0;
         repInfoTableApiPtr->dataWt       = 0;
         removeRepInfoTable(repInfoTableApiPtr->rep);
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 4:
      {
         printf("-----%s :: Testing Range Check Condition for repPort-----\n",__FUNCTION__);
         strncpy(repInfoTableApiPtr->rep, "10.100.211.72", 25);
         //repInfoTableApiPtr->ipType       = 1;
         repInfoTableApiPtr->repPort      = 65536;
         repInfoTableApiPtr->signallingWt = 0;
         repInfoTableApiPtr->dataWt       = 0;
         removeRepInfoTable(repInfoTableApiPtr->rep);
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 5:
      {
         printf("-----%s :: Testing Boundary Condition for rep-----\n",__FUNCTION__);
         strncpy(repInfoTableApiPtr->rep, "10.100.211.72", 25);
         //repInfoTableApiPtr->ipType       = 1;
         repInfoTableApiPtr->repPort      = 1100;
         repInfoTableApiPtr->signallingWt = 0;
         repInfoTableApiPtr->dataWt       = 0;
         removeRepInfoTable(repInfoTableApiPtr->rep);
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 6:
      {
         printf("-----%s :: Testing Range Check Condition for rep-----\n",__FUNCTION__);
         strncpy(repInfoTableApiPtr->rep, "10.100.211.72", 25);
         //repInfoTableApiPtr->ipType       = 1;
         repInfoTableApiPtr->repPort      = 1100;
         repInfoTableApiPtr->signallingWt = 0;
         repInfoTableApiPtr->dataWt       = 0;
         removeRepInfoTable(repInfoTableApiPtr->rep);
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 7:
      {
         printf("-----%s :: Testing Sunny-Day condition for repInfoTable-----\n",__FUNCTION__);
         strncpy(repInfoTableApiPtr->rep, "10.100.211.72", 25);
         //repInfoTableApiPtr->ipType       = 1;
         repInfoTableApiPtr->repPort      = 1100;
         repInfoTableApiPtr->signallingWt = 0;
         repInfoTableApiPtr->dataWt       = 0;
         removeRepInfoTable(repInfoTableApiPtr->rep);
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      default:
      {
         testInitiation = 1;
         gTestCaseCompleted = 1;
      }
   }
}

void bssPsTableRangeChkTest()
{
   static int testInitiation =1;

   BssPsTableApi *bssPsTableApiPtr;

   if (testInitiation != 1)
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("bssPsTableRangeChk:TestCase %d:Nack Receieved\n \n",testInitiation-1);
            }
            else
            {
               printf("bssPsTableRangeChk:TestCase %d:Ack Receieved\n \n",testInitiation-1);
            }
         }
         break;
      }
   }
   else
   {
      setBssPsPreConfigTable();
      setBssPsTable();
      insertIntoBssTable(1, LOCKED);
   }
//   removeBssPsTable(1);
   bssPsTableApiPtr = (BssPsTableApi*)calloc(1, sizeof(BssPsTableApi));
   switch (testInitiation)
   {
      case 1:
      {
         printf("-----%s :: Testing Boundary condition for nmo-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 2:
      {
         printf("-----%s :: Testing range check for nmo-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 2;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 3:
      {
         printf("-----%s :: Testing boundary condition for sgsnr-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 4:
      {
         printf("-----%s :: Testing range check for sgsnr-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 2;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 5:
      {
         printf("-----%s :: Testing boundary condition for tAvgW-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 25;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 6:
      {
         printf("-----%s :: Testing range check for tAvgW-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 26;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 7:
      {
         printf("-----%s :: Testing boundary condition for tAvgT-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 25;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 8:
      {
         printf("-----%s :: Testing range check for tAvgT-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 26;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 9:
      {
         printf("-----%s :: Testing boundary condition for nAvgI-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 15;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 10:
      {
         printf("-----%s :: Testing range check for nAvgI-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 16;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 11:
      {
         printf("-----%s :: Testing boundary condition for MaxNumPdch-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 12:
      {
         printf("-----%s :: Testing range check for MaxNumPdch-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS + 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 13:
      {
         printf("-----%s :: Testing Sunny-Day condition for BssPsTable-----\n",__FUNCTION__);
         bssPsTableApiPtr->bssPsId       = 2;
         bssPsTableApiPtr->nmo           = 1;
         bssPsTableApiPtr->sgsnr         = 1;
         bssPsTableApiPtr->tAvgW         = 24;
         bssPsTableApiPtr->tAvgT         = 24;
         bssPsTableApiPtr->nAvgI         = 13;
         bssPsTableApiPtr->maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
         cfgStubSendCmMessage(bssPsTableApiPtr,sizeof(BssPsTableApi),BSC_API_SET_BSSPSTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      default:
      {
         testInitiation = 1;
         gTestCaseCompleted = 1;
      }
   }
}

void lepInfoTableRangeChkTest()
{
   static int testInitiation =1;

   LepInfoTableApi *lepInfoTableApiPtr;

   if (testInitiation != 1)
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("lepInfoTableRangeChk:TestCase %d:Nack Receieved\n \n",testInitiation-1);
            }
            else
            {
               printf("lepInfoTableRangeChk:TestCase %d:Ack Receieved\n \n",testInitiation-1);
            }
         }
         break;
      }
   }
   else
   {
      setBssPsPreConfigTable();
      setGbInterfaceTable();
   }
   removeLepInfoTable("10.100.211.72");
   lepInfoTableApiPtr = (LepInfoTableApi*)calloc(1, sizeof(LepInfoTableApi));
   switch (testInitiation)
   {
      case 1:
      {
         printf("-----%s :: Testing Boundary condition for lepPort-----\n",__FUNCTION__);
         strncpy(lepInfoTableApiPtr->lep, "10.100.211.72", 25);
         //lepInfoTableApiPtr->ipType       = 0;
         lepInfoTableApiPtr->lepPort      = 65535;
         lepInfoTableApiPtr->signallingWt = 0;
         lepInfoTableApiPtr->dataWt       = 0;
         removeLepInfoTable(lepInfoTableApiPtr->lep);
         cfgStubSendCmMessage(lepInfoTableApiPtr,sizeof(LepInfoTableApi),BSC_API_SET_LEPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 2:
      {
         printf("-----%s :: Testing range check for lepPort-----\n",__FUNCTION__);
         strncpy(lepInfoTableApiPtr->lep, "10.100.211.72", 25);
         //lepInfoTableApiPtr->ipType       = 0;
         lepInfoTableApiPtr->lepPort      = 65536;
         lepInfoTableApiPtr->signallingWt = 0;
         lepInfoTableApiPtr->dataWt       = 0;
         removeLepInfoTable(lepInfoTableApiPtr->lep);
         cfgStubSendCmMessage(lepInfoTableApiPtr,sizeof(LepInfoTableApi),BSC_API_SET_LEPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 3:
      {
         printf("-----%s :: Testing Sunny-Day condition for LepInfoTable-----\n",__FUNCTION__);
         strncpy(lepInfoTableApiPtr->lep, "10.100.211.72", 25);
         //lepInfoTableApiPtr->ipType       = 0;
         lepInfoTableApiPtr->lepPort      = 3;
         lepInfoTableApiPtr->signallingWt = 0;
         lepInfoTableApiPtr->dataWt       = 0;
         removeLepInfoTable(lepInfoTableApiPtr->lep);
         cfgStubSendCmMessage(lepInfoTableApiPtr,sizeof(LepInfoTableApi),BSC_API_SET_LEPINFOTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      default:
      {
         testInitiation = 1;
         gTestCaseCompleted = 1;
      }
   }
}

void gbInterfaceTableRangeChkTest()
{
   static int testInitiation =1;

   GbInterfaceTableApi *gbInterfaceTableApiPtr;


   if (testInitiation != 1)
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("GbInterfaceTableRangeChk:TestCase %d:Nack Receieved\n \n",testInitiation-1);
            }
            else
            {
               printf("GbInterfaceTableRangeChk:TestCase %d:Ack Receieved\n \n",testInitiation-1);
            }
         }
         break;
      }
   }
   else
   {
      insertIntoBssTable(1, LOCKED);
      setGbInterfaceTable();
   }
//   removeGbInterfaceTable(1);
   gbInterfaceTableApiPtr = (GbInterfaceTableApi*)calloc(1, sizeof(GbInterfaceTableApi));
   switch (testInitiation)
   {
      case 1:
      {
         printf("-----%s :: Testing range check for transportType-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 10;
         gbInterfaceTableApiPtr->tFcTh            = 100;
         gbInterfaceTableApiPtr->tFcSup           = 8;
         gbInterfaceTableApiPtr->nMaxFcRep        = 1;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 2:
      {
         printf("-----%s :: Testing boundary condition for tFcC-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 1;
         gbInterfaceTableApiPtr->tFcTh            = 100;
         gbInterfaceTableApiPtr->tFcSup           = 8;
         gbInterfaceTableApiPtr->nMaxFcRep        = 1;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 3:
      {
         printf("-----%s :: Testing boundary condition for tFcC-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 10;
         gbInterfaceTableApiPtr->tFcTh            = 100;
         gbInterfaceTableApiPtr->tFcSup           = 8;
         gbInterfaceTableApiPtr->nMaxFcRep        = 1;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 4:
      {
         printf("-----%s :: Testing Range Check for tFcC-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 0;
         gbInterfaceTableApiPtr->tFcTh            = 100;
         gbInterfaceTableApiPtr->tFcSup           = 8; 
         gbInterfaceTableApiPtr->nMaxFcRep        = 1;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 5:
      {
         printf("-----%s :: Testing Range Check for tFcC-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 11;
         gbInterfaceTableApiPtr->tFcTh            = 100;
         gbInterfaceTableApiPtr->tFcSup           = 8;
         gbInterfaceTableApiPtr->nMaxFcRep        = 1;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 6:
      {
         printf("-----%s :: Testing boundary condition for tFcTh-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 5;
         gbInterfaceTableApiPtr->tFcTh            = 5;
         gbInterfaceTableApiPtr->tFcSup           = 2;
         gbInterfaceTableApiPtr->nMaxFcRep        = 2;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 7:
      {
         printf("-----%s :: Testing boundary condition for tFcTh-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 5;
         gbInterfaceTableApiPtr->tFcTh            = 6000;
         gbInterfaceTableApiPtr->tFcSup           = 2;
         gbInterfaceTableApiPtr->nMaxFcRep        = 2;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 8:
      {
         printf("-----%s :: Testing Range Check for tFcTh-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 5;
         gbInterfaceTableApiPtr->tFcTh            = 4;
         gbInterfaceTableApiPtr->tFcSup           = 2;
         gbInterfaceTableApiPtr->nMaxFcRep        = 2;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 9:
      {
         printf("-----%s :: Testing Range Check for tFcTh-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 5;
         gbInterfaceTableApiPtr->tFcTh            = 6001;
         gbInterfaceTableApiPtr->tFcSup           = 2;
         gbInterfaceTableApiPtr->nMaxFcRep        = 2;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 10:
      {
         printf("-----%s :: Testing boundary condition for tFcSup-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 5;
         gbInterfaceTableApiPtr->tFcTh            = 10;
         gbInterfaceTableApiPtr->tFcSup           = 0;
         gbInterfaceTableApiPtr->nMaxFcRep        = 2;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 11:
      {
         printf("-----%s :: Testing boundary condition for tFcSup-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 50;
         gbInterfaceTableApiPtr->tFcTh            = 1000;
         gbInterfaceTableApiPtr->tFcSup           = 99;
         gbInterfaceTableApiPtr->nMaxFcRep        = 2;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 12:
      {
         printf("-----%s :: Testing Range Check for tFcSup-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 50;
         gbInterfaceTableApiPtr->tFcTh            = 1000;
         gbInterfaceTableApiPtr->tFcSup           = 100;
         gbInterfaceTableApiPtr->nMaxFcRep        = 2;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 13:
      {
         printf("-----%s :: Testing boundary condition for nMaxFcRep-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 5;
         gbInterfaceTableApiPtr->tFcTh            = 10;
         gbInterfaceTableApiPtr->tFcSup           = 4;
         gbInterfaceTableApiPtr->nMaxFcRep        = 1;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 14:
      {
         printf("-----%s :: Testing boundary condition for tFcSup-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 5;
         gbInterfaceTableApiPtr->tFcTh            = 10;
         gbInterfaceTableApiPtr->tFcSup           = 1;
         gbInterfaceTableApiPtr->nMaxFcRep        = 3;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 15:
      {
         printf("-----%s :: Testing Range Check for nMaxFcRep-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 5;
         gbInterfaceTableApiPtr->tFcTh            = 10;
         gbInterfaceTableApiPtr->tFcSup           = 50;
         gbInterfaceTableApiPtr->nMaxFcRep        = 0;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 16:
      {
         printf("-----%s :: Testing Range Check for nMaxFcRep-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 5;
         gbInterfaceTableApiPtr->tFcTh            = 10;
         gbInterfaceTableApiPtr->tFcSup           = 1;
         gbInterfaceTableApiPtr->nMaxFcRep        = 4;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 17:
      {
         printf("-----%s :: Testing Range Check for GbInterfaceTable-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2;
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5;
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 7;
         gbInterfaceTableApiPtr->tFcTh            = 6;
         gbInterfaceTableApiPtr->tFcSup           = 50;
         gbInterfaceTableApiPtr->nMaxFcRep        = 2;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 18:
      {
         printf("-----%s :: Testing Range Check for GbInterfaceTable-----\n",__FUNCTION__);
         gbInterfaceTableApiPtr->gbIfIndex        = 2; 
         gbInterfaceTableApiPtr->nsei             = 10;
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr= 5; 
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp= 0;
         gbInterfaceTableApiPtr->maxNumLeps       = 20;
         gbInterfaceTableApiPtr->maxNumReps       = 20;
         gbInterfaceTableApiPtr->transportType    = FR;
         gbInterfaceTableApiPtr->tFcC             = 5;
         gbInterfaceTableApiPtr->tFcTh            = 10;
         gbInterfaceTableApiPtr->tFcSup           = 50;
         gbInterfaceTableApiPtr->nMaxFcRep        = 2;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr,sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      default:
      {
         testInitiation = 1;
         gTestCaseCompleted = 1;
      }
   }
}

void psCellTableRangeChkTest()
{
   static int testInitiation =1;

   PsCellTableApi *psCellTableApiPtr;

   if (testInitiation != 1)
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("PsCellTableRangeChk:TestCase %d:Nack Receieved\n \n",testInitiation-1);
            }
            else
            {
               printf("PsCellTableRangeChk:TestCase %d:Ack Receieved\n \n",testInitiation-1);
            }
         }
         break;
      }
   }
   else
   {
      setBssPsPreConfigTable();
//      setCellPerTable();
      setRaTable();
      removeCellPerTable(10,10);
   }
   psCellTableApiPtr = (PsCellTableApi*)calloc(1, sizeof(PsCellTableApi));
   switch (testInitiation)
   {
      case 1:
      {
         printf("-----%s :: Testing Boundary condition for RaColour-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 0;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 2:
      {
         printf("-----%s :: Testing Boundary condition for RaColour-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 7;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 3:
      {
         printf("-----%s :: Testing range check for RaColour-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 8;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 4:
      {
         printf("-----%s :: Testing Boundary condition for lac-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 1;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 5:
      {
         printf("-----%s :: Testing Boundary condition for lac-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 65535;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 6:
      {
         printf("-----%s :: Testing Range Check for lac-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 0;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 7:
      {
         printf("-----%s :: Testing Range Check for lac-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 65534;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 8:
      {
         printf("-----%s :: Testing Boundary Condition for bvciId-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 2;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 9:
      {
         printf("-----%s :: Testing Boundary Condition for bvciId-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 65535;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 10:
      {
         printf("-----%s :: Testing Range check for bvciId-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 1;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 11:
      {
         printf("-----%s :: Testing Boundary Condition for priorityAccessThr-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 0;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 12:
      {
         printf("-----%s :: Testing Boundary Condition for priorityAccessThr-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 7;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 13:
      {
         printf("-----%s :: Testing Range Check for priorityAccessThr-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 8;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 14:
      {
         printf("-----%s :: Testing Boundary Condition for maxNumPdchCell-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 1;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 15:
      {
         printf("-----%s :: Testing Boundary Condition for maxNumPdchCell-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = MAX_NUM_TRX_PER_CELL * 8 - 1;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 16:
      {
         printf("-----%s :: Testing Range Check for maxNumPdchCell-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 0;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 17:
      {
         printf("-----%s :: Testing Range Check for maxNumPdchCell-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = MAX_NUM_TRX_PER_CELL * 8;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_PDCH_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 18:
      {
         printf("-----%s :: Testing Boundary Condition for minNumPdchCell-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 1;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 19:
      {
         printf("-----%s :: Testing Boundary Condition for minNumPdchCell-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = MAX_NUM_TRX_PER_CELL * 8 - 1;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 20:
      {
         printf("-----%s :: Testing Range Check for minNumPdchCell-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = MAX_NUM_TRX_PER_CELL * 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 21:
      {
         printf("-----%s :: Testing Boundary Condition for maxNumTbfPdch-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 1;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 22:
      {
         printf("-----%s :: Testing Boundary Condition for maxNumTbfPdch-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 7;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 23:
      {
         printf("-----%s :: Testing Range Check for maxNumTbfPdch-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 0;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 24:
      {
         printf("-----%s :: Testing Range Check for maxNumTbfPdch-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 8;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 25:
      {
         printf("-----%s :: Testing Boundary Condition for ssb-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 0;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 26:
      {
         printf("-----%s :: Testing Boundary Condition for ssb-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 63;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 27:
      {
         printf("-----%s :: Testing Range Check for ssb-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 64;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 28:
      {
         printf("-----%s :: Testing Range Check for gprsDlaEnabled-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 3;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 29:
      {
         printf("-----%s :: Testing Boundary Condition for gprsCsMax-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 1;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 30:
      {
         printf("-----%s :: Testing Boundary Condition for gprsCsMax-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 4;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 31:
      {
         printf("-----%s :: Testing Range Check for gprsCsMax-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 0;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 32:
      {
         printf("-----%s :: Testing Range Check for gprsCsMax-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 5;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 33:
      {
         printf("-----%s :: Testing Boundary Condition for gprsCsInitial-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 1;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 34:
      {
         printf("-----%s :: Testing Boundary Condition for gprsCsInitial-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 4;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 35:
      {
         printf("-----%s :: Testing Range Check for gprsCsInitial-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 0;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 36:
      {
         printf("-----%s :: Testing Range Check for gprsCsInitial-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;//MAX_NUM_TRX_PER_CELL * 8 - 2;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 5;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 37:
      {
         printf("-----%s :: Testing Range Check for PsCell Table-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 7;
         psCellTableApiPtr->minNumPdchCell   = 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 38:
      {
         printf("-----%s :: Testing Range check for PsCell Table-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 2;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 39:
      {
         printf("-----%s :: Testing Sunny-Day condition for PSCell Table-----\n",__FUNCTION__);
         psCellTableApiPtr->lac              = 10;
         psCellTableApiPtr->cellId           = 10;
         psCellTableApiPtr->rac              = 5;   
         psCellTableApiPtr->raColour         = 5;
         psCellTableApiPtr->bvciId           = 50;
         psCellTableApiPtr->maxNumPdchCell   = 10;
         psCellTableApiPtr->minNumPdchCell   = 8;
         psCellTableApiPtr->maxNumTbfPdch    = 5;
         psCellTableApiPtr->ssb              = 5;
         psCellTableApiPtr->priorityAccessThr= 5;
         psCellTableApiPtr->gprsDlaEnabled   = 1;
         psCellTableApiPtr->gprsCsMax        = 3;
         psCellTableApiPtr->gprsCsInitial    = 3;
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      default:
      {
         testInitiation = 1;
         gTestCaseCompleted = 1;
      }
   }
}


void cellTableRangeChkTest()
{
   static int testInitiation =1;

   CellPerTableApi *cellPerTableApiPtr;

   if (testInitiation != 1)
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
            {
               printf("cellTableRangeChk:TestCase %d:Nack Receieved\n \n",testInitiation-1);
            }
            else
            {
               printf("cellTableRangeChk:TestCase %d:Ack Receieved\n \n",testInitiation-1);
            }
         }
         break;
      }
   }
   else
   {
   }
   cellPerTableApiPtr = (CellPerTableApi*)calloc(1, sizeof(CellPerTableApi));
   switch (testInitiation)
   {
      case 1:
      {
         printf("-----%s :: Testing Range Check for admin state-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = 3;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 2:
      {
         printf("-----%s :: Testing Boundary condition for bcchArfcn with freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 1;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 3:
      {
         printf("-----%s :: Testing Boundary condition for bcchArfcn with freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 124;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 4:
      {
         printf("-----%s :: Testing Range Check for bcchArfcn with freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 0;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 5:
      {
         printf("-----%s :: Testing Range Check for bcchArfcn with freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 125;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 6:
      {
         printf("-----%s :: Testing Boundary Condition for bcchArfcn with freqBandBcch GSM1800-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 512;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 7:
      {
         printf("-----%s :: Testing Boundary Condition for bcchArfcn with freqBandBcch GSM1800-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 885;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 8:
      {
         printf("-----%s :: Testing Range Check bcchArfcn with freqBandBcch GSM1800-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 511;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 9:
      {
         printf("-----%s :: Testing Range Check bcchArfcn with freqBandBcch GSM1800-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 886;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 10:
      {
         printf("-----%s :: Testing Range Check for freqBandBcch-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = 6;//GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 11:
      {
         printf("-----%s :: Testing Boundary Condition for bcc-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 0;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 12:
      {
         printf("-----%s :: Testing Boundary Condition for bcc-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 7;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 13:
      {
         printf("-----%s :: Testing Range Check for bcc-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 8;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 14:
      {
         printf("-----%s :: Testing Boundary Condition for msTxPwrMax for freqBandBcch GSM850-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_850;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 5;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 15:
      {
         printf("-----%s :: Testing Boundary Condition for msTxPwrMax for freqBandBcch GSM850-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_850;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 19;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 16:
      {
         printf("-----%s :: Testing Range Check for msTxPwrMax for freqBandBcch GSM850-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_850;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 4;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 17:
      {
         printf("-----%s :: Testing Range Check for msTxPwrMax for freqBandBcch GSM850-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_850;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 20;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 18:
      {
         printf("-----%s :: Testing Boundary Condition for msTxPwrMax for freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 5;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 19:
      {
         printf("-----%s :: Testing Boundary Condition for msTxPwrMax for freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 19;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 20:
      {
         printf("-----%s :: Testing Range check for msTxPwrMax for freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 4;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 21:
      {
         printf("-----%s :: Testing Range check for msTxPwrMax for freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 20;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 22:
      {
         printf("-----%s :: Testing Boundary Condition for msTxPwrMax for freqBandBcch GSM1800-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 0;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 23:
      {
         printf("-----%s :: Testing Boundary Condition for msTxPwrMax for freqBandBcch GSM1800-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 15;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 24:
      {
         printf("-----%s :: Testing Range check for msTxPwrMax for freqBandBcch GSM1800-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 16;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 25:
      {
         printf("-----%s :: Testing Boundary Condition for msTxPwrMax for freqBandBcch GSM1900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 0;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 26:
      {
         printf("-----%s :: Testing Boundary Condition for msTxPwrMax for freqBandBcch GSM1900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 15;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 27:
      {
         printf("-----%s :: Testing Range check for msTxPwrMax for freqBandBcch GSM1900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 16;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 28:
      {
         printf("-----%s :: Testing Boundary condition for msTxPowerMaxCch for freqBandBcch GSM850-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_850;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 5;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 29:
      {
         printf("-----%s :: Testing Boundary condition for msTxPowerMaxCch for freqBandBcch GSM850-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_850;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 19;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 30:
      {
         printf("-----%s :: Testing Range Check for msTxPowerMaxCch for freqBandBcch GSM850-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_850;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 4;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 31:
      {
         printf("-----%s :: Testing Range Check for msTxPowerMaxCch for freqBandBcch GSM850-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_850;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 20;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 32:
      {
         printf("-----%s :: Testing Boundary condition for msTxPowerMaxCch for freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 5;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 33:
      {
         printf("-----%s :: Testing Boundary condition for msTxPowerMaxCch for freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 19;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 34:
      {
         printf("-----%s :: Testing Range Check for msTxPowerMaxCch for freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 4;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 35:
      {
         printf("-----%s :: Testing Range Check for msTxPowerMaxCch for freqBandBcch GSM900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 20;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 36:
      {
         printf("-----%s :: Testing Boundary condition for msTxPowerMaxCch for freqBandBcch GSM1800-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 0;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 37:
      {
         printf("-----%s :: Testing Boundary condition for msTxPowerMaxCch for freqBandBcch GSM1800-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 15;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 38:
      {
         printf("-----%s :: Testing Range Check for msTxPowerMaxCch for freqBandBcch GSM1800-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 16;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 39:
      {
         printf("-----%s :: Testing Boundary condition for msTxPowerMaxCch for freqBandBcch GSM1900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 0;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 40:
      {
         printf("-----%s :: Testing Boundary condition for msTxPowerMaxCch for freqBandBcch GSM1900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 15;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 41:
      {
         printf("-----%s :: Testing Range Check for msTxPowerMaxCch for freqBandBcch GSM1900-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1900;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 16;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 42:
      {
         printf("-----%s :: Testing Range Check for psAllowed-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = 2;//TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 43:
      {
         printf("-----%s :: Testing Range Check for cellBarAccess-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 2;//0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 44:
      {
         printf("-----%s :: Testing Boundary Condition for bcchPwr-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 0;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 45:
      {
         printf("-----%s :: Testing Boundary Condition for bcchPwr-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 127;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 46:
      {
         printf("-----%s :: Testing Range Check for bcchPwr-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 128;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 47:
      {
         printf("-----%s :: Testing Boundary Condition for bsAgBlkRes-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 0;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 48:
      {
         printf("-----%s :: Testing Boundary Condition for bsAgBlkRes-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 7;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 49:
      {
         printf("-----%s :: Testing Range Check for bsAgBlkRes-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 8;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 50:
      {
         printf("-----%s :: Testing Boundary Condition for bsPaMfrms-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 0;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 51:
      {
         printf("-----%s :: Testing Boundary Condition for bsPaMfrms-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 7;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 52:
      {
         printf("-----%s :: Testing Range Check for bsPaMfrms-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 8;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 53:
      {
         printf("-----%s :: Testing Boundary condition for cellReselectHysteresis-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 0;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 54:
      {
         printf("-----%s :: Testing Boundary condition for cellReselectHysteresis-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 7;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 55:
      {
         printf("-----%s :: Testing Range Check for cellReselectHysteresis-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 8;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 56:
      {
         printf("-----%s :: Testing Boundary Condition for rxLevAccessMin-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 0;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 57:
      {
         printf("-----%s :: Testing Boundary Condition for rxLevAccessMin-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 63;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 58:
      {
         printf("-----%s :: Testing Range Check for rxLevAccessMin-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 64;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 59:
      {
         printf("-----%s :: Testing Boundary Condition for PowerOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 0;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 60:
      {
         printf("-----%s :: Testing Boundary Condition for PowerOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 3;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 61:
      {
         printf("-----%s :: Testing Range Check for PowerOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 4;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 62:
      {
         printf("-----%s :: Testing Boundary Condition for cbq-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 0;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 63:
      {
         printf("-----%s :: Testing Boundary Condition for cbq-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 3;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 64:
      {
         printf("-----%s :: Testing Range Check for cbq-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 4;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 65:
      {
         printf("-----%s :: Testing Boundary Condition for cellReselectOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 0;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 66:
      {
         printf("-----%s :: Testing Boundary Condition for cellReselectOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 63;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 67:
      {
         printf("-----%s :: Testing Range Check for cellReselectOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 64;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 68:
      {
         printf("-----%s :: Testing Boundary Condtion for tempOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 0;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 69:
      {
         printf("-----%s :: Testing Boundary Condtion for tempOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 7;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 70:
      {
         printf("-----%s :: Testing Range Check for tempOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 8;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 71:
      {
         printf("-----%s :: Testing Boundary Condition for penaltyTime-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 0;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 72:
      {
         printf("-----%s :: Testing Boundary Condition for penaltyTime-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 31;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 73:
      {
         printf("-----%s :: Testing Range Check for penaltyTime-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 32;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 74:
      {
         printf("-----%s :: Testing Boundary Condition for fnOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 0;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 75:
      {
         printf("-----%s :: Testing Boundary Condition for fnOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 25;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 76:
      {
         printf("-----%s :: Testing Range Check for fnOffset-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 26;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         //gTestCaseCompleted = 1;
         break;
      }
      case 77:
      {
         printf("-----%s :: Testing Sunny-Day Condition for Cell Table-----\n",__FUNCTION__);
         cellPerTableApiPtr->lac                    = 10;
         cellPerTableApiPtr->cellId                 = 10;
         cellPerTableApiPtr->adminState             = LOCK;
         cellPerTableApiPtr->antennaId              = 1;
         cellPerTableApiPtr->bcchArfcn              = 30;
         cellPerTableApiPtr->freqBandBcch           = GSM_1800;
         cellPerTableApiPtr->bcc                    = 5;
         cellPerTableApiPtr->bcchPwr                = 50;
         cellPerTableApiPtr->msTxPwrMax             = 10;
         cellPerTableApiPtr->msTxPowerMaxCch          = 10;
         cellPerTableApiPtr->fnOffset               = 10;
         cellPerTableApiPtr->psAllowed               = TRUE;
         cellPerTableApiPtr->cellBarAccess          = 0;
         cellPerTableApiPtr->accessCtrlClass        = 0;
         cellPerTableApiPtr->bsAgBlksRes            = 5;
         cellPerTableApiPtr->bsPaMfrms              = 5;
         cellPerTableApiPtr->cellReselectHysteresis = 5;
         cellPerTableApiPtr->rxLevAccessMin         = 10;
         cellPerTableApiPtr->powerOffset            = 2;
         cellPerTableApiPtr->cbq                    = 1;
         cellPerTableApiPtr->cellReselectOffset     = 10;
         cellPerTableApiPtr->tempOffset             = 5;
         cellPerTableApiPtr->penalityTime           = 10;
         setArfcnListTable(cellPerTableApiPtr);
         cfgStubSendCmMessage(cellPerTableApiPtr,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
         testInitiation++;
         gTestCaseCompleted = 1;
         break;
      }
      default:
      {
         testInitiation = 1;
         gTestCaseCompleted = 1;
      }
   }
}


void removeNsvcTable(I_U16 nsvcId)
{
   NsvcTableIndices nsvcTableIndicesBuff;
   nsvcTableIndicesBuff.nsvcId = nsvcId;
   if(deleteNsvcTable(&nsvcTableIndicesBuff) == CLIB_SUCCESS)
   {
      printf("Delete from NSvc Table successful\n");
   }
   else
   {
      printf("Delete from NSvc Table unsuccessful\n");
   }
}


void removeNsvcStatusTable(I_U16 nsvcId)
{
   NsvcStatusTableIndices nsvcStatusTableApiBuff;
   nsvcStatusTableApiBuff.nsvcId = nsvcId;
   if(deleteNsvcStatusTable(&nsvcStatusTableApiBuff) == CLIB_SUCCESS)
   {
      printf("Delete from Nsvc Status Table Successful\n");
   }
   else
   {
      printf("Delete from Nsvc Status Table Unsuccessful\n");
   }
}


void removeNsvcConnIdMapTable(I_U16 nsvcId)
{
   NsvcConnIdMapTableIndices nsvcConnIdMapTableApiBuff;
   nsvcConnIdMapTableApiBuff.nsvcId = nsvcId;
   if(deleteNsvcConnIdMapTable(&nsvcConnIdMapTableApiBuff) == CLIB_SUCCESS)
   {
      printf("Delete from Nsvc ConnId Map Table Successful\n");
   }
   else
   {
      printf("Delete from Nsvc ConnId Map Table Unsuccessful\n");
   }
}


void removeFrLinkTable(I_U16 frChnId)
{
   FrLinkTableIndices frLinkTableIndicesBuff;
   frLinkTableIndicesBuff.frChnId = frChnId;
   if(deleteFrLinkTable(&frLinkTableIndicesBuff) == CLIB_SUCCESS)
   {
      printf("Delete from FrLink Table Successful\n");
   }
   else
   {
      printf("Delete from FrLink Table Unsuccessful\n");
   }
}
void   removeFrLinkStatusTable(I_U16 frChnId)
{
   FrLinkStatusTableIndices frLinkStatusTableIndicesBuff;
   frLinkStatusTableIndicesBuff.frChnId = frChnId;
   if(deleteFrLinkStatusTable(&frLinkStatusTableIndicesBuff) == CLIB_SUCCESS)
   {
      printf("Delete from FrLink Status Table Successful\n");
   }
   else
   {
      printf("Delete from FrLink Status Table Unsuccessful\n");
   }
}



void removeRepInfoTable(I_S8 *rep)
{
   RepInfoTableIndices repInfoTableIndicesBuff;
   RepInfoTableApi *repPtr = NULL;
   RepInfoTableApi *tmpRepPtr = NULL;
   I_U32 outCount = 0;
   I_U16 outSize = 0;
   I_U32 i;
   strncpy(repInfoTableIndicesBuff.rep, rep, 25);
    if(getallRepInfoTable(&repPtr,&outCount,&outSize) == CLIB_SUCCESS)
    {
      printf("outCount = [%d]\n",outCount);
      for(i = 0;i < outCount;i++)
      {
         tmpRepPtr = (RepInfoTableApi*)(((I_U8*)repPtr + i * outSize));
         printf("Get from RepInfo Table Successful:tmpRepPtr->rep = [%u]\n",tmpRepPtr->rep);
      } 
    }
    else
    {
      printf("Get from RepInfo Table Unsuccessful\n"); 
    }
   //repInfoTableIndicesBuff.ipType = ipType;
   if(deleteRepInfoTable(&repInfoTableIndicesBuff) == CLIB_SUCCESS)
   {
      printf("Delete from RepInfo Table Successful\n"); 
   }
   else
   {
      printf("Delete from RepInfo Table Unsuccessful\n"); 
   }
}


void removeBssPsTable(I_U16 bssPsId)
{
   BssPsTableIndices bssPsTableIndicesBuff;
   bssPsTableIndicesBuff.bssPsId = bssPsId;
   if(deleteBssPsTable(&bssPsTableIndicesBuff) == CLIB_SUCCESS)
   {
      printf("Delete from BssPs Table Successful\n"); 
   }
   else
   {
      printf("Delete from BssPs Table Unsuccessful\n");
   } 
}


void removeLepInfoTable(I_S8 *lep)
{
   LepInfoTableIndices lepInfoTableIndicesBuff;
   strncpy(lepInfoTableIndicesBuff.lep, lep, 25);
   //lepInfoTableIndicesBuff.ipType = ipType;
   if(deleteLepInfoTable(&lepInfoTableIndicesBuff) == CLIB_SUCCESS)
   {
      printf("Delete from LepInfo table Successful\n");
   }
   else
   {
      printf("Delete from LepInfo table Unsuccessful\n");
   }
}


void removeGbInterfaceTable(I_U16    gbIfIndex)
{
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;
   gbInterfaceTableIndicesBuff.gbIfIndex = gbIfIndex;
   if(deleteGbInterfaceTable(&gbInterfaceTableIndicesBuff) == CLIB_SUCCESS)
   {
      printf("Delete from gbInterface Table Successful\n");
   }
   else
   {
      printf("Delete from gbInterface Table Unsuccessful\n");
   }
}


void setFrLinkTable()
{
   FrLinkTableApi frLinkTableApiBuff;
   frLinkTableApiBuff.frChnId = OAMS_CFG_FR_CHN_ID_MAX_VALUE - 2;
   frLinkTableApiBuff.e1Id    = 2; 
   frLinkTableApiBuff.startTs = 2;
   frLinkTableApiBuff.numTs   = 2;
   if(CLIB_SUCCESS == insertFrLinkTable(&frLinkTableApiBuff))
   {
      printf("Insert Fr Successfull\n");
   }
   else
   {
      printf("Insert Fr Unsuccessful\n");
   }
}

void insertIntoCellTable(I_U16 cellId, I_U16 lac, I_U32 adminState, I_U32 psAllowed)
{
   CellPerTableApi cellPerTableApiBuff;
   CellNonPerTableApi cellNonPerTableApiBuff;
   cellPerTableApiBuff.lac                     =lac;
   cellPerTableApiBuff.cellId                  = cellId;
   cellPerTableApiBuff.adminState              = adminState;
   //cellPerTableApiBuff.antennaId               =;
   //cellPerTableApiBuff.bcchArfcn               =;
   //cellPerTableApiBuff.freqBandBcch            =;
   //cellPerTableApiBuff.bcc                     =;
   //cellPerTableApiBuff.bcchPwr                 =;
   //cellPerTableApiBuff.msTxPwrMax              =;
   //cellPerTableApiBuff.msTxPowerMaxCch         =;
   //cellPerTableApiBuff.fnOffset                =;
   cellPerTableApiBuff.psAllowed               = psAllowed;
   cellPerTableApiBuff.cellBarAccess           = FALSE;
   //cellPerTableApiBuff.accessCtrlClass         =;
   //cellPerTableApiBuff.bsAgBlksRes             =;
   //cellPerTableApiBuff.bsPaMfrms               =;
   //cellPerTableApiBuff.cellReselectHysteresis  =;
   //cellPerTableApiBuff.rxLevAccessMin          =;
   //cellPerTableApiBuff.powerOffset             =;
   //cellPerTableApiBuff.cbq                     =;
   //cellPerTableApiBuff.cellReselectOffset      =;
   //cellPerTableApiBuff.tempOffset              =;
   //cellPerTableApiBuff.penalityTime            =;
   if(CLIB_SUCCESS == insertCellPerTable(&cellPerTableApiBuff))
   {
      printf("Insert in CellPerTable Successful\n");
      cellNonPerTableApiBuff.cellId = cellId;
      cellNonPerTableApiBuff.lac = lac;
      cellNonPerTableApiBuff.oprState = DISABLED;
      
      if(CLIB_SUCCESS == insertCellNonPerTable(&cellNonPerTableApiBuff))
      {
         printf("Insert in CellNonPerTable Successful\n");

      }
      else
      {
         printf("Insert in CellNonPerTable UnSuccessful\n");
      }
   }
   else
   {
      printf("Insert in CellPerTable UnSuccessful\n");
   }
}


void insertIntoPsCellTable(I_U16 cellId, I_U16 lac, I_U8 rac)
{
   PsCellTableApi psCellTableApiBuff;

   psCellTableApiBuff.lac              = lac;
   psCellTableApiBuff.cellId           = cellId;
   psCellTableApiBuff.rac              = rac;
   psCellTableApiBuff.raColour         = 5;
   psCellTableApiBuff.bvciId           = 50;
   psCellTableApiBuff.maxNumPdchCell   = 10;
   psCellTableApiBuff.minNumPdchCell   = 8;
   psCellTableApiBuff.maxNumTbfPdch    = 5;
   psCellTableApiBuff.ssb              = 5;
   psCellTableApiBuff.priorityAccessThr= 5;
   psCellTableApiBuff.gprsDlaEnabled   = 1;
   psCellTableApiBuff.gprsCsMax        = 3;
   psCellTableApiBuff.gprsCsInitial    = 1;
   if(CLIB_SUCCESS == insertPsCellTable(&psCellTableApiBuff))
   {
      printf("Insert PS Cell Successfull\n");
		
   }
   else
   {
      printf("Insert Ps Cell Unsuccessful\n");
   }

}
void insertIntoNsvcTable(I_U16 nsvcId, I_U16 frChnId, I_U32 adminState)
{
   NsvcTableApi nsvcTableApiBuff;
   nsvcTableApiBuff.nsvcId     = nsvcId;
   nsvcTableApiBuff.adminState = adminState;
   nsvcTableApiBuff.frChnId    = frChnId;
   nsvcTableApiBuff.dlci       = 20;

   if(CLIB_SUCCESS == insertNsvcTable(&nsvcTableApiBuff))
   {
      printf("Insert NSVC Successfull\n");
   }
   else
   {
      printf("Insert NSVC Unsuccessful\n");
   }
}


void insertIntoFrLinkTable(I_U16 frChnId, I_U16 e1Id)
{
   FrLinkTableApi frLinkTableApiBuff;
   frLinkTableApiBuff.frChnId = frChnId;
   frLinkTableApiBuff.e1Id    = e1Id; 
   frLinkTableApiBuff.startTs = frChnId;
   frLinkTableApiBuff.numTs   = 1;
   if(CLIB_SUCCESS == insertFrLinkTable(&frLinkTableApiBuff))
   {
      printf("Insert Fr Successfull\n");
   }
   else
   {
      printf("Insert Fr Unsuccessful\n");
   }
}

void insertIntoLinkTable(I_U16 linksetId, I_U16 linkId, I_U16 e1Num, I_U8 timeslot, I_U32 adminState)
{
   LinkTableApi linkTableApiBuff;

   linkTableApiBuff.linksetID = linksetId;
   linkTableApiBuff.linkId    = linkId; 
   linkTableApiBuff.slc = 1;
   linkTableApiBuff.e1Num = e1Num;
   linkTableApiBuff.timeSlot = timeslot;
   linkTableApiBuff.cardNum = 1;
   linkTableApiBuff.crcFlag = 1;
   linkTableApiBuff.adminState = adminState;
   if(CLIB_SUCCESS == insertLinkTable(&linkTableApiBuff))
   {
      printf("Insert Link Table Successfull\n");
   }
   else
   {
      printf("Insert Link Table Unsuccessful\n");
   }
}


void insertIntoMlppConfigTable(I_U16 e1Num, I_U8 timeslot)
{
   MlpppConfigTableApi mlpppConfigTableApiBuff;

   mlpppConfigTableApiBuff.numChannel = 1;
   mlpppConfigTableApiBuff.mlpppLinkId = 1;
   mlpppConfigTableApiBuff.trunkportId1 = e1Num;
   mlpppConfigTableApiBuff.timeslot1 = timeslot;
   if(CLIB_SUCCESS == insertMlpppConfigTable(&mlpppConfigTableApiBuff))
   {
      printf("Insert MlpppConfig Table Successfull\n");
   }
   else
   {
      printf("Insert MlpppConfig Table Unsuccessful\n");
   }
}


void insertIntoLaTable(I_U16 lac)
{
   LaTableApi laTableApiBuff;
   laTableApiBuff.lac = lac;
   if(CLIB_SUCCESS == insertLaTable(&laTableApiBuff))
   {
      printf("Insert La Successfull\n");
   }
   else
   {
      printf("Insert La Unsuccessful\n");
   }
}
void insertIntoRaTable(I_U16 lac, I_U8 rac)
{
   RaTableApi raTableApiBuff;
   raTableApiBuff.lac = lac;
   raTableApiBuff.rac = rac; 
   if(CLIB_SUCCESS == insertRaTable(&raTableApiBuff))
   {
      printf("Insert Ra Successfull\n");
   }
   else
   {
      printf("Insert Ra Unsuccessful\n");
   }
}


void insertIntoChnGrpTable(I_U16 cellId, I_U16 lac)
{
   ChnGrpTableApi chnGrpTableApiBuff;
   chnGrpTableApiBuff.lac = lac;
   chnGrpTableApiBuff.cellId = cellId;
   chnGrpTableApiBuff.chnGrpId = 1;
   chnGrpTableApiBuff.bcchCcchSdcch4 = 1;
   chnGrpTableApiBuff.bcchCcch = 0;
   chnGrpTableApiBuff.sdcch8 = 1;
   chnGrpTableApiBuff.dualTraffic = 1;
   chnGrpTableApiBuff.hsn = 1;
   chnGrpTableApiBuff.maxTxPwr = 4;
   chnGrpTableApiBuff.tsc = 3;
   chnGrpTableApiBuff.band = GSM_1800;
   chnGrpTableApiBuff.validArfcns = 4;
   chnGrpTableApiBuff.arfcn1 = 700;
   chnGrpTableApiBuff.arfcn2 = 725;
   chnGrpTableApiBuff.arfcn3 = 600;
   chnGrpTableApiBuff.arfcn4 = 600;
   if(CLIB_SUCCESS == insertChnGrpTable(&chnGrpTableApiBuff))
   {
     printf("Insert ChnGrp Successfull\n");
   }
   else
   {
      printf("Insert ChnGrp Unsuccessfull\n");
   }
}


void insertIntoArfcnListTable(I_U32 band, I_U32 arfcn)
{
   ArfcnListTableApi arfcnListTableApiBuff;
   arfcnListTableApiBuff.band = band;
   arfcnListTableApiBuff.arfcn = arfcn;
   if(CLIB_SUCCESS == insertArfcnListTable(&arfcnListTableApiBuff))
   {
     printf("Insert ArfcnList Successfull\n");
   }
   else
   {
      printf("Insert ArfcnList Unsuccessfull\n");
   }

}

void insertIntoFrLinkExtE1TsMccE1TsMapTable(I_U16 frChnId, I_U16 e1Id, I_U16 numRows)
{
   I_U16 i = 0;

   for (i = 0; i < numRows; i++)
   {
      FrLinkExtE1TsMccE1TsMapTableApi frLinkExtE1TsMccE1TsMapTableApiBuff;
      frLinkExtE1TsMccE1TsMapTableApiBuff.frChnId = frChnId;
      frLinkExtE1TsMccE1TsMapTableApiBuff.e1Id = e1Id;
      frLinkExtE1TsMccE1TsMapTableApiBuff.e1Ts = i;
      frLinkExtE1TsMccE1TsMapTableApiBuff.mccE1Id = 1;
      frLinkExtE1TsMccE1TsMapTableApiBuff.mccE1Ts = i + 1;
      frLinkExtE1TsMccE1TsMapTableApiBuff.mccStrmTs = i + 2;
   
      if(CLIB_SUCCESS == insertFrLinkExtE1TsMccE1TsMapTable(&frLinkExtE1TsMccE1TsMapTableApiBuff))
      {
         printf("Insert Fr Successfull\n");
      }
      else
      {
         printf("Insert Fr Unsuccessful\n");
      }

   }

}

void removeAllFromMlpppConfigTable()
{
   MlpppConfigTableApi *mlpppConfigTableApiAllPtr = NULL;
   MlpppConfigTableApi *mlpppConfigTableApiPtr = NULL;
   MlpppConfigTableIndices mlpppConfigTableIndicesBuff;
          
   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallMlpppConfigTable(&mlpppConfigTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          mlpppConfigTableApiPtr = (MlpppConfigTableApi *) (((I_U8 *) mlpppConfigTableApiAllPtr ) + (outSize * i));
          mlpppConfigTableIndicesBuff.mlpppLinkId = mlpppConfigTableApiPtr->mlpppLinkId;
          deleteMlpppConfigTable(&mlpppConfigTableIndicesBuff);
       }
       free(mlpppConfigTableApiAllPtr);

   }
   printf("Deletion from MlpppConfig Table successful\n");
}


void removeAllFromLinkTable()
{
   LinkTableApi *linkTableApiAllPtr = NULL;
   LinkTableApi *linkTableApiPtr = NULL;
   LinkTableIndices linkTableIndicesBuff;
          
   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallLinkTable(&linkTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          linkTableApiPtr = (LinkTableApi *) (((I_U8 *) linkTableApiAllPtr ) + (outSize * i));
          linkTableIndicesBuff.linksetID = linkTableApiPtr->linksetID;
          linkTableIndicesBuff.linkId = linkTableApiPtr->linkId;
          deleteLinkTable(&linkTableIndicesBuff); 
       }
       free(linkTableApiAllPtr);

   }
   printf("Deletion from Link Table successful\n");
}

void removeAllFromCicTable()
{
   CicTableApi *cicTableApiAllPtr = NULL;
   CicTableApi *cicTableApiPtr = NULL;
   CicTableIndices cicTableIndicesBuff;
          
   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallCicTable(&cicTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          cicTableApiPtr = (CicTableApi *) (((I_U8 *) cicTableApiAllPtr ) + (outSize * i));
          cicTableIndicesBuff.interfaceId = cicTableApiPtr->interfaceId;
          cicTableIndicesBuff.tgpId = cicTableApiPtr->tgpId;
          cicTableIndicesBuff.e1Num = cicTableApiPtr->e1Num;
          cicTableIndicesBuff.timeSlot = cicTableApiPtr->timeSlot;
          deleteCicTable(&cicTableIndicesBuff); 
       }
       free(cicTableApiAllPtr);

   }
   printf("Deletion from Cic successful\n");
}


void removeAllFromCellTable()
{
   CellPerTableApi *cellPerTableApiAllPtr = NULL;
   CellPerTableApi *cellPerTableApiPtr = NULL;
   CellPerTableIndices cellPerTableIndicesBuff;
          
   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallCellPerTable(&cellPerTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          cellPerTableApiPtr = (CellPerTableApi *) (((I_U8 *) cellPerTableApiAllPtr ) + (outSize * i));
          cellPerTableIndicesBuff.cellId = cellPerTableApiPtr->cellId;
          cellPerTableIndicesBuff.lac = cellPerTableApiPtr->lac;
          deleteCellPerTable(&cellPerTableIndicesBuff); 
       }
       free(cellPerTableApiAllPtr);

   }
   printf("Deletion from Cell Per Table successful\n");
}
void removeAllFromPsCellTable()
{
   PsCellTableApi *psCellTableApiAllPtr = NULL;
   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;
          
   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallPsCellTable(&psCellTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          psCellTableApiPtr = (PsCellTableApi *) (((I_U8 *) psCellTableApiAllPtr ) + (outSize * i));
          psCellTableIndicesBuff.cellId = psCellTableApiPtr->cellId;
          psCellTableIndicesBuff.lac = psCellTableApiPtr->lac;
          deletePsCellTable(&psCellTableIndicesBuff); 
       }
       free(psCellTableApiAllPtr);

   }
   printf("Deletion from PsCell successful\n");
}

void removeAllFromBssPsTable()
{
   BssPsTableApi *bssPsTableApiAllPtr = NULL;
   BssPsTableApi *bssPsTableApiPtr = NULL;

   BssPsTableIndices bssPsTableIndicesBuff;

   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallBssPsTable(&bssPsTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          bssPsTableApiPtr = (BssPsTableApi *) (((I_U8 *) bssPsTableApiAllPtr ) + (outSize * i));
          bssPsTableIndicesBuff.bssPsId = bssPsTableApiPtr->bssPsId;
          deleteBssPsTable(&bssPsTableIndicesBuff); 
       }
       free(bssPsTableApiAllPtr);

   }
   printf("Deletion from BssPs Table successful\n");
}

void removeAllFromBssPsPreConfigTable()
{
   BssPsPreConfigTableApi *bssPsPreConfigTableApiAllPtr = NULL;
   BssPsPreConfigTableApi *bssPsPreConfigTableApiPtr = NULL;

   BssPsPreConfigTableIndices bssPsPreConfigTableIndicesBuff;

   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallBssPsPreConfigTable(&bssPsPreConfigTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          bssPsPreConfigTableApiPtr = (BssPsPreConfigTableApi *) (((I_U8 *) bssPsPreConfigTableApiAllPtr ) + (outSize * i));
          bssPsPreConfigTableIndicesBuff.bssPsPreConfigIndex = bssPsPreConfigTableApiPtr->bssPsPreConfigIndex;
          deleteBssPsPreConfigTable(&bssPsPreConfigTableIndicesBuff); 
       }
       free(bssPsPreConfigTableApiAllPtr);

   }
   printf("Deletion from BssPsPreConfig Table successful\n");
}

void removeAllFromLaTable()
{
   LaTableApi *laTableApiAllPtr = NULL;
   LaTableApi *laTableApiPtr = NULL;
   LaTableIndices laTableIndicesBuff;
          
   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallLaTable(&laTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          laTableApiPtr = (LaTableApi *) (((I_U8 *) laTableApiAllPtr ) + (outSize * i));
          laTableIndicesBuff.lac = laTableApiPtr->lac;
          deleteLaTable(&laTableIndicesBuff); 
       }
       free(laTableApiAllPtr);

   }
   printf("Deletion from La successful\n");
}
void removeAllFromRaTable()
{
   RaTableApi *raTableApiAllPtr = NULL;
   RaTableApi *raTableApiPtr = NULL;
   RaTableIndices raTableIndicesBuff;
          
   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallRaTable(&raTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          raTableApiPtr = (RaTableApi *) (((I_U8 *) raTableApiAllPtr ) + (outSize * i));
          raTableIndicesBuff.rac = raTableApiPtr->rac;
          raTableIndicesBuff.lac = raTableApiPtr->lac;
          deleteRaTable(&raTableIndicesBuff); 
       }
       free(raTableApiAllPtr);

   }
   printf("Deletion from Ra successful\n");
}

void removeAllFromFrLinkTable()
{
   FrLinkTableApi *frLinkTableApiAllPtr = NULL;
   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkIndicesBuff;
          
   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallFrLinkTable(&frLinkTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          frLinkTableApiPtr = (FrLinkTableApi *) (((I_U8 *) frLinkTableApiAllPtr ) + (outSize * i));
          frLinkIndicesBuff.frChnId = frLinkTableApiPtr->frChnId;
          deleteFrLinkTable(&frLinkIndicesBuff); 
       }
       free(frLinkTableApiAllPtr);

   }
   printf("Deletion from FrLink successful\n");
}

void removeAllFromFrLinkExtE1TsMccE1TsMapTable()
{
   FrLinkExtE1TsMccE1TsMapTableApi *frLinkExtE1TsMccE1TsMapTableApiAllPtr= NULL;
   FrLinkExtE1TsMccE1TsMapTableApi *frLinkExtE1TsMccE1TsMapTableApiPtr = NULL;
   FrLinkExtE1TsMccE1TsMapTableIndices frLinkExtE1TsMccE1TsMapTableIndicesBuff;

   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallFrLinkExtE1TsMccE1TsMapTable(&frLinkExtE1TsMccE1TsMapTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          frLinkExtE1TsMccE1TsMapTableApiPtr = (FrLinkExtE1TsMccE1TsMapTableApi *) (((I_U8 *) frLinkExtE1TsMccE1TsMapTableApiAllPtr ) + (outSize * i));
          frLinkExtE1TsMccE1TsMapTableIndicesBuff.frChnId = frLinkExtE1TsMccE1TsMapTableApiAllPtr->frChnId;
          frLinkExtE1TsMccE1TsMapTableIndicesBuff.e1Id = frLinkExtE1TsMccE1TsMapTableApiAllPtr->e1Id;
          frLinkExtE1TsMccE1TsMapTableIndicesBuff.e1Ts = frLinkExtE1TsMccE1TsMapTableApiAllPtr->e1Ts;

          deleteFrLinkExtE1TsMccE1TsMapTable(&frLinkExtE1TsMccE1TsMapTableIndicesBuff);
       }
       free(frLinkExtE1TsMccE1TsMapTableApiAllPtr);

   }
   printf("Deletion from FrLinkExtE1TsMccE1TsMapTable successful\n");
}

void removeAllFromNsvcTable()
{
   NsvcTableApi *nsvcTableApiAllPtr = NULL;
   NsvcTableApi *nsvcTableApiPtr = NULL;
   NsvcTableIndices nsvcIndicesBuff;
          
   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallNsvcTable(&nsvcTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          nsvcTableApiPtr = (NsvcTableApi *) (((I_U8 *) nsvcTableApiAllPtr ) + (outSize * i));
          nsvcIndicesBuff.nsvcId = nsvcTableApiPtr->nsvcId;
          deleteNsvcTable(&nsvcIndicesBuff); 
       }
       free(nsvcTableApiAllPtr);

   }
   printf("Deletion from Nsvc table successful\n");
}

void setBssPsPreConfigTable()
{
   BssPsPreConfigTableApi bssPsPreConfigTableApiBuff;
   bssPsPreConfigTableApiBuff.bssPsPreConfigIndex   = 2;
//   bssPsPreConfigTableApiBuff.bscAbisSctpPort       = 1200;
//   bssPsPreConfigTableApiBuff.bscAbisUdpPort        = 1300;
   bssPsPreConfigTableApiBuff.tIpHeartbeatAbis      = 100;
   bssPsPreConfigTableApiBuff.maxNumTbfperBss       = 10;
   bssPsPreConfigTableApiBuff.maxNumTbfPerPdch      = 8;
   bssPsPreConfigTableApiBuff.maxNumTbfPerTrx       = 8;
   bssPsPreConfigTableApiBuff.maxNumTbfPerCell      = 32;
   bssPsPreConfigTableApiBuff.sttOffset2Phase       = 50;
   bssPsPreConfigTableApiBuff.t3142                 = 20;
   bssPsPreConfigTableApiBuff.tMsRelSup             = 10;
   bssPsPreConfigTableApiBuff.tPdchActSup           = 10;
   bssPsPreConfigTableApiBuff.tPdchRelSup           = 10;
   bssPsPreConfigTableApiBuff.t3168                 = 50;
   bssPsPreConfigTableApiBuff.t3192                 = 50;
   bssPsPreConfigTableApiBuff.drxTimerMax           = 10;
   bssPsPreConfigTableApiBuff.bsCvMax               = 15;  
   bssPsPreConfigTableApiBuff.panDec                = 10;
   bssPsPreConfigTableApiBuff.panInc                = 10;
   bssPsPreConfigTableApiBuff.panMax                = 10;
   bssPsPreConfigTableApiBuff.alpha                 = 10; 
   bssPsPreConfigTableApiBuff.pcMeasChan            = 2;
   if(CLIB_SUCCESS == insertBssPsPreConfigTable(&bssPsPreConfigTableApiBuff))
   {
      printf("Insert BssPsPreConfig Successful\n");
   }   
   else
   {
      printf("Insert BssPsPreConfig Unsuccessful\n");
   }
}

void setGbInterfaceTable()
{
   GbInterfaceTableApi gbInterfaceTableApiBuff;
   gbInterfaceTableApiBuff.gbIfIndex          = 2;
   gbInterfaceTableApiBuff.nsei               = 10;
   gbInterfaceTableApiBuff.maxNumNsvcsOverFr  = 5;
   gbInterfaceTableApiBuff.maxNumNsvcsOverIp  = 0;
   gbInterfaceTableApiBuff.maxNumLeps         = 20;
   gbInterfaceTableApiBuff.maxNumReps         = 20;
   gbInterfaceTableApiBuff.transportType      = FR;
   gbInterfaceTableApiBuff.tFcC               = 10;
   gbInterfaceTableApiBuff.tFcTh              = 100;
   gbInterfaceTableApiBuff.tFcSup             = 8;
   gbInterfaceTableApiBuff.nMaxFcRep          = 1;
   if(CLIB_SUCCESS == insertGbInterfaceTable(&gbInterfaceTableApiBuff))
   {
      printf("Insert Gb Interface Successful\n");
   }
   else
   {
      printf("Insert Gb Interface Unsuccessful\n");
      if(CLIB_SUCCESS == updateGbInterfaceTable(&gbInterfaceTableApiBuff))
      {
         printf("Update Gb Interface Successful\n");
      }
      else
      {
         printf("Update Gb Interface Unsuccessful\n");
      }
   }
}

void setE1PerTable()
{
   TrunkTableApi trunkTableApiBuff;
   trunkTableApiBuff.e1Num        = 1; 
   trunkTableApiBuff.adminState   = LOCKED;
   trunkTableApiBuff.usageType    = SYS_E1_USAGE_AIF;
   trunkTableApiBuff.usingEntity  = 32;
   trunkTableApiBuff.trunkPortId  = 2;
   trunkTableApiBuff.mapAction    = 32;
   trunkTableApiBuff.e1Category   = 32;
   if(CLIB_SUCCESS == insertE1PerTable(&trunkTableApiBuff))
   {
      printf("Insert E1 Per table successful\n");
   }
   else
   {
      printf("Insert E1 per table Unsuccessful\n");
   }
}
void updateGprsEnabledInBssTable(I_U16 bssIndex, I_Bool gprsEnabled)
{
   BssTableApi *bssTableApiPtr = NULL;
   BssTableIndices bssTableIndicesBuff;
   bssTableIndicesBuff.bscId = bssIndex;
   if(CLIB_SUCCESS == getBssTable(&bssTableIndicesBuff, &bssTableApiPtr))
   {
      bssTableApiPtr->gprsEnabled = gprsEnabled;
      if(CLIB_SUCCESS == updateBssTable(bssTableApiPtr))
      {
         printf("Gprs Enabled for BSC ID %d set to %d",bssIndex, gprsEnabled);
      }
   }
}
void insertIntoBssTable(I_U16 bssIndex, I_U32 adminState)
{
   gBssTableApiBuff.bscId                    = bssIndex;
   gBssTableApiBuff.adminState               = adminState;
   //gBssTableApiBuff.bssReset               =;
   gBssTableApiBuff.gprsEnabled              = TRUE;
   //gBssTableApiBuff.callReestablishmentInd =;
   //gBssTableApiBuff.attInd                 =;
   //gBssTableApiBuff.t3212                  =;
   //gBssTableApiBuff.mcc                    =;
   //gBssTableApiBuff.mnc                    =;
   //gBssTableApiBuff.ncc                    =;
   //gBssTableApiBuff.nccPermitted           =;
   //gBssTableApiBuff.dtxDnLinkInd           =;
   //gBssTableApiBuff.dtxUpLinkInd           =;
   //gBssTableApiBuff.minChannelGap          =;
   //gBssTableApiBuff.txInteger              =;
   //gBssTableApiBuff.radioLinkTimeout       =;
   //gBssTableApiBuff.maxRetrans             =;
   //gBssTableApiBuff.shutdownTimer          =;
   //gBssTableApiBuff.cicMaster              =;
   //gBssTableApiBuff.tHandRqd               =;
   //gBssTableApiBuff.bssapTimer8            =;
   //gBssTableApiBuff.bssapTimer7            =;
   if(CLIB_SUCCESS == insertBssTable(&gBssTableApiBuff))
   {
      printf("Insert in BssTable Successful\n");
   }
   else
   {
      printf("Insert in BssTable UnSuccessful\n");
   }
}

void setCellPerTable()
{
   CellPerTableApi cellPerTableApiBuff;
   cellPerTableApiBuff.lac                     = 10;
   cellPerTableApiBuff.cellId                  = 10;
   cellPerTableApiBuff.adminState              = LOCKED;
   //cellPerTableApiBuff.antennaId               =;
   //cellPerTableApiBuff.bcchArfcn               =;
   //cellPerTableApiBuff.freqBandBcch            =;
   //cellPerTableApiBuff.bcc                     =;
   //cellPerTableApiBuff.bcchPwr                 =;
   //cellPerTableApiBuff.msTxPwrMax              =;
   //cellPerTableApiBuff.msTxPowerMaxCch         =;
   //cellPerTableApiBuff.fnOffset                =;
   cellPerTableApiBuff.psAllowed               = TRUE;
   //cellPerTableApiBuff.cellBarAccess           =;
   //cellPerTableApiBuff.accessCtrlClass         =;
   //cellPerTableApiBuff.bsAgBlksRes             =;
   //cellPerTableApiBuff.bsPaMfrms               =;
   //cellPerTableApiBuff.cellReselectHysteresis  =;
   //cellPerTableApiBuff.rxLevAccessMin          =;
   //cellPerTableApiBuff.powerOffset             =;
   //cellPerTableApiBuff.cbq                     =;
   //cellPerTableApiBuff.cellReselectOffset      =;
   //cellPerTableApiBuff.tempOffset              =;
   //cellPerTableApiBuff.penalityTime            =; 
   if(CLIB_SUCCESS == insertCellPerTable(&cellPerTableApiBuff))
   {
      printf("Insert in CellPerTable Successful\n");
   }
   else
   {
      printf("Insert in CellPerTable UnSuccessful\n");
   }
}

void setRaTable()
{
   RaTableApi raTableApiBuff;
   raTableApiBuff.rac = 5;
   raTableApiBuff.lac = 10;
   if(CLIB_SUCCESS == insertRaTable(&raTableApiBuff))
   {
      printf("Insert In Ra Table Successful\n");
   }
   else
   {
      printf("Insert in Ra Table Unsuccessful\n");
   }
}

void setArfcnListTable(CellPerTableApi *cellPerTableApiPtr)
{
   ArfcnListTableApi arfcnListTableApiBuff;
   arfcnListTableApiBuff.band  = cellPerTableApiPtr->freqBandBcch; 
   arfcnListTableApiBuff.arfcn = cellPerTableApiPtr->bcchArfcn; 
   if(CLIB_SUCCESS == insertArfcnListTable(&arfcnListTableApiBuff))
   {
      printf("Insert in Arfcn Table Successful\n");
   }
   else
   {  
      printf("Insert in Arfcn Table Unsuccessful\n");
   }
}

void setBssPsTable()
{
   BssPsTableApi bssPsTableApiBuff;
   bssPsTableApiBuff.bssPsId       = 2;
   bssPsTableApiBuff.nmo           = 1;
   bssPsTableApiBuff.sgsnr         = 1;
   bssPsTableApiBuff.tAvgW         = 24;
   bssPsTableApiBuff.tAvgT         = 24;
   bssPsTableApiBuff.nAvgI         = 13;
   bssPsTableApiBuff.maxNumPdchBss = MAX_NUM_PDCH_PER_BSS - 1;
   if(CLIB_SUCCESS == insertBssPsTable(&bssPsTableApiBuff))
   {
      printf("Insert in BssPs Table Successful\n");
   }
   else
   {
      printf("Insert in BssPs Table Unsuccessful\n");
   }
}

void removeCellPerTable(I_U32 cellId, I_U32 lac)
{
   CellPerTableIndices cellPerTableIndicesBuff;
   cellPerTableIndicesBuff.cellId = cellId;
   cellPerTableIndicesBuff.lac = lac;
   if(CLIB_SUCCESS == deleteCellPerTable(&cellPerTableIndicesBuff))
   {
      LOG_PRINT(LOG_INFO,"Delete from Cell Per table Successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Delete from Cell Per table Unsuccessfull\n");
   }
}


void CfgDelHndlr1()
{
   static int testInitiation = 1;
   CellPerTableApi *cellTableApiPtr = NULL;
   CellPerTableIndices cellTableIndicesBuff;
   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;
   I_U16 lac = 1;
   I_U8 rac = 1;
   I_U16 cellId = 1;
    

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/

      /* delete  From table */
      removeAllFromPsCellTable();
      removeAllFromCellTable(); 
      removeAllFromLaTable();

      insertIntoLaTable(lac);
      insertIntoPsCellTable(cellId, lac, rac);
      insertIntoCellTable(cellId, lac, LOCKED, 1); /*PS_ALLOWED*/
      
      CellDataStruct cellDataStructBuff;
      cellDataStructBuff.CellState    = locked;/*As required*/
      cellDataStructBuff.Availlability = FALSE;
      cellDataStructBuff.CellID       = 1;
      cellDataStructBuff.adminState= 0;
      cellDataStructBuff.lac= 1;
      cellDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&cellDataStructBuff, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);


      cellTableIndicesBuff.cellId = cellId;
      cellTableIndicesBuff.lac = lac;
      if (CLIB_SUCCESS == getCellPerTable(&cellTableIndicesBuff, &cellTableApiPtr))
      {
         cfgStubSendCmMessage(cellTableApiPtr,sizeof(CellPerTableApi),BSC_API_DEL_CELLPERTABLE);

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

void CfgDelHndlr2()
{
   static int testInitiation = 1;
   CellPerTableApi *cellTableApiPtr = NULL;
   CellPerTableIndices cellTableIndicesBuff;
   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;
   I_U16 lac = 1;
   I_U8 rac = 1;
   I_U16 cellId = 1;
    

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/


 /* delete  From table */
      removeAllFromPsCellTable();
      removeAllFromCellTable();
      removeAllFromLaTable();

      insertIntoLaTable(lac);
//      insertIntoPsCellTable(cellId, lac, rac);
      insertIntoCellTable(cellId, lac, LOCKED, 1); /*PS_ALLOWED*/

      CellDataStruct cellDataStructBuff;
      cellDataStructBuff.CellState    = locked;/*As required*/
      cellDataStructBuff.Availlability = FALSE;
      cellDataStructBuff.CellID       = 1;
      cellDataStructBuff.adminState= 0;
      cellDataStructBuff.lac= 1;
      cellDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&cellDataStructBuff, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);


      cellTableIndicesBuff.cellId = cellId;
      cellTableIndicesBuff.lac = lac;
      if (CLIB_SUCCESS == getCellPerTable(&cellTableIndicesBuff, &cellTableApiPtr))
      {
         cfgStubSendCmMessage(cellTableApiPtr,sizeof(CellPerTableApi),BSC_API_DEL_CELLPERTABLE);

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

void CfgDelHndlr3()
{
   static int testInitiation = 1;
   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;
   I_U16 lac = 1;
   I_U8 rac = 1;
   I_U16 cellId = 1;
    

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/

      /* delete  From table */
      removeAllFromPsCellTable();
      removeAllFromCellTable(); 
      insertIntoLaTable(lac);
      insertIntoPsCellTable(cellId, lac, rac);
      insertIntoCellTable(cellId, lac, UNLOCKED, 1); /*PS_ALLOWED*/

      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
 
      CellDataStruct cellDataStructBuff;
      cellDataStructBuff.CellState    = unlockedEnabled;/*As required*/
      cellDataStructBuff.Availlability = FALSE;
      cellDataStructBuff.CellID       = 1;
      cellDataStructBuff.adminState= 0;
      cellDataStructBuff.lac= 1;
      cellDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&cellDataStructBuff, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      if (CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_DEL_PSCELLTABLE);

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

void CfgDelHndlr4()
{
   static int testInitiation = 1;
   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;
   I_U16 lac = 1;
   I_U8 rac = 1;
   I_U16 cellId = 1;
    

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/

      /* delete  From table */
      removeAllFromPsCellTable();
      removeAllFromCellTable(); 
      insertIntoLaTable(lac);
      insertIntoPsCellTable(cellId, lac, rac);
      insertIntoCellTable(cellId, lac, LOCKED, 1); /*PS_ALLOWED*/

      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
 
      CellDataStruct cellDataStructBuff;
      cellDataStructBuff.CellState    = locked; /*As required*/
      cellDataStructBuff.Availlability = FALSE;
      cellDataStructBuff.CellID       = 1;
      cellDataStructBuff.adminState= 0;
      cellDataStructBuff.lac= 1;
      cellDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&cellDataStructBuff, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      if (CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         cfgStubSendCmMessage(psCellTableApiPtr,sizeof(PsCellTableApi),BSC_API_DEL_PSCELLTABLE);

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
void CfgDelHndlr5()
{
   static int testInitiation = 1;
   RaTableApi *raTableApiPtr = NULL;
   RaTableIndices raTableIndicesBuff;
   I_U16 lac = 1;
   I_U8 rac = 1;
   I_U16 cellId = 1;
    

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/

      /* delete  From table */
      removeAllFromRaTable();
      removeAllFromLaTable();
      removeAllFromPsCellTable();
    
      insertIntoLaTable(lac);
      insertIntoRaTable(lac, rac);
      insertIntoPsCellTable(cellId, lac, rac);

      raTableIndicesBuff.rac = rac;
      raTableIndicesBuff.lac = lac;
 
      if (CLIB_SUCCESS == getRaTable(&raTableIndicesBuff, &raTableApiPtr))
      {
         cfgStubSendCmMessage(raTableApiPtr,sizeof(RaTableApi),BSC_API_DEL_RATABLE);

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

void CfgDelHndlr6()
{
   static int testInitiation = 1;
   RaTableApi *raTableApiPtr = NULL;
   RaTableIndices raTableIndicesBuff;
   I_U16 lac = 1;
   I_U8 rac = 1;
   I_U16 cellId = 1;
    

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/

      /* delete  From table */
      removeAllFromRaTable();
      removeAllFromLaTable();
      removeAllFromPsCellTable();
    
      insertIntoLaTable(lac);
      insertIntoRaTable(lac, rac);

      raTableIndicesBuff.rac = rac;
      raTableIndicesBuff.lac = lac;
 
      if (CLIB_SUCCESS == getRaTable(&raTableIndicesBuff, &raTableApiPtr))
      {
         cfgStubSendCmMessage(raTableApiPtr,sizeof(RaTableApi),BSC_API_DEL_RATABLE);

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
void CfgDelHndlr7()
{
   static int testInitiation = 1;
   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkTableIndicesBuff;
   I_U16 frChnId = 1;
   I_U16 e1Id = 1;
   I_U16 nsvcId = 1;
    

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/

      /* delete  From table */
      removeAllFromFrLinkTable();
      removeAllFromNsvcTable();

      insertIntoNsvcTable(nsvcId, frChnId, UNLOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);
      sleep(1);      
      frLinkTableIndicesBuff.frChnId = frChnId;
      if (CLIB_SUCCESS == getFrLinkTable(&frLinkTableIndicesBuff, &frLinkTableApiPtr))
      {
         cfgStubSendCmMessage(frLinkTableApiPtr,sizeof(FrLinkTableApi),BSC_API_DEL_FRLINKTABLE);      
     
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
void CfgDelHndlr8()
{
   static int testInitiation = 1;
   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkTableIndicesBuff;
   I_U16 frChnId = 1;
   I_U16 e1Id = 1;
   I_U16 nsvcId = 1;
    

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/

      /* delete  From table */
      removeAllFromFrLinkTable();
      removeAllFromNsvcTable();

      insertIntoFrLinkTable(frChnId, e1Id);
      sleep(1);      
      frLinkTableIndicesBuff.frChnId = frChnId;
      if (CLIB_SUCCESS == getFrLinkTable(&frLinkTableIndicesBuff, &frLinkTableApiPtr))
      {
         cfgStubSendCmMessage(frLinkTableApiPtr,sizeof(FrLinkTableApi),BSC_API_DEL_FRLINKTABLE);      
     
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
void CfgDelHndlr9()
{
   static int testInitiation =1;

   I_U16 gbIfIndex = 1;
   I_S8 lepInfoIndex [25] = "172.31.123.72";
   I_U16 bscIndex = 1;

   LepInfoTableApi *lepInfoTableApiPtr = NULL;
   LepInfoTableIndices lepinfoTableIndicesBuff;


   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromGbInterfaceTable();
      removeAllFromLepInfoTable();
      removeAllFromBssTable(); 

      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoLepInfoTable(lepInfoIndex); 
      insertIntoBssTable(bscIndex, UNLOCKED);
      sleep(1);
      strncpy(lepinfoTableIndicesBuff.lep,  lepInfoIndex, 25);

      if( CLIB_SUCCESS == getLepInfoTable(&lepinfoTableIndicesBuff, &lepInfoTableApiPtr))
      {
         /* Now Send BSS UNLOCK to the CFG message */
//         gBssTableApiBuff.adminState = UNLOCKED;  
//         cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
     
//         cfgStubSendCmMessage(lepInfoTableApiPtr, sizeof(LepInfoTableApi), BSC_API_UNLOCK_BSS);
         cfgStubSendCmMessage(lepInfoTableApiPtr,sizeof(LepInfoTableApi),BSC_API_DEL_LEPINFOTABLE);
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

void CfgDelHndlr10()
{
   static int testInitiation =1;

   I_U16 gbIfIndex = 1;
   I_S8 lepInfoIndex [25] = "172.31.123.72";
   I_U16 bscIndex = 1;

   LepInfoTableApi *lepInfoTableApiPtr = NULL;
   LepInfoTableIndices lepinfoTableIndicesBuff;


   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromGbInterfaceTable();
      removeAllFromLepInfoTable();
      removeAllFromBssTable(); 

      insertIntoGbInterfaceTable(gbIfIndex, FR);
      insertIntoLepInfoTable(lepInfoIndex); 
      insertIntoBssTable(bscIndex, UNLOCKED);
      sleep(1);
      strncpy(lepinfoTableIndicesBuff.lep, lepInfoIndex, 25);

      if( CLIB_SUCCESS == getLepInfoTable(&lepinfoTableIndicesBuff, &lepInfoTableApiPtr))
      {
         /* Now Send BSS UNLOCK to the CFG message */
//         gBssTableApiBuff.adminState = UNLOCKED;  
//         cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
     
//         cfgStubSendCmMessage(lepInfoTableApiPtr, sizeof(LepInfoTableApi), BSC_API_UNLOCK_BSS);
         cfgStubSendCmMessage(lepInfoTableApiPtr,sizeof(LepInfoTableApi),BSC_API_DEL_LEPINFOTABLE);
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
void CfgDelHndlr11()
{
   static int testInitiation =1;

   I_U16 gbIfIndex = 1;
   I_S8 lepInfoIndex [25] = "172.31.123.72";
   I_U16 bscIndex = 1;

   LepInfoTableApi *lepInfoTableApiPtr = NULL;
   LepInfoTableIndices lepinfoTableIndicesBuff;


   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromGbInterfaceTable();
      removeAllFromLepInfoTable();
      removeAllFromBssTable(); 

      insertIntoGbInterfaceTable(gbIfIndex, FR);
      insertIntoLepInfoTable(lepInfoIndex); 
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      strncpy(lepinfoTableIndicesBuff.lep, lepInfoIndex, 25);

      if( CLIB_SUCCESS == getLepInfoTable(&lepinfoTableIndicesBuff, &lepInfoTableApiPtr))
      {
//         cfgStubSendCmMessage(lepInfoTableApiPtr, sizeof(LepInfoTableApi), BSC_API_LOCK_BSS);
         cfgStubSendCmMessage(lepInfoTableApiPtr,sizeof(LepInfoTableApi),BSC_API_DEL_LEPINFOTABLE);
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
void CfgDelHndlr12()
{
   static int testInitiation =1;

   I_U16 bscIndex = 1;
   I_U16 gbIfIndex = 1;
   I_S8 repInfoIndex [25] = "172.31.123.72";

   RepInfoTableApi *repInfoTableApiPtr = NULL;
   RepInfoTableIndices repinfoTableIndicesBuff;


   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromGbInterfaceTable();
      removeAllFromRepInfoTable();
      removeAllFromBssTable(); 
      
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoRepInfoTable(repInfoIndex); 
      insertIntoBssTable(bscIndex, UNLOCKED);
      sleep(1);
       strncpy(repinfoTableIndicesBuff.rep, repInfoIndex, 25);

      if( CLIB_SUCCESS == getRepInfoTable(&repinfoTableIndicesBuff, &repInfoTableApiPtr))
      {
         /* Now Send BSS UNLOCK to the CFG message */
//         gBssTableApiBuff.adminState = UNLOCKED;  
//         cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
//         cfgStubSendCmMessage(repInfoTableApiPtr, sizeof(RepInfoTableApi), BSC_API_UNLOCK_BSS);
     
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_DEL_REPINFOTABLE);
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

void CfgDelHndlr13()
{
   static int testInitiation =1;

   I_U16 bscIndex = 1;
   I_U16 gbIfIndex = 1;
   I_S8 repInfoIndex [25] = "172.31.123.72";

   RepInfoTableApi *repInfoTableApiPtr = NULL;
   RepInfoTableIndices repinfoTableIndicesBuff;


   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromGbInterfaceTable();
      removeAllFromRepInfoTable();
      removeAllFromBssTable(); 
      
      insertIntoGbInterfaceTable(gbIfIndex, FR);
      insertIntoRepInfoTable(repInfoIndex); 
      insertIntoBssTable(bscIndex, UNLOCKED);
      sleep(1);
      strncpy(repinfoTableIndicesBuff.rep, repInfoIndex, 25);

      if( CLIB_SUCCESS == getRepInfoTable(&repinfoTableIndicesBuff, &repInfoTableApiPtr))
      {
         /* Now Send BSS UNLOCK to the CFG message */
//         gBssTableApiBuff.adminState = UNLOCKED;  
//         cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
//         cfgStubSendCmMessage(repInfoTableApiPtr, sizeof(RepInfoTableApi), BSC_API_UNLOCK_BSS);
     
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_DEL_REPINFOTABLE);
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
void CfgDelHndlr14()
{
   static int testInitiation =1;

   I_U16 bscIndex = 1;
   I_U16 gbIfIndex = 1;
   I_S8 repInfoIndex [25] = "172.31.123.72";

   RepInfoTableApi *repInfoTableApiPtr = NULL;
   RepInfoTableIndices repinfoTableIndicesBuff;


   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromGbInterfaceTable();
      removeAllFromRepInfoTable();
      removeAllFromBssTable(); 
      
      insertIntoGbInterfaceTable(gbIfIndex, FR);
      insertIntoRepInfoTable(repInfoIndex); 
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      strncpy(repinfoTableIndicesBuff.rep, repInfoIndex, 25);

      if( CLIB_SUCCESS == getRepInfoTable(&repinfoTableIndicesBuff, &repInfoTableApiPtr))
      {
         cfgStubSendCmMessage(repInfoTableApiPtr,sizeof(RepInfoTableApi),BSC_API_DEL_REPINFOTABLE);
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

/*no row in BssPsPreConfig Table */
void CfgSetHndlr1()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 e1Id = 1;

   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkTableIndicesBuff;


   if ( testInitiation >  0)
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeFromE1Table(e1Id);

      insertIntoE1Table(e1Id, LOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);

      frLinkTableIndicesBuff.frChnId = frChnId;
      if (CLIB_SUCCESS == getFrLinkTable(&frLinkTableIndicesBuff, &frLinkTableApiPtr))
      {
         frLinkTableApiPtr->numTs = frLinkTableApiPtr->numTs + 1;
	 cfgStubSendCmMessage(frLinkTableApiPtr, sizeof(FrLinkTableApi), BSC_API_SET_FRLINKTABLE);
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

/* Modify on Fr when NSVC is Unlocked */
void CfgSetHndlr2()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;

   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkTableIndicesBuff;


   if ( testInitiation > 0)
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromNsvcTable();
      removeFromE1Table(e1Id);

      setBssPsPreConfigTable();
      insertIntoE1Table(e1Id, LOCKED);
      insertIntoNsvcTable(nsvcId, frChnId, UNLOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);
      sleep(1);
      frLinkTableIndicesBuff.frChnId = frChnId;
      if (CLIB_SUCCESS == getFrLinkTable(&frLinkTableIndicesBuff, &frLinkTableApiPtr))
      {
         frLinkTableApiPtr->numTs = frLinkTableApiPtr->numTs + 1;
	 cfgStubSendCmMessage(frLinkTableApiPtr, sizeof(FrLinkTableApi), BSC_API_SET_FRLINKTABLE);
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

/* Add on Fr when Max rows already present */ 
void CfgSetHndlr3()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U32 i = 0;

   FrLinkTableApi frLinkTableApiBuff;
   FrLinkTableIndices frLinkTableIndicesBuff;


   if ( testInitiation > 0)
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromNsvcTable();
      removeFromE1Table(e1Id);

      setBssPsPreConfigTable();
      insertIntoE1Table(e1Id, LOCKED);
      insertIntoNsvcTable(nsvcId, frChnId, LOCKED);

      for (i = 0; i < 1; i++)   /* CFG_MAX_NUM_NSVCS = 1*/
      {
         insertIntoFrLinkTable((frChnId + i + 1), e1Id);

         frLinkTableIndicesBuff.frChnId = frChnId + i + 1;
          
      }
      sleep(1);      
      frLinkTableApiBuff.frChnId = frChnId;
      frLinkTableApiBuff.e1Id = e1Id;
      frLinkTableApiBuff.startTs = 1;
      frLinkTableApiBuff.numTs = 1;
      cfgStubSendCmMessage(&frLinkTableApiBuff, sizeof(FrLinkTableApi), BSC_API_SET_FRLINKTABLE);
    
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

/*Add on Fr when E1 is not present in E1 Tabel */
void CfgSetHndlr4()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;

   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkTableIndicesBuff;


   if ( testInitiation > 0)
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromNsvcTable();
      removeFromE1Table(e1Id);

      setBssPsPreConfigTable();
      insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);
      sleep(1);
      frLinkTableIndicesBuff.frChnId = frChnId;
      if (CLIB_SUCCESS == getFrLinkTable(&frLinkTableIndicesBuff, &frLinkTableApiPtr))
      {
         frLinkTableApiPtr->numTs = frLinkTableApiPtr->numTs + 1;
	 cfgStubSendCmMessage(frLinkTableApiPtr, sizeof(FrLinkTableApi), BSC_API_SET_FRLINKTABLE);
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

/* Modify on Fr when timeslot is already in another Fr Link */
void CfgSetHndlr5()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;

   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkTableIndicesBuff;


   if ( testInitiation > 0)
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromNsvcTable();
      removeFromE1Table(e1Id);

      setBssPsPreConfigTable();
      insertIntoE1Table(e1Id, LOCKED);
      insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);

      insertIntoFrLinkTable(frChnId + 1, e1Id);

      frLinkTableIndicesBuff.frChnId = frChnId;
      if (CLIB_SUCCESS == getFrLinkTable(&frLinkTableIndicesBuff, &frLinkTableApiPtr))
      {
         frLinkTableApiPtr->startTs = 2;
         frLinkTableApiPtr->numTs = 3;
	 cfgStubSendCmMessage(frLinkTableApiPtr, sizeof(FrLinkTableApi), BSC_API_SET_FRLINKTABLE);
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

/* Modify on Fr when timeslot is already in another Cic */
void CfgSetHndlr6()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 cicId = 1;

   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkTableIndicesBuff;


   if ( testInitiation > 0)
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromCicTable();
      removeAllFromNsvcTable();
      removeFromE1Table(e1Id);

      setBssPsPreConfigTable();
      insertIntoE1Table(e1Id, LOCKED);
      insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
      insertIntoCicTable(cicId, e1Id, 2);
      insertIntoFrLinkTable(frChnId, e1Id);
      sleep(1);
      frLinkTableIndicesBuff.frChnId = frChnId;
      if (CLIB_SUCCESS == getFrLinkTable(&frLinkTableIndicesBuff, &frLinkTableApiPtr))
      {
         frLinkTableApiPtr->startTs = 2;
         frLinkTableApiPtr->numTs = 2;
	 cfgStubSendCmMessage(frLinkTableApiPtr, sizeof(FrLinkTableApi), BSC_API_SET_FRLINKTABLE);
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

/* Modify on Fr when timeslot is already in another Mtp2 Link */
void CfgSetHndlr7()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linksetId = 1;
   I_U16 linkId = 1;

   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromLinkTable();
      removeAllFromNsvcTable();
      removeFromE1Table(e1Id);
      removeAllFromCicTable();

      setBssPsPreConfigTable();
      insertIntoE1Table(e1Id, LOCKED);
      insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
      insertIntoLinkTable(linksetId, linkId, e1Id, 2, UNLOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);
      sleep(1);
      frLinkTableIndicesBuff.frChnId = frChnId;
      if (CLIB_SUCCESS == getFrLinkTable(&frLinkTableIndicesBuff, &frLinkTableApiPtr))
      {
         frLinkTableApiPtr->startTs = 2;
         frLinkTableApiPtr->numTs = 2;
	 cfgStubSendCmMessage(frLinkTableApiPtr, sizeof(FrLinkTableApi), BSC_API_SET_FRLINKTABLE);
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

/* Modify on Fr when timeslot is already in another Mlpp Link */
void CfgSetHndlr8()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;

   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromLinkTable();
      removeAllFromNsvcTable();
      removeFromE1Table(e1Id);

      setBssPsPreConfigTable();
      insertIntoE1Table(e1Id, LOCKED);
      insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);
      insertIntoMlppConfigTable(e1Id,2);
      sleep(1);
      frLinkTableIndicesBuff.frChnId = frChnId;
      if (CLIB_SUCCESS == getFrLinkTable(&frLinkTableIndicesBuff, &frLinkTableApiPtr))
      {
         frLinkTableApiPtr->startTs = 2;
         frLinkTableApiPtr->numTs = 2;
	 cfgStubSendCmMessage(frLinkTableApiPtr, sizeof(FrLinkTableApi), BSC_API_SET_FRLINKTABLE);
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

void CfgSetHndlr9()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;

   FrLinkTableApi *frLinkTableApiPtr = NULL;
   FrLinkTableIndices frLinkTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromLinkTable();
      removeAllFromNsvcTable();
      removeFromE1Table(e1Id);

      setBssPsPreConfigTable();
      insertIntoE1Table(e1Id, LOCKED);
      setUsageTypeInE1Table(e1Id,SYS_E1_USAGE_ABISIF);
      insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);
      insertIntoMlppConfigTable(e1Id,2);
      sleep(1);
      frLinkTableIndicesBuff.frChnId = frChnId;
      if (CLIB_SUCCESS == getFrLinkTable(&frLinkTableIndicesBuff, &frLinkTableApiPtr))
      {
         frLinkTableApiPtr->startTs = 2;
         frLinkTableApiPtr->numTs = 2;
	 cfgStubSendCmMessage(frLinkTableApiPtr, sizeof(FrLinkTableApi), BSC_API_SET_FRLINKTABLE);
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

/*Test cases for Consistency Checks on Set On Nsvc Table*/
void CfgSetHndlr10()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;

   NsvcTableApi *nsvcTableApiPtr = NULL;
   NsvcTableIndices nsvcTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromLinkTable();
      removeAllFromNsvcTable();
      removeFromE1Table(e1Id);

//      setBssPsPreConfigTable();
//      insertIntoE1Table(e1Id, LOCKED);
//      setUsageTypeInE1Table(e1Id,SYS_E1_USAGE_ABISIF);
//        insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
//      insertIntoFrLinkTable(frChnId, e1Id);
//      insertIntoMlppConfigTable(e1Id,2);
      sleep(1);
      nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
      nsvcTableApiPtr->nsvcId = nsvcId;
      nsvcTableApiPtr->adminState = locked;
      nsvcTableApiPtr->frChnId = frChnId; 
      nsvcTableApiPtr->dlci = 20;
      cfgStubSendCmMessage(nsvcTableApiPtr, sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE);
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


void CfgSetHndlr11()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;

   NsvcTableApi *nsvcTableApiPtr = NULL;
   NsvcTableIndices nsvcTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromLinkTable();
      removeAllFromNsvcTable();
      removeFromE1Table(e1Id);

//      setBssPsPreConfigTable();
//      insertIntoE1Table(e1Id, LOCKED);
//      setUsageTypeInE1Table(e1Id,SYS_E1_USAGE_ABISIF);
//        insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
        insertIntoFrLinkTable(frChnId, e1Id);
//      insertIntoMlppConfigTable(e1Id,2);
      sleep(1);
      nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
      nsvcTableApiPtr->nsvcId = nsvcId;
      nsvcTableApiPtr->adminState = locked;
      nsvcTableApiPtr->frChnId = frChnId; 
      nsvcTableApiPtr->dlci = 20;
      cfgStubSendCmMessage(nsvcTableApiPtr, sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE);
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


void CfgSetHndlr12()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   NsvcTableApi *nsvcTableApiPtr = NULL;
   NsvcTableIndices nsvcTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromLinkTable();
      removeAllFromNsvcTable();
      removeAllFromGbInterfaceTable();
      removeFromE1Table(e1Id);

      setBssPsPreConfigTable();
//    insertIntoE1Table(e1Id, LOCKED);
//    setUsageTypeInE1Table(e1Id,SYS_E1_USAGE_ABISIF);
      insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);
      insertIntoGbInterfaceTable(gbIfIndex, FR);
      setMaxNumNsvcsIngbInterfaceTable(gbIfIndex, FR, 1);
//    insertIntoMlppConfigTable(e1Id,2);
      sleep(1);
      nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
      nsvcTableApiPtr->nsvcId = nsvcId+1;
      nsvcTableApiPtr->adminState = locked;
      nsvcTableApiPtr->frChnId = frChnId; 
      nsvcTableApiPtr->dlci = 20;
      cfgStubSendCmMessage(nsvcTableApiPtr, sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE);
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


void CfgSetHndlr13()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   NsvcTableApi *nsvcTableApiPtr = NULL;
   NsvcTableIndices nsvcTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromLinkTable();
      removeAllFromNsvcTable();
      removeAllFromGbInterfaceTable();
      removeFromE1Table(e1Id);

      setBssPsPreConfigTable();
//    insertIntoE1Table(e1Id, LOCKED);
//    setUsageTypeInE1Table(e1Id,SYS_E1_USAGE_ABISIF);
      insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);
      insertIntoGbInterfaceTable(gbIfIndex, FR);
//      setMaxNumNsvcsIngbInterfaceTable(gbIfIndex, FR, 1);
//    insertIntoMlppConfigTable(e1Id,2);
      sleep(1);
      nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
      nsvcTableApiPtr->nsvcId = nsvcId+1;
      nsvcTableApiPtr->adminState = locked;
      nsvcTableApiPtr->frChnId = frChnId; 
      nsvcTableApiPtr->dlci = 20;
      cfgStubSendCmMessage(nsvcTableApiPtr, sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE);
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

void CfgSetHndlr14()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   NsvcTableApi *nsvcTableApiPtr = NULL;
   NsvcTableIndices nsvcTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromLinkTable();
      removeAllFromNsvcTable();
      removeAllFromGbInterfaceTable();
      removeFromE1Table(e1Id);

      setBssPsPreConfigTable();
//    insertIntoE1Table(e1Id, LOCKED);
//    setUsageTypeInE1Table(e1Id,SYS_E1_USAGE_ABISIF);
//    insertIntoNsvcTable(nsvcId, frChnId, LOCKED);
      insertIntoFrLinkTable(frChnId, e1Id);
      insertIntoGbInterfaceTable(gbIfIndex, FR);
      setMaxNumNsvcsIngbInterfaceTable(gbIfIndex, FR, 1);
//    insertIntoMlppConfigTable(e1Id,2);
      sleep(1);
      nsvcTableApiPtr = (NsvcTableApi*)calloc(1, sizeof(NsvcTableApi));
      nsvcTableApiPtr->nsvcId = nsvcId;
      nsvcTableApiPtr->adminState = locked;
      nsvcTableApiPtr->frChnId = frChnId; 
      nsvcTableApiPtr->dlci = 20;
      cfgStubSendCmMessage(nsvcTableApiPtr, sizeof(NsvcTableApi), BSC_API_SET_NSVCTABLE);
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
/*Test cases for Consistency Checks on Set On Nsvc Table---END*/

void CfgSetHndlr15()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    lep[25]     = "10.100.211.72";
   I_U16    lepPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;

   LepInfoTableApi *lepInfoTableApiPtr = NULL;
   LepInfoTableIndices lepInfoTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromFrLinkTable();
      removeAllFromBssPsPreConfigTable();
      removeAllFromLinkTable();
      removeAllFromNsvcTable();
      removeAllFromGbInterfaceTable();
      removeFromE1Table(e1Id);

//      setBssPsPreConfigTable();
      sleep(1);
      lepInfoTableApiPtr = (LepInfoTableApi*)calloc(1, sizeof(LepInfoTableApi));
      strncpy(lepInfoTableApiPtr->lep, lep, 25);
      lepInfoTableApiPtr->lepPort = lepPort;
      lepInfoTableApiPtr->signallingWt = signallingWt; 
      lepInfoTableApiPtr->dataWt = dataWt;
      cfgStubSendCmMessage(lepInfoTableApiPtr, sizeof(LepInfoTableApi), BSC_API_SET_LEPINFOTABLE);
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


void CfgSetHndlr16()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    lep[25]     = "10.100.211.72";
   I_U16    lepPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   LepInfoTableApi *lepInfoTableApiPtr = NULL;
   LepInfoTableIndices lepInfoTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 

      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, UNLOCKED);
      sleep(1);
      lepInfoTableApiPtr = (LepInfoTableApi*)calloc(1, sizeof(LepInfoTableApi));
      strncpy(lepInfoTableApiPtr->lep, lep, 25);
      lepInfoTableApiPtr->lepPort = lepPort;
      lepInfoTableApiPtr->signallingWt = signallingWt; 
      lepInfoTableApiPtr->dataWt = dataWt;
      cfgStubSendCmMessage(lepInfoTableApiPtr, sizeof(LepInfoTableApi), BSC_API_SET_LEPINFOTABLE);
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

void CfgSetHndlr17()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    lep[25]     = "10.100.211.72";
   I_U16    lepPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   LepInfoTableApi *lepInfoTableApiPtr = NULL;
   LepInfoTableIndices lepInfoTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromLepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      insertIntoLepInfoTable(lep);
      sleep(1);
      lepInfoTableApiPtr = (LepInfoTableApi*)calloc(1, sizeof(LepInfoTableApi));
      sprintf(lep, "%s%d", lep, testInitiation);
      strncpy(lepInfoTableApiPtr->lep, lep, 25);
      lepInfoTableApiPtr->lepPort = lepPort;
      lepInfoTableApiPtr->signallingWt = signallingWt; 
      lepInfoTableApiPtr->dataWt = dataWt;
      cfgStubSendCmMessage(lepInfoTableApiPtr, sizeof(LepInfoTableApi), BSC_API_SET_LEPINFOTABLE);
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

void CfgSetHndlr18()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    lep[25]     = "10.100.211.72";
   I_U16    lepPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   LepInfoTableApi *lepInfoTableApiPtr = NULL;
   LepInfoTableIndices lepInfoTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromLepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      lepInfoTableApiPtr = (LepInfoTableApi*)calloc(1, sizeof(LepInfoTableApi));
      sprintf(lep, "%s%d", lep, testInitiation);
      strncpy(lepInfoTableApiPtr->lep, lep, 25);
      lepInfoTableApiPtr->lepPort = lepPort;
      lepInfoTableApiPtr->signallingWt = signallingWt; 
      lepInfoTableApiPtr->dataWt = dataWt;
      cfgStubSendCmMessage(lepInfoTableApiPtr, sizeof(LepInfoTableApi), BSC_API_SET_LEPINFOTABLE);
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

void CfgSetHndlr19()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   RepInfoTableApi *repInfoTableApiPtr = NULL;
   RepInfoTableIndices repInfoTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
//      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      repInfoTableApiPtr = (RepInfoTableApi*)calloc(1, sizeof(RepInfoTableApi));
      sprintf(rep, "%s%d", rep, testInitiation);
      strncpy(repInfoTableApiPtr->rep, rep, 25);
      repInfoTableApiPtr->repPort = repPort;
      repInfoTableApiPtr->signallingWt = signallingWt; 
      repInfoTableApiPtr->dataWt = dataWt;
      cfgStubSendCmMessage(repInfoTableApiPtr, sizeof(RepInfoTableApi), BSC_API_SET_REPINFOTABLE);
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

void CfgSetHndlr20()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   RepInfoTableApi *repInfoTableApiPtr = NULL;
   RepInfoTableIndices repInfoTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, UNLOCKED);
      sleep(1);
      repInfoTableApiPtr = (RepInfoTableApi*)calloc(1, sizeof(RepInfoTableApi));
      sprintf(rep, "%s%d", rep, testInitiation);
      strncpy(repInfoTableApiPtr->rep,  rep, 25);
      repInfoTableApiPtr->repPort = repPort;
      repInfoTableApiPtr->signallingWt = signallingWt; 
      repInfoTableApiPtr->dataWt = dataWt;
      cfgStubSendCmMessage(repInfoTableApiPtr, sizeof(RepInfoTableApi), BSC_API_SET_REPINFOTABLE);
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

void CfgSetHndlr21()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   RepInfoTableApi *repInfoTableApiPtr = NULL;
   RepInfoTableIndices repInfoTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      setMaxNumNsvcsIngbInterfaceTable(gbIfIndex,3,1);
      insertIntoBssTable(bscIndex, LOCKED);
      insertIntoRepInfoTable(rep);
      sleep(1);
      repInfoTableApiPtr = (RepInfoTableApi*)calloc(1, sizeof(RepInfoTableApi));
      sprintf(rep, "%s%d", rep, testInitiation);
      strncpy(repInfoTableApiPtr->rep,  rep, 25);
      repInfoTableApiPtr->repPort = repPort;
      repInfoTableApiPtr->signallingWt = signallingWt; 
      repInfoTableApiPtr->dataWt = dataWt;
      cfgStubSendCmMessage(repInfoTableApiPtr, sizeof(RepInfoTableApi), BSC_API_SET_REPINFOTABLE);
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

void CfgSetHndlr22()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   RepInfoTableApi *repInfoTableApiPtr = NULL;
   RepInfoTableIndices repInfoTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      repInfoTableApiPtr = (RepInfoTableApi*)calloc(1, sizeof(RepInfoTableApi));
      sprintf(rep, "%s%d", rep, testInitiation);
      strncpy(repInfoTableApiPtr->rep,  rep, 25);
      repInfoTableApiPtr->repPort = repPort;
      repInfoTableApiPtr->signallingWt = signallingWt; 
      repInfoTableApiPtr->dataWt = dataWt;
      cfgStubSendCmMessage(repInfoTableApiPtr, sizeof(RepInfoTableApi), BSC_API_SET_REPINFOTABLE);
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


void CfgSetHndlr23()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, UNLOCKED);
      sleep(1);
      gbInterfaceTableIndicesBuff.gbIfIndex = gbIfIndex;
      if(CLIB_SUCCESS == getGbInterfaceTable(&gbInterfaceTableIndicesBuff, &gbInterfaceTableApiPtr))
      {
         cfgStubSendCmMessage(gbInterfaceTableApiPtr, sizeof(GbInterfaceTableApi), BSC_API_SET_GBINTERFACETABLE);
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


void CfgSetHndlr24()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      gbInterfaceTableIndicesBuff.gbIfIndex = gbIfIndex;
      if(CLIB_SUCCESS == getGbInterfaceTable(&gbInterfaceTableIndicesBuff, &gbInterfaceTableApiPtr))
      {
         gbInterfaceTableApiPtr->gbIfIndex = gbIfIndex + 1;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr, sizeof(GbInterfaceTableApi), BSC_API_SET_GBINTERFACETABLE);
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

void CfgSetHndlr25()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      gbInterfaceTableIndicesBuff.gbIfIndex = gbIfIndex;
      if(CLIB_SUCCESS == getGbInterfaceTable(&gbInterfaceTableIndicesBuff, &gbInterfaceTableApiPtr))
      {
         gbInterfaceTableApiPtr->maxNumLeps++;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr, sizeof(GbInterfaceTableApi), BSC_API_SET_GBINTERFACETABLE);
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

void CfgSetHndlr26()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8   rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      gbInterfaceTableIndicesBuff.gbIfIndex = gbIfIndex;
      if(CLIB_SUCCESS == getGbInterfaceTable(&gbInterfaceTableIndicesBuff, &gbInterfaceTableApiPtr))
      {
         gbInterfaceTableApiPtr->maxNumNsvcsOverFr++;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr, sizeof(GbInterfaceTableApi), BSC_API_SET_GBINTERFACETABLE);
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


void CfgSetHndlr27()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      gbInterfaceTableIndicesBuff.gbIfIndex = gbIfIndex;
      if(CLIB_SUCCESS == getGbInterfaceTable(&gbInterfaceTableIndicesBuff, &gbInterfaceTableApiPtr))
      {
         gbInterfaceTableApiPtr->maxNumNsvcsOverIp++;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr, sizeof(GbInterfaceTableApi), BSC_API_SET_GBINTERFACETABLE);
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

void CfgSetHndlr28()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      gbInterfaceTableIndicesBuff.gbIfIndex = gbIfIndex;
      if(CLIB_SUCCESS == getGbInterfaceTable(&gbInterfaceTableIndicesBuff, &gbInterfaceTableApiPtr))
      {
         gbInterfaceTableApiPtr->maxNumReps++;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr, sizeof(GbInterfaceTableApi), BSC_API_SET_GBINTERFACETABLE);
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

void CfgSetHndlr29()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      gbInterfaceTableIndicesBuff.gbIfIndex = gbIfIndex;
      if(CLIB_SUCCESS == getGbInterfaceTable(&gbInterfaceTableIndicesBuff, &gbInterfaceTableApiPtr))
      {
         cfgStubSendCmMessage(gbInterfaceTableApiPtr, sizeof(GbInterfaceTableApi), BSC_API_SET_GBINTERFACETABLE);
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

void CfgSetHndlr30()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      gbInterfaceTableIndicesBuff.gbIfIndex = gbIfIndex;
      if(CLIB_SUCCESS == getGbInterfaceTable(&gbInterfaceTableIndicesBuff, &gbInterfaceTableApiPtr))
      {
         gbInterfaceTableApiPtr->tFcTh = 5;
         gbInterfaceTableApiPtr->tFcC = 10;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr, sizeof(GbInterfaceTableApi), BSC_API_SET_GBINTERFACETABLE);
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

void CfgSetHndlr31()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_S8    rep[25]     = "10.100.211.72";
   I_U16    repPort = 1100;
   I_U8    signallingWt = 20;
   I_U8    dataWt = 20;
   I_U16 bscIndex = 1;

   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      setBssPsPreConfigTable();
      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      gbInterfaceTableIndicesBuff.gbIfIndex = gbIfIndex;
      if(CLIB_SUCCESS == getGbInterfaceTable(&gbInterfaceTableIndicesBuff, &gbInterfaceTableApiPtr))
      {
         gbInterfaceTableApiPtr->tFcSup = 2;
         gbInterfaceTableApiPtr->nMaxFcRep = 8;
         gbInterfaceTableApiPtr->tFcC = 10;
         cfgStubSendCmMessage(gbInterfaceTableApiPtr, sizeof(GbInterfaceTableApi), BSC_API_SET_GBINTERFACETABLE);
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

void CfgSetHndlr32()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;

   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
//      setBssPsPreConfigTable();
//      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
        insertIntoPsCellTable(cellId, lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         psCellTableApiPtr->cellId = 2;
         psCellTableApiPtr->lac = 2;
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void CfgSetHndlr33()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;

   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
//    insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
      insertIntoCellTable(cellId,lac,UNLOCKED,1);
      insertIntoPsCellTable(cellId, lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void CfgSetHndlr34()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;

   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
      insertIntoCellTable(cellId,lac,LOCKED,1);
      insertIntoPsCellTable(cellId, lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         psCellTableApiPtr->maxNumPdchCell = 5;
         psCellTableApiPtr->minNumPdchCell = 6;
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void CfgSetHndlr35()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;

   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
      insertIntoCellTable(cellId,lac,LOCKED,1);
      insertIntoPsCellTable(cellId, lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void CfgSetHndlr36()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;

   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
      insertIntoCellTable(cellId,lac,LOCKED,1);
      insertIntoCellTable(cellId+1,lac+1,LOCKED,1);
      insertIntoPsCellTable(cellId, lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         psCellTableApiPtr->cellId++;
         psCellTableApiPtr->lac++;
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void CfgSetHndlr37()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;
   I_U32 i = 0;
   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
      for(i = 0; i<40;i++)
      {
         insertIntoCellTable(cellId + i,lac + i,LOCKED,1);
         insertIntoPsCellTable(cellId + i, lac + i, rac + i);
         insertIntoRaTable(lac + i, rac + i);
      }
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         psCellTableApiPtr->cellId = 41;
         psCellTableApiPtr->lac = 41;
         psCellTableApiPtr->bvciId = 51;
         
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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


void CfgSetHndlr38()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;
   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      removeAllFromPsCellTable();
      setBssPsPreConfigTable();
      insertIntoCellTable(cellId,lac,LOCKED,1);
      insertIntoPsCellTable(cellId, lac, rac);
      insertIntoRaTable(lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         psCellTableApiPtr->maxNumTbfPdch = 9;
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void CfgSetHndlr39()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;
   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
      insertIntoCellTable(cellId,lac,LOCKED,1);
      insertIntoRaTable(lac, rac);
      insertIntoPsCellTable(cellId, lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      CellDataStruct cellData;
      cellData.CellState = unlockOrEnableInProgress;
      cellData.CellID = cellId;
      cellData.Availlability = FALSE;
      cellData.lac = lac;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void CfgSetHndlr40()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;
   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
      insertIntoCellTable(cellId,lac,LOCKED,1);
      insertIntoRaTable(lac, rac);
      insertIntoPsCellTable(cellId, lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      CellDataStruct cellData;
      cellData.CellState = lockeOrDisableInProgress;
      cellData.CellID = cellId;
      cellData.Availlability = FALSE;
      cellData.lac = lac;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void CfgSetHndlr41()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;
   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
      insertIntoCellTable(cellId,lac,LOCKED,1);
      insertIntoRaTable(lac, rac);
      insertIntoPsCellTable(cellId, lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      CellDataStruct cellData;
      cellData.CellState = blockInProgress;
      cellData.CellID = cellId;
      cellData.Availlability = FALSE;
      cellData.lac = lac;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void CfgSetHndlr42()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;
   CellTableApi *cellTableApiPtr = NULL;
   CellTableIndices cellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
      insertIntoCellTable(cellId,lac,LOCKED,1);
      insertIntoRaTable(lac, rac);
      insertIntoChnGrpTable(cellId,lac);
      sleep(1);
      CellDataStruct cellData;
      cellData.CellState = locked;
      cellData.CellID = cellId;
      cellData.Availlability = FALSE;
      cellData.lac = lac;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      cellTableIndicesBuff.cellId = cellId;
      cellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getCellTable(&cellTableIndicesBuff, &cellTableApiPtr))
      {
         cellTableApiPtr->bcchPwr = 5; 
         cfgStubSendCmMessage(cellTableApiPtr, sizeof(CellTableApi), BSC_API_SET_CELLPERTABLE);
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

void CfgSetHndlr43()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;
   I_U32 band = GSM_1800;
   I_U32 arfcn = 700;
   CellTableApi *cellTableApiPtr = NULL;
   CellTableIndices cellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
      insertIntoCellTable(cellId,lac,LOCKED,1);
      insertIntoRaTable(lac, rac);
      insertIntoChnGrpTable(cellId,lac);
      insertIntoArfcnListTable(band,arfcn);
      sleep(1);
      cellTableIndicesBuff.cellId = cellId;
      cellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getCellTable(&cellTableIndicesBuff, &cellTableApiPtr))
      {
         cellTableApiPtr->freqBandBcch = GSM_1800;
         cellTableApiPtr->bcchArfcn = arfcn++; 
         cfgStubSendCmMessage(cellTableApiPtr, sizeof(CellTableApi), BSC_API_SET_CELLPERTABLE);
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

void CfgSetHndlr44()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;

   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
//      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
        insertIntoPsCellTable(cellId, lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         psCellTableApiPtr->cellId = 2;
         psCellTableApiPtr->lac = 2;
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void CfgSetHndlr45()
{
   static int testInitiation =1;

   I_U16 frChnId = 1;
   I_U16 nsvcId = 1;
   I_U16 e1Id = 1;
   I_U16 linkId = 1;
   I_U16 linksetId = 1;
   I_U16 gbIfIndex = 1;
   I_U16  cellId       = 1;
   I_U16  lac = 1;
   I_U8   rac = 1;
   I_U16 bscIndex = 1;

   PsCellTableApi *psCellTableApiPtr = NULL;
   PsCellTableIndices psCellTableIndicesBuff;


   if ( testInitiation > 0 )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      

      /* delete  From table */
      
      removeAllFromBssPsPreConfigTable();
      removeAllFromGbInterfaceTable();
      removeAllFromBssTable(); 
      removeAllFromRepInfoTable();
      removeAllFromCellTable();
      setBssPsPreConfigTable();
      insertIntoCellTable(cellId,lac,LOCKED,1);
//      insertIntoGbInterfaceTable(gbIfIndex, IP_STATIC);
        insertIntoPsCellTable(cellId, lac, rac);
//      insertIntoBssTable(bscIndex, LOCKED);
      sleep(1);
      psCellTableIndicesBuff.cellId = cellId;
      psCellTableIndicesBuff.lac = lac;
      if(CLIB_SUCCESS == getPsCellTable(&psCellTableIndicesBuff, &psCellTableApiPtr))
      {
         psCellTableApiPtr->gprsCsInitial = 7;
         psCellTableApiPtr->gprsCsMax = 5;
         cfgStubSendCmMessage(psCellTableApiPtr, sizeof(PsCellTableApi), BSC_API_SET_PSCELLTABLE);
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

void insertIntoCicTable(I_U32 cicId, I_U16 e1Num, I_U8 timeslot)
{

   CicTableApi cicTableApiBuff;
   cicTableApiBuff.interfaceId = 1;
   cicTableApiBuff.tgpId = 1;
   cicTableApiBuff.e1Num = e1Num;
   cicTableApiBuff.timeSlot = timeslot;
   cicTableApiBuff.cicId = cicId;
   cicTableApiBuff.usage = 2;
   cicTableApiBuff.adminState = UNLOCKED;
   cicTableApiBuff.reset = 2;

   if(CLIB_SUCCESS == insertCicTable(&cicTableApiBuff))
   {
      printf("Insert Cic Table Successful\n");
   }
   else
   {
      printf("Insert Cic Table Unsuccessful\n");
   }

}
	
void insertIntoLepInfoTable(I_S8 *lepInfoIndex)
{
   LepInfoTableApi lepInfoTableApiBuff;
   strncpy(lepInfoTableApiBuff.lep, lepInfoIndex, 25);
   lepInfoTableApiBuff.lepPort = 5055;
   lepInfoTableApiBuff.signallingWt = 0;
   lepInfoTableApiBuff.dataWt = 0;

   if(CLIB_SUCCESS == insertLepInfoTable(&lepInfoTableApiBuff))
   {
      printf("Insert Lep Info Table Successful\n");
   }
   else
   {
      printf("Insert Lep Info Table Unsuccessful\n");
   }
   
}


void insertIntoRepInfoTable(I_S8 *repInfoIndex)
{
   RepInfoTableApi repInfoTableApiBuff;
   strncpy(repInfoTableApiBuff.rep, repInfoIndex, 25);
   repInfoTableApiBuff.repPort = 5055;
   repInfoTableApiBuff.signallingWt = 0;
   repInfoTableApiBuff.dataWt = 0;

   if(CLIB_SUCCESS == insertRepInfoTable(&repInfoTableApiBuff))
   {
      printf("Insert Rep Info Table Successful\n");
   }
   else
   {
      printf("Insert Rep Info Table Unsuccessful\n");
   }

}
void setMaxNumNsvcsIngbInterfaceTable(I_U16 gbIfIndex, I_U32 transportType, I_U16 maxNum)
{
   GbInterfaceTableApi gbInterfaceTableApiBuff;
   gbInterfaceTableApiBuff.gbIfIndex = gbIfIndex;
   if(transportType == FR)
   {
      gbInterfaceTableApiBuff.maxNumNsvcsOverFr = maxNum;
   }
   else if (transportType == IP_STATIC || transportType == IP_DYNAMIC)
   {
      gbInterfaceTableApiBuff.maxNumNsvcsOverIp = maxNum;
   }
   else
   {
      gbInterfaceTableApiBuff.maxNumReps = maxNum;
   }
   if(CLIB_SUCCESS == updateGbInterfaceTable(&gbInterfaceTableApiBuff))
   {
      printf("\nUpdate in Gb Interface table Successfull");
   }
   else
   {
      printf("\nUpdate in Gb Interface table Unsuccessfull");
   }
}

void insertIntoGbInterfaceTable(I_U16 gbIfIndex, I_U32 transportType)
{
   GbInterfaceTableApi gbInterfaceTableApiBuff;
   gbInterfaceTableApiBuff.gbIfIndex          = gbIfIndex;
   gbInterfaceTableApiBuff.nsei               = 10;
   gbInterfaceTableApiBuff.maxNumNsvcsOverFr  = 5;
   gbInterfaceTableApiBuff.maxNumNsvcsOverIp  = 0;
   gbInterfaceTableApiBuff.maxNumLeps         = 20;
   gbInterfaceTableApiBuff.maxNumReps         = 20;
   gbInterfaceTableApiBuff.transportType      = transportType;
   gbInterfaceTableApiBuff.tFcC               = 10;
   gbInterfaceTableApiBuff.tFcTh              = 100;
   gbInterfaceTableApiBuff.tFcSup             = 8;
   gbInterfaceTableApiBuff.nMaxFcRep          = 1;
   if(CLIB_SUCCESS == insertGbInterfaceTable(&gbInterfaceTableApiBuff))
   {
      printf("Insert Gb Interface Successful\n");
   }
   else
   {
      printf("Insert Gb Interface Unsuccessful\n");
      if(CLIB_SUCCESS == updateGbInterfaceTable(&gbInterfaceTableApiBuff))
      {
         printf("Update Gb Interface Successful\n");
      }
      else
      {
         printf("Update Gb Interface Unsuccessful\n");
      }
   }
}

void removeAllFromBssTable()
{
   BssTableApi *bssTableApiAllPtr = NULL;
   BssTableApi *bssTableApiPtr = NULL;
   BssTableIndices bssTableIndicesBuff;

   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallBssTable(&bssTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          bssTableApiPtr = (BssTableApi *) (((I_U8 *) bssTableApiAllPtr ) + (outSize * i));
          bssTableIndicesBuff.bscId = bssTableApiPtr->bscId;
          deleteBssTable(&bssTableIndicesBuff);
       }
       free(bssTableApiAllPtr);

   }
   printf("Deletion from Bss successful\n");
}

void removeAllFromGbInterfaceTable()
{
   GbInterfaceTableApi *gbInterfaceTableApiAllPtr = NULL;
   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   GbInterfaceTableIndices gbInterfaceIndicesBuff;

   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallGbInterfaceTable(&gbInterfaceTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          gbInterfaceTableApiPtr = (GbInterfaceTableApi *) (((I_U8 *) gbInterfaceTableApiAllPtr ) + (outSize * i));
          gbInterfaceIndicesBuff.gbIfIndex = gbInterfaceTableApiPtr->gbIfIndex;
          deleteGbInterfaceTable(&gbInterfaceIndicesBuff);
       }
       free(gbInterfaceTableApiAllPtr);

   }
   printf("Deletion from Gb Interface successful\n");
}

void removeAllFromRepInfoTable()
{
   RepInfoTableApi *repInfoTableApiAllPtr = NULL;
   RepInfoTableApi *repInfoTableApiPtr = NULL;
   RepInfoTableIndices repInfoIndicesBuff;

   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallRepInfoTable(&repInfoTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          repInfoTableApiPtr = (RepInfoTableApi *) (((I_U8 *) repInfoTableApiAllPtr ) + (outSize * i));
          strncpy(repInfoIndicesBuff.rep, repInfoTableApiPtr->rep, 25);
          deleteRepInfoTable(&repInfoIndicesBuff);
       }
       free(repInfoTableApiAllPtr);

   }
   printf("Deletion from RepInfo successful\n");
}
void removeAllFromLepInfoTable()
{
   LepInfoTableApi *lepInfoTableApiAllPtr = NULL;
   LepInfoTableApi *lepInfoTableApiPtr = NULL;
   LepInfoTableIndices lepInfoIndicesBuff;

   I_U32  i = 0;
   I_U32  rowsCount = 0;
   I_U16  outSize = 0;

   if (getallLepInfoTable(&lepInfoTableApiAllPtr, &rowsCount, &outSize) == CLIB_SUCCESS)
   {
       for(i = 0; i < rowsCount; i++)
       {
          lepInfoTableApiPtr = (LepInfoTableApi *) (((I_U8 *) lepInfoTableApiAllPtr ) + (outSize * i));
          strncpy(lepInfoIndicesBuff.lep, lepInfoTableApiPtr->lep, 25);
          deleteLepInfoTable(&lepInfoIndicesBuff);
       }
       free(lepInfoTableApiAllPtr);

   }
   printf("Deletion from LepInfo successful\n");
}

