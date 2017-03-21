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
 *  ID: $Id: isup_china.h,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
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
 * LOG: Revision 9.1  2005/03/23 12:54:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:53:24  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.3  2002/02/13 18:28:32  mmiers
 * LOG: Finish off the ISUP integration.  Still need to add CHINA
 * LOG: variant lib.
 * LOG:
 * LOG: Revision 1.2  2002/02/01 20:07:30  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/22 23:40:39  ssharma
 * LOG: Added files for IntelliNet ISUP stack.
 * LOG:
 * LOG:
 *
 *****************************************************************************/

#ifndef _CHINA_H
#define _CHINA_H

#include <its_types.h>
#include <itu/isup_93.h>

#ifdef __cplusplus
extern "C"
{
#endif




/*****************************************************************************
 *
 * ISUP CHINA Variant "Derived Class" ("Base Class": ITU93 Variant).
 *
 ****************************************************************************/

/*
** Convenience #defs for filling up MsgSupported Table
*/
#define TABLE_MSG_SUPPORTED_R0W1_CHINA  0xB9U /* 10111001 */
#define TABLE_MSG_SUPPORTED_R0W2_CHINA  0xC7U /* 11000111 */
#define TABLE_MSG_SUPPORTED_R0W3_CHINA  0x89U /* 10001001 */


/*
** These signatures define the ISUP ITU 93 Variant class implementation.
*/
typedef ITS_INT       (*VariantSpecificMsgProc)(ITS_Class, ITS_EVENT*);


/*
** Inheritance.
*/
#define CHINA_VARIANT_SPECIFIC_MSG_INHERIT  ((VariantSpecificMsgProc)NULL)

                                                                               
/*
** the ISUP CHINA Variant Definition
*/
typedef struct
{
    VariantSpecificMsgProc VariantSpecificMsg;
}
CHINA_VARIANT_ClassPart;


/*
** the ISUP CHINA Variant Class Record.
*/
typedef struct
{
    ITS_CoreClassPart       coreClass;
    ISUP_VARIANT_ClassPart  variantClass;
    CHINA_VARIANT_ClassPart variantCHINAClass;  
}
CHINA_VARIANT_ClassRec, *CHINA_VARIANT_Class;

/*
** ISUP CHINA Variant Macros.
*/
#define CHINA_VARIANT_SPECIFIC_MSG(x) \
    (((CHINA_VARIANT_Class)(x))->variantCHINAClass.VariantSpecificMsg)


#define CHINA_VARIANT_CLASS_NAME "CHINA_VARIANT"

CHINA_VARIANT_Class CHINA_CreateClass();
ITS_BOOLEAN CHINA_IsMsgSupported(CHINA_VARIANT_Class, ITS_OCTET);
ITS_BOOLEAN CHINA_IsMsgCompInfoSupported(CHINA_VARIANT_Class);                 
ITS_BOOLEAN CHINA_IsParamCompInfoSupported(CHINA_VARIANT_Class);
ISUP_MSG_DESC* CHINA_GetMsgDescription(CHINA_VARIANT_Class, ITS_OCTET);
int CHINA_DecodeMsg(CHINA_VARIANT_Class, ITS_EVENT, ITS_OCTET,
                    ITS_OCTET, ITS_ISUP_IE*, int*, ITS_HDR*);
int CHINA_EncodeMsg(CHINA_VARIANT_Class, ITS_ISUP_IE*, int, ITS_OCTET,
                      ITS_OCTET, ITS_HDR*, ITS_EVENT*);
ITS_UINT  CHINA_ComputeMsize(CHINA_VARIANT_Class, ITS_OCTET);
ITS_OCTET CHINA_HandleUnrecMsg(CHINA_VARIANT_Class, ITS_EVENT *); 
__ISUP_MsgHandlerProc CHINA_GetMsgProc(CHINA_VARIANT_Class, ITS_OCTET,
                                                     ITS_ISUP_STATE); 
__ISUP_TimeoutHandlerProc CHINA_GetTimeoutProc(CHINA_VARIANT_Class, ITS_UINT,
                                                     ITS_ISUP_STATE); 

ITS_INT CHINA_VARIANT_SpecificMsg(ITS_Class, ITS_EVENT *);   
int CHINA_InitTimeoutProcs(ITS_Class);
int CHINA_InitMsgProcs(ITS_Class);
int CHINA_SetMsgProc(ITS_Class, HASH_Table, ITS_OCTET, ITS_ISUP_STATE,
                     __ISUP_MsgHandlerProc);                                 
int CHINA_SetTimeoutProc(ITS_Class, HASH_Table, ITS_UINT, ITS_ISUP_STATE,
                         __ISUP_TimeoutHandlerProc);                                 

/*
 * The set of msg supported for each variant is represented by a table of
 * 32 raws.
 * Each bit of this table is a msg supported indicator for the message type.
 * raw 0 bit 1 will be the msg supported indicator for message type 0x01, and
 * raw 31 bit 8 will be the msg supported indicator for message type 0xFF.
 * Raw 0 -> 6 (included) are for msgs common to all ITU variants (ITU 93 ref.).
 * Raw 7 -> 31 (included) are for msgs specific for each variant.
 *
 *
 * The following table is the table for msgs common to all ITU variants:
 *                                                                             
 *        bit 8  bit 7  bit 6  bit 5  bit 4  bit 3  bit 2  bit 1
 *       ---------------------------------------------------------
 * Raw 0 | FOT  | CON  | ACM  | COT  | INF  | INR  | SAM  | IAM  |
 *       ---------------------------------------------------------
 * Raw 1 | RLC  | NULL | RES  | SUS  | REL  | NULL | NULL | ANM  |
 *       ---------------------------------------------------------
 * Raw 2 | CGB  | GRS  | UBA  | BLA  | UBL  | BLO  | RSC  | CCR  |
 *       ---------------------------------------------------------
 * Raw 3 | FAA  | FAR  | NULL | NULL | NULL | CGUA | CGBA | CGU  |
 *       ---------------------------------------------------------
 * Raw 4 | PAM  | NULL | NULL | NULL | LPA  | NULL | NULL | FRJ  |
 *       ---------------------------------------------------------
 * Raw 5 | OLM  | CFN  | UCIC | USR  | CPG  | CQR  | CQM  | GRA  |
 *       ---------------------------------------------------------
 * Raw 6 |SGM   | IRS  | IDR  | UPA  | UPT  | FAC  | NRM  | CRG  |
 *       ---------------------------------------------------------
 *
 * NULL: No msg or Reserved (used in 1984 or 1988 version).
 *
 */                                                                            


#ifdef __cplusplus
}
#endif

#endif /* #define _CHINA_H*/
                                                                               
