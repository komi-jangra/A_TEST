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
 *  ID: $Id: ttc-slm.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $ 
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
 * LOG: Revision 9.1  2005/03/23 12:54:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.1  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/02/18 11:26:52  dsatish
 * LOG: Added Initial version file for TTC
 * LOG:
 * LOG: Revision 7.6.2.3.8.1.8.3  2005/01/25 11:36:14  snagesh
 * LOG: OAM Bug fixes for bugs 1419,1420
 * LOG:
 * LOG: Revision 7.6.2.3.8.1.8.2  2004/12/31 07:28:03  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.6.2.3.8.1.8.1  2004/12/17 03:57:46  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.6.2.3.8.1  2004/08/10 12:14:46  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.6.2.3  2003/04/07 08:21:55  randresol
 * LOG: Preliminary fix for numToStart problem
 * LOG:
 * LOG: Revision 7.6.2.2  2003/02/21 01:42:34  randresol
 * LOG: Add more alarms
 * LOG:
 * LOG: Revision 7.6.2.1  2003/02/18 02:35:01  randresol
 * LOG: Issue "Out of Service" alarm when a link goes down
 * LOG:
 * LOG: Revision 7.6  2003/02/13 10:37:38  ttipatre
 * LOG: New Alarms Added.
 * LOG:
 * LOG: Revision 7.5  2002/12/24 07:47:47  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.4  2002/12/03 20:57:07  randresol
 * LOG: Make sure the link is STOPped when COO/ECO is received.
 * LOG:
 * LOG: Revision 7.3  2002/11/20 05:19:11  ttipatre
 * LOG: Modified to protocol specific alarms.
 * LOG:
 * LOG: Revision 7.2  2002/11/09 22:07:13  randresol
 * LOG: Solve link stability problem after a deactivation/actication
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/08/16 22:07:09  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.3  2002/06/13 20:34:49  ttipatre
 * LOG: Adding MTP3 Pegs and Alarms
 * LOG:
 * LOG: Revision 6.2  2002/05/15 15:06:48  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2001/12/29 00:12:36  mmiers
 * LOG: ITU uses SLS key for SLC
 * LOG:
 * LOG: Revision 5.3  2001/12/28 19:35:02  mmiers
 * LOG: Remove priority.  ITU doesn't have this.
 * LOG:
 * LOG: Revision 5.2  2001/12/11 23:49:53  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.1  2001/12/06 22:39:05  mmiers
 * LOG: First cut of ITU MTP3.
 * LOG:
 *
 ****************************************************************************/

#include <string.h>
#include <stdlib.h>

#undef ANSI
#undef CCITT
#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <its.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_timers.h>
#include <its_assertion.h>

#ident "$Id: ttc-slm.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

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

static ITS_BOOLEAN  optionA = ITS_TRUE;
static ITS_BOOLEAN  optionB = ITS_FALSE;

/*
 * this is left to the discretion of the MTP2 implementation.
 */
#define MTP2_RETRIEVAL_IN_PARALLEL  0

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
SLM_Main_CCITT(MTP3_SubSystems src, MTP3_SubSystems dest,
              SLM_Triggers trigger,
              ITS_OCTET *sif, ITS_USHORT len,
              ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SNMM_MESSAGE *snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                              sizeof(ITS_OCTET)];

    MTP3_TRACE_ENTRY_CCITT(MTP3_SLM, src, trigger, sif, len,
                           linkSet, linkCode);


    if (trigger == SLM_TRIGGER_L2_MSG)
    {
        switch (SNMM_HC0_GET(*snmm))
        {
        case SNMM_HC0_DLM:
            switch (SNMM_HC1_GET(*snmm))
            {
            case SNMM_HC1_DLC:
                /* data link connection order */
                LSDA_Main_CCITT(src, SLM_TRIGGER_CONNECTION_ORDER,
                               sif, len,
                               linkSet, linkCode);
                break;

            case SNMM_HC1_CSS:
                /* connection successful */
                LSDA_Main_CCITT(src, SLM_TRIGGER_CONNECTION_SUCCESSFUL,
                               sif, len,
                               linkSet, linkCode);
                break;

            case SNMM_HC1_CNS:
                /* connection not successful */
                LSDA_Main_CCITT(src, SLM_TRIGGER_CONNECTION_UNSUCCESS,
                               sif, len,
                               linkSet, linkCode);
                break;

            case SNMM_HC1_CNP:
                /* connection not possible */
                LSDA_Main_CCITT(src, SLM_TRIGGER_CONNECTION_NOT_POSS,
                               sif, len,
                               linkSet, linkCode);
                break;

            default:
                MTP3_DEBUG(("Unknown HC1 code %x\n",
                            SNMM_HC1_GET(*snmm)));
                PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
                break;
            }
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
int
LLSC_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;
    ITS_UINT i, j, k;
    int cnt;
    static ITS_BOOLEAN starting = ITS_TRUE;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SLM_LLSC, src, trigger, sif, len,
                           linkSet, linkCode);

    switch (trigger)
    {
    case SLM_TRIGGER_ACTIVATE_LINK_SET:      /* from MGMT */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Failed to find link set\n"));
 
            MTP3_Alarm_CCITT(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);

            return (ITS_EINVALIDARGS);
        }
        if (ls->numToStart == 0 /*||
            ls->numToStart > ls->numLinks*/)
        {
            ls->numToStart = ls->numLinks;
        }

        j = 0;
        for (i = 0; i < ls->numLinks; i++)
        {
            ln = ls->links[i];

            /* select links to activate */
            if (ln->initActive)
            {
                j++;

                LSAC_Main_CCITT(MTP3_SLM_LLSC,
                               SLM_TRIGGER_ACTIVATE_LINK,
                               NULL, 0,
                               ls->linkSet, ln->linkCode);

                if (j >= ls->numToStart)
                {
                    i = ls->numLinks;
                }
            }
        }
        return (ITS_SUCCESS);

    case SLM_TRIGGER_RESTART_BEGINS:         /* from TPRC */
        /*
         * Set initial admin state of all link sets.
         * This is done elsewhere.
         */
        /* placeholder */
        for (k = 0; k < ITS_SS7_DEFAULT_LINK_SET; k++)
        {
            if ((ls = LINKSET_FindLinkSet((ITS_OCTET)k)) == NULL ||
                ls->adjacent == 0)
            {
                continue;
            }

            if (ls->numToStart == 0 /*||
                ls->numToStart > ls->numLinks*/)
            {
                ls->numToStart = ls->numLinks;
            }

            j = 0;
            for (i = 0; i < ls->numLinks; i++)
            {
                ln = ls->links[i];

                /* select links to activate */
                if (ln->initActive)
                {
                    j++;

                    LSAC_Main_CCITT(MTP3_SLM_LLSC,
                                   SLM_TRIGGER_ACTIVATE_LINK,
                                   NULL, 0,
                                   ls->linkSet, ln->linkCode);

                    if (j >= ls->numToStart)
                    {
                        i = ls->numLinks;
                    }
                }
            }
        }
        return (ITS_SUCCESS);

    case SLM_TRIGGER_DEACTIVATE_LINK_SET:    /* from MGMT */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Failed to find link set\n"));

            MTP3_Alarm_CCITT(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);

            return (ITS_EINVALIDARGS);
        }

        for (i = 0; i < ls->numLinks; i++)
        {
            ln = ls->links[i];

            /* select links to deactivate */
            if (ln->isUp)
            {
                LSAC_Main_CCITT(MTP3_SLM_LLSC,
                               SLM_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               ls->linkSet, ln->linkCode);
            }
        }
        return (ITS_SUCCESS);

    case SLM_TRIGGER_LINK_ACTIVE:            /* from LSAC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Failed to find link set\n"));
 
            MTP3_Alarm_CCITT(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);

            return (ITS_EINVALIDARGS);
        }

        j = 0;
        for (i = 0; i < ls->numLinks; i++)
        {
            if (ls->links[i]->isUp)
            {
                j++;
            }
        }

        /* is current number of active links greater than specified? */
        if (j > ls->numToStart)
        {
#if 0
/* FIXME: ln->numToStart always set to initial ln->numLinks
          This is because numToStart in XML is not assigned 
          to this field. This problem prevent us from addding 
          a link dynamically... Automatic deactivation is 
          removed for now until the correct XML value is set
          properly in linkset record.
*/
            /* select link to deactivate */
            for (cnt = (int)ls->numLinks - 1; cnt >= 0; cnt--)
            {
                if (ls->links[cnt]->isUp)
                {
                    LSAC_Main_CCITT(MTP3_SLM_LLSC,
                                   SLM_TRIGGER_DEACTIVATE_LINK,
                                   NULL, 0,
                                   ls->linkSet, ls->links[cnt]->linkCode);

                    break;
                }
            }
#endif
        }
        break;

    case SLM_TRIGGER_LINK_INACTIVE:          /* from LSAC */
        /* don't care */
        break;

    case SLM_TRIGGER_LINK_FAILED:            /* from LSAC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Failed to find link set\n"));

            MTP3_Alarm_CCITT(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);

            return (ITS_EINVALIDARGS);
        }

        for (i = 0; i < ls->numLinks; i++)
        {
            if (ls->links[i]->isUp)
            {
                break;
            }
        }

        /* no active link in link set? */
        if (i == ls->numLinks)
        {
            for (i = 0; i < ls->numLinks; i++)
            {
                ln = ls->links[i];

                /* select links to activate */
                if (ls->links[i]->initActive)
                {
                    LSAC_Main_CCITT(MTP3_SLM_LLSC,
                                   SLM_TRIGGER_ACTIVATE_LINK,
                                   NULL, 0,
                                   ls->linkSet, ln->linkCode);
                }
            }
        }
        break;

    case SLM_TRIGGER_ACTIVATE_ANOTHER_LINK:  /* from LSAC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Failed to find link set\n"));

            MTP3_Alarm_CCITT(2423, __FILE__, __LINE__, "LinkSet %x not found ", linkSet);

            return (ITS_EINVALIDARGS);
        }

        j = 0;
        for (i = 0; i < ls->numLinks; i++)
        {
            if (ls->links[i]->isUp)
            {
                j++;
            }
        }

        /* is current number of active links less than specified? */
        if (j < ls->numToStart)
        {
            /* select link to activate */
            for (cnt = (int)ls->numLinks - 1; cnt >= 0; cnt--)
            {
                if (!ls->links[cnt]->isUp)
                {
                    return LSAC_Main_CCITT(MTP3_SLM_LLSC,
                                          SLM_TRIGGER_ACTIVATE_LINK,
                                          NULL, 0,
                                          linkSet, linkCode);
                }
            }
        }
        break;

    case SLM_TRIGGER_EMERGENCY:              /* from TSRC */
        if (!starting)
        {
            if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
            {
                MTP3_ERROR(("Failed to find link set\n"));

                MTP3_Alarm_CCITT(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);

                return (ITS_EINVALIDARGS);
            }

            for (i = 0; i < ls->numLinks; i++)
            {
                ln = ls->links[i];

                LSAC_Main_CCITT(MTP3_SLM_LLSC,
                               SLM_TRIGGER_EMERGENCY,
                               NULL, 0,
                               ls->linkSet, ln->linkCode);
            }
        }
        break;

    case SLM_TRIGGER_EMERGENCY_CEASES:       /* from TSRC */
        if (!starting)
        {
            if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
            {
                MTP3_ERROR(("Failed to find link set\n"));

                MTP3_Alarm_CCITT(2423, __FILE__, __LINE__, "The LinkSet is %x", linkSet);

                return (ITS_EINVALIDARGS);
            }

            for (i = 0; i < ls->numLinks; i++)
            {
                ln = ls->links[i];

                LSAC_Main_CCITT(MTP3_SLM_LLSC,
                               SLM_TRIGGER_EMERGENCY_CEASES,
                               NULL, 0,
                               ls->linkSet, ln->linkCode);
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
LSAC_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    MTP3_TimerContext tc;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SLM_LSAC, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

        return (ITS_EINVALIDARGS);
    }

    switch (trigger)
    {
    case SLM_TRIGGER_ACTIVATE_LINK:          /* from LLSC: from MGMT */
    case SLM_TRIGGER_DATA_LINK:              /* from LSDA */
        if (ln->activityState == LINK_ACTIVITY_INACTIVE)
        {
            ln->activityState = LINK_ACTIVITY_ACTIVATING_RESTORING;

            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_ACTIVATION);
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_ACTIVATION);

            LSLA_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_START_ACTIVATION,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_EMERGENCY:              /* from LLSC */
        ln->slFlags |= LINK_EMERGENCY;
        break;

    case SLM_TRIGGER_EMERGENCY_CEASES:       /* from LLSC */
        ln->slFlags &= ~LINK_EMERGENCY;
        break;

    case SLM_TRIGGER_T32:
        if (ln->activityState == LINK_ACTIVITY_INACTIVE &&
            optionA)
        {
            /* mark T32 stopped */
            ln->t32 = TIMER_BAD_SERIAL;
        }
        else if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING &&
                 optionA)
        {
            /* mark T32 stopped */
            ln->t32 = TIMER_BAD_SERIAL;

            /* if not link restoring */
            if (!(ln->slFlags & LINK_IS_RESTORING))
            {
                /* start T32 */
                tc.timerId = MTP3_T32;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t32 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t32 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                /* mark link restoring */
                ln->slFlags |= LINK_IS_RESTORING;

                /* cancel T32 stopped */
            }
        }
        else if (ln->activityState == LINK_ACTIVITY_ACTIVE &&
                 optionA)
        {
            /* mark T32 stopped */
            ln->t32 = TIMER_BAD_SERIAL;
        }
        /*FIX: this scenario is not handle. */
        else if (ln->activityState == LINK_ACTIVITY_WAIT_1 && optionA)
        {
            /* mark T32 stopped */
            ln->t32 = TIMER_BAD_SERIAL;

        }
        break;

    case SLM_TRIGGER_T33:
        if (ln->activityState == LINK_ACTIVITY_INACTIVE &&
            optionB)
        {
            /* mark T33 stopped */
            ln->t33 = TIMER_BAD_SERIAL;
        }
        break;

    case SLM_TRIGGER_T34:
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING &&
            optionB)
        {
            LSLR_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_RESTART_RESTORATION,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_L2_IN_SERVICE:          /* from L2 */

        MTP3_Alarm_CCITT(2527, __FILE__, __LINE__,NULL); 

        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            ln->activityState = LINK_ACTIVITY_ACTIVE;

            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_IN_SERVICE);
            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_IN_SERVICE);


            if (optionB)
            {
                /* start T33 */
                tc.timerId = MTP3_T33;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t33 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t33 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }

            ln->isUp = ITS_TRUE;

            /* stop T19 */
            TIMERS_CancelSharedTimer(ln->t19);
            ln->t19 = TIMER_BAD_SERIAL;

            /*
             * I believe this belongs in SLT.
             */
#if 0
            TLAC_Main_CCITT(MTP3_SLM_LSAC,
                           STM_TRIGGER_LINK_IN_SERVICE,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_ACTIVE,
                           NULL, 0,
                           linkSet, linkCode);
#endif

           MTP3_Alarm_CCITT(2528, __FILE__, __LINE__,
                            "linkset:linkcode %x:%x", linkSet,linkCode);

            /* start the link test */
            SLTC_Main_CCITT(MTP3_SLM_LSAC,
                           SLT_TRIGGER_START_TEST,
                           NULL, 0,
                           linkSet, linkCode);

            ln->slFlags &= ~(LINK_FIRST_FAILURE|
                             LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL);
        }
        break;

    case SLM_TRIGGER_L2_RPO:                 /* from L2 */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            ln->activityState = LINK_ACTIVITY_ACTIVE;

            TLAC_Main_CCITT(MTP3_SLM_LSAC,
                           STM_TRIGGER_RP_OUTAGE,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_ACTIVE,
                           NULL, 0,
                           linkSet, linkCode);

            ln->slFlags &= ~(LINK_FIRST_FAILURE|
                             LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL);
        }
        else if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            TLAC_Main_CCITT(MTP3_SLM_LSAC,
                           STM_TRIGGER_RP_OUTAGE,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_L2_OUT_OF_SERVICE:      /* from L2 */
        MTP3_Alarm_CCITT(2509, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                         linkSet, linkCode);

        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            ln->testPassed = ITS_FALSE;

            if (ln->slFlags & LINK_FIRST_FAILURE)
            {
                /* terminal available to LSTA */
                LSTA_Main_CCITT(MTP3_SLM_LSAC,
                               SLM_TRIGGER_TERMINAL_AVAILABLE,
                               NULL, 0,
                               linkSet, linkCode);

                ln->slFlags &= ~LINK_FIRST_FAILURE;
            }
            else
            {
                ln->slFlags |= LINK_FIRST_FAILURE;
            }

            if (ln->slFlags & LINK_IS_ACTIVATING)
            {
                LSLA_Main_CCITT(MTP3_SLM_LSAC,
                               SLM_TRIGGER_RESTART_ACTIVATION,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLR_Main_CCITT(MTP3_SLM_LSAC,
                               SLM_TRIGGER_RESTART_RESTORATION,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        else if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {

            MTP3_TimerContext tc;

            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_OUT_OF_SERVICE);
            PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_OUT_OF_SERVICE);

            ln->testPassed = ITS_FALSE;

#if !MTP2_RETRIEVAL_IN_PARALLEL
            ln->activityState = LINK_ACTIVITY_FAILED;
#endif

            ln->slFlags |= LINK_FIRST_FAILURE;

            /* start T19 */
            tc.timerId = MTP3_T19;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t19 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t19 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

            TLAC_Main_CCITT(MTP3_SLM_LSAC,
                           STM_TRIGGER_LINK_FAILED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->isUp = ITS_FALSE;

            LLSC_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_FAILED,
                           NULL, 0,
                           linkSet, linkCode);

            /* optional: if retrieval cannot be carried out in parallel
             * with signalling link restoration */
#if MTP2_RETRIEVAL_IN_PARALLEL
            goto STM_Ready;
#endif
        }
        break;

    case SLM_TRIGGER_START_LINK:             /* from LSLA: from LSLR */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            MTP3_TimerContext tc;

            ln->activityState = LINK_ACTIVITY_WAIT_1;

            /* start T17 */
            tc.timerId = MTP3_T17;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            MTP3_DEBUG(("T17 started for %d:%d\n", linkSet, linkCode));

            MTP3_Alarm_CCITT(2505, __FILE__, __LINE__,
                           "Alignment started for %x:%x", linkSet, linkCode);
 
            
            ln->t17 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t17 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
        }
        break;

    case SLM_TRIGGER_T17:
        if (ln->activityState == LINK_ACTIVITY_WAIT_1)
        {
            ln->activityState = LINK_ACTIVITY_ACTIVATING_RESTORING;

            if (ln->slFlags & LINK_EMERGENCY)
            {
                MTP2_SendData_CCITT(linkSet, linkCode,
                                   L3_L2_EMERGENCY, NULL, 0);
            }

            MTP3_Alarm_CCITT(2506, __FILE__, __LINE__,
                           "T17 Expired for linkset:linkcode %x:%x", linkSet, linkCode);


            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_START, NULL, 0);

        }
        break;

    case SLM_TRIGGER_ACTIVATION_UNSUCCESS:   /* from LSLA */
    case SLM_TRIGGER_RESTORATION_UNSUCCESS:  /* from LSLR */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            if (!(ln->slFlags & LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL))
            {
                ln->slFlags |= LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL;

                LLSC_Main_CCITT(MTP3_SLM_LSAC,
                               SLM_TRIGGER_ACTIVATE_ANOTHER_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        break;

    case SLM_TRIGGER_T19:                    /* from timer control */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            MGMT_Main_CCITT(MTP3_SLM_LSAC,
                           MGMT_TRIGGER_LINK_ACTIVATION_FAIL,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_ACTIVATE_ANOTHER_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_NOT_POSSIBLE:           /* from LSLA */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            ln->activityState = LINK_ACTIVITY_INACTIVE;
        }
        break;

    case SLM_TRIGGER_DEACTIVATE_LINK:        /* from LLSC: from LSLA: from MGMT */
       /*  FIX:  ln->testPassed must be set to false.
        *  this fix solve the problem of deactivating and 
        *  reactivating a link from our stack
        */
        ln->testPassed = ITS_FALSE;

        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_DEACTIVATION); 
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_DEACTIVATION);

        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            ln->activityState = LINK_ACTIVITY_INACTIVE;

            MTP2_SendData_CCITT(linkSet, linkCode, L3_L2_STOP, NULL, 0);

            LSLD_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_DEACTIVATE_LINK,
                           NULL, 0,
                           linkSet, linkCode);

            LSLA_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_DEACTIVATE_LINK,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_INACTIVE,
                           NULL, 0,
                           linkSet, linkCode);

            if (ln->slFlags & LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL)
            {
                ln->slFlags &= ~LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL;
            }
            else
            {
                LLSC_Main_CCITT(MTP3_SLM_LSAC,
                               SLM_TRIGGER_ACTIVATE_ANOTHER_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        else if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            if (src == MTP3_MGMT)
            {
                LLSC_Main_CCITT(MTP3_SLM_LSAC,
                               SLM_TRIGGER_ACTIVATE_ANOTHER_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }

            MTP2_SendData_CCITT(linkSet, linkCode, L3_L2_STOP, NULL, 0);

            TLAC_Main_CCITT(MTP3_SLM_LSAC,
                           STM_TRIGGER_LINK_FAILED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->isUp = ITS_FALSE;

            if (ln->slFlags & LINK_LOADED)
            {
               ln->activityState = LINK_ACTIVITY_WAIT_4;
            }
            else
            {
                LLSC_Main_CCITT(MTP3_SLM_LSAC,
                               SLM_TRIGGER_LINK_FAILED,
                               NULL, 0,
                               linkSet, linkCode);

                LSLD_Main_CCITT(MTP3_SLM_LSAC,
                               SLM_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               linkSet, linkCode);

                LLSC_Main_CCITT(MTP3_SLM_LSAC,
                               SLM_TRIGGER_LINK_INACTIVE,
                               NULL, 0,
                               linkSet, linkCode);

                ln->activityState = LINK_ACTIVITY_INACTIVE;
            }
        }
        break;

    case SLM_TRIGGER_RESUME:                 /* from TLAC */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING ||
            ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP2_SendData_CCITT(linkSet, linkCode, L3_L2_RESUME,
                               NULL, 0);
        }
        break;

    case SLM_TRIGGER_CLEAR_BUFFERS:          /* from TLAC */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING ||
            ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP2_SendData_CCITT(linkSet, linkCode, L3_L2_CLEAR_BUFFERS,
                               NULL, 0);
        }
        break;

    case SLM_TRIGGER_STM_READY:
#if MTP2_RETRIEVAL_IN_PARALLEL
STM_Ready:
#else
        if (ln->activityState == LINK_ACTIVITY_FAILED)
#endif
        {
            ln->activityState = LINK_ACTIVITY_ACTIVATING_RESTORING;

            if (optionA)
            {
                /* if T32 stopped */

                if (ln->t32 == TIMER_BAD_SERIAL)
                {
                    /* start T32 */
                    tc.timerId = MTP3_T32;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = linkCode;

                    ln->t32 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                           __ccitt_t32 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    /* mark link restoring */
                    ln->slFlags |= LINK_IS_RESTORING;

                    /* cancel T32 stopped */

                    LSLR_Main_CCITT(MTP3_SLM_LSAC,
                                   SLM_TRIGGER_START_RESTORATION,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
                else
                {
                    /* cancel link restoring */
                    ln->slFlags &= ~LINK_IS_RESTORING;
                }
            }
            else if (optionB)
            {
                /* if not T33 stopped */
                if (ln->t33 != TIMER_BAD_SERIAL)
                {
                    /* start T34 */
                    tc.timerId = MTP3_T34;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = linkCode;

                    ln->t34 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                           __ccitt_t32 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    /* cancel T33 stopped */
                }
                else
                {
                    LSLR_Main_CCITT(MTP3_SLM_LSAC,
                                   SLM_TRIGGER_START_RESTORATION,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
            }
        }
        break;

    case SLM_TRIGGER_LINK_LOADED:            /* from TSRC */
        if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            ln->slFlags |= LINK_LOADED;
        }
        break;

    case SLM_TRIGGER_LINK_DELOADED:          /* from TSRC */
        ln->slFlags &= ~LINK_LOADED;
        if (ln->activityState == LINK_ACTIVITY_WAIT_4)
        {
            ln->activityState = LINK_ACTIVITY_INACTIVE;

            LLSC_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_FAILED,
                           NULL, 0,
                           linkSet, linkCode);

            LSLD_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_DEACTIVATE_LINK,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_CCITT(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_INACTIVE,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_CHANGEOVER_ORDER:       /* from TLAC */
    case SLM_TRIGGER_CHANGEOVER_ORDER_RECVD:
        if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_STOP, NULL, 0);
        }
        break;

    case SLM_TRIGGER_L2_RPR:                 /* from L2 */
        if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            TLAC_Main_CCITT(MTP3_SLM_LSAC, STM_TRIGGER_RP_RECOVERD,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_RB_CLEARED:
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING ||
            ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            TLAC_Main_CCITT(MTP3_SLM_LSAC,
                           STM_TRIGGER_RB_CLEARED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_RTB_CLEARED:
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING ||
            ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            TLAC_Main_CCITT(MTP3_SLM_LSAC,
                           STM_TRIGGER_RTB_CLEARED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_CLEAR_RTB:              /* from TLAC */
        if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_CLEAR_RTB, NULL, 0);
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
TerminalPredetermined(SS7_LinkPtr ln)
{
    ITS_C_ASSERT(ln != NULL);

    if (MTP3_CCITT_AutomaticTerminalAllocation)
    {
        return (ln->termFixed);
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
DataLinkPredetermined(SS7_LinkPtr ln)
{
    ITS_C_ASSERT(ln != NULL);

    if (MTP3_CCITT_AutomaticDataLinkAllocation)
    {
        return (ln->linkFixed);
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
ReplaceTerminal(SS7_LinkPtr ln)
{
    /*
     * This needs an algorithm.  Unfortunately, without an L2 implementation
     * we can't define one.
     */
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
static ITS_BOOLEAN
ReplaceDataLink(SS7_LinkPtr ln)
{
    /*
     * This needs an algorithm.  Unfortunately, without an L2 implementation
     * we can't define one.
     */
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
int
LSLA_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SLM_LSLA, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

        return (ITS_EINVALIDARGS);
    }

    /* handle trigger */
    switch (trigger)
    {
    case SLM_TRIGGER_START_ACTIVATION:       /* from LSAC */
        if (ln->activationState == LINK_ACTIVATION_IDLE)
        {
            if (TerminalPredetermined(ln))
            {
                MTP2_SendData_CCITT(linkSet, linkCode, L3_L2_CONNECT, NULL, 0);

                LSAC_Main_CCITT(MTP3_SLM_LSLA,
                               SLM_TRIGGER_START_LINK,
                               NULL, 0,
                               linkSet, linkCode);

                ln->slFlags &= ~(LINK_TERMINAL_DETERMINED|
                                 LINK_DATA_LINK_DETERMINED);
            }
            else
            {
                ln->activationState = LINK_ACTIVATION_WAIT_1;

                LSTA_Main_CCITT(MTP3_SLM_LSLA,
                               SLM_TRIGGER_DETERMINE_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);

                if (!DataLinkPredetermined(ln))
                {
                    LSDA_Main_CCITT(MTP3_SLM_LSLA,
                                   SLM_TRIGGER_DETERMINE_DATA_LINK,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
            }
        }
        break;

    case SLM_TRIGGER_RESTART_ACTIVATION:     /* from LSAC */
        if (ln->activationState == LINK_ACTIVATION_IDLE)
        {
            if (ReplaceDataLink(ln))
            {
                ln->activationState = LINK_ACTIVATION_WAIT_2;

                LSDA_Main_CCITT(MTP3_SLM_LSLA,
                               SLM_TRIGGER_DETERMINE_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSAC_Main_CCITT(MTP3_SLM_LSLA,
                               SLM_TRIGGER_ACTIVATION_UNSUCCESS,
                               NULL, 0,
                               linkSet, linkCode);

                LSAC_Main_CCITT(MTP3_SLM_LSLA,
                               SLM_TRIGGER_START_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        break;

    case SLM_TRIGGER_DATA_LINK:              /* from LSDA */
        if (ln->activationState == LINK_ACTIVATION_WAIT_1)
        {
            ln->slFlags |= LINK_DATA_LINK_DETERMINED;

            if (ln->slFlags & LINK_TERMINAL_DETERMINED)
            {
                ln->activationState = LINK_ACTIVATION_IDLE;

                MTP2_SendData_CCITT(linkSet, linkCode,
                                   L3_L2_CONNECT, NULL, 0);

                LSAC_Main_CCITT(MTP3_SLM_LSLA,
                               SLM_TRIGGER_START_LINK,
                               NULL, 0,
                               linkSet, linkCode);

                ln->slFlags &= ~(LINK_TERMINAL_DETERMINED|
                               LINK_DATA_LINK_DETERMINED);
            }
        }

        if (ln->activationState == LINK_ACTIVATION_WAIT_2)
        {
            ln->activationState = LINK_ACTIVATION_IDLE;

            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_CONNECT, NULL, 0);

            LSAC_Main_CCITT(MTP3_SLM_LSLA,
                           SLM_TRIGGER_START_LINK,
                           NULL, 0,
                           linkSet, linkCode);

            ln->slFlags &= ~(LINK_TERMINAL_DETERMINED|
                           LINK_DATA_LINK_DETERMINED);
        }
        break;

    case SLM_TRIGGER_NO_DATA_LINK:           /* from LSDA */
        if (ln->activationState == LINK_ACTIVATION_WAIT_1)
        {
            ln->activationState = LINK_ACTIVATION_IDLE;

            LSAC_Main_CCITT(MTP3_SLM_LSLA,
                           SLM_TRIGGER_NOT_POSSIBLE,
                           NULL, 0,
                           linkSet, linkCode);

            ln->slFlags &= ~(LINK_TERMINAL_DETERMINED|
                           LINK_DATA_LINK_DETERMINED);
        }
        else if (ln->activationState == LINK_ACTIVATION_WAIT_2)
        {
            ln->activationState = LINK_ACTIVATION_IDLE;

            LSAC_Main_CCITT(MTP3_SLM_LSLA,
                           SLM_TRIGGER_ACTIVATION_UNSUCCESS,
                           NULL, 0,
                           linkSet, linkCode);

            LSAC_Main_CCITT(MTP3_SLM_LSLA,
                           SLM_TRIGGER_START_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_DEACTIVATE_LINK:        /* from LSAC */
        if (ln->activationState == LINK_ACTIVATION_WAIT_1)
        {
            ln->slFlags &= ~(LINK_TERMINAL_DETERMINED|
                           LINK_DATA_LINK_DETERMINED);
        }

        ln->activationState = LINK_ACTIVATION_IDLE;
        break;

    case SLM_TRIGGER_TERMINAL:               /* from LSTA */
        if (ln->activationState == LINK_ACTIVATION_WAIT_1)
        {
            ln->slFlags |= LINK_TERMINAL_DETERMINED;

            if (ln->slFlags & LINK_DATA_LINK_DETERMINED)
            {
                ln->activationState = LINK_ACTIVATION_IDLE;

                MTP2_SendData_CCITT(linkSet, linkCode,
                                   L3_L2_CONNECT, NULL, 0);

                LSAC_Main_CCITT(MTP3_SLM_LSLA,
                               SLM_TRIGGER_START_LINK,
                               NULL, 0,
                               linkSet, linkCode);

                ln->slFlags &= ~(LINK_TERMINAL_DETERMINED|
                               LINK_DATA_LINK_DETERMINED);
            }
        }
        break;

    case SLM_TRIGGER_NO_TERMINAL:            /* from LSTA */
        if (ln->activationState == LINK_ACTIVATION_WAIT_1)
        {
            ln->activationState = LINK_ACTIVATION_IDLE;

            LSAC_Main_CCITT(MTP3_SLM_LSLA,
                           SLM_TRIGGER_NOT_POSSIBLE,
                           NULL, 0,
                           linkSet, linkCode);

            ln->slFlags &= ~(LINK_TERMINAL_DETERMINED|
                           LINK_DATA_LINK_DETERMINED);
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
LSLR_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SLM_LSLR, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

        return (ITS_EINVALIDARGS);
    }

    switch (trigger)
    {
    case SLM_TRIGGER_START_RESTORATION:      /* from LSAC */
        if (ln->restorationState == LINK_RESTORATION_IDLE)
        {
            LSAC_Main_CCITT(MTP3_SLM_LSLR,
                           SLM_TRIGGER_START_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_RESTART_RESTORATION:    /* from LSAC */
        if (ln->restorationState == LINK_RESTORATION_IDLE)
        {
            if (ReplaceTerminal(ln))
            {
                ln->restorationState = LINK_RESTORATION_WAIT_2;

                LSTA_Main_CCITT(MTP3_SLM_LSLR,
                               SLM_TRIGGER_DETERMINE_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else if (ReplaceDataLink(ln))
            {
                ln->restorationState = LINK_RESTORATION_WAIT_1;

                LSDA_Main_CCITT(MTP3_SLM_LSLR,
                               SLM_TRIGGER_DETERMINE_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSAC_Main_CCITT(MTP3_SLM_LSLR,
                               SLM_TRIGGER_RESTORATION_UNSUCCESS,
                               NULL, 0,
                               linkSet, linkCode);

                LSAC_Main_CCITT(MTP3_SLM_LSLR,
                               SLM_TRIGGER_START_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        break;

    case SLM_TRIGGER_TERMINAL:               /* from LSTA */
        if (ln->restorationState == LINK_RESTORATION_WAIT_2)
        {
            ln->restorationState = LINK_RESTORATION_IDLE;

            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_CONNECT, NULL, 0);

            LSAC_Main_CCITT(MTP3_SLM_LSLA,
                           SLM_TRIGGER_START_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_NO_TERMINAL:            /* from LSTA */
        if (ln->restorationState == LINK_RESTORATION_WAIT_2)
        {
            ln->restorationState = LINK_RESTORATION_IDLE;

            LSAC_Main_CCITT(MTP3_SLM_LSLR,
                           SLM_TRIGGER_RESTORATION_UNSUCCESS,
                           NULL, 0,
                           linkSet, linkCode);

            LSAC_Main_CCITT(MTP3_SLM_LSLR,
                           SLM_TRIGGER_START_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_DATA_LINK:              /* from LSDA */
        if (ln->restorationState == LINK_RESTORATION_WAIT_1)
        {
            ln->restorationState = LINK_RESTORATION_IDLE;

            MTP2_SendData_CCITT(linkSet, linkCode,
                               L3_L2_CONNECT, NULL, 0);

            LSAC_Main_CCITT(MTP3_SLM_LSLA,
                           SLM_TRIGGER_START_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_NO_DATA_LINK:           /* from LSDA */
        if (ln->restorationState == LINK_RESTORATION_WAIT_1)
        {
            ln->restorationState = LINK_RESTORATION_IDLE;

            LSAC_Main_CCITT(MTP3_SLM_LSLR,
                           SLM_TRIGGER_RESTORATION_UNSUCCESS,
                           NULL, 0,
                           linkSet, linkCode);

            LSAC_Main_CCITT(MTP3_SLM_LSLR,
                           SLM_TRIGGER_START_LINK,
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
LSLD_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_TRACE_ENTRY_CCITT(MTP3_SLM_LSLD, src, trigger, sif, len,
                           linkSet, linkCode);

    switch (trigger)
    {
    case SLM_TRIGGER_DEACTIVATE_LINK:      /* from LSAC */

        MTP2_SendData_CCITT(linkSet, linkCode, L3_L2_DISCONNECT, NULL, 0);

        MTP3_Alarm_CCITT(2509, __FILE__, __LINE__, "linkset:linkcode %x:%x",
                        linkSet, linkCode);

        LSDA_Main_CCITT(MTP3_SLM_LSLD,
                       SLM_TRIGGER_LINK_AVAILABLE,
                       NULL, 0,
                       linkSet, linkCode);

        LSTA_Main_CCITT(MTP3_SLM_LSLD,
                       SLM_TRIGGER_TERMINAL_IDLE,
                       NULL, 0,
                       linkSet, linkCode);
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
static ITS_BOOLEAN
AnyTerminalsIdle(SS7_LinkSetPtr ls)
{
    ITS_UINT i;

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->slFlags & LINK_TERMINAL_IDLE)
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
AnyTerminalsAvailable(SS7_LinkSetPtr ls)
{
    ITS_UINT i;

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->slFlags & LINK_TERMINAL_AVAILABLE)
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
static int
SelectNextTerminal(SS7_LinkSetPtr ls, SS7_LinkPtr *ln)
{
    ITS_UINT i;

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i] != *ln &&
            ls->links[i]->slFlags & (LINK_TERMINAL_IDLE |
                                     LINK_TERMINAL_AVAILABLE))
        {
            *ln = ls->links[i];

            return (ITS_SUCCESS);
        }
    }

    return (ITS_ENOTFOUND);
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
LSTA_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SLM_LSTA, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Link set %d not found\n", linkSet));
     
        return (ITS_EINVALIDARGS);
    }

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

        return (ITS_EINVALIDARGS);
    }

    switch (trigger)
    {
    case SLM_TRIGGER_DETERMINE_TERMINAL:     /* from LSLA: from LSLR */
        if (ln->terminalState != TERMINAL_ALLOCATION_IDLE)
        {
            MTP3_Alarm_CCITT(2434, __FILE__, __LINE__, "link is %x:%x",linkSet, linkCode);
            break;
        }

        if (src == MTP3_SLM_LSLA)
        {
            ln->slFlags |= LINK_IS_ACTIVATING;
        }
        else if (src == MTP3_SLM_LSLR)
        {
            ln->slFlags &= ~LINK_IS_ACTIVATING;
        }
        
        if (AnyTerminalsIdle(ls))
        {
            SelectNextTerminal(ls, &ln);

            if (ln->slFlags & LINK_IS_ACTIVATING)
            {
                LSLA_Main_CCITT(MTP3_SLM_LSTA,
                               SLM_TRIGGER_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLR_Main_CCITT(MTP3_SLM_LSTA,
                               SLM_TRIGGER_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }

            ln->slFlags &= ~LINK_IS_ACTIVATING;
        }
        else if (AnyTerminalsAvailable(ls))
        {
            SelectNextTerminal(ls, &ln);

            LSLD_Main_CCITT(MTP3_SLM_LSTA,
                           SLM_TRIGGER_DEACTIVATE_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        else
        {
            if (ln->slFlags & LINK_IS_ACTIVATING)
            {
                LSLA_Main_CCITT(MTP3_SLM_LSTA,
                               SLM_TRIGGER_NO_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLR_Main_CCITT(MTP3_SLM_LSTA,
                               SLM_TRIGGER_NO_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }

            ln->slFlags &= ~LINK_IS_ACTIVATING;
        }
        break;

    case SLM_TRIGGER_TERMINAL_IDLE:          /* from LSLD */
        if (ln->terminalState == TERMINAL_ALLOCATION_IDLE)
        {
            ln->slFlags |= LINK_TERMINAL_IDLE;
        }
        else
        {
            ln->terminalState = TERMINAL_ALLOCATION_IDLE;

            if (ln->slFlags & LINK_IS_ACTIVATING)
            {
                LSLA_Main_CCITT(MTP3_SLM_LSTA,
                               SLM_TRIGGER_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLR_Main_CCITT(MTP3_SLM_LSTA,
                               SLM_TRIGGER_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }

            ln->slFlags &= ~LINK_IS_ACTIVATING;
        }
        break;

    case SLM_TRIGGER_TERMINAL_AVAILABLE:     /* from LSAC */
        ln->slFlags |= LINK_TERMINAL_AVAILABLE;
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
static ITS_BOOLEAN
AnotherDataLinkAvailable(SS7_LinkSetPtr ls, SS7_LinkPtr ln)
{
    ITS_UINT i;

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->slFlags & LINK_IS_AVAILABLE &&
            ls->links[i] != ln)
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
int
LSDA_Main_CCITT(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER omtp3, *mtp3, *lmtp3;
    SNMM_MESSAGE snmm, *isnmm;
    ITS_EVENT ev;
    ITS_OCTET ni, ols, oln;
    ITS_UINT pc1, pc2;
    SS7_LinkSetPtr ls, nls;
    SS7_LinkPtr ln, nln;
    int ret;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SLM_LSDA, src, trigger, sif, len,
                           linkSet, linkCode);

    switch (trigger)
    {
    case SLM_TRIGGER_DETERMINE_DATA_LINK:    /* from LSLA: from LSLR */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Link set %d not found\n", linkSet));
 
            return (ITS_EINVALIDARGS);
        }

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->allocationState != LINK_ALLOCATION_IDLE)
        {
            MTP3_Alarm_CCITT(2439, __FILE__, __LINE__, "link is %x:%x",linkSet, linkCode); 

            break;
        }

        if (src == MTP3_SLM_LSLA)
        {
            ln->slFlags |= LINK_IS_ACTIVATING;
        }
        else if (src == MTP3_SLM_LSLR)
        {
            ln->slFlags &= ~LINK_IS_ACTIVATING;
        }

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        MTP3_HDR_SET_SIO(omtp3, ls->ni);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

        MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                    &omtp3, NULL, 0);

        ln->allocationState = LINK_ALLOCATION_WAIT_2;

        TSRC_Main_CCITT(MTP3_SLM_LSDA, STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                       ev.data, ev.len,
                       linkSet, linkCode);

        ITS_EVENT_TERM(&ev);
        break;

    case SLM_TRIGGER_LINK_AVAILABLE:         /* from LSLD */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Link set %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if (ln->allocationState == LINK_ALLOCATION_IDLE ||
            ln->allocationState == LINK_ALLOCATION_WAIT_2 ||
            ln->allocationState == LINK_ALLOCATION_WAIT_3)
        {
            ln->slFlags |= LINK_IS_AVAILABLE;
        }
        break;

    case SLM_TRIGGER_CONNECTION_ORDER:       /* from HMDT */
        /* sanitize the linkSet */
        mtp3 = (MTP3_HEADER *)&sif[1];
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                     sizeof(ITS_OCTET)];

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));
            
            MTP3_Alarm_CCITT(2440, __FILE__, __LINE__, NULL);

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Link set %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for DLC Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_RX);

        if (ln->allocationState == LINK_ALLOCATION_IDLE)
        {
            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            MTP3_HDR_SET_SIO(omtp3, ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            ln->allocationState = LINK_ALLOCATION_WAIT_3;

            TSRC_Main_CCITT(MTP3_SLM_LSDA, STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           ev.data, ev.len,
                           linkSet, linkCode);

            ITS_EVENT_TERM(&ev);
        }
        else if (ln->allocationState == LINK_ALLOCATION_WAIT_1)
        {
            mtp3 = (MTP3_HEADER *)&sif[1];

            /* determine who is controlling */
            pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

            /* local SP controlling? */
            if (pc1 > pc2)
            {
                /* stop T7 */
                TIMERS_CancelSharedTimer(ln->t7);
                ln->t7 = TIMER_BAD_SERIAL;

                if (ln->slFlags & LINK_IS_AVAILABLE)
                {
                    /* build CSS, send */
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                    MTP3_RL_SET_SLS(omtp3.label, linkCode);

                    SNMM_HC0_SET(snmm, SNMM_HC0_DLM);
                    SNMM_HC1_SET(snmm, SNMM_HC1_CSS);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                    SNMM_Encode(&ev, &omtp3, &snmm);

                    /* Increament Link Peg for CSS Trasmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_TX);

                    ret = HMRT_Main_CCITT(MTP3_SLM_LSDA,
                                         SMH_TRIGGER_LINK_MGMT_MSG,
                                         ev.data, ev.len,
                                         linkSet, linkCode);
                    ITS_EVENT_TERM(&ev);

                    ln->allocationState = LINK_ALLOCATION_IDLE;

                    if (ln->slFlags & LINK_IS_ACTIVATING)
                    {
                        LSLA_Main_CCITT(MTP3_SLM_LSDA,
                                       SLM_TRIGGER_DATA_LINK,
                                       NULL, 0,
                                       linkSet, linkCode);
                    }
                    else
                    {
                        LSLR_Main_CCITT(MTP3_SLM_LSDA,
                                       SLM_TRIGGER_DATA_LINK,
                                       NULL, 0,
                                       linkSet, linkCode);
                    }
                }
                else if (AnotherDataLinkAvailable(ls, ln))
                {
                    /* build CNS, send */
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                    MTP3_RL_SET_SLS(omtp3.label, linkCode);

                    SNMM_HC0_SET(snmm, SNMM_HC0_DLM);
                    SNMM_HC1_SET(snmm, SNMM_HC1_CNS);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                    SNMM_Encode(&ev, &omtp3, &snmm);

                    /* Increament Link Peg for CNS Transmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_TX);

                    ret = HMRT_Main_CCITT(MTP3_SLM_LSDA,
                                         SMH_TRIGGER_LINK_MGMT_MSG,
                                         ev.data, ev.len,
                                         linkSet, linkCode);
                    ITS_EVENT_TERM(&ev);
                }
                else
                {
                    /* build CNP, send */
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                    MTP3_RL_SET_SLS(omtp3.label, linkCode);

                    SNMM_HC0_SET(snmm, SNMM_HC0_DLM);
                    SNMM_HC1_SET(snmm, SNMM_HC1_CNP);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                    SNMM_Encode(&ev, &omtp3, &snmm);

                    /* Increament Link Peg for CNP Transmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_TX);

                    ret = HMRT_Main_CCITT(MTP3_SLM_LSDA,
                                         SMH_TRIGGER_LINK_MGMT_MSG,
                                         ev.data, ev.len,
                                         linkSet, linkCode);
                    ITS_EVENT_TERM(&ev);

                    ln->allocationState = LINK_ALLOCATION_IDLE;

                    if (ln->slFlags & LINK_IS_ACTIVATING)
                    {
                        LSLA_Main_CCITT(MTP3_SLM_LSDA,
                                       SLM_TRIGGER_NO_DATA_LINK,
                                       NULL, 0,
                                       linkSet, linkCode);
                    }
                    else
                    {
                        LSLA_Main_CCITT(MTP3_SLM_LSDA,
                                       SLM_TRIGGER_NO_DATA_LINK,
                                       NULL, 0,
                                       linkSet, linkCode);
                    }

                    ln->slFlags &= ~LINK_IS_ACTIVATING;
                }
            }
        }
        break;

    case SLM_TRIGGER_ALTERNATE_ROUTING_DATA: /* from TSRC */
        lmtp3 = (MTP3_HEADER *)&sif[sizeof(MTP3_HEADER) +
                                    sizeof(ITS_OCTET)];
        ols = sif[2 * sizeof(MTP3_HEADER) + sizeof(ITS_OCTET)];
        oln = sif[2 * sizeof(MTP3_HEADER) + 2 * sizeof(ITS_OCTET)];

        if ((ls = LINKSET_FindLinkSet(ols)) == NULL)
        {
            MTP3_ERROR(("Link set %d not found\n", linkSet));
 
            return (ITS_EINVALIDARGS);
        }

        if ((ln = LINK_FindLink(ols, oln)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        if ((nls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Link set %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if ((nln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));
 
            return (ITS_EINVALIDARGS);
        }

        if (ln->allocationState == LINK_ALLOCATION_WAIT_2)
        {
            if (nln->slFlags & LINK_IS_AVAILABLE)
            {
                MTP3_TimerContext tc;

                /* build DLC, send */
                MTP3_RL_SET_DPC_VALUE(omtp3.label, nls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, nls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_DLM);
                SNMM_HC1_SET(snmm, SNMM_HC1_DLC);
                SNMM_DATALINK_CONNECT_SET_LINK(snmm.data.datalinkConnect,
                                               nln->dataLink);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for DLC Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);

                ret = HMRT_Main_CCITT(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                /* Start T7 */
                tc.timerId = MTP3_T7;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                nln->t7 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t7 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                nln->allocationState = LINK_ALLOCATION_WAIT_1;
            }
            else
            {
                nln->allocationState = LINK_ALLOCATION_IDLE;

                if (nln->slFlags & LINK_IS_ACTIVATING)
                {
                    LSLA_Main_CCITT(MTP3_SLM_LSDA,
                                   SLM_TRIGGER_NO_DATA_LINK,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
                else
                {
                    LSLA_Main_CCITT(MTP3_SLM_LSDA,
                                   SLM_TRIGGER_NO_DATA_LINK,
                                   NULL, 0,
                                   linkSet, linkCode);
                }

                nln->slFlags &= ~LINK_IS_ACTIVATING;
            }
        }
        else if (ln->allocationState == LINK_ALLOCATION_WAIT_3)
        {
            ln->allocationState = LINK_ALLOCATION_IDLE;

            if (nln->slFlags & LINK_IS_AVAILABLE)
            {
                LSAC_Main_CCITT(MTP3_SLM_LSDA,
                               SLM_TRIGGER_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);

                /* build CSS, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | nls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, nls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, nls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_DLM);
                SNMM_HC1_SET(snmm, SNMM_HC1_CSS);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for CSS Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_TX);

                ret = HMRT_Main_CCITT(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);
            }
            else if (AnotherDataLinkAvailable(ls, ln))
            {
                /* build CNS, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_DLM);
                SNMM_HC1_SET(snmm, SNMM_HC1_CNS);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for CNS Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_TX);

                ret = HMRT_Main_CCITT(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);
            }
            else
            {
                /* build CNP, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_DLM);
                SNMM_HC1_SET(snmm, SNMM_HC1_CNP);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for CNP Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_TX);

                ret = HMRT_Main_CCITT(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);
            }
        }
        break;

    case SLM_TRIGGER_CONNECTION_SUCCESSFUL:  /* from HMDT */
        /* sanitize the linkSet */
        mtp3 = (MTP3_HEADER *)&sif[1];
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                     sizeof(ITS_OCTET)];

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            MTP3_Alarm_CCITT(2440, __FILE__, __LINE__, NULL);

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Link set %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for CSS Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_RX);

        if (ln->allocationState == LINK_ALLOCATION_WAIT_1)
        {
            /* stop T7 */
            TIMERS_CancelSharedTimer(ln->t7);
            ln->t7 = TIMER_BAD_SERIAL;

            ln->allocationState = LINK_ALLOCATION_IDLE;

            if (ln->slFlags & LINK_IS_ACTIVATING)
            {
                LSLA_Main_CCITT(MTP3_SLM_LSDA,
                               SLM_TRIGGER_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLR_Main_CCITT(MTP3_SLM_LSDA,
                               SLM_TRIGGER_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        break;

    case SLM_TRIGGER_CONNECTION_UNSUCCESS:   /* from HMDT */
        /* sanitize the linkSet */
        mtp3 = (MTP3_HEADER *)&sif[1];
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                     sizeof(ITS_OCTET)];

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            MTP3_Alarm_CCITT(2440, __FILE__, __LINE__, NULL);

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Link set %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for CNS Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_RX);

        if (ln->allocationState == LINK_ALLOCATION_WAIT_1)
        {
            /* stop T7 */
            TIMERS_CancelSharedTimer(ln->t7);
            ln->t7 = TIMER_BAD_SERIAL;

            if (ln->slFlags & LINK_IS_AVAILABLE)
            {
                MTP3_TimerContext tc;

                /* SelectDataLink(&linkSet, &linkCode); */

                /* build DLC, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_DLM);
                SNMM_HC1_SET(snmm, SNMM_HC1_DLC);
                SNMM_DATALINK_CONNECT_SET_LINK(snmm.data.datalinkConnect,
                                               ln->dataLink);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for DLC Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);

                ret = HMRT_Main_CCITT(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                /* Start T7 */
                tc.timerId = MTP3_T7;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t7 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t7 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                ln->allocationState = LINK_ALLOCATION_WAIT_1;
            }
            else
            {
                ln->allocationState = LINK_ALLOCATION_IDLE;

                if (ln->slFlags & LINK_IS_ACTIVATING)
                {
                    LSLA_Main_CCITT(MTP3_SLM_LSDA,
                                   SLM_TRIGGER_NO_DATA_LINK,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
                else
                {
                    LSLA_Main_CCITT(MTP3_SLM_LSDA,
                                   SLM_TRIGGER_NO_DATA_LINK,
                                   NULL, 0,
                                   linkSet, linkCode);
                }

                ln->slFlags &= ~LINK_IS_ACTIVATING;
            }
        }
        break;

    case SLM_TRIGGER_CONNECTION_NOT_POSS:    /* from HMDT */
        /* sanitize the linkSet */
        mtp3 = (MTP3_HEADER *)&sif[1];
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                     sizeof(ITS_OCTET)];

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        linkSet = MTP3_FindAdjacent_CCITT(ni, pc1, linkSet);
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            MTP3_Alarm_CCITT(2440, __FILE__, __LINE__, NULL);

            return (ITS_EINVALIDARGS);
        }

        linkCode = MTP3_RL_GET_SLS(mtp3->label);

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Link set %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            return (ITS_EINVALIDARGS);
        }

        /* Increament Link Peg for CNP Received */
        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_RX);

        if (ln->allocationState == LINK_ALLOCATION_WAIT_1)
        {
            /* stop T7 */
            TIMERS_CancelSharedTimer(ln->t7);
            ln->t7 = TIMER_BAD_SERIAL;

            ln->allocationState = LINK_ALLOCATION_IDLE;

            if (ln->slFlags & LINK_IS_ACTIVATING)
            {
                LSLA_Main_CCITT(MTP3_SLM_LSDA,
                               SLM_TRIGGER_NO_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLA_Main_CCITT(MTP3_SLM_LSDA,
                               SLM_TRIGGER_NO_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }

            ln->slFlags &= ~LINK_IS_ACTIVATING;
        }
        break;

    case SLM_TRIGGER_T7:                     /* from timer control */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Link set %d not found\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));

            

            return (ITS_EINVALIDARGS);
        }

        if (ln->allocationState == LINK_ALLOCATION_WAIT_1)
        {
            /* another link available? */
            if (AnotherDataLinkAvailable(ls, ln))
            {
                if (ln->slFlags & LINK_IS_AVAILABLE)
                {
                    MTP3_TimerContext tc;

                    /* build DLC, send */
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                    MTP3_RL_SET_SLS(omtp3.label, ln->linkCode);

                    SNMM_HC0_SET(snmm, SNMM_HC0_DLM);
                    SNMM_HC1_SET(snmm, SNMM_HC1_DLC);
                    SNMM_DATALINK_CONNECT_SET_LINK(snmm.data.datalinkConnect,
                                                   ln->dataLink);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                    SNMM_Encode(&ev, &omtp3, &snmm);

                    /* Increament Link Peg for DLC Transmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);

                    ret = HMRT_Main_CCITT(MTP3_SLM_LSDA,
                                         SMH_TRIGGER_LINK_MGMT_MSG,
                                         ev.data, ev.len,
                                         linkSet, linkCode);
                    ITS_EVENT_TERM(&ev);

                    /* Start T7 */
                    tc.timerId = MTP3_T7;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = linkCode;

                    ln->t7 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                           __ccitt_t7 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    ln->allocationState = LINK_ALLOCATION_WAIT_1;
                }
                else
                {
                    ln->allocationState = LINK_ALLOCATION_IDLE;

                    if (ln->slFlags & LINK_IS_ACTIVATING)
                    {
                        LSLA_Main_CCITT(MTP3_SLM_LSDA,
                                       SLM_TRIGGER_NO_DATA_LINK,
                                       NULL, 0,
                                       linkSet, linkCode);
                    }
                    else
                    {
                        LSLA_Main_CCITT(MTP3_SLM_LSDA,
                                       SLM_TRIGGER_NO_DATA_LINK,
                                       NULL, 0,
                                       linkSet, linkCode);
                    }

                    ln->slFlags &= ~LINK_IS_ACTIVATING;
                }
            }
            else
            {
                MTP3_TimerContext tc;

                /* build DLC, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
                MTP3_RL_SET_SLS(omtp3.label, linkCode);

                SNMM_HC0_SET(snmm, SNMM_HC0_DLM);
                SNMM_HC1_SET(snmm, SNMM_HC1_DLC);
                SNMM_DATALINK_CONNECT_SET_LINK(snmm.data.datalinkConnect,
                                               ln->dataLink);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                /* Increament Link Peg for DLC Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);

                ret = HMRT_Main_CCITT(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                /* Start T7 */
                tc.timerId = MTP3_T7;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t7 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t7 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                ln->allocationState = LINK_ALLOCATION_WAIT_1;
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
