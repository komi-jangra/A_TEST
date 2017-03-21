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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/16 03:26:18  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.42.1  2004/10/25 20:39:57  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/05 19:58:21  mmiers
 * LOG: Add PRC IP transports
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2001/10/18 00:10:25  mmiers
 * LOG: Correct a few bugs.
 * LOG:
 * LOG: Revision 5.3  2001/10/17 00:39:15  mmiers
 * LOG: Allow simultaneous family presence for TALI, IMAL, GDI
 * LOG:
 * LOG: Revision 5.2  2001/10/10 20:10:19  mmiers
 * LOG: Both families
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/07 18:31:16  mmiers
 * LOG: Make this work on NT.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.6  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.2  2000/11/09 23:04:24  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:17  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.9  2000/08/05 00:20:32  mmiers
 * LOG: IMAL: Add per link SLTM data.
 * LOG: SCTP: Update implementation.
 * LOG:
 * LOG: Revision 2.8  2000/07/28 23:54:24  labuser
 * LOG:
 * LOG:
 * LOG: Get the #define right.
 * LOG:
 * LOG: Revision 2.7  2000/07/13 19:29:31  mmiers
 * LOG: Per transport timer.
 * LOG:
 * LOG: Revision 2.6  2000/06/22 23:07:49  rsonak
 * LOG:
 * LOG: Iterative servers cannot run protocols.
 * LOG:
 * LOG: Revision 2.5  2000/06/02 17:18:10  mmiers
 * LOG:
 * LOG:
 * LOG: Socket modifications.
 * LOG:
 * LOG: Revision 2.4  2000/05/22 18:27:35  mmiers
 * LOG:
 * LOG:
 * LOG: Add framework for SCTP transports.
 * LOG:
 * LOG: Revision 2.3  2000/05/11 20:44:30  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the IMAL heartbeat.
 * LOG:
 * LOG: Revision 2.2  2000/05/11 02:06:12  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 2.1  2000/05/10 23:39:48  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based protocols with heartbeats.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_IMAL_TRANS_H)
#define ITS_IMAL_TRANS_H

#include <its.h>
#include <its_ip_trans.h>
#include <its_kasock_trans.h>

#ident "$Id: its_imal_trans.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#define IMAL_KEEPALIVE_TIMEOUT_STRING   "imalKeepAliveTimer"
#define IMAL_TRACE_KEEPALIVES_STRING    "imalTraceKeepAlives"
#define IMAL_TRACE_PAYLOAD_STRING       "imalTracePayload"
#define IMAL_LOCAL_PC_STRING            "imalLocalPC"
#define IMAL_ADJ_PC_STRING              "imalAdjacentPC"

#define IMALTRAN_CLIENT_CLASS_NAME      "IMALTRAN_CLIENT"
#define IMALTRAN_SERVER_CLASS_NAME      "IMALTRAN_SERVER"
#define IMALTRAN_ITERATIVE_CLASS_NAME   "IMALTRAN_ITERATIVE"
#define IMALTRAN_DYNAMIC_CLASS_NAME     "IMALTRAN_DYNAMIC"
#define IMALTRAN_LOCAL_EP_CLASS_NAME    "IMALTRAN_LOCAL_EP"
#define IMALTRAN_REMOTE_EP_CLASS_NAME   "IMALTRAN_REMOTE_EP"

#define IMAL_KEEP_ALIVE_TIMEOUT_DEFAULT     5


#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * pattern buffer size.
 */
#define IMAL_PATTERN_SIZE       16

/*
 * how many SLTA mismatches to accept before declaring the
 * transport bad.  Reset if good SLTA seen.
 */
#define IMAL_MISMATCH_LIMIT     3

/*
 * transport control
 */
typedef struct
{
    ITS_MUTEX               patternLock;
    ITS_OCTET               sendPattern[IMAL_PATTERN_SIZE];
    ITS_OCTET               recvPattern[IMAL_PATTERN_SIZE];
    ITS_USHORT              sendPatternLen;
    ITS_USHORT              recvPatternLen;
    ITS_UINT                mismatchCount;
    ITS_TIME                keepAliveStartTime;
    ITS_TIME                keepAliveTransmitTime;
    ITS_BOOLEAN             keepAliveReqPending;
    ITS_UINT                keepAliveTimeout;
    ITS_UINT                adjacentPC;
    ITS_UINT                localPC;
}
IMALTRAN_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    SOCKTRAN_ObjectPart     socket;
    KASOCKTRAN_ObjectPart   kasocket;
    IMALTRAN_ObjectPart     imal;
}
IMALTRAN_Manager;

#define IMALTRAN_KA_PATTERN_LOCK(x) \
    (((IMALTRAN_Manager *)(x))->imal.patternLock)

#define IMALTRAN_KA_SEND_PATTERN(x) \
    (((IMALTRAN_Manager *)(x))->imal.sendPattern)

#define IMALTRAN_KA_RECV_PATTERN(x) \
    (((IMALTRAN_Manager *)(x))->imal.recvPattern)

#define IMALTRAN_KA_SEND_PATTERN_LEN(x) \
    (((IMALTRAN_Manager *)(x))->imal.sendPatternLen)

#define IMALTRAN_KA_RECV_PATTERN_LEN(x) \
    (((IMALTRAN_Manager *)(x))->imal.recvPatternLen)

#define IMALTRAN_KA_MISMATCH_COUNT(x) \
    (((IMALTRAN_Manager *)(x))->imal.mismatchCount)

#define IMALTRAN_KA_START_TIME(x) \
    (((IMALTRAN_Manager *)(x))->imal.keepAliveStartTime)

#define IMALTRAN_KA_TRANSMIT_TIME(x) \
    (((IMALTRAN_Manager *)(x))->imal.keepAliveTransmitTime)

#define IMALTRAN_KA_TIMEOUT(x) \
    (((IMALTRAN_Manager *)(x))->imal.keepAliveTimeout)

#define IMALTRAN_KA_REQ_PENDING(x) \
    (((IMALTRAN_Manager *)(x))->imal.keepAliveReqPending)

#define IMALTRAN_KA_ADJACENT_PC(x) \
    (((IMALTRAN_Manager *)(x))->imal.adjacentPC)

#define IMALTRAN_KA_LOCAL_PC(x) \
    (((IMALTRAN_Manager *)(x))->imal.localPC)

/*
 * transport subclass
 */
typedef struct
{
    ITS_CoreClassPart       coreClass;
    TRANSPORT_ClassPart     transportClass;
    SOCKTRAN_ClassPart      socktranClass;
    KASOCKTRAN_ClassPart    kasockClass;
}
IMALTRAN_ClassRec, *IMALTRAN_Class;

/*
 * the class records for the transport.  This is not
 * the only transport possible with IMAL, just the
 * most common.
 * The transport doesn't care what protocol family it
 * carries, but if you want to use both families simultaneously
 * the user does.
 */
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_ClientClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_ClientClass_ANSI;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_ServerClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_ServerClass_ANSI;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_DynamicServerClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_DynamicServerClass_ANSI;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_LocalEndPointClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_LocalEndPointClass_ANSI;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_RemoteEndPointClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_RemoteEndPointClass_ANSI;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_ClientClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_ClientClass_CCITT;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_ServerClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_ServerClass_CCITT;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_DynamicServerClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_DynamicServerClass_CCITT;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_LocalEndPointClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_LocalEndPointClass_CCITT;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_RemoteEndPointClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_RemoteEndPointClass_CCITT;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_ClientClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_ClientClass_PRC;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_ServerClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_ServerClass_PRC;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_DynamicServerClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_DynamicServerClass_PRC;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_LocalEndPointClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_LocalEndPointClass_PRC;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_RemoteEndPointClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_RemoteEndPointClass_PRC;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_ClientClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_ClientClass_TTC;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_ServerClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_ServerClass_TTC;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_DynamicServerClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_DynamicServerClass_TTC;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_LocalEndPointClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_LocalEndPointClass_TTC;
ITSDLLAPI extern IMALTRAN_ClassRec    itsIMALTRAN_RemoteEndPointClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsIMALTRAN_RemoteEndPointClass_TTC;

#if !defined(IMAL_IMPLEMENTATION)
#if defined(WIN32)
#define IMALDLLAPI   __declspec(dllimport)
#else
#define IMALDLLAPI
#endif
#else
#if defined(WIN32)
#define IMALDLLAPI   __declspec(dllexport)
#else
#define IMALDLLAPI
#endif /* WIN32 */
#endif

/*
 * shorthand.
 */
#if defined(CCITT)

#define itsIMALTRAN_ClientClassRec          itsIMALTRAN_ClientClassRec_CCITT
#define itsIMALTRAN_ClientClass             itsIMALTRAN_ClientClass_CCITT
#define itsIMALTRAN_ServerClassRec          itsIMALTRAN_ServerClassRec_CCITT
#define itsIMALTRAN_ServerClass             itsIMALTRAN_ServerClass_CCITT
#define itsIMALTRAN_DynamicServerClassRec   itsIMALTRAN_DynamicServerClassRec_CCITT
#define itsIMALTRAN_DynamicServerClass      itsIMALTRAN_DynamicServerClass_CCITT
#define itsIMALTRAN_LocalEndPointClassRec   itsIMALTRAN_LocalEndPointClassRec_CCITT
#define itsIMALTRAN_LocalEndPointClass      itsIMALTRAN_LocalEndPointClass_CCITT
#define itsIMALTRAN_RemoteEndPointClassRec  itsIMALTRAN_RemoteEndPointClassRec_CCITT
#define itsIMALTRAN_RemoteEndPointClass     itsIMALTRAN_RemoteEndPointClass_CCITT

#define itsIMAL_ClassRec        itsIMAL_ClassRec_CCITT
#define itsIMAL_Class           itsIMAL_Class_CCITT

#define IMALTRAN_SetSendPattern IMALTRAN_SetSendPattern_CCITT
#define IMALTRAN_GetSendPattern IMALTRAN_GetSendPattern_CCITT
#define IMALTRAN_GetRecvPattern IMALTRAN_GetRecvPattern_CCITT

#elif defined(ANSI)

#define itsIMALTRAN_ClientClassRec          itsIMALTRAN_ClientClassRec_ANSI
#define itsIMALTRAN_ClientClass             itsIMALTRAN_ClientClass_ANSI
#define itsIMALTRAN_ServerClassRec          itsIMALTRAN_ServerClassRec_ANSI
#define itsIMALTRAN_ServerClass             itsIMALTRAN_ServerClass_ANSI
#define itsIMALTRAN_DynamicServerClassRec   itsIMALTRAN_DynamicServerClassRec_ANSI
#define itsIMALTRAN_DynamicServerClass      itsIMALTRAN_DynamicServerClass_ANSI
#define itsIMALTRAN_LocalEndPointClassRec   itsIMALTRAN_LocalEndPointClassRec_ANSI
#define itsIMALTRAN_LocalEndPointClass      itsIMALTRAN_LocalEndPointClass_ANSI
#define itsIMALTRAN_RemoteEndPointClassRec  itsIMALTRAN_RemoteEndPointClassRec_ANSI
#define itsIMALTRAN_RemoteEndPointClass     itsIMALTRAN_RemoteEndPointClass_ANSI

#define itsIMAL_ClassRec        itsIMAL_ClassRec_ANSI
#define itsIMAL_Class           itsIMAL_Class_ANSI

#define IMALTRAN_SetSendPattern IMALTRAN_SetSendPattern_ANSI
#define IMALTRAN_GetSendPattern IMALTRAN_GetSendPattern_ANSI
#define IMALTRAN_GetRecvPattern IMALTRAN_GetRecvPattern_ANSI

#elif defined(PRC)

#define itsIMALTRAN_ClientClassRec          itsIMALTRAN_ClientClassRec_PRC
#define itsIMALTRAN_ClientClass             itsIMALTRAN_ClientClass_PRC
#define itsIMALTRAN_ServerClassRec          itsIMALTRAN_ServerClassRec_PRC
#define itsIMALTRAN_ServerClass             itsIMALTRAN_ServerClass_PRC
#define itsIMALTRAN_DynamicServerClassRec   itsIMALTRAN_DynamicServerClassRec_PRC
#define itsIMALTRAN_DynamicServerClass      itsIMALTRAN_DynamicServerClass_PRC
#define itsIMALTRAN_LocalEndPointClassRec   itsIMALTRAN_LocalEndPointClassRec_PRC
#define itsIMALTRAN_LocalEndPointClass      itsIMALTRAN_LocalEndPointClass_PRC
#define itsIMALTRAN_RemoteEndPointClassRec  itsIMALTRAN_RemoteEndPointClassRec_PRC
#define itsIMALTRAN_RemoteEndPointClass     itsIMALTRAN_RemoteEndPointClass_PRC

#define itsIMAL_ClassRec        itsIMAL_ClassRec_PRC
#define itsIMAL_Class           itsIMAL_Class_PRC

#define IMALTRAN_SetSendPattern IMALTRAN_SetSendPattern_PRC
#define IMALTRAN_GetSendPattern IMALTRAN_GetSendPattern_PRC
#define IMALTRAN_GetRecvPattern IMALTRAN_GetRecvPattern_PRC

#elif defined(TTC)

#define itsIMALTRAN_ClientClassRec          itsIMALTRAN_ClientClassRec_TTC
#define itsIMALTRAN_ClientClass             itsIMALTRAN_ClientClass_TTC
#define itsIMALTRAN_ServerClassRec          itsIMALTRAN_ServerClassRec_TTC
#define itsIMALTRAN_ServerClass             itsIMALTRAN_ServerClass_TTC
#define itsIMALTRAN_DynamicServerClassRec   itsIMALTRAN_DynamicServerClassRec_TTC
#define itsIMALTRAN_DynamicServerClass      itsIMALTRAN_DynamicServerClass_TTC
#define itsIMALTRAN_LocalEndPointClassRec   itsIMALTRAN_LocalEndPointClassRec_TTC
#define itsIMALTRAN_LocalEndPointClass      itsIMALTRAN_LocalEndPointClass_TTC
#define itsIMALTRAN_RemoteEndPointClassRec  itsIMALTRAN_RemoteEndPointClassRec_TTC
#define itsIMALTRAN_RemoteEndPointClass     itsIMALTRAN_RemoteEndPointClass_TTC

#define itsIMAL_ClassRec        itsIMAL_ClassRec_TTC
#define itsIMAL_Class           itsIMAL_Class_TTC

#define IMALTRAN_SetSendPattern IMALTRAN_SetSendPattern_TTC
#define IMALTRAN_GetSendPattern IMALTRAN_GetSendPattern_TTC
#define IMALTRAN_GetRecvPattern IMALTRAN_GetRecvPattern_TTC

#endif

/*
 * feature record.
 * NOTE: This record is protocol family specific.  Use
 * the long name in XML configurations/code, or make sure
 * you have the right #define.
 */
IMALDLLAPI extern ITS_ClassRec         itsIMAL_ClassRec_CCITT;
IMALDLLAPI extern ITS_Class            itsIMAL_Class_CCITT;
IMALDLLAPI extern ITS_ClassRec         itsIMAL_ClassRec_ANSI;
IMALDLLAPI extern ITS_Class            itsIMAL_Class_ANSI;
IMALDLLAPI extern ITS_ClassRec         itsIMAL_ClassRec_PRC;
IMALDLLAPI extern ITS_Class            itsIMAL_Class_PRC;
IMALDLLAPI extern ITS_ClassRec         itsIMAL_ClassRec_TTC;
IMALDLLAPI extern ITS_Class            itsIMAL_Class_TTC;

/*
 * SLTM pattern
 */
IMALDLLAPI int IMALTRAN_SetSendPattern(IMALTRAN_Manager *mgr,
                                       ITS_OCTET *pattern, ITS_USHORT len);
IMALDLLAPI int IMALTRAN_GetSendPattern(IMALTRAN_Manager *mgr,
                                       ITS_OCTET *pattern, ITS_USHORT *len);
IMALDLLAPI int IMALTRAN_GetRecvPattern(IMALTRAN_Manager *mgr,
                                       ITS_OCTET *pattern, ITS_USHORT *len);

#if defined(__cplusplus)
}
#endif

#endif /* ITS_IMAL_TRANS_H */
