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
 *  ID: $Id: test6.cpp,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:52:33  cvsadmin
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
 * LOG: Revision 3.2  2001/03/06 22:24:37  mmiers
 * LOG: Convert to SUPPORT only
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:25  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/04/25 16:46:43  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:34  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.9  1999/12/02 21:20:32  labuser
 * LOG:
 * LOG:
 * LOG: Update test6 to latest environ
 * LOG:
 * LOG: Revision 1.8  1998/11/09 22:01:58  rsonak
 * LOG: Update for successful HP build.
 * LOG:
 * LOG: Revision 1.7  1998/09/23 22:04:31  jrao
 * LOG: Updates from HPUX.
 * LOG:
 * LOG: Revision 1.6  1998/09/22 23:56:33  jrao
 * LOG: Changes made to accomodate HPUX code
 * LOG:
 * LOG: Revision 1.5  1998/06/09 16:03:54  mmiers
 * LOG: More intelligent test.
 * LOG:
 * LOG: Revision 1.4  1998/05/29 00:32:59  mmiers
 * LOG: More documentation and bug fixes.
 * LOG:
 * LOG: Revision 1.3  1998/05/28 17:28:44  mmiers
 * LOG: More documenation.  Split the thread implementation into basic threads
 * LOG: and thread pools.
 * LOG:
 * LOG: Revision 1.2  1998/04/19 02:42:52  mmiers
 * LOG: Pretty close to having the basic worker architecture for the HLR
 * LOG: done.
 * LOG:
 * LOG: Revision 1.1  1998/04/15 00:07:18  mmiers
 * LOG: Tests and bug fixes for infrastructure.
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
#include <its_thread.h>
#include <its_timers.h>
#include <its_statics.cpp>

#if defined(WIN32)
#define SLEEP(x)    Sleep(x * 1000);
#else
#define SLEEP(x)    sleep(x)
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

/*
 * thread test
 */

class WorkerThread : public ITS_Thread
{
public:
    WorkerThread(ITS_THREAD_FUNC thread, int which);
    ~WorkerThread();

#if defined(WIN32)
    static unsigned __stdcall Worker(void *arg);
#else
    static void * Worker(void *arg);
#endif
    int which;
};


WorkerThread::WorkerThread(ITS_THREAD_FUNC func, int w)
    : ITS_Thread(0, func), which(w)
{
}

WorkerThread::~WorkerThread()
{
}

#if defined(WIN32)
unsigned __stdcall
#else
void *
#endif
WorkerThread::Worker(void *arg)
{
    WorkerThread *work = (WorkerThread *)arg;

#if defined(WIN32)
    for (int i = 0; i < 500; i++)
    {
        for (volatile int j = 0; j < 1000; j++)
            ;
        Sleep(100);
    }
#else
    for (int i = 0; i < 5; i++)
    {
        for (volatile int j = 0; j < 100; j++)
            ;
        TIMERS_Sleep(1);
    }
#endif

    if (!(work->which % 100))
    {
        time_t tm;
        
        time(&tm);
        printf("Thread %d exiting: %s\n", work->which, ctime(&tm));
    }

    delete work;
    WorkerThread::Exit(NULL);

    return (0);
}

int
main(int argc, char **argv)
{
    time_t tm;

    time(&tm);
    printf("Start time: %s\n", ctime(&tm));

    for (int i = 0; i < 500; i++)
    {
            WorkerThread *work = new WorkerThread(WorkerThread::Worker, i);

            if (work->Enter((void *)work) != ITS_SUCCESS)
            {
                printf("Failed to create thread: count %d\n", i);
                fflush(stdout);
            }
    }

    printf("End time: %s\n", ctime(&tm));

#if !defined(HPUX)
    ITS_Thread::Exit(0);
#else
    TIMERS_Sleep(20);
#endif

    return (0);
}
