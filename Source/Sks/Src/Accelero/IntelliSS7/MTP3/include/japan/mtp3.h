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
 * LOG: Revision 1.2  2005/03/23 07:26:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.2  2004/12/17 03:27:53  randresol
 * LOG: Correct SLS problem for TTC
 * LOG:
 * LOG: Revision 1.1.4.1  2004/12/16 02:02:57  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 1.1.2.3  2004/12/16 00:45:09  randresol
 * LOG: Fix Initial link alignment problem
 * LOG:
 * LOG: Revision 1.1.2.2  2004/10/25 20:39:56  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 1.1.2.1  2004/10/08 23:36:45  randresol
 * LOG: Start Japan SS7
 * LOG:
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_MTP3_TTC_H_
#define _ITS_MTP3_TTC_H_

#ident "$Id: mtp3.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $"

#include <its.h>
#include <its_callback.h>

#include <japan/mtp2.h>

/*
 * Point Code format
 */
typedef struct
{
    ITS_OCTET   data[2];
}
MTP3_POINT_CODE_TTC;

/* Signalling Point ID: value range 0-15 */
#define MTP3_PC_SPID_MASK_TTC       (0x0FU)

#define MTP3_PC_SET_MEMBER_TTC(x,v)                                     \
    (((x).data[0] &= ~MTP3_PC_SPID_MASK_TTC),                           \
     ((x).data[0] |= ((v) & MTP3_PC_SPID_MASK_TTC)))
#define MTP3_PC_GET_MEMBER_TTC(x)                                       \
    ((x).data[0] & MTP3_PC_SPID_MASK_TTC)

/* Signalling Point Cluster: value range 0-255 */
#define MTP3_PC_CLUST_MASK_LOW_TTC  (0xF0U)
#define MTP3_PC_CLUST_MASK_HI_TTC   (0x0FU)

#define MTP3_PC_SET_CLUSTER_TTC(x,v)                                    \
    (((x).data[0] &= ~MTP3_PC_CLUST_MASK_LOW_TTC),                      \
     ((x).data[1] &= ~MTP3_PC_CLUST_MASK_HI_TTC),                       \
     ((x).data[0] |= (((v) << 4) & MTP3_PC_CLUST_MASK_LOW_TTC)),        \
     ((x).data[1] |= (((v) >> 4) & MTP3_PC_CLUST_MASK_HI_TTC)))
#define MTP3_PC_GET_CLUSTER_TTC(x)                                      \
    ((((x).data[0] & MTP3_PC_CLUST_MASK_LOW_TTC) >> 4) |                \
     (((x).data[1] & MTP3_PC_CLUST_MASK_HI_TTC) << 4))

/* Signalling Point Network: value range 0-15 */
#define MTP3_PC_NET_MASK_TTC        (0xF0U)

#define MTP3_PC_SET_NETWORK_TTC(x,v)                                    \
    (((x).data[1] &= MTP3_PC_NET_MASK_TTC),                             \
     ((x).data[1] |= (((v) << 4) & MTP3_PC_NET_MASK_TTC)))
#define MTP3_PC_GET_NETWORK_TTC(x)                                      \
    (((x).data[1] & MTP3_PC_NET_MASK_TTC) >> 4)

/*
 * point code as value
 */
#define MTP3_PC_SET_VALUE_TTC(x,v)                                      \
    (((x).data[0] = (ITS_OCTET)((v) & 0xFFU)),                            \
     ((x).data[1] = (ITS_OCTET)(((v) >> 8) & 0xFFU)))
#define MTP3_PC_GET_VALUE_TTC(x)                                        \
    ((((x).data[1] & 0xFFU) << 8) | ((x).data[0]))


/*
 * Routing Label format
 */
typedef struct
{
    ITS_OCTET   data[6];
}
MTP3_ROUTING_LABEL_TTC;

/* Destination Point Code */
#define MTP3_RL_DPC_HI_MASK_TTC     (0xFFU)

#define MTP3_RL_SET_DPC_TTC(x,v)                                        \
    (((x).data[0] = (v).data[0]),                                         \
     ((x).data[1] &= ~MTP3_RL_DPC_HI_MASK_TTC),                         \
     ((x).data[1] |= ((v).data[1] & MTP3_RL_DPC_HI_MASK_TTC)))
#define MTP3_RL_GET_DPC_TTC(x,v)                                        \
    (((v).data[0] = (x).data[0]),                                         \
     ((v).data[1] = ((x).data[1] & MTP3_RL_DPC_HI_MASK_TTC)))

/* Origination Point Code */
#define MTP3_RL_OPC_LOW_MASK_TTC    (0xFFU)
#define MTP3_RL_OPC_HI_MASK_TTC     (0xFFU)

#define MTP3_RL_SET_OPC_TTC(x,v)                                        \
    (((x).data[2] &= ~MTP3_RL_OPC_LOW_MASK_TTC),                        \
     ((x).data[2] |= (((v).data[0] ) & MTP3_RL_OPC_LOW_MASK_TTC)),      \
     ((x).data[3] &= ~MTP3_RL_OPC_HI_MASK_TTC),                         \
     ((x).data[3] |= (((v).data[1] ) & MTP3_RL_OPC_HI_MASK_TTC)))
#define MTP3_RL_GET_OPC_TTC(x,v)                                        \
    (((v).data[0] = ((x).data[2]) & MTP3_RL_OPC_LOW_MASK_TTC) ,         \
     ((v).data[1] = ((x).data[3] & MTP3_RL_OPC_HI_MASK_TTC)))

/* SLS */
#define MTP3_RL_SLS_MASK_TTC    (0x0FU)

#define MTP3_RL_SET_SLS_TTC(x,v)                                        \
    (((x).data[4] &= ~MTP3_RL_SLS_MASK_TTC),                            \
     ((x).data[4] |= ( (v)  & MTP3_RL_SLS_MASK_TTC)))
#define MTP3_RL_GET_SLS_TTC(x)                                          \
    ((x).data[4] & MTP3_RL_SLS_MASK_TTC) 

/*
 * point codes by value
 */
#define MTP3_RL_SET_DPC_VALUE_TTC(x,v)                                      \
    (((x).data[0] = (ITS_OCTET)((v) & 0xFFU)),                              \
     ((x).data[1] &= ~MTP3_RL_DPC_HI_MASK_TTC),                             \
     ((x).data[1] |= (ITS_OCTET)(((v) >> 8) & MTP3_RL_DPC_HI_MASK_TTC)))

#define MTP3_RL_GET_DPC_VALUE_TTC(x)                                        \
    ((x).data[0] | (((x).data[1] & MTP3_RL_DPC_HI_MASK_TTC) << 8))

#define MTP3_RL_SET_OPC_VALUE_TTC(x,v)                                      \
    (((x).data[2] &= ~MTP3_RL_OPC_LOW_MASK_TTC),                            \
     ((x).data[2] |= (ITS_OCTET)(((v) ) & MTP3_RL_OPC_LOW_MASK_TTC)),       \
     ((x).data[3] &= ~MTP3_RL_OPC_HI_MASK_TTC),                             \
     ((x).data[3] |= (ITS_OCTET)(((v) >> 8) & MTP3_RL_OPC_HI_MASK_TTC)))
#define MTP3_RL_GET_OPC_VALUE_TTC(x)                                        \
    (((x).data[2] & MTP3_RL_OPC_LOW_MASK_TTC)  |                            \
     (((x).data[3] & MTP3_RL_OPC_HI_MASK_TTC) << 8))

/*
 * MTP3 Message Header
 */
typedef struct
{
    ITS_OCTET                   sio;
    MTP3_ROUTING_LABEL_TTC    label;
}
MTP3_HEADER_TTC;

/* Service Information Octet */
#define MTP3_HDR_SET_SIO_TTC(x,v)                                       \
    ((x).sio = (v))
#define MTP3_HDR_GET_SIO_TTC(x)                                         \
    ((x).sio)

/*
 * User Data
 */
#define MTP3_MAX_SIF_LENGTH     300
typedef struct
{
    ITS_OCTET               data[1];
}
MTP3_USER_DATA_TTC;

/*
 * MTP3 Pause/Resume
 */
typedef struct
{
    MTP3_POINT_CODE_TTC   affected;
}
MTP3_PAUSE_RESUME_TTC;

/*
 * MTP3 Status
 */
typedef struct
{
    MTP3_POINT_CODE_TTC   affected;
    ITS_OCTET             cause;
    ITS_OCTET             congLevel;
}
MTP3_STATUS_TTC;

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
 * this is only for TTC.  The default variant is white book 97.
 * This is not valid for any stack other than the IntelliNet stack.
 */
#define TTC_MTP3_BLUE_BOOK        ITS_FIRST_GEN
#define TTC_MTP3_WHITE_BOOK       ITS_SECOND_GEN
#define TTC_MTP3_WHITE_BOOK_97    ITS_THIRD_GEN

SS7DLLAPI int MTP3_SetVariant_TTC(int variant);
SS7DLLAPI int MTP3_GetVariant_TTC();

SS7DLLAPI extern int  TTC_MTP3_Variant;

/*
 * UserData functions
 */
SS7DLLAPI int MTP3_Encode_TTC(ITS_EVENT* ev, ITS_OCTET type,
                                MTP3_HEADER_TTC* hdr,
                                ITS_OCTET* data, ITS_USHORT len);
SS7DLLAPI int MTP3_Decode_TTC(ITS_EVENT* ev, ITS_OCTET* type,
                                MTP3_HEADER_TTC* hdr,
                                ITS_OCTET* data, ITS_USHORT* len);

SS7DLLAPI int MTP3_SendEvent_TTC(ITS_HANDLE handl,
                                   ITS_OCTET type, MTP3_HEADER_TTC *mtp3,
                                   ITS_OCTET *buf, ITS_USHORT len);
SS7DLLAPI int MTP3_ReceiveEvent_TTC(ITS_HANDLE handl, ITS_EVENT *ev,
                                      ITS_OCTET *type, MTP3_HEADER_TTC *mtp3,
                                      ITS_OCTET *buf, ITS_USHORT *len);

/*
 * Management callbacks
 */
SS7DLLAPI extern CALLBACK_Manager*    MTP3_TTC_ManagementCallbacks;

/*
 * User Part management
 */
ITSSS7DLLAPI int           MTP3_EnableUserPart_TTC(ITS_OCTET up, ITS_USHORT id);
ITSSS7DLLAPI int           MTP3_DisableUserPart_TTC(ITS_OCTET up);
ITSSS7DLLAPI ITS_USHORT    MTP3_UserPartOwner_TTC(ITS_OCTET up);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_MTP3_TTC_H_ */
