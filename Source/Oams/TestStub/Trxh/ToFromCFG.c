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

//#include<sysxxx_include.h>
//#include<oams_include.h>
//#include <oamscellh_include.h>
//#include<oams_msgstruct.h>

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
I_PVoid Build_OamsCfgBichUpdateAbisE1Msg(I_U32, I_S32 *);

/* Added in R2.2 */
I_PVoid Build_OamsCfgTrxhTrxResetReq(I_U32, I_S32 *);

void ReceiveData();

I_U16 srcinstG;
I_U16 CallRef;

main()
{
I_S32 count=0,size=0,i=0,result;
I_S32 srcId,dstId,interval;
I_SL32 priority;
I_U32 cellId;
I_U32 lac;
//PRIVATE struct timeval timeout = {1,0};
I_S8 buffer[100];
I_U32 ptrxId,bicId;
I_PVoid bufferPtr;
I_U32 e1Id;
int choice ;

srcId = (int)ENT_OAMS_CFG ;

if(RegisterWithIpcFrmwrk((int)ENT_OAMS_CFG, (I_S8 *)"ENT_OAMS_CFG")!=0)
{
	fprintf(stderr,"Counld not register with framework\n");
}

result = dbConnect();
if (result != 0)
{
    LOG_PRINT(CRITICAL,"BICHandler: Unable to Register itself with DBServer:Exiting");
    exit(0);
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


fprintf(stderr, "-------->> 7.To Send OAMS_CFG_TRXH_ADD_TRX_REQ \n");
fprintf(stderr, "-------->> 8.To Send OAMS_CFG_TRXH_DEL_TRX_REQ \n");

fprintf(stderr, "-------->> 9.To Send OAMS_CFG_BICH_ADD_BIC_REQ \n");
fprintf(stderr, "-------->>10.To Send OAMS_CFG_BICH_DEL_BIC_REQ \n");
fprintf(stderr, "-------->>11.To Send OAMS_CFG_BICH_INIT_ABIS_E1 \n");
fprintf(stderr, "-------->>12.To Send OAMS_CFG_BICH_UPDATE_ABIS_E1 \n");
fprintf(stderr, "-------->>13.To Send OAMS_CFG_TRXH_TRX_RESET \n");
fprintf(stderr, "<<--------14. To_Receive data \n");

scanf("%d", &choice);

switch(choice)
{

	case 1 :
		fprintf(stderr,"--------UNLOCK Req for CellId - \n");
		scanf("%d",&cellId);
		//fflush(stdin);
		fprintf(stderr,"--------UNLOCK Req for Lac - \n");
                scanf("%d",&lac);
//		printf("\n----Value of CellId and Lac is - %d %d\n", cellId,lac); 
		bufferPtr = Build_OamsCfgCellhUnlockReqMsg(cellId, lac, &size);
		break;

	case 2 :
                fprintf(stderr,"--------LOCK Req for CellId - \n");
                scanf("%d",&cellId);
                //fflush(stdin);
                fprintf(stderr,"--------LOCK Req for Lac - \n");
                scanf("%d",&lac);
		bufferPtr = Build_OamsCfgCellhLockReqMsg(cellId, lac, &size);
		break;	
	
	case 3 :
               bufferPtr = Build_OamsCfgCellhCellShutdownInd(&size); 
	       break;		

	case 4 :
		bufferPtr = Build_OamsCfgCellhCellBarAccess(&size);
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
		fprintf(stderr, "\n--------Enter PtrxId, for which this ADD Req is  - ");
		scanf("%d",&ptrxId);
                bufferPtr = Build_OamsCfgTrxhAddTrxReqMsg(ptrxId, &size);
                break;
        case 8 :
		fprintf(stderr, "\n--------Enter PtrxId, for which this DEL Req is  - ");
		scanf("%d",&ptrxId);
                bufferPtr = Build_OamsCfgTrxhDelTrxReqMsg(ptrxId, &size);
                break;
        case 9 :
		fprintf(stderr, "\n--------Enter bicId, for which this ADD Req is  - ");
		scanf("%d",&bicId);
                //bicId=0xffffffff;
                bufferPtr = Build_OamsCfgBichAddBicReqMsg(bicId, &size);
                break;
        case 10 :
		fprintf(stderr, "\n--------Enter bicId, for which this DEL Req is  - ");
		scanf("%d",&bicId);
                bufferPtr = Build_OamsCfgBichDelBicReqMsg(bicId, &size);
                break;
        case 11 :
		fprintf(stderr, "\n--------Enter e1Id, for which Init Abis E1 Request is  - ");
		scanf("%d",&e1Id);
                bufferPtr = Build_OamsCfgBichInitAbisE1Msg(e1Id, &size);
                break;
        case 12 :
		fprintf(stderr, "\n--------Enter e1Id, for which Update Abis E1 Request is  - ");
		scanf("%d",&e1Id);
                bufferPtr = Build_OamsCfgBichUpdateAbisE1Msg(e1Id, &size);
                break;
        case 13 :
		fprintf(stderr, "\n--------Enter PtrxId, for which TRX Reset Request is  - ");
		scanf("%d",&ptrxId);
                bufferPtr = Build_OamsCfgTrxhTrxResetReq(ptrxId, &size);
                break;
	case 14 :
		ReceiveData() ;
	        break ;		
	
	default :
		fprintf(stderr, "\n INVALID CHOICE \n");

     }// switch choice
	if (choice == 1 || choice == 2 ||  choice == 3 || choice == 4 || choice ==5 \
            || choice == 6 || choice == 7 || choice == 8 || choice == 9 || choice == 10 || choice == 11 || choice == 12 || choice == 13)
	{
	if (bufferPtr != NULL && size > 0)
	 {
         fprintf(stderr,"sending Ptr =%x\n",bufferPtr);
	 if(SendMsg(bufferPtr, priority, size) == SND_FAIL)
		{
		    fprintf(stderr, "\n--------msg sending failed  - ");
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
                case OAMS_TRXH_CFG_ADD_TRX_RESP:
                        fprintf(stderr,"Lock Response received from TRXH\n") ;
                        break ;
                case OAMS_TRXH_CFG_DEL_TRX_RESP:
                        fprintf(stderr,"Lock Response received from TRXH\n") ;
                        break ;
                case OAMS_BICH_CFG_ADD_BIC_RESP:
                        fprintf(stderr,"ADD_BIC_RESP received from BICH\n") ;
                        break ;
                case OAMS_BICH_CFG_DEL_BIC_RESP:
                        fprintf(stderr,"DELETE BIC RESP received from BICH\n") ;
                        break ;
                case OAMS_BICH_CFG_ALARM_IND:
                        fprintf(stderr,"Alarm received from BICH \n") ;
                        break ;
                case OAMS_TRXH_CFG_TRX_RESET_ACK:
                        fprintf(stderr,"TRX RESET ACK received from TRXH \n") ;
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
//	fprintf(stderr,"\n ---In Fun CellId is - %d",cellId);
//	fprintf(stderr,"\n--- In Fun lac is    - %d",lac);
	//I_U32 dinstid=0;
	I_U16 len=0;

	//printf(" Entered Inst Id = %d \n", dinstid);


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

I_PVoid Build_OamsCfgTrxhTrxResetReq(I_U32 ptrxId, I_S32 *size)
{
        OamsCfgTrxhTrxReset    *trxResetMsg ;

        I_U16 len=0;

        len = sizeof(OamsCfgTrxhTrxReset);
        if((trxResetMsg = (OamsCfgTrxhTrxReset *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }


        //Filling OAMS_CFG_TRXH_TRX_RESET Messages
        trxResetMsg->objId = ptrxId ;

        *size=len;

        FILL_SYS_HDR(&(trxResetMsg->sysHdr),OAMS_CFG_TRXH_TRX_RESET, 1,PRCR_CP, ENT_OAMS_CFG ,0,PRCR_CP, ENT_OAMS_TRXH,0);


        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);

        return trxResetMsg;
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
        I_U32  e1Id;
        I_U32  tsVal;
	I_S32  errCode;
        BicTrxTimeslotUsageTableApi bicTrxTimeSlotUsageTableApi;

        len = sizeof(OamsCfgBichAddBicReq);
        if((addBicReqMsg = (OamsCfgBichAddBicReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }


        //Filling OAMS_CFG_TRXH_ADD_TRX_REQ Messages
        addBicReqMsg->bicId = bicId ;
	fprintf(stderr, "\n--------Enter e1Id, for which this ADD Req is  - ");
	scanf("%d",&e1Id);
        
        addBicReqMsg->e1Id =e1Id;
	fprintf(stderr, "\n--------Enter TimeSlot, for which this ADD Req is  - ");
	scanf("%d",&tsVal);
        addBicReqMsg->e1Ts =tsVal;
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

