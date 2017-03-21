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


main()
{
I_S32 srcId;

int choice ;

srcId = (int)ENT_CSAPP_MRHM ;

if(RegisterWithIpcFrmwrk((int)ENT_CSAPP_MRHM, (I_S8 *)"SND_RECV_FROM_MRHM")!=0)
{
	fprintf(stderr,"Could not register with framework\n");
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
	I_S32 		msgSize;
	I_U32		msgType;
  while(1)
  {
	rcvPtr = (I_PVoid)RecvMsg((int)(ENT_CSAPP_MRHM), &msgSize);
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
		case OAMS_CELLH_MRHM_CSNEIGHCELLS_CHANGE:
			fprintf(stderr,"OAMS_CELLH_MRHM_CSNEIGHCELLS_CHANGE received from CELLH\n") ;
			break ;
		default:
			fprintf(stderr,"Invalid Message Received\n") ;
	}
}


