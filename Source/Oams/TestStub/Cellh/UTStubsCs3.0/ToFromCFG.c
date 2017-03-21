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

I_PVoid Build_OamsCfgCellhUnlockReqMsg(I_U32, I_U32, I_S32 *);
I_PVoid Build_OamsCfgCellhLockReqMsg(I_U32, I_U32, I_S32 *);
I_PVoid Build_OamsCfgCellhCellShutdownInd(I_S32 *,I_U32, I_U32);
I_PVoid Build_OamsCfgCellhCellBarAccess(I_S32 *,I_U32, I_U32);
I_PVoid Build_OamsCfgCellhCsNeighCellsChange(I_S32 *,I_U32, I_U32);

I_PVoid Build_OamsCfgTrxhUnlockReqMsg(I_U32, I_S32 *);
I_PVoid Build_OamsCfgTrxhLockReqMsg(I_U32, I_S32 *);

I_PVoid Build_OamsCfgCellhAbisE1UnlockReqMsg(I_U32, I_U32, I_U32, I_S32 *);
I_PVoid Build_OamsCfgCellhAbisE1LockReqMsg(I_U32, I_U32, I_U32, I_S32 *);

void ReceiveData();

I_U16 srcinstG;
I_U16 CallRef;

main()
{
I_S32 count=0,size=0,i=0;
I_S32 srcId,dstId,interval;
I_SL32 priority;
I_U32 cellId;
I_U32 lac;
I_U32 e1Id;
I_S8 buffer[100];
I_U32 ptrxId;
I_PVoid bufferPtr;

int choice ;

srcId = (int)ENT_OAMS_CFG ;

if(RegisterWithIpcFrmwrk((int)ENT_OAMS_CFG, (I_S8 *)"ENT_OAMS_CFG")!=0)
{
	fprintf(stderr,"Counld not register with framework\n");
}


while(1)
{
fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------- \n");
fprintf(stderr, "-------->> 1.To Send OAMS_CFG_CELLH_UNLOCK_REQ \n");
fprintf(stderr, "-------->> 2.To Send OAMS_CFG_CELLH_LOCK_REQ \n");
fprintf(stderr, "-------->> 3.To Send OAMS_CFG_CELLH_SHUTDOWN_IND \n");
fprintf(stderr, "-------->> 4.To Send OAMS_CFG_CELLH_CELL_BAR_ACCESS \n");

fprintf(stderr, "-------->> 5.To Send OAMS_CFG_TRXH_UNLOCK_REQ \n");
fprintf(stderr, "-------->> 6.To Send OAMS_CFG_TRXH_LOCK_REQ \n");
fprintf(stderr, "-------->> 7.To Send OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE\n");
fprintf(stderr, "-------->> 8.To Send OAMS_CFG_CELLH_E1_UNLOCK_REQ\n");
fprintf(stderr, "-------->> 9.To Send OAMS_CFG_CELLH_E1_LOCK_REQ\n");

fprintf(stderr, "<<-------- 10. To_Receive data \n");

scanf("%d", &choice);

switch(choice)
{

	case 1 :
		fprintf(stderr,"--------UNLOCK Req for CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------UNLOCK Req for Lac - \n");
                scanf("%d",&lac);

		bufferPtr = Build_OamsCfgCellhUnlockReqMsg(cellId, lac, &size);
		break;

	case 2 :
                fprintf(stderr,"--------LOCK Req for CellId - \n");
                scanf("%d",&cellId);

                fprintf(stderr,"--------LOCK Req for Lac - \n");
                scanf("%d",&lac);

		bufferPtr = Build_OamsCfgCellhLockReqMsg(cellId, lac, &size);
		break;	
	
	case 3 :
		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac);

                bufferPtr = Build_OamsCfgCellhCellShutdownInd(&size,cellId,lac); 
                break;		

	case 4 :
		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac);

		bufferPtr = Build_OamsCfgCellhCellBarAccess(&size,cellId,lac);
		break;

        case 5 :
                fprintf(stderr, "\n--------Enter PtrxId, for which this UNLOCK Req is - ");
                scanf("%d",&ptrxId);
		bufferPtr = Build_OamsCfgTrxhUnlockReqMsg(ptrxId, &size);
		break;
        case 6 :
		fprintf(stderr, "\n--------Enter PtrxId, for which this LOCK Req is  - ");
		scanf("%d",&ptrxId);
                bufferPtr = Build_OamsCfgTrxhLockReqMsg(ptrxId, &size);
                break;
        case 7 :
		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac);

		bufferPtr = Build_OamsCfgCellhCsNeighCellsChange(&size,cellId, lac);
		break;

        case 8 :
		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac);
                
                fprintf(stderr,"--------Enter E1 Num - \n");
                scanf("%d",&e1Id);

		bufferPtr = Build_OamsCfgCellhAbisE1UnlockReqMsg(cellId, lac, e1Id , &size);
		break;

        case 9 :
		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac);

                fprintf(stderr,"--------Enter E1 Num - \n");
                scanf("%d",&e1Id);

		bufferPtr = Build_OamsCfgCellhAbisE1LockReqMsg(cellId, lac, e1Id, &size);
		break;

	case 10 :
		ReceiveData() ;
	        break ;		
	
	default :
		fprintf(stderr, "\n INVALID CHOICE \n");

     }// switch choice
	if (choice == 1 || choice == 2 ||  choice == 3 || choice == 4 || choice ==5 || choice == 6 || choice ==7 || choice == 8 || choice == 9)
	{
	if (bufferPtr != NULL && size > 0)
	 {
         fprintf(stderr,"sending Ptr =%x\n",bufferPtr);
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
	I_S32 		msgSize ;
	I_U16		msgType ;
	I_U8		entId;
	while(1)
	{
		rcvPtr = (I_PVoid)RecvMsg((int)ENT_OAMS_CFG, &msgSize);
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

		case OAMS_CELLH_CFG_E1_UNLOCK_RESP:
			fprintf(stderr,"Abis E1 UnLock Response received from CELLH\n") ;
			break ;
		case OAMS_CELLH_CFG_E1_LOCK_RESP:
			fprintf(stderr,"Abis E1 Lock Response received from CELLH\n") ;
			break ;
		default:
			fprintf(stderr,"Invalid message received from SIM\n") ;
	}
        if (rcvPtr != NULL)
	  DalocMsgBuf(rcvPtr) ;
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
	*size=len;
	   
	FILL_SYS_HDR(&(unlockReqMsg->sysHdr),OAMS_CFG_CELLH_UNLOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_CELLH,0);

	fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
	fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

	return  unlockReqMsg;
			
}// Build_OamsCfgCellhUnlockReqMsg Complete

I_PVoid Build_OamsCfgCellhAbisE1UnlockReqMsg(I_U32 cellId, I_U32 lac, I_U32 e1Id, I_S32 *size)
{
	OamsCfgCellhAbisE1UnlockReq    *abisE1UnlockReqMsg ;
	I_U16 len=0;

	len = sizeof(OamsCfgCellhAbisE1UnlockReq);
	if((abisE1UnlockReqMsg = (OamsCfgCellhAbisE1UnlockReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }
		 
	//Filling CFG_CELLH_E1_UNLOCK_REQ Messages
	abisE1UnlockReqMsg->objId = cellId ;
	abisE1UnlockReqMsg->lac = lac;
	abisE1UnlockReqMsg->e1Id = e1Id;
	*size=len;
	   
	FILL_SYS_HDR(&(abisE1UnlockReqMsg->sysHdr),OAMS_CFG_CELLH_E1_UNLOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_CELLH,0);

	fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
	fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

	return  abisE1UnlockReqMsg;
			
}// Build_OamsCfgCellhABisE1UnlockReqMsg Complete

I_PVoid Build_OamsCfgCellhAbisE1LockReqMsg(I_U32 cellId, I_U32 lac, I_U32 e1Id, I_S32 *size)
{
        OamsCfgCellhAbisE1LockReq    *abisE1LockReqMsg ;
        I_U16 len=0;

        len = sizeof(OamsCfgCellhAbisE1LockReq);
        if((abisE1LockReqMsg = (OamsCfgCellhAbisE1LockReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        //Filling OAMS_CFG_CELLH_E1_LOCK_REQ Messages
        abisE1LockReqMsg->objId = cellId ;
        abisE1LockReqMsg->lac = lac;
        abisE1LockReqMsg->e1Id = e1Id;
        *size=len;

        FILL_SYS_HDR(&(abisE1LockReqMsg->sysHdr),OAMS_CFG_CELLH_E1_LOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_CELLH,0);

        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return abisE1LockReqMsg; 
}// Build_OamsCfgCellhAbisE1LockReqMsg Complete


I_PVoid Build_OamsCfgCellhLockReqMsg(I_U32 cellId, I_U32 lac, I_S32 *size)
{
        OamsCfgCellhLockReq    *lockReqMsg ;
        I_U16 len=0;

        len = sizeof(OamsCfgCellhLockReq);
        if((lockReqMsg = (OamsCfgCellhLockReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        //Filling OAMS_CFG_CELLH_LOCK_REQ Messages
        lockReqMsg->objId = cellId ;
        lockReqMsg->objType = 1 ;
        lockReqMsg->lac = lac;
        *size=len;

        FILL_SYS_HDR(&(lockReqMsg->sysHdr),OAMS_CFG_CELLH_LOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_CELLH,0);

        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return lockReqMsg; 
}// Build_OamsCfgCellhLockReqMsg Complete


I_PVoid Build_OamsCfgCellhCellShutdownInd(I_S32 *size,I_U32 cellId,I_U32 lac)
{
        OamsCfgCellhShutdownInd    *shutDwnReqMsg ;
        I_U16 len=0;

        len = sizeof(OamsCfgCellhShutdownInd);
        if((shutDwnReqMsg = (OamsCfgCellhShutdownInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        //Filling OAMS_CFG_CELLH_SHUTDOWN nessage
        shutDwnReqMsg->objId = cellId;
        shutDwnReqMsg->lac = lac;
	*size=len;

        FILL_SYS_HDR(&(shutDwnReqMsg->sysHdr),OAMS_CFG_CELLH_SHUTDOWN_IND, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_CELLH,0);

                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return shutDwnReqMsg;                                                                                                     
}// Build_OamsCfgCellhShutdownInd Complete


I_PVoid Build_OamsCfgCellhCellBarAccess(I_S32 *size,I_U32 cellId,I_U32 lac)
{
        OamsCfgCellhCellBarAccess    *cellBarMsg ;
        I_U16 len=0;

        len = sizeof(OamsCfgCellhCellBarAccess);
        if((cellBarMsg = (OamsCfgCellhCellBarAccess *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        //Filling OAMS_CFG_CELLH_CELL_BAR_ACCESS Messages
        cellBarMsg->cellId = cellId;
        cellBarMsg->lac = lac;
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
        I_U16 len=0;

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
        *size=len;

         FILL_SYS_HDR(&(unlockReqMsg->sysHdr),OAMS_CFG_TRXH_UNLOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_TRXH,0);

        fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

        return  unlockReqMsg;

}// Build_OamsCfgTrxhUnlockReqMsg Complete


I_PVoid Build_OamsCfgTrxhLockReqMsg(I_U32 ptrxId, I_S32 *size)
{
        OamsCfgTrxhLockReq    *lockReqMsg ;
        I_U16 len=0;

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
        *size=len;

        FILL_SYS_HDR(&(lockReqMsg->sysHdr),OAMS_CFG_TRXH_LOCK_REQ, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_TRXH,0);

        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return lockReqMsg; 
}// Build_OamsCfgTrxhLockReqMsg Complete

I_PVoid Build_OamsCfgCellhCsNeighCellsChange(I_S32 *size,I_U32 cellId, I_U32 lac)
{
	OamsCfgCellhCsNeighCellsChange    *neighChange;
	I_U16 len=0;

	len = sizeof(OamsCfgCellhCsNeighCellsChange);
	if((neighChange = (OamsCfgCellhCsNeighCellsChange *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }
		 
	//Filling CFG_CELLH_UNLOCK_REQ Messages
	neighChange->cellId = cellId ;
	neighChange->lac = lac;
	*size=len;
	   
	FILL_SYS_HDR(&(neighChange->sysHdr),OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_CELLH,0);

	fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
	fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

	return  neighChange;
			
}// Build_OamsCfgCellhCsNeighCellsChange Complete
