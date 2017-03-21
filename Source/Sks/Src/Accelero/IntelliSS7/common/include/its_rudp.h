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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.5  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.2  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:20  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.16  2000/02/10 00:44:34  mmiers
 * LOG:
 * LOG:
 * LOG: RUDP connections at IDLE now work.  More tomorrow.
 * LOG:
 * LOG: Revision 1.15  2000/02/08 21:58:37  mmiers
 * LOG:
 * LOG:
 * LOG: Fine grain locking.
 * LOG:
 * LOG: Revision 1.14  2000/02/08 21:43:31  mmiers
 * LOG:
 * LOG:
 * LOG: Visual debugging.
 * LOG:
 * LOG: Revision 1.13  2000/02/08 18:23:22  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up RUDP.  Now to test this mess.
 * LOG:
 * LOG: Revision 1.12  2000/01/25 23:47:22  mmiers
 * LOG:
 * LOG:
 * LOG: More work on RUDP.  This is finally taking shape.
 * LOG:
 * LOG: Revision 1.11  2000/01/24 23:13:49  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating.
 * LOG:
 * LOG: Revision 1.10  2000/01/21 22:13:15  mmiers
 * LOG:
 * LOG: Checkpoint changes.  Include routing behavior change for
 * LOG: Rajesh.
 * LOG:
 * LOG: Revision 1.9  2000/01/18 00:20:25  mmiers
 * LOG: First complete (more or less) cut of RUDP.
 * LOG:
 * LOG: Revision 1.8  2000/01/14 23:58:33  mmiers
 * LOG:
 * LOG:
 * LOG: More cleanup.
 * LOG:
 * LOG: Revision 1.7  2000/01/14 23:25:44  mmiers
 * LOG:
 * LOG:
 * LOG: Work with RUDP more.
 * LOG:
 * LOG: Revision 1.6  2000/01/06 23:44:14  mmiers
 * LOG:
 * LOG:
 * LOG: RUDP update.
 * LOG:
 * LOG: Revision 1.5  2000/01/05 02:55:41  mmiers
 * LOG:
 * LOG: Continue with the initial RUDP implementation.
 * LOG:
 * LOG: Revision 1.4  2000/01/05 00:24:58  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks for RUDP.
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

#if !defined(ITS_RUDP_H)
#define ITS_RUDP_H

#include <its.h>
#include <its_sockets.h>
#include <its_callback.h>
#include <its_transports.h>
#include <its_ip_trans.h>
#include <rudp_msgs.h>

#ident "$Id: its_rudp.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

/*
 * All they need for the API.
 */
#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * this is a first guess.  Probably wrong at this point.  Server
 * should do bind()/recvfrom() (wait for SYN segments), client should
 * do bind()/sendto() (send SYN segment, wait for recvmsg()).
 *
 * Note that ITS_SocketInfo (which is exposed in the SUPPORT headers)
 * contains bind() information about the client.  (addr, addrlen).
 */
typedef enum
{
    RUDP_IDLE,
    RUDP_LISTEN,
    RUDP_SYN_RCVD,
    RUDP_SYN_SENT,
    RUDP_OPEN,
    RUDP_TRANSFER,
    RUDP_CONN_FAIL,
    RUDP_CLOSE_WAIT,
    RUDP_CLOSED
}
RUDP_MACHINE_STATE;

/*
 * signals
 */
typedef enum
{
    /* backward signals */
    RUDP_MSG_CONN_OPEN          = 0,
    RUDP_MSG_CONN_REFUSED       = 1,
    RUDP_MSG_CONN_CLOSING       = 2,
    RUDP_MSG_CONN_FAILURE       = 3,
    RUDP_MSG_CONN_RESET         = 4,
    RUDP_MSG_CONN_TRANS_STATE   = 5,
    RUDP_MSG_CONN_TRANS_FAIL    = 6,
    RUDP_MSG_SEND_OVERFLOW      = 7
}
RUDP_UMSG_TYPE;

/*
 * RUDP timers
 */
typedef struct
{
    enum
    {
        RUDP_T1,        /* OpenWaitTimer    */
        RUDP_T2,        /* OpenClose        */
        RUDP_T3,        /* Retransmit       */
        RUDP_T4,        /* CumAck           */
        RUDP_T5,        /* Transfer State   */
        RUDP_T6,        /* Keepalive        */
        RUDP_T7         /* AutoReset        */
    }
    timerID;
    ITS_UINT    connID; /* OpenWait */
}
RUDP_TimerContext;

/*
 * the user sets these values as required for each endpoint.
 */
typedef RUDP_SYN_DATA   RUDP_EndPointParams;

#define RUDP_MAX_HOST_NAME_LEN  128


typedef struct
{
    RUDP_UMSG_TYPE  type;
    ITS_USHORT      connID;
}
ITS_RUDP_CALLBACK_DATA;

/*
 * the following are not user addressable.
 */
typedef struct
{
    ITS_OCTET   maxOpenAttempts;    /* maximum open attempts (5)      */
    ITS_OCTET   maxSyncAttempts;    /* maximum SYN attempts           */
    ITS_OCTET   syncAttemptCount;   /* count of SYN attempts          */
    ITS_OCTET   sendNext;           /* sequence number of next seg tx */
    ITS_OCTET   iss;                /* initial send sequence number   */
    ITS_OCTET   rcvCur;             /* seq num of last in seq rx seg  */
    ITS_OCTET   irs;                /* initial receive sequence num   */
    ITS_OCTET   timedAck;           /* seq num of current retrans seg */
    ITS_OCTET   retransCount;       /* count of retrans attempts      */
    ITS_OCTET   cumAckCount;        /* count of segs awaiting ack     */
    ITS_OCTET   oosCount;           /* count of OOS segs              */
    ITS_OCTET   openWaitCount;      /* SYN transmit count             */
    ITS_USHORT  openWaitTimeout;    /* open wait (1 sec)              */
    ITS_USHORT  openCloseTimeout;   /* close wait (1 sec)             */
    ITS_USHORT  autoResetTimeout;   /* reset timeout (open * count)   */
    ITS_BOOLEAN recvTransferDone;   /* ?? */
    ITS_BOOLEAN okToSend;           /* ?? */
    ITS_BOOLEAN sendTransferDone;   /* ?? */
    ITS_BOOLEAN transferInitiator;  /* self explanatory, I think */
}
RUDP_ContextParams;

typedef struct
{
    RUDP_MACHINE_STATE  state;
    ITS_UINT            localConnID;
    ITS_UINT            remoteConnID;
    ITS_UINT            transferConnID;
    ITS_BOOLEAN         isActive;
    RUDP_EndPointParams uparams;
    RUDP_ContextParams  cparams;
    CALLBACK_Manager    *callbacks;
    ITS_MUTEX           lock;
    ITS_RUDP_MSG        **sendQueue;
    ITS_RUDP_MSG        **recvQueue;
    ITS_RUDP_MSG        **oosQueue;
    ITS_EVENT           **userQueue;
    ITS_USHORT          sendQueueCount;
    ITS_USHORT          recvQueueCount;
    ITS_USHORT          oosQueueCount;
    ITS_USHORT          pad;
    ITS_OCTET           *sendBuf;
    ITS_OCTET           *recvBuf;
    ITS_USHORT          curSendSegSize;
    ITS_USHORT          curRecvSegSize;
    ITS_SERIAL          openWait;
    ITS_SERIAL          openClose;
    ITS_SERIAL          retrans;
    ITS_SERIAL          cumAck;
    ITS_SERIAL          transferState;
    ITS_SERIAL          keepAlive;
    ITS_SERIAL          autoReset;
}
RUDP_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    SOCKTRAN_ObjectPart     socket;
    RUDP_ObjectPart         rudp;
}
RUDP_Manager;

#define RUDP_STATE(x) \
    (((RUDP_Manager *)(x))->rudp.state)

#define RUDP_LOCAL_CONN_ID(x) \
    (((RUDP_Manager *)(x))->rudp.localConnID)

#define RUDP_REMOTE_CONN_ID(x) \
    (((RUDP_Manager *)(x))->rudp.remoteConnID)

#define RUDP_TRANSFER_CONN_ID(x) \
    (((RUDP_Manager *)(x))->rudp.transferConnID)

#define RUDP_IS_ACTIVE(x) \
    (((RUDP_Manager *)(x))->rudp.isActive)

#define RUDP_UPARAMS(x) \
    (((RUDP_Manager *)(x))->rudp.uparams)

#define RUDP_CPARAMS(x) \
    (((RUDP_Manager *)(x))->rudp.cparams)

#define RUDP_CALLBACKS(x) \
    (((RUDP_Manager *)(x))->rudp.callbacks)

#define RUDP_LOCK(x) \
    (((RUDP_Manager *)(x))->rudp.lock)

#define RUDP_SEND_QUEUE(x) \
    (((RUDP_Manager *)(x))->rudp.sendQueue)

#define RUDP_RECV_QUEUE(x) \
    (((RUDP_Manager *)(x))->rudp.recvQueue)

#define RUDP_OOS_QUEUE(x) \
    (((RUDP_Manager *)(x))->rudp.oosQueue)

#define RUDP_USER_QUEUE(x) \
    (((RUDP_Manager *)(x))->rudp.userQueue)

#define RUDP_SEND_QUEUE_COUNT(x) \
    (((RUDP_Manager *)(x))->rudp.sendQueueCount)

#define RUDP_RECV_QUEUE_COUNT(x) \
    (((RUDP_Manager *)(x))->rudp.recvQueueCount)

#define RUDP_OOS_QUEUE_COUNT(x) \
    (((RUDP_Manager *)(x))->rudp.oosQueueCount)

#define RUDP_SEND_BUF(x) \
    (((RUDP_Manager *)(x))->rudp.sendBuf)

#define RUDP_RECV_BUF(x) \
    (((RUDP_Manager *)(x))->rudp.recvBuf)

#define RUDP_CUR_SEND_SEG_SIZE(x) \
    (((RUDP_Manager *)(x))->rudp.curSendSegSize)

#define RUDP_CUR_RECV_SEG_SIZE(x) \
    (((RUDP_Manager *)(x))->rudp.curRecvSegSize)

#define RUDP_OPEN_WAIT(x) \
    (((RUDP_Manager *)(x))->rudp.openWait)

#define RUDP_OPEN_CLOSE(x) \
    (((RUDP_Manager *)(x))->rudp.openClose)

#define RUDP_RETRANS(x) \
    (((RUDP_Manager *)(x))->rudp.retrans)

#define RUDP_CUM_ACK(x) \
    (((RUDP_Manager *)(x))->rudp.cumAck)

#define RUDP_TRANSFER_STATE(x) \
    (((RUDP_Manager *)(x))->rudp.transferState)

#define RUDP_KEEPALIVE(x) \
    (((RUDP_Manager *)(x))->rudp.keepAlive)

#define RUDP_AUTO_RESET(x) \
    (((RUDP_Manager *)(x))->rudp.autoReset)

#define RUDPTRAN_LOCAL_ENDPOINT_CLASS_NAME   "RUDP LocalEnd"
#define RUDPTRAN_REMOTE_ENDPOINT_CLASS_NAME  "RUDP RemoteEnd"

#if !defined(RUDP_IMPLEMENTATION)
#define RUDPDLLAPI   ITSDLLAPI
#else
#if defined(WIN32)
#define RUDPDLLAPI   __declspec(dllexport)
#else
#define RUDPDLLAPI
#endif /* WIN32 */
#endif

RUDPDLLAPI extern TRANSPORT_ClassRec   itsRUDPTRAN_LocalClassRec;
RUDPDLLAPI extern ITS_Class            itsRUDPTRAN_LocalClass;
RUDPDLLAPI extern TRANSPORT_ClassRec   itsRUDPTRAN_RemoteClassRec;
RUDPDLLAPI extern ITS_Class            itsRUDPTRAN_RemoteClass;

/*
 * the API.  Most everything is hidden under the hood.
 * Send using TRANSPORT_PutEvent().  Receive using
 * ITS_GetNextEvent() and friends.
 */
RUDPDLLAPI RUDP_Manager* RUDP_Open(const char *name,
                                   ITS_USHORT instance,
                                   ITS_UINT mask,
                                   RUDP_EndPointParams *params,
                                   ITS_CALLBACK callback);
RUDPDLLAPI RUDP_Manager* RUDP_Listen(const char *name,
                                     ITS_USHORT instance,
                                     ITS_UINT mask,
                                     RUDP_EndPointParams *params,
                                     ITS_CALLBACK callback);
RUDPDLLAPI void    RUDP_Close(RUDP_Manager* handle);
RUDPDLLAPI int     RUDP_TransferState(RUDP_Manager *ctxt, ITS_UINT connID);

/*
 * special class for RUDP management
 */
typedef ITS_ClassRec            RUDP_ClassRec;

#define RUDP_CLASS_NAME         "RUDP_CLASS"

RUDPDLLAPI extern RUDP_ClassRec            itsRUDP_ClassRec;
RUDPDLLAPI extern ITS_Class                itsRUDP_Class;

#if defined(__cplusplus)
}
#endif

#endif /* ITS_RUDP_H */
