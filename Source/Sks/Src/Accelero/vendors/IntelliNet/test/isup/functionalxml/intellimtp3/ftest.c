/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: ftest.c,v 1.1.1.1 2007-10-08 11:12:22 bsccs2 Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:24:58  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:49:28  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:15:16  cvsadmin
 * BSC project
 *
 * Revision 9.1  2005/03/23 12:55:08  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.3  2005/03/21 13:54:21  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1.4.2.8.1  2004/02/11 08:36:28  sjaddu
 * Changes done for testing active-stand by config
 *
 * Revision 7.1.4.2.2.1  2003/09/05 09:55:09  akumar
 * To accomodate msg based redundancy arch.
 *
 * Revision 7.1.4.2  2003/03/31 10:47:50  akumar
 * Moved Callback functions from main.c file to ftest.c file in order to
 * run the app.
 *
 * Revision 7.1.4.1  2003/03/27 13:08:35  akumar
 * Removed Extra Ref to the Stack, Removed some console commands as well.
 *
 * Revision 7.1  2002/08/26 22:10:39  mmiers
 * Begin PR6.2
 *
 * Revision 1.5  2002/08/01 16:01:46  ssharma
 * Merge from ISUP_PR7 branch.
 *
 * Revision 1.4.2.1  2002/07/10 20:22:09  ssharma
 * Pass the right handle.
 *
 * Revision 1.4  2002/06/22 22:04:07  hbalimid
 * ANSI and ITU specific functioanlity in place
 *
 * Revision 1.3  2002/06/22 20:43:35  hbalimid
 * variant specific makefile for test application
 *
 * Revision 1.2  2002/05/20 15:58:49  sjaddu
 * Merge from PR6, remove unwanted directories.
 *
 * Revision 1.1.2.3  2002/05/09 18:40:21  labuser
 * Merge from ISUP_APR_19_2002 to PR6.
 *
 * Revision 1.1.2.2.2.2  2002/04/26 01:14:25  labuser
 * Base line for functional test
 *
 *
 ****************************************************************************/

#include <stdio.h>

#include <its.h>
#include <engine.h>
#include <its_app.h>
#include <its_timers.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_thread_pool.h>
#include <its_worker.h>
#include <its_redundancy.h>

#include "ftest.h"

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#else
#error "Protocol family not defined."
#endif

#if defined(CCITT)
#define HANDLE ISS7_CCITT_Stack
#elif defined(ANSI)
#define HANDLE ISS7_ANSI_Stack
#endif

/* Trans id for sctp*/
int __ISUP_SCTP_TARNS_ID_1 = 0;
int __ISUP_SCTP_TARNS_ID_2 = 0;


#define ISUP_RECEIVE_QUEUE_ID 401

void WorkerThreadDispatchFunction(TPOOL_THREAD* thr, ITS_HANDLE handle);
static void DumpITSEvent(ITS_EVENT* ev);
int RouteApp(ITS_HDR *hdr,ITS_EVENT *event);

extern void ExecuteCommand(DBC_Server *dbc, const char *cmdLine);


void ApplicationMembershipChangeCb( ITS_POINTER object,
                                    ITS_POINTER userData,
                                    ITS_POINTER callData);

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is a Call Back function, used for sending the MTP3
 *      Status Indications to the App.
 *
 *  Input Parameters:
 *      object   - 1st Call Back function argument.
 *      userData - 2nd Call Back function argument.
 *      callData - 3rd Call Back function argument.
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
MTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    /* Do nothing */
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is Call Back function, used for sending the ISUP Local
 *      Congestion Indications to the App.
 *
 *  Input Parameters:
 *      object   - Call Back function argument
 *      userData - Call Back function argument
 *      callData - Per invocation callback function argument
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
ISUPMgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ISUP_CONGESTION_ENTRY *cong = (ISUP_CONGESTION_ENTRY *)callData;
    ITS_OCTET mType;
    ITS_OCTET buf[255];
    ITS_USHORT len;

    printf("Entered IsupMgmt\n");
    printf("\n--The ISUP Local Congestion ID is 0x%02x--\n", cong->congId);
    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is called when App is initialized 
 *
 *  Input Parameters:
 *      NONE. 
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
void ftestPreFunc(void)
{
    static char dmpFile[256];
    CALLBACK_Manager* cbManager;
    int ret = 0;

    printf("Ftest: Entered PreFunc\n");

    strcpy(dmpFile,APPL_GetConfigFileName());
    strcat(dmpFile,".dmp");

    printf("App Dmp Name = %s\n", dmpFile);

#if defined(PROTOTYPE)
    cbManager = DSM_GetMembershipChangeCallbacks(DSM_MgmtDataFtGroupId);
    if (cbManager == NULL)
    {
        return;
    }
    ret = CALLBACK_AddCallback(cbManager, ApplicationMembershipChangeCb, NULL);
    if (ret != ITS_SUCCESS)
    {
        printf("ERROR PreFunc:  CALLBACK_AddCallback failed");

       return;
    }
#endif

    printf("Ftest: Ready to accept Commands!\n");

    return;
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
void ftestPostFunc(void)
{
    printf("Ftest: Entered PostFunc\n");

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is called for Routing Purpose. 
 *
 *  Input Parameters:
 *      hdr - provides context for individual messages. 
 *      event - Message to be routed in tlv format.
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
int
RouteApp(ITS_HDR *hdr,ITS_EVENT *event)
{
    ITS_INT ret = 0;
    TPOOL_THREAD* thread;

    ITS_HDR routeHeader;

    routeHeader.type = ITS_ISUP;
    routeHeader.context.cic = hdr->context.cic;


    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return ret;
    }

    ROUTE_AddApplication( ((WORKER_Control*)thread)->worker.instance, &routeHeader);

    printf("Ftest: RouteApp: Dispatching worker thread\n");

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_BACK_PTR(thread));

    return ( ((WORKER_Control*)thread)->worker.instance );
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Dispatches the Event to a Thread.  
 *
 *  Input Parameters:
 *      thr - Pointer to Pool of Threads.
 *      handle - void pointer. 
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
WorkerThreadDispatchFunction(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    ITS_USHORT workerInstance;
    ITS_EVENT event;
    ITS_INT ret;

    WORKER_Control* worker = (WORKER_Control*)thr;
    workerInstance = worker->worker.instance;
    printf("Application:: Instance Number of Worker is ... %d\n",workerInstance);

    memset(&event,0,sizeof(event));

    while(1)
    {
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
                printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }
        printf("Application:: Event Src = %x\n", event.src);
        DumpITSEvent(&event);

        if ( event.src == ITS_ISUP_SRC )
        {
            printf("Application:: Decoding the Received Event from ISUP:\n");
            if (ISUP_ReceiveMsg(HANDLE, &event) == ITS_SUCCESS)
            {
                printf("Application:: Worker Thread: ISUP msg receive success\n");
                printf("------------------------------------------------------\n");
            }
        }
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function porvides HEX dump of the Event.  
 *
 *  Input Parameters:
 *      ev - Received Event from Stack. 
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
static void
DumpITSEvent(ITS_EVENT* ev)
{
    int i;

    switch(ev->src)
    {
        case ITS_ISUP_CCITT_SRC:
             printf("Event Source is ITS_ISUP_CCITT_SRC\n");
             break;
        case ITS_ISUP_ANSI_SRC:
             printf("Event Source is ITS_ISUP_ANSI_SRC\n");
             break;
        case ITS_MTP3_CCITT_SRC:
             printf("Event Source is ITS_MTP3_CCITT_SRC\n");
             break;
        case ITS_MTP3_ANSI_SRC:
             printf("Event Source is ITS_MTP3_ANSI_SRC\n");
             break;
        case ITS_TIMER_SRC:
             printf("Event Source is ITS_TIMER_SRC\n");
             break;
        default:
             printf("Event Source is * UNKNOWN * (%d)\n", ev->src);
             break;
    }

    printf("Event Length: %d\n", ev->len);
    printf("Event Dump follows:\n");

    for (i = 0; i < ev->len; i++)
    {
        printf("%02x ", ev->data[i]);
        if (!((i+1) % 20))
        {
            printf("\n");
        }
    }
    if ((i+1) % 20)
    {
        printf("\n");
    }

    printf("------------------------------------------------------\n");
}

int
SelectApplication(ITS_HDR *hdr,ITS_EVENT *event)
{
    ITS_INT ret = 0;
    TPOOL_THREAD* thread;

    ITS_HDR routeHeader;

    routeHeader.type = ITS_ISUP;
    routeHeader.context.cic = hdr->context.cic;


    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return ret;
    }

    printf("Ftest: SelectApplication******************: Dispatching worker thread\n");

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_BACK_PTR(thread));

    return ( ((WORKER_Control*)thread)->worker.instance );
}
int
Node1SelectApplication(ITS_HDR *hdr,ITS_EVENT *event)
{

    if (hdr->context.cic % 2 == 0)
    {
    ITS_INT ret = 0;
    TPOOL_THREAD* thread;

    ITS_HDR routeHeader;

    routeHeader.type = ITS_ISUP;
    routeHeader.context.cic = hdr->context.cic;


    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return ret;
    }

    ROUTE_AddApplication( ((WORKER_Control*)thread)->worker.instance, &routeHeader);

    printf("Ftest: Node1SelectApplication: ******* Dispatching worker thread\n");

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_BACK_PTR(thread));

    return ( ((WORKER_Control*)thread)->worker.instance );

    }

    return ITS_NO_SRC;

}

int
Node2SelectApplication(ITS_HDR *hdr,ITS_EVENT *event)
{

    if (hdr->context.cic % 2 != 0)
    {
    ITS_INT ret = 0;
    TPOOL_THREAD* thread;

    ITS_HDR routeHeader;

    routeHeader.type = ITS_ISUP;
    routeHeader.context.cic = hdr->context.cic;


    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return ret;
    }

    ROUTE_AddApplication( ((WORKER_Control*)thread)->worker.instance, &routeHeader);

    printf("Ftest: RouteApp: Dispatching worker thread\n");

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_BACK_PTR(thread));

    return ( ((WORKER_Control*)thread)->worker.instance );

    //    return ISUP_RECEIVE_QUEUE_ID;
    }

    return ITS_NO_SRC;

}

int
NoneSelectApplication(ITS_HDR *hdr,ITS_EVENT *event)
{

    return ITS_NO_SRC;

}


