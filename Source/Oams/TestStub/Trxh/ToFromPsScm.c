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

srcId = (int)ENT_PSSTK_PSSCM;

if(RegisterWithIpcFrmwrk(srcId, (I_S8 *)"ENT_PSSTK_PSSCM")!=0)
{
	fprintf(stderr,"Counld not register with framework\n");
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
		rcvPtr = (I_PVoid)RecvMsg((int)(ENT_PSSTK_PSSCM), &msgSize);
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
		case OAMS_TRXH_PSSCM_TRX_AVAIL:
			fprintf(stderr,"PS_SCM_AVAIL received from TRXH\n") ;		
			break ;
		default:
			fprintf(stderr,"Invalid message received from SIM\n") ;
	}
        if (rcvPtr != NULL)
	  DalocMsgBuf(rcvPtr) ;
}



