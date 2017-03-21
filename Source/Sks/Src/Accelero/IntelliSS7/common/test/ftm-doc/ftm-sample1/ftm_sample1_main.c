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
 
#ident "$Id: ftm_sample1_main.c,v 1.1.1.1 2007-10-08 11:12:03 bsccs2 Exp $"


#include <engine.h>


/* Required to export functions (even if within executable). */
#if defined(WIN32)
#define DLLEXPORT __declspec(dllexport)
#else /* !defined(WIN32) */
#define DLLEXPORT
#endif /* defined(WIN32) */

/* Membership change callback for a specific FtGroup. */
DLLEXPORT void
MembershipChangeCb(
    ITS_POINTER object,
    ITS_POINTER userData,
    ITS_POINTER callData)
{
    DSM_MembershipChangeCbData* 
        membershipChangeCbData =
            (DSM_MembershipChangeCbData*)callData;
    ITS_USHORT i;

    printf("\nBegin MembershipChangeCallback...\n\n");

    printf(
        "\nFtGroupId is %d...\n\n",
        membershipChangeCbData->ftGroupId);

    switch (membershipChangeCbData->membershipChangeType)
    {
    case DSM_FT_GROUP_MEMBER_ALIVE:
        printf(
            "\nNode%d Process%d alive...\n\n", 
            membershipChangeCbData->memberNodeId,
            membershipChangeCbData->memberProcessId);
        break;

    case DSM_FT_GROUP_MEMBER_JOIN:
        printf(
            "\nNode%d Process%d join...\n\n", 
            membershipChangeCbData->memberNodeId,
            membershipChangeCbData->memberProcessId);
        break;

    case DSM_FT_GROUP_MEMBER_LEAVE:
        printf(
            "\nNode%d Process%d leave...\n\n", 
            membershipChangeCbData->memberNodeId,
            membershipChangeCbData->memberProcessId);
        break;

    case DSM_FT_GROUP_MEMBER_DEAD:
        printf(
            "\nNode%d Process%d dead...\n\n", 
            membershipChangeCbData->memberNodeId,
            membershipChangeCbData->memberProcessId);
        break;

    default:
        {
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);
            break;
        }
    }

    printf("\nFtGroupMembers (nodeId, processId): ");
    for (i = 0; i < membershipChangeCbData->numFtGroupMembers; i++)
    {
        if (i > 0)
        {
            printf(" - ");
        }

        printf(
            "(%d, %d)",
            membershipChangeCbData->ftGroupMembers[i].nodeId,
            membershipChangeCbData->ftGroupMembers[i].processId);
    }
    printf("\n\n");

    printf("\nEnd MembershipChangeCallback...\n\n");
}

/* Membership change callback for all FtGroups. */
DLLEXPORT void
MembershipChangeAllFtGroupsCb(
    ITS_POINTER object,
    ITS_POINTER userData,
    ITS_POINTER callData)
{
    FTM_MembershipChangeAllFtGroupsCbData* 
        membershipChangeAllFtGroupsCbData =
            (FTM_MembershipChangeAllFtGroupsCbData*)callData;
    ITS_USHORT i;

    printf("\nBegin MembershipChangeAllFtGroupsCallback...\n\n");

    printf(
        "\nFtGroupId is %d...\n\n",
        membershipChangeAllFtGroupsCbData->ftGroupId);

    switch (membershipChangeAllFtGroupsCbData->membershipChangeType)
    {
    case DSM_FT_GROUP_MEMBER_ALIVE:
        printf(
            "\nNode%d Process%d alive...\n\n", 
            membershipChangeAllFtGroupsCbData->memberNodeId,
            membershipChangeAllFtGroupsCbData->memberProcessId);
        break;

    case DSM_FT_GROUP_MEMBER_JOIN:
        printf(
            "\nNode%d Process%d join...\n\n", 
            membershipChangeAllFtGroupsCbData->memberNodeId,
            membershipChangeAllFtGroupsCbData->memberProcessId);
        break;

    case DSM_FT_GROUP_MEMBER_LEAVE:
        printf(
            "\nNode%d Process%d leave...\n\n", 
            membershipChangeAllFtGroupsCbData->memberNodeId,
            membershipChangeAllFtGroupsCbData->memberProcessId);
        break;

    case DSM_FT_GROUP_MEMBER_DEAD:
        printf(
            "\nNode%d Process%d dead...\n\n", 
            membershipChangeAllFtGroupsCbData->memberNodeId,
            membershipChangeAllFtGroupsCbData->memberProcessId);
        break;

    default:
        {
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);
            break;
        }
    }

    printf("\nFtGroupMembers (nodeId, processId): ");
    for (i = 0; i < membershipChangeAllFtGroupsCbData->numFtGroupMembers; i++)
    {
        if (i > 0)
        {
            printf(" - ");
        }

        printf(
            "(%d, %d)",
            membershipChangeAllFtGroupsCbData->ftGroupMembers[i].nodeId,
            membershipChangeAllFtGroupsCbData->ftGroupMembers[i].processId);
    }
    printf("\n\n");

    printf("\nEnd MembershipChangeAllFtGroupsCallback...\n\n");
}



/* Sample FTM context data structure. */
typedef struct
{
    int field1;
    int field2;
    int field3;
} FtmContext;

/* Sample FTM context instance. */
FtmContext ftmContext = { 1, 2, 3 };


DLLEXPORT void
FtmPreExecuteLogicProc()
{
    printf("\nBegin FtmPreExecuteLogicProc...\n\n");

    /* How to set FTM context. */
    FTM_SetContext((void*)&ftmContext);


    printf("\nEnd FtmPreExecuteLogicProc...\n\n");
}

DLLEXPORT void
FtmLoopExecuteLogicProc()
{
    int ret;

    /* How to retrieve FTM context. */
    FtmContext* retrievedFtmContext = (FtmContext*)FTM_GetContext();

    printf("\nBegin FtmLoopExecuteLogicProc...\n\n");

    /* Wait for 1 second. */
    ret = FTM_WaitForTerminationWithTimeout(1000);
    if (ret == ITS_ETIMEOUT)
    {
        printf("\nFTM_WaitForTerminationWithTimeout timeout...\n\n");
    }
    else if (ret == ITS_SUCCESS)
    {
        printf("\nFTM_WaitForTerminationWithTimeout success...\n\n");
    }
    else
    {
        printf("\nFTM_WaitForTerminationWithTimeout error: %d...\n\n", ret);
    }

    printf("\nEnd FtmLoopExecuteLogicProc...\n\n");
}

DLLEXPORT void
FtmPostExecuteLogicProc()
{
    /* How to retrieve FTM context. */
    FtmContext* retrievedFtmContext = (FtmContext*)FTM_GetContext();

    printf("\nBegin FtmPostExecuteLogicProc...\n\n");


    printf("\nEnd FtmPostExecuteLogicProc...\n\n");
}

int 
main(int argc, const char** argv)
{
    ENGINE_Initialize(argc, argv, NULL, 0);

    ENGINE_Run(argc, argv);

    return 0;
}

