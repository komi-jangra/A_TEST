/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: mtp3.h,v 1.2 2008-02-13 02:04:43 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:23  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:46  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:12  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:17  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:50:17  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1  2004/09/21 06:54:43  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 22:11:41  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/03 15:29:30  mmiers
 * LOG: Update for china
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.8  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.7  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.6  2001/10/18 20:02:52  mmiers
 * LOG: Avoid many version defines, destination parsing.
 * LOG:
 * LOG: Revision 5.5  2001/09/24 22:51:21  mmiers
 * LOG: Work on MTP3 integration.
 * LOG:
 * LOG: Revision 5.4  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.3  2001/09/05 23:06:41  mmiers
 * LOG: Initial cut at an MTP2 interface.  Likely to change.
 * LOG:
 * LOG: Revision 5.2  2001/08/23 21:04:13  mmiers
 * LOG: Fix comment.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:46  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/08/07 22:01:41  mmiers
 * LOG: Add API
 * LOG:
 * LOG: Revision 4.2  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:10  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 3.4  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.3  2000/11/30 22:45:32  mmiers
 * LOG: Common stuff.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:32  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:01:55  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:26  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:28  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.33  1999/11/10 18:06:42  mmiers
 * LOG:
 * LOG:
 * LOG: Update after GDI.
 * LOG:
 * LOG: Revision 1.32  1999/10/06 15:59:52  mmiers
 * LOG:
 * LOG:
 * LOG: Add new user part for signalling network management messages.
 * LOG:
 * LOG: Revision 1.31  1999/10/05 18:57:33  rsonak
 * LOG:
 * LOG: Moved the protocol defines here from its.h
 * LOG:
 * LOG: Revision 1.30  1999/08/26 00:48:26  rsonak
 * LOG:
 * LOG:
 * LOG: Long standing bug in OPC_GET
 * LOG:
 * LOG: Revision 1.29  1999/06/28 17:00:51  mmiers
 * LOG:
 * LOG:
 * LOG: Move the generic dispatchers out of here.
 * LOG:
 * LOG: Revision 1.28  1999/06/25 19:29:20  labuser
 * LOG:
 * LOG:
 * LOG: Fix a bunch of brain farts with generic thread dispatchers.
 * LOG: This needs revisiting, as the argument type will screw up
 * LOG: C++ code expecting a true thread function signature.
 * LOG:
 * LOG: Revision 1.27  1999/06/23 19:56:38  mmiers
 * LOG:
 * LOG:
 * LOG: Rework MTP3 for saner implementation of dual protocols.
 * LOG:
 * LOG: Revision 1.26  1999/03/17 18:41:55  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol updates.
 * LOG:
 * LOG: Revision 1.25  1999/03/17 15:10:06  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol work.
 * LOG:
 * LOG: Revision 1.24  1999/02/13 00:44:19  mmiers
 * LOG:
 * LOG:
 * LOG: Prepare for ITU TCAP over ANSI SCCP and vice-versa.
 * LOG:
 * LOG: Revision 1.23  1999/02/12 23:40:22  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for simultaneous protocol families.
 * LOG:
 * LOG: Revision 1.22  1998/11/11 00:44:45  mmiers
 * LOG: Enhance routing a bit to simplify the logic and increase speed.
 * LOG: Work on defining CPC/CSSN information for SCCP.  Almost done.
 * LOG:
 * LOG: Revision 1.21  1998/10/28 23:52:48  mmiers
 * LOG: Update for SCCP SCMG.
 * LOG:
 * LOG: Revision 1.20  1998/10/28 00:26:50  mmiers
 * LOG: Warning avoidance.
 * LOG:
 * LOG: Revision 1.19  1998/10/21 15:11:27  whu
 * LOG: Change syntax of how ansi includes itu header.
 * LOG:
 * LOG: Revision 1.18  1998/10/16 14:41:27  mmiers
 * LOG: Remove warnings about precision loss.
 * LOG:
 * LOG: Revision 1.17  1998/10/15 23:15:26  mmiers
 * LOG: Add C++ for MTP3.  Add routing label to SCCP.
 * LOG:
 * LOG: Revision 1.16  1998/10/15 17:26:49  mmiers
 * LOG: Add C++ API for MTP3.
 * LOG:
 * LOG: Revision 1.15  1998/09/30 02:40:00  mmiers
 * LOG: Updates for SCCP.  I think I've got the compromises for SCCP routing
 * LOG: down.  Need to add the routing label everywhere.
 * LOG:
 * LOG: Revision 1.14  1998/09/29 21:38:49  mmiers
 * LOG: Bug fixes for new SCCP support.
 * LOG:
 * LOG: Revision 1.12  1998/09/29 17:32:46  mmiers
 * LOG: Tweaking MTP3.
 * LOG:
 * LOG: Revision 1.11  1998/09/28 17:39:36  mmiers
 * LOG: Add Init, Term functions.
 * LOG:
 * LOG: Revision 1.10  1998/09/28 17:27:36  mmiers
 * LOG: Add some helper functions.
 * LOG:
 * LOG: Revision 1.9  1998/09/27 00:01:04  mmiers
 * LOG: Remove extra arg.
 * LOG:
 * LOG: Revision 1.8  1998/09/25 20:29:45  mmiers
 * LOG: Build MTP3 library (all 2 functions).
 * LOG:
 * LOG: Revision 1.7  1998/09/25 20:12:22  mmiers
 * LOG: Build MTP3 project.
 * LOG:
 * LOG: Revision 1.6  1998/09/25 19:51:59  mmiers
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.5  1998/09/25 19:40:11  mmiers
 * LOG: Integrate with SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/09/25 17:42:09  mmiers
 * LOG: Finish up what we need for MTP3.
 * LOG:
 * LOG: Revision 1.3  1998/09/25 17:26:44  mmiers
 * LOG: Parentheses alignment.
 * LOG:
 * LOG: Revision 1.2  1998/09/25 17:18:26  mmiers
 * LOG: Definitions for MTP3 for ANSI and ITU.
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_MTP3_CCITT_H_
#define _ITS_MTP3_CCITT_H_

#ident "$Id: mtp3.h,v 1.2 2008-02-13 02:04:43 bsccs2 Exp $"

#include <its.h>
#include <its_callback.h>

#include <itu/mtp2.h>

/*
 * Point Code format
 */
typedef struct
{
    ITS_OCTET   data[2];
}
MTP3_POINT_CODE_CCITT;

/* Signalling Point ID: value range 0-7 */
#define MTP3_PC_SPID_MASK_CCITT       (0x03U)

#define MTP3_PC_SET_MEMBER_CCITT(x,v)                                     \
    (((x).data[0] &= ~MTP3_PC_SPID_MASK_CCITT),                           \
     ((x).data[0] |= ((v) & MTP3_PC_SPID_MASK_CCITT)))
#define MTP3_PC_GET_MEMBER_CCITT(x)                                       \
    ((x).data[0] & MTP3_PC_SPID_MASK_CCITT)

/* Signalling Point Cluster: value range 0-255 */
#define MTP3_PC_CLUST_MASK_LOW_CCITT  (0xF8U)
#define MTP3_PC_CLUST_MASK_HI_CCITT   (0x07U)

#define MTP3_PC_SET_CLUSTER_CCITT(x,v)                                    \
    (((x).data[0] &= ~MTP3_PC_CLUST_MASK_LOW_CCITT),                      \
     ((x).data[1] &= ~MTP3_PC_CLUST_MASK_HI_CCITT),                       \
     ((x).data[0] |= (((v) << 3) & MTP3_PC_CLUST_MASK_LOW_CCITT)),        \
     ((x).data[1] |= (((v) >> 5) & MTP3_PC_CLUST_MASK_HI_CCITT)))
#define MTP3_PC_GET_CLUSTER_CCITT(x)                                      \
    ((((x).data[0] & MTP3_PC_CLUST_MASK_LOW_CCITT) >> 3) |                \
     (((x).data[1] & MTP3_PC_CLUST_MASK_HI_CCITT) << 5))

/* Signalling Point Network: value range 0-7 */
#define MTP3_PC_NET_MASK_CCITT        (0x38U)

#define MTP3_PC_SET_NETWORK_CCITT(x,v)                                    \
    (((x).data[1] &= MTP3_PC_NET_MASK_CCITT),                             \
     ((x).data[1] |= (((v) << 3) & MTP3_PC_NET_MASK_CCITT)))
#define MTP3_PC_GET_NETWORK_CCITT(x)                                      \
    (((x).data[1] & MTP3_PC_NET_MASK_CCITT) >> 3)

/*
 * point code as value
 */
#define MTP3_PC_SET_VALUE_CCITT(x,v)                                      \
    (((x).data[0] = (ITS_OCTET)((v) & 0xFFU)),                            \
     ((x).data[1] = (ITS_OCTET)(((v) >> 8) & 0x3FU)))
#define MTP3_PC_GET_VALUE_CCITT(x)                                        \
    ((((x).data[1] & 0x3FU) << 8) | ((x).data[0]))


/*
 * Routing Label format
 */
typedef struct
{
    ITS_OCTET   data[4];
}
MTP3_ROUTING_LABEL_CCITT;

/* Destination Point Code */
#define MTP3_RL_DPC_HI_MASK_CCITT     (0x3FU)

#define MTP3_RL_SET_DPC_CCITT(x,v)                                        \
    (((x).data[0] = (v).data[0]),                                         \
     ((x).data[1] &= ~MTP3_RL_DPC_HI_MASK_CCITT),                         \
     ((x).data[1] |= ((v).data[1] & MTP3_RL_DPC_HI_MASK_CCITT)))
#define MTP3_RL_GET_DPC_CCITT(x,v)                                        \
    (((v).data[0] = (x).data[0]),                                         \
     ((v).data[1] = ((x).data[1] & MTP3_RL_DPC_HI_MASK_CCITT)))

/* Origination Point Code */
#define MTP3_RL_OPC_LOW_MASK_CCITT    (0xC0U)
#define MTP3_RL_OPC_HI_MASK_CCITT     (0x0FU)

#define MTP3_RL_SET_OPC_CCITT(x,v)                                        \
    (((x).data[1] &= ~MTP3_RL_OPC_LOW_MASK_CCITT),                        \
     ((x).data[1] |= (((v).data[0] << 6) & MTP3_RL_OPC_LOW_MASK_CCITT)),  \
     ((x).data[2] = ((v).data[0] >> 2) & 0X3FU),                          \
     ((x).data[2] &= ~MTP3_RL_OPC_LOW_MASK_CCITT),                        \
     ((x).data[2] |= (((v).data[1] << 6) & MTP3_RL_OPC_LOW_MASK_CCITT)),  \
     ((x).data[3] &= ~MTP3_RL_OPC_HI_MASK_CCITT),                         \
     ((x).data[3] |= (((v).data[1] >> 2) & MTP3_RL_OPC_HI_MASK_CCITT)))
#define MTP3_RL_GET_OPC_CCITT(x,v)                                        \
    (((v).data[0] = ((((x).data[1] & MTP3_RL_OPC_LOW_MASK_CCITT) >> 6) |  \
                     (((x).data[2] << 2) & 0xFCU))),                      \
     ((v).data[1] = ((((x).data[2] & MTP3_RL_OPC_LOW_MASK_CCITT) >> 6) |  \
                     (((x).data[3] << 2) & 0x3CU))))

/* SLS */
#define MTP3_RL_SLS_MASK_CCITT    (0xF0U)

#define MTP3_RL_SET_SLS_CCITT(x,v)                                        \
    (((x).data[3] &= ~MTP3_RL_SLS_MASK_CCITT),                            \
     ((x).data[3] |= (((v) << 4) & MTP3_RL_SLS_MASK_CCITT)))
#define MTP3_RL_GET_SLS_CCITT(x)                                          \
    (((x).data[3] & MTP3_RL_SLS_MASK_CCITT) >> 4)

/*
 * point codes by value
 */
#define MTP3_RL_SET_DPC_VALUE_CCITT(x,v)                                      \
    (((x).data[0] = (ITS_OCTET)(v)),                                          \
     ((x).data[1] &= ~MTP3_RL_DPC_HI_MASK_CCITT),                             \
     ((x).data[1] |= (ITS_OCTET)(((v) >> 8) & MTP3_RL_DPC_HI_MASK_CCITT)))

#define MTP3_RL_GET_DPC_VALUE_CCITT(x)                                        \
    ((x).data[0] | (((x).data[1] & MTP3_RL_DPC_HI_MASK_CCITT) << 8))

#define MTP3_RL_SET_OPC_VALUE_CCITT(x,v)                                      \
    (((x).data[1] &= ~MTP3_RL_OPC_LOW_MASK_CCITT),                            \
     ((x).data[1] |= (ITS_OCTET)(((v) << 6) & MTP3_RL_OPC_LOW_MASK_CCITT)),   \
     ((x).data[2] = (ITS_OCTET)((v) >> 2) & 0XFFU),                           \
     ((x).data[3] &= ~MTP3_RL_OPC_HI_MASK_CCITT),                             \
     ((x).data[3] |= (ITS_OCTET)(((v) >> 10) & MTP3_RL_OPC_HI_MASK_CCITT)))
#define MTP3_RL_GET_OPC_VALUE_CCITT(x)                                        \
    ((((x).data[1] & MTP3_RL_OPC_LOW_MASK_CCITT) >> 6) |                      \
      ((x).data[2] << 2) |                                                    \
     (((x).data[3] & MTP3_RL_OPC_HI_MASK_CCITT) << 10))

/*
 * MTP3 Message Header
 */
typedef struct
{
    ITS_OCTET                   sio;
    MTP3_ROUTING_LABEL_CCITT    label;
}
MTP3_HEADER_CCITT;

/* Service Information Octet */
#define MTP3_HDR_SET_SIO_CCITT(x,v)                                       \
    ((x).sio = (v))
#define MTP3_HDR_GET_SIO_CCITT(x)                                         \
    ((x).sio)

/*
 * User Data
 */
#define MTP3_MAX_SIF_LENGTH     300
typedef struct
{
    ITS_OCTET               data[1];
}
MTP3_USER_DATA_CCITT;

/*
 * MTP3 Pause/Resume
 */
typedef struct
{
    MTP3_POINT_CODE_CCITT   affected;
}
MTP3_PAUSE_RESUME_CCITT;

/*
 * MTP3 Status
 */
typedef struct
{
    MTP3_POINT_CODE_CCITT   affected;
    ITS_OCTET               cause;
    ITS_OCTET               congLevel;
}
MTP3_STATUS_CCITT;

/*
 * include common defines
 */
#include <mtp3_cmn.h>

/*.interface:MTP3_
 *****************************************************************************
 *  Interface:
 *      MTP3_*
 *
 *  Purpose:
 *      This interface provides the user access to "MTP3" like functions
 *      (or direct MTP3, as the case may be) to the user.
 *
 *  Usage:
 *
 *****************************************************************************/

/*
 * short names are deprecated and may be removed in a future release
 */
#include <mtp3_sn.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * this is only for CCITT.  The default variant is white book 97.
 * This is not valid for any stack other than the IntelliNet stack.
 */
#define CCITT_MTP3_BLUE_BOOK        ITS_FIRST_GEN
#define CCITT_MTP3_WHITE_BOOK       ITS_SECOND_GEN
#define CCITT_MTP3_WHITE_BOOK_97    ITS_THIRD_GEN

SS7DLLAPI int MTP3_SetVariant_CCITT(int variant);
SS7DLLAPI int MTP3_GetVariant_CCITT();

SS7DLLAPI extern int  CCITT_MTP3_Variant;

/*
 * UserData functions
 */
SS7DLLAPI int MTP3_Encode_CCITT(ITS_EVENT* ev, ITS_OCTET type,
                                MTP3_HEADER_CCITT* hdr,
                                ITS_OCTET* data, ITS_USHORT len);
SS7DLLAPI int MTP3_Decode_CCITT(ITS_EVENT* ev, ITS_OCTET* type,
                                MTP3_HEADER_CCITT* hdr,
                                ITS_OCTET* data, ITS_USHORT* len);

SS7DLLAPI int MTP3_SendEvent_CCITT(ITS_HANDLE handl,
                                   ITS_OCTET type, MTP3_HEADER_CCITT *mtp3,
                                   ITS_OCTET *buf, ITS_USHORT len);
SS7DLLAPI int MTP3_ReceiveEvent_CCITT(ITS_HANDLE handl, ITS_EVENT *ev,
                                      ITS_OCTET *type, MTP3_HEADER_CCITT *mtp3,
                                      ITS_OCTET *buf, ITS_USHORT *len);
SS7DLLAPI int MTP3_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *lCount,
                                MTP3_HEADER_CCITT *hdr);

/*
 * Management callbacks
 */
SS7DLLAPI extern CALLBACK_Manager*    MTP3_CCITT_ManagementCallbacks;

/*
 * User Part management
 */
ITSSS7DLLAPI int           MTP3_EnableUserPart_CCITT(ITS_OCTET up, ITS_USHORT id);
ITSSS7DLLAPI int           MTP3_DisableUserPart_CCITT(ITS_OCTET up);
ITSSS7DLLAPI ITS_USHORT    MTP3_UserPartOwner_CCITT(ITS_OCTET up);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_MTP3_CCITT_H_ */
