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
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2002/12/30 17:30:31  lbana
 * LOG: propagating bug fixes in PR6.1 to current.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2002/01/15 23:04:57  mmiers
 * LOG: Add CRC32C.  Update M2PA as far as I can without SCTP support.
 * LOG:
 * LOG: Revision 5.3  2002/01/09 21:21:58  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 5.2  2002/01/03 23:25:16  mmiers
 * LOG: Change codec signature.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.15  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.14  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.13  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.12  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.11  2000/12/19 17:43:33  mmiers
 * LOG: Start testing.
 * LOG:
 * LOG: Revision 3.10  2000/11/29 00:59:30  mmiers
 * LOG: Got read done.  Write should be simple.
 * LOG:
 * LOG: Revision 3.9  2000/11/28 23:44:29  mmiers
 * LOG: Today's SCTPTRAN installment.  About finished, just need to create
 * LOG: remote transports when clients connect/destroy when they leave.
 * LOG:
 * LOG: Revision 3.8  2000/11/16 23:01:55  mmiers
 * LOG: Add the SCTP transport.  Getting close on this...
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_SCTP_TRANS_H)
#define ITS_SCTP_TRANS_H

#include <its.h>
#include <its_object.h>
#include <its_callback.h>
#include <its_sctp.h>
#include <its_ip_trans.h>

#ident "$Id: its_sctp_trans.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

/*
 * IOCTL strings
 */
#define MAX_IN_STREAMS_STRING       "maxInStreams"
#define NUM_OUT_STREAMS_STRING      "numOutStreams"
#define MAX_ATTEMPTS_STRING         "maxAttempts"
#define INIT_COOKIE_LIFE_STRING     "cookieLife"
#define INIT_HB_ON_STRING           "hbOn"
#define INIT_TIMEOUT_STRING         "initTimeOut"
#define SEND_TIMEOUT_STRING         "sendTimeOut"
#define RECV_TIMEOUT_STRING         "recvTimeOut"
#define HB_TIMEOUT_STRING           "hbTimeOut"
#define SHUT_TIMEOUT_STRING         "shutdownTimeOut"
#define PMTU_TIMEOUT_STRING         "pmtuTimeOut"
#define IS_CLIENT_STRING            "isClient"

/*
 * payload type
 */
#define PAYLOAD_TYPE_STRING         "payloadType"

/*
 * forward
 */
typedef struct _sctptran_Manager *SCTPTRAN_ManagerPtr;

/*
 * IP transport API
 */
ITSDLLAPI int   SCTPTRAN_Open(SOCKTRAN_Manager *m);
ITSDLLAPI int   SCTPTRAN_Connect(SOCKTRAN_Manager *m);
ITSDLLAPI void  SCTPTRAN_Close(SOCKTRAN_Manager *m);

typedef int (*SCTP_CodecPtr)(SCTPTRAN_ManagerPtr m, ITS_EVENT *ev,
                             ITS_BOOLEAN *isManagement, ITS_OCTET *sls);

/*
 * codec data struct
 */
typedef struct
{
    char            *name;
    SCTP_PAYLOAD    type;
    SCTP_CodecPtr   encode;
    SCTP_CodecPtr   decode;
}
SCTPTRAN_CodecRec;

/*
 * local object needs
 */
typedef struct
{
    SCTP_PAYLOAD    ptype;
    SCTP_CodecPtr   encode;
    SCTP_CodecPtr   decode;
    char *          buffer;
    ITS_BOOLEAN     isClient;
    ITS_USHORT      inStreams;
    ITS_USHORT      outStreams;
    /* M2PA, being weird, needs some stuff here */
    ITS_INT         state;
    ITS_UINT        flags;
    ITS_SERIAL      t1;
    ITS_SERIAL      t2;
    ITS_SERIAL      t3;
    ITS_SERIAL      t6;
    ITS_SERIAL      pd;
    ITS_SERIAL      ls;
}
SCTPTRAN_ObjectPart;

#define SCTPTRAN_FLAG_EMERG         0x0001
#define SCTPTRAN_FLAG_ALIGN_SENT    0x0002
#define SCTPTRAN_FLAG_ALIGN_RCVD    0x0004
#define SCTPTRAN_FLAG_ASSOC_UP      0x0008
#define SCTPTRAN_FLAG_READY         0x0010
#define SCTPTRAN_FLAG_LPO           0x0020
#define SCTPTRAN_FLAG_PD_MASK       0x0f00
#define SCTPTRAN_FLAG_PD_SHIFT      8
#define SCTPTRAN_FLAG_PDM_MASK      0xf000
#define SCTPTRAN_FLAG_PDM_SHIFT     12

typedef struct _sctptran_Manager
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    SOCKTRAN_ObjectPart     socket;
    SCTPTRAN_ObjectPart     sctp;
}
SCTPTRAN_Manager;

#define SCTPTRAN_INSTREAMS(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.inStreams)
 
#define SCTPTRAN_OUTSTREAMS(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.outStreams)

#define SCTPTRAN_PAYLOAD(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.ptype)

#define SCTPTRAN_ENCODE(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.encode)

#define SCTPTRAN_DECODE(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.decode)

#define SCTPTRAN_BUFFER(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.buffer)

#define SCTPTRAN_IS_CLIENT(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.isClient)

#define SCTPTRAN_STATE(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.state)

#define SCTPTRAN_FLAGS(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.flags)

#define SCTPTRAN_T1(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.t1)

#define SCTPTRAN_T2(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.t2)

#define SCTPTRAN_T3(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.t3)

#define SCTPTRAN_T6(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.t6)

#define SCTPTRAN_PD(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.pd)

#define SCTPTRAN_LS(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.ls)

#define SCTPTRAN_LOCAL_ENDPOINT_CLASS_NAME  "SCTPTRAN_LocalEndPoint"
#define SCTPTRAN_REMOTE_ENDPOINT_CLASS_NAME "SCTPTRAN_RemoteEndPoint"

ITSDLLAPI extern SOCKTRAN_ClassRec    itsSCTPTRAN_LocalEndPointClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSCTPTRAN_LocalEndPointClass;
ITSDLLAPI extern SOCKTRAN_ClassRec    itsSCTPTRAN_RemoteEndPointClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSCTPTRAN_RemoteEndPointClass;

/*
 * UA usage
 */
ITSDLLAPI int SCTPTRAN_RegisterCodec(char *name, SCTP_PAYLOAD ptype,
                                     SCTP_CodecPtr encode, SCTP_CodecPtr decode);
ITSDLLAPI int SCTPTRAN_DeregisterCodec(char *name);

/*
 * UA usage
 */
ITSDLLAPI extern CALLBACK_Manager    *SCTPTRAN_ManagementCallbacks;

#endif /* ITS_SCTP_TRANS_H */
