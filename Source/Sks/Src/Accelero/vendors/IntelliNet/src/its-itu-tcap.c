/*********************************-*-C-*-************************************
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
 *  ID: $Id: its-itu-tcap.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $
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
 * LOG: Revision 8.14  2003/10/17 09:22:11  vjatti
 * LOG: set the trace levels to null. if not set
 * LOG:
 * LOG: Revision 8.13  2003/10/15 10:41:46  vjatti
 * LOG: Removed duplicate peg for error received
 * LOG:
 * LOG: Revision 8.12  2003/10/13 11:25:17  vjatti
 * LOG: removed unwanted pegs
 * LOG:
 * LOG: Revision 8.11  2003/10/07 10:29:43  vjatti
 * LOG: Corrected typos for MMLs.
 * LOG:
 * LOG: Revision 8.10  2003/10/06 04:59:09  vjatti
 * LOG: Removed printing of junk chars for ti_get_gen_cfg.
 * LOG: An extra string was being appended on to the output buffer.
 * LOG:
 * LOG: Revision 8.9  2003/07/22 15:43:46  mmiers
 * LOG: Warning removal.  Fix Windoze build.
 * LOG:
 * LOG: Revision 8.8  2003/07/16 11:56:59  vjatti
 * LOG: Warning removal with CC compiler.
 * LOG:
 * LOG: Revision 8.7  2003/07/16 08:29:35  vjatti
 * LOG: Changes for MML output display format.
 * LOG:
 * LOG: Revision 8.6  2003/07/03 11:40:17  vjatti
 * LOG: MML: Alarms & Pegs changes for PR6.4.
 * LOG:
 * LOG: Revision 8.5  2003/06/16 13:51:40  mmanikandan
 * LOG: Xml Persistency is added.
 * LOG:
 * LOG: Revision 8.4  2003/04/29 21:08:34  rsonak
 * LOG: Added GenerateLTID for Intellinet specific TID generation
 * LOG:
 * LOG: Revision 8.3  2003/04/16 05:35:08  yranade
 * LOG: Initialization Fixes.
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

#include <assert.h>

#undef ANSI
#undef CCITT
#define CCITT

#include <its.h>
#include <its_trace.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_thread_pool.h>
#include <its_mutex.h>
#include <its_assertion.h>

#include <dbc_serv.h>

#ident "$Id: its-itu-tcap.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"

#include <itu/tcap.h>

#include "tcap_intern.h"

TQUEUETRAN_Manager *__TCAP_CCITT_RcvQueue;

static ITS_CHAR *tcapPegStr[] =
{
    "TCAP_APP_MSG_SENT",
    "TCAP_APP_MSG_DISCARDED",
    "TCAP_APP_CMP_SENT",
    "TCAP_APP_CMP_DISCARDED",
    "TCAP_REMOTE_CMP_RCVD",
    "TCAP_REMOTE_CMP_DISCARDED",
    "TCAP_REMOTE_MSG_RCVD",
    "TCAP_REMOTE_UNKNOWN_MSG_RCVD",
    "TCAP_REMOTE_MSG_DISCARDED",
    "TCAP_ACTIVE_DIALOGUE",
    "TCAP_ACTIVATED_DIALOGUE",
    "TCAP_ACTIVE_TRANSACTIONS",
    "TCAP_ACTIVATED_TRANSACTIONS",
    "TCAP_PREARRANGED_END",
    "TCAP_REMOTE_UDT_RCVD",
    "TCAP_REMOTE_XUDT_RCVD",
    "TCAP_REMOTE_UDTS_RCVD",
    "TCAP_REMOTE_XUDTS_RCVD",
    "TCAP_REMOTE_LUDT_RCVD",
    "TCAP_REMOTE_LUDTS_RCVD",
    "TCAP_REMOTE_INVALID_SCCP_RCVD",
    "TCAP_REMOTE_SCCP_CLASS_0_RCVD",
    "TCAP_REMOTE_SCCP_CLASS_1_RCVD",
    "TCAP_REMOTE_UNI_RCVD",
    "TCAP_APP_UDT_SENT",
    "TCAP_APP_XUDT_SENT",
    "TCAP_APP_UDTS_SENT",
    "TCAP_APP_XUDTS_SENT",
    "TCAP_APP_LUDT_SENT",
    "TCAP_APP_LUDTS_SENT",
    "TCAP_APP_SCCP_CLASS_0_SENT",
    "TCAP_APP_SCCP_CLASS_1_SENT",
    "TCAP_APP_U_ABORT_TO_REMOTE_SENT",
    "TCAP_APP_UNI_SENT",
    "TCAP_P_ABORT_TO_REMOTE_SENT",
    "TCAP_P_ABORT_TO_APP_SENT",
    "TCAP_P_REJECT_TO_REMOTE_SENT",
    "TCAP_P_REJECT_TO_APP_SENT",
    "TCAP_REMOTE_U_ABORT_RCVD",
    "TCAP_REMOTE_P_ABORT_RCVD",
    "TCAP_LOCAL_CANCEL",
    "TCAP_DLG_SEND_TO_REMOTE_FAIL",
    "TCAP_DLG_SEND_TO_APP_FAIL",
    "TCAP_APP_U_REJECT_SENT",
    "TCAP_APP_INVOKE_L_SENT",
    "TCAP_APP_RESULT_L_SENT",
    "TCAP_APP_RESULT_NL_SENT",
    "TCAP_APP_ERROR_SENT",
    "TCAP_REMOTE_INVOKE_L_RCVD",
    "TCAP_REMOTE_RESULT_L_RCVD",
    "TCAP_REMOTE_RESULT_NL_RCVD",
    "TCAP_REMOTE_ERROR_RCVD",
    "TCAP_REMOTE_REJECT_RCVD",

/* ITU Specific ones */
    "TCAP_APP_INV_CLASS_1_SENT",
    "TCAP_APP_INV_CLASS_2_SENT",
    "TCAP_APP_INV_CLASS_3_SENT",
    "TCAP_APP_INV_CLASS_4_SENT",
    "TCAP_APP_SCCP_RET_ON_ERR_SENT",
    "TCAP_APP_BEGIN_SENT",
    "TCAP_REMOTE_BEGIN_RCVD",
    "TCAP_APP_CONT_SENT",
    "TCAP_APP_END_SENT",
    "TCAP_REMOTE_END_RCVD",
    "TCAP_REMOTE_R_REJECT_RCVD",
    "TCAP_REMOTE_U_REJECT_RCVD",
    "TCAP_REMOTE_CONT_RCVD",

/*ANSI specific */
    "TCAP_APP_QWOP_SENT",
    "TCAP_REMOTE_QWOP_RCVD",
    "TCAP_APP_QWIP_SENT",
    "TCAP_REMOTE_QWIP_RCVD",
    "TCAP_APP_RESP_SENT",
    "TCAP_REMOTE_RESP_RCVD",
    "TCAP_APP_CWOP_SENT",
    "TCAP_REMOTE_CWOP_RCVD",
    "TCAP_APP_CWIP_SENT",
    "TCAP_REMOTE_CWIP_RCVD",
    "TCAP_APP_INVOKE_NL_SENT",
    "TCAP_REMOTE_INVOKE_NL_RCVD",
    NULL
};

static ITS_CHAR* TCAP_CCITT_Timers[] =
{
    TCAP_REJECT_TIMEOUT_STRING,
    NULL
};

THREAD_RET_TYPE CCITT_TCAPThread(void *arg);

static void TCAP_Console_CCITT(DBC_Server *dbc, const char *cmdLine);

static ITS_THREAD   *tcapThread;

static ITS_BOOLEAN  started = ITS_FALSE;
static ITS_BOOLEAN  stopped = ITS_FALSE;

static int numThreads = 1;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method initializes the TCAP subsystem for use.
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
 *      If the subsystem is successfully initialized, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_TCAP_Initialize_CCITT(ITS_SS7_HANDLE handle)
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

    if ((__TCAP_CCITT_RcvQueue = TQUEUETRAN_CreateTransport("ITU-TCAP",
                                                            ITS_TCAP_CCITT_SRC,
                                                            ITS_TCAP_CCITT |
                                                            ITS_SCCP_CCITT |
                                                            ITS_SCCP_ANSI)) == NULL)
    {
        TCAP_CRITICAL(("TCAP_Initialize: couldn't create transport.\n"));

        /* TCAP failed to Intialize -  couldn't create transport. */
        TCAP_Alarm_CCITT(1413, __FILE__, __LINE__, NULL);

        started = ITS_FALSE;
        
        return (ITS_ENOTRANSPORT);
    }

    res = TRANSPORT_RES(__TCAP_CCITT_RcvQueue);
    name = TRANSPORT_NAME(__TCAP_CCITT_RcvQueue);

    ret = TCAP_Init_CCITT(res, name, TRANSPORT_SS7_INFO(__TCAP_CCITT_RcvQueue).linkInfo);
    if (ret != ITS_SUCCESS)
    {
        TQUEUETRAN_DeleteTransport(__TCAP_CCITT_RcvQueue);

        return (ret);
    }

    if (res != NULL)
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

    if ((tcapThread = (ITS_THREAD *)malloc(numThreads *
                                           sizeof(ITS_THREAD))) == NULL)
    {
        TCAP_CRITICAL(("TCAP_Initialize: couldn't create thread array.\n"));

        /* TCAP failed to Intialize -  couldn't create thread array. */
        TCAP_Alarm_CCITT(1413, __FILE__, __LINE__, NULL);

        TCAP_Term_CCITT(TRANSPORT_SS7_INFO(__TCAP_CCITT_RcvQueue).linkInfo);

        TQUEUETRAN_DeleteTransport(__TCAP_CCITT_RcvQueue);

        started = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    for (i = 0; i < numThreads; i++)
    {
        if (THREAD_CreateThread(&tcapThread[i], 0, CCITT_TCAPThread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            TCAP_CRITICAL(("TCAP_Init: Couldn't create TCAP thread.\n"));
            
            /* TCAP failed to Intialize -  couldn't create thread. */
            TCAP_Alarm_CCITT(1413, __FILE__, __LINE__, NULL);

            for (j = 0; j < i; j++)
            {
                THREAD_KillThread(&tcapThread[j]);

                THREAD_DeleteThread(&tcapThread[j]);
            }

            TCAP_Term_CCITT(TRANSPORT_SS7_INFO(__TCAP_CCITT_RcvQueue).linkInfo);

            TQUEUETRAN_DeleteTransport(__TCAP_CCITT_RcvQueue);

            free(tcapThread);

            started = ITS_FALSE;

            return (ITS_EBADTHREAD);
        }
    }

    /* Informational - TCAP Intialized Successfully. */
    TCAP_Alarm_CCITT(1414, __FILE__, __LINE__, NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_AddDoCommand(TCAP_Console_CCITT);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function terminates the TCAP subsystem.  Well behaved
 *      applications should call this function before exiting.
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
 *      If the subsystem is successfully terminated, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
INTELLINET_TCAP_Terminate_CCITT(ITS_SS7_HANDLE handle)
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

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_RemDoCommand(TCAP_Console_CCITT);
    }

    ITS_EVENT_INIT(&ev, ITS_TCAP_CCITT_SRC, 0);

    for (i = 0; i < numThreads; i++)
    {
        TRANSPORT_PutEvent(ITS_TCAP_CCITT_SRC, &ev);
    }

    for (i = 0; i < numThreads; i++)
    {
        THREAD_WaitForThread(&tcapThread[i], &status);

        THREAD_DeleteThread(&tcapThread[i]);
    }

    free(tcapThread);

    assert(__TCAP_CCITT_RcvQueue != NULL);

    TCAP_Term_CCITT(TRANSPORT_SS7_INFO(__TCAP_CCITT_RcvQueue).linkInfo);

    TQUEUETRAN_DeleteTransport(__TCAP_CCITT_RcvQueue);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is the entry point for the CCITT TCAP thread.
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
 *      TCAP function.
 *
 *  See Also:
 ****************************************************************************/
THREAD_RET_TYPE
CCITT_TCAPThread(void *arg)
{
    ITS_EVENT tcapEvent;
    ITS_BOOLEAN cont;

    if (sizeof(TCAP_INVOKE_ENTRY) > ITS_MAX_TIMER_CONTEXT)
    {
        TCAP_CRITICAL(("Structure overflow\n"));
        
        /* TCAP Aborting  - Structure overflow. */
        TCAP_Alarm_CCITT(1416, __FILE__, __LINE__, NULL);

        abort();
    }

    memset(&tcapEvent, 0, sizeof(ITS_EVENT));

    cont = ITS_TRUE;

    TRANSPORT_IS_ACTIVE(__TCAP_CCITT_RcvQueue) = ITS_TRUE;

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__TCAP_CCITT_RcvQueue))
                                                        (__TCAP_CCITT_RcvQueue,
                                                        &tcapEvent)
           == ITS_SUCCESS)
    {
        switch (tcapEvent.src)
        {
        case ITS_SCCP_SRC:
            TCAP_DEBUG(("TCAP_Main: process SCCP event.\n"));
            TCOHandleSCCPMsg_CCITT(&tcapEvent);
            break;

        case ITS_TCAP_CCITT_SRC:
            TCAP_CRITICAL(("TCAP_Main: termination event.\n"));

            TRANSPORT_IS_ACTIVE(__TCAP_CCITT_RcvQueue) = ITS_FALSE;

            cont = ITS_FALSE;
            break;

        case ITS_TIMER_SRC:
            TCAP_DEBUG(("TCAP_Main: process TIMER event.\n"));
            CCOHandleTimeout_CCITT(&tcapEvent);
            break;

        default:
            TCAP_DEBUG(("TCAP_Main: process APP event.\n"));

            /* we accept the message regardless.  This is dangerous, as
             * the user may not have registered their application for sending.
             */
            if (TCAP_MSG_TYPE(&tcapEvent) == ITS_TCAP_DLG)
            {
                DHAHandleAPPMsg_CCITT(&tcapEvent);
            }
            else if (TCAP_MSG_TYPE(&tcapEvent) == ITS_TCAP_CPT)
            {            
                CCOHandleAPPMsg_CCITT(&tcapEvent);
            }
            else
            {
                /* user sending funky stuff */
                TCAP_CRITICAL(("TCAP_Main: unrecognized event type.\n"));
                
                /* Received Unrecognized or Invalid Event. */
                TCAP_Alarm_CCITT(1417, __FILE__, __LINE__, NULL);
            }
            break;
        }
    }

    TRANSPORT_IS_ACTIVE(__TCAP_CCITT_RcvQueue) = ITS_FALSE;

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
TCAP_Console_CCITT(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    int ret;
    ITS_UINT i;

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "ti_get_gen_cfg", "TCAP Get General Config", "", ""))
    {
        TCAPGeneralCfg *cfg;
        cfg =  TCAP_GetGeneralCfg_CCITT();

        i = cfg->alarmLevel;

        switch(i)
        {
            case ALARM_LVL_CRIT :
                sprintf(buf, "\n    Alarm Level  CRITICAL\n");
            break;

            case ALARM_LVL_MAJOR :
                sprintf(buf, "\n    Alarm Level  MAJOR\n");
            break;

            case ALARM_LVL_MINOR :
                sprintf(buf, "\n    Alarm Level  MINOR\n");
            break;
            case ALARM_LVL_INFO :
                sprintf(buf, "\n    Alarm Level  INFO\n");
            break;

            case ALARM_LVL_OFF :
                sprintf(buf, "\n    Alarm Level  OFF\n");
            break;

            default :
                sprintf(buf, "\n    Alarm Level Not Set\n");
            break;
        }

        DBC_AppendText(dbc, buf);
        strcpy(buf, "\n    TCAP Trace -\n");
        DBC_AppendText(dbc, buf);

       if ( cfg->traceOn)
       {
           if (TRACE_IsLevelOn(TCAP_CCITT_TraceData,
                                    TCAP_TRACE_DEBUG))
           {
               strcpy(buf, "        Debug     = ");
               if(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (!(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      0)) &&
                   !(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      1)))
               {
                   strcpy(buf, "        Debug     =  null");
               }
           }
           else
           {
               strcpy(buf, "        Debug     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(TCAP_CCITT_TraceData,
                                    TCAP_TRACE_CRITICAL))
           {
               strcpy(buf, "        Critical  = ");
               if(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (!(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      0)) &&
                   !(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      1)))
               {
                   strcpy(buf, "        Critical  =  null");
               }
           }
           else
           {
               strcpy(buf, "        Critical  = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(TCAP_CCITT_TraceData,
                                    TCAP_TRACE_WARNING))
           {
               strcpy(buf, "        Warning   = ");
               if(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_WARNING,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_WARNING,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (!(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_WARNING,
                                      0)) &&
                   !(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_WARNING,
                                      1)))
               {
                   strcpy(buf, "        Warning   =  null");
               }
           }
           else
           {
               strcpy(buf, "        Warning   = null");
           }

           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(TCAP_CCITT_TraceData,
                                    TCAP_TRACE_ERROR))
           {
               strcpy(buf, "        Error     = ");
               if(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_ERROR,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_ERROR,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (!(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_ERROR,
                                      0)) &&
                   !(TRACE_IsOutputOn(TCAP_CCITT_TraceData,
                                      TCAP_TRACE_ERROR,
                                      1)))
               {
                   strcpy(buf, "        Error     =  null");
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
    }
    else if (DBC_Cmd(dbc, "ti_set_gen_cfg", "TCAP Set General Config", 
                      "<al> <tl>",
                     "<alarm level> <On / Off>"))

    {
        TCAPGeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType,
                     traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "\n   **** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n   Usage: ti_set_gen_cfg [CRITICAL/MAJOR/MINOR/INFO/OFF]\n");
            DBC_AppendText(dbc, buf);

            sprintf(buf, "\n          [CRITICAL/ERROR/WARNING/DEBUG] [stdout/file] [ON/OFF]\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n Note : The arguements are case insensitive (either in lower/upper case.\n");
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
            sprintf(buf, "\n   Invalid Alarm Level\n");
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
            sprintf(buf, "\n   Invalid Trace Level\n");
            DBC_AppendText(dbc, buf);
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, TCAP_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, TCAP_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, TCAP_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, TCAP_ERROR_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "\n   Invalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, TCAP_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, TCAP_FILE_STRING);
        }
        else
        {
            sprintf(buf, "\n   Invalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  TCAP_SetGeneralCfg_CCITT(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

        sprintf(buf, "\n *********** TCAP General Config Set*************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "ti_get_tmr", "TCAP Get Timers", 

                     "", ""))

    {
        int value = 0;
        if (TIMERS_GetTimerValue(&CCITT_TCAP_Timers, TCAP_T_reject))
        {
            value = TIMERS_GetTimerValue(&CCITT_TCAP_Timers, TCAP_T_reject);
        }

        sprintf(buf, "    TCAP_T_reject   <%d> \n", value);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "ti_set_tmr", "TCAP Set Timers", 
                     "<tr>", "<Treject>"))

    {
        int tr = 0;

        ret = sscanf(cmdLine, "%s %d", buf, &tr);

        if (ret != 2)
        {
            sprintf(buf, "\n   **** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n   Usage: ti_set_tmr <value> where value -> Timer value in seconds\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        TIMERS_SetTimerValue(&CCITT_TCAP_Timers, TCAP_T_reject, tr);

        sprintf(buf, "    TCAP_T_reject   Timer Set \n");
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "ti_get_behavior", "TCAP Get Behaviors", 

                     "", ""))

    {
        if (BEHAVIORS_GetBehavior(&CCITT_TCAP_Behaviors, TCAP_B_use_reserved_NI))
        {
            sprintf(buf, "    TCAP_B_use_reserved_NI    <yes> \n");
        }
        else
        {
            sprintf(buf, "    TCAP_B_use_reserved_NI    <no> \n");
        }
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "ti_set_behavior", "TCAP Set Behaviors", 
                     "<rni>", ""))

    {
        int rni;

        ret = sscanf(cmdLine, "%s %d", buf, &rni);

        if (ret != 2)
        {
            sprintf(buf, "\n   **** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n   Usage : ti_set_behavior <rni> - rni = 0/1. \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (rni)
        {
            BEHAVIORS_SetBehavior(&CCITT_TCAP_Behaviors, TCAP_B_use_reserved_NI, 
                                  ITS_TRUE);
        }
        else
        {
            BEHAVIORS_SetBehavior(&CCITT_TCAP_Behaviors, TCAP_B_use_reserved_NI, 
                                   ITS_FALSE);
        }

        sprintf(buf, "\n*******TCAP Behaviors Set*******\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "ti_get_peg", "Get Pegs", "<pg> ", "<Peg#> <>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT value;
        ITS_UINT pg = PEG_TCAP_NUM_PEGS;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
            sprintf(buf, "\n   **** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n   Usage: ti_get_peg <peg>  Pls see cmd $help ti_get_peg for PEGs list\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        for (i = 0; i < PEG_TCAP_NUM_PEGS; i++)
        {
            if ( strstr(pgName, tcapPegStr[i]))
            {
                pg = i;
                break;
            }
        }

        if (pg == PEG_TCAP_NUM_PEGS)
        {
            sprintf(buf, "\n   **** Invalid Peg Type *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\n   %s \n", pgName);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(CCITT_TCAP_Pegs, pg);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "ti_clr_peg", "Clear Peg", "<pg> ", "<Peg#> <>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT pg = PEG_TCAP_NUM_PEGS;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
             sprintf(buf, "\n   **** Invalid Command Arguments *******\n");
             DBC_AppendText(dbc, buf);
             sprintf(buf, "\n   Usage: ti_clr_peg <ALL/all/peg-type> Pls see cmd $help ti_get_peg for PEGs list\n");
             DBC_AppendText(dbc, buf);
             return;
        }
     
        if ( strstr(pgName, "ALL") || strstr(pgName, "all"))
        {
            PEG_ClearBlock(CCITT_TCAP_Pegs);

            sprintf(buf, "\n   Clearing All ITU TCAP Pegs \n");
            DBC_AppendText(dbc, buf);
        }
        else
        {
            for (i = 0; i < PEG_TCAP_NUM_PEGS; i++)
            {
                if ( strstr(pgName, tcapPegStr[i]))
                {
                    pg = i;
                    break;
                }
            }

            if (pg == PEG_TCAP_NUM_PEGS)
            {
                sprintf(buf, "\n   **** Invalid Peg Type *******\n");
                DBC_AppendText(dbc, buf);
                return;
            }

            sprintf(buf, "\n   Clearing the Pegs for %s \n", pgName);
            DBC_AppendText(dbc, buf);

            PEG_ClearPeg(CCITT_TCAP_Pegs, pg);
        }
    }
    else if (DBC_Cmd(dbc, "ti_set_local_ss", "TCAP Set Local Subsystem Entry", 
                     "<ssn>",
                     "<ssn>"))

    {
        TCAPSubSystemInfo info;
        ITS_UINT linkset = 0;
        SS7_LinkSetPtr lptr = NULL;
        int ssn;

        ret = sscanf(cmdLine, "%s %d", buf, &ssn);

        if (ret != 2)
        {
            sprintf(buf, "\n   **** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n   Usage: ti_set_local_ss <ssn>");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n          where ssn -> Local Subsystem Number to add value range 0-255 \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "\n   ********* Local Linkset 0 Not Configured********\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        
        info.pointcode = lptr->lpc;
        info.ni = lptr->ni;
        info.ssn = (ITS_OCTET)ssn;

        ret = TCAP_SetLocalSSEntry_CCITT(&info);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "Failed To Set TCAP Local Subsystem Entryt********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

         sprintf(buf, "********* TCAP Local Subsystem Entry Set********\n");
         DBC_AppendText(dbc, buf);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Generate LTID.
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
ITS_UINT
GenerateNewLTID_CCITT(ITS_UINT* nextLTid)
{
        (*nextLTid)--;

        return (*nextLTid);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the configured stack information for itu tcap.
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
INTELLINET_TCAP_Commit_CCITT(FILE* fp)
{
    int count = 0;
    TRACE_Data* td = TCAP_CCITT_TraceData;

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

    for (count = 0; count < (int)CCITT_TCAP_Timers.numTimers; count++)
    {
        fprintf(fp,"\t\t\t\t\t%s = \"%d\"\n",TCAP_CCITT_Timers[count],
                                             CCITT_TCAP_Timers.timers[count]);
    }

    fprintf(fp,"\t\t\t\t/>\n");
    fprintf(fp,"\t\t\t\t<BehaviorControl\n");
    fprintf(fp,"\t\t\t\t\tuse_reserved_NI = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&CCITT_TCAP_Behaviors,
                                   TCAP_B_use_reserved_NI) == ITS_TRUE)?
            "yes" : "no");
    fprintf(fp,"\t\t\t\t/>\n");

    return ITS_SUCCESS;
}
