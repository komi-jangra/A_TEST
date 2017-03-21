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
 *  ID: $Id: ansi-generic_state_ansi95.c,v 1.1.1.1 2007-10-08 11:12:18 bsccs2 Exp $
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
 * LOG: Revision 8.3  2005/03/21 13:54:02  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.1  2003/05/07 10:49:27  ssingh
 * LOG: Latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.2  2003/03/15 13:02:22  ssingh
 * LOG: Changes done to support CRM/CRA messaging for ANSI
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:28  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.2  2002/12/02 04:06:14  sjaddu
 * LOG: Handling of continuity in 95
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/08/16 19:59:41  ssingh
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:49  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/06 06:12:53  hbalimid
 * LOG: Took care of all warnings.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/03 18:17:18  hbalimid
 * LOG: generic state for ANSI95.
 * LOG:
 *
 *****************************************************************************/

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>

#include <ansi/isup.h>
#include <isup_intern.h>

#include <ansi/isup_95.h>

#include "ansi-isup_95_intern.h"


/* Common Get Message Handlers
 * These are used to return state specific
 * message procs.
 */


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a message handler procedure, 
 *      based on the msgType and state of the CIC. This is the main function
 *      for the ANSI ISUP generic variant (ANSI95) message handling procedures. 
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
__ISUP_GetMsgHandler_ANSI95(ITS_OCTET msgType, ITS_ISUP_STATE state)
{
    switch(state)
    {
    /* 
     * This should be called only after verifying that the msgType is correct.
     */
    case IDLE:
        return __ISUP_GetMsgProc_Idle_ANSI95(msgType);

    /* IAM sent to network, waiting for ACM. */
    case WAIT_INCOMING_ACM:
        return __ISUP_GetMsgProc_WaitIncomingAcm_ANSI95(msgType);

    /* ACM sent to network, waiting for ANM. */
    case WAIT_INCOMING_ANM:
        return __ISUP_GetMsgProc_WaitIncomingAnm_ANSI95(msgType);

    /* ANM rcvd from network, call established. */
    case RCVD_INCOMING_ANM: 
        return __ISUP_GetMsgProc_RcvdIncomingAnm_ANSI95(msgType);

    /* REL sent to network, waiting for RLC. */
    case WAIT_INCOMING_RLC: 
        return __ISUP_GetMsgProc_WaitIncomingRlc_ANSI95(msgType);

    /* SUS rcvd from network, call suspended, waiting for RES. */
    case WAIT_INCOMING_RES: 
        return __ISUP_GetMsgProc_WaitIncomingRes_ANSI95(msgType);

    /* IAM rcvd from network, waiting to send ACM. */
    case WAIT_OUTGOING_ACM: 
        return __ISUP_GetMsgProc_WaitOutgoingAcm_ANSI95(msgType);

    /* ACM rcvd from network, waiting to send ANM. */
    case WAIT_OUTGOING_ANM:     
        return __ISUP_GetMsgProc_WaitOutgoingAnm_ANSI95(msgType);

    /* ANM sent to network, call established. */
    case SENT_OUTGOING_ANM: 
        return __ISUP_GetMsgProc_SentOutgoingAnm_ANSI95(msgType);

    /* REL rcvd from network, waiting to send RLC. */
    case WAIT_OUTGOING_RLC: 
        return __ISUP_GetMsgProc_WaitOutgoingRlc_ANSI95(msgType);

    /* SUS sent to network, call suspended, waiting to send RES to network. */
    case WAIT_OUTGOING_RES: 
        return __ISUP_GetMsgProc_WaitOutgoingRes_ANSI95(msgType);

    /* Timeout/error, waiting to send REL to network. */
    case WAIT_OUTGOING_REL: 
        return __ISUP_GetMsgProc_WaitOutgoingRel_ANSI95(msgType);

    /* Timeout/error, waiting to send RSC to network. */
    case WAIT_OUTGOING_RSC: 
        return (__ISUP_MsgHandlerProc)
                   __ISUP_GetMsgProc_WaitOutgoingRsc_ANSI95(msgType);

    case WAIT_OUTGOING_GRA:
        return (__ISUP_MsgHandlerProc)
                   __ISUP_GetMsgProc_WaitOutgoingGra_ANSI95(msgType);

    case WAIT_CONTINUITY_REPORT:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitCotReport_ANSI95(msgType);

    case WAIT_INCOMING_COT:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitIncomingCot_ANSI95(msgType);

    case WAIT_COT_REPORTS_AND_CRA:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitCotReportAndCra_ANSI95(msgType);

    case WAIT_COT_REPORTS_HAVE_CRA:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitCotReportHaveCra_ANSI95(msgType);

    case WAIT_INCOMING_CRA:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitIncomingCra_ANSI95(msgType);

    case WAIT_INCOMING_IAM:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitIncomingIam_ANSI95(msgType);

    case WAIT_INCOMING_COT_AND_IAM:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitIncomingCotAndIam_ANSI95(msgType);

    case WAIT_OUTGOING_IAM:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitOutgoingIam_ANSI95(msgType);

    default:
        /* Log error in call */
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg_ANSI95(msgType);
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a timeout handler procedure, 
 *      based on the msgType and state of the CIC. This is the main function
 *      for the ANSI ISUP generic variant (ANSI95) timeout handling procedures.
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
__ISUP_TimeoutHandlerProc
__ISUP_GetTimeoutHandler_ANSI95(ITS_UINT timerID, ITS_ISUP_STATE state)
{
    __ISUP_TimeoutHandlerProc handler = NULL;

    /* To be implemented if needed */
    return (__ISUP_TimeoutHandlerProc)handler;
}
__ISUP_MsgHandlerProc
__ISUP_Received_UnexpectedMsg_ANSI95(ITS_OCTET msgType)
{
    __ISUP_MsgHandlerProc handler = NULL;

    /* To be implemented if needed */
    return (__ISUP_MsgHandlerProc)handler;
}

__ISUP_TimeoutHandlerProc
__ISUP_Received_UnexpectedTimeout_ANSI95(ITS_UINT timerID)
{
    __ISUP_TimeoutHandlerProc handler = NULL;

    /* To be implemented if needed */
    return (__ISUP_TimeoutHandlerProc)handler;
}


/*
 * Functions for handling messages in the generic state for ANSI95 variant.
 * This is considered to be the generic ANSI variant, and all other ANSI variants
 * use these functions as defaults if they do not have different behaviour.
 */

 /* FOR ANY FURTHER ADDITIONS */
