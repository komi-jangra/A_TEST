/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: bssapif_callbacks.cpp,v 1.4 2008-03-14 04:42:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.2  2007/12/23 14:21:44  bsccs2
 * LOG: Remove the Bsc cic configuration (hardcoding)
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:12:26  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:04  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.7  2007/09/28 05:39:21  amaresh.prasad
 * LOG: Updated Trace Enabled
 * LOG:
 * LOG: Revision 1.6  2007/09/28 00:16:18  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.5  2007/09/27 08:53:35  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.4  2007/09/26 09:16:55  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.3  2007/09/24 05:37:57  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/09/20 09:15:50  amaresh.prasad
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  2007/08/22 05:25:05  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:36  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.21  2007/06/07 07:51:11  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.20  2007/05/31 10:13:55  ashutosh.singh
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.19  2007/05/31 03:39:29  ashutosh.singh
 * LOG: chage for GTT
 * LOG:
 * LOG: Revision 1.18  2007/05/11 05:05:01  ashutosh.singh
 * LOG: Block the config Api for cic and BSCID
 * LOG:
 * LOG: Revision 1.17  2007/05/04 03:38:02  ashutosh.singh
 * LOG: changes for Accept thread processing in case of failure
 * LOG:
 * LOG: Revision 1.16  2007/04/18 07:53:48  ashutosh.singh
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.14  2007/04/17 08:35:36  ashutosh.singh
 * LOG: Logger Lib related changes
 * LOG:
 * LOG: Revision 1.13  2007/04/09 11:15:52  ashutosh.singh
 * LOG:  Implemet related to GTT(Callback) and remove the some harcoded value
 * LOG:
 * LOG: Revision 1.11  2007/03/06 08:03:59  cvsadmin
 * LOG: Added  the Traces
 * LOG:
 * LOG: Revision 1.10  2007/02/21 05:24:27  ashutosh.singh
 * LOG: if condition resolve for SSP and SSA
 * LOG:
 * LOG: Revision 1.9  2007/02/19 09:03:22  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.8  2007/02/19 08:55:04  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.7  2007/01/23 04:31:38  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.6  2007/01/21 04:14:21  cvsadmin
 * LOG: chnage  Ni value  from  80 to  0x80
 * LOG:
 * LOG: Revision 1.5  2007/01/17 04:31:45  ashutosh.singh
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.4  2007/01/15 10:26:17  ashutosh.singh
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.3  2007/01/11 13:52:01  ashutosh.singh
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/01/11 13:35:42  ashutosh.singh
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:32:02  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.3  2005/12/22 17:38:52  adutta
 * LOG: Can act as server with non-Accelero platform
 * LOG:
 * LOG: Revision 1.1.2.2  2005/12/21 19:49:54  adutta
 * LOG: Added Native define
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:04:35  adutta
 * LOG: Initial implementation
 * LOG:
 ****************************************************************************/
#ident "$Id: bssapif_callbacks.cpp,v 1.4 2008-03-14 04:42:25 bsccs2 Exp $"

#if !defined(WIN32)
#include <netinet/in.h>
#if defined(solaris)
#include <sys/socket.h>
#endif
#endif


#include <time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/times.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>
#include <sched.h>


#include <its.h>
#include <its++.h>
#include <its_callback.h>
#include <its_assertion.h>
#include <engine++.h>
#include<mtp3_sn.h>
#include<mtp2_cmn.h>
#include<its_thread.h>

#include <bssapif_transport.h>
#include <bssapif_trace.h>
#include <bssapif_socket.h>
#include <../Inc/bssapif_dispatcher.h>
#include <bssapif_common.h>
#include <BSSAP++.h>
  
#include <bssap_tqhandler.h>
#include <bssap_sccphandler.h>
#include <bssap_discriminator.h>
#include <bssap_timer.h>
#include <its_redundancy.h>
#include <mtp3_intern.h>
extern  "C"
{
 #include <tcap_clientapi.h>
 #include <tcap_clientimpl.h>
}
 #include <isup_variants.h>
// #include <its_sctp.h>
 #include <engine.h>
 #include <sccp_sn.h>
// #include <sctp_msgs.h>
 #include <its_route_rwlock.h>
// #include "its_sctp_impl.h"                                                              
 #include "its_sockets.h"
 #include "interface.h"
 #include "Coder.h"
 #include "trace.h"
 extern "C"
 {
   #include"GTT_Implem.h"
 }
int SwitchOver_Flag =0;/* if flag value is 1 then peer node had  joined,if flag is 2 then peer node had left */
#include <sysxxx_typedef.h>
#include <nwstkscm_hashdefs.h>
#include <nwstkscm_msgdef.h>
extern ITS_OCTET pegtrid;
extern ITS_USHORT linkTransportMapDB[MAX_LINKSETS][MAX_LINKS_PER_LINKSET];
extern "C"  int ISIL_GETNODE_STATE ();
extern "C"  int ISIL_SETNODE_STATE (ISIL_NODE_STATE state);
extern "C"  int ISIL_LinkOpreation (ISIL_NODE_STATE state);
extern "C"  int ISIL_LinkAdd (ISIL_NODE_STATE state);
extern "C" void MTP2SIM_Config ();
/*Redundnacy*/
static ISIL_STATE isilstate;

char buf_platform[16]={'\0',};
extern "C" void Stack_Health_Check(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData);

extern ITS_SEMAPHORE scm_sema;
extern ITS_SEMAPHORE mtp2_sema;
/* Added by Amaresh */
void printMsgchk(ITS_EVENT *evt);
/* Added by Amaresh */

 extern "C" ITS_OCTET GTT_ENABLE;
// extern "C" IMR_GTT_INFO gtt_info;
 extern "C" char NRET; 
 extern "C" char  NewSer_value;

#if defined (CCITT)
#define FAMILY   FAMILY_ITU
#define LSAC_Main LSAC_Main_CCITT
#else
#define FAMILY   FAMILY_ANSI
#define LSAC_Main LSAC_Main_ANSI

#endif
 
/***********************************************************************
 *  Purpose:
 *      This function is called to select the route to send the message to APP
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      id of the APP
 *
 *  Notes:
 *

*******************************************************************/

extern "C" ITS_INT LAPDIF_Init();
extern ITS_INT ReadFromApp(ITS_EVENT *event);
extern char ScmIpAddress[15];
extern int LAPDSCMServerPort;

extern "C"
{

ITS_USHORT
RouteToApp(ITS_HDR *hdr, ITS_EVENT *event)
{
    if (event->src == ITS_BSSAP_SRC)
    {
        return ITS_ISUP_SRC ;
    }
    if (event->src == ITS_GCS_EVENT_TO_NETWORK)
    {
        return ITS_MTP3_SRC;
    }
    if (event->src == ITS_RED_MODULE_SRC)
    {
        return ITS_ISUP_SRC;
    }


    ISIL_DEBUG_TRACE(("RouteToApp: Unknown source\n"));
    return ITS_NO_SRC;
}





/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is called when the App is Terminating.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/



void
BSSAPIFPostFunc(void)
{
//   Free_MemList();
   return;
}

/*************************************************************************

 *  Purpose:
 *      This function is called when the process will UP.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *


*************************************************************************/

ITS_INT
BSSAPIFPostInit(ThreadPoolThread *thr, ITS_HANDLE handle)
{
    SocketCom* sCom = SocketCom::GetInstance();
    ITS_Worker* work = (ITS_Worker *)thr;

    ISIL_DEBUG_TRACE(("BSSAPIFPostInit\n"));
    if (handle == NULL)
    {
    ISIL_DEBUG_TRACE(("BSSAPIFPostInit:Client transport init failed\n"));
    }

/*    ITS_ASSERT(handle != NULL);*/

    sCom->SetSocketTransHandle(handle);

    sCom->SetSocketTransInst(work->GetInstance());


    return (ITS_SUCCESS);
}



/*************************************************************************

 *  Purpose:
 *      This function is called when the App is Terminating.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *

*************************************************************************/


ITS_INT
BSSAPIFPostNext(ThreadPoolThread *thr, Event &event)
{
    ITS_INT count = 0;
    ITS_INT len = 0;
    BSSAPDispatcher disp;

//   ISIL_DEBUG_TRACE(("BSSAPIFPostNext\n"));
//   ISIL_DEBUG_TRACE(("BSSAPIFPostNext: Recevied event from CP:8540\n"));
#if  0 /*Amaresh  */
    for (len = 0; len < event.GetLength(); len++)
    {
        printf("%02x ", event.GetData()[len]);
    }
#endif
    disp.ProcessSocketEvent(&event);

    return (!ITS_SUCCESS);
}

/*************************************************************************

 *  Purpose:
 *      This function is called to read the configuration file.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *

*************************************************************************/


extern  "C"
{
void read_config()
{
   FILE* file;
     int len,i,j;
     int  offset =0;
     char buf[BUF_SIZE];
  char* tmp = NULL,*dup = NULL;
     char *path, *absPath;

    memset( buf, 0 , BUF_SIZE );
     absPath=(char*)malloc(sizeof(char)*100);
     path = getenv ((const char *) "CONFIG");
     strcpy(absPath, path);
     strcat(absPath,"isilconf.dat");


    // file = fopen((const char *)"../config/isilconf.dat","r");
     file = fopen(absPath,"r");
     if(file==NULL)
     {
     puts("cannot open file");
     }

     while( !feof(file) )
     {
        fgets(buf, BUF_SIZE, file);
        tmp = strchr(buf,'=');

        if( !tmp ) continue;
        *tmp = 0; tmp++;

        while(*tmp == ' ' || *tmp == '\t')
        tmp++;
        dup = tmp;

         if( (len = strlen(tmp)) == 0 )
        {
            return;
        }

        if( strstr(buf,"isupClientPort") != NULL )
        {
           isupClientPort = atoi(tmp);
           ISIL_DEBUG_TRACE(("ISUPCLIENT PORT=%d\n",isupClientPort));
        }
    else if( strstr(buf,"tcapClientPort") != NULL )
        {
           tcapClientPort = atoi(tmp);
          ISIL_DEBUG_TRACE(("TCAPCLIENT PORT=%d\n",tcapClientPort));
        }

        else if( strstr(buf,"mmClientPort") != NULL )
        {
           mmClientPort = atoi(tmp);
           ISIL_DEBUG_TRACE(("MMCLIENT PORT=%d\n",mmClientPort));
        }
        else if( strstr(buf,"ServerPort") != NULL )
        {
           ServerPort = atoi(tmp);
           ISIL_DEBUG_TRACE(("SERVER PORT=%d\n",ServerPort));

        }
        else if( strstr(buf,"LAPDSCMport") != NULL )
        {
           LAPDSCMServerPort = atoi(tmp);
           ISIL_DEBUG_TRACE(("LAPDSCMServerPort=%d\n", LAPDSCMServerPort));
        }
       else if( strstr(buf,"CPIPAddress") != NULL )
        {
           strcpy(CpIpAddress,tmp);
           ISIL_DEBUG_TRACE(("CPIP ADD=%d\n",CpIpAddress));
        }
       else if( strstr(buf,"PPIPAddress") != NULL )
        {
           strcpy(PpIpAddress,tmp);
           ISIL_DEBUG_TRACE(("PPIP ADD=%d\n",PpIpAddress));
           strcpy(ScmIpAddress, PpIpAddress);
        }
#ifdef  MTP2SIM
       else if( strstr(buf,"localPort") != NULL )
        {
           local_port[offset] = atoi(tmp);
            ISIL_DEBUG_TRACE(("LOCAL PORT=%d\n",local_port[offset]));
        }
       else if( strstr(buf,"localIP") != NULL )
        {
           strcpy(localIpAddr,tmp);
           ISIL_DEBUG_TRACE(("LOCAL IP=%d\n",localIpAddr));
        }
       else if( strstr(buf,"remotePort") != NULL )
        {
           remote_port[offset] = atoi(tmp);
           ISIL_DEBUG_TRACE(("REMOTE PORT=%d\n",remote_port[offset]));
        }

       else if( strstr(buf,"remoteIP") != NULL )
        {
           strcpy(remoteIpAddr[offset],tmp);
           ISIL_DEBUG_TRACE(("REMOTE IP=%d\n",remoteIpAddr[offset]));


		/*  one  Mtp2Sim LINK  configuration   completed  here so  increment the  offset
		    local port,  local ip , remote port, remote ip	*/	 
           offset++;
        }
#endif


        if( feof(file) )
        break;

     }
     fclose(file);
}

} /* extern  "C" */

/*************************************************************************

 *  Purpose:
 *  This is the main function are used to initilaize all the requiremnts for
    Interface layer.
    This will call  through Xml file.
 
*  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
*************************************************************************/



void
BSSAPIFPreFunc()
{   
    ITS_EVENT event;
    ITS_INT ret = ITS_SUCCESS;
    ITS_ThreadPoolEntry thrEntry;
     pthread_t Clientthread ;
     pthread_t Serverthread ;
     pthread_t  Sendthread;
     FILE* file;
     int len,i,j;
     char buf[BUF_SIZE];   
     char* tmp = NULL,*dup = NULL;   
      BSSAP_Api intf;     

       /*configuration form OAM*/

      /*intf.SetDestinations(1, 1, 2, 254, 254);
      intf.SetCIC(1, 1, 0, 100); */

     #if 0 
      printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
      printf("\nXXXXXXXXXXXXX VIHAAN NETWORKS L T D  XXXXXXXXXXXXXXXXXXXXX");

      printf("\nXXXXXX   BSC-BSSAP & BSC-APP I N T E R F A C E  L A Y E R  XXXXXXXXXXXX");

      printf("\nXXXXXX B / W   F S S  &  I N   S T A C K S   XXXXXXXXXXX");
      printf("\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    #endif
      memset( buf, 0 , BUF_SIZE );
     EnableBSSAPIFTracing();

   ROUTE_SetApplicationSelector(RouteToApp);
   LAPDIF_Init();  // To initialise LAPD 

   pthread_create(&Serverthread, NULL, Server, NULL);
   /* pthread_create(&Clientthread, NULL,Client, NULL);*/
    if ((recvQ = TQUEUETRAN_CreateTransport("ITU-ISUP", ITS_ISUP_SRC,ITS_ISUP))== NULL)
    {
       ISIL_ERROR_TRACE(("Cannot create the quee\n"));
    }

    if ((IFThread = (ITS_THREAD *)malloc(numThreads *sizeof(ITS_THREAD))) == NULL)
    {
        ISIL_ERROR_TRACE((" Couldn't create thread array\n"));
        TQUEUETRAN_DeleteTransport(recvQ);
    }

    for (i = 0; i < numThreads; i++)
    {
        if (THREAD_CreateThread(&IFThread[i], 0,ReceiveEventFromStack ,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {

            ISIL_ERROR_TRACE(("Couldn't create ISUP thread\n"));
            for (j = 0; j < i; j++)
            {
                THREAD_KillThread(&IFThread[j]);

                THREAD_DeleteThread(&IFThread[j]);
            }
            free(IFThread);


            TQUEUETRAN_DeleteTransport(recvQ);
       }

      }

  CALLBACK_AddCallback(MTP3_ManagementCallbacks, IMRMTP3TCAPMgmt, NULL);
  CALLBACK_AddCallback(MTP3_ManagementCallbacks, IMRMTP3ISUPMgmt, NULL);
  CALLBACK_AddCallback(SCCP_ManagementCallbacks, IMRSCCPMgmt, NULL);
 /* pthread_create(&Serverthread, NULL, Server, NULL);*/
//    sleep(5);
    pthread_create(&Clientthread, NULL,Client, NULL);
  //  pthread_create(&Sendthread, NULL,SEND, NULL);
 //  ROUTE_SetApplicationSelector(RouteToApp);
  
   CALLBACK_AddCallback(SCCP_GlobalTitleTranslator,IMR_GTT,NULL);
   DBC_AddDoCommand(ISIL_Console_CCITT);
  IMR_GTT_SetTransRulePerFunc();
}



/*************************************************************************

 *  Purpose: This thread are used accept the event coming from PP 
 *            stacks and check the user and write the event to
 *             correponding user socket 
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *

*************************************************************************/




THREAD_RET_TYPE
ReceiveEventFromStack(void *arg)
 {  
    ITS_INT ret,i;
    ITS_USHORT inst = 0;
    BSSAPDispatcher disp;
    ITS_EVENT ev,event,res;
    ITS_INT count;
    ITS_OCTET *buff=NULL;
    ITS_OCTET TempBuffer[10];
    NwstkScmMtp2PegResponse *Mtp2PegResponse;
    NwStkHdr hdr;
    DSM_MembershipChangeCbData_temp membershipChangeCbData;
    CALLBACK_Manager *callbackManager = NULL;
 
    ITS_Class redunClass = ITS_FindFeature (REDUNDANCY_CLASS_NAME);
    /*set the initial node state*/
      if (REDUNDANCY_GET_NODE_STATE (redunClass) != ITS_STATE_PRIMARY)
      {
           ISIL_SETNODE_STATE (ISIL_STATE_BACKUP);
      }
      else
      {
        ISIL_SETNODE_STATE (ISIL_STATE_PRIMARY);
       }

   //chages for VNL Platform
    
    for (;;)
    {

       
        memset(&ev, 0, sizeof(ITS_EVENT));

        ret = TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(recvQ))
                                                        (recvQ,
                                                         &ev);
        if (ret != ITS_SUCCESS)
        {
            continue;
        }
       if(ev.src!=ITS_RED_MODULE_SRC)
       {
         if (redunClass)
         {
           if ((REDUNDANCY_GET_NODE_STATE (redunClass) != ITS_STATE_PRIMARY) && (ev.src != ITS_MTP2_SRC))
            {

                ISIL_DEBUG_TRACE (("ISIL: Backup Node Cannot Initiate Messages. %d\n",REDUNDANCY_GET_NODE_STATE (redunClass)));
                continue;
            }
         }
      }
        ITS_Event evt(&ev);
        switch (ev.src)
        {

        /* Redundacy related event receives */
        case ITS_RED_MODULE_SRC:
            ISIL_DEBUG_TRACE (("\n\nData received at the INTERFACE LAYER : -\n"));
            ISIL_DEBUG_TRACE (("NODE STATE . %d\n",REDUNDANCY_GET_NODE_STATE (redunClass)));
           for (int i = 0; i < ev.len; i++)
           {
              //printf ("\t%02x", ev.data[i]);
           }
       if (ev.data[0] == DSM_FT_GROUP_MEMBER_LEAVE )
         {
                    SwitchOver_Flag =2;
                    ISIL_DEBUG_TRACE (("\nDSM_FT_GROUP_MEMBER_LEAVE Received at ISIL\n SwitchOver_Flag %d\n",SwitchOver_Flag));                  
                  /*  Making Active after leave as pause is not generated*/
                  callbackManager = DSM_GetMembershipChangeCallbacks(DSM_Mtp3FtGroupId);
                  if (callbackManager != NULL )
                          {
                           memset(&membershipChangeCbData,0,sizeof(DSM_MembershipChangeCbData_temp));
                           membershipChangeCbData.membershipChangeType= PLATFORM_ACT_NOTIF_EVENT;
                           ISIL_DEBUG_TRACE(("SelfCard State Change BACKUP TO ACTIVE::PEER CARD DSM_FT_GROUP_MEMBER_LEAVE \n"));
                           CALLBACK_CallCallbackList(callbackManager,NULL,(ITS_POINTER)&membershipChangeCbData);
                          }

                    //ISIL_LinkOpreation (ISIL_STATE_PRIMARY);
         }
       else if(ev.data[0] == PLATFORM_ACT_NOTIF_EVENT )
         {
              if( ev.data[1] == ISIL_STATE_PRIMARY)
              {
                   ISIL_DEBUG_TRACE (("\n:ITS_PLATFORM_ACTIVE_NOTIFICATION_EVENT at ISIL\n"));
              }
        }
       else if (ev.data[0] == PLATFORM_BKUP_NOTIF_EVENT)
        {
           if( ev.data[1] == ISIL_STATE_BACKUP)
            {
                  ISIL_DEBUG_TRACE (("\n:ITS_PLATFORM_BACKUP_NOTIFICATION_EVENT::ISIL _STATE_BACKUP"));
            }
        }
       else if (ev.data[0] == DSM_FT_GROUP_MEMBER_JOIN )
        {       SwitchOver_Flag =1      ;   
	ISIL_DEBUG_TRACE (("\nDSM_FT_GROUP_MEMBER_JOIN MEMBER JOINED at ISIL\n SwitchOver_Flag= %d\n",SwitchOver_Flag));
	}
      else
        {
                 ISIL_DEBUG_TRACE (("\nUNKNOWN NOTIFICATION EVENT"));
        }
                    ISIL_ERROR_TRACE (("For loop EXIT   FILE:%s LINE:%d\n", __FILE__, __LINE__));


    ITS_EVENT_TERM (&ev);
    break;

     /*************************MSG COMING FROM  BSSAP*********************/


        case ITS_BSSAP_SRC:
        case ITS_GCS_EVENT_FROM_STACK: 
          buff = (ITS_OCTET*)calloc(ev.len*6+1, sizeof(ITS_OCTET));

          for (count = 0; count < ev.len; count++)
           {
              sprintf((char *)TempBuffer, "0x%02x ",ev.data[count]);
              strcat((char*)buff,(const char *)TempBuffer);
              
              if (!(count % 15)&& (count!=0))
               {
                 strcat((char *)buff,"\n");
               }
           }
     
       //   ISIL_DEBUG_TRACE(("Data received from BSSAP:-\n\n%02x\n\n",buff));
          free(buff);
 
         /* for (i = 0; i < ev.len; i++)
            {
                 printf("%02x ", ev.data[i]);
            }

               printf("\n");
         */
      #if defined (DEBUG_TRACE)
            TRACE_ON(ev);
      #endif

           ITS_EVENT_TERM(&ev);
           disp.ProcessNetworkEvent(evt); 
            break;

     /*************************MSG COMING FROM  SCCP*********************/

	case ITS_SCCP_SRC:

           int result;
           if (ev.len>0)
             {
               buff = (ITS_OCTET*)calloc(ev.len*6+1, sizeof(ITS_OCTET));
  
               for (count = 0; count < ev.len; count++)
               {
                 sprintf((char *)TempBuffer, "0x%02x ",ev.data[count]);
                 strcat((char*)buff,(const char *)TempBuffer);
                 if (!(count % 15)&& (count!=0))
                 {
                   strcat((char*)buff,"\n");
                 }
               }
     
              ISIL_DEBUG_TRACE(("Data received from SCCP:-\n\n%s\n\n",buff));
              free(buff);

              /* ISIL_DEBUG_TRACE(("Data received from SCCP:--\n"));
               for (i = 0; i < ev.len; i++)
                 {
                     printf("%02x ", ev.data[i]);
                 }

                   printf("\n");
                */
             //  if (ev.data[0]==0x09||ev.data[0]==0x11||ev.data[0]==0x13)
             if (ev.data[0] == SCCP_MSG_XUDT || ev.data[0] == SCCP_MSG_LUDT
                                       || ev.data[0] == SCCP_MSG_UDT
                                            || ev.data[0] == SCCP_MSG_NOTICE || ev.data[0] == SCCP_MSG_UDTS)

                {
                   result=ISILPro_SccpMsg(&ev);
                }

       /******************MTP3 MANAGEMENT MESSAGE TO TCAP*****************/

              // else if (ev.data[0]==0x22||ev.data[0]==0x23||ev.data[0]==0x24)
               else if (ev.data[0]==ISIL_MTP3PAUSE||ev.data[0]==ISIL_MTP3RESUME||ev.data[0]==ISIL_MTP3STATUS)
                {
                   result=ISILPro_Mtp3TcapManageMsg(&ev);
                }

       /********************SCCP MANAGEMENT MESSAGE TO TCAP***************/
               else if (ev.data[0]==ISIL_SSA||ev.data[0]==ISIL_SSP||ev.data[0]==ISIL_SSC)
                {
                   result=ISILPro_SccpTcapManageMsg(&ev);
                }
             }
        break;

/*end of SCCP case in  switch*/

      /**********************MSG COMING FROM MTP3*************************/
case ITS_MTP3_SRC:

         int ret;

         if (ev.len>0)
          {
             
               buff = (ITS_OCTET*)calloc(ev.len*6+1, sizeof(ITS_OCTET));
  
               for (count = 0; count < ev.len; count++)
               {
                 sprintf((char *)TempBuffer, "0x%02x ",ev.data[count]);
                 strcat((char*)buff,(const char *)TempBuffer);
                 if (!(count % 15)&& (count!=0))
                 {
                   strcat((char *)buff,"\n");
                 }
               }
     
              ISIL_DEBUG_TRACE(("Data received from MTP3:-\n\n%s\n\n",buff));
              free(buff);
          /*
           ISIL_DEBUG_TRACE(("Data received from MTP3:--\n"));
           for (i = 0; i < ev.len; i++)
            {
              printf("%02x ", ev.data[i]);
            }
              printf("\n");
            */

             // if(ev.data[0]==0x21)
              if(ev.data[0]==ISIL_USRDATA)
              {
                ret=ISILPro_Mtp3Msg(&ev);
              }

              else
              {
                ret=ISILPro_Mtp3IsupManageMsg(&ev);
              }

          }/*end of IF*/
        break;
        case ITS_DEFAULT_SRC:
           ISIL_DEBUG_TRACE (("BSSAP_MSG_PROTOCOL_ERROR:Have Send >>>"));
           ev.src = ITS_BSSAP_SRC;
           ret = CL_WriteEventMM (CL_Handle_MM, &ev);
           if (ret != ITS_SUCCESS)
           {
                CL_Handle_MM = NULL;
                ITS_EVENT_TERM (&ev);
           }
         break;
         case ITS_MTP2_SRC:
             hdr.len=sizeof(NwstkScmMtp2PegResponse);
             hdr.appid=160;
             hdr.opcode=NWSTK_SCM_MTP2_PEG_RESP;
             hdr.trid=pegtrid;

             memcpy(&ev.data[0],&hdr,sizeof(NwStkHdr));
             ISIL_DEBUG_TRACE(("Len=%d\n",ev.len));
             ret=CL_WriteEventSCM(CL_Handle_SCM,&ev);
             if(ret!=ITS_SUCCESS)
             {
                ISIL_ERROR_TRACE(("Mtp2Pegsreponse :SCM Write Event Fail"));
                ITS_EVENT_TERM(&ev);
             }
              pegtrid=0;
          break;
        default:
             ISIL_ERROR_TRACE(("ReceiveEventFromStack:Unknown event received from stack\n"));
            break;

        }
       
      /*  ITS_EVENT_TERM(&ev);*/
    }
    MTP3_DisableUserPart(MTP3_SIO_ISUP);

    THREAD_NORMAL_EXIT;
}


/*************************************************************************

 *  Purpose:
 *  Server thread open the socket and wait in the accept.

 *  All PP server-CP client connection handle put in the array.
 *
  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
**************************************************************************/

ITS_SocketInfo *connections[MAX_CON];
void *Server(void  *args)
{

    int i;
    ITS_SocketInfo *sock1;
    ITS_SocketInfo *tmpsock;
    char count=0;

    /* connections array initalised with NULL values*/
     for(i=0;i<MAX_CON;i++)
     {

	connections[i] = NULL;
     } 


    if (SOCK_ServerOpen(&sock1,INET_DOMAIN,PpIpAddress,ServerPort) != ITS_SUCCESS)
    {
        ISIL_ERROR_TRACE(("Server Socket Open to USER FAIL=%d\n",ServerPort));

    }
    else
    {
     ISIL_DEBUG_TRACE(("Open the Server with ISIL USER=%d\n",ServerPort));

    }

   if (THREAD_CreateThread(&thread, 0, Receive, NULL,ITS_TRUE) != ITS_SUCCESS)
  {
       ISIL_ERROR_TRACE(("Receive Thread From USER FAIL\n"));

    }
   while(1)
   {
     if(SOCK_ServerAccept(sock1,&tmpsock)==ITS_SUCCESS)
     {
       ISIL_DEBUG_TRACE(("New Connection Accepted on server <%d> \n",ServerPort));
       add_connection(tmpsock);
     }
     else
     {
       if(count<=2)
       {
       ISIL_ERROR_TRACE(("THE Server  Return  ERROR , Running  on PORT <%d> \n",ServerPort));
        count++;
       }
       else
       {
        exit(1);        
       }

     }

   }

   return 0;

}




/*****************************************************************************************
 *  Purpose: Receive thread are using the select function to return the fd
 *            for the particular socket connection and  receives  the event
 *            from the socket and will process it
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

******************************************************************************************/


void *Receive(void *args)

{
    ITS_EVENT evt,syn_event;
    ITS_EVENT*event;
    ITS_INT ret=0;
    ITS_SockPollInfo fds[MAX_FD]; 
    unsigned char count,offset;
    ITS_UINT i=0; 


    while (1)
    {
      int ret;
       offset =0;

	for(count=0;count<MAX_CON;count++)
    	{
	  if(connections[count] != NULL)
          {	
 	   fds[offset].sinfo= connections[count];
           fds[offset].lookFor =SOCK_POLL_READ | SOCK_POLL_READ_OOB;
           offset++; 
          }
    	}
         
        ret =IMRSOCK_Poll(fds,offset,1000);
        
        if (ret > 0)
        {
		
	  for(count=0;count<offset;count++)
    	  {
             if (fds[count].wasSet)
             {
	       if((fds[count].wasSet & SOCK_POLL_READ) == SOCK_POLL_READ)
                {	
                  if(ReadEvent(fds[count].sinfo,&evt) == ITS_SUCCESS)
                   {
                       if(ProcessMsg(&evt) !=ITS_SUCCESS)
                       ISIL_ERROR_TRACE(("message processing failed\n")); 
                   }
                   else
                    {  
                      /* this will make the connection NULL which having read  error */ 
	                for(i =0; i<MAX_CON;i++)
                          {
                            if(fds[count].sinfo == connections[i])
                              {
            	  		 ISIL_DEBUG_TRACE(("connections[i]=%x\n", connections[i]));
                                 close_connection(connections[i]);			
                                  connections[i]= NULL; 
                                    
                                  break;
                               }
                           }
                          if(CL_Handle_ISUP==NULL&&ISUPFLAG==1)
                          {
                           ISIL_WARNING_TRACE(("ISUP DEREGISTERED\n"));
                           MTP3_DisableUserPart(MTP3_SIO_ISUP);
                           ISUPFLAG=0;
                          /* ssn=0;*/
                           //printf("%x",ISUPFLAG); 
                          }
                          if(CL_Handle_TCAP==NULL&&TCAPFLAG==1)
                          {
                           ISIL_WARNING_TRACE(("TCAP DEREGISTERED\n"));
          /*               IMRSCCP_DisableUserPart(SCCP_SSN_MAP);
                           IMRSCCP_DisableUserPart(SCCP_SSN_HLR);
                           IMRSCCP_DisableUserPart(SCCP_S:xSN_VLR);*/
                           //printf("%x",TCAPFLAG); 
                          }
                    }
                 }  
	         if((fds[count].wasSet & SOCK_POLL_ERROR) == SOCK_POLL_ERROR)
                  {	
	               for(i =0; i<MAX_CON;i++)
                          {
                            if(fds[count].sinfo == connections[i])
                              {
				 close_connection(connections[i]);			 
                                  connections[i]= NULL;  
                                  break;
                               }
                           }

                   }
	           if((fds[count].wasSet & SOCK_POLL_WRITE) == SOCK_POLL_WRITE)
                   ISIL_WARNING_TRACE((" Write  Flag set in Fds\n")); 
               }


   

         }               
      }
      else if (ret < 0)
      {
          ISIL_ERROR_TRACE((" IMRSOCK_Poll return [%d]\n",ret)); 
	         for(count=0;count<MAX_CON;count++)
           {
            ISIL_ERROR_TRACE(("ALL FDS connections[%d]=%x\n",count,connections[count])); 
           }

      }
  }                     /*end of while loop*/
}                       /*end of receive func*/  
       

    

/*************************************************************************

 *  Purpose: This function is used to read event from the socket i.e from user.
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

*******************************************************************************************/
int ReadEvent(ITS_SocketInfo *info, ITS_EVENT *evt)
{

 ITS_EVENT syn_event;
 ITS_EVENT *event;
 int nread = 0, ret =0,i;
 unsigned short len;
 unsigned char  buffer[TCAP_HEADER];
 ITS_SocketInfo *handle=(ITS_SocketInfo*)info;
 ITS_OCTET *buff;
 ITS_OCTET TempBuffer[10];
 ITS_INT count ,Ret=0;
 static ITS_INT cnt=0;


    if (evt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

        evt->len =0;
    MUTEX_AcquireMutex(&CL_ReadMutexLock);

   // ret = SOCK_NonBlockingRead(handle,(char *)buffer,5,5);
    ret = SOCK_NonBlockingRead(handle,(char *)buffer,TCAP_HEADER,TCAP_HEADER);
    //if (ret != 5)
    if (ret != TCAP_HEADER)
     {
         MUTEX_ReleaseMutex(&CL_ReadMutexLock);
         return (ITS_ERCVFAIL);

     }

 /*     printf("\n\nISIL_Trace: Data received from user:--\n\n");

    printf(" api_id=%d\t", buffer[0]);
    printf(" api.ver=%d\t",  buffer[1]);
    printf(" element=%d\t",  buffer[2]);*/
    len  =  buffer[3] | buffer[4] << 8;
   // printf(" len =%d\t", (len));
   if(buffer[1]==SCM_REGMSG)
    {
       CL_Handle_SCM=handle;
      if(cnt==0)
      {
         Ret=SEMA_CreateSemaphore(&scm_sema, 0);
         if(Ret!=ITS_SUCCESS)
          {
          }
         else
          {
             ISIL_DEBUG_TRACE (("Scm_sema:SEMA Create Sucess"));
          }
         Ret=SEMA_CreateSemaphore(&mtp2_sema, 0);
         if(Ret!=ITS_SUCCESS)
          {
          }
         else
          {
             ISIL_DEBUG_TRACE (("mtp2_sema::SEMA Create Sucess"));
          }
      }
      cnt++;

    }
 

    evt->data = (ITS_OCTET *)ITS_Malloc(len );
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&CL_ReadMutexLock);
        return (ITS_ENOMEM);
    }
    evt->len= len ;
   // memcpy(evt->data ,(char *)buffer  ,5);
    memcpy(evt->data ,(char *)buffer  ,TCAP_HEADER);
//    nread = SOCK_NonBlockingRead(handle, (char *)(evt->data + 5), len-5 ,5);
    nread = SOCK_NonBlockingRead(handle, (char *)(evt->data +TCAP_HEADER ), len-TCAP_HEADER ,TCAP_HEADER);

    ISIL_DEBUG_TRACE (("Data received from USER:-\n\n\n\n"));
    if(evt->data[0] == 0xa0)
    {
          buff = (ITS_OCTET *) calloc (evt->len * 6 + 1, sizeof (ITS_OCTET));
          for (count = 0; count < evt->len; count++)
          {
              sprintf ((char *) TempBuffer, "0x%02x ", evt->data[count]);
              strcat ((char *) buff, (const char *) TempBuffer);
              if (!(count % 15) && (count != 0))
              {
                strcat ((char *) buff, "\n");
              }
         }
      ISIL_DEBUG_TRACE (("Data received from SCM:-\n\n%s\n\n", buff));
      free (buff);

    }


    //if (nread != len-5)
    if (nread != len-TCAP_HEADER)
    {
      ITS_Free(evt->data);
      evt->data = NULL;
      MUTEX_ReleaseMutex(&CL_ReadMutexLock);
      return (ITS_ERCVFAIL);
    }
    return ITS_SUCCESS;

}

/******************************************************************************

 * Purpose: This function process the receive messag recieve  from  user 
 *           by read()function
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

******************************************************************************/

int ProcessMsg(ITS_EVENT *evt)
{

  unsigned char*buffer;
  ITS_EVENT event;
  ITS_INT ret = ITS_SUCCESS;
  ITS_INT i;
  BSSAPDispatcher disp; 
  buffer =  evt->data;
  ITS_OCTET index=0;
  ITS_INT count;
  ITS_OCTET *buff;
  ITS_OCTET TempBuffer[10];

/*********************FOR APP To LAPD ********************/

 if(buffer[0] == 0xc2)	    // Api id for LAPD
 {
    ReadFromApp(evt);
    MUTEX_ReleaseMutex(&CL_ReadMutexLock);
    ITS_EVENT_TERM(evt);
    return ITS_SUCCESS;
 }

/*********************FOR ISUP TO MTP3********************/
  
// if(buffer[0]==0x1b )
 if(buffer[0]==ISIL_ISUP_ID2)
 {
  
   buff = (ITS_OCTET*)calloc(evt->len*6+1, sizeof(ITS_OCTET));

   for (count = 0; count < evt->len; count++)
    {
       sprintf((char *)TempBuffer, "0x%02x ",evt->data[count]);
       strcat((char*)buff,(const char *)TempBuffer);
        if (!(count % 15)&& (count!=0))
         {
          strcat((char*)buff,"\n");
         }
       }
     
    ISIL_DEBUG_TRACE(("Data received from ISUP:-\n\n%s\n\n",buff));
    free(buff);

/*  ISIL_WARNING_TRACE(("Data received from ISUP:-\n"));
  for (i = 0; i < evt->len; i++)
   {
      printf("%02x ", evt->data[i]);
   }
   printf("\n");
 */
  if(evt->len >0)
   {
     ISILPro_IsupMsg(evt);
   }

 }/*end of buffer[0] check*/


/*********************FOR MAP TO SCCP***********************/


 //else if(buffer[0]==0xa7)
 else if(buffer[index]==ISIL_TCAP_ID2)
 {
 if (evt->len >0)
      {
        ISILPro_TcapMsg(evt);

      }/*end of if*/


 }/*end of MAP DATA*/ 


/****************BSSAP DATA from BSC-APP************************/



// else if(buffer[0]==0xc1) 
 else if(buffer[index]==ISIL_BSSAP_ID2) 
 { 
/* Added by Amaresh for print msg type & data  */
        ISIL_DEBUG_TRACE(("RECEIVED DATA FROM CP(BSC->APP)  >>>>>>"));
         printMsgchk(evt);
/* Addition completed by Amaresh for print msg type & data  */

 ISILPro_MMMsg(evt);

 }
 
 /************************for enable ISUP *******************************/



// else if(buffer[0]==0x1a) 
 else if(buffer[index]==ISIL_ISUPREG_ID) 
 {

     ITS_EVENT_TERM(evt);
 }
 /********************for enable MAP VLR and HLR**************************/

// else if(buffer[0]==0xa6) 
 else if(buffer[0]==ISIL_MAPUSREG_ID) 
 {
   buff = (ITS_OCTET*)calloc(buffer[3]*6+1, sizeof(ITS_OCTET));

   for (count = 0; count < buffer[3]; count++)
    {
       sprintf((char *)TempBuffer, "0x%02x ",evt->data[count]);
       strcat((char*)buff,(const char *)TempBuffer);
        if (!(count % 15)&&(count!=0))
         {
          strcat((char*)buff,"\n");
         }
    }
    ISIL_DEBUG_TRACE(("Register message from TCAP:-\n\n%s\n\n",buff));
    free(buff);

  #if defined(CCITT)
   ssn[counter]=evt->data[7];
   #elif defined(ANSI)
   ssn[counter]=evt->data[8];
   #endif
    USRREGISTER_FLAG=1;
    counter++;
    ITS_EVENT_TERM(evt);
    
 }
 /*****************N STATE REQUEST from TCAP to SCCP************************/

//else if(buffer[0]==0xb7)
else if(buffer[index]==ISIL_NSTATE_REQ)
 { 
      ITS_EVENT eve; 
     // ITS_EVENT_INIT(&eve,ITS_TCAP_SRC,((evt->len)-5)*sizeof(ITS_OCTET));
      ITS_EVENT_INIT(&eve,ITS_TCAP_SRC,((evt->len)-TCAP_HEADER)*sizeof(ITS_OCTET));

  #if defined(CCITT)
     
      if(evt->data[3]==0)/*User in service*/
      {
       /*Send SSA to Network by using the IN api SCCP_SendSCMG message*/
      }
      if(evt->data[3]==1)/*User out of service*/
       {     
       /*Send SSP or SST  to Networkby using the IN api SCCP_SendSCMG message*/
       }

  #elif defined(ANSI)

      if(evt->data[4]==0)/*User in service*/
      {
       /*Send SSA to Network by using the IN api SCCP_SendSCMG message*/
      }
      if(evt->data[4]==1)/*User out of service*/
       {     
       /*Send SSP or SST  to Network  by using the IN api SCCP_SendSCMG message*/
       }

 #endif 

     ITS_EVENT_TERM(&eve);
  }
     else if(buffer[index]==SCM_APPID)
      {
         if(buffer[1]==SCM_REGMSG)
          {
             ISIL_DEBUG_TRACE(("Register message from SCM"));
             ITS_EVENT_TERM(evt);
          }
        else
          {
              ISILPro_SCMMsg(evt);
          }
      }

   /* Free the event
    if (evt->data)
    {
        free(evt->data);
        evt->data=0;
    
    }*/

   MUTEX_ReleaseMutex(&CL_ReadMutexLock);
   return ITS_SUCCESS;
}




/******************************************************************************

 * Purpose: This function is used to select the scoket interafce from where message is coming 
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************************/


int
IMRSOCK_Poll(ITS_SockPollInfo *socks,int nsocks,int usecs)
{
    int i;
    fd_set reads, writes,errors;
    int ret, max;

    if (nsocks == 0 ||
        (usecs == SOCK_POLL_WAIT_FOREVER && nsocks == 0))
    {
        sleep(5);
        return  -1;
       /* return (ITS_EINVALIDARGS);*/
    }

    FD_ZERO(&reads);
    FD_ZERO(&writes);
    FD_ZERO(&errors);

    max = 0;
    for (i = 0; i < nsocks; i++)
    {
        socks[i].wasSet = 0;

        if ((int)socks[i].sinfo->socket > max)
        {
            max = socks[i].sinfo->socket;
        }

        if (socks[i].lookFor & (SOCK_POLL_READ|SOCK_POLL_READ_OOB))
        {
            FD_SET(socks[i].sinfo->socket, &reads);
        }

        if (socks[i].lookFor & (SOCK_POLL_WRITE|SOCK_POLL_WRITE_OOB))
        {
            FD_SET(socks[i].sinfo->socket, &writes);
        }

        if (socks[i].lookFor & (SOCK_POLL_ERROR|SOCK_POLL_ERROR_OOB))
        {
            FD_SET(socks[i].sinfo->socket, &errors);
        }
    }

    if (max > 0)
    {
        max++;
    }

    if (usecs == SOCK_POLL_WAIT_FOREVER)
    {
        ret = select(max, &reads, &writes, NULL, NULL);
    }
    else
    {
        struct timeval tv;

        tv.tv_sec = usecs / USEC_PER_SEC;
        tv.tv_usec = usecs % USEC_PER_SEC;

        ret = select(max, &reads, &writes, NULL, &tv);
    }
/*   ret = select(max, &reads, &writes, &errors, NULL);*/


    if (ret< 0)
    {
        return (ret);
    }
    if (ret == 0)
    {
        return (ret);
    }

     
    for (i = 0; i < nsocks; i++)
    {
        if (FD_ISSET(socks[i].sinfo->socket, &reads))
        {
            socks[i].wasSet |= SOCK_POLL_READ;
        }
        if (FD_ISSET(socks[i].sinfo->socket, &writes))
        {
            socks[i].wasSet |= SOCK_POLL_WRITE;
        }
        
        if (FD_ISSET(socks[i].sinfo->socket, &errors))
        {
            socks[i].wasSet |= SOCK_POLL_ERROR;
        }
    }


    return (ret);
}

/*********************************************************************************
 * Purpose:This function are used to maintain the PP client connetion and retry 
 *          the connection in case of failure.

 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

*********************************************************************************/

void *Client(void *args)
{
  int ret;
  ITS_EVENT event;
 
  while(1)
  {     
   	if(CL_Handle_ISUP==NULL)
    	{
	    /*  ISUP interface  not required  in  BSC */	
	     CL_Handle_ISUP=NULL;

#if  0		
     		ret = InitClientIsup();
     		if (ret == ITS_SUCCESS)
      		{
 		        ISIL_DEBUG_TRACE(("Clinet_Thread:ISUP Client Initialization success\n"));
                        MTP3_EnableUserPart(MTP3_SIO_ISUP, ITS_ISUP_SRC);
		        ISUPFLAG=1;    
      		}	
     		else
      		{
		  // ISIL_DEBUG_TRACE(("Clinet_Thread:ISUP Client Initialization failed\n"));
                   CL_Handle_ISUP=NULL;
         
       		}
#endif 
     	}/*end of check ISUP handle*/

	if(CL_Handle_TCAP==NULL) 
    	{
		ret = InitClientTcap();
		if (ret == ITS_SUCCESS)
     		{


                       ISIL_DEBUG_TRACE(("Clinet_Thread:TCAP Client Initialization success\n"));
		       SCCP_EnableUserPart(SCCP_SSN_MSC, ITS_ISUP_SRC);
		       SCCP_EnableUserPart(SCCP_SSN_EIR, ITS_ISUP_SRC);
		       SCCP_EnableUserPart(SCCP_SSN_MAP, ITS_ISUP_SRC);
		       SCCP_EnableUserPart(SCCP_SSN_VLR, ITS_ISUP_SRC);
		       SCCP_EnableUserPart(SCCP_SSN_HLR, ITS_ISUP_SRC);
                       SCCP_EnableUserPart(ISIL_SSN_CAP1, ITS_ISUP_SRC);
                       SCCP_EnableUserPart(ISIL_SSN_CAP2, ITS_ISUP_SRC);

                       TCAPFLAG=1;
		 }
     		else
     		{
		    //ISIL_DEBUG_TRACE(("Clinet_Thread:TCAP Client Initialization failed\n"));
                    CL_Handle_TCAP=NULL;
        
     		}
   	}/*end of TCAP Handle check*/
   

	if(CL_Handle_MM==NULL)
   	{      
		ret = InitClientMM();
		if (ret == ITS_SUCCESS)
     		{
                  ISIL_DEBUG_TRACE(("Clinet_Thread:MM Client Initialization success\n"));
                }
     		else
     		{
		//     ISIL_DEBUG_TRACE(("Clinet_Thread:MM Client Initialization failed\n"));
                     CL_Handle_MM=NULL;
        
     		}
    	} /*end of M Handle check*/


        sleep(5);
   }
} /* Client end */ 


/**************************************************************************
 * Purpose:This are used to close the socket connection if its breaks
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
**************************************************************************/

void  close_connection(ITS_SocketInfo *connect)
{
	 unsigned char i;
	if(connect !=NULL)
	{
	if(connect == CL_Handle_ISUP)
	 {
           ISIL_WARNING_TRACE(("close_connection:ISUP Socket closed=%d\n")); 
           CL_Handle_ISUP =NULL;
	 }
	else
	 {
		if(connect == CL_Handle_TCAP)
		 {
                  ISIL_WARNING_TRACE(("close_connection:TCAP Socket closed=%d\n"));
                  CL_Handle_TCAP =NULL;
              
                 }
		 else
		  {		
			if(connect == CL_Handle_MM)
			 {
                          ISIL_WARNING_TRACE(("close_connection:MM Socket closed=%d\n"));
                          CL_Handle_MM =NULL;
			 }
		  }
	 }
	}
       SOCK_Close(connect);
	

}


/*************************************************************************
 * Purpose:This function are used to maintain the socket fds .
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*************************************************************************/



void  add_connection(ITS_SocketInfo *connect)
{
	 unsigned char i;



	MUTEX_AcquireMutex(&CON_WriteMutexLock);

	for(i=0; i<MAX_CON;i++)
     	{

       		if(connections[i] == NULL)
        	{
          		connections[i] =connect;
                       ISIL_DEBUG_TRACE(("add_connection:connections[i]=%x\n",connections[i])); 
          		break;
        	}
     	}
     	if(i==MAX_CON)
        ISIL_WARNING_TRACE(("add_connection:No location free for  new ENTRY  of handle\n"));
	MUTEX_ReleaseMutex(&CON_WriteMutexLock);


}/*end of add_connection func*/


/***************************************************************************
 * Purpose: MTP3 managemnet callfuction to process the MTP3 management messages
 *   for ISUP
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
***************************************************************************/


void
IMRMTP3ISUPMgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ITS_EVENT* ev = (ITS_EVENT *)callData;
    ITS_EVENT tmp;
    ev->src=ITS_MTP3_SRC;
    ITS_EVENT_INIT(&tmp, ev->src, ev->len);
    memcpy(tmp.data, ev->data, ev->len);

    if (TRANSPORT_PutEvent(ITS_ISUP_SRC, ev) != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&tmp);
    }
    else
    {
        *ev = tmp;
    }
}/*end of IMRMTP3ISUP func*/



/***************************************************************************
 * Purpose: MTP3 management callfuction to process MTP3 management messages
 *           for TCAP 
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:


***************************************************************************/

void
IMRMTP3TCAPMgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ITS_EVENT* ev = (ITS_EVENT *)callData;
    ITS_EVENT tmp;
 

     ev->src=ITS_SCCP_SRC;
    ITS_EVENT_INIT(&tmp, ev->src, ev->len);
    memcpy(tmp.data, ev->data, ev->len);

    if (TRANSPORT_PutEvent(ITS_ISUP_SRC, ev) != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&tmp);
    }
    else
    {
        *ev = tmp;
    }
}/*end of IMRMTP3TCAPMgnt func*/





/***************************************************************************
 * Purpose:  SCCP  managemnet callfuction to process the SCCP management message
 *            for TCAP
 * 
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
***************************************************************************/

 void
IMRSCCPMgmt(ITS_POINTER object, ITS_POINTER userData,
                      ITS_POINTER callData)
{
    ITS_EVENT *event = (ITS_EVENT*)callData;
    ITS_SCCP_IE ies[32];
    ITS_HDR hdr;
    int ieCount;
    ITS_OCTET *scmgData = NULL;
    ITS_USHORT dlen = 0;
    ITS_EVENT ev;
    ITS_USHORT PC=0;
    ITS_OCTET index=0;
    //printf("SCCPMgmtHandler\n");
   #if defined MTP3_MANAGE_REQ

   // if(event->data[0]==0x22)
    if(event->data[index]==ISIL_MTP3PAUSE)
     {

     }
   // if(event->data[0]==0x23)
    if(event->data[index]==ISIL_MTP3RESUME)
     {


     }
   // if(event->data[0]==0x24)
    if(event->data[index]==ISIL_MTP3STATUS)
     {

     }
   #endif
    
    if (SCCP_MSG_TYPE(event) != SCCP_MSG_UDT)
    {
    //printf("ISIL_Trace SCCPMgmtHandler\n");
    // ISIL_DEBUG_TRACE(("IMRSCCPMgmt:Is Not the UDT Message\n"));
    }
    else
    {
        if (SCCP_ReceiveUnitData((ITS_HANDLE)ISS7_Stack,
                                 event,&hdr, ies,
                                 &ieCount) != ITS_SUCCESS)
        {
     	 //printf("SCCPMgmtHandler\n");
           ISIL_ERROR_TRACE(("IMRSCCPMgmt:SCCPMgmtHandler fail \n"));
            return;
        }

        for (int i=0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_DATA)
            {
                scmgData = ies[i].param_data.userData.data;
                dlen = ies[i].param_length;
            }
        }
         ITS_EVENT_INIT(&ev,ITS_SCCP_SRC,dlen*sizeof(ITS_OCTET));
       {
        ev.data[index++] = ((SCCP_SCMG *)scmgData)->type;
        ev.data[index++]= ((SCCP_SCMG *)scmgData)->ssn;
	#if defined(CCITT)   
	ev.data[index++]=((SCCP_SCMG *)scmgData)->pointCode.data[0];
        ev.data[index++]=((SCCP_SCMG *)scmgData)->pointCode.data[1];
        ev.data[index++] = ((SCCP_SCMG *)scmgData)->multiplicity;
	PC=ev.data[2]|ev.data[3]<<8;
	#elif defined(ANSI)
    
	ev.data[2]=((SCCP_SCMG *)scmgData)->pointCode.data[0];
        ev.data[3]=((SCCP_SCMG *)scmgData)->pointCode.data[1];
        ev.data[4]=((SCCP_SCMG *)scmgData)->pointCode.data[2];
        ev.data[5] = ((SCCP_SCMG *)scmgData)->multiplicity;
        #endif
       }  
        switch (ev.data[0])
        {
	    case SCCP_SCMG_SS_ALLOWED:
                 ISIL_DEBUG_TRACE(("SCCPMgmtHandler : SCCP-SSA ssn =%d\t ,pc =%d \n",ev.data[1],PC));
                break;
            case SCCP_SCMG_SS_PROHIBIT:
                ISIL_DEBUG_TRACE(("SCCPMgmtHandler:SCCP-SSP:ssn =%d\t ,pc =%d \n",ev.data[1],PC));

                break;
            case SCCP_SCMG_SS_CONG:
                 ISIL_DEBUG_TRACE(("SCCPMgmtHandler :SCCP-SSC:ssn =%d\t ,pc =%d \n",ev.data[1],PC));
                break;
            default:
    //             ISIL_DEBUG_TRACE(("SCCPMgmtHandler:Unknown Msg \n"));
                return;
        }
/*send to TCAP*/
     TRANSPORT_PutEvent(ITS_ISUP_SRC, &ev);
    }
}

/**********************************************************************

 * Purpose :To check the Health and update the same in the Flag for VNL Platfrom
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters: Updated value of Flag HEALTH_STAT
 *      None.
 *  *  Return Value:
***********************************************************************/
void Stack_Health_Check(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{ ITS_EVENT *hmi_event = (ITS_EVENT*)(callData);

   if(hmi_event->src== HEALTH_MANAGER_INSTANCE)
    {     
          if( hmi_event->data[0]==HEALTH_OK)
            {
             //  HEALTH_STAT=HEALTH_OK;
              // ISIL_DEBUG_TRACE (("VNL HEALTH:Checking health OK HEALTH_STAT%d\n",HEALTH_STAT));
            }
         else

           { 
             //  HEALTH_STAT=HEALTH_NOT_OK;
             //  ISIL_DEBUG_TRACE (("VNL HEALTH:Checking health NOT OK HEALTH_STAT%d\n",HEALTH_STAT));
            }
   }
  else
     ISIL_DEBUG_TRACE (("VNL HEALTH:NOT A Health Event\n"));
 }






/**********************************************************************

 * Purpose :
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
***********************************************************************/

int
TRACE_ON(ITS_EVENT ev)
{

   switch(ev.data[6])
    {
       case 0x00:
                 ISIL_DEBUG_TRACE(("MSG_DISCRIMINATOR is BSSMAP\n"));
             switch(ev.data[7])
              {
                case 0x01 :
                 ISIL_DEBUG_TRACE(("Received Msg is ASSIGN_REQUEST\n"));
                break;
                case 0x02:
                 ISIL_DEBUG_TRACE(("Received Msg is ASSIGN_COMPLETE\n"));
                break;
                case 0x20:
                 ISIL_DEBUG_TRACE(("Received Msg is CLEAR_COMMAND\n"));
                break;
                case 0x21:
                 ISIL_DEBUG_TRACE(("Received Msg is CLEAR_COMPLETE\n"));
                break;
                case 0x22:
                 ISIL_DEBUG_TRACE(("Received Msg is CLEAR_REQUEST\n"));
                break;
                case 0x52:
                 ISIL_DEBUG_TRACE(("Received Msg is PAGING_RESPONSE\n"));
                break;
                case 0x27:
                 ISIL_DEBUG_TRACE(("Received Msg is PAGING\n"));
                break;
                case 0x57:
                 ISIL_DEBUG_TRACE(("Received Msg is COMPLETE_LAYER3_INFO\n"));

                 break;
              }

               break;

       case 0x01:
                 ISIL_DEBUG_TRACE(("MSG_DISCRIMINATOR is DTAP\n"));
            switch(ev.data[7])
             {
               case 0x01:
                 ISIL_DEBUG_TRACE(("Received Msg is ALERTING\n"));
               break;
               case 0x02:
                 ISIL_DEBUG_TRACE(("Received Msg is CALL_PROCEEDING\n"));
               break;
               case 0x08:
                 ISIL_DEBUG_TRACE(("Received Msg is CALL_CONFIRMED\n"));
               break;
               case 0x07:
                 ISIL_DEBUG_TRACE(("Received Msg is CONNECT\n"));
               break;
               case 0x0f:
                 ISIL_DEBUG_TRACE(("Received Msg is CONNECT_ACKNOWLEDGE\n"));
               break;
               case 0x25:
                 ISIL_DEBUG_TRACE(("Received Msg is DISCONNECT\n"));
               break;
              case 0x2d:
                 ISIL_DEBUG_TRACE(("Received Msg is RELEASE\n"));
               break;
               case 0x2a:
                 ISIL_DEBUG_TRACE(("Received Msg is RELEASE_COMPLETE\n"));
               break;
               case 0x05:
                 ISIL_DEBUG_TRACE(("Received Msg is SETUP:\n"));
               break;
               case 0x12:
                 ISIL_DEBUG_TRACE(("Received Msg is AUTHENTICATION_REQUEST\n"));
               break;
               case 0x14:
                 ISIL_DEBUG_TRACE(("Received Msg is  AUTHENTICATION_RESPONSE\n"));
               break;
             }
               break;
   }
 return(ITS_SUCCESS);
}




/********************************************************************
 * Purpose:
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/


int  ISILPro_SccpMsg(ITS_EVENT *ev)
{

/*Patch:8-june-10:Not to merge:For MSC only:Updated for ANSI:SCCP CL*/
    //ITS_OCTET *cdaptr[1],*cpaptr[1],*Usrdatptr[1];
    ITS_OCTET *cdaptr[1], *cpaptr[1], *Usrdatptr[1], *mandptr[1];
/*Updated for ANSI:SCCP CL End*/
    ITS_OCTET msgtype;
    ITS_EVENT event;
    ITS_OCTET noargs;
    ITS_OCTET *OPptr[3];
//    ITS_OCTET *p,*U,*d;
    int result=0,i;
     ITS_OCTET index=0;

    //msgtype=ev->data[0];
    msgtype=ev->data[index];


     if (ev->len>0)
       {
     /*       printf("\n\nData received from SCCP..................\n\n");
            for (i = 0; i < ev->len; i++)
             {
                printf("%02x ", ev->data[i]);
             }
            printf("\n\n...........................................\n\n");
*/
/*Patch:8-june-10:Not_to_merge:For MSC only:Updated for ANSI:SCCP CL*/
      	if (msgtype == SCCP_MSG_NOTICE)
	      {
            ISIL_ERROR_TRACE(("ISILPro_SccpMsg:SCCP_MSG_NOTICE \n"));
     	     MandFix_Decoder (*ev, &mandptr[index]);
	      }
/*Updated for ANSI:SCCP CL End*/
            CDA_Decoder(*ev,&cdaptr[index]);

            CPA_Decoder(*ev ,&cpaptr[index]);

            Userdata_Decoder(*ev ,&Usrdatptr[index]);

            OP_Decoder(*ev ,&OPptr[index],&noargs);

/*Patch:8-june-10:Not_to_merge:For MSC only:Updated for ANSI:SCCP CL*/
     //       EVENT_Encoder(cdaptr[index],cpaptr[index],Usrdatptr[index],&OPptr[index] ,msgtype,&event,&noargs);
      	EVENT_Encoder (cdaptr[index], cpaptr[index], Usrdatptr[index], &OPptr[index], msgtype, &event, &noargs,
		       mandptr[index]);
/*Updated for ANSI:SCCP CL End*/
     }

    if (ev->data)
     {
       ITS_Free(ev->data);
     }

   /* printf("\n\nta send to SCCP User :\n\n");
   
    for ( i=0; i < event.len; i++)

     {
       printf("%02x ", event.data[i]);
     }
*/

  if (TCAPFLAG==1)
      {
        result=CL_WriteEventTcap(CL_Handle_TCAP,&event);
        if (result != ITS_SUCCESS)
          {
            ISIL_ERROR_TRACE(("ISILPro_SccpMsg:write to TCAP failed\n"));
            ITS_EVENT_TERM(&event);
            CL_Handle_TCAP=NULL;
          }
     }/*end of TCAP Flag if */

    else
     {
            ISIL_WARNING_TRACE(("ISILPro_SccpMsg:TCAP is not Regitered as SCCP User\n"));
            ITS_EVENT_TERM(&event);
            result=-1;
     }
 return(ITS_SUCCESS);
 }/*end of  Sccp_MsgProc*/

/********************************************************************
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/


int ISILPro_Mtp3TcapManageMsg(ITS_EVENT *ev)
{

   ITS_EVENT  event;
   int result=0,j=0,i=0;
   ITS_OCTET sio=0,ni=MTP3_NIC_INTERNATIONAL;
   ITS_OCTET SSN=0;
   ITS_USHORT src;
   ITS_USHORT pc;
   ITS_OCTET index=0;
   src=ev->src;

   ni=(ev->data[1]&0xF0);
   
   sio=(ev->data[1]&0x0F);
   pc=((ev->data[3]&0xc0)>>6)|(ev->data[4]<<8);
 //  printf("\nL_TRACE:VALUE OF PC= %d-SIO= %d and NI=%d",pc,sio,ni);

 for (i=0 ;i<counter ;i++)
  {

  // if (ev->data[0]==0x22)/*MTP Pause*/
   if (ev->data[index]==ISIL_MTP3PAUSE)/*MTP Pause*/
    {
      ITS_EVENT_INIT(&event,ITS_MTP3_SRC,(ev->len+1)*sizeof(ITS_OCTET));
     /*1 byte extra due to SP status parametre other len is (ev.len+4)*/
     // event.data[0]=0xb6;/*N PC state*/
      event.data[index++]=ISIL_PCSTATE_IND;/*N PC state*/
      event.data[index++]=ISIL_VERSION1;
      event.data[index++]=ISIL_NOELEM4;
      event.data[index++]=(ev->len+1)&0xff;
      event.data[index++]=((((ev->len+1))&0xff00)>>8 );
      event.data[index++]=ssn[i];
    #if defined(CCITT)
      memcpy(&event.data[index],&ev->data[6],(ev->len-6));
    #elif defined(ANSI)
      memcpy(&event.data[index],&ev->data[9],(ev->len-9));
    #endif
     // event.data[(ev->len)]=0x01;/*SP inaccessible */
      event.data[(ev->len)]=ISIL_SPINACC;/*SP inaccessible */

    index=0;
   } /*end of MTP Pause*/

  // if (ev->data[0]==0x23)/*MTP Resume*/
   if (ev->data[index]==ISIL_MTP3RESUME)/*MTP Resume*/
   {
     ITS_EVENT_INIT(&event,ITS_MTP3_SRC,(ev->len+1)*sizeof(ITS_OCTET));
//     event.data[0]=0xb6;/*N PC state INDICATION */
     event.data[index++]=ISIL_PCSTATE_IND;/*N PC state INDICATION */
     event.data[index++]=ISIL_VERSION1;
     event.data[index++]=ISIL_NOELEM4;
     event.data[index++]=(ev->len+1)&0xff;
     event.data[index++]=((((ev->len+1))&0xff00)>>8 );
     event.data[index++]=ssn[i];
    #if defined(CCITT)
     memcpy(&event.data[index],&ev->data[6],(ev->len-6));
    #elif defined(ANSI)
     memcpy(&event.data[index],&ev->data[9],(ev->len-9));
    #endif
    // event.data[(ev->len)]=0x03;/*SP accessible */
     event.data[(ev->len)]=ISIL_SPACC;/*SP accessible */

    index=0;
   } /*end of MTP Resume*/

  // if (ev->data[0]==0x24)/*MTP Status*/
   if (ev->data[index]==ISIL_MTP3STATUS)/*MTP Status*/
   {
     ITS_EVENT_INIT(&event,ITS_MTP3_SRC,(ev->len)*sizeof(ITS_OCTET));
    // event.data[0]=0xb6;/*N PC state INDICATION */
     event.data[index++]=ISIL_PCSTATE_IND;/*N PC state INDICATION */
     event.data[index++]=ISIL_VERSION1;
     event.data[index++]=ISIL_NOELEM4;
     event.data[index++]=(ev->len)&0xff;
     event.data[index++]=((((ev->len))&0xff00)>>8 );
     event.data[index++]=ssn[i];
    #if defined(ANSI)        
     event.data[index++]=ev->data[9];
     event.data[index++]=ev->data[10];
     event.data[index++]=ev->data[11];
    // event.data[9]=0x02;/*SP congested*/
     event.data[index++]=ISIL_CONG;/*SP congested*/
     if (ev->data[12])
      {
        event.data[index]=ev->data[12];
      }
    #elif defined(CCITT)  
     event.data[index++]=ev->data[6];
     event.data[index++]=ev->data[7];
     event.data[index++]=0x02;/*SP congested */
     if(ev->data[8])
      {
        event.data[index]=ev->data[8];
      }
    #endif

    index=0;
 
   } /*end of MTP status*/
   /* if (ev->data)
      {
        ITS_Free(ev->data);
      }*/

   /*  printf("\nIL_TRACE:Data send to TCAP :\n\n");


    for (j = 0; j < event.len; j++)
     {
       printf("%02x ", event.data[j]);
     }
*/
     /*changes due to APP team requirement for RESUME for particular User*/

	CHECKTCAP_RESUME=1;
         Get_SSN(pc,src,&SSN,ni);
     if (TCAPFLAG==1 && (USRREGISTER_FLAG==1)&&
            (SSN==SCCP_SSN_VLR||SSN==SCCP_SSN_HLR||SSN==SCCP_SSN_MSC||
                  SSN==SCCP_SSN_EIR|| SSN==ISIL_SSN_CAP1 || SSN==ISIL_SSN_CAP2))

      {

        result=CL_WriteEventTcap(CL_Handle_TCAP,&event);
        if (result != ITS_SUCCESS)
          {
            ISIL_ERROR_TRACE(("ISILPro_Mtp3TcapManageMsg:write to TCAP failed\n"));
            ITS_EVENT_TERM(&event);
            CL_Handle_TCAP=NULL;
          }
      }
     else
      {
          ISIL_WARNING_TRACE(("ISILPro_Mtp3TcapManageMsg: TCAP is not Registered as SCCP User\n"));
          ITS_EVENT_TERM(&event);
          result=-1;
      }
  }/* end of for of counter*/
      if (ev->data)
      {
        ITS_Free(ev->data);
      }


 return(result);

}/*end of Sccp_ManageMsg func*/

/********************************************************************
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
*******************************************************************/
int ISILPro_SccpTcapManageMsg(ITS_EVENT *ev)
{

 ITS_EVENT  event;
 int result=0,j=0;
 ITS_OCTET sio=0,ni=MTP3_NIC_INTERNATIONAL;
 ITS_OCTET SSN=0;
 ITS_USHORT src;
 ITS_USHORT pc;
 int ret=0;
   src=ev->src;
 ITS_OCTET index=0;
/*   ni=(ev->data[1]&0xF0);

   sio=(ev->data[1]&0x0F);
   pc=((ev->data[3]&0xc0)>>6)|(ev->data[4]<<8);
*/
  SSN=ev->data[1];
  pc=ev->data[2]|ev->data[3]<<8;
//  printf("\nSIL_TRACE:VALUE OF SSN=%d\t,PC=%d",SSN,pc);
/*len will be more bcz user status are extra*/
  ITS_EVENT_INIT(&event,ITS_SCCP_SRC,(ev->len+5) * sizeof(ITS_OCTET));

  // event.data[0]=0xb5; /* N state INDICATION primitive*/
   event.data[index++]=ISIL_NSTATE_IND; /* N state INDICATION primitive*/
   event.data[index++]=ISIL_VERSION1;
   event.data[index++]=ISIL_VERSION3;/*min 2or max 6*/
   event.data[index++]=((ev->len)+5)&0xff;
   event.data[index++]=((((ev->len)+5)&0xff00)>>8 );

   #if defined(ANSI) 
   memcpy(&event.data[index],&ev->data[1],(ev->len)*sizeof(ITS_OCTET));
  // if (ev->data[0]==0x01)/*SSA*/
   if (ev->data[0]==ISIL_SSA)/*SSA*/
    {
      event.data[5]=0 ;/*user in service*/
    }

  // if (ev->data[0]==0x02)/*SSP */
   if (ev->data[0]==ISIL_SSP)/*SSP */
    {
      event.data[5]=1 ;/*user out service*/
    }

   if (ev->data[6])
    {
      event.data[10]=ev->data[6];
    }

  // if (ev->data[0]==0xf2)
   if (ev->data[0]==ISIL_SSC)
    {
      /*N PC STATE will be go to user*/
    }
   #elif defined(CCITT)
   memcpy(&event.data[index],&ev->data[1],3*sizeof(ITS_OCTET));
  // if (ev->data[0]==0x01)
   if (ev->data[0]==ISIL_SSA)
    {
      event.data[index+3]=0 ;/*user in service*/
    }

  // if (ev->data[0]==0x02)
   if (ev->data[0]==ISIL_SSP)
    {
      event.data[index+3]=1 ;/*user out service*/
    }

   if (ev->data[4])
    {
      event.data[index+4]=ev->data[4];
    }
   #endif

  /* free the memory */
    if (ev->data)
     {
       ITS_Free(ev->data);
     }

/*     printf("\nSIL_TRACE:Data send to TCAP  ..................\n\n");
     for (j = 0; j < event.len; j++)
       {
          printf("%02x ", event.data[j]);
       }
*/
    CHECKTCAP_RESUME=1;
    ret=Get_SSN(pc,src,&SSN,ni);
//    printf("\nSIL_TRACE:VALUE OF SSN=%d",SSN);

    if (TCAPFLAG==1 && (USRREGISTER_FLAG==1) &&
            (SSN==SCCP_SSN_VLR||SSN==SCCP_SSN_HLR||SSN==SCCP_SSN_MSC||
                  SSN==SCCP_SSN_EIR||SSN==ISIL_SSN_CAP1||SSN==ISIL_SSN_CAP2))
       {
         result=CL_WriteEventTcap(CL_Handle_TCAP,&event);
         if (result != ITS_SUCCESS)
          {
           ISIL_ERROR_TRACE(("ISILPro_SccpTcapManageMsg:write to TCAP failed\n"));
            ITS_EVENT_TERM(&event);
            CL_Handle_TCAP=NULL;
          }
       }/*end of TCAP FLAG if*/
      else
       {
         ISIL_WARNING_TRACE(("ISILPro_SccpTcapManageMsg:TCAP is not Registered as SCCP User \n"));
          ITS_EVENT_TERM(&event);
         result=-1;
       }

   return(result);
 }/*ene of Sccp_ManageMsg func*/

/************************************************************************

 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

*************************************************************************/

int ISILPro_Mtp3Msg(ITS_EVENT *ev)
{
   ITS_EVENT event;
   int ret=0;
   ITS_OCTET index=0;
#ifndef ADAX
   ITS_EVENT_INIT(&event,ITS_ISUP_SRC,(ev->len+1) * sizeof(ITS_OCTET));

  // event.data[0]=0x34;                   /*api id*/
   event.data[index++]=ISIL_ISUP_ID1;                   /*api id*/
   event.data[index++]=ISIL_VERSION1;                   /*ver */
   event.data[index++]=ISIL_NOELEM1;                   /*number of ele*/
   event.data[index++]=((ev->len)+1)&0xff;     /*len*/
   event.data[index++]=((((ev->len)+1)&0xff00)>>8 );  /*len*/
   memcpy(&event.data[index],&ev->data[1],(ev->len)-4);

#endif
#ifdef  ADAX
   ITS_EVENT_INIT(&event,ITS_ISUP_SRC,(ev->len+4) * sizeof(ITS_OCTET));

  // event.data[0]=0x34;                   /*api id*/
   event.data[index++]=ISIL_ISUP_ID1;                   /*api id*/
   event.data[index++]=ISIL_VERSION1;                   /*ver */
   event.data[index++]=ISIL_NOELEM1;                   /*number of ele*/
   event.data[index++]=((ev->len)+4)&0xff;     /*len*/
   event.data[index++]=((((ev->len)+4)&0xff00)>>8 );  /*len*/
   memcpy(&event.data[index],&ev->data[1],(ev->len)-1);
#endif

  if(ISUPFLAG==1)
    {
     ret=CL_WriteEventIsup(CL_Handle_ISUP,&event);

     if (ret != ITS_SUCCESS)
      {
        ITS_EVENT_TERM(&event);
        CL_CloseConnection(CL_Handle_ISUP);
        CL_Handle_ISUP=0;
      }
    }
   else
   {
      ISIL_WARNING_TRACE(("ISILPro_Mtp3Msg:ISUP is not registered as MTP3 User\n"));
     ITS_EVENT_TERM(&event);
     ret=-1;
   }

  return(ret);

}

/********************************************************************
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

********************************************************************/


int ISILPro_Mtp3IsupManageMsg(ITS_EVENT *ev)
{
 ITS_EVENT event;
 int ret=0,j=0,length=0;
 ITS_USHORT dpc=0;
 ITS_OCTET SIO=0;
 ITS_USHORT src;
 ITS_USHORT x=0,y=0,z=0;
 ITS_OCTET ni,index=0;

/* x=(ITS_USHORT)ev->data[];
 y=(ITS_USHORT)ev->data[4];
 z=(ITS_USHORT)ev->data[5];
*/

 x=(ITS_USHORT)ev->data[2];
 y=(ITS_USHORT)ev->data[3];

  #if defined(ANSI)
  dpc=(ev->data[6]|ev->data[7]<<8|ev->data[8]<<0x10);

  #elif defined(CCITT)
  dpc=(ev->data[6]|ev->data[7]<<8);
        //gtt_dpc=((x>>6|y<<2|z<<0x0a))& (0x3fff);
  gtt_opc=((x|(y&0x003f)<<0x08));

  ISIL_DEBUG_TRACE(("value of gtt_opc=%d\n",gtt_opc));

  #endif

 ni=(ev->data[1])&0xF0;
 gtt_ni=ni;
 ISIL_DEBUG_TRACE(("value of gtt_ni=%d\n",gtt_ni));


 //if(ev->data[0]==0x22)
 if(ev->data[index]==ISIL_MTP3PAUSE)
  {
     ISIL_DEBUG_TRACE(("ISILPro_Mtp3IsupManageMsg:MTP-PAUSE is received from MTP3\n"));
   #if defined(CCITT)
    length=7;
   #elif defined(ANSI)
    length=8;
   #endif
    ITS_EVENT_INIT(&event,ITS_MTP3_SRC,(length)*sizeof(ITS_OCTET));
  //  event.data[0]=0x35;
    event.data[index++]=ISIL_USERPAUSE;
    event.data[index++]=ISIL_VERSION1;
    event.data[index++]=ISIL_NOELEM1;
    event.data[index++]=(length)&0xff;
    event.data[index++]=(((length)&0xff00)>>8 );
   #if defined(CCITT)
    memcpy(&event.data[index],&ev->data[6],((ev->len)-6));
   #elif defined(ANSI)
    memcpy(&event.data[index],&ev->data[9],(ev->len-9));
   #endif
   index=0;
  }/*end of MTP pause*/

// else if(ev->data[0]==0x23)
 else if(ev->data[index]==ISIL_MTP3RESUME)
  {
   ISIL_DEBUG_TRACE(("ISILPro_Mtp3IsupManageMsg:MTP-RESUME is received from MTP3\n"));
   #if defined(CCITT)
     length=7;
   #elif defined(ANSI)
     length=8;
   #endif
    ITS_EVENT_INIT(&event,ITS_MTP3_SRC,(length)*sizeof(ITS_OCTET));
   // event.data[0]=0x36;
    event.data[index++]=ISIL_USERRESUME;
    event.data[index++]=ISIL_VERSION1;
    event.data[index++]=ISIL_NOELEM1;
    event.data[index++]=(length)&0xff;
    event.data[index++]=(((length)&0xff00)>>8 );
   #if defined(CCITT)
    memcpy(&event.data[index],&ev->data[6],(ev->len-6));
   #elif defined(ANSI)
    memcpy(&event.data[index],&ev->data[9],(ev->len-9));
   #endif
  index=0;
  }/*end of MTP Resume*/
 //else if(ev->data[0]==0x24)
 else if(ev->data[index]==ISIL_MTP3STATUS)
  {
   ISIL_DEBUG_TRACE(("ISILPro_Mtp3IsupManageMsg:MTP-STATUS is received from MTP3\n"));
    #if defined(CCITT)
     length=9;
    #elif defined(ANSI)
     length=10;
    #endif
     ITS_EVENT_INIT(&event,ITS_MTP3_SRC,(length)*sizeof(ITS_OCTET));
    // event.data[0]=0x37;
     event.data[index++]=ISIL_USERSTATUS;
     event.data[index++]=ISIL_VERSION1;
     event.data[index++]=ISIL_NOELEM1;
     event.data[index++]=(length)&0xff;
     event.data[index++]=(((length)&0xff00)>>8 );
    #if defined(CCITT)
     memcpy(&event.data[index],&ev->data[6],(ev->len-6));
    #elif defined(ANSI)
     memcpy(&event.data[index],&ev->data[9],(ev->len-9));
    #endif
   index=0;
  }/*ened of MTP Status*/

   if (ev->data)
    {
      ITS_Free(ev->data);
    }

   if ( event.data[index]==ISIL_USERPAUSE ||
            event.data[index]==ISIL_USERRESUME ||
                           event.data[index]==ISIL_USERSTATUS)
     {

     /*  printf("\nData send to ISUP: \n\n");
       for (j = 0; j < event.len; j++)
       {
         printf("%02x ", event.data[j]);
       }

*/

       CHECKISUP_RESUME=1;

       src=event.src;
       Get_SSN(dpc,src,&SIO,ni);
       if (ISUPFLAG==1&&SIO==0x03|ni)
         {
           ret=CL_WriteEventIsup(CL_Handle_ISUP,&event);
           if (ret != ITS_SUCCESS)
             {
                ITS_EVENT_TERM(&event);
                CL_CloseConnection(CL_Handle_ISUP);
                CL_Handle_ISUP=0;
              }
        }/*ened of ISUP FLAF if*/
      else
       {
         ITS_EVENT_TERM(&event);
         ret=-1;
       }
  }

   return(ret);

 }/*end of main func*/

/********************************************************************
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

********************************************************************/
int ISILPro_IsupMsg(ITS_EVENT *evt)
{
   ITS_EVENT event;
   int j;
   ITS_INT count;
   ITS_OCTET *buff;
   ITS_OCTET TempBuffer[10];
   ITS_EVENT_INIT(&event,ITS_ISUP_SRC,((evt->len)-4)*sizeof(ITS_OCTET));

  //  event.data[0]=0x21;
    event.data[0]=ISIL_USRDATA;
    memcpy(&event.data[1],&evt->data[5],(evt->len)-5);

   buff = (ITS_OCTET*)calloc(evt->len*6+1, sizeof(ITS_OCTET));

   for (count = 0; count < evt->len; count++)
    {
       sprintf((char *)TempBuffer, "0x%02x ",evt->data[count]);
       strcat((char*)buff,(const char *)TempBuffer);
        if (!(count % 15)&&(count!=0))
         {
          strcat((char*)buff,"\n");
         }
       }
     
    ISIL_DEBUG_TRACE(("Data Send to MTP3:-\n\n%s\n\n",buff));
    free(buff);
/*
    ISIL_DEBUG_TRACE(("Data send to MTP3 :--\n")); 
   for (j = 0; j < event.len; j++)
      {
       printf("%02x ", event.data[j]);
      }
   printf("\n");
*/
   TRANSPORT_PutEvent(ITS_MTP3_SRC, &event);

   ITS_EVENT_TERM(evt);
   return(ITS_SUCCESS);
}
/********************************************************************
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

********************************************************************/
int ISILPro_MMMsg(ITS_EVENT *evt)
{
  BSSAPDispatcher disp;
  ITS_EVENT eve;
  int i;
  ITS_INT count;
  ITS_OCTET *buff;
  ITS_OCTET TempBuffer[10];
#ifdef TRACE_DUMP
   buff = (ITS_OCTET*)calloc(evt->len*6+1, sizeof(ITS_OCTET));

   for (count = 0; count < evt->len; count++)
    {
       sprintf((char *)TempBuffer, "0x%02x ",evt->data[count]);
       strcat((char*)buff,(const char *)TempBuffer);
        if (!(count % 15)&&(count!=0))
         {
          strcat((char*)buff,"\n");
         }
       }
    ISIL_DEBUG_TRACE(("BSCAPP-BSSAP: Recevied event from CP:8540\n")); 
    ISIL_DEBUG_TRACE(("Data received from BSC-APP:-\n\n%s\n\n",buff));
    free(buff);
#endif
/*
   ISIL_DEBUG_TRACE(("Data received from MM:-\n"));

   for (i = 0; i < evt->len; i++)
     {
         printf("%02x ", evt->data[i]);
     }

   printf("\n");
*/
     ITS_EVENT_INIT(&eve,ITS_BSSAP_SRC,((evt->len)-5)*sizeof(ITS_OCTET));
     memcpy(&eve.data[0],&evt->data[5],(evt->len)-5);

     #if defined (DEBUG_TRACE)
        TRACE_ON(eve);
     #endif
   // ISIL_DEBUG_TRACE(("Data Send to BSSAP:-\n"));
    ITS_Event event(&eve);
    ITS_EVENT_TERM(&eve);
    disp.ProcessSocketEvent(&event);
    ITS_EVENT_TERM(evt);
    sched_yield();
    return(ITS_SUCCESS);

}
                                           

/********************************************************************
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

********************************************************************/
int ISILPro_TcapMsg(ITS_EVENT *evt)
{
   ISIL_IE ie[10];
   ISIL_ARGS args;
   ITS_OCTET totalargs=evt->data[2];
   ITS_EVENT event;
   ITS_OCTET sls=0,sio;
   int i=0;
   ITS_INT count;
   ITS_OCTET *buff;
   ITS_OCTET TempBuffer[10];


   if (evt->len >0)
    {
     buff = (ITS_OCTET*)calloc(evt->len*6+1, sizeof(ITS_OCTET));

     for (count = 0; count < evt->len; count++)
      {
        sprintf((char *)TempBuffer, "0x%02x ",evt->data[count]);
        strcat((char*)buff,(const char *)TempBuffer);
        if (!(count % 15)&&(count!=0))
         {
          strcat((char*)buff,"\n");
         }
       }
     
    ISIL_DEBUG_TRACE(("Data received from TCAP:-\n\n%s\n\n",buff));
    free(buff);
/*
        ISIL_DEBUG_TRACE(("Data received from TCAP:-\n"));  
        for (i = 0; i < evt->len; i++)
        {
          printf("%02x ", evt->data[i]);
        }

   printf("\n");
*/
    ISIL_Decode(evt,ie,&args);
   // ISILgethdr(evt,opc,dpc,sio);
    ISIL_Encoder(&event,ie,args);

    buff = (ITS_OCTET*)calloc(event.len*6+1, sizeof(ITS_OCTET));

     for (count = 0; count < event.len; count++)
      {
        sprintf((char *)TempBuffer, "0x%02x ",event.data[count]);
        strcat((char*)buff,(const char *)TempBuffer);
        if (!(count % 15)&&(count!=0))
         {
           strcat((char*)buff,"\n");
         }
       }
     
    ISIL_DEBUG_TRACE(("Data send to SCCP:-\n\n%s\n\n",buff));
    free(buff);
/*
    ISIL_DEBUG_TRACE(("Data send to SCCP:-\n"));

     for (i= 0; i < event.len; i++)
       {
         printf("%02x ", event.data[i]);
       }
*/
    TRANSPORT_PutEvent(ITS_SCCP_SRC,&event);

    ITS_EVENT_TERM(evt);
  }/*end of if*/
 }/*end of MAP DATA*/

/********************************************************************
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:

********************************************************************/

int
Get_SSN(ITS_USHORT pc,ITS_USHORT src,ITS_OCTET *ssn,ITS_OCTET ni)

{
    int ret=0;
/*  ITS_OCTET S[6];*/
  ITS_OCTET i=0,nssn=0;
  ITS_BOOLEAN isAllowed;

   if (src==0x20)
    {
      *ssn=0xFE;
        if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          *ssn,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
         {
            if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
              {
                 if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                  {
                      if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_RESERVED | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                      {

                                 printf("SET SSN FAIL");
                      }
                      else
                      {
                         *ssn=0xFE;
                          ni = MTP3_NIC_RESERVED;
	                       ret=1;
                       }
                  }
                 else
                  {
                     *ssn=0xFE;
                      ni = MTP3_NIC_NATIONAL;
	                    ret=1;
                  } 
              }
             else
              {
                 *ssn=0xFE;
                  ni = MTP3_NIC_SPARE;
	                ret=1;
              } 
        }
        else
         {
           *ssn=0xFE;
            ni = MTP3_NIC_INTERNATIONAL;
	          ret=1;

         }
           

    }
    else if (src==ITS_SCCP_SRC && (*ssn==0))
    {

      for (i=0;i<MAX_SSN;i++)
       {
           *ssn=RESUME_SSN[i];
           if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          *ssn,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
             {
                if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                 {
                   if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                     {
                         if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_RESERVED | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                          {
                                  printf("SET SSN FAIL");
                                  *ssn=0;
                                  ret=-1;
                          }
                         else
                          {
                               ret=1;
                               break;
                          }
                     }
                    else
                     {
                          ret=1;
                          break;
                     } 
                  }
                else
                  {
                      ret=1;
                      break;
                  } 
              }
            else
              {
                  ret=1;
                  break;
              }
           
       }
    }
   else if (src==ITS_SCCP_SRC  &&  (*ssn!=0))
    {
           if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          *ssn,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
             {
                if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                 {
                   if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                     {
                         if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_RESERVED | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                          {
                                  printf("SET SSN FAIL");
                          }
                         else
                          {
                             for (i=0;i<MAX_SSN;i++)
                              {
                               if (*ssn==RESUME_SSN[i])
                                {
                                  ret=1;
                                }
                              else
                                {  
                                  ret=-1;
                                }
                              }
                          }
                      }
                     else
                      {
                          for (i=0;i<MAX_SSN;i++)
                          {
                             if (*ssn==RESUME_SSN[i])
                              {
                                  ret=1;
                              }
                            else
                              {  
                                  ret=-1;
                              }
                           }
                       }
                  }
                 else
                  {
                      for (i=0;i<MAX_SSN;i++)
                       {
                         if (*ssn==RESUME_SSN[i])
                           {
                                  ret=1;
                              }
                            else
                              {  
                                  ret=-1;
                              }
                           }
                  }
             }
            else
             {
                for (i=0;i<MAX_SSN;i++)
                  {
                     if (*ssn==RESUME_SSN[i])
                       {
                              ret=1;
                       }
                       else
                       {  
                           ret=-1;
                       }
                 }
            }

   }
  else if (src==ITS_MTP3_SRC)
   {
           if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          *ssn,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
             {
                if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                 {
                   if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                     {
                         if (ROUTE_GetRouteContextStatus(pc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_RESERVED | MTP3_SIO_SCCP),*ssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                          {
                                  printf("SET SSN FAIL");
                                  *ssn=0;
                                   ret=-1;
                          }
                         else
                          {
                            *ssn=(MTP3_NIC_RESERVED|0x03);
                             ret=1;
                          }  
                     }
                    else
                     {
                       *ssn=(MTP3_NIC_NATIONAL|0x03);
                       ret=1;
                     }
                }
               else
                {
                      *ssn=(MTP3_NIC_SPARE|0x03);
                      ret=1;
                }
            }
           else
            {
               *ssn= (MTP3_NIC_INTERNATIONAL|0x03);
                ret=1;
            }
            
  }

 return(ret);

}




/***************************************************************************
 * Purpose:  SCCP  GTT Translation of the GTT Digts .
 *
 * Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
***************************************************************************/
//extern "C" IMR_GTT_INFO gtt_Info;
void
IMR_GTT(ITS_POINTER object, ITS_POINTER userData,ITS_POINTER callData)
{
    SCCP_CALLBACK_DATA *data =(SCCP_CALLBACK_DATA*)callData;
    SCCP_ADDR *cdp=0;
    SCCP_ADDR *clp=0;
    MTP3_HEADER *mtp3;
    IMR_GTT_TransRule *Rule=NULL;
    char *gtaistring=0;
    ISIL_DPC_SSN *dpc_ssn=NULL;
    char  digits[20];
    IMR_GTT_IN inputgtt;
    ITS_OCTET gtival=0;
    ITS_OCTET offset=0;
    ITS_OCTET noffset=0;
    ITS_USHORT cdp_ssn=0;
    ITS_USHORT dpc_value=0;
    ITS_UINT   opc_value=0;
    ITS_OCTET ssn_value=0;
    ITS_OCTET AddIndicator=0;
    int i=0,j=0;
    int len=0;
    int ret=0;


  inputgtt.AddIn=data->addrInd;
  gtival=(inputgtt.AddIn & GTT_VALUE) >> GTI_SHIFT;
            ISIL_DEBUG_TRACE(("value of AddIn=%d \n",inputgtt.AddIn));
            ISIL_DEBUG_TRACE(("value of GTI=%d \n",gtival));
       inputgtt.gti=gtival;

          for (i = 0; i < data->ieCount; i++)
          {
             if (data->ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
               {
                  cdp = &data->ies[i].param_data.calledPartyAddr;
               }
             if (data->ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
               {
                  clp = &data->ies[i].param_data.callingPartyAddr;
               }
             if(data->ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
               {
                 mtp3=&data->ies[i].param_data.routingLabel;
                mtp3_dpc=MTP3_RL_GET_DPC_VALUE(mtp3->label);
                mtp3_opc=MTP3_RL_GET_OPC_VALUE(mtp3->label);

               }
         }
      
         if (cdp->data[0] & IS_DPC)
          {
/*Patch:Itika :14-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
             cdp_dpc=cdp->data[1]|(cdp->data[2]<<8);
#endif
#ifdef ANSI
             cdp_dpc=cdp->data[2]|(cdp->data[3]<<8)|(cdp->data[4]<<16);
#endif
/*End:Updated for ANSI SCCP-CL*/

             if (cdp->data[0] & IS_SSN)
             {
/*Patch:Itika :14-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
               cdp_ssn=cdp->data[3];
#endif
#ifdef ANSI
               cdp_ssn=cdp->data[1];
#endif
/*End:Updated for ANSI SCCP-CL*/
             }
          }
        else if(!(cdp->data[0] & IS_DPC) && (cdp->data[0] & IS_SSN))
          {
               cdp_ssn=cdp->data[1];
          }

        if (clp->data[0] & IS_DPC)
          {
/*Patch:Itika :14-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
             clp_opc=clp->data[1]|(clp->data[2]<<8);
#endif
#ifdef ANSI
             clp_opc=clp->data[2]|(clp->data[3]<<8)|(cdp->data[4]<<16);
#endif
/*End:Updated for ANSI SCCP-CL*/
          }
           ISIL_DEBUG_TRACE(("cpd_dpc=%d,cpd_ssn=%d,clp_opc=%d",cdp_dpc,cdp_ssn,clp_opc));

         
        ISIL_DEBUG_TRACE(("#########[GTI =%d #############\n",gtival));
  switch(gtival)
  {
    case 0x01:
/*Patch:Itika :14-june-10:Updated for ANSI SCCP-CL*/
      {
            inputgtt.TF_in.TransType=data->gttInfo[offset];  
          ISIL_DEBUG_TRACE(("value of Translation type=%d \n",inputgtt.TF_in.TransType));
            offset++;
 
            inputgtt.TF_in.Encod_scheme=data->gttInfo[offset ]& 0x0f;
          ISIL_DEBUG_TRACE(("value of Encoding Scheme=%d \n", inputgtt.TF_in.Encod_scheme));

            inputgtt.TF_in.Num_Plan=(data->gttInfo[offset] & 0xf0) >> 4;
          ISIL_DEBUG_TRACE(("value of Num plan=%d \n", inputgtt.TF_in.Num_Plan));
            offset++;
       } 
        break;
/*End:Updated for ANSI SCCP-CL*/
      return ;
    break;
    case 0x02:
            inputgtt.TF_in.TransType=data->gttInfo[offset];  
            offset++;
            ISIL_DEBUG_TRACE(("value of Translation type=%d \n",inputgtt.TF_in.TransType));
    break ;
    case 0x03:
     return;
    break;
     case 0x04 :
        {
            inputgtt.TF_in.TransType=data->gttInfo[offset];  
  //        ISIL_DEBUG_TRACE(("value of Translation type=%d \n",inputgtt.TF_in.TransType));
            offset++;
 
            inputgtt.TF_in.Encod_scheme=data->gttInfo[offset ]& 0x0f;
  //        ISIL_DEBUG_TRACE(("value of Encoding Scheme=%d \n", inputgtt.TF_in.Encod_scheme));

            inputgtt.TF_in.Num_Plan=(data->gttInfo[offset] & 0xf0) >> 4;
  //        ISIL_DEBUG_TRACE(("value of Num plan=%d \n", inputgtt.TF_in.Num_Plan));
            offset++;
 
            inputgtt.TF_in.NAI=(data->gttInfo[offset] & 0x7F);
 //          ISIL_DEBUG_TRACE(("value of Nature of AddIn=%d \n", inputgtt.TF_in.NAI));
            offset++;

            ISIL_DEBUG_TRACE(("value of TT=%d ES=%d,NP=%d,NAI=%d \n",inputgtt.TF_in.TransType,inputgtt.TF_in.Encod_scheme, inputgtt.TF_in.Num_Plan, inputgtt.TF_in.NAI));
    

     }
   break;
   default:
       ISIL_WARNING_TRACE(("Unknown GTI value"));
 }


   len=data->gttLen-(offset);
   for (i=0,j=0;i<len;i++)
     {
          inputgtt.gt_Info.gtt_digits[j]=((data->gttInfo[offset])& 0x0f);
    //      printf("digits=%d",  inputgtt.gt_Info.gtt_digits[j]);
          digits[j]=inputgtt.gt_Info.gtt_digits[j]+48;
           j++;
          inputgtt.gt_Info.gtt_digits[j]=(((data->gttInfo[offset]) & 0xf0) >>4);
    //      printf("digits=%d",  inputgtt.gt_Info.gtt_digits[j]);
          digits[j]=inputgtt.gt_Info.gtt_digits[j]+48;
           j++;

      offset++;
     }
     inputgtt.gt_Info.gtt_digits[j]='\0';
     digits[j]='\0';



    ISIL_DEBUG_TRACE(("Input GTAI string=%s",digits));



    Rule=(IMR_GTT_TransRule*)malloc(sizeof(IMR_GTT_TransRule));
   //Get the Translation function w.r.t in gtt value
    ret= IMR_GTT_GetTransFunc(inputgtt,Rule);
    if(ret!=ITS_SUCCESS)
    {
      ISIL_ERROR_TRACE(("Wrong Transfer Function received\n"));
      return;
      
    }

    dpc_ssn=IMR_GTDigts_Translation(Rule,inputgtt.gt_Info.gtt_digits);

    if(dpc_ssn !=NULL)
    {
       if(dpc_ssn->primaryssnflag)
       {
         data->dpc=dpc_ssn->primarydpc;
         data->ssn=dpc_ssn->ssn;
         ISIL_DEBUG_TRACE(("GTT Tranlation dpc=%d \n",data->dpc));
       }
    /*   else if(dpc_ssn->secondaryssnflag)
       {
         data->dpc=dpc_ssn->secondarydpc;
         data->ssn=dpc_ssn->ssn;
         ISIL_DEBUG_TRACE(("GTT Tranlation dpc=%d \n",data->dpc));
       } Due to OAM not support*/
       else
       {
         ISIL_DEBUG_TRACE(("GTT Tranlation Failed:No Entry Found \n"));
         data->dpc=0;
         data->ssn=0;

       } 

       //check if both ssn and dpc are present
       if (data->dpc||data->ssn)
       {
           data->transSuccess = ITS_TRUE;
          /* when the translation will be success */
       }
    
      ISIL_DEBUG_TRACE(("GTT Translation  route flag=%d ",dpc_ssn->routeflag));
       /*if route flag is 0 then route on GTT*/
       if(dpc_ssn->routeflag==0)
       {
          if (data->dpc && data->ssn)
           {
/*Patch:Itika :15-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
             AddIndicator=(data->addrInd|0x02 )& 0xFE ;
#endif
#ifdef ANSI
             AddIndicator=(data->addrInd|0x01 )& 0xFD ;
#endif
/*End:Updated for ANSI SCCP-CL*/
             /*only ssn value must be present*/
           }

           data->translation->data[noffset]=AddIndicator;
           noffset++;

           if ((data->ssn) && (cdp_ssn==0))
           {
               data->translation->data[noffset]=data->ssn;
               ISIL_DEBUG_TRACE(("GTT Translation  ssn value=%d ",data->translation->data[noffset]));
               noffset++;
           }
           else if(cdp_ssn>0)
           {
              data->translation->data[noffset]=cdp_ssn;
              ISIL_DEBUG_TRACE(("CDPA ssn value=%d ",data->translation->data[noffset]));
              noffset++;
           }
         data->translation->len=(data->gttLen)+noffset;
         memcpy(&data->translation->data[noffset],data->gttInfo,data->gttLen);
       }
       /*if route flag is 1 then route on DPC and SSN*/
       else  if(dpc_ssn->routeflag==1)
       {
          if (data->dpc && data->ssn)
           {
             AddIndicator=(data->addrInd|0x43) & 0xc3 ;
             /*dpc and ssn value must be present*/
           }
           data->translation->len=0x04;
           data->translation->data[noffset]=AddIndicator;
           noffset++;
           data->translation->data[noffset]=ITS_OCTET(data->dpc);
         //  ISIL_DEBUG_TRACE(("GTT Tranlation data->translayytion->data[noffset]=%d\n",data->translation->data[noffset]));
           noffset++;
           data->translation->data[noffset]=ITS_OCTET((data->dpc)>>8);
          // memcpy(&data->translation->data[noffset],dpc_ssn,sizeof(ITS_USHORT));
         //  ISIL_DEBUG_TRACE(("GTT Tranlation data->translayytion->data[noffset]=%d\n",data->translation->data[noffset]));
         //  noffset+=sizeof(ITS_USHORT);
           noffset++;

           if ((data->ssn) && (cdp_ssn==0))
           {
               data->translation->data[noffset]=data->ssn;
               ISIL_DEBUG_TRACE((" GTT Translation ssn value=%d ",data->translation->data[noffset]));
               noffset++;
           }
           else if(cdp_ssn>0)
           {
              data->translation->data[noffset]=cdp_ssn;
              ISIL_DEBUG_TRACE(("CDPA ssn value=%d ",data->translation->data[noffset]));
              noffset++;
          }       
           
       }
     }
     else
     {
         ISIL_DEBUG_TRACE(("GTT Tranlation Failed:\n"));
     }

     if (Rule) 
     {
        free(Rule);
        Rule=NULL;
     }
 }
/*end of func IMR_GTT*/
 

/*change for redundancy*/
   int ISIL_GETNODE_STATE ()
  {
    return (isilstate.state);
  }

   int ISIL_SETNODE_STATE (ISIL_NODE_STATE state)
  {
    isilstate.state = state;
    return (ITS_SUCCESS);
  }

   int ISIL_LinkOpreation (ISIL_NODE_STATE state)
  {
    ITS_INT i = 0, j = 0;
    SS7_LinkPtr ln = NULL;
    int ret = 0;
    cntr = 0;
    ITS_EVENT ev;
    ITS_EVENT Out_ev = { '\0', };
    ITS_UINT lscount=0,cnt=0;
    ITS_OCTET linkset[255];
    ITS_UINT k=0,l=0;

        ISIL_DEBUG_TRACE(("ISIL_LinkOpreation: linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        //ISIL_ERROR_TRACE(("ISIL_LinkOpreation: linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (k = 0; k < MAX_LINKSETS; k++)
         {
          for(l = 0;l < MAX_LINKS_PER_LINKSET ;l++)
          {
            if(linkTransportMapDB[k][l] >0) 
             {  
               ISIL_DEBUG_TRACE((" linkTransportMapDB[%d][%d]=%d\n",k,l,linkTransportMapDB[k][l]));
               //ISIL_ERROR_TRACE((" linkTransportMapDB[%d][%d]=%d\n",k,l,linkTransportMapDB[k][l]));
               if( k > 0 && k < 252)
               {
                lscount++;
                linkset[cnt++]=k;
                ISIL_DEBUG_TRACE((" linkset = %d\n",k));
                //ISIL_ERROR_TRACE((" linkset = %d\n",k));
                break;
               }
             }
          }
         }
         ISIL_DEBUG_TRACE((" linkTransportMapDB\n"));
         //ISIL_ERROR_TRACE((" linkTransportMapDB\n"));
           //ISIL_DEBUG_TRACE((" Total Linkset %d found\n", lscount));
           ISIL_ERROR_TRACE((" Total Linkset %d found\n", lscount));

        for (i = 0; i < lscount; i++)/*should be change for 255*/
          {
            for (j = 0; j < MAX_LINKS_PER_LINKSET; j++)/*should be change for 8*/
            {
                k = linkset[i];
               if(linkTransportMapDB[k][j] >0)
               {
                //ISIL_DEBUG_TRACE((" Linkset %d link %d\n", k,j));
               // ISIL_ERROR_TRACE(("Before LINK_FindLink for Linkset %d link %d\n", k,j));
                if ((ln = LINK_FindLink (k, j)) != NULL)
                  {
                    ISIL_ERROR_TRACE(("LINK_FindLink SUCCESS for Linkset %d link %d\n", k,j));
                    //ISIL_DEBUG_TRACE (("For link instance id =%d FILE:%s LINE:%d\n", ln->id, __FILE__, __LINE__));
                    ISIL_ERROR_TRACE (("ISIL_LinkOpreation:For link instance id =%d FILE:%s LINE:%d\n", ln->id, __FILE__, __LINE__));
                    if (ln->id == ISIL_INTERNODE_BT)
                      {
                           ISIL_DEBUG_TRACE (("\nFor linkset =%d,link Code =%d   OUT OF SERVICE FILE:%s LINE:%d\n", linkset[i], j, __FILE__, __LINE__));
                           ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,3 * sizeof(ITS_OCTET));

                           ev.data[0] = L2_L3_OUT_OF_SERVICE;
                           ev.data[1] = linkset[i];
                           ev.data[2] = j;
                           TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
                           //ISIL_DEBUG_TRACE (("\nFor linkset =%d,link Code =%d  DEACTIVATION FILE:%s LINE:%d\n", linkset[i], j, __FILE__, __LINE__));
                        /*****************************to cancel T17 in case of Internode*****************/	
			if((TIMERS_CancelSharedTimer(ln->t17))== ITS_SUCCESS)
                 	{
                  	MTP3_ERROR(("T17 Cancled for Internode linkset|linkcode %d|%d \n\n ",i,j));
                 	}
               		ln->t17 = TIMER_BAD_SERIAL;
                         //ISIL_DEBUG_TRACE (("\nFor linkset =%d,link Code =%d  DEACTIVATION ", linkset[i], j));
                        /*****************************to cancel T17 *****************/
                         //LSAC_Main_CCITT(MTP3_MGMT,SLM_TRIGGER_DEACTIVATE_LINK,NULL, 0,(ITS_OCTET)linkset[i],(ITS_OCTET)j);
                      }

                  }             /*end of ln check null */
                ISIL_ERROR_TRACE(("ISIL_LinkOpreation:ln %x\n",ln));
                
              }                 /*end of for loop for link */
            }
          }                     /*end of for loop linkset */
   //     ISIL_SETNODE_STATE (state);
                        /*end of check of state */

    ISIL_ERROR_TRACE (("For loop  link  FILE:%s LINE:%d\n", __FILE__, __LINE__));
  }


void *SEND(void*arg)
{
char x;
ITS_EVENT event;
 int i,j,k=0;

for(;;)

 {

  printf("\nENETR 1:\n");
  sleep(10);
// scanf("%d",&x);
 x=1;
 switch(x)
 {
  case 1:
      ITS_EVENT_INIT(&event,ITS_TCAP_SRC,105* sizeof(ITS_OCTET));
    {

    event.data[0]=0x09;
    event.data[1]=0x00;
    event.data[2]=0x00;
    event.data[3]=0x00;
    event.data[4]=0x00;
    event.data[5]=0x03;
    event.data[6]=0x00;
    event.data[7]=0x40;
    event.data[8]=0x00;
    event.data[9]=0x00;
    event.data[10]=0x00;

    event.data[11]=0x03;
    event.data[12]=0x0f;
    event.data[13]=0x13;

    event.data[14]=0x0c; /*called party address*/
    event.data[15]=0x92;
    event.data[16]=0x0d;
    event.data[17]=0x00;/*TT*/
    event.data[18]=0x12;/*NP+ES*/
    event.data[19]=0x04;/*NAI*/
    event.data[20]=0x19;
    event.data[21]=0x89;
    event.data[22]=0x00;
    event.data[23]=0x00;
    event.data[24]=0x00;
    event.data[25]=0x10;
    event.data[26]=0x04;

    event.data[27]=0x04;/*calling party address*/
    event.data[28]=0x43;
    event.data[29]=0x02;
    event.data[30]=0x00;
    event.data[31]=0xf1;

    event.data[32]=0x48;/*2 bytes for user data length*/
    event.data[33]=0x2b;
    event.data[34]=0x62;
    event.data[35]=0x80;
    event.data[36]=0x48;
    event.data[37]=0x04;
    event.data[38]=0x00;
    event.data[39]=0x00;
    event.data[40]=0x09;
    event.data[41]=0xbe;
    event.data[42]=0x6b;
    event.data[43]=0x80;
    event.data[44]=0x28;
    event.data[45]=0x80;
    event.data[46]=0x06;
event.data[47]=0x07;
    event.data[48]=0x00;
    event.data[49]=0x11;
    event.data[50]=0x86;
    event.data[51]=0x05;
    event.data[52]=0x01;
    event.data[53]=0x01;
    event.data[54]=0x01;
    event.data[55]=0x0a;
    event.data[56]=0x80;
    event.data[57]=0x60;
    event.data[58]=0x80;
    event.data[59]=0xa1;
    event.data[60]=0x80;
event.data[61]=0x60;
    event.data[62]=0x07;
    event.data[63]=0x04;
    event.data[64]=0x00;
    event.data[65]=0x00;
    event.data[66]=0x01;
    event.data[67]=0x15;
    event.data[68]=0x03;
    event.data[69]=0x04;
    event.data[70]=0x00;
    event.data[71]=0x00;
    event.data[72]=0x00;
    event.data[73]=0x00;
    event.data[74]=0x00;
 event.data[75]=0x00;
    event.data[76]=0x00;
    event.data[77]=0x00;
    event.data[78]=0x00;
    event.data[79]=0x00;
    event.data[80]=0x6c;
event.data[81]=0x80;
    event.data[82]=0xa1;
    event.data[83]=0x80;
   event.data[84]=0x80;
    event.data[85]=0x02;
    event.data[86]=0x01;
    event.data[87]=0x00;
 event.data[88]=0x02;
    event.data[89]=0x01;
    event.data[90]=0x00;
    event.data[91]=0x30;
    event.data[92]=0x06;
    event.data[93]=0x80;
    event.data[94]=0x01;
    event.data[95]=0x06;
    event.data[96]=0x9c;
    event.data[97]=0x00;
    event.data[98]=0x01;
    event.data[99]=0x00;
    event.data[100]=0x00;
    event.data[101]=0x0;
    event.data[102]=0x00;
    event.data[103]=0x00;
    event.data[104]=0x00;



   TRANSPORT_PutEvent(ITS_SCCP_SRC, &event);
    ITS_EVENT_TERM(&event);

  }
 break;
  case 2:
      ITS_EVENT_INIT(&event,ITS_TCAP_SRC,101* sizeof(ITS_OCTET));
    {

    event.data[0]=0x09;
    event.data[1]=0x00;
    event.data[2]=0x00;
    event.data[3]=0x00;
    event.data[4]=0x00;
    event.data[5]=0x83;
    event.data[6]=0x00;
    event.data[7]=0x40;
    event.data[8]=0x00;
    event.data[9]=0x00;
    event.data[10]=0x00;

    event.data[11]=0x03;
    event.data[12]=0x0b;
    event.data[13]=0x0f;

    event.data[14]=0x08; /*called party address*/
    event.data[15]=0x92;
    event.data[16]=0x0d;
    event.data[17]=0x00;/*TT*/
    event.data[18]=0x12;/*NP+ES*/
    event.data[19]=0x04;/*NAI*/
    event.data[20]=0x19;
    event.data[21]=0x89;
    event.data[22]=0x00;

    event.data[23]=0x04;/*calling party address*/
    event.data[24]=0x43;
    event.data[25]=0x02;
    event.data[26]=0x00;
    event.data[27]=0xf1;

    event.data[28]=0x48;/*2 bytes for user data length*/
    event.data[29]=0x2b;
    event.data[30]=0x62;
    event.data[31]=0x80;
    event.data[32]=0x48;
    event.data[33]=0x04;
    event.data[34]=0x00;
    event.data[35]=0x00;
    event.data[36]=0x09;
    event.data[37]=0xbe;
    event.data[38]=0x6b;
    event.data[39]=0x80;
    event.data[40]=0x28;
    event.data[41]=0x80;
    event.data[42]=0x06;
event.data[43]=0x07;
    event.data[44]=0x00;
    event.data[45]=0x11;
    event.data[46]=0x86;
    event.data[47]=0x05;
    event.data[48]=0x01;
    event.data[49]=0x01;
    event.data[50]=0x01;
    event.data[51]=0x0a;
    event.data[52]=0x80;
    event.data[53]=0x60;
    event.data[54]=0x80;
    event.data[55]=0xa1;
    event.data[56]=0x80;
event.data[57]=0x60;
    event.data[58]=0x07;
    event.data[59]=0x04;
    event.data[60]=0x00;
    event.data[61]=0x00;
    event.data[62]=0x01;
    event.data[63]=0x15;
    event.data[64]=0x03;
    event.data[65]=0x04;
    event.data[66]=0x00;
    event.data[67]=0x00;
    event.data[68]=0x00;
    event.data[69]=0x00;
    event.data[70]=0x00;
 event.data[71]=0x00;
    event.data[72]=0x00;
    event.data[73]=0x00;
    event.data[74]=0x00;
    event.data[75]=0x00;
    event.data[76]=0x6c;
event.data[77]=0x80;
    event.data[78]=0xa1;
    event.data[79]=0x80;
   event.data[80]=0x80;
    event.data[81]=0x02;
    event.data[82]=0x01;
    event.data[83]=0x00;
 event.data[84]=0x02;
    event.data[85]=0x01;
    event.data[86]=0x00;
    event.data[87]=0x30;
    event.data[88]=0x06;
    event.data[89]=0x80;
    event.data[90]=0x01;
    event.data[91]=0x06;
    event.data[92]=0x9c;
    event.data[93]=0x00;
    event.data[94]=0x01;
    event.data[95]=0x00;
    event.data[96]=0x00;
    event.data[97]=0x0;
    event.data[98]=0x00;
    event.data[99]=0x00;
    event.data[100]=0x00;



   TRANSPORT_PutEvent(ITS_SCCP_SRC, &event);
    ITS_EVENT_TERM(&event);

  }
break;
 default :
 printf("\nISIL_ERROR:INAVLID CHOICE");
 }
}

}





}
 /* "C"   */

