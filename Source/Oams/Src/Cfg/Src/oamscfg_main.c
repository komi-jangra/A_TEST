/***********************************File Header ***************************
   File Name        : oamcfg_main.c
Purpose          : This file contains the main function for the CFG Process.
Project          : BSC
Subsystem        : OAMS
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/
#include <oamscfg_includes.h>
#include <oamscfg_globals.h>

//#define MAX_MSGQ_BUF_SIZE 4096

SysHdr      *sysHdrPtr;
I_U32       *logLevelPtrG;
I_U8        consolePrintFlagG;

#if 0
void *threadfunc()
{
   struct sAisParam param;
   I_Void *cfgMsg = NULL;
   I_U32 cfgMsgSize;
   I_S8 retVal;
   LOG_PRINT(LOG_INFO,"Thread: Initializing with IPC FrameWork");
   LOG_PRINT(LOG_INFO,"Thread: THREAD Pid [%d]", getpid());  
//   gSrcId = ENT_OAMS_CFG;
/*   retVal = RegisterWithIpcFrmwrk(ENT_CFG_THREAD, (I_S8*)"CFG_THREAD");
   LOG_PRINT(LOG_INFO,"Return Value of IPC Registration: %d",retVal);
   if (retVal < ZERO)
      cfgPanic(CFG_REGD_IPC_FAIL);*/
   LOG_PRINT(LOG_INFO," Thread: Initialized with IPC Framework");


   while(1)
   {
      sleep(1);
      LOG_PRINT(LOG_INFO,"Thread: Child Thread waiting");
      cfgMsg = (void *)RecvMsg(ENT_CFG_THREAD, &cfgMsgSize); 
      if (cfgMsg == NULL)
      {
         /* LOG_PRINT(LOG_INFO," Message received is NULL");*/
         continue; 
      }
      else
         LOG_PRINT(LOG_INFO," Thread: Message recieved successfully of size = %d", cfgMsgSize); 
      param.messageId = ((sAisParam *)((I_U8 *)cfgMsg +sizeof(SysHdr)))->messageId;
      param.cardState = ((sAisParam *)((I_U8 *)cfgMsg +sizeof(SysHdr)))->cardState;
      bpmAisCallbackFunc(&param);
   }
  return NULL;
}
#endif

I_S32 main(I_S32 argc, I_S8 *argv[])
{
   gSrcId = ENT_OAMS_CFG;
   SysAddr     slfAddr;
   slfAddr.entity = ENT_OAMS_CFG;
   //InitLoggingUtility(slfAddr);
#if BPM_PRESENT == 0
   I_U32 rc; 
   pthread_t thread;
#endif
   LOG_PRINT(LOG_INFO,"CFG Process Started");
   /*1.   Once the Initialization is successful then CFG will send OAMS_CFG_OIL_GET_BCARD_INFO_REQ message to OIL for fetching B card data from platform.
      2.   CFG will send MGS_SMM_INIT_TRIGGER message to MGS-IF to trigger initialization of MGS. It will start "mgsGuardTimer" to guard the Driver Init Status message from MGS for TRAU and TSI.
      3.   It will change its state to "InitializeTRAU&TSI".*/
   gCurrentCardState = CARDSTATE_INIT;
   gNextCardState = CARDSTATE_INVALID;
   gCfgState = CFG_INIT;
   LOG_PRINT(LOG_INFO,"Initializing with Frame Work");
   cfgFrmwrkInit();
   //LOCK_MUTEX;

//   LOG_PRINT(INFO,"BPM_PRESENT IS  TRUE");  

   LOG_PRINT(LOG_INFO,"Initializing with BPM");
   cfgBpmInit();
   /*BSC-R2.5.5 Diagnostic Changes Start*/
   LOG_PRINT(DEBUG,"Initializing Diagnostic Library");
   cfgDiagInit();
   /*BSC-R2.5.5 Diagnostic Changes End*/
#if 0
   LOG_PRINT(LOG_CRITICAL,"BPM_PRESENT NOT TRUE");  
   LOG_PRINT(LOG_INFO,"CFG [%d]", getpid());  

   retVal = RegisterWithIpcFrmwrk(ENT_CFG_THREAD, (I_S8*)"CFG_THREAD");
   LOG_PRINT(LOG_INFO,"Return Value of IPC Registration: %d",retVal);
   if (retVal < ZERO)
      cfgPanic(CFG_REGD_IPC_FAIL);



   rc = pthread_create(&thread, NULL, threadfunc, (void *)NULL);

   cfgFrmwrkInit();
   LOG_PRINT(LOG_INFO,"CFG_THREAD [%d]", getpid());  
   if (rc)
   {
      LOG_PRINT(LOG_CRITICAL, "ERROR; return code from pthread_create() is [%d], UT Failed", rc);
   }
#endif
/*Temporary changes done for cloud 21 Dec 2015*/
	//gStackStatus = SS7_STACK_UP; //Commented for IP_BSC_STACK 18 July 2016 Gaurav Sinha Now SS7_UP/DOWN alarm expected from SCM
/*Temporary changes done for CLOUD 21 Dec 2015*/
/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
	gSwicthoverCloudTrigger=0;//resetting it to zero again	
/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
   LOG_PRINT(LOG_INFO," CFG: Entering into forever loop - for message waiting");
   for(;;)
   {
      /*   LOG_PRINT(LOG_INFO," Waiting for the message queue....");*/
      gCfgMsgBuf = NULL;
      gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRecvMsgSize); 
      if (gCfgMsgBuf == NULL)
      {
         /* LOG_PRINT(LOG_INFO," Message received is NULL");*/
         continue; 
      }
      else
         LOG_PRINT(LOG_INFO," Message recieved successfully of size = %d", gRecvMsgSize);
         //PRINT_HEX_DUMP(LOG_DEBUG, (I_U8*)gCfgMsgBuf, (I_U16)sizeof(SysHdr));
      /* Decode SysHdr to find out the message */

      LOG_PRINT(LOG_INFO,"------------------------------------------------------------------------------------------");   
      sysHdrPtr =  (SysHdr *) gCfgMsgBuf;
      LOG_PRINT(LOG_DEBUG,"MsgType=%d srcID=%d ",sysHdrPtr->msgType,sysHdrPtr->src.entity);
      switch( sysHdrPtr->src.entity)
      {
//         case ENT_OAMS_CFG:
//         case ENT_IPC_TEST1:
//         case ENT_OAMS_RM:
//            selfMsgHandler();
//            break;
         case ENT_OAM_CM:
            cmMsgHandler();
            break;
         case ENT_OAM_OIL:
            oilMsgHandler();         
            break;
         case ENT_CSAPP_GRHM:
            grhmMsgHandler();         
            break;
         case ENT_OAMS_TRXH:
            trxhMsgHandler();         
            break;
         case ENT_OAMS_CELLH:   
            cellhMsgHandler();         
            break;
         case ENT_IPC_TSMIF:
            mgsMsgHandler();   
            break;         
         case ENT_IPC_TMR:
            timerMsgHandler();
            break;
            /* Changes For CS2.2 : Starts */
         case ENT_OAMS_BICH:
            bichMsgHandler();
            break;   
            /* Changes For CS2.2 : Ends */
            /*CS3.0 Changes : Start */
         case ENT_OAMS_SWMH:   
            swmhMsgHandler();         
            break;
         case ENT_CSAPP_MRHM:
            mrhmMsgHandler();
            break;
            /*CS3.0 Changes : End */
         /* BSC CS4.0 HA Changes Starts*/
         case ENT_OAMS_RM:
            rmMsgHandler();
            break;
         /* BSC CS4.0 HA Changes Ends*/
         /* BSC CS4.0 CCU Changes : Start */
          case ENT_OAMS_CCUH:
            ccuMsgHandler();
            break;
          case ENT_CSAPP_CBSIF:
            cbsifMsgHandler();
            break;
          case ENT_CSAPP_CBSH:
            cfgAlarmHandler();
            break;
         /* BSC CS4.0 CCU Changes : End */

					/*BSC R2.0 changes starts*/
					case ENT_OAMS_DSPH :
				    dsphMsgHandler();	
					break;
					/*BSC R2.0 changes Ends*/
         /*Changes PCU R2.5 Aricent -- START*/
          case ENT_OAMS_GBH:
            gbhMsgHandler();
            break;
          case ENT_OAMS_PSCH:
            pschMsgHandler();
            break;
          case ENT_OAMS_PSSCM:
            psscmMsgHandler();
            break;
          case ENT_PSSKS_FRU:
            frMsgHandler();
            break;
         /*Changes PCU R2.5 Aricent -- END*/
    
         /*HA changes starts*/
         case ENT_OAMS_CFG:
            cpCpifMsgHandler();
            break;  
         /*HA changes ends*/

         case ENT_OAM_PDD :
            pddMsgHandler(); 
            break;

         case ENT_OAM_PDC:
            pdcMsgHandler();

         default:
            break;
      }
      DalocMsgBuf((I_Void *)gCfgMsgBuf); /* Free the received buffer */
      /*if(gIsListCreated == TRUE)
      {
         traverseAbisList();
      }*/
   //      LOCK_MUTEX;
   }
}


