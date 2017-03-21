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
 * LOG: Revision 3.2  2001/01/16 21:39:25  mmiers
 * LOG: Reorganize so that support is completely standalone
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:28  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/05/15 21:21:04  mmiers
 * LOG:
 * LOG:
 * LOG: Snapshot for TALI.  Almost everything but ISUP is there now.
 * LOG:
 * LOG: Revision 2.1  2000/05/13 00:36:32  mmiers
 * LOG:
 * LOG:
 * LOG: Ok, we can read and write TALI messages, now to build the state
 * LOG: machine...
 * LOG:
 * LOG: Revision 1.1  2000/03/01 15:45:09  mmiers
 * LOG:
 * LOG:
 * LOG: Additional test, SCTP target.
 * LOG:
 *
 ****************************************************************************/

#if !defined(TALI_MSGS_H)
#define TALI_MSGS_H

#ident "$Id: tali_msgs.h,v 1.1.1.1 2007-10-08 11:11:33 bsccs2 Exp $"

/*
 * Max PDU size for TALI
 */
#define TALI_MAX_MSG_SIZE                   263

/*
 * operations
 */
#define TALI_SYNC                           0x5441474C  /* TAGL */

#define TALI_TEST_MESSAGE                   0x74657374  /* test : no data */
#define TALI_ALLOW_SERVICE_MESSAGE          0x616C6C77  /* allw : no data */
#define TALI_PROHIBIT_SERVICE_MESSAGE       0x70726F68  /* proh : no data */
#define TALI_PROHIBIT_ACKNOWLEDGE_MESSAGE   0x70726F61  /* proa : no data */
#define TALI_MONITOR_MESSAGE                0x6D6F6E69  /* moni : data */
#define TALI_MONITOR_ACKNOWLEDGE_MESSAGE    0x6D6F6E61  /* mona : data */
#define TALI_SCCP_SERVICE_MESSAGE           0x73636370  /* sccp : data */
#define TALI_ISUP_SERVICE_MESSAGE           0x69736f74  /* isot : data */
#define TALI_MTP3_SERVICE_MESSAGE           0x6d747033  /* mtp3 : data */
#define TALI_EVENT_MESSAGE                  0xFFFFFFFF  /* -1   : data */

/*
 * Timers:
 *
 * T1 - interval between successive "test" messages.
 * T2 - interval between a sent "test" and a received
 *   "allo" or "proh" message.
 * T3 - how long to process SERVICE messages after a
 *   management prohibit.
 */

/*
 * This structure represents the header information in the first ten bytes
 * of all TALI messages.  Service data is stored in data for up to length
 * bytes.  Note that when this hits the wire it should be in network byte
 * order.
 */
typedef struct
{
    ITS_UINT    sync;       /* always SYNC */
    ITS_UINT    operation;  /* one of the opcodes above */
    ITS_USHORT  length;     /* length of what follows */
}
ITS_TALI_HDR;

/*
 * tali message when it actually contains data.
 */
typedef struct
{
    ITS_TALI_HDR    hdr;
    ITS_OCTET       data[TALI_MAX_MSG_SIZE];
}
ITS_TALI_MSG;

#endif /* TALI_MSGS_H */
