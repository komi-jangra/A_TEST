#include <oamcfg_includes.h>


#define CFG_INIT_MGS_START    0xfffE

extern gTestCaseCompleted ; 

void initTrauTestCaseDatabase()
{
   RadioClockTableApi RadioClockTableApiBuff={0};

   insertRadioClockTable( &RadioClockTableApiBuff );


}
void CfgTrauHndlr1()
{
   static int testInitiation =1;

   /* TRAU_INIT_RESP */
   /* For this test case we need to run stub first */
   initTrauTestCaseDatabase();

   if ( testInitiation )
   {
      OamAfhAlarmInd OamAfhAlarmIndBuf;
      OamAfhAlarmIndBuf.sysAlarm.sysalarmId = CLOCK_STABILIZED;
      cfgStubSendMessage(&OamAfhAlarmIndBuf,sizeof(OamAfhAlarmInd),ENT_OAM_OIL, ENT_OAMS_CFG, OAM_OIL_CFG_ALARM_IND,0);

      testInitiation =0;


   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               printf("\n Received OAMS_CFG_AFH_ALARM_IND::\n");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == CLOCK_STABILIZED)
               {
                  RadioClockTableApi* RadioClockTableApiPtr=NULL;
                  I_U32 outRows=0;
                  I_U16 outSize=0;

                  printf(" Got CLOCK_STABILIZED Alarm \n");
                  gTestCaseCompleted = 1; 
                  sleep(1);
                  if (getallRadioClockTable(&RadioClockTableApiPtr, &outRows, &outSize) == CLIB_SUCCESS )
                  {
                     if ( RadioClockTableApiPtr->oprStatus == 1)
                        printf("  CFG_TRAU_INIT_1 PASSED \n");
                     else
                        printf("  CFG_TRAU_INIT_1 FAILED OprStatus is not updated\n");
                  }
                  else
                     printf("  CFG_TRAU_INIT_1 FAILED : DB operation Failed\n");
               } 
            }
            break;
         default:
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;

      }
   }

}


void CfgTrauHndlr2()
{
   static int testInitiation =1;

   /* TRAU_INIT_RESP */
   /* For this test case we need to run stub first */

   initTrauTestCaseDatabase();
   if ( testInitiation )
   {
      OamAfhAlarmInd OamAfhAlarmIndBuf;
      OamAfhAlarmIndBuf.sysAlarm.sysalarmId = CLOCK_DISAPPEAR;
      cfgStubSendMessage(&OamAfhAlarmIndBuf,sizeof(OamAfhAlarmInd),ENT_OAM_OIL, ENT_OAMS_CFG, OAM_OIL_CFG_ALARM_IND,0);

      testInitiation =0;


   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               printf("\n Received OAMS_CFG_AFH_ALARM_IND::\n");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == CLOCK_DISAPPEAR)
               {
                  RadioClockTableApi* RadioClockTableApiPtr=NULL;
                  I_U32 outRows=0;
                  I_U16 outSize=0;

                  printf(" Got CLOCK_DISAPPEAR Alarm \n");
                  gTestCaseCompleted = 1; 
                  sleep(1);
                  if (getallRadioClockTable(&RadioClockTableApiPtr, &outRows, &outSize) == CLIB_SUCCESS )
                  {
                     if ( RadioClockTableApiPtr->oprStatus == 1)
                        printf("  CFG_TRAU_INIT_2 PASSED \n");
                     else
                        printf("  CFG_TRAU_INIT_2 FAILED OprStatus is not updated\n");
                  }
                  else
                     printf("  CFG_TRAU_INIT_2 FAILED : DB operation Failed\n");
               } 
            }
            break;
         default:
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;

      }
   }

}



void CfgTrauHndlr3()
{
   static int testInitiation =1;

   /* TRAU_INIT_RESP */
   /* For this test case we need to run stub first */

   if ( testInitiation )
   {
      testInitiation =0;
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case MGS_SMM_INIT_TRIGGER :
            {
               printf(" Recived MGS_SMM_INIT_TRIGGER:\n");
               cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);

            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               printf(" Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               printf(" Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
         case MGS_TRAU_INIT_REQ:
            {
               cfgStubSendDTrauMgsuTrauInitResp();
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               gTestCaseCompleted = 1; 
               printf(" Testcase CfgTrauHndlr3 Passed \n");
            }
            break;
         default:
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;

      }

   }
}

void CfgTrauHndlr4()
{
   static int testInitiation =1;


   if ( testInitiation )
   {
      testInitiation =0;
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case MGS_SMM_INIT_TRIGGER :
            {
               printf(" Recived MGS_SMM_INIT_TRIGGER:\n");
               cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_FAILURE);
               cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);

            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               printf(" Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               printf(" Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
         case MGS_TRAU_INIT_REQ:
            {
               cfgStubSendDTrauMgsuTrauInitResp();
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               printf("\n Received OAMS_CFG_AFH_ALARM_IND::\n");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_INITIALIZATION_FAILED)
               {
                  printf("  Received Alarm  TSI_INITIALIZATION_FAILED \n");
                  printf("  CFG_TRAU_INIT_4 PASSED \n");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  printf("  CFG_TRAU_INIT_4 FAILED: Alarm Id is not correct \n");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;

      }

   }
}

void CfgTrauHndlr5()
{
   static int testInitiation =1;


   if ( testInitiation )
   {
      testInitiation =0;
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case MGS_SMM_INIT_TRIGGER :
            {
               printf(" Recived MGS_SMM_INIT_TRIGGER:\n");
               cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_FAILURE);

            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               printf(" Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               printf(" Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
         case MGS_TRAU_INIT_REQ:
            {
               cfgStubSendDTrauMgsuTrauInitResp();
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               printf("\n Received OAMS_CFG_AFH_ALARM_IND::\n");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_INITIALIZATION_FAILED)
               {
                  printf("  Received Alarm  TRAU_INITIALIZATION_FAILED \n");
                  printf("  CFG_TRAU_INIT_5 PASSED \n");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  printf("  CFG_TRAU_INIT_5 FAILED: Alarm Id is not correct \n");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;

      }

   }
}

void CfgTrauHndlr6()
{
   static int testInitiation =1;


   if ( testInitiation )
   {
      testInitiation =0;
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case MGS_SMM_INIT_TRIGGER :
            {
               printf(" Recived MGS_SMM_INIT_TRIGGER:\n");
               cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_FAILURE);

            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               printf(" Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               printf(" Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
         case MGS_TRAU_INIT_REQ:
            {
               /* Don't send the response 
                  cfgStubSendDTrauMgsuTrauInitResp(); */
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               printf("\n Received OAMS_CFG_AFH_ALARM_IND::\n");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_INITIALIZATION_FAILED)
               {
                  printf("  Received Alarm  TRAU_INITIALIZATION_FAILED \n");
                  printf("  CFG_TRAU_INIT_6 PASSED \n");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  printf("  CFG_TRAU_INIT_6 FAILED: Alarm Id is not correct \n");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;

      }

   }
}

void CfgTrauHndlr7()
{
   static int testInitiation =1;


   if ( testInitiation )
   {
      testInitiation =0;
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case MGS_SMM_INIT_TRIGGER :
            {
               printf(" Recived MGS_SMM_INIT_TRIGGER:\n");
               cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               /* Don't send response for TRAU driver init 
                  cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_FAILURE); */

            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               printf(" Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               printf(" Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
         case MGS_TRAU_INIT_REQ:
            {
               cfgStubSendDTrauMgsuTrauInitResp(); 
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               printf("\n Received OAMS_CFG_AFH_ALARM_IND::\n"); if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_INITIALIZATION_FAILED)
               {
                  printf("  Received Alarm  TSI_INITIALIZATION_FAILED \n");
                  printf("  CFG_TRAU_INIT_7 PASSED \n");
                  gTestCaseCompleted = 1; 
               }
               else
               {
#if 0
                  printf("  CFG_TRAU_INIT_7 FAILED: Alarm Id is not correct \n");
                  gTestCaseCompleted = 1; 
#endif
               }
            }
            break;
         default:
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;

      }

   }
}
