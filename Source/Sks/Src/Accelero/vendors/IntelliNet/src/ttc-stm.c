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
 *  ID: $Id: ttc-stm.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:35  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:11  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.2  2005/04/05 11:27:24  sjaddu
 * LOG: Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.1  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/02/18 11:26:52  dsatish
 * LOG: Added Initial version file for TTC
 * LOG:
 * LOG: Revision 7.7.2.7.2.2.8.4  2005/01/25 11:36:14  snagesh
 * LOG: OAM Bug fixes for bugs 1419,1420
 * LOG:
 * LOG: Revision 7.7.2.7.2.2.8.3  2005/01/04 06:18:33  snagesh
 * LOG: Deleted generation of alarm 2470
 * LOG:
 * LOG: Revision 7.7.2.7.2.2.8.2  2004/12/31 07:34:55  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.7.2.7.2.2.8.1  2004/12/17 03:57:46  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.7.2.7.2.2  2004/08/11 09:59:33  kannanp
 * LOG: Changes for MTP3 pegs .
 * LOG:
 * LOG: Revision 7.7.2.7.2.1  2004/08/10 12:14:46  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.7.2.7  2003/12/12 11:57:43  kannanp
 * LOG: Fix bug 605 Peg Counts MSG_STATUS, CONGESTION not incrementing.
 * LOG:
 * LOG: Revision 7.7.2.6  2003/12/08 10:57:48  kannanp
 * LOG: Fix bug 582 Inhibition not working when done on both sides.
 * LOG:
 * LOG: Revision 7.7.2.5  2003/11/28 07:50:12  kannanp
 * LOG: Peg Fix patch from Current.
 * LOG:
 * LOG: Revision 7.7.2.4  2003/04/28 12:04:25  ttipatre
 * LOG: Add one more check to fix core problem for adding dummy linkSet and route.
 * LOG:
 * LOG: Revision 7.7.2.3  2003/04/23 05:09:02  ttipatre
 * LOG: Fix core problem after adding dummy linkSet and route.
 * LOG:
 * LOG: Revision 7.7.2.2  2003/02/21 01:42:34  randresol
 * LOG: Add more alarms
 * LOG:
 * LOG: Revision 7.7.2.1  2003/02/14 07:29:22  randresol
 * LOG: Enhancement for Pegs and Alarms
 * LOG:
 * LOG: Revision 7.7  2003/02/13 10:42:17  ttipatre
 * LOG: Pegs are Modified.
 * LOG:
 * LOG: Revision 7.6  2002/12/24 19:59:04  randresol
 * LOG: Fix message lost problem during change over
 * LOG:
 * LOG: Revision 7.5  2002/12/24 07:51:22  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.4  2002/11/20 11:52:13  ttipatre
 * LOG: fix the problem reported for not sending second CBD.
 * LOG:
 * LOG: Revision 7.3  2002/11/20 05:22:56  ttipatre
 * LOG: Modified to protocol specific alarms.
 * LOG:
 * LOG: Revision 7.2  2002/11/09 22:16:25  randresol
 * LOG: Fix various bugs
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.20  2002/08/26 17:13:07  yranade
 * LOG: Use C style comments.
 * LOG:
 * LOG: Revision 6.19  2002/08/22 01:14:09  randresol
 * LOG: fix pointer problem seen in 64bit mode. replace
 * LOG: rinfo = *(ROUTE_InfoPtr *)(tmp->data); by the safer
 * LOG: memcpy(&rinfo, tmp->data, sizeof(rinfo));
 * LOG:
 * LOG: Revision 6.18  2002/08/19 18:05:28  mmiers
 * LOG: China build debug
 * LOG:
 * LOG: Revision 6.17  2002/08/17 00:28:53  randresol
 * LOG: Fix Routing Label for MTP3 indications
 * LOG:
 * LOG: Revision 6.16  2002/08/16 22:07:09  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.15  2002/07/25 14:21:51  randresol
 * LOG: Fix bugs found during functional testing.
 * LOG:
 * LOG: Revision 6.14  2002/07/03 20:19:18  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.13  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.12  2002/06/13 20:36:19  ttipatre
 * LOG: Adding MTP3 Pegs and Alarms
 * LOG:
 * LOG: Revision 6.11  2002/05/17 19:50:33  randresol
 * LOG: Fix MTP3_STATUS to show USER_PART_INACCESSIBLE
 * LOG:
 * LOG: Revision 6.10  2002/05/15 15:06:48  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.9  2002/05/06 20:11:18  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.8  2002/04/29 22:53:14  randresol
 * LOG: Fix build problem
 * LOG:
 * LOG: Revision 6.7  2002/04/29 21:23:21  randresol
 * LOG: Add InterNode processing and shared booleans
 * LOG:
 * LOG: Revision 6.6  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.5  2002/03/27 19:00:37  randresol
 * LOG: Replace ItsEventToMTP3EventRec_ANSI by ItsEventToMTP3EventRec_CCITT
 * LOG:
 * LOG: Revision 6.4  2002/03/27 18:38:34  randresol
 * LOG: Remove Visual C++ warnings
 * LOG:
 * LOG: Revision 6.3  2002/03/26 18:28:23  randresol
 * LOG: crBuf, cocbBuf, rtrvBuf and route list are now in DSM
 * LOG:
 * LOG: Revision 6.2  2002/03/11 20:59:46  mmiers
 * LOG: It builds.  Now for the hard part.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.17  2002/02/19 21:51:53  mmiers
 * LOG: bounds checking.
 * LOG:
 * LOG: Revision 5.16  2002/02/19 19:29:20  mmiers
 * LOG: Fix bug spotted by Ricardo
 * LOG:
 * LOG: Revision 5.15  2002/02/12 23:29:04  mmiers
 * LOG: ISUP parser in place.
 * LOG:
 * LOG: Revision 5.14  2002/02/08 21:48:16  mmiers
 * LOG: Reorg complete.
 * LOG:
 * LOG: Revision 5.13  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.12  2002/02/01 20:25:56  mmiers
 * LOG: Fix subsystem call
 * LOG:
 * LOG: Revision 5.11  2002/01/29 19:58:01  mmiers
 * LOG: warning removal
 * LOG:
 * LOG: Revision 5.10  2002/01/29 19:56:26  mmiers
 * LOG: warning removal
 * LOG:
 * LOG: Revision 5.9  2002/01/09 21:24:15  mmiers
 * LOG: Correct the build settings, add XCO/XCA (SAAL changeover).
 * LOG:
 * LOG: Revision 5.8  2001/12/29 00:12:36  mmiers
 * LOG: ITU uses SLS key for SLC
 * LOG:
 * LOG: Revision 5.7  2001/12/28 20:31:05  mmiers
 * LOG: SLC is SLS in ITU
 * LOG:
 * LOG: Revision 5.6  2001/12/28 19:35:02  mmiers
 * LOG: Remove priority.  ITU doesn't have this.
 * LOG:
 * LOG: Revision 5.5  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.4  2001/12/11 23:49:53  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.3  2001/12/07 23:11:47  mmiers
 * LOG: Fix up ITU MTP3 (start testing it).
 * LOG:
 * LOG: Revision 5.2  2001/12/06 23:51:21  mmiers
 * LOG: Latest fixes.
 * LOG:
 *
 ****************************************************************************/

#undef ANSI
#undef CCITT
#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <its.h>
#include <its_dsm.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_assertion.h>
#include <its_types.h>
#include <its_timers.h>

#ident "$Id: ttc-stm.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

#if defined(PRC)
#include <china/snmm.h>
#include <china/sltm.h>
#include <china/mtp3.h>
#elif defined(TTC)
#include <japan/snmm.h>
#include <japan/sltm.h>
#include <japan/mtp3.h>
#else
#include <itu/snmm.h>
#include <itu/sltm.h>
#include <itu/mtp3.h>
#endif

#include "mtp3_intern.h"


/*
 * local globals: FIXME -- No longer needed; replaced by behaviors
 * 
static ITS_BOOLEAN       spRestarting = ITS_FALSE;
static ITS_BOOLEAN       fullRestartNeeded = ITS_TRUE;
static ITS_BOOLEAN       sendingStatus = ITS_FALSE;

 */

/*
 * T22: Timer at restarting SP waiting for signalling links to become
 *      available
 * T23: Timer at restarting SP, started after T22, waiting to receive
 *      all traffic restart allowed messages.
 * T24: Timer at restarting SP with transfer function, started after T23,
 *      waiting to broadcast all traffic restart allowed messages
 * T25: Timer at SP adjacent to restarting SP,
 *      waiting for traffic restart allowed message
 * T26: Timer at restarting SP waiting to repeat traffic restart waiting
 *      message
 * T27: Minimum duration of unavailability for full restart
 */
static ITS_SERIAL   t27 = TIMER_BAD_SERIAL;

/*.implementation:static
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
ITS_BOOLEAN
SPRestarting_CCITT()
{
    return BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_spRestarting);
}

/*.implementation:static
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
SPRestartingSet_CCITT(ITS_BOOLEAN isRestarting)
{

    BEHAVIORS_SetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_spRestarting,
                           isRestarting);

    BEHAVIORS_CommitSharedBehaviors(DSM_MGMT_REC_CCITT_MTP3_BEHAVIORS);

    return ITS_SUCCESS;
}

/*.implementation:static
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
ITS_BOOLEAN
FullRestartNeeded_CCITT()
{
    return BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors, 
                                  MTP3_B_fullRestartNeeded);
}

/*.implementation:static
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
FullRestartNeededSet_CCITT(ITS_BOOLEAN restartNeeded)
{

    BEHAVIORS_SetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_fullRestartNeeded,
                           restartNeeded);

    BEHAVIORS_CommitSharedBehaviors(DSM_MGMT_REC_CCITT_MTP3_BEHAVIORS);

    return ITS_SUCCESS;
  
}

/*.implementation:static
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
ITS_BOOLEAN
SendingStatus_CCITT()
{
    return BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_sendingStatus);
}

/*.implementation:static
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
SendingStatusSet_CCITT(ITS_BOOLEAN status) 
{
    BEHAVIORS_SetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_sendingStatus,
                           status);

    BEHAVIORS_CommitSharedBehaviors(DSM_MGMT_REC_CCITT_MTP3_BEHAVIORS);

    return ITS_SUCCESS;

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
 ****************************************************************************/
int 
STM_Main_CCITT(MTP3_SubSystems src, MTP3_SubSystems dest,
               STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    SNMM_MESSAGE *snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                              sizeof(ITS_OCTET)];

    MTP3_TRACE_ENTRY_CCITT(MTP3_STM, src, trigger, sif, len,
                          linkSet, linkCode);
    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }


    if (trigger == SRM_TRIGGER_L2_MSG)
    {
        switch (SNMM_HC0_GET(*snmm))
        {
        case SNMM_HC0_CHM:  /* changeover/changeback */
            switch (SNMM_HC1_GET(*snmm))
            {
            case SNMM_HC1_COO:   /* changeover */
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEOVER_ORDER,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_COA:   /* changeover ack */
                return TCOC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEOVER_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_XCO:   /* changeover */
                if (ln)
                {
                  /* Increament Link Peg for COO Received */
                  PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_RX);
                }
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEOVER_ORDER,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_XCA:   /* changeover ack */
                if (ln)
                {
                  /* Increament Link Peg for COA Received */
                  PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_RX);
                }
                return TCOC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEOVER_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_CBD:   /* changeback */
                return TCBC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEBACK_DECL,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_CBA:   /* changeback ack */
                return TCBC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_CHANGEBACK_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            default:
                MTP3_DEBUG(("Unknown HC1 code %d\n",
                            SNMM_HC1_GET(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_ECM:  /* emergency changeover */
            switch (SNMM_HC1_GET(*snmm))
            {
            case SNMM_HC1_ECO:   /* emergency changeover */
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_EMERG_CHANGEOVER_ORDER,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_ECA:   /* emergency changeover ack */
                return TCOC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_EMERG_CHANGEOVER_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            default:
                MTP3_DEBUG(("Unknown HC1 code %d\n",
                            SNMM_HC1_GET(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_MIM:  /* management inhibit */
            switch (SNMM_HC1_GET(*snmm))
            {
            case SNMM_HC1_LIN:   /* link inhibit */
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_INHIBIT_LINK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LUN:   /* link uninhibit */
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_UNINHIBIT_LINK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LIA:   /* link inhibit ack */
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_INHIBIT_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LUA:   /* link uninhibit ack */
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_UNINHIBIT_ACK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LID:   /* link inhibit denied */
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_INHIBIT_DENIED,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LFU:   /* link force uninhibit */
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_FORCE_UNINHIBIT_LINK,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LLI:   /* link local inhibit test */
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_LOCAL_INHIBIT_TEST,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_LRI:   /* link remote inhibit test */
                return TLAC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_REMOTE_INHIBIT_TEST,
                                      sif, len,
                                      linkSet, linkCode);

            default:
                MTP3_DEBUG(("Unknown HC1 code %d\n",
                            SNMM_HC1_GET(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_TRM:  /* traffic restart */
            switch (SNMM_HC1_GET(*snmm))
            {
            case SNMM_HC1_TRA:   /* traffic restart allowed */
                return TPRC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_TRAFFIC_RESTART_ALLOWED,
                                      sif, len,
                                      linkSet, linkCode);

            case SNMM_HC1_TRW:   /* traffer restart waiting */
                return TSRC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_TRAFFIC_RESTART_WAITING,
                                      sif, len,
                                      linkSet, linkCode);

            default:
                MTP3_DEBUG(("Unknown HC1 code %d\n",
                            SNMM_HC1_GET(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_UFC:  /* user flow control */
            switch (SNMM_HC1_GET(*snmm))
            {
            case SNMM_HC1_UPU:   /* user part unavailable */
                if (ln)
                {
                  /* Increament Link Peg for UPU Received */
                  PEG_IncrPeg(&ln->MTP3_LINK_PEGS,PEG_MTP3_LINK_UPU_RX );
                }
                return TSFC_Main_CCITT(MTP3_SMH_HMDT,
                                      STM_TRIGGER_UPU,
                                      sif, len,
                                      linkSet, linkCode);/* Pass UPU */

            default:
                MTP3_DEBUG(("Unknown HC1 code %d\n",
                            SNMM_HC1_GET(*snmm)));
                break;
            }
            break;

        default:
            MTP3_DEBUG(("Invalid HC0 code %d\n",
                        SNMM_HC0_GET(*snmm)));
            break;
        }
    }

    MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
    PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);

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
 ****************************************************************************/
static void
FindAlternateRoute(SS7_Destination *ent, MTP3_HEADER *mtp3,
                   int whichEntry, int firstMatch, int lastMatch,
                   ITS_OCTET linkSet, ITS_OCTET linkCode,
                   ITS_OCTET *nls, ITS_OCTET *nlc,
                   ITS_EVENT *ev)
{
    ITS_UINT i, cnt;
    int idx;
    ITS_OCTET alts[MAX_LINKS];
    ITS_BOOLEAN gotMatch = ITS_FALSE;

    /*
     * obtain alternative routing data
     */
    *nls = ITS_SS7_DEFAULT_LINK_SET;
    *nlc = ITS_SS7_DEFAULT_LINK_CODE;

    /*
     * Try to find an alternate link first.
     */
    cnt = 0;
    for (i = 0; i < ent->entries[whichEntry]->linkSet->numLinks; i++)
    {
        if (ent->entries[whichEntry]->isAllowed)
        {
            SS7_LinkPtr ln = ent->entries[whichEntry]->linkSet->links[i];

            if (ln && ln->linkCode != linkCode &&
                ln->isUp && ln->isAllowed && ln->testPassed)
            {
                *nls = ent->entries[whichEntry]->linkSet->linkSet;

                if (*nlc == ITS_SS7_DEFAULT_LINK_CODE)
                {
                    *nlc = ln->linkCode;
                    gotMatch = ITS_TRUE;
                }
                else
                {
                    alts[cnt] = ln->linkCode;
                    cnt++;
                }
            }
        }
    }

    /*
     * handle no alternate link
     */
    if (i == ent->entries[whichEntry]->linkSet->numLinks && !gotMatch)
    {
        /*
         * Do I have a route to this destination? Look at
         * all the ROUTE_Info records and determine if there is
         * at least one allowed route, whose link set is *not*
         * the same as the requester's.
         */
        for (idx = firstMatch; idx <= lastMatch; idx++)
        {

            if (ent->entries[idx]->isAllowed &&
                ent->entries[idx]->linkSet->linkSet != linkSet)
            {
                /*
                 * Try to find an alternate link first.
                 */
                for (i = 0;
                     i < ent->entries[idx]->linkSet->numLinks &&
                     i < MAX_LINKS;
                     i++)
                {
                    SS7_LinkPtr ln = ent->entries[idx]->linkSet->links[i];

                    if (ln && ln->linkCode != linkCode &&
                        ln->isUp && ln->isAllowed && ln->testPassed)
                    {
                        if (*nlc == ITS_SS7_DEFAULT_LINK_CODE)
                        {
                            *nls = (ITS_OCTET)ent->entries[idx]->linkSet->linkSet;

                            *nlc = ln->linkCode;

                            gotMatch = ITS_TRUE;
                        }
                        else
                        {
                            alts[cnt] = ln->linkCode;
                            cnt++;
                        }
                    }
                }

                /*
                 * make sure we have a link
                 */
                if (gotMatch)
                {
                    break;
                }
            }
        }

        /*
         * if no match is found, then there is no alternate route
         * data.  Indicate that by passing the input linkSet as
         * the matching entry (signalling no routing change).
         */
        if (idx > lastMatch)
        {
            MTP3_DEBUG(("No match found for alternate route  for linkSet "
                        "%d\n", linkSet));
            MTP3_Alarm_CCITT(2466, __FILE__, __LINE__,"%x",linkSet);
        }
    }

    /* build the event by hand.  It's weird anyway */
    ITS_EVENT_INIT(ev, ITS_MTP3_SRC,
                   2 * sizeof(MTP3_HEADER) + 3 * sizeof(ITS_OCTET) + cnt);

    ev->data[0] = MTP3_MSG_USER_DATA;
    memcpy(&ev->data[1], mtp3, sizeof(MTP3_HEADER));
    memcpy(&ev->data[sizeof(MTP3_HEADER) + sizeof(ITS_OCTET)],
           mtp3, sizeof(MTP3_HEADER));
    ev->data[2 * sizeof(MTP3_HEADER) + sizeof(ITS_OCTET)] = linkSet;
    ev->data[2 * sizeof(MTP3_HEADER) + 2 * sizeof(ITS_OCTET)] = linkCode;
    if (cnt)
    {
        memcpy(&ev->data[2 * sizeof(MTP3_HEADER) + 3 * sizeof(ITS_OCTET)],
               alts, cnt);
    }
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
 ****************************************************************************/
static int
SetLinkUnavailable(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    int ret = ITS_SUCCESS;
    SS7_LinkPtr ln;

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));
     
        return (ITS_EINVALIDARGS);
    }

    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                         STM_TRIGGER_LINK_UNAVAILABLE,
                         NULL, 0,
                         linkSet, linkCode);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Mark these states before sending link_unavailable to TCOC and TSRC */

    /*ln->stFlags |= LINK_COP; */

    if (SPRestarting_CCITT())
    {
        ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                             STM_TRIGGER_LINK_UNAVAILABLE,
                             NULL, 0,
                             linkSet, linkCode);

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Mark these states before sending link_unavailable to TCOC and TSRC */

        /* ln->availableState = LINK_UNAVAILABLE; */
    }
    else
    {
        /* ln->availableState = LINK_UNAVAILABLE; */
    }

    return (ret);
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
 ****************************************************************************/
static int
ForceUninhibitLink(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    SS7_LinkSetPtr ls;

    MTP3_TimerContext tc;
    MTP3_HEADER omtp3;
    SNMM_MESSAGE snmm;
    ITS_EVENT ev;

    int ret = ITS_SUCCESS;
    
    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));

        return (ITS_EINVALIDARGS);
    }

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

        return (ITS_EINVALIDARGS);
    }
    
    /* Build SNMM FORCE UNINHIBIT LINK */
    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
    MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

    SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
    SNMM_HC1_SET(snmm, SNMM_HC1_LFU);

    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

    SNMM_Encode(&ev, &omtp3, &snmm);
    
    /* Increament Link Peg for LFU Transmitted */
    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);

    ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                         SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                         ev.data, ev.len,
                         linkSet, linkCode);
    
    ITS_EVENT_TERM(&ev);

    /* Increament the peg for Link ForceUnInhibit */
     PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

    tc.timerId = MTP3_T13;
    tc.data.linkInfo.linkSet = linkSet;
    tc.data.linkInfo.linkCode = linkCode;

    ln->t13 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                 __ccitt_t13 * USEC_PER_MILLISEC,
                                 &tc, sizeof(MTP3_TimerContext));

    return ITS_SUCCESS;
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
 ****************************************************************************/
int
TLAC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    MTP3_HEADER omtp3;    
    SNMM_MESSAGE snmm, *snmm_ptr;
    ITS_UINT pc1;
    ITS_OCTET ni;
    ITS_EVENT ev;
    MTP3_TimerContext tc;
    int ret = ITS_SUCCESS;
    SS7_LinkPtr ln;
    SS7_LinkSetPtr ls;    
    ITS_OCTET i, j;
    SS7_Destination *dest;
    ROUTE_MatchInfo mi;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    ITS_OCTET nls, nlc;

    /* seems to want linkSet, linkCode */
    MTP3_TRACE_ENTRY_CCITT(MTP3_STM_TLAC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* For debugging now */
    ln = LINK_FindLink(linkSet, linkCode);
    if (ln == NULL)
    {
        MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));
    }
    else
    {
        MTP3_DEBUG(("TLAC state : %d, TLAC flags : %08x\n",
                    ln->availableState, ln->stFlags));
    }
    
    switch (trigger)
    {
    case STM_TRIGGER_INHIBIT_LINK:           /* from MGMT, HMDT */

        if (src == MTP3_SMH_HMDT)
        {
            ni = MTP3_HDR_GET_SIO(*mtp3);
            pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
            snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                        sizeof(ITS_OCTET));

            linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

            if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
            {

                MTP3_Alarm_CCITT(2471, __FILE__, __LINE__, 
                                 "Adjacent link %x not found", linkSet);

                MTP3_ERROR(("Can't find adjacent linkSet\n"));
 
                return (ITS_EINVALIDARGS);
            }

            linkCode = MTP3_RL_GET_SLS(mtp3->label);

            MTP3_DEBUG(("TLAC: linkSet = %d, linkCode = %d\n",
                         linkSet, linkCode));

            /* Linkset Pointer */
            ls = LINKSET_FindLinkSet(linkSet);
            if (ls == NULL)
            {
                MTP3_DEBUG(("Can't find link set %d\n", linkSet));
       
                return (ITS_EINVALIDARGS);
            }

            /* Link Pointer */
            ln = LINK_FindLink(linkSet, linkCode);
            if (ln == NULL)
            {
                MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

                return (ITS_EINVALIDARGS);
            }

            /* Increament Link Peg for LIN Received */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_RX);

            ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                 STM_TRIGGER_REMOTE_INHIBIT_REQUESTED,
                                 NULL, 0,
                                 ls->linkSet, ln->linkCode);

            MTP3_Alarm_CCITT(2516, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x",linkSet,linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }           
        }
        else if (src == MTP3_MGMT)
        {
            /* Increament Link Peg for LIN Received */
            /* PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_RX); */

            ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                 STM_TRIGGER_LOCAL_INHIBIT_REQUESTED,
                                 NULL, 0,
                                 linkSet, linkCode);

            MTP3_Alarm_CCITT(2517, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x",linkSet,linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }            
        }

        break;

    case STM_TRIGGER_UNINHIBITING_LINK:
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (src == MTP3_STM_TSRC)
        {
            if (ln->availableState == LINK_UNAVAILABLE)
            {
                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_LOC_BLOCKED) ||
                    (ln->stFlags & LINK_REM_BLOCKED))
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    if (ln->stFlags & LINK_LOC_INHIBITED)
                    {
                        /*Build and send SNMM UNINHIBIT LINK */

                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                        MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                        SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                        SNMM_HC1_SET(snmm, SNMM_HC1_LUN);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                        SNMM_Encode(&ev, &omtp3, &snmm);

                        /* Increament Link Peg for LUN Transmitted */
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

                        MTP3_Alarm_CCITT(2519, __FILE__, __LINE__, 
                               "linkset:linkcode %x:%x", linkSet,ln->linkCode);

                        ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                             SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                             ev.data, ev.len,
                                             linkSet, linkCode);

                        ITS_EVENT_TERM(&ev);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                        
                        tc.timerId = MTP3_T12;
                        tc.data.linkInfo.linkSet = linkSet;
                        tc.data.linkInfo.linkCode = linkCode;

                        ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                                     __ccitt_t12 * USEC_PER_MILLISEC,
                                                     &tc, sizeof(MTP3_TimerContext));

                        if (ln->stFlags & LINK_REM_INHIBITED)
                        {
                            ForceUninhibitLink(linkSet, linkCode);

                            ln->availableState = LINK_UNAVAILABLE;
                        }
                        else
                        {
                            ln->availableState = LINK_UNAVAILABLE;
                        }
                    }
                    else
                    {                            
                        ForceUninhibitLink(linkSet, linkCode);

                        ln->availableState = LINK_UNAVAILABLE;

                    }
                }
            }
        }

        break;

    case STM_TRIGGER_UNINHIBIT_LINK:         /* from HMDT, MGMT, TSRC */

        if (src == MTP3_SMH_HMDT)
        {                        
            ni = MTP3_HDR_GET_SIO(*mtp3);
            pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
            snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                                sizeof(ITS_OCTET));

            linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

            if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
            {
                MTP3_ERROR(("Can't find adjacent linkSet\n"));

                return (ITS_EINVALIDARGS);
            }

            linkCode = MTP3_RL_GET_SLS(mtp3->label);

            /* Linkset Pointer */
            ls = LINKSET_FindLinkSet(linkSet);
            if (ls == NULL)
            {
                MTP3_DEBUG(("Can't find link set %d\n", linkSet));

                return (ITS_EINVALIDARGS);
            }

            /* Link Pointer */
            ln = LINK_FindLink(linkSet, linkCode);
            if (ln == NULL)
            {
                MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

                return (ITS_EINVALIDARGS);
            }

            /* Increament Link Peg for LUN Received */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_RX);

            if (ln->availableState == LINK_AVAILABLE)
            {
                /* Build and send SNMM UNINHIBIT ACK */
                
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                SNMM_HC1_SET(snmm, SNMM_HC1_LUA);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for LUA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_TX);

                ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Increament the peg for Link UnInhibit */
                PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);

                /* Stop T13 and Cancel T13 retry */
                ln->timerRetryState.t13RetryOnOff = ITS_FALSE;
                TIMERS_CancelSharedTimer(ln->t13);
                ln->t13 = TIMER_BAD_SERIAL;

               /* Increament the peg for Link ForceUnInhibit */
                PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

                ln->availableState = LINK_AVAILABLE;
            }
            else if (ln->availableState == LINK_UNAVAILABLE)
            {
                ln->stFlags &= ~LINK_REM_INHIBITED;

                /* Build and send SNMM UNINHIBIT ACK */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                SNMM_HC1_SET(snmm, SNMM_HC1_LUA);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for LUA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_TX);

                ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                    SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                    ev.data, ev.len,
                                    linkSet, linkCode);

                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_LINK_REMOTE_UNINHIBIT,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Increament the peg for Link UnInhibit */
                PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);

                /* Stop T13 and Cancel T13 retry */
                ln->timerRetryState.t13RetryOnOff = ITS_FALSE;
                TIMERS_CancelSharedTimer(ln->t13);

               /* Increament the peg for Link ForceUnInhibit */
                PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

                ln->t13 = TIMER_BAD_SERIAL;

                if (ln->stFlags & LINK_LOC_INHIBITED)
                {
                    ln->availableState = LINK_UNAVAILABLE;

                }
                else
                {
                    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_CANCEL_LINK_INHIBITED,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    if ((ln->stFlags & LINK_FAILED) ||
                        (ln->stFlags & LINK_LOC_BLOCKED) ||
                        (ln->stFlags & LINK_REM_BLOCKED))
                    {
                        ln->availableState = LINK_UNAVAILABLE;

                    }
                    else
                    {
                        ln->stFlags |= LINK_CBP;
                        ln->availableState = LINK_AVAILABLE;

                        ret = TCBC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }                        

                        ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                    
                        if (SPRestarting_CCITT())
                        {
                            ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                                 STM_TRIGGER_LINK_AVAILABLE,
                                                 NULL, 0,
                                                 linkSet, linkCode);

                            if (ret != ITS_SUCCESS)
                            {
                                break;
                            }                            
                        }                              
                    }
                }
            }
        }
        else if (src == MTP3_MGMT)
        {
            /* Linkset Pointer */
            ls = LINKSET_FindLinkSet(linkSet);
            if (ls == NULL)
            {
                MTP3_DEBUG(("Can't find link set %d\n", linkSet));

                return (ITS_EINVALIDARGS);
            }

            /* Link Pointer */
            ln = LINK_FindLink(linkSet, linkCode);
            if (ln == NULL)
            {
                MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

                return (ITS_EINVALIDARGS);
            }

            /* Increament Link Peg for LUN Received */
            /* PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_RX); */

            if (ln->availableState == LINK_AVAILABLE)
            {
                ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_UNINHIBIT_LINK,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
            }
            else if (ln->availableState == LINK_UNAVAILABLE)
            {
                /* Mark management request */

                ln->stFlags |= LINK_MGMT_UNINHIBIT_REQ;

                ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_UNINHIBIT_REQUEST,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* MLM: Seems to be a brain-fart: ln->availableState = LINK_AVAILABLE; */
            }
        }
        break;
    
    case STM_TRIGGER_LOCAL_INHIBIT_ALLOWED:  /* from TSRC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));
  
            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            /* Build SNMM INHIBIT LINK */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
            SNMM_HC1_SET(snmm, SNMM_HC1_LIN);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LIN Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_TX);

            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_SUCCESS);

            MTP3_Alarm_CCITT(2518, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x",linkSet,ln->linkCode);

            ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->stFlags |= LINK_LIP;

            tc.timerId = MTP3_T14;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t14 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                         __ccitt_t14 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Build SNMM INHIBIT LINK */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
            SNMM_HC1_SET(snmm, SNMM_HC1_LIN);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LIN Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_TX);

            ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }
            
            tc.timerId = MTP3_T14;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t14 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                         __ccitt_t14 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_UNAVAILABLE;
        }
        break;

    case STM_TRIGGER_LOCAL_INHIBIT_DENIED:   /* from TSRC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        MTP3_Alarm_CCITT(2520, __FILE__, __LINE__,"linkset:linkcode %x:%x",
                          linkSet,linkCode);

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT_DNY);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_DENY);

        if (ln->availableState == LINK_AVAILABLE)
        {
            ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                 MGMT_TRIGGER_INHIBIT_DENIED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                 MGMT_TRIGGER_INHIBIT_DENIED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_UNAVAILABLE;

        }
        break;

    case STM_TRIGGER_INHIBIT_ALLOWED:  /* from HMDT */
        break;

    case STM_TRIGGER_INHIBIT_DENIED:   /* from HMDT */
        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }
        
        /* Increament Link Peg for LID Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_RX);

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT_DNY);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_DENY);

        if (ln->availableState == LINK_AVAILABLE)
        {
            ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                 MGMT_TRIGGER_INHIBIT_DENIED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->stFlags &= ~LINK_LIP;

            /* Stop T14 */
            TIMERS_CancelSharedTimer(ln->t14);
            ln->t14 = TIMER_BAD_SERIAL;

            ln->stFlags &= ~LINK_INHIBIT_RETRY;

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                 MGMT_TRIGGER_INHIBIT_DENIED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_UNAVAILABLE;

        }
        break;

    case STM_TRIGGER_REMOTE_INHIBIT_ALLOWED: /* from TSRC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_SUCCESS);

        if (ln->availableState == LINK_AVAILABLE)
        {
            ln->stFlags |= LINK_REM_INHIBITED;

            /* Build SNMM INHIBIT ACK and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
            SNMM_HC1_SET(snmm, SNMM_HC1_LIA);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LIA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_TX);


            ret = HMRT_Main_CCITT(MTP3_STM_TLAC, SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_INHIBITED,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = MGMT_Main_CCITT(MTP3_STM_TLAC,
                                 MGMT_TRIGGER_LINK_INHIBITED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            /* Increament the peg for Link Inhibit */
            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);

            /* Start T21 */
            tc.timerId = MTP3_T21;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t21 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                         __ccitt_t21 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            if (ln->stFlags & LINK_CBP)
            {
                ln->availableState = LINK_UNAVAILABLE;

            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
                ln->stFlags |= LINK_COP;


                ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_LINK_UNAVAILABLE,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ret = SetLinkUnavailable(linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Increament the counter for Link Unavailable */
                PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);

                /* FIX: isUp should be re-set to true to allow SLT 
                 *      messages on that link.
                 */
                 LINK_SetLinkState(ln, ITS_TRUE);
            }          
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags |= LINK_REM_INHIBITED;

            /* Build SNMM INHIBIT ACK and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
            SNMM_HC1_SET(snmm, SNMM_HC1_LIA);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LIA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_TX);

            ret = HMRT_Main_CCITT(MTP3_STM_TLAC, SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_INHIBITED,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = MGMT_Main_CCITT(MTP3_STM_TLAC,
                                 MGMT_TRIGGER_LINK_INHIBITED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            /* Increament the peg for Link Inhibit */
            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);

            /* Start T21 */
            tc.timerId = MTP3_T21;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t21 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                         __ccitt_t21 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_UNAVAILABLE;

        }
        break;

    case STM_TRIGGER_REMOTE_INHIBIT_DENIED:  /* from TSRC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        MTP3_Alarm_CCITT(2521, __FILE__, __LINE__,
                        "linkset:linkcode %x:%x",linkSet,linkCode);

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT_DNY);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_DENY);

        if (ln->availableState == LINK_AVAILABLE)
        {
            /* Build SNMM INHIBIT DENIED and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
            SNMM_HC1_SET(snmm, SNMM_HC1_LID);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LID Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_TX);

            ret = HMRT_Main_CCITT(MTP3_STM_TLAC, SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Build SNMM INHIBIT DENIED and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
            SNMM_HC1_SET(snmm, SNMM_HC1_LID);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for LID Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_TX);

            ret = HMRT_Main_CCITT(MTP3_STM_TLAC, SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_UNAVAILABLE;

        }
        break;

    case STM_TRIGGER_INHIBIT_ACK:            /* from HMDT */
        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LIA Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_RX);

        if (ln->availableState == LINK_AVAILABLE)
        {

            if (!(ln->stFlags & LINK_LIP))
            {
                ln->availableState = LINK_AVAILABLE;
                return ITS_SUCCESS;
            }

            /* local inhibit is in progress */

            ln->stFlags |= LINK_LOC_INHIBITED;

            ln->stFlags &= ~LINK_LIP;

            ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_INHIBITED,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                    break;
            }

            ret = MGMT_Main_CCITT(MTP3_STM_TLAC,
                                 MGMT_TRIGGER_LINK_INHIBITED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

           /* Stop T14 */
            TIMERS_CancelSharedTimer(ln->t14);
            ln->t14 = TIMER_BAD_SERIAL;
  
           /* Increament the peg for Link Inhibit */
            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT); 

            /* Start T20 */
            tc.timerId = MTP3_T20;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t20 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                         __ccitt_t20 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->stFlags &= ~LINK_INHIBIT_RETRY;

            if (ln->stFlags & LINK_CBP)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
                ln->stFlags |= LINK_COP;

                ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_LINK_UNAVAILABLE,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ret = SetLinkUnavailable(linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* FIX: isUp should be re-set to true to allow SLT 
                 *      messages on that link.
                 */
                 LINK_SetLinkState(ln, ITS_TRUE);

                /* Increament the counter for Link Unavailable */
                PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
            }          
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags |= LINK_LOC_INHIBITED;

            ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_INHIBITED,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = MGMT_Main_CCITT(MTP3_STM_TLAC,
                                 MGMT_TRIGGER_LINK_INHIBITED,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            /* Stop T14 */
            TIMERS_CancelSharedTimer(ln->t14);
            ln->t14 = TIMER_BAD_SERIAL;

            /* Increament the peg for Link Inhibit */
            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);

            /* Start T20 */
            tc.timerId = MTP3_T20;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t20 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                         __ccitt_t20 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->stFlags &= ~LINK_INHIBIT_RETRY;
            
            ln->availableState = LINK_UNAVAILABLE;
        }
        break;

    case STM_TRIGGER_UNINHIBIT_ACK:            /* from HMDT */

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }


        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));
  
            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LUA Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_RX);

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_UNINHIBIT_SUCCESS);

        if (ln->availableState == LINK_AVAILABLE)
        {
            /* Stop T12 */
            TIMERS_CancelSharedTimer(ln->t12);
            ln->t12 = TIMER_BAD_SERIAL;

            /* Increament the peg for Link UnInhibit */
            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);

            /* Cancel T13 retry */

            ln->timerRetryState.t13RetryOnOff = ITS_FALSE;

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Cancel locally inhibited management request */

/** FIXME: which one is valid */
            ln->stFlags &= ~LINK_MGMT_UNINHIBIT_REQ;

            ln->stFlags &= ~LINK_LOC_INHIBITED;
/** FIXME: END **/

            ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                 MGMT_TRIGGER_UNINHIBIT_LINK,
                                 sif, len,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }            

            /* Stop T12 */
            TIMERS_CancelSharedTimer(ln->t12);
            ln->t12 = TIMER_BAD_SERIAL;

            /* Increament the peg for Link UnInhibit */
            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);

            /* Cancel T12 retry */

            ln->timerRetryState.t12RetryOnOff = ITS_FALSE;

            if (ln->stFlags & LINK_REM_INHIBITED)
            {
                ln->availableState = LINK_UNAVAILABLE;

            }
            else
            {
                ret = TSRC_Main_CCITT(MTP3_STM_TLAC, 
                                     STM_TRIGGER_CANCEL_LINK_INHIBITED,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_LOC_BLOCKED) ||
                    (ln->stFlags & LINK_REM_BLOCKED))
                {
                    ln->availableState = LINK_UNAVAILABLE;

                }
                else
                {
                    ln->stFlags |= LINK_CBP;
                    ln->availableState = LINK_AVAILABLE;

                    ret = TCBC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                
                    if (SPRestarting_CCITT())
                    {
                        ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }                        
                    }                         
                }            
            }
        }

        break;

    case STM_TRIGGER_INHIBIT_POSSIBLE:       /* from TSRC */
        break;

    case STM_TRIGGER_INHIBIT_IMPOSSIBLE:     /* from TSRC */
        break;

    case STM_TRIGGER_UNINHIBIT_POSSIBLE:      /* from TSRC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Build SNMM UNINHIBIT LINK and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
            SNMM_HC1_SET(snmm, SNMM_HC1_LUN);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);
            
            /* Increament Link Peg for LUN Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

            MTP3_Alarm_CCITT(2519, __FILE__, __LINE__, 
                             "linkset:linkcode %x:%x", linkSet,ln->linkCode);

            ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }
            
            /* Start T12 */
            tc.timerId = MTP3_T12;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                         __ccitt_t12 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_UNAVAILABLE;

        }

        break;

    case STM_TRIGGER_UNINHIBIT_IMPOSSIBLE:    /* from TSRC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_INHIBIT_FAILURE);

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            if ((ln->stFlags & LINK_FAILED) ||
                (ln->stFlags & LINK_LOC_BLOCKED) ||
                (ln->stFlags & LINK_REM_BLOCKED))
            {
                ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Cancel Management request */
                ln->stFlags &= ~LINK_MGMT_UNINHIBIT_REQ;

                ln->availableState = LINK_UNAVAILABLE;

            }
            else
            {
               /* Build SNMM UNINHIBIT LINK and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                SNMM_HC1_SET(snmm, SNMM_HC1_LUN);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LUN Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

                MTP3_Alarm_CCITT(2519, __FILE__, __LINE__, 
                                "linkset:linkcode %x:%x", linkSet,ln->linkCode);

                ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
                
                /* Start T12 */
                tc.timerId = MTP3_T12;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                             __ccitt_t12 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));

                ln->availableState = LINK_UNAVAILABLE;

            }
        }

        break;

    case STM_TRIGGER_ADJACENT_SP_RESTARTING: /* from TSRC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        /* Here you may not get a linkCode. So loop for all the links in this linkSet */

        for (j = 0; j < ls->numLinks; j++)
        {            
            ln = ls->links[j];        

            if (ln->availableState == LINK_AVAILABLE)
            {
                /*
                 * Action: mark adjacent SP restarting.  Not necessary, TSRC
                 * marks this.
                 */

                /*Cancel all inhibiting marks and timers */

                if (ln->stFlags & LINK_LOC_INHIBITED)
                {
                    ln->stFlags &= ~LINK_LOC_INHIBITED;
                }
            
                if (ln->stFlags & LINK_REM_INHIBITED)
                {
                    ln->stFlags &= ~LINK_REM_INHIBITED;
                }

                if (ln->stFlags & LINK_LIP)
                {
                    ln->stFlags &= ~LINK_LIP;
                }

                if (ln->stFlags & LINK_RIP)
                {
                    ln->stFlags &= ~LINK_RIP;
                }

                /* Cancel T12, T13, T14, T20, T21 */

                /* Stop T12 */
                TIMERS_CancelSharedTimer(ln->t12);
                ln->t12 = TIMER_BAD_SERIAL;
            
                /* Stop T13 */
                TIMERS_CancelSharedTimer(ln->t13);
                ln->t13 = TIMER_BAD_SERIAL;

                /* Stop T14 */
                TIMERS_CancelSharedTimer(ln->t14);
                ln->t14 = TIMER_BAD_SERIAL;

                /* Stop T20 */
                TIMERS_CancelSharedTimer(ln->t20);
                ln->t20 = TIMER_BAD_SERIAL;

                /* Stop T21 */
                TIMERS_CancelSharedTimer(ln->t21);
                ln->t21 = TIMER_BAD_SERIAL;

                ln->availableState = LINK_AVAILABLE;
            }
            else if (ln->availableState == LINK_UNAVAILABLE)
            {
                /*
                 * Action: mark adjacent SP restarting.  Not necessary, TSRC
                 * marks this.
                 */

                /*Cancel all inhibiting marks and timers */

                if (ln->stFlags & LINK_LOC_INHIBITED)
                {
                    ln->stFlags &= ~LINK_LOC_INHIBITED;
                }
            
                if (ln->stFlags & LINK_REM_INHIBITED)
                {
                    ln->stFlags &= ~LINK_REM_INHIBITED;
                }

                if (ln->stFlags & LINK_LIP)
                {
                    ln->stFlags &= ~LINK_LIP;
                }

                if (ln->stFlags & LINK_RIP)
                {
                    ln->stFlags &= ~LINK_RIP;
                }

                /* Cancel T12, T13, T14, T20, T21 */

                /* Stop T12 */
                TIMERS_CancelSharedTimer(ln->t12);
                ln->t12 = TIMER_BAD_SERIAL;
            
                /* Stop T13 */
                TIMERS_CancelSharedTimer(ln->t13);
                ln->t13 = TIMER_BAD_SERIAL;

                /* Stop T14 */
                TIMERS_CancelSharedTimer(ln->t14);
                ln->t14 = TIMER_BAD_SERIAL;

                /* Stop T20 */
                TIMERS_CancelSharedTimer(ln->t20);
                ln->t20 = TIMER_BAD_SERIAL;

                /* Stop T21 */
                TIMERS_CancelSharedTimer(ln->t21);
                ln->t21 = TIMER_BAD_SERIAL;

                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_LOC_BLOCKED) ||
                    (ln->stFlags & LINK_REM_BLOCKED))
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ret = TCBC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         ls->linkSet, ln->linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         ls->linkSet, ln->linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         ls->linkSet, ln->linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_AVAILABLE;
                }
            }
        }

        break;

    case STM_TRIGGER_ADJACENT_SP_RESTARTED:  /* from TSRC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            /*
             * Action: cancel adjacent SP restarting.  Not necessary, TSRC
             * marks this.
             */
            if (ls->adjRestart)
            {
                ret = TCBC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_LINK_AVAILABLE,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->stFlags |= LINK_CBP;
            }

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            /*
             * Action: cancel adjacent SP restarting.  Not necessary, TSRC
             * marks this.
             */

            ln->availableState = LINK_UNAVAILABLE;
        }

        break;

    case STM_TRIGGER_CHANGEBACK_TERMINATED:  /* from TCBC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            ln->stFlags &= ~LINK_CBP;
            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags &= ~LINK_CBP;

            if (src == MTP3_STM_TCBC)
            {
                if (ln->stFlags & LINK_COO)
                {
                    ln->availableState = LINK_UNAVAILABLE;
                    ln->stFlags |= LINK_COP;


                    ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_CHANGEOVER_ORDER,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    ln->stFlags &= ~(LINK_ECOO|LINK_COO);

                    ret = SetLinkUnavailable(linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    /* Increament the counter for Link Unavailable */
                    PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
                }
                else
                {
                    if (ln->stFlags & LINK_ECOO)
                    {
                        ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_EMERG_CHANGEOVER_ORDER,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                    }
                    else
                    {
                        ln->availableState = LINK_UNAVAILABLE;
                        ln->stFlags |= LINK_COP;


                        ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_UNAVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                    }

                    ln->stFlags &= ~(LINK_ECOO|LINK_COO);

                    ret = SetLinkUnavailable(linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }                         
                    /* Increament the counter for Link Unavailable */
                    PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
                }
            }
            else
            {
                /* Nothing to do!! */
            }
        }
        break;

    case STM_TRIGGER_CHANGEOVER_EXECUTED:    /* from TCOC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags &= ~LINK_COP;

            if (ln->stFlags & LINK_RTB_CLEAR_REQ)
            {
                ret = LSAC_Main_CCITT(MTP3_STM_TLAC,
                                     SLM_TRIGGER_CLEAR_RTB,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Mark RTB clear pending */
                ln->stFlags |= LINK_RTB_CLEAR_PENDING;

                /* Cancel RTB clear request */
                ln->stFlags &= ~LINK_RTB_CLEAR_REQ;

                ln->availableState = LINK_UNAVAILABLE;

            }
            else
            {
                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_REM_BLOCKED) ||
                    (ln->stFlags & LINK_LOC_INHIBITED) ||
                    (ln->stFlags & LINK_REM_INHIBITED))
                {
                    ln->availableState = LINK_UNAVAILABLE;

                }
                else
                {
                    ln->stFlags |= LINK_CBP;
                    ln->availableState = LINK_AVAILABLE;

                    ret = TCBC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    if (SPRestarting_CCITT())
                    {
                        ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                    }                    
                }
            }
        }
        break;

    case STM_TRIGGER_CHANGEOVER_NOT_REQD:    /* from TCOC */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags &= ~LINK_COP;

            if ((ln->stFlags & LINK_FAILED) ||
                (ln->stFlags & LINK_REM_BLOCKED) ||
                (ln->stFlags & LINK_LOC_INHIBITED) ||
                (ln->stFlags & LINK_REM_INHIBITED))
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_AVAILABLE;

                ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_LINK_AVAILABLE,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
                
                if (SPRestarting_CCITT())
                {
                    ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }                    
                }                
            }
        }
        break;

    case STM_TRIGGER_LINK_FAILED:            /* from SLM */

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            MTP3_DEBUG(("TLAC: LINK_FAILED: link was available\n"));

            ln->stFlags |= LINK_FAILED;

            if (ln->stFlags & LINK_CBP)
            {
                MTP3_DEBUG(("TLAC: LINK_FAILED: changeback in progress\n"));

                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
                ln->stFlags |= LINK_COP;

                ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_LINK_UNAVAILABLE,
                                     NULL, 0,
                                     linkSet, linkCode);

#if 0
                if (ret != ITS_SUCCESS)
                {
                    break;
                }
#endif

                ret = SetLinkUnavailable(linkSet, linkCode);

#if 0
                if (ret != ITS_SUCCESS)
                {
                    break;
                }
#endif
                /* Increament the counter for Link Unavailable */
                PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_SL_UNAVAILABLE);
            }                    
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            MTP3_DEBUG(("TLAC: LINK_FAILED: link was unavailable\n"));

            ln->stFlags |= LINK_FAILED;

            ln->stFlags &= ~LINK_REM_BLOCKED;

            ln->availableState = LINK_UNAVAILABLE;


            /*
             * we MUST do this.  LSAC will ignore it if it's
             * not in the right state, but if we fail to do
             * this LSAC will NOT start restoration.
             */
            LSAC_Main_CCITT(MTP3_STM_TLAC,
                           SLM_TRIGGER_STM_READY,
                           NULL, 0,
                           linkSet, linkCode);
        }

        break;

    case STM_TRIGGER_LINK_IN_SERVICE:        /* from SLM */
        MTP3_Alarm_CCITT(2526, __FILE__, __LINE__,
               "linkset:linkcode %x:%x",linkSet,linkCode);

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Cancel link failed */

        ln->stFlags &= ~LINK_FAILED;
            
        if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (!(ln->stFlags & LINK_LOC_INHIBITED) &&
                !(ln->stFlags & LINK_REM_INHIBITED))
            {
                if (ln->stFlags & LINK_COP)
                {
                    ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ln->stFlags |= LINK_CBP;
                    ln->availableState = LINK_AVAILABLE;

                    ret = TCBC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }                    

                    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    if (SPRestarting_CCITT())
                    {
                        ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }                        
                    }
                    
                }                
            }
        }

        break;

    case STM_TRIGGER_RP_OUTAGE:              /* from SLM */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        MTP3_Alarm_CCITT(2403, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        ln->stFlags |= LINK_REM_BLOCKED;

        if (ln->stFlags & LINK_CBP)
        {
            ln->availableState = LINK_UNAVAILABLE;
        }
        else
        {
            ln->availableState = LINK_UNAVAILABLE;
            ln->stFlags |= LINK_COP;

            ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                 STM_TRIGGER_LINK_UNAVAILABLE,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ret = SetLinkUnavailable(linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }
            /* Increament the counter for Link Unavailable */
            PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
        }                    
        break;

    case STM_TRIGGER_RP_RECOVERD:            /* from SLM */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        MTP3_Alarm_CCITT(2404, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            ln->stFlags &= ~LINK_REM_BLOCKED;

            /*If RTB or RB clear pending */
            if (ln->stFlags & LINK_RTB_CLEAR_PENDING ||
                ln->stFlags & LINK_RB_CLEAR_PENDING)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                if (ln->stFlags & LINK_COP)
                {
                    if ((ln ->stFlags & LINK_LOC_INHIBITED) ||
                        (ln ->stFlags & LINK_REM_INHIBITED))
                    {
                        /* Mark RTB clear request */
                        ln->stFlags |= LINK_RTB_CLEAR_REQ;

                        ln->availableState = LINK_UNAVAILABLE;
                    }
                    else
                    {
                        /* If Adjacent SP restaring */
                        if (ls->adjRestart)
                        {
                            /* Mark RTB clear request */
                            ln->stFlags |= LINK_RTB_CLEAR_REQ;

                            ln->availableState = LINK_UNAVAILABLE;
                        }
                        else
                        {
                            ret = LSAC_Main_CCITT(MTP3_STM_TLAC,
                                                 SLM_TRIGGER_RESUME,
                                                 NULL, 0,
                                                 linkSet, linkCode);

                            if (ret != ITS_SUCCESS)
                            {
                                break;
                            }

                            ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                                 STM_TRIGGER_LINK_AVAILABLE,
                                                 NULL, 0,
                                                 linkSet, linkCode);

                            if (ret != ITS_SUCCESS)
                            {
                                break;
                            }

                            ln->availableState = LINK_UNAVAILABLE;
                        }
                    }
                }
                else /* else for 'is COP?' */
                {
                    ret = LSAC_Main_CCITT(MTP3_STM_TLAC,
                                         SLM_TRIGGER_CLEAR_RTB,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_UNAVAILABLE;
                }
            }
        }

        break;

    case STM_TRIGGER_RB_CLEARED:             /* from SLM */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Cancel RB clear pending */
            ln->stFlags &= ~LINK_RB_CLEAR_PENDING;
            
            /* If RTB clear pending */
            if (ln->stFlags | LINK_RTB_CLEAR_PENDING)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {

                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_REM_BLOCKED) ||
                    (ln->stFlags & LINK_LOC_INHIBITED) ||
                    (ln->stFlags & LINK_REM_INHIBITED))
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ln->stFlags |= LINK_CBP;
                    ln->availableState = LINK_AVAILABLE;

                    ret = TCBC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    if (SPRestarting_CCITT())
                    {
                        ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }                        
                    }                    
                }
            }
        }

        break;

    case STM_TRIGGER_RTB_CLEARED:            /* from SLM */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            /* Cancel RTB clear pending */
            ln->stFlags &= ~LINK_RTB_CLEAR_PENDING;
            
            /* If RB clear pending */
            if (ln->stFlags | LINK_RB_CLEAR_PENDING)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {

                if ((ln->stFlags & LINK_FAILED) ||
                    (ln->stFlags & LINK_REM_BLOCKED) ||
                    (ln->stFlags & LINK_LOC_INHIBITED) ||
                    (ln->stFlags & LINK_REM_INHIBITED))
                {
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ln->stFlags |= LINK_CBP;
                    ln->availableState = LINK_AVAILABLE;

                    ret = TCBC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    
                    if (SPRestarting_CCITT())
                    {
                        ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }                        
                    }                    
                }
            }
        }

        break;

    case STM_TRIGGER_RESTART_BEGIN:          /* from TPRC */        

        for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
        {
            if ((ls = LINKSET_FindLinkSet(i)) == NULL ||
                 ls->adjacent == 0)
            {
                continue;
            }

            for (j = 0; j < ls->numLinks; j++)
            {                 
                ln = ls->links[j];

                if (ln->availableState == LINK_AVAILABLE)
                {
                    /* Mark SP restaring */
                    /* this action is taken by TPRC */

                    /*Cancel all inhibiting marks and timers */

                    if (ln->stFlags & LINK_LOC_INHIBITED)
                    {
                        ln->stFlags &= ~LINK_LOC_INHIBITED;
                    }
            
                    if (ln->stFlags & LINK_REM_INHIBITED)
                    {
                        ln->stFlags &= ~LINK_REM_INHIBITED;
                    }

                    if (ln->stFlags & LINK_LIP)
                    {
                        ln->stFlags &= ~LINK_LIP;
                    }

                    if (ln->stFlags & LINK_RIP)
                    {
                        ln->stFlags &= ~LINK_RIP;
                    }

                    /* Stop T12 */
                    TIMERS_CancelSharedTimer(ln->t12);
                    ln->t12 = TIMER_BAD_SERIAL;
            
                    /* Stop T13 */
                    TIMERS_CancelSharedTimer(ln->t13);
                    ln->t13 = TIMER_BAD_SERIAL;

                    /* Stop T14 */
                    TIMERS_CancelSharedTimer(ln->t14);
                    ln->t14 = TIMER_BAD_SERIAL;

                    /* Stop T20 */
                    TIMERS_CancelSharedTimer(ln->t20);
                    ln->t14 = TIMER_BAD_SERIAL;

                    /* Stop T21 */
                    TIMERS_CancelSharedTimer(ln->t21);
                    ln->t21 = TIMER_BAD_SERIAL;
            
                    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         ls->linkSet, ln->linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_LINK_AVAILABLE,
                                         NULL, 0,
                                         ls->linkSet, ln->linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_AVAILABLE;
                }
                else if (ln->availableState == LINK_UNAVAILABLE)
                {
                    /* Mark SP restaring */
                    /* this action is taken by TPRC */

                    /*Cancel all inhibiting marks and timers */

                    if (ln->stFlags & LINK_LOC_INHIBITED)
                    {
                        ln->stFlags &= ~LINK_LOC_INHIBITED;
                    }
            
                    if (ln->stFlags & LINK_REM_INHIBITED)
                    {
                        ln->stFlags &= ~LINK_REM_INHIBITED;
                    }

                    if (ln->stFlags & LINK_LIP)
                    {
                        ln->stFlags &= ~LINK_LIP;
                    }

                    if (ln->stFlags & LINK_RIP)
                    {
                        ln->stFlags &= ~LINK_RIP;
                    }

                    /* Stop T12 */
                    TIMERS_CancelSharedTimer(ln->t12);
                    ln->t12 = TIMER_BAD_SERIAL;
            
                    /* Stop T13 */
                    TIMERS_CancelSharedTimer(ln->t13);
                    ln->t13 = TIMER_BAD_SERIAL;

                    /* Stop T14 */
                    TIMERS_CancelSharedTimer(ln->t14);
                    ln->t14 = TIMER_BAD_SERIAL;

                    /* Stop T20 */
                    TIMERS_CancelSharedTimer(ln->t20);
                    ln->t14 = TIMER_BAD_SERIAL;

                    /* Stop T21 */
                    TIMERS_CancelSharedTimer(ln->t21);
                    ln->t21 = TIMER_BAD_SERIAL;

                   /*
                    * if fullRestart and spRestarting, assume the links are down
                    * until proven otherwise.  Otherwise, check the status we think
                    * they have.
                    */
                    if ((FullRestartNeeded_CCITT() && SPRestarting_CCITT()) ||
                        (ln->stFlags & LINK_FAILED) ||
                        (ln->stFlags & LINK_LOC_BLOCKED) ||
                        (ln->stFlags & LINK_REM_BLOCKED))
                    {
                        /* If LPO */
                        if (SPRestarting_CCITT())
                        {
                            /* If LPO duration > T1 OR unknown */
                            if (ITS_TRUE)
                            {
                                ret = LSAC_Main_CCITT(MTP3_STM_TLAC,
                                                     SLM_TRIGGER_CLEAR_BUFFERS,
                                                     NULL, 0,
                                                     ls->linkSet,
                                                     ln->linkCode);

                                if (ret != ITS_SUCCESS)
                                {
                                    break;
                                }

                                /* Mark RTB clear pending and RB clear pending */
                                ln->stFlags |= LINK_RTB_CLEAR_PENDING;
                                ln->stFlags |= LINK_RB_CLEAR_PENDING;

                                ln->availableState = LINK_UNAVAILABLE;
                            }
                            else
                            {
                                if (ln->stFlags & LINK_REM_BLOCKED)
                                {
                                    ret = LSAC_Main_CCITT(MTP3_STM_TLAC,
                                                     SLM_TRIGGER_CLEAR_BUFFERS,
                                                     NULL, 0,
                                                     ls->linkSet,
                                                     ln->linkCode);

                                    if (ret != ITS_SUCCESS)
                                    {
                                        break;
                                    }

                                    /* Mark RTB clear pending and RB clear pending */
                                    ln->stFlags |= LINK_RTB_CLEAR_PENDING;
                                    ln->stFlags |= LINK_RB_CLEAR_PENDING;

                                    ln->availableState = LINK_UNAVAILABLE;
                                }
                                else
                                {
                                    ret = LSAC_Main_CCITT(MTP3_STM_TLAC,
                                                         SLM_TRIGGER_RESUME,
                                                         NULL, 0,
                                                         ls->linkSet,
                                                         ln->linkCode);

                                    if (ret != ITS_SUCCESS)
                                    {
                                        break;
                                    }

                                    ret = TCBC_Main_CCITT(MTP3_STM_TLAC,
                                                         STM_TRIGGER_LINK_AVAILABLE,
                                                         NULL, 0,
                                                         ls->linkSet,
                                                         ln->linkCode);

                                    if (ret != ITS_SUCCESS)
                                    {
                                        break;
                                    }

                                    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                                         STM_TRIGGER_LINK_AVAILABLE,
                                                         NULL, 0,
                                                         ls->linkSet,
                                                         ln->linkCode);

                                    if (ret != ITS_SUCCESS)
                                    {
                                        break;
                                    }

                                    ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                                         STM_TRIGGER_LINK_AVAILABLE,
                                                         NULL, 0,
                                                         ls->linkSet,
                                                         ln->linkCode);

                                    if (ret != ITS_SUCCESS)
                                    {
                                        break;
                                    }

                                    ln->availableState = LINK_AVAILABLE;
                                }
                            }
                        }
                        else
                        {
                            /* Typo in TLAC sheet 11 */
                            /* Should be GOTO 23 of sheet 11 and NOT 23 of sheet 10 */

                            ln->availableState = LINK_UNAVAILABLE;
                        }
                    }
                    else
                    {
                        ln->availableState = LINK_AVAILABLE;

                        ret = TCBC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             ls->linkSet, ln->linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }

                        ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             ls->linkSet, ln->linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }

                        ret = TPRC_Main_CCITT(MTP3_STM_TLAC,
                                             STM_TRIGGER_LINK_AVAILABLE,
                                             NULL, 0,
                                             ls->linkSet, ln->linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                    }     
                }
            }                                
        }
        break;

    case STM_TRIGGER_RESTART_END:            /* from TPRC */

        for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
        {
            if ((ls = LINKSET_FindLinkSet(i)) == NULL ||
                 ls->adjacent == 0)
            {
                continue;
            }

            for (j = 0; j < ls->numLinks; j++)
            {
                /* clear flags */
                ln = ls->links[j];
                if (ln->availableState == LINK_AVAILABLE)
                {
                    /*
                     * Action: cancel SP restarting.  This is not necessary, TPRC
                     * does this.
                     */
                    ln->availableState = LINK_AVAILABLE;
                }
                else if (ln->availableState == LINK_UNAVAILABLE)
                {
                    /*
                     * Action: cancel SP restarting.  This is not necessary, TPRC
                     * does this.
                     */
                    ln->availableState = LINK_UNAVAILABLE;
                }
            }
        }
        
        break;

    case STM_TRIGGER_LOCAL_INHIBIT_TEST:           /* from SMH */
        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                    sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LLI Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS,PEG_MTP3_LINK_LLI_RX );

        if (ln->availableState == LINK_AVAILABLE)
        {
            /* Build SNMM FORCE UNINHIBIT LINK and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
            SNMM_HC1_SET(snmm, SNMM_HC1_LFU);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);
            
            /* Increament Link Peg for LFU Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);

            ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            /* Increament the peg for Link ForceUnInhibit */
             PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

            /* Start T13 */
            tc.timerId = MTP3_T13;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t13 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                         __ccitt_t13 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_REM_INHIBITED)
            {
                ln->availableState = LINK_UNAVAILABLE;

            }
            else
            {
                ForceUninhibitLink(linkSet, linkCode);

                ln->availableState = LINK_UNAVAILABLE;

            }
        }
        break;

    case STM_TRIGGER_LOCAL_UNINHIBIT_TEST:         /* from SMH */
        break;

    case STM_TRIGGER_FORCE_UNINHIBIT_LINK:          /* from HMDT */
       
        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LFU Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS,PEG_MTP3_LINK_LFU_RX );

        /* Build SNMM UNINHIBIT LINK and send */

        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
        MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

        SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
        SNMM_HC1_SET(snmm, SNMM_HC1_LUN);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        SNMM_Encode(&ev, &omtp3, &snmm);
        
        /* Increament Link Peg for LUN Transmitted */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

        MTP3_Alarm_CCITT(2519, __FILE__, __LINE__, 
                         "linkset:linkcode %x:%x", linkSet,ln->linkCode);

        ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                             SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                             ev.data, ev.len,
                             linkSet, linkCode);
        ITS_EVENT_TERM(&ev);

        if (ret != ITS_SUCCESS)
        {
            break;
        }

        /* Increament the peg for Link ForceUnInhibit */
         PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

        /* Start T12 */
        tc.timerId = MTP3_T12;
        tc.data.linkInfo.linkSet = linkSet;
        tc.data.linkInfo.linkCode = linkCode;

        ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                     __ccitt_t12 * USEC_PER_MILLISEC,
                                     &tc, sizeof(MTP3_TimerContext));

        ln->availableState = LINK_UNAVAILABLE;          

        break;

    case STM_TRIGGER_REMOTE_INHIBIT_TEST:           /* from SMH */
        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for LRI Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS,PEG_MTP3_LINK_LRI_RX );

        if (ln->availableState == LINK_AVAILABLE)
        {
            /* Build SNMM UNINHIBIT LINK and send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
            SNMM_HC1_SET(snmm, SNMM_HC1_LUN);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);
            
            /* Increament Link Peg for LUN Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

            MTP3_Alarm_CCITT(2519, __FILE__, __LINE__, 
                             "linkset:linkcode %x:%x", linkSet,ln->linkCode);

            ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);
            
            if (ret != ITS_SUCCESS)
            {
                break;
            }

            /* Start T12 */
            tc.timerId = MTP3_T12;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                         __ccitt_t12 * USEC_PER_MILLISEC,
                                         &tc, sizeof(MTP3_TimerContext));

            ln->availableState = LINK_AVAILABLE;
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_LOC_INHIBITED)
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                /* Build SNMM UNINHIBIT LINK and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                SNMM_HC1_SET(snmm, SNMM_HC1_LUN);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LUN Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

                MTP3_Alarm_CCITT(2519, __FILE__, __LINE__, 
                                "linkset:linkcode %x:%x", linkSet,ln->linkCode);

                ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);
            
                if (ret != ITS_SUCCESS)
                {
                    break;
                }
            
                /* Start T12 */
                tc.timerId = MTP3_T12;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                             __ccitt_t12 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));

                ln->availableState = LINK_UNAVAILABLE;

            }
        }

        break;

    case STM_TRIGGER_REMOTE_UNINHIBIT_TEST:         /* from SMH */
        break;

    case STM_TRIGGER_CHANGEOVER_ORDER:  /* from SMH */

        if (sif == NULL)
        {
            MTP3_DEBUG(("SIF is NULL, No COO message in trigger \
                STM_TRIGGER_CHANGEOVER_ORDER"));

            return (~ITS_SUCCESS);
        }

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        MTP3_Alarm_CCITT(2510, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for COO Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_RX);

        if (ln->availableState == LINK_AVAILABLE)
        {
            MTP3_DEBUG(("*****TLAC: CHANGE_OVER_ORDER: link was available\n"));

            ln->stFlags |= LINK_FAILED;

            ret = LSAC_Main_CCITT(MTP3_STM_TLAC,
                                 SLM_TRIGGER_CHANGEOVER_ORDER_RECVD,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {

                MTP3_DEBUG(("*****TLAC --> LSAC FAILS\n"));

                break;
            }
            
            if (ln->stFlags & LINK_CBP)
            {
                MTP3_DEBUG(("\n*****CHANGE BACK in PROGRESS\n"));
                ln->stFlags |= LINK_COO;
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
                ln->stFlags |= LINK_COP;
                  
                MTP3_DEBUG(("\n*****SET CHANGE OVER in PROGRESS\n"));

                ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_CHANGEOVER_ORDER,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    MTP3_DEBUG(("TLAC ---> TCOC FAILED\n"));
                    break;
                }

                MTP3_DEBUG(("\n****** SETLINKUNAVAILABLE\n"));
                ret = SetLinkUnavailable(linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    MTP3_DEBUG(("\n****** SETLINKUNAVAILABLE FAILS\n"));
                    break;
                }
                /* Increament the counter for Link Unavailable */
                PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
            }                    
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            MTP3_DEBUG(("*****TLAC: CHANGE_OVER_ORDER: link was unavailable\n"));

            if (ln->stFlags & LINK_COP)
            {
                ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_CHANGEOVER_ORDER,
                                     sif, len,
                                     linkSet, linkCode);

                return (ITS_SUCCESS);
            }
            else
            {
                /*Simply fall thru */
            }
            
            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ITU,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &nls, &nlc, &ev);

            ITS_EVENT_TERM(&ev);

            SNMM_HC0_SET(snmm, SNMM_HC0_ECM);
            SNMM_HC1_SET(snmm, SNMM_HC1_ECA);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);
        
            /* Increament Link Peg for ECA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

            ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 nls, nlc);

            ITS_EVENT_TERM(&ev);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_UNAVAILABLE;
        }

        break;

    case STM_TRIGGER_EMERG_CHANGEOVER_ORDER:       /* from SMH */

        if (sif == NULL)
        {
            MTP3_DEBUG(("SIF is NULL, No ECO message in trigger \
                STM_TRIGGER_EMERG_CHANGEOVER_ORDER"));

            return (~ITS_SUCCESS);
        }

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        MTP3_Alarm_CCITT(2512, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln)
        {
          /* Increament Link Peg for CBA Received */
          PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_RX);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            ln->stFlags |= LINK_FAILED;

            ret = LSAC_Main_CCITT(MTP3_STM_TLAC,
                                 SLM_TRIGGER_CHANGEOVER_ORDER_RECVD,
                                 NULL, 0,
                                 linkSet, linkCode);

            if (ret != ITS_SUCCESS)
            {
                break;
            }

            if (ln->stFlags & LINK_CBP)
            {
                ln->stFlags |= LINK_ECOO;
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
                ln->stFlags |= LINK_COP;

                ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_EMERG_CHANGEOVER_ORDER,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ret = SetLinkUnavailable(linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
                /* Increament the counter for Link Unavailable */
                PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_SL_UNAVAILABLE);
            }                    
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_COP)
            {
                ret = TCOC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_EMERG_CHANGEOVER_ORDER,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }
            }
            else
            {
                /* Simply fall thru */
            }
            
            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ITU,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            /* Send ECA */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &nls, &nlc, &ev);

            ITS_EVENT_TERM(&ev);

            SNMM_HC0_SET(snmm, SNMM_HC0_ECM);
            SNMM_HC1_SET(snmm, SNMM_HC1_ECA);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);
        
            /* Increament Link Peg for ECA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

            ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                 SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                 ev.data, ev.len,
                                 nls, nlc);
            ITS_EVENT_TERM(&ev);
           
            if (ret != ITS_SUCCESS)
            {
                break;
            }

            ln->availableState = LINK_UNAVAILABLE;
        }

        break;

    case STM_TRIGGER_T12:                    /* from timer control */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }  

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            if (ln->timerRetryState.t12RetryOnOff)
            {
                /* Cancel T12 retry */

                ln->timerRetryState.t12RetryOnOff = ITS_FALSE;

                ln->availableState = LINK_AVAILABLE;
            }
            else
            {
                /* Mark T12 retry */
                ln->timerRetryState.t12RetryOnOff = ITS_TRUE;

                /* Build SNMM UNINHIBIT LINK and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                SNMM_HC1_SET(snmm, SNMM_HC1_LUN);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LUN Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

                MTP3_Alarm_CCITT(2519, __FILE__, __LINE__, 
                                "linkset:linkcode %x:%x", linkSet,ln->linkCode);

                ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Start T12 */
                tc.timerId = MTP3_T12;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                             __ccitt_t12 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));
            }
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->timerRetryState.t12RetryOnOff)
            {
                /* Cancel T12 retry */
                ln->timerRetryState.t12RetryOnOff = ITS_FALSE;
                
                if (ln->stFlags & LINK_MGMT_UNINHIBIT_REQ)
                {
                    ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                         MGMT_TRIGGER_UNINHIBIT_REQ_TIMEOUT,
                                         sif, len,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    /* Cancel MGMT request */
                    ln->stFlags &= ~LINK_MGMT_UNINHIBIT_REQ;
    
                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE,
                                     sif, len,
                                     linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_UNAVAILABLE;
                }
            }
            else
            {
                /* Mark T12 retry */
                ln->timerRetryState.t12RetryOnOff = ITS_TRUE;

                if (ln->stFlags & LINK_MGMT_UNINHIBIT_REQ)
                {
                    ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                         STM_TRIGGER_UNINHIBIT_REQUEST,
                                         NULL, 0,
                                         linkSet, linkCode);

                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }

                    ln->availableState = LINK_UNAVAILABLE;
                }
                else
                {
                    if ((ln->stFlags & LINK_FAILED) ||
                        (ln->stFlags & LINK_LOC_BLOCKED) ||
                        (ln->stFlags & LINK_REM_BLOCKED))
                    {
                        ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                             MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE,
                                             sif, len,
                                             linkSet, linkCode);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }

                        /* Cancel Management request */
                        ln->stFlags &= ~LINK_MGMT_UNINHIBIT_REQ;

                        ln->availableState = LINK_UNAVAILABLE;
                    }
                    else
                    {
                       /* Build SNMM UNINHIBIT LINK and send */
                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                        MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                        SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                        SNMM_HC1_SET(snmm, SNMM_HC1_LUN);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                        SNMM_Encode(&ev, &omtp3, &snmm);
            
                        /* Increament Link Peg for LUN Transmitted */
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);

                        MTP3_Alarm_CCITT(2519, __FILE__, __LINE__, 
                                "linkset:linkcode %x:%x", linkSet,ln->linkCode);

                        ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                             SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                             ev.data, ev.len,
                                             linkSet, linkCode);
                        ITS_EVENT_TERM(&ev);

                        if (ret != ITS_SUCCESS)
                        {
                            break;
                        }
                
                        /* Start T12 */
                        tc.timerId = MTP3_T12;
                        tc.data.linkInfo.linkSet = linkSet;
                        tc.data.linkInfo.linkCode = linkCode;

                        ln->t12 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                                     __ccitt_t12 * USEC_PER_MILLISEC,
                                                     &tc, sizeof(MTP3_TimerContext));

                        ln->availableState = LINK_UNAVAILABLE;
                    }
                }                
            }
        }
        break;

    case STM_TRIGGER_T13:                    /* from timer control */    

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {
            if (ln->timerRetryState.t13RetryOnOff)
            {
                /* Cancel T13 retry */
                ln->timerRetryState.t13RetryOnOff = ITS_FALSE;

                ln->availableState = LINK_AVAILABLE;
            }
            else
            {
                /* Mark T13 retry */
                ln->timerRetryState.t13RetryOnOff = ITS_TRUE;

                /* Build SNMM FORCE UNINHIBIT LINK and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                SNMM_HC1_SET(snmm, SNMM_HC1_LFU);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LFU Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);

                ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

               /* Increament the peg for Link ForceUnInhibit */
                PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

                /* Start T13 */
                tc.timerId = MTP3_T13;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t13 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                             __ccitt_t13 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));
            }
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->timerRetryState.t13RetryOnOff)
            {
                /* Cancel T13 retry */

                ln->timerRetryState.t13RetryOnOff = ITS_FALSE;

                ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                /* Mark T13 retry */

                ln->timerRetryState.t13RetryOnOff = ITS_TRUE;

                /* Build SNMM FORCE UNINHIBIT LINK and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                SNMM_HC1_SET(snmm, SNMM_HC1_LFU);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LFU Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);

                ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

               /* Increament the peg for Link ForceUnInhibit */
                PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);

                /* Start T13 */
                tc.timerId = MTP3_T13;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t13 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                             __ccitt_t13 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));

                ln->availableState = LINK_UNAVAILABLE;
            }
        }
        break;

    case STM_TRIGGER_T14:                    /* from timer control */
        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_AVAILABLE)
        {            
            ITS_C_ASSERT(ln->stFlags & LINK_LIP);
        
            ln->stFlags &= ~LINK_LIP;

            if (ln->stFlags & LINK_INHIBIT_RETRY)
            {
                ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_INHIBIT_REQ_TIMEOUT,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->stFlags &= ~LINK_INHIBIT_RETRY;
                ln->availableState = LINK_AVAILABLE;
            }
            else
            {
                ln->stFlags |= LINK_INHIBIT_RETRY;

                ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_LOCAL_INHIBIT_REQUESTED,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->availableState = LINK_AVAILABLE;
            }
        }
        else if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_INHIBIT_RETRY)
            {
                ret = MGMT_Main_CCITT(MTP3_STM_TLAC, 
                                     MGMT_TRIGGER_INHIBIT_REQ_TIMEOUT,
                                     sif, len,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->stFlags &= ~LINK_INHIBIT_RETRY;
                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->stFlags |= LINK_INHIBIT_RETRY;

                ret = TSRC_Main_CCITT(MTP3_STM_TLAC,
                                     STM_TRIGGER_LOCAL_INHIBIT_REQUESTED,
                                     NULL, 0,
                                     linkSet, linkCode);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                ln->availableState = LINK_UNAVAILABLE;
            }
        }
        break;

    case STM_TRIGGER_T20:                    /* from timer control */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_LOC_INHIBITED)
            {
                /* Build SNMM LOCAL INHIBIT TEST and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                SNMM_HC1_SET(snmm, SNMM_HC1_LLI);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LLI Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_TX); 

                MTP3_Alarm_CCITT(2522, __FILE__, __LINE__,"linkset:linkcode %x:%x", linkSet,linkCode);

                ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Start T20 */
                tc.timerId = MTP3_T20;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t20 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                             __ccitt_t20 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));

                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
        }
        break;

    case STM_TRIGGER_T21:                    /* from timer control */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Linkset %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }    

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->availableState == LINK_UNAVAILABLE)
        {
            if (ln->stFlags & LINK_REM_INHIBITED)
            {
                /* Build SNMM REMOTE INHIBIT TEST and send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_MIM);
                SNMM_HC1_SET(snmm, SNMM_HC1_LRI);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);
            
                /* Increament Link Peg for LRI Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_TX);

                MTP3_Alarm_CCITT(2523, __FILE__, __LINE__,
                                 "linkset:linkcode %x:%x", linkSet,linkCode);

                ret = HMRT_Main_CCITT(MTP3_STM_TLAC,
                                     SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                /* Start T21 */
                tc.timerId = MTP3_T21;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t21 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                             __ccitt_t21 * USEC_PER_MILLISEC,
                                             &tc, sizeof(MTP3_TimerContext));

                ln->availableState = LINK_UNAVAILABLE;
            }
            else
            {
                ln->availableState = LINK_UNAVAILABLE;
            }
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        
        break;
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test if an SP is accessible, via any route/linkSet
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
 *************** *************************************************************/
static ITS_BOOLEAN
AdjacentAccessible(SS7_LinkSetPtr ls)
{
    ROUTE_MatchInfo mi;
    SS7_Destination *ent;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;

    if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                      REMOTE_ROUTE, ROUTE_DPC_NI,
                                      FAMILY_ITU,
                                      ls->ni,
                                      ls->linkSet,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_PRI,
                                      ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        MTP3_ERROR(("Can't parse route info\n"));

        return (ITS_FALSE);
    }

    if ((ent = ROUTE_FindBestMatch(&mi, &whichEntry,
                                   &firstMatch, &lastMatch,
                                   &whichLinkCode,
                                   ITS_FALSE)) == NULL)
    {
        MTP3_ERROR(("Can't find route\n"));

        return (ITS_FALSE);
    }

    for (i = firstMatch; i <= lastMatch; i++)
    {
        if (ent->entries[i]->linkSet->isUp &&
            ent->entries[i]->isAllowed)
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Determine if an adjacent is directly accessible
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
static ITS_BOOLEAN
LinkSetAvailable(SS7_LinkSetPtr ls)
{
    ITS_UINT i;

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->isAllowed)
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
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
 ****************************************************************************/
static ITS_BOOLEAN
AlternateLink(SS7_LinkSetPtr ls, SS7_LinkPtr ln)
{
    ITS_UINT i;

    ITS_C_ASSERT(ls != NULL && ln != NULL);

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->isUp &&
            ls->links[i]->isAllowed &&
            ls->links[i]->testPassed &&
            ls->links[i]->linkCode != ln->linkCode)
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test if SP is accessible via any other linkSet than this one.
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
static ITS_BOOLEAN
AlternateRoute(ROUTE_Info *ri)
{
    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;
    SS7_Destination *ent;
    ROUTE_MatchInfo mi;

    ITS_C_ASSERT(ri != NULL);

    mi.basic = ri->basic;
    mi.linkSet = ri->linkSet->linkSet;
    mi.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
    mi.priority = ITS_SS7_DEFAULT_PRI;
    mi.sls = ITS_SS7_DEFAULT_SLS;

    if ((ent = ROUTE_FindBestMatch(&mi, &whichEntry,
                                   &firstMatch, &lastMatch,
                                   &whichLinkCode,
                                   ITS_FALSE)) == NULL)
    {
        MTP3_ERROR(("Can't find match\n"));
   
        return (ITS_FALSE);
    }

    for (i = firstMatch; i <= lastMatch; i++)
    {
        MTP3_DEBUG(("AlternateRoute: pc %08x vs %08x ri %08x cmp %08x ls %d vs %d\n"
                    "up %d allowed %d\n",
                    ri->basic.dpc, ent->entries[i]->basic.dpc,
                    ri, ent->entries[i], ri->linkSet->linkSet,
                    ent->entries[i]->linkSet->linkSet,
                    ent->entries[i]->linkSet->isUp,
                    ent->entries[i]->isAllowed));

        if (ent->entries[i] != ri &&
            ent->entries[i]->isAllowed
#if 1
            && ent->entries[i]->linkSet->isUp
#endif
            )
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test if SP is accessible via any other linkSet than this one.
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
static ROUTE_Info *
GetAlternateRoute(ROUTE_Info *ri)
{
    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;
    SS7_Destination *ent;
    ROUTE_MatchInfo mi;

    ITS_C_ASSERT(ri != NULL);

    mi.basic = ri->basic;
    mi.linkSet = ri->linkSet->linkSet;
    mi.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
    mi.priority = ITS_SS7_DEFAULT_PRI;
    mi.sls = ITS_SS7_DEFAULT_SLS;

    if ((ent = ROUTE_FindBestMatch(&mi, &whichEntry,
                                   &firstMatch, &lastMatch,
                                   &whichLinkCode,
                                   ITS_FALSE)) == NULL)
    {
        MTP3_ERROR(("Can't find match\n"));

        return (NULL);
    }

    for (i = firstMatch; i <= lastMatch; i++)
    {
        if (ent->entries[i] != ri &&
            ent->entries[i]->isAllowed
#if 1
            && ent->entries[i]->linkSet->isUp
#endif
            )
        {
            return (ent->entries[i]);
        }
    }

    return (NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test link set might congest.
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
static ITS_BOOLEAN
DangerOfCongestion(SS7_LinkSetPtr ls)
{
    ITS_UINT i;

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->congLevel > 0)
        {
            return (ITS_TRUE);
        }
    }

    return (ITS_FALSE);
}

/*.implementation:static
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
static int
MarkAllRoutesAvailable(ITS_POINTER entry,
                       void *in, void *out)
{
    SS7_Destination *dest = (SS7_Destination *)entry;
    ITS_UINT i;

    for (i = 0; i < dest->numEntries; i++)
    {
        if (dest->family == FAMILY_ITU &&
            dest->entries[i]->basic.type == REMOTE_ROUTE &&
            (dest->entries[i]->basic.style == ROUTE_DPC_NI ||
             dest->entries[i]->basic.style == ROUTE_DPC_OPC_NI) &&
            dest->entries[i]->linkSet->adjacent != 0)
        {
            dest->entries[i]->isAllowed = ITS_TRUE;
            dest->entries[i]->isRestricted = ITS_FALSE;
        }

        dest->status = DESTINATION_AVAILABLE;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
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
static ITS_BOOLEAN
RemoteSPAccessible(ITS_UINT pc, ITS_OCTET ni)
{
    ROUTE_MatchInfo mi;
    SS7_Destination *ent;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;

    if (ROUTE_ParseRouteMatchInfoArgs(&mi, pc,
                                      REMOTE_ROUTE, ROUTE_DPC_NI,
                                      FAMILY_ITU,
                                      ni,
                                      ITS_SS7_DEFAULT_LINK_SET,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_PRI,
                                      ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        MTP3_ERROR(("Can't parse route info\n"));
   
        return (ITS_FALSE);
    }

    if ((ent = ROUTE_FindBestMatch(&mi, &whichEntry,
                                   &firstMatch, &lastMatch,
                                   &whichLinkCode,
                                   ITS_FALSE)) == NULL)
    {
        MTP3_ERROR(("Can't find route\n"));

        return (ITS_FALSE);
    }

    for (i = firstMatch; i <= lastMatch; i++)
    {
        if (ent->entries[i]->linkSet->isUp &&
            ent->entries[i]->isAllowed)
        {
            return (ITS_TRUE);
        }
    }
#if 0
    /* this should be equivalent and is a better test.  However... */
    if (ent->status != DESTINATION_UNAVAILABLE)
    {
        return (ITS_TRUE);
    }
#endif

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Test link set might congest.
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
static ITS_BOOLEAN
EmergencyState(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;

    /* 12.2.4 */
    /*
     * the conditions for emergency restart may vary between different
     * applications of the signalling system.  Possibilities include:
     * 1) signalling traffic that may be conveyed over the link set to
     *    be restarted is blocked
     * 2) the remote SP is inaccessible.
     */
    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        return (ITS_FALSE);
    }

    /* we can at least do (2) */
    if (!SPRestarting_CCITT() && !RemoteSPAccessible(ls->adjacent, ls->ni))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
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
 ****************************************************************************/
static void
TryInhibitLink(SS7_LinkPtr ln)
{
    DSMQUEUE_Entry *tmp;
    ROUTE_Info *ri;
    ITS_UINT count;

    /* link available */
    if (!ln->isAllowed)
    {
        /* obtain accessibility data for remote SP */

        /* if remote is accessible */
        if (AdjacentAccessible(ln->linkSet))
        {
            /* if inhibit request is local */
            if (ln->stFlags & LINK_LOCAL_LIR)
            {
                TLAC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_LOCAL_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel local inhibit request */
                ln->stFlags &= ~LINK_LOCAL_LIR;
            }
            else
            {
                TLAC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_REMOTE_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel remote inhibit request */
                ln->stFlags &= ~LINK_REMOTE_LIR;

                /* mark link inhibited */
                ln->stFlags |= LINK_INHIBITED;
                
            }
        }
        else
        {
            /* if inhibit request is local */
            if (ln->stFlags & LINK_LOCAL_LIR)
            {
                TLAC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_LOCAL_INHIBIT_DENIED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel local inhibit request */
                ln->stFlags &= ~LINK_LOCAL_LIR;
            }
            else
            {
                TLAC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_REMOTE_INHIBIT_DENIED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel remote inhibit request */
                ln->stFlags &= ~LINK_REMOTE_LIR;
            }
        }
    }
    else
    {
        /* if alternative link in link set */
        if (AlternateLink(ln->linkSet, ln))
        {
            /* if inhibit request is local */
            if (ln->stFlags & LINK_LOCAL_LIR)
            {
                TLAC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_LOCAL_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel local inhibit request */
                ln->stFlags &= ~LINK_LOCAL_LIR;
            }
            else
            {
                TLAC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_REMOTE_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel remote inhibit request */
                ln->stFlags &= ~LINK_REMOTE_LIR;

                /* mark link inhibited */
                ln->stFlags |= LINK_INHIBITED;

            }
        }
        else
        {
            /* while not last destination */
            for (count = 0, tmp = DSMQUEUE_HEAD(ln->linkSet->routes);
                 tmp != NULL && count < DSMQUEUE_COUNT(ln->linkSet->routes);
                 count++, tmp = DSMQUEUE_NEXT(ln->linkSet->routes, tmp) )
            {
                /* select one of concerned destinations */
                memcpy(&ri, tmp->data, sizeof(ri));

                /* if no alternative link set for dest */
                if (!AlternateRoute(ri))
                {
                    /* if inhibit request is local */
                    if (ln->stFlags & LINK_LOCAL_LIR)
                    {
                        TLAC_Main_CCITT(MTP3_STM_TSRC,
                                       STM_TRIGGER_LOCAL_INHIBIT_DENIED,
                                       NULL, 0,
                                       ln->linkSet->linkSet, ln->linkCode);

                        /* cancel local inhibit request */
                        ln->stFlags &= ~LINK_LOCAL_LIR;
                    }
                    else
                    {
                        TLAC_Main_CCITT(MTP3_STM_TSRC,
                                       STM_TRIGGER_REMOTE_INHIBIT_DENIED,
                                       NULL, 0,
                                       ln->linkSet->linkSet, ln->linkCode);

                        /* cancel remote inhibit request */
                        ln->stFlags &= ~LINK_REMOTE_LIR;
                    }

                    return;
                }
            }

            /* if inhibit request is local */
            if (ln->stFlags & LINK_LOCAL_LIR)
            {
                TLAC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_LOCAL_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel local inhibit request */
                ln->stFlags &= ~LINK_LOCAL_LIR;
            }
            else
            {
                TLAC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_REMOTE_INHIBIT_ALLOWED,
                               NULL, 0,
                               ln->linkSet->linkSet, ln->linkCode);

                /* cancel remote inhibit request */
                ln->stFlags &= ~LINK_REMOTE_LIR;

                /* mark link inhibited */
                ln->stFlags |= LINK_INHIBITED;

            }
        }
    }
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
 ****************************************************************************/
static void
AvailableRoute(SS7_LinkPtr ln,
               SS7_Destination *ent, int whichEntry,
               int firstMatch, int lastMatch)
{
    int i, current;
    ROUTE_Info *ri = ent->entries[whichEntry];
    MTP3_POINT_CODE pc;
    ITS_EVENT ev;
    MTP3_HEADER mtp3;

    /* gather PC */
    MTP3_PC_SET_VALUE(pc, ent->entries[whichEntry]->basic.dpc);

    /*
     * NOTE: I reversed the search order (so that if an alternate route
     * is really in use it shows up as the active STP.  This may break
     * other tests (it fixes 9.4.2).  FIXME.
     */
    /* find current entry */
    for (current = -1, i = lastMatch; i >= firstMatch; i--)
    {
        if (ent->entries[i]->flags & ROUTE_STP_IN_USE)
        {
            current = i;

            break;
        }
    }

    MTP3_DEBUG(("######### AvailableRoute: dest %08x pri %d cur %d\n",
                ri->basic.dpc, ri->priority, current));

    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

    MTP3_HDR_SET_SIO(mtp3, ri->linkSet->ni);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, ri->basic.dpc);

    MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                &mtp3, NULL, 0);

    /* if priority >= that of current route */
    if (current < 0 ||
        ri->priority <= ent->entries[current]->priority)
    {
        /* mark STP in use for destination (cluster) */
        ri->flags |= ROUTE_STP_IN_USE;

        /* prohibit new STP. */
        RTPC_Main_CCITT(MTP3_STM_TSRC,
                       SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ITS_SS7_DEFAULT_LINK_CODE);

        /* if STP no longer used for destination (cluster)
         *
         * Watch it here.  This is too much like ITU and not enough
         * like CCITT.  Don't forget that you don't remove STPs for
         * combined linksets (equal priority routes).
         */
        if (current >= 0 && whichEntry != current &&
            ent->entries[current]->priority != ent->entries[whichEntry]->priority)
        {
            /* Mark STP not in use for destination (cluster) */
            ent->entries[current]->flags &= ~ROUTE_STP_IN_USE;

            /* if new route normal */
            if (ri->priority == 0)
            {
                RTAC_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_REM_STP_DEST,
                               ev.data, ev.len,
                               ent->entries[current]->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
            else
            {
                RTRC_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_REM_STP_DEST,
                               ev.data, ev.len,
                               ent->entries[current]->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
        }

        /* if new route normal route */
        if (ri->priority == 0)
        {
            /* if T11 running */
            if (ri->t11 == TIMER_BAD_SERIAL)
            {
                /* stop T11 */
                TIMERS_CancelSharedTimer(ri->t11);
                ri->t11 = TIMER_BAD_SERIAL;
            }

            /* if not destination (cluster) accessible */
            if (!AlternateRoute(ri) || ent->status == DESTINATION_RESTRICTED)
            {
                /* if link becoming available */
                if (ln && ln->stFlags & LINK_COMING_AVAILABLE)
                {
                    /* if danger of congestion possible in normal link set */
                    if (DangerOfCongestion(ln->linkSet))
                    {
                        /* if not destination (cluster) restricted */
                        if (ent->status != DESTINATION_RESTRICTED)
                        {
                            /* mark destination (cluster) restricted */
                            ent->status = DESTINATION_RESTRICTED;

                            TSFC_Main_CCITT(MTP3_STM_TSRC,
                                           STM_TRIGGER_DEST_ACCESS,
                                           ev.data, ev.len,
                                           ri->linkSet->linkSet,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            if (!SPRestarting_CCITT())
                            {
                                RTAC_Main_CCITT(MTP3_STM_TSRC,
                                               SRM_TRIGGER_DEST_RESTRICT,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);
                            }
                        }
                        else
                        {
                            if (ln == NULL || !(ln->stFlags & LINK_COMING_AVAILABLE))
                            {
                                /*
                                 * note: the order is changed here.  There's no point
                                 * in doing TCRC first, as the calls to RTAC and RTRC
                                 * will not have been made.  Since TCRC may REROUTE_END
                                 * before returning, we need to adjust the order.
                                 * therefore, move this.
                                 */
                                RTPC_Main_CCITT(MTP3_STM_TSRC,
                                               SRM_TRIGGER_CONTROLLED_REROUTE,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);

                                RTRC_Main_CCITT(MTP3_STM_TSRC,
                                               SRM_TRIGGER_CONTROLLED_REROUTE,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);

                                /* moved to here */
                                TCRC_Main_CCITT(MTP3_STM_TSRC,
                                               STM_TRIGGER_ROUTE_RESTRICTED,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);
                            }
                        }
            
                        return;
                    }
                }
                
                /* mark destination (cluster) accessible */
                ent->status = DESTINATION_AVAILABLE;

                TSFC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_DEST_ACCESS,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                if (!SPRestarting_CCITT())
                {
                    RTAC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_DEST_ACCESS,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
            }
            else /* there is an alternate route or dest isn't restricted */
            {
                /* if not link becoming available */
                if (ln == NULL || !(ln->stFlags & LINK_COMING_AVAILABLE))
                {
                    MTP3_DEBUG(("AvailableRoute: It's where I wondered it would be.\n"));

                    /*
                     * note: the order is changed here.  There's no point
                     * in doing TCRC first, as the calls to RTAC and RTRC
                     * will not have been made.  Since TCRC may REROUTE_END
                     * before returning, we need to adjust the order.
                     * therefore, move this.
                     */
                    RTPC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    RTRC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    /* moved to here */
                    TCRC_Main_CCITT(MTP3_STM_TSRC,
                                   STM_TRIGGER_ROUTE_AVAILABLE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
            }
        }
        else /* this isn't a normal route */
        {
            /* if not destination (cluster) restricted */
            if (ent->status != DESTINATION_RESTRICTED)
            {
                /* mark destination (cluster) restricted */
                ent->status = DESTINATION_RESTRICTED;

                TSFC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_DEST_ACCESS,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                if (!SPRestarting_CCITT())
                {
                    RTRC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_DEST_RESTRICT,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
            }
            else
            {
                if (ln == NULL ||
                    !(ln->stFlags & LINK_COMING_AVAILABLE))
                {
                    MTP3_DEBUG(("AvailableRoute: It's where I think it is.\n"));

                    /*
                     * note: the order is changed here.  There's no point
                     * in doing TCRC first, as the calls to RTAC and RTRC
                     * will not have been made.  Since TCRC may REROUTE_END
                     * before returning, we need to adjust the order.
                     * therefore, move this.
                     */
                    RTPC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    RTRC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    TCRC_Main_CCITT(MTP3_STM_TSRC,
                                   STM_TRIGGER_ROUTE_RESTRICTED,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }
            }
        }
    }

    ITS_EVENT_TERM(&ev);
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
 ****************************************************************************/
static void
RestrictedRoute(SS7_LinkPtr ln,
                SS7_Destination *ent, int whichEntry,
                int firstMatch, int lastMatch)
{
    ROUTE_Info *ri = ent->entries[whichEntry];
    MTP3_POINT_CODE pc;
    int i, current;
    ITS_EVENT ev;
    MTP3_HEADER mtp3;

    /* gather PC */
    MTP3_PC_SET_VALUE(pc, ent->entries[whichEntry]->basic.dpc);

    /* find current entry */
    for (current = -1, i = firstMatch; i <= lastMatch; i++)
    {
        if (ent->entries[i]->isAllowed)
        {
            current = i;

            break;
        }
    }

    MTP3_DEBUG(("######### RestrictedRoute: dest %08x pri %d cur %d\n",
                ri->basic.dpc, ri->priority, current));

    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

    MTP3_HDR_SET_SIO(mtp3, ri->linkSet->ni);
    MTP3_RL_SET_DPC_VALUE(mtp3.label, ri->basic.dpc);

    MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                &mtp3, NULL, 0);

    /* if destination (cluster) inaccessible */
    if (!AlternateRoute(ri))
    {
        if (!SPRestarting_CCITT())
        {
            TSFC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_DEST_ACCESS,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            RTRC_Main_CCITT(MTP3_STM_TSRC,
                           SRM_TRIGGER_DEST_RESTRICT,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }

        /* if not link becoming available */
        if (ln && !(ln->stFlags & LINK_COMING_AVAILABLE))
        {
            TCRC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_ROUTE_RESTRICTED,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
            
            RTPC_Main_CCITT(MTP3_STM_TSRC,
                           SRM_TRIGGER_CONTROLLED_REROUTE,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
            
            RTRC_Main_CCITT(MTP3_STM_TSRC,
                           SRM_TRIGGER_CONTROLLED_REROUTE,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }

        /* mark destination (cluster) restricted */
        ent->status = DESTINATION_RESTRICTED;

        /* mark STP in use for destination (cluster) */
        ri->flags |= ROUTE_STP_IN_USE;
    }
    else
    {
        /* if not restricted route lower priority than current route */
        if (current >= 0 &&
            !(ri->priority > ent->entries[current]->priority))
        {
            /* if restricted route higher priority than current route */
            if (current >= 0 &&
                ri->priority < ent->entries[current]->priority)
            {
                /* mark STP not in use for destination (cluster) */
                ent->entries[current]->flags &= ~ROUTE_STP_IN_USE;

                /* if new route normal route */
                if (ri->priority == 0)
                {
                    RTAC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_REM_STP_DEST,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    /* if T11 running */
                    if (ri->t11 != TIMER_BAD_SERIAL)
                    {
                        /* stop T11 */
                        TIMERS_CancelSharedTimer(ri->t11);
                        ri->t11 = TIMER_BAD_SERIAL;
                    }
                }
                else
                {
                    RTRC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_REM_STP_DEST,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }

                /* if not link becoming available */
                if (!(ln->stFlags & LINK_COMING_AVAILABLE))
                {
                    TCRC_Main_CCITT(MTP3_STM_TSRC,
                                   STM_TRIGGER_ROUTE_RESTRICTED,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    RTPC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    RTRC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   ev.data, ev.len,
                                   ri->linkSet->linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);
                }

                /* mark destination (cluster) restricted */
                ent->status = DESTINATION_RESTRICTED;

                /* mark STP in use for destination (cluster) */
                ri->flags |= ROUTE_STP_IN_USE;
            }
            else
            {
                /* if restricted route in use */
                if (ri->isRestricted && ri->flags & ROUTE_STP_IN_USE)
                {
                    /* if equal priority route available (not restricted) */
                    {
                        TCRC_Main_CCITT(MTP3_STM_TSRC,
                                       STM_TRIGGER_ROUTE_RESTRICTED,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        RTPC_Main_CCITT(MTP3_STM_TSRC,
                                       SRM_TRIGGER_CONTROLLED_REROUTE,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        RTRC_Main_CCITT(MTP3_STM_TSRC,
                                       SRM_TRIGGER_CONTROLLED_REROUTE,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);
                    }
                    /* else */
                    {
                        /* if not destination (cluster) restricted */
                        if (ent->status != DESTINATION_RESTRICTED)
                        {
                            /* mark destination (cluster) restricted */
                            ent->status = DESTINATION_RESTRICTED;

                            if (!SPRestarting_CCITT())
                            {
                                RTRC_Main_CCITT(MTP3_STM_TSRC,
                                               SRM_TRIGGER_DEST_RESTRICT,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);
                            }
                        }

                        /* if equal priority route restricted and not in use */
                        if (ri->isRestricted && !(ri->flags & ROUTE_STP_IN_USE))
                        {
                            /* if not link becoming available */
                            if (!(ln->stFlags & LINK_COMING_AVAILABLE))
                            {
                                TCRC_Main_CCITT(MTP3_STM_TSRC,
                                               STM_TRIGGER_ROUTE_RESTRICTED,
                                               ev.data, ev.len,
                                               ri->linkSet->linkSet,
                                               ITS_SS7_DEFAULT_LINK_CODE);
                            }

                            /* mark destination (cluster) restricted */
                            ent->status = DESTINATION_RESTRICTED;

                            /* mark STP in use for destination (cluster) */
                            ri->flags |= ROUTE_STP_IN_USE;
                        }
                    }
                }
                else
                {
                    /* if current route restricted */
                    if (ri->isRestricted)
                    {
                        /* if not link becoming available */
                        if (!(ln->stFlags & LINK_COMING_AVAILABLE))
                        {
                            TCRC_Main_CCITT(MTP3_STM_TSRC,
                                           STM_TRIGGER_ROUTE_RESTRICTED,
                                           ev.data, ev.len,
                                           ri->linkSet->linkSet,
                                           ITS_SS7_DEFAULT_LINK_CODE);
                        }

                        /* mark destination (cluster) restricted */
                        ent->status = DESTINATION_RESTRICTED;

                        /* mark STP in use for destination (cluster) */
                        ri->flags |= ROUTE_STP_IN_USE;
                    }
                }
            }
        }
    }
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
 ****************************************************************************/
static void
UnavailableRoute(ROUTE_Info *ri)
{
    ROUTE_Info *oldri;
    MTP3_POINT_CODE pc;
    MTP3_HEADER mtp3;
    ITS_EVENT ev;
    MTP3_TimerContext tc;
    SS7_Destination *ent;
    ITS_BOOLEAN firstLoop = ITS_TRUE;

    MTP3_DEBUG(("UnavailableRoute: Consider route %08x pri %d inUse %d\n",
                ri->basic.dpc, ri->priority, ri->flags & ROUTE_STP_IN_USE));

    if (!(ri->flags & ROUTE_STP_IN_USE))
    {
        MTP3_DEBUG(("UnavailableRoute: STP_IN_USE not set: %08x\n",
                    ri->basic.dpc));

        return;
    }

    ent = ri->dest;

    MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

    MTP3_HDR_SET_SIO(mtp3, ri->linkSet->ni);
    MTP3_RL_SET_DPC(mtp3.label, pc);

    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
    
    MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                &mtp3, NULL, 0);

    /* if alternative link set */
    if (AlternateRoute(ri))
    {
        MTP3_DEBUG(("UnavailableRoute: have alternate route: %08x\n",
                    ri->basic.dpc));

        oldri = ri;
        ri = GetAlternateRoute(ri);

        MTP3_DEBUG(("UnavailableRoute: new STP? pc %08x ripri %d oldripri %d\n",
                    ri->basic.dpc, ri->priority, oldri->priority));
        MTP3_DEBUG(("UnavailableRoute: adjSTP? %d riSTP %d oldriSTP %d\n",
                    ri->linkSet->adjSTP, ri->flags & ROUTE_STP_IN_USE,
                    oldri->flags & ROUTE_STP_IN_USE));

        /* if new STP to be used for dest */
        if (ri && ri->linkSet->adjSTP &&
            ri->priority > oldri->priority &&
            !(ri->flags & ROUTE_STP_IN_USE))
        {
            RTPC_Main_CCITT(MTP3_STM_TSRC,
                           SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            /* mark STP in use for destination (cluster) */
            ri->flags |= ROUTE_STP_IN_USE;

            /* if destination (cluster) restricted */
            if (ent->status == DESTINATION_RESTRICTED)
            {
                MTP3_DEBUG(("UnavailableRoute: destination restricted: %08x\n",
                            ri->basic.dpc));

                return;
            }

            /* if new STP lower priority */
            if (ri->priority > oldri->priority)
            {
                if (SPRestarting_CCITT())
                {
                    /* mark destination (cluster) restricted */
                    ent->status = DESTINATION_RESTRICTED;

                    MTP3_DEBUG(("UnavailableRoute: mark destination restricted: %08x\n",
                                ri->basic.dpc));

                    return;
                }
                else
                {
                    /* start T11 */
                    tc.timerId = MTP3_T11;
                    tc.data.routeInfo.pointCode = MTP3_PC_GET_VALUE(pc);
                    tc.data.routeInfo.linkSet = ri->linkSet->linkSet;
                    tc.data.routeInfo.sio = ri->linkSet->ni;

                    ri->t11 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                           __ccitt_t11 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    return;
                }
            }
            else
            {
                /* if new route restricted */
                if (ri->isRestricted)
                {
                    if (SPRestarting_CCITT())
                    {
                        /* mark destination (cluster) restricted */
                        ent->status = DESTINATION_RESTRICTED;

                        MTP3_DEBUG(("UnavailableRoute: mark destination restricted2: %08x\n",
                                    ri->basic.dpc));

                        return;
                    }
                    else
                    {
                        RTRC_Main_CCITT(MTP3_STM_TSRC,
                                       SRM_TRIGGER_DEST_RESTRICT,
                                       ev.data, ev.len,
                                       ri->linkSet->linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        /* mark destination (cluster) restricted */
                        ent->status = DESTINATION_RESTRICTED;
                    }
                }
                else
                {
                    MTP3_DEBUG(("UnavailableRoute: route not restricted: %08x\n",
                                ri->basic.dpc));

                    return;
                }
            }
        }
        else
        {
            MTP3_DEBUG(("UnavailableRoute: new STP not to be used: %08x\n",
                        ri->basic.dpc));

            return;
        }
    }
    else /* (no alternative link set) */
    {
        ITS_UINT i;

        MTP3_DEBUG(("UnavailableRoute: no alternate link set: %08x\n",
                    ri->basic.dpc));

        /* mark destination (cluster) inaccessible */
        ent->status = DESTINATION_UNAVAILABLE;

        /*
         * we should do this only once, as we don't need to uninhibit
         * for every destination.
         */
        if (firstLoop)
        {
            /* if any links inhibited */
            /* loop through links in link set.  If any marked
             * inhibited, send this trigger */
            for (i = 0; i < ri->linkSet->numLinks; i++)
            {
                if (ri->linkSet->links[i]->stFlags & LINK_INHIBITED)
                {
                    TLAC_Main_CCITT(MTP3_STM_TSRC,
                                   STM_TRIGGER_UNINHIBITING_LINK,
                                   NULL, 0,
                                   ri->linkSet->linkSet,
                                   ri->linkSet->links[i]->linkCode);
                }
            }

            firstLoop = ITS_FALSE;
        }

        if (!SPRestarting_CCITT())
        {
            RTPC_Main_CCITT(MTP3_STM_TSRC,
                           SRM_TRIGGER_DEST_INACCESS,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);
        }

        TSFC_Main_CCITT(MTP3_STM_TSRC,
                       STM_TRIGGER_DEST_INACCESS,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ITS_SS7_DEFAULT_LINK_CODE);

        /* stop T11 */
        if (ri->t11 != TIMER_BAD_SERIAL)
        {
            TIMERS_CancelSharedTimer(ri->t11);
            ri->t11 = TIMER_BAD_SERIAL;
        }
    }

    ITS_EVENT_TERM(&ev);
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
 ****************************************************************************/
static void
DeactivateLinkSet(SS7_LinkSetPtr ls)
{
    DSMQUEUE_Entry *tmp;
    ROUTE_Info *ri;
    ITS_UINT count;
    
    MTP3_DEBUG(("DeactivateLinkSet: %d\n", ls->linkSet));

    /* while affected destinations or clusters */
    for (count = 0, tmp = DSMQUEUE_HEAD(ls->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ls->routes);
         count++, tmp = DSMQUEUE_NEXT(ls->routes, tmp) )
    {
        /* select an affected destination or cluster */
        memcpy(&ri, tmp->data, sizeof(ri));

        UnavailableRoute(ri);
    }
}

/*.implementation:static
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
static void
UpdateInaccessibleRestricted(SS7_LinkSetPtr ls)
{
    DSMQUEUE_Entry *tmp;
    ROUTE_Info *ri;
    MTP3_POINT_CODE pc;
    MTP3_HEADER mtp3;
    ITS_EVENT ev;
    ITS_UINT count;

    /* while any inaccessible destinations or clusters */
    for (count = 0, tmp = DSMQUEUE_HEAD(ls->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ls->routes);
         count++, tmp = DSMQUEUE_NEXT(ls->routes, tmp) )
    { 
        memcpy(&ri, tmp->data, sizeof(ri));

        if (!(ri->flags & ROUTE_TRANSFER_PROHIBITED))
        {
            continue;
        }

        MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

        MTP3_HDR_SET_SIO(mtp3, ls->ni);
        MTP3_RL_SET_DPC(mtp3.label, pc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        RTPC_Main_CCITT(MTP3_STM_TSRC,
                       SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                       ev.data, ev.len,
                       ls->linkSet,
                       ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);
    }

    /* while any restricted destinations or clusters */
    for (count = 0, tmp = DSMQUEUE_HEAD(ls->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ls->routes);
         count++, tmp = DSMQUEUE_NEXT(ls->routes, tmp) )
    {
        memcpy(&ri, tmp->data, sizeof(ri));

        if (!(ri->isRestricted))
        {
            continue;
        }

        MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

        MTP3_HDR_SET_SIO(mtp3, ls->ni);
        MTP3_RL_SET_DPC(mtp3.label, pc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        RTRC_Main_CCITT(MTP3_STM_TSRC,
                       SRM_TRIGGER_SEND_TRANSFER_RESTRICT,
                       ev.data, ev.len,
                       ls->linkSet,
                       ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);
    }
}

/*.implementation:static
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
static void
UpdateAdjacent(SS7_LinkSetPtr ls)
{
    DSMQUEUE_Entry *tmp;
    ROUTE_Info *ri;
    MTP3_POINT_CODE pc;
    MTP3_HEADER mtp3;
    ITS_EVENT ev;
    ITS_UINT count;

    /* while any destination or cluster normally routed via adjacent SP */
    for (count = 0, tmp = DSMQUEUE_HEAD(ls->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ls->routes);
         count++, tmp = DSMQUEUE_NEXT(ls->routes, tmp) )
    {
        memcpy(&ri, tmp->data, sizeof(ri));

        if (ri->priority != 0)
        {
            continue;
        }

        MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

        MTP3_HDR_SET_SIO(mtp3, ls->ni);
        MTP3_RL_SET_DPC(mtp3.label, pc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &mtp3, NULL, 0);

        RTPC_Main_CCITT(MTP3_STM_TSRC,
                       SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                       ev.data, ev.len,
                       ls->linkSet,
                       ITS_SS7_DEFAULT_LINK_SET);

        ITS_EVENT_TERM(&ev);
    }

    UpdateInaccessibleRestricted(ls);
}

/*.implementation:static
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
static void
StartTrafficRestart(ROUTE_Info *ri)
{
    MTP3_TimerContext tc;
    MTP3_HEADER mtp3;
    SNMM_MESSAGE snmm;
    ITS_EVENT ev;
    DSMQUEUE_Entry *tmp;
    MTP3_POINT_CODE pc;
    ITS_UINT count;

    /* if T29 or T30 running */
    if (ri->t29 != TIMER_BAD_SERIAL || ri->t30 != TIMER_BAD_SERIAL)
    {
        return;
    }

    if (STPFunction_CCITT())
    {
        /* Build SNMM traffic restart waiting */
        MTP3_HDR_SET_SIO(mtp3, MTP3_SIO_SNMM | ri->linkSet->ni);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ri->basic.dpc);
        MTP3_RL_SET_OPC_VALUE(mtp3.label, ri->linkSet->lpc);

        SNMM_HC0_SET(snmm, SNMM_HC0_TRM);
        SNMM_HC1_SET(snmm, SNMM_HC1_TRW);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        SNMM_Encode(&ev, &mtp3, &snmm);

        HMRT_Main_CCITT(MTP3_STM_TSRC,
                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        /* start T30 */
        tc.timerId = MTP3_T30;
        tc.data.routeInfo.pointCode = ri->basic.dpc;
        tc.data.routeInfo.linkSet = ri->linkSet->linkSet;
        tc.data.routeInfo.sio = ri->linkSet->ni;

        ri->t30 =
            TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                               __ccitt_t30 * USEC_PER_MILLISEC,
                               &tc, sizeof(MTP3_TimerContext));

        /*
         * for each destination or cluster currently routed via originator of
         * TRW, TRA (HERE)
         */
        for (count = 0, tmp = DSMQUEUE_HEAD(ri->linkSet->routes); 
             tmp != NULL && count < DSMQUEUE_COUNT(ri->linkSet->routes);
             count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
        {
            memcpy(&ri, tmp->data, sizeof(ri));

            MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

            MTP3_HDR_SET_SIO(mtp3, ri->linkSet->ni);
            MTP3_RL_SET_DPC_VALUE(mtp3.label, ri->basic.dpc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &mtp3, NULL, 0);

            RTPC_Main_CCITT(MTP3_STM_TSRC,
                           SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                           ev.data, ev.len,
                           ri->linkSet->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }

        if (ri->basic.dpc == ri->linkSet->adjacent)
        {
            UpdateInaccessibleRestricted(ri->linkSet);
        }
    }
    else
    {
        /* Build SNMM traffic restart allowed */
        MTP3_HDR_SET_SIO(mtp3, MTP3_SIO_SNMM | ri->linkSet->ni);
        MTP3_RL_SET_DPC_VALUE(mtp3.label, ri->basic.dpc);
        MTP3_RL_SET_OPC_VALUE(mtp3.label, ri->linkSet->lpc);

        SNMM_HC0_SET(snmm, SNMM_HC0_TRM);
        SNMM_HC1_SET(snmm, SNMM_HC1_TRA);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        SNMM_Encode(&ev, &mtp3, &snmm);

        HMRT_Main_CCITT(MTP3_STM_TSRC,
                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        /* start T29 */
        tc.timerId = MTP3_T29;
        tc.data.routeInfo.pointCode = ri->basic.dpc;
        tc.data.routeInfo.linkSet = ri->linkSet->linkSet;
        tc.data.routeInfo.sio = ri->linkSet->ni;

        ri->t29 =
            TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                               __ccitt_t29 * USEC_PER_MILLISEC,
                               &tc, sizeof(MTP3_TimerContext));
    }
}

/*.implementation:static
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
static int
StatusIterate(ITS_POINTER entry,
              void *in, void *out)
{
    ITS_UINT dpc;
    SS7_Destination *dest = (SS7_Destination *)entry;
    ITS_EVENT ev;
    MTP3_HEADER omtp3;
    MTP3_POINT_CODE pc;

    if (dest->family != FAMILY_ITU ||
        dest->numEntries == 0 ||
        dest->entries[0]->basic.type != REMOTE_ROUTE ||
        (dest->entries[0]->basic.style != ROUTE_DPC_NI &&
         dest->entries[0]->basic.style != ROUTE_DPC_OPC_NI))
    {
        /* skip it */
        return (ITS_SUCCESS);
    }

    dpc = dest->entries[0]->basic.dpc;
    MTP3_PC_SET_VALUE(pc, dpc);

    /* destination or cluster inaccessible */
    if (dest->status == DESTINATION_UNAVAILABLE)
    {
        /* The DPC needs to have NI */
        MTP3_HDR_SET_SIO(omtp3, dest->entries[0]->basic.criteria.sio &
                         MTP3_NIC_MASK);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, dpc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &omtp3, NULL, 0);

        RTPC_Main_CCITT(MTP3_STM_TSRC,
                       SRM_TRIGGER_DEST_INACCESS,
                       ev.data, ev.len,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        TSFC_Main_CCITT(MTP3_STM_TSRC,
                       STM_TRIGGER_DEST_INACCESS,
                       ev.data, ev.len,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);
    }
    /* destination or cluster restricted */
    else if (dest->status == DESTINATION_RESTRICTED)
    {
        MTP3_HDR_SET_SIO(omtp3, dest->entries[0]->basic.criteria.sio &
                                MTP3_NIC_MASK);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, dpc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &omtp3, NULL, 0);

        RTRC_Main_CCITT(MTP3_STM_TSRC,
                       SRM_TRIGGER_DEST_RESTRICT,
                       ev.data, ev.len,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
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
static void
TrafficRestart(ROUTE_Info *ri)
{
    ITS_UINT i;
    ITS_EVENT ev;
    MTP3_HEADER mtp3;
    MTP3_POINT_CODE pc;
    DSMQUEUE_Entry *tmp;
    ITS_UINT count;

    /* cancel adjacent SP restarting */
    ri->linkSet->adjRestart = ITS_FALSE;

    MTP3_PC_SET_VALUE(pc, ri->linkSet->adjacent);

    MTP3_HDR_SET_SIO(mtp3, ri->linkSet->ni);
    MTP3_RL_SET_DPC(mtp3.label, pc);

    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

    MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                &mtp3, NULL, 0);

    /* for each link of the linkset */
    for (i = 0; i < ri->linkSet->numLinks; i++)
    {
        TLAC_Main_CCITT(MTP3_STM_TSRC,
                       STM_TRIGGER_ADJACENT_SP_RESTARTED,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ri->linkSet->links[i]->linkCode);
    }

    TSFC_Main_CCITT(MTP3_STM_TSRC,
                   STM_TRIGGER_DEST_ACCESS,
                   ev.data, ev.len,
                   ri->linkSet->linkSet,
                   ITS_SS7_DEFAULT_LINK_CODE);

    /* if danger of congestion possible in normal link set */
    if (DangerOfCongestion(ri->linkSet))
    {
        /* mark destination restricted */
        ri->dest->status = DESTINATION_RESTRICTED;

        RTRC_Main_CCITT(MTP3_STM_TSRC,
                       SRM_TRIGGER_DEST_RESTRICT,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ITS_SS7_DEFAULT_LINK_CODE);
    }
    else
    {
        RTAC_Main_CCITT(MTP3_STM_TSRC,
                       SRM_TRIGGER_DEST_ACCESS,
                       ev.data, ev.len,
                       ri->linkSet->linkSet,
                       ITS_SS7_DEFAULT_LINK_CODE);
    }

    ITS_EVENT_TERM(&ev);

    /* for each destination (cluster) */
    for (count = 0, tmp = DSMQUEUE_HEAD(ri->linkSet->routes);
         tmp != NULL && count < DSMQUEUE_COUNT(ri->linkSet->routes);
         count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
    {
        ROUTE_InfoPtr rt;

        memcpy(&rt, tmp->data, sizeof(ri));

        /* if STP no longer used for destination (cluster) */
        if (!(rt->flags & ROUTE_STP_IN_USE))
        {
            MTP3_PC_SET_VALUE(pc, rt->basic.dpc);

            MTP3_HDR_SET_SIO(mtp3, rt->linkSet->ni);
            MTP3_RL_SET_DPC(mtp3.label, pc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &mtp3, NULL, 0);

            if (rt->priority == 0)
            {
                RTAC_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_REM_STP_DEST,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
            else
            {
                RTRC_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_REM_STP_DEST,
                               ev.data, ev.len,
                               ri->linkSet->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }

            ITS_EVENT_TERM(&ev);
        }
    }

    /* while any destination or cluster becoming available */
    for (count = 0, tmp = DSMQUEUE_HEAD(ri->linkSet->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ri->linkSet->routes);
         count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
    {
        ROUTE_Info *ri;
        SS7_LinkSetPtr ls;
        SS7_Destination *dest;

        memcpy(&ri, tmp->data, sizeof(ri));
        ls = ri->linkSet;

        dest = ROUTE_FindDestination(ri->basic.dpc,
                                     ri->basic.criteria.sio,
                                     FAMILY_ITU);

        if (dest && dest->status == DESTINATION_AVAILABLE)
        {
            /* if adjacent */
            if (ri->basic.dpc == ls->adjacent)
            {
                UpdateAdjacent(ls);
            }

            MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

            MTP3_HDR_SET_SIO(mtp3, ls->ni);
            MTP3_RL_SET_DPC(mtp3.label, pc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &mtp3, NULL, 0);

            /* if danger of congestion possible in normal link set */
            if (ri->priority == 0 &&
                DangerOfCongestion(ri->linkSet))
            {
                ri->dest->status = DESTINATION_RESTRICTED;

                RTRC_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_DEST_RESTRICT,
                               ev.data, ev.len,
                               ls->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }
            else
            {
                RTAC_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_DEST_ACCESS,
                               ev.data, ev.len,
                               ls->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }

            TSFC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_DEST_ACCESS,
                           ev.data, ev.len,
                           ls->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }
    }

    /* while any prohibited destination or cluster becoming restricted */
    for (count = 0, tmp = DSMQUEUE_HEAD(ri->linkSet->routes); 
         tmp != NULL && count < DSMQUEUE_COUNT(ri->linkSet->routes);
         count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
    {
        ROUTE_Info *ri;
        SS7_LinkSetPtr ls;
        SS7_Destination *dest;

        memcpy(&ri, tmp->data, sizeof(ri));
        ls = ri->linkSet;

        dest = ROUTE_FindDestination(ri->basic.dpc,
                                     ri->basic.criteria.sio,
                                     FAMILY_ITU);

        if (dest && dest->status == DESTINATION_RESTRICTED)
        {
            /* if adjacent */
            if (ri->basic.dpc == ls->adjacent)
            {
                UpdateAdjacent(ls);
            }

            MTP3_PC_SET_VALUE(pc, ri->basic.dpc);

            MTP3_HDR_SET_SIO(mtp3, ls->ni);
            MTP3_RL_SET_DPC(mtp3.label, pc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &mtp3, NULL, 0);

            RTRC_Main_CCITT(MTP3_STM_TSRC,
                           SRM_TRIGGER_DEST_RESTRICT,
                           ev.data, ev.len,
                           ls->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            TSFC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_DEST_ACCESS,
                           ev.data, ev.len,
                           ls->linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }
    }
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
 ****************************************************************************/
int
TSRC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1], omtp3;
    MTP3_TimerContext tc;
    MTP3_POINT_CODE dpc;
    ITS_UINT pc;
    ITS_OCTET ni, nls, nlc;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, ret;
    SS7_Destination *ent;
    ROUTE_MatchInfo rinfo;
    ROUTE_Info *ri = NULL;
    ITS_UINT i, j, count;
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;
    SNMM_MESSAGE osnmm;
    ITS_EVENT ev;
    ITS_BOOLEAN allowed;
    DSMQUEUE_Entry *tmp;
    int idx; 
    ITS_BOOLEAN isUp = ITS_FALSE;

    MTP3_TRACE_ENTRY_CCITT(MTP3_STM_TSRC, src, trigger, sif, len,
                          linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }

    /* sometimes wants linkSet,linkCode, sometimes wants point code for route?*/
    switch (trigger)
    {
    case STM_TRIGGER_RESTART_END:               /* from TPRC */
        /*
         * Action: clear SP restarting.  Not necessary, TPRC does
         * this.
         */

        /* one message for each adjacent SP */
        for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
        {
            ls = LINKSET_FindLinkSet((ITS_OCTET)i);

            if (ls && ls->adjacent != 0)
            {
                /* Build SNMM traffic restart allowed */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET(osnmm, SNMM_HC0_TRM);
                SNMM_HC1_SET(osnmm, SNMM_HC1_TRA);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &osnmm);


                HMRT_Main_CCITT(MTP3_STM_TSRC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               ls->linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }
        }
        SendingStatusSet_CCITT(ITS_FALSE);

        break;

    case STM_TRIGGER_RESTART_BEGIN:             /* from TPRC */

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_RESTART);
        if (SPRestarting_CCITT())
        {
            /*
             * Action: mark SP restarting.  Not necessary, TPRC does
             * this.
             */

            /* mark all routes available */
            DSM_TableIterate(DSM_Mtp3FtGroupId,
                             DSM_TABLE_DESTINATIONS,
                             NULL, NULL, MarkAllRoutesAvailable);

            /* cancel all inhibited links and inhibit requests */
            for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
            {
                ls = LINKSET_FindLinkSet((ITS_OCTET)i);

                if (ls && ls->adjacent != 0)
                {
                    for (j = 0; j < ls->numLinks; j++)
                    {
                        SS7_LinkPtr ln = ls->links[j];

                        ln->stFlags &= ~(LINK_INHIBITED|
                                         LINK_LOCAL_LIR|
                                         LINK_REMOTE_LIR);
                    }
                }
            }
        }
        break;

    case STM_TRIGGER_ACCESSIBILITY_REQUEST:     /* from RSRT, TRCC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }
        /*
         * obtain accessibility data for concerned destination
         *
         * Do I have a route to this destination? Look at
         * all the ROUTE_Info records and determine if there is
         * at least one allowed route.
         */
        allowed = ITS_FALSE;
        for (idx = firstMatch; idx <= lastMatch; idx++)
        {
            if (ent->entries[idx]->isAllowed)
            {
                allowed = ITS_TRUE;

                break;
            }
        }

        if (src == MTP3_SRM_RSRT)
        {
            /* NOTE: the status is being sent via the link code arg */
            RSRT_Main_CCITT(MTP3_STM_TSRC,
                           SRM_TRIGGER_ACCESSIBILITY_DATA,
                           sif, len,
                           linkSet, (ITS_OCTET)allowed);
        }
        else if (src == MTP3_STM_TRCC)
        {
            /* NOTE: the status is being sent via the link code arg */
            TRCC_Main_CCITT(MTP3_STM_TRCC,
                           STM_TRIGGER_ACCESSIBILITY_DATA,
                           sif, len,
                           linkSet, (ITS_OCTET)allowed);
        }
        break;

    case STM_TRIGGER_ALTERNATE_ROUTE_REQ:       /* from TCOC, TCBC, TFRC, TCRC, LSDA */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni,
#if 1
    /* THIS IS A LARGE CHANGE.  IT PROBABLY BREAKS THINGS. */
                                                 linkSet, linkCode,
#else
                                                 ITS_SS7_DEFAULT_LINK_SET,
                                                 ITS_SS7_DEFAULT_LINK_CODE,
#endif
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Status not maintained for NI:PC %02x:%08x\n",
                        ni, pc));

            return ITS_ENOTFOUND;
        }

        FindAlternateRoute(ent, mtp3,
                           whichEntry, firstMatch, lastMatch,
                           linkSet, linkCode,
                           &nls, &nlc,
                           &ev);

        if (src == MTP3_STM_TCOC)
        {
            TCOC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_DATA,
                           ev.data, ev.len,
                           nls, nlc); /* RSFIX: was nls, nlc */
        }
        else if (src == MTP3_STM_TCBC)
        {
            TCBC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_DATA,
                           ev.data, ev.len,
                           nls, nlc); /* RSFIX: was nls, nlc */
        }
        else if (src == MTP3_STM_TFRC)
        {
            TFRC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_DATA,
                           ev.data, ev.len,
                           nls, nlc); /* RSFIX: was nls, nlc */
        }
        else if (src == MTP3_STM_TCRC)
        {
            TCRC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_DATA,
                           ev.data, ev.len,
                           nls, nlc); /* RSFIX: was nls, nlc */
        }
        else if (src == MTP3_SLM_LSDA)
        {
            LSDA_Main_CCITT(MTP3_STM_TSRC,
                           SLM_TRIGGER_ALTERNATE_ROUTING_DATA,
                           ev.data, ev.len,
                           nls, nlc); /* RSFIX: was nls, nlc */
        }

        ITS_EVENT_TERM(&ev);
        break;

    case STM_TRIGGER_CHANGEOVER_NOT_REQD:        /* from TCOC */
        /* nothing needed */
        break;

    case STM_TRIGGER_CHANGEOVER_EXECUTED:       /* from TCOC */
        /* mark changeover completed for new link */
        ln = LINK_FindLink(linkSet, linkCode);
        ITS_C_ASSERT(ln != NULL);

        ln->stFlags |= LINK_CHANGEOVER_COMPLETE;
        /* Increament the peg for ChangeOver */
        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER);

        /* if signalling links loaded */
        if (ln->isUp && ln->isAllowed && ln->testPassed)
        {
            LSAC_Main_CCITT(MTP3_STM_TSRC,
                           SLM_TRIGGER_LINK_LOADED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        else
        {
            LSAC_Main_CCITT(MTP3_STM_TSRC,
                           SLM_TRIGGER_LINK_DELOADED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case STM_TRIGGER_PROCEDURE_TERMINATED:      /* from TCBC, TFRC, TCRC */
        /* cancel changeover completed */
        if (src == MTP3_STM_TCBC || src == MTP3_STM_TCOC)
        {
            ln = LINK_FindLink(linkSet, linkCode);
            ITS_C_ASSERT(ln != NULL);

            ln->stFlags &= ~LINK_CHANGEOVER_COMPLETE;

            /* if signalling links loaded */
            if (ln->isUp && ln->isAllowed && ln->testPassed)
            {
                LSAC_Main_CCITT(MTP3_STM_TSRC,
                               SLM_TRIGGER_LINK_LOADED,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSAC_Main_CCITT(MTP3_STM_TSRC,
                               SLM_TRIGGER_LINK_DELOADED,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        else /* TFRC or TCRC */
        {
            ls = LINKSET_FindLinkSet(linkSet);

            for (i = 0; i < ls->numLinks; i++)
            {
                ln = ls->links[i];

                /* if signalling links loaded */
                if (ln->isUp && ln->isAllowed && ln->testPassed)
                {
                    LSAC_Main_CCITT(MTP3_STM_TSRC,
                                   SLM_TRIGGER_LINK_LOADED,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
                else
                {
                    LSAC_Main_CCITT(MTP3_STM_TSRC,
                                   SLM_TRIGGER_LINK_DELOADED,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
            }
        }
        break;

    case STM_TRIGGER_ROUTE_AVAILABLE:           /* from RTAC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, /* linkSet; FIXME: 
                                                 linkSet; default???
                                                 all we need to know here 
                                                 is if the status of this 
                                                 route is maintained.
                                                 Do we need to specify the link
                                                 we got the message from??? */
                                                 ITS_SS7_DEFAULT_LINK_SET,
                                                 ITS_SS7_DEFAULT_LINK_CODE,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }
        /* if route in use */
        if (ri->flags & ROUTE_STP_IN_USE)
        {
            MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: STP in use\n"));

            /* if not route already marked available */
            if (!ri->isAllowed)
            {
                MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: route not allowed\n"));

                /* if any links in route available */
                if (LinkSetAvailable(ri->linkSet))
                {
                    MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: link set available\n"));

                    if (SPRestarting_CCITT())
                    {
                        /* mark route available */
                        ri->isAllowed = ITS_TRUE;
                        ri->isRestricted = ITS_FALSE;

                        AvailableRoute(NULL,
                                       ent, whichEntry,
                                       firstMatch, lastMatch);
                    }
                    else
                    {
                        MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: not SP restarting\n"));

                        /* if not adjacent SP accessible */
                        if (!AdjacentAccessible(ri->linkSet))
                        {
                            MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: available route\n"));

                            /* mark route available */
                            ri->isAllowed = ITS_TRUE;
                            ri->isRestricted = ITS_FALSE;

                            AvailableRoute(NULL,
                                           ent, whichEntry,
                                           firstMatch, lastMatch);
                        }
                        else
                        {
                            MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: not available route\n"));

                            /* mark route available */
                            ri->isAllowed = ITS_TRUE;
                            ri->isRestricted = ITS_FALSE;

                            UpdateAdjacent(ri->linkSet);

                            AvailableRoute(NULL,
                                           ent, whichEntry,
                                           firstMatch, lastMatch);
                        }
                    }
                }
            }
        }
        else
        {
            MTP3_DEBUG(("TSRC_Main: ROUTE_AVAIL: STP NOT in use\n"));
        }
        break;

    case STM_TRIGGER_LOCAL_INHIBIT_REQUESTED:   /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* mark local inhibit request */
        ln->stFlags |= LINK_LOCAL_LIR;

        TryInhibitLink(ln);
        break;

    case STM_TRIGGER_REMOTE_INHIBIT_REQUESTED:  /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* mark remote inhibit request */
        ln->stFlags |= LINK_REMOTE_LIR;

        TryInhibitLink(ln);
        break;

    case STM_TRIGGER_LINK_INHIBITED:            /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* mark link inhibited */
        ln->stFlags |= LINK_INHIBITED;

        break;

    case STM_TRIGGER_CANCEL_LINK_INHIBITED:     /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {

            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* cancel link inhibited */
        ln->stFlags &= ~LINK_INHIBITED;
        break;

    case STM_TRIGGER_UNINHIBIT_REQUEST:         /* from TLAC */
        /* obtain accessibility information for remote */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_ERROR(("Link available for no link set\n"));

            return (ITS_SUCCESS);
        }

        /* if SP accessible */
        if (AdjacentAccessible(ls))
        {
            TLAC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_UNINHIBIT_POSSIBLE,
                           NULL, 0,
                           linkSet, linkCode);
        }
        else
        {
            TLAC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_UNINHIBIT_IMPOSSIBLE,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case STM_TRIGGER_LINK_UNAVAILABLE:          /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* mark link unavailable */
        LINK_SetLinkStatus(ln, ITS_FALSE);
        
        /*
         * NOTE: This may cause the linkSet to transition to !isUp.
         * See STM_TRIGGER_LINK_AVAILABLE.
         */
        LINK_SetLinkState(ln, ITS_FALSE);

         /* get new linkSet state */
        if (LINKSET_GetLinkSetState(ln->linkSet, &isUp) != ITS_SUCCESS)
            MTP3_ERROR(("Can't find link set %d\n", ln->linkSet->linkSet));

         /* Increament the counter for Link Failure */
        if (!isUp)
            PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_SLS_UNAVAILABLE);

        /* if any traffic on link */
        {
            /* if emergency */
            if (EmergencyState(linkSet, linkCode))
            {
                LLSC_Main_CCITT(MTP3_STM_TSRC,
                               SLM_TRIGGER_EMERGENCY,
                               NULL, 0,
                               linkSet, linkCode);
            }

            /* if not any alternative link in link set */
            if (!AlternateLink(ln->linkSet, ln))
            {
                DeactivateLinkSet(ln->linkSet);
            }
        }
        break;

    case STM_TRIGGER_ROUTE_UNAVAILABLE:         /* from RTPC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }
        /* if route used */
        if (ri->flags & ROUTE_STP_IN_USE)
        {
            MTP3_DEBUG(("TSRC_Main: STP in use.\n"));

            /* mark route unavailable */
            ri->isAllowed = ITS_FALSE;

            /* FIXME: All of these want destination */
            if (trigger == STM_TRIGGER_TCP)
            {
                RSRT_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_TCP_RCVD,
                               sif, len,
                               linkSet, linkCode);
            }

            /* FIXME: the difference, please: if route currently in use */
            if (ri->flags & ROUTE_STP_IN_USE)
            {
                /*
                 * note: the order is changed here.  There's no point
                 * in doing TFRC first, as the calls to RTAC and RTRC
                 * will not have been made since TFRC is synchronous.
                 * therefore, move this.
                 */
                RTAC_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_FORCED_REROUTE,
                               sif, len,
                               linkSet, linkCode);

                RTRC_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_FORCED_REROUTE,
                               sif, len,
                               linkSet, linkCode);

                /* moved to here */
                TFRC_Main_CCITT(MTP3_STM_TSRC,
                               STM_TRIGGER_ROUTE_UNAVAILABLE,
                               sif, len,
                               linkSet, linkCode);

                /* FIXME: if option */
                if (ITS_FALSE)
                {
                    RTAC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   sif, len,
                                   linkSet, linkCode);

                    RTRC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_CONTROLLED_REROUTE,
                                   sif, len,
                                   linkSet, linkCode);
                }
            }

            if (ri->basic.dpc == ri->linkSet->adjacent)
            {
                DeactivateLinkSet(ri->linkSet);
            }
            else
            {
                UnavailableRoute(ri);
            }
        }
        else
        {
            MTP3_DEBUG(("TSRC_Main: STP NOT in use.\n"));
        }
        break;

    case STM_TRIGGER_LINK_AVAILABLE:            /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);

        if (ln == NULL)
        {
            MTP3_ERROR(("Cant find link\n"));

            return (ITS_EINVALIDARGS);
        }

        if (!SendingStatus_CCITT())
        {
            /* mark link available */
            /*ln->isAllowed = ITS_TRUE;*/
            LINK_SetLinkStatus(ln, ITS_TRUE);

            /* if not emergency */
            if (!EmergencyState(linkSet, linkCode))
            {
                LLSC_Main_CCITT(MTP3_STM_TSRC,
                               SLM_TRIGGER_EMERGENCY_CEASES,
                               NULL, 0,
                               linkSet, linkCode);
            }

            /* if no other links available in link set */
            if (!AlternateLink(ln->linkSet, ln))
            {
                /* if adjacent SP inaccessible */
                if (AdjacentAccessible(ln->linkSet))
                {
                    MTP3_DEBUG(("TSRC_Main: adjacent accessible %d\n", ln->linkCode));

                    /* FIXME: Network option:  Start route set test: RSRT */

                    /* mark link becoming available */
                    ln->stFlags |= LINK_COMING_AVAILABLE;

                    /*
                     * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                     * and isAllowed, but until this function call, the
                     * linkSet is not up!
                     */
                    LINK_SetLinkState(ln, ITS_TRUE);

                    /* for each destination (cluster) for which link set may be used */
                    for (count = 0, tmp = DSMQUEUE_HEAD(ln->linkSet->routes);
                         tmp != NULL && count < DSMQUEUE_COUNT(ln->linkSet->routes);
                         count++, tmp = DSMQUEUE_NEXT(ln->linkSet->routes, tmp) )
                    {
                        /* select one of concerned destinations */
                        memcpy(&ri, tmp->data, sizeof(ri));

                        rinfo.basic = ri->basic;
                        rinfo.linkSet = ri->linkSet->linkSet;
                        rinfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
                        rinfo.priority = ITS_SS7_DEFAULT_PRI;
                        rinfo.sls = ITS_SS7_DEFAULT_SLS;

                        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                                       &firstMatch, &lastMatch,
                                                       &whichLinkCode,
                                                       ITS_FALSE)) == NULL)
                        {
                            MTP3_ERROR(("Can't find match\n"));

                            return (ITS_FALSE);
                        }

                        /** FIXME **/
                        /* Fix core problem after adding dummy route-linkSet,
                           we should verify that whichEntry is always positive.
                        */

                        if (whichEntry < 0)
                        {
                            MTP3_ERROR(("Can't find link with associated route \n"));

                            return (ITS_FALSE);
                        }

                        /* if route status is available */
                        if (ri->isAllowed && !ri->isRestricted)
                        {
                            AvailableRoute(ln,
                                           ent, whichEntry,
                                           firstMatch, lastMatch);
                        }
                        /* else if route status is restricted */
                        else if (ri->isRestricted)
                        {
                            RestrictedRoute(ln,
                                            ent, whichEntry,
                                            firstMatch, lastMatch);
                        }
                    }

                    /* cancel link becoming available */
                    ln->stFlags &= ~LINK_COMING_AVAILABLE;
                }
                else
                {
                    MTP3_DEBUG(("TSRC_Main: !AdjacentAccessible %d\n", ln->linkCode));

                    /*
                     * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                     * and isAllowed, but until this function call, the
                     * linkSet is not up!
                     */
                    LINK_SetLinkState(ln, ITS_TRUE);

                    if (!SPRestarting_CCITT())
                    {
                        ls = LINKSET_FindLinkSet(linkSet);
                        if (ls == NULL)
                        {
                            MTP3_ERROR(("Link available for no link set\n"));

                            return (ITS_SUCCESS);
                        }

                        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, ls->adjacent,
                                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                                 FAMILY_ITU,
                                                                 ls->ni, ls->linkSet,
                                                                 ITS_SS7_DEFAULT_LINK_CODE,
                                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
                        {
                            MTP3_DEBUG(("Unable to parse destination %08x\n", ls->adjacent));

                            return (ret);
                        }

                        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                                       &firstMatch, &lastMatch,
                                                       &whichLinkCode,
                                                       ITS_FALSE)) == NULL)
                        {
                            MTP3_ERROR(("Can't find match\n"));

                            return (ITS_FALSE);
                        }

                        ri = ent->entries[whichEntry];

                        /* cancel inhibited links to adjacent point */
                        for (i = 0; i < ls->numLinks; i++)
                        {
                            ls->links[i]->stFlags &= ~LINK_INHIBITED;
                        }

                        /* mark adjacent SP restarting */
                        ls->adjRestart = ITS_TRUE;

                        MTP3_HDR_SET_SIO(omtp3, ls->ni);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                                    &omtp3, NULL, 0);

                        RSRT_Main_CCITT(MTP3_STM_TSRC,
                                       SRM_TRIGGER_ADJACENT_RESTARTING,
                                       ev.data, ev.len,
                                       linkSet, linkCode);

                        TLAC_Main_CCITT(MTP3_STM_TSRC,
                                       STM_TRIGGER_ADJACENT_SP_RESTARTING,
                                       ev.data, ev.len,
                                       linkSet, linkCode);

                        ITS_EVENT_TERM(&ev);

                        /* start T28 */
                        tc.timerId = MTP3_T28;
                        tc.data.routeInfo.pointCode = ls->adjacent;
                        tc.data.routeInfo.linkSet = linkSet;
                        tc.data.routeInfo.sio = ri->linkSet->ni;

                        ri->t28 =
                            TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                               __ccitt_t28 * USEC_PER_MILLISEC,
                                               &tc, sizeof(MTP3_TimerContext));

                        /* Build SNMM traffic restart waiting */
                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                        SNMM_HC0_SET(osnmm, SNMM_HC0_TRM);
                        SNMM_HC1_SET(osnmm, SNMM_HC1_TRW);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                        SNMM_Encode(&ev, &omtp3, &osnmm);

                        HMRT_Main_CCITT(MTP3_STM_TSRC,
                                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                       ev.data, ev.len,
                                       linkSet, linkCode);

                        ITS_EVENT_TERM(&ev);

                        UpdateAdjacent(ls);

                        /* stop T30 */
                        if (ri->t30 != TIMER_BAD_SERIAL)
                        {
                            TIMERS_CancelSharedTimer(ri->t30);
                            ri->t30 = TIMER_BAD_SERIAL;
                        }

                        /* Build SNMM traffic restart allowed */
                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                        SNMM_HC0_SET(osnmm, SNMM_HC0_TRM);
                        SNMM_HC1_SET(osnmm, SNMM_HC1_TRA);

                        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                        SNMM_Encode(&ev, &omtp3, &osnmm);

                        HMRT_Main_CCITT(MTP3_STM_TSRC,
                                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                       ev.data, ev.len,
                                       linkSet, linkCode);

                        ITS_EVENT_TERM(&ev);

                        /* start T29 */
                        tc.timerId = MTP3_T29;
                        tc.data.linkInfo.linkSet = linkSet;
                        tc.data.linkInfo.linkCode = linkCode;

                        ri->t29 =
                            TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                               __ccitt_t29 * USEC_PER_MILLISEC,
                                               &tc, sizeof(MTP3_TimerContext));
                    }
                    else /* SP is restarting */
                    {
                        /* Maintenance: this is the same code as if the SP wasn't
                         * accessible (above) */

                        /* mark link becoming available */
                        ln->stFlags |= LINK_COMING_AVAILABLE;

                        /*
                         * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                         * and isAllowed, but until this function call, the
                         * linkSet is not up!
                         */
                        LINK_SetLinkState(ln, ITS_TRUE);

                        /* for each destination (cluster) for which link set may be used */
                        for (count = 0, tmp = DSMQUEUE_HEAD(ln->linkSet->routes);
                             tmp != NULL && count < DSMQUEUE_COUNT(ln->linkSet->routes);
                             count++, tmp = DSMQUEUE_NEXT(ln->linkSet->routes, tmp) )
                        {
                            /* select one of concerned destinations */
                            memcpy(&ri, tmp->data, sizeof(ri));

                            rinfo.basic = ri->basic;
                            rinfo.linkSet = ri->linkSet->linkSet;
                            rinfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
                            rinfo.priority = ITS_SS7_DEFAULT_PRI;
                            rinfo.sls = ITS_SS7_DEFAULT_SLS;

                            if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                                           &firstMatch, &lastMatch,
                                                           &whichLinkCode,
                                                           ITS_FALSE)) == NULL)
                            {
                                MTP3_ERROR(("Can't find match\n"));

                                return (ITS_FALSE);
                            }

                            /** FIXME **/
                            /* Fix core problem after adding dummy route-linkSet,
                               we should verify that whichEntry is always positive.
                            */

                            if (whichEntry < 0)
                            {
                                MTP3_ERROR(("Can't find link with associated route \n"));
                                return (ITS_FALSE);
                            }

                            /* if route status is available */
                            if (ri->isAllowed && !ri->isRestricted)
                            {
                                AvailableRoute(ln,
                                               ent, whichEntry,
                                               firstMatch, lastMatch);
                            }
                            /* else if route status is restricted */
                            else if (ri->isRestricted)
                            {
                                RestrictedRoute(ln,
                                                ent, whichEntry,
                                                firstMatch, lastMatch);
                            }
                        }

                        /* cancel link becoming available */
                        ln->stFlags &= ~LINK_COMING_AVAILABLE;
                    }
                }
            }
            else
            {
                MTP3_DEBUG(("TSRC_Main: AlternativeLink %d\n", ln->linkCode));

                /*
                 * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                 * and isAllowed, but until this function call, the
                 * linkSet is not up!
                 */
                LINK_SetLinkState(ln, ITS_TRUE);

                /* if danger of congestion on normal link set subsides */
                if (!DangerOfCongestion(ln->linkSet))
                {
                    MTP3_POINT_CODE pc;

                    if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, ln->linkSet->adjacent,
                                                             REMOTE_ROUTE, ROUTE_DPC_NI,
                                                             FAMILY_ITU,
                                                             ln->linkSet->ni,
                                                             ln->linkSet->linkSet,
                                                             ln->linkCode,
                                                             ITS_SS7_DEFAULT_LINK_PRI,
                                                             ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
                    {
                        MTP3_DEBUG(("Unable to parse destination %08x\n", ln->linkSet->adjacent));

                        return (ret);
                    }

                    if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                                   &firstMatch, &lastMatch,
                                                   &whichLinkCode,
                                                   ITS_FALSE)) == NULL)
                    {
                        MTP3_ERROR(("Can't find match\n"));

                        return (ITS_FALSE);
                    }

                    ri = ent->entries[whichEntry];

                    /* mark destination (cluster) accessible */
                    ri->dest->status = DESTINATION_AVAILABLE;

                    MTP3_PC_SET_VALUE(pc, ln->linkSet->adjacent);

                    MTP3_HDR_SET_SIO(omtp3, ln->linkSet->ni);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ln->linkSet->adjacent);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                    MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                                &omtp3, NULL, 0);

                    RTAC_Main_CCITT(MTP3_STM_TSRC,
                                   SRM_TRIGGER_DEST_ACCESS,
                                   ev.data, ev.len,
                                   linkSet, linkCode);

                    ITS_EVENT_TERM(&ev);
                }
            }
        }
        else /* sending status */
        {
            /* if no other links available in link set */
            if (!AlternateLink(ln->linkSet, ln))
            {
                /*
                 * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                 * and isAllowed, but until this function call, the
                 * linkSet is not up!
                 */
                LINK_SetLinkState(ln, ITS_TRUE);

                /* Build SNMM traffic restart waiting */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ln->linkSet->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ln->linkSet->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ln->linkSet->lpc);

                SNMM_HC0_SET(osnmm, SNMM_HC0_TRM);
                SNMM_HC1_SET(osnmm, SNMM_HC1_TRW);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &osnmm);


                HMRT_Main_CCITT(MTP3_STM_TSRC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               linkSet, linkCode);

                ITS_EVENT_TERM(&ev);
            }
            else
            {
                /*
                 * NOTE: Careful here!  TLAC and LSAC manipulate isUp
                 * and isAllowed, but until this function call, the
                 * linkSet is not up!
                 */
                LINK_SetLinkState(ln, ITS_TRUE);
            }
        }
        break;

    case STM_TRIGGER_ROUTE_RESTRICTED:          /* from RTRC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }
        /* if route used */
        if (ri->flags & ROUTE_STP_IN_USE)
        {
            /* if not route marked restricted */
            if (!(ri->isRestricted))
            {
                /* mark route restricted */
                ri->isRestricted = ITS_TRUE;

                /* if any links in route available */
                if (LinkSetAvailable(ri->linkSet))
                {
                    if (SPRestarting_CCITT())
                    {
                        RestrictedRoute(NULL,
                                        ent, whichEntry,
                                        firstMatch, lastMatch);
                    }
                    else
                    {
                        /* if not adjacent SP inaccessible */
                        if (!AdjacentAccessible(ri->linkSet))
                        {
                            RestrictedRoute(NULL,
                                            ent, whichEntry,
                                            firstMatch, lastMatch);
                        }
                        else
                        {
                            UpdateAdjacent(ri->linkSet);

                            RestrictedRoute(NULL,
                                            ent, whichEntry,
                                            firstMatch, lastMatch);
                        }
                    }
                }
            }
        }
        break;

    case STM_TRIGGER_DANGER_OF_CONGESTION:      /* from HMDC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }
        /* is alternate link set in use */
        if (ent->entries[whichEntry]->priority != 0)
        {
            /* if not destination marked restricted */
            if (ent->status != DESTINATION_RESTRICTED)
            {
                /* stop T11 */
                if (ri->t11 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ri->t11);
                    ri->t11 = TIMER_BAD_SERIAL;
                }

                RTRC_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_DEST_RESTRICT,
                               NULL, 0,
                               linkSet, linkCode);

                /* mark destination restricted */
                ent->status = DESTINATION_RESTRICTED;
            }
        }
        else
        {
            /* if link set partially failed */
            {
                RTRC_Main_CCITT(MTP3_STM_TSRC,
                               SRM_TRIGGER_MSG_FOR_RESTRICTED_DEST,
                               sif, len,
                               linkSet, linkCode);
            }
        }
        break;

    case STM_TRIGGER_T11:                       /* from timer control */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }
        /* while affected destination (cluster) remain */
        for (count = 0, tmp = DSMQUEUE_HEAD(ri->linkSet->routes);
             tmp != NULL && count < DSMQUEUE_COUNT(ri->linkSet->routes);
             count++, tmp = DSMQUEUE_NEXT(ri->linkSet->routes, tmp) )
        {
            ROUTE_InfoPtr ri;

            /* select an effected destination (cluster) */
            memcpy(&ri, tmp->data, sizeof(ri));

            /* mark destination (cluster) restricted */
            ri->dest->status = DESTINATION_RESTRICTED;

            MTP3_PC_SET_VALUE(dpc, ri->basic.dpc);

            MTP3_HDR_SET_SIO(omtp3, ri->linkSet->ni);
            MTP3_RL_SET_DPC(omtp3.label, dpc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            RTRC_Main_CCITT(MTP3_STM_TSRC,
                           SRM_TRIGGER_DEST_RESTRICT,
                           ev.data, ev.len,
                           linkSet, linkCode);

            ITS_EVENT_TERM(&ev);
        }
        break;

    case STM_TRIGGER_LINK_CONGESTION_STATUS:    /* implementation dependent */
        /* determine affected destinations */

        ls = LINKSET_FindLinkSet(linkSet);

        if (ls != NULL)
        {
            MTP3_HDR_SET_SIO(omtp3, ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);

            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            if (sif[0] == L2_L3_CONGESTION_ONSET)
            {
                /* FIXME: If relevent, start T31 */
                MTP2_SendData_CCITT(linkSet, linkCode,
                                   L3_L2_FLOW_CONTROL_START,
                                   NULL, 0);
            }
            else if (sif[0] == L2_L3_CONGESTION_ABATES)
            {
                MTP2_SendData_CCITT(linkSet, linkCode,
                                   L3_L2_FLOW_CONTROL_STOP,
                                   NULL, 0);
            }

            TSFC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_DEST_CONGESTION_STATUS,
                           ev.data, ev.len,
                           linkSet, linkCode);

            ITS_EVENT_TERM(&ev);
        }
        break;

    case STM_TRIGGER_SENDING_STATUS_PHASE:      /* from TPRC */
        SendingStatusSet_CCITT(ITS_TRUE);
        break;

    case STM_TRIGGER_SEND_TRW:                  /* from TPRC */
#if 0
/* ITU doesn't do this */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Build SNMM traffic restart waiting */
        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

        SNMM_HC0_SET(osnmm, SNMM_HC0_TRM);
        SNMM_HC1_SET(osnmm, SNMM_HC1_TRW);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        SNMM_Encode(&ev, &omtp3, &osnmm);


        HMRT_Main_CCITT(MTP3_STM_TSRC,
                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                       ev.data, ev.len,
                       linkSet, linkCode);

        ITS_EVENT_TERM(&ev);
#endif
        break;

    case STM_TRIGGER_TRAFFIC_RESTART_ALLOWED:   /* from TPRC */
        pc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }
        else
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ret);
        }

        /* if from adjacent restarting SP */
        if (ri->basic.dpc == ri->linkSet->adjacent ||
            ri->linkSet->adjRestart)
        {
            /* stop T28 */
            if (ri->t28 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t28);
                ri->t28 = TIMER_BAD_SERIAL;
            }

            /* stop T25 */
            if (ri->t25 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t25);
                ri->t25 = TIMER_BAD_SERIAL;
            }

            TrafficRestart(ri);
        }
        else
        {
            StartTrafficRestart(ri);
        }
        break;

    case STM_TRIGGER_T25:                       /* from timer control */
    case STM_TRIGGER_T28:                       /* from timer control */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }

        if (trigger == STM_TRIGGER_T25)
        {
            ri->t25 = TIMER_BAD_SERIAL;
        }
        else
        {
            ri->t28 = TIMER_BAD_SERIAL;
        }

        TrafficRestart(ri);
        break;

    case STM_TRIGGER_TRAFFIC_RESTART_WAITING:   /* from HMDT */
        pc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /* may be from non-adjacent */
        linkSet = MTP3_FindAdjacent_CCITT(ni, pc, linkSet);

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }

        if (ent == NULL || ri == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        /* if from adjacent SP */
        if (ri->basic.dpc == ri->linkSet->adjacent)
        {
            /* stop T28 */
            if (ri->t28 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t28);
                ri->t28 = TIMER_BAD_SERIAL;
            }

            /* start T25 */
            tc.timerId = MTP3_T25;
            tc.data.routeInfo.pointCode = ri->basic.dpc;
            tc.data.routeInfo.linkSet = ri->linkSet->linkSet;
            tc.data.routeInfo.sio = ri->linkSet->ni;

            ri->t25 =
                 TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t25 * USEC_PER_MILLISEC,
                                    &tc, sizeof(MTP3_TimerContext));

#if 0
            /* stop T25 */
            if (ri->t25 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t25);
                ri->t25 = TIMER_BAD_SERIAL;
            }
#endif
        }
        else
        {
            if (SPRestarting_CCITT())
            {
                /* start T25 */
                tc.timerId = MTP3_T25;
                tc.data.routeInfo.pointCode = ri->basic.dpc;
                tc.data.routeInfo.linkSet = ri->linkSet->linkSet;
                tc.data.routeInfo.sio = ri->linkSet->ni;

                ri->t25 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t25 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

            }
            else
            {
                StartTrafficRestart(ri);
            }
        }
        break;

    case STM_TRIGGER_SEND_STATUS:               /* from TPRC */
        if (SendingStatus_CCITT())
        {
            DSM_TableIterate(DSM_Mtp3FtGroupId,
                             DSM_TABLE_DESTINATIONS,
                             NULL, NULL, StatusIterate);

            TPRC_Main_CCITT(MTP3_STM_TSRC,
                           STM_TRIGGER_STATUS_SENT,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case STM_TRIGGER_T29:
    case STM_TRIGGER_T30:
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) != NULL)
        {
            ri = ent->entries[whichEntry];
        }
        if (ri)
        {
            if (trigger == STM_TRIGGER_T29)
            {
                ri->t29 = TIMER_BAD_SERIAL;
            }
            else if (trigger == STM_TRIGGER_T30)
            {
                ri->t30 = TIMER_BAD_SERIAL;
            }
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
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
 ****************************************************************************/
int
TRCC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1], omtp3;
    SNMM_MESSAGE *snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                              sizeof(ITS_OCTET)];
    MTP3_TimerContext tc;
    ITS_UINT pc;
    ITS_OCTET ni, congLevel;
    ITS_EVENT ev;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, ret;
    SS7_Destination *ent;
    ROUTE_MatchInfo rinfo;
    ROUTE_Info *ri;

    MTP3_TRACE_ENTRY_CCITT(MTP3_STM_TRCC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* wants a point code to get a route? */    
    switch (trigger)
    {
    case STM_TRIGGER_DEST_CONGESTION_STATUS:    /* from RTCC */
        pc = SNMM_TRANSFER_CONTROL_GET_DEST(snmm->data.transferControl);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_CCITT(2477, __FILE__, __LINE__,"dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }

        ri = ent->entries[whichEntry];

        congLevel = SNMM_TRANSFER_CONTROL_GET_STATUS(snmm->data.transferControl);

        MTP3_HDR_SET_SIO(omtp3, ni);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, pc);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &omtp3, NULL, 0);

        if (ri->congestionState == CONGESTION_IDLE)
        {
            /* store destination congestion status */
            ri->congLevel = congLevel;

            ri->congestionState = CONGESTION_WAIT_1;
            
            TSRC_Main_CCITT(MTP3_STM_TRCC,
                           STM_TRIGGER_ACCESSIBILITY_REQUEST,
                           ev.data, ev.len,
                           linkSet, linkCode);
            
        }
        else if (ri->congestionState == CONGESTION_WAIT_1)
        {
            /* if new congestion status greater */
            if (congLevel > ri->congLevel)
            {
                /* store congestion status */
                ri->congLevel = congLevel;
            }
        }
        else if (ri->congestionState == CONGESTION_WAIT_2)
        {
            /* if new congestion status greater */
            if (congLevel > ri->congLevel)
            {
                /* update congestion status */
                ri->congLevel = congLevel;
                
                TSFC_Main_CCITT(MTP3_STM_TRCC,
                               STM_TRIGGER_DEST_CONGESTION_STATUS,
                               ev.data, ev.len,
                               linkSet, linkCode);
                
                /* stop T15 */
                if (ri->t15 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ri->t15);
                }

                /* start T15 */
                tc.timerId = MTP3_T15;
                tc.data.routeInfo.pointCode = pc;
                tc.data.routeInfo.linkSet = linkSet;
                tc.data.routeInfo.sio = ni;

                ri->t15 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t15 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }
            /* else if new congestion status equal */
            else if (congLevel == ri->congLevel)
            {
                /* stop T15 */
                if (ri->t15 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ri->t15);
                    ri->t15 = TIMER_BAD_SERIAL;
                }

                /* start T15 */
                tc.timerId = MTP3_T15;
                tc.data.routeInfo.pointCode = pc;
                tc.data.routeInfo.linkSet = linkSet;
                tc.data.routeInfo.sio = ni;

                ri->t15 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t15 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }
        }
        else if (ri->congestionState == CONGESTION_WAIT_3)
        {
            RCAT_Main_CCITT(MTP3_STM_TRCC,
                           SRM_TRIGGER_STOP_CONG_TEST,
                           ev.data, ev.len,
                           linkSet, linkCode);
            
            /* if new congestion status different */
            if (congLevel != ri->congLevel)
            {
                /* update congestion status */
                ri->congLevel = congLevel;
                
                TSFC_Main_CCITT(MTP3_STM_TRCC,
                               STM_TRIGGER_DEST_CONGESTION_STATUS,
                               ev.data, ev.len,
                               linkSet, linkCode);
            }
            
            /* start T15 */
            tc.timerId = MTP3_T15;
            tc.data.routeInfo.pointCode = pc;
            tc.data.routeInfo.linkSet = linkSet;
            tc.data.routeInfo.sio = ni;

            ri->t15 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t15 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
            
            ri->congestionState = CONGESTION_WAIT_2;
        }
        break;
        
    case STM_TRIGGER_DECR_DEST_CONG_STATUS:     /* from RCAT */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_CCITT(2477, __FILE__, __LINE__,"dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }

        ri = ent->entries[whichEntry];

        if (ri->congestionState == CONGESTION_WAIT_3)
        {
            /* decrement congestion status */
            ri->congLevel--;
            
            TSFC_Main_CCITT(MTP3_STM_TRCC,
                           STM_TRIGGER_DEST_CONGESTION_STATUS,
                           sif, len,
                           linkSet, linkCode);
        
            /* if congestion status equal zero */
            if (ri->congLevel == 0)
            {
                ri->congestionState = CONGESTION_IDLE;
            }
            else
            {
                RCAT_Main_CCITT(MTP3_STM_TRCC,
                               SRM_TRIGGER_START_CONG_TEST,
                               sif, len,
                               linkSet, linkCode);
            }
        }
        break;
        
    case STM_TRIGGER_ACCESSIBILITY_DATA:        /* from TSRC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_CCITT(2477, __FILE__, __LINE__,"dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }

        ri = ent->entries[whichEntry];

        if (ri->congestionState == CONGESTION_WAIT_1)
        {
            ITS_BOOLEAN accessible = linkCode;

            /*
             * NOTE: The linkCode contains a boolean indicating if the
             * destination is accessible.
             */
            if (accessible)
            {
                /* update congestion status */
                ri->congLevel = 0;
                
                TSFC_Main_CCITT(MTP3_STM_TRCC,
                               STM_TRIGGER_DEST_CONGESTION_STATUS,
                               sif, len,
                               linkSet, linkCode);
                
                /* start T15 */
                tc.timerId = MTP3_T15;

                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t15 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
                ri->congestionState = CONGESTION_WAIT_2;
            }
        }
        break;
        
    case STM_TRIGGER_DEST_INACCESS:             /* from TSRC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_CCITT(2477, __FILE__, __LINE__,"dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->congestionState == CONGESTION_WAIT_1)
        {
            ri->congestionState = CONGESTION_IDLE;
        }
        else if (ri->congestionState == CONGESTION_WAIT_2)
        {
            /* update congestion status to zero */
            ri->congLevel = 0;
            
            /* stop T15 */
            if (ri->t15 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ri->t15);
                ri->t15 = TIMER_BAD_SERIAL;
            }
            
            ri->congestionState = CONGESTION_IDLE;
        }
        else if (ri->congestionState == CONGESTION_WAIT_3)
        {
            /* update congestion status to zero */
            ri->congLevel = 0;
            
            RCAT_Main_CCITT(MTP3_STM_TRCC,
                           SRM_TRIGGER_STOP_CONG_TEST,
                           sif, len,
                           linkSet, linkCode);
            
            ri->congestionState = CONGESTION_IDLE;
        }
        break;
        
    case STM_TRIGGER_T15:                       /* from timer control */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_CCITT(2477, __FILE__, __LINE__,"dpc %08x ni %x",pc,ni);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->congestionState == CONGESTION_WAIT_2)
        {
            RCAT_Main_CCITT(MTP3_STM_TRCC,
                           SRM_TRIGGER_CONG_TEST,
                           NULL, 0,
                           linkSet, linkCode);
            
            ri->congestionState = CONGESTION_WAIT_3;
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
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
static ITS_BOOLEAN
ChangeoverRequired(SS7_LinkPtr ln)
{   
    if (ln != NULL)
    {
        /* is signalling Link Loaded */
        return ( ( ln->isUp  && ln->isAllowed) || (ln->stFlags & LINK_COP) );
        /*  return ( (ln->slFlags & LINK_FIRST_FAILURE) && ln->isAllowed); */
    }

    MTP3_DEBUG(("ChangeoverRequired: Link Pointer is NULL"));
    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Build ChangeOver Message
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
static ITS_BOOLEAN
BuildChangeOverMsg(MTP3_HEADER *mtp3,
                   SNMM_MESSAGE *snmm, SS7_LinkSetPtr ls, 
                   SS7_LinkPtr ln, ITS_OCTET hc0, 
                   ITS_OCTET hc1)
{
    MTP3_HDR_SET_SIO(*mtp3, MTP3_SIO_SNMM | ls->ni);
    MTP3_RL_SET_DPC_VALUE(mtp3->label, ls->adjacent);
    MTP3_RL_SET_OPC_VALUE(mtp3->label, ls->lpc);
    MTP3_RL_SET_SLS(mtp3->label, ln->linkCode);

    switch (hc0) 
    {
    case SNMM_HC0_CHM:
        /* Build SNMM changeover ack */
        SNMM_HC0_SET(*snmm, SNMM_HC0_CHM);

        if (hc1 == SNMM_HC1_COA)
        {
            if (ln->isSAAL)
            {
                SNMM_HC1_SET(*snmm, SNMM_HC1_XCA);
            }
            else
            {
                SNMM_HC1_SET(*snmm, SNMM_HC1_COA);
            }
        }
        else if (hc1 == SNMM_HC1_COO)
        {
            if (ln->isSAAL)
            {
                SNMM_HC1_SET(*snmm, SNMM_HC1_XCO);
            }
            else
            {
                SNMM_HC1_SET(*snmm, SNMM_HC1_COO);
            }
        }    
        
        /* set FSN */
        if (ln->isSAAL)
        {
            SNMM_CHANGEOVER_SET_FSN_SAAL(snmm->data.changeOver, ln->localBSN);
        }
        else
        {
            SNMM_CHANGEOVER_SET_FSN(snmm->data.changeOver, ln->localBSN);
            MTP3_DEBUG(("*** Set ChangeOver FSN: fsn= %02x :bsn %d\n",
                         snmm->data.changeOver.fsn[0], ln->localBSN));
        }
  
        break;
    
    case SNMM_HC0_ECM:
        SNMM_HC0_SET(*snmm, SNMM_HC0_ECM);

        if (hc1 == SNMM_HC1_ECO)
        {
            SNMM_HC1_SET(*snmm, SNMM_HC1_ECO);
        }
        else if (hc1 == SNMM_HC1_ECA)
        {        
            SNMM_HC1_SET(*snmm, SNMM_HC1_ECA);
        }

        break;
    }
    return (ITS_TRUE);
}

/*.implementation:static
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
static ITS_BOOLEAN
RoutingChanged(ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *req, *resp;
    ITS_OCTET reqLS, reqLC, ni;
    ITS_UINT pc, i;
    SS7_Destination *dest;
    ITS_UINT ols, nls;

    /*
     * if we get this, there is *no* alternate route at all.
     * This falls under 6.2.5.
     */
    if (linkSet == ITS_SS7_DEFAULT_LINK_SET &&
        linkCode == ITS_SS7_DEFAULT_LINK_CODE)
    {
        return (ITS_TRUE);
    }

    ITS_C_ASSERT(len >= (sizeof(ITS_OCTET) +
                         2 * sizeof(MTP3_HEADER) +
                         2 * sizeof(ITS_OCTET)));

    resp = (MTP3_HEADER *)&sif[sizeof(ITS_OCTET)];
    req = (MTP3_HEADER *)&sif[sizeof(ITS_OCTET) +
                                   sizeof(MTP3_HEADER)];
    reqLS = sif[sizeof(ITS_OCTET) +
                2 * sizeof(MTP3_HEADER)];
    reqLC = sif[sizeof(ITS_OCTET) +
                2 * sizeof(MTP3_HEADER) +
                sizeof(ITS_OCTET)];

    /*
     * if the link set is the same, the routing is different
     * if the link is different (alternate link).
     */
    if (reqLS == linkSet && reqLC != linkCode)
    {
        return (ITS_TRUE);
    }

    pc = MTP3_RL_GET_DPC_VALUE(resp->label);
    ni = MTP3_HDR_GET_SIO(*resp) & MTP3_NIC_MASK;

    dest = ROUTE_FindDestination(pc, ni, FAMILY_ITU);

    ols = nls = (ITS_UINT)-1;
    for (i = 0; i < dest->numEntries; i++)
    {
        if (dest->entries[i]->basic.type == REMOTE_ROUTE &&
            (dest->entries[i]->basic.style == ROUTE_DPC_NI ||
             dest->entries[i]->basic.style == ROUTE_DPC_OPC_NI))
        {
            if (dest->entries[i]->linkSet->linkSet == linkSet)
            {
                nls = i;
            }
            if (dest->entries[i]->linkSet->linkSet == reqLS)
            {
                ols = i;
            }
        }
    }

    if (dest->entries[nls]->priority < dest->entries[ols]->priority)
    {
        return (ITS_FALSE);
    }

    return (MTP3_RL_GET_DPC_VALUE(req->label) !=
            MTP3_RL_GET_DPC_VALUE(resp->label) ||
            reqLS != linkSet ||
            reqLC != linkCode);
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
 ****************************************************************************/
int
TCOC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_TimerContext tc;
    SS7_LinkPtr ln;
    SS7_LinkSetPtr ls;
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1], *slsUnshift;
    MTP3_HEADER omtp3;
    SNMM_MESSAGE snmm, *snmm_ptr;
    ITS_EVENT ev, *fetched, *cocbEv;
    MTP3_EventRec evRec;
    ITS_UINT pc1;
    ITS_OCTET ni, sls, tls, tlc;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    SS7_Destination *dest;
    ROUTE_MatchInfo mi;

    MTP3_TRACE_ENTRY_CCITT(MTP3_STM_TCOC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* DO NOT RETURN HERE. */
    ln = LINK_FindLink(linkSet, linkCode);
    if (ln == NULL)
    {
        MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));
    }

    /* Do Not return, LinkSet sent by TSRC (alternate routing data)might be 
     * default linkset 
     */
    ls = LINKSET_FindLinkSet(linkSet);
    if (ls == NULL)
    {
        MTP3_DEBUG(("Can't find link set %d\n", linkSet));
    }

    if (ln != NULL)
    {
       MTP3_DEBUG(("**** TCOC: trigger: %d state:%d ***\n", trigger, ln->changeoverState));
    }

    /* Wants a link, I think */    
    switch (trigger)
    {
    case STM_TRIGGER_LINK_UNAVAILABLE:          /* from TLAC */
        if (ln->changeoverState == CHANGEOVER_IDLE)
        {
            /* buffer messages for affected link */
            /*ln->qPut = ITS_TRUE;*/
            LINK_SetLinkQPut(ln, ITS_TRUE);

            /* alternate route request */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            
            ln->changeoverState = CHANGEOVER_WAIT_1;

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);
            
            TSRC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           ev.data, ev.len, /* Tmp RL */
                           linkSet, linkCode);
            
            ITS_EVENT_TERM(&ev);
        }
        else if (ln->changeoverState == CHANGEOVER_RETRIEVING)
        {
            /* mark link unavailable */
            ln->stFlags |= LINK_IS_UNAVAILABLE;
        }
        break;
        
    case STM_TRIGGER_LINK_AVAILABLE:            /* from TLAC */
        if (ln->changeoverState == CHANGEOVER_WAIT_1)
        {
            /* stop T1 */
            TIMERS_CancelSharedTimer(ln->t1);
            ln->t1 = TIMER_BAD_SERIAL;

            /* these tasks should be carried out in the order shown */

            /*
             * NOTE: this order is backwards, but necessary.  MTP2_SendData
             * examines the qPut variable to determine if it should queue
             * or transmit the messages.
             *
             * NOTE 2: when MTP3 becomes multithreaded, we'll have to revisit
             * this.  The second platform might transmit while we are.  This
             * could be avoided by not committing the link info until the
             * queue is cleared.
             */

            /* stop buffering messages on restored link */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);

            /*
             * send buffered messages on restored link
             *
             * ROTATION COMMENT
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_CCITT(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            ln->changeoverState = CHANGEOVER_IDLE;    

            TLAC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_NOT_REQD,
                           NULL, 0,
                           linkSet, linkCode);
                
            TSRC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_NOT_REQD,
                           NULL, 0,
                           linkSet, linkCode);
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_2 ||
                 ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK ||
                 ln->changeoverState == CHANGEOVER_WAIT_5 ||
                 ln->changeoverState == CHANGEOVER_WAIT_6 ||
                 ln->changeoverState == CHANGEOVER_WAIT_8)
        {
            /*
             * NOTE: this order is backwards, but necessary.  MTP2_SendData
             * examines the qPut variable to determine if it should queue
             * or transmit the messages.
             *
             * NOTE 2: when MTP3 becomes multithreaded, we'll have to revisit
             * this.  The second platform might transmit while we are.  This
             * could be avoided by not committing the link info until the
             * queue is cleared.
             */

            /* stop buffering messages on restored link */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);

            /*
             * send buffered messages on restored link
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_CCITT(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            ln->changeoverState = CHANGEOVER_IDLE;      
            
            TLAC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_NOT_REQD,
                           NULL, 0,
                           linkSet, linkCode);
                
            TSRC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_NOT_REQD,
                           NULL, 0,
                           linkSet, linkCode);          
        }
        else if (ln->changeoverState == CHANGEOVER_RETRIEVING)
        {
            /* Cancel Link Unavailable */
            ln->stFlags &= (~LINK_IS_UNAVAILABLE);
        }
        break;
        
    case STM_TRIGGER_EMERG_CHANGEOVER_ORDER:    /* from TLAC */

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_EMER_CHANGEOVER);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_EMERG_CH_OVER);

        if (ln->changeoverState == CHANGEOVER_IDLE)
        {
            /* cancel remote BSNT retrieved */
            ln->stFlags &= (~LINK_REMOTE_BSNT_RETRIEVED);

            /* buffer messages for affected link */
            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_RETRIEVE_BSNT, NULL, 0);
            
            ln->changeoverState = CHANGEOVER_WAIT_5;
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_1 ||
                 ln->changeoverState == CHANGEOVER_WAIT_2)
        {
            /* do nothing */
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK)
        {
            /* stop T2 */
            TIMERS_CancelSharedTimer(ln->t2);
            ln->t2 = TIMER_BAD_SERIAL;
            ln->changeoverState = CHANGEOVER_IDLE;
            /* Increament the peg for ChangeOver */
            /* PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER); */

            if (ln->stFlags & LINK_LOCAL_BSNT_RETRIEVED)
            {                              
                BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_CHM,
                                                            SNMM_HC1_COA);

                if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                                  REMOTE_ROUTE, ROUTE_DPC_NI,
                                                  FAMILY_ITU,
                                                  ls->ni,
                                                  ls->linkSet,
                                                  ITS_SS7_DEFAULT_LINK_CODE,
                                                  ITS_SS7_DEFAULT_PRI,
                                                  ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Can't parse route info\n"));

                    MTP3_Alarm_CCITT(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                    return (ITS_EINVALIDARGS);
                }

                if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                               &firstMatch, &lastMatch,
                                               &whichLinkCode,
                                               ITS_FALSE)) == NULL)
                {
                    MTP3_ERROR(("Can't find route\n"));
                
                    return (ITS_EINVALIDARGS);
                }

                ITS_EVENT_INIT(&ev, 0, 0);
                FindAlternateRoute(dest, &omtp3,
                                   whichEntry, firstMatch, lastMatch,
                                   linkSet, linkCode,
                                   &tls, &tlc, &ev);

                ITS_EVENT_TERM(&ev);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for COA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);

                HMRT_Main_CCITT(MTP3_STM_TCOC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               tls, tlc);
                
                ITS_EVENT_TERM(&ev);
            }
            else
            {
                BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_ECM,
                                                            SNMM_HC1_ECA);

                if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                                  REMOTE_ROUTE, ROUTE_DPC_NI,
                                                  FAMILY_ITU,
                                                  ls->ni,
                                                  ls->linkSet,
                                                  ITS_SS7_DEFAULT_LINK_CODE,
                                                  ITS_SS7_DEFAULT_PRI,
                                                  ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Can't parse route info\n"));

                    MTP3_Alarm_CCITT(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                    return (ITS_EINVALIDARGS);
                }

                if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                               &firstMatch, &lastMatch,
                                               &whichLinkCode,
                                               ITS_FALSE)) == NULL)
                {
                    MTP3_ERROR(("Can't find route\n"));
       
                    return (ITS_EINVALIDARGS);
                }

                ITS_EVENT_INIT(&ev, 0, 0);
                FindAlternateRoute(dest, &omtp3,
                                   whichEntry, firstMatch, lastMatch,
                                   linkSet, linkCode,
                                   &tls, &tlc, &ev);

                ITS_EVENT_TERM(&ev);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for ECA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

                HMRT_Main_CCITT(MTP3_STM_TCOC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               tls, tlc);
            }

            LSAC_Main_CCITT(MTP3_STM_TCOC,
                           SLM_TRIGGER_STM_READY,
                           NULL, 0,
                           linkSet, linkCode);

            /*
             * do this first to avoid circular transmission
             */
            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            /*
             * send buffered messages on alternative links
             *
             * ROTATION COMMENT
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                ITS_C_ASSERT(ls != NULL);

                slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                /*
                 * NOTE: ITU doesn't need to undo bit rotation.
                 */
                /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                HMRT_Main_CCITT(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }
            
            TLAC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
            TSRC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_7)
        {
            /* cancel FSNC available */
            ln->stFlags &= (~LINK_REMOTE_BSNT_RETRIEVED);
            
            /* stop T1 */
            TIMERS_CancelSharedTimer(ln->t1);
            ln->t1 = TIMER_BAD_SERIAL;
            
            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_RETRIEVE_BSNT, NULL, 0);
            
            ln->changeoverState = CHANGEOVER_WAIT_8;
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_2)
        {
            /* SDL save construct: we save the information and
             * set the flag.
             */
            ln->stFlags |= LINK_CHANGE_OVER_RECEIVED;

            /* cancel FSNC available */
            ln->stFlags &= (~LINK_REMOTE_BSNT_RETRIEVED);

        }

        break;
        
    case STM_TRIGGER_ALTERNATE_ROUTE_DATA:      /* from TSRC */
        tls = sif[2 * sizeof(MTP3_HEADER) + sizeof(ITS_OCTET)];
        tlc = sif[2 * sizeof(MTP3_HEADER) + 2 * sizeof(ITS_OCTET)];

        ln = LINK_FindLink(tls, tlc);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", tls, tlc));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(tls);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", tls));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changeoverState == CHANGEOVER_WAIT_1)
        {
            if (ChangeoverRequired(ln))
            {
                MTP3_DEBUG(("Changeover Required %d:%d!\n", tls, tlc));

                if (linkSet != ITS_SS7_DEFAULT_LINK_SET &&
                    linkCode != ITS_SS7_DEFAULT_LINK_CODE &&
                    !(ln->stFlags & (LINK_REM_INHIBITED|LINK_LOC_INHIBITED|
                                     LINK_REM_BLOCKED|LINK_LOC_BLOCKED)))
                {
                    /* There is alternate, Route to exchange CO messages */

                    MTP2_SendData_CCITT(tls, tlc,
                                       L3_L2_RETRIEVE_BSNT, NULL, 0);
                    
                    ln->changeoverState = CHANGEOVER_WAIT_2;
                }
                else
                {
                    ln->changeoverState = CHANGEOVER_WAIT_7;

                    LSAC_Main_CCITT(MTP3_STM_TCOC,
                                   SLM_TRIGGER_STM_READY,
                                   NULL, 0,
                                   tls, tlc);
                    
                    /* start T1 */
                    tc.timerId = MTP3_T1;
                    tc.data.linkInfo.linkSet = tls;
                    tc.data.linkInfo.linkCode = tlc;

                    ln->t1 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                                __ccitt_t1 * USEC_PER_MILLISEC,
                                                &tc, sizeof(MTP3_TimerContext));
                    
                }
            }
            else
            {
                MTP3_DEBUG(("Changeover NOT Required %d:%d!", tls, tlc));

                LSAC_Main_CCITT(MTP3_STM_TCOC,
                               SLM_TRIGGER_STM_READY,
                               NULL, 0,
                               tls, tlc);
                
                /*
                 * NOTE: this order is backwards, but necessary.  MTP2_SendData
                 * examines the qPut variable to determine if it should queue
                 * or transmit the messages.
                 *
                 * NOTE 2: when MTP3 becomes multithreaded, we'll have to revisit
                 * this.  The second platform might transmit while we are.  This
                 * could be avoided by not committing the link info until the
                 * queue is cleared.
                 */

                /* stop buffering messages on restored link */
                /*ln->qPut = ITS_FALSE;*/
                 LINK_SetLinkQPut(ln, ITS_FALSE);

                /*
                 * send buffered messages on restored link
                 *
                 * NOTE: SLS unshifting not required here, as this is
                 * recovery (link bounce).
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                    fetched = &evRec.event;

                    MTP2_SendData_CCITT(L2_LINK_SET(fetched),
                                       L2_LINK_CODE(fetched),
                                       L2_MSG_TYPE(fetched),
                                       L2_LINK_DATA(fetched),
                                       (ITS_USHORT)(fetched->len -
                                        3 * sizeof(ITS_OCTET)));

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }

                ln->changeoverState = CHANGEOVER_IDLE;
                
                TLAC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               tls, tlc);
                
                TSRC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               tls, tlc);
            }
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_6)
        {
            if (ChangeoverRequired(ln))
            {
                if (ln->stFlags & LINK_REMOTE_BSNT_RETRIEVED)
                {
                    MTP2_SendData_CCITT(tls, tlc,
                                       L3_L2_RETRIEVE_MSGS,
                                       (ITS_OCTET *)&ln->remoteBSN, 
                                       sizeof(ITS_UINT));
            
                    /* mark link unavailable */
                    ln->stFlags |= LINK_IS_UNAVAILABLE;
            
                    ln->changeoverState = CHANGEOVER_RETRIEVING;
                }
                else
                {
                    ln->changeoverState = CHANGEOVER_IDLE;

                    LSAC_Main_CCITT(MTP3_STM_TCOC,
                                   SLM_TRIGGER_STM_READY,
                                   NULL, 0,
                                   tls, tlc);

                    /*
                     * do this first to avoid a circle.
                     */
                    HMRT_Main_CCITT(MTP3_STM_TCOC,
                                   SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                                   NULL, 0,
                                   tls, tlc);
            
                    /*
                     * send buffered messages on alternative links
                     *
                     * SLS unshifting *is* required here.  It's not terribly
                     * awful, though.
                     */
                    while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                    {
                        evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                        fetched = &evRec.event;

                        /* if this fails we're toast. */
                        ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                        ITS_C_ASSERT(ls != NULL);

                        slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                        sls = MTP3_RL_GET_SLS(slsUnshift->label);

                        /*
                         * NOTE: ITU doesn't need to undo bit rotation.
                         */
                        /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                        /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                        HMRT_Main_CCITT(MTP3_SMH_HMDT,
                                       SMH_TRIGGER_MSG_FOR_ROUTING,
                                       L2_LINK_DATA(fetched),
                                       (ITS_USHORT)(fetched->len -
                                        3 * sizeof(ITS_OCTET)),
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        ITS_EVENT_TERM(cocbEv);
                        ITS_Free(cocbEv);
                    }

                    TLAC_Main_CCITT(MTP3_STM_TCOC,
                                   STM_TRIGGER_CHANGEOVER_EXECUTED,
                                   NULL, 0,
                                   tls, tlc);
            
                    TSRC_Main_CCITT(MTP3_STM_TCOC,
                                   STM_TRIGGER_CHANGEOVER_EXECUTED,
                                   NULL, 0,
                                   tls, tlc);
                }
            }
            else
            {
                ln->changeoverState = CHANGEOVER_IDLE;

                LSAC_Main_CCITT(MTP3_STM_TCOC,
                               SLM_TRIGGER_STM_READY,
                               NULL, 0,
                               tls, tlc);
                
                /*
                 * NOTE: this order is backwards, but necessary.  MTP2_SendData
                 * examines the qPut variable to determine if it should queue
                 * or transmit the messages.
                 *
                 * NOTE 2: when MTP3 becomes multithreaded, we'll have to revisit
                 * this.  The second platform might transmit while we are.  This
                 * could be avoided by not committing the link info until the
                 * queue is cleared.
                 */

                /* stop buffering messages on restored link */
                /*ln->qPut = ITS_FALSE;*/
                LINK_SetLinkQPut(ln, ITS_FALSE);

                /*
                 * send buffered messages on restored link
                 *
                 * NOTE: SLS unshifting not required here, as this is
                 * recovery (link bounce).
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                    fetched = &evRec.event;

                    MTP2_SendData_CCITT(L2_LINK_SET(fetched),
                                       L2_LINK_CODE(fetched),
                                       L2_MSG_TYPE(fetched),
                                       L2_LINK_DATA(fetched),
                                       (ITS_USHORT)(fetched->len -
                                        3 * sizeof(ITS_OCTET)));

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }
                
                TLAC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               tls, tlc);
                
                TSRC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               tls, tlc);
            }
        }
        break;
                
    case STM_TRIGGER_CHANGEOVER_ORDER:          /* from TLAC */

        /* Assume that TLAC is giving correct linkSet and LinkCode */

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_NORMAL_CH_OVER);

        if (ln->changeoverState == CHANGEOVER_IDLE)
        {
            /* mark remote BSNT retrieved */

            ln->stFlags |= LINK_REMOTE_BSNT_RETRIEVED;
            
            ln->changeoverState = CHANGEOVER_WAIT_5;

            ln->stFlags |= LINK_CHANGE_OVER_RECEIVED;
            /* Retrieve and save FSNC (Remote BSN) */
            if (sif == NULL)
            {
                MTP3_DEBUG(("SIF is NULL, No COO message in trigger \
                    STM_TRIGGER_CHANGEOVER_ORDER"));


                return (~ITS_SUCCESS);
            }
            /* Retrieve and save FSNC (Remote BSN) */

            snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                                          sizeof(ITS_OCTET));
            if (ln->isSAAL)
            {
                ln->remoteBSN =
                    SNMM_CHANGEOVER_GET_FSN_SAAL(snmm_ptr->data.changeOver);
            }
            else
            {
                ln->remoteBSN =
                    SNMM_CHANGEOVER_GET_FSN(snmm_ptr->data.changeOver);
            }

            /* buffer messages for affected link */
            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_RETRIEVE_BSNT, NULL, 0);

        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK)
        {

            if (src != MTP3_STM_TCOC)
            {
                /* Retrieve and save FSNC (Remote BSN) */
                if (sif == NULL)
                {
                    MTP3_DEBUG(("SIF is NULL, No COO message in trigger \
                        STM_TRIGGER_CHANGEOVER_ORDER"));

                    return (~ITS_SUCCESS);
                }
                /* Retrieve and save FSNC (Remote BSN) */

                snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                                            sizeof(ITS_OCTET));
                if (ln->isSAAL)
                {
                    ln->remoteBSN = 
                        SNMM_CHANGEOVER_GET_FSN_SAAL(snmm_ptr->data.changeOver);
                }
                else
                {
                    ln->remoteBSN = 
                        SNMM_CHANGEOVER_GET_FSN(snmm_ptr->data.changeOver);
                }

                /* mark remote BSNT retrieved */
                ln->stFlags |= LINK_REMOTE_BSNT_RETRIEVED;

            }
            /* stop T2 */
            TIMERS_CancelSharedTimer(ln->t2);
            ln->t2 = TIMER_BAD_SERIAL;
            ln->changeoverState = CHANGEOVER_RETRIEVING;
            /* Increament the peg for ChangeOver */
            /* PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER); */
            
            if (ln->stFlags & LINK_LOCAL_BSNT_RETRIEVED)
            {

                BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_CHM,
                                                            SNMM_HC1_COA);
 
                if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                                  REMOTE_ROUTE, ROUTE_DPC_NI,
                                                  FAMILY_ITU,
                                                  ls->ni,
                                                  ls->linkSet,
                                                  ITS_SS7_DEFAULT_LINK_CODE,
                                                  ITS_SS7_DEFAULT_PRI,
                                                  ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Can't parse route info\n"));

                    MTP3_Alarm_CCITT(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                    return (ITS_EINVALIDARGS);
                }

                if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                               &firstMatch, &lastMatch,
                                               &whichLinkCode,
                                               ITS_FALSE)) == NULL)
                {
                    MTP3_ERROR(("Can't find route\n"));
 
                    return (ITS_EINVALIDARGS);
                }

                ITS_EVENT_INIT(&ev, 0, 0);
                FindAlternateRoute(dest, &omtp3,
                                   whichEntry, firstMatch, lastMatch,
                                   linkSet, linkCode,
                                   &tls, &tlc, &ev);

                ITS_EVENT_TERM(&ev);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for COA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);

                HMRT_Main_CCITT(MTP3_STM_TCOC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               tls, tlc);
                
                ITS_EVENT_TERM(&ev);
            }
            else
            {
                BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_ECM,
                                                            SNMM_HC1_ECA);

                if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                                  REMOTE_ROUTE, ROUTE_DPC_NI,
                                                  FAMILY_ITU,
                                                  ls->ni,
                                                  ls->linkSet,
                                                  ITS_SS7_DEFAULT_LINK_CODE,
                                                  ITS_SS7_DEFAULT_PRI,
                                                  ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Can't parse route info\n"));

                    MTP3_Alarm_CCITT(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                    return (ITS_EINVALIDARGS);
                }

                if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                               &firstMatch, &lastMatch,
                                               &whichLinkCode,
                                               ITS_FALSE)) == NULL)
                {
                    MTP3_ERROR(("Can't find route\n"));

                    return (ITS_EINVALIDARGS);
                }

                ITS_EVENT_INIT(&ev, 0, 0);
                FindAlternateRoute(dest, &omtp3,
                                   whichEntry, firstMatch, lastMatch,
                                   linkSet, linkCode,
                                   &tls, &tlc, &ev);

                ITS_EVENT_TERM(&ev);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for ECA Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

                HMRT_Main_CCITT(MTP3_STM_TCOC,
                               SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                               ev.data, ev.len,
                               tls, tlc);
                
                ITS_EVENT_TERM(&ev);
            }
            
            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_RETRIEVE_MSGS,
                               (ITS_OCTET *)&ln->remoteBSN, 
                               sizeof(ITS_UINT));
            
            /* mark link unavailable */
            ln->stFlags |= LINK_IS_UNAVAILABLE;
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_7)
        {
            if (sif == NULL)
            {
                MTP3_DEBUG(("SIF is NULL, No COO message in trigger \
                    STM_TRIGGER_CHANGEOVER_ORDER"));

                return (~ITS_SUCCESS);
            }
            /* Retrieve and save FSNC (Remote BSN) */

            snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                                        sizeof(ITS_OCTET));
            if (ln->isSAAL)
            {
                ln->remoteBSN = 
                    SNMM_CHANGEOVER_GET_FSN_SAAL(snmm_ptr->data.changeOver);
            }
            else
            {
                ln->remoteBSN = 
                    SNMM_CHANGEOVER_GET_FSN(snmm_ptr->data.changeOver);
            }

            /* mark FSNC available */
            ln->stFlags |= LINK_REMOTE_BSNT_RETRIEVED;
            
            /* stop T1 */
            TIMERS_CancelSharedTimer(ln->t1);
            ln->t1 = TIMER_BAD_SERIAL;
            
            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_RETRIEVE_BSNT, NULL, 0); 
            
            ln->changeoverState = CHANGEOVER_WAIT_8;
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_2)
        {
            /* SDL save construct: we save the information and 
             * set the flag.
             */ 
            ln->stFlags |= LINK_CHANGE_OVER_RECEIVED;
            /* Retrieve and save FSNC (Remote BSN) */
            if (sif == NULL)
            {
                MTP3_DEBUG(("SIF is NULL, No COO message in trigger \
                    STM_TRIGGER_CHANGEOVER_ORDER"));

                return (~ITS_SUCCESS);
            }
            /* Retrieve and save FSNC (Remote BSN) */

            snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                                          sizeof(ITS_OCTET));
            if (ln->isSAAL)
            {
                ln->remoteBSN =
                    SNMM_CHANGEOVER_GET_FSN_SAAL(snmm_ptr->data.changeOver);
            }
            else
            {
                ln->remoteBSN =
                    SNMM_CHANGEOVER_GET_FSN(snmm_ptr->data.changeOver);
            }

            /* mark remote BSNT retrieved */
            ln->stFlags |= LINK_REMOTE_BSNT_RETRIEVED;



        }
        break;
            
    case STM_TRIGGER_BSNT:                      /* from L2 */

        /* Retrieve Local BSNT from the message */
        ln->localBSN = (sif[1] << 24) | (sif[2] << 16) | (sif[3] << 8) | sif[4];

        MTP3_DEBUG(("**** STM_TRIGGER_BSNT: bsnt=%d ****\n", ln->localBSN));

        if (ln->changeoverState == CHANGEOVER_WAIT_2)
        {
            /* mark local BSNT received */
            ln->stFlags |= LINK_LOCAL_BSNT_RETRIEVED;
            ln->changeoverState = CHANGEOVER_WAIT_FOR_ACK;
            
            /* Build SNMM CHANGEOVER ORDER message */
            BuildChangeOverMsg(&omtp3, &snmm, ls, ln,
                               SNMM_HC0_CHM, SNMM_HC1_COO);

            MTP3_Alarm_CCITT(2513, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x and bsnt %d", 
                             linkSet,linkCode,ln->localBSN);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ITU,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));
 
                MTP3_Alarm_CCITT(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for COO Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_TX);

            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);
            
            /* start T2 */
            tc.timerId = MTP3_T2;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t2 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                        __ccitt_t2 * USEC_PER_MILLISEC,
                                        &tc, sizeof(MTP3_TimerContext));

            /* This flag is set if the COO is recieved while in
             * state CHANGEOVER_WAIT_2. But the COO is processed
             * in CHANGEOVER_WAIT_FOR_ACK state. Therefore TCOC
             * re-generate the COO event after the local BSN is processed
             */
            if (ln->stFlags & LINK_CHANGE_OVER_RECEIVED) 
            {
                /* cancel LINK_CHANGE_OVER_RECEIVED */
                ln->stFlags &= (~LINK_CHANGE_OVER_RECEIVED);

                if (ln->stFlags & LINK_REMOTE_BSNT_RETRIEVED)
                {
                    TCOC_Main_CCITT(MTP3_STM_TCOC,    
                                    STM_TRIGGER_CHANGEOVER_ORDER,
                                    NULL, 0,
                                    linkSet, linkCode);
                }
                else
                {
                    TCOC_Main_CCITT(MTP3_STM_TCOC,
                                    STM_TRIGGER_EMERG_CHANGEOVER_ORDER,
                                    NULL, 0,
                                    linkSet, linkCode);
                }
            }
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_5)
        {
            ln->changeoverState = CHANGEOVER_WAIT_6;

            BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_CHM,
                                                        SNMM_HC1_COA);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ITU,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_CCITT(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for COA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);

            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);

            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
       
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);
            

            TSRC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           ev.data, ev.len, /* Tmp RL */
                           linkSet, linkCode);
            
            ITS_EVENT_TERM(&ev);
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_8)
        {
            BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_CHM, 
                                                        SNMM_HC1_COA);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ITU,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_CCITT(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for COA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);

            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);
            
            if (ln->stFlags & LINK_REMOTE_BSNT_RETRIEVED) /* FSNCAvailable */
            {
                /* Neet to send FSNC to L2 to retrieve buffers */

                MTP2_SendData_CCITT(linkSet, linkCode,
                                   L3_L2_RETRIEVE_MSGS,
                                   (ITS_OCTET *)&ln->remoteBSN, 
                                   sizeof(ITS_UINT));
            
                /* mark link unavailable */
                ln->stFlags = LINK_IS_UNAVAILABLE;
            
                ln->changeoverState = CHANGEOVER_RETRIEVING;
            }
            else
            {
                /*
                 * do this first to avoid circular transmission.
                 */
                HMRT_Main_CCITT(MTP3_STM_TCOC,
                               SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                               NULL, 0,
                               linkSet, linkCode);
            
                /*
                 * send buffered messages on alternative links
                 *
                 * SLS unshifting *is* required here.  It's not terribly
                 * awful, though.
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                    fetched = &evRec.event;

                    /* if this fails we're toast. */
                    ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                    ITS_C_ASSERT(ls != NULL);

                    slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                    sls = MTP3_RL_GET_SLS(slsUnshift->label);

                    /*
                     * NOTE: ITU doesn't need to undo bit rotation.
                     */
                    /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                    /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                    HMRT_Main_CCITT(MTP3_SMH_HMDT,
                                   SMH_TRIGGER_MSG_FOR_ROUTING,
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)),
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }

                ln->changeoverState = CHANGEOVER_IDLE;
            
                TLAC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            
                TSRC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            
            }
        }
        break;
        
    case STM_TRIGGER_BSNT_NOT_RETRIEVABLE:      /* from L2 */
        if (ln->changeoverState == CHANGEOVER_WAIT_2)
        {
            /* cancel local BSNT retrieved */
            ln->stFlags &= (~LINK_LOCAL_BSNT_RETRIEVED);
            ln->changeoverState = CHANGEOVER_WAIT_FOR_ACK;
            
            BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_ECM,
                                                        SNMM_HC1_ECO);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ITU,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_CCITT(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for ECO Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_TX);

            MTP3_Alarm_CCITT(2515, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x",
                             tls,tlc);

            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);
            
            /* start T2 */
            tc.timerId = MTP3_T2;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t2 = TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                        __ccitt_t2 * USEC_PER_MILLISEC,
                                        &tc, sizeof(MTP3_TimerContext));

        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_5)
        {
            ln->changeoverState = CHANGEOVER_WAIT_6;

            BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_ECM,
                                                        SNMM_HC1_ECA);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ITU,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_CCITT(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for ECA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);

            ITS_EVENT_TERM(&ev);

            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            TSRC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           ev.data, ev.len, /* Tmp RL */
                           linkSet, linkCode);

            ITS_EVENT_TERM(&ev);
        }
        else if (ln->changeoverState == CHANGEOVER_WAIT_8)
        {
            BuildChangeOverMsg(&omtp3, &snmm, ls, ln, SNMM_HC0_ECM,
                                                        SNMM_HC1_ECA);

            if (ROUTE_ParseRouteMatchInfoArgs(&mi, ls->adjacent,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ITU,
                                              ls->ni,
                                              ls->linkSet,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't parse route info\n"));

                MTP3_Alarm_CCITT(2482, __FILE__, __LINE__, "The destination is  %08x",ls->adjacent);

                return (ITS_EINVALIDARGS);
            }

            if ((dest = ROUTE_FindBestMatch(&mi, &whichEntry,
                                           &firstMatch, &lastMatch,
                                           &whichLinkCode,
                                           ITS_FALSE)) == NULL)
            {
                MTP3_ERROR(("Can't find route\n"));

                return (ITS_EINVALIDARGS);
            }

            ITS_EVENT_INIT(&ev, 0, 0);
            FindAlternateRoute(dest, &omtp3,
                               whichEntry, firstMatch, lastMatch,
                               linkSet, linkCode,
                               &tls, &tlc, &ev);

            ITS_EVENT_TERM(&ev);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for ECA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);

            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);
            
            if (ln->stFlags & LINK_REMOTE_BSNT_RETRIEVED) /* FSNCAvailable */
            {
                MTP2_SendData_CCITT(linkSet, linkCode,
                                   L3_L2_RETRIEVE_MSGS, 
                                   (ITS_OCTET *)&ln->remoteBSN,
                                   sizeof(ITS_UINT));

            
                /* mark link unavailable */
                ln->stFlags |= LINK_IS_UNAVAILABLE;
            
                ln->changeoverState = CHANGEOVER_RETRIEVING;
            }
            else
            {
                /*
                 * do this first to avoid circular transmission.
                 */
                HMRT_Main_CCITT(MTP3_STM_TCOC,
                               SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                               NULL, 0,
                               linkSet, linkCode);
            
                /*
                 * send buffered messages on alternative links
                 *
                 * SLS unshifting *is* required here.  It's not terribly
                 * awful, though.
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                    fetched = &evRec.event;

                    /* if this fails we're toast. */
                    ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                    ITS_C_ASSERT(ls != NULL);

                    slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                    sls = MTP3_RL_GET_SLS(slsUnshift->label);

                    /*
                     * NOTE: ITU doesn't need to undo bit rotation.
                     */
                    /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                    /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                    HMRT_Main_CCITT(MTP3_SMH_HMDT,
                                   SMH_TRIGGER_MSG_FOR_ROUTING,
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)),
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }

                ln->changeoverState = CHANGEOVER_IDLE;
            
                TLAC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            
                TSRC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            
            }
        }
        break;
        
    case STM_TRIGGER_T1:                        /* from timer control */
        if (ln->changeoverState == CHANGEOVER_WAIT_7)
        {
            /*
             * do this first to avoid circular transmission.
             */
            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            /*
             * send buffered messages on alternative links
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                ITS_C_ASSERT(ls != NULL);

                slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                /*
                 * NOTE: ITU doesn't need to undo bit rotation.
                 */
                /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                HMRT_Main_CCITT(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            ln->changeoverState = CHANGEOVER_IDLE;

            TLAC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
            /* TSRC wants destination information */

            MTP3_HDR_SET_SIO(omtp3, ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            TSRC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           ev.data, ev.len,
                           linkSet, linkCode);
            
            ITS_EVENT_TERM(&ev);
        }
        break;
        
    case STM_TRIGGER_CHANGEOVER_ACK:            /* from HMDT */

        /* Get correct Linkset and Link using opc dpc and slc in SNMM */
        if (sif == NULL)
        {
            MTP3_DEBUG(("SIF is NULL, No COA message in trigger \
                STM_TRIGGER_CHANGEOVER_ACK"));

            return (~ITS_SUCCESS);
        }

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                                    sizeof(ITS_OCTET));

        /* Linkset */
        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            return (ITS_EINVALIDARGS);
        }

        /* Link */
        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for COA Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_RX);

        if (ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK)
        {
            /* stop T2 */
            TIMERS_CancelSharedTimer(ln->t2);
            ln->t2 = TIMER_BAD_SERIAL;

            /* Increament the peg for ChangeOver */
            /* PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER); */
            
            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_RETRIEVE_MSGS, 
                               (ITS_OCTET *)&ln->remoteBSN,
                               sizeof(ITS_UINT));
            
            /* mark link unavailable */
            ln->stFlags |= LINK_IS_UNAVAILABLE;
            
            ln->changeoverState = CHANGEOVER_RETRIEVING;
        }
        break;
        
    case STM_TRIGGER_EMERG_CHANGEOVER_ACK:      /* from HMDT */

        /* Get correct Linkset and Link using opc dpc and slc in SNMM */
        if (sif == NULL)
        {
            MTP3_DEBUG(("SIF is NULL, No ECA message in trigger \
                STM_TRIGGER_EMERG_CHANGEOVER_ACK"));

            return (~ITS_SUCCESS);
        }

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        snmm_ptr = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) + 
                                                    sizeof(ITS_OCTET));

        /* Linkset */
        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            return (ITS_EINVALIDARGS);
        }

        /* Link */
        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for ECA Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_RX);

        if (ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK)
        {
            /* stop T2 */
            TIMERS_CancelSharedTimer(ln->t2);
            ln->t2 = TIMER_BAD_SERIAL;
            ln->changeoverState = CHANGEOVER_IDLE;

            /* Increament the peg for ChangeOver */
            /* PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER); */

            LSAC_Main_CCITT(MTP3_STM_TCOC,
                           SLM_TRIGGER_STM_READY,
                           NULL, 0,
                           linkSet, linkCode);

            /*
             * do this first to avoid circular transmission.
             */
            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            /*
             * send buffered messages on alternative links
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                ITS_C_ASSERT(ls != NULL);

                slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                /*
                 * NOTE: ITU doesn't need to undo bit rotation.
                 */
                /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                HMRT_Main_CCITT(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }
            
            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            TLAC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
            TSRC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;
        
    case STM_TRIGGER_RETRIEVED_MSGS:            /* from L2 */
        if (ln->changeoverState == CHANGEOVER_RETRIEVING)
        {

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, len + 3 * sizeof(ITS_OCTET) );

            L2_MSG_TYPE(&ev) = L3_L2_DATA;
            L2_LINK_SET(&ev) = linkSet;
            L2_LINK_CODE(&ev) = linkCode;


            if (len)
            {
                memcpy(L2_LINK_DATA(&ev), sif, len);
            }

            /* save retrieved messages */
            return DSMQUEUE_Enqueue(ln->rtrvBuf, ev);
        }
        break;
        
    case STM_TRIGGER_RETRIEVAL_COMPLETE:        /* from L2 */
        if (ln->changeoverState == CHANGEOVER_RETRIEVING)
        {
            if (ln->stFlags & LINK_IS_UNAVAILABLE) /* LinkUnavailable */
            {
                /* send retrieved messages on alternate link */
                while (DSMQUEUE_Dequeue(ln->rtrvBuf, &fetched) == ITS_SUCCESS)
                {

                    /* if this fails we're toast. */
                    ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                    ITS_C_ASSERT(ls != NULL);

                    slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                    sls = MTP3_RL_GET_SLS(slsUnshift->label);

                    /*
                     * NOTE: ITU doesn't need to undo bit rotation.
                     */
                    /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                    /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                    HMRT_Main_CCITT(MTP3_SMH_HMDT,
                                   SMH_TRIGGER_MSG_FOR_ROUTING,
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)),
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_Free(fetched);
                }

                ln->changeoverState = CHANGEOVER_IDLE;
                
                LSAC_Main_CCITT(MTP3_STM_TCOC,
                               SLM_TRIGGER_STM_READY,
                               NULL, 0,
                               linkSet, linkCode);

                /*
                 * do this first to avoid circular transmission.
                 */
                HMRT_Main_CCITT(MTP3_STM_TCOC,
                               SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                               NULL, 0,
                               linkSet, linkCode);
            
                /*
                 * send buffered messages on alternative links
                 *
                 * SLS unshifting *is* required here.  It's not terribly
                 * awful, though.
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                    fetched = &evRec.event;

                    /* if this fails we're toast. */
                    ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                    ITS_C_ASSERT(ls != NULL);

                    slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                    sls = MTP3_RL_GET_SLS(slsUnshift->label);

                    /*
                     * NOTE: ITU doesn't need to undo bit rotation.
                     */
                    /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                    /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                    HMRT_Main_CCITT(MTP3_SMH_HMDT,
                                   SMH_TRIGGER_MSG_FOR_ROUTING,
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)),
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }
            
                TLAC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            
                TSRC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_EXECUTED,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                /* these tasks should be carried out in the order shown */
                /* send retrieved messages on restored link */
                while (DSMQUEUE_Dequeue(ln->rtrvBuf, &fetched) == ITS_SUCCESS)
                {
                    /* if this fails we're toast. */
                    ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                    ITS_C_ASSERT(ls != NULL);

                    slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                    sls = MTP3_RL_GET_SLS(slsUnshift->label);

                    /*
                     * NOTE: ITU doesn't need to undo bit rotation.
                     */
                    /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                    /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                    HMRT_Main_CCITT(MTP3_SMH_HMDT,
                                   SMH_TRIGGER_MSG_FOR_ROUTING,
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)),
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_Free(fetched);
                }

                /*
                 * NOTE: this order is backwards, but necessary.  MTP2_SendData
                 * examines the qPut variable to determine if it should queue
                 * or transmit the messages.
                 *
                 * NOTE 2: when MTP3 becomes multithreaded, we'll have to revisit
                 * this.  The second platform might transmit while we are.  This
                 * could be avoided by not committing the link info until the
                 * queue is cleared.
                 */

                /* stop buffering messages on restored link */
                /*ln->qPut = ITS_FALSE;*/
                LINK_SetLinkQPut(ln, ITS_FALSE); 

                /*
                 * send buffered messages on restored link
                 *
                 * NOTE: SLS unshifting not required here, as this is
                 * recovery (link bounce).
                 */
                while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
                {
                    evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                    fetched = &evRec.event;

                    MTP2_SendData_CCITT(L2_LINK_SET(fetched),
                                       L2_LINK_CODE(fetched),
                                       L2_MSG_TYPE(fetched),
                                       L2_LINK_DATA(fetched),
                                       (ITS_USHORT)(fetched->len -
                                        3 * sizeof(ITS_OCTET)));

                    ITS_EVENT_TERM(cocbEv);
                    ITS_Free(cocbEv);
                }
                
                ln->changeoverState = CHANGEOVER_IDLE;

                TLAC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               linkSet, linkCode);
                
                TSRC_Main_CCITT(MTP3_STM_TCOC,
                               STM_TRIGGER_CHANGEOVER_NOT_REQD,
                               NULL, 0,
                               linkSet, linkCode);
                
            }
        }
        break;
        
    case STM_TRIGGER_RETRIEVAL_NOT_POSSIBLE:    /* from L2 */
        if (ln->changeoverState == CHANGEOVER_RETRIEVING)
        {
            ln->changeoverState = CHANGEOVER_IDLE;

            LSAC_Main_CCITT(MTP3_STM_TCOC,
                           SLM_TRIGGER_STM_READY,
                           NULL, 0,
                           linkSet, linkCode);

            /*
             * do this first to avoid circular transmission.
             */
            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            /*
             * send buffered messages on alternative links
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                ITS_C_ASSERT(ls != NULL);

                slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                /*
                 * NOTE: ITU doesn't need to undo bit rotation.
                 */
                /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                HMRT_Main_CCITT(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }
            
            TLAC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
            TSRC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;
        
    case STM_TRIGGER_T2:                        /* from timer control */
        if (ln->changeoverState == CHANGEOVER_WAIT_FOR_ACK)
        {
            ln->changeoverState = CHANGEOVER_IDLE;

            LSAC_Main_CCITT(MTP3_STM_TCOC,
                           SLM_TRIGGER_STM_READY,
                           NULL, 0,
                           linkSet, linkCode);

            /*
             * have to do this first, otherwise we send to ourselves.
             */
            HMRT_Main_CCITT(MTP3_STM_TCOC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);
            
            /*
             * send buffered messages on alternative links
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));

                ITS_C_ASSERT(ls != NULL);

                slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                /*
                 * NOTE: ITU doesn't need to undo bit rotation.
                 */
                /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                HMRT_Main_CCITT(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }
            
            TLAC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
            
            TSRC_Main_CCITT(MTP3_STM_TCOC,
                           STM_TRIGGER_CHANGEOVER_EXECUTED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
}

/*
 * sequence number wrapping.
 */
#define MAX_SEQNO   0xFFFFFFFFU
#define IS_SEQNO_WRAPPED(a, b)                      \
    ((((a) > (b)) && (((a) - (b)) < ((MAX_SEQNO) >> 1))) || \
     (((b) > (a)) && (((b) - (a)) > ((MAX_SEQNO) >> 1))))

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
static int          
InsertEvent(QUEUE_Entry *prev, QUEUE_Entry *next, QUEUE_Entry *item)
{ 
    MTP3_EventRec here, there, before;
                
    /* emtpy list? */
    if (prev == NULL && next == NULL)
    {        
        return (ITS_TRUE); 
    }
                     
    /*
     * less than head?
     */
    if (prev == NULL)
    {
        here  = ItsEventToMTP3EventRec_CCITT(item->data);
        there = ItsEventToMTP3EventRec_CCITT(next->data);
        /*
         * sequence number can wrap, so be careful
         */
        if (IS_SEQNO_WRAPPED(here.seqNo, there.seqNo))
        {
            /*
             * it wrapped, so even though here->seqNo < there->seqNo,
             * we have to consider it as greater.
             */
            return (ITS_FALSE);
        }
        else if (here.seqNo < there.seqNo)
        {
            return (ITS_TRUE);
        }

        /* default is it's greater */
        return (ITS_FALSE);
    }
    /*
     * at end of list?  Always insert
     */
    if (next == NULL)
    {
        return (ITS_TRUE);
    }

    /*
     * hard case.  Middle of list.
     */
    here = ItsEventToMTP3EventRec_CCITT(item->data);
    there = ItsEventToMTP3EventRec_CCITT(next->data);
    before = ItsEventToMTP3EventRec_CCITT(prev->data);

    /*
     * we still have to check wrappage.
     */
    if (IS_SEQNO_WRAPPED(here.seqNo, there.seqNo))
    {
        /* insert after */
        return (ITS_FALSE);
    }

    /*
     * weird case.  This may fall into a gap between
     * UINT_MAX and low numbers.  We know that next is ok in this case,
     * or we would have tripped the condition above.
     */
    if (IS_SEQNO_WRAPPED(here.seqNo, before.seqNo))
    {
        /*
         * now, or later
         */
        if (here.seqNo < there.seqNo)
        {
            return (ITS_TRUE);
        }

        /* no, keep going. */
        return (ITS_FALSE);
    }

    /* normal case.  Range check. */
    if (here.seqNo > before.seqNo && here.seqNo < there.seqNo)
    {
        return (ITS_TRUE);
    }

    /* give up */
    return (ITS_FALSE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert a DSMQUEUE_Entry to a MTP3_EventRec
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
static MTP3_EventRec
DsmQueueEntryToMTP3EventRec_CCITT(DSMQUEUE_Entry entry)
{
    MTP3_EventRec evRec;

    ITS_UINT seqNoSize = sizeof(evRec.seqNo);

    ITS_EVENT_INIT(&evRec.event, entry.src, entry.len - seqNoSize);

    memcpy(&evRec.seqNo, entry.data, seqNoSize);
    memcpy(evRec.event.data, &entry.data[seqNoSize], entry.len - seqNoSize);

    return evRec;

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
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for 64 link support 
 *                     ID::D0020                   and load balancing 
 ****************************************************************************/
static void
MoveTraffic(SS7_LinkSetPtr ls, ITS_OCTET linkCode)
{
    ITS_UINT i, idx;
    SS7_LinkPtr ln, nln;
    DSMQUEUE_Entry *ent;
    MTP3_EventRec evRec;
    MTP3_HEADER *mtp3;
    ITS_OCTET linkSel, sls;

    /*
     * find the link index
     */
    nln = NULL;
    for (idx = 0; idx < ls->numLinks; idx++)
    {
        if (ls->links[idx]->linkCode == linkCode)
        {
            nln = ls->links[idx];
            break;
        }
    }

    /*
     * if the link isn't found, ditch
     */
    if (idx == ls->numLinks || nln == NULL)
    {
        return;
    }

    /*
     * for each link
     */
    for (i = 0; i < ls->numLinks; i++)
    {
        ln = ls->links[i];

        /*
         * if the linkCode is not self
         */
        if (ls->links[i]->linkCode != linkCode)
        {
            ITS_UINT i;
            ITS_UINT msgCount = ln->cocbBuf->numEntries;
            /*
             * for each message in the buffer
             */
            for (i = 0, ent = &ln->cocbBuf->entries[ln->cocbBuf->firstEntry];
                 ent != NULL && i < msgCount ;
                 i++)
            {
                evRec = DsmQueueEntryToMTP3EventRec_CCITT(*ent);

                mtp3 = (MTP3_HEADER *)(L2_LINK_DATA(&evRec.event) +
                                            sizeof(ITS_OCTET));
                sls = MTP3_RL_GET_SLS(mtp3->label) & MTP3_NIC_MASK;

                /* FIXME: MLM: SHOULD WE BE DOING BIT ROTATION HERE?  THIS IS ITU */
                /*
                 * unrotate it to retrieve original value
                 */
                sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls);

                /*
                 * rotate again to find index.  Key point; we don't have
                 * to change the SLS value in the message, it is already
                 * right.  We had to do this unrotate/rotate to find the
                 * link offset.
                 */

                /* commenting the  ROUTE_SLSRotate API , because we are not 
                 * having required parameters SS7_Destination, numlinkSet,
                 * firstMatch. We will use sls MOD (number of links) to get 
                 * the link offset.
                 */

                /* ROUTE_SLSRotate(!ls->is5Bit, sls, &dummy, &linkSel); */

                linkSel = sls % ls->numLinks;

                /*
                 * if the codeMap has this sls belonging to the changing
                 * back link
                 */
                if (ls->codeMap[linkSel] == idx)
                {
                    /*
                     * move it to the new link
                     */
                    DSMQUEUE_Unlink(ln->cocbBuf, ent);
                    DSMQUEUE_Insert(nln->cocbBuf, InsertEvent,
                                MTP3EventRecToItsEvent_CCITT(evRec) );

                    ITS_EVENT_TERM(&evRec.event);

                }
                else
                {
                    /*
                     * let's compare with the next entry
                     */
                     ent = (ent == &ln->cocbBuf->entries[ln->cocbBuf->key.maxQueueSize-1]) ?
                     ln->cocbBuf->entries                                         :
                     ent + 1; 
                }
            }
        }
    }
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
 ****************************************************************************/
int
TCBC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{    
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    MTP3_TimerContext tc;
    ITS_UINT pc1;
    ITS_OCTET ni;
    MTP3_HEADER omtp3;
    SNMM_MESSAGE snmm;
    SNMM_MESSAGE* isnmm;
    ITS_EVENT ev, *fetched, *cocbEv;
    MTP3_EventRec evRec;
    SS7_LinkPtr ln;
    SS7_LinkSetPtr ls;
    ITS_OCTET changeBackCode, tls, tlc;

    MTP3_TRACE_ENTRY_CCITT(MTP3_STM_TCBC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* wants a link, I think */
    switch (trigger)
    {
    case STM_TRIGGER_LINK_AVAILABLE:            /* from TLAC */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changebackState == CHANGEBACK_IDLE)
        {
            MTP3_HDR_SET_SIO(omtp3, ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);
                        
            ln->changebackState = CHANGEBACK_WAIT_FOR_DATA;
            
            TSRC_Main_CCITT(MTP3_STM_TCBC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           ev.data, ev.len,
                           linkSet, linkCode);
            
            ITS_EVENT_TERM(&ev);
        }
        break;

    case STM_TRIGGER_CHANGEBACK_DECL:           /* from HMDT */
        tls = linkSet;
        tlc = linkCode;

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        isnmm = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        MTP3_Alarm_CCITT(2511, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet,linkCode);

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for CBD Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_RX);

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK);
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_CHANGE_BACK);

        if (ln->changebackState == CHANGEBACK_IDLE ||
            ln->changebackState == CHANGEBACK_TIME_CONTROLLED_DIVERT ||
            ln->changebackState == CHANGEBACK_FIRST_ATTEMPT ||
            ln->changebackState == CHANGEBACK_SECOND_ATTEMPT)
        {
            /* Extract the CB Code */
            ITS_C_ASSERT(sif != NULL);
            isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                         sizeof(ITS_OCTET)];
            changeBackCode = SNMM_CHANGEBACK_GET_CODE(isnmm->data.changeBack);

            /* Build SNMM changeback ACK */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

            SNMM_HC0_SET(snmm, SNMM_HC0_CHM);
            SNMM_HC1_SET(snmm, SNMM_HC1_CBA);

            SNMM_CHANGEBACK_SET_CODE(snmm.data.changeBack, changeBackCode);
            
            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);

            /* Increament Link Peg for CBA Transmitted */
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_TX);

            HMRT_Main_CCITT(MTP3_STM_TCBC,
                           SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                           ev.data, ev.len,
                           tls, tlc);
        }
        break;

    case STM_TRIGGER_CHANGEBACK_ACK:            /* from HMDT */
        tls = linkSet;
        tlc = linkCode;

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        isnmm = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER) +
                                            sizeof(ITS_OCTET));

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);

        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent linkSet\n"));

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);
        changeBackCode = SNMM_CHANGEBACK_GET_CODE(isnmm->data.changeBack);

        /* this is invariant in our stack */
        tlc = changeBackCode;

        /* Linkset Pointer */
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /* Link Pointer */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for CBA Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_RX);

        ln->gotCBA |= (1 << tlc);

        if (ln->changebackState == CHANGEBACK_FIRST_ATTEMPT /*&&
            ln->gotCBA == ln->needCBA*/)
        {
            /* stop T4 */
            TIMERS_CancelSharedTimer(ln->t4);
            ln->t4 = TIMER_BAD_SERIAL;

            /* Increament the peg for ChangeBack */
            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK);

            /* reset masks */
            ln->gotCBA = ln->needCBA = 0;

            /*
             * I love this paragraph: 4.3.2:
             *
             * "In the case that multiple links in the link set are unavailable,
             * traffic in addition to that for which the newly available link
             * is the normal one may be transferred to the newly available link
             * in order to distribute traffic among available links as evenly
             * as possible. If this option is implemented, implementation-
             * dependent safeguards must be employed to prevent missequencing
             * or excessive delay of messages when additional links within the
             * link set become available while changeback is still in progress."
             *
             * I had to go and get ambitious.
             *
             * This requires deep thought.  Consider this case:
             * 1. Changeback is in progress, we buffer messages for this link
             * based on SLS map recomputation.
             * 2. Another link becomes available.  Recompute the SLS map again.
             * 3. The second link gets the CBA before the first link.
             *
             * Now, consider.  *Unless* the SLS map computation is such that
             * _no_ SLS value transferred to the second link was previously
             * transferred to the first link, the possibility for missequencing
             * exists.
             *
             * This means that the algorithm (as earlier thought) MUST NOT move
             * SLS values for changing back links until the changeback occurs.
             *
             ****************************************************************
             *
             * Here's an approach:
             *
             * 1. When a link starts changeback, balance the SLS map with
             * this link included.
             * 2. If another link starts changeback before the procedure
             * finishes, rebalance the map.
             * 3. In case 2, if any SLS code represented the link referred
             * to in 1, walk the CB buffer for that link, looking for matching
             * SLS values.  If found, move the message to (2).
             * 4. Since we'll be moving messages from possibly multiple sources,
             * we'll need a global sequence number (can you say TSN).  When
             * performing 3, the CB buffer will need sorting by this sequence
             * number.
             * 5. If changeover completes while any of this is in progress,
             * we'll have to distribute the SLS values of the failed link
             * among all links, even if they are changing back.
             *
             ****************************************************************
             *
             * restart traffic on link buffered messages first
             *
             * ROTATION COMMENT
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_CCITT(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            HMRT_Main_CCITT(MTP3_STM_TCBC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);

            TLAC_Main_CCITT(MTP3_STM_TCBC,
                           STM_TRIGGER_CHANGEBACK_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            TSRC_Main_CCITT(MTP3_STM_TCBC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->changebackState = CHANGEBACK_IDLE;
        }
        else if (ln->changebackState == CHANGEBACK_SECOND_ATTEMPT /*&&
                 ln->gotCBA == ln->needCBA*/)
        {
            /* stop T5 */
            TIMERS_CancelSharedTimer(ln->t5);
            ln->t5 = TIMER_BAD_SERIAL;

            /* Increament the peg for ChangeBack */
            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK);

            /* reset masks */
            ln->needCBA = ln->gotCBA = 0;

            /*
             * restart traffic on link buffered messages first
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_CCITT(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            HMRT_Main_CCITT(MTP3_STM_TCBC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);

            TLAC_Main_CCITT(MTP3_STM_TCBC,
                           STM_TRIGGER_CHANGEBACK_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            TSRC_Main_CCITT(MTP3_STM_TCBC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->changebackState = CHANGEBACK_IDLE;
        }
        break;

    case STM_TRIGGER_ALTERNATE_ROUTE_DATA:      /* from TSRC */
        tls = sif[2 * sizeof(MTP3_HEADER) + sizeof(ITS_OCTET)];
        tlc = sif[2 * sizeof(MTP3_HEADER) + 2 * sizeof(ITS_OCTET)];

        ln = LINK_FindLink(tls, tlc);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", tls, tlc));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(tls);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", tls));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changebackState == CHANGEBACK_WAIT_FOR_DATA)
        {
            if (!RoutingChanged(sif, len, linkSet, linkCode))
            {
                MTP3_DEBUG(("TCBC_Main: Routing didn't change for %d %d: %d %d\n",
                            tls, tlc, linkSet, linkCode));

                ln->changebackState = CHANGEBACK_IDLE;

                TLAC_Main_CCITT(MTP3_STM_TCBC,
                               STM_TRIGGER_CHANGEBACK_TERMINATED,
                               NULL, 0,
                               tls, tlc);

                TSRC_Main_CCITT(MTP3_STM_TCBC,
                               STM_TRIGGER_PROCEDURE_TERMINATED,
                               sif, len,
                               tls, tlc);
            }
            else
            {
                MTP3_DEBUG(("TCBC_Main: Routing did change for %d %d: %d %d\n",
                            tls, tlc, linkSet, linkCode));

                /* buffer concerned messages in changeback buffer */
                /* reset the SLS map */
                LINKSET_AddActiveLink(ls, ln->linkCode);

                /* move traffic from other CO/CB buffers to this link */
                MoveTraffic(ls, ln->linkCode);

                /* NOTE this tells SMH to queue instead of transmit */
                /*ln->qPut = ITS_TRUE;*/
                LINK_SetLinkQPut(ln, ITS_TRUE);

                pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

                if (/*RemoteSPAccessible(pc1, ni)*/linkSet == tls)
                {
                    int nextras = (int)len -
                                  (int)(2 * sizeof(MTP3_HEADER) +
                                        3 * sizeof(ITS_OCTET));
                    ITS_OCTET *extras = &sif[2 * sizeof(MTP3_HEADER) +
                                             3 * sizeof(ITS_OCTET)];
                    int i;
                    SS7_LinkPtr tln;

                    MTP3_DEBUG(("TCBC_Main: RemoteSPAccessible for %d %d\n", tls, tlc));

                    ITS_C_ASSERT(nextras >= 0);

                    /* Build SNMM changeback for each available link */
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                    SNMM_HC0_SET(snmm, SNMM_HC0_CHM);
                    SNMM_HC1_SET(snmm, SNMM_HC1_CBD);

                    /*
                     * we did an alternate route request, but we're the only
                     * link available.
                     * FIXME: What if the link drops then immediately comes
                     * back.  This should go into time-controlled but doesn't.
                     * Think about how this really happens.
                     * This seems to be when there is no alternate link.
                     */
                    if (linkSet == ITS_SS7_DEFAULT_LINK_SET &&
                        linkCode == ITS_SS7_DEFAULT_LINK_CODE)
                    {
                        return (ITS_SUCCESS);
                    }

                    /*
                     * In this case, the SP MUST be accessible, so linkSet/linkCode
                     * MUST be valid
                     */
                    tln = LINK_FindLink(linkSet, linkCode);
                    if ( tln == NULL)
                    {

                       ITS_C_ASSERT(tln != NULL);
                    }

                    /*
                     * Massive simplification.  The changeback code is
                     * simply the link this message should be sent on.  Ehm.  Right?
                     */
                    MTP3_RL_SET_SLS(mtp3->label, ln->linkCode);
                    SNMM_CHANGEBACK_SET_CODE(snmm.data.changeBack, linkCode);

                    /* update management info */
                    ln->needCBA |= 1 << linkCode;
                    ln->cbLinkSet = linkSet;

                    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                    SNMM_Encode(&ev, &omtp3, &snmm);

#if 1
/* To fix the problem reported for not sending second CBD if first
   CBD is not acknowledged.
*/

                    /* Increament Link Peg for CBD Transmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);

                    MTP3_Alarm_CCITT(2514, __FILE__, __LINE__,
                                    "linkset:linkcode %x:%x",linkSet,ln->linkCode);

                    HMRT_Main_CCITT(MTP3_STM_TCBC,
                                   SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                   ev.data, ev.len,
                                   linkSet, linkCode);
#endif

                    ITS_EVENT_TERM(&ev);

                    /*
                     * send messages on other links
                     */
                    for (i = 0; i < nextras; i++)
                    {
                        /* Build SNMM changeback for each available link */
                        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                        MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                        SNMM_HC0_SET(snmm, SNMM_HC0_CHM);
                        SNMM_HC1_SET(snmm, SNMM_HC1_CBD);

                        /*
                         * In this case, the SP MUST be accessible, so linkSet/linkCode
                         * MUST be valid
                         */
                        tln = LINK_FindLink(linkSet, extras[i]);
                    if ( tln == NULL)
                    {

                        ITS_C_ASSERT(tln != NULL);
                    }

                        SNMM_CHANGEBACK_SET_CODE(snmm.data.changeBack, extras[i]);

                        /* update management info */
                        ln->needCBA |= 1 << extras[i];

                        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                        SNMM_Encode(&ev, &omtp3, &snmm);

                        /* Increament Link Peg for CBD Transmitted */
                        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);

                        MTP3_Alarm_CCITT(2514, __FILE__, __LINE__,
                                         "linkset:linkcode %x:%x",
                                          linkSet,ln->linkCode);

                        HMRT_Main_CCITT(MTP3_STM_TCBC,
                                       SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                       ev.data, ev.len,
                                       linkSet, extras[i]);

                        ITS_EVENT_TERM(&ev);
                    }

                    /* start T4 */
                    tc.timerId = MTP3_T4;
                    tc.data.linkInfo.linkSet = tls;
                    tc.data.linkInfo.linkCode = tlc;

                    ln->t4 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                           __ccitt_t4 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    ln->changebackState = CHANGEBACK_FIRST_ATTEMPT;
                }
                else
                {
                    MTP3_DEBUG(("TCBC_Main: RemoteSPNotAccessible for %d %d\n", tls, tlc));

                    /* start T3 */
                    tc.timerId = MTP3_T3;
                    tc.data.linkInfo.linkSet = tls;
                    tc.data.linkInfo.linkCode = tlc;

                    ln->t3 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                           __ccitt_t3 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    ln->changebackState = CHANGEBACK_TIME_CONTROLLED_DIVERT;
                }
            }
        }
        else
        {
            MTP3_DEBUG(("TCBC_Main: Bad state for %d %d\n",
                        tls, tlc));

            MTP3_Alarm_CCITT(2487, __FILE__, __LINE__, 
                             "Bad state detected for %d %d",tls, tlc);
        }
        break;

    case STM_TRIGGER_T3:                        /* from timer control */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changebackState == CHANGEBACK_TIME_CONTROLLED_DIVERT)
        {
            /* reset masks */
            ln->needCBA = ln->gotCBA = 0;

            /*
             * restart traffic on link buffered messages first
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE); 
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_CCITT(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            HMRT_Main_CCITT(MTP3_STM_TCBC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);

            TLAC_Main_CCITT(MTP3_STM_TCBC,
                           STM_TRIGGER_CHANGEBACK_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            TSRC_Main_CCITT(MTP3_STM_TCBC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->changebackState = CHANGEBACK_IDLE;
        }
        break;

    case STM_TRIGGER_T4:                        /* from timer control */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changebackState == CHANGEBACK_FIRST_ATTEMPT)
        {
            SS7_LinkPtr tln;
            ITS_USHORT i;

            for (i = 0; i < MAX_LINKS; i++)
            {
                if ((ln->needCBA & (1 << i)) && !(ln->gotCBA & (1 << i)))
                {
                    /* Build SNMM changeback */
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                    MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                    SNMM_HC0_SET(snmm, SNMM_HC0_CHM);
                    SNMM_HC1_SET(snmm, SNMM_HC1_CBD);

                    tln = LINK_FindLink(ln->cbLinkSet, (ITS_OCTET)i);
                    ITS_C_ASSERT(tln != NULL);

                    SNMM_CHANGEBACK_SET_CODE(snmm.data.changeBack,
                                                   (ITS_OCTET)i);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                    SNMM_Encode(&ev, &omtp3, &snmm);

                    /* Increament Link Peg for CBD Transmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);

                    MTP3_Alarm_CCITT(2514, __FILE__, __LINE__,
                                    "linkset:linkcode %x:%x",linkSet,ln->linkCode)
;
                    HMRT_Main_CCITT(MTP3_STM_TCBC,
                                   SMH_TRIGGER_TRAFFIC_MGMT_MSG,
                                   ev.data, ev.len,
                                   ln->cbLinkSet, (ITS_OCTET)i);

                    ITS_EVENT_TERM(&ev);
                }
            }

            /* start T5 */
            tc.timerId = MTP3_T5;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t5 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t5 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

            ln->changebackState = CHANGEBACK_SECOND_ATTEMPT;
        }
        break;

    case STM_TRIGGER_T5:                        /* from timer control */
        ln = LINK_FindLink(linkSet, linkCode);
        if (ln == NULL)
        {
            MTP3_DEBUG(("Can't find link %d:%d\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Can't find link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if (ln->changebackState == CHANGEBACK_SECOND_ATTEMPT)
        {
            /* reset masks */
            ln->needCBA = ln->gotCBA = 0;

            /*
             * restart traffic on link buffered messages first
             *
             * NOTE: SLS unshifting not required here, as this is
             * recovery (link bounce).
             */
            /*ln->qPut = ITS_FALSE;*/
            LINK_SetLinkQPut(ln, ITS_FALSE);
            while (DSMQUEUE_Dequeue(ln->cocbBuf, &cocbEv) == ITS_SUCCESS)
            {
                evRec = ItsEventToMTP3EventRec_CCITT(*cocbEv);

                fetched = &evRec.event;

                MTP2_SendData_CCITT(L2_LINK_SET(fetched),
                                   L2_LINK_CODE(fetched),
                                   L2_MSG_TYPE(fetched),
                                   L2_LINK_DATA(fetched),
                                   (ITS_USHORT)(fetched->len -
                                    3 * sizeof(ITS_OCTET)));

                ITS_EVENT_TERM(cocbEv);
                ITS_Free(cocbEv);
            }

            HMRT_Main_CCITT(MTP3_STM_TCBC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           NULL, 0,
                           linkSet, linkCode);

            TLAC_Main_CCITT(MTP3_STM_TCBC,
                           STM_TRIGGER_CHANGEBACK_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            TSRC_Main_CCITT(MTP3_STM_TCBC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->changebackState = CHANGEBACK_IDLE;
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
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
 ****************************************************************************/
int
TFRC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1], *nmtp3;
    ITS_UINT pc, oldPC;
    ITS_OCTET ni, oldNI, oldLS, oldLC;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, ret;
    SS7_Destination *ent;
    ROUTE_MatchInfo rinfo;
    ROUTE_Info *ri, *newri;

    MTP3_TRACE_ENTRY_CCITT(MTP3_STM_TFRC, src, trigger, sif, len,
                          linkSet, linkCode);

    switch (trigger)
    {
    case STM_TRIGGER_ROUTE_UNAVAILABLE:         /* from TSRC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_CCITT(2489, __FILE__, __LINE__, "%08x",pc);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->forcedState == FORCE_REROUTING_IDLE)
        {
            /*
             * Buffer concerned traffic in forced rerouting buffer
             *
             * NOTE: This is irrelevent in our implementation.  Additional
             * messages for this destination are piling up in our input
             * queue.
             */
            ri->forcedState = FORCE_REROUTING_WAIT_1;
            
            TSRC_Main_CCITT(MTP3_STM_TFRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           sif, len,
                           linkSet, linkCode);
        }
        break;

    case STM_TRIGGER_ALTERNATE_ROUTE_DATA:      /* from TSRC */

        /* new route */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /* get the *old* RL */
        nmtp3 = (MTP3_HEADER *)&sif[sizeof(ITS_OCTET) +
                                         sizeof(MTP3_HEADER)];
        oldLS = sif[sizeof(ITS_OCTET) + 2 * sizeof(MTP3_HEADER)];
        oldLC = sif[2 * sizeof(ITS_OCTET) + 2 * sizeof(MTP3_HEADER)];

        oldPC = MTP3_RL_GET_DPC_VALUE(nmtp3->label);
        oldNI = MTP3_HDR_GET_SIO(*nmtp3) & MTP3_NIC_MASK;

        /* old route rec */
        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, oldPC,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 oldNI, oldLS, oldLC,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            MTP3_Alarm_CCITT(2489, __FILE__, __LINE__, "%08x",pc);

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->forcedState == FORCE_REROUTING_WAIT_1)
        {
            MTP3_HEADER omtp3;
            ITS_EVENT ev;

            if (RoutingChanged(sif, len, linkSet, linkCode))
            {
                /* new route rec */
                if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                         REMOTE_ROUTE, ROUTE_DPC_NI,
                                                         FAMILY_ITU,
                                                         ni, linkSet, linkCode,
                                                         ITS_SS7_DEFAULT_LINK_PRI,
                                                         ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
                {
                    MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

                    MTP3_Alarm_CCITT(2489, __FILE__, __LINE__, "%08x",pc);

                    return (ret);
                }

                if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                               &firstMatch, &lastMatch,
                                               &whichLinkCode,
                                               ITS_FALSE)) == NULL)
                {
                    MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

                    return (ITS_EINVALIDARGS);
                }

                newri = ent->entries[whichEntry];

                if (!newri->isAllowed)
                {
                    /* 
                     * Discard messages in forced rerouting buffer
                     * NOTE: This will happen automatically
                     */
                }
                else
                {
                    /*
                     * start straffic on newly available route, buffer first.
                     * NOTE: This will happen automatically
                     */
                }

                HMRT_Main_CCITT(MTP3_STM_TFRC,
                               SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                               sif, len,
                               linkSet, linkCode);
            }

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            MTP3_HDR_SET_SIO(omtp3, oldNI);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, oldPC);

            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            TSRC_Main_CCITT(MTP3_STM_TFRC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           ev.data, ev.len,
                           oldLS, oldLC);

            RTAC_Main_CCITT(MTP3_STM_TFRC,
                           SRM_TRIGGER_FORCED_REROUTE_END,
                           ev.data, ev.len,
                           oldLS, oldLC);

            RTRC_Main_CCITT(MTP3_STM_TFRC,
                           SRM_TRIGGER_FORCED_REROUTE_END,
                           ev.data, ev.len,
                           oldLS, oldLC);

            ITS_EVENT_TERM(&ev);

            ri->forcedState = FORCE_REROUTING_IDLE;
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
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
 ****************************************************************************/
int
TCRC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    MTP3_HEADER *nmtp3, omtp3, *slsUnshift;
    MTP3_TimerContext tc;
    ITS_UINT pc, oldPC;
    ITS_OCTET ni, oldNI, oldLS, oldLC, sls;
    ITS_EVENT ev, *fetched;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, ret;
    SS7_Destination *ent;
    ROUTE_MatchInfo rinfo;
    ROUTE_Info *ri;
    SS7_LinkSetPtr ls;

    MTP3_TRACE_ENTRY_CCITT(MTP3_STM_TCRC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* needs a point code to get a route? */    
    switch (trigger)
    {
    case STM_TRIGGER_ROUTE_RESTRICTED:      /* from TSRC */
    case STM_TRIGGER_ROUTE_AVAILABLE:       /* from RTAC, TSRC */
    case STM_TRIGGER_ROUTE_UNAVAILABLE:
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }
        ri = ent->entries[whichEntry];

        if (ri->controlledState == CONT_REROUTING_IDLE)
        {
            ri->controlledState = CONT_REROUTING_WAIT_1;

            TSRC_Main_CCITT(MTP3_STM_TCRC,
                           STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           sif, len,
                           linkSet, linkCode);
        }
        break;

    case STM_TRIGGER_ALTERNATE_ROUTE_DATA: /* from TSRC */

        /* new route */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /* get the *old* RL */
        nmtp3 = (MTP3_HEADER *)&sif[sizeof(ITS_OCTET) +
                                         sizeof(MTP3_HEADER)];
        oldLS = sif[sizeof(ITS_OCTET) + 2 * sizeof(MTP3_HEADER)];
        oldLC = sif[2 * sizeof(ITS_OCTET) + 2 * sizeof(MTP3_HEADER)];

        oldPC = MTP3_RL_GET_DPC_VALUE(nmtp3->label);
        oldNI = MTP3_HDR_GET_SIO(*nmtp3) & MTP3_NIC_MASK;

        /* old route rec */
        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, oldPC,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 oldNI, oldLS, oldLC,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }

        ri = ent->entries[whichEntry];

        if (ri->controlledState == CONT_REROUTING_WAIT_1)
        {
            if (!RoutingChanged(sif, len, linkSet, linkCode))
            {
                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                MTP3_HDR_SET_SIO(omtp3, oldNI);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, oldPC);

                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, NULL, 0);

                TSRC_Main_CCITT(MTP3_STM_TCRC,
                               STM_TRIGGER_PROCEDURE_TERMINATED,
                               ev.data, ev.len,
                               oldLS, oldLC);

                RTPC_Main_CCITT(MTP3_STM_TCRC,
                               SRM_TRIGGER_CONTROLLED_REROUTE_END,
                               ev.data, ev.len,
                               oldLS, oldLC);

                ITS_EVENT_TERM(&ev);

                ri->controlledState = CONT_REROUTING_IDLE;
            }
            else
            {
                /*
                 * buffer concerned traffic in controlled rerouting buffer
                 * NOTE: This signals HMCG to queue instead of transmitting.
                 */
                ri->qPut = ITS_TRUE;

                /* start T6 */
                tc.timerId = MTP3_T6;
                tc.data.routeInfo.pointCode = oldPC;
                tc.data.routeInfo.linkSet = oldLS;
                tc.data.routeInfo.sio = oldNI;

                ri->t6 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t6 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                ri->controlledState = CONT_REROUTING_WAIT_2;
            }
        }
        break;

    case STM_TRIGGER_T6:                    /* from timer control */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        if ((ret = ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                                 REMOTE_ROUTE, ROUTE_DPC_NI,
                                                 FAMILY_ITU,
                                                 ni, linkSet, linkCode,
                                                 ITS_SS7_DEFAULT_LINK_PRI,
                                                 ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc));

            return (ret);
        }

        if ((ent = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                       &firstMatch, &lastMatch,
                                       &whichLinkCode,
                                       ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("Unable to find route for destination %08x\n", pc));

            return (ITS_EINVALIDARGS);
        }

        ri = ent->entries[whichEntry];

        ri->t6 = TIMER_BAD_SERIAL;

        /* stop buffering on this route */
        ri->qPut = ITS_FALSE;

        if (ri->controlledState == CONT_REROUTING_WAIT_2)
        {
            /*
             * start traffic on new route buffered messages first
             *
             * ROTATION COMMENT
             *
             * SLS unshifting *is* required here.  It's not terribly
             * awful, though.
             */
            while (DSMQUEUE_Dequeue(ri->crBuf, &fetched) == ITS_SUCCESS)
            {

                /* if this fails we're toast. */
                ls = LINKSET_FindLinkSet(L2_LINK_SET(fetched));
                if ( ls == NULL)
                {
                    ITS_C_ASSERT(ls != NULL);
                }

                slsUnshift = (MTP3_HEADER *)(L2_LINK_DATA(fetched) + 1);
                sls = MTP3_RL_GET_SLS(slsUnshift->label);

                /*
                 * NOTE: ITU doesn't need to undo bit rotation.
                 */
                /* sls = ROUTE_SLSUnrotate(!ls->is5Bit, sls); */
                /* MTP3_RL_SET_SLS(slsUnshift->label, sls); */

                HMRT_Main_CCITT(MTP3_SMH_HMDT,
                               SMH_TRIGGER_MSG_FOR_ROUTING,
                               L2_LINK_DATA(fetched),
                               (ITS_USHORT)(fetched->len -
                                3 * sizeof(ITS_OCTET)),
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);
            }

            HMRT_Main_CCITT(MTP3_STM_TCRC,
                           SMH_TRIGGER_UPDATE_ROUTING_TABLES,
                           sif, len,
                           linkSet, linkCode);

            TSRC_Main_CCITT(MTP3_STM_TCRC,
                           STM_TRIGGER_PROCEDURE_TERMINATED,
                           sif, len,
                           linkSet, linkCode);

            RTPC_Main_CCITT(MTP3_STM_TCRC,
                           SRM_TRIGGER_CONTROLLED_REROUTE_END,
                           sif, len,
                           linkSet, linkCode);

            RTAC_Main_CCITT(MTP3_STM_TCRC,
                           SRM_TRIGGER_CONTROLLED_REROUTE_END,
                           sif, len,
                           linkSet, linkCode);

            RTRC_Main_CCITT(MTP3_STM_TCRC,
                           SRM_TRIGGER_CONTROLLED_REROUTE_END,
                           sif, len,
                           linkSet, linkCode);

            ri->controlledState = CONT_REROUTING_IDLE;
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
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
 ****************************************************************************/
int
TSFC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3=NULL;
    SNMM_MESSAGE *snmm=NULL;
    MTP3_PAUSE_RESUME pr;
    MTP3_STATUS stat;
    ITS_UINT apc=0, dpc=0, opc=0;
    SS7_LinkSetPtr ls;
    ITS_EVENT ev;
    int ret;

    MTP3_TRACE_ENTRY_CCITT(MTP3_STM_TSFC, src, trigger, sif, len,
                          linkSet, linkCode);

    if (sif != NULL)
    {
        mtp3 = (MTP3_HEADER *)&sif[1];
        snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                              sizeof(ITS_OCTET)];


        /* For MTP3 indications the Routing Label is build as follow:
         * OPC = The affected Destination 
         * DPC = Local Point code 
         */
        opc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        if ( ( ls = LINKSET_FindLinkSet(linkSet) ) != NULL)
        {
            dpc = ls->lpc;
        } 
    }

    /* this looks like it wants a point code, maybe a user part (for UPU) */
    switch (trigger)
    {
    case STM_TRIGGER_DEST_CONGESTION_STATUS:    /* from TRCC, RTCC, TSRC */
        /* Stop signalling traffic to concerned destination with msg
         * priority less than congestion status */
        /* Generate MTP3 status indication to each user part
         */
        apc = SNMM_TRANSFER_CONTROL_GET_DEST(snmm->data.transferControl);
        MTP3_PC_SET_VALUE(stat.affected, apc);
        MTP3_RL_SET_OPC_VALUE(mtp3->label, opc); 
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc); 
        stat.cause = MTP3_STATUS_CONGESTED;
        stat.congLevel = SNMM_TRANSFER_CONTROL_GET_STATUS(snmm->data.transferControl);

        if ((ret = MTP3_Encode(&ev, MTP3_MSG_STATUS, mtp3,
                               (ITS_OCTET *)&stat, sizeof(stat))) !=
            ITS_SUCCESS)
        {
            MTP3_ERROR(("Failed to encode status message\n"));
 
            return (ret);
        }

        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_STATUS);

        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_CONGESTION);

        return CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                         NULL, (ITS_POINTER)&ev);

    case STM_TRIGGER_DEST_INACCESS:             /* from TSRC */
        /* Stop signalling traffic to concerned destination */
        /* Generate MTP3 PAUSE indication to each user part */
        apc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        MTP3_PC_SET_VALUE(pr.affected, apc);
        MTP3_RL_SET_OPC_VALUE(mtp3->label, opc); 
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc); 

        if ((ret = MTP3_Encode(&ev, MTP3_MSG_PAUSE, mtp3,
                               (ITS_OCTET *)&pr, sizeof(pr))) !=
            ITS_SUCCESS)
        {
            MTP3_ERROR(("Failed to encode status message\n"));

            return (ret);
        }

        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_PAUSE);

        /* Increament the peg for Adjecent SP UNACCESIBLE*/
        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE);

        /* Increament the peg for Route Set Unavailable */
        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_ROUTESET_UNAVAILABLE);

        return CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                         NULL, (ITS_POINTER)&ev);

    case STM_TRIGGER_DEST_ACCESS:               /* from TSRC */
        /* Start signalling traffic to concerned destination */
        /* Generate MTP3 RESUME indication to each user part */
        apc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        MTP3_PC_SET_VALUE(pr.affected, apc);
        MTP3_RL_SET_OPC_VALUE(mtp3->label, opc); 
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc); 

        if ((ret = MTP3_Encode(&ev, MTP3_MSG_RESUME, mtp3,
                               (ITS_OCTET *)&pr, sizeof(pr))) !=
            ITS_SUCCESS)
        {
            MTP3_ERROR(("Failed to encode status message\n"));

            return (ret);
        }

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RESUME);

        return CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                         NULL, (ITS_POINTER)&ev);

    case STM_TRIGGER_UPU:                       /* from RTCC */
        /* Build a MTP3_STATUS message and send to all user parts */
        apc = SNMM_USER_PART_UNAVAIL_GET_DEST(
                  snmm->data.userPartUnavailable);

        MTP3_PC_SET_VALUE(stat.affected, apc);
        MTP3_RL_SET_OPC_VALUE(mtp3->label, opc); 
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc); 

        if (SNMM_USER_PART_UNAVAIL_GET_CAUSE(
                   snmm->data.userPartUnavailable) == SNMM_UPU_CAUSE_INACCESS)
        {
            stat.cause = MTP3_STATUS_UPU_INACCESS;
        }
        else
        {
            stat.cause = MTP3_STATUS_UPU_UNEQUIP;
        }
        stat.congLevel = 0;

        if ((ret = MTP3_Encode(&ev, MTP3_MSG_STATUS, mtp3,
                               (ITS_OCTET *)&stat, sizeof(stat))) !=
            ITS_SUCCESS)
        {
            MTP3_ERROR(("Failed to encode status message\n"));

            return (ret);
        }

        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_STATUS);

        return CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                         NULL, (ITS_POINTER)&ev);

    case STM_TRIGGER_RESTART_BEGIN:             /* from TPRC */
        /* The SDL says send a restart indication to L4.  What's the point. */
        break;

    case STM_TRIGGER_RESTART_END:               /* from TPRC */
        /* The SDL says send a restart end indication to L4.  What's the point */
        /* newer SDL says send a resume for all reachable destinations if in
         * idle state. */
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
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
static ITS_BOOLEAN
FullRestartNeeded()
{
    MTP3_TimerContext tc;

    if (FullRestartNeeded_CCITT())
    {
        tc.timerId = MTP3_T27;

        t27 =
            TIMERS_StartSharedTimer(ITS_MTP3_SRC,
                              __ccitt_t27 / MILLISEC_PER_SEC,
                              &tc, sizeof(MTP3_TimerContext));
    }

    return (FullRestartNeeded_CCITT());
}

/*.implementation:static
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
static ITS_BOOLEAN
AllExpectedTRAs()
{
    ITS_UINT i;
    SS7_LinkSetPtr ls;

    for (i = 0; i <= ITS_SS7_DEFAULT_LINK_SET; i++)
    {
        if ((ls = LINKSET_FindLinkSet((ITS_OCTET)i)) != NULL &&
            ls->adjacent != 0)
        {
            if ((ls->isUp && !ls->gotTRA) ||
                !ls->isUp)
            {
                return (ITS_FALSE);
            }
        }
    }

    return (ITS_TRUE);
}

/*.implementation:static
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
static ITS_BOOLEAN
FirstLinkAvailable(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;
    ITS_UINT i;

    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Can't find link set %d\n", linkSet));

        return (ITS_FALSE);
    }

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->isUp &&
            ls->links[i]->isAllowed &&
            ls->links[i]->testPassed &&
            ls->links[i]->linkCode != linkCode)
        {
            return (ITS_FALSE);
        }
    }

    return (ITS_TRUE);
}

/*.implementation:static
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
static ITS_BOOLEAN
SufficientLinksAvailable(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;
    ITS_UINT i, numWanted;

    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
 
        return (ITS_FALSE);
    }

    numWanted = 0;
    for (i = 0; i < ls->numToStart; i++)
    {
        if (ls->links[i]->linkCode == linkCode ||
            (ls->links[i]->isUp && ls->links[i]->isAllowed))
        {
            numWanted++;
        }
    }

    if (numWanted >= (ls->numToStart - 1))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

static ITS_BOOLEAN statusFirstTime = ITS_TRUE;

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
TPRC_Main_CCITT(MTP3_SubSystems src, STM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    MTP3_TimerContext tc;
    ITS_UINT pc, i;
    ITS_OCTET ni;
    SS7_LinkSetPtr ls;

    MTP3_TRACE_ENTRY_CCITT(MTP3_STM_TPRC, src, trigger, sif, len,
                          linkSet, linkCode);

    /* this looks like it doesn't want args at all */
    /* no, link available/unavailable needs linkset linkcode */
    /* turns out it mostly needs linkSet */
    switch (trigger)
    {
    case STM_TRIGGER_T27: /* from timer control */
        /* have to wait until t27 expires to continue */

        SPRestartingSet_CCITT(ITS_TRUE);

        statusFirstTime = ITS_TRUE;

        for (i = 0; i <= ITS_SS7_DEFAULT_LINK_SET; i++)
        {
            if ((ls = LINKSET_FindLinkSet((ITS_OCTET)i)) != NULL)
            {
                ls->gotTRA = ITS_FALSE;
                ls->state = RESTART_WAIT_1;
            }
        }

        LLSC_Main_CCITT(MTP3_STM_TPRC,
                       SLM_TRIGGER_RESTART_BEGINS,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        TSRC_Main_CCITT(MTP3_STM_TPRC,
                       STM_TRIGGER_RESTART_BEGIN,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        TSFC_Main_CCITT(MTP3_STM_TPRC,
                       STM_TRIGGER_RESTART_BEGIN,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        TLAC_Main_CCITT(MTP3_STM_TPRC,
                       STM_TRIGGER_RESTART_BEGIN,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        RSRT_Main_CCITT(MTP3_STM_TPRC,
                       SRM_TRIGGER_RESTART_BEGINS,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);
        break;

    case STM_TRIGGER_TRAFFIC_RESTART_ALLOWED:   /* from HMDT */
        pc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /* may be from non-adjacent */
        linkSet = MTP3_FindAdjacent_CCITT(ni, pc, linkSet);

        ls = LINKSET_FindLinkSet(linkSet);

        if (ls == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if (ls->state == RESTART_IDLE)
        {
            TSRC_Main_CCITT(MTP3_STM_TPRC,
                           STM_TRIGGER_TRAFFIC_RESTART_ALLOWED,
                           sif, len,
                           linkSet, linkCode);
        }
        else if (ls->state == RESTART_WAIT_1)
        {
            /* mark TRA received */
            ls->gotTRA = ITS_TRUE;
        }
        else if (ls->state == RESTART_WAIT_2)
        {
            /* mark TRA recieved */
            if (AllExpectedTRAs())
            {
                ITS_C_ASSERT(ls != NULL);

                /* stop T23 */
                if (ls->t23 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ls->t23);
                    ls->t23 = TIMER_BAD_SERIAL;
                }

                if (STPFunction_CCITT())
                {
                    ls->state = RESTART_WAIT_3;

                    if (statusFirstTime)
                    {
                        TSRC_Main_CCITT(MTP3_STM_TPRC,
                                       STM_TRIGGER_SENDING_STATUS_PHASE,
                                       NULL, 0,
                                       linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TSRC_Main_CCITT(MTP3_STM_TPRC,
                                       STM_TRIGGER_SEND_STATUS,
                                       NULL, 0,
                                       linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        statusFirstTime = ITS_FALSE;
                    }

                    /* start T24 */
                    tc.timerId = MTP3_T24;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                    ls->t24 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                           __ccitt_t24 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));
                }
                else
                {
                    /* stop T26 */
                    if (ls->t26 != TIMER_BAD_SERIAL)
                    {
                        TIMERS_CancelSharedTimer(ls->t26);
                        ls->t26 = TIMER_BAD_SERIAL;
                    }

                    ls->state = RESTART_IDLE;

                    if (SPRestarting_CCITT())
                    {
                        TSRC_Main_CCITT(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TSFC_Main_CCITT(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TLAC_Main_CCITT(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        RSRT_Main_CCITT(MTP3_STM_TPRC,
                                       SRM_TRIGGER_RESTART_ENDS,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        SPRestartingSet_CCITT(ITS_FALSE);
                        /* FIXME: Clear fullRestartNeeded? */
                    }
                }
            }
        }
        break;

    case STM_TRIGGER_RESTART_INDIC:             /* from MGMT */
        /* cancel all marks */
        if (!FullRestartNeeded())
        {
            statusFirstTime = ITS_TRUE;

            for (i = 0; i <= ITS_SS7_DEFAULT_LINK_SET; i++)
            {
                if ((ls = LINKSET_FindLinkSet((ITS_OCTET)i)) != NULL)
                {
                    ls->state = RESTART_IDLE;
                }
            }


            TSRC_Main_CCITT(MTP3_STM_TPRC,
                           STM_TRIGGER_RESTART_END,
                           NULL, 0,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);

            TSFC_Main_CCITT(MTP3_STM_TPRC,
                           STM_TRIGGER_RESTART_END,
                           NULL, 0,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);

            SPRestartingSet_CCITT(ITS_FALSE);
            /* FIXME: Clear fullRestartNeeded? */
        }
        break;

    case STM_TRIGGER_T26:                       /* from timer control */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        ls->t26 = TIMER_BAD_SERIAL;

        if (SPRestarting_CCITT())
        {
            if (ls->state == RESTART_WAIT_1 ||
                ls->state == RESTART_WAIT_2 ||
                ls->state == RESTART_WAIT_3)
            {
                TSRC_Main_CCITT(MTP3_STM_TPRC,
                               STM_TRIGGER_SEND_TRW,
                               NULL, 0,
                               linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                /* start T26 */
                tc.timerId = MTP3_T26;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
 
                ls->t26 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t26 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }
        }
        break;

    case STM_TRIGGER_T22:                       /* from timer control */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        ls->t22 = TIMER_BAD_SERIAL;

        if (ls->state == RESTART_WAIT_1)
        {
            if (!AllExpectedTRAs())
            {
                /* start T23 */
                tc.timerId = MTP3_T23;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                ls->t23 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t23 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                ls->state = RESTART_WAIT_2;
            }
            else
            {
                if (STPFunction_CCITT())
                {
                    ls->state = RESTART_WAIT_3;

                    if (statusFirstTime)
                    {
                        TSRC_Main_CCITT(MTP3_STM_TPRC,
                                       STM_TRIGGER_SENDING_STATUS_PHASE,
                                       NULL, 0,
                                       linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TSRC_Main_CCITT(MTP3_STM_TPRC,
                                       STM_TRIGGER_SEND_STATUS,
                                       NULL, 0,
                                       linkSet,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        statusFirstTime = ITS_FALSE;
                    }

                    /* start T24 */
                    tc.timerId = MTP3_T24;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                    ls->t24 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                           __ccitt_t24 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));
                }
                else
                {
                    /* stop T26 */
                    if (ls->t26 != TIMER_BAD_SERIAL)
                    {
                        TIMERS_CancelSharedTimer(ls->t26);
                        ls->t26 = TIMER_BAD_SERIAL;
                    }

                    ls->state = RESTART_IDLE;

                    if (SPRestarting_CCITT())
                    {
                        TSRC_Main_CCITT(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TSFC_Main_CCITT(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        TLAC_Main_CCITT(MTP3_STM_TPRC,
                                       STM_TRIGGER_RESTART_END,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        RSRT_Main_CCITT(MTP3_STM_TPRC,
                                       SRM_TRIGGER_RESTART_ENDS,
                                       NULL, 0,
                                       ITS_SS7_DEFAULT_LINK_SET,
                                       ITS_SS7_DEFAULT_LINK_CODE);

                        SPRestartingSet_CCITT(ITS_FALSE);
                    }
                }
            }
        }
        break;

    case STM_TRIGGER_LINK_AVAILABLE:            /* from TLAC */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        if (ls->state == RESTART_WAIT_1)
        {
            /* mark link available */
            if (FirstLinkAvailable(linkSet, linkCode))
            {
                TSRC_Main_CCITT(MTP3_STM_TPRC,
                               STM_TRIGGER_SEND_TRW,
                               NULL, 0,
                               linkSet,
                               linkCode);

                /* start T26 */
                tc.timerId = MTP3_T26;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                /* This needs to be on a link */
                if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
                {
                    return (ITS_SUCCESS);
                }

                ls->t26 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t26 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                /* start T22 */
                tc.timerId = MTP3_T22;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                ls->t22 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t22 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }

            if (SufficientLinksAvailable(linkSet, linkCode))
            {
                if (ls->t22 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ls->t22);
                    ls->t22 = TIMER_BAD_SERIAL;
                }

                if (!AllExpectedTRAs())
                {
                    /* start T23 */
                    tc.timerId = MTP3_T23;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                    ls->t23 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                           __ccitt_t23 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    ls->state = RESTART_WAIT_2;
                }
                else
                {
                    if (STPFunction_CCITT())
                    {
                        ls->state = RESTART_WAIT_3;

                        if (statusFirstTime)
                        {
                            TSRC_Main_CCITT(MTP3_STM_TPRC,
                                           STM_TRIGGER_SENDING_STATUS_PHASE,
                                           NULL, 0,
                                           linkSet,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            TSRC_Main_CCITT(MTP3_STM_TPRC,
                                           STM_TRIGGER_SEND_STATUS,
                                           NULL, 0,
                                           linkSet,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            statusFirstTime = ITS_FALSE;
                        }

                        /* start T24 */
                        tc.timerId = MTP3_T24;
                        tc.data.linkInfo.linkSet = linkSet;
                        tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                        ls->t24 =
                            TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                               __ccitt_t24 * USEC_PER_MILLISEC,
                                               &tc, sizeof(MTP3_TimerContext));
                    }
                    else
                    {
                        /* stop T26 */
                        if (ls->t26 != TIMER_BAD_SERIAL)
                        {
                            TIMERS_CancelSharedTimer(ls->t26);
                            ls->t26 = TIMER_BAD_SERIAL;
                        }

                        ls->state = RESTART_IDLE;

                        if (SPRestarting_CCITT())
                        {
                            TSRC_Main_CCITT(MTP3_STM_TPRC,
                                           STM_TRIGGER_RESTART_END,
                                           NULL, 0,
                                           ITS_SS7_DEFAULT_LINK_SET,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            TSFC_Main_CCITT(MTP3_STM_TPRC,
                                           STM_TRIGGER_RESTART_END,
                                           NULL, 0,
                                           ITS_SS7_DEFAULT_LINK_SET,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            TLAC_Main_CCITT(MTP3_STM_TPRC,
                                           STM_TRIGGER_RESTART_END,
                                           NULL, 0,
                                           ITS_SS7_DEFAULT_LINK_SET,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            RSRT_Main_CCITT(MTP3_STM_TPRC,
                                           SRM_TRIGGER_RESTART_ENDS,
                                           NULL, 0,
                                           ITS_SS7_DEFAULT_LINK_SET,
                                           ITS_SS7_DEFAULT_LINK_CODE);

                            SPRestartingSet_CCITT(ITS_FALSE);
                        }
                    }
                }
            }
        }
        break;

    case STM_TRIGGER_LINK_UNAVAILABLE:          /* from TLAC */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        if (ls->state == RESTART_WAIT_1)
        {
            /* cancel link available */
        }
        break;

    case STM_TRIGGER_T23:                       /* from timer control */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        ls->t23 = TIMER_BAD_SERIAL;

        if (ls->state == RESTART_WAIT_2)
        {
            if (STPFunction_CCITT())
            {
                ls->state = RESTART_WAIT_3;

                if (statusFirstTime)
                {
                    TSRC_Main_CCITT(MTP3_STM_TPRC,
                                   STM_TRIGGER_SENDING_STATUS_PHASE,
                                   NULL, 0,
                                   linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    TSRC_Main_CCITT(MTP3_STM_TPRC,
                                   STM_TRIGGER_SEND_STATUS,
                                   NULL, 0,
                                   linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    statusFirstTime = ITS_FALSE;
                }

                /* start T24 */
                tc.timerId = MTP3_T24;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

                ls->t24 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t24 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }
            else
            {
                /* stop T26 */
                if (ls->t26 != TIMER_BAD_SERIAL)
                {
                    TIMERS_CancelSharedTimer(ls->t26);
                    ls->t26 = TIMER_BAD_SERIAL;
                }

                ls->state = RESTART_IDLE;

                if (SPRestarting_CCITT())
                {
                    TSRC_Main_CCITT(MTP3_STM_TPRC,
                                   STM_TRIGGER_RESTART_END,
                                   NULL, 0,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    TSFC_Main_CCITT(MTP3_STM_TPRC,
                                   STM_TRIGGER_RESTART_END,
                                   NULL, 0,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    TLAC_Main_CCITT(MTP3_STM_TPRC,
                                   STM_TRIGGER_RESTART_END,
                                   NULL, 0,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    RSRT_Main_CCITT(MTP3_STM_TPRC,
                                   SRM_TRIGGER_RESTART_ENDS,
                                   NULL, 0,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    SPRestartingSet_CCITT(ITS_FALSE);
                }
            }
        }
        break;

    case STM_TRIGGER_STATUS_SENT:               /* from TSRC */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        if (ls->state == RESTART_WAIT_3)
        {
            /* stop T24 */
            if (ls->t24 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ls->t24);
                ls->t23 = TIMER_BAD_SERIAL;
            }

            /* stop T26 */
            if (ls->t26 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ls->t26);
                ls->t26 = TIMER_BAD_SERIAL;
            }

            ls->state = RESTART_IDLE;

            if (SPRestarting_CCITT())
            {
                TSRC_Main_CCITT(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                TSFC_Main_CCITT(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                TLAC_Main_CCITT(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                RSRT_Main_CCITT(MTP3_STM_TPRC,
                               SRM_TRIGGER_RESTART_ENDS,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                SPRestartingSet_CCITT(ITS_FALSE);
            }
        }
        break;

    case STM_TRIGGER_T24:                       /* from timer control */
        /* This needs to be on a linkSet */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            return (ITS_SUCCESS);
        }

        ls->t24 = TIMER_BAD_SERIAL;

        if (ls->state == RESTART_WAIT_3)
        {
            /* stop T26 */
            if (ls->t26 != TIMER_BAD_SERIAL)
            {
                TIMERS_CancelSharedTimer(ls->t26);
                ls->t26 = TIMER_BAD_SERIAL;
            }

            ls->state = RESTART_IDLE;

            if (SPRestarting_CCITT())
            {
                TSRC_Main_CCITT(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                TSFC_Main_CCITT(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                TLAC_Main_CCITT(MTP3_STM_TPRC,
                               STM_TRIGGER_RESTART_END,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                RSRT_Main_CCITT(MTP3_STM_TPRC,
                               SRM_TRIGGER_RESTART_ENDS,
                               NULL, 0,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                SPRestartingSet_CCITT(ITS_FALSE);
            }
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
}
