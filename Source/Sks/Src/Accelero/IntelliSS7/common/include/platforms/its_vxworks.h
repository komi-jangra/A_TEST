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
 * LOG: Revision 4.2  2001/08/16 19:54:16  lbana
 * LOG: variables for big endian and little endians are defined
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:14  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.4  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 1.3  2001/02/12 21:47:28  lbana
 * LOG: ident macro is added and indentation.
 * LOG:
 * LOG: Revision 1.2  2001/02/12 20:50:25  lbana
 * LOG: added log info
 * LOG:
 *
 ****************************************************************************/
#if !defined(ITS_PLATFORM_H)
#define ITS_PLATFORM_H

#include "VxWorks.h"
#include "taskLib.h"
#include "stdio.h"
#include "semLib.h"
#include "signal.h"
#include "unistd.h"
#include <string.h>
#include <symLib.h>

#ident "$Id: its_vxworks.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $"

#define TIME_FOREVER          WAIT_FOREVER
#define MSEC_PER_SEC          1000
#define VXWORKS_STACK_SIZE    20480
#define THREAD_USE_ACTIVATE   ITS_TRUE
#define THREAD_NUSE_ACTIVATE  ITS_FALSE

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 *   FIFO
 */
/* Do not use FIFO , it isto remove compiler errors */
typedef int ITS_FIFO;

/*
 *  MUTEX 
 */
typedef  SEM_ID ITS_MUTEX;

/*
 * IPC MUTEX
 */
#define RTOS_PLATFORM   /* IPC doesn't exist here */

/*
 *  CONDITION VARIABLES
 */
typedef struct
{
    ITS_UINT        waiters;        /* number of waiting threads */
    ITS_MUTEX       waiterLock;     /* guard for above */
    SEM_ID          cv_sema;        /* wait queue */
    SEM_ID          waitersDone;    /* wait for all wakeups to finish */
    ITS_BOOLEAN     wasBroadcast;   /* wakeup was broadcast */
}
ITS_CONDVAR;

/*
 *  IPC SEMAPHORE
 */
typedef SEM_ID ITS_IPC_SEMAPHORE;

/* 
 *  SOCKETS
 */
typedef int ITS_SOCKET;

/* 
 *  THREADS
 */
typedef int (*ITS_THREAD_FUNC)(void *);

typedef struct
{   
    ITS_INT	    tID;
    int             stackSize;
    ITS_BOOLEAN	    runnable;
    ITS_BOOLEAN     constructed;
    ITS_THREAD_FUNC threadFunc;
    void*           threadArgs[10];
    ITS_BOOLEAN     tVarState;
}
ITS_ThreadPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ITS_ThreadPart      thread;
}
ITS_THREAD;

#define THREAD_RET_TYPE     int 
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

static __inline__ char* strdup(const char* source)
{
        char* temp;

        temp = (char *)malloc(strlen(source) + 1);

        /* Think about it */
        if(temp == NULL)
        {
            return NULL;
        }

        strcpy(temp, source);

        return temp;
}

#if defined(__cplusplus)
}
#endif

/* 
   VxWorks Symbol TBL id Since all symbols are added 
   to the global symbol table unlike linux/solaris ?
*/
typedef SYMTAB_ID ITS_DLSYM_HANDLE;

typedef void*     ITS_DLSYM;

#if defined(_BYTE_ORDER)
#define __LITTLE_ENDIAN  _LITTLE_ENDIAN
#define __BYTE_ORDER     _BYTE_ORDER
#else
#error "Define byte order for ITS"
#endif

#endif
