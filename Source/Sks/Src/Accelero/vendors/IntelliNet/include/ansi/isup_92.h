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
 *  ID: $Id: isup_92.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
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
 * LOG: Revision 8.3  2005/03/21 13:53:23  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.1.38.1  2004/12/06 14:04:18  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/05/07 09:56:15  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.2  2003/03/15 12:48:56  ssingh
 * LOG: Message handlers and Timeout handlers procs are added
 * LOG: for CRM/CRA related FSM states. COT/CCR handling functions added.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:21  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.4  2002/12/11 14:18:12  ssingh
 * LOG: New functions been added for INF/INR and T33 handling.
 * LOG:
 * LOG: Revision 7.3  2002/11/11 11:20:30  akumar
 * LOG: Code added for Automatic Congestion Control, ANSI ISUP Alarms and modified
 * LOG: the signature of __ISUP_IsExchangeControlling() func to include the new
 * LOG: argument.
 * LOG:
 * LOG: Revision 7.2  2002/10/30 06:23:43  sjaddu
 * LOG: Added continuity functions.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:52:01  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 1.1.2.13  2002/07/30 13:40:45  sjaddu
 * LOG: Added function for T37 timer.
 * LOG:
 * LOG: Revision 1.1.2.12  2002/07/18 18:48:49  ssingh
 * LOG: New function added to handle outgoing group ACKs.
 * LOG:
 * LOG: Revision 1.1.2.11  2002/07/13 17:41:37  hbalimid
 * LOG: Wait for Incoming ACM procedures completed.
 * LOG:
 * LOG: Revision 1.1.2.10  2002/07/13 02:29:42  hbalimid
 * LOG: CVT and CVR added.
 * LOG:
 * LOG: Revision 1.1.2.9  2002/07/12 22:23:47  hbalimid
 * LOG: Handlers for UCIC.
 * LOG:
 * LOG: Revision 1.1.2.8  2002/07/11 04:28:52  hbalimid
 * LOG: Added controlling exchange handler.
 * LOG:
 * LOG: Revision 1.1.2.7  2002/07/10 18:43:30  hbalimid
 * LOG: RELProcedure handler added.
 * LOG:
 * LOG: Revision 1.1.2.6  2002/07/06 19:55:36  hbalimid
 * LOG: Fixed warnings.
 * LOG:
 * LOG: Revision 1.1.2.5  2002/07/05 21:56:47  hbalimid
 * LOG: Added CVT max restarts.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/07/03 16:45:27  hbalimid
 * LOG: Modified according to ANSI92.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/02 23:06:54  ssingh
 * LOG: procs added for WaitOutgoingGra_ANSI92
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/02 22:51:42  hbalimid
 * LOG: modified bitmap by removing FAC and OLM.
 * LOG: Not in ANSI92
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/01 19:38:54  hbalimid
 * LOG: Baseline for ANSI ISUP92.
 * LOG:
 *
 *****************************************************************************/

#ifndef _ANSI_ISUP92_H
#define _ANSI_ISUP92_H

#include <its_types.h>
#include <isup_variants.h>
#include <isup_intern.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include <its_object.h>                                                        


/*
** the ISUP ANSI 92 Variant Class Record.
*/
typedef struct
{
    ITS_CoreClassPart       coreClass;
    ISUP_VARIANT_ClassPart  variantClass;
}
ANSI92_VARIANT_ClassRec, *ANSI92_VARIANT_Class;

extern ITSSS7DLLAPI ANSI92_VARIANT_ClassRec isupANSI92_ClassRec;

#define ANSI92_VARIANT_CLASS_NAME ISUP_ANSI_GENERIC_92_STRING

ANSI92_VARIANT_Class ANSI92_CreateClass();

ITS_BOOLEAN ANSI92_IsMsgSupported(ITS_Class, ITS_OCTET);

ITS_BOOLEAN ANSI92_IsMsgCompInfoSupported(ITS_Class); 

ITS_BOOLEAN ANSI92_IsParamCompInfoSupported(ITS_Class);

ISUP_MSG_DESC* ANSI92_GetMsgDescription(ITS_Class, ITS_OCTET);

ITSSS7DLLAPI int ANSI92_DecodeMsg(ITS_Class, ITS_EVENT, ITS_OCTET, ITS_OCTET,
                    ITS_ISUP_IE*, int*, ITS_HDR*);

ITSSS7DLLAPI int ANSI92_EncodeMsg(ITS_Class, ITS_ISUP_IE*, int, 
                    ITS_OCTET, ITS_OCTET,
                    ITS_HDR*, ITS_EVENT*);

ITSSS7DLLAPI ITS_UINT  ANSI92_ComputeMsize(ITS_Class, ITS_OCTET);   

ITSSS7DLLAPI ITS_OCTET ANSI92_HandleUnrecMsg(ITS_Class, ITS_EVENT *);   

ITSSS7DLLAPI int ANSI92_InitMsgProcs(ITS_Class);

ITSSS7DLLAPI int ANSI92_InitTimeoutProcs(ITS_Class);

ITSSS7DLLAPI int ANSI92_SetMsgProc(ITS_Class V_Class, HASH_Table MsgProcTable,
                      ITS_OCTET msg, ITS_ISUP_STATE state,
                      __ISUP_MsgHandlerProc func);

ITSSS7DLLAPI int ANSI92_SetTimeoutProc(ITS_Class V_Class, HASH_Table TimeoutProcTable,
                          ITS_UINT tmr, ITS_ISUP_STATE state,
                          __ISUP_TimeoutHandlerProc func);

ITSSS7DLLAPI ITS_OCTET ANSI92_HandleUnrecParamProc(ITS_Class V_Class,
                                      ITS_OCTET mType,ITS_OCTET *compInfo);

/* Generic timer can come in any state */
ITSSS7DLLAPI void
__ISUP_Received_TimeoutT37_ANSI92(ISUP_TIMER_ENTRY* t_entry,
                                ISUP_CIC_INFO *cic_rec,
                                ISUP_OPC_DPC_INFO *config_info);
/*
 * Functions returning Message handlers and Timeout handlers
 * depending on message type and call state
 * These are variant specific handlers.
 */
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgHandler_ANSI92(ITS_OCTET msgType,
                                                 ITS_ISUP_STATE state);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutHandler_ANSI92(ITS_UINT timerID,
                                                          ITS_ISUP_STATE state);


ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_Idle_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingAcm_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingAnm_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_RcvdIncomingAnm_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingRlc_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingRes_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingAcm_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingAnm_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_SentOutgoingAnm_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRlc_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRes_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRel_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRsc_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingGra_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_Received_UnexpectedMsg_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitCotReport_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingCot_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingCra_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingIam_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitCotReportAndCra_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitCotReportHaveCra_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingCotAndIam_ANSI92(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingIam_ANSI92(ITS_OCTET msgType);

ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitCotReport_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingCot_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_Idle_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingAcm_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingAnm_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_RcvdIncomingAnm_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingRlc_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingRes_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingAcm_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingAnm_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_SentOutgoingAnm_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingRlc_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingRes_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingRel_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingRsc_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingGra_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingCra_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingIam_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingIam_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitCotReportAndCra_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitCotReportHaveCra_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingCotAndIam_ANSI92(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_Received_UnexpectedTimeout_ANSI92(ITS_UINT timerId);


ITSSS7DLLAPI __ISUP_MsgHandlerProc ANSI92_GetMsgProc(ITS_Class, ITS_OCTET, ITS_ISUP_STATE);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc ANSI92_GetTimeoutProc(ITS_Class, ITS_UINT, ITS_ISUP_STATE);

/*
 * Generic state handlers
 */
ITSSS7DLLAPI void 
__ISUP_StartRELProcedure(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_IsExchangeControlling(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_CSC_Received_CVT(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);

ITSSS7DLLAPI void
__ISUP_CSC_Received_CVR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);

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

ITSSS7DLLAPI void
__ISUP_StopCROToDCO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

/* INR-INF Procedure */
ITSSS7DLLAPI void
__ISUP_CPC_Received_INR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);

ITSSS7DLLAPI void
__ISUP_CPC_Received_INF(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);

ITSSS7DLLAPI void
__ISUP_Received_TimeoutT33_ANSI92(ISUP_TIMER_ENTRY* t_entry,
                    ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info);

/*
ITSSS7DLLAPI void
__ISUP_ResetCGRRToCPC(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);
*/


ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopCPCToCCO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopCPCToCCI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StartCPCToCRO (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopCPCToCRO (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StartCPCToCRI (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopCPCToCRI (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StartCPCToCCO (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StartCPCToCCI (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StartCPCToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);


ITSSS7DLLAPI void
__ISUP_StopCRRToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);


ITSSS7DLLAPI void
__ISUP_StopCRRToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopMGBRToCRO(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopMGBRToCRI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopMGBSToCRO(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopMGBSToCRI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info);

/*
 * CVT Timer Max Restarts
 * ANSI T1.113-1992, Page T1.113.4-60
 * TABLE 3/T1.113.4 (Sheet 5 of 5)
 */

#define CVT_TIMER_MAX_RESTARTS 2


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
 * row 6 | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL |
 *       ---------------------------------------------------------
 * row 7 | NULL | NULL | NULL | NULL | NULL | NULL | NULL | NULL |
 *       ---------------------------------------------------------   
 * row ..| .... | .... | .... | .... | .... | .... | .... | .... | All rows NULL
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
 * Message set supported by ANSI 92.
 */

#define TABLE_MSG_SUPPORTED_ROW0_ANSI92  0x7AU /* 0111 1010 */
#define TABLE_MSG_SUPPORTED_ROW1_ANSI92  0x73U /* 0111 0011 */
/* Row 2 : Set. */
#define TABLE_MSG_SUPPORTED_ROW3_ANSI92  0x0FU /* 0000 1111 */
#define TABLE_MSG_SUPPORTED_ROW4_ANSI92  0x10U /* 0001 0000 */
#define TABLE_MSG_SUPPORTED_ROW5_ANSI92  0xDFU /* 1101 1111 */
/* Intermediate rows all NULL */
#define TABLE_MSG_SUPPORTED_ROW29_ANSI92 0x3EU /* 0011 1110 */


#ifdef __cplusplus
}
#endif

#endif /* #define _ANSI_ISUP92_H*/
