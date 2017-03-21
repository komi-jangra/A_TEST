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
 *  ID: $Id: ansi-slt.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $  
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:31  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:06  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.2  2005/04/07 09:10:29  snagesh
 * LOG: Modifications for LPO Feature
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:33  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:53:36  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.6.2.1.8.3.8.2  2005/01/25 11:34:26  snagesh
 * LOG: OAM Bug fixes for bugs 1419,1420
 * LOG:
 * LOG: Revision 7.6.2.1.8.3.8.1  2004/12/31 06:51:02  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.6.2.1.8.3  2004/09/07 06:45:55  sswami
 * LOG: Fix for text changes for alarm Id 2107
 * LOG:
 * LOG: Revision 7.6.2.1.8.2  2004/09/03 09:30:29  sswami
 * LOG: Fix given for text changes for alarm Ids 2108 & 2107
 * LOG:
 * LOG: Revision 7.6.2.1.8.1  2004/08/10 12:14:45  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.6.2.1  2003/02/21 01:42:34  randresol
 * LOG: Add more alarms
 * LOG:
 * LOG: Revision 7.6  2003/02/13 10:23:58  ttipatre
 * LOG: Bug 156 fixed and new alarm added.
 * LOG:
 * LOG: Revision 7.5  2002/12/24 19:30:13  randresol
 * LOG: Mark slt2 timer expired
 * LOG:
 * LOG: Revision 7.4  2002/12/24 07:40:17  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.3  2002/11/20 05:10:01  ttipatre
 * LOG: Pegs code submission.
 * LOG:
 * LOG: Revision 7.2  2002/11/10 19:48:27  randresol
 * LOG: Remove Shared Timers for SLT's
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/05/15 15:06:47  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.18  2002/01/29 19:56:26  mmiers
 * LOG: warning removal
 * LOG:
 * LOG: Revision 5.17  2001/12/06 22:39:04  mmiers
 * LOG: First cut of ITU MTP3.
 * LOG:
 * LOG: Revision 5.16  2001/11/29 23:43:24  mmiers
 * LOG: All config A tests passed (by kicking the INET).
 * LOG:
 * LOG: Revision 5.15  2001/11/14 23:17:13  mmiers
 * LOG: Many changes from conformance testing.
 * LOG:
 * LOG: Revision 5.14  2001/11/01 20:41:01  mmiers
 * LOG: A few fixes.
 * LOG:
 * LOG: Revision 5.13  2001/10/30 00:16:10  mmiers
 * LOG: Today's debugging session.  Looks close.
 * LOG:
 * LOG: Revision 5.12  2001/10/25 16:51:32  mmiers
 * LOG: SLT timer context bug.  T28 timer context bug.  Fix bugs in
 * LOG: SMH I added yesterday.
 * LOG:
 * LOG: Revision 5.11  2001/10/22 21:18:21  rsonak
 * LOG: Get cvs logs in the file
 * LOG:
 ****************************************************************************/

#include <string.h>
#include <stdlib.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_assertion.h>
#include <its_timers.h>

#ident "$Id: ansi-slt.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $"

#include <ansi/snmm.h>
#include <ansi/sltm.h>
#include <ansi/mtp3.h>

#include "mtp3_intern.h"
/*27-Oct-2010 Sandeep As we need SLT T1 and SLT T2 need to be LOCAL*/
#define TIMERS_StartUTimer TIMERS_StartTimer_MSEC

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
SLT_Main_ANSI(MTP3_SubSystems src, MTP3_SubSystems dest,
              SLT_Triggers trigger,
              ITS_OCTET *sif, ITS_USHORT len,
              ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_TRACE_ENTRY_ANSI(MTP3_SLT, src, trigger, sif, len,
                          linkSet, linkCode);

    switch (trigger)
    {
    case SLT_TRIGGER_L2_MSG:                 /* from HMDT */
    case SLT_TRIGGER_START_TEST:             /* from MGMT */
    case SLT_TRIGGER_T1:                     /* from timer control */
        return SLTC_Main_ANSI(src, trigger, sif, len, linkSet, linkCode);
    }

    MTP3_DEBUG(("Invalid trigger for function %d\n",
                trigger));
    PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);

    return (ITS_EINVALIDARGS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
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
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * snagesh   04-04-2005  ACC651-SDS-MTPL-1.0.02  Propogation for LPO feature
 *                       ID::D0010
 *
 ****************************************************************************/
int
SLTC_Main_ANSI(MTP3_SubSystems src,
               SLT_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    SLTM_MESSAGE *sltm = (SLTM_MESSAGE *)&sif[sizeof(MTP3_HEADER_ANSI) +
                                              sizeof(ITS_OCTET)];
    MTP3_HEADER_ANSI omtp3;
    SLTM_MESSAGE osltm;
    ITS_UINT pc1, pc2;
    ITS_EVENT ev;
    ITS_OCTET dlen;
    int ret;
    SS7_LinkPtr ln;
    SS7_LinkSetPtr ls;
    MTP3_TimerContext tc;
    ITS_OCTET slc;

    MTP3_TRACE_ENTRY_ANSI(MTP3_SLT_SLTC, src, trigger, sif, len,
                          linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Invalid link %d:%d\n", linkSet, linkCode));

        return (ITS_EINVALIDARGS);
    }

    ls = ln->linkSet;
    ITS_C_ASSERT(ls != NULL);

    switch (trigger)
    {
    case SLT_TRIGGER_L2_MSG:                 /* from HMDT */
        switch (SLTM_HC0_GET_ANSI(*sltm))
        {
        case SLTM_HC0_TST_ANSI:
            switch (SLTM_HC1_GET_ANSI(*sltm))
            {
            case SLTM_HC1_SLTM_ANSI:
                /* Increament Link Peg for SLTM Received */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_RX);

                PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_SLTM_RX);
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLTM_RX);
		
                /* build SLTA, send */
                pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

                /*
                 * For some reason, the INET sends us our own
                 * SLTM back.  This check avoids us stopping
                 * because of that.  Used to be:
                 * ITS_C_ASSERT(pc1 == ls->lpc);
                 * ITS_C_ASSERT(pc2 == ls->adjacent);
                 */
                if (pc1 != ls->lpc || pc2 != ls->adjacent)
                {
                    return (ITS_EINVALIDARGS);
                }

                /* Fix the problem for Bug 156 */
                /* Don't send SLTA if Invalid SLC in SLTM */
                slc = sltm->data.linkTest.slc_li & 0x0FU;

                if ((ln = LINK_FindLink(linkSet, slc)) == NULL)
                {
                    MTP3_ERROR(("Invalid slc %d\n", slc));

                    return (ITS_EINVALIDARGS);
                }

                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SLTM_SPEC | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc2);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, pc1);

                dlen = SLTM_LINK_TEST_GET_LENGTH_ANSI(sltm->data.linkTest);

                SLTM_HC0_SET_ANSI(osltm, SLTM_HC0_TST_ANSI);
                SLTM_HC1_SET_ANSI(osltm, SLTM_HC1_SLTA_ANSI);
                SLTM_LINK_TEST_SET_SLC_ANSI(osltm.data.linkTest, ln->linkCode);
                SLTM_LINK_TEST_SET_LENGTH_ANSI(osltm.data.linkTest, dlen);
                memcpy(osltm.data.linkTest.pattern, sltm->data.linkTest.pattern,
                       dlen);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SLTM_Encode_ANSI(&ev, &omtp3, &osltm);

                /* Increament Link Peg for SLTA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_TX);

                PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_SLTA_TX);
	        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLTA_TX);	


                ret = HMRT_Main_ANSI(MTP3_SLT_SLTC, SMH_TRIGGER_TEST_CONTROL_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                return (ret);

            case SLTM_HC1_SLTA_ANSI:
                ev.data = sif;
                ev.len = len;
                SLTM_Decode_ANSI(&ev, &omtp3, &osltm);
                /* Increament Link Peg for SLTA Received */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_RX);
 
                PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_SLTA_RX);
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLTA_RX);

                if (memcmp(ln->testPattern, osltm.data.linkTest.pattern,
                           SLTM_LINK_TEST_GET_LENGTH_ANSI(osltm.data.linkTest)) == 0)
                {
                    /* if (first attempt || second attempt) */
                    if (ln->sltFlags & LINK_TEST_FIRST_ATTEMPT ||
                        ln->sltFlags & LINK_TEST_SECOND_ATTEMPT)
                    {
                        /* stop T1 */
                        if (ln->slt1 != TIMER_BAD_SERIAL)
                        {
                            TIMERS_CancelTimer(ln->slt1);
                            ln->slt1 = TIMER_BAD_SERIAL;
                        }

                        ln->sltFlags &= ~(LINK_TEST_FIRST_ATTEMPT|
                                          LINK_TEST_SECOND_ATTEMPT);

                        /*
                         * This was in SLM, but I believe belongs here
                         */
                        if (!ln->testPassed)
                        {
                            ln->testPassed = ITS_TRUE;

                            TLAC_Main_ANSI(MTP3_SLM_LSAC,
                                           STM_TRIGGER_LINK_IN_SERVICE,
                                           NULL, 0,
                                           linkSet, linkCode);
                            MTP3_ERROR(("Going to deactivate the link Now \n"));

                            LLSC_Main_ANSI(MTP3_SLM_LSAC,
                                           SLM_TRIGGER_LINK_ACTIVE,
                                           NULL, 0,
                                           linkSet, linkCode);
                        }

                        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_SLT_PASSED);
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLT_PASSED);

                        return MGMT_Main_ANSI(MTP3_SLT_SLTC,
                                              MGMT_TRIGGER_LINK_TEST_PASSED,
                                              sif, len,
                                              linkSet, linkCode);
                    }
                }
                else
                {
                    /* if (first attempt) */
                    if (ln->sltFlags & LINK_TEST_FIRST_ATTEMPT)
                    {
                        /* stop T1 */
                        if (ln->slt1 != TIMER_BAD_SERIAL)
                        {
                            TIMERS_CancelTimer(ln->slt1);
                            ln->slt1 = TIMER_BAD_SERIAL;
                        }
 
                        MTP3_Alarm_ANSI(2507, __FILE__, __LINE__,
                                        "SLT failed for linkset:linkcode %x:%x",
                                        linkSet,linkCode);
                        
                        /* build SLTM, send */
                        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                        pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SLTM_SPEC | ls->ni | MTP3_MPC_PRI_3);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, pc2);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, pc1);

                        dlen = strlen((char *)ln->testPattern);

                        SLTM_HC0_SET_ANSI(osltm, SLTM_HC0_TST_ANSI);
                        SLTM_HC1_SET_ANSI(osltm, SLTM_HC1_SLTM_ANSI);
                        SLTM_LINK_TEST_SET_SLC_ANSI(osltm.data.linkTest, ln->linkCode);
                        SLTM_LINK_TEST_SET_LENGTH_ANSI(osltm.data.linkTest, dlen);
                        memcpy(osltm.data.linkTest.pattern, ln->testPattern,
                               dlen);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                        SLTM_Encode_ANSI(&ev, &omtp3, &osltm);

                        /* Increament Link Peg for SLTM Transmitted */
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_TX);

                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLTM_TX);
                        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_SLTM_TX);

                        ret = HMRT_Main_ANSI(MTP3_SLT_SLTC, SMH_TRIGGER_TEST_CONTROL_MSG,
                                             ev.data, ev.len,
                                             linkSet, linkCode);
                        ITS_EVENT_TERM(&ev);

                        /* start T1 */
                        tc.timerId = MTP3_SLT_T1;
                        tc.data.linkInfo.linkSet = linkSet;
                        tc.data.linkInfo.linkCode = linkCode;

                        ln->slt1 =
                            TIMERS_StartUTimer(ITS_MTP3_ANSI_SRC,
                                               __ansi_slt_t1 * USEC_PER_MILLISEC,
                                               &tc, sizeof(MTP3_TimerContext));
                        return (ret);
                    }
                    else if (ln->sltFlags & LINK_TEST_SECOND_ATTEMPT)
                    {
                        /* stop T1 */
                        if (ln->slt1 != TIMER_BAD_SERIAL)
                        {
                            TIMERS_CancelTimer(ln->slt1);
                            ln->slt1 = TIMER_BAD_SERIAL;
                        }

                        MTP3_Alarm_ANSI(2508, __FILE__, __LINE__, 
                                        "SLT failed for linkset:linkcode %x:%x",
                                         linkSet,linkCode);

                        ln->sltFlags &= ~(LINK_TEST_FIRST_ATTEMPT|
                                          LINK_TEST_SECOND_ATTEMPT);

                        ln->testPassed = ITS_FALSE;

                        /* This should also cause a link failure as well */
                        MTP2_SendData_ANSI(linkSet, linkCode, L3_L2_STOP, NULL, 0);

                        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_SLT_FAILED);
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLT_FAILED);

                        LSAC_Main_ANSI(MTP3_SLT_SLTC,
                                       SLM_TRIGGER_L2_OUT_OF_SERVICE,
                                       NULL, 0,
                                       linkSet, linkCode);

                        MGMT_Main_ANSI(MTP3_SLT_SLTC,
                                       MGMT_TRIGGER_LINK_TEST_FAILED,
                                       sif, len,
                                       linkSet, linkCode);
                    }
                }
                break;

            default:
                MTP3_DEBUG(("SLTC_Main_ANSI: Bad HC1 code %0x\n",
                            SLTM_HC1_GET_ANSI(*sltm)));
                break;
            }
            break;

        default:
            MTP3_DEBUG(("SLTC_Main_ANSI: Bad HC0 code %0x\n",
                        SLTM_HC0_GET_ANSI(*sltm)));
            break;
        }
        break;

    case SLT_TRIGGER_START_TEST:             /* from MGMT */
        ln->sltFlags &= ~(LINK_TEST_FIRST_ATTEMPT|
                         LINK_TEST_SECOND_ATTEMPT);

        if (ln->isUp)
        {
            /* set TP = 'x' */

            /* start T1 */
            tc.timerId = MTP3_SLT_T1;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->slt1 =
                TIMERS_StartUTimer(ITS_MTP3_ANSI_SRC,
                                   __ansi_slt_t1 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

            /* start the repeat test timer */
            if (ln->slt2 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelTimer(ln->slt2);
            }

            tc.timerId = MTP3_SLT_T2;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->slt2 =
                TIMERS_StartUTimer(ITS_MTP3_ANSI_SRC,
                                   __ansi_slt_t2 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

            /* set first attempt */
            ln->sltFlags |= LINK_TEST_FIRST_ATTEMPT;

            /* build SLTM, send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SLTM_SPEC | ls->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            dlen = strlen((char *)ln->testPattern);

            SLTM_HC0_SET_ANSI(osltm, SLTM_HC0_TST_ANSI);
            SLTM_HC1_SET_ANSI(osltm, SLTM_HC1_SLTM_ANSI);
            MTP3_ERROR(("\n  SLTM SLC =%d Testpattern Length %d",ln->linkCode ,dlen));
            SLTM_LINK_TEST_SET_SLC_ANSI(osltm.data.linkTest, ln->linkCode);
            SLTM_LINK_TEST_SET_LENGTH_ANSI(osltm.data.linkTest, dlen);
            memcpy(osltm.data.linkTest.pattern, ln->testPattern,
                   dlen);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SLTM_Encode_ANSI(&ev, &omtp3, &osltm);

            /* Increament Link Peg for SLTM Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_TX);

            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_SLTM_TX); 
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLTM_TX);

            ret = HMRT_Main_ANSI(MTP3_SLT_SLTC, SMH_TRIGGER_TEST_CONTROL_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            return (ret);
        }

    case SLT_TRIGGER_T1:                     /* from timer control */
        if (!ln->isUp )
        {
            MTP3_WARNING(("SLT_TRIGGER_T1: Test NOT Started; Link is not active\n"));
            break;
        }

        if (ln->sltFlags & LINK_TEST_FIRST_ATTEMPT)
        {

            MTP3_Alarm_ANSI(2507, __FILE__, __LINE__,
                      "SLT failed for linkset:linkcode %x:%x",
                      linkSet,linkCode);

            /* start T1 */
            tc.timerId = MTP3_SLT_T1;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->slt1 =
                TIMERS_StartUTimer(ITS_MTP3_ANSI_SRC,
                                   __ansi_slt_t1 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

            ln->sltFlags &= ~LINK_TEST_FIRST_ATTEMPT;
            ln->sltFlags |= LINK_TEST_SECOND_ATTEMPT;

            /* build SLTM, send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SLTM_SPEC | ln->linkSet->ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ln->linkSet->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ln->linkSet->lpc);

            dlen = strlen((char *)ln->testPattern);

            SLTM_HC0_SET_ANSI(osltm, SLTM_HC0_TST_ANSI);
            SLTM_HC1_SET_ANSI(osltm, SLTM_HC1_SLTM_ANSI);
            SLTM_LINK_TEST_SET_SLC_ANSI(osltm.data.linkTest, ln->linkCode);
            SLTM_LINK_TEST_SET_LENGTH_ANSI(osltm.data.linkTest, dlen);
            memcpy(osltm.data.linkTest.pattern, ln->testPattern,
                   dlen);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            SLTM_Encode_ANSI(&ev, &omtp3, &osltm);

            /* Increament Link Peg for SLTM Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_TX);

            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_SLTM_TX);
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLTM_TX);

            ret = HMRT_Main_ANSI(MTP3_SLT_SLTC,
                                 SMH_TRIGGER_TEST_CONTROL_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            return (ret);
        }
        else if (ln->sltFlags & LINK_TEST_SECOND_ATTEMPT)
        {

            MTP3_Alarm_ANSI(2508, __FILE__, __LINE__,
                     "SLT failed for linkset:linkcode %x:%x",
                      linkSet,linkCode);

            /* set test stopped */
            ln->sltFlags &= ~(LINK_TEST_FIRST_ATTEMPT|
                              LINK_TEST_SECOND_ATTEMPT);

            if (ln->slt2 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelTimer(ln->slt2);
                ln->slt2 = TIMER_BAD_SERIAL;
            }

            MTP2_SendData_ANSI(linkSet, linkCode, L3_L2_STOP, NULL, 0);

            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_SLT_FAILED);
            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_SLT_FAILED);

            LSAC_Main_ANSI(MTP3_SLT_SLTC,
                           SLM_TRIGGER_L2_OUT_OF_SERVICE,
                           NULL, 0,
                           linkSet, linkCode);

            return MGMT_Main_ANSI(MTP3_SLT_SLTC,
                                  MGMT_TRIGGER_LINK_TEST_FAILED,
                                  sif, len,
                                  linkSet, linkCode);
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
}
