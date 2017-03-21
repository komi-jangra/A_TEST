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
 *                  
 * CONTRACT: INTERNAL
 *      
 * ID: $Id: m2pa.c,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:45  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:16  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2002/01/15 23:04:56  mmiers
 * LOG: Add CRC32C.  Update M2PA as far as I can without SCTP support.
 * LOG:
 * LOG: Revision 5.2  2002/01/10 16:51:35  mmiers
 * LOG: Finish the transport refcounting effort.  Move vframe from
 * LOG: vendors to here.
 * LOG:
 * LOG: Revision 5.1  2002/01/09 21:23:38  mmiers
 * LOG: Add M2PA file, update ignore lists.
 * LOG:
 *                 
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include <its.h>
#include <its_link.h>
#include <its_assertion.h>
#include <its_trace.h>
#include <its_tq_trans.h>
#include <its_timers.h>

#include <m2pa_msgs.h>
#include <m2pa.h>

#include <mtp2_cmn.h>

#if defined(ANSI)
#include <ansi/mtp3.h>
#elif defined(CCITT)
#include <itu/mtp3.h>
#endif

/*
 * we subclass from the SCTP transport.  We need to do some extra work
 * as M2PA needs to track state itself.  To do this properly, M2PA needs
 * to be implemented as a vendor library.
 *
 * Design decisions:
 * 1) Remote EndPoints will represent links.  Each remote transport will
 * need an associated link data structure.  This is because each remote
 * transport represents an event sink.
 * 2) The VENDOR_Instance will be associated with the Local EndPoint.
 * This is because regardless of the multiplexing decision, each local
 * transport represents an event source.
 */

/*
 * configuration items:
 *  T1 - 1 - 60 seconds, default 10
 *  T2 - Normal - Range: 1-60 seconds             Default: 10 seconds
 *       Emergency - Range: 400-600 milliseconds  Default: 500 ms
 *  T3 - 1 - 60 seconds, default 10
 *  Status_Interval - implementation dependent
 *  Proving_Data_Rate - implementation dependent
 *  T6 - 1 - 6 seconds
 */

/*
 * local variables
 */
static ITS_HANDLE m2paHandle = NULL;
static ITS_THREAD m2paThread;

static int  m2paT1 = 10;
static int  m2paT2 = 10000;
static int  m2paT2Emerg = 500;
static int  m2paT3 = 10;
static int  m2paT6 = 3;
static int  m2paPD = 1;
static int  m2paLS = 1;

#define NUM_PROVES          5
#define PROVING_DATA_LEN    20
#define MAX_PD_MISS         15

static ITS_OCTET provingData[NUM_PROVES][PROVING_DATA_LEN] =
{
    { 0x00, 0xff, 0x43, 0x37, 0x69, 0x22, 0xad, 0x53, 0xca,
      0x13, 0x96, 0x73, 0xc5, 0xb7, 0x4b, 0xe9, 0xd1, 0x85 },
    { 0x01, 0x96, 0x73, 0xc5, 0xb7, 0x4b, 0xe9, 0xd1, 0x85,
      0x43, 0xff, 0x13, 0x37, 0x69, 0x22, 0xad, 0x53, 0xca },   
    { 0x02, 0xe3, 0x11, 0xa3, 0x55, 0x9e, 0x3b, 0xf3, 0x4f,
      0x75, 0xb2, 0x57, 0xd1, 0x63, 0xe4, 0x2c, 0xe4, 0xa3 },
    { 0x03, 0xb2, 0x57, 0xd1, 0x63, 0xe4, 0x2c, 0xe4, 0xa3,
      0x75, 0xe3, 0x11, 0xa3, 0x55, 0x9e, 0x3b, 0xf3, 0x4f },
    { 0x04, 0xe3, 0x11, 0xa3, 0x55, 0x9e, 0x3b, 0xf3, 0x4f,
      0x13, 0x96, 0x73, 0xc5, 0xb7, 0x4b, 0xe9, 0xd1, 0x85 }
};

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Encode a message as an M2PA message.  Called by WriteEvent.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
static void
M2PA_StateMachine(SCTPTRAN_Manager *sctp, M2PA_Trigger trigger)
{
    M2PA_TimerContext tc;

    /*
     * decide the transition based on the current state.
     */
    switch (SCTPTRAN_STATE(sctp))
    {
    case M2PA_STATE_IDLE:
        SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ALIGN_SENT;
        SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ALIGN_RCVD;
        SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_READY;

        if (trigger == M2PA_TRIGGER_COMM_UP)
        {
            SCTPTRAN_FLAGS(sctp) |= SCTPTRAN_FLAG_ASSOC_UP;

            SCTPTRAN_STATE(sctp) = M2PA_STATE_OOS;
        }
        else
        {
            ITS_TRACE_DEBUG(("Ignoring trigger %d in IDLE state\n",
                             trigger));
        }
        break;

    case M2PA_STATE_OOS:
        SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ALIGN_SENT;
        SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ALIGN_RCVD;
        SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_READY;

        /* if MTP3 starts us, go to align in progress */
        if (trigger == M2PA_TRIGGER_LINK_START)
        {
            if (!(SCTPTRAN_FLAGS(sctp) & SCTPTRAN_FLAG_ALIGN_SENT))
            {
                /* alignment will start in the calling function */
            }

            SCTPTRAN_STATE(sctp) = M2PA_STATE_AIP;
        }
        /* if the assoc dropped, go back to IDLE */
        else if (trigger == M2PA_TRIGGER_COMM_DOWN)
        {
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ASSOC_UP;

            /* FIXME: start restart */

            SCTPTRAN_STATE(sctp) = M2PA_STATE_IDLE;
        }
        /* if the assoc restarted, ignore at this point */
        else if (trigger == M2PA_TRIGGER_COMM_RESTART)
        {
            ITS_TRACE_DEBUG(("Assoc restarted in OOS state\n"));
        }
        else
        {
            ITS_TRACE_DEBUG(("Ignoring trigger %d in OOS\n",
                             trigger));
        }
        break;

    case M2PA_STATE_AIP:
        /* if MTP2 stops us, we can't do a whole lot */
        if (trigger == M2PA_TRIGGER_LINK_STOP)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_OOS;
        }
        /* if any of the error conditions trigger, go back to OOS */
        else if (trigger == M2PA_TRIGGER_COMM_DOWN)
        {
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ASSOC_UP;

            /* FIXME: start restart */

            SCTPTRAN_STATE(sctp) = M2PA_STATE_IDLE;
        }
        else if (trigger == M2PA_TRIGGER_COMM_ERROR ||
                 trigger == M2PA_TRIGGER_COMM_RESTART)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_IDLE;
        }
        /* if we time out, just go to OOS (don't restart assoc) */
        else if (trigger == M2PA_TRIGGER_T1_EXPIRY)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_OOS;
        }
        /* if we get alignment or proving go to proving */
        else if (trigger == M2PA_TRIGGER_ALIGNMENT ||
                 trigger == M2PA_TRIGGER_PROVING)
        {
            /* stop T1 */
            TIMERS_CancelTimer(SCTPTRAN_T1(sctp));

            /* start T2 */
            tc.trigger = M2PA_TRIGGER_T2_EXPIRY;
            tc.transport = TRANSPORT_INSTANCE(sctp);

            SCTPTRAN_T2(sctp) = TIMERS_StartUTimer(M2PA_MANAGER_INSTANCE,
                                                   m2paT2 * USEC_PER_MILLISEC,
                                                   &tc, sizeof(M2PA_TimerContext));

            SCTPTRAN_STATE(sctp) = M2PA_STATE_PROVING;
        }
        else
        {
            ITS_TRACE_DEBUG(("Ignoring trigger %d in AIP\n",
                             trigger));
        }
        break;

    case M2PA_STATE_PROVING:
        /* if MTP2 stops us, we can't do a whole lot */
        if (trigger == M2PA_TRIGGER_LINK_STOP)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_OOS;
        }
        /* if any of the error conditions trigger, go back to OOS */
        else if (trigger == M2PA_TRIGGER_COMM_DOWN)
        {
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ASSOC_UP;

            /* FIXME: start restart */

            SCTPTRAN_STATE(sctp) = M2PA_STATE_IDLE;
        }
        else if (trigger == M2PA_TRIGGER_COMM_ERROR ||
                 trigger == M2PA_TRIGGER_COMM_RESTART)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_IDLE;
        }
        /* if T2 expiry goto aligned ready */
        else if (trigger == M2PA_TRIGGER_T2_EXPIRY)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_ALIGNED_READY;
        }
        else
        {
            ITS_TRACE_DEBUG(("Ignoring trigger %d in PROVING\n",
                             trigger));
        }
        break;

    case M2PA_STATE_ALIGNED_READY:
        /* if MTP2 stops us, we can't do a whole lot */
        if (trigger == M2PA_TRIGGER_LINK_STOP)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_OOS;
        }
        /* if any of the error conditions trigger, go back to OOS */
        else if (trigger == M2PA_TRIGGER_COMM_DOWN)
        {
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ASSOC_UP;

            /* FIXME: start restart */

            SCTPTRAN_STATE(sctp) = M2PA_STATE_IDLE;
        }
        else if (trigger == M2PA_TRIGGER_COMM_ERROR ||
                 trigger == M2PA_TRIGGER_COMM_RESTART)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_IDLE;
        }
        /* if we time out, go to OOS (don't restart assoc) */
        else if (trigger == M2PA_TRIGGER_T3_EXPIRY)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_OOS;
        }
        else if (trigger == M2PA_TRIGGER_PROVING_COMPLETE ||
                 trigger == M2PA_TRIGGER_USER_DATA)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_INS;
        }
        else
        {
            ITS_TRACE_DEBUG(("Ignoring trigger %d in ALIGNED_READY\n",
                             trigger));
        }
        break;

    case M2PA_STATE_INS:
        /* fast path: ignore data */
        if (trigger == M2PA_TRIGGER_USER_DATA)
        {
        }
        /* if MTP2 stops us get ready for retrieval */
        else if (trigger == M2PA_TRIGGER_LINK_STOP)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_RETRIEVAL;
        }
        /* if any of the error conditions trigger, start retrieval */
        else if (trigger == M2PA_TRIGGER_COMM_DOWN)
        {
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ASSOC_UP;
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ALIGN_SENT;
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ALIGN_RCVD;

            /* FIXME: start restart */

            SCTPTRAN_STATE(sctp) = M2PA_STATE_RETRIEVAL;
        }
        else if (trigger == M2PA_TRIGGER_COMM_ERROR ||
                 trigger == M2PA_TRIGGER_COMM_RESTART)
        {
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ALIGN_SENT;
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ALIGN_RCVD;

            SCTPTRAN_STATE(sctp) = M2PA_STATE_RETRIEVAL;
        }
        /* if we time out, go to OOS (don't restart assoc) */
        else if (trigger == M2PA_TRIGGER_T6_EXPIRY)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_RETRIEVAL;
        }
        else
        {
            ITS_TRACE_DEBUG(("Ignoring trigger %d in INS\n",
                             trigger));
        }
        break;

    case M2PA_STATE_RETRIEVAL:
        /* if retrieval complete, go to OOS */
        if (trigger == M2PA_TRIGGER_RETRIEVAL_COMPLETE)
        {
            if (SCTPTRAN_FLAGS(sctp) & SCTPTRAN_FLAG_ASSOC_UP)
            {
                SCTPTRAN_STATE(sctp) = M2PA_STATE_OOS;
            }
            else
            {
                SCTPTRAN_STATE(sctp) = M2PA_STATE_IDLE;
            }
        }
        /* if assoc error, stay in state */
        else if (trigger == M2PA_TRIGGER_COMM_DOWN)
        {
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ASSOC_UP;
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ALIGN_SENT;
            SCTPTRAN_FLAGS(sctp) &= ~SCTPTRAN_FLAG_ALIGN_RCVD;

            /* FIXME: start restart */

            SCTPTRAN_STATE(sctp) = M2PA_STATE_RETRIEVAL;
        }
        else if (trigger == M2PA_TRIGGER_COMM_ERROR ||
                 trigger == M2PA_TRIGGER_COMM_RESTART)
        {
            SCTPTRAN_STATE(sctp) = M2PA_STATE_RETRIEVAL;
        }
        /* if MTP3 restarts now, bail out */
        else if (trigger == M2PA_TRIGGER_LINK_START)
        {
            if (SCTPTRAN_FLAGS(sctp) & SCTPTRAN_FLAG_ASSOC_UP)
            {
                if (!(SCTPTRAN_FLAGS(sctp) & SCTPTRAN_FLAG_ALIGN_SENT))
                {
                    /* alignment will start in the calling function */
                }

                SCTPTRAN_STATE(sctp) = M2PA_STATE_AIP;
            }
            else
            {
                SCTPTRAN_STATE(sctp) = M2PA_STATE_IDLE;
            }
        }
        else
        {
            ITS_TRACE_DEBUG(("Ignoring trigger %d in RETRIEVAL\n",
                             trigger));
        }
        break;

    default:
        ITS_TRACE_DEBUG(("Invalid state %d\n", SCTPTRAN_STATE(sctp)));
        break;
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Encode a message as an M2PA message.  Called by WriteEvent.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
VSS7DLLAPI int
M2PA_Encode(SCTPTRAN_ManagerPtr m, ITS_EVENT *ev,
            ITS_BOOLEAN *isManagement, ITS_OCTET *sls)
{
    M2PA_MSG *msg;
    M2PA_TimerContext tc;
    ITS_EVENT rsp;
    int mlen;
    SS7_LinkPtr ln;
    ITS_USHORT ssn;

    ln = TRANSPORT_SS7_INFO(m).linkInfo;
    ITS_C_ASSERT(ln != NULL);

    /* handle messages */
    /* note that self generated messages are going to pass through here as well. */
    switch (L2_MSG_TYPE(ev))
    {
    case M2PA_VERSION_1:
        /* these are self generated messages.  We need to be SURE they are MTP3 */
        /* just pass them through on stream zero. */
        *sls = 0;
        return (ITS_SUCCESS);

    case L3_L2_START:
        /* run the state machine */
        M2PA_StateMachine(m, M2PA_TRIGGER_LINK_START);
        /* send alignment message if appropriate */
        if (SCTPTRAN_FLAGS(m) & SCTPTRAN_FLAG_ASSOC_UP)
        {
            mlen = sizeof(UA_HDR) + sizeof(M2PA_LINK_STATUS_MSG);
            msg = ITS_Malloc(mlen);
            if (msg == NULL)
            {
                return (ITS_ENOMEM);
            }
            /* initialize it */
            msg->hdr.version = M2PA_VERSION_1;
            msg->hdr.spare = 0;
            msg->hdr.msgClass = M2PA_MSG_CLASS;
            msg->hdr.msgType = M2PA_MSG_LINK_STATUS;
            msg->hdr.msgLength = SOCK_HToNL(mlen);
            msg->body.linkStatus.status = SOCK_HToNL(M2PA_LS_ALIGNMENT);
            ITS_Free(ev->data);
            ev->data = (ITS_OCTET *)msg;

            SCTPTRAN_FLAGS(m) |= SCTPTRAN_FLAG_ALIGN_SENT;

            if (!(SCTPTRAN_FLAGS(m) & SCTPTRAN_FLAG_ALIGN_RCVD))
            {
                /* start T1 */
                tc.trigger = M2PA_TRIGGER_T1_EXPIRY;
                tc.transport = TRANSPORT_INSTANCE(m);

                SCTPTRAN_T1(m) = TIMERS_StartTimer(M2PA_MANAGER_INSTANCE, m2paT1,
                                                   &tc, sizeof(M2PA_TimerContext));
            }

            return (ITS_SUCCESS);
        }
        /* status goes on stream 0 */
        *sls = 0;
        /* make sure SCTP doesn't transmit */
        return (ITS_ENOMSG);

    case L3_L2_STOP:
        M2PA_StateMachine(m, M2PA_TRIGGER_LINK_STOP);
        /* make sure SCTP doesn't transmit */
        return (ITS_ENOMSG);

    case L3_L2_RESUME:
        return (ITS_ENOMSG);

    case L3_L2_CLEAR_BUFFERS:
        /* FIXME: Clear buffers as required */
        /*  Send L2_L3_RB_CLEARED to MTP3 */
        ITS_EVENT_INIT(&rsp, TRANSPORT_INSTANCE(m), 3 * sizeof(ITS_OCTET));
        L2_MSG_TYPE(&rsp) = L2_L3_RB_CLEARED;
        L2_LINK_SET(&rsp) = ln->linkSet->linkSet;
        L2_LINK_CODE(&rsp) = ln->linkCode;
        TRANSPORT_PutEvent(ITS_MTP3_SRC, &rsp);
        /* make sure SCTP doesn't transmit */
        return (ITS_ENOMSG);

    case L3_L2_CLEAR_RTB:
        /* FIXME: Clear buffers as required */
        /* Send L2_L3_RTB_CLEARED to MTP3 */
        ITS_EVENT_INIT(&rsp, TRANSPORT_INSTANCE(m), 3 * sizeof(ITS_OCTET));
        L2_MSG_TYPE(&rsp) = L2_L3_RTB_CLEARED;
        L2_LINK_SET(&rsp) = ln->linkSet->linkSet;
        L2_LINK_CODE(&rsp) = ln->linkCode;
        TRANSPORT_PutEvent(ITS_MTP3_SRC, &rsp);
        /* make sure SCTP doesn't transmit */
        return (ITS_ENOMSG);

    case L3_L2_EMERGENCY:
        /* set emergency */
        SCTPTRAN_FLAGS(m) |= SCTPTRAN_FLAG_EMERG;
        return (ITS_ENOMSG);

    case L3_L2_EMERGENCY_CEASE:
        /* clear emergency */
        SCTPTRAN_FLAGS(m) &= ~SCTPTRAN_FLAG_EMERG;
        return (ITS_ENOMSG);

    case L3_L2_DATA:
        /* sanity check */
        ITS_C_ASSERT(ev->len > 3 * sizeof(ITS_OCTET));
        if (SCTPTRAN_FLAGS(m) & SCTPTRAN_FLAG_ASSOC_UP)
        {
            /* allocate the message body data.  Dump the link set/code bytes */
            msg = ITS_Malloc(sizeof(UA_HDR) + ev->len - 2 * sizeof(ITS_OCTET));
            if (msg == NULL)
            {
                return (ITS_ENOMEM);
            }
            mlen = ev->len - 3 * sizeof(ITS_OCTET);
            /* initialize it */
            msg->hdr.version = M2PA_VERSION_1;
            msg->hdr.spare = 0;
            msg->hdr.msgClass = M2PA_MSG_CLASS;
            msg->hdr.msgType = M2PA_MSG_USER_DATA;
            msg->hdr.msgLength = SOCK_HToNL(sizeof(UA_HDR) + ev->len -
                                            2 * sizeof(ITS_OCTET));
            /* copy the data.  Note that the li is always zero for us */
            msg->body.userData.li = 0;
            if (mlen)
            {
                memcpy(msg->body.userData.data, L2_LINK_DATA(ev) + 1, mlen);
            }
            ev->len = sizeof(UA_HDR) + sizeof(ITS_OCTET) + mlen;
            /* ditch the old data */
            ITS_Free(ev->data);
            ev->data = (ITS_OCTET *)msg;
            /* data goes on stream 1 */
            *sls = 1;
            return (ITS_SUCCESS);
        }
        return (ITS_ESENDFAIL);

    case L3_L2_RETRIEVE_BSNT:
        /* FIXME: fetch SSN */
        ITS_EVENT_INIT(&rsp, TRANSPORT_INSTANCE(m), 5 * sizeof(ITS_OCTET));
        /* FIXME: Under what circumstances? L2_L3_BSNT_NOT_RETRIEVABLE */
        L2_MSG_TYPE(&rsp) = L2_L3_BSNT;
        L2_LINK_SET(&rsp) = ln->linkSet->linkSet;
        L2_LINK_CODE(&rsp) = ln->linkCode;
        L2_LINK_DATA(&rsp)[0] = (ssn >> 8) & 0xFF;
        L2_LINK_DATA(&rsp)[0] = ssn & 0xFF;
        TRANSPORT_PutEvent(ITS_MTP3_SRC, &rsp);
        return (ITS_ENOMSG);

    case L3_L2_RETRIEVE_MSGS:
        /*
         * FIXME: send to MTP3:
         *  L2_L3_RETRIEVED_MSG
         *  L2_L3_RETRIEVAL_COMPLETE
         *  L2_L3_RETRIEVAL_NOT_POSSIBLE
         * as appropriate
         */
        ITS_EVENT_INIT(&rsp, TRANSPORT_INSTANCE(m), 3 * sizeof(ITS_OCTET));
        L2_MSG_TYPE(&rsp) = L2_L3_RETRIEVAL_COMPLETE;
        L2_LINK_SET(&rsp) = ln->linkSet->linkSet;
        L2_LINK_CODE(&rsp) = ln->linkCode;
        TRANSPORT_PutEvent(ITS_MTP3_SRC, &rsp);
        return (ITS_ENOMSG);

    case L3_L2_FLOW_CONTROL_START:
    case L3_L2_FLOW_CONTROL_STOP:
        return (ITS_ENOMSG);

    case L3_L2_LOCAL_PROCESSOR_OUT:
        SCTPTRAN_FLAGS(m) |= SCTPTRAN_FLAG_LPO;
        return (ITS_ENOMSG);

    case L3_L2_LOCAL_PROCESSOR_REC:
        SCTPTRAN_FLAGS(m) &= ~SCTPTRAN_FLAG_LPO;
        return (ITS_ENOMSG);

    default:
        ITS_TRACE_ERROR(("Unknown L3 msg type %d\n", L2_MSG_TYPE(ev)));
        return (ITS_ENOMSG);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Decode a message as an M2PA message.  Called by ReadEvent.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
VSS7DLLAPI int
M2PA_Decode(SCTPTRAN_ManagerPtr m, ITS_EVENT *ev,
            ITS_BOOLEAN *isManagement, ITS_OCTET *sls)
{
    M2PA_MSG *msg;
    TRANSPORT_Control *t;
    ITS_UINT status;
    SS7_LinkPtr ln;
    M2PA_TimerContext tc;
    ITS_OCTET *tmp;
    ITS_UINT pdIdx;
    ITS_UINT pdm;

    /* M2PA has none */
    *isManagement = ITS_FALSE;

    /* sanity */
    ITS_C_ASSERT(ev->len > sizeof(UA_HDR));

    /* get the data */
    msg = (M2PA_MSG *)ev->data;
    
    /* is it for us */
    if (msg->hdr.msgClass != M2PA_MSG_CLASS)
    {
        return (ITS_ENOMSG);
    }

    /* find the remote associated with this message */
    t = TRANSPORT_FindTransport(ev->src);
    if (t == NULL)
    {
        return (ITS_ENOTRANSPORT);
    }

    /* find the link info */
    ln = TRANSPORT_SS7_INFO(t).linkInfo;
    ITS_C_ASSERT(ln != NULL);

    /* decide what to do with it */
    switch (msg->hdr.msgType)
    {
    case M2PA_MSG_USER_DATA:
        /* Send L2_L3_DATA to MTP3 */
        tmp = ev->data;
        ev->data = ITS_Malloc(msg->hdr.msgLength - 1 + 3 * sizeof(ITS_OCTET));
        L2_MSG_TYPE(ev) = L2_L3_DATA;
        L2_LINK_SET(ev) = ln->linkSet->linkSet;
        L2_LINK_CODE(ev) = ln->linkCode;
        memcpy(L2_LINK_DATA(ev), msg->body.userData.data, msg->hdr.msgLength - 1);
        ITS_Free(tmp);
        break;

    case M2PA_MSG_LINK_STATUS:
        status = SOCK_NToHL(msg->body.linkStatus.status);
        switch (status)
        {
        case M2PA_LS_ALIGNMENT:
            SCTPTRAN_FLAGS(t) |= SCTPTRAN_FLAG_ALIGN_RCVD;
            if (SCTPTRAN_FLAGS(t) & SCTPTRAN_FLAG_ALIGN_SENT)
            {
                M2PA_StateMachine(m, M2PA_TRIGGER_ALIGNMENT);

                TRANSPORT_UnfindTransport(t);

                return (ITS_ENOMSG);
            }
            break;

        case M2PA_LS_PROVING_NORMAL:
            SCTPTRAN_FLAGS(t) |= SCTPTRAN_FLAG_ALIGN_RCVD;

            M2PA_StateMachine(m, M2PA_TRIGGER_PROVING);

            TRANSPORT_UnfindTransport(t);
            return (ITS_ENOMSG);

        case M2PA_LS_PROVING_EMERG:
            if (!(SCTPTRAN_FLAGS(t) & SCTPTRAN_FLAG_EMERG))
            {
                /* stop T2, start T2 with emergency interval */
                TIMERS_CancelTimer(SCTPTRAN_T2(t));

                tc.trigger = M2PA_TRIGGER_T2_EXPIRY;
                tc.transport = TRANSPORT_INSTANCE(t);

                SCTPTRAN_T2(t) = TIMERS_StartUTimer(M2PA_MANAGER_INSTANCE,
                                                    m2paT2Emerg * USEC_PER_MILLISEC,
                                                    &tc, sizeof(M2PA_TimerContext));
            }
            SCTPTRAN_FLAGS(t) |= SCTPTRAN_FLAG_EMERG;

            M2PA_StateMachine(m, M2PA_TRIGGER_PROVING);

            TRANSPORT_UnfindTransport(t);

            return (ITS_ENOMSG);

        case M2PA_LS_READY:
            /* Stop T3 */
            TIMERS_CancelTimer(SCTPTRAN_T3(t));

            SCTPTRAN_FLAGS(t) |= SCTPTRAN_FLAG_READY;

            /* Send L2_L3_IN_SERVICE to MTP3 */
            tmp = ev->data;
            ev->data = ITS_Malloc(3 * sizeof(ITS_OCTET));
            L2_MSG_TYPE(ev) = L2_L3_IN_SERVICE;
            L2_LINK_SET(ev) = ln->linkSet->linkSet;
            L2_LINK_CODE(ev) = ln->linkCode;
            ITS_Free(tmp);
            break;

        case M2PA_LS_PROCESSOR_OUT:
            /*
             * Send L2_L3_REMOTE_PROCESSOR_OUT to MTP3
             * if state > OOS
             */
            if (SCTPTRAN_STATE(t) > M2PA_STATE_OOS)
            {
                tmp = ev->data;
                ev->data = ITS_Malloc(3 * sizeof(ITS_OCTET));
                L2_MSG_TYPE(ev) = L2_L3_REMOTE_PROCESSOR_OUT;
                L2_LINK_SET(ev) = ln->linkSet->linkSet;
                L2_LINK_CODE(ev) = ln->linkCode;
                ITS_Free(tmp);
            }
            break;

        case M2PA_LS_PROCESSOR_REC:
            /*
             * Send L2_L3_REMOTE_PROCESSOR_REC to MTP3
             * if state > OOS
             */
            if (SCTPTRAN_STATE(t) > M2PA_STATE_OOS)
            {
                tmp = ev->data;
                ev->data = ITS_Malloc(3 * sizeof(ITS_OCTET));
                L2_MSG_TYPE(ev) = L2_L3_REMOTE_PROCESSOR_REC;
                L2_LINK_SET(ev) = ln->linkSet->linkSet;
                L2_LINK_CODE(ev) = ln->linkCode;
                ITS_Free(tmp);
            }
            break;

        case M2PA_LS_BUSY:
            /* start T6 */
            tc.trigger = M2PA_TRIGGER_T6_EXPIRY;
            tc.transport = TRANSPORT_INSTANCE(m);

            SCTPTRAN_T6(m) = TIMERS_StartTimer(M2PA_MANAGER_INSTANCE, m2paT6,
                                               &tc, sizeof(M2PA_TimerContext));
            break;

        case M2PA_LS_BUSY_END:
            /* stop T6 */
            TIMERS_CancelTimer(SCTPTRAN_T6(t));
            break;

        default:
            break;
        }
        break;

    case M2PA_MSG_PROVING_DATA:
        /* check data, determine accuracy */
        msg->hdr.msgLength = SOCK_NToHL(msg->hdr.msgLength);
        ITS_C_ASSERT(msg->hdr.msgLength == PROVING_DATA_LEN);
        pdIdx = msg->body.provingData.data[0];
        if (pdIdx > NUM_PROVES ||
            memcmp(msg->body.provingData.data, provingData[pdIdx],
                   PROVING_DATA_LEN) != 0)
        {
            pdm = (SCTPTRAN_FLAGS(t) & SCTPTRAN_FLAG_PDM_MASK) >>
                    SCTPTRAN_FLAG_PDM_SHIFT;
            if (pdm < MAX_PD_MISS)
            {
                pdm++;

                SCTPTRAN_FLAGS(t) &= ~SCTPTRAN_FLAG_PDM_MASK;
                SCTPTRAN_FLAGS(t) |= (pdm << SCTPTRAN_FLAG_PDM_SHIFT) &
                                        SCTPTRAN_FLAG_PDM_MASK;
            }
        }
        return (ITS_ENOMSG);

    default:
        break;
    }

    TRANSPORT_UnfindTransport(t);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Handle M2PA timers.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
static void
M2PA_Callback(ITS_POINTER object,
              ITS_POINTER userData, ITS_POINTER callData)
{
    SCTPTRAN_Manager *rem = (SCTPTRAN_Manager *)object;
    SCTP_API_MSG_HDR *msg = (SCTP_API_MSG_HDR *)callData;
    SCTP_API_CMSG *cmsg = (SCTP_API_CMSG *)msg->control;
    ITS_EVENT rsp;
    SS7_LinkPtr ln;

    switch (cmsg->hdr.type)
    {
    case SCTP_CM_ASSOC_CHG:
        switch (cmsg->data.assocChg.state)
        {
        case SCTP_AC_COMM_UP:
            M2PA_StateMachine(rem, M2PA_TRIGGER_COMM_UP);
            break;

        case SCTP_AC_COMM_LOST:
        case SCTP_AC_COMM_ABORTED:
        case SCTP_AC_SHUTDOWN_DONE:
            M2PA_StateMachine(rem, M2PA_TRIGGER_COMM_DOWN);
            /* Send L2_L3_OUT_OF_SERVICE to MTP3 */
            if (SCTPTRAN_STATE(rem) > M2PA_STATE_OOS)
            {
                ln = TRANSPORT_SS7_INFO(rem).linkInfo;
                ITS_C_ASSERT(ln != NULL);

                ITS_EVENT_INIT(&rsp, TRANSPORT_INSTANCE(rem),
                               3 * sizeof(ITS_OCTET));
                L2_MSG_TYPE(&rsp) = L2_L3_OUT_OF_SERVICE;
                L2_LINK_SET(&rsp) = ln->linkSet->linkSet;
                L2_LINK_CODE(&rsp) = ln->linkCode;
                TRANSPORT_PutEvent(ITS_MTP3_SRC, &rsp);
            }
            break;

        case SCTP_AC_COMM_RESTART:
            M2PA_StateMachine(rem, M2PA_TRIGGER_COMM_RESTART);
            break;

        default:
            break;
        }
        break;

    /*
     * FIXME: There may eventually be a CONGESTION callback, in which
     * case these go here (send to MTP3 one of):
     *  L2_L3_CONGESTION_ONSET
     *  L2_L3_CONGESTION_ABATES
     *
     * FIXME: ONSET send Link Status Busy messages
     * FIXME: ABATES send Link Status Busy End message
     */

    default:
        break;
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Handle M2PA timers.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
static THREAD_RET_TYPE
M2PAThread(void *arg)
{
    ITS_TimerData *its;
    M2PA_TimerContext tc;
    TRANSPORT_Control *t;
    ITS_EVENT m2paEvent;
    SS7_LinkPtr ln;
    ITS_EVENT rsp;
    M2PA_MSG *msg;
    ITS_UINT pdIdx;

    memset(&m2paEvent, 0, sizeof(ITS_EVENT));

    TRANSPORT_IS_ACTIVE(m2paHandle) = ITS_TRUE;

    while (TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(m2paHandle))
                                                        (m2paHandle,
                                                         &m2paEvent) ==
           ITS_SUCCESS)
    {
        switch (m2paEvent.src)
        {
        case M2PA_MANAGER_INSTANCE:
            /* termination message */
            ITS_TRACE_DEBUG(("M2PAThread: exiting ok\n"));

            TRANSPORT_IS_ACTIVE(m2paHandle) = ITS_FALSE;

            THREAD_NORMAL_EXIT;
            break;

        case ITS_TIMER_SRC:
            its = (ITS_TimerData *)m2paEvent.data;
            memcpy(&tc, its->context, sizeof(M2PA_TimerContext));
            switch (tc.trigger)
            {
            case M2PA_TRIGGER_T1_EXPIRY:
                t = TRANSPORT_FindTransport(tc.transport);
                M2PA_StateMachine((SCTPTRAN_Manager *)t, M2PA_TRIGGER_T1_EXPIRY);
                TRANSPORT_UnfindTransport(t);
                break;

            case M2PA_TRIGGER_T2_EXPIRY:
                t = TRANSPORT_FindTransport(tc.transport);
                /* FIXME: Determine if the proving period was successful */
                /* Unless a link status ready message has been received */
                if (SCTPTRAN_FLAGS(t) & SCTPTRAN_FLAG_READY)
                {
                    /* If yes, start T3 */
                    tc.trigger = M2PA_TRIGGER_T3_EXPIRY;
                    tc.transport = TRANSPORT_INSTANCE(t);

                    SCTPTRAN_T3(t) = TIMERS_StartTimer(M2PA_MANAGER_INSTANCE, m2paT3,
                                                       &tc, sizeof(M2PA_TimerContext));
                }
                /* Send link status ready to peer */
                ITS_EVENT_INIT(&rsp, M2PA_MANAGER_INSTANCE,
                               sizeof(UA_HDR) + sizeof(M2PA_LINK_STATUS_MSG));
                msg = (M2PA_MSG *)rsp.data;
                msg->hdr.version = M2PA_VERSION_1;
                msg->hdr.spare = 0;
                msg->hdr.msgClass = M2PA_MSG_CLASS;
                msg->hdr.msgType = M2PA_MSG_LINK_STATUS;
                msg->hdr.msgLength = SOCK_HToNL(sizeof(M2PA_LINK_STATUS_MSG));
                msg->body.linkStatus.status = SOCK_HToNL(M2PA_LS_READY);
                TRANSPORT_PutEvent(TRANSPORT_INSTANCE(t),
                                   &rsp);

                /* Start SEND STATUS timer */
                tc.trigger = M2PA_TRIGGER_SEND_STATUS;
                tc.transport = TRANSPORT_INSTANCE(t);
                SCTPTRAN_LS(t) = TIMERS_StartTimer(M2PA_MANAGER_INSTANCE,
                                                   m2paLS,
                                                   &tc, sizeof(M2PA_TimerContext));
                /* run the state machine */
                M2PA_StateMachine((SCTPTRAN_Manager *)t, M2PA_TRIGGER_T2_EXPIRY);
                TRANSPORT_UnfindTransport(t);
                break;

            case M2PA_TRIGGER_T3_EXPIRY:
                t = TRANSPORT_FindTransport(tc.transport);
                M2PA_StateMachine((SCTPTRAN_Manager *)t, M2PA_TRIGGER_T3_EXPIRY);

                ITS_EVENT_INIT(&rsp, TRANSPORT_INSTANCE(t),
                               3 * sizeof(ITS_OCTET));
                /* Send L2_L3_OUT_OF_SERVICE to MTP3 */
                ln = TRANSPORT_SS7_INFO(t).linkInfo;
                ITS_C_ASSERT(ln != NULL);

                L2_MSG_TYPE(&rsp) = L2_L3_OUT_OF_SERVICE;
                L2_LINK_SET(&rsp) = ln->linkSet->linkSet;
                L2_LINK_CODE(&rsp) = ln->linkCode;

                TRANSPORT_PutEvent(ITS_MTP3_SRC, &rsp);

                TRANSPORT_UnfindTransport(t);

                break;

            case M2PA_TRIGGER_T6_EXPIRY:
                t = TRANSPORT_FindTransport(tc.transport);
                M2PA_StateMachine((SCTPTRAN_Manager *)t, M2PA_TRIGGER_T6_EXPIRY);
                /* FIXME: Abort the association */
                TRANSPORT_UnfindTransport(t);
                break;

            case M2PA_TRIGGER_PROVING_DATA_NEEDED:
                /* send proving data on tc.transport */
                pdIdx = (SCTPTRAN_FLAGS(t) & SCTPTRAN_FLAG_PD_MASK) >>
                            SCTPTRAN_FLAG_PD_SHIFT;
                pdIdx = (pdIdx + 1) % NUM_PROVES;
                SCTPTRAN_FLAGS(t) &= ~SCTPTRAN_FLAG_PD_MASK;
                SCTPTRAN_FLAGS(t) |= (pdIdx << SCTPTRAN_FLAG_PD_SHIFT) &
                                        SCTPTRAN_FLAG_PD_MASK;
                ITS_EVENT_INIT(&rsp, M2PA_MANAGER_INSTANCE,
                               sizeof(UA_HDR) + PROVING_DATA_LEN);
                msg = (M2PA_MSG *)rsp.data;
                msg->hdr.version = M2PA_VERSION_1;
                msg->hdr.spare = 0;
                msg->hdr.msgClass = M2PA_MSG_CLASS;
                msg->hdr.msgType = M2PA_MSG_PROVING_DATA;
                msg->hdr.msgLength = SOCK_HToNL(PROVING_DATA_LEN);
                memcpy(msg->body.provingData.data, provingData[pdIdx],
                       PROVING_DATA_LEN);
                TRANSPORT_PutEvent(TRANSPORT_INSTANCE(t),
                                   &rsp);
                /* start PROVING_DATA_NEEDED timer */
                tc.trigger = M2PA_TRIGGER_PROVING_DATA_NEEDED;
                tc.transport = TRANSPORT_INSTANCE(t);
                SCTPTRAN_PD(t) = TIMERS_StartTimer(M2PA_MANAGER_INSTANCE,
                                                   m2paPD,
                                                   &tc, sizeof(M2PA_TimerContext));
                break;

            case M2PA_TRIGGER_SEND_STATUS:
                /* send Link Status Ready messages */
                t = TRANSPORT_FindTransport(tc.transport);
                ITS_EVENT_INIT(&rsp, M2PA_MANAGER_INSTANCE,
                               sizeof(UA_HDR) + sizeof(M2PA_LINK_STATUS_MSG));
                msg = (M2PA_MSG *)rsp.data;
                msg->hdr.version = M2PA_VERSION_1;
                msg->hdr.spare = 0;
                msg->hdr.msgClass = M2PA_MSG_CLASS;
                msg->hdr.msgType = M2PA_MSG_LINK_STATUS;
                msg->hdr.msgLength = SOCK_HToNL(sizeof(M2PA_LINK_STATUS_MSG));
                msg->body.linkStatus.status = SOCK_HToNL(M2PA_LS_READY);
                TRANSPORT_PutEvent(TRANSPORT_INSTANCE(t),
                                   &rsp);

                tc.trigger = M2PA_TRIGGER_SEND_STATUS;
                tc.transport = TRANSPORT_INSTANCE(t);
                SCTPTRAN_LS(t) = TIMERS_StartTimer(M2PA_MANAGER_INSTANCE,
                                                   m2paLS,
                                                   &tc, sizeof(M2PA_TimerContext));
                TRANSPORT_UnfindTransport(t);
                break;

            default:
                break;
            }
            break;

        default:
            break;
        }
    }

    THREAD_NORMAL_EXIT;
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Initialize the M2PA subsystem.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
static int
ClassInit(ITS_Class objClass)
{
    /* create transport */
    if ((m2paHandle = TQUEUETRAN_CreateTransport("M2PA Manager",
                                                 M2PA_MANAGER_INSTANCE,
                                                 0)) == NULL)
    {
        ITS_TRACE_ERROR(("ClassInit: Couldn't create transport."));

        return (ITS_ENOTRANSPORT);
    }


    /* create thread */
    if (THREAD_CreateThread(&m2paThread, 0,
                            M2PAThread, NULL,
                            ITS_TRUE) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ClassInit: Couldn't create thread.\n"));

        TQUEUETRAN_DeleteTransport(m2paHandle);

        return (ITS_EBADTHREAD);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Terminate the M2PA subsystem.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
static void
ClassTerm(ITS_Class objClass)
{
    void *status;
    ITS_EVENT stopEvent;

    ITS_TRACE_DEBUG(("ClassTerm:\n"));

    stopEvent.src = M2PA_MANAGER_INSTANCE;
    stopEvent.len = 0;
    stopEvent.data = NULL;

    /* send stop message */
    TRANSPORT_PutEvent(M2PA_MANAGER_INSTANCE, &stopEvent);

    /* delete thread */
    THREAD_WaitForThread(&m2paThread, &status);

    /* delete transport */
    TQUEUETRAN_DeleteTransport(m2paHandle);
}

/*
 * the class record
 */
ITS_ClassRec itsM2PA_ClassRec =
{
    /* core part */
    {
        NULL,                           /* we're in a DLL, windows can't cope */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        M2PA_CLASS_NAME,                /* class name */
        ClassInit,                      /* class init */
        ClassTerm,                      /* class destroy */
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

VSS7DLLAPI ITS_Class itsM2PA_Class = (ITS_Class)&itsM2PA_ClassRec;
