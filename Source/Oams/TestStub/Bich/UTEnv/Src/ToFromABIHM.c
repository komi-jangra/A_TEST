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
extern I_U32 gTei, gBtsId;

I_PVoid Build_CsappAbihmBichBicHelloMsg(I_U8,I_S32 *)  ;
I_PVoid Build_CsappAbihmBichDsLinkEstMsg(I_U8,I_S32 *)  ;
I_PVoid Build_CsappAbihmBichLapdLinkUpMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmBichLapdLinkDownMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmBichDsLinkFailMsg(I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmBichBmHelloMsg (I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmBichBicBscAlarmMsg (I_U8, I_S32 *)  ;
I_PVoid Build_CsappAbihmBichFailureEventReport (I_U8, I_S32 *)  ;
I_PVoid displaySlotConnect(I_PVoid);
I_PVoid displayBmRestart(I_PVoid);
I_PVoid displayDisSlotConnect(I_PVoid);
void ReceiveData();

I_U16 srcinstG;
I_U16 CallRef;

I_Void SendAbihmMsg(I_U32 msgOpCode)
{
  I_S32 count=0,size=0,i=0;
  I_S32 srcId,dstId,interval;
  I_U32 ch=0 ;
  I_U8 tei;
  I_SL32 priority;
  I_S8 buffer[100];

  I_PVoid bufferPtr;

  switch(msgOpCode) {
    case CSAPP_ABIHM_BICH_BIC_HELLO :
    {
      bufferPtr = Build_CsappAbihmBichBicHelloMsg(gTei, &size);
      ch = 1 ;
      break;
    }
    case CSAPP_ABIHM_BICH_BIC_DS_LINK_EST :
    {
      bufferPtr = Build_CsappAbihmBichDsLinkEstMsg(gTei, &size);
      ch = 1 ;
      break;
    }
    case CSAPP_ABIHM_TRXH_LAPD_LINK_UP :
    {
      bufferPtr = Build_CsappAbihmBichLapdLinkUpMsg(gTei, &size);
      ch = 1 ;
      break;
    }
    case CSAPP_ABIHM_TRXH_LAPD_LINK_DOWN :
    {
      bufferPtr = Build_CsappAbihmBichLapdLinkDownMsg(gTei, &size);
      ch = 1 ;
      break;
    }
    case CSAPP_ABIHM_BICH_BIC_DS_LINK_FAIL :
    {
      bufferPtr = Build_CsappAbihmBichDsLinkFailMsg(gTei, &size);
      ch = 1 ;
      break;
    }
    case CSAPP_ABIHM_BICH_BM_HELLO :
    {
      bufferPtr = Build_CsappAbihmBichBmHelloMsg(gTei, &size);
      ch = 1 ;
      break;
    }
    case CSAPP_ABIHM_BICH_BIC_BSC_ALARM_IND :
    {
      bufferPtr = Build_CsappAbihmBichBicBscAlarmMsg(gTei, &size);
      ch = 1 ;
      break;
    }
    case CSAPP_ABIHM_BICH_FAILURE_EVENT_REPORT :
    {
      bufferPtr = Build_CsappAbihmBichFailureEventReport(gTei, &size);
      ch = 1 ;
      break;
    }
    default :
    {
      fprintf(stderr, "\n INVALID CHOICE \n");
    }
  }// switch choice

	if ( (ch && bufferPtr && size ) && (SendMsg(bufferPtr, priority, size) == SND_FAIL)) {
	  exit(0);
	}
	
}// main

void RcvAbihmMsg(I_PVoid		rcvPtr)
{
	I_S32 		msgSize,size ;
	I_U16		  msgType ;
	I_U8		  tei;
	I_SL32    priority ;
	I_PVoid 	bufferPtr ;
  I_U8      entId;

	msgType = ((SysHdr *)rcvPtr)->msgType ;
  entId = ((SysHdr *) rcvPtr)->dest.entity ;

	switch (msgType) {
    case OAMS_BICH_ABIHM_LINK_EST_REQ:
      fprintf(stderr,"LINK ESTAB REQ received from BICH\n") ;
      break ;
    case OAMS_BICH_ABIHM_BIC_SLOT_CONNECT:
      fprintf(stderr,"SLOT_CONNECT received from BICH\n") ;
      displaySlotConnect(rcvPtr);
      break ;
    case OAMS_BICH_ABIHM_BIC_SLOT_DISCONNECT:
      displayDisSlotConnect(rcvPtr);
      fprintf(stderr,"SLOT_DISCONNECT received from BICH\n") ;
      break ;
    case OAMS_BICH_ABIHM_BM_RESTART:
      displayBmRestart(rcvPtr);
      fprintf(stderr,"BM_RESTART received from BICH\n") ;
      break ;
		default:
			fprintf(stderr,"Invalid message received from SIM\n") ;

	}
	if (!rcvPtr) {
    DalocMsgBuf(rcvPtr) ;
  }
}

I_PVoid displaySlotConnect(I_PVoid rcvPtr)
{
	OamsBichAbihmSlotConnect *slotConnect;
	slotConnect =(OamsBichAbihmSlotConnect *)(rcvPtr);
	fprintf(stderr, "from bicId=%d\n ",slotConnect->bicId);
	fprintf(stderr, "to bicId=%d\n",slotConnect->slotConnMap[0].bicId);
	fprintf(stderr, "slotNoUpStreamPort=%d\n",slotConnect->slotConnMap[0].slotNoUpStreamPort);
	fprintf(stderr, "slotNoDownStreamPort=%d\n",slotConnect->slotConnMap[0].slotNoDownStreamPort);
	fprintf(stderr, "noOfSlots=%d\n",slotConnect->slotConnMap[0].noOfSlots);
	fprintf(stderr, "bictei=%d\n",slotConnect->bicTei);
	fprintf(stderr, "numSlotConMap=%d\n",slotConnect->numSlotConMap);
          
}

I_PVoid displayDisSlotConnect(I_PVoid rcvPtr)
{
        OamsBichAbihmSlotDisConnect  *slotConnect;
        slotConnect =(OamsBichAbihmSlotDisConnect *)(rcvPtr);
        fprintf(stderr, "from bicId=%d\n ",slotConnect->bicId);
        fprintf(stderr, "to bicId=%d\n",slotConnect->slotConnMap[0].bicId);
        fprintf(stderr, "slotNoUpStreamPort=%d\n",slotConnect->slotConnMap[0].slotNoUpStreamPort);
        fprintf(stderr, "slotNoDownStreamPort=%d\n",slotConnect->slotConnMap[0].slotNoDownStreamPort);
        fprintf(stderr, "noOfSlots=%d\n",slotConnect->slotConnMap[0].noOfSlots);
        fprintf(stderr, "bictei=%d\n",slotConnect->bicTei);
        fprintf(stderr, "numSlotConMap=%d\n",slotConnect->numSlotConMap);

}

I_PVoid displayBmRestart(I_PVoid rcvPtr)
{
        OamsBichAbihmBmRestart  *bmRestart;
        bmRestart =(OamsBichAbihmBmRestart *)(rcvPtr);
        fprintf(stderr, "btstei=%d\n",bmRestart->bicTei);
        fprintf(stderr, "placementInd=%d\n",bmRestart->placementInd );
        fprintf(stderr, "seqNum=%d\n",bmRestart->seqNum);
        fprintf(stderr, "objClass=%d\n",bmRestart->objClass);
        fprintf(stderr, "objInstance[1]=%d\n",bmRestart->objInstance.btsObjInst[0]);
        fprintf(stderr, "objInstance[2]=%d\n",bmRestart->objInstance.btsObjInst[1]);
        fprintf(stderr, "objInstance[3]=%d\n",bmRestart->objInstance.btsObjInst[2]);

}

I_PVoid Build_CsappAbihmBichBicHelloMsg(I_U8 tei , I_S32 *size)
{
        CsappAbihmBichBicHello *ptr;

        I_U16 len=0;
        I_U32 bicId=gBtsId ;

        len = sizeof(CsappAbihmBichBicHello);
        if((ptr = (CsappAbihmBichBicHello *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->bicTei  = tei ;
        ptr->bicId   = bicId ;

      	ptr->swDes.len = 7;
        strcpy(ptr->swDes.fileVer,"17.31.6") ;
        ptr->isInactiveSwDesPresent = 1;
        ptr->inactiveSwDes.len = 7;
        strcpy(ptr->inactiveSwDes.fileVer,"81.99.1") ;
        ptr->isInactiveSwDesPresent = 1;

	      *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_BICH_BIC_HELLO, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_BICH,0);


        fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmBichBicHello Complete

I_PVoid Build_CsappAbihmBichDsLinkEstMsg(I_U8 tei , I_S32 *size)
{
        CsappAbihmBichDsLinkEst *ptr;

        I_U16 len=0;
        I_U32 bicId=0 ;
        I_U32 fromBicId=0;
	I_U8  parentBicDsPort=0;

        len = sizeof(CsappAbihmBichDsLinkEst);
        if((ptr = (CsappAbihmBichDsLinkEst *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }
        fprintf(stderr, "-------->>Enter bicId, for which  DS_LINK_EST_MSG is  - ");
        scanf("%d",&bicId);
        

	fprintf(stderr, "-------->>Enter fromBicId(parent BicId), for which  DS_LINK_EST_MSG is  - ");
        scanf("%d",&fromBicId);
        
        fprintf(stderr,"fromBicId=%d \n",fromBicId);
	
	
        ptr->bicTei     = tei ;
        ptr->bicId      = bicId ;
        ptr->fromBicId  = fromBicId ;
      
 
	ptr->swDes.len = 7;
        strcpy(ptr->swDes.fileVer,"17.31.6") ;
        ptr->inactiveSwDes.len = 7;
        strcpy(ptr->inactiveSwDes.fileVer,"81.99.1") ;

	fprintf(stderr, "-------->>Enter parentBicDsPort , for which  DS_LINK_EST_MSG is  - ");
        scanf("%d",&parentBicDsPort);
	ptr->physicalIf = parentBicDsPort;
        
	printf("fromBicId=%d \n",ptr->fromBicId);
        
	fprintf(stderr,"parentDsPort=%d \n",ptr->physicalIf);
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_BICH_BIC_DS_LINK_EST, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_BICH,0);


        fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);

        return ptr;

}//Build_CsappAbihmBichDsLinkEstMsg Complete

I_PVoid Build_CsappAbihmBichLapdLinkUpMsg(I_U8 tei, I_S32 *size)
{
        CsappAbihmBichLapdLinkUp *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmBichLapdLinkUp);
        if((ptr = (CsappAbihmBichLapdLinkUp *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->bicTei = tei ;
        ptr->sapi =SAPI62 ;
        *size=len;
        fprintf(stderr,"Sending LAPD Link Up Message with msgid [%x]\n",CSAPP_ABIHM_TRXH_LAPD_LINK_UP);
        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_BICH_LAPD_LINK_UP, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_BICH,0);


        fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmBichLapdLinkUp Complete


I_PVoid Build_CsappAbihmBichLapdLinkDownMsg(I_U8 tei, I_S32 *size)
{
        CsappAbihmBichLapdLinkDown *ptr;

        //I_U32 dinstid=0;
        I_U16 len=0;

        //printf(" Entered Inst Id = %d \n", dinstid);

        len = sizeof(CsappAbihmBichLapdLinkDown);
        if((ptr = (CsappAbihmBichLapdLinkDown *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->bicTei = tei ;
        ptr->sapi =SAPI62 ;
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_BICH_LAPD_LINK_DOWN, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_BICH,0);


        fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmBichLapdLinkDown Complete

I_PVoid Build_CsappAbihmBichDsLinkFailMsg(I_U8 tei , I_S32 *size)
{
        CsappAbihmBichDsLinkFail *ptr;

        I_U16 len=0;
        I_U32 bicId=0 ;
        I_U32 bicList[10];
        I_U8  i;
        I_U8  numBic;
        fprintf(stderr, "-------->>Enter bicId, from which  DS_LINK_FAIL_MSG is Originated  - ");
        scanf("%d",&bicId);

        fprintf(stderr, "-------->>Enter no of effected BIC's , for DS_LINK_FAIL_MSG - ");
        scanf("%d",&numBic);

        len = sizeof(CsappAbihmBichDsLinkFail);
        if((ptr = (CsappAbihmBichDsLinkFail *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }
 	ptr->bicId   = bicId ;
	ptr->bicTei  = tei ;
        ptr->numBic  = numBic ;
        for(i=0;i<numBic;i++)
        {
        fprintf(stderr, "-------->>Enter bicId of effected BIC's, due to  DS_LINK_FAIL_MSG - ");
        scanf("%d",&(ptr->bicIdList[i]));
        }
        *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_BICH_BIC_DS_LINK_FAIL, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_BICH,0);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
        return ptr;
}

I_PVoid Build_CsappAbihmBichBmHelloMsg(I_U8 tei , I_S32 *size)
{
        CsappAbihmBichBmHello *ptr;

        I_U16 len=0;
        I_U32 btsId=gBtsId ;

        len = sizeof(CsappAbihmBichBmHello);
        if((ptr = (CsappAbihmBichBmHello *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->bicTei  = tei ;
        ptr->btsId   = gBtsId ;

	      ptr->btsActiveSwDes.len = 7;
        strcpy(ptr->btsActiveSwDes.fileVer,"17.31.6") ;
        ptr->btsInactiveSwDes.len = 7;
        strcpy(ptr->btsInactiveSwDes.fileVer,"81.99.1") ;
        ptr->isInactiveSwDesPresent = 1;

	      *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_BICH_BM_HELLO, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_BICH,0);


        fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmBichBmHello Complete

I_PVoid Build_CsappAbihmBichBicBscAlarmMsg (I_U8 tei , I_S32 *size)
{
        CsappAbihmBichBicBscAlarmInd *ptr;

        I_U16 len=0;
        I_U32 btsId=gBtsId ;

        len = sizeof(CsappAbihmBichBicBscAlarmInd);
        if((ptr = (CsappAbihmBichBicBscAlarmInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->bicTei  = tei ;
        ptr->bicId   = btsId ;

	      fprintf(stderr, "-------->>Enter alarmCause - ");
        scanf("%d",&(ptr->alarmCause));

	      *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_BICH_BIC_BSC_ALARM_IND, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_BICH,0);


        fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmBichBicBscAlarmMsg Complete

I_PVoid Build_CsappAbihmBichFailureEventReport (I_U8 tei , I_S32 *size)
{
        CsappAbihmBichFailureEventReport *ptr;

        I_U16 len=0;
        I_U32 btsId=0 ;

        len = sizeof(CsappAbihmBichFailureEventReport);
        if((ptr = (CsappAbihmBichFailureEventReport *)AlocMsgBuf(len) ) == (I_Void *)NULL)        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        ptr->tei  = tei ;

	      *size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),CSAPP_ABIHM_BICH_FAILURE_EVENT_REPORT, 1,PRCR_CP, ENT_CSAPP_ABIHM ,0,PRCR_CP, ENT_OAMS_BICH,0);


        fprintf(stderr,"Initial Msg (*size = %d : 0x%x) \n", *size, *size);

        return ptr;
}// Build_CsappAbihmBichFailureEventReport Complete
