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
 *  ID: $Id: test2.cpp,v 1.1.1.1 2007-10-08 11:11:59 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:33  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:14  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:25  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:27  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
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
 * LOG: Revision 3.2  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:18  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/06/02 15:51:36  mmiers
 * LOG:
 * LOG:
 * LOG: More sockets testing.
 * LOG:
 * LOG: Revision 2.2  2000/05/23 23:49:15  mmiers
 * LOG: Use localhost.
 * LOG:
 * LOG: Revision 2.1  2000/04/25 16:46:42  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:31  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.7  1998/11/18 18:07:10  mmiers
 * LOG: Update project information.
 * LOG:
 * LOG: Revision 1.6  1998/09/23 22:04:30  jrao
 * LOG: Updates from HPUX.
 * LOG:
 * LOG: Revision 1.5  1998/05/29 03:31:38  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.4  1998/04/13 21:16:32  mmiers
 * LOG: Resolving some cross-platform issues.
 * LOG:
 * LOG: Revision 1.3  1998/04/13 20:41:11  mmiers
 * LOG: Finish tracking down the bugs for Windows sockets.  NOTE:
 * LOG: You MUST call WSAStartup for ALL sockets created --
 * LOG: INCLUDING the socket that is the result of accept().
 * LOG:
 * LOG: Revision 1.2  1998/04/10 15:40:49  mmiers
 * LOG: More debug on the infrastructure.
 * LOG:
 * LOG: Revision 1.1  1998/04/09 23:43:45  mmiers
 * LOG: Debugging threads and sockets.
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

#if defined(unix)
#include <signal.h>
#endif

#include <exception>

#include <its++.h>
#include <its_thread.h>
#include <its_sockets.h>
#include <its_statics.cpp>

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

/*
 * server test
 */
class ITS_Server
{
public:
    ITS_Server();
    ~ITS_Server();

    void HandleConnections();

private:
    ITS_ServerSocket *ssocket;
};

class WorkerThread : public ITS_Thread
{
public:
    WorkerThread(ITS_Socket *connection, ITS_THREAD_FUNC thread);
    ~WorkerThread();

    static THREAD_RET_TYPE Worker(void *arg);

    ITS_Socket *wsocket;
};

ITS_Server::ITS_Server()
{
    ssocket = NULL;
    ssocket = new ITS_ServerSocket(INET_DOMAIN, "127.0.0.1", 30000);
}

ITS_Server::~ITS_Server()
{
    if (ssocket)
    {
        delete ssocket;
    }
}

void
ITS_Server::HandleConnections()
{
    for (;;)
    {
        ITS_Socket *connection;

        printf("Accepting connections...\n");
        fflush(stdout);

        int ret;
        if ((ret = ssocket->Accept(&connection)) == ITS_SUCCESS)
        {
            printf("Starting worker...\n");
            fflush(stdout);

            WorkerThread *work = new WorkerThread(connection,
                                                  WorkerThread::Worker);

            assert(work->Enter((void *)work) == ITS_SUCCESS);

            printf("Worker started\n");
            fflush(stdout);
        }
        else
        {
            printf("Couldn't accept connection: %d.\n", ret);
        }
    }
}

WorkerThread::WorkerThread(ITS_Socket *_connection, ITS_THREAD_FUNC func)
    : ITS_Thread(0, func)
{
    wsocket = _connection;
}

WorkerThread::~WorkerThread()
{
    delete wsocket;
}

#if defined(WIN32)
unsigned __stdcall
#else
void *
#endif
WorkerThread::Worker(void *arg)
{
    WorkerThread *worker = (WorkerThread *)arg;

    assert(worker->wsocket != NULL);

    char buf[256];
    int nb;
    while ((nb = worker->wsocket->Read(buf, 1)) >= 0)
    {
        /* end of file -- client gone */
        if (nb == 0)
        {
            printf("Worker exiting on EOF\n");
            fflush(stdout);

            delete worker;
            WorkerThread::Exit(NULL);

            // not reached, I hope
            break;
        }

        for (int i = 0; i <  nb; i++)
        {
            putchar(buf[i]);
        }
    }

    printf("Worker thread exiting on error: %d\n", nb);
    fflush(stdout);

    delete worker;
    WorkerThread::Exit(NULL);

    // not reached, I hope
    return (0);
}

ITS_Server *server = NULL;

#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
{
    if (server)
    {
        delete server;
    }

    exit(0);

    return 1;
}
#else
static void exitHandler(int sig)
{
    if (server)
    {
        delete server;
    }


    exit(0);
}
#endif

int
main(int argc, char **argv)
{
#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    if (ITS_GlobalStart(0) != ITS_SUCCESS)
    {
        printf("failed to start\n");

        return (0);
    }

    try
    {
        server = new ITS_Server;
    }
    catch(exception& ex)
    {
        if (server)
        {
            delete server;
        }

        printf("Failed to create server socket\n");

        return (0);
    }

    server->HandleConnections();

    ITS_GlobalStop();

    return (0);
}
