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
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:46  cvsadmin
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
 * LOG: Revision 5.4  2001/11/07 23:01:41  mmiers
 * LOG: A bug fix, adding IPC mutex.
 * LOG:
 * LOG: Revision 5.3  2001/10/18 00:10:25  mmiers
 * LOG: Correct a few bugs.
 * LOG:
 * LOG: Revision 5.2  2001/10/17 00:39:15  mmiers
 * LOG: Allow simultaneous family presence for TALI, IMAL, GDI
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
 * LOG: Revision 3.4  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.3  2001/01/16 21:39:25  mmiers
 * LOG: Reorganize so that support is completely standalone
 * LOG:
 * LOG: Revision 3.2  2000/11/13 19:08:34  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.2  2000/11/09 23:04:24  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:14  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.10  2000/06/22 23:07:49  rsonak
 * LOG:
 * LOG: Iterative servers cannot run protocols.
 * LOG:
 * LOG: Revision 2.9  2000/06/02 17:18:09  mmiers
 * LOG:
 * LOG:
 * LOG: Socket modifications.
 * LOG:
 * LOG: Revision 2.8  2000/05/16 00:17:19  mmiers
 * LOG:
 * LOG:
 * LOG: Add C++ API for SOCK_GetPeerName().  Clean up GDI a bit.
 * LOG:
 * LOG: Revision 2.7  2000/05/11 02:06:12  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 2.6  2000/05/10 23:39:48  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based protocols with heartbeats.
 * LOG:
 * LOG: Revision 2.5  2000/01/31 23:17:00  mmiers
 * LOG:
 * LOG:
 * LOG: Some GDI tweaks, some RUDP work.
 * LOG:
 * LOG: Revision 2.4  2000/01/14 23:25:44  mmiers
 * LOG:
 * LOG:
 * LOG: Work with RUDP more.
 * LOG:
 * LOG: Revision 2.3  1999/12/16 21:15:11  mmiers
 * LOG:
 * LOG: Try to get the split right.
 * LOG:
 * LOG: Revision 2.2  1999/12/16 00:52:35  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 21:25:23  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI
 * LOG:
 * LOG: Revision 1.5.2.1  1999/12/06 21:22:44  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP GDI.
 * LOG:
 * LOG: Revision 1.5  1999/12/01 19:44:41  mmiers
 * LOG:
 * LOG:
 * LOG: Make the application ID more intuitive.
 * LOG:
 * LOG: Revision 1.4  1999/11/10 15:04:05  mmiers
 * LOG:
 * LOG:
 * LOG: Build problems on Solaris.
 * LOG:
 * LOG: Revision 1.3  1999/11/05 20:30:07  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up first cut of GDI, remove volatile qualifier from
 * LOG: FindTransport.
 * LOG:
 * LOG: Revision 1.2  1999/10/29 21:06:50  mmiers
 * LOG:
 * LOG:
 * LOG: Cleanup, C++ protection.
 * LOG:
 * LOG: Revision 1.1  1999/10/29 20:46:08  mmiers
 * LOG:
 * LOG:
 * LOG: Initial GDI implementation.  Needs work still.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_GDI_TRANS_H)
#define ITS_GDI_TRANS_H

#include <its.h>
#include <its_ip_trans.h>
#include <its_kasock_trans.h>

#ident "$Id: its_gdi_trans.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#define GDITRAN_CLIENT_CLASS_NAME       "GDITRAN_CLIENT"
#define GDITRAN_SERVER_CLASS_NAME       "GDITRAN_SERVER"
#define GDITRAN_ITERATIVE_CLASS_NAME    "GDITRAN_ITERATIVE"
#define GDITRAN_DYNAMIC_CLASS_NAME      "GDITRAN_DYNAMIC"

/*
 * GDI keepalive timer name
 */
#define GDI_KEEPALIVE_TIMEOUT_STRING    "gdiKeepAliveTimer"
#define GDI_TRACE_KEEPALIVES_STRING     "gdiTraceKeepAlives"
#define GDI_TRACE_PAYLOAD_STRING        "gdiTracePayload"
#define GDI_LOCAL_PC_STRING             "gdiLocalPC"
#define GDI_REMOTE_PC_STRING            "gdiRemotePC"
#define GDI_REMOTE_SSN_STRING           "gdiRemoteSSN"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * transport control
 */
typedef struct
{
    ITS_TIME                lastMsgTransmitTime;
    ITS_TIME                lastMsgReceiveTime;
    ITS_TIME                keepAliveLocalTransmitTime;
    ITS_TIME                keepAliveRemoteReceiveTime;
    ITS_BOOLEAN             keepAliveRemoteReqPending;
    ITS_BOOLEAN             keepAliveLocalReqPending;
    ITS_UINT                localPC;
    ITS_UINT                remotePC;
    ITS_OCTET               remoteSSN;
}
GDITRAN_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    SOCKTRAN_ObjectPart     socket;
    KASOCKTRAN_ObjectPart   kasocket;
    GDITRAN_ObjectPart      gdi;
}
GDITRAN_Manager;

#define GDITRAN_LAST_MSG_TX_TIME(x) \
    (((GDITRAN_Manager *)(x))->gdi.lastMsgTransmitTime)

#define GDITRAN_LAST_MSG_RX_TIME(x) \
    (((GDITRAN_Manager *)(x))->gdi.lastMsgReceiveTime)

#define GDITRAN_KA_LOCAL_TX_TIME(x) \
    (((GDITRAN_Manager *)(x))->gdi.keepAliveLocalTransmitTime)

#define GDITRAN_KA_REMOTE_RX_TIME(x) \
    (((GDITRAN_Manager *)(x))->gdi.keepAliveRemoteReceiveTime)

#define GDITRAN_KA_REMOTE_REQ_PENDING(x) \
    (((GDITRAN_Manager *)(x))->gdi.keepAliveRemoteReqPending)

#define GDITRAN_KA_LOCAL_REQ_PENDING(x) \
    (((GDITRAN_Manager *)(x))->gdi.keepAliveLocalReqPending)

#define GDITRAN_LOCAL_PC(x) \
    (((GDITRAN_Manager *)(x))->gdi.localPC)

#define GDITRAN_REMOTE_PC(x) \
    (((GDITRAN_Manager *)(x))->gdi.remotePC)

#define GDITRAN_LOCAL_SSN(x) \
    (((GDITRAN_Manager *)(x))->gdi.localSSN)

#define GDITRAN_REMOTE_SSN(x) \
    (((GDITRAN_Manager *)(x))->gdi.remoteSSN)
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
GDITRAN_ClassRec, *GDITRAN_Class;

/*
 * the class records for the transport.  This is not
 * the only transport possible with GDI, just the
 * most common.
 */
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_ClientClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_ClientClass_ANSI;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_ServerClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_ServerClass_ANSI;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_DynamicServerClassRec_ANSI;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_DynamicServerClass_ANSI;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_ClientClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_ClientClass_CCITT;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_ServerClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_ServerClass_CCITT;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_DynamicServerClassRec_CCITT;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_DynamicServerClass_CCITT;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_ClientClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_ClientClass_PRC;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_ServerClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_ServerClass_PRC;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_DynamicServerClassRec_PRC;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_DynamicServerClass_PRC;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_ClientClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_ClientClass_TTC;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_ServerClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_ServerClass_TTC;
ITSDLLAPI extern GDITRAN_ClassRec     itsGDITRAN_DynamicServerClassRec_TTC;
ITSDLLAPI extern TRANSPORT_Class      itsGDITRAN_DynamicServerClass_TTC;

#if defined(CCITT)

#define itsGDITRAN_ClientClassRec           itsGDITRAN_ClientClassRec_CCITT
#define itsGDITRAN_ClientClass              itsGDITRAN_ClientClass_CCITT
#define itsGDITRAN_ServerClassRec           itsGDITRAN_ServerClassRec_CCITT
#define itsGDITRAN_ServerClass              itsGDITRAN_ServerClass_CCITT
#define itsGDITRAN_DynamicServerClassRec    itsGDITRAN_DynamicServerClassRec_CCITT
#define itsGDITRAN_DynamicServerClass       itsGDITRAN_DynamicServerClass_CCITT

#define itsGDI_ClassRec          itsGDI_ClassRec_CCITT
#define itsGDI_Class             itsGDI_Class_CCITT

#elif defined(ANSI)

#define itsGDITRAN_ClientClassRec           itsGDITRAN_ClientClassRec_ANSI
#define itsGDITRAN_ClientClass              itsGDITRAN_ClientClass_ANSI
#define itsGDITRAN_ServerClassRec           itsGDITRAN_ServerClassRec_ANSI
#define itsGDITRAN_ServerClass              itsGDITRAN_ServerClass_ANSI
#define itsGDITRAN_DynamicServerClassRec    itsGDITRAN_DynamicServerClassRec_ANSI
#define itsGDITRAN_DynamicServerClass       itsGDITRAN_DynamicServerClass_ANSI

#define itsGDI_ClassRec          itsGDI_ClassRec_ANSI
#define itsGDI_Class             itsGDI_Class_ANSI

#elif defined(PRC)

#define itsGDITRAN_ClientClassRec           itsGDITRAN_ClientClassRec_PRC
#define itsGDITRAN_ClientClass              itsGDITRAN_ClientClass_PRC
#define itsGDITRAN_ServerClassRec           itsGDITRAN_ServerClassRec_PRC
#define itsGDITRAN_ServerClass              itsGDITRAN_ServerClass_PRC
#define itsGDITRAN_DynamicServerClassRec    itsGDITRAN_DynamicServerClassRec_PRC
#define itsGDITRAN_DynamicServerClass       itsGDITRAN_DynamicServerClass_PRC

#define itsGDI_ClassRec          itsGDI_ClassRec_PRC
#define itsGDI_Class             itsGDI_Class_PRC

#elif defined(TTC)

#define itsGDITRAN_ClientClassRec           itsGDITRAN_ClientClassRec_TTC
#define itsGDITRAN_ClientClass              itsGDITRAN_ClientClass_TTC
#define itsGDITRAN_ServerClassRec           itsGDITRAN_ServerClassRec_TTC
#define itsGDITRAN_ServerClass              itsGDITRAN_ServerClass_TTC
#define itsGDITRAN_DynamicServerClassRec    itsGDITRAN_DynamicServerClassRec_TTC
#define itsGDITRAN_DynamicServerClass       itsGDITRAN_DynamicServerClass_TTC

#define itsGDI_ClassRec          itsGDI_ClassRec_TTC
#define itsGDI_Class             itsGDI_Class_TTC

#endif

/*
 * feature record
 */
#if !defined(GDI_IMPLEMENTATION)
#if defined(WIN32)
#define GDIDLLAPI   __declspec(dllimport)
#else
#define GDIDLLAPI
#endif
#else
#if defined(WIN32)
#define GDIDLLAPI   __declspec(dllexport)
#else
#define GDIDLLAPI
#endif /* WIN32 */
#endif

GDIDLLAPI extern ITS_ClassRec           itsGDI_ClassRec_CCITT;
GDIDLLAPI extern ITS_Class              itsGDI_Class_CCITT;
GDIDLLAPI extern ITS_ClassRec           itsGDI_ClassRec_ANSI;
GDIDLLAPI extern ITS_Class              itsGDI_Class_ANSI;
GDIDLLAPI extern ITS_ClassRec           itsGDI_ClassRec_PRC;
GDIDLLAPI extern ITS_Class              itsGDI_Class_PRC;
GDIDLLAPI extern ITS_ClassRec           itsGDI_ClassRec_TTC;
GDIDLLAPI extern ITS_Class              itsGDI_Class_TTC;

#if defined(__cplusplus)
}
#endif

#endif /* ITS_GDI_TRANS_H */
