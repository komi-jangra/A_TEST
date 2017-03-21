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

int choice ;

srcId = (int)ENT_OAMS_SWMH ;

if(RegisterWithIpcFrmwrk((int)ENT_OAMS_SWMH, (I_S8 *)"SND_RECV_FROM_SWMH")!=0)
{
	fprintf(stderr," SWMH Could not register with framework\n");
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
		rcvPtr = (I_PVoid)RecvMsg((int)(ENT_OAMS_SWMH), &msgSize);
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
	 switch (msgType)
	 {
		case OAMS_TRXH_SWMH_TRX_HELLO:
			fprintf(stderr,"OAMS_TRXH_SWMH_TRX_HELLO received from TRXH\n") ;
			//tei = ((OamsTrxhGrhmCreChanReq *)rcvPtr)->tei;
			break ;
		case OAMS_TRXH_SWMH_LAPD_LINK_UP:
			fprintf(stderr,"OAMS_TRXH_SWMH_LAPD_LINK_UP from Trxh\n") ;		
			//tei = ((OamsTrxhGrhmDelChanReq *)rcvPtr)->tei;
			break ;
		case OAMS_TRXH_SWMH_LAPD_LINK_DOWN:
			fprintf(stderr,"OAMS_TRXH_SWMH_LAPD_LINK_DOWN from Trxh\n") ;		
			//tei = ((OamsTrxhGrhmDelChanReq *)rcvPtr)->tei;
			break ;
		default:
			fprintf(stderr,"Invalid message received from SIM\n") ;
	 }
}






