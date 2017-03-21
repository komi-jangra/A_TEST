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
 * ID: $Id: bssap-msc.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.8  2006/06/28 04:51:45  adutta
 * LOG: Added pc/ssn in mgmt. messages
 * LOG:
 * LOG: Revision 1.1.2.7  2005/12/20 09:10:04  adutta
 * LOG: Chnaged message type for network status
 * LOG:
 * LOG: Revision 1.1.2.6  2005/11/30 06:42:18  mkrishna
 * LOG: Added Pegs. pause flag changed to true
 * LOG:
 * LOG: Revision 1.1.2.5  2005/11/28 05:05:33  adutta
 * LOG: Timer 3250 implemented (Issue fixed)
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/17 06:26:39  mkrishna
 * LOG: Auth. Req/Ident. Req. timer implemented
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/08 07:09:17  mkrishna
 * LOG: Added T22 timer
 * LOG:
 * LOG: Revision 1.1.2.2  2005/10/14 09:30:49  adutta
 * LOG: Added mtp and sccp mgmt. callbacks
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#include <bssap-msc.h>
#include <bssap_msc-calldb.h>
#include <bssap_msc-common.h>
#include <bssap_msc-tqhandler.h>
#include <bssap_msc-timer.h>
#include <bssap_msc-fsm.h>
#include <bssap_msc-dtap.h>
#include <bssap_msc-map.h>
#include <bssap_msc-dbc.h>
#include <bssap_msc-pegs.h>

ITS_OCTET TIMER_Tries[BSSAP_NUM_TIMERS];
ITS_BOOLEAN pauseFlag = ITS_TRUE;
ITS_BOOLEAN sspFlag = ITS_FALSE;

TQUEUETRAN_Manager* __BSSAP_RcvQueue = NULL;
static ITS_THREAD   bssapThread;

static ITS_TIME timers[BSSAP_NUM_TIMERS];
TIMERS_DECL_SUBSYS(BSSAP, timers);

static ITS_UINT pegs[PEG_BSSAP_NUM_PEGS];
static PEGS_DECL_SUBSYS(BSSAP, pegs);
PEG_Manager *BSSAP_Pegs = &BSSAP_PEGS;

#define LEVEL_MAP_COUNT                5

extern "C"
{

static TRACE_OutputInitializer fileCritTrace =
{
    BSSAP_FILE_STRING,
    ITS_TRUE,
    BSSAP_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    BSSAP_FILE_STRING,
    ITS_TRUE,
    BSSAP_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    BSSAP_FILE_STRING,
    ITS_TRUE,
    BSSAP_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    BSSAP_FILE_STRING,
    ITS_TRUE,
    BSSAP_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileEventTrace =
{
    BSSAP_FILE_STRING,
    ITS_TRUE,
    BSSAP_TRACE_EVENT_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    BSSAP_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    BSSAP_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};


static TRACE_LevelInitializer BSSAP_TraceMap[] =
{
    {BSSAP_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {BSSAP_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {BSSAP_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {BSSAP_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } },
    {BSSAP_EVENT_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileEventTrace, &syslogTrace } }
};

TRACE_Data* BSSAP_TraceData = NULL;

/*implementation:internal
*
* PURPOSE:
*       Intializing configuration details with default values.
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  14-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0800
*/

static void 
BSSAP_MTP3MgmtHandler(ITS_POINTER object, ITS_POINTER userData,
                      ITS_POINTER callData)
{
    ITS_OCTET  ret_code = 0;
    ITS_EVENT *event = ( ITS_EVENT *)callData;
    MTP3_HEADER hdr;
    MTP3_STATUS stat;
    ITS_UINT pc = 0;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_MTP3MgmtHandler\n"));

    ret_code = MTP3_MSG_TYPE(event);
    memcpy(&hdr, &event->data[1], sizeof(MTP3_HEADER));

    pc = MTP3_RL_GET_OPC_VALUE(hdr.label);

    if (ret_code == MTP3_MSG_RESUME)
    {
        pauseFlag = ITS_FALSE;

        BSSAP_DEBUG(("BSSAP_MTP3MgmtHandler: MTP-RESUME from pc %d\n", pc));
    }
    else if (ret_code == MTP3_MSG_PAUSE)
    {
        pauseFlag = ITS_TRUE;

        BSSAP_CRITICAL(("BSSAP_MTP3MgmtHandler: MTP-PAUSE from pc %d\n", pc));
    }
    else if (ret_code == MTP3_MSG_STATUS)
    {
        BSSAP_DEBUG(("BSSAP_MTP3MgmtHandler: MTP-STATUS from pc %d\n", pc));

        ITS_UINT len = event->len - (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER));
        memcpy(&stat, &event->data[1 + sizeof(MTP3_HEADER)], len);

        ret_code = stat.cause;
    }

    bssIf.DispatchErrorToApp(BSSAP_MD_NETWORK, ret_code, pc, 0);
}

/*implementation:internal
*
* PURPOSE:
*       Intializing configuration details with default values.
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  14-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0800
*/

static void
BSSAP_SCCPMgmtHandler(ITS_POINTER object, ITS_POINTER userData,
                      ITS_POINTER callData)
{
    ITS_OCTET ret_code = 0;
    ITS_EVENT *event = (ITS_EVENT*)callData;
    ITS_SCCP_IE ies[32];
    ITS_HDR hdr;
    int ieCount;
    ITS_OCTET *scmgData = NULL;
    ITS_USHORT dlen = 0;
    ITS_UINT pc = 0;
    ITS_OCTET ssn = 0;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler\n"));

    if (SCCP_MSG_TYPE(event) != SCCP_MSG_UDT)
    {
        BSSAP_ERROR(("BSSAP_SCCPMgmtHandler: Unknown SCCP mssg. from stack\n"));
    }
    else
    {
        if (SCCP_ReceiveUnitData((ITS_HANDLE)ISS7_Stack,
                                 event,&hdr, ies,
                                 &ieCount) != ITS_SUCCESS)
        {
            BSSAP_ERROR(("BSSAP_SCCPMgmtHandler: Error in SCCP mgmt-mssg.\n"));

            return;
        }

        for (int i=0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_DATA)
            {
                scmgData = ies[i].param_data.userData.data;
                dlen = ies[i].param_length;
            }
        }

        ret_code = ((SCCP_SCMG *)scmgData)->type;
        pc = MTP3_PC_GET_VALUE_CCITT(((SCCP_SCMG *)scmgData)->pointCode);
        ssn = ((SCCP_SCMG *)scmgData)->ssn;

        BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP mgmt-mssg from %d %d\n",
                                                                    pc, ssn));

        switch (ret_code)
        {
            case SCCP_SCMG_SS_ALLOWED:
                sspFlag = ITS_FALSE;
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-SSA\n"));
                break;
            case SCCP_SCMG_SS_PROHIBIT:
                sspFlag = ITS_TRUE;
                BSSAP_CRITICAL(("BSSAP_SCCPMgmtHandler: SCCP-SSP\n"));
                break;
            case SCCP_SCMG_SS_STATUS_TEST:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-SST\n"));
                break;
            case SCCP_SCMG_SS_OOS_REQ:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-OSS-REQ\n"));
                break;
            case SCCP_SCMG_SS_OOS_GRANT:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-OSS-GRANT\n "));
                break;
            case SCCP_SCMG_SS_BACKUP_ROUTE:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-SS-BACKUP\n"));
                break;
            case SCCP_SCMG_SS_NORMAL_ROUTE:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-SS-NORMAL\n"));
                break;
            case SCCP_SCMG_SS_ROUTE_STATUS:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-SS-ROUTE-STATUS\n"));
                break;
            default:
                BSSAP_WARNING(("BSSAP_SCCPMgmtHandler: SCCP Management Msg\n"));
                return;
        }

        bssIf.DispatchErrorToApp(BSSAP_MD_NETWORK, ret_code, pc, ssn);
    }
}


/*implementation:internal
*
* PURPOSE:
*       Intializing configuration details with default values. 
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0800
*/
static void
InitSettings()
{
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_301, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_303, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_306, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_308, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_310, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_313, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_2, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_5, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_6, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_12, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_16, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_21, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_22, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_3250, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_3260, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_3270, 60);

    for (int i = 0; i < BSSAP_NUM_TIMERS; i++)
    {
        // Setting 1 for retries by default 
        TIMER_Tries[i] = 1;
    } 

    if (TRANSPORT_RES(__BSSAP_RcvQueue) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(__BSSAP_RcvQueue);
        char *name = TRANSPORT_NAME(__BSSAP_RcvQueue);

        // get the timers 
        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T301_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_301, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T303_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_303, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T306_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_306, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T308_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_308, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T310_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_310, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T313_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_313, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T2_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_2, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T5_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_5, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T6_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_6, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T12_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_12, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T16_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_16, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T21_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_21, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T22_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_22, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T3250_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_3250, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T3260_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_3260, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T3270_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_3270, atoi(value));
        }

        // critical 
        if (RESFILE_GetKeyValueOf(res, name, BSSAP_TRACE_CRITICAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, BSSAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_CRITICAL_STRING, ITS_FALSE);
            }
        }

        // error 
        if (RESFILE_GetKeyValueOf(res, name, BSSAP_TRACE_ERROR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, BSSAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_TRUE);

                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_ERROR_STRING, ITS_FALSE);
            }
        }

        // warning
        if (RESFILE_GetKeyValueOf(res, name, BSSAP_TRACE_WARNING_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, BSSAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_WARNING_STRING, ITS_FALSE);
            }
        }

        // debug 
        if (RESFILE_GetKeyValueOf(res, name, BSSAP_TRACE_DEBUG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, BSSAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)

            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_DEBUG_STRING, ITS_FALSE);
            }
        }
    }
}

/*implementation:internal
*
* PURPOSE:
*      Initialize the BSSAP subsystem.
* INPUT:
*      objClass - BSSAP stack object.
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      ITS_SUCCES - success.  Any other value indicates an IntelliSS7
*      processing error.
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0780, ID :: D0790
*/
static ITS_INT 
BSSAP_Initialize(ITS_Class objClass)
{
    ITS_INT ret = 0;
    BSSAP_Dtap dtap;
    BSSAP_Map map;
    ITS_Class dbClass;

    if ((BSSAP_TraceData = TRACE_Constructor("BSSAP",
                                                  BSSAP_TraceMap, 
                                                      LEVEL_MAP_COUNT)) == NULL)
    {
        return (ITS_ENOMEM);
    }


    __BSSAP_RcvQueue  = TQUEUETRAN_CreateTransport("BSSAP",
                                                   ITS_BSSAP_SRC,
                                                   ITS_SS7_MASK);
    if (!__BSSAP_RcvQueue)
    {
        printf("BSSAP_Initialize: Failed to create BSSAP Message queue\n");

        return (!ITS_SUCCESS);
    }
    else
    {
        printf("BSSAP_Initialize: BSSAP Message queue created\n");
    }

    TRANSPORT_IS_ACTIVE(__BSSAP_RcvQueue) = ITS_TRUE;

    InitSettings();

    if (!BSSAP_CallDB::IsInitialized())
    {
        ret = BSSAP_CallDB::Initialize();
        if (ret != ITS_SUCCESS)
        {
            printf("BSSAP_Initialize: Failed to initialize call table\n");

            return (!ITS_SUCCESS);
        }
    }

    if (!FsmMT::IsInitialized())
    {
        ret = FsmMT::Initialize();
        if (ret != ITS_SUCCESS)
        {
            printf("BSSAP_Initialize: Failed to initialize MT state table\n");

            return (!ITS_SUCCESS);
        }
    }

    if (!FsmMO::IsInitialized())
    {
        ret = FsmMO::Initialize();
        if (ret != ITS_SUCCESS)
        {
            printf("BSSAP_Initialize: Failed to initialize MO state table\n");
                                                                                                                                              
            return (!ITS_SUCCESS);
        }
    }

    dtap.Initialize();
    map.Initialize();


    if (THREAD_CreateThread(&bssapThread, 0, BSSAP_MssgHandler,
                            __BSSAP_RcvQueue, ITS_TRUE) != ITS_SUCCESS)
    {

        printf("BSSAP_Initialize: Failed to create BSSAP Stack thread\n"); 

        THREAD_KillThread(&bssapThread);

        THREAD_DeleteThread(&bssapThread);

        return (!ITS_SUCCESS);
    }

    DBC_ServerCreate("Demo", NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        printf("BSSAP_Initialize: Debug Console active\n");

        DBC_AddDoCommand(BSSAP_ConsoleCommand);
    }

    CALLBACK_AddCallback(MTP3_ManagementCallbacks, BSSAP_MTP3MgmtHandler, NULL);
    CALLBACK_AddCallback(SCCP_ManagementCallbacks, BSSAP_SCCPMgmtHandler, NULL);

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       None
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0780, ID :: D0790
*/                                                                                                                             
static void
BSSAP_Terminate(ITS_Class objClass)
{

}

}

/*implementation:internal
*
* PURPOSE:
*       None
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0780, ID :: D0790
*/                                                                                                                             
ITS_ClassRec itsBSSAP_ClassRec =
{
    /* core */
    {
        NULL,
        0,
        ITS_FALSE,
        0,
        "BSSAP",
        BSSAP_Initialize,
        BSSAP_Terminate,
        NULL,
        NULL,
        NULL
    }
};

ITS_Class itsBSSAP_Class = &itsBSSAP_ClassRec;

 
