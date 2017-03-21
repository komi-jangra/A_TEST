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
 * LOG: Revision 8.2  2005/03/21 13:50:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1.4.3  2005/01/11 12:24:36  craghavendra
 * LOG: Syslog Enhancements.
 * LOG:
 * LOG: Revision 7.2.10.1.4.2  2004/12/15 12:14:55  asingh
 * LOG: separate traces for SCTP
 * LOG:
 * LOG: Revision 7.2.10.1.4.1  2004/12/15 07:17:31  adutta
 * LOG: SCTP_PAYLOAD_M2UA Identifier set to 2
 * LOG:
 * LOG: Revision 7.2.10.1  2004/10/15 23:47:52  randresol
 * LOG: Add Definition for M2UA
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2002/02/27 22:57:04  vnitin
 * LOG: Adding code for Retrive buffer and SSN (BSNT)
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.5  2001/07/19 17:24:23  hdivoux
 * LOG: Replaced C++ comments by C comments.
 * LOG:
 * LOG: Revision 4.4  2001/07/11 19:24:11  mmiers
 * LOG: forward port the SCTP work.
 * LOG:
 * LOG: Revision 3.18.2.2  2001/07/06 22:13:53  vnitin
 * LOG: Adding SCTP MIB support and fixing other problems like shutdown logic
 * LOG:
 * LOG: Revision 3.18.2.1  2001/05/10 20:18:59  rsonak
 * LOG: Someone forgot to make the declarations for support hooks as 'externs'
 * LOG:
 * LOG: Revision 3.18  2001/04/03 15:29:34  omayor
 * LOG: Modified the Payload Id for M3UA and SUA (3 and 4).
 * LOG:
 * LOG: Revision 3.17  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.16  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.15  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.14  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.13  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.12  2001/01/16 21:39:25  mmiers
 * LOG: Reorganize so that support is completely standalone
 * LOG:
 * LOG: Revision 3.11  2000/12/18 19:59:16  mmiers
 * LOG: Clean up a few bits.
 * LOG:
 * LOG: Revision 3.10  2000/12/05 16:56:00  mmiers
 * LOG: Final route installment.
 * LOG:
 * LOG: Revision 3.9  2000/11/30 20:06:00  mmiers
 * LOG: Correctness tweaks.
 * LOG:
 * LOG: Revision 3.8  2000/11/29 18:24:42  mmiers
 * LOG: Write ok.  Think about SLS->stream.
 * LOG:
 * LOG: Revision 3.7  2000/11/28 23:44:29  mmiers
 * LOG: Today's SCTPTRAN installment.  About finished, just need to create
 * LOG: remote transports when clients connect/destroy when they leave.
 * LOG:
 * LOG: Revision 3.6  2000/11/17 23:09:51  mmiers
 * LOG: clean up on SCTP some.
 * LOG:
 * LOG: Revision 3.5  2000/11/16 23:01:55  mmiers
 * LOG: Add the SCTP transport.  Getting close on this...
 * LOG:
 * LOG: Revision 3.4  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.9  2000/10/30 16:18:20  mmiers
 * LOG: Post bakeoff.  Now to clean up.
 * LOG:
 * LOG: Revision 3.8  2000/10/22 20:27:42  mmiers
 * LOG: Add static cookie life extension.
 * LOG:
 * LOG: Revision 3.7  2000/10/15 18:50:37  mmiers
 * LOG: Test program done.  Now debugging is all that's left.
 * LOG:
 * LOG: Revision 3.6  2000/10/15 01:38:44  mmiers
 * LOG: This is about there.  IOCTLs in, think about streams an test program.
 * LOG:
 * LOG: Revision 3.5  2000/10/13 23:01:12  mmiers
 * LOG: 99 percent done.  Debug the glue, finish the ULP, and streams.
 * LOG:
 * LOG: Revision 3.4  2000/10/13 18:12:44  mmiers
 * LOG: Ok, got a good bit of the API.  Last is data translation.
 * LOG:
 * LOG: Revision 3.3  2000/10/05 00:11:02  mmiers
 * LOG: Merge in the rev13 changes.
 * LOG:
 * LOG: Revision 3.2  2000/10/03 23:47:31  mmiers
 * LOG: Integrate some v13 stuff.  Nothing behavioral yet.
 * LOG:
 * LOG: Revision 3.1  2000/10/03 21:17:04  mmiers
 * LOG: Today's installment.  Getting real close now.
 * LOG:
 * LOG: Revision 3.6  2000/10/02 23:01:29  mmiers
 * LOG: stream in/out.  Convert to lists.
 * LOG:
 * LOG: Revision 3.5  2000/10/02 22:15:50  mmiers
 * LOG: More work.
 * LOG:
 * LOG: Revision 3.4  2000/09/29 17:52:01  mmiers
 * LOG: OK.  Skeleton done, hook things together, rething its_sctp_trans.
 * LOG:
 * LOG: Revision 3.3  2000/09/28 21:49:47  mmiers
 * LOG:
 * LOG: Checkpoint for solaris build.
 * LOG:
 * LOG: Revision 3.2  2000/09/27 18:56:44  mmiers
 * LOG: Working on SCTP again.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:21  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.17  2000/08/11 22:06:39  mmiers
 * LOG:
 * LOG: The long awaited day is here!  The core implementation is in place.
 * LOG: Now to glue it together and optimize performance.
 * LOG:
 * LOG: Revision 2.16  2000/08/10 22:46:45  mmiers
 * LOG:
 * LOG:
 * LOG: SCTP update, dispatcher rework for generic behavior.
 * LOG:
 * LOG: Revision 2.15  2000/08/10 01:35:57  mmiers
 * LOG: SCTP update again.  A few K lines left.
 * LOG:
 * LOG: Revision 2.14  2000/08/10 00:04:56  mmiers
 * LOG: SCTP update.  Almost there.
 * LOG:
 * LOG: Revision 2.13  2000/08/09 00:08:19  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 2.12  2000/08/07 23:52:31  mmiers
 * LOG: SCTP update.
 * LOG:
 * LOG: Revision 2.11  2000/08/05 00:20:32  mmiers
 * LOG: IMAL: Add per link SLTM data.
 * LOG: SCTP: Update implementation.
 * LOG:
 * LOG: Revision 2.10  2000/08/03 22:47:31  mmiers
 * LOG: SCTP update.
 * LOG:
 * LOG: Revision 2.9  2000/08/02 17:20:43  mmiers
 * LOG: I know I did this somewhere.
 * LOG:
 * LOG: Revision 2.8  2000/07/25 22:47:36  mmiers
 * LOG: Get SCTP building again.  I think I know how I'm going to do this now.
 * LOG:
 * LOG: Revision 2.7  2000/07/21 23:34:38  mmiers
 * LOG:
 * LOG:
 * LOG: SCTP update.
 * LOG:
 * LOG: Revision 2.6  2000/06/02 17:18:10  mmiers
 * LOG:
 * LOG:
 * LOG: Socket modifications.
 * LOG:
 * LOG: Revision 2.5  2000/05/26 21:34:19  mmiers
 * LOG:
 * LOG:
 * LOG: A few bug fixes, more SCTP work.
 * LOG:
 * LOG: Revision 2.4  2000/05/25 23:47:04  mmiers
 * LOG:
 * LOG:
 * LOG: Subclass from EPtrans for SCTP.
 * LOG:
 * LOG: Revision 2.3  2000/05/23 21:26:34  mmiers
 * LOG:
 * LOG:
 * LOG: Snapshot of SCTP.
 * LOG:
 * LOG: Revision 2.2  2000/05/22 23:00:58  mmiers
 * LOG:
 * LOG:
 * LOG: Checkpoint.
 * LOG:
 * LOG: Revision 2.1  2000/05/22 18:27:36  mmiers
 * LOG:
 * LOG:
 * LOG: Add framework for SCTP transports.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_SCTP_H)
#define ITS_SCTP_H

#include <its.h>
#include <its_crypt.h>
#include <its_sockets.h>
#include <its_callback.h>
#include <its_list.h>
#include <its_trace.h>

#ident "$Id: its_sctp.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

/*
 * pegs types
 */
enum SCTP_PEGS
{
    SCTP_PEG_SACKS_RCVD,
    SCTP_PEG_SACKS_SENT,
    SCTP_PEG_TSNS_RCVD,
    SCTP_PEG_TSNS_SENT,
    SCTP_PEG_DGRAMS_RCVD,
    SCTP_PEG_DGRAMS_SENT,
    SCTP_PEG_NUM_RETRANS,
    SCTP_PEG_NUM_DUPS,
    SCTP_PEG_HBEATS_RCVD,
    SCTP_PEG_HBEATS_SENT,
    SCTP_PEG_HABEATS_RCVD,
    SCTP_PEG_HABEATS_SENT,
    SCTP_PEG_DATA_RCVD,
    SCTP_PEG_DATA_SENT,
    SCTP_PEG_XMIT_TIMER,
    SCTP_PEG_RECV_TIMER,
    SCTP_PEG_HB_TIMER,
    SCTP_PEG_FAST_RETRANS,
    SCTP_PEG_TSNS_SEEN,
    SCTP_PEG_RWND_FULL,
    SCTP_PEG_NONE_TO_SEND,
    SCTP_PEG_CWND_FULL,
    SCTP_PEG_T1_EXPIRED,
    SCTP_PEG_T2_EXPIRED,
    SCTP_PEG_CHECKSUM_ERROR,
    SCTP_PEG_MAX_PEGS,

    SCTP_PEG_COUNT = SCTP_PEG_MAX_PEGS
};

/*
 * payload types
 */
typedef enum
{
    SCTP_PAYLOAD_UNDEFINED,
    SCTP_PAYLOAD_IUA,
    SCTP_PAYLOAD_M2UA,
    SCTP_PAYLOAD_M3UA,
    SCTP_PAYLOAD_SUA,
    SCTP_PAYLOAD_M2PA,
    SCTP_PAYLOAD_V5UA,
    SCTP_PAYLOAD_GCP,
    SCTP_PAYLOAD_BICC,
    SCTP_PAYLOAD_TALI,
    SCTP_PAYLOAD_MAX
}
SCTP_PAYLOAD;

#if defined(__cplusplus)
extern "C"
{
#endif

#if !defined(SCTP_IMPLEMENTATION)
#define SCTPDLLAPI   ITSDLLAPI
#else
#if defined(WIN32)
#define SCTPDLLAPI   __declspec(dllexport)
#else
#define SCTPDLLAPI
#endif /* WIN32 */
#endif

/*
 * feature record(s)
 */
SCTPDLLAPI extern ITS_Class        itsSCTP_Class;/* protocol engine */

ITSDLLAPI extern ITS_ClassRec     itsSCTPTRAN_ClassRec;   /* transport wrapper */
ITSDLLAPI extern ITS_Class        itsSCTPTRAN_Class;      /* transport wrapper */

#define SCTPTRAN_CLASS_NAME "SCTP Transport Feature"

/*
 * SCTP API
 */

/*
 * iovec
 */
typedef struct
{
    ITS_POINTER     vector;
    ITS_INT         len;
}
SCTP_API_IOVEC;

/*
 * typical message structure
 */
typedef struct
{
    ITS_POINTER     name;
    ITS_INT         nameLen;
    SCTP_API_IOVEC  *ioVecs;
    ITS_INT         numIOVecs;
    ITS_POINTER     control;
    ITS_INT         controlLen;
    ITS_INT         flags;
}
SCTP_API_MSG_HDR;

/*
 * flags in the msghdr
 */
#define SCTP_IS_DATA    0
#define SCTP_IS_EVENT   1

/*
 * flags to SCTP_SendMsg();
 */
#define SCTP_API_SYNC       0x01
#define SCTP_API_ASYNC      0x02

/*
 * control message structure
 */
typedef struct
{
    ITS_UINT    len;
    ITS_INT     level;
    ITS_INT     type;
}
SCTP_API_CMSG_HDR;

/*
 * notifications (types)
 */
#define SCTP_CM_DATA_IO          1
#define SCTP_CM_ASSOC_CHG        2
#define SCTP_CM_INTF_CHG         3
#define SCTP_CM_SEND_FAIL        4
#define SCTP_CM_REMOTE_ERR       5
#define SCTP_CM_HB_RESP          6
#define SCTP_CM_SSN_NOT_RTRV     7  /* Not able to Retrieve Stream Seq Num */
#define SCTP_CM_SSN_CONFM        8  /* Stream Seq Num Confirm */
#define SCTP_CM_BUFF_RTRV        9  /* next Buffer retrieved */
#define SCTP_CM_BUFF_RTRV_COMP   10 /* Buffer Retrieval complete */


/*
 * send/receive
 */
typedef struct
{
    ITS_UINT        tsn;            /* data's TSN */
    ITS_USHORT      stream;         /* data's stream */
    ITS_USHORT      seqNum;         /* data's stream sequence */
    ITS_USHORT      deliveryNum;    /* data's fragment number.  Only used in partial delivery
                                     * to the user */
    ITS_USHORT      flags;          /* data's flags (on transmit) */
    SOCK_IPv4Addr   primary;        /* remote primary addr (not in spec) */
    ITS_UINT        context;        /* user-specified context number (on transmit) */
    ITS_UINT        payload;        /* payload ID */
    ITS_OCTET       tos;            /* type of service */
}
SCTP_API_SND_RCV;

/*
 * send/receive flags
 */
#define SCTP_SR_MORE_DATA       0x0001
#define SCTP_SR_END_REC         0x0002
#define SCTP_SR_UNORDERED       0x0004

#define SCTP_SR_ABORT           0x0008
#define SCTP_SR_SHUTDOWN        0x0010
#define SCTP_SR_MY_ADDR_ONLY    0x0020


#define SCTP_SR_DEFAULT_DATA_STREAM  0x0001
  

/*
 * assoc change data
 */
typedef struct
{
    SOCK_AddrStore  primaryAddr;
    ITS_INT         state;
    ITS_INT         error;
}
SCTP_API_ASSOC_CHG_DATA;

#define SCTP_AC_COMM_UP         1
#define SCTP_AC_COMM_LOST       2
#define SCTP_AC_COMM_RESTART    3
#define SCTP_AC_COMM_ABORTED    4
#define SCTP_AC_SHUTDOWN_DONE   5
#define SCTP_AC_CANT_START      6

/* M2PA BSNT and BUFFER defines */
#define SCTP_SSN_NOT_RETRIEVABLE    0x0010
#define SCTP_SSN_CONFIRM            0x0011
#define SCTP_RETRIVE_BUFFER         0x0012
#define SCTP_RETRIVE_BUFFER_COMP    0x0013


/*
 * interface change data
 */
typedef struct
{
    SOCK_AddrStore  primaryAddr;
    SOCK_AddrStore  affectedAddr;
    ITS_INT         state;
    ITS_INT         errorCode;
}
SCTP_API_INTF_CHG_DATA;

#define SCTP_IC_ADDR_REACHABLE      1
#define SCTP_IC_ADDR_UNREACHABLE    2

/*
 * remote error data
 */
typedef struct
{
    ITS_USHORT  causeCode;
    ITS_USHORT  causeLen;
    ITS_OCTET   causeData[1];
}
SCTP_API_REM_ERR_DATA;

/*
 * the control message
 */
typedef struct
{
    SCTP_API_CMSG_HDR   hdr;
    union
    {
        SCTP_API_SND_RCV        sndRcv;
        SCTP_API_ASSOC_CHG_DATA assocChg;
        SCTP_API_INTF_CHG_DATA  intfChg;
        SCTP_API_REM_ERR_DATA   remErr;
    }
    data;
}
SCTP_API_CMSG;

/*
 * SCTP MIB Parameters
 */

/* General Variables */
#define     SCTP_MIB_RTO_ALGORITHM      0x00
#define     SCTP_MIB_RTO_MIN            0x01
#define     SCTP_MIB_RTO_MAX            0x02
#define     SCTP_MIB_RTO_INITIAL        0x03
#define     SCTP_MIB_COOKIE_LIFE        0x04
#define     SCTP_MIB_MAX_INIT_RETR      0x05
/* gap for future use */
#define     SCTP_MIB_GEN_VARIABLE       0x0F    /*All Genral Variables */

/* SCTP Protocol state Statistics */
#define     SCTP_MIB_CURR_ESTAB         0x10 
#define     SCTP_MIB_ACTIVE_ESTAB       0x11 
#define     SCTP_MIB_PASSIVE_ESTAB      0x12 
#define     SCTP_MIB_ABORTED            0x13 
#define     SCTP_SHUTDOWNS              0x14
/* gap for future use */
#define     SCTP_MIB_GEN_STATES         0x1F    /*All state statistics */

/* SCTP Protocols other Statistics */

#define     SCTP_MIB_OOB                0x20    /* Out of Blue */
#define     SCTP_MIB_SENT_CHUNKS        0x21    
#define     SCTP_MIB_REC_CHUNKS         0x22
#define     SCTP_MIB_OO_SENT_CHUNKS     0x23    /*Out of order, ubit set */
#define     SCTP_MIB_OO_REC_CHUNKS      0x24
#define     SCTP_MIB_FRAG_DG            0x25
#define     SCTP_MIB_REASMB_DG          0x26
/* gap for future use */
#define     SCTP_MIB_GEN_STATISTICS     0x2F    /*All Gen other Statistics*/


/* SCTP Association releated genral variables */
#define     SCTP_MIB_ASSOC_ID           0x30
#define     SCTP_MIB_REM_NAME           0x31
#define     SCTP_MIB_LOCAL_PORT         0x32
#define     SCTP_MIB_REM_PORT           0x33
#define     SCTP_MIB_REM_PRIM_ADDR_TYP  0x34
#define     SCTP_MIB_REM_PRIM_ADDR      0x35
#define     SCTP_MIB_HBEAT_FLAG         0x36
#define     SCTP_MIB_HBEAT_TIMER        0x37
#define     SCTP_MIB_ASSOC_STATE        0x38
#define     SCTP_MIB_IN_STREAM          0x39
#define     SCTP_MIB_OUT_STREAM         0x3A
#define     SCTP_MIB_MAX_SEND_RETR      0x3B
#define     SCTP_MIB_ASSOC_START_TIME   0x3C
/* gap for future use */
#define     SCTP_ASSOC_GEN_VARIABLE     0x4F    /*All assoc Gen Variables*/

/* SCTP Assoc statistics */
#define     SCTP_MIB_T1_EXPIRED         0x50
#define     SCTP_MIB_T2_EXPIRED         0x51
#define     SCTP_MIB_RETR_CHUNKS        0x52
#define     SCTP_MIB_CKSUM_ERROR        0x53
/* Gap for future use */
#define     SCTP_MIB_ASSOC_STATISTICS   0x6F    /*All assoc Statistics */

/* Local IP Table */
#define     SCTP_MIB_LCL_ADDR_TYPE      0x70
#define     SCTP_MIB_LCL_IP_ADDR        0x71
#define     SCTP_MIB_LCL_IP_START_TIME  0x72

/* Gap for future use */
#define     SCTP_MIB_LOCAL_IP_TABLE     0x7F    /*all variables in table*/

/* Remote IP Table per association */
#define     SCTP_MIB_REM_ADDR_TYPE      0x80
#define     SCTP_MIB_REM_IP_ADDR        0x81
#define     SCTP_MIB_REM_ADDR_STATE     0x82
#define     SCTP_MIB_REM_ADDR_RTO       0x83
#define     SCTP_MIB_REM_MAX_PATH_RETR  0x84
#define     SCTP_MIB_REM_RETR_COUNT     0x85
#define     SCTP_MIB_REM_IP_START_TIME  0x86

/* Gap for future use */
#define     SCTP_MIB_REM_IP_TABLE       0x8F    /* all variables in a table*/

typedef struct
{
    ITS_USHORT   rto_algo;
    ITS_ULONG    rto_min;
    ITS_ULONG    rto_max;
    ITS_ULONG    rto_init;
    ITS_ULONG    cookieLife;
    ITS_USHORT   maxInitAttempts;
}
SCTP_API_GEN_VAR;

typedef struct
{
    ITS_UINT  currEstab;
    ITS_UINT  activeEstab;
    ITS_UINT  passiveEstab;
    ITS_UINT  aborted;
    ITS_UINT  numShutdowns;
}
SCTP_API_GEN_STATE;

typedef struct
{
    ITS_ULONG numOutOfBlue; /* Out of blue packets received */
    ITS_ULONG numSentChunks;/*data & control chunks sent, no retransmission */
    ITS_ULONG numRecChunks; /*data & control chunks received, no duplicates */
    ITS_ULONG numOutOfOrderSent;/*data chunks sent with u bit set to 1 */
    ITS_ULONG numOutOfOrderRec; /*data chunks received with u bit set to 1 */
    ITS_ULONG numFragUsrMsgs;   /*User messages fragmented due to MTU */
    ITS_ULONG numReassmbUsrMsgs;/*of user messages reassembled */
}
SCTP_API_GEN_COUNTER;

typedef struct
{
    ITS_TIME        assocId;
    ITS_OCTET       remoteName[12];
    ITS_USHORT      srcPort;
    ITS_USHORT      destPort;
    ITS_OCTET       remPrimAddrType;
    SOCK_IPv4Addr   remPrimAddr;
    ITS_USHORT      hbState;
    ITS_TIME        hbTimer;
    ITS_USHORT      state;
    ITS_ULONG       numInStreams;         
    ITS_ULONG       numOutStreams;     
    ITS_USHORT      maxRetrans;
    ITS_TIME        startTime;
}
SCTP_API_AS_VAR;

typedef struct
{
    ITS_ULONG    t1Expired;
    ITS_ULONG    t2Expired;
    ITS_ULONG    retransChunks;
    ITS_ULONG    chksumError;
}
SCTP_API_AS_COUNTER;

typedef struct
{
    ITS_USHORT      addrType;
    SOCK_IPv4Addr   addr;
    ITS_TIME        startTime;
}
SCTP_API_LCL_IP_TABLE;

typedef struct
{
    ITS_USHORT      addrType;
    SOCK_IPv4Addr   addr;
    ITS_USHORT      status;
    ITS_ULONG       rto;
    ITS_SHORT       maxPathRetrans;
    ITS_ULONG       retransCount;
    ITS_TIME        startTime;
}
SCTP_API_REM_IP_TABLE;


typedef struct
{
    SOCK_AddrStore    addr;
    ITS_USHORT        numNets;
    ITS_USHORT        numRemote;
    union
    {
        SCTP_API_GEN_VAR        genVar;
        SCTP_API_GEN_STATE      genState;
        SCTP_API_GEN_COUNTER    genCounter;
        SCTP_API_AS_VAR         assocVar;
        SCTP_API_AS_COUNTER     assocCounter;
        SCTP_API_LCL_IP_TABLE   lclIpTable[10];
        SCTP_API_REM_IP_TABLE   remIpTable[10];
    }
    msg;
}
SCTP_API_MIB_DATA;


/*
 * socket types
 */
#define SCTP_STREAM_SOCK    1
#define SCTP_DATAGRAM_SOCK  2

/*
 * The API
 */
SCTPDLLAPI ITS_USHORT  SCTP_Socket(int af, int t);
SCTPDLLAPI int         SCTP_Bind(ITS_USHORT sd, SOCK_AddrStore *who, int wlen);
SCTPDLLAPI int         SCTP_Listen(ITS_USHORT sd, int backlog);
SCTPDLLAPI ITS_USHORT  SCTP_Accept(ITS_USHORT sd, SOCK_AddrStore *who, int *wlen);
SCTPDLLAPI int         SCTP_Connect(ITS_USHORT sd, SOCK_AddrStore *who, int wlen);
SCTPDLLAPI int         SCTP_SendMsg(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags);
SCTPDLLAPI int         SCTP_RecvMsg(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags);
SCTPDLLAPI int         SCTP_Close(ITS_USHORT sd);
SCTPDLLAPI int         SCTP_Pending(ITS_USHORT sd);
SCTPDLLAPI int         SCTP_Ioctl(ITS_USHORT sd, int req, ...);
SCTPDLLAPI int         SCTP_GetMIBInfo(ITS_USHORT sd, int which, SCTP_API_MIB_DATA *data);
SCTPDLLAPI int         SCTP_SetMIBInfo(ITS_USHORT sd, int which, SCTP_API_MIB_DATA *data); 
                                       

/*
 * support hooks
 */
extern ITSDLLAPI ITS_USHORT  (*SCTP_SocketPtr)(int af, int t);
extern ITSDLLAPI int         (*SCTP_BindPtr)(ITS_USHORT sd, SOCK_AddrStore *who, int wlen);
extern ITSDLLAPI int         (*SCTP_ListenPtr)(ITS_USHORT sd, int backlog);
extern ITSDLLAPI ITS_USHORT  (*SCTP_AcceptPtr)(ITS_USHORT sd, SOCK_AddrStore *who, int *wlen);
extern ITSDLLAPI int         (*SCTP_ConnectPtr)(ITS_USHORT sd, SOCK_AddrStore *who, int wlen);
extern ITSDLLAPI int         (*SCTP_SendMsgPtr)(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags);
extern ITSDLLAPI int         (*SCTP_RecvMsgPtr)(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags);
extern ITSDLLAPI int         (*SCTP_ClosePtr)(ITS_USHORT sd);
extern ITSDLLAPI int         (*SCTP_PendingPtr)(ITS_USHORT sd);
extern ITSDLLAPI int         (*SCTP_IoctlPtr)(ITS_USHORT sd, int req, ...);

/*
 * after associated
 */
#define IOCTL_SET_COOKIE_LIFE       0x0001 /* "value" sets */
#define IOCTL_GET_COOKIE_LIFE       0x0002 /* "value" contains */
#define IOCTL_GET_LOCAL_RWND        0x0003 /* "value" contains */
#define IOCTL_GET_PEER_RWND         0x0004 /* "value" contains */
#define IOCTL_SET_NET_ERR_THRESH    0x0005 /* "value" sets specific net */
#define IOCTL_SET_ASSOC_ERR_THRESH  0x0006 /* "value" sets */
#define IOCTL_REQUEST_HEARTBEAT     0x0007 /* generate heartbeat */
#define IOCTL_GET_NUM_NETS          0x0008 /* "value" contains */
#define IOCTL_CLEAR_PEGS            0x0009 /* clear the pegs */
#define IOCTL_GET_PEGS              0x000A /* "pegs" contain */
#define IOCTL_GET_OUTBOUND_FLUSHED  0x000B /* "value" sets */
#define IOCTL_SET_HEARTBEAT         0x000C /* "value" clears or sets */
#define IOCTL_GET_HEARTBEAT_DELAY   0x000D /* "value" sets */
#define IOCTL_SET_HEARTBEAT_DELAY   0x000E /* "value" contains */
#define IOCTL_GET_RTO_REPORT        0x000F /* "value" gets specific net */
#define IOCTL_GET_CWND_REPORT       0x0010 /* "value" gets specific net */
#define IOCTL_GET_SRTT_REPORT       0x0011 /* "value" gets specific net */
#define IOCTL_GET_STATE_REPORT      0x0012 /* "value" gets specific net */
#define IOCTL_GET_NUM_OUT_STREAMS   0x0013 /* "value" contains */
#define IOCTL_GET_NUM_IN_STREAMS    0x0014 /* "value" contains */
#define IOCTL_SET_PRIMARY           0x0015 /* "value" sets */
#define IOCTL_SET_NUM_RETRANS       0x0016 /* "value" sets */
#define IOCTL_SET_RTO_PARAMS        0x0017 /* "value,2,3" sets */
#define IOCTL_SET_LOCAL_RWND        0x0018 /* "value" sets */
#define IOCTL_FIND_LAST_SSN         0x0019 /* Notification sent */
#define IOCTL_RETRIEVE_BUFFER       0x0020 /* Notification sent */


/*
 * before associated
 */
#define IOCTL_SET_INIT_TIMEOUT      0x8003 /* "value, value2" sets */
#define IOCTL_SET_SEND_TIMEOUT      0x8004 /* "value, value2" sets */
#define IOCTL_SET_RECV_TIMEOUT      0x8005 /* "value, value2" sets */
#define IOCTL_SET_HB_TIMEOUT        0x8006 /* "value, value2" sets */
#define IOCTL_SET_SHUT_TIMEOUT      0x8007 /* "value, value2" sets */
#define IOCTL_SET_PMTU_TIMEOUT      0x8008 /* "value, value2" sets */
#define IOCTL_SET_INIT_DATA         0x8009 /* "value,2,3" sets */
#define IOCTL_GET_INIT_DATA         0x800A /* "value,2,3" sets */
#define IOCTL_SET_SEND_ATTEMPTS     0x800B /* "value" sets */
#define IOCTL_SET_INIT_COOK_LIFE    0x800C /* "value" sets */
#define IOCTL_SET_INIT_HB_ON        0x800D /* "value" sets */

/*
 * ioctl arg struct
 */
typedef struct
{
    SOCK_AddrStore    addr;
    int               value;   /* basic, RTO.initial, numOStreams */
    int               value2;  /* usecs, RTO.min, maxIStreams */
    int               value3;  /* RTO.max, maxAttempts */
    int               pegs[SCTP_PEG_COUNT];
}
SCTP_API_IOCTL_ARG;


/*
 * transport names
 */
#define SCTP_TRANSPORT_NAME_FORMAT  "SCTP Instance %d"


#define SCTP_FILE_STRING                ITS_FILE_STRING
#define SCTP_STDOUT_STRING              ITS_STDOUT_STRING
#define SCTP_SYSLOG_STRING              ITS_SYSLOG_STRING

/*
 * tracing strings
 */
#define SCTP_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING
#define SCTP_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define SCTP_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define SCTP_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING

#define SCTP_CRITICAL_STRING        ITS_CRITICAL_STRING
#define SCTP_ERROR_STRING           ITS_ERROR_STRING
#define SCTP_WARNING_STRING         ITS_WARNING_STRING
#define SCTP_DEBUG_STRING           ITS_DEBUG_STRING


/*
 * the global control flag defined for SCTP
 */
extern TRACE_Data* SCTP_TraceData; 

/*
 * trace possibilities:
 */
#define SCTP_TRACE_CRITICAL  0
#define SCTP_TRACE_ERROR     1
#define SCTP_TRACE_WARNING   2
#define SCTP_TRACE_DEBUG     3




/* Macros for SCTP traces */

#define SCTP_CRITICAL(args) \
    TRACE(SCTP_TraceData, SCTP_TRACE_CRITICAL, args)

#define SCTP_ERROR(args) \
    TRACE(SCTP_TraceData, SCTP_TRACE_ERROR, args)

#define SCTP_WARNING(args) \
    TRACE(SCTP_TraceData, SCTP_TRACE_WARNING, args)

#define SCTP_DEBUG(args) \
    TRACE(SCTP_TraceData, SCTP_TRACE_DEBUG, args)


#define SCTP_TRACE_CRITICAL_FILE    ".sctp-traceCritical"
#define SCTP_TRACE_ERROR_FILE       ".sctp-traceError"
#define SCTP_TRACE_WARNING_FILE     ".sctp-traceWarning"
#define SCTP_TRACE_DEBUG_FILE       ".sctp-traceDebug"

#if defined(__cplusplus)
}
#endif

#endif /* ITS_SCTP_TRANS_H */
