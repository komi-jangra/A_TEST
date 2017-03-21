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
 *  ID: $Id: ansi-csc_ansi92.c,v 1.1.1.1 2007-10-08 11:12:17 bsccs2 Exp $
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
 * LOG: Revision 9.2  2005/04/08 06:21:34  ssingh
 * LOG: ISUP bug fix propagation (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.20  2005/03/21 13:53:55  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.18.2.2.6.1.12.4  2005/02/11 05:54:30  ssingh
 * LOG: Changes to fix bug#1447 [pegs for RSC(T17)/GRS(T23)
 * LOG: timer expiry and respective peg increament.
 * LOG: (Ramesh KV, Abhijit D)
 * LOG:
 * LOG: Revision 7.18.2.2.6.1.12.3  2005/02/03 12:44:40  ssingh
 * LOG: Bug #1448; unexpected Msg from Network and peg/stats handling.
 * LOG: (Ramesh KV, Abhijit D)
 * LOG:
 * LOG: Revision 7.18.2.2.6.1.12.2  2004/12/29 14:35:54  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.18.2.2.6.1.12.1  2004/12/06 13:34:49  mmanikandan
 * LOG: Windows Compilation Support
 * LOG:
 * LOG: Revision 7.18.2.2.6.1  2004/01/05 10:10:43  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.18.2.2.2.6  2003/12/11 15:04:32  ssingh
 * LOG: Alarms associated with RangeNStatus check failure for
 * LOG: CSC group messages received from Network are updated.
 * LOG:
 * LOG: Revision 7.18.2.2.2.5  2003/11/24 06:38:04  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.18.2.2.2.4  2003/11/13 13:19:26  akumar
 * LOG: Bug fix cycle for TCS-ISUP.
 * LOG:
 * LOG: Revision 7.18.2.2.2.3  2003/10/21 06:22:00  akumar
 * LOG: Grammer error resolved.
 * LOG:
 * LOG: Revision 7.18.2.2.2.2  2003/10/17 09:40:56  akumar
 * LOG: Fix Req no R480-17 for TCS.
 * LOG:
 * LOG: Revision 7.18.2.2.2.1  2003/09/13 06:27:00  akumar
 * LOG: Msg Based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 7.18.2.2  2003/05/07 10:37:59  ssingh
 * LOG: Latest Changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.15  2003/05/06 13:55:52  sswami
 * LOG: Alarm related changes :opc information included.
 * LOG:
 * LOG: Revision 8.14  2003/04/28 15:07:15  sjaddu
 * LOG: Removed EVEN TERM every thing is taken care.
 * LOG:
 * LOG: Revision 8.13  2003/04/24 14:13:25  sswami
 * LOG: Bug #317; Alarm Enhancement related changes done.
 * LOG:
 * LOG: Revision 8.12  2003/04/24 06:44:58  ssingh
 * LOG: Bug# 313; handling of CGB/CGU (range 0) received from Network modified.
 * LOG:
 * LOG: Revision 8.11  2003/04/17 08:45:36  akumar
 * LOG: Mem Leak Avoided.
 * LOG:
 * LOG: Revision 8.10  2003/04/16 06:42:11  akumar
 * LOG: ITS_EVENT_TERM added.
 * LOG:
 * LOG: Revision 8.9  2003/04/08 05:10:06  ssingh
 * LOG: received_RSC (from App) is changed; extra EVENT_INIT avoided.
 * LOG:
 * LOG: Revision 8.8  2003/04/04 12:01:20  ssingh
 * LOG: Handling of CGB/CGU is modified.
 * LOG:
 * LOG: Revision 8.7  2003/04/04 07:09:43  ssingh
 * LOG: ISUP_ReleaseCicMsgBuf related changes done.
 * LOG:
 * LOG: Revision 8.6  2003/04/04 05:19:10  ssingh
 * LOG: Modified/Enhanced CGBA/CGUA from Network handling.
 * LOG:
 * LOG: Revision 8.5  2003/04/03 15:24:34  sjaddu
 * LOG: ISUP DSM reorganization.
 * LOG:
 * LOG: Revision 8.4  2003/03/26 12:29:32  ssingh
 * LOG: Modified CIC_INFO changes incorporated. ISUPPending List Items done.
 * LOG:
 * LOG: Revision 8.3  2003/03/15 13:18:08  ssingh
 * LOG: Changes done in existing files to support CRM/CRA messaging.
 * LOG:
 * LOG: Revision 8.2  2003/03/14 09:37:11  ssingh
 * LOG: Changed done to prop fixes for BUG# 245,237,226 from PR6.3.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:27  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.18  2003/01/29 19:08:21  sjaddu
 * LOG: Added one more state for CRI.
 * LOG:
 * LOG: Revision 7.17  2003/01/29 13:23:26  ssingh
 * LOG: changed || with && in case of wrong blocking type.
 * LOG:
 * LOG: Revision 7.16  2003/01/27 15:38:01  ssingh
 * LOG: Added changes for cgb/cgu received from Network with
 * LOG: invalid Blocking type. Changes done for Comparing received CGBA
 * LOG: with CGB and received CGUA with CGU.
 * LOG:
 * LOG: Revision 7.15  2002/12/27 07:01:15  ssingh
 * LOG: UCIC(rcvd) with CGU/CGB/GRS(send) n GRS(rcvd) related changes.
 * LOG:
 * LOG: Revision 7.14  2002/12/11 14:23:04  ssingh
 * LOG: Changed code for INF/INR/CPG and T33 expiry handling.
 * LOG:
 * LOG: Revision 7.13  2002/12/06 12:00:47  ssingh
 * LOG: Updated Expiry of Timer T18/19 and T22/23 code.
 * LOG:
 * LOG: Revision 7.12  2002/12/02 10:41:05  sjaddu
 * LOG: COT Hanlding in IDLE.
 * LOG:
 * LOG: Revision 7.11  2002/11/21 11:20:06  sjaddu
 * LOG: Forward CCR to application in IDLE.
 * LOG:
 * LOG: Revision 7.10  2002/11/20 12:47:34  akumar
 * LOG: Worked on ALARMS indentation
 * LOG:
 * LOG: Revision 7.9  2002/11/19 05:21:55  ssingh
 * LOG: Outgoing CGB handling is been changed.
 * LOG:
 * LOG: Revision 7.8  2002/11/14 14:12:33  ssingh
 * LOG: Code changed as per the Functional testing in case of IAM handling.
 * LOG:
 * LOG: Revision 7.7  2002/11/12 05:31:56  akumar
 * LOG: Added ANSI ISUP Alarms
 * LOG:
 * LOG: Revision 7.6  2002/10/30 13:49:17  sjaddu
 * LOG: Set cot_first_time indicator to ITS_TRUE.
 * LOG:
 * LOG: Revision 7.5  2002/10/30 08:55:45  sjaddu
 * LOG: Added Continuity procedures.
 * LOG:
 * LOG: Revision 7.4  2002/10/25 13:43:57  ssingh
 * LOG: Code changes done as a part of BUG 141-to-146 fixing.
 * LOG:
 * LOG: Revision 7.3  2002/10/21 12:26:09  ssingh
 * LOG: Addec functions to support <-CQR- for ANSI.
 * LOG:
 * LOG: Revision 7.2  2002/10/11 09:24:56  sjaddu
 * LOG: Added PEGS for ANSI ISUP.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.30  2002/07/30 13:46:33  sjaddu
 * LOG: Added MTP indications and CFN procedures.
 * LOG:
 * LOG: Revision 1.1.2.29  2002/07/29 15:07:14  ssingh
 * LOG: Changes Done in UCIC handle procedure.
 * LOG:
 * LOG: Revision 1.1.2.28  2002/07/23 18:24:12  ssingh
 * LOG: Added/Changed Code to fix BUG noticed during testing.
 * LOG:
 * LOG: Revision 1.1.2.27  2002/07/19 19:12:25  ssingh
 * LOG: ANSI92 completed according to the SDLs.
 * LOG:
 * LOG: Revision 1.1.2.26  2002/07/18 22:40:28  ssingh
 * LOG: Added Code for handling BLS/BLR/RSC from remote/local.
 * LOG:
 * LOG: Revision 1.1.2.25  2002/07/18 19:02:20  ssingh
 * LOG: Changes for handling of CGB/CGU/CGBA/CGUA/GRS/GRA from local/remote.
 * LOG:
 * LOG: Revision 1.1.2.24  2002/07/18 15:55:53  hbalimid
 * LOG: BLS and BLR states done.
 * LOG:
 * LOG: Revision 1.1.2.23  2002/07/15 23:23:29  ssingh
 * LOG: Completed ANSI as per ITU SDLs.
 * LOG:
 * LOG: Revision 1.1.2.22  2002/07/15 21:26:58  hbalimid
 * LOG: Old Implementation restored.
 * LOG:
 * LOG: Revision 1.1.2.21  2002/07/14 19:01:41  hbalimid
 * LOG: Wait for OGC Completion in place.
 * LOG:
 * LOG: Revision 1.1.2.20  2002/07/13 17:41:37  hbalimid
 * LOG: Wait for Incoming ACM procedures completed.
 * LOG:
 * LOG: Revision 1.1.2.19  2002/07/13 02:29:13  hbalimid
 * LOG: Added Inter-state procedures.
 * LOG:
 * LOG: Revision 1.1.2.18  2002/07/12 22:45:58  hbalimid
 * LOG: UCIC bug fixed. Reset of states done.
 * LOG:
 * LOG: Revision 1.1.2.17  2002/07/12 21:50:08  hbalimid
 * LOG: StartCRS added for Unexpected Messages.
 * LOG:
 * LOG: Revision 1.1.2.16  2002/07/12 20:54:18  hbalimid
 * LOG: Removed CCITT specific hardware blocking
 * LOG:
 * LOG: Revision 1.1.2.15  2002/07/12 15:25:08  ssingh
 * LOG: Added/Changed CQM/CQR related methods.
 * LOG:
 * LOG: Revision 1.1.2.14  2002/07/12 14:05:26  hbalimid
 * LOG: CQM moved to CSC.
 * LOG:
 * LOG: Revision 1.1.2.13  2002/07/12 01:02:00  hbalimid
 * LOG: UCIC procedures added.
 * LOG:
 * LOG: Revision 1.1.2.12  2002/07/10 19:32:12  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 1.1.2.11  2002/07/10 18:41:38  hbalimid
 * LOG: CPC outgoing statemachine implemented.
 * LOG:
 * LOG: Revision 1.1.2.10  2002/07/10 14:08:15  ssingh
 * LOG: code chages related to CSC.
 * LOG:
 * LOG: Revision 1.1.2.9  2002/07/10 05:36:00  hbalimid
 * LOG: CPC Incoming States completed.
 * LOG:
 * LOG: Revision 1.1.2.8  2002/07/08 23:45:23  hbalimid
 * LOG: Test call implemented for Received IAM from L3.
 * LOG:
 * LOG: Revision 1.1.2.7  2002/07/08 14:08:44  ssingh
 * LOG: Code changes as per ANSI92 testing (BUG FIX)
 * LOG:
 * LOG: Revision 1.1.2.6  2002/07/07 14:06:23  hbalimid
 * LOG: Completed CRS state machine handling.
 * LOG:
 * LOG: Revision 1.1.2.5  2002/07/06 06:09:59  hbalimid
 * LOG: Tookcare of all warnings.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/07/05 23:29:36  ssingh
 * LOG: Bug Fix for BLO.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/05 13:57:21  ssingh
 * LOG: ansi 92 changes.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/02 23:19:34  ssingh
 * LOG: Added ANSI92 specific changes.
 * LOG: Timer handling and GRS/GRA implemented.
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

#include <ansi/isup.h>
#include <isup_intern.h>

#include <ansi/isup_92.h>

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
ITSSS7DLLAPI void
__ISUP_CSC_Received_BLA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received BLA from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->bls_state == BLS_IDLE)
        {
            /* Alert maintenance system */
            ISUP_CRITICAL(("Got unexpected BLA, pcic 0x%08x, vcic %d.\n",
                           cic_rec->pcic, cic_rec->vcic)); 

            ISUP_Alarm_ANSI(3020, __FILE__, __LINE__, "dpc: %d opc: %d "
                            "cic: %x Message: %x",
                            MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                            MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                            ISUP_PCIC_TO_CIC(cic_rec->pcic),
                            msg->data[sizeof(MTP3_HEADER_ANSI) + 
                            sizeof(ITS_USHORT) + sizeof(ITS_OCTET)]);

            if (!(ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state)))
            {
               /* Send UBL to Network */ 
               SPRC_SendUBLToMTP3_ANSI(cic_rec, config_info);

               /* Start T14, T15 */
               __ISUP_StartUBLTimers(cic_rec, config_info);

               /* Set the bls state to Wait for UBA */
               cic_rec->bls_state = BLS_WAIT_FOR_UBA;

               /* Send Indication to the App */
               SPRC_SendIndToApp_ANSI(ITS_ISUP_BLA_IND, cic_rec);

               PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, 
                                        PEG_ISUP_CIC_UNEXP_BLA_ABNORMAL_ACK);
            }
        }
        else if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
        {
            /* We are in WaitForBLA state */
            /* This is a response to a BLO sent earlier */
            /* Stop timers T13, T12. */
            __ISUP_StopBLOTimers(cic_rec, config_info);

            /* Send to app - this is a confirmation */
            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

            cic_rec->bls_state = BLS_IDLE;
        }
        else if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
        {
            /* Send UBL to L3 */
            SPRC_SendUBLToMTP3_ANSI(cic_rec, config_info);
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, 
                               PEG_ISUP_CIC_UNEXP_BLA_ABNORMAL_ACK);

            ISUP_Alarm_ANSI(3021, __FILE__, __LINE__, "cic : %x dpc:%d opc: %d",
                            ISUP_PCIC_TO_CIC(cic_rec->pcic),
                            MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                            MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));

            /* No change of state here */
        }
    }
    else 
    {
        ISUP_DEBUG(("Received Unexpected BLA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        ISUP_Alarm_ANSI(3022, __FILE__, __LINE__, "Message %x cic : %x",
                         msg->data[sizeof(MTP3_HEADER_ANSI) + 
                         sizeof(ITS_USHORT) + sizeof(ITS_OCTET)],
                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

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
 *  Notes:
 *      Procedures as per T1.113-4
 *
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_CSC_Received_BLO(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received BLO from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* BLR State Machine */
        if (cic_rec->blr_state == BLR_IDLE)
        {
            /* automatically send bla to remote */
            SPRC_SendBLAToMTP3_ANSI(cic_rec, config_info);

            /* Check whether remotely blocked */
            if (!ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
            {
                /* Mark CIC state accordingly: Remotely blocked */
                cic_rec->cic_state &= 0xFDU;
                cic_rec->cic_state |= CKTS_RBLOCKED;
 
                /* Blocking BLR to CPC */
                __ISUP_BlockingBLRToCPC(cic_rec, config_info);

                /* Send BLO Ind to app */
                SPRC_SendIndToApp_ANSI(ITS_ISUP_BLO_RBLOCK_IND, cic_rec);

                cic_rec->blr_state = BLR_IDLE;
            }
            /* Stop CRO BLR->CRO */
            __ISUP_StopBLRToCRO(cic_rec, config_info);

            /* Stop CRI BLR->CRI */
            __ISUP_StopBLRToCRI(cic_rec, config_info);


            /* No change of state */
        }
    }
    else 
    {
        ISUP_DEBUG(("Received BLO from APP, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        /* Process according to BLS state */
        if (cic_rec->bls_state == BLS_IDLE)
        {
            /* Manual blocking from App or */
            if ( !(ISUP_CIC_IS_IDLE(cic_rec->cic_state)) )
            {
                __ISUP_BlockingBLSToCPC(cic_rec,config_info);
            }

            /* Mark circuit Locally Blocked */
            cic_rec->cic_state &= 0xFEU;
            cic_rec->cic_state |= CKTS_LBLOCKED;

            /* Maintenance system ind */
            ISUP_CRITICAL(("Got Blocking Req, pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic)); 

            /* Send to L3 */
            SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

            __ISUP_StartBLOTimers(cic_rec, config_info);

            cic_rec->bls_state = BLS_WAIT_FOR_BLA;
        }
        else if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
        {
            /* Send to L3 */
            SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

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
ITSSS7DLLAPI void
__ISUP_CSC_Received_CGB(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_USHORT affected_cics[256];
    ITS_USHORT num_affected_cics;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;
    ISUP_RANGE_AND_STATUS cgba_rs;
    ITS_BOOLEAN bool_ret = ITS_FALSE;
    ITS_EVENT   event;
    ITS_BOOLEAN uneqCicPresent = ITS_FALSE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("CGB RangeStatus check failed (%d), pcic 0x%08x, vcic %d.\n",
                 ret, cic_rec->pcic, cic_rec->vcic));

        if (src != ISUP_SRC_L3_ANSI)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_ANSI(ISUP_MSG_CGB,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);    

        }
        else
        {
            ISUP_Alarm_ANSI(3023, __FILE__, __LINE__, "cic: %x Range: %d "
                            "dpc: %d opc: %d", cic, rs_ie.param_data.rangeAndStatus.range,
                            MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                            MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
        }
        return;
    }

    /* Forward CGB appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received CGB from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if(sup_msg_type != BLOCK_WO_RELEASE &&
           sup_msg_type != BLOCK_W_IMDIAT_RELEASE)
        {
           ISUP_DEBUG(("Incorrect CGB Blocking Type Indicator: 0x%02x\n",
                                                              sup_msg_type));
           return;
        }

        __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, &num_affected_cics);

        /* Check for all the CICs in range (equipped/not)
         * if not equipped; any of them,
         * send UCIC for all unequipped CICs.
         */
        if(__ISUP_IsRangeCICUnequipped(cic_rec, config_info, affected_cics,
                                                       num_affected_cics))
        {
           uneqCicPresent = ITS_TRUE;
        }

        bool_ret = __ISUP_BlockingMGBRCommon1(cic_rec, config_info,
                                    affected_cics, num_affected_cics,
                                    sup_msg_type, rs_ie);

        if (bool_ret == ITS_FALSE)
        {
            __ISUP_GetCGBARangeNStatus(cic_rec, config_info, affected_cics,
                                               num_affected_cics, &cgba_rs);

            cgba_rs.range =  rs_ie.param_data.rangeAndStatus.range;
        }
        else
        {
            if (rs_ie.param_data.rangeAndStatus.range == 0)
            {
                if (uneqCicPresent == ITS_TRUE)
                {
                   __ISUP_GetCGBARangeNStatus(cic_rec, config_info,
                              affected_cics, num_affected_cics, &cgba_rs);

                   cgba_rs.range =  num_affected_cics - 1;
                }
                else
                {
                   cgba_rs.range =  rs_ie.param_data.rangeAndStatus.range;
                }
            }
        }

        /* Send to L3 */
        SPRC_SendCGBAToMTP3_ANSI(cic_rec, config_info, cgba_rs, sup_msg_type);

        /* Change mgbr state to IDLE */
        cic_rec->mgbr_state = MGBR_IDLE;
    }
    else 
    {
        ISUP_DEBUG(("Received CGB from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->mgbs_state != MGBS_WAIT_FOR_CGBA)
        {
            if(sup_msg_type != BLOCK_WO_RELEASE &&
               sup_msg_type != BLOCK_W_IMDIAT_RELEASE)
            {
               ISUP_DEBUG(("Incorrect CGB Blocking Type Indicator: 0x%02x\n",
                                                               sup_msg_type));
               return;
            }

            __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics,
                                           &num_affected_cics);


           __ISUP_BlockingMGBSCommon1(cic_rec, config_info, affected_cics,
                                      num_affected_cics, sup_msg_type, rs_ie);

           /* store the message in msg for cic_rec */
           cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, ITS_TRUE);
           memcpy(cic_msg->cgb_msg, msg->data, msg->len);
           cic_msg->cgb_msg_len = msg->len;
           ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, ITS_TRUE);

           /* Copy the Event before 1st-sending */
           event.src = msg->src;
           event.len = msg->len;
           event.data = (ITS_OCTET *)ITS_Malloc(msg->len);
           memcpy(event.data, msg->data, msg->len);

           /* Send to L3 */
           SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

           __ISUP_StartCGBTimers(cic_rec, config_info);

           /* Send 2nd-CGB to L3 */
           SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

           /* Change mgbs state to IDLE */
           cic_rec->mgbs_state = MGBS_WAIT_FOR_CGBA;
        }
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BugId: 389     Added Message type in the
 *                                          Error indication to application.
 *
 ****************************************************************************/
ITSSS7DLLAPI void
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

        if (src != ISUP_SRC_L3_ANSI)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_ANSI(ISUP_MSG_CGBA,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);    
        }
        else
        {
            ISUP_Alarm_ANSI(3024, __FILE__, __LINE__, "cic: %x, Range: %d "
                            "dpc:%d opc: %d", cic, rs_ie.param_data.rangeAndStatus.range,
                            MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                            MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
        }
        return;
    }

    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received CGBA from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        
        if (sup_msg_type == BLOCK_WO_RELEASE || 
            sup_msg_type == BLOCK_W_IMDIAT_RELEASE)
        {
            __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                   &num_affected_cics);

            if (cic_rec->mgbs_state == MGBS_IDLE)
            {
                bool_ret = __ISUP_HandleUnexpectedCGBA(cic_rec, config_info,
                                            sup_msg_type, rs_ie, affected_cics,
                                            num_affected_cics);
                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("Unexpected CGBA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_CGBA_ABNORMAL_ACK);
                    return;
                }
            }
            else if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGBA)
            {
                bool_ret = __ISUP_CompareCGBAWithCGB(msg, cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("CGBA compare CGB failed pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    return;
                }

                /* Stop timers T18, T19 */
                __ISUP_StopCGBTimers(cic_rec, config_info);

                bool_ret = __ISUP_HandleUnexpectedCGBA(cic_rec, config_info, 
                                            sup_msg_type, rs_ie, affected_cics,
                                            num_affected_cics);

                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("Unexpected CGBA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    return;
                }

                /* Send to app */
                SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
                
                /* Change state to IDLE */
                cic_rec->mgbs_state = MGBS_IDLE;
            }
            else if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGUA)
            {
                /* Stop timers T20, T21 */
                __ISUP_StopCGUTimers(cic_rec, config_info);

                bool_ret = __ISUP_HandleUnexpectedCGBA(cic_rec, config_info, 
                                            sup_msg_type, rs_ie, affected_cics,
                                            num_affected_cics);

                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("Unexpected CGBA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_CGBA_ABNORMAL_ACK);
                    return;
                }

            }
        }
        else
        {
            /* error, discard */
        }
    }
    else 
    {
       ISUP_DEBUG(("Received Unexpected CGBA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        ISUP_Alarm_ANSI(3025, __FILE__, __LINE__, "dpc: %d opc: %d "
                       "cic: %x Message: %x",
                       MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                       MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                       ISUP_PCIC_TO_CIC(cic_rec->pcic),
                       msg->data[sizeof(MTP3_HEADER_ANSI) + 
                       sizeof(ITS_USHORT) + sizeof(ITS_OCTET)]);
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
 *
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_CSC_Received_CGU(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;
    ITS_USHORT affected_cics[256];
    ITS_USHORT num_affected_cics;
    ISUP_RANGE_AND_STATUS cgua_rs;
    ITS_BOOLEAN bool_ret = ITS_TRUE;
    ITS_BOOLEAN uneqCicPresent = ITS_FALSE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("CGU RangeStatus check failed (%d), pcic 0x%08x, vcic %d.\n",
                 ret, cic_rec->pcic, cic_rec->vcic));

        if (src != ISUP_SRC_L3_ANSI)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_ANSI(ISUP_MSG_CGU,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);    
        }
        else
        {
            ISUP_Alarm_ANSI(3026, __FILE__, __LINE__, "cic: %x Range: %d "
                           "dpc: %d opc: %d", cic, rs_ie.param_data.rangeAndStatus.range,
                            MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                            MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
        }
        return;
    }

    /* Forward CGU appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received CGU from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if(sup_msg_type != BLOCK_WO_RELEASE &&
           sup_msg_type != BLOCK_W_IMDIAT_RELEASE)
        {
           ISUP_DEBUG(("Incorrect CGU Blocking Type Indicator: 0x%02x\n",
                                                              sup_msg_type));
           return;
        }

        __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, &num_affected_cics);
  
        /* Check for all the CICs in range (equipped/not)
         * if not equipped; any of them,
         * send UCIC for all unequipped CICs.
         */
        if(__ISUP_IsRangeCICUnequipped(cic_rec, config_info, affected_cics,
                                                      num_affected_cics))
        {
          uneqCicPresent = ITS_TRUE;
        }

        bool_ret = __ISUP_UnblockingMGBRCommon1(cic_rec, config_info,
                             affected_cics, num_affected_cics, rs_ie);

        if (bool_ret == ITS_TRUE)
        {
          __ISUP_GetCGUARangeNStatus(cic_rec, config_info, affected_cics,
                                     num_affected_cics, &cgua_rs);

          cgua_rs.range =  rs_ie.param_data.rangeAndStatus.range;
        }
        else
        {
            if (rs_ie.param_data.rangeAndStatus.range == 0)
            {
                if (uneqCicPresent == ITS_TRUE)
                {
                    __ISUP_GetCGUARangeNStatus(cic_rec, config_info,
                                  affected_cics, num_affected_cics, &cgua_rs);

                    cgua_rs.range =  num_affected_cics - 1;
                }
                else
                {
                   cgua_rs.range =  rs_ie.param_data.rangeAndStatus.range;
                }
            }
        }

        /* Send to L3 */
        SPRC_SendCGUAToMTP3_ANSI(cic_rec, config_info, cgua_rs, sup_msg_type);

        /* Change mgbr state to IDLE */
        cic_rec->mgbr_state = MGBR_IDLE;
    }
    else 
    {
        ISUP_DEBUG(("Received CGU from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        
        if (sup_msg_type == BLOCK_WO_RELEASE ||
            sup_msg_type == BLOCK_W_IMDIAT_RELEASE)
        {
            if (cic_rec->mgbs_state == MGBS_IDLE)
            {
                /* Store the message in cic rec */
                cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE,
                                                            ITS_TRUE);
                memcpy(cic_msg->cgu_msg, msg->data, msg->len);
                cic_msg->cgu_msg_len = msg->len;
                ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, ITS_TRUE);

                /* Send to L3 */
                SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);
        
                __ISUP_StartCGUTimers(cic_rec, config_info);

                cic_rec->mgbs_state = MGBS_WAIT_FOR_CGUA;
            }
            else if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGBA)
            {
                /* Stop Timers */
                __ISUP_StopCGBTimers(cic_rec, config_info);

                /* Resend CGB  */
                SPRC_ResendCGBToMTP3_ANSI(cic_rec, config_info);

                /* Start the Timers */
                __ISUP_StartCGBTimers(cic_rec, config_info);

                /* Send 2nd CGB to L3 */
                SPRC_ResendCGBToMTP3_ANSI(cic_rec, config_info);

                /* Drop current CGU */
            }
        }
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
 *
 ****************************************************************************/
ITSSS7DLLAPI void
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

        if (src != ISUP_SRC_L3_ANSI)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_ANSI(ISUP_MSG_CGUA,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);    
        }
        else
        {
            ISUP_Alarm_ANSI(3027, __FILE__, __LINE__, "cic :%x, Range: %d "
                            "dpc: %d opc: %d", cic, rs_ie.param_data.rangeAndStatus.range,
                            MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                            MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
        }
        return;
    }

    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received CGUA from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (sup_msg_type == BLOCK_WO_RELEASE || 
            sup_msg_type == BLOCK_W_IMDIAT_RELEASE)
        {
            __ISUP_GetAffectedCics(cic, &rs_ie, affected_cics, 
                                   &num_affected_cics);

            if (cic_rec->mgbs_state == MGBS_IDLE)
            {
                bool_ret = __ISUP_HandleUnexpectedCGUA(cic_rec, config_info,
                                            sup_msg_type, rs_ie, affected_cics,
                                            num_affected_cics);

                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("Unexpected CGUA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK);
                    return;
                }
            }
            else if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGUA)
            {
                bool_ret = __ISUP_CompareCGUAWithCGU(msg, cic_rec, config_info);
                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("CGUA compare CGU failed pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    return;
                }

                /* Stop timers T20, T21 */
                __ISUP_StopCGUTimers(cic_rec, config_info);

                bool_ret = __ISUP_HandleUnexpectedCGUA(cic_rec, config_info,
                                            sup_msg_type, rs_ie, affected_cics,
                                            num_affected_cics);
                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("Unexpected CGUA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    return;
                }

                /* Send to app */
                SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

                __ISUP_ProcessAffectedCics(affected_cics, 
                                           num_affected_cics,
                                           __ISUP_UnblockingMGBSToBLS,
                                           cic_rec, config_info);

                cic_rec->mgbs_state = MGBS_IDLE;
            }
            else if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGBA)
            {
                /* Stop timers T18, T19 */
                __ISUP_StopCGBTimers(cic_rec, config_info);

                bool_ret = __ISUP_HandleUnexpectedCGUA(cic_rec, config_info,
                                            sup_msg_type, rs_ie, affected_cics,
                                            num_affected_cics);

                if (bool_ret == ITS_FALSE)
                {
                    /* Maintenance system ind */
                    ISUP_CRITICAL(("Unexpected CGUA pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK);
                    return;
                }
            }
        }
    }
    else 
    {
        ISUP_DEBUG(("Received Unexpected CGUA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
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
 *
 ****************************************************************************/
ITSSS7DLLAPI void
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

    ITS_USHORT affected_cics[256];
    ITS_USHORT num_affected_cics;

    /* Forward GRA appropriately */

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("GRA RangeStatus check failed (%d), pcic 0x%08x, vcic %d.\n",
                 ret, cic_rec->pcic, cic_rec->vcic));

        if (src != ISUP_SRC_L3_ANSI)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_ANSI(ISUP_MSG_GRA,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);    
        }
        else
        {
            ISUP_Alarm_ANSI(3028, __FILE__, __LINE__, "cic :%x, Range: %d "
                            "dpc: %d opc: %d", cic, rs_ie.param_data.rangeAndStatus.range,
                            MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                            MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
        }
        return;
    }

    if (src == ISUP_SRC_L3_ANSI)
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
                return;
            }

            if (rs_ie.param_data.rangeAndStatus.range != 0)
            {
                __ISUP_GetGRACics(cic, &rs_ie, set_cics, &num_set_cics,
                                  unset_cics, &num_unset_cics);

                __ISUP_ProcessAffectedCics(unset_cics,
                                           num_unset_cics,
                                           __ISUP_IdleCircuit,
                                           cic_rec, config_info);

               __ISUP_ProcessAffectedCics(set_cics,
                                          num_set_cics,
                                          __ISUP_IdleRemoteBlockCircut,
                                          cic_rec, config_info);

             }
             else
             {
               __ISUP_GetGRSCics(cic, &rs_ie, affected_cics, &num_affected_cics);

               __ISUP_ProcessAffectedCics(affected_cics,
                                          num_affected_cics,
                                          __ISUP_IdleCircuit,
                                          cic_rec, config_info);
             }

            /* Stop timers T22, T23 */
            __ISUP_StopGRSTimers(cic_rec, config_info);

            /* Send to app */
            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

            cic_rec->cgrs_state = CGRS_IDLE;
        }
    }
    else 
    {
        ISUP_DEBUG(("Received Unexpected GRA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

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
 *
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_CSC_Received_GRS(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int ret = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_OCTET sup_msg_type;
    ITS_USHORT cic;
    ITS_USHORT affected_cics[256];
    ITS_USHORT num_affected_cics;
    ITS_OCTET  range;
    ISUP_RANGE_AND_STATUS gra_rs;    
    ITS_EVENT  event ;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    /* Validate message */
    ret = __ISUP_Validate_RangeStatus(msg, cic_rec, config_info,
                                      &rs_ie, &sup_msg_type, &cic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("GRS RangeStatus check failed (%d), pcic 0x%08x",
                    " vcic %d.\n", ret, cic_rec->pcic, cic_rec->vcic));
    
        if (src != ISUP_SRC_L3_ANSI)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_ANSI(ISUP_MSG_GRS,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);    
        }
        else
        {
            ISUP_Alarm_ANSI(3029, __FILE__, __LINE__, "cic :%x Range: %d "
                            "dpc %d opc: %d", cic, rs_ie.param_data.rangeAndStatus.range,
                            MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                            MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
        }
        return;
    }

    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received GRS from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

 
        if (cic_rec->cgrr_state == CGRR_IDLE)
        {
            __ISUP_GetGRSCics(cic, &rs_ie, affected_cics, &num_affected_cics);

            /* Check for all the CICs in range (equipped/not)
             * if not equipped; any of them,
             * drop the GRA acknowledgement,
             * send UCIC for the unequipped CICs.
             */
            if(__ISUP_IsRangeCICUnequipped( cic_rec, config_info,
                                            affected_cics, num_affected_cics))
            {
              /* NO ACKNOWLADGE to L3; message dropped */
              SPRC_SendIndToApp_ANSI(ITS_ISUP_UCIC_GRSDROPPED_IND, cic_rec);
              return;
            }
            range = rs_ie.param_data.rangeAndStatus.range;

            if (range == 0)
            {
               /* FIXME: No GBR/GBNR state
                * Resend Group Blocking CGRR->GBR
                * Resend Group Blocking CGRR->GBNR
                * This action makes GBR/GBNR state IDLE
                */

                __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                           __ISUP_ResetCGRRCommon0,
                                           cic_rec, config_info);

                gra_rs.range = 0;
            }
            else
            { 
                __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                           __ISUP_ResetCGRRCommon1,
                                           cic_rec, config_info);
                __ISUP_GetGRARangeNStatus(cic_rec, 
                                          config_info, 
                                          affected_cics,
                                          num_affected_cics,
                                          &gra_rs);

            }

            /* Send to L3 */
            SPRC_SendGRAToMTP3_ANSI(cic_rec, config_info, gra_rs);

            /* Change cgrr state to IDLE */
            cic_rec->cgrr_state = CGRR_IDLE;
        }
    }
    else 
    {
        ISUP_DEBUG(("Received GRS from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cgrs_state == CGRS_IDLE)
        {
            /* Store the message in cic rec */
            cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, ITS_TRUE);
            memcpy(cic_msg->grs_msg, msg->data, msg->len);
            cic_msg->grs_msg_len = msg->len;
            ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, ITS_TRUE);

            /* Stop CGRS -> GBUS (Blocking and Unblocking both */
            __ISUP_ResetCGRSToMGBS(cic_rec, config_info);

            __ISUP_GetGRSCics(cic, &rs_ie, affected_cics, &num_affected_cics);

            /* 
             * For each circuit in group
             * Reset call processing on CICs
             * Remove any Blocking
             * Make it Transient
             */
            __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                       __ISUP_ResetCGRSCommon2,
                                       cic_rec, config_info);

            /* Copy the event before sending
             * for further use
             */
            event.src = msg->src;
            event.len = msg->len;
            event.data = (ITS_OCTET *)ITS_Malloc(msg->len);
            memcpy(event.data, msg->data, msg->len);
            
            /* Send to L3 */
            SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

            /* Start timers T23, T22 */
            __ISUP_StartGRSTimers(cic_rec, config_info);

            /* Send to L3; 2nd GRS sent */
            SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

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
ITSSS7DLLAPI void
__ISUP_CSC_Received_RSC(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward RSC appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received RSC from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->crs_state == CRS_WAIT_FOR_RELEASE)
        {
            /* send RLC to SPRC */
            SPRC_SendRLCToMTP3_ANSI(cic_rec, config_info);

            /* Stop Timer T16 and T17 */
            __ISUP_StopRSCTimers(cic_rec, config_info);

            /* Stop Repeat RSC timer also */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T98);

            /* FIXME:
             * Check for Alert Indicator On/Off
             * If ON;alert maintenance, otherwise do not
             */

            /* Indication to App */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_RSC_CPCIDLE_STIND, cic_rec);

            /* Idle circuit and change fsm state to IDLE*/
            ISUP_ClearCic(cic_rec);

            /* crs state to Idle */
            cic_rec->crs_state = CRS_IDLE;
        }
        else if (cic_rec->crr_state == CRR_IDLE)
        {
            /* check whether ckt is "Not" Idle */
            
            if (!(ISUP_CIC_IS_IDLE(cic_rec->cic_state)) )
            {
                __ISUP_ResetCRRToCPC(cic_rec, config_info);
            }

            if (ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
            {
                __ISUP_BlockingCRRToBLS(cic_rec, config_info);
            }
            if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
            {
                __ISUP_UnblockingCRRToBLR(cic_rec, config_info);
            }

            __ISUP_ResetCompleteCPCIToCRR(cic_rec, config_info);
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
            __ISUP_ResetCRSToCPC(cic_rec, config_info);

            __ISUP_ResetCRSCommon1(cic_rec, config_info);

            __ISUP_StopCRRToCRO(cic_rec, config_info);
            __ISUP_StopCRRToCRI(cic_rec, config_info);

            ISUP_CIC_SET_TRANSIENT(cic_rec->cic_state);

            /* Send to L3 */
            SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

            __ISUP_StartRSCTimers(cic_rec, config_info);

            cic_rec->reset_flag = RESET_FROM_CC;

            cic_rec->crs_state = CRS_WAIT_FOR_RELEASE;

            cic_rec->fsm_state = WAIT_INCOMING_RLC;
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_UBA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward UBA appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received UBA from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->bls_state == BLS_IDLE)
        {
            if (ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
            {
                /* Send BLO to SPRC */
                SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);
    
                /* Start T12, T13 */
                __ISUP_StartBLOTimers(cic_rec, config_info);
    
                /* Set the bls state to Wait for BLA */
                cic_rec->bls_state = BLS_WAIT_FOR_BLA;

                /* Send the UBA Ind to App */
                SPRC_SendIndToApp_ANSI(ITS_ISUP_UBA_IND, cic_rec);

                PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS,
                            PEG_ISUP_CIC_UNEXP_UBA_ABNORMAL_ACK);
            }
            else
            {
                /* discard message */
                /* No change of state */
            }
        }
        else if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
        {
            /* Send BLO to SPRC */
            SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_UBA_ABNORMAL_ACK);
    
            /* No change of state here */
        }
        else if (cic_rec->bls_state == BLS_WAIT_FOR_UBA)
        {
            /* We are in WaitForUBA state */
            /* This is a response to a UBL sent earlier */

            /* Send to app - Confirmation */
            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

            /* Remove Local Blocking */
            ISUP_CIC_REMOVE_LOC_BLOCK(cic_rec->cic_state);

            /* Stop timers T15, T14 */
            __ISUP_StopUBLTimers(cic_rec, config_info);

            cic_rec->bls_state = BLS_IDLE;
        }

        /* Change state to IDLE */
    }
    else 
    {
        ISUP_DEBUG(("Received Unexpected UBA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_UBL(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward UBL appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received UBL from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* BLR State Machine */
        if (cic_rec->blr_state == BLR_IDLE)
        {
            /* Check whether remotely blocked */
            if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
            {
                /* Send Ind to app */
                SPRC_SendIndToApp_ANSI(ITS_ISUP_UBL_RUNBLOCK_IND, cic_rec);

                /* Remove Remote Blocking */
                ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                cic_rec->blr_state = BLR_IDLE;
            }

            /* Automatically send UBA to remote */
            SPRC_SendUBAToMTP3_ANSI(cic_rec, config_info);


            /* No change of state here */
        }
    }
    else
    {
        ISUP_DEBUG(("Received UBL from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Process according to BLS state */
        if (cic_rec->bls_state == BLS_IDLE)
        {
            /* Send to L3 */
            SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

            __ISUP_StartUBLTimers(cic_rec, config_info);

            cic_rec->bls_state = BLS_WAIT_FOR_UBA;
        }
        else if (cic_rec->bls_state == BLS_WAIT_FOR_BLA)
        {
            __ISUP_StopBLOTimers(cic_rec, config_info);

            /* Send to L3 */
            SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

            __ISUP_StartUBLTimers(cic_rec, config_info);

            cic_rec->bls_state = BLS_WAIT_FOR_UBA;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an CVT received in any state is done here.
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
__ISUP_CSC_Received_CVT(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward CVT appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received CVT from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cvtr_state != CVTR_IDLE)
        {
            ISUP_CRITICAL(("CVTR in progress..discarding incomig CVT,"
                           " pcic 0x%08x, vcic %d.\n",
                           cic_rec->pcic, cic_rec->vcic));
            return;
        }

        /* FIXME:
         * Current implementation depends on the
         * application for Ckt translation existance.
         * App should check for CCLI and CIN and it requests
         * ISUP stack to send a CVR with required parameters.
         * So the received CVT is given to Application.
         */

        /* Send to app */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

        /* Change cvtr state to CVTR_WAIT_FOR_CVR */
        cic_rec->cvtr_state = CVTR_WAIT_FOR_CVR;

        /* Change state to IDLE - No change of cpc fsm state*/
    }
    else
    {
        ISUP_DEBUG(("Received CVT in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /*
         * FIXME: It is assumed that the circuit translation
         * is done by the application as it has CLCI info.
         * TBD: if it is need, this should be implemented
         * on a demand basis.
         */

        if (cic_rec->cvts_state != CVTS_IDLE)
        {
            ISUP_CRITICAL(("CVTS in progress..discarding request,"
                           " pcic 0x%08x, vcic %d.\n",
                           cic_rec->pcic, cic_rec->vcic));
            return;
        }

        /* Send to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

        __ISUP_StartCVTTimers(cic_rec, config_info);

        /* Change cvts state to CVTS_WAIT_FOR_CVR */
        cic_rec->cvts_state = CVTS_WAIT_FOR_CVR;

        /* Change call state to IDLE, i.e. no change. */
    }

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for an CVR received in any state is done here.
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
__ISUP_CSC_Received_CVR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward CVR appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_OPC_DPC_STAT *config_stat = NULL;
        ISUP_DEBUG(("Received CVR in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        switch(cic_rec->cvts_state)
        {   
        case CVTS_WAIT_FOR_CVR:

            /* Stop timer TCVT */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCVT);
            break;

        case CVTS_WAIT_FOR_CVR_UPT:

            /* chage the status ISUP_REMOTE_ISUP_STATUS */
            config_info->remote_isup_stat = ISUP_REMOTE_AVAILABLE;

            /* We have to update opc_dpc_stat as well here wierd */
            config_stat = ISUP_FindOpcDpcStat(config_info->opc_dpc_ni,
                                                            ITS_TRUE);
            if(config_stat != NULL)
            {
                config_stat->remote_isup_stat = ISUP_REMOTE_AVAILABLE;
                ISUP_ReleaseOpcDpcStat(config_stat, ITS_TRUE);
            }

            /* Stop timer T37 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T37);
            break;

         default:
            ISUP_DEBUG(("Received Unexpected CVR from MTP3 in CVTS State: %d :."
                        " Discarding CVR...pcic 0x%08x, vcic %d\n",
                        cic_rec->cvts_state, cic_rec->pcic, cic_rec->vcic));
            return;
         }

        /* FIXME:
         * In the current implementation
         * this CVR will be given to application
         * Applicaton should do the CIN and CLLI checks
         */

        /* Send to app */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

        /* Change cvts state to idle */
        cic_rec->cvts_state = CVTS_IDLE;

        /* Change call state to IDLE - No change*/
    }
    else
    {
        ISUP_DEBUG(("Received CVR in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cvtr_state != CVTR_WAIT_FOR_CVR)
        {
            ISUP_DEBUG(("Received Unexpected CVR from APP in CVTR State: %d :."
                        " Discarding CVR...pcic 0x%08x, vcic %d\n",
                        cic_rec->cvtr_state, cic_rec->pcic, cic_rec->vcic));
            return;
        }
        /* Send to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

        /* Change cvtr state to idle */
        cic_rec->cvtr_state = CVTR_IDLE;

        /* Change state to IDLE - no change of fsm state */
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_CCR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received CCR from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            if (cic_rec->cot_first_ind == ITS_FALSE)
            {
                /*stop T27 timer*/
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
            }
            else
            {
                /* Check if TCCRR is running & stop it */
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCCRR);
            }


            /* Change CRI state to wait for LPA from APP */
            cic_rec->cri_state = CRI_WAIT_FOR_LPA;
            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

            /** Removed
            SPRC_SendLPAToMTP3_ANSI(cic_rec,config_info);
            **/
        }
        else if (cic_rec->fsm_state == IDLE)
        {
            if (cic_rec->cot_first_ind == ITS_FALSE)
            {
                /*stop T27 timer*/
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
            }

            /* Change CRI state to wait for REL */
            cic_rec->cri_state = CRI_WAIT_FOR_LPA;

            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

            /** Removed
            SPRC_SendLPAToMTP3_ANSI(cic_rec,config_info);
            **/
        }
        else
        {
            ISUP_ERROR(("Received Unexpected CCR message"));
        }
    }
    else
    {
        ISUP_DEBUG(("Received CCR in from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->fsm_state == IDLE ||
            cic_rec->cro_state == CRO_WAIT_FOR_OUTGOING_CCR)
        {
            cic_rec->cro_state = CRO_WAIT_FOR_COT;
            cic_rec->dco_state = DCO_WAIT_FOR_LPA;

            __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TCCR,
                              config_info->\
                              tmr_hndl_info[ITS_ISUP_TIMER_TCCR].tmr_value);

            /* Send to L3 */
            SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);
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
 *
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_CSC_Received_LPA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int tret = 0;

    if (src == ISUP_SRC_L3_ANSI)
    {

        ISUP_DEBUG(("Received LPA from L3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if ( cic_rec->dco_state == DCO_WAIT_FOR_LPA)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCCR);

            /*Start T24 Timer and wait for COT report */
            tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T24, config_info->
                    tmr_hndl_info[ITS_ISUP_TIMER_T24].tmr_value);
            if (tret != ITS_SUCCESS)
            {
                ISUP_ERROR(("IDLE : Failed to start T24."
                    "pcic 0x%08x, vcic %d.\n",cic_rec->pcic, cic_rec->vcic));
            }

            /*Change DCO state to idle*/
            cic_rec->dco_state = DCO_IDLE;
            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
        }
        else
        {
            ISUP_ERROR(("Received Unexpected LPA message"));
        }
    }
    else
    {
        ISUP_DEBUG(("Received LPA from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cri_state == CRI_WAIT_FOR_LPA)
        {
            /* Start timer T34 */
            if (__ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T34,
               config_info->\
               tmr_hndl_info[ITS_ISUP_TIMER_T34].tmr_value) != ITS_SUCCESS)
            {
                ISUP_ERROR(("CSC: Failed to start T34."
                "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }
            cic_rec->cri_state = CRI_WAIT_FOR_REL;
        }

        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

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
ITSSS7DLLAPI void
__ISUP_CSC_Received_UCIC(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    ITS_OCTET status = 0xFF;

    if (src == ISUP_SRC_L3_ANSI)
    {
        /* received from the remote end because the
         * remote end is unable to perform a cic translation
         * on the message sent by us.
         */

        ISUP_DEBUG(("Received UCIC from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Query circuit status from SPRC */
        status = SPRC_QueryCircuitStatus(cic_rec);

        switch (status)
        {
            case SPRC_CKTS_TRANSIENT:
                /* No need to Call UCIC and CPC interection
                 * as We don't put CIC in TRANSIENT for any
                 * Call processing State
                 */

                /* Stop UCIC to CRS */
                __ISUP_StopUCICToCRS(cic_rec, config_info);

                /* Stop UCIC to CGRS */
                __ISUP_StopUCICToCGRS(cic_rec, config_info);

                /* Stop UCIC to CRO */
                __ISUP_StopUCICToCRO(cic_rec, config_info);

                break;

            case SPRC_CKTS_OUTBUSY_ACTIVE:
            case SPRC_CKTS_OUTBUSY_LBLOCKED:
            case SPRC_CKTS_OUTBUSY_RBLOCKED:
            case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                /* This is because we do put circuit in outgoing busy
                 * state before receiving any backward message though
                 * by spec it should be in TRANSIENT.
                 * same for REL send to Nework
                 */
                /* Reset UCIC to CPC */
                __ISUP_ResetUCICToCPC(cic_rec, config_info);

                /* Stop UCIC to CRO */
                __ISUP_StopUCICToCRO(cic_rec, config_info);

                break;

            case SPRC_CKTS_INBUSY_ACTIVE:
            case SPRC_CKTS_INBUSY_LBLOCKED:
            case SPRC_CKTS_INBUSY_RBLOCKED:
            case SPRC_CKTS_INBUSY_LRBLOCKED:

                /* Stop UCIC to CRO */
                __ISUP_StopUCICToCRO(cic_rec, config_info);

                break;

            case SPRC_CKTS_IDLE_ACTIVE:
            case SPRC_CKTS_IDLE_LBLOCKED:
            case SPRC_CKTS_IDLE_RBLOCKED:
            case SPRC_CKTS_IDLE_LRBLOCKED:

                break;

            default:
                ISUP_ERROR(("__ISUP_CSC_Received_UCIC(): Invalid Ckt state "
                            "(0x%x), pcic 0x%08x, vcic 0x%x.\n",
                            status, cic_rec->pcic, cic_rec->vcic));
                return;
        }

        if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
        {
            /* Remove Remote Blocking. if any */
            ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);
            cic_rec->blr_state = BLR_IDLE;
        }

        if (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LBLOCKED)
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
        SPRC_SendIndToApp_ANSI(ITS_ISUP_UCIC_LBLOCK_STIND, cic_rec);

        /* Send to app */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
    }
    else 
    {
        ISUP_DEBUG(("Received UCIC from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

        /* No change of state */
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
ITSSS7DLLAPI void
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
        ISUP_ERROR(("CQM RangeStatus check failed (%d), pcic 0x%08x, "
                    "vcic %d.\n", ret, cic_rec->pcic, cic_rec->vcic));

        if (src != ISUP_SRC_L3_ANSI)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_ANSI(ISUP_MSG_CQM,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);
        }
        else
        {
            ISUP_Alarm_ANSI(3030, __FILE__, __LINE__, "cic :%x  Range: %d "
                            "dpc %d opc: %d", cic, rs_ie.param_data.rangeAndStatus.range,
                            MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                            MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
        }
        return;
    }

    /* Forward CQM appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received CQM from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Send to app */
        SPRC_SendCQRToMTP3_ANSI(cic_rec, config_info, &rs_ie, cic);

        /* Change state to IDLE */
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
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

        /* Change state to IDLE */
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
ITSSS7DLLAPI void
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

        if (src != ISUP_SRC_L3_ANSI)
        {
            /* Send error indic to app. */
            SPRC_SendErrorToApp_ANSI(ISUP_MSG_CQR,ITS_ISUP_BAD_RNG_STATUS_ERR, cic_rec);
        }
        else
        {
            ISUP_Alarm_ANSI(3031, __FILE__, __LINE__, "cic :%x Range: %d "
                            "dpc %d opc: %d", cic, rs_ie.param_data.rangeAndStatus.range,
                            MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                            MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
        }
        return;
    }

    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received CQR from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Stop timer T28 */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T28);

        __ISUP_UpdateNearEndCktState(msg, cic_rec, config_info);

        /* Send to app */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
    }
    else
    {
        ISUP_DEBUG(("Received Unexpected CQR from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
    }
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT12(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT12 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    ISUP_Alarm_ANSI(3032, __FILE__, __LINE__, "dpc:%d opc: %d cic:%x\n",
                      MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                      MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

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
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T12].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Resend BLO to L3 */
            SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);

            /* Restart T12, update restartCounter */
            __ISUP_StartBLORepeatTimer(cic_rec, config_info);
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT13(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT13 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_BLA_T13);

    ISUP_Alarm_ANSI(3033, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

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
        
        /* Send maint indic to app */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T13].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Check if maintenance has intervened; if yes, clear all & return */

            /* Send BLO to L3 */
            SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);

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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT14(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT14 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    ISUP_Alarm_ANSI(3034, __FILE__, __LINE__,"dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

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
        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T14].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Resend UBL to L3 */
            SPRC_SendUBLToMTP3_ANSI(cic_rec, config_info);

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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT15(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT15 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_UBA_T15);
    
    ISUP_Alarm_ANSI(3035, __FILE__, __LINE__,"dpc: %d opc :%d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));
    
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

        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T15].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Check if maintenance has intervened; if yes, clear all & return */

            /* Send UBL to L3 */
            SPRC_SendUBLToMTP3_ANSI(cic_rec, config_info);
        
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT16(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT16 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    
    ISUP_Alarm_ANSI(3036, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

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
        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T16].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* FIXME:
             * Cross-Check with ANSI SDL whther this is required.
             * Check if maintenance has intervened; if yes,
             * clear all and return
             */
            __ISUP_ResetCRSCommon1(cic_rec, config_info);

            /* Send RSC to SPRC */
            SPRC_SendRSCToMTP3_ANSI(cic_rec, config_info);

            /* Restart T16, update restartCounter */
            __ISUP_StartRSCRepeatTimer(cic_rec, config_info);

            /* set crs state to Wait for RLC */
            cic_rec->crs_state = CRS_WAIT_FOR_RELEASE;
        }
        else
        {
            /* App will send RSC */
            /* Change fsm state to WAIT_OUTGOING_RSC */
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT17(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT17 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
   
    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_ACK_RSC_T17);
 
    ISUP_Alarm_ANSI(3037, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

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

            /* FIXME:
             * check if Alert Indicator is On/Off
             * If on, alert maintenance
             * If off, do not alert maintenance.
             */
        }
        /* Send maint indic to app */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T17].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* FIXME:
             * Check whether the following check is needed.
             * Check if maintenance has intervened; if yes, clear all & return
             */
            __ISUP_ResetCRSCommon1(cic_rec, config_info);

            /* send RSC to SPRC */
            SPRC_SendRSCToMTP3_ANSI(cic_rec, config_info);
            
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

            /* change crs state to Wait for RLC */
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT18(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT18 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    
    ISUP_Alarm_ANSI(3038, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

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

    if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGBA)
    {
        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T18].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Resend CGB to L3 */
            SPRC_ResendCGBToMTP3_ANSI(cic_rec, config_info);

            /* Restart T18, update restartCounter */
            __ISUP_StartCGBRepeatTimer(cic_rec, config_info);

            /* Send 2nd CGB to L3 */
            SPRC_ResendCGBToMTP3_ANSI(cic_rec, config_info);
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT19(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT19 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_CGBA_T19);
    
    ISUP_Alarm_ANSI(3039, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                     MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                     MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

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

    if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGBA)
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
        
        /* Send maint indic to app */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T19].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Check if maintenance has intervened; if yes, clear all & return */

            /* Send CGB to L3 */
            SPRC_ResendCGBToMTP3_ANSI(cic_rec, config_info);

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

            /* Send 2nd CGB to L3 */
            SPRC_ResendCGBToMTP3_ANSI(cic_rec, config_info);
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT20(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT20 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    
    ISUP_Alarm_ANSI(3040, __FILE__, __LINE__,  "dpc: %d opc: %d cic: %x",
                      MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                      MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                             ISUP_PCIC_TO_CIC(cic_rec->pcic));

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

    if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGUA)
    {
        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T20].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Resend CGU to L3 */
            SPRC_ResendCGUToMTP3_ANSI(cic_rec, config_info);

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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT21(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT21 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_CGUA_T21);
    
    ISUP_Alarm_ANSI(3041, __FILE__, __LINE__,  "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

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

    if (cic_rec->mgbs_state == MGBS_WAIT_FOR_CGUA)
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
        
        /* Send maint indic to app */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T21].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Check if maintenance has intervened; if yes, clear all & return */

            /* Send CGU to L3 */
            SPRC_ResendCGUToMTP3_ANSI(cic_rec, config_info);

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
ITSSS7DLLAPI void
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

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    ISUP_DEBUG(("TimeoutT22 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    
    ISUP_Alarm_ANSI(3042, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                      MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                      MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                       ISUP_PCIC_TO_CIC(cic_rec->pcic));
        
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
        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T22].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {

            cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, ITS_TRUE);

            ITS_EVENT_INIT(&event, ITS_ISUP_ANSI_SRC, cic_msg->grs_msg_len);
            memcpy((void *)(event.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

            ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

            __ISUP_Validate_RangeStatus(&event, cic_rec, config_info,
                                        &rs_ie, &sup_msg_type, &cic);

            __ISUP_GetGRSCics(cic, &rs_ie, affected_cics, &num_affected_cics);

            __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                       __ISUP_ResetCGRSCommon1,
                                       cic_rec, config_info);
            ITS_EVENT_TERM((&event));

            /* Resend GRS to L3 */
            SPRC_ResendGRSToMTP3_ANSI(cic_rec, config_info);

            /* Restart T22, update restartCounter */
            __ISUP_StartGRSRepeatTimer(cic_rec, config_info);

            /* Send 2nd GRS to L3 */
            SPRC_ResendGRSToMTP3_ANSI(cic_rec, config_info);
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
ITSSS7DLLAPI void
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

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    ISUP_DEBUG(("TimeoutT23 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_NO_GRA_T23); 
 
    ISUP_Alarm_ANSI(3043, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                     MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                     MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

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
        
        /* Send maint indic to app */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
        
        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T23].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, ITS_TRUE);

            ITS_EVENT_INIT(&event, ITS_ISUP_ANSI_SRC, cic_msg->grs_msg_len);
            memcpy((void *)(event.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

            ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

            __ISUP_Validate_RangeStatus(&event, cic_rec, config_info,
                                        &rs_ie, &sup_msg_type, &cic);

            __ISUP_GetGRSCics(cic, &rs_ie, affected_cics, &num_affected_cics);

            __ISUP_ProcessAffectedCics(affected_cics, num_affected_cics,
                                       __ISUP_ResetCGRSCommon1,
                                       cic_rec, config_info);
            ITS_EVENT_TERM((&event));

            /* Resend GRS to L3 */
            SPRC_ResendGRSToMTP3_ANSI(cic_rec, config_info);

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

            /* Send 2nd GRS to L3 */
            SPRC_ResendGRSToMTP3_ANSI(cic_rec, config_info);
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT24(ISUP_TIMER_ENTRY* t_entry,
                               ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    ISUP_DEBUG(("TimeoutT24 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic,
                 ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    ISUP_Alarm_ANSI(3044, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

    if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T24].tmr_hndl_layer
        == ISUP_TMR_HNDL_STACK)
    {
        /*Send COT msg with failure indic and start T25 timer */
        SPRC_SendCOTToMTP3_ANSI(CONTINUITY_CHECK_FAILED,cic_rec,config_info);


       /*FIXME: Send Reattempt indication */

       if (__ISUP_StopCPCToCCO(cic_rec, config_info))
       {
        __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T7);
        __ISUP_StartCPCToCRO(cic_rec, config_info);
       }
       else
       {
        __ISUP_StartCPCToCRO(cic_rec, config_info);
       }
    }
    else
    {
        /* do nothing */
        /* be in the same state */
        /* handle messages/COT(pass/fail) like it never expired */
    }

    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT25(ISUP_TIMER_ENTRY* t_entry,
                               ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int tret =0;
    ISUP_Alarm_ANSI(3045, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                            ISUP_PCIC_TO_CIC(cic_rec->pcic));

    if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY)
    {
        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T25].tmr_hndl_layer
            == ISUP_TMR_HNDL_STACK)
        {
            /*Send CCR msg start TCCR timer */
            SPRC_SendCCRToMTP3_ANSI(cic_rec,config_info);    

            tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TCCR,
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_TCCR].tmr_value);
            if (tret != ITS_SUCCESS)
            {
                ISUP_ERROR(("WAIT COT REPORT Failed to start TCCR."
                        "pcic 0x%08x, vcic %d.\n",cic_rec->pcic,cic_rec->vcic));
            }
     
            cic_rec->dco_state = DCO_WAIT_FOR_LPA;
            cic_rec->cro_state = CRO_WAIT_FOR_COT;
            cic_rec->cot_first_ind = ITS_FALSE;
        }
        else
        {
           /* Send timeout indication and wait for ccr form app*/
           cic_rec->cro_state = CRO_WAIT_FOR_OUTGOING_CCR;
           cic_rec->cot_first_ind = ITS_FALSE;
        }
    }
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
   
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT26(ISUP_TIMER_ENTRY* t_entry,
                               ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int tret =0;

    ISUP_DEBUG(("TimeoutT26 event received. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic,
                 ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    ISUP_Alarm_ANSI(3046, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                     MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                     MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                             ISUP_PCIC_TO_CIC(cic_rec->pcic));

    if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY)
    {
        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T26].tmr_hndl_layer
            == ISUP_TMR_HNDL_STACK)
        {

            /*Send CCR msg and start TCCR timer */
            SPRC_SendCCRToMTP3_ANSI(cic_rec,config_info);    

            tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TCCR,
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_TCCR].tmr_value);

            if (tret != ITS_SUCCESS)
            {
                ISUP_ERROR(("WAIT COT REPORT Failed to start TCCR."
                        "pcic 0x%08x, vcic %d.\n",cic_rec->pcic,cic_rec->vcic));
            }
     
            cic_rec->dco_state = DCO_WAIT_FOR_LPA;
            cic_rec->cro_state = CRO_WAIT_FOR_COT;
        }
        else
        {
            cic_rec->cro_state = CRO_WAIT_FOR_OUTGOING_CCR;
        }
   }
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
   
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT27(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ISUP_DEBUG(("TimeoutT27 event received in . "
               "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));


    ISUP_Alarm_ANSI(3185, __FILE__, __LINE__, "dpc: %d  opc: %d cic: %x", 
                     MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                     MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                     ISUP_PCIC_TO_CIC(cic_rec->pcic));



    /*Reset the circuit */
    __ISUP_CSC_StartCRS(cic_rec,config_info);

    /*Change CRI state to IDLE */
    cic_rec->cri_state = CRI_IDLE;
    cic_rec->cot_first_ind = ITS_TRUE;
    /*
     * Send the timeout data to user app.
     * This will be done whether the procedure is automated or not.
     */
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
    SPRC_SendIndToApp_ANSI(ITS_ISUP_CIC_COT_RESET_RQIND, cic_rec);

    /* Change state to WAIT_INCOMING_RLC */
    cic_rec->fsm_state = WAIT_INCOMING_RLC;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T34 timer in the
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutT34(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ISUP_DEBUG(("TimeoutT34 event received in WAIT_INCOMING_COT state. "
               "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));




    ISUP_Alarm_ANSI(3186, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                    ISUP_PCIC_TO_CIC(cic_rec->pcic));



    /*Reset the circuit */
    __ISUP_CSC_StartCRS(cic_rec,config_info);

    /*Change CRI state to IDLE */
    cic_rec->cri_state = CRI_IDLE;
    cic_rec->cot_first_ind = ITS_TRUE;

    /*
     * Send the timeout data to user app.
     * This will be done whether the procedure is automated or not.
     */
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
    SPRC_SendIndToApp_ANSI(ITS_ISUP_CIC_COT_RESET_RQIND, cic_rec);

    /* Change state to WAIT_INCOMING_RLC */
    cic_rec->fsm_state = WAIT_INCOMING_RLC;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of TCCRR timer in the
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutTCCRR(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ISUP_DEBUG(("TimeoutTCCRR event received in WAIT_INCOMING_COT state. "
               "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));


    ISUP_Alarm_ANSI(3187, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                    ISUP_PCIC_TO_CIC(cic_rec->pcic));


    /*Reset the circuit */
    __ISUP_CSC_StartCRS(cic_rec,config_info);

    /*Change CRI state to IDLE */
    cic_rec->cri_state = CRI_IDLE;
    cic_rec->cot_first_ind = ITS_TRUE;

    /*
     * Send the timeout data to user app.
     * This will be done whether the procedure is automated or not.
     */
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
    SPRC_SendIndToApp_ANSI(ITS_ISUP_CIC_COT_RESET_RQIND, cic_rec);

    /* Change state to WAIT_INCOMING_RLC */
    cic_rec->fsm_state = WAIT_INCOMING_RLC;
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
ITSSS7DLLAPI void
__ISUP_CSC_Received_TimeoutTCCR(ISUP_TIMER_ENTRY* t_entry,
                                ISUP_CIC_INFO *cic_rec,
                                ISUP_OPC_DPC_INFO *config_info)
{
    /*FIX ME Alert maintenance system ALARM*/
    ISUP_CRITICAL(("Falied To receive LPA from reomte"));


    ISUP_Alarm_ANSI(3188, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                    ISUP_PCIC_TO_CIC(cic_rec->pcic));



    /*Reset circuit */
    __ISUP_CSC_StartCRS(cic_rec,config_info);

    cic_rec->cro_state = CRO_IDLE;
    cic_rec->cot_first_ind = ITS_TRUE;
    cic_rec->dco_state =  DCO_IDLE;

    /* Change state to WAIT_INCOMING_RLC */
    cic_rec->fsm_state = WAIT_INCOMING_RLC;

    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
    SPRC_SendIndToApp_ANSI(ITS_ISUP_CIC_COT_RESET_RQIND, cic_rec);
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing of BLS from 
 *      CPC, CQS, CRR and CGRR
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
ITSSS7DLLAPI void
__ISUP_CSC_BlockingBLS(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
   switch(cic_rec->bls_state)
   {
        case BLS_IDLE:
            /* Send BLO to SPRC */
            SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);

            /* Start T12, T13 */
            __ISUP_StartBLOTimers(cic_rec, config_info);

            /* Set the bls state to Wait for BLA */
            cic_rec->bls_state = BLS_WAIT_FOR_BLA;

            break;

        case BLS_WAIT_FOR_BLA:
            /* Send BLO to SPRC */
            SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);

            /* No change of state here */
            break;

        case BLS_WAIT_FOR_UBA:
            /* Remove Local Blocking */
            ISUP_CIC_REMOVE_LOC_BLOCK(cic_rec->cic_state);

            /* Start T14, T15 */
            __ISUP_StopUBLTimers(cic_rec, config_info);

            /* change state to Idle */
            cic_rec->bls_state = BLS_IDLE;

            break;

        default:
            ISUP_ERROR(("__ISUP_CSC_BlockingBLS(), Invalid BLS State. "
                        "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
    }

    return;
}

 /****************************************************************************
  * Start CRS: CPCI->CRS
  * Start CRS: CPCO->CRS
  * Start CRS: CRI->CRS
  * Start CRS: CRO->CRS
  ***************************************************************************/

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
ITSSS7DLLAPI void
__ISUP_CSC_StartCRS(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{

    switch(cic_rec->crs_state)
    {
        case CRS_IDLE:

            /* Mark circuit Transient */
            ISUP_CIC_SET_TRANSIENT(cic_rec->cic_state);

            /* Send RSC to SPRC */
            SPRC_SendRSCToMTP3_ANSI(cic_rec, config_info);

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

/****************************************************************************/
