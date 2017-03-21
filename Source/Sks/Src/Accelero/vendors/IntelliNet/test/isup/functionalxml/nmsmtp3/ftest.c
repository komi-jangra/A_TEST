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
 * Revision 1.1.1.1  2007/10/04 13:24:59  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:49:28  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:15:17  cvsadmin
 * BSC project
 *
 * Revision 9.1  2005/03/23 12:55:13  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.2  2005/03/21 13:54:26  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1  2002/08/26 22:10:39  mmiers
 * Begin PR6.2
 *
 * Revision 1.5  2002/08/01 16:01:46  ssharma
 * Merge from ISUP_PR7 branch.
 *
 * Revision 1.4.2.3  2002/07/25 21:52:06  ssingh
 * Infinite while loop is removed from Worker Thread Dispatch function.
 *
 * Revision 1.4.2.2  2002/07/06 06:16:52  hbalimid
 * Took care of all the warnings.
 *
 * Revision 1.4.2.1  2002/06/29 16:52:55  ssharma
 * Use correct handle for ReceiveMsg.
 *
 * Revision 1.4  2002/06/27 17:44:46  hbalimid
 * Modified to take care of ANSI ISUP testing
 *
 * Revision 1.3  2002/06/25 19:07:02  ssingh
 * updated to give good display
 *
 * Revision 1.2  2002/05/20 15:58:49  sjaddu
 * Merge from PR6, remove unwanted directories.
 *
 * Revision 1.1.2.2  2002/04/13 06:09:04  hbalimid
 * ISUP Functional test with NMS MTP3 and multiple vendor support at layer 2
 *
 *
 ****************************************************************************/

/*
 * system includes
 */
#include <stdio.h>

/*
 * local includes
 */
#include "ftest.h"
#include <printISUPMsg.h>

/*
 * IntelliSS7 includes
 */
#include <its.h>
#include <engine.h>
#include <its_app.h>
#include <its_timers.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_thread_pool.h>
#include <its_worker.h>

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

extern void ExecuteCommand(DBC_Server *dbc, const char *cmdLine);
void
WorkerThreadDispatchFunction(TPOOL_THREAD* thr, ITS_HANDLE handle);
void DumpITSEvent(ITS_EVENT* ev);


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     PreFunc of functional test 
 *
 *  Input Parameters:
 *      None
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
ftestPreFunc(void)
{
    char dmpFile[256];

    printf("Ftest: Entered PreFunc\n");

    strcpy(dmpFile,APPL_GetConfigFileName());
    strcat(dmpFile,".dmp");

    printf("App Dmp Name = %s\n", dmpFile);

   /*
    * This is supposed to be the correct place
    * where DBC_SetDoCommand is called
    * still the old method works...in main
    */

    printf("Before DBC_SetDoCommand() in ftestPreFunc\n");
    DBC_SetDoCommand(ExecuteCommand);
    printf("After DBC_SetDoCommand() in ftestPreFunc\n");

    printf("Ftest: Leaving PreFunc...\n");
    printf("Ready to accept commands!\n");

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     PostFunc of functional test
 *
 *  Input Parameters:
 *      None
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
ftestPostFunc(void)
{
    printf("Ftest: Entered PostFunc\n");

    printf("Ftest: Leaving PostFunc\n");

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     RouteApp of functional test
 *     As this test doesn't do a RouteAdd, ISUP calls this callback
 *
 *  Input Parameters:
 *      ITS Header
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Worker instance.
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
 *     Dispatch function of the worker thread
 *
 *  Input Parameters:
 *      thread object of TPOOL
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

    memset(&event, 0, sizeof(event));
/*
    while(1)
    {
*/
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
                printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }
        printf("Application:: Event Src = %x\n", event.src);
        DumpITSEvent(&event);

        if ( event.src == ITS_ISUP_SRC )
        {
	    if (ISUP_ReceiveMsg(HANDLE, &event) == ITS_SUCCESS)
	    {
	        printf("Application:: Worker Thread: ISUP msg receive success\n");
                printf("------------------------------------------------------\n");
	    }
        }
/*
    }
*/

}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Print the given ITS event
 *
 *  Input Parameters:
 *      ITS Event
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
DumpITSEvent(ITS_EVENT* ev)
{
    int i=0;

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

    printf("The length was:  %d\n", ev->len);
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
