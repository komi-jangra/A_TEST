/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: clientimpl.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:23:46  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:48:43  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:13:05  cvsadmin
 * BSC project
 *
 * Revision 9.1  2005/03/23 12:52:01  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.2  2005/03/23 07:26:06  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 1.1.2.6.6.1.10.1  2004/12/15 06:04:37  mmanikandan
 * Windows Build Support.
 *
 * Revision 1.1.2.6.6.1  2004/01/05 09:48:02  sjaddu
 * Merged code from tcs isup branch.
 *
 * Revision 1.1.2.6.2.5  2003/10/31 05:57:45  sjaddu
 * Final commit.
 *
 * Revision 1.1.2.6.2.4  2003/10/29 12:32:06  akumar
 * CL_CloseConnection API added.
 *
 * Revision 1.1.2.6.2.3  2003/08/29 09:54:21  akumar
 * Modifications for Deregistration APi.
 *
 * Revision 1.1.2.6.2.2  2003/08/28 15:32:34  sjaddu
 * Functions restructured ...
 *
 * Revision 1.1.2.6.2.1  2003/08/26 12:47:48  sjaddu
 * Redundancy changes done.
 *
 * Revision 1.1.2.6  2003/07/25 06:07:25  sjaddu
 * Some sock info cahnge
 *
 * Revision 1.1.2.5  2003/06/30 05:02:30  sjaddu
 * Removed #include clietapi.h
 *
 * Revision 1.1.2.4  2003/06/25 09:03:47  sjaddu
 * Moved some macors here.
 *
 * Revision 1.1.2.3  2003/06/20 11:22:21  sjaddu
 * Some hash defines moved api.h
 *
 * Revision 1.1.2.2  2003/06/18 08:27:23  tsanthosh
 * Added Request & Response functinality.
 *
 * Revision 1.1.2.1  2003/06/05 05:21:45  sjaddu
 * Added first revision of files for ISUP client.
 *
 *
 ****************************************************************************/

#ifndef CLIENTIMPL_H
#define CLIENTIMPL_H

#include <its.h>
#include <its_sockets.h>
#include <stdlib.h>
#include <string.h>
#include <its_hmi.h>
#include <its_tq_trans.h>
#include <clientapi.h>

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

/*
 * clientimpl.h
 * This file contains the internal usage functions for client layer
 */

/* Server Event types */
#define CL_SRC_SERVER     0x11
#define CL_APP_ISUP_SRC   0x01
#define CL_APP_TCAP_SRC   0x02


/* Event types between client and server */
#define CL_ISUP_REGISTER_EVENT   0x01 
#define CL_TCAP_REGISTER_EVENT   0x02

#define CL_ISUP_DEREGISTER_EVENT 0x03 
#define CL_TCAP_DEREGISTER_EVENT 0x04


/* Request Events */
#define CL_ISUP_RESERVE_CIC_REQ     0x05 
#define CL_ISUP_UNRESERVE_CIC_REQ   0x09 

/* For Backup Server */
#define CL_ISUP_REGISTER_BACKUP_EVENT   0x0A
#define CL_ISUP_DEREGISTER_BACKUP_EVENT 0x0B 

#define CL_MAX_ROUTE_HDRS  100  /*This is for each application*/
#define CL_IP_ADDR_LEN 15


typedef struct
{
    ITS_THREAD          info;
    ITS_THREAD_FUNC     func;
    ITS_BOOLEAN         isRunning;
}
CL_THR_INFO;


typedef struct
{
    MTP3_HEADER  mtp3[CL_MAX_ROUTE_HDRS];
    int count;
}
CL_REG_INFO;


typedef struct
{
    ITS_SocketInfo      *sockInfo;
    CL_THR_INFO         thrInfo;
    ITS_MUTEX           readLock;
    ITS_MUTEX           writeLock;
    ITS_BOOLEAN         isUp;
    ITS_UINT            port;
    char                ipAddr[CL_IP_ADDR_LEN];
    ITS_BOOLEAN         isInitialized;
}
CL_CONNECTION_INFO;

typedef struct
{
    EMLIST_Manager       *taskQue;
    ITS_UINT             noCurrEnts;
}
CL_TRANS_QUE;

typedef struct
{
    CL_CONNECTION_INFO    primaryInfo;
    CL_CONNECTION_INFO    backupInfo;
    CL_REG_INFO           regInfo;
    CL_TRANS_QUE          taskTrans;
}
CL_CONNECTION;

/*
 * Send the event to Server
 */
CLDLLAPI int 
CL_WriteEvent(ITS_HANDLE handle, ITS_EVENT *evt);

/*
 * Read the event from Server
 */
CLDLLAPI int 
CL_ReadEvent(ITS_HANDLE handle, ITS_EVENT *evt);

/*
 * This function handles the client events
 */
CLDLLAPI int 
CL_HandleClientEvent(ITS_EVENT *evt);

CLDLLAPI int 
CL_SendEvent(ITS_HANDLE handle, ITS_EVENT *evt);

CLDLLAPI int
CL_ReRegister(CL_CONNECTION_INFO *info, CL_CONNECTION_TYPE type,
              MTP3_HEADER *hdr, int count);

CLDLLAPI int
CL_Connect(CL_CONNECTION_INFO *info);

CLDLLAPI int
CL_CloseCon(ITS_HANDLE handle);

CLDLLAPI int
CL_PutEventOnTaskQue(CL_TRANS_QUE *taskTran, ITS_EVENT *evt);

CLDLLAPI int
CL_GetEventFromTaskQue(CL_TRANS_QUE *taskTran, ITS_EVENT *evt);

#endif
