/*se ts=2************************************File Header*****
File Name      :    ToFromTRXH.c
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
#include<sysxxx_datastruct.h>
#include<sysxxx_msgstruct.h>
#include<syscmn_hashdefs.h>
#include<syscmn_datastruct.h>
#include<ipcfrm_syslog.h>
#include<ipcfrm_msgqueue.h>
#include<ipcfrm_extern.h>
#include<ipcinst_dbstruct.h>
#include<ipcinst_extern.h>
#include <dbsxxx_commondefs.h>
#include<csappxxx_common_datastruct.h>
#include<msg_struct.h>
#include<oamxxx_datastruct.h>
#include<oamxxx_hashdefs.h>
#include<oamsxxx_typedef.h>
#include<oamsxxx_hashdef.h>
#include<oamxxx_msgstruct.h>
#include<oams_msgstruct.h>
#include<oamsxxx_msgstruct.h>

//#include<sysxxx_include.h>
//#include<oams_include.h>
//#include<oamscellh_include.h>

I_PVoid Build_OamsTrxhBichOperStateChangeMsg(I_U32 bicId, I_U32 trxId, I_U32 oprState, I_S32 *size);
I_PVoid displayLockInd(I_PVoid rcvPtr);
I_PVoid displayUnLockInd(I_PVoid rcvPtr);
I_PVoid displayLapdDiscInd(I_PVoid rcvPtr);

void ReceiveData();

I_U16 srcinstG;
I_U16 CallRef;

main()
{
I_S32 count=0,size=0,i=0;
I_S32 srcId,dstId,interval;
I_U32 ch=0 ;
I_U8 tei;
I_SL32 priority;
I_S8 buffer[100];
I_U32 bicId, trxId;
I_PVoid bufferPtr;
I_U32 oprState;

int choice ;

srcId = (int)ENT_OAMS_TRXH ;

if(RegisterWithIpcFrmwrk((int)ENT_OAMS_TRXH, (I_S8 *)"ENT_OAMS_TRXH")!=0)
{
	fprintf(stderr,"Counld not register with framework\n");
}


while(1)
{
fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------- \n");
fprintf(stderr, "-------->> 1.To Send OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND \n");
fprintf(stderr, "<<-------- 2. To_Receive data \n");

scanf("%d", &choice);

switch(choice)
{

	 case 1 :
		fprintf(stderr, "-------->>Enter BicId, for which OPER_STATE_CHANGE_IND_MSG is  - ");
                scanf("%d",&bicId);
		fprintf(stderr, "-------->>Enter TrxId, for which OPER_STATE_CHANGE_IND_MSG is  - ");
                scanf("%d",&trxId);
		fprintf(stderr, "-------->>Enter OPR State, for which OPER_STATE_CHANGE_IND_MSG is  - ");
                scanf("%d",&oprState);
                bufferPtr = Build_OamsTrxhBichOperStateChangeMsg(bicId, trxId, oprState, &size);
                ch = 1 ;
                break;
	 case 2 :
		ReceiveData() ;
                ch = 0 ;
		break ;		
	
	default :
		fprintf(stderr, "\n INVALID CHOICE \n");
		continue ;

}// switch choice

	if(ch==1)
        {
            if (bufferPtr != NULL && size > 0)
	    {
		if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
		{
			exit(0);
		}
	    }
	}

}// while 1
	
}// main

void ReceiveData()
{
	I_PVoid		rcvPtr ;
	I_S32 		msgSize,size ;
	I_U16		msgType ;
	I_U8		tei;
	I_SL32    	priority ;
	I_PVoid 	bufferPtr ;
        I_U8            entId; 
	I_U32           ch;
	while(1)
	{
		rcvPtr = (I_PVoid)RecvMsg((int)(ENT_OAMS_TRXH), &msgSize);
		fprintf(stderr,"No of Bytes received = [%d]\n",msgSize);

		if(msgSize <= 0)
		{
			continue ;
		}
		else
		{
			break ;
		}
	}
	if(rcvPtr == NULL)
	{
		fprintf(stderr,"Could not read from Framework\n") ;
		return ;
	}
	
	msgType = ((SysHdr *)rcvPtr)->msgType ;
        entId = ((SysHdr *) rcvPtr)->dest.entity ;
        fprintf(stderr,"Received msg with msgType [%d]\n",msgType) ;
        fprintf(stderr,"Received msg with EntityId [%d]\n",entId) ;


	switch (msgType)
	{

                case OAMS_BICH_TRXH_LOCK_IND:
                        fprintf(stderr,"OAMS_BICH_TRXH_LOCK_IND received from BICH\n") ;
                        displayLockInd(rcvPtr);

                        fprintf(stderr, "-------->>Do U want to Send \
                               OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND ( (YES=1/NO=2)  ");
                        scanf("%d",&ch);
                        if ( ch == 1 )
                           bufferPtr = Build_OamsTrxhBichOperStateChangeMsg(((OamsBichTrxhLockInd *)rcvPtr)->bicId, ((OamsBichTrxhLockInd *)rcvPtr)->ptrxId, DISABLED, &size);

                        break ;
                case OAMS_BICH_TRXH_UNLOCK_IND:
                        fprintf(stderr,"OAMS_BICH_TRXH_UNLOCK_IND received from BICH\n") ;
                        displayUnLockInd(rcvPtr);
                        break ;
                case OAMS_BICH_TRXH_LAPD_DISCONNECT_IND:
			displayLapdDiscInd(rcvPtr);
                        fprintf(stderr,"OAMS_BICH_TRXH_LAPD_DISCONNECT_IND received from BICH\n") ;
                        break ;
		default:
			fprintf(stderr,"Invalid message received from SIM\n") ;

	}
        if(ch==1)
        {
            if (bufferPtr != NULL && size > 0)
	    {
		if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
		{
			exit(0);
		}
	    }
	}

	 if (rcvPtr != NULL)
          DalocMsgBuf(rcvPtr) ;
}

I_PVoid displayLockInd(I_PVoid rcvPtr)
{
	OamsBichTrxhLockInd *msgPtr;
	msgPtr =(OamsBichTrxhLockInd *)(rcvPtr);
	fprintf(stderr, "BicId=%d\n ",msgPtr->bicId);
	fprintf(stderr, "TrxId=%d\n ",msgPtr->ptrxId);
}
I_PVoid displayUnLockInd(I_PVoid rcvPtr)
{
	OamsBichTrxhUnlockInd *msgPtr;
	msgPtr =(OamsBichTrxhUnlockInd *)(rcvPtr);
	fprintf(stderr, "BicId=%d\n ",msgPtr->bicId);
	fprintf(stderr, "TrxId=%d\n ",msgPtr->ptrxId);
}
I_PVoid displayLapdDiscInd(I_PVoid rcvPtr)
{
	OamsBichTrxhLapdDiscInd *msgPtr;
	msgPtr =(OamsBichTrxhLapdDiscInd *)(rcvPtr);
	fprintf(stderr, "BicId=%d\n ",msgPtr->bicId);
	fprintf(stderr, "TrxId=%d\n ",msgPtr->ptrxId);
}

I_PVoid Build_OamsTrxhBichOperStateChangeMsg(I_U32 bicId, I_U32 trxId, I_U32 oprState, I_S32 *size)
{
        OamsTrxhBichOperStateChangeInd *ptr;

        I_U16 len=0;

        len = sizeof(OamsTrxhBichOperStateChangeInd);
        if((ptr = (OamsTrxhBichOperStateChangeInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->bicId   = bicId ;
        ptr->ptrxId   = trxId ;
        ptr->operState   =  oprState;

	*size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND, 1,PRCR_CP, ENT_OAMS_TRXH ,0,PRCR_CP, ENT_OAMS_BICH,0);


        fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_OamsTrxhBichOperStateChangeInd Complete


