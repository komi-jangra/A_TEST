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
 
#ident "$Id: test_sci_main.c,v 1.1.1.1 2007-10-08 11:12:03 bsccs2 Exp $"

#include <its.h>
#include <its_timers.h>
#include <its_assertion.h>

#include <sisci_api.h>

/* 
 * SCI raw tests. 
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

void TestCommon();

#define PRINT_LINE printf("\n[line: %d] ", __LINE__)


void
Usage()
{
    printf("\nUsage: test_sci \"test#[_node[1|2]]\"\n\n");
}




/*
 * DSM state related (SCI).
 */

enum
{
    DSM_STATE_INITIAL           = 1,
    DSM_STATE_JOINING           = 2,
    DSM_STATE_SYNC_SLAVE        = 3,
    DSM_STATE_SYNC_MASTER       = 4,
    DSM_STATE_OP_ONE_MB         = 5,
    DSM_STATE_OP_TWO_MB         = 6
};




#define NO_FLAGS        0
#define NO_CALLBACK     NULL

sci_error_t     error;
sci_desc_t      sd;

unsigned int    localAdapterNo;
unsigned int    remoteAdapterNo;     
unsigned int    localNodeId;
unsigned int    remoteNodeId;

unsigned int    localSlaveIrtNo;  
unsigned int    remoteSlaveIrtNo; 
unsigned int    localMasterIrtNo; 
unsigned int    remoteMasterIrtNo;
unsigned int    localOpIrtNo;     
unsigned int    remoteOpIrtNo;    


sci_local_interrupt_t   localSlaveIrt;
sci_remote_interrupt_t  remoteSlaveIrt;
sci_local_interrupt_t   localMasterIrt;
sci_remote_interrupt_t  remoteMasterIrt;
sci_local_interrupt_t   localOpIrt;
sci_remote_interrupt_t  remoteOpIrt;

#define DSM_SLAVE_IRT_NO    1
#define DSM_MASTER_IRT_NO   2
#define DSM_OP_IRT_NO       3



/* Need to add some more precise time functions to IntellisS7 support...*/
/* ftime needs to be used. */


/* All timeouts in millisecs. */

#if 0 /* Timeouts used for initial tests (working). */
unsigned int irtJoinTimeout = 1000;
unsigned int irtTriggerTimeout = 1000; /* MUST BE >= 3 * irtWaitTimeout. */
unsigned int irtWaitTimeout = 333;
unsigned int irtConnectTimeout = 500;
unsigned int pingTimeout = 500;

/* 
 * SyncTimeout: need to add the (max) time the slave is trying to trigger
 * the master to the actual synchronization time.
 */
 
unsigned int syncTimeout = 4000; 
#endif /* 0 */


unsigned int irtJoinTimeout = 500;
unsigned int irtTriggerTimeout = 500; /* MUST BE >= 3 * irtWaitTimeout. */
unsigned int irtWaitTimeout = 175;
unsigned int irtConnectTimeout = 250;
unsigned int pingTimeout = 250;

/* 
 * SyncTimeout: need to add the (max) time the slave is trying to trigger
 * the master to the actual synchronization time.
 */
 
unsigned int syncTimeout = 2000; 


/**************************** Note: the following to be added to its_timers.[ch] ******/

typedef struct {
    ITS_TIME secs;
    ITS_TIME usecs;
} ITS_UTime;

ITS_UTime
TIMERS_GetCurrentUTime()
{
    ITS_UTime utime;
    TIMERS_UTime(&utime.secs, &utime.usecs);
    return utime;
}

ITS_UTime
TIMERS_UTimeFromTime(ITS_TIME time)
{
    ITS_UTime utime = 
        { time, 0 };
    return utime;
}

ITS_UTime
TIMERS_UTimeFromSecs(ITS_ULONG secs)
{
    ITS_UTime utime = 
        { secs, 0 };
    return utime;
}

ITS_UTime
TIMERS_UTimeFromMillisecs(ITS_ULONG millisecs)
{
    ITS_UTime utime = 
        { millisecs / MILLISEC_PER_SEC, millisecs % MILLISEC_PER_SEC };
    return utime;
}

ITS_UTime
TIMERS_UTimeFromUsecs(ITS_ULONG usecs)
{
    ITS_UTime utime = 
        { usecs / USEC_PER_SEC, usecs % USEC_PER_SEC };
    return utime;
}


ITS_UTime 
TIMERS_SubUTime(ITS_UTime utime, ITS_UTime delta)
{
    ITS_UTime result;

    result.secs  = utime.secs  - delta.secs;
    result.usecs = utime.usecs - delta.usecs;

    if (result.usecs < 0)
    {
            result.usecs = result.usecs + USEC_PER_SEC;
            result.secs--;
    } 

    return result;
}

ITS_UTime 
TIMERS_AddUTime(ITS_UTime utime, ITS_UTime delta)
{
    ITS_UTime result;

    result.secs  = utime.secs  + delta.secs;
    result.usecs = utime.usecs + delta.usecs;

    if (result.usecs >= USEC_PER_SEC)
    {
            result.usecs = result.usecs - USEC_PER_SEC;
            result.secs++;
    }

    return result;
}

int 
TIMERS_CompareUTime(ITS_UTime utime1, ITS_UTime utime2)
{
    if (utime1.secs  > utime2.secs)
    {
        return 1;
    }
    else if (utime1.secs  < utime2.secs)
    {
        return -1;
    }
    else if (utime1.usecs > utime2.usecs)
    {
        return 1;
    }
    else if (utime1.usecs < utime2.usecs )
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/***********************************************************************************/

sci_error_t GetLocalNodeId(unsigned int localAdapterNo,
                           unsigned int *localNodeId)
{

    sci_query_adapter_t queryAdapter;
    sci_error_t  error;
    unsigned int nodeId;

    queryAdapter.subcommand = SCI_Q_ADAPTER_NODEID;
    queryAdapter.localAdapterNo = localAdapterNo;
    queryAdapter.data = &nodeId; 

    SCIQuery(SCI_Q_ADAPTER,&queryAdapter,NO_FLAGS,&error);

    *localNodeId = nodeId;

    return error;
}


int 
main(int argc, const char** argv)
{
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
    else
    {
        Usage();
        return -1;
    };

    return 0;
}

/* Test1_Node1. */
void 
Test1_Node1()
{
    localAdapterNo  = 0;
    remoteAdapterNo = 0;
    localNodeId     = 4;
    remoteNodeId    = 4;

    localSlaveIrtNo     = DSM_SLAVE_IRT_NO;
    remoteSlaveIrtNo    = DSM_SLAVE_IRT_NO + 16;
    localMasterIrtNo    = DSM_MASTER_IRT_NO;
    remoteMasterIrtNo   = DSM_MASTER_IRT_NO + 16;
    localOpIrtNo        = DSM_OP_IRT_NO;
    remoteOpIrtNo       = DSM_OP_IRT_NO + 16;

    TestCommon();
}

/* Test1_Node2. */
void
Test1_Node2()
{
    localAdapterNo  = 0;
    remoteAdapterNo = 0;
    localNodeId     = 4;
    remoteNodeId    = 4;

    localSlaveIrtNo     = DSM_SLAVE_IRT_NO + 16;
    remoteSlaveIrtNo    = DSM_SLAVE_IRT_NO;
    localMasterIrtNo    = DSM_MASTER_IRT_NO + 16;
    remoteMasterIrtNo   = DSM_MASTER_IRT_NO;
    localOpIrtNo        = DSM_OP_IRT_NO + 16;
    remoteOpIrtNo       = DSM_OP_IRT_NO;

    TestCommon();
}

/* TestCommon. */
void TestCommon()
{
    int dummyLocalNodeId;
    int state;
    ITS_UTime beginTriggerTime;
    ITS_UTime endTriggerTime;


    /*
     * Initializations.
     */


    /* Initialize SCI library. */
    SCIInitialize(NO_FLAGS, &error);
    if (error != SCI_ERR_OK) 
    {
        PRINT_LINE;
        fprintf(stderr, "SCIInitialize failed - Error code: 0x%x\n", error);
        exit(error);
    }

    /* Open SCI file descriptor. */
    SCIOpen(&sd, NO_FLAGS, &error);
    if (error != SCI_ERR_OK) 
    {
        PRINT_LINE;
        fprintf(stderr, "SCIOpen failed - Error code 0x%x\n", error);
        exit(error); 
    }

    error = GetLocalNodeId(localAdapterNo, &dummyLocalNodeId);

    /* Create local slave interrupt. */
    SCICreateInterrupt(
        sd, 
        &localSlaveIrt, 
        localAdapterNo, 
        &localSlaveIrtNo, 
        NO_CALLBACK, 
        NULL, 
        SCI_FLAG_FIXED_INTNO, 
        &error);
    if (error == SCI_ERR_OK) 
    {
        PRINT_LINE; 
        printf("Created interrupt with interrupt no (%u)\n", localSlaveIrtNo);
    } 
    else 
    {
        PRINT_LINE;
        fprintf(stderr,"SCICreateInterrupt failed - Error code 0x%x\n",error);
        exit(error);
    }

    /* Create local master interrupt. */
    SCICreateInterrupt(
        sd, 
        &localMasterIrt, 
        localAdapterNo, 
        &localMasterIrtNo, 
        NO_CALLBACK, 
        NULL, 
        SCI_FLAG_FIXED_INTNO, 
        &error);
    if (error == SCI_ERR_OK) 
    {
        PRINT_LINE;
        printf("Created interrupt with interrupt no (%u)\n", localMasterIrtNo);
    } 
    else 
    {
        PRINT_LINE;
        fprintf(stderr,"SCICreateInterrupt failed - Error code 0x%x\n",error);
        exit(error);
    }

    /* Create local operational interrupt. */
    SCICreateInterrupt(
        sd, 
        &localOpIrt, 
        localAdapterNo, 
        &localOpIrtNo, 
        NO_CALLBACK, 
        NULL, 
        SCI_FLAG_FIXED_INTNO, 
        &error);
    if (error == SCI_ERR_OK) 
    {
        PRINT_LINE;
        printf("Created interrupt with interrupt no (%u)\n", localOpIrtNo);
    } 
    else 
    {
        PRINT_LINE;
        fprintf(stderr,"SCICreateInterrupt failed - Error code 0x%x\n",error);
        exit(error);
    } 

    /* Proceeding like if DSM_JoinFtGroup has already been called... */
    state = DSM_STATE_JOINING; 

    while (1) /* In true implementation should be !exit. */
    {
        printf("\nLoop starting: current state is %d\n", state);

        switch (state)
        {
        case DSM_STATE_INITIAL:
            break;

        case DSM_STATE_JOINING:
            {
                SCIWaitForInterrupt(localSlaveIrt, irtJoinTimeout, NO_FLAGS, &error);
                if (error == SCI_ERR_TIMEOUT)
                {
                    PRINT_LINE;
                    printf("State transition to OP_ONE_MB\n");
                    state = DSM_STATE_OP_ONE_MB;
                }
                else if (error == SCI_ERR_OK)
                {
                    SCIConnectInterrupt(
                        sd,
                        &remoteMasterIrt,
                        remoteNodeId,
                        localAdapterNo,
                        remoteMasterIrtNo,
                        irtConnectTimeout,
                        NO_FLAGS,
                        &error);
                    if (error != SCI_ERR_OK)
                    {
                        PRINT_LINE;
                        printf("State transition to OP_ONE_MB\n");
                        state = DSM_STATE_OP_ONE_MB;
                        break;
                    }

                    
                    /* Trigger remote master interrupt. */
                    beginTriggerTime = TIMERS_GetCurrentUTime();

                    endTriggerTime = 
                        TIMERS_AddUTime(
                            beginTriggerTime, 
                            TIMERS_UTimeFromMillisecs(irtTriggerTimeout));

                    do
                    {
                        SCITriggerInterrupt(remoteMasterIrt, NO_FLAGS, &error);
                        if (error != SCI_ERR_OK)
                        {
                            PRINT_LINE;
                            fprintf(stderr, "SCITriggerInterrupt failed - Error code 0x%x\n", error);
                            /* Do we want to go to DSM_STATE_OP_ONE_MB? */
                            break;
                        }   

                        TIMERS_USleep(250 * USEC_PER_MILLISEC); /* Sleep 250 ms. */
                    }
                    while (TIMERS_CompareUTime(TIMERS_GetCurrentUTime(), endTriggerTime) <= 0);

                    /* Ignore errors. */
                    SCIDisconnectInterrupt(remoteMasterIrt, NO_FLAGS, &error);

                    PRINT_LINE;
                    printf("State transition to SYNC_SLAVE\n");
                    state = DSM_STATE_SYNC_SLAVE;
                }
                else
                {
                    PRINT_LINE;
                    fprintf(stderr, "SCIWaitForInterrupt failed - Error code 0x%x\n", error);
                    exit(error);
                }
            }
            break;

        case DSM_STATE_SYNC_SLAVE:
            {
                SCIWaitForInterrupt(localSlaveIrt, syncTimeout, NO_FLAGS, &error);
                if (error == SCI_ERR_TIMEOUT)
                {
                    PRINT_LINE;
                    printf("State transition to OP_ONE_MB\n");
                    state = DSM_STATE_OP_ONE_MB;
                }
                else if (error == SCI_ERR_OK)
                {
                    PRINT_LINE;
                    printf("State transition to OP_TWO_MB\n");
                    state = DSM_STATE_OP_TWO_MB;     
                }
                else
                {
                    PRINT_LINE;
                    fprintf(stderr, "SCIWaitForInterrupt failed - Error code 0x%x\n", error);
                    exit(error);
                }
            }
            break;


        case DSM_STATE_SYNC_MASTER:
            {
                /* 
                 * To be sure that slave is waiting for interrupt 
                 * (and not still triggering the master). 
                 */

                TIMERS_USleep(irtTriggerTimeout * USEC_PER_MILLISEC);

                /* This is where the master is suppose to sync its memory with the slave. */

                /* When finished need to tell the slave by triggering interrupt. */

                /* The slave should be waiting for that interrupt... */
                SCIConnectInterrupt(
                    sd,
                    &remoteSlaveIrt,
                    remoteNodeId,
                    localAdapterNo,
                    remoteSlaveIrtNo,
                    irtConnectTimeout,
                    NO_FLAGS,
                    &error);
                if (error != SCI_ERR_OK)
                {
                    PRINT_LINE;
                    printf("State transition to OP_ONE_MB\n");
                    state = DSM_STATE_OP_ONE_MB;
                }

                /* Trigger remote slave interrupt. */
                SCITriggerInterrupt(remoteSlaveIrt, NO_FLAGS, &error);
                if (error != SCI_ERR_OK)
                {
                    PRINT_LINE;
                    printf("State transition to OP_ONE_MB\n");
                    state = DSM_STATE_OP_ONE_MB;
                }

                /* Ignore errors. */
                SCIDisconnectInterrupt(remoteSlaveIrt, NO_FLAGS, &error);

                PRINT_LINE;
                printf("State transition to OP_TWO_MB\n");
                state = DSM_STATE_OP_TWO_MB;
            }
            break;


        case DSM_STATE_OP_ONE_MB:
            {
                SCIConnectInterrupt(
                    sd,
                    &remoteSlaveIrt,
                    remoteNodeId,
                    localAdapterNo,
                    remoteSlaveIrtNo,
                    irtConnectTimeout,
                    NO_FLAGS,
                    &error);
                if (error == SCI_ERR_OK)
                {
                    /* Ignore errors. */
                    SCITriggerInterrupt(remoteSlaveIrt, NO_FLAGS, &error);
                    
                    /* Ignore errors. */
                    SCIDisconnectInterrupt(remoteSlaveIrt, NO_FLAGS, &error);
                }

                SCIWaitForInterrupt(localMasterIrt, irtWaitTimeout, NO_FLAGS, &error);
                if (error == SCI_ERR_TIMEOUT)
                {
                    /* Nothing to do. Just continue the loop. */
                }
                else if (error == SCI_ERR_OK)
                {
                    SCIConnectInterrupt(
                        sd,
                        &remoteSlaveIrt,
                        remoteNodeId,
                        localAdapterNo,
                        remoteSlaveIrtNo,
                        irtConnectTimeout,
                        NO_FLAGS,
                        &error);
                    if (error == SCI_ERR_OK)
                    {
                        /* Trigger remote slave interrupt. */
                        beginTriggerTime = TIMERS_GetCurrentUTime();

                        endTriggerTime = 
                            TIMERS_AddUTime(
                                beginTriggerTime, 
                                TIMERS_UTimeFromMillisecs(irtTriggerTimeout));

                        do
                        {
                            SCITriggerInterrupt(remoteSlaveIrt, NO_FLAGS, &error);
                            if (error != SCI_ERR_OK)
                            {
                                PRINT_LINE;
                                fprintf(stderr, "SCITriggerInterrupt failed - Error code 0x%x\n", error);
                                /* Do we want to stay in DSM_STATE_OP_ONE_MB? */
                                break;
                            }   

                            TIMERS_USleep(250 * USEC_PER_MILLISEC); /* Sleep 250 ms. */
                        }
                        while (TIMERS_CompareUTime(TIMERS_GetCurrentUTime(), endTriggerTime) <= 0);

                        PRINT_LINE;
                        printf("State transition to SYNC_MASTER\n");
                        state = DSM_STATE_SYNC_MASTER;

                        /* Ignore errors. */
                        SCIDisconnectInterrupt(remoteSlaveIrt, NO_FLAGS, &error);
                    }
                    else
                    {
                        /* Nothing to do: stay in OP_ONE_MB. */
                    }
                }
                else
                {
                    PRINT_LINE;
                    fprintf(stderr, "SCIWaitForInterrupt failed - Error code 0x%x\n", error);
                    exit(error);
                }

                if (state == DSM_STATE_SYNC_MASTER)
                {
                    break;
                }

                SCIConnectInterrupt(
                    sd,
                    &remoteMasterIrt,
                    remoteNodeId,
                    localAdapterNo,
                    remoteMasterIrtNo,
                    irtConnectTimeout,
                    NO_FLAGS,
                    &error);
                if (error == SCI_ERR_OK)
                {
                    /* Ignore errors. */
                    SCITriggerInterrupt(remoteMasterIrt, NO_FLAGS, &error);
                    
                    /* Ignore errors. */
                    SCIDisconnectInterrupt(remoteMasterIrt, NO_FLAGS, &error);
                }

                SCIWaitForInterrupt(localSlaveIrt, irtWaitTimeout, NO_FLAGS, &error);
                if (error == SCI_ERR_TIMEOUT)
                {
                    /* Nothing to do. Just continue the loop. */
                }
                else if (error == SCI_ERR_OK)
                {
                    SCIConnectInterrupt(
                        sd,
                        &remoteMasterIrt,
                        remoteNodeId,
                        localAdapterNo,
                        remoteMasterIrtNo,
                        irtConnectTimeout,
                        NO_FLAGS,
                        &error);
                    if (error == SCI_ERR_OK)
                    {
                        /* Trigger remote master interrupt. */
                        beginTriggerTime = TIMERS_GetCurrentUTime();

                        endTriggerTime = 
                            TIMERS_AddUTime(
                                beginTriggerTime, 
                                TIMERS_UTimeFromMillisecs(irtTriggerTimeout));

                        do
                        {
                            SCITriggerInterrupt(remoteMasterIrt, NO_FLAGS, &error);
                            if (error != SCI_ERR_OK)
                            {
                                PRINT_LINE;
                                fprintf(stderr, "SCITriggerInterrupt failed - Error code 0x%x\n", error);
                                /* Do we want to stay in DSM_STATE_OP_ONE_MB? */
                                break;
                            }   

                            TIMERS_USleep(250 * USEC_PER_MILLISEC); /* Sleep 250 ms. */
                        }
                        while (TIMERS_CompareUTime(TIMERS_GetCurrentUTime(), endTriggerTime) <= 0);

                        PRINT_LINE;
                        printf("State transition to SYNC_SYNC_SLAVE\n");
                        state = DSM_STATE_SYNC_SLAVE;

                        /* Ignore errors. */
                        SCIDisconnectInterrupt(remoteMasterIrt, NO_FLAGS, &error);
                    }
                    else
                    {
                        /* Nothing to do: stay in OP_ONE_MB. */
                    }
                }
                else
                {
                    PRINT_LINE;
                    fprintf(stderr, "SCIWaitForInterrupt failed - Error code 0x%x\n", error);
                    exit(error);
                }

                if (state == DSM_STATE_SYNC_SLAVE)
                {
                    break;
                }
            }
            break;

        case DSM_STATE_OP_TWO_MB:
            {
                unsigned int missCount = 0;

                SCIConnectInterrupt(
                    sd,
                    &remoteOpIrt,
                    remoteNodeId,
                    localAdapterNo,
                    remoteOpIrtNo,
                    irtConnectTimeout,
                    NO_FLAGS,
                    &error);
                if (error != SCI_ERR_OK)
                {
                    PRINT_LINE;
                    printf("State transition to OP_ONE_MB\n");
                    state = DSM_STATE_OP_ONE_MB;
                    break;
                }

                while (1) /* In true implementation should be !exit. */
                {
                    printf("\nLoop: current state is %d\n", state);

                    SCITriggerInterrupt(remoteOpIrt, NO_FLAGS, &error);
                    if (error != SCI_ERR_OK)
                    {
                        PRINT_LINE;
                        fprintf(stderr, "SCITriggerInterrupt failed - Error code 0x%x\n", error);
                        /* Continue, the missCount will stop the loop if necessary. */
                    }

                    SCIWaitForInterrupt(localOpIrt, pingTimeout * 2, NO_FLAGS, &error);
                    if (error == SCI_ERR_TIMEOUT)
                    {
                        missCount++;
                        if (missCount >= 3)
                        {
                            PRINT_LINE;
                            printf("State transition to OP_ONE_MB\n");
                            state = DSM_STATE_OP_ONE_MB;
                            break;
                        }
                    }
                    else if (error == SCI_ERR_OK)
                    {
                        /* Nothing to do continue. */
                    }
                    else
                    {
                        PRINT_LINE;
                        fprintf(stderr, "SCIWaitForInterrupt failed - Error code 0x%x\n", error);
                        exit(error);
                    }

                    /* Sleep for Ping... */
                    /* Note: some much processing (locks... might have to be somewhere.) */
                    /* Need to measure the time they take and remove that from the pingTimeout. */

                    TIMERS_USleep(pingTimeout * USEC_PER_MILLISEC);
                }

                /* Ignore errors. */
                SCIDisconnectInterrupt(remoteOpIrt, NO_FLAGS, &error);
            }
            break;

        default:
            {
                PRINT_LINE;
                fprintf(stderr, "Must not be reached...\n");
                exit(-1);
            }
        }
    }
}


