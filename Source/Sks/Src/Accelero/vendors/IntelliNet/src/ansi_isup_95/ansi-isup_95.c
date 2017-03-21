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
 * ID: $Id: ansi-isup_95.c,v 1.1.1.1 2007-10-08 11:12:18 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:53  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:10  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:56  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:54:02  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.1.38.1  2004/12/06 13:39:22  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.3.2.1  2003/05/07 10:49:27  ssingh
 * LOG: Latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.2  2003/04/14 10:19:15  sjaddu
 * LOG: FAC message changes, SendFACRequet() is moved to isup.c
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:28  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.3  2003/01/22 14:55:02  vnitin
 * LOG: Tandem port for Ansi ISUP
 * LOG:
 * LOG: Revision 7.2  2002/11/22 15:03:05  ssingh
 * LOG: Added CQM message Desc as it got changed for ANSI95 variant.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/08/15 20:26:11  mmiers
 * LOG: Warning/error removal
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:49  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.6  2002/07/31 19:05:28  ssingh
 * LOG: IAM desc is updated for ANSI95.
 * LOG:
 * LOG: Revision 1.1.2.5  2002/07/06 06:12:53  hbalimid
 * LOG: Took care of all warnings.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/07/05 22:03:13  hbalimid
 * LOG: Default timer handling by STACK for all timers.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/04 23:31:42  hbalimid
 * LOG: Initialization with the correct super-class.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/03 18:19:13  hbalimid
 * LOG: variant record completed.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/02 19:57:37  hbalimid
 * LOG: ANSI95 specific message descriptions in place.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/02 02:13:55  hbalimid
 * LOG: Baseline for ISUP ANSI95.
 * LOG:
 *
 *****************************************************************************/

#include <its.h>

#undef ANSI
#undef CCITT
#define ANSI

#include <ansi/isup_95.h>

#include "ansi-isup_95_intern.h"

/* 
 * Description of ANSI95 messages that differ
 * from the ANSI GENERIC 92 variant
 * All other common messages will be inherited
 * as a part of the variant implementation.
 */

/*
 * ADDRESS COMPLETE MESSAGE (ACM)
 */

static ITS_OCTET    acmMArgs[] =
{
    ISUP_PRM_BKWD_CALL_INDICATORS
};
static ITS_OCTET    acmOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BUSINESS_GROUP,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CAUSE_INDICATORS,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_INFO_INDICATORS,
    ISUP_PRM_NTWK_TRANSPORT,
    ISUP_PRM_NOTIFICATION,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,
    ISUP_PRM_REDIRECTION_INFO,
    ISUP_PRM_REMOTE_OPERATIONS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TRANSMISSION_MEDIUM_USED,
    ISUP_PRM_USER_TO_USER_INDS,
    ISUP_PRM_USER_TO_USER_INFORM
};

SS7DLLAPI ISUP_MSG_DESC ANSI95_ISUP_ACM_Desc =
{
    ITS_TRUE,
    acmMArgs, sizeof(acmMArgs),
    NULL, 0,
    acmOArgs, sizeof(acmOArgs)
};


/*
 * ANSWER MESSAGE (ANM)
 */

static ITS_OCTET anmOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BKWD_CALL_INDICATORS,
    ISUP_PRM_BUSINESS_GROUP,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_INFO_INDICATORS,
    ISUP_PRM_NTWK_TRANSPORT,
    ISUP_PRM_NOTIFICATION,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,
    ISUP_PRM_REMOTE_OPERATIONS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TRANSMISSION_MEDIUM_USED,
    ISUP_PRM_USER_TO_USER_INDS,
    ISUP_PRM_USER_TO_USER_INFORM
};

SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_ANM_Desc =
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
    ISUP_PRM_BUSINESS_GROUP,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CAUSE_INDICATORS,
    ISUP_PRM_INFO_INDICATORS,
    ISUP_PRM_NTWK_TRANSPORT,
    ISUP_PRM_NOTIFICATION,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,
    ISUP_PRM_REMOTE_OPERATIONS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TRANSMISSION_MEDIUM_USED,
    ISUP_PRM_USER_TO_USER_INDS,
    ISUP_PRM_USER_TO_USER_INFORM
};

SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_CPG_Desc =
{
    ITS_TRUE,
    cpgMArgs, sizeof(cpgMArgs),
    NULL, 0,
    cpgOArgs, sizeof(cpgOArgs),
};

/*
 * INFORMATION (INF)
 */

static ITS_OCTET infMArgs[] =
{
    ISUP_PRM_INFO_INDICATORS
};
static ITS_OCTET infOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BUSINESS_GROUP,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CALLING_PARTY_NUM,
    ISUP_PRM_CALLING_PARTY_CATEGORY,
    ISUP_PRM_CHARGE_NUMBER,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_ORIG_LINE_INFO,
    ISUP_PRM_REDIRECTING_NUM,
    ISUP_PRM_REDIRECTION_INFO,
    ISUP_PRM_USER_TO_USER_INFORM
};

SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_INF_Desc =
{
    ITS_TRUE,
    infMArgs, sizeof(infMArgs),
    NULL, 0,
    infOArgs, sizeof(infOArgs)
};


/*
 * INITIAL ADDRESS (IAM)
 */

static ITS_OCTET iamMArgs[] =
{
    ISUP_PRM_NATURE_CONN_INDICATORS,
    ISUP_PRM_FWD_CALL_INDICATORS,
    ISUP_PRM_CALLING_PARTY_CATEGORY
};
static ITS_OCTET iamVArgs[] =
{
    ISUP_PRM_USER_SERVICE_INFO,
    ISUP_PRM_CALLED_PARTY_NUM
};
static ITS_OCTET iamOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BUSINESS_GROUP,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CALLING_PARTY_NUM,
    ISUP_PRM_CARRIER_ID,
    ISUP_PRM_CARRIER_SELECTION_INFO,
    ISUP_PRM_CHARGE_NUMBER,
    ISUP_PRM_CIRCUIT_ASSIGN_MAP,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_EGRESS_SERVICE,
    ISUP_PRM_GENERIC_ADDR,
    ISUP_PRM_GENERIC_DIGITS,
    ISUP_PRM_GENERIC_NAME,
    ISUP_PRM_HOP_CTR,
    ISUP_PRM_INFO_REQ_INDICATORS,
    ISUP_PRM_JURISDICTION,
    ISUP_PRM_NTWK_TRANSPORT,
    ISUP_PRM_OPERATOR_SERVICES_INFO,
    ISUP_PRM_ORIG_CALLED_NUM,
    ISUP_PRM_ORIG_LINE_INFO,
    ISUP_PRM_PRECEDENCE,
    ISUP_PRM_REDIRECTING_NUM,
    ISUP_PRM_REDIRECTION_INFO,
    ISUP_PRM_REMOTE_OPERATIONS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_SERVICE_CODE,
    ISUP_PRM_SPECIAL_PROCESS_REQUEST,
    ISUP_PRM_TRANSACTION_REQUEST,
    ISUP_PRM_TRANSIT_NTWK_SELECT,
    ISUP_PRM_USER_SERVICE_INFORM_PRIME,
    ISUP_PRM_USER_TO_USER_INFORM
};
SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_IAM_Desc =
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
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_AUTO_CONGEST_LEVEL,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CHARGE_NUMBER,
    ISUP_PRM_GENERIC_ADDR,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_USER_TO_USER_INFORM
};

SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_REL_Desc =
{
    ITS_TRUE,
    NULL, 0,
    relVArgs, sizeof(relVArgs),
    relOArgs, sizeof(relOArgs)
};

/*
 * CIRCUIT GROUP RESET (GRS)
 */

static ITS_OCTET grsVArgs[] =
{
    ISUP_PRM_RANGE_STATUS
};
static ITS_OCTET grsOArgs[] =
{
    ISUP_PRM_CIRCUIT_ASSIGN_MAP
};

SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_GRS_Desc =
{
    ITS_TRUE,
    NULL, 0,
    grsVArgs, sizeof(grsVArgs),
    grsOArgs, sizeof(grsOArgs)
};

/*
 * CIRCUIT QUERY (CQM)
 */

static ITS_OCTET cqmVArgs[] =
{
    ISUP_PRM_RANGE_STATUS
};

static ITS_OCTET cqmOArgs[] =
{
    ISUP_PRM_CIRCUIT_ASSIGN_MAP
};

SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_CQM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    cqmVArgs, sizeof(cqmVArgs),
    cqmOArgs, sizeof(cqmOArgs)
};

/*
 * CIRCUIT GROUP RESET ACKNOWLEDGEMENT (GRA)
 */

static ITS_OCTET graVArgs[] =
{
    ISUP_PRM_RANGE_STATUS
};
static ITS_OCTET graOArgs[] =
{
    ISUP_PRM_CIRCUIT_ASSIGN_MAP
};

SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_GRA_Desc =
{
    ITS_TRUE,
    NULL, 0,
    graVArgs, sizeof(graVArgs),
    graOArgs, sizeof(graOArgs)
};


/*
 * New Messages in the ANSI95 variant
 * Not present in ANSI GENERIC 92
 */

/*
 * FACILITY (FAC)
 */

static ITS_OCTET facOArgs[] =
{
    ISUP_PRM_REMOTE_OPERATIONS,
    ISUP_PRM_SERVICE_ACTIVATION
};

SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_FAC_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    facOArgs, sizeof(facOArgs)
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
    int msg = 0;

    /* get the super class */
    ITS_CLASS_SUPERCLASS(objClass) = isupANSI92_Class;

    ISUP_DEBUG(("ClassInitialize: Initializing class ANSI95...\n"));

    /*
     * ANSI92 part
     */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[0] = NULL;
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[1] = &ISUP_IAM_Desc;     /* 0x01 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[2] = NULL;               /* 0x02 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[3] = &ISUP_INR_Desc;     /* 0x03 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[4] = &ISUP_INF_Desc;     /* 0x04 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[5] = &ISUP_COT_Desc;     /* 0x05 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[6] = &ISUP_ACM_Desc;     /* 0x06 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[7] = NULL;               /* 0x07 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[8] = &ISUP_FOT_Desc;     /* 0x08 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[9] = &ISUP_ANM_Desc;     /* 0x09 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[10] = NULL;              /* 0x0A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[11] = NULL;              /* 0x0B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[12] = &ISUP_REL_Desc;    /* 0x0C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[13] = &ISUP_SUS_Desc;    /* 0x0D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[14] = &ISUP_RES_Desc;    /* 0x0E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[15] = NULL;              /* 0x0F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[16] = &ISUP_RLC_Desc;    /* 0x10 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[17] = &ISUP_CCR_Desc;    /* 0x11 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[18] = &ISUP_RSC_Desc;    /* 0x12 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[19] = &ISUP_BLO_Desc;    /* 0x13 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[20] = &ISUP_UBL_Desc;    /* 0x14 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[21] = &ISUP_BLA_Desc;    /* 0x15 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[22] = &ISUP_UBA_Desc;    /* 0x16 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[23] = &ISUP_GRS_Desc;    /* 0x17 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[24] = &ISUP_CGB_Desc;    /* 0x18 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[25] = &ISUP_CGU_Desc;    /* 0x19 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[26] = &ISUP_CGBA_Desc;   /* 0x1A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[27] = &ISUP_CGUA_Desc;   /* 0x1B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[28] = NULL;              /* 0x1C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[29] = NULL;              /* 0x1D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[30] = NULL;              /* 0x1E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[31] = NULL;              /* 0x1F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[32] = NULL;              /* 0x20 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[33] = NULL;              /* 0x21 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[34] = NULL;              /* 0x22 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[35] = NULL;              /* 0x23 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[36] = &ISUP_LPA_Desc;    /* 0x24 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[37] = NULL;              /* 0x25 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[38] = NULL;              /* 0x26 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[39] = NULL;              /* 0x27 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[40] = &ISUP_PAM_Desc;    /* 0x28 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[41] = &ISUP_GRA_Desc;    /* 0x29 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[42] = &ISUP_CQM_Desc;    /* 0x2A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[43] = &ISUP_CQR_Desc;    /* 0x2B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[44] = &ISUP_CPG_Desc;    /* 0x2C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[45] = NULL;              /* 0x2D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[46] = &ISUP_UCIC_Desc;   /* 0x2E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[47] = &ISUP_CFN_Desc;    /* 0x2F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[48] = NULL;              /* 0x30 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[49] = NULL;              /* 0x31 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[50] = NULL;              /* 0x32 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[51] = NULL;              /* 0x33 */

    /* No msg. codes from 52 through 232 for ANSI */
    for (msg = 52; msg < 233; msg++)
    {
        ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[msg] = NULL;    /* 0x34
                                                                       through
                                                                       0xE8 */
    }
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[233] = &ISUP_CRA_Desc;   /* 0xE9 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[234] = &ISUP_CRM_Desc;   /* 0xEA */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[235] = &ISUP_CVR_Desc;   /* 0xEB */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[236] = &ISUP_CVT_Desc;   /* 0xEC */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[237] = &ISUP_EXM_Desc;   /* 0xED */

    /* BEGIN - ANSI95 over-riding 92 part */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[1] = &ANSI95_ISUP_IAM_Desc;
/* 0x01 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[6] = &ANSI95_ISUP_ACM_Desc;     /* 0x06 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[9] = &ANSI95_ISUP_ANM_Desc;     /* 0x09 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[44] = &ANSI95_ISUP_CPG_Desc;    /* 0x2C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[4] = &ANSI95_ISUP_INF_Desc;     /* 0x04 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[12] = &ANSI95_ISUP_REL_Desc;    /* 0x0C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[23] = &ANSI95_ISUP_GRS_Desc;    /* 0x17 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[41] = &ANSI95_ISUP_GRA_Desc;    /* 0x29 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[42] = &ANSI95_ISUP_CQM_Desc;    /* 0x42 */

    /* END - ANSI95 over-riding 92 part */

    /* Additional Message in ANSI95, not in 92 */

    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[51] = &ANSI95_ISUP_FAC_Desc;    /* 0x33 */

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
    ISUP_DEBUG(("(%s) ClassDestroy: ANSI95...\n",__FILE__));

    return;
}


/*.implementation:static
****************************************************************************
 *  Purpose:
 *      Destroy the class part.
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
ANSI_ISUP95_ClassPartDestroy(ITS_Class classRec)
{
    ISUP_DEBUG(("(%s) ANSI_ISUP95_ClassPartDestroy: ANSI95...\n",__FILE__));

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
ANSI_ISUP95_InitTimeoutProcs(ITS_Class classRec)
{
#if 0
    HASH_Table TimeoutProcTable = NULL;
#endif

    ISUP_DEBUG(("ANSI_ISUP95_InitTimeoutProcs: ANSI95...\n"));

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
ANSI_ISUP95_SetMsgProc(ITS_Class V_Class, HASH_Table MsgProcTable,
                 ITS_OCTET msgType, ITS_ISUP_STATE state,
                 __ISUP_MsgHandlerProc func)
{
    ISUP_DEBUG(("ANSI_ISUP95_SetMsgProc: mtype %x, state %x, func %x\n",
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
ANSI_ISUP95_InitMsgProcs(ITS_Class classRec)
{
    ITS_USHORT state = 0;
    ITS_USHORT key = 0;
    ITS_USHORT msg = ISUP_MSG_FAC;
    HASH_Table MsgProcTable = NULL;
    __ISUP_MsgHandlerProc func = NULL;

    ISUP_DEBUG(("(%s) ANSI_ISUP95_InitMsgProcs: ANSI95...\n",__FILE__));

    if ((MsgProcTable = ISUP_CLASS_HASH_MSG_PROCS(classRec)) == NULL)
    {
        ISUP_DEBUG(("ERROR:: MsgProcTable access error: Exiting\n"));
        ISUP_ERROR(("ANSI_ISUP95_InitMsgProcs(): MsgProcTable access error!"
                     " Exiting...\n"));
        return ITS_EINITFAIL;
    }

    for (state = 0; state < ISUP_NB_STATES; state++)
    {
        func = __ISUP_GetMsgHandler_ANSI95((ITS_OCTET)msg,
                  (ITS_ISUP_STATE)state);

        if (ANSI_ISUP95_SetMsgProc(classRec, MsgProcTable,
                                 (ITS_OCTET)msg, (ITS_ISUP_STATE) state,
                                 func) != ITS_SUCCESS)
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
 *      generic variant class (ANSI92). Note that this is because initialization
 *      of the ANSI92 class (base class) has been already done before calling
 *      this function.
 *
 *  See Also:
 ****************************************************************************/
static int
ANSI_ISUP95_ClassPartInitialize(ITS_Class classRec)
{
    ISUP_DEBUG(("ANSI_ISUP95_ClassPartInitialize(): "
                "Executing ClassPartInitialize for %s\n",
                 ITS_CLASS_CLASSNAME(classRec)));

    if (ANSI_ISUP95_InitMsgProcs(classRec) != ITS_SUCCESS)
    {
        return ITS_EINITFAIL;
    }

    if (ANSI_ISUP95_InitTimeoutProcs(classRec) != ITS_SUCCESS)
    {
        return ITS_EINITFAIL;
    }

    ISUP_DEBUG(("\nANSI_ISUP95_ClassPartInitialize()::"
                  " End executing VARIANT_ClassPartInitialize() for %s\n\n",
                    ITS_CLASS_CLASSNAME(classRec)));

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
ANSI_ISUP95_VARIANT_SpecificMsg(ITS_Class V_class, ITS_EVENT* event)
{
    ISUP_DEBUG(("ANSI_ISUP95_VARIANT_SpecificMsg: ANSI95...\n"));
    return 0;
}


/*
 * ANSI95 Variant Record
 */

ISUP_VariantInfo   isupANSI95_Info =
{
    {
        /* Bitwise table for msgs. supported in the variant. */
        TABLE_MSG_SUPPORTED_ROW0_ANSI92,
        TABLE_MSG_SUPPORTED_ROW1_ANSI92,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROW3_ANSI92,
        TABLE_MSG_SUPPORTED_ROW4_ANSI92,
        TABLE_MSG_SUPPORTED_ROW5_ANSI92,
        TABLE_MSG_SUPPORTED_ROW6_ANSI95,  /* Row 6 */
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,   /* Row 10 */
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,   /* Row 15 */
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,   /* Row 20 */
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,   /* Row 25 */
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROW29_ANSI92,
    },
    {
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T1.  4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T5.  1 min.               */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T6.  10-32 s.             */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer T7.  20-30 s.             */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T8.  10-15 s.             */
        { ISUP_TMR_HNDL_STACK, 180 },  /* Timer T9.  2-4 mins.            */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer T11. 15-20 s.             */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T12. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T13. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T14. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T15. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T16. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T17. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T18. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T19. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T20. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T21. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T22. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T23. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 1   },  /* Timer T24. < 2 s.               */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T25. 1-10 s.              */
        { ISUP_TMR_HNDL_STACK, 120 },  /* Timer T26. 1-3 mins.            */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T27. > 3 mins.            */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T28. 10 s.                */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T31. > 6 mins.            */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T32. 3-5 s.               */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T33. 12-15 s.             */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T34. 10-15 s.             */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 3   },  /* Timer T36. 2-4 s.               */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T37. 30 s.                */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer TACCr. 5 s.               */
        { ISUP_TMR_HNDL_STACK, 2   },  /* Timer TCCR. 2 s.                */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer TCCRr. 20 s.              */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer TCGB. 5 s.                */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer TCRA. 20 s.               */
        { ISUP_TMR_HNDL_STACK, 3   },  /* Timer TCRM. 3-4 s.              */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer TCVT. 10 s.               */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer TEXMd. network dependent  */
        { ISUP_TMR_HNDL_STACK, 50  },  /* Timer TGRS. 5 s.                */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer THGA. 0-5 min.            */
        { ISUP_TMR_HNDL_STACK, 120 },  /* Timer TSCGA. 0-2 min.           */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer TSCGAd. 5-120 s.          */
    },
    {
        NULL /* Array of msg. descriptors : updated within ClassInitialize() */
    },
    NULL,   /* Hash Table for message procs. : Table ptr. updated after init.*/
    NULL,   /* Hash Table for timeout procs. : Table ptr. updated after init.*/
    0,      /* First CIC in Ckgp. */
    24,     /* Number of CICs in Circuit Group */
    0x00U,  /* supportMsgCompInfo */
    0x00U,  /* supportParamCompInfo */
    0x01U   /* exchangeType */
};


/*
 * the class record of ANSI95
 */
SS7DLLAPI ANSI_ISUP95_VARIANT_ClassRec isupANSI95_ClassRec =
{
    /* core part */
    {
#if defined(WIN32)
		NULL,
#else
        (ITS_Class)&isupANSI92_ClassRec, /* superclass is ANSI92 */
#endif
        sizeof(ISUP_VariantInfo),        /* sizeof instance  ??? */
        ITS_FALSE,                       /* not initted */
        0,                               /* initial refCount */
        ANSI_ISUP95_VARIANT_CLASS_NAME,  /* class name */
        ClassInitialize,                 /* class initialize ??? inherit */
        ClassDestroy,                    /* class destroy ??? inherit */
        ANSI_ISUP95_ClassPartInitialize, /* class initialize part */
        ANSI_ISUP95_ClassPartDestroy,    /* class destroy part */
        NULL,                            /* instantiate */
        NULL,                            /* destroy */
        ITS_INST_CLONE_INHERIT,          /* inherit clone */
        ITS_INST_PRINT_INHERIT,          /* inherit print */
        ITS_INST_SERIAL_INHERIT,         /* inherit serial */
        ITS_INST_EQUALS_INHERIT,         /* inherit equals */
        ITS_INST_HASH_INHERIT,           /* inherit hash */
        NULL                             /* no extension of interest */
    },
    /* VARIANT part */
    {
        &isupANSI95_Info,                 /* info */
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
        ANSI_ISUP95_VARIANT_SpecificMsg   /* Variant Specific processing of msgs */
    }

};

SS7DLLAPI ITS_Class isupANSI95_Class = (ITS_Class)&isupANSI95_ClassRec;
