#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  2
int test_result[totalNoOfTC];
void setup (void)
{
  /* Setup Procedure to be written (if any)*/
}


void teardown (void)
{
  /* TearDown Procedure to be written (if any)*/
}


/**************************************************************************
 TC Name: TC_001

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_UNLOCK_REQ is received in PsscmIdle state.
**************************************************************************/
START_TEST (TC_001)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgPsscmUnlockReq oamsCfgPsscmUnlockReq;

  /*Receive Message Struct */
   OamsPsscmNsProvNsei oamsPsscmNsProvNsei;
   oamsCfgPsscmUnlockReq.sysHdr.src.prcr = PRCR_PP;
   oamsCfgPsscmUnlockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPsscmUnlockReq.sysHdr.src.clsId = 0;
   oamsCfgPsscmUnlockReq.sysHdr.src.rfu = 0;
   oamsCfgPsscmUnlockReq.sysHdr.src.inst = 0;
   oamsCfgPsscmUnlockReq.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgPsscmUnlockReq.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsCfgPsscmUnlockReq.sysHdr.dest.clsId = 0;
   oamsCfgPsscmUnlockReq.sysHdr.dest.rfu = 0;
   oamsCfgPsscmUnlockReq.sysHdr.dest.inst = 0;
   oamsCfgPsscmUnlockReq.sysHdr.msgType = OAMS_CFG_PSSCM_UNLOCK_REQ;
   oamsCfgPsscmUnlockReq.sysHdr.subType = 0;
   oamsCfgPsscmUnlockReq.sysHdr.priority = 0;
   oamsCfgPsscmUnlockReq.reason = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPsscmUnlockReq,sizeof(OamsCfgPsscmUnlockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsProvNsei = *((OamsPsscmNsProvNsei *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsProvNsei.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.sysHdr.msgType == OAMS_PSSCM_NS_PROV_NSEI) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.type == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.type is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[1] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[1] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_002

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_UNLOCK_REQ is received in PsscmIdle state and Db call for populating local context fails .
**************************************************************************/
START_TEST (TC_002)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgPsscmUnlockReq oamsCfgPsscmUnlockReq;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   oamsCfgPsscmUnlockReq.sysHdr.src.prcr = PRCR_PP;
   oamsCfgPsscmUnlockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPsscmUnlockReq.sysHdr.src.clsId = 0;
   oamsCfgPsscmUnlockReq.sysHdr.src.rfu = 0;
   oamsCfgPsscmUnlockReq.sysHdr.src.inst = 0;
   oamsCfgPsscmUnlockReq.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgPsscmUnlockReq.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsCfgPsscmUnlockReq.sysHdr.dest.clsId = 0;
   oamsCfgPsscmUnlockReq.sysHdr.dest.rfu = 0;
   oamsCfgPsscmUnlockReq.sysHdr.dest.inst = 0;
   oamsCfgPsscmUnlockReq.sysHdr.msgType = OAMS_CFG_PSSCM_UNLOCK_REQ;
   oamsCfgPsscmUnlockReq.sysHdr.subType = 0;
   oamsCfgPsscmUnlockReq.sysHdr.priority = 0;
   oamsCfgPsscmUnlockReq.reason = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPsscmUnlockReq,sizeof(OamsCfgPsscmUnlockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgUnlockResp = *((OamsPsscmCfgUnlockResp *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgUnlockResp.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.sysHdr.msgType == OAMS_PSSCM_CFG_UNLOCK_RESP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.result is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.cause == 0xff) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.cause is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[2] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[2] = 1;    /* 1 for pass*/

}
END_TEST


 
int RunTestSuite(Suite * s)
{
   int number_failed;
   SRunner *sr = srunner_create(s);
   srunner_set_log(sr,"result.txt");
   srunner_set_fork_status(sr, CK_NOFORK);
   srunner_run_all(sr,CK_NORMAL);
   number_failed = srunner_ntests_failed (sr);
   srunner_free(sr);
   return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
 
 
void ExecuteTestSuite(void)
{
   int iChoice; 
   int iTCChoice; 
   int iTSChoice; 
   int iTSSChoice; 
   do{
 
      system("clear");
      printf("\n0: Exit ");  
      printf("\n1: Run Elementary Test case(s) ");  
      printf("\n2: Run Test Suite(s) ");  
      printf("\nEnter your choice :  ");  
      scanf("%d",&iChoice); 
      if(1 == iChoice)
      { 
        do{
       Suite *s = suite_create ("CFG");
       /* Core test case */
       TCase *tc_core = tcase_create ("Core");
       tcase_add_checked_fixture (tc_core, setup, teardown);
        system("clear");
        printf("\n0 : Previous Menu");
        printf("\n1. Run TC_001");
        printf("\n2. Run TC_002");
        printf("\nEnter your choice :  ");  
        scanf("%d",&iTCChoice); 
        if(iTCChoice > 0) 
        {
         
         if( 1 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_001);
           printf("\nRunning Test Case TC_001"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 2 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_002);
           printf("\nRunning Test Case TC_002"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
        }
           }while(iTCChoice != 0);
      }
    if(2 == iChoice)
     {
      do{
       Suite *s = suite_create ("CFG");
        system("clear");
        printf("\n0 : Previous Menu");
        printf("\n 100: Run all Test Suits");
        printf("\nPlease enter your choice : ");
        scanf("%d",&iTSChoice); 
         if( 100 == iTSChoice)  
         {
               printf("Running all Test Suites...");
               RunTestSuite(s);
         }
         }while(iTSChoice != 0);
      }
 
     }while(iChoice!=0);
    printf("\nExiting...");
    system("clear");
}


