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
 *  ID: $Id: itu-idle_itu93.c,v 1.1.1.1 2007-10-08 11:12:18 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:53  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:11  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.3  2005/05/05 09:26:24  ssingh
 * LOG: fix for bug #1736.
 * LOG:
 * LOG: Revision 9.2  2005/04/08 07:12:27  ssingh
 * LOG: ISUP bug fix propagation (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:57  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.12  2005/03/21 13:54:06  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.6.2.4.6.1.12.2  2005/02/08 12:30:26  ssingh
 * LOG: Peg increament after receiving Unexpected Msg in given FSM state.
 * LOG: Bug# 1448. (Ramesh KV, Abhijit Dutta)
 * LOG:
 * LOG: Revision 7.6.2.4.6.1.12.1  2004/12/29 14:56:04  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.6.2.4.6.1  2004/01/05 10:10:45  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.6.2.4.2.3  2003/11/24 06:40:44  akumar
 * LOG: bug fix cycle.
 * LOG:
 * LOG: Revision 7.6.2.4.2.2  2003/11/13 13:17:49  akumar
 * LOG: Bug fixing cycle for TCS-ISUP.
 * LOG:
 * LOG: Revision 7.6.2.4.2.1  2003/09/05 09:44:02  akumar
 * LOG: Modifications for Msg Based redundancy scheme.
 * LOG:
 * LOG: Revision 7.6.2.4  2003/07/25 05:11:42  akumar
 * LOG: ITU National Matter is implemented.
 * LOG:
 * LOG: Revision 7.6.2.3  2003/06/13 03:21:05  akumar
 * LOG: Fixed BUG #376.
 * LOG:
 * LOG: Revision 7.6.2.2  2003/05/07 11:03:12  ssingh
 * LOG: Latest Changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.4  2003/05/02 14:36:17  ssingh
 * LOG: ANSI changes propped to ITU (common and related).
 * LOG:
 * LOG: Revision 8.3  2003/04/30 05:19:02  akumar
 * LOG: Bug Fix #256. Test call procedure done.
 * LOG:
 * LOG: Revision 8.2  2003/04/03 15:29:29  sjaddu
 * LOG: ISUP DSM reorganization.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:30  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.6  2003/02/05 18:55:29  sjaddu
 * LOG: Fixed new line strings errors compiled with cc.
 * LOG:
 * LOG: Revision 7.5  2003/02/04 09:25:18  akumar
 * LOG: Fixed Error in DEBUG print cropping up with CC compiler
 * LOG:
 * LOG: Revision 7.4  2003/01/22 07:32:10  akumar
 * LOG: Added ITU COT procedure
 * LOG:
 * LOG: Revision 7.3  2002/12/31 05:36:16  akumar
 * LOG: Segmentation Procedure has been added
 * LOG:
 * LOG: Revision 7.2  2002/10/10 10:40:12  sjaddu
 * LOG: Added Alarms for ITU93/97.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/08/01 15:57:49  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 6.5  2002/07/05 21:27:56  ssharma
 * LOG: Fix Linux warnings.
 * LOG:
 * LOG: Revision 6.4.2.4  2002/07/31 22:26:06  ssharma
 * LOG: ITU pegs.
 * LOG:
 * LOG: Revision 6.4.2.3  2002/07/24 20:13:35  ssingh
 * LOG: Done changes in receiving IAM from Application.
 * LOG:
 * LOG: Revision 6.4.2.2  2002/07/10 19:34:16  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.4.2.1  2002/07/06 20:06:42  hbalimid
 * LOG: Fixed all warnings.
 * LOG:
 * LOG: Revision 6.4  2002/06/24 17:00:44  ssingh
 * LOG: Phase 3 missing functionality and auto timer handling.
 * LOG:
 * LOG: Revision 6.3  2002/05/20 15:49:09  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 1.8.2.18  2002/05/14 18:12:17  sjaddu
 * LOG: Added MTP3 Indications.
 * LOG:
 * LOG: Revision 1.8.2.17  2002/05/09 18:38:10  labuser
 * LOG: Merge from ISUP_APR_19_2002 branch to PR6.
 * LOG:
 * LOG: Revision 1.8.2.16.2.3  2002/05/02 22:29:36  labuser
 * LOG: IAM on a locally blocked circuit is allowed. BugId 45
 * LOG:
 * LOG: Revision 1.8.2.16.2.2  2002/04/29 16:46:40  labuser
 * LOG: reset the BLR state to idle for incoming RLC
 * LOG:
 * LOG: Revision 1.8.2.16.2.1  2002/04/27 02:09:19  labuser
 * LOG: added check for the RBLOCK in incoming IAM procedure
 * LOG:
 * LOG: Revision 1.8.2.16  2002/04/18 18:58:17  ssanyal
 * LOG: compilation changes after ANSI/ITU reorg. within IntelliSS7 ISUP
 * LOG:
 * LOG: Revision 1.8.2.15  2002/04/05 19:37:44  ssharma
 * LOG: Add parameter to timeout handling procedures.
 * LOG:
 * LOG: Revision 1.8.2.14  2002/04/02 23:53:54  ssharma
 * LOG: Completion of phase 2, coding standards conformance.
 * LOG:
 * LOG: Revision 1.8.2.13  2002/04/01 21:08:02  ssharma
 * LOG: Fix memory leaks in ISUP_FindXX() functions.
 * LOG:
 * LOG: Revision 1.8.2.12  2002/03/28 20:21:07  ssharma
 * LOG: Add CSC file, Reorganize code to separate CSC code to a file.
 * LOG:
 * LOG: Revision 1.8.2.11  2002/03/26 22:10:37  ssharma
 * LOG: More changes for CGRS, CGRR.
 * LOG:
 * LOG: Revision 1.8.2.10  2002/03/22 16:24:12  ssharma
 * LOG: Warning removal, CGRS related changes.
 * LOG:
 * LOG: Revision 1.8.2.9  2002/03/19 18:08:28  ssharma
 * LOG: Bug fix (FindPcic resulting in 5 second timeout).
 * LOG:
 * LOG: Revision 1.8.2.8  2002/03/19 17:38:56  ssharma
 * LOG: Bug fixes.
 * LOG:
 * LOG: Revision 1.8.2.7  2002/03/19 17:24:35  ssharma
 * LOG: Circuit reset state machines.
 * LOG:
 * LOG: Revision 1.8.2.6  2002/03/14 22:59:06  ssharma
 * LOG: Implement HGBS, HGBR, HLB and HRB
 * LOG:
 * LOG: Revision 1.8.2.5  2002/03/14 15:31:05  ssharma
 * LOG: Change signature of Validate_RangeStatus, add CSC state machines.
 * LOG:
 * LOG: Revision 1.8.2.4  2002/03/07 20:12:48  ssharma
 * LOG: Factor out timer related code into a common file.
 * LOG:
 * LOG: Revision 1.8.2.3  2002/03/05 21:26:58  ssharma
 * LOG: Validate range and status parameter.
 * LOG:
 * LOG: Revision 1.8.2.2  2002/03/05 14:54:02  ssharma
 * LOG: Add new file that contains parameter level validation functions.
 * LOG:
 * LOG: Revision 1.8.2.1  2002/03/04 20:25:20  ssharma
 * LOG: Change printf to ISUP_DEBUG.
 * LOG:
 * LOG: Revision 1.8  2002/02/27 23:31:07  ssharma
 * LOG: Fix IAM handling as per the spec.
 * LOG:
 * LOG: Revision 1.7  2002/02/26 23:52:58  ssharma
 * LOG: Send timeout indication as a (pseudo) ISUP message.
 * LOG:
 * LOG: Revision 1.6  2002/02/26 16:41:30  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 1.5  2002/02/22 22:36:07  ssharma
 * LOG: Change signature of a function.
 * LOG:
 * LOG: Revision 1.4  2002/02/20 23:24:21  ssharma
 * LOG: Fix traces and Makefile.
 * LOG:
 * LOG: Revision 1.3  2002/02/19 23:04:07  ssharma
 * LOG: Fix traces, .ini file after functional test.
 * LOG:
 * LOG: Revision 1.2  2002/02/13 23:23:05  mmiers
 * LOG: Warning removal, debug.
 * LOG:
 * LOG: Revision 1.1  2002/02/13 18:28:33  mmiers
 * LOG: Finish off the ISUP integration.  Still need to add CHINA
 * LOG: variant lib.
 * LOG:
 * LOG: Revision 5.2  2002/02/08 21:48:16  mmiers
 * LOG: Reorg complete.
 * LOG:
 * LOG: Revision 5.1  2002/02/01 20:07:31  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/22 23:37:11  ssharma
 * LOG: New files for IntelliNet ISUP stack.
 * LOG:
 * LOG:
 *
 *****************************************************************************/


#undef ANSI
#undef CCITT
#define CCITT

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <itu/isup.h>
#include <isup_intern.h>
#include <isup_93.h>

/*
 * Functions for handling messages in the Idle state for ITU93 variant.
 * This is considered to be the generic ITU variant, and all other ITU variants
 * use these functions as defaults if they do not have different behaviour.
 */


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an BLA received in the IDLE state is done here.
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
static void
__ISUP_Received_BLA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_BLA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an BLO received in the IDLE state is done here.
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
static void
__ISUP_Received_BLO(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_BLO(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CCR received in the IDLE state is done here.
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
static void
__ISUP_Received_CCR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CCR(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGB received in the IDLE state is done here.
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
static void
__ISUP_Received_CGB(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGB(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGBA received in the IDLE state is done here.
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
static void
__ISUP_Received_CGBA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGBA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGU received in the IDLE state is done here.
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
static void
__ISUP_Received_CGU(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGU(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGUA received in the IDLE state is done here.
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
static void
__ISUP_Received_CGUA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGUA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an COT received in the IDLE state is done here.
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BugId: 389     Added Message type in the
 *                                          Error indication to application.
 ****************************************************************************/
static void
__ISUP_Received_COT(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int offset = 0, tret = 0;

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received COT in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T36);

            __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T27,
                             config_info->\
                             tmr_hndl_info[ITS_ISUP_TIMER_T27].tmr_value);

            cic_rec->cri_state = CRI_WAIT_FOR_CCR;
            if (cic_rec->cot_first_ind == ITS_TRUE)
            {
                cic_rec->cot_first_ind = ITS_FALSE;
                /* FIXME - Raise an Alarm */
            }
           /* Check for failed or success indicator */
            offset = sizeof(MTP3_HEADER_CCITT) + sizeof(ITS_USHORT) +
                     sizeof(ITS_OCTET);
            switch(msg->data[offset+1] & 0x01U)
            {
            case CONTINUITY_CHECK_SUCCESS:
                ISUP_CRITICAL((" Unexpected COT Received In Wait For REL\n"));
                break;
            case CONTINUITY_CHECK_FAILED:
                ISUP_CRITICAL((" COT Falure Received In Wait For REL\n"));
                break;
            }
        }
        else
        {
            ISUP_ERROR(("Received Unexpected COT in IDLE from MTP3,"
                         "pcic 0x%08x, vcic %d.\n",
                         cic_rec->pcic, cic_rec->vcic));
        }
    }
    else 
    {
        ISUP_DEBUG(("Received COT in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cro_state == CRO_WAIT_FOR_COT ||
            cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY) 
        {

            /* Check for failed or success indicator */
            offset = sizeof(MTP3_HEADER_CCITT) + sizeof(ITS_USHORT) +
                                                  sizeof(ITS_OCTET);

            switch(msg->data[offset+1] & 0x01U)
            {
            case CONTINUITY_CHECK_SUCCESS:
                ISUP_DEBUG(("In IDLE :COT SUCCESSFUL Received"
                            " from App. pcic 0x%08x,vcic %d.\n",
                              cic_rec->pcic, cic_rec->vcic));

                if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY)
                {
                    if (cic_rec->cot_first_ind == ITS_TRUE)
                    {
                        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
                    }
                    else
                    {
                        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
                    }
                }
                else
                {
                    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
                }

                /*Send REL */
                SPRC_SendRELToMTP3_CCITT(CI_CAUSE_NORMAL_UNSPECIFIED,
                                        cic_rec,config_info);
                __ISUP_StartRELTimers(cic_rec, config_info);

                cic_rec->cro_state = CRO_WAIT_FOR_RLC;
                cic_rec->fsm_state = WAIT_INCOMING_RLC;
                cic_rec->cot_first_ind = ITS_TRUE;
                break;
            case CONTINUITY_CHECK_FAILED:

                if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY)
                {
                    ISUP_DEBUG(("In IDLE :Unexpected COT Failure Received"
                            " from App discarding. pcic 0x%08x,vcic %d.\n",
                              cic_rec->pcic, cic_rec->vcic));

                    /* Send error indication to application. */
                    SPRC_SendErrorToApp_CCITT(ISUP_MSG_COT,
                                             ITS_ISUP_UNEXP_APPMSG_IDLE_ERR,
                                             cic_rec);
                    return;
                }

                ISUP_DEBUG(("IDLE :COT FAILURE Received"
                            " from App. pcic 0x%08x, vcic %d.\n",
                             cic_rec->pcic, cic_rec->vcic));

                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);

                if (cic_rec->cot_first_ind == ITS_TRUE)
                {
                    tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T25,
                                             config_info->\
                                             tmr_hndl_info[ITS_ISUP_TIMER_T25].\
                                             tmr_value);
                    if (tret != ITS_SUCCESS)
                    {
                        ISUP_ERROR(("IDLE: Failed to start"
                                    " T25. pcic 0x%08x, vcic %d.\n",
                                     cic_rec->pcic, cic_rec->vcic));
                    }
                    cic_rec->cot_first_ind = ITS_FALSE;
                }
                else
                {
                    ISUP_CRITICAL(("COT check failed on CIC :"
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

                    tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T26,
                                             config_info->\
                                             tmr_hndl_info[ITS_ISUP_TIMER_T26].\
                                             tmr_value);
                    if (tret != ITS_SUCCESS)
                    {
                        ISUP_ERROR(("IDLE: Failed to start"
                                    " T26. pcic 0x%08x, vcic %d.\n",
                                     cic_rec->pcic, cic_rec->vcic));
                    }
                }
                cic_rec->cro_state = CRO_WAIT_TIMER_EXPIRY;
                SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
                break;
            }
        }
        else
        {
            ISUP_ERROR(("IDLE:Received COT in invalid"
                        "state pcic 0x%08x, vcic %d.\n",
                         cic_rec->pcic, cic_rec->vcic));

            /* Send error indication to application. */
            SPRC_SendErrorToApp_CCITT(ISUP_MSG_COT,
                                     ITS_ISUP_UNEXP_APPMSG_IDLE_ERR,
                                     cic_rec);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CQM received in the IDLE state is done here.
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
static void
__ISUP_Received_CQM(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CQM(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CQR received in the IDLE state is done here.
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
static void
__ISUP_Received_CQR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CQR(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an GRA received in the IDLE state is done here.
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
static void
__ISUP_Received_GRA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_GRA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an GRS received in the IDLE state is done here.
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
static void
__ISUP_Received_GRS(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_GRS(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an IAM received in the IDLE state is done here.
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BugId: 389     Added Message type in the
 *                                          Error indication to application.
 *
 ****************************************************************************/
static void
__ISUP_Received_IAM(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int offset = 0;
    int tret = ITS_SUCCESS; 
    int app_err = ITS_SUCCESS;
    ITS_BOOLEAN testcall = ITS_FALSE;
    int discard = 0;
    int sendblo = 0;
    int sendcgb = 0;

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received IAM in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* 
         * populate testcall (part of calling party's category parameter)
         */
         if (msg->data[12] == CGP_CAT_TEST_CALL)
         {
             /* set the testcall */
             testcall = ITS_TRUE;

             ISUP_DEBUG(("Received IAM is a TEST CALL, pcic 0x%08x, vcic %d.\n",
                         cic_rec->pcic, cic_rec->vcic));
        }
        else
        {
             /* not a test call */
             testcall = ITS_FALSE;
        }

        if (!testcall)
        {
            /* Check CIC maint blocking states */
            if (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_RBLOCKED)
            {
                ISUP_CIC_SET_MAINT(cic_rec->cic_state, CKTS_ACTIVE);

                if (cic_rec->blr_state == BLR_RBLOCKED)
                {
                    cic_rec->blr_state = BLR_IDLE;
                }
            }
            else if (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LBLOCKED)
            {
                discard = 1;
                sendblo = 1;
            } 
            else if (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LRBLOCKED)
            {
                ISUP_CIC_SET_MAINT(cic_rec->cic_state, CKTS_LBLOCKED);
                discard = 1;
                sendblo = 1;

                if (cic_rec->blr_state == BLR_RBLOCKED)
                {
                    cic_rec->blr_state = BLR_IDLE;
                }
            }
    
            /* Check CIC hardware blocking states */
            if (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_RBLOCKED)
            {
                ISUP_CIC_SET_HDW(cic_rec->cic_state, CKTS_ACTIVE);

                if (cic_rec->hrb_state == HRB_RBLOCKED)
                {
                    cic_rec->hrb_state = HRB_IDLE;
                }
            } 
            else if (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LBLOCKED)
            {
                discard = 1;
                sendcgb = 1;
            } 
            else if (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LRBLOCKED)
            {
                ISUP_CIC_SET_HDW(cic_rec->cic_state, CKTS_LBLOCKED);
                discard = 1;
                sendcgb = 1;

                if (cic_rec->hrb_state == HRB_RBLOCKED)
                {
                    cic_rec->hrb_state = HRB_IDLE;
                }
            } 
        }
        
        if (discard == 1)
        {
            ISUP_Alarm_CCITT(3478, __FILE__, __LINE__, "pcic %x",
                                                      cic_rec->pcic);

            ISUP_ERROR(("Discarding incoming IAM message due to maintenance "
                        "and/or hardware blocking, pcic 0x%08x, vcic %d\n",
                        cic_rec->pcic, cic_rec->vcic));

            if (sendblo == 1)
            {
                ISUP_DEBUG(("Sending BLO\n"));

                SPRC_SendBLOToMTP3_CCITT(cic_rec, config_info);
    
                __ISUP_StartBLOTimers(cic_rec, config_info);

                cic_rec->bls_state = BLS_WAIT_FOR_BLA;
            }

            if (sendcgb == 1)
            {
                ISUP_DEBUG(("Sending CGB\n"));

                SPRC_SendHWBToMTP3_CCITT(cic_rec, config_info);
    
                __ISUP_StartCGBTimers(cic_rec, config_info);
                
                cic_rec->bls_state = BLS_WAIT_FOR_BLA;
            }
            return;
        }
        else
        {
            /* Mark CIC as incoming_busy */
            ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IN_CTK_BUSY);

            if(cic_rec->cro_state != CRO_IDLE)
            {
                if(cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY)
                {
                    if (cic_rec->cot_first_ind == ITS_TRUE)
                    {
                        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
                    }
                    else
                    {
                        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
                    }

                    cic_rec->cro_state = CRO_IDLE;
                    cic_rec->cot_first_ind = ITS_TRUE;
                    ISUP_ClearCic(cic_rec);
                }
                else if (cic_rec->cro_state == CRO_WAIT_FOR_COT)
                {
                    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
                    cic_rec->cro_state = CRO_IDLE;
                    cic_rec->cot_first_ind = ITS_TRUE;
                    ISUP_ClearCic(cic_rec);
                }
            }

            if (cic_rec->cri_state != CRI_IDLE)
            {
                if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
                {
                    cic_rec->cri_state = CRI_IDLE;
                    cic_rec->cot_first_ind = ITS_TRUE;
                    ISUP_ClearCic(cic_rec);
                }
                else if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
                {
                    __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T36);
                    cic_rec->cri_state = CRI_IDLE;
                    cic_rec->cot_first_ind = ITS_TRUE;
                }
            }
            offset = sizeof(MTP3_HEADER_CCITT) + sizeof(ITS_USHORT) +
                                                   sizeof(ITS_OCTET);

            switch((msg->data[offset+1] >> 2) & 0x03U)
            {
            case NCI_CHECK_NOT_REQUIRED:

                /* Change state to WAIT_OUTGOING_ACM - Wait for OGC Complete */
                /* Here we directly jump to Wait for OGC Complete */
                cic_rec->fsm_state = WAIT_OUTGOING_ACM;
                break;

            case NCI_CHECK_CKT_REQUIRED:
            case NCI_CHECKED_PREV_CKT:

                ISUP_DEBUG(("Received IAM with COT chk, pcic 0x%08x,vcic %d.\n",
                             cic_rec->pcic, cic_rec->vcic));

                /* Start Timer T8 */
                tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T8,
                   config_info->tmr_hndl_info[ITS_ISUP_TIMER_T8].
                                                                    tmr_value);
                if (tret != ITS_SUCCESS)
                {
                    ISUP_ERROR(("IDLE IAM: Failed to start T8"
                                "pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                }

                /* Change CCI state to Wait for COT */
                cic_rec->cci_state = CCI_WAIT_FOR_COT;

                /* Change state to Wait for continuity report */
                cic_rec->fsm_state = WAIT_INCOMING_COT;

                break;
            default :
                cic_rec->fsm_state = WAIT_OUTGOING_ACM;
                break;
            }

            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
        }
    }
    else
    {
        ISUP_DEBUG(("Received IAM in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if(cic_rec->cro_state != CRO_IDLE)
        {
            if(cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY)
            {
                if (cic_rec->cot_first_ind == ITS_TRUE)
                {
                    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
                }
                else
                {
                    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
                }

                cic_rec->cro_state = CRO_IDLE;
                cic_rec->cot_first_ind = ITS_TRUE;
                ISUP_ClearCic(cic_rec);
            }
            else if (cic_rec->cro_state == CRO_WAIT_FOR_COT )
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
                cic_rec->cot_first_ind = ITS_TRUE;
                ISUP_ClearCic(cic_rec);
            }
        }

        if (cic_rec->cri_state != CRI_IDLE)
        {
            if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
            {
                cic_rec->cri_state = CRI_IDLE;
                cic_rec->cot_first_ind = ITS_TRUE;
                ISUP_ClearCic(cic_rec);
            }
            else if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
            {
                __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T36);
                cic_rec->cri_state = CRI_IDLE;
                cic_rec->cot_first_ind = ITS_TRUE;

            }
        }


        /* Check CIC call processing state */
        if (ISUP_CIC_GET_CALL(cic_rec->cic_state) != CKTS_IDLE_CTK)
        {
            app_err = ITS_ISUP_CIC_BUSY_ERR;
        }

        /* Check CIC maint blocking states */

        /*
         * Check if Test Call
         */
        if (msg->data[12] != CGP_CAT_TEST_CALL)
        {
           /* Not a Test Call, Check CIC Maintenance/Hwr Block State */

           if (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LBLOCKED)
           {
               ISUP_CIC_SET_MAINT(cic_rec->cic_state, CKTS_ACTIVE);

               if (cic_rec->bls_state == BLS_LBLOCKED)
               {
                   cic_rec->bls_state = BLS_IDLE;
               }
           }
           else if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_RBLOCKED) ||
                (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LRBLOCKED))
           {
               app_err = ITS_ISUP_CIC_MNBLOCK_ERR;
           }
    
           /* Check CIC hardware blocking states */
           if (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LBLOCKED)
           {
               ISUP_CIC_SET_HDW(cic_rec->cic_state, CKTS_ACTIVE);

               if (cic_rec->hlb_state == HLB_LBLOCKED)
               {
                   cic_rec->hlb_state = HLB_IDLE;
               }
           } 
           else if ((ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_RBLOCKED) ||
               (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LRBLOCKED))
           {
               app_err = ITS_ISUP_CIC_HWBLOCK_ERR;
           }
        }
        else
        {
            ISUP_DEBUG(("Received IAM is a TEST CALL, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));
        }

        if (app_err != ITS_SUCCESS)
        {
            ISUP_Alarm_CCITT(3479, __FILE__, __LINE__, "pcic %x", cic_rec->pcic);
            ISUP_ERROR(("Discarding outgoing IAM message since CIC in "
                        "invalid state, pcic 0x%08x, vcic %u\n",
                        cic_rec->pcic, cic_rec->vcic));

            /* Send error indic to app. */
            SPRC_SendErrorToApp_CCITT(ISUP_MSG_IAM,app_err, cic_rec);

            /* No updates to any data in cic_rec */

            return;
        }

        /* Mark CIC as outgoing_busy */
        ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_OUT_CTK_BUSY);

        /* Start Timer T7 */
        tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T7, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T7].tmr_value);
        if (tret != ITS_SUCCESS)
        {
            ISUP_ERROR(("IDLE IAM: Failed to start T7. pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));
        }

        offset = sizeof(MTP3_HEADER_CCITT) + sizeof(ITS_USHORT) +
                                               sizeof(ITS_OCTET);

        /* Check the value of CCH in NCI parameter
         * if CCH = 0, COT check not required, if CCH = 1
         * COT check is required on the incoming circuit, else if
         * CCH = 2, COT check is reqd on the previous circuit
         */
        switch((msg->data[offset+1] >> 2) & 0x03U)
        {
        case NCI_CHECK_NOT_REQUIRED:

            /* Change state to WAIT_INCOMING_ACM - Wait for Address Complete */
            cic_rec->fsm_state = WAIT_INCOMING_ACM;
            break;

        case NCI_CHECK_CKT_REQUIRED:
        case NCI_CHECKED_PREV_CKT:

            ISUP_DEBUG(("++Received IAM with COT chk , pcic 0x%08x, vcic %d.\n",
                         cic_rec->pcic, cic_rec->vcic));

            /* Start Timer T24 */
            tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T24,
                   config_info->tmr_hndl_info[ITS_ISUP_TIMER_T24].
tmr_value);
            if (tret != ITS_SUCCESS)
            {
                ISUP_ERROR(("IDLE IAM: Failed to start T24"
                    ". pcic 0x%08x, vcic %d.\n",cic_rec->pcic, cic_rec->vcic));
            }

            cic_rec->cco_state = CCO_WAIT_COT_REPORT;

            /* Change state to Wait for continuity report */
            cic_rec->fsm_state = WAIT_CONTINUITY_REPORT;

            break;

        default :
            cic_rec->fsm_state = WAIT_INCOMING_ACM;
            break;
        }

        /*
         * Store the IAM msg in cic_rec
         * offset to encoded IAM is after MTP3 header + CIC + MsgType
         */
        offset = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_CCITT) +
                  sizeof(ITS_USHORT) + sizeof(ITS_OCTET);

        cic_rec->cpc_msg_len = msg->len - offset;
        memcpy((char *)cic_rec->cpc_msg, (char *)&(msg->data[offset]),
                cic_rec->cpc_msg_len);

        if (cic_rec->cpc_msg_len > MTP3_MAX_SIF_LENGTH &&
                                 cic_rec->cpc_msg_len < 2*MTP3_MAX_SIF_LENGTH)
        {
            __ISUP_SegmentOverlenMsg_ITU93(msg, cic_rec, ISUP_MSG_IAM,
                                                         config_info);
        }
        else
        {
            /* Send to L3 */
            SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an IDR received in the IDLE state is done here.
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
static void
__ISUP_Received_IDR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received IDR in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Forward IDR to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

        /* State remains same */
    }

    if (src != ISUP_SRC_L3_ITU) 
    {
        ISUP_DEBUG(("Received IDR in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* Start timer T39 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T39, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T39].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("IDLE IDR: Failed to start T39. pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));
        }

        /* State remains the same */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an IRS received in the IDLE state is done here.
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
static void
__ISUP_Received_IRS(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received IRS in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Stop timer T39 */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T39);

        /* Forward IRS to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

        /* State remains same */
    }


    if (src != ISUP_SRC_L3_ITU) 
    {
        ISUP_DEBUG(("Received IRS in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Forward IRS to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* State remains same */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an NRM received in the IDLE state is done here.
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
static void
__ISUP_Received_NRM(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward NRM appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received NRM in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

        /* State remains same */
    }
    else 
    {
        ISUP_DEBUG(("Received NRM in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* State remains same */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an OLM received in the IDLE state is done here.
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
static void
__ISUP_Received_OLM(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;

    /* Forward OLM appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received OLM in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Start Timer T3 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T3, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T3].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("IDLE OLM: Failed to start T3. pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));
        }
        else
        {
            cic_rec->ovld_indic = ITS_TRUE;
        }
        /* Stop T7, if IAM has been sent */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

        /* State remains same */
    }
    else 
    {
        ISUP_DEBUG(("Received OLM in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* State remains same */
    }

    /*   Q.764(2.9.9) (Temporary truck blocking)
     *   When an initial address message is received by an exchange which
     *   is subject to load control and the calling party category parameter
     *   does not indicate a priority call, the initial address message is not
     *   processed and an overload message is returned to the preceding exchange.
     */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an PAM received in the IDLE state is done here.
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
static void
__ISUP_Received_PAM(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward PAM appropriately CHECK: Is this allowed in IDLE state ? */

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received PAM in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

        /* Change state to IDLE */
    }
    else 
    {
        ISUP_DEBUG(("Received PAM in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* Change state to IDLE */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an REL received in the IDLE state is done here.
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
static void
__ISUP_Received_REL(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward REL appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received REL in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T36);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;

            /* Send to app */
            /* FIXME - Do we need to send the ind, or just send
             * RLC from here, and change the FSM state to
             * WAIT_INCOMING_RLC */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
            cic_rec->fsm_state = WAIT_OUTGOING_RLC;
        }
        else if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            /*handle*/
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T27);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;

            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
            cic_rec->fsm_state = WAIT_OUTGOING_RLC;
        }
        else
        {
            SPRC_SendRLCToMTP3_CCITT(CI_CAUSE_NORMAL, cic_rec, config_info);

            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);
        }
        /* No State Change */
    }
    else 
    {
        ISUP_DEBUG(("Received REL in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY)
        {
            if (cic_rec->cot_first_ind == ITS_TRUE)
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
            }
            else
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
            }
            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_COT)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T36);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        } 

        /* store the message in cic rec */
        memcpy(cic_rec->cpc_msg, msg->data, msg->len);
        cic_rec->cpc_msg_len = msg->len;

        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        __ISUP_StartRELTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }

   /* Q.764(2.11)   (Automatic congetion control)
    * When an exchange receives a release message containing an automatic
    * congestion level parameter, the ISDN User Part should pass the
    * appropriate information to the signalling system independent network
    * management/overload control function within the exchange.  
    * This information consists of the received congestion level
    * information and the circuit identification to which the release
    * message applies.
    */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an RLC received in the IDLE state is done here.
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
static void
__ISUP_Received_RLC(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Mark cic as idle and forward RLC appropriately */

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received RLC in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* FIXED ?? : check for call state */
        /* Stop Timer T1 and T5 if running - for REL sent */
        __ISUP_StopRELTimers(cic_rec, config_info);

        if (cic_rec->crs_state == CRS_WAIT_FOR_RELEASE)
        {
            /* Stop Timer T16 and T17 if running - for RSC sent */
            __ISUP_StopRSCTimers(cic_rec, config_info);
                    
            /* Stop Repeat RSC timer also */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T98);

            /* Change state to IDLE - clear cic_rec */
            ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);
            ISUP_ClearCic(cic_rec);

            if (cic_rec->reset_flag == RESET_FROM_CC)
            {
                /* Send to app */
                SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
            }

            cic_rec->crs_state = CRS_IDLE;
        }
        else
        {
            ISUP_Alarm_CCITT(3480, __FILE__, __LINE__,
                                    "pcic %x", cic_rec->pcic);
            /* discard the message */
            ISUP_DEBUG(("Got unexpected RLC from MTP3, pcic 0x%08x, vcic %d.\n",
                 cic_rec->pcic, cic_rec->vcic));

            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);
        }
    }
    else 
    {
        ISUP_DEBUG(("Received RLC in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->crr_state == CRR_WAIT_FOR_RESPONSE)
        {
            /* Send to L3 */
            SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

            cic_rec->crr_state = CRR_IDLE;

            /* Change state to IDLE - clear cic_rec */
            ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);
            ISUP_ClearCic(cic_rec);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an RSC received in the IDLE state is done here.
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
 *  Notes:
 *      Procedures as per Q.764 (03/93), Sec. 2.9.3.1
 *
 ****************************************************************************/
static void
__ISUP_Received_RSC(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_RSC(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an UBA received in the IDLE state is done here.
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
static void
__ISUP_Received_UBA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_UBA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an UBL received in the IDLE state is done here.
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
static void
__ISUP_Received_UBL(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_UBL(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an UPT received in the IDLE state is done here.
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
static void
__ISUP_Received_UPT(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ITU)
    {
        /* NOTE: Later automate ack back to L3 */
        ISUP_DEBUG(("Received UPT in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

        /* Change state to IDLE */
    }
    else 
    {
        ISUP_DEBUG(("Received UPT in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
        /* Timer T4 to be started at receipt of MTP 'remote user unavail' */

        /* Change state to IDLE */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an USR received in the IDLE state is done here.
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
static void
__ISUP_Received_USR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward USR appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received USR in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
        /* Change state to IDLE */
    }
    else 
    {
        ISUP_DEBUG(("Received USR in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* Change state to IDLE */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an UCIC received in the IDLE state is done here.
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
__ISUP_Received_UCIC(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Check if the msg is national or international significant */
    if ((cic_rec->pcic.hdr.sio & MTP3_NIC_MASK) == MTP3_NIC_NATIONAL)
    {
        /* National Network, Process this */
        __ISUP_CSC_Received_UCIC(msg, cic_rec, config_info, src);
    }
    else if ((cic_rec->pcic.hdr.sio & MTP3_NIC_MASK) == MTP3_NIC_INTERNATIONAL)
    {
        /* International Network, don't do anything */
    }
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an LPA received in the IDLE state is done here.
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
__ISUP_Received_LPA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_LPA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing of a message not expected in 
 *      the IDLE state. It also serves as a default handler for any errors
 *      arising from out-of-range function calls.
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
 *  Name       Date         Reference    Description
 *  --------------------------------------------------------------------------
 *  kramesh    05-05-2005   Bug Id #1736 Error Indication to app added 
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
     
       __ISUP_ResetCPCToCRS(cic_rec, config_info);

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
__ISUP_GetMsgProc_Idle_ITU93(ITS_OCTET msgType)
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
    case ISUP_MSG_RSC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_RSC;
    case ISUP_MSG_IAM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_IAM;
    case ISUP_MSG_REL:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_REL;
    case ISUP_MSG_RLC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_RLC;
    case ISUP_MSG_UCIC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UCIC;
    case ISUP_MSG_BLO:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_BLO;
    case ISUP_MSG_BLA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_BLA;
    case ISUP_MSG_CGB:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGB;
    case ISUP_MSG_CGBA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGBA;
    case ISUP_MSG_CQM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CQM;
    case ISUP_MSG_CQR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CQR;
    case ISUP_MSG_GRS:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_GRS;
    case ISUP_MSG_GRA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_GRA;
    case ISUP_MSG_CGU:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGU;
    case ISUP_MSG_CGUA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGUA;
    case ISUP_MSG_COT:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_COT;
    case ISUP_MSG_CCR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CCR;
    case ISUP_MSG_LPA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_LPA;
    case ISUP_MSG_FOT:
    case ISUP_MSG_INF:
    case ISUP_MSG_INR:
        break;
    case ISUP_MSG_PAM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_PAM;
    case ISUP_MSG_RES:
    case ISUP_MSG_SUS:
        break;
    case ISUP_MSG_UBL:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UBL;
    case ISUP_MSG_UBA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UBA;
    case ISUP_MSG_CRG:
    case ISUP_MSG_FAC:
    case ISUP_MSG_FAA:
    case ISUP_MSG_FRJ:
    case ISUP_MSG_FAR:
        break;
    case ISUP_MSG_IDR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_IDR;
    case ISUP_MSG_IRS:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_IRS;
    case ISUP_MSG_NRM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_NRM;
    case ISUP_MSG_SGM:
        break;
    case ISUP_MSG_OLM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_OLM;
    case ISUP_MSG_UPA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UPA_ITU93;
    case ISUP_MSG_UPT:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UPT;
    case ISUP_MSG_USR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_USR;
    default:
        /*
         * Unknown message type for ISUP.
         * Send back Confusion message.
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
 *      for the ITU ISUP generic variant (ITU93) message handling procedures. 
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
__ISUP_GetMsgHandler_ITU93(ITS_OCTET msgType, ITS_ISUP_STATE state)
{
    switch(state)
    {
    /* 
     * This should be called only after verifying that the msgType is correct.
     */
    case IDLE:
        return __ISUP_GetMsgProc_Idle_ITU93(msgType);

    /* IAM sent to network, waiting for ACM. */
    case WAIT_INCOMING_ACM:
        return __ISUP_GetMsgProc_WaitIncomingAcm_ITU93(msgType);

    /* ACM sent to network, waiting for ANM. */
    case WAIT_INCOMING_ANM:
        return __ISUP_GetMsgProc_WaitIncomingAnm_ITU93(msgType);

    /* ANM rcvd from network, call established. */
    case RCVD_INCOMING_ANM: 
        return __ISUP_GetMsgProc_RcvdIncomingAnm_ITU93(msgType);

    /* REL sent to network, waiting for RLC. */
    case WAIT_INCOMING_RLC: 
        return __ISUP_GetMsgProc_WaitIncomingRlc_ITU93(msgType);

    /* SUS rcvd from network, call suspended, waiting for RES. */
    case WAIT_INCOMING_RES: 
        return __ISUP_GetMsgProc_WaitIncomingRes_ITU93(msgType);

    /* IAM rcvd from network, waiting to send ACM. */
    case WAIT_OUTGOING_ACM: 
        return __ISUP_GetMsgProc_WaitOutgoingAcm_ITU93(msgType);

    /* ACM rcvd from network, waiting to send ANM. */
    case WAIT_OUTGOING_ANM:     
        return __ISUP_GetMsgProc_WaitOutgoingAnm_ITU93(msgType);

    /* ANM sent to network, call established. */
    case SENT_OUTGOING_ANM: 
        return __ISUP_GetMsgProc_SentOutgoingAnm_ITU93(msgType);

    /* REL rcvd from network, waiting to send RLC. */
    case WAIT_OUTGOING_RLC: 
        return __ISUP_GetMsgProc_WaitOutgoingRlc_ITU93(msgType);

    /* SUS sent to network, call suspended, waiting to send RES to network. */
    case WAIT_OUTGOING_RES: 
        return __ISUP_GetMsgProc_WaitOutgoingRes_ITU93(msgType);

    /* Timeout/error, waiting to send REL to network. */
    case WAIT_OUTGOING_REL: 
        return __ISUP_GetMsgProc_WaitOutgoingRel_ITU93(msgType);

    /* Timeout/error, waiting to send RSC to network. */
    case WAIT_OUTGOING_RSC: 
        return (__ISUP_MsgHandlerProc)
                   __ISUP_GetMsgProc_WaitOutgoingRsc_ITU93(msgType);

    /* GRS received, waiting to send GRA to network. */
    case WAIT_OUTGOING_GRA: 
        return (__ISUP_MsgHandlerProc)
                   __ISUP_GetMsgProc_WaitOutgoingGra_ITU93(msgType);

    case WAIT_CONTINUITY_REPORT:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitCotReport_ITU93(msgType);

    case WAIT_INCOMING_COT:
        return (__ISUP_MsgHandlerProc)
                      __ISUP_GetMsgProc_WaitIncomingCot_ITU93(msgType);
    default:
        /* Log error in call */
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg;
    }
}


/* TIMEOUT Handling */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T3 timer in the 
 *      IDLE state. 
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
 *  Notes:
 *      Q.764 (03/93) Sec. 2.9.9 gives the procedure. When stack is set up
 *      to handle timeout processing, it follows that procedure. Otherwise
 *      the stack expects the App to follow up with the appropriate procedures.
 *
 ****************************************************************************/
static void
__ISUP_Received_TimeoutT3(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT3 event received in IDLE state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, 
                 ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Remove info about timer from cic_rec. T3 is not restarted. */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T3);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT3 in IDLE state: Unable to remove T3 "
                    "info from CIC rec. Error %s. pcic 0x%08x, vcic %d,"
                    "cic %d.\n", ITS_GetErrorText(ret), cic_rec->pcic, 
                     cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    /* Remove the Overload indication for this CIC */
    cic_rec->ovld_indic = ITS_FALSE;

    if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T3].tmr_hndl_layer 
        == ISUP_TMR_HNDL_STACK)
    {
        /* Do the thing. Phase II. */
        /* Send REL to L3 */
        SPRC_SendRELToMTP3_CCITT(CI_CAUSE_SWITCH_CONGESTED,
                                 cic_rec,
                                 config_info);

        /* Start T1 and T5 */
        __ISUP_StartRELTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }
    else
    {
        /* Change state to WAIT_OUTGOING_REL */
        cic_rec->fsm_state = WAIT_OUTGOING_REL;
    }

    ISUP_Alarm_CCITT(3472, __FILE__, __LINE__, NULL);

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T8 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT8(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT8 event received in IDLE state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, 
                 ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T8);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT8 in IDLE state: Unable to remove T8 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T8].tmr_hndl_layer 
        == ISUP_TMR_HNDL_STACK)
    {
        /* Do the thing. Phase II. */
        /* Send REL to L3 */
        SPRC_SendRELToMTP3_CCITT(CI_CAUSE_TEMPORARY_FAILURE,
                                 cic_rec,
                                 config_info);

        /* Start T1 and T5 */
        __ISUP_StartRELTimers(cic_rec, config_info);

        /* Send Indication to App */
        SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_COT_RELEASE_RQIND,cic_rec);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }
    else
    {
        /* Change state to WAIT_OUTGOING_REL */
        cic_rec->fsm_state = WAIT_OUTGOING_REL;
    }

    ISUP_Alarm_CCITT(3468, __FILE__, __LINE__, NULL);

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T12 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT12(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT12(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T13 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT13(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT13(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T14 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT14(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT14(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T15 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT15(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT15(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T16 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT16(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT16(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T17 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT17(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT17(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T18 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT18(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT18(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T19 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT19(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT19(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T20 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT20(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT20(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T21 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT21(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT21(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T22 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT22(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT22(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T23 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT23(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT23(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T24 timer in the
 *      IDLE state.
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
__ISUP_Received_TimeoutT24(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT24(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T27 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT27(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT27 event received in IDLE state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic,
                 ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T27].
                                                       tmr_hndl_layer 
                                              == ISUP_TMR_HNDL_STACK)
    {
        /* Do the thing. Phase II. */
        /* Send RSC to L3 */
        SPRC_SendRSCToMTP3_CCITT( cic_rec, config_info);

        /* Start Timers T16, T17 */
        __ISUP_StartRSCTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }
    else
    {
        /* Remove info about timer from cic_rec */
        ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T27);
        if (ret != ITS_SUCCESS)
        {
            /* log error */
            ISUP_ERROR(("TimeoutT27 in IDLE state: Unable to remove T27 info "
                        "from CIC rec. Error %s. pcic 0x%08x,"
                        " vcic %d, cic %d.\n", ITS_GetErrorText(ret), 
                        cic_rec->pcic, cic_rec->vcic,
                        ISUP_PCIC_TO_CIC(cic_rec->pcic)));
        }
        /* Change state to WAIT_OUTGOING_RSC */
        cic_rec->fsm_state = WAIT_OUTGOING_RSC;
    }

    if(cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        cic_rec->cri_state = CRI_IDLE;
    }

    ISUP_Alarm_CCITT(3462, __FILE__, __LINE__, NULL);

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
    SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_COT_RESET_RQIND, cic_rec);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T28 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT28(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT28 event received in IDLE state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Nothing to be done at expiry except notify maintenance */
    ISUP_CRITICAL(("Timer T28 expired, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T28);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT28 in IDLE state: Unable to remove T28 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }
    ISUP_Alarm_CCITT(3463, __FILE__, __LINE__, NULL);

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T33 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT33(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT33 event received in IDLE state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T33);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT33 in IDLE state: Unable to remove T33 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T33].tmr_hndl_layer 
        == ISUP_TMR_HNDL_STACK)
    {
        /* Do the thing. Phase II. */
        /* Send REL to L3 */
        SPRC_SendRELToMTP3_CCITT(CI_CAUSE_TEMPORARY_FAILURE,
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

    ISUP_Alarm_CCITT(3464, __FILE__, __LINE__, NULL);

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T36 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT36(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT36(t_entry,cic_rec,config_info);

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T39 timer in the 
 *      IDLE state. 
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
__ISUP_Received_TimeoutT39(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT39 event received in IDLE state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Remove info about timer from cic_rec; it won't be restarted. */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T39);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT39 in IDLE state: Unable to remove T39 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    /* No processing: call continues. Remain in same state. */
    ISUP_Alarm_CCITT(3466, __FILE__, __LINE__, NULL);

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing of a timeout not expected in 
 *      the IDLE state. It also serves as a default handler for any errors
 *      arising from out-of-range function calls.
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
__ISUP_Received_UnexpectedTimeout(ISUP_TIMER_ENTRY* t_entry, 
                                  ISUP_CIC_INFO *cic_rec,
                                  ISUP_OPC_DPC_INFO *config_info)
{
    /* Log error, update stats and drop msg */
    ISUP_ERROR(("Rcvd Unexpected Timeout T%d for CIC %d in IDLE. "
                "cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                t_entry->timerId, t_entry->cic,
                cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));
    /* Could print out mtp3 header or entire ITS_EVENT */ 

    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

    ISUP_Alarm_CCITT(3467, __FILE__, __LINE__, "Timer id: T%d", t_entry->timerId);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a timout handler procedure for  
 *      the IDLE state, based on the ID of the timer that has expired.
 *
 *  Input Parameters:
 *      timerID: the ID of the timer that has expired, as per ISUP.
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
__ISUP_GetTimeoutProc_Idle_ITU93(ITS_UINT timerID)
{
    switch(timerID)
    {
    case ITS_ISUP_TIMER_T1: /*  1    First RLC timer        */
        break;
    case ITS_ISUP_TIMER_T2: /*  2    Suspend timer          */
        break;
    case ITS_ISUP_TIMER_T3: /*  3    Unused                 */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT3;
    case ITS_ISUP_TIMER_T4: /*  4    used for MTP3 status indic */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT4_ITU93;
        break;
    case ITS_ISUP_TIMER_T5: /*  5    Second RLC timer       */
        break;
    case ITS_ISUP_TIMER_T6: /*  6    RES timer (network)    */
        break;
    case ITS_ISUP_TIMER_T7: /*  7    ACM timer              */
        break;
    case ITS_ISUP_TIMER_T8: /*  8    COT timer              */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT8;
    case ITS_ISUP_TIMER_T9: /*  9    ANM timer              */
        break;
    case ITS_ISUP_TIMER_T10: /* 10   Unused                 */
        break;
    case ITS_ISUP_TIMER_T11: /* 11   Unused                 */
        break;
    case ITS_ISUP_TIMER_T12: /* 12   First BLA timer        */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT12;
    case ITS_ISUP_TIMER_T13: /* 13   Second BLA timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT13;
    case ITS_ISUP_TIMER_T14: /* 14   First UBA timer        */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT14;
    case ITS_ISUP_TIMER_T15: /* 15   Second UBA timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT15;
    case ITS_ISUP_TIMER_T16: /* 16   First RSC response timer   */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT16;
    case ITS_ISUP_TIMER_T17: /* 17   Second RSC response timer  */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT17;
    case ITS_ISUP_TIMER_T18: /* 18   First CGBA timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT18;
    case ITS_ISUP_TIMER_T19: /* 19   Second CGBA timer      */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT19;
    case ITS_ISUP_TIMER_T20: /* 20   First CGUA timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT20;
    case ITS_ISUP_TIMER_T21: /* 21   Second CGUA timer      */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT21;
    case ITS_ISUP_TIMER_T22: /* 22   First GRA timer        */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT22;
    case ITS_ISUP_TIMER_T23: /* 23   Second GRA timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT23;
    case ITS_ISUP_TIMER_T24: /* 24   Continuity toner timer */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT24;
    case ITS_ISUP_TIMER_T25: /* 25   CCR timing timer       */
        break;
    case ITS_ISUP_TIMER_T26: /* 26   CCR response timer     */
        break;
    case ITS_ISUP_TIMER_T27: /* 27   CCR receive timer      */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT27;
    case ITS_ISUP_TIMER_T28: /* 28   CQR timer              */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT28;
    case ITS_ISUP_TIMER_T29: /* 29   First congestion       */
        break;
    case ITS_ISUP_TIMER_T30: /* 30   First congestion indication    */
        break;
    case ITS_ISUP_TIMER_T31: /* 31   Unused         */
        break;
    case ITS_ISUP_TIMER_T32: /* 32   Unused         */
        break;
    case ITS_ISUP_TIMER_T33: /* 33   Unused         */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT33;
    case ITS_ISUP_TIMER_T34: /* 34   SGM Message Timer    */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT34;
        break;
    case ITS_ISUP_TIMER_T35: /* 35          */
        break;
    case ITS_ISUP_TIMER_T36: /* 36          */
        return(__ISUP_TimeoutHandlerProc) __ISUP_Received_TimeoutT36;
    case ITS_ISUP_TIMER_T37: /* 37          */
        break;
    case ITS_ISUP_TIMER_T38: /* 38          */
        break;
    case ITS_ISUP_TIMER_T39: /* 39          */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT39;

    default:
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;
    }
    return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a timeout handler procedure, 
 *      based on the msgType and state of the CIC. This is the main function
 *      for the ITU ISUP generic variant (ITU93) timeout handling procedures.
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
__ISUP_GetTimeoutHandler_ITU93(ITS_UINT timerID, ITS_ISUP_STATE state)
{
    switch(state)
    {
    /* 
     * This should be called only after verifying that the timerID is correct.
     */
    case IDLE:
        return __ISUP_GetTimeoutProc_Idle_ITU93(timerID);

    /* IAM sent to network, waiting for ACM. */
    case WAIT_INCOMING_ACM:
        return __ISUP_GetTimeoutProc_WaitIncomingAcm_ITU93(timerID);

    /* ACM sent to network, waiting for ANM. */
    case WAIT_INCOMING_ANM: 
        return __ISUP_GetTimeoutProc_WaitIncomingAnm_ITU93(timerID);

    /* ANM rcvd from network, call established. */
    case RCVD_INCOMING_ANM: 
        return __ISUP_GetTimeoutProc_RcvdIncomingAnm_ITU93(timerID);

    /* REL sent to network, waiting for RLC. */
    case WAIT_INCOMING_RLC: 
        return __ISUP_GetTimeoutProc_WaitIncomingRlc_ITU93(timerID);

    /* SUS rcvd from network, call suspended, waiting for RES. */
    case WAIT_INCOMING_RES: 
        return __ISUP_GetTimeoutProc_WaitIncomingRes_ITU93(timerID);

    /* IAM rcvd from network, waiting to send ACM. */
    case WAIT_OUTGOING_ACM: 
        return __ISUP_GetTimeoutProc_WaitOutgoingAcm_ITU93(timerID);

    /* ACM rcvd from network, waiting to send ANM. */
    case WAIT_OUTGOING_ANM:     
        return __ISUP_GetTimeoutProc_WaitOutgoingAnm_ITU93(timerID);

    /* ANM sent to network, call established. */
    case SENT_OUTGOING_ANM: 
        return __ISUP_GetTimeoutProc_SentOutgoingAnm_ITU93(timerID);

    /* REL rcvd from network, waiting to send RLC. */
    case WAIT_OUTGOING_RLC: 
        return __ISUP_GetTimeoutProc_WaitOutgoingRlc_ITU93(timerID);

    /* SUS sent to network, call suspended, waiting to send RES to network. */
    case WAIT_OUTGOING_RES: 
        return __ISUP_GetTimeoutProc_WaitOutgoingRes_ITU93(timerID);

    /* Timeout/error, waiting to send REL to network. */
    case WAIT_OUTGOING_REL: 
        return __ISUP_GetTimeoutProc_WaitOutgoingRel_ITU93(timerID);

    /* Timeout/error, waiting to send RSC to network. */
    case WAIT_OUTGOING_RSC:
        return __ISUP_GetTimeoutProc_WaitOutgoingRsc_ITU93(timerID);

    /* GRS received, waiting to send GRA to network. */
    case WAIT_OUTGOING_GRA:
        return __ISUP_GetTimeoutProc_WaitOutgoingGra_ITU93(timerID);

    case WAIT_CONTINUITY_REPORT:
        return (__ISUP_TimeoutHandlerProc)
                      __ISUP_GetTimeoutProc_WaitCotReport_ITU93(timerID);

    case WAIT_INCOMING_COT:
        return (__ISUP_TimeoutHandlerProc)
                      __ISUP_GetTimeoutProc_WaitIncomingCot_ITU93(timerID);

    default:
        /* Log details of bad call */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;

    }
}

