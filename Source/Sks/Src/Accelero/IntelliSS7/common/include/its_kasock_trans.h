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
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.2  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:18  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.4  2000/06/22 23:07:50  rsonak
 * LOG:
 * LOG: Iterative servers cannot run protocols.
 * LOG:
 * LOG: Revision 1.3  2000/06/02 17:18:10  mmiers
 * LOG:
 * LOG:
 * LOG: Socket modifications.
 * LOG:
 * LOG: Revision 1.2  2000/05/23 21:26:34  mmiers
 * LOG:
 * LOG:
 * LOG: Snapshot of SCTP.
 * LOG:
 * LOG: Revision 1.1  2000/05/10 23:43:44  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based transports with heartbeats.
 * LOG:
 * LOG: Revision 1.1  2000/05/10 23:41:22  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCAP based transports with heartbeats.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_KASOCKTRAN_H)
#define ITS_KASOCKTRAN_H

#include <its.h>
#include <its_object.h>
#include <its_transports.h>
#include <its_ip_trans.h>

#ident "$Id: its_kasock_trans.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * GDI and TALI are implemented via this abstraction
 */

#define KASOCKTRAN_CLIENT_CLASS_NAME       "KASOCKTRAN_CLIENT"
#define KASOCKTRAN_SERVER_CLASS_NAME       "KASOCKTRAN_SERVER"
#define KASOCKTRAN_ITERATIVE_CLASS_NAME    "KASOCKTRAN_ITERATIVE"
#define KASOCKTRAN_DYNAMIC_CLASS_NAME      "KASOCKTRAN_DYNAMIC"

/*
 * locally significant info
 */
typedef struct
{
    ITS_POINTER lowReadBuf;
    ITS_POINTER lowWriteBuf;
}
KASOCKTRAN_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    SOCKTRAN_ObjectPart     socket;
    KASOCKTRAN_ObjectPart   keepalive;
}
KASOCKTRAN_Manager;

#define KASOCKTRAN_LOW_READ_BUF(x) \
    (((KASOCKTRAN_Manager *)(x))->keepalive.lowReadBuf)

#define KASOCKTRAN_LOW_WRITE_BUF(x) \
    (((KASOCKTRAN_Manager *)(x))->keepalive.lowWriteBuf)

/*
 * class procs.
 *
 * A note to users: if a received event is eaten (because it
 * is consumed as a protocol message and not a payload message),
 * then decode proc should return ITS_ENOMSG.
 */
typedef int     (*KASOCKTRANRegisterProc)(KASOCKTRAN_Manager *);
typedef void    (*KASOCKTRANDeregisterProc)(KASOCKTRAN_Manager *);
typedef int     (*KASOCKTRANReadWriteProc)(KASOCKTRAN_Manager *, void *);
typedef int     (*KASOCKTRANCodecProc)(KASOCKTRAN_Manager *, ITS_EVENT *, void *);
typedef void    (*KASOCKTRANRunProc)(KASOCKTRAN_Manager *);
typedef void    (*KASOCKTRANMsgProc)(KASOCKTRAN_Manager *, ITS_EVENT *);

typedef struct
{
    KASOCKTRANRegisterProc       reg;
    KASOCKTRANDeregisterProc     dereg;
    KASOCKTRANReadWriteProc      lowRead;
    KASOCKTRANReadWriteProc      lowWrite;
    KASOCKTRANCodecProc          encodeInject;
    KASOCKTRANCodecProc          decodeFilter;
    KASOCKTRANRunProc            checkTime;
    KASOCKTRANMsgProc            checkEvent;
}
KASOCKTRAN_ClassPart;

typedef struct
{
    ITS_CoreClassPart       coreClass;
    TRANSPORT_ClassPart     transportClass;
    SOCKTRAN_ClassPart      socktranClass;
    KASOCKTRAN_ClassPart    kasocktranClass;
}
KASOCKTRAN_ClassRec, *KASOCKTRAN_Class;

#define KASOCKTRAN_CLASS_REGISTER(x) \
    (((KASOCKTRAN_Class)(x))->kasocktranClass.reg)

#define KASOCKTRAN_CLASS_DEREGISTER(x) \
    (((KASOCKTRAN_Class)(x))->kasocktranClass.dereg)

#define KASOCKTRAN_CLASS_LOW_READ(x) \
    (((KASOCKTRAN_Class)(x))->kasocktranClass.lowRead)

#define KASOCKTRAN_CLASS_LOW_WRITE(x) \
    (((KASOCKTRAN_Class)(x))->kasocktranClass.lowWrite)

#define KASOCKTRAN_CLASS_ENCODE(x) \
    (((KASOCKTRAN_Class)(x))->kasocktranClass.encodeInject)

#define KASOCKTRAN_CLASS_DECODE(x) \
    (((KASOCKTRAN_Class)(x))->kasocktranClass.decodeFilter)

#define KASOCKTRAN_CLASS_CHECK_TIME(x) \
    (((KASOCKTRAN_Class)(x))->kasocktranClass.checkTime)

#define KASOCKTRAN_CLASS_CHECK_EVENT(x) \
    (((KASOCKTRAN_Class)(x))->kasocktranClass.checkEvent)

/*
 * inheritance
 */
#define KASOCKTRAN_CLASS_REGISTER_INHERIT \
    (KASOCKTRANRegisterProc)NULL

#define KASOCKTRAN_CLASS_DEREGISTER_INHERIT \
    (KASOCKTRANDeregisterProc)NULL

#define KASOCKTRAN_CLASS_LOW_READ_INHERIT \
    (KASOCKTRANReadWriteProc)NULL

#define KASOCKTRAN_CLASS_LOW_WRITE_INHERIT \
    (KASOCKTRANReadWriteProc)NULL

#define KASOCKTRAN_CLASS_ENCODE_INHERIT \
    (KASOCKTRANCodecProc)NULL

#define KASOCKTRAN_CLASS_DECODE_INHERIT \
    (KASOCKTRANCodecProc)NULL

#define KASOCKTRAN_CLASS_CHECK_TIME_INHERIT \
    (KASOCKTRANRunProc)NULL

#define KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT \
    (KASOCKTRANMsgProc)NULL

/*
 * the class records for the transport.
 */
ITSDLLAPI extern KASOCKTRAN_ClassRec  itsKASOCKTRAN_ClientClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsKASOCKTRAN_ClientClass;
ITSDLLAPI extern KASOCKTRAN_ClassRec  itsKASOCKTRAN_ServerClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsKASOCKTRAN_ServerClass;
ITSDLLAPI extern KASOCKTRAN_ClassRec  itsKASOCKTRAN_DynamicServerClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsKASOCKTRAN_DynamicServerClass;
ITSDLLAPI extern KASOCKTRAN_ClassRec  itsKASOCKTRAN_LocalEndPointClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsKASOCKTRAN_LocalEndPointClass;
ITSDLLAPI extern KASOCKTRAN_ClassRec  itsKASOCKTRAN_RemoteEndPointClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsKASOCKTRAN_RemoteEndPointClass;

/*
 * feature start
 */
ITSDLLAPI extern ITS_Class            itsKEEPALIVE_Class;

#if defined(__cplusplus)
}
#endif

#endif /* ITS_KASOCKTRAN_H */
