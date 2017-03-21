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

I_PVoid Build_OamsTrxhCellhBcchAvailReqMsg(I_S32 *,I_U32 ptrxId,I_U8 tei,I_U32 cellId, I_U32 lac);
I_PVoid Build_OamsTrxhCellhBcchUnAvailReqMsg(I_S32 *,I_U32 ptrxId,I_U8 tei,I_U32 cellId, I_U32 lac);
I_PVoid Build_OamsTrxhMapentInitiateMap(I_S32 *,I_U32 ptrxId);
I_PVoid Build_OamsTrxhMapentCreLtrxPtrxMapResp(I_S32 *,I_U32 ptrxId,I_U32 ltrxId,I_U32 chgrId,I_U32 cellId,I_U32 lac);
I_PVoid Build_OamsTrxhMapentCreLtrxPtrxMapFailed(I_S32 *,I_U32 ptrxId,I_U32 ltrxId,I_U32 chgrId,I_U32 cellId,I_U32 lac);
I_PVoid Build_OamsTrxhMapentDelLtrxPtrxMapResp(I_S32 *,I_U32 ptrxId,I_U32 ltrxId,I_U32 cellId,I_U32 lac);
I_PVoid Build_OamsTrxhCellhSendSacchInfo(I_S32 *,I_U32 ptrxId,I_U8 tei,I_U32 cellId, I_U32 lac);
void ReceiveData();

I_U16 srcinstG;
I_U16 CallRef;

main()
{
I_S32 count=0,size=0,i=0;
I_S32 srcId,dstId,interval;
I_SL32 priority;
I_S8 buffer[100];
I_PVoid bufferPtr;

I_U32 choice=0;
I_U32 ptrxId=0;
I_U32 cellId=0;
I_U32 lac=0;
I_U32 ltrxId=0;
I_U32 chgrId=0;
I_U8  tei=0;

srcId = (int)ENT_OAMS_TRXH ;

if(RegisterWithIpcFrmwrk(srcId, (I_S8 *)"ENT_OAMS_TRXH")!=0)
{
	fprintf(stderr,"Counld not register with framework\n");
}


while(1)
{
fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------- \n");
fprintf(stderr, "-------->> 1.To Send OAMS_TRXH_CELLH_BCCH_AVAIL_MSG \n");
fprintf(stderr, "-------->> 2.To Send OAMS_TRXH_CELLH_BCCH_UNAVAIL_MSG \n");
fprintf(stderr, "-------->> 3.To Send OAMS_TRXH_MAPENT_INITIATE_MAP \n");
fprintf(stderr, "-------->> 4.To Send OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_RESP \n");
fprintf(stderr, "-------->> 5.To Send OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED \n");
fprintf(stderr, "-------->> 6.To Send OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP \n");
fprintf(stderr, "-------->> 7.To Send OAMS_TRXH_CELLH_SEND_SACCH_INFO \n");
fprintf(stderr, "<<-------- 8. To_Receive data \n");

scanf("%d", &choice);

switch(choice)
{

	case 1 :
		fprintf(stderr,"--------Enter PtrxId - \n");
		scanf("%d",&ptrxId);
		
                fprintf(stderr,"--------Enter Tei - \n");
                scanf("%d",&tei);

		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac);
 
		bufferPtr = Build_OamsTrxhCellhBcchAvailReqMsg(&size,ptrxId,tei,cellId,lac);
		break;

	case 2 :
		fprintf(stderr,"--------Enter PtrxId - \n");
		scanf("%d",&ptrxId);
		
                fprintf(stderr,"--------Enter Tei - \n");
                scanf("%d",&tei);

		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac);
 
		bufferPtr = Build_OamsTrxhCellhBcchUnAvailReqMsg(&size,ptrxId,tei,cellId,lac);
		break;	

	case 3 :
		fprintf(stderr,"--------Enter PtrxId - \n");
		scanf("%d",&ptrxId);
 
		bufferPtr = Build_OamsTrxhMapentInitiateMap(&size,ptrxId);
		break;

	case 4 :
		fprintf(stderr,"--------Enter PtrxId - \n");
		scanf("%d",&ptrxId);
		
                fprintf(stderr,"--------Enter LtrxId - \n");
                scanf("%d",&ltrxId);

                fprintf(stderr,"--------Enter ChgrpId - \n");
                scanf("%d",&chgrId);

		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac); 

		bufferPtr = Build_OamsTrxhMapentCreLtrxPtrxMapResp(&size,ptrxId,ltrxId,chgrId,cellId,lac);
		break;

	case 5 : 
		fprintf(stderr,"--------Enter PtrxId - \n");
		scanf("%d",&ptrxId);
		
                fprintf(stderr,"--------Enter LtrxId - \n");
                scanf("%d",&ltrxId);

                fprintf(stderr,"--------Enter ChgrpId - \n");
                scanf("%d",&chgrId);

		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac);

		bufferPtr = Build_OamsTrxhMapentCreLtrxPtrxMapFailed(&size,ptrxId,ltrxId,chgrId,cellId,lac);
		break;

	case 6 :
		fprintf(stderr,"--------Enter PtrxId - \n");
		scanf("%d",&ptrxId);
		
                fprintf(stderr,"--------Enter LtrxId - \n");
                scanf("%d",&ltrxId);

		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac); 

		bufferPtr = Build_OamsTrxhMapentDelLtrxPtrxMapResp(&size,ptrxId,ltrxId,cellId,lac);
		break;
	
	case 7 :
		fprintf(stderr,"--------Enter PtrxId - \n");
		scanf("%d",&ptrxId);
		
                fprintf(stderr,"--------Enter Tei - \n");
                scanf("%d",&tei);

		fprintf(stderr,"--------Enter CellId - \n");
		scanf("%d",&cellId);
		
                fprintf(stderr,"--------Enter Lac - \n");
                scanf("%d",&lac);

                bufferPtr = Build_OamsTrxhCellhSendSacchInfo(&size,ptrxId,tei,cellId,lac);
                break;
	case 8 :
		ReceiveData() ;
		break;		
	
	default :
		fprintf(stderr, "\n INVALID CHOICE \n");

}// switch choice
	if( choice == 1 || choice == 2 || choice == 3|| choice == 4 || choice == 5 ||choice == 6 || choice ==7)
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
	I_S32 		msgSize ;
	I_U16		msgType ;

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

	switch (msgType)
	{
		case OAMS_MAPENT_TRXH_CRE_LTRX_PTRX_MAPPING_REQ:
			fprintf(stderr,"LTRX PTRX Cre Mapping Req received from Mapent\n") ;
			break ;

		case OAMS_MAPENT_TRXH_DEL_LTRX_PTRX_MAPPING_REQ:
			fprintf(stderr,"LTRX PTRX Del Mapping Req received from Mapent\n") ;
			break ;

		default:
			fprintf(stderr,"Invalid message received from SIM\n") ;
	}
        if (rcvPtr != NULL)
	  DalocMsgBuf(rcvPtr) ;
}

I_PVoid Build_OamsTrxhCellhBcchAvailReqMsg(I_S32 *size,I_U32 ptrxId,I_U8 tei,I_U32 cellId,I_U32 lac)
{
	OamsTrxhCellhBcchAvail    *bcchAvailReqMsg ;
	I_U16 len=0;

	len = sizeof(OamsTrxhCellhBcchAvail);
	if((bcchAvailReqMsg = (OamsTrxhCellhBcchAvail *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }
		 
	//Filling TRXH_CELLH_BCCH_AVAIL Msg
	bcchAvailReqMsg->ptrxId = ptrxId ;
	bcchAvailReqMsg->tei = tei ;
	bcchAvailReqMsg->cellId = cellId ;
	bcchAvailReqMsg->lac = lac ;
        
	*size=len;
	FILL_SYS_HDR(&(bcchAvailReqMsg->sysHdr),OAMS_TRXH_CELLH_BCCH_AVAIL, 1,PRCR_CP, ENT_OAMS_TRXH,0,PRCR_CP, ENT_OAMS_CELLH,0);

	fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
	fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

	return  bcchAvailReqMsg;
			
}// Build_OamsTrxhCellhBcchAvailReqMsg Complete



I_PVoid Build_OamsTrxhCellhBcchUnAvailReqMsg(I_S32 *size,I_U32 ptrxId,I_U8 tei,I_U32 cellId,I_U32 lac)
{
        OamsTrxhCellhBcchUnAvail    *bcchUnAvailReqMsg ;
        I_U16 len=0;

        len = sizeof(OamsCfgTrxhLockReq);
        if((bcchUnAvailReqMsg = (OamsTrxhCellhBcchUnAvail *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        //Filling TRXH_CELLH_BCCH_UNAVAIL Msg
	bcchUnAvailReqMsg->ptrxId = ptrxId ;
	bcchUnAvailReqMsg->tei = tei ;
	bcchUnAvailReqMsg->cellId = cellId ;
	bcchUnAvailReqMsg->lac = lac ;
        
	*size=len;

        FILL_SYS_HDR(&(bcchUnAvailReqMsg->sysHdr),OAMS_TRXH_CELLH_BCCH_UNAVAIL, 1,PRCR_CP, ENT_OAMS_TRXH ,0,PRCR_CP, ENT_OAMS_CELLH,0);

        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return bcchUnAvailReqMsg;                                                                                                     
}// Build_OamsTrxhCellhBcchUnAvailReqMsg Complete


I_PVoid Build_OamsTrxhCellhSendSacchInfo(I_S32 *size,I_U32 ptrxId,I_U8 tei,I_U32 cellId,I_U32 lac)
{
        OamsTrxhCellhSendSacchInfo    *sacchReqMsg ;
        I_U16 len=0;

        len = sizeof(OamsTrxhCellhSendSacchInfo);
        if((sacchReqMsg = (OamsTrxhCellhSendSacchInfo *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        //Filling TRXH_CELLH_SEND_SACCH_INFO msg
        sacchReqMsg->ptrxId = ptrxId ;
        sacchReqMsg->tei = tei  ;
        sacchReqMsg->cellId = cellId ;
        sacchReqMsg->lac = lac ;

        *size=len;
        FILL_SYS_HDR(&(sacchReqMsg->sysHdr),OAMS_TRXH_CELLH_SEND_SACCH_INFO, 1,PRCR_CP, ENT_OAMS_TRXH,0,PRCR_CP, ENT_OAMS_CELLH,0);

        fprintf(stderr,"App Begin (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"App Begin (*size = %d : 0x%x) \n", *size, *size);

        return  sacchReqMsg;

}// Build_OamsTrxhCellhSendSacchInfo Complete


I_PVoid Build_OamsTrxhMapentCreLtrxPtrxMapResp(I_S32 *size,I_U32 ptrxId,I_U32 ltrxId,I_U32 chgrId,I_U32 cellId,I_U32 lac)
{
        OamsTrxhMapentCreLtrxPtrxMappingResp    *creMapRespMsg ;
        I_U16 len=0;

        len = sizeof(OamsTrxhMapentCreLtrxPtrxMappingResp);
        if((creMapRespMsg = (OamsTrxhMapentCreLtrxPtrxMappingResp *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        //Filling OamsTrxhMapentCreLtrxPtrxMappingResp Msg
	creMapRespMsg->ptrxId = ptrxId ;
	creMapRespMsg->ltrxId = ltrxId;
	creMapRespMsg->chgrId = chgrId;
	creMapRespMsg->cellId = cellId;
	creMapRespMsg->lac = lac;
        
	*size=len;

        FILL_SYS_HDR(&(creMapRespMsg->sysHdr),OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_RESP, 1,PRCR_CP, ENT_OAMS_TRXH ,0,PRCR_CP, ENT_OAMS_CELLH,0);

                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return creMapRespMsg;                                                                                                     
}// Build_OamsTrxhMapentCreLtrxPtrxMappingResp Complete

I_PVoid Build_OamsTrxhMapentCreLtrxPtrxMapFailed(I_S32 *size,I_U32 ptrxId,I_U32 ltrxId,I_U32 chgrId,I_U32 cellId,I_U32 lac)
{
        OamsTrxhMapentCreLtrxPtrxMappingFailed    *failedMsg ;
        I_U16 len=0;

        len = sizeof(OamsTrxhMapentCreLtrxPtrxMappingFailed);
        if((failedMsg = (OamsTrxhMapentCreLtrxPtrxMappingFailed *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }


        //Filling OamsTrxhMapentCreLtrxPtrxMappingFailed Msg
	failedMsg->ptrxId = ptrxId ;
	failedMsg->ltrxId = ltrxId;
	failedMsg->cellId = cellId;
	failedMsg->lac = lac;
	failedMsg->chgrId = chgrId;
        
	*size=len;

        FILL_SYS_HDR(&(failedMsg->sysHdr),OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED, 1,PRCR_CP, ENT_OAMS_TRXH ,0,PRCR_CP, ENT_OAMS_CELLH,0);

                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return failedMsg;                                                                                                     
}// Build_OamsTrxhMapentCreLtrxPtrxMapFail Complete

I_PVoid Build_OamsTrxhMapentDelLtrxPtrxMapResp(I_S32 *size,I_U32 ptrxId,I_U32 ltrxId,I_U32 cellId,I_U32 lac)
{
        OamsTrxhMapentDelLtrxPtrxMappingResp    *delMapRespMsg ;
        I_U16 len=0;

        len = sizeof(OamsTrxhMapentDelLtrxPtrxMappingResp);
        if((delMapRespMsg = (OamsTrxhMapentDelLtrxPtrxMappingResp *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        //Filling OamsTrxhMapentDelLtrxPtrxMapResp Msg
	delMapRespMsg->ptrxId = ptrxId;
	delMapRespMsg->ltrxId = ltrxId;
	delMapRespMsg->cellId = cellId ;
	delMapRespMsg->lac = lac ;
        
	*size=len;

        FILL_SYS_HDR(&(delMapRespMsg->sysHdr),OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP, 1,PRCR_CP, ENT_OAMS_TRXH ,0,PRCR_CP, ENT_OAMS_CELLH,0);

                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return delMapRespMsg;                                                                                                     
}// Build_OamsTrxhMapentDelLtrxPtrxMapResp Complete

I_PVoid Build_OamsTrxhMapentInitiateMap(I_S32 *size,I_U32 ptrxId)
{
        OamsTrxhMapentInitiateMap    *initiateMapReqMsg ;
        I_U16 len=0;

        len = sizeof(OamsTrxhMapentInitiateMap);
        if((initiateMapReqMsg = (OamsTrxhMapentInitiateMap *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

        //Filling OamsTrxhMapentInitiateMap Msg
	initiateMapReqMsg->ptrxId = ptrxId ;
       
	*size=len;

        FILL_SYS_HDR(&(initiateMapReqMsg->sysHdr),OAMS_TRXH_MAPENT_INITIATE_MAP, 1,PRCR_CP, ENT_OAMS_TRXH ,0,PRCR_CP, ENT_OAMS_CELLH,0);

                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return initiateMapReqMsg;                                                                                                     
}// Build_OamsTrxhMapentInitiateMap Complete

