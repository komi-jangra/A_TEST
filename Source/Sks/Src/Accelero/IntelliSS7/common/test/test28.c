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
 *  ID: $Id: test28.c,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:52:30  cvsadmin
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
 * LOG: Revision 3.1  2001/01/10 19:44:00  mmiers
 * LOG: Debug new implementation.
 * LOG:
 *
 ****************************************************************************/

/*
 * list handling routines
 */
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <its.h>
#include <its_timers.h>
#include <its_thread.h>
#include <its_tq_trans.h>

TQUEUETRAN_Manager *queue;
ITS_BOOLEAN doExit = ITS_FALSE;

THREAD_RET_TYPE
testIt(void *arg)
{
    ITS_EVENT ev;

    while (!doExit)
    {
        int ret;

        ret = ITS_GetNextEvent(queue, &ev);

        printf("Thread %08x got ret %d src %d\n", pthread_self(), ret, ev.src);
        fflush(stdout);
    }

    THREAD_NORMAL_EXIT;
}

int
main(int argc, char **argv)
{
    int i;
    ITS_EVENT ev;
    ITS_THREAD thr;

    queue = ITS_Initialize(ITS_TRANSPORT_SINGLE_USER|ITS_TRANSPORT_TQUEUE, 1);

    if (queue == NULL)
    {
        printf("No queue\n");

        return (0);
    }

    for (i = 0; i < 5; i++)
    {
        if (THREAD_CreateThread(&thr, 0, testIt, NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            printf("No thread %d\n", i);
        }
    }

    for (i = 0; i < 15; i++)
    {
        ITS_EVENT_INIT(&ev, i, 0);

        TRANSPORT_PutEvent(1, &ev);
    }

    TIMERS_Sleep(1);
    printf("do exit\n");
    fflush(stdout);

    doExit = ITS_TRUE;

    for (i = 0; i < 5; i++)
    {
        ITS_EVENT_INIT(&ev, i, 0);

        TRANSPORT_PutEvent(1, &ev);
    }

    TIMERS_Sleep(1);

    return (0);
}

