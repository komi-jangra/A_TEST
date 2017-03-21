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
 * LOG: Revision 1.2  2007/03/30 04:59:27  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:46  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:02  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2002/01/29 22:12:22  mmiers
 * LOG: Worker getting hung up if transport never initialized.
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
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.13  2001/04/10 19:29:16  mmiers
 * LOG: Debugging still.
 * LOG:
 * LOG: Revision 3.12  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.11  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.10  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.9  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.8  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.7  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.5  2001/01/12 17:13:11  mmiers
 * LOG: Tweak
 * LOG:
 * LOG: Revision 3.4  2001/01/10 00:24:06  mmiers
 * LOG: Linux build.
 * LOG:
 * LOG: Revision 3.3  2001/01/10 00:05:55  mmiers
 * LOG: Extra #endif
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:55  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:47  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/07/07 22:27:16  mmiers
 * LOG:
 * LOG:
 * LOG: Rework close logic for sockets.
 * LOG:
 * LOG: Revision 2.3  2000/05/26 21:34:20  mmiers
 * LOG:
 * LOG:
 * LOG: A few bug fixes, more SCTP work.
 * LOG:
 * LOG: Revision 2.2  2000/01/24 23:15:23  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating
 * LOG:
 * LOG: Revision 2.1  1999/12/16 02:19:23  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
 * LOG: though.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:22  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.9  1999/10/25 18:28:17  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.8  1999/10/12 22:59:58  mmiers
 * LOG:
 * LOG:
 * LOG: Rework termination handling of dynamic sockets.  The transport
 * LOG: control needs to go away when the thread does.
 * LOG:
 * LOG: Revision 1.7  1999/06/25 16:06:45  mmiers
 * LOG:
 * LOG:
 * LOG: Rework the berkeley sockets transport classes a little.  Required
 * LOG: modification to the Accept() method to create a transport correctly.
 * LOG:
 * LOG: Revision 1.6  1999/06/23 21:52:23  mmiers
 * LOG:
 * LOG:
 * LOG: Fix from C version of the worker for dynamic socket transports.
 * LOG:
 * LOG: Revision 1.5  1999/06/23 21:30:44  rsonak
 * LOG:
 * LOG:
 * LOG: Rework this slightly to allow for transport type changing to transport
 * LOG: flag.
 * LOG:
 * LOG: Revision 1.4  1999/06/15 16:15:17  rsonak
 * LOG:
 * LOG: DynamicServerTransport modified
 * LOG:
 * LOG: Revision 1.3  1999/06/14 20:55:24  rsonak
 * LOG:
 * LOG: Added Iterative server and Dynamic server transports
 * LOG:
 * LOG: Revision 1.2  1998/10/29 18:10:10  mmiers
 * LOG: Avoid C++ comments in C files.
 * LOG:
 * LOG: Revision 1.1  1998/10/29 00:30:26  mmiers
 * LOG: C worker (thread pools in C)
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_transports.h>
#include <its_worker.h>
#include <its_transport_factory.h>
#include <its_assertion.h>

#ident "$Id: its_worker.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

static WORKER_Control*  allWorkers[ITS_INVALID_SRC + 1];
static ITS_MUTEX        gate;

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
static int
CreateTransport(WORKER_Control *worker)
{
    WORKER_TRANSPORT(worker) = (TRANSPORT_Control *)
        FACTORY_CreateInstance((FACTORY_Class)itsTRANSPORT_FACTORY_Class,
                               WORKER_NAME(worker),
                               WORKER_INSTANCE(worker),
                               WORKER_MASK(worker));

    if (WORKER_TRANSPORT(worker) == NULL)
    {
        return (ITS_ENOTRANSPORT);
    }

    TRANSPORT_OWNER(WORKER_TRANSPORT(worker)) = (ITS_THREAD *)worker;

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
DeleteTransport(WORKER_Control *worker)
{
    FACTORY_DeleteInstance((FACTORY_Class)itsTRANSPORT_FACTORY_Class,
                           (ITS_Object)WORKER_TRANSPORT(worker));
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Create a worker
 *
 *  Input Parameters:
 *      obj - the object to create into
 *      args - the arg list
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to the created object or NULL
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
InitWorker(ITS_Object obj, va_list args)
{
    char *name;
    ITS_UINT mask;
    ITS_USHORT instance;
    int stackSize;
    WORKER_Control *ret = (WORKER_Control *)obj;

    stackSize = va_arg(args, int); /* throwaway */
    name = va_arg(args, char *);
    instance = va_arg(args, ITS_UINT);
    mask = va_arg(args, ITS_UINT);

    if (MUTEX_AcquireMutex(&gate) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if (allWorkers[instance] != NULL)
    {
        MUTEX_ReleaseMutex(&gate);

        return (ITS_EBADTRANSPORT);
    }

    WORKER_MASK(ret) = mask;
    WORKER_INSTANCE(ret) = instance;
    WORKER_NAME(ret) = strdup(name);

    /*
     * if the user did not specify delayed transport creation, try
     * to create the transport
     */
    if (!(mask & ITS_TRANSPORT_DELAY_CREATE))
    {
        if (CreateTransport(ret) != ITS_SUCCESS)
        {
            free(ret);

            MUTEX_ReleaseMutex(&gate);

            return (ITS_ENOMEM);
        }
    }

    allWorkers[instance] = ret;

    MUTEX_ReleaseMutex(&gate);

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Destroy a worker
 *
 *  Input Parameters:
 *      worker - the object to destroy
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
DeleteWorker(ITS_Object obj)
{
    WORKER_Control* worker = (WORKER_Control *)obj;

    if (MUTEX_AcquireMutex(&gate) != ITS_SUCCESS)
    {
        return;
    }

    allWorkers[WORKER_INSTANCE(worker)] = NULL;

    if (WORKER_NAME(worker))
    {
        free(WORKER_NAME(worker));
    }

    WORKER_DeleteTransport(worker);

    MUTEX_ReleaseMutex(&gate);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
static int
GetNextEvent(WORKER_Control* worker, ITS_EVENT* ev)
{
    ITS_Class cl;

    if (WORKER_TRANSPORT(worker) && ITS_OBJ_CLASS(WORKER_TRANSPORT(worker)))
    {
        cl = ITS_OBJ_CLASS(WORKER_TRANSPORT(worker));

        return TRANSPORT_CLASS_GET_NEXT_EVENT(cl)
                   ((ITS_HANDLE)WORKER_TRANSPORT(worker), ev);
    }

    return (ITS_EINVALIDARGS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
static int
PeekNextEvent(WORKER_Control* worker, ITS_EVENT* ev)
{
    ITS_Class cl;

    if (WORKER_TRANSPORT(worker) && ITS_OBJ_CLASS(WORKER_TRANSPORT(worker)))
    {
        cl = ITS_OBJ_CLASS(WORKER_TRANSPORT(worker));

        return TRANSPORT_CLASS_PEEK_NEXT_EVENT(cl)
                   ((ITS_HANDLE)WORKER_TRANSPORT(worker), ev);
    }

    return (ITS_EINVALIDARGS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
static int
PutEvent(WORKER_Control* worker, ITS_EVENT* ev)
{
    ITS_Class cl;

    if (WORKER_TRANSPORT(worker) && ITS_OBJ_CLASS(WORKER_TRANSPORT(worker)))
    {
        cl = ITS_OBJ_CLASS(WORKER_TRANSPORT(worker));

        return TRANSPORT_CLASS_PUT_EVENT(cl)
                   ((ITS_HANDLE)WORKER_TRANSPORT(worker), ev);
    }

    return (ITS_EINVALIDARGS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the class.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInit(ITS_Class objClass)
{
    if (MUTEX_CreateMutex(&gate, 0) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the class.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
    MUTEX_DeleteMutex(&gate);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the class record.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassPartInitialize(ITS_Class classRec)
{
    if (WORKER_CLASS_CREATE_TRANSPORT(classRec) == NULL)
    {
        WORKER_CLASS_CREATE_TRANSPORT(classRec) =
            WORKER_CLASS_CREATE_TRANSPORT(ITS_CLASS_SUPERCLASS(classRec));
    }
    if (WORKER_CLASS_DELETE_TRANSPORT(classRec) == NULL)
    {
        WORKER_CLASS_DELETE_TRANSPORT(classRec) =
            WORKER_CLASS_DELETE_TRANSPORT(ITS_CLASS_SUPERCLASS(classRec));
    }
    if (WORKER_CLASS_GET_NEXT_EVENT(classRec) == NULL)
    {
        WORKER_CLASS_GET_NEXT_EVENT(classRec) =
            WORKER_CLASS_GET_NEXT_EVENT(ITS_CLASS_SUPERCLASS(classRec));
    }
    if (WORKER_CLASS_PEEK_NEXT_EVENT(classRec) == NULL)
    {
        WORKER_CLASS_PEEK_NEXT_EVENT(classRec) =
            WORKER_CLASS_PEEK_NEXT_EVENT(ITS_CLASS_SUPERCLASS(classRec));
    }
    if (WORKER_CLASS_PUT_EVENT(classRec) == NULL)
    {
        WORKER_CLASS_PUT_EVENT(classRec) =
            WORKER_CLASS_PUT_EVENT(ITS_CLASS_SUPERCLASS(classRec));
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the class record.
 *
 *  Input Parameters:
 *      classRec - the class to destroy
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
ClassPartDestroy(ITS_Class classRec)
{
}

/*
 * the class record
 */
ITSDLLAPI WORKER_ClassRec itsWORKER_ClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsTPOOLTHREAD_ClassRec,/* superclass is TPOOLTHREAD */
        sizeof(WORKER_Control),         /* sizeof instance */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial refCount */
        WORKER_CLASS_NAME,              /* class name */
        ClassInit,                      /* class initialize */
        ClassDestroy,                   /* class destroy */
        ClassPartInitialize,            /* class initialize part */
        ClassPartDestroy,               /* class destroy part */
        InitWorker,                     /* instantiate */
        DeleteWorker,                   /* destroy */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        ITS_INST_HASH_INHERIT,          /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* worker part */
    {
        CreateTransport,                /* transport create */
        DeleteTransport,                /* transport delete */
        GetNextEvent,                   /* get next */
        PeekNextEvent,                  /* peek next */
        PutEvent                        /* put */
    }
};

ITSDLLAPI ITS_Class itsWORKER_Class = (ITS_Class)&itsWORKER_ClassRec;

#undef WORKER_InitWorker
#undef WORKER_DeleteWorker
#undef WORKER_CreateTransport
#undef WORKER_DeleteTransport
#undef WORKER_GetNextEvent
#undef WORKER_PeekNextEvent
#undef WORKER_PutEvent

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI WORKER_Control*
WORKER_InitWorker(int stackSize, const char *name,
                  ITS_USHORT instance, ITS_UINT mask)
{
    return (WORKER_Control *)ITS_ConstructObject(itsWORKER_Class, stackSize,
                                                 name, instance, mask);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
WORKER_DeleteWorker(WORKER_Control* worker)
{
    ITS_DestructObject((ITS_Object)worker);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI int
WORKER_CreateTransport(WORKER_Control *worker)
{
    return WORKER_CLASS_CREATE_TRANSPORT(ITS_OBJ_CLASS(worker))(worker);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
WORKER_DeleteTransport(WORKER_Control *worker)
{
    WORKER_CLASS_DELETE_TRANSPORT(ITS_OBJ_CLASS(worker))(worker);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI int
WORKER_GetNextEvent(WORKER_Control* worker, ITS_EVENT* ev)
{
    return WORKER_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(worker))(worker, ev);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI int
WORKER_PeekNextEvent(WORKER_Control* worker, ITS_EVENT* ev)
{
    return WORKER_CLASS_PEEK_NEXT_EVENT(ITS_OBJ_CLASS(worker))(worker, ev);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI int
WORKER_PutEvent(WORKER_Control* worker, ITS_EVENT* ev)
{
    return WORKER_CLASS_PUT_EVENT(ITS_OBJ_CLASS(worker))(worker, ev);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI WORKER_Control*
WORKER_FindWorker(ITS_USHORT instance)
{
    return (allWorkers[instance]);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI ITS_BOOLEAN
WORKER_GetExit(WORKER_Control *work)
{
    if (WORKER_TRANSPORT(work) && TRANSPORT_GetExit(WORKER_TRANSPORT(work)))
    {
        return (ITS_TRUE);
    }

    if (TPOOL_THREAD_EXIT(work))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
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
WORKER_SetExit(WORKER_Control *work, ITS_BOOLEAN which)
{
    TRANSPORT_Control *base;

    if (WORKER_TRANSPORT(work))
    {
        TRANSPORT_SetExit(WORKER_TRANSPORT(work), which);
    }
    else if ((base = TRANSPORT_FindTransport(WORKER_INSTANCE(work))))
    {
        TRANSPORT_SetExit(base, which);

        TRANSPORT_UnfindTransport(base);
    }

    TPOOL_THREAD_EXIT(work) = which;
}
