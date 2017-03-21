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
 *  ID: $Id: itu-idle_itu97.c,v 1.1.1.1 2007-10-08 11:12:19 bsccs2 Exp $
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
 * LOG: Revision 9.2  2005/04/06 06:51:03  ssingh
 * LOG: ISUP Bug Fix propagation. BugId #389 (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:01  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:54:12  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.4.1.6.1.12.2  2005/02/08 12:43:49  ssingh
 * LOG: Peg increament after receiving Unexpected Msg in given FSM state.
 * LOG: Bug# 1448. (Ramesh KV, Abhijit Dutta)
 * LOG:
 * LOG: Revision 7.2.4.1.6.1.12.1  2004/12/29 14:58:44  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.2.4.1.6.1  2004/01/05 10:10:46  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.2.4.1.2.1  2003/09/05 09:50:42  akumar
 * LOG: Modifications for msg based redundancy scheme.
 * LOG:
 * LOG: Revision 7.2.4.1  2003/05/07 11:05:31  ssingh
 * LOG: Latest Changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:31  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.2  2002/10/10 11:04:56  sjaddu
 * LOG: Added ITU Alarms.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/08/01 15:57:50  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.2.2.1  2002/07/03 19:35:16  hbalimid
 * LOG: Added/modified for wait_outgoing_gra.
 * LOG:
 * LOG: Revision 1.2  2002/06/19 15:52:00  hbalimid
 * LOG: Accomodated Msg Procs for LOP in all state machines
 * LOG:
 * LOG: Revision 1.1  2002/06/18 22:23:32  hbalimid
 * LOG: LOP Handling in Idle
 * LOG:
 *
 *****************************************************************************/

#undef ANSI
#undef CCITT
#define CCITT

#include <its.h>

#include <itu/isup_97.h>

#include "itu-isup_97_intern.h"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an LOP received in the IDLE state
 *      is done here. The message is forwarded to the application if received
 *      from the network, or vice versa.
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
static void
__ISUP_Received_LOP(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward LOP appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received LOP in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

        /* Change state to IDLE */
    }
    else
    {
        ISUP_DEBUG(("Received LOP in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* Change state to IDLE */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing of a message not expected in
 *      the IDLE state. It also serves as a default handler for
 *      any errors arising from out-of-range function calls.
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BugId: 389     Added Message type in the
 *                                          Error indication to application.
 *
 ****************************************************************************/
static void
__ISUP_Received_UnexpectedMsg(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                              ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Log error, update stats and drop msg */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from MTP3 in IDLE. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n",
                    msg->data[sizeof(MTP3_HEADER_CCITT) + sizeof (ITS_USHORT)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));
        /* Could print out mtp3 header or entire ITS_EVENT */
        
        PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);
        
        ISUP_Alarm_CCITT(3481, __FILE__, __LINE__, "pcic %x", cic_rec->pcic);
    }
    else
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from App in IDLE. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n",
                    msg->data[sizeof(MTP3_HEADER_CCITT) + sizeof (ITS_USHORT)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));

        /* Send error indication to application. */
        SPRC_SendErrorToApp_CCITT(msg->data[sizeof(MTP3_HEADER_CCITT) +
                                 sizeof (ITS_USHORT) + sizeof(ITS_OCTET)],
                                 ITS_ISUP_UNEXP_APPMSG_IDLE_ERR,
                                 cic_rec);
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a valid pointer to a message handler function
 *      for the IDLE state, based on the msgType received.
 *
 *  Input Parameters:
 *      msgType: the type of the message received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Pointer to a message handler function.
 *
 ****************************************************************************/
__ISUP_MsgHandlerProc
__ISUP_GetMsgProc_Idle_ITU97(ITS_OCTET msgType)
{
    switch(msgType)
    {
    case ISUP_MSG_ACM:
        break;
    case ISUP_MSG_ANM:
        break;
    case ISUP_MSG_CFN:
        break;
    case ISUP_MSG_CON:
        break;
    case ISUP_MSG_SAM:
        break;
    case ISUP_MSG_CPG:
        break;
    case ISUP_MSG_IAM:
        break;
    case ISUP_MSG_REL:
        break;
    case ISUP_MSG_RLC:
        break;
    case ISUP_MSG_RSC:
        break;
    case ISUP_MSG_UCIC:
        break;

    case ISUP_MSG_BLO:
        break;
    case ISUP_MSG_BLA:
        break;
    case ISUP_MSG_CGB:
        break;
    case ISUP_MSG_CGBA:
        break;
    case ISUP_MSG_CQM:
        break;

    case ISUP_MSG_CQR:
        break;
    case ISUP_MSG_GRS:
        break;
    case ISUP_MSG_GRA:
        break;
    case ISUP_MSG_CGU:
        break;
    case ISUP_MSG_CGUA:
        break;
    case ISUP_MSG_COT:
        break;
    case ISUP_MSG_CCR:
        break;

    case ISUP_MSG_FOT:
        break;
    case ISUP_MSG_INF:
        break;
    case ISUP_MSG_INR:
        break;
    case ISUP_MSG_LPA:
        break;
    case ISUP_MSG_PAM:
        break;
    case ISUP_MSG_RES:
        break;
    case ISUP_MSG_SUS:
        break;
    case ISUP_MSG_UBL:
        break;
    case ISUP_MSG_UBA:
        break;
    case ISUP_MSG_CRG:
        break;
    case ISUP_MSG_FAC:
        break;
    case ISUP_MSG_FAA:
        break;
    case ISUP_MSG_FRJ:
        break;
    case ISUP_MSG_FAR:
        break;
    case ISUP_MSG_IDR:
        break;
    case ISUP_MSG_IRS:
        break;
    case ISUP_MSG_NRM:
        break;
    case ISUP_MSG_OLM:
        break;
    case ISUP_MSG_SGM:
        break;
    case ISUP_MSG_UPA:
        break;
    case ISUP_MSG_UPT:
        break;
    case ISUP_MSG_USR:
        break;

    case ISUP_MSG_LOP:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_LOP;

    default:
        /* Unexpected message type for ISUP.
         * Send back Confusion message ?
         */
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg;
    }
    return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a message handler procedure,
 *      based on the msgType and state of the CIC. This is the main function
 *      for the ITU ISUP 97 variant (ITU97) message handling procedures.
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
__ISUP_MsgHandlerProc
__ISUP_GetMsgHandler_ITU97(ITS_OCTET msgType, ITS_ISUP_STATE state)
{
    switch(state)
    {
    /*
     * This should be called only after verifying that the msgType is correct.
     */
    case IDLE:
        return __ISUP_GetMsgProc_Idle_ITU97(msgType);

    /* IAM sent to network, waiting for ACM. */
    case WAIT_INCOMING_ACM:
        return __ISUP_GetMsgProc_WaitIncomingAcm_ITU97(msgType);

    /* ACM sent to network, waiting for ANM. */
    case WAIT_INCOMING_ANM:
        return __ISUP_GetMsgProc_WaitIncomingAnm_ITU97(msgType);

    /* ANM rcvd from network, call established. */
    case RCVD_INCOMING_ANM:
        return __ISUP_GetMsgProc_RcvdIncomingAnm_ITU97(msgType);

    /* REL sent to network, waiting for RLC. */
    case WAIT_INCOMING_RLC:
        return __ISUP_GetMsgProc_WaitIncomingRlc_ITU97(msgType);

    /* SUS rcvd from network, call suspended, waiting for RES. */
    case WAIT_INCOMING_RES:
        return __ISUP_GetMsgProc_WaitIncomingRes_ITU97(msgType);

    /* IAM rcvd from network, waiting to send ACM. */
    case WAIT_OUTGOING_ACM:
        return __ISUP_GetMsgProc_WaitOutgoingAcm_ITU97(msgType);

    /* ACM rcvd from network, waiting to send ANM. */
    case WAIT_OUTGOING_ANM:
        return __ISUP_GetMsgProc_WaitOutgoingAnm_ITU97(msgType);

    /* ANM sent to network, call established. */
    case SENT_OUTGOING_ANM:
        return __ISUP_GetMsgProc_SentOutgoingAnm_ITU97(msgType);

    /* REL rcvd from network, waiting to send RLC. */
    case WAIT_OUTGOING_RLC:
        return __ISUP_GetMsgProc_WaitOutgoingRlc_ITU97(msgType);

    /* SUS sent to network, call suspended, waiting to send RES to network. */
    case WAIT_OUTGOING_RES:
        return __ISUP_GetMsgProc_WaitOutgoingRes_ITU97(msgType);

    /* Timeout/error, waiting to send REL to network. */
    case WAIT_OUTGOING_REL:
        return __ISUP_GetMsgProc_WaitOutgoingRel_ITU97(msgType);

    /* Timeout/error, waiting to send RSC to network. */
    case WAIT_OUTGOING_RSC:
        return (__ISUP_MsgHandlerProc)
                   __ISUP_GetMsgProc_WaitOutgoingRsc_ITU97(msgType);

    /* Timeout/error, waiting to send GRA to network. */
    case WAIT_OUTGOING_GRA:
        return (__ISUP_MsgHandlerProc)
                   __ISUP_GetMsgProc_WaitOutgoingGra_ITU97(msgType);

    default:
        /* Log error in call */
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg;
    }
}

