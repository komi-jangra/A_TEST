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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:52  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:58  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/08/09 14:57:47  vnitin
 * LOG:
 * LOG: ops!! fixing binary character in file
 * LOG:
 * LOG: Revision 4.2  2001/08/01 21:25:14  vnitin
 * LOG: Enhanced SCTP as per Implementors Guide 01. 
 * LOG: add new OpErr
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.9  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.8  2001/02/05 22:05:02  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.7  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.6  2000/11/16 20:38:30  mmiers
 * LOG: SCTP update from Randall's post-bakeoff code.
 * LOG:
 * LOG: Revision 3.5  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.8  2000/11/02 00:20:41  mmiers
 * LOG: Some code cleanup from after the bakeoff.  Get it structured
 * LOG: so that I can stand to read it.
 * LOG:
 * LOG: Revision 3.7  2000/10/30 16:18:21  mmiers
 * LOG: Post bakeoff.  Now to clean up.
 * LOG:
 * LOG: Revision 3.6  2000/10/19 23:19:25  mmiers
 * LOG: More testing bug fixes.
 * LOG:
 * LOG: Revision 3.5  2000/10/16 19:32:30  mmiers
 * LOG: Debugging round 1.
 * LOG:
 * LOG: Revision 3.4  2000/10/05 00:11:02  mmiers
 * LOG: Merge in the rev13 changes.
 * LOG:
 * LOG: Revision 3.3  2000/10/03 22:35:29  mmiers
 * LOG: All code enabled.  Final walkthrough and support integration
 * LOG: next, then debug.
 * LOG:
 * LOG: Revision 3.2  2000/10/03 21:17:05  mmiers
 * LOG: Today's installment.  Getting real close now.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:28  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.15  2000/08/11 22:06:39  mmiers
 * LOG:
 * LOG: The long awaited day is here!  The core implementation is in place.
 * LOG: Now to glue it together and optimize performance.
 * LOG:
 * LOG: Revision 1.14  2000/08/10 22:46:46  mmiers
 * LOG:
 * LOG:
 * LOG: SCTP update, dispatcher rework for generic behavior.
 * LOG:
 * LOG: Revision 1.13  2000/08/10 00:04:56  mmiers
 * LOG: SCTP update.  Almost there.
 * LOG:
 * LOG: Revision 1.12  2000/08/09 00:08:20  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 1.11  2000/08/07 23:52:31  mmiers
 * LOG: SCTP update.
 * LOG:
 * LOG: Revision 1.10  2000/08/03 22:47:31  mmiers
 * LOG: SCTP update.
 * LOG:
 * LOG: Revision 1.9  2000/06/12 22:07:45  mmiers
 * LOG:
 * LOG:
 * LOG: Checkpoint.
 * LOG:
 * LOG: Revision 1.8  2000/06/02 22:39:27  mmiers
 * LOG:
 * LOG:
 * LOG: SCTP update.
 * LOG:
 * LOG: Revision 1.7  2000/05/25 23:25:32  mmiers
 * LOG:
 * LOG:
 * LOG: Today's SCTP snapshot.
 * LOG:
 * LOG: Revision 1.6  2000/05/24 18:55:48  mmiers
 * LOG:
 * LOG:
 * LOG: Warning removal ("incomplete last line")
 * LOG:
 * LOG: Revision 1.5  2000/05/23 21:26:34  mmiers
 * LOG:
 * LOG:
 * LOG: Snapshot of SCTP.
 * LOG:
 * LOG: Revision 1.4  2000/05/22 23:00:58  mmiers
 * LOG:
 * LOG:
 * LOG: Checkpoint.
 * LOG:
 * LOG: Revision 1.3  2000/05/22 18:40:46  mmiers
 * LOG:
 * LOG:
 * LOG: Make sure the checked in version builds.
 * LOG:
 * LOG: Revision 1.2  2000/05/22 18:27:36  mmiers
 * LOG:
 * LOG:
 * LOG: Add framework for SCTP transports.
 * LOG:
 * LOG: Revision 1.1  2000/03/01 15:45:09  mmiers
 * LOG:
 * LOG:
 * LOG: Additional test, SCTP target.
 * LOG:
 *
 ****************************************************************************/

#if !defined(SCTP_MSGS_H)
#define SCTP_MSGS_H

#ident "$Id: sctp_msgs.h,v 1.1.1.1 2007-10-08 11:11:33 bsccs2 Exp $"

/*
 * type of service
 */
#define SCTP_TOS_CE_BIT     (1 << 0)
#define SCTP_TOS_ECT_BIT    (1 << 1)

/*
 * parameter type(s)
 */
#define SCTP_OPERR_UNKNOWN_CAUSE    0x0000U
#define SCTP_OPERR_INVALID_STREAM   0x0001U
#define SCTP_OPERR_MISSING_MAND     0x0002U
#define SCTP_OPERR_STALE_COOKIE     0x0003U
#define SCTP_OPERR_OUT_OF_RESOURCE  0x0004U /* empty */
#define SCTP_OPERR_BAD_ADDRESS      0x0005U
#define SCTP_OPERR_UNKNOWN_CHUNK    0x0006U
#define SCTP_OPERR_INVALID_PARAM    0x0007U /* empty */
#define SCTP_OPERR_UNKNOWN_PARAM    0x0008U
#define SCTP_OPERR_NO_USER_DATA     0x0009U
#define SCTP_OPERR_COOKIE_SHUTDOWN  0x000AU /* empty */
#define SCTP_OPERR_AS_RESET_NEWADDR 0x000BU

/*
 * error causes reuse some of the values, making the params
 * message specific.  Idiots.
 */
#define SCTP_PARAM_HEARTBEAT_INFO   0x0001U
#define SCTP_PARAM_IPv4_ADDR        0x0005U
#define SCTP_PARAM_IPv6_ADDR        0x0006U
#define SCTP_PARAM_ENCRYPT_COOKIE   0x0007U
#define SCTP_PARAM_UNKNOWN_PARAMS   0x0008U
#define SCTP_PARAM_COOKIE_PRESERVE  0x0009U
#define SCTP_PARAM_ECN_CAPABLE      0x8000U
#define SCTP_PARAM_HOST_NAME_ADDR   0x000BU
#define SCTP_PARAM_SUPP_ADDR_TYPES  0x000CU

#define SCTP_PARAM_VENDOR_SPECIFIC  0xFFFEU
#define SCTP_PARAM_EXTENSIONS       0xFFFFU

#define SCTP_PARAM_REPORT_ON_ERR    0x4000U
#define SCTP_PARAM_SKIP_ON_ERR      0x8000U

/*
 * param header
 */
typedef struct
{
    ITS_USHORT  paramType;
    ITS_USHORT  paramLen;
}
ITS_SCTP_PARAM_HDR;

/*
 * parameter type(s)
 */
typedef struct
{
    ITS_SCTP_PARAM_HDR  paramHdr;
    union
    {
        ITS_USHORT          streamID;
        struct SCTPParam_HBInfo
        {
            ITS_UINT        sentOn;
            ITS_BOOLEAN     userReq;
            ITS_TIME        rttSecs;
            ITS_TIME        rttUSecs;
        }
        heartbeatInfo;
        SOCK_IPv4Addr       ipv4Addr;
        SOCK_IPv6Addr       ipv6Addr;
        ITS_TIME            cookieLifeSpan;
        struct SCTPParam_VendorSpec
        {
            ITS_UINT        vendorId;
            ITS_OCTET       vendorData[ITS_PATH_MAX];
        }
        vendorSpecific;
        struct SCTPParam_CookieData
        {
            ITS_UINT        curTag;
            ITS_UINT        hisTag;
            ITS_TIME        lifeSpan;
            ITS_TIME        creationTimeSecs;
            ITS_TIME        creationTimeUSecs;
            ITS_USHORT      addrType;
            union
            {
                SOCK_IPv4Addr   ipv4Addr;
                SOCK_IPv6Addr   ipv6Addr;
            }
            addrInfo;
        }
        cookieData;
        ITS_OCTET           hostName[ITS_PATH_MAX];
        ITS_USHORT          addrTypes[4];
        struct SCTPParam_MissingParams
        {
            ITS_UINT        numMissing;
            ITS_USHORT      tags[32];
        }
        missingParams;
        ITS_UINT            staleness;
        ITS_UINT            tsn;
        ITS_OCTET           badAddr[ITS_PATH_MAX];
        ITS_OCTET           unknownParams[ITS_PATH_MAX];
        ITS_OCTET           generic[ITS_PATH_MAX];
    }
    paramData;
}
ITS_SCTP_PARAM;

/*
 * address types
 */
#define SCTP_PARAM_VAL_ADDR_TYPE_IPV4   0x0005
#define SCTP_PARAM_VAL_ADDR_TYPE_IPV6   0x0006

/*
 * chunk types
 */
#define SCTP_CHUNK_TYPE_DATA            0x00U
#define SCTP_CHUNK_TYPE_INIT            0x01U
#define SCTP_CHUNK_TYPE_INIT_ACK        0x02U
#define SCTP_CHUNK_TYPE_SACK            0x03U
#define SCTP_CHUNK_TYPE_HEARTBEAT       0x04U
#define SCTP_CHUNK_TYPE_HEARTBEAT_ACK   0x05U
#define SCTP_CHUNK_TYPE_ABORT           0x06U
#define SCTP_CHUNK_TYPE_SHUTDOWN        0x07U
#define SCTP_CHUNK_TYPE_SHUTDOWN_ACK    0x08U
#define SCTP_CHUNK_TYPE_ERROR           0x09U
#define SCTP_CHUNK_TYPE_COOKIE          0x0AU
#define SCTP_CHUNK_TYPE_COOKIE_ACK      0x0BU
#define SCTP_CHUNK_TYPE_ECNE            0x0CU
#define SCTP_CHUNK_TYPE_CWR             0x0DU
#define SCTP_CHUNK_TYPE_SHUTDOWN_COMP   0x0EU
/* 0x0C-0xFD are reserved */
#define SCTP_CHUNK_TYPE_VENDOR_SPECIFIC 0xFEU
#define SCTP_CHUNK_TYPE_EXTENSIONS      0xFFU

#define SCTP_CHUNK_TYPE_SKIP_ON_ERR     0x80U
#define SCTP_CHUNK_TYPE_REPORT_ON_ERR   0x40U

/*
 * INIT, INIT_ACK
 */
typedef struct
{
    ITS_UINT        initiateTag;
    ITS_INT         windowCredit;
    ITS_USHORT      numOutboundStreams;
    ITS_USHORT      numInboundStreams;
    ITS_UINT        initialTSN;
    ITS_SCTP_PARAM  params[1];
}
ITS_SCTP_CHUNK_INIT;

/*
 * SACK
 */
typedef struct
{
    ITS_UINT    cumTSNAck;
    ITS_INT     windowCredit;
    ITS_USHORT  numFrags;
    ITS_USHORT  numDups;
    ITS_USHORT  fragsAndDups[2];
}
ITS_SCTP_CHUNK_SACK;

/*
 * HEARTBEAT, HEARTBEAT_ACK have no fixed params.
 */
typedef struct
{
    ITS_SCTP_PARAM  params[1];
}
ITS_SCTP_CHUNK_HEARTBEAT;

/*
 * ABORT has one or more error cause params
 */
typedef struct
{
    ITS_SCTP_PARAM  params[1];
}
ITS_SCTP_CHUNK_ABORT;

/*
 * ABORT and SHUTDOWN_COMPLETE share this
 */
#define SCTP_TCB_NOT_PRESENT    (1 << 0)

/*
 * SHUTDOWN
 */
typedef struct
{
    ITS_UINT    cumTSNAck;
}
ITS_SCTP_CHUNK_SHUTDOWN;

/*
 * SHUTDOWN_ACK has no params at all.
 */

/*
 * ERROR has one or more error cause params
 */
typedef struct
{
    ITS_SCTP_PARAM  params[1];
}
ITS_SCTP_CHUNK_ERROR;

/*
 * COOKIE has free format data.
 */
typedef struct
{
    ITS_SCTP_PARAM  params[1];
}
ITS_SCTP_CHUNK_COOKIE;

/*
 * COOKIE_ACK has no data
 */

/*
 * DATA
 */
typedef struct
{
    ITS_UINT    tsn;
    ITS_USHORT  streamID;
    ITS_USHORT  streamSeq;
    ITS_UINT    protocolID;
    ITS_OCTET   userData[4];
}
ITS_SCTP_CHUNK_DATA;

#define SCTP_MSG_END_SEG            (1 << 0)
#define SCTP_MSG_BEGIN_SEG          (1 << 1)
#define SCTP_MSG_DELIVER_UNORDERED  (1 << 2)
#define SCTP_MSG_NOT_FRAG           (SCTP_MSG_BEGIN_SEG|SCTP_MSG_END_SEG)

/*
 * ECNE
 */
typedef struct
{
    ITS_UINT    lowestTSN;
}
ITS_SCTP_CHUNK_ECNE;

/*
 * CWR
 */
typedef struct
{
    ITS_UINT    lowestTSN;
}
ITS_SCTP_CHUNK_CWR;

typedef struct SCTP_ChunkHdr
{
    ITS_OCTET           chunkID;
    ITS_OCTET           chunkFlags;
    ITS_USHORT          chunkLen;
}
ITS_SCTP_CHUNK_HDR;

/*
 * one chunk
 */
typedef struct
{
    ITS_SCTP_CHUNK_HDR   chunkHdr;
    union SCTP_ChunkData
    {
        ITS_SCTP_CHUNK_INIT         init;           /* open */
        ITS_SCTP_CHUNK_INIT         initAck;        /* open ack */
        ITS_SCTP_CHUNK_SACK         sack;           /* standalone ack */
        ITS_SCTP_CHUNK_HEARTBEAT    heartbeat;      /* heartbeat */
        ITS_SCTP_CHUNK_HEARTBEAT    heartbeatAck;   /* heartbeat ack */
        ITS_SCTP_CHUNK_ABORT        abort;          /* for abort */
        ITS_SCTP_CHUNK_SHUTDOWN     shutdown;       /* shutdown */
                                                    /* nothing for shutdown ack */
        ITS_SCTP_CHUNK_ERROR        error;          /* nothing for error */
        ITS_SCTP_CHUNK_COOKIE       cookie;         /* cookie */
                                                    /* nothing for cookie ack */
        ITS_SCTP_CHUNK_DATA         data;           /* payload */
        ITS_SCTP_CHUNK_ECNE         ecne;
        ITS_SCTP_CHUNK_CWR          cwr;
    }
    chunkData;
}
ITS_SCTP_CHUNK;

/*
 * message header
 */
typedef struct
{
    ITS_USHORT      sourcePort;
    ITS_USHORT      destPort;
    ITS_UINT        verificationTag;
    ITS_UINT        checkSum;
}
ITS_SCTP_HDR;

/*
 * message
 */
typedef struct
{
    ITS_SCTP_HDR    hdr;
    ITS_SCTP_CHUNK  chunks[1];
}
ITS_SCTP_MSG;

#endif /* SCTP_MSGS_H */
