/*****************************************************************************
 *                                                                           *
 *     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *             Manufactured in the United States of America.                 *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                           *
 *   This product and related documentation is protected by copyright and    *
 *   distributed under licenses restricting its use, copying, distribution   *
 *   and decompilation.  No part of this product or related documentation    *
 *   may be reproduced in any form by any means without prior written        *
 *   authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                           *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *   government is subject to restrictions as set forth in subparagraph      *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                           *
 *****************************************************************************
 *                                                                           *
 * CONTRACT: INTERNAL                                                        *
 *                                                                           *
 *****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2002/09/10 19:13:37  yranade
 * LOG: Portability fix.  Can be long as that is 32 bits on most archs
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/03/26 21:22:35  hdivoux
 * LOG: Add mailbox poll function.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:07  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 1.4  2001/07/02 21:53:57  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.3  2001/06/29 16:46:50  hdivoux
 * LOG: Add GCS event related functions.
 * LOG:
 * LOG: Revision 1.2  2001/06/28 15:11:28  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.1  2001/06/26 21:40:16  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/

/*
 *  GCS (Group Communication System) client interface.
 */

#if !defined(_GCS_CLIENT_H_)
#define _GCS_CLIENT_H_

#include <its.h>

#ident "$Id: gcs_client.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 * Export control.
 */

#if defined(WIN32)

#if defined(GCS_IMPLEMENTATION)
#define GCSDLLAPI __declspec(dllexport)
#else
#define GCSDLLAPI __declspec(dllimport)
#endif

#else  /* !defined(WIN32) */

#define GCSDLLAPI

#endif /* defined(WIN32) */


/*
 * Event related constants.
 */

#define GCS_MAX_FD_EVENTS           2000


#define	GCS_NUM_PRIORITY            3

#define GCS_LOW_PRIORITY            0
#define GCS_MEDIUM_PRIORITY         1
#define GCS_HIGH_PRIORITY           2


#define GCS_NUM_FDTYPES             3

#define GCS_READ_FD                 0
#define GCS_WRITE_FD                1
#define GCS_EXCEPT_FD               2


/* 
 * Contants.
 */

#define GCS_DEFAULT_PORT            4803

#define GCS_VERSION                 ((3 << 24) | (15 << 16) | 2)

#define GCS_MAX_GROUP_NAME          32
#define GCS_MAX_PRIVATE_NAME        10
#define GCS_MAX_PROCESS_NAME        20

#define GCS_UNRELIABLE_MSG          0x00000001
#define GCS_RELIABLE_MSG            0x00000002
#define GCS_FIFO_MSG                0x00000004
#define GCS_CAUSAL_MSG              0x00000008
#define GCS_AGREED_MSG              0x00000010
#define GCS_SAFE_MSG                0x00000020
#define GCS_REGULAR_MSG             0x0000003F

#define GCS_SELF_DISCARD            0x00000040
#define GCS_DROP_RECV               0x01000000

#define GCS_REG_MEMB_MSG            0x00001000
#define GCS_TRANSITION_MSG          0x00002000
#define GCS_CAUSED_BY_JOIN          0x00000100
#define GCS_CAUSED_BY_LEAVE         0x00000200
#define GCS_CAUSED_BY_DISCONNECT    0x00000400
#define GCS_CAUSED_BY_NETWORK       0x00000800
#define GCS_MEMBERSHIP_MSG          0x00003F00

#define GCS_ENDIAN_RESERVED         0x80000080
#define GCS_RESERVED                0x003FC000
#define GCS_REJECT_MSG              0x00400000


/*
 * Success codes.
 */

#define GCS_SUCCESS                 0
#define GCS_ACCEPT_SESSION          1


/* 
 * Error codes.
 */

#define GCS_ILLEGAL                 -1
#define GCS_COULD_NOT_CONNECT       -2
#define GCS_REJECT_QUOTA            -3
#define GCS_REJECT_NO_NAME          -4
#define GCS_REJECT_ILLEGAL_NAME     -5
#define GCS_REJECT_NOT_UNIQUE       -6
#define GCS_REJECT_VERSION          -7
#define GCS_CONNECTION_CLOSED       -8

#define GCS_ILLEGAL_SESSION         -11
#define GCS_ILLEGAL_SERVICE         -12
#define GCS_ILLEGAL_MESSAGE         -13
#define GCS_ILLEGAL_GROUP           -14
#define GCS_BUFFER_TOO_SHORT        -15
#define GCS_GROUPS_TOO_SHORT        -16
#define GCS_MESSAGE_TOO_LONG        -17


/*
 * Boolean helpers for message types.
 */

#define GCS_IsUnreliableMsg(type)       (type &  GCS_UNRELIABLE_MSG      )
#define GCS_IsReliableMsg(type)         (type &  GCS_RELIABLE_MSG        )
#define GCS_IsFifoMsg(type)             (type &  GCS_FIFO_MSG            )
#define GCS_IsCausalMsg(type)           (type &  GCS_CAUSAL_MSG          )
#define GCS_IsAgreedMsg(type)           (type &  GCS_AGREED_MSG          )
#define GCS_IsSafeMsg(type)             (type &  GCS_SAFE_MSG            )
#define GCS_IsRegularMsg(type)          (type &  GCS_REGULAR_MSG         )

#define GCS_IsSelfDiscard(type)         (type &  GCS_SELF_DISCARD        )

#define GCS_IsRegMembMsg(type)          (type &  GCS_REG_MEMB_MSG        )
#define GCS_IsTransitionMsg(type)       (type &  GCS_TRANSITION_MSG      )
#define GCS_IsCausedJoinMsg(type)       (type &  GCS_CAUSED_BY_JOIN      )
#define GCS_IsCausedLeaveMsg(type)      (type &  GCS_CAUSED_BY_LEAVE     )
#define GCS_IsCausedDisconnectMsg(type) (type &  GCS_CAUSED_BY_DISCONNECT)
#define GCS_IsCausedNetworkMsg(type)    (type &  GCS_CAUSED_BY_NETWORK   )
#define GCS_IsMembershipMsg(type)       (type &  GCS_MEMBERSHIP_MSG      )
#define GCS_IsRejectMsg(type)           (type &  GCS_REJECT_MSG          )

#define GCS_IsSelfLeave(type)           (((type) & GCS_CAUSED_BY_LEAVE) &&  \
                                            !((type) & (GCS_REG_MEMB_MSG |  \
                                                GCS_TRANSITION_MSG)))

/*
 *  Flip (little endian vs. big endian) helpers.
 */

#define GCS_FlipInt16(value)    (((value >> 8) & 0x00FF) |  \
                                    ((value << 8) & 0xFF00))

#define GCS_FlipInt32(value)    (((value >>24) & 0x000000FF) |           \
                                    ((value >> 8) & 0x0000FF00) |        \
                                        ((value << 8) & 0x00FF0000) |    \
                                            ((value <<24) & 0xFF000000))


/*
 * Mailbox and service definitions.
 */

#define GCS_MAILBOX int
#define GCS_SERVICE int


/*
 * Mailbox poll related constants.
 */

#define GCS_POLL_READ           (0x01)
#define GCS_POLL_WRITE          (0x04)
#define GCS_POLL_ERROR          (0x08)


/*
 * Public structures used by GCS API.
 */

#define GCS_MAX_SCATTER_ELEMENTS    100

typedef struct _st_GCS_SCAT_ELEMENT
{
    char*   buf;
    ITS_INT len;
} 
GCS_SCAT_ELEMENT;

typedef struct _st_GCS_SCATTER
{
    ITS_INT             numElements;
    GCS_SCAT_ELEMENT    elements[GCS_MAX_SCATTER_ELEMENTS];
}
GCS_SCATTER;

typedef struct _st_GCS_GROUP_ID
{
    ITS_INT id[5];
} 
GCS_GROUP_ID;

typedef struct _st_GCS_TIME 
{
    ITS_LONG sec;
	ITS_LONG usec;
}
GCS_TIME;

typedef struct
{
    GCS_MAILBOX mailbox;
    GCS_MAILBOX Stubmailbox;
    int         lookFor;
    int         wasSet;
}
GCS_MAILBOX_POLL_INFO;



/*.interface:GCS_
 *****************************************************************************
 *  Interface:
 *      GCS_*
 *
 *  Purpose:
 *      Group Communication System client API.
 *
 *  Usage:
 *      See GCS associated documentation.
 *
 *****************************************************************************/

GCSDLLAPI int GCS_Version(
                    ITS_INT* majorVersion, 
                    ITS_INT* minorVersion, 
                    ITS_INT* patchVersion);

GCSDLLAPI int GCS_Connect( 
                    const char* gcsName, 
                    const char* privateName,
                    ITS_INT priority, 
                    ITS_INT groupMembership, 
                    GCS_MAILBOX* mailbox,
                    char* privateGroup);

GCSDLLAPI int GCS_ConnectTimeout(
                    const char* gcsName, 
                    const char* privateName,
                    ITS_INT priority, 
                    ITS_INT groupMembership, 
                    GCS_MAILBOX* mailbox,
                    char* privateGroup,
                    GCS_TIME timeout);

GCSDLLAPI int GCS_Disconnect(GCS_MAILBOX mailbox);

GCSDLLAPI int GCS_Join(GCS_MAILBOX mailbox, const char* group);

GCSDLLAPI int GCS_Leave(GCS_MAILBOX mailbox, const char* group);

GCSDLLAPI int GCS_Multicast(
                    GCS_MAILBOX mailbox, 
                    GCS_SERVICE service, 
                    const char* group,
                    ITS_SHORT msgType, 
                    ITS_INT msgLen, 
                    const char* msg);

GCSDLLAPI int GCS_ScatMulticast( 
                    GCS_MAILBOX mailbox, 
                    GCS_SERVICE service,
                    const char* group,
                    ITS_SHORT msgType, 
                    const GCS_SCATTER* scatter);

GCSDLLAPI int GCS_MultigroupMulticast(
                    GCS_MAILBOX mailbox, 
                    GCS_SERVICE service,
                    ITS_INT numGroups,
                    const char groups[][GCS_MAX_GROUP_NAME],
                    ITS_SHORT msgType, 
                    ITS_INT msgLen,
                    const char* msg);

GCSDLLAPI int GCS_MultigroupScatMulticast( 
                    GCS_MAILBOX mailbox, 
                    GCS_SERVICE service,
                    ITS_INT numGroups,
                    const char groups[][GCS_MAX_GROUP_NAME],
                    ITS_SHORT msgType,
                    const GCS_SCATTER* scatter);

GCSDLLAPI int GCS_Receive( 
                    GCS_MAILBOX mailbox, 
                    GCS_SERVICE* service,
                    char sender[GCS_MAX_GROUP_NAME], 
                    ITS_INT maxGroups,
                    ITS_INT* numGroups, 
                    char groups[][GCS_MAX_GROUP_NAME],
                    ITS_SHORT* msgType, 
                    ITS_INT* endianMismatch,
                    ITS_INT maxMsgLen, 
                    char* msg);

GCSDLLAPI int GCS_ScatReceive( 
                    GCS_MAILBOX mailbox, 
                    GCS_SERVICE* service,
                    char sender[GCS_MAX_GROUP_NAME], 
                    ITS_INT maxGroups,
                    ITS_INT* numGroups, 
                    char groups[][GCS_MAX_GROUP_NAME],
                    ITS_SHORT* msgType, 
                    ITS_INT* endianMismatch,
                    GCS_SCATTER* scatter);

GCSDLLAPI int GCS_Poll(GCS_MAILBOX mailbox);

GCSDLLAPI int GCS_EqualGroupIds(GCS_GROUP_ID groupId1, GCS_GROUP_ID groupId2);

GCSDLLAPI void GCS_ReportError(int error);


/*
 *  Mailbox poll related.
 */

GCSDLLAPI int GCS_MailboxPoll(
                    GCS_MAILBOX_POLL_INFO* mailboxPollInfos,
                    ITS_UINT numMailboxPollInfos,
                    GCS_TIME* timeout);

/*
 *  Time related.
 */

GCSDLLAPI GCS_TIME  GCS_GetTime();

GCSDLLAPI GCS_TIME  GCS_SubTime(GCS_TIME t, GCS_TIME delta);

GCSDLLAPI GCS_TIME  GCS_AddTime(GCS_TIME t, GCS_TIME delta);

GCSDLLAPI int       GCS_CompareTime(GCS_TIME t1, GCS_TIME t2);


/*
 *  Event related (not thread safe).
 */

GCSDLLAPI int   GCS_EventInitialize();

GCSDLLAPI int   GCS_EventQueue(
                    void (*function)(int code, void* data), 
                    int code, 
                    void* data,
                    GCS_TIME deltaTime);

GCSDLLAPI int   GCS_EventDequeue( 
                    void (*function)(int code, void* data), 
                    int code,
                    void* data);

GCSDLLAPI void  GCS_EventDelay(GCS_TIME t);

GCSDLLAPI int   GCS_EventAttachFd(
                    int fd, 
                    int fdType,
                    void (*function)(int fd, int code, void* data),
                    int code,
                    void* data, 
                    int priority);

GCSDLLAPI int   GCS_EventDetachFd(int fd, int fdType);

GCSDLLAPI int   GCS_EventSetActiveThreshold(int priority);

GCSDLLAPI int   GCS_EventActivateFd(int fd, int fdType);

GCSDLLAPI int   GCS_EventDeactivateFd(int fd, int fdType);

GCSDLLAPI int   GCS_EventNumActive(int priority);

GCSDLLAPI void  GCS_EventHandleEvents();

GCSDLLAPI void  GCS_EventExitEvents();


#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_GCS_CLIENT_H_) */
