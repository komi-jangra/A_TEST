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
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:50  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/16 03:26:18  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.42.1  2004/10/25 20:39:57  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/05 19:58:21  mmiers
 * LOG: Add PRC IP transports
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/10/18 00:10:25  mmiers
 * LOG: Correct a few bugs.
 * LOG:
 * LOG: Revision 5.2  2001/10/17 00:39:15  mmiers
 * LOG: Allow simultaneous family presence for TALI, IMAL, GDI
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/07 18:31:16  mmiers
 * LOG: Make this work on NT.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.8  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.4  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.3  2001/01/16 21:39:25  mmiers
 * LOG: Reorganize so that support is completely standalone
 * LOG:
 * LOG: Revision 3.2  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.2  2000/11/09 23:04:24  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:23  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.8  2000/06/22 23:07:50  rsonak
 * LOG:
 * LOG: Iterative servers cannot run protocols.
 * LOG:
 * LOG: Revision 2.7  2000/06/02 17:18:10  mmiers
 * LOG:
 * LOG:
 * LOG: Socket modifications.
 * LOG:
 * LOG: Revision 2.6  2000/05/15 21:21:04  mmiers
 * LOG:
 * LOG:
 * LOG: Snapshot for TALI.  Almost everything but ISUP is there now.
 * LOG:
 * LOG: Revision 2.5  2000/05/15 00:56:58  mmiers
 * LOG:
 * LOG:
 * LOG: First real cut of TALI implementation.  It's about 75% done, I
 * LOG: think.  Only 3 issues, 16 FIXMEs, mostly building messages.
 * LOG:
 * LOG: Revision 2.4  2000/05/13 00:56:04  mmiers
 * LOG:
 * LOG:
 * LOG: More thinking.
 * LOG:
 * LOG: Revision 2.3  2000/05/13 00:36:32  mmiers
 * LOG:
 * LOG:
 * LOG: Ok, we can read and write TALI messages, now to build the state
 * LOG: machine...
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

#if !defined(ITS_TALI_TRANS_H)
#define ITS_TALI_TRANS_H

#include <its.h>
#include <its_ip_trans.h>
#include <its_kasock_trans.h>
#include <its_mutex.h>

#ident "$Id: its_tali_trans.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

/*.interface:TALITRAN_*
 ****************************************************************************
 *
 * Interface: TALITRAN_*
 *
 * Purpose: this interface implements the TALI transport
 *  protocol.
 *
 * Usage:
 *  A few notes.
 *  o There are two types of synthetic messages.  Monitor messages are
 *      sent via TALITRAN_SendMonitorMsg(transport, data, len).  The msgs
 *      are received via the TALITRAN_MONITOR_ACK_CALLBACK list.  Thus,
 *      these messages do not appear on the event stream when GetNextEvent()
 *      is called.  The second type of synthetic message is the
 *      TALI_EVENT_MESSAGE.  This type of message *does* appear in the
 *      normal event stream.  These are sent via TALITRAN_SendRaw().
 *  o The layer (mtp3, sccp, or isup) that is transmitted is controlled
 *      by the taliUseUpperLayer resource.  "yes" or "YES" implies that
 *      payload should be sent via the SCCP or ISUP TALI messages.  Anything
 *      else implies that MTP3 should be used.
 *  o T1 and T2 default to two seconds.  T3 defaults to 5.
 ****************************************************************************/

/*
 * tali config vars
 */
#define TALI_T1_STRING                   "taliT1"
#define TALI_T2_STRING                   "taliT2"
#define TALI_T3_STRING                   "taliT3"
#define TALI_TRACE_KEEPALIVES_STRING     "taliTraceKeepAlives"
#define TALI_TRACE_PAYLOAD_STRING        "taliTracePayload"

/*
 * per transport config var
 */
#define TALI_LOCALLY_ALLOWED_ON_OPEN_STRING "taliLocallyAllowedOnOpen"
#define TALI_USE_UPPER_LAYER_STRING         "taliUseUpperLayer"
#define TALI_LOCAL_PC_STRING                "taliLocalPC"
#define TALI_ADJ_PC_STRING                  "taliAdjacentPC"

#define TALITRAN_CLIENT_CLASS_NAME       "TALITRAN_CLIENT"
#define TALITRAN_SERVER_CLASS_NAME       "TALITRAN_SERVER"
#define TALITRAN_ITERATIVE_CLASS_NAME    "TALITRAN_ITERATIVE"
#define TALITRAN_DYNAMIC_CLASS_NAME      "TALITRAN_DYNAMIC"
#define TALITRAN_LOCAL_EP_CLASS_NAME     "TALITRAN_LOCAL_EP"
#define TALITRAN_REMOTE_EP_CLASS_NAME    "TALITRAN_REMOTE_EP"

/*
 * All valid TALI states.
 */
typedef enum
{
    TALI_OOS,
    TALI_CONNECTING,
    TALI_CONNECTING_ALLOWED,
    TALI_PROHIBITED_PROHIBITED,
    TALI_PROHIBITED_ALLOWED,
    TALI_ALLOWED_PROHIBITED,
    TALI_ALLOWED_ALLOWED
}
TALI_ConnState;

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * transport control
 */
typedef struct
{
    TALI_ConnState          state;
    ITS_BOOLEAN             t1Running;
    ITS_TIME                t1Started;
    ITS_BOOLEAN             t2Running;
    ITS_TIME                t2Started;
    ITS_BOOLEAN             t3Running;
    ITS_TIME                t3Started;
    ITS_BOOLEAN             useUpperLayer;
    ITS_UINT                localPC;
    ITS_UINT                adjacentPC;
    ITS_BOOLEAN             localAllowed;
    ITS_MUTEX               localGuard;
    CALLBACK_Manager        *monitorAckCallback;
}
TALITRAN_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    SOCKTRAN_ObjectPart     socket;
    KASOCKTRAN_ObjectPart   kasocket;
    TALITRAN_ObjectPart     tali;
}
TALITRAN_Manager;

#define TALITRAN_STATE(x) \
    (((TALITRAN_Manager *)(x))->tali.state)

#define TALITRAN_T1_RUNNING(x) \
    (((TALITRAN_Manager *)(x))->tali.t1Running)

#define TALITRAN_T1_STARTED(x) \
    (((TALITRAN_Manager *)(x))->tali.t1Started)

#define TALITRAN_T2_RUNNING(x) \
    (((TALITRAN_Manager *)(x))->tali.t2Running)

#define TALITRAN_T2_STARTED(x) \
    (((TALITRAN_Manager *)(x))->tali.t2Started)

#define TALITRAN_T3_RUNNING(x) \
    (((TALITRAN_Manager *)(x))->tali.t3Running)

#define TALITRAN_T3_STARTED(x) \
    (((TALITRAN_Manager *)(x))->tali.t3Started)

#define TALITRAN_USE_UPPER_LAYER(x) \
    (((TALITRAN_Manager *)(x))->tali.useUpperLayer)

#define TALITRAN_LOCAL_ALLOWED(x) \
    (((TALITRAN_Manager *)(x))->tali.localAllowed)

#define TALITRAN_LOCAL_GUARD(x) \
    (((TALITRAN_Manager *)(x))->tali.localGuard)

#define TALITRAN_MONITOR_ACK_CALLBACK(x) \
    (((TALITRAN_Manager *)(x))->tali.monitorAckCallback)

#define TALITRAN_LOCAL_PC(x) \
    (((TALITRAN_Manager *)(x))->tali.localPC)

#define TALITRAN_ADJ_PC(x) \
    (((TALITRAN_Manager *)(x))->tali.adjacentPC)

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
TALITRAN_ClassRec, *TALITRAN_Class;

/*
 * the class records for the transport.  This is not
 * the only transport possible with TALI, just the
 * most common.
 */
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_ClientClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_ClientClass_ANSI;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_ServerClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_ServerClass_ANSI;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_DynamicServerClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_DynamicServerClass_ANSI;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_ClientClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_ClientClass_CCITT;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_ServerClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_ServerClass_CCITT;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_DynamicServerClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_DynamicServerClass_CCITT;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_ClientClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_ClientClass_PRC;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_ServerClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_ServerClass_PRC;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_DynamicServerClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_DynamicServerClass_PRC;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_ClientClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_ClientClass_TTC;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_ServerClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_ServerClass_TTC;
ITSDLLAPI extern TALITRAN_ClassRec    itsTALITRAN_DynamicServerClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsTALITRAN_DynamicServerClass_TTC;

#if defined(CCITT)

#define itsTALITRAN_ClientClassRec          itsTALITRAN_ClientClassRec_CCITT
#define itsTALITRAN_ClientClass             itsTALITRAN_ClientClass_CCITT
#define itsTALITRAN_ServerClassRec          itsTALITRAN_ServerClassRec_CCITT
#define itsTALITRAN_ServerClass             itsTALITRAN_ServerClass_CCITT
#define itsTALITRAN_DynamicServerClassRec   itsTALITRAN_DynamicServerClassRec_CCITT
#define itsTALITRAN_DynamicServerClass      itsTALITRAN_DynamicServerClass_CCITT

#define itsTALI_ClassRec                itsTALI_ClassRec_CCITT
#define itsTALI_Class                   itsTALI_Class_CCITT

#elif defined(ANSI)

#define itsTALITRAN_ClientClassRec          itsTALITRAN_ClientClassRec_ANSI
#define itsTALITRAN_ClientClass             itsTALITRAN_ClientClass_ANSI
#define itsTALITRAN_ServerClassRec          itsTALITRAN_ServerClassRec_ANSI
#define itsTALITRAN_ServerClass             itsTALITRAN_ServerClass_ANSI
#define itsTALITRAN_DynamicServerClassRec   itsTALITRAN_DynamicServerClassRec_ANSI
#define itsTALITRAN_DynamicServerClass      itsTALITRAN_DynamicServerClass_ANSI

#define itsTALI_ClassRec                itsTALI_ClassRec_ANSI
#define itsTALI_Class                   itsTALI_Class_ANSI

#elif defined(PRC)

#define itsTALITRAN_ClientClassRec          itsTALITRAN_ClientClassRec_PRC
#define itsTALITRAN_ClientClass             itsTALITRAN_ClientClass_PRC
#define itsTALITRAN_ServerClassRec          itsTALITRAN_ServerClassRec_PRC
#define itsTALITRAN_ServerClass             itsTALITRAN_ServerClass_PRC
#define itsTALITRAN_DynamicServerClassRec   itsTALITRAN_DynamicServerClassRec_PRC
#define itsTALITRAN_DynamicServerClass      itsTALITRAN_DynamicServerClass_PRC

#define itsTALI_ClassRec                itsTALI_ClassRec_PRC
#define itsTALI_Class                   itsTALI_Class_PRC

#elif defined(TTC)

#define itsTALITRAN_ClientClassRec          itsTALITRAN_ClientClassRec_TTC
#define itsTALITRAN_ClientClass             itsTALITRAN_ClientClass_TTC
#define itsTALITRAN_ServerClassRec          itsTALITRAN_ServerClassRec_TTC
#define itsTALITRAN_ServerClass             itsTALITRAN_ServerClass_TTC
#define itsTALITRAN_DynamicServerClassRec   itsTALITRAN_DynamicServerClassRec_TTC
#define itsTALITRAN_DynamicServerClass      itsTALITRAN_DynamicServerClass_TTC

#define itsTALI_ClassRec                itsTALI_ClassRec_TTC
#define itsTALI_Class                   itsTALI_Class_TTC

#endif

#if !defined(TALI_IMPLEMENTATION)
#if defined(WIN32)
#define TALIDLLAPI   __declspec(dllimport)
#else
#define TALIDLLAPI
#endif
#else
#if defined(WIN32)
#define TALIDLLAPI   __declspec(dllexport)
#else
#define TALIDLLAPI
#endif /* WIN32 */
#endif

/*
 * feature record
 */
TALIDLLAPI extern ITS_ClassRec         itsTALI_ClassRec_CCITT;
TALIDLLAPI extern ITS_Class            itsTALI_Class_CCITT;
TALIDLLAPI extern ITS_ClassRec         itsTALI_ClassRec_ANSI;
TALIDLLAPI extern ITS_Class            itsTALI_Class_ANSI;
TALIDLLAPI extern ITS_ClassRec         itsTALI_ClassRec_PRC;
TALIDLLAPI extern ITS_Class            itsTALI_Class_PRC;
TALIDLLAPI extern ITS_ClassRec         itsTALI_ClassRec_TTC;
TALIDLLAPI extern ITS_Class            itsTALI_Class_TTC;

/*
 * special functions.  Allowed can be controlled by resource, too.
 */
TALIDLLAPI int TALITRAN_SetLocalAllowed(TALITRAN_Manager *ft, ITS_BOOLEAN allowed);
TALIDLLAPI int TALITRAN_SendMonitorMsg(TALITRAN_Manager *ft,
                                       ITS_OCTET *data, ITS_USHORT len);
TALIDLLAPI int TALITRAN_SendRawEvent(TALITRAN_Manager *ft,
                                     ITS_OCTET *data, ITS_USHORT len);

#if defined(__cplusplus)
}
#endif

#endif /* ITS_TALI_TRANS_H */
