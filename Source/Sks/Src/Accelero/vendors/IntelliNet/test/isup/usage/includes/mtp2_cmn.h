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
 * ID: $Id: mtp2_cmn.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:44:57  hbalimid
 * LOG: Got here for demo isup
 * LOG:
 * LOG: Revision 5.11  2001/12/11 23:50:19  mmiers
 * LOG: Redundant signal.
 * LOG:
 * LOG: Revision 5.10  2001/11/30 15:28:17  mmiers
 * LOG: Add a few commands.
 * LOG:
 * LOG: Revision 5.9  2001/10/05 22:59:15  mmiers
 * LOG: Update from working on NMS MTP2 API
 * LOG:
 * LOG: Revision 5.8  2001/09/28 21:32:32  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 * LOG: Revision 5.7  2001/09/20 22:52:19  mmiers
 * LOG: Congestion addition
 * LOG:
 * LOG: Revision 5.6  2001/09/13 15:29:37  mmiers
 * LOG: Make all signals hex
 * LOG:
 * LOG: Revision 5.5  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.4  2001/09/06 17:24:39  mmiers
 * LOG: Closing in.
 * LOG:
 * LOG: Revision 5.3  2001/09/05 23:06:40  mmiers
 * LOG: Initial cut at an MTP2 interface.  Likely to change.
 * LOG:
 * LOG: Revision 5.2  2001/08/27 22:57:25  mmiers
 * LOG: More L2 signals.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:46  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/08/07 20:28:30  mmiers
 * LOG: Adjust common codes.
 * LOG:
 * LOG: Revision 4.5  2001/08/02 16:33:16  mmiers
 * LOG: Update signals.
 * LOG:
 * LOG: Revision 4.4  2001/08/01 21:51:07  mmiers
 * LOG: Add additional signals.
 * LOG:
 * LOG: Revision 4.3  2001/07/27 21:49:47  mmiers
 * LOG: Add MTP2 signals.
 * LOG:
 * LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
 * LOG: Make sure files end with newline
 * LOG:
 * LOG: Revision 4.1  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 *                 
 ****************************************************************************/

#if !defined(_ITS_MTP2_CMN_H_)
#define _ITS_MTP2_CMN_H_

#ident "$Id: mtp2_cmn.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $"

/*
 * fill this in (the header I think is family independent)
 */

/******************************** SIGNALS ***********************************/

#define MTP2_SIGNAL_DIR_BIT     (0x80)

#define MTP2_SIGNAL_FROM_L2(s)  (((s) & MTP2_SIGNAL_DIR_BIT) == 0)
#define MTP2_SIGNAL_TO_L2(s)    ((s) & MTP2_SIGNAL_DIR_BIT))

/*
 * NOTE:
 *
 * These codes MUST NOT overlap with the MTP3 message type codes.
 * MTP3 message types are allocated the range 0 - 64.
 * L2 to L3 are allocated 64-127.
 * L3 to L2 are allocated 128-255.
 */

/*
 * FROM L2
 */
#define L2_L3_IN_SERVICE                (0x41)
#define L2_L3_REMOTE_PROCESSOR_OUT      (0x42)
#define L2_L3_OUT_OF_SERVICE            (0x43)
#define L2_L3_REMOTE_PROCESSOR_REC      (0x44)
#define L2_L3_DATA                      (0x45)
#define L2_L3_BSNT                      (0x46)
#define L2_L3_BSNT_NOT_RETRIEVABLE      (0x47)
#define L2_L3_RETRIEVED_MSG             (0x48)
#define L2_L3_RETRIEVAL_COMPLETE        (0x49)
#define L2_L3_RETRIEVAL_NOT_POSSIBLE    (0x4A)
#define L2_L3_RB_CLEARED                (0x4B)
#define L2_L3_RTB_CLEARED               (0x4C)
#define L2_L3_CONGESTION_ONSET          (0x4D)
#define L2_L3_CONGESTION_ABATES         (0x4E)

/*
 * TO L2
 */
#define L3_L2_START                     (0x80)
#define L3_L2_STOP                      (0x81)
#define L3_L2_RESUME                    (0x82)
#define L3_L2_CLEAR_BUFFERS             (0x83)
#define L3_L2_CLEAR_RTB                 (0x84)
#define L3_L2_EMERGENCY                 (0x85)
#define L3_L2_EMERGENCY_CEASE           (0x86)
#define L3_L2_DATA                      (0x87)
#define L3_L2_RETRIEVE_BSNT             (0x88)
#define L3_L2_RETRIEVE_MSGS             (0x89)
#define L3_L2_FLOW_CONTROL_START        (0x8A)
#define L3_L2_FLOW_CONTROL_STOP         (0x8B)
#define L3_L2_LOCAL_PROCESSOR_OUT       (0x8C)
#define L3_L2_LOCAL_PROCESSOR_REC       (0x8D)

/*
 * This one says L3 to L1.  I suspect L2 needs to know.
 */
#define L3_L2_CONNECT                   (0x90)
#define L3_L2_DISCONNECT                (0x91)

/*
 * the format of a message to/from L2
 * data[0]   - signal
 * data[1]   - link set
 * data[2]   - link code
 * data[3-n] - message
 */
#define L2_MSG_TYPE(ev)     ((ev)->data[0])
#define L2_LINK_SET(ev)     ((ev)->data[1])
#define L2_LINK_CODE(ev)    ((ev)->data[2])
#define L2_LINK_DATA(ev)    (&(ev)->data[3])

#endif /* _ITS_MTP2_CMN_H_ */

