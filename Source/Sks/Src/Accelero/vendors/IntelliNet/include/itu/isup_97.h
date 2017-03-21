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
 *  ID: $Id: isup_97.h,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:22:06  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:05  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:53:24  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.4  2002/08/01 15:52:01  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 1.3.2.1  2002/07/02 20:00:59  hbalimid
 * LOG: comments modified.
 * LOG:
 * LOG: Revision 1.3  2002/06/22 03:12:09  hbalimid
 * LOG: corrected the LOP position in the Message BitMap
 * LOG:
 * LOG: Revision 1.2  2002/05/20 16:30:38  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/05/14 18:05:07  hbalimid
 * LOG: ITU97 specific message descriptions declared
 * LOG:
 * LOG: Revision 1.1.2.2  2002/05/13 23:03:25  hbalimid
 * LOG: class part defined
 * LOG:
 * LOG: Revision 1.1.2.1  2002/04/15 17:45:05  hbalimid
 * LOG: Base line ITU ISUP 97 variant
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITU_ISUP97_H
#define _ITU_ISUP97_H

#include <itu/isup_93.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * These signatures define the ISUP ITU 97 Variant class implementation.
 */
typedef ITS_INT       (*ITU_ISUP97_VariantSpecificMsgProc)(ITS_Class, ITS_EVENT*);


/*
 * Inheritance.
 */
#define ITU_ISUP97_VARIANT_SPECIFIC_MSG_INHERIT  ((ITU_ISUP97_VariantSpecificMsgProc)NULL)

/*
 * ITU ISUP97 Variant definition
 */
typedef struct
{
    ITU_ISUP97_VariantSpecificMsgProc VariantSpecificMsg;
}
ITU_ISUP97_VARIANT_ClassPart;


/*
 * the ITU ISUP 97 Variant Class Record.
 */
typedef struct
{
    ITS_CoreClassPart       coreClass;
    ISUP_VARIANT_ClassPart  variantClass;
    ITU_ISUP97_VARIANT_ClassPart variantITUISUP97Class;
}
ITU_ISUP97_VARIANT_ClassRec, *ITU_ISUP97_VARIANT_Class;


/*
 * ITU ISUP 97 Variant Macros.
 */

#define ITU_ISUP97_VARIANT_CLASS_NAME ISUP_ITU_GENERIC_97_STRING


/*
 * The set of messages supported for this variant is represented by a table of
 * 32 rows.
 * Each bit of this table is a msg supported indicator for the message type.
 * row 0 bit 1 will be the msg supported indicator for message type 0x01, and
 * row 31 bit 7 will be the msg supported indicator for message type 0xFF.
 *
 * The following table is the table for msgs supported in ituisup 97 variant:
 *
 *        bit 7  bit 6  bit 5  bit 4  bit 3  bit 2  bit 1  bit 0
 *       ---------------------------------------------------------
 * row 0 | CON  | ACM  | COT  | INF  | INR  | SAM  | IAM  | NULL |
 *       ---------------------------------------------------------
 * row 1 | NULL | RES  | SUS  | REL  | NULL | NULL | ANM  | FOT  |
 *       ---------------------------------------------------------
 * row 2 | GRS  | UBA  | BLA  | UBL  | BLO  | RSC  | CCR  | RLC  |
 *       ---------------------------------------------------------
 * row 3 | FAR  | NULL | NULL | NULL | CGUA | CGBA | CGU  | CGB  |
 *       ---------------------------------------------------------
 * row 4 | NULL | NULL | NULL | LPA  | NULL | NULL | FRJ  | FAA  |
 *       ---------------------------------------------------------
 * row 5 | CFN  | UCIC | USR  | CPG  | CQR  | CQM  | GRA  | PAM  |
 *       ---------------------------------------------------------
 * row 6 | IRS  | IDR  | UPA  | UPT  | FAC  | NRM  | CRG  | OLM  |
 *       ---------------------------------------------------------
 * row 7 | NULL | NULL | NULL | NULL | NULL | NULL | NULL | SGM  |
 *       ---------------------------------------------------------
 * row 8 | NULL | NULL | NULL | NULL | NULL | NULL | NULL | LOP  |
 *       ---------------------------------------------------------
 * NULL: No msg or Reserved (used in 1984 or 1988 version).
 *
 */


/*
 * Message set addition in ITU ISUP 97.
 */

#define TABLE_MSG_SUPPORTED_ROW8_ITU_ISUP97  0x01U /* 0000 0001 */


/*
 * externs for messages - in ITU97, differing from ITU93
 */

extern SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_ACM_Desc; /* Address Complete */
extern SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_ANM_Desc; /* Answer */
extern SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_CPG_Desc; /* Call Progress */
extern SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_CON_Desc; /* Connect */
extern SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_IAM_Desc; /* Initial Address */
extern SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_REL_Desc; /* Release */
extern SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_FAC_Desc; /* Facility */
extern SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_NRM_Desc; /* Network Resource Management */
extern SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_IDR_Desc; /* Identification Response */

/*
 * externs for messages - Specific to ITU97; not in ITU93
 */

extern SS7DLLAPI ISUP_MSG_DESC   ITU97_ISUP_LOP_Desc; /* Loop Prevention */

#ifdef __cplusplus
}
#endif


#endif /* #define _ITU_ISUP97_H*/
