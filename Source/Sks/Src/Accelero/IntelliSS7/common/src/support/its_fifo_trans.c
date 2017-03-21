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
 * LOG: Revision 1.2  2007/03/30 04:58:56  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:38  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:58  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/11/15 18:07:36  mmiers
 * LOG: Add exit proc for SCTP transports.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/07/09 19:59:15  mmiers
 * LOG: Finish off shared timers.
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
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/05 23:54:35  mmiers
 * LOG: Start adding in assertions
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:39  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:28  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.7  2000/05/15 22:34:00  mmiers
 * LOG:
 * LOG:
 * LOG: Add ON_CONNECT/ON_DISCONNECT functions.  Really only used by sockets
 * LOG: and fifos.
 * LOG:
 * LOG: Revision 2.6  2000/03/02 16:24:14  ssharma
 * LOG:
 * LOG: Watch for type promotion in varargs (short becomes int).
 * LOG:
 * LOG: Revision 2.5  2000/02/15 20:34:46  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.4  2000/02/14 19:17:41  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.3  1999/12/22 02:09:00  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 2.2  1999/12/16 02:19:21  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
 * LOG: though.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 00:53:02  mmiers
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:38  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.19  1999/11/10 00:09:40  mmiers
 * LOG:
 * LOG:
 * LOG: Transport extensions
 * LOG:
 * LOG: Revision 1.18  1999/10/25 23:38:49  mmiers
 * LOG:
 * LOG:
 * LOG: Documentation code for the programming impaired.
 * LOG:
 * LOG: Revision 1.17  1999/10/25 18:28:12  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.16  1999/03/12 00:06:11  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.15  1999/02/25 22:57:10  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.14  1998/11/12 01:41:53  mmiers
 * LOG: Trying to straighten out SSP/SSA.
 * LOG:
 * LOG: Revision 1.13  1998/11/12 00:09:13  mmiers
 * LOG: Debugging SSP/SSA.  Note that this has a major change for FIFOs.
 * LOG: Revert to the previous version of fifo-win and fifo_trans if this
 * LOG: doesn't work everywhere.
 * LOG:
 * LOG: Revision 1.12  1998/11/05 16:52:14  mmiers
 * LOG: Add in transport pause/resume.
 * LOG: Add reconnect to sockets.
 * LOG:
 * LOG: Revision 1.11  1998/10/01 00:01:45  mmiers
 * LOG: Port to digital unix
 * LOG:
 * LOG: Revision 1.10  1998/09/23 22:04:28  jrao
 * LOG: Updates from HPUX.
 * LOG:
 * LOG: Revision 1.9  1998/09/21 22:52:32  mmiers
 * LOG: Start adding C-trace to infrastructure.
 * LOG:
 * LOG: Revision 1.8  1998/07/21 00:12:12  ahanda
 * LOG: Retry after reopening FIFO's
 * LOG:
 * LOG: Revision 1.7  1998/07/20 16:51:16  ahanda
 * LOG: ReCreate FIFO on getting EBADFIFO during ReadFIFO in GetNextEvent
 * LOG:
 * LOG: Revision 1.6  1998/07/16 19:16:49  mmiers
 * LOG: Add a peek for fifo objects.
 * LOG:
 * LOG: Revision 1.5  1998/06/26 14:29:57  mmiers
 * LOG: Convert C++ transports to use C versions.
 * LOG:
 * LOG: Revision 1.4  1998/06/18 03:10:08  mmiers
 * LOG: Build on Solaris.  Right now, the NT build is not OK.
 * LOG:
 * LOG: Revision 1.3  1998/06/18 02:37:15  mmiers
 * LOG: More work on the C side for back compat.
 * LOG:
 * LOG: Revision 1.2  1998/06/18 01:02:41  mmiers
 * LOG: More "C" style transports.
 * LOG:
 * LOG: Revision 1.1  1998/06/18 00:24:58  mmiers
 * LOG: Documentation update, C versions of some transports, C version of
 * LOG: resource file manager.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_route.h>
#include <its_fifo_trans.h>
#include <its_iniparse.h>
#include <its_trace.h>
#include <its_assertion.h>

#ident "$Id: its_fifo_trans.c,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method instantiates a FIFO transport
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
Create(ITS_Object h, va_list args)
{
    char cpath[ITS_PATH_MAX], spath[ITS_PATH_MAX], buf[ITS_PATH_MAX];
    FIFOTRAN_Manager *ret = (FIFOTRAN_Manager *)h;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;

    ITS_TRACE_DEBUG(("FIFOTRAN_CreateTransport:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    ITS_C_ASSERT(TRANSPORT_RES(ret) != NULL);

    /* get the cpath name */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              FIFO_CLIENT_PATH_STRING, buf, ITS_PATH_MAX)
        != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("FIFOTRAN_CreateTransport: INI is missing "
                         "FIFO_CLIENT_PATH\n"));

        return (ITS_ENOTRANSPORT);
    }
    else
    {
        strcpy(cpath, buf);
    }

    /* get the spath name */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(ret), TRANSPORT_NAME(ret),
                              FIFO_SERVER_PATH_STRING, buf, ITS_PATH_MAX)
        != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("FIFOTRAN_CreateTransport: INI is mssing "
                         "FIFO_SERVER_PATH\n"));

        return (ITS_ENOTRANSPORT);
    }
    else
    {
        strcpy(spath, buf);
    }

    ITS_TRACE_DEBUG(("FIFOTRAN_CreateTransport: creating fifos source %s "
                     "sink %s\n", spath, cpath));

    /* create the write fifo */
    if (FIFO_CreateFifo(&FIFOTRAN_SINK(ret), cpath,
                        ITS_FIFO_WRITER) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("FIFOTRAN_CreateTransport: couldn't create sink "
                         "FIFO\n"));

        return (ITS_ENOTRANSPORT);
    }
    FIFOTRAN_SINK_NAME(ret) = strdup(cpath);

    /* create the read fifo */
    if (FIFO_CreateFifo(&FIFOTRAN_SOURCE(ret), spath,
                        ITS_FIFO_READER) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("FIFOTRAN_CreateTransport: couldn't create source "
                         "FIFO\n"));

        FIFO_DeleteFifo(&FIFOTRAN_SOURCE(ret), FIFOTRAN_SINK_NAME(ret));

        free(FIFOTRAN_SINK_NAME(ret));
    }
    FIFOTRAN_SOURCE_NAME(ret) = strdup(spath);

    if (TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ret)))
    {
        TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ret))(ret);
    }

    TRANSPORT_SetState((TRANSPORT_Control *)ret, ITS_TRUE);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method destroys a FIFO transport.  Note that the release of the
 *      individual components of the transport may be delayed until both
 *      ends of the FIFO transport have released their resources.
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
 *      FIFOTRAN_CreateTransport()
 ****************************************************************************/
static void
Destroy(ITS_Object h)
{
    FIFOTRAN_Manager *ft = (FIFOTRAN_Manager *)h;

    if (TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft)))
    {
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft))(ft);
    }

    TRANSPORT_SetState((TRANSPORT_Control *)h, ITS_FALSE);

    FIFO_DeleteFifo(&FIFOTRAN_SOURCE(ft), FIFOTRAN_SOURCE_NAME(ft));
    FIFO_DeleteFifo(&FIFOTRAN_SINK(ft), FIFOTRAN_SINK_NAME(ft));

    free(FIFOTRAN_SOURCE_NAME(ft));
    free(FIFOTRAN_SINK_NAME(ft));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads from the server end of the fifo to retrieve an
 *      event.
 *
 *  Input Parameters:
 *      None.
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
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
GetNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    FIFOTRAN_Manager *ft = (FIFOTRAN_Manager *)h;
    int retVal;
    ITS_BOOLEAN wasPaused = ITS_FALSE;

    ITS_TRACE_DEBUG(("FIFOTRAN_GetNextEvent:\n"));

    ITS_C_REQUIRE(h != NULL);
    ITS_C_REQUIRE(ev != NULL);

    /* no data present */
    ev->data = NULL;

retry:
    /* avoid leaks on retry */
    if (ev->data)
    {
        ITS_Free(ev->data);

        ev->data = NULL;
    }

    /*
     * Read from the FIFO. If the connection has been broken, Re-open
     */
    retVal = FIFO_ReadFifo(&FIFOTRAN_SOURCE(ft),
                           (char *)ev, sizeof(ITS_EVENT));

    if (retVal == ITS_SUCCESS)
    {
        ev->data = (ITS_OCTET *)ITS_Malloc(ev->len);

        if (ev->data == NULL)
        {
            return (ITS_ENOMEM);
        }

        retVal = FIFO_ReadFifo(&FIFOTRAN_SOURCE(ft),
                               (char *)ev->data, ev->len);
    }

    if (retVal == ITS_EBADFIFO)
    {
        ITS_TRACE_DEBUG(("FIFOTRAN_GetNextEvent: read failed.  Reopen "
                         "fifos\n"));

        wasPaused = ITS_TRUE;
        TRANSPORT_SetState(TRANSPORT(ft), ITS_FALSE);

        if (TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft)))
        {
            TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft))(ft);
        }

        FIFO_DeleteFifo(&FIFOTRAN_SOURCE(ft), FIFOTRAN_SOURCE_NAME(ft));
        FIFO_DeleteFifo(&FIFOTRAN_SINK(ft), FIFOTRAN_SINK_NAME(ft));
           
        if ((retVal = FIFO_CreateFifo(&FIFOTRAN_SINK(ft),
                                      FIFOTRAN_SINK_NAME(ft),
                                      ITS_FIFO_WRITER)) == ITS_SUCCESS)
        {
            if ((retVal = FIFO_CreateFifo(&FIFOTRAN_SOURCE(ft),
                                          FIFOTRAN_SOURCE_NAME(ft),
                                          ITS_FIFO_READER)) == ITS_SUCCESS)
            {
                ITS_TRACE_DEBUG(("FIFOTRAN_GetNextEvent: FIFOs Reopened\n"));

                if (wasPaused)
                {
                    TRANSPORT_SetState(TRANSPORT(ft), ITS_TRUE);
                    TRANSPORT_SetCongestion(TRANSPORT(ft), 0);

                    wasPaused = ITS_FALSE;
                }

                if (TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ft)))
                {
                    TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ft))(ft);
                }

                goto retry;
            }
        }
    }

    return (retVal);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method peeks at the server end of the fifo to see if data is
 *      present.  If data is present, it attempts to read the data into
 *      an event.
 *
 *  Input Parameters:
 *      None.
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
PeekNextEvent(ITS_HANDLE h, ITS_EVENT* ev)
{
    FIFOTRAN_Manager *ft = (FIFOTRAN_Manager *)h;
    int retVal;
    ITS_BOOLEAN wasPaused = ITS_FALSE;

    ITS_TRACE_DEBUG(("FIFOTRAN_PeekNextEvent:\n"));

    ITS_C_REQUIRE(h != NULL);
    ITS_C_REQUIRE(ev != NULL);

    /* mark no data */
    ev->data = NULL;

retry:
    /* avoid leaks on retry */
    if (ev->data)
    {
        ITS_Free(ev->data);

        ev->data = NULL;
    }

    /*
     * Read from the FIFO. If the connection has been broken, Re-open
     */
    retVal = FIFO_PeekFifo(&FIFOTRAN_SOURCE(ft),
                           (char *)ev, sizeof(ITS_EVENT));

    if (retVal == ITS_SUCCESS)
    {
        ev->data = (ITS_OCTET *)ITS_Malloc(ev->len);

        if (ev->data == NULL)
        {
            return (ITS_ENOMEM);
        }

        retVal = FIFO_ReadFifo(&FIFOTRAN_SOURCE(ft),
                               (char *)ev->data, ev->len);
    }

    if (retVal == ITS_EBADFIFO)
    {
        ITS_TRACE_DEBUG(("FIFOTRAN_GetNextEvent: read failed.  Reopen "
                         "fifos\n"));

        wasPaused = ITS_TRUE;
        TRANSPORT_SetState(TRANSPORT(ft), ITS_FALSE);

        if (TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft)))
        {
            TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft))(ft);
        }

        FIFO_DeleteFifo(&FIFOTRAN_SOURCE(ft), FIFOTRAN_SOURCE_NAME(ft));
        FIFO_DeleteFifo(&FIFOTRAN_SINK(ft), FIFOTRAN_SINK_NAME(ft));
           
        if ((retVal = FIFO_CreateFifo(&FIFOTRAN_SINK(ft),
                                      FIFOTRAN_SINK_NAME(ft),
                                      ITS_FIFO_WRITER)) == ITS_SUCCESS)
        {
            if ((retVal = FIFO_CreateFifo(&FIFOTRAN_SOURCE(ft),
                                          FIFOTRAN_SOURCE_NAME(ft),
                                          ITS_FIFO_READER)) == ITS_SUCCESS)
            {
                ITS_TRACE_DEBUG(("FIFOTRAN_PeekNextEvent: FIFOs Reopened\n"));

                if (wasPaused)
                {
                    TRANSPORT_SetState(TRANSPORT(ft), ITS_TRUE);
                    TRANSPORT_SetCongestion(TRANSPORT(ft), 0);

                    wasPaused = ITS_FALSE;
                }

                if (TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ft)))
                {
                    TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ft))(ft);
                }

                goto retry;
            }
        }
    }

    return (retVal);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method *writes* to the fifo transport.  For fifos, this implies
 *      writing the event to the client side of the fifo transport (i.e.,
 *      the fifo the *other* end will read from).
 *
 *  Input Parameters:
 *      event - a reference to an ITS_Event to send to the remote end
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
 *
 *  See Also:
 ****************************************************************************/
static int
PutEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    FIFOTRAN_Manager *ft = (FIFOTRAN_Manager *)h;

    ITS_TRACE_DEBUG(("FIFOTRAN_PutEvent:\n"));

    ITS_C_REQUIRE(h != NULL);
    ITS_C_REQUIRE(ev != NULL);

    ret = FIFO_WriteFifo(&FIFOTRAN_SINK(ft), (char *)ev, sizeof(ITS_EVENT));

    if (ret == ITS_SUCCESS)
    {
        ret = FIFO_WriteFifo(&FIFOTRAN_SINK(ft), (char *)ev->data, ev->len);
    }

    return (ret);
}

/*
 * the class record.
 */
ITSDLLAPI TRANSPORT_ClassRec itsFIFOTRAN_ClassRec =
{
    /* core */
    {
        (ITS_Class)&itsTRANSPORT_BaseClassRec,  /* base class */
        sizeof(FIFOTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        FIFOTRAN_CLASS_NAME,                    /* class name */
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
        NULL                                    /* no extension */
    },
    /* transport */
    {
        GetNextEvent,                   /* get */
        PeekNextEvent,                  /* peek */
        PutEvent,                       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
    }
};
ITSDLLAPI TRANSPORT_Class itsFIFOTRAN_Class = &itsFIFOTRAN_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method creates a FIFO based transport.  Two fifos are
 *      created (one for reading, one for writing); this routine should
 *      succeed even if the other endpoint process is not present when
 *      the fifos are created.
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
 *      The resource file is consulted for path information for the
 *      fifo.
 *
 *  See Also:
 *      FIFOTRAN_DeleteTransport()
 ****************************************************************************/
ITSDLLAPI FIFOTRAN_Manager*
FIFOTRAN_CreateTransport(const char *name,
                         ITS_USHORT instance,
                         ITS_UINT mask)
{
    ITS_TRACE_DEBUG(("FIFOTRAN_CreateTransport:\n"));

    return (FIFOTRAN_Manager *)TRANSPORT_Create(itsFIFOTRAN_Class, name,
                                                instance, mask);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method destroys a FIFO transport.  Note that the release of the
 *      individual components of the transport may be delayed until both
 *      ends of the FIFO transport have released their resources.
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
 *      FIFOTRAN_CreateTransport()
 ****************************************************************************/
ITSDLLAPI void
FIFOTRAN_DeleteTransport(FIFOTRAN_Manager *ft)
{
    ITS_TRACE_DEBUG(("FIFOTRAN_DeleteTransport: delete source %s sink %s\n",
                     FIFOTRAN_SOURCE_NAME(ft), FIFOTRAN_SINK_NAME(ft)));

    TRANSPORT_Delete((ITS_HANDLE)ft);
}

