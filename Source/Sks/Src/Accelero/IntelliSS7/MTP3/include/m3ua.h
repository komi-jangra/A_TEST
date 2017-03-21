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
 * ID: $Id: m3ua.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:46  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:12  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2  2005/04/06 05:55:20  adutta
 * LOG: Fix for BugID#1557
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:17  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:17  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.4.2.2.2.4.4  2005/02/21 12:00:53  dsatish
 * LOG: changes propagated for DAUD support from r7.1.12.3 (KINETO BRANCH)
 * LOG:
 * LOG: Revision 7.1.4.2.2.2.4.3  2005/01/11 11:51:24  craghavendra
 * LOG: Syslog Enhancements.
 * LOG:
 * LOG: Revision 7.1.4.2.2.2.4.2  2004/12/16 02:02:56  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.4.2.2.2.4.1  2004/12/15 12:11:56  asingh
 * LOG: separate traces for M3UA
 * LOG:
 * LOG: Revision 7.1.4.2.2.2  2004/10/06 13:27:34  mmanikandan
 * LOG: Support for windows build.
 * LOG:
 * LOG: Revision 7.1.4.2.2.1  2004/05/03 13:17:45  ssingh
 * LOG: m3ua alarms max/min limits.
 * LOG:
 * LOG: Revision 7.1.4.2  2003/09/21 13:24:55  lbana
 * LOG: add DRST indicator
 * LOG:
 * LOG: Revision 7.1.4.1  2003/09/19 05:24:36  lbana
 * LOG: send error message in case if we get invalid version or missing
 * LOG: mandatory param.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/07/03 19:54:53  mmiers
 * LOG: China fixes
 * LOG:
 * LOG: Revision 6.2  2002/05/20 16:02:30  lbana
 * LOG: m3ua ver 10 codec
 * LOG:
 * LOG: Revision 1.1.2.4  2002/03/12 21:50:43  omayor
 * LOG: Minor typo found.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/03/12 21:03:38  lbana
 * LOG: changed Codec signature
 * LOG:
 * LOG: Revision 1.1.2.2  2002/02/12 22:07:57  labuser
 * LOG: Make sure you commit the bug fix.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/30 16:47:47  labuser
 * LOG: M3UA V10 Codec.
 * LOG:
 *                 
 ****************************************************************************/


#ifndef M3UA_H
#define M3UA_H

#include <its.h>
#include <its_object.h>
#include <its_sctp_trans.h>
#include <its_alarm.h>
#include <dbc_serv.h>

#include <its_ual.h>

#include <its_trace.h>


#if defined(ANSI)
#include <ansi/mtp3.h>
#elif defined(CCITT)
#include <itu/mtp3.h>
#elif defined(PRC)
#include <china/mtp3.h>
#elif defined(TTC)
#include <japan/mtp3.h>
#else
#error "Protocol family not defined."
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

#if defined (WIN32)

#if defined (M3UA_IMPLEMENTATION)
#define M3UADLLAPI __declspec (dllexport)
#else
#define M3UADLLAPI __declspec (dllimport)
#endif

#else
#define M3UADLLAPI
#endif

/* M3UA alarms */
#define M3UA_ALARM_START 4027
#define M3UA_ALARM_END   4029

/* M3UA protocol version */
#define M3UA_PROT_VER1     0x01

/* message class */
#define M3UA_CL_TRANSFER_MSG          0x01
#define M3UA_CL_SSNM_MSG              0x02


/* transfer messages */
#define M3UA_MSG_PAYLOAD_DATA      0x01

/* Signaling network management messages (SSNM) */
#define M3UA_MSG_DUNA              0x01
#define M3UA_MSG_DAVA              0x02
#define M3UA_MSG_DAUD              0x03
#define M3UA_MSG_SCON              0x04
#define M3UA_MSG_DUPU              0x05
#define M3UA_MSG_DRST              0x06


/* M3UA common message Header */
typedef struct
{
    ITS_OCTET   version;
    ITS_OCTET   reserved;
    ITS_OCTET   msgClass;
    ITS_OCTET   msgType;
    ITS_UINT    msgLen;  /* msg data + sizeof(M3UA_MSG_HDR) */   
}
M3UA_MSG_HDR;


/* parameters */
#define M3UA_PRM_MSG_HDR                0x0000
#define M3UA_PRM_INFO_STR               0x0004
#define M3UA_PRM_ROUT_CTX               0x0006
#define M3UA_PRM_AFFECTED_PC            0x0012
#define M3UA_PRM_NET_APP                0x0200
#define M3UA_PRM_CAUSE_USER             0x0204
#define M3UA_PRM_CONGEST_LEVEL          0x0205
#define M3UA_PRM_CONCERN_PC             0x0206
#define M3UA_PRM_DATA                   0x0210
#define M3UA_PRM_COR_ID                 0x0211


/* 
 * Network apperance 
 */

#define MAX_NET_APP_SIZE         4

typedef struct
{
    ITS_OCTET    networkApp[MAX_NET_APP_SIZE];
}
M3UA_NET_APP;

/*
 * M3UA Point Code 
 */

typedef struct
{
    ITS_OCTET    mask;
    ITS_OCTET    data[3];
}
M3UA_PC;


/* 
 * Data parameter 
 */
#define M3UA_HDR_SIZE          12
#define M3UA_MAX_DATA_SIZE   (512) /* SCCP_MAX_DATA   254 */

typedef struct
{
    M3UA_PC      opc;
    M3UA_PC      dpc;
    ITS_OCTET    si;
    ITS_OCTET    ni;
    ITS_OCTET    mp;
    ITS_OCTET    sls;
    ITS_OCTET    data[M3UA_MAX_DATA_SIZE]; 
}
M3UA_DATA;


/*
 * Info String 
 */

#define M3UA_MAX_INFO_STR_LEN   254 

typedef struct
{
    ITS_OCTET    infoStr[M3UA_MAX_INFO_STR_LEN];
}
M3UA_INFO_STR;


/* 
 * Affected PC 
 */

typedef struct
{
    M3UA_PC    apc;
}
M3UA_AFFECTED_PC;

/* 
 * Concerned PC 
 */

typedef struct
{
    M3UA_PC    cpc;
}
M3UA_CONCERNED_PC;


/* 
 * Routing Context 
 */

#define M3UA_MAX_ROUT_CTX_LEN   1024 
#define M3UA_MAX_RK_NUM         15


typedef struct
{
    ITS_OCTET    rCtxt[M3UA_MAX_ROUT_CTX_LEN];
}
M3UA_ROUT_CTX;


/*
 * Cause-User
 */

typedef struct
{
    ITS_USHORT   cause;
    ITS_USHORT   user;
}
M3UA_CAUSE_USER;


#define M3UA_UNKNOWN_CAUSE           0x00
#define M3UA_UNEQUIP_REMOTE_USR      0x01
#define M3UA_INACCESS_REMOTE_USR     0x02

#define M3UA_USER_SCCP               0x03
#define M3UA_USER_TUP                0x04
#define M3UA_USER_ISUP               0x05
#define M3UA_BROADB_ISUP             0x09
#define M3UA_SAT_ISUP                0x0A


/*
 * Congestion Level
 */

typedef struct
{
    ITS_UINT    level;
}
M3UA_CONG_LEVEL;

#define M3UA_NO_CONG                    0x00
#define M3UA_CONG_LEVEL_1               0x01
#define M3UA_CONG_LEVEL_2               0x02
#define M3UA_CONG_LEVEL_3               0x03




#define M3UA_ERROR_CODE  UAL_ERROR_CODE

/*------------------------------------------------------------------------------*/



#define M3UA_MAX_IE_SIZE            1024

/*
 * M3UA IES
 */
typedef struct
{
    ITS_USHORT   param_id;      
    ITS_USHORT   param_length;
    union
    {
        M3UA_MSG_HDR         msgHeader;
        M3UA_NET_APP         networkAppearance;
        M3UA_DATA            data;
        M3UA_INFO_STR        infoStr;
        M3UA_AFFECTED_PC     apc;
        M3UA_CONCERNED_PC    cpc;
        M3UA_ROUT_CTX        rCtxt;
        M3UA_CAUSE_USER      causeUsr;
        M3UA_CONG_LEVEL      congestion;
        M3UA_ERROR_CODE      errorCode;
    }
    param_data;
}
ITS_M3UA_IE;

#define ITS_MAX_M3UA_IES   32

typedef struct
{
    ITS_USHORT*    mParam;
    int           nmParam;
    ITS_USHORT*    oParam;
    int           noParam;
}
M3UA_MSG_DESC;

/* message descriptors */
extern M3UA_MSG_DESC M3UA_DATA_Desc;
extern M3UA_MSG_DESC M3UA_DUNA_Desc;
extern M3UA_MSG_DESC M3UA_DAVA_Desc;
extern M3UA_MSG_DESC M3UA_SCON_Desc;
extern M3UA_MSG_DESC M3UA_DUPU_Desc;
extern M3UA_MSG_DESC M3UA_DAUD_Desc;
extern M3UA_MSG_DESC M3UA_ERROR_Desc;

#define M3UA_DRST_Desc M3UA_DAVA_Desc


#if defined(CCITT)

#define M3UA_To_MTP3_Codec  M3UA_To_MTP3_Codec_CCITT
#define MTP3_To_M3UA_Codec  MTP3_To_M3UA_Codec_CCITT

#define M3UA_CLASS_NAME     "CCITT-M3UA"

#define itsM3UA_Class       itsM3UA_Class_CCITT

#elif defined(ANSI)

#define M3UA_To_MTP3_Codec  M3UA_To_MTP3_Codec_ANSI
#define MTP3_To_M3UA_Codec  MTP3_To_M3UA_Codec_ANSI

#define M3UA_CLASS_NAME     "ANSI-M3UA"

#define itsM3UA_Class       itsM3UA_Class_ANSI

#elif defined(PRC)

#define M3UA_To_MTP3_Codec  M3UA_To_MTP3_Codec_PRC
#define MTP3_To_M3UA_Codec  MTP3_To_M3UA_Codec_PRC

#define M3UA_CLASS_NAME     "PRC-M3UA"

#define itsM3UA_Class       itsM3UA_Class_PRC

#elif defined(TTC)

#define M3UA_To_MTP3_Codec  M3UA_To_MTP3_Codec_TTC
#define MTP3_To_M3UA_Codec  MTP3_To_M3UA_Codec_TTC

#define M3UA_CLASS_NAME     "TTC-M3UA"

#define itsM3UA_Class       itsM3UA_Class_TTC


#endif

/*
 * Codecs
 */

M3UADLLAPI int 
M3UA_EncodeMsg(ITS_M3UA_IE *ies, int ieCount,ITS_EVENT *event,
               M3UA_MSG_DESC* desc);

M3UADLLAPI int 
M3UA_DecodeMsg(ITS_M3UA_IE *ies, int *ieCount, ITS_EVENT *ev,
               M3UA_MSG_DESC *desc);


M3UADLLAPI int 
M3UA_To_MTP3_Codec(SCTPTRAN_Manager* m, ITS_EVENT *evt, 
                   ITS_BOOLEAN *isMgmt, ITS_OCTET *sls);

M3UADLLAPI int 
MTP3_To_M3UA_Codec(SCTPTRAN_Manager* m, ITS_EVENT *evt, 
                   ITS_BOOLEAN *isMgmt, ITS_OCTET *sls);


/*
 * Helper functions
 */

M3UADLLAPI ITS_M3UA_IE* 
M3UA_FindM3UAIE(ITS_M3UA_IE *ies, int ieCount, ITS_USHORT paramId);

M3UADLLAPI int 
M3UA_EncodeRoutingContext(ITS_OCTET *data, ITS_USHORT *len, ITS_UINT *rkList, 
                         int size);

M3UADLLAPI int
M3UA_DecodeRoutingContext(ITS_OCTET *data, ITS_USHORT len, ITS_UINT *rkList,
                         int *size);


/*
 * feature record
 */
M3UADLLAPI extern ITS_Class   itsM3UA_Class;

/*
 * user knows by which API they implemented with
 */
#define ITS_M3UA     ITS_MTP3


#define M3UA_FILE_STRING                ITS_FILE_STRING
#define M3UA_STDOUT_STRING              ITS_STDOUT_STRING
#define M3UA_SYSLOG_STRING              ITS_SYSLOG_STRING

/*
 * tracing strings
 */
#define M3UA_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING
#define M3UA_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define M3UA_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define M3UA_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING

#define M3UA_CRITICAL_STRING        ITS_CRITICAL_STRING
#define M3UA_ERROR_STRING           ITS_ERROR_STRING
#define M3UA_WARNING_STRING         ITS_WARNING_STRING
#define M3UA_DEBUG_STRING           ITS_DEBUG_STRING

/*
 * the global control flag defined for M3UA
 */
extern TRACE_Data* M3UA_TraceData;

/*
 * trace possibilities:
 */
#define M3UA_TRACE_CRITICAL  0
#define M3UA_TRACE_ERROR     1
#define M3UA_TRACE_WARNING   2
#define M3UA_TRACE_DEBUG     3

/* Macros for M3UA traces */

#define M3UA_CRITICAL(args) \
    TRACE(M3UA_TraceData, M3UA_TRACE_CRITICAL, args)

#define M3UA_ERROR(args) \
    TRACE(M3UA_TraceData, M3UA_TRACE_ERROR, args)

#define M3UA_WARNING(args) \
    TRACE(M3UA_TraceData, M3UA_TRACE_WARNING, args)

#define M3UA_DEBUG(args) \
    TRACE(M3UA_TraceData, M3UA_TRACE_DEBUG, args)


#define M3UA_TRACE_CRITICAL_FILE    ".m3ua-traceCritical"
#define M3UA_TRACE_ERROR_FILE       ".m3ua-traceError"
#define M3UA_TRACE_WARNING_FILE     ".m3ua-traceWarning"
#define M3UA_TRACE_DEBUG_FILE       ".m3ua-traceDebug"

/*
 * levels
 */
M3UADLLAPI extern ITS_UINT M3UA_AlarmLevel;


/*
 * alarm levels
 */
typedef enum
{
    ALARM_OFF,
    ALARM_DEFAULT,
    ALARM_DEBUG,
    ALARM_DETAIL
}
MGMT_AlarmLevel;


typedef struct _m3u_generalcfg_
{
    MGMT_AlarmLevel     alarmLevel;
    ITS_BOOLEAN         traceOn;     /* on(1), off(0) */
    ITS_CHAR            traceType[ITS_PATH_MAX];
    ITS_CHAR            traceOutput[ITS_PATH_MAX];
}
M3UAGeneralCfg;

M3UADLLAPI void
M3UA_Console(DBC_Server *dbc, const char *cmdLine);

#if defined(__cplusplus)
}
#endif

#endif /*M3UA_H*/

