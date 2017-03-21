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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:15  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/16 03:30:36  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.42.1  2004/10/25 20:39:59  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/07/11 15:17:19  dalonso
 * LOG: Use the right mask bits when verifying
 * LOG:
 * LOG: Revision 6.2  2002/07/05 19:58:21  mmiers
 * LOG: Add PRC IP transports
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:22  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/12/13 17:52:19  mmiers
 * LOG: Access violation avoidance.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/06/20 19:18:17  mmiers
 * LOG: Finish up HMI
 * LOG:
 * LOG: Revision 4.2  2001/06/16 00:03:42  mmiers
 * LOG: Various fixes from PR4.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.9  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.8  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.7  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.4  2001/01/17 20:34:54  mmiers
 * LOG: Add mask verification function.
 * LOG:
 * LOG: Revision 3.3  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:38  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:01  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.12  2000/05/26 22:24:09  mmiers
 * LOG:
 * LOG:
 * LOG: Update for changed #define
 * LOG:
 * LOG: Revision 2.11  2000/02/15 20:34:43  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.10  2000/02/09 18:51:39  mmiers
 * LOG:
 * LOG:
 * LOG: Debug of EndPoint sockets done.  On to RUDP debug.
 * LOG:
 * LOG: Revision 2.9  2000/02/02 15:52:59  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.8  2000/02/02 02:20:50  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 2.7  2000/02/01 23:41:50  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more feature initialization.
 * LOG:
 * LOG: Revision 2.6  2000/02/01 23:09:12  mmiers
 * LOG:
 * LOG:
 * LOG: Auto start the license system.  Can do away with standalone *now*.
 * LOG:
 * LOG: Revision 2.5  2000/01/26 18:12:10  mmiers
 * LOG:
 * LOG:
 * LOG: Add feature processing.
 * LOG:
 * LOG: Revision 2.4  2000/01/26 17:36:31  mmiers
 * LOG:
 * LOG:
 * LOG: Fix feature processing.
 * LOG:
 * LOG: Revision 2.3  1999/12/17 20:41:19  mmiers
 * LOG:
 * LOG:
 * LOG: Still trying to get this to work.
 * LOG:
 * LOG: Revision 2.2  1999/12/16 02:19:20  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
 * LOG: though.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 00:53:01  mmiers
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:20  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.18  1999/12/01 00:11:19  mmiers
 * LOG:
 * LOG:
 * LOG: Get GDI working.
 * LOG:
 * LOG: Revision 1.17  1999/10/25 18:28:11  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.16  1999/10/13 21:59:56  mmiers
 * LOG:
 * LOG:
 * LOG: Put fixme comments in here about TRANSPORT_GetState() calls.
 * LOG:
 * LOG: Revision 1.15  1999/10/13 20:32:44  labuser
 * LOG:
 * LOG:
 * LOG: More cleanup of teardown code.
 * LOG:
 * LOG: Revision 1.14  1999/10/13 17:17:42  labuser
 * LOG:
 * LOG:
 * LOG: Can't do equality check, have to work on individual bits.
 * LOG:
 * LOG: Revision 1.13  1999/10/12 22:59:56  mmiers
 * LOG:
 * LOG:
 * LOG: Rework termination handling of dynamic sockets.  The transport
 * LOG: control needs to go away when the thread does.
 * LOG:
 * LOG: Revision 1.12  1999/10/12 18:32:15  mmiers
 * LOG:
 * LOG:
 * LOG: Exit with error code.
 * LOG:
 * LOG: Revision 1.11  1999/08/11 20:12:35  mmiers
 * LOG:
 * LOG:
 * LOG: Try for cleanness.
 * LOG:
 * LOG: Revision 1.10  1999/08/11 02:35:31  mmiers
 * LOG:
 * LOG:
 * LOG: Try to sanitize the environment variable/string getting.  Trace is
 * LOG: confusing this issue a bit.
 * LOG:
 * LOG: Revision 1.9  1999/07/29 00:08:39  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating some of Hubert's review comments.
 * LOG:
 * LOG: Revision 1.8  1999/06/24 23:06:05  mmiers
 * LOG:
 * LOG:
 * LOG: Remove banner print.
 * LOG:
 * LOG: Revision 1.7  1999/06/23 23:24:31  labuser
 * LOG:
 * LOG:
 * LOG: NO SIDE EFFECTS IN ASSERT STATEMENTS!
 * LOG:
 * LOG: Revision 1.6  1999/06/22 16:26:24  mmiers
 * LOG:
 * LOG:
 * LOG: Document the format string for unnamed transports.
 * LOG:
 * LOG: Revision 1.5  1999/06/21 22:58:59  mmiers
 * LOG:
 * LOG:
 * LOG: Handle the case where we have multiple single user transports (so that
 * LOG: each transport can have a different section name in an INI file).
 * LOG:
 * LOG: Revision 1.4  1999/03/24 22:45:26  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a number of bugs with the new infrastructure.  Provide an
 * LOG: example for the new format INI files.  Add duration to licensing
 * LOG: scheme.  Fix memory leak in timer subsystem.  Fix initialization
 * LOG: bug in thread lib.
 * LOG:
 * LOG: Revision 1.3  1999/03/17 14:27:39  mmiers
 * LOG:
 * LOG:
 * LOG: More work on simultaneous ANSI and CCITT protocols.  Change the size
 * LOG: of the "type" field of ITS_HDR to be 16 bits.
 * LOG:
 * LOG: Revision 1.2  1999/03/12 23:24:46  mmiers
 * LOG:
 * LOG:
 * LOG: Finish dual protocol family support.
 * LOG:
 * LOG: Revision 1.1  1999/03/12 18:20:10  mmiers
 * LOG:
 * LOG:
 * LOG: Break the core functions out of the support library.  This
 * LOG: allows just the core and vendor library to be sold to a customer.
 * LOG:
 * LOG: Revision 1.34  1999/03/12 00:06:10  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.33  1999/02/26 04:09:52  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.32  1999/02/25 22:57:09  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.31  1999/02/12 23:40:24  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for simultaneous protocol families.
 * LOG:
 * LOG: Revision 1.30  1999/02/04 22:26:38  mmiers
 * LOG:
 * LOG:
 * LOG: Fool around with this thing a bit.
 * LOG:
 * LOG: Revision 1.29  1998/11/19 00:36:23  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.28  1998/11/18 19:54:45  mmiers
 * LOG: Final sanitization build.
 * LOG:
 * LOG: Revision 1.27  1998/11/18 16:31:35  mmiers
 * LOG: Add C thread pool test.
 * LOG:
 * LOG: Revision 1.26  1998/11/12 00:09:12  mmiers
 * LOG: Debugging SSP/SSA.  Note that this has a major change for FIFOs.
 * LOG: Revert to the previous version of fifo-win and fifo_trans if this
 * LOG: doesn't work everywhere.
 * LOG:
 * LOG: Revision 1.25  1998/11/05 15:45:59  mmiers
 * LOG: A partial fix for the timer problem.  The timers need reimplementing
 * LOG: as a hash table.
 * LOG:
 * LOG: Revision 1.24  1998/11/05 03:27:02  mmiers
 * LOG: Add serialization counters to transports.
 * LOG:
 * LOG: Revision 1.23  1998/11/03 02:56:14  mmiers
 * LOG: Add registration/deregistration callbacks to TRANSPORT control.
 * LOG:
 * LOG: Revision 1.22  1998/10/28 17:16:35  mmiers
 * LOG: Add/complete C-based thread pools and workers.
 * LOG:
 * LOG: Revision 1.21  1998/10/20 23:37:33  mmiers
 * LOG: Minor tweaks, getting the C-API up to reentrant standards.
 * LOG:
 * LOG: Revision 1.20  1998/10/16 20:48:09  mmiers
 * LOG: Enable MTP3 startup/shutdown.
 * LOG:
 * LOG: Revision 1.19  1998/09/29 16:03:32  mmiers
 * LOG: Disable MTP3 for now.
 * LOG:
 * LOG: Revision 1.18  1998/09/28 20:36:18  jrao
 * LOG: Fix initCount nesting
 * LOG:
 * LOG: Revision 1.17  1998/09/28 20:03:33  mmiers
 * LOG: Add MTP3 support in.
 * LOG:
 * LOG: Revision 1.16  1998/09/28 19:35:27  mmiers
 * LOG: Update to match current C++ code.
 * LOG:
 * LOG: Revision 1.15  1998/09/28 17:22:27  mmiers
 * LOG: Add global stop.
 * LOG:
 * LOG: Revision 1.14  1998/09/21 18:31:18  mmiers
 * LOG: Get C-trace hooked up and working.
 * LOG:
 * LOG: Revision 1.13  1998/07/21 21:29:12  mmiers
 * LOG: Update tests.
 * LOG:
 * LOG: Revision 1.12  1998/07/16 15:53:26  mmiers
 * LOG: Brain fart.
 * LOG:
 * LOG: Revision 1.11  1998/06/26 17:32:14  whu
 * LOG: More bug fixes for the C API.
 * LOG:
 * LOG: Revision 1.10  1998/06/26 17:17:23  whu
 * LOG: Dual code paths suck.  Fix missing code fragments from its++.cpp.
 * LOG:
 * LOG: Revision 1.9  1998/06/26 16:31:25  mmiers
 * LOG: Complete the transport conversion.
 * LOG:
 * LOG: Revision 1.8  1998/06/26 14:54:39  mmiers
 * LOG: Finish conversion.
 * LOG:
 * LOG: Revision 1.7  1998/06/26 14:29:57  mmiers
 * LOG: Convert C++ transports to use C versions.
 * LOG:
 * LOG: Revision 1.6  1998/06/18 23:39:33  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.5  1998/06/18 17:16:29  mmiers
 * LOG: Finish up the C transports and the SS7 transports.
 * LOG:
 * LOG: Revision 1.4  1998/06/17 19:57:05  mmiers
 * LOG: Retain backwards compatibility.
 * LOG:
 * LOG: Revision 1.3  1998/06/16 23:41:00  mmiers
 * LOG: Backwards compatibility fixes.
 * LOG:
 * LOG: Revision 1.2  1998/05/29 22:35:38  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.1  1998/05/29 15:08:59  mmiers
 * LOG: More documentation.
 * LOG:
 *
 *****************************************************************************/

#include <stdlib.h>

#include <its.h>
#include <its_assertion.h>
#include <its_transports.h>
#include <its_route.h>
#include <its_timers.h>
#include <its_trace.h>
#include <its_worker.h>
#include <its_license.h>
#include <its_app.h>
#include <its_transport_factory.h>

#ident "$Id: its.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

static ITS_BOOLEAN  started = ITS_FALSE;
static ITS_BOOLEAN  terminated = ITS_FALSE;
static ITS_BOOLEAN  singleUser = ITS_FALSE;
static ITS_BOOLEAN  recursing = ITS_FALSE;

static int initCount = 0;
static int toolkitCount = 0;

/*
 * stack interface variable
 */
ITSDLLAPI ITS_UINT    ITS_SS7_Mask = 0;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Verify that a user-defined masked has sane SS7 bits set.
 *
 *  Input Parameters:
 *      mask - the mask to verify.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The corrected mask
 *
 *  Notes:
 *      Note that this function should normally not be called by the user.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
ITS_VerifyMask(ITS_UINT mask)
{
    /* sanity check the mask. */
    if (mask & ITS_SS7_MASK)
    {
        /* check ANSI flags */
        if ((mask & ITS_TCAP_ANSI) == ITS_TCAP_ANSI)
        {
            mask |= ITS_SCCP_ANSI;
        }
        if ((mask & ITS_SCCP_ANSI) == ITS_SCCP_ANSI)
        {
            mask |= ITS_MTP3_ANSI;
        }
        if ((mask & ITS_ISUP_ANSI) == ITS_ISUP_ANSI)
        {
            mask |= ITS_MTP3_ANSI;
        }

        /* check ITU flags */
        if ((mask & ITS_TCAP_CCITT) == ITS_TCAP_CCITT)
        {
            mask |= ITS_SCCP_CCITT;
        }
        if ((mask & ITS_SCCP_CCITT) == ITS_SCCP_CCITT)
        {
            mask |= ITS_MTP3_CCITT;
        }
        if ((mask & ITS_ISUP_CCITT) == ITS_ISUP_CCITT)
        {
            mask |= ITS_MTP3_CCITT;
        }

        /* check PRC flags */
        if ((mask & ITS_TCAP_PRC) == ITS_TCAP_PRC)
        {
            mask |= ITS_SCCP_PRC;
        }
        if ((mask & ITS_SCCP_PRC) == ITS_SCCP_PRC)
        {
            mask |= ITS_MTP3_PRC;
        }
        if ((mask & ITS_ISUP_PRC) == ITS_ISUP_PRC)
        {
            mask |= ITS_MTP3_PRC;
        }

        /* check JT flags */
        if ((mask & ITS_TCAP_TTC) == ITS_TCAP_TTC)
        {
            mask |= ITS_SCCP_TTC;
        }
        if ((mask & ITS_SCCP_TTC) == ITS_SCCP_TTC)
        {
            mask |= ITS_MTP3_TTC;
        }
        if ((mask & ITS_ISUP_TTC) == ITS_ISUP_TTC)
        {
            mask |= ITS_MTP3_TTC;
        }

    }

    return (mask);
}

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
    int startCount;

    if (recursing)
    {
        return (ITS_SUCCESS);
    }

    initCount++;

    if (started)
    {
        return (ITS_SUCCESS);
    }

    started = ITS_TRUE;
    recursing = ITS_TRUE;

    startCount = initCount - 1;

    ITS_SS7_Mask = ITS_VerifyMask(mask);

    /* make feature manipulation thread safe. */
    if (ITS_FeatureStart() != ITS_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }

    /* init features */
    if (ITS_InitFeatures() != ITS_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }

    recursing = ITS_FALSE;

    toolkitCount = initCount - startCount;

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

    initCount--;

    /*
     * Note: we WANT underflow here to stop the Terminates/Destroy/Stop
     * from happening twice.
     */
    if (initCount - toolkitCount)
    {
        return;
    }

    terminated = ITS_TRUE;

    ITS_DestroyFeatures();

    ITS_FeatureStop();
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
    ITS_TRACE_DEBUG(("ITS_Terminate:\n"));

    if (singleUser)
    {
        if (handle)
        {
            TRANSPORT_IS_ACTIVE(handle) = ITS_FALSE;

            if (TRANSPORT_NAME(handle))
            {
                ITS_TRACE_DEBUG(("ITS_Terminate: terminating single user '%s'\n",
                                 TRANSPORT_NAME(handle)));
            }

            FACTORY_DeleteInstance(&itsTRANSPORT_FACTORY_ClassRec, handle);
        }
    }
    else
    {
        if (handle)
        {
            WORKER_Control* work =
                WORKER_FindWorker(TRANSPORT_INSTANCE(handle));

            if (TRANSPORT_NAME(WORKER_TRANSPORT(work)))
            {
                ITS_TRACE_DEBUG(("ITS_Terminate: terminating multi "
                                 "user '%s'\n",
                                 TRANSPORT_NAME(WORKER_TRANSPORT(work))));
            }

            if (work != NULL)
            {
                TRANSPORT_CUR_TERM_INVOKE(WORKER_TRANSPORT(work))++;

                TRANSPORT_IS_ACTIVE(handle) = ITS_FALSE;

                if (!WORKER_THREAD(work).exit)
                {
                    if (!(WORKER_MASK(work) & ITS_TRANSPORT_DONT_CLEAN))
                    {
                        ITS_EVENT ev;

                        ITS_EVENT_INIT(&ev, 0, 0);

                        TIMERS_Clean(WORKER_INSTANCE(work));
                        ROUTE_Clean(WORKER_INSTANCE(work));

                        while (WORKER_PeekNextEvent(work, &ev) == ITS_SUCCESS)
                        {
                        }
                    }
                }

                if ((WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET) &&
                    (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN))
                {
                    WORKER_DeleteTransport(work);
                }
            }
        }
    }

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
    ITS_C_REQUIRE(instance != ITS_NO_SRC && instance != ITS_INVALID_SRC);

    /* start our subsystems. */
    if (ITS_GlobalStart(mask) != ITS_SUCCESS)
    {
        return (NULL);
    }

    ITS_TRACE_DEBUG(("ITS_Initialize: mask %08x instance %04x\n",
                     mask, instance));

    if (ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SINGLE_USER)
    {
        singleUser = ITS_TRUE;
    }

    if (singleUser)
    {
        TRANSPORT_Control* tr = NULL;
        char name[64];
    
        sprintf(name, ITS_UNNAMED_TRANSPORT_FORMAT_STRING, instance);

        ITS_TRACE_DEBUG(("ITS_Initialize: single user mode\n"));

        tr = (TRANSPORT_Control *)
            FACTORY_CreateInstance(&itsTRANSPORT_FACTORY_ClassRec,
                                   name, instance, mask);

        if (tr)
        {
            TRANSPORT_IS_ACTIVE(tr) = ITS_TRUE;
        }

        return (ITS_HANDLE)tr;
    }
    else
    {
        WORKER_Control* work = WORKER_FindWorker(instance);
        int ret;

        ITS_TRACE_DEBUG(("ITS_Initialize: multi-user mode\n"));

        if (work)
        {
            if (WORKER_MASK(work) & ITS_TRANSPORT_DELAY_CREATE)
            {
                ITS_TRACE_DEBUG(("ITS_Initialize: transport has "
                                 "delayed create\n"));

                if ((ret = WORKER_CreateTransport(work)) != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR(("ITS_Initialize: transport create "
                                     "failed: %d\n", ret));

                    return (NULL);
                }
                else
                {
                    TRANSPORT_CUR_INIT_INVOKE(WORKER_TRANSPORT(work)) = 0;
                    TRANSPORT_CUR_TERM_INVOKE(WORKER_TRANSPORT(work)) = 0;

                    if (!(WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET) &&
                        !(WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN))
                    {
                        WORKER_MASK(work) &= ~ITS_TRANSPORT_DELAY_CREATE;
                    }
                }
            }
            else
            {
                TRANSPORT_CUR_INIT_INVOKE(WORKER_TRANSPORT(work))++;
            }
    
            TRANSPORT_IS_ACTIVE(WORKER_TRANSPORT(work)) = ITS_TRUE;

            ITS_TRACE_DEBUG(("ITS_Initialize: worker:transport created: "
                             "%08x:%08x\n",
                             work, WORKER_TRANSPORT(work)));

            if (TRANSPORT_CUR_INIT_INVOKE(WORKER_TRANSPORT(work)) !=
                TRANSPORT_CUR_TERM_INVOKE(WORKER_TRANSPORT(work)))
            {
                ITS_TRACE_CRITICAL(("ITS_Initialize: Initialize/Terminate "
                                    "mismatch: "
                                    "%u : %u !!!\n",
                                    TRANSPORT_CUR_INIT_INVOKE(WORKER_TRANSPORT(work)),
                                    TRANSPORT_CUR_TERM_INVOKE(WORKER_TRANSPORT(work))));

                TRANSPORT_CUR_TERM_INVOKE(WORKER_TRANSPORT(work)) =
                    TRANSPORT_CUR_INIT_INVOKE(WORKER_TRANSPORT(work));
            }

            TRANSPORT_BACK(WORKER_TRANSPORT(work)) = WORKER_TRANSPORT(work);

            return (ITS_HANDLE)WORKER_TRANSPORT(work);
        }
        else
        {
            return (NULL);
        }
    }
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
    ITS_TRACE_DEBUG(("ITS_GetNextEvent:\n"));

    ITS_C_REQUIRE(handle != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(handle) != NULL);

    return TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(handle))(handle,
                                                                 event);
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
    ITS_TRACE_DEBUG(("ITS_PeekNextEvent:\n"));

    ITS_C_REQUIRE(handle != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(handle) != NULL);

    return TRANSPORT_CLASS_PEEK_NEXT_EVENT(ITS_OBJ_CLASS(handle))(handle,
                                                                  event);
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
    ITS_TRACE_DEBUG(("ITS_PutEvent:\n"));

    ITS_C_REQUIRE(handle != NULL);
    ITS_C_REQUIRE(ITS_OBJ_CLASS(handle) != NULL);

    return TRANSPORT_CLASS_PUT_EVENT(ITS_OBJ_CLASS(handle))(handle,
                                                            event);
}
