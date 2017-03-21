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
 *  ID: $Id: isup_95.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:22:04  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:53:23  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/08/01 15:52:01  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 1.2.2.3  2002/07/03 18:20:39  hbalimid
 * LOG: varinat declaraions complete.
 * LOG:
 * LOG: Revision 1.2.2.2  2002/07/02 19:59:37  hbalimid
 * LOG: baseline for ISUP ANSI95.
 * LOG:
 *
 *****************************************************************************/

#ifndef _ANSI_ISUP95_H
#define _ANSI_ISUP95_H

#include <ansi/isup_92.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * These signatures define the ISUP ANSI95 Variant class implementation.
 */
typedef ITS_INT    (*ANSI_ISUP95_VariantSpecificMsgProc)(ITS_Class, ITS_EVENT*);


/*
 * Inheritance.
 */
#define ANSI_ISUP95_VARIANT_SPECIFIC_MSG_INHERIT  ((ANSI_ISUP95_VariantSpecificMsgProc)NULL)

/*
 * ANSI ISUP95 Variant definition
 */
typedef struct
{
    ANSI_ISUP95_VariantSpecificMsgProc VariantSpecificMsg;
}
ANSI_ISUP95_VARIANT_ClassPart;

/*
 * the ANSI ISUP95 Variant Class Record.
 */
typedef struct
{
    ITS_CoreClassPart       coreClass;
    ISUP_VARIANT_ClassPart  variantClass;
    ANSI_ISUP95_VARIANT_ClassPart variantANSIISUP95Class;
}
ANSI_ISUP95_VARIANT_ClassRec, *ANSI_ISUP95_VARIANT_Class;

/*
 * ANSI ISUP95 Variant Macros.
 */

#define ANSI_ISUP95_VARIANT_CLASS_NAME ISUP_ANSI_95_STRING


/*
 * The set of messages supported for each variant is represented by a table of
 * 32 rows.
 * Each bit of this table is a msg supported indicator for the message type.
 * row 0 bit 1 will be the msg supported indicator for message type 0x01, and
 * row 31 bit 7 will be the msg supported indicator for message type 0xFF.
 *
 * The following table is the table for msgs common to all ANSI variants:
 *
 *        bit 7  bit 6  bit 5  bit 4  bit 3  bit 2  bit 1  bit 0
 *       ---------------------------------------------------------
 * row 0 | NULL | ACM  | COT  | INF  | INR  | NULL | IAM  | NULL |
 *       ---------------------------------------------------------
 * row 1 | NULL | RES  | SUS  | REL  | NULL | NULL | ANM  | FOT  |
 *       ---------------------------------------------------------
 * row 2 | GRS  | UBA  | BLA  | UBL  | BLO  | RSC  | CCR  | RLC  |
 *       ---------------------------------------------------------
 * row 3 | NULL | NULL | NULL | NULL | CGUA | CGBA | CGU  | CGB  |
 *       ---------------------------------------------------------
 * row 4 | NULL | NULL | NULL | LPA  | NULL | NULL | NULL | NULL |
 *       ---------------------------------------------------------
 * row 5 | CFN  | UCIC | NULL | CPG  | CQR  | CQM  | GRA  | PAM  |
 *       ---------------------------------------------------------
 * row 6 | NULL | NULL | NULL | NULL | FAC  | NULL | NULL | NULL |
 *       ---------------------------------------------------------
 * row 7 | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL |
 *       ---------------------------------------------------------
 * row ..| .... | .... | .... | .... | .... | .... | .... | .... |
 * ... All rows NULL
 *       ---------------------------------------------------------
 * row 28| NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL |
 *       ---------------------------------------------------------
 * row 29| NULL | NULL | EXM  | CVT  | CVR  | CRM  | CRA  | NULL |
 *       ---------------------------------------------------------
 * NULL: No msg or Reserved .
 *
 * row m, bit n: msg_code = m * 8 + n
 */

/*
 * externs for messages - in ANSI95, differing from ANSI92
 */

extern SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_ACM_Desc; /* Address Complete */
extern SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_ANM_Desc; /* Answer */
extern SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_CPG_Desc; /* Call Progress */
extern SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_INF_Desc; /* Information */
extern SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_REL_Desc; /* Release */
extern SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_GRS_Desc; /* Circuit Group Reset */
extern SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_GRA_Desc; /* Circuit Group Reset Acknowledgement */


/*
 * externs for messages - Specific to ANSI95, not in ANSI92
 */

extern SS7DLLAPI ISUP_MSG_DESC   ANSI95_ISUP_FAC_Desc; /* Facility */

/*
 * Message set specific to by ANSI95.
 */

#define TABLE_MSG_SUPPORTED_ROW6_ANSI95  0x08U /* 0000 1000 */

#ifdef __cplusplus
}
#endif

#endif /* #define _ANSI_ISUP95_H*/
