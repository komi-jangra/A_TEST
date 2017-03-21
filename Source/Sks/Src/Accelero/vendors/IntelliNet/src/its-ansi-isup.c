/***************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: its-ansi-isup.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $
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
 * LOG: Revision 8.28  2004/01/09 06:56:33  akumar
 * LOG: Bug Propagation from TCS-ISUP/PR_6.3 takes place in this commit.
 * LOG:
 * LOG: Revision 8.27  2003/12/29 11:23:23  ssingh
 * LOG: Bug #691 fix propagation from TCS ISUP Branch to current.
 * LOG:
 * LOG: Revision 8.26  2003/12/29 10:26:10  ssingh
 * LOG: Message Based pegs; Bug #683 fix propagated from PR6.3
 * LOG:
 * LOG: Revision 8.25  2003/12/22 07:08:57  akumar
 * LOG: Minor Modifications.
 * LOG:
 * LOG: Revision 8.24  2003/11/24 05:38:41  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 8.23  2003/08/14 12:53:18  sswami
 * LOG: Indentation and formatting of message based PEGS
 * LOG:
 * LOG: Revision 8.22  2003/08/13 04:27:48  sswami
 * LOG: Fix for Compilation Errors with CC.[Message based PEGS MML commands]
 * LOG:
 * LOG: Revision 8.21  2003/08/12 12:58:00  sswami
 * LOG: Implementation of Message PEGS and related MML commands
 * LOG:
 * LOG: Revision 8.20  2003/07/29 19:09:29  mmiers
 * LOG: Warning removal.  People are playing fast and loose with int types,
 * LOG: please stop that.
 * LOG:
 * LOG: Revision 8.19  2003/07/22 15:43:46  mmiers
 * LOG: Warning removal.  Fix Windoze build.
 * LOG:
 * LOG: Revision 8.18  2003/07/16 11:54:04  akumar
 * LOG: GenConfig MML Modified.
 * LOG:
 * LOG: Revision 8.17  2003/06/16 13:39:56  mmanikandan
 * LOG: Xml Persistency is added.
 * LOG:
 * LOG: Revision 8.16  2003/04/30 13:34:38  sjaddu
 * LOG: ANSI To ITU changes.
 * LOG:
 * LOG: Revision 8.15  2003/04/28 15:28:08  sjaddu
 * LOG: Event TERM related changes.
 * LOG:
 * LOG: Revision 8.14  2003/04/25 14:04:29  sjaddu
 * LOG: Cic Rules is changed to ITS_OCTET.
 * LOG:
 * LOG: Revision 8.13  2003/04/25 09:52:05  akumar
 * LOG: ITS_SS7_CONTEXT name changed with ISUP_CONG_CONTEXT for cong.
 * LOG:
 * LOG: Revision 8.12  2003/04/24 14:02:44  sswami
 * LOG: Bug# 317; Alarm Enhancement related changes.
 * LOG:
 * LOG: Revision 8.11  2003/04/22 08:45:57  akumar
 * LOG: Build Error/ Warning Removal for CC compiler.
 * LOG:
 * LOG: Revision 8.10  2003/04/22 07:17:36  akumar
 * LOG: Front port PR_6.3 to Current Branch (Mainly MML)
 * LOG:
 * LOG: Revision 8.9  2003/04/18 07:17:30  sjaddu
 * LOG: Warning removal and DLSYM_Destroy being callled.
 * LOG:
 * LOG: Revision 8.8  2003/04/16 06:01:39  akumar
 * LOG: Congestion Related Changes.
 * LOG:
 * LOG: Revision 8.7  2003/04/14 10:28:27  sjaddu
 * LOG: Added destination on fly.
 * LOG:
 * LOG: Revision 8.6  2003/04/03 14:45:45  sjaddu
 * LOG: DSM reorganization, configuration changes must persisted in STAT table.
 * LOG:
 * LOG: Revision 8.5  2003/03/26 12:11:20  ssingh
 * LOG: Changed done as per ISUPPending List:
 * LOG: ansi-isup_alarms.c  : New Alarms added for HandleMTP3MgmtMsg.
 * LOG: ansi-isup_context.c : Function calls for DPC and Remote ISUP status.
 * LOG:                     : Indication sent; if msg received is on BAD Cic.
 * LOG:                     : Alarms for PAUSE/RESUME/STATUS.
 * LOG: ansi-isup_ifc.c     : Changes to incorporate CIC_INFO changes.
 * LOG: ansi-sprc.c         : CIC_INFO/CIC_MSG_INFO related changes.
 * LOG:                     : SendConfToApp removed, SendIsupIndToApp added.
 * LOG: isup_data.c         : Modified to include CIC_INFO/CIC_MSG_INFO changes.
 * LOG: its-ansi-isup.c     : CIC_INFO related changes.
 * LOG:
 * LOG: Revision 8.4  2003/03/20 21:30:34  mmiers
 * LOG: Warning removal.  Fix PRC build issue
 * LOG:
 * LOG: Revision 8.3  2003/02/27 11:01:53  akumar
 * LOG: Warning Removal
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

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <its.h>
#include <its_trace.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_iniparse.h>
#include <its_assertion.h>

#include <engine.h>

#include <dbc_serv.h>

#ident "$Id: its-ansi-isup.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"

#undef ANSI
#undef CCITT
#define ANSI
                                                                               
#ident "$Id: its-ansi-isup.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"
                                                                       
#include <ansi/isup.h>
#include <ansi/sccp.h>
#include <ansi/tcap.h>
#include <ansi/mtp3.h>

#include <isup_variants.h>
#include "isup_intern.h"

TQUEUETRAN_Manager *__ISUP_ANSI_RcvQueue;

THREAD_RET_TYPE ANSI_ISUPThread(void *arg);
static void ISUP_Console_ANSI(DBC_Server *dbc, const char *cmdLine);

static ITS_THREAD   *isupThread;

static int numThreads = 1;

static ITS_BOOLEAN  started = ITS_FALSE;
static ITS_BOOLEAN  stopped = ITS_FALSE;

extern ITS_BOOLEAN ANSI_ISUP_conglevel1Found;
extern ITS_BOOLEAN ANSI_ISUP_conglevel2Found;

/* Default values if not specified in the XML file */
extern ITS_UINT ANSI_ISUP_conglevel1;  
extern ITS_UINT ANSI_ISUP_conglevel2; 
static ITS_UINT Getlocalconglevel(TQUEUETRAN_Manager *tq);

static int DBCVarifyCicState(ITS_OCTET cic_state, DBC_Server *dbc);

#define MAX_DESC_STR      128
static char CPCFsmState[][MAX_DESC_STR] =
{
    " IDLE                  (CPC  Idle)",

    " WAIT_INCOMING_ACM     (CPC  Outgoing: Wait for Address Complete)",
    " WAIT_INCOMING_ANM     (CPC  Outgoing: Wait for Answer)",
    " RCVD_INCOMING_ANM     (CPC  Outgoing: OGC Answered)",
    " WAIT_INCOMING_RLC     (CPC  Outgoing: Wait for RLC: i.e. REL sent to Nwk)"
,
    " WAIT_INCOMING_RES     (CPC  Outgoing: OGC Suspended: SUS rcvd form Nwk)",

    " WAIT_OUTGOING_ACM     (CPC  Incoming: Wait for OGC Complete)",
    " WAIT_OUTGOING_ANM     (CPC  Incoming: Wait for Answer)",
    " SENT_OUTGOING_ANM     (CPC  Incoming: ICC Answered)",
    " WAIT_OUTGOING_RLC     (CPC  Incoming: Wait for RLC: i.e. REL rcvd from Nwk)",
    " WAIT_OUTGOING_RES     (CPC  Incoming: ICC Suspended: SUS sent to Nwk)",

    " WAIT_OUTGOING_REL     (Timeout/error, waiting to send REL to Nwk)",
    " WAIT_OUTGOING_RSC     (RSC sent to Nwk, waiting for RLC)",
    " WAIT_OUTGOING_GRA     (GRS rcvd from Nwk, waiting to send GRA to Nwk)",
    " WAIT_CONTINUITY_REPORT",
    " WAIT_INCOMING_COT",
    " WAIT_COT_REPORTS_AND_CRA",
    " WAIT_COT_REPORTS_HAVE_CRA",
    " WAIT_INCOMING_CRA",
    " WAIT_OUTGOING_IAM",
    " WAIT_INCOMING_IAM",
    " WAIT_INCOMING_COT_AND_IAM"
};

static char BLSFsmState[][MAX_DESC_STR] =
{
    "BLS_IDLE              (BLS  Outgoing: Idle)",
    "BLS_WAIT_FOR_BLA      (BLS  Outgoing: Wait for BLA from Nwk)",
    "BLS_WAIT_FOR_UBA      (BLS  Outgoing: Wait for UBA from Nwk)"
};

static char BLRFsmState[][MAX_DESC_STR] =
{
    "BLR_IDLE              (BLR  Incoming: Idle)"
};

static char MGBSFsmState[][MAX_DESC_STR] =
{
    "MGBS_IDLE             (MGBS Outgoing: Idle)",
    "MGBS_WAIT_FOR_CGBA    (MGBS Outgoing: Wait for CGBA from Nwk)",
    "MGBS_WAIT_FOR_CGUA    (MGBS Outgoing: Wiat for CGUA from Nwk)"
};

static char MGBRFsmState[][MAX_DESC_STR] =
{
    "MGBR_IDLE             (MGBR Incoming: Idle)"
};

static char CRSFsmState[][MAX_DESC_STR] =
{
    "CRS_IDLE              (CRS  Outgoing: Idle)",
    "CRS_WAIT_FOR_RELEASE  (CRS  Outgoing: Wait for RLC from Nwk)"
};

static char CRRFsmState[][MAX_DESC_STR] =
{
    "CRR_IDLE              (CRR  Incoming: Idle)"
};

static char CGRSFsmState[][MAX_DESC_STR] =
{
    "CGRS_IDLE             (CGRS Outgoing: Idle)",
    "CGRS_WAIT_FOR_GRA     (CGRS Outgoing: Wiat for GRA from Nwk)"
};

static char CGRRFsmState[][MAX_DESC_STR] =
{
    "CGRR_IDLE             (CGRR Incoming: Idle)"
};

static char CVTSFsmState[][MAX_DESC_STR] =
{
    "CVTS_IDLE             (CVT  Outgoing: Idle)",
    "CVTS_WAIT_FOR_CVR     (CVT  Outgoing: Wait for CVR from Nwk)"
};

static char CVTRFsmState[][MAX_DESC_STR] =
{
    "CVTR_IDLE             (CVT  Incoming: Idle)",
    "CVTR_WAIT_FOR_CVR     (CVT  Incoming: CVT rcvd from Nwk, waiting to send CVR)"
};

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle MTP3 management indications.
 *
 *  Input Parameters:
 *      object
 *      userData
 *      callData
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
HandleMTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ITS_EVENT* ev = (ITS_EVENT *)callData;
    ITS_EVENT tmp;

    ITS_EVENT_INIT(&tmp, ev->src, ev->len);
    memcpy(tmp.data, ev->data, ev->len);

    if (TRANSPORT_PutEvent(ITS_ISUP_ANSI_SRC, ev) != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&tmp);
    }
    else
    {
        *ev = tmp;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is called for LOcal Automatic Congestion Control.
 *
 *  Input Parameters:
 *      event - Time out Event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      int - Level of Congestion.
 *
 *  Notes:
 *      None.
 *
 *  See Also:
 ****************************************************************************/
int
CheckLocalCongestion(ITS_EVENT *event)
{
    ITS_UINT lvl = 0;
    ISUP_CONGESTION_ENTRY localcong_ind;

    static ITS_UINT previous_level = 0;
    ITS_UINT current_level = 0;


    /* Get the ISUP Transport Queue Length */
    lvl = Getlocalconglevel(__ISUP_ANSI_RcvQueue);

    /* Set Current Level of Congestion */
    if (lvl < ANSI_ISUP_conglevel1)
    {
        current_level = 0;
    }
    else if (lvl >= ANSI_ISUP_conglevel1 && lvl < ANSI_ISUP_conglevel2)
    {
        current_level = ANSI_ISUP_conglevel1;
    }
    else if (lvl >= ANSI_ISUP_conglevel2)
    {
        current_level = ANSI_ISUP_conglevel2;
    }

    /* Check If we need to Report Congestion */
    if (!current_level && !previous_level)
    {
        /* No Previous and current congestion */
        return current_level;
    }
    else if (current_level == previous_level)
    {
        /* No Change in Cong Level */
        return current_level;
    }
    else if (!current_level &&  previous_level)
    {
        /* Congestion removed, report */
        localcong_ind.congId = ITS_ISUP_LOC_NOCONG_IND;
        ANSI_ISUP_conglevel1Found = ITS_FALSE;
        ANSI_ISUP_conglevel2Found = ITS_FALSE;
        previous_level = 0;
        ISUP_DEBUG(("\n Local Congestion Ceased !!\n"));
        ISUP_Alarm_ANSI(3169, __FILE__, __LINE__,"Local Congestion Ceased");
    }

    /* Congestion level is either changed (up/down) or reported
     * for the first time. Report to Application
     */
    else if (current_level == ANSI_ISUP_conglevel1 )
    {
        ISUP_DEBUG(("\n Local Congestion of LEVEL 1 detected \n"));
        localcong_ind.congId = ITS_ISUP_LOC_CONGLEVEL1_IND;
        ANSI_ISUP_conglevel1Found = ITS_TRUE;
        ANSI_ISUP_conglevel2Found = ITS_FALSE;
        previous_level = ANSI_ISUP_conglevel1;
        /* Generate an Alarm */

        ISUP_Alarm_ANSI(3167, __FILE__, __LINE__,
                        "Local Cong Level : 0x%02x", ANSI_ISUP_conglevel1);

    }
    else if (current_level == ANSI_ISUP_conglevel2)
    {
        ISUP_DEBUG(("\n Local Congestion of LEVEL 2 detected \n"));
        localcong_ind.congId = ITS_ISUP_LOC_CONGLEVEL2_IND;
        ANSI_ISUP_conglevel1Found = ITS_FALSE;
        ANSI_ISUP_conglevel2Found = ITS_TRUE;
        previous_level = ANSI_ISUP_conglevel2;
        /* Generate an Alarm */

        ISUP_Alarm_ANSI(3168, __FILE__, __LINE__,
                        "Local Cong Level : 0x%02x", ANSI_ISUP_conglevel2);
    }
    else
    {
        /*just to be safe*/
        return current_level;
    }

    /* Fill in Indication data to be sent to app. */
    localcong_ind.sio = 0; 
    localcong_ind.opc = 0; 
    localcong_ind.dpc = 0; 

    /* Send a congestion level indication to the application */
    SPRC_SendLocCongIndicToApp_ANSI(ITS_ISUP_INV_VCIC, &localcong_ind);
    
    return previous_level;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the IntelliNet stack thread
 *
 *  Input Parameters:
 *      handle - stack transport handle
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
INTELLINET_ISUP_Initialize_ANSI(ITS_SS7_HANDLE handle)
{
    RESFILE_Manager *res;
    const char *section;
    int i, j, ret;
    ITS_Class dbClass;
    char val[ITS_PATH_MAX << 2];

    if (started)
    {
        return (ITS_SUCCESS);
    }

    started = ITS_TRUE;

    if ((__ISUP_ANSI_RcvQueue = TQUEUETRAN_CreateTransport("ANSI-ISUP",
                                                            ITS_ISUP_ANSI_SRC,
                                                            ITS_ISUP_ANSI))
        == NULL)
    {
        started = ITS_FALSE;

        return (ITS_ENOTRANSPORT);
    }

    res = TRANSPORT_RES(__ISUP_ANSI_RcvQueue);
    section = TRANSPORT_NAME(__ISUP_ANSI_RcvQueue);

    ret = ISUP_Init_ANSI(res, section);

    if (ret != ITS_SUCCESS)
    {
        TQUEUETRAN_DeleteTransport(__ISUP_ANSI_RcvQueue);

        return (ret);
    }

    /* get the number of threads */
    if (res != NULL)
    {
        if (RESFILE_GetKeyValueOf(res, section, NUM_THREADS_STRING,
                                  val, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            numThreads = RESFILE_ParseNum(val);
            if (numThreads < 1)
            {
                numThreads = 1;
            }
        }
    }

    CALLBACK_AddCallback(MTP3_ANSI_ManagementCallbacks, HandleMTP3Mgmt, NULL);

    if ((isupThread = (ITS_THREAD *)malloc(numThreads *
                                           sizeof(ITS_THREAD))) == NULL)
    {
        ISUP_CRITICAL(("ISUP_Init: Couldn't create thread array.\n"));

        ISUP_Term_ANSI();

        TQUEUETRAN_DeleteTransport(__ISUP_ANSI_RcvQueue);

        started = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    for (i = 0; i < numThreads; i++)
    {
        if (THREAD_CreateThread(&isupThread[i], 0, ANSI_ISUPThread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            ISUP_CRITICAL(("ISUP_Init: Couldn't create ISUP thread.\n"));

            /* ISUP failed to Intialize -  couldn't create thread */

            ISUP_Alarm_ANSI(3001, __FILE__, __LINE__, NULL);

            for (j = 0; j < i; j++)
            {
                THREAD_KillThread(&isupThread[j]);

                THREAD_DeleteThread(&isupThread[j]);
            }

            free(isupThread);

            ISUP_Term_ANSI();

            TQUEUETRAN_DeleteTransport(__ISUP_ANSI_RcvQueue);

            started = ITS_FALSE;

            return (ITS_EBADTHREAD);
        }
    }

    /* INFORMATIONAL - ISUP Intialized Successfully */
    ISUP_Alarm_ANSI(3002, __FILE__, __LINE__, NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_AddDoCommand(ISUP_Console_ANSI);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the IntelliNet stack thread
 *
 *  Input Parameters:
 *      handle - stack transport handle
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
INTELLINET_ISUP_Terminate_ANSI(ITS_SS7_HANDLE handle)
{
    ITS_EVENT ev;
    void *status;
    int i;
    ITS_Class dbClass;

    if (!started || stopped)
    {
        return;
    }

    stopped = ITS_TRUE;

    ISUP_CRITICAL(("ISUP_Terminate_ANSI.\n"));

    /* ISUP Terminating */

    ISUP_Alarm_ANSI(3003, __FILE__, __LINE__, NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_RemDoCommand(ISUP_Console_ANSI);
    }

    CALLBACK_RemCallback(MTP3_ANSI_ManagementCallbacks, HandleMTP3Mgmt, NULL);

    ITS_EVENT_INIT(&ev, ITS_ISUP_ANSI_SRC, 0);

    for (i = 0; i < numThreads; i++)
    {
        TRANSPORT_PutEvent(ITS_ISUP_SRC, &ev);
    }

    for (i = 0; i < numThreads; i++)
    {
        THREAD_WaitForThread(&isupThread[i], &status);

        THREAD_DeleteThread(&isupThread[i]);
    }

    free(isupThread);

    assert(__ISUP_ANSI_RcvQueue != NULL);

    TQUEUETRAN_DeleteTransport(__ISUP_ANSI_RcvQueue);

    ISUP_Term_ANSI();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is the entry point for the ANSI ISUP thread.
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
 *
 *  Notes:
 *      This method should be considered an undocumented internal
 *      ISUP function.
 *
 *  See Also:
 ****************************************************************************/
THREAD_RET_TYPE
ANSI_ISUPThread(void *arg)
{
    ITS_EVENT isupEvent;
    ITS_BOOLEAN cont;

    ISUP_DEBUG(("ISUP_Main: -------  Starting ISUP Thread  -------\n"));

    MTP3_EnableUserPart_ANSI(MTP3_SIO_ISUP, ITS_ISUP_ANSI_SRC);

    memset(&isupEvent, 0, sizeof(ITS_EVENT));

    /* 
     * Before waiting for ISUP events, we must set the context for the
     * Variant in used (such as: Message and Parameter Sets supported).
     */

    cont = ITS_TRUE;

    TRANSPORT_IS_ACTIVE(__ISUP_ANSI_RcvQueue) = ITS_TRUE;

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__ISUP_ANSI_RcvQueue))
                                                        (__ISUP_ANSI_RcvQueue,
                                                         &isupEvent)
           == ITS_SUCCESS)

    {
        ISUP_DEBUG(("\n****** Enter the ISUPThread WHILE loop ******\n\n"));

        switch (isupEvent.src)
        {
        case ITS_MTP3_ANSI_SRC:
            ISUP_DEBUG(("ISUP_Main: process ISUP event from MTP3.\n"));

            __ISUP_HandleMsg_ANSI(&isupEvent, ISUP_SRC_L3_ANSI);
            break;

        case ITS_ISUP_ANSI_SRC:
            ISUP_CRITICAL(("ISUP_Main: termination event.\n"));
            ISUP_DEBUG(("ISUP_Main: Termination event...Terminating!\n"));

            TRANSPORT_IS_ACTIVE(__ISUP_ANSI_RcvQueue) = ITS_FALSE;

            cont = ITS_FALSE;
            break;

        case ITS_TIMER_SRC:
            ISUP_DEBUG(("ISUP_Main: process TIMER event.\n"));
            __ISUP_HandleTimeout_ANSI(&isupEvent);
            break;

        default:
            ISUP_DEBUG(("ISUP_Main: process ISUP event from Application.\n"));
            __ISUP_HandleMsg_ANSI(&isupEvent, ISUP_SRC_APP_ANSI);
            break;
        }
    }

    TRANSPORT_IS_ACTIVE(__ISUP_ANSI_RcvQueue) = ITS_FALSE;

    ISUP_DEBUG(("ISUP_Main: -------  Terminating ISUP Thread  -------\n"));
    ISUP_CRITICAL(("ISUP_Main: -------  Terminating ISUP Thread  -------\n"));

    /* ISUP aborting */
    ISUP_Alarm_ANSI(3004, __FILE__, __LINE__, NULL);

    MTP3_DisableUserPart_ANSI(MTP3_SIO_ISUP);

    THREAD_NORMAL_EXIT;
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
ITSSS7DLLAPI int
ISUP_SendMsgMMLToStack_ANSI(ISUP_PCIC pcic, ITS_OCTET type,
                            ITS_ISUP_IE *ies, int ieCount)
{
    int ret ;
    ITS_USHORT len =0;
    int index = 0;
    ISUP_MSG_DESC *msg_desc = NULL;
    ISUP_CIC_INFO *cic_rec = NULL;
    ISUP_OPC_DPC_INFO config_info;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_EVENT ev;

    /* Get cic_rec using the pcic as key */
    cic_rec = ISUP_FindPcic( pcic);
    if (cic_rec == NULL)
    {
        return ITS_EINVCIC;
    }

    /* CIC record no longer needed. */
    ISUP_ReleaseCic(cic_rec);


    ret = ISUP_FindOpcDpc(ISUP_PCIC_TO_OPC_DPC(pcic),&config_info);
    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTCONFIG;
    }

    /* Check the Message Type */
    if (!VAR_IsMsgSupported( config_info.isup_var_class, type ))
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ITS_EINVISUPMSGTYPE;
    }

    /* Get MSG_DESC from Variant record */
    msg_desc = VAR_GetMsgDescription( config_info.isup_var_class, type );
    if (msg_desc == NULL)
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ITS_ENOTCONFIG;
    }

    ret = ISUP_MessageSanityCheck_ANSI(type, ies, ieCount, msg_desc);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ret;
    }

    memset( (char *)data, 0, ISUP_MAX_MSG_LEN );
    ret = ISUP_MTP3Encode_ANSI( data, &len, type, ies, ieCount,
                                config_info.isup_var_class );
    if (ret != ITS_SUCCESS)
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ret;
    }

    ret = ISUP_ReleaseOpcDpc(&config_info);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT( (&ev), ISUP_SRC_APP_ANSI, (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len) );

    /* Fill in MTP3 Message Type */
    ev.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy( (char *)&ev.data[index], (char *)&pcic.hdr,
             sizeof(MTP3_HEADER_ANSI) );

    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    ev.data[index++] = (ITS_OCTET)(pcic.cic & 0xFFU);
    ev.data[index++] = (ITS_OCTET)(( pcic.cic >> 8) & 0xFFU);

    /* Fill in the ISUP message type */
    ev.data[index++] = type;


    /* Fill in Encoded ISUP message data */
    memcpy( (char *)&ev.data[index], (char *)data, len );
    ret = TRANSPORT_PutEvent(ITS_ISUP_ANSI_SRC, &ev);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&ev);
    }

    return ret;
}

/*.implementation:
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
DBCPrintCicPegs(ISUP_CFG_PEGS *cicPeg, DBC_Server *dbc)
{
    int i =0;
    ITS_UINT value;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name                       Peg Count \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                       --------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
    {
        value = cicPeg[i].pegVal;
        switch (i)
        {
        case    PEG_ISUP_CIC_NO_RLC_T5:
            sprintf(buf,"\n%s %18d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_REL_ABNORMAL:
            sprintf(buf,"%s %15d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_MISSING_ACK_IN_CGBA:
            sprintf(buf,"%s %8d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_MISSING_ACK_IN_CGUA:
            sprintf(buf,"%s %8d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGBA:
            sprintf(buf,"%s %7d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGUA:
            sprintf(buf,"%s %7d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_CGBA_ABNORMAL_ACK:
            sprintf(buf,"%s %4d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK:
            sprintf(buf,"%s %4d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_BLA_ABNORMAL_ACK :
            sprintf(buf,"%s %5d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_UBA_ABNORMAL_ACK:
            sprintf(buf,"%s %5d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_BLA_T13:
            sprintf(buf,"%s %17d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_UBA_T15:
            sprintf(buf,"%s %17d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_CGBA_T19:
            sprintf(buf,"%s %16d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_CGUA_T21:
            sprintf(buf,"%s %16d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_MSG_FORMAT_ERR:
            sprintf(buf,"%s %13d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_MSG_RCVD:
            sprintf(buf,"%s %13d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        }
    }
}
/*.implementation:
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
DBCPrintGeneralPegs(DBC_Server *dbc)
{

    int i =0;
    ITS_UINT value;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name                   Peg Count \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                   --------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < PEG_ISUP_NUM_PEGS; i++)
    {
        switch(i)
        {
        case PEG_ISUP_TOT_MSGS_SENT:
            value = PEG_GetPeg(ANSI_ISUP_Pegs, i);
            sprintf(buf,"\n%s %16d\n",ISUP_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case PEG_ISUP_TOT_MSGS_RCVD:
            value = PEG_GetPeg(ANSI_ISUP_Pegs, i);
            sprintf(buf,"%s %16d\n",ISUP_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        }
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
DBCPrintCicState(ISUP_CIC_INFO *cic_rec, DBC_Server *dbc)
{
    char buf[ITS_PATH_MAX];
    char *cco , *cro ,*dco;
    char *cci, *cri;

    sprintf(buf, "\n======================================================================\n");
    DBC_AppendText(dbc, buf);
    sprintf(buf, "Cic States for cic %d:\n",cic_rec->pcic.cic);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "----------------------\n");
    DBC_AppendText(dbc, buf);
    sprintf(buf, "Original cic number = %d\n", cic_rec->pcic.cic);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CIC Rule String =  %s\n", ISUP_CkgpCtrlToString(cic_rec->cic_rule));
    DBC_AppendText(dbc, buf);
    sprintf(buf, "** (cpc, mpc) : ");
    DBC_AppendText(dbc, buf);
    switch(buf, cic_rec->cic_state)
    {
       /* H G F E  D C B A */
       /* 0 0 0 0  0 0 0 0 */
        case 0x00: /* Transient */
            sprintf(buf, "Circuit State: 0x%x : TRANSIENT\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);

            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 0 0 1 */
        case 0x01: /* spare (no interpretation) */
            sprintf(buf, "Circuit State: 0x%x : Spare "
                   "(no Interpretation)\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 0 1 0 */
        case 0x02: /* spare (no interpretation) */
            sprintf(buf, "Circuit State: 0x%x : Spare "
                   "(no Interpretation)\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 0 1 1 */
        case 0x03: /* Unequipped */
            sprintf(buf, "Circuit State: 0x%x : UNEQUIPPED\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 1 0 0 */
        case 0x04: /* Incoming Circuit Busy, Active */
            sprintf(buf, "Circuit State: 0x%x : INCOMING CIRCUIT BUSY, ACTIVE\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;


       /* H G F E  D C B A */
       /* 0 0 0 0  0 1 0 1 */
        case 0x05: /* Incoming Circuit Busy, Locally Blocked */
            sprintf(buf, "Circuit State: 0x%x : INCOMING CIRCUIT BUSY, LOCALLY BLOCKED \n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 1 1 0 */
        case 0x06: /* Incoming Circuit Busy, Remotely Blocked */
            sprintf(buf, "Circuit State: 0x%x : INCOMING CIRCUIT BUSY, REMOTELY BLOCKED\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 1 1 1 */
        case 0x07: /* Incoming Circuit Busy, Locally & Remotely Blocked */
            sprintf(buf, "Circuit State: 0x%x : INCOMING CIRCUIT BUSY, LOCALLY &REMOTELY BLOCKED\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;


       /* H G F E  D C B A */
       /* 0 0 0 0  1 0 0 0 */
        case 0x08: /* Outgoing Circuit Busy, Active */
            sprintf(buf, "Circuit State: 0x%x : OUTGOING CIRCUIT BUSY, ACTIVE\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 0 0 1 */
        case 0x09: /* Outgoing Circuit Busy, Locally Blocked */
            sprintf(buf, "Circuit State: 0x%x : OUTGOING CIRCUIT BUSY, LOCALLY BLOCKED \n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 0 1 0 */
        case 0x0A: /* Outgoing Circuit Busy, Remotely Blocked */
            sprintf(buf, "Circuit State: 0x%x : OUTGOING CIRCUIT BUSY, REMOTELY BLOCKED\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 0 1 1 */
        case 0x0B: /* Outgoing Circuit Busy, Locally & Remotely Blocked */
            sprintf(buf, "Circuit State: 0x%x : OUTGOING CIRCUIT BUSY, LOCALLY &REMOTELY BLOCKED\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 1 0 0 */
        case 0x0C: /* Idle, local UNblok, remote UNblock*/
            sprintf(buf, "Circuit State: 0x%x : IDLE, LOCAL UNBLOCK, REMOTE UNBLOCK\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 1 0 1 */
        case 0x0D: /* Idle, Locally Blocked */
            sprintf(buf, "Circuit State: 0x%x : IDLE, LOCALLY BLOCKED\n",
                   cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 1 1 0 */
        case 0x0E: /* Idle, Remotely Blocked */
            sprintf(buf, "Circuit State: 0x%x : IDLE, REMOTELY BLOCKED\n",
                   cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

       /* H G F E  D C B A */

       /* 0 0 0 0  1 1 1 1 */
        case 0x0F: /* Idle, Locally & Remotely Blocked */
            sprintf(buf, "Circuit State: 0x%x : IDLE, LOCALLY & REMOTELY BLOCKED
\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;

        default:
            sprintf(buf, "Circuit State: 0x%x : Spare "
                   "(no Interpretation)\n", cic_rec->cic_state);
            DBC_AppendText(dbc, buf);
            break;
    }

    sprintf(buf, "\nCall Processing Control Fsm State:\n");
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CPC  State: %s\n", CPCFsmState[cic_rec->fsm_state]);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\nMaintenance Processing Control Fsm States:\n");
    DBC_AppendText(dbc, buf);
    sprintf(buf, "BLS  State: %s\n", BLSFsmState[cic_rec->bls_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "BLR  State: %s\n", BLRFsmState[cic_rec->blr_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "MGBS State: %s\n", MGBSFsmState[cic_rec->mgbs_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "MGBR State: %s\n", MGBRFsmState[cic_rec->mgbr_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CRS  State: %s\n", CRSFsmState[cic_rec->crs_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CRR  State: %s\n", CRRFsmState[cic_rec->crr_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CGRS State: %s\n", CGRSFsmState[cic_rec->cgrs_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CGRR State: %s\n", CGRRFsmState[cic_rec->cgrr_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CVTS State: %s\n", CVTSFsmState[cic_rec->cvts_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CVTR State: %s\n", CVTRFsmState[cic_rec->cvtr_state]);
    DBC_AppendText(dbc, buf);

    switch(cic_rec->cco_state)
    {
    case CCO_IDLE :
        cco = "CCO_IDLE";
        break;
    case CCO_WAIT_COT_REPORT :
        cco = "CCO_WAIT_COT_REPORT";
        break;
    }
    sprintf(buf, "CCO State:  %s\n",cco);
    DBC_AppendText(dbc, buf);

    switch(cic_rec->cci_state)
    {
    case CCI_IDLE :
        cci = "CCI_IDLE";
        break;
    case CCI_WAIT_FOR_COT :
        cci = "CCI_WAIT_FOR_COT";
        break;
    }
    sprintf(buf, "CCI State:  %s\n",cci);
    DBC_AppendText(dbc, buf);

    switch(cic_rec->cro_state)
    {
    case CRO_IDLE :
        cro = "CRO_IDLE";
        break;
    case CRO_WAIT_TIMER_EXPIRY :
        cro = "CRO_WAIT_TIMER_EXPIRY";
        break;
    case CRO_WAIT_FOR_COT :
        cro = "CRO_WAIT_FOR_COT";
        break;
    case CRO_WAIT_FOR_RLC :
        cro = "CRO_WAIT_FOR_RLC";
        break;
    }
    sprintf(buf, "CRO State:  %s\n",cro);
    DBC_AppendText(dbc, buf);
    switch(cic_rec->cri_state)
    {
    case CRI_IDLE :
        cri = "CRI_IDLE";
        break;
    case CRI_WAIT_FOR_CCR :
        cri = "CRI_WAIT_FOR_CCR";
        break;
    case CRI_WAIT_FOR_REL :
        cri = "CRI_WAIT_FOR_REL";
        break;
    case CRI_WAIT_FOR_LPA :
        cri = "CRI_WAIT_FOR_LPA";
        break;
    }
    sprintf(buf, "CRI State:  %s\n",cri);
    DBC_AppendText(dbc, buf);

    switch(cic_rec->dco_state)
    {
    case DCO_IDLE :
        dco = "DCO_IDLE";
        break;
    case DCO_WAIT_FOR_LPA :
        dco = "DCO_WAIT_FOR_LPA";
        break;
    }
    sprintf(buf, "DCO State:  %s\n",dco);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "\n======================================================================\n");

    DBC_AppendText(dbc, buf);
    /* release cic_rec */
    ISUP_ReleaseCic(cic_rec);

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
static void
DBCPrintAllCicsCfg(ISUP_CFG_CKGP_INFO *ckgp, ITS_UINT noEnt, DBC_Server *dbc)
{
    char buf[ITS_PATH_MAX];
    ITS_UINT count;
    int cicsInckg = ISUP_ANSI_MAX_CICS_IN_GP;
    int j =0;
    ITS_USHORT cic = 0, startcic = 0;
    ITS_OCTET cicrule = ISUP_CKGP_CTRL_DEF;
    ITS_BOOLEAN cics_present = ITS_FALSE;
    ITS_BOOLEAN startcicFound = ITS_FALSE;

    /* how to find the number of CICs configured, what if
     * there is no CIC configured, it's good to print, the
     * following statement, Will it ever reach here :(
     */
    if (noEnt == 0)
    {
        sprintf(buf,"\nCics Provisioned: NONE\n");
        DBC_AppendText(dbc, buf);
        return;
    }

    for (count = 0; count < (ITS_UINT)noEnt; ++count)
    {
        if (ckgp[count].usable_cics[0] == 0)
        {
            continue;
        }

        sprintf(buf,"\nCircuit group id = %d ", ckgp[count].ckgp_id);
        DBC_AppendText(dbc, buf);

        sprintf(buf,"\nProvisioned cicRange        cicRule\n");
        DBC_AppendText(dbc, buf);

        startcicFound = ITS_FALSE;

        for (j = 0; j < cicsInckg; j++)
        {
            if ((ckgp[count].usable_cics[0] & (0x00000001 << j)) != 0)
            {
                cics_present = ITS_TRUE;
                cic = (ckgp[count].ckgp_id * cicsInckg) + j;

                if (!startcicFound)
                {
                    startcic = (ckgp[count].ckgp_id * cicsInckg) + j;
                    startcicFound = ITS_TRUE;
                }
                else if (cicrule != ckgp[count].contl[j])
                {
                     sprintf(buf,"    %5d-%d %20s \n",
                             startcic, cic - 1,
                             ISUP_CkgpCtrlToString( cicrule));
                     DBC_AppendText(dbc, buf);
                     startcic = (ckgp[count].ckgp_id * cicsInckg) + j;
                }
            }
            else
            {
                if (startcicFound)
                {
                     sprintf(buf,"    %5d-%d %20s \n",
                             startcic, cic,
                             ISUP_CkgpCtrlToString(cicrule));
                     DBC_AppendText(dbc, buf);
                }
                startcicFound = ITS_FALSE;
            }

            cicrule = ckgp[count].contl[j];
        }

        if (startcicFound)
        {
            sprintf(buf,"    %5d-%d %20s \n",
                    startcic, cic, 
                    ISUP_CkgpCtrlToString(cicrule));
            DBC_AppendText(dbc, buf);
        }
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
DBCPrintTimerCfg(ISUP_CFG_TMR_INFO *cfg,int *tId, DBC_Server *dbc)
{
    ITS_OCTET i =0;
    ISUP_CFG_TMR_INFO tmr_info;
    const char *tmr_hndl_str;
    const char *tmr_id_str;
    char buf[ITS_PATH_MAX];

    if (tId == NULL)
    {
        sprintf(buf,"\nTimer   Value    Handled By  \n");
        DBC_AppendText(dbc,buf);

        sprintf(buf,"        (sec)   \n\n");
        DBC_AppendText(dbc,buf);

        for (i = 1; i < ITS_ISUP_TIMER_LAST; i++)
        {
            tmr_id_str = ISUP_TimerToString(i);
            if (tmr_id_str == NULL)
            {
                return;
            }

            tmr_info = cfg[i];

            tmr_hndl_str = ISUP_TimerHandlerToString((ISUP_TMR_HNDL)tmr_info.tmr_cfg_hndl_layer);

            if (tmr_hndl_str == NULL)
            {
                return;
            }

            if (tmr_info.tmr_cfg_value != 0)
            {

                sprintf(buf,"%5s%8d%14s  \n\n",tmr_id_str,
                                                         tmr_info.tmr_cfg_value,
                                                              tmr_hndl_str);
            }
            else
            {
                sprintf(buf,"%5s%8d         %s  \n\n",tmr_id_str,
                                                         tmr_info.tmr_cfg_value,
                                        "Comment: Unspecified for US Networks");
            }
            DBC_AppendText(dbc,buf);
        } 
    }
    else
    {
        ISUP_CFG_TMR_INFO tmr_info;

        if (*tId > ISUP_CFG_MAX_TIMERS)
        {
            sprintf(buf, "\n**** Invalid Timer Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        tmr_info = cfg[*tId]; 


        if (tmr_info.tmr_cfg_value == 0)
        {
            sprintf(buf,"\nTimer   %s  Value  %d sec   HandledBy    %s\n",
                   ISUP_TimerToString((ITS_OCTET)*tId),
                   tmr_info.tmr_cfg_value,
                   "Comment: Unspecified for US Networks");
        }
        else
        {
            sprintf(buf,"\nTimer   %s  Value  %d sec  HandledBy    %s\n\n",
                   ISUP_TimerToString((ITS_OCTET)*tId),
                   tmr_info.tmr_cfg_value,
                   ISUP_TimerHandlerToString((ISUP_TMR_HNDL)tmr_info.tmr_cfg_hndl_layer));
        }
        DBC_AppendText(dbc, buf);
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
DBCPrintDestCfgInfo(ISUP_CFG_DEST_INFO *config_info, DBC_Server *db_c)
{
    char buf[ITS_PATH_MAX];
    int ret =0;
    ISUP_CFG_CKGP_INFO * info;
    int noEnt;

    sprintf(buf,"\nVARIANT TYPE    %s",
            ISUP_VariantToString(config_info->variant));
    DBC_AppendText(db_c, buf);

    sprintf(buf,"\nOPC = %d \n", config_info->cfg.opc);
    DBC_AppendText(db_c, buf);
    sprintf(buf,"DPC = %d \n", config_info->cfg.dpc);
    DBC_AppendText(db_c, buf);
    sprintf(buf,"SIO = %d \n", config_info->cfg.sio);
    DBC_AppendText(db_c, buf);

    ret = ISUP_GetAllCicsCfg_ANSI(config_info->cfg, &info, &noEnt);
    if (ret == ITS_SUCCESS)
    {
        DBCPrintAllCicsCfg(info, noEnt, db_c);
        free(info);
    }

    switch(config_info->congesInd)
    {
    case ISUP_CFG_RMTCONGES_LEVEL1:
        
        sprintf(buf,"\nRemote ISUP_CONGES Indicator:  %s\n","ISUP_RMT_CONGES_LEVEL1");
        break;
    case ISUP_CFG_RMTCONGES_LEVEL2:
        sprintf(buf,"\nRemote ISUP_CONGES Indicator:  %s\n","ISUP_RMT_CONGES_LEVEL2");
        break;
    case ISUP_CFG_RMTCONGES_LEVEL3:
        sprintf(buf,"\nRemote ISUP_CONGES Indicator:  %s\n","ISUP_RMT_CONGES_LEVEL3");
        break;
    case ISUP_CFG_RMTCONGES_OFF:
        sprintf(buf,"\nRemote ISUP_CONGES Indicator:  %s\n","ISUP_RMT_CONGES_OFF");
        break;
    }
    DBC_AppendText(db_c, buf);

    switch(config_info->exchange_type)
    {
    case ISUP_CFG_EXCHANGE_TYPE_A:
        sprintf(buf,"\nLocal Exchange Type:           %s\n","TYPE_A");
        break;

    case ISUP_CFG_EXCHANGE_TYPE_B:
        sprintf(buf,"\nLocal Exchange Type:           %s\n","TYPE_B");
        break;
   
    case ISUP_CFG_EXCHANGE_TYPE_INV:
        sprintf(buf,"\nLocal Exchange Type:           %s\n","TYPE_INV");
    }
    DBC_AppendText(db_c, buf);

    switch(config_info->remote_isup_stat)
    {
    case ISUP_CFG_REMOTE_AVAILABLE:
        
        sprintf(buf,"\nISUP_REMOTE_ISUP_STATUS:       %s\n",
                "REMOTE ISUP AVAILABLE");
        break;
    case ISUP_CFG_REMOTE_UNAVAILABLE:
        sprintf(buf,"\nISUP_REMOTE_ISUP_STATUS:       %s\n",                                           "REMOTE ISUP UNAVAILABLE");
        break;
    case ISUP_CFG_REMOTE_UNEQUIPPED:
        sprintf(buf,"\nISUP_REMOTE_ISUP_STATUS:       %s\n", 
                   "REMOTE ISUP UNEQUIPPED");
        break;
    }
    DBC_AppendText(db_c, buf);

    switch(config_info->dest_reachable)
    {
    case ISUP_CFG_DEST_UNREACHABLE:
        sprintf(buf,"\nISUP_DEST_STATUS:              %s\n","DESTINATION UNREACHABLE");
        break;

    case ISUP_CFG_DEST_REACHABLE:
        sprintf(buf,"\nISUP_DEST_STATUS:              %s\n","DESTINATION REACHABLE");
        break;
    }
    DBC_AppendText(db_c, buf);
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
ISUP_DestIterProc_ANSI(ITS_INT context, ITS_POINTER data, void *in, void *out)
{
    ISUP_OPC_DPC_INFO *config_info;
    ISUP_CFG_DEST_INFO info;
    int i =0;

    if (data == NULL || in == NULL)
    {
        return !ITS_SUCCESS;
    }

    config_info = (ISUP_OPC_DPC_INFO *)data;

    info.cfg.opc = MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label);
    info.cfg.dpc = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->opc_dpc_ni.label);
    info.cfg.sio = config_info->opc_dpc_ni.sio;

    info.variant =  config_info->isup_var_type;
    info.congesInd = (ISUP_CFG_CONGES)config_info->isup_rmt_conglev;
    info.exchange_type = (ISUP_CFG_EXCHANGE_TYPE)config_info->exchange_type;
    info.dest_reachable = (ISUP_CFG_DEST_STATUS)config_info->dest_stat;
    info.remote_isup_stat =
         (ISUP_CFG_REMOTE_ISUP_STATUS) config_info->remote_isup_stat;
    
    for( i = 0;i < ISUP_CFG_MAX_TIMERS ; ++i)
    {
        info.timer_info[i].tmr_cfg_hndl_layer = 
             (ISUP_CFG_TMR_HNDL)config_info->tmr_hndl_info[i].tmr_hndl_layer;

        info.timer_info[i].tmr_cfg_value = 
                config_info->tmr_hndl_info[i].tmr_value;
    }
    DBCPrintDestCfgInfo(&info, (DBC_Server*) in);

    return ITS_SUCCESS;
}

/*.implementation:
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
ISUP_PrintCong_ANSI(ITS_UINT congLev, DBC_Server *dbc)
{
    char buf[ITS_PATH_MAX];

    if (congLev == 1)
    {
       /* Print the Congestion Level 1 Value */
       sprintf(buf,"\nCongLevel1:    %d\n", ANSI_ISUP_conglevel1);
    }
    else
    {
       /* Print the Congestion Level 2 Value */
       sprintf(buf,"\nCongLevel2:    %d\n", ANSI_ISUP_conglevel2);
    }

    DBC_AppendText(dbc, buf);
    return ITS_SUCCESS;
}

/*.implementation:
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
DBCPrintGeneralPegType(DBC_Server *dbc)
{

    int i =0;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name              Peg id \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------              ------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < PEG_ISUP_NUM_PEGS; i++)
    {
        switch(i)
        {
        case PEG_ISUP_TOT_MSGS_SENT:
            sprintf(buf,"%s    %5d\n",ISUP_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case PEG_ISUP_TOT_MSGS_RCVD:
            sprintf(buf,"%s    %5d\n",ISUP_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        }
    }
}

/*.implementation:
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
DBCPrintMsgSentPegsType(DBC_Server *dbc)
{
    int i =0;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name                                 Peg id \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                                 ------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < ISUP_MAX_MSG_CODE ; i++)
    {
        switch (i)
        {
        case PEG_ISUP_IAM_SENT_TO_REMOTE:
            sprintf(buf,"\n%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_ACM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_ANM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REL_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_RLC_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_BLO_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_UBL_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_BLA_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CPG_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CGB_SENT_TO_REMOTE :
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CGBA_SENT_TO_REMOTE:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CQM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CQR_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_GRS_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_GRA_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CGU_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CGUA_SENT_TO_REMOTE:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CRG_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
  
        case PEG_ISUP_CFN_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_COT_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CCR_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_FOT_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_INF_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_INR_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_LPA_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_PAM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_RSC_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_RES_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_SUS_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_UBA_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_UCIC_SENT_TO_REMOTE:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CRM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break; 

        case PEG_ISUP_CRA_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CVR_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CVT_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_EXM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break; 

        case PEG_ISUP_FAC_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d [ANSI-95 Specific]",
                        ISUP_Msg_Pegs_Sent_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        
        }
    }
}
/*.implementation:
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
DBCPrintMsgSentPegs(ISUP_CFG_PEGS *SentPegs,int noEnt,DBC_Server *dbc)
 
{

    int i =0;
    ITS_UINT value;
    char buf[ITS_PATH_MAX];
    sprintf(buf,"\n     Peg Name                             Peg Count \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                             --------\n");
    DBC_AppendText(dbc, buf); 
   
    for (i = 0; i < noEnt - 1; i++)
    {
        value = SentPegs[i].pegVal;
        switch (i)
        {
        case PEG_ISUP_IAM_SENT_TO_REMOTE:
            sprintf(buf,"\n%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_ACM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_ANM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REL_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_RLC_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_BLO_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_UBL_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_BLA_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CPG_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CGB_SENT_TO_REMOTE :
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CGBA_SENT_TO_REMOTE:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CQM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CQR_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_GRS_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_GRA_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CGU_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CGUA_SENT_TO_REMOTE:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CRG_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CFN_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_COT_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CCR_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_FOT_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_INF_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_INR_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_LPA_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_PAM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_RSC_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_RES_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_SUS_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_UBA_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_UCIC_SENT_TO_REMOTE:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CRM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CRA_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CVR_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_CVT_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_EXM_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_FAC_SENT_TO_REMOTE:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break; 

        }
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
DBCPrintMsgRcvdPegsType(DBC_Server *dbc)
{
    int i =0;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name                             Peg id \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                             ------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < ISUP_MAX_MSG_CODE; i++)
    {
        switch (i)
        {
        case PEG_ISUP_REMOTE_IAM_RCVD:
            sprintf(buf,"\n%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_ACM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_ANM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_REL_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_RLC_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_BLO_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UBL_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_BLA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CPG_RCVD :
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGB_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGBA_RCVD:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CQM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CQR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_GRS_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_GRA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGU_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGUA_RCVD:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
  
        case PEG_ISUP_REMOTE_CRG_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CFN_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_COT_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CCR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_FOT_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_INF_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_INR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_LPA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_PAM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_RSC_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_RES_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_SUS_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UBA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UCIC_RCVD:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CRM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CRA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CVR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CVT_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_EXM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_FAC_RCVD:
            sprintf(buf,"%s %18d [ANSI-95 Specific]\n",
                        ISUP_Msg_Pegs_Rcvd_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        
        }
    }
}
/*.implementation:
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
DBCPrintMsgRcvdPegs(ISUP_CFG_PEGS *RcvdPegs, int noEnt, DBC_Server *dbc)
{
    int i =0;
    char buf[ITS_PATH_MAX];
    ITS_UINT value;

    sprintf(buf,"\n     Peg Name                            Peg Count \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                            ----------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < noEnt - 1 ; i++)
    {
        value = RcvdPegs[i].pegVal;
        switch (i)
        {
        case PEG_ISUP_REMOTE_IAM_RCVD:
            sprintf(buf,"\n%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_ACM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_ANM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_REL_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_RLC_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_BLO_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UBL_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_BLA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CPG_RCVD :
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGB_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGBA_RCVD:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CQM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CQR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_GRS_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_GRA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGU_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGUA_RCVD:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CRG_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CFN_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_COT_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CCR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_FOT_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_INF_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_INR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_LPA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_PAM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_RSC_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_RES_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_SUS_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UBA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UCIC_RCVD:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CRM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CRA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CVR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CVT_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_EXM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_FAC_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        }
    }
}

/*.implementation:
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
DBCPrintCicPegsType(DBC_Server *dbc)
{
    int i =0;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name                       Peg id \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                       ------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
    {
        switch (i)
        {
        case    PEG_ISUP_CIC_NO_RLC_T5:
            sprintf(buf,"\n%s %18d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_REL_ABNORMAL:
            sprintf(buf,"%s %15d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_MISSING_ACK_IN_CGBA:
            sprintf(buf,"%s %8d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_MISSING_ACK_IN_CGUA:
            sprintf(buf,"%s %8d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGBA:
            sprintf(buf,"%s %7d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGUA:
            sprintf(buf,"%s %7d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_UNEXP_CGBA_ABNORMAL_ACK:
            sprintf(buf,"%s %4d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK:
            sprintf(buf,"%s %4d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_UNEXP_BLA_ABNORMAL_ACK :
            sprintf(buf,"%s %5d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_UNEXP_UBA_ABNORMAL_ACK:
            sprintf(buf,"%s %5d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_NO_BLA_T13:
            sprintf(buf,"%s %17d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_NO_UBA_T15:
            sprintf(buf,"%s %17d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_NO_CGBA_T19:
            sprintf(buf,"%s %16d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_NO_CGUA_T21:
            sprintf(buf,"%s %16d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_MSG_FORMAT_ERR:
            sprintf(buf,"%s %13d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;

        case    PEG_ISUP_CIC_UNEXP_MSG_RCVD:
            sprintf(buf,"%s %13d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
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
ISUP_Console_ANSI(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    ITS_UINT i;
    int ret =0;

    if (dbc == NULL)
    {
        ISUP_ERROR(("ISUP_Console_ANSI:: dbc == NULL"));
        return;
    }

    if (DBC_Cmd(dbc, "ia_get_gen_cfg", "ISUP Get General Config", "", ""))
    {
        ISUPGeneralCfg *cfg = 0;
        cfg =  ISUP_GetGeneralCfg_ANSI();
        sprintf(buf, "\n*********** ISUP General Config *************\n");
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
        strcpy(buf, "\n    ISUP Trace: \n");
        DBC_AppendText(dbc, buf);

        if ( cfg->traceOn)
        {
            if (TRACE_IsLevelOn(ISUP_ANSI_TraceData,
                                    ISUP_TRACE_DEBUG))
            {
                strcpy(buf, "        Debug     = ");
                if(TRACE_IsOutputOn(ISUP_ANSI_TraceData,
                                       ISUP_TRACE_DEBUG,
                                       0))
                {
                     strcat(buf, " stdout");
                }
                if(TRACE_IsOutputOn(ISUP_ANSI_TraceData,
                                       ISUP_TRACE_DEBUG,
                                       1))
                {
                     strcat(buf, " file");
                }
            }
            else
            {
                strcpy(buf, "        Debug     =  null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(ISUP_ANSI_TraceData,
                                     ISUP_TRACE_CRITICAL))
            {
                strcpy(buf, "        Critical  = ");
                if(TRACE_IsOutputOn(ISUP_ANSI_TraceData,
                                      ISUP_TRACE_CRITICAL,
                                      0))
                {
                     strcat(buf, " stdout");
                }
                if(TRACE_IsOutputOn(ISUP_ANSI_TraceData,
                                      ISUP_TRACE_CRITICAL,
                                      1))
                {
                     strcat(buf, " file");
                }
            }
            else
            {
                strcpy(buf, "        Critical  =  null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(ISUP_ANSI_TraceData,
                                    ISUP_TRACE_WARNING))
            {
                strcpy(buf, "        Warning   = ");
                if(TRACE_IsOutputOn(ISUP_ANSI_TraceData,
                                      ISUP_TRACE_WARNING,
                                      0))
                {
                     strcat(buf, " stdout");
                }
                if(TRACE_IsOutputOn(ISUP_ANSI_TraceData,
                                       ISUP_TRACE_WARNING,
                                       1))
                {
                     strcat(buf, " file");
                }
            }
            else
            {
                strcpy(buf, "        Warning   =  null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(ISUP_ANSI_TraceData,
                                   ISUP_TRACE_ERROR))
            {
                strcpy(buf, "        Error     = ");
                if(TRACE_IsOutputOn(ISUP_ANSI_TraceData,
                                      ISUP_TRACE_ERROR,
                                      0))
                {
                     strcat(buf, " stdout");
                }
                if(TRACE_IsOutputOn(ISUP_ANSI_TraceData,
                                      ISUP_TRACE_ERROR,
                                      1))
                {
                     strcat(buf, " file");
                }
            }
            else
            {
                strcpy(buf, "        Error     =  null");
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

        sprintf(buf, "\n*********** End of ISUP General Config ***********\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "ia_set_gen_cfg", "ISUP Set General Config",
                      "<alarmLevel> <traceType> <traceOutput> <On/Off>", ""))
    {
        ISUPGeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType,
                     traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ia_set_gen_cfg <alarmlevel> <tracetype>"
                         " <trOutput> <On/Off>\n"
                          "See help for possible values\n");
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
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, ISUP_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, ISUP_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, ISUP_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, ISUP_ERROR_STRING);
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
            strcpy(cfg.traceOutput, ISUP_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, ISUP_FILE_STRING);
        }
        else
        {
            sprintf(buf, "\nInvalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  ISUP_SetGeneralCfg_ANSI(&cfg);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "\n*********ISUP Set Gen Cfg Failed**********\n");
            DBC_AppendText(dbc, buf);
            return;
        }
       sprintf(buf, "\n********** ISUP General Config Set Successful*******\n");
       DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "ia_get_dest_info", "ISUP Get Destination Info",
                      "<opc> <dpc> <sio> or  <*>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char astrix[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret != 4)
        {
            if (ret == 2)
            {
                sscanf(cmdLine," %s %s",buf,astrix);
                if (strcmp(astrix,"*") == 0)
                {
                    ISUP_HashTableIterate(ISUP_DestIterProc_ANSI,(void*)dbc,NULL);
                }
                else
                {
                    sprintf(buf, "\n**** Invalid Command Arguments *******\n");
                    DBC_AppendText(dbc, buf);
                    return;
                }
            }
            else
            {
                sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                        "Usage: ia_get_dest_info <opc> <dpc> <sio> or  <*>");
                DBC_AppendText(dbc, buf);
                return;
            }
        }
        else
        {
            ISUP_CFG_KEY cfg;
            ISUP_CFG_DEST_INFO dest_info;

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_GetDestCfgInfo_ANSI(cfg, &dest_info);
            if (ret == ITS_SUCCESS)
            {
                DBCPrintDestCfgInfo(&dest_info, dbc);
                
            }
            else if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d) ",atoi(opc),atoi(dpc),atoi(sio)); 
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf,"\n*** ia_get_dest_info Error...  check arguments\n");
                DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ia_add_dest_info", "ISUP Add Destination Info",
             "<opc> <dpc> <sio> <VariantType> <ExchangeType>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char varName[ITS_PATH_MAX];
        char exchangeType[ITS_PATH_MAX];
        ISUP_CFG_KEY cfg;

        ret = sscanf(cmdLine, "%s %s %s %s %s %s", buf, opc, dpc, sio, varName, 
                     exchangeType);
        if (ret != 6)
        {
            sprintf(buf,"\n*** Add Destination Falied: "
                        "\nUsage: ia_add_dest_info <opc> <dpc> <sio>"
                        " <variant type>  <exchange type>");
            DBC_AppendText(dbc, buf);
        }
        else
        {
            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_AddDestCfgInfo_ANSI(cfg, varName, exchangeType);
            if (ret == ITS_SUCCESS)
            {
                sprintf(buf,"\n *** Added Destination Successfully ***\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOROUTE)
            {
                sprintf(buf,"\n Route Not Found For Destination : "
                              "See help To Add Route First\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_EINVXCHANGE)
            {
                sprintf(buf,"\n Exchange Type is Invalid: "
                              "See help To see Valid Exchange Types\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOFEATURE)
            {
                sprintf(buf,"\n Variant Feature: %s is Not Loaded: "
                            "Try to add Variant first (ia_add_variant)\n",
                             varName);
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_EINUSE)
            {
                sprintf(buf,"\nAdd Destination Failed: Destinatoin Already "
                            "Configured\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOTFOUND)
            {
                sprintf(buf,"Add Destination Failed: %s Variant Not Supported", 
                            varName);
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf,"\n*** Add Destination Falied: ,See help"
                            "\nUsage: ia_add_dest_info <opc> <dpc> <sio>"
                            " <variant type>  <exchange type>\n");
                DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ia_add_variant", "ISUP Add Variant Feature ",
             "<Variant Name>",""))
    {
        char varName[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s", buf, varName);
        if (ret != 2)
        {
            sprintf(buf,"\n *** Add Variant failed ,check the parameters: "
                    "\nUsage: ia_add_variant  <Variant Type>\n");
            DBC_AppendText(dbc, buf);
        }
        else
        {
            ret = ISUP_AddVariantFeature_ANSI(varName);
            if (ret == ITS_SUCCESS)
            {
                sprintf(buf,"\n Variant Successfully Added\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOFEATURE)
            {
                sprintf(buf,"\n Invalid Variant Type: %s (or) Not supported\n",
                        varName);
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_EINVVARIANT)
            {
                sprintf(buf,"\nAdd Variant Failed: %s Invalid Variant Entered\n ",
                            varName);
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_EINUSE)
            {
                sprintf(buf,"\nAdd Variant Failed: Variant Already Exists\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOTFOUND)
            {
                sprintf(buf,"\nAdd Variant Failed: Required varaint library"
                            " not found in the LD path\n");
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf,"\n *** Add Variant Failed ,check the parameters: "
                            "\nUsage: ia_add_dest_info  <Variant Type>");
                DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ia_get_timers", 
                          "ISUP Get Timer Info",
                          "<opc> <dpc> <sio> [<Tid> (or) <*>]",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char tId[ITS_PATH_MAX];
        ITS_INT timeId;

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, opc, dpc, sio, tId);
        if (ret == 5)
        {
            ISUP_CFG_KEY cfg;
            ISUP_CFG_TMR_INFO tmr_info[ISUP_CFG_MAX_TIMERS];

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            if (strcmp(tId,"*") == 0)
            {
                ret = ISUP_GetAllTimerCfgInfo_ANSI(cfg, tmr_info);

                if (ret == ITS_SUCCESS)
                {
                    DBCPrintTimerCfg(tmr_info, NULL, dbc);
                }
                else if (ret == ITS_ENOTCONFIG)
                {
                    sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                           " SIO (%d)\n",atoi(opc),atoi(dpc),atoi(sio));
                    DBC_AppendText(dbc, buf);
                }
            }
            else
            {
                timeId = atoi(tId);
                ret = ISUP_GetAllTimerCfgInfo_ANSI(cfg, tmr_info);
                if (ret == ITS_SUCCESS)
                {
                    DBCPrintTimerCfg(tmr_info, &timeId, dbc);
                }
                else if (ret == ITS_ENOTCONFIG)
                {
                    sprintf(buf,"\n*** Could not find config OPC (%d)  DPC (%d)"
                           " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
                    DBC_AppendText(dbc, buf);
                }
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                  "Usage: ia_get_timers <opc> <dpc> <sio> [<Tid> (or) <*>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

    }
    else if (DBC_Cmd(dbc, "ia_set_timers",
                          "ISUP Set Timer Info",
                          "<opc> <dpc> <sio> <Tid> <TimerVal> <HandledBy>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char tId[ITS_PATH_MAX];
        char tVal[ITS_PATH_MAX];
        char tHand[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s %s %s", buf, opc, dpc, sio,
                     tId,tVal,tHand);
        if (ret == 7)
        {
            MTP3_HEADER opc_dpc_ni;
            ISUP_OPC_DPC_STAT *config_stat = NULL;
            ISUP_TMR_HNDL_INFO tmr_info;

            memset(&opc_dpc_ni, 0, sizeof(opc_dpc_ni));
            MTP3_RL_SET_OPC_VALUE_ANSI(opc_dpc_ni.label,atoi(opc));
            MTP3_RL_SET_DPC_VALUE_ANSI(opc_dpc_ni.label,atoi(dpc));
            MTP3_HDR_SET_SIO_ANSI(opc_dpc_ni,atoi(sio));

            if ((strcmp(tHand, "STACK") == 0) || (strcmp(tHand, "APP") == 0))
            {
            }
            else
            {
                sprintf(buf, "\n *** Invalid Handle argument  Valid are:"
                             " STACK  or APP\n");
                DBC_AppendText(dbc, buf);
                return;
            }

            /* First look for config info for this opc-dpc */
            config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni);
            if (config_stat == NULL)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
                return;
            }

            if (atoi(tId) > ISUP_CFG_MAX_TIMERS)
            {
                sprintf(buf, "\n**** Invalid Timer Id *******\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            else
            {
                switch(atoi(tId))
                {
                    case ITS_ISUP_TIMER_T2:
                    case ITS_ISUP_TIMER_T3:
                    case ITS_ISUP_TIMER_T4:
                    case ITS_ISUP_TIMER_T10:
                    case ITS_ISUP_TIMER_T29:
                    case ITS_ISUP_TIMER_T30:
                    case ITS_ISUP_TIMER_T35:

                    sprintf(buf,"\nUnspecifeid Timer %d for US Networks\n",
                            atoi(tId));
                    DBC_AppendText(dbc, buf);
                    return;
                }
            }

            tmr_info = config_stat->tmr_hndl_info[atoi(tId)];
            tmr_info.tmr_value = atoi(tVal);
            tmr_info.tmr_hndl_layer = ISUP_StringToTimerHandler(tHand);

            config_stat->tmr_hndl_info[atoi(tId)] = tmr_info;

            sprintf(buf, "\n**** ISUP Set Timer Successful********\n");
            DBC_AppendText(dbc, buf);

            ISUP_ReleaseOpcDpcStat(config_stat);
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ia_set_timers <opc> <dpc> <sio>"
                         " <Tid> <TimerVal> <HandledBy>\n");
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_get_cics",
                          "ISUP Get Circuit Info",
                          "<opc> <dpc> <sio>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret == 4)
        {
            ISUP_CFG_KEY cfg;
            ISUP_CFG_CKGP_INFO * info;
            int noEnt;

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_GetAllCicsCfg_ANSI(cfg, &info, &noEnt);
            if (ret == ITS_SUCCESS)
            {
                DBCPrintAllCicsCfg(info, noEnt, dbc);
                free(info);
            }
            else if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ia_get_cics  <dpc> <opc> <sio>\n");
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_add_cics",
                          "ISUP Add Circuit Info",
                          "<opc> <dpc> <sio> <startCic> <count> <control>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char startCic[ITS_PATH_MAX];
        char count[ITS_PATH_MAX];
        char contl[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s %s %s", buf, opc, dpc,
                     sio, startCic, count,contl);
        if (ret == 7)
        {
            ISUP_CFG_KEY cfg;

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);


            switch(ISUP_StringToCkgpCtrl(contl))
            {
                case ISUP_CFG_CKGP_CTRL_NONE:
                case ISUP_CFG_CKGP_CTRL_EVEN:
                case ISUP_CFG_CKGP_CTRL_ODD:
                case ISUP_CFG_CKGP_CTRL_ALL:
                case ISUP_CFG_CKGP_CTRL_DEF:
                    break;
                default:
                    sprintf(buf,"\nCic Rule is Invalid try again "
                                 "Possile Values are NONE, ALL, ODD, "
                                 "EVEN, DEF \n");
                    DBC_AppendText(dbc, buf);
                    return;
            }

            ret =ISUP_AddCicsCfg_ANSI(cfg, (ITS_USHORT)atoi(startCic),
                              (ITS_USHORT)atoi(count),
                              ISUP_StringToCkgpCtrl(contl));
            if (ret == ITS_SUCCESS)
            {
                sprintf(buf,"\nSuccessfully added Cic(s)\n");
            }
            else if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
            }
            else
            {
                sprintf(buf,"\nInvalid range of Cics or Invalid argumetns\n");
            }
            DBC_AppendText(dbc, buf);
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ia_add_cics  <opc> <dpc> <sio> "
                         "<startCic> <count> <control>");
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_del_cics",
                          "ISUP Del Circuit Info",
                          "<opc> <dpc> <sio> <startCic> <count>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char startCic[ITS_PATH_MAX];
        char count[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s %s ", buf, opc, dpc,
                     sio, startCic, count);
        if (ret == 6)
        {
            int ret;
            ISUP_CFG_KEY cfg;

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_DelCicsCfg_ANSI(cfg,
                                  (ITS_USHORT)atoi(startCic),
                                  (ITS_USHORT)atoi(count));
            if (ret == ITS_SUCCESS)
            {
                sprintf(buf,"\n**** Successfully deleted Cics\n");
            }
            else if (ret == ITS_ECICBUSY)
            {
                sprintf(buf,"\n**** One or more Cics are BUSY ***\n");
            }
            else if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n",atoi(opc),atoi(dpc),atoi(sio));
            }
            else
            {
                sprintf(buf,"\n*** Invalid range of Cics entered\n");
            }

            DBC_AppendText(dbc, buf);
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "\nUsage: ia_del_cics  <opc> <dpc> <sio> "
                                             "<startCic> <count>\n");
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_get_cic_state",
                          "ISUP Get specified Circuit State ",
                          "<opc> <dpc> <sio> <cic> ",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char cic[ITS_PATH_MAX];

        ISUP_PCIC pcic;
        ISUP_CIC_INFO *cic_rec = NULL;

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, opc, dpc, sio, cic);
        if (ret == 5)
        {
            ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), atoi(cic));

            /* Get cic_rec using the pcic as key */
            cic_rec = ISUP_FindPcic(pcic);

            if (cic_rec == NULL)
            {
                sprintf(buf,"\nCic record not found for given cic %d. Check inputs\n", cic);
                DBC_AppendText(dbc, buf);
            }
            else
            {
                DBCPrintCicState(cic_rec, dbc);
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ia_get_cic_state  <opc> <dpc> <sio> <cic>\n");
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "ia_set_cic_state",
                          "ISUP Set specified Circuit State ",
                          "<opc> <dpc> <sio> <cic> <state> ",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char cic[ITS_PATH_MAX];
        ITS_UINT state;

        ret = sscanf(cmdLine, "%s %s %s %s %s %d", buf, opc, dpc, sio, cic, &state);
        if (ret == 6)
        {
            ISUP_CFG_KEY cfg;

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);
            ret = DBCVarifyCicState((ITS_OCTET)state, dbc);
            if (ret != ITS_SUCCESS)
            {
                sprintf(buf, "\nInvalid CiC state try again\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            ret = ISUP_SetCicStateInfo_ANSI(cfg, (ITS_USHORT)RESFILE_ParseNum(cic),
                                            (ITS_OCTET)state);
            if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\nCic record not found for given cic %d.\n",atoi(cic));
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ia_set_cic_state <opc> <dpc> <sio> <cic> <state>\n");
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "ia_get_gen_pegs", "ISUP Get Genaral Pegs"," "," "))
    {
        char pgName[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        DBCPrintGeneralPegs(dbc);
    }
    else if (DBC_Cmd(dbc, "ia_get_gen_pegid", "ISUP Get General Peg Id"," ", " "))
    {
        char pgName[ITS_PATH_MAX];
        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        DBCPrintGeneralPegType(dbc);
    }

    else if (DBC_Cmd(dbc, "ia_get_msg_sent_pegid",
                         "ISUP Get Message Sent peg Id"," ", " "))
    {
        char pgName[ITS_PATH_MAX];
        ret = sscanf(cmdLine, "%s %s", buf, pgName);

        DBCPrintMsgSentPegsType(dbc);
    }

    else if (DBC_Cmd(dbc, "ia_get_msg_sent_pegs",
                        "ISUP Get Message Sent pegs","<opc> <dpc> <sio>",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        int noEnt;

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                       "Usage: ia_get_msg_sent_pegs <opc> <dpc> <sio> \n");
            DBC_AppendText(dbc, buf);
            return;
        }
 
        else
        {
            ISUP_CFG_KEY cfg;
            ISUP_CFG_PEGS SentPegs[ISUP_MAX_MSG_CODE];
            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_GetMsgSentPegs_ANSI(cfg,SentPegs,&noEnt);

            if (ret == ITS_SUCCESS)
            {
                DBCPrintMsgSentPegs(SentPegs,noEnt,dbc);
            }
            else if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                           " SIO (%d) ",atoi(opc),atoi(dpc),atoi(sio)); 
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf,"\n ia_get_msg_sent_pegs Error:check arguments\n");
                DBC_AppendText(dbc, buf);
            }
        }
    }

    else if (DBC_Cmd(dbc, "ia_get_msg_rcvd_pegs",
                      "ISUP Get Received Message pegs","<opc> <dpc> <sio>",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        int noEnt;

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments ****\n"
                        "Usage: ia_get_msg_rcvd_pegs <opc> <dpc> <sio> \n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            ISUP_CFG_KEY cfg;
            ISUP_CFG_PEGS  RcvdPegs[ISUP_MAX_MSG_CODE];

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);
            ret = ISUP_GetMsgRcvdPegs_ANSI(cfg, RcvdPegs, &noEnt);

            if( ret == ITS_SUCCESS)
            {
                DBCPrintMsgRcvdPegs(RcvdPegs, noEnt, dbc);  
                
            }
            else if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                             " SIO (%d) ",atoi(opc),atoi(dpc),atoi(sio)); 
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf,"\n ia_get_msg_rcvd_pegs Error.Check Arguments\n");
                DBC_AppendText(dbc, buf);
            }
        }
    }

    else if (DBC_Cmd(dbc, "ia_get_msg_rcvd_pegid",
                         "ISUP Get Received Message peg Id"," ", " "))
    {
        char pgName[ITS_PATH_MAX];
        ret = sscanf(cmdLine, "%s %s", buf, pgName);

        DBCPrintMsgRcvdPegsType(dbc);
    }

    else if (DBC_Cmd(dbc, "ia_get_cic_pegs", "ISUP Get CIC Pegs",
                                            "<opc> <dpc> <sio> <cic>",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_CFG_KEY cfg;
        ISUP_CFG_PEGS cicPegs[PEG_ISUP_CIC_NUM_PEGS];

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret != 5)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                    "Usage: ia_get_cic_pegs <opc> <dpc> <sio> <cic>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

       cfg.opc = atoi(opc);
       cfg.dpc = atoi(dpc);
       cfg.sio = atoi(sio);

        ret = ISUP_GetCicPegs_ANSI(cfg, (ITS_USHORT)cic, cicPegs);

       if (ret == ITS_SUCCESS)
       {
            DBCPrintCicPegs(cicPegs, dbc);
       }

        else if (ret == ITS_ENOTCONFIG)
        {
            sprintf(buf, "\n**** Cic record not found ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }
    }

    else if (DBC_Cmd(dbc, "ia_get_cic_pegid", "ISUP Get CIC Pegs Id"," ", " "))
    {
        char pgName[ITS_PATH_MAX];
        ret = sscanf(cmdLine, "%s %s", buf, pgName);

        DBCPrintCicPegsType(dbc);
    }

    else if (DBC_Cmd(dbc, "ia_clr_gen_pegs", "ISUP Reset a perticular gen Peg",
                          "[<PegType> (or) <All/all>]",""))
    {
        char buf[ITS_PATH_MAX];
        char pegType[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s", buf, pegType);

        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ia_clr_gen_pegs [<PegType> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strncmp(pegType, "All", 3) == 0 ||
           strncmp(pegType, "all", 3) == 0)
        {
           for (i = 0; i < PEG_ISUP_NUM_PEGS; i++)
           {
               PEG_ClearPeg(ANSI_ISUP_Pegs, i);
           }

           sprintf(buf, "\n** Cleared all ISUP gen pegs **\n");
           DBC_AppendText(dbc, buf);
           return;
         }
         else
         {
            if (!isdigit((int)pegType[0]))
            {
               sprintf(buf, "\n**** Unrecognized Peg *****\n");
               DBC_AppendText(dbc, buf);
               return;
            }
         }

         if ( atoi(pegType) > PEG_ISUP_NUM_PEGS - 1)
         {
             sprintf(buf, "\n** ISUP general peg %d does not exist **\n", atoi(pegType));
             DBC_AppendText(dbc, buf);
             return;
         }

         for (i = 0; i < PEG_ISUP_NUM_PEGS; i++)
         {
             if (i == (ITS_UINT)RESFILE_ParseNum(pegType))
             {
                 PEG_ClearPeg(ANSI_ISUP_Pegs, i);
                 sprintf(buf, "\n** Cleared ISUP general peg type %d **\n", i);
                 DBC_AppendText(dbc, buf);
                 break;
             }
         }
    }

    else if (DBC_Cmd(dbc, "ia_clr_msg_sent_pegs","ISUP Reset Message "
                      "sent Pegs","<opc> <dpc> <sio> [<PegId> (or) <All/all>]",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char buf[ITS_PATH_MAX];
        char pegId[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, opc, dpc, sio, pegId);

        if (ret != 5)
        {
            sprintf(buf, "\n*** Invalid Command Arguments ***\n"
                         "Usage: ia_clr_msg_sent_pegs <opc> <dpc> <sio> [<PegId> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            ITS_OCTET i;
            ISUP_CFG_KEY cfg;
            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            if (strncmp(pegId, "All", 3) == 0 || strncmp(pegId, "all", 3) == 0)
            {
                ret = ISUP_ClearAllMsgSentPegs_ANSI(cfg);
                if (ret == ITS_SUCCESS)
                {
                    sprintf(buf, "\n** Cleared all ISUP Message pegs **\n");
                    DBC_AppendText(dbc, buf);
                }
                else if (ret == ITS_ENOTCONFIG)
                {
                    sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                            " SIO (%d) \n",atoi(opc), atoi(dpc), atoi(sio));
                    DBC_AppendText(dbc, buf);
                }
                return;
            }

            if (!isdigit((int)pegId[0]))
            {
               sprintf(buf, "\n**** Unrecognized Message Peg *****\n");
               DBC_AppendText(dbc, buf);
               return;
            }

            if ( atoi(pegId) > ISUP_MAX_MSG_CODE - 1)
            {
                sprintf(buf, "\n** ISUP Message peg %d does not exist **\n",
                                                                atoi(pegId));
                DBC_AppendText(dbc, buf);
                return;
            }

            i = (ITS_OCTET)RESFILE_ParseNum(pegId);

            ret = ISUP_ClearMsgSentPeg_ANSI(cfg, i);
            if(ret == ITS_SUCCESS)
            {
               sprintf(buf, "\n** ISUP Message peg  %d Reseted **\n", i);
               DBC_AppendText(dbc, buf);
            }
            else
            {
               sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n",atoi(opc),atoi(dpc),atoi(sio));
               DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ia_clr_msg_rcvd_pegs", "ISUP Reset Message "
                       "Received Pegs","<opc> <dpc> <sio> [<PegId> (or) <All/all>]",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char buf[ITS_PATH_MAX];
        char pegId[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, opc, dpc, sio, pegId);

        if (ret != 5)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ia_clr_msg_rcvd_pegs <opc> <dpc> <sio> [<PegId> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            ITS_OCTET i;
            ISUP_CFG_KEY cfg;
            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            if (strncmp(pegId, "All", 3) == 0 || strncmp(pegId, "all", 3) == 0)
            {
                ret = ISUP_ClearAllMsgRcvdPegs_ANSI(cfg);
                if (ret == ITS_SUCCESS)
                {
                    sprintf(buf, "\n** Cleared all ISUP Message pegs **\n");
                    DBC_AppendText(dbc, buf);
                }
                else if (ret == ITS_ENOTCONFIG)
                {
                    sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                            " SIO (%d)\n",atoi(opc), atoi(dpc), atoi(sio));
                    DBC_AppendText(dbc, buf);
                }
                return;
            }

            if (!isdigit((int)pegId[0]))
            {
               sprintf(buf, "\n**** Unrecognized Message Peg *****\n");
               DBC_AppendText(dbc, buf);
               return;
            }

            if ( atoi(pegId) > ISUP_MAX_MSG_CODE - 1)
            {
                sprintf(buf, "\n** ISUP Message peg %d does not exist **\n",
                                                                atoi(pegId));
                DBC_AppendText(dbc, buf);
                return;
            }

            i = (ITS_OCTET)RESFILE_ParseNum(pegId);

            ret = ISUP_ClearMsgRcvdPeg_ANSI(cfg, i);
            if(ret == ITS_SUCCESS)
            {
               sprintf(buf, "\n** ISUP Message peg  %d Reseted **\n", i);
               DBC_AppendText(dbc, buf);
            }
            else
            {
               sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n",atoi(opc),atoi(dpc),atoi(sio));
               DBC_AppendText(dbc, buf);
            }
        }
    }

    else if (DBC_Cmd(dbc, "ia_clr_cic_pegs", "ISUP Clear perticular Cic Peg",
                     "<opc> <dpc> <sio> <cic> [<PegType> (or) <All/all>]", ""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_PCIC pcic;
        char pegType[ITS_PATH_MAX];
        ISUP_CIC_INFO *cic_rec = NULL;

        ret = sscanf(cmdLine, "%s %s %s %s %d %s", buf, opc, dpc, sio, &cic, pegType);
        if (ret != 6)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
            "Usage: ia_clr_cic_pegs <opc> <dpc> <sio> <cic> [<PegType> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ( atoi(pegType) > PEG_ISUP_CIC_NUM_PEGS - 1)
        {
            sprintf(buf, "\n** ISUP CIC peg %d does not exist **\n", atoi(pegType));
            DBC_AppendText(dbc, buf);
            return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        /* Get cic_rec using the pcic as key */
        cic_rec = ISUP_FindPcic( pcic);
        if (cic_rec == NULL)
        {
            sprintf(buf, "\n**** Cic record not found ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strncmp(pegType, "All", 3) == 0 ||
           strncmp(pegType, "all", 3) == 0)
        {
           for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
           {
               PEG_ClearPeg(&cic_rec->ISUP_CIC_PEGS, i);
           }

           sprintf (buf, "\n** Cleared all cic pegs for CIC %d **\n", cic);
           DBC_AppendText(dbc, buf);
           ISUP_ReleaseCic(cic_rec);
           return;
         }
         else
         {
            if (!isdigit((int)pegType[0]))
            {
               sprintf(buf, "\n**** Unrecognized Peg *****\n");
               DBC_AppendText(dbc, buf);
               ISUP_ReleaseCic(cic_rec);
               return;
            }
         }

        for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
        {
            if ((ITS_UINT)RESFILE_ParseNum(pegType) == i)
            {
               PEG_ClearPeg(&cic_rec->ISUP_CIC_PEGS, i);
               sprintf(buf, "\n** Cleared peg type %d for CIC %d **\n", i, cic);
               DBC_AppendText(dbc, buf);
               break;
            }
        }
        ISUP_ReleaseCic(cic_rec);
    }
    else if (DBC_Cmd(dbc, "ia_get_cong_lev", "ISUP Get Congestion Level",
                       "<congLevel> ",""))
    {
        char congLevel[ITS_PATH_MAX];
        int congLev;

        ret = sscanf(cmdLine, "%s %s", buf, congLevel);

        congLev = atoi(congLevel);

        if (ret == 2)
        {
            if (congLev == 1 || congLev == 2)
            {
               ISUP_PrintCong_ANSI(congLev, dbc);
            }
            else
            {
                sprintf(buf, "\nInvalid congLevel value. Valid values: 1 or 2\n");
                DBC_AppendText(dbc, buf);
                return;
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
           "Usage: ia_get_cong_lev <congLevel: 1 or 2>\n");
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "ia_set_cong_lev", "ISUP Set Congestion Level",
                       "<congLevel> <congValue>",""))
    {
        char congLevel[ITS_PATH_MAX];
        char congValue[ITS_PATH_MAX];
        int congLev, congVal, ret; 
        int retVal=0;

        ret = sscanf(cmdLine, "%s %s %s", buf, congLevel, congValue);

        congLev = atoi(congLevel);
        congVal = atoi(congValue);

        if (ret == 3)
        {
            if (congLev == 1 || congLev == 2)
            {
                retVal = ISUP_SetCong_ANSI(congLev, congVal);

                if (retVal == ITS_SUCCESS)
                {
                    sprintf(buf, "\n*** Successfully Set Cong Level ***\n");
                    DBC_AppendText(dbc, buf);
                }
                else
                {
                    sprintf(buf, "\n *** New Cong Level NOT set ***\n");
                    DBC_AppendText(dbc, buf);
                }
            }
            else
            {
                sprintf(buf, "\nInvalid congLevel value. Valid values: 1 or 2\n");
                DBC_AppendText(dbc, buf);
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
           "Usage: ia_set_cong_lev <congLevel> <congValue>\n");
            DBC_AppendText(dbc, buf);
        }
        return;
    }
    else if (DBC_Cmd(dbc, "ia_get_xchange_type", "ISUP Get Local Exchange Type",
                          "<opc> <dpc> <sio>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char astrix[ITS_PATH_MAX];

        MTP3_HEADER opc_dpc_ni;
        ISUP_OPC_DPC_STAT *config_stat = NULL;

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret != 4)
        {
            if (ret == 2)
            {
                sscanf(cmdLine," %s %s",buf,astrix);
                if (strcmp(astrix,"*") == 0)
                {
                }
                else
                {
                    sprintf(buf, "\n**** Invalid Command Arguments *******\n");
                    DBC_AppendText(dbc, buf);
                    return;
                }
            }
            else
            {
                sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                        "Usage: ia_get_xchange_type <opc> <dpc> <sio>\n");
                DBC_AppendText(dbc, buf);
                return;
            }
        }
        else
        {
            MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,atoi(opc));
            MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,atoi(dpc));
            MTP3_HDR_SET_SIO(opc_dpc_ni,atoi(sio));

            /* First look for config info for this opc-dpc */
            config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni);
            if (config_stat == NULL)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
                return;
            }
            else
            {
                /* Print Exchange Type from config info */
                if (config_stat->exchange_type == 0)
                {
                    sprintf(buf,"\n ** Local ExchangeType: TYPE_A \n");
                    DBC_AppendText(dbc, buf);
                }
                else if (config_stat->exchange_type == 1)
                {
                    sprintf(buf,"\n ** Local ExchangeType: TYPE_B \n");
                    DBC_AppendText(dbc, buf);
                }
                else
                {
                    sprintf(buf,"\n ** Local ExchangeType: INVALID \n");
                    DBC_AppendText(dbc, buf);
                }
            }
        }
        ISUP_ReleaseOpcDpcStat(config_stat);
    }
    else if (DBC_Cmd(dbc, "ia_set_xchange_type", "ISUP Set Local Exchange Type",
                          "<opc> <dpc> <sio> <xchangeType> ",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char xchangeType[ITS_PATH_MAX];
        MTP3_HEADER opc_dpc_ni;
        ISUP_OPC_DPC_STAT *config_stat = NULL;

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, opc, dpc, sio,
                                                      xchangeType);
        if (ret != 5)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                    "Usage: ia_set_xchange_type <opc> <dpc> <sio> <xchangeType>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((strcmp(xchangeType, "TYPE_A") == 0) ||
                               (strcmp(xchangeType, "TYPE_B") == 0))
        {
        }
        else
        {
            sprintf(buf, "\n *** Invalid xchangeType argument.  Valid are:"
                         " TYPE_A  or TYPE_B ");
            DBC_AppendText(dbc, buf);
            return;
        }
        MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,atoi(opc));
        MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,atoi(dpc));
        MTP3_HDR_SET_SIO(opc_dpc_ni,atoi(sio));

        /* First look for config info for this opc-dpc */
        config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni);
        if (config_stat == NULL)
        {
            sprintf(buf," *** Could not find config OPC (%d)  DPC (%d)"
                    " SIO (%d) ",atoi(opc),atoi(dpc),atoi(sio));
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            config_stat->exchange_type =  ISUP_StringToXchangeType(xchangeType);
            sprintf(buf,"\n ****** Set Exchange Type Successful *******\n");
            DBC_AppendText(dbc, buf);
        }
        ISUP_SyncOpcDpcInfoWithStat(config_stat);
        ISUP_ReleaseOpcDpcStat(config_stat);
    }

    /*
     * MML CSC Commands Start right here
     */

    else if (DBC_Cmd(dbc, "ia_send_ubl", "ISUP Send Unblocking Msg",
                          "<opc> <dpc> <sio> <cic>",""))
    {
        int          ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret != 5)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ia_send_ubl <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ret = ISUP_SendMsgMMLToStack_ANSI(pcic, ISUP_MSG_UBL, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent the msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ia_send_ubl <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ia_send_ubl <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send msg *******\n"
                          "Usage: ia_send_ubl <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_send_rsc", "ISUP Send Reset circuit Msg",
                          "<opc> <dpc> <sio> <cic>",""))
    {
        int          ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret != 5)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ia_send_rsc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ret = ISUP_SendMsgMMLToStack_ANSI(pcic, ISUP_MSG_RSC, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent the msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ia_send_rsc <opc> <dpc> <sio> <cic>");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ia_send_rsc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send msg *******\n"
                          "Usage: ia_send_rsc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_send_rlc", "ISUP Send Release confirmation Msg",
                          "<opc> <dpc> <sio> <cic>",""))
    {
        int          ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret != 5)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ia_send_rlc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ret = ISUP_SendMsgMMLToStack_ANSI(pcic, ISUP_MSG_RLC, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent the msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ia_send_rlc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ia_send_rlc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send msg *******\n"
                          "Usage: ia_send_rlc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_send_blo", "ISUP Send Blocking Msg",
                          "<opc> <dpc> <sio> <cic>",""))
    {
        int          ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret != 5)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ia_send_blo <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ret = ISUP_SendMsgMMLToStack_ANSI(pcic, ISUP_MSG_BLO, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent the msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ia_send_blo <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ia_send_blo <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send msg *******\n"
                          "Usage: ia_send_blo <opc> <dpc> <sio> <cic>");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_send_cgb", "ISUP Send Circuit group reset Msg",
                          "<opc> <dpc> <sio> <cic> <msgType> "
                          "<range> <status> ",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic = 0;
        ITS_UINT msgType = 0;
        ITS_UINT range = 0;
        ITS_UINT status = 0;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d %d  %d  %d ", buf, opc, dpc, sio,
                               &cic, &msgType, &range, &status);
        if (ret != 8)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ia_send_cgb <opc> <dpc> <sio> <cic>"
                          "<msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));
        ies[0].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
        ies[0].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);
        ies[0].param_data.supervisionMsgType.sup_mt = msgType;

        ies[1].param_id = ISUP_PRM_RANGE_STATUS;
        ies[1].param_length = 4;
        ies[1].param_data.rangeAndStatus.range = (ITS_OCTET)range;
        ies[1].param_data.rangeAndStatus.status[0] = (ITS_OCTET)status;
        ies[1].param_data.rangeAndStatus.status[1] = (ITS_OCTET)(status >> 8);
        ies[1].param_data.rangeAndStatus.status[2] = (ITS_OCTET)(status >> 16);
        ieCount = 2;

        ret = ISUP_SendMsgMMLToStack_ANSI(pcic, ISUP_MSG_CGB, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent the msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ia_send_cgb <opc> <dpc> <sio> <cic>"
                          "<msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ia_send_cgb <opc> <dpc> <sio> <cic>"
                          "<msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send msg *******\n"
                          "Usage: ia_send_cgb <opc> <dpc> <sio> <cic>"
                          "<msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_send_cgu", "ISUP Send Circuit group unblocking Msg",
                          "<opc> <dpc> <sio> <cic> <msgType> "
                          "<range> <status> ",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic = 0;
        ITS_UINT msgType = 0;
        ITS_UINT range = 0;
        ITS_UINT status = 0;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d %d  %d  %d ", buf, opc, dpc, sio,
                               &cic, &msgType, &range, &status);
        if (ret != 8)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ia_send_cgu <opc> <dpc> <sio> <cic>"
                          " <msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));
        ies[0].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
        ies[0].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);
        ies[0].param_data.supervisionMsgType.sup_mt = msgType;

        ies[1].param_id = ISUP_PRM_RANGE_STATUS;
        ies[1].param_length = 4;
        ies[1].param_data.rangeAndStatus.range = (ITS_OCTET)range;
        ies[1].param_data.rangeAndStatus.status[0] = (ITS_OCTET)status;
        ies[1].param_data.rangeAndStatus.status[1] = (ITS_OCTET)(status >> 8);
        ies[1].param_data.rangeAndStatus.status[2] = (ITS_OCTET)(status >> 16);
        ieCount = 2;

        ret = ISUP_SendMsgMMLToStack_ANSI(pcic, ISUP_MSG_CGU, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent the msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ia_send_cgu <opc> <dpc> <sio> <cic>"
                          " <msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ia_send_cgu <opc> <dpc> <sio> <cic>"
                          " <msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send msg *******\n"
                          "Usage: ia_send_cgu <opc> <dpc> <sio> <cic>"
                          " <msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_send_grs", "ISUP Send Group reset Msg",
                          "<opc> <dpc> <sio> <cic> <range> "
                          "<msgType> <CicAsignMap> ",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic = 0;
        ITS_UINT range = 0;
        ITS_UINT mapType = 0;
        ITS_UINT cicMap = 0;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d %d %d %d", buf, opc, dpc, sio,
                               &cic, &range, &mapType, &cicMap);
        if (ret != 8)
        {
            if (ret != 7)
            {
                sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ia_send_grs <opc> <dpc> <sio> <cic>"
                          " <range> <mapTpye> <CicAsignMap>\n");
                DBC_AppendText(dbc, buf);
                return;
            }
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ies[0].param_id = ISUP_PRM_RANGE_STATUS;
        ies[0].param_length = 1;
        ies[0].param_data.rangeAndStatus.range = (ITS_OCTET)range;

        ieCount = 1;

        if (ret == 8)
        {
            ies[1].param_id = ISUP_PRM_CIRCUIT_ASSIGN_MAP;
            ies[1].param_length = 4;
            ies[1].param_data.circuitAssignmentMap.map_type =
                                             (ITS_OCTET)mapType;
            ies[1].param_data.circuitAssignmentMap.map_format[0] =
                                             (ITS_OCTET)cicMap;
            ies[1].param_data.circuitAssignmentMap.map_format[1] =
                                             (ITS_OCTET)cicMap >> 8;
            ies[1].param_data.circuitAssignmentMap.map_format[2] =
                                             (ITS_OCTET)cicMap >> 16;
            ies[1].param_data.circuitAssignmentMap.map_format[3] =
                                            (ITS_OCTET)cicMap >> 24;
            ieCount = 2;
        }

        ret = ISUP_SendMsgMMLToStack_ANSI(pcic, ISUP_MSG_GRS, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent the msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ia_send_grs <opc> <dpc> <sio> <cic>"
                          " <range> <mapTpye> <CicAsignMap>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ia_send_grs <opc> <dpc> <sio> <cic>"
                          " <range> <mapTpye> <CicAsignMap>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send msg *******\n"
                          "Usage: ia_send_grs <opc> <dpc> <sio> <cic>"
                          " <range> <mapTpye> <CicAsignMap>");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ia_send_cqm", "ISUP Send Circuit query Msg",
                          "<opc> <dpc> <sio> <cic> <range> "
                          "<msgType> <CicAsignMap> ",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic = 0;
        ITS_UINT range = 0;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d %d", buf, opc, dpc, sio,
                               &cic, &range);
        if (ret != 6)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                      "Usage: ia_send_cqm <opc> <dpc> <sio> <cic> <range>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));
        ies[0].param_id = ISUP_PRM_RANGE_STATUS;
        ies[0].param_length = 1;
        ies[0].param_data.rangeAndStatus.range = (ITS_OCTET)range;
        ieCount = 1;

        ret = ISUP_SendMsgMMLToStack_ANSI(pcic, ISUP_MSG_CQM, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent the msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                      "Usage: ia_send_cqm <opc> <dpc> <sio> <cic> <range>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                      "Usage: ia_send_cqm <opc> <dpc> <sio> <cic> <range>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send msg *******\n"
                      "Usage: ia_send_cqm <opc> <dpc> <sio> <cic> <range>");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Start parsing ISUP ACC information in XML files.
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
ITSSS7DLLAPI void
ISUP_ParseStart(ENGINE_ParserExtension ext, const char *el, const char **attr)
{
    XML_ParseData *pd;
    ISUP_CONG_CONTEXT *ctxt;

    pd = calloc(1, sizeof(XML_ParseData));
    ITS_C_ASSERT(pd != NULL);
    pd->next = ENGINE_PE_USER_DATA(ext);
    ENGINE_PE_USER_DATA(ext) = pd;

    ctxt = (ISUP_CONG_CONTEXT *)&pd->ctxt;

    while (*attr)
    {
        if (strcmp(*attr, "sectionName") == 0)
        {
            attr++;

            pd->sectionName = strdup(*attr);
            ITS_C_ASSERT(pd->sectionName != NULL);

            attr++;
        }
        if (strcmp(*attr, "congLevel1") == 0)
        {
            attr++;

            ctxt->congLevel1 = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "congLevel2") == 0)
        {
            attr++;

            ctxt->congLevel2 = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "congLevel3") == 0)
        {
            attr++;

            ctxt->congLevel3 = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "localcongTimer") == 0)
        {
            attr++;

            ctxt->localcongTimer = RESFILE_ParseNum(*attr);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Term parsing ISUP ACC information in XML files.
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
ITSSS7DLLAPI void
ISUP_ParseEnd(ENGINE_ParserExtension ext, const char *el)
{
    /* don't care */
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Convert ISUP ACC information in XML files.
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
ITSSS7DLLAPI void
ISUP_ConvertParserData(RESFILE_Manager *appRes, ENGINE_ParserExtension ext)
{
    int ret;
    char tmp[ITS_PATH_MAX];
    XML_ParseData *pd = (XML_ParseData *)ENGINE_PE_USER_DATA(ext);
    ISUP_CONG_CONTEXT *ctxt;


    while (pd != NULL)
    {
        ctxt = (ISUP_CONG_CONTEXT *)&pd->ctxt;

        /* convert the extension data to resources */
        sprintf(tmp, "%d", ctxt->congLevel1);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "congLevel1", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->congLevel2);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "congLevel2", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->congLevel3);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "congLevel3", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->localcongTimer);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "localcongTimer", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
  
        pd = pd->next;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Diff ISUP ACC information in XML files.
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
ITSSS7DLLAPI void
ISUP_Diff(RESFILE_Manager *appRes,
         ENGINE_ParserExtension ext1,
         ENGINE_ParserExtension ext2)
{
    /* don't care */
} 

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get Destination (DPC) state.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_GetDpcState(ISUP_OPC_DPC_INFO *config_info,
                 ISUP_DEST_STATUS *state)
{
     *state = config_info->dest_stat;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set Destination (DPC) state.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_SetDpcState(ISUP_OPC_DPC_INFO *config_info, ISUP_DEST_STATUS state)
{
     config_info->dest_stat = state;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get Remote ISUP status.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_GetRemoteIsupState(ISUP_OPC_DPC_INFO *config_info, 
                        ISUP_REMOTE_ISUP_STATUS *state)
{
     *state = config_info->remote_isup_stat;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set Remote ISUP Status.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_SetRemoteIsupState(ISUP_OPC_DPC_INFO *config_info, 
                        ISUP_REMOTE_ISUP_STATUS state)
{
     config_info->remote_isup_stat = state;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Get Local ISUP Congestion Level by measuring the ISUP Q length.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
static ITS_UINT
Getlocalconglevel(TQUEUETRAN_Manager *tq)
{
    return(LIST_COUNT(TQUEUETRAN_EMLIST(tq)));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Check the Route exits or not
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *     dpc - pc
 *     sio - service octet
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
ISUP_IsRouteExists_ANSI(ITS_UINT dpc, ITS_OCTET sio) 
{
    SS7_Destination *dest = NULL;

    dest = ROUTE_FindDestination(dpc, sio, FAMILY_ANSI);
    if (dest == NULL)
    {
        return ITS_FALSE;;
    }
    ROUTE_CommitDestination(dest, dpc, sio, FAMILY_ANSI);
    return ITS_TRUE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add Varaint feature dynamically.
 *
 *  Input Parameters:
 *          varType  -  Variant Name
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *          ITS_EINVVARIANT
 *          ITS_ENOFEATURE
 *          ITS_EINUSE
 *          ITS_ENOTFOUND
 *          ITS_SUCCESS if operation succesds.
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_AddVariantFeature_ANSI(const char *varType)
{
    ITS_Class isup_Class = NULL;
    int ret;
    DLSYM_Manager *mgr = NULL;
    ISUP_VAR_TYPE variant;

    variant = ISUP_StringToVariant(varType);

    if (variant == ISUP_UNKNOWN)
    {
        return ITS_EINVVARIANT;
    }

    if (!(variant == ISUP_ANSI_95 || variant == ISUP_ANSI_GENERIC_92))
    {
        return ITS_ENOFEATURE;
    }

    if (ITS_FindFeature(varType) != NULL)
    {
        return ITS_EINUSE;
    }

    if (strcmp(varType, "ANSI_ISUP_95") == ITS_SUCCESS)
    {
        mgr = DLSYM_Create("libANSI_ISUP_95.so");
        if (mgr == NULL)
        {
            mgr = DLSYM_Create("libANSI_ISUP_95D.so");
            if (mgr == NULL)
            {
                return ITS_ENOTFOUND;
            }
        }

        isup_Class = (ITS_Class) DLSYM_Resolve(mgr, "isupANSI95_Class");
    }
    else if (strcmp(varType, "ANSI_GENERIC_92") == ITS_SUCCESS)
    {
        mgr = DLSYM_Create("libANSI_GENERIC_92.so");
        if (mgr == NULL)
        {
            mgr = DLSYM_Create("libANSI_GENERIC_92D.so");
            if (mgr == NULL)
            {
                return ITS_ENOTFOUND;
            }
        }
        isup_Class = (ITS_Class) DLSYM_Resolve(mgr, "isupANSI92_Class");
    }
    else
    {
        return !ITS_SUCCESS;
    }

    if (!isup_Class)
    {
        DLSYM_Destroy(mgr);
        return !ITS_SUCCESS;
    }

    /* I don't why I can't use isup_Class */
    ret  = ITS_InitializeClass(ITS_CLASS_SUPERCLASS(isup_Class));
    if (ret != ITS_SUCCESS)
    {
        DLSYM_Destroy(mgr);
        return ret;
    }

    ISUP_DEBUG(("ISUP_AddVariantFeature %s: Initialize Class ret Val %d\n",
                 varType, ret));

    return ITS_AddFeature(ITS_CLASS_SUPERCLASS(isup_Class));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the configured stack information for ansi isup.
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
INTELLINET_ISUP_Commit_ANSI (FILE* fp, int pos, int opc, int dpc, int sio)
{
    if (fp == NULL)
    {
        return ITS_ENULLPTR;
    }

    switch (pos)
    {
        case 1:
        {
            int count = 0;
            TRACE_Data* td = ISUP_ANSI_TraceData;

            fprintf(fp,"\t\t\t\t<StackTrace>\n");

            for (count = 0; count < TRACE_DATA_NUM_LEVELS(td); count++)
            {
                fprintf(fp,"\t\t\t\t\t<%s output = \"%s\"/>\n",
                        TRACE_DATA_LEVEL_MAP(td)[count]->level.levelName,
                        (TRACE_DATA_LEVEL_MAP(td)[count]->
                        level.outputs[0]->trace.isEnabled)?
                        TRACE_DATA_LEVEL_MAP(td)[count]->
                        level.outputs[0]->trace.name : "");
                fprintf(fp,"\t\t\t\t\t<%s output = \"%s\"/>\n",
                        TRACE_DATA_LEVEL_MAP(td)[count]->level.levelName,
                        (TRACE_DATA_LEVEL_MAP(td)[count]->
                        level.outputs[1]->trace.isEnabled)?
                        TRACE_DATA_LEVEL_MAP(td)[count]->
                        level.outputs[1]->trace.name : "");
            }

            fprintf(fp,"\t\t\t\t</StackTrace>\n");
            break;
        }
        case 2:
        {
            MTP3_HEADER opc_dpc_ni;
            ISUP_OPC_DPC_STAT *config_stat = NULL;

            memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
            MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,opc);
            MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,dpc);
            MTP3_HDR_SET_SIO(opc_dpc_ni,sio);
            config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni);

            if (config_stat != NULL)
            {
                fprintf(fp,
                        "\t\t                exchangeType   = \"%s\"\n",
                        (config_stat->exchange_type == 0)?
                              "TYPE_A" : "TYPE_B");
            }
            break;
        }
        case 3:
        {
            ISUP_CFG_TMR_INFO tmr_info[ISUP_CFG_MAX_TIMERS];
            ISUP_CFG_KEY cfg;
            ISUP_CFG_CKGP_INFO *ckgp;
            int noEnt;
            ITS_BOOLEAN startcicFound = ITS_FALSE;
            ITS_BOOLEAN cics_present = ITS_FALSE;
            ITS_OCTET cicrule = ISUP_CKGP_CTRL_DEF;
            int cicsInckg = 32;
            ITS_USHORT cic = 0, startcic = 0;
            int i, j, count;
            int ret = !ITS_SUCCESS;

            cfg.opc = opc;
            cfg.dpc = dpc;
            cfg.sio = sio;

            ret = ISUP_GetAllTimerCfgInfo_ANSI(cfg, tmr_info);

            if (ret == ITS_SUCCESS)
            {
                for (i = 1; i < ITS_ISUP_TIMER_LAST; i++)
                {
                    fprintf(fp,
                            "\t\t\t<Timer name = \"%s\"\n",
                            ISUP_TimerToString((ITS_OCTET)i));
                    fprintf(fp,
                            "\t\t\t       value = \"%d\"\n",
                            tmr_info[i].tmr_cfg_value);
                    fprintf(fp,
                            "\t\t\t       handledBy = \"%s\"/>\n",
                            ISUP_TimerHandlerToString(
                              (ISUP_TMR_HNDL) tmr_info[i].tmr_cfg_hndl_layer));
                }
            }

            ret = !ITS_SUCCESS;
            ret = ISUP_GetAllCicsCfg_ANSI(cfg, &ckgp, &noEnt);
            if (ret == ITS_SUCCESS)
            {
                for (count = 0; count < noEnt; count++)
                {
                    if (ckgp[count].usable_cics[0] == 0)
                    {
                        continue;
                    }

                    startcicFound = ITS_FALSE;

                    for(j = 0; j < cicsInckg; j++)
                    {
                        if ((ckgp[count].usable_cics[0] &
                            (0x00000001 << j)) != 0)
                        {
                            cics_present = ITS_TRUE;
                            cic = (ckgp[count].ckgp_id * cicsInckg) + (j+1);

                            if (!startcicFound)
                            {
                                startcic = (ckgp[count].ckgp_id * cicsInckg) +
                                           (j+1);
                                startcicFound = ITS_TRUE;
                            }
                            else if (cicrule != ckgp[count].contl[j])
                            {
                                fprintf(fp,
                                        "\t\t\t<CircuitGroup huntRule"
                                        " = \"%s\">\n",
                                        ISUP_CkgpCtrlToString(cicrule));
                                fprintf(fp,
                                        "\t\t\t\t<CircuitCodes start"
                                        " = \"%d\"\n",
                                        startcic);
                                fprintf(fp,
                                        "\t\t\t\t              "
                                        "count = \"%d\"/>\n",
                                        cic);
                                fprintf(fp, "\t\t\t</CircuitGroup>\n");
                                startcic = (ckgp[count].ckgp_id * cicsInckg) +
                                           (j+1);
                            }
                        }
                        else
                        {
                            if (startcicFound)
                            {
                                fprintf(fp,
                                        "\t\t\t<CircuitGroup huntRule"
                                        " = \"%s\">\n",
                                        ISUP_CkgpCtrlToString(cicrule));
                                fprintf(fp,
                                        "\t\t\t\t<CircuitCodes start"
                                        " = \"%d\"\n",
                                        startcic);
                                fprintf(fp,
                                        "\t\t\t\t              "
                                        "count = \"%d\"/>\n",
                                        cic);
                                fprintf(fp, "\t\t\t</CircuitGroup>\n");
                            }

                            startcicFound = ITS_FALSE;
                        }

                        cicrule = ckgp[count].contl[j];
                    }

                    if (startcicFound)
                    {
                        fprintf(fp,
                                "\t\t\t<CircuitGroup huntRule = \"%s\">\n",
                                ISUP_CkgpCtrlToString(cicrule));
                        fprintf(fp,
                                "\t\t\t\t<CircuitCodes start = \"%d\"\n",
                                startcic);
                        fprintf(fp,
                                "\t\t\t\t              count = \"%d\"/>\n",
                                cic);
                        fprintf(fp, "\t\t\t</CircuitGroup>\n");
                    }
                }
            }
            break;
        }
        case 4:
        {
            fprintf(fp,
                    "\t\t\tcongLevel1 = \"%d\"\n",
                    ANSI_ISUP_conglevel1);
            fprintf(fp,
                    "\t\t\tcongLevel2 = \"%d\"\n",
                    ANSI_ISUP_conglevel2);
            break;
        }
    }

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
static int
DBCVarifyCicState(ITS_OCTET cic_state, DBC_Server *dbc)
{
    int      ret = ITS_SUCCESS;
    char     buf[ITS_PATH_MAX];

    switch(cic_state & 0x0cU) /* check bits DC */
    {
        case 0x00: /* DC is 00 */
            /* Now check for BA */
            switch(cic_state & 0x03)
            {
                case 0x00:
                    sprintf(buf, "\nMaintenance blocking state: TRANSIENT\n");
                    DBC_AppendText(dbc, buf);
                    break;

                case 0x11:
                    sprintf(buf, "Maintenance blocking state: UNEQUIPPED\n");
                    DBC_AppendText(dbc, buf);
                    break;

                default:
                    sprintf(buf, "Spare!\n");
                    DBC_AppendText(dbc, buf);
                    ret = !ITS_SUCCESS;
                    break;
            }
    }

    /* Bits DC not equal to 00 */
    switch(cic_state & 0x03U) /* Bits BA */
    {
        case 0x00:
            sprintf(buf, "Maintenance blocking state: UNBLOCKED (ACTIVE)\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x01:
            sprintf(buf, "Maintenance blocking state: LOCALLY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x02:
            sprintf(buf, "Maintenance blocking state: REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x03:
            sprintf(buf, "Maintenance blocking state: LOCALLY & REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        default:
            sprintf(buf, "Maintenance state: INVALID STATE!\n");
            DBC_AppendText(dbc, buf);
            ret = !ITS_SUCCESS;
            break;
    }

    switch(cic_state & 0x0cU) /* Bits DC */
    {
        case 0x04:
            sprintf(buf, "Call processing state: CIRCUIT INCOMING BUSY\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x08:
            sprintf(buf, "Call processing state: CIRCUIT OUTGOING BUSY\n");
            DBC_AppendText(dbc, buf);
            break;
        case 0x0c:
            sprintf(buf, "Call processing state: IDLE\n");
            DBC_AppendText(dbc, buf);
            break;

        default:
            sprintf(buf, "Call processing state: INVALID STATE!\n");
            DBC_AppendText(dbc, buf);
            ret = !ITS_SUCCESS;
            break;
    }

    switch(cic_state & 0x30U)
    {
        case 0x00:
            sprintf(buf, "Hardware blocking state: UNBLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x10:
            sprintf(buf, "Hardware blocking state: LOCALLY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x20:
            sprintf(buf, "Hardware blocking state: REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x30:
            sprintf(buf, "Hardware blocking state: LOCALLY & REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        default:
            sprintf(buf, "Hardware blocking state: INVALID STATE!\n");
            DBC_AppendText(dbc, buf);
            ret = !ITS_SUCCESS;
            break;
    }
    return ret;
}
