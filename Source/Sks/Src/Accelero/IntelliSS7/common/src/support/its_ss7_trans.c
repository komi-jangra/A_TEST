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
 * LOG: Revision 1.2  2007/03/30 04:59:17  cvsadmin
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
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2001/12/13 23:01:05  mmiers
 * LOG: Common vendor framework start.
 * LOG:
 * LOG: Revision 5.3  2001/11/16 23:37:03  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.2  2001/11/15 18:07:36  mmiers
 * LOG: Add exit proc for SCTP transports.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
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
 * LOG: Revision 3.6  2001/04/04 01:30:07  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.5  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:41  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.7  2000/07/27 22:03:23  mmiers
 * LOG: Last of the core changes for PR3.  Removed last stubs, stack
 * LOG: binding is now dynamic.
 * LOG:
 * LOG: Revision 2.6  2000/05/15 22:34:02  mmiers
 * LOG:
 * LOG:
 * LOG: Add ON_CONNECT/ON_DISCONNECT functions.  Really only used by sockets
 * LOG: and fifos.
 * LOG:
 * LOG: Revision 2.5  2000/03/02 16:24:16  ssharma
 * LOG:
 * LOG: Watch for type promotion in varargs (short becomes int).
 * LOG:
 * LOG: Revision 2.4  2000/02/15 20:34:48  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.3  2000/02/14 19:17:44  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.2  1999/12/22 02:09:03  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 00:53:03  mmiers
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:11  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.10  1999/11/10 00:09:41  mmiers
 * LOG:
 * LOG:
 * LOG: Transport extensions
 * LOG:
 * LOG: Revision 1.9  1999/10/25 23:38:51  mmiers
 * LOG:
 * LOG:
 * LOG: Documentation code for the programming impaired.
 * LOG:
 * LOG: Revision 1.8  1999/10/25 18:28:14  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.7  1999/08/22 21:23:36  labuser
 * LOG:
 * LOG:
 * LOG: Move the transport registration so that the database can be used
 * LOG: by SS7_Initialize
 * LOG:
 * LOG: Revision 1.6  1999/02/25 22:57:12  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.5  1998/11/20 23:07:37  mmiers
 * LOG: Fix some integration bugs.
 * LOG:
 * LOG: Revision 1.4  1998/09/22 18:51:20  mmiers
 * LOG: Finish off C-trace.  Turn debug off by default.
 * LOG:
 * LOG: Revision 1.3  1998/06/26 14:29:59  mmiers
 * LOG: Convert C++ transports to use C versions.
 * LOG:
 * LOG: Revision 1.2  1998/06/18 17:16:30  mmiers
 * LOG: Finish up the C transports and the SS7 transports.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_route.h>
#include <its_ss7_trans.h>
#include <its_trace.h>
#include <its_timers.h>

#ident "$Id: its_ss7_trans.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method creates a SS7 transport based transport.
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
 *      SS7TRAN_DeleteTransport()
 ****************************************************************************/
static int
Create(ITS_Object h, va_list args)
{
    SS7TRAN_Manager *ret = (SS7TRAN_Manager *)h;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;
    char buf[ITS_PATH_MAX];
    ITS_Class stackClass;

    ITS_TRACE_DEBUG(("SS7TRAN_CreateTransport:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              SS7_STACK_BINDING_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Create: Couldn't determine stack binding.\n"));

        return (ITS_ENOTRANSPORT);
    }

    if ((stackClass = ITS_FindFeature(buf)) == NULL)
    {
        ITS_TRACE_ERROR(("Create: Couldn't find stack class rec: %s.\n",
                         buf));

        return (ITS_ENOTRANSPORT);
    }

    SS7TRAN_HANDLE(ret) = ITS_ConstructObject(stackClass, ret);
    if (SS7TRAN_HANDLE(ret) == NULL)
    {
        ITS_TRACE_ERROR(("Create: SS7_Initialize failed\n"));

        return (ITS_ENOTRANSPORT);
    }
    
    SS7TRAN_SUBORDINATE(ret) = (SS7STACK_Class)stackClass;

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This method destroys a SS7 transport transport.
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
 *      SS7TRAN_CreateTransport()
 ****************************************************************************/
static void
Destroy(ITS_Object h)
{
    SS7TRAN_Manager* ft = (SS7TRAN_Manager *)h;

    ITS_TRACE_DEBUG(("Destroy:\n"));

    if (SS7TRAN_SUBORDINATE(ft))
    {
        ITS_DestructObject(SS7TRAN_HANDLE(ft));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function reads an event from the SS7 transport.
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
    SS7TRAN_Manager* ft = (SS7TRAN_Manager *)h;
    int ret;
    
    ITS_TRACE_DEBUG(("SS7TRAN_GetNextEvent:\n"));

    if (SS7TRAN_SUBORDINATE(ft) &&
        SS7STACK_CLASS_GET_NEXT_EVENT(SS7TRAN_SUBORDINATE(ft)))
    {
retry:
        ret = SS7STACK_CLASS_GET_NEXT_EVENT(SS7TRAN_SUBORDINATE(ft))
                                            (SS7TRAN_HANDLE(ft), event);

        if (TRANSPORT_EXIT_NOW(ft))
        {
            return (ITS_ERCVFAIL);
        }

        if (ret == ITS_ETIMEOUT)
        {
            TRANSPORT_LAST_UPDATE(h) = TIMERS_Time();

            goto retry;
        }

        if (ret == ITS_SUCCESS)
        {
            TRANSPORT_NUM_RECV(h)++;
            TRANSPORT_LAST_UPDATE(h) = TIMERS_Time();
        }

        return (ret);
    }
    else
    {
        return (ITS_ENOTRANSPORT);
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function peeks at the SS7 transport to see if data is
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
    SS7TRAN_Manager* ft = (SS7TRAN_Manager *)h;
    int ret;
    
    ITS_TRACE_DEBUG(("SS7TRAN_PeekNextEvent:\n"));

    if (SS7TRAN_SUBORDINATE(ft) &&
        SS7STACK_CLASS_PEEK_NEXT_EVENT(SS7TRAN_SUBORDINATE(ft)))
    {
        ret = SS7STACK_CLASS_PEEK_NEXT_EVENT(SS7TRAN_SUBORDINATE(ft))
                                             (SS7TRAN_HANDLE(ft), event);

        if (ret == ITS_SUCCESS)
        {
            TRANSPORT_NUM_RECV(h)++;
            TRANSPORT_LAST_UPDATE(h) = TIMERS_Time();
        }

        return (ret);
    }
    else
    {
        return (ITS_ENOTRANSPORT);
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function *writes* to the SS7 transport.
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
 *      SS7 transports are unique in that sending to a SS7 transport is normally
 *      performed from outside the task owning the queue.
 *
 *  See Also:
 ****************************************************************************/
static int
PutEvent(ITS_HANDLE h, ITS_EVENT* event)
{
    SS7TRAN_Manager* ft = (SS7TRAN_Manager *)h;
    int ret;
    
    ITS_TRACE_DEBUG(("SS7TRAN_PutEvent:\n"));

    if (SS7TRAN_SUBORDINATE(ft) &&
        SS7STACK_CLASS_PUT_EVENT(SS7TRAN_SUBORDINATE(ft)))
    {
        ret = SS7STACK_CLASS_PUT_EVENT(SS7TRAN_SUBORDINATE(ft))
                                           (SS7TRAN_HANDLE(ft), event);

        if (ret == ITS_SUCCESS)
        {
            TRANSPORT_NUM_SENT(h)++;
        }

        return (ret);
    }
    else
    {
        return (ITS_ENOTRANSPORT);
    }
}

/*
 * the class record
 */
ITSDLLAPI TRANSPORT_ClassRec itsSS7TRAN_ClassRec =
{
    /* core */
    {
        (ITS_Class)&itsTRANSPORT_BaseClassRec,  /* superclass */
        sizeof(SS7TRAN_Manager),                /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SS7TRAN_CLASS_NAME,                     /* class name */
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

ITSDLLAPI TRANSPORT_Class itsSS7TRAN_Class = &itsSS7TRAN_ClassRec;

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This method creates a SS7 transport based transport.
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
 *      SS7TRAN_DeleteTransport()
 ****************************************************************************/
ITSDLLAPI SS7TRAN_Manager*
SS7TRAN_CreateTransport(const char *name,
                        ITS_USHORT instance,
                        ITS_UINT mask)
{
    ITS_TRACE_DEBUG(("SS7TRAN_CreateTransport:\n"));

    return (SS7TRAN_Manager *)TRANSPORT_Create(itsSS7TRAN_Class,
                                               name, instance, mask);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This method destroys a SS7 transport transport.
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
 *      SS7TRAN_CreateTransport()
 ****************************************************************************/
ITSDLLAPI void
SS7TRAN_DeleteTransport(SS7TRAN_Manager* ft)
{
    ITS_TRACE_DEBUG(("SS7TRAN_DeleteTransport:\n"));

    TRANSPORT_Delete((ITS_HANDLE)ft);
}
