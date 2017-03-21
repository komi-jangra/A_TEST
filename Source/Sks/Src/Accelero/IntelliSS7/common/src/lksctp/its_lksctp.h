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
 *  ID: $Id: its_lksctp.h,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $
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
 ****************************************************************************/
#ident "$Id: its_lksctp.h,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

#if !defined(ITS_LKSCTP_H)
#define ITS_LKSCTP_H

#include <its_tq_trans.h>
#include <dbc_serv.h>
#include <its_sockets.h>

#if defined(linux)
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#endif

#if !defined(SCTP_IMPLEMENTATION)
#define SCTPDLLAPI   ITSDLLAPI
#else
#define SCTPDLLAPI
#endif

/*
 * feature record(s)
 */
SCTPDLLAPI extern ITS_Class        itsLKSCTP_Class;        /* protocol engine */
ITSDLLAPI  extern ITS_ClassRec     itsSCTPTRAN_ClassRec;   /* transport wrapper */
ITSDLLAPI  extern ITS_Class        itsSCTPTRAN_Class;      /* transport wrapper */

#define SCTPTRAN_CLASS_NAME "SCTP Transport Feature"


/*****************************************************************************
 *
 * Generic management data.
 *
 *****************************************************************************/
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

/*****************************************************************************
 *
 * The LKSCTP General Configuration.
 *
 *****************************************************************************/
typedef struct
{
    MGMT_AlarmLevel alarmLevel;
    ITS_BOOLEAN     traceOn;     /* on(1), off(0) */
    ITS_CHAR        traceType[ITS_PATH_MAX];
    ITS_CHAR        traceOutput[ITS_PATH_MAX];
}
LKSCTPGeneralCfg;

/*****************************************************************************
 *
 * Association Database Block
 *
 *****************************************************************************/
typedef struct
{
    ITS_USHORT     localPort;          /* source port */
    SOCK_AddrStore remote;             /* remote address */
    sctp_assoc_t   assocId;            /* Assocation Id */
}
LKSCTP_AssocDb;

/*****************************************************************************
 *
 * hash table contents.
 *
 *****************************************************************************/
typedef struct _SCTP_HE
{
    struct _SCTP_HE     *next;
    LKSCTP_AssocDb      *assocDb;
}
SCTP_HashEntry;

/*****************************************************************************
 *
 * Manager structure
 *
 *****************************************************************************/
typedef struct
{
    TQUEUETRAN_Manager  *queue;
    ITS_MUTEX           gate;
    ITS_USHORT          localPort;     /* source port */
    HASH_Table          assocDb;   
}
LKSCTP_Manager;

void LKSCTP_Console(DBC_Server *dbc, const char *cmdLine);

/*****************************************************************************
 *
 * These two constants are defined for socket-level recv and send timeouts.
 * Depending on performance change these values.
 * The values are in seconds.
 *
 *****************************************************************************/
#define RCV_NON_BLOCKING_TIMEOUT_VAL 5
#define SND_NON_BLOCKING_TIMEOUT_VAL 2

/*****************************************************************************
 *
 * These two IOCTLs are used for the above two timeouts.
 *
 *****************************************************************************/
#define IOCTL_SET_RCV_NON_BLOCKING_TIMEOUT 0x0021
#define IOCTL_SET_SND_NON_BLOCKING_TIMEOUT 0x0022


/*****************************************************************************
 *
 * Transport state NOTE NOTE NOTE
 * This is a exact copy of SCTP_STATE in <its_sctp_impl.h>
 * and should alway reflect the same!
 *
 *****************************************************************************/
typedef enum
{
    ITS_SCTP_CLOSED,
    ITS_SCTP_COOKIE_WAIT,
    ITS_SCTP_COOKIE_SENT,    /* This is COOKIE_ECHOED */
    ITS_SCTP_ESTABLISHED,
    ITS_SCTP_SHUTDOWN_PENDING,
    ITS_SCTP_SHUTDOWN_SENT,
    ITS_SCTP_SHUTDOWN_RECEIVED,
    ITS_SCTP_SHUTDOWN_ACK_SENT
}
ITS_SCTP_STATE;

#endif /* ITS_LKSCTP_H */

