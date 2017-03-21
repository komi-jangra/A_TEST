/*****************************************************************************
 *                                                                           *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *             Manufactured in the United States of America.                 *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                           *
 *   This product and related documentation is protected by copyright and    *
 *   distributed under licenses restricting its use, copying, distribution   *
 *   and decompilation.  No part of this product or related documentation    *
 *   may be reproduced in any form by any means without prior written        *
 *   authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                           *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *   government is subject to restrictions as set forth in subparagraph      *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                           *
 *****************************************************************************
 *                                                                           *
 * CONTRACT: INTERNAL                                                        *
 *                                                                           *
 *****************************************************************************/
 
#ident "$Id: dsm_sample1_main.c,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $"


#include <engine.h>


/* Required to export functions (even if within executable). */
#if defined(WIN32)
#define DLLEXPORT __declspec(dllexport)
#else /* !defined(WIN32) */
#define DLLEXPORT
#endif /* defined(WIN32) */

static ITS_BOOLEAN node1JoinedG = ITS_FALSE;
static ITS_BOOLEAN node2JoinedG = ITS_FALSE;

DLLEXPORT void
MembershipChangeCb(
    ITS_POINTER object,
    ITS_POINTER userData,
    ITS_POINTER callData)
{
    DSM_MembershipChangeCbData* 
        membershipChangeCbData =
            (DSM_MembershipChangeCbData*)callData;

    if (membershipChangeCbData->memberNodeId == 1)
    {
        if (membershipChangeCbData->
                membershipChangeType == 
                    DSM_FT_GROUP_MEMBER_JOIN)
        {
            node1JoinedG = ITS_TRUE;
        }
        else if (membershipChangeCbData->
                    membershipChangeType ==
                        DSM_FT_GROUP_MEMBER_LEAVE)
        {
            node1JoinedG = ITS_FALSE;
        }
        else
        {
            /* Ignore. */
        }
    }
    else if (membershipChangeCbData->memberNodeId == 2)
    {
        if (membershipChangeCbData->
                membershipChangeType == 
                    DSM_FT_GROUP_MEMBER_JOIN)
        {
            node2JoinedG = ITS_TRUE;
        }
        else if (membershipChangeCbData->
                    membershipChangeType ==
                        DSM_FT_GROUP_MEMBER_LEAVE)
        {
            node2JoinedG = ITS_FALSE;
        }
        else
        {
            /* Ignore. */
        }
    }
    else
    {
        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ITS_C_ASSERT(must_not_be_reached);
    }
}

static ITS_THREAD userThreadG;

static THREAD_RET_TYPE
UserThreadFunc(void* arg)
{
    void* ptr;
    int error;
    int ret;

    printf("\nInside thread function...\n\n");

    if (strstr(APPL_GetName(), "node1"))
    {
       /***********************************************************************
        *
        * Begin node 1 role.
        *
        */

        /*
         * Node1 role: 
         * - Wait for node2 to join.
         * - Allocate and commit row.
         */

        printf("\nRunning with node1 role...\n\n");

        /* Polling (waiting for Node2 to join). */
        while (!node2JoinedG && !SERVICE_IsStopped())
        {
            printf("\nNode1 waiting for node2 to join...\n\n");
            TIMERS_Sleep(2);
        }

        if (SERVICE_IsStopped())
        {
            THREAD_NORMAL_EXIT;
        }

        ptr = DSM_Alloc(0, 70, (ITS_OCTET*)"abcdef", 6, 1024, &error);
        if (ptr != NULL && error == ITS_SUCCESS)
        {
            printf("\nNode1 succeeded to allocate row...\n\n");
        }
        else
        {
            printf("\nNode1 failed to allocate row...\n\n");

            printf("\nNode1 to exit user thread...\n\n");
            THREAD_NORMAL_EXIT;
        }

        memcpy(ptr, "abcdefghijklmnopqrstuvwxyz\0", 27);

        ret = DSM_Commit(0, 70, (ITS_OCTET*)"abcdef", 6, ptr);
        if (ret == ITS_SUCCESS)
        {
            printf("\nNode1 succeeded to commit row...\n\n");
        }
        else
        {
            printf("\nNode1 failed to commit row...\n\n");

            printf("\nNode1 to exit user thread...\n\n");
            THREAD_NORMAL_EXIT;
        }

       /*
        *
        * End node 1 role.
        *
        **********************************************************************/
    }
    else if (strstr(APPL_GetName(), "node2"))
    {
       /***********************************************************************
        *
        * Begin node 2 role.
        *
        */

        /*
         * Node2 role: 
         * - Sleep 2 seconds (to allow node1 to alloc and commit row).
         * - find and free row.
         */

        printf("\nRunning with node2 role...\n\n");

        TIMERS_Sleep(2);

        ptr = DSM_Find(0, 70, (ITS_OCTET*)"abcdef", 6, &error);
        if (ptr != NULL && error == ITS_SUCCESS)
        {
            printf("\nNode2 succeeded to find row...\n\n");
        }
        else
        {
            printf("\nNode2 failed to find row...\n\n");

            printf("\nNode2 to exit user thread...\n\n");
            THREAD_NORMAL_EXIT;
        }

        printf("\nNode2 retrieved row content is: <%s>...\n\n", ptr);

        ret = DSM_Free(0, 70, (ITS_OCTET*)"abcdef", 6, ptr);
        if (ret == ITS_SUCCESS)
        {
            printf("\nNode2 succeeded to free row...\n\n");
        }
        else
        {
            printf("\nNode2 failed to free row...\n\n");

            printf("\nNode2 to exit user thread...\n\n");
            THREAD_NORMAL_EXIT;
        }

       /*
        *
        * End node 2 role.
        *
        **********************************************************************/
    }
    else
    {
        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ITS_C_ASSERT(must_not_be_reached);
    }

    while (!SERVICE_IsStopped())
    {
        printf("\nUser thread running (use ^C to stop application)...\n\n");
        TIMERS_Sleep(2);
    }

    THREAD_NORMAL_EXIT;
}

DLLEXPORT void
UserPreFunc()
{
    int ret = THREAD_CreateThread(
                            &userThreadG, 
                            0, 
                            UserThreadFunc, 
                            NULL, 
                            ITS_TRUE);
    if (ret != ITS_SUCCESS)
    {
        printf("\nTHREAD_CreateThread failed: %d\n\n", ret);
    }
}

DLLEXPORT void
UserPostFunc()
{
    THREAD_DeleteThread(&userThreadG);
}

int 
main(int argc, const char** argv)
{
    ENGINE_Initialize(argc, argv, NULL, 0);

    ENGINE_Run(argc, argv);

    return 0;
}

