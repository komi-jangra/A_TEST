/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:51:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/12/14 00:04:29  mmiers
 * LOG: Getting it working...
 * LOG:
 * LOG: Revision 5.2  2001/12/07 18:50:18  mmiers
 * LOG: CheckExpiry shouldn't exit anymore.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:05  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.7  2000/07/27 22:03:23  mmiers
 * LOG: Last of the core changes for PR3.  Removed last stubs, stack
 * LOG: binding is now dynamic.
 * LOG:
 * LOG: Revision 2.6  2000/03/18 21:03:50  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.5  2000/02/14 19:17:39  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.4  2000/02/01 23:09:14  mmiers
 * LOG:
 * LOG:
 * LOG: Auto start the license system.  Can do away with standalone *now*.
 * LOG:
 * LOG: Revision 2.3  2000/01/26 18:12:58  mmiers
 * LOG:
 * LOG:
 * LOG: Add feature processing.
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
 * LOG: Revision 2.0  1999/12/03 23:27:22  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.13  1999/11/10 00:09:39  mmiers
 * LOG:
 * LOG:
 * LOG: Transport extensions
 * LOG:
 * LOG: Revision 1.12  1999/10/27 15:33:09  mmiers
 * LOG:
 * LOG:
 * LOG: Add class name in here, too
 * LOG:
 * LOG: Revision 1.11  1999/10/25 18:28:12  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.10  1999/10/12 18:32:15  mmiers
 * LOG:
 * LOG:
 * LOG: Exit with error code.
 * LOG:
 * LOG: Revision 1.9  1999/10/07 14:19:01  mmiers
 * LOG:
 * LOG:
 * LOG: Change the core library so that standalone vendor builds don't need
 * LOG: to understand the different handles.
 * LOG:
 * LOG: Revision 1.8  1999/08/11 20:12:36  mmiers
 * LOG:
 * LOG:
 * LOG: Try for cleanness.
 * LOG:
 * LOG: Revision 1.7  1999/08/11 02:35:32  mmiers
 * LOG:
 * LOG:
 * LOG: Try to sanitize the environment variable/string getting.  Trace is
 * LOG: confusing this issue a bit.
 * LOG:
 * LOG: Revision 1.6  1999/07/29 00:08:40  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating some of Hubert's review comments.
 * LOG:
 * LOG: Revision 1.5  1999/06/29 15:09:31  mmiers
 * LOG:
 * LOG:
 * LOG: Call SS7_Terminate() where appropriate.
 * LOG:
 * LOG: Revision 1.4  1999/06/24 23:06:06  mmiers
 * LOG:
 * LOG:
 * LOG: Remove banner print.
 * LOG:
 * LOG: Revision 1.3  1999/06/23 23:36:36  labuser
 * LOG:
 * LOG:
 * LOG: Add more license checking in standalone mode.
 * LOG:
 * LOG: Revision 1.2  1999/06/23 23:24:31  labuser
 * LOG:
 * LOG:
 * LOG: NO SIDE EFFECTS IN ASSERT STATEMENTS!
 * LOG:
 * LOG: Revision 1.1  1999/03/12 21:05:01  mmiers
 * LOG:
 * LOG:
 * LOG: Add these files for standalone vendor lib support.
 * LOG:
 *
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include <its.h>
#include <its_license.h>
#include <its_app.h>
#include <its_object.h>
#include <its_ss7_trans.h>

#ident "$Id: its_standalone.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

static ITS_BOOLEAN  started = ITS_FALSE;
static ITS_BOOLEAN  terminated = ITS_FALSE;

/*
 * the class record
 */
ITSDLLAPI TRANSPORT_ClassRec itsSS7TRAN_ClassRec =
{
    /* core */
    {
        NULL,                       /* superclass */
        sizeof(SS7TRAN_Manager),    /* instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial ref count */
        SS7TRAN_CLASS_NAME,         /* class name */
        ITS_CLASS_NO_INIT,          /* no class init */
        ITS_CLASS_NO_DEST,          /* no class dest */
        ITS_CLASS_PART_NO_INIT,     /* class part init */
        ITS_CLASS_PART_NO_DEST,     /* class part destroy */
        ITS_INST_NO_CONST,          /* no instantiate */
        ITS_INST_NO_DEST,           /* no destroy */
        NULL                        /* extension */
    },
    /* transport */
    {
        ITS_GetNextEvent,           /* get next */
        ITS_PeekNextEvent,          /* peek next */
        ITS_PutEvent                /* put */
    }
};

ITSDLLAPI TRANSPORT_Class itsSS7TRAN_Class = &itsSS7TRAN_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function is implicitly called by ITS_Initialize() to initialize
 *      the various IntellISS7 subsystems.
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
 *      If everything initializes successfully, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      Note that this function should normally not be called by the user.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ITS_GlobalStart(ITS_UINT mask)
{
    if (started)
    {
        return (ITS_SUCCESS);
    }

    started = ITS_TRUE;

    /* init featurs */
    if (ITS_InitFeatures() != ITS_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function terminates the IntelliSS7 API.  The last caller of
 *      ITS_Terminate() will cause this function to be invoked.
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
 *      Note that this function should normally not be called by the user.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
ITS_GlobalStop()
{
    if (terminated)
    {
        return;
    }

    terminated = ITS_TRUE;

    ITS_DestroyFeatures();
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function terminates processing for a transport.  In single
 *      threaded mode, the transport is assumed to be an SS7 transport.
 *
 *  Input Parameters:
 *      handle - the transport handle to stop processing for
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
 *      ITS_Initialize()
 ****************************************************************************/
ITSDLLAPI void
ITS_Terminate(ITS_HANDLE handle)
{
    SS7TRAN_Manager* ss7 = (SS7TRAN_Manager *)handle;

    if (SS7TRAN_SUBORDINATE(ss7))
    {
        ITS_DestructObject(SS7TRAN_HANDLE(ss7));
    }

    free(ss7);

    /* try for global termination */
    ITS_GlobalStop();
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function initializes a transport for communication.  This
 *      function is the basic startup point for IntelliSS7 communication
 *
 *  Input Parameters:
 *      mask - an inclusive-or'ed mask of transport modifiers
 *      instance - the identity of this transport
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the transport is initialized correctly, an opaque type pointer is
 *          returned.
 *      Any error during transport initialization forces the return of NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      ITS_Terminate()
 ****************************************************************************/
ITSDLLAPI ITS_HANDLE
ITS_Initialize(ITS_UINT mask, ITS_USHORT instance)
{
    SS7TRAN_Manager *ret = NULL;

    /* start our subsystems. */
    if (ITS_GlobalStart(mask) != ITS_SUCCESS)
    {
        return (NULL);
    }

    if ((ret = (SS7TRAN_Manager *)calloc(1, sizeof(SS7TRAN_Manager))) ==
        NULL)
    {
        return (NULL);
    }

    SS7TRAN_SUBORDINATE(ret) = itsSS7STANDALONE_Class;

    SS7TRAN_HANDLE(ret) =
        ITS_ConstructObject((ITS_Class)itsSS7STANDALONE_Class, ret);
    if (SS7TRAN_HANDLE(ret) == NULL)
    {
        free(ret);

        return (NULL);
    }

    ITS_OBJ_CLASS(ret) = (ITS_Class)itsSS7TRAN_Class;
    TRANSPORT_MASK(ret) = mask;
    TRANSPORT_INSTANCE(ret) = instance;
    TRANSPORT_NAME(ret) = "Default SS7 Transport";

    return (ITS_HANDLE)ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is a blocking call that waits for the next event
 *      to appear on this transport for consumption.  There are better
 *      ways of doing this for C++, however, such as
 *      ITS_Transport::GetNextEvent().
 *
 *  Input Parameters:
 *      handle - the tranport handle to wait on
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      event - a pointer to the ITS_EVENT to populate with received data
 *
 *  Return Value:
 *      If an event was retrieved, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      For C++, the application write can use ITS_Transport::GetNextEvent().
 *
 *  See Also:
 *      ITS_PeekNextEvent()
 ****************************************************************************/
ITSDLLAPI int
ITS_GetNextEvent(ITS_HANDLE handle, ITS_EVENT *event)
{
    SS7TRAN_Manager* ss7 = (SS7TRAN_Manager *)handle;

    if (LICENSE_CheckExpiry() != ITS_SUCCESS)
    {
        return (ITS_ENOLICENSE);
    }

    if (SS7STACK_CLASS_GET_NEXT_EVENT(SS7TRAN_SUBORDINATE(ss7)))
    {
        return SS7STACK_CLASS_GET_NEXT_EVENT(SS7TRAN_SUBORDINATE(ss7))
                                                (SS7TRAN_HANDLE(ss7), event);
    }
    else
    {
        return (ITS_ENOTRANSPORT);
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is a non-blocking call that checks the transport for
 *      pending events.  If an event is pending, the event is retrieved.
 *      There are better ways of doing this for C++, however, such as
 *      ITS_Transport::PeekNextEvent().
 *
 *  Input Parameters:
 *      handle - the tranport handle to wait on
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      event - a pointer to the ITS_EVENT to populate with received data
 *
 *  Return Value:
 *      If an event was retrieved, ITS_SUCCESS is returned.
 *      If no event is pending, ITS_ENOMSG is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      For C++, the application write can use ITS_Transport::PeekNextEvent().
 *
 *  See Also:
 *      ITS_GetNextEvent()
 ****************************************************************************/
ITSDLLAPI int
ITS_PeekNextEvent(ITS_HANDLE handle, ITS_EVENT *event)
{
    SS7TRAN_Manager* ss7 = (SS7TRAN_Manager *)handle;

    if (LICENSE_CheckExpiry() != ITS_SUCCESS)
    {
        return (ITS_ENOLICENSE);
    }

    if (SS7STACK_CLASS_PEEK_NEXT_EVENT(SS7TRAN_SUBORDINATE(ss7)))
    {
        return SS7STACK_CLASS_PEEK_NEXT_EVENT(SS7TRAN_SUBORDINATE(ss7))
                                                (SS7TRAN_HANDLE(ss7), event);
    }
    else
    {
        return (ITS_ENOTRANSPORT);
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function allows the user to put an event on a transport.
 *      This does NOT necessarily mean that an event is transmitted;
 *      for transports that are local only, this has the effect of adding
 *      an event to their own event source.
 *       There are better ways of doing this for C++, however, such as
 *      ITS_Transport::PutEvent().
 *
 *  Input Parameters:
 *      handle - the tranport handle to wait on
 *      event - a pointer to the ITS_EVENT to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the event is sent successfully, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      For C++, the application write can use ITS_Transport::PutEvent()
 *      for Put'ting to the local transport.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ITS_PutEvent(ITS_HANDLE handle, ITS_EVENT *event)
{
    SS7TRAN_Manager* ss7 = (SS7TRAN_Manager *)handle;

    if (LICENSE_CheckExpiry() != ITS_SUCCESS)
    {
        return (ITS_ENOLICENSE);
    }

    if (SS7STACK_CLASS_PUT_EVENT(SS7TRAN_SUBORDINATE(ss7)))
    {
        return SS7STACK_CLASS_PUT_EVENT(SS7TRAN_SUBORDINATE(ss7))
                                                (SS7TRAN_HANDLE(ss7), event);
    }
    else
    {
        return (ITS_ENOTRANSPORT);
    }
}
