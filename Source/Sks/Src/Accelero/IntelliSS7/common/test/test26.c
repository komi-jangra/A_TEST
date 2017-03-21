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
 *  ID: $Id: test26.c,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:52:29  cvsadmin
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
 * LOG: Revision 3.3  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.2  2000/10/15 18:50:40  mmiers
 * LOG: Test program done.  Now debugging is all that's left.
 * LOG:
 *
 ****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <its_app.h>
#include <its_ip_trans.h>
#include <its_kasock_trans.h>
#include <its_imal_trans.h>
#include <its_timers.h>
#include <its_worker.h>

#define FIRST_BORDER    2
#define NUM_BORDER      5

TPOOL *borderPool = NULL;

/*
 * create the IPC transports
 */
static TPOOL_THREAD *
CreateTransports(TPOOL *pool, int stackSize)
{
    WORKER_Control* border;
    char buf[32];
    static int thisBorder = FIRST_BORDER;

    sprintf(buf, "Border %d", thisBorder);

    border = WORKER_InitWorker(stackSize,
                               buf,
                               (ITS_USHORT)thisBorder,
                               ITS_TRANSPORT_IMAL_SOCKET|
                                   ITS_TRANSPORT_SSOCKET_DYN|
                                   ITS_TRANSPORT_DELAY_CREATE|
                                   ITS_TRANSPORT_SSOCKET);

    thisBorder++;

    return (&WORKER_THREAD(border));
}

void
Dispatch(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    ITS_HANDLE h;
    ITS_EVENT event;

    h = ITS_Initialize(WORKER_MASK(work),
                       WORKER_INSTANCE(work));
    assert(h != NULL);

    printf("Entering: %d\n",
           TRANSPORT_INSTANCE(WORKER_TRANSPORT(work)));

    while (!WORKER_THREAD(work).exit)
    {
        if (WORKER_GetNextEvent(work, &event) != ITS_SUCCESS)
        {
            break;
        }

        printf("Got something: %04x\n",
               TRANSPORT_INSTANCE(WORKER_TRANSPORT(work)));
    }
    
    printf("Leaving: %d\n",
           TRANSPORT_INSTANCE(WORKER_TRANSPORT(work)));

    ITS_Terminate(h);
}

int
main(int argc, char **argv)
{
    APPL_SetName("Test26");

    ITS_AddFeature(itsKEEPALIVE_Class);

    ITS_AddFeature(itsIMAL_Class);

    ITS_GlobalStart(0);

    if ((borderPool = TPOOL_InitPool(NULL)) == NULL)
    {
        printf("Fatal error creating IPC transports pool.\n");

        ITS_GlobalStop();

        ITS_RemFeature(itsIMAL_Class);

        ITS_RemFeature(itsKEEPALIVE_Class);

        return (EXIT_FAILURE);
    }

    if (TPOOL_CreatePool(borderPool, NUM_BORDER, 0,
                         CreateTransports) != ITS_SUCCESS)
    {
        printf("Fatal error creating unit-of-work transports pool.\n");

        TPOOL_DestroyPool(borderPool);

        ITS_GlobalStop();

        ITS_RemFeature(itsIMAL_Class);

        ITS_RemFeature(itsKEEPALIVE_Class);

        return (EXIT_FAILURE);
    }

    for (;;)
    {
        SOCKTRAN_Manager *endPoint;
        WORKER_Control *work;

        while ((work = WORKER_InitWorker(0,
                                         "Default-Transport1", 1,
                                         ITS_TRANSPORT_IMAL_SOCKET|
                                             ITS_TRANSPORT_SSOCKET_ITER|
                                             ITS_TRANSPORT_SSOCKET)) == NULL)
        {
            printf("Error creating accept worker\n");

            TIMERS_Sleep(2);
        }

        endPoint = (SOCKTRAN_Manager *)WORKER_TRANSPORT(work);

        printf("Init done\n");

        for (;;)
        {
            WORKER_Control *thr;

            printf("Accepting...\n");

            if (TPOOL_GetFirstAvailThread(borderPool,
                                          (TPOOL_THREAD **)&thr) != ITS_SUCCESS)
            {
                printf("No more threads\n");

                TIMERS_Sleep(2);

                continue;
            }

            if (SOCKTRAN_IterativeAccept(endPoint,
                                         WORKER_NAME(thr),
                                         WORKER_INSTANCE(thr),
                                         WORKER_MASK(thr)) == NULL)
            {
                printf("Accept failure\n");

                TPOOL_ReturnToAvailThreads(borderPool,
                                           (TPOOL_THREAD *)thr);

                TIMERS_Sleep(2);

                continue;
            }

            printf("Dispatching...\n");

            TPOOL_DispatchOnThread((TPOOL_THREAD *)thr,
                                   Dispatch, thr);
        }

        WORKER_DeleteWorker(work);
    }

    ITS_GlobalStop();

    ITS_RemFeature(itsIMAL_Class);

    ITS_RemFeature(itsKEEPALIVE_Class);

    return (0);
}
