/****************************************************************************
 *                                                                          *
 * Copyright 1997-1999 IntelliNet Technologies, Inc. All Rights Reserved.   *
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:09  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:00  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:57  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:51:06  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:44  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/11/08 20:47:38  mmiers
 * LOG: A better performing mem pool implementation.
 * LOG:
 * LOG: Revision 5.2  2001/11/07 22:53:58  mmiers
 * LOG: Add IPC mutex.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:00  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:14  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.4  2001/02/14 20:44:54  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.3  2001/02/08 22:43:05  mmiers
 * LOG: Add dynamic symbol resolution.
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:56  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.3  2000/08/09 00:08:21  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 1.2  2000/04/24 22:20:04  mmiers
 * LOG:
 * LOG:
 * LOG: Add condition variable type.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 18:17:05  mmiers
 * LOG: Platform cleanup
 * LOG:
 * LOG: Revision 1.1  1999/12/16 18:16:17  mmiers
 * LOG: Platform cleanup.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 18:14:56  mmiers
 * LOG: Platform cleanup
 * LOG:
 * LOG: Revision 1.1  1999/12/16 18:13:03  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_PLATFORM_H)
#define ITS_PLATFORM_H

#ident "$Id: its_win.h,v 1.1.1.1 2007-10-08 11:11:39 bsccs2 Exp $"

#include <windows.h>
#include <process.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * FIFO
 */

/*
 * this platform has reentrant fifos
 */
typedef struct
{
    HANDLE          handle;
    int             mode;
    ITS_BOOLEAN     isPipe;
    ITS_BOOLEAN     isConnected;
}
ITS_FIFO;

/*
 * MUTEX
 */
typedef CRITICAL_SECTION    ITS_MUTEX;

/*
 * IPC MUTEX
 */
typedef HANDLE    ITS_IPC_MUTEX;

/*
 * SEMAPHORE
 */
typedef HANDLE    ITS_IPC_SEMAPHORE;

/*
 * CONDVAR
 */
typedef HANDLE    ITS_CONDVAR;

/*
 * SOCKET
 */
typedef SOCKET    ITS_SOCKET;

/*
 * THREAD
 */
typedef unsigned (__stdcall *ITS_THREAD_FUNC)(void *);

typedef struct
{
    HANDLE            thread;
    int               stackSize;
    ITS_BOOLEAN       runnable;
    ITS_BOOLEAN       constructed;
    ITS_THREAD_FUNC   threadFunc;
    void              *threadArg;
}
ITS_ThreadPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ITS_ThreadPart      thread;
}
ITS_THREAD;

#define THREAD_RET_TYPE unsigned __stdcall
#define THREAD_NORMAL_EXIT                                              \
    do                                                                  \
    {                                                                   \
        MEMPOOL_Manager *m;                                             \
        if ((m = (MEMPOOL_Manager *)THREAD_GetLocalStorage()) != NULL)  \
        {                                                               \
            MEMPOOL_DestroyPool(m);                                     \
            THREAD_SetLocalStorage(NULL);                               \
        }                                                               \
        return (0);                                                     \
    }                                                                   \
    while (0)

#if defined(__cplusplus)
}
#endif

/*
 * Can't believe this isn't already defined
 */
#if !defined(__LITTLE_ENDIAN)
#define __LITTLE_ENDIAN 1
#endif
#if !defined(__BIG_ENDIAN)
#define __BIG_ENDIAN    2
#endif
#if !defined(__BYTE_ORDER)
#define __BYTE_ORDER    __LITTLE_ENDIAN
#endif

/*
 * DLL types
 */
typedef HINSTANCE   ITS_DLSYM_HANDLE;
typedef void *      ITS_DLSYM;


#endif /* ITS_PLATFORM_H */
