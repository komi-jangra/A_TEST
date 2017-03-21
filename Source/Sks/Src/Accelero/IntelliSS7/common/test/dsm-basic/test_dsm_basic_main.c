/*****************************************************************************
 *                                                                           *
 *     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     *
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
 
#ident "$Id: test_dsm_basic_main.c,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $"

#include <time.h>

#include <its.h>
#include <its_app.h>
#include <its_dsm.h>
#include <its_trace.h>
#include <its_assertion.h>
#include <its_timers.h>
#include <its_thread.h>

/*
 * DSM basic tests (without MNT): simple tests, multi-threaded tests and 
 * performance tests.
 *
 * Work with 3 different implementations of DSM:
 *      - Stub.
 *      - GCS (Group Communication System).
 *      - SCI.
 *
 * Most of the tests require to use two machines (i.e. two nodes), where each
 * machine runs a specific part of the test. Typically assertions are used to
 * catch errors (vs. traces).
 */

/* Forward declarations. */

void Test1_Node1();
void Test1_Node2();
void Test2_Node1();
void Test2_Node2();
void Test3_Node1();
void Test3_Node2();
void Test4_Node1();
void Test4_Node2();
void Test5_Node1();
void Test5_Node2();
void Test6_Node1();
void Test6_Node2();
void Test7_Node1();
void Test7_Node2();
void Test8_Node1();
void Test8_Node2();
void Test9_Node1();
void Test9_Node2();
void Test10_Node1();
void Test10_Node2();


void TestInitialization();
void TestTermination();


void
Usage()
{
    printf("\nUsage: test_dsm_gcs \"test#[_node[1|2]]\"\n\n");
}


int 
main(int argc, const char** argv)
{
    int ret;

#if defined(WIN32)
    APPL_SetName("test_dsm_basic_win32");
#else /* !defined(WIN32) */
    APPL_SetName("test_dsm_basic_unix");
#endif /* defined(WIN32) */

    ret = ITS_InitializeClass(itsTRACE_Class);
    ITS_C_ASSERT(ret == ITS_SUCCESS);
    TRACE_UpdateSettings();

    if (argc != 2)
    {
        Usage();
        return -1;
    }

    if (strcmp("test1_node1", argv[1]) == 0)
    {
        Test1_Node1();
    }
    else if (strcmp("test1_node2", argv[1]) == 0)
    {
        Test1_Node2();
    }
    else if (strcmp("test2_node1", argv[1]) == 0)
    {
        Test2_Node1();
    }
    else if (strcmp("test2_node2", argv[1]) == 0)
    {
        Test2_Node2();
    }
    else if (strcmp("test3_node1", argv[1]) == 0)
    {
        Test3_Node1();
    }
    else if (strcmp("test3_node2", argv[1]) == 0)
    {
        Test3_Node2();
    }
    else if (strcmp("test4_node1", argv[1]) == 0)
    {
        Test4_Node1();
    }
    else if (strcmp("test4_node2", argv[1]) == 0)
    {
        Test4_Node2();
    }
    else if (strcmp("test5_node1", argv[1]) == 0)
    {
        Test5_Node1();
    }
    else if (strcmp("test5_node2", argv[1]) == 0)
    {
        Test5_Node2();
    }
    else if (strcmp("test6_node1", argv[1]) == 0)
    {
        Test6_Node1();
    }
    else if (strcmp("test6_node2", argv[1]) == 0)
    {
        Test6_Node2();
    }
    else if (strcmp("test7_node1", argv[1]) == 0)
    {
        Test7_Node1();
    }
    else if (strcmp("test7_node2", argv[1]) == 0)
    {
        Test7_Node2();
    }
    else if (strcmp("test8_node1", argv[1]) == 0)
    {
        Test8_Node1();
    }
    else if (strcmp("test8_node2", argv[1]) == 0)
    {
        Test8_Node2();
    }
    else if (strcmp("test9_node1", argv[1]) == 0)
    {
        Test9_Node1();
    }
    else if (strcmp("test9_node2", argv[1]) == 0)
    {
        Test9_Node2();
    }
    else if (strcmp("test10_node1", argv[1]) == 0)
    {
        Test10_Node1();
    }
    else if (strcmp("test10_node2", argv[1]) == 0)
    {
        Test10_Node2();
    }
    else
    {
        Usage();
        return -1;
    };

    return 0;
}

/*
 * TestInitializationNode1: generic initialization for Node1.
 */
void 
TestInitializationNode1()
{
    int ret;

#if defined(TEST_DSM_GCS)

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_Initialize failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_Initialize succeeded\n");
    }

    ret = ITS_GlobalStart(0); /* Use DSM_ functions. */
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ ITS_GlobalStart failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ ITS_GlobalStart succeeded\n");
    }

    /* 
     * To avoid still using DSM_ functions when joining.
     */
    printf("\n\n@@@ Ready to sleep 1 second\n");
    TIMERS_Sleep(1); 

    ret = DSM_JoinRemote(10000);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_JoinRemote failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_JoinRemote succeeded\n");
    }

    printf("\n\n@@@ Ready to sleep 2 seconds\n");
    TIMERS_Sleep(2);

#elif defined(TEST_DSM_SCI)

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_Initialize failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_Initialize succeeded\n");
    }

    printf("\n\n@@@ Following DSM_JoinRemote should fail...\n");
    ret = DSM_JoinRemote(50);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_JoinRemote failed: %d\n");
    }
    else
    {
        printf("\n\n@@@ DSM_JoinRemote succeeded\n");
    }

    ret = DSM_MarkInitComplete();
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_MarkInitComplete failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_MarkInitComplete succeeded\n");
    }

    printf("\n\n@@@ Ready to sleep 5 seconds (to allow node2 to join)...\n");
    TIMERS_Sleep(5);

#elif defined(TEST_DSM_STUB)

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_Initialize failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_Initialize succeeded\n");
    }

    ret = ITS_GlobalStart(0); /* Use DSM_ functions. */
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ ITS_GlobalStart failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ ITS_GlobalStart succeeded\n");
    }

    /* 
     * To avoid still using DSM_ functions when joining. 
     */
    printf("\n\n@@@ Ready to sleep 1 second\n");
    TIMERS_Sleep(1);

    ret = DSM_JoinRemote(10000);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_JoinRemote failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_JoinRemote succeeded\n");
    }

    printf("\n\n@@@ Ready to sleep 2 seconds\n");
    TIMERS_Sleep(2);

#else
#error "TEST DSM type not defined!"
#endif

}

/*
 * TestInitializationNode2: generic initialization for Node2.
 */
void 
TestInitializationNode2()
{
    int ret;

#if defined(TEST_DSM_GCS)

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_Initialize failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_Initialize succeeded\n");
    }

    ret = ITS_GlobalStart(0); /* Use DSM_ functions. */
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ ITS_GlobalStart failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ ITS_GlobalStart succeeded\n");
    }

    /* 
     * To avoid still using DSM_ functions when joining. Node2 must also be
     * joining after node1.
     */
    printf("\n\n@@@ Ready to sleep 3 second\n");
    TIMERS_Sleep(3);

    ret = DSM_JoinRemote(10000);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_JoinRemote failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_JoinRemote succeeded\n");
    }

    ret = DSM_RequestDmaArea();
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_RequestDmaArea failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_RequestDmaArea succeeded\n");
    }

    ret = DSM_WaitForDmaComplete(10000);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_WaitForDmaComplete failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_WaitForDmaComplete succeeded\n");
    }

    printf("\n\n@@@ Ready to sleep 3 seconds\n");
    TIMERS_Sleep(3);

#elif defined(TEST_DSM_SCI)

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_Initialize failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_Initialize succeeded\n");
    }

    ret = DSM_JoinRemote(10000);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_JoinRemote failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_JoinRemote succeeded\n");
    }

    ret = DSM_RequestDmaArea();
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_RequestDmaArea failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_RequestDmaArea succeeded\n");
    }

    /* Should be a call to DSM_WaitForDmaComplete but does not work. */
    printf("\n\n@@@ Ready to sleep 2 seconds (instead of "
        "DSM_WaitForDmaComplete)\n");
    TIMERS_Sleep(2);

    ret = DSM_MarkInitComplete();
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_MarkInitComplete failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_MarkInitComplete succeeded\n");
    }

    printf("\n\n@@@ Ready to sleep 3 seconds\n");
    TIMERS_Sleep(3);

#elif defined(TEST_DSM_STUB)

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_Initialize failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_Initialize succeeded\n");
    }

    ret = ITS_GlobalStart(0); /* Use DSM_ functions. */
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ ITS_GlobalStart failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ ITS_GlobalStart succeeded\n");
    }

    /* 
     * To avoid still using DSM_ functions when joining. Node2 must also be
     * joining after node1.
     */
    printf("\n\n@@@ Ready to sleep 3 second\n");
    TIMERS_Sleep(3);

    ret = DSM_JoinRemote(10000);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_JoinRemote failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_JoinRemote succeeded\n");
    }

    ret = DSM_RequestDmaArea();
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_RequestDmaArea failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_RequestDmaArea succeeded\n");
    }

    ret = DSM_WaitForDmaComplete(10000);
    if (ret != ITS_SUCCESS)
    {
        printf("\n\n@@@ DSM_WaitForDmaComplete failed: %d\n");
        ITS_C_ASSERT(ITS_FALSE);
    }
    else
    {
        printf("\n\n@@@ DSM_WaitForDmaComplete succeeded\n");
    }

    printf("\n\n@@@ Ready to sleep 3 seconds\n");
    TIMERS_Sleep(3);

#else
#error "TEST DSM type not defined!"
#endif

}

/*
 * TestTerminationNode1: generic termination for Node1.
 */
void 
TestTerminationNode1()
{
#if defined(TEST_DSM_GCS)

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

#elif defined(TEST_DSM_SCI)

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

#elif defined(TEST_DSM_STUB)

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

#else
#error "TEST DSM type not defined!"
#endif

}

/*
 * TestTerminationNode2: generic termination for Node2.
 */
void 
TestTerminationNode2()
{
#if defined(TEST_DSM_GCS)

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

#elif defined(TEST_DSM_SCI)

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

#elif defined(TEST_DSM_STUB)

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

#else
#error "TEST DSM type not defined!"
#endif

}


/*
 * Test1 is a basic test of DSM GCS functionalities:
 *
 * - Initialization of DSM subsystem.
 * - Join remote.
 * - Leave remote.
 * - Termination of DSM subsystem. 
 * - Allocation of one row by node1.
 * - Commit one row by node1.
 * - Find row by node2.
 * - ITS_GlobalStart and ITS_GlobalStop are also used (test of interactions).
 *
 * Node1 must be started first followed by node2 within few seconds.
 */

/* Test1_Node1. */
void 
Test1_Node1()
{
    void* ptr;
    int error;
    int ret;

    printf("\n\n****** Test1 Node1 begin...\n\n");

    TestInitializationNode1();

    ptr = DSM_Alloc(70, (ITS_OCTET*)"abcdef", 6, 1024, &error);
    ITS_C_ASSERT(ptr != NULL);
    ITS_C_ASSERT(error == ITS_SUCCESS);

    memcpy(ptr, "abcdefghijklmnopqrstuvwxyz\0", 27);

    ret = DSM_Commit(70, (ITS_OCTET*)"abcdef", 6, ptr);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(2);

    TestTerminationNode1();

    printf("\n\n****** Test1 Node1 end...\n\n");
}

/* Test1_Node2. */
void
Test1_Node2()
{
    void* ptr;
    int error;

    printf("\n\n****** Test1 Node2 begin...\n\n");

    TestInitializationNode2();

    ptr = DSM_Find(70, (ITS_OCTET*)"abcdef", 6, &error);
    ITS_C_ASSERT(ptr != NULL);
    ITS_C_ASSERT(error == ITS_SUCCESS);

    printf(
        "\n\n****** Retrieved row from table 70 and key <abcdef> is: <%s>."
        "\n\n",
        ptr);

    TIMERS_Sleep(2);

    TestTerminationNode2();

    printf("\n\n****** Test1 Node2 end...\n\n");
}


/*
 * Test2 is similar to Test1 but both tests go into an infinite sleeping loop
 * at the end. This is to allow testing (manually) various scenarios where 
 * node2 dies (use ^C) and join again the GCS later. DSM GCS functionalities
 * tested:
 *
 * - Initialization of DSM subsystem.
 * - Join remote.
 * - Die and join again later.
 * - ITS_GlobalStart is also used (test of interactions).
 *
 * Node1 must be started first followed by node2 within few seconds. After
 * node2 can be killed and restarted at any time.
 *
 */

/* Test2_Node1. */
void 
Test2_Node1()
{
    void* ptr;
    int error;
    int ret;

    printf("\n\n****** Test2 Node1 begin...\n\n");

    ret = DSM_Initialize(1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_GlobalStart(0); /* Use DSM_ functions. */
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(1); /* To avoid still using DSM_ functions when joining. */

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(2);

    ptr = DSM_Alloc(70, (ITS_OCTET*)"abcdef", 6, 1024, &error);
    ITS_C_ASSERT(ptr != NULL);
    ITS_C_ASSERT(error == ITS_SUCCESS);

    memcpy(ptr, "abcdefghijklmnopqrstuvwxyz\0", 27);

    ret = DSM_Commit(70, (ITS_OCTET*)"abcdef", 6, ptr);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    printf(
        "\n\n****** Test2 Node1 ready to go in infinite sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate.\n\n");

    while (1)
    {
        TIMERS_Sleep(30);
    }
}

/* Test2_Node2. */
void
Test2_Node2()
{
    void* ptr;
    int error;
    int ret;

    printf("\n\n****** Test2 Node2 begin...\n");

    ret = DSM_Initialize(1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_GlobalStart(0); /* Use DSM_ functions. */
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* 
     * To avoid still using DSM_ functions when joining. Node2 must also be
     * joining after node1.
     */

    TIMERS_Sleep(3);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_RequestDmaArea();
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_WaitForDmaComplete(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    ptr = DSM_Find(70, (ITS_OCTET*)"abcdef", 6, &error);

    if (ptr != NULL)
    {
        ITS_C_ASSERT(error == ITS_SUCCESS);

        printf("\n\n****** Found row from table 70 and key <abcdef>.\n\n");

        printf(
            "\n\n****** Retrieved row from table 70 and key <abcdef> is: "
            "<%s>.\n\n",
            ptr);
    }
    else
    {
        printf(
            "\n\n****** Unable to found row from table 70 and key "
            "<abcdef>.\n\n");
    }

    printf(
        "\n\n****** Test2 ready to go in infinite sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate.\n\n");

    while (1)
    {
        TIMERS_Sleep(30);
    }
}


/*
 * Test3 is a similar to Test2 but is automatic. Node2 leaves and joins 
 * node1 exactly 10 times and each time retrieve a row (after memory
 * synchronization). DSM GCS functionalities tested:
 * - Initialization of DSM subsystem.
 * - Join remote.
 * - Leave remote.
 * - Termination of DSM subsystem. 
 * - Allocation of one row by node1.
 * - Commit one row by node1.
 * - Find row by node2.
 * 
 * Note that ITS_GlobalStart and ITS_GlobalStop are not used in Test3.
 *
 * Currently Test3 DOES NOT PASS due to the following limitations:
 * 
 * - In GCS Client library there is nothing to terminate (i.e.
 *   GCS_EventInitialize but no GCS_EventTerminate). That leads to 
 *   assert(!(Mem[obj_type].exist)) in memory.c line 319 to be false.
 *
 * - DSM_JoinRemote requires DSM internal state to be DSM_STATE_INITIAL and
 *   after a DSM_LeaveRemote is done DSM internal state is still 
 *   DSM_STATE_TERMINAL. 
 */

/* Test3_Node1. */
void 
Test3_Node1()
{
    void* ptr;
    int error;
    int ret;
    int i;

    printf("\n\n****** Test3 Node1 begin...\n\n");

    ret = DSM_Initialize(1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(1);

    ptr = DSM_Alloc(70, (ITS_OCTET*)"abcdef", 6, 1024, &error);
    ITS_C_ASSERT(ptr != NULL);
    ITS_C_ASSERT(error == ITS_SUCCESS);

    memcpy(ptr, "abcdefghijklmnopqrstuvwxyz\0", 27);

    ret = DSM_Commit(70, (ITS_OCTET*)"abcdef", 6, ptr);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    printf(
        "\n\n****** Test3 ready to go in 60s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 6)
    {
        TIMERS_Sleep(10);

        i++;
    }

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    printf("\n\n****** Test3 Node1 end...\n\n");
}

/* Test3_Node2. */
void
Test3_Node2()
{
    void* ptr;
    int error;
    int ret;
    int i;

    printf("\n\n****** Test3 Node2 begin...\n\n");

    printf("\n\n****** Test3 ready to begin loop...\n\n");

    for (i = 0; i < 10; i++)
    {
        printf("\n\n****** Test3 loop number: <%d>.\n\n", i + 1);

        ret = DSM_Initialize(1024 * 1024, 1);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ret = DSM_JoinRemote(10000);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ret = DSM_RequestDmaArea();
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        if (i == 0)
        {
            TIMERS_Sleep(3);
        }

        ret = DSM_WaitForDmaComplete(10000);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ptr = DSM_Find(70, (ITS_OCTET*)"abcdef", 6, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        printf(
            "\n\n****** Retrieved row from table 70 and key <abcdef> is:"
            " <%s>.\n\n",
            ptr);

        DSM_LeaveRemote();

        DSM_Terminate();
    }

    printf("\n\n****** Test3 Node2 end...\n\n");
}


/* 
 * Test4 is to test allocation by node1 of multiple rows and retrieval of
 * these rows by node2.
 * - Initialization of DSM subsystem.
 * - Join remote.
 * - Leave remote.
 * - Termination of DSM subsystem.
 * - Allocation of multiples row by node1.
 * - Commit of multiples row by node1.
 * - Find (or fail to find) multiples rows by node2.
 * 
 * Node1 must be started first followed by node2 within few seconds. 
 * Alternatively, node2 might be started when node1 has reached the 60s
 * sleeping loop (to test synchronization of memory with multiples rows).
 */

/* Test4_Node1. */
void 
Test4_Node1()
{
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    printf("\n\n****** Test4 Node1 begin...\n\n");

    TestInitializationNode1();

    printf("\n\n****** Test4 ready to begin loop...\n\n");

    /* Insert 128 rows of 1K. */
    for (i = 0; i < 128; i++)
    {
        printf("\n\n****** Test4 loop number: <%d>.\n\n", i);

        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.3dkey", i);
        sprintf(bufData, "%.3ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 6, 1024, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 6, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    printf(
        "\n\n****** Test4 ready to go in 60s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 6)
    {
        TIMERS_Sleep(10);

        i++;
    }

    TestTerminationNode1();

    printf("\n\n****** Test4 Node1 end...\n\n");
}

/* Test4_Node2. */
void
Test4_Node2()
{
    void* ptr;
    char bufKey[32];
    int error;
    int i;

    printf("\n\n****** Test4 Node2 begin...\n\n");

    TestInitializationNode2();

    printf("\n\n****** Test4 ready to sleep 20s...\n\n");

    TIMERS_Sleep(20);

    printf("\n\n****** Test4 ready to begin loop...\n\n");

    for (i = 0; i < 128; i++)
    {
        printf("\n\n****** Test4 loop number: <%d>.\n\n", i + 1);

        memset(bufKey, 0, 32);
        sprintf(bufKey, "%.3dkey", i);

        ptr = DSM_Find(70, (ITS_OCTET*)bufKey, 6, &error);

        if (ptr != NULL)
        {
            ITS_C_ASSERT(error == ITS_SUCCESS);

            printf(
                "\n\n****** Found row from table 70 and key <%s>.\n\n",
                bufKey);

            printf(
                "\n\n****** Retrieved row from table 70 and key <%s> is: "
                "<%s>.\n\n",
                bufKey,
                ptr);
        }
        else
        {
            printf(
                "\n\n****** Unable to found row from table 70 and key "
                "<%s>.\n\n",
                bufKey);
        }
    }

    printf(
        "\n\n****** Test4 ready to go in 30s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 3)
    {
        TIMERS_Sleep(10);

        i++;
    }

    TestTerminationNode2();

    printf("\n\n****** Test4 Node2 end...\n\n");
}


/* 
 * Test5 is a basic test of DSM GCS performance. Node1 allocates 100000 rows
 * of size 128 octets. Node2 is passive (but still the memory is replicated 
 * in node2).
 * - Initialization of DSM subsystem.
 * - Join remote.
 * - Leave remote.
 * - Termination of DSM subsystem.
 * - Allocation of multiples row by node1.
 * - Commit of multiples row by node1.
 * 
 * Node1 must be started first followed by node2 within few seconds. To be
 * relevant for performance, Test5 must be run without any DEBUG traces and
 * obviously everything must be a release build (including GCS Daemon).
 */

/* Test5_Node1. */
void 
Test5_Node1()
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;


    printf("\n\n****** Test5 Node1 begin...\n\n");

    ret = DSM_Initialize(24 * 1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(1);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    printf("\n\n****** Test5 ready to begin insertion loop...\n\n");

    time(&tm);
    printf("\n\n****** Test5 insertion loop start time: %s\n\n", ctime(&tm));

    /* Insert 100000 rows of 128 octets. */
    for (i = 0; i < 100000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5dkey", i);
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    printf("\n\n****** Test5 end of insertion loop...\n\n");

    time(&tm);
    printf("\n\n****** Test5 insertion loop end time: %s\n\n", ctime(&tm));

    printf(
        "\n\n****** Test5 ready to go in 30s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 3)
    {
        TIMERS_Sleep(10);

        i++;
    }

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    printf("\n\n****** Test5 Node1 end...\n\n");
}

/* Test5_Node2. */
void
Test5_Node2()
{
    int ret;
    int i;

    printf("\n\n****** Test5 Node2 begin...\n\n");

    ret = DSM_Initialize(24 * 1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_RequestDmaArea();
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_WaitForDmaComplete(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    printf(
        "\n\n****** Test5 ready to go in 480s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 48)
    {
        TIMERS_Sleep(10);

        i++;
    }


    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    printf("\n\n****** Test5 Node2 end...\n\n");
}


/* 
 * Test6 is similar to Test5 but both nodes allocate (simultaneously) 100000
 * rows of size 128 octets (using 2 different key spaces). Memory is replicated
 * on both nodes.
 * - Initialization of DSM subsystem.
 * - Join remote.
 * - Leave remote.
 * - Termination of DSM subsystem.
 * - Allocation of multiples row by node1.
 * - Commit of multiples row by node1.
 * - Allocation of multiples row by node2.
 * - Commit of multiples row by node2.
 * 
 * Node1 must be started first followed by node2 within few seconds. To be 
 * relevant for performance, Test6 must be run without any DEBUG traces and
 * obviously everything must be a release build (including GCS Daemon).
 */

/* Test6_Node1. */
void 
Test6_Node1()
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;


    printf("\n\n****** Test6 Node1 begin...\n\n");

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(1);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(5);

    printf("\n\n****** Test6 ready to begin insertion loop...\n\n");

    time(&tm);
    printf("\n\n****** Test6 insertion loop start time: %s\n\n", ctime(&tm));

    /* Insert 100000 rows of 128 octets. */
    for (i = 0; i < 100000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d111", i); /* '111' for node1. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    printf("\n\n****** Test6 end of insertion loop...\n\n");

    time(&tm);
    printf("\n\n****** Test6 insertion loop end time: %s\n\n", ctime(&tm));

    printf(
        "\n\n****** Test6 ready to go in 30s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 3)
    {
        TIMERS_Sleep(10);

        i++;
    }

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    printf("\n\n****** Test6 Node1 end...\n\n");
}

/* Test6_Node2. */
void
Test6_Node2()
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    printf("\n\n****** Test6 Node2 begin...\n\n");

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_RequestDmaArea();
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_WaitForDmaComplete(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    printf("\n\n****** Test6 ready to begin insertion loop...\n\n");

    time(&tm);
    printf("\n\n****** Test6 insertion loop start time: %s\n\n", ctime(&tm));

    /* Insert 100000 rows of 128 octets. */
    for (i = 0; i < 100000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d222", i); /* '222' for node2. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    printf("\n\n****** Test6 end of insertion loop...\n\n");

    time(&tm);
    printf("\n\n****** Test6 insertion loop end time: %s\n\n", ctime(&tm));

    printf(
        "\n\n****** Test6 ready to go in 30s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 3)
    {
        TIMERS_Sleep(10);

        i++;
    }

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    printf("\n\n****** Test6 Node2 end...\n\n");
}


/*
 * Test7 is similar to Test5 but node1 uses two threads to allocates 100000
 * rows of size 128 octets. Node2 is passive (but still the memory is
 * replicated in node2).
 * - Initialization of DSM subsystem.
 * - Join remote.
 * - Leave remote.
 * - Termination of DSM subsystem.
 * - Allocation of multiples row by node1 (two threads).
 * - Commit of multiples row by node1 (two threads).
 * 
 * Node1 must be started first followed by node2 within few seconds. To be
 * relevant for performance, Test7 must be run without any DEBUG traces and
 * obviously everything must be a release build (including GCS Daemon).
 */

static ITS_MUTEX test7Node1Lock;

static THREAD_RET_TYPE
Test7_Node1_Thread1_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test7Node1Lock);
    printf(
        "\n\n****** Test7 Thread1 ready to begin insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test7 Thread1 insertion loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test7Node1Lock);

    /* Insert 50000 rows of 128 octets. */
    for (i = 0; i < 50000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d1_1", i); /* 1_1 = Node1 Thread1. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test7Node1Lock);
    printf(
        "\n\n****** Test7 Thread1 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test7 Thread1 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test7Node1Lock);

    THREAD_NORMAL_EXIT;
}

static THREAD_RET_TYPE
Test7_Node1_Thread2_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test7Node1Lock);
    printf(
        "\n\n****** Test7 Thread2 ready to begin insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test7 Thread2 insertion loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test7Node1Lock);

    /* Insert 50000 rows of 128 octets. */
    for (i = 0; i < 50000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d1_2", i); /* 1_2 = Node1 Thread2. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test7Node1Lock);
    printf(
        "\n\n****** Test7 Thread2 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test7 Thread2 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test7Node1Lock);

    THREAD_NORMAL_EXIT;
}

/* Test7_Node1. */
void 
Test7_Node1()
{
    ITS_THREAD thread1;
    ITS_THREAD thread2;
    void* status1;
    void* status2;
    int ret;
    int i;

    printf("\n\n****** Test7 Node1 begin...\n\n");

    MUTEX_CreateMutex(&test7Node1Lock, 0);

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(1);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    printf("\n\n****** Test7 ready to start Thread1 and Thread2...\n\n");

    THREAD_CreateThread(&thread1, 0, Test7_Node1_Thread1_Func, NULL, ITS_TRUE);
    THREAD_CreateThread(&thread2, 0, Test7_Node1_Thread2_Func, NULL, ITS_TRUE);

    MUTEX_AcquireMutex(&test7Node1Lock);
    printf(
        "\n\n****** Test7 ready to wait for Thread1 and Thread2 to finish..."
        "\n\n");
    MUTEX_ReleaseMutex(&test7Node1Lock);

    THREAD_WaitForThread(&thread1, &status1);
    THREAD_WaitForThread(&thread2, &status2);

    printf("\n\n****** Test7 finished to wait for Thread1 and Thread2...\n\n");

    printf(
        "\n\n****** Test7 ready to go in 30s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 3)
    {
        TIMERS_Sleep(10);

        i++;
    }

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    MUTEX_DeleteMutex(&test7Node1Lock);

    printf("\n\n****** Test7 Node1 end...\n\n");
}

/* Test7_Node2. */
void
Test7_Node2()
{
    int ret;
    int i;

    printf("\n\n****** Test7 Node2 begin...\n\n");

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_RequestDmaArea();
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_WaitForDmaComplete(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    printf(
        "\n\n****** Test7 ready to go in 480s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 48)
    {
        TIMERS_Sleep(10);

        i++;
    }


    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    printf("\n\n****** Test7 Node2 end...\n\n");
}


/*
 * Test8 is similar to Test5 but node1 uses four threads to allocates 100000
 * rows of size 128 octets. Node2 is passive (but still the memory is
 * replicated in node2).
 * - Initialization of DSM subsystem.
 * - Join remote.
 * - Leave remote.
 * - Termination of DSM subsystem.
 * - Allocation of multiples row by node1 (two threads).
 * - Commit of multiples row by node1 (two threads).
 * 
 * Node1 must be started first followed by node2 within few seconds. To be
 * relevant for performance, Test8 must be run without any DEBUG traces and
 * obviously everything must be a release build (including GCS Daemon).
 */

static ITS_MUTEX test8Node1Lock;

static THREAD_RET_TYPE
Test8_Node1_Thread1_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test8Node1Lock);
    printf(
        "\n\n****** Test8 Thread1 ready to begin insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test8 Thread1 insertion loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test8Node1Lock);

    /* Insert 25000 rows of 128 octets. */
    for (i = 0; i < 25000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d1_1", i); /* 1_1 = Node1 Thread1. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test8Node1Lock);
    printf(
        "\n\n****** Test8 Thread1 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test8 Thread1 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test8Node1Lock);

    THREAD_NORMAL_EXIT;
}

static THREAD_RET_TYPE
Test8_Node1_Thread2_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test8Node1Lock);
    printf(
        "\n\n****** Test8 Thread2 ready to begin insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test8 Thread2 insertion loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test8Node1Lock);

    /* Insert 25000 rows of 128 octets. */
    for (i = 0; i < 25000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d1_2", i); /* 1_2 = Node1 Thread2. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test8Node1Lock);
    printf(
        "\n\n****** Test8 Thread2 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test8 Thread2 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test8Node1Lock);

    THREAD_NORMAL_EXIT;
}

static THREAD_RET_TYPE
Test8_Node1_Thread3_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test8Node1Lock);
    printf(
        "\n\n****** Test8 Thread3 ready to begin insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test8 Thread3 insertion loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test8Node1Lock);

    /* Insert 25000 rows of 128 octets. */
    for (i = 0; i < 25000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d1_3", i); /* 1_3 = Node1 Thread3. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test8Node1Lock);
    printf(
        "\n\n****** Test8 Thread3 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test8 Thread3 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test8Node1Lock);

    THREAD_NORMAL_EXIT;
}

static THREAD_RET_TYPE
Test8_Node1_Thread4_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test8Node1Lock);
    printf(
        "\n\n****** Test8 Thread4 ready to begin insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test8 Thread4 insertion loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test8Node1Lock);

    /* Insert 25000 rows of 128 octets. */
    for (i = 0; i < 25000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d1_4", i); /* 1_4 = Node1 Thread4. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test8Node1Lock);
    printf(
        "\n\n****** Test8 Thread4 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test8 Thread4 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test8Node1Lock);

    THREAD_NORMAL_EXIT;
}


/* Test8_Node1. */
void 
Test8_Node1()
{
    ITS_THREAD thread1;
    ITS_THREAD thread2;
    ITS_THREAD thread3;
    ITS_THREAD thread4;
    void* status1;
    void* status2;
    void* status3;
    void* status4;
    int ret;
    int i;

    printf("\n\n****** Test8 Node1 begin...\n\n");

    MUTEX_CreateMutex(&test8Node1Lock, 0);

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(1);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    printf("\n\n****** Test8 ready to start Thread 1 to 4...\n\n");

    THREAD_CreateThread(&thread1, 0, Test8_Node1_Thread1_Func, NULL, ITS_TRUE);
    THREAD_CreateThread(&thread2, 0, Test8_Node1_Thread2_Func, NULL, ITS_TRUE);
    THREAD_CreateThread(&thread3, 0, Test8_Node1_Thread3_Func, NULL, ITS_TRUE);
    THREAD_CreateThread(&thread4, 0, Test8_Node1_Thread4_Func, NULL, ITS_TRUE);

    MUTEX_AcquireMutex(&test8Node1Lock);
    printf(
        "\n\n****** Test8 ready to wait for Thread 1 to 2 to finish..."
        "\n\n");
    MUTEX_ReleaseMutex(&test8Node1Lock);

    THREAD_WaitForThread(&thread1, &status1);
    THREAD_WaitForThread(&thread2, &status2);
    THREAD_WaitForThread(&thread3, &status3);
    THREAD_WaitForThread(&thread4, &status4);

    printf("\n\n****** Test8 finished to wait for Thread 1 to 4...\n\n");

    printf(
        "\n\n****** Test8 ready to go in 30s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 3)
    {
        TIMERS_Sleep(10);

        i++;
    }

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    MUTEX_DeleteMutex(&test8Node1Lock);

    printf("\n\n****** Test8 Node1 end...\n\n");
}

/* Test8_Node2. */
void
Test8_Node2()
{
    int ret;
    int i;

    printf("\n\n****** Test8 Node2 begin...\n\n");

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_RequestDmaArea();
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_WaitForDmaComplete(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    printf(
        "\n\n****** Test8 ready to go in 480s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 48)
    {
        TIMERS_Sleep(10);

        i++;
    }


    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    printf("\n\n****** Test8 Node2 end...\n\n");
}


/*
 * Test9 is similar to Test5 but both nodes use two threads to allocates 100000
 * rows of size 128 octets (using 4 different key spaces). Memory is replicated
 * on both nodes.
 * - Initialization of DSM subsystem.
 * - Join remote.
 * - Leave remote.
 * - Termination of DSM subsystem.
 * - Allocation of multiples row by node1 (two threads).
 * - Commit of multiples row by node1 (two threads).
 * - Allocation of multiples row by node2 (two threads).
 * - Commit of multiples row by node2 (two threads).
 * 
 * Node1 must be started first followed by node2 within few seconds. To be
 * relevant for performance, Test9 must be run without any DEBUG traces and
 * obviously everything must be a release build (including GCS Daemon).
 */

static ITS_MUTEX test9Node1Lock;

static THREAD_RET_TYPE
Test9_Node1_Thread1_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test9Node1Lock);
    printf(
        "\n\n****** Test9 Thread1 ready to begin insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test9 Thread1 insertion loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test9Node1Lock);

    /* Insert 50000 rows of 128 octets. */
    for (i = 0; i < 50000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d1_1", i); /* 1_1 = Node1 Thread1. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test9Node1Lock);
    printf(
        "\n\n****** Test9 Thread1 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test9 Thread1 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test9Node1Lock);

    THREAD_NORMAL_EXIT;
}

static THREAD_RET_TYPE
Test9_Node1_Thread2_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test9Node1Lock);
    printf(
        "\n\n****** Test9 Thread2 ready to begin insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test9 Thread2 insertion loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test9Node1Lock);

    /* Insert 50000 rows of 128 octets. */
    for (i = 0; i < 50000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d1_2", i); /* 1_2 = Node1 Thread2. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test9Node1Lock);
    printf(
        "\n\n****** Test9 Thread2 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test9 Thread2 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test9Node1Lock);

    THREAD_NORMAL_EXIT;
}

/* Test9_Node1. */
void 
Test9_Node1()
{
    ITS_THREAD thread1;
    ITS_THREAD thread2;
    void* status1;
    void* status2;
    int i;

    printf("\n\n****** Test9 Node1 begin...\n\n");

    MUTEX_CreateMutex(&test9Node1Lock, 0);

    TestInitializationNode1();

    printf("\n\n****** Test9 ready to start Thread1 and Thread2...\n\n");

    THREAD_CreateThread(&thread1, 0, Test9_Node1_Thread1_Func, NULL, ITS_TRUE);
    THREAD_CreateThread(&thread2, 0, Test9_Node1_Thread2_Func, NULL, ITS_TRUE);

    MUTEX_AcquireMutex(&test9Node1Lock);
    printf(
        "\n\n****** Test9 ready to wait for Thread1 and Thread2 to finish..."
        "\n\n");
    MUTEX_ReleaseMutex(&test9Node1Lock);

    THREAD_WaitForThread(&thread1, &status1);
    THREAD_WaitForThread(&thread2, &status2);

    printf("\n\n****** Test9 finished to wait for Thread1 and Thread2...\n\n");

    printf(
        "\n\n****** Test9 ready to go in 30s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 3)
    {
        TIMERS_Sleep(10);

        i++;
    }

    TestTerminationNode1();

    MUTEX_DeleteMutex(&test9Node1Lock);

    printf("\n\n****** Test9 Node1 end...\n\n");
}

static ITS_MUTEX test9Node2Lock;

static THREAD_RET_TYPE
Test9_Node2_Thread1_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test9Node2Lock);
    printf(
        "\n\n****** Test9 Thread2 ready to begin insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test9 Thread2 insertion loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test9Node2Lock);

    /* Insert 50000 rows of 128 octets. */
    for (i = 0; i < 50000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d2_1", i); /* 2_1 = Node2 Thread1. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test9Node2Lock);
    printf(
        "\n\n****** Test9 Thread2 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test9 Thread2 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test9Node2Lock);

    THREAD_NORMAL_EXIT;
}

static THREAD_RET_TYPE
Test9_Node2_Thread2_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test9Node2Lock);
    printf(
        "\n\n****** Test9 Thread2 ready to begin insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test9 Thread2 insertion loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test9Node2Lock);

    /* Insert 50000 rows of 128 octets. */
    for (i = 0; i < 50000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d2_2", i); /* 2_2 = Node2 Thread2. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 8, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 8, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test9Node2Lock);
    printf(
        "\n\n****** Test9 Thread2 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test9 Thread2 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test9Node2Lock);

    THREAD_NORMAL_EXIT;
}

/* Test9_Node2. */
void
Test9_Node2()
{
    ITS_THREAD thread1;
    ITS_THREAD thread2;
    void* status1;
    void* status2;
    int i;

    printf("\n\n****** Test9 Node2 begin...\n\n");

    MUTEX_CreateMutex(&test9Node2Lock, 0);

    TestInitializationNode2();

    printf("\n\n****** Test9 ready to start Thread1 and Thread2...\n\n");

    THREAD_CreateThread(&thread1, 0, Test9_Node2_Thread1_Func, NULL, ITS_TRUE);
    THREAD_CreateThread(&thread2, 0, Test9_Node2_Thread2_Func, NULL, ITS_TRUE);

    MUTEX_AcquireMutex(&test9Node2Lock);
    printf(
        "\n\n****** Test9 ready to wait for Thread1 and Thread2 to finish..."
        "\n\n");
    MUTEX_ReleaseMutex(&test9Node2Lock);

    THREAD_WaitForThread(&thread1, &status1);
    THREAD_WaitForThread(&thread2, &status2);

    printf("\n\n****** Test9 finished to wait for Thread1 and Thread2...\n\n");

    printf(
        "\n\n****** Test9 ready to go in 30s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 3)
    {
        TIMERS_Sleep(10);

        i++;
    }

    TestTerminationNode2();

    MUTEX_DeleteMutex(&test9Node2Lock);

    printf("\n\n****** Test9 Node2 end...\n\n");
}

/*
 * Test10 is a basic test to verify thread-safety (in one node) of DSM No Lock
 * and DSM Table Lock related functions. Test10 node1 uses two threads to do 
 * various DSM related calls. Node2 is passive (but still the memory is 
 * replicated in node2).
 * - Initialization of DSM subsystem.
 * - Join remote.
 * - Leave remote.
 * - Termination of DSM subsystem.
 * - Table Lock/Unlock.
 * - Alloc, Commit, Find, Free.
 * 
 * Node1 must be started first followed by node2 within few seconds. To be
 * relevant for performance, Test10 must be run without any DEBUG traces and
 * obviously everything must be a release build (including GCS Daemon).
 */

static ITS_MUTEX test10Node1Lock;

static THREAD_RET_TYPE
Test10_Node1_Thread1_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test10Node1Lock);
    printf(
        "\n\n****** Test10 Thread1 ready to begin DSM calls loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test10 Thread1 DSM calls loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test10Node1Lock);

    /* Insert and remove 25000 times a row of 128 octets. */
    for (i = 0; i < 25000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);

        sprintf(bufKey, "fixed1_key", i); /* fixed1 = Node1. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ret = DSM_LockTable(70);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ptr = DSM_AllocNoLock(70, (ITS_OCTET*)bufKey, 10, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_CommitNoLock(70, (ITS_OCTET*)bufKey, 10, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ptr = DSM_FindNoLock(70, (ITS_OCTET*)bufKey, 10, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        ret = DSM_FreeNoLock(70, (ITS_OCTET*)bufKey, 10, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ret = DSM_UnlockTable(70);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test10Node1Lock);
    printf(
        "\n\n****** Test10 Thread1 part 1 done...\n\n");
    MUTEX_ReleaseMutex(&test10Node1Lock);

    /* Insert 25000 rows of 128 octets. */
    for (i = 0; i < 25000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d1_1", i); /* 1_1 = Node1 Thread1. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 9, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 9, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test10Node1Lock);
    printf(
        "\n\n****** Test10 Thread1 part 2 done...\n\n");
    printf(
        "\n\n****** Test10 Thread1 end of DSM calls loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test10 Thread1 DSM calls loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test10Node1Lock);

    THREAD_NORMAL_EXIT;
}

static THREAD_RET_TYPE
Test10_Node1_Thread2_Func(void* arg)
{
    time_t tm;
    void* ptr;
    char bufKey[32];
    char bufData[64];
    int error;
    int ret;
    int i;

    MUTEX_AcquireMutex(&test10Node1Lock);
    printf(
        "\n\n****** Test10 Thread2 ready to begin DSM calls loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test10 Thread2 DSM calls loop start time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test10Node1Lock);

    /* Insert and remove 25000 times a row of 128 octets. */
    for (i = 0; i < 25000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);

        sprintf(bufKey, "fixed1_key", i); /* fixed1 = Node1. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ret = DSM_LockTable(70);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ptr = DSM_AllocNoLock(70, (ITS_OCTET*)bufKey, 10, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_CommitNoLock(70, (ITS_OCTET*)bufKey, 10, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ptr = DSM_FindNoLock(70, (ITS_OCTET*)bufKey, 10, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        ret = DSM_FreeNoLock(70, (ITS_OCTET*)bufKey, 10, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ret = DSM_UnlockTable(70);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test10Node1Lock);
    printf(
        "\n\n****** Test10 Thread2 part 1 done...\n\n");
    MUTEX_ReleaseMutex(&test10Node1Lock);

    /* Insert 25000 rows of 128 octets. */
    for (i = 0; i < 25000; i++)
    {
        memset(bufKey, 0, 32);
        memset(bufData, 0, 64);
        sprintf(bufKey, "%.5d1_2", i); /* 1_2 = Node1 Thread2. */
        sprintf(bufData, "%.5ddata[abcdefghijklmnopqrstuvwxyz]\0", i);

        ptr = DSM_Alloc(70, (ITS_OCTET*)bufKey, 9, 128, &error);
        ITS_C_ASSERT(ptr != NULL);
        ITS_C_ASSERT(error == ITS_SUCCESS);

        memcpy(ptr, bufData, strlen(bufData));

        ret = DSM_Commit(70, (ITS_OCTET*)bufKey, 9, ptr);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    MUTEX_AcquireMutex(&test10Node1Lock);
    printf(
        "\n\n****** Test10 Thread2 part 2 done...\n\n");
    printf(
        "\n\n****** Test10 Thread2 end of insertion loop...\n\n");
    time(&tm);
    printf(
        "\n\n****** Test10 Thread2 insertion loop end time: %s\n\n",
        ctime(&tm));
    MUTEX_ReleaseMutex(&test10Node1Lock);

    THREAD_NORMAL_EXIT;
}

/* Test10_Node1. */
void 
Test10_Node1()
{
    ITS_THREAD thread1;
    ITS_THREAD thread2;
    void* status1;
    void* status2;
    int ret;
    int i;

    printf("\n\n****** Test10 Node1 begin...\n\n");

    MUTEX_CreateMutex(&test10Node1Lock, 0);

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(1);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    printf("\n\n****** Test10 ready to start Thread1 and Thread2...\n\n");

    THREAD_CreateThread(&thread1, 0, Test10_Node1_Thread1_Func, NULL, ITS_TRUE);
    THREAD_CreateThread(&thread2, 0, Test10_Node1_Thread2_Func, NULL, ITS_TRUE);

    MUTEX_AcquireMutex(&test10Node1Lock);
    printf(
        "\n\n****** Test10 ready to wait for Thread1 and Thread2 to finish..."
        "\n\n");
    MUTEX_ReleaseMutex(&test10Node1Lock);

    THREAD_WaitForThread(&thread1, &status1);
    THREAD_WaitForThread(&thread2, &status2);

    printf("\n\n****** Test10 finished to wait for Thread1 and Thread2...\n\n");

    printf(
        "\n\n****** Test10 ready to go in 30s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 3)
    {
        TIMERS_Sleep(10);

        i++;
    }

    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    MUTEX_DeleteMutex(&test10Node1Lock);

    printf("\n\n****** Test10 Node1 end...\n\n");
}

/* Test10_Node2. */
void
Test10_Node2()
{
    int ret;
    int i;

    printf("\n\n****** Test10 Node2 begin...\n\n");

    ret = DSM_Initialize(64 * 1024 * 1024, 1);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    TIMERS_Sleep(3);

    ret = DSM_JoinRemote(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_RequestDmaArea();
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = DSM_WaitForDmaComplete(10000);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    printf(
        "\n\n****** Test10 ready to go in 480s sleeping loop...\n\n");

    printf(
        "\n\n****** Use ^C to terminate early if necessary...\n\n");

    i = 0;
    while (i < 48)
    {
        TIMERS_Sleep(10);

        i++;
    }


    DSM_LeaveRemote();

    ITS_GlobalStop();

    DSM_Terminate();

    printf("\n\n****** Test10 Node2 end...\n\n");
}



