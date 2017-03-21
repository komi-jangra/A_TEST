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
 *     FILE: sccp.h                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: sccp_cmn.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:21  cvsadmin
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
 * LOG: Revision 5.4  2002/01/02 20:57:52  mmiers
 * LOG: Get rid of the shortname conversion for the routing label.
 * LOG: It breaks hybrid stack building.
 * LOG:
 * LOG: Revision 5.3  2002/01/02 19:55:46  mmiers
 * LOG: Convert to long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:47  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
 * LOG: Make sure files end with newline
 * LOG:
 * LOG: Revision 4.1  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_SCCP_CMN_H_
#define _ITS_SCCP_CMN_H_

#ident "$Id: sccp_cmn.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $"

#include <ansi/mtp3.h>
#include <itu/mtp3.h>

/*
 * T1.114 SCCP parameters
 */

/*
 * message type
 */
#define SCCP_MSG_CR         (0x01U)     /* Connection Request */
#define SCCP_MSG_CC         (0x02U)     /* Conection Confirm */     
#define SCCP_MSG_CREF       (0x03U)     /* Connection REFused */
#define SCCP_MSG_RLSD       (0x04U)     /* ReLeaSed */
#define SCCP_MSG_RLC        (0x05U)     /* ReLease Complete */
#define SCCP_MSG_DT1        (0x06U)     /* DaTa form 1 */
#define SCCP_MSG_DT2        (0x07U)     /* DaTa form 2 */
#define SCCP_MSG_AK         (0x08U)     /* AcKnowledgement */
#define SCCP_MSG_UDT        (0x09U)     /* Unit DaTa */
#define SCCP_MSG_XUDT       (0x11U)     /* eXtended Unit DaTa */
#define SCCP_MSG_UDTS       (0x0AU)     /* Unit DaTa Service */
#define SCCP_MSG_XUDTS      (0x12U)     /* eXtended Unit DaTa Service */
#define SCCP_MSG_ED         (0x0BU)     /* Expedited Data */
#define SCCP_MSG_EA         (0x0CU)     /* Expedited data Acknowledgement */
#define SCCP_MSG_RSR        (0x0DU)     /* ReSet Request */
#define SCCP_MSG_RSC        (0x0EU)     /* ReSet Confirmation */
#define SCCP_MSG_ERR        (0x0FU)     /* ERRor */
#define SCCP_MSG_IT         (0x10U)     /* Inactivity Test */
#define SCCP_MSG_NOTICE     (0xFFU)     /* Notice from MTP3/to user */
#define SCCP_MSG_LUDT       (0x13U)     /* Long Unitdata message */
#define SCCP_MSG_LUDTS      (0x14U)     /* Long Unitdata Service Msg */

/*
 * parameter tags
 */
#define SCCP_PRM_EOP                (0x00U)
#define SCCP_PRM_DEST_LOCAL_REF     (0x01U)
#define SCCP_PRM_SRC_LOCAL_REF      (0x02U)
#define SCCP_PRM_CALLED_PARTY_ADDR  (0x03U)
#define SCCP_PRM_CALLING_PARTY_ADDR (0x04U)
#define SCCP_PRM_PROTOCOL_CLASS     (0x05U)
#define SCCP_PRM_SEGMENT_REASSEM    (0x06U)
#define SCCP_PRM_RCV_SEQ_NUM        (0x07U)
#define SCCP_PRM_SEQUENCE_SEGMENT   (0x08U)
#define SCCP_PRM_CREDIT             (0x09U)
#define SCCP_PRM_RELEASE_CAUSE      (0x0AU)
#define SCCP_PRM_RETURN_CAUSE       (0x0BU)
#define SCCP_PRM_RESET_CAUSE        (0x0CU)
#define SCCP_PRM_ERROR_CAUSE        (0x0DU)
#define SCCP_PRM_REFUSAL_CAUSE      (0x0EU)
#define SCCP_PRM_DATA               (0x0FU)
#define SCCP_PRM_SEGMENTATION       (0x10U)
#define SCCP_PRM_HOP_COUNTER        (0x11U)
#define SCCP_PRM_IMPORTANCE         (0x12U)
#define SCCP_PRM_LONG_DATA          (0x13U)
#define SCCP_PRM_ISNI               (0xFAU)
#define SCCP_PRM_ROUTING_LABEL      (0xFFU)     /* This is fake, but SCCP
                                                 * needs to know the values
                                                 * in certain cases */

/*
 * reference
 */
typedef struct
{
    ITS_OCTET   refno[3];
}
SCCP_REF_NUM;

#define RN_GET_REF_NUM(x) \
    (((x).refno[0] << 16) | ((x).refno[1] << 8) | ((x).refno[2]))
#define RN_SET_REF_NUM(x,y)                   \
    (((x).refno[0] = (((y) >> 16) & 0xFFU)),  \
     ((x).refno[1] = (((y) >> 8) & 0xFFU)),   \
     ((x).refno[2] = ((y) & 0xFFU)))

/*
 * calling and called party address
 */

/*
 * address indicator
 */

/*
 * flags
 */
#define SCCP_CPA_HAS_PC_CCITT   0x01U
#define SCCP_CPA_HAS_SSN_CCITT  0x02U

#define SCCP_CPA_HAS_PC_ANSI    0x02U
#define SCCP_CPA_HAS_SSN_ANSI   0x01U

/* GTT */
#define SCCP_CPA_GTTI_NONE      (0x00U)

/* CCITT translation types */
#define SCCP_CPA_GTTI_NATURE        (0x04U)
#define SCCP_CPA_GTTI_TRANS_CCITT   (0x08U)
#define SCCP_CPA_GTTI_TNE_CCITT     (0x0CU)
#define SCCP_CPA_GTTI_ALL           (0x10U)

/* ANSI translation types */
#define SCCP_CPA_GTTI_TNE_ANSI      (0x04U)
#define SCCP_CPA_GTTI_TRANS_ANSI    (0x08U)

#define SCCP_CPA_GTTI_MASK          (0x1CU)

/* routing */
#define SCCP_CPA_ROUTE_GTTI         (0x00U)
#define SCCP_CPA_ROUTE_SSN          (0x40U)

#define SCCP_CPA_ROUTE_INT_CCITT    (0x80U)
#define SCCP_CPA_ROUTE_NAT_CCITT    (0x00U)

#define SCCP_CPA_ROUTE_NAT_ANSI     (0x80U)
#define SCCP_CPA_ROUTE_INT_ANSI     (0x00U)

/*
 * called, calling party address
 */
#define SCCP_MAX_ADDR_LEN       32
typedef struct
{
    ITS_USHORT      len;
    ITS_OCTET       data[SCCP_MAX_ADDR_LEN];
}
SCCP_ADDR;

/*
 * Long Data Parameter
 */
#define SCCP_LONG_DATA_MAX  3952
typedef struct
{
    ITS_USHORT      len;
    ITS_OCTET       data[SCCP_LONG_DATA_MAX];
}
SCCP_LONG_DATA;

/*
 * it is recommended that the user not use the following macros.
 * Use the functions SCCP_EncodeAddr() or SCCP_DecodeAddr() instead.
 */
#define SCCP_ITU_SET_PC(x,y) \
    ((x)[0] = (ITS_OCTET)((y) & 0xFFU), \
     (x)[1] = (ITS_OCTET)(((y) >> 8) & 0x3FU))

#define SCCP_ITU_GET_PC(x) \
    ((((x)[1] << 8) | ((x)[0])) & 0x3FFFU)

#define SCCP_ANSI_SET_PC(x,y) \
    ((x)[0] = (ITS_OCTET)((y) & 0xFFU), \
     (x)[1] = (ITS_OCTET)(((y) >> 8) & 0xFFU), \
     (x)[2] = (ITS_OCTET)(((y) >> 16) & 0xFFU))

#define SCCP_ANSI_GET_PC(x) \
    (((x)[2] << 16) | ((x)[1] << 8) | (x)[0])

#define SCCP_SET_SSN(x,y) \
    ((x)[0] = y)

/*
 * SSN values
 */
#define SCCP_SSN_NONE         0x00U
#define SCCP_SSN_SCCPMGMT     0x01U
#define SCCP_SSN_ISUP         0x03U
#define SCCP_SSN_OMAP         0x04U
#define SCCP_SSN_MAP          0x05U
#define SCCP_SSN_HLR          0x06U
#define SCCP_SSN_VLR          0x07U
#define SCCP_SSN_MSC          0x08U
#define SCCP_SSN_EIR          0x09U
#define SCCP_SSN_AUTH         0x0AU
#define SCCP_SSN_SMC          0x0BU
#define SCCP_SSN_BSAP         0xFAU /* Validate this */

#define SCCP_MAX_SSN          (0xFFU)

/*
 * GTT number encoding
 */
#define SCCP_GTT_ENC_UNKNOWN      0x00U
#define SCCP_GTT_ENC_BCD_ODD      0x01U
#define SCCP_GTT_ENC_BCD_EVEN     0x02U

/*
 * GTT numbering plans
 */
#define SCCP_GTT_NP_UNK              0x00U
#define SCCP_GTT_NP_ISDN             0x01U
#define SCCP_GTT_NP_TEL              0x02U
#define SCCP_GTT_NP_DATA             0x03U
#define SCCP_GTT_NP_TELEX            0x04U
#define SCCP_GTT_NP_MARITIME         0x05U
#define SCCP_GTT_NP_LANDMOB          0x06U
#define SCCP_GTT_NP_ISDNMOB          0x07U
#define SCCP_GTT_NP_NATIONAL         0x08U
#define SCCP_GTT_NP_PRIVATE          0x09U
#define SCCP_GTT_NP_EXT              0x0FU

/*
 * protocol class
 */
typedef struct
{
    ITS_OCTET   pclass;
}
SCCP_PROT_CLASS;

#define SCCP_PCLASS_0           (0x00U)
#define SCCP_PCLASS_1           (0x01U)
#define SCCP_PCLASS_2           (0x02U)
#define SCCP_PCLASS_3           (0x03U)

#define SCCP_PCLASS_MASK        SCCP_PCLASS_3

/*
 * QOS for SCCP
 */
#define SCCP_PCLASS_RET_ON_ERR  (0x80U)

/*
 * credit (window size)
 */
typedef struct
{
    ITS_OCTET   win_size;
}
SCCP_CREDIT;

/*
 * impotance
 */
typedef struct
{
    ITS_OCTET   importance;
}
SCCP_IMPORTANCE;

/*
 * segmenting/reassembling parameter
 */
typedef struct
{
    ITS_OCTET   seg_res;
}
SCCP_SEG_RES;
#define SCCP_SR_END_OF_DATA     (0x00U)
#define SCCP_SR_MORE_DATA       (0x01U)

/*
 * received sequence number
 */
typedef struct
{
    ITS_OCTET   rsn;
}
SCCP_RSN;

/*
 * sequencing/segmentation
 */
typedef struct
{
    ITS_OCTET   tsn;
    ITS_OCTET   rsn;
}
SCCP_SEQ_SEG;

/*
 * release cause
 */
typedef struct
{
    ITS_OCTET   cause;
}
SCCP_REL_CAUSE;
#define SCCP_RLC_END_USER_ORG       (0x00U)
#define SCCP_RLC_END_USER_BUSY      (0x01U)
#define SCCP_RLC_END_USER_FAIL      (0x02U)
#define SCCP_RLC_SCCP_ORG           (0x03U)
#define SCCP_RLC_RPC_ERROR          (0x04U)
#define SCCP_RLC_INCONSISTENT_DATA  (0x05U)
#define SCCP_RLC_ACCESS_FAIL        (0x06U)
#define SCCP_RLC_ACCESS_CONG        (0x07U)
#define SCCP_RLC_SUBSYS_FAIL        (0x08U)
#define SCCP_RLC_SUBSYS_CONG        (0x09U)
#define SCCP_RLC_NETWORK_FAIL       (0x0AU)
#define SCCP_RLC_NETWORK_CONG       (0x0BU)
#define SCCP_RLC_RESET_EXPIRY       (0x0CU)
#define SCCP_RLC_INACT_EXPIRY       (0x0DU)
#define SCCP_RLC_NOT_OBTAINABLE     (0x0EU)
#define SCCP_RLC_UNQUAL             (0x0FU)

/*
 * return cause
 */
typedef struct
{
    ITS_OCTET   cause;
}
SCCP_RET_CAUSE;
#define SCCP_RET_NO_TRANS_ADDR_NAT  (0x00U)
#define SCCP_RET_NO_TRANS_THIS_ADDR (0x01U)
#define SCCP_RET_SUBSYS_CONG        (0x02U)
#define SCCP_RET_SUBSYS_FAIL        (0x03U)
#define SCCP_RET_UNEQUIPPED_USER    (0x04U)
#define SCCP_RET_NETWORK_FAIL       (0x05U)
#define SCCP_RET_NETWORK_CONG       (0x06U)
#define SCCP_RET_UNQUAL             (0x07U)
#define SCCP_RET_HOP_COUNT_EXCEEDED (0x08U)

/*
 * reset cause
 */
typedef struct
{
    ITS_OCTET   cause;
}
SCCP_RES_CAUSE;
#define SCCP_RES_END_USER_ORG       (0x00U)
#define SCCP_RES_SCCP_ORG           (0x01U)
#define SCCP_RES_OUT_OF_ORDER_S     (0x02U)
#define SCCP_RES_OUT_OF_ORDER_R     (0x03U)
#define SCCP_RES_RPC_OUT_WINDOW     (0x04U)
#define SCCP_RES_RPC_PS_AFTER_INIT  (0x05U)
#define SCCP_RES_RPC_GENERAL        (0x06U)
#define SCCP_RES_NETWORK_OP         (0x07U)
#define SCCP_RES_ACCESS_OP          (0x08U)
#define SCCP_RES_NETWORK_CONG       (0x09U)
#define SCCP_RES_NOT_OBTAINABLE     (0x0AU)
#define SCCP_RES_UNQUAL             (0x0BU)

/*
 * error cause
 */
typedef struct
{
    ITS_OCTET   cause;
}
SCCP_ERR_CAUSE;
#define SCCP_ERR_LRN_MISS_DRN       (0x00U)
#define SCCP_ERR_BAD_LRN            (0x01U)
#define SCCP_ERR_PC_MISMATCH        (0x02U)
#define SCCP_ERR_SCLASS_MIS         (0x03U)
#define SCCP_ERR_UNQUAL             (0x04U)

/*
 * refusal cause
 */
typedef struct
{
    ITS_OCTET   cause;
}
SCCP_REF_CAUSE;
#define SCCP_REF_END_USER_ORG       (0x00U)
#define SCCP_REF_END_USER_CONG      (0x01U)
#define SCCP_REF_END_USER_FAIL      (0x02U)
#define SCCP_REF_SCCP_ORG           (0x03U)
#define SCCP_REF_DEST_UKNOWN        (0x04U)
#define SCCP_REF_DEST_UNAVAIL       (0x05U)
#define SCCP_REF_QOS_NEVER_AVAIL    (0x06U)
#define SCCP_REF_QOS_UNAVAIL_NOW    (0x07U)
#define SCCP_REF_ACCESS_FAIL        (0x08U)
#define SCCP_REF_ACCESS_CONG        (0x09U)
#define SCCP_REF_SUBSYS_FAIL        (0x0AU)
#define SCCP_REF_SUBSYS_CONG        (0x0BU)
#define SCCP_REF_CONN_EXPIRY        (0x0CU)
#define SCCP_REF_BAD_USER_DATA      (0x0DU)
#define SCCP_REF_NOT_OBTAINABLE     (0x0EU)
#define SCCP_REF_UNQUAL             (0x0FU)

/*
 * data
 */
#define SCCP_MAX_DATA   254
typedef struct
{
    ITS_OCTET   data[SCCP_MAX_DATA];
}
SCCP_DATA;

/*
 * segmentation. ITU only.
 */
typedef struct
{
    ITS_OCTET       flags;
    SCCP_REF_NUM    localRef;
}
SCCP_SEGMENTATION;

#define SCCP_SEG_IS_FIRST       (0x80U)
#define SCCP_SEG_RETAIN_SEQ     (0x40U)
#define SCCP_SEG_REMNANT_MASK   (0x0FU)

/*
 * hop counter
 */
typedef struct
{
    ITS_OCTET   count;
}
SCCP_HOP_COUNT;

/*
 * SCMG messages
 */
typedef struct
{
    ITS_OCTET               type;
    ITS_OCTET               ssn;
    MTP3_POINT_CODE_ANSI    pointCode;
    ITS_OCTET               multiplicity;
}
SCCP_SCMG_ANSI;
typedef struct
{
    ITS_OCTET               type;
    ITS_OCTET               ssn;
    MTP3_POINT_CODE_CCITT   pointCode;
    ITS_OCTET               multiplicity;
}
SCCP_SCMG_CCITT;

/* types */
#define SCCP_SCMG_SS_ALLOWED       (0x01U)
#define SCCP_SCMG_SS_PROHIBIT      (0x02U)
#define SCCP_SCMG_SS_STATUS_TEST   (0x03U)
#define SCCP_SCMG_SS_OOS_REQ       (0x04U)
#define SCCP_SCMG_SS_OOS_GRANT     (0x05U)
#define SCCP_SCMG_SS_BACKUP_ROUTE  (0xFDU)
#define SCCP_SCMG_SS_NORMAL_ROUTE  (0xFEU)
#define SCCP_SCMG_SS_ROUTE_STATUS  (0xFFU)

/* IntelliSS7 defined */
#define SCCP_SCMG_SS_UIS           (0xF0U)
#define SCCP_SCMG_SS_UOS           (0xF1U)
#define SCCP_SCMG_SS_CONG          (0xF2U)

/* multiplicity */
#define SCCP_SCMG_SMI_UNKNOWN      (0x00U)
#define SCCP_SCMG_SMI_SOLO         (0x01U)
#define SCCP_SCMG_SMI_DUP          (0x02U)
#define SCCP_SCMG_SMI_DENIED       (0x10U)

/*
 * SCCP IES
 */
typedef struct
{
    ITS_OCTET   param_id;
    ITS_OCTET   param_length;
    union
    {
        MTP3_HEADER         routingLabel;
        SCCP_REF_NUM        destinationLocalReference;
        SCCP_REF_NUM        sourceLocalReference;
        SCCP_CREDIT         credit;
        SCCP_ADDR           calledPartyAddr;
        SCCP_ADDR           callingPartyAddr;
        SCCP_PROT_CLASS     protocolClass;
        SCCP_SEG_RES        segmentingReassembly;
        SCCP_SEQ_SEG        sequenceSegment;
        SCCP_RSN            receivedSequenceNumber;
        SCCP_REL_CAUSE      releaseCause;
        SCCP_RET_CAUSE      returnCause;
        SCCP_RES_CAUSE      resetCause;
        SCCP_ERR_CAUSE      errorCause;
        SCCP_REF_CAUSE      refusalCause;
        SCCP_DATA           userData;
        SCCP_HOP_COUNT      hopCount;
        SCCP_SCMG_ANSI      managementMessageANSI;
        SCCP_SCMG_CCITT     managementMessageCCITT;
        SCCP_LONG_DATA      longData;
        SCCP_IMPORTANCE     importance;
        SCCP_SEGMENTATION   segmentation;
    }
    param_data;
}
ITS_SCCP_IE;

/*
 * maximum number of SCCP IEs that can appear in an SCCP PDU
 */
#define ITS_MAX_SCCP_IES   32

/*
 * message types and data
 */
#define SCCP_MSG_TYPE(ev)   ((ev)->data[0])
#define SCCP_MSG_DATA(ev)   ((ev)->data[1 + sizeof(ITS_USHORT)])

/*
 * SCCP PDU descriptor
 */
typedef struct
{
    ITS_OCTET*  mArgs;
    int         nmArgs;
    ITS_OCTET*  vArgs;
    int         nvArgs;
    ITS_OCTET*  oArgs;
    int         noArgs;
}
SCCP_MSG_DESC;

/*
 * Global title callback data
 *
 * Semantics of the callback are as follows:
 *  o user indicates successful translation by setting
 *    transSuccess to ITS_TRUE
 *  o addrInd contains the 4 bit GTT mask.  Mask must
 *    be right shifted, or use the GTT mask values
 *    defined above.
 *  o gttInfo is a byte pointer, gttLen bytes long,
 *    pointing to the location of the GTT information.
 *  o user must build a valid SCCP address into the
 *    translation SCCP_ADDR.  User is encouraged to
 *    use SCCP_EncodeAddr() for this.
 *  o If the translated address does not include a new
 *    point code, the user MUST fill in the dpc field.
 *    If a point code is found in the translated address,
 *    the message will be forwarded to that DPC (overrides
 *    the value in the dpc member).  If the translated address
 *    does NOT contain a point code, the dpc member must
 *    contain a valid value.
 */
typedef struct
{
    ITS_BOOLEAN transSuccess;   /* result of translation */
    SCCP_ADDR   *translation;   /* translated addr goes here */
    void        *mtp3;          /* original routing label (type MTP3_HEADER) */
    ITS_UINT    dpc;            /* new destination point code here.
                                 * can be the same as the current pc */
    ITS_OCTET   addrInd;        /* from original addr - do not modify */
    ITS_OCTET   ssn;            /* from original addr - do not modify */
    ITS_USHORT  gttLen;         /* from original addr - do not modify */
    ITS_UINT    pc;             /* from original addr - do not modify */
    ITS_OCTET   *gttInfo;       /* from original addr - do not modify */
    ITS_SCCP_IE *ies;           /* from original message - do not modify */
    int         ieCount;        /* from original message - do not modify */
}
SCCP_CALLBACK_DATA;

#endif /* _ITS_SCCP_CMN_H_ */

