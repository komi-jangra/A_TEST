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
 * LOG: Revision 1.2  2007/03/30 04:59:05  cvsadmin
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
 * LOG: Revision 7.1.46.1  2005/01/05 07:21:27  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2002/01/09 23:28:35  mmiers
 * LOG: Switch FindTransport to a reference counting mechanism to
 * LOG: avoid race problems.
 * LOG:
 * LOG: Revision 5.3  2001/11/15 18:07:36  mmiers
 * LOG: Add exit proc for SCTP transports.
 * LOG:
 * LOG: Revision 5.2  2001/09/19 00:53:36  mmiers
 * LOG: Bugs found in cross platform build.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 19:18:17  mmiers
 * LOG: Finish up HMI
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.11  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.10  2001/02/28 17:09:45  mmiers
 * LOG: Add XML parser.  Not the greatest, but small, lightweight, and we
 * LOG: can use other tools for correctness verification.
 * LOG:
 * LOG: Revision 3.9  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.8  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.7  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.5  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.5  2000/11/09 01:32:34  mmiers
 * LOG: Some cross platform issues, more comments about the new routing mech.
 * LOG:
 * LOG: Revision 3.4  2000/09/01 20:56:30  mmiers
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.3  2000/08/24 23:06:40  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.2  2000/08/22 18:53:29  mmiers
 * LOG: Track down the KDD problem.  The MEMPOOL is really finding some tricky
 * LOG: bugs.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:34  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.12  2000/07/07 22:27:15  mmiers
 * LOG:
 * LOG:
 * LOG: Rework close logic for sockets.
 * LOG:
 * LOG: Revision 2.11  2000/07/06 20:47:19  rsonak
 * LOG:
 * LOG:
 * LOG: Peek all pending events, not just the first on the queue.
 * LOG:
 * LOG: Revision 2.10  2000/07/05 22:25:37  rsonak
 * LOG:
 * LOG: route: read from global section, not ini name
 * LOG: kasock: add trace saying which down transport sent sltm
 * LOG: iptrans: add debug
 * LOG:
 * LOG: Revision 2.9  2000/07/04 00:14:57  rsonak
 * LOG:
 * LOG:
 * LOG: Debug, bad route delete, transport route ls/lc collection
 * LOG:
 * LOG: Revision 2.8  2000/06/22 23:10:46  rsonak
 * LOG: Iterative servers cannot run protocols.
 * LOG: Fix route bugs with multilink routes.
 * LOG:
 * LOG: Revision 2.7  2000/06/17 01:18:39  rsonak
 * LOG:
 * LOG:
 * LOG: Integration bug hunting.
 * LOG:
 * LOG: Revision 2.6  2000/06/12 23:39:58  rsonak
 * LOG:
 * LOG: Integration bug hunting.
 * LOG:
 * LOG: Revision 2.5  2000/06/02 17:19:12  mmiers
 * LOG:
 * LOG:
 * LOG: Socket changes.
 * LOG:
 * LOG: Revision 2.4  2000/05/26 20:52:17  mmiers
 * LOG:
 * LOG:
 * LOG: Prep the EP KA class for SCTP.
 * LOG:
 * LOG: Revision 2.3  2000/05/15 22:34:02  mmiers
 * LOG:
 * LOG:
 * LOG: Add ON_CONNECT/ON_DISCONNECT functions.  Really only used by sockets
 * LOG: and fifos.
 * LOG:
 * LOG: Revision 2.2  2000/05/13 00:36:32  mmiers
 * LOG:
 * LOG:
 * LOG: Ok, we can read and write TALI messages, now to build the state
 * LOG: machine...
 * LOG:
 * LOG: Revision 2.1  2000/05/10 23:43:45  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based transports with heartbeats.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_transports.h>
#include <its_kasock_trans.h>
#include <its_trace.h>
#include <its_thread.h>
#include <its_timers.h>
#include <its_tq_trans.h>
#include <its_assertion.h>

#ident "$Id: its_kasock_trans.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*
 * trace control
 */
#define KEEPALIVE_DEBUG

static ITS_USHORT   numKATransports = 0;
static ITS_USHORT   maxKATransports = 8;
static ITS_USHORT*  transportList = NULL;
static ITS_MUTEX    kaMutex;
static ITS_THREAD   kaThread;

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      These next two functions essentially represents our protocol for
 *      socket communication.
 *
 *  Input Parameters:
 *      msg - the message to convert
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
 ************************************************************************/
static int
ReadEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;
    KASOCKTRAN_Manager *kt = (KASOCKTRAN_Manager *)h;
    ITS_Class cl = ITS_OBJ_CLASS(kt);

    ITS_C_REQUIRE(h != NULL);
    ITS_C_REQUIRE(ev != NULL);

repeat:
    if (KASOCKTRAN_CLASS_LOW_READ(cl))
    {
        ret = KASOCKTRAN_CLASS_LOW_READ(cl)(kt,
                                            KASOCKTRAN_LOW_READ_BUF(kt));

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }
    }
    else
    {
        return (ITS_ENOTRANSPORT);
    }

    ev->src = 0;
    ev->len = 0;

    if (KASOCKTRAN_CLASS_DECODE(cl))
    {
        ret = KASOCKTRAN_CLASS_DECODE(cl)(kt, ev,
                                          KASOCKTRAN_LOW_READ_BUF(kt));

        if (ret == ITS_ENOMSG)
        {
            goto repeat;
        }

        return (ret);
    }
    else
    {
        ITS_TRACE_ERROR(("KARead: Using KA transport without starting KA\n"));

        return (ITS_ERCVFAIL);
    }
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      These next two functions essentially represents our protocol for
 *      socket communication.
 *
 *  Input Parameters:
 *      msg - the message to convert
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
 ************************************************************************/
static int
WriteEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;
    KASOCKTRAN_Manager *kt = (KASOCKTRAN_Manager *)h;
    ITS_Class cl = ITS_OBJ_CLASS(kt);

    ITS_C_REQUIRE(h != NULL);
    ITS_C_REQUIRE(ev != NULL);

    if (KASOCKTRAN_CLASS_ENCODE(cl))
    {
        ret = KASOCKTRAN_CLASS_ENCODE(cl)(kt, ev,
                                          KASOCKTRAN_LOW_WRITE_BUF(kt));

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }
    }
    else
    {
        ITS_TRACE_ERROR(("KAWrite: Attempt to write when KA not enabled.\n"));

        return (ITS_ESENDFAIL);
    }

    if (KASOCKTRAN_CLASS_LOW_WRITE(cl))
    {
        ret = KASOCKTRAN_CLASS_LOW_WRITE(cl)(kt,
                                              KASOCKTRAN_LOW_WRITE_BUF(kt));

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }
    }

    return (ITS_SUCCESS);
}

static SOCKTRAN_ClassExtRec KAReadWrite =
{
    /* coreClass */
    {
        ITS_EXT_VERSION
    },
    /* socktranClass */
    {
        ReadEvent,  /* Read one */
        WriteEvent  /* Write one */
    }
};

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function creates a KeepAlive socket transport
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
 ************************************************************************/
static int
Create(ITS_Object h, va_list args)
{
    KASOCKTRAN_Manager *tc = (KASOCKTRAN_Manager *)h;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;
    int ret;

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    /* if it is a rendezvous socket, never start keepalives on it */
    if (TRANSPORT_MASK(tc) & ITS_TRANSPORT_SSOCKET_ITER)
    {
        return (ITS_SUCCESS);
    }

    if (!ITS_CLASS_INITTED(itsKEEPALIVE_Class))
    {
        ITS_TRACE_CRITICAL(("Create: itsKEEPALIVE_Class Not Initted\n"));
        abort();
    }

    if (KASOCKTRAN_CLASS_REGISTER(ITS_OBJ_CLASS(tc)))
    {
        ret = KASOCKTRAN_CLASS_REGISTER(ITS_OBJ_CLASS(tc))(tc);

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }
    }

    KASOCKTRAN_LOW_READ_BUF(tc) = NULL;
    KASOCKTRAN_LOW_WRITE_BUF(tc) = NULL;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function destroys a KeepAlive socket transport
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
 ************************************************************************/
static void
Destroy(ITS_Object h)
{
    KASOCKTRAN_Manager *tc = (KASOCKTRAN_Manager *)h;

    if (KASOCKTRAN_CLASS_DEREGISTER(ITS_OBJ_CLASS(h)))
    {
        KASOCKTRAN_CLASS_DEREGISTER(ITS_OBJ_CLASS(h))(tc);
    }
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function initializes the class part for keepalive subs.
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
 ************************************************************************/
static int
ClassPartInit(ITS_Class subClass)
{
    ITS_Class superClass = ITS_CLASS_SUPERCLASS(subClass);

    if (!superClass)
    {
        ITS_TRACE_ERROR(("Invalid class hierarchy\n"));

        return (ITS_ENOTFOUND);
    }

    if (KASOCKTRAN_CLASS_REGISTER(subClass) ==
        KASOCKTRAN_CLASS_REGISTER_INHERIT)
    {
        KASOCKTRAN_CLASS_REGISTER(subClass) =
            KASOCKTRAN_CLASS_REGISTER(superClass);
    }

    if (KASOCKTRAN_CLASS_DEREGISTER(subClass) ==
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT)
    {
        KASOCKTRAN_CLASS_DEREGISTER(subClass) =
            KASOCKTRAN_CLASS_DEREGISTER(superClass);
    }

    if (KASOCKTRAN_CLASS_LOW_READ(subClass) ==
        KASOCKTRAN_CLASS_LOW_READ_INHERIT)
    {
        KASOCKTRAN_CLASS_LOW_READ(subClass) =
            KASOCKTRAN_CLASS_LOW_READ(superClass);
    }

    if (KASOCKTRAN_CLASS_LOW_WRITE(subClass) ==
        KASOCKTRAN_CLASS_LOW_WRITE_INHERIT)
    {
        KASOCKTRAN_CLASS_LOW_WRITE(subClass) =
            KASOCKTRAN_CLASS_LOW_WRITE(superClass);
    }

    if (KASOCKTRAN_CLASS_ENCODE(subClass) ==
        KASOCKTRAN_CLASS_ENCODE_INHERIT)
    {
        KASOCKTRAN_CLASS_ENCODE(subClass) =
            KASOCKTRAN_CLASS_ENCODE(superClass);
    }

    if (KASOCKTRAN_CLASS_DECODE(subClass) ==
        KASOCKTRAN_CLASS_DECODE_INHERIT)
    {
        KASOCKTRAN_CLASS_DECODE(subClass) =
            KASOCKTRAN_CLASS_DECODE(superClass);
    }

    if (KASOCKTRAN_CLASS_CHECK_TIME(subClass) ==
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT)
    {
        KASOCKTRAN_CLASS_CHECK_TIME(subClass) =
            KASOCKTRAN_CLASS_CHECK_TIME(superClass);
    }

    if (KASOCKTRAN_CLASS_CHECK_EVENT(subClass) ==
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT)
    {
        KASOCKTRAN_CLASS_CHECK_EVENT(subClass) =
            KASOCKTRAN_CLASS_CHECK_EVENT(superClass);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
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
Register(KASOCKTRAN_Manager *tc)
{
    ITS_TRACE_DEBUG(("KASOCK register\n"));

    ITS_C_REQUIRE(tc != NULL);

    if (MUTEX_AcquireMutex(&kaMutex) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Register: BadMutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* add instance */
    transportList[numKATransports] = TRANSPORT_INSTANCE(tc);
    numKATransports++;

    /* grow list if necessary */
    if (numKATransports == maxKATransports)
    {
        maxKATransports *= 2;

        if ((transportList = (ITS_USHORT *)
                                realloc(transportList,
                                        maxKATransports *
                                            sizeof(ITS_USHORT)))
            == NULL)
        {
            MUTEX_ReleaseMutex(&kaMutex);

            return (ITS_ENOMEM);
        }
    }

    MUTEX_ReleaseMutex(&kaMutex);

    return (ITS_SUCCESS);
}

/*.implementation:static
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
Deregister(KASOCKTRAN_Manager *tc)
{
    int i;

    ITS_TRACE_DEBUG(("KASOCK deregister\n"));

    ITS_C_REQUIRE(tc != NULL);

    if (MUTEX_AcquireMutex(&kaMutex) != ITS_SUCCESS)
    {
        return;
    }

    /* locate and remove instance */
    for (i = 0; i < numKATransports; i++)
    {
        if (transportList[i] == TRANSPORT_INSTANCE(tc))
        {
            numKATransports--;

            if (numKATransports != 0 &&
                i != numKATransports)
            {
                /* compact */
                memmove(&transportList[i],
                        &transportList[i+1],
                        sizeof(ITS_USHORT) * (numKATransports - i));
            }

            MUTEX_ReleaseMutex(&kaMutex);

            return;
        }
    }

    MUTEX_ReleaseMutex(&kaMutex);
}

/*.implementation:static
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
LowRead(KASOCKTRAN_Manager *kt, void *buf)
{
    ITS_TRACE_ERROR(("LowRead: subclass must provide this\n"));

    return (ITS_ENOTRANSPORT);
}

/*.implementation:static
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
LowWrite(KASOCKTRAN_Manager *kt, void *buf)
{
    ITS_TRACE_ERROR(("LowWrite: subclass must provide this\n"));

    return (ITS_ENOTRANSPORT);
}

/*.implementation:static
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
Encode(KASOCKTRAN_Manager *kt, ITS_EVENT *ev, void *buf)
{
    ITS_TRACE_ERROR(("Encode: subclass must provide this\n"));

    return (ITS_ENOTRANSPORT);
}

/*.implementation:static
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
Decode(KASOCKTRAN_Manager *kt, ITS_EVENT *ev, void *buf)
{
    ITS_TRACE_ERROR(("Decode: subclass must provide this\n"));

    return (ITS_ENOTRANSPORT);
}

/*.implementation:static
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
CheckTime(KASOCKTRAN_Manager *kt)
{
    ITS_TRACE_ERROR(("CheckTime: subclass must provide this\n"));
}

/*.implementation:static
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
CheckEvent(KASOCKTRAN_Manager *kt, ITS_EVENT *ev)
{
    ITS_TRACE_ERROR(("CheckEvent: subclass must provide this\n"));
}

/*.implementation:static
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
KeepAliveTimerCheck()
{
    TRANSPORT_Control *tc;
    KASOCKTRAN_Manager *kt;
    int i;

    ITS_TRACE_DEBUG(("KASOCK timer check\n"));

    if (MUTEX_AcquireMutex(&kaMutex) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("KA_KeepAliveTimerCheck: failed to acquire "
                         "mutex.\n"));

        return;
    }

    for (i = 0; i < numKATransports; i++)
    {
        tc = TRANSPORT_FindTransport(transportList[i]);
        if (!tc)
        {
            ITS_TRACE_WARNING(("KA_KeepAliveTimerCheck: bad or missing"
                               "transport: %04x\n", transportList[i]));

            continue;
        }

        kt = (KASOCKTRAN_Manager *)tc;

        if (!SOCKTRAN_IS_VALID(kt))
        {
            ITS_TRACE_DEBUG(("KT_KeepAliveTimerCheck: transport %04x "
                             "isn't valid right now.\n", transportList[i]));

            TRANSPORT_UnfindTransport(tc);

            continue;
        }

        ITS_TRACE_DEBUG(("KASOCK CheckTime\n"));

        if (KASOCKTRAN_CLASS_CHECK_TIME(ITS_OBJ_CLASS(kt)))
        {
            KASOCKTRAN_CLASS_CHECK_TIME(ITS_OBJ_CLASS(kt))(kt);
        }

        TRANSPORT_UnfindTransport(tc);
    }

    MUTEX_ReleaseMutex(&kaMutex);
}

/*.implementation:static
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
static THREAD_RET_TYPE
KeepAliveThread(void *arg)
{
    ITS_HANDLE ktHandle;
    ITS_EVENT ktEvent;
    KASOCKTRAN_Manager *kaSrc;

    memset(&ktEvent, 0, sizeof(ITS_EVENT));

    if ((ktHandle = TQUEUETRAN_CreateTransport("KeepAlives",
                                                ITS_KEEPALIVE_INSTANCE,
                                                0)) == NULL)
    {
        ITS_TRACE_ERROR(("KeepAliveThread: Couldn't create transport."));

        exit(EXIT_FAILURE);
    }

    if (!ktHandle)
    {
        ITS_TRACE_ERROR(("KeepAliveThread: failed to initialize "
                         "transport.\n"));

        TQUEUETRAN_DeleteTransport(ktHandle);

        exit(EXIT_FAILURE);
    }

    TRANSPORT_IS_ACTIVE(ktHandle) = ITS_TRUE;

    for (;;)
    {
        TIMERS_Sleep(1);

        while (TRANSPORT_CLASS_PEEK_NEXT_EVENT(ITS_OBJ_CLASS(ktHandle))
                                                (ktHandle, &ktEvent) ==
               ITS_SUCCESS)
        {
            switch (ktEvent.src)
            {
            case ITS_KEEPALIVE_INSTANCE:
                /* termination message */
                ITS_TRACE_DEBUG(("KeepAliveThread: exiting ok\n"));

                TRANSPORT_IS_ACTIVE(ktHandle) = ITS_FALSE;

                TQUEUETRAN_DeleteTransport(ktHandle);

                free(transportList);

                MUTEX_DeleteMutex(&kaMutex);

                THREAD_DeleteThread(&kaThread);

                THREAD_NORMAL_EXIT;

                break;

            default:
                /* they initiated: mark response pending. */
                kaSrc = (KASOCKTRAN_Manager *)
                    TRANSPORT_FindTransport(ktEvent.src);

                if (kaSrc &&
                    KASOCKTRAN_CLASS_CHECK_EVENT(ITS_OBJ_CLASS(kaSrc)))
                {
                    KASOCKTRAN_CLASS_CHECK_EVENT(ITS_OBJ_CLASS(kaSrc))(kaSrc,
                                                                       &ktEvent);

                    TRANSPORT_UnfindTransport((TRANSPORT_Control *)kaSrc);
                }
                else
                {
                    ITS_TRACE_ERROR(("Missing kaSrc or no event check: t %04x.\n",
                                     kaSrc));
                    ITS_TRACE_ERROR(("Event says: %04x is still running.\n",
                                     ktEvent.src));
                    if (kaSrc)
                    {
                        TRANSPORT_UnfindTransport((TRANSPORT_Control *)kaSrc);
                    }
                }

                break;
            }
        }

        /* See if a keepalive needs to be sent */
        KeepAliveTimerCheck();
    }

    TRANSPORT_IS_ACTIVE(ktHandle) = ITS_FALSE;

    /* NOTREACHED */
    THREAD_NORMAL_EXIT;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the GDI class record (aka the GDI subsystem).
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
Init(ITS_Class objClass)
{
    if (MUTEX_CreateMutex(&kaMutex, 0) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    numKATransports = 0;
    maxKATransports = 8;

    if ((transportList = (ITS_USHORT *)
                            calloc(maxKATransports,
                                   sizeof(ITS_USHORT))) == NULL)
    {
        MUTEX_DeleteMutex(&kaMutex);

        return (ITS_ENOMEM);
    }

    if (THREAD_CreateThread(&kaThread, 0,
                            KeepAliveThread, NULL,
                            ITS_TRUE) != ITS_SUCCESS)
    {
        free(transportList);

        MUTEX_DeleteMutex(&kaMutex);

        return (ITS_EBADTHREAD);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the GDI class record (aka terminate the GDI subsystem).
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
Term(ITS_Class objClass)
{
    void *status;

    ITS_EVENT stopEvent;

    stopEvent.src = ITS_KEEPALIVE_INSTANCE;
    stopEvent.len = 0;

    TRANSPORT_PutEvent(ITS_KEEPALIVE_INSTANCE, &stopEvent);

    THREAD_WaitForThread(&kaThread, &status);
}

ITSDLLAPI ITS_ClassRec itsKEEPALIVE_ClassRec =
{
    /* core */
    {
        NULL,
        0,
        ITS_FALSE,
        0,
        "KeepAlive",
        Init,
        Term,
        NULL,
        NULL,
        NULL
    }
};

ITSDLLAPI ITS_Class itsKEEPALIVE_Class = &itsKEEPALIVE_ClassRec;

/*
 * the class record
 */
ITSDLLAPI KASOCKTRAN_ClassRec itsKASOCKTRAN_ClientClassRec =
{
    /* core */
    {
        (ITS_Class)&itsSOCKTRAN_ClientClassRec,     /* super class */
        sizeof(KASOCKTRAN_Manager),                 /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        KASOCKTRAN_CLIENT_CLASS_NAME,               /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ClassPartInit,                              /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        Create,                                     /* create routine */
        Destroy,                                    /* destructor */
        ITS_INST_CLONE_INHERIT,                     /* inherit clone */
        ITS_INST_PRINT_INHERIT,                     /* inherit print */
        ITS_INST_SERIAL_INHERIT,                    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                    /* inherit equals */
        ITS_INST_HASH_INHERIT,                      /* inherit equals */
        (ITS_ClassExt)&KAReadWrite                  /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        Register,               /* register */
        Deregister,             /* deregister */
        LowRead,                /* low read */
        LowWrite,               /* low write */
        Encode,                 /* encode */
        Decode,                 /* decode */
        CheckTime,              /* check time */
        CheckEvent              /* check event */
    }
};

ITSDLLAPI TRANSPORT_Class itsKASOCKTRAN_ClientClass =
    (TRANSPORT_Class)&itsKASOCKTRAN_ClientClassRec;

ITSDLLAPI KASOCKTRAN_ClassRec itsKASOCKTRAN_ServerClassRec =
{
    /* core */
    {
        (ITS_Class)&itsSOCKTRAN_ServerClassRec,     /* super class */
        sizeof(KASOCKTRAN_Manager),                 /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        KASOCKTRAN_SERVER_CLASS_NAME,               /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ClassPartInit,                              /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        Create,                                     /* create routine */
        Destroy,                                    /* destructor */
        ITS_INST_CLONE_INHERIT,                     /* inherit clone */
        ITS_INST_PRINT_INHERIT,                     /* inherit print */
        ITS_INST_SERIAL_INHERIT,                    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                    /* inherit equals */
        ITS_INST_HASH_INHERIT,                      /* inherit equals */
        (ITS_ClassExt)&KAReadWrite                  /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        Register,               /* register */
        Deregister,             /* deregister */
        LowRead,                /* low read */
        LowWrite,               /* low write */
        Encode,                 /* encode */
        Decode,                 /* decode */
        CheckTime,              /* check time */
        CheckEvent              /* check event */
    }
};

ITSDLLAPI TRANSPORT_Class itsKASOCKTRAN_ServerClass =
    (TRANSPORT_Class)&itsKASOCKTRAN_ServerClassRec;

/*
 * the dynamic server class record
 */
ITSDLLAPI KASOCKTRAN_ClassRec itsKASOCKTRAN_DynamicServerClassRec =
{
    /* core */
    {
        (ITS_Class)&itsSOCKTRAN_DynamicServerClassRec,  /* the root object */
        sizeof(KASOCKTRAN_Manager),                     /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        KASOCKTRAN_DYNAMIC_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ClassPartInit,                                  /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        (ITS_ClassExt)&KAReadWrite                      /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        Register,               /* register */
        Deregister,             /* deregister */
        LowRead,                /* low read */
        LowWrite,               /* low write */
        Encode,                 /* encode */
        Decode,                 /* decode */
        CheckTime,              /* check time */
        CheckEvent              /* check event */
    }
};

ITSDLLAPI TRANSPORT_Class itsKASOCKTRAN_DynamicServerClass =
    (TRANSPORT_Class)&itsKASOCKTRAN_DynamicServerClassRec;

static SOCKTRAN_ClassExtRec KAEPReadWrite =
{
    /* coreClass */
    {
        ITS_EXT_VERSION
    },
    /* socktranClass */
    {
        ReadEvent,  /* Read one */
        WriteEvent, /* Write one */
        (SOCKTRAN_Class)&itsKASOCKTRAN_RemoteEndPointClassRec
    }
};

/*
 * the dynamic server class record
 */
ITSDLLAPI KASOCKTRAN_ClassRec itsKASOCKTRAN_LocalEndPointClassRec =
{
    /* core */
    {
        (ITS_Class)&itsSOCKTRAN_LocalEndPointClassRec,  /* the root object */
        sizeof(KASOCKTRAN_Manager),                     /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        KASOCKTRAN_DYNAMIC_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ClassPartInit,                                  /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        (ITS_ClassExt)&KAEPReadWrite                    /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        Register,               /* register */
        Deregister,             /* deregister */
        LowRead,                /* low read */
        LowWrite,               /* low write */
        Encode,                 /* encode */
        Decode,                 /* decode */
        CheckTime,              /* check time */
        CheckEvent              /* check event */
    }
};

ITSDLLAPI TRANSPORT_Class itsKASOCKTRAN_LocalEndPointClass =
    (TRANSPORT_Class)&itsKASOCKTRAN_LocalEndPointClassRec;

/*
 * the dynamic server class record
 */
ITSDLLAPI KASOCKTRAN_ClassRec itsKASOCKTRAN_RemoteEndPointClassRec =
{
    /* core */
    {
        (ITS_Class)&itsSOCKTRAN_RemoteEndPointClassRec, /* the root object */
        sizeof(KASOCKTRAN_Manager),                     /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        KASOCKTRAN_DYNAMIC_CLASS_NAME,                  /* class name */
        NULL,                                           /* class initialize */
        NULL,                                           /* class destroy */
        ClassPartInit,                                  /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        (ITS_ClassExt)&KAEPReadWrite                    /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        Register,               /* register */
        Deregister,             /* deregister */
        LowRead,                /* low read */
        LowWrite,               /* low write */
        Encode,                 /* encode */
        Decode,                 /* decode */
        CheckTime,              /* check time */
        CheckEvent              /* check event */
    }
};

ITSDLLAPI TRANSPORT_Class itsKASOCKTRAN_RemoteEndPointClass =
    (TRANSPORT_Class)&itsKASOCKTRAN_RemoteEndPointClassRec;
