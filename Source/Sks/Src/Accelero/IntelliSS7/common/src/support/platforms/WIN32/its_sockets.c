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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:30  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:52:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.12.3  2004/10/29 06:41:00  dsatish
 * LOG: Fix done for handling multiple connections
 * LOG:
 * LOG: Revision 7.1.12.2  2004/10/12 10:37:12  mmanikandan
 * LOG: Compilation Error.
 * LOG:
 * LOG: Revision 7.1.12.1  2004/10/12 10:10:44  mmanikandan
 * LOG: Deadlock issue is resolved while testing SCTP & M3UA.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/06/19 19:31:15  lbana
 * LOG: Missing SOCK_CreateAddr in SOCK_RawOpen call.
 * LOG:
 * LOG: Revision 6.2  2002/04/12 15:35:40  hdivoux
 * LOG: ITSDLLAPI specifier for class and class record.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2001/12/18 17:41:03  hdivoux
 * LOG: Typo.
 * LOG:
 * LOG: Revision 5.4  2001/12/18 17:37:46  hdivoux
 * LOG: More bug correction.
 * LOG:
 * LOG: Revision 5.3  2001/12/18 16:16:07  hdivoux
 * LOG: Bug correction: do not use errno with Windows socket API.
 * LOG:
 * LOG: Revision 5.2  2001/10/30 22:59:39  ssharma
 * LOG: Typo in GetLocalAddrs().
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.14  2001/03/16 21:42:28  hdivoux
 * LOG: Start update for ASN.1 runtime (unknown elements and tag adjustment).
 * LOG:
 * LOG: Revision 3.13  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.12  2001/02/20 19:00:56  mmiers
 * LOG: Assert removal
 * LOG:
 * LOG: Revision 3.11  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.10  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.9  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.8  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.7  2000/12/21 18:24:07  mmiers
 * LOG: Finish fixing address conversion
 * LOG:
 * LOG: Revision 3.6  2000/11/30 19:37:45  mmiers
 * LOG: Ready to debug.
 * LOG:
 * LOG: Revision 3.5  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.7  2000/10/10 17:10:05  mmiers
 * LOG: Associations work!
 * LOG:
 * LOG: Revision 3.6  2000/10/09 22:40:11  mmiers
 * LOG: Cross platform tweaks.  Looks like I have to test linux to linux.
 * LOG:
 * LOG: Revision 3.5  2000/10/09 22:02:54  mmiers
 * LOG: Correct bugs in addr fetch logic.
 * LOG:
 * LOG: Revision 3.4  2000/10/05 23:05:35  mmiers
 * LOG: New routing scheme.
 * LOG:
 * LOG: Revision 3.3  2000/10/05 00:11:04  mmiers
 * LOG: Merge in the rev13 changes.
 * LOG:
 * LOG: Revision 3.2  2000/09/28 21:49:51  mmiers
 * LOG:
 * LOG: Checkpoint for solaris build.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:53  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.19  2000/07/12 20:00:26  mmiers
 * LOG:
 * LOG: getpeername() size is [in/out].  Docs on UNIX confirm this.
 * LOG:
 * LOG: Revision 1.18  2000/07/08 00:22:24  rsonak
 * LOG:
 * LOG:
 * LOG: Try not to be brain damaged.
 * LOG:
 * LOG: Revision 1.17  2000/07/07 22:27:16  mmiers
 * LOG:
 * LOG:
 * LOG: Rework close logic for sockets.
 * LOG:
 * LOG: Revision 1.16  2000/06/23 19:09:17  rsonak
 * LOG:
 * LOG:
 * LOG: Fix some long standing errors in here.
 * LOG:
 * LOG: Revision 1.15  2000/06/02 15:51:33  mmiers
 * LOG:
 * LOG:
 * LOG: More sockets testing.
 * LOG:
 * LOG: Revision 1.14  2000/05/26 21:34:20  mmiers
 * LOG:
 * LOG:
 * LOG: A few bug fixes, more SCTP work.
 * LOG:
 * LOG: Revision 1.13  2000/05/24 22:13:09  mmiers
 * LOG:
 * LOG:
 * LOG: const modifier
 * LOG:
 * LOG: Revision 1.12  2000/05/24 22:01:11  mmiers
 * LOG:
 * LOG:
 * LOG: More fixes for raw sockets.  Now 3 platforms down.
 * LOG:
 * LOG: Revision 1.11  2000/05/24 19:59:39  mmiers
 * LOG:
 * LOG:
 * LOG: Back this change out.  Special case only the windows code, its
 * LOG: the oddball here.
 * LOG:
 * LOG: Revision 1.10  2000/05/24 19:45:31  mmiers
 * LOG:
 * LOG:
 * LOG: Work around an NT limitation.
 * LOG:
 * LOG: Revision 1.9  2000/05/23 18:53:11  mmiers
 * LOG:
 * LOG:
 * LOG: bind() on RawOpen
 * LOG:
 * LOG: Revision 1.8  2000/05/23 18:47:32  mmiers
 * LOG:
 * LOG:
 * LOG: Socket API update.
 * LOG:
 * LOG: Revision 1.7  2000/05/23 14:39:24  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a few typo bugs.
 * LOG:
 * LOG: Revision 1.6  2000/05/22 23:47:49  mmiers
 * LOG:
 * LOG:
 * LOG: Unix domain datagram sockets.
 * LOG:
 * LOG: Revision 1.5  2000/05/22 16:01:14  mmiers
 * LOG:
 * LOG:
 * LOG: Add RAW socket type.
 * LOG:
 * LOG: Revision 1.4  2000/05/03 21:07:16  mmiers
 * LOG:
 * LOG:
 * LOG: Start adding support for reader/writer locks.
 * LOG: Add SOCK_GetPeerName().
 * LOG:
 * LOG: Revision 1.3  2000/02/10 14:48:12  mmiers
 * LOG:
 * LOG: Add functions for network/host conversion so they're always in our
 * LOG: namespace.
 * LOG:
 * LOG: Revision 1.2  2000/01/05 00:25:01  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks for RUDP.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:21  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:09  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.21  1999/10/14 15:38:39  mmiers
 * LOG:
 * LOG:
 * LOG: Remove memory leaks from socket creation.  Publish
 * LOG: ReConnect/ReAccept APIs.
 * LOG:
 * LOG: Revision 1.20  1999/08/31 21:11:38  labuser
 * LOG:
 * LOG:
 * LOG: Fixes for UNIX domain sockets.
 * LOG:
 * LOG: Revision 1.19  1999/06/24 00:59:14  mmiers
 * LOG:
 * LOG:
 * LOG: Add an IPC type semaphore
 * LOG:
 * LOG: Revision 1.18  1999/03/01 21:26:20  mmiers
 * LOG:
 * LOG:
 * LOG: Make DNS usage a configurable option for sockets.
 * LOG:
 * LOG: Revision 1.17  1998/12/11 21:58:43  rsonak
 * LOG: Fix some socket related bugs.
 * LOG:
 * LOG: Revision 1.16  1998/12/11 21:46:59  rsonak
 * LOG: Fix strange runtime error with resolver library.
 * LOG:
 * LOG: Revision 1.15  1998/11/19 02:18:23  mmiers
 * LOG: Straighten out a few potential bugs.
 * LOG:
 * LOG: Revision 1.14  1998/11/17 14:58:18  mmiers
 * LOG: #include <ctype.h>
 * LOG:
 * LOG: Revision 1.13  1998/11/17 03:31:11  mmiers
 * LOG: Deal with gethostbyaddr() when appropriate.
 * LOG:
 * LOG: Revision 1.12  1998/11/13 17:50:54  mmiers
 * LOG: Add UDP sockets to the collection.
 * LOG:
 * LOG: Revision 1.11  1998/09/28 16:07:27  mmiers
 * LOG: Fix long standing bug in hostname/addr resolution.  Affects all
 * LOG: platforms.
 * LOG:
 * LOG: Revision 1.10  1998/06/02 17:24:47  mmiers
 * LOG: Cleanup for the doc tool.
 * LOG:
 * LOG: Revision 1.9  1998/05/14 20:46:00  mmiers
 * LOG: Remove references to non-associated projects.
 * LOG:
 * LOG: Revision 1.8  1998/04/15 00:07:16  mmiers
 * LOG: Tests and bug fixes for infrastructure.
 * LOG:
 * LOG: Revision 1.7  1998/04/13 20:41:10  mmiers
 * LOG: Finish tracking down the bugs for Windows sockets.  NOTE:
 * LOG: You MUST call WSAStartup for ALL sockets created --
 * LOG: INCLUDING the socket that is the result of accept().
 * LOG:
 * LOG: Revision 1.6  1998/04/09 23:43:43  mmiers
 * LOG: Debugging threads and sockets.
 * LOG:
 * LOG: Revision 1.5  1998/04/09 15:25:57  mmiers
 * LOG: Some cleanup for testing purposes.
 * LOG:
 * LOG: Revision 1.4  1998/04/08 20:26:54  mmiers
 * LOG: Work on tracing...
 * LOG:
 * LOG: Revision 1.3  1998/04/08 20:12:57  mmiers
 * LOG: update socket library and classes.
 * LOG:
 * LOG: Revision 1.3  1998/04/08 18:43:26  mmiers
 * LOG: Get sockets to build on Solaris.
 * LOG:
 * LOG: Revision 1.2  1998/04/08 17:25:28  mmiers
 * LOG: Work on sockets abstraction.
 * LOG:
 * LOG: Revision 1.1  1998/04/08 03:23:46  mmiers
 * LOG: Trace and sockets APIs.
 * LOG:
 * LOG: Revision 1.1  1998/02/25 20:38:39  ssharma
 * LOG: First cut version of the sockets library.
 * LOG:
 *
 ****************************************************************************/

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <its.h>
#include <its_sockets.h>
#include <its_object.h>
#include <its_assertion.h>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#include <its_timers.h>
#include <its_iniparse.h>
#include <its_app.h>

#ident "$Id: its_sockets.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $"

/*
 * for those OS's who don't define this
 */
#ifndef SOMAXCONN
#define SOMAXCONN 25	
#endif

/* local definition, maximum amount of times to retry hostname resolution */ 
#define MAX_RESOLVE_ATTEMPTS 12 

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      SOCK_WinInit.
 *
 *  Purpose:
 *      Initialize the WINSOCK DLL.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - Something bad happened
 *
 ****************************************************************************/
static int
SOCK_WinInit(ITS_Class objClass)
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
 
    wVersionRequested = MAKEWORD(2, 2);
 
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        /* Tell the user that we couldn't find a usable */
        /* WinSock DLL.                                  */
        return (ITS_EBADSOCKET);
    }
 
    /* Confirm that the WinSock DLL supports 2.0.*/
    /* Note that if the DLL supports versions greater    */
    /* than 2.0 in addition to 2.0, it will still return */
    /* 2.0 in wVersion since that is the version we      */
    /* requested.                                        */
     if (LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2 )
    {
        /* Tell the user that we couldn't find a usable */
        /* WinSock DLL.                                  */
        WSACleanup();

        return (ITS_EBADSOCKET); 
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Name:
 *      SOCK_WinDone.
 *
 *  Purpose:
 *      Terminate use of the WINSOCK DLL.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 ****************************************************************************/
static void
SOCK_WinDone(ITS_Class objClass)
{
    WSACleanup();
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_CreateAddr
 *
 *  Purpose:
 *      Create the address structure appropriate for an INET addr
 *
 *  Input Parameters:
 *      host - the hostname or IP address (second form is dotted quad).
 *      port - the port number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      sin - the INET address
 *      NULL - an error occurred
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_CreateAddr(ITS_SOCK_DOMAIN domain,
                const char* host_or_path, int port,
                void **data, int *size)
{
    struct sockaddr_in *sin;             /* ptr to INET domain addr data */ 
    u_long addr;

    /* setup if INET domain */ 
    if (domain == INET_DOMAIN)
    {
#if defined(USE_DNS)
        int    i;                            /* loop iterator */
        struct hostent     *hostinfo = NULL; /* host resolution structure */
        int    attempt = 0;                  /* count of resolve attempts */
        int    done = ITS_FALSE;             /* while termination */

        /*
         * Try for up to one minute to resolve hostname 
         * Close socket on failure because if we can't   
         * resolve then we don't have a use for it        
         */
        while (!done) 
        {
            ITS_BOOLEAN byName = isalpha(host_or_path[0]);
            done = ITS_TRUE; 

            if (byName)
            {
                hostinfo = gethostbyname(host_or_path);
            }
            else
            {
                addr = inet_addr(host_or_path);

                if ((int)addr == -1)
                {
                    hostinfo = gethostbyname(host_or_path);
                }
                else
                {
                    hostinfo = gethostbyaddr((char *)&addr,
                                             sizeof(addr),
                                             AF_INET);

                    if (hostinfo == NULL)
                    {
                        hostinfo = gethostbyname(host_or_path);
                    }
                }
            }

            if (hostinfo == NULL) 
            {
               int error;

                /*
                 * If the error is WSATRY_AGAIN do so unless we have tried to
                 * often already, in which case just timeout 
                 */
                switch ((error = WSAGetLastError())) 
                {    
                case WSATRY_AGAIN:
                    if (++attempt > MAX_RESOLVE_ATTEMPTS) 
                    {
                        return (ITS_EBADHOST);
                    } 
                    else
                    {
                        done = ITS_FALSE;

                        TIMERS_Sleep(5);
                    } 
                    break; 

                /* Any other error we just give up */ 
                default:
                    return (ITS_EINVALIDARGS);
                }
            }
        }

#else /* !USE_DNS */

        addr = inet_addr(host_or_path);

        if ((int)addr == -1)
        {
            return (ITS_EBADHOST);
        }

#endif /* USE_DNS */

        /* Allocate storage for sockaddr_in structure */ 
        if ((sin = calloc(1, sizeof(struct sockaddr_in))) == NULL)
        {
            return (ITS_ENOMEM);
        }

        /* Set up pertinant info in sockaddr_in */ 
        sin->sin_family = AF_INET;
        sin->sin_port = htons((u_short)port);

#if defined(USE_DNS)

        /* Find index into host list */ 
        for (i = 0; hostinfo->h_addr_list[i] != NULL; i++) 
        {    
            if (hostinfo->h_addrtype == AF_INET)
            {    
                if (hostinfo->h_length == sizeof(sin->sin_addr.s_addr))
                {  
                    break; 
                } 
            } 
        }

        /*
         * Err if nothing in list, otherwise get info into the sockaddr_in  
         * (I am not real sure that he error CAN happen, but I'll leave     
         *  this check in because it doesn't hurt...) 
         */
        if (hostinfo->h_addr_list[i] == NULL)
        {
            free(sin);

            return (ITS_EBADHOST);
        }             

        memcpy((void *)&sin->sin_addr.s_addr, (void *)hostinfo->h_addr,
               hostinfo->h_length);
#else

        sin->sin_addr.s_addr = addr;

#endif

        *data = (void *)sin;
        *size = sizeof(struct sockaddr_in);
    }
    else
    {
        *data = NULL;
        *size = 0;

        return (ITS_EINVALIDARGS);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientOpen.
 *
 *  Purpose:
 *      This will create a client socket and resolve the target server's 
 *      hostname.
 *
 *  Input Parameters:
 *      SOCK_DOMAIN    INET_DOMAIN or UNIX_DOMAIN
 *      char *         hostname or stream pathname of server
 *      int            port number of server socket
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - Something bad happened
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_ClientOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                const char *host_or_path, int port) 
{
    int                 dummy = 1;                    /* for setsockoption() */
    ITS_SocketInfo      *ret = NULL;

    /* Make sure we've got a valid pointer */
    ITS_C_ASSERT(sockInfo != NULL);

    *sockInfo = NULL;

    /* Initialize addr storage if we need to */ 
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* get the address */
    if (SOCK_CreateAddr(domain, host_or_path, port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
    {
        free(ret);

        return (ITS_EBADHOST);
    }

    /* setup if INET domain */ 
    if (domain == INET_DOMAIN)
    {
        struct linger      linger;           /* set linger structure */

        /* Create a socket */ 
        if ((ret->socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
        {
            free(ret->addr);
            free(ret);

            return (ITS_ENOSOCKET);
        }

        /* Set linger on, to 0 time */ 
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                   (char *)&linger, sizeof(struct linger));

        /* Save off addr info in our own dataspace */ 
        ret->type = SPROT_TYPE_TCP_CLIENT;
        ret->af = AF_INET;

        *sockInfo = ret;
    }
    /* Any other domain in invalid */ 
    else
    {
        free(ret->addr);
        free(ret);

        return (ITS_EINVALIDARGS);
    }

    /* Set re-use addr socket option */ 
    setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));

    /* fini */ 
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ServerOpen.
 *
 *  Purpose:
 *     Create a server socket and resolve hostname (why a hostname?  don't 
 *     ask me I didn't write this I am just cleaning it up.  I suspect the 
 *     client was written first and modified into this... ) 
 *
 *  Input Parameters:
 *      SOCK_DOMAIN         INET_DOMAIN or UNIX_DOMAIN 
 *      host_or_path        local hostname
 *      port                local port number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - an error occured 
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_ServerOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                const char *host_or_path, int port) 
{
    int    dummy = 1;       /* for socket option */
    ITS_SocketInfo *ret;

    /* Make sure the address is good */
    ITS_C_ASSERT(sockInfo != NULL);

    /* Set up our addr info accounting */ 
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* get the address */
    if (SOCK_CreateAddr(domain, host_or_path, port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
    {
        free(ret);

        return (ITS_EBADHOST);
    }

    /* setup if INET domain */
    if (domain == INET_DOMAIN) 
    {
        struct linger      linger;           /* for set linger */ 

        /* Create a socket */ 
        if ((ret->socket = socket(AF_INET, SOCK_STREAM, 0)) ==
            INVALID_SOCKET) 
        {
            free(ret->addr);
            free(ret);

            return (ITS_ENOSOCKET);
        }
 
        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                   (char *)&linger, sizeof(struct linger));
 
        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_TCP_SERVER;
        ret->af = AF_INET;

        *sockInfo = ret;
    }
    /* Any other domain is invalid */ 
    else
    {
        free(ret->addr);
        free(ret);

        return (ITS_EINVALIDARGS);
    }

    /* Set reuseaddr socket option */ 
    setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
               (void *)&dummy, sizeof(int));

    /* bind to the port specified */ 
    if (bind(ret->socket, (struct sockaddr *)ret->addr, ret->asize) ==
        SOCKET_ERROR) 
    {
        free(ret->addr);
        closesocket(ret->socket);
        free(ret);

        return (ITS_EBINDFAIL);
    }

    /* Set up a listen queue */ 
    if (listen(ret->socket, SOMAXCONN) == SOCKET_ERROR)
    {
        free(ret->addr);
        closesocket(ret->socket);
        free(ret);

        return (ITS_ELISTENFAIL);
    }

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_EndPointOpen.
 *
 *  Purpose:
 *     Create an end socket and resolve hostname
 *
 *  Input Parameters:
 *      host_or_path        local hostname
 *      port                local port number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - an error occured 
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_EndPointOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                  const char *host_or_path, int port) 
{
    int    dummy = 1;                    /* for socket option */
    ITS_SocketInfo *ret;
    struct linger      linger;           /* for set linger */ 

    /* Make sure the address is good */
    ITS_C_ASSERT(sockInfo != NULL);

    /* Set up our addr info accounting */ 
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* get the address */
    if (SOCK_CreateAddr(domain, host_or_path, port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
    {
        free(ret);

        return (ITS_EBADHOST);
    }

    /* Create a socket */ 
    if (domain == INET_DOMAIN)
    {
        if ((ret->socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) 
        {
            free(ret->addr);
            free(ret);

            return (ITS_ENOSOCKET);
        }

        /* Set linger on, to 0 time */
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                   (char *)&linger, sizeof(struct linger));

        /* Save off addr info in our own dataspace */
        ret->type = SPROT_TYPE_UDP;
        ret->af = AF_INET;

        *sockInfo = ret;

        /* Set reuseaddr socket option */ 
        setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR,
                   (void *)&dummy, sizeof(int));
    }
    else
    {
        free(ret->addr);
        free(ret);

        return (ITS_EINVALIDARGS);
    }

    /* bind to the port specified */ 
    if (bind(ret->socket, (struct sockaddr *)ret->addr, ret->asize) ==
        SOCKET_ERROR) 
    {
        free(ret->addr);
        closesocket(ret->socket);
        free(ret);

        return (ITS_EBINDFAIL);
    }

    /* fini */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_RawOpen.
 *
 *  Purpose:
 *      This will create a raw socket and resolve the target server's 
 *      hostname.
 *
 *  Input Parameters:
 *      SOCK_DOMAIN                        INET_DOMAIN or UNIX_DOMAIN
 *      char *                             hostname of steam pathname of server
 *      int                                port number of server socket
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - Something bad happened
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_RawOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
             const char *host_or_path, int port, int pf,
             ITS_BOOLEAN autoHeaders) 
{
    int                 dummy = 1;                    /* for setsockoption() */
    ITS_SocketInfo      *ret = NULL;
    BOOL hdr = TRUE;

    /* Make sure we've got a valid pointer */
    ITS_C_ASSERT(sockInfo != NULL);

    *sockInfo = NULL;

    /* Initialize addr storage if we need to */ 
    if ((ret = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    if(SOCK_CreateAddr(domain, host_or_path, port, &ret->addr,
                       &ret->asize) != ITS_SUCCESS)
    {
        free(ret);

        return ITS_EBADHOST;
    }

    /* setup if INET domain */ 
    if (domain != INET_DOMAIN)
    {
        free(ret->addr);
        free(ret);

        return (ITS_EINVALIDARGS);
    }
    else
    {
        struct linger      linger;           /* set linger structure */

        /* Create a socket */ 
        if ((ret->socket = socket(AF_INET, SOCK_RAW, pf)) < 0) 
        {
            free(ret->addr);
            free(ret);

            return (ITS_ENOSOCKET);
        }

        /* Set linger on, to 0 time */ 
        linger.l_onoff = 1;
        linger.l_linger = 0;
        setsockopt(ret->socket, SOL_SOCKET, SO_LINGER,
                       (char *)&linger, sizeof(struct linger));

        /* Save off addr info in our own dataspace */ 
        ret->type = SPROT_TYPE_RAW;
        ret->af = AF_INET;

        *sockInfo = ret;
    }

    /*
     * if user wants automatic IP header generated, clear this
     * NOTE: This only works on W2K.  Sigh.
     */
    if (autoHeaders)
    {
        if (setsockopt(ret->socket, IPPROTO_IP, IP_HDRINCL,
                       (void *)&hdr, sizeof(BOOL)) == SOCKET_ERROR)
        {
            dummy = WSAGetLastError();
        }
    }

    /*
     * don't fragment datagrams.  Will result in ICMP message
     * if frag is required.  This works around the bug above.
     */
    if (setsockopt(ret->socket, IPPROTO_IP, IP_DONTFRAGMENT,
                   (void *)&hdr, sizeof(BOOL)) == SOCKET_ERROR)
    {
        dummy = WSAGetLastError();
    }

    SOCK_Send(ret, NULL, 2, ret->addr, ret->asize);

    /* fini */ 
    return (ITS_SUCCESS);
        
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Pending.
 *
 *  Purpose:
 *      Use this to see how many bytes can be gotten from a subsequent read() 
 *      call.  Note that this will return a number meaning that _at least_ so 
 *      many bytes can be read, because more data may be received in between 
 *      the time this call is made and the actual read() system call is made
 *
 *  Input Parameters:
 *      int     sock                File descriptor to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      -1              An error occured: on Windows check WSAGetLastError.
 *      (Other)         Number of bytes available (may be 0)
 *
 *  Notes:
 *      This function only works on TCP/IP sockets.
 ****************************************************************************/
ITSDLLAPI int
SOCK_Pending(ITS_SocketInfo *info)
{    
    int bytes_pending = 0;       /* ioctl() will fill in with #bytes ready */  
    int rc;                      /* return code */  

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    /* If error display and return -1 else return bytes pending */ 
    if (ioctlsocket(info->socket, FIONREAD, &bytes_pending) < 0) 
    {
        rc= -1; 
    } 
    else
    {    
        rc = bytes_pending; 
    }

    return rc;  
} 
    
/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ReadyToRead.  
 *
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      int    sock              File descriptor to check 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - data pending
 *      ITS_FALSE - no data or error.
 *
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
SOCK_ReadyToRead(ITS_SocketInfo* info) 
{    
    fd_set fds;

    FD_ZERO(&fds);
    FD_SET(info->socket, &fds);

    if (select(info->socket + 1, &fds, NULL, NULL, NULL) > 0)
    {
        return (ITS_TRUE);
    }
    else
    {
        return (ITS_FALSE);
    }
} 

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientConnect.
 *
 *  Purpose:
 *      Connect a socket, if it is a tcp socket disable that pesky nagle 
 *      algorithm
 *
 *  Input Parameters:
 *      int sock        file descriptor to connect() with
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS      if everything is OK
 *      Anything else    if it's all gone horribly wrong
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_ClientConnect(ITS_SocketInfo* info)
{    
    struct protoent     *ent;                /* For use in disabling nagle */ 
    int flag = 1;                            /* For use in disabling nagle */

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    /*
     * Attempt connection 
     */
    if (connect(info->socket, info->addr, info->asize) == SOCKET_ERROR)
    {
        return (ITS_ECONNECTFAIL);
    } 

    /*
     * Disable TCP NAGLE algorighm. (don't delay short messages waiting for 
     * window ack)
     */
    if (info->af == AF_INET && (ent = getprotobyname("tcp")) != NULL)
    {    
        setsockopt(info->socket, ent->p_proto,
                   TCP_NODELAY, (char *)&flag, sizeof(flag));
    }

    /*
     * fini 
     */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ServerAccept.
 *
 *  Purpose:
 *      Accept a connection and disable the NAGLE algorithm (queue short 
 *      messages waiting for window ack) support on connection 
 *
 *  Input Parameters:
 *      int sock                file descriptor to accept on 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS           file descriptor of connection 
 *      Anything else         something is wrong     
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_ServerAccept(ITS_SocketInfo* info, ITS_SocketInfo **newInfo)
{
    int    flag = 1;          /* for setsockopt() call */
    struct protoent    *ent;  /* protocol entry */ 
    ITS_SocketInfo* tmp;
    ITS_SocketInfo buf;
    struct sockaddr_in abuf;

    ITS_C_ASSERT(newInfo != NULL);

    *newInfo = NULL;

    /* Accept a connection */ 
    buf.asize = sizeof(struct sockaddr_in);
    buf.socket = accept(info->socket, (struct sockaddr *)&abuf, &buf.asize);

    /*
     * If the return code is 0 or greater it is a file descriptor 
     * (technically this is an err, but you will never see a file 
     * descriptor of zero so I'm leaving the code as is        
     */
    if (buf.socket == INVALID_SOCKET) 
    {
        int error = WSAGetLastError();

        return (ITS_EBADSOCKET);
    }

    /* allocate info struct */
    if ((tmp = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    *tmp = buf;

    /* Allocate storage for addr structure */ 
    if ((tmp->addr = calloc(1, sizeof(struct sockaddr_in))) == NULL)
    {
        free(tmp);

        return (ITS_ENOMEM);
    }

    *((struct sockaddr_in *)tmp->addr) = abuf;

    /* Update our socket data info */ 
    tmp->af = ((struct sockaddr_in *)tmp->addr)->sin_family;

    /* Get rid of nagle support */ 
    if (tmp->af == AF_INET && (ent = getprotobyname("tcp")) != NULL) 
    {    
        setsockopt(tmp->socket, ent->p_proto,
                   TCP_NODELAY, (char *)&flag, sizeof(flag));
    }

    *newInfo = tmp;

    /* fini */ 
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Read.
 *
 *  Purpose:
 *      Read whatever data is on the socket, keep doing it until we get all 
 *      data or a closed peer
 *
 *  Input Parameters:
 *      int sock                       file descriptor of this socket
 *      char *buf                      pointer to where you want to stick data
 *      int nbytes                     the number of bytes you expect to read
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  0                    peer has closed connection or there was an error 
 *                       and thus far no data has been read 
 *
 *  >0                   This much data has been read.  There may or 
 *                       may not have been an error. 
 ****************************************************************************/
ITSDLLAPI int
SOCK_Read(ITS_SocketInfo* info, char *buf, int nbytes) 
{
    int     nleft;                    /* Amount of data left to read */      
    int     nread;                    /* Amount of data we have read */ 
    int     done = ITS_FALSE;             /* Loop terminator for EOF      */  
    int     first = ITS_TRUE;

    /* Set up how much we want to read */ 
    nleft = nbytes;

    if (!info)
    {
        return (0);
    }

    /* While not error or EOF and there is more data expected... */ 
    while ((nleft > 0) && (!done)) 
    {
        /* Read something */ 
        nread = recv(info->socket, buf, nleft, 0); 

        /*
         * If there was an error return # of bytes read thus far  
         * (how odd..)                                            
         */
        if (nread == SOCKET_ERROR)        
        {
            if (WSAGetLastError() == WSAECONNRESET && first)
            {
                first = ITS_FALSE;

                continue;
            }
            else
            {
                return nread;
            }
        }

        /* If there is an EOF set while to exit */ 
        else if (nread == 0)    
        {    
            done = ITS_TRUE; 
        }

        /* We read some data */ 
        else 
        {    
            nleft -= nread;
            buf += nread;
        }

        first = ITS_FALSE;
    }

    /* Return the amount of data we read */ 
    return (nbytes - nleft);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Read.
 *
 *  Purpose:
 *      Read whatever data is on the socket, keep doing it until we get all 
 *      data or a closed peer
 *
 *  Input Parameters:
 *      int sock                       file descriptor of this socket
 *      char *buf                      pointer to where you want to stick data
 *      int nbytes                     the number of bytes you expect to read
 *      void *from                     who the message came from
 *      int *len                       length of the orig addr
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  0                    peer has closed connection or there was an error 
 *                       and thus far no data has been read 
 *
 *  >0                   This much data has been read.  There may or 
 *                       may not have been an error. 
 ****************************************************************************/
ITSDLLAPI int
SOCK_Recv(ITS_SocketInfo* info, char *buf, int nbytes, void* from, int* len) 
{
    if (!info)
    {
        return (0);
    }

    /* Read something */ 
    return recvfrom(info->socket, buf, nbytes, 0, from, len); 
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NonBlockingRead.
 *
 *  Purpose:
 *      This is a nonblocking read that will timeout if it does not receive the
 *      specified amount of data in the time indicated.   
 *
 *  Input Parameters:
 *      int fd                   file descriptor of socket to read from 
 *      char *dataptr            pointer to buffer to write to 
 *      int datasize             amount of bytes to attempt reading 
 *      int maxtime              time in seconds to wait for data 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                          EOF or TIMEOUT or ERROR has occured  
 *      default                    The amount of bytes read
 ****************************************************************************/
ITSDLLAPI int
SOCK_NonBlockingRead(ITS_SocketInfo* info, char *buf, int size, int maxtime) 
{ 
    time_t     start_time, now_time;    /* Used to check for timeout */  
    int        ioctl_val = 1;           /* value for ioctl() call */
    int        br = 0;                  /* bytes read in single read() */ 
    int        rc = 0;                  /* function return code */ 
    int        done = ITS_FALSE;            /* while() terminator */ 
    int        totalread = 0;           /* bytes read in total */
    int        error;

 
    /* Note the time we started */ 
    time(&start_time); 

    if (!info)
    {
        return (0);
    }

    /* Set this socket to nonblocking */ 
    ioctl_val = 1;
    if (ioctlsocket(info->socket, FIONBIO, &ioctl_val) < 0) 
    {
        return (0);
    }  

    /* While we are not done, try to read */ 
    while(!done) 
    {
        /* Read some data */ 
        switch ((br = recv(info->socket, buf + totalread,
                           size - totalread, 0)))
        {
        /* An error has occured */ 
        case SOCKET_ERROR: 
            switch((error = WSAGetLastError())) 
            {
            /* Resource temporarily unavailable (no data yet) */ 
            case WSAEINPROGRESS:  
                break; 

            /* Recover from interrupt errors */ 
            case WSAEINTR: 
                break;
            
            /* Recover if recv would block (retry within timeout). */
            case WSAEWOULDBLOCK:
                break;
 
            /* Any other error */ 
            default: 
                done = ITS_TRUE;
                rc = 0;  
                break; 
            } 
            break; 

        /* EOF (peer has closed connection) */ 
        case 0:
            done = ITS_TRUE;
            rc=0;  
            break;

        /* We have read some amount of data */ 
        default:
            totalread += br;   
            if (totalread >= size) 
            {    
                done = ITS_TRUE;
            } 
            break; 
        }
        
        /* Set the return code (may be reset in timeout below) */ 
        rc = totalread;
 
        /*
         * Check to see if we have timed out if we are not already done 
         */
        if (!done) 
        {    
            time(&now_time); 
            if (now_time > start_time + maxtime) 
            {    
                done = ITS_TRUE;
            }
        }
    } 

   /* Set this socket back to blocking */
   ioctl_val = 0; 
   if (ioctlsocket(info->socket, FIONBIO, &ioctl_val) < 0)
   {
       /* what to do? */
   }

    /* fini */
    return rc; 
} 

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Write.
 *
 *  Purpose:
 *      Write a fixed amount of data (or as much as you can) out over a socket 
 *
 *  Input Parameters:
 *      int sock             file descriptor of socket 
 *      char *buf            pointer to data to write out 
 *      int nbytes           size of data to write 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                   Some sort of error occured and no data send 
 *      other               Amount of data that was sent (which could be less
 *                          than requested) 
 ****************************************************************************/
ITSDLLAPI int
SOCK_Write(ITS_SocketInfo* info, char *buf, int nbytes) 
{
    int     nleft;
    int     nwritten;
    int     first = ITS_TRUE;

    /* Set up how much we need to write */ 
    nleft = nbytes;

    if (!info)
    {
        return (0);
    }

    /* While still bytes to write do so */ 
    while (nleft > 0)
    {
        /* Write some data */ 
        nwritten = send(info->socket, buf, nleft, 0); 

        /* If any of these errors return # actually written */ 
        if (nwritten == SOCKET_ERROR)
        {
            int error = WSAGetLastError();

            /* error, or zero length write */
            if (error == WSAECONNRESET && first)
            {
                first = ITS_FALSE;

                continue;
            }
            else if (error != WSAEINTR && error != WSAEWOULDBLOCK &&
                     error != WSAEINPROGRESS)
            {
                return nwritten;
            }
        }

        /* else adjust counters and keep going */
        else
        {
            /*
             * If the return code was -1 (error) set to zero so we 
             * do not end up losing data!!!                        
             */
            if (nwritten == -1)
            {    
                nwritten = 0;
            }

            /*
             * Note that the buf pointer is incremented as opposed to 
             * doing a write to buf+nwritten (which might have been a  
             * bit more clear).
             */
            nleft -= nwritten;
            buf += nwritten;
        }

        first = ITS_FALSE;
    }

    /* Return how much we actually wrote */ 
    return (nbytes - nleft);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Write.
 *
 *  Purpose:
 *      Write a fixed amount of data (or as much as you can) out over a socket 
 *
 *  Input Parameters:
 *      int sock             file descriptor of socket 
 *      char *buf            pointer to data to write out 
 *      int nbytes           size of data to write 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                   Some sort of error occured and no data send 
 *      other               Amount of data that was sent (which could be less
 *                          than requested) 
 ****************************************************************************/
ITSDLLAPI int
SOCK_Send(ITS_SocketInfo* info, char *buf, int nbytes, void* to, int len) 
{
    if (!info)
    {
        return (0);
    }

    /*
     *  Write some data
     *  FIXME: first part works around MS bug.  Remove for W2K.
     */ 
    if (info->type == SPROT_TYPE_RAW)
    {
        int ret;

        ret = sendto(info->socket, buf + sizeof(SOCK_IPv4Header), nbytes - sizeof(SOCK_IPv4Header),
                     0, to, len);

        if (ret <= 0)
        {
            return (ret);
        }
        else
        {
            return (ret + sizeof(SOCK_IPv4Header));
        }
    }
    else
    {
        return sendto(info->socket, buf, nbytes,
                      0, to, len); 
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NonBlockingWrite.
 *
 *  Purpose:
 *      This is a nonblocking write that will timeout if it cannot write the
 *      specified amount of data in the time indicated. 
 *
 *  Input Parameters:
 *      int fd                  file descriptor of socket to write from 
 *      char *dataptr           pointer to buffer to write to 
 *      int datasize            amount of bytes to attempt writeing 
 *      int maxtime             time in seconds to wait for data 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                          EOF or TIMEOUT or ERROR has occured  
 *      default                    The amount of bytes actually written
 ****************************************************************************/
ITSDLLAPI int
SOCK_NonBlockingWrite(ITS_SocketInfo* info, char *buf, int size, int maxtime) 
{ 
    time_t    start_time, now_time;        /* Used to check for timeout */  
    int       ioctl_val = 1;              /* value for ioctl() call */
    int       br = 0;                    /* bytes write in single write() */ 
    int       rc = 0;                    /* function return code */ 
    int       done = ITS_FALSE;              /* while() terminator */ 
    int       totalwrite = 0;           /* bytes write in total */ 
    int       write_attempt_size = 0;     /* Amount of bytes to attempt */ 
                                           /* to write on a single write()*/ 
    int       error;
 
    /* Note the time we started */ 
    time(&start_time); 

    /* Set this socket to nonblocking */ 
    if (!info)
    {
        return (0);
    }

    ioctl_val = 1;
    if (ioctlsocket(info->socket, FIONBIO, &ioctl_val) < 0) 
    {
        return (0);
    } 

    /* While we are not done, try to write */ 
    while(!done) 
    {
        /* Optimize write for ethernet */ 
        write_attempt_size = size - totalwrite; 
        if (write_attempt_size > 1400) 
        {
            write_attempt_size = 1400; 
        } 
    
        /* Read some data */ 
        switch((br = send(info->socket, buf + totalwrite,
                          write_attempt_size, 0)))
        {
        /* An error has occured */ 
        case SOCKET_ERROR: 
            switch((error = WSAGetLastError())) 
            {
            /* Resource temporarily unavailable (no data yet) */ 
            case WSAEINPROGRESS:  
                break; 

            /*
             * Recover from intterupted system calls and that lot 
             * In these cases return with whatever data we wrote   
             */
            case WSAEINTR: 
                break;

            /* Recover if send would block (retry within timeout). */
            case WSAEWOULDBLOCK:
                break;

            /* Any other error */ 
            default: 
                done = ITS_TRUE;
                rc = 0;  
                break; 
            } 
            break; 

            /* EOF (peer has closed connection) */ 
            case 0:
            done = ITS_TRUE;
            rc=0;  
            break;

            /* We have write some amount of data */ 
            default:
            totalwrite+=br;   
            if (totalwrite >= size) 
            {    
                done = ITS_TRUE;
            } 
            break; 
        }
        
        /* Set the return code (may be reset in timeout below) */ 
        rc = totalwrite;
 
        /* Check to see if we have timed out if we are not already done */ 
        if (!done) 
        {    
            time(&now_time); 
            if (now_time > start_time + maxtime) 
            {    
                done = ITS_TRUE;
                rc = 0; 
            }
        }
    } 

    /* Set this socket back to blocking */
    ioctl_val = 0; 
    if (ioctlsocket(info->socket, FIONBIO, &ioctl_val) < 0)
    {
        /* what to do here */
    }

    /* fini */
    return rc; 
} 

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Close.
 *
 *  Purpose:
 *      Close the socket, delete any stream files that may be littering 
 *      the file system and remove the socket data from the tracking structure
 *
 *  Input Parameters:
 *      int sock                                socket handle
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 ****************************************************************************/
ITSDLLAPI void
SOCK_Close(ITS_SocketInfo* info)
{
    if (!info)
    {
        return;
    }

    if (info->socket != INVALID_SOCKET)
    {
        shutdown(info->socket, SD_BOTH);

        /* Close the socket handle */ 
        closesocket(info->socket);

        info->socket = INVALID_SOCKET;

        /* Remove from our dataspace */ 
        if (info->addr)
        {
            free(info->addr);
        }
    }

    free(info);
 
    return; 
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_DebugDump.  
 *
 *  Purpose:
 *      Dump out all the accounting info we have been maintaining on a 
 *      given socket
 *
 *  Input Parameters:
 *      int sock                        file descriptor of socket
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
SOCK_DebugDump(ITS_SocketInfo* info) 
{
#if 0
    struct hostent *hostinfo;
    struct in_addr in;

    TRACE_DEBUG(("sock_debug_dump: SOCKET DEBUG INFO:\n"));
    TRACE_DEBUG(("sock_debug_dump: fd: %d  address family: %s\n",
                 info->socket,
                 info->af == AF_INET ? "AF_INET" : "AF_UNIX"));

    /* If this is a socket... */ 
    if (info->af == AF_INET) 
    {
        /*
         * Print address and hostname if available 
         * Print out the port in any case          
         */
        in = ((struct sockaddr_in *)info->addr)->sin_addr;
        if ((hostinfo = gethostbyaddr((char *)&in, sizeof(struct in_addr),
                                      AF_INET)) != NULL)
        {    
            TRACE_DEBUG(( "address: %-16.16s  hostname: %s\n",
                    inet_ntoa(in), hostinfo->h_name));
        } 
        else
        {    
            TRACE_DEBUG (("address: %-16.16s  hostname: unresolved\n",
                    inet_ntoa(in)));
        }

        TRACE_DEBUG (("port: %d\n",
             ntohs(((struct sockaddr_in *)info->addr)->sin_port)));
    }

    /* This is not a socket, it must be a stream */ 
    else 
    {    
        TRACE_DEBUG(("path: %s\n",
                    ((struct sockaddr_un *)info->addr)->sun_path));
    }

    /* fini */ 
    return; 
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetPeerName
 *
 *  Purpose:
 *      Determine the address information for a connected peer.
 *
 *  Input Parameters:
 *      in - pointer to ITS_SocketInfo
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      out - pointer to ITS_SocketInfo
 *
 *  Return Value:
 *      ITS_SUCCESS - address of connected peer is in "out".
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_GetPeerName(ITS_SocketInfo* in, ITS_SocketInfo* out)
{
    out->socket = in->socket;
    out->type = in->type;

    if ((out->addr = calloc(1, sizeof(struct sockaddr))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    out->asize = sizeof(struct sockaddr);

    if (getpeername(in->socket, out->addr, &out->asize) != 0)
    {
        free(out->addr);

        return (ITS_EBADSOCKET);
    }

    out->af = in->af;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_AddrsAreEqual
 *
 *  Purpose:
 *      Determine if the address information for two connections
 *
 *  Input Parameters:
 *      a1, a2 - pointers to ITS_SocketInfo
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_FALSE - addrs are not equal
 *      ITS_TRUE - addrs are equal
 *
 *  Notes:
 *      The actual file descriptors for the sockets are not included
 *      in the equality check.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
SOCK_AddrsAreEqual(ITS_SocketInfo* a1, ITS_SocketInfo* a2)
{
    struct sockaddr_in *tmp = (struct sockaddr_in *)a1->addr;

    if (a1->type != a2->type ||
        a1->af != a2->af)
    {
        return (ITS_FALSE);
    }

    switch (tmp->sin_family)
    {
    default:
        return (ITS_FALSE);

    case AF_INET:
        {
            struct sockaddr_in *a, *b;

            a = (struct sockaddr_in *)a1->addr;
            b = (struct sockaddr_in *)a2->addr;

            if (a->sin_port == b->sin_port &&
                a->sin_addr.s_addr == b->sin_addr.s_addr)
            {
                return (ITS_TRUE);
            }
        }
        break;
    }

    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned long from network order to host order
 *
 *  Input Parameters:
 *      ulong - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_ULONG
SOCK_NToHL(ITS_ULONG ulong)
{
    return ntohl(ulong);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned short from network order to host order
 *
 *  Input Parameters:
 *      ushort - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
SOCK_NToHS(ITS_USHORT ushort)
{
    return ntohs(ushort);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned long from host order to network order
 *
 *  Input Parameters:
 *      ulong - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_ULONG
SOCK_HToNL(ITS_ULONG ulong)
{
    return htonl(ulong);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned short from host order to network order
 *
 *  Input Parameters:
 *      ushort - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
SOCK_HToNS(ITS_USHORT ushort)
{
    return htons(ushort);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetLocalAddrs()
 *
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_Poll(ITS_SockPollInfo *socks, int nsocks, int usecs)
{
    int i;
    fd_set reads, writes;
    int ret, max;

    if (nsocks < 0 ||
        (usecs == SOCK_POLL_WAIT_FOREVER && nsocks == 0))
    {
        return (ITS_EINVALIDARGS);
    }

    FD_ZERO(&reads);
    FD_ZERO(&writes);

    max = 0;
    for (i = 0; i < nsocks; i++)
    {
        socks[i].wasSet = 0;

        if ((int)socks[i].sinfo->socket > max)
        {
            max = socks[i].sinfo->socket;
        }

        if (socks[i].lookFor & (SOCK_POLL_READ|SOCK_POLL_READ_OOB))
        {
            FD_SET(socks[i].sinfo->socket, &reads);
        }

        if (socks[i].lookFor & (SOCK_POLL_WRITE|SOCK_POLL_WRITE_OOB))
        {
            FD_SET(socks[i].sinfo->socket, &writes);
        }
    }

    if (max > 0)
    {
        max++;
    }

    if (usecs == SOCK_POLL_WAIT_FOREVER)
    {
        ret = select(max, &reads, &writes, NULL, NULL);
    }
    else
    {
        struct timeval tv;

        tv.tv_sec = usecs / USEC_PER_SEC;
        tv.tv_usec = usecs % USEC_PER_SEC;

        ret = select(max, &reads, &writes, NULL, &tv);
    }

    if (ret == SOCKET_ERROR)
    {
        return (ITS_EBADSOCKET);
    }

    for (i = 0; i < nsocks; i++)
    {
        if (FD_ISSET(socks[i].sinfo->socket, &reads))
        {
            socks[i].wasSet |= SOCK_POLL_READ;
        }
        if (FD_ISSET(socks[i].sinfo->socket, &writes))
        {
            socks[i].wasSet |= SOCK_POLL_WRITE;
        }
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetLocalAddrs()
 *
 *  Purpose:
 *
 *  Input Parameters:
 *      name - for the crippled OS, what else?
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_GetLocalAddrs(SOCK_AddrStore **addrs, SOCK_AddrStore **masks,
                   SOCK_AddrStore **bcasts)
{
    int numAddrs, numnets;
    struct sockaddr_in *tmp;
    RESFILE_Manager *globalRes = NULL;
    static char var[ITS_PATH_MAX], val[ITS_PATH_MAX];
    const char *name = APPL_GetConfigFileName();

    *addrs = *masks = NULL;

    globalRes = RESFILE_CreateResourceManager(name);

    numAddrs = 32;

    if (!globalRes)
    {
        return (-1);
    }

    if ((*addrs = (SOCK_AddrStore *)calloc(numAddrs,
                                           sizeof(SOCK_AddrStore))) == NULL)
    {
        return (-1);
    }
    
    if ((*masks = (SOCK_AddrStore *)calloc(numAddrs,
                                           sizeof(SOCK_AddrStore))) == NULL)
    {
        free(*addrs);

        return (-1);
    }

    if ((*bcasts = (SOCK_AddrStore *)calloc(numAddrs,
                                           sizeof(SOCK_AddrStore))) == NULL)
    {
        free(*masks);
        free(*addrs);

        return (-1);
    }
    
    numnets = 0;

    if (RESFILE_Lock(globalRes) != ITS_SUCCESS)
    {
        free(*bcasts);
        free(*masks);
        free(*addrs);

        return (-1);
    }

    RESFILE_Rewind(globalRes, NULL);

    while (RESFILE_GetKeyName(globalRes, NULL,
                              var, sizeof(var)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(globalRes, NULL,
                               val, sizeof(val)) == ITS_SUCCESS)
    {
        if (strcmp(var, LOCAL_INTERFACE_STRING) == 0)
        {
            tmp = (struct sockaddr_in *)&((*addrs)[numnets]);

            tmp->sin_addr.s_addr = inet_addr(val);
            tmp->sin_port = 0;
            memset(tmp->sin_zero, 0, sizeof(tmp->sin_zero));
            tmp->sin_family = AF_INET;
        }

        if (strcmp(var, LOCAL_MASK_STRING) == 0)
        {
            tmp = (struct sockaddr_in *)&((*masks)[numnets]);

            tmp->sin_addr.s_addr = inet_addr(val);
            tmp->sin_port = 0;
            memset(tmp->sin_zero, 0, sizeof(tmp->sin_zero));
            tmp->sin_family = AF_INET;
        }

        if (strcmp(var, LOCAL_BCAST_STRING) == 0)
        {
            tmp = (struct sockaddr_in *)&((*bcasts)[numnets]);

            tmp->sin_addr.s_addr = inet_addr(val);
            tmp->sin_port = 0;
            memset(tmp->sin_zero, 0, sizeof(tmp->sin_zero));
            tmp->sin_family = AF_INET;

            numnets++;
        }
    }

    if (!numnets)
    {
        if (*addrs)
        {
            free(*addrs);
            *addrs = NULL;
        }

        if (*masks)
        {
            free(*masks);
            *masks = NULL;
        }

        if (*bcasts)
        {
            free(*bcasts);
            *bcasts = NULL;
        }
    }

    if (RESFILE_Unlock(globalRes) != ITS_SUCCESS)
	{
		return -1;
	}

    return (numnets);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetIPv4AddrAndPort() extracts the IP addr and port from
 *      an opaque type.
 *
 *  Purpose:
 *
 *  Input Parameters:
 *      addrStruct - the address to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      addr - the IP address
 *      port - the port
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_GetIPv4AddrAndPort(SOCK_AddrStore *addrStruct,
                        SOCK_IPv4Addr *addr,
                        ITS_USHORT *port)
{
    struct sockaddr_in *who = (struct sockaddr_in *)addrStruct;

    if (who->sin_family != AF_INET)
    {
        return (ITS_EINVALIDARGS);
    }

    *addr = SOCK_NToHL(who->sin_addr.s_addr);
    *port = SOCK_NToHS(who->sin_port);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *
 *  Purpose:
 *      Convert from a name in dotted quad to an address.
 *
 *  Input Parameters:
 *      name - the name to convert.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      addr - the IP address
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_IPv4NameToAddr(const char *name, SOCK_IPv4Addr *addr)
{
    char *tmp, *tmp2;
    ITS_ULONG conv;

    /* first */
    if ((tmp = strchr(name, '.')) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    *tmp = 0;
    tmp++;
    conv = atoi(name) << 24;

    /* second */
    tmp2 = tmp;
    if ((tmp = strchr(tmp, '.')) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    *tmp = 0;
    tmp++;
    conv |= atoi(tmp2) << 16;

    /* third */
    tmp2 = tmp;
    if ((tmp = strchr(tmp, '.')) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    *tmp = 0;
    tmp++;
    conv |= atoi(tmp2) << 8;

    /* last */
    conv |= atoi(tmp);

    *addr = SOCK_HToNL(conv);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *
 *  Purpose:
 *      Convert from an address to the dotted quad notation
 *
 *  Input Parameters:
 *      addr - the IP address
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      name - the string value of the name
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_IPv4AddrToName(char *name, SOCK_IPv4Addr addr)
{
    char buf[12];

    sprintf(buf, "%u.", addr >> 24);
    strcpy(name, buf);

    sprintf(buf, "%u.", (addr >> 16) & 0xFFU);
    strcat(name, buf);

    sprintf(buf, "%u.", (addr >> 8) & 0xFFU);
    strcat(name, buf);

    sprintf(buf, "%u", addr & 0xFFU);
    strcat(name, buf);

    return (ITS_SUCCESS);
}

/*
 * the class record
 */
ITSDLLAPI ITS_ClassRec itsSOCKET_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        SOCKET_CLASS_NAME,              /* class name */
        SOCK_WinInit,                   /* class init */
        SOCK_WinDone,                   /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsSOCKET_Class = (ITS_Class)&itsSOCKET_ClassRec;
