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
 *  ID: $Id: test3.cpp,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:52:31  cvsadmin
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
 * LOG: Revision 3.3  2001/03/06 22:24:37  mmiers
 * LOG: Convert to SUPPORT only
 * LOG:
 * LOG: Revision 3.2  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:23  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/05/23 23:48:04  mmiers
 * LOG:
 * LOG:
 * LOG: Use localhost.
 * LOG:
 * LOG: Revision 2.1  2000/04/25 16:46:42  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:32  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1998/11/18 18:07:11  mmiers
 * LOG: Update project information.
 * LOG:
 * LOG: Revision 1.3  1998/09/23 22:04:31  jrao
 * LOG: Updates from HPUX.
 * LOG:
 * LOG: Revision 1.2  1998/05/29 03:31:39  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.1  1998/04/09 23:43:46  mmiers
 * LOG: Debugging threads and sockets.
 * LOG:
 * LOG: Revision 1.1  1998/04/09 15:25:58  mmiers
 * LOG: Some cleanup for testing purposes.
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

#include <exception>

#include <its++.h>
#include <its_thread.h>
#include <its_sockets.h>
#include <its_statics.cpp>

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

int
main(int argc, char **argv)
{
    ITS_ClientSocket *sock;

    if (ITS_GlobalStart(0) != ITS_SUCCESS)
    {
        printf("global start failed\n");

        return (0);
    }

    try
    {
        sock = new ITS_ClientSocket(INET_DOMAIN, "127.0.0.1", 30000);
    }
    catch (exception& ex)
    {
        printf("Couldn't create client\n");

        return (EXIT_FAILURE);
    }

    if (sock->Connect() != ITS_SUCCESS)
    {
        printf("Couldn't connect to server.\n");

        delete sock;

        exit(0);
    }

    printf("Connected to server.  Enter text to send.\n> ");
    fflush(stdout);

    char buf[256];
    while (gets(buf) != NULL)
    {
        if (strlen(buf) == 0)
        {
            break;
        }

        sock->Write(buf, strlen(buf));
        sock->Write("\n", 1);

        printf("> ");
        fflush(stdout);
    }

    delete sock;

    ITS_GlobalStop();

    return (0);
}
