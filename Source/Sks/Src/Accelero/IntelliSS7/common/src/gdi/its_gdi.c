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
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:05  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/08/15 17:30:57  mmiers
 * LOG: Header changes mandate different include setup.
 * LOG:
 * LOG: Revision 4.3  2001/05/02 19:58:55  mmiers
 * LOG: Add thread pool shutdown logic.  People using the C API
 * LOG: need to convert to WORKER_GetExit() instead of TPOOL_THREAD_EXIT().
 * LOG:
 * LOG: Revision 4.2  2001/05/02 19:06:01  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.5  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.4  2001/02/15 16:05:45  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.3  2001/01/16 21:39:25  mmiers
 * LOG: Reorganize so that support is completely standalone
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:37  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:56  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.14  2000/08/09 01:13:43  mmiers
 * LOG: Platform corrections.
 * LOG:
 * LOG: Revision 2.13  2000/07/12 15:25:47  mmiers
 * LOG:
 * LOG: Some cleanups and performance enhancements.
 * LOG:
 * LOG: Revision 2.12  2000/07/05 22:27:10  rsonak
 * LOG:
 * LOG:
 * LOG: Read from the right section name for globals
 * LOG:
 * LOG: Revision 2.11  2000/06/22 23:08:30  rsonak
 * LOG: Iterative servers cannot run protocols.
 * LOG:
 * LOG: Revision 2.10  2000/06/02 17:52:10  mmiers
 * LOG:
 * LOG:
 * LOG: Timeout means shutdown for KASOCKs.
 * LOG:
 * LOG: Revision 2.9  2000/06/02 17:18:10  mmiers
 * LOG:
 * LOG:
 * LOG: Socket modifications.
 * LOG:
 * LOG: Revision 2.8  2000/05/11 02:06:12  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 2.7  2000/05/10 23:39:48  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based protocols with heartbeats.
 * LOG:
 * LOG: Revision 2.6  2000/02/10 14:48:09  mmiers
 * LOG:
 * LOG: Add functions for network/host conversion so they're always in our
 * LOG: namespace.
 * LOG:
 * LOG: Revision 2.5  2000/02/10 02:03:06  mmiers
 * LOG:
 * LOG: Match up with the headers.
 * LOG:
 * LOG: Revision 2.4  2000/02/02 02:20:49  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 2.3  2000/01/31 23:17:01  mmiers
 * LOG:
 * LOG:
 * LOG: Some GDI tweaks, some RUDP work.
 * LOG:
 * LOG: Revision 2.2  1999/12/17 20:41:18  mmiers
 * LOG:
 * LOG:
 * LOG: Still trying to get this to work.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 21:15:12  mmiers
 * LOG:
 * LOG: Try to get the split right.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_app.h>
#include <its_sockets.h>
#include <its_transports.h>
#include <its_ip_trans.h>
#include <its_tq_trans.h>
#include <its_trace.h>
#include <its_thread.h>
#include <its_timers.h>
#include <its_hmi.h>

#include <gdi_msgs.h>

#ident "$Id: its_gdi.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

#if defined(CCITT)
#include <itu/tcap.h>
#elif defined(ANSI)
#include <ansi/tcap.h>
#else
#error "Protocol family not defined."
#endif

#define GDI_IMPLEMENTATION

#include <its_gdi_trans.h>

/*
 * trace control
 */
#define GDI_DEBUG

static int gdiKeepAliveTimeout = 20;

#if defined(GDI_DEBUG)
int gdiTraceKeepAlives = 0;
int gdiTracePayload = 0;
#endif

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function converts a message to network form
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
static void
ToNetwork(ITS_GDI_MSG *msg)
{
    msg->header.messageType = SOCK_HToNS(msg->header.messageType);
    msg->header.messageLength = SOCK_HToNS(msg->header.messageLength);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function converts a message from network form
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
static void
FromNetwork(ITS_GDI_MSG *msg)
{
    msg->header.messageType = SOCK_NToHS(msg->header.messageType);
    msg->header.messageLength = SOCK_NToHS(msg->header.messageLength);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function performs the network read.
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
LowRead(KASOCKTRAN_Manager *kt, void *buf)
{
    int ret;
    ITS_GDI_MSG *msg= (ITS_GDI_MSG *)buf;
    ITS_SockPollInfo info;

    if (TRANSPORT_EXIT_NOW(kt))
    {
        return (ITS_ERCVFAIL);
    }

    /*
     * this should be the blocking point
     */
repeat:
    memset(&info, 0, sizeof(info));

    info.lookFor = SOCK_POLL_READ;
    info.sinfo = SOCKTRAN_SOURCE(kt);

    ret = SOCK_Poll(&info, 1,
                    HMI_GetTimeOutInterval() * USEC_PER_SEC);

    if (TRANSPORT_EXIT_NOW(kt))
    {
        return (ITS_ERCVFAIL);
    }

    if (ret < ITS_SUCCESS)
    {
        return (ITS_ERCVFAIL);
    }

    if (ret == 0)
    {
        TRANSPORT_LAST_UPDATE(kt) = TIMERS_Time();

        goto repeat;
    }

    /* read the sControl.source */
    ret = SOCK_Read(SOCKTRAN_SOURCE(kt),
                    (char *)&msg->header,
                    sizeof(ITS_GDI_HDR));

    if (ret != sizeof(ITS_GDI_HDR))
    {
        return (ITS_ERCVFAIL);
    }

    FromNetwork(msg);

    /* read the data */
    if (msg->header.messageLength > (2 * sizeof(ITS_OCTET)))
    {
        ret = SOCK_Read(SOCKTRAN_SOURCE(kt),
                        (char *)msg->contents.payload,
                        msg->header.messageLength - (2 * sizeof(ITS_OCTET)));

        if (ret != (int)(msg->header.messageLength - 
                         (2 * sizeof(ITS_OCTET))))
        {
            return (ITS_ERCVFAIL);
        }
    }

    TRANSPORT_LAST_UPDATE(kt) = TIMERS_Time();
    TRANSPORT_NUM_RECV(kt)++;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function performs the network write.
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
LowWrite(KASOCKTRAN_Manager *kt, void *buf)
{
    ITS_USHORT tmp;
    int ret;
    ITS_GDI_MSG *msg = (ITS_GDI_MSG *)buf;

    GDITRAN_LAST_MSG_TX_TIME(kt) = TIMERS_Time();

    /* Write the sControl.source */
    tmp = msg->header.messageLength - (2 * sizeof(ITS_OCTET));

    ToNetwork(msg);

    ret = SOCK_Write(SOCKTRAN_SOURCE(kt),
                     (char *)&msg->header,
                     sizeof(ITS_GDI_HDR));

    if (ret != sizeof(ITS_GDI_HDR))
    {
        return (ITS_ESENDFAIL);
    }

    /* Write the data */
    if (msg->header.messageLength > (2 * sizeof(ITS_OCTET)))
    {
        ret = SOCK_Write(SOCKTRAN_SOURCE(kt),
                         (char *)msg->contents.payload,
                         tmp);

        if (ret != tmp)
        {
            return (ITS_ESENDFAIL);
        }
    }

    TRANSPORT_NUM_SENT(kt)++;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function creates a GDI transport
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
    GDITRAN_Manager *tc = (GDITRAN_Manager *)h;
    char value[ITS_PATH_MAX];
    RESFILE_Manager *res;
    char *rname;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    if (TRANSPORT_MASK(tc) & ITS_TRANSPORT_SSOCKET_ITER)
    {
        return (ITS_SUCCESS);
    }

    KASOCKTRAN_LOW_READ_BUF(tc) = malloc(sizeof(ITS_GDI_MSG));
    if (KASOCKTRAN_LOW_READ_BUF(tc) == NULL)
    {
        return (ITS_ENOMEM);
    }

    KASOCKTRAN_LOW_WRITE_BUF(tc) = malloc(sizeof(ITS_GDI_MSG));
    if (KASOCKTRAN_LOW_WRITE_BUF(tc) == NULL)
    {
        free(KASOCKTRAN_LOW_READ_BUF(tc));

        KASOCKTRAN_LOW_READ_BUF(tc) = NULL;

        return (ITS_ENOMEM);
    }

    /* get the remoteSSN value */
    res = TRANSPORT_RES(tc);
    rname = TRANSPORT_NAME(tc);
    if (RESFILE_GetKeyValueOf(res, rname, GDI_LOCAL_PC_STRING,
                              value, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GDI Create: Missing localPC\n"));

        free(KASOCKTRAN_LOW_READ_BUF(tc));
        free(KASOCKTRAN_LOW_WRITE_BUF(tc));

        KASOCKTRAN_LOW_READ_BUF(tc) = NULL;
        KASOCKTRAN_LOW_WRITE_BUF(tc) = NULL;

        return (ITS_EINVALIDARGS);
    }
    else
    {
        GDITRAN_LOCAL_PC(tc) = RESFILE_ParseNum(value);
    }

    if (RESFILE_GetKeyValueOf(res, rname, GDI_REMOTE_PC_STRING,
                              value, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GDI Create: Missing remotePC\n"));

        free(KASOCKTRAN_LOW_READ_BUF(tc));
        free(KASOCKTRAN_LOW_WRITE_BUF(tc));

        KASOCKTRAN_LOW_READ_BUF(tc) = NULL;
        KASOCKTRAN_LOW_WRITE_BUF(tc) = NULL;

        return (ITS_EINVALIDARGS);
    }
    else
    {
        GDITRAN_REMOTE_PC(tc) = RESFILE_ParseNum(value);
    }

    if (RESFILE_GetKeyValueOf(res, rname, GDI_REMOTE_SSN_STRING,
                              value, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GDI Create: Missing remoteSSN\n"));

        free(KASOCKTRAN_LOW_READ_BUF(tc));
        free(KASOCKTRAN_LOW_WRITE_BUF(tc));

        KASOCKTRAN_LOW_READ_BUF(tc) = NULL;
        KASOCKTRAN_LOW_WRITE_BUF(tc) = NULL;

        return (ITS_EINVALIDARGS);
    }
    else
    {
        GDITRAN_REMOTE_SSN(tc) = atoi(value);
    }

    /* initial values for the keepalives */
    GDITRAN_LAST_MSG_TX_TIME(tc) =
        GDITRAN_LAST_MSG_RX_TIME(tc) =
        GDITRAN_KA_LOCAL_TX_TIME(tc) =
        GDITRAN_KA_REMOTE_RX_TIME(tc) =
            TIMERS_Time();

    GDITRAN_KA_LOCAL_REQ_PENDING(tc) = ITS_FALSE;
    GDITRAN_KA_REMOTE_REQ_PENDING(tc) = ITS_FALSE;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function destroys a GDI transport
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
    GDITRAN_Manager *tc = (GDITRAN_Manager *)h;

    free(KASOCKTRAN_LOW_READ_BUF(tc));
    free(KASOCKTRAN_LOW_WRITE_BUF(tc));

    KASOCKTRAN_LOW_READ_BUF(tc) = NULL;
    KASOCKTRAN_LOW_WRITE_BUF(tc) = NULL;
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
Forward(KASOCKTRAN_Manager *ft, ITS_EVENT *ev, void *m)
{
    ITS_GDI_MSG *msg = (ITS_GDI_MSG *)m;
    ITS_SCCP_IE ies[6];
    MTP3_HEADER label;
    ITS_OCTET buf[1024];
    ITS_USHORT len;
    int i;

#if defined(GDI_DEBUG)
    if ((gdiTraceKeepAlives &&
         (msg->header.messageType == GDI_MSG_KEEP_ALIVE_REQ ||
          msg->header.messageType == GDI_MSG_KEEP_ALIVE_RESP)) ||
        (gdiTracePayload &&
         msg->header.messageType != GDI_MSG_KEEP_ALIVE_REQ &&
         msg->header.messageType != GDI_MSG_KEEP_ALIVE_RESP))
    {
        ITS_TRACE_DEBUG(("GDI Received message:\n"));
        ITS_TRACE_DEBUG(("  Type: %04x  Length: %04x  "
                         "AppId: %02x  Version: %02x\n",
                         msg->header.messageType,
                         msg->header.messageLength,
                         msg->header.applicationID,
                         msg->header.versionNumber));
        ITS_TRACE_DEBUG(("  "));
        for (i = 0;
             i < (int)(msg->header.messageLength - 2 * sizeof(ITS_OCTET));
             i++)
        {
            TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                      ("%02x ", msg->contents.payload[i]));

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

    switch (msg->header.messageType)
    {
    case GDI_MSG_KEEP_ALIVE_REQ:
    case GDI_MSG_KEEP_ALIVE_RESP:
        /* overhead messages go to the keepalive thread */
        ev->len = msg->header.messageLength + 2 * sizeof(ITS_USHORT);

        if (ev->len > GDI_MAX_MSG_SIZE)
        {
            return (ITS_EOVERFLOW);
        }

        ev->src = TRANSPORT_INSTANCE(ft);

        memcpy(ev->data, &msg, ev->len);

        TRANSPORT_PutEvent(ITS_KEEPALIVE_INSTANCE, ev);

        return (ITS_ENOMSG);

    case GDI_MSG_ERROR:
        /*
         * error messages are to be treated as transport failures.
         * Further, we are supposed to terminate all requests pending,
         * but we can't really do that (well, we could - walk the
         * dialogue id table and issue P-ABORTs for every pending
         * transaction - FIXME).
         */
        ITS_TRACE_ERROR(("Rcvd GDI error: %02x from peer\n",
                         SOCK_NToHS(msg->contents.errorCode)));
#if defined(GDI_DEBUG)
        exit(EXIT_FAILURE);
#endif
        return (ITS_ERCVFAIL);

    case GDI_MSG_DATA:
        GDITRAN_LAST_MSG_RX_TIME(ft) = TIMERS_Time();

        /*
         * package up the data messages for forwarding to SCCP.
         * This means:
         *  messageType - irrelevant
         *  messageSize - USER_DATA size (after adjustment)
         *  versionNumber - check for allowed value here
         *  applicationID - "SSN".  If 0, send to "defaultSSN".
         */
        MTP3_HDR_SET_SIO(label,
                         MTP3_NIC_NATIONAL|MTP3_MPC_PRI_0|MTP3_SIO_SCCP);
        MTP3_RL_SET_OPC_VALUE(label.label, GDITRAN_REMOTE_PC(ft));
        MTP3_RL_SET_DPC_VALUE(label.label, GDITRAN_LOCAL_PC(ft));
        MTP3_RL_SET_SLS(label.label, 0);

        ies[0].param_id = SCCP_PRM_PROTOCOL_CLASS;
        ies[0].param_length = sizeof(SCCP_PROT_CLASS);
        ies[0].param_data.protocolClass.pclass = SCCP_PCLASS_0;

        ies[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        ies[1].param_length = sizeof(SCCP_ADDR);
        SCCP_EncodeAddr(&ies[1].param_data.calledPartyAddr,
                        SCCP_CPA_ROUTE_NAT|SCCP_CPA_ROUTE_SSN|
                            SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN,
                        GDITRAN_LOCAL_PC(ft), msg->header.applicationID, NULL, 0);

        ies[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        ies[2].param_length = sizeof(SCCP_ADDR);
        SCCP_EncodeAddr(&ies[2].param_data.callingPartyAddr,
                        SCCP_CPA_ROUTE_NAT|SCCP_CPA_ROUTE_SSN|
                            SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN,
                        GDITRAN_REMOTE_PC(ft), GDITRAN_REMOTE_SSN(ft), NULL, 0);

        ies[3].param_id = SCCP_PRM_DATA;
        ies[3].param_length = msg->header.messageLength - 2 * sizeof(ITS_OCTET);
        memcpy(ies[3].param_data.userData.data,
               msg->contents.payload,
               ies[3].param_length);

        if (SCCP_EncodeMTP3(buf, &len, SCCP_MSG_UDT,
                            ies, 4, &SCCP_UDT_Desc) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("Rcv GDI error: SCCP Encode error\n"));

            return (ITS_ERCVFAIL);
        }

        if (MTP3_Encode(ev, MTP3_MSG_USER_DATA,
                        &label, buf, len) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("Rcvd GDI error: MTP3 Encode error\n"));

            return (ITS_ERCVFAIL);
        }

        break;
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
Convert(KASOCKTRAN_Manager *gdi, ITS_EVENT *ev, void *m)
{
    ITS_GDI_MSG *msg = (ITS_GDI_MSG *)m;
    int i, ieCount;
    ITS_SCCP_IE ies[6];
    MTP3_HEADER label;
    ITS_OCTET buf[1024], msgType, ai;
    ITS_USHORT len;

    switch (ev->src)
    {
    case ITS_KEEPALIVE_INSTANCE:
        /* keepalive responses and requests */
        memcpy(&msg, ev->data, ev->len);
        break;

    case ITS_SCCP_SRC:
        /*
         * data - Decode network format SCCP message and send
         * only TCAP payload.  Use CDP-SSN as application name.
         */
        if (MTP3_Decode(ev, &msgType, &label, buf, &len) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("Xmit GDI error: MTP3 Decode error\n"));

            return (ITS_ESENDFAIL);
        }

        if (msgType != MTP3_MSG_USER_DATA)
        {
            ITS_TRACE_ERROR(("Xmit GDI error: Invalid MTP3 message\n"));

            return (ITS_ESENDFAIL);
        }

        if (SCCP_DecodeMTP3(buf, len, &msgType,
                            ies, &ieCount, &SCCP_UDT_Desc) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("Xmit GDI error: Invalid MTP3 message\n"));

            return (ITS_ESENDFAIL);
        }

        msg->header.messageType = GDI_MSG_DATA;
        msg->header.versionNumber = GDI_VERSION_5;

        for (i = 0; i < ieCount; i++)
        {
            /*
             * This is confused, I don't know what is right.
             * The spec says the client uses this to select the
             * application, but the server is supposed to echo it back.
             * However, which is which?  The only thing that makes sense
             * is for the initiator to be the client.
             */
            if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
            {
                SCCP_DecodeAddr(&ies[i].param_data.calledPartyAddr,
                                &ai, NULL, &msg->header.applicationID, NULL, NULL);

                if (!(ai & SCCP_CPA_HAS_SSN))
                {
                    ITS_TRACE_ERROR(("Xmit GDI error: Unknown destination\n"));

                    return (ITS_ESENDFAIL);
                }
            }
            else if (ies[i].param_id == SCCP_PRM_DATA)
            {
                memcpy(msg->contents.payload,
                       ies[i].param_data.userData.data,
                       ies[i].param_length);

                msg->header.messageLength = ies[i].param_length +
                                            2 * sizeof(ITS_OCTET);
            }
        }
        break;

    default:
        /* errors */
        memcpy(&msg, ev->data, ev->len);
        break;
    }


#if defined(GDI_DEBUG)
    if ((gdiTraceKeepAlives &&
         (msg->header.messageType == GDI_MSG_KEEP_ALIVE_REQ ||
          msg->header.messageType == GDI_MSG_KEEP_ALIVE_RESP)) ||
        (gdiTracePayload &&
         msg->header.messageType != GDI_MSG_KEEP_ALIVE_REQ &&
         msg->header.messageType != GDI_MSG_KEEP_ALIVE_RESP))
    {
        ITS_TRACE_DEBUG(("GDI Sending message:\n"));
        ITS_TRACE_DEBUG(("  Type: %04x  Length: %04x  "
                         "AppId: %02x  Version: %02x\n",
                         msg->header.messageType,
                         msg->header.messageLength,
                         msg->header.applicationID,
                         msg->header.versionNumber));
        ITS_TRACE_DEBUG(("  "));
        for (i = 0;
             i < (int)(msg->header.messageLength - 2 * sizeof(ITS_OCTET));
             i++)
        {
            TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                      ("%02x ", msg->contents.payload[i]));

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
CheckTime(KASOCKTRAN_Manager *kt)
{
    GDITRAN_Manager *gdi;
    ITS_TIME currentTime;

    currentTime = TIMERS_Time();

    gdi = (GDITRAN_Manager *)kt;

    if (!SOCKTRAN_IS_VALID(gdi))
    {
        ITS_TRACE_DEBUG(("GDI_KeepAliveTimerCheck: transport %04x "
                         "isn't valid right now.\n",
                         TRANSPORT_INSTANCE(kt)));

        return;
    }

    /*
     * Here's the algorithm for computing if response or request is
     * necessary.
     */
    if (GDITRAN_KA_REMOTE_REQ_PENDING(gdi))
    {
        /*
         * someone at some point sent *us* a request
         */
        if (GDITRAN_LAST_MSG_TX_TIME(gdi) >
            GDITRAN_KA_REMOTE_RX_TIME(gdi))
        {
            GDITRAN_KA_REMOTE_REQ_PENDING(gdi) = ITS_FALSE;
        }
        else if (currentTime >
                 (GDITRAN_KA_REMOTE_RX_TIME(gdi) + gdiKeepAliveTimeout))
        {
            ITS_EVENT ev;
            ITS_GDI_HDR msg;

#if defined(GDI_DEBUG)
            if (gdiTraceKeepAlives)
            {
                ITS_TRACE_DEBUG(("Sending KeepAlive Response\n"));
            }
#endif
            GDITRAN_KA_REMOTE_REQ_PENDING(gdi) = ITS_FALSE;

            ev.src = ITS_KEEPALIVE_INSTANCE;
            ev.len = sizeof(ITS_GDI_HDR);
            ev.data = (ITS_OCTET *)ITS_Malloc(sizeof(ITS_GDI_HDR));
            if (ev.data == NULL)
            {
                ITS_TRACE_ERROR(("No memory when sending GDI KA RESP\n"));

                return;
            }

            msg.messageType = GDI_MSG_KEEP_ALIVE_RESP;
            msg.messageLength = 2 * sizeof(ITS_OCTET);
            msg.versionNumber = GDI_VERSION_5;
            msg.applicationID = GDITRAN_REMOTE_SSN(gdi);

            memcpy(ev.data, &msg, sizeof(ITS_GDI_HDR));

            TRANSPORT_PutEvent(TRANSPORT_INSTANCE(gdi), &ev);
        }
    }

    if (GDITRAN_KA_LOCAL_REQ_PENDING(gdi))
    {
        /*
         * we issued a request
         */
        if (GDITRAN_LAST_MSG_RX_TIME(gdi) >
            GDITRAN_KA_LOCAL_TX_TIME(gdi))
        {
            GDITRAN_KA_LOCAL_REQ_PENDING(gdi) = ITS_FALSE;
        }
        else if (currentTime >
                 (GDITRAN_KA_LOCAL_TX_TIME(gdi) + (3 * gdiKeepAliveTimeout)))
        {
            ITS_TRACE_WARNING(("GDI shutdown on %04x due to timeout\n",
                               TRANSPORT_INSTANCE(gdi)));

            GDITRAN_KA_LOCAL_REQ_PENDING(gdi) = ITS_FALSE;

            SOCKTRAN_CLASS_SHUTDOWN(ITS_OBJ_CLASS(gdi))
                ((SOCKTRAN_Manager *)gdi);

            return;
        }
    }

    if (currentTime >
        (GDITRAN_LAST_MSG_RX_TIME(gdi) + gdiKeepAliveTimeout) &&
        !GDITRAN_KA_LOCAL_REQ_PENDING(gdi))
    {
        /*
         * start a keepAlive
         */
        ITS_EVENT ev;
        ITS_GDI_HDR msg;

#if defined(GDI_DEBUG)
        if (gdiTraceKeepAlives)
        {
            ITS_TRACE_DEBUG(("Sending KeepAlive Request\n"));
        }
#endif
        GDITRAN_KA_LOCAL_REQ_PENDING(gdi) = ITS_TRUE;
        GDITRAN_KA_LOCAL_TX_TIME(gdi) = currentTime;

        ev.src = ITS_KEEPALIVE_INSTANCE;
        ev.len = sizeof(ITS_GDI_HDR);
        ev.data = (ITS_OCTET *)ITS_Malloc(sizeof(ITS_GDI_HDR));
        if (ev.data == NULL)
        {
            ITS_TRACE_ERROR(("No memory when sending KA REQ\n"));

            return;
        }

        msg.messageType = GDI_MSG_KEEP_ALIVE_REQ;
        msg.messageLength = 2 * sizeof(ITS_OCTET);
        msg.versionNumber = GDI_VERSION_5;
        msg.applicationID = GDITRAN_REMOTE_SSN(gdi);

        memcpy(ev.data, &msg, sizeof(ITS_GDI_HDR));

        TRANSPORT_PutEvent(TRANSPORT_INSTANCE(gdi), &ev);
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
CheckEvent(KASOCKTRAN_Manager *keepAliveSrc, ITS_EVENT *gdiEvent)
{
    ITS_GDI_MSG msg;

    if (gdiEvent->len != sizeof(ITS_GDI_HDR))
    {
        /* we don't know what it is: discard */
        ITS_TRACE_WARNING(("GDI_CheckEvent: bad GDI message len %0d\n",
                           gdiEvent->len));

        return;
    }

#if defined(GDI_DEBUG)
    if (gdiTraceKeepAlives)
    {
        ITS_TRACE_DEBUG(("Handle keepalive...\n"));
    }
#endif

    /* it's a keepalive */
    memcpy(&msg, gdiEvent->data, gdiEvent->len);
    switch (msg.header.messageType)
    {
    case GDI_MSG_KEEP_ALIVE_REQ:
#if defined(GDI_DEBUG)
        if (gdiTraceKeepAlives)
        {
            ITS_TRACE_DEBUG(("Handle keepalive request...\n"));
        }
#endif

        GDITRAN_KA_REMOTE_REQ_PENDING(keepAliveSrc) = ITS_TRUE;
        GDITRAN_KA_REMOTE_RX_TIME(keepAliveSrc) = TIMERS_Time();
        break;

    case GDI_MSG_KEEP_ALIVE_RESP:
#if defined(GDI_DEBUG)
        if (gdiTraceKeepAlives)
        {
            ITS_TRACE_DEBUG(("Handle keepalive response...\n"));
        }
#endif

        GDITRAN_LAST_MSG_RX_TIME(keepAliveSrc) = TIMERS_Time();
        break;

    default:
        /* we don't know what it is: discard */
        ITS_TRACE_WARNING(("GDI_KeepAliveThread: unknown "
                           "GDI message type %04x\n",
                           msg.header.messageType));
        break;
    }
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
    static RESFILE_Manager *globalRes = NULL;
    static char value[ITS_PATH_MAX];
    const char *name = APPL_GetConfigFileName();

    globalRes = RESFILE_CreateResourceManager(name);

    if (globalRes)
    {
        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  GDI_KEEPALIVE_TIMEOUT_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            gdiKeepAliveTimeout = atoi(value);
        }

        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  GDI_TRACE_KEEPALIVES_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            gdiTraceKeepAlives = atoi(value);
        }

        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  GDI_TRACE_PAYLOAD_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            gdiTracePayload = atoi(value);
        }
    }

    ITS_CLASS_EXTENSION(itsGDITRAN_ClientClass) =
        ITS_CLASS_EXTENSION(ITS_CLASS_SUPERCLASS(itsGDITRAN_ClientClass));

    ITS_CLASS_OBJECT_INSTANTIATE(itsGDITRAN_ClientClass) = Create;
    ITS_CLASS_OBJECT_DESTROY(itsGDITRAN_ClientClass) = Destroy;
    KASOCKTRAN_CLASS_CHECK_TIME(itsGDITRAN_ClientClass) = CheckTime;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsGDITRAN_ClientClass) = CheckEvent;
    KASOCKTRAN_CLASS_LOW_READ(itsGDITRAN_ClientClass) = LowRead;
    KASOCKTRAN_CLASS_LOW_WRITE(itsGDITRAN_ClientClass) = LowWrite;
    KASOCKTRAN_CLASS_DECODE(itsGDITRAN_ClientClass) = Forward;
    KASOCKTRAN_CLASS_ENCODE(itsGDITRAN_ClientClass) = Convert;

    ITS_CLASS_EXTENSION(itsGDITRAN_ServerClass) =
        ITS_CLASS_EXTENSION(ITS_CLASS_SUPERCLASS(itsGDITRAN_ServerClass));

    ITS_CLASS_OBJECT_INSTANTIATE(itsGDITRAN_ServerClass) = Create;
    ITS_CLASS_OBJECT_DESTROY(itsGDITRAN_ServerClass) = Destroy;
    KASOCKTRAN_CLASS_CHECK_TIME(itsGDITRAN_ServerClass) = CheckTime;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsGDITRAN_ServerClass) = CheckEvent;
    KASOCKTRAN_CLASS_LOW_READ(itsGDITRAN_ServerClass) = LowRead;
    KASOCKTRAN_CLASS_LOW_WRITE(itsGDITRAN_ServerClass) = LowWrite;
    KASOCKTRAN_CLASS_DECODE(itsGDITRAN_ServerClass) = Forward;
    KASOCKTRAN_CLASS_ENCODE(itsGDITRAN_ServerClass) = Convert;

    ITS_CLASS_EXTENSION(itsGDITRAN_DynamicServerClass) =
        ITS_CLASS_EXTENSION(ITS_CLASS_SUPERCLASS(itsGDITRAN_DynamicServerClass));

    ITS_CLASS_OBJECT_INSTANTIATE(itsGDITRAN_DynamicServerClass) = Create;
    ITS_CLASS_OBJECT_DESTROY(itsGDITRAN_DynamicServerClass) = Destroy;
    KASOCKTRAN_CLASS_CHECK_TIME(itsGDITRAN_DynamicServerClass) = CheckTime;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsGDITRAN_DynamicServerClass) = CheckEvent;
    KASOCKTRAN_CLASS_LOW_READ(itsGDITRAN_DynamicServerClass) = LowRead;
    KASOCKTRAN_CLASS_LOW_WRITE(itsGDITRAN_DynamicServerClass) = LowWrite;
    KASOCKTRAN_CLASS_DECODE(itsGDITRAN_DynamicServerClass) = Forward;
    KASOCKTRAN_CLASS_ENCODE(itsGDITRAN_DynamicServerClass) = Convert;

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
    ITS_CLASS_OBJECT_INSTANTIATE(itsGDITRAN_ClientClass) = NULL;
    ITS_CLASS_OBJECT_DESTROY(itsGDITRAN_ClientClass) = NULL;
    KASOCKTRAN_CLASS_CHECK_TIME(itsGDITRAN_ClientClass) = NULL;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsGDITRAN_ClientClass) = NULL;
    KASOCKTRAN_CLASS_LOW_READ(itsGDITRAN_ClientClass) = NULL;
    KASOCKTRAN_CLASS_LOW_WRITE(itsGDITRAN_ClientClass) = NULL;
    KASOCKTRAN_CLASS_DECODE(itsGDITRAN_ClientClass) = NULL;
    KASOCKTRAN_CLASS_ENCODE(itsGDITRAN_ClientClass) = NULL;

    ITS_CLASS_OBJECT_INSTANTIATE(itsGDITRAN_ServerClass) = NULL;
    ITS_CLASS_OBJECT_DESTROY(itsGDITRAN_ServerClass) = NULL;
    KASOCKTRAN_CLASS_CHECK_TIME(itsGDITRAN_ServerClass) = NULL;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsGDITRAN_ServerClass) = NULL;
    KASOCKTRAN_CLASS_LOW_READ(itsGDITRAN_ServerClass) = NULL;
    KASOCKTRAN_CLASS_LOW_WRITE(itsGDITRAN_ServerClass) = NULL;
    KASOCKTRAN_CLASS_DECODE(itsGDITRAN_ServerClass) = NULL;
    KASOCKTRAN_CLASS_ENCODE(itsGDITRAN_ServerClass) = NULL;

    ITS_CLASS_OBJECT_INSTANTIATE(itsGDITRAN_DynamicServerClass) = NULL;
    ITS_CLASS_OBJECT_DESTROY(itsGDITRAN_DynamicServerClass) = NULL;
    KASOCKTRAN_CLASS_CHECK_TIME(itsGDITRAN_DynamicServerClass) = NULL;
    KASOCKTRAN_CLASS_CHECK_EVENT(itsGDITRAN_DynamicServerClass) = NULL;
    KASOCKTRAN_CLASS_LOW_READ(itsGDITRAN_DynamicServerClass) = NULL;
    KASOCKTRAN_CLASS_LOW_WRITE(itsGDITRAN_DynamicServerClass) = NULL;
    KASOCKTRAN_CLASS_DECODE(itsGDITRAN_DynamicServerClass) = NULL;
    KASOCKTRAN_CLASS_ENCODE(itsGDITRAN_DynamicServerClass) = NULL;
}

GDIDLLAPI ITS_ClassRec itsGDI_ClassRec =
{
    /* core */
    {
        NULL,
        0,
        ITS_FALSE,
        0,
        "GDI",
        Init,
        Term,
        NULL,
        NULL,
        NULL
    }
};

GDIDLLAPI ITS_Class itsGDI_Class = &itsGDI_ClassRec;
