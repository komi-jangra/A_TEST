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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:15  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:45  cvsadmin
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
 * LOG: Revision 6.3  2002/08/22 20:44:53  omayor
 * LOG: Added PRC if defines.
 * LOG:
 * LOG: Revision 6.2  2002/08/15 15:13:34  hcho
 * LOG: Linkcode set to zero for compliance.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2002/01/02 20:47:46  mmiers
 * LOG: CCITT doesn't include the link.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.8  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/02/15 16:05:45  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.5  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.5  2000/11/09 00:48:41  mmiers
 * LOG: Today's installment.  Also an IMAL fix.
 * LOG:
 * LOG: Revision 3.4  2000/09/02 01:41:26  mmiers
 * LOG: Don't use source event when reflecting heartbeat.
 * LOG:
 * LOG: Revision 3.3  2000/09/01 20:56:30  mmiers
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:38  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:58  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.17  2000/08/07 20:29:49  mmiers
 * LOG: Make recv pattern the SLTM we get.
 * LOG:
 * LOG: Revision 1.16  2000/08/05 00:20:33  mmiers
 * LOG: IMAL: Add per link SLTM data.
 * LOG: SCTP: Update implementation.
 * LOG:
 * LOG: Revision 1.15  2000/07/13 19:29:14  mmiers
 * LOG:
 * LOG: Per transport timer.
 * LOG:
 * LOG: Revision 1.14  2000/07/12 15:25:47  mmiers
 * LOG:
 * LOG: Some cleanups and performance enhancements.
 * LOG:
 * LOG: Revision 1.13  2000/07/11 23:37:49  rsonak
 * LOG:
 * LOG:
 * LOG: flush after print.
 * LOG:
 * LOG: Revision 1.12  2000/07/10 22:49:10  mmiers
 * LOG:
 * LOG:
 * LOG: return after shutdown, don't start new KA.
 * LOG:
 * LOG: Revision 1.11  2000/07/07 22:27:32  mmiers
 * LOG:
 * LOG:
 * LOG: Move printf to avoid stalls.
 * LOG:
 * LOG: Revision 1.10  2000/07/05 22:26:54  rsonak
 * LOG:
 * LOG:
 * LOG: Try to track down the thrashing sockets.
 * LOG:
 * LOG: Revision 1.9  2000/06/23 19:09:54  rsonak
 * LOG:
 * LOG:
 * LOG: When you get SLTA, stop the pending test.
 * LOG:
 * LOG: Revision 1.8  2000/06/22 23:08:40  rsonak
 * LOG: Iterative servers cannot run protocols.
 * LOG:
 * LOG: Revision 1.7  2000/06/17 01:19:13  rsonak
 * LOG:
 * LOG: Integration bug hunting, let user messages pass if the event id is
 * LOG: not for MTP3.
 * LOG:
 * LOG: Revision 1.6  2000/06/12 23:40:16  rsonak
 * LOG:
 * LOG:
 * LOG: Integration bug hunting.
 * LOG:
 * LOG: Revision 1.5  2000/06/02 17:52:10  mmiers
 * LOG:
 * LOG:
 * LOG: Timeout means shutdown for KASOCKs.
 * LOG:
 * LOG: Revision 1.4  2000/05/11 22:48:16  mmiers
 * LOG:
 * LOG:
 * LOG: Update link state when heartbeat detects failure.
 * LOG:
 * LOG: Revision 1.3  2000/05/11 20:44:30  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the IMAL heartbeat.
 * LOG:
 * LOG: Revision 1.2  2000/05/11 02:06:13  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 1.1  2000/05/10 23:39:50  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based protocols with heartbeats.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_app.h>
#include <its_iniparse.h>
#include <its_sockets.h>
#include <its_mutex.h>
#include <its_transports.h>
#include <its_ip_trans.h>
#include <its_tq_trans.h>
#include <its_trace.h>
#include <its_thread.h>
#include <its_timers.h>

#ident "$Id: its_imal.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

#include <stdio.h>

#if defined(ANSI)
#include <ansi/sltm.h>
#include <ansi/mtp3.h>
#elif defined(CCITT)
#include <itu/sltm.h>
#include <itu/mtp3.h>
#elif defined(PRC)
#include <china/sltm.h>
#include <china/mtp3.h>
#elif defined(TTC)
#include <japan/sltm.h>
#include <japan/mtp3.h>
#else
#error "Protocol family not defined."
#endif

#define IMAL_IMPLEMENTATION

#include <its_imal_trans.h>

/*
 * trace control
 */
#define IMAL_DEBUG

#if defined(IMAL_DEBUG)
int imalTraceKeepAlives = 0;
int imalTracePayload = 0;
#endif

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
Forward(KASOCKTRAN_Manager *ft, ITS_EVENT *ev, void *msg)
{
    MTP3_HEADER hdr;
    ITS_OCTET type;
    ITS_USHORT len;

    memcpy(ev, msg, sizeof(ITS_EVENT));

    if (MTP3_Decode(ev, &type, &hdr, msg, &len) != ITS_SUCCESS)
    {
        /* might as well bail, there's not much else we can do */
        return (ITS_SUCCESS);
    }

    if (type != MTP3_MSG_USER_DATA)
    {
        /* this should not happen... unless the user sends non-ss7 traffic */
        return (ITS_SUCCESS);
    }

    /* filter out SLTM (eventually SNMM as well for link state management). */
    switch (MTP3_HDR_GET_SIO(hdr) & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
        /*
         * note the transport source so we can reply on
         * the correct transport
         */
        ev->src = TRANSPORT_INSTANCE(ft);

#if defined(IMAL_DEBUG)
        if (imalTraceKeepAlives)
        {
            unsigned i;

            ITS_TRACE_DEBUG(("IMAL Received keepalive:\n"));
            ITS_TRACE_DEBUG(("  Src: %04x  Length: %04x\n",
                             ev->src, ev->len));
            ITS_TRACE_DEBUG(("  "));
            for (i = 0; i < ev->len; i++)
            {
                TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                          ("%02x ", ev->data[i]));

                if (!((i+1) % 25))
                {
                    TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                              ("\n  "));
                }
            }
            if ((i+1) % 25)
            {
                TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                          ("\n"));
            }
        }
#endif
        TRANSPORT_PutEvent(ITS_KEEPALIVE_INSTANCE, ev);

        return (ITS_ENOMSG);

    default:
#if defined(IMAL_DEBUG)
        if (imalTracePayload)
        {
            unsigned i;

            ITS_TRACE_DEBUG(("IMAL Received message:\n"));
            ITS_TRACE_DEBUG(("  Src: %04x  Length: %04x\n",
                            ev->src, ev->len));
            ITS_TRACE_DEBUG(("  "));
            for (i = 0; i < ev->len; i++)
            {
                TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                          ("%02x ", ev->data[i]));

                if (!((i+1) % 25))
                {
                    TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                              ("\n  "));
                }
            }
            if ((i+1) % 25)
            {
                TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                          ("\n"));
            }
        }
#endif
        break;
    }

    /*
     * we've read an ITS_EVENT.  Figure out if it is a SNMM or SLTM msg
     * and forward accordingly
     */
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
Convert(KASOCKTRAN_Manager *imal, ITS_EVENT *ev, void *msg)
{
    /*
     * we actually don't have to filter or translate here.  Everything is
     * automatically in the right format.
     */
	memcpy(msg, ev, sizeof(ITS_EVENT));

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
 *      algorithm:
 *
 *      1. SLTM is generated every T1 seconds
 *      2. SLTA must be received within 3 * T1 seconds.  No drops
 *      means SLTA must be received within T1 seconds.
 *      3. No generation or sequence number.  Underlying protocol
 *      should guarantee that.
 *      4. Since we are using SLTM/SLTA, acknowledgement cannot be
 *      "piggybacked" on a valid user data packet.  We want a
 *      standalone ack.
 *
 *      This routine should check to see if another SLTM should be
 *      generated.  It also needs to check if too much time has
 *      expired since an SLTA was received.
 *
 *      This routine is called from the context of the keepalive
 *      thread.
 *
 *  See Also:
 ****************************************************************************/
static void
CheckTime(KASOCKTRAN_Manager *kt)
{
    IMALTRAN_Manager *imal;
    ITS_TIME currentTime;

    currentTime = TIMERS_Time();

    imal = (IMALTRAN_Manager *)kt;

    if (!SOCKTRAN_IS_VALID(imal))
    {
        ITS_TRACE_DEBUG(("IMAL_KeepAliveTimerCheck: transport %04x "
                         "isn't valid right now.\n",
                         TRANSPORT_INSTANCE(kt)));

        return;
    }

    /* somebody been fucking with the clock? */
    if (currentTime < IMALTRAN_KA_START_TIME(imal) ||
        currentTime < IMALTRAN_KA_TRANSMIT_TIME(imal))
    {
        ITS_TRACE_DEBUG(("IMAL_KeepAliveTimerCheck: transport %04x: "
                         "some idiot time warped me into the past.\n",
                         TRANSPORT_INSTANCE(kt)));

        IMALTRAN_KA_START_TIME(imal) = currentTime;
        IMALTRAN_KA_TRANSMIT_TIME(imal) = currentTime;

        return;
    }

    /*
     * see if we've missed an ACK (remote is dead).
     */
    if (IMALTRAN_KA_REQ_PENDING(imal) &&
        (currentTime >
         (ITS_TIME)(IMALTRAN_KA_START_TIME(imal) +
                    (3U * IMALTRAN_KA_TIMEOUT(imal)))))
    {
        IMALTRAN_KA_REQ_PENDING(imal) = ITS_FALSE;

        SOCKTRAN_CLASS_SHUTDOWN(ITS_OBJ_CLASS(imal))
            ((SOCKTRAN_Manager *)imal);

#if defined(IMAL_DEBUG)
        if (imalTraceKeepAlives)
        {
            ITS_TRACE_WARNING(("***** IMAL shutdown on %04x due to timeout\n",
                               TRANSPORT_INSTANCE(imal)));
        }
#endif

        return;
    }

    /*
     * start (or refresh) a keepalive
     */
    if (currentTime >
        (ITS_TIME)(IMALTRAN_KA_TRANSMIT_TIME(imal) +
                   IMALTRAN_KA_TIMEOUT(imal)))
    {
        ITS_EVENT ev;
        SLTM_MESSAGE sltm;
        MTP3_HEADER mtp3;

        IMALTRAN_KA_TRANSMIT_TIME(imal) = currentTime;

        if (!IMALTRAN_KA_REQ_PENDING(imal))
        {
            IMALTRAN_KA_REQ_PENDING(imal) = ITS_TRUE;
            IMALTRAN_KA_START_TIME(imal) = currentTime;
        }

#if defined(IMAL_DEBUG)
        if (imalTraceKeepAlives)
        {
            ITS_TRACE_DEBUG(("Sending KeepAlive Request: to %04x\n",
                             TRANSPORT_INSTANCE(imal)));
        }
#endif

        ev.src = ITS_KEEPALIVE_INSTANCE;

        MTP3_HDR_SET_SIO(mtp3, MTP3_SIO_SLTM_REG);
        MTP3_RL_SET_OPC_VALUE(mtp3.label, IMALTRAN_KA_LOCAL_PC(imal));
        MTP3_RL_SET_DPC_VALUE(mtp3.label, IMALTRAN_KA_ADJACENT_PC(imal));

        SLTM_HC0_SET(sltm, SLTM_HC0_TST);
        SLTM_HC1_SET(sltm, SLTM_HC1_SLTM);
        SLTM_LINK_TEST_SET_SLC(sltm.data.linkTest, 0); /* FIXME */ 

        if (MUTEX_AcquireMutex(&IMALTRAN_KA_PATTERN_LOCK(imal)) != ITS_SUCCESS)
        {
            return;
        }

        SLTM_LINK_TEST_SET_LENGTH(sltm.data.linkTest,
                                  IMALTRAN_KA_SEND_PATTERN_LEN(imal));

        memcpy(sltm.data.linkTest.pattern,
               IMALTRAN_KA_SEND_PATTERN(imal),
               IMALTRAN_KA_SEND_PATTERN_LEN(imal));

        MUTEX_ReleaseMutex(&IMALTRAN_KA_PATTERN_LOCK(imal));

        SLTM_Encode(&ev, &mtp3, &sltm);

        TRANSPORT_PutEvent(TRANSPORT_INSTANCE(imal), &ev);
    }
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
CheckEvent(KASOCKTRAN_Manager *keepAliveSrc, ITS_EVENT *imalEvent)
{
    SLTM_MESSAGE sltm;
    MTP3_HEADER mtp3;
    ITS_EVENT ev;

    /*
     * if the transport isn't valid, discard it
     */
    if (!SOCKTRAN_IS_VALID(keepAliveSrc))
    {
        return;
    }

    /*
     * we've gotten either:
     * 1) an SLTM.  Build and send the SLTA.
     * 2) an SLTA.  Compare the data with local store.
     */
    if (SLTM_Decode(imalEvent, &mtp3, &sltm) != ITS_SUCCESS)
    {
        /* might as well bail, there's not much else we can do */
        return;
    }

    /* filter out SLTM (eventually SNMM as well for link state management). */
    switch (MTP3_HDR_GET_SIO(mtp3) & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
        if (SLTM_HC0_GET(sltm) == SLTM_HC0_TST)
        {
            /* send ack */
            if (SLTM_HC1_GET(sltm) == SLTM_HC1_SLTM)
            {
                ITS_UINT opc, dpc;

                MTP3_HDR_SET_SIO(mtp3, MTP3_SIO_SLTM_REG);
                opc = MTP3_RL_GET_OPC_VALUE(mtp3.label);
                dpc = MTP3_RL_GET_DPC_VALUE(mtp3.label);
                MTP3_RL_SET_OPC_VALUE(mtp3.label, dpc);
                MTP3_RL_SET_DPC_VALUE(mtp3.label, opc);

                SLTM_HC0_SET(sltm, SLTM_HC0_TST);
                SLTM_HC1_SET(sltm, SLTM_HC1_SLTA);

                SLTM_Encode(&ev, &mtp3, &sltm);

#if defined(IMAL_DEBUG)
                if (imalTraceKeepAlives)
                {
                    ITS_TRACE_DEBUG(("Sending keepalive response\n"));
                }
#endif
                TRANSPORT_PutEvent(imalEvent->src, &ev);

                if (MUTEX_AcquireMutex(&IMALTRAN_KA_PATTERN_LOCK(keepAliveSrc)) !=
                    ITS_SUCCESS)
                {
                    ITS_TRACE_CRITICAL(("IMAL: Can't acquire gate checking "
                                        "pattern!\n"));

                    return;
                }

                memcpy(IMALTRAN_KA_RECV_PATTERN(keepAliveSrc),
                       sltm.data.linkTest.pattern,
                       SLTM_LINK_TEST_GET_LENGTH(sltm.data.linkTest));
                IMALTRAN_KA_RECV_PATTERN_LEN(keepAliveSrc) =
                    SLTM_LINK_TEST_GET_LENGTH(sltm.data.linkTest);

                MUTEX_ReleaseMutex(&IMALTRAN_KA_PATTERN_LOCK(keepAliveSrc));
            }
            else if (SLTM_HC1_GET(sltm) == SLTM_HC1_SLTA)
            {
                /*
                 * we don't do this yet
                 * SLTM_LINK_TEST_SET_SLC(sltm.data.linkTest) == localValue;
                 * FIXME
                 */
                if (MUTEX_AcquireMutex(&IMALTRAN_KA_PATTERN_LOCK(keepAliveSrc)) !=
                    ITS_SUCCESS)
                {
                    ITS_TRACE_CRITICAL(("IMAL: Can't acquire gate checking "
                                        "pattern!\n"));

                    return;
                }

                if (SLTM_LINK_TEST_GET_LENGTH(sltm.data.linkTest) !=
                    IMALTRAN_KA_SEND_PATTERN_LEN(keepAliveSrc) ||
                    memcmp(sltm.data.linkTest.pattern,
                           IMALTRAN_KA_SEND_PATTERN(keepAliveSrc),
                           IMALTRAN_KA_SEND_PATTERN_LEN(keepAliveSrc)) != 0)
                {
                    ITS_TRACE_CRITICAL(("IMAL: SLTA pattern mismatch!\n"));

                    ITS_TRACE_CRITICAL(("transport: %04x "
                                        "pattern len %d rcv len %d\n",
                                        imalEvent->src,
                                        IMALTRAN_KA_SEND_PATTERN_LEN(keepAliveSrc),
                                        SLTM_LINK_TEST_GET_LENGTH(sltm.data.linkTest)));

                    ITS_TRACE_CRITICAL(("pattern: %08x %08x %08x %08x\n",
                                        (sltm.data.linkTest.pattern[0] << 24) |
                                        (sltm.data.linkTest.pattern[1] << 16) |
                                        (sltm.data.linkTest.pattern[2] << 8) |
                                        sltm.data.linkTest.pattern[3],
                                        (sltm.data.linkTest.pattern[4] << 24) |
                                        (sltm.data.linkTest.pattern[5] << 16) |
                                        (sltm.data.linkTest.pattern[6] << 8) |
                                        sltm.data.linkTest.pattern[7],
                                        (sltm.data.linkTest.pattern[8] << 24) |
                                        (sltm.data.linkTest.pattern[9] << 16) |
                                        (sltm.data.linkTest.pattern[10] << 8) |
                                        sltm.data.linkTest.pattern[11],
                                        (sltm.data.linkTest.pattern[12] << 24) |
                                        (sltm.data.linkTest.pattern[13] << 16) |
                                        (sltm.data.linkTest.pattern[14] << 8) |
                                        sltm.data.linkTest.pattern[15]));

                    IMALTRAN_KA_MISMATCH_COUNT(keepAliveSrc)++;

                    if (IMALTRAN_KA_MISMATCH_COUNT(keepAliveSrc) > 3)
                    {
                        /* shutdown */
                    }
                }
                else
                {
                    IMALTRAN_KA_MISMATCH_COUNT(keepAliveSrc) = 0;

                    IMALTRAN_KA_REQ_PENDING(keepAliveSrc) = ITS_FALSE;
                }

                MUTEX_ReleaseMutex(&IMALTRAN_KA_PATTERN_LOCK(keepAliveSrc));
            }
        }
        break;

    default:
        return;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the IMAL class record (aka the IMAL subsystem).
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
    static RESFILE_Manager *globalRes = NULL;
    static char value[ITS_PATH_MAX];
    const char *name = APPL_GetConfigFileName();

    globalRes = RESFILE_CreateResourceManager(name);

    if (globalRes)
    {
        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  IMAL_TRACE_KEEPALIVES_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            imalTraceKeepAlives = atoi(value);
        }

        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  IMAL_TRACE_PAYLOAD_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            imalTracePayload = atoi(value);
        }
    }

    KASOCKTRAN_CLASS_CHECK_TIME(itsIMALTRAN_ClientClass) = CheckTime;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsIMALTRAN_ClientClass) = CheckEvent;
    KASOCKTRAN_CLASS_DECODE(itsIMALTRAN_ClientClass) = Forward;
    KASOCKTRAN_CLASS_ENCODE(itsIMALTRAN_ClientClass) = Convert;
    ITS_CLASS_EXTENSION(itsIMALTRAN_ClientClass) =
        ITS_CLASS_EXTENSION(ITS_CLASS_SUPERCLASS(itsIMALTRAN_ClientClass));

    KASOCKTRAN_CLASS_CHECK_TIME(itsIMALTRAN_ServerClass) = CheckTime;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsIMALTRAN_ServerClass) = CheckEvent;
    KASOCKTRAN_CLASS_DECODE(itsIMALTRAN_ServerClass) = Forward;
    KASOCKTRAN_CLASS_ENCODE(itsIMALTRAN_ServerClass) = Convert;
    ITS_CLASS_EXTENSION(itsIMALTRAN_ServerClass) =
        ITS_CLASS_EXTENSION(ITS_CLASS_SUPERCLASS(itsIMALTRAN_ServerClass));

    KASOCKTRAN_CLASS_CHECK_TIME(itsIMALTRAN_DynamicServerClass) = CheckTime;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsIMALTRAN_DynamicServerClass) = CheckEvent;
    KASOCKTRAN_CLASS_DECODE(itsIMALTRAN_DynamicServerClass) = Forward;
    KASOCKTRAN_CLASS_ENCODE(itsIMALTRAN_DynamicServerClass) = Convert;
    ITS_CLASS_EXTENSION(itsIMALTRAN_DynamicServerClass) =
        ITS_CLASS_EXTENSION(ITS_CLASS_SUPERCLASS(itsIMALTRAN_DynamicServerClass));

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the IMAL class record (aka terminate the IMAL subsystem).
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
    KASOCKTRAN_CLASS_CHECK_TIME(itsIMALTRAN_ClientClass) = NULL;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsIMALTRAN_ClientClass) = NULL;
    KASOCKTRAN_CLASS_DECODE(itsIMALTRAN_ClientClass) = NULL;
    KASOCKTRAN_CLASS_ENCODE(itsIMALTRAN_ClientClass) = NULL;
    ITS_CLASS_EXTENSION(itsIMALTRAN_ClientClass) = NULL;

    KASOCKTRAN_CLASS_CHECK_TIME(itsIMALTRAN_ServerClass) = NULL;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsIMALTRAN_ServerClass) = NULL;
    KASOCKTRAN_CLASS_DECODE(itsIMALTRAN_ServerClass) = NULL;
    KASOCKTRAN_CLASS_ENCODE(itsIMALTRAN_ServerClass) = NULL;
    ITS_CLASS_EXTENSION(itsIMALTRAN_ServerClass) = NULL;

    KASOCKTRAN_CLASS_CHECK_TIME(itsIMALTRAN_DynamicServerClass) = NULL;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsIMALTRAN_DynamicServerClass) = NULL;
    KASOCKTRAN_CLASS_DECODE(itsIMALTRAN_DynamicServerClass) = NULL;
    KASOCKTRAN_CLASS_ENCODE(itsIMALTRAN_DynamicServerClass) = NULL;
    ITS_CLASS_EXTENSION(itsIMALTRAN_DynamicServerClass) = NULL;
}

IMALDLLAPI ITS_ClassRec itsIMAL_ClassRec =
{
    /* core */
    {
        NULL,
        0,
        ITS_FALSE,
        0,
        "IMAL",
        Init,
        Term,
        NULL,
        NULL,
        NULL
    }
};

IMALDLLAPI ITS_Class itsIMAL_Class = &itsIMAL_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the SLTM test pattern.
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
IMALDLLAPI int
IMALTRAN_SetSendPattern(IMALTRAN_Manager *mgr,
                        ITS_OCTET *pattern, ITS_USHORT len)
{
    if (MUTEX_AcquireMutex(&IMALTRAN_KA_PATTERN_LOCK(mgr)) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if (len > SLTM_MAX_SIZE)
    {
        MUTEX_ReleaseMutex(&IMALTRAN_KA_PATTERN_LOCK(mgr));

        return (ITS_EOVERFLOW);
    }

    memcpy(IMALTRAN_KA_SEND_PATTERN(mgr), pattern, len);
    IMALTRAN_KA_SEND_PATTERN_LEN(mgr) = len;

    MUTEX_ReleaseMutex(&IMALTRAN_KA_PATTERN_LOCK(mgr));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get the SLTM test pattern.
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
IMALDLLAPI int
IMALTRAN_GetSendPattern(IMALTRAN_Manager *mgr,
                        ITS_OCTET *pattern, ITS_USHORT *len)
{
    if (MUTEX_AcquireMutex(&IMALTRAN_KA_PATTERN_LOCK(mgr)) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    memcpy(pattern,
           IMALTRAN_KA_SEND_PATTERN(mgr),
           IMALTRAN_KA_SEND_PATTERN_LEN(mgr));
    *len = IMALTRAN_KA_SEND_PATTERN_LEN(mgr);

    MUTEX_ReleaseMutex(&IMALTRAN_KA_PATTERN_LOCK(mgr));

    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get the SLTA test pattern.
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
IMALDLLAPI int
IMALTRAN_GetRecvPattern(IMALTRAN_Manager *mgr,
                        ITS_OCTET *pattern, ITS_USHORT *len)
{
    if (MUTEX_AcquireMutex(&IMALTRAN_KA_PATTERN_LOCK(mgr)) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    memcpy(pattern,
           IMALTRAN_KA_RECV_PATTERN(mgr),
           IMALTRAN_KA_RECV_PATTERN_LEN(mgr));
    *len = IMALTRAN_KA_RECV_PATTERN_LEN(mgr);

    MUTEX_ReleaseMutex(&IMALTRAN_KA_PATTERN_LOCK(mgr));

    return (ITS_SUCCESS);
}
