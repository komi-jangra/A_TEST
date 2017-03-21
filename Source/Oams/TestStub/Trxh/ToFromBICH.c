/*se ts=2************************************File Header*****
File Name      :    ToFromBICH.c
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

I_PVoid Build_OamsBichTrxhLockIndReq(I_S32 *,I_U32 ptrxId,I_U32 bicId);
I_PVoid Build_OamsBichTrxhUnlockIndReq(I_S32 *,I_U32 ptrxId,I_U32 bicId);
I_PVoid Build_OamsBichTrxhLapdDiscIndReq(I_S32 *,I_U32 ptrxId,I_U32 bicId);
I_PVoid Build_OamsBichCfgAddBicRespMsg(I_U32 ,I_S32 *);


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

int choice;
int ptrxId;
int bicId;
int chgrId;

srcId = (int)ENT_OAMS_BICH ;

if(RegisterWithIpcFrmwrk(srcId, (I_S8 *)"ENT_OAMS_BICH")!=0)
{
	fprintf(stderr,"Counld not register with framework\n");
}


while(1)
{
fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------- \n");
fprintf(stderr, "-------->> 1.To Send OAMS_BICH_TRXH_UNLOCK_IND \n");
fprintf(stderr, "-------->> 2.To Send OAMS_BICH_TRXH_LOCK_IND \n");
fprintf(stderr, "-------->> 3.To Send OAMS_BICH_TRXH_LAPD_DISC_IND \n");
fprintf(stderr, "<<-------- 4. To_Receive data \n");
scanf("%d", &choice);

switch(choice)
{

	case 1 :
		fprintf(stderr,"--------UNLOCK_IND for PtrxId - \n");
		scanf("%d",&ptrxId);
		fprintf(stderr,"--------UNLOCK Req for BicId  - \n");
                scanf("%d",&bicId);
		printf("\n----Value of PtrxId and BicId is - %d %d\n", ptrxId,bicId); 
		bufferPtr = Build_OamsBichTrxhUnlockIndReq(&size, ptrxId,bicId);
		break;

	case 2 :
   		fprintf(stderr,"--------LOCK_IND for PtrxId - \n");
		scanf("%d",&ptrxId);
		fprintf(stderr,"--------LOCK Req for BicId  - \n");
                scanf("%d",&bicId);
		printf("\n----Value of PtrxId and BicId is - %d %d\n", ptrxId,bicId); 
		bufferPtr = Build_OamsBichTrxhLockIndReq(&size, ptrxId,bicId);
		break;

	case 3 :
   		fprintf(stderr,"--------LAPD_DISC_IND for PtrxId - \n");
		scanf("%d",&ptrxId);
		fprintf(stderr,"--------LAPD_DISC_IND for BicId  - \n");
                scanf("%d",&bicId);
		printf("\n----Value of PtrxId and BicId is - %d %d\n", ptrxId,bicId); 
		bufferPtr = Build_OamsBichTrxhLapdDiscIndReq(&size, ptrxId,bicId);
		break;

	case 4 :
		ReceiveData() ;
		break;		
	
	default :
		fprintf(stderr, "\n INVALID CHOICE \n");

}// switch choice
	if( choice == 1 || choice == 2 || choice == 3 )
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
	I_S32 		msgSize,size ;
	I_U16		msgType ;
        I_U32           bicId;
	I_PVoid 	bufferPtr ;
	I_SL32    	priority ;


	while(1)
	{
		rcvPtr = (I_PVoid)RecvMsg((int)(ENT_OAMS_BICH), &msgSize);
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
		case OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND:
			fprintf(stderr,"OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND received from TRXH\n") ;
			break ;

		case OAMS_CFG_BICH_ADD_BIC_REQ:
			fprintf(stderr,"OAMS_CFG_BICH_ADD_BIC_REQ received from TRXH\n") ;

			 /*Send ADD_BIC_RESP Msg*/
			bicId = ((OamsCfgBichAddBicReq *)rcvPtr)->bicId;
			bufferPtr = Build_OamsBichCfgAddBicRespMsg( bicId, &size);
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


I_PVoid Build_OamsBichTrxhUnlockIndReq(I_S32 *size,I_U32 ptrxId,I_U32 bicId)
{
        OamsBichTrxhUnlockInd    *ptr ;
        
        I_U16 len=0;
        len = sizeof(OamsBichTrxhUnlockInd);
        if((ptr = (OamsBichTrxhUnlockInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

	ptr->ptrxId = ptrxId ;
	ptr->bicId = bicId;

        fprintf(stderr, " Given PtrxId =%d,BicId = %d " ,ptrxId,bicId);
	*size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),OAMS_BICH_TRXH_UNLOCK_IND, 1, PRCR_CP, ENT_OAMS_BICH,0,PRCR_CP, ENT_OAMS_TRXH,0);
                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return ptr;                                                                                                     
}// Build_OamsBichTrxhUnlockIndReq Complete

I_PVoid Build_OamsBichTrxhLockIndReq(I_S32 *size,I_U32 ptrxId,I_U32 bicId)
{
        OamsBichTrxhLockInd    *ptr ;
        
        I_U16 len=0;
        len = sizeof(OamsBichTrxhLockInd);
        if((ptr = (OamsBichTrxhLockInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

	ptr->ptrxId = ptrxId ;
	ptr->bicId = bicId;

        fprintf(stderr, " Given PtrxId =%d,BicId = %d " ,ptrxId,bicId);
	*size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),OAMS_BICH_TRXH_LOCK_IND, 1, PRCR_CP, ENT_OAMS_BICH,0,PRCR_CP, ENT_OAMS_TRXH,0);
                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return ptr;                                                                                                     
}// Build_OamsBichTrxhLockIndReq Complete

I_PVoid Build_OamsBichTrxhLapdDiscIndReq(I_S32 *size,I_U32 ptrxId,I_U32 bicId)
{
        OamsBichTrxhLapdDiscInd    *ptr ;
        
        I_U16 len=0;
        len = sizeof(OamsBichTrxhLapdDiscInd);
        if((ptr = (OamsBichTrxhLapdDiscInd *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

	ptr->ptrxId = ptrxId ;
	ptr->bicId = bicId;

        fprintf(stderr, " Given PtrxId =%d,BicId = %d " ,ptrxId,bicId);
	*size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),OAMS_BICH_TRXH_LAPD_DISCONNECT_IND, 1, PRCR_CP, ENT_OAMS_BICH,0,PRCR_CP, ENT_OAMS_TRXH,0);
                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return ptr;                                                                                                     
}// Build_OamsBichTrxhLapdDiscIndReq Complete


I_PVoid Build_OamsBichCfgAddBicRespMsg(I_U32 bicId ,I_S32 *size)
{
        OamsBichCfgAddBicResp    *ptr ;
        
        I_U16 len=0;
        len = sizeof(OamsBichCfgAddBicResp);
        if((ptr = (OamsBichCfgAddBicResp *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

	ptr->result = 1;
	ptr->bicId = bicId;

        fprintf(stderr, " Given BicId = %d ",bicId);
	*size=len;

        FILL_SYS_HDR(&(ptr->sysHdr),OAMS_BICH_CFG_ADD_BIC_RESP, 1, PRCR_CP, ENT_OAMS_BICH,0,PRCR_CP, ENT_OAMS_CFG,0);
                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return ptr;                                                                                                     
}// Build_OamsBichCfgAddBicRespMsg Complete

