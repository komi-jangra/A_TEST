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
 *  ID: $Id: mtp3.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
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
 * LOG: Revision 8.3  2005/03/21 13:50:17  cvsadmin
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
 * LOG: Revision 6.4  2002/05/28 21:34:29  mmiers
 * LOG: Try again.
 * LOG:
 * LOG: Revision 6.3  2002/05/28 21:28:15  mmiers
 * LOG: Still need cluster def
 * LOG:
 * LOG: Revision 6.2  2002/05/28 21:23:15  mmiers
 * LOG: Change the macros and comments.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.10  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.9  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.8  2001/10/18 20:02:52  mmiers
 * LOG: Avoid many version defines, destination parsing.
 * LOG:
 * LOG: Revision 5.7  2001/10/18 19:16:42  mmiers
 * LOG: Get engine in sync, add missing C++ guards in headers.
 * LOG:
 * LOG: Revision 5.6  2001/10/08 21:35:14  mmiers
 * LOG: Long form was calling short form.  Broken, broken, broken.
 * LOG:
 * LOG: Revision 5.5  2001/09/24 22:51:21  mmiers
 * LOG: Work on MTP3 integration.
 * LOG:
 * LOG: Revision 5.4  2001/09/14 19:09:19  mmiers
 * LOG: Add ANSI cluster detector.
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 23:06:41  mmiers
 * LOG: Initial cut at an MTP2 interface.  Likely to change.
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
 * LOG: Revision 3.4  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 3.3  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:32  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:01:54  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:26  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:27  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.17  1999/11/10 18:06:42  mmiers
 * LOG:
 * LOG:
 * LOG: Update after GDI.
 * LOG:
 * LOG: Revision 1.16  1999/08/27 21:27:19  mmiers
 * LOG:
 * LOG:
 * LOG: Change the point code format order for ANSI
 * LOG:
 * LOG: Revision 1.15  1999/06/28 17:00:50  mmiers
 * LOG:
 * LOG:
 * LOG: Move the generic dispatchers out of here.
 * LOG:
 * LOG: Revision 1.14  1999/06/25 19:29:19  labuser
 * LOG:
 * LOG:
 * LOG: Fix a bunch of brain farts with generic thread dispatchers.
 * LOG: This needs revisiting, as the argument type will screw up
 * LOG: C++ code expecting a true thread function signature.
 * LOG:
 * LOG: Revision 1.13  1999/06/23 22:58:26  mmiers
 * LOG:
 * LOG:
 * LOG: Slight compile flag modification
 * LOG:
 * LOG: Revision 1.12  1999/06/23 19:55:02  mmiers
 * LOG:
 * LOG:
 * LOG: Rework header files for dual protocol more intelligently.
 * LOG:
 * LOG: Revision 1.11  1999/02/13 00:44:18  mmiers
 * LOG:
 * LOG:
 * LOG: Prepare for ITU TCAP over ANSI SCCP and vice-versa.
 * LOG:
 * LOG: Revision 1.10  1998/11/17 22:31:14  mmiers
 * LOG: Some fixes to MTP3, SCCP.
 * LOG:
 * LOG: Revision 1.9  1998/11/16 20:44:26  mmiers
 * LOG: Flip the byte order in ANSI PC.
 * LOG:
 * LOG: Revision 1.8  1998/10/21 15:11:27  whu
 * LOG: Change syntax of how ansi includes itu header.
 * LOG:
 * LOG: Revision 1.7  1998/10/16 14:41:26  mmiers
 * LOG: Remove warnings about precision loss.
 * LOG:
 * LOG: Revision 1.6  1998/09/27 00:01:04  mmiers
 * LOG: Remove extra arg.
 * LOG:
 * LOG: Revision 1.5  1998/09/25 20:12:21  mmiers
 * LOG: Build MTP3 project.
 * LOG:
 * LOG: Revision 1.4  1998/09/25 19:40:11  mmiers
 * LOG: Integrate with SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/09/25 17:42:08  mmiers
 * LOG: Finish up what we need for MTP3.
 * LOG:
 * LOG: Revision 1.2  1998/09/25 17:18:26  mmiers
 * LOG: Definitions for MTP3 for ANSI and ITU.
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_MTP3_ANSI_H_
#define _ITS_MTP3_ANSI_H_

#ident "$Id: mtp3.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $"

#include <its.h>
#include <its_callback.h>

#include <ansi/mtp2.h>

/*
 * Point Code format
 */
typedef struct
{
    ITS_OCTET   data[3];
}
MTP3_POINT_CODE_ANSI;

/* Signalling Point ID: value range 0-255 */
#define MTP3_PC_SET_MEMBER_ANSI(x,v)                                     \
    ((x).data[0] = (v))
#define MTP3_PC_GET_MEMBER_ANSI(x)                                       \
    ((x).data[0])

/* Signalling Point Cluster: value range 0-255 */
#define MTP3_PC_SET_CLUSTER_ANSI(x,v)                                    \
    ((x).data[1] = (v))
#define MTP3_PC_GET_CLUSTER_ANSI(x)                                      \
    ((x).data[1])
#define MTP3_PC_IS_CLUSTER_ANSI(x)                                       \
    ((x).data[0] == 0)

/* Signalling Point Network: value range 1-255 */
#define MTP3_PC_SET_NETWORK_ANSI(x,v)                                    \
    ((x).data[2] = (v))
#define MTP3_PC_GET_NETWORK_ANSI(x)                                      \
    ((x).data[2])
#define MTP3_PC_IS_NETWORK_ANSI(x)                                       \
    ((x).data[2] != 0)

/*
 * point code as value
 */
#define MTP3_PC_SET_VALUE_ANSI(x,v)                                      \
    (((x).data[0] = (ITS_OCTET)((v) & 0xFFU)),                           \
     ((x).data[1] = (ITS_OCTET)(((v) >> 8) & 0xFFU)),                    \
     ((x).data[2] = (ITS_OCTET)(((v) >> 16) & 0xFFU)))
#define MTP3_PC_GET_VALUE_ANSI(x)                                        \
    ((x).data[0] | ((x).data[1] << 8) | ((x).data[2] << 16))


/*
 * Routing Label format
 */
typedef struct
{
    MTP3_POINT_CODE_ANSI    dpc;
    MTP3_POINT_CODE_ANSI    opc;
    ITS_OCTET               sls;
}
MTP3_ROUTING_LABEL_ANSI;

/* Destination Point Code */
#define MTP3_RL_SET_DPC_ANSI(x,v)                                        \
    ((x).dpc = (v))
#define MTP3_RL_GET_DPC_ANSI(x,v)                                        \
    ((v) = (x).dpc)

/* Origination Point Code */
#define MTP3_RL_SET_OPC_ANSI(x,v)                                        \
    ((x).opc = (v))
#define MTP3_RL_GET_OPC_ANSI(x,v)                                        \
    ((v) = (x).opc)

/* SLS */
#define MTP3_RL_SET_SLS_ANSI(x,v)                                        \
    ((x).sls = (v))
#define MTP3_RL_GET_SLS_ANSI(x)                                          \
    ((x).sls)

/*
 * point codes by value
 */
#define MTP3_RL_SET_DPC_VALUE_ANSI(x,v)                                  \
    MTP3_PC_SET_VALUE_ANSI((x).dpc, (v))
#define MTP3_RL_GET_DPC_VALUE_ANSI(x)                                    \
    MTP3_PC_GET_VALUE_ANSI((x).dpc)

#define MTP3_RL_SET_OPC_VALUE_ANSI(x,v)                                  \
    MTP3_PC_SET_VALUE_ANSI((x).opc, (v))
#define MTP3_RL_GET_OPC_VALUE_ANSI(x)                                    \
    MTP3_PC_GET_VALUE_ANSI((x).opc)

/*
 * MTP3 Header
 */
typedef struct
{
    ITS_OCTET                   sio;
    MTP3_ROUTING_LABEL_ANSI     label;
}
MTP3_HEADER_ANSI;

/* Service Information Octet */
#define MTP3_HDR_SET_SIO_ANSI(x,v)                                       \
    ((x).sio = (v))
#define MTP3_HDR_GET_SIO_ANSI(x)                                         \
    ((x).sio)

/*
 * User Data
 */
#define MTP3_MAX_SIF_LENGTH     300
typedef struct
{
    ITS_OCTET           data[1];
}
MTP3_USER_DATA_ANSI;

/*
 * MTP3 Pause/Resume
 */
typedef struct
{
    MTP3_POINT_CODE_ANSI    affected;
}
MTP3_PAUSE_RESUME_ANSI;

/*
 * MTP3 Status
 */
typedef struct
{
    MTP3_POINT_CODE_ANSI    affected;
    ITS_OCTET               cause;
    ITS_OCTET               congLevel;
}
MTP3_STATUS_ANSI;

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
 * this is only for ANSI.  The default variant is '96.
 * This is not valid for any stack other than the IntelliNet stack.
 */
#define ANSI_MTP3_1988      ITS_FIRST_GEN
#define ANSI_MTP3_1992      ITS_SECOND_GEN
#define ANSI_MTP3_1996      ITS_THIRD_GEN

SS7DLLAPI int MTP3_SetVariant_ANSI(int variant);
SS7DLLAPI int MTP3_GetVariant_ANSI();

SS7DLLAPI extern int  ANSI_MTP3_Variant;

/*
 * Management callbacks
 */
SS7DLLAPI extern CALLBACK_Manager*    MTP3_ANSI_ManagementCallbacks;

SS7DLLAPI int MTP3_Encode_ANSI(ITS_EVENT* ev, ITS_OCTET type,
                               MTP3_HEADER_ANSI* hdr,
                               ITS_OCTET* data, ITS_USHORT len);
SS7DLLAPI int MTP3_Decode_ANSI(ITS_EVENT* ev, ITS_OCTET* type,
                               MTP3_HEADER_ANSI* hdr,
                               ITS_OCTET* data, ITS_USHORT* len);

SS7DLLAPI int MTP3_SendEvent_ANSI(ITS_HANDLE handl,
                                  ITS_OCTET type, MTP3_HEADER_ANSI *mtp3,
                                  ITS_OCTET *buf, ITS_USHORT len);
SS7DLLAPI int MTP3_ReceiveEvent_ANSI(ITS_HANDLE handl, ITS_EVENT *ev,
                                     ITS_OCTET *type, MTP3_HEADER_ANSI *mtp3,
                                     ITS_OCTET *buf, ITS_USHORT *len);
SS7DLLAPI int MTP3_PPrint_ANSI(RINGBUF_Manager *rb, ITS_UINT *lCount,
                               MTP3_HEADER_ANSI *hdr);

/*
 * User Part management (only in our stack)
 */
ITSSS7DLLAPI int           MTP3_EnableUserPart_ANSI(ITS_OCTET up, ITS_USHORT id);
ITSSS7DLLAPI int           MTP3_DisableUserPart_ANSI(ITS_OCTET up);
ITSSS7DLLAPI ITS_USHORT    MTP3_UserPartOwner_ANSI(ITS_OCTET up);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_MTP3_ANSI_H_ */
