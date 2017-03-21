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
 * LOG: Revision 1.1  2007/03/30 04:58:48  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:46  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:57  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.3  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.2  2002/08/29 18:31:26  ngoel
 * LOG: add delimitor '|' after line number
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.7  2002/07/05 19:33:59  yranade
 * LOG: Fix flag handling for IP transports.  Warning removal.
 * LOG:
 * LOG: Revision 6.6  2002/06/13 20:45:01  mmiers
 * LOG: Range checking
 * LOG:
 * LOG: Revision 6.5  2002/05/07 16:23:29  mmiers
 * LOG: Change field separator
 * LOG:
 * LOG: Revision 6.4  2002/05/07 15:58:27  wweng
 * LOG: Add extra fields to format.
 * LOG:
 * LOG: Revision 6.3  2002/03/01 23:12:56  mmiers
 * LOG: Pegs and alarms
 * LOG:
 * LOG: Revision 6.2  2002/02/28 23:32:46  mmiers
 * LOG: Add to alarm API.  Add peg API.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/11/19 16:02:23  mmiers
 * LOG: Wrong thread id.
 * LOG:
 * LOG: Revision 5.2  2001/09/04 16:16:37  mmiers
 * LOG: Move alarm event to callData.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:10  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/06/20 19:18:17  mmiers
 * LOG: Finish up HMI
 * LOG:
 * LOG: Revision 4.5  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.4  2001/05/09 22:21:31  mmiers
 * LOG: Updates after ADP brainstorming.
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
#include <its_alarm.h>
#include <its_iniparse.h>
#include <its_trace.h>
#include <its_thread.h>
#include <its_tq_trans.h>
#include <its_assertion.h>
#include <its_timers.h>

#ident "$Id: its_alarm_orig.c,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $"

/*
 * local
 */
static ITS_THREAD   alarmThread;
static ITS_HANDLE   alarmHandle;
static ITS_Class    baseClass;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an alarm
 *
 *  Input Parameters:
 *      text - the text you want to send.
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
AlarmSend(ITS_OCTET *bytes, ITS_UINT len)
{
    ITS_EVENT ev;

    ITS_EVENT_INIT(&ev, ITS_NO_SRC, len);

    memcpy(ev.data, bytes, len);

    TRANSPORT_PutEvent(ALARM_MANAGER_INSTANCE, &ev);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle alarm events.
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
AlarmThread(void *arg)
{
    ITS_EVENT alarmEvent;

    memset(&alarmEvent, 0, sizeof(ITS_EVENT));

    TRANSPORT_IS_ACTIVE(alarmHandle) = ITS_TRUE;

    while (TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(alarmHandle))
                                                        (alarmHandle,
                                                        &alarmEvent) ==
           ITS_SUCCESS)
    {
        switch (alarmEvent.src)
        {
        case ALARM_MANAGER_INSTANCE:
            /* termination message */
            ITS_TRACE_DEBUG(("AlarmThread: exiting ok\n"));

            TRANSPORT_IS_ACTIVE(alarmHandle) = ITS_FALSE;

            THREAD_NORMAL_EXIT;
            break;

        default:
            /* handle an alarm */
            CALLBACK_CallCallbackList(ALARM_Callbacks,
                                      NULL,
                                      (ITS_POINTER)&alarmEvent);
            break;
        }
    }

    TRANSPORT_IS_ACTIVE(alarmHandle) = ITS_FALSE;

    /* NOTREACHED */
    THREAD_NORMAL_EXIT;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the ALARM subsystem to a ready state.
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
    ITS_TRACE_DEBUG(("ALARM_Initialize:\n"));

    /* create transport */
    if ((alarmHandle = TQUEUETRAN_CreateTransport("Alarms",
                                                  ALARM_MANAGER_INSTANCE,
                                                  0)) == NULL)
    {
        ITS_TRACE_ERROR(("ALARM_Initialize: Couldn't create transport."));

        CALLBACK_DestroyManager(ALARM_Callbacks);

        return (ITS_ENOTRANSPORT);
    }


    /* create thread */
    if (THREAD_CreateThread(&alarmThread, 0,
                            AlarmThread, NULL,
                            ITS_TRUE) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ALARM_Initialize: Couldn't create thread.\n"));

        CALLBACK_DestroyManager(ALARM_Callbacks);

        TQUEUETRAN_DeleteTransport(alarmHandle);

        return (ITS_EBADTHREAD);
    }

    baseClass = itsALARM_Class;
    itsALARM_Class = (ITS_Class)&itsALARM_ClassRec;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the ALARM subystem.
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

    ITS_TRACE_DEBUG(("ALARM_Terminate:\n"));

    itsALARM_Class = baseClass;

    stopEvent.src = ALARM_MANAGER_INSTANCE;
    stopEvent.len = 0;
    stopEvent.data = NULL;

    /* send stop message */
    TRANSPORT_PutEvent(ALARM_MANAGER_INSTANCE, &stopEvent);

    /* delete thread */
    THREAD_WaitForThread(&alarmThread, &status);

    /* delete transport */
    TQUEUETRAN_DeleteTransport(alarmHandle);
}

/*
 * the class record
 */
ITSDLLAPI ALARM_ClassRec itsALARM_ClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsALARMS_ClassRec, /* ALARMS is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        ALARM_CLASS_NAME,               /* class name */
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
    },
    /* alarm part */
    {
        AlarmSend
    }
};
