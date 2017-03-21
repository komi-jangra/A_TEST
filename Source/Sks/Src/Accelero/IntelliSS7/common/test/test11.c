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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: test11.c,v 1.1.1.1 2007-10-08 11:11:59 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:32  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:14  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:24  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:24  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/01/18 23:19:23  mmiers
 * LOG: Profiling
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:13  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/07/07 22:27:50  mmiers
 * LOG:
 * LOG:
 * LOG: New test for IMAL.
 * LOG:
 * LOG: Revision 2.3  2000/03/29 18:26:53  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks from testing.
 * LOG:
 * LOG: Revision 2.2  1999/12/18 00:35:38  mmiers
 * LOG: Continued tweaks.
 * LOG:
 * LOG: Revision 2.1  1999/12/17 21:55:27  mmiers
 * LOG: Try this on DECUNIX
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:28  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.7  1999/08/24 02:45:52  mmiers
 * LOG:
 * LOG:
 * LOG: Update the test to reflect current philosophy.
 * LOG:
 * LOG: Revision 1.6  1999/08/18 16:36:49  mmiers
 * LOG:
 * LOG:
 * LOG: Finish comments.
 * LOG:
 * LOG: Revision 1.5  1999/08/18 16:19:48  mmiers
 * LOG:
 * LOG:
 * LOG: Add in comments.
 * LOG:
 * LOG: Revision 1.4  1999/08/18 15:16:00  mmiers
 * LOG:
 * LOG:
 * LOG: Build the C test.   Finish the C service API.
 * LOG:
 * LOG: Revision 1.3  1999/07/27 22:34:20  mmiers
 * LOG:
 * LOG:
 * LOG: Update the infrastructure tests.
 * LOG:
 * LOG: Revision 1.2  1999/03/12 00:06:14  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.2  1999/03/01 20:28:19  mmiers
 * LOG:
 * LOG:
 * LOG: Update the test.
 * LOG:
 * LOG: Revision 1.1  1999/03/01 18:12:13  mmiers
 *
 ****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(unix)
#include <unistd.h>
#include <signal.h>
#endif

#include <its.h>
#include <its_app.h>
#include <its_timers.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_worker.h>
#include <its_ss7_trans.h>
#include <its_service.h>

#include <ansi/tcap.h>
#include <ansi/sccp.h>

static TPOOL *borderPool;
static TPOOL *actorPool;
static ITS_BOOLEAN globalStart = ITS_FALSE;

#define FIRST_BORDER    1
#define NUM_BORDER      2
#define FIRST_ACTOR     (FIRST_BORDER + NUM_BORDER)
#define NUM_ACTOR       10

/*
 * create the transaction unit-of-work threads
 */
static TPOOL_THREAD *
CreateActorTransports(TPOOL *pool, int stackSize)
{
    WORKER_Control* actor;
    int thisActor = FIRST_ACTOR;

    actor = WORKER_InitWorker(stackSize, "An actor", (ITS_USHORT)thisActor,
                              ITS_SCCP|ITS_TCAP|ITS_TRANSPORT_TQUEUE);

    thisActor++;

    return (&WORKER_THREAD(actor));
}

/*
 * create the IPC transports
 */
static TPOOL_THREAD *
CreateBorderTransports(TPOOL *pool, int stackSize)
{
    WORKER_Control* border;
    static int thisBorder = FIRST_BORDER;

    switch (thisBorder)
    {
    case 1:
        border = WORKER_InitWorker(stackSize,
                                   "First Border", (ITS_USHORT)thisBorder,
                                   ITS_SCCP|ITS_TCAP|ITS_TRANSPORT_DELAY_CREATE|
                                       ITS_TRANSPORT_CSOCKET);
        break;

    case 2:
        border = WORKER_InitWorker(stackSize,
                                   "Second Border", (ITS_USHORT)thisBorder,
                                   ITS_SCCP|ITS_TCAP|ITS_TRANSPORT_DELAY_CREATE|
                                       ITS_TRANSPORT_SSOCKET);
        break;

    default:
        printf("Error: Too many border transports.\n");
        exit(0);
    }

    thisBorder++;

    return (&WORKER_THREAD(border));
}

/*
 * handle a TCAP transaction
 *
 * The application selector dispatches each new incoming TCAP
 * transaction to a thread that runs this function.  This function
 * should not exit until the transaction has been completely
 * finished (ended).
 */
void
ActorDispatch(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    ITS_HANDLE h;
    ITS_EVENT event;
    ITS_HDR hdr;
    TCAP_DLG dlg;

    /* getting NULL here is a fatal error */
    h = ITS_Initialize(WORKER_MASK(work),
                       WORKER_INSTANCE(work));
    assert(h != NULL);
    
    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!WORKER_THREAD(work).exit)
    {
        /* Note: we could use ITS_GetNextEvent() here. */
        if (WORKER_GetNextEvent(work, &event) != ITS_SUCCESS)
        {
            continue;
        }

        switch (event.src)
        {
        case ITS_TCAP_SRC:
            TCAP_ReceiveDialogue(h, &event, &hdr, &dlg);
            break;

        default:
            break;
        }
    }
    
    /* this is good practice */
    ITS_Terminate(h);
}

/*
 * transmit incoming IPC events to SCCP for processing
 */
void
BorderDispatch(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    ITS_HANDLE h;
    ITS_EVENT event;

    /* getting NULL here is a fatal error */
    h = ITS_Initialize(WORKER_MASK(work),
                       WORKER_INSTANCE(work));
    assert(h != NULL);
    
    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!WORKER_THREAD(work).exit)
    {
        /* Note: we could use ITS_GetNextEvent() here. */
        if (WORKER_GetNextEvent(work, &event) != ITS_SUCCESS)
        {
            continue;
        }

        event.src = ITS_MTP3_SRC;

        if (TRANSPORT_PutEvent(ITS_SCCP_SRC, &event) != ITS_SUCCESS)
        {
            printf("Couldn't send message to SCCP\n");
        }
    }
    
    /* this is good practice */
    ITS_Terminate(h);
}

/****************************************************************************
 *  Purpose:
 *      Routes the TCAP message to the application based on the dialog id
 *      This functions as the "application selector" as documented by
 *      ROUTE_*
 *
 *  Input Parameters:
 *      hdr - the per-thread application context (dialogue_id).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns the instance id of the first available dispatch thread
 *
 *  Notes:
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *
 *   DO NOT THROW EXCEPTIONS FROM THIS CALL.  THE CALLER IS A "C" FUNCTION
 *   THAT HAS A LOCKED MUTEX.  AN UNCAUGHT EXCEPTION ORIGINATING FROM THIS
 *   FUNCTION MEANS THE MUTEX WILL STAY LOCKED, EFFECTIVELY BLOCKING ANY NEW
 *   TCAP TRANSACTION OR SCCP CONNECTION FROM THE PROGRAM.  YOU HAVE BEEN
 *   WARNED.
 *
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING 
 *
 *  See Also:
 ****************************************************************************/
ITS_USHORT
SelectApplication(ITS_HDR *hdr, ITS_EVENT* event)
{
    TPOOL_THREAD* thread;
    int did = hdr->context.dialogue_id;
    WORKER_Control* actor;
    int ret;

    ret = TPOOL_GetFirstAvailThread(actorPool, &thread);
    assert(ret == ITS_SUCCESS);

    actor = (WORKER_Control *)thread;

    ROUTE_AddApplication(WORKER_INSTANCE(actor), hdr);
        
    /* Invoke the Function for the thread */
    ret = TPOOL_DispatchOnThread(thread,
                                 ActorDispatch,
                                 NULL);
    assert(ret == ITS_SUCCESS); 
        
    return (WORKER_INSTANCE(actor));
}

/*
 * Initialization function.  Build the thread pools
 */
void
InitFunc(int argc, const char **argv)
{
    APPL_SetName("HLR");

    /* Add our stack */
    if (ITS_AddFeature(itsINTELLISS7_Class) != ITS_SUCCESS)
    {
        printf("Fatal error adding stack.\n");

        SERVICE_CallHandler(SERV_HANDLER_STOP);

        return;
    }

    /* needed by multithreaded programs */
    if (ITS_GlobalStart(ITS_SCCP|ITS_TCAP) != ITS_SUCCESS)
    {
        printf("Fatal error starting stack.\n");

        SERVICE_CallHandler(SERV_HANDLER_STOP);

        return;
    }
    
    globalStart = ITS_TRUE;

    /* set the application selector for TCAP */
    if (ROUTE_SetApplicationSelector(SelectApplication) == NULL)
    {
        printf("Fatal error setting app selector.\n");

        SERVICE_CallHandler(SERV_HANDLER_STOP);

        return;
    }

    /* create this first, so that any incoming transaction that
     * comes in quickly after startup has a handler */
    if ((actorPool = TPOOL_InitPool(NULL)) == NULL)
    {
        printf("Fatal error creating unit-of-work transports pool.\n");

        SERVICE_CallHandler(SERV_HANDLER_STOP);

        return;
    }

    if (TPOOL_CreatePool(actorPool, NUM_ACTOR, 0, /* 0 says use OS default */
                         CreateActorTransports) != ITS_SUCCESS)
    {
        printf("Fatal error creating unit-of-work transports pool.\n");

        SERVICE_CallHandler(SERV_HANDLER_STOP);

        return;
    }

    /* create this second */
    if ((borderPool = TPOOL_InitPool(NULL)) == NULL)
    {
        printf("Fatal error creating IPC transports pool.\n");

        SERVICE_CallHandler(SERV_HANDLER_STOP);

        return;
    }

    if (TPOOL_CreatePool(borderPool, NUM_BORDER, 0, /* 0 says use OS default */
                         CreateBorderTransports) != ITS_SUCCESS)
    {
        printf("Fatal error creating unit-of-work transports pool.\n");

        SERVICE_CallHandler(SERV_HANDLER_STOP);

        return;
    }
}

/*
 * Main function.  Not much to do other than sleep.  The
 * "main" thread executes this until a stop signal is
 * received.
 */
void
MainFunc(void)
{
    TIMERS_Sleep(5);
}

/*
 * termination handler
 */
void
TermFunc(void)
{
    TPOOL_DestroyPool(actorPool);

    TPOOL_WaitForDestroyComplete();

    /*
     * Normally, you kill your exterior comm points FIRST.
     * However, if your app selector is smart enough, and
     * your application simple enough, you can kill your
     * actor pool first, which allows you to terminate running
     * transactions before terminating IPC.  Thus the call to
     * TPOOL_WaitForDestroyComplete() above.
     */
    TPOOL_DestroyPool(borderPool);

    if (globalStart)
    {
        ITS_GlobalStop();

        ITS_RemFeature(itsINTELLISS7_Class);
    }
}

int
main(int argc, const char **argv)
{
    int ret;

    ret = SERVICE_Initialize("HLR", "HLR_Service");

    assert(ret == ITS_SUCCESS);

    SERVICE_SetInitFunction(InitFunc);
    SERVICE_SetMainFunction(MainFunc);
    SERVICE_SetTermFunction(TermFunc);

    SERVICE_ProcessCommandLine(argc, argv);

    if (SERVICE_GetType() == ST_SERVICE)
    {
        SERVICE_RunAsService();
    }
    else if (SERVICE_GetType() == ST_CONSOLE_APPLICATION)
    {
        SERVICE_RunAsConsoleApplication(argc, argv);
    }

    SERVICE_Terminate();

    return (SERVICE_GetExitCode());
}

