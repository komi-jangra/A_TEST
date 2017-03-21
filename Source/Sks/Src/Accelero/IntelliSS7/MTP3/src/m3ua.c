/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                  
 * CONTRACT: INTERNAL
 *      
 *  ID: $Id: m3ua.c,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $
 *
 *  LOG: $Log: not supported by cvs2svn $
 *  LOG: Revision 1.1.1.1  2007/10/04 13:23:51  bsccs2
 *  LOG: init tree
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/08/03 06:48:47  cvsadmin
 *  LOG: BscCs2
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/03/08 15:13:13  cvsadmin
 *  LOG: BSC project
 *  LOG:
 *  LOG: Revision 9.5  2005/05/06 09:36:38  mmanikandan
 *  LOG: PR6.5.1 Validation Bug(1773) Fix.
 *  LOG:
 *  LOG: Revision 9.4  2005/05/05 05:53:24  adutta
 *  LOG: Fix for #1795
 *  LOG:
 *  LOG: Revision 9.3  2005/04/06 06:06:52  adutta
 *  LOG: Fix for Bug# 1670/1557
 *  LOG:
 *  LOG: Revision 9.2  2005/04/01 12:01:22  ssingh
 *  LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:52:17  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:50:18  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.10  2005/02/22 11:22:58  adutta
 *  LOG: Fix for Bug#1557
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.9  2005/02/21 12:02:16  dsatish
 *  LOG: changes propagated from KINETO BRANCH(Revision 7.1.4.6.2.15/16)
 *  LOG: DAUD support.
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.8  2005/02/09 10:54:42  csireesh
 *  LOG: Validation Bug Fix(Alarms).
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.7  2005/01/11 11:48:45  craghavendra
 *  LOG: Syslog Enhancements.
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.6  2005/01/04 15:23:36  sbabu
 *  LOG: M3UA OAM changes
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.5  2004/12/25 10:48:58  ssingh
 *  LOG: Fix for Bug No #1332
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.4  2004/12/16 02:15:06  randresol
 *  LOG: Add JAPAN variant implementation
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.3  2004/12/15 16:31:40  dsatish
 *  LOG: typo corrected
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.2  2004/12/15 12:10:32  asingh
 *  LOG: separate traces for M3UA
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4.4.1  2004/12/09 15:31:16  snagesh
 *  LOG: Modifications for Chinese variant
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.4  2004/10/06 09:16:16  mmanikandan
 *  LOG: Support for windows build.
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.3  2004/10/06 08:44:03  ssingh
 *  LOG: Modified SLS setting for MTP3_To_M3UA based on avaliable outstreams.
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.2  2004/09/29 09:57:41  asingh
 *  LOG: Changes for linux ES 30 operating system; compilation issue.
 *  LOG:
 *  LOG: Revision 7.1.4.14.2.1  2004/05/03 13:21:30  ssingh
 *  LOG: Fixes for 775/776/777/778/779/804/805 bugs.
 *  LOG:
 *  LOG: Revision 7.1.4.14  2003/11/17 21:42:06  hcho
 *  LOG: Missing pc for resume callback.
 *  LOG:
 *  LOG: Revision 7.1.4.13  2003/11/17 21:31:18  hcho
 *  LOG: Payload shall not send on stream 0.
 *  LOG:
 *  LOG: Revision 7.1.4.12  2003/10/21 14:33:29  lbana
 *  LOG: fix long name issues in routing notification
 *  LOG:
 *  LOG: Revision 7.1.4.11  2003/10/14 20:47:55  lbana
 *  LOG: TCS bug fixes and removed begin and end tags for each fix.
 *  LOG:
 *  LOG: Revision 7.1.4.10  2003/09/21 14:11:34  lbana
 *  LOG: send error for invalid param in DUPU
 *  LOG:
 *  LOG: Revision 7.1.4.9  2003/09/21 13:27:38  lbana
 *  LOG: add DRST tag
 *  LOG:
 *  LOG: Revision 7.1.4.8  2003/09/20 20:13:24  lbana
 *  LOG: add mtp3 status feature for DUPU and SCON
 *  LOG:
 *  LOG: Revision 7.1.4.7  2003/09/19 05:24:36  lbana
 *  LOG: send error message in case if we get invalid version or missing
 *  LOG: mandatory param.
 *  LOG:
 *  LOG: Revision 7.1.4.6  2003/09/11 01:13:40  lbana
 *  LOG: code clean up.
 *  LOG:
 *  LOG: Revision 7.1.4.5  2003/09/11 00:43:59  lbana
 *  LOG: Code reorganized for Pause/Resumes and tested config with 2linksets
 *  LOG:
 *  LOG: Revision 7.1.4.4  2003/08/04 23:34:07  hcho
 *  LOG: Fixed Pause/Resume reverse placed.
 *  LOG:
 *  LOG: Revision 7.1.4.3  2003/07/11 21:12:52  labuser
 *  LOG: DUNA/DAVA functionality is added.
 *  LOG:
 *  LOG: Revision 7.1.4.2  2003/04/04 16:12:54  pmandal
 *  LOG: Finish porting.
 *  LOG:
 *  LOG: Revision 7.1.4.1  2003/04/04 16:02:58  lbana
 *  LOG: fix ansi point code bug
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.7  2002/08/15 19:41:54  mmiers
 *  LOG: Warning removal
 *  LOG:
 *  LOG: Revision 6.6  2002/08/05 15:46:05  labuser
 *  LOG: Plug memory leak. (clin)
 *  LOG:
 *  LOG: Revision 6.5  2002/07/03 19:54:53  mmiers
 *  LOG: China fixes
 *  LOG:
 *  LOG: Revision 6.4  2002/06/12 16:19:15  lbana
 *  LOG: Take message out of MTP3 too.
 *  LOG:
 *  LOG: Revision 6.3  2002/05/20 16:19:13  lbana
 *  LOG: have to include sccp/include dir in makefile.
 *  LOG:
 *  LOG: Revision 6.2  2002/05/20 16:02:50  lbana
 *  LOG: m3ua ver 10 codec
 *  LOG:
 *  LOG: Revision 1.1.2.14  2002/04/05 20:42:38  lbana
 *  LOG: flip 2 bytes of point code in codec
 *  LOG:
 *  LOG: Revision 1.1.2.13  2002/04/04 17:07:05  lbana
 *  LOG: Bug fix for network indicator
 *  LOG:
 *  LOG: Revision 1.1.2.12  2002/04/02 17:45:01  lbana
 *  LOG: bug fix in setting sio
 *  LOG:
 *  LOG: Revision 1.1.2.11  2002/03/26 23:09:03  omayor
 *  LOG: Bug in getting routing context.
 *  LOG:
 *  LOG: Revision 1.1.2.10  2002/03/12 21:50:06  omayor
 *  LOG: Routing Context now in Data for V10.
 *  LOG:
 *  LOG: Revision 1.1.2.9  2002/03/12 21:03:38  lbana
 *  LOG: changed Codec signature
 *  LOG:
 *  LOG: Revision 1.1.2.8  2002/03/05 20:58:17  omayor
 *  LOG: fixes provided in Bakeoff
 *  LOG:
 *  LOG: Revision 1.1.2.7  2002/02/21 20:23:05  omayor
 *  LOG: More on STATUS - SCON.
 *  LOG:
 *  LOG: Revision 1.1.2.6  2002/02/15 00:13:06  omayor
 *  LOG: Add some ERROR Traces.
 *  LOG:
 *  LOG: Revision 1.1.2.5  2002/02/13 22:29:31  omayor
 *  LOG: Typo in message class selection.
 *  LOG:
 *  LOG: Revision 1.1.2.4  2002/02/04 16:46:39  lbana
 *  LOG: include ual.h file
 *  LOG:
 *  LOG: Revision 1.1.2.3  2002/01/30 19:51:49  lbana
 *  LOG: added printf event func
 *  LOG:
 *  LOG: Revision 1.1.2.2  2002/01/30 16:59:13  labuser
 *  LOG: Fix one bug in M3UA to MTP3 conversion (wrong msg type for MGNT).
 *  LOG:
 *  LOG: Revision 1.1.2.1  2002/01/30 16:47:00  labuser
 *  LOG: M3UA V10 Codec.
 *  LOG:
 *                 
 ****************************************************************************/
/*#include <netinet/in.h>*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <its.h>
#include <its_assertion.h>

#include <m3ua.h>

#include <its_sockets.h>
#include <its_transports.h>
#include <its_route_rwlock.h>
#include <its_trace.h>
#include <its_sctp_trans.h>

#include <its_ual.h>
#include <its_alarm.h>

#include <engine.h>

#if defined (CCITT)
#include <itu/sccp.h>
#endif

UALDLLAPI extern CALLBACK_Manager*   __UAL_MgntCallBack;

static ITS_BOOLEAN      started = ITS_FALSE;

static void InitTraceSettings(TRANSPORT_Control*);

static TRACE_OutputInitializer fileCritTrace =
{
    M3UA_FILE_STRING,
    ITS_TRUE,
    M3UA_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    M3UA_FILE_STRING,
    ITS_TRUE,
    M3UA_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    M3UA_FILE_STRING,
    ITS_TRUE,
    M3UA_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    M3UA_FILE_STRING,
    ITS_TRUE,
    M3UA_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    M3UA_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    M3UA_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer M3UA_TraceMap[] =
{
    {M3UA_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {M3UA_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {M3UA_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {M3UA_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } }
};

TRACE_Data* M3UA_TraceData = NULL;

static void
PauseCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData);
static void
ResumeCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData);
static void
StatusCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData);

void
M3UA_Alarm(int which, const char *file, const int line,
           char *format, ...);
int M3UA_Commit(FILE* fp);

/*
 * DATA
 */

static ITS_USHORT    dataMArgs[] =
{
    M3UA_PRM_DATA
};

static ITS_USHORT    dataOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_ROUT_CTX,
    M3UA_PRM_COR_ID
};


M3UA_MSG_DESC M3UA_DATA_Desc =
{
    dataMArgs, sizeof(dataMArgs) / sizeof(ITS_USHORT),
    dataOArgs, sizeof(dataOArgs) / sizeof(ITS_USHORT)
};


/*
 * DUNA 
 */

static ITS_USHORT    dunaMArgs[] =
{
    M3UA_PRM_AFFECTED_PC
};

static ITS_USHORT    dunaOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_ROUT_CTX,
    M3UA_PRM_INFO_STR
};


M3UA_MSG_DESC M3UA_DUNA_Desc =
{
    dunaMArgs, sizeof(dunaMArgs) / sizeof(ITS_USHORT),
    dunaOArgs, sizeof(dunaOArgs) / sizeof(ITS_USHORT)
};


/*
 * DAVA 
 */

static ITS_USHORT    davaMArgs[] =
{
    M3UA_PRM_AFFECTED_PC
};

static ITS_USHORT    davaOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_ROUT_CTX,
    M3UA_PRM_INFO_STR
};


M3UA_MSG_DESC M3UA_DAVA_Desc =
{
    davaMArgs, sizeof(davaMArgs) / sizeof(ITS_USHORT),
    davaOArgs, sizeof(davaOArgs) / sizeof(ITS_USHORT)
};


/*
 * SCON 
 */
static ITS_USHORT    sconMArgs[] =
{
    M3UA_PRM_AFFECTED_PC
};

static ITS_USHORT    sconOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_CONGEST_LEVEL,
    M3UA_PRM_INFO_STR,
    M3UA_PRM_CONCERN_PC,
    M3UA_PRM_ROUT_CTX
};


M3UA_MSG_DESC M3UA_SCON_Desc =
{
    sconMArgs, sizeof(sconMArgs) / sizeof(ITS_USHORT),
    sconOArgs, sizeof(sconOArgs) / sizeof(ITS_USHORT)
};





/*
 * DUPU 
 */

static ITS_USHORT    dupuMArgs[] =
{
    M3UA_PRM_AFFECTED_PC,
    M3UA_PRM_CAUSE_USER
};

static ITS_USHORT    dupuOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_INFO_STR,
    M3UA_PRM_ROUT_CTX
};


M3UA_MSG_DESC M3UA_DUPU_Desc =
{
    dupuMArgs, sizeof(dupuMArgs) / sizeof(ITS_USHORT),
    dupuOArgs, sizeof(dupuOArgs) / sizeof(ITS_USHORT)
};

/*
 * DAUD
 */

static ITS_USHORT    daudMArgs[] =
{
    M3UA_PRM_AFFECTED_PC
};

static ITS_USHORT    daudOArgs[] =
{
    M3UA_PRM_NET_APP,
    M3UA_PRM_ROUT_CTX,
    M3UA_PRM_INFO_STR
};

M3UA_MSG_DESC M3UA_DAUD_Desc =
{
    daudMArgs, sizeof(daudMArgs) / sizeof(ITS_USHORT),
    daudOArgs, sizeof(daudOArgs) / sizeof(ITS_USHORT)
};

/*
 * ERR
 */
static ITS_USHORT    errMArgs[] =
{
    UAL_PRM_ERROR_CODE
};

static ITS_USHORT    errOArgs[] =
{
    M3UA_PRM_INFO_STR,
    M3UA_PRM_ROUT_CTX,
    M3UA_PRM_NET_APP,
    M3UA_PRM_AFFECTED_PC
};

M3UA_MSG_DESC M3UA_ERROR_Desc =
{
    errMArgs, sizeof(errMArgs) / sizeof(ITS_USHORT),
    errOArgs, sizeof(errOArgs) / sizeof(ITS_USHORT)
};

/*
 * application server process maintenance messages
 */

int
M3UA_GetPadding(int size)
{
    if ((size % 4) == 0)
    {
        return 0;
    }
    else
    {
        return 4 - (size % 4);
    }
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This is a helper function that prints a M3UA IE element.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      IE - pointer to the M3UA_IE to be displayed.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
void
M3UA_PrintM3UA_IES(ITS_M3UA_IE *IE)
{
    if (IE != NULL)
    {
        int i;

        printf("------------ M3UA_IE Begin ------------\n");
        printf("Prarmeter Type: 0x%04x \n", IE->param_id);
        printf("Parameter len : 0x%04x \n", IE->param_length);

        for (i = 0; i < IE->param_length; i++)
        {
            printf("0x%02x ", *((unsigned char *)&(IE->param_data) + i));
        }
        printf("\n------------ M3UA_IE End ------------\n");
    }
    else
    {
        printf("IE * is NULL \n");
    }

    return;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This is a helper function that find a M3UA IE element.
 *     
 *  Input Parameters:
 *      ies - pointer to th first element of an array of ITS_M3UA_IE
 *      ieCount - Number of ies in the array
 *      paramId - ie Id of the searched IE
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to the IE if found, else NULL
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
M3UADLLAPI ITS_M3UA_IE*
M3UA_FindM3UAIE(ITS_M3UA_IE *ies, int ieCount, ITS_USHORT paramId)
{
    int i;
    
    for (i=0; i < ieCount; i++)
    {
        if (ies[i].param_id == paramId)
        {
            return &ies[i];
        }
    }

    return NULL;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change the common message header from host
 *      to network format.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      msgHdr - pointer to the message common message header.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
void
M3UA_HComHdrToN(M3UA_MSG_HDR *msgHdr)
{
    msgHdr->msgLen = SOCK_HToNL(msgHdr->msgLen);

    return;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to convert the common message header from
 *      network to host format.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      msgHdr - pointer to the message common message header.
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
 ******************************************************************************/
void
M3UA_NComHdrToH(M3UA_MSG_HDR *msgHdr)
{

    msgHdr->msgLen = SOCK_NToHL(msgHdr->msgLen);

    return;
}



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change an ITS_M3UA_IE array to the network 
 *      format
 *     
 *  Input Parameters:
 *      ieCount - number of element in the array.
 *
 *  Input/Output Parameters:
 *      ies - pointer to the first element of the array.
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
 ******************************************************************************/
void
M3UA_Hm3uaIESToN(ITS_M3UA_IE *ies, int ieCount)
{
    int i = 0;

    for (i=0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case M3UA_PRM_MSG_HDR:

            ies[i].param_data.msgHeader.msgLen = 
                              SOCK_HToNL(ies[i].param_data.msgHeader.msgLen);
            
            break;

        case M3UA_PRM_CAUSE_USER:

            ies[i].param_data.causeUsr.cause = 
                              SOCK_HToNS(ies[i].param_data.causeUsr.cause);

            ies[i].param_data.causeUsr.user = 
                              SOCK_HToNS(ies[i].param_data.causeUsr.user);
            
            break;

        case M3UA_PRM_CONGEST_LEVEL:

            ies[i].param_data.congestion.level = 
                              SOCK_HToNL(ies[i].param_data.congestion.level);

            break;
        
        }
    }

    return;
}



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change an ITS_M3UA_IE array to the HOST 
 *      format.
 *     
 *  Input Parameters:
 *      ieCount - number of element in the array.
 *
 *  Input/Output Parameters:
 *      ies - pointer to the first element of the array.
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
 ******************************************************************************/
void
M3UA_Nm3uaIESToH(ITS_M3UA_IE *ies, int ieCount)
{
    int i = 0;

    for (i=0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case M3UA_PRM_MSG_HDR:

            ies[i].param_data.msgHeader.msgLen = 
                              SOCK_NToHL(ies[i].param_data.msgHeader.msgLen);
            
            break;

        case M3UA_PRM_CAUSE_USER:

            ies[i].param_data.causeUsr.cause = 
                              SOCK_NToHS(ies[i].param_data.causeUsr.cause);

            ies[i].param_data.causeUsr.user = 
                              SOCK_NToHS(ies[i].param_data.causeUsr.user);
            
            break;

        case M3UA_PRM_CONGEST_LEVEL:

            ies[i].param_data.congestion.level = 
                              SOCK_NToHL(ies[i].param_data.congestion.level);

            break;
        
        }
    }

    return;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to encode a M3UA message from a given array of
 *      M3UA IES.
 *     
 *  Input Parameters:
 *      ies - pointer to the first element of IES array (common msg header).
 *      ieCount - number of IES in the array.
 *      desc - pointer to M3UA message descriptor.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      event - pointer to ITS_EVENT containing the built M3UA message.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
M3UADLLAPI int
M3UA_EncodeMsg(ITS_M3UA_IE *ies, int ieCount,ITS_EVENT *event,
               M3UA_MSG_DESC* desc)
{
    int i, j, offset, evoffset;
    ITS_M3UA_IE* ieRef[ITS_MAX_M3UA_IES];
    ITS_USHORT *margs = desc->mParam;
    int nmargs = desc->nmParam;
    ITS_USHORT *oargs = desc->oParam;
    int noargs = desc->noParam;
    ITS_USHORT len = 0, padding = 0;
    ITS_BOOLEAN sawOpt = ITS_FALSE;

    assert(event != NULL);

    M3UA_DEBUG(("M3UA_EncodeMsg: \n"));

    /* sanity */
    if (ieCount > ITS_MAX_M3UA_IES)
    {
        return (ITS_EOVERFLOW);
    }
     

    /* change the params to network format */
    M3UA_Hm3uaIESToN(ies, ieCount);

    /* 
     * The first step is to use a temporary array of IES* to
     * store ptrs to the message parameters in the following order
     * - the common header
     * - the madatory parameters
     * - the optional parameters if any
     * In the meanwhile we can check if all mandatory parameters are 
     * present for sanity purposes
     */

    /*
     * The first IE int the array should be the common message header
     * this is common to all M3UA messages
     */
    if(ies[0].param_id != M3UA_PRM_MSG_HDR)
    {
        return (ITS_EINVALIDARGS);
    }

    ieRef[0] = ies;

    /* start at one, 0 is the common msg header */
    offset = 1;

    /* find the mandatory parameters */
    for (i = 0; i < nmargs; i++)
    {
        for (j = 1; j < ieCount; j++) /* we can start at 1, 0 is message header */
        {
            if (ies[j].param_id == margs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }
    
    /* find the optionals */
    for (i = 0; i < noargs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (ies[j].param_id == oargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                sawOpt = ITS_TRUE;
                break;
            }
        }
        /* if missing, that's ok */
    }

    /* skip extras */
    while (offset <= ieCount)   /* we use <= because of the common 
                                   message header offset starts at 1 */
    {
        ieRef[offset] = NULL;
        offset++;
    }

    evoffset = sizeof(M3UA_MSG_HDR);

    /* copy in the mandatories */
    for (i = 1; i <= nmargs; i++)
    {
        /* cpy param id */
        ieRef[i]->param_id = SOCK_HToNS(ieRef[i]->param_id);

        memcpy(&event->data[evoffset], &ieRef[i]->param_id, 
               sizeof(ITS_USHORT));
        evoffset += 2;
        /* cpy param len */
        len = ieRef[i]->param_length;
        padding = M3UA_GetPadding(len);
        ieRef[i]->param_length = SOCK_HToNS((ITS_USHORT)(len + 4));

        memcpy(&event->data[evoffset], &ieRef[i]->param_length, 
               sizeof(ITS_USHORT));

        evoffset += 2;

        memset(&event->data[evoffset], 0, (len + padding)); 
        memcpy(&event->data[evoffset], &ieRef[i]->param_data, len);
  
        evoffset += (len + padding);
    }

    /* copy in the optionals */

    for (i = 1; i <= noargs; i++)
    {
        if (ieRef[i + nmargs] == NULL )
        {
            break;
        }

        /* cpy param id */
        ieRef[i + nmargs]->param_id = SOCK_HToNS(ieRef[i+nmargs]->param_id);


        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_id, 
               sizeof(ITS_USHORT));
        evoffset += 2;
        /* cpy param len */
        len = ieRef[i+nmargs]->param_length;
        padding = M3UA_GetPadding(len);
        ieRef[i + nmargs]->param_length = 
                                 SOCK_HToNS((ITS_USHORT)(len + 4));


        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_length, 
               sizeof(ITS_USHORT));

        evoffset += 2;


        memset(&event->data[evoffset], 0, (len + padding));
        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_data, len);
            
        evoffset += (len + padding);
    }

    /* set final length */
    event->len = evoffset;

    /* take care of the message length */
    ieRef[0]->param_data.msgHeader.msgLen = SOCK_HToNL(event->len);

    /* copy in the message header with updated message pointers */
    memcpy(&event->data[0], &ieRef[0]->param_data, sizeof(M3UA_MSG_HDR));

    /* WHAT ABOUT THE EVENT SOURCE -> left to the user to fill in */

    return (ITS_SUCCESS);

}




/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to decode a M3UA message to an array of M3UA IES.
 *     
 *  Input Parameters:
 *      ev - pointer to ITS_EVENT containing the M3UA message to be decoded.
 *      desc - pointer to the message descriptor.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      ies - pointer to the array of IES where the message is decoded.
 *      ieCount - number of decode IES in the array.
 *
 *  Return Value:
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *      This function is used internally that is not directly by the user.
 *
 *  See Also:
 *      M3UA_EncodeMsg().
 *
 ******************************************************************************/
M3UADLLAPI int
M3UA_DecodeMsg(ITS_M3UA_IE *ies, int *ieCount, ITS_EVENT *ev,
              M3UA_MSG_DESC *desc)
{
    ITS_USHORT msgLen = ev->len;
    int evOffset = 0;
    ITS_M3UA_IE *ieRef = ies;

    *ieCount = 0;

    M3UA_DEBUG(("M3UA_DecodeMsg: \n"));

    /* take care of the common msg header */
    ies[0].param_id = M3UA_PRM_MSG_HDR;
    ies[0].param_length = sizeof(M3UA_MSG_HDR);
    memcpy(&ies[0].param_data.msgHeader, &ev->data[evOffset], 
           sizeof(M3UA_MSG_HDR));

    M3UA_NComHdrToH(&ies[0].param_data.msgHeader);

    (*ieCount)++;
    ies++;
    evOffset += sizeof(M3UA_MSG_HDR);
    
    
    /* mandatory parameters */
    if (desc->nmParam != 0)   /* It can be possible */
    {
        int i;

        /* Need to fix: Check whether we are missing mandatory paramers if there 
         * two or more in the list.
         */
        if (evOffset >= ev->len)
        {
            return ITS_EMISSMAND;
        }

        for (i = 0; i < desc->nmParam; i++)
        {
            ies[0].param_id = ev->data[evOffset] << 8 | 
                              ev->data[evOffset + 1];
            evOffset += 2;
            ies[0].param_length = (ev->data[evOffset] << 8 | 
                                  ev->data[evOffset + 1]) - 4;
            evOffset += 2;

            if ((ies[0].param_length < msgLen) && (evOffset < ev->len)) 
            { 
                memcpy(&ies[0].param_data.data, &ev->data[evOffset], 
                       ies[0].param_length);

                evOffset += ies[0].param_length + M3UA_GetPadding(ies[0].param_length);
            
                (*ieCount)++;
    
                if (*ieCount > ITS_MAX_M3UA_IES)
                {
                    return (ITS_EOVERFLOW);
                }
       
                ies++;
            }
            else
            {
                return ITS_EOVERFLOW;
            }
        }  
    }


    /* if we have optional parameters take care of them too */
    if (desc->noParam != 0)
    {
        while (evOffset < msgLen)
        {
            ies[0].param_id = ev->data[evOffset] << 8 | 
                              ev->data[evOffset + 1];
            evOffset += 2;

            ies[0].param_length = (ev->data[evOffset] << 8 | 
                                  ev->data[evOffset + 1]) - 4;

            evOffset += 2;

            if ((ies[0].param_length < msgLen) && (evOffset < ev->len))
            { 
                memcpy(&ies[0].param_data.data, &ev->data[evOffset], 
                       ies[0].param_length);

                evOffset += ies[0].param_length + M3UA_GetPadding(ies[0].param_length); 

                (*ieCount)++;

                if (*ieCount > ITS_MAX_M3UA_IES)
                {
                    return (ITS_EOVERFLOW);
                }

                ies++;
            }
            else
            {
                return ITS_EOVERFLOW;
            }
        }
    }

    /* put the params in the host format */
    M3UA_Nm3uaIESToH(ieRef, *ieCount);

    return (ITS_SUCCESS);
}

static void
M3UA_Pause(MTP3_PAUSE_RESUME *pause, UALMgntData *mgnt, SCTPTRAN_Manager *tc)
{
    MTP3_HEADER hdr;
    ITS_EVENT   evt;

    M3UA_DEBUG(("M3UA_Pause: \n"));

    hdr.sio = mgnt->cdata.info.sio;
    MTP3_RL_SET_OPC_VALUE(hdr.label, MTP3_PC_GET_VALUE(pause->affected));
    MTP3_RL_SET_DPC_VALUE(hdr.label, mgnt->cdata.info.pc);
    MTP3_RL_SET_SLS(hdr.label, 0);

    MTP3_Encode(&evt, MTP3_MSG_PAUSE, &hdr,
                (ITS_OCTET *)pause, sizeof(MTP3_PAUSE_RESUME));

    CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                              (ITS_POINTER) tc,
                              (ITS_POINTER) &evt);

    ITS_EVENT_TERM(&evt);
}


static void 
M3UA_Resume(MTP3_PAUSE_RESUME *resume, UALMgntData *mgnt, SCTPTRAN_Manager *tc)
{
    MTP3_HEADER hdr;
    ITS_EVENT   evt;

    M3UA_DEBUG(("M3UA_Resume: \n"));

    hdr.sio = mgnt->cdata.info.sio;
    MTP3_RL_SET_OPC_VALUE(hdr.label, MTP3_PC_GET_VALUE(resume->affected));
    MTP3_RL_SET_DPC_VALUE(hdr.label, mgnt->cdata.info.pc);
    MTP3_RL_SET_SLS(hdr.label, 0);

    MTP3_Encode(&evt, MTP3_MSG_RESUME, &hdr,
                (ITS_OCTET *)resume, sizeof(MTP3_PAUSE_RESUME)); 

    CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                              (ITS_POINTER) tc,
                              (ITS_POINTER) &evt);

    ITS_EVENT_TERM(&evt);
}

static void
Send_Parm_ERROR(SCTPTRAN_Manager *m, ITS_UINT ecode, ITS_M3UA_IE *Ies)
{
    ITS_EVENT evt;
    ITS_INT   ieC = 0;
    ITS_INT   ret = 0;
    ITS_M3UA_IE ies[10];

    M3UA_DEBUG(("Send_Parm_ERROR: \n"));

    memset(ies, 0, 10 * sizeof(ITS_M3UA_IE));

    ies[ieC].param_id = M3UA_PRM_MSG_HDR;
    ies[ieC].param_length =  sizeof(M3UA_MSG_HDR);
    ies[ieC].param_data.msgHeader.msgClass = UAL_CLASS_MGMT; 
    ies[ieC].param_data.msgHeader.msgType  = UAL_MSG_ERR;
    ies[ieC].param_data.msgHeader.version  = M3UA_PROT_VER1;

    ieC++;    

    ies[ieC].param_id = UAL_PRM_ERROR_CODE;
    ies[ieC].param_length =  sizeof(UAL_ERROR_CODE);
    ies[ieC].param_data.errorCode.eCode = SOCK_HToNL(ecode);
    
    ieC++;

    if (Ies != NULL)
    {
        /* Add additional ies depending on error codes */
        memcpy(&ies[ieC], Ies, sizeof(ITS_M3UA_IE));

        ieC++;
    }

    ITS_EVENT_INIT(&evt, UAL_MANAGER_INSTANCE, 256);

    ret = M3UA_EncodeMsg(ies, ieC, &evt, &M3UA_ERROR_Desc);

    if (ret == ITS_SUCCESS)
    {
        TRANSPORT_PutEvent(TRANSPORT_INSTANCE(m), &evt);
    }
    else
    {
        M3UA_ERROR(("Send_Parm_ERROR: encode failed. ret = %d\n", ret));
    }

     ITS_EVENT_TERM(&evt);
}
 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert from M3UA to MTP3
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
 *
 *  DATA ---> MTP3-Transfer 
 *  DUNA ---> MTP-Pause
 *  DAVA ---> MTP-Resume
 *  DAUD ---> MTP-Status
 * 
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference      Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005                 Modified to change Traces from  
 *                                      ITS_TRACE to M3UA.
 * adutta    04-06-2005  BugId:1670     Peg count for DAUD incremented.
 *
 * gdevanand 05-03-2005  BugId:1795     Peg count for DAUD incremented.
 *
 *  See Also:
 ****************************************************************************/
M3UADLLAPI int
M3UA_To_MTP3_Codec(SCTPTRAN_Manager* m, ITS_EVENT *evt, ITS_BOOLEAN *isMgmt, 
                   ITS_OCTET *sls)
{
    int ret = ITS_SUCCESS;
    M3UA_MSG_HDR commonHdr;
    ITS_M3UA_IE ies[10];
    int ieCount = 0;
    MTP3_POINT_CODE pc;
    UAL_MIB_STATS *stats;

    M3UA_DEBUG(("M3UA_To_MTP3_Codec: \n"));
    PRINT_EVENT(evt);

    memcpy(&commonHdr, evt->data, sizeof(M3UA_MSG_HDR));

    stats = UALPEGMgr_GetStats(TRANSPORT_INSTANCE(m));
	
    if (commonHdr.msgLen < 8)
    {
       /* 1 - version, 1 - reserved, 1 - msgClass, 1 - msgType, 4 - msgLen */
       Send_Parm_ERROR (m, UAL_ERR_UNSUP_MSG_TYPE, NULL);
       return ITS_EPROTERR;
    }

    /* 
     * if it is an ASP management message it is for the Management instance
     * set the flag and return
     */
    if (((commonHdr.msgClass != M3UA_CL_TRANSFER_MSG) &&
        (commonHdr.msgClass != M3UA_CL_SSNM_MSG)) || 
        (commonHdr.version != M3UA_PROT_VER1))
    {
        if (*sls != 0x00)
        {
           if (commonHdr.msgClass == UAL_CLASS_MGMT &&
               commonHdr.msgType  == UAL_MSG_ERR)
           {
              M3UA_ERROR(("Error msg received on Invalid Stream "
                               "Message dropped\n"));
           }
           else if( commonHdr.msgClass != UAL_CLASS_ASPTM)
           {
              Send_Parm_ERROR (m, UAL_ERR_INV_STREAM_ID, NULL);
              return ITS_EPROTERR;
           }
        }

        *isMgmt = ITS_TRUE;
        return ITS_SUCCESS;
    }

    if (commonHdr.msgClass == M3UA_CL_SSNM_MSG)
    {
        switch(commonHdr.msgType)
        {
        case M3UA_MSG_DUNA:
        {
            /* converts to an MTP_PAUSE msg */
            MTP3_PAUSE_RESUME pause;
            MTP3_HEADER hdr;
            ITS_M3UA_IE *ieTmp = NULL;   
            UALMgntData ualData;

            /* log an alarm */
            M3UA_Alarm(4027, __FILE__, __LINE__, NULL);

            ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_DUNA_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Error Decoding DUNA msg\n"));
                break;
            }

            ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
            if (ieTmp != NULL)
            {
                ITS_UINT rCtxts[M3UA_MAX_RK_NUM]; /* TODO may need larger Array...*/
                int numRctxt = 0;

                ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                ieTmp->param_length, rCtxts,
                                                &numRctxt);
                if (ret != ITS_SUCCESS)
                {
                    M3UA_ERROR(("M3UA, malformed Routing Ctxt.\n"));

                    return ITS_EMISSMAND;
                }

                if (!UAL_IsRCtxtValid(*rCtxts))
                {
                    Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);

                    return ITS_EMISSMAND;
                }
            }

            ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_AFFECTED_PC);
            if (ieTmp == NULL)
            {
                M3UA_ERROR(("Missing Affected PC in DUNA msg\n"));
                if (stats)
                {
                    stats->errOut++;
                }

                ret=ITS_EMISSMAND;
                break;
            }

            if (stats)
            {
                stats->duna++;
            }

#if defined(CCITT) || defined(TTC)
            memcpy(pc.data, &ieTmp->param_data.apc.apc.data[1],
                   sizeof(MTP3_POINT_CODE_CCITT));

            pause.affected.data[0] = pc.data[1];
            pause.affected.data[1] = pc.data[0];
        
#elif defined(ANSI)
            memcpy(pc.data, ieTmp->param_data.apc.apc.data,
                   sizeof(MTP3_POINT_CODE_ANSI));

            pause.affected.data[0] = pc.data[2];
            pause.affected.data[1] = pc.data[1];
            pause.affected.data[2] = pc.data[0];
#elif defined(PRC)
            memcpy(pc.data, ieTmp->param_data.apc.apc.data,
                   sizeof(MTP3_POINT_CODE_PRC));

            pause.affected.data[0] = pc.data[2];
            pause.affected.data[1] = pc.data[1];
            pause.affected.data[2] = pc.data[0];
#endif

            ret = MTP3_Encode(evt, MTP3_MSG_PAUSE, &hdr,
                              (ITS_OCTET*)&pause, sizeof(MTP3_PAUSE_RESUME));
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Error encoding PAUSE\n"));

                return ret;
            }

            ualData.type = UAL_MTP3_PAUSE;
            ualData.cdata.mtp3_info.pc = MTP3_PC_GET_VALUE(pause.affected);

            PauseCallback((ITS_POINTER)m, (ITS_POINTER)&pause, (ITS_POINTER)&ualData);

            break;
        }
        case M3UA_MSG_DAVA:
        case M3UA_MSG_DRST:
        {
            /* converts to an MTP_RESUME msg */
            MTP3_PAUSE_RESUME resume;
            MTP3_HEADER hdr;
            ITS_M3UA_IE *ieTmp = NULL;   
            UALMgntData ualData;

            /* log an alarm */
            M3UA_Alarm(4028, __FILE__, __LINE__, NULL);

            ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_DAVA_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Error Decoding DAVA msg\n"));
                break;
             }
             if (stats)
             {
                if (commonHdr.msgType == M3UA_MSG_DAVA)
                {
                    stats->dava++;
                }
                else
                {
                    stats->drst++;
                }
            }
            ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
            if (ieTmp != NULL)
            {
                ITS_UINT rCtxts[M3UA_MAX_RK_NUM]; /* TODO may need larger Array...*/
                int numRctxt = 0;

                ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                ieTmp->param_length, rCtxts,
                                                &numRctxt);
                if (ret != ITS_SUCCESS)
                {
                    M3UA_ERROR(("M3UA, malformed Routing Ctxt.\n"));

                    return ITS_EMISSMAND;
                }

                if (!UAL_IsRCtxtValid(*rCtxts))
                {
                    Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);

                    return ITS_EMISSMAND;
                }
            }

            ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_AFFECTED_PC);
            if (ieTmp == NULL)
            {
                M3UA_ERROR(("Missing Affected PC in DAVA msg\n"));
                if (stats)
                {
                    stats->errOut++;
                }
                ret=ITS_EMISSMAND;
                break;
            }

#if defined(CCITT) || defined(TTC)
            memcpy(pc.data, &ieTmp->param_data.apc.apc.data[1],
                   sizeof(MTP3_POINT_CODE_CCITT));
            resume.affected.data[0] = pc.data[1];
            resume.affected.data[1] = pc.data[0];
#elif defined(ANSI)
            memcpy(pc.data, ieTmp->param_data.apc.apc.data,
                   sizeof(MTP3_POINT_CODE_ANSI));

            resume.affected.data[0] = pc.data[2];
            resume.affected.data[1] = pc.data[1];
            resume.affected.data[2] = pc.data[0];
#elif defined(PRC)
            memcpy(pc.data, ieTmp->param_data.apc.apc.data,
                   sizeof(MTP3_POINT_CODE_PRC));

            resume.affected.data[0] = pc.data[2];
            resume.affected.data[1] = pc.data[1];
            resume.affected.data[2] = pc.data[0];
#endif

            ret = MTP3_Encode(evt, MTP3_MSG_RESUME, &hdr,
                              (ITS_OCTET*)&resume, sizeof(MTP3_PAUSE_RESUME));
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Error encoding RESUME\n"));

                return ret;
            }

            ualData.type = UAL_MTP3_RESUME;
            ualData.cdata.mtp3_info.pc = MTP3_PC_GET_VALUE(resume.affected);

            ResumeCallback((ITS_POINTER)m, (ITS_POINTER)&resume, (ITS_POINTER)&ualData);

            break;
        }
        case M3UA_MSG_SCON:
        {
            MTP3_STATUS status;
            MTP3_HEADER hdr;
            ITS_M3UA_IE *ieTmp = NULL;   

            /* log an alarm */
            M3UA_Alarm(4029, __FILE__, __LINE__, NULL);

            ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_SCON_Desc);
            if (ret == ITS_SUCCESS)
            {
                ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
                if (ieTmp != NULL)
                {
                    ITS_UINT rCtxts[M3UA_MAX_RK_NUM]; /* TODO may need larger Array...*/
                    int numRctxt = 0;

                    ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                    ieTmp->param_length, rCtxts,
                                                    &numRctxt);
                    if (ret != ITS_SUCCESS)
                    {
                        M3UA_ERROR(("M3UA, malformed Routing Ctxt.\n"));

                        return ITS_EMISSMAND;
                    }

                    if (!UAL_IsRCtxtValid(*rCtxts))
                    {
                        Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);

                        return ITS_EMISSMAND;
                    }
                }

                ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_AFFECTED_PC);
            }

            if (ieTmp == NULL || ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Missing Affected PC in SCON msg\n"));
         
                if (stats)
                {
                    stats->errOut++;
                }

                ret = ITS_EMISSMAND;
                break;
            }
            if (stats)
            {
                stats->sconIn++;
            }

#if defined(CCITT) || defined(TTC)
            memcpy(pc.data, &ieTmp->param_data.apc.apc.data[1],
                   sizeof(MTP3_POINT_CODE));
            status.affected.data[0] = pc.data[1];
            status.affected.data[1] = pc.data[0];
#elif defined(ANSI)
            memcpy(status.affected.data, ieTmp->param_data.apc.apc.data,
                   sizeof(MTP3_POINT_CODE_ANSI));
#elif defined(PRC)
            memcpy(status.affected.data, ieTmp->param_data.apc.apc.data,
                   sizeof(MTP3_POINT_CODE_PRC));
#endif

            ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_CONGEST_LEVEL);
            if (ieTmp == NULL)
            {
                M3UA_WARNING(("Missing Cong Level in SCON msg\n"));
            }
            else
            {
                status.congLevel = (ieTmp->param_data.congestion.level & 0xFF);

                if (ieTmp->param_data.congestion.level < 0 || 
                    ieTmp->param_data.congestion.level > 3)
                {
                     Send_Parm_ERROR(m, UAL_ERR_INV_PARM_VALUE, NULL);
                     if (stats)
                     {
                        stats->errOut++;
                     }
                    return ITS_EMISSMAND;
                }
            }

            ret = MTP3_Encode(evt, MTP3_MSG_STATUS, &hdr,
                              (ITS_OCTET*)&status, sizeof(MTP3_STATUS));
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Error encoding STATUS\n"));

                return ret;
            }

            StatusCallback((ITS_POINTER)m, NULL, (ITS_POINTER)evt);

            break;
        }
        case M3UA_MSG_DUPU:
        {
            MTP3_STATUS     status;
            MTP3_HEADER     hdr;
#if defined(CCITT) || defined(TTC)
            MTP3_POINT_CODE pc;
#endif
            int             i, j, c;
            ITS_M3UA_IE *ieTmp = NULL;   

            i = j = -1;

            ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_DUPU_Desc);

            for (c = 0; (ret == ITS_SUCCESS) && (c < ieCount); c++)
            {
                if (ies[c].param_id == M3UA_PRM_AFFECTED_PC)
                {
                    i = c;  /* Affected point code index */
                }
                else if (ies[c].param_id == M3UA_PRM_CAUSE_USER)
                {
                    j = c;  /* USER and CAUSE param index */
                }
            }

            if (i == -1 || j == -1)
            {
               if (stats)
               {
                   stats->errOut++;
               }
               ret = ITS_EMISSMAND;
               break;
            }
            if (stats)
            {
                stats->dupu++;
            }
            ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
            if (ieTmp != NULL)
            {
                ITS_UINT rCtxts[M3UA_MAX_RK_NUM]; /* TODO may need larger Array...*/
                int numRctxt = 0;

                ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                ieTmp->param_length, rCtxts,
                                                &numRctxt);
                if (ret != ITS_SUCCESS)
                {
                    M3UA_ERROR(("M3UA, malformed Routing Ctxt.\n"));

                    return ITS_EMISSMAND;
                }

                if (!UAL_IsRCtxtValid(*rCtxts))
                {
                    Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);

                    return ITS_EMISSMAND;
                }
            }

#if defined(CCITT) || defined(TTC)
            memcpy(pc.data, &ies[i].param_data.apc.apc.data[1],
                   sizeof(MTP3_POINT_CODE));
            status.affected.data[0] = pc.data[1];
            status.affected.data[1] = pc.data[0];
#elif defined(ANSI)
            memcpy(status.affected.data, ies[i].param_data.apc.apc.data,
                   sizeof(MTP3_POINT_CODE_ANSI));
#elif defined(PRC)
            memcpy(status.affected.data, ies[i].param_data.apc.apc.data,
                   sizeof(MTP3_POINT_CODE_PRC));
#endif

            c = (ies[j].param_data.causeUsr.cause & 0xFF);

            if (c == M3UA_UNKNOWN_CAUSE)
            {
                status.cause = MTP3_STATUS_UPU_UNKNOWN;
            }
            else if (c == M3UA_UNEQUIP_REMOTE_USR)
            {
                status.cause = MTP3_STATUS_UPU_UNEQUIP;
            }
            else if (c == M3UA_INACCESS_REMOTE_USR)
            {
                status.cause = MTP3_STATUS_UPU_INACCESS;
            }
            else
            {
                Send_Parm_ERROR(m, UAL_ERR_INV_PARM_VALUE, NULL);
                
                if (stats)
                {
                    stats->errOut++;
                }
                M3UA_WARNING(("Received Invalid cause.\n"));

                return !ITS_SUCCESS;
            }

            ret = MTP3_Encode(evt, MTP3_MSG_STATUS, &hdr,
                              (ITS_OCTET*)&status, sizeof(MTP3_STATUS));
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Error encoding STATUS\n"));

                return ret;
            }

            StatusCallback((ITS_POINTER)m, NULL, (ITS_POINTER)evt);

            break;
        }
        case M3UA_MSG_DAUD:
        {
            if (stats)
            {
                stats->daud++;
            }
#ifdef USING_DAUD
            ITS_M3UA_IE *ieTmp = NULL;
            ITS_UINT ieCount = 0;
            MTP3_PAUSE_RESUME pr;

            ITS_UINT dpc = 0;
            ITS_BOOLEAN isUp;
            ITS_EVENT m3uaEvt;
            ITS_OCTET msgType = 0;
            SS7_Family family;

            M3UA_DEBUG(("DAUD Received\n"));

            ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_DAUD_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Error Decoding DAUD msg\n"));

                return ret;
            }

            ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_AFFECTED_PC);
            if (ieTmp == NULL)
            {
                M3UA_ERROR(("Missing Affected PC in DAUD msg\n"));

                Send_Parm_ERROR(m, UAL_ERR_MISSING_PARAM, NULL);

                if (stats)
                {
                    stats->errOut++;
                }

                return ITS_EMISSMAND;
            }

#if defined(CCITT)
            memcpy(pc.data, &ieTmp->param_data.apc.apc.data[1],
                   sizeof(MTP3_POINT_CODE_CCITT));
            pr.affected.data[0] = pc.data[1];
            pr.affected.data[1] = pc.data[0];

            /* affected destination */
            dpc = MTP3_PC_GET_VALUE_CCITT(pr.affected);
            family = FAMILY_ITU;
#elif defined(ANSI)
            memcpy(pc.data, ieTmp->param_data.apc.apc.data,
                   sizeof(MTP3_POINT_CODE_ANSI));

            pr.affected.data[0] = pc.data[2];
            pr.affected.data[1] = pc.data[1];
            pr.affected.data[2] = pc.data[0];

            /* affected destination */
            dpc = MTP3_PC_GET_VALUE_ANSI(pr.affected);
            family = FAMILY_ANSI;
#endif

            M3UA_DEBUG(("Affected PC = %d", dpc));

            ret = ROUTE_GetRouteContextState(
                        dpc,
                        &isUp,
                        ROUTE_DPC_NI,
                        family,
                        0x00,
                        ITS_SS7_DEFAULT_LINK_SET,
                        ITS_SS7_DEFAULT_LINK_CODE);
            if (ret == ITS_SUCCESS)
            {
                if (isUp)
                {
                    M3UA_DEBUG(("Destination Available DPC = %d", dpc));

                    msgType = M3UA_MSG_DAVA;
                }
                else
                {
                    M3UA_ERROR(("Destination Unavailable DPC = %d", dpc));

                    msgType =  M3UA_MSG_DUNA;
                }
            }
            else
            {
                ret = ROUTE_GetRouteContextState(
                            dpc,
                            &isUp,
                            ROUTE_DPC_NI,
                            family,
                            0x80,
                            ITS_SS7_DEFAULT_LINK_SET,
                            ITS_SS7_DEFAULT_LINK_CODE);
                if (ret == ITS_SUCCESS)
                {
                    if (isUp)
                    {
                        M3UA_DEBUG(("Destination Available DPC = %d", dpc));

                        msgType = M3UA_MSG_DAVA;
                    }
                    else
                    {
                         M3UA_DEBUG(("Destination Unavailable DPC = %d", dpc));

                         msgType =  M3UA_MSG_DUNA;
                    }
                }
                else
                {
                    ret = ROUTE_GetRouteContextState(
                                dpc,
                                &isUp,
                                ROUTE_DPC_NI,
                                family,
                                0x40,
                                ITS_SS7_DEFAULT_LINK_SET,
                                ITS_SS7_DEFAULT_LINK_CODE);
                    if (ret == ITS_SUCCESS)
                    {
                        if (isUp)
                        {
                            M3UA_DEBUG(("Destination Available DPC = %d", dpc));

                            msgType = M3UA_MSG_DAVA;
                        }
                        else
                        {
                             M3UA_DEBUG(("Destination Unavailable DPC = %d", dpc));

                             msgType =  M3UA_MSG_DUNA;
                        }
                    }
                    else
                    {
                        ret = ROUTE_GetRouteContextState(
                                    dpc,
                                    &isUp,
                                    ROUTE_DPC_NI,
                                    family,
                                    0xC0,
                                    ITS_SS7_DEFAULT_LINK_SET,
                                    ITS_SS7_DEFAULT_LINK_CODE);
                        if (ret == ITS_SUCCESS)
                        {
                            if (isUp)
                            {
                                M3UA_DEBUG(("Destination Available DPC = %d", dpc));

                                msgType = M3UA_MSG_DAVA;
                            }
                            else
                            {
                                 M3UA_DEBUG(("Destination Unavailable DPC = %d", dpc));

                                 msgType =  M3UA_MSG_DUNA;
                            }
                        }
                        else
                        {
                            M3UA_ERROR (("Error Getting Route Context"));
                            return ret;
                        }
                    }
                }
            }

            /*Get the SLS value */
            *sls = 1 % 32;

            ies[0].param_id = M3UA_PRM_MSG_HDR;
            ies[0].param_length = sizeof(M3UA_MSG_HDR);
            ies[0].param_data.msgHeader.msgClass = M3UA_CL_SSNM_MSG;
            ies[0].param_data.msgHeader.msgType = msgType;
            ies[0].param_data.msgHeader.version = M3UA_PROT_VER1;

            ies[1].param_id = M3UA_PRM_AFFECTED_PC;
            ies[1].param_length = sizeof(M3UA_AFFECTED_PC);
            ies[1].param_data.apc.apc.mask = 0x00;

#if defined(CCITT)
            ies[1].param_data.apc.apc.data[0] = 0x00;
            pc.data[0] = pr.affected.data[1];
            pc.data[1] = pr.affected.data[0];
            memcpy(&ies[1].param_data.apc.apc.data[1], pc.data,
                   sizeof(MTP3_POINT_CODE_CCITT));

#elif defined(ANSI)
            ies[1].param_data.apc.apc.data[0] = 0x00;
            pc.data[0] = pr.affected.data[2];
            pc.data[1] = pr.affected.data[1];
            pc.data[2] = pr.affected.data[0];
            memcpy(ies[1].param_data.apc.apc.data, pc.data,
                   sizeof(MTP3_POINT_CODE_ANSI));
#endif

            ITS_EVENT_INIT(&m3uaEvt, UAL_MANAGER_INSTANCE, 256);

            if (msgType == M3UA_MSG_DAVA)
            {
                ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DAVA_Desc);
            }
            else if (msgType == M3UA_MSG_DUNA)
            {
                ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DUNA_Desc);
            }

            if (ret == ITS_SUCCESS)
            {
                ret = TRANSPORT_PutEvent(TRANSPORT_INSTANCE(m), &m3uaEvt);
                if (ret == ITS_SUCCESS)
                {
                   if (msgType == M3UA_MSG_DAVA)
                   {
                      M3UA_DEBUG(("Destination Available, DAVA Sent"));
                   }
                   else if (msgType == M3UA_MSG_DUNA)
                   {
                      M3UA_DEBUG(("Destination Unavailable, DUNA Sent"));
                   }

                }
                else
                {
                     M3UA_ERROR(("Error Sending DAUD Resp, ret = %d\n", ret));
                }
            }
            else
            {
                M3UA_ERROR(("Error Sending DAUD Resp, ret = %d\n", ret));
            }

            ITS_EVENT_TERM(evt);

            /* Stop processing here; rcvd event responded */
            return (!ITS_SUCCESS);

#endif
            break;
        }
        default:

            Send_Parm_ERROR(m, UAL_ERR_UNSUP_MSG_TYPE, NULL);
            
            if (stats)
            {
                stats->errOut++;
            }
            break;

        }

        if (ret == ITS_EMISSMAND)
        {
            /*
             * Send an error message for a missing mandator.
             */
            Send_Parm_ERROR(m, UAL_ERR_MISSING_PARAM, NULL);
        }

        return ret;
    }
    else if (commonHdr.msgClass == M3UA_CL_TRANSFER_MSG)
    {
        ITS_M3UA_IE *ieTmp = NULL;
        MTP3_HEADER hdr;
        MTP3_POINT_CODE pc, pcTmp;

        UAL_ASP_STATE aspState;
        ITS_USHORT trid = TRANSPORT_INSTANCE(m);

        /* Check for ASP state before processing */
        ret = UAL_GetASPState(trid, &aspState);
        if (ret == ITS_SUCCESS) 
        {
           if (aspState != UAL_ASP_ACTIVE) 
           {
              ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_DATA_Desc);
              if (ret == ITS_SUCCESS)
              {
                 ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
              }

              if (UAL_GetIntWorkingMode() == UAL_ITW_SG)
              {
                  Send_Parm_ERROR (m, UAL_ERR_UNEPECTED_MSG, ieTmp);
              }
              else
              {
                  M3UA_ERROR(("Message discarded, ASP state = %d\n", aspState));
              }
              return ITS_EBADSTATE;
           }
        }
        else
        {
           return ret;
        }

        switch(commonHdr.msgType)
        {
        case M3UA_MSG_PAYLOAD_DATA:
        {
            ret = M3UA_DecodeMsg(ies, &ieCount, evt, &M3UA_DATA_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Failed to decode M3UA DATA Msg\n"));
                break;                
            }

            if (stats)
            {
                stats->dataIn++;
            }

            /* We look if the Routing Context param is present */
            ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_ROUT_CTX);
            if (ieTmp != NULL)
            {
                ITS_UINT rCtxts[M3UA_MAX_RK_NUM]; /* TODO may need larger Array...*/
                int numRctxt = 0;

                ret = M3UA_DecodeRoutingContext(ieTmp->param_data.rCtxt.rCtxt,
                                                ieTmp->param_length, rCtxts, 
                                                &numRctxt);
                if (ret != ITS_SUCCESS)
                {
                    M3UA_ERROR(("M3UA, malformed Routing Ctxt.\n"));

                    return ITS_EMISSMAND;  
                }

                if (!UAL_IsRCtxtValid(*rCtxts))
                {
                    Send_Parm_ERROR(m, UAL_ERR_INV_ROUT_CTXT, ieTmp);
                    if (stats)
                    {
                        stats->errOut++;
                    }
                    return ITS_EMISSMAND;
                } 
            }

            ieTmp = M3UA_FindM3UAIE(ies, ieCount, M3UA_PRM_DATA);
            if (ieTmp == NULL) 
            {
                M3UA_ERROR(("Failed to decode M3UA DATA Msg\n"));
                if (stats)
                {
                    stats->errOut++;
                }
                return ITS_EMISSMAND;
                break;
            }

#if defined(CCITT) || defined(TTC)
            memcpy(&pcTmp, &ieTmp->param_data.data.dpc.data[1], 
                   sizeof(MTP3_POINT_CODE));
            pc.data[0] = pcTmp.data[1];  /* TODO remove after bakeoff */
            pc.data[1] = pcTmp.data[0];
            MTP3_RL_SET_DPC(hdr.label, pc);
            memcpy(&pcTmp, &ieTmp->param_data.data.opc.data[1],
                   sizeof(MTP3_POINT_CODE));
            pc.data[0] = pcTmp.data[1];  /* TODO remove after bakeoff */
            pc.data[1] = pcTmp.data[0];
            MTP3_RL_SET_OPC(hdr.label, pc);
            MTP3_RL_SET_SLS(hdr.label, ieTmp->param_data.data.sls);
#elif defined(ANSI)
            memcpy(&pcTmp, ieTmp->param_data.data.dpc.data,
	                   sizeof(MTP3_POINT_CODE));
            pc.data[0] = pcTmp.data[2];
            pc.data[1] = pcTmp.data[1];
            pc.data[2] = pcTmp.data[0];
            MTP3_RL_SET_DPC_ANSI(hdr.label, pc);

            memcpy(&pcTmp, ieTmp->param_data.data.opc.data,
	                   sizeof(MTP3_POINT_CODE));
            pc.data[0] = pcTmp.data[2];
            pc.data[1] = pcTmp.data[1];
            pc.data[2] = pcTmp.data[0];
            MTP3_RL_SET_OPC_ANSI(hdr.label, pc);

            MTP3_RL_SET_SLS_ANSI(hdr.label, ieTmp->param_data.data.sls);
#elif defined(PRC)
            memcpy(&pcTmp, ieTmp->param_data.data.dpc.data,
                       sizeof(MTP3_POINT_CODE));
            pc.data[0] = pcTmp.data[2];
            pc.data[1] = pcTmp.data[1];
            pc.data[2] = pcTmp.data[0];
            MTP3_RL_SET_DPC_PRC(hdr.label, pc);

            memcpy(&pcTmp, ieTmp->param_data.data.opc.data,
                       sizeof(MTP3_POINT_CODE));
            pc.data[0] = pcTmp.data[2];
            pc.data[1] = pcTmp.data[1];
            pc.data[2] = pcTmp.data[0];
            MTP3_RL_SET_OPC_PRC(hdr.label, pc);

            MTP3_RL_SET_SLS_PRC(hdr.label, ieTmp->param_data.data.sls);
#endif
            hdr.sio = ieTmp->param_data.data.si;
            hdr.sio |= ((ieTmp->param_data.data.ni << 6) & 0xC0); 

            /*deallocate memory if it has been already been allocated for evt*/
            ITS_EVENT_TERM(evt);

            ret = MTP3_Encode(evt, MTP3_MSG_USER_DATA, &hdr,
                              (ieTmp->param_data.data.data),
                              (ITS_USHORT)(ieTmp->param_length - 12));
            
             if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Failed to encode M3UA DATA Msg\n"));

                return ret;
            }
             break;           

        }
          default:
            Send_Parm_ERROR(m, UAL_ERR_UNSUP_MSG_TYPE, NULL);

            break;
        }

        if (ret == ITS_EMISSMAND)
        {
            /*
             * Send an error message for a missing mandator.
             */
            Send_Parm_ERROR(m, UAL_ERR_MISSING_PARAM, NULL);
        }

        return ret;
    }
    else
    {
        Send_Parm_ERROR(m, UAL_ERR_UNSUP_MSG_CLASS, NULL);
        if (stats)
        {
            stats->errOut++;
        }
    }

    return (ITS_SUCCESS);
}

static ITS_USHORT
SelectStream(ITS_OCTET sls, ITS_USHORT availStreams)
{
    ITS_USHORT stream = 0;

    M3UA_DEBUG(("SelectStream: \n"));

    stream = (sls % availStreams);

    /* avoid sending on stream 0 */
    if (stream == 0)
    {
        stream++;
    }

    return stream;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert from MTP3 to M3UA
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
 *
 *  See Also:
 ****************************************************************************/
M3UADLLAPI int
MTP3_To_M3UA_Codec(SCTPTRAN_Manager* m, ITS_EVENT *evt, ITS_BOOLEAN *isMgmt, 
                   ITS_OCTET *sls)
{
    ITS_OCTET msgType, data[MTP3_MAX_SIF_LENGTH];
    ITS_USHORT  len = 0, outStreams = 1;
    MTP3_HEADER hdr;
    ITS_M3UA_IE ies[6];
    int ret = ITS_SUCCESS;
    ITS_UINT ieCount = 0;
    ITS_EVENT m3uaEvt;
    ITS_USHORT trid = TRANSPORT_INSTANCE(m); 
    UAL_ASP_STATE aspState;
    UAL_MIB_STATS *stats;  
    assert(evt != NULL);

    M3UA_DEBUG(("MTP3_To_M3UA_Codec: \n"));

    stats = UALPEGMgr_GetStats(TRANSPORT_INSTANCE(m));

    if (*isMgmt)
    {
        *sls = 0x00;
        return ITS_SUCCESS;
    }

    /* Check if ASP is ACTIVE first */
    M3UA_DEBUG((" ----- checking ASP STATE -----\n"));

    ret = UAL_GetASPState(trid, &aspState);
    if (ret != ITS_SUCCESS)
    {
        M3UA_ERROR(("Send failed no ASP State.\n"));

        return ret;
    }

    if (aspState != UAL_ASP_ACTIVE)
    {
        UAL_CB_Context cb_ctxt;

        memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

        M3UA_ERROR(("M3UA Codec, User trying to Send while not ACTIVE.\n"));

        UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_RT_FAIL_CTXT;
        UAL_CB_CTXT_MSU_LEN(&cb_ctxt)   = evt->len;
        memcpy(UAL_CB_CTXT_MSU_DATA(&cb_ctxt), evt->data, evt->len); 

        CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                  (ITS_POINTER)&cb_ctxt);

        ITS_EVENT_TERM(evt);

        return (ITS_EBADSTATE);
    }

    ITS_EVENT_INIT(&m3uaEvt, ITS_MTP3_SRC, M3UA_MAX_DATA_SIZE);
     
    /* if event source is MTP3, skip the 3 first bytes */
    if (evt->src == ITS_MTP3_CCITT_SRC ||
        evt->src == ITS_MTP3_ANSI_SRC ||
        evt->src == ITS_MTP3_TTC_SRC ||
        evt->src == ITS_MTP3_PRC_SRC)
    {
        m3uaEvt.data[0] = MTP3_MSG_USER_DATA;

        memcpy(&(m3uaEvt.data[1]), &(evt->data[4]), (evt->len - 4));
  
        m3uaEvt.len = evt->len - 3;
    }
    else
    {
        memcpy(m3uaEvt.data, evt->data, evt->len);

        m3uaEvt.len = evt->len;
    }

    ITS_EVENT_TERM(evt);

    ret = MTP3_Decode(&m3uaEvt, &msgType, &hdr, data, &len);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get the SLS value */
    *sls = SelectStream(MTP3_RL_GET_SLS(hdr.label), outStreams);

    switch(msgType)
    {
    case MTP3_MSG_USER_DATA:
    {
        MTP3_POINT_CODE pc, pcTmp;

        ies[ieCount].param_id = M3UA_PRM_MSG_HDR;
        ies[ieCount].param_length = sizeof(M3UA_MSG_HDR);
        ies[ieCount].param_data.msgHeader.msgClass = M3UA_CL_TRANSFER_MSG;
        ies[ieCount].param_data.msgHeader.msgType = M3UA_MSG_PAYLOAD_DATA;
        ies[ieCount].param_data.msgHeader.version = M3UA_PROT_VER1;
       
        ieCount++;

        ies[ieCount].param_id = M3UA_PRM_DATA;
        ies[ieCount].param_length = len + M3UA_HDR_SIZE;

#if defined(CCITT) || defined(TTC)
        /* DPC */
        MTP3_RL_GET_DPC(hdr.label, pcTmp);

        ies[ieCount].param_data.data.dpc.data[0] = 0x00;

        pc.data[0] = pcTmp.data[1]; 
        pc.data[1] = pcTmp.data[0]; 

        memcpy(&ies[ieCount].param_data.data.dpc.data[1], pc.data, 2);

        /* OPC */
        MTP3_RL_GET_OPC(hdr.label, pcTmp);

        pc.data[0] = pcTmp.data[1];
        pc.data[1] = pcTmp.data[0]; 

        memcpy(&ies[ieCount].param_data.data.opc.data[1], pc.data, 2);

        /* SLS */
        ies[ieCount].param_data.data.sls = MTP3_RL_GET_SLS(hdr.label); 

#elif defined(ANSI)

        MTP3_RL_GET_OPC(hdr.label, pcTmp);

        /* flip the point code */
        pc.data[0] = pcTmp.data[2];
        pc.data[1] = pcTmp.data[1];
        pc.data[2] = pcTmp.data[0];
   
        /* OPC */
        memcpy(ies[ieCount].param_data.data.opc.data, pc.data,
               sizeof(MTP3_POINT_CODE));

        MTP3_RL_GET_DPC(hdr.label, pcTmp);

        /* flip the point code */
        pc.data[0] = pcTmp.data[2];
        pc.data[1] = pcTmp.data[1];
        pc.data[2] = pcTmp.data[0];
   
        /* DPC */
        memcpy(ies[ieCount].param_data.data.dpc.data, pc.data,
               sizeof(MTP3_POINT_CODE));

        /* SLS */
        ies[ieCount].param_data.data.sls = MTP3_RL_GET_SLS_ANSI(hdr.label); 

#elif defined(PRC)

        MTP3_RL_GET_OPC(hdr.label, pcTmp);

        /* flip the point code */
        pc.data[0] = pcTmp.data[2];
        pc.data[1] = pcTmp.data[1];
        pc.data[2] = pcTmp.data[0];

        /* OPC */
        memcpy(ies[ieCount].param_data.data.opc.data, pc.data,
               sizeof(MTP3_POINT_CODE));

        MTP3_RL_GET_DPC(hdr.label, pcTmp);

        /* flip the point code */
        pc.data[0] = pcTmp.data[2];
        pc.data[1] = pcTmp.data[1];
        pc.data[2] = pcTmp.data[0];

        /* DPC */
        memcpy(ies[ieCount].param_data.data.dpc.data, pc.data,
               sizeof(MTP3_POINT_CODE));

        /* SLS */
        ies[ieCount].param_data.data.sls = MTP3_RL_GET_SLS_PRC(hdr.label);
#endif 
        /* SIO */
        ies[ieCount].param_data.data.si = hdr.sio & 0x0F;
        ies[ieCount].param_data.data.ni = (hdr.sio & 0xC0) >> 6;

        memcpy(ies[ieCount].param_data.data.data, data, len);

        ieCount++;
  
        ret = M3UA_EncodeMsg(ies, ieCount, &m3uaEvt, &M3UA_DATA_Desc);
        
        if (stats)
        {
            stats->dataOut++;
        }
        break;
    }    
    case MTP3_MSG_PAUSE:
    {
        MTP3_PAUSE_RESUME pause;
        MTP3_POINT_CODE pc;

        if (len > sizeof(MTP3_PAUSE_RESUME))
        {
            return ITS_EINVLEN;
        }

        memcpy(&pause, data, sizeof(MTP3_PAUSE_RESUME));
        
        ies[0].param_id = M3UA_PRM_MSG_HDR;
        ies[0].param_length = sizeof(M3UA_MSG_HDR);
        ies[0].param_data.msgHeader.msgClass = M3UA_CL_SSNM_MSG;
        ies[0].param_data.msgHeader.msgType = M3UA_MSG_DUNA;
        ies[0].param_data.msgHeader.version = M3UA_PROT_VER1;

        ies[1].param_id = M3UA_PRM_AFFECTED_PC;
        ies[1].param_length = sizeof(M3UA_AFFECTED_PC);
        ies[1].param_data.apc.apc.mask = 0x00;

#if defined(CCITT) || defined(TTC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = pause.affected.data[1];
        pc.data[1] = pause.affected.data[0];
        memcpy(&ies[1].param_data.apc.apc.data[1], pc.data,
               sizeof(MTP3_POINT_CODE));
        
#elif defined(ANSI)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = pause.affected.data[2];
        pc.data[1] = pause.affected.data[1];
        pc.data[2] = pause.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data, 
               sizeof(MTP3_POINT_CODE_ANSI));
#elif defined(PRC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = pause.affected.data[2];
        pc.data[1] = pause.affected.data[1];
        pc.data[2] = pause.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data,
               sizeof(MTP3_POINT_CODE_PRC));
#endif

        ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DUNA_Desc);
        if (ret != ITS_SUCCESS)
        {
            M3UA_ERROR(("Error Encoding DUNA msg\n"));
        }
        if (stats)
        {
            stats->duna++;
        }
        break;
        
    }
    case MTP3_MSG_RESUME:
    {
        MTP3_PAUSE_RESUME resume;
        MTP3_POINT_CODE pc;

        if (len > sizeof(MTP3_PAUSE_RESUME))
        {
            return ITS_EINVLEN;
        }

        memcpy(&resume, data, sizeof(MTP3_PAUSE_RESUME));
        
        ies[0].param_id = M3UA_PRM_MSG_HDR;
        ies[0].param_length = sizeof(M3UA_MSG_HDR);
        ies[0].param_data.msgHeader.msgClass = M3UA_CL_SSNM_MSG;
        ies[0].param_data.msgHeader.msgType = M3UA_MSG_DAVA;
        ies[0].param_data.msgHeader.version = M3UA_PROT_VER1;

        ies[1].param_id = M3UA_PRM_AFFECTED_PC;
        ies[1].param_length = sizeof(M3UA_AFFECTED_PC);
        ies[1].param_data.apc.apc.mask = 0x00;

#if defined(CCITT) || defined(TTC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = resume.affected.data[1];
        pc.data[1] = resume.affected.data[0];
        memcpy(&ies[1].param_data.apc.apc.data[1], pc.data,
               sizeof(MTP3_POINT_CODE));
        
#elif defined(ANSI)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = resume.affected.data[2];
        pc.data[1] = resume.affected.data[1];
        pc.data[2] = resume.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data, 
               sizeof(MTP3_POINT_CODE));
#elif defined(PRC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = resume.affected.data[2];
        pc.data[1] = resume.affected.data[1];
        pc.data[2] = resume.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data,
               sizeof(MTP3_POINT_CODE));
#endif

        ret = M3UA_EncodeMsg(ies, 2, &m3uaEvt, &M3UA_DAVA_Desc);
        if (ret != ITS_SUCCESS)
        {
            M3UA_ERROR(("Error Encoding DAVA msg\n"));
        }
        if (stats)
        {
            stats->dava++;
        }
        break;
        
    }
    case MTP3_MSG_STATUS:
    {
        MTP3_STATUS status;
        MTP3_POINT_CODE pc;

        if (len > sizeof(MTP3_STATUS))
        {
            return ITS_EINVLEN;
        }

        memcpy(&status, data, sizeof(MTP3_STATUS));

        ies[0].param_id = M3UA_PRM_MSG_HDR;
        ies[0].param_length = sizeof(M3UA_MSG_HDR);
        ies[0].param_data.msgHeader.msgClass = M3UA_CL_SSNM_MSG;
        ies[0].param_data.msgHeader.version = M3UA_PROT_VER1;

        ies[1].param_id = M3UA_PRM_AFFECTED_PC;
        ies[1].param_length = sizeof(M3UA_AFFECTED_PC);
        ies[1].param_data.apc.apc.mask = 0x00;

#if defined(CCITT) || defined(TTC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = status.affected.data[1];
        pc.data[1] = status.affected.data[0];
        memcpy(&ies[1].param_data.apc.apc.data[1], pc.data,
               sizeof(MTP3_POINT_CODE));
        
#elif defined(ANSI)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = status.affected.data[2];
        pc.data[1] = status.affected.data[1];
        pc.data[2] = status.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data, 
               sizeof(MTP3_POINT_CODE));
#elif defined(PRC)
        ies[1].param_data.apc.apc.data[0] = 0x00;
        pc.data[0] = status.affected.data[2];
        pc.data[1] = status.affected.data[1];
        pc.data[2] = status.affected.data[0];
        memcpy(ies[1].param_data.apc.apc.data, pc.data,
               sizeof(MTP3_POINT_CODE));
#endif
        if (status.cause == MTP3_STATUS_CONGESTED)
        {
            /* Send SCON message.*/
              
            ies[0].param_data.msgHeader.msgType = M3UA_MSG_SCON;

            ies[2].param_id = M3UA_PRM_CONGEST_LEVEL;
            ies[2].param_length = sizeof(M3UA_CONG_LEVEL);
            memset(&ies[2].param_data.congestion.level, 0, sizeof(M3UA_CONG_LEVEL));
            ies[2].param_data.congestion.level = status.congLevel;

            ret = M3UA_EncodeMsg(ies, 3, &m3uaEvt, &M3UA_SCON_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Error Encoding SCOM msg\n"));
            }
             else
            {
                if (stats)
                {
                    stats->sconOut++;
                }
            }

        }
        else
        {
            /* Send DUPU message. */

            if((ies[0].param_data.msgHeader.msgType == M3UA_MSG_DRST) || (ies[0].param_data.msgHeader.msgType = M3UA_MSG_DUPU))
            {
#if defined(TTC)
            return -1;
#endif
            }

            if(ies[0].param_data.msgHeader.msgType == M3UA_MSG_DRST)
            { 
                 ies[0].param_data.msgHeader.msgType = M3UA_MSG_DRST;
            }
            else
            {
                 ies[0].param_data.msgHeader.msgType = M3UA_MSG_DUPU;
            }

            ies[2].param_id     = M3UA_PRM_CAUSE_USER;
            ies[2].param_length = sizeof(M3UA_CAUSE_USER);

            if (status.cause == MTP3_STATUS_UPU_UNKNOWN)
            {
                ies[2].param_data.causeUsr.cause = M3UA_UNKNOWN_CAUSE;
            }
            else if (status.cause == MTP3_STATUS_UPU_UNEQUIP)
            {
                ies[2].param_data.causeUsr.cause = M3UA_UNEQUIP_REMOTE_USR;
            }
            else if (status.cause == MTP3_STATUS_UPU_INACCESS)
            {
                ies[2].param_data.causeUsr.cause = M3UA_INACCESS_REMOTE_USR;
            }
            else
            {
                M3UA_WARNING(("MTP3 Invalid Status Cause.\n"));
            }

            /*
             * FIXME: M3UA is not aware of which user is not available.
             *        Need to fix this in MTP3_STATUS indicator. 
             */
            ies[2].param_data.causeUsr.user = M3UA_USER_SCCP;

            ret = M3UA_EncodeMsg(ies, 3, &m3uaEvt, &M3UA_DUPU_Desc);

            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("M3UA Decode failed for DUPU.\n"));
            }
             else
            {
               if (stats)
               {
                    stats->dupu++;
               }
            }
        }

        break;
    }
    default:

        break;
    }    

    evt->len = m3uaEvt.len;
    evt->data = m3uaEvt.data;
    evt->src = m3uaEvt.src;

    return (ret);
}

M3UADLLAPI int 
M3UA_EncodeRoutingContext(ITS_OCTET *data, ITS_USHORT *len, ITS_UINT *rkList, 
                         int size)
{
    int ret = ITS_SUCCESS, i;
    ITS_USHORT offset = 0;
    
    M3UA_DEBUG(("M3UA_EncodeRoutingContext: \n"));

    if (rkList == NULL)
    {
        *len = 0;
    }
    else
    {
        for (i = 0; i<size; i++)
        {
            rkList[i] = SOCK_HToNL(rkList[i]);
            memcpy(&data[offset], &rkList[i], sizeof(ITS_UINT));
            offset += sizeof(ITS_UINT);      
        }

        *len = offset;

    }
    return ret;
}


M3UADLLAPI int
M3UA_DecodeRoutingContext(ITS_OCTET *data, ITS_USHORT len, ITS_UINT *rkList,
                         int *size)
{
    int ret = ITS_SUCCESS;
    int num = len / sizeof(ITS_UINT);

    M3UA_DEBUG(("M3UA_DecodeRoutingContext: \n"));

    *size = 0;

    if (!(len % sizeof(ITS_UINT)) && (num < M3UA_MAX_RK_NUM))
    {
        int i;

        for (i = 0; i < num; i++)
        {
            memcpy(&rkList[i], data, sizeof(ITS_UINT));
            rkList[i] = SOCK_NToHL(rkList[i]);
            data += sizeof(ITS_UINT);
            (*size)++;
        }
    }
    else
    {
        return -1; /* TODO pick error code */
    }

    return ret;
}


/*
 * UAL Callback functions
 */

M3UADLLAPI void
UAL_RoutingNotification(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    //TRANSPORT_Control *tc      = (TRANSPORT_Control *)object;
    UAL_CB_Context    *ctxt = (UAL_CB_Context *)callData;
    int i, ret = ITS_SUCCESS;
    ITS_OCTET mType = SCCP_MSG_UDT;
    ITS_SCCP_IE ies[10], respIes[10];
    int ieCount = 0;
    SCCP_DATA* data = NULL;
    ITS_OCTET dlen = 0, type, sccpMsg[500];
    ITS_USHORT sccpLen = 0;
    SCCP_ADDR *clp = NULL, *cdp = NULL;
    MTP3_HEADER hdr, resp;
    ITS_EVENT mtp3Evt, sccpEvt;
    ITS_UINT tmp = 0;

    M3UA_DEBUG(("UAL_RoutingNotification: \n"));

    switch (UAL_CB_CTXT_TYPE(ctxt))
    {
        case UAL_CB_RT_FAIL_CTXT:
        {
            // Now decode the message
            mtp3Evt.len = UAL_CB_CTXT_MSU_LEN(ctxt);
            mtp3Evt.data = UAL_CB_CTXT_MSU_DATA(ctxt);

            ret = MTP3_Decode(&mtp3Evt, &type, &hdr, sccpMsg, &sccpLen);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Failed to decode MTP3 message.\n"));

                return;
            }

            ret = SCCP_DecodeMTP3(sccpMsg, sccpLen, &mType, ies,
                                    &ieCount, &SCCP_UDT_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR(("Failed to DECODE SCCP Message \n"));

                break;
            }

            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_DATA)
                {
                    data = &ies[i].param_data.userData;
                    dlen = ies[i].param_length;
                }
                else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
                {
                    clp = &ies[i].param_data.callingPartyAddr;
                }
                else if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
                {
                    cdp = &ies[i].param_data.calledPartyAddr;
                }
            }

            /* now build the Routing Label */
            resp.sio = hdr.sio;
            tmp = MTP3_RL_GET_DPC_VALUE(hdr.label);

            MTP3_RL_SET_OPC_VALUE(resp.label, tmp);
            tmp = MTP3_RL_GET_OPC_VALUE(hdr.label);

            MTP3_RL_SET_DPC_VALUE(resp.label, tmp);
            MTP3_RL_SET_SLS(resp.label, MTP3_RL_GET_SLS(hdr.label));

            /* return cause */
            respIes[0].param_id = SCCP_PRM_RETURN_CAUSE;
            respIes[0].param_length = sizeof(SCCP_RET_CAUSE);
            respIes[0].param_data.returnCause.cause = 0x01;

            /* calledParty */
            respIes[1].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
            respIes[1].param_length = sizeof(SCCP_ADDR);
            memcpy(&respIes[1].param_data.calledPartyAddr, clp, sizeof(SCCP_ADDR));

            /* callingParty */
            respIes[2].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
            respIes[2].param_length = sizeof(SCCP_ADDR);
            memcpy(&respIes[2].param_data.callingPartyAddr, cdp, sizeof(SCCP_ADDR));

            /* copy in data */
            respIes[3].param_id = SCCP_PRM_DATA;
            respIes[3].param_length = dlen;
            memcpy(respIes[3].param_data.userData.data, data->data, dlen);

            ret = SCCP_EncodeMTP3(sccpMsg, &sccpLen, SCCP_MSG_UDTS, respIes, 4,
                              &SCCP_UDTS_Desc);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR((" Failed to ENCODE SCCP Message \n"));

                break;
            } 

            ret = MTP3_Encode(&sccpEvt, 0x21, &resp, sccpMsg, sccpLen);

            sccpEvt.src = ITS_MTP3_SRC;

            ret = TRANSPORT_PutEvent(ITS_SCCP_SRC, &sccpEvt);
            if (ret != ITS_SUCCESS)
            {
                M3UA_ERROR((" Failed to Send UDTS Message \n"));
            }
        }

        case UAL_CB_INVALID_CTXT:
        case UAL_CB_ASP_CTXT:
        case UAL_CB_AS_CTXT:
            break;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Registering puase/resume/status callbacks.
 *      and addition of debug console feature.
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
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name        Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * gdevanand   04-06-2005  BugId:1557     Addition of debug console feature.
 * Mani        05-05-2005  BugId:1773
 *
 *  See Also:
 ****************************************************************************/
static void
UALTRAN_Register(ITS_POINTER object, ITS_POINTER userData,
                 ITS_POINTER callData)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)object;
    ITS_USHORT        tid = TRANSPORT_INSTANCE(tc);
    ITS_Class dbClass;

    if (!started)
    {
    	started = ITS_TRUE;

    /* Since M3UA has no transport of its own, this is being taken as */
    /* the starting point. This callback will always be hit, so       */
    /* tracing component to M3UA is being added here.                 */

    	if ((M3UA_TraceData = TRACE_Constructor("M3UA",
                                             M3UA_TraceMap, 4)) == NULL)
        {
            /* M3UA failed to Intialize -  No Memory. */
            started = ITS_FALSE;
            return;
        }

        if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
        {
            DBC_AddDoCommand(M3UA_Console);
        }

        AddCommitCallback("M3UA",M3UA_Commit);
    }


    InitTraceSettings(tc);

    /*
     * We care only virtual transports for SCTP.
     */                 
    if (tid >= SCTPTRAN_FIRST_SRC && tid <= SCTPTRAN_LAST_SRC)
    {        
        CALLBACK_AddCallback(TRANSPORT_SS7_INFO(tc).resumeCallbacks,
                             ResumeCallback,
                             NULL);
        CALLBACK_AddCallback(TRANSPORT_SS7_INFO(tc).pauseCallbacks,
                             PauseCallback,
                             NULL); 
        CALLBACK_AddCallback(TRANSPORT_SS7_INFO(tc).statusCallbacks,
                             StatusCallback,
                             NULL);
    }                    

}                        
                         
static void              
UALTRAN_Deregister(ITS_POINTER object, ITS_POINTER userData,
                   ITS_POINTER callData)
{                           
    TRANSPORT_Control *tc = (TRANSPORT_Control *)object;
    ITS_USHORT        tid = TRANSPORT_INSTANCE(tc);
    started = ITS_FALSE;
                            
    M3UA_DEBUG(("UALTRAN_Deregister: \n"));
    /*      
     * We care only virtual transports.
     */                    
    if (tid >= SCTPTRAN_FIRST_SRC && tid <= SCTPTRAN_LAST_SRC)
    {           
        CALLBACK_RemCallback(TRANSPORT_SS7_INFO(tc).resumeCallbacks,
                             ResumeCallback,
                             NULL);
        CALLBACK_RemCallback(TRANSPORT_SS7_INFO(tc).pauseCallbacks,
                             PauseCallback,
                             NULL); 
        CALLBACK_RemCallback(TRANSPORT_SS7_INFO(tc).statusCallbacks,
                             StatusCallback,
                             NULL);
    }                       
}                           
                            
M3UADLLAPI
void M3UA_RegisterTransportCallbacks()
{                           
    CALLBACK_AddCallback(TRANSPORT_registrations, UALTRAN_Register, NULL);
    CALLBACK_AddCallback(TRANSPORT_deregistrations, UALTRAN_Deregister, NULL);
    return;         
}

M3UADLLAPI
void  M3UA_DeregisterTransportCallbacks()
{
    CALLBACK_RemCallback(TRANSPORT_registrations, UALTRAN_Register, NULL);
    CALLBACK_RemCallback(TRANSPORT_deregistrations, UALTRAN_Deregister, NULL);

    return;
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
 *
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 924/770/818   Bug Fix propagation.
 *                              826/861/867   changes for PAUSE/RESUME
 *                                            propagation at ASP.
 *
 ****************************************************************************/
static void
PauseCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)object;
    UALMgntData       *ualData = (UALMgntData *)callData;
    ITS_UINT          type = UAL_TRANS_IND;
    ITS_UINT          dpc  = 0x00;
    MTP3_PAUSE_RESUME pause;

    memset(&pause, 0, sizeof(MTP3_PAUSE_RESUME));

    if (ualData)
    {
        type = ualData->type;
        dpc  = ualData->cdata.mtp3_info.pc;
    }

    if (type == UAL_TRANS_IND)
    {
        return;
    }

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        M3UA_WARNING(("PauseCallback: link lock failed\n"));

        return;
    }


    if ((TRANSPORT_MASK(tc) & ITS_SS7_MASK) && TRANSPORT_RES(tc))
    {
        SS7_LinkPtr link;

        for (link = TRANSPORT_SS7_INFO(tc).linkInfo;
             link != NULL; link = link->next)
        {
            DSMQUEUE_Entry *tmp;
            ITS_UINT count;
            ITS_BOOLEAN allDown = ITS_TRUE;

            for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes);
                 tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                 count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
            {
                ROUTE_Info *rinfo;
                ROUTE_MatchInfo minfo;
                SS7_Destination *dest;
                int whichEntry, firstMatch, lastMatch, whichLinkCode, i;

                /* select one of concerned destinations */
                memcpy(&rinfo, tmp->data, sizeof(rinfo));

                /*
                 * We are interested in remote routes and affected
                 * dpc from DUNA in routing table.
                 */
                if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE ||
                   dpc != rinfo->basic.dpc)
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
                    M3UA_WARNING(("Configured route not found\n"));

                    continue;
                }

                for (i = firstMatch; i <= lastMatch; i++)
                {
                    /* ASSUMPTION: The destination in DUNA can't be reachable
                     * from here.
                     */
                    if (dest->entries[i]->isAllowed)
                    {
                        dest->entries[i]->isAllowed = ITS_FALSE;
                        ROUTE_CommitRoute(dest->entries[i]);
                    }
                    else
                    {
                        allDown = ITS_FALSE;
                    }
                }

                ualData->type = UAL_MTP3_RESULT;

                /* determine if this was the last up route */
                if (allDown)
                {
                    M3UA_DEBUG(("MTP3_Pause_ANSI: setting state PC: %08x\n",
                                     rinfo->basic.dpc));

                    ualData->cdata.info.result = ITS_SUCCESS;
                    ualData->cdata.info.pc     = link->linkSet->lpc;
                    ualData->cdata.info.sio    = link->linkSet->ni;

                    M3UA_Pause((MTP3_PAUSE_RESUME *)userData, ualData,
                                (SCTPTRAN_Manager *)tc);

                    allDown = ITS_FALSE;
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
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 924/770/818   Bug Fix propagation.
 *                              826/861/867   changes for PAUSE/RESUME
 *                                            propagation at ASP.
 *
 ****************************************************************************/
static void
ResumeCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
   TRANSPORT_Control *tc = (TRANSPORT_Control *)object;
   UALMgntData       *ualData = (UALMgntData *)callData;
   UAL_MTP3_TYPE     type = UAL_TRANS_IND;
   ITS_UINT          dpc  = 0x00;
   MTP3_PAUSE_RESUME resume;

M3UA_DEBUG (("ResumeCallback called:"));

   memset(&resume, 0, sizeof(MTP3_PAUSE_RESUME));

   if (ualData)
   {
       type = ualData->type;
       dpc = ualData->cdata.mtp3_info.pc;
   }

   if (type == UAL_TRANS_IND)
   {
       return;
   }

   if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
   {
       M3UA_WARNING(("PauseCallback: link lock failed\n"));

       return;
   }

   if (TRANSPORT_MASK(tc) & ITS_SS7_MASK && TRANSPORT_RES(tc))
   {
        SS7_LinkPtr link;
        for (link = TRANSPORT_SS7_INFO(tc).linkInfo;
             link != NULL; link = link->next)
        {
            DSMQUEUE_Entry *tmp;
            ITS_UINT count;
            ITS_BOOLEAN flag;
            ITS_BOOLEAN firstUp = ITS_TRUE;

            LINK_GetLinkState(link, &flag);

            if (!flag)
            {
                LINK_SetLinkState(link, ITS_TRUE);
            }

            for (count = 0, tmp = DSMQUEUE_HEAD(link->linkSet->routes);
                 tmp != NULL && count < DSMQUEUE_COUNT(link->linkSet->routes);
                 count++, tmp = DSMQUEUE_NEXT(link->linkSet->routes, tmp) )
            {
                ROUTE_Info      *rinfo;
                ROUTE_MatchInfo minfo;
                SS7_Destination *dest;
                int whichEntry, firstMatch, lastMatch, whichLinkCode, i;

                /* select one of concerned destinations */
                memcpy(&rinfo, tmp->data, sizeof(rinfo));

                if (rinfo == NULL || rinfo->basic.type != REMOTE_ROUTE ||
                    dpc != rinfo->basic.dpc)
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
                                                &whichLinkCode, ITS_TRUE)) == NULL)
                {
                    M3UA_WARNING(("Configured route not found\n"));

                    continue;
                }

                for (i = firstMatch; i <= lastMatch; i++)
                {
                    /* Mark all the routes as unprohibited
                     * for this destination.
                     */
                    if (!dest->entries[i]->isAllowed)
                    {
                        dest->entries[i]->isAllowed = ITS_TRUE;
                        ROUTE_CommitRoute(dest->entries[i]);
                    }
                    else
                    {
                        firstUp = ITS_FALSE;
                    }
                }

                ualData->type = UAL_MTP3_RESULT;

                /* determine if this is a newly up route */
                if (firstUp)
                {
                    ualData->cdata.info.result = ITS_SUCCESS;
                    ualData->cdata.info.pc     = link->linkSet->lpc;
                    ualData->cdata.info.sio    = link->linkSet->ni;

                    M3UA_Resume((MTP3_PAUSE_RESUME *)userData, ualData,
                                (SCTPTRAN_Manager *)tc);

                    firstUp = ITS_FALSE;
                }
            }
        }
    }

    ROUTE_UnlockWrite(routeRWLock);

    return;
}

static void
StatusCallback(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)tc;

    CALLBACK_CallCallbackList(MTP3_ManagementCallbacks,
                              (ITS_POINTER)tc,
                              callData);
 
    return;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the M3UA transport subsytem.
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
 *      If the M3UA subsystem is initialized correctly, ITS_SUCCESS is
 *          returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    ITS_Class ualClass;

    M3UA_DEBUG(("Initialize\n"));

    M3UA_RegisterTransportCallbacks();

    if ( (ualClass = ITS_FindFeature(UAL_CLASS_NAME)) == NULL)
    {
        if (ITS_AddFeature(itsUAL_Class) != ITS_SUCCESS)
        {
            M3UA_ERROR(("ClassInitialize: failed to add UAL featute class.\n"));
        }
    }
    else
    {
        M3UA_WARNING(("ClassInitialize: UAL Class feature exists.\n"));
    }

    if (ITS_InitializeClass(itsUAL_Class) != ITS_SUCCESS)
    {
        M3UA_ERROR(("ClassInitialize: UAL class initialization failed.\n"));
    }

    CALLBACK_AddCallback(__UAL_MgntCallBack,
                         UAL_RoutingNotification,
                         NULL);

    return SCTPTRAN_RegisterCodec(M3UA_CLASS_NAME, SCTP_PAYLOAD_M3UA,
                                  MTP3_To_M3UA_Codec, M3UA_To_MTP3_Codec);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the M3UA transport subsystem.
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
 *      ROUTE_Initialize()
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    M3UA_DEBUG(("Terminate:\n"));

    M3UA_DeregisterTransportCallbacks();

    SCTPTRAN_DeregisterCodec(M3UA_CLASS_NAME);
}

M3UADLLAPI ITS_ClassRec itsM3UA_ClassRec =
{
    /* core part */
    {
        NULL,                           /* no superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        M3UA_CLASS_NAME,                /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

M3UADLLAPI ITS_Class itsM3UA_Class = &itsM3UA_ClassRec;
 
/* M3UA Alarms */

ITS_UINT M3UA_AlarmLevel = ALARM_LVL_OFF;

ALARM_FORMAT_SUBSYS(M3UA, 4027,
                    "Received DUNA",
                    ALARM_LVL_MINOR,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4028,
                    "Received DAVA",
                    ALARM_LVL_INFO,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_FALSE);

ALARM_FORMAT_SUBSYS(M3UA, 4029,
                    "Received SCON",
                    ALARM_LVL_MINOR,         "M3UA_To_MTP3_Codec",
                    "M3UA", ITS_FALSE);

ALARM_Format *M3UA_Alarms[] =
{
    &ALARM_M3UA4027,
    &ALARM_M3UA4028,
    &ALARM_M3UA4029
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method issues a UAL alarm.
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
 *                  
 *  See Also:       
 ****************************************************************************/
void
M3UA_Alarm(int which, const char *file, const int line,
           char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= M3UA_ALARM_START &&
                 which <= M3UA_ALARM_END);

    fmt = M3UA_Alarms[which - M3UA_ALARM_START];

    if (fmt->severity > M3UA_AlarmLevel)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialise M3UA trace settings.
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
 *                  
 *  See Also:       
 ****************************************************************************/
static void
InitTraceSettings(TRANSPORT_Control* tc)
{
     /*
     * determine tracing from INI files
     */
    if (TRANSPORT_RES(tc) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(tc);
        char *name = "M3UA";

        /* critical */
        if (RESFILE_GetKeyValueOf(res, name, M3UA_TRACE_CRITICAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, M3UA_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_STDOUT_STRING, ITS_FALSE);

            }
            if (strstr(value, M3UA_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_FILE_STRING, ITS_FALSE);

            }
            if (strstr(value, M3UA_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_CRITICAL_STRING,
                                           M3UA_SYSLOG_STRING, ITS_FALSE);

            }
            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_CRITICAL_STRING, ITS_FALSE);
            }
        }

        /* error */
        if (RESFILE_GetKeyValueOf(res, name, M3UA_TRACE_ERROR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, M3UA_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_ERROR_STRING,
                                           M3UA_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_ERROR_STRING, ITS_FALSE);
            }
        }

        /* warning */
        if (RESFILE_GetKeyValueOf(res, name, M3UA_TRACE_WARNING_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, M3UA_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_WARNING_STRING,
                                           M3UA_SYSLOG_STRING, ITS_FALSE);

            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_WARNING_STRING, ITS_FALSE);
            }
        }

        /* debug */
        if (RESFILE_GetKeyValueOf(res, name, M3UA_TRACE_DEBUG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, M3UA_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, M3UA_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                           M3UA_DEBUG_STRING,
                                           M3UA_SYSLOG_STRING, ITS_FALSE);

            }
            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                          M3UA_DEBUG_STRING, ITS_FALSE);
            }
        }
    }
}

