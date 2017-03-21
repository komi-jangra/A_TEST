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
 *  ID: $Id: isup_93.h,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:22:05  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:05  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:53:23  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.2.6.2.12.2  2004/12/07 11:12:12  mmanikandan
 * LOG: Windows Compilation Support test bugs fixed.
 * LOG:
 * LOG: Revision 7.2.2.2.6.2.12.1  2004/12/06 14:04:18  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.2.2.2.6.2  2004/01/08 07:31:00  sjaddu
 * LOG: Type fixed.
 * LOG:
 * LOG: Revision 7.2.2.2.6.1  2004/01/05 10:16:59  sjaddu
 * LOG: Merged code from tcs isup.
 * LOG:
 * LOG: Revision 7.2.2.2  2003/07/25 04:57:20  akumar
 * LOG: National UCIC related Functions added.
 * LOG:
 * LOG: Revision 7.2.2.1  2003/05/07 09:56:15  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.2  2003/03/24 12:27:47  akumar
 * LOG: Warning Removal
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:21  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.2  2003/01/22 09:32:20  akumar
 * LOG: Modified for ITU COT procedure
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/08/01 15:52:01  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 6.2.2.1  2002/07/06 19:55:36  hbalimid
 * LOG: Fixed warnings.
 * LOG:
 * LOG: Revision 6.2  2002/05/20 15:44:41  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.4.2.2  2002/05/15 16:45:41  hbalimid
 * LOG: removed extern declaration for 93 class
 * LOG:
 * LOG: Revision 1.4.2.1  2002/05/14 18:03:13  hbalimid
 * LOG: extern declarations for isup93 class and classrec
 * LOG:
 * LOG: Revision 1.4  2002/02/13 18:28:32  mmiers
 * LOG: Finish off the ISUP integration.  Still need to add CHINA
 * LOG: variant lib.
 * LOG:
 * LOG: Revision 1.3  2002/02/12 23:29:03  mmiers
 * LOG: ISUP parser in place.
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

#ifndef _ITU93_H
#define _ITU93_H

#include <its_types.h>
#include <isup_variants.h>
#include <isup_intern.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <its_object.h>                                                        


/*
** the ISUP ITU 93 Variant Class Record.
*/
typedef struct
{
    ITS_CoreClassPart       coreClass;
    ISUP_VARIANT_ClassPart  variantClass;
}
ITU93_VARIANT_ClassRec, *ITU93_VARIANT_Class;

extern ITSSS7DLLAPI ITU93_VARIANT_ClassRec isupITU93_ClassRec;
extern ITSSS7DLLAPI ITS_Class isupITU93_Class;

#define ITU93_VARIANT_CLASS_NAME ISUP_ITU_GENERIC_93_STRING

ITU93_VARIANT_Class ITU93_CreateClass();

ITS_BOOLEAN ITU93_IsMsgSupported(ITS_Class, ITS_OCTET);

ITS_BOOLEAN ITU93_IsMsgCompInfoSupported(ITS_Class); 

ITS_BOOLEAN ITU93_IsParamCompInfoSupported(ITS_Class);

ISUP_MSG_DESC* ITU93_GetMsgDescription(ITS_Class, ITS_OCTET);

ITSSS7DLLAPI int ITU93_DecodeMsg(ITS_Class, ITS_EVENT, ITS_OCTET, ITS_OCTET,
                    ITS_ISUP_IE*, int*, ITS_HDR*);

ITSSS7DLLAPI int ITU93_EncodeMsg(ITS_Class, ITS_ISUP_IE*, int, 
                    ITS_OCTET, ITS_OCTET,
                    ITS_HDR*, ITS_EVENT*);

ITSSS7DLLAPI ITS_UINT ITU93_ComputeMsize(ITS_Class, ITS_OCTET);   

ITSSS7DLLAPI ITS_OCTET ITU93_HandleUnrecMsg(ITS_Class, ITS_EVENT *);   

ITSSS7DLLAPI int ITU93_InitMsgProcs(ITS_Class);

ITSSS7DLLAPI int ITU93_InitTimeoutProcs(ITS_Class);

ITSSS7DLLAPI int ITU93_SetMsgProc(ITS_Class V_Class, HASH_Table MsgProcTable,
                     ITS_OCTET msg, ITS_ISUP_STATE state,
                     __ISUP_MsgHandlerProc func);

ITSSS7DLLAPI int ITU93_SetTimeoutProc(ITS_Class V_Class, HASH_Table TimeoutProcTable,
                         ITS_UINT tmr, ITS_ISUP_STATE state,
                         __ISUP_TimeoutHandlerProc func);

ITSSS7DLLAPI ITS_OCTET ITU93_HandleUnrecParamProc(ITS_Class V_Class,
                                     ITS_OCTET mType,ITS_OCTET *compInfo);


ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_WaitIncomingAcm_ITU93(ITS_OCTET msgType) ;
ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_WaitIncomingAnm_ITU93(ITS_OCTET msgType) ;
ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_RcvdIncomingAnm_ITU93(ITS_OCTET msgType) ;
ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_WaitIncomingRlc_ITU93(ITS_OCTET msgType) ;
ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_WaitIncomingRes_ITU93(ITS_OCTET msgType) ;
ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_WaitOutgoingAcm_ITU93(ITS_OCTET msgType) ;
ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_WaitOutgoingAnm_ITU93(ITS_OCTET msgType) ;
ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_SentOutgoingAnm_ITU93(ITS_OCTET msgType) ;
ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_WaitOutgoingRlc_ITU93(ITS_OCTET msgType) ;
ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_WaitOutgoingRes_ITU93(ITS_OCTET msgType) ;
ITSSS7DLLAPI __ISUP_MsgHandlerProc
                  __ISUP_GetMsgProc_WaitOutgoingRel_ITU93(ITS_OCTET msgType) ;                                                                              

ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_Idle_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_WaitIncomingAcm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_WaitIncomingAnm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_RcvdIncomingAnm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_WaitIncomingRlc_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_WaitIncomingRes_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_WaitOutgoingAcm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_WaitOutgoingAnm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_SentOutgoingAnm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_WaitOutgoingRlc_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_WaitOutgoingRes_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                  __ISUP_GetTimeoutProc_WaitOutgoingRel_ITU93(ITS_UINT timerId);


ITSSS7DLLAPI __ISUP_MsgHandlerProc
                    ITU93_GetMsgProc(ITS_Class, ITS_OCTET, ITS_ISUP_STATE);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
                    ITU93_GetTimeoutProc(ITS_Class, ITS_UINT, ITS_ISUP_STATE);

ITSSS7DLLAPI __ISUP_MsgHandlerProc
              __ISUP_GetMsgProc_WaitCotReport_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc
              __ISUP_GetMsgProc_WaitIncomingCot_ITU93(ITS_OCTET msgType);

ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
              __ISUP_GetTimeoutProc_WaitCotReport_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc 
              __ISUP_GetTimeoutProc_WaitIncomingCot_ITU93(ITS_UINT timerId);


/*
 * UCIC Procedures
 */
ITSSS7DLLAPI void
__ISUP_ResetUCICToCPC(ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopUCICToCRS(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopUCICToCGRS(ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopUCICToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopUCICToBLS(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopUCICToGBUS(ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info);


/*
 * CRO/CRI Procedures
 */
ITSSS7DLLAPI void
__ISUP_StopCGRRToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopCGRRToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopCGRSToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopCGRSToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopBLRToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void
__ISUP_StopBLRToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopBLSToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopBLSToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopMGBSToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopCRRToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_StopCRRToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopCPCToCCO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopCPCToCCI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);


/*
 * Generic state handlers
 */
ITSSS7DLLAPI void
__ISUP_StartRELProcedure(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_IsExchangeControlling(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info);


/*
 * SGM Timer T34 Declaration
 */
void __ISUP_Received_TimeoutT34(ISUP_TIMER_ENTRY* t_entry,
                                       ISUP_CIC_INFO *cic_rec,
                                       ISUP_OPC_DPC_INFO *config_info);

/* TODO Remove later this is just for testing !!! */

#define DISCARD_AND_SEND_CONFUSION    0xFF
#define MCIP                          0xF0


/*
 * The set of messages supported for each variant is represented by a table of
 * 32 rows.
 * Each bit of this table is a msg supported indicator for the message type.
 * row 0 bit 1 will be the msg supported indicator for message type 0x01, and
 * row 31 bit 7 will be the msg supported indicator for message type 0xFF.
 *
 * The following table is the table for msgs common to all ITU variants:
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
 * NULL: No msg or Reserved (used in 1984 or 1988 version).
 *
 */                                                                            


/*
 * Message set supported by ITU 93.
 */

#define TABLE_MSG_SUPPORTED_ROW0_ITU93  0xFEU /* 1111 1110 */
#define TABLE_MSG_SUPPORTED_ROW1_ITU93  0x73U /* 0111 0011 */
/* Row 2 : Set. */
#define TABLE_MSG_SUPPORTED_ROW3_ITU93  0x8FU /* 1000 1111 */
#define TABLE_MSG_SUPPORTED_ROW4_ITU93  0x13U /* 0001 0011 */
/* Row 5 : Set. */
#define TABLE_MSG_SUPPORTED_ROW6_ITU93  0xFDU /* 1111 1101 */
/* In Row 6 CRG is not being supported now: TBD */
#define TABLE_MSG_SUPPORTED_ROW7_ITU93  0x01U /* 0000 0001 */

#ifdef __cplusplus
}
#endif

#endif /* #define _ITU93_H*/
                                                                               
