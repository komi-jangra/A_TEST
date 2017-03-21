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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:17  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1  2005/06/02 06:54:35  yranade
 * LOG: Linux Kernel SCTP Integration as per ACC652-SDS-LKSC-V1.0.02.
 * LOG:
 *
 * ID: $Id: its_lksctp.c,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $
 *
 ****************************************************************************/

#ident "$Id: its_lksctp.c,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if defined(linux)
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#endif

#include <its_trace.h>
#include <its_sctp_trans.h>
#include <its_assertion.h>
#include <its_alarm.h>

#include <its_lksctp.h>


/* Note: Most of the IntelliNet Alarms are at management level.
 *        In our case Kernel takes care of it, so we will not handle them.
 *        This 'sctpAlarmLevel' is just plain won't work.  
 */
ITS_UINT sctpAlarmLevel = ALARM_LVL_OFF;


/*
 * Sctp Manager
 */
static LKSCTP_Manager manager;


/*
 * in reality this is MAX IP DATAGRAM size
 */
#define LKSCTP_MAX_BUFF_SIZE 0x00010000


/* 
 * trace 
 */
static TRACE_OutputInitializer fileCritTrace =
{
    SCTP_FILE_STRING,
    ITS_TRUE,
    SCTP_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    SCTP_FILE_STRING,
    ITS_TRUE,
    SCTP_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    SCTP_FILE_STRING,
    ITS_TRUE,
    SCTP_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    SCTP_FILE_STRING,
    ITS_TRUE,
    SCTP_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    SCTP_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    SCTP_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer SCTP_TraceMap[] =
{
    {SCTP_CRITICAL_STRING, ITS_TRUE,  3, 
          { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {SCTP_ERROR_STRING,    ITS_TRUE,  3, 
          { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {SCTP_WARNING_STRING,  ITS_TRUE,  3, 
          { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {SCTP_DEBUG_STRING,    ITS_FALSE, 3, 
          { &stdoutTrace, &fileDebugTrace, &syslogTrace } }
};

TRACE_Data* SCTP_TraceData = NULL;


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the LK-SCTP Manager
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
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Initialize the LK-SCTP
 *                             ID :: D0010             Manager
 ****************************************************************************/
static int
InitManager(LKSCTP_Manager *m)
{
    int i;

    if (MUTEX_CreateMutex(&m->gate, 0) != ITS_SUCCESS)
    {
        SCTP_ERROR(("Couldn't create gate.\n"));

        return (ITS_EBADMUTEX);
    }
 
    /*
     * Assocation-Id Hash Table Creation
     */
    if ((m->assocDb = HASH_CreateTable()) == NULL)
    {
        MUTEX_DeleteMutex(&m->gate);

        return (ITS_EINVALIDARGS);
    }

    m->queue = TQUEUETRAN_CreateTransport("SCTP",
                                          SCTP_MANAGER_INSTANCE,
                                          ITS_TRANSPORT_TQUEUE);

    if (m->queue == NULL)
    {   
        HASH_DeleteTable(m->assocDb);
  
        MUTEX_DeleteMutex(&m->gate);

        return (ITS_EINVALIDARGS);
    }

    DBC_AddDoCommand(LKSCTP_Console);
 
    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the LK-SCTP manager
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
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Destroy the LK-SCTP
 *                             ID :: D0130             Manager
 ****************************************************************************/
static void
DestroyManager(LKSCTP_Manager *m)
{
    TQUEUETRAN_DeleteTransport(m->queue);
  
    HASH_DeleteTable(m->assocDb);

    MUTEX_DeleteMutex(&m->gate);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize LK-SCTP trace settings.
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
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Initialize the LK-SCTP
 *                             ID :: D0010             trace
 ****************************************************************************/
static void
InitTraceSettings()
{
     /*
     * determine tracing from INI files
     */
    if (TRANSPORT_RES(manager.queue) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(manager.queue);
        char *name = TRANSPORT_NAME(manager.queue);

        /* critical */
        if (RESFILE_GetKeyValueOf(res, name, SCTP_TRACE_CRITICAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, SCTP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_CRITICAL_STRING,
                                           SCTP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_CRITICAL_STRING,
                                           SCTP_STDOUT_STRING, ITS_FALSE);

            }
 
            if (strstr(value, SCTP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_CRITICAL_STRING,
                                           SCTP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_CRITICAL_STRING,
                                           SCTP_FILE_STRING, ITS_FALSE);

            }
 
            if (strstr(value, SCTP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_CRITICAL_STRING,
                                           SCTP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_CRITICAL_STRING,
                                           SCTP_SYSLOG_STRING, ITS_FALSE);

            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                          SCTP_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                          SCTP_CRITICAL_STRING, ITS_FALSE);
            }
        }

        /* error */
        if (RESFILE_GetKeyValueOf(res, name, SCTP_TRACE_ERROR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, SCTP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_ERROR_STRING,
                                           SCTP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_ERROR_STRING,
                                           SCTP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, SCTP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_ERROR_STRING,
                                           SCTP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_ERROR_STRING,
                                           SCTP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, SCTP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_ERROR_STRING,
                                           SCTP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_ERROR_STRING,
                                           SCTP_SYSLOG_STRING, ITS_FALSE);

            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                          SCTP_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                          SCTP_ERROR_STRING, ITS_FALSE);
            }
        }

        /* warning */
        if (RESFILE_GetKeyValueOf(res, name, SCTP_TRACE_WARNING_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, SCTP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_WARNING_STRING,
                                           SCTP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_WARNING_STRING,
                                           SCTP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, SCTP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_WARNING_STRING,
                                           SCTP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_WARNING_STRING,
                                           SCTP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, SCTP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_WARNING_STRING,
                                           SCTP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_WARNING_STRING,
                                           SCTP_SYSLOG_STRING, ITS_FALSE);

            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                          SCTP_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                          SCTP_WARNING_STRING, ITS_FALSE);
            }
        }
        /* debug */
        if (RESFILE_GetKeyValueOf(res, name, SCTP_TRACE_DEBUG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, SCTP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_DEBUG_STRING,
                                           SCTP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_DEBUG_STRING,
                                           SCTP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, SCTP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_DEBUG_STRING,
                                           SCTP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_DEBUG_STRING,
                                           SCTP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, SCTP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_DEBUG_STRING,
                                           SCTP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                           SCTP_DEBUG_STRING,
                                           SCTP_SYSLOG_STRING, ITS_FALSE);

            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                          SCTP_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                          SCTP_DEBUG_STRING, ITS_FALSE);
            }
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Commiting the configuration in the XML file.
 *
 *  Input Parameters:
 *      FILE* fp - File Pointer to commit.
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
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Commits XML file.
 *                             ID :: D0010             
 ****************************************************************************/
static int
LKSCTP_Commit(FILE* fp)
{
    fprintf(fp, "\t\t<SCTP>\n");

    if (SCTP_TraceData != NULL)
    {
        fprintf(fp, "\t\t\t<SigtranTrace>\n");
        if (TRACE_IsLevelOn(SCTP_TraceData,
            SCTP_TRACE_CRITICAL))
        {
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_CRITICAL, 0))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_CRITICAL, 1))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_CRITICAL, 2))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(SCTP_TraceData,
            SCTP_TRACE_ERROR))
        {
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_ERROR, 0))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_ERROR, 1))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_ERROR, 2))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(SCTP_TraceData,
            SCTP_TRACE_WARNING))
        {
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_WARNING, 0))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_WARNING, 1))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_WARNING, 2))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(SCTP_TraceData,
            SCTP_TRACE_DEBUG))
        {
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_DEBUG, 0))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_DEBUG, 1))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(SCTP_TraceData,
                SCTP_TRACE_DEBUG, 2))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"syslog\" />\n");
            }
        }
        fprintf(fp, "\t\t\t</SigtranTrace>\n");
    }

    fprintf(fp, "\t\t</SCTP>\n\n");
    return ITS_SUCCESS;
}


/*
 * hash table.  PKey is (lport << 16) | rport).  Within that,
 * assocId *MUST* be unique.
 */
#define SCTP_RID_PORT   1

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Adds association Id to hash table.
 *
 *  Input Parameters:
 *      struct sockaddr *remote - ip address of remote
 *        sctp_assoc_t  assocId - Assoc Id to add
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
 *
 *  See Also:
 *     LKSCTP_RecvMsg()
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Inserts assoc id
 *                                           
 ****************************************************************************/
static ITS_UINT 
AddAssocId(struct sockaddr *remote, sctp_assoc_t assocId)
{
    ITS_UINT ctxt;
    ITS_UINT i;
    SCTP_HashEntry *ent, *add;
    struct sockaddr_in *to;

    to = (struct sockaddr_in*)remote;  
 
    /* Get raddr from struct sockaddr *remote */
    unsigned long raddr = ntohl(to->sin_addr.s_addr); 

    /* Get rport from struct sockaddr *remote */ 
    ITS_USHORT rport = ntohs(to->sin_port);
 
    /* Get local port from LKSCTP Manager */
    ITS_USHORT lport = GetLocalPort(); 
    
    ctxt = (lport << 16) | rport;

    SCTP_DEBUG(("LKSCTP_AddAssocId: Lport = %d, "
                 "Remote Ip:Port = %d.%d.%d.%d:%d:, Aid = %d\n",
                 lport,
                 (int)((raddr>>24) & 0x000000ff),
                 (int)((raddr>>16) & 0x000000ff),
                 (int)((raddr>>8) & 0x000000ff),
                 (int)(raddr & 0x000000ff),
                 rport,
                 assocId));

    /* See if we already have this */
    ent = NULL;
    if (HASH_FindEntry(manager.assocDb, SCTP_RID_PORT, ctxt,
                       (ITS_POINTER *)&ent) == ITS_SUCCESS)
    {
        SCTP_HashEntry *tmp = ent;

        while (tmp != NULL)
        {
            to = (struct sockaddr_in*)&tmp->assocDb->remote;

            if (tmp->assocDb->localPort == lport &&
                ntohl(to->sin_addr.s_addr) == raddr &&
                ntohs(to->sin_port) == rport &&
                tmp->assocDb->assocId == assocId)
            {
                SCTP_DEBUG(("AddAssocId: already exists?\n"));

                return (NULL);
            }
            
            tmp = tmp->next;
        }
    }
    else
    {
        ent = NULL;
    }

    /* ok, create it, link it in if necessary */
    add = (SCTP_HashEntry *)calloc(1, sizeof(SCTP_HashEntry));

    if (add == NULL)
    {
        SCTP_ERROR(("AddAssocId: Out of memory.\n"));

        return (NULL);
    }

    if (ent)
    {
        add->next = ent->next;
        ent->next = add;
    }

    add->assocDb = (LKSCTP_AssocDb *)calloc(1, sizeof(LKSCTP_AssocDb));

    if (add->assocDb == NULL)
    {
        SCTP_ERROR(("AddAssocId: Out of memory.\n"));

        free(add);

        return (NULL);
    }

    /* Upadate assocDb for creation of this assocId */
    add->assocDb->localPort = lport;
    memcpy(&add->assocDb->remote, remote, sizeof(struct sockaddr_in));
    add->assocDb->assocId = assocId;

    /* hash it */
    SCTP_DEBUG(("AddAssocId: Add %d %08x %p\n", SCTP_RID_PORT, ctxt, add));

    if (ent == NULL &&
        HASH_AddEntry(manager.assocDb, SCTP_RID_PORT, ctxt,
                      (ITS_POINTER)add) != ITS_SUCCESS)
    {
        SCTP_ERROR(("AddAssocId: Couldn't hash entry.\n"));

        free(add->assocDb);
        
        free(add);

        return (NULL);
    }

#if 0
    /* Verify */
    ent = NULL;
    if (HASH_FindEntry(manager.assocDb, SCTP_RID_PORT, ctxt,
                       (ITS_POINTER *)&ent) == ITS_SUCCESS)
    {
        SCTP_HashEntry *tmp = ent;
        unsigned long x;

        while (tmp != NULL)
        {
            to = (struct sockaddr_in*)&tmp->assocDb->remote;

            x = ntohl(to->sin_addr.s_addr);

            printf("Lport = %d, Remote Ip:Port = %d.%d.%d.%d:%d:, Aid = %d\n",
                    tmp->assocDb->localPort,
                    (int)((x>>24) & 0x000000ff),
                    (int)((x>>16) & 0x000000ff),
                    (int)((x>>8) & 0x000000ff),
                    (int)(x & 0x000000ff),
                    ntohs(to->sin_port),
                    tmp->assocDb->assocId);
  
            tmp = tmp->next;
        }
    }
    else
    {
        SCTP_ERROR(("AddAssocId... ADD ERROR\n"));
    }
#endif
    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *        Removes association Id to hash table.
 *
 *  Input Parameters:
 *      struct sockaddr *remote - ip address of remote
 *        sctp_assoc_t  assocId - Assoc Id to remove
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
 *
 *  See Also:
 *    LKSCTP_RecvMsg()
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Deletes assoc id
 *
 ****************************************************************************/
static int 
RemoveAssocId(struct sockaddr *remote, sctp_assoc_t assocId)
{
    ITS_UINT ctxt;
    ITS_UINT i;
    SCTP_HashEntry *ent, **lst, *tmp;

    struct sockaddr_in *to;
 
    to = (struct sockaddr_in*)remote;

    /* Get raddr from struct sockaddr *remote */
    unsigned long raddr = ntohl(to->sin_addr.s_addr);

    /* Get rport from struct sockaddr *remote */
    ITS_USHORT rport = ntohs(to->sin_port);

    /* Get local port from LKSCTP Manager */
    ITS_USHORT lport = GetLocalPort();

    ctxt = (lport << 16) | rport;

    SCTP_DEBUG(("RemoveAssocId: Lport = %d, "
                 "Remote Ip:Port = %d.%d.%d.%d:%d:, Aid = %d\n",
                 lport,
                 (int)((raddr>>24) & 0x000000ff),
                 (int)((raddr>>16) & 0x000000ff),
                 (int)((raddr>>8) & 0x000000ff),
                 (int)(raddr & 0x000000ff),
                 rport,
                 assocId));

    ent = NULL;

    if (HASH_FindEntry(manager.assocDb, SCTP_RID_PORT, ctxt,
                       (ITS_POINTER *)&ent) != ITS_SUCCESS)
    {
        SCTP_ERROR(("No RemoveAssocId entry in table\n"));

        return;
    }

    for (lst = &ent; *lst != NULL; )
    {
        to = (struct sockaddr_in*) &((*lst)->assocDb->remote);
  
        if (((*lst)->assocDb->localPort == lport) &&
            (ntohl(to->sin_addr.s_addr) == raddr) && 
            (ntohs(to->sin_port) == rport) &&
            ((*lst)->assocDb->assocId == assocId))
        {
            tmp = (*lst)->next;

            free(*lst);

            *lst = tmp;

            break;
        }
        else
        {
             lst = &(*lst)->next;
        }
    }

    if (ent == NULL)
    {
        HASH_DeleteEntry(manager.assocDb, SCTP_RID_PORT, ctxt);
    }
    else
    {
        HASH_AddEntry(manager.assocDb, SCTP_RID_PORT, ctxt, (ITS_POINTER)ent);
    }

#if 0
    /* Verify */
    ent = NULL;
    if (HASH_FindEntry(manager.assocDb, SCTP_RID_PORT, ctxt,
                       (ITS_POINTER *)&ent) == ITS_SUCCESS)
    {
        SCTP_HashEntry *tmp = ent;
        unsigned long x;

        while (tmp != NULL)
        {
            to = (struct sockaddr_in*)&tmp->assocDb->remote;

            x = ntohl(to->sin_addr.s_addr);

            printf("Lport = %d, Remote Ip:Port = %d.%d.%d.%d:%d:, Aid = %d\n",
                       tmp->assocDb->localPort,
                       (int)((x>>24) & 0x000000ff),
                       (int)((x>>16) & 0x000000ff),
                       (int)((x>>8) & 0x000000ff),
                       (int)(x & 0x000000ff),
                       ntohs(to->sin_port),
                       tmp->assocDb->assocId);

            tmp = tmp->next;
        }
    }
    else
    {
        SCTP_ERROR(("RemoveAssocId: No Content\n"));
    }
#endif
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *        Finds association Id.
 *
 *  Input Parameters:
 *      struct sockaddr *remote - ip address of remote
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
 *
 *  See Also:
 *    LKSCTP_Ioctl()
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Finds assoc id given  
 *                                                     ip addr
 ****************************************************************************/
static sctp_assoc_t
FindAssocId(struct sockaddr_in *remote)
{
    ITS_UINT ctxt;
    ITS_UINT i;
    SCTP_HashEntry *ent, **lst, *tmp;

    struct sockaddr_in *to;

    to = (struct sockaddr_in*)remote;

    /* Get raddr from struct sockaddr *remote */
    unsigned long raddr = ntohl(to->sin_addr.s_addr);    

    /* Get rport from struct sockaddr *remote */
    ITS_USHORT rport = ntohs(to->sin_port);

    /* Get local port from LKSCTP Manager */
    ITS_USHORT lport = GetLocalPort();

    ctxt = (lport << 16) | rport;

    SCTP_DEBUG(("FindAssocId: Lport = %d, "
                 "Remote Ip:Port = %d.%d.%d.%d:%d\n",
                 lport,
                 (int)((raddr>>24) & 0x000000ff),
                 (int)((raddr>>16) & 0x000000ff),
                 (int)((raddr>>8) & 0x000000ff),
                 (int)(raddr & 0x000000ff),
                 rport));

    ent = NULL;

    if (HASH_FindEntry(manager.assocDb, SCTP_RID_PORT, ctxt,
                       (ITS_POINTER *)&ent) != ITS_SUCCESS)
    {
        SCTP_ERROR(("No AssocId entry in table\n"));

        return -1;
    }

    for (lst = &ent; *lst != NULL; )
    {
        to = (struct sockaddr_in*)&((*lst)->assocDb->remote);

        if (((*lst)->assocDb->localPort == lport) &&
            (ntohl(to->sin_addr.s_addr) == raddr) && 
            (ntohs(to->sin_port) == rport))
        {
            SCTP_DEBUG(("FindAssocId: Assoc Id found %d\n",
                (*lst)->assocDb->assocId));
   
            return((*lst)->assocDb->assocId);
        }
        else
        {
             lst = &(*lst)->next;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      set local port to LK-SCTP Manager.
 *
 *  Input Parameters:
 *      localPort - Local Port to add.
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
 *
 *  See Also:
 *    LKSCTP_Bind()
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Sets local port
 *                                                     in LK-SCTP manager
 ****************************************************************************/
static int 
SetLocalPort(int localPort)
{
    SCTP_DEBUG(("SetLocalPort...LPort = %d\n", ntohs(localPort)));

    if (MUTEX_AcquireMutex(&manager.gate) != ITS_SUCCESS)
    {
        SCTP_ERROR(("Failed to acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }
    
    manager.localPort = ntohs(localPort);

    if (MUTEX_ReleaseMutex(&manager.gate) != ITS_SUCCESS)
    {
         SCTP_ERROR(("Failed to release mutex.\n"));

         return (ITS_EBADMUTEX);
    }
    return (ITS_SUCCESS);
}   

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Gets local port from SCTP Manager.
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
 *      Local port.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Gets local port 
 *                                                     from LK-SCTP Manager
 ****************************************************************************/
static int
GetLocalPort()
{
    int lport;

    SCTP_DEBUG(("GetLocalPort\n"));

    if (MUTEX_AcquireMutex(&manager.gate) != ITS_SUCCESS)
    {
        SCTP_ERROR(("Failed to acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    lport = manager.localPort;

    if (MUTEX_ReleaseMutex(&manager.gate) != ITS_SUCCESS)
    {
         SCTP_ERROR(("Failed to release mutex.\n"));

         return (ITS_EBADMUTEX);
    }

    SCTP_DEBUG(("GetLocalPort... Lport = %d\n", lport));

    return (lport);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Get General Configuration of LK-SCTP.
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
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Gets general conf
 *                             ID :: D0120             
 ****************************************************************************/
static LKSCTPGeneralCfg*
LKSCTP_GetGeneralCfg()
{
    LKSCTPGeneralCfg *ret;

    ret = calloc(1, sizeof(LKSCTPGeneralCfg));
    if (ret == NULL)
    {
        return (NULL);
    }

    ret->traceOn = (TRACE_IsLevelOn(SCTP_TraceData,
                                    SCTP_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_DEBUG,
                                      0) ||
                     TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_DEBUG,
                                      1) ||
                     TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_DEBUG,
                                      2))) ||
                   (TRACE_IsLevelOn(SCTP_TraceData,
                                    SCTP_TRACE_WARNING) &&
                    (TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_WARNING,
                                      0) ||
                     TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_WARNING,
                                      1) ||
                     TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_WARNING,
                                      2))) ||
                   (TRACE_IsLevelOn(SCTP_TraceData,
                                    SCTP_TRACE_ERROR) &&
                    (TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_ERROR,
                                      0) ||
                     TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_ERROR,
                                      1) ||
                     TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_ERROR,
                                      2))) ||
                   (TRACE_IsLevelOn(SCTP_TraceData,
                                    SCTP_TRACE_CRITICAL) &&
                    (TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_CRITICAL,
                                      0) ||
                     TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_CRITICAL,
                                      1) ||
                     TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_CRITICAL,
                                      2)));
    ret->alarmLevel = sctpAlarmLevel;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Set General Configuration of LK-SCTP.
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
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Sets General Conf
 *                             ID :: D0120             
 ****************************************************************************/
static int
LKSCTP_SetGeneralCfg(LKSCTPGeneralCfg *data)
{
    sctpAlarmLevel = data->alarmLevel;

    if (strstr(data->traceType, "all") != NULL)
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                       SCTP_CRITICAL_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                      SCTP_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                       SCTP_ERROR_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                      SCTP_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                       SCTP_WARNING_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                      SCTP_WARNING_STRING, ITS_TRUE);


            TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                       SCTP_DEBUG_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                      SCTP_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                       SCTP_CRITICAL_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                       SCTP_ERROR_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                       SCTP_WARNING_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                       SCTP_DEBUG_STRING,
                                       data->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(SCTP_TraceData,
                                      data->traceType, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(SCTP_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_FALSE);
        }
    }

    return (ITS_SUCCESS);
}



/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Open an SCTP socket.
 *
 *  Input Parameters:
 *      af - the address family (AF_INET only)
 *      t - the type (stream or datagram)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      the socket descriptor.  ITS_INVALID_SRC indicates an error.
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Opens LK-SCTP socket
 *                             ID :: D0020             
 ****************************************************************************/
SCTPDLLAPI ITS_USHORT
LKSCTP_Socket(int af, int t)
{
    int sd;
    struct sctp_event_subscribe event;

    int    dummy = 1;          /* for socket option */
    struct linger linger;      /* for set linger */    
    
    SCTP_DEBUG(("LKSCTP_Socket... Creating socket\n"));

    if ((sd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP)) == -1) 
    {
        SCTP_ERROR(("Couldn't create transport\n"));        

        return (ITS_INVALID_SRC);
    }

    /* Enable all notifications and events */
    bzero(&event, sizeof(struct sctp_event_subscribe));

    event.sctp_data_io_event          = 1;
    event.sctp_association_event      = 1;
    event.sctp_address_event          = 1;
    event.sctp_send_failure_event     = 1;
    event.sctp_peer_error_event       = 1;
    event.sctp_shutdown_event         = 1;
    event.sctp_partial_delivery_event = 1;
    event.sctp_adaption_layer_event   = 1;

    if (setsockopt(sd, IPPROTO_SCTP, SCTP_EVENTS, &event, sizeof(event)) < 0)
    {
        SCTP_ERROR(("Couldn't set SCTP_EVENTS\n"));

        return (ITS_INVALID_SRC);
    }

#if 0
    TODO: Check if Linger/Reuseaddr needs to be set 
    Set linger on, to 0 time 
    linger.l_onoff = 1;
    linger.l_linger = 0;
    setsockopt(sd, SOL_SCTP, SO_LINGER,
               (char *)&linger, sizeof(struct linger));

    Set reuseaddr socket option  
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));
#endif    

    return (sd);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Bind a local port to this socket
 *
 *  Input Parameters:
 *      sd - the socket
 *      who - the ip address and port to bind
 *      wlen - the length of socket address   
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0 on success.  Any other return means an error
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Binds local ip & port
 *                             ID :: D0030             
 ****************************************************************************/
SCTPDLLAPI int
LKSCTP_Bind(ITS_USHORT sd, SOCK_AddrStore *who, int wlen)
{
    int i;

    struct sockaddr_in locals[1];

    SCTP_DEBUG(("LKSCTP_Bind... Binding to local address\n"));

    locals[0] = *(struct sockaddr_in *)who;

    locals[0].sin_family = AF_INET; 

    /*  
     * Got local port, update LKSCTP_Manager
     */
    SCTP_DEBUG(("LKSCTP_Bind... localport = %d\n", ntohs(locals[0].sin_port)));
    SetLocalPort(locals[0].sin_port);
    
    if (sctp_bindx(sd, (struct sockaddr *)locals, 1, SCTP_BINDX_ADD_ADDR) == -1)
    {
        SCTP_ERROR(("Bind Failure: Error No = %d\n", errno));

        return (ITS_ENOTFOUND);
    }

    /* TODO: Check to change the permission bits on the socket */

    return (ITS_SUCCESS);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *       Allow new associations to be accepted
 *
 *  Input Parameters:
 *      sd - the socket
 *      backlog - the listen depth
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0 on success.  Any other return indicates an error
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Listens for new 
 *                             ID :: D0040             association
 ****************************************************************************/
SCTPDLLAPI int
LKSCTP_Listen(ITS_USHORT sd, int backlog)
{
    SCTP_DEBUG(("LKSCTP_Listen... Listening for new association\n"));

    /* TODO: Check Set up a listen queue */
    if (listen(sd, backlog) < 0)
    {
        SCTP_ERROR(("Listen Failure\n"));
        
        return (ITS_ELISTENFAIL);
    }      

    return (ITS_SUCCESS); 

}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Accept a connection on a socket
 *
 *  Input Parameters:
 *      sd - the socket
 *
 *  Input/Output Parameters:
 *      who  - the entity to connect to (datagram) or the entity
   *           connecting (stream)
 *      wlen - length of who
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0 on success.  Any other return code indicates an error
 *
 *  Notes:
 *      This just plain won't work.  In TCP, this works by having accept
 *      create another socket on a different port, and assigning the port
 *      to the remote's current tuple with the accept port.  How is this
 *      supposed to work in SCTP?  How would the initiator "know" which
 *      dest the INIT-ACK is in relation to?
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Accepts new association
 *                             ID :: D0050             
 ****************************************************************************/
SCTPDLLAPI ITS_USHORT
LKSCTP_Accept(ITS_USHORT sd, SOCK_AddrStore *who, int *wlen)
{
    SCTP_DEBUG(("LKSCTP_Accept\n"));

    return (ITS_SUCCESS);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      connect to a remote
 *
 *  Input Parameters:
 *      sd - the socket
 *      who - the entity to connect to
 *      wlen - length of who
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0 indicates success.  Any other return indicates an error
 *
 *  Notes:
 *      I like this, but the draft says only for connection oriented.
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Connects to remote
 *                             ID :: D0060             
 ****************************************************************************/
SCTPDLLAPI int
LKSCTP_Connect(ITS_USHORT sd, SOCK_AddrStore *who, int wlen)
{
    struct sockaddr_in local = *(struct sockaddr_in *)who;

    local.sin_family = AF_INET;

    SCTP_DEBUG(("LKSCTP_Connect... Connecting to the remote\n"));

    if (connect(sd, (struct sockaddr_in *)&local, sizeof(local)) < 0)
    {
        SCTP_ERROR(("Connect Failure\n"));

        return (ITS_ELISTENFAIL);
    }
   
    return (ITS_SUCCESS);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Retrive MIB Information
 *
 *  Input Parameters:
 *      sd - the socket
 *      which - Index to MIB info.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      data - Filled with requested information.
 *
 *  Return Value:
 *      0 indicates success.  Any other value indicates an error
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Gets MIB Info
 *                             ID :: D0120             
 ****************************************************************************/
SCTPDLLAPI int
LKSCTP_GetMIBInfo(ITS_USHORT sd, int which, SCTP_API_MIB_DATA *data)
{
    /* TODO
       All the MIB Info are at SCTP management level and
       cannot be accessable at Kernel level!
     */ 
   
    return (ITS_SUCCESS);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Set MIB data allowed by SCTP MIB Document
 *
 *  Input Parameters:
 *      sd - the socket
 *      which - Index to MIB info.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0 indicates success.  Any other value indicates an error
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Sets MIB Info
 *                             ID :: D0120             
 ****************************************************************************/
SCTPDLLAPI int
LKSCTP_SetMIBInfo(ITS_USHORT sd, int which, SCTP_API_MIB_DATA *data)
{
    /* TODO
       All the MIB Info are at SCTP management level and
       cannot be accessable at Kernel level!
     */

    return (ITS_SUCCESS);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *     SCTP MML Handler
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
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Handles LK-SCTP MMLs 
 *                             ID :: D0120             
 ****************************************************************************/
void
LKSCTP_Console(DBC_Server *dbc, const char *cmdLine)
{
    SCTP_DEBUG(("LKSCTP_Console\n"));

    ITS_CHAR buf[ITS_PATH_MAX];
    ITS_INT ret = ITS_SUCCESS;
    ITS_UINT i;

    TRANSPORT_Control *tc = NULL;
    SCTP_API_MIB_DATA* data = NULL;

    if (DBC_Cmd(dbc, "s_get_gen_cfg", "SCTP Get General Config", "", ""))
    {
        LKSCTPGeneralCfg *cfg;
        cfg =  LKSCTP_GetGeneralCfg();

        sprintf(buf, "*********** SCTP General Config *************\n");
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

        strcpy(buf, "    SCTP Trace -\n");
        DBC_AppendText(dbc, buf);

        if ( cfg->traceOn)
        {
            if (TRACE_IsLevelOn(SCTP_TraceData, SCTP_TRACE_DEBUG))
            {
                strcpy(buf, "        Debug     = ");
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_DEBUG, 0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_DEBUG, 1))
                {
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_DEBUG, 2))
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

            if (TRACE_IsLevelOn(SCTP_TraceData, SCTP_TRACE_CRITICAL))
            {
                strcpy(buf, "        Critical  = ");
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_CRITICAL, 0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_CRITICAL, 1))
                {
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_CRITICAL, 2))
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

            if (TRACE_IsLevelOn(SCTP_TraceData, SCTP_TRACE_WARNING))
            {
                strcpy(buf, "        Warning   = ");
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_WARNING, 0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_WARNING, 1))
                {
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_WARNING, 2))
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

            if (TRACE_IsLevelOn(SCTP_TraceData, SCTP_TRACE_ERROR))
            {
                strcpy(buf, "        Error     = ");
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_ERROR, 0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(SCTP_TraceData,
                                      SCTP_TRACE_ERROR, 1))
                {
                    strcat(buf, " file");
                } 
                if (TRACE_IsOutputOn(SCTP_TraceData, SCTP_TRACE_ERROR, 2))
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

        sprintf(buf, "*********** End of SCTP General Config *************\n");
        DBC_AppendText(dbc, buf);
     }
     else if (DBC_Cmd(dbc, "s_set_gen_cfg", "SCTP Set General Config",
                      "<al> <tl>", "<alarm level> <On / Off>"))
     {
         LKSCTPGeneralCfg cfg;
         char alarmLevel[ITS_PATH_MAX];
         char traceOn[ITS_PATH_MAX];
         char traceType[ITS_PATH_MAX];
         char traceOutput[ITS_PATH_MAX];

         ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType,
                      traceOutput, traceOn);

         if (ret != 5)
         {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: s_set_gen_cfg <alarmlevel> <tracetype> "
                          "<trOutput> <On/Off>\n");
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
             strcpy(cfg.traceType, SCTP_CRITICAL_STRING);
         }
         else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
         {
            strcpy(cfg.traceType, SCTP_DEBUG_STRING);
         }
         else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
         {
             strcpy(cfg.traceType, SCTP_WARNING_STRING);
         }
         else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
         {
             strcpy(cfg.traceType, SCTP_ERROR_STRING);
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
             strcpy(cfg.traceOutput, SCTP_STDOUT_STRING);
         }
         else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
         {
             strcpy(cfg.traceOutput, SCTP_FILE_STRING);
         }
         else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
         {
             strcpy(cfg.traceOutput, SCTP_SYSLOG_STRING);
         }
         else
         {
             sprintf(buf, "Invalid Trace Output\n");
             DBC_AppendText(dbc, buf);
             return;
         }

         ret =  LKSCTP_SetGeneralCfg(&cfg);
         if (ret != ITS_SUCCESS)
         {
             sprintf(buf, "\n********* SCTP Set Gen Cfg Failed***********\n");
             DBC_AppendText(dbc, buf);
             return;
         }

        sprintf(buf, "*********** SCTP General Config Set*************\n");
        DBC_AppendText(dbc, buf);

     }
     else if (DBC_Cmd(dbc, "s_get_gen_peg", "SCTP Get Peg Counts",
                     "<transportID> <PegID> ", " "))
     {
        ITS_INT pegid;
        ITS_UINT trid;
        ITS_INT sockId;
        ITS_CHAR trash[ITS_PATH_MAX];
        char pgName[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %x %s %s", buf, &trid, pgName, trash);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid number of parameters ****\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "Usage: s_get_gen_peg <transportID> <PegID>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        /*
         * lock the transport manager as other thead may be deleting
         * the transport
         */
        ret = TRANSPORT_LockManager();
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("SCTP_Console: Failed to lock TRANSPORT Manager "
                             "ret = %d\n", ret));
            return;
        }

        tc = TRANSPORT_FindTransportNoLock(trid);
        if (tc == NULL)
        {
            sprintf(buf, "\n**** Invalid Transport Id ****\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get transport id run command u_asptbl\n");
            DBC_AppendText(dbc, buf);
            TRANSPORT_UnlockManager();
            return;
        }

        /*
         * Not sure why that is ?
         */
        if (!strstr(tc->transport.name, "ASP") &&
            !strstr(tc->transport.name, "SCTP"))
        {
            sprintf(buf, "\n**** Invalid Transport Id ****\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get transport id run command u_asptbl\n");
            DBC_AppendText(dbc, buf);
            TRANSPORT_UnlockManager();
            return;
        }

        sockId = SOCKTRAN_SOURCE(tc)->socket;
        data = calloc(1, sizeof(SCTP_API_MIB_DATA));

        memcpy(&data->addr, SOCKTRAN_CONNECT(tc)->addr,
                                            SOCKTRAN_CONNECT(tc)->asize);
 
        pegid = atoi(pgName);

        ret = LKSCTP_GetMIBInfo(sockId, pegid, data);

        if (ret == ITS_EINVCHOICE)
        {
      	    sprintf(buf, "Invalid peg id\n");
            DBC_AppendText(dbc, buf);

            sprintf(buf, "To get valid peg id do help <s_get_gen_peg>\n");
            DBC_AppendText(dbc, buf);

            TRANSPORT_UnlockManager();
            free(data);
            return;
        }

	switch (pegid)
        {
        /* State statistics */
        case SCTP_MIB_CURR_ESTAB:
        case SCTP_MIB_ACTIVE_ESTAB:
        case SCTP_MIB_ABORTED:
        case SCTP_SHUTDOWNS:
        case SCTP_MIB_GEN_STATES:
            sprintf(buf, "\nCurrently Not Supported!\n");
            DBC_AppendText(dbc, buf);
            break;

        /* General statistics */
        case SCTP_MIB_OOB:
        case SCTP_MIB_SENT_CHUNKS:
        case SCTP_MIB_REC_CHUNKS:
        case SCTP_MIB_OO_SENT_CHUNKS:
        case SCTP_MIB_OO_REC_CHUNKS:
        case SCTP_MIB_FRAG_DG:
        case SCTP_MIB_REASMB_DG:
        case SCTP_MIB_GEN_STATISTICS:
            sprintf(buf, "\nCurrently Not Supported!\n");
            DBC_AppendText(dbc, buf);
            break;

        /* Association statistics */
        case SCTP_MIB_T1_EXPIRED:
        case SCTP_MIB_T2_EXPIRED:
        case SCTP_MIB_RETR_CHUNKS:
        case SCTP_MIB_CKSUM_ERROR:
        case SCTP_MIB_ASSOC_STATISTICS:
            sprintf(buf, "\nCurrently Not Supported!\n");
            DBC_AppendText(dbc, buf);
            break;

        default :
            sprintf(buf, "\n**** Invalid peg id ****\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get valid peg id do help <s_get_gen_peg>\n");
            DBC_AppendText(dbc, buf);
            break;
        }

        free(data);

        ret =  TRANSPORT_UnlockManager();
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("SCTP_Console: Failed to Unlock TRANSPORT Manager "
                             "ret = %d\n", ret));
        }
    }
    else if (DBC_Cmd(dbc, "s_clr_gen_peg", "Clear Peg", "<pg> ", "<Peg#> <>"))
    {
        ITS_INT pegid;
        ITS_UINT trid;
        ITS_INT sockId;
        ITS_CHAR trash[ITS_PATH_MAX];
        char pgName[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %x %s %s", buf, &trid, pgName, trash);
        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid number of parameters ****\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "Usage: s_clr_gen_peg <transportID> <PegID>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        /*
         * lock the transport manager as other thead may be deleting
         * the transport
         */
        ret = TRANSPORT_LockManager();
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("SCTP_Console: Failed to lock TRANSPORT Manager "
                             "ret = %d\n", ret));
            return;
        }

        tc = TRANSPORT_FindTransportNoLock(trid);
        if (tc == NULL)
        {
            sprintf(buf, "\n**** Invalid Transport Id ****\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get transport id run command u_asptbl\n");
            DBC_AppendText(dbc, buf);
            TRANSPORT_UnlockManager();
            return;
        }

        /*
         * Not sure why that is ?
         */
        if (!strstr(tc->transport.name, "ASP") &&
            !strstr(tc->transport.name, "SCTP"))
        {
            sprintf(buf, "\n**** Invalid Transport Id ****\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get transport id run command u_asptbl\n");
            DBC_AppendText(dbc, buf);
            TRANSPORT_UnlockManager();
            return;
        }

        sockId = SOCKTRAN_SOURCE(tc)->socket;
        data = calloc(1, sizeof(SCTP_API_MIB_DATA));

        memcpy(&data->addr, SOCKTRAN_CONNECT(tc)->addr,
                                            SOCKTRAN_CONNECT(tc)->asize);

        pegid = atoi(pgName);

        ret = LKSCTP_GetMIBInfo(sockId, pegid, data);
        if (ret == ITS_EINVCHOICE)
        {
            sprintf(buf, "Invalid peg id\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get valid peg id do help <s_clr_gen_peg>\n");
            DBC_AppendText(dbc, buf);
            TRANSPORT_UnlockManager();
            free(data);
            return;
        }

        switch (pegid)
        {
        /* State statistics */
        case SCTP_MIB_CURR_ESTAB:
        case SCTP_MIB_ACTIVE_ESTAB:
        case SCTP_MIB_PASSIVE_ESTAB:
        case SCTP_MIB_ABORTED:
        case SCTP_SHUTDOWNS:
        case SCTP_MIB_GEN_STATES:
            sprintf(buf, "\nCurrently Not Supported!\n");
            DBC_AppendText(dbc, buf);
            break;

        /* General statistics */
        case SCTP_MIB_OOB:
        case SCTP_MIB_SENT_CHUNKS:
        case SCTP_MIB_REC_CHUNKS:
        case SCTP_MIB_OO_SENT_CHUNKS:
        case SCTP_MIB_OO_REC_CHUNKS:
        case SCTP_MIB_FRAG_DG:
        case SCTP_MIB_REASMB_DG:
        case SCTP_MIB_GEN_STATISTICS:
            sprintf(buf, "\nCurrently Not Supported!\n");
            DBC_AppendText(dbc, buf);
            break;

        /* Association statistics */
        case SCTP_MIB_T1_EXPIRED:
        case SCTP_MIB_T2_EXPIRED:
        case SCTP_MIB_RETR_CHUNKS:
        case SCTP_MIB_CKSUM_ERROR:
        case SCTP_MIB_ASSOC_STATISTICS:
            sprintf(buf, "\nCurrently Not Supported!\n");
            DBC_AppendText(dbc, buf);
            break;
 
        default :
            sprintf(buf, "\n**** Invalid peg id ****\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get valid peg id do help <s_clr_gen_peg>\n");
            DBC_AppendText(dbc, buf);
            break;
        }

        if (ret != ITS_SUCCESS)		
        {
	    sprintf(buf, "Clear Peg failed \n");
            DBC_AppendText(dbc, buf);
        }

        free(data);

        ret =  TRANSPORT_UnlockManager();
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("SCTP_Console: Failed to Unlock TRANSPORT Manager "
                             "ret = %d\n", ret));
        }
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Send a message to the remote
 *
 *  Input Parameters:
 *      sd - the socket
 *      msg - the control structure
 *      flags - sync or async
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      the number of bytes sent.  negative values indicate errors
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Sends data
 *                             ID :: D0070             
 ****************************************************************************/
#if 0
SCTPDLLAPI int
LKSCTP_SendMsg(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags)
{ 
    struct sockaddr_in *to = NULL;
    char *data             = NULL;
    int dataLen            = 0;
    
    SCTP_API_CMSG *cmsg;
    struct sctp_sndrcvinfo sinfo;
    
    int retVal;
    unsigned int x;

    /*
     * By default this value will be the one defined in lksctp.h
     */
    sinfo.sinfo_timetolive = SND_NON_BLOCKING_TIMEOUT_VAL * 1000;

    cmsg = (SCTP_API_CMSG *)msg->control;
   
    /* NOTE */
    switch (flags)
    {
        case SCTP_API_SYNC: /* Blocking Call */
            /* timetolive = 0; */
            break;

        case SCTP_API_ASYNC: /* Non Blocking Call */
           /* This is default already done */
           break;
    }
 
    /* Reset the flags */ 
    sinfo.sinfo_flags ^= sinfo.sinfo_flags;
    switch (cmsg->data.sndRcv.flags)
    {    
        /* Un-Order delivery of message? */
        case SCTP_SR_UNORDERED:
            sinfo.sinfo_flags |= MSG_UNORDERED;
            break;
 
        /* user wants abort? */
        case SCTP_SR_ABORT:
            SCTP_DEBUG(("LKSCTP_SendMsg: Abort Msg\n"));
            sinfo.sinfo_flags |= MSG_ABORT;
            break;
       
        /* user wants shutdown? */
        case SCTP_SR_SHUTDOWN:
            SCTP_DEBUG(("LKSCTP_SendMsg: Shutdown Msg\n"));
            sinfo.sinfo_flags |= MSG_EOF;
            break;
    
        /* record options */
        case SCTP_SR_MY_ADDR_ONLY:
            sinfo.sinfo_flags |= MSG_ADDR_OVER;
            break;
    }

    /* Get Destination Address */
    if (msg->name)
    {
        to = (struct sockaddr_in *)msg->name;
    }

    /* Get data count */ 
    if (msg->numIOVecs == 0)
    {
        return (ITS_FALSE);
    }

    /* Get data */
    if (msg->ioVecs[0].vector)
    {
        data = (char *)msg->ioVecs[0].vector;
        dataLen = msg->ioVecs[0].len;
    }

    /* Get other control info */
    sinfo.sinfo_stream = cmsg->data.sndRcv.stream;
    
    sinfo.sinfo_ppid = htonl(cmsg->data.sndRcv.payload);
    
    sinfo.sinfo_context = htonl(cmsg->data.sndRcv.context);

    /* From Remote sockaddr, get assocId */
    if ((sinfo.sinfo_assoc_id = FindAssocId(to)) < 0)
    {
        SCTP_ERROR(("LKSCTP_SendMsg: Assoc Id not found\n"));
        return (ITS_ESENDFAIL);   
    } 
    
    while(1) 
    {
        retVal = sctp_send(sd,
                          (void *)data,
                          (size_t)dataLen,
                          (struct sctp_sndrcvinfo *) &sinfo, 
                          MSG_DONTWAIT);

        /* Timeout? */ 
        if (errno == EAGAIN) 
        {
            SCTP_WARNING(("LKSCTP_SendMsg: Msg Send Timeout\n"));
            continue;
        }    
    
        break;
    }

    /* Send Error, Other than timeout? */
    if (retVal < 0)
    {    
        SCTP_ERROR(("LKSCTP_SendMsg: Msg Send Failed\n"));
        return (ITS_ESENDFAIL);
    }

    /* Send Successfully */ 
    x = ntohl(to->sin_addr.s_addr);
    SCTP_DEBUG(("LKSCTP_SendMsg: Msg send to %d.%d.%d.%d:%d of length: %d\n",
              (int)((x>>24) & 0x000000ff),
              (int)((x>>16) & 0x000000ff),
              (int)((x>>8) & 0x000000ff),
              (int)(x & 0x000000ff),
              ntohs(to->sin_port),
              dataLen)); 

    return (retVal);
}
#endif

SCTPDLLAPI int
LKSCTP_SendMsg(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags)
{
    struct sockaddr_in *to = NULL;
    char *data             = NULL;
    int dataLen            = 0;
    int stream             = 0;
    /*
     * By default this value will be the one defined in lksctp.h
     */
    int timetolive         = SND_NON_BLOCKING_TIMEOUT_VAL * 1000;
    int retVal;
    SCTP_API_CMSG *cmsg;
    ITS_UINT kflags;
    unsigned int ppid;
    unsigned int context;
    unsigned int x;

    cmsg = (SCTP_API_CMSG *)msg->control;

    /* NOTE */
    switch (flags)
    {
        case SCTP_API_SYNC: /* Blocking Call */
            /* timetolive = 0; */
            break;

        case SCTP_API_ASYNC: /* Non Blocking Call */
           /* This is default already done */
           break;
    }
 
    /* Reset the flags */
    kflags ^= kflags;
    switch (cmsg->data.sndRcv.flags)
    {
        /* Un-Order delivery of message? */
        case SCTP_SR_UNORDERED:
            kflags |= MSG_UNORDERED;
            break;
 
        /* user wants abort? */
        case SCTP_SR_ABORT:
            SCTP_DEBUG(("LKSCTP_SendMsg: Abort Msg\n"));
            kflags |= MSG_ABORT;
            break;
       
        /* user wants shutdown? */
        case SCTP_SR_SHUTDOWN:
            SCTP_DEBUG(("LKSCTP_SendMsg: Shutdown Msg\n"));
            kflags |= MSG_EOF;
            break;
    
        /* record options */
        case SCTP_SR_MY_ADDR_ONLY:
            kflags |= MSG_ADDR_OVER;
            break;
    }

    if (msg->name)
    {
        to = (struct sockaddr_in *)msg->name;
    }

    if (msg->numIOVecs == 0)
    {
        return (ITS_FALSE);
    }

    if (msg->ioVecs[0].vector)
    {
        data = (char *)msg->ioVecs[0].vector;
        dataLen = msg->ioVecs[0].len;
    }

    stream = cmsg->data.sndRcv.stream;

    ppid = htonl(cmsg->data.sndRcv.payload);

    context = htonl(cmsg->data.sndRcv.context);

    while(1)
    {
        retVal = sctp_sendmsg(sd,
                             (void *)data,
                             (size_t)dataLen,
                             (struct sockaddr *)to,
                             (socklen_t)sizeof(struct sockaddr),
                             ppid,
                             kflags,
                             stream,
                             timetolive,
                             context);

        if (errno == EAGAIN) 
        {
            SCTP_WARNING(("LKSCTP_SendMsg: Msg Send Timeout\n"));
            continue;
        }

        break;
    }

    if (retVal < 0)
    {
        SCTP_ERROR(("LKSCTP_SendMsg: Msg Send Failed\n"));
        return (ITS_ESENDFAIL);
    }
 
    x = ntohl(to->sin_addr.s_addr);
    SCTP_DEBUG(("LKSCTP_SendMsg: Msg send to %d.%d.%d.%d:%d of length: %d\n",
              (int)((x>>24) & 0x000000ff),
              (int)((x>>16) & 0x000000ff),
              (int)((x>>8) & 0x000000ff),
              (int)(x & 0x000000ff),
              ntohs(to->sin_port),
              dataLen));

    return (retVal);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      receive data from the remote
 *
 *  Input Parameters:
 *      sd - the socket
 *      msg - the message control structure
 *      flags - sync or async
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      the number of bytes received.  negative values indicate errors
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Receives data
 *                             ID :: D0080             
****************************************************************************/
SCTPDLLAPI int
LKSCTP_RecvMsg(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags)
{
    char data[LKSCTP_MAX_BUFF_SIZE];
    int dataLen = LKSCTP_MAX_BUFF_SIZE;
    struct sockaddr_in from;
    socklen_t fromLen = sizeof(struct sockaddr);
    struct sctp_sndrcvinfo srInfo;
    int msg_flags;  
    int retVal;
    unsigned int x;

    /* IntelliNet SCTP Data Structure */
    SCTP_API_CMSG cmsg;
    SCTP_API_IOVEC ioVecs;

    /* NOTE */
    switch (flags)
    {
        case SCTP_API_SYNC: /* Blocking */
            break;
    
        case SCTP_API_ASYNC: /* Non Blocking */
            /* This is default already done */
            break;  
    }

    while (1) 
    {
        retVal = sctp_recvmsg(sd,
                             (void *)data,
                             dataLen,
                             (struct sockaddr *)&from,
                             (socklen_t *)&fromLen,
                             (struct sctp_sndrcvinfo *)&srInfo,
                             (int *)&msg_flags);

        /* Error? */  
        if (retVal <= 0)
        {
            /* Timeout or Other Receive Error? */
            if (errno == EAGAIN)
            {
                /* timeout */
                SCTP_WARNING(("LKSCTP_RecvMsg: Receive Timeout\n"));
                continue;
            }
            else
            {
                /* other error */  
                SCTP_ERROR(("LKSCTP_RecvMsg: Receive Failure\n"));
            }
        }
        
        break;
    } 

    /* Successfully Received */
    x = ntohl(from.sin_addr.s_addr);
    SCTP_DEBUG(("LKSCTP_RecvMsg: Msg received from %d.%d.%d.%d:%d" 
                " of length: %d on stream %d\n",
                (int)((x>>24) & 0x000000ff),
                (int)((x>>16) & 0x000000ff),
                (int)((x>>8) & 0x000000ff),
                (int)(x & 0x000000ff),
                ntohs(from.sin_port),
                retVal,
                srInfo.sinfo_stream));
    
    /* Now map Kernel SCTP DS to IntelliNet SCTP DS */              
 
    /* Get Source Address */
    memcpy(msg->name, &from, fromLen);
    msg->nameLen = fromLen;

    /* Data or Notification? */        
    if (msg_flags & MSG_NOTIFICATION)
    {
        /* Notification Received */     

        union sctp_notification *snp;
                
        /* Now IntelliNet msg->control must contain Kernel Notifications */
        msg->flags = SCTP_IS_EVENT;

        bzero(msg->ioVecs->vector, LKSCTP_MAX_BUFF_SIZE);
            
        msg->numIOVecs = 0;

        /* Map Kernel Notifications to IntelliNet Notifications */ 
        snp = (union sctp_notification *)data;
                
        switch (snp->sn_header.sn_type)
        {
            case SCTP_ASSOC_CHANGE:
            {
                SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                            " SCTP Notification Assoc Change\n"));   
                    
                struct sctp_assoc_change *sac;
                    
                sac = (struct sctp_assoc_change *)&snp->sn_assoc_change;

                cmsg.hdr.len = sizeof(SCTP_API_ASSOC_CHG_DATA);
                cmsg.hdr.level = IPPROTO_SCTP;
                cmsg.hdr.type = SCTP_CM_ASSOC_CHG;
                        
                /* No Kernel Notification for SCTP_AC_COMM_ABORTED!?! */ 
                switch (sac->sac_state)
                {
                    /* error field set to 0, as IntelliNet SCTP */
                    case SCTP_COMM_UP:
                    {
                        SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                                    " SCTP Notification Communication Up\n"));

                        AddAssocId(&from, sac->sac_assoc_id);
 
                        memcpy(&cmsg.data.assocChg.primaryAddr, &from, sizeof(from));
                       
                        cmsg.data.assocChg.state = SCTP_AC_COMM_UP;
                        cmsg.data.assocChg.error = 0;

                        break;
                    }

                    case SCTP_COMM_LOST:
                    {
                        SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                                    " SCTP Notification Communication Lost\n"));   

                        RemoveAssocId(&from, sac->sac_assoc_id);

                        memcpy(&cmsg.data.assocChg.primaryAddr, &from,
                               sizeof(from));
                        
                        cmsg.data.assocChg.state = SCTP_AC_COMM_LOST;
                        cmsg.data.assocChg.error = 0;
                        
                        break;
                    }

                    case SCTP_RESTART:
                    {
                        SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                                    " SCTP Notification Restart\n"));   
                         
                        AddAssocId(&from, sac->sac_assoc_id);
 
                        memcpy(&cmsg.data.assocChg.primaryAddr, &from, sizeof(from));
                        
                        cmsg.data.assocChg.state = SCTP_AC_COMM_RESTART;
                        cmsg.data.assocChg.error = 0;
 
                        break;
                    }

                    case SCTP_SHUTDOWN_COMP:
                    {
                        SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                                    " SCTP Notification Shutdown Done\n"));   
                            
                        RemoveAssocId(&from, sac->sac_assoc_id);

                        memcpy(&cmsg.data.assocChg.primaryAddr, &from, sizeof(from));
 
                        cmsg.data.assocChg.state = SCTP_AC_SHUTDOWN_DONE;
                        cmsg.data.assocChg.error = 0;

                        break;
                    }

                    case SCTP_CANT_STR_ASSOC:
                    {
                        SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                                    " SCTP Notification Assoc cannot start\n"));   
 
                        memcpy(&cmsg.data.assocChg.primaryAddr, &from, sizeof(from));
  
                        cmsg.data.assocChg.state = SCTP_AC_CANT_START;
                        cmsg.data.assocChg.error = 0;

                        break;                        
                    }
                }
                        
                break;
            } 

            case SCTP_PEER_ADDR_CHANGE:
            {
                SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                            " SCTP Notification Peer Address Change\n"));   

                struct sctp_paddr_change *spc;

                spc = (struct sctp_paddr_change *)&snp->sn_paddr_change;
            
                cmsg.hdr.len = sizeof(SCTP_API_INTF_CHG_DATA);
                cmsg.hdr.level = IPPROTO_SCTP;
                cmsg.hdr.type = SCTP_CM_INTF_CHG;

                switch (spc->spc_state)
                {
                    /* SCTP_ADDR_AVAILABLE || SCTP_ADDR_ADDED */
                    case SCTP_ADDR_AVAILABLE: 
                    case SCTP_ADDR_ADDED:
                    {
                        SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                                    " SCTP Notification Address Reachable\n"));   
 
                        AddAssocId(&from, spc->spc_assoc_id);
                        
                        memcpy(&cmsg.data.intfChg.primaryAddr, &from,
                               sizeof(from));
                        memcpy(&cmsg.data.intfChg.affectedAddr, &spc->spc_aaddr,
                               sizeof(spc->spc_aaddr));
 
                        cmsg.data.intfChg.state = SCTP_IC_ADDR_REACHABLE;
                        cmsg.data.intfChg.errorCode = 0;

                        break; 
                    }   
                         
                    /* SCTP_ADDR_UNREACHABLE || SCTP_ADDR_REMOVED */
                    case SCTP_ADDR_UNREACHABLE:
                    case SCTP_ADDR_REMOVED:
                    {
                        SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                                    " SCTP Notification Address Unreachable\n"));   
 
                        RemoveAssocId(&from, spc->spc_assoc_id);
                        
                        memcpy(&cmsg.data.intfChg.primaryAddr, &from,
                               sizeof(SOCK_AddrStore));
                        memcpy(&cmsg.data.intfChg.affectedAddr, &spc->spc_aaddr,
                               sizeof(SOCK_AddrStore));
 
                        cmsg.data.intfChg.state = SCTP_IC_ADDR_UNREACHABLE;
                        cmsg.data.intfChg.errorCode = 0;

                        break;
                    }
                            
                    /* No IntelliNet Notification for SCTP_ADDR_MADE_PRIM!?!  */ 
                    case SCTP_ADDR_MADE_PRIM:
                    {
                        SCTP_WARNING(("LKSCTP_RecvMsg:"
                                      " SCTP Notification: "
                                      "Address Made Primary... Not Handled!\n")); 
                    }    
                }  
                         
                break;
            }  

            case SCTP_REMOTE_ERROR:
            {
                SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                            " SCTP Notification Remote Error\n"));   

                struct sctp_remote_error *sre;

                sre = (struct sctp_remote_error *)&snp->sn_remote_error;
                        
                cmsg.hdr.len = 0;
                cmsg.hdr.level = IPPROTO_SCTP;
                cmsg.hdr.type = SCTP_CM_REMOTE_ERR;

                cmsg.data.remErr.causeCode = ntohs(sre->sre_error);
                cmsg.data.remErr.causeLen = ntohs(sre->sre_length);

                memcpy(cmsg.data.remErr.causeData, sre->sre_data, 
                       sizeof(cmsg.data.remErr.causeData));

                break;
            } 

            case SCTP_SEND_FAILED:
            {
                /* 
                 *  Kernel Notifications,
                 *  SCTP_DATA_UNSENT & SCTP_DATA_SENT
                 *  handled together as IntelliNet Notification
                 *  SCTP_CM_SEND_FAIL
                 */

                SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                            " SCTP Notification Send Failed\n"));   
                struct sctp_send_failed *ssf;

                ssf = (struct sctp_send_failed *)&snp->sn_send_failed;

                cmsg.hdr.len = 0;
                cmsg.hdr.level = IPPROTO_SCTP;
                cmsg.hdr.type = SCTP_CM_SEND_FAIL;
                cmsg.data.sndRcv.tsn = ssf->ssf_info.sinfo_tsn; 
                cmsg.data.sndRcv.stream = ssf->ssf_info.sinfo_stream;
                cmsg.data.sndRcv.seqNum =  ssf->ssf_info.sinfo_ssn; 
                cmsg.data.sndRcv.deliveryNum = 0xFFFF;
       
                /* Reset the flag */
                cmsg.data.sndRcv.flags ^= cmsg.data.sndRcv.flags;                   
                     
                /* Entire message has been read? */ 
                if (msg_flags & MSG_EOR)
                {
                    /* Yes, entire message read */ 
                    cmsg.data.sndRcv.flags |= SCTP_SR_END_REC;
                }
                else
                {
                    /* No, entire message read */ 
                    cmsg.data.sndRcv.flags |= SCTP_SR_MORE_DATA;
                }
                         
                if (ssf->ssf_info.sinfo_flags & MSG_UNORDERED)
                {
                    /* Message was sent unordered */
                    cmsg.data.sndRcv.flags |= SCTP_SR_UNORDERED; 
                }

                memcpy(&cmsg.data.sndRcv.primary, &from, sizeof(from));
  
                cmsg.data.sndRcv.context = htonl(ssf->ssf_info.sinfo_context); 
                cmsg.data.sndRcv.payload = htonl(ssf->ssf_info.sinfo_ppid);
                cmsg.data.sndRcv.tos = ssf->ssf_info.sinfo_timetolive; 
                      
                break;
            }

            /* No IntelliNet Notification for following */ 
            case SCTP_SHUTDOWN_EVENT:
            {
                /* 
                 * No direct IntelliNet Notification found,
                 * but it can & should be mapped to IntelliNet ABORT Event
                 */  

                struct sctp_shutdown_event *sse;

                sse = (struct sctp_send_failed *)&snp->sn_shutdown_event;

                SCTP_DEBUG(("LKSCTP_RecvMsg:"
                            " SCTP Notification Assoc Change\n"));
      
                SCTP_DEBUG(("LKSCTP_RecvMsg:" 
                            " SCTP Notification Abort Event\n"));   

                RemoveAssocId(&from, sse->sse_assoc_id);

                cmsg.hdr.len = sizeof(SCTP_API_ASSOC_CHG_DATA);
                cmsg.hdr.level = IPPROTO_SCTP;
                cmsg.hdr.type = SCTP_CM_ASSOC_CHG;
     
                memcpy(&cmsg.data.assocChg.primaryAddr, &from,
                       sizeof(from));

                cmsg.data.assocChg.state = SCTP_AC_COMM_ABORTED;
                cmsg.data.assocChg.error = 0;
 
                break;
            }
              
            /* No IntelliNet Notification for following */ 
            case SCTP_ADAPTION_INDICATION:
            {
                SCTP_WARNING(("LKSCTP_RecvMsg:" 
                              " SCTP Notification: "
                              "Adaption Indication... Not Handled!\n"));   
                    
                break;
            }

            /* No IntelliNet Notification for following */ 
            case SCTP_PARTIAL_DELIVERY_EVENT:
            {
                SCTP_WARNING(("LKSCTP_RecvMsg:" 
                              " SCTP Notification: "
                              "Partial Delivery Event... Not Handled!\n"));   
                 
                break;
            }
        } 
    }
    else
    {
        /* Data Received */   
        SCTP_DEBUG(("LKSCTP_RecvMsg: SCTP Data Received\n"));   

        /* Now IntelliNet msg->control must contain Kernel SCTP_SNDRCV Info */
        msg->flags = SCTP_IS_DATA;

        /* Copy Data */
        memcpy(msg->ioVecs->vector, data, retVal); 
        msg->ioVecs->len = retVal;

        /* Copy Data count */
        msg->numIOVecs = 1;

        /* Get other control info */ 
        cmsg.hdr.type = SCTP_CM_DATA_IO;
        cmsg.hdr.len = sizeof(SCTP_API_SND_RCV);
        cmsg.hdr.level = IPPROTO_SCTP;
                
        cmsg.data.sndRcv.tsn = srInfo.sinfo_tsn; 
        cmsg.data.sndRcv.stream = srInfo.sinfo_stream;
        cmsg.data.sndRcv.seqNum =  srInfo.sinfo_ssn; 
        cmsg.data.sndRcv.deliveryNum = 0xFFFF; 

        /* Entire Data Received? */            
        if (msg_flags & MSG_EOR)
        {
            /* Yes, entire message read */
            cmsg.data.sndRcv.flags |= SCTP_SR_END_REC;
        }
        else
        {
            /* No, entire not message read */
            cmsg.data.sndRcv.flags |= SCTP_SR_MORE_DATA;
        }
      
        /* Message was sent unordered? */   
        switch (srInfo.sinfo_flags)
        {
           case MSG_UNORDERED:
              cmsg.data.sndRcv.flags |= SCTP_SR_UNORDERED; 
              break;
        }
 
        /* Get few other control info */
              
        memcpy(&cmsg.data.sndRcv.primary, &from, sizeof(from));
  
        cmsg.data.sndRcv.context = htonl(srInfo.sinfo_context); 
        cmsg.data.sndRcv.payload = htonl(srInfo.sinfo_ppid);
        cmsg.data.sndRcv.tos = srInfo.sinfo_timetolive;   
    } 

    /* Copy control info.
     * for 'Notification' it must contains 'Kernel Notifications' Info
     * for 'Data' it must contains 'Kernel SCTP_SNDRCV' Info 
     */ 
    memcpy(msg->control, &cmsg, sizeof(SCTP_API_CMSG));
    msg->controlLen = sizeof(SCTP_API_CMSG);
   
    return retVal;
}

/*.implementation:
 ****************************************************************************
 *  Name:
 *      LKSCTP_Pending
 *
 *  Purpose:
 *      Use this to see how many bytes can be gotten from a subsequent read() 
 *      call.  Note that this will return a number meaning that _at least_ so
 *      many bytes can be read, because more data may be received in between 
 *      the time this call is made and the actual read() system call is made
 *
 *  Input Parameters:
 *      int     sd                File descriptor to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      <0              An error occured
 *      (Other)         Number of bytes available (may be 0)
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Read pending status
 *                             ID :: D0100            
 ****************************************************************************/
SCTPDLLAPI int
LKSCTP_Pending(ITS_USHORT sd)
{
    int rc;                      /* return code */

    struct sctp_status status;
    int status_len;

    /*
     TODO:
       How to know remote Address!?! 
       
       Change the phototpe of the function 
       int LKSCTP_Pending(ITS_USHORT sd, struct sockaddr_in *remote)
     */

#if 0
    SCTP_DEBUG(("LKSCTP_Pending\n"));

    memset(&status, 0, sizeof(status));

    if ((assocId = FindAssocId(remote)) < 0)
    {
        SCTP_ERROR(("LKSCTP_Pending... Assoc ID not found\n"));

        /* No Assoc Id, If set to zero than for endpoint; */
        assocId = 0;
    }

    status.sstat_assoc_id = assoc_id;

    status_len = sizeof(struct sctp_status);

    if (getsockopt(sd, SOL_SCTP, SCTP_STATUS,
                   (char *)&status, &status_len) < 0)
    {
        rc = ITS_EINVALIDARGS;
    }
    else
    {
        rc = status.sstat_penddata;
    }

    return rc;  
#endif
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Close a socket
 *
 *  Input Parameters:
 *      sd - the socket to close
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0 indicates success.  Any other value indicates an error
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Closes LK-SCTP socket
 *                             ID :: D0090             
 ****************************************************************************/
SCTPDLLAPI int
LKSCTP_Close(ITS_USHORT sd)
{
    SCTP_DEBUG(("LKSCTP_Close\n"));

    if (sd >= 0)
    {
        /* Close the socket handle */ 
        close(sd);
    }

    return; 
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      ioctl a socket
 *
 *  Input Parameters:
 *      sd - the socket
 *      req - the action to perform
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0 indicates success.  Any other value indicates an error
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Get-Set socket options
 *                             ID :: D0110             
 ****************************************************************************/
SCTPDLLAPI int
LKSCTP_Ioctl(ITS_USHORT sd, int req, ...)
{
    va_list alist;
    int ret                 = ITS_SUCCESS;
    socklen_t optlen        = 0;
    SCTP_API_IOCTL_ARG *arg = NULL;

    struct sockaddr_in *to;
    sctp_assoc_t assocId;  

    va_start(alist, req);
    arg = va_arg(alist, SCTP_API_IOCTL_ARG *);
    va_end(alist);

    SCTP_DEBUG(("LKSCTP_Ioctl\n"));
 
    if (arg == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    to = (struct sockaddr_in *)&arg->addr;
    SCTP_DEBUG(("LKSCTP_Ioctl... Remote addr %08x\n", to));
    
    /**
     * NOTE:
     *
     * For the one-to-many style sockets, an sctp_assoc_t
     * structure (association ID) is used to identify the the
     * association instance that the operation affects. So it
     * must be set when using this style.
     *
     * For the one-to-one style sockets and branched off
     * one-to-many style sockets, this association ID parameter
     * is ignored.
     *
     * If the sctp_assoc_t structure is '0', for the
     * the one-to-many style sockets, then the change effects
     * the entire endpoint.
     *
     * To examine a endpoint's default parameters the
     * sctp_assoc_t should must be set to the value '0'.
     *
     * A value of 0, when modifying the parameters,
     * indicates that the current value should not be changed.
     *   
     * sctp_opt_info() call is a replacement for getsockopt() only and
     * will not set any options associated with the specified socket
     */

    switch (req)
    {        
        /* All Pre-Assocation SETS of IntelliNet */  
        case IOCTL_SET_INIT_DATA:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_INIT_DATA\n"));
            
            struct sctp_initmsg sctp_initmsg;

            bzero(&sctp_initmsg, sizeof(sctp_initmsg));

            sctp_initmsg.sinit_num_ostreams  = arg->value;

            sctp_initmsg.sinit_max_instreams = arg->value2;

            sctp_initmsg.sinit_max_attempts  = arg->value3;

            ret = setsockopt(sd, IPPROTO_SCTP, SCTP_INITMSG,
                                 &sctp_initmsg, sizeof(sctp_initmsg));
            break;
        }
 
        case IOCTL_SET_INIT_TIMEOUT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_INIT_TIMEOUT\n"));
            
            struct sctp_initmsg sctp_initmsg;

            bzero(&sctp_initmsg, sizeof(sctp_initmsg));

            sctp_initmsg.sinit_max_init_timeo = (arg->value * 1000) + arg->value2;

            ret = setsockopt(sd, IPPROTO_SCTP, SCTP_INITMSG,
                                 &sctp_initmsg, sizeof(sctp_initmsg));
            break;
        }

        /* Following are currently not handled!
         * There is no need to implement them, Kernel does it for you.
         * Simply return ITS_SUCCESS 
         */ 
        case IOCTL_SET_HB_TIMEOUT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_HB_TIMEOUT\n"));

            break;
        }

        case IOCTL_SET_INIT_HB_ON:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_INIT_HB_ON\n"));

            break;
        }

        case IOCTL_SET_SEND_TIMEOUT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_SEND_TIMEOUT\n"));

            break;
        }
        case IOCTL_SET_RECV_TIMEOUT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_RECV_TIMEOUT\n"));
 
            break;
        }
        case IOCTL_SET_SHUT_TIMEOUT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_SHUT_TIMEOUT\n"));

            break;
        } 
        case IOCTL_SET_PMTU_TIMEOUT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_PMTU_TIMEOUT\n"));
 
            break;
        }
        case IOCTL_SET_SEND_ATTEMPTS:
        { 
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_SEND_ATTEMPTS\n"));  
             
            break;
        }
        case IOCTL_SET_INIT_COOK_LIFE:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_INIT_COOK_LIFE\n"));

            break;
        }  
   
        /* All Post-Assocation SETS of IntelliNet */
        case IOCTL_SET_COOKIE_LIFE:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_COOKIE_LIFE\n"));

            struct sctp_assocparams sctp_assocparams;

            bzero(&sctp_assocparams, sizeof(sctp_assocparams));

            sctp_assocparams.sasoc_cookie_life = arg->value;
            sctp_assocparams.sasoc_assoc_id =  FindAssocId(to);

            ret = setsockopt(sd, IPPROTO_SCTP, SCTP_ASSOCINFO,
                                 &sctp_assocparams, sizeof(sctp_assocparams));
            break;
        }

        case IOCTL_SET_PRIMARY:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_PRIMARY\n"));

            struct sctp_setpeerprim sctp_setpeerprim;

            bzero(&sctp_setpeerprim, sizeof(sctp_setpeerprim));

            sctp_setpeerprim.sspp_assoc_id =  FindAssocId(to);
            sctp_setpeerprim.sspp_addr = *((struct sockaddr_storage*)to);

            ret = setsockopt(sd, IPPROTO_SCTP, SCTP_SET_PEER_PRIMARY_ADDR,
                                 &sctp_setpeerprim, sizeof(sctp_setpeerprim));
            break;
        }

        case IOCTL_SET_RTO_PARAMS:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_RTO_PARAMS\n"));

            struct sctp_rtoinfo sctp_rtoinfo;

            bzero(&sctp_rtoinfo, sizeof(sctp_rtoinfo));

            sctp_rtoinfo.srto_assoc_id =  FindAssocId(to);
            sctp_rtoinfo.srto_initial = arg->value;
            sctp_rtoinfo.srto_min = arg->value2;
            sctp_rtoinfo.srto_max = arg->value3;

            ret = setsockopt(sd, IPPROTO_SCTP, SCTP_RTOINFO,
                                 &sctp_rtoinfo, sizeof(sctp_rtoinfo));

            break;
        }
 
        case IOCTL_SET_LOCAL_RWND:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_LOCAL_RWND\n"));
   
            struct sctp_assocparams sctp_assocparams;

            bzero(&sctp_assocparams, sizeof(sctp_assocparams));

            sctp_assocparams.sasoc_local_rwnd = arg->value;
            sctp_assocparams.sasoc_assoc_id =  FindAssocId(to);

            ret = setsockopt(sd, IPPROTO_SCTP, SCTP_ASSOCINFO,
                                 &sctp_assocparams, sizeof(sctp_assocparams));
            break;
        }

        /* Following are currently not handled */
        case IOCTL_SET_NET_ERR_THRESH:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_NET_ERR_THRESH\n"));

            SCTP_WARNING(("LKSCTP_Ioctl:"
                         " IOCTL_SET_NET_ERR_THRESH Not Handled!\n"));

            break;
        }
        case IOCTL_SET_ASSOC_ERR_THRESH:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_ASSOC_ERR_THRESH\n"));

            SCTP_WARNING(("LKSCTP_Ioctl:"
                         " IOCTL_SET_ASSOC_ERR_THRESH Not Handled!\n"));

            break;
        }
        case IOCTL_SET_HEARTBEAT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_HEARTBEAT\n"));

            SCTP_WARNING(("LKSCTP_Ioctl:"
                         " IOCTL_SET_HEARTBEAT Not Handled!\n"));

            break;
        }
        case IOCTL_SET_HEARTBEAT_DELAY:    
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_HEARTBEAT_DELAY\n"));

            SCTP_WARNING(("LKSCTP_Ioctl:"
                         " IOCTL_SET_HEARTBEAT_DELAY Not Handled!\n"));

            break;
        }
         
        /* All Pre-Assocation GETS of IntelliNet */
        case IOCTL_GET_INIT_DATA:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_INIT_DATA\n"));

            struct sctp_initmsg sctp_initmsg;

            int optlen = sizeof(sctp_initmsg);

            bzero(&sctp_initmsg, sizeof(sctp_initmsg));

            ret = getsockopt(sd, IPPROTO_SCTP, SCTP_INITMSG,
                                 &sctp_initmsg, &optlen);

            arg->value  = sctp_initmsg.sinit_num_ostreams;
            arg->value2 = sctp_initmsg.sinit_max_instreams;
            arg->value3 = sctp_initmsg.sinit_max_attempts;

            break;
        }

        /* All Post-Assocation GETS of IntelliNet */ 
        case IOCTL_GET_COOKIE_LIFE:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_COOKIE_LIFE\n"));

            struct sctp_assocparams sctp_assocparams;

            int optlen = sizeof(sctp_assocparams);

            bzero(&sctp_assocparams, sizeof(sctp_assocparams));
                    
            sctp_assocparams.sasoc_assoc_id = FindAssocId(to);

            ret = getsockopt(sd, IPPROTO_SCTP, SCTP_ASSOCINFO,
                                 &sctp_assocparams, &optlen);

            arg->value = sctp_assocparams.sasoc_cookie_life;

            break;
        }

        case IOCTL_GET_LOCAL_RWND:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_LOCAL_RWND\n"));

            struct sctp_assocparams sctp_assocparams;

            int optlen = sizeof(sctp_assocparams);

            bzero(&sctp_assocparams, sizeof(sctp_assocparams));

            sctp_assocparams.sasoc_assoc_id = FindAssocId(to);

            ret = getsockopt(sd, IPPROTO_SCTP, SCTP_ASSOCINFO,
                                 &sctp_assocparams, &optlen);

            arg->value = sctp_assocparams.sasoc_local_rwnd;

            break;
        }

        case IOCTL_GET_PEER_RWND:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_PEER_RWND\n"));

            struct sctp_assocparams sctp_assocparams;

            int optlen = sizeof(sctp_assocparams);

            bzero(&sctp_assocparams, sizeof(sctp_assocparams));

            sctp_assocparams.sasoc_assoc_id = FindAssocId(to);

            ret = getsockopt(sd, IPPROTO_SCTP, SCTP_ASSOCINFO,
                                 &sctp_assocparams, &optlen);

            arg->value = sctp_assocparams.sasoc_peer_rwnd;

            break;
        }
 
        case IOCTL_GET_RTO_REPORT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_RTO_REPORT\n"));

            struct sctp_paddrinfo sctp_paddrinfo;

            int optlen = sizeof(sctp_paddrinfo);

            bzero(&sctp_paddrinfo, sizeof(sctp_paddrinfo));

            sctp_paddrinfo.spinfo_assoc_id = FindAssocId(to); 

            ret = getsockopt(sd, IPPROTO_SCTP, SCTP_GET_PEER_ADDR_INFO,
                                 &sctp_paddrinfo, &optlen);

            arg->value = sctp_paddrinfo.spinfo_rto;

            break;
        }

        case IOCTL_GET_CWND_REPORT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_CWND_REPORT\n"));

            struct sctp_paddrinfo sctp_paddrinfo;

            int optlen = sizeof(sctp_paddrinfo);

            bzero(&sctp_paddrinfo, sizeof(sctp_paddrinfo));

            sctp_paddrinfo.spinfo_assoc_id = FindAssocId(to);

            ret = getsockopt(sd, IPPROTO_SCTP, SCTP_GET_PEER_ADDR_INFO,
                                 &sctp_paddrinfo, &optlen);

            arg->value = sctp_paddrinfo.spinfo_cwnd;

            break;
        }

        case IOCTL_GET_SRTT_REPORT:
        {

            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_SRTT_REPORT\n"));

            struct sctp_paddrinfo sctp_paddrinfo;

            int optlen = sizeof(sctp_paddrinfo);

            bzero(&sctp_paddrinfo, sizeof(sctp_paddrinfo));

            sctp_paddrinfo.spinfo_assoc_id = FindAssocId(to);

            ret = getsockopt(sd, IPPROTO_SCTP, SCTP_GET_PEER_ADDR_INFO,
                                 &sctp_paddrinfo, &optlen);

            arg->value = sctp_paddrinfo.spinfo_srtt;

            break;
        }

        case IOCTL_GET_STATE_REPORT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_STATE_REPORT\n"));

            struct sctp_status sctp_status;

            int optlen = sizeof(sctp_status);

            bzero(&sctp_status, sizeof(sctp_status));
 
            arg->value = sctp_status.sstat_assoc_id = FindAssocId(to);

            ret = getsockopt(sd, IPPROTO_SCTP, SCTP_STATUS,
                                 &sctp_status, &optlen);
 
            arg->value = sctp_status.sstat_state;

            switch (sctp_status.sstat_state)
            {
                case SCTP_CLOSED:
                    arg->value = ITS_SCTP_CLOSED;
                    break;

                case SCTP_COOKIE_WAIT:
                    arg->value = ITS_SCTP_COOKIE_WAIT;
                    break;

                case SCTP_COOKIE_ECHOED:
                    arg->value = ITS_SCTP_COOKIE_SENT;
                    break;

                case SCTP_ESTABLISHED:
                    arg->value = ITS_SCTP_ESTABLISHED;
                    break;

                case SCTP_SHUTDOWN_PENDING:
                    arg->value = ITS_SCTP_SHUTDOWN_PENDING;
                    break;

                case SCTP_SHUTDOWN_SENT:
                    arg->value = ITS_SCTP_SHUTDOWN_SENT;
                    break;
 
                case SCTP_SHUTDOWN_RECEIVED:
                    arg->value = ITS_SCTP_SHUTDOWN_RECEIVED;
                    break;

                case SCTP_SHUTDOWN_ACK_SENT:
                    arg->value = ITS_SCTP_SHUTDOWN_ACK_SENT;
                    break;
 
            } 

            break;
        }

        case IOCTL_GET_NUM_IN_STREAMS:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_NUM_IN_STREAMS\n"));

            struct sctp_initmsg sctp_initmsg;

            int optlen = sizeof(sctp_initmsg);

            bzero(&sctp_initmsg, sizeof(sctp_initmsg));

            ret = getsockopt(sd, IPPROTO_SCTP, SCTP_INITMSG,
                                 &sctp_initmsg, &optlen);

            arg->value = sctp_initmsg.sinit_max_instreams;

            break;
        }

        case IOCTL_GET_NUM_OUT_STREAMS:
        {
            if ((assocId = FindAssocId(to)) < 0)
            {
                SCTP_ERROR(("LKSCTP_Ioctl... Assoc ID not found\n"));
                
                /* No Assoc Id, Get for endpoint; both are same here */
                assocId = 0;
            }

            SCTP_DEBUG(("LKSCTP_Ioctl... ASS ID = %d\n", assocId));

            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_NUM_OUT_STREAMS\n"));

            struct sctp_initmsg sctp_initmsg;

            int optlen = sizeof(sctp_initmsg);

            bzero(&sctp_initmsg, sizeof(sctp_initmsg));

            /* Use sctp_opt_info() OR getsockopt() call, both will work */

            ret = sctp_opt_info(sd, assocId, SCTP_INITMSG,
                                    &sctp_initmsg, &optlen);

#if 0
            ret = getsockopt(sd, IPPROTO_SCTP, SCTP_INITMSG,
                                 &sctp_initmsg, &optlen);
#endif
            arg->value = sctp_initmsg.sinit_num_ostreams;
 
            break;
        }

        /* Following are currently not handled */
        case IOCTL_GET_NUM_NETS:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_NUM_NETS\n"));

            SCTP_WARNING(("LKSCTP_Ioctl:"
                         " IOCTL_GET_NUM_NETS Not Handled!\n"));
            break;
        }
        case IOCTL_GET_PEGS:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_PEGS\n"));

            SCTP_WARNING(("LKSCTP_Ioctl:"
                         " IOCTL_GET_PEGS Not Handled!\n"));
            break;
        }
        case IOCTL_GET_OUTBOUND_FLUSHED:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_OUTBOUND_FLUSHED\n"));

            SCTP_WARNING(("LKSCTP_Ioctl:"
                         " IOCTL_GET_OUTBOUND_FLUSHED Not Handled!\n"));
            break;
        }
        case IOCTL_GET_HEARTBEAT_DELAY:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_GET_HEARTBEAT_DELAY\n"));

            SCTP_WARNING(("LKSCTP_Ioctl:"
                         " IOCTL_GET_HEARTBEAT_DELAY Not Handled!\n"));
            break;
        }

        /* All Other IOCTLS */
        case IOCTL_REQUEST_HEARTBEAT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_REQUEST_HEARTBEAT\n"));

            SCTP_WARNING(("LKSCTP_Ioctl:"
                         " IOCTL_REQUEST_HEARTBEAT Not Handled!\n"));
            break;
        }
        case IOCTL_CLEAR_PEGS:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_CLEAR_PEGS\n"));

            SCTP_WARNING(("LKSCTP_Ioctl:"
                         " IOCTL_CLEAR_PEGS Not Handled!\n"));

            break;
        }

        /* New Ioctl SET Added for LKSCTP, for NON_BLOCKING RECEIVE & SEND */ 
        case IOCTL_SET_RCV_NON_BLOCKING_TIMEOUT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_RCV_NON_BLOCKING_TIMEOUT\n"));

            struct timeval timeval;

            bzero(&timeval, sizeof(timeval)); 

            timeval.tv_sec  = RCV_NON_BLOCKING_TIMEOUT_VAL;

            timeval.tv_usec = 0;

            ret = setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, 
                                 &timeval, sizeof(timeval));

            break;
        }

        case IOCTL_SET_SND_NON_BLOCKING_TIMEOUT:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl... IOCTL_SET_SND_NON_BLOCKING_TIMEOUT\n"));
 
            struct timeval timeval;

            bzero(&timeval, sizeof(timeval));

            timeval.tv_sec  = SND_NON_BLOCKING_TIMEOUT_VAL;

            timeval.tv_usec = 0;

            ret = setsockopt(sd, SOL_SOCKET, SO_SNDTIMEO, 
                                 &timeval, sizeof(timeval));

            break;
        }

        /* Illegal IOCTL */
        default:
        {
            SCTP_DEBUG(("LKSCTP_Ioctl:"
                         " Illegal IOCTL!\n"));
            break;
        }
    }
    
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the LK-SCTP class record (aka the SCTP subsystem).
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
 *
 *  Revision History: 
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Initialize the LK-SCTP
 *                             ID :: D0010             class record 
 ****************************************************************************/
static int
Init(ITS_Class objClass)
{
    if ((SCTP_TraceData = TRACE_Constructor("SCTP",
                                             SCTP_TraceMap, 4)) == NULL)
    {
        /* SCTP failed to Intialize -  No Memory. */

        return (ITS_ENOMEM);
    }

    /*
     * lock in the interfaces
     */
    if (InitManager(&manager) != ITS_SUCCESS)
    {
        return (ITS_EINVALIDARGS);
    }

    InitTraceSettings();

    SCTP_SocketPtr   = LKSCTP_Socket;
    SCTP_BindPtr     = LKSCTP_Bind;
    SCTP_ListenPtr   = LKSCTP_Listen;
    SCTP_AcceptPtr   = LKSCTP_Accept;
    SCTP_ConnectPtr  = LKSCTP_Connect;
    SCTP_SendMsgPtr  = LKSCTP_SendMsg;
    SCTP_RecvMsgPtr  = LKSCTP_RecvMsg;
    SCTP_ClosePtr    = LKSCTP_Close;
    SCTP_PendingPtr  = LKSCTP_Pending;
    SCTP_IoctlPtr    = LKSCTP_Ioctl;

    AddCommitCallback("SCTP", LKSCTP_Commit);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the LK-SCTP class record (aka terminate the SCTP subsystem).
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
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 Destroy the LK-SCTP
 *                             ID :: D0130             class record
 ****************************************************************************/
static void
Term(ITS_Class objClass)
{
    SCTP_SocketPtr   = NULL;
    SCTP_BindPtr     = NULL;
    SCTP_ListenPtr   = NULL;
    SCTP_AcceptPtr   = NULL;
    SCTP_ConnectPtr  = NULL;
    SCTP_SendMsgPtr  = NULL;
    SCTP_RecvMsgPtr  = NULL;
    SCTP_ClosePtr    = NULL;
    SCTP_PendingPtr  = NULL;
    SCTP_IoctlPtr    = NULL;

    DestroyManager(&manager);

    DBC_RemDoCommand(LKSCTP_Console);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The LK-SCTP class record (aka the SCTP subsystem).
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
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02    The LK-SCTP
 *                             ID :: D0010                class record
 ****************************************************************************/
SCTPDLLAPI ITS_ClassRec itsLKSCTP_ClassRec =
{
    /* core */
    {
        NULL,
        0,
        ITS_FALSE,
        0,
        "LKSCTP",
        Init,
        Term,
        NULL,
        NULL,
        NULL
    }
};

SCTPDLLAPI ITS_Class itsLKSCTP_Class = &itsLKSCTP_ClassRec;

