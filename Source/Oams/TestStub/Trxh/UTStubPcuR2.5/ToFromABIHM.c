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
#include<sysxxx_prcr.h>
#include<sysxxx_datastruct.h>
#include<syscmn_hashdefs.h>
#include<syscmn_datastruct.h>
#include<sysinst_hashdefs.h>
#include<sysxxx_msgstruct.h>
#include<bpmxxx_OAM_commonDef.h>
#include<msg_struct.h>
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
#include<oamxxx_datastruct.h>
#include<oamxxx_msgstruct.h>
#include<oams_msgstruct.h>
#include<oamsxxx_msgstruct.h>

//#include<sysxxx_include.h>
//#include<oams_include.h>
//#include<oamscellh_include.h>

I_PVoid Build_CsappAbihmTrxhSetBtsAttrAckMsg(I_U8, I_S32 *);
I_PVoid Build_CsappAbihmTrxhSetBtsAttrNackMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhSetChanAttrAckMsg(I_U8, I_S32 *) ;
I_PVoid Build_CsappAbihmTrxhSetChanAttrNackMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhStateChangeEventReportMsg(I_U8,I_U32, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhStateChangeEventReportMsg1(I_U8,I_U32, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhFailureEventReportMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhOpStartAckMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhOpStopAckMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhTrxHelloMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhLapdLinkUpMsg(I_U8,I_U32, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhLinkEstabRespMsg(I_U8, I_S32 *) ;
I_PVoid Build_CsappAbihmTrxhLapdLinkDownMsg(I_U8,I_U32, I_S32 *)  ;

/* Added for R2.2 */
I_PVoid Build_CsappAbihmTrxhTmHelloMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhTmRestartAckMsg(I_U8, I_S32 *)  ;


/* Added for PCU Rel2.5 */
I_PVoid Build_CsappAbihmTrxhSetTrxPsAttrAckMsg(I_U8, I_S32 *);
I_PVoid Build_CsappAbihmTrxhSetTrxPsAttrNackMsg(I_U8, I_S32 *);
void ReceiveData();

I_U16 srcinstG;
I_U16 CallRef;
static I_U32 sacchCounter,bcchCounter;

main()
{
I_S32 count=0,size=0,i=0;
I_S32 srcId,dstId,interval;
I_U32 ch=0 ;
I_U8 tei;
I_U32 sapi;
I_U32 state;
I_SL32 priority;
I_U8 receiveMsg;
//PRIVATE struct timeval timeout = {1,0};
I_S8 buffer[100];

I_PVoid bufferPtr;

int choice ;

srcId = (int)ENT_CSAPP_ABIHM ;

if(RegisterWithIpcFrmwrk((int)ENT_CSAPP_ABIHM, (I_S8 *)"ENT_CSAPP_ABIHM")!=0)
{
	fprintf(stderr,"Counld not register with framework\n");
}


while(1)
{
fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------- \n");
fprintf(stderr, "-------->> 1.To Send CSAPP_ABIHM_TRXH_SET_BTS_ATTR_ACK \n");
fprintf(stderr, "-------->> 2.To Send CSAPP_ABIHM_TRXH_SET_BTS_ATTR_NACK \n");
fprintf(stderr, "-------->> 3.To Send CSAPP_ABIHM_TRXH_SET_CHAN_ATTR_ACK \n");
fprintf(stderr, "-------->> 4.To Send CSAPP_ABIHM_TRXH_SET_CHAN_ATTR_NACK \n");
fprintf(stderr, "-------->> 5.To Send CSAPP_ABIHM_TRXH_STATE_CHANGE_EVENT_REPORT \n");
fprintf(stderr, "-------->> 6.To Send OAMS_ABIHM_TRXH_FAILURE_EVENT_REPORT \n");
/*fprintf(stderr, "-------->> 7.To Send CSAPP_ABIHM_TRXH_TRX_HELLO \n");*/
fprintf(stderr, "-------->> 8.To Send CSAPP_ABIHM_TRXH_LAPD_LINK_UP \n");
/*fprintf(stderr, "-------->> 9.To Send CSAPP_ABIHM_TRXH_LAPD_LINK_DOWN \n");*/
fprintf(stderr, "-------->> 10.To Send CSAPP_ABIHM_TRXH_OP_STOP_ACK \n");
fprintf(stderr, "-------->> 11.To Send CSAPP_ABIHM_TRXH_OP_START_ACK \n");
fprintf(stderr, "-------->> 12.To Send CSAPP_ABIHM_TRXH_TM_HELLO \n");
fprintf(stderr, "-------->> 13.To Send CSAPP_ABIHM_TRXH_TM_RESTART_ACK \n");
fprintf(stderr, "-------->> 14.To Send CSAPP_ABIHM_TRXH_SET_TRX_PS_ATTR_ACK \n");
fprintf(stderr, "-------->> 15.To Send CSAPP_ABIHM_TRXH_SET_TRX_PS_ATTR_NACK \n");
fprintf(stderr, "<<-------- 16. To_Receive data \n");

scanf("%d", &choice);

switch(choice)
{

	 case 1 :
		fprintf(stderr, "-------->>Enter TEI, for which this SET_BTS_ATTR_ACK_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhSetBtsAttrAckMsg(tei, &size);
                ch = 1 ;
                break;
	 case 2 :
		fprintf(stderr, "-------->>Enter TEI, for which this SET_BTS_ATTR_NACK_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhSetBtsAttrNackMsg(tei, &size);
                ch = 1 ;
                break;


	 case 3 :
		fprintf(stderr, "-------->>Enter TEI, for which this SET_CHAN_ATTR_ACK_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhSetChanAttrAckMsg(tei, &size);
                ch = 1 ;
                break;
	 case 4 :
		fprintf(stderr, "-------->>Enter TEI, for which this SET_CHAN_ATTR_NACK_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhSetChanAttrNackMsg(tei, &size);
                ch = 1 ;
                break;

	 case 5 :
		fprintf(stderr, "-------->>Enter TEI, for which this STATE_CHANGE_EVENT_REPORT_MSG is  - ");
                scanf("%d",&tei);
		fprintf(stderr, "-------->>Enter OprState, for which this STATE_CHANGE_EVENT_REPORT_MSG is(Enable/Disable- 2:1)  - ");
                scanf("%d",&state);
		if(state==1)
                    bufferPtr = Build_CsappAbihmTrxhStateChangeEventReportMsg(tei,1, &size);
                else
                    bufferPtr = Build_CsappAbihmTrxhStateChangeEventReportMsg1(tei,2, &size);
		ch = 1 ;
                break;

	 case 6 :
		fprintf(stderr, "-------->>Enter TEI, for which this FAILURE_EVENT_REPORT_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhFailureEventReportMsg(tei, &size);
                ch = 1 ;
                break;

	 case 7 :
		fprintf(stderr, "-------->>Enter TEI, for which this TRX_HELLO_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhTrxHelloMsg(tei, &size);
                ch = 1 ;
                break;

	 case 8 :
		fprintf(stderr, "-------->>Enter TEI, for which this LAPD_LINKUP_MSG is  - ");
                scanf("%d",&tei);
		fprintf(stderr, "-------->>Enter SAPI, for which this LAPD_LINKUP_MSG is  - ");
                scanf("%d",&sapi);
                bufferPtr = Build_CsappAbihmTrxhLapdLinkUpMsg(tei,sapi, &size);
                ch = 1 ;
                break;
	 case 9 :
		fprintf(stderr, "-------->>Enter TEI, for which this LAPD_LINK_DOWN_MSG is  - ");
                scanf("%d",&tei);
                fflush(stdin);
		fprintf(stderr, "-------->>Enter SAPI, for which this LAPD_LINK_DOWN_MSG is  - ");
                scanf("%d",&sapi);
		printf("\n----Value of Tei and Sapi is - %d %d\n", tei,sapi); 

                bufferPtr = Build_CsappAbihmTrxhLapdLinkDownMsg(tei,sapi, &size);
                ch = 1 ;
                break;

	 case 10 :
		fprintf(stderr, "-------->>Enter TEI, for which this OP_STOP_ACK_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhOpStopAckMsg(tei, &size);
                ch = 1 ;
                break;
	 
	 case 11 :
		fprintf(stderr, "-------->>Enter TEI, for which this OP_START_ACK_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhOpStartAckMsg(tei, &size);
                ch = 1 ;
                break;

	 case 12 :
		fprintf(stderr, "-------->>Enter TEI, for which this TM_HELLO_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhTmHelloMsg(tei, &size);
                receiveMsg = 1;
                ch = 1 ;
                break;

	 case 13 :
		fprintf(stderr, "-------->>Enter TEI, for which this TM_RESET_ACK_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhTmRestartAckMsg(tei, &size);
                ch = 1 ;
                break;

	 case 14 :
		fprintf(stderr, "-------->>Enter TEI, for which this SET_TRX_PS_ATTR_ACK is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhSetTrxPsAttrAckMsg(tei, &size);
                ch = 1 ;
                break;

	 case 15 :
		fprintf(stderr, "-------->>Enter TEI, for which this SET_TRX_PS_ATTR_NACK is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhSetTrxPsAttrNackMsg(tei, &size);
                ch = 1 ;
                break;

	 case 16 :
		ReceiveData() ;
                ch = 0 ;
		break ;		
	
	default :
		fprintf(stderr, "\n INVALID CHOICE \n");

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
   if(receiveMsg == 1)
   {
      ReceiveData();
   }

}// while 1
	
}// main

void ReceiveData()
{
	I_PVoid		rcvPtr ;
	I_S32 		msgSize,size ;
	I_U16		msgType ;
	I_U8		tei;
	I_U8		sapi;
	I_SL32    	priority ;
	I_PVoid 	bufferPtr ;

	while(1)
	{
		rcvPtr = (I_PVoid)RecvMsg((int)(ENT_CSAPP_ABIHM), &msgSize);
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

	fprintf(stderr,"msgType is  - %d\n",msgType);
	switch (msgType)
	{
		case OAMS_CELLH_ABIHM_BCCH_INFO:
			fprintf(stderr,"BCCH_INFO received from CELLH\n") ;
			bcchCounter++;
			fprintf(stderr,"BcchCounter Value is - %d\n",bcchCounter);
			break ;

		case OAMS_CELLH_ABIHM_SACCH_FILL:
			fprintf(stderr,"SACCH_FILL received from CELLH\n") ;		
			sacchCounter++;
			fprintf(stderr,"SacchCounter Value is - %d\n",sacchCounter);
			break ;

		case OAMS_TRXH_ABIHM_SET_BTS_ATTR_REQ:
			fprintf(stderr,"SET_BTS_ATTR_REQ received from TRXH\n") ;
			tei = ((OamsTrxhAbihmSetBtsAttrReq *)rcvPtr)->tei;
			bufferPtr = Build_CsappAbihmTrxhSetBtsAttrAckMsg( tei, &size);
			if (bufferPtr != NULL && size > 0)
			{
			    if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
					{
			                exit(0);
					}
			}
			break ;

		case OAMS_TRXH_ABIHM_SET_TRX_PS_ATTR:
			fprintf(stderr,"SET_PS_ATTR_REQ received from TRXH\n") ;
			tei = ((OamsTrxhAbihmSetPsAttrReq *)rcvPtr)->tei;
			bufferPtr = Build_CsappAbihmTrxhSetTrxPsAttrAckMsg(tei,&size);
			if (bufferPtr != NULL && size > 0)
			{
			    if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
					{
			                exit(0);
					}
			}
			ReceiveData() ;
			break ;

		case OAMS_TRXH_ABIHM_SET_CHAN_ATTR_REQ:
			fprintf(stderr,"SET_CHAN_ATTR_REQ received from TRXH\n") ;
			tei = ((OamsTrxhAbihmSetChanAttrReq *)rcvPtr)->tei;
			bufferPtr = Build_CsappAbihmTrxhSetChanAttrAckMsg( tei, &size);
			if (bufferPtr != NULL && size > 0)
			{
			     if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
			     {
			     exit(0);
			     }
			}
			ReceiveData() ;
			break ;

		case OAMS_TRXH_ABIHM_OP_START_REQ:
			fprintf(stderr,"OP_START_REQ received from TRXH\n") ;

			/*Send Op_Start_Ack Msg*/
			tei = ((OamsTrxhAbihmOpStartReq *)rcvPtr)->tei;
			bufferPtr = Build_CsappAbihmTrxhOpStartAckMsg( tei, &size);
			if (bufferPtr != NULL && size > 0)
			{
			     if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
	  	     		{
	             		exit(0);
			     	}
			}
			/*Send State Change Event Report Msg*/
			bufferPtr = Build_CsappAbihmTrxhStateChangeEventReportMsg1(tei,2, &size);
			if (bufferPtr != NULL && size > 0)
                        {
                             if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
                                {
                                exit(0);
                                }
                        }
			break ;

		case OAMS_TRXH_ABIHM_OP_STOP_REQ:
			fprintf(stderr,"OP_STOP_REQ received from TRXH\n") ;
			 /*Send Op_Stop_Ack Msg*/
			tei = ((OamsTrxhAbihmOpStopReq *)rcvPtr)->tei;
			bufferPtr = Build_CsappAbihmTrxhOpStopAckMsg( tei, &size);
			if (bufferPtr != NULL && size > 0)
			{
			     if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
				 {
		                  exit(0);
			         }
			}

			/*Send State Change Event Report Msg*/
                        bufferPtr = Build_CsappAbihmTrxhStateChangeEventReportMsg(tei,1, &size);
                        if (bufferPtr != NULL && size > 0)
                        {
                             if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
                                {
                                exit(0);
                                }
			ReceiveData() ;
                        }
			break ;

		case OAMS_TRXH_ABIHM_LINK_ESTAB_REQ:
			fprintf(stderr,"LINK_ESTAB_REQ received from TRXH\n") ;

			/*Sending Ack of Link_Estab_Req signal*/
			tei = ((OamsTrxhAbihmLinkEstabReq *)rcvPtr)->tei;
			sapi = ((OamsTrxhAbihmLinkEstabReq *)rcvPtr)->sapi;
			bufferPtr = Build_CsappAbihmTrxhLapdLinkUpMsg(tei,sapi, &size);
                        LOG_PRINT(DEBUG,"Sending CSAPP_ABIHM_TRXH_LINK_ESTAB_RESP signal to TRXH");
			if (bufferPtr != NULL && size > 0)
                        {
                             if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
                                {
                                exit(0);
                                }
                        }
			ReceiveData() ;
			break ;

		case OAMS_TRXH_ABIHM_TM_RESTART:
			fprintf(stderr,"OAMS_TRXH_ABIHM_TM_RESTART received from TRXH\n") ;

			 /*Send TM_Restart_Ack Msg*/
			tei = ((OamsTrxhAbihmTmRestart *)rcvPtr)->tei;
			bufferPtr = Build_CsappAbihmTrxhTmRestartAckMsg( tei, &size);
			if (bufferPtr != NULL && size > 0)
			{
			     if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
				 {
		                  exit(0);
			         }
			}
			break ;

		case OAMS_TRXH_ABIHM_LINK_DISC_REQ:
			fprintf(stderr,"OAMS_TRXH_ABIHM_LINK_DISC_REQ received from TRXH\n") ;

			 /*Send LINK_DISC_REQ Msg*/
			tei = ((OamsTrxhAbihmLinkDiscReq *)rcvPtr)->tei;
			sapi = ((OamsTrxhAbihmLinkDiscReq *)rcvPtr)->sapi;
                        printf("\n----Value of Tei and Sapi is - %d %d\n", tei,sapi);
                        
			bufferPtr = Build_CsappAbihmTrxhLapdLinkDownMsg( tei,sapi, &size);
			if (bufferPtr != NULL && size > 0)
			{
			     if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
				 {
		                  exit(0);
			         }
			}
			break ;

		default:
			fprintf(stderr,"Invalid message received from SIM\n") ;

	}
	 if (rcvPtr != NULL)
          DalocMsgBuf(rcvPtr) ;
}

I_PVoid Build_CsappAbihmTrxhSetBtsAttrAckMsg(I_U8 tei, I_S32 *size)
{
	CsappAbihmTrxhSetBtsAttrAck *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhSetBtsAttrAck);
        if((ptr = (CsappAbihmTrxhSetBtsAttrAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_SET_BTS_ATTR_ACK, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhSetBtsAttrAck Complete


I_PVoid Build_CsappAbihmTrxhSetTrxPsAttrAckMsg(I_U8 tei, I_S32 *size)
{
	CsappAbihmTrxhSetPsAttrAck *ptr;
        I_U16 len=0;

        len = sizeof(CsappAbihmTrxhSetPsAttrAck);
        if((ptr = (CsappAbihmTrxhSetPsAttrAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_SET_TRX_PS_ATTR_ACK, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhSetTrxPsAttrAck Complete


I_PVoid Build_CsappAbihmTrxhSetTrxPsAttrNackMsg(I_U8 tei, I_S32 *size)
{
	CsappAbihmTrxhSetPsAttrNack *ptr;
        I_U16 len=0;

        len = sizeof(CsappAbihmTrxhSetPsAttrNack);
        if((ptr = (CsappAbihmTrxhSetPsAttrNack *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_SET_TRX_PS_ATTR_NACK, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhSetTrxPsAttrNack Complete

I_PVoid Build_CsappAbihmTrxhSetBtsAttrNackMsg(I_U8 tei, I_S32 *size)
{
        CsappAbihmTrxhSetBtsAttrNack *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhSetBtsAttrNack);
        if((ptr = (CsappAbihmTrxhSetBtsAttrNack *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_SET_BTS_ATTR_NACK, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhSetBtsAttrNack Complete


I_PVoid Build_CsappAbihmTrxhSetChanAttrAckMsg(I_U8 tei, I_S32 *size)
{
        CsappAbihmTrxhSetChanAttrAck *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhSetChanAttrAck);
        if((ptr = (CsappAbihmTrxhSetChanAttrAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_SET_CHAN_ATTR_ACK, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhSetChanAttrAck Complete


I_PVoid Build_CsappAbihmTrxhSetChanAttrNackMsg(I_U8 tei, I_S32 *size)
{
        CsappAbihmTrxhSetChanAttrNack *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhSetChanAttrNack);
        if((ptr = (CsappAbihmTrxhSetChanAttrNack *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_SET_CHAN_ATTR_NACK, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhSetChanAttrNck Complete


I_PVoid Build_CsappAbihmTrxhStateChangeEventReportMsg(I_U8 tei, I_U32 oprState, I_S32 *size)
{
        CsappAbihmTrxhStateChangeEventReport *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhStateChangeEventReport);
        if((ptr = (CsappAbihmTrxhStateChangeEventReport *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
	ptr->oprState = oprState;
        ptr->availStatus.len = 10;
	ptr->availStatus.availStatus[0] = 10;

	*size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_STATE_CHANGE_EVENT_REPORT, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmStateChangeEventReport Complete


I_PVoid Build_CsappAbihmTrxhStateChangeEventReportMsg1(I_U8 tei, I_U32 oprState, I_S32 *size)
{
        CsappAbihmTrxhStateChangeEventReport *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhStateChangeEventReport);
        if((ptr = (CsappAbihmTrxhStateChangeEventReport *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
	ptr->oprState = oprState;
        ptr->availStatus.len = 10;
	ptr->availStatus.availStatus[0] = 8;

	*size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_STATE_CHANGE_EVENT_REPORT, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmStateChangeEventReport Complete
I_PVoid Build_CsappAbihmTrxhFailureEventReportMsg(I_U8 tei, I_S32 *size)
{
        CsappAbihmTrxhFailureEventReport *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhFailureEventReport);
        if((ptr = (CsappAbihmTrxhFailureEventReport *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_FAILURE_EVENT_REPORT, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhFailureEventReport Complete


I_PVoid Build_CsappAbihmTrxhOpStartAckMsg(I_U8 tei ,I_S32 *size)
{
        CsappAbihmTrxhOpStartAck *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhOpStartAck);
        if((ptr = (CsappAbihmTrxhOpStartAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_OP_START_ACK, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhSetBtsAttrAck Complete


I_PVoid Build_CsappAbihmTrxhOpStopAckMsg(I_U8 tei, I_S32 *size)
{
        CsappAbihmTrxhOpStopAck *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhOpStopAck);
        if((ptr = (CsappAbihmTrxhOpStopAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_OP_STOP_ACK, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhOpStopAck Complete


I_PVoid Build_CsappAbihmTrxhTrxHelloMsg(I_U8 tei , I_S32 *size)
{
        CsappAbihmTrxhTrxHello *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;
        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhTrxHello);
        if((ptr = (CsappAbihmTrxhTrxHello *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
	
	if(tei == 15)
	{
	  ptr->trxHwCap.powerClassCapability=(I_U8)40 ;
	  ptr->trxHwCap.bandSupport=(I_U32)90;
	}
	else
	{
          ptr->trxHwCap.powerClassCapability=(I_U8)25 ;
	  ptr->trxHwCap.bandSupport=(I_U32)4;
	}
        ptr->swDes.len = 7;
        strcpy(ptr->swDes.fileVer,"17.31.6") ;
        ptr->inactiveSwDes.len = 7;
        strcpy(ptr->inactiveSwDes.fileVer,"81.99.1") ;

        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_TRX_HELLO, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhTrxHello Complete

I_PVoid Build_CsappAbihmTrxhTmHelloMsg(I_U8 tei , I_S32 *size)
{
        CsappAbihmTrxhTmHello *ptr;
/*
{
   SysHdr              sysHdr;
   OptFlag             isBtsIdPresent;
   OptFlag             isGprsSupportPresent;
   Tei                 tei;
   PlacementInd        placementInd;
   SeqNum              seqNum;
   ObjClass            objClass;
   ObjInstance         objInstance;
   TrxHwCap            trxHwCap;
   BtsIdentifier       btsId;
   GprsSupport         gprsSupport;
}

*/
        
   I_U16 len=0;
   I_U32 powerClassCapability=0;
   I_U32 bandSupport=4;
   I_U32 gprsSupport=I_FALSE;

        len = sizeof(CsappAbihmTrxhTmHello);
        if((ptr = (CsappAbihmTrxhTmHello *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
	
/*	fprintf(stderr, "-------->>Enter powerClassCapability, of TRX  - ");
        scanf("%d",&powerClassCapability);
	fprintf(stderr, "-------->>Enter bandSupport, of TRX  - ");
        scanf("%d",&bandSupport);
	fprintf(stderr, "-------->>Enter isGprsSupportPresent, for TRX  - ");
        scanf("%d",&gprsSupport);*/

        ptr->trxHwCap.powerClassCapability=(I_U8)powerClassCapability ;
	ptr->trxHwCap.bandSupport=(I_U32)bandSupport;
        ptr->isGprsSupportPresent=gprsSupport;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_TM_HELLO, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhTMHello Complete

I_PVoid Build_CsappAbihmTrxhTmRestartAckMsg(I_U8 tei, I_S32 *size)
{
        CsappAbihmTrxhTmRestartAck *ptr;
/*
{
  SysHdr                sysHdr;
  TrxTei                tei;
  PlacementInd          placementInd;
  SeqNum                seqNum;
  ObjClass              objClass;
  BtsObjInst            objInstance;
}CsappAbihmTrxhTmRestartAck;
*/
        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhTmRestartAck);
        if((ptr = (CsappAbihmTrxhTmRestartAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_TM_RESTART_ACK, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhTmResetAck Complete


I_PVoid Build_CsappAbihmTrxhLapdLinkUpMsg(I_U8 tei,I_U32 sapi, I_S32 *size)
{
        CsappAbihmTrxhLapdLinkUp *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhLapdLinkUp);
        if((ptr = (CsappAbihmTrxhLapdLinkUp *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        ptr->sapi = sapi ;
        *size=len;
        fprintf(stderr,"Sending LAPD Link Up Message with msgid [%x]\n",CSAPP_ABIHM_TRXH_LAPD_LINK_UP);
        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_LAPD_LINK_UP, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhLapdLinkUp Complete


I_PVoid Build_CsappAbihmTrxhLinkEstabRespMsg(I_U8 tei, I_S32 *size)
{
        CsappAbihmTrxhLinkEstabResp *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhLinkEstabResp);
        if((ptr = (CsappAbihmTrxhLinkEstabResp *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_LINK_ESTAB_RESP, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
	fprintf(stderr,"Message type of CSAPP_ABIHM_TRXH_LINK_ESTAB_RESP is [0x%x]",CSAPP_ABIHM_TRXH_LINK_ESTAB_RESP) ;

        return ptr;
}// Build_CsappAbihmTrxhLinkEstabResp Complete


I_PVoid Build_CsappAbihmTrxhLapdLinkDownMsg(I_U8 tei,I_U32 sapi, I_S32 *size)
{
        CsappAbihmTrxhLapdLinkDown *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmTrxhLapdLinkDown);
        if((ptr = (CsappAbihmTrxhLapdLinkDown *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei = tei ;
        ptr->sapi = sapi ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_LAPD_LINK_DOWN, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhLapdLinkDown Complete

