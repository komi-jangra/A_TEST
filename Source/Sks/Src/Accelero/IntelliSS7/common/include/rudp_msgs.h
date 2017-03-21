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
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:05:02  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.2  2000/10/09 17:37:21  mmiers
 * LOG: RUDP updates, cross-platform build.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:27  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/02/10 00:44:35  mmiers
 * LOG:
 * LOG:
 * LOG: RUDP connections at IDLE now work.  More tomorrow.
 * LOG:
 * LOG: Revision 2.2  2000/01/18 00:20:25  mmiers
 * LOG: First complete (more or less) cut of RUDP.
 * LOG:
 * LOG: Revision 2.1  2000/01/14 23:25:45  mmiers
 * LOG:
 * LOG:
 * LOG: Work with RUDP more.
 * LOG:
 *
 ****************************************************************************/

#if !defined(RUDP_MSGS_H)
#define RUDP_MSGS_H

#include <its.h>

#ident "$Id: rudp_msgs.h,v 1.1.1.1 2007-10-08 11:11:33 bsccs2 Exp $"

/*
 * All RUDP messages
 */
typedef struct
{
    ITS_OCTET   flags;
    ITS_OCTET   hdrLength;
    ITS_OCTET   seqNumber;
    ITS_OCTET   ackNumber;
}
RUDP_HDR;

typedef struct
{
    ITS_USHORT  checkSum;
}
RUDP_CKSUM;

/*
 * flags
 */
#define RUDP_SYN            0x80U   /* variable */
#define RUDP_ACK            0x40U   /* variable */
#define RUDP_EAK            0x20U   /* variable */
#define RUDP_RST            0x10U   /* variable */
#define RUDP_NUL            0x08U   /* variable */
#define RUDP_CHK            0x04U   /* fixed, after SYN ACK */
#define RUDP_TCS            0x02U   /* variable */
#define RUDP_SPARE          0x00U

/*
 * RUDP message structures.  Note that we aren't including
 * chksum areas.  That's because the position of these can
 * vary, so the tx/rx functions will compute/verify them
 * (as needed - the data checksum may not be included).
 */

/*
 * SYN segment.  Don't worry about the USHORTS.  We call
 * ntohs/htons after receiving/before transmitting.
 */
/*
 * ACK bit in header *may* be set, if this is response SYN
 * to opener's request SYN.  This would be part of the
 * handshake when establishing the connection.
 */
typedef struct
{
    ITS_OCTET   version;            /* RUDP protocol version number   */
    ITS_OCTET   maxNumSegsPending;  /* window size                    */
    ITS_OCTET   options;            /* checksumming and resuse        */
    ITS_OCTET   spare;
    ITS_USHORT  maxSegmentSize;     /* maximum message size           */
    ITS_USHORT  retransTimeout;     /* time to wait before retransmit */
    ITS_USHORT  cumAckTimeout;      /* time to wait before empty ACK  */
    ITS_USHORT  nullSegTimeout;     /* time to wait before keepalive  */
    ITS_USHORT  transStateTimeout;  /* time to wait for ULP transfer  */
    ITS_OCTET   maxRetrans;         /* maximum retransmit attempts    */
    ITS_OCTET   maxCumAck;          /* maximum unacked segments       */
    ITS_OCTET   maxOOS;             /* maximum OOS segs before EACK   */
    ITS_OCTET   maxAutoReset;       /* maximum SYN attempts           */
    ITS_USHORT  connIdentifier[2];  /* 18 */
}
RUDP_SYN_DATA;

/*
 * SYN rev
 */
#define RUDP_SYN_VER_LOW_REV                    0x00U
#define RUDP_SYN_VER_REV_E                      0x10U

/*
 * segs pending
 */
#define RUDP_SYN_MAX_SEGS_PEND_DEFAULT          0x02U

/*
 * SYN options
 */
#define RUDP_SYN_OPT_CHK                        0x02U
#define RUDP_SYN_OPT_REUSE                      0x04U

/*
 * max segment size
 */
#define RUDP_SYN_MAX_SEG_SIZE_DEFAULT           1000U

/*
 * retransmission minimum timeout
 */
#define RUDP_SYN_MIN_RETRANS_TIMEOUT            100U
#define RUDP_SYN_DEFAULT_RETRANS_TIMEOUT        1500U

/*
 * cumulative ACK minimum timeout
 */
#define RUDP_SYN_MIN_CUM_ACK_TIMEOUT            100U
#define RUDP_SYN_DEFAULT_CUM_ACK_TIMEOUT        1500U

/*
 * null segment timeout (keepalive)
 */
#define RUDP_SYN_NULL_SEG_TIMEOUT_IGNORE        0U
#define RUDP_SYN_NULL_SEG_TIMEOUT_DEFAULT       3000U

/*
 * transfer state timeout
 */
#define RUDP_SYN_TRANS_STATE_TIMEOUT_NONE       0U
#define RUDP_SYN_TRANS_STATE_TIMEOUT_DEFAULT    30000U

/*
 * retransmission attempts
 */
#define RUDP_SYN_RETRANS_FOREVER                0U
#define RUDP_SYN_RETRANS_DEFAULT                5U

/*
 * cumulative Ack depth
 */
#define RUDP_SYN_CUM_ACK_DEPTH_NONE             0U
#define RUDP_SYN_CUM_ACK_DEPTH_DEFAULT          2U

/*
 * out of sequence ack depth
 */
#define RUDP_SYN_OOS_ACK_DEPTH_NONE             0U
#define RUDP_SYN_OOS_ACK_DEPTH_DEFAULT          2U

/*
 * auto resets before connection reset.
 */
#define RUDP_SYN_AUTO_RESET_DEPTH_NONE          0U
#define RUDP_SYN_AUTO_RESET_DEPTH_DEFAULT       5U

/*
 * connection identifier. Identifier is an ITS_UINT.
 */
#define RUDP_SYN_SET_CONN_ID(x, y) \
    ((x).connIdentifier[0] = (ITS_USHORT)(((y) >> 16) & 0xFFFFU), \
     (x).connIdentifier[1] = (ITS_USHORT)((y) & 0xFFU))
#define RUDP_SYN_GET_CONN_ID(x) \
    (((ITS_UINT)(x).connIdentifier[0]) << 16 | \
     ((ITS_UINT)(x).connIdentifier[1]))

/*
 * ACK segment
 */
/*
 * nothing new here.  Same as standard header, but ACK can
 * (and should) include data payload.  Contains both the next
 * send sequence number and the ack sequence number.  Probably
 * the best thing to do here is that if the user transmits
 * data before the cumulative ACK timeout, then we should
 * include this in an ACK segment containing payload.  Unless
 * of course there is an OOS packet received - in which case
 * we should delay until either the missing packet arrives,
 * the OOS timeout occurs (in which case we send EAK), or
 * the CUM_ACK timeout occurs (in which case we send NUL/ACK).
 */

/*
 * EAK segment
 */
/*
 * payload is list of sequence numbers of the out of sequence
 * messages received.  This would be the sequence number of all
 * messages received, past the OOS packet, but less than or equal
 * to the OOS receive depth.
 */
typedef struct
{
    ITS_OCTET   outOfSequenceSegs[1];
}
RUDP_EAK_DATA;

/*
 * RST segment.  
 */
/*
 * nothing new here.  Same as standard header, and cannot
 * include data.  RST is used to close or reset a connection
 * when certain conditions appear.  When a sender receives
 * an RST, it must stop sending packets, but must continue to
 * attempt delivery of packets already accepted from the API.
 * (Now that's confusing - in which direction do they mean?
 *  It sounds like the receiver should attempt to deliver
 *  queued messages, even if OOS.  TEST-FIXME).
 */

/*
 * NUL segment.
 */
/* This may be used as a heartbeat/sequence number increment when
 * no data is flowing.  When a NUL segment is received, an RUDP
 * implementation must ACK if a valid connection exists and the
 * segment sequence number is the next one in sequence.  It may
 * be combined with an ACK, but should never include user data.
 */

/*
 * TCS segment.
 */
/*
 * Transfer the Connection State (TCS).  Likely this is used
 * for failover in redundant systems.  Need to check the text
 * on this one a bit more.
 */
typedef struct
{
    ITS_OCTET   seqAdjFactor;
    ITS_OCTET   spare;
    ITS_USHORT  connIdentifier[2];
}
RUDP_TCS_DATA;

/*
 * connection identifier. Identifier is an ITS_UINT.
 */
#define RUDP_TCS_SET_CONN_ID(x, y) \
    ((x).connIdentifier[0] = (ITS_USHORT)(((y) >> 16) & 0xFFFFU), \
     (x).connIdentifier[1] = (ITS_USHORT)((y) & 0xFFU))
#define RUDP_TCS_GET_CONN_ID(x) \
    (((ITS_UINT)(x).connIdentifier[0]) << 16 | \
     ((ITS_UINT)(x).connIdentifier[1]))

/*
 * likely, I've gotten part of the above wrong, but that's what
 * testing is for.
 */

typedef union
{
    RUDP_SYN_DATA   syn;
    RUDP_EAK_DATA   eak;
    RUDP_TCS_DATA   tcs;

    /* the header can at most be 255 bytes in size */
    ITS_OCTET       pad[256];
}
RUDP_HDR_DATA;

/*
 * This is arbitrary.  Note that the checksums are still not
 * included.  That is done when this stuff hits the wire
 * (to ensure correct checksum calculation).  Note that this
 * whole thing has to fit inside an ITS_EVENT.
 */
#define RUDP_MAX_USER_DATA \
  (4088 - \
    (sizeof(RUDP_HDR) + sizeof(RUDP_HDR_DATA) + \
     sizeof(ITS_USHORT) * 2))

/*
 * message format.
 */
typedef struct
{
    RUDP_HDR        hdr;
    ITS_USHORT      hdrLen;
    RUDP_HDR_DATA   hdrData;
    ITS_OCTET       userData[RUDP_MAX_USER_DATA];
    ITS_USHORT      dataLen;
}
ITS_RUDP_MSG;

#endif /* RUDP_MSGS_H */
