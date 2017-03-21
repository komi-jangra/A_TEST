/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 2001,2002 IntelliNet Technologies, Inc.            *
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
 *  ID: $Id: ansi-generic_state_ansi92.c,v 1.1.1.1 2007-10-08 11:12:17 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:08  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.7  2005/03/21 13:53:56  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.7.2.2.6.1.12.2  2004/12/29 14:35:54  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.7.2.2.6.1.12.1  2004/12/06 13:34:49  mmanikandan
 * LOG: Windows Compilation Support
 * LOG:
 * LOG: Revision 7.7.2.2.6.1  2004/01/05 10:10:44  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.7.2.2.2.1  2003/09/13 06:27:00  akumar
 * LOG: Msg Based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 7.7.2.2  2003/06/17 04:42:55  sjaddu
 * LOG: Changed INR trcaces bug 365.
 * LOG:
 * LOG: Revision 7.7.2.1  2003/05/07 10:37:59  ssingh
 * LOG: Latest Changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.5  2003/05/06 13:55:52  sswami
 * LOG: Alarm related changes :opc information included.
 * LOG:
 * LOG: Revision 8.4  2003/04/24 14:13:25  sswami
 * LOG: Bug #317; Alarm Enhancement related changes done.
 * LOG:
 * LOG: Revision 8.3  2003/04/03 15:24:34  sjaddu
 * LOG: ISUP DSM reorganization.
 * LOG:
 * LOG: Revision 8.2  2003/03/15 13:18:08  ssingh
 * LOG: Changes done in existing files to support CRM/CRA messaging.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:27  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.7  2003/01/14 00:23:31  sjaddu
 * LOG: You can access cic_rule from CIC record.
 * LOG:
 * LOG: Revision 7.6  2002/12/11 14:23:04  ssingh
 * LOG: Changed code for INF/INR/CPG and T33 expiry handling.
 * LOG:
 * LOG: Revision 7.5  2002/12/06 05:18:34  akumar
 * LOG: Removed unwanted TABS
 * LOG:
 * LOG: Revision 7.4  2002/11/13 12:37:07  akumar
 * LOG: Removed Warnings
 * LOG:
 * LOG: Revision 7.3  2002/11/12 05:28:54  akumar
 * LOG: Added ANSI ISUP Alarms, Automatic Congestion Control
 * LOG: procedures and a logic to determine the exhange
 * LOG: control
 * LOG:
 * LOG: Revision 7.2  2002/10/30 08:57:15  sjaddu
 * LOG: Added continuity proceddures.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/08/16 20:00:03  ssingh
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.7  2002/07/30 13:46:58  sjaddu
 * LOG: Added MTP indications and CFN procedures.
 * LOG:
 * LOG: Revision 1.1.2.6  2002/07/13 17:41:37  hbalimid
 * LOG: Wait for Incoming ACM procedures completed.
 * LOG:
 * LOG: Revision 1.1.2.5  2002/07/11 04:26:09  hbalimid
 * LOG: OGC Suspended completed.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/07/10 18:41:38  hbalimid
 * LOG: CPC outgoing statemachine implemented.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/06 06:09:59  hbalimid
 * LOG: Tookcare of all warnings.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/03 16:41:16  hbalimid
 * LOG: Modified according to ANSI92.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/01 20:17:50  hbalimid
 * LOG: Baseline for ISUP ANSI GENERIC 92.
 * LOG:
 *
 *****************************************************************************/

#undef CCITT
#undef ANSI
#define ANSI

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <isup_intern.h>
#include <ansi/isup_92.h>

static void __ISUP_Received_TimeoutTACCr(ISUP_TIMER_ENTRY* , ISUP_CIC_INFO *,
                               ISUP_OPC_DPC_INFO *);
/* Common Get Message Handlers
 * These are used to return state specific
 * message procs.
 */


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a message handler procedure, 
 *      based on the msgType and state of the CIC. This is the main function
 *      for the ANSI ISUP generic variant (ANSI92) message handling procedures. 
 *
 *  Input Parameters:
 *      msgType: the type of message per ISUP.
 *      status: the state of the CIC, as defined in isup_intern.h.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Valid pointer to a function.
 *
 ****************************************************************************/
ITSSS7DLLAPI __ISUP_MsgHandlerProc
__ISUP_GetMsgHandler_ANSI92(ITS_OCTET msgType, ITS_ISUP_STATE state)
{
    switch(state)
    {
    /* 
     * This should be called only after verifying that the msgType is correct.
     */
    case IDLE:
        return __ISUP_GetMsgProc_Idle_ANSI92(msgType);

    /* IAM sent to network, waiting for ACM. */
    case WAIT_INCOMING_ACM:
        return __ISUP_GetMsgProc_WaitIncomingAcm_ANSI92(msgType);

    /* ACM sent to network, waiting for ANM. */
    case WAIT_INCOMING_ANM:
        return __ISUP_GetMsgProc_WaitIncomingAnm_ANSI92(msgType);

    /* ANM rcvd from network, call established. */
    case RCVD_INCOMING_ANM: 
        return __ISUP_GetMsgProc_RcvdIncomingAnm_ANSI92(msgType);

    /* REL sent to network, waiting for RLC. */
    case WAIT_INCOMING_RLC: 
        return __ISUP_GetMsgProc_WaitIncomingRlc_ANSI92(msgType);

    /* SUS rcvd from network, call suspended, waiting for RES. */
    case WAIT_INCOMING_RES: 
        return __ISUP_GetMsgProc_WaitIncomingRes_ANSI92(msgType);

    /* IAM rcvd from network, waiting to send ACM. */
    case WAIT_OUTGOING_ACM: 
        return __ISUP_GetMsgProc_WaitOutgoingAcm_ANSI92(msgType);

    /* ACM rcvd from network, waiting to send ANM. */
    case WAIT_OUTGOING_ANM:     
        return __ISUP_GetMsgProc_WaitOutgoingAnm_ANSI92(msgType);

    /* ANM sent to network, call established. */
    case SENT_OUTGOING_ANM: 
        return __ISUP_GetMsgProc_SentOutgoingAnm_ANSI92(msgType);

    /* REL rcvd from network, waiting to send RLC. */
    case WAIT_OUTGOING_RLC: 
        return __ISUP_GetMsgProc_WaitOutgoingRlc_ANSI92(msgType);

    /* SUS sent to network, call suspended, waiting to send RES to network. */
    case WAIT_OUTGOING_RES: 
        return __ISUP_GetMsgProc_WaitOutgoingRes_ANSI92(msgType);

    /* Timeout/error, waiting to send REL to network. */
    case WAIT_OUTGOING_REL: 
        return __ISUP_GetMsgProc_WaitOutgoingRel_ANSI92(msgType);

    /* Timeout/error, waiting to send RSC to network. */
    case WAIT_OUTGOING_RSC: 
        return (__ISUP_MsgHandlerProc)
                   __ISUP_GetMsgProc_WaitOutgoingRsc_ANSI92(msgType);

    case WAIT_OUTGOING_GRA:
        return (__ISUP_MsgHandlerProc)
                   __ISUP_GetMsgProc_WaitOutgoingGra_ANSI92(msgType);

    case WAIT_CONTINUITY_REPORT:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitCotReport_ANSI92(msgType);

    case WAIT_INCOMING_COT:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitIncomingCot_ANSI92(msgType);

    case WAIT_COT_REPORTS_AND_CRA:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitCotReportAndCra_ANSI92(msgType);

    case WAIT_COT_REPORTS_HAVE_CRA:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitCotReportHaveCra_ANSI92(msgType);

    case WAIT_INCOMING_CRA:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitIncomingCra_ANSI92(msgType);

    case WAIT_INCOMING_IAM:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitIncomingIam_ANSI92(msgType);

    case WAIT_INCOMING_COT_AND_IAM:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitIncomingCotAndIam_ANSI92(msgType);

    case WAIT_OUTGOING_IAM:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitOutgoingIam_ANSI92(msgType);

    default:
        /* Log error in call */
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg_ANSI92(msgType);
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a timeout handler procedure, 
 *      based on the msgType and state of the CIC. This is the main function
 *      for the ANSI ISUP generic variant (ANSI92) timeout handling procedures.
 *
 *  Input Parameters:
 *      timerID - the ID of the timer, per ISUP.
 *      state - the ISUP state of the CIC, as defined in isup_intern.h.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Valid pointer to a function.
 *
 ****************************************************************************/
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
__ISUP_GetTimeoutHandler_ANSI92(ITS_UINT timerID, ITS_ISUP_STATE state)
{
    /* Timeout Handler for Automatic Congestion Control(TACCr) Timer
     * is called here, since it doesn't depend on the FSM state
     */
    if (timerID == ITS_ISUP_TIMER_TACCR)
    {
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutTACCr;
    }
    switch(state)
    {
    /* 
     * This should be called only after verifying that the timerID is correct.
     */
    case IDLE:
        return __ISUP_GetTimeoutProc_Idle_ANSI92(timerID);

    /* IAM sent to network, waiting for ACM. */
    case WAIT_INCOMING_ACM:
        return __ISUP_GetTimeoutProc_WaitIncomingAcm_ANSI92(timerID);

    /* ACM sent to network, waiting for ANM. */
    case WAIT_INCOMING_ANM: 
        return __ISUP_GetTimeoutProc_WaitIncomingAnm_ANSI92(timerID);

    /* ANM rcvd from network, call established. */
    case RCVD_INCOMING_ANM: 
        return __ISUP_GetTimeoutProc_RcvdIncomingAnm_ANSI92(timerID);

    /* REL sent to network, waiting for RLC. */
    case WAIT_INCOMING_RLC: 
        return __ISUP_GetTimeoutProc_WaitIncomingRlc_ANSI92(timerID);

    /* SUS rcvd from network, call suspended, waiting for RES. */
    case WAIT_INCOMING_RES: 
        return __ISUP_GetTimeoutProc_WaitIncomingRes_ANSI92(timerID);

    /* IAM rcvd from network, waiting to send ACM. */
    case WAIT_OUTGOING_ACM: 
        return __ISUP_GetTimeoutProc_WaitOutgoingAcm_ANSI92(timerID);

    /* ACM rcvd from network, waiting to send ANM. */
    case WAIT_OUTGOING_ANM:     
        return __ISUP_GetTimeoutProc_WaitOutgoingAnm_ANSI92(timerID);

    /* ANM sent to network, call established. */
    case SENT_OUTGOING_ANM: 
        return __ISUP_GetTimeoutProc_SentOutgoingAnm_ANSI92(timerID);

    /* REL rcvd from network, waiting to send RLC. */
    case WAIT_OUTGOING_RLC: 
        return __ISUP_GetTimeoutProc_WaitOutgoingRlc_ANSI92(timerID);

    /* SUS sent to network, call suspended, waiting to send RES to network. */
    case WAIT_OUTGOING_RES: 
        return __ISUP_GetTimeoutProc_WaitOutgoingRes_ANSI92(timerID);

    /* Timeout/error, waiting to send REL to network. */
    case WAIT_OUTGOING_REL: 
        return (__ISUP_TimeoutHandlerProc)__ISUP_GetTimeoutProc_WaitOutgoingRel_ANSI92(timerID);

    /* Timeout/error, waiting to send RSC to network. */
    case WAIT_OUTGOING_RSC:
        return (__ISUP_TimeoutHandlerProc)__ISUP_GetTimeoutProc_WaitOutgoingRsc_ANSI92(timerID);

    /* GRS received, waiting to send GRA to network. */
    case WAIT_OUTGOING_GRA:
        return (__ISUP_TimeoutHandlerProc) __ISUP_GetTimeoutProc_WaitOutgoingGra_ANSI92(timerID);

    case WAIT_CONTINUITY_REPORT:
        return (__ISUP_TimeoutHandlerProc)
                      __ISUP_GetTimeoutProc_WaitCotReport_ANSI92(timerID);

    case WAIT_INCOMING_COT:
        return (__ISUP_TimeoutHandlerProc)
                      __ISUP_GetTimeoutProc_WaitIncomingCot_ANSI92(timerID);

    case WAIT_COT_REPORTS_AND_CRA:
        return (__ISUP_TimeoutHandlerProc)
                      __ISUP_GetTimeoutProc_WaitCotReportAndCra_ANSI92(timerID);

    case WAIT_COT_REPORTS_HAVE_CRA:
        return (__ISUP_TimeoutHandlerProc)
                      __ISUP_GetTimeoutProc_WaitCotReportHaveCra_ANSI92(timerID);

    case WAIT_INCOMING_CRA:
        return (__ISUP_TimeoutHandlerProc)
                      __ISUP_GetTimeoutProc_WaitIncomingCra_ANSI92(timerID);

    case WAIT_INCOMING_IAM:
        return (__ISUP_TimeoutHandlerProc)
                      __ISUP_GetTimeoutProc_WaitIncomingIam_ANSI92(timerID);

    case WAIT_INCOMING_COT_AND_IAM:
        return (__ISUP_TimeoutHandlerProc)
                      __ISUP_GetTimeoutProc_WaitIncomingCotAndIam_ANSI92(timerID);

    case WAIT_OUTGOING_IAM:
        return (__ISUP_TimeoutHandlerProc)
                      __ISUP_GetTimeoutProc_WaitOutgoingIam_ANSI92(timerID);

    default:
        /* Log details of bad call */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout_ANSI92(timerID);

    }
}

ITSSS7DLLAPI __ISUP_MsgHandlerProc
__ISUP_Received_UnexpectedMsg_ANSI92(ITS_OCTET msgType)
{
    __ISUP_MsgHandlerProc handle = NULL;

    /* To be completed if needed */

    return (__ISUP_MsgHandlerProc)handle;
}

ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
__ISUP_Received_UnexpectedTimeout_ANSI92(ITS_UINT timerID)
{
    __ISUP_TimeoutHandlerProc handle = NULL;

    /* To be completed */

    return (__ISUP_TimeoutHandlerProc)handle;
}


/*
 * Functions for handling messages in the generic state for ANSI92 variant.
 * This is considered to be the generic ANSI variant, and all other ANSI variants
 * use these functions as defaults if they do not have different behaviour.
 */

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This procedure determines the controlliing exchange
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
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
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_IsExchangeControlling(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT opc, dpc;


    /* Get opc and dpc from config_info structure */
    opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
    dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);

    if ((cic_rec->cic_rule == ISUP_CKGP_CTRL_NONE) ||
       ((cic_rec->pcic.cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_EVEN))
       || (!(cic_rec->pcic.cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_ODD))
       || ((cic_rec->pcic.cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_DEF)
                                                         && (opc > dpc))
       || (!(cic_rec->pcic.cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_DEF)
                                                        && (opc < dpc)))
    {
        /* non-controlling exchange for this call (cic) */
        return ITS_FALSE;
    }
    else if ((cic_rec->cic_rule == ISUP_CKGP_CTRL_ALL) ||
            ((cic_rec->pcic.cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_ODD))
            || (!(cic_rec->pcic.cic % 2) && 
               (cic_rec->cic_rule == ISUP_CKGP_CTRL_EVEN))
            || (!(cic_rec->pcic.cic % 2) &&
               (cic_rec->cic_rule == ISUP_CKGP_CTRL_DEF) && (opc > dpc)) || ((cic_rec->pcic.cic % 2) &&
               (cic_rec->cic_rule == ISUP_CKGP_CTRL_DEF) && (opc < dpc)))
    {
        /* controlling exchange for this call (cic) */
        return ITS_TRUE;
    }

    /* Ideally it should be NEVER reach here */
    return ITS_TRUE; 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an T37 time out received is done here.
 *      The message is forwarded to the application if received from the
 *      network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3.
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
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_Received_TimeoutT37_ANSI92(ISUP_TIMER_ENTRY* t_entry,
                                ISUP_CIC_INFO *cic_rec,
                                ISUP_OPC_DPC_INFO *config_info)
{
    if (config_info->remote_isup_stat == ISUP_REMOTE_AVAILABLE)
    {
        /* FIXME : we never stop the T37 timer */
        return ;
    }
    ISUP_Alarm_ANSI(3054, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                    ISUP_PCIC_TO_CIC(cic_rec->pcic));

    /* Resend CVT */
    SPRC_SendCVTToMTP3_ANSI(cic_rec,config_info);

    /* If T37 expires the procedure is re started (T1.113 95 2.1OA.l) */
    if (__ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T37,
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T37].tmr_value) !=
 ITS_SUCCESS)
    {
        ISUP_ERROR(("ITS_ISUP_TIMER_T37 :Failed to start T37. pcic 0x%08x,"
                    " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an TACCr time out received is done here.
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
 ****************************************************************************/
static void
__ISUP_Received_TimeoutTACCr(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    /* Remove info about timer from cic_rec */
    ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_TACCR);

    /* Send the indication to the application to remove the 
    * congestion control
    */
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

    /* Raise an Alarm */

    ISUP_Alarm_ANSI(3055, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                     MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                     MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));
}

/*.implementation
 ****************************************************************************
 *  Purpose:
 *      The processing for an INF received.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3.
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
 *      Procedure implemented as per Q.764 (03/93) Sec. 2.1.6.
 *
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_CPC_Received_INF(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received INF from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Stop timer T33, if response of INR;(solicitated) */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T33);

        /* Forward INF to app */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

        /* State remains same */
    }
    else
    {
        ISUP_DEBUG(("Received INF from App, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Forward INF to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

        /* State remains same */
    }
}

/*.implementation
 ****************************************************************************
 *  Purpose:
 *      The processing for an INR received.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3.
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
 *      Procedure implemented as per Q.764 (03/93) Sec. 2.1.6.
 *
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_CPC_Received_INR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{

    int ret = ITS_SUCCESS;

    if (src == ISUP_SRC_L3_ANSI)
    {

        ISUP_DEBUG(("Received INR from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to app */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

        /* No State Change */
    }
    else
    {
        ISUP_DEBUG(("Received INR from App, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Start timer T33 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T33,
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T33].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("Received INR: Failed to start T33. pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));
        }

        /* Forward INR to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

        /* No State Change */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an T33 time out received is done here.
 *      The message is forwarded to the application if received from the
 *      network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3.
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
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_Received_TimeoutT33_ANSI92(ISUP_TIMER_ENTRY* t_entry,
                                ISUP_CIC_INFO *cic_rec,
                                ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT33 event received"
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    ISUP_Alarm_ANSI(3051, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                            ISUP_PCIC_TO_CIC(cic_rec->pcic));

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T33);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT33: Unable to remove T33 info"
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T33].tmr_hndl_layer
        == ISUP_TMR_HNDL_STACK)
    {
        /* Send REL to L3 */
        SPRC_SendRELToMTP3_ANSI(CI_CAUSE_RECOVERY_ON_TIMER_EXPIRY,
                                 cic_rec,
                                 config_info);

        /* Start Timers T1, T5 */
        __ISUP_StartRELTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }
    else
    {
        /* Change state to WAIT_OUTGOING_REL: App to release call */
        cic_rec->fsm_state = WAIT_OUTGOING_REL;
    }

    /*
     * Send the timeout data to user app.
     * This will be done whether the procedure is automated or not.
     */
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
}
