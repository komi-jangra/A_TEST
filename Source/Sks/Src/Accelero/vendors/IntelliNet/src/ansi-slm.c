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
 *  ID: $Id: ansi-slm.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $  
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
 * LOG: Revision 9.1  2005/03/23 12:54:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:53:35  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.7.2.2.8.3.8.2  2005/01/25 11:34:26  snagesh
 * LOG: OAM Bug fixes for bugs 1419,1420
 * LOG:
 * LOG: Revision 7.7.2.2.8.3.8.1  2004/12/31 06:49:07  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.7.2.2.8.3  2004/09/07 05:17:54  sswami
 * LOG: Fix after text changes for alert 2128
 * LOG:
 * LOG: Revision 7.7.2.2.8.2  2004/09/03 09:28:52  sswami
 * LOG: Fix given for text changes for alarms 2109,2106 & 2105
 * LOG:
 * LOG: Revision 7.7.2.2.8.1  2004/08/10 12:14:45  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.7.2.2  2003/02/21 01:42:34  randresol
 * LOG: Add more alarms
 * LOG:
 * LOG: Revision 7.7.2.1  2003/02/18 02:35:01  randresol
 * LOG: Issue "Out of Service" alarm when a link goes down
 * LOG:
 * LOG: Revision 7.7  2003/02/13 10:23:00  ttipatre
 * LOG: New Alarms added.
 * LOG:
 * LOG: Revision 7.6  2002/12/24 07:39:24  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.5  2002/12/03 20:57:07  randresol
 * LOG: Make sure the link is STOPped when COO/ECO is received.
 * LOG:
 * LOG: Revision 7.4  2002/11/20 05:08:59  ttipatre
 * LOG: Alarms and Pegs code submission.
 * LOG:
 * LOG: Revision 7.3  2002/11/10 19:48:27  randresol
 * LOG: Remove Shared Timers for SLT's
 * LOG:
 * LOG: Revision 7.2  2002/11/09 22:07:13  randresol
 * LOG: Solve link stability problem after a deactivation/actication
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
 * LOG: Revision 5.38  2001/12/11 23:49:52  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.37  2001/12/06 22:39:04  mmiers
 * LOG: First cut of ITU MTP3.
 * LOG:
 * LOG: Revision 5.36  2001/11/29 23:43:24  mmiers
 * LOG: All config A tests passed (by kicking the INET).
 * LOG:
 * LOG: Revision 5.35  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.34  2001/11/14 23:17:13  mmiers
 * LOG: Many changes from conformance testing.
 * LOG:
 * LOG: Revision 5.33  2001/11/13 16:13:44  vnitin
 * LOG: fixed mgmt activate link and deactivate link
 * LOG:
 * LOG: Revision 5.32  2001/11/01 20:41:01  mmiers
 * LOG: A few fixes.
 * LOG:
 * LOG: Revision 5.31  2001/11/01 20:22:06  vnitin
 * LOG: isUp and TCOC fixes
 * LOG:
 * LOG: Revision 5.30  2001/10/30 00:16:10  mmiers
 * LOG: Today's debugging session.  Looks close.
 * LOG:
 * LOG: Revision 5.29  2001/10/26 17:40:12  mmiers
 * LOG: Bug fixes for pulling the plug.
 * LOG:
 * LOG: Revision 5.28  2001/10/22 21:18:21  rsonak
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
#include <its_timers.h>
#include <its_assertion.h>

#ident "$Id: ansi-slm.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $"

#include <ansi/snmm.h>
#include <ansi/sltm.h>
#include <ansi/mtp3.h>

#include "mtp3_intern.h"

static ITS_BOOLEAN  optionA = ITS_TRUE;
static ITS_BOOLEAN  optionB = ITS_FALSE;
extern ITS_USHORT linkTransportMapDB[MAX_LINKSETS][MAX_LINKS_PER_LINKSET];
extern ITS_UINT PEER_MTP3_NODE_STATUS;
/*
 * this is left to the discretion of the MTP2 implementation.
 */
#define MTP2_RETRIEVAL_IN_PARALLEL  0
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
SLM_Main_ANSI(MTP3_SubSystems src, MTP3_SubSystems dest,
              SLM_Triggers trigger,
              ITS_OCTET *sif, ITS_USHORT len,
              ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SNMM_MESSAGE *snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER_ANSI) +
                                              sizeof(ITS_OCTET)];

    MTP3_TRACE_ENTRY_ANSI(MTP3_SLM, src, trigger, sif, len,
                          linkSet, linkCode);


    if (trigger == SLM_TRIGGER_L2_MSG)
    {
        switch (SNMM_HC0_GET_ANSI(*snmm))
        {
        case SNMM_HC0_DLM_ANSI:
            switch (SNMM_HC1_GET_ANSI(*snmm))
            {
            case SNMM_HC1_DLC_ANSI:
                /* data link connection order */
                LSDA_Main_ANSI(src, SLM_TRIGGER_CONNECTION_ORDER,
                               sif, len,
                               linkSet, linkCode);
                break;

            case SNMM_HC1_CSS_ANSI:
                /* connection successful */
                LSDA_Main_ANSI(src, SLM_TRIGGER_CONNECTION_SUCCESSFUL,
                               sif, len,
                               linkSet, linkCode);
                break;

            case SNMM_HC1_CNS_ANSI:
                /* connection not successful */
                LSDA_Main_ANSI(src, SLM_TRIGGER_CONNECTION_UNSUCCESS,
                               sif, len,
                               linkSet, linkCode);
                break;

            case SNMM_HC1_CNP_ANSI:
                /* connection not possible */
                LSDA_Main_ANSI(src, SLM_TRIGGER_CONNECTION_NOT_POSS,
                               sif, len,
                               linkSet, linkCode);
                break;

            default:
                MTP3_DEBUG(("Unknown HC1 code %x\n",
                            SNMM_HC1_GET_ANSI(*snmm)));
                PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
                break;
            }
            break;
        }
    }

    MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
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
 ****************************************************************************/
int
LLSC_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln=NULL;
    SS7_LinkPtr lnk=NULL;
    ITS_UINT i, j, k;
    int cnt;
    static ITS_BOOLEAN starting = ITS_TRUE;
    /* Default Loop optimization changes start*/
    ITS_UINT lscount=0;
    ITS_OCTET linkset[255];
    /* Default Loop optimization changes end*/

    MTP3_TRACE_ENTRY_ANSI(MTP3_SLM_LLSC, src, trigger, sif, len,
                          linkSet, linkCode);

    switch (trigger)
    {
    case SLM_TRIGGER_ACTIVATE_LINK_SET:      /* from MGMT */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Failed to find link set\n"));
 
            MTP3_Alarm_ANSI(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);

            return (ITS_EINVALIDARGS);
        }

        if (ls->numToStart == 0 ||
            ls->numToStart > ls->numLinks)
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

                LSAC_Main_ANSI(MTP3_SLM_LLSC,
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
        /* Default Loop optimization changes start*/
        //for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
        //MTP3_ERROR((" linkTransportMapDB %s %d\n",__FILE__,__LINE__));
        for (i = 0; i < MAX_LINKSETS; i++)
         {
          for(j = 0;j < MAX_LINKS_PER_LINKSET ;j++)
          {
            if(linkTransportMapDB[i][j] >0) 
             {  
              // MTP3_ERROR((" linkTransportMapDB[%d][%d]=%d\n",i,j,linkTransportMapDB[i][j]));
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
        /* Default Loop optimization changes end*/
        for (k = 0; k < lscount; k++)
        {
            if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkset[k])) == NULL ||
                ls->adjacent == 0)
            {
                continue;
            }

            if (ls->numToStart == 0 ||
                ls->numToStart > ls->numLinks)
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

                    LSAC_Main_ANSI(MTP3_SLM_LLSC,
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

            MTP3_Alarm_ANSI(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);

            return (ITS_EINVALIDARGS);
        }

        for (i = 0; i < ls->numLinks; i++)
        {
            ln = ls->links[i];

            /* select links to deactivate */
            if (ln->isUp)
            {
                LSAC_Main_ANSI(MTP3_SLM_LLSC,
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

            MTP3_Alarm_ANSI(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);

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
        MTP3_ERROR(("Value of j = %d numToStart= %d cnt %d",j,ls->numToStart,((int)ls->numLinks - 1)));

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
                    MTP3_ERROR(("Before LSAC_Main_ANSI Call for ls|lc %d|%d ",ls->linkSet,ls->links[cnt]->linkCode));
                    LSAC_Main_ANSI(MTP3_SLM_LLSC,
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
				MTP3_DEBUG(("FILE %s LINE %d SLM_TRIGGER_LINK_FAILED\n",__FILE__,__LINE__));
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Failed to find link set\n"));

            MTP3_Alarm_ANSI(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);

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
/* REDUNDANCY CHANGES START HERE *****/

                if ((lnk = LINK_FindLink(linkSet,ln->linkCode)) == NULL)
                   {
                         MTP3_ERROR(("Link %d:%d not found\n", linkSet, ln->linkCode));
                         return (ITS_EINVALIDARGS);
                   }

                MTP3_ERROR(("!!!!!ln->id %d Code %d!!!!!\n",lnk->id,ln->linkCode));
	        if(lnk->id == 20002)
		{
		  MTP3_ERROR(("\nLink is For Internode \n"));
                  continue;
		}

/* REDUNDANCY CHANGES ENDS HERE *****/
                /* select links to activate */
                if (ls->links[i]->initActive)
                {
                    MTP3_ERROR(("After change over default link activation for linkcode %d\n",i));
#if 0
/* sandeep As not activated link are getting activated by outofservice of the Other link in the link set*/
                    LSAC_Main_CCITT(MTP3_SLM_LLSC,
                                   SLM_TRIGGER_ACTIVATE_LINK,
                                   NULL, 0,
                                   ls->linkSet, ln->linkCode);
#endif

                }
            }
        }
        break;

    case SLM_TRIGGER_ACTIVATE_ANOTHER_LINK:  /* from LSAC */
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
        {
            MTP3_ERROR(("Failed to find link set\n"));

	          MTP3_Alarm_ANSI(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);
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
                    return LSAC_Main_ANSI(MTP3_SLM_LLSC,
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
                
                MTP3_Alarm_ANSI(2423, __FILE__, __LINE__, "The LinkSet is %x", linkSet);

                return (ITS_EINVALIDARGS);
            }

            for (i = 0; i < ls->numLinks; i++)
            {
                ln = ls->links[i];

                LSAC_Main_ANSI(MTP3_SLM_LLSC,
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

                MTP3_Alarm_ANSI(2423, __FILE__, __LINE__, "LinkSet %x not found", linkSet);
                return (ITS_EINVALIDARGS);
            }

            for (i = 0; i < ls->numLinks; i++)
            {
                ln = ls->links[i];

                LSAC_Main_ANSI(MTP3_SLM_LLSC,
                               SLM_TRIGGER_EMERGENCY_CEASES,
                               NULL, 0,
                               ls->linkSet, ln->linkCode);
            }
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
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
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * snagesh   04-04-2005  ACC651-SDS-MTPL-1.0.02  Added handling of SLM triggers
 *                       ID::D0010               for LPO feature                                              
 *
 ****************************************************************************/
int
LSAC_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    MTP3_TimerContext tc;
    SS7_LinkSetPtr ls;   /* Magesh 28-June-06 */
    ITS_BOOLEAN LINKSET_STATUS = ITS_FALSE;
    int i=0;

    MTP3_TRACE_ENTRY_ANSI(MTP3_SLM_LSAC, src, trigger, sif, len,
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
         MTP3_ERROR(("ln->activityState = %d linkSet|linkCode %d|%d",ln->activityState,linkSet,linkCode));
        /*if (ln->activityState == LINK_ACTIVITY_INACTIVE)Sandeep changed due to mi_deact_command changed*/
        if (ln->activityState == LINK_ACTIVITY_INACTIVE||ln->activityState==LINK_ACTIVITY_DEACTIVE)
        {
            ln->activityState = LINK_ACTIVITY_ACTIVATING_RESTORING;

            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_ACTIVATION);
            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_ACTIVATION);

            LSLA_Main_ANSI(MTP3_SLM_LSAC,
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
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t32 * USEC_PER_MILLISEC,
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
            LSLR_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_RESTART_RESTORATION,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_L2_IN_SERVICE:          /* from L2 */
	
        MTP3_Alarm_ANSI(2527, __FILE__, __LINE__,NULL);
        if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
          {
              MTP3_ERROR(("Failed to find link set\n"));
                return (ITS_EINVALIDARGS);
          }



        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            ln->activityState = LINK_ACTIVITY_ACTIVE;

            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_IN_SERVICE);
            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_IN_SERVICE);
            /*change for Link OUT OF SERVICE Alarm*/
            for (i = 0; i < ls->numLinks; i++)
            {
               MTP3_DEBUG(("Link %d  ls->links[i]->isUp %d \n",i,ls->links[i]->isUp));
               if(ls->links[i]->isUp!=ITS_FALSE)
               {
                 MTP3_DEBUG(("Link set %d already in In Service\n",ls->linkSet));
                 LINKSET_STATUS = ITS_TRUE;
               }
            }

           if(LINKSET_STATUS == ITS_FALSE &&  ls->numLinks !=0)
            {
              MTP3_ERROR(("Link set %d In Service\n",ls->linkSet));
             /*Generation Of Alarm*/
             MTP3_Alarm_ANSI(2801, __FILE__, __LINE__, "LinkSet %d IN Service", ls->linkSet);

            }
         /*End fo Changes*/

            if (optionB)
            {
                /* start T33 */
                tc.timerId = MTP3_T33;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t33 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t33 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));
            }

            ln->isUp = ITS_TRUE;
            MTP3_ERROR(("ln->isUp = ITS_TRUE\n"));

            /* stop T19 */
            TIMERS_CancelSharedTimer(ln->t19);
            ln->t19 = TIMER_BAD_SERIAL;

            /*
             * I believe this belongs in SLT.
             */
#if 0
            TLAC_Main_ANSI(MTP3_SLM_LSAC,
                           STM_TRIGGER_LINK_IN_SERVICE,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_ACTIVE,
                           NULL, 0,
                           linkSet, linkCode);
#endif

           MTP3_Alarm_ANSI(2528, __FILE__, __LINE__,
                   "linkset:linkcode %x:%x",
                   linkSet,linkCode);


            /* start the link test */
            SLTC_Main_ANSI(MTP3_SLM_LSAC,
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

            TLAC_Main_ANSI(MTP3_SLM_LSAC,
                           STM_TRIGGER_RP_OUTAGE,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_ACTIVE,
                           NULL, 0,
                           linkSet, linkCode);

            ln->slFlags &= ~(LINK_FIRST_FAILURE|
                             LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL);
        }
        else if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            TLAC_Main_ANSI(MTP3_SLM_LSAC,
                           STM_TRIGGER_RP_OUTAGE,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_LP_OUTAGE:                 /* from MGMT */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            ln->activityState = LINK_ACTIVITY_ACTIVE;

            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_LOCAL_PROCESSOR_OUT, NULL, 0);

            TLAC_Main_ANSI(MTP3_SLM_LSAC,
                           STM_TRIGGER_LP_OUTAGE,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_ACTIVE,
                           NULL, 0,
                           linkSet, linkCode);

            ln->slFlags &= ~(LINK_FIRST_FAILURE|
                             LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL);

        }
        else if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_LOCAL_PROCESSOR_OUT, NULL, 0);

            TLAC_Main_ANSI(MTP3_SLM_LSAC,
                           STM_TRIGGER_LP_OUTAGE,
                           NULL, 0,
                           linkSet, linkCode);

        }
        break;

    case SLM_TRIGGER_LP_RECOVERD:                 /* from MGMT */
        if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            
            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_LOCAL_PROCESSOR_REC, NULL, 0);

            TLAC_Main_ANSI(MTP3_SLM_LSAC, STM_TRIGGER_LP_RECOVERD,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_L2_OUT_OF_SERVICE:      /* from L2 */
        MTP3_Alarm_ANSI(2509, __FILE__, __LINE__, "linkset:linkcode  %x:%x",
                        linkSet, linkCode);

          /*change for LinkSet Out Service Alarm*/
          if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
            {
                MTP3_ERROR(("Failed to find link set\n"));
                return (ITS_EINVALIDARGS);
            }

        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            ln->testPassed = ITS_FALSE;
          /*************Sandeep Code Change starts********
           As activity state is LINK_ACTIVITY_ACTIVATING_RESTORING and we are nor marking link 
           failed as it is not in INSERVICE state stFlags need to be updated so as to overcome 
           Adjacent SPRestart leg work through*/ 
            ln->stFlags |= LINK_FAILED;
          /*************Sandeep Code Change Ends********/


            if (ln->slFlags & LINK_FIRST_FAILURE)
            {
                /* terminal available to LSTA */
                LSTA_Main_ANSI(MTP3_SLM_LSAC,
                               SLM_TRIGGER_TERMINAL_AVAILABLE,
                               NULL, 0,
                               linkSet, linkCode);

                ln->slFlags &= ~LINK_FIRST_FAILURE;
                MTP3_ERROR(("SANDEEP LINK_FIRST_FAILURE slFlags LINK_TERMINAL_AVAILABLE\n"));
            }
            else
            {
                ln->slFlags |= LINK_FIRST_FAILURE;
            }

            if (ln->slFlags & LINK_IS_ACTIVATING)
            {
                MTP3_ERROR(("SANDEEP slFlag LINK_IS_ACTIVATING"));
                LSLA_Main_ANSI(MTP3_SLM_LSAC,
                               SLM_TRIGGER_RESTART_ACTIVATION,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLR_Main_ANSI(MTP3_SLM_LSAC,
                               SLM_TRIGGER_RESTART_RESTORATION,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        else if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP3_TimerContext tc;


            ln->testPassed = ITS_FALSE;
            ln->isUp = ITS_FALSE;
            MTP3_DEBUG(("ln->isUp = ITS_FALSE\n"));

            PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_OUT_OF_SERVICE);
            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_OUT_OF_SERVICE);
	    

#if !MTP2_RETRIEVAL_IN_PARALLEL
            MTP3_ERROR(("SANDEEP activityState LINK_ACTIVITY_ACTIVE->LINK_ACTIVITY_FAILED marking slFlags|LINK_FIRST_FAILURE"));
            ln->activityState = LINK_ACTIVITY_FAILED;
            MTP3_DEBUG(("ln->activityState = LINK_ACTIVITY_FAILED\n"));
#endif

            ln->slFlags |= LINK_FIRST_FAILURE;
            MTP3_DEBUG(("Link state LINK_ACTIVITY_ACTIVE"));

            /* start T19 */
            tc.timerId = MTP3_T19;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            ln->t19 =
                TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                   __ansi_t19 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));

            TLAC_Main_ANSI(MTP3_SLM_LSAC,
                           STM_TRIGGER_LINK_FAILED,
                           NULL, 0,
                           linkSet, linkCode);

//            ln->isUp = ITS_FALSE;

            LLSC_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_FAILED,
                           NULL, 0,
                           linkSet, linkCode);
            /*change for Link OUT OF SERVICE Alarm*/
            MTP3_DEBUG(("Link set %d has numlinks %d\n",ls->linkSet,ls->numLinks));
            for (i = 0; i < ls->numLinks; i++)
            {
              MTP3_DEBUG(("Link i %d ls->links[i]->isUp  %d \n",i,ls->links[i]->isUp));
              if(ls->links[i]->isUp!=ITS_FALSE)
              {
                 MTP3_DEBUG(("Link set %d is not Out of Service\n",ls->linkSet));
                 LINKSET_STATUS = ITS_TRUE;
              }
            }

           if(LINKSET_STATUS == ITS_FALSE &&  ls->numLinks !=0)
            {
                MTP3_ERROR(("Link set %d Out of Service\n",ls->linkSet));
             /*Generation Of Alarm*/
             MTP3_Alarm_ANSI(2800, __FILE__, __LINE__, "LinkSet %d Out of Service", ls->linkSet);

            }
         /*End fo Changes*/

            /* optional: if retrieval cannot be carried out in parallel
             * with signalling link restoration */
#if MTP2_RETRIEVAL_IN_PARALLEL
            MTP3_DEBUG(("activityState  LINK_ACTIVITY_FAILED \n"));
            goto STM_Ready;
#endif
        }
        else
           {
              MTP3_DEBUG(("OUT_OF_SERVICE   ln->activityState %d\n",ln->activityState));
           }
        break;

    case SLM_TRIGGER_START_LINK:             /* from LSLA: from LSLR */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            MTP3_CRITICAL(("Going to Start T17  LINK_ACTIVITY_ACTIVATING_RESTORING \n"));
            MTP3_TimerContext tc;

            ln->activityState = LINK_ACTIVITY_WAIT_1;

            /* start T17 */
            tc.timerId = MTP3_T17;
            tc.data.linkInfo.linkSet = linkSet;
            tc.data.linkInfo.linkCode = linkCode;

            MTP3_DEBUG(("T17 started for %d:%d __ansi_t17 %d\n", linkSet, linkCode,__ansi_t17));

            MTP3_Alarm_ANSI(2505, __FILE__, __LINE__,
                           "Alignment started for linkset:linkcode %x:%x", linkSet, linkCode);

            ln->t17 =
                TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                   __ansi_t17 * USEC_PER_MILLISEC,
                                   &tc, sizeof(MTP3_TimerContext));
             /***************sandeep changes for Redundancy ***************/
                //LINK_CommitLink(ln);
            /***************sandeep changes for Redundancy Ends ***************/
        }
        else if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING && ln->id == 20002 && PEER_MTP3_NODE_STATUS == 1)
        {
             MTP3_CRITICAL((" No Need to Start T17  LINK_ACTIVITY_ACTIVATING_RESTORING \nDeactivate ls|lc %d|%d\n",linkSet,linkCode));
             LSAC_Main_CCITT(MTP3_MGMT,SLM_TRIGGER_DEACTIVATE_LINK,NULL, 0,(ITS_OCTET)linkSet,(ITS_OCTET)linkCode);
        }
        else
        {
              MTP3_CRITICAL((" SLM_TRIGGER_START_LINK ln-activityState = %d \n",ln->activityState));
        }
        break;

    case SLM_TRIGGER_T17:
					MTP3_DEBUG(("trigger %d ln->activityState %d \n",trigger,ln->activityState));
        if (ln->activityState == LINK_ACTIVITY_WAIT_1)
        {
            ln->activityState = LINK_ACTIVITY_ACTIVATING_RESTORING;

            if (ln->slFlags & LINK_EMERGENCY)
            {
                MTP2_SendData_ANSI(linkSet, linkCode,
                                   L3_L2_EMERGENCY, NULL, 0);
            }

            MTP3_Alarm_ANSI(2506, __FILE__, __LINE__,
                           "T17 Expired for linkset:linkcode %x:%x", linkSet, linkCode);   

					  MTP3_ERROR(("START trigger %d ln->activityState %d \n",trigger,ln->activityState));
            MTP2_SendData_ANSI(linkSet, linkCode,
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
                MTP3_ERROR(("LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL ACTIVATE ANOTHER LINK \n"));
                LLSC_Main_ANSI(MTP3_SLM_LSAC,
                               SLM_TRIGGER_ACTIVATE_ANOTHER_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        break;

    case SLM_TRIGGER_T19:                    /* from timer control */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            MGMT_Main_ANSI(MTP3_SLM_LSAC,
                           MGMT_TRIGGER_LINK_ACTIVATION_FAIL,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_ANSI(MTP3_SLM_LSAC,
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
       /* FIX:  ln->testPassed must be set to false.
          this fix solve the problem of deactivating and reactivating 
          a link from our stack
       */
          /*change for LinkSet Out Service Alarm*/
          if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
            {
                MTP3_ERROR(("Failed to find link set\n"));
                return (ITS_EINVALIDARGS);
            }
        ln->testPassed = ITS_FALSE;

        PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_DEACTIVATION); 
        PEG_ClearPeg(ANSI_MTP3_Pegs, PEG_MTP3_LINK_DEACTIVATION);

        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING)
        {
            MTP3_ERROR(("Deactivating a LINK NOT  IN_SERVICE LINK_ACTIVITY_ACTIVATING_RESTORING ->> LINK_ACTIVITY_INACTIVE\n"));
            /*Sandeep Changes for deactivation Command Start here*/
            if(src!=MTP3_MGMT)
	           {
	             ln->activityState = LINK_ACTIVITY_INACTIVE;
	           }
	          else
	           {
              /*change due to link down form mi_deact_lik cmd*/ 
                  ln->activityState = LINK_ACTIVITY_DEACTIVE;
             }
            /*Sandeep Changes for deactivation Command ends here*/

            MTP2_SendData_ANSI(linkSet, linkCode, L3_L2_STOP, NULL, 0);


            LSLD_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_DEACTIVATE_LINK,
                           NULL, 0,
                           linkSet, linkCode);

            LSLA_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_DEACTIVATE_LINK,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_INACTIVE,
                           NULL, 0,
                           linkSet, linkCode);

            if (ln->slFlags & LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL)
            {
                ln->slFlags &= ~LINK_ACTIVATION_RESTORATION_UNSUCCESSFUL;
            }
            else
            {
                MTP3_ERROR((" Deactivating Trying to activate another link when deactivating from link not IN_SERVICE\n"));
                /*Sandeep No need to activate any link in a linkset as link activation is taken care by the self
                
                LLSC_Main_ANSI(MTP3_SLM_LSAC,
                               SLM_TRIGGER_ACTIVATE_ANOTHER_LINK,
                               NULL, 0,
                               linkSet, linkCode); */
            }
        }
        else if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP3_ERROR(("Deactivating a already IN_SERVICE LINK\n"));
            if (src == MTP3_MGMT)
            {
                MTP3_ERROR((" Deactivating Trying to activate another link when deactivating from link  IN_SERVICE\n"));
                /*Sandeep No need to activate another link as we shall be taking care of link activation/deactivation*/
               /* LLSC_Main_ANSI(MTP3_SLM_LSAC,
                               SLM_TRIGGER_ACTIVATE_ANOTHER_LINK,
                               NULL, 0,
                               linkSet, linkCode);*/
            }

            MTP2_SendData_ANSI(linkSet, linkCode, L3_L2_STOP, NULL, 0);
            /*requirement for OMC*/
            MTP3_Alarm_ANSI(2509, __FILE__, __LINE__, "linkset:linkcode %d:%d", linkSet, linkCode);

            TLAC_Main_ANSI(MTP3_SLM_LSAC,
                           STM_TRIGGER_LINK_FAILED,
                           NULL, 0,
                           linkSet, linkCode);

            ln->isUp = ITS_FALSE;

            /*change for Link OUT OF SERVICE Alarm*/
            MTP3_DEBUG(("Link set %d has numlinks %d\n",ls->linkSet,ls->numLinks));
            for (i = 0; i < ls->numLinks; i++)
            {
              if(ls->links[i]->isUp!=ITS_FALSE )
              {
                 MTP3_DEBUG(("Link set %d is not Out of Service\n",ls->linkSet));
                 LINKSET_STATUS = ITS_TRUE;
              }
            }

           if(LINKSET_STATUS == ITS_FALSE &&  ls->numLinks !=0)
            {
                MTP3_ERROR(("Link set %d Out of Service\n",ls->linkSet));
             /*Generation Of Alarm*/
             MTP3_Alarm_ANSI(2800, __FILE__, __LINE__, "LinkSet %d Out of Service", ls->linkSet);

            }
         /*End fo Changes*/

            if (ln->slFlags & LINK_LOADED)
            {
               MTP3_ERROR(("Deactivating link is loaded  IN_SERVICE\n"));
               ln->activityState = LINK_ACTIVITY_WAIT_4;
                if (src == MTP3_MGMT)
                {
                  ln->activityState = LINK_ACTIVITY_DEACTIVE;
                }
            }
            else
            {
                LLSC_Main_ANSI(MTP3_SLM_LSAC,
                               SLM_TRIGGER_LINK_FAILED,
                               NULL, 0,
                               linkSet, linkCode);

                LSLD_Main_ANSI(MTP3_SLM_LSAC,
                               SLM_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               linkSet, linkCode);

                LLSC_Main_ANSI(MTP3_SLM_LSAC,
                               SLM_TRIGGER_LINK_INACTIVE,
                               NULL, 0,
                               linkSet, linkCode);
                MTP3_ERROR(("SANDEEP Deactivating LINK_ACTIVITY_ACTIVE ->> LINK_ACTIVITY_INACTIVE  IN_SERVICE\n"));
               if (src == MTP3_MGMT)
	             {
		             ln->activityState = LINK_ACTIVITY_DEACTIVE;
	             }
	            else
	             {
                ln->activityState = LINK_ACTIVITY_INACTIVE;
               }
            }
        }
        break;

    case SLM_TRIGGER_RESUME:                 /* from TLAC */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING ||
            ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP2_SendData_ANSI(linkSet, linkCode, L3_L2_RESUME,
                               NULL, 0);
        }
        break;

    case SLM_TRIGGER_CLEAR_BUFFERS:          /* from TLAC */
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING ||
            ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP2_SendData_ANSI(linkSet, linkCode, L3_L2_CLEAR_BUFFERS,
                               NULL, 0);
        }
        break;

    case SLM_TRIGGER_STM_READY:
       MTP3_DEBUG(("OUT OF SERVICE for linkset %d ,linkcode %d\n", linkSet,linkCode));
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
                    MTP3_DEBUG(("T32 Have Started for  linkset %d ,linkcode %d\n", linkSet,linkCode)); 
                    /* start T32 */
                    tc.timerId = MTP3_T32;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = linkCode;

                    ln->t32 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                           __ansi_t32 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    /* mark link restoring */
                    ln->slFlags |= LINK_IS_RESTORING;

                    /* cancel T32 stopped */

                    LSLR_Main_ANSI(MTP3_SLM_LSAC,
                                   SLM_TRIGGER_START_RESTORATION,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
                else
                {
                     MTP3_DEBUG(("T32 not available for  linkset %d ,linkcode%d\n", linkSet,linkCode));
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
                        TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                           __ansi_t32 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    /* cancel T33 stopped */
                }
                else
                {
                    LSLR_Main_ANSI(MTP3_SLM_LSAC,
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

            LLSC_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_FAILED,
                           NULL, 0,
                           linkSet, linkCode);

            LSLD_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_DEACTIVATE_LINK,
                           NULL, 0,
                           linkSet, linkCode);

            LLSC_Main_ANSI(MTP3_SLM_LSAC,
                           SLM_TRIGGER_LINK_INACTIVE,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_CHANGEOVER_ORDER:       /* from TLAC */
    case SLM_TRIGGER_CHANGEOVER_ORDER_RECVD:
        if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_STOP, NULL, 0);
        }
        break;

    case SLM_TRIGGER_L2_RPR:                 /* from L2 */
        if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            TLAC_Main_ANSI(MTP3_SLM_LSAC, STM_TRIGGER_RP_RECOVERD,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_RB_CLEARED:
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING ||
            ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            TLAC_Main_ANSI(MTP3_SLM_LSAC,
                           STM_TRIGGER_RB_CLEARED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_RTB_CLEARED:
        if (ln->activityState == LINK_ACTIVITY_ACTIVATING_RESTORING ||
            ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            TLAC_Main_ANSI(MTP3_SLM_LSAC,
                           STM_TRIGGER_RTB_CLEARED,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_CLEAR_RTB:              /* from TLAC */
        if (ln->activityState == LINK_ACTIVITY_ACTIVE)
        {
            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_CLEAR_RTB, NULL, 0);
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
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

    if (MTP3_ANSI_AutomaticTerminalAllocation)
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

    if (MTP3_ANSI_AutomaticDataLinkAllocation)
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
LSLA_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;

    MTP3_TRACE_ENTRY_ANSI(MTP3_SLM_LSLA, src, trigger, sif, len,
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
                MTP2_SendData_ANSI(linkSet, linkCode, L3_L2_CONNECT, NULL, 0);

                LSAC_Main_ANSI(MTP3_SLM_LSLA,
                               SLM_TRIGGER_START_LINK,
                               NULL, 0,
                               linkSet, linkCode);

                ln->slFlags &= ~(LINK_TERMINAL_DETERMINED|
                                 LINK_DATA_LINK_DETERMINED);
            }
            else
            {
                ln->activationState = LINK_ACTIVATION_WAIT_1;

                LSTA_Main_ANSI(MTP3_SLM_LSLA,
                               SLM_TRIGGER_DETERMINE_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);

                if (!DataLinkPredetermined(ln))
                {
                    LSDA_Main_ANSI(MTP3_SLM_LSLA,
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
                MTP3_ERROR(("ActivationState  LINK_ACTIVATION_IDLE -> LINK_ACTIVATION_WAIT_2\n"));
                LSDA_Main_ANSI(MTP3_SLM_LSLA,
                               SLM_TRIGGER_DETERMINE_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                MTP3_ERROR(("ActivationState  LINK_ACTIVATION_IDLE -> LINK_ACTIVATION_WAIT_2\n"));
                LSAC_Main_ANSI(MTP3_SLM_LSLA,
                               SLM_TRIGGER_ACTIVATION_UNSUCCESS,
                               NULL, 0,
                               linkSet, linkCode);

                LSAC_Main_ANSI(MTP3_SLM_LSLA,
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

                MTP2_SendData_ANSI(linkSet, linkCode,
                                   L3_L2_CONNECT, NULL, 0);

                LSAC_Main_ANSI(MTP3_SLM_LSLA,
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

            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_CONNECT, NULL, 0);

            LSAC_Main_ANSI(MTP3_SLM_LSLA,
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

            LSAC_Main_ANSI(MTP3_SLM_LSLA,
                           SLM_TRIGGER_NOT_POSSIBLE,
                           NULL, 0,
                           linkSet, linkCode);

            ln->slFlags &= ~(LINK_TERMINAL_DETERMINED|
                           LINK_DATA_LINK_DETERMINED);
        }
        else if (ln->activationState == LINK_ACTIVATION_WAIT_2)
        {
            ln->activationState = LINK_ACTIVATION_IDLE;

            LSAC_Main_ANSI(MTP3_SLM_LSLA,
                           SLM_TRIGGER_ACTIVATION_UNSUCCESS,
                           NULL, 0,
                           linkSet, linkCode);

            LSAC_Main_ANSI(MTP3_SLM_LSLA,
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

                MTP2_SendData_ANSI(linkSet, linkCode,
                                   L3_L2_CONNECT, NULL, 0);

                LSAC_Main_ANSI(MTP3_SLM_LSLA,
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

            LSAC_Main_ANSI(MTP3_SLM_LSLA,
                           SLM_TRIGGER_NOT_POSSIBLE,
                           NULL, 0,
                           linkSet, linkCode);

            ln->slFlags &= ~(LINK_TERMINAL_DETERMINED|
                           LINK_DATA_LINK_DETERMINED);
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
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
LSLR_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;

    MTP3_TRACE_ENTRY_ANSI(MTP3_SLM_LSLR, src, trigger, sif, len,
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
            LSAC_Main_ANSI(MTP3_SLM_LSLR,
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

                LSTA_Main_ANSI(MTP3_SLM_LSLR,
                               SLM_TRIGGER_DETERMINE_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else if (ReplaceDataLink(ln))
            {
                ln->restorationState = LINK_RESTORATION_WAIT_1;

                LSDA_Main_ANSI(MTP3_SLM_LSLR,
                               SLM_TRIGGER_DETERMINE_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSAC_Main_ANSI(MTP3_SLM_LSLR,
                               SLM_TRIGGER_RESTORATION_UNSUCCESS,
                               NULL, 0,
                               linkSet, linkCode);

                LSAC_Main_ANSI(MTP3_SLM_LSLR,
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

            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_CONNECT, NULL, 0);

            LSAC_Main_ANSI(MTP3_SLM_LSLA,
                           SLM_TRIGGER_START_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_NO_TERMINAL:            /* from LSTA */
        if (ln->restorationState == LINK_RESTORATION_WAIT_2)
        {
            ln->restorationState = LINK_RESTORATION_IDLE;

            LSAC_Main_ANSI(MTP3_SLM_LSLR,
                           SLM_TRIGGER_RESTORATION_UNSUCCESS,
                           NULL, 0,
                           linkSet, linkCode);

            LSAC_Main_ANSI(MTP3_SLM_LSLR,
                           SLM_TRIGGER_START_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_DATA_LINK:              /* from LSDA */
        if (ln->restorationState == LINK_RESTORATION_WAIT_1)
        {
            ln->restorationState = LINK_RESTORATION_IDLE;

            MTP2_SendData_ANSI(linkSet, linkCode,
                               L3_L2_CONNECT, NULL, 0);

            LSAC_Main_ANSI(MTP3_SLM_LSLA,
                           SLM_TRIGGER_START_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        break;

    case SLM_TRIGGER_NO_DATA_LINK:           /* from LSDA */
        if (ln->restorationState == LINK_RESTORATION_WAIT_1)
        {
            ln->restorationState = LINK_RESTORATION_IDLE;

            LSAC_Main_ANSI(MTP3_SLM_LSLR,
                           SLM_TRIGGER_RESTORATION_UNSUCCESS,
                           NULL, 0,
                           linkSet, linkCode);

            LSAC_Main_ANSI(MTP3_SLM_LSLR,
                           SLM_TRIGGER_START_LINK,
                           NULL, 0,
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
LSLD_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_TRACE_ENTRY_ANSI(MTP3_SLM_LSLD, src, trigger, sif, len,
                          linkSet, linkCode);

    switch (trigger)
    {
    case SLM_TRIGGER_DEACTIVATE_LINK:      /* from LSAC */

        MTP2_SendData_ANSI(linkSet, linkCode, L3_L2_DISCONNECT, NULL, 0);
 
        MTP3_Alarm_ANSI(2509, __FILE__, __LINE__, "linkset:linkcode  %x:%x",
                        linkSet, linkCode);

        LSDA_Main_ANSI(MTP3_SLM_LSLD,
                       SLM_TRIGGER_LINK_AVAILABLE,
                       NULL, 0,
                       linkSet, linkCode);

        LSTA_Main_ANSI(MTP3_SLM_LSLD,
                       SLM_TRIGGER_TERMINAL_IDLE,
                       NULL, 0,
                       linkSet, linkCode);
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
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
LSTA_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;

    MTP3_TRACE_ENTRY_ANSI(MTP3_SLM_LSTA, src, trigger, sif, len,
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
            MTP3_Alarm_ANSI(2434, __FILE__, __LINE__, "linkset:linkcode %x:%x", linkSet, linkCode); 
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
                LSLA_Main_ANSI(MTP3_SLM_LSTA,
                               SLM_TRIGGER_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLR_Main_ANSI(MTP3_SLM_LSTA,
                               SLM_TRIGGER_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }

            ln->slFlags &= ~LINK_IS_ACTIVATING;
        }
        else if (AnyTerminalsAvailable(ls))
        {
            SelectNextTerminal(ls, &ln);

            LSLD_Main_ANSI(MTP3_SLM_LSTA,
                           SLM_TRIGGER_DEACTIVATE_LINK,
                           NULL, 0,
                           linkSet, linkCode);
        }
        else
        {
            if (ln->slFlags & LINK_IS_ACTIVATING)
            {
                LSLA_Main_ANSI(MTP3_SLM_LSTA,
                               SLM_TRIGGER_NO_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLR_Main_ANSI(MTP3_SLM_LSTA,
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
                LSLA_Main_ANSI(MTP3_SLM_LSTA,
                               SLM_TRIGGER_TERMINAL,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLR_Main_ANSI(MTP3_SLM_LSTA,
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
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
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
LSDA_Main_ANSI(MTP3_SubSystems src, SLM_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI omtp3, *mtp3, *lmtp3;
    SNMM_MESSAGE snmm, *isnmm;
    ITS_EVENT ev;
    ITS_OCTET ni, ols, oln;
    ITS_UINT pc1, pc2;
    SS7_LinkSetPtr ls, nls;
    SS7_LinkPtr ln, nln;
    int ret;

    MTP3_TRACE_ENTRY_ANSI(MTP3_SLM_LSDA, src, trigger, sif, len,
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
            MTP3_Alarm_ANSI(2439, __FILE__, __LINE__, "linkset:linkcode %x:%x", linkSet, linkCode);
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

        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

        MTP3_HDR_SET_SIO(omtp3, ls->ni);
        MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
        MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

        MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                         &omtp3, NULL, 0);

        ln->allocationState = LINK_ALLOCATION_WAIT_2;

        TSRC_Main_ANSI(MTP3_SLM_LSDA, STM_TRIGGER_ALTERNATE_ROUTE_REQ,
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
        mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER_ANSI) +
                                     sizeof(ITS_OCTET)];

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            MTP3_Alarm_ANSI(2440, __FILE__, __LINE__, NULL);

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_DATALINK_CONNECT_GET_SLC_ANSI(isnmm->data.datalinkConnect);

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
            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);

            MTP3_HDR_SET_SIO(omtp3, ls->ni);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

            MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                             &omtp3, NULL, 0);

            ln->allocationState = LINK_ALLOCATION_WAIT_3;

            TSRC_Main_ANSI(MTP3_SLM_LSDA, STM_TRIGGER_ALTERNATE_ROUTE_REQ,
                           ev.data, ev.len,
                           linkSet, linkCode);

            ITS_EVENT_TERM(&ev);
        }
        else if (ln->allocationState == LINK_ALLOCATION_WAIT_1)
        {
            mtp3 = (MTP3_HEADER_ANSI *)&sif[1];

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
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                    SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_DLM_ANSI);
                    SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_CSS_ANSI);
                    SNMM_DATALINK_CONN_ACK_SET_SLC_ANSI(snmm.data.datalinkConnectAck,
                                                        linkCode);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                    SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                    /* Increament Link Peg for CSS Trasmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_TX);

                    ret = HMRT_Main_ANSI(MTP3_SLM_LSDA,
                                         SMH_TRIGGER_LINK_MGMT_MSG,
                                         ev.data, ev.len,
                                         linkSet, linkCode);
                    ITS_EVENT_TERM(&ev);

                    ln->allocationState = LINK_ALLOCATION_IDLE;

                    if (ln->slFlags & LINK_IS_ACTIVATING)
                    {
                        LSLA_Main_ANSI(MTP3_SLM_LSDA,
                                       SLM_TRIGGER_DATA_LINK,
                                       NULL, 0,
                                       linkSet, linkCode);
                    }
                    else
                    {
                        LSLR_Main_ANSI(MTP3_SLM_LSDA,
                                       SLM_TRIGGER_DATA_LINK,
                                       NULL, 0,
                                       linkSet, linkCode);
                    }
                }
                else if (AnotherDataLinkAvailable(ls, ln))
                {
                    /* build CNS, send */
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                    SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_DLM_ANSI);
                    SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_CNS_ANSI);
                    SNMM_DATALINK_CONN_ACK_SET_SLC_ANSI(snmm.data.datalinkConnectAck,
                                                        linkCode);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                    SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                    /* Increament Link Peg for CNS Transmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_TX);

                    ret = HMRT_Main_ANSI(MTP3_SLM_LSDA,
                                         SMH_TRIGGER_LINK_MGMT_MSG,
                                         ev.data, ev.len,
                                         linkSet, linkCode);
                    ITS_EVENT_TERM(&ev);
                }
                else
                {
                    /* build CNP, send */
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                    SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_DLM_ANSI);
                    SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_CNP_ANSI);
                    SNMM_DATALINK_CONN_ACK_SET_SLC_ANSI(snmm.data.datalinkConnectAck,
                                                        linkCode);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                    SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                    /* Increament Link Peg for CNP Transmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_TX);

                    ret = HMRT_Main_ANSI(MTP3_SLM_LSDA,
                                         SMH_TRIGGER_LINK_MGMT_MSG,
                                         ev.data, ev.len,
                                         linkSet, linkCode);
                    ITS_EVENT_TERM(&ev);

                    ln->allocationState = LINK_ALLOCATION_IDLE;

                    if (ln->slFlags & LINK_IS_ACTIVATING)
                    {
                        LSLA_Main_ANSI(MTP3_SLM_LSDA,
                                       SLM_TRIGGER_NO_DATA_LINK,
                                       NULL, 0,
                                       linkSet, linkCode);
                    }
                    else
                    {
                        LSLA_Main_ANSI(MTP3_SLM_LSDA,
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
        lmtp3 = (MTP3_HEADER_ANSI *)&sif[sizeof(MTP3_HEADER_ANSI) +
                                         sizeof(ITS_OCTET)];
        ols = sif[2 * sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_OCTET)];
        oln = sif[2 * sizeof(MTP3_HEADER_ANSI) + 2 * sizeof(ITS_OCTET)];

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

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_DLM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_DLC_ANSI);
                SNMM_DATALINK_CONNECT_SET_SLC_ANSI(snmm.data.datalinkConnect,
                                                   linkCode);
                SNMM_DATALINK_CONNECT_SET_LINK_ANSI(snmm.data.datalinkConnect,
                                                    nln->dataLink);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for DLC Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);

                ret = HMRT_Main_ANSI(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                /* Start T7 */
                tc.timerId = MTP3_T7;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                nln->t7 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t7 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                nln->allocationState = LINK_ALLOCATION_WAIT_1;
            }
            else
            {
                nln->allocationState = LINK_ALLOCATION_IDLE;

                if (nln->slFlags & LINK_IS_ACTIVATING)
                {
                    LSLA_Main_ANSI(MTP3_SLM_LSDA,
                                   SLM_TRIGGER_NO_DATA_LINK,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
                else
                {
                    LSLA_Main_ANSI(MTP3_SLM_LSDA,
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
                LSAC_Main_ANSI(MTP3_SLM_LSDA,
                               SLM_TRIGGER_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);

                /* build CSS, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | nls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, nls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, nls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_DLM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_CSS_ANSI);
                SNMM_DATALINK_CONN_ACK_SET_SLC_ANSI(snmm.data.datalinkConnectAck,
                                                    linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for CSS Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_TX);

                ret = HMRT_Main_ANSI(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);
            }
            else if (AnotherDataLinkAvailable(ls, ln))
            {
                /* build CNS, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_DLM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_CNS_ANSI);
                SNMM_DATALINK_CONN_ACK_SET_SLC_ANSI(snmm.data.datalinkConnectAck,
                                                    linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for CNS Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_TX);

                ret = HMRT_Main_ANSI(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);
            }
            else
            {
                /* build CNP, send */
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_DLM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_CNP_ANSI);
                SNMM_DATALINK_CONN_ACK_SET_SLC_ANSI(snmm.data.datalinkConnectAck,
                                                    linkCode);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for CNP Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_TX);

                ret = HMRT_Main_ANSI(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);
            }
        }
        break;

    case SLM_TRIGGER_CONNECTION_SUCCESSFUL:  /* from HMDT */
        /* sanitize the linkSet */
        mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER_ANSI) +
                                     sizeof(ITS_OCTET)];

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            MTP3_Alarm_ANSI(2440, __FILE__, __LINE__, NULL);

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_DATALINK_CONN_ACK_GET_SLC_ANSI(isnmm->data.datalinkConnectAck);

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
                LSLA_Main_ANSI(MTP3_SLM_LSDA,
                               SLM_TRIGGER_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLR_Main_ANSI(MTP3_SLM_LSDA,
                               SLM_TRIGGER_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
        }
        break;

    case SLM_TRIGGER_CONNECTION_UNSUCCESS:   /* from HMDT */
        /* sanitize the linkSet */
        mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER_ANSI) +
                                     sizeof(ITS_OCTET)];

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            MTP3_Alarm_ANSI(2440, __FILE__, __LINE__, NULL);

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_DATALINK_CONNECT_GET_SLC_ANSI(isnmm->data.datalinkConnect);

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
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_DLM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_DLC_ANSI);
                SNMM_DATALINK_CONNECT_SET_SLC_ANSI(snmm.data.datalinkConnect,
                                                   linkCode);
                SNMM_DATALINK_CONNECT_SET_LINK_ANSI(snmm.data.datalinkConnect,
                                                    ln->dataLink);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for DLC Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);

                ret = HMRT_Main_ANSI(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                /* Start T7 */
                tc.timerId = MTP3_T7;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t7 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t7 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                ln->allocationState = LINK_ALLOCATION_WAIT_1;
            }
            else
            {
                ln->allocationState = LINK_ALLOCATION_IDLE;

                if (ln->slFlags & LINK_IS_ACTIVATING)
                {
                    LSLA_Main_ANSI(MTP3_SLM_LSDA,
                                   SLM_TRIGGER_NO_DATA_LINK,
                                   NULL, 0,
                                   linkSet, linkCode);
                }
                else
                {
                    LSLA_Main_ANSI(MTP3_SLM_LSDA,
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
        mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
        isnmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER_ANSI) +
                                     sizeof(ITS_OCTET)];

        ni = MTP3_HDR_GET_SIO(*mtp3);
        pc1 = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        linkSet = MTP3_FindAdjacent_ANSI(ni, pc1, linkSet);
        if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
        {
            MTP3_ERROR(("Can't find adjacent for connection order\n"));

            MTP3_Alarm_ANSI(2440, __FILE__, __LINE__, NULL);

            return (ITS_EINVALIDARGS);
        }

        linkCode = SNMM_DATALINK_CONNECT_GET_SLC_ANSI(isnmm->data.datalinkConnect);

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
                LSLA_Main_ANSI(MTP3_SLM_LSDA,
                               SLM_TRIGGER_NO_DATA_LINK,
                               NULL, 0,
                               linkSet, linkCode);
            }
            else
            {
                LSLA_Main_ANSI(MTP3_SLM_LSDA,
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
                    MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                    MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                    MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                    SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_DLM_ANSI);
                    SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_DLC_ANSI);
                    SNMM_DATALINK_CONNECT_SET_SLC_ANSI(snmm.data.datalinkConnect,
                                                       linkCode);
                    SNMM_DATALINK_CONNECT_SET_LINK_ANSI(snmm.data.datalinkConnect,
                                                        ln->dataLink);

                    ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                    SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                    /* Increament Link Peg for DLC Transmitted */
                    PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);

                    ret = HMRT_Main_ANSI(MTP3_SLM_LSDA,
                                         SMH_TRIGGER_LINK_MGMT_MSG,
                                         ev.data, ev.len,
                                         linkSet, linkCode);
                    ITS_EVENT_TERM(&ev);

                    /* Start T7 */
                    tc.timerId = MTP3_T7;
                    tc.data.linkInfo.linkSet = linkSet;
                    tc.data.linkInfo.linkCode = linkCode;

                    ln->t7 =
                        TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                           __ansi_t7 * USEC_PER_MILLISEC,
                                           &tc, sizeof(MTP3_TimerContext));

                    ln->allocationState = LINK_ALLOCATION_WAIT_1;
                }
                else
                {
                    ln->allocationState = LINK_ALLOCATION_IDLE;

                    if (ln->slFlags & LINK_IS_ACTIVATING)
                    {
                        LSLA_Main_ANSI(MTP3_SLM_LSDA,
                                       SLM_TRIGGER_NO_DATA_LINK,
                                       NULL, 0,
                                       linkSet, linkCode);
                    }
                    else
                    {
                        LSLA_Main_ANSI(MTP3_SLM_LSDA,
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
                MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ls->ni | MTP3_MPC_PRI_3);
                MTP3_RL_SET_DPC_VALUE(omtp3.label, ls->adjacent);
                MTP3_RL_SET_OPC_VALUE(omtp3.label, ls->lpc);

                SNMM_HC0_SET_ANSI(snmm, SNMM_HC0_DLM_ANSI);
                SNMM_HC1_SET_ANSI(snmm, SNMM_HC1_DLC_ANSI);
                SNMM_DATALINK_CONNECT_SET_SLC_ANSI(snmm.data.datalinkConnect,
                                                   linkCode);
                SNMM_DATALINK_CONNECT_SET_LINK_ANSI(snmm.data.datalinkConnect,
                                                    ln->dataLink);

                ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
                SNMM_Encode_ANSI(&ev, &omtp3, &snmm);

                /* Increament Link Peg for DLC Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);

                ret = HMRT_Main_ANSI(MTP3_SLM_LSDA,
                                     SMH_TRIGGER_LINK_MGMT_MSG,
                                     ev.data, ev.len,
                                     linkSet, linkCode);
                ITS_EVENT_TERM(&ev);

                /* Start T7 */
                tc.timerId = MTP3_T7;
                tc.data.linkInfo.linkSet = linkSet;
                tc.data.linkInfo.linkCode = linkCode;

                ln->t7 =
                    TIMERS_StartSharedUTimer(ITS_MTP3_ANSI_SRC,
                                       __ansi_t7 * USEC_PER_MILLISEC,
                                       &tc, sizeof(MTP3_TimerContext));

                ln->allocationState = LINK_ALLOCATION_WAIT_1;
            }
        }
        break;

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    return (ITS_SUCCESS);
}
