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
 *  ID: $Id: ansi-idle_ansi92.c,v 1.1.1.1 2007-10-08 11:12:17 bsccs2 Exp $
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
 * LOG: Revision 9.1  2005/03/23 12:54:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.13  2005/03/21 13:53:56  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.13.2.2.6.1.12.4  2005/02/24 09:57:27  ssingh
 * LOG: fix for bug #1552/1553 (Ramesh KV)
 * LOG:
 * LOG: Revision 7.13.2.2.6.1.12.3  2005/02/03 12:44:40  ssingh
 * LOG: Bug #1448; unexpected Msg from Network and peg/stats handling.
 * LOG: (Ramesh KV, Abhijit D)
 * LOG:
 * LOG: Revision 7.13.2.2.6.1.12.2  2004/12/29 14:35:54  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.13.2.2.6.1.12.1  2004/12/06 13:34:50  mmanikandan
 * LOG: Windows Compilation Support
 * LOG:
 * LOG: Revision 7.13.2.2.6.1  2004/01/05 10:10:44  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.13.2.2.2.2  2003/11/24 06:36:29  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.13.2.2.2.1  2003/09/13 06:27:00  akumar
 * LOG: Msg Based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 7.13.2.2  2003/06/16 14:17:49  sjaddu
 * LOG: COT t26 timer fix propagation from current.
 * LOG:
 * LOG: Revision 7.13.2.1  2003/05/07 10:37:59  ssingh
 * LOG: Latest Changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.8  2003/05/06 13:55:52  sswami
 * LOG: Alarm related changes :opc information included.
 * LOG:
 * LOG: Revision 8.7  2003/04/28 15:07:15  sjaddu
 * LOG: Removed EVEN TERM every thing is taken care.
 * LOG:
 * LOG: Revision 8.6  2003/04/24 14:13:25  sswami
 * LOG: Bug #317; Alarm Enhancement related changes done.
 * LOG:
 * LOG: Revision 8.5  2003/04/16 06:42:11  akumar
 * LOG: ITS_EVENT_TERM added.
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
 * LOG: Revision 7.13  2003/02/05 01:08:36  sjaddu
 * LOG: Added some Cic Reserve checks.
 * LOG:
 * LOG: Revision 7.12  2003/01/29 19:08:21  sjaddu
 * LOG: Added one more state for CRI.
 * LOG:
 * LOG: Revision 7.11  2003/01/22 14:55:02  vnitin
 * LOG: Tandem port for Ansi ISUP
 * LOG:
 * LOG: Revision 7.10  2002/12/23 22:49:04  sjaddu
 * LOG: Forward Cot msg to application.
 * LOG:
 * LOG: Revision 7.9  2002/12/11 14:23:04  ssingh
 * LOG: Changed code for INF/INR/CPG and T33 expiry handling.
 * LOG:
 * LOG: Revision 7.8  2002/12/02 11:17:59  sjaddu
 * LOG: COT Handling in IDLE state.
 * LOG:
 * LOG: Revision 7.7  2002/11/14 14:12:33  ssingh
 * LOG: Code changed as per the Functional testing in case of IAM handling.
 * LOG:
 * LOG: Revision 7.6  2002/11/12 06:04:59  akumar
 * LOG: Added ANSI ISUP Alarms
 * LOG:
 * LOG: Revision 7.5  2002/11/07 14:01:16  ssingh
 * LOG: Added FIX for BUG# 147 for inconsistent handling of RLC across the states.
 * LOG:
 * LOG: Revision 7.4  2002/10/30 08:59:30  sjaddu
 * LOG: Added Continuity procedures.
 * LOG:
 * LOG: Revision 7.3  2002/10/25 13:43:57  ssingh
 * LOG: Code changes done as a part of BUG 141-to-146 fixing.
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
 * LOG: Revision 1.1.2.28  2002/07/30 13:54:00  sjaddu
 * LOG: Added MTP indications and CFN procedures.
 * LOG:
 * LOG: Revision 1.1.2.27  2002/07/24 18:50:05  ssingh
 * LOG: FIXED Test Call (origination) Bug.
 * LOG:
 * LOG: Revision 1.1.2.26  2002/07/23 18:24:12  ssingh
 * LOG: Added/Changed Code to fix BUG noticed during testing.
 * LOG:
 * LOG: Revision 1.1.2.25  2002/07/22 21:36:10  ssingh
 * LOG: FIXED some problem processing local REL request.
 * LOG:
 * LOG: Revision 1.1.2.24  2002/07/19 19:12:25  ssingh
 * LOG: ANSI92 completed according to the SDLs.
 * LOG:
 * LOG: Revision 1.1.2.23  2002/07/15 23:23:29  ssingh
 * LOG: Completed ANSI as per ITU SDLs.
 * LOG:
 * LOG: Revision 1.1.2.22  2002/07/14 19:01:41  hbalimid
 * LOG: Wait for OGC Completion in place.
 * LOG:
 * LOG: Revision 1.1.2.21  2002/07/13 02:29:13  hbalimid
 * LOG: Added Inter-state procedures.
 * LOG:
 * LOG: Revision 1.1.2.20  2002/07/12 21:50:08  hbalimid
 * LOG: StartCRS added for Unexpected Messages.
 * LOG:
 * LOG: Revision 1.1.2.19  2002/07/12 15:25:08  ssingh
 * LOG: Added/Changed CQM/CQR related methods.
 * LOG:
 * LOG: Revision 1.1.2.18  2002/07/12 14:05:26  hbalimid
 * LOG: CQM moved to CSC.
 * LOG:
 * LOG: Revision 1.1.2.17  2002/07/12 01:02:00  hbalimid
 * LOG: UCIC procedures added.
 * LOG:
 * LOG: Revision 1.1.2.16  2002/07/10 21:36:57  hbalimid
 * LOG: OGC Answered complete.
 * LOG:
 * LOG: Revision 1.1.2.15  2002/07/10 19:32:12  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 1.1.2.14  2002/07/10 18:41:38  hbalimid
 * LOG: CPC outgoing statemachine implemented.
 * LOG:
 * LOG: Revision 1.1.2.13  2002/07/10 05:36:00  hbalimid
 * LOG: CPC Incoming States completed.
 * LOG:
 * LOG: Revision 1.1.2.12  2002/07/09 00:00:15  ssingh
 * LOG: CQR implemented. Bug Fixed.
 * LOG:
 * LOG: Revision 1.1.2.11  2002/07/08 23:45:23  hbalimid
 * LOG: Test call implemented for Received IAM from L3.
 * LOG:
 * LOG: Revision 1.1.2.10  2002/07/08 14:11:30  ssingh
 * LOG: Code changes as per ANSI92 testing (BUG FIX)
 * LOG:
 * LOG: Revision 1.1.2.9  2002/07/07 14:06:23  hbalimid
 * LOG: Completed CRS state machine handling.
 * LOG:
 * LOG: Revision 1.1.2.8  2002/07/06 18:33:04  hbalimid
 * LOG: CVTR state implemented.
 * LOG:
 * LOG: Revision 1.1.2.7  2002/07/06 06:09:59  hbalimid
 * LOG: Tookcare of all warnings.
 * LOG:
 * LOG: Revision 1.1.2.6  2002/07/05 22:01:24  hbalimid
 * LOG: ANSI CVT states and timers implemented.
 * LOG:
 * LOG: Revision 1.1.2.5  2002/07/04 23:27:04  hbalimid
 * LOG: CVT handling added.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/07/04 00:25:42  hbalimid
 * LOG: Typos propagated from CCITT fixed in all files.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/03 16:41:16  hbalimid
 * LOG: Modified according to ANSI92.
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

#include <isup_intern.h>
#include <ansi/isup_92.h>

/*
 * Functions for handling messages in the Idle state for ANSI92 variant.
 * This is considered to be the generic ANSI variant, and all other ANSI variants
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
 *      The processing for an LPA received in the IDLE state is done here.
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
__ISUP_Received_LPA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_LPA(msg, cic_rec, config_info, src);
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
 *
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
static void
__ISUP_Received_COT(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received COT in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Check if COT msg indicates success */

        if (cic_rec->cri_state == CRI_WAIT_FOR_REL)
        {
            int offset = 0;
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T34);

            __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T27,
                             config_info->\
                             tmr_hndl_info[ITS_ISUP_TIMER_T27].tmr_value);
            
            cic_rec->cri_state = CRI_WAIT_FOR_CCR;

            if (cic_rec->cot_first_ind == ITS_TRUE)
            {
                cic_rec->cot_first_ind = ITS_FALSE;
                ISUP_Alarm_ANSI(3171, __FILE__, __LINE__, "cic : %x",
                                       ISUP_PCIC_TO_CIC(cic_rec->pcic));
            }
           /* Check for failed or success indicator */
            offset = sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT) +
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
            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
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
        int offset =0 ;
        ISUP_DEBUG(("Received COT in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if ((cic_rec->cro_state == CRO_WAIT_FOR_COT &&
           cic_rec->dco_state != DCO_WAIT_FOR_LPA) ||
           cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY ||
           cic_rec->cro_state == CRO_WAIT_FOR_OUTGOING_CCR)
        {

           /* Check for failed or success indicator */
            offset = sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT) +
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
                else if (cic_rec->cro_state != CRO_WAIT_FOR_OUTGOING_CCR)
                {
                    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);
                }

                /*Send REL */
                SPRC_SendRELToMTP3_ANSI(CI_CAUSE_NORMAL_UNSPECIFIED,
                                        cic_rec,config_info);
                __ISUP_StartRELTimers(cic_rec, config_info);

                cic_rec->cro_state = CRO_WAIT_FOR_RLC;
                cic_rec->fsm_state = WAIT_INCOMING_RLC;
                cic_rec->cot_first_ind = ITS_TRUE;
                break;

            case CONTINUITY_CHECK_FAILED:

                if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY ||
                    cic_rec->cro_state == CRO_WAIT_FOR_OUTGOING_CCR)
                {
                    ISUP_ERROR(("In IDLE :Unexpected COT Failure Received"
                            " from App discarding. pcic 0x%08x,vcic %d.\n",
                              cic_rec->pcic, cic_rec->vcic));

                     /* Send error indication to application. */
                     SPRC_SendErrorToApp_ANSI(ISUP_MSG_COT,
                                              ITS_ISUP_UNEXP_APPMSG_IDLE_ERR,
                                              cic_rec);
                    return;
                }
                ISUP_DEBUG(("IDLE :COT FAILURE Received"
                            " from App. pcic 0x%08x, vcic %d.\n",
                             cic_rec->pcic, cic_rec->vcic));

                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T24);

                __ISUP_StartCPCToCRO (cic_rec, config_info);

                SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);
                break;
            }
        }
        else
        {
            ISUP_ERROR(("IDLE:Received COT in invalid"
                        "state pcic 0x%08x, vcic %d.\n",
                         cic_rec->pcic, cic_rec->vcic));
            /* Send error indication to application. */
            SPRC_SendErrorToApp_ANSI(ISUP_MSG_COT,
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

    if (src == ISUP_SRC_L3_ANSI)    /* CPC Incoming */
    {
        ISUP_DEBUG(("Received IAM in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));


        /*
         * Check for the test call
         * calling party category gives whether test call or not
         */

        /* NOTE:
         * Depending on the current event structure recived
         * (ITS_EVENT) event->data[15] is the calling party category
         * so directly comparing against 16th octet
         * If incoming event structre is changed in IntelliSS7
         * search for calling party category is to be modified.
         * This parameter is a fixed mandatory in IAM
         * Also direct indexing into the array is more faster
         */

        if (msg->data[15] == CGP_CAT_TEST_CALL)
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

        /* circuit remotely blocked? */
        if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
        {
            if (testcall == ITS_FALSE)
            {
                /* Remove the Remote Blocking */
                ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);
            }

        }

        /* circuit locally blocked? */
        if(ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
        {
            if (testcall == ITS_FALSE)
            {
                /* Blocking CPC->BLS */
                __ISUP_CSC_BlockingBLS(cic_rec, config_info);

                /* Idle the circuit */
                ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

                /* cic fsm state to Idle */
                cic_rec->fsm_state = IDLE;

                return;
            }
        }

        /* Here we directly jump to Wait for OGC Complete */

        if(cic_rec->cro_state != CRO_IDLE)
        {
           __ISUP_StopCPCToCRO (cic_rec, config_info);
        }

        if (cic_rec->cri_state != CRI_IDLE)
        {
            __ISUP_StopCPCToCRI(cic_rec, config_info);
        }

        offset = sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT) + 
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

            ISUP_DEBUG(("Received IAM with COT chk , pcic 0x%08x, vcic %d.\n",
                         cic_rec->pcic, cic_rec->vcic));

            /* Start Timer T8 */
            tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T8, 
                   config_info->tmr_hndl_info[ITS_ISUP_TIMER_T8].tmr_value);
            if (tret != ITS_SUCCESS)
            {
                ISUP_ERROR(("IDLE IAM: Failed to start T8"
                            ". pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic));
            }

            /*Change CCI state to Wait for COT*/
            cic_rec->cci_state = CCI_WAIT_FOR_COT;

            /* Change state to Wait for continuity report */
            cic_rec->fsm_state = WAIT_INCOMING_COT;

            break;
        default :
            break;
        }

        /* Mark ckt Incoming Busy */
        ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IN_CTK_BUSY);

        /*Check Reserving bussiness */
        if (cic_rec->resrv_ind != ITS_TRUE)
        {
            cic_rec->resrv_ind = ITS_TRUE;
        }

        /* Send to app */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

    }
    else    /* CPC Outgoing */
    {
        ISUP_DEBUG(("++Received IAM in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if(cic_rec->cro_state != CRO_IDLE)
        {
           __ISUP_StopCPCToCRO (cic_rec, config_info);
        }

        if (cic_rec->cri_state != CRI_IDLE)
        {
            __ISUP_StopCPCToCRI(cic_rec, config_info);
        }

        /* Check CIC call processing state */
        if (ISUP_CIC_GET_CALL(cic_rec->cic_state) != CKTS_IDLE_CTK)
        {
            app_err = ITS_ISUP_CIC_BUSY_ERR;
        }

        if (msg->data[15] != CGP_CAT_TEST_CALL)
        {
            /* not a test call */
            /* Check CIC maint blocking states */

            if (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LBLOCKED)
            {
                ISUP_CIC_SET_MAINT(cic_rec->cic_state, CKTS_ACTIVE);

                cic_rec->bls_state = BLS_IDLE;
            }
            else if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
            {
                app_err = ITS_ISUP_CIC_MNBLOCK_ERR;
            }
        }
        else
        {
            ISUP_DEBUG(("Received IAM is a TEST CALL, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));
        }

        if (app_err != ITS_SUCCESS)
        {
            ISUP_ERROR(("Discarding outgoing IAM message since CIC in "
                        "invalid state, pcic 0x%08x, vcic %u\n",
                        cic_rec->pcic, cic_rec->vcic));

            /* Send error indication to application. */
            SPRC_SendErrorToApp_ANSI(ISUP_MSG_IAM,app_err, cic_rec);
            /* No updates to any data in cic_rec */

            return;
        }

        /* OGC Selected
         * Mark ckt Outgoing Busy 
         */
        ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_OUT_CTK_BUSY);

        /* 
         * offset to encoded IAM is after MTP3 header + CIC + MsgType 
         */
        offset = sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT) + 
                     sizeof(ITS_OCTET);

        /* FIXME:
         * Set Pre-ACM Connect Indicator
         * OGC Selection Successful to APP
         */

        /* Start Timer T7 */
        tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T7, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T7].tmr_value);
        if (tret != ITS_SUCCESS)
        {
            ISUP_ERROR(("IDLE IAM: Failed to start T7. pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));
        }

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
                   config_info->tmr_hndl_info[ITS_ISUP_TIMER_T24].tmr_value);
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
            break;
        }

        /* Send to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);
    }
}


/*
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

    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received PAM in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to app */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

        /* Change state to IDLE */
    }
    else 
    {
        ISUP_DEBUG(("Received PAM in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
static void
__ISUP_Received_REL(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    if (src == ISUP_SRC_L3_ANSI) /* CPC Incoming */
    {
        ISUP_DEBUG(("Received REL in IDLE from MTP3, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cri_state == CRI_WAIT_FOR_REL ||
                     cic_rec->cri_state == CRI_WAIT_FOR_LPA)
        {
            if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
            {
                __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T34);
            }
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;

            /* Send to app */
            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
            cic_rec->fsm_state = WAIT_OUTGOING_RLC;
        }
        else if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            /*handle*/
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T27);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;

            /* Send to app */
            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
            cic_rec->fsm_state = WAIT_OUTGOING_RLC;

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

            /* Send to app */
            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
            cic_rec->fsm_state = WAIT_OUTGOING_RLC;
        }
        else if (cic_rec->cro_state == CRO_WAIT_FOR_COT)
        {
            __ISUP_StopCROToDCO(cic_rec,config_info);

            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;

            /* Send to app */
            SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
            cic_rec->fsm_state = WAIT_OUTGOING_RLC;
        }
        else
        {
            /* Send out RLC */
            SPRC_SendRLCToMTP3_ANSI(cic_rec, config_info);
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);
        }

        /* No State Change */
    }
    else  /* CPC Outgoing */
    {
        ISUP_DEBUG(("Received REL in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY ||
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
            __ISUP_StopCROToDCO(cic_rec,config_info);

            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            /*handle*/
            __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_TCCRR);
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL ||
                     cic_rec->cri_state == CRI_WAIT_FOR_LPA)
        {
            if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
            {
                __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T34);
            }
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }

        /* store the message in cic rec */
        memcpy(cic_rec->cpc_msg, msg->data, msg->len);
        cic_rec->cpc_msg_len = msg->len;

        /* Send to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

        __ISUP_StartRELTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   COT message handling
 *                           #445 & #454    related changes.
 ****************************************************************************/
static void
__ISUP_Received_RLC(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{

    if (src == ISUP_SRC_L3_ANSI)    /* CPC Incoming */
    {
        ISUP_DEBUG(("Received RLC in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Actually this condition should not hit but if there */
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
                SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);
            }

            cic_rec->crs_state = CRS_IDLE;
        }
        else
        {
            /* discard the message */
            ISUP_DEBUG(("Got unexpected RLC from MTP3, pcic 0x%08x, vcic %d.\n",
                         cic_rec->pcic, cic_rec->vcic));

            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);
        }
    }
    else    /* CPC Outgoing */
    {
        ISUP_DEBUG(("Received RLC in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        if (cic_rec->cro_state == CRO_WAIT_TIMER_EXPIRY ||
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
            __ISUP_StopCROToDCO(cic_rec,config_info);

            cic_rec->cro_state = CRO_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if (cic_rec->cri_state == CRI_WAIT_FOR_CCR)
        {
            if(cic_rec->cot_first_ind == ITS_TRUE)
            {
                /*handle*/
                __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_TCCRR);
            }
            else
            {
                /*handle*/
                __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T27);
            }
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }
        else if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL ||
                     cic_rec->cri_state == CRI_WAIT_FOR_LPA)
        {
            if (cic_rec->cri_state ==  CRI_WAIT_FOR_REL)
            {
                __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T34);
            }
            cic_rec->cri_state = CRI_IDLE;
            cic_rec->cot_first_ind = ITS_TRUE;
        }

        /* Change cic crr_state to idle */
        cic_rec->crr_state = CRR_IDLE;

        /* Send to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);

        /* Change state to IDLE - clear cic_rec */
        ISUP_ClearCic(cic_rec);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:

 *      The processing for a CRM received in the IDLE state
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
 ****************************************************************************/
static void
__ISUP_Received_CRM(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    int offset = 0;
    int tret = ITS_SUCCESS; 
    int app_err = ITS_SUCCESS;

    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received CRM in IDLE from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
 
        /* circuit remotely blocked? */
        if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
        {
            /* Remove the Remote Blocking */
            ISUP_CIC_REMOVE_REM_BLOCK(cic_rec->cic_state);
        }

        if(ISUP_CIC_IS_LOC_BLOCKED(cic_rec->cic_state))
        {
            /* Blocking CPC to BLS */
            __ISUP_CSC_BlockingBLS(cic_rec, config_info);

            /* Idle the circuit */
            ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IDLE_CTK);

            /* cic fsm state to Idle */
            cic_rec->fsm_state = IDLE;

            return;
        }

        /* Mark ckt Incoming Busy */
        ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_IN_CTK_BUSY);

        /*Check Reserving bussiness */
        if (cic_rec->resrv_ind != ITS_TRUE)
        {
            cic_rec->resrv_ind = ITS_TRUE;
        }

        offset = sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT) + sizeof(ITS_OCTET);

        switch((msg->data[offset+1] >> 2) & 0x03U)
        {
        case NCI_CHECK_NOT_REQUIRED:
        case NCI_CHECKED_PREV_CKT:
            cic_rec->fsm_state = WAIT_INCOMING_IAM;
            break; 

        case NCI_CHECK_CKT_REQUIRED:
            ISUP_DEBUG(("Received CRM with COT chk , pcic 0x%08x, vcic %d.\n",
                         cic_rec->pcic, cic_rec->vcic));

            __ISUP_StartCPCToCCI(cic_rec, config_info);

            /* Start Timer T8 */
            tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T8, 
                   config_info->tmr_hndl_info[ITS_ISUP_TIMER_T8].tmr_value);
            if (tret != ITS_SUCCESS)
            {
                ISUP_ERROR(("Failed to start T8. pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic));
            }

            /* Change state to Wait for continuity report */
            cic_rec->fsm_state = WAIT_INCOMING_COT_AND_IAM;

            break;
        default :
            break;
        }

        /* Start Timer TCRA */
        tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TCRA, 
               config_info->tmr_hndl_info[ITS_ISUP_TIMER_TCRA].tmr_value);

        if (tret != ITS_SUCCESS)
        {
            ISUP_ERROR(("Failed to start TCRA. pcic 0x%08x, vcic %d.\n",
                            cic_rec->pcic, cic_rec->vcic));
        }

        /* Send Message to application */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

        /* Send CRA back to Network as acknowledgement */
        SPRC_SendCRAToMTP3_ANSI(cic_rec, config_info);
    }
    else
    {
        ISUP_DEBUG(("Received CRM in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* Check CIC call processing state */
        if (ISUP_CIC_GET_CALL(cic_rec->cic_state) != CKTS_IDLE_CTK)
        {
            app_err = ITS_ISUP_CIC_BUSY_ERR;
        }
        else if (ISUP_CIC_GET_MAINT(cic_rec->cic_state) == CKTS_LBLOCKED)
        {
            ISUP_CIC_SET_MAINT(cic_rec->cic_state, CKTS_ACTIVE);

            cic_rec->bls_state = BLS_IDLE;
        }
        else if (ISUP_CIC_IS_REM_BLOCKED(cic_rec->cic_state))
        {
            app_err = ITS_ISUP_CIC_MNBLOCK_ERR;
        }

        if (app_err != ITS_SUCCESS)
        {
            ISUP_ERROR(("Discarding outgoing CRM message since CIC in "
                        "invalid state, pcic 0x%08x, vcic %u\n",
                        cic_rec->pcic, cic_rec->vcic));

             /* Send error indication to application. */
             SPRC_SendErrorToApp_ANSI(ISUP_MSG_CRM,app_err, cic_rec);

            /* No updates to any data in cic_rec */

            return;
        }

        /* OGC Selected; Mark ckt Outgoing Busy */
        ISUP_CIC_SET_CALL(cic_rec->cic_state, CKTS_OUT_CTK_BUSY);

        /* Start Timer TCRM */
        tret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TCRM,
             config_info->tmr_hndl_info[ITS_ISUP_TIMER_TCRM].tmr_value);

        if (tret != ITS_SUCCESS)
        {
            ISUP_ERROR(("IDLE CRM: Failed to start TCRM"
                ". pcic 0x%08x, vcic %d.\n",cic_rec->pcic, cic_rec->vcic));
        }
          
        offset = sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT) + sizeof(ITS_OCTET);

        /* Check for CRM with COT */
        switch((msg->data[offset+1] >> 2) & 0x03U)
        {
        case NCI_CHECK_NOT_REQUIRED:
        case NCI_CHECKED_PREV_CKT:

            /* OGC Selection Successful */

            /* Change state to wait incoming CRA */
            cic_rec->fsm_state = WAIT_INCOMING_CRA;
            break; 

        case NCI_CHECK_CKT_REQUIRED:

            ISUP_DEBUG(("Received CRM with COT check , pcic 0x%08x, vcic %d.\n",
                         cic_rec->pcic, cic_rec->vcic));

            __ISUP_StartCPCToCCO(cic_rec, config_info);

            /* OGC Selection Successful */

            /* Change state to Wait for continuity report and CRA */
            cic_rec->fsm_state = WAIT_COT_REPORTS_AND_CRA;

            break;
        
        default :
            break;
        }

        /* Send to L3 */
        SPRC_SendIsupToMTP3_ANSI(msg, cic_rec->vcic);
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
    __ISUP_CSC_Received_UCIC(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CVT received in the IDLE state
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
__ISUP_Received_CVT(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CVT(msg, cic_rec, config_info, src);

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CVR received in the IDLE state
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
__ISUP_Received_CVR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CVR(msg, cic_rec, config_info, src);

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


        ISUP_Alarm_ANSI(3139, __FILE__, __LINE__, "Message %x cic : %x",
                         msg->data[sizeof(MTP3_HEADER_ANSI) +
                         sizeof(ITS_USHORT) + sizeof(ITS_OCTET)],
                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

       /* Start CPC to CRS */
       __ISUP_CSC_StartCRS(cic_rec, config_info);

       PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);

  
       /* No change of state here */
    }
    else
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from App in IDLE. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                    msg->data[sizeof(MTP3_HEADER_ANSI) + sizeof (ITS_USHORT) +
                    sizeof(ITS_OCTET)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));

        /* Send error indication to application. */
        SPRC_SendErrorToApp_ANSI(msg->data[sizeof(MTP3_HEADER_ANSI) +
                                 sizeof (ITS_USHORT) + sizeof(ITS_OCTET)],
                                 ITS_ISUP_UNEXP_APPMSG_IDLE_ERR,
                                 cic_rec);

        ISUP_Alarm_ANSI(3140, __FILE__, __LINE__, "Message %x cic : %x",
                         msg->data[sizeof(MTP3_HEADER_ANSI) +
                         sizeof(ITS_USHORT) + sizeof(ITS_OCTET)],
                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

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
ITSSS7DLLAPI __ISUP_MsgHandlerProc
__ISUP_GetMsgProc_Idle_ANSI92(ITS_OCTET msgType)
{
    switch(msgType)
    {
    /* Following CPC messages should be treated here */
    case ISUP_MSG_IAM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_IAM;

    case ISUP_MSG_REL:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_REL;

    case ISUP_MSG_RLC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_RLC;

    case ISUP_MSG_ACM:
        break;

    case ISUP_MSG_ANM:
        break;

    case ISUP_MSG_CPG:
        break;

    case ISUP_MSG_COT:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_COT;

    case ISUP_MSG_CRA:
        break;

    case ISUP_MSG_CRM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CRM;

    case ISUP_MSG_CFN:
        break;

    case ISUP_MSG_EXM:
        break;

    case ISUP_MSG_FOT:
        break;

    case ISUP_MSG_INF:
    case ISUP_MSG_INR:
    case ISUP_MSG_RES:
    case ISUP_MSG_SUS:
        break;

    case ISUP_MSG_PAM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_PAM;

    case ISUP_MSG_CRG:
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

    case ISUP_MSG_LPA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_LPA;

    case ISUP_MSG_CQM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CQM;

    case ISUP_MSG_CQR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CQR;

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

    case ISUP_MSG_CVT:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CVT;

    case ISUP_MSG_CVR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CVR;

    case ISUP_MSG_UCIC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UCIC;

    default:
        /* 
         * Unknown message type for ISUP.
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
        /* Send REL to L3 */
        SPRC_SendRELToMTP3_ANSI(CI_CAUSE_TEMPORARY_FAILURE,
                                cic_rec,
                                config_info);
        /* Start T1 and T5 */
        __ISUP_StartRELTimers(cic_rec, config_info);

        /*Change CCI state to IDLE*/
        cic_rec->cci_state = CCI_IDLE;

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

    /* Send Indication to App */
    SPRC_SendIndToApp_ANSI(ITS_ISUP_CIC_COT_RELEASE_RQIND,cic_rec);
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
    __ISUP_CSC_Received_TimeoutT24(t_entry,cic_rec,config_info);
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of TCCR timer in the
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
__ISUP_Received_TimeoutTCCR(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutTCCR(t_entry,cic_rec,config_info);
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T25 timer in the
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
__ISUP_Received_TimeoutT25(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT25(t_entry,cic_rec,config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T26 timer in the
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
__ISUP_Received_TimeoutT26(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT26(t_entry,cic_rec,config_info);
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
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    ISUP_Alarm_ANSI(3047, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                     MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                     MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                         ISUP_PCIC_TO_CIC(cic_rec->pcic));

    if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T27].tmr_hndl_layer 
        == ISUP_TMR_HNDL_STACK)
    {
        /* Send RSC to L3 */
        SPRC_SendRSCToMTP3_ANSI( cic_rec, config_info);

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
                        "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                        ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                        ISUP_PCIC_TO_CIC(cic_rec->pcic)));
        }
        /* Change state to WAIT_OUTGOING_RSC */
        cic_rec->fsm_state = WAIT_OUTGOING_RSC;
    }

    if(cic_rec->cri_state == CRI_WAIT_FOR_CCR)
    {
        cic_rec->cri_state = CRI_IDLE;
    }

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
    SPRC_SendIndToApp_ANSI(ITS_ISUP_CIC_COT_RESET_RQIND, cic_rec);
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

    ISUP_Alarm_ANSI(3048, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                      MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                      MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                             ISUP_PCIC_TO_CIC(cic_rec->pcic));

    /* Nothing to be done at expiry except notify maintenance */
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
    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T33);
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T34 timer in the
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
__ISUP_Received_TimeoutT34(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_CSC_Received_TimeoutT34(t_entry,cic_rec,config_info);
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
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT36 event received in IDLE state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    ISUP_Alarm_ANSI(3053, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                     MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                     MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                                             ISUP_PCIC_TO_CIC(cic_rec->pcic));

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

    if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_T36].tmr_hndl_layer 
        == ISUP_TMR_HNDL_STACK)
    {
        /* Send RSC to L3 */
        SPRC_SendRSCToMTP3_ANSI( cic_rec, config_info);

        /* Start T16, T17 */
        __ISUP_StartRSCTimers(cic_rec, config_info);

        /* Change state to WAIT_INCOMING_RLC */
        cic_rec->fsm_state = WAIT_INCOMING_RLC;
    }
    else
    {
        /* Change state to WAIT_OUTGOING_RSC */
        cic_rec->fsm_state = WAIT_OUTGOING_RSC;
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
 *      This function handles the processing at expiry of TCVT timer in the 
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
__ISUP_Received_TimeoutTCVT(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                               ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutTCVT event received in IDLE state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    
    ISUP_Alarm_ANSI(3058, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                    MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                    MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                    ISUP_PCIC_TO_CIC(cic_rec->pcic));

    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_TCVT);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutTCVT in IDLE state: Unable to remove TCVT info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    if (cic_rec->cvts_state == CVTS_WAIT_FOR_CVR)
    {
        /* 
         * Send the timeout data to user app. 
         * This will be done whether the procedure is automated or not. 
         */
        SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);

        if (config_info->tmr_hndl_info[ITS_ISUP_TIMER_TCVT].tmr_hndl_layer 
            == ISUP_TMR_HNDL_STACK)
        {
            /* Restart TCVT, update restartCounter */
            ret = __ISUP_StartCVTRepeatTimer(cic_rec, config_info);
            if (ret == ITS_ISUP_TIMER_DONE)
            {
                /*
                 * Print Fail Message
                 */
                 ISUP_CRITICAL(("Second Expiry of CVT Timer. Failed to"
                                " receive CVR, pcic 0x%08x, vcic %d.\n",
                                cic_rec->pcic, cic_rec->vcic));
                 /* set cvts_state to idle */
                 cic_rec->cvts_state = CVTS_IDLE;
                 return;
            }

            /* Resend CVT to L3 */
            SPRC_SendCVTToMTP3_ANSI(cic_rec, config_info);
        }
        else
        {
            ISUP_DEBUG(("TimeoutTCVT Timeout Handler \"%s\"\n"
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                ISUP_TimerHandlerToString(config_info->\
                         tmr_hndl_info[ITS_ISUP_TIMER_TCVT].tmr_hndl_layer),
                cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));
            /* App will send CVT. */
        }
    }
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
    
   ISUP_Alarm_ANSI(3059, __FILE__, __LINE__, "State: %x Timer id: T%d",
                   cic_rec->cic_state,t_entry->timerId);

    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
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
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
__ISUP_GetTimeoutProc_Idle_ANSI92(ITS_UINT timerID)
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
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT25;
    case ITS_ISUP_TIMER_T26: /* 26   CCR response timer     */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT26;
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
    case ITS_ISUP_TIMER_T34: /* 34   Circuit query timer    */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT34;
        break;
    case ITS_ISUP_TIMER_T35: /* 35          */
        break;
    case ITS_ISUP_TIMER_T36: /* 36          */
        return(__ISUP_TimeoutHandlerProc) __ISUP_Received_TimeoutT36;
    case ITS_ISUP_TIMER_T37: /* 37          */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT37_ANSI92;
        break;
    case ITS_ISUP_TIMER_TCVT: /* TCVT          */
        return(__ISUP_TimeoutHandlerProc) __ISUP_Received_TimeoutTCVT;
    case ITS_ISUP_TIMER_TCCR: /* TCVT          */
        return(__ISUP_TimeoutHandlerProc) __ISUP_Received_TimeoutTCCR;
    default:
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;
    }
    return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;
}

