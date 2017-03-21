#include<oamcfg_includes.h>
#define CFG_RESET 0xffff

extern int gTestCaseCompleted; 
I_Bool setDbForPtrx(I_U32 State, I_U32 ptrxId) 
{ 
   /* First set the required database */ 
   I_S32 errCode = 0; 
   /*Delete the row before Inserting....*/  
   PhysicalTrxPreconfiguredTableIndices  ptrxTableIndices; 
   ptrxTableIndices.ptrxId = ptrxId; 
   I_Bool   retVal; 
   errCode=deletePhysicalTrxPreconfiguredTable(&ptrxTableIndices); 
   /* Set the config parameters into database */ 
   PhysicalTrxPreconfiguredTableApi *inData; 
   inData = (PhysicalTrxPreconfiguredTableApi *) malloc(sizeof(PhysicalTrxPreconfiguredTableApi)); /* memory allocation */ 
   inData->ptrxId = ptrxId; 
   inData->adminState = State;    
   inData->tei = 2;       
   inData->antennaId = 1;//enabled 
   inData->e1Id = TRUE; 
   inData->startE1Timeslot = 10; 
   inData->rackId = 11; 
   inData->slotId = 1;//enum :GSM850/GSM900 
   /*inData->pwrCapability = 1;*///enum 
   errCode= insertPhysicalTrxPreconfiguredTable(inData);  /*DB Wrapper .................*/ 
   if(errCode==CLIB_SUCCESS) 
   { 
      printf("\nSuccess Errcode :%d",(I_S32)errCode);      
      printf("\nInsertion is Success\n");    
      retVal = TRUE; 
   } 
   else 
   { 
      printf("\nInsertion Failed"); 
      retVal = FALSE; 
   } 
   free(inData); 
   return retVal; 

} 


void CfgTrxObjHndlr1() 
{ 
   /*Trigger PTRX Object Unlock when PTRX is in Locked state (case1: PTRX Id is in DB)*/ 
   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0};
   OamsCfgTrxhUnlockReq *TrxhUnlockReq;
   SysAlarm sysAlarmBuff; 
   I_S32 errCode = 0; 

   if ( testInitiation ) 
   { 
      printf("\nCfgTrxObjHndlr1 Started :");
      testInitiation =0; 
      /* First set the required database        
         setDbForPtrx(I_U32 State, I_U32 ptrxId)*/ 
      if(setDbForPtrx(0,1) == FALSE) 
      { 
         printf(" \n CfgTrxObjHndlr1 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return; 
      }
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      printf("\n Sending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n");       
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId =(I_U32) 1; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = (I_U32)1; /* unlocked */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE); 

   } 
   else 
   {
      static I_U8 alarmCount=0; 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
               { 
                  printf("\nReceived ACK :CM_SUCCESS\n"); 
               } 
               else 
               { 

                  printf("\nNot expected"); 
                  printf("Received NACk :CM_FAILURE\n"); 
               } 

            }
            break; 

         case OAMS_CFG_TRXH_UNLOCK_REQ: 
            { 
               printf("\nReceived UNLOCK REQUEST");

               TrxhUnlockReq = (OamsCfgTrxhUnlockReq *)gCfgMsgBuf;   
               printf(" \n OamsCfgTrxhUnlockReq recevied with objType = %d",TrxhUnlockReq->objType); 
               printf("\nSending UNLOCK Response"); 
               cfgStubSendTrxhCfgUnlockResp(TrxhUnlockReq->objType,TrxhUnlockReq->objId);
               sysAlarmBuff.sysalarmId = PTRX_ENABLED;
               sysAlarmBuff.key1 = OAMS_OBJTYPE_PTRX;
               sysAlarmBuff.key2= TrxhUnlockReq->objId;
               printf("\nSending Alarm"); 
               cfgStubSendTrxhCfgAlarmInd(sysAlarmBuff); 
            } 
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            alarmCount++;
            if (alarmCount > 1 )
            {
               gTestCaseCompleted = 1;
               printf("\nCfgTrxObjHndlr 1 : Success\n");
            }
            printf("\n Received OAMS_CFG_AFH_ALARM_IND \n");

            break; 
         default: 
            printf("\n Not Expected Message = %d\n ",((SysHdr*) gCfgMsgBuf)->msgType); 
            printf("\nCfgTrxObjHndlr1 : Failed\n "); 
      } 
   } 
} 


void CfgTrxObjHndlr2() 
{ 
   /*Trigger PTRX Object Unlock when PTRX is in Locked state (case1: PTRX Id is Not in DB)*/ 
   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff= {0}; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      /* First set the required database */
      printf("\nCfgTrxObjHndlr2 Started :");       
      if(setDbForPtrx(0,1) == FALSE) 
      { 
         printf(" \n CfgTrxObjHndlr2 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return; 
      }          
      printf("\n Sending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n"); 
      /* send Ptrx unlock */
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId = 25; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = 1; /* unlocked */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);  

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
               { 
                  printf("\nNot Expected"); 
                  printf("\nReceived ACK :CM_SUCCESS");
                  printf("\nCfgTrxObjHndlr 2 : Failed\n"); 
               } 
               else 
               { 
                  gTestCaseCompleted = 1;
                  printf("\nReceived NACk :CM_FAILURE");
                  printf("\nCfgTrxObjHndlr 2 : Success\n"); 
               } 

            } 
            break; 
         default:                
            printf("\n Not Expected Message\n"); 
            printf("\nCfgTrxObjHndlr2 : Failed\n "); 

      } 


   }    

} 
void CfgTrxObjHndlr3() 
{ 
   /*In DB PTRX's adminState is Locked, trigger BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as Locked */ 
   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0}; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      /* First set the required database */
      printf("\nCfgTrxObjHndlr3 Started :");       
      if(setDbForPtrx(0,1) == FALSE) 
      { 
         printf(" \n CfgTrxObjHndlr3 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return; 
      }
      cfgStubSendCmMessage(NULL,0,CFG_RESET);          
      printf("\n Sending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n"); 
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId = 1; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = 0;/*locked*/ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 2;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE); 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               gTestCaseCompleted = 1; 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
               { 
                  printf("\nCfgTrxObjHndlr 3 : Success\n");
               } 
               else 
               { 
                  printf("\nCfgTrxObjHndlr3 :Failed"); 
                  printf("\nReceived NACK :CM_FAIURE"); 
               } 

            } 
            break; 
         default:                
            printf("\n Not Expected Message\n"); 
            printf("\nCfgTrxObjHndlr3  : Failed\n "); 

      } 

   } 


} 
void CfgTrxObjHndlr4() 
{ 
   /* In DB PTRX's adminState is Unlocked, trigger BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as Unlocked*/ 
   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0}; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      /* First set the required database */
      printf("\nCfgTrxObjHndlr4 Started :");       
      if(setDbForPtrx(1,2) == FALSE) 
      { 
         printf(" \n CfgTrxObjHndlr4 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return; 
      }
      cfgStubSendCmMessage(NULL,0,CFG_RESET);          
      printf(" \nSendig BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n"); 
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId = 2; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = 1;/*unlocked*/ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE); 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
               { 
                  printf("\nCfgTrxObjHndlr4 :Failed"); 
               } 
               else 
               { 
                  gTestCaseCompleted = 1; 
                  printf("\nReceived NACK :CM_FAILURE"); 
                  printf("\nCfgTrxObjHndlr 4 : Success\n");
               } 

            } 
            break; 
         default:                
            printf("\n Not Expected Message\n"); 
            printf("\nCfgTrxObjHndlr4 : Failed\n "); 

      } 

   } 
} 
void CfgTrxObjHndlr5() 
{ 
   /*In DB PTRX's adminState is Unlocked, trigger BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as Locked */ 

   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0};
   OamsCfgTrxhLockReq* TrxhLockReq;
   SysAlarm sysAlarmBuff; 

   if ( testInitiation ) 
   { 
      printf("\nCfgTrxObjHndlr5 Started :");
      testInitiation =0; 
      /* First set the required database */       
      if(setDbForPtrx(1,1) == FALSE) 
      { 
         printf(" \n CfgTrxObjHndlr5 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return; 
      }
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      printf(" \nSendig BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE Req to CFG \n");       
      /* send Ptrx lock */ 
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId = 1; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = 0; /* locked */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE); 

   } 
   else 
   {   static I_U8 alarmCount=0; 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
               { 
                  printf("\n Received ACK :CM_SUCCESS"); 
               } 
               else 
               { 
                  printf("\nNot expected :"); 
                  printf("Received NACK :CM_FAILURE"); 
               } 

            } 
            break; 
         case OAMS_CFG_TRXH_LOCK_REQ: 
            { 
               printf("\nReceived LOCK REQUEST");          

               TrxhLockReq = (OamsCfgTrxhLockReq *)gCfgMsgBuf;    
               printf("\nSending LOCK Response"); 
               cfgStubSendTrxhCfgLockResp(TrxhLockReq->objType,TrxhLockReq->objId);
               sysAlarmBuff.sysalarmId = PTRX_DISABLED;
               sysAlarmBuff.key1 = OAMS_OBJTYPE_PTRX;
               sysAlarmBuff.key2= TrxhLockReq->objId; 
               printf("\nSending Alarm"); 
               cfgStubSendTrxhCfgAlarmInd(sysAlarmBuff); 

            } 
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            alarmCount++;
            if (alarmCount > 1 )
            {
               gTestCaseCompleted = 1;
               printf("\nCfgTrxObjHndlr 5 : Success\n");
            }
            printf("\n Received OAMS_CFG_AFH_ALARM_IND \n");

            break; 
         default: 
            printf("\n Not Expected Message\n"); 
            printf("\nCfgTrxObjHndlr5: Failed\n "); 

      } 

   } 
} 



void CfgTrxObjHndlr6() 
{ 
   /*  In DB PTRX's adminState is Locked, trigger BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as Unlocked, Before sending Unlock Response from TRXHandler send BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as Unlocked*/ 
   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0};
   OamsCfgTrxhUnlockReq *TrxhUnlockReq;
   SysAlarm sysAlarmBuff; 
   I_S32 errCode = 0; 

   if ( testInitiation ) 
   { 
      printf("\nCfgTrxObjHndlr6 Started :");
      testInitiation =0;       
      /* First set the required database        
         setDbForPtrx(I_U32 State, I_U32 ptrxId)*/ 
      if(setDbForPtrx(0,6) == FALSE) 
      { 
         printf("\n  CfgTrxObjHndlr6 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return; 
      }
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      printf(" \nSending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n");       
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId =(I_U32) 6; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = (I_U32)1; /* unlocked */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE); 

   } 
   else 
   {
      static I_U8 appCount=0; 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
               { 
                  appCount++;
                  printf("\nReceived ACK :CM_SUCCESS\n");
               }

               else 
               { 
                  if(appCount == 0)
                  { 
                     printf("\nNot expected"); 
                     printf("Received NACk :CM_FAILURE\n");
                  }
                  else
                  {
                     printf("\nReceived NACk :CM_FAILURE\n");
                     gTestCaseCompleted = 1;
                     printf("\nCfgTrxObjHndlr 6 : Success\n");   
                  } 
               } 

            }
            break; 

         case OAMS_CFG_TRXH_UNLOCK_REQ: 
            { 
               printf("\nReceived UNLOCK REQUEST");

               TrxhUnlockReq = (OamsCfgTrxhUnlockReq *)gCfgMsgBuf;   
               printf(" \n OamsCfgTrxhUnlockReq recevied with objType = %d",TrxhUnlockReq->objType); 

               printf("\nSending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE request before response");
               PhysicalTrxPreconfiguredTableApiBuff.ptrxId =(I_U32) 6; 
               PhysicalTrxPreconfiguredTableApiBuff.adminState = 1; /* unlocked*/ 
               cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);

            } 
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {               
               printf("\n Received OAMS_CFG_AFH_ALARM_IND \n");
            }
            break; 
         default: 
            printf("\n Not Expected Message = %d\n ",((SysHdr*) gCfgMsgBuf)->msgType); 
            printf("\nCfgTrxObjHndlr6 : Failed\n "); 
      } 




   } 
}



void CfgTrxObjHndlr7() 
{ 
   /*  In DB PTRX's adminState is Locked, trigger BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as Unlocked, Before sending Unlock Response from TRXHandler send BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as locked*/ 
   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0};
   OamsCfgTrxhUnlockReq *TrxhUnlockReq;
   SysAlarm sysAlarmBuff; 
   I_S32 errCode = 0; 

   if ( testInitiation ) 
   { 
      printf("\nCfgTrxObjHndlr7 Started :");
      testInitiation =0;

      /* First set the required database        
         setDbForPtrx(I_U32 State, I_U32 ptrxId)*/ 
      if(setDbForPtrx(0,7) == FALSE) 
      { 
         printf("\n  CfgTrxObjHndlr7 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return; 
      }
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      printf("\n Sending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n");       
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId =(I_U32) 7; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = (I_U32)1; /* unlocked */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      /*inData->pwrCapability = 1;*///enum

      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE); 

   } 
   else 
   {
      static I_U8 appCount=0; 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
               { 
                  appCount++;
                  printf("\nReceived ACK :CM_SUCCESS\n");
               }

               else 
               { 
                  if(appCount == 0)
                  { 
                     printf("\nNot expected"); 
                     printf("\nReceived NACk :CM_FAILURE\n");
                  }
                  else
                  {
                     printf("\nReceived NACk :CM_FAILURE\n");
                     gTestCaseCompleted = 1;
                     printf("\nCfgTrxObjHndlr 7 : Success\n");   
                  } 
               } 

            }
            break; 

         case OAMS_CFG_TRXH_UNLOCK_REQ: 
            { 
               printf("\nReceived UNLOCK REQUEST");

               TrxhUnlockReq = (OamsCfgTrxhUnlockReq *)gCfgMsgBuf;   
               printf(" \n OamsCfgTrxhUnlockReq recevied with objType = %d",TrxhUnlockReq->objType); 

               printf("\nSending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE request before response");
               PhysicalTrxPreconfiguredTableApiBuff.ptrxId =(I_U32) 7; 
               PhysicalTrxPreconfiguredTableApiBuff.adminState = 0; /* locked*/ 
               cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);

            } 
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {               
               printf("\n Received OAMS_CFG_AFH_ALARM_IND \n");
            }
            break; 
         default: 
            printf("\n Not Expected Message = %d\n ",((SysHdr*) gCfgMsgBuf)->msgType); 
            printf("\nCfgTrxObjHndlr7 : Failed\n "); 
      } 




   } 
}




void CfgTrxObjHndlr8() 
{ 
   /*  In DB PTRX's adminState is UnLocked, trigger BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as locked, Before sending Unlock Response from TRXHandler send BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as Unlocked*/ 
   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0};
   OamsCfgTrxhLockReq* TrxhLockReq;
   SysAlarm sysAlarmBuff; 
   I_S32 errCode = 0; 

   if ( testInitiation ) 
   { 
      printf("\nCfgTrxObjHndlr8 Started :");
      testInitiation =0; 
      /* First set the required database        
         setDbForPtrx(I_U32 State, I_U32 ptrxId)*/ 
      if(setDbForPtrx(1,8) == FALSE) 
      { 
         printf("  \nCfgTrxObjHndlr8 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return; 
      }
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      printf(" \nSending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n");       
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId =(I_U32) 8; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = (I_U32)0; /* locked */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE); 

   } 
   else 
   {
      static I_U8 appCount=0; 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
               { 
                  appCount++;
                  printf("\nReceived ACK :CM_SUCCESS\n");
               }

               else 
               { 
                  if(appCount == 0)
                  { 
                     printf("\nNot expected"); 
                     printf("Received NACk :CM_FAILURE\n");
                  }
                  else
                  {
                     printf("Received NACk :CM_FAILURE\n");
                     gTestCaseCompleted = 1;
                     printf("CfgTrxObjHndlr 8 : Success\n");   
                  } 
               } 

            }
            break; 

         case OAMS_CFG_TRXH_LOCK_REQ: 
            { 
               printf("\nReceived UNLOCK REQUEST");

               TrxhLockReq = (OamsCfgTrxhLockReq *)gCfgMsgBuf;   
               printf(" \n OamsCfgTrxhUnlockReq recevied with objType = %d",TrxhLockReq->objType); 

               printf("\nSending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE request before response");
               PhysicalTrxPreconfiguredTableApiBuff.ptrxId =(I_U32) 8; 
               PhysicalTrxPreconfiguredTableApiBuff.adminState = 1; /* unlocked*/ 
               cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);

            } 
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {               
               printf("\n Received OAMS_CFG_AFH_ALARM_IND \n");
            }
            break; 
         default: 
            printf("\n Not Expected Message = %d\n ",((SysHdr*) gCfgMsgBuf)->msgType); 
            printf("\nCfgTrxObjHndlr8 : Failed\n "); 
      } 




   } 
}



void CfgTrxObjHndlr9() 
{ 
   /*  In DB PTRX's adminState is UnLocked, trigger BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as locked, Before sending Unlock Response from TRXHandler send BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as locked*/ 
   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0};
   OamsCfgTrxhLockReq* TrxhLockReq;
   SysAlarm sysAlarmBuff; 
   I_S32 errCode = 0; 

   if ( testInitiation ) 
   { 
      printf("CfgTrxObjHndlr9 Started :");
      testInitiation =0; 
      /* First set the required database        
         setDbForPtrx(I_U32 State, I_U32 ptrxId)*/ 
      if(setDbForPtrx(1,9) == FALSE) 
      { 
         printf(" \n CfgTrxObjHndlr9 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return; 
      }
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      printf("\n Sending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n");       
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId =(I_U32) 9; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = (I_U32)0; /* locked */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE); 

   } 
   else 
   {
      static I_U8 appCount=0; 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
               { 
                  appCount++;
                  printf("\nReceived ACK :CM_SUCCESS\n");
               }

               else 
               { 
                  if(appCount == 0)
                  { 
                     printf("\nNot expected"); 
                     printf("Received NACk :CM_FAILURE\n");
                  }
                  else
                  {
                     printf("Received NACk :CM_FAILURE\n");
                     gTestCaseCompleted = 1;
                     printf("CfgTrxObjHndlr 9 : Success\n");   
                  } 
               } 

            }
            break; 

         case OAMS_CFG_TRXH_LOCK_REQ: 
            { 
               printf("\nReceived UNLOCK REQUEST");

               TrxhLockReq = (OamsCfgTrxhLockReq *)gCfgMsgBuf;   
               printf(" \n OamsCfgTrxhUnlockReq recevied with objType = %d",TrxhLockReq->objType); 

               printf("\nSending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE request before response");
               PhysicalTrxPreconfiguredTableApiBuff.ptrxId =(I_U32) 9; 
               PhysicalTrxPreconfiguredTableApiBuff.adminState = 0; /* locked*/ 
               cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);

            } 
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {               
               printf("\n Received OAMS_CFG_AFH_ALARM_IND \n");
            }
            break; 
         default: 
            printf("\n Not Expected Message = %d\n ",((SysHdr*) gCfgMsgBuf)->msgType); 
            printf("\nCfgTrxObjHndlr9 : Failed\n "); 
      } 




   } 
}




void CfgTrxObjHndlr10() 
{ 
   /* In DB PTRX's adminState is locked,Trigger  BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE with adminState as unknown value   */ 
   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0};
   int i;
   I_S32 errCode = 0; 
   if ( testInitiation ) 
   { 
      printf("\nCfgTrxObjHndlr10 Started :");
      testInitiation =0; 
      /* First set the required database        
         setDbForPtrx(I_U32 State, I_U32 ptrxId)*/
      if(setDbForPtrx(0,16) == FALSE) 
      { 
         printf("  \nCfgTrxObjHndlr10 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return;
      } 
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      printf(" \nSending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n");
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId = 16; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = (I_U32)6; /* unknown */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);



   } 
   else 
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
               { 
                  printf("CfgTrxObjHndlr10 :Failed"); 
               } 
               else 
               { 
                  gTestCaseCompleted = 1; 
                  printf("\nReceived NACK :CM_FAIURE"); 
                  printf("\nCfgTrxObjHndlr 10 : Success\n");
               } 

            } 
            break;

         default:                
            printf("\n Not Expected Message\n"); 
            printf("\nCfgTrxObjHndlr10 : Failed\n "); 

      } 

   }
} 





void CfgTrxObjHndlr11() 
{ 
   /*Trigger multiple BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE Requests from different PTRXId for locking and unlocking*/ 
   static int testInitiation =1; 
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0}; 
   OamsCfgTrxhUnlockReq *TrxhUnlockReq; 
   OamsCfgTrxhLockReq* TrxhLockReq; 
   SysAlarm sysAlarmBuff;
   int i;
   I_S32 errCode = 0; 
   if ( testInitiation ) 
   { 
      printf("\nCfgTrxObjHndlr11 Started :");
      testInitiation =0; 

      if(setDbForPtrx(1,11) == FALSE) 
      { 
         printf("  \nCfgTrxObjHndlr11 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return;
      } 
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      printf(" \nSending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n");


      PhysicalTrxPreconfiguredTableApiBuff.ptrxId = 11; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = (I_U32)0; /* locked */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);

      if(setDbForPtrx(1,12) == FALSE) 
      { 
         printf("  \nCfgTrxObjHndlr11 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return;
      } 
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      printf(" \nSending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n");

      PhysicalTrxPreconfiguredTableApiBuff.ptrxId = 12; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = (I_U32)0; /* locked */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);

      if(setDbForPtrx(1,13) == FALSE) 
      { 
         printf("  \nCfgTrxObjHndlr11 insertion Failed \n");
         gTestCaseCompleted = 1;      
         return;
      } 
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      printf(" \nSending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE to CFG \n");
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId = 13; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = (I_U32)1; /* unlocked */ 
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 10;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 11;
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);       


   } 
   else 
   {
      static I_U8 alarmCount=0;
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS ) 
                  printf("Received ACK:CM_SUCCESS"); 

               else 
                  printf("\nReceived NACK :CM_FAIURE");

            } 
            break;
         case OAMS_CFG_TRXH_UNLOCK_REQ: 
            { 
               printf("\nReceived UNLOCK REQUEST");

               TrxhUnlockReq = (OamsCfgTrxhUnlockReq *)gCfgMsgBuf;   
               printf(" \n OamsCfgTrxhUnlockReq recevied with objType = %d",TrxhUnlockReq->objType); 
               printf("\nSending UNLOCK Response"); 
               cfgStubSendTrxhCfgUnlockResp(TrxhUnlockReq->objType,TrxhUnlockReq->objId);
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
               cfgStubSendTrxhCfgLockResp(TrxhLockReq->objType,TrxhLockReq->objId);
               sysAlarmBuff.sysalarmId = PTRX_DISABLED;
               sysAlarmBuff.key1 = OAMS_OBJTYPE_PTRX;
               sysAlarmBuff.key2= TrxhLockReq->objId; 
               printf("\nSending Alarm"); 
               cfgStubSendTrxhCfgAlarmInd(sysAlarmBuff); 

            }
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmCount++;
            if (alarmCount == 4 )
            {
               gTestCaseCompleted = 1;
               printf("\nCfgTrxObjHndlr 11 : Success\n");
            }
            printf("\n Received OAMS_CFG_AFH_SYS_ALARM \n");

            break;
         default:                
            printf("\n Not Expected Message\n"); 
            printf("\nCfgTrxObjHndlr11  : Failed\n "); 

      } 


   } 
}





