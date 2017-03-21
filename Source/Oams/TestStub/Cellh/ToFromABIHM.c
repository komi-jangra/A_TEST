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
I_PVoid Build_CsappAbihmTrxhStateChangeEventReportMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhFailureEventReportMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhOpStartAckMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhOpStopAckMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhTrxHelloMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhLapdLinkUpMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmTrxhLinkEstabRespMsg(I_U8, I_S32 *) ;
I_PVoid Build_CsappAbihmTrxhLapdLinkDownMsg(I_U8, I_S32 *)  ;

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
I_SL32 priority;
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
fprintf(stderr, "-------->> 1.To Send CSAPP_ABIHM_TRXH_SET_BTS_ATTR_NACK \n");
fprintf(stderr, "-------->> 2.To Send CSAPP_ABIHM_TRXH_SET_CHAN_ATTR_NACK \n");
//fprintf(stderr, "-------->> 3.To Send CSAPP_ABIHM_TRXH_STATE_CHANGE_EVENT_REPORT \n");
fprintf(stderr, "-------->> 3.To Send OAMS_ABIHM_TRXH_FAILURE_EVENT_REPORT \n");
fprintf(stderr, "-------->> 4.To Send CSAPP_ABIHM_TRXH_TRX_HELLO \n");
fprintf(stderr, "-------->> 5.To Send CSAPP_ABIHM_TRXH_LAPD_LINK_UP \n");
//fprintf(stderr, "-------->> 7.To Send CSAPP_ABIHM_TRXH_LINK_ESTAB_RESP\n");
fprintf(stderr, "-------->> 6.To Send CSAPP_ABIHM_TRXH_LAPD_LINK_DOWN \n");
fprintf(stderr, "<<-------- 7. To_Receive data \n");

scanf("%d", &choice);

switch(choice)
{

	 case 1 :
		fprintf(stderr, "-------->>Enter TEI, for which this SET_BTS_ATTR_NACK_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhSetBtsAttrNackMsg(tei, &size);
                ch = 1 ;
                break;


	 case 2 :
		fprintf(stderr, "-------->>Enter TEI, for which this SET_BTS_ATTR_NACK_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhSetChanAttrNackMsg(tei, &size);
                ch = 1 ;
                break;
/*
	 case 3 :
		fprintf(stderr, "-------->>Enter TEI, for which this STATE_CHANGE_EVENT_REPORT_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhStateChangeEventReportMsg(tei, &size);
                ch = 1 ;
                break;
*/
	 case 3 :
		fprintf(stderr, "-------->>Enter TEI, for which this FAILURE_EVENT_REPORT_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhFailureEventReportMsg(tei, &size);
                ch = 1 ;
                break;

	 case 4 :
		fprintf(stderr, "-------->>Enter TEI, for which this TRX_HELLO_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhTrxHelloMsg(tei, &size);
                ch = 1 ;
                break;

	 case 5 :
		fprintf(stderr, "-------->>Enter TEI, for which this LAPD_LINKUP_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhLapdLinkUpMsg(tei, &size);
                ch = 1 ;
                break;
/*
	 case 6 :
		fprintf(stderr, "-------->>Enter TEI, for which this LINK_ESTABLISH_RESP_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhLinkEstabRespMsg(tei, &size);
                ch = 1 ;
                PRINT(DEBUG,"Sending CSAPP_ABIHM_TRXH_LINK_ESTAB_RESP signal to TRXH");
		break;
*/
	 case 6 :
		fprintf(stderr, "-------->>Enter TEI, for which this LAPD_LINKDOWN_MSG is  - ");
                scanf("%d",&tei);
                bufferPtr = Build_CsappAbihmTrxhLapdLinkDownMsg(tei, &size);
                ch = 1 ;
                break;

	 case 7 :
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
			tei = ((CsappAbihmTrxhSetBtsAttrAck *)rcvPtr)->tei;
			bufferPtr = Build_CsappAbihmTrxhSetBtsAttrAckMsg( tei, &size);
			if (bufferPtr != NULL && size > 0)
			{
			    if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
					{
			                exit(0);
					}
			}
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
			bufferPtr = Build_CsappAbihmTrxhStateChangeEventReportMsg(tei, &size);
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
                        bufferPtr = Build_CsappAbihmTrxhStateChangeEventReportMsg(tei, &size);
                        if (bufferPtr != NULL && size > 0)
                        {
                             if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
                                {
                                exit(0);
                                }
                        }
			break ;

		case OAMS_TRXH_ABIHM_LINK_ESTAB_REQ:
			fprintf(stderr,"LINK_ESTAB_REQ received from TRXH\n") ;

			/*Sending Ack of Link_Estab_Req signal*/
			tei = ((OamsTrxhAbihmLinkEstabReq *)rcvPtr)->tei;
//			bufferPtr = Build_CsappAbihmTrxhLinkEstabRespMsg(tei, &size);
			bufferPtr = Build_CsappAbihmTrxhLapdLinkUpMsg(tei, &size);
                        LOG_PRINT(DEBUG,"Sending CSAPP_ABIHM_TRXH_LINK_ESTAB_RESP signal to TRXH");
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


I_PVoid Build_CsappAbihmTrxhStateChangeEventReportMsg(I_U8 tei, I_S32 *size)
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
	ptr->oprState = 2;
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
/*	if(tei == 15)
	{
	  ptr->hwCap.powerClassCapability=(I_U8)40 ;
	  ptr->hwCap.bandSupport=(I_U32)90;
	}
	else
	{
          ptr->hwCap.powerClassCapability=(I_U8)15 ;
	  ptr->hwCap.bandSupport=(I_U32)100;
	}
*/
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_TRX_HELLO, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhTrxHello Complete


I_PVoid Build_CsappAbihmTrxhLapdLinkUpMsg(I_U8 tei, I_S32 *size)
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


I_PVoid Build_CsappAbihmTrxhLapdLinkDownMsg(I_U8 tei, I_S32 *size)
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
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_TRXH_LAPD_LINK_DOWN, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmTrxhLapdLinkDown Complete

