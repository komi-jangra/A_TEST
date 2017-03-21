/*se ts=2************************************File Header*****
File Name      :    ToFromDSPH.c
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
#include<sysxxx_datastruct.h>//NEW
#include<syscmn_hashdefs.h>
#include<syscmn_datastruct.h>//NEW
#include<ipcfrm_syslog.h>
#include<ipcfrm_msgqueue.h>
#include<ipcfrm_extern.h>
#include<ipcinst_dbstruct.h>
#include<ipcinst_extern.h>
#include <dbsxxx_commondefs.h>
#include<csappxxx_common_datastruct.h>

#include<bpmxxx_OAM_commonDef.h>
#include<msg_struct.h>
#include<syscmn_hashdefs.h>
#include<sysxxx_datastruct.h>
#include<syscmn_datastruct.h>


#include<oamxxx_hashdefs.h>
#include<oamsxxx_typedef.h>
#include<oamsxxx_hashdef.h>
#include<oamxxx_datastruct.h>
#include<oamxxx_msgstruct.h>
#include<oamsxxx_msgstruct.h>
#include<syspcu_typedefs.h>
#include<syspcu_datastruct.h>
#include<oams_msgstruct.h>
#include <dbsxxx_commondefs.h>
#include<csappxxx_common_datastruct.h>

#include<dsp_pp_com.h>



I_PVoid Build_OamsDsphTrxhTrauChanConfResp(I_S32 *);
I_PVoid Build_OamsDsphTrxhTrauChanDeconfResp(I_S32 *);
I_PVoid Build_OamsDsphTrxhDspStatusInd(I_S32 *);
I_PVoid Build_OamsDsphGrhmAddTrauResourceInd(I_U32, I_S32 *);
I_PVoid Build_OamsDsphGrhmDelTrauResourceInd(I_U32, I_S32 *);


I_U32 dspId;
I_U16 coreId;
I_U16 ptrxId;
I_U16 trauIndex;
I_U16 timeSlot;
I_U16 subTimeSlot;

void ReceiveData();
void DspStatus(int);

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
I_S8 buffer[100];

I_PVoid bufferPtr;

int choice,subChoice ;
int loopIndex;
srcId = (int)ENT_OAMS_DSPH;

if(RegisterWithIpcFrmwrk((int)ENT_OAMS_DSPH, (I_S8 *)"ENT_OAMS_DSPH")!=0)
{
	fprintf(stderr,"Counld not register with framework\n");
}



while(1)
{

fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------- \n");
fprintf(stderr, "<<-------- 1. To_Receive data \n");
fprintf(stderr, "<<-------- 2. DSP Lock \n");
fprintf(stderr, "<<-------- 3. DSP Down \n");
fprintf(stderr, "<<-------- 4. DSP Available \n");
fprintf(stderr, "-------->> 5.To Send OAMS_DSPH_GRHM_ADD_TRAU_RESOURCE_IND \n");
fprintf(stderr, "-------->> 6.To Send OAMS_DSPH_GRHM_DEL_TRAU_RESOURCE_IND \n");

scanf("%d", &choice);

fprintf(stderr, "<<-------- 1. Enter PtrxId \n");
scanf("%d", &ptrxId);


switch(choice)
{

   case 1 :
           ReceiveData();
           break;
   case 2:
   case 3:
   case 4:
           DspStatus(choice);
           break;
   case 5 :
           fprintf(stderr, "-------->>Enter DSP Id \n");
           scanf("%u",&dspId);
           bufferPtr = Build_OamsDsphGrhmAddTrauResourceInd(dspId, &size);
           ch = 1;
           break;
   case 6 :
           fprintf(stderr, "-------->>Enter DSP Id \n");
           scanf("%u",&dspId);
           bufferPtr = Build_OamsDsphGrhmDelTrauResourceInd(dspId, &size);
           ch = 1;
           break;
   default :
	       fprintf(stderr, "\n INVALID CHOICE \n");
 }
    if (ch==1) 
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
		rcvPtr = (I_PVoid)RecvMsg((int)(ENT_OAMS_DSPH), &msgSize);
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
		case OAMS_TRXH_DSPH_TRAU_CHAN_CONF_REQ:
      
      PRINT_HEX_DUMP(DEBUG, (I_U8 *)rcvPtr, sizeof(DTrauMgsTrxhTrauChanConfReq));
      trauIndex=((DTrauMgsTrxhTrauChanConfReq *)rcvPtr)->trauHdr.Index ;
      timeSlot=((DTrauMgsTrxhTrauChanConfReq *)rcvPtr)->timeSlot;
      subTimeSlot=((DTrauMgsTrxhTrauChanConfReq *)rcvPtr)->subTimeSlot;
      dspId=((DTrauMgsTrxhTrauChanConfReq *)rcvPtr)->trauHdr.DSP_Id;
      coreId=((DTrauMgsTrxhTrauChanConfReq *)rcvPtr)->trauHdr.Core_Id;
			fprintf(stderr,"Received OAMS_TRXH_DSPH_TRAU_CHAN_CONF_REQ from TRXH\n") ;
			fprintf(stderr,"TrauChan=%d\n",trauIndex);
			fprintf(stderr,"TimeSlot=%d\n",timeSlot);
			fprintf(stderr,"SubTimeSlotn=%d\n",subTimeSlot);
			fprintf(stderr,"pTRXID=%d\n",ptrxId);
			fprintf(stderr,"dspId=%d\n",dspId);
			fprintf(stderr,"coreId=%d\n",coreId);

      bufferPtr=Build_OamsDsphTrxhTrauChanConfResp(&size);
      if (bufferPtr != NULL && size > 0)
	    {
			  if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
		    {
			   	exit(0);
			  }
			}

      break ;

		case OAMS_TRXH_DSPH_TRAU_CHAN_DECONF_REQ:
      PRINT_HEX_DUMP(DEBUG, (I_U8 *)rcvPtr, sizeof(DTrauMgsTrxhTrauChanDeconfReq));
			fprintf(stderr,"Received OAMS_TRXH_DSPH_TRAU_CHAN_DECONF_REQ From TRXH\n") ;	
			fprintf(stderr,"TrauChan=%d\n",(trauIndex=(((DTrauMgsTrxhTrauChanDeconfReq *)rcvPtr)->trauHdr.Index)));
			fprintf(stderr,"pTRXID=%d\n",(((DTrauMgsTrxhTrauChanDeconfReq *)rcvPtr)->ptrxId));
			fprintf(stderr,"dspId=%d\n",(dspId=(((DTrauMgsTrxhTrauChanDeconfReq *)rcvPtr)->trauHdr.DSP_Id)));
			fprintf(stderr,"coreId=%d\n",(coreId=(((DTrauMgsTrxhTrauChanDeconfReq *)rcvPtr)->trauHdr.Core_Id)));

      bufferPtr=Build_OamsDsphTrxhTrauChanDeconfResp(&size);
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

I_PVoid Build_OamsDsphTrxhTrauChanConfResp(I_S32 *size)
{
   int len;
	  DTrauMgsTrxhTrauChanConfResp *ptr;

    len = sizeof(DTrauMgsTrxhTrauChanConfResp);
    if((ptr = (DTrauMgsTrxhTrauChanConfResp *)AlocMsgBuf(len) ) == (I_Void *)NULL)
    {
       fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
       exit(0);
    }
    *size=len;
FILL_SYS_HDR(&(ptr->sysHdr),OAMS_DSPH_TRXH_TRAU_CHAN_CONF_RESP, 1,PRCR_CP, ENT_OAMS_DSPH ,0,PRCR_CP, ENT_OAMS_TRXH,0);
      
FILL_TRAU_HDR(ptr->trauHdr,dspId,coreId,ENT_MGS_TSM,ZERO,DSP_TRAU,trauIndex,TRAU_TS_CONF,(sizeof (DTrauMgsTrxhTrauChanConfReq)-(sizeof(SysHdr) + sizeof(tHdr))));
      ptr->ptrxId=10;
     ptr->response=DSP_SUCCESS;
      return ptr;
}

I_PVoid Build_OamsDsphTrxhTrauChanDeconfResp(I_S32 *size)
{
   int len;
	  DTrauMgsTrxhTrauChanDeconfResp *ptr;

    len = sizeof(DTrauMgsTrxhTrauChanDeconfResp);
    if((ptr = (DTrauMgsTrxhTrauChanDeconfResp *)AlocMsgBuf(len) ) == (I_Void *)NULL)
    {
       fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
       exit(0);
    }
    *size=len;
FILL_SYS_HDR(&(ptr->sysHdr),OAMS_DSPH_TRXH_TRAU_CHAN_DECONF_RESP, 1,PRCR_CP, ENT_OAMS_DSPH ,0,PRCR_CP, ENT_OAMS_TRXH,0);
      
FILL_TRAU_HDR(ptr->trauHdr,dspId,coreId,ENT_MGS_TSM,ZERO,DSP_TRAU,trauIndex,TRAU_TS_DECONF,(sizeof (DTrauMgsTrxhTrauChanDeconfReq)-(sizeof(SysHdr) + sizeof(tHdr))));
      ptr->ptrxId=10;
      ptr->response=DSP_SUCCESS;
      return ptr;
}



void DspStatus(int ch)
{
  OamsDsphTrxhDspStatusInd *ptr;
  int len;
  I_SL32 priority;

  len=sizeof(OamsDsphTrxhDspStatusInd); 
  
  if((ptr = (OamsDsphTrxhDspStatusInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
      fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
      exit(0);
  }
  FILL_SYS_HDR(&(ptr->sysHdr),OAMS_DSPH_TRXH_DSP_STATUS_IND, 1,PRCR_CP, ENT_OAMS_DSPH ,0,PRCR_CP, ENT_OAMS_TRXH,0);
  
  if(2 == ch)
  {
    ptr->cause=DSP_NOT_AVAILABLE_LOCK;
  }
  else if(3 == ch)
  {
    ptr->cause=DSP_NOT_AVAILABLE_DOWN;
  }
  else if(4 == ch)
  {
    ptr->cause=DSP_AVAILABLE;
  }
  else
  {
    printf("Default: Invalid value of ch=%d\n",ch);
  }
  if(SendMsg(ptr, priority, len) == SND_FAIL)
   {
		   printf("\nSend Failed in Fn (DspStatus)\n");	
       exit(0);
	  }
}


I_PVoid Build_OamsDsphGrhmAddTrauResourceInd(I_U32 dspId, I_S32 *size)
{
   OamsDsphGrhmAddTrauResourceInd *ptr;
   I_U16 len=0,coreId=0,maxAbisTs=0,maxTrauChan=0,activeTs=0;

   len = sizeof(OamsDsphGrhmAddTrauResourceInd);
   if((ptr = (OamsDsphGrhmAddTrauResourceInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
       fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
       exit(0);
   }
   /*
				    fprintf(stderr, "-------->>Enter MaxAbisTs is  - \n");
				       scanf("%u",&maxAbisTs);
				          fprintf(stderr, "-------->>Enter CoreId  \n");
					     scanf("%u",&coreId);
					        fprintf(stderr, "-------->>Enter maxTrauChan  \n");
						   scanf("%u",&maxTrauChan);
						      fprintf(stderr, "-------->>Enter activeTs  \n");
						         scanf("%u",&activeTs);
							    */
      ptr->maxAbisTs = 3;
      ptr->dspId = 1;
      ptr->coreId = 1;
      ptr->maxTrauChan = 12;
      ptr->activeTs = 12;
     *size = len;
      FILL_SYS_HDR(&(ptr->sysHdr),OAMS_DSPH_GRHM_ADD_TRAU_RESOURCE_IND, 1,PRCR_CP, ENT_OAMS_DSPH ,0,PRCR_CP, ENT_CSAPP_GRHM,0);
      fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
      return ptr;
}

I_PVoid Build_OamsDsphGrhmDelTrauResourceInd(I_U32 dspId, I_S32 *size)
{
   OamsDsphGrhmDelTrauResourceInd *ptr;
   I_U16 len=0;
   len = sizeof(OamsDsphGrhmDelTrauResourceInd);
   if((ptr = (OamsDsphGrhmDelTrauResourceInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
   {
       fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
       exit(0);
   }
   ptr->dspId = dspId;
  *size = len;
  FILL_SYS_HDR(&(ptr->sysHdr),OAMS_DSPH_GRHM_DEL_TRAU_RESOURCE_IND, 1,PRCR_CP, ENT_OAMS_DSPH ,0,PRCR_CP, ENT_CSAPP_GRHM,0);
  fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);
  return ptr;
}






