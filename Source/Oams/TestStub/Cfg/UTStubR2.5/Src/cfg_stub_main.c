/*#include <unistd.h>*/
#include <oamcfg_includes.h>
#define DESTINATION ENT_OAMS_CFG
void cfgStubFrmwrkInit();
void cfgDbInit();
I_S32 cfgStubSendCmMessageFromOil(  I_U32 MessageType ,I_U32 result);
int gTestCaseCompleted =0;
BssTableApi gBssTableApiBuff={0};
int cellObjHandlerFromBss  =0;

#define MAX_GROUP_ID 9
#define MAX_TEST_CASES 250
#define CFG_RESET    0xffff
/******************
typedef struct alarm_NWSTACK{
I_U16     AlarmID;
I_U8   AlarmLevel;
I_U8    FieldId;
I_U8    FamilyType;
I_U32   dpc ;
I_U32   opc;
I_U8    SSN;
I_U8    NetworkIndicator;
I_U8    LinksetID ;
I_U8    LinkCode ;
I_U8    UserPart;
I_U8    Messagetype;
I_U8    ProtocolClass;
I_U16   PCM;
I_U16   TimeSlot;
I_U8    infostring[100];
}Alarm_NWSTACK;
************************************/

/************** Structure  for CFG-OIL Interface**************/

typedef struct CfgOilAlarm
{

 sCmMsg  syshdr;
 Alarm_NWSTACK sysAlarm; 

}CfgOilAlarm;

/************************************************************/




void startTrxh();
void startCellh();
void startGrhm();
void startPcuh();
void startOil();
void startCm();
void startSCM();
void startPSSCM();
void startMGS();
I_PVoid Build_CsappGrhmTrxhDelChanResp(I_U32 tei, I_S32 *size);
I_PVoid Build_CsappGrhmTrxhCreChanResp(I_U32 tei, I_S32 *size);
/*************************************************************/
typedef  void (*pt2TestCaseFunc)();
pt2TestCaseFunc pt2TestCase[MAX_GROUP_ID][MAX_TEST_CASES] = {
   {
     /*nsvcTableRangeChkTest,
     frLinkTableRangeChkTest,
     repInfoTableRangeChkTest,
     bssPsTableRangeChkTest,
     lepInfoTableRangeChkTest,
     gbInterfaceTableRangeChkTest,
     psCellTableRangeChkTest,
     cellTableRangeChkTest,
     CfgDelHndlr1,
     CfgDelHndlr2,
     CfgDelHndlr3,
     CfgDelHndlr4,
     CfgDelHndlr5,
     CfgDelHndlr6,
     CfgDelHndlr7,
     CfgDelHndlr8,
     CfgDelHndlr9,
     CfgDelHndlr10,
     CfgDelHndlr11,
     CfgDelHndlr12,
     CfgDelHndlr13,
     CfgDelHndlr14,
     CfgSetHndlr1,
     CfgSetHndlr2,
     CfgSetHndlr3,
     CfgSetHndlr4,
     CfgSetHndlr5,
     CfgSetHndlr6,
     CfgSetHndlr7,
     CfgSetHndlr8,
     CfgSetHndlr9,
     CfgSetHndlr10,
     CfgSetHndlr11,
     CfgSetHndlr12,
     CfgSetHndlr13,
     CfgSetHndlr14,
     CfgSetHndlr15,
     CfgSetHndlr16,
     CfgSetHndlr17,
     CfgSetHndlr18,
     CfgSetHndlr19,
     CfgSetHndlr20,
     CfgSetHndlr21,
     CfgSetHndlr22,
     CfgSetHndlr23,
     CfgSetHndlr24,
     CfgSetHndlr25,
     CfgSetHndlr26,
     CfgSetHndlr27,
     CfgSetHndlr28,
     CfgSetHndlr29,
     CfgSetHndlr30,
     CfgSetHndlr31,
     CfgSetHndlr32,
     CfgSetHndlr33,
     CfgSetHndlr34,
     CfgSetHndlr35,
     CfgSetHndlr36,
     CfgSetHndlr37,
     CfgSetHndlr38,
     CfgSetHndlr39,
     CfgSetHndlr40,
     CfgSetHndlr41,
     CfgSetHndlr42,
     CfgSetHndlr43,
     CfgSetHndlr44,
     CfgSetHndlr45*/
   },  
   {
      /*nsvcObjHandler1,
      nsvcObjHandler2,
      nsvcObjHandler3,
      nsvcObjHandler4,
      nsvcObjHandler5,
      nsvcObjHandler6,
      nsvcObjHandler7,
      nsvcObjHandler8,
      nsvcObjHandler9,
      nsvcObjHandler10,
      nsvcObjHandler11,
      nsvcObjHandler12,
      nsvcObjHandler13,
      nsvcObjHandler14,
      nsvcObjHandler15,
      nsvcObjHandler16*/
   },
   {
     /*CfgE1ObjHndlr1,
     CfgE1ObjHndlr2,
     CfgE1ObjHndlr3,
     CfgE1ObjHndlr4*/
   },
   {
     /*cfgAlarmObjHndlr1,
     cfgAlarmObjHndlr2,
     cfgAlarmObjHndlr3,
     cfgAlarmObjHndlr4, 
     cfgBssHndlr1,
     cfgBssHndlr2,
     cfgBssHndlr3,
     cfgBssHndlr4,
     cfgBssHndlr5,
     cfgBssHndlr6,*/
     cfgBssHndlr7
   },
   {
   },
   {
   },
   {
   },
   {
      /*cellObjHandler1,
      cellObjHandler2,
      cellObjHandler3,
      cellObjHandler4,
      cellObjHandler5,
      cellObjHandler6,
      cellObjHandler7,
      cellObjHandler8,
      cellObjHandler9,
      cellObjHandler10,
      cellObjHandler11,
      cellObjHandler12,
      cellObjHandler13,
      cellObjHandler14,
      cellObjHandler15,
      cellObjHandler16,
      cellObjHandler17,
      cellObjHandler18,
      cellObjHandler19,
      cellObjHandler20,
      cellObjHandler21,
      cellObjHandler22,
      cellObjHandler23,
      cellObjHandler24*/
   }

};
#define MAX_MSGQ_BUF_SIZE 4096
I_S32 gSrcId;      /* SrcId for the CFG */
void *gCfgMsgBuf;   /* Message Pointer for the received message */
I_U32 gRecvMsgSize;  /* received message size */
#define ENT_OAMS_CFGSTUB 0x8888 /* some number */
I_S32 cfgStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType);

main()
{
   int  testCaseOpton;
   char  testCaseOptonString[80];
   int testCaseNum;
   int testCaseGroupId;
   int choice1=1,choice2;

   printf(" Before  DBInit\n");
   cfgDbInit();
   printf(" After DBInit\n");
   printf("***************************************************************\n");
   printf("\nEnter Your Choice: \n 1 - CFG -REGRESSION \n 2- SSI - STUB\n");
   scanf("%d",&choice1);
   if (choice1 == 2)
   {
      printf("Enter the Enity type: \n1 - ENT_OAM_TRXH\n2 - ENT_OAM_CELLH\n3 - ENT_CSAPP_GRHM\n4 - ENT_PSAPP_PCUH\n5 - ENT_OAM_OIL\n6 - ENT_OAM_CM\n7-ENT_OAM_SCM\n8-ENT_STK_PSSM\n9-ENT_MGS_TSM");
      scanf("%d",&choice2);
      switch(choice2) 
      {
         case 1:
            printf("\n TRXH Stub......\n");
            gSrcId = ENT_OAMS_TRXH;
            printf("\n Before FrameworkInit\n");
            cfgStubFrmwrkInit();
            startTrxh();
            break;
         case 2:
            printf("\n Cellh Stub......\n");
            gSrcId = ENT_OAMS_CELLH;
            printf("\n Before FrameworkInit\n");
            cfgStubFrmwrkInit();
            startCellh(); 
            break;
         case 3:
            gSrcId = ENT_CSAPP_GRHM;
            printf("\n Grhm Stub......\n");
            printf("\n Before FrameworkInit\n");
            cfgStubFrmwrkInit();
            startGrhm(); 
            break;
         case 4:
#if 0
            printf("\n Pcuh Stub......\n");
            gSrcId = ENT_PSAPP_PCUH;   
            printf("\n Before FrameworkInit\n");
            cfgStubFrmwrkInit();
            startPcuh();
#endif
            break;
#if 0
         case 5:
            printf("\n Oil Stub......\n");
            gSrcId = ENT_OAM_OIL;
            printf("\n Before FrameworkInit\n");
            cfgStubFrmwrkInit();
            startOil();
            break; 
         case 6:
            printf("\nCM stub...\n");  
            gSrcId = ENT_OAM_CM;
            printf("\n Before FrameworkInit\n");
            cfgStubFrmwrkInit();
            startCm();
	    break;
	case 7:
            printf("\nSCM stub...\n");  
            gSrcId = ENT_IPC_SCMIF;
            printf("\n Before FrameworkInit\n");
            cfgStubFrmwrkInit();
            startSCM();
            break;   
#endif
       case 8:
#if 0
            printf("\nPSSCM stub...\n");
            gSrcId = ENT_PSSTK_PSSCM;
            printf("\n Before FrameworkInit\n");
            cfgStubFrmwrkInit();
            startPSSCM();
#endif
            break;
       case 9:
            printf("\nMGS stub.......\n");
            gSrcId=ENT_IPC_TSMIF;
            printf("\n Before FrameworkInit\n");
            cfgStubFrmwrkInit();
            startMGS();
            break;
 

      }              

   }    
   else /******************** Regreesion *****************************/
   {        
      gSrcId = 36;      /*Initilise the Stub as default 36 EntityID */
      cfgStubFrmwrkInit();  /*register with the IPC Framework.. */  
      for (;;)
      {
         printf ("\n **** CFG UNIT TEST CASE EXECUTION ****\n\n");
         printf ("  Enter TestGrpId or ALL for Regression       : ");
         scanf("%s",testCaseOptonString);
         if ((strcmp(testCaseOptonString,"ALL") == 0 )||
               (strcmp(testCaseOptonString,"All") == 0 )||
               (strcmp(testCaseOptonString,"all") == 0 ))
         {
            testCaseOpton = 2; /* Regression */
         }
         else
         {
            testCaseGroupId=atoi(testCaseOptonString);
            testCaseOpton = 1; /* individual */
         }
         if (( testCaseOpton == 1) || (testCaseOpton == 2))
         {
            break;
         }
         else
         {
            printf("Invalid test cases optoin\n");
         }
      }
      if ( testCaseOpton == 1 )
      {
         printf (" Please Enter Test Case Number to be executed : ");
         scanf( "%d",&testCaseNum);
         cfgStubSendCmMessage(NULL,0,CFG_RESET);
         if (  (*pt2TestCase[testCaseGroupId-1][testCaseNum-1]) == NULL )
         {
            printf ("\n Test case Does not exits \n");
            printf ("\n Bye Bye!!!!!!!!!! \n");
            return;
         }

         for (;;)
         {
            printf("\n cleaning  the  message queue....");
            gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
            if (gCfgMsgBuf == NULL)
            {
               break;
            }
            DalocMsgBuf((I_Void *)gCfgMsgBuf);
         }

         gTestCaseCompleted =0;
         (*pt2TestCase[testCaseGroupId-1][testCaseNum-1])();
         /* receive messages */
         for (;;)
         {
            static I_U8 waitingFlag = 0;
            if (gTestCaseCompleted)
            {
               getchar();
               getchar();
               break;
            }
            /* receive message */
            gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
            if (gCfgMsgBuf == NULL)
            {
               if ( waitingFlag == 0 )
               {
                  //     printf("\n Waiting for Message");
                  waitingFlag=1;
               }
               else
                  //     printf(".");
                  fflush(NULL);
               continue; 
            }
            else
               printf("\n Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRecvMsgSize);

            waitingFlag=0;
            (*pt2TestCase[testCaseGroupId-1][testCaseNum-1])();      
            DalocMsgBuf((I_Void *)gCfgMsgBuf);
         }

      }
      else
      {
         /* Regression */
         int i,j = 0;
         for ( i = 0 ;i < MAX_GROUP_ID ; i++ )
            for ( j =0 ; j < MAX_TEST_CASES; j++)
            {  
               if ( ((pt2TestCase[i][j])) == NULL )
               {
                  /* printf( " Testcase Not available for index  Group Id= %d Test Case Id = %d\n ",i,j);*/
                  continue;
               }
               else
               {
                  /*cfgStubSendCmMessage(NULL,0,CFG_RESET);
                  for (;;)
                  {
                     usleep(500000);
                     //      printf("\n cleaning  the  message queue....");
                     gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
                     if (gCfgMsgBuf == NULL)
                     {
                        break;
                     }
                     DalocMsgBuf((I_Void *)gCfgMsgBuf);
                  }
                  */
                  printf ( "\n**** Execution of Test case Group = %d  Test Case Id = %d ****\n",i+1,j+1);
                  gTestCaseCompleted =0;
                  (*pt2TestCase[i][j])();

                  /* receive messages */
                  for (;;)
                  {  
                     sleep(1);
                     printf("gTestCaseCompleted = %d\n",gTestCaseCompleted);
                     if (gTestCaseCompleted)
                     {
                        gTestCaseCompleted =0;
                        printf("*********Test Case completed********\n\n");
                        //cfgStubSendCmMessage(NULL,0,CFG_RESET);
                        break;
                     }
                     /* receive message */
                     printf("Waiting for the message queue....\n");
                     gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize);
                     if (gCfgMsgBuf == NULL)
                     {
                        printf("Message received is NULL\n");
                        continue;
                     }
                     else
                        printf("Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRecvMsgSize);
                     (*pt2TestCase[i][j])();
                     DalocMsgBuf((I_Void *)gCfgMsgBuf);
                  }
               }
            }
         printf ( "************ Execution of all Test case is completed *************\n");
      }

   }

   return 0;
}


/*Changes R2.5 Aricent -- Start*/
void cfgStubSendPschCfgUnlockResp(I_U32 lac, I_U32 cellId, I_U32 cellIndex, I_U32 bvci)
{
   OamsPschCfgUnlockResp oamsPschCfgUnlockRespBuff;
   oamsPschCfgUnlockRespBuff.lac = lac;
   oamsPschCfgUnlockRespBuff.cellId = cellId;
   oamsPschCfgUnlockRespBuff.cellIndex = cellIndex;
   oamsPschCfgUnlockRespBuff.bvci = bvci;
   cfgStubSendMessage(&oamsPschCfgUnlockRespBuff, sizeof(OamsPschCfgUnlockResp), ENT_OAMS_PSCH, ENT_OAMS_CFG, OAMS_PSCH_CFG_UNLOCK_RESP,0);
}
void cfgStubSendPschCfgLockResp(I_U32 lac, I_U32 cellId, I_U32 cellIndex)
{
   OamsPschCfgLockResp oamsPschCfgLockRespBuff;
   oamsPschCfgLockRespBuff.lac = lac;
   oamsPschCfgLockRespBuff.cellId = cellId;
   oamsPschCfgLockRespBuff.cellIndex = cellIndex;
   cfgStubSendMessage(&oamsPschCfgLockRespBuff, sizeof(OamsPschCfgLockResp), ENT_OAMS_PSCH, ENT_OAMS_CFG, OAMS_PSCH_CFG_LOCK_RESP,0);
}
void cfgStubSendPschCfgAlarmInd( SysAlarm sysAlarm)
{
   OamsPschCfgAlarmInd oamsPschCfgAlarmIndBuff;

   memcpy((I_U8*)(((I_U8*)&oamsPschCfgAlarmIndBuff)+sizeof(SysHdr)),(I_U8*)&sysAlarm,sizeof(SysAlarm));
   cfgStubSendMessage(&oamsPschCfgAlarmIndBuff,sizeof(OamsPschCfgAlarmInd),ENT_OAMS_PSCH, ENT_OAMS_CFG, OAMS_PSCH_CFG_ALARM_IND,0);
}

void cfgStubSendNsvchCfgUnlockResp(I_U32 nsvcId)
{
   OamsNsvchCfgUnlockResp oamsNsvchCfgUnlockRespBuff;
   oamsNsvchCfgUnlockRespBuff.nsvcId = nsvcId;
   cfgStubSendMessage(&oamsNsvchCfgUnlockRespBuff, sizeof(OamsNsvchCfgUnlockResp), ENT_OAMS_PSSCM, ENT_OAMS_CFG, OAMS_NSVCH_CFG_UNLOCK_RESP,0);
}

void cfgStubSendNsvchCfgLockResp(I_U32 nsvcId)
{
   OamsNsvchCfgLockResp oamsNsvchCfgLockRespBuff;
   oamsNsvchCfgLockRespBuff.nsvcId = nsvcId;
   cfgStubSendMessage(&oamsNsvchCfgLockRespBuff, sizeof(OamsNsvchCfgLockResp), ENT_OAMS_PSSCM, ENT_OAMS_CFG, OAMS_NSVCH_CFG_LOCK_RESP,0);
}

/*Changes R2.5 Aricent -- End*/
/************************** Oam_cfg_cellh.h ***** Start ***********************/
void cfgStubSendCellhCfgLockResp(   I_U32 objType, I_U32 objId, I_U32  lac)
{
   OamsCellhCfgLockResp OamsCellhCfgLockRespBuff;
   OamsCellhCfgLockRespBuff.objType = objType;
   OamsCellhCfgLockRespBuff.objId = objId;
   OamsCellhCfgLockRespBuff.lac=lac; 
   cfgStubSendMessage(&OamsCellhCfgLockRespBuff,sizeof(OamsCellhCfgLockResp),ENT_OAMS_CELLH,ENT_OAMS_CFG, OAMS_CELLH_CFG_LOCK_RESP,0);
}

void cfgStubSendCellhCfgUnlockResp(   I_U32 objType, I_U32 objId, I_U32  lac)
{
   OamsCellhCfgUnlockResp OamsCellhCfgUnlockRespBuff;

   OamsCellhCfgUnlockRespBuff.objType = objType;
   OamsCellhCfgUnlockRespBuff.objId = objId;
   OamsCellhCfgUnlockRespBuff.lac=lac; 
   cfgStubSendMessage(&OamsCellhCfgUnlockRespBuff,sizeof(OamsCellhCfgUnlockResp),ENT_OAMS_CELLH,ENT_OAMS_CFG, OAMS_CELLH_CFG_UNLOCK_RESP,0);
}

void cfgStubSendCellhCfgAlarmInd( SysAlarm sysAlarm)
{
   OamsCellhCfgAlarmInd OamsCellhCfgAlarmIndBuff;

   memcpy((I_U8*)(((I_U8*)&OamsCellhCfgAlarmIndBuff)+sizeof(SysHdr)),(I_U8*)&sysAlarm,sizeof(SysAlarm));
   cfgStubSendMessage(&OamsCellhCfgAlarmIndBuff,sizeof(OamsCellhCfgAlarmInd),ENT_OAMS_CELLH,ENT_OAMS_CFG, OAMS_CELLH_CFG_ALARM_IND,0);
}
/************************** Oam_cfg_cellh.h ***** End ***********************/
/************************** Oam_cfg_grhm.h **** Start ***********************/

void cfgStubSendGrhmCfgLockResp(   I_U32 objType, I_U32 objId)
{
   CsappGrhmCfgLockResp CsappGrhmCfgLockRespBuff;

   CsappGrhmCfgLockRespBuff.objType = objType;
   CsappGrhmCfgLockRespBuff.objectId = objId;
   cfgStubSendMessage(&CsappGrhmCfgLockRespBuff,sizeof(CsappGrhmCfgLockResp),ENT_CSAPP_GRHM, ENT_OAMS_CFG, CSAPP_GRHM_CFG_LOCK_RESP,0);
}

void cfgStubSendGrhmCfgUnlockResp(   I_U32 objType, I_U32 objId)
{
   CsappGrhmCfgUnlockResp CsappGrhmCfgUnlockRespBuff;

   CsappGrhmCfgUnlockRespBuff.objType = objType;
   CsappGrhmCfgUnlockRespBuff.objectId = objId;
   cfgStubSendMessage(&CsappGrhmCfgUnlockRespBuff,sizeof(CsappGrhmCfgUnlockResp),ENT_CSAPP_GRHM,ENT_OAMS_CFG, CSAPP_GRHM_CFG_UNLOCK_RESP,0);
}

void cfgStubSendGrhmCfgAlarmInd( SysAlarm sysAlarm)
{
   CsappGrhmCfgAlarmInd CsappGrhmCfgAlarmIndBuff;

   memcpy((I_U8*)(((I_U8*)&CsappGrhmCfgAlarmIndBuff)+sizeof(SysHdr)),(I_U8*)&sysAlarm,sizeof(SysAlarm));
   cfgStubSendMessage(&CsappGrhmCfgAlarmIndBuff,sizeof(CsappGrhmCfgAlarmInd),ENT_CSAPP_GRHM,ENT_OAMS_CFG, CSAPP_GRHM_CFG_ALARM_IND,0);
}

/************************** Oam_cfg_grhm.h **** End ***********************/


/************************** Oam_cfg_trxh.h **** Start ***********************/

void cfgStubSendTrxhCfgLockResp(   I_U32 objType, I_U32 objId, I_U32 e1Num )
{
   OamsTrxhCfgLockResp OamsTrxhCfgLockRespBuff;

   OamsTrxhCfgLockRespBuff.objType = objType;
   OamsTrxhCfgLockRespBuff.objId = objId;
   OamsTrxhCfgLockRespBuff.e1Num = e1Num;
   cfgStubSendMessage(&OamsTrxhCfgLockRespBuff,sizeof(OamsTrxhCfgLockResp),ENT_OAMS_TRXH, ENT_OAMS_CFG, OAMS_TRXH_CFG_LOCK_RESP,0);
}

void cfgStubSendTrxhCfgUnlockResp(   I_U32 objType, I_U32 objId, I_U32 e1Num)
{
   OamsTrxhCfgUnlockResp OamsTrxhCfgUnlockRespBuff;

   OamsTrxhCfgUnlockRespBuff.objType = objType;
   OamsTrxhCfgUnlockRespBuff.objId = objId;
   OamsTrxhCfgUnlockRespBuff.e1Num=e1Num;
   cfgStubSendMessage(&OamsTrxhCfgUnlockRespBuff,sizeof(OamsTrxhCfgUnlockResp),ENT_OAMS_TRXH,ENT_OAMS_CFG, OAMS_TRXH_CFG_UNLOCK_RESP,0);
}

void cfgStubSendTrxhCfgAlarmInd( SysAlarm sysAlarm)
{
   OamsTrxhCfgAlarmInd oamsTrxhCfgAlarmIndBuff;

   memcpy((I_U8*)(((I_U8*)&oamsTrxhCfgAlarmIndBuff)+sizeof(SysHdr)),(I_U8*)&sysAlarm,sizeof(SysAlarm));
   cfgStubSendMessage(&oamsTrxhCfgAlarmIndBuff,sizeof(OamsTrxhCfgAlarmInd),ENT_OAMS_TRXH,ENT_OAMS_CFG, OAMS_TRXH_CFG_ALARM_IND,0);
}

/************************** Oam_cfg_trxh.h **** End ***********************/
/************************** Oam_cfg_pcu.h **** Start ***********************/
#if 0
void cfgStubSendPcuCfgLockResp(   I_U32 objType, I_U32 objId, I_U32 lac)
{
   PsappPcuCfgLockResp PsappPcuCfgLockRespBuff;

   PsappPcuCfgLockRespBuff.objType = objType;
   PsappPcuCfgLockRespBuff.objId = objId;
   PsappPcuCfgLockRespBuff.lac = lac;

   cfgStubSendMessage(&PsappPcuCfgLockRespBuff,sizeof(PsappPcuCfgLockResp),ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PCUH_CFG_LOCK_RESP,0);
}

void cfgStubSendPcuCfgUnlockResp(   I_U8 objType, I_U32 objId, I_U32 lac,   I_U32  result, I_U8  cause)
{
   PsappPcuCfgUnlockResp PsappPcuCfgUnlockRespBuff;

   PsappPcuCfgUnlockRespBuff.objType = objType;
   PsappPcuCfgUnlockRespBuff.objId = objId;
   PsappPcuCfgUnlockRespBuff.lac = lac;
   PsappPcuCfgUnlockRespBuff.cause = cause;
   PsappPcuCfgUnlockRespBuff.result = result;
   cfgStubSendMessage(&PsappPcuCfgUnlockRespBuff,sizeof(PsappPcuCfgUnlockResp),ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PCUH_CFG_UNLOCK_RESP,0);
}

void cfgStubSendPcuCfgAlarmInd( SysAlarm sysAlarm)
{
   PsappPcuCfgAlarmInd PsappPcuCfgAlarmIndBuff;

   memcpy((I_U8*)(((I_U8*)&PsappPcuCfgAlarmIndBuff)+sizeof(SysHdr)),(I_U8*)&sysAlarm,sizeof(SysAlarm));
   cfgStubSendMessage(&PsappPcuCfgAlarmIndBuff,sizeof(PsappPcuCfgAlarmInd),ENT_PSAPP_PCUH,ENT_OAMS_CFG, PSAPP_PCUH_CFG_ALARM_IND,0);
}

void cfgStubSendCfgPcuCellEnabledResp(   I_U8 objType, I_U32 objId, I_U32 lac)
{
   OamsCfgPcuCellEnabledResp OamsCfgPcuCellEnabledRespBuff;

   /*OamsCfgPcuCellEnabledRespBuff.objType = objType;*/
   OamsCfgPcuCellEnabledRespBuff.objId = objId;
   OamsCfgPcuCellEnabledRespBuff.lac = lac;

   cfgStubSendMessage(&OamsCfgPcuCellEnabledRespBuff,sizeof(OamsCfgPcuCellEnabledResp),ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PCUH_CFG_CELL_ENABLED_RESP,0);
}
void cfgStubSendCfgPcuFirstNsvcEnabledResp()
{
   cfgStubSendMessage(NULL,0,ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PCUH_CFG_FIRST_NSVC_ENABLED_RESP,0);
}

void cfgStubSendCfgPcuAllNsvcDisabledReqResp()
{
   cfgStubSendMessage(NULL,0,ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PCUH_CFG_ALL_NSVC_DISABLED_RESP,0);
}

void cfgStubSendPcuCfgBvcReset( I_U32 nsei, I_U32 bvci,  I_U32  result)
{
   PsappPcuCfgBvcResetResp PsappPcuCfgBvcResetRespBuff;

   PsappPcuCfgBvcResetRespBuff.nsei = nsei;
   PsappPcuCfgBvcResetRespBuff.bvci = bvci;
   PsappPcuCfgBvcResetRespBuff.result = result;
   cfgStubSendMessage(&PsappPcuCfgBvcResetRespBuff,sizeof(PsappPcuCfgBvcResetResp),ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PCUH_CFG_BVC_RESET_RESP,0);
}
void cfgStubSendPcuCfgFirstNsvcEnabledResp()
{
   cfgStubSendMessage(NULL,0,ENT_OAM_OIL, ENT_OAMS_CFG, PSAPP_PCUH_CFG_FIRST_NSVC_ENABLED_RESP,0);       
}
#endif
/************************** Oam_cfg_pcu.h **** End ***********************/
/************************** Oam_cfg_OIL.h **** sTART ***********************/


void cfgStubSendCfgScmLockResp(I_U8  ObjType,  I_U16  lengthOfList, I_U32 objectIdList[], I_U32  e1Num,I_U32 tsNum, I_U8 reason)
{
   OamsScmCfgLockResp OamsScmCfgLockRespBuff;
   OamsScmCfgLockRespBuff.ObjType =ObjType;
   OamsScmCfgLockRespBuff.lengthOfList=lengthOfList;
   memcpy((I_U8*)&(OamsScmCfgLockRespBuff.objectIdList[0]),(I_U8 *)objectIdList,lengthOfList*sizeof(I_U32));

   OamsScmCfgLockRespBuff.e1Num=e1Num;         /* Valid only when ObjectType is "E1"  */
   OamsScmCfgLockRespBuff.tsNum=tsNum;         /* Valid only when ObjectType is "E1"  */

   OamsScmCfgLockRespBuff.reason=reason;
   cfgStubSendMessage(&OamsScmCfgLockRespBuff,sizeof(OamsScmCfgLockResp),ENT_OAM_OIL, ENT_OAMS_CFG, OAMS_SCM_CFG_LOCK_RESP,0);       

}
void cfgStubSendCfgScmUnLockResp(I_U8  ObjType,  I_U16  lengthOfList, I_U32 objectIdList[], I_U32  e1Num,I_U32 tsNum, I_U8 reason)
{
   OamsScmCfgUnlockResp OamsCfgScmUnLockRespBuff;
   OamsCfgScmUnLockRespBuff.ObjType =ObjType;
   OamsCfgScmUnLockRespBuff.lengthOfList=lengthOfList;
   memcpy((I_U8*)&(OamsCfgScmUnLockRespBuff.objectIdList[0]),(I_U8 *)objectIdList,lengthOfList*sizeof(I_U32));

   OamsCfgScmUnLockRespBuff.e1Num=e1Num;         /* Valid only when ObjectType is "E1"  */
   OamsCfgScmUnLockRespBuff.tsNum=tsNum;         /* Valid only when ObjectType  is TimeSLot "  */
   OamsCfgScmUnLockRespBuff.reason=reason;
   cfgStubSendMessage(&OamsCfgScmUnLockRespBuff,sizeof(OamsScmCfgUnlockResp),ENT_OAM_OIL, ENT_OAMS_CFG, OAMS_SCM_CFG_UNLOCK_RESP,0);       

}

#if 0
void cfgStubSendPsscmCfgUnlockResp(I_U8  ObjType,  I_U16  lengthOfList, I_U32 objectIdList[], I_U32  e1Num, I_U32  result,I_U8 cause,I_U32 lac)
{
   PsappPsscmCfgUnlockResp PsappPsscmCfgUnlockRespBuff;
   PsappPsscmCfgUnlockRespBuff.ObjType =ObjType;
   PsappPsscmCfgUnlockRespBuff.lengthOfList=lengthOfList;
   memcpy((I_U8*)&(PsappPsscmCfgUnlockRespBuff.objectIdList[0]),(I_U8 *)objectIdList,lengthOfList*sizeof(I_U32)); 
   PsappPsscmCfgUnlockRespBuff.e1Num=e1Num;         /* Valid only when ObjectType is "E1"  */
   PsappPsscmCfgUnlockRespBuff.cause=cause;
   PsappPsscmCfgUnlockRespBuff.lac=lac;
   PsappPsscmCfgUnlockRespBuff.result=result;
   cfgStubSendMessage(&PsappPsscmCfgUnlockRespBuff,sizeof(PsappPsscmCfgUnlockResp),ENT_OAM_OIL, ENT_OAMS_CFG, PSAPP_PSSCM_CFG_UNLOCK_RESP,0);       

}
#endif
void cfgStubSendScmCfgAlarmInd(I_U32 alarmId)
{
   OamsCfgScmCfgAlarmInd OamsCfgScmCfgAlarmIndBuff;
   OamsCfgScmCfgAlarmIndBuff.sysAlarm.sysalarmId= alarmId;
   cfgStubSendMessage(&OamsCfgScmCfgAlarmIndBuff,sizeof(OamsCfgScmCfgAlarmInd),ENT_OAM_OIL, ENT_OAMS_CFG, OAMS_SCM_CFG_ALARM_IND,0);     


}                  

void cfgStubSendPsscmCfgAlarmInd( SysAlarm sysAlarm)
{
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmIndBuff;

   memcpy((I_U8*)(((I_U8*)&oamsPsscmCfgAlarmIndBuff)+sizeof(SysHdr)),(I_U8*)&sysAlarm,sizeof(SysAlarm));
   cfgStubSendMessage(&oamsPsscmCfgAlarmIndBuff,sizeof(OamsPsscmCfgAlarmInd),ENT_OAMS_PSSCM,ENT_OAMS_CFG, OAMS_PSSCM_CFG_ALARM_IND,0);
}


void cfgStubSendNsvchCfgAlarmInd(SysAlarm sysAlarm)
{
  OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmIndBuff;
   memcpy((I_U8*)(((I_U8*)&oamsNsvchCfgAlarmIndBuff)+sizeof(SysHdr)),(I_U8*)&sysAlarm,sizeof(SysAlarm));
   cfgStubSendMessage(&oamsNsvchCfgAlarmIndBuff,sizeof(OamsNsvchCfgAlarmInd),ENT_OAMS_PSSCM,ENT_OAMS_CFG, OAMS_NSVCH_CFG_ALARM_IND,0);
}
#if 0
void cfgStubSendPsscmCfgLockResp(I_U8  ObjType,  I_U16  lengthOfList, I_U32 objectIdList[], I_U32  e1Num, I_U32 lac)
{
   PsappPsscmCfgLockResp PsappPsscmCfgLockRespBuff;
   PsappPsscmCfgLockRespBuff.ObjType =ObjType;
   PsappPsscmCfgLockRespBuff.lengthOfList=lengthOfList;
   memcpy((I_U8*)&(PsappPsscmCfgLockRespBuff.objectIdList[0]),(I_U8 *)objectIdList,lengthOfList*sizeof(I_U32));  
   PsappPsscmCfgLockRespBuff.e1Num=e1Num;         /* Valid only when ObjectType is "E1"  */
   PsappPsscmCfgLockRespBuff.lac=lac;

   cfgStubSendMessage(&PsappPsscmCfgLockRespBuff,sizeof(PsappPsscmCfgLockResp),ENT_OAM_OIL, ENT_OAMS_CFG, PSAPP_PSSCM_CFG_LOCK_RESP,0);       

}
void cfgStubSendPsscmCfgAlarmInd( SysAlarm sysAlarm)
{
   PsappPsscmCfgAlarmInd PsappPsscmCfgAlarmIndBuff;

   memcpy((I_U8*)(((I_U8*)&PsappPsscmCfgAlarmIndBuff)+sizeof(SysHdr)),(I_U8*)&sysAlarm,sizeof(SysAlarm));
   cfgStubSendMessage(&PsappPsscmCfgAlarmIndBuff,sizeof(PsappPcuCfgAlarmInd),ENT_PSAPP_PCUH,ENT_OAMS_CFG, PSAPP_PSSCM_CFG_ALARM_IND,0);
}

void cfgStubSendPsscmReviveIpLinkResp(   I_U32  result,I_U8  cause )
{
   OamsCfgPsscmReviveIpLinkResp OamsCfgPsscmReviveIpLinkRespBuff;
   OamsCfgPsscmReviveIpLinkRespBuff.result =result;
   OamsCfgPsscmReviveIpLinkRespBuff.cause=cause;

   cfgStubSendMessage(&OamsCfgPsscmReviveIpLinkRespBuff,sizeof(OamsCfgPsscmReviveIpLinkResp),ENT_OAM_OIL, ENT_OAMS_CFG, PSAPP_PSSCM_CFG_REVIVE_IP_LINK_RESP,0);       

}

void cfgStubSendPsscmCfgLepEnabled()
{
   cfgStubSendMessage(NULL,0,ENT_OAM_OIL, ENT_OAMS_CFG, PSAPP_PSSCM_CFG_LEP_ENABLED,0);       
}
#endif

/************************** Oam_cfg_OIL.h **** End ***********************/
I_S32 cfgStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;

   sndMsgSize = 0;

   printf("\n\t Calling cfgStubSendMessage().....");

   if (bufPtr != NULL)
      sndMsgSize = size;
   else
      sndMsgSize = sizeof(SysHdr);

   if ((sndPtr = (SysHdr *)AlocMsgBuf(sndMsgSize)) == NULL)
   {
      printf("CFG_SEND_ALLOC_FAIL");
      return -1; 
   }

   memset(sndPtr,0,sndMsgSize) ;
   if (bufPtr != NULL)
      memcpy(((I_U8 *)sndPtr), (I_U8*)bufPtr, size);

   sndPtr->msgType = msgType;
   //sndPtr->src.entity = gSrcId;
   sndPtr->src.entity = SrcEntId;
   /* sndPtr->dest.entity = DestEntId;
    */
   sndPtr->dest.entity = DESTINATION;


   printf("\n sndPtr->msgType = %d", sndPtr->msgType);
   printf("\n sndPtr->sHdr.src.entity = %d", sndPtr->src.entity);
   printf("\n sndPtr->sHdr.dest.entity = %d", sndPtr->dest.entity);

   printf("\n Sending message ...........");

   fflush(stdin);
   if (SendMsg(sndPtr, 1, sndMsgSize) < 0)
   {
      printf("\nCFG: In func cfgSendMessage() - msg sending failed");
      DalocMsgBuf((I_PVoid) sndPtr);
      return(-1);
   }
   return(1);
}

I_S32 cfgStubSendCmMessage(  void *buff,I_U32 size,I_U32 MessageType )
{
   sCmMsg* CmMsgPtr ;

   if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(size+sizeof(sCmMsg))) == NULL)
   {
      printf("CFG_SEND_ALLOC_FAIL");
      return -1; 
   }

   CmMsgPtr->sHdr.msgType = MessageType;
   CmMsgPtr->sHdr.src.entity =gSrcId; 
   CmMsgPtr->sHdr.dest.entity = DESTINATION;
   CmMsgPtr->cmHdr.size = size;
   memcpy((((I_U8 *)CmMsgPtr)+sizeof(sCmMsg)),(I_U8*)buff,size);
   if (SendMsg(CmMsgPtr, 1, (size+sizeof(sCmMsg))) < 0)
   {
      printf("\nCFG: In func cfgSendMessage() - msg sending failed");
      DalocMsgBuf((I_PVoid) CmMsgPtr);
      return(-1);
   }
   return(1);

}

I_S32 cfgStubSendCmMessageFromOil(  I_U32 MessageType ,I_U32 result)
{
   sCmMsg* CmMsgPtr ;

   if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(sCmMsg))) == NULL)
   {
      printf("CFG_SEND_ALLOC_FAIL");
      return -1;
   }
   CmMsgPtr->sHdr.msgType = MessageType;
   CmMsgPtr->sHdr.src.entity = gSrcId;
   CmMsgPtr->sHdr.dest.entity = DESTINATION;
   CmMsgPtr->cmHdr.status = result;
   CmMsgPtr->cmHdr.size  = CM_NO_DATA;

   if (SendMsg(CmMsgPtr, 1, (sizeof(sCmMsg))) < 0)
   {
      printf("\nCFG: In func cfgStubSendCmMessageFromOil() - msg sending failed");
      DalocMsgBuf((I_PVoid) CmMsgPtr);
      return(-1);
   }

}
void cfgStubSendDSmmMgsuDriverInitStatus(I_U32 tsiStatus)
{
   /* TODO */
   /*DSmmMgsuDriverInitStatus DSmmMgsuDriverInitStatusBuff;
   DSmmMgsuDriverInitStatusBuff.messageId= MGS_TSM_TSI_DRIVER_INIT_STS;
   DSmmMgsuDriverInitStatusBuff.tsiStatus = tsiStatus;
   cfgStubSendMessage(&DSmmMgsuDriverInitStatusBuff,sizeof(DSmmMgsuDriverInitStatus),ENT_MGS_TSM, ENT_OAMS_CFG, MGS_TSM_TSI_DRIVER_INIT_STS,0);*/

}

void cfgStubSendDTrauMgsuDriverInitStatus(I_U32 dspStatus)
{
   /* TODO */
   /*DTrauMgsuDriverInitStatus DTrauMgsuDriverInitStatusBuff;
   DTrauMgsuDriverInitStatusBuff.messageId=MGS_TRAU_DRIVER_INIT_STATUS;
   DTrauMgsuDriverInitStatusBuff.dspStatus = dspStatus;
   cfgStubSendMessage(&DTrauMgsuDriverInitStatusBuff,sizeof(DSmmMgsuDriverInitStatus),ENT_MGS_TSM, ENT_OAMS_CFG, MGS_TRAU_DRIVER_INIT_STATUS,0);*/

}
void cfgStubSendDTrauMgsuTrauInitResp()
{
   /* TODO */
   /*DTrauMgsuTrauInitResp DTrauMgsuTrauInitRespBuff={0};
   DTrauMgsuTrauInitRespBuff.messageId=MGS_TRAU_INIT_RESP;
   cfgStubSendMessage(&DTrauMgsuTrauInitRespBuff,sizeof(DTrauMgsuTrauInitResp),ENT_MGS_TSM, ENT_OAMS_CFG, MGS_TRAU_INIT_RESP,0);*/

}

void cfgDbInit()
{
   I_S32 retVal;
   I_U8 *ptr=NULL;

   /* Register with imdb server */
   /* ptr = getenv("DB_CFG_FILE"); Connect to DB taking clib.cfg from fixed config path-Guru */
#if 0
   ptr = malloc(20);
   ptr,"../DB-Server-Rel-1.1/DBS/Bin/Host/Config"

      if (ptr == NULL)
      {
         printf("\n env path for DB_CFG_FILE is NULl. Exiting ..... ");
         exit(-1);
      }

#endif
   /*COMP_C  retVal = clib_init("../Config/CP/iclib.cfg");*/
   printf("\n Before DB Connect\n");
   printf("%d ",dbConnect());
   printf("\n AFTER DBCONNECT\n");
   //retVal = clib_init(getenv("DB_CFG_FILE"));
   /*if (retVal != CLIB_SUCCESS)
   //retVal = clib_init(getenv("DB_CFG_FILE"));
   if (retVal != CLIB_SUCCESS)
   {
   printf("\n DB registration failed. retVal = %d Exiting ....... ", retVal);
   cfgPanic(CFG_DB_INIT_FAIL);
   } */

} /* End of function cfgDbInit() */

void cfgStubFrmwrkInit()
{
   I_U32 retVal;
   printf("\nCFG: Calling function cfgFrmwrkInit()");
   retVal = RegisterWithIpcFrmwrk(gSrcId, "CFG");
   printf("\nReturn Value of IPC Registration: %d\n",retVal);
   if (retVal < ZERO)
      cfgPanic(CFG_REGD_IPC_FAIL);
   printf("\nCFG: Calling function cfgFrmwrkInit() Exiting");

} /* End of function cfgFrmwrkInit() */




/******************************************** Code Added by Sanjeev ********************************************************
Date :18-10-2007    Remarks: Code added to run multiple instances of stubs based on the entity id.
This code changes is part of SSI Integration....
 *********************************************************************************************
 ******************************                   Trxh Stub *************************************************************************************************************************************************************************/
void startTrxh()
{
   OamsCfgTrxhLockReq* TrxhLockReq;
   OamsCfgTrxhUnlockReq* TrxhUnlockReq;
   SysAlarm sysAlarmBuff;
   for (;;)
   {
      //printf("\n cleaning  the  message queue....");
      gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
      if (gCfgMsgBuf == NULL)
      {
         continue;
      }
      else
      {
         printf("\n Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRecvMsgSize);
         switch((((SysHdr*) gCfgMsgBuf)->msgType)) /*switch on messages...*/
         {
            case OAMS_CFG_TRXH_UNLOCK_REQ:
               {
                  printf("\nReceived UNLOCK REQUEST");
                  TrxhUnlockReq = (OamsCfgTrxhUnlockReq *)gCfgMsgBuf;
                  printf(" \n OamsCfgTrxhUnlockReq recevied with objType = %d",TrxhUnlockReq->objType);
                  printf("\nSending UNLOCK Response");
                  cfgStubSendTrxhCfgUnlockResp(TrxhUnlockReq->objType,TrxhUnlockReq->objId,0);
                  sysAlarmBuff.sysalarmId = PTRX_ENABLED;
                  sysAlarmBuff.key1 = OAMS_OBJTYPE_PTRX;
                  sysAlarmBuff.key2= TrxhUnlockReq->objId;
                  printf("\nSending Alarm");
                  cfgStubSendTrxhCfgAlarmInd(sysAlarmBuff);
               }
               break;    
            case OAMS_CFG_TRXH_LOCK_REQ:
               {
                  printf("\nReceived LOCK REQUEST");
                  TrxhLockReq = (OamsCfgTrxhLockReq *)gCfgMsgBuf;
                  printf("\nSending LOCK Response");
                  cfgStubSendTrxhCfgLockResp(TrxhLockReq->objType,TrxhLockReq->objId,TrxhLockReq->e1Num);
                  sysAlarmBuff.sysalarmId = PTRX_DISABLED;
                  sysAlarmBuff.key1 = OAMS_OBJTYPE_PTRX;
                  sysAlarmBuff.key2= TrxhLockReq->objId;
                  printf("\nSending Alarm");
                  cfgStubSendTrxhCfgAlarmInd(sysAlarmBuff);

               }
               break;

         } //switch end...

      } ///else.. end


   }//for  ends here..

}
/************************************************************************************************/
/***********************************************************************************************************************
 ******************************                   Cellh Stub  ******************************************************
 ************************************************************************************************************************/
void startCellh()
{
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   SysAlarm sysAlarmBuff;
   for (;;)
   {
      //   printf("\n cleaning  the  message queue....");
      gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
      if (gCfgMsgBuf == NULL)
      {
         continue;
      }
      else
      {
         printf("\n Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRecvMsgSize);
         switch((((SysHdr*) gCfgMsgBuf)->msgType)) /*switch on messages...*/
         {
            case OAMS_CFG_CELLH_LOCK_REQ :
               {
                  printf("Test Case 1 :Received OAMS_CFG_CELLH_LOCK_REQ \n");
                  oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
                  cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
               }
               break;
            case OAMS_CFG_CELLH_UNLOCK_REQ  :
               {
                  oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
                  cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac); 
               }
               break;
            case OAMS_CFG_CELLH_BLOCK_IND :
               {
                  printf("Cell Shut down indicator received\n");
               }
               break;  

         } //switch end...

      } ///else.. end


   }//for  ends here..

}
/**************************************************************************************************/
/***********************************************************************************************************************
 ******************************                   Grhm Stub  ******************************************************
 ************************************************************************************************************************/
void startGrhm()
{
   /*
      OAMS_CFG_GRHM_START_CHAN_ALLOC         
      OAMS_CFG_GRHM_STOP_CHAN_ALLOC          
      OAMS_CFG_GRHM_LOCK_REQ                 
      OAMS_CFG_GRHM_UNLOCK_REQ               
      OAMS_CFG_GRHM_START_STATIC_SWITCHING  
    */
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   SysAlarm sysAlarmBuff;
   I_U32   tei ;
   I_PVoid bufferPtr;
   I_S32       msgSize,size ;
   for (;;)
   {
      gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
      if (gCfgMsgBuf == NULL)
      {
         continue;
      }
      else
      {
         printf("\n Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRecvMsgSize);
         switch((((SysHdr*) gCfgMsgBuf)->msgType)) /*switch on messages...*/
         {
            case  OAMS_CFG_GRHM_LOCK_REQ:
               {
                  OamsCfgGrhmLockReq*  grhmLockReq;
                  grhmLockReq = (OamsCfgGrhmLockReq *)gCfgMsgBuf ;
                  // Send response from stub to CFG.
                  cfgStubSendGrhmCfgLockResp(grhmLockReq->objType, grhmLockReq->objectId);
                  //send Alarm..
                  SysAlarm sysAlarmBuff;
                  //sysAlarmBuff.sysalarmId = LOCK_COMPLETE;
                  sysAlarmBuff.key1 = grhmLockReq->objType;
                  sysAlarmBuff.key2 = grhmLockReq->objectId;
                  sysAlarmBuff.key3 = 0;
                  sysAlarmBuff.key4 = 0;
                  cfgStubSendGrhmCfgAlarmInd(sysAlarmBuff);
               }
               break;
            case  OAMS_CFG_GRHM_UNLOCK_REQ:
               {
                  OamsCfgGrhmUnlockReq*  grhmUnlockReq; 
                  grhmUnlockReq = (OamsCfgGrhmUnlockReq *) gCfgMsgBuf;
                  // Send response from stub to CFG.
                  printf("grhmUnlockReq->objectId  %ld",grhmUnlockReq->objectId);
                  cfgStubSendGrhmCfgUnlockResp(grhmUnlockReq->objType,grhmUnlockReq->objectId);
                  //send Alarm..
                  SysAlarm sysAlarmBuff;
                  //sysAlarmBuff.sysalarmId = UNLOCK_COMPLETE;
                  sysAlarmBuff.key1 = grhmUnlockReq->objType;
                  sysAlarmBuff.key2 = grhmUnlockReq->objectId;
                  sysAlarmBuff.key3 = 0;
                  sysAlarmBuff.key4 = 0;
                  cfgStubSendGrhmCfgAlarmInd(sysAlarmBuff);

                  printf("\nSending the OAMS_CFG_GRHM_UNLOCK_RESP ...\n");
               }
               break;
            case OAMS_CFG_GRHM_START_CHAN_ALLOC:
               {
                  printf("OAMS_CFG_GRHM_START_CHAN_ALLOC: has been received..\n");      
               }
               break;
            case OAMS_CFG_GRHM_STOP_CHAN_ALLOC   :
               {
                  printf("GRHM STUB: CFG_GRHM_STOP_CHAN_ALLOC indicator received"); 
               }
               break;
            case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
               {
                  printf(" Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
               }   
               break; 
            case OAMS_TRXH_GRHM_CRE_CHN_REQ:
#if 0
               fprintf(stderr,"CREATE CHANNEL REQ received from TRXH\n") ;
               tei = ((OamsTrxhGrhmCreChanReq *)gCfgMsgBuf)->tei;
               bufferPtr = Build_CsappGrhmTrxhCreChanResp( tei, &size);
               if (bufferPtr != NULL && size > 0)
               {
                  if(SendMsg(bufferPtr, 1, size) <= 0)
                  {
                     exit(0);
                  }
               }
#endif
               break ;
            case OAMS_TRXH_GRHM_DEL_CHN_REQ:
               fprintf(stderr,"Del Channel Req Received from Trxh\n") ;
               tei = ((OamsTrxhGrhmDelChanReq *)gCfgMsgBuf)->tei;
               bufferPtr = Build_CsappGrhmTrxhDelChanResp( tei, &size);
               if (bufferPtr != NULL && size > 0)
               {
                  if(SendMsg(bufferPtr, 1, size) <= 0)
                  {
                     exit(0);
                  }
               }
               break ;

         } //switch end...

      } ///else.. end

   }//for  ends here..

}
/*************************************************************************************************/
/***********************************************************************************************************************
 ******************************                   Pcuh Stub  ******************************************************
 ************************************************************************************************************************/
#if 0
void startPcuh()
{
   /*
      OAMS_CFG_PCUH_CELL_SHUTDOWN_IND             
      OAMS_CFG_PCUH_LOCK_REQ                      
      OAMS_CFG_PCUH_UNLOCK_REQ                    
      OAMS_CFG_PCUH_CELL_ENABLED_REQ             
      OAMS_CFG_PCUH_ALL_NSVC_DISABLED_REQ       
      OAMS_CFG_PCUH_FIRST_NSVC_ENABLED_REQ     
      OAMS_CFG_PCUH_BVC_RESET_REQ             
    */
   SysAlarm sysAlarmBuff;
   for (;;)
   {
      gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
      if (gCfgMsgBuf == NULL)
      {
         continue;
      }
      else
      {
         printf("\n Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRecvMsgSize);
         switch((((SysHdr*) gCfgMsgBuf)->msgType)) /*switch on messages...*/
         {
            case OAMS_CFG_PCUH_CELL_SHUTDOWN_IND  :
               {
                  printf("Test Case 5 : CFG_PCU_CELL_SHUTDOWN_IND indicator received\n");
               }
               break;
            case OAMS_CFG_PCUH_LOCK_REQ :
               {
                  OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr; 
                  oamsCfgPcuLockReqPtr = (OamsCfgPcuLockReq *) gCfgMsgBuf;
                  cfgStubSendPcuCfgLockResp(oamsCfgPcuLockReqPtr->objType,oamsCfgPcuLockReqPtr->objId,oamsCfgPcuLockReqPtr->lac);
               }
               break;
            case OAMS_CFG_PCUH_UNLOCK_REQ  :
               {
                  OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr;
                  oamsCfgPcuUnlockReqPtr    = (OamsCfgPcuUnlockReq *)gCfgMsgBuf;
                  cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0);
               }
               break;
            case OAMS_CFG_PCUH_CELL_ENABLED_REQ :
               {
                  OamsCfgPcuCellEnabledReq* oamsCfgPcuCellEnabledReqPtr; 
                  oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf;
                  cfgStubSendCfgPcuCellEnabledResp(oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac);

               }
               break;
            case OAMS_CFG_PCUH_FIRST_NSVC_ENABLED_REQ :
               {
                  cfgStubSendPcuCfgFirstNsvcEnabledResp();
               }
               break;

         } //switch end...

      } ///else.. end


   }//for  ends here..

}
#endif
/*************************************************************************************************/

/*************************************************************************************************
 ******************************                   Scm Stub  ******************************************************
 ************************************************************************************************************************/
/*

   OAMS_CFG_SCM_UNLOCK_REQ 
   OAMS_CFG_SCM_LOCK_REQ 

 */
#if 0
void startOil()
{
   SysAlarm sysAlarmBuff;
   for (;;)
   {
      gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
      if (gCfgMsgBuf == NULL)
      {
         continue;
      }
      else
      {
         printf("\n Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRecvMsgSize);
         switch((((SysHdr*) gCfgMsgBuf)->msgType)) /*switch on messages...*/
         {
            case OAMS_CFG_SCM_UNLOCK_REQ:
               {
                  OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;
                  if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
                  {
                     SysAlarm SysAlarmBuff;
                     cfgStubSendCfgScmUnLockResp(OamsCfgScmUnlockReqPtr->ObjType,OamsCfgScmUnlockReqPtr->lengthOfList,OamsCfgScmUnlockReqPtr->objectIdList, 0,0,0);
                     /* Also Initiate A interface UP Alaram towards the CFG */
                     cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_ALLOWED);

                  }
                  else if (OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_E1  || OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_TIMESLOT )
                  { 
                     /*void cfgStubSendCfgScmUnLockResp(I_U8  ObjType,  I_U16  lengthOfList, I_U32 objectIdList[], I_U32  e1Num,I_U32 tsNum, I_U8 reason)
                      */
                     cfgStubSendCfgScmUnLockResp( OamsCfgScmUnlockReqPtr->ObjType, OamsCfgScmUnlockReqPtr->lengthOfList,OamsCfgScmUnlockReqPtr->objectIdList,OamsCfgScmUnlockReqPtr->e1Num,OamsCfgScmUnlockReqPtr->tsNum,0);
                     cfgStubSendScmCfgAlarmInd(AINTERFACE_ENABLED);
                  }

               }
               break;
            case OAMS_CFG_SCM_LOCK_REQ :
               {
                  OamsCfgScmLockReq *scmlockReq;
                  scmlockReq = (OamsCfgScmLockReq  *)gCfgMsgBuf;
                  if(scmlockReq->ObjType == OAMS_OBJTYPE_E1 || scmlockReq->ObjType == OAMS_OBJTYPE_TIMESLOT)
                  {
                     SysAlarm sysAlarm;
                     // Send response from stub to CFG.
                     cfgStubSendCfgScmLockResp(scmlockReq->ObjType, scmlockReq->lengthOfList,scmlockReq->objectIdList, scmlockReq->e1Num,scmlockReq->tsNum,0);
                     cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);

                  }
                  else
                  {   
                     cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
                     cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_PROHIBITED);
                  }                
               }
               break;
            case OAMS_CFG_PSSCM_LOCK_REQ :
               {

                  if ((( (OamsCfgPsscmLockReq *)gCfgMsgBuf)->ObjType) == OAMS_OBJTYPE_CELL || (( (OamsCfgPsscmLockReq *)gCfgMsgBuf)->ObjType) == OAMS_OBJTYPE_E1 || (( (OamsCfgPsscmLockReq *)gCfgMsgBuf)->ObjType) == OAMS_OBJTYPE_TIMESLOT )
                  {
                     OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr ;
                     oamsCfgPsscmLockReqPtr = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
                     cfgStubSendPsscmCfgLockResp(oamsCfgPsscmLockReqPtr->ObjType,oamsCfgPsscmLockReqPtr->lengthOfList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->e1Num,oamsCfgPsscmLockReqPtr->lac);

                  }
                  else
                  {
                     /* . It will set NSVC and FR operational state as "Disabled" in DB
                        and will send Alarm (SCN: NSVC, OST=Disabled) and
                        Alarm (SCN: FR, OST=Disabled) to CFG to be forwarded to OMC. */
                     SysAlarm sysAlarmBuff;
                     sysAlarmBuff.sysalarmId = NSVC_DISABLED;
                     cfgStubSendPsscmCfgAlarmInd(sysAlarmBuff);
                     sysAlarmBuff.sysalarmId = FRLINK_DISABLED;
                     OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr ;
                     oamsCfgPsscmLockReqPtr = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
                     cfgStubSendPsscmCfgLockResp(OAMS_OBJTYPE_GBINTERFACE,oamsCfgPsscmLockReqPtr->lengthOfList,oamsCfgPsscmLockReqPtr->ObjId, oamsCfgPsscmLockReqPtr->e1Num,oamsCfgPsscmLockReqPtr->lac);

                  }
               }
               break;
            case OAMS_CFG_PSSCM_UNLOCK_REQ :
               {

                  OamsCfgPsscmUnlockReq* oamsCfgPsscmUnlockReqPtr;
                  oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf;
                  cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num,0,0,oamsCfgPsscmUnlockReqPtr->lac);
               }
               break;
            case OAMS_CFG_PSSCM_NSVC_RESET_REQ:
               {
                  OamsCfgPsscmNsvcResetReq *OamsCfgPsscmNsvcResetReqBuff;
                  OamsCfgPsscmNsvcResetReqBuff = (OamsCfgPsscmNsvcResetReq *) gCfgMsgBuf;
                  printf("NSVC Rest Request contents are: NSVC ID %d\n", OamsCfgPsscmNsvcResetReqBuff->nsvcId);
               }
               break;

         } //switch end...

      } ///else.. end


   }//for  ends here..

}
#endif
/*************************************************************************************************/

/*********************************************** CM stub... *******************************************************/

void startCm()
{
   int choice;
   void BSSLOCK();
   void BSSUNLOCK();
   void CELLLOCK();
   void CELLUNLOCK();   
   void CELLSHUTDOWN();
   void TRXHLOCK();
   void  TRXHUNLOCK();
   void  E1LOCK();
   void  E1UNLOCK ();
   void  TIMESLOTLOCK();
   void  TIMESLOTUNLOCK();
   printf("\nEnter The Table Name to be Set..\n");
   printf("\n 1 - BSS LOCK\n 2 - BSS UNLOCK\n 3 - CELL LOCK\n 4 - CELL UNLOCK\n 5 - CELL SHUTDOWN\n 6 - TRXH LOCK\n 7 - TRXH UNLOCK\n  8 - E1 LOCK\n 9 - E1 UNLOCK\n 10 - TIMESLOT LOCK\n 11 - TIMESLOT UNLOCK\n");
   scanf("%d",&choice);
   switch(choice)
   {
      case 1:
         BSSLOCK();
         break;
      case 2:
         BSSUNLOCK();
         break;
      case 3:
         CELLLOCK();
         break;
      case 4:
         CELLUNLOCK();
         break;
      case 5:
         CELLSHUTDOWN();
         break;
      case 6:
         //TRXHLOCK();
         break;
      case 7:
         //TRXHUNLOCK();
         break;
      case 8:
         /*  E1LOCK();*/
         break;
      case 9:
         /*  E1UNLOCK();*/
         break;
      case 10:
 	/*  TIMESLOTLOCK(); */
         break;
      case 11:
        /*  TIMESLOTUNLOCK();*/
         break;
      default:
         printf("\n Invalid choice..\n");

   } 
}

void BSSLOCK()
{
   BssTableIndices bssTableIndicesbuff;
   BssTableApi *bssTableApibuff;
   printf("\nEnter the Bsc Id \n");
   scanf("%d",&bssTableIndicesbuff.bscId); 
   if(getBssTable(&bssTableIndicesbuff,&bssTableApibuff) == CLIB_SUCCESS )
   {
      bssTableApibuff->adminState = 0;  /* locked */
      cfgStubSendCmMessage(bssTableApibuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
   }
   else
      printf("\n No rows in BSS Table\n");
}


void BSSUNLOCK()
{
   BssTableIndices bssTableIndicesbuff;
   BssTableApi *bssTableApibuff;
   printf("\nEnter the Bsc Id \n");
   scanf("%d",&bssTableIndicesbuff.bscId);  
   if(getBssTable(&bssTableIndicesbuff,&bssTableApibuff) == CLIB_SUCCESS )
   {
      bssTableApibuff->adminState = 1;  /* unlocked */
      cfgStubSendCmMessage(bssTableApibuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
   }
   else
      printf("\n No rows in BSS Table\n");
}

void CELLLOCK()
{
   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   printf("Enter the CellId & Lac\n");
   scanf("%d",&CellTableIndicesBuff.cellId);
   scanf("%d",&CellTableIndicesBuff.lac);
   if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
   {
      CellTableApiPtr->adminState = 0; /* locked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
   }

} 

void CELLUNLOCK()
{
   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   printf("Enter the CellId & Lac\n");
   scanf("%d",&CellTableIndicesBuff.cellId);
   scanf("%d",&CellTableIndicesBuff.lac);
   if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
   {
      CellTableApiPtr->adminState = 1; /* unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
   }

}

void CELLSHUTDOWN()
{
   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   printf("Enter the CellId & Lac\n");
   scanf("%d",&CellTableIndicesBuff.cellId);
   scanf("%d",&CellTableIndicesBuff.lac);
   if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
   {
      CellTableApiPtr->adminState = 2; /*shutdown*/
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
   }

}

/* void TRXHLOCK()
{
   PhysicalTrxPreconfiguredTableApi *PhysicalTrxPreconfiguredTableApiBuff = {0};
   PhysicalTrxPreconfiguredTableIndices PhysicalTrxPreconfiguredTableSecIndicesbuff;   
   printf("Enter the PtrxId ");
   scanf("%d",&PhysicalTrxPreconfiguredTableSecIndicesbuff.ptrxId); 
   if ( getPhysicalTrxPreconfiguredTable(&PhysicalTrxPreconfiguredTableSecIndicesbuff,&PhysicalTrxPreconfiguredTableApiBuff) == CLIB_SUCCESS )
   {
      PhysicalTrxPreconfiguredTableApiBuff->adminState=0; 
      cfgStubSendCmMessage(PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);

   }
} 
void TRXHUNLOCK()
{
   PhysicalTrxPreconfiguredTableApi *PhysicalTrxPreconfiguredTableApiBuff = {0};
   PhysicalTrxPreconfiguredTableIndices PhysicalTrxPreconfiguredTableSecIndicesbuff;
   printf("Enter the PtrxId ");
   scanf("%d",&PhysicalTrxPreconfiguredTableSecIndicesbuff.ptrxId);
   if ( getPhysicalTrxPreconfiguredTable(&PhysicalTrxPreconfiguredTableSecIndicesbuff,&PhysicalTrxPreconfiguredTableApiBuff) == CLIB_SUCCESS )
   {
      PhysicalTrxPreconfiguredTableApiBuff->adminState=1; 
      cfgStubSendCmMessage(PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);

   }
} */


I_PVoid Build_CsappGrhmTrxhCreChanResp(I_U32 tei, I_S32 *size)
{
   CsappGrhmTrxhCreChanAck    *msgPtr ;

   //I_U32 dinstid=0;
   I_U16 len=0;

   //printf(" Entered Inst Id = %d \n", dinstid);

   len = sizeof(CsappGrhmTrxhCreChanAck);
   if((msgPtr = (CsappGrhmTrxhCreChanAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }


   //Filling GRHM_TRXH_CRE_CHAN_RESP Messages
   msgPtr->tei = tei ;
   *size=len;

   FILL_SYS_HDR(&(msgPtr->sysHdr),CSAPP_GRHM_TRXH_CRE_CHN_ACK, 1,0, ENT_CSAPP_GRHM ,0,0, ENT_OAMS_TRXH,0);

   fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
   fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

   return  msgPtr;

}// Build_CsappGrhmTrxhCreChanRespMsg Complete




I_PVoid Build_CsappGrhmTrxhDelChanResp(I_U32 tei, I_S32 *size)
{
   CsappGrhmTrxhDelChanAck *msgPtr ;

   //I_U32 dinstid=0;
   I_U16 len=0;

   //printf(" Entered Inst Id = %d \n", dinstid);

   len = sizeof(CsappGrhmTrxhDelChanAck);
   if((msgPtr = (CsappGrhmTrxhDelChanAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
   }

   //Filling GRHM_TRXH_DEL_CHAN_RESP Messages
   msgPtr->tei = tei ;
   *size=len;

   FILL_SYS_HDR(&(msgPtr->sysHdr),CSAPP_GRHM_TRXH_DEL_CHN_ACK, 1,0, ENT_CSAPP_GRHM ,0,0, ENT_OAMS_TRXH,0);

   fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
   fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

   return  msgPtr;

}// Build_CsappGrhmTrxhDelChanRespMsg Complete


void startSCM()
{
   SysAlarm sysAlarmBuff;
   for (;;)
   {
      gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
      if (gCfgMsgBuf == NULL)
      {
         continue;
      }
      else
      {
         printf("\n Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRecvMsgSize);
	
                       ((SysHdr *)gCfgMsgBuf)->src.entity=ENT_IPC_SCMIF;
                       ((SysHdr *)gCfgMsgBuf)->dest.entity=ENT_OAM_OIL;
                       ((SysHdr *)gCfgMsgBuf)->msgType=OAMS_SCM_CFG_LOCK_RESP;

         switch(((SysHdr*) (gCfgMsgBuf+sizeof(SysHdr)+sizeof(I_U32)))->msgType) /*switch on messages...*/
         {
            case OAMS_CFG_SCM_UNLOCK_REQ:
               {
                  int sendSCCP=0;
                  OamsScmCfgUnlockResp *scmlockResp;
                  scmlockResp=(OamsScmCfgUnlockResp *)(gCfgMsgBuf+sizeof(SysHdr)+sizeof(I_U32)) ;
                  scmlockResp->sysHdr.sHdr.src.entity=ENT_SKS_SCM;
                  scmlockResp->sysHdr.sHdr.dest.entity=ENT_OAM_OIL;
                  scmlockResp->sysHdr.sHdr.msgType=OAMS_SCM_CFG_UNLOCK_RESP;
                  if(scmlockResp->ObjType == OAMS_OBJTYPE_AINTERFACE)  
                         sendSCCP=1;             
                  SendMsg(gCfgMsgBuf,1,gRecvMsgSize);
                  if(sendSCCP==1)                
                  {

                   void  *sndPtr;        
                   I_S16  size;
                   size=sizeof(SysHdr) + sizeof(I_U32) + sizeof(sCmMsg) + sizeof(Alarm_NWSTACK);
                   if ((sndPtr = AlocMsgBuf(size)) == NULL)
                   {
                          printf("CFG_SEND_ALLOC_FAIL");
                          //return -1;
                   }
                   /*Filling outermost syshdr **************/
                   ((SysHdr*)(sndPtr))->src.entity=ENT_IPC_SCMIF;
                   ((SysHdr*)(sndPtr))->dest.entity=ENT_OAM_OIL;                   
                   ((SysHdr*)(sndPtr))->msgType=OAMS_SCM_CFG_ALARM_IND; 
                     
                   /*****************************************/
                   ( (sCmMsg*) (sndPtr + sizeof(SysHdr) + sizeof(I_U32) ) )->sHdr.src.entity=ENT_SKS_SCCP;
                   ( (sCmMsg*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) ) )->sHdr.msgType=OAMS_SCM_CFG_ALARM_IND;
                   ( (sCmMsg*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) ) )->cmHdr.size=sizeof(Alarm_NWSTACK);
                   ( (Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) )->FieldId=NWSTACK_LINKSET_LINKCODE;
                 ((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) ) ->AlarmID =SCCP_SCMG_SS_ALLOWED;
                 ((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) )->AlarmLevel=1;
                 SendMsg(sndPtr,1,size);
                  }  

               }
               break;
            case OAMS_CFG_SCM_LOCK_REQ :
               {
                  int sendSCCP=0;
                  OamsScmCfgLockResp *scmlockResp;
                  scmlockResp=(OamsScmCfgLockResp *)(gCfgMsgBuf+sizeof(SysHdr)+sizeof(I_U32)) ;  
		  scmlockResp->sysHdr.sHdr.src.entity=ENT_SKS_SCM;
                  scmlockResp->sysHdr.sHdr.dest.entity=ENT_OAM_OIL;
                  scmlockResp->sysHdr.sHdr.msgType=OAMS_SCM_CFG_LOCK_RESP;
                  if(scmlockResp->ObjType == OAMS_OBJTYPE_AINTERFACE)  
                         sendSCCP=1;             
		  SendMsg(gCfgMsgBuf,1,gRecvMsgSize);
                  if(sendSCCP==1)                
                  {

                   void  *sndPtr;        
                   I_S16  size;
                   size=sizeof(SysHdr) + sizeof(I_U32) + sizeof(sCmMsg) + sizeof(Alarm_NWSTACK);
                   if ((sndPtr = AlocMsgBuf(size)) == NULL)
                   {
                          printf("CFG_SEND_ALLOC_FAIL");
                          //return -1;
                   }
                   /*Filling outermost syshdr **************/
                   ((SysHdr*)(sndPtr))->src.entity=ENT_IPC_SCMIF;
                   ((SysHdr*)(sndPtr))->dest.entity=ENT_OAM_OIL;                   
                   ((SysHdr*)(sndPtr))->msgType=OAMS_SCM_CFG_ALARM_IND; 
                     
                   /*****************************************/
                   ( (sCmMsg*) (sndPtr + sizeof(SysHdr) + sizeof(I_U32) ) )->sHdr.src.entity=ENT_SKS_SCCP;
                   ( (sCmMsg*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) ) )->sHdr.msgType=OAMS_SCM_CFG_ALARM_IND;
                   ( (sCmMsg*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) ) )->cmHdr.size=sizeof(Alarm_NWSTACK);
                   ( (Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) )->FieldId=NWSTACK_LINKSET_LINKCODE;
                 ((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) ) ->AlarmID =SCCP_SCMG_SS_PROHIBITED;
                 ((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) )->AlarmLevel=1;
                 SendMsg(sndPtr,1,size);
                }
		  
               }
               break;
#if 0
            case BSC_API_SET_LINKADMINSTATETABLE :
               {
                      
                   void  *sndPtr;        
                   I_S16  size;
                    BscApiSetLinkAdminStateTable *scmlockResp;
                    scmlockResp=(BscApiSetLinkAdminStateTable *)(gCfgMsgBuf+sizeof(SysHdr)+sizeof(I_U32)) ;  
                   printf("BSC_API_SET_LINKADMINSTATETABLE is received from CFG\n"); 
                   size=sizeof(SysHdr) + sizeof(I_U32) + sizeof(sCmMsg) + sizeof(Alarm_NWSTACK);
                   if ((sndPtr = AlocMsgBuf(size)) == NULL)
                   {
                          printf("CFG_SEND_ALLOC_FAIL");
                          //return -1;
                   }
                   /*Filling outermost syshdr **************/
                   ((SysHdr*)(sndPtr))->src.entity=ENT_IPC_SCMIF;
                   ((SysHdr*)(sndPtr))->dest.entity=ENT_OAM_OIL;                   
                   ((SysHdr*)(sndPtr))->msgType=OAMS_SCM_CFG_ALARM_IND; 
                     
                   /*****************************************/
                   ( (sCmMsg*) (sndPtr + sizeof(SysHdr) + sizeof(I_U32) ) )->sHdr.src.entity=ENT_SKS_SCCP;
                   ( (sCmMsg*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) ) )->sHdr.msgType=OAMS_SCM_CFG_ALARM_IND;
                   ( (sCmMsg*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) ) )->cmHdr.size=sizeof(Alarm_NWSTACK);
                   ( (Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) )->FieldId=NWSTACK_LINKSET_LINKCODE;
		   if ( scmlockResp->tblObject.linkAdminadminState == 0 )
                 	((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) ) ->AlarmID =SCCP_SCMG_SS_PROHIBITED;
		    else
                 	((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) ) ->AlarmID =SCCP_SCMG_SS_ALLOWED;
                 ((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) )->AlarmLevel=1;
		  SendMsg(gCfgMsgBuf,1,gRecvMsgSize);
                 SendMsg(sndPtr,1,size);
                 printf("BSC_API_SET_LINKADMINSTATETABLE RESP has been sent to CFG\n"); 
                 printf("Alarm has been sent to CFG\n"); 
                }
		  
	       break;
#endif
            default:
                  ((CmApplHdr*)(gCfgMsgBuf + sizeof(SysHdr) + sizeof(I_U32) + sizeof(SysHdr)))->status = CM_SUCCESS;
                  SendMsg(gCfgMsgBuf,1,gRecvMsgSize);

         } //switch end...

      } ///else.. end


   }//for  ends here..

}


#if 0
void TIMESLOTLOCK()
{
   TimeSlotTableApi *inData;
   TimeSlotTableIndices timeSlotTableIndices;
   
   printf("\nEnter the E1Num Id \n");
   scanf("%d",&timeSlotTableIndices.e1Num); 
   printf("\nEnter the Timeslot Id \n");
   scanf("%d",&timeSlotTableIndices.tsNum); 
   if(getTimeSlotTable(&timeSlotTableIndices,&inData) == CLIB_SUCCESS )
   {
      inData->adminState = 0;  /* locked */
      cfgStubSendCmMessage(inData,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);
   }
   else
      printf("\n No rows in Timeslot  Table\n");
}


void TIMESLOTUNLOCK()
{
   TimeSlotTableApi *inData;
   TimeSlotTableIndices timeSlotTableIndices;

   printf("\nEnter the E1Num Id \n");
   scanf("%d",&timeSlotTableIndices.e1Num);
   printf("\nEnter the Timeslot Id \n");
   scanf("%d",&timeSlotTableIndices.tsNum);
   if(getTimeSlotTable(&timeSlotTableIndices,&inData) == CLIB_SUCCESS )
                     /* Send NSVC Disabled Alarm*/{
      inData->adminState = 1;  /* unlocked */
      cfgStubSendCmMessage(inData,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);
   }
   else
      printf("\n No rows in Timeslot  Table\n");
}
#endif
#if 0
void startPSSCM()
{
   SysAlarm sysAlarmBuff;
   for (;;)
   {
      gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
      if (gCfgMsgBuf == NULL)
      {
         continue;
      }
      else
      {
         printf("\n Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRecvMsgSize);
         switch((((SysHdr*) gCfgMsgBuf)->msgType)) /*switch on messages...*/
         {
            case OAMS_CFG_PSSCM_LOCK_REQ :
               {
                  OamsCfgPsscmLockReq *psscmlockResp;
                  psscmlockResp=(OamsCfgPsscmLockReq *)(gCfgMsgBuf) ;
                  psscmlockResp->sysHdr.src.entity=ENT_PSSTK_PSSCM;
                  psscmlockResp->sysHdr.dest.entity=ENT_OAM_OIL;
                  psscmlockResp->sysHdr.msgType=PSAPP_PSSCM_CFG_LOCK_RESP;
                  SendMsg(gCfgMsgBuf,1,gRecvMsgSize);
                  /* Send NSVC Disabled Alarm  */
                  /**********************************************************************************************************************/ 
                  void  *sndPtr;
                   I_S16  size;
                   size=sizeof(SysHdr) + sizeof(I_U32) + sizeof(sCmMsg) + sizeof(Alarm_NWSTACK);
                   if ((sndPtr = AlocMsgBuf(size)) == NULL)
                   {
                          printf("CFG_SEND_ALLOC_FAIL");
                          //return -1;
                   }
                   /*Filling outermost syshdr **************/
                   ((SysHdr*)(sndPtr))->src.entity=ENT_IPC_SCMIF;
                   ((SysHdr*)(sndPtr))->dest.entity=ENT_OAM_OIL;
                   ((SysHdr*)(sndPtr))->msgType=OAMS_SCM_CFG_ALARM_IND;

                   /*****************************************/
                   ( (sCmMsg*) (sndPtr + sizeof(SysHdr) + sizeof(I_U32) ) )->sHdr.src.entity=ENT_SKS_SCCP;
                   ( (sCmMsg*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) ) )->sHdr.msgType=PSAPP_PSSCM_CFG_ALARM_IND;
                   ( (sCmMsg*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) ) )->cmHdr.size=sizeof(Alarm_NWSTACK);
                   ( (Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) )->FieldId=NWSTACK_LINKSET_LINKCODE;
                 ((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) ) ->AlarmID = NSVC_DISABLED;
                 ((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) )->AlarmLevel=1;
                 SendMsg(sndPtr,1,size);
                  /************************************************************************************************************************/ 
                 
               }
               break;
            case OAMS_CFG_PSSCM_UNLOCK_REQ :
               {
                  OamsCfgPsscmUnlockReq *psscmunlockResp;
                  psscmunlockResp=(OamsCfgPsscmUnlockReq *)(gCfgMsgBuf) ;
                  psscmunlockResp->sysHdr.src.entity=ENT_PSSTK_PSSCM;
                  psscmunlockResp->sysHdr.dest.entity=ENT_OAM_OIL;
                  psscmunlockResp->sysHdr.msgType=PSAPP_PSSCM_CFG_UNLOCK_RESP;
                  SendMsg(gCfgMsgBuf,1,gRecvMsgSize);
                  /* Send NSVC Enabled Alarm  */
                  /**********************************************************************************************************************/
                  void  *sndPtr;
                   I_S16  size;
                   size=sizeof(SysHdr) + sizeof(I_U32) + sizeof(sCmMsg) + sizeof(Alarm_NWSTACK);
                   if ((sndPtr = AlocMsgBuf(size)) == NULL)
                   {
                          printf("CFG_SEND_ALLOC_FAIL");
                          //return -1;
                   }
                   /*Filling outermost syshdr **************/
                   ((SysHdr*)(sndPtr))->src.entity=ENT_IPC_SCMIF;
                   ((SysHdr*)(sndPtr))->dest.entity=ENT_OAM_OIL;
                   ((SysHdr*)(sndPtr))->msgType=OAMS_SCM_CFG_ALARM_IND;

                   /*****************************************/
                   ( (sCmMsg*) (sndPtr + sizeof(SysHdr) + sizeof(I_U32) ) )->sHdr.src.entity=ENT_SKS_SCCP;
                   ( (sCmMsg*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) ) )->sHdr.msgType=PSAPP_PSSCM_CFG_ALARM_IND;
                   ( (sCmMsg*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) ) )->cmHdr.size=sizeof(Alarm_NWSTACK);
                   ( (Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) )->FieldId=NWSTACK_LINKSET_LINKCODE;
                 ((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) ) ->AlarmID = NSVC_ENABLED;
                 ((Alarm_NWSTACK*)(sndPtr + sizeof(SysHdr)+sizeof(I_U32) + sizeof(sCmMsg) ) )->AlarmLevel=1;
                 SendMsg(sndPtr,1,size);
                  /************************************************************************************************************************/


               }
               break;
            case OAMS_CFG_PSSCM_NSVC_RESET_REQ:
               {
               }
               break;

         } //switch end...

      } ///else.. end


   }//for  ends here..

}
#endif
void startMGS()
{
   I_U8* msgBuffer;
   I_U8 option;
   I_S8* msgName = NULL;
   I_S8 retVal;
   I_S32 sndMsgSz;
   I_U8* msgRcvP = NULL;
   for (;;)
   {
      gCfgMsgBuf =(void*) RecvMsg(gSrcId, &gRecvMsgSize); 
      msgRcvP=gCfgMsgBuf;
      if (gCfgMsgBuf == NULL)
      {
         continue;
      }
      else
      {
         printf("\n Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRecvMsgSize);
	

   if ( (((SysHdr*) gCfgMsgBuf)->msgType)==EXT_TSM_MSG)
      {
        switch(*(I_U8*)(gCfgMsgBuf + sizeof(SysHdr) + sizeof(tHdr)))
        {
         case MGS_SMM_INIT_TRIGGER :
            {
                cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
                cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);
            }
            break;
         case MGS_TRAU_INIT_REQ:
            {
               cfgStubSendDTrauMgsuTrauInitResp(MGS_SMM_SUCCESS);

            }
            break;
         default:
            printf(" No Message handling for the message Type");
            break;
       }
   }
   /****************************************************************************************/
                            /*     TSM STUB            */
   else  if(*(msgRcvP + 22) == MGS_TSM_SWITCH_MAKE_REQ )
     {
      sndMsgSz = 28;
      msgBuffer = (I_U8*)AlocMsgBuf(sndMsgSz);
      memset((I_PVoid)msgBuffer, ZERO, sndMsgSz);
      FILL_SYS_HDR(msgBuffer, MGS_TSM_GRHM_DATA_IND, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_CSAPP_GRHM, 0);
      *(msgBuffer + 20) = *(msgRcvP + 20);
      *(msgBuffer + 21) = *(msgRcvP + 21);
      *(msgBuffer + 22) = MGS_TSM_SWITCH_MAKE_RESP;
      *(msgBuffer + 23) = 1;
      *(msgBuffer + 24) = *(msgRcvP + 24);
      *(msgBuffer + 25) = *(msgRcvP + 25);
      *(msgBuffer + 26) = *(msgRcvP + 26);
      *(msgBuffer + 27) = *(msgRcvP + 27);
      msgName = "SWITCH MAKE RESP";
      SendMsg((I_PVoid)msgBuffer,1, sndMsgSz);
     }
   /****************************************************************************************/
   
    else
       {
        printf("this is not a valid message type");
       }


   }

  }
}
