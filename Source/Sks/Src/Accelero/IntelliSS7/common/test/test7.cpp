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
 *  ID: $Id: test7.cpp,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:33  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:15  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:26  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:34  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:07  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.3  2001/03/06 22:24:37  mmiers
 * LOG: Convert to SUPPORT only
 * LOG:
 * LOG: Revision 3.2  2001/01/31 23:40:53  mmiers
 * LOG: Work around thread data duplication.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:26  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/04/25 16:46:43  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:35  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1998/11/18 18:07:13  mmiers
 * LOG: Update project information.
 * LOG:
 * LOG: Revision 1.4  1998/05/29 00:32:59  mmiers
 * LOG: More documentation and bug fixes.
 * LOG:
 * LOG: Revision 1.3  1998/04/19 02:42:52  mmiers
 * LOG: Pretty close to having the basic worker architecture for the HLR
 * LOG: done.
 * LOG:
 * LOG: Revision 1.2  1998/04/17 21:22:30  mmiers
 * LOG: Thread pools are working.
 * LOG:
 * LOG: Revision 1.1  1998/04/17 17:43:52  mmiers
 * LOG: Add thread pool test.
 * LOG:
 *
 ****************************************************************************/

/*
 * list handling routines
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#if defined(unix)
#include <unistd.h>
#include <signal.h>
#endif

#include <exception>

#include <its++.h>
#include <its_thread_pool.h>
#include <its_timers.h>
#include <its_statics.cpp>

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

/*
 * thread pool test
 */
class WorkerThread : public ITS_ThreadPoolThread
{
public:
    WorkerThread(int stackSize)
        : ITS_ThreadPoolThread(stackSize)
    {
    }
    ~WorkerThread()
    {
    }

    int which;
};

class ThreadPool : public ITS_ThreadPool
{
public:
    ThreadPool()
        : ITS_ThreadPool(), count(0)
    {
    }

    virtual ITS_ThreadPoolThread* CreatePoolThread(int stackSize)
    {
        WorkerThread* work = new WorkerThread(stackSize);

        work->which = count;
        count++;

        return (ITS_ThreadPoolThread *)work;
    }

private:
    int count;
};

void
WorkFunc1(ITS_ThreadPoolThread *thr, void *arg)
{
    printf("Func 1: thr %d\n", ((WorkerThread *)thr)->which);
    fflush(stdout);

    TIMERS_Sleep(5);
}

void
WorkFunc2(ITS_ThreadPoolThread *thr, void *arg)
{
    printf("Func 2: thr %d\n", ((WorkerThread *)thr)->which);
    fflush(stdout);

    TIMERS_Sleep(2);
}

ThreadPool* pool = NULL;

int
main(int argc, char **argv)
{
    ITS_GlobalStart(0);

    try
    {
        pool = new ThreadPool();

        pool->CreatePool(100, 0);
    }
    catch (exception& ex)
    {
        printf("Caught exception creating pool\n");

        exit(0);
    }

    for (int i = 0; i < 300; i++)
    {
        if (i & 1)
        {
            if (pool->Dispatch(WorkFunc1, NULL) != ITS_SUCCESS)
            {
                printf("Out of dispatch threads: Func1\n");
                TIMERS_Sleep(1);
            }
        }
        else
        {
            if (pool->Dispatch(WorkFunc2, NULL) != ITS_SUCCESS)
            {
                printf("Out of dispatch threads: Func2\n");
                TIMERS_Sleep(1);
            }
        }
    }

    delete pool;

    ITS_ThreadPool::WaitForDeletionComplete();

    ITS_GlobalStop();

    return (0);
}
