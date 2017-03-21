/********************************************************************************/
#include<oamcfg_includes.h>
#define SET_BIT( var, bit ) var |= (1<<bit)
#define lBYtes 0
#define hBytes 16
#define CFG_RESET  0xffff
extern int  gTestCaseCompleted;
void setDbMuxForTimeSlot(I_U32 State, I_U32 type1, I_U32 type2, I_U32 type3, I_U32 eNum);
void setDbCombForTimeSlot(I_U32 State, I_U32 type1, I_U32 type2,  I_U32 e1Num);
void setDbForAbisTimeslot(I_U32 State, I_U32 usageType, I_U32 e1num, I_U32 count);
void setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num);
void setDbForE1TimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum);
void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num);
void setFrLinkTable();
I_U32 maskBits(I_U32 var,int value,int bitCount)
{/*---------------------------------*/
   /*var - ObjectId.*/
   /*value - E1 Number /TimeSlot Number*/
   /*---------------------------------*/
   while(value>0)
   {
      if( value%2!=0) SET_BIT(var,bitCount);
      value=value/2;
      bitCount++;
   }
   return var;
}

/********************************************************************************
  Test Case #1;
 *********************************************************************************/
void CfgE1ObjectHandler1()
{
   static int testInitiation =1;

   E1TableApi E1TableApiBuff = {0};

   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler1  : E1 Lock Request\n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      setDbForE1(1,0,1);

      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {

                  printf("CM_SUCCESS");
               }
               else
               {
                  printf("CM_FAILURE");
                  gTestCaseCompleted = 1;
                  printf("CfgE1ObjHndlr 1 : Success\n");
               }

            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\nCfgE1ObjHndlr 1 : Failed\n ");

      }   
   }
}
/********************************************************************************/


/********************************************************************************
  Test Case #2;
 ********************************************************************************/
void CfgE1ObjectHandler2()
{
   static int testInitiation =1;
   static alarmcount;         
   E1TableApi E1TableApiBuff = {0};

   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler2  : E1 ULock Request\n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      setDbForE1(0,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/
      /* setDbForTimeSlot(1,0,1); */
      /* setDbForTimeSlot(1,0,1); */
      setDbForTimeSlot(1,SYS_TS_USAGE_MTP2,1); 
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 1; /* unlocked */
      E1TableApiBuff.usageType = SYS_E1_USAGE_AIF; 
      E1TableApiBuff.usingEntity = 1; 
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);

   }
   else
   {
      printf("\n Iam in else part of TestCase#2\n");   
      printf("\n CFG STUB : %d",(((SysHdr*) gCfgMsgBuf)->msgType));   
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         printf("\n CFG STUB : %d",(((SysHdr*) gCfgMsgBuf)->msgType));   
         case CM_API_APP_RESPONSE:
         {
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
            {
               printf("\n Expected Message\n");
               printf("\nCfgE1ObjHndlr 1 : Got CM_APP_API_MESSAGE\n ");
            }
            else
            {
               printf("CM_FAILURE");
            }

         }
         break;

         case  OAMS_CFG_SCM_UNLOCK_REQ:
         {
            printf("\n I am here in OAMS_CFG_SCM_UNLOCK_REQ\n"); 
            OamsCfgScmUnlockReq *scmUnlockReq;
            scmUnlockReq = (OamsCfgScmUnlockReq  *)gCfgMsgBuf;
            // Send response from stub to CFG.   
            cfgStubSendCfgScmUnLockResp(scmUnlockReq->ObjType, scmUnlockReq->lengthOfList,scmUnlockReq->objectIdList, scmUnlockReq->e1Num,0,0);
            /*send Alarm..*/
         }
         break;  

         case  OAMS_CFG_AFH_ALARM_IND:
         alarmcount++;
         if( alarmcount ==1 )
         {
            printf("\nAlarm has been received (E1 AST=Unlocked)\n");        
            cfgStubSendScmCfgAlarmInd(AINTERFACE_ENABLED);
         } 
         if( alarmcount ==2 ) 
         {
            gTestCaseCompleted = 1;
            printf("CfgE1ObjectHandler2 : Success\n");
         } 
         break;   


         default:
         printf("\n Not Expected Message\n");
         printf("\n CfgE1ObjectHandler2 : Failed\n ");

      }
   }
}

/******************************************************************************************
  Test case #3
 ******************************************************************************************/
void CfgE1ObjectHandler3()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount; 
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler3  : E1 ULock Request with timeslots for CIC \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      /* setDbForE1(0,0,1); */
      setDbForE1(0,SYS_E1_USAGE_AIF,1); 
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/
      /* setDbForTimeSlot(1,2,1); */
      setDbForTimeSlot(1,SYS_TS_USAGE_CIC,1);
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.usageType=SYS_E1_USAGE_AIF;
      E1TableApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               printf("\n I am in TestCase#3 \n");   
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message CM SUCCESS\n");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *grhmUnlockReq;
               grhmUnlockReq = (OamsCfgGrhmUnlockReq *) gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendGrhmCfgUnlockResp (grhmUnlockReq->objType,grhmUnlockReq->objectId);
               printf("\n Sending OAMS_CFG_GRHM_UNLOCK_RESP \n");     
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {  
               printf("\nAlarm has been received (E1 AST=Unlocked)\n");        
               cfgStubSendScmCfgAlarmInd(CIC_ENABLED);
            } 
            if( alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf("CfgE1ObjectHandler3 : Success\n");
            }
            break;


         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler3 : Failed\n ");
      }
   }
}

/******************************************************************************************
  Test case #4
 ******************************************************************************************/
void CfgE1ObjectHandler4()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;  
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler4  : E1 ULock Request\n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      /*setDbForE1(0,0,1); */
      setDbForE1(0,SYS_E1_USAGE_AIF,1);

      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/
      /* setDbForTimeSlot(1,1,1); */
      setDbForTimeSlot(1,SYS_TS_USAGE_FR,1);

      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);

   }
   else
   {
      printf("\n TestCase Completed: %d",gTestCaseCompleted);     
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\nExpected Message\n");
                  printf("\nCfgE1ObjHndlr 4 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_PSSCM_UNLOCK_REQ:
            {
               OamsCfgPsscmUnlockReq *psscmUlockReq;
               psscmUlockReq = (OamsCfgPsscmUnlockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               printf("\n Sending the OAMS_CFG_PSSCM_UNLOCK_RESP to cfg\n"); 
               cfgStubSendPsscmCfgUnlockResp (psscmUlockReq->ObjType, psscmUlockReq->lengthOfList, 
                     psscmUlockReq->objectIdList, psscmUlockReq->e1Num,0);
            }
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if(alarmcount ==1)
            { 
               printf("\nAlarm has been received (E1 AST=Unlocked)\n");        
               cfgStubSendScmCfgAlarmInd(FRLINK_ENABLED);
            }    
            if(alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf("CfgE1ObjectHandler4 : Success\n");
            }
            break;



            break; 
         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler4 : Failed\n ");

      }
   }
}

/******************************************************************************************
  Test case #5
 ******************************************************************************************/
void CfgE1ObjectHandler5()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;   
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler5: E1 ULock Request\n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      /* setDbForE1(0,0,1); */
      setDbForE1(0,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/

      /* setDbCombForTimeSlot(1,0,1,1);*/
      setDbCombForTimeSlot(1,SYS_TS_USAGE_FR,SYS_TS_USAGE_MTP2,1);
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 1; /* unlocked */
      E1TableApiBuff.usageType = SYS_E1_USAGE_AIF;
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n  Expected Message\n");
                  printf("\nCfgE1ObjHndlr 5 : CM Success\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *scmUnlockReq;
               scmUnlockReq = (OamsCfgScmUnlockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               printf("\n Sending OAMS_CFG_SCM_UNLOCK_RESP to CFG\n");  
               cfgStubSendCfgScmUnLockResp( scmUnlockReq->ObjType, scmUnlockReq->lengthOfList, 
                     scmUnlockReq->objectIdList, scmUnlockReq->e1Num,0,0);
               //send Alarm..
               /*cfgStubSendScmCfgAlarmInd(AINTERFACE_ENABLED);*/
            }
            break;
         case  OAMS_CFG_PSSCM_UNLOCK_REQ:
            {
               OamsCfgPsscmUnlockReq *psscmUlockReq;

               psscmUlockReq = (OamsCfgPsscmUnlockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               printf("\n Sending OAMS_CFG_PSSCM_UNLOCK_RESP to CFG with eNum:\n", psscmUlockReq->e1Num);  
               cfgStubSendPsscmCfgUnlockResp( psscmUlockReq->ObjType, psscmUlockReq->lengthOfList, 
                     psscmUlockReq->objectIdList, psscmUlockReq->e1Num,0,0,0);
               //send Alarm..
               /*cfgStubSendPsscmCfgAlarmInd (AINTERFACE_DISABLED);*/
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount == 1)
            { 
               printf("\nAlarm has been received (E1 AST=Unlocked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_ENABLED);
               cfgStubSendScmCfgAlarmInd(FRLINK_ENABLED);
            } 
            if( alarmcount == 3 )
            {
               gTestCaseCompleted = 1;
               printf(" CfgE1ObjectHandler5 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler5 : Failed\n ");

      }
   }
}


/******************************************************************************************
  Test case #6
 ******************************************************************************************/
void CfgE1ObjectHandler6()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;  
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler6: E1 ULock Request for MTP2 and CIC combined \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      /* setDbForE1(0,0,1); */
      setDbForE1(0,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/

      /* setDbCombForTimeSlot(1,0,2,1); */
      setDbCombForTimeSlot(1,SYS_TS_USAGE_CIC,SYS_TS_USAGE_MTP2,1);
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 1; /* unlocked */
      E1TableApiBuff.usageType = SYS_E1_USAGE_AIF;
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message, CM_API_APP_RESPONSE \n");
                  printf("\nCfgE1ObjHndlr 6 : SUCCESS \n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }
            }
            break;
         case  OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *scmUnlockReq;
               scmUnlockReq = (OamsCfgScmUnlockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendCfgScmUnLockResp( scmUnlockReq->ObjType, scmUnlockReq->lengthOfList, 
                     scmUnlockReq->objectIdList, scmUnlockReq->e1Num,0,0);
               //send Alarm..
               //cfgStubSendScmCfgAlarmInd(AINTERFACE_ENABLED);
            }
            break;
         case  OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq*  grhmUnlockReq;
               grhmUnlockReq= (OamsCfgGrhmUnlockReq *)gCfgMsgBuf ;
               // Send response from stub to CFG.

               cfgStubSendGrhmCfgUnlockResp(grhmUnlockReq->objType,grhmUnlockReq->objectId);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount == 1)
            {
               printf("\nAlarm has been received (E1 AST=Unlocked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_ENABLED);
               cfgStubSendScmCfgAlarmInd(CIC_ENABLED);
            }
            if( alarmcount == 3 )
            {
               gTestCaseCompleted = 1;
               printf("CfgE1ObjHndlr 6 : Success\n");
            }
            break;


         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler6 : Failed\n ");
      }
   }
}

/******************************************************************************************
  Test case #7
 ******************************************************************************************/
void CfgE1ObjectHandler7()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount; 
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 7  : E1 ULock Request for FR and CIC combined \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      /* setDbForE1(0,0,1); */
      setDbForE1(0,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/

      /* setDbCombForTimeSlot(1,0,2,1); */
      setDbCombForTimeSlot(1,SYS_TS_USAGE_FR,SYS_TS_USAGE_CIC,1);

      /* setDbCombForTimeSlot(1,1,2,1); */
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 1; /* unlocked */
      E1TableApiBuff.usageType=SYS_E1_USAGE_AIF;
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\nExpected Message\n");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;

         case  OAMS_CFG_PSSCM_UNLOCK_REQ:
            {
               OamsCfgPsscmUnlockReq *psscmUlockReq;

               psscmUlockReq = (OamsCfgPsscmUnlockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendPsscmCfgUnlockResp( psscmUlockReq->ObjType, psscmUlockReq->lengthOfList, 
                     psscmUlockReq->objectIdList, psscmUlockReq->e1Num,0);
               //send Alarm..
               //cfgStubSendPsscmCfgAlarmInd (NSVC_Enabled);
            }
            break;  
         case  OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq*  grhmUnlockReq;
               grhmUnlockReq = (OamsCfgGrhmUnlockReq *)gCfgMsgBuf ;
               // Send response from stub to CFG. 
               cfgStubSendGrhmCfgUnlockResp (grhmUnlockReq->objType, grhmUnlockReq->objectId);
               //send Alarm.. 
               // cfgStubSendScmCfgAlarmInd(CIC_ENABLED);
            }
            break;  
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount == 1)
            {
               printf("\nAlarm has been received (E1 AST=Unlocked)\n");        
               cfgStubSendScmCfgAlarmInd(FRLINK_ENABLED);
               cfgStubSendScmCfgAlarmInd(CIC_ENABLED);
            }
            if( alarmcount == 3 )
            {
               gTestCaseCompleted = 1;
               printf(" CfgE1ObjectHandler7 : Success\n");
            }
            break;


         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler7 : Failed\n ");
      }
   }
}

/******************************************************************************************
  Test case #8
 ******************************************************************************************/
void CfgE1ObjectHandler8()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;    
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 8  : E1 ULock Request for FR, CIC & MTP2 combined \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      /* setDbForE1(0,0,1); */
      setDbForE1(0,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/

      /* setDbMuxForTimeSlot(1,1,2,0,1);*/
      setDbMuxForTimeSlot(1,SYS_TS_USAGE_FR,SYS_TS_USAGE_CIC,SYS_TS_USAGE_MTP2,1);
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);

   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message, CM_API_APP_RESPONSE \n");
                  printf("\n CfgE1ObjHndlr 8 : SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *scmUnlockReq;
               scmUnlockReq = (OamsCfgScmUnlockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendCfgScmUnLockResp( scmUnlockReq->ObjType, scmUnlockReq->lengthOfList, 
                     scmUnlockReq->objectIdList, scmUnlockReq->e1Num,0,0);
               //send Alarm..
               cfgStubSendScmCfgAlarmInd(AINTERFACE_ENABLED);
            }
            break;
         case  OAMS_CFG_PSSCM_UNLOCK_REQ:
            {
               OamsCfgPsscmUnlockReq *psscmUnlockReq;

               psscmUnlockReq = (OamsCfgPsscmUnlockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendPsscmCfgUnlockResp( psscmUnlockReq->ObjType, psscmUnlockReq->lengthOfList, 
                     psscmUnlockReq->objectIdList, psscmUnlockReq->e1Num,0);

               //send Alarm..
               //cfgStubSendPsscmCfgAlarmInd(NSVC_Enabled);
            }
            break;
         case  OAMS_CFG_GRHM_UNLOCK_REQ:
            {

               OamsCfgGrhmUnlockReq*  grhmUnlockReq;
               grhmUnlockReq = (OamsCfgGrhmUnlockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.

               cfgStubSendGrhmCfgUnlockResp (grhmUnlockReq->objType,grhmUnlockReq->objectId);
               //send Alarm..
               //cfgStubSendGrhmCfgAlarmInd (CIC_ENABLED);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount == 1)
            {
               printf("\nAlarm has been received (E1 AST=Unlocked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_ENABLED);
               cfgStubSendScmCfgAlarmInd(FRLINK_ENABLED);
               cfgStubSendScmCfgAlarmInd(CIC_ENABLED);
            }
            if( alarmcount == 4 )
            {
               gTestCaseCompleted = 1;
               printf(" CfgE1ObjectHandler8 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler8 : Failed\n ");
      }
   }
}


/******************************************************************************************
  Test case #9
 ******************************************************************************************/
void CfgE1ObjectHandler9()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;  
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 9 : E1 ULock Request for LAPD link on Abis link \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      /*    setDbForE1(0,1,1);*/
      setDbForE1(0,SYS_E1_USAGE_ABIS,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/

      /* Configure in DB 'n' no. of timeslots for Abis - LAPD link */
      /* setDbForAbisTimeslot(1,3,1,1);   */
      setDbForAbisTimeslot(1,SYS_TS_USAGE_LAPD_OML,1,1);   
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   } 
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message, CM_API_APP_RESPONSE \n");
                  printf("\n CfgE1ObjectHandler9 : Success\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_TRXH_UNLOCK_REQ:
            {

               OamsCfgTrxhUnlockReq*  trxhUnlockReq;
               trxhUnlockReq = (OamsCfgTrxhUnlockReq  *)gCfgMsgBuf;

               // Send response from stub to CFG.
               cfgStubSendTrxhCfgUnlockResp(trxhUnlockReq->objType,trxhUnlockReq->objId,trxhUnlockReq->e1Num);
               printf("\n OAMS_CFG_TRXH_UNLOCK_RESP has been sent\n"); 
               //send Alarm..
               //cfgStubSendPcuCfgAlarmInd ();

            }

            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (E1 AST=Unlocked)\n");        
               gTestCaseCompleted = 1;
               printf(" CfgE1ObjectHandler9 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler9 : Failed\n ");
      }
   }
}


/******************************************************************************************
  Test case #10
 ******************************************************************************************/
void CfgE1ObjectHandler10()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount; 
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 10 : E1 ULock Request for LAPD link on Abis link \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      /* setDbForE1(0,1,1); */
      setDbForE1(0,SYS_E1_USAGE_ABIS,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/

      /* Configure in DB 'n' no. of timeslots for Abis - LAPD link */
      /* setDbForAbisTimeslot(0,3,1,2);   */
      setDbForAbisTimeslot(0,SYS_TS_USAGE_LAPD_OML,1,1);   
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   } 
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message\n");
                  printf("\n CfgE1ObjectHandler10  : SUCCESS \n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_TRXH_UNLOCK_REQ:
            {
               printf("\n Received OAMS_CFG_TRXH_UNLOCK_REQ \n");

               OamsCfgTrxhUnlockReq*  trxhUnlockReq;
               trxhUnlockReq = (OamsCfgTrxhUnlockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendTrxhCfgUnlockResp(trxhUnlockReq->objType,trxhUnlockReq->objId,trxhUnlockReq->e1Num);
               //send Alarm..
               //   cfgStubSendPcuCfgAlarmInd(0);

            }
            break; 
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (E1 AST=Unlocked)\n");        
               gTestCaseCompleted = 1;
               printf(" CfgE1ObjectHandler10 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler10 : Failed\n ");
      }
   }
}


/******************************************************************************************
  Test case #11
 ******************************************************************************************/
void CfgE1ObjectHandler11()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount; 
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 10 : E1 ULock Request for LAPD link on Abis link \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      /* setDbForE1(0,1,1); */
      setDbForE1(0,SYS_E1_USAGE_ABIS,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/

      /* Configure in DB 'n' no. of timeslots for Abis - LAPD link */
      /* setDbForAbisTimeslot(0,3,1,3); */
      setDbForAbisTimeslot(0,SYS_TS_USAGE_LAPD_OML,1,3);   
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   } 
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message\n");
                  printf("\nCfgE1ObjHndlr 1 : CM_SUCCESS");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_TRXH_UNLOCK_REQ:
            {
               OamsCfgTrxhUnlockReq*  trxhUnlockReq;
               trxhUnlockReq = (OamsCfgTrxhUnlockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendTrxhCfgUnlockResp(trxhUnlockReq->objType,trxhUnlockReq->objId,trxhUnlockReq->e1Num);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (E1 AST=Unlocked)\n");        
               gTestCaseCompleted = 1;
               printf("CfgE1ObjHndlr 11 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler11 : Failed\n ");
      }
   }
}
/******************************************************************************************
  Test case #12
 ******************************************************************************************/
void CfgE1ObjectHandler12()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;  
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 12 : E1 Lock Procedure for MTP2 link on A interface link \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/

      /* setDbForE1(1,0,1); */
      setDbForE1(1,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/
      /* setDbForTimeSlot(0,0,1); */
      setDbForTimeSlot(0,SYS_TS_USAGE_MTP2,1);

      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 0; /* Locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);

   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message, CM_API_APP_RESPONSE \n");
                  printf("\n CfgE1ObjectHandler12 : SUCCESS \n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_SCM_LOCK_REQ:
            {
               OamsCfgScmLockReq *scmlockReq;
               SysAlarm sysAlarm;
               scmlockReq = (OamsCfgScmLockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendCfgScmLockResp(scmlockReq->ObjType, scmlockReq->lengthOfList,scmlockReq->objectIdList, scmlockReq->e1Num,0,0);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (E1 AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
            }
            if( alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf(" CfgE1ObjectHandler12 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler12 : Failed\n ");
      }
   }
}

/******************************************************************************************
  Test case #13
 ******************************************************************************************/
void CfgE1ObjectHandler13()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;   
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 13 : E1 Lock Procedure for CIC link on A interface link \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/

      /* setDbForE1(1,0,1); */
      setDbForE1(1,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/
      /* setDbForTimeSlot(0,2,1);*/
      setDbForTimeSlot(0,SYS_TS_USAGE_CIC,1);
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 0; /* Locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\nExpected Message\n");
                  printf("\nCfgE1ObjHndlr 13 : CM_SUCCESS \n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_GRHM_LOCK_REQ:
            {
               OamsCfgGrhmLockReq*  grhmLockReq;
               grhmLockReq = (OamsCfgGrhmLockReq *)gCfgMsgBuf ;
               // Send response from stub to CFG.
               cfgStubSendGrhmCfgLockResp(grhmLockReq->objType, grhmLockReq->objectId,0);
               //send Alarm..
               // cfgStubSendScmCfgAlarmInd(CIC_ENABLED);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (E1 AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(CIC_DISABLED);
            }
            if( alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf(" CfgE1ObjectHandler13 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\nCfgE1ObjHndlr 13 : Failed\n ");
      }
   }
}

/******************************************************************************************
  Test case #14
 ******************************************************************************************/
void CfgE1ObjectHandler14()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;   
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 14 : E1 Lock Procedure for CIC link on A interface link \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/

      /* setDbForE1(1,0,1); */
      setDbForE1(1,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/
      /* setDbForTimeSlot(0,1,1); */
      setDbForTimeSlot(0,SYS_TS_USAGE_FR,1);

      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 0; /* Locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n  Expected Message\n");
                  printf("\nCfgE1ObjHndlr 14 : SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_PSSCM_LOCK_REQ:
            {
               OamsCfgPsscmLockReq *psscmLockReq;
               psscmLockReq = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendPsscmCfgLockResp(psscmLockReq->ObjType,psscmLockReq->lengthOfList,psscmLockReq->ObjId,psscmLockReq->e1Num,0);
               //send Alarm..
               //cfgStubSendScmCfgAlarmInd(0);
               printf("\nSendin the OAMS_CFG_PSSCM_LOCK_RESP\n:");               
            }
            break;    
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if(alarmcount ==1)
            {
               printf("\nAlarm has been received (E1 AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(FRLINK_DISABLED);
            }
            if(alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf("CfgE1ObjectHandler14 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler14 : Failed\n ");

      }
   }
}

/******************************************************************************************
  Test case #15
 ******************************************************************************************/
void CfgE1ObjectHandler15()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;   
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 15 : E1 Lock Procedure for MTP2 & FR on A interface link \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/
      /*    setDbForE1(1,0,1); */
      setDbForE1(1,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /* setDbCombForTimeSlot(0,0,1,1); */
      setDbCombForTimeSlot(0,SYS_TS_USAGE_FR,SYS_TS_USAGE_MTP2,1);

      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 0; /* Locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message\n");
                  printf("\nCfgE1ObjHndlr 15 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_SCM_LOCK_REQ:
            {

               OamsCfgScmUnlockReq *scmUnlockReq;
               scmUnlockReq = (OamsCfgScmUnlockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendCfgScmLockResp( scmUnlockReq->ObjType, scmUnlockReq->lengthOfList, 
                     scmUnlockReq->objectIdList, scmUnlockReq->e1Num,0,0);
               printf("\nSending the OAMS_CFG_SCM_LOCK_RESP to CFG...\n");
               //send Alarm..
               //cfgStubSendScmCfgAlarmInd(0);
            }
            break;  
         case  OAMS_CFG_PSSCM_LOCK_REQ:
            {
               OamsCfgPsscmLockReq *psscmLockReq;
               psscmLockReq = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendPsscmCfgLockResp(psscmLockReq->ObjType,psscmLockReq->lengthOfList,psscmLockReq->ObjId,psscmLockReq->e1Num,0);
               printf("\nSending the OAMS_CFG_PSSCM_LOCK_RESP to CFG...\n");
               //send Alarm..
               //cfgStubSendScmCfgAlarmInd(0);
               printf("\nSending the OAMS_CFG_PSSCM_LOCK_RESP\n:");
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount == 1)
            {
               printf("\nAlarm has been received (E1 AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
               cfgStubSendScmCfgAlarmInd(FRLINK_DISABLED);
            }
            if( alarmcount == 3 )
            {
               gTestCaseCompleted = 1;
               printf(" CfgE1ObjectHandler15 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler15 : Failed\n ");
      }
   }
}

/******************************************************************************************
  Test case #16
 ******************************************************************************************/
void CfgE1ObjectHandler16()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount; 
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 16 : E1 Lock Procedure for MTP2 & CIC on A interface link \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/      
      /* setDbForE1(1,0,1); */
      setDbForE1(1,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /* setDbCombForTimeSlot(0,0,2,1); */
      setDbCombForTimeSlot(0,SYS_TS_USAGE_CIC,SYS_TS_USAGE_MTP2,1);

      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 0; /* Locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message\n");
                  printf("\nCfgE1ObjHndlr 16 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }
            }
            break;
         case  OAMS_CFG_SCM_LOCK_REQ:
            {

               OamsCfgScmUnlockReq *scmUnlockReq;
               scmUnlockReq = (OamsCfgScmUnlockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendCfgScmLockResp( scmUnlockReq->ObjType, scmUnlockReq->lengthOfList,
                     scmUnlockReq->objectIdList, scmUnlockReq->e1Num,0,0);
               printf("\nSending the OAMS_CFG_SCM_LOCK_RESP to CFG...\n");
               //send Alarm..
               //cfgStubSendScmCfgAlarmInd(0);
            }
            break;
         case  OAMS_CFG_GRHM_LOCK_REQ:
            {
               OamsCfgGrhmUnlockReq*  grhmUnlockReq;
               grhmUnlockReq = (OamsCfgGrhmUnlockReq *)gCfgMsgBuf ;
               // Send response from stub to CFG.
               cfgStubSendGrhmCfgLockResp(grhmUnlockReq->objType, grhmUnlockReq->objectId,0);
               printf("\nSending the OAMS_CFG_GRHM_LOCK_RESP to CFG...\n");
               //send Alarm..
               // cfgStubSendScmCfgAlarmInd(CIC_ENABLED);
            }
            break;  
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount == 1)
            {
               printf("\nAlarm has been received (E1 AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
               cfgStubSendScmCfgAlarmInd(CIC_DISABLED);
            }
            if( alarmcount == 3 )
            {
               gTestCaseCompleted = 1;
               printf("CfgE1ObjHndlr 16 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\nCfgE1ObjHndlr 1 : Failed\n ");

      }
   }
}

/******************************************************************************************
  Test case #17
 ******************************************************************************************/
void CfgE1ObjectHandler17()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;  
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 17 : E1 Lock Procedure for FR & CIC on A interface link \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/      
      /* setDbForE1(1,0,1); */
      setDbForE1(1,SYS_E1_USAGE_AIF,1);
      /*setDbCombForTimeSlot(0,1,2,1); */
      setDbCombForTimeSlot(0,SYS_TS_USAGE_CIC,SYS_TS_USAGE_FR,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/

      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 0; /* Locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\nExpected Message\n");
                  printf("\nCfgE1ObjHndlr 17 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }
            }
            break;
         case  OAMS_CFG_GRHM_LOCK_REQ:
            {
               OamsCfgGrhmUnlockReq*  grhmUnlockReq;
               grhmUnlockReq = (OamsCfgGrhmUnlockReq *)gCfgMsgBuf ;
               // Send response from stub to CFG.
               cfgStubSendGrhmCfgLockResp(grhmUnlockReq->objType, grhmUnlockReq->objectId,0);
               printf("\nSending the OAMS_CFG_GRHM_LOCK_RESP to CFG...\n");
               //send Alarm..
               // cfgStubSendScmCfgAlarmInd(CIC_ENABLED);
            }
            break;
         case  OAMS_CFG_PSSCM_LOCK_REQ:
            {
               OamsCfgPsscmLockReq *psscmLockReq;
               psscmLockReq = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendPsscmCfgLockResp(psscmLockReq->ObjType,psscmLockReq->lengthOfList,psscmLockReq->ObjId,psscmLockReq->e1Num,0);
               printf("\nSending the OAMS_CFG_PSSCM_LOCK_RESP to CFG...\n");
               //send Alarm..
               //cfgStubSendScmCfgAlarmInd(0);
               printf("\nSending the OAMS_CFG_PSSCM_LOCK_RESP\n:");
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount == 1)
            {
               printf("\nAlarm has been received (E1 AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(FRLINK_DISABLED);
               cfgStubSendScmCfgAlarmInd(CIC_DISABLED);
            }
            if( alarmcount == 3 )
            {
               gTestCaseCompleted = 1;
               printf(" CfgE1ObjectHandler17 : Success\n");
            }
            break;




         default:
            printf("\n Not Expected Message\n");
            printf("\nCfgE1ObjHndlr 1 : Failed\n ");
            break;
      }
   }
}


/******************************************************************************************
  Test case #18
 ******************************************************************************************/
void CfgE1ObjectHandler18()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount; 
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 18 : E1 Lock Procedure for FR, CIC & MTP2 on A interface link \n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/

      /* setDbForE1(1,0,1); */
      setDbForE1(1,SYS_E1_USAGE_AIF,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/   
      /*setDbMuxForTimeSlot(1,0,1,2,1);*/   
      setDbMuxForTimeSlot(1,SYS_TS_USAGE_FR,SYS_TS_USAGE_CIC,SYS_TS_USAGE_MTP2,1);
      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 0; /* Locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message\n");
                  printf("\nCfgE1ObjHndlr 18 : SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_SCM_LOCK_REQ:
            {

               OamsCfgScmLockReq *scmlockReq;
               scmlockReq = (OamsCfgScmLockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendCfgScmLockResp( scmlockReq->ObjType, scmlockReq->lengthOfList,
                     scmlockReq->objectIdList, scmlockReq->e1Num,0,0);
               printf("\nSending the OAMS_CFG_SCM_LOCK_RESP to CFG...\n");
               //send Alarm..
               //cfgStubSendScmCfgAlarmInd(0);
            }
            break;

         case  OAMS_CFG_GRHM_LOCK_REQ:
            {
               OamsCfgGrhmUnlockReq*  grhmUnlockReq;
               grhmUnlockReq = (OamsCfgGrhmUnlockReq *)gCfgMsgBuf ;
               // Send response from stub to CFG.
               cfgStubSendGrhmCfgLockResp(grhmUnlockReq->objType, grhmUnlockReq->objectId,0);
               printf("\nSending the OAMS_CFG_GRHM_LOCK_RESP to CFG...\n");
               //send Alarm..
               // cfgStubSendScmCfgAlarmInd(CIC_ENABLED);
            }
            break;
         case  OAMS_CFG_PSSCM_LOCK_REQ:
            {
               OamsCfgPsscmLockReq *psscmLockReq;
               psscmLockReq = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendPsscmCfgLockResp(psscmLockReq->ObjType,psscmLockReq->lengthOfList,psscmLockReq->ObjId,psscmLockReq->e1Num,0);
               printf("\nSending the OAMS_CFG_PSSCM_LOCK_RESP to CFG...\n");
               //send Alarm..
               //cfgStubSendScmCfgAlarmInd(0);
               printf("\nSending the OAMS_CFG_PSSCM_LOCK_RESP\n:");
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount == 1)
            {
               printf("\nAlarm has been received (E1 AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
               cfgStubSendScmCfgAlarmInd(FRLINK_DISABLED);
               cfgStubSendScmCfgAlarmInd(CIC_DISABLED);
            }
            if( alarmcount == 4 )
            {
               gTestCaseCompleted = 1;
               printf(" CfgE1ObjectHandler18 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1ObjectHandler18 : Failed\n ");

      }
   }
}

/******************************************************************************************
  Test case #19
 ******************************************************************************************/
void CfgE1ObjectHandler19()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 19 : E1 Lock Procedure for LAPD link on Abis interface link\n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/

      /* setDbForE1(1,1,1); */
      setDbForE1(1,SYS_E1_USAGE_ABIS,1);
      /* setDbForAbisTimeslot(0,3,1,32); */
      setDbForAbisTimeslot(0,SYS_TS_USAGE_LAPD_OML,1,32);   

      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 0; /* Locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\nExpected Message\n");
                  printf("\nCfgE1ObjHndlr 19 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;

         case  OAMS_CFG_TRXH_LOCK_REQ:
            {
               OamsCfgTrxhLockReq*  trxhlockReq;
               trxhlockReq  = (OamsCfgTrxhLockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendTrxhCfgLockResp(trxhlockReq->objType,trxhlockReq->objId,trxhlockReq->e1Num);
               printf("\nSending the OAMS_CFG_TRXH_LOCK_RESP... \n");  
               //send Alarm..
               //SysAlarm sysAlarm;
               //cfgStubSendPcuCfgAlarmInd (sysAlarm);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (E1 AST=Locked)\n");        
               gTestCaseCompleted = 1;
               printf("CfgE1ObjHndlr 19 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\nCfgE1ObjHndlr 1 : Failed\n ");

      }
   }
}

/******************************************************************************************
  Test case #20
 ******************************************************************************************/
void CfgE1ObjectHandler20()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;  
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 20 : E1 Lock Procedure for LAPD link on Abis interface link\n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/

      /* setDbForE1(1,1,1); */
      setDbForE1(1,SYS_E1_USAGE_ABIS,1);

      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/

      /*Configure in Db for Abis timeslots */
      /* setDbForAbisTimeslot(0,3,1,2); */
      setDbForAbisTimeslot(0,SYS_TS_USAGE_LAPD_OML,1,2);   

      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 0; /* Locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\nExpected Message\n");
                  printf("\nCfgE1ObjHndlr 20 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;

         case  OAMS_CFG_TRXH_LOCK_REQ:
            {
               OamsCfgTrxhLockReq*  trxhlockReq;
               trxhlockReq  = (OamsCfgTrxhLockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendTrxhCfgLockResp(trxhlockReq->objType,trxhlockReq->objId,trxhlockReq->e1Num);
               printf("\nSending the OAMS_CFG_TRXH_LOCK_RESP... \n");  
               //send Alarm..
               //SysAlarm sysAlarm;
               //cfgStubSendPcuCfgAlarmInd (sysAlarm);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (E1 AST=Locked)\n");        
               gTestCaseCompleted = 1;
               printf("CfgE1ObjHndlr 20 : Success\n");
            }
            break;

         default:
            printf("\n Unexpected Message\n");

      }
   }
}
/******************************************************************************************
  Test case #21
 ******************************************************************************************/
void CfgE1ObjectHandler21()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff = {0};
   static alarmcount;   
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1ObjectHandler 21 : E1 Lock Procedure for LAPD link on Abis interface link\n");

      /* First set the required database */
      /*setDbForE1(I_U32 State, I_U32 UsingEntity, I_U32 e1Num)*/

      /* setDbForE1(1,1,1); */
      setDbForE1(1,SYS_E1_USAGE_ABIS,1);
      /*Set TimeSlot Table According to the Scenario*/ 
      /*void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)*/

      /*Configure in Db for Abis timeslots */
      /* setDbForAbisTimeslot(0,3,1,3); */
      setDbForAbisTimeslot(0,SYS_TS_USAGE_LAPD_OML,1,3);   

      E1TableApiBuff.e1Num=1;
      E1TableApiBuff.adminState = 0; /* Locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_SET_E1PERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\nExpected Message\n");
                  printf("\nCfgE1ObjHndlr 21 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;

         case  OAMS_CFG_TRXH_LOCK_REQ:
            {
               OamsCfgTrxhLockReq*  trxhlockReq;
               trxhlockReq  = (OamsCfgTrxhLockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendTrxhCfgLockResp(trxhlockReq->objType,trxhlockReq->objId,trxhlockReq->e1Num);
               printf("\nSending the OAMS_CFG_TRXH_LOCK_RESP... \n");  
               //send Alarm..
               //SysAlarm sysAlarm;
               //cfgStubSendPcuCfgAlarmInd (sysAlarm);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (E1 AST=Locked)\n");        
               gTestCaseCompleted = 1;
               printf("CfgE1ObjHndlr 21 : Success\n");
            }
            break;

         default:
            printf("\nNot Expected Message\n");
            printf("\nCfgE1ObjHndlr 21 : Failure\n ");

      }
   }
}
/******************************************************************************************
  Test case #22
 ******************************************************************************************/
void CfgE1TimeslotObjectHandler1()
{
   static int testInitiation =1;
   TimeSlotTableApi tSlotApiBuff = {0};
   static alarmcount; 
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1TimeslotObjectHandler1, Test case 22 :E1Timeslot Lock Procedure for A interface link\n");

      /* First set the required database */
      /* void setDbForE1TimeSlot(i_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum)*/
      /* setDbForE1TimeSlot(1,0,1,0); */
      setDbForE1TimeSlot(1,SYS_TS_USAGE_MTP2,1,0);
      tSlotApiBuff.e1Num=1;
      tSlotApiBuff.tsNum=0;
      tSlotApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&tSlotApiBuff,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {

                  printf("CM_SUCCESS");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  printf("CM_FAILURE");
                  gTestCaseCompleted = 1;
                  printf("CfgE1TimeslotObjectHandler1 1 : Success\n");
               }

            }
            break;
         default:
            gTestCaseCompleted = 1;
            printf("\n Not Expected Message\n");
            printf("\nCfgE1TimeslotObjectHandler1 : Failed\n ");
      }   
   }
}
/********************************************************************************
  Test Case #23;
 ********************************************************************************/
void CfgE1TimeslotObjectHandler2()
{
   static int testInitiation =1;
   static alarmcount;   
   TimeSlotTableApi tSlotApiBuff = {0};

   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1TimeslotObjectHandler2  : E1TimeSlot ULock Request for MTP2 \n");

      /* First set the required database */
      /* void setDbForE1TimeSlot(i_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum)*/
      /*setDbForE1TimeSlot(0,0,1,0);*/
      setDbForE1TimeSlot(0,SYS_TS_USAGE_MTP2,1,0);
      tSlotApiBuff.e1Num=1;
      tSlotApiBuff.tsNum=0;
      tSlotApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&tSlotApiBuff,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);

   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n  Expected Message\n");
                  printf("\nC : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;

         case  OAMS_CFG_SCM_UNLOCK_REQ:
            { 
               printf("\n I am In OAMS_CFG_SCM_UNLOCK_RESP\n");   
               OamsCfgScmUnlockReq *scmUnlockReq;
               scmUnlockReq = (OamsCfgScmUnlockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               printf("\nSending the OAMS_CFG_SCM_UNLOCK_RESP Message... \n");                                      
               cfgStubSendCfgScmUnLockResp( scmUnlockReq->ObjType, scmUnlockReq->lengthOfList,scmUnlockReq->objectIdList,scmUnlockReq->e1Num,scmUnlockReq->tsNum,0);
            }
            break; 
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (TimeSlot AST=Unlocked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_ENABLED);
            }
            if( alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf("CfgE1TimeslotObjectHandler2 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\nCfgE1TimeslotObjectHandler2 : Failed\n ");

      }
   }
}

/********************************************************************************
  Test Case #26;
 ********************************************************************************/
void CfgE1TimeslotObjectHandler5()
{
   static int testInitiation =1;
   static alarmcount;   
   TimeSlotTableApi tSlotApiBuff = {0};
   OamsCfgGrhmUnlockReq*  grhmUnlockReq;
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1TimeslotObjectHandler3  : E1iTimeSlot ULock Request for FR\n");

      /* First set the required database */
      /* void setDbForE1TimeSlot(i_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum)*/
      /* setDbForE1TimeSlot(0,2,1,0); */
      setDbForE1TimeSlot(0,SYS_TS_USAGE_CIC,1,0);
      tSlotApiBuff.e1Num=1;
      tSlotApiBuff.tsNum=0;
      tSlotApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&tSlotApiBuff,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);

   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message\n");
                  printf("\nCfgE1TimeslotObjectHandler5 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_GRHM_UNLOCK_REQ:
            {

               grhmUnlockReq = (OamsCfgGrhmUnlockReq *) gCfgMsgBuf;
               // Send response from stub to CFG.
               printf("grhmUnlockReq->objectId  %ld",grhmUnlockReq->objectId);  
               cfgStubSendGrhmCfgUnlockResp(OAMS_OBJTYPE_TIMESLOT,grhmUnlockReq->objectId);
               printf("\nSending the OAMS_CFG_GRHM_UNLOCK_RESP ...\n"); 
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (TimeSlot AST=Unlocked)\n");        
               cfgStubSendScmCfgAlarmInd(CIC_ENABLED);
            }
            if( alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf(" CfgE1TimeslotObjectHandler3 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1TimeslotObjectHandler5: Failed\n ");

      }
   }
}
/********************************************************************************
  Test Case #25;
 ********************************************************************************/
void CfgE1TimeslotObjectHandler4()
{
   static int testInitiation =1;
   static alarmcount;   
   TimeSlotTableApi tSlotApiBuff = {0};

   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1TimeslotObjectHandler4  : E1iTimeSlot ULock Request for CIC \n");

      /* First set the required database */
      /* void setDbForE1TimeSlot(i_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum)*/
      /* setDbForE1TimeSlot(0,3,1,0); */
      setDbForE1TimeSlot(0,SYS_TS_USAGE_MTP2,1,0);
      tSlotApiBuff.e1Num=1;
      tSlotApiBuff.tsNum=0;
      tSlotApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&tSlotApiBuff,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);

   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message\n");
                  printf("\nCfgE1TimeslotObjectHandler4 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;  
         case  OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *scmUnlockReq;
               scmUnlockReq = (OamsCfgScmUnlockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendCfgScmUnLockResp( scmUnlockReq->ObjType, scmUnlockReq->lengthOfList,scmUnlockReq->objectIdList,scmUnlockReq->e1Num,scmUnlockReq->tsNum,0);
               printf("\nSending the OAMS_CFG_SCM_UNLOCK_RESP Message... \n");
            }
            break; 
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (TimeSlot AST=Unlocked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_ENABLED);
            }
            if( alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf("CfgE1TimeslotObjectHandler4 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1TimeslotObjectHandler4: Failed\n ");

      }
   }
}
/********************************************************************************
  Test Case #24;
 ********************************************************************************/
void CfgE1TimeslotObjectHandler3()
{
   static int testInitiation =1;
   static alarmcount;   
   TimeSlotTableApi tSlotApiBuff = {0};


   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1TimeslotObjectHandler5  : E1iTimeSlot ULock Request for LAPD\n");

      /* First set the required database */
      /* void setDbForE1TimeSlot(i_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum)*/
      /* setDbForE1TimeSlot(0,1,1,0); */
      setDbForE1TimeSlot(0,SYS_TS_USAGE_FR,1,0);
      tSlotApiBuff.e1Num=1;
      tSlotApiBuff.tsNum=0;
      tSlotApiBuff.adminState = 1; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&tSlotApiBuff,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);

   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message\n");
                  printf("\nCfgE1TimeslotObjectHandler3 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_PSSCM_UNLOCK_REQ:
            {
               OamsCfgPsscmUnlockReq *psscmUnlockReq;
               setFrLinkTable(); /*For Pre Condition*/  
               psscmUnlockReq = (OamsCfgPsscmUnlockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               printf("\n psscmUnlockReq->objectIdList :%d\n",psscmUnlockReq->objectIdList[0]);     
               cfgStubSendPsscmCfgUnlockResp(psscmUnlockReq->ObjType, psscmUnlockReq->lengthOfList,
                     psscmUnlockReq->objectIdList, psscmUnlockReq->e1Num,0,0,0);
               printf("\nSending the OAMS_CFG_PSSCM_UNLOCK_RESP \n");   
            }
            break; 
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (TimeSlot AST=Unlocked)\n");        
               cfgStubSendScmCfgAlarmInd(FRLINK_ENABLED);
            }
            if( alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf("\n CfgE1TimeslotObjectHandler3 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1TimeslotObjectHandler3 : Failed\n ");
      }
   }
}

/********************************************************************************
  Test Case #27;
 ********************************************************************************/
void CfgE1TimeslotObjectHandler6()
{
   static int testInitiation =1;
   static alarmcount;   
   TimeSlotTableApi tSlotApiBuff = {0};


   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1TimeslotObjectHandler6: E1TimeSlot Lock Request for MTP2 \n");

      /* First set the required database */
      /* void setDbForE1TimeSlot(i_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum)*/
      /* setDbForE1TimeSlot(1,0,1,0); */
      setDbForE1TimeSlot(1,SYS_TS_USAGE_MTP2,1,0);
      tSlotApiBuff.e1Num=1;
      tSlotApiBuff.tsNum=0;
      tSlotApiBuff.adminState = 0; /* locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&tSlotApiBuff,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);
   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\nExpected Message\n");
                  printf("\nCfgE1TimeslotObjectHandler6 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_SCM_LOCK_REQ:
            {
               OamsCfgScmLockReq *scmlockReq;
               SysAlarm sysAlarm;
               scmlockReq = (OamsCfgScmLockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendCfgScmLockResp(scmlockReq->ObjType, scmlockReq->lengthOfList,scmlockReq->objectIdList,scmlockReq->e1Num,scmlockReq->tsNum,0);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (TimeSlot AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
            }
            if( alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf("CfgE1TimeslotObjectHandler6: Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n : Failed\n ");
      }
   }
}

/********************************************************************************
  Test Case #30;
 ********************************************************************************/
void CfgE1TimeslotObjectHandler9()
{
   static int testInitiation =1;
   static alarmcount;   
   TimeSlotTableApi tSlotApiBuff = {0};


   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1TimeslotObjectHandler30  : E1iTimeSlot ULock Request for cic \n");

      /* First set the required database */
      /* void setDbForE1TimeSlot(i_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum)*/
      /* setDbForE1TimeSlot(1,2,1,0); */
      setDbForE1TimeSlot(1,SYS_TS_USAGE_CIC,1,0);
      tSlotApiBuff.e1Num=1;
      tSlotApiBuff.tsNum=0;
      tSlotApiBuff.adminState = 0; /* locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&tSlotApiBuff,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);

   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\nExpected Message\n");
                  printf("\nCfgE1TimeslotObjectHandler9: CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_GRHM_LOCK_REQ:
            {
               OamsCfgGrhmLockReq*  grhmUnlockReq;
               grhmUnlockReq = (OamsCfgGrhmLockReq *)gCfgMsgBuf ;
               // Send response from stub to CFG.
               cfgStubSendGrhmCfgLockResp(grhmUnlockReq->objType, grhmUnlockReq->objectId);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount ==1 )
            {
               printf("\nAlarm has been received (TimeSlot AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(CIC_DISABLED);
            }
            if( alarmcount ==2 )
            {
               gTestCaseCompleted = 1;
               printf("CfgE1TimeslotObjectHandler9 : Success\n");
            }
            break;


         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1TimeslotObjectHandler9 : Failed\n ");

      }
   }
}
/********************************************************************************
  Test Case #29;
 ********************************************************************************/
void CfgE1TimeslotObjectHandler8()
{
   static int testInitiation =1;
   static alarmcount;       
   TimeSlotTableApi tSlotApiBuff = {0};
   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1TimeslotObjectHandler29  : E1iTimeSlot ULock Request for LAPD \n");

      /* First set the required database */
      /* void setDbForE1TimeSlot(i_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum)*/
      /* setDbForE1TimeSlot(1,3,1,0); */
      setDbForE1TimeSlot(1,SYS_TS_USAGE_LAPD_OML,1,0);
      tSlotApiBuff.e1Num=1;
      tSlotApiBuff.tsNum=0;
      tSlotApiBuff.adminState =0 ; /* unlocked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&tSlotApiBuff,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);

   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\n Expected Message\n");
                  printf("\nCfgE1TimeslotObjectHandler8 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break; 
         case  OAMS_CFG_SCM_LOCK_REQ:
            {
               OamsCfgScmLockReq *scmlockReq;
               SysAlarm sysAlarm;
               scmlockReq = (OamsCfgScmLockReq  *)gCfgMsgBuf;
               // Send response from stub to CFG.
               printf("\n Sending the... OAMS_CFG_SCM_LOCK_RESP\n");
               cfgStubSendCfgScmLockResp(scmlockReq->ObjType, scmlockReq->lengthOfList,scmlockReq->objectIdList,scmlockReq->e1Num,scmlockReq->tsNum,0);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount == 1 )
            {
               printf("\nAlarm has been received (TimeSlot AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
            }
            if( alarmcount == 2 )
            {
               gTestCaseCompleted = 1;
               printf("CfgE1TimeslotObjectHandler8 : Success\n");
            }
            break;


         default:
            printf("\n Not Expected Message\n");
            printf("\nCfgE1TimeslotObjectHandler8 : Failed\n ");

      }
   }
}
/********************************************************************************
  Test Case #28
 ********************************************************************************/
void CfgE1TimeslotObjectHandler7()
{
   static int testInitiation =1;
   static alarmcount;   
   TimeSlotTableApi tSlotApiBuff = {0};


   if ( testInitiation )
   {
      testInitiation =0;
      printf("CfgE1TimeslotObjectHandler28  : E1iTimeSlot ULock Request for FR\n");

      /* First set the required database */
      /* void setDbForE1TimeSlot(i_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum)*/
      /* setDbForE1TimeSlot(1,1,1,0); */
      setDbForE1TimeSlot(1,SYS_TS_USAGE_FR,1,0);
      tSlotApiBuff.e1Num=1;
      tSlotApiBuff.tsNum=0;
      tSlotApiBuff.adminState = 0; /* locked */
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&tSlotApiBuff,sizeof(TimeSlotTableApi),BSC_API_SET_TIMESLOTPERTABLE);

   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  printf("\nExpected Message\n");
                  printf("\nCfgE1TimeslotObjectHandler7 : CM_SUCCESS\n ");
               }
               else
               {
                  printf("CM_FAILURE");
               }

            }
            break;
         case  OAMS_CFG_PSSCM_LOCK_REQ:
            {
               OamsCfgPsscmLockReq *psscmUnlockReq;
               setFrLinkTable();/*For Pre condition..*/  
               psscmUnlockReq = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
               // Send response from stub to CFG.
               cfgStubSendPsscmCfgLockResp (psscmUnlockReq->ObjType, psscmUnlockReq->lengthOfList,
                     psscmUnlockReq->ObjId, psscmUnlockReq->e1Num,0);
               //send Alarm..
               //cfgStubSendPsscmCfgAlarmInd(0);
            }
            break;
         case  OAMS_CFG_AFH_ALARM_IND:
            alarmcount++;
            if( alarmcount == 1 )
            {
               printf("\nAlarm has been received (TimeSlot AST=Locked)\n");        
               cfgStubSendScmCfgAlarmInd(FRLINK_DISABLED);
            }
            if( alarmcount == 2 )
            {
               gTestCaseCompleted = 1;
               printf("\nCfgE1TimeslotObjectHandler7 : Success\n");
            }
            break;

         default:
            printf("\n Not Expected Message\n");
            printf("\n CfgE1TimeslotObjectHandler7 : Failed\n ");
      } /* Swotch ends here*/
   }/*Else ends here*/


}/*Function ends here*/

/************************ E1 DB INSRTIONS FOR EXECUTING TEST CASES ****************************/
void setDbForE1(I_U32 State, I_U32 UsingType, I_U32 e1Num)
{
   /* First set the required database */
   I_S32 errCode = 0;
   E1TableApi *inData;
   E1TableIndices  e1TableIndices;

   /*Delete the row before Inserting....*/ 
   e1TableIndices.e1Num=e1Num;
   if(deleteE1Table(&e1TableIndices) != CLIB_SUCCESS)
   {
      printf("Delete failed for E1Table\n");
   }

   /* Set the config parameters into database */
   inData = (E1TableApi *) malloc(sizeof(E1TableApi));    /* memory allocation */
   inData->e1Num = e1Num;
   inData->adminState = State;
   inData->usingEntity=0;/* Ain - 0 , Abis -1  */
   inData->usageType=UsingType;/* Ain - 0 , Abis -1  */
   inData->oprState=(I_U32)0;/* 0 - Enabled , 1- Disabled */   
   errCode= insertE1Table(inData);  /*DB Wrapper .................*/
   if(errCode==CLIB_SUCCESS)
      printf("\nInsertion is Success\n");   
   free(inData);
}
/********************************************************************************************/

void setDbForE1TimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num, I_U32 tsNum)
{
   /* First set the required database */
   I_S32 errCode = 0;
   TimeSlotTableApi *inData;
   TimeSlotTableIndices timeSlotTableIndices;

   /* Delete the row before inserting */        
   timeSlotTableIndices.e1Num=e1Num;
   timeSlotTableIndices.tsNum=tsNum;   
   errCode=deleteTimeSlotTable(&timeSlotTableIndices);
   /* Set the config parameters into database */
   inData = (TimeSlotTableApi *) malloc(sizeof(TimeSlotTableApi));    /* memory allocation */
   inData->e1Num = e1Num;
   inData->tsNum=tsNum;
   inData->adminState = State;
   inData->usageType=usageType; /*mtp2 0 , fr 1, cic 2, OMLLAPD 3*/
   inData->usingEntity=(I_U32)1; /* linkCode - mtp2 , fr -index , cic -cic list*/
   if(State==1)
      inData->oprState=(I_U32)1;/* 0 - Enabled , 1- Disabled */   
   else
      inData->oprState=(I_U32)0;/* 0 - Enabled , 1- Disabled */        
   errCode= insertTimeSlotTable(inData);  /*DB Wrapper .................*/
   if(errCode==CLIB_SUCCESS)
      printf("\nInsertion is Success\n");   
   free(inData);


}

/************************ TimeSlot DB INSRTIONS FOR EXECUTING TEST CASES ****************************/
void setDbForTimeSlot(I_U32 State, I_U32 usageType, I_U32 e1Num)
{
   /* First set the required database */
   I_S32 errCode = 0;
   TimeSlotTableApi *inData;
   TimeSlotTableIndices timeSlotTableIndices;

   /*Delete the row before Inserting....*/ 
   timeSlotTableIndices.e1Num=e1Num;
   int i;
   for(i=0;i<32;i++)
   {   
      timeSlotTableIndices.tsNum=(I_U32)i;   
      errCode=deleteTimeSlotTable(&timeSlotTableIndices);
      if(errCode!=CLIB_SUCCESS)
         printf("\n setDbForTimeSlot delete Error\n");      
   }

   /* Set the config parameters into database */
   for(i=0;i<32;i++)
   {   
      inData = (TimeSlotTableApi *) malloc(sizeof(TimeSlotTableApi));    /* memory allocation */
      inData->e1Num = e1Num;
      inData->tsNum=(I_U32)i;
      inData->adminState =State ;
      inData->usageType=usageType; /*mtp2 0 , fr 1, cic 2, OMLLAPD 3*/
      inData->usingEntity=(I_U32)1; /* linkCode - mtp2 , fr -index , cic -cic list*/
      if(State==1)
         inData->oprState=(I_U32)1;/* 0 - Enabled , 1- Disabled */   
      else
         inData->oprState=(I_U32)0;/* 0 - Enabled , 1- Disabled */        
      errCode= insertTimeSlotTable(inData);  /*DB Wrapper .................*/
      if(errCode==CLIB_SUCCESS)
         printf("\nInsertion is Success\n");   
      free(inData);
   }
}


void setDbForAbisTimeslot(I_U32 State, I_U32 usageType, I_U32 e1num, I_U32 count)
{
   /* First set the required database */
   I_S32 errCode = 0;
   I_U16 i;
   TimeSlotTableIndices timeSlotTableIndices;
   TimeSlotTableApi *inData;

   /* Delete the row before inserting ...*/
   timeSlotTableIndices.e1Num = e1num;

   for (i = 0; i < count; i++)
   {
      timeSlotTableIndices.tsNum = (I_U32)i;
      errCode = deleteTimeSlotTable(&timeSlotTableIndices);
   }

   /* Set the confit parameters into database */
   for (i = 0; i < count;i++)
   {
      inData = (TimeSlotTableApi *) malloc(sizeof(TimeSlotTableApi));      /* memory allocation */
      inData->e1Num = e1num;
      inData->tsNum = (I_U32)i;
      inData->adminState = State;
      inData->usingEntity = usageType;  /* linkCode - mtp2, fr - index, cic - cic list */

      if(State==1)
         inData->oprState=(I_U32)1;/* 0 - Enabled , 1- Disabled */   
      else
         inData->oprState=(I_U32)0;/* 0 - Enabled , 1- Disabled */        
      errCode= insertTimeSlotTable(inData);  /*DB Wrapper .................*/
      if(errCode==CLIB_SUCCESS)
         printf("\nInsertion is Success\n");   
      free(inData);
   }
}   

/********************************************************************************************/

/************************ TimeSlot DB INSRTIONS FOR EXECUTING TEST CASES ****************************/
void setDbCombForTimeSlot(I_U32 State, I_U32 type1, I_U32 type2,  I_U32 e1Num)
{
   /* First set the required database */
   I_S32 errCode = 0;
   I_U16 i;
   TimeSlotTableApi *inData;
   TimeSlotTableIndices timeSlotTableIndices;
   /*Delete the row before Inserting....*/ 
   timeSlotTableIndices.e1Num=e1Num;
   for(i=0;i<32;i++)
   {   
      timeSlotTableIndices.tsNum=(I_U32)i;   
      errCode=deleteTimeSlotTable(&timeSlotTableIndices);
   }

   /* Set the config parameters into database */
   for(i=0;i<32;i++)
   {   
      inData = (TimeSlotTableApi *) malloc(sizeof(TimeSlotTableApi));    /* memory allocation */
      inData->e1Num = e1Num;
      inData->tsNum=(I_U32)i;
      inData->adminState = State;
      if (i%2 == 0)
         inData->usageType=type1; /*mtp2 0 , fr 1, cic 2, OMLLAPD 3*/
      else
         inData->usageType=type2;
      inData->usingEntity=(I_U32)1; /* linkCode - mtp2 , fr -index , cic -cic list*/
      if(State==1)
         inData->oprState=(I_U32)1;/* 0 - Enabled , 1- Disabled */   
      else
         inData->oprState=(I_U32)0;/* 0 - Enabled , 1- Disabled */        
      errCode= insertTimeSlotTable(inData);  /*DB Wrapper .................*/
      if(errCode==CLIB_SUCCESS)
         printf("\nInsertion is Success\n");   
      free(inData);
   }
}

void setDbMuxForTimeSlot(I_U32 State, I_U32 type1, I_U32 type2, I_U32 type3, I_U32 eNum)
{
   /* First set the required database */
   I_S32 errCode = 0;
   TimeSlotTableApi *inData;
   TimeSlotTableIndices timeSlotTableIndices;
   I_U16 i;
   /*Delete the row before Inserting....*/
   timeSlotTableIndices.e1Num=eNum;
   for(i=0;i<32;i++)
   {
      timeSlotTableIndices.tsNum=(I_U32)i;
      errCode=deleteTimeSlotTable(&timeSlotTableIndices);
   }

   /* Set the config parameters into database */
   for(i=0;i<32;i++)
   {
      inData = (TimeSlotTableApi *) malloc(sizeof(TimeSlotTableApi));         /* memory allocation */
      inData->e1Num = eNum;
      inData->tsNum=(I_U32)i;
      inData->adminState = State;
      if (i%3 == 0)
         inData->usageType=type1; /*mtp2 0 , fr 1, cic 2, OMLLAPD 3*/
      if (i%3 == 1)
         inData->usageType=type2;
      if (i%3 == 2)
         inData->usageType=type3;
      inData->usingEntity=(I_U32)1; /* linkCode - mtp2 , fr -index , cic -cic list*/
      if(State==1)
         inData->oprState=(I_U32)1;/* 0 - Enabled , 1- Disabled */
      else
         inData->oprState=(I_U32)0;/* 0 - Enabled , 1- Disabled */
      errCode= insertTimeSlotTable(inData);  /*DB Wrapper .................*/
      if(errCode==CLIB_SUCCESS)
         printf("\nInsertion is Success\n");
      free(inData);
   }
}

/************************************************************************************************/


void setFrLinkTable()
{
   FrLinkTableIndices frIndices;
   frIndices.frLinkNo=1;
   printf("%d",deleteFrLinkTable(&frIndices));
   FrLinkTableApi *FrLinkBuff;
   FrLinkBuff =(FrLinkTableApi *) malloc(sizeof(FrLinkTableApi));         /* memory allocation */
   FrLinkBuff->frLinkNo=1;
   FrLinkBuff->e1=1;
   FrLinkBuff->ts=0;
   printf("%d", insertFrLinkTable(FrLinkBuff));


}
