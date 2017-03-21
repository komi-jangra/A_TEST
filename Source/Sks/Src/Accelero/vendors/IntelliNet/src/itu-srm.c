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
 *  ID: $Id: itu-srm.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:34  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:09  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.5  2005/05/17 06:09:22  adutta
 * LOG: Fixed issue#1839
 * LOG:
 * LOG: Revision 9.4  2005/05/12 12:00:18  adutta
 * LOG: Fixed issue #1833
 * LOG:
 * LOG: Revision 9.3  2005/05/10 06:43:12  adutta
 * LOG: Null checks for route pegs
 * LOG:
 * LOG: Revision 9.2  2005/05/06 06:21:35  adutta
 * LOG: MTP Route peg declaration
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:43  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:53:50  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.2.2.1.8.2  2005/01/05 12:50:27  sbabu
 * LOG:  Removed unwanted alarms
 * LOG:
 * LOG: Revision 7.4.2.2.2.1.8.1  2004/12/31 07:32:33  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.4.2.2.2.1  2004/08/10 12:14:46  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.4.2.2  2003/12/12 11:49:39  kannanp
 * LOG: Fix bug 602 RST message is not sent for every T10 expiry.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/11/28 07:50:11  kannanp
 * LOG: Peg Fix patch from Current.
 * LOG:
 * LOG: Revision 7.4  2003/02/13 10:40:22  ttipatre
 * LOG: Pegs are Modified.
 * LOG:
 * LOG: Revision 7.3  2002/12/24 07:49:55  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.2  2002/11/20 05:21:21  ttipatre
 * LOG: Modified to protocol specific alarms.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/08/16 22:07:09  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.5  2002/07/25 14:21:51  randresol
 * LOG: Fix bugs found during functional testing.
 * LOG:
 * LOG: Revision 6.4  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.3  2002/06/13 20:35:50  ttipatre
 * LOG: Adding MTP3 Pegs and Alarms
 * LOG:
 * LOG: Revision 6.2  2002/05/15 15:06:48  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
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
#if !defined(PRC)
#define CCITT
#endif

#include <its.h>
#include <engine.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_timers.h>
#include <its_route_rwlock.h>
#ident "$Id: itu-srm.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#if defined(PRC)
#include <china/snmm.h>
#include <china/sltm.h>
#include <china/mtp3.h>
#else
#include <itu/snmm.h>
#include <itu/sltm.h>
#include <itu/mtp3.h>
#endif

#include "mtp3_intern.h"
extern ITS_USHORT linkTransportMapDB[MAX_LINKSETS][MAX_LINKS_PER_LINKSET];
/*   TIMERS_CancelSharedTimer is not working so changing it with TIMERS_CancelTimer
     as it is able to remove the timer from local hash too if it is unable to find the
     timer in the DSM*/
#define TIMERS_CancelSharedTimer TIMERS_CancelTimer
#define TIMERS_StartSharedUTimer TIMERS_StartTimer_MSEC

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
SRM_Main_CCITT(MTP3_SubSystems src, MTP3_SubSystems dest,
              SRM_Triggers trigger,
              ITS_OCTET *sif, ITS_USHORT len,
              ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    SNMM_MESSAGE *snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                              sizeof(ITS_OCTET)];

    MTP3_TRACE_ENTRY_CCITT(MTP3_SRM, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }

    if (trigger == SRM_TRIGGER_L2_MSG)
    {
        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_STATUS);
        switch (SNMM_HC0_GET(*snmm))
        {
        case SNMM_HC0_FCM: /* transfer controlled/congestion */
            switch (SNMM_HC1_GET(*snmm))
            {
            case SNMM_HC1_RCT: /* route congestion test */
                return RCAT_Main_CCITT(src, SRM_TRIGGER_CONG_TEST,
                                       sif, len,
                                       linkSet, linkCode);

            case SNMM_HC1_TFC: /* transfer controlled */
                return RTCC_Main_CCITT(src, SRM_TRIGGER_TRANSFER_CONTROL,
                                       sif, len,
                                       linkSet, linkCode);
            default:
                MTP3_DEBUG(("SRM_Main: Invalid code %d for FCM message\n",
                            SNMM_HC1_GET(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_TFM: /* transfer prohibit/allow/restrict */
            switch (SNMM_HC1_GET(*snmm))
            {
            case SNMM_HC1_TFP: /* transfer prohibited */
                return RTPC_Main_CCITT(src,
                                       SRM_TRIGGER_TRANSFER_PROHIBIT,
                                       sif, len,
                                       linkSet, linkCode);

            case SNMM_HC1_TFR: /* transfer restricted */
                return RTRC_Main_CCITT(src,
                                       SRM_TRIGGER_TRANSFER_RESTRICT,
                                       sif, len,
                                       linkSet, linkCode);

            case SNMM_HC1_TFA: /* transfer allowed */
                return RTAC_Main_CCITT(src,
                                       SRM_TRIGGER_TRANSFER_ALLOW,
                                       sif, len,
                                       linkSet, linkCode);

            default:
                MTP3_DEBUG(("SRM_Main: Invalid code %d for TFM message\n",
                            SNMM_HC1_GET(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_RSM: /* route set test */
            switch (SNMM_HC1_GET(*snmm))
            {
            case SNMM_HC1_RSP: /* route set test prohibited */
            case SNMM_HC1_RSR: /* route set test restricted */
                return RSRT_Main_CCITT(src,
                                       SRM_TRIGGER_ROUTE_SET_TEST,
                                       sif, len,
                                       linkSet, linkCode);

            default:
                MTP3_DEBUG(("SRM_Main: Invalid code %d for RSM message\n",
                            SNMM_HC1_GET(*snmm)));
                break;
            }
            break;

        case SNMM_HC0_UFC:
            switch (SNMM_HC1_GET(*snmm))
            {
            case SNMM_HC1_UPU:
                if (ln)
                {
                  /* Increament Link Peg for UPU Received */
                  PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_RX);
                }
                return RTCC_Main_CCITT(src,
                                      SRM_TRIGGER_USER_PART_UNAVAIL,
                                      sif, len,
                                      linkSet, linkCode);
            default:
                MTP3_DEBUG(("SRM_Main: Invalid code %d for UFC message\n",
                            SNMM_HC1_GET(*snmm)));
                break;
            }
            break;

        default:
            MTP3_DEBUG(("SRM_Main: Invalid HC0 code %d\n",
                        SNMM_HC0_GET(*snmm)));
            return (ITS_EINVALIDARGS);
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
 *
 *  Notes:
 * We know these facts:
 *
 * We may receive SNMM messages from non-adjacent points.
 * However, TFP/TCP/TFR/TCR/TFA/TCA are always sent from adjacents, but
 * via any available route.
 * RSP/RSR/RCP/RCR are sent to the adjacent that initiated the prohibit
 * or restricted state.  They are stopped when the correct allow is returned.
 * Again, via any available route.
 * TFC and RCT and  is sent to adjacents and non-adjacents alike.
 * UPU is sent to anybody, and doesn't care about the originating linkSet.
 * DLC/CSS/CNS/CNP are always between adjacents.  However, any available
 * route certainly makes sense.
 * LIN/LIU/LIA/LUA/LID/LFU/LLI/LRI are definitely between adjacents, but
 * may take alternate routes.
 * I'm not sure about TRW/TRA.
 *
 * So, we need the following procedure:  for most of the SNMM messages,
 * when we get one it may not have arrived on the link set to the adjacent.
 * This is ok, as we have to have an alternate route to that adjacent (or
 * our config is screwed up).  In this case, the linkSet from L2 might be
 * wrong, so we have to go looking for the right one.
 *
 * How?  SelectRoute.  From first to last, look for a route where the
 * dpc is the same as the route->linkSet->adjacent, and both match the
 * OPC received in the message.
 *
 * Having said all that, we aren't interested in the route found, that
 * just has told us the real adjacent.  We're interested in the linkSet,
 * as that tells us the info we need (sometimes we are interested in
 * the adjacent route, but that code has been written already).
 *
 * Also note that, For CHM ECM and MIM correct link identity needs to be
 * retrived from OPC DPC and slc messages. This includes changeover 
 * changeback, Emergency changeover, all inhibit and uninhibit messages.
 *
 ****************************************************************************/
ITS_OCTET
MTP3_FindAdjacent_CCITT(ITS_OCTET ni, ITS_UINT pc,
                        ITS_OCTET linkSet)
{
    ROUTE_MatchInfo rinfo;
    SS7_Destination *rc;
    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;

    /* get the routing info for this destination */
    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                      REMOTE_ROUTE, ROUTE_DPC_NI,
                                      FAMILY_ITU,
                                      ni, linkSet,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_LINK_PRI,
                                      ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        MTP3_ERROR(("Couldn't parse routing info\n"));
 
        /* Increament the peg for Adjecent SP UNACCESIBLE*/
        /*PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE);*/
        
        return (ITS_SS7_DEFAULT_LINK_SET);
    }

    /* status not maintained for this PC? */
    if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                  &firstMatch, &lastMatch,
                                  &whichLinkCode,
                                  ITS_FALSE)) == NULL)
    {
        MTP3_DEBUG(("FindBestMatch failed, return.\n"));
 
        /* Increament the peg for Adjecent SP UNACCESIBLE*/
        /*PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE);*/

        return (ITS_SS7_DEFAULT_LINK_SET);
    }
    
    for (i = firstMatch; i <= lastMatch; i++)
    {
        if (rc->entries[i]->basic.dpc == pc &&
            rc->entries[i]->linkSet->adjacent == pc)
        {
            return (rc->entries[i]->linkSet->linkSet);
        }
    }
    
    /* bogus message, probably */
    return (ITS_SS7_DEFAULT_LINK_SET);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Deal with prohibited routes.
 *
 *  Input Parameters:
 *      Standard MTP3 args.
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
RTPC_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
                ITS_OCTET *sif, ITS_USHORT len,
                ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    MTP3_HEADER omtp3;
    SNMM_MESSAGE snmm, *isnmm;
    ITS_UINT pc1, pc2;
    ITS_OCTET ni;
    ITS_EVENT ev;
    ROUTE_MatchInfo rinfo;
    SS7_Destination *rc;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    int ret;
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;
    MTP3_TimerContext tc;
    ITS_UINT lscount=0,cnt=0;
    ITS_OCTET linkset[255];
    ITS_UINT i=0,j=0;

    ret = ITS_SUCCESS;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SRM_RTPC, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }


    switch (trigger)
    {
    case SRM_TRIGGER_TRANSFER_PROHIBIT:      /* from HMDT */
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                     sizeof(ITS_OCTET)];
        pc1 = SNMM_TRANSFER_STATE_GET_DEST(isnmm->data.transferState);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
        MTP3_ERROR(("\nSANDEEPTransfer Probhited point code is %d \n",pc1));
        /*
         * Find the link set whose adjacent PC matches the OPC
         * in the TFP.  This can then be used to look up the correct
         * route.
         */
        pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        MTP3_ERROR(("\nSANDEEPTransfer Probhited send by Point Code= %d \n",pc2));
        linkSet = MTP3_FindAdjacent_CCITT(ni, pc2, linkSet);

        rc = ROUTE_FindDestination(pc2, ni, FAMILY_ITU);
        if (rc)
        {
            PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_RX);
        }
        
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("%08x might think we're adjacent, but we don't.\n",
                         pc2));
            MTP3_Alarm_CCITT(2448, __FILE__, __LINE__, "%d",pc2); 

            return (ITS_EINVALIDARGS);
        }
        
        /* get the routing info for this destination via this adjacent */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));
        
            return (ITS_EINVALIDARGS);
        }

        /* status not maintained for this PC? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("FindBestMatch failed, return.\n"));

            return (ITS_SUCCESS);
        }
        else
        {
            /* which is negative here */
            if (whichEntry < 0)
            {
                MTP3_DEBUG(("Status not maintained or bogus route\n"));

                return (ITS_SUCCESS);
            }

            /* controlled rerouting in progress? */
            if (rc->entries[whichEntry]->flags & ROUTE_CONTROLLED_REROUTING)
            {
                /* yes, mark transfer prohibited, return */
                rc->entries[whichEntry]->flags |= ROUTE_TRANSFER_PROHIBITED;

                return (ITS_SUCCESS);
            }
            else
            {
                MTP3_HDR_SET_SIO(omtp3, ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                
                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, NULL, 0);

                /* signalling route unavailable */
                /* NOTE we tell TSRC the adjacent (linkSet) */
                TSRC_Main_CCITT(MTP3_SRM_RTPC,
                                STM_TRIGGER_ROUTE_UNAVAILABLE,
                                ev.data, ev.len,
                                linkSet,
                                ITS_SS7_DEFAULT_LINK_CODE);

                /* start route set test */
                /* NOTE we tell RSRT the adjacent (linkSet) */
								MTP3_ERROR(("\nSANDEEPStarting The RST for the Remote Destibnation linkSet is %d\n",linkSet));
                RSRT_Main_CCITT(MTP3_SRM_RTPC,
                                SRM_TRIGGER_START_ROUTE_SET_TEST,
                                ev.data, ev.len,
                                linkSet,
                                ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }
        }
        break;

    case SRM_TRIGGER_MSG_FOR_INACCESS_SP:    /* from HMRT */
        /* only STPs perform this action */
        if (!STPFunction_CCITT())
        {
            return (ITS_SUCCESS);
        }

        /* build TFP, send */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Invaliding incoming link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /*
         * NOTE: pc1 is the dest to prohibit, but ls->adj and ls-lpc are
         * the point codes to put in the routing label.
         * DON'T use linkSet looking up the route.  The normal route will
         * do just fine, as we know the destination is prohibited.
         */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;


        /* get the routing info for this destination */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        /* status not maintained for this PC? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("FindBestMatch failed.\n"));

            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET(snmm, SNMM_HC0_TFM);
            SNMM_HC1_SET(snmm, SNMM_HC1_TFP);
            SNMM_TRANSFER_STATE_SET_DEST(snmm.data.transferState, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);

            rc = ROUTE_FindDestination(pc1, ni, FAMILY_ITU);
            if (rc)
            {
                PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_TX);
            }


            /*
             * DON'T specify the link set/link code.  Use any
             * available route.
             */
            ret = HMRT_Main_CCITT(MTP3_SRM_RTPC,
                                  SMH_TRIGGER_ROUTE_MGMT_MSG,
                                  ev.data, ev.len,
                                  ITS_SS7_DEFAULT_LINK_SET,
                                  ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);

            return (ITS_SUCCESS);
        }

        /* T8 handling */
        if (rc->entries[whichEntry]->t8 == TIMER_BAD_SERIAL)
        {
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET(snmm, SNMM_HC0_TFM);
            SNMM_HC1_SET(snmm, SNMM_HC1_TFP);
            SNMM_TRANSFER_STATE_SET_DEST(snmm.data.transferState, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);


            rc = ROUTE_FindDestination(pc1, ni, FAMILY_ITU);
            if (rc)
            {
                PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_TX);
            }

            /*
             * DON'T specify the link set/link code.  Use any
             * available route.
             */
            ret = HMRT_Main_CCITT(MTP3_SRM_RTPC,
                                  SMH_TRIGGER_ROUTE_MGMT_MSG,
                                  ev.data, ev.len,
                                  ITS_SS7_DEFAULT_LINK_SET,
                                  ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);

            /* Start T8 */
            /* USE the link set of this entry */
            tc.timerId = MTP3_T8;
            tc.data.routeInfo.pointCode = pc1;
            tc.data.routeInfo.linkSet = rc->entries[whichEntry]->linkSet->linkSet;
            tc.data.routeInfo.sio = ni;

            rc->entries[whichEntry]->t8 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t8 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T8 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t8));
        }
        return (ret);

    case SRM_TRIGGER_SEND_TRANSFER_PROHIBIT: /* from RSRT */
    case SRM_TRIGGER_NEW_STP_DEST:           /* from TSRC */
        /* only STPs perform this action */
        if (!STPFunction_CCITT())
        {
            return (ITS_SUCCESS);
        }

        /* build TFP, send */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Invaliding incoming link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /*
         * NOTE: pc1 is dest to prohibit.  linkSet says which
         * adjacent to send to.
         * DON'T use linkSet looking up the route.  The normal route will
         * do just fine, as we know the destination is prohibited.
         */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);


        /* get the routing info for this destination */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ls->ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        /* status not maintained for this PC? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("FindBestMatch failed, return.\n"));

            return (ITS_EINVALIDARGS);
        }

        /* T8 handling */
        if (rc->entries[whichEntry]->t8 == TIMER_BAD_SERIAL)
        {
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET(snmm, SNMM_HC0_TFM);
            SNMM_HC1_SET(snmm, SNMM_HC1_TFP);
            SNMM_TRANSFER_STATE_SET_DEST(snmm.data.transferState, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            SNMM_Encode(&ev, &omtp3, &snmm);

            rc = ROUTE_FindDestination(pc1, ls->ni, FAMILY_ITU);
            if (rc)
            {
                PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_TX);
            }

            /*
             * DON'T specify the link set/link code.  Use any
             * available route.
             */
/**** to cut sending the TFP to adjusent**/
            if(pc1== ls->adjacent)
             {
							return;
						 }
/*****sandeep***/
            ret = HMRT_Main_CCITT(MTP3_SRM_RTPC,
                                  SMH_TRIGGER_ROUTE_MGMT_MSG,
                                  ev.data, ev.len,
                                  ITS_SS7_DEFAULT_LINK_SET,
                                  ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);

            /* Start T8 */
            /* USE the link set of this entry */
            tc.timerId = MTP3_T8;
            tc.data.routeInfo.pointCode = pc1;
            tc.data.routeInfo.linkSet = rc->entries[whichEntry]->linkSet->linkSet;
            tc.data.routeInfo.sio = ls->ni;

            rc->entries[whichEntry]->t8 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t8 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T8 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t8));
        }
        return (ret);

    case SRM_TRIGGER_DEST_INACCESS:          /* from TSRC */
        /* build TFP, send */

        /* only STPs perform this action */
        if (!STPFunction_CCITT())
        {
            return (ITS_SUCCESS);
        }

        /*
         * FIXME: An argument can be made that T8 (in this case) belongs
         * on the destination, not the route.  This repeats for other
         * timers as well.  The others (MSG_FOR_INACCESS_DEST, for example,
         * *should* be using the linkSet info when looking up the route.
         * This is because they need to notify the sender of the TFP, and
         * T8 runs only for that route.
         */

        /*
         * NOTE: pc1 is dest to prohibit.
         * DON'T use linkSet looking up the route.  The normal route will
         * do just fine, as we know the destination is prohibited.
         */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;


        /* get the routing info for this destination */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        /* status not maintained for this PC? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("FindBestMatch failed, return.\n"));

            return (ITS_EINVALIDARGS);
        }

        /* for each adjacent SP */
       //for (pc2 = 0; pc2 < ITS_SS7_DEFAULT_LINK_SET; pc2++)
        //MTP3_ERROR((" linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (i = 0; i < MAX_LINKSETS; i++)
         {
          for(j = 0;j < MAX_LINKS_PER_LINKSET ;j++)
          {
            if(linkTransportMapDB[i][j] >0)
             {
         //      MTP3_ERROR((" linkTransportMapDB[%d][%d]=%d\n",i,j,linkTransportMapDB[i][j]));
               if( i > 0 && i < 252)
               {
                lscount++;
                linkset[cnt++]=i;
                MTP3_ERROR((" linkset = %d\n",i));
                break;
               }
             }
          }
         }
         //MTP3_ERROR((" linkTransportMapDB\n"));
         //MTP3_ERROR((" Total Linkset %d found\n", lscount));

        for (pc2 = 0; pc2 < lscount; pc2++)
        {
            //if ((ls = LINKSET_FindLinkSet((ITS_OCTET)pc2)) == NULL ||
            if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkset[pc2])) == NULL ||
                ls->adjacent == 0)
            {
                continue;
            }

            /* don't bother notifying this adjacent if it's itself */
#if 0
            if (rc->entries[whichEntry]->linkSet->linkSet ==
                ls->linkSet)
            {
                continue;
            }
#endif

            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);

            SNMM_HC0_SET(snmm, SNMM_HC0_TFM);
            SNMM_HC1_SET(snmm, SNMM_HC1_TFP);
            SNMM_TRANSFER_STATE_SET_DEST(snmm.data.transferState, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            SNMM_Encode(&ev, &omtp3, &snmm);

            rc = ROUTE_FindDestination(pc1, ni, FAMILY_ITU);
            if (rc)
            {
                PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFP_TX);
            }

            /*
             * DON'T specify the link set/link code.  Use any
             * available route.
             */
            ret = HMRT_Main_CCITT(MTP3_SRM_RTPC,
                                 SMH_TRIGGER_ROUTE_MGMT_MSG,
                                 ev.data, ev.len,
                                 ITS_SS7_DEFAULT_LINK_SET,
                                 ITS_SS7_DEFAULT_LINK_CODE);
            ITS_EVENT_TERM(&ev);
        }

        /* Start T8 */
        /* USE the linkSet of this entry */
        tc.timerId = MTP3_T8;
        tc.data.routeInfo.pointCode = pc1;
        tc.data.routeInfo.linkSet = rc->entries[whichEntry]->linkSet->linkSet;
        tc.data.routeInfo.sio = ni;

        rc->entries[whichEntry]->t8 =
            TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                               __ccitt_t8 * USEC_PER_MILLISEC,
                               &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T8 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t8));

        return (ret);

    case SRM_TRIGGER_CONTROLLED_REROUTE_END: /* from TCRC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * USE the link set here.  TCRC has to tell us which path
         * controlled rerouting ended for.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet, linkCode,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        /* cancel controlled routing in progress */
        rc->entries[whichEntry]->flags &= ~ROUTE_CONTROLLED_REROUTING;

        if (!(rc->entries[whichEntry]->flags & ROUTE_TRANSFER_PROHIBITED))
        {
            return (ITS_SUCCESS);
        }
        else
        {
            rc->entries[whichEntry]->flags &= ~ROUTE_TRANSFER_PROHIBITED;

            MTP3_HDR_SET_SIO(omtp3, ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            /* signalling route unavailable */
            TSRC_Main_CCITT(MTP3_SRM_RTPC,
                           STM_TRIGGER_ROUTE_UNAVAILABLE,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

             /* start route set test */
            RSRT_Main_CCITT(MTP3_SRM_RTPC,
                           SRM_TRIGGER_START_ROUTE_SET_TEST,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }
        break;

    case SRM_TRIGGER_CONTROLLED_REROUTE:     /* from RTAC */
        /* mark controlled routing in progress */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * USE linkSet.  RTAC has to tell us which path
         * controlled rerouting is starting for.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet, linkCode,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        /* mark controlled routing in progress */
        rc->entries[whichEntry]->flags |= ROUTE_CONTROLLED_REROUTING;
        break;

    case SRM_TRIGGER_T8: /* optional */
        /* mark the timer stopped */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination
         * NOTE: when we started the timer, we specified the
         * correct linkSet to use.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        /* status not maintained for this PC? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("FindBestMatch failed, return.\n"));

            return (ITS_EINVALIDARGS);
        }

        /* mark the timer stopped */
        rc->entries[whichEntry]->t8 = TIMER_BAD_SERIAL;
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
 *      Deal with allowed routes.
 *
 *  Input Parameters:
 *      Standard MTP3 args.
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
RTAC_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    MTP3_HEADER omtp3;
    SNMM_MESSAGE snmm, *isnmm;
    ITS_UINT pc1, pc2;
    ITS_OCTET ni;
    ITS_EVENT ev;
    ROUTE_MatchInfo rinfo;
    SS7_Destination *rc;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    int ret;
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;
     ITS_UINT lscount=0,cnt=0;
    ITS_OCTET linkset[255];
    ITS_UINT i=0,j=0;

    ret = ITS_SUCCESS;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SRM_RTAC, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }

    switch (trigger)
    {
    case SRM_TRIGGER_TRANSFER_ALLOW:         /* from HMRT */
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                     sizeof(ITS_OCTET)];
        pc1 = SNMM_TRANSFER_STATE_GET_DEST(isnmm->data.transferState);
        pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /* Increament the peg for Transfer Allowed */
        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_RECEIVED);

        rc = ROUTE_FindDestination(pc2, ni, FAMILY_ITU);
        if (rc)
        {
            PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_RX);
        }

        /*
         * Find the link set whose adjacent PC matches the OPC
         * in the TFA.  This can then be used to look up the correct
         * route.
         */
        linkSet = MTP3_FindAdjacent_CCITT(ni, pc2, linkSet);
        
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("%08x might think we're adjacent, but we don't.\n",
                         pc2));

            MTP3_Alarm_CCITT(2451, __FILE__, __LINE__, "%d",pc2);
            
            
            return (ITS_EINVALIDARGS);
        }
        
        /* get the routing info for this destination */
        /* USE the link set we found above */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, /*linkSet;  FIXME:
                                          default linkset???
                                          all we need to know here
                                          is if the status of this
                                          route is maintained.
                                          Do we need to specify the link
                                          we got the message from??? */
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        /* status not maintained for this PC? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("RTAC_Main: status not maintained for %02x:%08x\n",
                        ni, pc1));
            /* no, return */
            return (ITS_SUCCESS);
        }
        else
        {
            /* if controlled rerouting in progress */
            /* if forced rerouting in progress */
            if (rc->entries[whichEntry]->flags & ROUTE_FORCED_REROUTING ||
                rc->entries[whichEntry]->flags & ROUTE_CONTROLLED_REROUTING)
            {
                MTP3_DEBUG(("RTAC_Main: we think NI:PC %02x:%08x is FR or CR\n",
                            ni, pc1));

                rc->entries[whichEntry]->flags |= ROUTE_TRANSFER_ALLOWED;
            }
            else
            {
                MTP3_DEBUG(("RTAC_Main: we think NI:PC %02x:%08x is available\n",
                            ni, pc1));

                MTP3_HDR_SET_SIO(omtp3, ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                
                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, NULL, 0);

                /* notify TSRC of singalling route available */
                /* Tell TSRC what the adjacent is */
                TSRC_Main_CCITT(MTP3_SRM_RTAC,
                               STM_TRIGGER_ROUTE_AVAILABLE,
                               ev.data, ev.len,
                               linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                /* notify RSRT of signalling route available */
                RSRT_Main_CCITT(MTP3_SRM_RTAC,
                               SRM_TRIGGER_ROUTE_AVAILABLE,
                               ev.data, ev.len,
                               linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }
        }
        break;

    case SRM_TRIGGER_DEST_ACCESS:            /* from TSRC */
        /* only STPs perform this action */
        if (!STPFunction_CCITT())
        {
            return (ITS_SUCCESS);
        }

        /* build TFA, send */
        /*
         * NOTE: pc1 is dest to allow.  linkSet says which
         * adjacent to send to.
         * DON'T CARE about the link set.  TSRC will have to
         * mark status.
         */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        rc = ROUTE_FindDestination(pc1, ni, FAMILY_ITU);
        if (rc)
        {
            PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_TX);
        }

        /* get the routing info for this destination */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));
   
            return (ITS_EINVALIDARGS);
        }

        /* status not maintained for this PC? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("SRM_TRIGGER_DEST_ACCESS:FindBestMatch failed, return.\n"));

            return (ITS_EINVALIDARGS);
        }

        /* to all adjacent SPs except as noted in 13.3.2(2) */
        //for (pc2 = 0; pc2 < ITS_SS7_DEFAULT_LINK_SET; pc2++)
        //MTP3_ERROR((" linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (i = 0; i < MAX_LINKSETS; i++)
         {
          for(j = 0;j < MAX_LINKS_PER_LINKSET ;j++)
          {
            if(linkTransportMapDB[i][j] >0)
             {
         //      MTP3_ERROR((" linkTransportMapDB[%d][%d]=%d\n",i,j,linkTransportMapDB[i][j]));
               if( i > 0 && i < 252)
               {
                lscount++;
                linkset[cnt++]=i;
                MTP3_ERROR((" linkset = %d\n",i));
                break;
               }
             }
          }
         }
         //MTP3_ERROR((" linkTransportMapDB\n"));
       //MTP3_ERROR(("Total Linket %d found ",lscount));
        for (pc2 = 0; pc2 < lscount; pc2++)
        {
            //if ((ls = LINKSET_FindLinkSet((ITS_OCTET)pc2)) == NULL ||
            if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkset[pc2])) == NULL ||
                ls->adjacent == 0)
            {
                continue;
            }

#if 0
            /* don't bother notifying this adjacent if it's itself */
            if (rc->entries[whichEntry]->linkSet->linkSet ==
                ls->linkSet)
            {
                continue;
            }
#endif

            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET(snmm, SNMM_HC0_TFM);
            SNMM_HC1_SET(snmm, SNMM_HC1_TFA);
            SNMM_TRANSFER_STATE_SET_DEST(snmm.data.transferState, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);


            /* USE any available route to the destination */
            ret = HMRT_Main_CCITT(MTP3_SRM_RTAC,
                                 SMH_TRIGGER_ROUTE_MGMT_MSG,
                                 ev.data, ev.len,
                                 ITS_SS7_DEFAULT_LINK_SET,
                                 ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }
        return (ret);

    case SRM_TRIGGER_REM_STP_DEST:           /* from TSRC */
    case SRM_TRIGGER_SEND_TRANSFER_ALLOW:    /* from RSRT */
        /* only STPs perform this action */
        if (!STPFunction_CCITT())
        {
            return (ITS_SUCCESS);
        }

        /* build TFA, send */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Invalid incoming link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /*
         * NOTE: pc1 is dest to allow.  linkSet says which
         * adjacent to send to.
         * DON'T CARE about the linkSet.  TSRC and RSRT have to
         * get this right.
         */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        

        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

        rc = ROUTE_FindDestination(pc1, ls->ni, FAMILY_ITU);
        if (rc)
        {
            PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFA_TX);
        }

        SNMM_HC0_SET(snmm, SNMM_HC0_TFM);
        SNMM_HC1_SET(snmm, SNMM_HC1_TFA);
        SNMM_TRANSFER_STATE_SET_DEST(snmm.data.transferState, pc1);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
        SNMM_Encode(&ev, &omtp3, &snmm);
        

        /* USE any available route */
        ret = HMRT_Main_CCITT(MTP3_SRM_RTAC,
                             SMH_TRIGGER_ROUTE_MGMT_MSG,
                             ev.data, ev.len,
                             ITS_SS7_DEFAULT_LINK_SET,
                             ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case SRM_TRIGGER_FORCED_REROUTE:         /* from TSRC */
        /* mark forced rerouting in progress */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
        /*
         * get the routing info for this destination
         * USE the linkSet.  TSRC has to tell us which path
         * forced rerouting is starting for.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_ERROR(("SRM_TRIGGER_FORCED_REROUTE:FindBestMatch failed\n"));
            return (ITS_EINVALIDARGS);
        }

        rc->entries[whichEntry]->flags |= ROUTE_FORCED_REROUTING;
        break;

    case SRM_TRIGGER_CONTROLLED_REROUTE:     /* from TSRC */
        /* mark controlled routing in progress */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * USE the linkSet.  TSRC has to tell us the path
         * controlled rerouting is starting for.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_ERROR(("SRM_TRIGGER_CONTROLLED_REROUTE:FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        /* mark controlled routing in progress */
        rc->entries[whichEntry]->flags |= ROUTE_CONTROLLED_REROUTING;
        break;

    case SRM_TRIGGER_FORCED_REROUTE_END:     /* from TFRC */
        /* cancel forced rerouting */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * USE the linkSet.  TFRC has to tell us who forced rerouting
         * is ending for.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_ERROR(("SRM_TRIGGER_FORCED_REROUTE_END:FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        rc->entries[whichEntry]->flags &= ~ROUTE_FORCED_REROUTING;

        if (rc->entries[whichEntry]->flags & ROUTE_TRANSFER_ALLOWED)
        {
            rc->entries[whichEntry]->flags &= ~ROUTE_TRANSFER_ALLOWED;

            MTP3_HDR_SET_SIO(omtp3, ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            /* notify TSRC of singalling route available */
            /* USE linkSet to tell TSRC which path */
            TSRC_Main_CCITT(MTP3_SRM_RTAC,
                           STM_TRIGGER_ROUTE_AVAILABLE,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            /* notify RSRT of signalling route available */
            /* USE linkSet to tell RSRT which path */
            RSRT_Main_CCITT(MTP3_SRM_RTAC,
                           SRM_TRIGGER_ROUTE_AVAILABLE,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }
        break;

    case SRM_TRIGGER_CONTROLLED_REROUTE_END: /* from TCRC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * USE the linkSet.  TCRC has to tell us which path controlled
         * rerouting is ending for.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("SRM_TRIGGER_CONTROLLED_REROUTE_END:FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        /* cancel controlled routing in progress */
        rc->entries[whichEntry]->flags &= ~ROUTE_CONTROLLED_REROUTING;

        if (rc->entries[whichEntry]->flags & ROUTE_TRANSFER_ALLOWED)
        {
            rc->entries[whichEntry]->flags &= ~ROUTE_TRANSFER_ALLOWED;

            MTP3_HDR_SET_SIO(omtp3, ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            /* notify TSRC of singalling route available */
            /* USE the linkSet to tell TSRC which path */
            TSRC_Main_CCITT(MTP3_SRM_RTAC,
                           STM_TRIGGER_ROUTE_AVAILABLE,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            /* notify RSRT of signalling route available */
            /* USE the linkSet to tell RSRT which path */
            RSRT_Main_CCITT(MTP3_SRM_RTAC,
                           SRM_TRIGGER_ROUTE_AVAILABLE,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
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
RSRT_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    MTP3_HEADER omtp3;
    SNMM_MESSAGE snmm, *isnmm;
    MTP3_POINT_CODE tpc;
    ITS_UINT pc1, pc2;
    ITS_OCTET ni, hc1;
    ITS_EVENT ev;
    ROUTE_MatchInfo rinfo;
    SS7_Destination *rc, *rc1;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    int ret, i;
    ROUTE_Info *ri;
    SS7_LinkPtr ln;
    MTP3_TimerContext tc1;
    ITS_BOOLEAN onlyThroughY;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SRM_RSRT, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
       MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }

    switch (trigger)
    {
    case SRM_TRIGGER_START_ROUTE_SET_TEST:   /* from RTRC: RTPC: TSRC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination
         * USE the linkSet information.  We are looking at a specific
         * path.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_ERROR(("SRM_TRIGGER_START_ROUTE_SET_TEST:FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        if (rc->entries[whichEntry]->testState == ROUTE_TEST_IDLE)
        {
            if (src == MTP3_STM_TSRC)
            {
                /* build RSR/RSP/RCR/RCP, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM |
                                        rc->entries[whichEntry]->linkSet->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label,
                                      rc->entries[whichEntry]->linkSet->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label,
                                      rc->entries[whichEntry]->linkSet->lpc);

                MTP3_PC_SET_VALUE(tpc, pc1);

                SNMM_HC0_SET(snmm, SNMM_HC0_RSM);
                if (rc->status == DESTINATION_UNAVAILABLE)
                {
                    SNMM_HC1_SET(snmm, SNMM_HC1_RSP);
                }
                else if (rc->status == DESTINATION_RESTRICTED)
                {
                    SNMM_HC1_SET(snmm, SNMM_HC1_RSR);
                }
                SNMM_ROUTE_SET_TEST_SET_DEST(snmm.data.routeSetTest, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                SNMM_Encode(&ev, &omtp3, &snmm);

                rc = ROUTE_FindDestination(pc1, ni, FAMILY_ITU);
                if (rc)
                {
                    PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_TX);
                }

                /* USE any available route */
                ret = HMRT_Main_CCITT(MTP3_SRM_RSRT,
                                     SMH_TRIGGER_ROUTE_MGMT_MSG,
                                     ev.data, ev.len,
                                     ITS_SS7_DEFAULT_LINK_SET,
                                     ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);

                return (ret);
            }
            else
            {
                MTP3_TimerContext tc;

                /* start route test test */
                /* mark route set test for (restricted|prohibited) destination */
                if (src == MTP3_SRM_RTRC)
                {
                    rc->entries[whichEntry]->flags |= ROUTE_TEST_FOR_RESTRICTED;
                }
                else
                {
                    rc->entries[whichEntry]->flags |= ROUTE_TEST_FOR_PROHIBITED;
                }

                /* start T10 */
                tc.timerId = MTP3_T10;
                tc.data.routeInfo.pointCode = pc1;
                tc.data.routeInfo.linkSet = rc->entries[whichEntry]->linkSet->linkSet;
                tc.data.routeInfo.sio = ni;

                rc->entries[whichEntry]->t10 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t10 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T10 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t10));

                /* go to WAIT 1 */
                rc->entries[whichEntry]->testState = ROUTE_TEST_WAIT_1;
            }
        }
        break;

    case SRM_TRIGGER_ROUTE_AVAILABLE:        /* from RTAC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination
         * USE the linkSet information.  We are looking at a specific
         * path.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,  /* linkSet; FIXME:
                                          default linkset???
                                          all we need to know here
                                          is if the status of this
                                          route is maintained.
                                          Do we need to specify the link
                                          we got the message from??? */
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("SRM_TRIGGER_ROUTE_AVAILABLE:FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        if (rc->entries[whichEntry]->testState == ROUTE_TEST_WAIT_1)
        {
            if (rc->entries[whichEntry]->t10 != TIMER_BAD_SERIAL)
            {
                MTP3_DEBUG(("MTP3 CANCEL T10 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t10));
                TIMERS_CancelSharedTimer(rc->entries[whichEntry]->t10);
                rc->entries[whichEntry]->t10 = TIMER_BAD_SERIAL;
            }

            rc->entries[whichEntry]->testState = ROUTE_TEST_IDLE;
        }
        break;

    case SRM_TRIGGER_T10:                    /* from timer control */
        /* build RSR/RSP/RCR/RCP, send */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination
         * USE the linkSet information.  We are looking at a specific
         * path.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("SRM_TRIGGER_T10:FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        rc->entries[whichEntry]->t10 = TIMER_BAD_SERIAL;

        MTP3_PC_SET_VALUE(tpc, pc1);

        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM |
                                rc->entries[whichEntry]->linkSet->ni);
        MTP3_RL_SET_DPC_VALUE(omtp3.label,
                              rc->entries[whichEntry]->linkSet->adjacent);
        MTP3_RL_SET_OPC_VALUE(omtp3.label,
                              rc->entries[whichEntry]->linkSet->lpc);

        SNMM_HC0_SET(snmm, SNMM_HC0_RSM);
        if (rc->status == DESTINATION_UNAVAILABLE)
        {
            SNMM_HC1_SET(snmm, SNMM_HC1_RSP);
        }
        else if (rc->status == DESTINATION_RESTRICTED)
        {
            SNMM_HC1_SET(snmm, SNMM_HC1_RSR);
        }
        else /* it's available */
        {
            return (ITS_SUCCESS);
        }

        SNMM_ROUTE_SET_TEST_SET_DEST(snmm.data.routeSetTest, pc1);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        SNMM_Encode(&ev, &omtp3, &snmm);

        rc1 = ROUTE_FindDestination(MTP3_RL_GET_DPC_VALUE(omtp3.label), 
                                                            ni, FAMILY_ITU);
        if (rc1)
        {
            PEG_IncrPeg(&rc1->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_TX);
        }

        /* USE any path */
        ret = HMRT_Main_CCITT(MTP3_SRM_RSRT,
                             SMH_TRIGGER_ROUTE_MGMT_MSG,
                             ev.data, ev.len,
                             ITS_SS7_DEFAULT_LINK_SET,
                             ITS_SS7_DEFAULT_LINK_CODE);

       /* start T10 */
       tc1.timerId = MTP3_T10;
       tc1.data.routeInfo.pointCode = pc1;
       tc1.data.routeInfo.linkSet = rc->entries[whichEntry]->linkSet->linkSet;
       tc1.data.routeInfo.sio = ni;

       rc->entries[whichEntry]->t10 =
              TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                               __ccitt_t10 * USEC_PER_MILLISEC,
                                &tc1, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T10 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t10));

        ITS_EVENT_TERM(&ev);

        return (ret);

    case SRM_TRIGGER_ROUTE_SET_TEST:         /* from HMDT */
        pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        rc = ROUTE_FindDestination(pc2, ni, FAMILY_ITU);
        if (rc)
        {
            PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_RST_RX);
        }

        if (STPFunction_CCITT())
        {
            if (!SPRestarting_CCITT())
            {
                isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                             sizeof(ITS_OCTET)];

                pc1 = SNMM_ROUTE_SET_TEST_GET_DEST(isnmm->data.routeSetTest);
                ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

                /*
                 * can't trust the linkSet info.  Find the true adjacent.
                 */
                linkSet = MTP3_FindAdjacent_CCITT(ni, pc2, linkSet);

                if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
                {
                    MTP3_ERROR(("%08x might think we're adjacent, but we don't.\n", pc2));

                    MTP3_Alarm_CCITT(2456, __FILE__, __LINE__, "%d",pc2); 
            
                    return (ITS_EINVALIDARGS);
                }

                /*
                 * get the routing info for this destination
                 * DON'T USE the linkSet information.  An adjacent is asking if
                 * any of our routes are back up.  Stick the state information
                 * on the normal route.
                 */
                if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                                  REMOTE_ROUTE, ROUTE_DPC_NI,
                                                  FAMILY_ITU,
                                                  ni,
                                                  ITS_SS7_DEFAULT_LINK_SET,
                                                  ITS_SS7_DEFAULT_LINK_CODE,
                                                  ITS_SS7_DEFAULT_LINK_PRI,
                                                  ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Couldn't parse routing info\n"));

                    return (ITS_EINVALIDARGS);
                }

                if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                              &firstMatch, &lastMatch,
                                              &whichLinkCode,
                                              ITS_FALSE)) == NULL)
                {
                    MTP3_DEBUG(("SRM_TRIGGER_ROUTE_SET_TEST:FindBestMatch failed\n"));

                    return (ITS_EINVALIDARGS);
                }

                MTP3_HDR_SET_SIO(omtp3, ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
        
                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, sif, len);
                
                rc->entries[whichEntry]->testState = ROUTE_TEST_WAIT_2;

                /* get accessibility */
                TSRC_Main_CCITT(MTP3_SRM_RSRT,
                               STM_TRIGGER_ACCESSIBILITY_REQUEST,
                               ev.data, ev.len,
                               linkSet, linkCode);

                ITS_EVENT_TERM(&ev);
            }
        }
        break;

    case SRM_TRIGGER_ACCESSIBILITY_DATA:     /* from TSRC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination
         * DON'T USE the linkSet information.  An adjacent is asking if
         * any of our routes are back up.  Stick the state information
         * on the normal route.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("SRM_TRIGGER_ACCESSIBILITY_DATA:FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        if (rc->entries[whichEntry]->testState == ROUTE_TEST_WAIT_2)
        {
            /*
             * NOTE: The linkCode contains a boolean indicating if the
             * destination is accessible.  The linkSet is whatever was
             * passed to the accessibility request.  The body of the
             * message is the original sif (header + SNMM).
             */

            isnmm = (SNMM_MESSAGE *)&sif[2 * sizeof(ITS_OCTET) +
                                         2 * sizeof(MTP3_HEADER)];

            mtp3 = (MTP3_HEADER *)&sif[2 * sizeof(ITS_OCTET) +
                                       sizeof(MTP3_HEADER)];
            pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

            /* Find route via Y */
            ri = NULL;
            onlyThroughY = ITS_TRUE;
            for (i = firstMatch; i <= lastMatch; i++)
            {
                if (rc->entries[i]->isAllowed &&
                    rc->entries[i]->linkSet->adjacent != pc2)
                {
                    onlyThroughY = ITS_FALSE;
                }

                if (rc->entries[i]->linkSet->adjacent == pc2)
                {
                    ri = rc->entries[i];
                }
            }

            hc1 = SNMM_HC1_GET(*isnmm);
            /* is accessibility the same as in the RST? */
            if ((rc->status == DESTINATION_UNAVAILABLE &&
                 hc1 == SNMM_HC1_RSP) ||
                (rc->status == DESTINATION_RESTRICTED &&
                 hc1 == SNMM_HC1_RSR))
            {
                /* yes, return */
                return (ITS_SUCCESS);
            }
            /* else if destination not accessible, or */
            /* destination only available via Y, or */
            /* FIXME: a preventative TFP was sent to Y */
            else if (rc->status == DESTINATION_UNAVAILABLE ||
                     (ri != NULL && rc->status == DESTINATION_AVAILABLE &&
                      onlyThroughY))
            {
                MTP3_HDR_SET_SIO(omtp3, ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, NULL, 0);

                /* send the TFP to the originator of the RST */
                ret = RTPC_Main_CCITT(MTP3_SRM_RSRT,
                                     SRM_TRIGGER_SEND_TRANSFER_PROHIBIT,
                                     ev.data, ev.len,
                                     linkSet,
                                     ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }
            /* else if not via Y and not via a first priority set */
            else if (rc->status == DESTINATION_AVAILABLE &&
                     ri && ri->priority != 0)
            {
                MTP3_HDR_SET_SIO(omtp3, ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, NULL, 0);

                /* send the TFR to the originator of the RST */
                ret = RTRC_Main_CCITT(MTP3_SRM_RSRT,
                                     SRM_TRIGGER_SEND_TRANSFER_RESTRICT,
                                     ev.data, ev.len,
                                     linkSet,
                                     ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }
            else
            {
                MTP3_HDR_SET_SIO(omtp3, ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, NULL, 0);

                /* send the TFA to the originator of the RST */
                ret = RTAC_Main_CCITT(MTP3_SRM_RSRT,
                                     SRM_TRIGGER_SEND_TRANSFER_ALLOW,
                                     ev.data, ev.len,
                                     linkSet,
                                     ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }

            return (ret);
        }
        else if (rc->entries[whichEntry]->testState == ROUTE_TEST_WAIT_5)
        {
            /*
             * NOTE: The linkCode contains a boolean indicating if the
             * destination is accessible.  The linkSet is whatever was
             * passed to the accessibility request.  The message body
             * is the original sif (header + SNMM).
             */

            isnmm = (SNMM_MESSAGE *)&sif[2 * sizeof(ITS_OCTET) +
                                         2 * sizeof(MTP3_HEADER)];

            mtp3 = (MTP3_HEADER *)&sif[2 * sizeof(ITS_OCTET) +
                                       sizeof(MTP3_HEADER)];
            pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

            /* Find route via Y */
            ri = NULL;
            onlyThroughY = ITS_TRUE;
            for (i = firstMatch; i <= lastMatch; i++)
            {
                if (rc->entries[i]->isAllowed &&
                    rc->entries[i]->linkSet->adjacent != pc2)
                {
                    onlyThroughY = ITS_FALSE;
                }

                if (rc->entries[i]->linkSet->adjacent == pc2)
                {
                    ri = rc->entries[i];
                }
            }

            hc1 = SNMM_HC1_GET(*isnmm);
            /* is accessibility the same as in the RST? */
            /* AKA: data in test message correct? */
            if ((rc->status == DESTINATION_UNAVAILABLE &&
                 hc1 == SNMM_HC1_RSP) ||
                (rc->status == DESTINATION_RESTRICTED &&
                 hc1 == SNMM_HC1_RSR))
            {
                return (ITS_SUCCESS);
            }
            /* else is any point in cluster accessible via normal routing and
             * not Y? */
            else if (ri && ri->priority == 0 && !onlyThroughY)
            {
                MTP3_HDR_SET_SIO(omtp3, ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, NULL, 0);

                ret = RTAC_Main_CCITT(MTP3_SRM_RSRT,
                                     SRM_TRIGGER_SEND_TCA,
                                     ev.data, ev.len,
                                     linkSet,
                                     ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }
            /* else is any point in cluster accessiblevia alternate route and
             * not Y? */
            else if (ri && ri->priority != 0 && !onlyThroughY)
            {
                MTP3_HDR_SET_SIO(omtp3, ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, NULL, 0);

                ret = RTRC_Main_CCITT(MTP3_SRM_RSRT,
                                     SRM_TRIGGER_SEND_TCR,
                                     ev.data, ev.len,
                                     linkSet,
                                     ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }
            else
            {
                MTP3_HDR_SET_SIO(omtp3, ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, NULL, 0);

                ret = RTPC_Main_CCITT(MTP3_SRM_RSRT,
                                      SRM_TRIGGER_SEND_TCP,
                                      ev.data, ev.len,
                                      linkSet,
                                      ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }
        }
        break;

    case SRM_TRIGGER_TCA_RCVD:               /* from RTAC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination
         * USE the linkSet information.  We are looking at a specific
         * path.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("SRM_TRIGGER_TCA_RCVD:FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        if (rc->entries[whichEntry]->testState == ROUTE_TEST_IDLE)
        {
            /* FIXME: stop tests on this route for destinations in cluster */
            /* UPDATE: This presupposes xlists */
        }
        else if (rc->entries[whichEntry]->testState == ROUTE_TEST_WAIT_3 ||
                 rc->entries[whichEntry]->testState == ROUTE_TEST_WAIT_4)
        {
            rc->entries[whichEntry]->testState = ROUTE_TEST_IDLE;
        }
        break;

    case SRM_TRIGGER_TCP_RCVD:               /* from TSRC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination
         * USE the linkSet information.  We are looking at a specific
         * path.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("SRM_TRIGGER_TCP_RCVD:FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        if (rc->entries[whichEntry]->testState == ROUTE_TEST_IDLE)
        {
            MTP3_TimerContext tc;

            /* FIXME: stop tests on that route for destinations in cluster */
            /* UPDATE: This presupposes xlists */

            /* start T10 */
            tc.timerId = MTP3_T10;
            tc.data.routeInfo.pointCode = pc1;
            tc.data.routeInfo.linkSet = linkSet;
            tc.data.routeInfo.sio = ni;

            rc->entries[whichEntry]->t10 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t10 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T10 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t10));

            rc->entries[whichEntry]->testState = ROUTE_TEST_WAIT_3;
        }
        else if (rc->entries[whichEntry]->testState == ROUTE_TEST_WAIT_4)
        {
            MTP3_TimerContext tc;

            /* start T10 */
            tc.timerId = MTP3_T10;
            tc.data.routeInfo.pointCode = pc1;
            tc.data.routeInfo.linkSet = linkSet;
            tc.data.routeInfo.sio = ni;

            rc->entries[whichEntry]->t10 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t10 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T10 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t10));

            rc->entries[whichEntry]->testState = ROUTE_TEST_WAIT_3;
        }
        break;

    case SRM_TRIGGER_TCR_RCVD:               /* from TSRC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination
         * USE the linkSet information.  We are looking at a specific
         * path.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("SRM_TRIGGER_TCR_RCVD:FindBestMatch failed\n"));

            return (ITS_EINVALIDARGS);
        }

        /* if state is idle */
        if (rc->entries[whichEntry]->testState == ROUTE_TEST_IDLE)
        {
            MTP3_TimerContext tc;

            /* FIXME: stop tests on that route for restricted destinations in cluster */
            /* UPDATE: This presupposes xlists */

            /* start T10 */
            tc.timerId = MTP3_T10;
            tc.data.routeInfo.pointCode = pc1;
            tc.data.routeInfo.linkSet = linkSet;
            tc.data.routeInfo.sio = ni;

            rc->entries[whichEntry]->t10 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t10 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T10 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t10));

            rc->entries[whichEntry]->testState = ROUTE_TEST_WAIT_4;
        }
        /* else if state == WAIT 3 */
        else if (rc->entries[whichEntry]->testState == ROUTE_TEST_WAIT_3)
        {
            MTP3_TimerContext tc;

            /* start T10 */
            tc.timerId = MTP3_T10;
            tc.data.routeInfo.pointCode = pc1;
            tc.data.routeInfo.linkSet = linkSet;
            tc.data.routeInfo.sio = ni;

            rc->entries[whichEntry]->t10 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t10 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T10 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t10));

            rc->entries[whichEntry]->testState = ROUTE_TEST_WAIT_4;
        }
        break;

    case SRM_TRIGGER_RESTART_BEGINS:         /* from TPRC */
        /*
         * Action: mark SP restarting.  This is not necessary, TPRC does
         * this.
         */
        break;

    case SRM_TRIGGER_RESTART_ENDS:           /* from TPRC */
        /*
         * Action: clear SP restarting.  This is not necessary, TPRC does
         * this.
         */
        break;

    case SRM_TRIGGER_ADJACENT_RESTARTING:    /* from TSRC */
        /* stop tests to adjacent SP */
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
 *      Deal with restricted destinations.
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
RTRC_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    MTP3_HEADER omtp3;
    SNMM_MESSAGE snmm, *isnmm;
    ITS_UINT pc1, pc2;
    ITS_OCTET ni;
    ITS_EVENT ev;
    ROUTE_MatchInfo rinfo;
    SS7_Destination *rc = NULL;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    int ret;
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;
    MTP3_TimerContext tc;

    ret = ITS_SUCCESS;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SRM_RTRC, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
      MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }

    switch (trigger)
    {
    case SRM_TRIGGER_TRANSFER_RESTRICT:      /* from HMDT */
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                     sizeof(ITS_OCTET)];
        pc1 = SNMM_TRANSFER_STATE_GET_DEST(isnmm->data.transferState);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * Find the link set whose adjacent PC matches the OPC
         * in the TFR.  This can then be used to look up the correct
         * route.
         */
        pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        linkSet = MTP3_FindAdjacent_CCITT(ni, pc2, linkSet);

        rc = ROUTE_FindDestination(pc2, ni, FAMILY_ITU);
        if (rc)
        {
            PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFR_RX);
        }
        
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("%08x might think we're adjacent, but we don't.\n",
                         pc2));

            MTP3_Alarm_CCITT(2459, __FILE__, __LINE__, "%d",pc2);
            
            return (ITS_EINVALIDARGS);
        }
        
        /*
         * get the routing info for this destination.
         * USE the linkSet we just found.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        /* status not maintained for this PC? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            return (ITS_SUCCESS);
        }
        else
        {
           /* Return error, No route is confogured on this linkset
             * Fix propagated from WSC #1808 */
            if (whichEntry == -1)
            {
                MTP3_ERROR((" TFR received no route found PC = %d, \
                             LinkSet = %d\n", rinfo.basic.dpc, rinfo.linkSet));

                return ITS_EINVALIDARGS;
            }

            if (rc->entries[whichEntry]->flags & ROUTE_CONTROLLED_REROUTING ||
                rc->entries[whichEntry]->flags & ROUTE_FORCED_REROUTING)
            {
                rc->entries[whichEntry]->flags |= ROUTE_TRANSFER_RESTRICTED;
            }
            else
            {
                MTP3_HDR_SET_SIO(omtp3, ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                
                MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                            &omtp3, NULL, 0);

                /* signalling route restricted */
                /* TELL TSRC which path (linkSet) */
                TSRC_Main_CCITT(MTP3_SRM_RTRC,
                               STM_TRIGGER_ROUTE_RESTRICTED,
                               ev.data, ev.len,
                               linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                /* start route set test */
                /* TELL RSRT which path (linkSet) */
                RSRT_Main_CCITT(MTP3_SRM_RTRC,
                               SRM_TRIGGER_START_ROUTE_SET_TEST,
                               ev.data, ev.len,
                               linkSet,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);
            }
        }
        break;

    case SRM_TRIGGER_TCR:                    /* from HMDT */
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                     sizeof(ITS_OCTET)];
        pc1 = SNMM_TRANSFER_STATE_GET_DEST(isnmm->data.transferState);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * Find the link set whose adjacent PC matches the OPC
         * in the TCR.  This can then be used to look up the correct
         * route.
         */
        pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        linkSet = MTP3_FindAdjacent_CCITT(ni, pc2, linkSet);
        
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("%08x might think we're adjacent, but we don't.\n",
                         pc2));

            MTP3_Alarm_CCITT(2459, __FILE__, __LINE__, "%d",pc2);
            
            return (ITS_EINVALIDARGS);
        }
        
        /*
         * get the routing info for this destination.
         * USE the linkSet we just found.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        /* status maintained for this cluster? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) != NULL)
        {
            MTP3_HDR_SET_SIO(omtp3, ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            /* yes, send cluster allowed */
            /* TELL TSRC which path (linkSet) */
            TSRC_Main_CCITT(MTP3_SRM_RTRC,
                           STM_TRIGGER_TCR,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }
        else
        {
            ITS_UINT i;
            MTP3_POINT_CODE spc;

            /* for each member status is maintained for */
            for (i = 0; i < 255; i++)
            {

                MTP3_PC_SET_VALUE(spc, pc1);
                MTP3_PC_SET_MEMBER(spc, i);
                pc2 = MTP3_PC_GET_VALUE(spc);

                /*
                 * get the routing info for this destination
                 * USE the linkSet we found.
                 */
                if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc2,
                                                  REMOTE_ROUTE, ROUTE_DPC_NI,
                                                  FAMILY_ITU,
                                                  ni, linkSet, linkCode,
                                                  ITS_SS7_DEFAULT_LINK_PRI,
                                                  ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Couldn't parse routing info\n"));

                    continue;
                }

                /* status maintained for this cluster? */
                if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                              &firstMatch, &lastMatch,
                                              &whichLinkCode,
                                              ITS_FALSE)) == NULL)
                {
                    MTP3_DEBUG(("Status not maintained for member %08x\n", pc2));

                    continue;
                }

                /* if forced rerouting in progress, or */
                /* if controlled rerouting in progress */
                if (rc->entries[whichEntry]->flags & ROUTE_FORCED_REROUTING ||
                    rc->entries[whichEntry]->flags & ROUTE_CONTROLLED_REROUTING)
                {
                    /* mark transfer restricted */
                    rc->entries[whichEntry]->flags |= ROUTE_TRANSFER_RESTRICTED;
                }
                else
                {
                    MTP3_HDR_SET_SIO(omtp3, ni);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
                
                    MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                                &omtp3, NULL, 0);

                    /* signalling route restricted */
                    /* TELL TSRC which path (linkSet) */
                    TSRC_Main_CCITT(MTP3_SRM_RTRC,
                                   STM_TRIGGER_ROUTE_RESTRICTED,
                                   ev.data, ev.len,
                                   linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    /* start route set test */
                    /* TELL RSRT which path (linkSet) */
                    RSRT_Main_CCITT(MTP3_SRM_RTRC,
                                   SRM_TRIGGER_START_ROUTE_SET_TEST,
                                   ev.data, ev.len,
                                   linkSet,
                                   ITS_SS7_DEFAULT_LINK_CODE);

                    ITS_EVENT_TERM(&ev);
                }
            }
        }
        break;

    case SRM_TRIGGER_MSG_FOR_RESTRICTED_DEST: /* from HMRT, TSRC */
        /* only STPs perform this action */
        if (!STPFunction_CCITT())
        {
            return (ITS_SUCCESS);
        }

        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Invalid incoming link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * DON'T use the linkSet we got.  That's telling us who
         * to send the TFR/TCR to.  Use the normal route instead
         * (it's the destination restricted, not necessarily the route).
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if (!(rc->entries[whichEntry]->flags & ROUTE_SENT_TFR_TWICE))
        {
            if (rc->entries[whichEntry]->flags & ROUTE_SENT_TFR_ONCE)
            {
                /* if not T18 running */
                if (rc->entries[whichEntry]->t18 == TIMER_BAD_SERIAL)
                {
                    rc->entries[whichEntry]->flags |= ROUTE_SENT_TFR_TWICE;
                }
            }
            else
            {
                /* start T18 */
                /* USE the linkset from the route entry */
                tc.timerId = MTP3_T18;
                tc.data.routeInfo.pointCode = pc1;
                tc.data.routeInfo.linkSet = rc->entries[whichEntry]->linkSet->linkSet;
                tc.data.routeInfo.sio = ls->ni;

                rc->entries[whichEntry]->t18 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                       __ccitt_t18 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T18 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t18));

                rc->entries[whichEntry]->flags |= ROUTE_SENT_TFR_ONCE;

                /* build TFR, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET(snmm, SNMM_HC0_TFM);
                SNMM_HC1_SET(snmm, SNMM_HC1_TFR);
                SNMM_TRANSFER_STATE_SET_DEST(snmm.data.transferState, pc1);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);

                /* USE any route for delivery */
                ret = HMRT_Main_CCITT(MTP3_SRM_RTRC,
                                     SMH_TRIGGER_ROUTE_MGMT_MSG,
                                     ev.data, ev.len,
                                     ITS_SS7_DEFAULT_LINK_SET,
                                     ITS_SS7_DEFAULT_LINK_CODE);
                ITS_EVENT_TERM(&ev);

                return (ret);
            }
        }
        break;

    case SRM_TRIGGER_SEND_TRANSFER_RESTRICT: /* from RSRT: from TSRC */
        /* only STPs perform this action */
        if (!STPFunction_CCITT())
        {
            return (ITS_SUCCESS);
        }

        /* build TFR, send */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Invalid incoming link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);

        /*
         * NOTE: the linkSet is DON'T CARE.  RSRT and TSRC have to send
         * the right one.
         */
        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

        SNMM_HC0_SET(snmm, SNMM_HC0_TFM);
        SNMM_HC1_SET(snmm, SNMM_HC1_TFR);
        SNMM_TRANSFER_STATE_SET_DEST(snmm.data.transferState, pc1);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
        SNMM_Encode(&ev, &omtp3, &snmm);


        /* use any available route */
        ret = HMRT_Main_CCITT(MTP3_SRM_RTRC,
                             SMH_TRIGGER_ROUTE_MGMT_MSG,
                             ev.data, ev.len,
                             ITS_SS7_DEFAULT_LINK_SET,
                             ITS_SS7_DEFAULT_LINK_CODE);
        ITS_EVENT_TERM(&ev);

        return (ret);

    case SRM_TRIGGER_DEST_RESTRICT:          /* from TSRC */
        /* only STPs perform this action */
        if (!STPFunction_CCITT())
        {
            return (ITS_SUCCESS);
        }

        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * DON'T USE the linkSet.  The destination is restricted, so
         * use the normal route for this information.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        rc->entries[whichEntry]->flags |= ROUTE_SENT_TFR_ONCE;

        /* for all adjacent SPs except as per 13.2.2(1) */
        //for (pc2 = 0; pc2 < ITS_SS7_DEFAULT_LINK_SET; pc2++)
        for (pc2 = 0; pc2 < 2; pc2++)
        {
            if ((ls = LINKSET_FindLinkSet((ITS_OCTET)pc2)) == NULL ||
                ls->adjacent == 0)
            {
                continue;
            }

#if 0
            /* don't bother notifying this adjacent if it's itself */
            if (rc->entries[whichEntry]->linkSet->linkSet ==
                ls->linkSet)
            {
                continue;
            }
#endif

            /* build TFR, send */
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            SNMM_HC0_SET(snmm, SNMM_HC0_TFM);
            SNMM_HC1_SET(snmm, SNMM_HC1_TFR);
            SNMM_TRANSFER_STATE_SET_DEST(snmm.data.transferState, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

            SNMM_Encode(&ev, &omtp3, &snmm);


            /* USE any available route */
            ret = HMRT_Main_CCITT(MTP3_SRM_RTRC,
                                 SMH_TRIGGER_ROUTE_MGMT_MSG,
                                 ev.data, ev.len,
                                 ITS_SS7_DEFAULT_LINK_SET,
                                 ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }

        /* start T18 */
        /* use the route's link set */
        tc.timerId = MTP3_T18;
        tc.data.routeInfo.pointCode = pc1;
        tc.data.routeInfo.linkSet = rc->entries[whichEntry]->linkSet->linkSet;
        tc.data.routeInfo.sio = rc->entries[whichEntry]->linkSet->ni;

        rc->entries[whichEntry]->t18 =
            TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                               __ccitt_t18 * USEC_PER_MILLISEC,
                               &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T18 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t18));

        return (ret);

    case SRM_TRIGGER_FORCED_REROUTE:        /* from TSRC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * USE the linkSet.  TSRC has to tell us which path.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        rc->entries[whichEntry]->flags |= ROUTE_FORCED_REROUTING;
        break;

    case SRM_TRIGGER_FORCED_REROUTE_END:    /* from TFRC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * USE the linkSet.  TFRC has to tell us which path forced
         * rerouting is ending for.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        rc->entries[whichEntry]->flags &= ~ROUTE_FORCED_REROUTING;

        if (rc->entries[whichEntry]->flags & ROUTE_TRANSFER_RESTRICTED)
        {
            rc->entries[whichEntry]->flags &= ~ROUTE_TRANSFER_RESTRICTED;

            MTP3_HDR_SET_SIO(omtp3, ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
        
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            /* signalling route restricted */
            /* TELL TSRC which path (linkSet) */
            TSRC_Main_CCITT(MTP3_SRM_RTRC,
                           STM_TRIGGER_ROUTE_RESTRICTED,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            /* start route set test */
            /* TELL RSRT which path (linkSet) */
            RSRT_Main_CCITT(MTP3_SRM_RTRC,
                           SRM_TRIGGER_START_ROUTE_SET_TEST,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }
        break;

    case SRM_TRIGGER_CONTROLLED_REROUTE_END:/* from TCRC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * USE the linkSet.  TCRC has to tell us which path controlled
         * rerouting is ending for.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        rc->entries[whichEntry]->flags &= ~ROUTE_CONTROLLED_REROUTING;

        if (rc->entries[whichEntry]->flags & ROUTE_TRANSFER_RESTRICTED)
        {
            rc->entries[whichEntry]->flags &= ~ROUTE_TRANSFER_RESTRICTED;

            MTP3_HDR_SET_SIO(omtp3, ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
        
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            /* signalling route restricted */
            /* TELL TSRC which path (linkSet) */
            TSRC_Main_CCITT(MTP3_SRM_RTRC,
                           STM_TRIGGER_ROUTE_RESTRICTED,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            /* start route set test */
            /* TELL RSRT which path (linkSet) */
            RSRT_Main_CCITT(MTP3_SRM_RTRC,
                           SRM_TRIGGER_START_ROUTE_SET_TEST,
                           ev.data, ev.len,
                           linkSet,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }
        break;

    case SRM_TRIGGER_CONTROLLED_REROUTE:    /* from TCRC */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * USE the linkSet.  TCRC has to tell us which path
         * controlled rerouting is for.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        rc->entries[whichEntry]->flags |= ROUTE_CONTROLLED_REROUTING;
        break;

    case SRM_TRIGGER_REM_STP_DEST:          /* from TSRC */
        /* only STPs perform this action */
        if (!STPFunction_CCITT())
        {
            return (ITS_SUCCESS);
        }

        /* build TFR, send */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Invalid incoming link set %d\n", linkSet));

            return (ITS_EINVALIDARGS);
        }

        /*
         * DON'T CARE which linkSet.  TSRC has to get this right.
         */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

        SNMM_HC0_SET(snmm, SNMM_HC0_TFM);
        SNMM_HC1_SET(snmm, SNMM_HC1_TFR);
        SNMM_TRANSFER_STATE_SET_DEST(snmm.data.transferState, pc1);

        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

        SNMM_Encode(&ev, &omtp3, &snmm);


        /* USE any available route */
        ret = HMRT_Main_CCITT(MTP3_SRM_RTRC,
                             SMH_TRIGGER_ROUTE_MGMT_MSG,
                             ev.data, ev.len,
                             ITS_SS7_DEFAULT_LINK_SET,
                             ITS_SS7_DEFAULT_LINK_CODE);

        ITS_EVENT_TERM(&ev);

        return (ret);

    case SRM_TRIGGER_T18:
        /* mark the timer stopped */
        pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this destination.
         * USE the linkSet.  It's what we sent to the timer
         * subsystem.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni, linkSet,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        /* status not maintained for this PC? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) == NULL)
        {
            MTP3_DEBUG(("FindBestMatch failed, return.\n"));

            return (ITS_EINVALIDARGS);
        }

        /* mark the timer stopped */
        rc->entries[whichEntry]->t18 = TIMER_BAD_SERIAL;
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
 *      Deal with congestion.
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
RTCC_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    MTP3_HEADER omtp3;
    SNMM_MESSAGE snmm, *isnmm;
    ITS_UINT pc1, pc2;
    ITS_EVENT ev;
    ROUTE_MatchInfo rinfo;
    SS7_Destination *rc;
    SS7_LinkPtr ln;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    ITS_BOOLEAN isLocal;
    ITS_OCTET ni, congLevel;
    int ret;

    ret = ITS_SUCCESS;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SRM_RTCC, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
         MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }


    switch (trigger)
    {
    case SRM_TRIGGER_TRANSFER_CONTROL:       /* from HMDT */
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER) +
                                     sizeof(ITS_OCTET)];
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
        /* Increament the peg for Transfer Control */
        PEG_IncrPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFC_RECEIVED);

        rc = ROUTE_FindDestination(pc1, ni, FAMILY_ITU);
        if (rc)
        {
            PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFC_RX);
        }

        /*
         * get the routing info for this destination.
         * DON'T USE the linkSet.  Use the normal route, as this is a destination
         * congesting.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));
 
            return (ITS_EINVALIDARGS);
        }

        /* if we maintain status for this PC? */
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) != NULL)
        {
            ret = TRCC_Main_CCITT(MTP3_SRM_RTCC,
                                 STM_TRIGGER_DEST_CONGESTION_STATUS,
                                 sif, len,
                                 linkSet, linkCode);

            return (ret);
        }
        else
        {
            MTP3_DEBUG(("Unable to parse destination %08x\n", pc1));

            MTP3_Alarm_CCITT(2477, __FILE__, __LINE__,"dpc %d ni %d",pc1,ni);
        }
        break;

    case SRM_TRIGGER_USER_PART_UNAVAIL:      /* from HMDT */
        return TSFC_Main_CCITT(MTP3_SRM_RTCC,
                              STM_TRIGGER_UPU,
                              sif, len,
                              linkSet, linkCode);

    case SRM_TRIGGER_SEND_TRANSFER_CONTROL:  /* from HMCG */
        /*
         * NOTE: the OPC is who to send the TFC to.  The DPC is the
         * congested destination.
         */
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
        pc2 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * get the routing info for this source.
         * DON'T USE the linkSet. The normal route is good enough, as we
         * are determining a destination to send to.  NOTE: The normal
         * route *MAY* be a local route.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc2,
                                          DONT_CARE, ROUTE_DPC_SIO,
                                          FAMILY_ITU,
                                          MTP3_HDR_GET_SIO(*mtp3),
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        /* 
         * destination congestion level stored on the normal route.
         */
        congLevel = 0;
        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) != NULL)
        {
            congLevel = rc->entries[whichEntry]->congLevel;
        }

        if (ROUTE_GetRouteContextInfoLocal(&rinfo, &isLocal) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("Message source unknown: %08x\n", pc1));

            isLocal = ITS_FALSE;
        }
                        
        if (isLocal)
        {
            MTP3_HDR_SET_SIO(omtp3, ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
        
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            /* linkSet is irrelevent */
            ret = TSFC_Main_CCITT(MTP3_SRM_RTCC,
                                 STM_TRIGGER_DEST_CONGESTION_STATUS,
                                 ev.data, ev.len,
                                 ITS_SS7_DEFAULT_LINK_SET,
                                 ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }
        else
        {
            /*
             * Get the routing info for the destination.  Don't
             * use the link set, use the normal route
             */
            if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc1,
                                              REMOTE_ROUTE, ROUTE_DPC_NI,
                                              FAMILY_ITU,
                                              ni,
                                              ITS_SS7_DEFAULT_LINK_SET,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_LINK_PRI,
                                              ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
            {
                MTP3_DEBUG(("Don't maintain status for that destination\n"));

                return (ITS_EINVALIDARGS);
            }

            /* if we maintain status for this PC? */
            if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                          &firstMatch, &lastMatch,
                                          &whichLinkCode,
                                          ITS_FALSE)) != NULL)
            {
                /* build TFC, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ni);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, pc1);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, rc->entries[whichEntry]->linkSet->lpc);

                SNMM_HC0_SET(snmm, SNMM_HC0_FCM);
                SNMM_HC1_SET(snmm, SNMM_HC1_TFC);
                SNMM_TRANSFER_CONTROL_SET_DEST(snmm.data.transferControl,
                                               pc2);
                SNMM_TRANSFER_CONTROL_SET_STATUS(snmm.data.transferControl,
                                                 congLevel);

                ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

                SNMM_Encode(&ev, &omtp3, &snmm);

                rc = ROUTE_FindDestination(pc1, ni, FAMILY_ITU);
                if (rc)
                {
                    PEG_IncrPeg(&rc->MTP3_DPC_PEGS, PEG_MTP3_DPC_TFC_TX);
                }

                /* USE any available route */
                ret = HMRT_Main_CCITT(MTP3_SRM_RTRC,
                                     SMH_TRIGGER_ROUTE_MGMT_MSG,
                                     ev.data, ev.len,
                                     ITS_SS7_DEFAULT_LINK_SET,
                                     ITS_SS7_DEFAULT_LINK_CODE);

                ITS_EVENT_TERM(&ev);

                return (ret);
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
 *      Deal with congestion testing.
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
RCAT_Main_CCITT(MTP3_SubSystems src, SRM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER *mtp3 = (MTP3_HEADER *)&sif[1];
    MTP3_HEADER omtp3;
    SNMM_MESSAGE snmm;
    ITS_UINT pc;
    ITS_OCTET ni, cl;
    ITS_EVENT ev;
    ROUTE_MatchInfo rinfo;
    SS7_Destination *rc;
    SS7_LinkPtr ln;
    int whichEntry, firstMatch, lastMatch, whichLinkCode;
    MTP3_TimerContext tc;
    int ret;

    MTP3_TRACE_ENTRY_CCITT(MTP3_SRM_RCAT, src, trigger, sif, len,
                           linkSet, linkCode);

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
       MTP3_DEBUG(("Link %d:%d not found\n", linkSet, linkCode));
    }


    switch (trigger)
    {
    case SRM_TRIGGER_START_CONG_TEST:        /* from TRCC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * status not maintained for this PC?
         * DON'T USE the linkSet.  It's the destination we care about,
         * not the route, so use the normal route.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) != NULL)
        {
            /* build RCT, send */
            cl = rc->entries[whichEntry]->congLevel;
            if (cl > 0)
            {
                cl--;
            }

            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM |
                                    rc->entries[whichEntry]->linkSet->ni |
                                    (cl << 4));
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, rc->entries[whichEntry]->linkSet->lpc);

            SNMM_HC0_SET(snmm, SNMM_HC0_FCM);
            SNMM_HC1_SET(snmm, SNMM_HC1_RCT);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
            SNMM_Encode(&ev, &omtp3, &snmm);


            /* send via any route */
            ret = HMRT_Main_CCITT(MTP3_SRM_RCAT,
                                 SMH_TRIGGER_ROUTE_MGMT_MSG,
                                 ev.data, ev.len,
                                 ITS_SS7_DEFAULT_LINK_SET,
                                 ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);

            /* start T16 */
            tc.timerId = MTP3_T16;
            tc.data.routeInfo.pointCode = pc;
            tc.data.routeInfo.linkSet = rc->entries[whichEntry]->linkSet->linkSet;
            tc.data.routeInfo.sio = ni;

            rc->entries[whichEntry]->t16 =
                TIMERS_StartSharedUTimer(ITS_MTP3_SRC,
                                   __ccitt_t16 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
            MTP3_DEBUG(("MTP3 START T16 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t16));
            return (ret);
        }
 
        break;

    case SRM_TRIGGER_CONG_TEST:              /* from HMDT */
        /* discard message */
        break;

    case SRM_TRIGGER_STOP_CONG_TEST:         /* from TRCC */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * status not maintained for this PC?
         * DON'T USE the linkSet.  It's the destination we care about,
         * not the route, so use the normal route.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) != NULL)
        {
            /* if T16 running, stop T16 */
            if (rc->entries[whichEntry]->t16 != TIMER_BAD_SERIAL)
            {
                MTP3_DEBUG(("MTP3 CANCEL T16 Timer SERIAL [%d]\n",rc->entries[whichEntry]->t16));
                TIMERS_CancelSharedTimer(rc->entries[whichEntry]->t16);
                rc->entries[whichEntry]->t16 = TIMER_BAD_SERIAL;
            }
        }
        break;

    case SRM_TRIGGER_T16:                    /* from timer control */
        pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
        ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

        /*
         * status not maintained for this PC?
         * DON'T USE the linkSet.  It's the destination we care about,
         * not the route, so use the normal route.
         */
        if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                          REMOTE_ROUTE, ROUTE_DPC_NI,
                                          FAMILY_ITU,
                                          ni,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_LINK_PRI,
                                          ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
        {
            MTP3_ERROR(("Couldn't parse routing info\n"));

            return (ITS_EINVALIDARGS);
        }

        if ((rc = ROUTE_FindBestMatch(&rinfo, &whichEntry,
                                      &firstMatch, &lastMatch,
                                      &whichLinkCode,
                                      ITS_FALSE)) != NULL)
        {
            rc->entries[whichEntry]->t16 = TIMER_BAD_SERIAL;

            MTP3_HDR_SET_SIO(omtp3, ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc);

            ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);
    
            MTP3_Encode(&ev, MTP3_MSG_USER_DATA,
                        &omtp3, NULL, 0);

            /* the linkSet is irrelevent */
            ret = TRCC_Main_CCITT(MTP3_SRM_RCAT,
                                 STM_TRIGGER_DECR_DEST_CONG_STATUS,
                                 ev.data, ev.len,
                                 ITS_SS7_DEFAULT_LINK_SET,
                                 ITS_SS7_DEFAULT_LINK_CODE);

            ITS_EVENT_TERM(&ev);
        }

        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(CCITT_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
}
