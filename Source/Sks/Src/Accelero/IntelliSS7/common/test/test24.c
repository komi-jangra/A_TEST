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
 *  ID: $Id: test24.c,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:52:28  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:07  mmiers
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
 * LOG: Revision 3.2  2001/03/13 02:26:22  mmiers
 * LOG: UNIX build is a heck of a lot easier to set up.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:21  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/06/21 22:20:11  mmiers
 * LOG:
 * LOG:
 * LOG: Linux non-portability issue.
 * LOG:
 * LOG: Revision 2.2  2000/06/02 17:19:25  mmiers
 * LOG:
 * LOG:
 * LOG: Socket changes.
 * LOG:
 * LOG: Revision 2.1  2000/06/02 15:51:36  mmiers
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
#include <errno.h>

#if defined(unix)
#include <signal.h>
#endif

#include <its.h>
#include <its_thread.h>
#include <its_sockets.h>
#include <its_timers.h>

static ITS_SocketInfo *sock;
static ITS_THREAD thread;

static THREAD_RET_TYPE
accFunc(void *arg)
{
    ITS_SocketInfo *sock = (ITS_SocketInfo *)arg;
    ITS_SocketInfo *accSock;
    char buf[ITS_PATH_MAX];

    printf("Accepting...\n");
    fflush(stdout);

    SOCK_ServerAccept(sock, &accSock);

    printf("Accept broken: errno %d\n", errno);
    fflush(stdout);

    SOCK_Read(accSock, buf, ITS_PATH_MAX);

    printf("Read broken: errno %d\n", errno);
    fflush(stdout);

    THREAD_NORMAL_EXIT;
}

#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
{
    exit(0);

    return 1;
}
#else
static void exitHandler(int sig)
{
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

    if (SOCK_ServerOpen(&sock, INET_DOMAIN, "127.0.0.1", 7500) != ITS_SUCCESS)
    {
        abort();
    }

    if (THREAD_CreateThread(&thread, 0, accFunc, (void *)sock,
                            ITS_TRUE) != ITS_SUCCESS)
    {
        abort();
    }

    TIMERS_Sleep(5);

    printf("closing...\n");

    SOCK_Close(sock);

    TIMERS_Sleep(5);

    return (0);
}
