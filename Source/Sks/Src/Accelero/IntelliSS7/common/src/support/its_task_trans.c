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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:29  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:19  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:46  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:40  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:01  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.2  2004/12/22 11:53:55  ssingh
 * LOG: ITS_EVENT_TERM is back in GetNextEvent to prevent memory leak
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/06 14:09:43  mmanikandan
 * LOG: Issue in GetNextEvent
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/11/15 18:07:36  mmiers
 * LOG: Add exit proc for SCTP transports.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.5  2001/05/16 20:10:53  mmiers
 * LOG: Locating bottlenecks.
 * LOG:
 * LOG: Revision 4.4  2001/05/16 01:19:15  mmiers
 * LOG: When cond_timedwait returns on timeout, the mutex *is* held.
 * LOG:
 * LOG: Revision 4.3  2001/05/02 19:58:55  mmiers
 * LOG: Add thread pool shutdown logic.  People using the C API
 * LOG: need to convert to WORKER_GetExit() instead of TPOOL_THREAD_EXIT().
 * LOG:
 * LOG: Revision 4.2  2001/05/02 19:06:02  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.9  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.8  2001/03/02 23:04:04  mmiers
 * LOG: Cross platform cleanup.
 * LOG:
 * LOG: Revision 3.7  2001/03/02 22:44:15  mmiers
 * LOG: DLSYM needs to be in CORE.  CORE and ENGINE will be present
 * LOG: always.  The rest will be loaded on demand.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.3  2001/01/18 23:50:26  mmiers
 * LOG: Ditch the list allocator, use mempool instead.
 * LOG:
 * LOG: Revision 3.2  2000/09/01 20:56:31  mmiers
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:43  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.9  2000/06/16 22:34:45  rsonak
 * LOG:
 * LOG:
 * LOG: Fix PeekNextEvent with free lock.
 * LOG:
 * LOG: Revision 2.8  2000/05/25 23:26:40  mmiers
 * LOG:
 * LOG:
 * LOG: Today's SCTP update.
 * LOG:
 * LOG: Revision 2.7  2000/05/15 22:34:03  mmiers
 * LOG:
 * LOG:
 * LOG: Add ON_CONNECT/ON_DISCONNECT functions.  Really only used by sockets
 * LOG: and fifos.
 * LOG:
 * LOG: Revision 2.6  2000/03/02 16:24:16  ssharma
 * LOG:
 * LOG: Watch for type promotion in varargs (short becomes int).
 * LOG:
 * LOG: Revision 2.5  2000/02/15 20:34:48  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.4  2000/02/14 19:17:45  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.3  1999/12/22 02:09:04  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.2  1999/12/16 02:19:22  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
 * LOG: though.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 00:53:04  mmiers
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:13  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.14  1999/11/10 00:09:41  mmiers
 * LOG:
 * LOG:
 * LOG: Transport extensions
 * LOG:
 * LOG: Revision 1.13  1999/10/25 23:38:51  mmiers
 * LOG:
 * LOG:
 * LOG: Documentation code for the programming impaired.
 * LOG:
 * LOG: Revision 1.12  1999/10/25 18:28:14  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.11  1999/02/25 22:57:12  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.10  1998/09/28 16:20:08  mmiers
 * LOG: Misleading error message.
 * LOG:
 * LOG: Revision 1.9  1998/09/23 22:04:29  jrao
 * LOG: Updates from HPUX.
 * LOG:
 * LOG: Revision 1.8  1998/09/23 20:52:21  jrao
 * LOG: Screwed up the task transport.
 * LOG:
 * LOG: Revision 1.7  1998/09/22 18:51:21  mmiers
 * LOG: Finish off C-trace.  Turn debug off by default.
 * LOG:
 * LOG: Revision 1.6  1998/06/26 14:29:59  mmiers
 * LOG: Convert C++ transports to use C versions.
 * LOG:
 * LOG: Revision 1.5  1998/06/18 16:32:59  mmiers
 * LOG: Example of how to convert old tests to new API.
 * LOG:
 * LOG: Fix bugs in the "C" task queue transport.
 * LOG:
 * LOG: Revision 1.4  1998/06/18 03:45:05  mmiers
 * LOG: Get the task transport correct.  This one's important.
 * LOG:
 * LOG: Revision 1.3  1998/06/18 03:29:14  mmiers
 * LOG: Create the task queue transport type.
 * LOG:
 * LOG: Revision 1.2  1998/06/18 03:13:44  mmiers
 * LOG: Initial implementation.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_trace.h>
#include <its_hmi.h>
#include <its_timers.h>

#ident "$Id: its_task_trans.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method creates a task queue based transport.
 *
 *  Input Parameters:
 *      name - the name of this transport
 *      instance - the instance id of this transport
 *      mask - transport modifiers for the base class
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
 *      TQUEUETRAN_DeleteTransport()
 ****************************************************************************/
static int
Create(ITS_Object h, va_list args)
{
    TQUEUETRAN_Manager *ret = (TQUEUETRAN_Manager *)h;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;

    ITS_TRACE_DEBUG(("Create:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    if ((TQUEUETRAN_EMLIST(ret) = EMLIST_Create()) == NULL)
    {
        ITS_TRACE_ERROR(("Create: couldn't create EMLIST\n"));

        return (ITS_ENOTRANSPORT);
    }

    TRANSPORT_SetState((TRANSPORT_Control *)ret, ITS_TRUE);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method destroys a task queue transport.
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
 *      TQUEUETRAN_CreateTransport()
 ****************************************************************************/
static void
Destroy(ITS_Object h)
{
    TQUEUETRAN_Manager* ft = (TQUEUETRAN_Manager *)h;

    ITS_TRACE_DEBUG(("TQUEUETRAN_DeleteTransport:\n"));

    TRANSPORT_SetState((TRANSPORT_Control *)h, ITS_FALSE);

    EMLIST_Delete(TQUEUETRAN_EMLIST(ft));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function reads an event from the task queue.
 *
 *  Input Parameters:
 *      h - the handle of the transport to read from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      event - a ITS_EVENT to place the incoming event
 *          into
 *
 *  Return Value:
 *      If the event is successfully read, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
GetNextEvent(ITS_HANDLE h, ITS_EVENT* event)
{
    TQUEUETRAN_Manager* ft = (TQUEUETRAN_Manager *)h;
    int len, ret;
    void *data;
    
    ITS_TRACE_DEBUG(("TQUEUETRAN_GetNextEvent:\n"));

    ITS_EVENT_TERM(event);

repeat:
    //if ((ret = EMLIST_GetNextEventWithTimeOut(TQUEUETRAN_EMLIST(ft),&data, &len, HMI_GetTimeOutInterval())) != ITS_SUCCESS)
    if ((ret = EMLIST_GetNextEventWithTimeOut(TQUEUETRAN_EMLIST(ft),&data, &len,ITS_INFINITE_WAIT)) != ITS_SUCCESS)
    {
        if (ret == ITS_ETIMEOUT)
        {
            if (TRANSPORT_EXIT_NOW(ft))
            {
                return (ITS_ERCVFAIL);
            }

            TRANSPORT_LAST_UPDATE(ft) = TIMERS_Time();

            goto repeat;
        }

        ITS_TRACE_ERROR(("TQUEUETRAN_GetNextEvent: failed to retrieve "
                         "event from queue\n"));

        return (ret);
    }

    if (TRANSPORT_EXIT_NOW(ft))
    {
        ITS_TRACE_DEBUG(("TQUEUETRAN_GetNextEvent: EXIT NOW\n", ret));

        return (ITS_ERCVFAIL);
    }

    TRANSPORT_LAST_UPDATE(ft) = TIMERS_Time();
    TRANSPORT_NUM_RECV(ft)++;

    memcpy(event, data, len);

    if (EMLIST_Lock(TQUEUETRAN_EMLIST(ft)) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    ITS_Free(data);

    EMLIST_Unlock(TQUEUETRAN_EMLIST(ft));

    ITS_TRACE_DEBUG(("TQUEUETRAN_GetNextEvent: returning event\n", ret));

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function peeks at the task queue to see if data is
 *      present.  If data is present, it attempts to read the data into
 *      an event.
 *
 *  Input Parameters:
 *      h - the handle of the transport to read from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      event - a reference to an ITS_Event to place the incoming event
 *          into
 *
 *  Return Value:
 *      If the event is successfully read, ITS_SUCCESS is returned.
 *      If no data is available, ITS_ENOMSG is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PeekNextEvent(ITS_HANDLE h, ITS_EVENT* event)
{
    TQUEUETRAN_Manager* ft = (TQUEUETRAN_Manager *)h;
    int len, ret;
    void *data;
    
    ITS_TRACE_DEBUG(("TQUEUETRAN_PeekNextEvent:\n"));

    ITS_EVENT_TERM(event);

    if ((ret = EMLIST_PeekNextEvent(TQUEUETRAN_EMLIST(ft), &data, &len))
        != ITS_SUCCESS)
    {
        TRANSPORT_LAST_UPDATE(ft) = TIMERS_Time();

        return (ITS_ENOMSG);
    }

    TRANSPORT_LAST_UPDATE(ft) = TIMERS_Time();
    TRANSPORT_NUM_RECV(ft)++;

    memcpy(event, data, len);

    if (EMLIST_Lock(TQUEUETRAN_EMLIST(ft)) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    ITS_Free(data);

    EMLIST_Unlock(TQUEUETRAN_EMLIST(ft));

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function *writes* to the task queue transport.  For task queues,
 *      this implies putting the event into the queue.
 *
 *  Input Parameters:
 *      h - the handle of the transport to read from
 *      event - a reference to an ITS_Event to send to the message queue.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the data is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Task queues are unique in that sending to a task queue is normally
 *      performed from outside the task owning the queue.
 *
 *  See Also:
 ****************************************************************************/
static int
PutEvent(ITS_HANDLE h, ITS_EVENT* event)
{
    TQUEUETRAN_Manager* ft = (TQUEUETRAN_Manager *)h;
    int ret;
    
    ITS_TRACE_DEBUG(("TQUEUETRAN_PutEvent:\n"));

    ret = EMLIST_PutEvent(TQUEUETRAN_EMLIST(ft), (char *)event, sizeof(ITS_EVENT));

    if (ret == ITS_SUCCESS)
    {
        TRANSPORT_NUM_SENT(ft)++;
    }

    return (ret);
}

/*
 * the class record
 */
ITSDLLAPI TRANSPORT_ClassRec itsTQUEUETRAN_ClassRec =
{
    /* core */
    {
        (ITS_Class)&itsTRANSPORT_BaseClassRec,  /* superclass */
        sizeof(TQUEUETRAN_Manager),             /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        TQUEUETRAN_CLASS_NAME,                  /* class name */
        ITS_AddFeature,             /* class initialize */
        ITS_RemFeature,             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        Create,                                 /* constructor */
        Destroy,                                /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        NULL                                    /* extension */
    },
    /* transport */
    {
        GetNextEvent,                   /* get next */
        PeekNextEvent,                  /* peek next */
        PutEvent,                       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    }
};

ITSDLLAPI TRANSPORT_Class itsTQUEUETRAN_Class = &itsTQUEUETRAN_ClassRec;

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This method creates a task queue based transport.
 *
 *  Input Parameters:
 *      name - the name of this transport
 *      instance - the instance id of this transport
 *      mask - transport modifiers for the base class
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
 *      TQUEUETRAN_DeleteTransport()
 ****************************************************************************/
ITSDLLAPI TQUEUETRAN_Manager*
TQUEUETRAN_CreateTransport(const char *name,
                           ITS_USHORT instance,
                           ITS_UINT mask)
{
    ITS_TRACE_DEBUG(("TQUEUETRAN_CreateTransport:\n"));

    return (TQUEUETRAN_Manager *)TRANSPORT_Create(itsTQUEUETRAN_Class,
                                                  name, instance, mask);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This method destroys a task queue transport.
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
 *      TQUEUETRAN_CreateTransport()
 ****************************************************************************/
ITSDLLAPI void
TQUEUETRAN_DeleteTransport(TQUEUETRAN_Manager* ft)
{
    ITS_TRACE_DEBUG(("TQUEUETRAN_DeleteTransport:\n"));

    TRANSPORT_Delete((ITS_HANDLE)ft);
}
