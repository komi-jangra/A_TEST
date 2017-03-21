/*se ts=2************************************File Header*****
File Name      :    ToFromGRHM.c
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
#include<sysxxx_macro.h>

I_PVoid Build_CsappGrhmTrxhCreChanResp(I_U32 ,I_S32 *);
//I_PVoid Build_CsappGrhmTrxhCreChanFail(I_S32 *);
I_PVoid Build_CsappGrhmTrxhDelChanResp(I_U32 , I_S32 *);
void ReceiveData();

I_U16 srcinstG;
I_U16 CallRef;

main()
{
I_S32 count=0,size=0,i=0;
I_S32 srcId,dstId,interval;
I_SL32 priority;
//PRIVATE struct timeval timeout = {1,0};
I_S8 buffer[100];

I_PVoid bufferPtr;

int choice ;

srcId = (int)ENT_CSAPP_GRHM ;

if(RegisterWithIpcFrmwrk((int)ENT_CSAPP_GRHM, (I_S8 *)"SND_RECV_FROM_GRHM")!=0)
{
	fprintf(stderr,"Could not register with framework\n");
}

while(1)
{
fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------- \n");

fprintf(stderr, "<<-------- 1. To_Receive data \n");

scanf("%d", &choice);

switch(choice)
{

  case 1 :
    ReceiveData() ;
		     break ;
							
	default :
	 fprintf(stderr, "\n INVALID CHOICE \n");
									
}// switch choice
	
}//while 1	

}// main

void ReceiveData()
{
	I_PVoid		rcvPtr ;
	I_S32 		msgSize,size ;
	I_U32		  msgType,tei ;
	I_SL32    priority ;
	I_PVoid bufferPtr;
  while(1)
  {
	rcvPtr = (I_PVoid)RecvMsg((int)(ENT_CSAPP_GRHM), &msgSize);
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
  fprintf(stderr," Msg Type received is = [%d]\n",msgType);

  //tei = ((CsappGrhmTrxhCreChanAck *)rcvPtr)->tei;
	
	switch (msgType)
	{
		case OAMS_TRXH_GRHM_CRE_CHN_REQ:
			fprintf(stderr,"CREATE CHANNEL REQ received from TRXH\n") ;
			tei = ((OamsTrxhGrhmCreChanReq *)rcvPtr)->tei;
			bufferPtr = Build_CsappGrhmTrxhCreChanResp( tei, &size);
			if (bufferPtr != NULL && size > 0)
	    {
				   if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
		       {
					    	exit(0);
					 }
			}
			break ;
		case OAMS_TRXH_GRHM_DEL_CHN_REQ:
			fprintf(stderr,"Del Channel Req Received from Trxh\n") ;		
			tei = ((OamsTrxhGrhmDelChanReq *)rcvPtr)->tei;
			bufferPtr = Build_CsappGrhmTrxhDelChanResp( tei, &size);
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
}

I_PVoid Build_CsappGrhmTrxhCreChanResp(I_U32 tei, I_S32 *size)
{
	CsappGrhmTrxhCreChanAck    *msgPtr ;

	//I_U32 dinstid=0;
	I_U16 len=0;

	//printf(" Entered Inst Id = %d \n", dinstid);

	len = sizeof(CsappGrhmTrxhCreChanAck);
	if((msgPtr = (CsappGrhmTrxhCreChanAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }
	
		 
	//Filling GRHM_TRXH_CRE_CHAN_RESP Messages
	msgPtr->tei = tei ;
	*size=len;
	   
	 FILL_SYS_HDR(&(msgPtr->sysHdr),CSAPP_GRHM_TRXH_CRE_CHN_ACK, 1,PRCR_CP, ENT_CSAPP_GRHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);

	fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
	fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

	return  msgPtr;
			
}// Build_CsappGrhmTrxhCreChanRespMsg Complete




I_PVoid Build_CsappGrhmTrxhDelChanResp(I_U32 tei, I_S32 *size)
{
        CsappGrhmTrxhDelChanAck *msgPtr ;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappGrhmTrxhDelChanAck);
        if((msgPtr = (CsappGrhmTrxhDelChanAck *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        //Filling GRHM_TRXH_DEL_CHAN_RESP Messages
        msgPtr->tei = tei ;
        *size=len;

         FILL_SYS_HDR(&(msgPtr->sysHdr),CSAPP_GRHM_TRXH_DEL_CHN_ACK, 1,PRCR_CP, ENT_CSAPP_GRHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);

        fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

        return  msgPtr;

}// Build_CsappGrhmTrxhDelChanRespMsg Complete




/*

I_PVoid Build_CsappGrhmTrxhCreChanFail(I_S32 *size)
{
        CsappGrhmTrxhCreChanFail    *msgPtr ;

        //I_U32 dinstid=0;
        I_U16 len=0;

	//printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappGrhmTrxhCreChanFail);
        if((msgPtr = (CsappGrhmTrxhCreChanFail *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }


        //Filling CSAPP_GRHM_TRXH_CRE_CHAN_FAIL Messages
        msgPtr->teiId = 1 ;

        FILL_SYS_HDR(&(msgPtr->sysHdr),CSAPP_GRHM_TRXH_CRE_CHAN_FAIL, 1,PRCR_CP, ENT_CSAPP_GRHM ,0,PRCR_CP, ENT_OAMS_TRXH,0);

                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return msgPtr;                                                                                                     
}// Build_CsappGrhmTrxhCreChanFailMsg Complete

*/

