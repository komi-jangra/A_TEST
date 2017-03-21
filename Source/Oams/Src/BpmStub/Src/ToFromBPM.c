/*se ts=2************************************File Header*****
File Name      :    ToFromABIHM.c
Purpose        :		 
Project        :    GSM
Subsystem      :    IPC	
Author         :    
CSCI id        :
Version        :    V0.1
*************************************************************/

/*******************************************Change History***
S.No.   Release        Patch        Author        Description
1.      Rel0.0         None         xxxxx         Creation
*************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<sysxxx_macro.h>
#include<sysxxx_hashdefs.h>
#include<sysxxx_typedef.h>
#include<sysxxx_msgopcode.h>
#include<sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include<sysinst_hashdefs.h>
#include<sysxxx_msgstruct.h>
#include<ipcfrm_syslog.h>
#include<ipcfrm_msgqueue.h>
#include<ipcfrm_extern.h>
#include<ipcinst_dbstruct.h>
#include<ipcinst_extern.h>
#include <dbsxxx_commondefs.h>
#include<csappxxx_common_datastruct.h>
#include<oamxxx_hashdefs.h>
#include<oamsxxx_typedef.h>
#include<oamsxxx_hashdef.h>
#include<bpmxxx_commonDef.h>
#include<bpmxxx_OAM_commonDef.h>
#include<syscmn_hashdefs.h>
#include<sysxxx_datastruct.h>
#include<syscmn_datastruct.h>
#include<msg_struct.h>
#include<oamxxx_msgstruct.h>
#include<oamsxxx_msgstruct.h>
#include<oams_msgstruct.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>



#define MSGSIZE 50
//#include<sysxxx_include.h>
//#include<oams_include.h>
//#include<oamscellh_include.h>
I_Void sendSelfCardStateChange();

I_U16 srcinstG;
I_U16 CallRef;

int gMsgqId[COUNT_STUB_ENTITIES];

typedef struct {
		     long    type;
			     unsigned char payload[MSGSIZE];
}message_buf;



main()
{
I_S32 srcId;
I_U32 choice;
int ctr;
srcId = (int)ENT_IPC_TEST1 ;
key_t key;
int msgflg = 0777 | IPC_CREAT;


	for(ctr=1; ctr <=COUNT_STUB_ENTITIES; ctr++) 
	{
		// message queues to be opened for all the stubs
		
		fprintf(stderr,"Openeing message queue\n");
		key = BASE_STUB_ENTITIES+ctr;
		if ((gMsgqId[ctr-1] = msgget(key, msgflg)) < 0)
   	{
			//LOG_PRINT(INFO," msgget failed for entity :: %d", key);
			fprintf(stderr," msgget failed for entity :: %d\n", key);

       	//exit (-1);
   	}
			fprintf(stderr," msgget success for entity :: %d\n", key);
	}	
/*	if(RegisterWithIpcFrmwrk((int)ENT_IPC_TEST1, (I_S8 *)"ENT_TEST_PMIF")!=0)
	{
		fprintf(stderr,"Counld not register with framework\n");
	}*/

while(1)
{

fprintf(stderr, "\n---------------- DO you want to send BPM_SELFCARD_STATE_CHANGE message-------------- \n");
fprintf(stderr, "-------->> 1.YES \n");
fprintf(stderr, "-------->> 2.NO \n");
scanf("%d", &choice);

switch(choice)
{

	 case 1 :
                sendSelfCardStateChange();
                break;
	 case 2 :
                continue ;
	default :
		fprintf(stderr, "\n INVALID CHOICE \n");
		continue ;

}// switch choice

}// while 1
}

I_Void sendSelfCardStateChange()
{
	message_buf qmsg;
   I_U32 choice;
	int i;
   //I_S32 len = sizeof(SysHdr) + sizeof(struct sAisParam);
   //I_PVoid *sendPtr ;
   struct sAisParam *param;
	//printf("The len of sysHdr is :: %d, len of param is :: %d and len is :: %d\n", sizeof(SysHdr),sizeof(struct sAisParam),len);

	fprintf(stderr, "\n---------------- ENTER UR CHOICE for SELF_CARD_STATE-------------- \n");
	fprintf(stderr, "-------->> 1.CARDSTATE_IN_SERVICE \n");
	fprintf(stderr, "-------->> 2.CARDSTATE_STANDBY\n");
	fprintf(stderr, "-------->> 3.CARDSTATE_ACTIVE_IN_PROGRESS \n");
	fprintf(stderr, "-------->> 4.CARDSTATE_ACTIVE \n");
	fprintf(stderr, "-------->> 5.CARDSTATE_RECOVERY \n");
	scanf("%d", &choice);
	fflush(stdin);
	for(i=1; i <=COUNT_STUB_ENTITIES; i++)
	{
		param = (sAisParam*)malloc(sizeof(sAisParam));
   	/*if((sendPtr = AlocMsgBuf(len) ) == (I_Void *)NULL) 
   	{
      	fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      	exit(0);                      
   	}*/
     fprintf(stderr,"ADDRESS ALLOCATED FOR THIS MESSAGE IS :: %x\n", param);

  // FILL_SYS_HDR(((SysHdr*)sendPtr),BPM_SELFCARD_STATE_CHANGE, 1,PRCR_CP, ENT_IPC_PMIF ,0,PRCR_CP, ENT_CSAPP_MRHM_STUB,0);
 //  	FILL_SYS_HDR(((SysHdr*)sendPtr),BPM_SELFCARD_STATE_CHANGE, 1,PRCR_CP, ENT_IPC_TEST1 ,0,PRCR_CP, BASE_STUB_ENTITIES+i,0);
  // 	param = (struct sAisParam *)((I_U8*)sendPtr+sizeof(SysHdr));
   	memset(param,1, sizeof(struct sAisParam));

  
   	param->messageId = BPM_SELFCARD_STATE_CHANGE;
		switch(choice)
		{
   		case 1:param->cardState = CARDSTATE_IN_SERVICE;
        	 break;
   		case 2:param->cardState = CARDSTATE_STANDBY;
        	 break;
   		case 3:param->cardState = CARDSTATE_ACTIVE_IN_PROGRESS;
         	break;
   		case 4:param->cardState = CARDSTATE_ACTIVE;
         	break;
   		case 5:param->cardState = CARDSTATE_RECOVERY;
        	 break;
   		case 6:printf(" Entered Default case");
         	break;
		}
      qmsg.type = 1;//TAU_MSGQ_TX_PORT;
      memset (qmsg.payload, 0, MSGSIZE);
      qmsg.payload[0] = BPM_SELFCARD_STATE_CHANGE;
      printf ("sending state change msg...\n");
      memcpy (&(qmsg.payload[1]), param, sizeof(struct sAisParam));
      if (msgsnd(gMsgqId[i-1], &qmsg, sizeof(qmsg), IPC_NOWAIT) < 0)
      {
	       perror("msgsnd");
          exit(1);
      }
		free(param);	
   	/*if(SendMsg(sendPtr, 1, len) == SND_FAIL)
   	{
      	LOG_PRINT(INFO,"SendMsg failed, EXITING........");
      	exit(0);
   	}*/
	}
}
