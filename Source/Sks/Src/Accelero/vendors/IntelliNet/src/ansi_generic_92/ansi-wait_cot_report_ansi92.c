/**********************************-*-C-*-************************************
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
 *  ID: $Id: ansi-wait_cot_report_ansi92.c,v 9.1 2005/03/23 12:54:52 cvsadmin
 *  Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:52  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2  2005/04/08 06:21:34  ssingh
 * LOG: ISUP bug fix propagation (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.10  2005/03/21 13:53:57  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.14.2.2.6.1.12.3  2005/02/03 12:44:40  ssingh
 * LOG: Bug #1448; unexpected Msg from Network and peg/stats handling.
 * LOG: (Ramesh KV, Abhijit D)
 * LOG:
 * LOG: Revision 1.14.2.2.6.1.12.2  2004/12/29 14:35:54  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 1.14.2.2.6.1.12.1  2004/12/06 13:34:50  mmanikandan
 * LOG: Windows Compilation Support
 * LOG:
 * LOG: Revision 1.14.2.2.6.1  2004/01/05 10:10:44  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 1.14.2.2.2.1  2003/09/13 06:27:00  akumar
 * LOG: Msg Based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 1.14.2.2  2003/06/16 14:17:49  sjaddu
 * LOG: COT t26 timer fix propagation from current.
 * LOG:
 * LOG: Revision 1.14.2.1  2003/05/07 10:38:00  ssingh
 * LOG: Latest Changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.7  2003/05/06 13:55:52  sswami
 * LOG: Alarm related changes :opc information included.
 * LOG:
 * LOG: Revision 8.6  2003/04/28 15:07:15  sjaddu
 * LOG: Removed EVEN TERM every thing is taken care.
 * LOG:
 * LOG: Revision 8.5  2003/04/24 14:13:26  sswami
 * LOG: Bug #317; Alarm Enhancement related changes done.
 * LOG:
 * LOG: Revision 8.4  2003/04/16 06:42:11  akumar
 * LOG: ITS_EVENT_TERM added.
 * LOG:
 * LOG: Revision 8.3  2003/04/03 15:24:34  sjaddu
 * LOG: ISUP DSM reorganization.
 * LOG:
 * LOG: Revision 8.2  2003/03/26 12:29:32  ssingh
 * LOG: Modified CIC_INFO changes incorporated. ISUPPending List Items done.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:28  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 1.14  2003/01/17 15:35:38  sjaddu
 * LOG: CPG changes handling.
 * LOG:
 * LOG: Revision 1.13  2002/12/11 14:23:05  ssingh
 * LOG: Changed code for INF/INR/CPG and T33 expiry handling.
 * LOG:
 * LOG: Revision 1.12  2002/12/02 11:22:13  sjaddu
 * LOG: COT handling in IDLE State.
 * LOG:
 * LOG: Revision 1.11  2002/11/28 08:58:43  sjaddu
 * LOG: Fix for DCO state handling.
 * LOG:
 * LOG: Revision 1.10  2002/11/20 12:49:07  akumar
 * LOG: Worked on ALARMS indentation
 * LOG:
 * LOG: Revision 1.9  2002/11/19 13:16:43  sjaddu
 * LOG: Ignore COT recieved in waint timer expiry.
 * LOG:
 * LOG: Revision 1.8  2002/11/14 08:29:22  akumar
 * LOG: Replaced inlined exchange control determinsitic logic with func call
 * LOG:
 * LOG: Revision 1.7  2002/11/12 06:05:00  akumar
 * LOG: Added ANSI ISUP Alarms
 * LOG:
 * LOG: Revision 1.6  2002/11/08 08:08:43  ssingh
 * LOG: Added some code to handle RLC from Application in all states.
 * LOG:
 * LOG: Revision 1.5  2002/11/07 14:01:16  ssingh
 * LOG: Added FIX for BUG# 147 for inconsistent handling of RLC across the states.
 * LOG:
 * LOG: Revision 1.4  2002/11/07 09:55:15  sjaddu
 * LOG: REL handling modified.
 * LOG:
 * LOG: Revision 1.3  2002/11/07 09:39:35  sjaddu
 * LOG: Fix for handling REL in this state.
 * LOG:
 * LOG: Revision 1.2  2002/10/30 13:49:18  sjaddu
 * LOG: Set cot_first_time indicator to ITS_TRUE.
 * LOG:
 * LOG: Revision 1.1  2002/10/30 08:33:59  sjaddu
 * LOG: Added new state file wait for continuity report.
 * LOG:
 *
 *****************************************************************************/

#undef CCITT
#undef ANSI
#define ANSI

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <isup_variants.h>

#include <isup_intern.h>
#include <ansi/isup_92.h>

/*
 * Functions for handling messages in the Wait in cot report state for ANSI92 
 * variant.This is considered to be the generic ANSI variant, and all other 
 * ANSI variants use these functions as defaults if they do not have different 
 * behaviour.
 */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an IAM received in the WAIT_CONTINUITY_REPORT state
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BugId: 389     Added Message type in the
 *                                          Error indication to application.
 *
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
static void
__ISUP_Received_IAM(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{

    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received IAM in WAIT_CONTINUITY_REPORT from MTP3, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {  
            /* Dual Seizure Code 
            * Find out if This node is Controlled or Controlling
            * Exchange for this particular cic
            */

            if (!__ISUP_IsExchangeControlling(msg, cic_rec, config_info))
            {
                /* Non-Control exchange for these circuits 
                * Let this call mature 
                */

                /* Mark ckt Incoming Busy */
                ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IN_CTK_BUSY);

                /* Stop Timer T7 */

                __ISUP_StopCPCToCCO(cic_rec,config_info);
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

                /*Send a Re-attempt indication to the application */
                SPRC_SendIndToApp_ANSI(ITS_ISUP_IAM_REATTEMPT_IND, cic_rec);

                /* Send IAM to App */
                SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);


                /* Change state to WAIT_OUTGOING_ACM - Wait for OGC Complete */
                cic_rec->fsm_state = WAIT_OUTGOING_ACM;
            }
            else if (__ISUP_IsExchangeControlling(msg, cic_rec, config_info))
            {
                /* Controlling exhange for these circuits
                * Disregard this IAM message
                *
                * Some Ack has to be sent to the Non-Controlling
                * Exchange also, that IAM has been dis-regarded ??
                */
                ISUP_DEBUG(("Received IAM Ignored! "
                     "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

                /* No change of state Here */
            }
        }
        else if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY ||
                 cic_rec->cro_state == CRO_WAIT_FOR_OUTGOING_CCR)
        {
            if (!__ISUP_IsExchangeControlling(msg, cic_rec, config_info))
            {
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
                cic_rec->cro_state = CRO_IDLE;
                cic_rec->cot_first_ind = ITS_TRUE;
                ISUP_ClearCic(cic_rec);

                cic_rec->fsm_state = WAIT_OUTGOING_ACM;
                SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
            }
            else
            {
                /*Discard */
                ISUP_DEBUG(("Received IAM Ignored! "
                     "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_COT)
        {
            if (!__ISUP_IsExchangeControlling(msg, cic_rec, config_info))
            {
                if (cic_rec->dco_state == DCO_IDLE)
                {
                    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
                }
                else
                {
                    __ISUP_StopCROToDCO(cic_rec,config_info);
                }
            
                ISUP_ClearCic(cic_rec);
                cic_rec->cro_state = CRO_IDLE;
                cic_rec->cot_first_ind = ITS_TRUE;

                cic_rec->fsm_state = WAIT_OUTGOING_ACM;
                SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
            }
            else
            {
                ISUP_DEBUG(("Received IAM Ignored! "
                     "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_RLC)
        {
            /*Never happens */
        }
    }
    else
    {
        ISUP_DEBUG(("Received IAM in WAIT_CONTINUITY_REPORT from APP,"
                    "Discarding pcic 0x%08x, vcic %d.\n", 
                     cic_rec->pcic, cic_rec->vcic));

        /* Send error indication to application. */
        SPRC_SendErrorToApp_ANSI(ISUP_MSG_IAM,
                                 ITS_ISUP_UNEXP_APPMSG_WAITFOR_COTREPORTS_ERR,
                                 cic_rec);

        /* No change of state */
    }

    return;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an ACM received in the WAIT_CONTINUITY_REPORT state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or it is dropped.
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
__ISUP_Received_ACM(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src != ISUP_SRC_L3_ANSI)
    {
        /* Msg out of sequence. Drop it and generate alarm. */
        ISUP_ERROR(("WAIT_CONTINUITY_REPORT ACM: Unexpected ACM from Application."
                    " pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        ISUP_Alarm_ANSI(3177, __FILE__, __LINE__, "Message %x cic : %x",
                         msg->data[sizeof(MTP3_HEADER_ANSI) + 
                         sizeof(ITS_USHORT) + sizeof(ITS_OCTET)],
                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

        SPRC_SendErrorToApp_ANSI(ISUP_MSG_ACM,
                                 ITS_ISUP_UNEXP_APPMSG_WAITFOR_COTREPORTS_ERR,
                                 cic_rec);

    }

    if (src == ISUP_SRC_L3_ANSI)    /* CPC outgoing */
    {
        ISUP_DEBUG(("Received ACM in WAIT_CONTINUITY_REPORT from MTP3,"
                    " pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {
            /* Stop Timer T7 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

           /* Send Retry Ind to App */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_RSC_REATTEMPT_RQIND, cic_rec);

           /* Start CPC to CRS */
           __ISUP_CSC_StartCRS(cic_rec, config_info);

           cic_rec->cco_state = CCO_IDLE;

           /* change fsm state to Idle */
           cic_rec->fsm_state = IDLE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_RLC)
        {
            /* ignore the message */
        } 
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an ANM received in the WAIT_CONTINUITY_REPORT state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or it is dropped.
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
__ISUP_Received_ANM(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                              ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ANSI) /* CPC Outgoing */
    {
        ISUP_DEBUG(("Received ANM in WAIT_CONTINUITY_REPORT from MTP3,"
                    " pcic 0x%08x vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {
            /* Stop Timer T7 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

           /* Send Retry Ind to App */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_RSC_REATTEMPT_RQIND, cic_rec);

           /* Start CPC to CRS */
           __ISUP_CSC_StartCRS(cic_rec, config_info);

           cic_rec->cco_state = CCO_IDLE;

           /* change fsm state to Idle */
           cic_rec->fsm_state = IDLE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_RLC)
        {
            /* ignore the message */
        } 

    }
    else
    {
        /* Msg out of sequence. Drop it and generate alarm. */
        ISUP_ERROR(("WAIT_CONTINUITY_REPORT ANM: Unexpected ANM from Application"
                    ".pcic 0x%08x vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        ISUP_Alarm_ANSI(3178, __FILE__, __LINE__, "Message %x cic : %x",
                         msg->data[sizeof(MTP3_HEADER_ANSI) + 
                         sizeof(ITS_USHORT) + sizeof(ITS_OCTET)],
                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

        SPRC_SendErrorToApp_ANSI(ISUP_MSG_ANM,
                                 ITS_ISUP_UNEXP_APPMSG_WAITFOR_COTREPORTS_ERR,
                                 cic_rec);

    }
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an COT received in the WAIT_CONTINUITY_REPORT state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or it is dropped.
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
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
static void
__ISUP_Received_COT(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                              ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int offset = 0;
    int tret = 0;

    if (src == ISUP_SRC_L3_ANSI) /* CPC Outgoing */
    {
        /* Msg out of sequence. Drop it and generate alarm. */
        ISUP_ERROR(("Received COT in WAIT_CONTINUITY_REPORT from MTP3",
                    " pcic 0x%08x,vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        ISUP_Alarm_ANSI(3179, __FILE__, __LINE__, "dpc: %d opc: %d "
                       "cic: %x  Message: %x",
                       MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                       MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                       ISUP_PCIC_TO_CIC(cic_rec->pcic),
                       msg->data[sizeof(MTP3_HEADER_ANSI) + 
                       sizeof(ITS_USHORT) + sizeof(ITS_OCTET)]);

        if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {
            /* Stop Timer T7 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

           /* Send Retry Ind to App */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_RSC_REATTEMPT_RQIND, cic_rec);

           /* Start CPC to CRS */
           __ISUP_CSC_StartCRS(cic_rec, config_info);

           cic_rec->cco_state = CCO_IDLE;
           /* change fsm state to Idle */
           cic_rec->fsm_state = IDLE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_RLC)
        {
            /* we should not receive this msg here */
            /* Msg out of sequence. Drop it and generate alarm. */
            ISUP_ERROR(("Received COT in WAIT_CONTINUITY_REPORT from"
                        " MTP3"," pcic 0x%08x,vcic %d.\n", 
                          cic_rec->pcic, cic_rec->vcic));
        } 
    }
    else
    {
        /* Check for failed or success indicator */
        offset = sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT) +
                 sizeof(ITS_OCTET);

        switch(msg->data[offset+1] & 0x01U)
        {
        case CONTINUITY_CHECK_SUCCESS:

            ISUP_DEBUG(("In WAIT_CONTINUITY_REPORT COT: SUCCESSFUL Received"
                        " from App. pcic 0x%08x,vcic %d.\n",
                          cic_rec->pcic, cic_rec->vcic));

            if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
                cic_rec->fsm_state = WAIT_INCOMING_ACM;
                cic_rec->cco_state = CCO_IDLE;
                /* Send to L3 */
                SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);
            }
            else if (cic_rec->cro_state == CRO_WAIT_FOR_COT &&
                     cic_rec->dco_state == DCO_IDLE)
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);

                /*Send REL */
                SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NORMAL_UNSPECIFIED,
                                        cic_rec,config_info);
                __ISUP_StartRELTimers(cic_rec, config_info);

                cic_rec->cro_state = CRO_WAIT_FOR_RLC;
                cic_rec->cco_state = CCO_IDLE;
                cic_rec->fsm_state = WAIT_INCOMING_RLC;
                cic_rec->cot_first_ind = ITS_TRUE;
            }
            else if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY||
                     cic_rec->cro_state == CRO_WAIT_FOR_OUTGOING_CCR)
            {
                /* This is considered as either manual stop
                 * or continuity detected at the app
                 */
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

                /*Send REL */
                SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NORMAL_UNSPECIFIED,
                                        cic_rec, config_info);
                __ISUP_StartRELTimers(cic_rec, config_info);

                cic_rec->cro_state = CRO_WAIT_FOR_RLC;
                cic_rec->cco_state = CCO_IDLE;
                cic_rec->fsm_state = WAIT_INCOMING_RLC;
                cic_rec->cot_first_ind = ITS_TRUE;
            }
            else 
            {
                /*Ignore it*/
                ISUP_ERROR(("WAIT_CONTINUITY_REPORT COT: SUCCESS Received from"
                            " App In Invalid State. pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic));

                SPRC_SendErrorToApp_ANSI(ISUP_MSG_COT,
                                 ITS_ISUP_UNEXP_APPMSG_WAITFOR_COTREPORTS_ERR,
                                 cic_rec);

            }
            break;

        case CONTINUITY_CHECK_FAILED:

            ISUP_DEBUG(("WAIT_CONTINUITY_REPORT COT: FAILURE Received from App."
                    " pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);

            if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
            {
                /*Stop T7 timer we are done with call processing*/
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

                tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T25,
                                config_info-> \
                                tmr_hndl_info[ITS_ISUP_TIMER_T25].tmr_value);
                if (tret != ITS_SUCCESS)
                {
                    ISUP_ERROR(("WAIT_CONTINUITY_REPORT: Failed to start T25."
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
                }
                cic_rec->cro_state = CRO_WAIT_TIMER_EXPIRY;
                cic_rec->cco_state = CCO_IDLE;
                SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);
            }
            else if(cic_rec->cro_state == CRO_WAIT_FOR_COT &&
                    cic_rec->dco_state == DCO_IDLE)
            {
                ISUP_CRITICAL(("COT check failed on CIC :"
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

                tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T26,
                                config_info->\
                                tmr_hndl_info[ITS_ISUP_TIMER_T26].tmr_value);
                if (tret != ITS_SUCCESS)
                {
                    ISUP_ERROR(("WAIT_CONTINUITY_REPORT: Failed to start T26."
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
                }
                cic_rec->cro_state = CRO_WAIT_TIMER_EXPIRY;
                SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);
            }
            else 
            {
                /*Ignore It*/
                ISUP_ERROR(("WAIT_CONTINUITY_REPORT:Received COT in invalid"
                            "state pcic 0x%08x, vcic %d.\n",
                             cic_rec->pcic, cic_rec->vcic));

                SPRC_SendErrorToApp_ANSI(ISUP_MSG_COT,
                                 ITS_ISUP_UNEXP_APPMSG_WAITFOR_COTREPORTS_ERR,
                                 cic_rec);
            }

            break;

        default :
            break;

        }

        ISUP_DEBUG(("WAIT_CONTINUITY_REPORT COT: Received from App."
                    " pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an INF received in the WAIT_CONTINUITY_REPORT state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network.
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
 *      Procedure coded from T1.113-1992 Figure 25/(30 of 41)
 *
 ****************************************************************************/
static void
__ISUP_Received_INF(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
  __ISUP_CPC_Received_INF(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an INR received in the WAIT_CONTINUITY_REPORT state 
 *      is done here. The message is forwarded to the network if received 
 *      from the application.
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
 *      Procedure coded from Q.764 (03/93) Sec. 2.1.6.2. 
 *
 ****************************************************************************/
static void
__ISUP_Received_INR(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
  __ISUP_CPC_Received_INR(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *     The processing for an REL received in WAIT_CONTINUITY_REPORT state is 
 *      done here. The message is forwarded to the application if received  
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
static void
__ISUP_Received_REL(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward REL appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received REL in WAIT_CONTINUITY_REPORT from MTP3, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));


        if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {

            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

            __ISUP_StopCPCToCCO(cic_rec,config_info);

            cic_rec->cco_state = CCO_IDLE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY||
                 cic_rec->cro_state == CRO_WAIT_FOR_OUTGOING_CCR)
        {
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

            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_COT)
        {
            if (cic_rec->dco_state == DCO_IDLE)
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
            }
            else
            {
                __ISUP_StopCROToDCO(cic_rec,config_info);
            }
            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }

        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
        cic_rec->fsm_state = WAIT_OUTGOING_RLC;
    }
    else
    {
        ISUP_DEBUG(("Received REL in WAIT COT REPORT from APP, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {
            __ISUP_StopCPCToCCO(cic_rec,config_info);

            /* Stop ACM Timer T7 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);
            cic_rec->cco_state = CCO_IDLE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY ||
                 cic_rec->cro_state == CRO_WAIT_FOR_OUTGOING_CCR)
        {
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

            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_COT)
        {
            if (cic_rec->dco_state == DCO_IDLE)
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
            }
            else
            {
                __ISUP_StopCROToDCO(cic_rec,config_info);
            }
            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }

        /* Start the REL Procedure */
        __ISUP_StartRELProcedure(msg, cic_rec, config_info, src);

    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an RLC received in  WAIT_CONTINUITY_REPORT state is 
 *      done here. The message is forwarded to the application if received  
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
static void
__ISUP_Received_RLC(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Mark cic as idle and forward RLC appropriately */

    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received RLC in WAIT_CONTINUITY_REPORT from MTP3, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {
            /* Retry Indication to App */
             SPRC_SendIndToApp_ANSI(ITS_ISUP_REL_REATTEMPT_IND, cic_rec);

            /*Stop cpc -> cco */
            __ISUP_StopCPCToCCO(cic_rec,config_info);

            /* Stop ACM Timer T7 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

            /*Send REL*/
            SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NORMAL_UNSPECIFIED,
                                    cic_rec,
                                    config_info);

            /* removed as we don't keep Ckt in Transient state
             * ISUP_CIC_SET_TRANSIENT(cic_rec->cic_state);
             */

            /* Start T5 and T1 */
            __ISUP_StartRELTimers(cic_rec, config_info);

            /* change cic fsm_state to INCOMING RLC */
            cic_rec->fsm_state = WAIT_INCOMING_RLC;
        }
        else if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY)
        {
            /*Nothing specified ignore it*/
        }
        else if(cic_rec->cro_state == CRO_WAIT_FOR_COT)
        {
            /*will not be handled here*/
        }
    }
    else
    {
        ISUP_DEBUG(("Received RLC in WAIT_CONTINUITY_REPORT from APP, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {

            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

            __ISUP_StopCPCToCCO(cic_rec,config_info);

            cic_rec->cco_state = CCO_IDLE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY ||
                 cic_rec->cro_state == CRO_WAIT_FOR_OUTGOING_CCR)
        {
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

            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_COT)
        {
            if (cic_rec->dco_state == DCO_IDLE)
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
            }
            else
            {
                __ISUP_StopCROToDCO(cic_rec,config_info);
            }
            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }

        /* Send to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

        /* Idle ckt and fsm state - clear cic_rec */
        ISUP_ClearCic(cic_rec);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an BLA received in the WAIT_CONTINUITY_REPORT state 
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
__ISUP_Received_BLA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_BLA(msg, cic_rec, config_info, src);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an BLO received in the WAIT_CONTINUITY_REPORT state 
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
__ISUP_Received_BLO(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_BLO(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an LPA received in the WAIT_CONTINUITY_REPORT state 
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
__ISUP_Received_LPA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_LPA(msg, cic_rec, config_info, src);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CPG received in the WAIT_FOR_COT_REPORTS
 *      state is done here. The message is forwarded to the application if 
 *      received from the network.
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
__ISUP_Received_CPG(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{

    if (src != ISUP_SRC_L3_ANSI)
    {
        /* Msg out of sequence. Drop it and generate alarm. */
        ISUP_ERROR(("WAIT_FOR_COT_REPORTS CPG: Unexp CPG from App. pcic 0x%08x, "
                    "vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        ISUP_Alarm_ANSI(3069, __FILE__, __LINE__, "Message: %x cic : %x",
                    msg->data[sizeof(MTP3_HEADER_ANSI) + 
                    sizeof(ITS_USHORT)+ sizeof(ITS_OCTET)],
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)); 
 
        /*Lets send the msg out, we are not supposed to discard
         * even though its wrong, some error condition exists
         * at the application. Any way after recieving this msg
         * the preceeding exchange will reset the circute,
         * let it happen, other wise this error condition will
         * screw up at some other point.
         */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);
    }
    else
    {
        ISUP_DEBUG(("Received CPG in WAIT_FOR_COT_REPORTS from MTP3, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        /* Forward CPG to app ,App will reset ciruit*/
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

        /* Change state to WAIT_FOR_COT_REPORTS, i.e. no change */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGB received in the WAIT_CONTINUITY_REPORT state 
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
__ISUP_Received_CGB(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGB(msg, cic_rec, config_info, src);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGBA received in the WAIT_CONTINUITY_REPORT state 
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
__ISUP_Received_CGBA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGBA(msg, cic_rec, config_info, src);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGU received in the WAIT_CONTINUITY_REPORT state 
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
__ISUP_Received_CGU(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGU(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGUA received in the WAIT_CONTINUITY_REPORT state 
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
__ISUP_Received_CGUA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGUA(msg, cic_rec, config_info, src);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an GRA received in the WAIT_CONTINUITY_REPORT state 
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
__ISUP_Received_GRA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_GRA(msg, cic_rec, config_info, src);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an GRS received in the WAIT_CONTINUITY_REPORT state 
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
__ISUP_Received_GRS(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_GRS(msg, cic_rec, config_info, src);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an RSC received in  WAIT_CONTINUITY_REPORT state is 
 *      done here.
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
__ISUP_Received_RSC(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_RSC(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an UBA received in  WAIT_CONTINUITY_REPORT state is 
 *      done here. The message is forwarded to the application if received  
 *      from the network.
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
__ISUP_Received_UBA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_UBA(msg, cic_rec, config_info, src);
}



/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an UBL received in  WAIT_CONTINUITY_REPORT state is 
 *      done here. The message is forwarded to the application if received  
 *      from the network.
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
__ISUP_Received_UBL(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_UBL(msg, cic_rec, config_info, src);
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an UCIC received in the WAIT_CONTINUITY_REPORT state
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
__ISUP_Received_UCIC(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
      ISUP_DEBUG(("__ISUP_Received_UCIC "));
    __ISUP_CSC_Received_UCIC(msg, cic_rec, config_info, src);

    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CQM received in WAIT_CONTINUITY_REPORT.
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
 *      The processing for an CQR received in WAIT_CONTINUITY_REPORT.
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
 *      The processing for an CCR received in WAIT_CONTINUITY_REPORT.
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
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
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
 *      This function handles the processing of a message not expected in 
 *      the WAIT_CONTINUITY_REPORT state. It also serves as a default handler for 
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
__ISUP_Received_UnexpectedMsg(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                              ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Log error, update stats and drop msg */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from MTP3 in"
                    " WAIT_CONTINUITY_REPORT. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                    msg->data[sizeof(MTP3_HEADER_ANSI) + sizeof (ITS_USHORT) +
                    sizeof(ITS_OCTET)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));

        PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);

        ISUP_Alarm_ANSI(3182, __FILE__, __LINE__, "dpc: %d opc: %d "
                        "cic: %x  Message: %x",
                        MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                        MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                        ISUP_PCIC_TO_CIC(cic_rec->pcic),
                        msg->data[sizeof(MTP3_HEADER_ANSI) + 
                        sizeof(ITS_USHORT) + sizeof(ITS_OCTET)]);

        if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
        {
            /*Stop cpc -> cco */
            __ISUP_StopCPCToCCO(cic_rec,config_info);

            /* Stop Timer T7 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

            /* Send Retry Ind to App */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_RSC_REATTEMPT_RQIND, cic_rec);

           /* Start CPC to CRS */
           __ISUP_CSC_StartCRS(cic_rec, config_info);

           /* change fsm state to Idle */
           cic_rec->fsm_state = IDLE;
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_RLC)
        {
            /*Ignore the message */
        }
    }
    else
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from App in"
                    " WAIT_CONTINUITY_REPORT. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                    msg->data[sizeof(MTP3_HEADER_ANSI) + sizeof (ITS_USHORT) +
                    sizeof(ITS_OCTET)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));

        ISUP_Alarm_ANSI(3183, __FILE__, __LINE__, "Message %x cic : %x",
                         msg->data[sizeof(MTP3_HEADER_ANSI) + 
                         sizeof(ITS_USHORT) + sizeof(ITS_OCTET)],
                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

        /* Send error indication to application. */
        SPRC_SendErrorToApp_ANSI(msg->data[sizeof(MTP3_HEADER_ANSI) +
                                 sizeof (ITS_USHORT) + sizeof(ITS_OCTET)],
                                 ITS_ISUP_UNEXP_APPMSG_WAITFOR_COTREPORTS_ERR,
                                 cic_rec);
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a valid pointer to a message handler function
 *      for the WAIT_CONTINUITY_REPORT state, based on the msgType received.
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI __ISUP_MsgHandlerProc
__ISUP_GetMsgProc_WaitCotReport_ANSI92(ITS_OCTET msgType)
{
    switch(msgType)
    {
    /* Following CPC messages should be treated here */
    case ISUP_MSG_ACM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_ACM;

    case ISUP_MSG_ANM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_ANM;

    case ISUP_MSG_COT:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_COT;
        break;

    case ISUP_MSG_IAM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_IAM;

    case ISUP_MSG_INF:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_INF;

    case ISUP_MSG_INR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_INR;

    case ISUP_MSG_REL:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_REL;
        break;
    case ISUP_MSG_RLC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_RLC;

    /* Following CSC messages are to be routed to CSC */
    case ISUP_MSG_BLO:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_BLO;

    case ISUP_MSG_BLA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_BLA;
    case ISUP_MSG_GRS:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_GRS;

    case ISUP_MSG_GRA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_GRA;

    case ISUP_MSG_CGB:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGB;

    case ISUP_MSG_CGBA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGBA;

    case ISUP_MSG_CGU:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGU;

    case ISUP_MSG_CGUA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGUA;

    case ISUP_MSG_UCIC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UCIC;
    case ISUP_MSG_UBL:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UBL;

    case ISUP_MSG_UBA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UBA;
    case ISUP_MSG_RSC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_RSC;
    case ISUP_MSG_LPA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_LPA;

    case ISUP_MSG_CPG:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CPG;

    case ISUP_MSG_CQM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CQM;
    case ISUP_MSG_CQR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CQR;

    case ISUP_MSG_CCR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CCR;

    case ISUP_MSG_CRA:
    case ISUP_MSG_CRM:
    case ISUP_MSG_CFN:
    case ISUP_MSG_EXM:
    case ISUP_MSG_FOT:
    case ISUP_MSG_PAM:
    case ISUP_MSG_RES:
    case ISUP_MSG_SUS:
    case ISUP_MSG_CVT:
    case ISUP_MSG_CRG:
    case ISUP_MSG_CVR:
        break;

    default:
        /* Unknown message type for ISUP.
         * Send back Confusion message.
         */
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg;
    }
    return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg;
}

/* TIMEOUT Handling */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T7 timer in the 
 *      WAIT_CONTINUITY_REPORT state. 
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Added Failure indication to
 *                           # 484          Application.
 *
 ****************************************************************************/
static void
__ISUP_Received_TimeoutT7(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                          ISUP_OPC_DPC_INFO *config_info)
{

    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT7 event received in WAIT_CONTINUITY_REPORT state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, 
                 ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T7);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT7 in WAIT_CONTINUITY_REPORT state:"
                    " Unable to remove T7 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    /* Stop T24 timer, if running */
    __ISUP_StopCPCToCCO(cic_rec,config_info);

    if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T7].tmr_hndl_layer 
        == ISUP_TMR_HNDL_STACK)
    {
        /* OGC Failure Indication with cause to App */
         SPRC_SendIndToApp_ANSI(ITS_ISUP_CALL_FAILURE_IND,cic_rec);

        /* Send REL to L3 */
        SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NO_USER_RESPONDING,
                                cic_rec,
                                config_info);

        /* Start T5 and T1 */
        __ISUP_StartRELTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }
    else
    {
        /* App wants to take action on this Timeout
         * It is supposed to send REL request to isup
         */

        /* So change state to WAIT_OUTGOING_REL */
        cic_rec->fsm_state = WAIT_OUTGOING_REL;
    }

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);


}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T9 timer in the 
 *      WAIT_CONTINUITY_REPORT state. 
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
__ISUP_Received_TimeoutT9(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                          ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT9 event received in WAIT_CONTINUITY_REPORT state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, 
                 ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T9);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT9 in WAIT_CONTINUITY_REPORT state:"
                    " Unable to remove T9 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T9].tmr_hndl_layer 
        == ISUP_TMR_HNDL_STACK)
    {
        /* Do the thing. Phase II. */
        /* Send REL to L3 */
        SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NO_ANSWER_FROM_USER,
                                 cic_rec,
                                 config_info);

        /* Start T5 and T1 */
        __ISUP_StartRELTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }
    else
    {
        /* Change state to WAIT_OUTGOING_REL */
        cic_rec->fsm_state = WAIT_OUTGOING_REL;
    }

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T12 timer in the 
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
 *      WAIT_CONTINUITY_REPORT state. 
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
    __ISUP_CSC_Received_TimeoutT24(t_entry,cic_rec,config_info);
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of TCCR timer in the 
 *      WAIT_CONTINUITY_REPORT state. 
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
__ISUP_Received_TimeoutTCCR(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutTCCR(t_entry,cic_rec,config_info);
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T25 timer in the 
 *      WAIT_CONTINUITY_REPORT state. 
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
__ISUP_Received_TimeoutT25(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT25(t_entry,cic_rec,config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T26 timer in the 
 *      WAIT_CONTINUITY_REPORT state. 
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
__ISUP_Received_TimeoutT26(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT26(t_entry,cic_rec,config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T28 timer in the 
 *      WAIT_CONTINUITY_REPORT state. 
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

    ISUP_DEBUG(("TimeoutT28 event received in WAIT_CONTINUITY_REPORT state. "
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
        ISUP_ERROR(("TimeoutT28 in WAIT_CONTINUITY_REPORT state: Unable to remove T28 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T33 timer in the 
 *      WAIT_CONTINUITY_REPORT state. 
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
__ISUP_Received_TimeoutT33_ANSI92(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing of a timeout not expected in 
 *      the WAIT_CONTINUITY_REPORT state. It also serves as a default handler for 
 *      any errors arising from out-of-range function calls.
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
    ISUP_ERROR(("Rcvd Unexpected Timeout T%d for CIC %d in "
              "WAIT_CONTINUITY_REPORT.cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                t_entry->timerId, t_entry->cic,
                cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));
    /* Could print out mtp3 header or entire ITS_EVENT */ 


    ISUP_Alarm_ANSI(3184, __FILE__, __LINE__, "State: %x Timer id: T%d",
                           cic_rec->cic_state,t_entry->timerId);

    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a timout handler procedure for  
 *      the WAIT_CONTINUITY_REPORT state, based on the ID of the timer that has 
 *      expired.
 *
 *  Input Parameters:
 *      timerID: the ID of the timer that expired, per ISUP.
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
__ISUP_GetTimeoutProc_WaitCotReport_ANSI92(ITS_UINT timerID)
{
    switch(timerID)
    {
    case ITS_ISUP_TIMER_T1: /*  1    First RLC timer        */
        break;
    case ITS_ISUP_TIMER_T5: /*  5    Second RLC timer       */
        break;
    case ITS_ISUP_TIMER_T6: /*  6    RES timer (network)    */
        break;
    case ITS_ISUP_TIMER_T7: /*  7    ACM timer              */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT7;
    case ITS_ISUP_TIMER_T8: /*  8    COT timer              */
        break;
    case ITS_ISUP_TIMER_T9: /*  9    ANM timer              */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT9;
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
        break;
    case ITS_ISUP_TIMER_T25: /* 25   CCR timing timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT25;
        break;
    case ITS_ISUP_TIMER_T26: /* 26   CCR response timer     */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT26;
        break;
    case ITS_ISUP_TIMER_T27: /* 27   CCR receive timer      */
        break;
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
    case ITS_ISUP_TIMER_T34: /* 34   Circuit query timer    */
        break;
    case ITS_ISUP_TIMER_T35: /* 35          */
        break;
    case ITS_ISUP_TIMER_T36: /* 36          */
        break;
    case ITS_ISUP_TIMER_T37: /* 37          */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT37_ANSI92;
        break;
    case ITS_ISUP_TIMER_TCCR: /* 37          */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutTCCR;
        break;
    default:
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;
    }
    return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;
}

