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
 *  ID: $Id: its_tandem.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
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
 * LOG: Revision 8.5  2005/03/21 13:51:06  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/07 15:27:42  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:44  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:00  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:14  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:56  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  2000/03/18 21:03:35  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 1.1  2000/03/01 15:44:16  mmiers
 * LOG:
 * LOG:
 * LOG: Add Tandem files.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 18:13:01  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_PLATFORM_H)
#define ITS_PLATFORM_H

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * mutex type (broken)
 */
typedef int ITS_MUTEX;

/*
 * IPC mutex (also broken)
 */
typedef int ITS_IPC_MUTEX;

/*
 * IPC SEMAPHORE (doesn't exist)
 */
typedef int ITS_IPC_SEMAPHORE;

/*
 * CONDVAR (no such beast here)
 */
typedef int ITS_CONDVAR;

/*
 * THREAD_FUNC (guess what ...)
 */
typedef void (*ITS_THREAD_FUNC)(void *);

#define THREAD_RET_TYPE     void
#define THREAD_NORMAL_EXIT

/*
 * THREAD (this doesn't exist either)
 */
typedef struct
{
    int             stackSize;
    ITS_THREAD_FUNC threadFunc;
    void            *threadArg;
    ITS_BOOLEAN     runnable;
    ITS_BOOLEAN     constructed;
}
ITS_ThreadPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ITS_ThreadPart      thread;
}
ITS_THREAD;

/*
 * SOCKET (and so it goes ...)
 */
typedef int ITS_SOCKET;

/*
 * Tandem lacks this...
 */
#define __BIG_ENDIAN    1
#define __LITTLE_ENDIAN 2

#if defined(TANDEM)
#define __BYTE_ORDER __BIG_ENDIAN
#else
#error "Byte order not defined"
#endif

/*
 * and this
 */
typedef void *      ITS_DLSYM_HANDLE;
typedef void *      ITS_DLSYM;

#if defined(__cplusplus)
}
#endif

#endif /* ITS_PLATFORM_H */
