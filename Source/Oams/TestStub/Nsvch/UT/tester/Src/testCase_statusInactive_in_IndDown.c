#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  1
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
 TC Name: TC_068

 TC Description: status Ind(Fr InActive) received in WaitForNSVCIndDownCnf state
**************************************************************************/
START_TEST (TC_068)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNStatusInd pssksFrNsvchNStatusInd;

  /*Receive Message Struct */
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
   pssksFrNsvchNStatusInd.sysHdr.src.prcr = PRCR_PP;
   pssksFrNsvchNStatusInd.sysHdr.src.entity = ENT_PSSTK_FRU;
   pssksFrNsvchNStatusInd.sysHdr.src.clsId = 1;
   pssksFrNsvchNStatusInd.sysHdr.src.rfu = 0;
   pssksFrNsvchNStatusInd.sysHdr.src.inst = 0;
   pssksFrNsvchNStatusInd.sysHdr.dest.prcr = PRCR_PP;
   pssksFrNsvchNStatusInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksFrNsvchNStatusInd.sysHdr.dest.clsId = 2;
   pssksFrNsvchNStatusInd.sysHdr.dest.rfu = 0;
   pssksFrNsvchNStatusInd.sysHdr.dest.inst = 0;
   pssksFrNsvchNStatusInd.sysHdr.msgType = PSSKS_FR_NSVCH_N_STATUS_IND;
   pssksFrNsvchNStatusInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksFrNsvchNStatusInd.sysHdr.priority = 0;
   pssksFrNsvchNStatusInd.reserved1 = 0;
   pssksFrNsvchNStatusInd.frChannel = 5;
   pssksFrNsvchNStatusInd.primCode = NS_OAM_STATUS_IND;
   pssksFrNsvchNStatusInd.receipt = 0;
   pssksFrNsvchNStatusInd.dataAttrib = 0;
   pssksFrNsvchNStatusInd.ssInfo = 0;
   pssksFrNsvchNStatusInd.connId = 5;
   pssksFrNsvchNStatusInd.dataLen = 0;
   pssksFrNsvchNStatusInd.refNum = 0;
   pssksFrNsvchNStatusInd.cause[0] = PCHAN_NOT_ACTIVE;
   pssksFrNsvchNStatusInd.dlci = 5;
   pssksFrNsvchNStatusInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNStatusInd,sizeof(PssksFrNsvchNStatusInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchCfgAlarmInd = *((OamsNsvchCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.src.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.msgType == OAMS_NSVCH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysAlarm.sysalarmId == ALARM_FRLINK_DISABLED) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysAlarm.key1 == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysAlarm.infoStrLen != 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysAlarm.infoStrLen is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[1] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[1] = 1;    /* 1 for pass*/

}
END_TEST


 
int RunTestSuite(Suite * s)
{
   int number_failed;
   SRunner *sr = srunner_create(s);
   //srunner_set_log(sr,log_fname);
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
       Suite *s = suite_create ("NSVCH");
       /* Core test case */
       TCase *tc_core = tcase_create ("Core");
       tcase_add_checked_fixture (tc_core, setup, teardown);
        system("clear");
        printf("\n0 : Previous Menu");
        printf("\n1. Run TC_068");
        printf("\nEnter your choice :  ");  
        scanf("%d",&iTCChoice); 
        if(iTCChoice > 0) 
        {
         
         if( 1 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_068);
           printf("\nRunning Test Case TC_068"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
        }
           }while(iTCChoice != 0);
      }
    if(2 == iChoice)
     {
      do{
       Suite *s = suite_create ("NSVCH");
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

