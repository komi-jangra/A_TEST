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
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:19  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:34  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:54  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2002/01/10 16:51:35  mmiers
 * LOG: Finish the transport refcounting effort.  Move vframe from
 * LOG: vendors to here.
 * LOG:
 * LOG: Revision 5.2  2001/11/16 02:07:22  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/05/02 19:58:55  mmiers
 * LOG: Add thread pool shutdown logic.  People using the C API
 * LOG: need to convert to WORKER_GetExit() instead of TPOOL_THREAD_EXIT().
 * LOG:
 * LOG: Revision 4.2  2001/05/02 19:06:01  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/28 23:04:40  mmiers
 * LOG: Remove a warning.
 * LOG:
 * LOG: Revision 3.6  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.5  2001/03/09 23:51:08  mmiers
 * LOG: Convert the sublayers.  Decide what info engine needs per transport.
 * LOG:
 * LOG: Revision 3.4  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.3  2001/02/15 16:05:45  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.2  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.2  2000/10/09 17:37:22  mmiers
 * LOG: RUDP updates, cross-platform build.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:15  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.24  2000/06/02 17:18:11  mmiers
 * LOG:
 * LOG:
 * LOG: Socket modifications.
 * LOG:
 * LOG: Revision 1.23  2000/03/02 16:24:13  ssharma
 * LOG:
 * LOG: Watch for type promotion in varargs (short becomes int).
 * LOG:
 * LOG: Revision 1.22  2000/02/15 20:34:45  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 1.21  2000/02/14 19:17:40  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 1.20  2000/02/12 00:08:42  mmiers
 * LOG:
 * LOG: Move RESFILE to core library.  Convert RESFILE and TRACE to OO footing.
 * LOG:
 * LOG: Revision 1.19  2000/02/11 00:02:54  mmiers
 * LOG:
 * LOG:
 * LOG: RUDP working (basic mode).  Work on OOS and TCS tomorrow.
 * LOG:
 * LOG: Revision 1.18  2000/02/10 14:48:09  mmiers
 * LOG:
 * LOG: Add functions for network/host conversion so they're always in our
 * LOG: namespace.
 * LOG:
 * LOG: Revision 1.17  2000/02/10 02:18:08  mmiers
 * LOG: Fix some nasty bugs that didn't show up on NT.
 * LOG:
 * LOG: Revision 1.16  2000/02/10 01:47:57  mmiers
 * LOG: Cross platform cleanup.
 * LOG:
 * LOG: Revision 1.15  2000/02/10 00:44:35  mmiers
 * LOG:
 * LOG:
 * LOG: RUDP connections at IDLE now work.  More tomorrow.
 * LOG:
 * LOG: Revision 1.14  2000/02/08 21:58:38  mmiers
 * LOG:
 * LOG:
 * LOG: Fine grain locking.
 * LOG:
 * LOG: Revision 1.13  2000/02/08 21:43:31  mmiers
 * LOG:
 * LOG:
 * LOG: Visual debugging.
 * LOG:
 * LOG: Revision 1.12  2000/02/08 18:23:23  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up RUDP.  Now to test this mess.
 * LOG:
 * LOG: Revision 1.11  2000/02/02 15:53:01  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 1.10  2000/01/31 23:17:01  mmiers
 * LOG:
 * LOG:
 * LOG: Some GDI tweaks, some RUDP work.
 * LOG:
 * LOG: Revision 1.9  2000/01/26 17:36:31  mmiers
 * LOG:
 * LOG:
 * LOG: Fix feature processing.
 * LOG:
 * LOG: Revision 1.8  2000/01/25 23:47:22  mmiers
 * LOG:
 * LOG:
 * LOG: More work on RUDP.  This is finally taking shape.
 * LOG:
 * LOG: Revision 1.7  2000/01/24 23:13:50  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating.
 * LOG:
 * LOG: Revision 1.6  2000/01/24 22:19:21  mmiers
 * LOG:
 * LOG:
 * LOG: Add UDP style transports.
 * LOG:
 * LOG: Revision 1.5  2000/01/21 22:14:05  mmiers
 * LOG:
 * LOG: Checkpoint changes.  Include routing behavior changes for Rajesh.
 * LOG:
 * LOG: Revision 1.4  2000/01/18 00:20:26  mmiers
 * LOG: First complete (more or less) cut of RUDP.
 * LOG:
 * LOG: Revision 1.3  2000/01/15 00:50:53  mmiers
 * LOG:
 * LOG:
 * LOG: Save of end of SYN_SENT.
 * LOG:
 * LOG: Revision 1.2  2000/01/14 23:59:57  mmiers
 * LOG:
 * LOG:
 * LOG: Try again.  This time get the right RUDP source.
 * LOG:
 * LOG: Revision 1.3  2000/01/06 23:43:59  mmiers
 * LOG:
 * LOG:
 * LOG: RUDP update, docgen fix.
 * LOG:
 * LOG: Revision 1.2  2000/01/05 02:55:42  mmiers
 * LOG:
 * LOG: Continue with the initial RUDP implementation.
 * LOG:
 * LOG: Revision 1.1  2000/01/05 00:25:54  mmiers
 * LOG:
 * LOG:
 * LOG: start implementing the lower level.
 * LOG:
 * LOG: Revision 1.3  1999/12/23 02:39:14  mmiers
 * LOG:
 * LOG:
 * LOG: Commit the full version.
 * LOG:
 * LOG: Revision 1.2  1999/12/23 02:27:16  mmiers
 * LOG:
 * LOG:
 * LOG: Code up the interface for this API.
 * LOG:
 * LOG: Revision 1.1  1999/12/22 23:14:12  mmiers
 * LOG: New file.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_object.h>
#include <its_hash.h>
#include <its_trace.h>
#include <its_timers.h>
#include <its_ip_trans.h>
#include <its_tq_trans.h>
#include <its_callback.h>
#include <its_transports.h>
#include <its_assertion.h>
#include <its_hmi.h>

#ident "$Id: its_rudp.c,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $"

#define RUDP_IMPLEMENTATION

#include <its_rudp.h>

static ITS_THREAD       rudpThread;

static TQUEUETRAN_Manager*  __RUDP_RcvQueue;

#define TO_SECS(x)  (((x) + 999) / 1000)

/*.implementation:extern
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
static ITS_USHORT
CheckSum(void *data, ITS_USHORT size)
{
    ITS_USHORT chksum = 0, i;

    ITS_TRACE_DEBUG(("CheckSum\n"));

    for (i = 0; i < size; i++)
    {
        chksum += ((ITS_OCTET *)data)[i];
    }

    return (chksum);
}

/*.implementation:extern
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
BuildMsg(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_USHORT chksum;

    ITS_TRACE_DEBUG(("BuildMsg\n"));

    /* compute the basic header length */
    msg->hdr.hdrLength = sizeof(RUDP_HDR) + msg->hdrLen +
                                sizeof(RUDP_CKSUM);

    /*
     * if we're carrying payload and we want it checksummed,
     * include space for it.
     */
    if (msg->hdr.flags & RUDP_CHK)
    {
        msg->hdr.hdrLength += sizeof(RUDP_CKSUM);
    }

    /*
     * check for overflow conditions
     */
    if (msg->hdr.hdrLength + msg->dataLen >
        RUDP_UPARAMS(rudp).maxSegmentSize)
    {
        return (ITS_EOVERFLOW);
    }

    /*
     * copy in the header and header payload, if any
     */
    memcpy(RUDP_SEND_BUF(rudp), &msg->hdr, sizeof(RUDP_HDR));

    if (msg->hdrLen)
    {
        memcpy(RUDP_SEND_BUF(rudp) + sizeof(RUDP_HDR),
               &msg->hdrData, msg->hdrLen);
    }

    /*
     * compute the data checksum and include it if necessary.
     *
     * FIXME: If we have no data, do we checksum it?  Assume yes.
     */
    if (msg->hdr.flags & RUDP_CHK)
    {
        chksum = CheckSum(msg->userData, msg->dataLen);
        chksum = SOCK_HToNS(chksum);

        memcpy(RUDP_SEND_BUF(rudp) + sizeof(RUDP_HDR) + msg->hdrLen,
               &chksum, sizeof(ITS_USHORT));
    }

    /*
     * compute the header checksum and include it.
     */
    chksum = CheckSum(RUDP_SEND_BUF(rudp),
                      (ITS_USHORT)(msg->hdr.hdrLength -
                        sizeof(ITS_USHORT)));
    chksum = SOCK_HToNS(chksum);
    memcpy(RUDP_SEND_BUF(rudp) + msg->hdr.hdrLength - sizeof(ITS_USHORT),
           &chksum, sizeof(ITS_USHORT));

    /*
     * copy data, if present
     */
    if (msg->dataLen)
    {
        memcpy(RUDP_SEND_BUF(rudp) + msg->hdr.hdrLength,
               msg->userData, msg->dataLen);
    }

    RUDP_CUR_SEND_SEG_SIZE(rudp) = msg->hdr.hdrLength + msg->dataLen;

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
sendMsg(RUDP_Manager *rudp, void *data, size_t dsize)
{
    int ret;
    ITS_EVENT ev;
    TRANSPORT_Control *ctxt = SOCKTRAN_REMOTES(rudp)[0];

    ITS_TRACE_DEBUG(("sendMsg\n"));

    ITS_EVENT_INIT(&ev, 0, dsize);

    memcpy(ev.data, data, dsize);

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_WMUTEX(ctxt))) != ITS_SUCCESS)
    {
        return (ret);
    }

    ret = SOCKTRAN_CLASS_EXT_WRITE_EVENT(ITS_OBJ_CLASS(ctxt))(ctxt, &ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(ctxt));

    return (ret);
}

/*.implementation:extern
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
ParseMsg(RUDP_Manager *rudp, ITS_EVENT *ev)
{
    ITS_RUDP_MSG msg;
    ITS_USHORT hdrChkSum, dataChkSum, dataLen, offset;

    ITS_TRACE_DEBUG(("ParseMsg\n"));

    if (ev->len < sizeof(RUDP_HDR) + sizeof(RUDP_CKSUM))
    {
        return (ITS_EOVERFLOW);
    }

    /* get the header */
    memcpy(&msg.hdr, ev->data, sizeof(RUDP_HDR));

    msg.hdrLen = msg.hdr.hdrLength -
                    (sizeof(RUDP_HDR) + sizeof(RUDP_CKSUM));

    /* get the header info, if any */
    if (msg.hdrLen)
    {
        memcpy(&msg.hdrData.syn, &ev->data[sizeof(RUDP_HDR)], msg.hdrLen);
    }

    /* get the header checksum */
    memcpy(&hdrChkSum,
           &ev->data[sizeof(RUDP_HDR) + msg.hdrLen],
           sizeof(ITS_USHORT));

    /* handle CHK case */
    if (msg.hdr.flags & RUDP_CHK)
    {
        offset = sizeof(RUDP_HDR) + msg.hdrLen + sizeof(RUDP_CKSUM) * 2;
        if (ev->len < offset)
        {
            return (ITS_EOVERFLOW);
        }
        dataLen = ev->len - offset;

        memcpy(&dataChkSum,
               &ev->data[sizeof(RUDP_HDR) + msg.hdrLen + sizeof(RUDP_CKSUM)],
               sizeof(ITS_USHORT));
    }
    else
    {
        offset = sizeof(RUDP_HDR) + msg.hdrLen + sizeof(RUDP_CKSUM);
        dataLen = ev->len - offset;
    }

    msg.dataLen = dataLen;
    if (dataLen)
    {
        memcpy(msg.userData, &ev->data[offset], dataLen);
    }

    ev->len = sizeof(ITS_RUDP_MSG);
    memcpy(ev->data, &msg, sizeof(ITS_RUDP_MSG));

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
FormatSYN(RUDP_Manager* rudp, ITS_RUDP_MSG *msg)
{
    RUDP_UPARAMS(rudp).version = RUDP_SYN_VER_REV_E;

    ITS_TRACE_DEBUG(("FormatSYN\n"));

    if (RUDP_UPARAMS(rudp).maxNumSegsPending < RUDP_SYN_MAX_SEGS_PEND_DEFAULT)
    {
        RUDP_UPARAMS(rudp).maxNumSegsPending = RUDP_SYN_MAX_SEGS_PEND_DEFAULT;
    }

    if (RUDP_UPARAMS(rudp).maxSegmentSize < RUDP_SYN_MAX_SEG_SIZE_DEFAULT)
    {
        RUDP_UPARAMS(rudp).maxSegmentSize = RUDP_SYN_MAX_SEG_SIZE_DEFAULT;
    }

    if (RUDP_UPARAMS(rudp).retransTimeout < RUDP_SYN_MIN_RETRANS_TIMEOUT)
    {
        RUDP_UPARAMS(rudp).retransTimeout = RUDP_SYN_DEFAULT_RETRANS_TIMEOUT;
    }

    if (RUDP_UPARAMS(rudp).cumAckTimeout < RUDP_SYN_MIN_CUM_ACK_TIMEOUT)
    {
        RUDP_UPARAMS(rudp).cumAckTimeout = RUDP_SYN_DEFAULT_CUM_ACK_TIMEOUT;
    }

    RUDP_SYN_SET_CONN_ID(RUDP_UPARAMS(rudp), SOCK_HToNL(RUDP_LOCAL_CONN_ID(rudp)));

    msg->hdrLen = sizeof(RUDP_SYN_DATA);
    msg->hdrData.syn = RUDP_UPARAMS(rudp);

    msg->hdrData.syn.maxSegmentSize =
        SOCK_HToNS(msg->hdrData.syn.maxSegmentSize);
    msg->hdrData.syn.retransTimeout =
        SOCK_HToNS(msg->hdrData.syn.retransTimeout);
    msg->hdrData.syn.cumAckTimeout =
        SOCK_HToNS(msg->hdrData.syn.cumAckTimeout);
    msg->hdrData.syn.nullSegTimeout =
        SOCK_HToNS(msg->hdrData.syn.nullSegTimeout);
    msg->hdrData.syn.transStateTimeout =
        SOCK_HToNS(msg->hdrData.syn.transStateTimeout);
    msg->hdrData.syn.connIdentifier[0] =
        SOCK_HToNS(msg->hdrData.syn.connIdentifier[0]);
    msg->hdrData.syn.connIdentifier[1] =
        SOCK_HToNS(msg->hdrData.syn.connIdentifier[1]);

    msg->dataLen = 0;
}

/*.implementation:extern
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
ParseSYN(RUDP_Manager *rudp, ITS_RUDP_MSG* msg)
{
    ITS_TRACE_DEBUG(("ParseSYN\n"));

    msg->hdrData.syn.maxSegmentSize =
        SOCK_NToHS(msg->hdrData.syn.maxSegmentSize);
    msg->hdrData.syn.retransTimeout =
        SOCK_NToHS(msg->hdrData.syn.retransTimeout);
    msg->hdrData.syn.cumAckTimeout =
        SOCK_NToHS(msg->hdrData.syn.cumAckTimeout);
    msg->hdrData.syn.nullSegTimeout =
        SOCK_NToHS(msg->hdrData.syn.nullSegTimeout);
    msg->hdrData.syn.transStateTimeout =
        SOCK_NToHS(msg->hdrData.syn.transStateTimeout);
    msg->hdrData.syn.connIdentifier[0] =
        SOCK_NToHS(msg->hdrData.syn.connIdentifier[0]);
    msg->hdrData.syn.connIdentifier[1] =
        SOCK_NToHS(msg->hdrData.syn.connIdentifier[1]);

    RUDP_SYN_SET_CONN_ID(msg->hdrData.syn,
                         SOCK_NToHL(RUDP_SYN_GET_CONN_ID(msg->hdrData.syn)));
}

/*.implementation:extern
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
FormatEAK(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    unsigned i;

    ITS_TRACE_DEBUG(("FormatEAK\n"));

    msg->hdrLen = (ITS_OCTET)RUDP_OOS_QUEUE_COUNT(rudp);

    for (i = 0; i < RUDP_OOS_QUEUE_COUNT(rudp); i++)
    {
        msg->hdrData.eak.outOfSequenceSegs[i] =
            RUDP_OOS_QUEUE(rudp)[i]->hdr.seqNumber;
    }
}

/*.implementation:extern
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
SendUserIndication(RUDP_Manager *rudp, RUDP_UMSG_TYPE type)
{
    ITS_RUDP_CALLBACK_DATA   msg;

    ITS_TRACE_DEBUG(("SendUserIndication: %d\n", type));

    msg.type = type;
    msg.connID = RUDP_LOCAL_CONN_ID(rudp);

    CALLBACK_CallCallbackList(RUDP_CALLBACKS(rudp),
                              (ITS_POINTER)rudp,
                              (ITS_POINTER)&msg);
}

/*.implementation:extern
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
static ITS_BOOLEAN
RcvdParamsOK(RUDP_Manager *rudp, ITS_RUDP_MSG* msg)
{
    ITS_TRACE_DEBUG(("RcvdParamsOK\n"));

    if (!(msg->hdr.flags & RUDP_SYN) ||
        msg->hdrLen != sizeof(RUDP_SYN_DATA))
    {
        ITS_TRACE_DEBUG(("RcvdParamsOK: size mismatch\n"));

        return (ITS_FALSE);
    }

    if (msg->hdrData.syn.retransTimeout > RUDP_UPARAMS(rudp).retransTimeout)
    {
        ITS_TRACE_DEBUG(("RcvdParamsOK: retrans mismatch\n"));

        return (ITS_FALSE);
    }

    if (msg->hdrData.syn.cumAckTimeout > RUDP_UPARAMS(rudp).cumAckTimeout)
    {
        ITS_TRACE_DEBUG(("RcvdParamsOK: cumAck mismatch\n"));

        return (ITS_FALSE);
    }

    if (msg->hdrData.syn.nullSegTimeout > RUDP_UPARAMS(rudp).nullSegTimeout)
    {
        ITS_TRACE_DEBUG(("RcvdParamsOK: nullSeg mismatch\n"));

        return (ITS_FALSE);
    }

    if (msg->hdrData.syn.transStateTimeout > RUDP_UPARAMS(rudp).transStateTimeout)
    {
        ITS_TRACE_DEBUG(("RcvdParamsOK: transState mismatch\n"));

        return (ITS_FALSE);
    }

    if (msg->hdrData.syn.maxRetrans > RUDP_UPARAMS(rudp).maxRetrans)
    {
        ITS_TRACE_DEBUG(("RcvdParamsOK: maxRetrans mismatch\n"));

        return (ITS_FALSE);
    }

    if (msg->hdrData.syn.maxCumAck > RUDP_UPARAMS(rudp).maxCumAck)
    {
        ITS_TRACE_DEBUG(("RcvdParamsOK:maxCumAck mismatch\n"));

        return (ITS_FALSE);
    }

    if (msg->hdrData.syn.maxOOS > RUDP_UPARAMS(rudp).maxOOS)
    {
        ITS_TRACE_DEBUG(("RcvdParamsOK: maxOOS mismatch\n"));

        return (ITS_FALSE);
    }

    if (msg->hdrData.syn.maxAutoReset > RUDP_UPARAMS(rudp).maxAutoReset)
    {
        ITS_TRACE_DEBUG(("RcvdParamsOK: maxAutoReset mismatch\n"));

        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

/*.implementation:extern
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
ComputeNegotiatedParams(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_TRACE_DEBUG(("ComputeNegotiatedParams\n"));

    if (msg->hdrData.syn.retransTimeout > RUDP_UPARAMS(rudp).retransTimeout)
    {
        msg->hdrData.syn.retransTimeout = RUDP_UPARAMS(rudp).retransTimeout;
    }

    if (msg->hdrData.syn.cumAckTimeout > RUDP_UPARAMS(rudp).cumAckTimeout)
    {
        msg->hdrData.syn.cumAckTimeout = RUDP_UPARAMS(rudp).cumAckTimeout;
    }

    if (msg->hdrData.syn.nullSegTimeout > RUDP_UPARAMS(rudp).nullSegTimeout)
    {
        msg->hdrData.syn.nullSegTimeout = RUDP_UPARAMS(rudp).nullSegTimeout;
    }

    if (msg->hdrData.syn.transStateTimeout > RUDP_UPARAMS(rudp).transStateTimeout)
    {
        msg->hdrData.syn.transStateTimeout = RUDP_UPARAMS(rudp).transStateTimeout;
    }

    if (msg->hdrData.syn.maxRetrans > RUDP_UPARAMS(rudp).maxRetrans)
    {
        msg->hdrData.syn.maxRetrans = RUDP_UPARAMS(rudp).maxRetrans;
    }

    if (msg->hdrData.syn.maxCumAck > RUDP_UPARAMS(rudp).maxCumAck)
    {
        msg->hdrData.syn.maxCumAck = RUDP_UPARAMS(rudp).maxCumAck;
    }

    if (msg->hdrData.syn.maxOOS > RUDP_UPARAMS(rudp).maxOOS)
    {
        msg->hdrData.syn.maxOOS = RUDP_UPARAMS(rudp).maxOOS;
    }

    if (msg->hdrData.syn.maxAutoReset > RUDP_UPARAMS(rudp).maxAutoReset)
    {
        msg->hdrData.syn.maxAutoReset = RUDP_UPARAMS(rudp).maxAutoReset;
    }
}

/*.implementation:extern
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
static ITS_BOOLEAN
ValidSeqNum(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_TRACE_DEBUG(("ValidSeqNum: cur %02x seq %02x\n",
                RUDP_CPARAMS(rudp).rcvCur, msg->hdr.seqNumber));

    ITS_TRACE_DEBUG(("Calc: %d < %d\n",
                msg->hdr.seqNumber - RUDP_CPARAMS(rudp).rcvCur,
                RUDP_UPARAMS(rudp).maxNumSegsPending));

    if (msg->hdr.seqNumber - RUDP_CPARAMS(rudp).rcvCur <
        RUDP_UPARAMS(rudp).maxNumSegsPending)
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

/*.implementation:extern
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
static ITS_BOOLEAN
ValidAckNum(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_TRACE_DEBUG(("ValidAckNum\n"));

    ITS_TRACE_DEBUG(("Calc: %d < %d\n",
                msg->hdr.ackNumber - RUDP_CPARAMS(rudp).sendNext,
                RUDP_UPARAMS(rudp).maxNumSegsPending));

    if (msg->hdr.ackNumber - RUDP_CPARAMS(rudp).sendNext <
        RUDP_UPARAMS(rudp).maxNumSegsPending)
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

/*.implementation:extern
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
static ITS_BOOLEAN
InSequence(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_TRACE_DEBUG(("InSequence\n"));

    if (msg->hdr.seqNumber == RUDP_CPARAMS(rudp).rcvCur + 1)
    {
        ITS_TRACE_DEBUG(("InSequence: True\n"));

        return (ITS_TRUE);
    }

    ITS_TRACE_DEBUG(("InSequence: False\n"));

    return (ITS_FALSE);
}

/*.implementation:extern
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
static ITS_BOOLEAN
RetransQueueEmpty(RUDP_Manager *rudp)
{
    ITS_TRACE_DEBUG(("RetransQueueEmpty\n"));

    if (RUDP_SEND_QUEUE_COUNT(rudp) == 0)
    {
        ITS_TRACE_DEBUG(("RetransQueueEmpty: True\n"));

        return (ITS_TRUE);
    }

    ITS_TRACE_DEBUG(("RetransQueueEmpty: False\n"));

    return (ITS_FALSE);
}

/*.implementation:extern
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
AppendToRetransQueue(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_RUDP_MSG *copy;

    ITS_TRACE_DEBUG(("AppendToRetransQueue: seq %02x\n",
                msg->hdr.seqNumber));

    if (RUDP_SEND_QUEUE_COUNT(rudp) >= RUDP_UPARAMS(rudp).maxNumSegsPending)
    {
        ITS_TRACE_DEBUG(("AppendToRetransQueue: overflow\n"));

        return (ITS_EOVERFLOW);
    }

    copy = (ITS_RUDP_MSG *)malloc(sizeof(ITS_RUDP_MSG));
    if (copy == NULL)
    {
        ITS_TRACE_DEBUG(("AppendToRetransQueue: out of mem\n"));

        return (ITS_ENOMEM);
    }

    memcpy(copy, msg, sizeof(ITS_RUDP_MSG));

    RUDP_SEND_QUEUE(rudp)[RUDP_SEND_QUEUE_COUNT(rudp)] = copy;
    RUDP_SEND_QUEUE_COUNT(rudp)++;

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
RemoveFromRetransQueue(RUDP_Manager *rudp, ITS_OCTET seqNumber)
{
    unsigned i;

    ITS_TRACE_DEBUG(("RemoveFromRetransQueue: Seq: %02x Count %d\n",
                seqNumber, RUDP_SEND_QUEUE_COUNT(rudp)));

    for (i = 0; i < RUDP_SEND_QUEUE_COUNT(rudp); i++)
    {
        if (RUDP_SEND_QUEUE(rudp)[i]->hdr.seqNumber == seqNumber)
        {
            RUDP_SEND_QUEUE_COUNT(rudp)--;

            ITS_TRACE_DEBUG(("RemoveFromRetransQueue: removed\n"));

            free(RUDP_SEND_QUEUE(rudp)[i]);

            if (RUDP_SEND_QUEUE_COUNT(rudp) > i)
            {
                memmove(&RUDP_SEND_QUEUE(rudp)[i], &RUDP_SEND_QUEUE(rudp)[i+1],
                        (RUDP_SEND_QUEUE_COUNT(rudp) - i) * sizeof(ITS_RUDP_MSG *));
            }
        }
    }
}

/*.implementation:extern
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
static ITS_BOOLEAN
OOSQueueEmpty(RUDP_Manager *rudp)
{
    ITS_TRACE_DEBUG(("OOSQueueEmtpy\n"));

    if (RUDP_OOS_QUEUE_COUNT(rudp) == 0)
    {
        ITS_TRACE_DEBUG(("OOSQueueEmtpy: True\n"));

        return (ITS_TRUE);
    }

    ITS_TRACE_DEBUG(("OOSQueueEmtpy: False\n"));

    return (ITS_FALSE);
}

/*.implementation:extern
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
AppendToOOSQueue(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_RUDP_MSG *copy;

    ITS_TRACE_DEBUG(("AppendToOOSQueue: seg %02x\n", msg->hdr.seqNumber));

    if (RUDP_OOS_QUEUE_COUNT(rudp) >= RUDP_UPARAMS(rudp).maxNumSegsPending)
    {
        ITS_TRACE_DEBUG(("AppendToOOSQueue: overflow\n"));

        return (ITS_EOVERFLOW);
    }

    copy = (ITS_RUDP_MSG *)malloc(sizeof(ITS_RUDP_MSG));
    if (copy == NULL)
    {
        ITS_TRACE_DEBUG(("AppendToOOSQueue: out of mem\n"));

        return (ITS_ENOMEM);
    }

    memcpy(copy, msg, sizeof(ITS_RUDP_MSG));

    RUDP_OOS_QUEUE(rudp)[RUDP_OOS_QUEUE_COUNT(rudp)] = copy;
    RUDP_OOS_QUEUE_COUNT(rudp)++;

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
RemoveFromOOSQueue(RUDP_Manager *rudp, ITS_OCTET seqNumber)
{
    unsigned i;

    ITS_TRACE_DEBUG(("RemoveFromOOSQueue: seqNumber\n", seqNumber));

    for (i = 0; i < RUDP_OOS_QUEUE_COUNT(rudp); i++)
    {
        if (RUDP_OOS_QUEUE(rudp)[i]->hdr.seqNumber == seqNumber)
        {
            RUDP_OOS_QUEUE_COUNT(rudp)--;

            ITS_TRACE_DEBUG(("RemoveFromOOSQueue: removed\n"));

            free(RUDP_OOS_QUEUE(rudp)[i]);

            if (RUDP_OOS_QUEUE_COUNT(rudp) > i)
            {
                memmove(&RUDP_OOS_QUEUE(rudp)[i], &RUDP_OOS_QUEUE(rudp)[i+1],
                        (RUDP_OOS_QUEUE_COUNT(rudp) - i) * sizeof(ITS_RUDP_MSG *));
            }
        }
    }
}

#if 0
/*
 * this gives a warning with gcc.  It isn't used, but is included
 * for completeness.
 */
/*.implementation:extern
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
static ITS_BOOLEAN
DuplicateInOOSQueue(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    unsigned i;

    ITS_TRACE_DEBUG(("DuplicateInOOSQueue\n"));

    for (i = 0; i < RUDP_OOS_QUEUE_COUNT(rudp); i++)
    {
        if (RUDP_OOS_QUEUE(rudp)[i]->hdr.seqNumber == msg->hdr.seqNumber)
        {
            ITS_TRACE_DEBUG(("DuplicateInOOSQueue: True\n"));

            return (ITS_TRUE);
        }
    }

    ITS_TRACE_DEBUG(("DuplicateInOOSQueue: False\n"));

    return (ITS_FALSE);
}
#endif

/*.implementation:extern
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
static ITS_BOOLEAN
RecvQueueEmpty(RUDP_Manager *rudp)
{
    ITS_TRACE_DEBUG(("RecvQueueEmpty\n"));

    if (RUDP_RECV_QUEUE_COUNT(rudp) == 0)
    {
        ITS_TRACE_DEBUG(("RecvQueueEmpty: True\n"));

        return (ITS_TRUE);
    }

    ITS_TRACE_DEBUG(("RecvQueueEmpty: False\n"));

    return (ITS_FALSE);
}

/*.implementation:extern
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
AppendToRecvQueue(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_RUDP_MSG *copy;

    ITS_TRACE_DEBUG(("AppendToRecvQueue: seq number %02x\n", msg->hdr.seqNumber));

    if (RUDP_RECV_QUEUE_COUNT(rudp) >= RUDP_UPARAMS(rudp).maxNumSegsPending)
    {
        ITS_TRACE_DEBUG(("AppendToRecvQueue: queue overflow\n"));

        return (ITS_EOVERFLOW);
    }

    copy = (ITS_RUDP_MSG *)malloc(sizeof(ITS_RUDP_MSG));
    if (copy == NULL)
    {
        ITS_TRACE_DEBUG(("AppendToRecvQueue: out of memory\n"));

        return (ITS_ENOMEM);
    }

    memcpy(copy, msg, sizeof(ITS_RUDP_MSG));

    RUDP_RECV_QUEUE(rudp)[RUDP_RECV_QUEUE_COUNT(rudp)] = copy;
    RUDP_RECV_QUEUE_COUNT(rudp)++;

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
RemoveFromRecvQueue(RUDP_Manager *rudp, ITS_OCTET seqNumber)
{
    unsigned i;

    ITS_TRACE_DEBUG(("RemoveFromRecvQueue: seq number %02x\n", seqNumber));

    for (i = 0; i < RUDP_RECV_QUEUE_COUNT(rudp); i++)
    {
        if (RUDP_RECV_QUEUE(rudp)[i]->hdr.seqNumber == seqNumber)
        {
            ITS_TRACE_DEBUG(("RemoveFromRecvQueue: removed\n"));

            RUDP_RECV_QUEUE_COUNT(rudp)--;

            free(RUDP_RECV_QUEUE(rudp)[i]);

            if (RUDP_RECV_QUEUE_COUNT(rudp) > i)
            {
                memmove(&RUDP_RECV_QUEUE(rudp)[i], &RUDP_RECV_QUEUE(rudp)[i+1],
                        (RUDP_RECV_QUEUE_COUNT(rudp) - i) * sizeof(ITS_RUDP_MSG *));
            }
        }
    }
}

/*.implementation:extern
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
TransferAllSegs(RUDP_Manager *from, RUDP_Manager *to,
                ITS_OCTET seqAdjFactor)
{
    int i, offset;

    ITS_TRACE_DEBUG(("TransferAllSegs\n"));

    /* transfer retransmit segs */
    offset = RUDP_SEND_QUEUE_COUNT(to);

    for (i = 0; i < RUDP_SEND_QUEUE_COUNT(from); i++)
    {
        AppendToRetransQueue(to, RUDP_SEND_QUEUE(from)[i]);

        RUDP_SEND_QUEUE(to)[offset+i]->hdr.seqNumber +=
            seqAdjFactor;
    }

    while (RUDP_SEND_QUEUE_COUNT(from) > 0)
    {
        RemoveFromRetransQueue(from,
                               RUDP_SEND_QUEUE(from)[0]->hdr.seqNumber);
    }

    /* transfer OOS segs */
    offset = RUDP_OOS_QUEUE_COUNT(to);

    for (i = 0; i < RUDP_OOS_QUEUE_COUNT(from); i++)
    {
        AppendToOOSQueue(to, RUDP_OOS_QUEUE(from)[i]);

        RUDP_OOS_QUEUE(to)[offset+i]->hdr.seqNumber +=
            seqAdjFactor;
    }

    while (RUDP_OOS_QUEUE_COUNT(from) > 0)
    {
        RemoveFromOOSQueue(from,
                           RUDP_OOS_QUEUE(from)[0]->hdr.seqNumber);
    }
}

/*.implementation:extern
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
CloseConnection(RUDP_Manager *rudp)
{
    ITS_USHORT eof;

    ITS_TRACE_DEBUG(("CloseConnection\n"));

    eof = 0xFFFFU;

    if (!SOCKTRAN_IS_VALID(rudp))
    {
        return;
    }

    SOCK_Send(SOCKTRAN_SOURCE(rudp), (char *)&eof, sizeof(ITS_USHORT),
              SOCKTRAN_SOURCE(rudp)->addr, SOCKTRAN_SOURCE(rudp)->asize);
}

/*.implementation:extern
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
RefuseConnection(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_RUDP_MSG rst;
    int ret;

    ITS_TRACE_DEBUG(("RefuseConnection\n"));

    /* FIXME: It's a data, NUL, or RST, so increment the seqNumber? */
    RUDP_CPARAMS(rudp).sendNext++;

    /* the header */
    rst.hdr.flags = RUDP_RST | RUDP_ACK;
    rst.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
    rst.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
    rst.hdr.hdrLength = 0;

    rst.hdrLen = 0;
    rst.dataLen = 0;

    /* send the RST */
    ret = BuildMsg(rudp, &rst);

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    SendUserIndication(rudp, RUDP_MSG_CONN_REFUSED);

    /* Cleanup connection (user activity) */

    /* Close connection (user activity) */
    CloseConnection(rudp);
}

/*.implementation:extern
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
SendACKOrEACK(RUDP_Manager *rudp)
{
    ITS_RUDP_MSG ack;
    RUDP_TimerContext timer;
    int ret;

    ITS_TRACE_DEBUG(("SendACKOrEAK\n"));

    if (!OOSQueueEmpty(rudp))
    {
        ITS_TRACE_DEBUG(("SendACKOrEAK: Send EAK\n"));

        ack.hdr.flags = RUDP_EAK;
        ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
        ack.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
        ack.hdr.hdrLength = 0;

        ack.hdrLen = 0;
        ack.dataLen = 0;

        FormatEAK(rudp, &ack);

        /* send the EAK */
        ret = BuildMsg(rudp, &ack);

        if (ret != ITS_SUCCESS)
        {
            return;
        }

        ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

        if (ret != ITS_SUCCESS)
        {
            return;
        }
    }
    else if (RUDP_CPARAMS(rudp).cumAckCount > 0)
    {
        ITS_TRACE_DEBUG(("SendACKOrEAK: Send ACK\n"));

        ack.hdr.flags = RUDP_ACK;
        ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
        ack.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
        ack.hdr.hdrLength = 0;

        ack.hdrLen = 0;
        ack.dataLen = 0;

        /* I think this is right. */
        RUDP_CPARAMS(rudp).cumAckCount = 0;

        /* send the ACK */
        ret = BuildMsg(rudp, &ack);

        if (ret != ITS_SUCCESS)
        {
            return;
        }

        ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

        if (ret != ITS_SUCCESS)
        {
            return;
        }
    }
    else
    {
        ITS_TRACE_DEBUG(("SendACKOrEAK: Send nothing\n"));
    }

    /* reset cumAck timer */
    ITS_TRACE_DEBUG(("SendACKOrEAK: Stop CumAck timer\n"));

    TIMERS_CancelTimer(RUDP_CUM_ACK(rudp));

    timer.timerID = RUDP_T4;
    timer.connID = RUDP_LOCAL_CONN_ID(rudp);

    ITS_TRACE_DEBUG(("SendACKOrEAK: Start CumAck timer\n"));

    RUDP_CUM_ACK(rudp) =
        TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                          TO_SECS(RUDP_UPARAMS(rudp).cumAckTimeout),
                          &timer, sizeof(timer));
}

/*.implementation:extern
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
TransferState(RUDP_Manager *rudp)
{
    RUDP_Manager *ctxt;
    ITS_RUDP_MSG tcs;
    int ret, i;

    ITS_TRACE_DEBUG(("TransferState\n"));

    /* SDL says do this */
    RUDP_CPARAMS(rudp).sendNext++;

    ctxt = (RUDP_Manager *)
            TRANSPORT_FindTransport((ITS_USHORT)RUDP_TRANSFER_CONN_ID(rudp));

    if (RetransQueueEmpty(ctxt))
    {
        tcs.hdrData.tcs.seqAdjFactor =
            RUDP_CPARAMS(rudp).sendNext - RUDP_CPARAMS(ctxt).sendNext;
    }
    else
    {
        tcs.hdrData.tcs.seqAdjFactor =
            RUDP_CPARAMS(rudp).sendNext - RUDP_SEND_QUEUE(ctxt)[0]->hdr.seqNumber;
    }

    TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);

    tcs.hdr.flags = RUDP_TCS | RUDP_ACK;
    tcs.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
    tcs.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
    tcs.hdr.hdrLength = 0;

    tcs.hdrLen = sizeof(RUDP_TCS_DATA);
    tcs.dataLen = 0;

    RUDP_TCS_SET_CONN_ID(tcs.hdrData.tcs, SOCK_HToNL(RUDP_LOCAL_CONN_ID(rudp)));

    /* send the TCS */
    ret = BuildMsg(rudp, &tcs);

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    AppendToRetransQueue(rudp, &tcs);

    /* Retransmit all segs on old retrans queue on
     * the current connection, with new sequence numbers */
    for (i = 0; i < RUDP_SEND_QUEUE_COUNT(rudp); i++)
    {
        ret = BuildMsg(rudp, RUDP_SEND_QUEUE(rudp)[i]);

        if (ret != ITS_SUCCESS)
        {
            return;
        }

        ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

        if (ret != ITS_SUCCESS)
        {
            return;
        }
    }

    RUDP_CPARAMS(rudp).sendTransferDone = ITS_TRUE;
}

/*.implementation:extern
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
ProcessACK(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_TRACE_DEBUG(("ProcessACK\n"));

    if (!(msg->hdr.flags & RUDP_ACK))
    {
        ITS_TRACE_DEBUG(("ProcessACK: not an ACK\n"));

        return;
    }

    if (!ValidAckNum(rudp, msg))
    {
        ITS_TRACE_DEBUG(("ProcessACK: invalid ACK num\n"));

        return;
    }

    RemoveFromRetransQueue(rudp, msg->hdr.ackNumber);

    /* was timed seg acked? */
    if (msg->hdr.ackNumber == RUDP_CPARAMS(rudp).timedAck)
    {
        RUDP_TimerContext timer;

        ITS_TRACE_DEBUG(("ProcessACK: stopping seg timer\n"));

        /* Stop retrans timer */
        ITS_TRACE_DEBUG(("ProcessACK: Stop Retransmit timer:\n"));
        ITS_TRACE_DEBUG(("rudp: %08x serial %08x\n",
                    rudp, RUDP_RETRANS(rudp)));

        TIMERS_CancelTimer(RUDP_RETRANS(rudp));

        /* are there unacked segs */
        if (!RetransQueueEmpty(rudp))
        {
            RUDP_CPARAMS(rudp).timedAck = RUDP_SEND_QUEUE(rudp)[0]->hdr.seqNumber;

            /* start retransmit timer */
            timer.timerID = RUDP_T3;
            timer.connID = RUDP_LOCAL_CONN_ID(rudp);

            ITS_TRACE_DEBUG(("ProcessACK: Start Retransmit timer\n"));

            RUDP_RETRANS(rudp) =
                TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                  TO_SECS(RUDP_UPARAMS(rudp).retransTimeout),
                                  &timer, sizeof(timer));

            ITS_TRACE_DEBUG(("rudp %08x conn %04x timer %08x\n",
                        rudp, timer.connID, RUDP_RETRANS(rudp)));
        }
        else
        {
            ITS_TRACE_DEBUG(("ProcessACK: No segs pending\n"));

            RUDP_CPARAMS(rudp).retransCount = 0;
        }
    }
    else
    {
        ITS_TRACE_DEBUG(("ProcessACK: Not ack for timed seg\n"));
        /* FIXME: Was sentList seg ack'd? */
            /* FIXME: Stop sentList timer */
    }
}

/*.implementation:extern
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
ProcessEACK(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_OCTET i;

    ITS_TRACE_DEBUG(("ProcessEACK\n"));

    if (!msg->hdr.flags & RUDP_EAK)
    {
        ITS_TRACE_DEBUG(("ProcessEACK: Not EAK\n"));

        return;
    }

    for (i = 0;
         i < msg->hdr.hdrLength - sizeof(RUDP_HDR) - sizeof(RUDP_CKSUM);
         i++)
    {
        ITS_TRACE_DEBUG(("ProcessEACK: remove pending seg %02x\n",
                    msg->hdrData.eak.outOfSequenceSegs[i]));

        RemoveFromRetransQueue(rudp, msg->hdrData.eak.outOfSequenceSegs[i]);
    }
}

/*.implementation:extern
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
ProcessMsgData(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_RUDP_MSG ack;
    int ret;

    ITS_TRACE_DEBUG(("ProcessMsgData\n"));

    if (msg->dataLen == 0)
    {
        ITS_TRACE_DEBUG(("ProcessMsgData: No data present.\n"));

        return;
    }

    RUDP_CPARAMS(rudp).cumAckCount++;

    if (InSequence(rudp, msg))
    {
        ITS_TRACE_DEBUG(("ProcessMsgData: Msg in sequence.\n"));

        AppendToRecvQueue(rudp, msg);

        RUDP_CPARAMS(rudp).rcvCur = msg->hdr.seqNumber;

        while (!OOSQueueEmpty(rudp) &&
               InSequence(rudp, RUDP_OOS_QUEUE(rudp)[0]))
        {
            ITS_TRACE_DEBUG(("ProcessMsgData: Move OOS msg %02x to recv Queue.\n",
                        RUDP_OOS_QUEUE(rudp)[0]->hdr.seqNumber));

            AppendToRecvQueue(rudp, RUDP_OOS_QUEUE(rudp)[0]);

            RUDP_CPARAMS(rudp).rcvCur =
                RUDP_OOS_QUEUE(rudp)[0]->hdr.seqNumber;

            RemoveFromOOSQueue(rudp,
                               RUDP_OOS_QUEUE(rudp)[0]->hdr.seqNumber);
        }
    }
    else
    {
        ITS_TRACE_DEBUG(("ProcessMsgData: Msg OO sequence.\n"));

        /* I don't think I got this right.  Retransmitted messages
         * will arrive here if no intervening ACK has been sent.
        if (DuplicateInOOSQueue(rudp, msg))
         */
        /* look instead for a duplicate of cur */
        if (msg->hdr.seqNumber == RUDP_CPARAMS(rudp).rcvCur)
        {
            ITS_TRACE_DEBUG(("ProcessMsgData: Msg duplicate.\n"));

            RUDP_CPARAMS(rudp).cumAckCount--;
        }
        else
        {
            ITS_TRACE_DEBUG(("ProcessMsgData: Msg OOS added.\n"));

            AppendToOOSQueue(rudp, msg);
        }
    }

    if (RUDP_CPARAMS(rudp).cumAckCount <= RUDP_UPARAMS(rudp).maxCumAck)
    {
        ITS_TRACE_DEBUG(("ProcessMsgData: Window not full.\n"));

        return;
    }

    if (RUDP_OOS_QUEUE_COUNT(rudp) > 0)
    {
        ITS_TRACE_DEBUG(("ProcessMsgData: Prepare EAK.\n"));

        ack.hdr.flags = RUDP_EAK;
        ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
        ack.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
        ack.hdr.hdrLength = 0;

        ack.hdrLen = 0;
        ack.dataLen = 0;

        FormatEAK(rudp, &ack);
    }
    else
    {
        ITS_TRACE_DEBUG(("ProcessMsgData: Prepare ACK.\n"));

        ack.hdr.flags = RUDP_ACK;
        ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
        ack.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
        ack.hdr.hdrLength = 0;

        ack.hdrLen = 0;
        ack.dataLen = 0;
    }

    /* send the SYN */
    ret = BuildMsg(rudp, &ack);

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

    if (ret != ITS_SUCCESS)
    {
        return;
    }
}

/*.implementation:extern
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
EnterCloseWait(RUDP_Manager *rudp)
{
    ITS_RUDP_MSG rst;
    RUDP_TimerContext timer;
    int ret;

    ITS_TRACE_DEBUG(("EnterCloseWait\n"));

    /* Increment sendNext */
    RUDP_CPARAMS(rudp).sendNext++;

    SendUserIndication(rudp, RUDP_MSG_CONN_CLOSING);

    rst.hdr.flags = RUDP_RST;
    rst.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
    rst.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
    rst.hdr.hdrLength = 0;

    rst.hdrLen = 0;
    rst.dataLen = 0;

    /* send the RST */
    ret = BuildMsg(rudp, &rst);

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    AppendToRetransQueue(rudp, &rst);

    /* start close wait */
    ITS_TRACE_DEBUG(("EnterCloseWait: Start CloseWait timer\n"));

    timer.timerID = RUDP_T2;
    timer.connID = RUDP_LOCAL_CONN_ID(rudp);
    RUDP_OPEN_CLOSE(rudp) =
        TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                          TO_SECS(RUDP_CPARAMS(rudp).openCloseTimeout),
                          &timer, sizeof(timer));
}

/*.implementation:extern
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
CloseOrResetConnection(RUDP_Manager *rudp)
{
    ITS_RUDP_MSG syn;
    int ret;
    RUDP_TimerContext timer;

    ITS_TRACE_DEBUG(("CloseOrResetConnection\n"));

    if (RUDP_UPARAMS(rudp).maxAutoReset == 0)
    {
        ITS_TRACE_DEBUG(("CloseOrResetConnection: No autoReset\n"));

        SendUserIndication(rudp, RUDP_MSG_CONN_RESET);

        /* Cleanup connection (user activity) */

        /* Close connection (user activity) */
        CloseConnection(rudp);

        RUDP_STATE(rudp) = RUDP_CLOSED;

        return;
    }

    /* FIXME: Cleanup connection */

    /* Reset ISS (FIXME: To what? */

    /* Format the header */
    ITS_TRACE_DEBUG(("CloseOrResetConnection: New SYN\n"));

    syn.hdr.flags = RUDP_SYN;
    syn.hdr.hdrLength = 0;
    syn.hdr.seqNumber = RUDP_CPARAMS(rudp).iss;
    syn.hdr.ackNumber = 0;

    syn.hdrLen = sizeof(RUDP_SYN_DATA);
    syn.dataLen = 0;

    /* build the SYN to send. */
    FormatSYN(rudp, &syn);

    /* send the SYN */
    ret = BuildMsg(rudp, &syn);

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    /* start open timer */
    timer.timerID = RUDP_T1;
    timer.connID = RUDP_LOCAL_CONN_ID(rudp);

    ITS_TRACE_DEBUG(("Start Open timer\n"));

    RUDP_OPEN_WAIT(rudp) =
        TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                          TO_SECS(RUDP_CPARAMS(rudp).openWaitTimeout),
                          &timer, sizeof(timer));

    RUDP_CPARAMS(rudp).openWaitCount++;

    SendUserIndication(rudp, RUDP_MSG_CONN_RESET);

    /* update state */
    RUDP_STATE(rudp) = RUDP_SYN_SENT;
}

/*.implementation:extern
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
Connect(RUDP_Manager *rudp)
{
    ITS_RUDP_MSG nwcopy;
    RUDP_TimerContext timer;
    int ret;

    ITS_TRACE_DEBUG(("Connect\n"));

    if (RUDP_STATE(rudp) != RUDP_IDLE && RUDP_STATE(rudp) != RUDP_LISTEN)
    {
        ITS_TRACE_DEBUG(("Connect: Bad state\n"));

        return (ITS_EBADSTATE);
    }

    /* Format the header */
    nwcopy.hdr.flags = RUDP_SYN;
    nwcopy.hdr.hdrLength = 0;
    nwcopy.hdr.seqNumber = RUDP_CPARAMS(rudp).iss;
    nwcopy.hdr.ackNumber = 0;

    nwcopy.hdrLen = sizeof(RUDP_SYN_DATA);
    nwcopy.dataLen = 0;

    /* build the SYN to send. */
    FormatSYN(rudp, &nwcopy);

    /* send the SYN */
    ret = BuildMsg(rudp, &nwcopy);

    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    /* start open timer */
    timer.timerID = RUDP_T1;
    timer.connID = RUDP_LOCAL_CONN_ID(rudp);

    ITS_TRACE_DEBUG(("Start Open timer\n"));

    RUDP_OPEN_WAIT(rudp) =
        TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                          TO_SECS(RUDP_CPARAMS(rudp).openWaitTimeout),
                          &timer, sizeof(timer));

    RUDP_CPARAMS(rudp).openWaitCount++;

    /* update state */
    RUDP_STATE(rudp) = RUDP_SYN_SENT;

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
TryOpen(RUDP_Manager *rudp, ITS_RUDP_MSG* msg)
{
    RUDP_TimerContext timer;
    int ret;

    ITS_TRACE_DEBUG(("TryOpen\n"));

    /* is it a SYN? */
    if (msg->hdr.flags & RUDP_SYN)
    {
        ITS_RUDP_MSG ack;

        ITS_TRACE_DEBUG(("TryOpen: got SYN\n"));

        ParseSYN(rudp, msg);

        /* have we been ACKed? */
        if (msg->hdr.flags & RUDP_ACK)
        {
            ITS_TRACE_DEBUG(("TryOpen: got SYN, ACK\n"));

            /* check for bad ACK. */
            if (msg->hdrLen != sizeof(RUDP_SYN_DATA) ||
                msg->hdr.ackNumber != RUDP_CPARAMS(rudp).iss)
            {
                ITS_TRACE_DEBUG(("TryOpen: Bad SYN\n"));

                return (ITS_EPROTERR);
            }

            ITS_TRACE_DEBUG(("Stop OpenWait timer\n"));

            TIMERS_CancelTimer(RUDP_OPEN_WAIT(rudp));

            /* set IRS */
            RUDP_CPARAMS(rudp).irs = msg->hdr.seqNumber;

            /*
             * Check reuse bit: FIXME: mine, or his?
             */
            if (!(RUDP_UPARAMS(rudp).options & RUDP_SYN_OPT_REUSE))
            {
                ITS_TRACE_DEBUG(("TryOpen: No reuse\n"));

                if (!RcvdParamsOK(rudp, msg))
                {
                    ITS_TRACE_DEBUG(("TryOpen: Refuse connection\n"));

                    RefuseConnection(rudp, msg);

                    RUDP_STATE(rudp) = RUDP_CLOSED;

                    return (ITS_EPROTERR);
                }

                RUDP_UPARAMS(rudp) = msg->hdrData.syn;
                RUDP_CPARAMS(rudp).rcvCur = msg->hdr.seqNumber;

                RUDP_REMOTE_CONN_ID(rudp) = RUDP_SYN_GET_CONN_ID(msg->hdrData.syn);
            }

            /* set maxSyncAttempts */
            RUDP_CPARAMS(rudp).maxSyncAttempts = RUDP_UPARAMS(rudp).maxAutoReset;

            /* keepalive timer */
            if (RUDP_UPARAMS(rudp).nullSegTimeout)
            {
                timer.timerID = RUDP_T6;
                timer.connID = RUDP_LOCAL_CONN_ID(rudp);

                ITS_TRACE_DEBUG(("Start KeepAlive timer on open\n"));

                RUDP_KEEPALIVE(rudp) =
                    TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                      TO_SECS(RUDP_UPARAMS(rudp).nullSegTimeout),
                                      &timer, sizeof(timer));
            }

            /* cumAck timer */
            timer.timerID = RUDP_T4;
            timer.connID = RUDP_LOCAL_CONN_ID(rudp);

            ITS_TRACE_DEBUG(("Start CumAck timer\n"));

            RUDP_CUM_ACK(rudp) =
                TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                  TO_SECS(RUDP_UPARAMS(rudp).cumAckTimeout),
                                  &timer, sizeof(timer));

            /* send standalone ACK */
            ack.hdr.flags = RUDP_ACK;
            ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
            ack.hdr.ackNumber = RUDP_CPARAMS(rudp).irs;
            ack.hdr.hdrLength = 0;

            ack.hdrLen = 0;
            ack.dataLen = 0;

            ret = BuildMsg(rudp, &ack);

            if (ret != ITS_SUCCESS)
            {
                return (ITS_EPROTERR);
            }

            ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

            if (ret != ITS_SUCCESS)
            {
                return (ITS_EPROTERR);
            }

            SendUserIndication(rudp, RUDP_MSG_CONN_OPEN);

            /* update state */
            RUDP_STATE(rudp) = RUDP_OPEN;
        }
        else
        {
            ITS_TRACE_DEBUG(("TryOpen: got SYN, !ACK\n"));

            /* set IRS */
            RUDP_CPARAMS(rudp).irs = msg->hdr.seqNumber;

            /*
             * Check reuse bit: FIXME: mine, or his?
             */
            if (!(RUDP_UPARAMS(rudp).options & RUDP_SYN_OPT_REUSE))
            {
                ITS_TRACE_DEBUG(("TryOpen: No reuse\n"));

                if (!RcvdParamsOK(rudp, msg))
                {
                    ITS_TRACE_DEBUG(("TryOpen: Negotiate params\n"));

                    ComputeNegotiatedParams(rudp, msg);
                }

                RUDP_UPARAMS(rudp) = msg->hdrData.syn;
                RUDP_CPARAMS(rudp).rcvCur = msg->hdr.seqNumber;

                RUDP_REMOTE_CONN_ID(rudp) = RUDP_SYN_GET_CONN_ID(msg->hdrData.syn);
            }

            ack = *msg;
            FormatSYN(rudp, &ack);

            ack.hdr.flags |= RUDP_ACK;
            ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
            ack.hdr.ackNumber = RUDP_CPARAMS(rudp).irs;
            ack.hdr.hdrLength = 0;

            ack.hdrLen = sizeof(RUDP_SYN_DATA);
            ack.dataLen = 0;

            /* send the SYN/ACK */
            ret = BuildMsg(rudp, &ack);

            if (ret != ITS_SUCCESS)
            {
                return (ITS_EPROTERR);
            }

            ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

            if (ret != ITS_SUCCESS)
            {
                return (ITS_EPROTERR);
            }

            timer.timerID = RUDP_T7;
            timer.connID = RUDP_LOCAL_CONN_ID(rudp);

            /* start autoReset timer */
            ITS_TRACE_DEBUG(("Start AutoReset timer\n"));

            RUDP_AUTO_RESET(rudp) =
                TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                  TO_SECS(RUDP_CPARAMS(rudp).autoResetTimeout),
                                  &timer, sizeof(timer));

            /* update state */
            RUDP_STATE(rudp) = RUDP_SYN_RCVD;
        }

        return (ITS_SUCCESS);
    }

    /* it's not a SYN. See if it's a RST. */
    if (msg->hdr.flags & RUDP_RST)
    {
        ITS_TRACE_DEBUG(("TryOpen: got RST\n"));

        if (msg->hdr.flags & RUDP_ACK)
        {
            ITS_TRACE_DEBUG(("TryOpen: CONN_REFUSED\n"));

            SendUserIndication(rudp, RUDP_MSG_CONN_REFUSED);
        }
        else
        {
            ITS_TRACE_DEBUG(("TryOpen: CONN_RESET\n"));

            SendUserIndication(rudp, RUDP_MSG_CONN_RESET);
        }

        /* Cleanup connection (user activity) */

        /* Close connection (user activity) */
        CloseConnection(rudp);

        /* update state */
        RUDP_STATE(rudp) = RUDP_CLOSED;

        return (ITS_SUCCESS);
    }

    /* Discard anything else. */
    ITS_TRACE_DEBUG(("Discarding message: flags %02x\n",
                     msg->hdr.flags));

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
TryListen(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_RUDP_MSG ack;
    int ret;
    RUDP_TimerContext timer;

    ITS_TRACE_DEBUG(("TryListen\n"));

    /* is it a reset */
    if (msg->hdr.flags & RUDP_RST)
    {
        ITS_TRACE_DEBUG(("TryListen: got RST\n"));

        SendUserIndication(rudp, RUDP_MSG_CONN_RESET);

        /* Cleanup connection (user activity) */

        /* Close connection (user activity) */
        CloseConnection(rudp);

        RUDP_STATE(rudp) = RUDP_CLOSED;
    }

    if (msg->hdr.flags & RUDP_SYN && !(msg->hdr.flags & RUDP_ACK))
    {
        ITS_TRACE_DEBUG(("TryListen: got SYN, !ACK\n"));

        ParseSYN(rudp, msg);

        /* save the IRS */
        RUDP_CPARAMS(rudp).irs = msg->hdr.seqNumber;

        if (!RcvdParamsOK(rudp, msg))
        {
            ComputeNegotiatedParams(rudp, msg);
        }

        RUDP_UPARAMS(rudp) = msg->hdrData.syn;
        RUDP_CPARAMS(rudp).rcvCur = msg->hdr.seqNumber;

        RUDP_REMOTE_CONN_ID(rudp) = RUDP_SYN_GET_CONN_ID(msg->hdrData.syn);

        ack = *msg;
        FormatSYN(rudp, &ack);

        ack.hdr.flags |= RUDP_ACK;
        ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
        ack.hdr.ackNumber = RUDP_CPARAMS(rudp).irs;
        ack.hdr.hdrLength = 0;
        
        ack.hdrLen = sizeof(RUDP_SYN_DATA);
        ack.dataLen = 0;

        /* send the SYN/ACK */
        ret = BuildMsg(rudp, &ack);

        if (ret != ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }

        ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

        if (ret != ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }

        timer.timerID = RUDP_T7;
        timer.connID = RUDP_LOCAL_CONN_ID(rudp);

        /* start autoReset timer */
        ITS_TRACE_DEBUG(("TryListen: Start AutoReset timer\n"));

        RUDP_AUTO_RESET(rudp) =
            TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                              TO_SECS(RUDP_CPARAMS(rudp).autoResetTimeout),
                              &timer, sizeof(timer));

        /* update state */
        RUDP_STATE(rudp) = RUDP_SYN_RCVD;
    }

    /* anything else is discarded */

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
TryAccept(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    RUDP_TimerContext timer;
    int ret;

    ITS_TRACE_DEBUG(("TryAccept\n"));

    /* is it a SYN? */
    if (msg->hdr.flags & RUDP_SYN)
    {
        ITS_RUDP_MSG ack;

        ITS_TRACE_DEBUG(("TryAccept: got SYN\n"));

        ParseSYN(rudp, msg);

        /* have we been ACKed? */
        if (msg->hdr.flags & RUDP_ACK)
        {
            ITS_TRACE_DEBUG(("TryAccept: got SYN, ACK\n"));

            /* check for bad ACK. */
            if (msg->hdrLen != sizeof(RUDP_SYN_DATA) ||
                msg->hdr.ackNumber != RUDP_CPARAMS(rudp).iss)
            {
                return (ITS_EPROTERR);
            }

            ITS_TRACE_DEBUG(("Stop AutoReset timer\n"));

            TIMERS_CancelTimer(RUDP_AUTO_RESET(rudp));

            /*
             * Check reuse bit: FIXME: mine, or his?
             */
            if (!(RUDP_UPARAMS(rudp).options & RUDP_SYN_OPT_REUSE))
            {
                ITS_TRACE_DEBUG(("TryAccept: No reuse\n"));

                if (!RcvdParamsOK(rudp, msg))
                {
                    ITS_TRACE_DEBUG(("TryAccept: Refuse connection\n"));

                    RefuseConnection(rudp, msg);

                    RUDP_STATE(rudp) = RUDP_CLOSED;

                    return (ITS_EPROTERR);
                }

                RUDP_UPARAMS(rudp) = msg->hdrData.syn;
                RUDP_CPARAMS(rudp).rcvCur = msg->hdr.seqNumber;

                RUDP_REMOTE_CONN_ID(rudp) = RUDP_SYN_GET_CONN_ID(msg->hdrData.syn);
            }

            /* set maxSyncAttempts */
            RUDP_CPARAMS(rudp).maxSyncAttempts = RUDP_UPARAMS(rudp).maxAutoReset;

            ITS_TRACE_DEBUG(("Stop OpenWait timer\n"));

            TIMERS_CancelTimer(RUDP_OPEN_WAIT(rudp));

            /* keepalive timer */
            if (RUDP_UPARAMS(rudp).nullSegTimeout)
            {
                ITS_TRACE_DEBUG(("TryAccept: Start KeepAlive\n"));

                timer.timerID = RUDP_T6;
                timer.connID = RUDP_LOCAL_CONN_ID(rudp);

                ITS_TRACE_DEBUG(("Start KeepAlive timer on accept, recv SYN/ACK\n"));

                RUDP_KEEPALIVE(rudp) =
                    TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                      TO_SECS(RUDP_UPARAMS(rudp).nullSegTimeout),
                                      &timer, sizeof(timer));
            }

            /* cumAck timer */
            timer.timerID = RUDP_T4;
            timer.connID = RUDP_LOCAL_CONN_ID(rudp);

            ITS_TRACE_DEBUG(("TryAccept: Start CumAck timer\n"));

            RUDP_CUM_ACK(rudp) =
                TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                  TO_SECS(RUDP_UPARAMS(rudp).cumAckTimeout),
                                  &timer, sizeof(timer));

            /* send standalone ACK */
            ack.hdr.flags = RUDP_ACK;
            ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
            ack.hdr.ackNumber = RUDP_CPARAMS(rudp).irs;
            ack.hdr.hdrLength = 0;

            ack.hdrLen = 0;
            ack.dataLen = 0;

            ret = BuildMsg(rudp, &ack);

            if (ret != ITS_SUCCESS)
            {
                return (ITS_EPROTERR);
            }

            ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

            if (ret != ITS_SUCCESS)
            {
                return (ITS_EPROTERR);
            }

            SendUserIndication(rudp, RUDP_MSG_CONN_OPEN);

            /* update state */
            RUDP_STATE(rudp) = RUDP_OPEN;
        }
        else
        {
            ITS_TRACE_DEBUG(("TryAccept: got SYN, !ACK\n"));

            /*
             * Spurious SYN (from race)
             */
            if (RUDP_CPARAMS(rudp).irs == msg->hdr.seqNumber)
            {
                ITS_TRACE_DEBUG(("TryAccept: Spurious SYN\n"));

                ack = *msg;
                FormatSYN(rudp, &ack);

                ack.hdr.flags |= RUDP_ACK;
                ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
                ack.hdr.ackNumber = RUDP_CPARAMS(rudp).irs;
                ack.hdr.hdrLength = 0;

                ack.hdrLen = sizeof(RUDP_SYN_DATA);
                ack.dataLen = 0;

                /* send the SYN/ACK */
                ret = BuildMsg(rudp, &ack);

                if (ret != ITS_SUCCESS)
                {
                    return (ITS_EPROTERR);
                }

                ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

                return (ret);
            }

            /* seqNumber != IRS */

            /*
             * Check reuse bit: FIXME: mine, or his?
             */
            if (!(RUDP_UPARAMS(rudp).options & RUDP_SYN_OPT_REUSE))
            {
                ITS_TRACE_DEBUG(("TryAccept: No reuse\n"));

                if (!RcvdParamsOK(rudp, msg))
                {
                    ComputeNegotiatedParams(rudp, msg);
                }

                RUDP_UPARAMS(rudp) = msg->hdrData.syn;
                RUDP_CPARAMS(rudp).rcvCur = msg->hdr.seqNumber;

                RUDP_REMOTE_CONN_ID(rudp) = RUDP_SYN_GET_CONN_ID(msg->hdrData.syn);
            }

            ack = *msg;
            FormatSYN(rudp, &ack);

            ack.hdr.flags |= RUDP_ACK;
            ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
            ack.hdr.ackNumber = RUDP_CPARAMS(rudp).irs;
            ack.hdr.hdrLength = 0;

            ack.hdrLen = sizeof(RUDP_SYN_DATA);
            ack.dataLen = 0;

            /* send the SYN/ACK */
            ret = BuildMsg(rudp, &ack);

            if (ret != ITS_SUCCESS)
            {
                return (ITS_EPROTERR);
            }

            ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

            if (ret != ITS_SUCCESS)
            {
                return (ITS_EPROTERR);
            }

            timer.timerID = RUDP_T7;
            timer.connID = RUDP_LOCAL_CONN_ID(rudp);

            /* start autoReset timer */
            ITS_TRACE_DEBUG(("Start AutoReset timer\n"));

            RUDP_AUTO_RESET(rudp) =
                TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                  TO_SECS(RUDP_CPARAMS(rudp).autoResetTimeout),
                                  &timer, sizeof(timer));

            /* update state */
            RUDP_STATE(rudp) = RUDP_SYN_RCVD;
        }

        return (ITS_SUCCESS);
    }

    /* see if it's a standalone ACK */
    if (msg->hdr.flags & RUDP_ACK && msg->hdr.ackNumber == RUDP_CPARAMS(rudp).iss)
    {
        ITS_TRACE_DEBUG(("TryAccept: got standalone ACK\n"));

        ITS_TRACE_DEBUG(("Stop OpenWait, AutoReset timer\n"));

        TIMERS_CancelTimer(RUDP_OPEN_WAIT(rudp));
        TIMERS_CancelTimer(RUDP_AUTO_RESET(rudp));

        /* set maxSyncAttempts */
        RUDP_CPARAMS(rudp).maxSyncAttempts = RUDP_UPARAMS(rudp).maxAutoReset;

        /* keepalive timer */
        if (RUDP_UPARAMS(rudp).nullSegTimeout)
        {
            timer.timerID = RUDP_T6;
            timer.connID = RUDP_LOCAL_CONN_ID(rudp);

            ITS_TRACE_DEBUG(("Start KeepAlive timer on accept, recv ACK\n"));

            RUDP_KEEPALIVE(rudp) =
                TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                  TO_SECS(RUDP_UPARAMS(rudp).nullSegTimeout) + 2, /* FIXME */
                                  &timer, sizeof(timer));
        }

        /* cumAck timer */
        timer.timerID = RUDP_T4;
        timer.connID = RUDP_LOCAL_CONN_ID(rudp);

        ITS_TRACE_DEBUG(("Start CumAck timer\n"));

        RUDP_CUM_ACK(rudp) =
            TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                              TO_SECS(RUDP_UPARAMS(rudp).cumAckTimeout),
                              &timer, sizeof(timer));

        SendUserIndication(rudp, RUDP_MSG_CONN_OPEN);

        /* update state */
        RUDP_STATE(rudp) = RUDP_OPEN;
    }

    /* Discard anything else. */
    ITS_TRACE_DEBUG(("Discarding message: flags %02x\n",
                     msg->hdr.flags));

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
OpenReceive(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_RUDP_MSG ack;
    int ret;
    RUDP_TimerContext timer;

    ITS_TRACE_DEBUG(("OpenReceive\n"));

    /* SYN w/o ACK */
    if (msg->hdr.flags & RUDP_SYN && !(msg->hdr.flags & RUDP_ACK))
    {
        ITS_TRACE_DEBUG(("OpenReceive: got SYN, !ACK\n"));

        ParseSYN(rudp, msg);

        /* check the reuse bit (FIXME: mine or his?) */
        if (!(RUDP_UPARAMS(rudp).options & RUDP_SYN_OPT_REUSE))
        {
            ITS_TRACE_DEBUG(("OpenReceive: No reuse\n"));

            RefuseConnection(rudp, msg);

            RUDP_STATE(rudp) = RUDP_CLOSED;

            return (ITS_EPROTERR);
        }

        /* FIXME: Cleanup connection */

        /* set IRS */
        RUDP_CPARAMS(rudp).irs = msg->hdr.seqNumber;

        /* reset ISS */

        /* send SYN/ACK */
        ack = *msg;
        FormatSYN(rudp, &ack);

        ack.hdr.flags |= RUDP_ACK;
        ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
        ack.hdr.ackNumber = RUDP_CPARAMS(rudp).irs;
        ack.hdr.hdrLength = 0;

        ack.hdrLen = sizeof(RUDP_SYN_DATA);
        ack.dataLen = 0;

        /* send the SYN/ACK */
        ret = BuildMsg(rudp, &ack);

        if (ret != ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }

        ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

        if (ret != ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }

        SendUserIndication(rudp, RUDP_MSG_CONN_RESET);

        timer.timerID = RUDP_T7;
        timer.connID = RUDP_LOCAL_CONN_ID(rudp);

        /* start autoReset timer */
        ITS_TRACE_DEBUG(("Start AutoReset timer\n"));

        RUDP_AUTO_RESET(rudp) =
            TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                              TO_SECS(RUDP_CPARAMS(rudp).autoResetTimeout),
                              &timer, sizeof(timer));

        /* update state */
        RUDP_STATE(rudp) = RUDP_SYN_RCVD;

        return (ITS_SUCCESS);
    }

    /* TCS w/o ACK */
    if (msg->hdr.flags & RUDP_TCS && !(msg->hdr.flags & RUDP_ACK))
    {
        ITS_UINT oldConnID;
        RUDP_Manager *ctxt;

        ITS_TRACE_DEBUG(("OpenReceive: got TCS, !ACK\n"));

        /* find old conn with recvd connID == connID */
        oldConnID = SOCK_NToHL(RUDP_TCS_GET_CONN_ID(msg->hdrData.tcs));

        ctxt = (RUDP_Manager *)TRANSPORT_FindTransport((ITS_USHORT)oldConnID);

        if (ctxt == NULL)
        {
            /* increment next seq num */
            RUDP_CPARAMS(rudp).sendNext++;

            ack.hdr.flags = RUDP_TCS | RUDP_ACK;
            ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
            ack.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
            ack.hdr.hdrLength = 0;

            ack.hdrLen = 0;
            ack.dataLen = 0;

            /* FIXME: send TCS/ACK, Trans indication set to conn unavail: HOW? */
            ack.hdrData.tcs.seqAdjFactor = 0;
            RUDP_TCS_SET_CONN_ID(ack.hdrData.tcs, SOCK_HToNL(0));

            /* send the TCS/ACK */
            ret = BuildMsg(rudp, &ack);

            if (ret != ITS_SUCCESS)
            {
                return (ITS_EPROTERR);
            }

            ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

            if (ret != ITS_SUCCESS)
            {
                return (ITS_EPROTERR);
            }

            AppendToRetransQueue(rudp, &ack);

            return (ITS_EPROTERR);
        }

        /* have old connection. */
        SendUserIndication(ctxt, RUDP_MSG_CONN_TRANS_STATE);
        
        /* note state change */
        RUDP_STATE(ctxt) = RUDP_TRANSFER;

        TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);

        /* update new conn */
        SendUserIndication(rudp, RUDP_MSG_CONN_TRANS_STATE);

        SendACKOrEACK(rudp);
        RUDP_TRANSFER_CONN_ID(rudp) = RUDP_LOCAL_CONN_ID(ctxt);

        /* start transfer state timer */
        ITS_TRACE_DEBUG(("Start TransferState timer\n"));

        timer.timerID = RUDP_T5;
        RUDP_TRANSFER_STATE(rudp) =
            TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                              TO_SECS(RUDP_UPARAMS(rudp).transStateTimeout),
                              &timer, sizeof(timer));

        /* retrans queue empty? */
        if (RetransQueueEmpty(rudp))
        {
            TransferState(rudp);
        }

        RUDP_STATE(rudp) = RUDP_TRANSFER;

        return (ITS_SUCCESS);
    }

    /* NUL msg */
    if (msg->hdr.flags & RUDP_NUL)
    {
        ITS_TRACE_DEBUG(("OpenReceive: got NUL\n"));

        /* valid sequence: FIXME what does this mean? */
        if (!ValidSeqNum(rudp, msg))
        {
            ITS_TRACE_DEBUG(("OpenReceive: bad sequence num\n"));

            return (ITS_EPROTERR);
        }

        /* in sequence? */
        if (!InSequence(rudp, msg))
        {
            ITS_TRACE_DEBUG(("OpenReceive: sequence num OOS\n"));

            return (ITS_EPROTERR);
        }

        RUDP_CPARAMS(rudp).rcvCur = msg->hdr.seqNumber;

        /* passive connection? */
        if (!RUDP_IS_ACTIVE(rudp))
        {
            ITS_TRACE_DEBUG(("Stop KeepAlive timer\n"));

            TIMERS_CancelTimer(RUDP_KEEPALIVE(rudp));

            timer.timerID = RUDP_T6;
            timer.connID = RUDP_LOCAL_CONN_ID(rudp);

            ITS_TRACE_DEBUG(("Start KeepAlive timer, open receive NUL\n"));

            RUDP_KEEPALIVE(rudp) =
                TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                  TO_SECS(RUDP_UPARAMS(rudp).nullSegTimeout) + 2, /* FIXME */
                                  &timer, sizeof(timer));
        }

        ITS_TRACE_DEBUG(("OpenReceive: sending ACK\n"));

        /* Send standalone ACK */
        ack.hdr.flags = RUDP_ACK;
        ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
        ack.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
        ack.hdr.hdrLength = 0;

        ack.hdrLen = 0;
        ack.dataLen = 0;

        /* send the ACK */
        ret = BuildMsg(rudp, &ack);

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }

        ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }

        ITS_TRACE_DEBUG(("Stop CumAck timer\n"));

        TIMERS_CancelTimer(RUDP_CUM_ACK(rudp));

        RUDP_CPARAMS(rudp).cumAckCount = 0;

        timer.timerID = RUDP_T4;
        timer.connID = RUDP_LOCAL_CONN_ID(rudp);

        ITS_TRACE_DEBUG(("Start CumAck timer\n"));

        RUDP_CUM_ACK(rudp) =
            TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                              TO_SECS(RUDP_UPARAMS(rudp).cumAckTimeout),
                              &timer, sizeof(timer));

        ProcessACK(rudp, msg);

        return (ITS_SUCCESS);
    }

    /* RST ? */
    if (msg->hdr.flags & RUDP_RST && !(msg->hdr.flags & RUDP_ACK) &&
        ValidSeqNum(rudp, msg))
    {
        ITS_TRACE_DEBUG(("OpenReceive: got RST, !ACK\n"));

        ack.hdr.flags = RUDP_ACK;
        ack.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
        ack.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
        ack.hdr.hdrLength = 0;

        ack.hdrLen = 0;
        ack.dataLen = 0;

        /* send the ACK */
        ret = BuildMsg(rudp, &ack);

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }

        ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }

        /* start close wait */
        ITS_TRACE_DEBUG(("Start CloseWait timer\n"));

        timer.timerID = RUDP_T2;
        timer.connID = RUDP_LOCAL_CONN_ID(rudp);
        RUDP_OPEN_CLOSE(rudp) =
            TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                              TO_SECS(RUDP_CPARAMS(rudp).openCloseTimeout),
                              &timer, sizeof(timer));

        SendUserIndication(rudp, RUDP_MSG_CONN_CLOSING);

        /* update state */
        RUDP_STATE(rudp) = RUDP_CLOSE_WAIT;

        return (ITS_SUCCESS);
    }

    /* valid seq num? */
    if (ValidSeqNum(rudp, msg))
    {
        ITS_TRACE_DEBUG(("OpenReceive: got data or ACK\n"));

        if (!RUDP_IS_ACTIVE(rudp))
        {
            ITS_TRACE_DEBUG(("OpenReceive: Stop KeepAlive timer\n"));

            TIMERS_CancelTimer(RUDP_KEEPALIVE(rudp));

            timer.timerID = RUDP_T6;
            timer.connID = RUDP_LOCAL_CONN_ID(rudp);

            ITS_TRACE_DEBUG(("Start KeepAlive timer, open receive data\n"));

            RUDP_KEEPALIVE(rudp) =
                TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                  TO_SECS(RUDP_UPARAMS(rudp).nullSegTimeout) + 2, /* FIXME */
                                  &timer, sizeof(timer));
        }

        ProcessACK(rudp, msg);

        ProcessEACK(rudp, msg);

        ProcessMsgData(rudp, msg);

        return (ITS_SUCCESS);
    }

    /* discard anything else */
    ITS_TRACE_DEBUG(("Discarding message: flags %02x\n",
                     msg->hdr.flags));

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
PerformTransfer(RUDP_Manager *rudp, ITS_USHORT connID)
{
    RUDP_Manager *ctxt;
    ITS_RUDP_MSG tcs;
    RUDP_TimerContext timer;
    int ret;

    ITS_TRACE_DEBUG(("PerformTransfer\n"));

    SendUserIndication(rudp, RUDP_MSG_CONN_TRANS_STATE);

    RUDP_STATE(rudp) = RUDP_TRANSFER;

    ctxt = (RUDP_Manager *)TRANSPORT_FindTransport(connID);

    SendUserIndication(ctxt, RUDP_MSG_CONN_TRANS_STATE);

    /* inc next seq num */
    RUDP_CPARAMS(ctxt).sendNext++;

    /* send tcs */
    tcs.hdr.flags = RUDP_TCS;
    tcs.hdr.seqNumber = RUDP_CPARAMS(ctxt).sendNext;
    tcs.hdr.ackNumber = RUDP_CPARAMS(ctxt).rcvCur;
    tcs.hdr.hdrLength = 0;

    tcs.hdrLen = sizeof(RUDP_TCS_DATA);
    tcs.dataLen = 0;

    tcs.hdrData.tcs.seqAdjFactor = 0;
    RUDP_TCS_SET_CONN_ID(tcs.hdrData.tcs, SOCK_HToNL(RUDP_LOCAL_CONN_ID(ctxt)));

    /* send the ACK */
    ret = BuildMsg(ctxt, &tcs);

    if (ret != ITS_SUCCESS)
    {
        TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);

        return;
    }

    ret = sendMsg(ctxt,
                    RUDP_SEND_BUF(ctxt),
                    RUDP_CUR_SEND_SEG_SIZE(ctxt));

    if (ret != ITS_SUCCESS)
    {
        TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);

        return;
    }

    /* add it to retransmit queue */
    AppendToRetransQueue(ctxt, &tcs);

    /* send ACK or EACK. */
    SendACKOrEACK(ctxt);

    ITS_TRACE_DEBUG(("Start TransferState timer\n"));

    timer.timerID = RUDP_T5;
    timer.connID = RUDP_LOCAL_CONN_ID(ctxt);
    RUDP_TRANSFER_STATE(ctxt) =
        TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                          TO_SECS(RUDP_UPARAMS(ctxt).transStateTimeout),
                          &timer, sizeof(timer));

    RUDP_STATE(ctxt) = RUDP_TRANSFER;

    TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);
}

/*.implementation:extern
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
TransferReceive(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    int ret;
    RUDP_Manager *ctxt;

    ITS_TRACE_DEBUG(("TransferReceive\n"));

    /* is it a TCS? */
    if (msg->hdr.flags & RUDP_TCS)
    {
        if (!(msg->hdr.flags & RUDP_ACK))
        {
            ITS_UINT connID;

            connID = SOCK_NToHL(RUDP_TCS_GET_CONN_ID(msg->hdrData.tcs));

            if (connID != RUDP_TRANSFER_CONN_ID(rudp))
            {
                ITS_RUDP_MSG tcs;

                ctxt = (RUDP_Manager *)
                        TRANSPORT_FindTransport((ITS_USHORT)RUDP_TRANSFER_CONN_ID(rudp));

                tcs.hdr.flags = RUDP_TCS | RUDP_ACK;
                tcs.hdr.seqNumber = RUDP_CPARAMS(ctxt).sendNext;
                tcs.hdr.ackNumber = RUDP_CPARAMS(ctxt).rcvCur;
                tcs.hdr.hdrLength = 0;

                tcs.hdrData.tcs.seqAdjFactor = 0;
                RUDP_TCS_SET_CONN_ID(tcs.hdrData.tcs, SOCK_HToNL(RUDP_LOCAL_CONN_ID(rudp)));

                tcs.hdrLen = sizeof(RUDP_TCS_DATA);
                tcs.dataLen = 0;

                /* send the TCS */
                ret = BuildMsg(rudp, &tcs);

                if (ret != ITS_SUCCESS)
                {
                    TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);

                    return;
                }

                ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

                if (ret != ITS_SUCCESS)
                {
                    TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);

                    return;
                }

                RUDP_STATE(rudp) = RUDP_OPEN;

                SendUserIndication(rudp, RUDP_MSG_CONN_TRANS_FAIL);

                SendUserIndication(ctxt, RUDP_MSG_CONN_TRANS_FAIL);

                /* FIXME: Assume "oldConn" means saved transfer connID */
                CloseOrResetConnection(ctxt);

                TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);

                return;
            }

            /* IDs match */
            /* FIXME: What does "set ok to send flag" mean */
            RUDP_CPARAMS(rudp).okToSend = ITS_TRUE;

            /* Is retrans queue emtpy? */
            /* retrans queue empty? */
            if (RetransQueueEmpty(rudp))
            {
                TransferState(rudp);
            }

            return;
        }
        else
        {
            ITS_OCTET seqAdjFactor;
            /* FIXME: Why aren't I using this? 
            ITS_UINT connID = SOCK_NToHL(RUDP_TCS_GET_CONN_ID(msg->hdrData.tcs));
             */

            ctxt = (RUDP_Manager *)
                    TRANSPORT_FindTransport((ITS_USHORT)RUDP_TRANSFER_CONN_ID(rudp));

            /* ACK is set */
            if (msg->hdrData.tcs.spare == 0) /* FIXME: Where are the error values? */
            {
                SendUserIndication(rudp, RUDP_MSG_CONN_TRANS_FAIL);

                RUDP_STATE(rudp) = RUDP_OPEN;

                SendUserIndication(ctxt, RUDP_MSG_CONN_TRANS_FAIL);

                /* FIXME: Assume "oldConn" means saved transfer connID */
                CloseOrResetConnection(ctxt);

                TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);

                return;
            }

            seqAdjFactor = msg->hdrData.tcs.seqAdjFactor;

            /*
             * Move all segs on OOS and RECV queues to new conn,
             * adjusting seq nums.  Discard duplicate segs.
             */
            TransferAllSegs(ctxt, rudp, seqAdjFactor);

            /*
             * set rcvCur += rcvSeqAdjust
             */
            RUDP_CPARAMS(rudp).rcvCur += seqAdjFactor;

            SendACKOrEACK(rudp);

            /* set recvTransferComplete */
            RUDP_CPARAMS(rudp).recvTransferDone = ITS_TRUE;

            /* set okToSend */
            RUDP_CPARAMS(rudp).okToSend = ITS_TRUE;

            if (!RUDP_CPARAMS(rudp).sendTransferDone)
            {
                if (!RetransQueueEmpty(rudp))
                {
                    return;
                }

                TransferState(rudp);
            }

            SendUserIndication(rudp, RUDP_MSG_CONN_OPEN);

            RUDP_STATE(rudp) = RUDP_OPEN;

            CloseOrResetConnection(ctxt);

            TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);
        }

        return;
    }

    /* other message */
    if (ValidSeqNum(rudp, msg))
    {
        ProcessACK(rudp, msg);

        ProcessEACK(rudp, msg);

        ProcessMsgData(rudp, msg);

        if (!RetransQueueEmpty(rudp))
        {
            return;
        }

        if (RUDP_CPARAMS(rudp).transferInitiator)
        {
            if (!RUDP_CPARAMS(rudp).okToSend)
            {
                return;
            }
        }

        TransferState(rudp);

        if (!RUDP_CPARAMS(rudp).recvTransferDone)
        {
            return;
        }

        SendUserIndication(rudp, RUDP_MSG_CONN_OPEN);

        RUDP_STATE(rudp) = RUDP_OPEN;

        ctxt = (RUDP_Manager *)
                TRANSPORT_FindTransport((ITS_USHORT)RUDP_TRANSFER_CONN_ID(rudp));

        CloseOrResetConnection(ctxt);

        TRANSPORT_UnfindTransport((TRANSPORT_Control *)ctxt);
    }
}

/*.implementation:extern
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
WaitReceive(RUDP_Manager *rudp, ITS_RUDP_MSG *msg)
{
    ITS_TRACE_DEBUG(("WaitRecieve\n"));

    if (msg->hdr.flags & RUDP_SYN ||
        msg->hdr.flags & RUDP_RST ||
        msg->hdr.flags & RUDP_NUL)
    {
        return;
    }

    if (ValidSeqNum(rudp, msg))
    {
        ProcessACK(rudp, msg);

        ProcessEACK(rudp, msg);

        ProcessMsgData(rudp, msg);
    }
}

/*.implementation:extern
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
Close(RUDP_Manager *rudp)
{
    int ret;
    ITS_RUDP_MSG rst;

    ITS_TRACE_DEBUG(("Close\n"));

    switch (RUDP_STATE(rudp))
    {
    case RUDP_IDLE:
        return;

    case RUDP_SYN_SENT:
        rst.hdr.flags = RUDP_RST;
        rst.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
        rst.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
        rst.hdr.hdrLength = 0;

        rst.hdrLen = 0;
        rst.dataLen = 0;

        /* send the RST */
        ret = BuildMsg(rudp, &rst);

        if (ret != ITS_SUCCESS)
        {
            return;
        }

        ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

        if (ret != ITS_SUCCESS)
        {
            return;
        }

        SendUserIndication(rudp, RUDP_MSG_CONN_RESET);

        /* Cleanup connection (user activity) */

        /* Close connection (user activity) */
        CloseConnection(rudp);

        /* update state */
        RUDP_STATE(rudp) = RUDP_CLOSED;
        
        break;

    case RUDP_OPEN:
        EnterCloseWait(rudp);
        RUDP_STATE(rudp) = RUDP_CLOSE_WAIT;
        break;

    case RUDP_CONN_FAIL:
        EnterCloseWait(rudp);
        RUDP_STATE(rudp) = RUDP_CLOSE_WAIT;
        break;

    default:
        ITS_TRACE_CRITICAL(("Close: Bad state for close\n"));
        break;
    }
}

/*.implementation:extern
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
OpenSend(RUDP_Manager *rudp, ITS_OCTET *data, ITS_USHORT count)
{
    RUDP_TimerContext timer;
    ITS_RUDP_MSG    snd;
    int ret;

    ITS_TRACE_DEBUG(("OpenSend\n"));

    /* room in the send window? */
    if (!(RUDP_SEND_QUEUE_COUNT(rudp) < RUDP_UPARAMS(rudp).maxNumSegsPending))
    {
        /* Send error to the application */
        SendUserIndication(rudp, RUDP_MSG_SEND_OVERFLOW);

        return;
    }

    /* make sure we do this here.  Otherwise we won't store
     * the right seq number, and ProcessACK will barf.
     */
    RUDP_CPARAMS(rudp).sendNext++;

    /* is there a segment being timed? */
    if (RUDP_SEND_QUEUE_COUNT(rudp) == 0)
    {
        ITS_TRACE_DEBUG(("OpenSend: Set timed segment\n"));

        RUDP_CPARAMS(rudp).timedAck = RUDP_CPARAMS(rudp).sendNext;

        /* start retransmit timer */
        timer.timerID = RUDP_T3;
        timer.connID = RUDP_LOCAL_CONN_ID(rudp);

        ITS_TRACE_DEBUG(("OpenSend: Start Retransmit timer:\n"));

        RUDP_RETRANS(rudp) =
            TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                              TO_SECS(RUDP_UPARAMS(rudp).retransTimeout),
                              &timer, sizeof(timer));

        ITS_TRACE_DEBUG(("rudp %08x conn %04x timer %08x\n",
                    rudp, timer.connID, RUDP_RETRANS(rudp)));
    }

    /* passive? */
    if (RUDP_IS_ACTIVE(rudp))
    {
        ITS_TRACE_DEBUG(("Stop KeepAlive timer\n"));

        TIMERS_CancelTimer(RUDP_KEEPALIVE(rudp));

        timer.timerID = RUDP_T6;
        timer.connID = RUDP_LOCAL_CONN_ID(rudp);

        ITS_TRACE_DEBUG(("Start KeepAlive timer, open send\n"));

        RUDP_KEEPALIVE(rudp) =
            TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                              TO_SECS(RUDP_UPARAMS(rudp).nullSegTimeout),
                              &timer, sizeof(timer));
    }

    /* Reset CumAck Timer and count */
    ITS_TRACE_DEBUG(("Stop CumAck timer\n"));

    TIMERS_CancelTimer(RUDP_CUM_ACK(rudp));
    RUDP_CPARAMS(rudp).cumAckCount = 0;

    timer.timerID = RUDP_T4;
    timer.connID = RUDP_LOCAL_CONN_ID(rudp);

    ITS_TRACE_DEBUG(("Start CumAck timer\n"));

    RUDP_CUM_ACK(rudp) =
        TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                          TO_SECS(RUDP_UPARAMS(rudp).cumAckTimeout),
                          &timer, sizeof(timer));

    /* build message */
    snd.hdr.flags = RUDP_ACK;
    snd.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
    snd.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
    snd.hdr.hdrLength = 0;

    snd.hdrLen = 0;
    snd.dataLen = count;
    memcpy(snd.userData, data, count);

    /* send the ACK/data */
    ret = BuildMsg(rudp, &snd);

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

    if (ret != ITS_SUCCESS)
    {
        return;
    }

    /* add to tx queue. */
    AppendToRetransQueue(rudp, &snd);
}

/*.implementation:extern
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
HandleTimeout(ITS_EVENT* timeout)
{
    ITS_TimerData *td = (ITS_TimerData *)timeout->data;
    RUDP_TimerContext *timer = (RUDP_TimerContext *)td->context;
    RUDP_Manager *rudp;
    int ret;

    ITS_TRACE_DEBUG(("Handle timeout:\n"));

    rudp = (RUDP_Manager *)TRANSPORT_FindTransport((ITS_USHORT)timer->connID);

    if (rudp == NULL)
    {
        ITS_TRACE_ERROR(("HandleTimeout: Couldn't find transport %04x\n",
                         timer->connID));

        return;
    }

    if (MUTEX_AcquireMutex(&RUDP_LOCK(rudp)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("HandleTimeout: Couldn't lock transport %04x\n",
                         timer->connID));
    }

    switch (timer->timerID)
    {
    case RUDP_T1:   /* OpenWait */
        ITS_TRACE_DEBUG(("OpenWait timer\n"));

        if ((RUDP_STATE(rudp) == RUDP_SYN_SENT ||
             RUDP_STATE(rudp) == RUDP_SYN_RCVD) &&
            td->serial == RUDP_OPEN_WAIT(rudp))
        {
            if (RUDP_CPARAMS(rudp).openWaitCount >= RUDP_CPARAMS(rudp).maxSyncAttempts)
            {
                SendUserIndication(rudp, RUDP_MSG_CONN_RESET);

                /* Cleanup connection (user activity) */

                /* Close connection (user activity) */
                CloseConnection(rudp);

                RUDP_STATE(rudp) = RUDP_CLOSED;

                MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                return;
            }
            else
            {
                Connect(rudp);
            }
        }
        else
        {
            ITS_TRACE_WARNING(("Discarding T1 for state %d\n",
                               RUDP_STATE(rudp)));
        }
        break;

    case RUDP_T2:   /* OpenClose */
        ITS_TRACE_DEBUG(("OpenClose timer\n"));

        if (RUDP_STATE(rudp) == RUDP_CLOSE_WAIT &&
            td->serial == RUDP_OPEN_CLOSE(rudp))
        {
            SendUserIndication(rudp, RUDP_MSG_CONN_RESET);

            /* Cleanup connection (user activity) */

            /* Close connection (user activity) */
            CloseConnection(rudp);

            RUDP_STATE(rudp) = RUDP_CLOSED;
        }
        break;

    case RUDP_T3:   /* Retransmit */
        ITS_TRACE_DEBUG(("Retransmit timer: serial %08x\n", td->serial));

        if (RUDP_STATE(rudp) == RUDP_OPEN &&
            td->serial == RUDP_RETRANS(rudp))
        {
            RUDP_TimerContext timer;

            RUDP_CPARAMS(rudp).retransCount++;

            if (RUDP_CPARAMS(rudp).retransCount < RUDP_UPARAMS(rudp).maxRetrans)
            {
                int i;

                /* Retransmit everything on queue */
                for (i = 0; i < RUDP_SEND_QUEUE_COUNT(rudp); i++)
                {
                    ret = BuildMsg(rudp, RUDP_SEND_QUEUE(rudp)[i]);

                    if (ret != ITS_SUCCESS)
                    {
                        MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                        TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                        return;
                    }

                    ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

                    if (ret != ITS_SUCCESS)
                    {
                        MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                        TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                        return;
                    }
                }

                timer.timerID = RUDP_T3;
                timer.connID = RUDP_LOCAL_CONN_ID(rudp);

                ITS_TRACE_DEBUG(("Start Retransmit timer\n"));

                RUDP_RETRANS(rudp) =
                    TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                      TO_SECS(RUDP_UPARAMS(rudp).retransTimeout),
                                      &timer, sizeof(timer));

                MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                return;
            }

            if (RUDP_UPARAMS(rudp).transStateTimeout == 0)
            {
                CloseOrResetConnection(rudp);

                MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                return;
            }

            ITS_TRACE_DEBUG(("Send user CONN_FAIL\n"));

            SendUserIndication(rudp, RUDP_MSG_CONN_FAILURE);

            timer.timerID = RUDP_T5;
            timer.connID = RUDP_LOCAL_CONN_ID(rudp);

            ITS_TRACE_DEBUG(("Start TransferState timer\n"));

            RUDP_TRANSFER_STATE(rudp) =
                TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                  TO_SECS(RUDP_UPARAMS(rudp).transStateTimeout),
                                  &timer, sizeof(timer));

            RUDP_STATE(rudp) = RUDP_CONN_FAIL;
        }
        else if (RUDP_STATE(rudp) == RUDP_TRANSFER)
        {
            RUDP_TimerContext timer;

            RUDP_CPARAMS(rudp).retransCount++;

            if (RUDP_CPARAMS(rudp).retransCount < RUDP_UPARAMS(rudp).maxRetrans)
            {
                int i;

                /* Retransmit everything on queue */
                for (i = 0; i < RUDP_SEND_QUEUE_COUNT(rudp); i++)
                {
                    ret = BuildMsg(rudp, RUDP_SEND_QUEUE(rudp)[i]);

                    if (ret != ITS_SUCCESS)
                    {
                        MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                        TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                        return;
                    }

                    ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

                    if (ret != ITS_SUCCESS)
                    {
                        MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                        TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                        return;
                    }
                }

                timer.timerID = RUDP_T3;
                timer.connID = RUDP_LOCAL_CONN_ID(rudp);

                ITS_TRACE_DEBUG(("Start Retransmit timer\n"));

                RUDP_RETRANS(rudp) =
                    TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                      TO_SECS(RUDP_UPARAMS(rudp).retransTimeout),
                                      &timer, sizeof(timer));

                MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                return;
            }

            CloseOrResetConnection(rudp);
        }
        else if (RUDP_STATE(rudp) == RUDP_CLOSE_WAIT)
        {
            RUDP_TimerContext timer;

            RUDP_CPARAMS(rudp).retransCount++;

            if (RUDP_CPARAMS(rudp).retransCount < RUDP_UPARAMS(rudp).maxRetrans)
            {
                int i;

                /* Retransmit everything on queue */
                for (i = 0; i < RUDP_SEND_QUEUE_COUNT(rudp); i++)
                {
                    ret = BuildMsg(rudp, RUDP_SEND_QUEUE(rudp)[i]);

                    if (ret != ITS_SUCCESS)
                    {
                        MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                        TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                        return;
                    }

                    ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

                    if (ret != ITS_SUCCESS)
                    {
                        MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                        TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                        return;
                    }
                }

                timer.timerID = RUDP_T3;
                timer.connID = RUDP_LOCAL_CONN_ID(rudp);

                ITS_TRACE_DEBUG(("Start Retransmit timer\n"));

                RUDP_RETRANS(rudp) =
                    TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                      TO_SECS(RUDP_UPARAMS(rudp).retransTimeout),
                                      &timer, sizeof(timer));

                MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                return;
            }
            else
            {
                SendUserIndication(rudp, RUDP_MSG_CONN_RESET);

                /* Cleanup connection (user activity) */

                /* Close connection (user activity) */
                CloseConnection(rudp);

                RUDP_STATE(rudp) = RUDP_CLOSED;
            }
        }
        break;

    case RUDP_T4:   /* CumulativeAck */
        ITS_TRACE_DEBUG(("CumAck timer\n"));

        if (RUDP_STATE(rudp) == RUDP_OPEN)
        {
            SendACKOrEACK(rudp);
        }
        break;

    case RUDP_T5:   /* TransferState */
        ITS_TRACE_DEBUG(("TransferState timer\n"));

        if (RUDP_STATE(rudp) == RUDP_CONN_FAIL)
        {
            CloseOrResetConnection(rudp);
        }
        break;

    case RUDP_T6:   /* KeepAlive */
        ITS_TRACE_DEBUG(("KeepAlive timer\n"));

        if (RUDP_STATE(rudp) == RUDP_OPEN)
        {
            ITS_RUDP_MSG nul;
            RUDP_TimerContext timer;

            if (!RUDP_IS_ACTIVE(rudp))
            {
                CloseOrResetConnection(rudp);

                MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                return;
            }

            /* active connection, send NUL */
            RUDP_CPARAMS(rudp).sendNext++;

            nul.hdr.flags = RUDP_NUL | RUDP_ACK;
            nul.hdr.seqNumber = RUDP_CPARAMS(rudp).sendNext;
            nul.hdr.ackNumber = RUDP_CPARAMS(rudp).rcvCur;
            nul.hdr.hdrLength = 0;

            nul.hdrLen = 0;
            nul.dataLen = 0;

            /* send the NUL */
            ret = BuildMsg(rudp, &nul);

            if (ret != ITS_SUCCESS)
            {
                MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                return;
            }

            ret = sendMsg(rudp, RUDP_SEND_BUF(rudp), RUDP_CUR_SEND_SEG_SIZE(rudp));

            if (ret != ITS_SUCCESS)
            {
                MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);

                return;
            }

            timer.timerID = RUDP_T6;
            timer.connID = RUDP_LOCAL_CONN_ID(rudp);

            ITS_TRACE_DEBUG(("Start KeepAlive timer, after timeout\n"));

            /* FIXME: SDL doesn't include this */
            RUDP_KEEPALIVE(rudp) =
                TIMERS_StartTimer(RUDP_MANAGER_INSTANCE,
                                  TO_SECS(RUDP_UPARAMS(rudp).nullSegTimeout),
                                  &timer, sizeof(timer));

            /* add to tx queue. */
            AppendToRetransQueue(rudp, &nul);
        }

        break;

    case RUDP_T7:   /* AutoReset */
        ITS_TRACE_DEBUG(("AutoReset timer\n"));

        if (RUDP_STATE(rudp) == RUDP_SYN_RCVD)
        {
            SendUserIndication(rudp, RUDP_MSG_CONN_RESET);

            /* Cleanup connection (user activity) */

            /* Close connection (user activity) */
            CloseConnection(rudp);

            RUDP_STATE(rudp) = RUDP_CLOSED;
        }
        break;

    default:
        ITS_TRACE_ERROR(("Unknown timer id: %d\n", timer->timerID));
        break;
    }

    MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

    TRANSPORT_UnfindTransport((TRANSPORT_Control *)rudp);
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
RUDP_Thread(void *arg)
{
    ITS_EVENT rudpEvent;
    ITS_BOOLEAN cont;

    cont = ITS_TRUE;

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__RUDP_RcvQueue))
                                                        (__RUDP_RcvQueue,
                                                        &rudpEvent)
           == ITS_SUCCESS)
    {
        switch (rudpEvent.src)
        {
        /* handle timeout */
        case ITS_TIMER_SRC:
            HandleTimeout(&rudpEvent);
            break;

        case RUDP_MANAGER_INSTANCE:
            ITS_TRACE_CRITICAL(("RUDP_Main: termination event.\n"));
            cont = ITS_FALSE;
            break;

        default:
            ITS_TRACE_DEBUG(("RUDP_Main: Unknown event source: %04x.\n",
                             rudpEvent.src));
            break;
        }
    }

    THREAD_NORMAL_EXIT;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the RUDP class.
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
 *      ITS_SUCCESS
 *
 *  Notes:
 *
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    if ((__RUDP_RcvQueue = TQUEUETRAN_CreateTransport("RUDP Manager",
                                                       RUDP_MANAGER_INSTANCE,
                                                       0)) == NULL)
    {
        ITS_TRACE_CRITICAL(("RUDP_Init: Couldn't create RUDP manager"
                            "transport.\n"));

        return (ITS_ENOTRANSPORT);
    }

    if (THREAD_CreateThread(&rudpThread, 0, RUDP_Thread, NULL, ITS_TRUE)
        != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("RUDP_Init: Couldn't create RUDP thread.\n"));

        TQUEUETRAN_DeleteTransport(__RUDP_RcvQueue);

        return (ITS_EBADTHREAD);
    }

    ITS_TRACE_CRITICAL(("RUDP_Initialize: initialization successful\n"));

    ITS_CLASS_SUPERCLASS(itsRUDPTRAN_LocalClass) =
            (ITS_Class)&itsSOCKTRAN_LocalEndPointClassRec;
    ITS_CLASS_SUPERCLASS(itsRUDPTRAN_RemoteClass) =
            (ITS_Class)&itsSOCKTRAN_RemoteEndPointClassRec;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the RUDP class.
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
 *      a constant pointer to the application name
 *
 *  Notes:
 *
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
    ITS_EVENT ev;
    void *status;

    ITS_TRACE_CRITICAL(("RUDP_Terminate.\n"));

    ev.src = RUDP_MANAGER_INSTANCE;
    ev.len = 0;

    TRANSPORT_PutEvent(RUDP_MANAGER_INSTANCE, &ev);

    THREAD_WaitForThread(&rudpThread, &status);

    THREAD_DeleteThread(&rudpThread);

    ITS_C_ASSERT(__RUDP_RcvQueue != NULL);

    TQUEUETRAN_DeleteTransport(__RUDP_RcvQueue);
}

/*
 * RUDP class record
 */
RUDPDLLAPI RUDP_ClassRec itsRUDP_ClassRec =
{
    /* core part */
    {
        NULL,                           /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        RUDP_CLASS_NAME,                /* class name */
        ClassInitialize,                /* class init */
        ClassDestroy,                   /* class destroy */
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

RUDPDLLAPI ITS_Class itsRUDP_Class = (ITS_Class)&itsRUDP_ClassRec;

/*.implementation:extern
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
void
RUDPDLLAPI RUDP_InitParams(RUDP_EndPointParams* params)
{
    memset(params, 0, sizeof(RUDP_EndPointParams));

    params->maxNumSegsPending = RUDP_SYN_MAX_SEGS_PEND_DEFAULT;
    params->options = 0;
    params->maxSegmentSize = RUDP_SYN_MAX_SEG_SIZE_DEFAULT;
    params->retransTimeout = RUDP_SYN_DEFAULT_RETRANS_TIMEOUT;
    params->cumAckTimeout = RUDP_SYN_DEFAULT_CUM_ACK_TIMEOUT;
    params->nullSegTimeout = RUDP_SYN_NULL_SEG_TIMEOUT_DEFAULT;
    params->transStateTimeout = RUDP_SYN_TRANS_STATE_TIMEOUT_DEFAULT;
    params->maxRetrans = RUDP_SYN_RETRANS_DEFAULT;
    params->maxCumAck = RUDP_SYN_CUM_ACK_DEPTH_DEFAULT;
    params->maxOOS = RUDP_SYN_OOS_ACK_DEPTH_DEFAULT;
    params->maxAutoReset = RUDP_SYN_AUTO_RESET_DEPTH_DEFAULT;
}

/*.implementation:extern
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
 *      Both sides of a connection call Create.  The determination of whether
 *      they are active or passive depends on whether or not they call
 *      Connect or Accept.  Note that anonymous binding is ok for either
 *      side, but makes little sense for the server as the client won't
 *      know a priori which address to use.  Anonymous binding is
 *      accomplished by passing "255.255.255.255", 0 to SOCK_EndPointOpen.
 *
 *  See Also:
 ****************************************************************************/
static int
Create(ITS_Object obj, va_list args)
{
    RUDP_Manager *rudp = (RUDP_Manager *)obj;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;
    RUDP_EndPointParams *params;
    ITS_CALLBACK callback;
    ITS_BOOLEAN isActive;

    ITS_TRACE_DEBUG(("Create:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);
    params = va_arg(args, RUDP_EndPointParams *);
    callback = va_arg(args, ITS_CALLBACK);
    isActive = va_arg(args, ITS_BOOLEAN);

    /* local reference for this puppy */
    RUDP_LOCAL_CONN_ID(rudp) = instance;

    /* allocate the callback list */
    if ((RUDP_CALLBACKS(rudp) = CALLBACK_InitManager()) == NULL)
    {
        ITS_TRACE_ERROR(("Create: Couldn't create callback manager.\n"));

        return (ITS_ENOMEM);
    }

    /* add the user's callback */
    if (callback)
    {
        if (CALLBACK_AddCallback(RUDP_CALLBACKS(rudp),
                                 callback,
                                 (ITS_POINTER)rudp) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("Create: Couldn't add callback.\n"));

            CALLBACK_DestroyManager(RUDP_CALLBACKS(rudp));

            return (ITS_ENOMEM);
        }
    }

    if (MUTEX_CreateMutex(&RUDP_LOCK(rudp), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Create: Couldn't create mutex.\n"));

        CALLBACK_DestroyManager(RUDP_CALLBACKS(rudp));

        return (ITS_ENOMEM);
    }

    RUDP_STATE(rudp) = RUDP_IDLE;

    if (params)
    {
        RUDP_UPARAMS(rudp) = *params;
    }
    else
    {
        RUDP_InitParams(&RUDP_UPARAMS(rudp));
    }

    srand(TIMERS_Time());

    RUDP_CPARAMS(rudp).maxOpenAttempts = 5;
    RUDP_CPARAMS(rudp).maxSyncAttempts = 0;
    RUDP_CPARAMS(rudp).syncAttemptCount = 0;
    RUDP_CPARAMS(rudp).iss = rand() % 256;
    RUDP_CPARAMS(rudp).sendNext = RUDP_CPARAMS(rudp).iss;
    RUDP_CPARAMS(rudp).rcvCur = 0;
    RUDP_CPARAMS(rudp).irs = 0;
    RUDP_CPARAMS(rudp).timedAck = 0;
    RUDP_CPARAMS(rudp).retransCount = 0;
    RUDP_CPARAMS(rudp).cumAckCount = 0;
    RUDP_CPARAMS(rudp).oosCount = 0;
    RUDP_CPARAMS(rudp).openWaitCount = 0;
    RUDP_CPARAMS(rudp).openWaitTimeout = 1000;
    RUDP_CPARAMS(rudp).openCloseTimeout = 1000;
    RUDP_CPARAMS(rudp).autoResetTimeout =
        RUDP_CPARAMS(rudp).maxOpenAttempts * RUDP_CPARAMS(rudp).openWaitTimeout;

    /*
     * initialize the pointers, as we will derive state information
     * from them.  We can't actually allocate here, as the user
     * must be allowed to change the default values specified in the
     * local SYN.
     */
    /* allocate the buffers */
    if ((RUDP_SEND_BUF(rudp) = (ITS_OCTET *)
                            malloc(RUDP_UPARAMS(rudp).maxSegmentSize)) == NULL)
    {
        ITS_TRACE_ERROR(("Create: Couldn't create sendBuf.\n"));

        MUTEX_DeleteMutex(&RUDP_LOCK(rudp));

        CALLBACK_DestroyManager(RUDP_CALLBACKS(rudp));

        return (ITS_ENOMEM);
    }

    if ((RUDP_RECV_BUF(rudp) = (ITS_OCTET *)
                            malloc(RUDP_UPARAMS(rudp).maxSegmentSize)) == NULL)
    {
        ITS_TRACE_ERROR(("Create: Couldn't create recvBuf.\n"));

        free(RUDP_SEND_BUF(rudp));

        MUTEX_DeleteMutex(&RUDP_LOCK(rudp));

        CALLBACK_DestroyManager(RUDP_CALLBACKS(rudp));

        return (ITS_ENOMEM);
    }

    if ((RUDP_SEND_QUEUE(rudp) = (ITS_RUDP_MSG **)
                            malloc(RUDP_UPARAMS(rudp).maxNumSegsPending *
                                   sizeof(ITS_RUDP_MSG *))) == NULL)
    {
        ITS_TRACE_ERROR(("Create: Couldn't create sendQueue.\n"));

        free(RUDP_RECV_BUF(rudp));
        free(RUDP_SEND_BUF(rudp));

        MUTEX_DeleteMutex(&RUDP_LOCK(rudp));

        CALLBACK_DestroyManager(RUDP_CALLBACKS(rudp));

        return (ITS_ENOMEM);
    }

    if ((RUDP_RECV_QUEUE(rudp) = (ITS_RUDP_MSG **)
                            malloc(RUDP_UPARAMS(rudp).maxCumAck *
                                   sizeof(ITS_RUDP_MSG *))) == NULL)
    {
        ITS_TRACE_ERROR(("Create: Couldn't create recvQueue.\n"));

        free(RUDP_SEND_QUEUE(rudp));
        free(RUDP_RECV_BUF(rudp));
        free(RUDP_SEND_BUF(rudp));

        MUTEX_DeleteMutex(&RUDP_LOCK(rudp));

        CALLBACK_DestroyManager(RUDP_CALLBACKS(rudp));

        return (ITS_ENOMEM);
    }

    if ((RUDP_OOS_QUEUE(rudp) = (ITS_RUDP_MSG **)
                           malloc(RUDP_UPARAMS(rudp).maxOOS *
                                  sizeof(ITS_RUDP_MSG *))) == NULL)
    {
        ITS_TRACE_ERROR(("Create: Couldn't create oosQueue.\n"));

        free(RUDP_RECV_QUEUE(rudp));
        free(RUDP_SEND_QUEUE(rudp));
        free(RUDP_RECV_BUF(rudp));
        free(RUDP_SEND_BUF(rudp));

        MUTEX_DeleteMutex(&RUDP_LOCK(rudp));

        CALLBACK_DestroyManager(RUDP_CALLBACKS(rudp));

        return (ITS_ENOMEM);
    }

    RUDP_CUR_SEND_SEG_SIZE(rudp) = 0;
    RUDP_CUR_RECV_SEG_SIZE(rudp) = 0;

    if (isActive)
    {
        RUDP_STATE(rudp) = RUDP_IDLE;
        RUDP_IS_ACTIVE(rudp) = ITS_TRUE;
    }
    else
    {
        RUDP_STATE(rudp) = RUDP_LISTEN;
        RUDP_IS_ACTIVE(rudp) = ITS_FALSE;
    }

    return (ITS_SUCCESS);
}

static int
RemoteCreate(ITS_Object obj, va_list args)
{
    return (ITS_SUCCESS);
}

/*.implementation:extern
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
Destroy(ITS_Object obj)
{
    int i;

    RUDP_Manager *rudp = (RUDP_Manager *)obj;

    CALLBACK_DestroyManager(RUDP_CALLBACKS(rudp));

    MUTEX_DeleteMutex(&RUDP_LOCK(rudp));

    if (RUDP_SEND_QUEUE(rudp))
    {
        for (i = 0; i < RUDP_SEND_QUEUE_COUNT(rudp); i++)
        {
            free(RUDP_SEND_QUEUE(rudp)[i]);
        }

        free(RUDP_SEND_QUEUE(rudp));
    }

    if (RUDP_RECV_QUEUE(rudp))
    {
        for (i = 0; i < RUDP_RECV_QUEUE_COUNT(rudp); i++)
        {
            free(RUDP_RECV_QUEUE(rudp)[i]);
        }

        free(RUDP_RECV_QUEUE(rudp));
    }

    if (RUDP_OOS_QUEUE(rudp))
    {
        for (i = 0; i < RUDP_OOS_QUEUE_COUNT(rudp); i++)
        {
            free(RUDP_OOS_QUEUE(rudp)[i]);
        }

        free(RUDP_OOS_QUEUE(rudp));
    }

    if (RUDP_SEND_BUF(rudp))
    {
        free(RUDP_SEND_BUF(rudp));
    }

    if (RUDP_RECV_BUF(rudp))
    {
        free(RUDP_RECV_BUF(rudp));
    }
}

static void
RemoteDestroy(ITS_Object obj)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an ITS_EVENT from a UDP socket.
 *
 *  Input Parameters:
 *      h - the handle to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - message read.
 *
 *  Notes:
 *      RemoteEndPoints are write only.  LocalEndPoints are read only.
 *      The SOURCE field in a remote is a pointer to the associated
 *      local's SOURCE.  The CONNECT field in local is a scratch buffer.
 *      The CONNECT field in a remote is the remote port addr.
 *
 *  See Also:
 ****************************************************************************/
static int
ReadEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;
    ITS_SockPollInfo info;

    ev->data = ITS_Malloc(4096);

    if (TRANSPORT_EXIT_NOW(h))
    {
        return (ITS_ERCVFAIL);
    }

    /*
     * this should be the blocking point
     */
repeat:
    memset(&info, 0, sizeof(info));

    info.lookFor = SOCK_POLL_READ;
    info.sinfo = SOCKTRAN_SOURCE(h);

    ret = SOCK_Poll(&info, 1,
                    HMI_GetTimeOutInterval() * USEC_PER_SEC);

    if (TRANSPORT_EXIT_NOW(h))
    {
        return (ITS_ERCVFAIL);
    }

    if (ret < ITS_SUCCESS)
    {
        return (ITS_ERCVFAIL);
    }

    if (ret == 0)
    {
        TRANSPORT_LAST_UPDATE(h) = TIMERS_Time();

        goto repeat;
    }

    ret = SOCK_Recv(SOCKTRAN_SOURCE(h),
                    (char *)ev->data, 4096,
                    SOCKTRAN_CONNECT(h)->addr, &SOCKTRAN_CONNECT(h)->asize);

    ev->len = ret;

    if (TRANSPORT_EXIT_NOW(h))
    {
        return (ITS_ERCVFAIL);
    }

    if (ret >= sizeof(RUDP_HDR) + sizeof(RUDP_CKSUM))
    {
        ret = ParseMsg((RUDP_Manager *)h, ev);

        if (ret == ITS_SUCCESS)
        {
            TRANSPORT_LAST_UPDATE(h) = TIMERS_Time();
            TRANSPORT_NUM_RECV(h)++;
        }

        return (ret);
    }
    else
    {
        return (ITS_ERCVFAIL);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method writes an ITS_EVENT to a UDP socket.
 *
 *  Input Parameters:
 *      h - the handle to write into
 *      ev - the buffer to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - message read.
 *
 *  Notes:
 *      RemoteEndPoints are write only.  LocalEndPoints are read only.
 *      The SOURCE field in a remote is a pointer to the associated
 *      local's SOURCE.  The CONNECT field in local is a scratch buffer.
 *      The CONNECT field in a remote is the remote port addr.
 *
 *  See Also:
 ****************************************************************************/
static int
WriteEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    ret = SOCK_Send(SOCKTRAN_SOURCE(h), (char *)ev->data, ev->len,
                     SOCKTRAN_CONNECT(h)->addr, SOCKTRAN_CONNECT(h)->asize);

    return (ret == ev->len ? ITS_SUCCESS : ITS_ESENDFAIL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method return an error. Used for mapping GetNextEvent, 
 *      PeeknextEvent and PutEvent in the Iterative Server.
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
ReturnErrorFunction(ITS_HANDLE h, ITS_EVENT* event)
{
    return !ITS_SUCCESS;
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
ReadOne(ITS_HANDLE h, ITS_EVENT *ev, ITS_BOOLEAN block)
{
    RUDP_Manager *rudp = (RUDP_Manager *)h;
    ITS_RUDP_MSG*   msg;
    int ret;

    ITS_TRACE_DEBUG(("ReadOne\n"));

    if (MUTEX_AcquireMutex(&RUDP_LOCK(rudp)) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    while (RecvQueueEmpty(rudp) &&
           RUDP_STATE(h) != RUDP_CONN_FAIL &&
           RUDP_STATE(h) != RUDP_CLOSE_WAIT &&
           RUDP_STATE(h) != RUDP_CLOSED)
    {
        if (!block)
        {
            if (!SOCK_Pending(SOCKTRAN_SOURCE(h)))
            {
                MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

                return (ITS_ENOMSG);
            }
        }

        /* don't carry the mutex through the potential block */
        MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

        ret = SOCKTRAN_CLASS_EXT_READ_EVENT(ITS_OBJ_CLASS(h))(h, ev);

        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }

        if (MUTEX_AcquireMutex(&RUDP_LOCK(rudp)) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        /* handle incoming data */
        msg = (ITS_RUDP_MSG *)ev->data;

        switch (RUDP_STATE(rudp))
        {
        case RUDP_SYN_SENT:
            ITS_TRACE_DEBUG(("ReadOne: TryOpen\n"));
            TryOpen(rudp, msg);
            break;

        case RUDP_SYN_RCVD:
            ITS_TRACE_DEBUG(("ReadOne: TryAccept\n"));
            TryAccept(rudp, msg);
            break;

        case RUDP_LISTEN:
            ITS_TRACE_DEBUG(("ReadOne: TryListen\n"));
            TryListen(rudp, msg);
            break;

        case RUDP_OPEN:
            ITS_TRACE_DEBUG(("ReadOne: OpenReceive\n"));
            OpenReceive(rudp, msg);
            break;

        case RUDP_TRANSFER:
            ITS_TRACE_DEBUG(("ReadOne: TransferReceive\n"));
            TransferReceive(rudp, msg);
            break;

        case RUDP_CLOSE_WAIT:
            ITS_TRACE_DEBUG(("ReadOne: WaitReceive\n"));
            WaitReceive(rudp, msg);
            break;

        default:
            ITS_TRACE_CRITICAL(("ReadOne: Bad state for read\n"));
            break;
        }
    }

    if (!RecvQueueEmpty(rudp))
    {
        ITS_TRACE_DEBUG(("ReadOne: Have data, len %d\n",
                    ev->len));

        ev->len = RUDP_RECV_QUEUE(rudp)[0]->dataLen;

        ITS_TRACE_DEBUG(("ReadOne: Have data, len %d\n",
                    ev->len));

        memcpy(ev->data,
               RUDP_RECV_QUEUE(rudp)[0]->userData,
               ev->len);

        RemoveFromRecvQueue(rudp, RUDP_RECV_QUEUE(rudp)[0]->hdr.seqNumber);

        MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

        return (ITS_SUCCESS);
    }
    else
    {
        ITS_TRACE_DEBUG(("ReadOne: No data\n"));

        MUTEX_ReleaseMutex(&RUDP_LOCK(rudp));

        return (ITS_ERCVFAIL);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an event from a local end point
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
LocalGetNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    ret = ReadOne(h, ev, ITS_TRUE);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(h));

    if (ret == ITS_SUCCESS)
    {
        TRANSPORT_NUM_RECV(h)++;
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an event from a local end point, if a message
 *      is pending
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
LocalPeekNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    ret = ReadOne(h, ev, ITS_FALSE);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(h));

    if (ret == ITS_SUCCESS)
    {
        TRANSPORT_NUM_RECV(h)++;
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method writes an event to a remote end point
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
RemotePutEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    RUDP_Manager *ctxt;

    /* recover the back pointer */
    ctxt = (RUDP_Manager *)SOCKTRAN_REMOTES(h)[0];

    if (MUTEX_AcquireMutex(&RUDP_LOCK(ctxt)) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if (RUDP_STATE(ctxt) == RUDP_OPEN)
    {
        OpenSend(ctxt, ev->data, ev->len);
    }
    else if (RUDP_STATE(ctxt) == RUDP_CONN_FAIL ||
             RUDP_STATE(ctxt) == RUDP_TRANSFER ||
             RUDP_STATE(ctxt) == RUDP_CLOSE_WAIT)
    {
        MUTEX_ReleaseMutex(&RUDP_LOCK(ctxt));

        return (ITS_EBADSTATE);
    }

    MUTEX_ReleaseMutex(&RUDP_LOCK(ctxt));

    TRANSPORT_NUM_SENT(h)++;

    return (ITS_SUCCESS);
}

/*
 * forward
 */
static SOCKTRAN_ClassExtRec RUDPReadWrite =
{
    /* core class */
    {
        ITS_EXT_VERSION
    },
    /* socket class */
    {
        ReadEvent,                  /* Read one */
        WriteEvent,                 /* Write one */
        (SOCKTRAN_Class)&itsRUDPTRAN_RemoteClassRec /* associate */
    }
};

/*
 * the UDP class record(s)
 */
RUDPDLLAPI TRANSPORT_ClassRec itsRUDPTRAN_LocalClassRec =
{
    /* core */
    {
        NULL,                                   /* parent class */
        sizeof(RUDP_Manager),                   /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        RUDPTRAN_LOCAL_ENDPOINT_CLASS_NAME,     /* class name */
        ITS_AddFeature,                         /* class initialize */
        ITS_RemFeature,                         /* class destroy */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        Create,                                 /* instantiate */
        Destroy,                                /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&RUDPReadWrite            /* extension */
    },
    /* transport */
    {
        LocalGetNextEvent,          /* get next */
        LocalPeekNextEvent,         /* peek next */
        ReturnErrorFunction         /* put */
    }
};

RUDPDLLAPI ITS_Class itsRUDPTRAN_LocalClass =
    (ITS_Class)&itsRUDPTRAN_LocalClassRec;

RUDPDLLAPI TRANSPORT_ClassRec itsRUDPTRAN_RemoteClassRec =
{
    /* core */
    {
        NULL,                                   /* parent class */
        sizeof(SOCKTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        RUDPTRAN_REMOTE_ENDPOINT_CLASS_NAME,    /* class name */
        ITS_AddFeature,                         /* class initialize */
        ITS_RemFeature,                         /* class destroy */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        RemoteCreate,                           /* instantiate */
        RemoteDestroy,                          /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&RUDPReadWrite            /* extension */
    },
    /* transport */
    {
        ReturnErrorFunction,        /* getNext */
        ReturnErrorFunction,        /* peekNext */
        RemotePutEvent              /* put */
    }
};

RUDPDLLAPI ITS_Class itsRUDPTRAN_RemoteClass =
    (ITS_Class)&itsRUDPTRAN_RemoteClassRec;

/*.implementation:extern
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
RUDPDLLAPI RUDP_Manager*
RUDP_Open(const char *name, ITS_USHORT instance, ITS_UINT mask,
          RUDP_EndPointParams* params, ITS_CALLBACK callback)
{
    RUDP_Manager *ctxt;
    ITS_RUDP_MSG*   msg;
    int ret;

    if (ITS_GlobalStart(mask) != ITS_SUCCESS)
    {
        return (NULL);
    }

    ctxt = (RUDP_Manager *)ITS_ConstructObject(itsRUDPTRAN_LocalClass,
                                               name, instance, mask,
                                               params, callback, ITS_TRUE);

    if (ctxt == NULL)
    {
        ITS_TRACE_CRITICAL(("RUDP_Open: Couldn't create endpoint.\n"));

        ITS_GlobalStop();

        return (NULL);
    }

    /* register this transport */
    if (TRANSPORT_RegisterTransport((TRANSPORT_Control *)ctxt) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RUDP_Open: couldn't register this "
                         "transport\n"));

        ITS_DestructObject((ITS_Object)ctxt);

        ITS_GlobalStop();

        return (NULL);
    }

    if (MUTEX_AcquireMutex(&RUDP_LOCK(ctxt)) != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("RUDP_Open: Couldn't acquire mutex.\n"));

        TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

        return (NULL);
    }

    /* connect to remote */
    if (Connect(ctxt) != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("RUDP_Open: Couldn't connect to remote.\n"));

        TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

        return (NULL);
    }

    while (RUDP_STATE(ctxt) == RUDP_IDLE ||
           RUDP_STATE(ctxt) == RUDP_SYN_SENT ||
           RUDP_STATE(ctxt) == RUDP_SYN_RCVD)
    {
        ITS_EVENT ev;

        MUTEX_ReleaseMutex(&RUDP_LOCK(ctxt));

        ret = SOCKTRAN_CLASS_EXT_READ_EVENT(ITS_OBJ_CLASS(ctxt))(ctxt, &ev);

        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_CRITICAL(("RUDP_Open: Read failed.\n"));

            TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

            return (NULL);
        }

        if (MUTEX_AcquireMutex(&RUDP_LOCK(ctxt)) != ITS_SUCCESS)
        {
            ITS_TRACE_CRITICAL(("RUDP_Open: Couldn't acquire mutex.\n"));

            TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

            return (NULL);
        }

        /* handle incoming data */
        msg = (ITS_RUDP_MSG *)ev.data;

        switch (RUDP_STATE(ctxt))
        {
        case RUDP_SYN_SENT:
            ITS_TRACE_DEBUG(("RUDP_Open: TryOpen\n"));
            TryOpen(ctxt, msg);
            break;

        case RUDP_SYN_RCVD:
            ITS_TRACE_DEBUG(("RUDP_Open: TryAccept\n"));
            TryAccept(ctxt, msg);
            break;

        case RUDP_LISTEN:
            ITS_TRACE_DEBUG(("RUDP_Open: TryListen\n"));
            TryListen(ctxt, msg);
            break;

        case RUDP_OPEN:
            ITS_TRACE_DEBUG(("RUDP_Open: OpenReceive\n"));
            OpenReceive(ctxt, msg);
            break;

        case RUDP_TRANSFER:
            ITS_TRACE_DEBUG(("RUDP_Open: TransferReceive\n"));
            TransferReceive(ctxt, msg);
            break;

        case RUDP_CLOSE_WAIT:
            ITS_TRACE_DEBUG(("RUDP_Open: WaitReceive\n"));
            WaitReceive(ctxt, msg);
            break;

        default:
            ITS_TRACE_DEBUG(("RUDP_Open: Unknown\n"));
            break;
        }
    }

    if (RUDP_STATE(ctxt) != RUDP_OPEN)
    {
        MUTEX_ReleaseMutex(&RUDP_LOCK(ctxt));

        TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

        return (NULL);
    }

    MUTEX_ReleaseMutex(&RUDP_LOCK(ctxt));

    TRANSPORT_SetState((TRANSPORT_Control *)ctxt, ITS_TRUE);

    return (ctxt);
}

/*.implementation:extern
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
RUDPDLLAPI RUDP_Manager*
RUDP_Listen(const char *name, ITS_USHORT instance, ITS_UINT mask,
            RUDP_EndPointParams *params, ITS_CALLBACK callback)
{
    RUDP_Manager *ctxt;
    ITS_RUDP_MSG*   msg;
    int ret;

    if (ITS_GlobalStart(mask) != ITS_SUCCESS)
    {
        return (NULL);
    }

    ctxt = (RUDP_Manager *)ITS_ConstructObject(itsRUDPTRAN_LocalClass,
                                               name, instance, mask,
                                               params, callback, ITS_FALSE);

    if (ctxt == NULL)
    {
        ITS_TRACE_CRITICAL(("RUDP_Listen: Couldn't create endpoint.\n"));

        ITS_GlobalStop();

        return (NULL);
    }

    /* register this transport */
    if (TRANSPORT_RegisterTransport((TRANSPORT_Control *)ctxt) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RUDP_Listen: couldn't register this "
                         "transport\n"));

        ITS_DestructObject((ITS_Object)ctxt);

        ITS_GlobalStop();

        return (NULL);
    }

    if (MUTEX_AcquireMutex(&RUDP_LOCK(ctxt)) != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("RUDP_Listen: Couldn't acquire mutex.\n"));

        TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

        return (NULL);
    }

    while (RUDP_STATE(ctxt) == RUDP_IDLE ||
           RUDP_STATE(ctxt) == RUDP_LISTEN ||
           RUDP_STATE(ctxt) == RUDP_SYN_SENT ||
           RUDP_STATE(ctxt) == RUDP_SYN_RCVD)
    {
        ITS_EVENT ev;

        MUTEX_ReleaseMutex(&RUDP_LOCK(ctxt));

        ret = SOCKTRAN_CLASS_EXT_READ_EVENT(ITS_OBJ_CLASS(ctxt))(ctxt, &ev);

        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_CRITICAL(("RUDP_Listen: Read fail\n"));

            TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

            return (NULL);
        }

        if (MUTEX_AcquireMutex(&RUDP_LOCK(ctxt)) != ITS_SUCCESS)
        {
            ITS_TRACE_CRITICAL(("RUDP_Listen: Couldn't acquire mutex.\n"));

            TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

            return (NULL);
        }

        /* handle incoming data */
        msg = (ITS_RUDP_MSG *)ev.data;

        switch (RUDP_STATE(ctxt))
        {
        case RUDP_SYN_SENT:
            ITS_TRACE_DEBUG(("RUDP_Listen: TryOpen\n"));
            TryOpen(ctxt, msg);
            break;

        case RUDP_SYN_RCVD:
            ITS_TRACE_DEBUG(("RUDP_Listen: TryAccept\n"));
            TryAccept(ctxt, msg);
            break;

        case RUDP_LISTEN:
            ITS_TRACE_DEBUG(("RUDP_Listen: TryListen\n"));
            TryListen(ctxt, msg);
            break;

        case RUDP_OPEN:
            ITS_TRACE_DEBUG(("RUDP_Listen: OpenReceive\n"));
            OpenReceive(ctxt, msg);
            break;

        case RUDP_TRANSFER:
            ITS_TRACE_DEBUG(("RUDP_Listen: TransferReceive\n"));
            TransferReceive(ctxt, msg);
            break;

        case RUDP_CLOSE_WAIT:
            ITS_TRACE_DEBUG(("RUDP_Listen: WaitReceive\n"));
            WaitReceive(ctxt, msg);
            break;

        default:
            ITS_TRACE_DEBUG(("RUDP_Listen: Unknown\n"));
            break;
        }
    }

    if (RUDP_STATE(ctxt) != RUDP_OPEN)
    {
        MUTEX_ReleaseMutex(&RUDP_LOCK(ctxt));

        TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

        return (NULL);
    }

    MUTEX_ReleaseMutex(&RUDP_LOCK(ctxt));

    TRANSPORT_SetState((TRANSPORT_Control *)ctxt, ITS_TRUE);

    return (ctxt);
}

/*.implementation:extern
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
RUDPDLLAPI void
RUDP_Close(RUDP_Manager *ctxt)
{
    ITS_RUDP_MSG*   msg;
    int ret;

    TRANSPORT_SetState((TRANSPORT_Control *)ctxt, ITS_FALSE);

    if (MUTEX_AcquireMutex(&RUDP_LOCK(ctxt)) != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("RUDP_Listen: Couldn't acquire mutex.\n"));

        TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

        return;
    }

    Close(ctxt);

    while (RUDP_STATE(ctxt) != RUDP_CLOSED &&
           SOCKTRAN_IS_VALID(ctxt))
    {
        ITS_EVENT ev;

        MUTEX_ReleaseMutex(&RUDP_LOCK(ctxt));

        ret = SOCKTRAN_CLASS_EXT_READ_EVENT(ITS_OBJ_CLASS(ctxt))(ctxt, &ev);

        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_CRITICAL(("RUDP_Close: Read fail\n"));

            TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

            return;
        }

        if (MUTEX_AcquireMutex(&RUDP_LOCK(ctxt)) != ITS_SUCCESS)
        {
            ITS_TRACE_CRITICAL(("RUDP_Close: Couldn't acquire mutex.\n"));

            TRANSPORT_Delete((TRANSPORT_Control *)ctxt);

            return;
        }

        /* handle incoming data */
        msg = (ITS_RUDP_MSG *)ev.data;

        switch (RUDP_STATE(ctxt))
        {
        case RUDP_SYN_SENT:
            ITS_TRACE_DEBUG(("RUDP_Close: TryOpen\n"));
            TryOpen(ctxt, msg);
            break;

        case RUDP_SYN_RCVD:
            ITS_TRACE_DEBUG(("RUDP_Close: TryAccept\n"));
            TryAccept(ctxt, msg);
            break;

        case RUDP_LISTEN:
            ITS_TRACE_DEBUG(("RUDP_Close: TryListen\n"));
            TryListen(ctxt, msg);
            break;

        case RUDP_OPEN:
            ITS_TRACE_DEBUG(("RUDP_Close: OpenReceive\n"));
            OpenReceive(ctxt, msg);
            break;

        case RUDP_TRANSFER:
            ITS_TRACE_DEBUG(("RUDP_Close: TransferReceive\n"));
            TransferReceive(ctxt, msg);
            break;

        case RUDP_CLOSE_WAIT:
            ITS_TRACE_DEBUG(("RUDP_Close: WaitReceive\n"));
            WaitReceive(ctxt, msg);
            break;

        default:
            ITS_TRACE_DEBUG(("RUDP_Close: Unknown\n"));
            break;
        }
    }

    SOCKTRAN_IS_VALID(ctxt) = ITS_FALSE;

    MUTEX_ReleaseMutex(&RUDP_LOCK(ctxt));

    TRANSPORT_Delete((TRANSPORT_Control *)ctxt);
}

/*.implementation:extern
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
RUDPDLLAPI int
RUDP_TransferState(RUDP_Manager *ctxt, ITS_UINT connID)
{
    PerformTransfer(ctxt, (ITS_USHORT)connID);

    return (ITS_SUCCESS);
}
