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
 *  ID: $Id: ansi-inter_state_ansi92.c,v 9.1 2005/03/23 12:54:52 cvsadmin Exp 
 *  $
 * LOG: Revision 9.1  2005/03/23 12:54:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.13  2005/03/21 13:53:56  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.15.2.2.6.1.12.2  2004/12/29 14:35:54  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.15.2.2.6.1.12.1  2004/12/06 13:34:50  mmanikandan
 * LOG: Windows Compilation Support
 * LOG:
 * LOG: Revision 7.15.2.2.6.1  2004/01/05 10:10:44  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.15.2.2.2.3  2003/12/11 13:46:10  ssingh
 * LOG: Alarm Id changed for given case as per Alarm Display Text.
 * LOG:
 * LOG: Revision 7.15.2.2.2.2  2003/11/24 06:36:29  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.15.2.2.2.1  2003/09/13 06:27:00  akumar
 * LOG: Msg Based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 7.15.2.2  2003/06/13 12:05:28  ssingh
 * LOG: CQM/CQR Metrix related changes/fixes reported during BCGI testing
 * LOG: propped from current to PR6.3.
 * LOG:
 * LOG: Revision 7.15.2.1  2003/05/07 10:37:59  ssingh
 * LOG: Latest Changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.9  2003/05/06 13:55:52  sswami
 * LOG: Alarm related changes :opc information included.
 * LOG:
 * LOG: Revision 8.8  2003/04/30 14:20:52  ssingh
 * LOG: Changes done for handling of UCIC received for message cic in
 * LOG: routing level in response of previously sent BLO/CGB/CGU.
 * LOG:
 * LOG: Revision 8.7  2003/04/25 13:26:17  ssingh
 * LOG: Sending UCIC to Far-end for locally not-configured CIC.
 * LOG: __ISUP_IsRangeCICUnequipped modified.
 * LOG:
 * LOG: Revision 8.6  2003/04/24 14:13:25  sswami
 * LOG: Bug #317; Alarm Enhancement related changes done.
 * LOG:
 * LOG: Revision 8.5  2003/04/04 07:09:43  ssingh
 * LOG: ISUP_ReleaseCicMsgBuf related changes done.
 * LOG:
 * LOG: Revision 8.4  2003/04/03 15:24:34  sjaddu
 * LOG: ISUP DSM reorganization.
 * LOG:
 * LOG: Revision 8.3  2003/03/26 12:29:32  ssingh
 * LOG: Modified CIC_INFO changes incorporated. ISUPPending List Items done.
 * LOG:
 * LOG: Revision 8.2  2003/03/15 13:18:08  ssingh
 * LOG: Changes done in existing files to support CRM/CRA messaging.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:28  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.15  2003/01/29 19:08:21  sjaddu
 * LOG: Added one more state for CRI.
 * LOG:
 * LOG: Revision 7.14  2003/01/22 14:55:02  vnitin
 * LOG: Tandem port for Ansi ISUP
 * LOG:
 * LOG: Revision 7.13  2003/01/15 12:29:24  ssingh
 * LOG: Changed done for handling of CQR(rcvd)/UCIC(rcvd)/CGB(immediate Release).
 * LOG: Indications added to inform Application.
 * LOG:
 * LOG: Revision 7.12  2002/12/27 06:57:55  ssingh
 * LOG: GRS/RSC(send) and UCIC(received) interection function changed.
 * LOG:
 * LOG: Revision 7.11  2002/12/03 13:20:44  ssingh
 * LOG: Release Cause been changed in case of CQR handling.
 * LOG:
 * LOG: Revision 7.10  2002/12/02 11:20:02  sjaddu
 * LOG: COT Handling in IDLE state.
 * LOG:
 * LOG: Revision 7.9  2002/11/21 12:00:14  sjaddu
 * LOG: More fixes for continuity.
 * LOG:
 * LOG: Revision 7.8  2002/11/20 12:41:44  akumar
 * LOG: Added CQM/CQR related Alarms, Worked on ALARMS indentation
 * LOG:
 * LOG: Revision 7.7  2002/11/12 06:04:59  akumar
 * LOG: Added ANSI ISUP Alarms
 * LOG:
 * LOG: Revision 7.6  2002/11/07 14:01:16  ssingh
 * LOG: Added FIX for BUG# 147 for inconsistent handling of RLC across the states.
 * LOG:
 * LOG: Revision 7.5  2002/10/30 13:49:18  sjaddu
 * LOG: Set cot_first_time indicator to ITS_TRUE.
 * LOG:
 * LOG: Revision 7.4  2002/10/30 09:04:10  sjaddu
 * LOG: Added Continuity procedures.
 * LOG:
 * LOG: Revision 7.3  2002/10/25 13:43:57  ssingh
 * LOG: Code changes done as a part of BUG 141-to-146 fixing.
 * LOG:
 * LOG: Revision 7.2  2002/10/21 12:26:09  ssingh
 * LOG: Addec functions to support <-CQR- for ANSI.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.8  2002/07/22 21:36:10  ssingh
 * LOG: FIXED some problem processing local REL request.
 * LOG:
 * LOG: Revision 1.1.2.7  2002/07/19 19:12:25  ssingh
 * LOG: ANSI92 completed according to the SDLs.
 * LOG:
 * LOG: Revision 1.1.2.6  2002/07/18 22:40:28  ssingh
 * LOG: Added Code for handling BLS/BLR/RSC from remote/local.
 * LOG:
 * LOG: Revision 1.1.2.5  2002/07/18 19:09:16  ssingh
 * LOG: Added new functions.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/07/18 15:55:53  hbalimid
 * LOG: BLS and BLR states done.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/14 19:01:41  hbalimid
 * LOG: Wait for OGC Completion in place.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/13 17:41:37  hbalimid
 * LOG: Wait for Incoming ACM procedures completed.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/13 02:25:10  hbalimid
 * LOG: Baseline for inter-state machine procedures.
 * LOG:
 *****************************************************************************/
#ident "$Id: ansi-inter_state_ansi92.c,v 1.1.1.1 2007-10-08 11:12:17 bsccs2 Exp $"

#undef CCITT
#undef ANSI
#define ANSI

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <isup_intern.h>
#include <ansi/isup_92.h>


/*
 * Procedures for handling inter state triggers
 * Significantly covers MPC (CSC) to CPC Triggers
 * and inter MPC triggers
 */

/************************************************************************
 **
 ** Forward declarations.
 **
 ************************************************************************/

static int __ISUP_GetCQRCICStatus(ITS_EVENT *msg,
                   ISUP_CIC_INFO *cic_rec,
                   ISUP_OPC_DPC_INFO *config_info,
                   ITS_OCTET *ckt_status,
                   ITS_USHORT *cic);

static ITS_BOOLEAN __ISUP_UpdateCktStatus(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static ITS_BOOLEAN __ISUP_ResetCQSToCPC(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

static ITS_BOOLEAN __ISUP_ReleaseCQSToCPC(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

static ITS_BOOLEAN __ISUP_BlockingCQSToBLS(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

static ITS_BOOLEAN __ISUP_UnblockingCQSToBLS(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info);

static void __ISUP_NearEndStateUNEQ(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateIdleActive(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateInbusyActive(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateOutbusyActive(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateIdleLBlocked(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateInbusyLBlocked(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateOutbusyLBlocked(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateIdleRBlocked(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateInbusyRBlocked(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateOutbusyRBlocked(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateIdleLRBlocked(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateInbusyLRBlocked(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_NearEndStateOutbusyLRBlocked(ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info,
                    ITS_OCTET far_end_state);

static void __ISUP_StopWaitingCGRS(ISUP_CIC_INFO *cic_rec, 
                    ISUP_OPC_DPC_INFO *config_info);

/************************************************************************/

/* FIXME:
 * Most of the functions here can be grouped
 * Each function should have a switch on fsm_state
 * Common functions should be:
 *
 * Reset():
 *    ResetCGBRToCPC 
 *    ResetCRRToCPC 
 *    ResetCQSToCPC
 *    ResetGBURToCPC
 *    ResetGBUSToCPC
 *    ResetUCICToCPC
 *        switch(cic_rec->fsm_state)
 *        {
 *            case IDLE:
 *
 *            case WAIT_INCOMING_ACM:
 *
 *            . . .
 *            . . .
 *
 *            default:
 *
 *        }
 *
 * Blocking():
 *    BlockingBLRToCPC
 * 
 */
 

/*
 * RSC Procedures
 */

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from CRR to CPC
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ResetCRRToCPC(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_TRUE;
    ITS_UINT indId = ITS_ISUP_RSC_CPCIDLE_STIND;

    switch (cic_rec->fsm_state)
    {
    case IDLE :
         return ITS_TRUE;
         break;

    case WAIT_COT_REPORTS_AND_CRA:
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

        __ISUP_StopCPCToCCO(cic_rec,config_info);

        /* Call retry indication     */
        indId = ITS_ISUP_RSC_CRMRETRY_RQIND;
        break;

    case WAIT_COT_REPORTS_HAVE_CRA:
        __ISUP_StopCPCToCCO(cic_rec,config_info);

        /* Call retry indication     */
        indId = ITS_ISUP_RSC_CRMRETRY_RQIND;

        break;

    case WAIT_INCOMING_CRA:
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

        /* Call retry indication     */
        indId = ITS_ISUP_RSC_CRMRETRY_RQIND;

        break;

    case WAIT_INCOMING_IAM:
        /* FIXME: not there in Specs */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

        break;

    case WAIT_INCOMING_COT_AND_IAM:
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
           __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }

        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

        break;

    case WAIT_CONTINUITY_REPORT :
        if(__ISUP_StopCPCToCCO(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);
            indId = ITS_ISUP_RSC_REATTEMPT_RQIND;
        }
        break;
    case WAIT_INCOMING_COT :
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);

            /* Incoming release request */
        }
        break;
    case WAIT_INCOMING_ACM :
         /* T7 stop */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Send Reset Re-attempt indication */
         indId = ITS_ISUP_RSC_REATTEMPT_RQIND;

         break;

    case WAIT_OUTGOING_IAM :
    case WAIT_INCOMING_ANM :
         /* Outgoing Release Req.*/

         break;

    case RCVD_INCOMING_ANM :
         break;

    case WAIT_INCOMING_RLC :
         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         break;

    case WAIT_OUTGOING_ACM :
         /* FIXME:
          * if (pre-ACM Connect) ? Y/N
          * Release Network Path
          */

         /* Incoming Release Req.*/

         break;

    case WAIT_OUTGOING_ANM :
         /* Release Network Path */

         /* Incoming Release Req.*/

         break;

    case SENT_OUTGOING_ANM :
         /* Charging office; Stop Charging, if (Y) */

         /* Release Network Path */

         /* Incoming Release Req.*/

         break;

    case WAIT_OUTGOING_RLC :
         break;

    case WAIT_INCOMING_RES :
         /* FIXME:
          * if (Controlling exchange == Y)
          * Stop T6 timer
          */

         /* Stop timers T6; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);

         /* Outgoing Release Req.*/

         break;

    case WAIT_OUTGOING_RES :
         /* FIXME:
          * if (Controlling exchange == Y)
          * Stop charging, if (Y)
          */

         /* Release Network Path */

         break;

    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
        break;
    default:
         ret  = ITS_FALSE;
         break;
    }

    /* Send Indication to Application */
    SPRC_SendIndToApp_ANSI(indId, cic_rec);

    /* Idle CPC state & Set fsm_state to IDLE */
    ISUP_ClearCic(cic_rec);

    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_StopCRRToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cro_state)
    {
    case CRO_IDLE :
        break;
    case CRO_WAIT_TIMER_EXPIRY :
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_OUTGOING_CCR :
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_COT :
        if (cic_rec->dco_state == DCO_IDLE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        }
        else
        {
            __ISUP_StopCROToDCO(cic_rec,config_info);
        }
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);

        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
        break;

    default :
        /* TODO add Trace or Alarm */
        break;
    }
    cic_rec->cro_state = CRO_IDLE;
    cic_rec->dco_state = DCO_IDLE;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_StopCRRToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_StopCPCToCRI(cic_rec, config_info);

    ISUP_ClearCic(cic_rec);

    return;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StartCPCToCRO (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_FALSE;
    int         tret;

    switch (cic_rec->cro_state)
    {
    case CRO_IDLE:
    case CRO_WAIT_FOR_COT:
         if (cic_rec->cot_first_ind == ITS_TRUE)
         {
             tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T25,
                             config_info->
                             tmr_hndl_info[ITS_ISUP_TIMER_T25].tmr_value);
             if (tret != ITS_SUCCESS)
             {
                 ISUP_ERROR(("Failed to start T25 pcic 0x%08x, vcic %d.\n",
                              cic_rec->pcic, cic_rec->vcic));
             }
         }
         else
         {
             ISUP_CRITICAL(("COT check failed on CIC :"
                  "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

              tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T26,
                              config_info->
                              tmr_hndl_info[ITS_ISUP_TIMER_T26].tmr_value);
              if (tret != ITS_SUCCESS)
              {
                 ISUP_ERROR(("Failed to start T26 pcic 0x%08x, vcic %d.\n",
                              cic_rec->pcic, cic_rec->vcic));
              }

         }
         cic_rec->cro_state = CRO_WAIT_TIMER_EXPIRY;

         ret  = ITS_TRUE;
         break;

    case CRO_WAIT_TIMER_EXPIRY:
    case CRO_WAIT_FOR_OUTGOING_CCR :
    case CRO_WAIT_FOR_RLC:
         /*Ignore It*/
         ISUP_ERROR(("WAIT_COT_REPORTS_AND_CRA:Received COT in invalid"
                     "state pcic 0x%08x, vcic %d.\n",
                      cic_rec->pcic, cic_rec->vcic));
         break;
    default:
         break;
    }
    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopCPCToCRO (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret;

    switch (cic_rec->cro_state)
    {
    case CRO_WAIT_FOR_COT:

         __ISUP_StopCROToDCO (cic_rec, config_info);

         cic_rec->cro_state = CRO_IDLE;
         cic_rec->cot_first_ind = ITS_TRUE;

         ret  = ITS_TRUE;
         break;

    case CRO_WAIT_TIMER_EXPIRY:
         if (cic_rec->cot_first_ind == ITS_TRUE)
         {
             __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
         }
         else
         {
             __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
             cic_rec->cot_first_ind = ITS_TRUE;
         }

         cic_rec->cro_state = CRO_IDLE;

         ret  = ITS_TRUE;
         break;

    case CRO_WAIT_FOR_OUTGOING_CCR :
         cic_rec->cro_state = CRO_IDLE;

         ret  = ITS_TRUE;
         break;

    case CRO_IDLE:
    case CRO_WAIT_FOR_RLC:
    default:
         /*Ignore It*/
         ISUP_ERROR(("Received COT in invalid state pcic 0x%08x, vcic %d.\n",
                      cic_rec->pcic, cic_rec->vcic));

         ret  = ITS_FALSE;
         break;
    }

    return ret;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StartCPCToCCO (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret;
    int         tret;

    switch (cic_rec->cco_state)
    {
    case IDLE :

         /* Connect Transceiver
          * Disable Echo Control Device (if any)
          * start Sending Check tone
          */

         /* Start OGC COT timer T24 */
         /* Start Timer T24 */
         tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T24,
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T24].tmr_value);
         if (tret != ITS_SUCCESS)
         {
             ISUP_ERROR(("IDLE IAM: Failed to start T24"
                 ". pcic 0x%08x, vcic %d.\n",cic_rec->pcic, cic_rec->vcic));
         }
         cic_rec->cco_state = CCO_WAIT_COT_REPORT;

         ret  = ITS_TRUE;
         break;

    case CCO_WAIT_COT_REPORT:
    default :
         ret  = ITS_FALSE;
         break;
    }

    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StartCPCToCCI (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret;

    switch (cic_rec->cco_state)
    {
    case CCI_IDLE :
         /*Change CCI state to Wait for COT*/
         cic_rec->cci_state = CCI_WAIT_FOR_COT;
         ret = ITS_TRUE;
         break;

    case CCI_WAIT_FOR_COT:
    default:
         ret = ITS_FALSE;
         break;
     }
     return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StartCPCToCRI (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret;
    int tret=0;

    switch (cic_rec->cri_state)
    {
    case CRI_IDLE :
         tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TCCRR,
                          config_info->
                          tmr_hndl_info[ITS_ISUP_TIMER_TCCRR].tmr_value);
         if (tret != ITS_SUCCESS)
         {
             ISUP_ERROR(("Failed to start TCCRR. pcic 0x%08x, vcic %d.\n", 
                          cic_rec->pcic, cic_rec->vcic));
         }
         cic_rec->cri_state = CRI_WAIT_FOR_CCR;

         ret = ITS_TRUE;
         break;

    case CRI_WAIT_FOR_REL:
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T34);

         __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T27,
                          config_info->
                          tmr_hndl_info[ITS_ISUP_TIMER_T27].tmr_value);

         if (cic_rec->cot_first_ind == ITS_TRUE)
         {
             cic_rec->cot_first_ind = ITS_FALSE;
         }

         cic_rec->cri_state = CRI_WAIT_FOR_CCR;

         ret = ITS_TRUE;
         break;

    case CRI_WAIT_FOR_CCR:
    case CRI_WAIT_FOR_LPA:
    default:
         ret = ITS_FALSE;
         break;
     }
     return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopCPCToCRI (ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret;

    switch (cic_rec->cri_state)
    {
    case CRI_WAIT_FOR_CCR:
         if(cic_rec->cot_first_ind == ITS_TRUE)
         {
             __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_TCCRR);
         }
         else
         {
             __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T27);
             cic_rec->cot_first_ind = ITS_TRUE;
         }

         cic_rec->cri_state = CRI_IDLE;
         ret = ITS_TRUE;
         break;

    case CRI_WAIT_FOR_REL:
         __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T34);
         cic_rec->cri_state = CRI_IDLE;
         cic_rec->cot_first_ind = ITS_TRUE;
         ret = ITS_TRUE;
         break;

    case CRI_WAIT_FOR_LPA:
         cic_rec->cri_state = CRI_IDLE;
         cic_rec->cot_first_ind = ITS_TRUE;
         ret = ITS_TRUE;
         break;

    case CRI_IDLE :
    default:
         ret = ITS_FALSE;
         break;
     }
     return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from one isup module to another.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_BlockingCRRToBLS(ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->bls_state)
    {
        case BLS_IDLE:
            /* send BLO to L3 */
            SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);
    
            /* Start BLO Timers */
            __ISUP_StartBLOTimers(cic_rec, config_info);

            /* change state to Wait for BLA */
            cic_rec->bls_state = BLS_WAIT_FOR_BLA;

            break;

        case BLS_WAIT_FOR_BLA:
            /* send BLO to L3 */
            SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);

            /* This is not in SDL */
            __ISUP_StopBLOTimers(cic_rec, config_info);

            /* Start BLO Timers */
            __ISUP_StartBLOTimers(cic_rec, config_info);

            /* No change of state */

            break;

        case BLS_WAIT_FOR_UBA:
             /* Remove Remote Blocking */
   
             /* Stop UBA TImers, T14 and T15 */

             /* change bls state to Idle */

             break;
        default:
            /* TODO add Trace or Alarm */
            break;
    }

    return ITS_TRUE;
}

/*
 * UCIC Procedures
 */

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for ResetUCICToCPC is done here
 *
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
__ISUP_ResetUCICToCPC(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ISUP_DEBUG(("__ISUP_Received_UCIC "));
    switch (cic_rec->fsm_state)
    {
        case IDLE:
            break;

        case WAIT_COT_REPORTS_AND_CRA:
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

            __ISUP_StopCPCToCCO(cic_rec,config_info);

            /* Retry to app */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_UCIC_CRMRETRY_RQIND, cic_rec);

            /* Idle Ckt and fsm_state to Idle */
            ISUP_ClearCic(cic_rec);
            break;

       case WAIT_COT_REPORTS_HAVE_CRA:
            __ISUP_StopCPCToCCO(cic_rec,config_info);

            /* Retry to app */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_UCIC_CRMRETRY_RQIND, cic_rec);

            /* Idle Ckt and fsm_state to Idle */
            ISUP_ClearCic(cic_rec);
            break;

       case WAIT_INCOMING_CRA:
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);
            /* Retry to app */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_UCIC_CRMRETRY_RQIND, cic_rec);

            /* Idle Ckt and fsm_state to Idle */
            ISUP_ClearCic(cic_rec);
            break;

       case WAIT_INCOMING_IAM:
            /* FIXME: not there in Specs */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

            /* Idle Ckt and fsm_state to Idle */
            ISUP_ClearCic(cic_rec);

            break;

       case WAIT_INCOMING_COT_AND_IAM:
        case WAIT_OUTGOING_IAM:
            /* Won't come here; UCIC is unexpected in this state */
            break;

       case WAIT_CONTINUITY_REPORT :
            if (__ISUP_StopCPCToCCO(cic_rec,config_info))
            {
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

                SPRC_SendIndToApp_ANSI(ITS_ISUP_UCIC_REATTEMPT_RQIND, cic_rec);
                ISUP_ClearCic(cic_rec);
            }
            break;

       case WAIT_INCOMING_COT :
            break;

       case WAIT_INCOMING_ACM:
            /* Stop ACM Timer T7 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

            /* Retry to app */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_UCIC_REATTEMPT_RQIND, cic_rec);

            /* Idle Ckt and fsm_state to Idle */
            ISUP_ClearCic(cic_rec);

            break;

        case WAIT_INCOMING_ANM:
            break;

        case RCVD_INCOMING_ANM:
            break;

        case WAIT_INCOMING_RLC:
            /* Stop Timer T5 and T1 */
            __ISUP_StopRELTimers(cic_rec, config_info);

            /* Indication to app */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_UCIC_CPCIDLE_STIND, cic_rec);

            /* Idle the circuit and fsm_state to Idle */
            ISUP_ClearCic(cic_rec);

            break;

        case WAIT_INCOMING_RES:
            break;

        case WAIT_OUTGOING_ACM:
            break;

        case WAIT_OUTGOING_ANM:
            break;

        case SENT_OUTGOING_ANM:
            break;

        case WAIT_OUTGOING_RLC:
            break;

        case WAIT_OUTGOING_RES:
            break;

        case WAIT_OUTGOING_REL:
            break;

        case WAIT_OUTGOING_RSC:
            break;

        case WAIT_OUTGOING_GRA:
            break;
        default:
            ISUP_ERROR(("__ISUP_ResetUCICToCPC(): Invalid State  0x%x "
                        "pcic 0x%08x, vcic 0x%x.\n",
                        cic_rec->fsm_state, cic_rec->pcic, cic_rec->vcic));
            break;
    }
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopUCICToCRS is done here
 *
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
__ISUP_StopUCICToCRS(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->crs_state)
    {
        case CRS_IDLE:
            break;

        case CRS_WAIT_FOR_RELEASE:
            /* Stop RSC Timers T16 and T17 */
            __ISUP_StopRSCTimers(cic_rec, config_info);

            /* Stop Repeat RSC timer also */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T98);

            /* FIXME:
             * check if Alert Indicator is On/Off
             * If on, alert maintenance else do not alert
             */
            SPRC_SendIndToApp_ANSI(ITS_ISUP_UCIC_MAINT_RQIND, cic_rec);

            ISUP_Alarm_ANSI(3062, __FILE__, __LINE__, "cic: %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

            /* Idle the circuit */
            ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

            /* cic crs state to Idle */
            cic_rec->crs_state = CRS_IDLE;

            break;

        default:
            ISUP_ERROR(("__ISUP_StopUCICToCRS(): Invalid State  0x%x "
                        "pcic 0x%08x, vcic 0x%x.\n",
                        cic_rec->crs_state, cic_rec->pcic, cic_rec->vcic));
            break;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopUCICToCGRS is done here
 *
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
__ISUP_StopUCICToCGRS(ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cgrs_state)
    {
        case CGRS_IDLE:
        case CGRS_WAIT_FOR_GRA:
            __ISUP_StopWaitingCGRS(cic_rec, config_info); 

            break;

        default:
            ISUP_ERROR(("__ISUP_StopUCICToCGRS(): Invalid State  0x%x "
                        "pcic 0x%08x, vcic 0x%x.\n",
                        cic_rec->cgrs_state, cic_rec->pcic, cic_rec->vcic));
            break;
    }

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopUCICToCRO is done here
 *
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_StopUCICToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cro_state)
    {
    case CRO_WAIT_TIMER_EXPIRY :
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
        }
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_OUTGOING_CCR :
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_COT :
        if (cic_rec->dco_state == DCO_IDLE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        }
        else
        {
            __ISUP_StopCROToDCO(cic_rec,config_info);
        }
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_IDLE :
        break;

    default :
        /* TODO add Trace or Alarm */
        break;
    }
    cic_rec->cro_state = CRO_IDLE;
    cic_rec->cot_first_ind = ITS_TRUE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopUCICToBLS is done here
 *
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
__ISUP_StopUCICToBLS(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{

    switch (cic_rec->bls_state)
    {
        case BLS_IDLE:
            break;

        case BLS_WAIT_FOR_BLA:
            /* stop T12 and T13 Timers */
            __ISUP_StopBLOTimers(cic_rec, config_info);

            /* change state to Idle */
            cic_rec->bls_state = BLS_IDLE;
            break;

        case BLS_WAIT_FOR_UBA:
            /* stop T14 and T15 Timers */
            __ISUP_StopUBLTimers(cic_rec, config_info);

            /* change state to Idle */
            cic_rec->bls_state = BLS_IDLE;
            break;

        default:
            ISUP_ERROR(("__ISUP_StopUCICToBLS(): Invalid State  0x%x "
                        "pcic 0x%08x, vcic 0x%x.\n",
                        cic_rec->cgrs_state, cic_rec->pcic, cic_rec->vcic));
            break;
    }

}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopUCICToGBUS is done here
 *
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
__ISUP_StopUCICToGBUS(ISUP_CIC_INFO *cic_rec,
                      ISUP_OPC_DPC_INFO *config_info)
{

    /* FIXME:
     * No implementation found in SDLs
     * Need to study more and implement
     */
    switch (cic_rec->mgbs_state)
    {
        case MGBS_IDLE:
            break;

        case MGBS_WAIT_FOR_CGBA:
            /* stop T18/T19 timers */
            __ISUP_StopCGBTimers(cic_rec, config_info);

            cic_rec->mgbs_state = MGBS_IDLE;
            break;

        case MGBS_WAIT_FOR_CGUA:
            /* stop T20/T21 timers */
            __ISUP_StopCGUTimers(cic_rec, config_info);

            cic_rec->mgbs_state = MGBS_IDLE;
            break;

        default:
            ISUP_ERROR(("__ISUP_StopUCICToCGRS(): Invalid State  0x%x "
                        "pcic 0x%08x, vcic 0x%x.\n",
                        cic_rec->cgrs_state, cic_rec->pcic, cic_rec->vcic));
            break;
    }
}

/*
 * Blocking BLR to CPC
 */

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from BLR to CPC.
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_BlockingBLRToCPC(ISUP_CIC_INFO *cic_rec, 
                       ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_TRUE;

    switch (cic_rec->fsm_state)
    {
    case IDLE :
         break;

    case WAIT_COT_REPORTS_AND_CRA:
    case WAIT_INCOMING_CRA:
         /*Stop TCRM timer */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);

         /*Send a Re-attempt indication to the application */
         SPRC_SendIndToApp_ANSI(ITS_ISUP_AUTOREL_CRMRETRY_RQIND, cic_rec);

         __ISUP_StopCPCToCCO(cic_rec,config_info);

         __ISUP_StartRELTimers(cic_rec, config_info);

         SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NORMAL_UNSPECIFIED,
                                             cic_rec,config_info);
         cic_rec->fsm_state = WAIT_INCOMING_RLC;

         break;

    case WAIT_COT_REPORTS_HAVE_CRA:
    case WAIT_INCOMING_COT_AND_IAM:
    case WAIT_INCOMING_IAM:
    case WAIT_OUTGOING_IAM:
        /* Ignore and no change of fsm_state */
         break;

    case WAIT_CONTINUITY_REPORT :

        SPRC_SendIndToApp_ANSI(ITS_ISUP_REL_REATTEMPT_IND,cic_rec);

        if(__ISUP_StopCPCToCCO(cic_rec,config_info))
        {
            /*Stop T7 timer */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

            /* Removed as we don't keep Ckt in transient
             * ISUP_CIC_SET_TRANSIENT(cic_rec->cic_state);
             */

            __ISUP_StartRELTimers(cic_rec, config_info);

            SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NORMAL_UNSPECIFIED,
                                                cic_rec,config_info);

            cic_rec->fsm_state = WAIT_INCOMING_RLC;
        }
        break;
    case WAIT_INCOMING_COT :
        /*Ignore */
        break;
    case WAIT_INCOMING_ACM :
         /* Send REATTEMPT indic to app */
         SPRC_SendIndToApp_ANSI(ITS_ISUP_REL_REATTEMPT_IND, cic_rec);

         /* Stop timer T7 */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Send REL to L3 */
         SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NORMAL_UNSPECIFIED,
                                 cic_rec, config_info);

         /* Start T5 and T1 */
         __ISUP_StartRELTimers(cic_rec, config_info);

         /* Change state to WAIT_INCOMING_RLC */
         cic_rec->fsm_state = WAIT_INCOMING_RLC;

         break;

    case WAIT_INCOMING_ANM :
        /* Ignore and no change of fsm_state */
    case RCVD_INCOMING_ANM :
        /* Ignore and no change of fsm_state */
    case WAIT_INCOMING_RES :
        /* Ignore and no change of fsm_state */
    case WAIT_INCOMING_RLC :
    case WAIT_OUTGOING_ACM :
        /* Ignore and no change of fsm_state */
    case WAIT_OUTGOING_ANM :
        /* Ignore and no change of fsm_state */
    case SENT_OUTGOING_ANM :
        /* Ignore and no change of fsm_state */
    case WAIT_OUTGOING_RLC :
    case WAIT_OUTGOING_RES :
        /* Ignore and no change of fsm_state */
    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
        break;
    default:
         /* Ignore the message */
         ret  = ITS_FALSE;
         break;
    }
    return ret;
}

/*
 * REL procedures
 * This will be called from many other sate machines
 */

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for a REL request from App in any state is done here.
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
__ISUP_StartRELProcedure(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* store the REL message in cic rec */
    memcpy(cic_rec->cpc_msg, msg->data, msg->len);
    cic_rec->cpc_msg_len = msg->len;

    /* Send REL to SPRC */
    SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

    /* Start T5 and T1 */
    __ISUP_StartRELTimers(cic_rec, config_info);

    /* Change fsm state to WAIT_INCOMING_RLC */
    cic_rec->fsm_state = WAIT_INCOMING_RLC;

    return;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCGRRToCRO is done here
 *
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_StopCGRRToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cro_state)
    {
    case CRO_WAIT_TIMER_EXPIRY :
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_OUTGOING_CCR :
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_COT :
        if (cic_rec->dco_state == DCO_IDLE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        }
        else
        {
            __ISUP_StopCROToDCO(cic_rec,config_info);
        }
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_IDLE :
        break;

    default :
        /* TODO add Trace or Alarm */
        break;
    }
    cic_rec->cro_state = CRO_IDLE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCGRSToCRO is done here
 *
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_StopCGRSToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cro_state)
    {
    case CRO_WAIT_TIMER_EXPIRY :
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_WAIT_FOR_OUTGOING_CCR :
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_WAIT_FOR_COT :
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
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_IDLE :
        break;

    default :
        /* TODO add Trace or Alarm */
        break;
    }
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCGRRToCRI is done here
 *
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
__ISUP_StopCGRRToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCCRR);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        ISUP_ClearCic(cic_rec);
    }
    else if (cic_rec->cri_state == CRI_WAIT_FOR_REL ||
                     cic_rec->cri_state == CRI_WAIT_FOR_LPA)
    {

        if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T34);
        }
        cic_rec->cot_first_ind = ITS_TRUE;
       /* remove loop
       - Enable echo suppressor, if any */
        ISUP_ClearCic(cic_rec);

    }
    cic_rec->cri_state = CRI_IDLE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCGRSToCRI is done here
 *
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
__ISUP_StopCGRSToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCCRR);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
        }
        cic_rec->fsm_state = IDLE;
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
    }
    else if (cic_rec->cri_state == CRI_WAIT_FOR_REL ||
                     cic_rec->cri_state == CRI_WAIT_FOR_LPA)
    {
        if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T34);
        }
       /* remove loop
       - Enable echo suppressor, if any */
        cic_rec->fsm_state = IDLE;
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
    }
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopBLRToCRI is done here
 *
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
__ISUP_StopBLRToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCCRR);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        ISUP_ClearCic(cic_rec);
    }
    else if (cic_rec->cri_state == CRI_WAIT_FOR_REL ||
                     cic_rec->cri_state == CRI_WAIT_FOR_LPA)
    {
        if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T34);
        }
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);

       /* remove loop
       - Enable echo suppressor, if any */
    }
    /* Idle the Ckt*/
    cic_rec->cri_state = CRI_IDLE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopBLSToCRI is done here
 *
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
__ISUP_StopBLSToCRI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCCRR);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T27);
        }
        cic_rec->fsm_state = IDLE;
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
    }
    else if (cic_rec->cri_state == CRI_WAIT_FOR_REL ||
                     cic_rec->cri_state == CRI_WAIT_FOR_LPA)
    {

        if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
        {
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T34);
        }
       /* remove loop
       - Enable echo suppressor, if any */
        cic_rec->fsm_state = IDLE;
        cic_rec->cri_state = CRI_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopBLRToCRO is done here
 *
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_StopBLRToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cro_state)
    {
    case CRO_WAIT_TIMER_EXPIRY :
        if (cic_rec->cot_first_ind == ITS_TRUE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T25);
        }
        else
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T26);
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_OUTGOING_CCR :
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_COT :
        if (cic_rec->dco_state == DCO_IDLE)
        {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
        }
        else
        {
            __ISUP_StopCROToDCO(cic_rec,config_info);
        }
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
        cic_rec->cot_first_ind = ITS_TRUE;
        ISUP_ClearCic(cic_rec);
        break;

    case CRO_IDLE :
        break;
    default :
        /* TODO add Trace or Alarm */
        break;
    }
    cic_rec->cro_state = CRO_IDLE;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopBLSToCRO is done here
 *
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_StopBLSToCRO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    switch (cic_rec->cro_state)
    {
    case CRO_WAIT_TIMER_EXPIRY :
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
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_WAIT_FOR_OUTGOING_CCR :
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_WAIT_FOR_COT :
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
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_WAIT_FOR_RLC :
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
        cic_rec->cro_state = CRO_IDLE;
        cic_rec->cot_first_ind = ITS_TRUE;
        cic_rec->fsm_state = IDLE;
        break;

    case CRO_IDLE :
        break;
    default :
        /* TODO add Trace or Alarm */
        break;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCPCToCCO is done here
 *
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
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopCPCToCCO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret;

    switch (cic_rec->cco_state)
    {
    case CCO_WAIT_COT_REPORT:
         /* Stop OGC COT timer T24; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);

         /* Stop sending Check Tone */

         /* Remove Transceiver
          * Enable Echo Control Device (if any)
          */

         cic_rec->cco_state = CCO_IDLE;

         ret  = ITS_TRUE;
         break;

    case CCO_IDLE :
    default :
         ret  = ITS_FALSE;
         break;
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCPCToCCI is done here
 *
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
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_StopCPCToCCI(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret;

    switch (cic_rec->cci_state)
    {
    case CCI_WAIT_FOR_COT:
         /*Change CCI state to Wait for COT*/
         cic_rec->cci_state = CCI_IDLE;
         ret = ITS_TRUE;
         break;

    case CCI_IDLE :
    default:
         ret = ITS_FALSE;
         break;
     }
     return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The processing for StopCROToDCO is done here
 *
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
__ISUP_StopCROToDCO(ISUP_CIC_INFO *cic_rec,
                     ISUP_OPC_DPC_INFO *config_info)
{
    if (cic_rec->dco_state == DCO_WAIT_FOR_LPA)
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCCR);
        cic_rec->dco_state = DCO_IDLE;
    }
    else
    {
        /* DCO IDLE tate is IDLE as LPA received *
         * but was still waiting for COT rep.
         */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
    }
}
/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from CQS to CPC
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
static ITS_BOOLEAN
__ISUP_ResetCQSToCPC(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_TRUE;
    ITS_UINT indId = ITS_ISUP_RSC_CPCIDLE_STIND;

    switch (cic_rec->fsm_state)
    {
    case IDLE :
         return ret;
         break;

    case WAIT_COT_REPORTS_AND_CRA:
        /* FIXME: Not maintion in SDL */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);
        __ISUP_StopCPCToCCO(cic_rec,config_info);

        /* Call retry indication     */
        indId = ITS_ISUP_RSC_CRMRETRY_RQIND;
        break;

    case WAIT_COT_REPORTS_HAVE_CRA:
        __ISUP_StopCPCToCCO(cic_rec,config_info);

        /* Call retry indication     */
        indId = ITS_ISUP_RSC_CRMRETRY_RQIND;
        break;

    case WAIT_INCOMING_CRA:
        /* FIXME: Not given in SDL !! */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);
        break;

    case WAIT_INCOMING_IAM:
        /* FIXME: Not given in SDL !! */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);

        break;

    case WAIT_INCOMING_COT_AND_IAM:
        if(__ISUP_StopCPCToCCI(cic_rec,config_info))
        {
           __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
        }
        break;

    case WAIT_INCOMING_ACM :
         /* T7 stop */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T7);

         /* Set Reset Re-attempt indication */
         indId = ITS_ISUP_RSC_REATTEMPT_RQIND;

         break;

    case WAIT_OUTGOING_IAM :
    case WAIT_INCOMING_ANM :
    case RCVD_INCOMING_ANM :
         /* Outgoing Release Req.*/

         break;

    case WAIT_INCOMING_RLC :
         /* T5 and T1 stop */
         __ISUP_StopRELTimers(cic_rec, config_info);

         break;

    case WAIT_OUTGOING_ACM :
         /* FIXME:
          * if (pre-ACM Connect) ? Y/N
          * Release Network Path
          */

         /* Incoming Release Req.*/

         break;

    case WAIT_OUTGOING_ANM :
         /* Release Network Path */

         /* Incoming Release Req.*/

         break;

    case SENT_OUTGOING_ANM :
         /* Charging office; Stop Charging, if (Y) */

         /* Release Network Path */

         /* Incoming Release Req.*/

         break;

    case WAIT_OUTGOING_RLC :

         break;

    case WAIT_INCOMING_RES :
         /* FIXME:
          * if (Controlling exchange == Y)
          * Stop T6 timer
          */

         /* Stop timers T6; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);

         /* Outgoing Release Req.*/

         break;

    case WAIT_OUTGOING_RES :
         /* FIXME:
          * if (Controlling exchange == Y)
          * Stop charging, if (Y)
          */

         /* Release Network Path */

         break;

    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :
    default:
         ret  = ITS_FALSE;
         return ret;
         break;
    }

    /* Send Indication to Application */
    SPRC_SendIndToApp_ANSI(indId, cic_rec);

    /* Idle CPC state & Set fsm_state to IDLE */
    ISUP_ClearCic(cic_rec);

    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from CQS to CPC
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
static ITS_BOOLEAN
__ISUP_ReleaseCQSToCPC(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_TRUE;
    ITS_UINT indId = ITS_ISUP_CQR_RELEASED_STIND;

    switch (cic_rec->fsm_state)
    {
    case IDLE :
          break;

    case WAIT_COT_REPORTS_AND_CRA:
         /* FIXME: SDL doesn't say anything about this action */
         /* Outgoing call failure */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);
         __ISUP_StopCPCToCCO(cic_rec,config_info);

         /* Call reattempt indication */
         indId = ITS_ISUP_AUTOREL_CRMRETRY_RQIND;
         break;

    case WAIT_COT_REPORTS_HAVE_CRA:
          __ISUP_StopCPCToCCO(cic_rec,config_info);

          /* Call reattempt indication */
          indId = ITS_ISUP_AUTOREL_CRMRETRY_RQIND;
          break;

    case WAIT_INCOMING_CRA:
         /* FIXME: SDL doesn't say anything about this action */
         /* Outgoing call failure */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRM);
         break;

    case WAIT_INCOMING_IAM:
        /* FIXME: SDL doesn't say anything about this action */
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_TCRA);
         break;

    case WAIT_INCOMING_COT_AND_IAM:
         if(__ISUP_StopCPCToCCI(cic_rec,config_info))
         {
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T8);
         }
         break;

    case WAIT_INCOMING_ACM :
    case WAIT_INCOMING_RLC :
         /* Chech if it is right ??? */
         break;

    case WAIT_OUTGOING_IAM :
    case WAIT_INCOMING_ANM :
         /* OGC failure with cause */
         indId = ITS_ISUP_CALL_FAILURE_IND;

    case RCVD_INCOMING_ANM :
         /* Outgoing Release Req.*/

         break;

    case WAIT_OUTGOING_ACM :
         /* Incoming Release Req.*/

         /* FIXME:
          * if (pre-ACM Connect) ? Y/N
          * Release Network Path
          */

         break;

    case WAIT_OUTGOING_ANM :
         /* Incoming Release Req.*/

         /* Release Network Path */

         break;

    case SENT_OUTGOING_ANM :
         /* Incoming Release Req.*/

         /* Charging office; Stop Charging, if (Y) */

         /* Release Network Path */

         break;

    case WAIT_OUTGOING_RLC :

         break;

    case WAIT_INCOMING_RES :
         /* FIXME:
          * if (Controlling exchange == Y)
          * Stop T6 timer
          */

         /* Stop timers T6; if running */
         __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T6);

         /* Outgoing Release Req.*/

         break;

    case WAIT_OUTGOING_RES :
         /* Incoming Release Req.*/

         /* FIXME:
          * if (Controlling exchange == Y)
          * Stop charging, if (Y)
          */

         /* Release Network Path */

         break;

    case WAIT_OUTGOING_REL :
    case WAIT_OUTGOING_RSC :

         break;

    default:
         ret  = ITS_FALSE;
         break;
    }

    /* Send Indication to Application */
    SPRC_SendIndToApp_ANSI(indId, cic_rec);

    /* Send Release to L3 */
    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR,
                            cic_rec, config_info);

    /* Start T5 and T1 */
    __ISUP_StartRELTimers(cic_rec, config_info);

    /* Change state to WAIT_INCOMING_RLC */
    cic_rec->fsm_state = WAIT_INCOMING_RLC;

    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from CQS to BLS
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITS_BOOLEAN
__ISUP_BlockingCQSToBLS(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_TRUE;

    /* send BLO to L3 */
    SPRC_SendBLOToMTP3_ANSI(cic_rec, config_info);

    /* Start BLO Timers */
    __ISUP_StartBLOTimers(cic_rec, config_info);

    /* Change state to Wait for BLA */
    cic_rec->bls_state = BLS_WAIT_FOR_BLA;

    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Process the trigger from CQS to BLS
 *
 *  Input Parameters:
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITS_BOOLEAN
__ISUP_UnblockingCQSToBLS(ISUP_CIC_INFO *cic_rec, 
                     ISUP_OPC_DPC_INFO *config_info)
{
    ITS_BOOLEAN ret = ITS_TRUE;

    /* send BLO to L3 */
    SPRC_SendUBLToMTP3_ANSI(cic_rec, config_info);

    /* Start BLO Timers */
    __ISUP_StartUBLTimers(cic_rec, config_info);

    /* change state to Wait for BLA */
    cic_rec->bls_state = BLS_WAIT_FOR_UBA;

    return ret;
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      msg    : ITS event
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *      sup_msg_type: Unblocking type
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_UpdateNearEndCktState(ITS_EVENT *msg,
                             ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info)
{
    int                    i, ret;
    ITS_ISUP_IE            rs_ie;
    ITS_OCTET              sup_msg_type;

    ISUP_PCIC              pcic;
    ITS_UINT               opc, dpc;
    ITS_OCTET              ni;

    ISUP_CIC_INFO         *affected_cic_rec;

    ITS_USHORT             cic = 0;
    ITS_OCTET              far_end_state;
    ITS_OCTET              ckt_status[32];

    __ISUP_Validate_RangeStatus(msg, cic_rec, config_info, &rs_ie,
                                &sup_msg_type, &cic);

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    for (i= 0; i <=rs_ie.param_data.rangeAndStatus.range; i++)
    {
        if (i == 0)
        {
            affected_cic_rec = cic_rec;
        }
        else
        {
            opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
            dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
            ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

            ISUP_PCICFromParts(&pcic, opc, dpc, ni, (ITS_USHORT)(cic + i));
            affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
        }

        if (affected_cic_rec == NULL)
        {
            ISUP_ERROR(("Could not find PCIC\n"));
        }
        else
        {
            memset((char *)ckt_status, 0, 32);

            ret = __ISUP_GetCQRCICStatus(msg, cic_rec, config_info,
                                         ckt_status, &cic);

            far_end_state = ckt_status[i];

            __ISUP_UpdateCktStatus(affected_cic_rec,
                                   config_info,
                                   far_end_state);

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) != 
                ISUP_PCIC_TO_CIC(cic_rec->pcic))
            {
                ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
            }
        }
    }
    return ITS_TRUE;
}

/*.implementation: static
 ****************************************************************************
 *  Purpose:
 *      Extract Circuit Status from Status field of CQR
 *
 *  Input Parameters:
 *      msg    : ITS event
 *      cic_rec: pointer to cic record
 *      config_info: pointer to config info pertaining to the opc dpc pair
 *      sup_msg_type: Unblocking type
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
static int
__ISUP_GetCQRCICStatus(ITS_EVENT *msg,
                       ISUP_CIC_INFO *cic_rec,
                       ISUP_OPC_DPC_INFO *config_info,
                       ITS_OCTET *ckt_status,
                       ITS_USHORT *cic)
{
    int ret     = ITS_SUCCESS;
    int index   = 0;
    ITS_USHORT  paramlen = 0;
    ITS_ISUP_IE ies[3];
    int ieCount = 0;
    int         i;
    ITS_OCTET   range = 0;
    ITS_OCTET   cic_index;

    /* initialize local */
    memset((char *)ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* get cic from message: CIC is two bytes: LSB and MSB (4 bits) */
    cic_index = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_ANSI);

    *cic = (ITS_USHORT)((msg->data[cic_index + 1] << 8) + msg->data[cic_index]);

    paramlen = (ITS_USHORT)(msg->len - sizeof(ITS_OCTET) - sizeof(ITS_USHORT)
                       - sizeof(MTP3_HEADER_ANSI));

    index = msg->len - paramlen;

    /* Need to do a Decode as TLV style is not being used. */
    ret = ISUP_MTP3Decode_ANSI(&msg->data[index + 1],
                                paramlen,
                                msg->data[index],
                                ies, &ieCount,
                                config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_RANGE_STATUS)
        {
            range = ies[i].param_data.rangeAndStatus.range;
        }
        else if (ies[i].param_id == ISUP_PRM_CKT_STATE_INDICATOR)
        {
            memcpy(ckt_status, ies[i].param_data.circuitStateIndicators.states, range+1);
        }
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      msg    : ITS event
 *      cic_rec: pointer to cic record
 *      far_end_state: Far End Circuit State
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - success.
 *      ITS_FALSE - failure
 *
 ****************************************************************************/
static ITS_BOOLEAN
__ISUP_UpdateCktStatus(ISUP_CIC_INFO *cic_rec,
                       ISUP_OPC_DPC_INFO *config_info,
                       ITS_OCTET far_end_state)
{
    ITS_OCTET near_end_state = 0xFF;

    /* Query circuit status from SPRC */
    near_end_state = SPRC_QueryCircuitStatus(cic_rec);

    switch (near_end_state)
    {
        case SPRC_CKTS_TRANSIENT:
             /* Do Nothing */
             break;

        case SPRC_CKTS_UNEQUIPPED:
             /* Take appropriate action */
             __ISUP_NearEndStateUNEQ (cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_IDLE_ACTIVE:
             /* Take appropriate action */
             __ISUP_NearEndStateIdleActive(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_INBUSY_ACTIVE:
             /* Take appropriate action */
             __ISUP_NearEndStateInbusyActive(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_OUTBUSY_ACTIVE:
             /* Take appropriate action */
             __ISUP_NearEndStateOutbusyActive(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_IDLE_LBLOCKED:
             /* Take appropriate action */
             __ISUP_NearEndStateIdleLBlocked(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_INBUSY_LBLOCKED:
             /* Take appropriate action */
             __ISUP_NearEndStateInbusyLBlocked(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_OUTBUSY_LBLOCKED:
             /* Take appropriate action */
             __ISUP_NearEndStateOutbusyLBlocked(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_IDLE_RBLOCKED:
             /* Take appropriate action */
             __ISUP_NearEndStateIdleRBlocked(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_INBUSY_RBLOCKED:
             /* Take appropriate action */
             __ISUP_NearEndStateInbusyRBlocked(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_OUTBUSY_RBLOCKED:
             /* Take appropriate action */
             __ISUP_NearEndStateOutbusyRBlocked(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_IDLE_LRBLOCKED:
             /* Take appropriate action */
             __ISUP_NearEndStateIdleLRBlocked(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_INBUSY_LRBLOCKED:
             /* Take appropriate action */
             __ISUP_NearEndStateInbusyLRBlocked(cic_rec, config_info, far_end_state);
             break;

        case SPRC_CKTS_OUTBUSY_LRBLOCKED:
             /* Take appropriate action */
             __ISUP_NearEndStateOutbusyLRBlocked(cic_rec, config_info, far_end_state);
             break;

        default:
            return ITS_FALSE;
    }
    return ITS_TRUE;
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void
__ISUP_NearEndStateUNEQ (ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
              case SPRC_CKTS_UNEQUIPPED:
              case SPRC_CKTS_TRANSIENT:
              break;

              case SPRC_CKTS_IDLE_ACTIVE:
                   /* Send BLO to L3 */
                   __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                   break;

              case SPRC_CKTS_INBUSY_ACTIVE:
              case SPRC_CKTS_OUTBUSY_ACTIVE:
                   /* Send Release to L3 */
                   SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                           config_info);
                   /* Don't start the timer */

                   /* send BLO to L3 */
                   __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

              case SPRC_CKTS_IDLE_LBLOCKED:
              case SPRC_CKTS_IDLE_RBLOCKED:
              case SPRC_CKTS_IDLE_LRBLOCKED:
                   /* Do nothing */

                   break;

              case SPRC_CKTS_INBUSY_LBLOCKED:
              case SPRC_CKTS_OUTBUSY_LBLOCKED:
              case SPRC_CKTS_INBUSY_RBLOCKED:
              case SPRC_CKTS_OUTBUSY_RBLOCKED:
              case SPRC_CKTS_INBUSY_LRBLOCKED:
              case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                   /* Send Release to L3 */
                   SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                           config_info);

                   /* Don't start the timer */
                   break;
      } 
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void
__ISUP_NearEndStateIdleActive (ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_IDLE_ACTIVE:
                    break;

               case SPRC_CKTS_UNEQUIPPED:
                    /* Set local Block */
                    ISUP_CIC_SET_LOC_MAINT(cic_rec->cic_state);
                    cic_rec->bls_state = BLS_IDLE;

                    /* Alert maintenence*/
                    ISUP_Alarm_ANSI(3257, __FILE__, __LINE__, "cic : %x",
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_LBLOCKED_STIND, cic_rec);

                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
               case SPRC_CKTS_OUTBUSY_ACTIVE:
                    /* Send REL to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                            config_info);

                    /* Don't start the timer */
                    break;

               case SPRC_CKTS_IDLE_LBLOCKED:
                    /* Set remote block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    ISUP_Alarm_ANSI(3189, __FILE__, __LINE__, "cic : %x",
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));
                    break;

               case SPRC_CKTS_INBUSY_LBLOCKED:
               case SPRC_CKTS_OUTBUSY_LBLOCKED:
                    /* Send REL to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                            config_info);

                    /* Don't start the timer */

                    /* Set remote block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3190, __FILE__, __LINE__, "cic : %x",
                                       ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_RBLOCKED:
                    /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_RBLOCKED:
               case SPRC_CKTS_OUTBUSY_RBLOCKED:
                    /* Send REL to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                            config_info);

                    /* Don't start the timer */

                    /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_LRBLOCKED:
                    /* Set remote block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3191, __FILE__, __LINE__, "cic : %x",
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_LRBLOCKED:
               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    /* Send REL to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                            config_info);

                    /* Don't start the timer */

                    /* Set remote block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3191, __FILE__, __LINE__, "cic : %x",
                                                       cic_rec->pcic);

                    /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;
       }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void 
__ISUP_NearEndStateInbusyActive(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_OUTBUSY_ACTIVE:

                    break;

               case SPRC_CKTS_UNEQUIPPED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Set local Block */
                    ISUP_CIC_SET_LOC_MAINT(cic_rec->cic_state);

                    cic_rec->bls_state = BLS_IDLE;

                    /* Alert maintenance*/
                    ISUP_Alarm_ANSI(3258, __FILE__, __LINE__, "cic : %x",
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_LBLOCKED_STIND, cic_rec);

                    break;

               case SPRC_CKTS_IDLE_ACTIVE:
                    /* IDLE the Circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
                    /* REL the Circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_LBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3192, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_LBLOCKED:
                    /* REL the Circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3193, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_LBLOCKED:
                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3194, __FILE__, __LINE__, "cic : %x",
                                            ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_RBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_RBLOCKED:
                    /* REL the Circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_OUTBUSY_RBLOCKED:
                    /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_LRBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3195, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));
                   
                    /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_LRBLOCKED:
                    /* REL the Circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3196, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3197, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;
       }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void 
__ISUP_NearEndStateOutbusyActive(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
     switch (far_end_state)
     {
             case SPRC_CKTS_TRANSIENT:
             case SPRC_CKTS_INBUSY_ACTIVE:

                  break;

             case SPRC_CKTS_UNEQUIPPED:
                  /* IDLE the circuit */
                  __ISUP_ResetCQSToCPC (cic_rec, config_info);

                  /* Set Local Block */
                  ISUP_CIC_SET_LOC_MAINT(cic_rec->cic_state);

                  cic_rec->bls_state = BLS_IDLE;

                  /* Indication to App */
                  SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_LBLOCKED_STIND, cic_rec);

                  /* ANSI Alarm; Alert Maintenance */
                  ISUP_Alarm_ANSI(3198, __FILE__, __LINE__, "cic : %x",
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

                  break;

             case SPRC_CKTS_IDLE_ACTIVE:
                  /* IDLE the circuit */
                  __ISUP_ResetCQSToCPC (cic_rec, config_info);

                  break;

             case SPRC_CKTS_OUTBUSY_ACTIVE:
                  /* REL the Circuit */
                  __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                  break;

             case SPRC_CKTS_IDLE_LBLOCKED:
                  /* IDLE the circuit */
                  __ISUP_ResetCQSToCPC (cic_rec, config_info);

                  /* Set Remote Block */
                  ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                  cic_rec->blr_state = BLR_IDLE;

                  /* Indication to App */
                  SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                  /* ANSI Alarm; Alert Maintenance */
                  ISUP_Alarm_ANSI(3199, __FILE__, __LINE__, "cic : %x",
                                            ISUP_PCIC_TO_CIC(cic_rec->pcic));

                  break;

             case SPRC_CKTS_INBUSY_LBLOCKED:
                  /* Set Remote Block */
                  ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                  cic_rec->blr_state = BLR_IDLE;

                  /* Indication to App */
                  SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                  /* ANSI Alarm; Alert Maintenance */
                  ISUP_Alarm_ANSI(3200, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                  break;

             case SPRC_CKTS_OUTBUSY_LBLOCKED:
                  /* REL the Circuit */
                  __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                  /* Set Remote Block */
                  ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                  cic_rec->blr_state = BLR_IDLE;

                  /* Indication to App */
                  SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                  /* ANSI Alarm; Alert Maintenance */
                  ISUP_Alarm_ANSI(3201, __FILE__, __LINE__, "cic : %x",
                                      ISUP_PCIC_TO_CIC(cic_rec->pcic));

                  break;

             case SPRC_CKTS_IDLE_RBLOCKED:
                  /* IDLE the circuit */
                  __ISUP_ResetCQSToCPC (cic_rec, config_info);

                  /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                  break;

             case SPRC_CKTS_INBUSY_RBLOCKED:
                  /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                  break;

             case SPRC_CKTS_OUTBUSY_RBLOCKED:
                  /* REL the Circuit */
                  __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                  /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                  break;

             case SPRC_CKTS_IDLE_LRBLOCKED:
                  /* IDLE the circuit */
                  __ISUP_ResetCQSToCPC (cic_rec, config_info);

                  /* Set Remote Block */
                  ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                  cic_rec->blr_state = BLR_IDLE;

                  /* Indication to App */
                  SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                  /* ANSI Alarm; Alert Maintenance */
                  ISUP_Alarm_ANSI(3202, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                   /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                  break;

             case SPRC_CKTS_INBUSY_LRBLOCKED:
                  /* Set Remote Block */
                  ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                  cic_rec->blr_state = BLR_IDLE;

                  /* Indication to App */
                  SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                  /* ANSI Alarm; Alert Maintenance */
                  ISUP_Alarm_ANSI(3203, __FILE__, __LINE__, "cic : %x",
                                      ISUP_PCIC_TO_CIC(cic_rec->pcic));

                   /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                  break;

             case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                  /* REL the Circuit */
                  __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                  /* Set Remote Block */
                  ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                  cic_rec->blr_state = BLR_IDLE;

                  /* Indication to App */
                  SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                  /* ANSI Alarm; Alert Maintenance */
                  ISUP_Alarm_ANSI(3204, __FILE__, __LINE__, "cic : %x",
                                       ISUP_PCIC_TO_CIC(cic_rec->pcic));

                   /* Send UBL to L3 */
                   __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                  break;
     }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void 
__ISUP_NearEndStateIdleLBlocked(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_UNEQUIPPED:
               case SPRC_CKTS_IDLE_RBLOCKED:

                    break;

               case SPRC_CKTS_IDLE_ACTIVE:
                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
               case SPRC_CKTS_OUTBUSY_ACTIVE:
                    /* REL the Circuit */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                           config_info);

                    /* Do not start Timers*/

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_LBLOCKED:
                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3205, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_LBLOCKED:
               case SPRC_CKTS_OUTBUSY_LBLOCKED:
                    /* Send REL to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                           config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance;print */
                    ISUP_Alarm_ANSI(3206, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_RBLOCKED:
               case SPRC_CKTS_OUTBUSY_RBLOCKED:
                    /* Send REL to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                           config_info);

                    /* Do not start Timers*/

                    break;

               case SPRC_CKTS_IDLE_LRBLOCKED:
                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3207, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_LRBLOCKED:
               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    /* REL the circuit */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                           config_info);

                    /* Do not start Timers*/

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance; Print */
                    ISUP_Alarm_ANSI(3208, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;
       }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void 
__ISUP_NearEndStateInbusyLBlocked(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_OUTBUSY_RBLOCKED:

                    break;

               case SPRC_CKTS_UNEQUIPPED:
                    /* IDLE the Circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);
                    break;

               case SPRC_CKTS_IDLE_ACTIVE:
                    /* IDLE the Circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);
                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
                    /* REL the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_OUTBUSY_ACTIVE:
                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_LBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                   __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert maintenance */
                    ISUP_Alarm_ANSI(3209, __FILE__, __LINE__, "cic : %x",
                                     ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_LBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                   __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert maintenance */
                    ISUP_Alarm_ANSI(3210, __FILE__, __LINE__, "cic: %x",
                                            ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_LBLOCKED:
                    /* Send BLO to L3 */
                   __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert maintenance */
                    ISUP_Alarm_ANSI(3211, __FILE__, __LINE__, "cic : %x",
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_RBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_RBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_LRBLOCKED:
                    /* IDLE the Circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert maintenance */
                    ISUP_Alarm_ANSI(3212, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_LRBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert maintenance */
                    ISUP_Alarm_ANSI(3213, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    /* Set Remote Block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert maintenance */
                    ISUP_Alarm_ANSI(3214, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;
       }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void 
__ISUP_NearEndStateOutbusyLBlocked(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_INBUSY_RBLOCKED:

                    break;

               case SPRC_CKTS_UNEQUIPPED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_ACTIVE:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send BLO */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
                    /* Send BLO */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_OUTBUSY_ACTIVE:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_LBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Set remote block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);
 
                    cic_rec->blr_state = BLR_IDLE;

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3215, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    /* Send BLO */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_LBLOCKED:
                    /* Send BLO */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Set remote block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);
 
                    cic_rec->blr_state = BLR_IDLE;

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3216, __FILE__, __LINE__, "cic : %x",
                                     ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_LBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send BLO */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Set remote block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);
 
                    cic_rec->blr_state = BLR_IDLE;

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3217, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_RBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_OUTBUSY_RBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_LRBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Set remote block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);
 
                    cic_rec->blr_state = BLR_IDLE;

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3218, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_LRBLOCKED:
                    /* Set remote block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);
 
                    cic_rec->blr_state = BLR_IDLE;

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3219, __FILE__, __LINE__, "cic : %x",
                                   ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Set remote block */
                    ISUP_CIC_SET_REM_MAINT(cic_rec->cic_state);
 
                    cic_rec->blr_state = BLR_IDLE;

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3220, __FILE__, __LINE__, "cic : %x",
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;
       }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void 
__ISUP_NearEndStateIdleRBlocked(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_IDLE_LBLOCKED:

                    break;

               case SPRC_CKTS_UNEQUIPPED:
                    /* Set local Blocking */
                    ISUP_CIC_SET_MAINT(cic_rec->cic_state, CKTS_LBLOCKED);

                    cic_rec->bls_state = BLS_IDLE;

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_LBLOCKED_STIND, cic_rec);
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3221, __FILE__, __LINE__, "cic : %x",
                                                       cic_rec->pcic);
                    break;

               case SPRC_CKTS_IDLE_ACTIVE:
                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3221, __FILE__, __LINE__, "cic : %x",
                                      ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
               case SPRC_CKTS_OUTBUSY_ACTIVE:
                    /* Send REL to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                            config_info);

                    /* Don't start the timer */

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3222, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_LBLOCKED:
               case SPRC_CKTS_OUTBUSY_LBLOCKED:
                    /* Send REL to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                            config_info);

                    /* Don't start the timer */

                    break;

               case SPRC_CKTS_IDLE_RBLOCKED:

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3223, __FILE__, __LINE__, "cic : %x",
                                       ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_RBLOCKED:
               case SPRC_CKTS_OUTBUSY_RBLOCKED:
                    /* Send REL to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                            config_info);

                    /* Don't start the timer */

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3224, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_LRBLOCKED:
                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_LRBLOCKED:
               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    /* Send REL to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                            config_info);

                    /* Don't start the timer */

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;
       }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void 
__ISUP_NearEndStateInbusyRBlocked(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_OUTBUSY_LBLOCKED:

                    break;

               case SPRC_CKTS_UNEQUIPPED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Set local Blocking */
                    ISUP_CIC_SET_LOC_MAINT(cic_rec->cic_state);

                    cic_rec->bls_state = BLS_IDLE;

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indications to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_LBLOCKED_STIND, cic_rec);
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3225, __FILE__, __LINE__, "cic : %x",
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_ACTIVE:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indications to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3226, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indications to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3227, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_ACTIVE:
                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indications to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3228, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_LBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_LBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_RBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);                  
                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indications to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3229, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_RBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);            

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indications to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3230, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_RBLOCKED:
                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);                  
                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indications to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3231, __FILE__, __LINE__, "cic : %x",
                                            ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_LRBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);                  
                    break;

               case SPRC_CKTS_INBUSY_LRBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);                  
                    break;

               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);                  
                    break;
       }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void 
__ISUP_NearEndStateOutbusyRBlocked(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_INBUSY_LBLOCKED:

                    break;

               case SPRC_CKTS_UNEQUIPPED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Set local Blocking */
                    ISUP_CIC_SET_LOC_MAINT(cic_rec->cic_state);

                    cic_rec->bls_state = BLS_IDLE;

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_LBLOCKED_STIND, cic_rec);
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3232, __FILE__, __LINE__, "cic : %x",
                                       ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_ACTIVE:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3233, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3234, __FILE__, __LINE__, "cic : %x",
                                       ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_ACTIVE:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3235, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_LBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_OUTBUSY_LBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_RBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);            

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3236, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_RBLOCKED:
                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);            

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3237, __FILE__, __LINE__, "cic : %x",
                                       ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_RBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);            

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3238, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_LRBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_LRBLOCKED:
                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send UBL to L3 */
                    __ISUP_UnblockingCQSToBLS(cic_rec, config_info);

                    break;
       }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void 
__ISUP_NearEndStateIdleLRBlocked(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_IDLE_LRBLOCKED:
                    break;

               case SPRC_CKTS_UNEQUIPPED:
               case SPRC_CKTS_IDLE_RBLOCKED:
                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3239, __FILE__, __LINE__, "cic : %x",
                                          ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_ACTIVE:
                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3240, __FILE__, __LINE__, "cic : %x",
                                     ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
               case SPRC_CKTS_OUTBUSY_ACTIVE:
                    /* Send Release to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                           config_info);
                    /* Don't start the timer */

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3241, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_LBLOCKED:
                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_LBLOCKED:
               case SPRC_CKTS_OUTBUSY_LBLOCKED:
                    /* Send Release to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                           config_info);
                    /* Don't start the timer */

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_RBLOCKED:
               case SPRC_CKTS_OUTBUSY_RBLOCKED:
                    /* Send Release to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                           config_info);
                    /* Don't start the timer */

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3242, __FILE__, __LINE__, "cic : %x",
                                      ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_LRBLOCKED:
               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    /* Send Release to L3 */
                    SPRC_SendRELToMTP3_ANSI(CI_CAUSE_PROTOCOL_ERROR, cic_rec,
                                           config_info);
                    /* Don't start the timer */

                    break;
       }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void
__ISUP_NearEndStateInbusyLRBlocked(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    break;

               case SPRC_CKTS_UNEQUIPPED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3243, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_ACTIVE:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3244, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3245, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_ACTIVE:
                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3246, __FILE__, __LINE__, "cic : %x",
                                    ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_LBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_LBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_OUTBUSY_LBLOCKED:
                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_RBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3247, __FILE__, __LINE__, "cic : %x",
                                            ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_RBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3248, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_RBLOCKED:
                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;
                    
                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */  
                    ISUP_Alarm_ANSI(3249, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_LRBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_LRBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    break;
       }
}

 /****************************************************************************
 *  Purpose:
 *      Update Circuit Status
 *
 *  Input Parameters:
 *      far_end_state: Far End Circuit State
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     NONE.
 ****************************************************************************/
static void 
__ISUP_NearEndStateOutbusyLRBlocked(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_OCTET far_end_state)
{
       switch (far_end_state)
       {
               case SPRC_CKTS_TRANSIENT:
               case SPRC_CKTS_INBUSY_LRBLOCKED:

                    break;

               case SPRC_CKTS_UNEQUIPPED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3250, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_ACTIVE:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3251, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_ACTIVE:
                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3252, __FILE__, __LINE__, "cic : %x",
                                    ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_ACTIVE:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3253, __FILE__, __LINE__, "cic : %x",
                                        ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_LBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_INBUSY_LBLOCKED:
                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_OUTBUSY_LBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Send BLO to L3 */
                    __ISUP_BlockingCQSToBLS(cic_rec, config_info);

                    break;

               case SPRC_CKTS_IDLE_RBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3254, __FILE__, __LINE__, "cic : %x",
                                           ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_INBUSY_RBLOCKED:
                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3255, __FILE__, __LINE__, "cic : %x",
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_OUTBUSY_RBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    /* Remove Remote Blocking */
                    ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);

                    cic_rec->blr_state = BLR_IDLE;

                    /* Indication to App */
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_CQR_RUNBLOCKED_STIND, cic_rec);

                    /* ANSI Alarm; Alert Maintenance */
                    ISUP_Alarm_ANSI(3256, __FILE__, __LINE__, "cic : %x",
                                      ISUP_PCIC_TO_CIC(cic_rec->pcic));

                    break;

               case SPRC_CKTS_IDLE_LRBLOCKED:
                    /* IDLE the circuit */
                    __ISUP_ResetCQSToCPC (cic_rec, config_info);

                    break;

               case SPRC_CKTS_OUTBUSY_LRBLOCKED:
                    /* Release the circuit */
                    __ISUP_ReleaseCQSToCPC (cic_rec, config_info);

                    break;
       }
}

 /***************************************************************************
 *  Purpose:
 *      The processing for StopWaitingCGRS is done here
 *
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
static void 
__ISUP_StopWaitingCGRS(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_USHORT    i = 0;
    ITS_USHORT    affected_cics[256];
    ITS_USHORT    num_affected_cics;
    ITS_USHORT    cic;
    ITS_USHORT    index_cic;
    ITS_UINT      opc, dpc;
    ITS_OCTET     ni;
    ISUP_CIC_INFO *affected_cic_rec;
    ITS_EVENT     grs_ev;
    ITS_ISUP_IE   grs_rs_ie;
    ITS_USHORT    grs_cic;
    ITS_OCTET     grs_sup_msg_type;
    ISUP_PCIC     pcic;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    /* check for this being a part of GRS previously sent
     * if yes, Assume GRS been discarded and stop GRA waiting
     */
    index_cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    if (cic_rec->cgrs_state == CGRS_WAIT_FOR_GRA)
    {
        cic = index_cic;
    }
    else
    {
        cic = (ITS_USHORT)(index_cic - 1);
    }

    opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
    dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
    ni  = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

    do
    {
      if(cic == index_cic)
      {
         affected_cic_rec = cic_rec; 
      }
      else
      {
         ISUP_PCICFromParts(&pcic, opc, dpc, ni, cic);
         affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
      }

      if (affected_cic_rec == NULL)
      {
          ISUP_ERROR(("Could not find PCIC\n"));
      }
      else if (affected_cic_rec->cgrs_state == CGRS_WAIT_FOR_GRA) 
      {
          /* Get the range and make all idle */
          cic_msg = ISUP_FindPcicMsgBuf(affected_cic_rec->pcic, ITS_FALSE,
                                                                ITS_TRUE);

          ITS_EVENT_INIT(&grs_ev, ITS_ISUP_ANSI_SRC, cic_msg->grs_msg_len);
          memcpy((void *)(grs_ev.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

          ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

          __ISUP_Validate_RangeStatus(&grs_ev, affected_cic_rec, config_info, 
                                      &grs_rs_ie, &grs_sup_msg_type, 
                                      &grs_cic);

          ITS_EVENT_TERM(&grs_ev);

          if (index_cic <= grs_cic + grs_rs_ie.param_data.rangeAndStatus.range)
          {
              __ISUP_GetGRSCics(grs_cic, &grs_rs_ie, 
                                affected_cics, &num_affected_cics);

              __ISUP_ProcessAffectedCics(affected_cics,
                                         num_affected_cics,
                                         __ISUP_IdleCircuit,
                                         affected_cic_rec, config_info);

              /* Stop timers T22, T23 */
              __ISUP_StopGRSTimers(affected_cic_rec, config_info);

              SPRC_SendIndToApp_ANSI(ITS_ISUP_UCIC_MAINT_RQIND, affected_cic_rec);

              /* Alert Maintenance Personnel */
              ISUP_Alarm_ANSI(3060, __FILE__, __LINE__, "cic : %x",
                                ISUP_PCIC_TO_CIC(affected_cic_rec->pcic));
            
              affected_cic_rec->cgrs_state = CGRS_IDLE;
           }

           if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) != 
               ISUP_PCIC_TO_CIC(cic_rec->pcic))
           {
               ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
           }

           break;
       }
       else
       {
          cic -=1;

          if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) !=
              ISUP_PCIC_TO_CIC(cic_rec->pcic))
          {
              ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
          }
       }
    }while ( i++ < ( index_cic > 24 ? 24 : index_cic));
}

 /***************************************************************************
 *  Purpose:
 *      To check for Unequipped range CICs in GRS received from L3
 *
 *  Input Parameters:
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_BOOLEAN
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_IsRangeCICUnequipped( ISUP_CIC_INFO *cic_rec, 
                             ISUP_OPC_DPC_INFO *config_info,
                             ITS_USHORT *affected_cics,
                             ITS_USHORT num_affected_cics)
{
    int i, j;
    ITS_USHORT msgCicCktGrpId, lastCicCktGrpId;
    ITS_USHORT cicsInCktGrp = 0;
    ITS_USHORT index, cicBit;
    ITS_BOOLEAN ret = ITS_FALSE;
    ISUP_CKGP_LIST *ckgp_list = NULL;
    ISUP_CFG_CKGP_INFO cktGrp;

    cicsInCktGrp    = ISUP_CLASS_INFO(config_info->isup_var_class)->CICsInCkgp;
    msgCicCktGrpId  = affected_cics[0] / cicsInCktGrp;
    lastCicCktGrpId = affected_cics[num_affected_cics - 1]/ cicsInCktGrp;

    ckgp_list = ISUP_FindCkgpList(config_info->opc_dpc_ni, ITS_TRUE);

    if(ckgp_list == NULL)
    {
        ISUP_DEBUG(("Problem in finding Circuit Group List Array."));
        return ret;
    }

    index = 0;

    for (i = msgCicCktGrpId; i <= lastCicCktGrpId ; i++)
    {
        if (ckgp_list->ckgp_info[i].ckgp_id == ISUP_INV_CKGP_ID)
        {
            memset(&cktGrp.usable_cics[0], 0, sizeof(ITS_UINT));
        }
        else
        {
            memcpy(&cktGrp.usable_cics[0], 
                        &ckgp_list->ckgp_info[i].usable_cics[0], 
                                                sizeof(ITS_UINT)); 
        }

        cicBit = affected_cics[index] % cicsInCktGrp;

        for(j = cicBit; j < cicsInCktGrp; 
                        j = (affected_cics[index] - i*cicsInCktGrp))
        {
           if ((cktGrp.usable_cics[0] & (0x00000001 << j)) == 0)
           {
              /* Send UCIC as not provisioned locally */
              SPRC_SendUCICToMTP3_ANSI( affected_cics[index], config_info);
              ret = ITS_TRUE;
           }

           index++;

           if(index == num_affected_cics)
           {
              return ret;
           }
        }
    }

    ISUP_ReleaseCkgpList(ckgp_list, ITS_TRUE);

    return ret;
}
