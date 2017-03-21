/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: its_route_rwlock.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:50:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.2.2.1  2003/03/25 19:28:17  randresol
 * LOG: Increase the size of MAX_THREAD
 * LOG:
 * LOG: Revision 1.2  2002/12/17 20:45:44  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 1.1  2002/11/09 21:18:10  randresol
 * LOG: Add definition for Route Reader/Writer Lock in DSM
 * LOG:
 * LOG: 
 * LOG:
 *
 ****************************************************************************/
#ifndef ITS_ROUTE_RWLOCK_H
#define ITS_ROUTE_RWLOCK_H


#include <its_tq_trans.h>

#define MAX_NODES    4     /* max DSM nodes */
#define MAX_THREADS  37    /* max threads/node using a lock */

typedef struct
{
    ITS_BOOLEAN  thisInstanceIsReading[MAX_NODES][MAX_THREADS];
    ITS_BOOLEAN  somethingIsWriting;
    ITS_UINT     writersWaitingForLock;
}
ROUTE_RWLock;


#if defined(__cplusplus)
extern "C"
{
#endif

ITSDLLAPI ROUTE_RWLock *ROUTE_RWLockCreate();
ITSDLLAPI int ROUTE_RWLockDelete(ROUTE_RWLock *routeLock);
ITSDLLAPI int ROUTE_LockForRead(ROUTE_RWLock *routeLock);
ITSDLLAPI int ROUTE_LockForWrite(ROUTE_RWLock *routeLock);
ITSDLLAPI int ROUTE_UnlockRead(ROUTE_RWLock *routeLock, 
                              const TQUEUETRAN_Manager *tq);
ITSDLLAPI int ROUTE_UnlockWrite(ROUTE_RWLock *routeLock);

ITSDLLAPI extern ROUTE_RWLock *routeRWLock;



#if defined(__cplusplus)
}
#endif

#endif /* ITS_ROUTE_RWLOCK_H */
