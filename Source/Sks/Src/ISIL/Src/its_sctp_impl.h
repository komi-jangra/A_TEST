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
 *  ID: $Id: its_sctp_impl.h,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:04  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:32:02  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:36  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:57  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.30.1  2005/01/04 11:40:32  csireesh
 * LOG: SCTP OAM changes
 * LOG:
 * LOG: Revision 7.2  2002/10/02 21:48:26  pmandal
 * LOG: Start building on windows
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/08/15 16:09:55  lbana
 * LOG: get updates in pr5 to current
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2002/02/27 22:57:28  vnitin
 * LOG: Adding code for Retrive buffer and SSN (BSNT)
 * LOG:
 * LOG: Revision 5.3  2002/02/19 15:52:13  vnitin
 * LOG: Fixing First Data Sack
 * LOG:
 * LOG: Revision 5.2  2002/01/17 22:44:20  vnitin
 * LOG: Adding checksum CRC32C: See Checksum Note
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:10  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.7  2001/08/16 20:25:24  vnitin
 * LOG: Modified code for better maintainability (comments)
 * LOG:
 * LOG: Revision 4.6  2001/08/09 14:47:35  vnitin
 * LOG:
 * LOG: oopS!! removed binary character..
 * LOG:
 * LOG: Revision 4.5  2001/08/01 21:24:27  vnitin
 * LOG: Enhanced SCTP as per Implementors Guide 01. 
 * LOG: Includes fast-retransmit , shutdown and new OpErr
 * LOG:
 * LOG: Revision 4.3  2001/07/11 19:24:12  mmiers
 * LOG: forward port the SCTP work.
 * LOG:
 * LOG: Revision 3.8.2.1  2001/07/06 22:13:24  vnitin
 * LOG: Adding SCTP MIB support and fixing other problems like shutdown logic
 * LOG:
 * LOG: Revision 3.8  2000/11/17 23:09:52  mmiers
 * LOG: clean up on SCTP some.
 * LOG:
 * LOG: Revision 3.7  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.28  2000/11/02 00:20:44  mmiers
 * LOG: Some code cleanup from after the bakeoff.  Get it structured
 * LOG: so that I can stand to read it.
 * LOG:
 * LOG: Revision 3.27  2000/10/30 16:18:23  mmiers
 * LOG: Post bakeoff.  Now to clean up.
 * LOG:
 * LOG: Revision 3.26  2000/10/22 20:27:44  mmiers
 * LOG: Add static cookie life extension.
 * LOG:
 * LOG: Revision 3.25  2000/10/21 22:45:06  mmiers
 * LOG: Surprising results running with efence.
 * LOG:
 * LOG: Revision 3.24  2000/10/21 01:10:33  mmiers
 * LOG: More debugging
 * LOG:
 * LOG: Revision 3.23  2000/10/19 23:19:27  mmiers
 * LOG: More testing bug fixes.
 * LOG:
 * LOG: Revision 3.22  2000/10/18 23:15:16  mmiers
 * LOG: Debug with Solaris refimpl.  Bug handling multiple interfaces.
 * LOG:
 * LOG: Revision 3.21  2000/10/18 17:21:39  mmiers
 * LOG: Last bug (hah!)
 * LOG:
 * LOG: Revision 3.20  2000/10/18 01:11:39  mmiers
 * LOG: More debugging.  Slow start is still broken.
 * LOG:
 * LOG: Revision 3.19  2000/10/17 18:25:52  mmiers
 * LOG: Retransmit working.
 * LOG:
 * LOG: Revision 3.18  2000/10/16 22:41:58  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.17  2000/10/16 20:29:32  mmiers
 * LOG: Clean up.  Debugging almost done.
 * LOG:
 * LOG: Revision 3.16  2000/10/15 18:50:39  mmiers
 * LOG: Test program done.  Now debugging is all that's left.
 * LOG:
 * LOG: Revision 3.15  2000/10/15 01:38:46  mmiers
 * LOG: This is about there.  IOCTLs in, think about streams an test program.
 * LOG:
 * LOG: Revision 3.14  2000/10/13 23:36:34  mmiers
 * LOG: 99.3 percent.  Now just debug glue and stream API.
 * LOG:
 * LOG: Revision 3.13  2000/10/13 23:01:14  mmiers
 * LOG: 99 percent done.  Debug the glue, finish the ULP, and streams.
 * LOG:
 * LOG: Revision 3.12  2000/10/13 18:12:46  mmiers
 * LOG: Ok, got a good bit of the API.  Last is data translation.
 * LOG:
 * LOG: Revision 3.11  2000/10/12 23:31:52  mmiers
 * LOG: Ok, cleaned up.  Tomorrow the hookup completes.
 * LOG:
 * LOG: Revision 3.10  2000/10/12 18:35:30  mmiers
 * LOG: Got it working.  Now for testing and completing the API
 * LOG:
 * LOG: Revision 3.9  2000/10/11 22:29:01  mmiers
 * LOG: We can init, so can they, we can shutdown, so can they.
 * LOG:
 * LOG: Revision 3.8  2000/10/11 00:31:00  mmiers
 * LOG: Debugging.  Associates in both directions now.
 * LOG:
 * LOG: Revision 3.7  2000/10/10 17:10:04  mmiers
 * LOG: Associations work!
 * LOG:
 * LOG: Revision 3.6  2000/10/06 18:16:29  mmiers
 * LOG: Timer hookup.  Now ifc and testing.
 * LOG:
 * LOG: Revision 3.5  2000/10/05 20:41:29  mmiers
 * LOG: V13 upgrade.  Finish IFC, hookup timers, and test.
 * LOG:
 * LOG: Revision 3.4  2000/10/05 00:11:04  mmiers
 * LOG: Merge in the rev13 changes.
 * LOG:
 * LOG: Revision 3.3  2000/10/03 23:47:33  mmiers
 * LOG: Integrate some v13 stuff.  Nothing behavioral yet.
 * LOG:
 * LOG: Revision 3.2  2000/10/03 22:35:31  mmiers
 * LOG: All code enabled.  Final walkthrough and support integration
 * LOG: next, then debug.
 * LOG:
 * LOG: Revision 3.1  2000/10/03 21:17:08  mmiers
 * LOG: Today's installment.  Getting real close now.
 * LOG:
 * LOG: Revision 3.2  2000/10/02 22:15:52  mmiers
 * LOG: More work.
 * LOG:
 * LOG: Revision 3.1  2000/09/29 17:52:03  mmiers
 * LOG: OK.  Skeleton done, hook things together, rething its_sctp_trans.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_SCTP_IMPL_H)
#define ITS_SCTP_IMPL_H

#include <its_thread.h>
#include <its_hash.h>
#include <its_tq_trans.h>

#include <dbc_serv.h>

/* Checksum Preprocessor flag
 * Modifiy Makefile accordingly to
 * use correct checksum
 */
#if defined(SCTP_USE_ADLER)
#define SCTP_CHKSUM	ADLER_Chksum32
#elif defined(SCTP_USE_CRC32C)
#define SCTP_CHKSUM	CRC_Chksum32C
#else
/* #warning "You did not specify which SCTP checksum. Default is CRC32C."
 */
#define SCTP_CHKSUM	CRC_Chksum32C
#endif


/*
 * parser aid
 */
#define SCTP_MAX_PARAMS     16

typedef struct
{
    ITS_SCTP_CHUNK* currentChunk;
    ITS_SCTP_PARAM* params[SCTP_MAX_PARAMS];
}
ITS_SCTP_MSG_PCB;

/*
 * transport state
 */
typedef enum
{
    SCTP_CLOSED,
    SCTP_COOKIE_WAIT,
    SCTP_COOKIE_SENT,    /* This is COOKIE_ECHOED */
    SCTP_ESTABLISHED,
    SCTP_SHUTDOWN_PENDING,
    SCTP_SHUTDOWN_SENT,
    SCTP_SHUTDOWN_RECEIVED,
    SCTP_SHUTDOWN_ACK_SENT
}
SCTP_STATE;

/*
 * ULP notifications
 */
typedef enum
{
    SCTP_NOTIFY_ASSOC_UP,
    SCTP_NOTIFY_ASSOC_DOWN,
    SCTP_NOTIFY_ASSOC_RESTART,
    SCTP_NOTIFY_ASSOC_ABORTED,
    SCTP_NOTIFY_ASSOC_CANT_START,
    SCTP_NOTIFY_ASSOC_SHUTDOWN_DONE,
    SCTP_NOTIFY_INTF_DOWN,
    SCTP_NOTIFY_INTF_UP,
    SCTP_NOTIFY_CANT_DELIVER,
    SCTP_NOTIFY_SEND_ON_DOWN_STREAM,
    SCTP_NOTIFY_REMOTE_ERR,
    SCTP_NOTIFY_HB_RESPONSE,
    SCTP_NOTIFY_SSN_NOT_RETRIEVABLE,
    SCTP_NOTIFY_SSN_CONFIRM,
    SCTP_NOTIFY_RETRIVE_BUFFER,
    SCTP_NOTIFY_RETRIVE_BUFFER_COMP
}
SCTP_NOTIFICATION_TYPE;

typedef enum
{
    SCTP_TRANS_DOWN,
    SCTP_TRANS_UP
}
SCTP_TRANS_TSTATE;

typedef enum
{
    SCTP_TRANS_NO_HB,
    SCTP_TRANS_ALLOW_HB
}
SCTP_TRANS_HBSTATE;

/*****************************************************************************
 *
 * Generic management data.
 *
 *****************************************************************************/
/*
 * alarm levels
 */
typedef enum
{
    ALARM_OFF,
    ALARM_DEFAULT,
    ALARM_DEBUG,
    ALARM_DETAIL
}
MGMT_AlarmLevel;

/*****************************************************************************
 *
 * The SCTP General Configuration.
 *
 *****************************************************************************/
typedef struct
{
    MGMT_AlarmLevel alarmLevel;
    ITS_BOOLEAN     traceOn;     /* on(1), off(0) */
    ITS_CHAR       traceType[ITS_PATH_MAX];
    ITS_CHAR       traceOutput[ITS_PATH_MAX];
}
SCTPGeneralCfg;

/*
 * timer defaults
 */
#define SCTP_TIME_INIT_SECS     3       /* 1 seconds */
#define SCTP_TIME_INIT_USECS    0
#define SCTP_TIME_SEND_SECS     3       /* 1 seconds */
#define SCTP_TIME_SEND_USECS    0
#define SCTP_TIME_RECV_SECS     0       /* 200 ms */
#define SCTP_TIME_RECV_USECS    200000
#define SCTP_TIME_HB_SECS       3       /* 3 seconds */
#define SCTP_TIME_HB_USECS      0
#define SCTP_TIME_SHUT_SECS     0       /* 300 ms */
#define SCTP_TIME_SHUT_USECS    300000
#define SCTP_TIME_PMTU_SECS     600     /* 10 minutes */
#define SCTP_TIME_PMTU_USECS    0

/*
 * other defaults/constants
 */
#define SCTP_TIME_MAX_RTO_SECS          15
#define SCTP_TIME_MAX_RTO_USECS         0
#define SCTP_TIME_MIN_RTO_SECS          1
#define SCTP_TIME_MIN_RTO_USECS         0
#define SCTP_TIME_INIT_RTO_SECS         3
#define SCTP_RTO_ALGORITHM_VANJ         2 /* Van jacobson */
#define SCTP_RTO_ALGORITHM_OTHR         1 /* Other RTO Algo */

#define SCTP_DEFAULT_MAX_INIT       5
#define SCTP_DEFAULT_MAX_SEND       8
#define SCTP_DEFAULT_MAX_WINDOW     32768
#define SCTP_DEFAULT_SEGMENT_MTU    1500            /* ethernet */
#define SCTP_MAX_MTU                65535
#define SCTP_DEFAULT_COOKIE_LIFE    5
#define SCTP_MAX_BURST              4     /* To limit transmission after FR */

#define SCTP_KEYSIZE                ITS_SHASH_DIGESTSIZE
#define SCTP_MAX_TSN                0xFFFFFFFFU
#define SCTP_MAX_SEQ                0xFFFFU
#define SCTP_MIN_RWND               1500
#define SCTP_CLOCK_VARIANCE         10000

#define SCTP_MIB_UNKNOWN_ADDR       0x00
#define SCTP_MIB_IPv4_ADDR          0x01
#define SCTP_MIB_IPv6_ADDR          0x02

#define SCTP_CONGESTION_STAT        0x01

/*
 * implementation constants
 */
#define SCTP_MAX_DUP_TSNS   20

#define SCTP_MAX_STREAMS    256

#define SCTP_MAX_STALE_COOKIES  10

#define SCTP_STARTING_GAP_ARRAY_SZ  10000

typedef struct
{
    ITS_INT         initial;
    ITS_INT         min;
    ITS_INT         max;
    double          alpha;
    double          beta;
}
SCTP_RTO_CONTROL;

/*
 * timer ids
 */
typedef enum
{
    SCTP_TIMER_TYPE_NONE,
    SCTP_TIMER_TYPE_SEND,
    SCTP_TIMER_TYPE_RECV,
    SCTP_TIMER_TYPE_INIT,
    SCTP_TIMER_TYPE_SHUTDOWN,
    SCTP_TIMER_TYPE_SHUTDOWN_ACK,
    SCTP_TIMER_TYPE_HEARTBEAT,
    SCTP_TIMER_TYPE_COOKIE,
    SCTP_TIMER_TYPE_PATH_MTU_RAISE
}
SctpTimerType;

typedef enum
{
    SCTP_TIMER_IDLE,
    SCTP_TIMER_EXPIRED,
    SCTP_TIMER_RUNNING
}
SctpTimerState;

typedef enum
{
    SCTP_TIMER_START,
    SCTP_TIMER_STOP
}
SctpTimerCommand;

typedef enum
{
    SCTP_TIMER_ID_INIT,
    SCTP_TIMER_ID_RECV,
    SCTP_TIMER_ID_COOKIE,
    SCTP_TIMER_ID_SHUTDOWN,
    SCTP_TIMER_ID_PATH_MTU,
    SCTP_TIMER_ID_PER_NET,
    SCTP_TIMER_MIN_NUM_TIMERS

}
SctpTimerId;

typedef struct
{
    void            *timerInfo;
    int             countOf;
    SctpTimerType   timerType;
    SctpTimerState  running;
}
SCTP_TIMER;

/*
 * internal storage
 */
typedef struct timer_s
{
    struct timer_s *next;
    struct timer_s *prev;
    ITS_BOOLEAN     used;
    int             period;
    ITS_BOOLEAN     start;
    ITS_TIME        secs;
    ITS_TIME        usecs;
    SCTP_TIMER      arg;
}
SCTP_TIMER_IMPL;

/*
 * notification callback struct
 */
typedef struct
{
    SCTP_NOTIFICATION_TYPE  type;
    SOCK_AddrStore          *from;
    SCTP_API_SND_RCV        undelivered;
    ITS_USHORT              len;
    ITS_USHORT              ssn;
    void                    *data;
}
SCTP_NOTIF_STRUCT;

/*
 * the remote struct
 */
typedef struct
{
    ITS_USHORT              ipAddrType;
    SOCK_IPv4Addr           raddr;                  /* remote addr */
    ITS_OCTET               addrType;               /* Addr type ipv4-6*/
    ITS_USHORT              rport;                  /* remote port */
    ITS_UINT                errorCount;             /* error count */
    ITS_UINT                errorThreshold;         /* if count reaches this, go down */
    ITS_INT                 cwnd;                   /* congestion window */
    ITS_INT                 ssthresh;               /* ssthresh value */
    ITS_INT                 rto;                    /* retransmission timeout value */
    ITS_INT                 partialBytesAcked;      /* congestion */
    SCTP_TRANS_TSTATE       tState;                 /* transport state */
    SCTP_TRANS_HBSTATE      hbState;                /* heartbeats */
    ITS_INT                 pMTU;                   /* path mtu */
    ITS_BOOLEAN             rtoPending;             /* rto is pending */
    ITS_INT                 srtt;                   /* smoothed round trip time */
    ITS_INT                 rttvar;                 /* rtt variation */
    ITS_TIME                lastUsedSecs;           /* last time used. */
    ITS_TIME                lastUsedUSecs;          /* last time used. */
    ITS_BOOLEAN             hbPending;              /* heartbeat pending here */
    ITS_BOOLEAN             hbAcked;                /* heartbeat was acked */
    SCTP_TIMER              perDestTimer;           /* heartbeat timer */
    ITS_TIME                startTime;
}
SCTPTRAN_REMOTE_EP;

/*
 * Transmission Control Block
 */
#define UNSUPPORTED     "unsupported"   /*we do not support DNS names */
typedef struct
{
    ITS_USHORT                  src;                    /* source port */
    ITS_USHORT                  dest;                   /* dest port */
    ITS_UINT                    peerVerificationTag;    /* peer id */
    ITS_UINT                    localVerificationTag;   /* my id */
    ITS_POINTER                 cookie;                 /* remote's cookie */
    ITS_TIME                    cookieLife;             /* cookie lifetime */
    ITS_POINTER                 remoteName;             /* for DNS */
    ITS_UINT                    staleCookieCnt;         /* obvious */
    SCTP_STATE                  state;                  /* state of this association */
    ITS_BOOLEAN                 shutdownPending;        /* shutdown is pending */
    ITS_UINT                    sendMode;               /* mode flags */
    ITS_INT                     peerRwnd;               /* peer's rwnd */
    ITS_INT                     localRwnd;              /* our rwnd */
    ITS_UINT                    maxWindow;              /* max window size */
    ITS_UINT                    numRetrans;             /* retransmissions needed */
    ITS_USHORT                  maxMTU;                 /* max MTU on all ifcs */
    ITS_USHORT                  minMTU;                 /* min MTU on all ifcs */
    ITS_UINT                    nextTSN;                /* next TSN */
    ITS_UINT                    echoTSN;                /* last echo */
    ITS_UINT                    cwrTSN;                 /* cwr */
    ITS_UINT                    initialTSN;             /* initial TSN */
    ITS_UINT                    lastAckedTSN;           /* last TSN acked */
    ITS_UINT                    gapBaseTSN;             /* base TSN of gap */
    ITS_UINT                    gapHighestTSN;          /* highest TSN of gap */
    ITS_OCTET*                  gaps;                   /* gap array */
    ITS_UINT                    maxGaps;                /* array size */
    ITS_UINT*                   dups;                   /* duplications */
    ITS_UINT                    numDups;                /* num dups */
    ITS_UINT                    recvBufSize;            /* buffer size */
    ITS_UINT                    sendBufSize;            /* buffer size */
    LIST_Manager*               sendQueue;              /* pending ack */
    LIST_Manager*               fragQueue;              /* pending frags */
    LIST_Manager**              strmQueues;             /* ordered delivery */
    ITS_USHORT*                 inStreamSeqNums;        /* inbound seqnos */
    ITS_USHORT*                 outStreamSeqNums;       /* outbound seqnos */
    ITS_UINT                    tmpSendSeq;             /* stream 0 sends */
    ITS_UINT                    numInStreams;           /* number of input streams */
    ITS_UINT                    numOutStreams;          /* number of output streams */
    ITS_UINT                    primaryDest;            /* primary destination */
    ITS_INT                     lastDest;                /* last remote used */
    ITS_INT                     lastSrc;                 /* last remote input */
    ITS_BOOLEAN                 ecnAllowed;             /* do we handle ECN */
    ITS_BOOLEAN                 restrictAddress;        /* do we restrict addresses */
    ITS_UINT                    maxLocalEPs;            /* max array size */
    SCTPTRAN_REMOTE_EP*         remoteEPs;              /* transmitters */
    ITS_UINT                    numRemoteEPs;           /* num transmitters */
    ITS_UINT                    maxRemoteEPs;           /* max array size */
    ITS_UINT                    errorCount;             /* overall error count */
    ITS_UINT                    maxInitCount;           /* number of inits to error */
    ITS_UINT                    maxSendCount;           /* number of sends to error */
    ITS_UINT                    needToAck;              /* ack pending */
    ITS_INT                     *netAckSz;              /* net ack size */
    ITS_INT                     *netAckSz2;             /* net ack size 2 */
    ITS_SCTP_CHUNK              *ecnEcho;               /* echo chunk */
    ITS_SCTP_CHUNK              *cwr;                   /* cwr */
    ITS_SCTP_CHUNK              *opErr;                 /* operational error */
    ITS_UINT                    opErrSize;              /* size of above */
    LIST_Entry                  *retryHead;             /* retry list head */
    ITS_TIME                    initSecs;               /* init timer */
    ITS_TIME                    initUSecs;              /* init timer */
    ITS_TIME                    sendSecs;               /* send timer */
    ITS_TIME                    sendUSecs;              /* send timer */
    ITS_TIME                    recvSecs;               /* recv timer */
    ITS_TIME                    recvUSecs;              /* recv timer */
    ITS_TIME                    hbSecs;                 /* hb timer */
    ITS_TIME                    hbUSecs;                /* hb timer */
    ITS_TIME                    shutSecs;               /* shutdown timer */
    ITS_TIME                    shutUSecs;              /* shutdown timer */
    ITS_TIME                    pmtuSecs;               /* mtu timer */
    ITS_TIME                    pmtuUSecs;              /* mtu timer */
    ITS_TIME                    enterStateSecs;         /* enter state time */
    ITS_TIME                    enterStateUSecs;        /* enter state time */
    SCTP_RTO_CONTROL            rtoControl;             /* rto control */
    ITS_ULONG                   pegs[SCTP_PEG_COUNT];   /* measurements */
    SCTP_TIMER                  *timers;                /* timers */
    ITS_UINT                    numTimers;              /* number of timers */
    ITS_UINT                    numUnsent;
    ITS_TIME                    startTime;              /* Time - TCB create */
    ITS_USHORT                  fastRTXAcked;           /* Ack rcvd Fast RTX */
    ITS_USHORT                  maxBurst;               /* Max.Burst param */
    ITS_BOOLEAN                 firstDataAck;           /* Ack first data */
}
SCTP_TCB;

#define SCTP_TCB_SRC(x) \
    (((SCTP_TCB *)(x))->src)

#define SCTP_TCB_DEST(x) \
    (((SCTP_TCB *)(x))->dest)

#define SCTP_TCB_PEER_VTAG(x) \
    (((SCTP_TCB *)(x))->peerVerificationTag)

#define SCTP_TCB_LOCAL_VTAG(x) \
    (((SCTP_TCB *)(x))->localVerificationTag)

#define SCTP_TCB_COOKIE(x) \
    (((SCTP_TCB *)(x))->cookie)

#define SCTP_TCB_COOKIE_LIFE(x) \
    (((SCTP_TCB *)(x))->cookieLife)

#define SCTP_TCB_REMOTE_NAME(x) \
    (((SCTP_TCB *)(x))->remoteName)

#define SCTP_TCB_STALE_COOKIE_CNT(x) \
    (((SCTP_TCB *)(x))->staleCookieCnt)

#define SCTP_TCB_STATE(x) \
    (((SCTP_TCB *)(x))->state)

#define SCTP_TCB_SHUTDOWN_PENDING(x) \
    (((SCTP_TCB *)(x))->shutdownPending)

#define SCTP_TCB_LOCAL_RWND(x) \
    (((SCTP_TCB *)(x))->localRwnd)

#define SCTP_TCB_PEER_RWND(x) \
    (((SCTP_TCB *)(x))->peerRwnd)

#define SCTP_TCB_MAX_WIND(x) \
    (((SCTP_TCB *)(x))->maxWindow)

#define SCTP_TCB_NEXT_TSN(x) \
    (((SCTP_TCB *)(x))->nextTSN)

#define SCTP_TCB_ECHO_TSN(x) \
    (((SCTP_TCB *)(x))->echoTSN)

#define SCTP_TCB_CWR_TSN(x) \
    (((SCTP_TCB *)(x))->cwrTSN)

#define SCTP_TCB_INIT_TSN(x) \
    (((SCTP_TCB *)(x))->initialTSN)

#define SCTP_TCB_NUM_RETRANS(x) \
    (((SCTP_TCB *)(x))->numRetrans)

#define SCTP_TCB_SEND_MODE(x) \
    (((SCTP_TCB *)(x))->sendMode)

#define SCTP_TCB_MAX_MTU(x) \
    (((SCTP_TCB *)(x))->maxMTU)

#define SCTP_TCB_MIN_MTU(x) \
    (((SCTP_TCB *)(x))->minMTU)

#define SCTP_TCB_LAST_ACKED_TSN(x) \
    (((SCTP_TCB *)(x))->lastAckedTSN)

#define SCTP_TCB_BASE_GAP_TSN(x) \
    (((SCTP_TCB *)(x))->gapBaseTSN)

#define SCTP_TCB_HIGHEST_GAP_TSN(x) \
    (((SCTP_TCB *)(x))->gapHighestTSN)

#define SCTP_TCB_GAPS(x) \
    (((SCTP_TCB *)(x))->gaps)

#define SCTP_TCB_MAX_GAPS(x) \
    (((SCTP_TCB *)(x))->maxGaps)

#define SCTP_TCB_DUPS(x) \
    (((SCTP_TCB *)(x))->dups)

#define SCTP_TCB_NUM_DUPS(x) \
    (((SCTP_TCB *)(x))->numDups)

#define SCTP_TCB_SEND_QUEUE(x) \
    (((SCTP_TCB *)(x))->sendQueue)

#define SCTP_TCB_FRAG_QUEUE(x) \
    (((SCTP_TCB *)(x))->fragQueue)

#define SCTP_TCB_STREAM_QUEUES(x) \
    (((SCTP_TCB *)(x))->strmQueues)

#define SCTP_TCB_RECV_SEQ_NUMS(x) \
    (((SCTP_TCB *)(x))->inStreamSeqNums)

#define SCTP_TCB_XMIT_SEQ_NUMS(x) \
    (((SCTP_TCB *)(x))->outStreamSeqNums)

#define SCTP_TCB_TMP_XMIT_SEQ_NUM(x) \
    (((SCTP_TCB *)(x))->tmpSendSeq)

#define SCTP_TCB_NUM_IN_STREAMS(x) \
    (((SCTP_TCB *)(x))->numInStreams)

#define SCTP_TCB_NUM_OUT_STREAMS(x) \
    (((SCTP_TCB *)(x))->numOutStreams)

#define SCTP_TCB_PRIMARY_DEST(x) \
    (((SCTP_TCB *)(x))->primaryDest)

#define SCTP_TCB_LAST_DEST(x) \
    (((SCTP_TCB *)(x))->lastDest)

#define SCTP_TCB_LAST_SRC(x) \
    (((SCTP_TCB *)(x))->lastSrc)

#define SCTP_TCB_ECN_ALLOWED(x) \
    (((SCTP_TCB *)(x))->ecnAllowed)

#define SCTP_TCB_RESTRICT_ADDRS(x) \
    (((SCTP_TCB *)(x))->restrictAddress)

#define SCTP_TCB_REMOTE_EPS(x) \
    (((SCTP_TCB *)(x))->remoteEPs)

#define SCTP_TCB_NUM_REMOTE_EPS(x) \
    (((SCTP_TCB *)(x))->numRemoteEPs)

#define SCTP_TCB_MAX_REMOTE_EPS(x) \
    (((SCTP_TCB *)(x))->maxRemoteEPs)

#define SCTP_TCB_ERROR_COUNT(x) \
    (((SCTP_TCB *)(x))->errorCount)

#define SCTP_TCB_MAX_INIT_COUNT(x) \
    (((SCTP_TCB *)(x))->maxInitCount)

#define SCTP_TCB_MAX_SEND_COUNT(x) \
    (((SCTP_TCB *)(x))->maxSendCount)

#define SCTP_TCB_TOT_ACK_SIZE(x) \
    (((SCTP_TCB *)(x))->netAckSz)

#define SCTP_TCB_NUM_FAST_RETRANS(x) \
    (((SCTP_TCB *)(x))->netAckSz)

#define SCTP_TCB_NEW_ACK_SIZE(x) \
    (((SCTP_TCB *)(x))->netAckSz2)

#define SCTP_TCB_NEED_TO_ACK(x) \
    (((SCTP_TCB *)(x))->needToAck)

#define SCTP_TCB_ECN_ECHO(x) \
    (((SCTP_TCB *)(x))->ecnEcho)

#define SCTP_TCB_CWR(x) \
    (((SCTP_TCB *)(x))->cwr)

#define SCTP_TCB_OP_ERR(x) \
    (((SCTP_TCB *)(x))->opErr)

#define SCTP_TCB_OP_ERR_SIZE(x) \
    (((SCTP_TCB *)(x))->opErrSize)

#define SCTP_TCB_RETRY_HEAD(x) \
    (((SCTP_TCB *)(x))->retryHead)

#define SCTP_TCB_INIT_SECS(x) \
    (((SCTP_TCB *)(x))->initSecs)

#define SCTP_TCB_INIT_USECS(x) \
    (((SCTP_TCB *)(x))->initUSecs)

#define SCTP_TCB_SEND_SECS(x) \
    (((SCTP_TCB *)(x))->sendSecs)

#define SCTP_TCB_SEND_USECS(x) \
    (((SCTP_TCB *)(x))->sendUSecs)

#define SCTP_TCB_RECV_SECS(x) \
    (((SCTP_TCB *)(x))->recvSecs)

#define SCTP_TCB_RECV_USECS(x) \
    (((SCTP_TCB *)(x))->recvUSecs)

#define SCTP_TCB_HB_SECS(x) \
    (((SCTP_TCB *)(x))->hbSecs)

#define SCTP_TCB_HB_USECS(x) \
    (((SCTP_TCB *)(x))->hbUSecs)

#define SCTP_TCB_SHUT_SECS(x) \
    (((SCTP_TCB *)(x))->shutSecs)

#define SCTP_TCB_SHUT_USECS(x) \
    (((SCTP_TCB *)(x))->shutUSecs)

#define SCTP_TCB_PMTU_SECS(x) \
    (((SCTP_TCB *)(x))->pmtuSecs)

#define SCTP_TCB_PMTU_USECS(x) \
    (((SCTP_TCB *)(x))->pmtuUSecs)

#define SCTP_TCB_ENTER_STATE_SECS(x) \
    (((SCTP_TCB *)(x))->enterStateSecs)

#define SCTP_TCB_ENTER_STATE_USECS(x) \
    (((SCTP_TCB *)(x))->enterStateUSecs)

#define SCTP_TCB_RTO_CTRL(x) \
    (((SCTP_TCB *)(x))->rtoControl)

#define SCTP_TCB_PEGS(x) \
    (((SCTP_TCB *)(x))->pegs)

#define SCTP_TCB_TIMERS(x) \
    (((SCTP_TCB *)(x))->timers)

#define SCTP_TCB_NUM_TIMERS(x) \
    (((SCTP_TCB *)(x))->numTimers)

#define SCTP_TCB_NUM_UNSENT(x) \
    (((SCTP_TCB *)(x))->numUnsent)

#define SCTP_TCB_START_TIME(x) \
    (((SCTP_TCB *)(x))->startTime)

#define SCTP_TCB_FAST_RTX_ACKED(x) \
    (((SCTP_TCB *)(x))->fastRTXAcked)

#define SCTP_TCP_MAX_BURST(x) \
    (((SCTP_TCB *)(x))->maxBurst)

#define SCTP_TCB_NEED_FIRST_DATA_ACK(x) \
    (((SCTP_TCB *)(x))->firstDataAck)

/*
 * datagram states
 */
typedef enum
{
    SCTP_DATAGRAM_UNSENT,
    SCTP_DATAGRAM_SENT,
    /* the gap is for "third time is the charm" fast retransmit */
    SCTP_DATAGRAM_RESEND = SCTP_DATAGRAM_SENT + 3,
    SCTP_DATAGRAM_ACKED = SCTP_DATAGRAM_RESEND + 10000,
    SCTP_DATAGRAM_INBOUND,
    SCTP_DATAGRAM_TX_READY,
    SCTP_DATAGRAM_MARKED = SCTP_DATAGRAM_TX_READY + 10000
}
SCTP_DGRAM_STATE;

/*
 * what lives in the queues
 */
typedef struct
{
    union
    {
        SOCK_IPv4Addr   v4;
        SOCK_IPv6Addr   v6;
    }
    toAddr;
    ITS_UINT            tsn;
    ITS_USHORT          seqNum;
    ITS_USHORT          stream;
    SCTP_DGRAM_STATE    sent;
    ITS_INT             lastRemote;
    ITS_UINT            sendCount;
    ITS_TIME            rtxSecs;
    ITS_TIME            rtxUsecs;
    ITS_TIME            sendSecs;
    ITS_TIME            sendUSecs;
    SCTP_TCB*           assoc;
    void *              data;
    ITS_UINT            payloadType;
    ITS_UINT            context;
    ITS_USHORT          len;
    ITS_OCTET           flags;
    ITS_OCTET           pad;
    ITS_BOOLEAN         fastRTXFlag; /* Ture - DG being Fast Retransmitted */
}
SCTP_TX_ENTRY;

#define SCTPTRAN_RE_REM_ADDR_TYPE(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->ipAddrType)

#define SCTPTRAN_RE_REM_ADDR(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->raddr)

#define SCTPTRAN_RE_REM_PORT(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->rport)

#define SCTPTRAN_RE_ADDR_TYPE(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->addrType)

#define SCTPTRAN_RE_ERROR_COUNT(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->errorCount)

#define SCTPTRAN_RE_ERROR_THRESHOLD(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->errorThreshold)

#define SCTPTRAN_RE_CONG_WIND(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->cwnd)

#define SCTPTRAN_RE_SS_THRESH(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->ssthresh)

#define SCTPTRAN_RE_RTO(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->rto)

#define SCTPTRAN_RE_SRTT(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->srtt)

#define SCTPTRAN_RE_RTTVAR(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->rttvar)

#define SCTPTRAN_RE_PARTIAL_BYTES_ACKED(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->partialBytesAcked)

#define SCTPTRAN_RE_TSTATE(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->tState)

#define SCTPTRAN_RE_HBSTATE(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->hbState)

#define SCTPTRAN_RE_PATH_MTU(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->pMTU)

#define SCTPTRAN_RE_RTO_PENDING(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->rtoPending)

#define SCTPTRAN_RE_LAST_USED_SECS(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->lastUsedSecs)

#define SCTPTRAN_RE_LAST_USED_USECS(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->lastUsedUSecs)

#define SCTPTRAN_RE_HB_PENDING(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->hbPending)

#define SCTPTRAN_RE_HB_ACKED(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->hbAcked)

#define SCTPTRAN_RE_HB_TIMER(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->perDestTimer)

#define SCTPTRAN_RE_START_TIME(x) \
    (((SCTPTRAN_REMOTE_EP *)(x))->startTime)

/*
 * SCTP instance struct
 */
#define SCTP_NEED_SOCKS     3

#define SCTP_RAW_SOCKET     0
#define SCTP_ICMP_SOCKET    1
#define SCTP_SCTP_SOCKET    2

/*
 * hash table contents.
 */
typedef struct _SCTP_HE
{
    struct _SCTP_HE     *next;
    SCTP_TCB            *tcb;
}
SCTP_HashEntry;

/*
 * socket API data
 */
typedef struct
{
    SOCK_AddrStore  *addrs;
    ITS_UINT        numAddrs;
    SOCK_AddrStore  *listen;
    ITS_UINT        numListen;
    ITS_UINT        curDepth;
    SOCK_AddrStore  *connects;
    ITS_UINT        numConnects;
    ITS_BOOLEAN     accepting;
    ITS_BOOLEAN     inUse;
    ITS_USHORT      port;
    ITS_USHORT      preOpens;
    ITS_USHORT      maxInbound;
    ITS_USHORT      sendAttempts;
    ITS_UINT        maxCredit;
    ITS_OCTET       type;
    ITS_TIME        initSecs;
    ITS_TIME        initUSecs;
    ITS_TIME        sendSecs;
    ITS_TIME        sendUSecs;
    ITS_TIME        recvSecs;
    ITS_TIME        recvUSecs;
    ITS_TIME        hbSecs;
    ITS_TIME        hbUSecs;
    ITS_TIME        shutSecs;
    ITS_TIME        shutUSecs;
    ITS_TIME        pmtuSecs;
    ITS_TIME        pmtuUSecs;
    ITS_TIME        startTime;
    ITS_BOOLEAN     hbOn;
}
SCTP_SOCKET_DATA;

/*
 * interface to API
 */
#define UOFFSET(x)  ((x) - SCTP_FIRST_USER)


/*
 * SCTP MIB PEGS
 */

/*
 * State related MIB General Variables: number of associations
 */
enum SCTP_MIB_STATE_PEGS
{
    CURR_ESTAB,          /* currently: ESTABLISHED, SHUTDOWN-RECEIVED or SHUTDOWN-PENDING */
    ACTIVE_ESTAB,        /* COOKIE-ECHOED -> ESTABLISHED, ULP initiated */
    PASSIVE_ESTAB,       /* CLOSED -> ESTABLISHED, Remote initiated */
    ABORTED,            /* Any state -> ABORT, Ungraceful  */
    NUM_SHUTDOWNS,       /* [SHUTDOWN-SENT,SHUTDOWN-ACK-SENT] -> CLOSED, graceful */
    MAX_STATE_PEGS,
    STATE_PEG_COUNT = MAX_STATE_PEGS
};

/*
 * Statistics MIB General Variables 
 */
enum SCTP_MIB_STAT_PEGS
{
    NUM_OUT_OF_BLUE,       /* Out of blue packets received */
    NUM_SENT_CHUNKS,      /* # of data & control chunks sent, no retransmission */
    NUM_REC_CHUNKS,       /* # of data & control chunks received, no duplicates */
    NUM_OUTOFORDER_SENT,  /* # data chunks sent with u bit set to 1 */
    NUM_OUTOFORDER_REC,   /* # data chunks received with u bit set to 1 */
    NUM_FRAG_USR_MSGS,     /* # User messages fragmented due to MTU */
    NUM_REASMB_USR_MSGS,  /* # of user messages reassembled */
    MAX_STAT_PEGS,
    STAT_PEG_COUNT = MAX_STAT_PEGS
};
/*
 * manager structure
 */
typedef struct
{
    ITS_SocketInfo      *socks[SCTP_NEED_SOCKS];
    SOCK_AddrStore      *nets;
    SOCK_AddrStore      *masks;
    SOCK_AddrStore      *broads;
    ITS_UINT            numNets;
    ITS_THREAD          rthread;
    ITS_THREAD          wthread;
    ITS_BOOLEAN         doReadExit;
    ITS_BOOLEAN         doWriteExit;
    TQUEUETRAN_Manager  *queue;
    ITS_OCTET           *readBuf;
    ITS_OCTET           *sendBuf;
    ITS_OCTET           *buildBuf;
    ITS_MUTEX           gate;
    HASH_Table          tcbs;
    ITS_USHORT          icmpCnt;
    ITS_USHORT          ipCnt;
    SCTP_TIMER_IMPL     *freeTimers;
    SCTP_TIMER_IMPL     *usedTimers;
    CALLBACK_Manager*   ulpCallbacks;
    ITS_UINT            secret[SCTP_KEYSIZE/sizeof(ITS_UINT)];
    SCTP_SOCKET_DATA    usocks[SCTP_LAST_USER - SCTP_FIRST_USER + 1];
    ITS_USHORT          ports[1<<16];
    SCTP_RTO_CONTROL    rtoControl;
    ITS_USHORT          maxInitAttempts;
    ITS_TIME            cookieLife;
    ITS_UINT            statePegs[STATE_PEG_COUNT];
    ITS_ULONG           statPegs[STAT_PEG_COUNT];
}
SCTP_Manager;


void SCTP_Console(DBC_Server *dbc, const char *cmdLine);

#define SCTP_MGR_STATE_PEGS(x) \
    (((SCTP_Manager *)(x))->statePegs)

#define SCTP_MGR_STAT_PEGS(x) \
    (((SCTP_Manager *)(x))->statPegs)

#define SCTP_MGR_RTO_CTRL(x) \
    (((SCTP_Manager *)(x))->rtoControl)

#define SCTP_MGR_MAX_INIT(x) \
    (((SCTP_Manager *)(x))->maxInitAttempts)

#define SCTP_MGR_COOKIE_LIFE(x) \
    (((SCTP_Manager *)(x))->cookieLife)

#endif /* ITS_SCTP_H */
