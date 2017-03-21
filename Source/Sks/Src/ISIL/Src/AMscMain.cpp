/*********************************-*-CPP-*-**********************************
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:36  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.6  2007/05/04 09:10:16  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.5  2007/04/17 14:16:07  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.4  2007/04/17 08:35:35  ashutosh.singh
 * LOG: Logger Lib related changes
 * LOG:
 * LOG: Revision 1.3  2007/03/19 05:08:28  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/01/05 06:00:43  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:32:02  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:04:35  adutta
 * LOG: Initial implementation
 * LOG:
 *
 * ID: $Id: AMscMain.cpp,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: AMscMain.cpp,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $"

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include <map>
#include <engine++.h>

#include<mtp3_intern.h>
#include <its++.h>
#include <its_transports.h>
#include <its_types.h>
#include <its_link.h>
#include <mtp2_cmn.h>
#include <its_route_rwlock.h>
#include "trace.h"

#ifdef PLATFORM_IMR
extern "C"
{
#include <bpmxxx_platformLib.h>
#include <stdlib.h>
unsigned char HealthNwStack;
}
#endif


#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
SysAddr slfAddr;
#endif



#if defined (ANSI)
#define ITS_MTP2_SRC   ITS_MTP2_ANSI_SRC
#elif defined (CCITT)
#define ITS_MTP2_SRC ITS_MTP2_CCITT_SRC
#endif


#if defined (ANSI)
#define ITS_MTP3_SRC   ITS_MTP3_ANSI_SRC
#elif defined (CCITT)
#define ITS_MTP3_SRC ITS_MTP3_CCITT_SRC
#endif

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

THREAD_RET_TYPE Console_Thread(void *arg);
ITS_THREAD conThread;
void static ShutDownNode();
extern "C" void  read_config();


static void Usage(const char** args)
{
    cout << " Usage: " << args[0] << endl;
    cout << " ConfigFileName <configFile> " << endl;
    cout << endl;
    exit (0);
}


int
ParseArguments(int argc, const char** args)
{
    int i = 4;
    int flag = 1;
    int ret = 0;

    if (argc <= 5)
    {
        Usage (args);
        return -1; 
    }

    for(; i < argc && flag; i++)
    {
        if(strcmp(args[i], "-configFile") == 0)
        {
           flag = 0;
        }
        else
        {
           Usage(args);
        }
    }

    /* from here onwards are engine arguments. */
    return (i - 2);
}
#ifdef PLATFORM_IMR
/*******************************************************************************
 * Function    : bpmAisCallbackFunc                                            *
 * Parameters  : None                                                          *
 * Description :                                                               *
 *                                                                             *
 *                                                                             *
 *                                                                             *
 *******************************************************************************/
extern  "C"
{
void nwStackBpmAisCallbackFunc(struct sAisParam* param)
{

        ISIL_DEBUG_TRACE(("In AIS Handler Function\n"));

        switch(param->messageId)
        {
                case BPM_HEALTHCHECK_MESSAGE:
                       { 
                        ISIL_DEBUG_TRACE((" HealthCheck Callback Function by NW_STACKS \n"));
                        fflush(stdout);

                            bpmRespondToAis (param->invocation,OK);
                        }
                        break;

                case BPM_SELFCARD_STATE_CHANGE:

                       ISIL_DEBUG_TRACE(("SelfCard State Change Callback called/\n"));
                        bpmRespondToAis (param->invocation,OK);
                        break;

                case BPM_PEERCARD_STATE_CHANGE:

                       ISIL_DEBUG_TRACE(("PeerCard State Change Callback called\n"));
                        bpmRespondToAis (param->invocation,OK);
                        break;

                case BPM_MSG_ACK_CONFIGURE:
                        ISIL_DEBUG_TRACE(("Message Acknowledgement received from Executive\n"));
                        break;

                case BPM_SHUTDOWN:
                        ISIL_DEBUG_TRACE(("\n SIGUSR1 RECEIVED by NW_STACKS\n"));
                               TIMERS_Sleep(5);
                       /*         ShutDownNode();


                               ENGINE_Terminate(); */
                      break;
                default:
                        break;
        }
}



}  /* extern  "C" */
#endif

extern  "C"
{
int
main(int argc, const char **args)
{
    int ret;
  #ifdef LOGGER_IMR
    slfAddr.prcr = 0;
    slfAddr.entity = 86;
    slfAddr.clsId = 0;
    slfAddr.rfu = 0;
    slfAddr.inst = 0;
    if(InitLoggingUtility(slfAddr) == 0)
     {
      printf(" ISIL GET REGISTERED  with LOGGER Utility   ");
     }
    else
     {
      printf (" ISIL couldnot  REGISTERED  with LOGGER Utility   ");
     }

  #endif




    ret = ParseArguments(argc, args);

#ifndef MTP2SIM

#ifdef PLATFORM_IMR
    /*  Application will  register with application  */
    bpmGetComponentRegister(nwStackBpmAisCallbackFunc,APPID_NW_STACKS);

    bpmComponentConfigure();  

#endif

#endif 

#ifdef PLATFORM_IMR
 /* replace with  connection lib  */
    read_config();  //ADDED  by ANAND
#else

    read_config();  //ADDED  by ANAND
#endif
    ENGINE_Initialize((argc - ret), &args[ret], NULL, 0);

    ret = ENGINE_Run(argc, args);

    return ret;
}

} /*  extern "C" */



void static
ShutDownNode()
{
    TRANSPORT_Manager *tm;
    TRANSPORT_Control *tr;
    ITS_UINT mask;
    char buf[ITS_PATH_MAX];

    tm = TRANSPORT_GetManager();

    if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
    {
         return;
    }

    for ( tr = tm->listHead;
          tr != NULL; tr = TRANSPORT_HMI_NEXT(tr))
    {
        mask = TRANSPORT_MASK(tr);

        if ((mask & ITS_MTP2_CCITT) == ITS_MTP2_CCITT)
        {
            SS7_LinkPtr lp;

            for (lp = TRANSPORT_SS7_INFO(tr).linkInfo;
                 lp != NULL; lp = lp->next)
            {
               sprintf(buf, "Deactivating ls:%d lc:%d\n",
                       lp->linkSet->linkSet, lp->linkCode);

#ifdef  CCITT
               MGMT_Main_CCITT(MTP3_USER,
                               MGMT_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               lp->linkSet->linkSet, lp->linkCode);
#endif
            }

        }
    }

    RWLOCK_UnlockShared(&tm->transportGate);
}
