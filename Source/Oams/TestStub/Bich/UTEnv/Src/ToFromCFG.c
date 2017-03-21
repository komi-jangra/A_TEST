/*se ts=2************************************File Header*****
File Name      :    ToFromCFG.c
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
#include <testsuit.h>

I_PVoid Build_OamsCfgCellhUnlockReqMsg(I_U32, I_U32, I_S32 *);
I_PVoid Build_OamsCfgCellhLockReqMsg(I_U32, I_U32, I_S32 *);
I_PVoid Build_OamsCfgCellhCellShutdownInd(I_S32 *);
I_PVoid Build_OamsCfgCellhCellBarAccess(I_S32 *);

I_PVoid Build_OamsCfgTrxhUnlockReqMsg(I_U32, I_S32 *);
I_PVoid Build_OamsCfgTrxhLockReqMsg(I_U32, I_S32 *);

I_PVoid Build_OamsCfgTrxhAddTrxReqMsg(I_U32, I_S32 *);
I_PVoid Build_OamsCfgTrxhDelTrxReqMsg(I_U32, I_S32 *);

I_PVoid Build_OamsCfgBichAddBicReqMsg(I_U32, I_S32 *);
I_PVoid Build_OamsCfgBichDelBicReqMsg(I_U32, I_S32 *);
I_PVoid Build_OamsCfgBichInitAbisE1Msg(I_U32, I_S32 *);
I_PVoid Build_OamsCfgBichDelAbisE1Msg(I_U32, I_S32 *);
I_PVoid Build_OamsCfgBichUpdateAbisE1Msg(I_U32, I_S32 *);
I_PVoid Build_OamsCfgBichLockBicReqMsg(I_U32, I_S32 *);
I_PVoid Build_OamsCfgBichUnlockBicReqMsg(I_U32, I_S32 *);
I_PVoid Build_OamsCfgBichAddTrxIndMsg(I_U32, I_U32, I_S32 *);
I_PVoid Build_OamsCfgBichDelTrxIndMsg(I_U32, I_U32, I_S32 *);
I_PVoid Build_OamsCfgBichBmResetMsg(I_U32, I_S32 *);
void ReceiveData();

I_U16 srcinstG;
I_U16 CallRef;

I_Void SendCfgMsg(I_U32 msgOpCode)
{
  I_S32 count=0,size=0,i=0,result;
  I_S32 srcId,dstId,interval;
  I_SL32 priority;
  I_U32 cellId;
  I_U32 lac;
  //PRIVATE struct timeval timeout = {1,0};
  I_S8 buffer[100];
  I_U32 ptrxId =gTrxId, bicId = gBtsId;
  I_PVoid bufferPtr;
  I_U32 e1Id = gE1Id;
  I_U32 choice = 1;

  switch(msgOpCode) {
	  case OAMS_CFG_CELLH_UNLOCK_REQ :
    {
  		fprintf(stderr,"--------UNLOCK Req for CellId - \n");
  		scanf("%d",&cellId);
  		fprintf(stderr,"--------UNLOCK Req for Lac - \n");
                scanf("%d",&lac);
  		bufferPtr = Build_OamsCfgCellhUnlockReqMsg(cellId, lac, &size);
		  break;
    }
  	case OAMS_CFG_CELLH_LOCK_REQ :
    {
      fprintf(stderr,"--------LOCK Req for CellId - \n");
      scanf("%d",&cellId);
      //fflush(stdin);
      fprintf(stderr,"--------LOCK Req for Lac - \n");
      scanf("%d",&lac);
		  bufferPtr = Build_OamsCfgCellhLockReqMsg(cellId, lac, &size);
		  break;	
    }
	  case OAMS_CFG_CELLH_SHUTDOWN_IND :
    {
      bufferPtr = Build_OamsCfgCellhCellShutdownInd(&size); 
	    break;		
    }
	  case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
    {
		  bufferPtr = Build_OamsCfgCellhCellBarAccess(&size);
		  break;
    }
    case OAMS_CFG_TRXH_UNLOCK_REQ :
    {
      fprintf(stderr, "\n--------Enter PtrxId, for which this UNLOCK Req is - ");
      scanf("%d",&ptrxId);
		  bufferPtr = Build_OamsCfgTrxhUnlockReqMsg(ptrxId, &size);
		  break;
    }
    case OAMS_CFG_TRXH_LOCK_REQ :
    {
      bufferPtr = Build_OamsCfgTrxhLockReqMsg(ptrxId, &size);
      break;
    }
    case OAMS_CFG_TRXH_ADD_TRX_REQ :
    {
      bufferPtr = Build_OamsCfgTrxhAddTrxReqMsg(ptrxId, &size);
      break;
    }
    case OAMS_CFG_TRXH_DEL_TRX_REQ :
    {
      bufferPtr = Build_OamsCfgTrxhDelTrxReqMsg(ptrxId, &size);
      break;
    }
    case OAMS_CFG_BICH_ADD_BIC_REQ :
    {
      bufferPtr = Build_OamsCfgBichAddBicReqMsg(bicId, &size);
      break;
    }
    case  OAMS_CFG_BICH_DEL_BIC_REQ:
    {
      bufferPtr = Build_OamsCfgBichDelBicReqMsg(bicId, &size);
      break;
    }
    case  OAMS_CFG_BICH_INIT_ABIS_E1:
    {
      bufferPtr = Build_OamsCfgBichInitAbisE1Msg(e1Id, &size);
      break;
    }
    case  OAMS_CFG_BICH_DELETE_ABIS_E1:
    {
      bufferPtr = Build_OamsCfgBichDelAbisE1Msg(e1Id, &size);
      break;
    }    
    case  OAMS_CFG_BICH_UPDATE_ABIS_E1:
    {
      bufferPtr = Build_OamsCfgBichUpdateAbisE1Msg(e1Id, &size);
      break;
    }
    case OAMS_CFG_BICH_LOCK_REQ :
    {
      bufferPtr = Build_OamsCfgBichLockBicReqMsg(bicId, &size);
      break;
    }
    case OAMS_CFG_BICH_UNLOCK_REQ :
    {
      bufferPtr = Build_OamsCfgBichUnlockBicReqMsg(bicId, &size);
      break;
    }
    case  OAMS_CFG_BICH_ADD_TRX_INDICATION:
    {
      bufferPtr = Build_OamsCfgBichAddTrxIndMsg(bicId, ptrxId, &size);
      break;
    }
    case  OAMS_CFG_BICH_DEL_TRX_INDICATION:
    {
      bufferPtr = Build_OamsCfgBichDelTrxIndMsg(bicId, ptrxId, &size);
      break;
    }
    case  OAMS_CFG_BICH_BTS_RESET:
    {
      bufferPtr = Build_OamsCfgBichBmResetMsg(bicId, &size);
      break;
    }
	  default :
  		fprintf(stderr, "\n INVALID CHOICE \n");
      choice = 0;
  }// switch choice
	if (choice && bufferPtr && size ) {
   fprintf(stderr,"sending Ptr =%x\n",bufferPtr);
	 if(SendMsg(bufferPtr, priority, size) == SND_FAIL) {
	  fprintf(stderr, "\n--------msg sending failed  - ");
	  exit(0);
	 }
	}
}// main

void RcvCfgMsg(I_PVoid		rcvPtr)
{
	I_S32 		msgSize ;
	I_U16		msgType ;
	I_U8		entId;

	
	msgType = ((SysHdr *)rcvPtr)->msgType ;
	entId = ((SysHdr *) rcvPtr)->dest.entity ;

	switch (msgType)
	{
    case OAMS_CELLH_CFG_UNLOCK_RESP:
      fprintf(stderr,"UnLock Response received from CELLH\n") ;
      break ;
    case OAMS_CELLH_CFG_ALARM_IND:
      fprintf(stderr,"Alarm received from CELLH\n") ;		
      break ;
    case OAMS_CELLH_CFG_LOCK_RESP:
      fprintf(stderr,"Lock Response received from CELLH\n") ;
      break ;
		case OAMS_TRXH_CFG_UNLOCK_RESP:
      fprintf(stderr,"UnLock Response received from TRXH\n") ;
      break ;
    case OAMS_TRXH_CFG_ALARM_IND:
      fprintf(stderr,"Alarm received from TRXH \n") ;
      break ;
    case OAMS_TRXH_CFG_LOCK_RESP:
      fprintf(stderr,"Lock Response received from TRXH\n") ;
      break ;
    case OAMS_TRXH_CFG_ADD_TRX_RESP:
      fprintf(stderr,"Lock Response received from TRXH\n") ;
      break ;
    case OAMS_TRXH_CFG_DEL_TRX_RESP:
      fprintf(stderr,"Lock Response received from TRXH\n") ;
      break ;
    case OAMS_BICH_CFG_ADD_BIC_RESP:
      fprintf(stderr,"ADD_BIC_RESP received from BICH\n") ;
      fprintf(stderr,"Status %d\n", ((OamsBichCfgAddBicResp *)rcvPtr)->result) ;
      break ;
    case OAMS_BICH_CFG_DEL_BIC_RESP:
      fprintf(stderr,"DELETE BIC RESP received from BICH\n") ;
      fprintf(stderr,"Status %d\n", ((OamsBichCfgDelBicResp *)rcvPtr)->result) ;
      break ;
    case OAMS_BICH_CFG_ALARM_IND:
      fprintf(stderr,"Alarm received from BICH \n") ;
      fprintf(stderr,"Status %d\n", ((OamsTrxhCfgAlarmInd *)rcvPtr)->sysAlarm.sysalarmId) ;
      fprintf(stderr,"Status %d\n", ((OamsTrxhCfgAlarmInd *)rcvPtr)->sysAlarm.alarmLevel) ;
      fprintf(stderr,"Status %d\n", ((OamsTrxhCfgAlarmInd *)rcvPtr)->sysAlarm.key1) ;
      fprintf(stderr,"Status %d\n", ((OamsTrxhCfgAlarmInd *)rcvPtr)->sysAlarm.key2) ;
      fprintf(stderr,"Status %d\n", ((OamsTrxhCfgAlarmInd *)rcvPtr)->sysAlarm.key3) ;
      fprintf(stderr,"Status %d\n", ((OamsTrxhCfgAlarmInd *)rcvPtr)->sysAlarm.info3) ;
      fprintf(stderr,"Status %s\n", ((OamsTrxhCfgAlarmInd *)rcvPtr)->sysAlarm.infoString) ;
      fprintf(stderr,"Status %d\n", ((OamsTrxhCfgAlarmInd *)rcvPtr)->sysAlarm.infoStrLen) ;
      break ;
    case OAMS_BICH_CFG_LOCK_RESP:
      fprintf(stderr,"OAMS_BICH_CFG_LOCK_RESP received from BICH \n") ;
      fprintf(stderr,"Status %d\n", ((OamsBichCfgLockResp *)rcvPtr)->result) ;
      break ;
    case OAMS_BICH_CFG_UNLOCK_RESP:
      fprintf(stderr,"OAMS_BICH_CFG_UNLOCK_RESP received from BICH \n") ;
      fprintf(stderr,"Status %d\n", ((OamsBichCfgUnlockResp *)rcvPtr)->result) ;
      break ;
		default:
			fprintf(stderr,"Invalid message received from SIM\n") ;
	}
  if (!rcvPtr) DalocMsgBuf(rcvPtr) ;
}

I_PVoid Build_OamsCfgCellhUnlockReqMsg(I_U32 cellId, I_U32 lac, I_S32 *size)
{
	OamsCfgCellhUnlockReq    *unlockReqMsg ;
	I_U16 len=0;

	len = sizeof(OamsCfgCellhUnlockReq);
	if((unlockReqMsg = (OamsCfgCellhUnlockReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }
		 
	//Filling CFG_CELLH_UNLOCK_REQ Messages
	unlockReqMsg->objId = cellId ;
	unlockReqMsg->objType = 1 ;
	unlockReqMsg->lac = lac;
        //Reason unLockReq;
        //unLockReq=reason;
        //unlockReqMsg->reason= reason;
	*size=len;
	   
	//FILL_SYS_HDR(&(unlockReqMsg->sysHdr),OAMS_CFG_TRXH_UNLOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_TRXHM,0);
	FILL_SYS_HDR(&(unlockReqMsg->sysHdr),OAMS_CFG_CELLH_UNLOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_CELLH,0);


	fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
	fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

	return  unlockReqMsg;
			
}// Build_OamsCfgCellhUnlockReqMsg Complete


I_PVoid Build_OamsCfgCellhLockReqMsg(I_U32 cellId, I_U32 lac, I_S32 *size)
{
  OamsCfgCellhLockReq    *lockReqMsg ;

  //I_U32 dinstid=0;
  I_U16 len=0;

  //printf(" Entered Inst Id = %d \n", dinstid);

  len = sizeof(OamsCfgCellhLockReq);
  if((lockReqMsg = (OamsCfgCellhLockReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_LOCK_REQ Messages
  lockReqMsg->objId = cellId ;
  lockReqMsg->objType = 1 ;
  lockReqMsg->lac = lac;
  //Reason lockReq;
  //lockReq= reason;
  //lockReqMsg->reason=lockReq;
  *size=len;

  FILL_SYS_HDR(&(lockReqMsg->sysHdr),OAMS_CFG_CELLH_LOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_CELLH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return lockReqMsg; 
}// Build_OamsCfgCellhLockReqMsg Complete


I_PVoid Build_OamsCfgCellhCellShutdownInd(I_S32 *size)
{
  OamsCfgCellhShutdownInd    *shutDwnReqMsg ;

  //I_U32 dinstid=0;
  I_U16 len=0;

  //printf(" Entered Inst Id = %d \n", dinstid);

  len = sizeof(OamsCfgCellhShutdownInd);
  if((shutDwnReqMsg = (OamsCfgCellhShutdownInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_LOCK_REQ Messages
  shutDwnReqMsg->objId = 14 ;
  shutDwnReqMsg->lac = 24 ;
  *size=len;

  FILL_SYS_HDR(&(shutDwnReqMsg->sysHdr),OAMS_CFG_CELLH_SHUTDOWN_IND, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_CELLH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return shutDwnReqMsg;                                                                                                     
}// Build_OamsCfgCellhShutdownInd Complete


I_PVoid Build_OamsCfgCellhCellBarAccess(I_S32 *size)
{
  OamsCfgCellhCellBarAccess    *cellBarMsg ;

  //I_U32 dinstid=0;
  I_U16 len=0;

  //printf(" Entered Inst Id = %d \n", dinstid);

  len = sizeof(OamsCfgCellhCellBarAccess);
  if((cellBarMsg = (OamsCfgCellhCellBarAccess *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_LOCK_REQ Messages
  cellBarMsg->cellId = 14 ;
  cellBarMsg->lac = 24 ;
  //Reason cellBar;
  // cellBar = reason;
  //cellBarMsg->reason = cellBar;
  cellBarMsg->cellBar = 1;
  *size=len;

  FILL_SYS_HDR(&(cellBarMsg->sysHdr),OAMS_CFG_CELLH_CELL_BAR_ACCESS, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_CELLH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return cellBarMsg;                                                                                                     
}// Build_OamsCfgCellhCellBarAccess Complete

I_PVoid Build_OamsCfgTrxhUnlockReqMsg(I_U32 ptrxId, I_S32 *size)
{
  OamsCfgTrxhUnlockReq    *unlockReqMsg ;

  //I_U32 dinstid=0;
  I_U16 len=0;

  //printf(" Entered Inst Id = %d \n", dinstid);

  len = sizeof(OamsCfgTrxhUnlockReq);
  if((unlockReqMsg = (OamsCfgTrxhUnlockReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }

  //Filling CFG_TRXH_UNLOCK_REQ Messages
  unlockReqMsg->objId = ptrxId ;
  unlockReqMsg->objType = 1 ;
  unlockReqMsg->e1Num = 20;
  // Reason unLockReq;
  // unLockReq=reason;
  // unlockReqMsg->reason= reason;
  *size=len;

  FILL_SYS_HDR(&(unlockReqMsg->sysHdr),OAMS_CFG_TRXH_UNLOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_TRXH,0);


  fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

  return  unlockReqMsg;

}// Build_OamsCfgTrxhUnlockReqMsg Complete


I_PVoid Build_OamsCfgTrxhLockReqMsg(I_U32 ptrxId, I_S32 *size)
{
  OamsCfgTrxhLockReq    *lockReqMsg ;

  //I_U32 dinstid=0;
  I_U16 len=0;

  //printf(" Entered Inst Id = %d \n", dinstid);

  len = sizeof(OamsCfgTrxhLockReq);
  if((lockReqMsg = (OamsCfgTrxhLockReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_LOCK_REQ Messages
  lockReqMsg->objId = ptrxId ;
  lockReqMsg->objType = 1 ;
  lockReqMsg->e1Num = 20;

  //        Reason lockReq;
  //      lockReq= reason;
  //    lockReqMsg->reason=lockReq;
  *size=len;

  FILL_SYS_HDR(&(lockReqMsg->sysHdr),OAMS_CFG_TRXH_LOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_TRXH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return lockReqMsg; 
}// Build_OamsCfgTrxhLockReqMsg Complete


I_PVoid Build_OamsCfgTrxhAddTrxReqMsg(I_U32 ptrxId, I_S32 *size)
{
  OamsCfgTrxhAddTrxReq    *addReqMsg ;

  I_U16 len=0;

  len = sizeof(OamsCfgTrxhAddTrxReq);
  if((addReqMsg = (OamsCfgTrxhAddTrxReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_ADD_TRX_REQ Messages
  addReqMsg->ptrxId = ptrxId ;

  *size=len;

  FILL_SYS_HDR(&(addReqMsg->sysHdr),OAMS_CFG_TRXH_ADD_TRX_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_TRXH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return addReqMsg;

}


I_PVoid Build_OamsCfgTrxhDelTrxReqMsg(I_U32 ptrxId, I_S32 *size)
{
  OamsCfgTrxhDelTrxReq    *deleteReqMsg ;

  I_U16 len=0;

  len = sizeof(OamsCfgTrxhDelTrxReq);
  if((deleteReqMsg = (OamsCfgTrxhDelTrxReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_ADD_TRX_REQ Messages
  deleteReqMsg->ptrxId = ptrxId ;

  *size=len;

  FILL_SYS_HDR(&(deleteReqMsg->sysHdr),OAMS_CFG_TRXH_DEL_TRX_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_TRXH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return deleteReqMsg;

}


I_PVoid Build_OamsCfgBichAddBicReqMsg(I_U32 bicId, I_S32 *size)
{
  OamsCfgBichAddBicReq    *addBicReqMsg ;

  I_U16 len=0;
  I_U32  e1Id  = gE1Id;
  I_U32  tsVal = gTsVal;
  I_S32  errCode;
  I_U32 btsType = gBtsType;
  BicTrxTimeslotUsageTableApi bicTrxTimeSlotUsageTableApi;
  BicE1TeiMapTableApi         teiMapData;

  len = sizeof(OamsCfgBichAddBicReq);
  if((addBicReqMsg = (OamsCfgBichAddBicReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_ADD_TRX_REQ Messages
  addBicReqMsg->bicId = bicId ;       
  addBicReqMsg->e1Id =e1Id;
  addBicReqMsg->e1Ts =tsVal;
  addBicReqMsg->btsType =btsType;
  addBicReqMsg->adminState = gAdminState;

  *size=len;
  bicTrxTimeSlotUsageTableApi.tsUser=SYS_NODE_TYPE_BIC;
  bicTrxTimeSlotUsageTableApi.bicOrTrxId=bicId;
  bicTrxTimeSlotUsageTableApi.e1Id=e1Id;
  bicTrxTimeSlotUsageTableApi.lapdTrxTs=(I_U8)tsVal;
  bicTrxTimeSlotUsageTableApi.numTs=(I_U8)1;
  errCode=insertBicTrxTimeslotUsageTable(&bicTrxTimeSlotUsageTableApi);
  if(errCode !=ZERO)
  {
    fprintf(stderr, "\n--------Error in insertBicTrxTimeslotUsageTable ");
  }
  teiMapData.e1Id=e1Id;
  teiMapData.e1Ts=tsVal;
  teiMapData.bicTei=e1Id+tsVal;
  errCode=insertBicE1TeiMapTable(&teiMapData);
  if(errCode !=ZERO)
  {
    fprintf(stderr, "\n--------Error in insertBicE1TeiMapTable ");
  }
  FILL_SYS_HDR(&(addBicReqMsg->sysHdr),OAMS_CFG_BICH_ADD_BIC_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_BICH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return addBicReqMsg;

}


I_PVoid Build_OamsCfgBichDelBicReqMsg(I_U32 bicId, I_S32 *size)
{
  OamsCfgBichDelBicReq    *delBicReqMsg ;

  I_U16 len=0;

  len = sizeof(OamsCfgBichDelBicReq);
  if((delBicReqMsg = (OamsCfgBichDelBicReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_ADD_TRX_REQ Messages
  delBicReqMsg->bicId = bicId ;

  *size=len;

  FILL_SYS_HDR(&(delBicReqMsg->sysHdr),OAMS_CFG_BICH_DEL_BIC_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_BICH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return delBicReqMsg;

}

I_PVoid Build_OamsCfgBichInitAbisE1Msg(I_U32 e1Id, I_S32 *size)
{
  OamsCfgBichInitAbisE1    *initAbisE1Msg ;

  I_U16 len=0;

  len = sizeof(OamsCfgBichInitAbisE1);
  if((initAbisE1Msg = (OamsCfgBichInitAbisE1 *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_ADD_TRX_REQ Messages
  initAbisE1Msg->e1Id = e1Id ;

  *size=len;

  FILL_SYS_HDR(&(initAbisE1Msg->sysHdr),OAMS_CFG_BICH_INIT_ABIS_E1, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_BICH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return initAbisE1Msg;
}

I_PVoid Build_OamsCfgBichDelAbisE1Msg(I_U32 e1Id, I_S32 *size)
{
  OamsCfgBichDeleteAbisE1    *delAbisE1Msg ;

  I_U16 len=0;

  len = sizeof(OamsCfgBichDeleteAbisE1);
  if((delAbisE1Msg = (OamsCfgBichDeleteAbisE1 *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_ADD_TRX_REQ Messages
  delAbisE1Msg->e1Id = e1Id ;

  *size=len;

  FILL_SYS_HDR(&(delAbisE1Msg->sysHdr),OAMS_CFG_BICH_DELETE_ABIS_E1, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_BICH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return delAbisE1Msg;
}

I_PVoid Build_OamsCfgBichUpdateAbisE1Msg(I_U32 e1Id, I_S32 *size)
{
  OamsCfgBichInitAbisE1    *initAbisE1Msg ;

  I_U16 len=0;

  len = sizeof(OamsCfgBichInitAbisE1);
  if((initAbisE1Msg = (OamsCfgBichInitAbisE1 *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_TRXH_ADD_TRX_REQ Messages
  initAbisE1Msg->e1Id = e1Id ;

  *size=len;

  FILL_SYS_HDR(&(initAbisE1Msg->sysHdr),OAMS_CFG_BICH_UPDATE_ABIS_E1, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_BICH,0);


  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return initAbisE1Msg;

}

I_PVoid Build_OamsCfgBichLockBicReqMsg(I_U32 bicId, I_S32 *size)
{
  OamsCfgBichLockReq   *lockReqMsg ;

  I_U16 len=0;

  len = sizeof(OamsCfgBichLockReq);
  if((lockReqMsg = (OamsCfgBichLockReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_BICH_LOCK_REQ Messages
  lockReqMsg->bicId = bicId ;
  FILL_SYS_HDR(&(lockReqMsg->sysHdr),OAMS_CFG_BICH_LOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_BICH,0);

  *size=len;
  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return lockReqMsg;

}

I_PVoid Build_OamsCfgBichUnlockBicReqMsg(I_U32 bicId, I_S32 *size)
{
  OamsCfgBichUnlockReq   *unlockReqMsg ;

  I_U16 len=0;

  len = sizeof(OamsCfgBichUnlockReq);
  if((unlockReqMsg = (OamsCfgBichUnlockReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_BICH_UNLOCK_REQ Messages
  unlockReqMsg->bicId = bicId ;
  FILL_SYS_HDR(&(unlockReqMsg->sysHdr),OAMS_CFG_BICH_UNLOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_BICH,0);

  *size=len;
  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return unlockReqMsg;

}

I_PVoid Build_OamsCfgBichAddTrxIndMsg(I_U32 bicId, I_U32 trxId, I_S32 *size)
{
  OamsCfgBichAddTrxInd   *msgPtr ;
  TrxTableApi trxData; 

  I_U16 len=0;

  len = sizeof(OamsCfgBichAddTrxInd);
  if((msgPtr = (OamsCfgBichAddTrxInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_BICH_ADD_TRX_INDICATION Messages
  msgPtr->bicId = bicId ;
  msgPtr->pTrxId = trxId ;
  trxData.ptrxId = trxId;
  trxData.adminState = LOCKED;
  trxData.trxLocation = 2;
  trxData.bicId = bicId;
  trxData.antennaID = bicId;
  trxData.trxPos = 1;
  trxData.rfPathGain = 0;
  trxData.trxPwrAction = 0;
  trxData.trxReset = 0;
  insertTrxTable ( &trxData);
  FILL_SYS_HDR(&(msgPtr->sysHdr),OAMS_CFG_BICH_ADD_TRX_INDICATION, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_BICH,0);
  *size=len;
  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return msgPtr;

}

I_PVoid Build_OamsCfgBichDelTrxIndMsg(I_U32 bicId, I_U32 trxId, I_S32 *size)
{
  OamsCfgBichDelTrxInd   *msgPtr ;

  I_U16 len=0;

  len = sizeof(OamsCfgBichDelTrxInd);
  if((msgPtr = (OamsCfgBichDelTrxInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_BICH_DEL_TRX_INDICATION Messages
  msgPtr->bicId = bicId ;
  msgPtr->pTrxId = trxId ;
  FILL_SYS_HDR(&(msgPtr->sysHdr),OAMS_CFG_BICH_DEL_TRX_INDICATION, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_BICH,0);
  *size=len;
  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return msgPtr;

}

I_PVoid Build_OamsCfgBichBmResetMsg(I_U32 bicId, I_S32 *size)
{
  OamsCfgBichBtsReset   *msgPtr ;

  I_U16 len=0;

  len = sizeof(OamsCfgBichBtsReset);
  if((msgPtr = (OamsCfgBichBtsReset *)AlocMsgBuf(len) ) == (I_Void *)NULL)
  {
    fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
    exit(0);
  }


  //Filling OAMS_CFG_BICH_BTS_RESET Messages
  msgPtr->bicId = bicId ;
  FILL_SYS_HDR(&(msgPtr->sysHdr),OAMS_CFG_BICH_BTS_RESET, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_BICH,0);
  *size=len;
  fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
  fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

  return msgPtr;

}
