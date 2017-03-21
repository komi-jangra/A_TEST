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
 *  ID: $Id: its-itu-mtp3.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:32  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:07  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:38  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.20  2003/11/28 06:18:20  kannanp
 * LOG: Changed PEG_MTP3_LINK_F_UNINHIBIT to PEG_MTP3_LINK_FORCE_UNINHIBIT.
 * LOG:
 * LOG: Revision 8.19  2003/11/24 09:25:31  kannanp
 * LOG: Fix 490 Trace problem.
 * LOG:
 * LOG: Revision 8.18  2003/10/16 10:52:28  ttipatre
 * LOG: mi_get_link_pegs bug fixed.
 * LOG:
 * LOG: Revision 8.17  2003/08/04 13:26:44  ttipatre
 * LOG: Bug for 401,404 and other pegs not getting increamented.
 * LOG:
 * LOG: Revision 8.16  2003/07/22 15:43:46  mmiers
 * LOG: Warning removal.  Fix Windoze build.
 * LOG:
 * LOG: Revision 8.15  2003/07/17 08:49:59  ttipatre
 * LOG: MML Modified.
 * LOG:
 * LOG: Revision 8.14  2003/06/16 13:56:40  mmanikandan
 * LOG: Xml Persistency is added.
 * LOG:
 * LOG: Revision 8.13  2003/06/13 08:07:37  ttipatre
 * LOG: Pegs Output Justified.
 * LOG:
 * LOG: Revision 8.12  2003/06/05 12:01:07  ttipatre
 * LOG: adding/updating MML commands.
 * LOG:
 * LOG: Revision 8.11  2003/05/19 13:16:39  ssanyal
 * LOG: Temporarily commenting out Alarm Output to File
 * LOG:
 * LOG: Revision 8.10  2003/05/19 06:32:21  ttipatre
 * LOG: Alarms updated.
 * LOG:
 * LOG: Revision 8.9  2003/04/07 21:07:20  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 8.8  2003/04/01 17:05:16  randresol
 * LOG: Change naming convention for Debug Console commands
 * LOG:
 * LOG: Revision 8.7  2003/03/06 19:11:42  mmiers
 * LOG: Convert to new tracing, simply by removing file names from
 * LOG: existing trace subsystems.
 * LOG:
 * LOG: Revision 8.6  2003/02/26 21:02:22  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 8.5  2003/02/26 17:01:16  mmiers
 * LOG: Warning removal, extra library generation.
 * LOG:
 * LOG: Revision 8.4  2003/02/26 02:00:45  randresol
 * LOG: log mtp3 alarms to file
 * LOG:
 * LOG: Revision 8.3  2003/02/25 22:58:07  randresol
 * LOG: Enhancement for Pegs, Alarms and MML commands
 * LOG:
 * LOG: Revision 8.2  2003/02/25 22:26:37  mmiers
 * LOG: Finish the split, clean up some warnings.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 21:39:13  mmiers
 * LOG: The great file split.  Files without an its- prefix can
 * LOG: be moved into a netcore library.
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
#include <its_app.h>
#include <its_alarm.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_assertion.h>
#include <its_timers.h>
#include <its_dsm.h>
#include <its_route_rwlock.h>
#include <its_pprint.h>

#include <dbc_serv.h>

#include <engine.h>

#ident "$Id: its-itu-mtp3.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"

#if defined(PRC)
#include <china/mtp3.h>
#else
#include <itu/mtp3.h>
#endif

#define MTP3_ALARM_FILE_NAME "itu-mtp3alarms.out"

#include <isup_sn.h>
#include <sccp_sn.h>

#include "mtp3_intern.h"

/*
 * local data
 */
static ITS_BOOLEAN      started = ITS_FALSE;
static ITS_BOOLEAN      stopped = ITS_FALSE;

static int numThreads = 1;
static ITS_THREAD* mtp3Thread = NULL;

static TRACE_OutputMethod *mtp3AlarmsOutput = NULL;

TQUEUETRAN_Manager* __MTP3_CCITT_RcvQueue = NULL;

THREAD_RET_TYPE     CCITT_MTP3Thread(void *arg);

static void MTP3_Console_CCITT(DBC_Server *dbc, const char *cmdLine);

static ITS_CHAR* MTP3_CCITT_Timers[] =
{
    MTP3_T1_STRING,
    MTP3_T2_STRING,
    MTP3_T3_STRING,
    MTP3_T4_STRING,
    MTP3_T5_STRING,
    MTP3_T6_STRING,
    MTP3_T7_STRING,
    MTP3_T8_STRING,
    MTP3_T9_STRING,
    MTP3_T10_STRING,
    MTP3_T11_STRING,
    MTP3_T12_STRING,
    MTP3_T13_STRING,
    MTP3_T14_STRING,
    MTP3_T15_STRING,
    MTP3_T16_STRING,
    MTP3_T17_STRING,
    MTP3_T18_STRING,
    MTP3_T19_STRING,
    MTP3_T20_STRING,
    MTP3_T21_STRING,
    MTP3_T22_STRING,
    MTP3_T23_STRING,
    MTP3_T24_STRING,
    MTP3_T25_STRING,
    MTP3_T26_STRING,
    MTP3_T27_STRING,
    MTP3_T28_STRING,
    MTP3_T29_STRING,
    MTP3_T30_STRING,
    MTP3_T31_STRING,
    MTP3_T32_STRING,
    MTP3_T33_STRING,
    MTP3_T34_STRING,
    NULL
};

static ITS_CHAR *mtp3GPegStr[] =
{
     "PEG_MTP3_MSG_PAUSE",
     "PEG_MTP3_MSG_RESUME",
     "PEG_MTP3_MSG_STATUS",
     "PEG_MTP3_INITIALIZE",
     "PEG_MTP3_TERMINATE",
     "PEG_MTP3_MSG_RECEIVED_INERROR",
     "PEG_MTP3_CHANGEOVER",
     "PEG_MTP3_CHANGEBACK",
     "PEG_MTP3_SL_UNAVAILABLE",
     "PEG_MTP3_LINK_INHIBIT",
     "PEG_MTP3_LINK_UNINHIBIT",
     "PEG_MTP3_LINK_FORCE_UNINHIBIT",
     "PEG_MTP3_CONGESTION",
     "PEG_MTP3_SLS_UNAVAILABLE",
     "PEG_MTP3_TFC_RECEIVED",
     "PEG_MTP3_TFA_RECEIVED",
     "PEG_MTP3_ROUTESET_UNAVAILABLE",
     "PEG_MTP3_ADJECENT_SP_UNACCESIBLE",
     "PEG_MTP3_USERPART_ENABLE",
     "PEG_MTP3_USERPART_DISABLE",
     "PEG_MTP3_T1_EXPIRED",
     "PEG_MTP3_T2_EXPIRED",
     "PEG_MTP3_T3_EXPIRED",
     "PEG_MTP3_T4_EXPIRED",
     "PEG_MTP3_T5_EXPIRED",
     "PEG_MTP3_T6_EXPIRED",
     "PEG_MTP3_T7_EXPIRED",
     "PEG_MTP3_T8_EXPIRED",
     "PEG_MTP3_T9_EXPIRED",
     "PEG_MTP3_T10_EXPIRED",
     "PEG_MTP3_T11_EXPIRED",
     "PEG_MTP3_T12_EXPIRED",
     "PEG_MTP3_T13_EXPIRED",
     "PEG_MTP3_T14_EXPIRED",
     "PEG_MTP3_T15_EXPIRED",
     "PEG_MTP3_T16_EXPIRED",
     "PEG_MTP3_T17_EXPIRED",
     "PEG_MTP3_T18_EXPIRED",
     "PEG_MTP3_T19_EXPIRED",
     "PEG_MTP3_T20_EXPIRED",
     "PEG_MTP3_T21_EXPIRED",
     "PEG_MTP3_T22_EXPIRED",
     "PEG_MTP3_T23_EXPIRED",
     "PEG_MTP3_T24_EXPIRED",
     "PEG_MTP3_T25_EXPIRED",
     "PEG_MTP3_T26_EXPIRED",
     "PEG_MTP3_T27_EXPIRED",
     "PEG_MTP3_T28_EXPIRED",
     "PEG_MTP3_T29_EXPIRED",
     "PEG_MTP3_T30_EXPIRED",
     "PEG_MTP3_T31_EXPIRED",
     "PEG_MTP3_T32_EXPIRED",
     "PEG_MTP3_T33_EXPIRED",
     "PEG_MTP3_T34_EXPIRED",
      NULL
};

static ITS_CHAR *mtp3LPegStr[] =
{
      "PEG_MTP3_LINK_MSU_TX",
      "PEG_MTP3_LINK_MSU_RX",
      "PEG_MTP3_LINK_OCTETS_TX",
      "PEG_MTP3_LINK_OCTETS_RX",
      "PEG_MTP3_LINK_COO_TX",
      "PEG_MTP3_LINK_COO_RX",
      "PEG_MTP3_LINK_COA_TX",
      "PEG_MTP3_LINK_COA_RX" ,
      "PEG_MTP3_LINK_ECO_TX",
      "PEG_MTP3_LINK_ECO_RX",
      "PEG_MTP3_LINK_ECA_TX",
      "PEG_MTP3_LINK_ECA_RX",
      "PEG_MTP3_LINK_CBD_TX",
      "PEG_MTP3_LINK_CBD_RX",
      "PEG_MTP3_LINK_CBA_TX",
      "PEG_MTP3_LINK_CBA_RX",
      "PEG_MTP3_LINK_LIN_TX",
      "PEG_MTP3_LINK_LIN_RX",
      "PEG_MTP3_LINK_LIA_TX",
      "PEG_MTP3_LINK_LIA_RX",
      "PEG_MTP3_LINK_LUN_TX",
      "PEG_MTP3_LINK_LUN_RX",
      "PEG_MTP3_LINK_LUA_TX",
      "PEG_MTP3_LINK_LUA_RX",
      "PEG_MTP3_LINK_LID_TX",
      "PEG_MTP3_LINK_LID_RX",
      "PEG_MTP3_LINK_LFU_TX",
      "PEG_MTP3_LINK_LFU_RX",
      "PEG_MTP3_LINK_LLI_TX",
      "PEG_MTP3_LINK_LLI_RX",
      "PEG_MTP3_LINK_LRI_TX",
      "PEG_MTP3_LINK_LRI_RX",
      "PEG_MTP3_LINK_DLC_TX",
      "PEG_MTP3_LINK_DLC_RX",
      "PEG_MTP3_LINK_CSS_TX",
      "PEG_MTP3_LINK_CSS_RX",
      "PEG_MTP3_LINK_CNS_TX",
      "PEG_MTP3_LINK_CNS_RX",
      "PEG_MTP3_LINK_CNP_TX",
      "PEG_MTP3_LINK_CNP_RX",
      "PEG_MTP3_LINK_UPU_TX",
      "PEG_MTP3_LINK_UPU_RX",
      "PEG_MTP3_LINK_SLTM_TX",
      "PEG_MTP3_LINK_SLTM_RX",
      "PEG_MTP3_LINK_SLTA_TX",
      "PEG_MTP3_LINK_SLTA_RX",
       NULL
};


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
MTP3_Pause(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* base = (TRANSPORT_Control *)object;
    MTP3_PAUSE_RESUME pause;
    MTP3_HEADER mtp3;
    ITS_EVENT event;

    MTP3_DEBUG(("MTP3_Pause_CCITT:\n"));

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        MTP3_WARNING(("Pause_CCITT: link lock failed\n"));
   
        return;
    }

    /*
     * if we're using SS7, set up the routing entries
     */
    /*
     * NOTE: We can only get here if we're NOT MTP2.
     */
    if ((TRANSPORT_MASK(base) & ITS_SS7_MASK) && TRANSPORT_RES(base))
    {
        SS7_LinkPtr link;

        for (link = TRANSPORT_SS7_INFO(base).linkInfo;
             link != NULL; link = link->next)
        {
            ITS_BOOLEAN wasUp = ITS_FALSE, isUp = ITS_FALSE;

            /*
             * deactivate this link
             */
            LINKSET_RemoveActiveLink(link->linkSet, link->linkCode);

            /* get old linkSet state */
            if (LINKSET_GetLinkSetState(link->linkSet, &wasUp) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't find link set %d\n", link->linkSet->linkSet));

            }

            LINK_SetLinkState(link, ITS_FALSE);

            /* get new linkSet state */
            if (LINKSET_GetLinkSetState(link->linkSet, &isUp) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't find link set %d\n", link->linkSet->linkSet));
                
            }

            /*
             * if link set was previously up, walk routes looking for dests to pause.
             */
            if (wasUp && !isUp)
            {
                DSMQUEUE_Entry *tmp;
                ITS_UINT count;

                for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes); 
                     tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                     count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
                {
                    ROUTE_Info *rinfo;
                    ROUTE_MatchInfo minfo;
                    SS7_Destination *dest;
                    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;
                    ITS_BOOLEAN allDown = ITS_TRUE;

                    /* select one of concerned destinations */
                    memcpy(&rinfo, tmp->data, sizeof(rinfo));

                    if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE)
                    {
                        continue;
                    }

                    minfo.basic = rinfo->basic;
                    minfo.linkSet = ITS_SS7_DEFAULT_LINK_SET;
                    minfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
                    minfo.priority = ITS_SS7_DEFAULT_PRI;
                    minfo.sls = ITS_SS7_DEFAULT_SLS;

                    if ((dest = ROUTE_FindBestMatch(&minfo, &whichEntry,
                                                    &firstMatch, &lastMatch,
                                                    &whichLinkCode,
                                                    ITS_TRUE)) == NULL)
                    {
                        MTP3_WARNING(("Configured route not found\n"));

                        continue;
                    }

                    for (i = firstMatch; i <= lastMatch; i++)
                    {
                        if (dest->entries[i]->linkSet->isUp)
                        {
                            allDown = ITS_FALSE;

                            break;
                        }
                    }

                    /* determine if this was the last up route */
                    if (allDown)
                    {
                        MTP3_DEBUG(("MTP3_Pause_CCITT: setting state PC: %08x\n",
                                    rinfo->basic.dpc));

                        MTP3_PC_SET_VALUE(pause.affected, rinfo->basic.dpc);

                        MTP3_Alarm_CCITT(2401, __FILE__, __LINE__,
                                        "affected point code %d", rinfo->basic.dpc);

                        mtp3.sio = link->linkSet->ni;
                        MTP3_RL_SET_OPC_VALUE(mtp3.label, rinfo->basic.dpc);
                        MTP3_RL_SET_DPC_VALUE(mtp3.label, link->linkSet->lpc);
                        MTP3_RL_SET_SLS(mtp3.label, 0);

                        event.src = ITS_MTP3_SRC;
                        MTP3_Encode(&event, MTP3_MSG_PAUSE, &mtp3,
                                    (ITS_OCTET *)&pause, sizeof(MTP3_PAUSE_RESUME));

                        CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                                  (ITS_POINTER)base,
                                                  (ITS_POINTER)&event);

                        ITS_EVENT_TERM(&event);
                    }
                }
            }
        }
    }

    ROUTE_UnlockWrite(routeRWLock);
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
MTP3_Resume(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* base = (TRANSPORT_Control *)object;
    MTP3_PAUSE_RESUME resume;
    MTP3_HEADER mtp3;
    ITS_EVENT event;

    MTP3_DEBUG(("MTP3_Resume_CCITT:\n"));

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        MTP3_WARNING(("Pause_CCITT: link lock failed\n"));

        return;
    }

    /*
     * if we're using SS7, set up the routing entries
     */
    /*
     * NOTE: We can only get here if we're NOT MTP2.
     */
    if ((TRANSPORT_MASK(base) & ITS_SS7_MASK) && TRANSPORT_RES(base))
    {
        SS7_LinkPtr link;

        for (link = TRANSPORT_SS7_INFO(base).linkInfo;
             link != NULL; link = link->next)
        {
            ITS_BOOLEAN wasUp = ITS_FALSE, isUp = ITS_FALSE;

            /*
             * activate this link
             */
            LINKSET_AddActiveLink(link->linkSet, link->linkCode);

            /* get old linkSet state */
            if (LINKSET_GetLinkSetState(link->linkSet, &wasUp) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't find link set %d\n", link->linkSet->linkSet));

            }

            LINK_SetLinkState(link, ITS_TRUE);

            /* get new linkSet state */
            if (LINKSET_GetLinkSetState(link->linkSet, &isUp) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Can't find link set %d\n", link->linkSet->linkSet));

            }

            /*
             * if link set was previously up, walk routes looking for dests to pause.
             */
            if (!wasUp && isUp)
            {
                DSMQUEUE_Entry *tmp;
                ITS_UINT count;

                for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes); 
                     tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                     count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
                {
                    ROUTE_Info *rinfo;
                    ROUTE_MatchInfo minfo;
                    SS7_Destination *dest;
                    int whichEntry, firstMatch, lastMatch, whichLinkCode, i;
                    ITS_BOOLEAN firstUp = ITS_TRUE;

                    /* select one of concerned destinations */
                    memcpy(&rinfo, tmp->data, sizeof(rinfo));

                    if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE)
                    {
                        continue;
                    }

                    minfo.basic = rinfo->basic;
                    minfo.linkSet = ITS_SS7_DEFAULT_LINK_SET;
                    minfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;
                    minfo.priority = ITS_SS7_DEFAULT_PRI;
                    minfo.sls = ITS_SS7_DEFAULT_SLS;

                    if ((dest = ROUTE_FindBestMatch(&minfo, &whichEntry,
                                                    &firstMatch, &lastMatch,
                                                    &whichLinkCode,
                                                    ITS_TRUE)) == NULL)
                    {
                        MTP3_WARNING(("Configured route not found\n"));

                        continue;
                    }

                    for (i = firstMatch; i <= lastMatch; i++)
                    {
                        if (dest->entries[i]->linkSet->linkSet != link->linkSet->linkSet &&
                            dest->entries[i]->linkSet->isUp)
                        {
                            firstUp = ITS_FALSE;

                            break;
                        }
                    }

                    /* determine if this is a newly up route */
                    if (firstUp)
                    {
                        MTP3_DEBUG(("MTP3_Resume_CCITT: setting state PC: %08x\n",
                                    rinfo->basic.dpc));

                        MTP3_PC_SET_VALUE(resume.affected, rinfo->basic.dpc);

                        MTP3_Alarm_CCITT(2402, __FILE__, __LINE__,
                                        "affected point code %d", rinfo->basic.dpc);

                        mtp3.sio = link->linkSet->ni;
                        MTP3_RL_SET_OPC_VALUE(mtp3.label, rinfo->basic.dpc);
                        MTP3_RL_SET_DPC_VALUE(mtp3.label, link->linkSet->lpc);
                        MTP3_RL_SET_SLS(mtp3.label, 0);

                        event.src = ITS_MTP3_SRC;
                        MTP3_Encode(&event, MTP3_MSG_RESUME, &mtp3,
                                    (ITS_OCTET *)&resume, sizeof(MTP3_PAUSE_RESUME));

                        CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                                  (ITS_POINTER)base,
                                                  (ITS_POINTER)&event);

                        ITS_EVENT_TERM(&event);
                    }
                }
            }
        }
    }

    ROUTE_UnlockWrite(routeRWLock);
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
MTP3_Status(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* base = (TRANSPORT_Control *)object;
    ITS_OCTET congLevel = 0;
    MTP3_STATUS status;
    MTP3_HEADER mtp3;
    ITS_EVENT event;

    MTP3_DEBUG(("MTP3_Status_CCITT:\n"));

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        MTP3_WARNING(("Status_CCITT: link lock failed\n"));

        return;
    }

    /*
     * if we're using SS7, set up the routing entries
     */
    /*
     * NOTE: We can only get here if we're NOT MTP2.
     */
    if ((TRANSPORT_MASK(base) & ITS_SS7_MASK) && TRANSPORT_RES(base))
    {
        SS7_LinkPtr link;

        for (link = TRANSPORT_SS7_INFO(base).linkInfo;
             link != NULL; link = link->next)
        {
            DSMQUEUE_Entry *tmp;
            ITS_UINT count;

            LINK_SetLinkCongestion(link, congLevel);

            /*
             * If not MTP2 link, if congestion deliver MTP3-STATUS.
             */
            for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes); 
                 tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                 count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
            {
                ROUTE_Info *rinfo;

                /* select one of concerned destinations */
                memcpy(&rinfo, tmp->data, sizeof(rinfo));

                if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE)
                {
                    continue;
                }

                /*
                 * if this route is congested, send a status message
                 * for congestion, always do this.  There's not a lot the
                 * user can do anyway.
                 */
                if (ITS_TRUE)
                {
                    MTP3_DEBUG(("MTP3_Status_CCITT: get congestion PC: %08x SSN: %02xn\n",
                                rinfo->basic.dpc, rinfo->basic.criteria.ssn));

                    MTP3_PC_SET_VALUE(status.affected, rinfo->basic.dpc);
                    status.congLevel = congLevel;

                    mtp3.sio = 0;
                    MTP3_RL_SET_OPC_VALUE(mtp3.label, rinfo->basic.dpc);
                    MTP3_RL_SET_DPC_VALUE(mtp3.label, link->linkSet->lpc);
                    MTP3_RL_SET_SLS(mtp3.label, 0);

                    event.src = ITS_MTP3_SRC;
                    MTP3_Encode(&event, MTP3_MSG_STATUS, &mtp3,
                                (ITS_OCTET *)&status, sizeof(MTP3_STATUS));

                    CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                                              (ITS_POINTER)base,
                                              (ITS_POINTER)&event);

                    ITS_EVENT_TERM(&event);
                }
            }
        }
    }

    ROUTE_UnlockWrite(routeRWLock);
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
MTP3_Register(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* tc = (TRANSPORT_Control *)object;

    /*
     * avoid MTP2 links by not registering callbacks here
     */
    if (TRANSPORT_MASK(tc) & ITS_SS7_MASK_CCITT &&
        !(TRANSPORT_MASK(tc) & ITS_FLAG_MTP2))
    {
        CALLBACK_AddCallback(TRANSPORT_SS7_INFO(tc).pauseCallbacks,
                             MTP3_Pause, NULL);
        CALLBACK_AddCallback(TRANSPORT_SS7_INFO(tc).resumeCallbacks,
                             MTP3_Resume, NULL);
        CALLBACK_AddCallback(TRANSPORT_SS7_INFO(tc).statusCallbacks,
                             MTP3_Status, NULL);
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
MTP3_Deregister(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control* tc = (TRANSPORT_Control *)object;

    /*
     * avoid MTP2 links by not registering callbacks here
     */
    if (TRANSPORT_MASK(tc) & ITS_SS7_MASK_CCITT &&
        !(TRANSPORT_MASK(tc) & ITS_FLAG_MTP2))
    {
        CALLBACK_RemCallback(TRANSPORT_SS7_INFO(tc).pauseCallbacks,
                             MTP3_Pause, NULL);
        CALLBACK_RemCallback(TRANSPORT_SS7_INFO(tc).resumeCallbacks,
                             MTP3_Resume, NULL);
        CALLBACK_RemCallback(TRANSPORT_SS7_INFO(tc).statusCallbacks,
                             MTP3_Status, NULL);
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
OutputAlarmToFile(char *data)
{
    /*
     * MLM: Somebody should be shot.  This
     * a) has no destructor
     * b) the original code here wouldn't have worked.
     * c) why go through this trouble just to write to a file.
     *
     * FIXME REAL SOON
     */
#if 0
    if (mtp3AlarmsOutput == NULL)
    {
        mtp3AlarmsOutput = (TRACE_OutputMethod *)
                            ITS_ConstructObject(itsTRACE_OutputFileClass,
                                                "ITU-MTP3 Alarms",
                                                ITS_TRUE,
                                                MTP3_ALARM_FILE_NAME);
    }

    if (mtp3AlarmsOutput)
    {
        PPrint((RINGBUF_Manager *)TRACE_OUTPUT_DATA(mtp3AlarmsOutput),
               "%s", data);
        RINGBUF_Flush((RINGBUF_Manager *)TRACE_OUTPUT_DATA(mtp3AlarmsOutput));
    }
#endif
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
CloseAlarmFile(char *data)
{

#if !defined(NO_FILESYSTEM)
    fclose((FILE *)TRACE_OUTPUT_DATA(mtp3AlarmsOutput));
#endif

    TRACE_OUTPUT_DATA(mtp3AlarmsOutput) = NULL;

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
void
MTP3_Alarms_CCITT(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData
)
{
    ALARM_Format    alarm;
    char            alarmDesc[ITS_PATH_MAX << 1];
    ITS_EVENT       *event = (ITS_EVENT *)callData;
    char            *token;
    char            alarmText[ITS_PATH_MAX << 2] ;
    int             index = 0;

    time_t now;                   /* Current time */
    struct tm *now_time;

#if !defined(WIN32) && !defined(TANDEM)
    struct tm tbuf;
#endif

#define MTP3_ALARM_OUTPUT 400

    char alarmOutput[MTP3_ALARM_OUTPUT];

    memset(alarmText, 0, ITS_PATH_MAX << 2);
    memset(alarmDesc, 0, ITS_PATH_MAX << 1);
    memset(&alarm, 0, sizeof(ALARM_Format));

    memcpy(alarmText, event->data, event->len);

    token = strtok(alarmText, "|");

    alarm.id = (ITS_UINT)atoi(token);

    if (alarm.id >= CCITT_MTP3_ALARM_START &&
        alarm.id <= CCITT_MTP3_ALARM_END)
    {

        /*MTP3_ERROR(("MTP3_ALARM: %s \n", alarmText));*/

        while ( token != NULL )
        {
            switch ( index )
            {
            case 0:
                alarm.id = (ITS_UINT)atoi(token);
                index++;
                token = strtok(NULL, "|");
                break;
            case 1:         /* Sussystem string */
                alarm.subsys = token;
                index++;
                token = strtok(NULL, "|");
                break;
            case 2:         /* Alarm severity */
                alarm.severity = (ITS_UINT)atoi(token);
                index++;
                token = strtok(NULL, "|");
                break;
            case 3:         /* Alarm object */
                alarm.object = token;
                index++;
                token = strtok(NULL, "|");
                break;
            case 4:         /* Alarm description */
                alarm.desc  = token;
                index++;
                token = strtok(NULL, "|");
                break;
            case 5:         /* Alarm file name */
                index++;
                token = strtok(NULL, "|");
                break;
            case 6:         /* Alarm function*/
                alarm.func = token;
                index++;
                token = strtok(NULL, "|");
                break;
            case 7:         /* Alarm line number */
                index++;
                token = strtok(NULL, "|");
                break;
            case 8:         /* Alarm cariable desc*/
                index++;
            strcpy(alarmDesc, alarm.desc);
            strcat(alarmDesc, "\nText: ");
            strcat(alarmDesc, token);
            alarm.desc = alarmDesc;


                token = strtok(NULL, "|");
                break;
            default:
                token = NULL;
                break;
            }
        }

        now = TIMERS_Time();

        memset(alarmOutput, 0, sizeof(MTP3_ALARM_OUTPUT));

#if defined(WIN32) || defined(TANDEM)
        now_time = localtime(&now);

        strftime(alarmOutput, MTP3_ALARM_OUTPUT, "[%b%d %Y %H:%M:%S] ",
                 now_time); /* [MMMDD YY, HH:MM:SS\0]  */
#else
        now_time = localtime_r(&now, &tbuf);

        strftime(alarmOutput, MTP3_ALARM_OUTPUT, "[%b%d %Y %H:%M:%S] ",
                 &tbuf); /* [MMMDD YY, HH:MM:SS\0]  */
#endif

        sprintf(alarmText,"\n%s: %6d %10s \n%-25s %s",
                alarm.subsys,
                alarm.id,
                ALARM_LEVEL_TO_TEXT(alarm.severity),
                alarm.func,
                alarm.desc);


        strcat(alarmOutput, alarmText);

        strcat(alarmOutput,"\n---------------------------------------------\n");

        OutputAlarmToFile(alarmOutput);

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
int
INTELLINET_MTP3_Initialize_CCITT(ITS_SS7_HANDLE handle)
{
    int i, j, ret;
    ITS_Class dbClass;
    RESFILE_Manager *res;
    char *name;
    char value[ITS_PATH_MAX];

    if (started)
    {
        return (ITS_SUCCESS);
    }

    started = ITS_TRUE;
    stopped = ITS_FALSE;

    if ((__MTP3_CCITT_RcvQueue = TQUEUETRAN_CreateTransport("ITU-MTP3",
                                                            ITS_MTP3_SRC,
                                                            ITS_MTP3)) == NULL)
    {
        started = ITS_FALSE;

        return (ITS_ENOTRANSPORT);
    }

    res = TRANSPORT_RES(__MTP3_CCITT_RcvQueue);
    name = TRANSPORT_NAME(__MTP3_CCITT_RcvQueue);

    ret = MTP3_Init_CCITT(res, name);
    if (ret != ITS_SUCCESS)
    {
        TQUEUETRAN_DeleteTransport(__MTP3_CCITT_RcvQueue);

        return (ret);
    }

    if (res)
    {
        /* get the number of threads */
        if (RESFILE_GetKeyValueOf(res, name, NUM_THREADS_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            numThreads = atoi(value);
            if (numThreads < 1)
            {
                numThreads = 1;
            }
        }
    }

    if ((mtp3Thread = (ITS_THREAD *)malloc(numThreads *
                                           sizeof(ITS_THREAD))) == NULL)
    {
        MTP3_CRITICAL(("MTP3_Initialize: couldn't create thread array\n"));

        MTP3_Term_CCITT();

        TQUEUETRAN_DeleteTransport(__MTP3_CCITT_RcvQueue);

        started = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    for (i = 0; i < numThreads; i++)
    {
        if (THREAD_CreateThread(&mtp3Thread[i], 0, CCITT_MTP3Thread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            MTP3_CRITICAL(("MTP3_Initialize: couldn't create thread\n"));

            for (j = 0; j < i; j++)
            {
                THREAD_KillThread(&mtp3Thread[j]);

                THREAD_DeleteThread(&mtp3Thread[j]);
            }

            free(mtp3Thread);

            MTP3_Term_CCITT();

            TQUEUETRAN_DeleteTransport(__MTP3_CCITT_RcvQueue);

            started = ITS_FALSE;

            return (ITS_EBADTHREAD);
        }
    }

    CALLBACK_AddCallback(TRANSPORT_registrations, MTP3_Register, NULL);
    CALLBACK_AddCallback(TRANSPORT_deregistrations, MTP3_Deregister, NULL);

    /* register Alarm Callback */
    CALLBACK_AddCallback(ALARM_Callbacks, MTP3_Alarms_CCITT, NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_AddDoCommand(MTP3_Console_CCITT);
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
void
INTELLINET_MTP3_Terminate_CCITT(ITS_SS7_HANDLE handle)
{
    int i;
    ITS_EVENT ev;
    void *status;
    ITS_Class dbClass;

    if (!started)
    {
        return;
    }

    if (stopped)
    {
        return;
    }

    stopped = ITS_TRUE;
    started = ITS_FALSE;

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_RemDoCommand(MTP3_Console_CCITT);
    }

    CALLBACK_RemCallback(TRANSPORT_deregistrations, MTP3_Deregister, NULL);
    CALLBACK_RemCallback(TRANSPORT_registrations, MTP3_Register, NULL);
    CALLBACK_RemCallback(ALARM_Callbacks, MTP3_Alarms_CCITT, NULL);


    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, 0);

    for (i = 0; i < numThreads; i++)
    {
        TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
    }

    for (i = 0; i < numThreads; i++)
    {
        THREAD_WaitForThread(&mtp3Thread[i], &status);

        THREAD_DeleteThread(&mtp3Thread[i]);
    }

    free(mtp3Thread);

    ITS_C_ASSERT(__MTP3_CCITT_RcvQueue != NULL);
    TQUEUETRAN_DeleteTransport(__MTP3_CCITT_RcvQueue);
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
THREAD_RET_TYPE
CCITT_MTP3Thread(void *arg)
{
    ITS_EVENT mtp3Event;
    ITS_BOOLEAN cont;
    ITS_TimerData *td;

    memset(&mtp3Event, 0, sizeof(ITS_EVENT));

    cont = ITS_TRUE;

    TRANSPORT_IS_ACTIVE(__MTP3_CCITT_RcvQueue) = ITS_TRUE;

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__MTP3_CCITT_RcvQueue))
                                                        (__MTP3_CCITT_RcvQueue,
                                                         &mtp3Event)
           == ITS_SUCCESS)
    {
        switch (mtp3Event.src)
        {
        case ITS_MTP3_SRC:
            MTP3_DEBUG(("MTP3_Main: handle termination event.\n"));

            TRANSPORT_IS_ACTIVE(__MTP3_CCITT_RcvQueue) = ITS_FALSE;

            cont = ITS_FALSE;
            break;

        case ITS_SCCP_SRC:
        case ITS_ISUP_SRC:
            MTP3_DEBUG(("MTP3_Main: handle L4 msg.\n"));

            if (MTP3_MSG_TYPE(&mtp3Event) != MTP3_MSG_USER_DATA)
            {
                MTP3_DEBUG(("MTP3_Main: message type is not user data: %d\n",
                            MTP3_MSG_TYPE(&mtp3Event)));

                break;
            }

            if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Failed to get route lock\n"));

                break;
            }

            SMH_Main_CCITT(MTP3_L4, MTP3_SMH_HMRT,
                           SMH_TRIGGER_L4_L3_MSG,
                           mtp3Event.data, mtp3Event.len,
                           ITS_SS7_DEFAULT_LINK_SET,
                           ITS_SS7_DEFAULT_LINK_CODE);

            ROUTE_UnlockRead(routeRWLock, __MTP3_CCITT_RcvQueue);
            break;

        case ITS_TIMER_SRC:
        {
            MTP3_TimerContext ctxt;
            
            MTP3_DEBUG(("MTP3_Main: handle TIMER msg.\n"));

            if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
            {
                MTP3_ERROR(("Failed to get route lock\n"));

                break;
            }

            td = (ITS_TimerData *)mtp3Event.data;
            memcpy(&ctxt, td->context, sizeof(MTP3_TimerContext));

            MTP3_HandleTimerEvent_CCITT(td);
            
            LINKSET_CommitLinkSet(
                    LINKSET_FindLinkSet(ctxt.data.linkInfo.linkSet));

            
            ROUTE_UnlockWrite(routeRWLock);
            break;
 
        }
        default:

            if (MTP3_MSG_TYPE(&mtp3Event) == MTP3_MSG_USER_DATA)
            {
                MTP3_DEBUG(("MTP3_Main: handle L4 msg.\n"));

                if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
                {
                    MTP3_ERROR(("Failed to get route lock\n"));

                    break;
                }

                SMH_Main_CCITT(MTP3_L4, MTP3_SMH_HMRT,
                               SMH_TRIGGER_L4_L3_MSG,
                               mtp3Event.data, mtp3Event.len,
                               ITS_SS7_DEFAULT_LINK_SET,
                               ITS_SS7_DEFAULT_LINK_CODE);

                ROUTE_UnlockRead(routeRWLock, __MTP3_CCITT_RcvQueue );
            }
            else
            {
                ITS_OCTET linkSet, linkCode;
                ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
                ITS_USHORT len;

                MTP3_DEBUG(("MTP3_Main: handle L2 msg.\n"));

                if (MTP2_ReceiveData_CCITT(&mtp3Event, &linkSet, &linkCode,
                                           buf, &len) != ITS_SUCCESS)
                {
                    MTP3_WARNING(("Failed to receive L2 data\n"));

                    MTP3_Alarm_CCITT(2405, __FILE__, __LINE__, NULL);
                }
                else
                {
                    ITS_BOOLEAN isLockSet = ITS_FALSE;

                    if (MTP3_NeedLock_CCITT(buf))
                    {
                        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
                        {
                            MTP3_ERROR(("Failed to get route lock\n"));

                            break;
                        }
                        isLockSet = ITS_TRUE;
                    }
                    else
                    {
                        if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
                        {
                            MTP3_ERROR(("Failed to get route lock\n"));

                            break;
                        }
                    }


                    SMH_Main_CCITT(MTP3_L2, MTP3_SMH_HMDT,
                                   SMH_TRIGGER_L2_L3_MSG,
                                   buf, len,
                                   linkSet, linkCode);

                    if (isLockSet)
                    {
                        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
                        ROUTE_UnlockWrite(routeRWLock);
                    }
                    else
                    {
                        ROUTE_UnlockRead(routeRWLock, __MTP3_CCITT_RcvQueue);
                    }

                }
           
            }

            break;
        }
    }

    TRANSPORT_IS_ACTIVE(__MTP3_CCITT_RcvQueue) = ITS_FALSE;

    THREAD_NORMAL_EXIT;
}

static void
DumpGlobalPegId(DBC_Server *dbc)
{

     char buf[ITS_PATH_MAX];

     sprintf(buf, "\n*****Printing Global Pegs****************\n");
     DBC_AppendText(dbc, buf);

     /* Print the pegs and their assciated Id's */
     sprintf(buf, "\n%12s %20d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_PAUSE),
             PEG_MTP3_MSG_PAUSE);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_RESUME),
             PEG_MTP3_MSG_RESUME);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_STATUS),
             PEG_MTP3_MSG_STATUS);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_INITIALIZE),
             PEG_MTP3_INITIALIZE);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %20d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TERMINATE),
             PEG_MTP3_TERMINATE);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %9d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_RECEIVED_INERROR),
             PEG_MTP3_MSG_RECEIVED_INERROR);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CHANGEOVER),
             PEG_MTP3_CHANGEOVER);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CHANGEBACK),
             PEG_MTP3_CHANGEBACK);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %15d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_SL_UNAVAILABLE),
             PEG_MTP3_SL_UNAVAILABLE);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %17d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_INHIBIT),
             PEG_MTP3_LINK_INHIBIT);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %15d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_UNINHIBIT),
             PEG_MTP3_LINK_UNINHIBIT);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %9d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_FORCE_UNINHIBIT),
             PEG_MTP3_LINK_FORCE_UNINHIBIT);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CONGESTION),
             PEG_MTP3_CONGESTION);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %14d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_SLS_UNAVAILABLE),
             PEG_MTP3_SLS_UNAVAILABLE);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %17d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TFC_RECEIVED),
             PEG_MTP3_TFC_RECEIVED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %17d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TFA_RECEIVED),
             PEG_MTP3_TFA_RECEIVED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %9d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_ROUTESET_UNAVAILABLE),
             PEG_MTP3_ROUTESET_UNAVAILABLE);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %6d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_ADJECENT_SP_UNACCESIBLE),
             PEG_MTP3_ADJECENT_SP_UNACCESIBLE);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %14d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_USERPART_ENABLE),
             PEG_MTP3_USERPART_ENABLE);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %13d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_USERPART_DISABLE),
             PEG_MTP3_USERPART_DISABLE);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T1_EXPIRED),
             PEG_MTP3_T1_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T2_EXPIRED),
             PEG_MTP3_T2_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T3_EXPIRED),
             PEG_MTP3_T3_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T4_EXPIRED),
             PEG_MTP3_T4_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T5_EXPIRED),
             PEG_MTP3_T5_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T6_EXPIRED),
             PEG_MTP3_T6_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T7_EXPIRED),
             PEG_MTP3_T7_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T8_EXPIRED),
             PEG_MTP3_T8_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %19d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T9_EXPIRED),
             PEG_MTP3_T9_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T10_EXPIRED),
             PEG_MTP3_T10_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T11_EXPIRED),
             PEG_MTP3_T11_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T12_EXPIRED),
             PEG_MTP3_T12_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T13_EXPIRED),
             PEG_MTP3_T13_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T14_EXPIRED),
             PEG_MTP3_T14_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T15_EXPIRED),
             PEG_MTP3_T15_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T16_EXPIRED),
             PEG_MTP3_T16_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T17_EXPIRED),
             PEG_MTP3_T17_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T18_EXPIRED),
             PEG_MTP3_T18_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T19_EXPIRED),
             PEG_MTP3_T19_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T20_EXPIRED),
             PEG_MTP3_T20_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T21_EXPIRED),
             PEG_MTP3_T21_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T22_EXPIRED),
             PEG_MTP3_T22_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T23_EXPIRED),
             PEG_MTP3_T23_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T24_EXPIRED),
             PEG_MTP3_T24_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T25_EXPIRED),
             PEG_MTP3_T25_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T26_EXPIRED),
             PEG_MTP3_T26_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T27_EXPIRED),
             PEG_MTP3_T27_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T28_EXPIRED),
             PEG_MTP3_T28_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T29_EXPIRED),
             PEG_MTP3_T29_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T30_EXPIRED),
             PEG_MTP3_T30_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T31_EXPIRED),
             PEG_MTP3_T31_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T32_EXPIRED),
             PEG_MTP3_T32_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T33_EXPIRED),
             PEG_MTP3_T33_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s %18d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T34_EXPIRED),
             PEG_MTP3_T34_EXPIRED);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n*******************************************\n");
     DBC_AppendText(dbc, buf);
}

static void
DumpGlobalPegs(DBC_Server *dbc)
{
     char buf[ITS_PATH_MAX];

     sprintf(buf, "\n*****Printing Global Pegs****************\n");
     DBC_AppendText(dbc, buf);

     /* Print the pegs and their assciated Id's */
     sprintf(buf, "\n%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_PAUSE),
              PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_PAUSE));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_RESUME),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RESUME));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_STATUS),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_STATUS));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_INITIALIZE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_INITIALIZE));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TERMINATE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TERMINATE));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:   value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_RECEIVED_INERROR),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RECEIVED_INERROR));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CHANGEOVER),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CHANGEBACK),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:         value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_SL_UNAVAILABLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SL_UNAVAILABLE));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:           value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_INHIBIT),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:         value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_UNINHIBIT),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:   value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_FORCE_UNINHIBIT),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CONGESTION),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CONGESTION));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:        value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_SLS_UNAVAILABLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLS_UNAVAILABLE));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:           value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TFC_RECEIVED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFC_RECEIVED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:           value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TFA_RECEIVED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_RECEIVED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:   value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_ROUTESET_UNAVAILABLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ROUTESET_UNAVAILABLE));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_ADJECENT_SP_UNACCESIBLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:         value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_USERPART_ENABLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_ENABLE));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:        value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_USERPART_DISABLE),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_DISABLE));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T1_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T1_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T2_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T2_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T3_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T3_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T4_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T4_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T5_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T5_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T6_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T6_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T7_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T7_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T8_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T8_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T9_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T9_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T10_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T10_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T11_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T11_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T12_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T12_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T13_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T13_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T14_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T14_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T15_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T15_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T16_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T16_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T17_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T17_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T18_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T18_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T19_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T19_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T20_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T20_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T21_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T21_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T22_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T22_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T23_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T23_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T24_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T24_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T25_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T25_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T26_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T26_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T27_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T27_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T28_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T28_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T29_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T29_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T30_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T30_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T31_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T31_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T32_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T32_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T33_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T33_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T34_EXPIRED),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T34_EXPIRED));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n*******************************************\n");
     DBC_AppendText(dbc, buf);
}

static void
DumpLinkPegId(DBC_Server *dbc)
{
     char buf[ITS_PATH_MAX];

     sprintf(buf, "\n*****Printing Link Level Pegs************\n");
     DBC_AppendText(dbc, buf);

     /* Print the pegs and their assciated Id's */
#if 0
     sprintf(buf, "PEG_MTP3_LINK_MSU_TX                    %3d\n",PEG_MTP3_LINK_MSU_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_MSU_RX                    %3d\n",PEG_MTP3_LINK_MSU_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_OCTETS_TX                 %3d\n",PEG_MTP3_LINK_OCTETS_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_OCTETS_RX                 %3d\n",PEG_MTP3_LINK_OCTETS_RX);
     DBC_AppendText(dbc, buf);
#endif

     sprintf(buf, "PEG_MTP3_LINK_COO_TX                    %3d\n",PEG_MTP3_LINK_COO_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_COO_RX                    %3d\n",PEG_MTP3_LINK_COO_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_COA_TX                    %3d\n", PEG_MTP3_LINK_COA_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_COA_RX                    %3d\n",PEG_MTP3_LINK_COA_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECO_TX                    %3d\n",PEG_MTP3_LINK_ECO_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECO_RX                    %3d\n",PEG_MTP3_LINK_ECO_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECA_TX                    %3d\n",PEG_MTP3_LINK_ECA_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECA_RX                    %3d\n",PEG_MTP3_LINK_ECA_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBD_TX                    %3d\n",PEG_MTP3_LINK_CBD_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBD_RX                    %3d\n",PEG_MTP3_LINK_CBD_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBA_TX                    %3d\n",PEG_MTP3_LINK_CBA_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBA_RX                    %3d\n",PEG_MTP3_LINK_CBA_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIN_TX                    %3d\n",PEG_MTP3_LINK_LIN_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIN_RX                    %3d\n",PEG_MTP3_LINK_LIN_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIA_TX                    %3d\n",PEG_MTP3_LINK_LIA_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIA_RX                    %3d\n",PEG_MTP3_LINK_LIA_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUN_TX                    %3d\n",PEG_MTP3_LINK_LUN_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUN_RX                    %3d\n",PEG_MTP3_LINK_LUN_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUA_TX                    %3d\n",PEG_MTP3_LINK_LUA_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUA_RX                    %3d\n",PEG_MTP3_LINK_LUA_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LID_TX                    %3d\n",PEG_MTP3_LINK_LID_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LID_RX                    %3d\n",PEG_MTP3_LINK_LID_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LFU_TX                    %3d\n",PEG_MTP3_LINK_LFU_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LFU_RX                    %3d\n",PEG_MTP3_LINK_LFU_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LLI_TX                    %3d\n",PEG_MTP3_LINK_LLI_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LLI_RX                    %3d\n",PEG_MTP3_LINK_LLI_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LRI_TX                    %3d\n",PEG_MTP3_LINK_LRI_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_LRI_RX                    %3d\n",PEG_MTP3_LINK_LRI_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_DLC_TX                    %3d\n",PEG_MTP3_LINK_DLC_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_DLC_RX                    %3d\n",PEG_MTP3_LINK_DLC_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_CSS_TX                    %3d\n",PEG_MTP3_LINK_CSS_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_CSS_RX                    %3d\n",PEG_MTP3_LINK_CSS_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNS_TX                    %3d\n",PEG_MTP3_LINK_CNS_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNS_RX                    %3d\n",PEG_MTP3_LINK_CNS_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNP_TX                    %3d\n",PEG_MTP3_LINK_CNP_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNP_RX                    %3d\n",PEG_MTP3_LINK_CNP_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_UPU_TX                    %3d\n",PEG_MTP3_LINK_UPU_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_UPU_RX                    %3d\n",PEG_MTP3_LINK_UPU_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTM_TX                   %3d\n",PEG_MTP3_LINK_SLTM_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTM_RX                   %3d\n",PEG_MTP3_LINK_SLTM_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTA_TX                   %3d\n",PEG_MTP3_LINK_SLTA_TX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTA_RX                   %3d\n",PEG_MTP3_LINK_SLTA_RX);
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n*******************************************\n");
     DBC_AppendText(dbc, buf);
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
void static
ShutDownNode(DBC_Server *dbc)
{
    TRANSPORT_Manager *tm;
    TRANSPORT_Control *tr;
    ITS_UINT mask;
    char buf[ITS_PATH_MAX];

    tm = TRANSPORT_GetManager();

    if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
    {
         return;
    }

    for ( tr = tm->listHead;
          tr != NULL; tr = TRANSPORT_HMI_NEXT(tr))
    {
        mask = TRANSPORT_MASK(tr);

        if ((mask & ITS_MTP2_CCITT) == ITS_MTP2_CCITT)
        {
            SS7_LinkPtr lp;

            for (lp = TRANSPORT_SS7_INFO(tr).linkInfo;
                 lp != NULL; lp = lp->next)
            {
               sprintf(buf, "Deactivating ls:%d lc:%d\n",
                       lp->linkSet->linkSet, lp->linkCode);

               DBC_AppendText(dbc, buf);

               MGMT_Main_CCITT(MTP3_USER,
                               MGMT_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               lp->linkSet->linkSet, lp->linkCode);
            }

        }
    }

    RWLOCK_UnlockShared(&tm->transportGate);
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
void
MTP3_Console_CCITT(DBC_Server *dbc, const char *cmdLine)
{    
    char buf[ITS_PATH_MAX];
    int linkSet = 0, linkCode = 0, ret = 0;
    ITS_UINT value;
    SS7_LinkPtr ln; 
    SS7_LinkSetPtr ls;
    ITS_UINT i;

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "mi_get_gen_cfg", "MTP3 Get General Config", "", ""))
    {
        MTP3GeneralCfg *cfg = 0;
        cfg =  MTP3_GetGeneralCfg_CCITT();
        sprintf(buf, "\n*********** MTP3 General Config *************\n");
        DBC_AppendText(dbc, buf);

        i = cfg->alarmLevel;

        switch(i)
        {
            case ALARM_LVL_CRIT :
                sprintf(buf, "\n    Alarm Level:  CRITICAL\n");
            break;

            case ALARM_LVL_MAJOR :
                sprintf(buf, "\n    Alarm Level:  MAJOR\n");
            break;

            case ALARM_LVL_MINOR :
                sprintf(buf, "\n    Alarm Level:  MINOR\n");
            break;

            case ALARM_LVL_INFO :
                sprintf(buf, "\n    Alarm Level:  INFO\n");
            break;

            case ALARM_LVL_OFF :
                sprintf(buf, "\n    Alarm Level:  OFF\n");
            break;

            default :
                sprintf(buf, "\n    Alarm Level Not Set\n");
            break;
        }

        DBC_AppendText(dbc, buf);
        strcpy(buf, "\n    MTP3 Trace -\n");
        DBC_AppendText(dbc, buf);

        if ( cfg->traceOn)
        {
           if (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_DEBUG))
           {
               strcpy(buf, "        Debug     = ");
               if(TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      1))
               {
                    strcat(buf, " file");
               }
               else if (!TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                              MTP3_TRACE_DEBUG,
                                              0))
               {
                   strcpy(buf, "        Debug     = null");
               }
           }
           else
           {
               strcpy(buf, "        Debug     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_ABORT))
           {
               strcpy(buf, "        Critical  = ");
               if(TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      1))
               {
                    strcat(buf, " file");
               }
               else if (!TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                               MTP3_TRACE_ABORT,
                                               0))
               {
                  strcpy(buf, "        Critical  = null");
               }
           }
           else
           {
               strcpy(buf, "        Critical  = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_WARNING))
           {
               strcpy(buf, "        Warning   = ");
               if(TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      1))
               {
                    strcat(buf, " file");
               }
               else if (!TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                            MTP3_TRACE_WARNING,
                                            0))
               {
                   strcpy(buf, "        Warning   = null");
               }
           }
           else
           {
               strcpy(buf, "        Warning   = null");
           }

           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_ERROR))
           {
               strcpy(buf, "        Error     = ");
               if(TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      1))
               {
                    strcat(buf, " file");
               }
               else if (!TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                              MTP3_TRACE_ERROR,
                                              0))
               {
                   strcpy(buf, "        Error     = null");
               } 
           }
           else
           {
               strcpy(buf, "        Error     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);
       }
       else
       {
           strcpy(buf, "        Debug     = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Critical  = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Warning   = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Error     = null\n");
           DBC_AppendText(dbc, buf);

       }
        sprintf(buf, "\n*********** End of MTP3 General Config ***********\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_set_gen_cfg", "MTP3 Set General Config",
                     "<alarm level> <Trace Type> <traceOutput> <On/Off>",""))
    {
        MTP3GeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType,
                     traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: mi_set_gen_cfg <alarmlevel> <tracetype>" 
                         " <trOutput> <On/Off>\n"
                          "See help to see possible values\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(alarmLevel, "CRITICAL") != NULL ||
            strstr(alarmLevel, "critical") != NULL)
        {
            cfg.alarmLevel = ALARM_LVL_CRIT;
        }
        else if (strstr(alarmLevel, "MAJOR") ||
                strstr(alarmLevel, "major") )
        {
            cfg.alarmLevel = ALARM_LVL_MAJOR;
        }
        else if (strstr(alarmLevel, "MINOR") ||
                strstr(alarmLevel, "minor"))
        {
            cfg.alarmLevel = ALARM_LVL_MINOR;
        }
        else if (strstr(alarmLevel, "INFO") ||
                 strstr(alarmLevel, "info"))
        {
            cfg.alarmLevel = ALARM_LVL_INFO;
        }
        else if (strstr(alarmLevel, "OFF") ||
                strstr(alarmLevel, "off") )
        {
            cfg.alarmLevel = ALARM_LVL_OFF;
        }
        else
        {
            sprintf(buf, "\nInvalid Alarm Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOn, "ON") || strstr(traceOn, "on"))
        {
            cfg.traceOn = ITS_TRUE;
        }
        else if (strstr(traceOn, "OFF") || strstr(traceOn, "off"))
        {
            cfg.traceOn = ITS_FALSE;
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, MTP3_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, MTP3_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, MTP3_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, MTP3_ERROR_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, MTP3_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, MTP3_FILE_STRING);
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  MTP3_SetGeneralCfg_CCITT(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

       sprintf(buf, "\n*********** MTP3 General Config Set*************\n");
       DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "mi_in_link", "Inhibit Link", "<linkset> <linkcode>",  ""))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: mi_in_link <linkset> <linkcode>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = MGMT_Main_CCITT(MTP3_USER,
                              MGMT_TRIGGER_INHIBIT_LINK,
                              NULL, 0,
                              (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Link  %d:%d inhibition failed: reason %s\n***\n",
                    linkSet, linkCode, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Link %d:%d Inhibition initiated*** \n", linkSet, linkCode);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "mi_unin_link", "Uninhibit Link", 
             "<linkset> <linkcode>", ""))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_unin_link <linkset> <linkcode>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = MGMT_Main_CCITT(MTP3_USER,
                              MGMT_TRIGGER_UNINHIBIT_LINK,
                              NULL, 0,
                              (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Link  %d:%d uninhibition failed: reason %s\n***\n",
                    linkSet, linkCode, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Link %d:%d Uninhibition initiated***\n", linkSet, linkCode);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_deact_ls", "Deactivate Link Set", "<linkset>", ""))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_deact_ls <linkset> \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkSet)) == NULL)
        {
            sprintf(buf, "\n***Linkset %d not configured***\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = MGMT_Main_CCITT(MTP3_USER,
                              MGMT_TRIGGER_DEACTIVATE_LINK_SET,
                              NULL, 0,
                              (ITS_OCTET)linkSet, ITS_SS7_DEFAULT_LINK_CODE);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Linkset %d deactivation failed: reason %s***\n",
                    linkSet, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Linkset %d Deactivation initiated***\n", linkSet);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_act_ls", "Activate Link Set", "<linkset>", ""))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_act_ls <linkset> \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkSet)) == NULL)
        {
            sprintf(buf, "\n***Linkset %d not configured***\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        ret= MGMT_Main_CCITT(MTP3_USER,
                             MGMT_TRIGGER_ACTIVATE_LINK_SET,
                             NULL, 0,
                             (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Linkset %d activation failed:reason %s***\n",
                    linkSet, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Linkset %d Activation initiated***\n", linkSet);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_deact_link", "Deactivate Link", 
             "<linkset> <linkcode>", ""))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_deact_link <linkset> <linkcode> \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        ret= MGMT_Main_CCITT(MTP3_USER,
                             MGMT_TRIGGER_DEACTIVATE_LINK,
                             NULL, 0,
                             (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Link %d:%d deactivation failed:reason %s***\n",
                    linkSet, linkCode, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Link %d:%d Deactivation initiated***\n", linkSet, linkCode);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_act_link", "Activate Link", 
             "<linkset> <linkcode>", ""))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n" 
                         "Usage: mi_act_link <linkset> <linkcode> \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        ret= MGMT_Main_CCITT(MTP3_USER,
                             MGMT_TRIGGER_ACTIVATE_LINK,
                             NULL, 0,
                             (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf,"\n***Linkset %d activation failed: reason %s***\n",
                    linkSet, ITS_GetErrorText(ret));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n***Link %d:%d Activation initiated***\n", linkSet, linkCode);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_start", "Start MTP3", "", ""))
    {
        sprintf(buf, "\n*********** Starting MTP3 **************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_RESTART,
                        NULL, 0,
                        ITS_SS7_DEFAULT_LINK_SET,
                        ITS_SS7_DEFAULT_LINK_CODE);

    }
    else if (DBC_Cmd(dbc, "mi_get_ls", "Dump Link Sets", "", ""))
    {
        char *dump = NULL;

        ROUTE_LockForWrite(routeRWLock);

        LINKSET_DumpLinkSetHashtable(&dump);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        }
    }
#if 0
    else if (DBC_Cmd(dbc, "mi_get_rt", "Dump Routes Info", "<>", "<>"))
    {
        char *dump = NULL;

        ROUTE_LockForWrite(routeRWLock);

        ROUTE_DumpSS7ToIdHashtable(&dump);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
	    free(dump);
        }

    }
#endif
    else if (DBC_Cmd(dbc, "mi_get_link", "get Link Status", 
             "<linkset> <linkcode>", ""))
    {
        char *dump = NULL;

        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);

        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: mi_get_link <linkset> <linkcode>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ROUTE_LockForWrite(routeRWLock);

        LINK_DumpLinkInfo(&dump, (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        }

    }
    else if (DBC_Cmd(dbc, "mi_get_gen_pegs", "Get MTP3 General Pegs", 
             "<Peg>", ""))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT pg = PEG_MTP3_NUM_PEGS;
        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
             sprintf(buf,  "\n**** Invalid Command Arguments *******\n"
                           "Usage: mi_get_gen_pegs [<Peg> or <All/all>]\n"); 
             DBC_AppendText(dbc, buf);
             return;
        }

        if(strncmp(pgName, "All", 3) == 0 ||
           strncmp(pgName, "all", 3) == 0)
        {
           DumpGlobalPegs(dbc);
           return;
        }

        for (i = 0; i < PEG_MTP3_NUM_PEGS; i++)
        {
            if ( strstr(pgName, mtp3GPegStr[i]))
            {
                pg = i;
                break;
            }
        }

        if (pg == PEG_MTP3_NUM_PEGS)
        {
            sprintf(buf, "\n   **** Invalid Peg Type *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n   %s \n", pgName);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(CCITT_MTP3_Pegs, pg);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_get_link_pegs", "Get Link Level Pegs", 
             "<linkset> <linkcode><Peg>", ""))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT pg = PEG_MTP3_LINK_NUM_PEGS;
        ret = sscanf(cmdLine, "%s %d %d %s", buf, &linkSet, &linkCode, pgName);
        if (ret != 4)
        {
            sprintf(buf,  "\n**** Invalid Command Arguments *******\n"
                          "Usage: mi_get_link_pegs <linkset> <linkcode> <Peg#>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        for (i = 0; i < PEG_MTP3_LINK_NUM_PEGS; i++)
        {
            if ( strstr(pgName, mtp3LPegStr[i]))
            {
                pg = i;
                break;
            }
        }

        if (pg == PEG_MTP3_LINK_NUM_PEGS)
        {
            sprintf(buf, "\n   **** Invalid Peg Type *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        value = PEG_GetPeg(&ln->MTP3_LINK_PEGS,pg);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_get_gen_pegid", "Show all general peg IDs", "", ""))
    {
        DumpGlobalPegId(dbc);
    }
    else if (DBC_Cmd(dbc, "mi_get_link_pegid", "Show all link level peg IDs", "", ""))
    {
        DumpLinkPegId(dbc);
    }
    else if (DBC_Cmd(dbc, "mi_clr_gen_pegs", "MTP3 Reset a particular gen Peg",
                          "[<Pegid> (or) <All/all>]",""))
    {
        char pegType[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s", buf, pegType);

        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: mi_clr_gen_pegs [<Pegid> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if(strncmp(pegType, "All", 3) == 0 ||
           strncmp(pegType, "all", 3) == 0)
        {
           for (i = 0; i < PEG_MTP3_NUM_PEGS; i++)
           {
               PEG_ClearPeg(CCITT_MTP3_Pegs, i);
           }

           sprintf(buf, "\n** Cleared all MTP3 gen pegs **\n");
           DBC_AppendText(dbc, buf);
           return;
        }
        else
        {
           if(!isdigit((int)pegType[0]))
           {
              sprintf(buf, "\n**** Unrecognized Peg *****\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }

        if ( atoi(pegType) > PEG_MTP3_NUM_PEGS - 1)
        {
             sprintf(buf, "\n** MTP3 general peg %d does not exist **\n",
                                                       atoi(pegType));
             DBC_AppendText(dbc, buf);
             return;
         }
         for (i = 0; i < PEG_MTP3_NUM_PEGS; i++)
         {
             if (i == (ITS_UINT)RESFILE_ParseNum(pegType))
             {
                 PEG_ClearPeg(CCITT_MTP3_Pegs, i);
                 sprintf(buf, "\n** Cleared MTP3 general peg id %d **\n", i);

                 DBC_AppendText(dbc, buf);
                 break;
             }
         }
    }
    else if (DBC_Cmd(dbc, "mi_clr_link_pegs", "MTP3 Clear particular Link Peg",
                          "<linkset> <linkcode> [<Pegid> (or) <All/all>]",""))
    {
        char pegType[ITS_PATH_MAX];
        ret = sscanf(cmdLine, "%s %d %d %s", buf, &linkSet, &linkCode,pegType);
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
            "Usage: mi_clr_link_pegs <linkset> <linkcode> [<Pegid> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (atoi(pegType) > PEG_MTP3_LINK_NUM_PEGS - 1)
        {
            sprintf(buf, "\n** MTP3 Link peg %d does not exist **\n", atoi(pegType)
);
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

        if(strncmp(pegType, "All", 3) == 0 ||
           strncmp(pegType, "all", 3) == 0)
        {
           for (i = 0; i < PEG_MTP3_LINK_NUM_PEGS; i++)
           {
               PEG_ClearPeg(&ln->MTP3_LINK_PEGS, i);
           }

           sprintf(buf, "\n** Cleared all pegs for linkset %d linkcode %d**\n", 
                   linkSet,linkCode);

           DBC_AppendText(dbc, buf);
           return;
         }
         else
         {
            if(!isdigit((int)pegType[0]))
            {
               sprintf(buf, "\n**** Unrecognized Peg *****\n");
               DBC_AppendText(dbc, buf);
               return;
            }
         }

        for (i = 0; i < PEG_MTP3_LINK_NUM_PEGS; i++)
        {
            if ((ITS_UINT)RESFILE_ParseNum(pegType) == i)
            {
               PEG_ClearPeg(&ln->MTP3_LINK_PEGS, i);
               sprintf(buf, "\n** Cleared peg id %d for linkset %d linkcode %d **\n",                       i, linkSet,linkCode);
               DBC_AppendText(dbc, buf);
               break;
            }
        }
    }
#if 0
    else if (DBC_Cmd(dbc, "mi_debug_trace", "Debug Trace", "<on, off>", "<>"))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_DEBUG_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_DEBUG_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_DEBUG_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_DEBUG_STRING, ITS_FALSE);
        }
    }      
    else if (DBC_Cmd(dbc, "mi_warning_trace", "Warning Trace", "<on, off>", "<>"
))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_WARNING_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_WARNING_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_WARNING_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_WARNING_STRING, ITS_FALSE);
        }
    }     
    else if (DBC_Cmd(dbc, "mi_error_trace", "Error Trace", "<on, off>", "<>"))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_ERROR_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_ERROR_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_ERROR_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_ERROR_STRING, ITS_FALSE);
        }
    }    
#endif
    else if (DBC_Cmd(dbc, "mi_shutdown", "shutdown mtp3", "", ""))
    {
        ShutDownNode(dbc);

        TIMERS_Sleep(5);

        ENGINE_Terminate();
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
MTP3_TransportPostInit_CCITT(TPOOL_THREAD *thr , ITS_HANDLE h)
{
   
    ITS_EVENT ev;
    TRANSPORT_Control *tc = (TRANSPORT_Control *) h;
    SS7_LinkPtr link = NULL;
    int i = 0;

    /* protect from bad ITS_Initialize calls. */
    if (h == NULL)
    {
        return (ITS_EINITFAIL);
    }

    /* FIXE ME: we have to wait until all links are configured 
     * before telling MTP3 to active links. This timer will give
     * Border transports enough time to configure to links.
     */
    TIMERS_Sleep(3);

    for (link = TRANSPORT_SS7_INFO(tc).linkInfo; link != NULL; link = link->next)
    {
#if 0
        /* Initialise Pegs for this Link */
        for (i = 0; i < PEG_MTP3_LINK_NUM_PEGS; i++)
        {
            link->pegs[i] = 0;
        }
        link->MTP3_LINK_PEGS.name = "MTP3";
        link->MTP3_LINK_PEGS.numPegs =
                            sizeof(link->pegs) / sizeof(ITS_UINT);
        link->MTP3_LINK_PEGS.pegs = link->pegs;
#endif

        /* Send a message to MTP3 in order to reactivate link */
        MTP3_DEBUG(("Activate link %d \n", link->linkCode));

        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_OUT_OF_SERVICE;
        ev.data[1] = link->linkSet->linkSet;
        ev.data[2] = link->linkCode;

        TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);

    }

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *
 *  Input Parameters:
 *     
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
SetLinkUnavailable(ITS_POINTER data, void *in, void *out)
{

    ITS_EVENT ev;
    SS7_Link *link = (SS7_Link *)data;
    DSM_MembershipChangeCbData *membershipChangeCbData = 
                        (DSM_MembershipChangeCbData *) in;

    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;

    MTP3_DEBUG(("SetLinkUnavailable: linkCode:%d  nodeId %d\n", 
            link->linkCode, link->dsmNodeId));
 
    if (link->dsmNodeId == concernedNodeId) 
    {
        /* we need to mark this link unavailable */

        MTP3_DEBUG(("Deactivate link %d \n", link->linkCode));

        ITS_EVENT_INIT(&ev, ITS_MTP2_SRC,
                       3 * sizeof(ITS_OCTET));

        ev.data[0] = L2_L3_OUT_OF_SERVICE;
        ev.data[1] = link->linkSet->linkSet;
        ev.data[2] = link->linkCode; 

        TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);

        return ITS_SUCCESS;  
    

    }

    return ITS_SUCCESS;

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *
 *  Input Parameters:
 *    
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
#if 0
static int
SetLinkAvailable(ITS_POINTER data, void *in, void *out)
{

    SS7_Link *link = (SS7_Link *)data;
    DSM_MembershipChangeCbData *membershipChangeCbData =
                        (DSM_MembershipChangeCbData *) in;

    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;

    MTP3_DEBUG(("SetLinkAvailable: linkCode:%d  nodeId %d \n",
            link->linkCode, link->dsmNodeId));

    if (link->dsmNodeId == concernedNodeId)
    {
        /* we need to mark this link unavailable */
        MTP3_DEBUG(("***Activate link %d ***\n", link->linkCode));
    }

    return ITS_SUCCESS;


}
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *
 *  Input Parameters:
 *      
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
ITSSS7DLLAPI void
MTP3_MembershipChangeCallBack_CCITT(ITS_POINTER object, 
                                    ITS_POINTER userData, 
                                    ITS_POINTER callData)
{

    DSM_MembershipChangeCbData *membershipChangeCbData = 
                        (DSM_MembershipChangeCbData *) callData;

    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;

    switch (membershipChangeCbData->membershipChangeType)
    {

    case DSM_FT_GROUP_MEMBER_JOIN:   

        /* Activate links owned by the concerned node */
        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_JOIN nodeID: %d\n", concernedNodeId));

        break;

   
    case DSM_FT_GROUP_MEMBER_LEAVE: 

        /* Deactivate links owned by the concerned node */
        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_LEAVE nodeID: %d\n",concernedNodeId));
        DSM_TableIterate(DSM_Mtp3FtGroupId,
                         DSM_TABLE_LINKS, callData, NULL, SetLinkUnavailable);  
        break;

    
    case DSM_FT_GROUP_MEMBER_DEAD:

        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_DEAD nodeID: %d\n",concernedNodeId));

        break;

    case DSM_FT_GROUP_MEMBER_ALIVE:

        MTP3_DEBUG(("DSM_FT_GROUP_MEMBER_ALIVE nodeID: %d\n",concernedNodeId));

        break;

    default:

        MTP3_DEBUG(("DSM_FT_GROUP: Unknown Event nodeID: %d\n",concernedNodeId));
        break;
  
    }
} 

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the configured stack information for itu mtp3.
 *
 *  Input Parameters:
 *      Pointer to a file.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the stack informations written successfully on the given file
 *      it returns ITS_SUCCESS else if file pointer is null it will return
 *      ITS_ENULLPTR.
 ****************************************************************************/

int
INTELLINET_MTP3_Commit_CCITT(FILE* fp)
{
    int count = 0;
    TRACE_Data* td = MTP3_CCITT_TraceData;

    if (fp == NULL)
    {
        return ITS_ENULLPTR;
    }

    fprintf(fp,"\t\t\t\t<StackTrace>\n");

    for (count = 0; count < TRACE_DATA_NUM_LEVELS(td); count++)
    {
        fprintf(fp,"\t\t\t\t\t<%s output=\"%s\"/>\n",
                TRACE_DATA_LEVEL_MAP(td)[count]->level.levelName,
                (TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[0]->trace.isEnabled)?
                TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[0]->trace.name : "");
        fprintf(fp,"\t\t\t\t\t<%s output=\"%s\"/>\n",
                TRACE_DATA_LEVEL_MAP(td)[count]->level.levelName,
                (TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[1]->trace.isEnabled)?
                TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[1]->trace.name : "");
    }

    fprintf(fp,"\t\t\t\t</StackTrace>\n");
    fprintf(fp,"\t\t\t\t<Timers\n");

    for (count = 0; count < (int)CCITT_MTP3_Timers.numTimers; count++)
    {
        fprintf(fp,"\t\t\t\t\t%s = \"%d\"\n",MTP3_CCITT_Timers[count],
                                             CCITT_MTP3_Timers.timers[count]);
    }

    fprintf(fp,"\t\t\t\t/>\n");
    fprintf(fp,"\t\t\t\t<BehaviorControl\n");
    fprintf(fp,"\t\t\t\t\tstpFunction = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors,
                                   MTP3_B_stpFunction) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\tfullRestartNeeded = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors,
                                   MTP3_B_fullRestartNeeded) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\tspRestarting = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors,
                                   MTP3_B_spRestarting) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\tsendingStatus = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors,
                                   MTP3_B_sendingStatus) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t/>\n");

    return ITS_SUCCESS;
}

