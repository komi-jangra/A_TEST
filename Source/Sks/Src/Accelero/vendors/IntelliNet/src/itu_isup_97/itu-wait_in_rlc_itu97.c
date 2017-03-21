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
 *  ID: $Id: itu-wait_in_rlc_itu97.c,v 1.1.1.1 2007-10-08 11:12:20 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:55  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:13  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2  2005/04/06 06:51:03  ssingh
 * LOG: ISUP Bug Fix propagation. BugId #389 (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:01  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:54:13  cvsadmin
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
 * LOG: Revision 7.2.4.1.2.1  2003/09/05 09:51:57  akumar
 * LOG: Modifications for msg based redundancy scheme.
 * LOG:
 * LOG: Revision 7.2.4.1  2003/05/07 11:05:32  ssingh
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
 * LOG: Revision 1.1  2002/06/18 22:19:35  hbalimid
 * LOG: LOP handling in Wait_In_RLC
 * LOG:
 *
 *****************************************************************************/

#undef ANSI
#undef CCITT
#define CCITT

#include <its.h>

#include <itu/isup_97.h>


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an LOP received in the WAIT_INCOMING_RLC state
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
        ISUP_DEBUG(("Received LOP in WAIT_IN_RLC from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

        /* Change state to WAIT_INCOMING_RLC */
    }
    else
    {
        ISUP_DEBUG(("Received LOP in WAIT_IN_RLC from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* Change state to WAIT_INCOMING_RLC */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing of a message not expected in
 *      the WAIT_INCOMING_RLC state. It also serves as a default handler for
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
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from MTP3 in WAIT_IN_RLC. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n",
                    msg->data[sizeof(MTP3_HEADER_CCITT) + sizeof (ITS_USHORT)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));
        /* Could print out mtp3 header or entire ITS_EVENT */

        PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);

        ISUP_Alarm_CCITT(3481, __FILE__, __LINE__, "pcic %x", cic_rec->pcic);
    }
    else
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from App in WAIT_IN_RLC. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n",
                    msg->data[sizeof(MTP3_HEADER_CCITT) + sizeof (ITS_USHORT)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));

        /* Send error indication to application. */
        SPRC_SendErrorToApp_CCITT(msg->data[sizeof(MTP3_HEADER_CCITT) +
                                 sizeof (ITS_USHORT) + sizeof(ITS_OCTET)],
                                 ITS_ISUP_UNEXP_APPMSG_WAITINC_RLC_ERR,
                                 cic_rec);
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a valid pointer to a message handler function
 *      for the WAIT_INCOMING_RLC state, based on the msgType received.
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
__ISUP_GetMsgProc_WaitIncomingRlc_ITU97(ITS_OCTET msgType)
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

