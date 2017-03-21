
#include<stdlib.h>
#include<pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#include "sysxxx_typedef.h"
#include "sysxxx_hashdefs.h"
#include "sysxxx_msgstruct.h"
#include "sysxxx_proc.h"
#include "sysinst_hashdefs.h"
#include "sysxxx_macro.h"

#include "ipcfrm_extern.h"
#include "ipcfrm_msgqueue.h"
#include "ipcfrm_msgdef.h"
#include "ipcfrm_syslog.h"
#include "sysxxx_msgopcode.h"
#include "bpmxxx_commonDef.h"
#include "bpmxxx_OAM_commonDef.h"

#define MSGSIZE 50


typedef struct {
           long    type;
              unsigned char payload[MSGSIZE];
}message_buf;

void *stubThr(void *args);
char gSelfEntityId;
char gCallBackFunc[50];
char func[100];
void (*gFuncPtr)(struct sAisParam*);
int msgflg = 0777;
int gMsqId;

//extern mrhmBpmCallbackFunc(struct sAisParam*);
//extern void selfCallBackFunc(struct sAisParam*);

/*void mrhmBpmCallbackFunc1(struct sAisParam* param)
{
	fprintf(stderr, "function called with crdstate:: %d", param->cardState );
	mrhmBpmCallbackFunc(param);	
}*/
/*void (*funcPtr[1])() =
 {
	mrhmBpmCallbackFunc
 };*/

	






void bpmGetComponentReg (char selfEntityId, void (*funcPtr)(struct sAisParam*))
{
	//LOG_PRINT(INFO, "Registring with bpm..");
	pthread_t myThr; 
	key_t key;
	gSelfEntityId = selfEntityId;
	gFuncPtr  = funcPtr;
	printf("Registring with BPM for module having entityID :: %d..................\n", gSelfEntityId);
	
	if (pthread_create(&myThr, NULL, stubThr, NULL) < 0)
	{
		printf(" thread creation fail. Bye.\n");
   	exit(1);
	}
	key = gSelfEntityId;
   if ((gMsqId = msgget(key, msgflg)) < 0)
   {
	   printf(" msgget failed for entity :: %d", key);
      exit (-1);
   }
	
/*	switch(gSelfEntityId)
	{
		case ENT_CSAPP_MRHM_STUB :
			printf("Mrhm ..................\n");
			strcpy(gCallBackFunc,"mrhmBpmCallbackFunc"); 
			sprintf(func, "%s(param)",gCallBackFunc );
			break;
		case ENT_CSAPP_GRHM_STUB :
			//strcpy(gCallBackFunc,"grhmBpmCallbackFunc"); 
			break;
	}*/
}


void* stubThr(void* Args)
{
	char msgType;
	int rcvRet;
	message_buf rcvMsg;
	struct sAisParam *param;
	 I_S32   messageSize;
	I_Void* rcvPtr;
	printf("thread created for entityID :: %d\n", gSelfEntityId);
	I_S32 len = sizeof(param);
	fprintf(stderr,"Length of the struct is :: %d", sizeof(struct sAisParam));
/*	if ((RegisterWithIpcFrmwrk(gSelfEntityId,"STUB")) < ZERO)
  	{
   	//LOG_PRINT(CRITICAL,"Unable to Register itself with IPC FrameWork");
     	exit(ZERO);
  	}*/
	fprintf(stderr,"Opened message queue with ID  %x", gMsqId);

	while(1)
	{
	   usleep(0); //port to be checked TAU_OPR_RX_PORT - 1
   	rcvRet = msgrcv(gMsqId, &rcvMsg, sizeof(rcvMsg), 1, IPC_NOWAIT);
   	if (rcvRet < 0)
   	{
           if (errno == ENOMSG) //not a problem. just don't do anything
           {
           }
           else
           {
            printf ("msgsnd error: %s",
            strerror(errno));
            //exit(-1);
           }
   }
   else // if rcvret > 0, we get a msg.
   {
      msgType = rcvMsg.payload[0];
      switch(msgType)
		{
			case BPM_SELFCARD_STATE_CHANGE :
				fprintf(stderr,"Message received");
				param = (struct sAisParam*)malloc(sizeof(struct sAisParam));
				fprintf(stderr, "Allocating address :: %x\n", param);
				memcpy (param, &(rcvMsg.payload[1]), sizeof(struct sAisParam));
			   (*gFuncPtr)(param);
				fprintf(stderr, "Returning from call-back and deallocating pointer\n");
				fprintf(stderr, "De-allocating address :: %x\n", param);
				 free (param);
				 break;
			default :
				fprintf(stderr, "Only selfcard state change messages expected\n");

			   //DalocMsgBuf((I_Void *)rcvPtr) ;

 		} 
	}
	}
}



