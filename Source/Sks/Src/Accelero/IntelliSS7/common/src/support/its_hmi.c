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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:28  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:00  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:39  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:59  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.40.1  2005/01/05 07:21:26  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/11/12 22:33:31  mmiers
 * LOG: Clean up on exit.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.8  2001/06/20 19:18:17  mmiers
 * LOG: Finish up HMI
 * LOG:
 * LOG: Revision 4.7  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.6  2001/05/16 01:19:15  mmiers
 * LOG: When cond_timedwait returns on timeout, the mutex *is* held.
 * LOG:
 * LOG: Revision 4.5  2001/05/09 22:21:31  mmiers
 * LOG: Updates after ADP brainstorming.
 * LOG:
 * LOG: Revision 4.4  2001/05/02 19:06:02  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.3  2001/05/02 00:01:51  mmiers
 * LOG: Finish alarm implementation.  HMI just needs the monitor
 * LOG: algorithm.
 * LOG:
 * LOG: Revision 4.2  2001/05/01 23:09:03  mmiers
 * LOG: Add functionality for HMI and alarm.  The rest is pretty easy.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_app.h>
#include <its_assertion.h>
#include <its_hmi.h>
#include <its_trace.h>
#include <its_tq_trans.h>
#include <its_timers.h>

#ident "$Id: its_hmi.c,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $"

/*
 * extern
 */
ITSDLLAPI CALLBACK_Manager   *HMI_Callbacks = NULL;

/*
 * locals
 */
static ITS_THREAD   hmiThread;
static ITS_HANDLE   hmiHandle = NULL;
static ITS_UINT     hmiCheckInterval = HMI_CHECK_INTERVAL;
static ITS_UINT     hmiTimeOutInterval = HMI_TIMEOUT_INTERVAL;
static ITS_MUTEX    hmiGate;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Default transport timeout interval.
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
 *      timeout interval, in msecs
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
HMI_GetTimeOutInterval()
{
    return hmiTimeOutInterval;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Default health management action.  Resets the transport, maybe
 *      creates a new thread.
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
ITSDLLAPI void
HMI_Reset(TRANSPORT_Control *tc)
{
    ITS_TRACE_WARNING(("HMI detected update failure for transport %s : %d\n",
                       TRANSPORT_NAME(tc), TRANSPORT_INSTANCE(tc)));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle messages (timers or stop event).
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
static THREAD_RET_TYPE
HMIThread(void *arg)
{
    ITS_EVENT hmiEvent;
    ITS_SERIAL timer;
    TRANSPORT_Manager *tm;
    TRANSPORT_Control *ent;
    ITS_TIME curTick;

    memset(&hmiEvent, 0, sizeof(ITS_EVENT));

    timer = TIMERS_StartTimer(HEALTH_MANAGER_INSTANCE,
                              hmiCheckInterval,
                              NULL, 0);

    ITS_C_ASSERT(timer != 0);

    tm = TRANSPORT_GetManager();

    TRANSPORT_IS_ACTIVE(hmiHandle) = ITS_TRUE;

    while (TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(hmiHandle))
                                                        (hmiHandle,
                                                        &hmiEvent) ==
           ITS_SUCCESS)
    {
        switch (hmiEvent.src)
        {
        case HEALTH_MANAGER_INSTANCE:
            /* termination message */
            ITS_TRACE_DEBUG(("HMIThread: exiting ok\n"));

            TIMERS_CancelTimer(timer);

            TRANSPORT_IS_ACTIVE(hmiHandle) = ITS_FALSE;

            THREAD_NORMAL_EXIT;
            break;

        default:
            /* check transports */
            if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
            {
                ITS_TRACE_CRITICAL(("HMIThread: RWLOCK_LockShared Failed\n"));
                abort();
            }

            curTick = TIMERS_Time();
            for (ent = tm->listHead;
                 ent != NULL;
                 ent = TRANSPORT_HMI_NEXT(ent))
            {
                /* verify up to date */
                if (TRANSPORT_IS_ACTIVE(ent) &&
                    (curTick - TRANSPORT_LAST_UPDATE(ent)) >
                    (ITS_TIME)HMI_GetTimeOutInterval())
                {
                    if (!CALLBACK_IsListEmpty(HMI_Callbacks))
                    {
                        CALLBACK_CallCallbackList(HMI_Callbacks,
                                                  (ITS_POINTER)ent,
                                                  NULL);
                    }
                    else
                    {
                        HMI_Reset(ent);
                    }
                }
            }

            RWLOCK_UnlockShared(&tm->transportGate);

            /* start another timer */
            timer = TIMERS_StartTimer(HEALTH_MANAGER_INSTANCE,
                                      hmiCheckInterval,
                                      NULL, 0);

            ITS_C_ASSERT(timer != 0);
            break;
        }
    }

    TRANSPORT_IS_ACTIVE(hmiHandle) = ITS_FALSE;

    /* NOTREACHED */
    THREAD_NORMAL_EXIT;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the HMI subsystem to a ready state.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    RESFILE_Manager *globalRes = NULL;
    static char value[ITS_PATH_MAX];
    const char *name = APPL_GetConfigFileName();

    ITS_TRACE_DEBUG(("HMI_Initialize:\n"));

    /* get resources */
    globalRes = RESFILE_CreateResourceManager(name);

    if (globalRes)
    {
        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  HMI_INTERVAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            hmiCheckInterval = RESFILE_ParseNum(value);
        }

        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  HMI_TIMEOUT_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            hmiTimeOutInterval = RESFILE_ParseNum(value);
        }
    }

    /* create mutex */
    if (MUTEX_CreateMutex(&hmiGate, 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* create callback manager */
    if ((HMI_Callbacks = CALLBACK_InitManager()) == NULL)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create callback manager\n"));

        MUTEX_DeleteMutex(&hmiGate);

        return (ITS_ENOMEM);
    }

    /* create transport */
    if ((hmiHandle = TQUEUETRAN_CreateTransport("Health Manager",
                                                HEALTH_MANAGER_INSTANCE,
                                                0)) == NULL)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create transport."));

        MUTEX_DeleteMutex(&hmiGate);

        CALLBACK_DestroyManager(HMI_Callbacks);

        return (ITS_ENOTRANSPORT);
    }


    /* create thread */
    if (THREAD_CreateThread(&hmiThread, 0,
                            HMIThread, NULL,
                            ITS_TRUE) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create thread.\n"));

        MUTEX_DeleteMutex(&hmiGate);

        CALLBACK_DestroyManager(HMI_Callbacks);

        TQUEUETRAN_DeleteTransport(hmiHandle);

        return (ITS_EBADTHREAD);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the HMI subystem.
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
static void
ClassTerminate(ITS_Class objClass)
{
    void *status;
    ITS_EVENT stopEvent;

    ITS_TRACE_DEBUG(("HMI_Terminate:\n"));

    stopEvent.src = HEALTH_MANAGER_INSTANCE;
    stopEvent.len = 0;
    stopEvent.data = NULL;

    /* send stop message */
    TRANSPORT_PutEvent(HEALTH_MANAGER_INSTANCE, &stopEvent);

    /* delete thread */
    THREAD_WaitForThread(&hmiThread, &status);

    /* delete transport */
    TQUEUETRAN_DeleteTransport(hmiHandle);

    /* delete callback manager */
    CALLBACK_DestroyManager(HMI_Callbacks);

    /* delete mutex */
    MUTEX_DeleteMutex(&hmiGate);
}

/*
 * the class record
 */
ITSDLLAPI ITS_ClassRec itsHMI_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        HMI_CLASS_NAME,                 /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsHMI_Class = (ITS_Class)&itsHMI_ClassRec;
