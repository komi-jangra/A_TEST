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
 *  ID: $Id: ttc-mgmt.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $
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
 * LOG: Revision 8.1  2005/03/23 09:41:22  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/02/18 11:26:51  dsatish
 * LOG: Added Initial version file for TTC
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.7  2005/01/31 11:51:02  snagesh
 * LOG: MTP3 OSS APIs added
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.6  2005/01/11 13:06:39  craghavendra
 * LOG: Syslog Enhancements.
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.5  2005/01/07 12:14:01  mmanikandan
 * LOG: Compiler limit in windows for braces.
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.4  2005/01/04 16:05:02  snagesh
 * LOG: Commented get_pegids MMLs
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.3  2005/01/04 13:43:56  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.2  2004/12/31 07:51:38  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.5.2.7.2.3.4.1  2004/12/17 03:57:44  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.5.2.7.2.3  2004/10/06 13:24:58  mmanikandan
 * LOG: Compiler limit in windows for braces.
 * LOG:
 * LOG: Revision 7.5.2.7.2.2  2004/08/25 10:41:19  kannanp
 * LOG: Get Global pegs T25 to T34 are removed .
 * LOG:
 * LOG: Revision 7.5.2.7.2.1  2004/08/10 12:14:46  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.5.2.7  2003/12/08 11:25:26  kannanp
 * LOG: Fix bugs 596,598 wrong display of Timers,Add MMLs for clearing peg counts.
 * LOG:
 * LOG: Revision 7.5.2.6  2003/11/28 07:50:11  kannanp
 * LOG: Peg Fix patch from Current.
 * LOG:
 * LOG: Revision 7.5.2.5  2003/11/13 12:11:00  kannanp
 * LOG: MTP3 MML API.
 * LOG:
 * LOG: Revision 7.5.2.4  2003/03/26 06:32:09  randresol
 * LOG: Change Debug Console commands naming convention
 * LOG:
 * LOG: Revision 7.5.2.3  2003/03/17 11:48:41  akumar
 * LOG: Added ITU MML in PR_6.3 Branch
 * LOG:
 * LOG: Revision 7.5.2.2  2003/02/18 02:11:52  randresol
 * LOG: Enhance mtp3Shutdown command
 * LOG:
 * LOG: Revision 7.5.2.1  2003/02/14 07:29:22  randresol
 * LOG: Enhancement for Pegs and Alarms
 * LOG:
 * LOG: Revision 7.5  2003/02/13 10:35:23  ttipatre
 * LOG: New Interface for Pegs.
 * LOG:
 * LOG: Revision 7.4  2002/12/24 07:46:10  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.3  2002/11/09 21:48:32  randresol
 * LOG: Add ROUTE Reader/Writer Lock for MTP3 Optimization
 * LOG:
 * LOG: Revision 7.2  2002/09/26 23:00:10  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.5  2002/07/15 14:44:08  ngoel
 * LOG: move TCAP Console function to itu-tcap
 * LOG:
 * LOG: Revision 6.4  2002/07/08 00:02:22  ngoel
 * LOG: move sccp console function to itu-sccp.c
 * LOG:
 * LOG: Revision 6.3  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.2  2002/05/15 15:06:48  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.8  2002/01/31 22:56:17  mmiers
 * LOG: Correct dispatch entity
 * LOG:
 * LOG: Revision 5.7  2002/01/29 19:56:26  mmiers
 * LOG: warning removal
 * LOG:
 * LOG: Revision 5.6  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.5  2001/12/11 23:49:52  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.4  2001/12/06 22:39:05  mmiers
 * LOG: First cut of ITU MTP3.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.2  2001/10/22 21:18:21  rsonak
 * LOG: Get cvs logs in the file
 * LOG:
 ****************************************************************************/

#include <string.h>
#include <stdlib.h>

#undef CCITT
#undef ANSI
#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <its.h>
#include <engine.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_assertion.h>
#include <its_route_rwlock.h>

#include <dbc_serv.h>

#ident "$Id: ttc-mgmt.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

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

void DumpGlobalPegId(DBC_Server *dbc);
void DumpLinkPegId(DBC_Server *dbc);

void static NodeShutDown();

static int DumpGlobalPegs(DBC_Server *dbc);
static int DumpLinkPegs(DBC_Server *dbc);

static int DumpRemotePointCodeData(ITS_POINTER data, void *in, void *out) ;
static int DumpLocalPointCodeData(ITS_POINTER data, void *in, void *out) ;

static int GetRemotePointCodeData(ITS_POINTER data, void *in, void *out);
static int GetLocalPointCodeData(ITS_POINTER data, void *in, void *out);



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
ITSSS7DLLAPI int
MGMT_Main_CCITT(MTP3_SubSystems src, MGMT_Triggers trigger,
                ITS_OCTET *sif, ITS_USHORT len,
                ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    int ret;

    MTP3_TRACE_ENTRY_CCITT(MTP3_MGMT, src, trigger, sif, len,
                          linkSet, linkCode);

    switch (trigger)
    {
    case MGMT_TRIGGER_NO_ROUTING_DATA:       /* from HMRT */
        break;

    case MGMT_TRIGGER_LINK_TEST_PASSED:      /* from SLTC */
        MTP3_DEBUG(("SLT passed for %d:%d\n", linkSet, linkCode));
        break;

    case MGMT_TRIGGER_LINK_TEST_FAILED:      /* from SLTC */
        MTP3_DEBUG(("SLT failed for %d:%d\n", linkSet, linkCode));
        break;

    case MGMT_TRIGGER_LINK_ACTIVATION_FAIL:  /* from LSAC */
    case MGMT_TRIGGER_INHIBIT_REQ_TIMEOUT:   /* from TLAC */
    case MGMT_TRIGGER_UNINHIBIT_REQ_TIMEOUT: /* from TLAC */    
    case MGMT_TRIGGER_INHIBIT_DENIED:        /* from TLAC */
    case MGMT_TRIGGER_LINK_INHIBITED:        /* from TLAC */
    case MGMT_TRIGGER_LINK_REMOTE_UNINHIBIT: /* from TLAC */
    case MGMT_TRIGGER_UNINHIBIT_IMPOSSIBLE:  /* from TLAC */
    case MGMT_TRIGGER_MSG_FOR_INVALID_DEST:          /* from HMRT */
        break;

    case MGMT_TRIGGER_RESTART:               /* from USER */
        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        ret = TPRC_Main_CCITT(MTP3_USER,
                              STM_TRIGGER_RESTART_INDIC,
                              NULL, 0,
                              ITS_SS7_DEFAULT_LINK_SET,
                              ITS_SS7_DEFAULT_LINK_CODE);

        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));

        ROUTE_UnlockWrite(routeRWLock);
 
        return (ret);

    case MGMT_TRIGGER_INHIBIT_LINK:
        if (src != MTP3_STM_TLAC) /* to avoid getting into the recursive loop */
        {
            if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS) 
            {
                return (ITS_EBADMUTEX);
            }

            ret = TLAC_Main_CCITT(MTP3_MGMT,
                                  STM_TRIGGER_INHIBIT_LINK,
                                  NULL, 0,
                                  linkSet,
                                  linkCode);          

            LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
            ROUTE_UnlockWrite(routeRWLock);

            return (ret);
        }
        break;

    case MGMT_TRIGGER_UNINHIBIT_LINK:
        if (src != MTP3_STM_TLAC) /* to avoid getting into the recursive loop */
        {
            if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
            {
                return (ITS_EBADMUTEX);
            }

            ret = TLAC_Main_CCITT(MTP3_MGMT,
                                  STM_TRIGGER_UNINHIBIT_LINK,
                                  NULL, 0,
                                  linkSet,
                                  linkCode);

            LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
            ROUTE_UnlockWrite(routeRWLock);

            return (ret);
        }
        break;

    case MGMT_TRIGGER_DEACTIVATE_LINK_SET:
        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS) 
        {
            return (ITS_EBADMUTEX);
        }

        ret = LLSC_Main_CCITT(MTP3_MGMT,
                              SLM_TRIGGER_DEACTIVATE_LINK_SET,
                              NULL, 0,
                              linkSet,
                              linkCode);

        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
        ROUTE_UnlockWrite(routeRWLock);
        
        return (ret);

    case MGMT_TRIGGER_DEACTIVATE_LINK:
        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        ret = LSAC_Main_CCITT(MTP3_MGMT,
                              SLM_TRIGGER_DEACTIVATE_LINK,
                              NULL, 0,
                              linkSet,
                              linkCode);
        
        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
        ROUTE_UnlockWrite(routeRWLock);
        
        return (ret);

    case MGMT_TRIGGER_ACTIVATE_LINK:
        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        ret = LSAC_Main_CCITT(MTP3_MGMT,
                              SLM_TRIGGER_ACTIVATE_LINK,
                              NULL, 0,
                              linkSet,
                              linkCode);
        
        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
        ROUTE_UnlockWrite(routeRWLock);
        
        return (ret);

    case MGMT_TRIGGER_ACTIVATE_LINK_SET:
        if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        ret = LLSC_Main_CCITT(MTP3_MGMT,
                              SLM_TRIGGER_ACTIVATE_LINK_SET,
                              NULL, 0,
                              linkSet,
                              linkCode);

        LINKSET_CommitLinkSet(LINKSET_FindLinkSet(linkSet));
        ROUTE_UnlockWrite(routeRWLock);
        
        return (ret);

    default:
        MTP3_DEBUG(("Unknown mgmt trigger\n"));
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
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_DEBUG,
                                      2))
               {
                    strcat(buf, " syslog");
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
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ABORT,
                                      2))
               {
                    strcat(buf, " syslog");
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
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_WARNING,
                                      2))
               {
                    strcat(buf, " syslog");
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
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_ERROR,
                                      2))
               {
                    strcat(buf, " syslog");
               }
           }
           else
           {
               strcpy(buf, "        Error     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(MTP3_CCITT_TraceData,
                                    MTP3_TRACE_EVENT))
           {
               strcpy(buf, "        Event     = ");
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(MTP3_CCITT_TraceData,
                                      MTP3_TRACE_EVENT,
                                      2))
               {
                    strcat(buf, " syslog");
               } 
           }
           else
           {
               strcpy(buf, "        Event     = null");
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
           strcpy(buf, "        Event     = null\n");
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
        else if (strstr(traceType, "EVENT") || strstr(traceType, "event"))
        {
            strcpy(cfg.traceType, MTP3_EVENT_STRING);
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
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, MTP3_SYSLOG_STRING);
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
                           linkCode, linkSet);
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
                           linkCode, linkSet);
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
    else if (DBC_Cmd(dbc, "mi_get_gen_peg", "Get MTP3 General Pegs", 
             "<Peg Id>", ""))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT value;
        ITS_INT pgNum;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
             sprintf(buf,  "\n**** Invalid Command Arguments *******\n"
                           "Usage: mi_get_gen_peg [<Peg Id> or <All/all>]\n"); 
             DBC_AppendText(dbc, buf);
             return;
        }

        if((strncmp(pgName, "All", 3) == 0)||
           (strncmp(pgName, "all", 3) == 0)||
           (atoi(pgName) == ALL_MTP3_PEGS))
        {
            DumpGlobalPegs(dbc);
            return;
        }
         
        pgNum = atoi(pgName); 
         
        if (pgNum >= PEG_MTP3_NUM_PEGS_CCITT)
        {
            sprintf(buf, "\n   **** Invalid Peg Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Getting the Peg for %s Now\n", mtp3GPegStr[pgNum]);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(CCITT_MTP3_Pegs, pgNum);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_get_link_peg", "Get Link Level Pegs", 
             "<linkset> <linkcode> <Peg Id>", ""))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT value;
        ITS_INT pgNum;

        ret = sscanf(cmdLine, "%s %d %d %s", buf, &linkSet, &linkCode, pgName);
        if (ret != 4)
        {
            sprintf(buf,  "\n**** Invalid Command Arguments *******\n"
                          "Usage: mi_get_link_peg <linkset> <linkcode> [<Peg Id> or<All/all>]\n");
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

        if((strncmp(pgName, "All", 3) == 0) ||
           (strncmp(pgName, "all", 3) == 0)||
           (atoi(pgName) == ALL_MTP3_PEGS))
        {
           DumpLinkPegs(dbc);
           return;
        }

        pgNum = atoi(pgName);

        if (pgNum >= PEG_MTP3_NUM_LINK_PEGS)
        {
            sprintf(buf, "\n   **** Invalid Peg Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Getting the Peg for %s Now\n",mtp3LPegStr[pgNum]);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(&ln->MTP3_LINK_PEGS,pgNum);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }

#if 0
    else if (DBC_Cmd(dbc, "mi_get_gen_pegid", "Show all general peg IDs", "", ""))
    {
        DumpGlobalPegId(dbc);
    }
    else if (DBC_Cmd(dbc, "mi_get_link_pegid", "Show all link level peg IDs", "", ""))
    {
        DumpLinkPegId(dbc);
    }
#endif

    else if (DBC_Cmd(dbc, "mi_clr_gen_peg", "MTP3 Reset a particular gen Peg",
                          "[<Pegid> (or) <All/all>]",""))
    {
        char pegType[ITS_PATH_MAX];
        ITS_INT pgNum; 
        ret = sscanf(cmdLine, "%s %s", buf, pegType);

        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: mi_clr_gen_peg [<Pegid> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if((strncmp(pegType, "All", 3) == 0) ||
           (strncmp(pegType, "all", 3) == 0)||
           (atoi(pegType) == ALL_MTP3_PEGS))

        {
            for (i = 0; i < PEG_MTP3_NUM_PEGS_CCITT; i++)
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

        pgNum = atoi(pegType);        

        if (pgNum > PEG_MTP3_NUM_PEGS_CCITT - 1)
        {
             sprintf(buf, "\n** MTP3 general peg %d does not exist **\n",
                                                       pgNum);
             DBC_AppendText(dbc, buf);
             return;
        }

        PEG_ClearPeg(CCITT_MTP3_Pegs, pgNum);

        sprintf(buf, "\n** Cleared MTP3 general peg id %d **\n", pgNum);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_clr_link_peg", "MTP3 Clear particular Link Peg",
                          "<linkset> <linkcode> [<Pegid> (or) <All/all>]",""))
    {
        char pegType[ITS_PATH_MAX];
        ITS_INT pgNum;
        ret = sscanf(cmdLine, "%s %d %d %s", buf, &linkSet, &linkCode,pegType);
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
            "Usage: mi_clr_link_peg <linkset> <linkcode> [<Pegid> (or) <All/all>]\n");
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

        if((strncmp(pegType, "All", 3) == 0) ||
           (strncmp(pegType, "all", 3) == 0) || 
           (atoi(pegType) == ALL_MTP3_PEGS))   
        {
            for (i = 0; i < PEG_MTP3_NUM_LINK_PEGS; i++)
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

        pgNum = atoi(pegType);

        if (pgNum >= PEG_MTP3_NUM_LINK_PEGS)
        {
            sprintf(buf, "\n** MTP3 Link peg %d does not exist **\n", atoi(pegType));
            DBC_AppendText(dbc, buf);
            return;
        }

         PEG_ClearPeg(&ln->MTP3_LINK_PEGS, pgNum);

         sprintf(buf, "\n** Cleared peg id %d for linkset %d linkcode %d **\n", pgNum, linkSet, linkCode); 
                                                
         DBC_AppendText(dbc, buf);
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
    else if (DBC_Cmd(dbc, "mi_set_rpc", "set a remote point code",
               "<rpc><ni><ls><f>", "<remote pc><ni><link set><family>"))
    {
        char direction[20];
        char family[10];
        char buf[ITS_PATH_MAX];
        ITS_UINT rpc ;
        ITS_UINT lpc ;
        ITS_UINT ni;
        ITS_UINT linkSet ;
        ITS_UINT linkCode ;
        ITS_UINT ret;

        SS7_LinkSetPtr ls;
        SS7_LinkPtr    lp;
        SS7_LinkSet    set;
        ROUTE_MatchInfo rinfo;

        memset(&rinfo, 0, sizeof(rinfo));

        memset(&set, 0, sizeof(SS7_LinkSet));
        set.isUp = ITS_FALSE;

        /* addRoute direction paremeters */
        ret = sscanf(cmdLine, "%s   %d    %d    %d       %s",
                               buf, &rpc, &ni, &linkSet, family);
       if (ret != 5)
       {
           sprintf(buf,"*** Error: Invalid parameters, try help mi_set_rpc \n");
           DBC_AppendText(dbc, buf);
           return;
       }
       /*** process family ***/

       if (strcmp(family, FAMILY_ANSI_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ANSI;
           set.family = FAMILY_ANSI ;
       }
       else if (strcmp(family, FAMILY_CCITT_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ITU;
           set.family = FAMILY_ITU ;
       }
       else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_CHINA;
       }
       else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_JAPAN;
       }
       else
       {
           sprintf(buf, "Error invalid family...\n");
           DBC_AppendText(dbc, buf);
           return;
       }
       ls = LINKSET_FindLinkSet(linkSet);
       if (ls != NULL)
       {
          /* LinkSet exist ,So check for linkcode configuration */

           for (linkCode = 0 ; linkCode < MAX_LINKS ; linkCode++)
           {
               lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);

               if (lp != NULL)
               {
                   /* link exist for this linkset ,So proceed */
                   /* sprintf(buf, "ls:%d lc:%d exist\n",linkSet, linkCode);
                      DBC_AppendText(dbc, buf);
                   */
                   break ;
               }
           }
           if ( linkCode == MAX_LINKS )
           {
               sprintf( buf,  "links not configured for this linkset : %d",
                               linkSet);
               DBC_AppendText(dbc, buf);

               return ;
           }
       }
       else
       {
            sprintf( buf,  "LinkSet %d not configured ", linkSet);
            DBC_AppendText(dbc, buf);
            return ;
       }
       /** Process Direction **/

       strcpy(direction,ROUTE_TYPE_REMOTE_STRING) ;

       rinfo.basic.type = REMOTE_ROUTE;

       sprintf(buf, "*********** Adding Remote pointcode %d*************\n",rpc
)
;
       DBC_AppendText(dbc, buf);
       /*** process route style ****/

       rinfo.basic.style = ROUTE_DPC_NI;
       rinfo.basic.dpc = rpc;
       rinfo.basic.criteria.sio = ni ;

       rinfo.linkSet = (ITS_OCTET) linkSet;
       rinfo.linkCode = 0;
       rinfo.priority = 0;
       rinfo.sls  = 0;
       rinfo.rkey = 0;
       rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

       if ( (ret = ROUTE_AddRouteContextInfo(&rinfo)) != ITS_SUCCESS)
       {
           sprintf(buf, "Error %d: Route cannot be added\n", ret);
           DBC_AppendText(dbc,buf);
           return;
       }
    }
    else if (DBC_Cmd(dbc, "mi_rem_rpc","Remove a remote point code",
         "<rpc><ni><LinkSet><family>", "<remote pc><ni><linkset><family>"))
    {
        char direction[20];
        char family[10];
        ITS_UINT rpc ;
        ITS_UINT lpc ;
        ITS_UINT ni,famly ;
        ITS_UINT linkSet;
        char* strDumpEntries = NULL;

        ROUTE_MatchInfo rinfo;
        SS7_Destination *rc;
        SS7_LinkSetPtr ls;

        ret = sscanf(cmdLine, "%s %d %d %d %s", buf, &rpc, &ni, &linkSet,family
);
        if (ret != 5)
        {
           sprintf(buf, "*** Error: Invalid parameters, try help mi_rem_rpc \n"
);
           DBC_AppendText(dbc, buf);
           return;
        }

        rinfo.basic.type = REMOTE_ROUTE;

       if (strcmp(family, FAMILY_ANSI_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ANSI;
           famly = FAMILY_ANSI ;
       }
       else if (strcmp(family, FAMILY_CCITT_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ITU;
           famly = FAMILY_ITU ;
       }
       else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_CHINA;
           famly = FAMILY_CHINA ;
       }
       else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_JAPAN;
           famly = FAMILY_JAPAN ;
       }
       else
       {
           sprintf(buf, "Error invalid family...\n");
           DBC_AppendText(dbc, buf);
           return;
       }

       ls = LINKSET_FindLinkSet(linkSet);
       if (ls == NULL)
       {
           sprintf(buf, "Invalid Linkset\n");
           DBC_AppendText(dbc, buf);
           return;
       }
       if ((rc = ROUTE_FindDestination(rpc, ni, famly)) == NULL)
       {
          sprintf(buf,"%s","Error : Cannot delete - RPC Not Found\n");
          DBC_AppendText(dbc, buf);
          return ;
       }

       rinfo.basic.style = ROUTE_DPC_NI;
       rinfo.basic.dpc = rpc;
       rinfo.basic.criteria.sio = (ITS_OCTET)ni & ROUTE_NI_MASK;

       rinfo.linkSet = (ITS_OCTET) linkSet;
       rinfo.linkCode = 0;
       rinfo.priority = 0;
       rinfo.sls  = 0;
       rinfo.rkey = 0;
       rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
       if (ROUTE_DeleteRouteContextInfo(&rinfo) != ITS_SUCCESS)
       {
           sprintf(buf, "Error %d: Route cannot be deleted\n", ret);
           DBC_AppendText(dbc, buf);
           return;
       }
       sprintf(buf, "*********** Deleting Remote pointcode %d**********\n",rpc)
;
       DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_get_all_rpc", "get all remote PC", "<>", "<>"))
    {
        char *dump = NULL;
        char** pStrDumpa;
        char* strDumpEntries = NULL;

        strDumpEntries = (char *)calloc(PRINT_DATA_MAX_SIZE, sizeof(char));

        DSM_TableIterate(DSM_RoutingFtGroupId,
                           DSM_TABLE_DESTINATIONS,
                           &strDumpEntries,
                           NULL,
                           DumpRemotePointCodeData);

        if (strDumpEntries)
        {
            DBC_AppendText(dbc, strDumpEntries);
            free(dump);
        }
    }
    else if (DBC_Cmd(dbc, "mi_get_all_lpc", "get all local PC", "<>", "<>"))
    {
        char *dump = NULL;
        char** pStrDumpa;
        char* strDumpEntries = NULL;

        strDumpEntries = (char *)calloc(PRINT_DATA_MAX_SIZE, sizeof(char));

        DSM_TableIterate(DSM_RoutingFtGroupId,
                           DSM_TABLE_DESTINATIONS,
                           &strDumpEntries,
                           NULL,
                           DumpLocalPointCodeData);

        if (strDumpEntries)
        {
            DBC_AppendText(dbc, strDumpEntries);
            free(dump);
        }
    }
}



#if 0
void
MTP3_Console_CCITT(DBC_Server *dbc, const char *cmdLine)
{    
    char buf[ITS_PATH_MAX];
    int linkSet = 0, linkCode = 0, ret = 0;
    ITS_UINT pg,value;
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln; 
    ITS_UINT i;

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "mi_il", "Inhibit Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*********** Going to inhibit link 1 now *************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_INHIBIT_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        sprintf(buf, "*********** Returned from the MGMT Inhibit *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_ul", "Uninhibit Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*********** Going to uninhibit link 1 now *************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_UNINHIBIT_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        sprintf(buf, "*********** Returned from the MGMT UnInhibit *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_dls", "Deactivate Link Set", "<ls>", "<link set>"))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            return;
        }

        if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkSet)) == NULL)
        {
            sprintf(buf, "\n***Linkset %d not configured***\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*********** Deactivating link set ************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_DEACTIVATE_LINK_SET,
                        NULL, 0,
                        (ITS_OCTET)linkSet, ITS_SS7_DEFAULT_LINK_CODE);

        sprintf(buf, "*********** Link set deactivated *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_als", "Activate Link Set", "<ls>", "<link set>"))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            return;
        }

        if ((ls = LINKSET_FindLinkSet((ITS_OCTET)linkSet)) == NULL)
        {
            sprintf(buf, "\n***Linkset %d not configured***\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*********** Activate Link Set ************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_ACTIVATE_LINK_SET,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        sprintf(buf, "*********** Link Set Activated *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_dln", "Deactivate Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "****** Going to Deactivate link now ******\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_DEACTIVATE_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        sprintf(buf, "****** Returned from the MGMT Deactivate Link ******\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_aln", "Activate Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        if ((ln = LINK_FindLink((ITS_OCTET)linkSet, (ITS_OCTET)linkCode)) == NULL)
        {
            sprintf(buf, "\n***Link %d on link set %d is not configured***\n",
                           linkCode, linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "****** Going to Activate link now ******\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_ACTIVATE_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        sprintf(buf, "****** Returned from the MGMT Activate Link ******\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_start", "Start MTP3", "<>", "<>"))
    {
        sprintf(buf, "*********** Starting MTP3 **************\n");
        DBC_AppendText(dbc, buf);

        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_RESTART,
                        NULL, 0,
                        ITS_SS7_DEFAULT_LINK_SET,
                        ITS_SS7_DEFAULT_LINK_CODE);

        sprintf(buf, "*********** Returned from the MGMT Restart *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_dumpls", "Dump Link Sets", "<>", "<>"))
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
    else if (DBC_Cmd(dbc, "mi_dumprt", "Dump Routes Info", "<>", "<>"))
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
    else if (DBC_Cmd(dbc, "mi_link_status", "get Link Status", "<ls>", "<lc>"))
    {
        char *dump = NULL;

        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);

        ROUTE_LockForWrite(routeRWLock);

        LINK_DumpLinkInfo(&dump, (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        }

    }
    else if (DBC_Cmd(dbc, "mi_get_peg", "Get Pegs", "<pg> ", "<Peg#> <>"))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &pg);
        if (ret != 2)
        {
             return;
        }

        if (pg >= PEG_MTP3_NUM_PEGS_CCITT || pg < 0)
        {
            sprintf(buf, "range for peg is %d - %d", 0,PEG_MTP3_NUM_PEGS_CCITT-1);
            DBC_AppendText(dbc, buf);
            return ;
        }

        sprintf(buf, "Getting the Peg for #%d Now\n", pg);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(CCITT_MTP3_Pegs, pg);

        sprintf(buf, "value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_get_link_peg", "Get Link Level Pegs", "<ls> <lc> <p g>", "<link set> <link code><Peg#>"))
    {
        ret = sscanf(cmdLine, "%s %d %d %d", buf, &linkSet, &linkCode, &pg);
        if (ret != 4)
        {
            sprintf(buf, "Please enter the proper format\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (pg >= PEG_MTP3_LINK_NUM_PEGS || pg < 4)
        {
            sprintf(buf, "range for Pegs is %d - %d\n", 4, (PEG_MTP3_LINK_NUM_PEGS - 1));
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "******Getting the Peg for link %d:%d, peg %d ******\n", linkSet, linkCode,pg);

        if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
        {
            MTP3_ERROR(("Link %d:%d not found\n", linkSet, linkCode));
            return;
        }

        value = PEG_GetPeg(&ln->MTP3_LINK_PEGS,pg);

        sprintf(buf, "value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "mi_show_peg_ids", "Dump Peg Ids", "<>", "<>"))
    {
        DumpGlobalPegId(dbc);
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
           for (i = 0; i < PEG_MTP3_NUM_PEGS_CCITT; i++)
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

        if ( atoi(pegType) > PEG_MTP3_NUM_PEGS_CCITT - 1)
        {
             sprintf(buf, "\n** MTP3 general peg %d does not exist **\n",
                                                       atoi(pegType));
             DBC_AppendText(dbc, buf);
             return;
         }
         for (i = 0; i < PEG_MTP3_NUM_PEGS_CCITT; i++)
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
                           linkCode, linkSet);
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
               sprintf(buf, "\n** Cleared peg id %d for linkset %d linkcode %d **\n",i,linkSet,linkCode);
               return;
            }
         }

        for (i = 0; i < PEG_MTP3_LINK_NUM_PEGS; i++)
        {
            if ((ITS_UINT)RESFILE_ParseNum(pegType) == i)
            {
               PEG_ClearPeg(&ln->MTP3_LINK_PEGS, i);
               sprintf(buf, "\n** Cleared peg id %d for linkset %d linkcode %d **\n",i, linkSet,linkCode);
               DBC_AppendText(dbc, buf);
               break;
            }
        }
    }
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
    else if (DBC_Cmd(dbc, "mi_shutdown", "shutdown mtp3", "<>", "<>"))
    {
        ShutDownNode(dbc);

        TIMERS_Sleep(5);

        ENGINE_Terminate();
    }

}
#endif

static int
DumpRemotePointCodeData(ITS_POINTER data, void *in, void *out)
{
    char** pStrDump = (char **)in;
    ITS_UINT i,j ;
    static ITS_UINT DuplicateEntry = 0 ;
    char printBuf[PRINT_BUF_MAX_SIZE];
    SS7_Destination* ss7Context = (SS7_Destination*)data;

    if (*pStrDump == NULL)
    {
        return ITS_ENOMEM;
    }

    for (i = 0; i < ss7Context->numEntries; i++)
    {
       if ( ss7Context->entries[i]->basic.type == REMOTE_ROUTE )
       {
           for (j = 0 ; j < i ;j++)
           {
               if (ss7Context->entries[i]->basic.dpc ==
                                            ss7Context->entries[j]->basic.dpc )
               {
                   return ITS_SUCCESS ;
               }
           }


           strcat(*pStrDump, "------------------------------\n");

           /* Remote PointCode. */

           strcat(*pStrDump, "Remote PC:         <");
           sprintf(printBuf, "%u", ss7Context->entries[i]->basic.dpc);
           strcat(*pStrDump, printBuf);
           strcat(*pStrDump, ">\n");

           /* Family */

           strcat(*pStrDump, "Family:      <");
           strcat(*pStrDump,
                  FAMILY_TO_TEXT(ss7Context->entries[i]->basic.family));
           strcat(*pStrDump, ">\n");

           /* SIO */

           strcat(*pStrDump, "SIO:         <");
           sprintf(printBuf, "%u",
                   ss7Context->entries[i]->basic.criteria.sio);
           strcat(*pStrDump, printBuf);
           strcat(*pStrDump, ">\n");

           /* status . */

           strcat(*pStrDump, "status:      <");
           sprintf(printBuf, "%s", STATUS_STR(ss7Context->status));
           strcat(*pStrDump, printBuf);
           strcat(*pStrDump, ">\n");
           strcat(*pStrDump, "------------------------------\n");

        }
     }
     return ITS_SUCCESS;
}


static int
DumpLocalPointCodeData(ITS_POINTER data, void *in, void *out)
{
    char** pStrDump = (char **)in;
    ITS_UINT i,j;
    ITS_UINT DuplicateEntry = 0;
    char printBuf[PRINT_BUF_MAX_SIZE];
    SS7_Destination* ss7Context = (SS7_Destination*)data;

    if (*pStrDump == NULL)
    {
        return ITS_ENOMEM;
    }

    for (i = 0; i < ss7Context->numEntries; i++)
    {
        if ( ss7Context->entries[i]->basic.type == LOCAL_ROUTE )
        {
           for (j = 0 ; j < i ;j++)
           {
               if (ss7Context->entries[i]->basic.dpc ==
                                            ss7Context->entries[j]->basic.dpc )
               {
                   return ITS_SUCCESS ;
               }
           }
           strcat(*pStrDump, "------------------------------\n");

           /*Local PointCode. */
           strcat(*pStrDump, "Local PC:         <");
           sprintf(printBuf, "%u", ss7Context->entries[i]->basic.dpc);
           strcat(*pStrDump, printBuf);
           strcat(*pStrDump, ">\n");

           /* Family */
           strcat(*pStrDump, "Family:      <");
           strcat(*pStrDump,
                  FAMILY_TO_TEXT(ss7Context->entries[i]->basic.family));
           strcat(*pStrDump, ">\n");

           strcat(*pStrDump, "------------------------------\n");

        }
     }
     return ITS_SUCCESS;
}


static int
DumpGlobalPegs(DBC_Server *dbc)
{
     char buf[ITS_PATH_MAX];

     sprintf(buf, "\n*****Printing Global Pegs****************\n");
     DBC_AppendText(dbc, buf);

#ifndef WIN32

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

#if 0
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
#endif
#endif
     sprintf(buf, "\n*******************************************\n");
     DBC_AppendText(dbc, buf);
}


void
DumpGlobalPegId(DBC_Server *dbc)
{

     char buf[32000];
     char buf1[32000];

     memset(buf , 0, 32000);
     memset(buf1, 0, 32000);

     sprintf(buf, "\n*****Printing Global Pegs****************\n");
     strcat(buf1, buf);

#ifndef WIN32

     /* Print the pegs and their assciated Id's */
     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_PAUSE),
             PEG_MTP3_MSG_PAUSE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_PAUSE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_RESUME),
             PEG_MTP3_MSG_RESUME, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RESUME));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_STATUS),
             PEG_MTP3_MSG_STATUS, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_STATUS));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_INITIALIZE),
             PEG_MTP3_INITIALIZE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_INITIALIZE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TERMINATE),
             PEG_MTP3_TERMINATE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TERMINATE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_MSG_RECEIVED_INERROR),
             PEG_MTP3_MSG_RECEIVED_INERROR, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RECEIVED_INERROR));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CHANGEOVER),
             PEG_MTP3_CHANGEOVER, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CHANGEBACK),
             PEG_MTP3_CHANGEBACK, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_SL_UNAVAILABLE),
             PEG_MTP3_SL_UNAVAILABLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SL_UNAVAILABLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_INHIBIT),
             PEG_MTP3_LINK_INHIBIT, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_UNINHIBIT),
             PEG_MTP3_LINK_UNINHIBIT, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_LINK_FORCE_UNINHIBIT),
             PEG_MTP3_LINK_FORCE_UNINHIBIT, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_CONGESTION),
             PEG_MTP3_CONGESTION, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CONGESTION));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_SLS_UNAVAILABLE),
             PEG_MTP3_SLS_UNAVAILABLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLS_UNAVAILABLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TFC_RECEIVED),
             PEG_MTP3_TFC_RECEIVED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFC_RECEIVED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_TFA_RECEIVED),
             PEG_MTP3_TFA_RECEIVED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_RECEIVED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_ROUTESET_UNAVAILABLE),
             PEG_MTP3_ROUTESET_UNAVAILABLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ROUTESET_UNAVAILABLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_ADJECENT_SP_UNACCESIBLE),
             PEG_MTP3_ADJECENT_SP_UNACCESIBLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_USERPART_ENABLE),
             PEG_MTP3_USERPART_ENABLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_ENABLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_USERPART_DISABLE),
             PEG_MTP3_USERPART_DISABLE, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_DISABLE));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T1_EXPIRED),
             PEG_MTP3_T1_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T1_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T2_EXPIRED),
             PEG_MTP3_T2_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T2_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T3_EXPIRED),
             PEG_MTP3_T3_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T3_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T4_EXPIRED),
             PEG_MTP3_T4_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T4_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T5_EXPIRED),
             PEG_MTP3_T5_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T5_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T6_EXPIRED),
             PEG_MTP3_T6_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T6_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T7_EXPIRED),
             PEG_MTP3_T7_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T7_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T8_EXPIRED),
             PEG_MTP3_T8_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T8_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T9_EXPIRED),
             PEG_MTP3_T9_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T9_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T10_EXPIRED),
             PEG_MTP3_T10_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T10_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T11_EXPIRED),
             PEG_MTP3_T11_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T11_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T12_EXPIRED),
             PEG_MTP3_T12_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T12_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T13_EXPIRED),
             PEG_MTP3_T13_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T13_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T14_EXPIRED),
             PEG_MTP3_T14_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T14_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T15_EXPIRED),
             PEG_MTP3_T15_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T15_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T16_EXPIRED),
             PEG_MTP3_T16_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T16_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T17_EXPIRED),
             PEG_MTP3_T17_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T17_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T18_EXPIRED),
             PEG_MTP3_T18_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T18_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T19_EXPIRED),
             PEG_MTP3_T19_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T19_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T20_EXPIRED),
             PEG_MTP3_T20_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T20_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T21_EXPIRED),
             PEG_MTP3_T21_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T21_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T22_EXPIRED),
             PEG_MTP3_T22_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T22_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T23_EXPIRED),
             PEG_MTP3_T23_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T23_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T24_EXPIRED),
             PEG_MTP3_T24_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T24_EXPIRED));
     strcat(buf1, buf);

#if 0
     /* Commented as per spec */
     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T25_EXPIRED),
             PEG_MTP3_T25_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T25_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T26_EXPIRED),
             PEG_MTP3_T26_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T26_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T27_EXPIRED),
             PEG_MTP3_T27_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T27_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T28_EXPIRED),
             PEG_MTP3_T28_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T28_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T29_EXPIRED),
             PEG_MTP3_T29_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T29_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T30_EXPIRED),
             PEG_MTP3_T30_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T30_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T31_EXPIRED),
             PEG_MTP3_T31_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T31_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T32_EXPIRED),
             PEG_MTP3_T32_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T32_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T33_EXPIRED),
             PEG_MTP3_T33_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T33_EXPIRED));
     strcat(buf1, buf);

     sprintf(buf, "%12s %5d: value %d\n", GLOBAL_PEGID_TO_TEXT(PEG_MTP3_T34_EXPIRED),
             PEG_MTP3_T34_EXPIRED, PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_T34_EXPIRED));
     strcat(buf1, buf);
#endif
#endif

     sprintf(buf, "\n*******************************************\n");
     strcat(buf1, buf);

     DBC_AppendText(dbc, buf1);
}

static int
DumpLinkPegs(DBC_Server *dbc)
{
     char buf[ITS_PATH_MAX];

     sprintf(buf, "\n*****Printing Link Pegs****************\n");
     DBC_AppendText(dbc, buf);

#ifndef WIN32

 /* Print the pegs and their assciated Id's */
     sprintf(buf, "\n%12s:              value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_MSU_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_MSU_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT( PEG_MTP3_LINK_MSU_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs,  PEG_MTP3_LINK_MSU_RX ));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_OCTETS_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_OCTETS_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_OCTETS_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_OCTETS_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:              value %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_COO_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_COO_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:   value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_COO_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_COO_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_COA_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_COA_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_COA_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_COA_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:         value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_ECO_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_ECO_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:           value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_ECO_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_ECO_RX));
     DBC_AppendText(dbc, buf);
     sprintf(buf, "\n%12s:         value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_ECA_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_ECA_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:   value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_ECA_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_ECA_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n",     LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CBD_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_CBD_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:        value %d\n", LINK_PEGID_TO_TEXT (PEG_MTP3_LINK_CBD_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_CBD_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:           value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CBA_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_CBA_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:           value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CBA_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_CBA_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:   value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LIN_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LIN_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LIN_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LIN_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:         value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LIA_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LIA_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:        value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LIA_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LIA_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LUN_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LUN_TX));
     DBC_AppendText(dbc, buf);
      sprintf(buf, "%12s:              value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LUN_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LUN_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LUA_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LUA_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LUA_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LUA_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LID_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LID_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LID_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LID_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LFU_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LFU_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LFU_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LFU_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:              value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LLI_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LLI_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LLI_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LLI_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LRI_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LRI_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_LRI_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_LRI_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_DLC_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_DLC_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_DLC_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs,PEG_MTP3_LINK_DLC_RX ));

     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CSS_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_CSS_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CSS_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_CSS_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n",LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CNS_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_CNS_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CNS_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_CNS_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CNP_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_CNP_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_CNP_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_CNP_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_UPU_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UPU_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_UPU_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UPU_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_SLTM_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_SLTM_TX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_SLTM_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_SLTM_RX));
     DBC_AppendText(dbc, buf);

     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_SLTA_TX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_SLTM_TX));
     DBC_AppendText(dbc, buf);
     sprintf(buf, "\n%12s:             value %d\n", LINK_PEGID_TO_TEXT(PEG_MTP3_LINK_SLTA_RX),
             PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_SLTM_RX));
     DBC_AppendText(dbc, buf);

#endif

      sprintf(buf, "\n*******************************************\n");
     DBC_AppendText(dbc, buf);
}

void
DumpLinkPegId(DBC_Server *dbc)
{
     char buf[32000];
     char buf1[32000];

     memset(buf , 0, 32000);
     memset(buf1, 0, 32000);

     sprintf(buf, "\n*****Printing Link Level Pegs************\n");
     strcat(buf1, buf);

     /* Print the pegs and their assciated Id's */
#if 0
     sprintf(buf, "PEG_MTP3_LINK_MSU_TX                    %3d\n",PEG_MTP3_LINK_MSU_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_MSU_RX                    %3d\n",PEG_MTP3_LINK_MSU_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_OCTETS_TX                 %3d\n",PEG_MTP3_LINK_OCTETS_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_OCTETS_RX                 %3d\n",PEG_MTP3_LINK_OCTETS_RX);
     strcat(buf1, buf);
#endif
     sprintf(buf, "PEG_MTP3_LINK_COO_TX                    %3d\n",PEG_MTP3_LINK_COO_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_COO_RX                    %3d\n",PEG_MTP3_LINK_COO_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_COA_TX                    %3d\n", PEG_MTP3_LINK_COA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_COA_RX                    %3d\n",PEG_MTP3_LINK_COA_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECO_TX                    %3d\n",PEG_MTP3_LINK_ECO_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECO_RX                    %3d\n",PEG_MTP3_LINK_ECO_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECA_TX                    %3d\n",PEG_MTP3_LINK_ECA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_ECA_RX                    %3d\n",PEG_MTP3_LINK_ECA_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBD_TX                    %3d\n",PEG_MTP3_LINK_CBD_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBD_RX                    %3d\n",PEG_MTP3_LINK_CBD_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBA_TX                    %3d\n",PEG_MTP3_LINK_CBA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CBA_RX                    %3d\n",PEG_MTP3_LINK_CBA_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIN_TX                    %3d\n",PEG_MTP3_LINK_LIN_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIN_RX                    %3d\n",PEG_MTP3_LINK_LIN_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIA_TX                    %3d\n",PEG_MTP3_LINK_LIA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LIA_RX                    %3d\n",PEG_MTP3_LINK_LIA_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUN_TX                    %3d\n",PEG_MTP3_LINK_LUN_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUN_RX                    %3d\n",PEG_MTP3_LINK_LUN_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUA_TX                    %3d\n",PEG_MTP3_LINK_LUA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LUA_RX                    %3d\n",PEG_MTP3_LINK_LUA_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LID_TX                    %3d\n",PEG_MTP3_LINK_LID_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LID_RX                    %3d\n",PEG_MTP3_LINK_LID_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LFU_TX                    %3d\n",PEG_MTP3_LINK_LFU_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LFU_RX                    %3d\n",PEG_MTP3_LINK_LFU_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LLI_TX                    %3d\n",PEG_MTP3_LINK_LLI_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LLI_RX                    %3d\n",PEG_MTP3_LINK_LLI_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LRI_TX                    %3d\n",PEG_MTP3_LINK_LRI_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_LRI_RX                    %3d\n",PEG_MTP3_LINK_LRI_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_DLC_TX                    %3d\n",PEG_MTP3_LINK_DLC_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_DLC_RX                    %3d\n",PEG_MTP3_LINK_DLC_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CSS_TX                    %3d\n",PEG_MTP3_LINK_CSS_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CSS_RX                    %3d\n",PEG_MTP3_LINK_CSS_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNS_TX                    %3d\n",PEG_MTP3_LINK_CNS_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNS_RX                    %3d\n",PEG_MTP3_LINK_CNS_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNP_TX                    %3d\n",PEG_MTP3_LINK_CNP_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_CNP_RX                    %3d\n",PEG_MTP3_LINK_CNP_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_UPU_TX                    %3d\n",PEG_MTP3_LINK_UPU_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_UPU_RX                    %3d\n",PEG_MTP3_LINK_UPU_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTM_TX                   %3d\n",PEG_MTP3_LINK_SLTM_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTM_RX                   %3d\n",PEG_MTP3_LINK_SLTM_RX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTA_TX                   %3d\n",PEG_MTP3_LINK_SLTA_TX);
     strcat(buf1, buf);

     sprintf(buf, "PEG_MTP3_LINK_SLTA_RX                   %3d\n",PEG_MTP3_LINK_SLTA_RX);
     strcat(buf1, buf);

     DBC_AppendText(dbc, buf1);
}


/****************************************************************************
 *  Purpose:
 *      To Start the MTP3 Node
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI void 
MTP3_OSS_Start_CCITT()
{
    ITS_INT ret = ITS_SUCCESS;
    
    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_RESTART,
                          NULL, 
                          0,
                          ITS_SS7_DEFAULT_LINK_SET,
                          ITS_SS7_DEFAULT_LINK_CODE);
}

/****************************************************************************
 *  Purpose:
 *      To Shutdown the MTP3 Node
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI void 
MTP3_OSS_Shutdown_CCITT()
{
    NodeShutDown();

    TIMERS_Sleep(5);

    ENGINE_Terminate();
}

/****************************************************************************
 *  Purpose:
 *      Gets the MTP3 General config
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetGeneralCfg_CCITT(MTP3_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    genCfg->alarmLevel = (MGMT_AlarmLevel)MTP3_AlarmLevel_CCITT;

    genCfg->debugTrace = TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG); 
    if (genCfg->debugTrace)
    {
        genCfg->debugTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG, 0))
        {
            genCfg->debugTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG, 1))
        {
            genCfg->debugTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_DEBUG, 2))
        {
            genCfg->debugTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->debugTraceOutput)
        {
            genCfg->debugTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->warningTrace = TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_WARNING); 
    if (genCfg->warningTrace)
    {
        genCfg->warningTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_WARNING, 0))
        {
            genCfg->warningTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_WARNING, 1))
        {
            genCfg->warningTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_WARNING, 2))
        {
            genCfg->warningTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->warningTraceOutput)
        {
            genCfg->warningTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->errorTrace = TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_ERROR); 
    if (genCfg->errorTrace)
    {
        genCfg->errorTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ERROR, 0))
        {
            genCfg->errorTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ERROR, 1))
        {
            genCfg->errorTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ERROR, 2))
        {
            genCfg->errorTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->errorTraceOutput)
        {
            genCfg->errorTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->criticalTrace = TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_ABORT); 
    if (genCfg->criticalTrace)
    {
        genCfg->criticalTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ABORT, 0))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ABORT, 1))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_ABORT, 2))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->criticalTraceOutput)
        {
            genCfg->criticalTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->eventTrace = TRACE_IsLevelOn(MTP3_CCITT_TraceData, MTP3_TRACE_EVENT); 
    if (genCfg->eventTrace)
    {
        genCfg->eventTraceOutput = 0;
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_EVENT, 0))
        {
            genCfg->eventTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_EVENT, 1))
        {
            genCfg->eventTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(MTP3_CCITT_TraceData, MTP3_TRACE_EVENT, 2))
        {
            genCfg->eventTraceOutput |= TRACE_TO_SYSLOG;
        }
        if (!genCfg->eventTraceOutput)
        {
            genCfg->eventTraceOutput |= TRACE_TO_NONE;
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Sets the MTP3 General config
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_SetGeneralCfg_CCITT(MTP3_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    MTP3_AlarmLevel_CCITT = genCfg->alarmLevel;

    if (genCfg->debugTrace)
    {
        TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_DEBUG_STRING,  ITS_TRUE); 

        if (genCfg->debugTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->debugTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->debugTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_DEBUG_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_DEBUG_STRING,  ITS_FALSE); 
        }
    }

    if (genCfg->warningTrace)
    {
        TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_WARNING_STRING,  ITS_TRUE); 

        if (genCfg->warningTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->warningTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->warningTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->warningTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_WARNING_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_WARNING_STRING,  ITS_FALSE); 
        }
    }

    if (genCfg->errorTrace)
    {
        TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_ERROR_STRING,  ITS_TRUE); 

        if (genCfg->errorTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->errorTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->errorTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->errorTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_ERROR_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_ERROR_STRING,  ITS_FALSE); 
        }
    }

    if (genCfg->criticalTrace)
    {
        TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_CRITICAL_STRING,  ITS_TRUE); 

        if (genCfg->criticalTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->criticalTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->criticalTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->criticalTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_CRITICAL_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_CRITICAL_STRING,  ITS_FALSE); 
        }
    }

    if (genCfg->eventTrace)
    {
        TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_EVENT_STRING,  ITS_TRUE); 

        if (genCfg->eventTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->eventTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->eventTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);
        }
        
        if (genCfg->eventTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData, 
                                       MTP3_EVENT_STRING, 
                                       MTP3_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData, MTP3_EVENT_STRING,  ITS_FALSE); 
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Sets the MTP3 Behavior
 *
 *  Input Parameters:
 *      ITS_BOOLEAN        isStp
 *      ITS_BOOLEAN        handleSpareNic
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI void
MTP3_OSS_SetBehavior_CCITT(ITS_BOOLEAN isStp, ITS_BOOLEAN handleSpareNic)
{
    BEHAVIORS_SetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_stpFunction, isStp);
    MTP3_CCITT_HandleSpareNIC = handleSpareNic;    
}

/****************************************************************************
 *  Purpose:
 *      Gets the MTP3 Behavior
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      ITS_BOOLEAN*    isStp
 *      ITS_BOOLEAN*    handleSpareNic
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetBehavior_CCITT(ITS_BOOLEAN* isStp, ITS_BOOLEAN* handleSpareNic)
{
    if (isStp == NULL || handleSpareNic == NULL)
        return ITS_ENOMEM;

    *isStp = BEHAVIORS_GetBehavior(&CCITT_MTP3_Behaviors, MTP3_B_stpFunction);
    *handleSpareNic = MTP3_CCITT_HandleSpareNIC; 

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Inhibits the link
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *      ITS_OCTET   linkCode
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_InhibitLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    ITS_INT     ret = ITS_SUCCESS; 

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_INHIBIT_LINK,
                          NULL, 
                          0,
                          linkSet, 
                          linkCode);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Inhibition error %d", linkCode, linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Link %d in linkset %d Inhibited\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Uninhibits the link
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *      ITS_OCTET   linkCode
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_UninhibitLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    ITS_INT     ret = ITS_SUCCESS; 

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_UNINHIBIT_LINK,
                          NULL, 
                          0,
                          linkSet, 
                          linkCode);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Uninhibition error %d", linkCode, linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Link %d in linkset %d Uninhibited\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Deactivates the link
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *      ITS_OCTET   linkCode
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_DeactivateLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    ITS_INT     ret = ITS_SUCCESS; 

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_DEACTIVATE_LINK,
                          NULL, 
                          0,
                          linkSet, 
                          linkCode);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Deactivation error %d", linkCode, linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Link %d in linkset %d Deactivated\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Activates the link
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *      ITS_OCTET   linkCode
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_ActivateLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkPtr ln;
    ITS_INT     ret = ITS_SUCCESS; 

    if ((ln = LINK_FindLink(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_ACTIVATE_LINK,
                          NULL, 
                          0,
                          linkSet, 
                          linkCode);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Activation error %d", linkCode, linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Link %d in linkset %d Activated\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Deactivates the linkset
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_DeactivateLinkset_CCITT (ITS_OCTET linkSet)
{
    SS7_LinkSetPtr  ls;
    ITS_INT         ret = ITS_SUCCESS; 

    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        return ITS_ELINKSETNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_DEACTIVATE_LINK_SET,
                          NULL, 
                          0,
                          linkSet, 
                          ITS_SS7_DEFAULT_LINK_CODE);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Linkset %d Deactivation error %d", linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Linkset %d Deactivated\n", linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Activates the linkset
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_ActivateLinkset_CCITT (ITS_OCTET linkSet)
{
    SS7_LinkSetPtr  ls;
    ITS_INT         ret = ITS_SUCCESS; 

    if ((ls = LINKSET_FindLinkSet(linkSet)) == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        return ITS_ELINKSETNOTFOUND;
    }

    ret = MGMT_Main_CCITT(MTP3_USER,
                          MGMT_TRIGGER_ACTIVATE_LINK_SET,
                          NULL, 
                          0,
                          linkSet, 
                          ITS_SS7_DEFAULT_LINK_CODE);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Linkset %d Activation error %d", linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Linkset %d Activated\n", linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets the configured linksets
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetLinkset_CCITT(ITS_OCTET linkSet, SS7_LinkSetInfo* linkSetInfoPtr, ITS_OCTET* numLinksets)
{
    SS7_LinkSetPtr  ls = NULL;
    ITS_OCTET       index;

    if (linkSetInfoPtr == NULL || numLinksets == NULL)
        return ITS_ENOMEM;

    if (linkSet == ITS_SS7_DEFAULT_LINK_SET)
    {
        if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("Couldn't acquire lock\n"));
            return ITS_EBADMUTEX;
        }

        (*numLinksets) = 0;
        for (index = 0; index < ITS_SS7_DEFAULT_LINK_SET; index++)
        {
            ls = LINKSET_FindLinkSet(index);
            if (ls)
            {
                linkSetInfoPtr->linkSet    = ls->linkSet;
                linkSetInfoPtr->lpc        = ls->lpc;
                linkSetInfoPtr->adjacent   = ls->adjacent;
                linkSetInfoPtr->ni         = ls->ni;
                linkSetInfoPtr->family     = ls->family;
                linkSetInfoPtr->numLinks   = ls->numLinks;
                linkSetInfoPtr->adjSTP     = ls->adjSTP;
                linkSetInfoPtr->isUp       = ls->isUp;

                linkSetInfoPtr++;
                (*numLinksets)++;
            }
        }

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);
    }
    else
    {
        ls = LINKSET_FindLinkSet(linkSet);
        if (ls == NULL)
        {
            MTP3_DEBUG(("Linkset %d not found", linkSet));
            return ITS_ELINKSETNOTFOUND;
        }

        (*numLinksets) = 1;
        linkSetInfoPtr->linkSet    = ls->linkSet;
        linkSetInfoPtr->lpc        = ls->lpc;
        linkSetInfoPtr->adjacent   = ls->adjacent;
        linkSetInfoPtr->ni         = ls->ni;
        linkSetInfoPtr->family     = ls->family;
        linkSetInfoPtr->numLinks   = ls->numLinks;
        linkSetInfoPtr->adjSTP     = ls->adjSTP;
        linkSetInfoPtr->isUp       = ls->isUp;
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets the link information
 *
 *  Input Parameters:
 *      ITS_OCTET   linkSet
 *      ITS_OCTET   linkCode
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode, SS7_LinkInfo* linkInfoPtr)
{
    SS7_LinkPtr  link = NULL ;

    if (linkInfoPtr == NULL)
        return ITS_ENOMEM;

    memset(linkInfoPtr, 0, sizeof(SS7_LinkInfo));

    link = LINK_FindLink(linkSet, linkCode);
    if (link == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    linkInfoPtr->linkSet    = link->linkSet->linkSet;
    linkInfoPtr->linkCode   = link->linkCode;
    linkInfoPtr->family     = link->family;
    linkInfoPtr->id         = link->id;
    linkInfoPtr->initActive = link->initActive;
    linkInfoPtr->localLink  = link->localLink;
    linkInfoPtr->priority   = link->priority ;
    linkInfoPtr->isUp       = link->isUp;
    linkInfoPtr->isAllowed  = link->isAllowed;
    linkInfoPtr->active     = link->active;
    linkInfoPtr->congLevel  = link->congLevel;
    linkInfoPtr->availableState = link->availableState;
    linkInfoPtr->testPassed = link->testPassed;

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets the MTP3 global pegs
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
MTP3_OSS_GetGeneralPegs_CCITT(MTP3_GenPegs* globalPegs)
{
    if (globalPegs == NULL)
        return ITS_ENOMEM;

    globalPegs->msgPause             = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_PAUSE);
    globalPegs->msgResume            = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RESUME);
    globalPegs->msgStatus            = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_STATUS);
    globalPegs->initialize           = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_INITIALIZE);
    globalPegs->terminate            = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TERMINATE);
    globalPegs->msgReceivedInError   = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RECEIVED_INERROR);
    globalPegs->changeover           = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER);
    globalPegs->changeback           = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK);
    globalPegs->slUnavailable        = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SL_UNAVAILABLE);
    globalPegs->linkInhibit          = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);
    globalPegs->linkUnInhibit        = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);
    globalPegs->linkforceUninhibit   = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);
    globalPegs->congestion           = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_CONGESTION);
    globalPegs->slsUnavailable       = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLS_UNAVAILABLE);
    globalPegs->tfcReceived          = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFC_RECEIVED);
    globalPegs->tfaReceived          = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_RECEIVED);
    globalPegs->routesetUnavailable  = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ROUTESET_UNAVAILABLE);
    globalPegs->adjacentSpUnaccesible= PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_ADJECENT_SP_UNACCESIBLE);
    globalPegs->userpartEnable       = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_ENABLE);
    globalPegs->userpartDisable      = PEG_GetPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_DISABLE);

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets the MTP3 link pegs for the specified link
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *
 *  Output Parameters:
 *      MTP3_LinkPegs*  linkPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetLinkPegs_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode, MTP3_LinkPegs* linkPegs)
{
    if (linkPegs == NULL)
        return ITS_ENOMEM;

    SS7_LinkPtr ln = NULL;

    ln = LINK_FindLinkNoLock(linkSet, linkCode);
    if (ln == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    linkPegs->cooTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_TX);
    linkPegs->cooRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_RX);
    linkPegs->coaTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);
    linkPegs->coaRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_RX);
    linkPegs->ecoTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_TX);
    linkPegs->ecoRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_RX);
    linkPegs->ecaTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);
    linkPegs->ecaRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_RX);
    linkPegs->cbdTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);
    linkPegs->cbdRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_RX);
    linkPegs->cbaTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_TX);
    linkPegs->cbaRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_RX);
    linkPegs->linTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_TX);
    linkPegs->linRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_RX);
    linkPegs->liaTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_TX);
    linkPegs->liaRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_RX);
    linkPegs->lunTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);
    linkPegs->lunRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_RX);
    linkPegs->luaTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_TX);
    linkPegs->luaRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_RX);
    linkPegs->lidTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_TX);
    linkPegs->lidRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_RX);
    linkPegs->lfuTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);
    linkPegs->lfuRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_RX);
    linkPegs->lliTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_TX);
    linkPegs->lliRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_RX);
    linkPegs->lriTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_TX);
    linkPegs->lriRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_RX);
    linkPegs->dlcTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);
    linkPegs->dlcRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_RX);
    linkPegs->cssTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_TX);
    linkPegs->cssRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_RX);
    linkPegs->cnsTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_TX);
    linkPegs->cnsRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_RX);
    linkPegs->cnpTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_TX);
    linkPegs->cnpRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_RX);
    linkPegs->upuTx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_TX);
    linkPegs->upuRx     = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_RX);
    linkPegs->sltmTx    = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_TX);
    linkPegs->sltmRx    = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_RX);
    linkPegs->sltaTx    = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_TX);
    linkPegs->sltaRx    = PEG_GetPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_RX);

    return ITS_SUCCESS; 
}

/****************************************************************************
 *  Purpose:
 *      Clears the MTP3 global pegs
 *
 *  Input Parameters:
 *      ITS_UINT    pegId
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_ClearGeneralPeg_CCITT(ITS_UINT pegId)
{
    if (pegId == MTP3_ALL_PEGS)
    {
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_INITIALIZE);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_TERMINATE);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_RESTART);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_PAUSE); 
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_RESUME);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSG_STATUS);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_OUT_OF_SERVICE);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_IN_SERVICE);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEOVER);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_EMER_CHANGEOVER);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_CHANGEBACK);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_INHIBIT_DNY);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNINHIBIT);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_FORCE_UNINHIBIT);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_BLOCK);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_UNBLOCK);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_ACTIVATION);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_LINK_DEACTIVATION);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_CONGESTION_DETECT);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSU_TX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_MSU_RX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLTM_TX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLTM_RX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLTA_TX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLTA_RX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLT_PASSED);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_SLT_FAILED);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFP_TX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFP_RX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_TX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_TFA_RX);
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_REMOTE_ROUTE_FAILURE );
        PEG_ClearPeg(CCITT_MTP3_Pegs, PEG_MTP3_USERPART_ROUTE_FAILURE );
    }
    else
    {
        if (pegId > PEG_MTP3_NUM_PEGS_CCITT)
        {
            MTP3_ERROR(("Peg Id %d not found\n", pegId));
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(CCITT_MTP3_Pegs, pegId);
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Clears the MTP3 link pegs
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *      ITS_UINT        pegId   
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_ClearLinkPeg_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode, ITS_UINT pegId)
{
    SS7_LinkPtr ln = NULL;

    ln = LINK_FindLinkNoLock(linkSet, linkCode);
    if (ln == NULL)
    {
        MTP3_ERROR(("Link %d not found in Linkset %d\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    if (pegId == MTP3_ALL_PEGS)
    {
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COO_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_COA_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECO_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_ECA_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBD_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CBA_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIN_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LIA_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUN_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LUA_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LID_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LFU_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LLI_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_LRI_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_DLC_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CSS_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNS_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_CNP_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTM_RX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_TX);
        PEG_ClearPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_SLTA_RX);
    }
    else
    {
        if (pegId > PEG_MTP3_NUM_LINK_PEGS)
        {
            MTP3_ERROR(("Peg Id %d not found\n", pegId));
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(&ln->MTP3_LINK_PEGS, pegId);
        }
    }
    
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Adds a specified linkset
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      SS7_Family      family
 *      ITS_UINT        lpc
 *      ITS_UINT        apc
 *      ITS_OCTET       ni
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
MTP3_OSS_AddLinkset_CCITT(ITS_OCTET linkSet, SS7_Family family, ITS_UINT lpc, ITS_UINT apc, ITS_UINT ni)
{
    ITS_INT         ret;
    SS7_LinkSetPtr  ls;
    SS7_LinkSet      linkset;

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls != NULL)
    {
        MTP3_ERROR(("Linkset %d already exists\n", linkSet));
        return ITS_EDUPLENTRY;
    }

    memset(&linkset, 0, sizeof(SS7_LinkSet));
    linkset.linkSet     = linkSet;
    linkset.adjacent    = apc;
    linkset.lpc         = lpc;
    linkset.ni          = ni & ROUTE_NI_MASK;
    linkset.numLinks    = 0;
    linkset.numToStart  = 0;
    linkset.isUp        = ITS_FALSE;
    linkset.family      = family;

    ret = LINKSET_AddLinkSet(&linkset);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Linkset %d Addition Error %d\n", linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Linkset %d Added\n", linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Deletes the specified linkset
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_RemoveLinkset_CCITT(ITS_OCTET linkSet)
{
    ITS_INT        ret;
    SS7_LinkSetPtr  ls;

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        return ITS_ELINKSETNOTFOUND;
    }

    if (ls->numLinks != 0)
    {
        MTP3_ERROR(("Links exist in linkset %d\n", linkSet));
        return ITS_ELINKSEXIST;
    }

    ret = LINKSET_RemLinkSet(ls);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Linkset %d Deletion Error %d\n", linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Linkset %d Deleted\n", linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Adds the specified linkcode to the linkset
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *      ITS_UINT        transId
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_AddLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode, ITS_UINT transId)
{
    ITS_INT             ret;
    SS7_LinkPtr         lp;
    SS7_LinkSetPtr      ls;
    TRANSPORT_Control   *tc;
    SS7_Link            ln;

    tc = TRANSPORT_FindTransport(transId);
    if (tc == NULL)
    {
        MTP3_ERROR(("Transport %d not found\n", transId));
        return ITS_ENOTRANSPORT;
    }

    ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
    if (ls == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        return ITS_ELINKSETNOTFOUND;
    }

    lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);
    if (lp != NULL)
    {
        MTP3_ERROR(("Link %d already exists in linkset %d\n", linkCode, linkSet));
        return ITS_EDUPLENTRY;
    }

    memset(&ln, 0, sizeof(SS7_Link));
    ln.initActive   = ITS_TRUE;
    ln.termFixed    = ITS_TRUE;
    ln.linkFixed    = ITS_TRUE;
    ln.isSAAL       = ITS_FALSE;
    ln.next         = NULL;
    ln.prev         = NULL; 
    ln.isUp         = ITS_FALSE;
    ln.isAllowed    = ITS_TRUE;
    ln.linkCode     = (ITS_OCTET) linkCode;
    ln.id           = transId;
    ln.dsmNodeId    = DSM_GetNodeId();
    ln.family       = ls->family;

    ret = LINK_AddLink(linkSet, &ln);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Addition Error %d\n", linkCode, linkSet, ret));
        return ret;
    }

    lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);
    if (lp == NULL)
    {
        MTP3_ERROR(("Link %d in linkset %d not found after addition\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    LINK_AddLinkInfoToTransport(tc, lp);

    MTP3_DEBUG(("Link %d in linkset %d Added\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Deletes the specified linkcode from the linkset
 *
 *  Input Parameters:
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       linkCode
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_RemoveLink_CCITT(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    ITS_INT         ret;
    SS7_LinkPtr     lp;
    SS7_LinkSetPtr  ls;

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        return ITS_ELINKSETNOTFOUND;
    }

    lp = LINK_FindLink(linkSet, linkCode);
    if (lp == NULL)
    {
        MTP3_ERROR(("Link %d in linkset %d not found\n", linkCode, linkSet));
        return ITS_ELINKNOTFOUND;
    }

    ret = LINK_RemLink(linkSet, lp);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Link %d in linkset %d Deletion error %d\n", linkCode, linkSet, ret));
        return ret;
    }

    MTP3_DEBUG(("Link %d in linkset %d Deleted\n", linkCode, linkSet));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Adds the specified remote point code
 *
 *  Input Parameters:
 *      ITS_UINT        rpc
 *      ITS_OCTET       ni
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       family
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_AddRemotePC_CCITT(ITS_UINT rpc, ITS_OCTET ni, ITS_OCTET linkSet, SS7_Family family)
{
    ITS_INT         ret;
    SS7_LinkSetPtr  ls;
    SS7_LinkPtr     lp;
    ROUTE_MatchInfo rinfo;
    ITS_OCTET       linkCode;

    memset(&rinfo, 0, sizeof(rinfo));

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls != NULL)
    {
        for (linkCode = 0 ; linkCode < MAX_LINKS ; linkCode++)
        {
            lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);
            if (lp != NULL)
            {
                /* link exist for this linkset ,So proceed */
                break ;
            }
        }
        if ( linkCode == MAX_LINKS )
        {
            MTP3_ERROR(("Link not found Linkset %d\n", linkSet));
            return ITS_ELINKNOTFOUND;
        }
    }
    else
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        return ITS_ELINKSETNOTFOUND;
    }

    rinfo.basic.type    = REMOTE_ROUTE;
    rinfo.basic.family  = family;
    rinfo.basic.style   = ROUTE_DPC_NI;
    rinfo.basic.dpc     = rpc;
    rinfo.basic.criteria.sio = ni ;

    rinfo.linkSet   = linkSet;
    rinfo.linkCode  = 0;
    rinfo.priority  = 0;
    rinfo.sls       = 0;
    rinfo.rkey      = 0;
    rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

    ret = ROUTE_AddRouteContextInfo(&rinfo);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Route Addition error %d\n", ret));
        return ret;
    }

    MTP3_DEBUG(("RPC %d Added\n", rpc));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Removes the specified remote point code
 *
 *  Input Parameters:
 *      ITS_UINT        rpc
 *      ITS_OCTET       ni
 *      ITS_OCTET       linkSet
 *      ITS_OCTET       family
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_RemoveRemotePC_CCITT(ITS_UINT rpc, ITS_OCTET ni, ITS_OCTET linkSet, SS7_Family family)
{
    ITS_INT             ret;
    SS7_LinkSetPtr      ls;
    SS7_Destination     *rc;
    ROUTE_MatchInfo     rinfo;

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls == NULL)
    {
        MTP3_ERROR(("Linkset %d not found\n", linkSet));
        return ITS_ELINKSETNOTFOUND;
    }

    rc = ROUTE_FindDestination(rpc, ni, family);
    if (rc == NULL)
    {
        MTP3_ERROR(("Destination with RPC %d not found\n", rpc));
        return ITS_ENODESTINATION;
    }

    rinfo.basic.type    = REMOTE_ROUTE;
    rinfo.basic.family  = family;
    rinfo.basic.style   = ROUTE_DPC_NI;
    rinfo.basic.dpc     = rpc;
    rinfo.basic.mask    = ITS_SS7_DEFAULT_ROUTE_MASK;
    rinfo.basic.criteria.sio = (ITS_OCTET)ni & ROUTE_NI_MASK;
    rinfo.linkSet   = (ITS_OCTET) linkSet;
    rinfo.linkCode  = 0;
    rinfo.priority  = 0;
    rinfo.sls       = 0;
    rinfo.rkey      = 0;

    ret = ROUTE_DeleteRouteContextInfo(&rinfo);
    if (ret != ITS_SUCCESS)
    {
        MTP3_ERROR(("Destination with RPC %d Deletion error %d\n", rpc, ret));
        return ret;
    }

    MTP3_DEBUG(("RPC %d Deleted\n", rpc));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the remote point codes configured
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      SS7_DestInfo*   remPc
 *      ITS_OCTET*      numDests
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetRemotePC_CCITT(SS7_DestInfo *remPc, ITS_OCTET* numDests)
{
    ITS_INT     ret;

    if (remPc == NULL || numDests == NULL)
        return ITS_ENOMEM;

    *numDests = 0;
    ret = DSM_TableIterate(DSM_RoutingFtGroupId, 
                           DSM_TABLE_DESTINATIONS, 
                           remPc, 
                           numDests, 
                           GetRemotePointCodeData);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the remote point codes configured
 *
 *  Input Parameters:
 *      ITS_POINTER        data
 *
 *  Output Parameters:
 *      void*       in
 *      void*       out
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
static int 
GetRemotePointCodeData(ITS_POINTER data, void *in, void *out)
{
    SS7_DestInfo*       destInfo = (SS7_DestInfo*)in;
    ITS_OCTET*          numDests = (ITS_OCTET*)out;
    SS7_Destination*    ss7Context = (SS7_Destination*)data;
    ITS_OCTET           i, j;
    ITS_OCTET           index;

    for (i = 0; i < ss7Context->numEntries; i++)
    {
        if (ss7Context->entries[i]->basic.type == REMOTE_ROUTE)
        {
            for (j = 0 ; j < i ;j++)
            {
                if (ss7Context->entries[i]->basic.dpc ==
                                  ss7Context->entries[j]->basic.dpc )
                {
                    return ITS_SUCCESS;
                }
            }

            index = *numDests;
            (destInfo + index)->dpc = ss7Context->entries[i]->basic.dpc;    
            (destInfo + index)->family = ss7Context->entries[i]->basic.family;
            (destInfo + index)->sio = ss7Context->entries[i]->basic.criteria.sio;
            (destInfo + index)->status = ss7Context->status;

            (*numDests)++;
        }
    }
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the local point codes configured
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      SS7_DestInfo*   localPc
 *      ITS_OCTET*      numDests
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
MTP3_OSS_GetLocalPC_CCITT(SS7_DestInfo *localPc, ITS_OCTET* numDests)
{
    ITS_INT     ret;

    if (localPc == NULL || numDests == NULL)
        return ITS_ENOMEM;

    *numDests = 0;
    ret = DSM_TableIterate(DSM_RoutingFtGroupId, 
                           DSM_TABLE_DESTINATIONS, 
                           localPc, 
                           numDests, 
                           GetLocalPointCodeData);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the local point codes configured
 *
 *  Input Parameters:
 *      ITS_POINTER        data
 *
 *  Output Parameters:
 *      void*   in
 *      void*   out
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
static int 
GetLocalPointCodeData(ITS_POINTER data, void *in, void *out)
{
    SS7_DestInfo*       destInfo = (SS7_DestInfo*)in;
    ITS_OCTET*          numDests = (ITS_OCTET*)out;
    SS7_Destination*    ss7Context = (SS7_Destination*)data;
    ITS_OCTET           i, j;
    ITS_OCTET           index;

    for (i = 0; i < ss7Context->numEntries; i++)
    {
        if (ss7Context->entries[i]->basic.type == LOCAL_ROUTE)
        {
            for (j = 0 ; j < i ;j++)
            {
                if (ss7Context->entries[i]->basic.dpc ==
                                            ss7Context->entries[j]->basic.dpc )
                {
                    return ITS_SUCCESS;
                }
            }

            index = *numDests;
            (destInfo + index)->dpc = ss7Context->entries[i]->basic.dpc;    
            (destInfo + index)->family = ss7Context->entries[i]->basic.family;

            (*numDests)++;
        }
    }
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      To ShutDown MTP3 Node.
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Void
 ****************************************************************************/
void static
NodeShutDown()
{
    TRANSPORT_Manager *tm;
    TRANSPORT_Control *tr;
    ITS_UINT mask;

    tm = TRANSPORT_GetManager();

    if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
    {
         return ;
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
               printf("Deactivating ls:%d lc:%d\n",
                       lp->linkSet->linkSet, lp->linkCode);

               MGMT_Main_CCITT(MTP3_USER,
                               MGMT_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               lp->linkSet->linkSet, lp->linkCode);
            }

        }
    }

    RWLOCK_UnlockShared(&tm->transportGate);
}
