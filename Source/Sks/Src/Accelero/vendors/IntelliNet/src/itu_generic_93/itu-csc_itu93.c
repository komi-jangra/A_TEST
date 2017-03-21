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
 *  ID: $Id: itu-csc_itu93.c,v 1.1.1.1 2007-10-08 11:12:18 bsccs2 Exp $
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
 * LOG: Revision 9.2  2005/04/08 06:47:44  ssingh
 * LOG: ISUP bug fix propagation (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:57  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.10  2005/03/21 13:54:05  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.6.2.1.12.2  2005/02/11 05:54:30  ssingh
 * LOG: Changes to fix bug#1447 [pegs for RSC(T17)/GRS(T23)
 * LOG: timer expiry and respective peg increament.
 * LOG: (Ramesh KV, Abhijit D)
 * LOG:
 * LOG: Revision 7.4.2.6.2.1.12.1  2004/12/29 14:56:04  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.4.2.6.2.1  2004/01/05 10:10:45  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.4.2.4.2.9  2003/12/12 09:06:27  ssingh
 * LOG: Code changed to move "RangeNstatus check failed"
 * LOG: alarms from App to Network.
 * LOG:
 * LOG: Revision 7.4.2.4.2.8  2003/11/24 06:40:44  akumar
 * LOG: bug fix cycle.
 * LOG:
 * LOG: Revision 7.4.2.4.2.7  2003/11/14 10:36:29  akumar
 * LOG: Bug Fix #658.
 * LOG:
 * LOG: Revision 7.4.2.4.2.6  2003/11/13 13:17:49  akumar
 * LOG: Bug fixing cycle for TCS-ISUP.
 * LOG:
 * LOG: Revision 7.4.2.4.2.5  2003/10/28 08:35:04  akumar
 * LOG: Got alarm id correct.
 * LOG:
 * LOG: Revision 7.4.2.4.2.4  2003/10/21 06:21:05  akumar
 * LOG: Grammer error resolved.
 * LOG:
 * LOG: Revision 7.4.2.4.2.3  2003/10/17 09:20:11  akumar
 * LOG: Fixed req no R480-17 for TCS, DEBUG statment mod.
 * LOG:
 * LOG: Revision 7.4.2.4.2.2  2003/10/17 07:14:56  akumar
 * LOG: Fixed req no R480-17 for TCS.
 * LOG:
 * LOG: Revision 7.4.2.4.2.1  2003/09/05 09:44:01  akumar
 * LOG: Modifications for Msg Based redundancy scheme.
 * LOG:
 * LOG: Revision 7.4.2.4  2003/07/25 05:11:42  akumar
 * LOG: ITU National Matter is implemented.
 * LOG:
 * LOG: Revision 7.4.2.3  2003/05/07 11:03:12  ssingh
 * LOG: Latest Changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.4  2003/05/02 14:36:17  ssingh
 * LOG: ANSI changes propped to ITU (common and related).
 * LOG:
 * LOG: Revision 8.3  2003/04/30 05:14:57  akumar
 * LOG: Buf Fix #254.
 * LOG:
 * LOG: Revision 8.2  2003/04/03 15:29:29  sjaddu
 * LOG: ISUP DSM reorganization.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:30  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.4  2003/02/05 18:55:29  sjaddu
 * LOG: Fixed new line strings errors compiled with cc.
 * LOG:
 * LOG: Revision 7.3  2003/01/22 08:32:25  akumar
 * LOG: Added ITU COT procedure
 * LOG:
 * LOG: Revision 7.2  2002/10/10 10:40:12  sjaddu
 * LOG: Added Alarms for ITU93/97.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:33  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.6  2002/08/01 15:57:49  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.5  2002/07/09 20:38:19  pmandal
 * LOG: Fixed warnings.
 * LOG:
 * LOG: Revision 1.4  2002/07/05 21:27:56  ssharma
 * LOG: Fix Linux warnings.
 * LOG:
 * LOG: Revision 1.3.2.3  2002/07/31 16:12:24  ssharma
 * LOG: Performance improvements.
 * LOG:
 * LOG: Revision 1.3.2.2  2002/07/10 19:34:16  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 1.3.2.1  2002/07/06 20:06:42  hbalimid
 * LOG: Fixed all warnings.
 * LOG:
 * LOG: Revision 1.3  2002/06/24 17:00:44  ssingh
 * LOG: Phase 3 missing functionality and auto timer handling.
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:46:49  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 1.1.2.5  2002/05/09 18:38:10  labuser
 * LOG: Merge from ISUP_APR_19_2002 branch to PR6.
 * LOG:
 * LOG: Revision 1.1.2.4.2.1  2002/04/29 20:40:14  labuser
 * LOG: Fix bug in handling of GRS/GRA.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/04/05 19:37:44  ssharma
 * LOG: Add parameter to timeout handling procedures.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/04/02 23:53:54  ssharma
 * LOG: Completion of phase 2, coding standards conformance.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/04/01 21:08:02  ssharma
 * LOG: Fix memory leaks in ISUP_FindXX() functions.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/03/28 20:49:29  ssharma
 * LOG: First version
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
#include <itu/isup_93.h>

/*
 * Functions for CSC procedures
 */

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an BLA received in any state is done here.
 *      The message is forwarded to the application if received from the 
 *      network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the message event
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *      src - source of event (L3 or application)
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
void
__ISUP_CSC_Received_BLA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received BLA from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->bls_state == BLS_IDLE)
        {
            /* Alert maintenance system */
            ISUP_CRITICAL(("Got unexpected BLA, pcic 0x%08x, vcic %d.\n",
                 cic_rec->pcic, cic_rec->vcic)); 

            ISUP_Alarm_CCITT(3430, __FILE__, __LINE__, "pCIC : %x",
                                                        cic_rec->pcic);

            if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) != CKTS_LBLOCKED))
            {
                PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS,
                                        PEG_ISUP_CIC_UNEXP_BLA_ABNORMAL_ACK);
            }
            
            /* Discard message */
        }
        else if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
        {
            /* We are in WaitForBLA state */
            /* This is a response to a BLO sent earlier */
            /* Stop timers T13, T12. */
            __ISUP_StopBLOTimers(cic_rec, config_info);

            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

            cic_rec->bls_state = BLS_LBLOCKED;

            ISUP_Alarm_CCITT(3431, __FILE__, __LINE__, "pCIC : %x",
                                                        cic_rec->pcic);
        }
    }
    else 
    {
        ISUP_DEBUG(("Received BLA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->blr_state == BLR_WAIT_FOR_BLO_RESP)
        {
            ISUP_Alarm_CCITT(3432, __FILE__, __LINE__, "pCIC : %x",
                                                        cic_rec->pcic);

            /* Send to L3 */
            SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

            /* Mark CIC state accordingly: Remotely blocked */
            cic_rec->cic_state &= 0xFDU;
            cic_rec->cic_state |= CKTS_RBLOCKED;

            cic_rec->blr_state = BLR_RBLOCKED;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an BLO received in any state is done here.
 *      The message is forwarded to the application if received from the 
 *      network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the message event
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *      src - source of event (L3 or application)
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
void
__ISUP_CSC_Received_BLO(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received BLO from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->blr_state == BLR_IDLE)
        {
            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

            /* Maintenance system ind */
            ISUP_CRITICAL(("Received BLO, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic));

            __ISUP_BlockingBLRToCPCO(cic_rec, config_info);

            cic_rec->blr_state = BLR_WAIT_FOR_BLO_RESP;
        }
        else if (cic_rec->blr_state == BLR_RBLOCKED)
        {
            /* Automatically send BLA to remote */
            SPRC_SendBLAToMTP3_CCITT(cic_rec, config_info);
        }
        else if (cic_rec->blr_state == BLR_WAIT_FOR_UBL_RESP)
        {
            ISUP_Alarm_CCITT(3432, __FILE__, __LINE__, "pCIC : %x",
                                                        cic_rec->pcic);

            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

            cic_rec->blr_state = BLR_WAIT_FOR_BLO_RESP;
        }

        /* Stop CRO BLR->CRO */
        __ISUP_StopBLRToCRO(cic_rec, config_info);

        /* Stop CRI BLR->CRI */
        __ISUP_StopBLRToCRI(cic_rec, config_info);

        /* Change state to IDLE, i.e. no change. */
    }
    else 
    {
        ISUP_DEBUG(("Received BLO from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Process according to BLS state */
        if (cic_rec->bls_state == BLS_IDLE)
        {
            /* Mark CIC state accordingly: Locally Blocked */
            cic_rec->cic_state &= 0xFEU;
            cic_rec->cic_state |= CKTS_LBLOCKED;

            /* Maintenance system ind */
            ISUP_CRITICAL(("Got Blocking Req, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic)); 

            __ISUP_BlockingBLSToCPC(cic_rec, config_info);

            /* Send to L3 */
            SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

            __ISUP_StartBLOTimers(cic_rec, config_info);

            cic_rec->bls_state = BLS_WAIT_FOR_BLA;
        }
        else if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
        {
            /* Send to L3 */
            SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

            /* Restart timers */
            __ISUP_StopBLOTimers(cic_rec, config_info);

            __ISUP_StartBLOTimers(cic_rec, config_info);
        }

        __ISUP_StopBLSToCRO(cic_rec,config_info);
        __ISUP_StopBLSToCRI(cic_rec,config_info);

        /* No change in ISUP state */
    }
}



/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGB received in any state is done here.
 *      The message is forwarded to the application if received from the 
 *      network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the message event
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *      src - source of event (L3 or application)
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
void
__ISUP_CSC_Received_CGB(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_USHORT affected_cics[256];
    ITS_USHORT num_affected_cics;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("CGB RangeStatus check failed (%d), pcic 0x%08x, vcic %d.\n",
                 ret, cic_rec->pcic, cic_rec->vcic));

        if (src != ISUP_SRC_L3_ITU)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_CCITT(ISUP_MSG_CGB,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);
        }
        else
        {
            ISUP_Alarm_CCITT(3433, __FILE__, __LINE__, "CIC : %d, Range: %d",
                                 cic, rs_ie.param_data.rangeAndStatus.range);
        }
        return;
    }

    /* Forward CGB appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received CGB from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (sup_msg_type == MAINTENANCE_ORIENTED)
        {
            if (cic_rec->mgbr_state == MGBR_IDLE)
            {
                /* Maintenance system ind */
                ISUP_CRITICAL(("Received Group Blocking Request, pcic 0x%08x, "
                               "vcic %d.\n", cic_rec->pcic, cic_rec->vcic)); 

                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                           __ISUP_BlockingMGBRToCPCO,
                                           cic_rec, config_info);

                /* Send to app */
                SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

                cic_rec->mgbr_state = MGBR_WAIT_FOR_BLO_RESP;

            }
        }
        else if (sup_msg_type == HARD_FAILURE_ORIENTED)
        {
            if (cic_rec->hgbr_state == HGBR_IDLE)
            {
                /* Send to app */
                SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

                /* Maintenance system ind */
                ISUP_CRITICAL(("Received Group Blocking Request, pcic 0x%08x, "
                               "vcic %d.\n", cic_rec->pcic, cic_rec->vcic)); 

                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                           __ISUP_ReleaseHGBRToCPC,
                                           cic_rec, config_info);

                cic_rec->hgbr_state = HGBR_WAIT_FOR_BLO_RESP;

            }
        }
        else
        {
            /* error, discard */
        }
    }
    else 
    {
        ISUP_DEBUG(("Received CGB from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (sup_msg_type == MAINTENANCE_ORIENTED)
        {
            if (cic_rec->mgbs_state == MGBS_IDLE)
            {
                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                           __ISUP_BlockingMGBSToBLS,
                                           cic_rec, config_info);

                __ISUP_ProcessAffectedCics(affected_cics,
                                               num_affected_cics,
                                               __ISUP_StopMGBSToCRI,
                                               cic_rec, config_info);

                /* store the message in cic rec */
                cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, isdsmlocal);
                memcpy(cic_msg->cgb_msg, msg->data, msg->len);
                cic_msg->cgb_msg_len = msg->len;
                ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, isdsmlocal);

                /* Send to L3 */
                SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
        
                /* Maintenance system ind */
                ISUP_CRITICAL(("Received Group Blocking Request, pcic 0x%08x, "
                               "vcic %d.\n", cic_rec->pcic, cic_rec->vcic)); 
                
                __ISUP_StartCGBTimers(cic_rec, config_info);

                cic_rec->mgbs_state = MGBS_WAIT_FOR_CGBA;
            }
        }
        else if (sup_msg_type == HARD_FAILURE_ORIENTED)
        {
            if (cic_rec->hgbs_state == HGBS_IDLE)
            {
                /* store the message in cic rec */
                cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, isdsmlocal);
                memcpy(cic_msg->cgb_msg, msg->data, msg->len);
                cic_msg->cgb_msg_len = msg->len;
                ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, isdsmlocal);

                /* Send to L3 */
                SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
                
                /* Maintenance system ind */
                ISUP_CRITICAL(("Received Group Blocking Request, pcic 0x%08x, "
                               "vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                           __ISUP_BlockingHGBSToHLB,
                                           cic_rec, config_info);

                __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                           __ISUP_ReleaseHGBSToCPC,
                                           cic_rec, config_info);

                __ISUP_StartCGBTimers(cic_rec, config_info);

                cic_rec->hgbs_state = HGBS_WAIT_FOR_CGBA;
            }
        }
        else
        {
            /* error, discard */
        }

        /* Change state to IDLE */
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGBA received in any state is done here.
 *      The message is forwarded to the application if received from the 
 *      network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the message event
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *      src - source of event (L3 or application)
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
void
__ISUP_CSC_Received_CGBA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_OCTET sup_msg_type;
    ITS_BOOLEAN bool_ret;
    ITS_USHORT affected_cics[256];
    ITS_USHORT num_affected_cics;
    ITS_USHORT cic;

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("CGBA RangeStatus check failed (%d), pcic 0x%08x, vcic %d.\n",
                 ret, cic_rec->pcic, cic_rec->vcic));

        if (src != ISUP_SRC_L3_ITU)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_CCITT(ISUP_MSG_CGBA,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);
        }
        else
        {
            ISUP_Alarm_CCITT(3435, __FILE__, __LINE__, "CIC : %d, Range: %d",
                                 cic, rs_ie.param_data.rangeAndStatus.range);
        }
        return;
    }

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received CGBA from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        
        if (sup_msg_type == MAINTENANCE_ORIENTED)
        {
            if (cic_rec->mgbs_state == MGBS_IDLE)
            {
                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                bool_ret = __ISUP_ProcessAffectedCics(affected_cics, 
                                                      num_affected_cics,
                                                      __ISUP_MGBSCheckLocallyBlocked,
                                                      cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("Received invalid CGBA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    ISUP_Alarm_CCITT(3436, __FILE__, __LINE__, "pCIC : %x,"
                                     "Range: %d", cic_rec->pcic,
                                     rs_ie.param_data.rangeAndStatus.range);
                    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS,
                                     PEG_ISUP_CIC_UNEXP_CGBA_ABNORMAL_ACK);
                }
                else
                {
                    ISUP_DEBUG(("Received valid CGBA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                }

                /* No change in MGBS state */
            }
            else if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGBA)
            {
                /* Stop timers T18, T19 */
                __ISUP_StopCGBTimers(cic_rec, config_info);

                bool_ret = __ISUP_CompareCGBAWithCGB(msg, cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    ISUP_Alarm_CCITT(3436, __FILE__, __LINE__, "pCIC : %x,"
                                     "Range: %d", cic_rec->pcic,
                                     rs_ie.param_data.rangeAndStatus.range);

                    /* Maintenance system ind */
                    ISUP_CRITICAL(("CGBA compare CGB failed pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                }
                else
                {
                    /* Send to app */
                    SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

                    ISUP_Alarm_CCITT(3437, __FILE__, __LINE__, "pCIC : %x, Range: %d", 
                                     cic_rec->pcic, rs_ie.param_data.rangeAndStatus.range);
                }
                
                cic_rec->mgbs_state = MGBS_IDLE;
                /* Change state to IDLE */
            }
        }
        else if (sup_msg_type == HARD_FAILURE_ORIENTED)
        {
            if (cic_rec->hgbs_state == HGBS_IDLE)
            {
                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                bool_ret = __ISUP_ProcessAffectedCics(affected_cics, 
                                                      num_affected_cics,
                                                      __ISUP_HGBSCheckLocallyBlocked,
                                                      cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    ISUP_Alarm_CCITT(3436, __FILE__, __LINE__, "pCIC : %x, Range: %d", 
                                     cic_rec->pcic, rs_ie.param_data.rangeAndStatus.range);

                    /* Maintenance system ind */
                    ISUP_CRITICAL(("Received invalid CGBA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS,
                                     PEG_ISUP_CIC_UNEXP_CGBA_ABNORMAL_ACK);
                }
                else
                {
                    ISUP_DEBUG(("Received valid CGBA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                }

                /* No change in HGBS state */
            }
            else if (cic_rec->hgbs_state == HGBS_WAIT_FOR_CGBA)
            {
                /* Stop timers T18, T19 */
                __ISUP_StopCGBTimers(cic_rec, config_info);

                bool_ret = __ISUP_CompareCGBAWithCGB(msg, cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    ISUP_Alarm_CCITT(3436, __FILE__, __LINE__, "pCIC : %x,"
                     "Range: %d", cic_rec->pcic, rs_ie.param_data.rangeAndStatus.range);

                    /* Maintenance system ind */
                    ISUP_CRITICAL(("CGBA compare CGB failed pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                }
                else
                {
                    /* Send to app */
                    SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

                    ISUP_Alarm_CCITT(3437, __FILE__, __LINE__, "pCIC : %x, "
                     "Range: %d", cic_rec->pcic, rs_ie.param_data.rangeAndStatus.range);
                }
                
                cic_rec->hgbs_state = HGBS_IDLE;
                /* Change state to IDLE */
            }
        }
        else
        {
            /* error, discard */
        }
    }
    else 
    {
        ISUP_DEBUG(("Received CGBA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (sup_msg_type == MAINTENANCE_ORIENTED)
        {
            if (cic_rec->mgbr_state == MGBR_WAIT_FOR_BLO_RESP)
            {
                /* Send to L3 */
                SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                __ISUP_ProcessAffectedCics(affected_cics, 
                                           num_affected_cics,
                                           __ISUP_BlockingMGBRToBLR,
                                           cic_rec, config_info);

                ISUP_Alarm_CCITT(3434, __FILE__, __LINE__, "CIC : %d, "
                  "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);

                cic_rec->mgbr_state = MGBR_IDLE;
            }
        }
        else if (sup_msg_type == HARD_FAILURE_ORIENTED)
        {
            if (cic_rec->hgbr_state == HGBR_WAIT_FOR_BLO_RESP)
            {
                /* Send to L3 */
                SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                __ISUP_ProcessAffectedCics(affected_cics, 
                                           num_affected_cics,
                                           __ISUP_BlockingHGBRToHRB,
                                           cic_rec, config_info);

                ISUP_Alarm_CCITT(3434, __FILE__, __LINE__, "CIC : %d, "
                  "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);

                cic_rec->hgbr_state = HGBR_IDLE;
            }
        }
        else
        {
            /* error, discard */
        }

        /* Change state to IDLE */
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGU received in any state is done here.
 *      The message is forwarded to the application if received from the 
 *      network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the message event
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *      src - source of event (L3 or application)
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
void
__ISUP_CSC_Received_CGU(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("CGU RangeStatus check failed (%d), pcic 0x%08x, vcic %d.\n",
                 ret, cic_rec->pcic, cic_rec->vcic));

        if (src != ISUP_SRC_L3_ITU)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_CCITT(ISUP_MSG_CGU,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);
        }
        else
        {
            ISUP_Alarm_CCITT(3438, __FILE__, __LINE__, "CIC : %d, Range: %d", 
                                    cic, rs_ie.param_data.rangeAndStatus.range);
        }
        return;
    }

    /* Forward CGU appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received CGU from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (sup_msg_type == MAINTENANCE_ORIENTED)
        {
            if (cic_rec->mgbr_state == MGBR_IDLE)
            {
                /* Send to app */
                SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

                cic_rec->mgbr_state = MGBR_WAIT_FOR_UBL_RESP;
            }
        }
        else if (sup_msg_type == HARD_FAILURE_ORIENTED)
        {
            if (cic_rec->hgbr_state == HGBR_IDLE)
            {
                /* Send to app */
                SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

                cic_rec->hgbr_state = HGBR_WAIT_FOR_UBL_RESP;
            }
        }
        else
        {
            /* error, discard */
        }

        /* Change state to IDLE */
    }
    else 
    {
        ISUP_DEBUG(("Received CGU from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        
        if (sup_msg_type == MAINTENANCE_ORIENTED)
        {
            if (cic_rec->mgbs_state == MGBS_IDLE)
            {
                /* store the message in cic rec */
                cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, isdsmlocal);
                memcpy(cic_msg->cgu_msg, msg->data, msg->len);
                cic_msg->cgu_msg_len = msg->len;
                ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, isdsmlocal);

                /* Send to L3 */
                SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
        
                __ISUP_StartCGUTimers(cic_rec, config_info);

                cic_rec->mgbs_state = MGBS_WAIT_FOR_CGUA;
            }
        }
        else if (sup_msg_type == HARD_FAILURE_ORIENTED)
        {
            if (cic_rec->hgbs_state == HGBS_IDLE)
            {
                /* store the message in cic rec */
                cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, isdsmlocal);
                memcpy(cic_msg->cgu_msg, msg->data, msg->len);
                cic_msg->cgu_msg_len = msg->len;
                ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, isdsmlocal);

                /* Send to L3 */
                SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
        
                __ISUP_StartCGUTimers(cic_rec, config_info);

                cic_rec->hgbs_state = HGBS_WAIT_FOR_CGUA;
            }
        }
        else
        {
            /* error, discard */
        } 

        /* Change state to IDLE */
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGUA received in any state is done here.
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
void
__ISUP_CSC_Received_CGUA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_USHORT affected_cics[256];
    ITS_USHORT num_affected_cics;
    ITS_BOOLEAN bool_ret;
    ITS_ISUP_IE rs_ie;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("CGUA RangeStatus check failed (%d), pcic 0x%08x, vcic %d.\n",
                 ret, cic_rec->pcic, cic_rec->vcic));

        if (src != ISUP_SRC_L3_ITU)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_CCITT(ISUP_MSG_CGUA,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);
        }
        else
        { 
            ISUP_Alarm_CCITT(3439, __FILE__, __LINE__, "CIC : %d, Range: %d", 
                                      cic, rs_ie.param_data.rangeAndStatus.range);
        } 
        return;
    }

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received CGUA from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (sup_msg_type == MAINTENANCE_ORIENTED)
        {
            if (cic_rec->mgbs_state == MGBS_IDLE)
            {
                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                bool_ret = __ISUP_ProcessAffectedCics(affected_cics, 
                                                      num_affected_cics,
                                                      __ISUP_MGBSCheckNotLocallyBlocked,
                                                      cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("Received invalid CGUA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));

                    ISUP_Alarm_CCITT(3440, __FILE__, __LINE__, "CIC : %d, "
                      "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);
                    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS,
                                PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK);
                }
                else
                {
                    ISUP_DEBUG(("Received valid CGUA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                }
            }
            else if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGUA)
            {
                /* Stop timers T20, T21 */
                __ISUP_StopCGUTimers(cic_rec, config_info);

                bool_ret = __ISUP_CompareCGUAWithCGU(msg, cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("CGUA compare CGU failed pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));

                    ISUP_Alarm_CCITT(3440, __FILE__, __LINE__, "CIC : %d, "
                      "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);
                }
                else
                {
                    __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                           &num_affected_cics);

                    __ISUP_ProcessAffectedCics(affected_cics, 
                                               num_affected_cics,
                                               __ISUP_UnblockingMGBSToBLS,
                                               cic_rec, config_info);

                    /* Send to app */
                    SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

                    ISUP_Alarm_CCITT(3441, __FILE__, __LINE__, "CIC : %d, "
                      "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);
                }

                cic_rec->mgbs_state = MGBS_IDLE;
            }
        }
        else if (sup_msg_type == HARD_FAILURE_ORIENTED)
        {
            if (cic_rec->hgbs_state == HGBS_IDLE)
            {
                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                bool_ret = __ISUP_ProcessAffectedCics(affected_cics, 
                                                      num_affected_cics,
                                                      __ISUP_HGBSCheckNotLocallyBlocked,
                                                      cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    ISUP_Alarm_CCITT(3440, __FILE__, __LINE__, "CIC : %d, "
                      "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);

                    /* Maintenance system ind */
                    ISUP_CRITICAL(("Received invalid CGUA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS,
                                PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK);
                }
                else
                {
                    ISUP_DEBUG(("Received valid CGUA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                }
            }
            else if (cic_rec->hgbs_state == HGBS_WAIT_FOR_CGUA)
            {
                /* Stop timers T20, T21 */
                __ISUP_StopCGUTimers(cic_rec, config_info);

                bool_ret = __ISUP_CompareCGUAWithCGU(msg, cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("CGUA compare CGU failed pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));

                    ISUP_Alarm_CCITT(3440, __FILE__, __LINE__, "CIC : %d, "
                      "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);
                }
                else
                {
                    /* Send to app */
                    SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

                    __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                           &num_affected_cics);

                    __ISUP_ProcessAffectedCics(affected_cics, 
                                               num_affected_cics,
                                               __ISUP_UnblockingHGBSToHLB,
                                               cic_rec, config_info);

                    ISUP_Alarm_CCITT(3441, __FILE__, __LINE__, "CIC : %d, "
                      "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);
                }

                cic_rec->hgbs_state = HGBS_IDLE;
            }
        }
        else
        {
            /* error, discard */
        }
    }
    else 
    {
        ISUP_DEBUG(("Received CGUA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        
        if (sup_msg_type == MAINTENANCE_ORIENTED)
        {
            if (cic_rec->mgbr_state == MGBR_WAIT_FOR_UBL_RESP)
            {
                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                __ISUP_ProcessAffectedCics(affected_cics, 
                                           num_affected_cics,
                                           __ISUP_UnblockingMGBRToBLR,
                                           cic_rec, config_info);

                /* Send to L3 */
                SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

                ISUP_Alarm_CCITT(3442, __FILE__, __LINE__, "CIC : %d, "
                  "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);

                cic_rec->mgbr_state = MGBR_IDLE;
            }
        }
        else if (sup_msg_type == HARD_FAILURE_ORIENTED)
        {
            if (cic_rec->hgbr_state == HGBR_WAIT_FOR_UBL_RESP)
            {
                __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                       &num_affected_cics);

                __ISUP_ProcessAffectedCics(affected_cics, 
                                           num_affected_cics,
                                           __ISUP_UnblockingHGBRToHRB,
                                           cic_rec, config_info);

                /* Send to L3 */
                SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

                ISUP_Alarm_CCITT(3442, __FILE__, __LINE__, "CIC : %d, "
                  "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);

                cic_rec->hgbr_state = HGBR_IDLE;
            }
        }
        else
        {
            /* error, discard */
        }

        /* Change state to IDLE */
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an GRA received in any state is done here.
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
void
__ISUP_CSC_Received_GRA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_USHORT set_cics[256];
    ITS_USHORT num_set_cics;
    ITS_USHORT unset_cics[256];
    ITS_USHORT num_unset_cics;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;
    ITS_BOOLEAN bool_ret;

    /* Forward GRA appropriately */

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("GRA RangeStatus check failed (%d), pcic 0x%08x, vcic %d.\n",
                 ret, cic_rec->pcic, cic_rec->vcic));

        if (src != ISUP_SRC_L3_ITU)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_CCITT(ISUP_MSG_GRA,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);
        }
        else
        {
            ISUP_Alarm_CCITT(3443, __FILE__, __LINE__, "CIC : %d, Range: %d", 
                                     cic, rs_ie.param_data.rangeAndStatus.range);
        }
        return;
    }

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received GRA from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cgrs_state == CGRS_WAIT_FOR_GRA)
        {
            bool_ret = __ISUP_CompareGRAWithGRS(msg, cic_rec, config_info);
            if (bool_ret == ITS_FALSE)
            {
                /* Maintenance system ind */
                ISUP_CRITICAL(("GRA compare GRS failed pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic));

                ISUP_Alarm_CCITT(3444, __FILE__, __LINE__, "CIC : %d, "
                  "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);
                return;
            }

            __ISUP_GetGRACics(cic, &rs_ie, set_cics, &num_set_cics,
                              unset_cics, &num_unset_cics);

            __ISUP_ProcessAffectedCics(set_cics, 
                                       num_set_cics,
                                       __ISUP_IdleCircuit,
                                       cic_rec, config_info);

            __ISUP_ProcessAffectedCics(unset_cics, 
                                       num_unset_cics,
                                       __ISUP_IdleCircuit,
                                       cic_rec, config_info);

            __ISUP_ProcessAffectedCics(set_cics, 
                                       num_set_cics,
                                       __ISUP_BlockingCGRSToBLR,
                                       cic_rec, config_info);

            __ISUP_ProcessAffectedCics(unset_cics, 
                                       num_unset_cics,
                                       __ISUP_UnblockingCGRSToBLR,
                                       cic_rec, config_info);

            /* Stop timers T22, T23 */
            __ISUP_StopGRSTimers(cic_rec, config_info);

            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

            ISUP_Alarm_CCITT(3445, __FILE__, __LINE__, "CIC : %d, "
              "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);

            cic_rec->cgrs_state = CGRS_IDLE;
        }
    }
    else 
    {
        ISUP_DEBUG(("Received GRA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cgrr_state == CGRR_WAIT_FOR_GROUP_RESET_COMPLETE)
        {
            __ISUP_ResetCompleteCPCToCGRR(msg, cic_rec, config_info);

            /* Send to L3 */
            SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

            ISUP_Alarm_CCITT(3446, __FILE__, __LINE__, "CIC : %d, "
              "Range: %d", cic, rs_ie.param_data.rangeAndStatus.range);

            /* Change cgrr state to IDLE */
            cic_rec->cgrr_state = CGRR_IDLE;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an GRS received in any state is done here.
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
void
__ISUP_CSC_Received_GRS(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;
    ITS_USHORT affected_cics[256];
    ITS_USHORT num_affected_cics;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("GRS RangeStatus check failed (%d), pcic 0x%08x, "
                     "vcic %d.\n", ret, cic_rec->pcic, cic_rec->vcic));
    
        if (src != ISUP_SRC_L3_ITU)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_CCITT(ISUP_MSG_GRS,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);
        }
        else
        {
            ISUP_Alarm_CCITT(3447, __FILE__, __LINE__, "CIC : %d, Range: %d", 
                                     cic, rs_ie.param_data.rangeAndStatus.range);
        }

        return;
    }

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received GRS from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cgrr_state == CGRR_IDLE)
        {
            /* FIXED: code according to H.38/Q.764 */
            
            __ISUP_ResetCGRRToMGBR(cic_rec, config_info);
            
            __ISUP_ResetCGRRToHGBR(cic_rec, config_info);

            __ISUP_GetGRSCics(cic, &rs_ie, affected_cics, &num_affected_cics);

            __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                       __ISUP_ResetCGRRCommon1,
                                       cic_rec, config_info);

            /* FIXME: Handle multi-connection type */

            __ISUP_BlockingCGRRToHGBS(affected_cics, num_affected_cics, 
                                      cic_rec, config_info);

            cic_rec->cgrr_state = CGRR_WAIT_FOR_GROUP_RESET_COMPLETE;

            /* Send to Application */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
        }
    }
    else 
    {
        ISUP_DEBUG(("Received GRS from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cgrs_state == CGRS_IDLE)
        {
            /* store the message in cic rec */
            cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, isdsmlocal);
            memcpy(cic_msg->grs_msg, msg->data, msg->len);
            cic_msg->grs_msg_len = msg->len;
            ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, isdsmlocal);

            __ISUP_ResetCGRSToMGBS(cic_rec, config_info);

            __ISUP_ResetCGRSToHGBS(cic_rec, config_info);

            __ISUP_GetGRSCics(cic, &rs_ie, affected_cics, &num_affected_cics);

            __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                       __ISUP_ResetCGRSCommon2,
                                       cic_rec, config_info);

            /* Send to L3 */
            SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

            /* Start timers T23, T22 */
            __ISUP_StartGRSTimers(cic_rec, config_info);

            cic_rec->cgrs_state = CGRS_WAIT_FOR_GRA;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an RSC received in any state is done here.
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
void
__ISUP_CSC_Received_RSC(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    ITS_BOOLEAN change_state = ITS_TRUE;

    /* Forward RSC appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received RSC from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->crr_state == CRR_IDLE)
        {
            change_state = __ISUP_ResetCRRToCPC(cic_rec, config_info);

            if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LBLOCKED) ||
                    (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LRBLOCKED))
            {
                __ISUP_BlockingCRRToBLS(cic_rec, config_info);
            }
            if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_RBLOCKED) ||
                    (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LRBLOCKED))
            {
                __ISUP_UnblockingCRRToBLR(cic_rec, config_info);
            }
            if ((ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LBLOCKED) ||
                    (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LRBLOCKED))
            {
                __ISUP_BlockingCRRToHGBS(cic_rec, config_info);
            }
            if ((ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_RBLOCKED) ||
                    (ISUP_CIC_GET_HDW(cic_rec->cic_state) == CKTS_LRBLOCKED))
            {
                __ISUP_UnblockingCRRToHRB(cic_rec, config_info);
            }

            if (change_state)
            {
                cic_rec->crr_state = CRR_WAIT_FOR_RESPONSE;
            }
            /* No need to send RSC to app */
            /* FIXME - But the SDL Fig H.21/Q.764 (Sheet 4 of 21)
             * says that Stack needs to send the RSC to
             * the Application
             */
        }
        else if (cic_rec->crs_state == CRS_WAIT_FOR_RELEASE)
        {
            /* send RLC to SPRC */
            SPRC_SendRLCToMTP3_CCITT(CI_CAUSE_NORMAL, cic_rec, config_info);

            /* Stop Timer T16 and T17 */
            __ISUP_StopRSCTimers(cic_rec, config_info);

            /* Stop Repeat RSC timer also */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T98);

            /* FIXME:
             * Check for Alert Indicator On/Off
             * If ON;alert maintenance, otherwise do not
             */

            /* Indication to App */
            SPRC_SendIndToApp_CCITT(ITS_ISUP_RSC_CPCIDLE_STIND, cic_rec);

            /* Idle circuit and change fsm state to IDLE*/
            ISUP_ClearCic(cic_rec);

            /* crs state to Idle */
            cic_rec->crs_state = CRS_IDLE;
        }

        __ISUP_StopCRRToCRO(cic_rec, config_info);
        __ISUP_StopCRRToCRI(cic_rec, config_info);
    }
    else 
    {
        ISUP_DEBUG(("Received RSC from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->crs_state == CRS_IDLE)
        {
            cic_rec->reset_flag = RESET_FROM_CC;

            __ISUP_ResetCRSToCPC(cic_rec, config_info);

            __ISUP_ResetCRSCommon2(cic_rec, config_info);

            /* Change state to WAIT_INCOMING_RLC */
            cic_rec->fsm_state = IDLE;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an UBA received in any state is done here.
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
void
__ISUP_CSC_Received_UBA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward UBA appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received UBA from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->bls_state == BLS_LBLOCKED)
        {
            /* Alert maintenance system */
            ISUP_CRITICAL(("Got unexpected UBA, pcic 0x%08x, vcic %d.\n",
                 cic_rec->pcic, cic_rec->vcic)); 
            
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS,
                        PEG_ISUP_CIC_UNEXP_UBA_ABNORMAL_ACK);

            /* Discard message */            
        }
        else if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
        {
            /* We are in WaitForUBA state */
            /* This is a response to a UBL sent earlier */

            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

            /* Stop timers T15, T14 */
            __ISUP_StopUBLTimers(cic_rec, config_info);

            /* Mark CIC state accordingly: Locally Un-Blocked */
            cic_rec->cic_state &= 0xFEU;

            ISUP_Alarm_CCITT(3448, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

            cic_rec->bls_state = BLS_IDLE;
        }

        /* Change state to IDLE */
    }
    else 
    {
        ISUP_DEBUG(("Received UBA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        
        if (cic_rec->blr_state == BLR_WAIT_FOR_UBL_RESP)
        {
            /* Send to L3 */
            SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

            /* Mark CIC state accordingly: Remotely Un-blocked */
            cic_rec->cic_state &= 0xFDU;

            cic_rec->blr_state = BLR_IDLE;

            ISUP_Alarm_CCITT(3449, __FILE__, __LINE__, "pCIC : %x", cic_rec->pcic);

            /* Change state to IDLE */
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an UBL received in any state is done here.
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
void
__ISUP_CSC_Received_UBL(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward UBL appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received UBL from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->blr_state == BLR_IDLE)
        {
            /* Automatically send UBA to remote */
            SPRC_SendUBAToMTP3_CCITT(cic_rec, config_info);
        }
        else if (cic_rec->blr_state == BLR_WAIT_FOR_BLO_RESP)
        {
            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

            cic_rec->blr_state = BLR_WAIT_FOR_UBL_RESP;
        }
        else if (cic_rec->blr_state == BLR_RBLOCKED)
        {
            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);

            cic_rec->blr_state = BLR_WAIT_FOR_UBL_RESP;
        }

        /* Change state to IDLE, i.e. no change. */
    }
    else 
    {
        ISUP_DEBUG(("Received UBL from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Process according to BLS state */
        if (cic_rec->bls_state == BLS_LBLOCKED)
        {
            /* Send to L3 */
            SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

            __ISUP_StartUBLTimers(cic_rec, config_info);

            cic_rec->bls_state = BLS_WAIT_FOR_UBA;
        }

        /* Change state to IDLE, i.e. no change. */
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an CCR received in any state is done here.
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
void
__ISUP_CSC_Received_CCR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received CCR from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            /*stop T27 timer*/
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);

            /* Start timer T36 */
            /* Start timer T34 */
            if (__ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T36,
               config_info->\
               tmr_hndl_info[ITS_ISUP_TIMER_T36].tmr_value) != ITS_SUCCESS)
            {
                ISUP_ERROR(("CSC: Failed to start T36."
                "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }

            /* Change CRI state to wait for REL */
            cic_rec->cri_state = CRI_WAIT_FOR_REL;
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
        }
        else if (cic_rec->fsm_state == IDLE)
        {
            if (cic_rec->cot_first_ind == ITS_FALSE)
            {
                /*stop T27 timer*/
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
            }

            /* Start timer T36 */
            if (__ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T36,
               config_info->\
               tmr_hndl_info[ITS_ISUP_TIMER_T36].tmr_value) != ITS_SUCCESS)
            {
                ISUP_ERROR(("WAIT_CONTINUITY_REPORT: Failed to start T36."
                "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }

            /* Change CRI state to wait for REL */
            cic_rec->cri_state = CRI_WAIT_FOR_REL;

            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
        }
        else
        {
            ISUP_ERROR(("Received Unexpected CCR message\n"));
        }
    }
    else
    {
        ISUP_DEBUG(("Received CCR in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        if (cic_rec->fsm_state == IDLE)
        {
            cic_rec->cro_state = CRO_WAIT_FOR_COT;
            __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T24,
                              config_info->\
                              tmr_hndl_info[ITS_ISUP_TIMER_T24].tmr_value);

            /* Send to L3 */
            SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
        }
        else if (cic_rec->fsm_state == WAIT_CONTINUITY_REPORT) 
        {
            cic_rec->cro_state = CRO_WAIT_TIMER_EXPIRY;
            __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T25,
                             config_info->\
                             tmr_hndl_info[ITS_ISUP_TIMER_T25].tmr_value);
            /* FIXME - Hold the CCR message in the cic_rec, and
             * on timer expiry T25, Send the CCR message to the L3
             */
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an LPA received in any state is done here.
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
 *  Ramesh K V  04-05-2005   BCGI Problem   Added log for LPA recieve.
 *                           # 485
 ****************************************************************************/
void
__ISUP_CSC_Received_LPA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received LPA from L3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Check if the msg is national or international significant */
        if ((cic_rec->pcic.hdr.sio & MTP3_NIC_MASK) == MTP3_NIC_NATIONAL)
        {
            /* Send to app */
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
        }
        else if ((cic_rec->pcic.hdr.sio & MTP3_NIC_MASK) ==
                                      MTP3_NIC_INTERNATIONAL)
        {
            /* International Network, don't do anything */
        }
    }
    else
    {
        ISUP_DEBUG(("Received LPA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* This is response to the National CCR msg received from the 
         * network, forward it 
         */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an CQM received in any state is done here.
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
void
__ISUP_CSC_Received_CQM(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("CQM RangeStatus check failed (%d), pcic 0x%08x, vcic %d.\n",
                 ret, cic_rec->pcic, cic_rec->vcic));

        if (src != ISUP_SRC_L3_ITU)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_CCITT(ISUP_MSG_CQM,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);
        }
        else
        {
            ISUP_Alarm_CCITT(3476, __FILE__, __LINE__, "CIC : %d, Range: %d", 
                                 cic, rs_ie.param_data.rangeAndStatus.range);
        }
        return;
    }

    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received CQM from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        SPRC_SendCQRToMTP3_CCITT(cic_rec, config_info, &rs_ie);
    }
    else
    {
        ISUP_DEBUG(("Received CQM from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Start Timer T28 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T28,
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T28].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("IDLE CQM: Failed to start T28. pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));
        }

        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an CQR received in any state is done here.
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
void
__ISUP_CSC_Received_CQR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("CQR RangeStatus check failed (%d), pcic 0x%08x, vcic %d.\n",
                 ret, cic_rec->pcic, cic_rec->vcic));
   
        if (src != ISUP_SRC_L3_ITU)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_CCITT(ISUP_MSG_CQR,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);
        }
        else
        {
            ISUP_Alarm_CCITT(3477, __FILE__, __LINE__, "CIC : %d, Range: %d", 
                                 cic, rs_ie.param_data.rangeAndStatus.range);
        }
        return;
    }

    /* Forward CQR appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received CQR from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Stop timer T28 */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T28);

        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
    }
    else
    {
        ISUP_DEBUG(("Received CQR from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an UCIC received in any state is done here.
 *      The message is forwarded to the application if received from the
 *      network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the message event
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *      src - source of event (L3 or application)
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
void
__ISUP_CSC_Received_UCIC(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ITU)
    {
        /* received from the remote end because the
         * remote end is unable to perform a cic translation
         * on the message sent by us.
         */

        ISUP_DEBUG(("Received UCIC from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Query circuit status */

        switch(cic_rec->cic_state & 0x0cU) /* check bits DC */
        {
            case 0x00: /* DC is 00 */
                /* Now check for BA */
                switch(cic_rec->cic_state & 0x03)
                {
                    case 0x00:
                        /* Maintenance blocking state: TRANSIENT */
                        /* Stop UCIC to CRS */
                        __ISUP_StopUCICToCRS(cic_rec, config_info);

                        /* Stop UCIC to CGRS */
                        __ISUP_StopUCICToCGRS(cic_rec, config_info);

                        break;
                }
                break;
            default:
                break;
        }
        switch(cic_rec->cic_state & 0x0cU) /* Bits DC */
        {
            case 0x04:
                /* Incoming Busy */
                switch(cic_rec->cic_state & 0x03U)
                {
                    case 0x00:
                    case 0x01:
                    case 0x02:
                    case 0x03:
                        /* Stop UCIC to CRO */
                        __ISUP_StopUCICToCRO(cic_rec, config_info);

                        break;
                    default:
                        break;
                }
                break;
            case 0x08:
                /* Outgoing Busy */
                switch(cic_rec->cic_state & 0x03U)
                {
                    case 0x00:
                    case 0x01:
                    case 0x02:
                    case 0x03:
                        /* Reset UCIC to CPC */
                        __ISUP_ResetUCICToCPC(cic_rec, config_info);

                        /* Stop UCIC to CRO */
                        __ISUP_StopUCICToCRO(cic_rec, config_info);

                        break;
                    default:
                        break;
                }
                break;
            case 0x0c:
                /* Idle */
                switch(cic_rec->cic_state & 0x03U)
                {
                    case 0x00:
                    case 0x01:
                    case 0x02:
                    case 0x03:
                    default:
                        break;
                }
                break;
            default:
                ISUP_ERROR(("__ISUP_CSC_Received_UCIC(): Invalid Ckt state "
                            "pcic 0x%08x, vcic 0x%x.\n",
                            cic_rec->pcic, cic_rec->vcic));
                return;
        }
        if (ISUP_CIC_GET_MAINT(cic_rec->cic_state == CKTS_RBLOCKED))
        {
            /* Remove Remote Blocking */
            cic_rec->cic_state &= 0xFDU;
            cic_rec->blr_state = BLR_IDLE;
        }
        if ((ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LBLOCKED))
        {
            /* Stop UCIC to BLS */
            __ISUP_StopUCICToBLS(cic_rec, config_info);

            /* Stop UCIC to GBUS */
            __ISUP_StopUCICToGBUS(cic_rec, config_info);
        }
        else
        {
            /* Local Blocking UCIC to SPRC */
            /* Remove ckt form service */

            ISUP_CIC_SET_MAINT(cic_rec->cic_state, CKTS_LBLOCKED);
            cic_rec->bls_state = BLS_IDLE;
        }

        /* Alert Maintenance Personnel */
        SPRC_SendIndToApp_CCITT(ITS_ISUP_UCIC_LBLOCK_STIND, cic_rec);

        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
    }
    else
    {
        ISUP_DEBUG(("Received UCIC from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);

        /* No change of state */
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing of CRS from
 *      CPC, CRI and CRO
 *  Input Parameters:
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
void
__ISUP_CSC_StartCRS(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{

    switch(cic_rec->crs_state)
    {
        case CRS_IDLE:

            /* Mark circuit Transient */
            ISUP_CIC_SET_TRANSIENT(cic_rec->cic_state);

            /* Send RSC to SPRC */
            SPRC_SendRSCToMTP3_CCITT(cic_rec, config_info);

            /* Start T16, T17 */
            __ISUP_StartRSCTimers(cic_rec, config_info);

            /* Set the crs state to Wait for RLC */
            cic_rec->crs_state = CRS_WAIT_FOR_RELEASE;

            break;

        case CRS_WAIT_FOR_RELEASE:

            break;

        default:
            break;

    }

    return;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T12 timer  
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
void
__ISUP_CSC_Received_TimeoutT12(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT12 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T12);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT12: Unable to remove T12 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T12].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Resend BLO to L3 */
            SPRC_SendBLOToMTP3_CCITT(cic_rec, config_info);

            /* Restart T12, update restartCounter */
            __ISUP_StartBLORepeatTimer(cic_rec, config_info);
        }
        else
        {
            /* App will send BLO */
        }

        ISUP_Alarm_CCITT(3450, __FILE__, __LINE__, NULL);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T13 timer  
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
void
__ISUP_CSC_Received_TimeoutT13(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT13 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_BLA_T13);

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T13);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT13: Unable to remove T13 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
    {
        if (cic_rec->cntT13 == 1)
        {
            /* Stop T12 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T12);
            cic_rec->cntT12 = 0;
            
            /* Maintenance system ind */
            ISUP_CRITICAL(("First T13 expiry, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic)); 
        }
        
        ISUP_Alarm_CCITT(3451, __FILE__, __LINE__, NULL);

        /* Send maint indic to app */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T13].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Check if maintenance has intervened; if yes, clear all & return */

            /* Send BLO to L3 */
            SPRC_SendBLOToMTP3_CCITT(cic_rec, config_info);

            /* Restart T13. */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T13, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T13].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("TimeoutT13: Failed to start T13. pcic 0x%08x, "
                            "vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }
            else
            {
                cic_rec->cntT13++;
            }
        }
        else
        {
            /* App will send BLO */
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T14 timer  
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
void
__ISUP_CSC_Received_TimeoutT14(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT14 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T14);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT14: Unable to remove T14 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
    {
        ISUP_Alarm_CCITT(3452, __FILE__, __LINE__, NULL);

        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T14].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Resend UBL to L3 */
            SPRC_SendUBLToMTP3_CCITT(cic_rec, config_info);

            /* Restart T14, update restartCounter */
            __ISUP_StartUBLRepeatTimer(cic_rec, config_info);
        }
        else
        {
            /* App will send UBL. */
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T15 timer  
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
void
__ISUP_CSC_Received_TimeoutT15(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT15 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    
    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_UBA_T15);

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T15);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT15: Unable to remove T15 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
    {
        if (cic_rec->cntT15 == 1)
        {
            /* Stop T14 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T14);
            cic_rec->cntT14 = 0;

            /* Maintenance system ind */
            ISUP_CRITICAL(("First T15 expiry, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic)); 
        }

        ISUP_Alarm_CCITT(3453, __FILE__, __LINE__, NULL);

        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T15].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Check if maintenance has intervened; if yes, clear all & return */

            /* Send UBL to L3 */
            SPRC_SendUBLToMTP3_CCITT(cic_rec, config_info);
        
            /* Restart T15. */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T15, 
                           config_info->tmr_hndl_info[ITS_ISUP_TIMER_T15].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("TimeoutT15: Failed to start T15. pcic 0x%08x, "
                            "vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }
            else
            {
                cic_rec->cntT15++;
            }
        }
        else
        {
            /* App will send UBL */
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T16 timer  
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
void
__ISUP_CSC_Received_TimeoutT16(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT16 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T16);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT16: Unable to remove T16 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (cic_rec->crs_state == CRS_WAIT_FOR_RELEASE)
    {
        ISUP_Alarm_CCITT(3454, __FILE__, __LINE__, NULL);

        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T16].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Check if maintenance has intervened; if yes, clear all & return */

            __ISUP_ResetCRSCommon1(cic_rec, config_info);

            SPRC_SendRSCToMTP3_CCITT(cic_rec, config_info);

            /* Restart T16, update restartCounter */
            __ISUP_StartRSCRepeatTimer(cic_rec, config_info);

            cic_rec->crs_state = CRS_WAIT_FOR_RELEASE;
        }
        else
        {
            /* App will send RSC */
            /* Change state to WAIT_OUTGOING_RSC */
            cic_rec->fsm_state = WAIT_OUTGOING_RSC;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T17 timer  
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
void
__ISUP_CSC_Received_TimeoutT17(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT17 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    
    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_ACK_RSC_T17);

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T17);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT17: Unable to remove T17 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (cic_rec->crs_state == CRS_WAIT_FOR_RELEASE)
    {
        if ((cic_rec->cntT17 == 1) && (cic_rec->reset_flag != RESET_AFTER_T5))
        {
            /* Stop T16 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T16);
            cic_rec->cntT16 = 0;
            
            /* Maintenance system ind */
            ISUP_CRITICAL(("First T17 expiry, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic)); 
        }

        ISUP_Alarm_CCITT(3455, __FILE__, __LINE__, NULL);

        /* Send maint indic to app */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T17].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Check if maintenance has intervened; if yes, clear all & return */

            __ISUP_ResetCRSCommon1(cic_rec, config_info);

            SPRC_SendRSCToMTP3_CCITT(cic_rec, config_info);
            
            /* Restart T17. */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T17, 
                  config_info->tmr_hndl_info[ITS_ISUP_TIMER_T17].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("TimeoutT17: Failed to start T17. pcic 0x%08x, "
                            "vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }
            else
            {
                cic_rec->cntT17++;
            }

            cic_rec->crs_state = CRS_WAIT_FOR_RELEASE;
        }
        else
        {
            /* App will send RSC */
            /* Change state to WAIT_OUTGOING_RSC */
            cic_rec->fsm_state = WAIT_OUTGOING_RSC;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T18 timer  
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
void
__ISUP_CSC_Received_TimeoutT18(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT18 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T18);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT18: Unable to remove T18 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if ((cic_rec->mgbs_state == MGBS_WAIT_FOR_CGBA) ||
            (cic_rec->hgbs_state == HGBS_WAIT_FOR_CGBA))
    {
        ISUP_Alarm_CCITT(3456, __FILE__, __LINE__, NULL);

        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T18].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Resend CGB to L3 */
            SPRC_ResendCGBToMTP3_CCITT(cic_rec, config_info);

            /* Restart T18, update restartCounter */
            __ISUP_StartCGBRepeatTimer(cic_rec, config_info);
        }
        else
        {
            /* App will send CGB */
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T19 timer  
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
void
__ISUP_CSC_Received_TimeoutT19(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT19 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_CGBA_T19);

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T19);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT19: Unable to remove T19 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if ((cic_rec->mgbs_state == MGBS_WAIT_FOR_CGBA) ||
            (cic_rec->hgbs_state == HGBS_WAIT_FOR_CGBA))
    {
        if (cic_rec->cntT19 == 1)
        {
            /* Stop T18 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T18);
            cic_rec->cntT18 = 0;
            
            /* Maintenance system ind */
            ISUP_CRITICAL(("First T19 expiry, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic)); 
        }
        
        ISUP_Alarm_CCITT(3457, __FILE__, __LINE__, NULL);

        /* Send maint indic to app */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T19].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Check if maintenance has intervened; if yes, clear all & return */

            /* Send CGB to L3 */
            SPRC_ResendCGBToMTP3_CCITT(cic_rec, config_info);

            /* Restart T19. */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T19, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T19].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("TimeoutT19: Failed to start T19. pcic 0x%08x, "
                            "vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }
            else
            {
                cic_rec->cntT19++;
            }
        }
        else
        {
            /* App will send CGB */
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T20 timer  
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
void
__ISUP_CSC_Received_TimeoutT20(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT20 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T20);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT20: Unable to remove T20 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if ((cic_rec->mgbs_state == MGBS_WAIT_FOR_CGUA) ||
            (cic_rec->hgbs_state == HGBS_WAIT_FOR_CGUA))
    {
        ISUP_Alarm_CCITT(3458, __FILE__, __LINE__, NULL);

        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T20].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Resend CGU to L3 */
            SPRC_ResendCGUToMTP3_CCITT(cic_rec, config_info);

            /* Restart T20, update restartCounter */
            __ISUP_StartCGURepeatTimer(cic_rec, config_info);
        }
        else
        {
            /* App will send CGU */
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T21 timer  
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
void
__ISUP_CSC_Received_TimeoutT21(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT21 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_CGUA_T21);

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T21);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT21: Unable to remove T21 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if ((cic_rec->mgbs_state == MGBS_WAIT_FOR_CGUA) ||
            (cic_rec->hgbs_state == HGBS_WAIT_FOR_CGUA))
    {
        if (cic_rec->cntT21 == 1)
        {
            /* Stop T20 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T20);
            cic_rec->cntT20 = 0;
            
            /* Maintenance system ind */
            ISUP_CRITICAL(("First T21 expiry, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic)); 
        }
        
        ISUP_Alarm_CCITT(3459, __FILE__, __LINE__, NULL);

        /* Send maint indic to app */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T21].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Check if maintenance has intervened; if yes, clear all & return */

            /* Send CGU to L3 */
            SPRC_ResendCGUToMTP3_CCITT(cic_rec, config_info);

            /* Restart T21. */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T21, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T21].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("TimeoutT21: Failed to start T21. pcic 0x%08x, "
                            "vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }
            else
            {
                cic_rec->cntT21++;
            }
        }
        else
        {
            /* App will send CGU */
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T22 timer  
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
void
__ISUP_CSC_Received_TimeoutT22(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;
    ITS_USHORT affected_cics[256];
    ITS_USHORT num_affected_cics;
    ITS_EVENT event;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    ISUP_DEBUG(("TimeoutT22 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
        
    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T22);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT22: Unable to remove T22 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }   

    if (cic_rec->cgrs_state == CGRS_WAIT_FOR_GRA)
    {
        ISUP_Alarm_CCITT(3460, __FILE__, __LINE__, NULL);

        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T22].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, isdsmlocal);

            ITS_EVENT_INIT(&event, ITS_ISUP_CCITT_SRC, cic_msg->grs_msg_len);
            memcpy((void *)(event.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

            ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, isdsmlocal);

            __ISUP_Validate_RangeStatus(&event, cic_rec, config_info,
                                        &rs_ie, &sup_msg_type, &cic);
        
            __ISUP_GetGRSCics(cic, &rs_ie, affected_cics, &num_affected_cics);

            __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                       __ISUP_ResetCGRSCommon1,
                                       cic_rec, config_info);
            ITS_EVENT_TERM((&event));

            /* Resend GRS to L3 */
            SPRC_ResendGRSToMTP3_CCITT(cic_rec, config_info);

            /* Restart T22, update restartCounter */
            __ISUP_StartGRSRepeatTimer(cic_rec, config_info);
        }
        else
        {
            /* App will send GRS */
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T23 timer  
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
void
__ISUP_CSC_Received_TimeoutT23(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_EVENT event;
    ITS_ISUP_IE rs_ie;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;
    ITS_USHORT affected_cics[256];
    ITS_USHORT num_affected_cics;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    ISUP_DEBUG(("TimeoutT23 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_GRA_T23);

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T23);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT23: Unable to remove T23 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }    

    if (cic_rec->cgrs_state == CGRS_WAIT_FOR_GRA)
    {
        if (cic_rec->cntT23 == 1)
        {
            /* Stop T22 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T22);
            cic_rec->cntT22 = 0;
            
            /* Maintenance system ind */
            ISUP_CRITICAL(("First T23 expiry, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic)); 
        }
        
        ISUP_Alarm_CCITT(3461, __FILE__, __LINE__, NULL);

        /* Send maint indic to app */
        SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
        
        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T23].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, isdsmlocal);

            ITS_EVENT_INIT(&event, ITS_ISUP_CCITT_SRC, cic_msg->grs_msg_len);
            memcpy((void *)(event.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

            ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, isdsmlocal);

            __ISUP_Validate_RangeStatus(&event, cic_rec, config_info,
                                        &rs_ie, &sup_msg_type, &cic);
        
            __ISUP_GetGRSCics(cic, &rs_ie, affected_cics, &num_affected_cics);

            __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                       __ISUP_ResetCGRSCommon1,
                                       cic_rec, config_info);
            ITS_EVENT_TERM((&event));
            /* Resend GRS to L3 */
            SPRC_ResendGRSToMTP3_CCITT(cic_rec, config_info);

            /* Restart T23. */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T23, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T23].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("TimeoutT23: Failed to start T23. pcic 0x%08x, "
                            "vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }
            else
            {
                cic_rec->cntT23++;
            }
        }
        else
        {
            /* App will send GRS */
        }
    }
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
void
__ISUP_CSC_Received_TimeoutT24(ISUP_TIMER_ENTRY* t_entry,
                               ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int tret =0;

    /*Send COT msg with failure indic */
    SPRC_SendCOTToMTP3_CCITT(CONTINUITY_CHECK_FAILED,cic_rec,config_info);

    /* FIXME - Raise an Alarm */ 

    if (cic_rec->cco_state == CCO_WAIT_COT_REPORT)
    {
        __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T7);
        cic_rec->cco_state = CCO_IDLE;

        tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T25,
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T25].tmr_value);
        if (tret != ITS_SUCCESS)
        {
            ISUP_ERROR(("IDLE WAIT_CONTINUITY_REPORT: Failed to start T25."
                        " pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));
        }
        
        /* FIXME - Send an indication to the APP for re-attempt
         * indication, and Send CCR message
         */
    }
    else if (cic_rec->cro_state == CRO_WAIT_FOR_COT)
    {
        tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T26,
                                  config_info->\
                                  tmr_hndl_info[ITS_ISUP_TIMER_T26].tmr_value);
        if (tret != ITS_SUCCESS)
        {
            ISUP_ERROR(("IDLE WAIT_CONTINUITY_REPORT: Failed to start T26."
                        " pcic 0x%08x, vcic %d.\n",
                          cic_rec->pcic, cic_rec->vcic));
        }
        else
        {
            ISUP_DEBUG(("Timer T26 Started, in IDLE state while waiting for CONTINUITY_REPORT"));
        }
    }
    cic_rec->cro_state = CRO_WAIT_TIMER_EXPIRY;
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
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
void
__ISUP_CSC_Received_TimeoutT25(ISUP_TIMER_ENTRY* t_entry,
                               ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int tret =0;

    /* FIXME - Raise an Alarm */
    if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY)
    {
        /*Send CCR msg start T24 timer */
        SPRC_SendCCRToMTP3_CCITT(cic_rec,config_info);

        tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T24,
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T24].tmr_value) ;
        if (tret != ITS_SUCCESS)
        {
            ISUP_ERROR(("WAIT COT REPORT Failed to start T24."
                        "pcic 0x%08x, vcic %d.\n",cic_rec->pcic,cic_rec->vcic));
        }

        cic_rec->cro_state = CRO_WAIT_FOR_COT;
        cic_rec->cot_first_ind = ITS_FALSE;
    }
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
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
void
__ISUP_CSC_Received_TimeoutT26(ISUP_TIMER_ENTRY* t_entry,
                               ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int tret =0;
    /* FIXME - Raise an Alarm */
    if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY)
    {
        /* Send CCR msg and start T24 timer */
        SPRC_SendCCRToMTP3_CCITT(cic_rec,config_info);

        tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T24,
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T24].tmr_value)
;

        if (tret != ITS_SUCCESS)
        {
            ISUP_ERROR(("WAIT COT REPORT Failed to start T24."
                        "pcic 0x%08x, vcic %d.\n",cic_rec->pcic,cic_rec->vcic));
        }

        cic_rec->cro_state = CRO_WAIT_FOR_COT;
    }
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
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
void
__ISUP_CSC_Received_TimeoutT27(ISUP_TIMER_ENTRY* t_entry,
                               ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    ISUP_DEBUG(("TimeoutT27 event received in . "
               "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* FIXME - Raise an Alarm */

    /*Reset the circuit */
    __ISUP_CSC_StartCRS(cic_rec,config_info);

    /*Change CRI state to IDLE */
    cic_rec->cri_state = CRI_IDLE;
    cic_rec->cot_first_ind = ITS_TRUE;
    /*
     * Send the timeout data to user app.
     * This will be done whether the procedure is automated or not.
     */
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
    SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_COT_RESET_RQIND, cic_rec);

    /* Change state to WAIT_INCOMING_RLC */
    cic_rec->fsm_state = WAIT_INCOMING_RLC;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T36 timer in the
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
void
__ISUP_CSC_Received_TimeoutT36(ISUP_TIMER_ENTRY* t_entry,
                               ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = 0;
    ISUP_DEBUG(("TimeoutT36 event received."
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* FIXME - Raise an Alarm */

   /* Remove info about timer from cic_rec; it wont be restarted. */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T36);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT36 in IDLE state: Unable to remove T36 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }


    /*Reset the circuit */
    __ISUP_CSC_StartCRS(cic_rec,config_info);

    /*Change CRI state to IDLE */
    cic_rec->cri_state = CRI_IDLE;
    cic_rec->cot_first_ind = ITS_TRUE;

    ISUP_Alarm_CCITT(3465, __FILE__, __LINE__, NULL);

    /*
     * Send the timeout data to user app.
     * This will be done whether the procedure is automated or not.
     */
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
    SPRC_SendIndToApp_CCITT(ITS_ISUP_CIC_COT_RESET_RQIND, cic_rec);

    /* Change state to WAIT_INCOMING_RLC */
    cic_rec->fsm_state = WAIT_INCOMING_RLC;
}
