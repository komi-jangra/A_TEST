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
 *  ID: $Id: test22.cpp,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
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
 * LOG: Revision 3.2  2001/03/06 22:24:37  mmiers
 * LOG: Convert to SUPPORT only
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:20  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.10  2000/06/02 15:51:36  mmiers
 * LOG:
 * LOG:
 * LOG: More sockets testing.
 * LOG:
 * LOG: Revision 1.9  2000/05/25 23:26:41  mmiers
 * LOG:
 * LOG:
 * LOG: Today's SCTP update.
 * LOG:
 * LOG: Revision 1.8  2000/05/25 14:09:39  mmiers
 * LOG:
 * LOG:
 * LOG: Allow room for port numbers
 * LOG:
 * LOG: Revision 1.7  2000/05/24 22:01:13  mmiers
 * LOG:
 * LOG:
 * LOG: More fixes for raw sockets.  Now 3 platforms down.
 * LOG:
 * LOG: Revision 1.6  2000/05/24 19:46:45  mmiers
 * LOG:
 * LOG:
 * LOG: Work around an NT limitation.
 * LOG:
 * LOG: Revision 1.5  2000/05/24 00:29:56  mmiers
 * LOG:
 * LOG:
 * LOG: Cross platform working.
 * LOG:
 * LOG: Revision 1.4  2000/05/24 00:24:59  mmiers
 * LOG:
 * LOG: Get this working on UNIX.  NT apparently automatically prepends
 * LOG: an IP header.  Unices apparently don't.
 * LOG:
 * LOG: Revision 1.3  2000/05/23 23:05:34  mmiers
 * LOG:
 * LOG:
 * LOG: Try to generate ICMP message.
 * LOG:
 * LOG: Revision 1.2  2000/05/23 19:35:10  mmiers
 * LOG:
 * LOG:
 * LOG: Fix up for testing.
 * LOG:
 * LOG: Revision 1.1  2000/05/23 18:48:03  mmiers
 * LOG:
 * LOG:
 * LOG: Raw tests.
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
using namespace std;
#endif

void
PrintHeader(SOCK_IPv4Header *hdr)
{
    printf(" IHL:      %01x\n", hdr->hdrLen);
    printf(" Version:  %01x\n", hdr->version);
    printf(" TOS:      %02x\n", hdr->typeOfService);
    printf(" TotalLen: %04x\n", ITS_Socket::NToHS(hdr->totalLen));
    printf(" ID:       %04x\n", ITS_Socket::NToHS(hdr->id));
    printf(" FragOff:  %04x\n", ITS_Socket::NToHS(hdr->fragOffset));
    printf(" TTL:      %02x\n", hdr->timeToLive);
    printf(" Protocol: %02x\n", hdr->protocol);
    printf(" Chksum:   %04x\n", ITS_Socket::NToHS(hdr->cksum));
    printf(" SrcAddr:  %08x\n", ITS_Socket::NToHL(hdr->saddr));
    printf(" DstAddr:  %08x\n", ITS_Socket::NToHL(hdr->daddr));
}

/*
 * raw test
 */
void
RawIO(ITS_Socket* sock)
{
    char buf[10000], *ptr;
    int nb;
    void *addr;
    int len;

    if (ITS_Socket::CreateAddr(INET_DOMAIN, "127.0.0.1", 25000,
                               &addr, &len) != ITS_SUCCESS)
    {
        return;
    }

    while ((nb = sock->Recv(buf, 10000, addr, &len)) >= 0)
    {
        int i;

        /* end of file -- client gone */
        if (nb == 0)
        {
            printf("Worker exiting on EOF\n");
            fflush(stdout);

            // not reached, I hope
            break;
        }

        printf("Received %d bytes from: ", nb);
        for (i = 0; i < len; i++)
        {
            printf("%02x ", ((ITS_OCTET *)addr)[i]);
        }
        printf("\n");

        printf("Received header:\n");
        PrintHeader((SOCK_IPv4Header *)buf);

        printf("Received text: ");
        ptr = buf + sizeof(SOCK_IPv4Header) + 4;
        nb -= sizeof(SOCK_IPv4Header) + 4;
        for (i = 0; i <  nb && i < 20; i++)
        {
            putchar(ptr[i]);
        }
    }

    printf("Loop terminated: code %d\n", nb);

    free(addr);
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
    ITS_Socket* sock = NULL;
#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    try
    {
#if 0
        sock = new ITS_RawSocket(INET_DOMAIN, "127.0.0.1", 25000,
                                 IPPROTO_SCTP, false);
#else
        sock = new ITS_RawSocket(INET_DOMAIN, "192.168.1.13", 25000,
                                 IPPROTO_SCTP, false);
#endif
    }
    catch(exception& ex)
    {
        if (sock)
        {
            delete sock;
        }

        printf("Failed to create server socket\n");
    }

    printf("Enter loop:\n");
    RawIO(sock);

    delete sock;

    return (0);
}
