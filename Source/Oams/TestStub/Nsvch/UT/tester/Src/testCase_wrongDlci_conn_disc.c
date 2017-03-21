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
 TC Name: TC_069

 TC Description: Conn Ind received with wrong dlci in unlockedDisabled
**************************************************************************/
START_TEST (TC_069)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNConnInd pssksFrNsvchNConnInd;

  /*Receive Message Struct */
   pssksFrNsvchNConnInd.sysHdr.src.prcr = PRCR_PP;
   pssksFrNsvchNConnInd.sysHdr.src.entity = ENT_PSSTK_FRU;
   pssksFrNsvchNConnInd.sysHdr.src.clsId = 1;
   pssksFrNsvchNConnInd.sysHdr.src.rfu = 0;
   pssksFrNsvchNConnInd.sysHdr.src.inst = 0;
   pssksFrNsvchNConnInd.sysHdr.dest.prcr = PRCR_PP;
   pssksFrNsvchNConnInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksFrNsvchNConnInd.sysHdr.dest.clsId = 2;
   pssksFrNsvchNConnInd.sysHdr.dest.rfu = 0;
   pssksFrNsvchNConnInd.sysHdr.dest.inst = 0;
   pssksFrNsvchNConnInd.sysHdr.msgType = PSSKS_FR_NSVCH_N_CONN_IND;
   pssksFrNsvchNConnInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksFrNsvchNConnInd.sysHdr.priority = 0;
   pssksFrNsvchNConnInd.reserved1 = 0;
   pssksFrNsvchNConnInd.frChannel = 5;
   pssksFrNsvchNConnInd.primCode = N_CONN_IN;
   pssksFrNsvchNConnInd.receipt = 0;
   pssksFrNsvchNConnInd.dataAttrib = 0;
   pssksFrNsvchNConnInd.ssInfo = 0;
   pssksFrNsvchNConnInd.connId = 5;
   pssksFrNsvchNConnInd.dataLen = 0;
   pssksFrNsvchNConnInd.refNum = 0;
   pssksFrNsvchNConnInd.cause[2] = 0;
   pssksFrNsvchNConnInd.dlci = 9;
   pssksFrNsvchNConnInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNConnInd,sizeof(PssksFrNsvchNConnInd));

   if(0 == flag)
      test_result[1] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[1] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_077

 TC Description: Disc Ind received with wrong dlci in unlockedDisabled
**************************************************************************/
START_TEST (TC_077)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNDiscInd pssksFrNsvchNDiscInd;

  /*Receive Message Struct */
   pssksFrNsvchNDiscInd.sysHdr.src.prcr = PRCR_PP;
   pssksFrNsvchNDiscInd.sysHdr.src.entity = ENT_PSSTK_FRU;
   pssksFrNsvchNDiscInd.sysHdr.src.clsId = 1;
   pssksFrNsvchNDiscInd.sysHdr.src.rfu = 0;
   pssksFrNsvchNDiscInd.sysHdr.src.inst = 0;
   pssksFrNsvchNDiscInd.sysHdr.dest.prcr = PRCR_PP;
   pssksFrNsvchNDiscInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksFrNsvchNDiscInd.sysHdr.dest.clsId = 2;
   pssksFrNsvchNDiscInd.sysHdr.dest.rfu = 0;
   pssksFrNsvchNDiscInd.sysHdr.dest.inst = 0;
   pssksFrNsvchNDiscInd.sysHdr.msgType = PSSKS_FR_NSVCH_N_DISC_IND;
   pssksFrNsvchNDiscInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksFrNsvchNDiscInd.sysHdr.priority = 0;
   pssksFrNsvchNDiscInd.reserved1 = 0;
   pssksFrNsvchNDiscInd.frChannel = 5;
   pssksFrNsvchNDiscInd.primCode = N_DISC_IN;
   pssksFrNsvchNDiscInd.receipt = 0;
   pssksFrNsvchNDiscInd.dataAttrib = 0;
   pssksFrNsvchNDiscInd.ssInfo = 0;
   pssksFrNsvchNDiscInd.connId = 5;
   pssksFrNsvchNDiscInd.dataLen = 0;
   pssksFrNsvchNDiscInd.refNum = 0;
   pssksFrNsvchNDiscInd.cause[2] = 0;
   pssksFrNsvchNDiscInd.dlci = 9;
   pssksFrNsvchNDiscInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNDiscInd,sizeof(PssksFrNsvchNDiscInd));

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
        printf("\n1. Run TC_069");
        printf("\n2. Run TC_077");
        printf("\nEnter your choice :  ");  
        scanf("%d",&iTCChoice); 
        if(iTCChoice > 0) 
        {
         
         if( 1 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_069);
           printf("\nRunning Test Case TC_069"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 2 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_077);
           printf("\nRunning Test Case TC_077"); 
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

