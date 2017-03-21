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
 * LOG: Revision 7.2  2003/01/07 15:27:22  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.1  2002/07/03 15:29:30  mmiers
 * LOG: Update for china
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_MTP3_PRC_H_
#define _ITS_MTP3_PRC_H_

#ident "$Id: mtp3.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $"

#include <its.h>
#include <its_callback.h>

#include <china/mtp2.h>

/*
 * Point Code format
 */
typedef struct
{
    ITS_OCTET   data[3];
}
MTP3_POINT_CODE_PRC;

/* Signalling Point ID: value range 0-255 */
#define MTP3_PC_SET_MEMBER_PRC(x,v)                                      \
    ((x).data[0] = (v))
#define MTP3_PC_GET_MEMBER_PRC(x)                                        \
    ((x).data[0])

/* Signalling Point Cluster: value range 0-255 */
#define MTP3_PC_SET_CLUSTER_PRC(x,v)                                     \
    ((x).data[1] = (v))
#define MTP3_PC_GET_CLUSTER_PRC(x)                                       \
    ((x).data[1])
#define MTP3_PC_IS_CLUSTER_PRC(x)                                        \
    ((x).data[0] == 0)

/* Signalling Point Network: value range 1-255 */
#define MTP3_PC_SET_NETWORK_PRC(x,v)                                     \
    ((x).data[2] = (v))
#define MTP3_PC_GET_NETWORK_PRC(x)                                       \
    ((x).data[2])
#define MTP3_PC_IS_NETWORK_PRC(x)                                        \
    ((x).data[2] != 0)

/*
 * point code as value
 */
#define MTP3_PC_SET_VALUE_PRC(x,v)                                       \
    (((x).data[0] = (ITS_OCTET)((v) & 0xFFU)),                           \
     ((x).data[1] = (ITS_OCTET)(((v) >> 8) & 0xFFU)),                    \
     ((x).data[2] = (ITS_OCTET)(((v) >> 16) & 0xFFU)))
#define MTP3_PC_GET_VALUE_PRC(x)                                         \
    ((x).data[0] | ((x).data[1] << 8) | ((x).data[2] << 16))


/*
 * Routing Label format
 */
typedef struct
{
    MTP3_POINT_CODE_PRC    dpc;
    MTP3_POINT_CODE_PRC    opc;
    ITS_OCTET               sls;
}
MTP3_ROUTING_LABEL_PRC;

/* Destination Point Code */
#define MTP3_RL_SET_DPC_PRC(x,v)                                         \
    ((x).dpc = (v))
#define MTP3_RL_GET_DPC_PRC(x,v)                                         \
    ((v) = (x).dpc)

/* Origination Point Code */
#define MTP3_RL_SET_OPC_PRC(x,v)                                         \
    ((x).opc = (v))
#define MTP3_RL_GET_OPC_PRC(x,v)                                         \
    ((v) = (x).opc)

/* SLS */
#define MTP3_RL_SET_SLS_PRC(x,v)                                         \
    ((x).sls = (v))
#define MTP3_RL_GET_SLS_PRC(x)                                           \
    ((x).sls)

/*
 * point codes by value
 */
#define MTP3_RL_SET_DPC_VALUE_PRC(x,v)                                   \
    MTP3_PC_SET_VALUE_PRC((x).dpc, (v))
#define MTP3_RL_GET_DPC_VALUE_PRC(x)                                     \
    MTP3_PC_GET_VALUE_PRC((x).dpc)

#define MTP3_RL_SET_OPC_VALUE_PRC(x,v)                                   \
    MTP3_PC_SET_VALUE_PRC((x).opc, (v))
#define MTP3_RL_GET_OPC_VALUE_PRC(x)                                     \
    MTP3_PC_GET_VALUE_PRC((x).opc)

/*
 * MTP3 Header
 */
typedef struct
{
    ITS_OCTET                   sio;
    MTP3_ROUTING_LABEL_PRC     label;
}
MTP3_HEADER_PRC;

/* Service Information Octet */
#define MTP3_HDR_SET_SIO_PRC(x,v)                                        \
    ((x).sio = (v))
#define MTP3_HDR_GET_SIO_PRC(x)                                          \
    ((x).sio)

/*
 * User Data
 */
#define MTP3_MAX_SIF_LENGTH     300
typedef struct
{
    ITS_OCTET           data[1];
}
MTP3_USER_DATA_PRC;

/*
 * MTP3 Pause/Resume
 */
typedef struct
{
    MTP3_POINT_CODE_PRC     affected;
}
MTP3_PAUSE_RESUME_PRC;

/*
 * MTP3 Status
 */
typedef struct
{
    MTP3_POINT_CODE_PRC     affected;
    ITS_OCTET               cause;
    ITS_OCTET               congLevel;
}
MTP3_STATUS_PRC;

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
 * this is only for PRC.  The default variant is '97.
 * This is not valid for any stack other than the IntelliNet stack.
 */
#define PRC_MTP3_BLUE_BOOK      ITS_FIRST_GEN
#define PRC_MTP3_WHITE_BOOK     ITS_SECOND_GEN
#define PRC_MTP3_WHITE_BOOK_97  ITS_THIRD_GEN

SS7DLLAPI int MTP3_SetVariant_PRC(int variant);
SS7DLLAPI int MTP3_GetVariant_PRC();

SS7DLLAPI extern int  PRC_MTP3_Variant;

/*
 * Management callbacks
 */
SS7DLLAPI extern CALLBACK_Manager*    MTP3_PRC_ManagementCallbacks;

SS7DLLAPI int MTP3_Encode_PRC(ITS_EVENT* ev, ITS_OCTET type,
                              MTP3_HEADER_PRC* hdr,
                              ITS_OCTET* data, ITS_USHORT len);
SS7DLLAPI int MTP3_Decode_PRC(ITS_EVENT* ev, ITS_OCTET* type,
                              MTP3_HEADER_PRC* hdr,
                              ITS_OCTET* data, ITS_USHORT* len);

SS7DLLAPI int MTP3_SendEvent_PRC(ITS_HANDLE handl,
                                 ITS_OCTET type, MTP3_HEADER_PRC *mtp3,
                                 ITS_OCTET *buf, ITS_USHORT len);
SS7DLLAPI int MTP3_ReceiveEvent_PRC(ITS_HANDLE handl, ITS_EVENT *ev,
                                    ITS_OCTET *type, MTP3_HEADER_PRC *mtp3,
                                    ITS_OCTET *buf, ITS_USHORT *len);
SS7DLLAPI int MTP3_PPrint_PRC(RINGBUF_Manager *rb, ITS_UINT *lCount,
                               MTP3_HEADER_PRC *hdr);

/*
 * User Part management (only in our stack)
 */
ITSSS7DLLAPI int           MTP3_EnableUserPart_PRC(ITS_OCTET up, ITS_USHORT id);
ITSSS7DLLAPI int           MTP3_DisableUserPart_PRC(ITS_OCTET up);
ITSSS7DLLAPI ITS_USHORT    MTP3_UserPartOwner_PRC(ITS_OCTET up);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_MTP3_PRC_H_ */
