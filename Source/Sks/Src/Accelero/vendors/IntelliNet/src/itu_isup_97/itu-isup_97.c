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
 * ID: $Id: itu-isup_97.c,v 1.1.1.1 2007-10-08 11:12:19 bsccs2 Exp $:
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:55  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:12  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:01  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:54:12  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.2.38.2  2004/12/07 11:06:36  mmanikandan
 * LOG: Windows Compilation support testing bugs.
 * LOG:
 * LOG: Revision 7.2.2.2.38.1  2004/12/06 13:46:38  mmanikandan
 * LOG: Windows Compilation Support
 * LOG:
 * LOG: Revision 7.2.2.2  2003/07/30 04:39:19  sjaddu
 * LOG: LOP msg is moved to IntelliSS7/ISUP dir.
 * LOG:
 * LOG: Revision 7.2.2.1  2003/05/07 11:05:31  ssingh
 * LOG: Latest Changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.2  2003/04/22 09:04:18  akumar
 * LOG: Replaced Number of CICs Magic Number with meaningful MACRO.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:31  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.2  2003/02/06 12:52:28  akumar
 * LOG: First CIC in the circuit group changed to 1 in the ClassRec
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.8  2002/08/15 20:26:11  mmiers
 * LOG: Warning/error removal
 * LOG:
 * LOG: Revision 1.7  2002/08/01 15:57:50  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.6.2.2  2002/07/10 19:34:56  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 1.6.2.1  2002/07/06 20:06:42  hbalimid
 * LOG: Fixed all warnings.
 * LOG:
 * LOG: Revision 1.6  2002/06/28 16:38:24  hbalimid
 * LOG: Message Description taken care of by VFRAME.
 * LOG:
 * LOG: Revision 1.5  2002/06/22 03:14:50  hbalimid
 * LOG: Request & Indications for LOP Message
 * LOG:
 * LOG: Revision 1.4  2002/06/19 15:52:00  hbalimid
 * LOG: Accomodated Msg Procs for LOP in all state machines
 * LOG:
 * LOG: Revision 1.3  2002/06/18 20:33:32  hbalimid
 * LOG: ITU97 specific message set complete.
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:50:06  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/05/14 18:00:07  hbalimid
 * LOG: Inheritance from 93 in place
 * LOG: ACM support for 97 completed
 * LOG::
 *
 *****************************************************************************/

#include <its.h>

#undef CCITT
#undef ANSI
#define CCITT

#include <itu/isup_97.h>

#include "itu-isup_97_intern.h"

/*
 * ADDRESS COMPLETE (ACM)
 */
static ITS_OCTET    acmMArgs[] =
{
    ISUP_PRM_BKWD_CALL_INDICATORS
};

static ITS_OCTET    acmOArgs[] =
{
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_CALL_DIVERSION_INFO,
    ISUP_PRM_ECHO_CTRL_INFO,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CAUSE_INDICATORS,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,

    /* ITU97 Specific */
    ISUP_PRM_CONF_TREAT_INDICATORS,
    ISUP_PRM_UID_ACTION_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC ITU97_ISUP_ACM_Desc =
{
    ITS_TRUE, /* has EOP */
    acmMArgs, /* Mandatory Fixed */
    sizeof(acmMArgs),
    NULL,     /* Mandatory Variable */
    0,
    acmOArgs, /* Optional */
    sizeof(acmOArgs)
};

/*
 * ANSWER (ANM)
 */
static ITS_OCTET anmOArgs[] =
{
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_CALL_HISTORY_INFO,
    ISUP_PRM_CONNECTED_NUM,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,
    ISUP_PRM_ECHO_CTRL_INFO,
    ISUP_PRM_GENERIC_NUM,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BKWD_CALL_INDICATORS,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,

    /* ITU97 Specific */
    ISUP_PRM_BACKWARD_GVNS,
    ISUP_PRM_DISPLAY_INFORMATION
};

SS7DLLAPI ISUP_MSG_DESC ITU97_ISUP_ANM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    anmOArgs, sizeof(anmOArgs)
};

/*
 * CALL PROGRESS (CPG)
 */
static ITS_OCTET cpgMArgs[] =
{
    ISUP_PRM_EVENT_INFO
};

static ITS_OCTET cpgOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BKWD_CALL_INDICATORS,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CAUSE_INDICATORS,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_CALL_DIVERSION_INFO,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,

    /* ITU97 Specific */
    ISUP_PRM_CALL_TRANSFER_NUMBER,
    ISUP_PRM_ECHO_CTRL_INFO,
    ISUP_PRM_CONNECTED_NUM,
    ISUP_PRM_BACKWARD_GVNS,
    ISUP_PRM_GENERIC_NUM,
    ISUP_PRM_CALL_HISTORY_INFO,
    ISUP_PRM_CONF_TREAT_INDICATORS,
    ISUP_PRM_UID_ACTION_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_CPG_Desc =
{
    ITS_TRUE,
    cpgMArgs, sizeof(cpgMArgs),
    NULL, 0,
    cpgOArgs, sizeof(cpgOArgs),
};


/*
 * CONNECT (CON)
 */
static ITS_OCTET    conMArgs[] =
{
    ISUP_PRM_BKWD_CALL_INDICATORS
};

static ITS_OCTET    conOArgs[] =
{
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,
    ISUP_PRM_CONNECTED_NUM,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_ECHO_CTRL_INFO,
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_CALL_HISTORY_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    /* ISUP_PRM_REDIRECTION_NUM, - only in ITU93 */
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_GENERIC_NUM,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,

    /* ITU97 Specific */
    ISUP_PRM_BACKWARD_GVNS,
    ISUP_PRM_CONF_TREAT_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_CON_Desc =
{
    ITS_TRUE,
    conMArgs, sizeof(conMArgs),
    NULL, 0,
    conOArgs, sizeof(conOArgs)
};

/*
 * INITIAL ADDRESS (IAM)
 */
static ITS_OCTET iamMArgs[] =
{
    ISUP_PRM_NATURE_CONN_INDICATORS,
    ISUP_PRM_FWD_CALL_INDICATORS,
    ISUP_PRM_CALLING_PARTY_CATEGORY,
    ISUP_PRM_TX_MEDIUM_REQMNT
};
static ITS_OCTET iamVArgs[] =
{
    ISUP_PRM_CALLED_PARTY_NUM
};
static ITS_OCTET iamOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CALLING_PARTY_NUM,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_GENERIC_DIGITS,
    ISUP_PRM_REDIRECTING_NUM,
    ISUP_PRM_REDIRECTION_INFO,
    ISUP_PRM_ORIG_CALLED_NUM,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TRANSIT_NTWK_SELECT,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_SERVICE_INFO,
    ISUP_PRM_OPT_FWD_CALL_INDICATORS,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE,
    ISUP_PRM_PROP_DELAY_COUNTER,
    ISUP_PRM_USER_SERVICE_INFO_PRIME,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_GENERIC_NUM,
    ISUP_PRM_ORIG_ISC_PC,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_GENERIC_REF,
    ISUP_PRM_MLPP_PRECEDENCE,
    ISUP_PRM_TX_MEDIUM_REQMNT_PRIME,
    ISUP_PRM_LOCATION_NUM,

    /* ITU97 Specific */
    ISUP_PRM_USER_TELESERVICE_INFO,
    ISUP_PRM_FORWARD_GVNS,
    ISUP_PRM_CCSS,
    ISUP_PRM_NETWORK_MANAGEMENT_CONTROLS,
    ISUP_PRM_CIRCUIT_ASSIGNMENT_MAP,
    ISUP_PRM_CORRELATION_ID,
    ISUP_PRM_CALL_DIV_TREAT_INDICATORS,
    ISUP_PRM_CALLED_IN_NUMBER,
    ISUP_PRM_CALL_OFF_TREAT_INDICATORS,
    ISUP_PRM_CONF_TREAT_INDICATORS,
    ISUP_PRM_SCF_ID,
    ISUP_PRM_UID_CAPABILITY_INDICATORS,
    ISUP_PRM_ECHO_CTRL_INFO,
    ISUP_PRM_HOP_COUNTER,
    ISUP_PRM_COLLECT_CALL_REQUEST
};
SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_IAM_Desc =
{
    ITS_TRUE,
    iamMArgs, sizeof(iamMArgs),
    iamVArgs, sizeof(iamVArgs),
    iamOArgs, sizeof(iamOArgs)
};


/*
 * RELEASE (REL)
 */
static ITS_OCTET relVArgs[] =
{
    ISUP_PRM_CAUSE_INDICATORS
};
static ITS_OCTET relOArgs[] =
{
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_REDIRECTION_INFO,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_SIGNALLING_POINT_CODE,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    /* ISUP_PRM_REDIRECTION_NUM_RESTRICT, - only in ITU93 */
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_AUTO_CONGEST_LEVEL,

    /* ITU97 Specific */
    ISUP_PRM_DISPLAY_INFORMATION,
    ISUP_PRM_REMOTE_OPS
};

SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_REL_Desc =
{
    ITS_TRUE,
    NULL, 0,
    relVArgs, sizeof(relVArgs),
    relOArgs, sizeof(relOArgs)
};


/*
 * FACILITY (FAC)
 */
static ITS_OCTET facOArgs[] =
{
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_SERVICE_ACTIVATION,

    /* ITU97 Specific */
    ISUP_PRM_CALL_TRANSFER_NUMBER,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_GENERIC_NOTIFICATION
};

SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_FAC_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    facOArgs, sizeof(facOArgs)
};

/*
 * NETWORK RESOURCE MANAGEMENT (NRM)
 */
static ITS_OCTET nrmOArgs[] =
{
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_ECHO_CTRL_INFO
    /* ISUP_PRM_TX_MEDIUM_USED - not in ITU97 */
};

SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_NRM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    nrmOArgs, sizeof(nrmOArgs)
};


/*
 * IDENTIFICATION RESPONSE (IDR)
 */
static ITS_OCTET idrOArgs[] =
{
    ISUP_PRM_MCID_REQ_INDICATOR,
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_CALLING_PARTY_NUM,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_GENERIC_NUM,

    /* ITU97 Specific */
    ISUP_PRM_CHARGED_PARTY_IDENTIFICATION
};

SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_IDR_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    idrOArgs, sizeof(idrOArgs)
};


/*
 * LOOP PREVENTION (LOP)
 * This message is specific to ITU97 variant
 */
static ITS_OCTET lopOArgs[] =
{
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_CALL_TRANSFER_REFERENCE,
    ISUP_PRM_LOOP_PREVENTION_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_LOP_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    lopOArgs, sizeof(lopOArgs)
};

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the class record
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *

 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{

    ITS_CLASS_SUPERCLASS(objClass) = isupITU93_Class;

    ISUP_DEBUG(("ClassInitialize: ITU97...\n"));

    /* This inheritacnce is to be refined further
     * currently using known methods
     * more work...later
     */

    /* ITU 93 part */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[0] = NULL;
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[1] = &ISUP_IAM_Desc;     /* 0x01 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[2] = &ISUP_SAM_Desc;     /* 0x02 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[3] = &ISUP_INR_Desc;     /* 0x03 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[4] = &ISUP_INF_Desc;     /* 0x04 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[5] = &ISUP_COT_Desc;     /* 0x05 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[6] = &ISUP_ACM_Desc;     /* 0x06 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[7] = &ISUP_CON_Desc;     /* 0x07 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[8] = &ISUP_FOT_Desc;     /* 0x08 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[9] = &ISUP_ANM_Desc;     /* 0x09 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[10] = NULL;               /* 0x0A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[11] = NULL;               /* 0x0B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[12] = &ISUP_REL_Desc;     /* 0x0C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[13] = &ISUP_SUS_Desc;     /* 0x0D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[14] = &ISUP_RES_Desc;     /* 0x0E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[15] = NULL;               /* 0x0F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[16] = &ISUP_RLC_Desc;     /* 0x10 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[17] = &ISUP_CCR_Desc;     /* 0x11 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[18] = &ISUP_RSC_Desc;     /* 0x12 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[19] = &ISUP_BLO_Desc;     /* 0x13 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[20] = &ISUP_UBL_Desc;     /* 0x14 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[21] = &ISUP_BLA_Desc;     /* 0x15 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[22] = &ISUP_UBA_Desc;     /* 0x16 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[23] = &ISUP_GRS_Desc;     /* 0x17 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[24] = &ISUP_CGB_Desc;     /* 0x18 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[25] = &ISUP_CGU_Desc;     /* 0x19 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[26] = &ISUP_CGBA_Desc;    /* 0x1A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[27] = &ISUP_CGUA_Desc;    /* 0x1B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[28] = NULL;               /* 0x1C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[29] = NULL;               /* 0x1D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[30] = NULL;               /* 0x1E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[31] = &ISUP_FAR_Desc;     /* 0x1F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[32] = &ISUP_FAA_Desc;     /* 0x20 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[33] = &ISUP_FRJ_Desc;     /* 0x21 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[34] = NULL;               /* 0x22 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[35] = NULL;               /* 0x23 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[36] = &ISUP_LPA_Desc;     /* 0x24 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[37] = NULL;               /* 0x25 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[38] = NULL;               /* 0x26 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[39] = NULL;               /* 0x27 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[40] = &ISUP_PAM_Desc;     /* 0x28 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[41] = &ISUP_GRA_Desc;     /* 0x29 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[42] = &ISUP_CQM_Desc;     /* 0x2A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[43] = &ISUP_CQR_Desc;     /* 0x2B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[44] = &ISUP_CPG_Desc;     /* 0x2C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[45] = &ISUP_USR_Desc;     /* 0x2D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[46] = &ISUP_UCIC_Desc;    /* 0x2E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[47] = &ISUP_CFN_Desc;     /* 0x2F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[48] = &ISUP_OLM_Desc;     /* 0x30 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[49] = NULL;               /* 0x31 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[50] = &ISUP_NRM_Desc;     /* 0x32 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[51] = &ISUP_FAC_Desc;     /* 0x33 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[52] = &ISUP_UPT_Desc;     /* 0x34 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[53] = &ISUP_UPA_Desc;     /* 0x35 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[54] = &ISUP_IDR_Desc;     /* 0x36 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[55] = &ISUP_IRS_Desc;     /* 0x37 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[56] = &ISUP_SGM_Desc;     /* 0x38 */

    /* Begin - ITU 97 over-riding 93 part */

    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[6] = &ITU97_ISUP_ACM_Desc; /* 0x06 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[9] = &ITU97_ISUP_ANM_Desc; /* 0x09 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[44] = &ITU97_ISUP_CPG_Desc; /* 0x2C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[7] = &ITU97_ISUP_CON_Desc; /* 0x07 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[1] = &ITU97_ISUP_IAM_Desc; /* 0x01 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[12] = &ITU97_ISUP_REL_Desc; /* 0x0C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[50] = &ITU97_ISUP_NRM_Desc; /* 0x32 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[51] = &ITU97_ISUP_FAC_Desc; /* 0x33 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[54] = &ITU97_ISUP_IDR_Desc; /* 0x36 */

    /* End - ITU 97 over-riding 93 part */

    /* Additional Message in ITU97 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[64] = &ITU97_ISUP_LOP_Desc; /* 0x40 */

    return (ITS_SUCCESS);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the class record
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
    ISUP_DEBUG(("(%s) ClassDestroy: ITU97...\n",__FILE__));

    return;
}

/*.implementation:static
****************************************************************************
 *  Purpose:
 *      Destroy the class record.
 *
 *  Input Parameters:
 *      classRec - the class to destroy
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ITU_ISUP97_ClassPartDestroy(ITS_Class classRec)
{
    ISUP_DEBUG(("(%s) ITU_ISUP97_ClassPartDestroy: ITU97...\n",__FILE__));

    /*  Call HASH_DeleteTable for function pointers */
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to initialize the variant class-specific
 *      Timeout Handler function addresses.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      Within this function, ONLY those addresses need to be inserted in
 *      Hash Table, which are either new or need to overwrite function
 *      addresses laid down by the base class.
 *
 *  See Also:
 ****************************************************************************/
int
ITU_ISUP97_InitTimeoutProcs(ITS_Class classRec)
{
#if 0
    HASH_Table TimeoutProcTable = NULL;
#endif

    ISUP_DEBUG(("ITU_ISUP97_InitTimeoutProcs: ITU97...\n"));

#if 0
    if ((TimeoutProcTable = ISUP_CLASS_HASH_TIMEOUT_PROCS(classRec)) == NULL)
    {
        ISUP_DEBUG(("TimeoutProcTable access error: exiting"));
        return ITS_EINITFAIL;
    }

    /* Try to add new function pointer in the HashTable, if any */

    /* Try to modify existing pointers inherited from BaseClass, if any
     * needed */
#endif

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to store the address of a message Handling
 *      function in the HashTable.
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      msg - particular message to be handled.
 *      HashTable - placeholder for Message Handling function addresses
 *      State - state where the msg was received.
 *      func - function address to be inserted in the Table.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This function may be recursively called during initialization of the
 *      variant. For each msg-state combination which requires a variant
 *      specific handling, this function is called to store the address of
 *      the variant specific Message Handler function in the Hash Table.
 *
 *  See Also:
 ****************************************************************************/
static int
ITU_ISUP97_SetMsgProc(ITS_Class V_Class, HASH_Table MsgProcTable,
                 ITS_OCTET msgType, ITS_ISUP_STATE state,
                 __ISUP_MsgHandlerProc func)
{
    ISUP_DEBUG(("ITU_ISUP97_SetMsgProc: mtype %x, state %x, func %x\n",
                                             msgType, state, func));

    return ISUP_SET_MSG_PROC(V_Class) ((ITS_Class)V_Class, MsgProcTable,
                                        msgType, state, func);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to initialize the variant class-specific
 *      Message Handler function addresses.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      Within this function, ONLY those addresses need to be inserted in
 *      Hash Table, which are either new or need to overwrite function
 *      addresses laid down by the base class.
 *
 *  See Also:
 ****************************************************************************/
static int
ITU_ISUP97_InitMsgProcs(ITS_Class classRec)
{
    ITS_USHORT state = 0;
    ITS_USHORT key = 0;
    ITS_USHORT msg = ISUP_MSG_LOP;
    HASH_Table MsgProcTable = NULL;
    __ISUP_MsgHandlerProc func = NULL;

    ISUP_DEBUG(("(%s) ITU_ISUP97_InitMsgProcs: ITU97...\n",__FILE__));

    if ((MsgProcTable = ISUP_CLASS_HASH_MSG_PROCS(isupITU93_Class)) == NULL)
    {
        ISUP_DEBUG(("MsgProcTable access error: exiting"));
        return ITS_EINITFAIL;
    }

    for (state = 0; state < ISUP_NB_STATES; state++)
    {
        func = __ISUP_GetMsgHandler_ITU97((ITS_OCTET)msg, state);

        if (ITU_ISUP97_SetMsgProc(classRec, MsgProcTable,
                                 (ITS_OCTET)msg, state, func) != ITS_SUCCESS)
        {
            ISUP_DEBUG(("\n could not add function entry in HASH_Table:"
                        " msg = %x, state = %x: key %x\n",
                        msg, state, key));

            return ITS_ENOMEM;
        }
        else
        {
            func = NULL;
            key = 0;
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the variant class-specific functionality.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      If the variant class does not have any specific handling of the
 *      function, then it will use (inherit) the function definition in the
 *      generic variant class (ITU93). Note that this is because initialization
 *      of the ITU93 class (base class) has been already done before calling
 *      this function.
 *
 *  See Also:
 ****************************************************************************/
static int
ITU_ISUP97_ClassPartInitialize(ITS_Class classRec)
{
    ISUP_DEBUG(("ITU_ISUP97_ClassPartInitialize: ITU97...\n"));

    if (ITU_ISUP97_InitMsgProcs(ITS_CLASS_SUPERCLASS(classRec)) != ITS_SUCCESS)
    {
        return ITS_EINITFAIL;
    }

    if (ITU_ISUP97_InitTimeoutProcs(classRec) != ITS_SUCCESS)
    {
        return ITS_EINITFAIL;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the variant-specific processing of a particular
 *      message.
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      event - a pointer to ITS_EVENT structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
ITU_ISUP97_VARIANT_SpecificMsg(ITS_Class V_class, ITS_EVENT* event)
{
    ISUP_DEBUG(("ITU_ISUP97_VARIANT_SpecificMsg: ITU97...\n"));
    return 0;
}



/*
 * the Variant Info. record
 */
ISUP_VariantInfo isupITU97_Info = 
{
    {
        /* Bitwise table for msgs. supported in the variant. */
        TABLE_MSG_SUPPORTED_ROW0_ITU93,
        TABLE_MSG_SUPPORTED_ROW1_ITU93,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROW3_ITU93,
        TABLE_MSG_SUPPORTED_ROW4_ITU93,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROW7_ITU93,
        TABLE_MSG_SUPPORTED_ROW8_ITU_ISUP97
    },
    {
        /* Timers: CSC timers - default handling stack; others - default app. */
        { ISUP_TMR_HNDL_STACK  , 15  },  /* Timer T1.  15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 180 },  /* Timer T2.  3 mins.              */
        { ISUP_TMR_HNDL_STACK, 120 },  /* Timer T3.  2 mins.              */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T4.  5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T5.  5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T6.  per Q.118            */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer T7.  20-30 sec.           */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T8.  10-15 sec.           */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T9.  per Q.118            */
        { ISUP_TMR_HNDL_STACK, 4   },  /* Timer T10. 4-6 sec.             */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T11. 15-20 sec.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T12. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T13. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T14. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T15. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T16. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T17. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T18. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T19. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T20. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T21. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T22. 15-60 sec.           */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T23. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 1   },  /* Timer T24. < 2 sec.             */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T25. 1-10 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T26. 1-3 mins.            */
        { ISUP_TMR_HNDL_STACK, 240 },  /* Timer T27. 4 mins.              */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T28. 10 sec.              */
        { ISUP_TMR_HNDL_STACK, 1   },  /* Timer T29. 300-600 ms. (FIXME)  */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T30. 5-10 sec.            */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T31. > 6 mins.            */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T32. 3-5 sec.             */
        { ISUP_TMR_HNDL_STACK, 12  },  /* Timer T33. 12-15 sec.           */
        { ISUP_TMR_HNDL_STACK, 4   },  /* Timer T34. 2-4 sec.             */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T35. 15-20 sec.           */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T36. 10-15 sec.           */
        { ISUP_TMR_HNDL_STACK, 4   },  /* Timer T37. 2-4 sec.             */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T38. per Q.118            */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T39. per Q.730            */
    },
    {
        NULL /* Array of msg. descriptors : updated within ClassInitialize() */
    },
    NULL,   /* Hash Table for message procs. : Table ptr. updated after init.*/
    NULL,   /* Hash Table for timeout procs. : Table ptr. updated after init.*/
    1,      /* First CIC in Ckgp. */
    ISUP_ITU_MAX_CICS_IN_GP,     /* Number of CICs in Circuit Group */
    0xFFU,  /* supportMsgCompInfo */
    0xFFU,  /* supportParamCompInfo */
    0x01U   /* exchangeType */
};



/*
 * the class record
 */
SS7DLLAPI ITU_ISUP97_VARIANT_ClassRec isupITU97_ClassRec =
{
    /* core part */
    {
#if defined(WIN32)
		NULL,
#else
        (ITS_Class)&isupITU93_ClassRec, /* superclass is ITU93 */
#endif
        sizeof(ISUP_VariantInfo),       /* sizeof instance  ??? */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial refCount */
        ITU_ISUP97_VARIANT_CLASS_NAME,  /* class name */
        ClassInitialize,                /* class initialize ??? inherit */
        ClassDestroy,                   /* class destroy ??? inherit */
        ITU_ISUP97_ClassPartInitialize, /* class initialize part */
        ITU_ISUP97_ClassPartDestroy,    /* class destroy part */
        NULL,                           /* instantiate */
        NULL,                           /* destroy */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        ITS_INST_HASH_INHERIT,          /* inherit hash */
        NULL                            /* no extension of interest */
    },
    /* VARIANT part */
    {
        &isupITU97_Info,                  /* info */
        ISUP_DECODE_MSG_INHERIT,          /* inherit from base ISUP VARIANT */
        ISUP_ENCODE_MSG_INHERIT,          /* inherit from base ISUP VARIANT */
        ISUP_COMPUTE_MSIZE_INHERIT,       /* inherit from base ISUP VARIANT */
        ISUP_HANDLE_UNREC_MSG_INHERIT,    /* inherit from base ISUP VARIANT */
        ISUP_GET_MSG_PROC_INHERIT,        /* inherit from base ISUP VARIANT */
        ISUP_GET_TIMEOUT_PROC_INHERIT,    /* inherit from base ISUP VARIANT */

        /* Private Functions for Class Init. : Users stay out */

        ISUP_INIT_MSG_PROCS_INHERIT,      /* inherit from base ISUP VARIANT */
        ISUP_INIT_TIMEOUT_PROCS_INHERIT,  /* inherit from base ISUP VARIANT */
        ISUP_SET_MSG_PROC_INHERIT,        /* inherit from base ISUP VARIANT */
        ISUP_SET_TIMEOUT_PROC_INHERIT     /* inherit from base ISUP VARIANT */
    },
    {
        ITU_ISUP97_VARIANT_SpecificMsg /* Variant Specific processing of msgs */
    }

};

SS7DLLAPI ITS_Class isupITU97_Class = (ITS_Class)&isupITU97_ClassRec;
