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
 *  ID: $Id: ansi-idle_ansi95.c,v 1.1.1.1 2007-10-08 11:12:18 bsccs2 Exp $
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
 * LOG: Revision 9.2  2005/04/06 06:39:10  ssingh
 * LOG: ISUP Bug Fix propagation. BugId #389 (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:56  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.7  2005/03/21 13:54:02  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.1.6.1.12.2  2005/02/08 12:19:16  ssingh
 * LOG: Peg increament after receiving Unexpected Msg in given FSM state.
 * LOG: Bug# 1448.
 * LOG: (Ramesh KV, Abhijit Dutta)
 * LOG:
 * LOG: Revision 7.5.2.1.6.1.12.1  2004/12/29 14:41:07  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.5.2.1.6.1  2004/01/05 10:10:45  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.5.2.1.2.1  2003/09/13 06:35:40  akumar
 * LOG: Msg based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 7.5.2.1  2003/05/07 10:49:27  ssingh
 * LOG: Latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.5  2003/05/06 13:58:51  sswami
 * LOG: Alarm related changes :opc information included.
 * LOG:
 * LOG: Revision 8.4  2003/04/28 15:09:07  sjaddu
 * LOG: Removed EVEN TERM every thing is taken care.
 * LOG:
 * LOG: Revision 8.3  2003/04/24 14:05:45  sswami
 * LOG: Bug# 317; Alarm Enhancement related changes done.
 * LOG:
 * LOG: Revision 8.2  2003/04/16 06:51:58  akumar
 * LOG: ITS_EVENT_TERM Added, to avoid mem leak, ISUP_ERROR() modified for print.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:28  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.5  2002/12/06 05:43:32  akumar
 * LOG: Removed unwanted TABS
 * LOG:
 * LOG: Revision 7.4  2002/11/20 13:03:24  akumar
 * LOG: Worked on ALARMS indentation
 * LOG:
 * LOG: Revision 7.3  2002/11/12 04:52:29  akumar
 * LOG: Added ANSI ISUP Alarms
 * LOG:
 * LOG: Revision 7.2  2002/10/30 04:58:56  ssingh
 * LOG: Replace ITU with ANSI for FAC and unexpected msg.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:49  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/04 00:21:46  hbalimid
 * LOG: Typos fixed in all the files.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/03 23:00:57  hbalimid
 * LOG: ANSI95 specific.
 * LOG:
 *****************************************************************************/


#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>

#include <ansi/isup_95.h>

#include "ansi-isup_95_intern.h"

/*
 * Functions for handling messages in the Idle state for ANSI95 variant.
 * This is considered to be the generic ANSI variant, and all other ANSI variants
 * use these functions as defaults if they do not have different behaviour.
 */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an FAC received in the IDLE state
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
__ISUP_Received_FAC(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward FAC appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received FAC in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to app */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

        /* Change state to IDLE */
    }
    else
    {
        ISUP_DEBUG(("Received FAC in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

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
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from MTP3 in IDLE. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n",
                    msg->data[sizeof(MTP3_HEADER_ANSI) + sizeof (ITS_USHORT) +
                    sizeof(ITS_OCTET)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));
        /* Could print out mtp3 header or entire ITS_EVENT */
        
        PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);
        
        ISUP_Alarm_ANSI(3139, __FILE__, __LINE__, "dpc: %d opc: %d "
                       "cic: %x  Message: %x",
                       MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                       MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                       ISUP_PCIC_TO_CIC(cic_rec->pcic),
                       msg->data[sizeof(MTP3_HEADER_ANSI) + 
                       sizeof(ITS_USHORT) + sizeof(ITS_OCTET)]);
    }
    else
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from App in IDLE. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n",
                    msg->data[sizeof(MTP3_HEADER_ANSI) + sizeof (ITS_USHORT) +
                    sizeof(ITS_OCTET)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));

        ISUP_Alarm_ANSI(3140, __FILE__, __LINE__, "Message %x cic : %x",
                         msg->data[sizeof(MTP3_HEADER_ANSI) + 
                         sizeof(ITS_USHORT) + sizeof(ITS_OCTET)],
                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

        /* Send error indication to application. */
        SPRC_SendErrorToApp_ANSI(msg->data[sizeof(MTP3_HEADER_ANSI) +
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
__ISUP_GetMsgProc_Idle_ANSI95(ITS_OCTET msgType)
{
    switch(msgType)
    {
    case ISUP_MSG_ACM:
        break;
    case ISUP_MSG_ANM:
        break;
    case ISUP_MSG_CFN:
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

    case ISUP_MSG_CRA:
        break;
    case ISUP_MSG_CRM:
        break;
    case ISUP_MSG_CVR:
        break;
    case ISUP_MSG_CVT:
        break;
    case ISUP_MSG_EXM:
        break;

    case ISUP_MSG_FAC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_FAC;

    default:
        /*
         * Unknown message type for ISUP.
         * Send back Confusion message.
         */
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg;
    }
    return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg;
}
