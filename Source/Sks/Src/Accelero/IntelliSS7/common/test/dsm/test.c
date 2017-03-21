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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:34  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:15  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:27  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:55  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:36  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:07  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:16  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 1.7  2001/06/19 18:32:53  mmiers
 * LOG: Fix allocate params.
 * LOG:
 * LOG: Revision 1.6  2001/06/18 22:28:36  ssharma
 * LOG:
 * LOG: Modified to compile with latest changes to its_dsm.h
 * LOG:
 * LOG: Revision 1.5  2001/06/14 21:27:14  mmiers
 * LOG: Oops, 1 second not 1 msec.
 * LOG:
 * LOG: Revision 1.4  2001/06/14 21:26:10  mmiers
 * LOG: Add row test.
 * LOG:
 * LOG: Revision 1.3  2001/06/14 20:19:39  mmiers
 * LOG: Add join to test.
 * LOG:
 * LOG: Revision 1.2  2001/06/14 18:50:45  mmiers
 * LOG: Make it work on both machines
 * LOG:
 * LOG: Revision 1.1  2001/06/14 17:32:41  mmiers
 * LOG: Pass 1.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* #include "dmalloc-4.6.0/dmalloc.h" */
#include <its.h>
#include <its_dsm.h>

#ident "$Id: test.c,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $"

/*
 * global
 */
DSM_Area *dsm;

#define DSM_TEST_KEY 99

/*
 * test the DSM interface
 */
int
main(int argc, char **argv)
{
    int ret, error;
    ITS_UINT lan, rni;
    ITS_OCTET key;
    void *row;

    /*
     * args
     */
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./test <adapterNum> <remoteNode>\n");
        return (0);
    }

    lan = atoi(argv[1]);
    rni = atoi(argv[2]);

    ret = ITS_GlobalStart(0);
    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Global start failed.\n");
        return (0);
    }

    /*
     *    int DSM_Initialize(void *requestedBase,
     *                       ITS_UINT size, 
     *                       ITS_UINT segmentNum,
     *                       ITS_UINT localAdapterNum,
     *                       ITS_UINT remoteNodeId,
     *                       ITS_UINT retryValue);
     */
    ret = DSM_Initialize((void *)0x8000000, 1024*1024, 1, lan, rni, 5);
    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Initialize failed.\n");
        ITS_GlobalStop();
        return (0);
    }

    /* join remote */
    if (DSM_JoinRemote(rni, 1000) != ITS_SUCCESS)
    {
        fprintf(stderr, "JoinRemoteFailed\n");
        DSM_Terminate();
        ITS_GlobalStop();
        return (0);
    }

    /* test the API */
    if (lan == 1)
    {
        TIMERS_Sleep(1);

        key = DSM_TEST_KEY;
        if ((row = DSM_Alloc(0, &key, sizeof(key),
                             strlen("foobar") + 1, &error)) == NULL)
        {
            fprintf(stderr, "Alloc failed\n");
            DSM_LeaveRemote(rni);
            DSM_Terminate();
            ITS_GlobalStop();
            return (0);
        }

        strcpy(row, "foobar");

        if (DSM_Commit(0, &key, sizeof(key), row) != ITS_SUCCESS)
        {
            fprintf(stderr, "Commit failed\n");
            DSM_Free(0, &key, sizeof(key), row);
            DSM_LeaveRemote(rni);
            DSM_Terminate();
            ITS_GlobalStop();
            return (0);
        }
    }
    else
    {
        key = DSM_TEST_KEY;
        TIMERS_Sleep(2);

        if ((row = DSM_Find(0, &key, sizeof(key), &error)) == NULL)
        {
            fprintf(stderr, "Find failed\n");
            DSM_LeaveRemote(rni);
            DSM_Terminate();
            ITS_GlobalStop();
            return (0);
        }

        printf("Row returned: %s\n", row);

        if (DSM_Free(0, &key, sizeof(key), row) != ITS_SUCCESS)
        {
            fprintf(stderr, "Commit failed\n");
            DSM_LeaveRemote(rni);
            DSM_Terminate();
            ITS_GlobalStop();
            return (0);
        }
    }

    printf("Test successful\n");
    TIMERS_Sleep(15);

    DSM_LeaveRemote(rni);
    DSM_Terminate();
    ITS_GlobalStop();
    return (0);
}
