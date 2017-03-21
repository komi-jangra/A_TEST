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
 *  ID: $Id: its-itu-sccp.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $
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
 * LOG: Revision 8.8  2003/09/24 19:43:10  mmiers
 * LOG: Pick up the other used before/never initialized warnings.
 * LOG:
 * LOG: Revision 8.7  2003/09/24 15:45:42  mmiers
 * LOG: Warning removal and one bug fix.
 * LOG:
 * LOG: Revision 8.6  2003/09/24 12:59:25  aganguly
 * LOG: Alarm change propagation from relase 6.3 to current and bug fixes.
 * LOG:
 * LOG: Revision 8.5  2003/07/22 15:43:46  mmiers
 * LOG: Warning removal.  Fix Windoze build.
 * LOG:
 * LOG: Revision 8.4  2003/07/16 09:06:20  aganguly
 * LOG: Changes for SCCP Pegs.
 * LOG:
 * LOG: Revision 8.3  2003/06/16 13:52:30  mmanikandan
 * LOG: Xml Persistency is added.
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
#include <assert.h>
#include <stdlib.h>

#undef ANSI
#undef CCITT
#if !defined(PRC)
#define CCITT
#endif

#include <its.h>
#include <its_dsm.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_timers.h>
#include <its_assertion.h>
#include <its_route_rwlock.h>

#include <dbc_serv.h>

#ident "$Id: its-itu-sccp.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"

#if defined(PRC)
#include <china/sccp.h>
#else
#include <itu/sccp.h>
#endif

#include "sccp_intern.h"

/*
 * global data
 */
TQUEUETRAN_Manager* __SCCP_CCITT_RcvQueue = NULL;

/*
 * local data
 */
THREAD_RET_TYPE CCITT_SCCPThread(void *arg);

static void SCCP_Console_CCITT(DBC_Server *dbc, const char *cmdLine);

static ITS_THREAD   *sccpThread;
static int numThreads = 1;

static ITS_BOOLEAN  initialized = ITS_FALSE;
static ITS_BOOLEAN  terminated = ITS_FALSE;

static ITS_CHAR *sccpPegStr[] =
{
    "PEG_SCCP_USER_MSG_SENT",
    "PEG_SCCP_REMOTE_MSG_RECEIVED",         
    "PEG_SCCP_ROUTING_FAILURE",
    "PEG_SCCP_REMOTE_GTT_REQUEST",
    "PEG_SCCP_REMOTE_GTT_SUCCESS",
    "PEG_SCCP_REMOTE_GTT_FAILURE",  
    "PEG_SCCP_USER_UNKNOWN_MSG_SENT",
    "PEG_SCCP_MSG_SYNTAX_ERR",
    "PEG_SCCP_REMOTE_REASSEMBLE_ERR",
    "PEG_SCCP_HOP_COUNTER_VIOLATION_ERR", 
    "PEG_SCCP_USER_SEGMENTATION_ERR",
    "PEG_SCCP_TIMER_TIAR_EXPIRY",
    "PEG_SCCP_USER_INITIATED_RLS",            
    "PEG_SCCP_USER_INITITATED_RESET",          
    "PEG_SCCP_REMOTE_UDT_RCVD",
    "PEG_SCCP_REMOTE_XUDT_RCVD",
    "PEG_SCCP_REMOTE_UDTS_RCVD",
    "PEG_SCCP_REMOTE_XUDTS_RCVD",              
    "PEG_SCCP_REMOTE_LUDT_RCVD",
    "PEG_SCCP_REMOTE_LUDTS_RCVD",
    "PEG_SCCP_USER_UDT_SENT",    
    "PEG_SCCP_USER_XUDT_SENT",
    "PEG_SCCP_USER_UDTS_SENT",
    "PEG_SCCP_USER_XUDTS_SENT",
    "PEG_SCCP_USER_LUDT_SENT",
    "PEG_SCCP_USER_LUDTS_SENT",
    "PEG_SCCP_USER_CR_SENT",                   
    "PEG_SCCP_CREF_TO_REMOTE_SENT",     
    "PEG_SCCP_RSR_TO_REMOTE_SENT",
    "PEG_SCCP_ERR_TO_REMOTE_SENT",            
    "PEG_SCCP_REMOTE_CR_RCVD",                 
    "PEG_SCCP_REMOTE_CREF_RCVD",
    "PEG_SCCP_REMOTE_RSR_RCVD",                
    "PEG_SCCP_REMOTE_ERR_RCVD",                
    "PEG_SCCP_REMOTE_ MSG_FOR_LOCAL_SS_RCVD",
    "PEG_SCCP_USER_DT1_SENT",
    "PEG_SCCP_REMOTE_DT1_RCVD",
    "PEG_SCCP_USER_DT2_SENT",                
    "PEG_SCCP_REMOTE_DT2_RCVD",          
    "PEG_SCCP_USER_ED_SENT",                   
    "PEG_SCCP_REMOTE_ED_RCVD",                 
    "PEG_SCCP_REMOTE_SSP_RCVD",
    "PEG_SCCP_REMOTE_SSA_RCVD",                
    "PEG_SCCP_REMOTE_SSC_RCVD",               
    "PEG_SCCP_LOCAL_SS_PROHIBITED",
    "PEG_SCCP_LOCAL_SS_ALLOWED",
    "PEG_SCCP_LOCAL_SS_CONGESTED",       
    "PEG_SCCP_RLSD_TO_REMOTE_SENT",           
    "PEG_SCCP_REMOTE_UNKNOWN_MSG_RCVD",
    "PEG_SCCP_ACTIVE_CONNECTION",
    "PEG_SCCP_ACTIVATED_CONNECTION",
    "PEG_SCCP_REMOTE_SSP_RCVD",
    NULL
};

static ITS_CHAR* SCCP_CCITT_Timers[]=
{
    SCCP_TSTAT_INFO_STRING,
    SCCP_TCOORD_CHG_STRING,
    SCCP_TIGNORE_SST_STRING,
    SCCP_TRTG_STAT_INFO_STRING,
    SCCP_TCONN_STRING,
    SCCP_TRELEASE_STRING,
    SCCP_TRESET_STRING,
    SCCP_TINACT_SEND_STRING,
    SCCP_TINACT_RECV_STRING,
    SCCP_TGUARD_STRING,
    SCCP_TREASSEM_STRING,
    SCCP_TINTERVAL_STRING,
    SCCP_TREPEAT_REL_STRING,
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
HandleMTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ITS_EVENT* ev = (ITS_EVENT *)callData;
    ITS_EVENT tmp;

    ITS_EVENT_INIT(&tmp, ev->src, ev->len);
    memcpy(tmp.data, ev->data, ev->len);

    if (TRANSPORT_PutEvent(ITS_SCCP_SRC, ev) != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&tmp);
    }
    else
    {
        *ev = tmp;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function starts the SCCP subsystem.
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
 *      If the subsystem is successfully started, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_SCCP_Initialize_CCITT(ITS_SS7_HANDLE handle)
{
    int i, j, ret;
    ITS_Class dbClass;
    RESFILE_Manager *res;
    char *name;
    char value[ITS_PATH_MAX];

    if (initialized)
    {
        return (ITS_SUCCESS);
    }

    initialized = ITS_TRUE;

    if ((__SCCP_CCITT_RcvQueue = TQUEUETRAN_CreateTransport("ITU-SCCP",
                                                            ITS_SCCP_SRC,
                                                            ITS_SCCP)) == NULL)
    {
        SCCP_CRITICAL(("SCCP_Initialize: couldn't create transport\n"));

        initialized = ITS_FALSE;
        SCCP_Alarm_CCITT(416, __FILE__, __LINE__, NULL);

        return (ITS_ENOTRANSPORT);
    }

    res = TRANSPORT_RES(__SCCP_CCITT_RcvQueue);
    name = TRANSPORT_NAME(__SCCP_CCITT_RcvQueue);

    ret = SCCP_Init_CCITT(res, name);
    if (ret != ITS_SUCCESS)
    {
        TQUEUETRAN_DeleteTransport(__SCCP_CCITT_RcvQueue);

        return (ret);
    }

    /* get the number of threads */
    if (res)
    {
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

    if ((sccpThread = (ITS_THREAD *)malloc(numThreads *
                                           sizeof(ITS_THREAD))) == NULL)
    {
        SCCP_CRITICAL(("SCCP_Initialize: couldn't create thread array\n"));
        SCCP_Alarm_CCITT(416, __FILE__, __LINE__, NULL);

        TQUEUETRAN_DeleteTransport(__SCCP_CCITT_RcvQueue);

        SCCP_Term_CCITT();

        initialized = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    for (i = 0; i < numThreads; i++)
    {
        if (THREAD_CreateThread(&sccpThread[i], 0, CCITT_SCCPThread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            SCCP_CRITICAL(("SCCP_Initialize: couldn't create thread\n"));
            SCCP_Alarm_CCITT(416, __FILE__, __LINE__, NULL);

            for (j = 0; j < i; j++)
            {
                THREAD_KillThread(&sccpThread[j]);

                THREAD_DeleteThread(&sccpThread[j]);
            }

            free(sccpThread);

            TQUEUETRAN_DeleteTransport(__SCCP_CCITT_RcvQueue);

            SCCP_Term_CCITT();

            initialized = ITS_FALSE;

            return (ITS_EBADTHREAD);
        }
    }

    CALLBACK_AddCallback(MTP3_ManagementCallbacks, HandleMTP3Mgmt, NULL);

    /* Informational - SCCP Intialized Successfully */
    SCCP_Alarm_CCITT(422, __FILE__, __LINE__, NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_AddDoCommand(SCCP_Console_CCITT);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function terminates SCCP
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
 *
 *  See Also:
 ****************************************************************************/
void
INTELLINET_SCCP_Terminate_CCITT(ITS_SS7_HANDLE handle)
{
    ITS_EVENT ev;
    void *status;
    ITS_Class dbClass;
    int i;

    if (!initialized || terminated)
    {
        return;
    }

    terminated = ITS_TRUE;

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_RemDoCommand(SCCP_Console_CCITT);
    }

    CALLBACK_RemCallback(MTP3_ManagementCallbacks, HandleMTP3Mgmt, NULL);

    ITS_EVENT_INIT(&ev, ITS_SCCP_SRC, 0);

    for (i = 0; i < numThreads; i++)
    {
        TRANSPORT_PutEvent(ITS_SCCP_SRC, &ev);
    }

    for (i = 0; i < numThreads; i++)
    {
        THREAD_WaitForThread(&sccpThread[i], &status);

        THREAD_DeleteThread(&sccpThread[i]);
    }

    free(sccpThread);

    assert(__SCCP_CCITT_RcvQueue != NULL);
    TQUEUETRAN_DeleteTransport(__SCCP_CCITT_RcvQueue);
    SCCP_Alarm_CCITT(423, __FILE__, __LINE__, NULL);

    SCCP_Term_CCITT();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is the entry point for the CCITT SCCP thread.
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
 *      SCCP function.
 *
 *  See Also:
 ****************************************************************************/

THREAD_RET_TYPE
CCITT_SCCPThread(void *arg)
{
    ITS_EVENT sccpEvent;
    ITS_BOOLEAN cont;
    ITS_TimerData *td;

    if (sizeof(SCCP_CONN_CTXT) > ITS_MAX_TIMER_CONTEXT)
    {
        SCCP_CRITICAL(("Structure overflow\n"));
        abort();
    }

    MTP3_EnableUserPart(MTP3_SIO_SCCP, ITS_SCCP_SRC);

    memset(&sccpEvent, 0, sizeof(ITS_EVENT));

    cont = ITS_TRUE;

    TRANSPORT_IS_ACTIVE(__SCCP_CCITT_RcvQueue) = ITS_TRUE;

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__SCCP_CCITT_RcvQueue))
                                                        (__SCCP_CCITT_RcvQueue,
                                                         &sccpEvent)
           == ITS_SUCCESS)
    {

        if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
        {
            SCCP_ERROR(("Failed to get route lock\n"));

            break;
        }

        switch (sccpEvent.src)
        {
        case ITS_MTP3_SRC:
            SCCP_DEBUG(("SCCP_Main: handle MTP3 msg.\n"));
            PEG_IncrPeg(CCITT_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_RECEIVED);

            SCRCHandleMTP3Msg_CCITT(&sccpEvent);
            break;

        case ITS_SCCP_SRC:
            SCCP_DEBUG(("SCCP_Main: handle termination event.\n"));
            
            TRANSPORT_IS_ACTIVE(__SCCP_CCITT_RcvQueue) = ITS_FALSE;

            cont = ITS_FALSE;
            
            break;

        case ITS_TIMER_SRC:
            SCCP_DEBUG(("SCCP_Main: handle TIMER msg.\n"));

            td = (ITS_TimerData*)sccpEvent.data;

            SCCP_CheckTimeout_CCITT(td);
            break;

        default:
            SCCP_DEBUG(("SCCP_Main: handle APP msg.\n"));

            switch (SCCP_MSG_TYPE(&sccpEvent))
            {
            case SCCP_MSG_UDT:
            case SCCP_MSG_XUDT:
            case SCCP_MSG_UDTS:
            case SCCP_MSG_XUDTS:
            case SCCP_MSG_LUDT:
            case SCCP_MSG_LUDTS:  
                SCLCHandleAPPMsg_CCITT(&sccpEvent);
                break;

            default:
                SCOCHandleAPPMsg_CCITT(&sccpEvent);
            }
        }

        ROUTE_UnlockRead(routeRWLock, __SCCP_CCITT_RcvQueue);
    }

    TRANSPORT_IS_ACTIVE(__SCCP_CCITT_RcvQueue) = ITS_FALSE;

    MTP3_DisableUserPart(MTP3_SIO_SCCP);

    THREAD_NORMAL_EXIT;
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
SCCP_Console_CCITT(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    int ret;
    int pc, cpc, ssn, cssn, ni;
    ITS_UINT i;

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "si_get_gen_cfg", "SCCP Get General Config", "", ""))
    {
        SCCPGeneralCfg *cfg;
        cfg =  SCCP_GetGeneralCfg_CCITT();

        sprintf(buf, "*********** SCCP General Config *************\n");
        DBC_AppendText(dbc, buf);

        i = cfg->alarmLevel;

        switch(i)
        {
            case ALARM_LVL_CRIT :
                sprintf(buf, "    Alarm Level = CRITICAL\n");
            break;

            case ALARM_LVL_MAJOR :
                sprintf(buf, "    Alarm Level = MAJOR\n");
            break;

            case ALARM_LVL_MINOR :
                sprintf(buf, "    Alarm Level = MINOR\n");
            break;

            case ALARM_LVL_INFO :
                sprintf(buf, "    Alarm Level = INFO\n");
            break;

            case ALARM_LVL_OFF :
                sprintf(buf, "    Alarm Level = OFF\n");
            break;

            default :
                sprintf(buf, "    Alarm Level Not Set\n");
            break;
        }

        DBC_AppendText(dbc, buf);

       strcpy(buf, "    SCCP Trace -\n");
       DBC_AppendText(dbc, buf);
       if ( cfg->traceOn)
       {
           if (TRACE_IsLevelOn(SCCP_CCITT_TraceData,
                                    SCCP_TRACE_DEBUG))
           {
               strcpy(buf, "        Debug     = ");
               if(TRACE_IsOutputOn(SCCP_CCITT_TraceData,
                                      SCCP_TRACE_DEBUG,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(SCCP_CCITT_TraceData,
                                      SCCP_TRACE_DEBUG,
                                      1))
               {
                    strcat(buf, " file");
               }
           }
           else
           {
               strcpy(buf, "        Debug     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(SCCP_CCITT_TraceData,
                                    SCCP_TRACE_CRITICAL))
           {
               strcpy(buf, "        Critical  = ");
               if(TRACE_IsOutputOn(SCCP_CCITT_TraceData,
                                      SCCP_TRACE_CRITICAL,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(SCCP_CCITT_TraceData,
                                      SCCP_TRACE_CRITICAL,
                                      1))
               {
                    strcat(buf, " file");
               }
           }
           else
           {
               strcpy(buf, "        Critical  = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(SCCP_CCITT_TraceData,
                                    SCCP_TRACE_WARNING))
           {
               strcpy(buf, "        Warning   = ");
               if(TRACE_IsOutputOn(SCCP_CCITT_TraceData,
                                      SCCP_TRACE_WARNING,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(SCCP_CCITT_TraceData,
                                      SCCP_TRACE_WARNING,
                                      1))
               {
                    strcat(buf, " file");
               }
           }
           else
           {
               strcpy(buf, "        Warning   = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(SCCP_CCITT_TraceData,
                                    SCCP_TRACE_ERROR))
           {
               strcpy(buf, "        Error     = ");
               if(TRACE_IsOutputOn(SCCP_CCITT_TraceData,
                                      SCCP_TRACE_ERROR,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(SCCP_CCITT_TraceData,
                                      SCCP_TRACE_ERROR,
                                      1))
               {
                    strcat(buf, " file");
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
           strcpy(buf, "        Error    = null\n");
           DBC_AppendText(dbc, buf);
       }


       sprintf(buf, "*********** End of SCCP General Config *************\n");
       DBC_AppendText(dbc, buf);


    }
    else if (DBC_Cmd(dbc, "si_set_gen_cfg", "SCCP Set General Config", 
                      "<al> <tl>",
                     "<alarm level> <On / Off>"))

    {
        SCCPGeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType, 
                     traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
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
            sprintf(buf, "Invalid Alarm Level\n");
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
            sprintf(buf, "Invalid Trace Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, SCCP_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, SCCP_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, SCCP_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, SCCP_ERROR_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "Invalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, SCCP_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, SCCP_FILE_STRING);
        }
        else
        {
            sprintf(buf, "Invalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  SCCP_SetGeneralCfg_CCITT(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

       sprintf(buf, "*********** SCCP General Config Set*************\n");
       DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_get_ss", "SCCP Get Subsystem Entry", 
                     "<sspc> <ni> <ssn>",
                     "<point code> <network indicator> <subsystem>"))

    {
        SCCPSubSystemInfo* info;

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &pc, &ni, &ssn);
        if (ret != 4)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info = SCCP_GetSSEntry_CCITT( (ITS_UINT)pc, (ITS_OCTET)ni, 
                                       (ITS_OCTET)ssn);

        if (info)
        {
            sprintf(buf, "*********** SCCP Found SSN Entry*************\n");
            DBC_AppendText(dbc, buf);

            sprintf(buf, "    pointcode          <%d>\n", info->pointcode);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ni                 <%d>\n", info->ni);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ssn                <%d>\n", info->ssn);
            DBC_AppendText(dbc, buf);

            if (info->inService == ITS_FALSE)
            {
                sprintf(buf, "    inService          <no>\n");
            }
            else
            {
                sprintf(buf, "    inService          <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            if (info->testOn == ITS_FALSE)
            {
                sprintf(buf, "    testOn             <no>\n");
            }
            else
            {
                sprintf(buf, "    testOn             <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            if (info->hasConcernPC == ITS_FALSE)
            {
                sprintf(buf, "    hasConcernPC       <no>\n");
            }
            else
            {
                sprintf(buf, "    hasConcernPC       <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            sprintf(buf, "    maxHops            <%d>\n", info->maxHops);
            DBC_AppendText(dbc, buf);

            if (info->backupStatus == SSN_STANDALONE)
            {
                sprintf(buf, "    backupStatus       <standalone>\n");
            }
            else if (info->backupStatus == SSN_PRIMARY)
            {
                sprintf(buf, "    backupStatus       <primary>\n");
            }
            else if (info->backupStatus == SSN_SECONDARY)
            {
                sprintf(buf, "    backupStatus       <secondary>\n");
            }
            else if (info->backupStatus == SSN_MATED)
            {
                sprintf(buf, "    backupStatus       <mated>\n");
            }
            else
            {
                sprintf(buf, "    backupStatus       <standalone>\n");
            }

            DBC_AppendText(dbc, buf);
            sprintf(buf, "    backupPC           <%d>\n", info->backupPC);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    backupNI           <%d>\n", info->backupNI);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    backupSSN          <%d>\n", info->backupSSN);
            DBC_AppendText(dbc, buf);

            if (info->backupSSNState == ITS_FALSE)
            {
                sprintf(buf, "    backupSSNState     <down>\n");
            }
            else
            {
                sprintf(buf, "    backupSSNState     <up>\n");
            }
            DBC_AppendText(dbc, buf);
        }
        else
        {
            sprintf(buf, "*********** SCCP SSN Entry Not Found***********\n");
            DBC_AppendText(dbc, buf);
        }

    }
    else if (DBC_Cmd(dbc, "si_get_all_ss", "SCCP Get All Subsystem Entries", 
                     "", ""))
    {
        SCCPSubSystemInfo *entry;
        ITS_UINT numEntries;

        SCCP_GetAllSSEntries_CCITT( &numEntries, &entry);

        sprintf(buf, "    Total Entries <%d>\n", numEntries);
        DBC_AppendText(dbc, buf);

        for ( i = 0; i < numEntries; i++)
        {
            sprintf(buf, "------------------------------\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    pointcode      <%d>\n", entry[i].pointcode);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ni             <%d>\n", entry[i].ni);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ssn            <%d>\n", entry[i].ssn);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    linkset        <%d>\n", entry[i].linkSet);
            DBC_AppendText(dbc, buf);

            if (entry[i].inService == ITS_FALSE)
            {
                sprintf(buf, "    inService      <no>\n");
            }
            else
            {
                sprintf(buf, "    inService      <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            if (entry[i].testOn == ITS_FALSE)
            {
                sprintf(buf, "    testOn         <no>\n");
            }
            else
            {
                sprintf(buf, "    testOn         <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            if (entry[i].hasConcernPC == ITS_FALSE)
            {
                sprintf(buf, "    hasConcernPC   <no>\n");
            }
            else
            {
                sprintf(buf, "    hasConcernPC   <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            sprintf(buf, "    maxHops        <%d>\n", entry[i].maxHops);
            DBC_AppendText(dbc, buf);

            if (entry[i].backupStatus == SSN_STANDALONE)
            {
                sprintf(buf, "    backupStatus   <standalone>\n");
            }
            else if (entry[i].backupStatus == SSN_PRIMARY)
            {
                sprintf(buf, "    backupStatus   <primary>\n");
            }
            else if (entry[i].backupStatus == SSN_SECONDARY)
            {
                sprintf(buf, "    backupStatus   <secondary>\n");
            }
            else if (entry[i].backupStatus == SSN_MATED)
            {
                sprintf(buf, "    backupStatus   <mated>\n");
            }
            else
            {
                sprintf(buf, "    backupStatus   <standalone>\n");
            }
            DBC_AppendText(dbc, buf);

            sprintf(buf, "    backupPC       <%d>\n", entry[i].backupPC);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    backupNI       <%d>\n", entry[i].backupNI);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    backupSSN      <%d>\n", entry[i].backupSSN);
            DBC_AppendText(dbc, buf);

            if (entry[i].backupSSNState == ITS_FALSE)
            {
                sprintf(buf, "    backupSSNState <down>\n");
            }
            else
            {
                sprintf(buf, "    backupSSNState <up>\n");
            }
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "si_rem_ss", "SCCP Remove Subsystem Entry", 
                     "<sspc> <ssn> <linkset>",
                     "<point code> <subsystem> <linkset>"))

    {
        SCCPSubSystemInfo info;
        ITS_UINT linkset;
        SS7_LinkSetPtr lptr = NULL;

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &pc, &ssn, &linkset);
        if (ret != 4)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "********* Invalid Linkset********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.linkSet = linkset;
        info.pointcode = pc;
        info.ni = lptr->ni;
        info.ssn = ssn;

       ret = SCCP_RemSSEntry_CCITT(&info);
       if (ret != ITS_SUCCESS)
       {
            sprintf(buf, "********* SCCP Remocve SSN Entry Failed***********\n");
            DBC_AppendText(dbc, buf);
           return;
       }

        sprintf(buf, "********* SCCP Subsystem Entry Removed********\n");
        SCCP_Alarm_CCITT(500, __FILE__, __LINE__, "PC %08x, SSN %02d", pc, ssn);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "si_set_ss", "SCCP Set Subsystem Entry", 
                     "<sspc> <ssn> <linkset> ",
                     "<point code> <ssn> <linkset>"))

    {
        SCCPSubSystemInfo info;
        ITS_UINT linkset;
        SS7_LinkSetPtr lptr = NULL;

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &pc, &ssn,
                     &linkset);
        if (ret != 4)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "********* Invalid Linkset********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pointcode = pc;
        info.ni = lptr->ni;
        info.ssn = ssn;
        info.linkSet = linkset;

       ret = SCCP_SetSSEntry_CCITT(&info);
       if (ret != ITS_SUCCESS)
       {
           sprintf(buf, "********* SCCP SSN Set Entry Failed***********\n");
           DBC_AppendText(dbc, buf);
           return;
       }

        sprintf(buf, "********* SCCP Subsystem Entry Set********\n");
        SCCP_Alarm_CCITT(501, __FILE__, __LINE__, "PC %08x, SSN %02d", pc, ssn);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "si_get_pc", "SCCP Get Point Code Entry", 
                     "<sspc> <ni>",
                     "<point code> <network indicator>"))

    {
        SCCPPointCodeInfo* info;

        ret = sscanf(cmdLine, "%s %d %d ", buf, &pc, &ni);
        if (ret != 3)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info = SCCP_GetPointCodeEntry_CCITT( (ITS_OCTET)ni, (ITS_UINT)pc);

        if (info)
        {
            sprintf(buf, "********* SCCP Found Point Code Entry**********\n");
            sprintf(buf, "    pointCode              <%d>\n", info->pointCode);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ni                     <%d>\n", info->ni);
            DBC_AppendText(dbc, buf);

            if (info->isPointcodeProhibited == ITS_FALSE)
            {
                sprintf(buf, "    isPointcodeProhibited  <no>\n");
            }
            else
            {
                sprintf(buf, "    isPointcodeProhibited  <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            sprintf(buf, "    pcCongestLevel         <%d>\n", 
                   info->pcCongestLevel);
            DBC_AppendText(dbc, buf);
            
            if (info->isAdjacent == ITS_FALSE)
            {
                sprintf(buf, "    isAdjacent             <no>\n");
            }
            else
            {
                sprintf(buf, "    isAdjacent             <yes>\n");
            }
            DBC_AppendText(dbc, buf);
        }
        else
        {
            sprintf(buf, "********* SCCP Point Code Entry Not Found******\n");
            DBC_AppendText(dbc, buf);
        }

    }
    else if (DBC_Cmd(dbc, "si_get_all_pc", "SCCP Get All Point Code Entries", 
                     "", ""))

    {
        SCCPPointCodeInfo *entry;
        ITS_UINT numEntries;

        SCCP_GetAllPointCodeEntries_CCITT( &numEntries, &entry);

        sprintf(buf, "    Total Entries          <%d>\n", numEntries);
        DBC_AppendText(dbc, buf);

        for ( i = 0; i < numEntries; i++)
        {
            sprintf(buf, "------------------------------\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    pointCode              <%d>\n", entry[i].pointCode);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ni                     <%d>\n", entry[i].ni);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    linkset                <%d>\n", entry[i].linkSet);
            DBC_AppendText(dbc, buf);

            if (entry[i].isPointcodeProhibited == ITS_FALSE)
            {
                sprintf(buf, "    isPointcodeProhibited  <no>\n");
            }
            else
            {
                sprintf(buf, "    isPointcodeProhibited  <yes>\n");
            }
            DBC_AppendText(dbc, buf);

            sprintf(buf, "    pcCongestLevel         <%d>\n", 
                    entry[i].pcCongestLevel);
            DBC_AppendText(dbc, buf);

            if (entry[i].isAdjacent == ITS_FALSE)
            {
                sprintf(buf, "    isAdjacent             <no>\n");
            }
            else
            {
                sprintf(buf, "    isAdjacent             <yes>\n");
            }
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "si_set_pc", "SCCP Set Point Code Entry", 
                     "<sspc> <linkset>",
                   "<point code> <linkset>"))
    {
        ITS_INT linkset;
        SCCPPointCodeInfo info;
        SS7_LinkSetPtr lptr = NULL;

        ret = sscanf(cmdLine, "%s %d %d", buf, &pc, &linkset);
        if (ret != 3)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "********* Invalid Linkset********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pointCode = pc;
        info.ni = lptr->ni;
        info.linkSet = linkset;

        ret = SCCP_SetPointCodeEntry_CCITT(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP PC Set Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "********* SCCP Point Code Entry Set********\n");
        SCCP_Alarm_CCITT(502, __FILE__, __LINE__, "PC %08x", pc);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_rem_pc", "SCCP Remove Point Code Entry", 
                     "<sspc> <linkset>",
                   "<point code> <linkset>"))

    {
        ITS_INT linkset;
        SCCPPointCodeInfo info;
        SS7_LinkSetPtr lptr = NULL;

        ret = sscanf(cmdLine, "%s %d %d", buf, &pc, &linkset);

        if (ret != 3)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "********* Invalid Linkset********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pointCode = pc;
        info.ni = lptr->ni;
        info.linkSet = (ITS_OCTET)linkset;

        ret = SCCP_RemPointCodeEntry_CCITT(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP Remove PC Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "********* SCCP Point Code Entry Removed********\n");
        SCCP_Alarm_CCITT(503, __FILE__, __LINE__, "PC %08x", pc);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_get_cpc", "SCCP Get Concerned Point Code Entry", 
                     "<sspc> <ni> <ssn> <cpc>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code>"))

    {
        SCCPConcernedPCInfo* info;

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &pc, &ni, &ssn, &cpc);
        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info = SCCP_GetConcernedPC_CCITT( (ITS_UINT)pc, (ITS_OCTET)ni, 
                                          (ITS_OCTET)ssn, (ITS_UINT)cpc);

        if (info)
        {
            sprintf(buf, "******** SCCP Found CPC Entry*************\n");
        }
        else
        {
            sprintf(buf, "*********** SCCP CPC Entry Not Found*************\n");
        }
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_get_all_cpc", "SCCP Get All CPC Entries", 
                     "", ""))

    {
        SCCPConcernedPCInfo *entry;
        ITS_UINT numEntries;

        SCCP_GetAllCPCEntries_CCITT( &numEntries, &entry);

        for ( i = 0; i < numEntries; i++)
        {
            sprintf(buf, "------------------------------\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    sspc    <%d>\n", entry[i].sspc);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ni      <%d>\n", entry[i].ni);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ssn     <%d>\n", entry[i].ssn);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    cpc     <%d>\n", entry[i].cpc);
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "si_set_cpc", "SCCP Set Concerned Point Code Entry", 
                     "<sspc> <ni> <ssn> <cpc>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code>"))

    {
        SCCPConcernedPCInfo info;

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &pc, &ni, &ssn, &cpc);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.sspc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;

        ret = SCCP_SetConcernedPC_CCITT(&info);
        if (ret == ITS_ENOTFOUND)
        {
             sprintf(buf, "No Local Route Found For pc=%d, ni=%d, ssn=%d\n",
                     pc, ni, ssn);
             DBC_AppendText(dbc, buf);
             sprintf(buf, "********* SCCP Set CPC Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP Set CPC Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "******* SCCP Concerned Point Code Entry Set********\n");
        SCCP_Alarm_CCITT(504, __FILE__, __LINE__, "PC %08x, SSN %02d", pc, ssn);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_rem_cpc", "SCCP Remove CPC Entry", 
                     "<sspc> <ni> <ssn> <cpc>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code>"))

    {
        SCCPConcernedPCInfo info;

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &pc, &ni, &ssn, &cpc);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.sspc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;

        ret = SCCP_RemConcernedPC_CCITT(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP Rem CPC Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "****** SCCP Concerned Point Code Entry Removed***\n");
        SCCP_Alarm_CCITT(505, __FILE__, __LINE__, "PC %08x, SSN %02d", pc, ssn);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_get_cssn", "SCCP Get Concerned SSN Entry", 
                     "<sspc> <ni> <ssn> <cpc> <cssn>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code> <concerned ssn>"))

    {
        SCCPConcernedSSInfo* info;

        ret = sscanf(cmdLine, "%s %d %d %d %d %d", buf, &pc, &ni, &ssn, &cpc,
                     &cssn);
        if (ret != 6)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info = SCCP_GetConcernedSS_CCITT( (ITS_UINT)pc, (ITS_OCTET)ni, 
                                         (ITS_OCTET)ssn, (ITS_UINT)cpc, 
                                          (ITS_OCTET)cssn);

        if (info)
        {
            sprintf(buf, "*********** SCCP Found CSSN Entry*************\n");
        }
        else
        {
            sprintf(buf, "******** SCCP CSSN Entry Not Found************\n");
        }
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_get_all_cssn", "SCCP Get All Concerned SSN Entry",
                     "", ""))

    {
        SCCPConcernedSSInfo *entry;
        ITS_UINT numEntries;

        SCCP_GetAllCSSEntries_CCITT( &numEntries, &entry);

        for ( i = 0; i < numEntries; i++)
        {
            sprintf(buf, "------------------------------\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    pc       <%d>\n", entry[i].pc);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ni       <%d>\n", entry[i].ni);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    ssn      <%d>\n", entry[i].ssn);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    cpc      <%d>\n", entry[i].cpc);
            DBC_AppendText(dbc, buf);
            sprintf(buf, "    cssn     <%d>\n", entry[i].cssn);
            DBC_AppendText(dbc, buf);

        }
    }
    else if (DBC_Cmd(dbc, "si_set_cssn", "SCCP Set Concerned SSN Entry", 
                     "<sspc> <ni> <ssn> <cpc> <cssn>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code> <concerned ssn"))

    {
        SCCPConcernedSSInfo info;

        ret = sscanf(cmdLine, "%s %d %d %d %d %d", buf, &pc, 
                     &ni, &ssn, &cpc, 
                     &cssn);

        if (ret != 6)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;
        info.cssn = cssn;

        ret = SCCP_SetConcernedSS_CCITT(&info);
        if (ret == ITS_ENOTFOUND)
        {
             sprintf(buf, "No Local Route Found For pc=%d, ni=%d, ssn=%d\n",
                     pc, ni, ssn);
             DBC_AppendText(dbc, buf);
             sprintf(buf, "********* SCCP Set CPC Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP CSSN Set Entry Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "********* SCCP Concerned Subsystem Entry Set*******\n");
        SCCP_Alarm_CCITT(506, __FILE__, __LINE__, "PC %08x SSN %02d", pc, ssn);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_rem_cssn", "SCCP Remove Concerned SSN Entry", 
                     "<sspc> <ni> <ssn> <cpc> <cssn>",
                     "<point code> <network indicator> <subsystem>" 
                      " <concerned point code> <concerned ssn"))

    {
        SCCPConcernedSSInfo info;
        ITS_INT inservice = ITS_FALSE;

        ret = sscanf(cmdLine, "%s %d %d %d %d %d", buf, &pc, &ni, &ssn, &cpc, 
                     &cssn);

        if (ret != 6)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        info.pc = pc;
        info.ni = ni;
        info.ssn = ssn;
        info.cpc = cpc;
        info.cssn = cssn;
        info.inservice = inservice;

        ret = SCCP_RemConcernedSS_CCITT(&info);
        if (ret != ITS_SUCCESS)
        {
             sprintf(buf, "********* SCCP Remove CSSN  Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "****** SCCP Concerned Subsystem Entry Removed*****\n");
        SCCP_Alarm_CCITT(507, __FILE__, __LINE__, "PC %08x SSN %02d", pc, ssn);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_behavior", "SCCP Get Behaviors", 
                     "", ""))

    {
        if (BEHAVIORS_GetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_use_SCMG))
        {
            sprintf(buf, "    SCCP_B_use_SCMG          <yes> \n");
        }
        else
        {
            sprintf(buf, "    SCCP_B_use_SCMG          <no> \n");
        }
        DBC_AppendText(dbc, buf);

        if (BEHAVIORS_GetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_propagate_SCMG))
        {
            sprintf(buf, "    SCCP_B_propagate_SCMG    <yes> \n");
        }
        else
        {
            sprintf(buf, "    SCCP_B_propagate_SCMG    <no> \n");
        }
        DBC_AppendText(dbc, buf);

        if (BEHAVIORS_GetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_propagate_IT))
        {
            sprintf(buf, "    SCCP_B_propagate_IT      <yes> \n");
        }
        else
        {
            sprintf(buf, "    SCCP_B_propagate_IT      <no> \n");
        }
        DBC_AppendText(dbc, buf);

        if (BEHAVIORS_GetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_propagate_ERR))
        {
            sprintf(buf, "    SCCP_B_propagate_ERR     <yes> \n");
        }
        else
        {
            sprintf(buf, "    SCCP_B_propagate_ERR     <no> \n");
        }
        DBC_AppendText(dbc, buf);


    }
    else if (DBC_Cmd(dbc, "si_set_behavior", "SCCP Set Behaviors", 
                     "<ps> <us> <pi> <pe>", ""))

    {
        char ps[ITS_PATH_MAX];
        char us[ITS_PATH_MAX];
        char pi[ITS_PATH_MAX];
        char pe[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, ps, us, pi, pe);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(us, "YES") != NULL || strstr(us, "yes") != NULL)
        {
            BEHAVIORS_SetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_use_SCMG, 
                                  ITS_TRUE);
        }
        else if (strstr(us, "NO") != NULL || strstr(us, "no") != NULL)
        {
            BEHAVIORS_SetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_use_SCMG, 
                                   ITS_FALSE);
        }
        else
        {
            sprintf(buf, "Invalid Value Of Use SCMG Behavior: Set Failed\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(ps, "YES") != NULL || strstr(ps, "yes") != NULL)
        {
            BEHAVIORS_SetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_propagate_SCMG, 
                                  ITS_TRUE);
        }
        else if (strstr(ps, "NO") != NULL || strstr(ps, "no") != NULL)
        {
            BEHAVIORS_SetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_propagate_SCMG, 
                                   ITS_FALSE);
        }
        else
        {
            sprintf(buf, "Invalid Value Propogate SCMG Behavior: Set Failed\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if  (strstr(pi, "YES") != NULL || strstr(pi, "yes") != NULL)
        {
            BEHAVIORS_SetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_propagate_IT, 
                                  ITS_TRUE);
        }
        else if (strstr(pi, "NO") != NULL || strstr(pi, "no") != NULL)
        {
            BEHAVIORS_SetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_propagate_IT, 
                                   ITS_FALSE);
        }
        else
        {
            sprintf(buf, 
                   "Invalid Value Propogate Inactivity Behavior: Set Failed\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if  (strstr(pe, "YES") != NULL || strstr(pe, "yes") != NULL)
        {
            BEHAVIORS_SetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_propagate_ERR, 
                                  ITS_TRUE);
        }
        else if (strstr(pe, "NO") != NULL || strstr(pe, "no") != NULL)
        {
            BEHAVIORS_SetBehavior(&CCITT_SCCP_Behaviors, SCCP_B_propagate_ERR, 
                                   ITS_FALSE);
        }
        else
        {
            sprintf(buf, "Invalid Value Propogate Error Behavior: Set Failed\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "*******SCCP Behaviors Set*******\n");
        DBC_AppendText(dbc, buf);


    }
    else if (DBC_Cmd(dbc, "si_get_tmr", "SCCP Get Timers", 
                     "", ""))
    {
        int value = 0;

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_statInfo);
        sprintf(buf, "    SCCP_T_statInfo       <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_coordChg);
        sprintf(buf, "    SCCP_T_coordChg       <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_ignoreSST);
        sprintf(buf, "    SCCP_T_ignoreSST      <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_rtgStatInfo);
        sprintf(buf, "    SCCP_T_rtgStatInfo    <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_conn);
        sprintf(buf, "    SCCP_T_conn           <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_release);
        sprintf(buf, "    SCCP_T_release        <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_reset);
        sprintf(buf, "    SCCP_T_reset          <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_ias);
        sprintf(buf, "    SCCP_T_ias            <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_iar);
        sprintf(buf, "    SCCP_T_iar            <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_guard);
        sprintf(buf, "    SCCP_T_guard          <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_reassembly);
        sprintf(buf, "    SCCP_T_reassembly     <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_interval);
        sprintf(buf, "    SCCP_T_interval       <%d> \n", value);
        DBC_AppendText(dbc, buf);

        value = TIMERS_GetTimerValue(&CCITT_SCCP_Timers, SCCP_T_repeatRelease);
        sprintf(buf, "    SCCP_T_repeatRelease  <%d> \n", value);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_set_tmr", "SCCP Set Timer", 
                     "<tmr> <value>", "<Timer#> <value>"))

    {
        int tr, value = 0;

        ret = sscanf(cmdLine, "%s %d %d", buf, &tr, &value);

        if (ret != 3)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        TIMERS_SetTimerValue(&CCITT_SCCP_Timers, tr, value);

        sprintf(buf, "    Timer # %d Set \n", tr);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "si_get_peg", "Get Pegs", "<pg> ", "<Peg#> <>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT value;
        ITS_UINT pg = PEG_SCCP_NUM_PEGS;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
             return;
        }

        for (i = 0; i < PEG_SCCP_NUM_PEGS; i++)
        {
            if ( strstr(pgName, sccpPegStr[i]))
            {
                pg = i;
            }
        }

        if (pg == PEG_SCCP_NUM_PEGS)
        {
            sprintf(buf, "**** Invalid Peg Type *******\n");
            DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "Getting the Peg for %s Now\n", pgName);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(CCITT_SCCP_Pegs, pg);

        sprintf(buf, "value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "si_clr_peg", "Clear Peg", "<pg> ", "<Peg#> <>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT pg = PEG_SCCP_NUM_PEGS;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
             sprintf(buf, "**** Invalid Command Arguments *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        for (i = 0; i < PEG_SCCP_NUM_PEGS; i++)
        {
            if ( strstr(pgName, sccpPegStr[i]))
            {
                pg = i;
            }
        }

        if (pg == PEG_SCCP_NUM_PEGS)
        {
            sprintf(buf, "**** Invalid Peg Type *******\n");
            DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "Clearing the Pegs for %s Now\n", pgName);
        DBC_AppendText(dbc, buf);

        PEG_ClearPeg(CCITT_SCCP_Pegs, pg);

    }
    else if (DBC_Cmd(dbc, "si_clr_all_peg", "Clear All Peg", "<> ", "<>"))
    {
        PEG_ClearBlock(CCITT_SCCP_Pegs);

        sprintf(buf, "Clearing All ITU SCCP Pegs for  Now\n");
        DBC_AppendText(dbc, buf);

    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the configured stack information for itu sccp.
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
INTELLINET_SCCP_Commit_CCITT(FILE* fp)
{
    int count = 0;
    TRACE_Data* td = SCCP_CCITT_TraceData; 

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

    for (count = 0; count < (int)CCITT_SCCP_Timers.numTimers; count++)
    {
        fprintf(fp,"\t\t\t\t\t%s = \"%d\"\n",SCCP_CCITT_Timers[count],
                                             CCITT_SCCP_Timers.timers[count]);
    }

    fprintf(fp,"\t\t\t\t/>\n");
    fprintf(fp,"\t\t\t\t<BehaviorControl\n");
    fprintf(fp,"\t\t\t\t\tpropagate_SCMG = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_SCCP_Behaviors,
                                   SCCP_B_propagate_SCMG) == ITS_TRUE)? 
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\tuse_SCMG = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_SCCP_Behaviors,
                                   SCCP_B_use_SCMG) == ITS_TRUE)? 
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\tpropagate_ERR = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_SCCP_Behaviors,
                                   SCCP_B_propagate_ERR) == ITS_TRUE)? 
            "yes" : "no");
    fprintf(fp,"\t\t\t\t\tpropagate_IT = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_SCCP_Behaviors,
                                   SCCP_B_propagate_IT) == ITS_TRUE)? 
            "yes" : "no");
    fprintf(fp,"\t\t\t\t/>\n");

    return ITS_SUCCESS;
}
