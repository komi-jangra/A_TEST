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
 * ID:$Id: itu-wait_in_cot_itu93.c,v 1.1.1.1 2007-10-08 11:12:19 bsccs2 Exp $
 * LOG:$Log: not supported by cvs2svn $
 * LOG:Revision 1.1.1.1  2007/10/04 13:24:54  bsccs2
 * LOG:init tree
 * LOG:
 * LOG:Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
 * LOG:BscCs2
 * LOG:
 * LOG:Revision 1.1.1.1  2007/03/08 15:15:12  cvsadmin
 * LOG:BSC project
 * LOG:
 * LOG:Revision 9.2  2005/04/06 07:17:24  ssingh
 * LOG:ISUP Bug Fix propagation. BugId #389 (kramesh)
 * LOG:
 * LOG:Revision 9.1  2005/03/23 12:54:58  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 8.9  2005/03/21 13:54:09  cvsadmin
 * LOG:PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG:Revision 1.2.2.2.6.1.12.1  2005/02/08 12:30:26  ssingh
 * LOG:Peg increament after receiving Unexpected Msg in given FSM state.
 * LOG:Bug# 1448. (Ramesh KV, Abhijit Dutta)
 * LOG:
 * LOG:Revision 1.2.2.2.6.1  2004/01/05 10:10:45  sjaddu
 * LOG:Merged code from tcs isup branch.
 * LOG:
 * LOG:Revision 1.2.2.2.2.1  2003/09/05 09:44:02  akumar
 * LOG:Modifications for Msg Based redundancy scheme.
 * LOG:
 * LOG:Revision 1.2.2.2  2003/07/25 05:13:08  akumar
 * LOG:ITU National Matter is implemented.
 * LOG:
 * LOG:Revision 1.2.2.1  2003/05/07 11:03:13  ssingh
 * LOG:Latest Changes propped from Current to 6.3
 * LOG:
 * LOG:Revision 8.5  2003/05/02 14:36:17  ssingh
 * LOG:ANSI changes propped to ITU (common and related).
 * LOG:
 * LOG:Revision 8.4  2003/04/03 15:29:29  sjaddu
 * LOG:ISUP DSM reorganization.
 * LOG:
 * LOG:Revision 8.3  2003/02/21 05:35:03  akumar
 * LOG:Solved Problem wrt CQM/CQR
 * LOG:
 * LOG:Revision 8.2  2003/02/21 05:16:41  akumar
 * LOG:Added CQM/CQR Procedures
 * LOG:
 * LOG:Revision 8.1  2003/02/13 17:44:30  yranade
 * LOG:Begin PR6.4
 * LOG:
 * LOG:Revision 1.2  2003/02/05 18:55:29  sjaddu
 * LOG:Fixed new line strings errors compiled with cc.
 * LOG:
 * LOG:Revision 1.1  2003/01/22 09:20:30  akumar
 * LOG:Added new file for COT handling
 * LOG:
 *****************************************************************************/

#undef CCITT
#undef ANSI
#define CCITT

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <isup_variants.h>

#include <isup_intern.h>
#include <itu/isup_93.h>

/*
 * Functions for handling messages in the WAIT_INCOMING_COT state for 
 * ITU93 variant.This is considered to be the generic ITU variant, and
 * all other ITU variants use these functions as defaults if they do not
 * have different behaviour.
 */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an IAM received in the WAIT_INCOMING_COT state 
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
 *      Procedure coded from the SDL Q.764-Annex H Fig H.21
 *
 ****************************************************************************/
static void
__ISUP_Received_IAM(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ITU)    /* CPC Incoming */
    {
        ISUP_DEBUG(("Received IAM in WAIT_INCOMING_COT from MTP3, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cci_state == CCI_WAIT_FOR_COT)
        {
            /*Nothing needs to be done */
        }
        else if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
            ISUP_ClearCic(cic_rec);

            cic_rec->fsm_state = WAIT_OUTGOING_ACM;
            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
        }
        else if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T36);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;

            cic_rec->fsm_state = WAIT_OUTGOING_ACM;
            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
        }
    }
    else
    {
        ISUP_DEBUG(("Received IAM in WAIT_INCOMING_COT from APP, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        /* Forward IAM to MTP3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* State remains same */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an SAM received in the WAIT_INCOMING_COT state is
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
 ****************************************************************************/
static void
__ISUP_Received_SAM(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if(src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received SAM in WAIT_INCOMING_COT from MTP3, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        /* Send this message to the Application, no change in state */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
    }
    else
    {
        ISUP_ERROR(("Received Unwxpected SAM from App in WAIT_INCOMING_COT"));
        /* FIXME - Raise an Alarm */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an REL received in the WAIT_INCOMING_COT state is 
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
 ****************************************************************************/
static void
__ISUP_Received_REL(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward REL appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received REL in WAIT_INCOMING_COT from MTP3, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));


        if (cic_rec->cci_state == CCI_WAIT_FOR_COT)
        {
            __ISUP_StopCPCToCCI(cic_rec,config_info);
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T8);
            cic_rec->cci_state = CCI_IDLE;
            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
            cic_rec->fsm_state = WAIT_OUTGOING_RLC;

        }
        else if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
            cic_rec->fsm_state = WAIT_OUTGOING_RLC;

        }
        else if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T36);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;

            /* Change cic state to idle */
            ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);
            SPRC_SendRLCToMTP3_CCITT(CI_CAUSE_NORMAL, cic_rec,
                                                 config_info);

            /* FIXEME - Send an Ind to the Applicayion, that RLC is sent */
            SPRC_SendIndToApp_CCITT(ITS_ISUP_RLC_RELEASE_IND,cic_rec);

            /* Clear cic_rec */
            ISUP_ClearCic(cic_rec);
        }
        else
        {
            ISUP_ERROR(("Received REL in WAIT IN COT from MTP3, CRI state IDLE "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            /* FIXME - Raise an Alarm */
            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
            cic_rec->fsm_state = WAIT_OUTGOING_RLC;
            return;
        }

    }
    else 
    {
        ISUP_DEBUG(("Received REL in WAIT_INCOMING_COT from APP, "
                     "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cci_state == CCI_WAIT_FOR_COT)
        {
            __ISUP_StopCPCToCCI(cic_rec,config_info);
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T8);

            /* Removed as we don't keep Ckt in Transient
             * ISUP_CIC_SET_TRANSIENT(cic_rec->cic_state);
             */

            cic_rec->cci_state = CCI_IDLE;
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

        /* Start the REL Procedure */
        __ISUP_StartRELProcedure(msg, cic_rec, config_info, src);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an RLC received in the WAIT_INCOMING_COT state is 
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
 ****************************************************************************/
static void
__ISUP_Received_RLC(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward RLC appropriately */

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received RLC in WAIT_INCOMING_COT from MTP3, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cci_state == CCI_WAIT_FOR_COT)
        {
            __ISUP_StopCPCToCCI(cic_rec,config_info);
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T8);

            SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_COT_RELEASE_RQIND, cic_rec);

            SPRC_SendRELToMTP3_CCITT(CI_CAUSE_NORMAL_UNSPECIFIED,
                                                     cic_rec,config_info);
            __ISUP_StartRELTimers(cic_rec, config_info);

            cic_rec->cci_state = CCI_IDLE;
            cic_rec->fsm_state = WAIT_INCOMING_RLC;
        }
    }
    else 
    {
        ISUP_DEBUG(("Received RLC in WAIT_INCOMING_COT from APP, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cci_state == CCI_WAIT_FOR_COT)
        {
            __ISUP_StopCPCToCCI(cic_rec,config_info);
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T8);
            cic_rec->cci_state = CCI_IDLE;

        }
        else if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T27);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;

        }
        else if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T36);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }

        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* Change cic crr_state to idle */
        cic_rec->crr_state = CRR_IDLE;

        /* Idle ckt and fsm state - clear cic_rec */
        ISUP_ClearCic(cic_rec);
    }
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing of COT message in  
 *      the WAIT_INCOMING_COT state. 
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
__ISUP_Received_COT(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                              ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int offset = 0 ,tret = 0;

    if (src == ISUP_SRC_L3_ITU)
    {
        /* Check for failed or success indicator */
        offset = sizeof(MTP3_HEADER_CCITT) + sizeof(ITS_USHORT) +
                 sizeof(ITS_OCTET);

        if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T36);

            __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T27,
                             config_info->
                             tmr_hndl_info[ITS_ISUP_TIMER_T27].tmr_value);
            
            cic_rec->cri_state = CRI_WAIT_FOR_CCR;

            if (cic_rec->cot_first_ind == ITS_TRUE)
            {
                /* FIXME - Send an Alarm */
                cic_rec->cot_first_ind = ITS_FALSE;
            }
            switch(msg->data[offset+1] & 0x01U)
            {
            case CONTINUITY_CHECK_SUCCESS:
                ISUP_CRITICAL((" Unexpected COT Received In Wait For REL\n"));
                break;
            case CONTINUITY_CHECK_FAILED:
                ISUP_DEBUG((" COT Falure Received In Wait For REL\n"));
                break;
            }

        }

        switch (msg->data[offset+1] & 0x01U)
        {
        case CONTINUITY_CHECK_SUCCESS:

            if (cic_rec->cci_state == CCI_WAIT_FOR_COT)
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);

               ISUP_DEBUG(("In WAIT_INCOMING_COT COT: SUCCESSFUL Received"
                            " from L3. pcic 0x%08x,vcic %d.\n",
                              cic_rec->pcic, cic_rec->vcic));

                cic_rec->cci_state = CCI_IDLE;
                cic_rec->fsm_state = WAIT_OUTGOING_ACM;
            }
            break;

        case CONTINUITY_CHECK_FAILED:

            if (cic_rec->cci_state == CCI_WAIT_FOR_COT)
            {
                tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T27,
                                 config_info->
                                 tmr_hndl_info[ITS_ISUP_TIMER_T27].tmr_value);
                if (tret != ITS_SUCCESS)
                {
                    ISUP_ERROR(("WAIT_INCOMING_COT: Failed to start T27."
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
                }
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
                /* FIXME - Raise an Alarm */

                /* Wait for Continuity check request */
                cic_rec->cri_state = CRI_WAIT_FOR_CCR;

                cic_rec->cci_state = CCI_IDLE;
            }
            break;

        default:

            break;
        } 
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
    }
    else
    {
        ISUP_ERROR(("Received Unwxpected COT from App in WAIT_INCOMING_COT"));
        /* FIXME - Raise an Alarm */

        /* Send error indication to application. */
        SPRC_SendErrorToApp_CCITT(ISUP_MSG_COT,
                                 ITS_ISUP_UNEXP_APPMSG_WAITINC_COT_ERR,
                                 cic_rec);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CQM received in the WAIT_INCOMING_COT state
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
__ISUP_Received_CQM(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CQM(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CQR received in the WAIT_INCOMING_COT state
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
__ISUP_Received_CQR(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CQR(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an BLA received in the WAIT_INCOMING_COT state 
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
 *      The processing for an BLO received in the WAIT_INCOMING_COT state 
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
 *      The processing for an CCR received in the WAIT_INCOMING_COT state 
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
__ISUP_Received_CCR(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CCR(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGB received in the WAIT_INCOMING_COT state 
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
 *      The processing for an CGBA received in the WAIT_INCOMING_COT state 
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
 *      The processing for an CGU received in the WAIT_INCOMING_COT state 
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
 *      The processing for an CGUA received in the WAIT_INCOMING_COT state 
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
 *      The processing for an GRA received in the WAIT_INCOMING_COT state 
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
 *      The processing for an GRS received in the WAIT_INCOMING_COT state 
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
 *      The processing for an RSC received in the WAIT_INCOMING_COT state is 
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
 *      The processing for an UBA received in the WAIT_INCOMING_COT state is 
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
 *      The processing for an UBL received in the WAIT_INCOMING_COT state is 
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
 *      The processing for an UCIC received in the WAIT_IN_COT state is done
 *      here.
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
 *      The processing for an LPA received in the WAIT_INCOMING_COT state
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
 *      This function handles the processing of a message not expected in 
 *      the WAIT_INCOMING_COT state. It also serves as a default handler for 
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
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from MTP3 in WAIT_INCOMING_COT"
                     "cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                     msg->data[sizeof(MTP3_HEADER_CCITT) + sizeof(ITS_USHORT) +
                                                             sizeof(ITS_OCTET)],
                     cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));
        
        PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);
        /* FIXME - Send a Alarm */

        if (cic_rec->cci_state == CCI_WAIT_FOR_COT)
        {
            cic_rec->cci_state = CCI_IDLE;
        }
        if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if(cic_rec->cri_state == CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T36);

           /* remove loop
           - Enable echo suppressor, if any */
           /* FIXME - Send an indication to the Application
            * to remove the Loop
            */

           /* Idle the Ckt*/
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        /* Start CPC to CRS */
        __ISUP_CSC_StartCRS(cic_rec, config_info);
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }
    else
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from App in WAIT_INCOMING_COT. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                    msg->data[sizeof(MTP3_HEADER_CCITT) + sizeof(ITS_USHORT)
                                                        + sizeof(ITS_OCTET)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));
        /* FIXME - Send a Alarm */

        /* Send error indication to application. */
        SPRC_SendErrorToApp_CCITT(msg->data[sizeof(MTP3_HEADER_CCITT) +
                                 sizeof (ITS_USHORT) + sizeof(ITS_OCTET)],
                                 ITS_ISUP_UNEXP_APPMSG_WAITINC_COT_ERR,
                                 cic_rec);
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a valid pointer to a message handler function
 *      for the WAIT_INCOMING_COT state, based on the msgType received.
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
__ISUP_GetMsgProc_WaitIncomingCot_ITU93(ITS_OCTET msgType)
{
    switch(msgType)
    {
    /* Following CPC messages should be treated here */
    case ISUP_MSG_IAM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_IAM;
        break;
    case ISUP_MSG_SAM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_SAM;
        break;
    case ISUP_MSG_REL:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_REL;
        break;
    case ISUP_MSG_RLC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_RLC;
        break;
    
    case ISUP_MSG_COT:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_COT;
        break;

    /* Following CSC messages are to be routed to CSC */
    case ISUP_MSG_BLO:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_BLO;

    case ISUP_MSG_BLA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_BLA;

    case ISUP_MSG_UBL:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UBL;

    case ISUP_MSG_UBA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UBA;

    case ISUP_MSG_RSC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_RSC;

    case ISUP_MSG_CCR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CCR;

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

    case ISUP_MSG_CQM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CQM;

    case ISUP_MSG_CQR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CQR;
    case ISUP_MSG_UCIC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UCIC;
    case ISUP_MSG_LPA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_LPA;

    /*Handle Other Messages */
    case ISUP_MSG_ACM:
    case ISUP_MSG_ANM:
    case ISUP_MSG_CFN:
    case ISUP_MSG_FOT:
    case ISUP_MSG_RES:
    case ISUP_MSG_SUS:
    case ISUP_MSG_CRG:
    case ISUP_MSG_PAM:
    case ISUP_MSG_CPG:
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
 *      This function handles the processing at expiry of T8 timer in the 
 *      WAIT_INCOMING_COT state. 
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
    if(cic_rec->cci_state == CCI_WAIT_FOR_COT)
    {
        /*Send REL message to L3 */
        SPRC_SendRELToMTP3_CCITT(CI_CAUSE_NORMAL_UNSPECIFIED,
                                          cic_rec,config_info);
        __ISUP_StartRELTimers(cic_rec, config_info);

        /*Change CCI state to IDLE*/
        cic_rec->cci_state = CCI_IDLE;

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

    SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_COT_RELEASE_RQIND, cic_rec);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T12 timer in the 
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      WAIT_INCOMING_COT state. 
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
 *      This function handles the processing at expiry of T27 timer in the 
 *      WAIT_INCOMING_COT state. 
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
    __ISUP_CSC_Received_TimeoutT27(t_entry,cic_rec,config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T28 timer in the 
 *      WAIT_INCOMING_COT state. 
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

    ISUP_DEBUG(("TimeoutT28 event received in WAIT_INCOMING_COT state. "
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
        ISUP_ERROR(("TimeoutT28 in WAIT_INCOMING_COT state:"
                    "Unable to remove T28 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

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
 *      This function handles the processing of a timeout not expected in 
 *      the WAIT_INCOMING_COT state. It also serves as a default handler for 
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
    ISUP_ERROR(("Rcvd Unexpected Timeout T%d for CIC %d from MTP3 in "
                "WAIT_INCOMING_COT. cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                t_entry->timerId, t_entry->cic, 
                cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));
    /* Could print out mtp3 header or entire ITS_EVENT */ 
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
    /* FIXME - Send an Alarm */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a timout handler procedure for  
 *      the WAIT_INCOMING_COT state, based on the ID of the timer that has 
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
__ISUP_TimeoutHandlerProc
        __ISUP_GetTimeoutProc_WaitIncomingCot_ITU93(ITS_UINT timerID)
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
        break;
    case ITS_ISUP_TIMER_T8: /*  8    COT timer              */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT8;
        break;
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
        break;
    case ITS_ISUP_TIMER_T25: /* 25   CCR timing timer       */
        break;
    case ITS_ISUP_TIMER_T26: /* 26   CCR response timer     */
        break;
    case ITS_ISUP_TIMER_T27: /* 27   CCR receive timer      */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT27;
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
        break;
    case ITS_ISUP_TIMER_T34: /* 34   SGM timer    */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT34;
        break;
    case ITS_ISUP_TIMER_T35: /* 35          */
        break;
    case ITS_ISUP_TIMER_T36: /* 36   COT Timer, While waiting for REL */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT36;
        break;
    case ITS_ISUP_TIMER_T37: /* 37    ECHO Control Procedure  */
        break;
    default:
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;
    }
    return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;
}
