/******************************************************************************
 *                                                                            *
 *  Copyright 2001 - 2002 IntelliNet Technologies, Inc. All Rights Reserved.  *
 *             Manufactured in the United States of America.                  *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.         *
 *                                                                            *
 *   This product and related documentation is protected by copyright and     *
 *   distributed under licenses restricting its use, copying, distribution    *
 *   and decompilation.  No part of this product or related documentation     *
 *   may be reproduced in any form by any means without prior written         *
 *   authorization of IntelliNet Technologies and its licensors, if any.      *
 *                                                                            *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        *
 *   government is subject to restrictions as set forth in subparagraph       *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software         *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                          *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 ******************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:24  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:09  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:13  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:24  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:51:40  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.10.1.10.2  2004/12/29 09:56:41  ssingh
 * LOG: Revision 7.3.10.1.10.1 corrected.
 * LOG:
 * LOG: Revision 7.3.10.1.10.1  2004/12/15 17:16:44  kannanp
 * LOG: Changes propagated from SHIM
 * LOG:
 * LOG: Revision 7.3.10.1  2004/01/05 09:27:10  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.3.6.1  2003/09/05 10:23:32  akumar
 * LOG: Message based redundnacy commit.
 * LOG:
 * LOG: Revision 7.3.4.1  2003/08/30 16:58:19  randresol
 * LOG: Add Logic for Message based redundnacy
 * LOG:
 * LOG: Revision 7.3  2003/01/30 22:00:50  mmiers
 * LOG: Some fixups.  More work on selectable table types.
 * LOG:
 * LOG: Revision 7.2  2003/01/30 20:46:12  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.4  2002/05/15 19:42:01  hdivoux
 * LOG: Added calls to (self) membership change callbacks for consistency.
 * LOG:
 * LOG: Revision 1.3  2002/04/23 15:34:25  hdivoux
 * LOG: Improved hash function (from Mitch input).
 * LOG:
 * LOG: Revision 1.2  2002/04/22 16:37:06  hdivoux
 * LOG: Slightly improved hash function (from Ricardo input).
 * LOG:
 * LOG: Revision 1.1  2002/04/11 20:40:48  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/


#include <its_dsm_stub.h>
#include <dsm_stub_impl.h>
#include <its_assertion.h>
#include <its_trace.h>
#include <its_timers.h>

#ident "$Id: dsm_stub_impl.c,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $"




/******************************************************************************
 ******************************************************************************
 **
 ** DSM (STUB) Data class.
 **
 */

static int
DsmInfoCreate(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj)
{
    int ret;

    ret = MUTEX_CreateMutex(&DSM_DATA_DSM_INFO(dataObj).lock, 0);
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return ret;
    }

    return ITS_SUCCESS;
}

static int
DsmInfoDestroy(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj)
{
    MUTEX_DeleteMutex(&DSM_DATA_DSM_INFO(dataObj).lock);

    return ITS_SUCCESS;
}

static int
MemCmp(void *k1, ITS_UINT k1Len, void *k2, ITS_UINT k2Len)
{
    return memcmp(k1, k2, k1Len > k2Len ? k1Len : k2Len);
}

static int
TablesCreate(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj)
{
    ITS_UINT i, j;

    DSM_DATA_TABLES(dataObj) =
        calloc(DSM_INST_MAX_NUM_TABLES(instObj), sizeof(DSM_Table));
    if (DSM_DATA_TABLES(dataObj) == NULL)
    {
        /* TODO: add trace. */
        return ITS_ENOMEM;
    }

    /* FIXME: Right now, the calloc() forces all the table types to DSM_TABLE_HASH */

    for (i = 0; i < DSM_INST_MAX_NUM_TABLES(instObj); i++)
    {
        switch (DSM_DATA_TABLES(dataObj)[i].type)
        {
        case DSM_TABLE_HASH:
            DSM_DATA_TABLES(dataObj)[i].table.hash = HASH_CreateTable();
            if (DSM_DATA_TABLES(dataObj)[i].table.hash == NULL)
            {
                /* TODO: add trace. */

                for (j = 0; j < i; j++)
                {
                    switch (DSM_DATA_TABLES(dataObj)[i].type)
                    {
                    case DSM_TABLE_HASH:
                        HASH_DeleteTable(DSM_DATA_TABLES(dataObj)[j].table.hash);
                        DSM_DATA_TABLES(dataObj)[j].table.hash = NULL;
                        break;
                    case DSM_TABLE_REDBLACK:
                        RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
                        DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
                        break;

                    case DSM_TABLE_SPLAY:
                        SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
                        DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
                        break;

                    default:
                        break;
                    }
                }

                return ITS_ENOMEM;
            }
            break;

        case DSM_TABLE_REDBLACK:
            DSM_DATA_TABLES(dataObj)[i].table.tree = RB_InitTree(MemCmp, ITS_TRUE);
            if (DSM_DATA_TABLES(dataObj)[i].table.tree == NULL)
            {
                /* TODO: add trace. */

                for (j = 0; j < i; j++)
                {
                    switch (DSM_DATA_TABLES(dataObj)[i].type)
                    {
                    case DSM_TABLE_HASH:
                        HASH_DeleteTable(DSM_DATA_TABLES(dataObj)[j].table.hash);
                        DSM_DATA_TABLES(dataObj)[j].table.hash = NULL;
                        break;
                    case DSM_TABLE_REDBLACK:
                        RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
                        DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
                        break;

                    case DSM_TABLE_SPLAY:
                        SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
                        DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
                        break;

                    default:
                        break;
                    }
                }

                return ITS_ENOMEM;
            }
            break;

        case DSM_TABLE_SPLAY:
            DSM_DATA_TABLES(dataObj)[i].table.splay = SPLAY_InitSplay(MemCmp, ITS_TRUE);
            if (DSM_DATA_TABLES(dataObj)[i].table.splay == NULL)
            {
                /* TODO: add trace. */

                for (j = 0; j < i; j++)
                {
                    switch (DSM_DATA_TABLES(dataObj)[i].type)
                    {
                    case DSM_TABLE_HASH:
                        HASH_DeleteTable(DSM_DATA_TABLES(dataObj)[j].table.hash);
                        DSM_DATA_TABLES(dataObj)[j].table.hash = NULL;
                        break;
                    case DSM_TABLE_REDBLACK:
                        RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
                        DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
                        break;

                    case DSM_TABLE_SPLAY:
                        SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
                        DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
                        break;

                    default:
                        break;
                    }
                }

                return ITS_ENOMEM;
            }
            break;

        default:
            /* FIXME: Trace */

            for (j = 0; j < i; j++)
            {
                switch (DSM_DATA_TABLES(dataObj)[i].type)
                {
                case DSM_TABLE_HASH:
                    HASH_DeleteTable(DSM_DATA_TABLES(dataObj)[j].table.hash);
                    DSM_DATA_TABLES(dataObj)[j].table.hash = NULL;
                    break;
                case DSM_TABLE_REDBLACK:
                    RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
                    DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
                    break;

                case DSM_TABLE_SPLAY:
                    SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
                    DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
                    break;

                default:
                    break;
                }
            }

            return ITS_ENOMEM;
        }
    }

    return ITS_SUCCESS;
}

static int
TablesDestroy(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj)
{
    ITS_UINT i;

    for (i = 0; i < DSM_INST_MAX_NUM_TABLES(instObj); i++)
    {
        switch (DSM_DATA_TABLES(dataObj)[i].type)
        {
        case DSM_TABLE_HASH:
            HASH_DeleteTable(DSM_DATA_TABLES(dataObj)[i].table.hash);
            DSM_DATA_TABLES(dataObj)[i].table.hash = NULL;
            break;

        case DSM_TABLE_REDBLACK:
            RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
            DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
            break;

        case DSM_TABLE_SPLAY:
            SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
            DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
            break;

        default:
            break;
        }
    }

    return ITS_SUCCESS;
}

static int 
TablesInfoCreate(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj)
{
    ITS_UINT i, j;
    int ret;

    DSM_DATA_TABLES_INFO(dataObj) =
        calloc(DSM_INST_MAX_NUM_TABLES(instObj), sizeof(DSM_TableInfo));
    if (DSM_DATA_TABLES_INFO(dataObj) == NULL)
    {
        /* TODO: add trace. */
        return ITS_ENOMEM;
    }

    for (i = 0; i < DSM_INST_MAX_NUM_TABLES(instObj); i++)
    {
        ret = MUTEX_CreateMutex(&DSM_DATA_TABLES_INFO(dataObj)[i].lock, 0);
        if (ret != ITS_SUCCESS)
        {
            /* TODO: add trace. */

            for (j = 0; j < i; j++)
            {
                MUTEX_DeleteMutex(&DSM_DATA_TABLES_INFO(dataObj)[j].lock);
            }

            return ret;
        }

        DSM_DATA_TABLES_INFO(dataObj)[i].entries = 0;
    }

    return ITS_SUCCESS;
}

static int
TablesInfoDestroy(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj)
{
    ITS_UINT i;

    for (i = 0; i < DSM_INST_MAX_NUM_TABLES(instObj); i++)
    {
        MUTEX_DeleteMutex(&DSM_DATA_TABLES_INFO(dataObj)[i].lock);
    }

    return ITS_SUCCESS;
}

/*
 * DataClassInitialize.
 */
static int
DataClassInitialize(
    ITS_Class objClass)
{
    /* Nothing to do. */
    return ITS_SUCCESS;
}

/*
 * DataClassTerminate.
 */
static void
DataClassTerminate(
    ITS_Class objClass)
{
    /* Nothing to do. */
    return;
}

/*
 * DataCreateInstance.
 */
static int
DataCreateInstance(
    ITS_Object obj, 
    va_list args)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_USHORT ftGroupId;
    int ret;

    coreObj     = va_arg(args, DSM_CoreObject*);
    instObj     = va_arg(args, DSM_InstObject*);
    ftGroupId   = (ITS_USHORT)va_arg(args, int);

    dataObj     = (DSM_DataObject*)obj;

    /* Access within destroy instance only. */
    DSM_DATA_CORE_OBJECT(dataObj) = coreObj;
    DSM_DATA_INST_OBJECT(dataObj) = instObj;

    ret = DsmInfoCreate(coreObj, instObj, dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance: DsmInfoCreate failed: %d\n", ret));
        return ret;
    }

    ret = TablesCreate(coreObj, instObj, dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance: TablesCreate failed: %d\n", ret));
        DsmInfoDestroy(coreObj, instObj, dataObj);
        return ret;
    }

    ret = TablesInfoCreate(coreObj, instObj, dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance: TablesInfoCreate failed: %d\n", ret));
        DsmInfoDestroy(coreObj, instObj, dataObj);
        TablesDestroy(coreObj, instObj, dataObj);
        return ret;
    }

    return ITS_SUCCESS;
}

/*
 * DataDestroyInstance.
 */
static void
DataDestroyInstance(
    ITS_Object obj)
{
    TablesInfoDestroy(
        DSM_DATA_CORE_OBJECT(obj),
        DSM_DATA_INST_OBJECT(obj),
        (DSM_DataObject*)obj);

    TablesDestroy(
        DSM_DATA_CORE_OBJECT(obj),
        DSM_DATA_INST_OBJECT(obj),
        (DSM_DataObject*)obj);

    DsmInfoDestroy(
        DSM_DATA_CORE_OBJECT(obj),
        DSM_DATA_INST_OBJECT(obj),
        (DSM_DataObject*)obj);

    DSM_DATA_CORE_OBJECT(obj) = NULL;
    DSM_DATA_INST_OBJECT(obj) = NULL;
}

static DSM_DataClassRec itsDSM_DataClassRec =
{
    /* core part */
    {
        NULL,                               /* no super class in DLL    */
        sizeof(DSM_DataObject),             /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_DATA_CLASS_NAME,                /* class name               */
        DataClassInitialize,                /* class init               */
        DataClassTerminate,                 /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        DataCreateInstance,                 /* instance create          */
        DataDestroyInstance,                /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* data part */
    {
        NULL,
        NULL
    }
};

static ITS_Class itsDSM_DataClass = (ITS_Class)&itsDSM_DataClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM (STUB) Impl (implementation) class.
 **
 */

static void
CallMembershipChangeCallbacks(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    ITS_USHORT ftGroupId,
    DSM_MembershipChangeType membershipChangeType)
{
    DSM_MembershipChangeCbData membershipChangeCbData;
    DSM_FtGroupMember ftGroupMembers[1];
    ITS_USHORT numFtGroupMembers;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(instObj != NULL);

    nodeId      = DSM_CORE_NODE_ID(coreObj);
    processId   = DSM_CORE_PROCESS_ID(coreObj);

    numFtGroupMembers = 1;

    ftGroupMembers[0].nodeId    = nodeId;
    ftGroupMembers[0].processId = processId;

    membershipChangeCbData.ftGroupId = ftGroupId;
    membershipChangeCbData.membershipChangeType = membershipChangeType;
    membershipChangeCbData.memberNodeId = nodeId;
    membershipChangeCbData.memberProcessId = processId;
    membershipChangeCbData.numFtGroupMembers = numFtGroupMembers;
    membershipChangeCbData.ftGroupMembers = ftGroupMembers;

    ret = CALLBACK_CallCallbackList(
            DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(instObj),
            (ITS_POINTER)coreObj,
            (ITS_POINTER)&membershipChangeCbData);
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return;
    }
}

static int 
DSM_ImplDataCreateInstanceImpl(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    ITS_USHORT ftGroupId)
{
    DSM_DataObject* dataObj;
    
    dataObj = (DSM_DataObject*)ITS_ConstructObject(
                                        itsDSM_DataClass,
                                        coreObj,
                                        instObj,
                                        (int)ftGroupId);
    if (dataObj == NULL)
    {
        /* TODO: add trace. */
        return ITS_EIMPLINITFAIL;
    }

    DSM_INST_IMPL_DATA(instObj) = (ITS_Object)dataObj;

    return ITS_SUCCESS;
}

static int 
DSM_ImplDataDestroyInstanceImpl(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    ITS_USHORT  ftGroupId)
{
    DSM_DataObject* dataObj;

    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    ITS_DestructObject((ITS_Object)dataObj);

    return ITS_SUCCESS;
}

static int 
DSM_JoinFtGroupImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(coreObj != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    DSM_INST_FT_GROUP_JOINED(instObj) = ITS_TRUE;

    CallMembershipChangeCallbacks(
        coreObj,
        instObj,
        ftGroupId,
        DSM_FT_GROUP_MEMBER_ALIVE);

    CallMembershipChangeCallbacks(
        coreObj,
        instObj,
        ftGroupId,
        DSM_FT_GROUP_MEMBER_JOIN);

    return ITS_SUCCESS;
}

static int 
DSM_LeaveFtGroupImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(coreObj != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    DSM_INST_FT_GROUP_JOINED(instObj) = ITS_FALSE;

    CallMembershipChangeCallbacks(
        coreObj,
        instObj,
        ftGroupId,
        DSM_FT_GROUP_MEMBER_LEAVE);

    CallMembershipChangeCallbacks(
        coreObj,
        instObj,
        ftGroupId,
        DSM_FT_GROUP_MEMBER_DEAD);

    return ITS_SUCCESS;
}

static int 
DSM_SynchronizeDsmImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT msecs)
{
    /* Nothing to do for STUB implementation. */
    return ITS_SUCCESS;
}

static int 
DSM_LockDsmImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    ret = MUTEX_AcquireMutex(&DSM_DATA_DSM_INFO(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_LockDsmImpl: MUTEX_AcquireMutex failed: %d\n", ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int 
DSM_UnlockDsmImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    ret = MUTEX_ReleaseMutex(&DSM_DATA_DSM_INFO(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_UnlockDsmImpl: MUTEX_ReleaseMutex failed: %d\n", ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int 
DSM_LockTableImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId, 
    ITS_UINT tableId)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_INFO(dataObj)[tableId].lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_LockTableImpl: MUTEX_AcquireMutex failed: %d\n", ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int 
DSM_UnlockTableImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId, 
    ITS_UINT tableId)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_INFO(dataObj)[tableId].lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_UnlockTableImpl: MUTEX_ReleaseMutex failed: %d\n", ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static void* 
DSM_AllocNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    DSM_RowHeader* allocPtr;
    DSM_RowHeader* tmp;
    DSM_RowHeader** list;
    ITS_INT hash;
    ITS_UINT round;
    ITS_UINT rowSize = size;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* Add row header to rowSize and make it a multiple of word size. */
    rowSize += sizeof(DSM_RowHeader) + sizeof(ITS_UINT) - 1;
    rowSize &= ~(sizeof(ITS_UINT) - 1);

    /* Allocate entry. */
    allocPtr = calloc(1, rowSize);
    if (allocPtr == NULL)
    {
        *error = ITS_ENOMEM;
        return NULL;
    }

    /* Allocate key. */
    round = klen + sizeof(ITS_UINT) - 1;
    round &= ~(sizeof(ITS_UINT) - 1);

    allocPtr->key = calloc(1, round);
    if (allocPtr->key == NULL)
    {
        free(allocPtr);
        *error = ITS_ENOMEM;
        return NULL;
    }

    /* Compute hash value. */
    hash = HASH_MakeKey((char *)key, klen);

    /* Add to hash table. */
    ret = HASH_FindEntry(
                DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                tableId,
                hash, 
                (ITS_POINTER*)&tmp);
    if (ret == ITS_SUCCESS)
    {
        for (list = &tmp->next; 
             (*list) != NULL; 
             list = &((*list)->next))
        {
            /* Check for duplicate keys. */
            if ((*list)->klen == klen && 
                memcmp((*list)->key, key, klen) == 0)
            {
                /* TODO: add debug trace. */
            }
        }

        *list = allocPtr;
    }
    else
    {
        ret = HASH_AddEntry(
                    DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                    tableId,
                    hash,
                    (ITS_POINTER)allocPtr);
        if (ret != ITS_SUCCESS)
        {
            free(allocPtr->key);
            free(allocPtr);
            *error = ret;
            return NULL;
        }
    }

    /* Store key info. */
    memcpy(allocPtr->key, key, klen);
    allocPtr->klen = klen;

    /* Adjust number of entries in table. */
    DSM_DATA_TABLES_INFO(dataObj)[tableId].entries++;

    /* Adjust pointer to user data (row header is before). */
    allocPtr = allocPtr + 1;

    return allocPtr;
}

static void*
DSM_FindNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    DSM_RowHeader* findPtr;
    DSM_RowHeader* row;
    ITS_INT hash;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* Compute hash value. */
    hash = HASH_MakeKey((char *)key, klen);

    /* Lookup for row list in table according to hash value. */
    ret = HASH_FindEntry(
                DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                tableId,
                hash,
                (ITS_POINTER*)&row);
    if (ret != ITS_SUCCESS)
    {
        *error = ITS_ENOTFOUND;
        return NULL;
    }

    /* Scan row list for correct row. */
    while (row != NULL)
    {
        if (row->klen == klen && memcmp(row->key, key, klen) == 0)
        {
            break;
        }

        row = row->next;
    }

    /* Make sure it was found. */
    if (row == NULL)
    {
        *error = ITS_ENOTFOUND;
        return NULL;
    }

    /* Adjust pointer to user data (row header is before). */
    findPtr = row;
    findPtr = findPtr + 1;

    return findPtr;
}

static int 
DSM_FreeNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,           
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    DSM_RowHeader* row;
    DSM_RowHeader* tmp;
    DSM_RowHeader* head;
    DSM_RowHeader** list;
    ITS_INT hash;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    /* Compute hash value. */
    hash = HASH_MakeKey((char *)key, klen);

    /* Lookup for row list in table according to hash value. */
    ret = HASH_FindEntry(
                DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                tableId,
                hash,
                (ITS_POINTER*)&head);
    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTFOUND;
    }

    /* Scan row list for correct row. */
    tmp = head;
    while (tmp != NULL)
    {
        if (tmp->klen == klen && 
            memcmp(tmp->key, key, klen) == 0 &&
            tmp == row)
        {
            break;
        }

        tmp = tmp->next;
    }

    ITS_C_ASSERT(tmp != NULL);

    if (tmp == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    /* Remove from list. */
    list = &head;
    while (*list)
    {
        if (*list == row)
        {
            *list = row->next;
            break;
        }

        list = &((*list)->next);
    }

    /* Update hash accordingly. */
    if (head == NULL)
    {
        ret = HASH_DeleteEntry(
                    DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                    tableId,
                    hash);

        if (ret != ITS_SUCCESS)
        {
            free(row->key);
            free(row);
            return ret;
        }
    }
    else
    {
        ret = HASH_AddEntry(
                    DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                    tableId,
                    hash, 
                    (ITS_POINTER)head);

        if (ret != ITS_SUCCESS)
        {
            free(row->key);
            free(row);
            return ret;
        }
    }
            
    free(row->key);
    free(row);

    /* Adjust number of entries in table. */
    if (DSM_DATA_TABLES_INFO(dataObj)[tableId].entries > 0)
    {
        DSM_DATA_TABLES_INFO(dataObj)[tableId].entries--;
    }    

    return ITS_SUCCESS;
}

static int 
DSM_CommitNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    DSM_RowHeader* row;
    DSM_RowHeader* tmp;
    DSM_RowHeader* head;
    ITS_INT hash;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    /* Compute hash value. */
    hash = HASH_MakeKey((char *)key, klen);

    /* Lookup for row list in table according to hash value. */
    ret = HASH_FindEntry(
                DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                tableId,
                hash,
                (ITS_POINTER*)&head);
    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTFOUND;
    }

    /* Scan row list for correct row. */
    tmp = head;
    while (tmp != NULL)
    {
        if (tmp->klen == klen &&
            memcmp(tmp->key, key, klen) == 0 &&
            tmp == row)
        {
            break;
        }

        tmp = tmp->next;
    }

    ITS_C_ASSERT(tmp != NULL);

    if (tmp == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    return ITS_SUCCESS;
}

static int 
DSM_LockRowNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    void* object)
{
    DSM_RowHeader* row;

    ITS_C_REQUIRE(object != NULL);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    row->locked = ITS_TRUE;
    row->lockTime = TIMERS_Time();

    return ITS_SUCCESS;
}

static int 
DSM_UnlockRowNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    void* object)
{
    DSM_RowHeader* row;

    ITS_C_REQUIRE(object != NULL);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    row->locked = ITS_FALSE;
    row->lockTime = 0;

    return ITS_SUCCESS;
}

static void* 
DSM_AllocImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    void* allocPtr;
    int ret;

    *error = ITS_SUCCESS;

    ret = DSM_LockTableImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        *error = ret;
        return NULL;
    }

    allocPtr = DSM_AllocNoLockImpl(
                    coreObj,
                    ftGroupId,
                    tableId, 
                    key, 
                    klen, 
                    size, 
                    error);
    if (allocPtr != NULL && *error == ITS_SUCCESS)
    {
        *error = DSM_LockRowNoLockImpl(
                    coreObj,
                    ftGroupId,
                    allocPtr);
    }

    ret = DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        /* Precedence to report errors from most important functions. */
        if (*error == ITS_SUCCESS)
        {
            *error = ret;
        }
    }

    return allocPtr;
}

static void* 
DSM_FindImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    void* findPtr;
    int ret;

    *error = ITS_SUCCESS;

    ret = DSM_LockTableImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        *error = ret;
        return NULL;
    }

    findPtr = DSM_FindNoLockImpl(
                    coreObj,
                    ftGroupId,
                    tableId, 
                    key, 
                    klen,  
                    error);
    if (findPtr != NULL && *error == ITS_SUCCESS)
    {
        *error = DSM_LockRowNoLockImpl(
                    coreObj,
                    ftGroupId,
                    findPtr);
    }

    ret = DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        /* Precedence to report errors from most important functions. */
        if (*error == ITS_SUCCESS)
        {
            *error = ret;
        }
    }

    return findPtr;
}

static int 
DSM_FreeImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_RowHeader* row;
    int ret;

    ITS_C_REQUIRE(object != NULL);

    ret = DSM_LockTableImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader *)((char *)object - sizeof(DSM_RowHeader));

    ITS_C_ASSERT(row->locked);

    if (!row->locked)
    {
        DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);

        return ITS_EROWNOTLOCKED;
    }

    ret = DSM_FreeNoLockImpl(
                    coreObj,
                    ftGroupId,
                    tableId,
                    key,
                    klen,
                    object);
    if (ret != ITS_SUCCESS)
    {
        DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
        
        return ret;
    }
    
    ret = DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}

static int 
DSM_CommitImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_RowHeader* row;
    int ret;

    ITS_C_REQUIRE(object != NULL);

    ret = DSM_LockTableImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader *)((char *)object - sizeof(DSM_RowHeader));

    ITS_C_ASSERT(row->locked);

    if (!row->locked)
    {
        DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);

        return ITS_EROWNOTLOCKED;
    }

    ret = DSM_CommitNoLockImpl(
                    coreObj,
                    ftGroupId,
                    tableId,
                    key,
                    klen,
                    object);
    if (ret != ITS_SUCCESS)
    {
        DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
        
        return ret;
    }
    
    ret = DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}

static int 
DSM_LockRowImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    void* findPtr;
    int error;
    int ret;

    ret = DSM_LockTableImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    findPtr = DSM_FindNoLockImpl(
                    coreObj,
                    ftGroupId,
                    tableId, 
                    key, 
                    klen,  
                    &error);
    if (findPtr != NULL && error == ITS_SUCCESS)
    {
        ret = DSM_LockRowNoLockImpl(
                    coreObj,
                    ftGroupId,
                    findPtr);
    }

    if (error != ITS_SUCCESS)
    {
        ret = error;
    }

    /* Precedence to report errors from most important functions. */
    if (ret == ITS_SUCCESS)
    {
        ret = DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }
    }
    else
    {
        DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);

        return ret;
    }
        
    return ITS_SUCCESS;
}

static int 
DSM_UnlockRowImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    void* findPtr;
    int error;
    int ret;

    ret = DSM_LockTableImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    findPtr = DSM_FindNoLockImpl(
                    coreObj,
                    ftGroupId,
                    tableId, 
                    key, 
                    klen,  
                    &error);
    if (findPtr != NULL && error == ITS_SUCCESS)
    {
        ret = DSM_UnlockRowNoLockImpl(
                    coreObj,
                    ftGroupId,
                    findPtr);
    }

    if (error != ITS_SUCCESS)
    {
        ret = error;
    }

    /* Precedence to report errors from most important functions. */
    if (ret == ITS_SUCCESS)
    {
        ret = DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }
    }
    else
    {
        DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);

        return ret;
    }
        
    return ITS_SUCCESS;
}

static int 
DSM_TableIterateImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    void* in, 
    void* out,
    DSM_IterateEntryProc iterateEntryFn)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    HASH_Table db;
    HASH_TableEntry* pentry;
    HASH_TableEntry entry, next;
    int ret;
    int i;

    DSM_RowHeader *rhdr;
    DSM_RowHeader *rhdr1;
    ITS_POINTER   nptr;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(iterateEntryFn != NULL);

    ITS_TRACE_DEBUG(("DSM_TableIterateImpl:\n"));

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    db = DSM_DATA_TABLES(dataObj)[tableId].table.hash;

    ITS_C_ASSERT(db != NULL);

    ret = DSM_LockTableImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Iterate hashtable. */
    for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
    {
        for (entry = *pentry; entry; entry = next)
        {
            if (entry->rid == tableId)
            {
                ITS_POINTER ptr = entry->data + sizeof(DSM_RowHeader);

                ret = iterateEntryFn(ptr, in, out);
                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                rhdr = (DSM_RowHeader *) entry->data;
                rhdr1 = rhdr->next;

                while(rhdr1 != NULL)
                {
                    nptr = (ITS_POINTER) (rhdr1) + sizeof(DSM_RowHeader);

                    ret = iterateEntryFn(nptr, in, out);
                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    rhdr1 = rhdr1->next;
                };
            }
        
            next = entry->next;
        }

        if (ret != ITS_SUCCESS)
        {
            break;
        }
    }

    /* Precedence to report errors from most important functions. */
    if (ret == ITS_SUCCESS)
    {
        ret = DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }
    }
    else
    {
        DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);

        return ret;
    }

    return ITS_SUCCESS;
}

static int 
DSM_TableIterateLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    void* in, 
    void* out,
    DSM_IterateEntryProc iterateEntryFn)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    HASH_Table db;
    HASH_TableEntry* pentry;
    HASH_TableEntry entry, next;
    int ret;
    int i;

    DSM_RowHeader *rhdr;
    DSM_RowHeader *rhdr1;
    ITS_POINTER   nptr;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(iterateEntryFn != NULL);

    ITS_TRACE_DEBUG(("DSM_TableIterateImpl:\n"));

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    db = DSM_DATA_TABLES(dataObj)[tableId].table.hash;

    ITS_C_ASSERT(db != NULL);

    ret = DSM_LockTableImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Iterate hashtable. */
    for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
    {
        for (entry = *pentry; entry; entry = next)
        {
            if (entry->rid == tableId)
            {
                ITS_POINTER ptr = entry->data + sizeof(DSM_RowHeader);

                ret = iterateEntryFn(ptr, in, out);
                if (ret != ITS_SUCCESS)
                {
                    break;
                }

                rhdr = (DSM_RowHeader *) entry->data;
                rhdr1 = rhdr->next;

                while(rhdr1 != NULL)
                {
                    nptr = (ITS_POINTER) (rhdr1) + sizeof(DSM_RowHeader);

                    ret = iterateEntryFn(nptr, in, out);
                    if (ret != ITS_SUCCESS)
                    {
                        break;
                    }
                    rhdr1 = rhdr1->next;
                };
            }
        
            next = entry->next;
        }

        if (ret != ITS_SUCCESS)
        {
            break;
        }
    }

    /* Precedence to report errors from most important functions. */
    if (ret == ITS_SUCCESS)
    {
        ret = DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }
    }
    else
    {
        DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);

        return ret;
    }

    return ITS_SUCCESS;
}
static int 
DSM_TableDumpImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    char** pStrDump,                            
    DSM_DumpEntryProc dumpEntryFn)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    HASH_Table db;
    HASH_TableEntry* pentry;
    HASH_TableEntry entry, next;
    char* strEntryDump;
    int ret;
    int i;

    DSM_RowHeader *rhdr;
    DSM_RowHeader *rhdr1;
    ITS_POINTER   nptr;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(pStrDump != NULL);
    ITS_C_REQUIRE(dumpEntryFn != NULL);

    ITS_TRACE_DEBUG(("DSM_TableDumpImpl:\n"));

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    db = DSM_DATA_TABLES(dataObj)[tableId].table.hash;

    ITS_C_ASSERT(db != NULL);

    ret = DSM_LockTableImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Initialization. */
    *pStrDump = (char *)malloc(1 * sizeof(char));
    if (*pStrDump == NULL)
    {
        ITS_TRACE_ERROR(("DSM_TableDumpImpl: out of memory\n"));

        DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);

        return ITS_ENOMEM;
    }

    **pStrDump = '\0'; 

    /* Iterate hashtable. */
    for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
    {
        for (entry = *pentry; entry; entry = next)
        {
            if (entry->rid == tableId)
            {
                ITS_POINTER ptr = entry->data + sizeof(DSM_RowHeader);

                strEntryDump = NULL;

                ret = dumpEntryFn(ptr, &strEntryDump);
                if (ret != ITS_SUCCESS)
                {
                    if (strEntryDump != NULL)
                    {
                        free(strEntryDump);
                    }

                    break;
                }

                /* + 1 = security. */
                *pStrDump = (char *)realloc(*pStrDump,
                                        strlen(*pStrDump) * sizeof(char) +
                                            strlen(strEntryDump) *
                                            sizeof(char) + 1);

                if (*pStrDump == NULL)
                {
                    ITS_TRACE_ERROR(("DSM_TableDumpImpl: out of memory\n"));

                    free(strEntryDump);
                    ret = ITS_ENOMEM;
                    break;
                }

                strcat(*pStrDump, strEntryDump);
                free(strEntryDump);

                rhdr = (DSM_RowHeader *) entry->data;

                rhdr1 = rhdr->next;

                while (rhdr1 != NULL)
                {
                    strEntryDump = NULL;

                    nptr = (ITS_POINTER) (rhdr1) + sizeof(DSM_RowHeader);

                    ret = dumpEntryFn(nptr, &strEntryDump);
                    if (ret != ITS_SUCCESS)
                    {
                        if (strEntryDump != NULL)
                        {
                            free(strEntryDump);
                        }
                        break;
                    }

                    /* + 1 = security. */
                    *pStrDump = (char *)realloc(*pStrDump,
                                            strlen(*pStrDump) * sizeof(char) +
                                                strlen(strEntryDump) *
                                                sizeof(char) + 1);
                    if (*pStrDump == NULL)
                    {
                        ITS_TRACE_ERROR(("DSM_TableDumpImpl: out of memory\n"));
    
                        free(strEntryDump);
                        ret = ITS_ENOMEM;
                        break;
                    }

                    strcat(*pStrDump, strEntryDump);
                    free(strEntryDump);

                    rhdr1 = rhdr1->next;
                }
            }
        
            next = entry->next;
        }

        if (ret != ITS_SUCCESS)
        {
            break;
        }
    }

    /* Precedence to report errors from most important functions. */
    if (ret == ITS_SUCCESS)
    {
        ret = DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }
    }
    else
    {
        DSM_UnlockTableImpl(
                    coreObj,
                    ftGroupId,
                    tableId);

        return ret;
    }

    return ITS_SUCCESS;
}

static int 
DSM_TableGetSizeImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    ITS_UINT* size)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(size != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *size = DSM_DATA_TABLES_INFO(dataObj)[tableId].entries;

    return ITS_SUCCESS;
}

static int 
DSM_MulticastEventToFtGroupMembersImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    const ITS_EVENT* event)
{
    ITS_BOOLEAN not_implemented = ITS_FALSE;
    ITS_C_ASSERT(not_implemented);

    return ITS_SUCCESS;
}

static int 
DSM_MulticastStackEventToFtGroupMembersImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_EVENT event,
    ITS_USHORT source,   
    ITS_USHORT destination)
{

    /* Tell the stack that message is not multicast */
    return ITS_ENOMSG;
}


#define DSM_STUB_IMPL_CLASS_NAME "DSM Implementation Class - STUB"

DSM_ImplClassRec itsDSM_StubImplClassRec =
{
    /* core part */
    {
        NULL,                               /* no superclass in a DLL   */
        0,                                  /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_STUB_IMPL_CLASS_NAME,           /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        ITS_INST_NO_CONST,                  /* instance create          */
        ITS_INST_NO_DEST,                   /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* impl part */
    {
        "STUB",
        DSM_ImplDataCreateInstanceImpl,
        DSM_ImplDataDestroyInstanceImpl,
        DSM_JoinFtGroupImpl,
        DSM_LeaveFtGroupImpl,
        DSM_SynchronizeDsmImpl,
        DSM_AllocImpl,
        DSM_AllocImpl,
        DSM_FindImpl,
        DSM_FindImpl,
        DSM_FreeImpl,
        DSM_FreeImpl,
        DSM_CommitImpl,
        DSM_CommitImpl,
        DSM_LockRowImpl,
        DSM_LockRowImpl,
        DSM_UnlockRowImpl,
        DSM_UnlockRowImpl,
        DSM_LockDsmImpl,
        DSM_UnlockDsmImpl,
        DSM_LockTableImpl,
        DSM_LockTableImpl,
        DSM_UnlockTableImpl,
        DSM_UnlockTableImpl,
        DSM_AllocNoLockImpl,
        DSM_AllocNoLockImpl,
        DSM_FindNoLockImpl,
        DSM_FindNoLockImpl,
        DSM_FreeNoLockImpl,
        DSM_FreeNoLockImpl,
        DSM_CommitNoLockImpl,
        DSM_CommitNoLockImpl,
        DSM_LockRowNoLockImpl,
        DSM_LockRowNoLockImpl,
        DSM_UnlockRowNoLockImpl,
        DSM_UnlockRowNoLockImpl,
        DSM_TableIterateImpl,
        DSM_TableDumpImpl,
        DSM_TableGetSizeImpl,
        DSM_MulticastEventToFtGroupMembersImpl,
        DSM_MulticastStackEventToFtGroupMembersImpl,
        DSM_TableIterateLocalImpl
    }
};

DSMDLLAPI ITS_Class itsDSM_StubImplClass = (ITS_Class)&itsDSM_StubImplClassRec;


