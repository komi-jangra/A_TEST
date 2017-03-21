/****************************************************************************
 *                                                                          *
 *     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: tcap_clientimpl.h,v 1.1.1.1 2007-10-08 11:12:27 bsccs2 Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:25:04  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2006/12/22 13:32:02  cvsadmin
 * Initialising sources in CVS
 *
 * Revision 1.2  2003/10/17 09:11:30  ssingh
 * compilation warning removal.
 *
 * Revision 1.1  2003/10/07 12:45:05  sswami
 * TCAP multiple application binding client implementation
 *
 *
 ****************************************************************************/

#ifndef CLIENTIMPL_H
#define CLIENTIMPL_H

#include <its.h>
#include <its_hmi.h>
#include <its_sockets.h>
#include <stdlib.h>

#if defined(CCITT)
#include <itu/tcap.h>
#elif defined(ANSI)
#include <ansi/tcap.h>
#endif

/*
 * clientimpl.h
 * This file contains the internal usage functions for client layer
 */

/* Server Event types */
#define CL_SRC_SERVER 0x11
#define CL_APP_ISUP_SRC   0x01
#define CL_APP_TCAP_SRC   0x02


/* Event types between client and server */
#define CL_TCAP_REGISTER_EVENT   0x02
#define CL_TCAP_DEREGISTER_EVENT 0x04

/* Request Events */
#define CL_TCAP_ALLOC_DID_REQ     0x08 
#define CL_TCAP_ALLOC_DID_RESP     0xF7 


/*Global data*/
extern ITS_SocketInfo * CL_SockInfo;

extern ITS_USHORT did;


/*
 * Creates Client socket 
 */
int CL_CreateClientSocket();

/*
 * Send the event to Server
 */
int CL_WriteEvent(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_WriteEventIsup(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_WriteEventMtp3(ITS_HANDLE handle, ITS_EVENT *evt);


int CL_WriteEventTcap(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_WriteEventSccp(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_WriteEventSCM(ITS_HANDLE handle, ITS_EVENT *evt);

/*
 * Read the event from Server
 */
int CL_ReadEvent(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_ReadEventMtp3(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_ReadEventIsup(ITS_HANDLE handle, ITS_EVENT *evt);

int CL_ReadEventSccp(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_ReadEventTcap(ITS_HANDLE handle, ITS_EVENT *evt);
/*
 * This function handles the client events
 */
int CL_HandleClientEvent(ITS_EVENT *evt);




#endif 
