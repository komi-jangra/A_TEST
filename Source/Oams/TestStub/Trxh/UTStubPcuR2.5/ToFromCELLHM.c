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
#include<sysxxx_datastruct.h>
#include<syscmn_hashdefs.h>
#include<syscmn_datastruct.h>
#include<sysxxx_msgstruct.h>
#include<ipcfrm_syslog.h>
#include<ipcfrm_msgqueue.h>
#include<ipcfrm_extern.h>
#include<ipcinst_dbstruct.h>
#include<ipcinst_extern.h>
#include <bpmxxx_OAM_commonDef.h>
#include <msg_struct.h>
#include <dbsxxx_commondefs.h>
#include<csappxxx_common_datastruct.h>
#include<oamxxx_hashdefs.h>
#include<oamsxxx_typedef.h>
#include<oamsxxx_hashdef.h>
#include<oamxxx_datastruct.h>
#include<oamxxx_msgstruct.h>
#include<oams_msgstruct.h>
#include<oamsxxx_msgstruct.h>

I_PVoid Build_OamsMapentTrxhCreLtrxPtrxMapReq(I_S32 *,I_U32 ptrxId,I_U32 ltrxId,I_U32 chgrId);
I_PVoid Build_OamsMapentTrxhDelLtrxPtrxMapReq(I_S32 *,I_U32 ptrxId,I_U32 ltrxId);
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

int choice=0;
int ptrxId=0;
int ltrxId=0;
int chgrId=0;

srcId = (int)ENT_OAMS_CELLH ;

if(RegisterWithIpcFrmwrk(srcId, (I_S8 *)"ENT_OAMS_CELLH")!=0)
{
	fprintf(stderr,"Counld not register with framework\n");
}


while(1)
{
fprintf(stderr, "\n---------------- ENTER UR CHOICE -------------- \n");
fprintf(stderr, "-------->> 1.To Send OAMS_MAPENT_TRXH_CRE_LTRX_PTRX_MAPPING_REQ \n");
fprintf(stderr, "-------->> 2.To Send OAMS_MAPENT_TRXH_DEL_LTRX_PTRX_MAPPING_REQ \n");
fprintf(stderr, "<<-------- 3. To_Receive data \n");
fprintf(stderr, "<<--------give choice, ptrxId,ltrxId,chgrId  \n");
scanf("%d %d %d %d", &choice,&ptrxId,&ltrxId,&chgrId);

fprintf(stderr, " Given choice = %d, ptrxId =%d,ltrxId = %d,chgrId = %d  " , choice,ptrxId,ltrxId,chgrId);

switch(choice)
{

	case 1 : 
		bufferPtr = Build_OamsMapentTrxhCreLtrxPtrxMapReq(&size,ptrxId,ltrxId,chgrId);
		break;
	case 2 : 
		bufferPtr = Build_OamsMapentTrxhDelLtrxPtrxMapReq(&size,ptrxId,ltrxId);
		break;
	case 3 :
		ReceiveData() ;
		break;		
	
	default :
		fprintf(stderr, "\n INVALID CHOICE \n");

}// switch choice
	if( choice == 1 || choice == 2 || choice == 3)
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
		rcvPtr = (I_PVoid)RecvMsg((int)(ENT_OAMS_CELLH), &msgSize);
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
		case OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_RESP:
			fprintf(stderr,"LTRX PTRX Cre Mapping Resp received from Mapent\n") ;
			break ;

		case OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP:
			fprintf(stderr,"LTRX PTRX Del Mapping Resp received from Mapent\n") ;
			break ;

		case OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED:
			fprintf(stderr,"LTRX PTRX Cre Mapping Failed  received from Mapent\n") ;
			break ;

		default:
			fprintf(stderr,"Invalid message received from SIM\n") ;
	}
        if (rcvPtr != NULL)
	  DalocMsgBuf(rcvPtr) ;
}


I_PVoid Build_OamsMapentTrxhCreLtrxPtrxMapReq(I_S32 *size,I_U32 ptrxId,I_U32 ltrxId,I_U32 chgrId)
{
        OamsMapentTrxhCreLtrxPtrxMappingReq    *creMapRespMsg ;
        I_U16 len=0;
	I_U32 cellId;
	I_U32 lac;
	I_U16 i;
        len = sizeof(OamsMapentTrxhCreLtrxPtrxMappingReq);
        if((creMapRespMsg = (OamsMapentTrxhCreLtrxPtrxMappingReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

	creMapRespMsg->ptrxId = ptrxId ;
	creMapRespMsg->ltrxId = ltrxId;
	creMapRespMsg->chgrId = chgrId;
	creMapRespMsg->cellIndex = 1;
	fprintf(stderr, "<<--------Enter the cellId and lac  \n");
	scanf("%d %d",&cellId,&lac);
	creMapRespMsg->cellId =cellId;
	creMapRespMsg->lac = lac;
	if(ltrxId==1)
	   creMapRespMsg->chCombinationId[0]=BCCH_CCCH;
	else
	   creMapRespMsg->chCombinationId[0]=DUAL_CHANNEL;
	for(i=1;i<8;i++)
	   creMapRespMsg->chCombinationId[i]=DUAL_CHANNEL;
   
        fprintf(stderr, " Given cellId =%d,lac = %d " , cellId,lac);
	*size=len;

        FILL_SYS_HDR(&(creMapRespMsg->sysHdr),OAMS_MAPENT_TRXH_CRE_LTRX_PTRX_MAPPING_REQ, 1,PRCR_CP, ENT_OAMS_CELLH ,0,PRCR_CP, ENT_OAMS_TRXH,0);

                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return creMapRespMsg;                                                                                                     
}// Build_OamsTrxhMapentCreLtrxPtrxMappingResp Complete


I_PVoid Build_OamsMapentTrxhDelLtrxPtrxMapReq(I_S32 *size,I_U32 ptrxId,I_U32 ltrxId)
{
        OamsMapentTrxhDelLtrxPtrxMappingReq    *delMapRespMsg ;
        I_U16 len=0;
	I_U32 cellId;
	I_U32 lac;
        len = sizeof(OamsMapentTrxhDelLtrxPtrxMappingReq);
        if((delMapRespMsg = (OamsMapentTrxhDelLtrxPtrxMappingReq *)AlocMsgBuf(len) ) == (I_Void *)NULL)
        {
           fprintf(stderr,"Message Buffer Aloc. Failure for  App Begin\n");
           exit(0);
        }

	delMapRespMsg->ptrxId = ptrxId;
	delMapRespMsg->ltrxId = ltrxId;
	fprintf(stderr, "<<--------Enter the lac and cellId  \n");
	scanf("%d %d", &cellId,&lac);
	delMapRespMsg->cellId = cellId;
	delMapRespMsg->lac = lac;
        fprintf(stderr, " Given cellId =%d,lac = %d " , cellId,lac);
        
	*size=len;

        FILL_SYS_HDR(&(delMapRespMsg->sysHdr),OAMS_MAPENT_TRXH_DEL_LTRX_PTRX_MAPPING_REQ, 1,PRCR_CP, ENT_OAMS_CELLH ,0,PRCR_CP, ENT_OAMS_TRXH,0);

                                                                              
        fprintf(stderr,"Initial DP (len = %d : 0x%x) \n", len, len);
        fprintf(stderr,"Initial DP (*size = %d : 0x%x) \n", *size, *size);
                        
	return delMapRespMsg;                                                                                                     
}// Build_OamsTrxhMapentDelLtrxPtrxMapResp Complete

