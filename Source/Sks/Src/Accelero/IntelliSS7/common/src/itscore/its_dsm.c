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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.13  2005/03/21 13:51:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.1.8.2  2004/02/16 12:49:00  yranade
 * LOG: Perf. related changes.
 * LOG:
 * LOG: Revision 7.3.2.1.8.1  2004/01/05 09:24:05  sjaddu
 * LOG: Merged files from tcs isup branch.
 * LOG:
 * LOG: Revision 7.3.2.1.4.1  2003/09/05 10:10:33  akumar
 * LOG: Msg based redundancy commit.
 * LOG:
 * LOG: Revision 7.3.2.1.2.2  2003/08/30 16:58:19  randresol
 * LOG: Add Logic for Message based redundnacy
 * LOG:
 * LOG: Revision 7.3.2.1.2.1  2003/05/05 22:04:36  randresol
 * LOG: Tag for GCS ISUP Prototype
 * LOG:
 * LOG: Revision 7.3.2.1  2003/02/19 16:19:22  randresol
 * LOG: Bug fixing for DSM-GCS.
 * LOG:
 * LOG: Revision 7.3  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/12/20 19:40:41  mmiers
 * LOG: Move files.
 * LOG:
 * LOG: Revision 7.1.4.2  2003/04/15 21:21:33  randresol
 * LOG:
 * LOG: Revision 7.1.4.1  2003/04/08 17:47:56  randresol
 * LOG: Chages for GCS TCAP prototype
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 4.34  2002/08/15 19:03:53  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 4.33  2002/07/03 19:34:22  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 4.32  2002/05/07 19:48:08  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 4.31  2002/05/01 20:08:48  hdivoux
 * LOG: Allow to specify no master FT group members (for stub).
 * LOG:
 * LOG: Revision 4.30  2002/04/23 15:04:57  hdivoux
 * LOG: Comment update.
 * LOG:
 * LOG: Revision 4.29  2002/04/22 20:03:16  hdivoux
 * LOG: Added definition for critical error notification callback.
 * LOG:
 * LOG: Revision 4.28  2002/04/22 16:22:43  hdivoux
 * LOG: Finish adding pre-add callbacks mechanism (for Engine).
 * LOG:
 * LOG: Revision 4.27  2002/04/19 22:09:36  hdivoux
 * LOG: Start adding pre-add callbacks mechanism (for Engine).
 * LOG:
 * LOG: Revision 4.26  2002/04/15 21:05:23  hdivoux
 * LOG: Added configurable FtGroups.
 * LOG:
 * LOG: Revision 4.25  2002/04/11 20:38:57  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/


#include <its_dsm.h>
#include <its_assertion.h>
#include <its_sockets.h>
#include <its_trace.h>
#include <its_app.h>

#include <../dsm-gcs/dsm_gcs_impl.h> 

#ident "$Id: its_dsm.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"


/******************************************************************************
 ******************************************************************************
 **
 ** Utilities (local).
 **
 */

/*
 * Implementation classes related.
 */

static ITS_BOOLEAN
HasImplClass(
    DSM_CoreObject* obj, 
    const char* implName)
{
    int i;

    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(implName != NULL);

    for (i = 0; i < DSM_MAX_IMPL_CLASSES; i++)
    {
        DSM_ImplClass implClass = DSM_CORE_IMPL_CLASSES(obj).classes[i];

        if (implClass != NULL && 
            strcmp(DSM_IMPL_CLASS_IMPL_NAME(implClass), implName) == 0)
        {
            return ITS_TRUE;
        }
    }

    return ITS_FALSE;
}

#if 0
/* dead code? */
static ITS_UINT
ImplClassSize(
    DSM_CoreObject* obj)
{
    int i;
    ITS_UINT result = 0;

    ITS_C_REQUIRE(obj != NULL);

    for (i = 0; i < DSM_MAX_IMPL_CLASSES; i++)
    {
        DSM_ImplClass implClass = DSM_CORE_IMPL_CLASSES(obj).classes[i];

        if (implClass != NULL)
        {
            result++;
        }
    }

    return result;
}
#endif

static DSM_ImplClass
ImplClassRetrieve(
    DSM_CoreObject* obj, 
    const char* implName)
{
    int i; 
    DSM_ImplClass result = NULL;

    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(implName != NULL);

    for (i = 0; i < DSM_MAX_IMPL_CLASSES; i++)
    {
        DSM_ImplClass implClass = DSM_CORE_IMPL_CLASSES(obj).classes[i];

        if (implClass != NULL &&
            strcmp(DSM_IMPL_CLASS_IMPL_NAME(implClass), implName) == 0)
        {
            result = implClass;
            break;
        }
    }

    return result;
}


/*
 * Fault Tolerance Group Members related.
 */

static ITS_BOOLEAN
HasFtGroupMember(
    ITS_USHORT numFtGroupMembers,
    const DSM_FtGroupMember* ftGroupMembers,
    ITS_USHORT nodeId,
    ITS_USHORT processId)
{
    int i;

    for (i = 0; i < numFtGroupMembers; i++)
    {
        if (ftGroupMembers[i].nodeId == nodeId && 
            ftGroupMembers[i].processId == processId)
        {
            return ITS_TRUE;
        }
    }

    return ITS_FALSE;
}


/*
 * Pre-added membership change callbacks.
 */

typedef struct __PreAddedMembershipChangeCb
{
    ITS_USHORT ftGroupId;
    ITS_CALLBACK cbFunction;
    ITS_POINTER userData;
    struct __PreAddedMembershipChangeCb* next;
} PreAddedMembershipChangeCb;

static PreAddedMembershipChangeCb* 
    preAddedMembershipChangeCbList;


/*
 * Pre-added critical error notification callbacks.
 */

typedef struct __PreAddedCriticalErrorNotificationCb
{
    ITS_CALLBACK cbFunction;
    ITS_POINTER userData;
    struct __PreAddedCriticalErrorNotificationCb* next;
} PreAddedCriticalErrorNotificationCb;

static PreAddedCriticalErrorNotificationCb* 
    preAddedCriticalErrorNotificationCbList;


/*
 * Pre-added event from Fault Tolerance Group Member callbacks.
 */

typedef struct __PreAddedEventFromFtGroupMemberCb
{
    ITS_USHORT ftGroupId;
    ITS_CALLBACK cbFunction;
    ITS_POINTER userData;
    struct __PreAddedEventFromFtGroupMemberCb* next;
} PreAddedEventFromFtGroupMemberCb;

static PreAddedEventFromFtGroupMemberCb* 
    preAddedEventFromFtGroupMemberCbList;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM Inst (instance) class.
 **
 */

/*
 * InstClassInitialize.
 */
static int
InstClassInitialize(
    ITS_Class objClass)
{
    return ITS_SUCCESS;
}

/*
 * InstClassTerminate.
 */
static void
InstClassTerminate(
    ITS_Class objClass)
{
    /* Nothing to do. */
}

/*
 * InstCreateInstance.
 */
static int
InstCreateInstance(
    ITS_Object obj, 
    va_list args)
{
    ITS_USHORT      ftGroupId;
    ITS_UINT        maxNumTables;
    ITS_UINT        dsmSize;
    const void*     dsmBaseAddress;
    const char*     dsmType;
    ITS_UINT        dsmJoinFtGroupTimeout;
    ITS_UINT        dsmRowLockTimeout;
    ITS_BOOLEAN     dsmSyncExplicit;
    int             res;

    DSM_CoreObject* coreObj;
    DSM_ImplClass   implClass;
    
    ftGroupId               = (ITS_USHORT)va_arg(args, int);
    maxNumTables            = (ITS_UINT)va_arg(args, int);
    dsmSize                 = (ITS_UINT)va_arg(args, int);
    dsmBaseAddress          = va_arg(args, const void*);
    dsmType                 = va_arg(args, const char*);
    dsmJoinFtGroupTimeout   = (ITS_UINT)va_arg(args, int);
    dsmRowLockTimeout       = (ITS_UINT)va_arg(args, int);
    dsmSyncExplicit         = (ITS_BOOLEAN)va_arg(args, int);

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(!DSM_IsInitialized(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    if (!HasImplClass(coreObj, dsmType))
    {
        /* TODO: add trace. */
        return ITS_EINVDSMTYPE;
    }

    implClass = ImplClassRetrieve(coreObj, dsmType);

    if ((res = ITS_InitializeClass((ITS_Class)implClass)) != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return (res);
    }

    DSM_INST_FT_GROUP_JOINED(obj)               = ITS_FALSE;
    DSM_INST_IMPL_CLASS(obj)                    = implClass;
    DSM_INST_MAX_NUM_TABLES(obj)                = maxNumTables;
    DSM_INST_DSM_SIZE(obj)                      = dsmSize;
    DSM_INST_DSM_BASE_ADDRESS(obj)              = dsmBaseAddress;
    DSM_INST_DSM_TYPE(obj)                      = dsmType;
    DSM_INST_DSM_JOIN_FT_GROUP_TIMEOUT(obj)     = dsmJoinFtGroupTimeout;
    DSM_INST_DSM_ROW_LOCK_TIMEOUT(obj)          = dsmRowLockTimeout;
    DSM_INST_DSM_SYNC_EXPLICIT(obj)             = dsmSyncExplicit;
    DSM_INST_NUM_FT_GROUP_MEMBERS(obj)          = 0;
    DSM_INST_FT_GROUP_MEMBERS(obj)              = NULL;
    DSM_INST_NUM_MASTER_FT_GROUP_MEMBERS(obj)   = 0;
    DSM_INST_MASTER_FT_GROUP_MEMBERS(obj)       = NULL;
    DSM_INST_FT_GROUP_ID(obj)                   = DSM_INVALID_FT_GROUP_ID;

    DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(obj) = CALLBACK_InitManager();
    if (DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(obj) == NULL)
    {
        return ITS_ENOMEM;
    }

    DSM_INST_EVENT_FROM_FT_GROUP_MEMBER_CALLBACKS(obj) = CALLBACK_InitManager();
    if (DSM_INST_EVENT_FROM_FT_GROUP_MEMBER_CALLBACKS(obj) == NULL)
    {
        CALLBACK_DestroyManager(
            DSM_INST_EVENT_FROM_FT_GROUP_MEMBER_CALLBACKS(obj));
        return ITS_ENOMEM;
    }

    res = DSM_IMPL_CLASS_IMPL_DATA_CREATE_INSTANCE(implClass)(
            coreObj,
            (DSM_InstObject*)obj,
            ftGroupId);
    if (res != ITS_SUCCESS)
    {
        CALLBACK_DestroyManager(
            DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(obj));
        CALLBACK_DestroyManager(
            DSM_INST_EVENT_FROM_FT_GROUP_MEMBER_CALLBACKS(obj));
        return res;
    }

    /* Mark DSM Instance as being initialized. */
    DSM_INST_FT_GROUP_ID(obj) = ftGroupId;

    /* Increment number of DSM instances. */
    DSM_CORE_NUM_FT_GROUPS(coreObj)++;

    /* Set DSM Instance as being initialized. */
    DSM_CORE_FT_GROUPS(coreObj)[ftGroupId] = (DSM_InstObject*)obj;

    /* Add pre-added membership change callbacks. */
    {
        PreAddedMembershipChangeCb** list = 
            &preAddedMembershipChangeCbList;
        PreAddedMembershipChangeCb* element;
        CALLBACK_Manager* callbackManager;

        while (*list != NULL)
        {
            element = *list;

            if (element->ftGroupId == ftGroupId)
            {
                callbackManager = 
                    DSM_GetMembershipChangeCallbacks(ftGroupId);

                ITS_C_ASSERT(callbackManager != NULL);

                CALLBACK_AddCallback(
                    callbackManager,
                    element->cbFunction,
                    element->userData);
            }

            list = &(*list)->next;
        }
    }

    /* Add pre-added event from Fault Tolerance Group callbacks. */
    {
        PreAddedEventFromFtGroupMemberCb** list =
            &preAddedEventFromFtGroupMemberCbList;
        PreAddedEventFromFtGroupMemberCb* element;
        CALLBACK_Manager* callbackManager;

        while (*list != NULL)
        {
            element = *list;

            if (element->ftGroupId == ftGroupId)
            {
                callbackManager =
                    DSM_GetEventFromFtGroupMemberCallbacks(ftGroupId);

                ITS_C_ASSERT(callbackManager != NULL);

                CALLBACK_AddCallback(
                    callbackManager,
                    element->cbFunction,
                    element->userData);
            }

            list = &(*list)->next;
        }
    }

    return ITS_SUCCESS;
}


/*
 * InstDestroyInstance.
 */
static void
InstDestroyInstance(
    ITS_Object obj)
{
    ITS_USHORT      ftGroupId;
    DSM_CoreObject* coreObj;
    DSM_ImplClass   implClass;
    int             res;

    ITS_C_REQUIRE(DSM_IsPreInitialized());

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return;
    }

    ftGroupId = DSM_INST_FT_GROUP_ID(obj);

    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return;
    }

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    implClass   = DSM_INST_IMPL_CLASS(obj);

    /* Unset DSM_Instance as being initialized. */
    DSM_CORE_FT_GROUPS(coreObj)[ftGroupId] = NULL;

    /* Decrement number of DSM instances. */
    DSM_CORE_NUM_FT_GROUPS(coreObj)--;

    /* Unmark DSM Instance as being initialized. */
    DSM_INST_FT_GROUP_ID(obj) = DSM_INVALID_FT_GROUP_ID;

    if (DSM_INST_FT_GROUP_MEMBERS(obj) != NULL)
    {
        free(DSM_INST_FT_GROUP_MEMBERS(obj));
        DSM_INST_FT_GROUP_MEMBERS(obj) = NULL;
        DSM_INST_NUM_FT_GROUP_MEMBERS(obj) = 0;
    }

    if (DSM_INST_MASTER_FT_GROUP_MEMBERS(obj) != NULL)
    {
        free(DSM_INST_MASTER_FT_GROUP_MEMBERS(obj));
        DSM_INST_MASTER_FT_GROUP_MEMBERS(obj) = NULL;
        DSM_INST_NUM_MASTER_FT_GROUP_MEMBERS(obj) = 0;
    }

    if (DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(obj) != NULL)
    {
        CALLBACK_DestroyManager(DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(obj));
        DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(obj) = NULL;
    }

    if (DSM_INST_EVENT_FROM_FT_GROUP_MEMBER_CALLBACKS(obj) != NULL)
    {
        CALLBACK_DestroyManager(
            DSM_INST_EVENT_FROM_FT_GROUP_MEMBER_CALLBACKS(obj));
        DSM_INST_EVENT_FROM_FT_GROUP_MEMBER_CALLBACKS(obj) = NULL;
    }

    res = DSM_IMPL_CLASS_IMPL_DATA_DESTROY_INSTANCE(implClass)(
            coreObj,
            (DSM_InstObject*)obj,
            ftGroupId);
    if (res != ITS_SUCCESS)
    {
        /* TODO: add trace. */
    }
}


ITSDLLAPI DSM_InstClassRec itsDSM_InstClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsCORE_ClassRec,       /* CORE is superclass       */
        sizeof(DSM_InstObject),             /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_INST_CLASS_NAME,                /* class name               */
        InstClassInitialize,                /* class init               */
        InstClassTerminate,                 /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        InstCreateInstance,                 /* instance create          */
        InstDestroyInstance,                /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* dsm part */
    {
        NULL,
        NULL
    }
};

ITSDLLAPI ITS_Class itsDSM_InstClass = (ITS_Class)&itsDSM_InstClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM Core class.
 **
 */

/*
 * Name (Node, Process, FtGroup) Resources related.
 */ 

static int
NodeNameResourcesCreate(
    DSM_CoreObject* obj)
{
    ITS_USHORT i;
    char buffer[16];
    char* nodeName;
    int ret = ITS_SUCCESS;

    ITS_C_REQUIRE(obj != NULL);
    
    DSM_CORE_NODE_NAME_RESOURCES(obj) =
        calloc(
            DSM_CORE_MAX_NUM_NODES(obj), 
            sizeof(DSM_NodeNameResource));
    if (DSM_CORE_NODE_NAME_RESOURCES(obj) == NULL)
    {
        return ITS_ENOMEM;
    }

    for (i = 0; i < DSM_CORE_MAX_NUM_NODES(obj); i++)
    {
        DSM_CORE_NODE_NAME_RESOURCES(obj)[i].nodeId = i;

        sprintf(buffer, "N%u", i);

        nodeName = strdup(buffer);
        if (nodeName == NULL)
        {
            ret = ITS_ENOMEM;
            break;
        }

        DSM_CORE_NODE_NAME_RESOURCES(obj)[i].nodeName = nodeName;
    }

    if (ret == ITS_ENOMEM)
    {
        for (i = 0; i < DSM_CORE_MAX_NUM_NODES(obj); i++)
        {
            if (DSM_CORE_NODE_NAME_RESOURCES(obj)[i].nodeName != NULL)
            {
                free(DSM_CORE_NODE_NAME_RESOURCES(obj)[i].nodeName);
            }
        }

        free(DSM_CORE_NODE_NAME_RESOURCES(obj));
        DSM_CORE_NODE_NAME_RESOURCES(obj) = NULL;

        return ITS_ENOMEM;
    }

    return ITS_SUCCESS;
}

static int
NodeNameResourcesDestroy(
    DSM_CoreObject* obj)
{
    ITS_USHORT i;

    if (DSM_CORE_NODE_NAME_RESOURCES(obj) != NULL)
    {
        for (i = 0; i < DSM_CORE_MAX_NUM_NODES(obj); i++)
        {
            if (DSM_CORE_NODE_NAME_RESOURCES(obj)[i].nodeName != NULL)
            {
                free(DSM_CORE_NODE_NAME_RESOURCES(obj)[i].nodeName);
            }
        }

        free(DSM_CORE_NODE_NAME_RESOURCES(obj));
        DSM_CORE_NODE_NAME_RESOURCES(obj) = NULL;
    }

    return ITS_SUCCESS;
}

static int
ProcessNameResourcesCreate(
    DSM_CoreObject* obj)
{
    ITS_USHORT i, j;
    char buffer[32];
    char* processName;
    int ret = ITS_SUCCESS;

    ITS_C_REQUIRE(obj != NULL);
    
    DSM_CORE_PROCESS_NAME_RESOURCES(obj) =
        calloc(
            DSM_CORE_MAX_NUM_NODES(obj) * DSM_CORE_MAX_NUM_PROCESSES(obj),
            sizeof(DSM_ProcessNameResource));
    if (DSM_CORE_PROCESS_NAME_RESOURCES(obj) == NULL)
    {
        return ITS_ENOMEM;
    }

    for (i = 0; i < DSM_CORE_MAX_NUM_NODES(obj); i++)
    {
        for (j = 0; j < DSM_CORE_MAX_NUM_PROCESSES(obj); j++)
        {
            DSM_CORE_PROCESS_NAME_RESOURCES(obj)[
                i * DSM_CORE_MAX_NUM_PROCESSES(obj) + j].nodeId = i;

            DSM_CORE_PROCESS_NAME_RESOURCES(obj)[
                i * DSM_CORE_MAX_NUM_PROCESSES(obj) + j].processId = j;

            sprintf(buffer, "N%uP%u", i, j);

            processName = strdup(buffer);
            if (processName == NULL)
            {
                ret = ITS_ENOMEM;
                break;
            }

            DSM_CORE_PROCESS_NAME_RESOURCES(obj)[i].processName = processName;
        }

        if (ret == ITS_ENOMEM)
        {
            break;
        }
    }

    if (ret == ITS_ENOMEM)
    {
        for (i = 0; i < DSM_CORE_MAX_NUM_NODES(obj); i++)
        {
            for (j = 0; j < DSM_CORE_MAX_NUM_PROCESSES(obj); j++)
            {
                if (DSM_CORE_PROCESS_NAME_RESOURCES(obj)[
                        i * DSM_CORE_MAX_NUM_PROCESSES(obj) + j].
                            processName != NULL)
                {
                    free(DSM_CORE_PROCESS_NAME_RESOURCES(obj)[
                        i * DSM_CORE_MAX_NUM_PROCESSES(obj) + j].processName);
                }
            }
        }

        free(DSM_CORE_PROCESS_NAME_RESOURCES(obj));
        DSM_CORE_PROCESS_NAME_RESOURCES(obj) = NULL;

        return ITS_ENOMEM;
    }

    return ITS_SUCCESS;
}

static int
ProcessNameResourcesDestroy(
    DSM_CoreObject* obj)
{
    ITS_USHORT i, j;

    if (DSM_CORE_PROCESS_NAME_RESOURCES(obj) != NULL)
    {
        for (i = 0; i < DSM_CORE_MAX_NUM_NODES(obj); i++)
        {
            for (j = 0; j < DSM_CORE_MAX_NUM_PROCESSES(obj); j++)
            {
                if (DSM_CORE_PROCESS_NAME_RESOURCES(obj)[
                        i * DSM_CORE_MAX_NUM_PROCESSES(obj) + j].
                            processName != NULL)
                {
                    free(DSM_CORE_PROCESS_NAME_RESOURCES(obj)[
                        i * DSM_CORE_MAX_NUM_PROCESSES(obj) + j].processName);
                }
            }
        }

        free(DSM_CORE_PROCESS_NAME_RESOURCES(obj));
        DSM_CORE_PROCESS_NAME_RESOURCES(obj) = NULL;
    }

    return ITS_SUCCESS;
}

static int
FtGroupNameResourcesCreate(
    DSM_CoreObject* obj)
{
    ITS_USHORT i;
    char buffer[16];
    char* ftGroupName;
    int ret = ITS_SUCCESS;

    ITS_C_REQUIRE(obj != NULL);
    
    DSM_CORE_FT_GROUP_NAME_RESOURCES(obj) =
        calloc(
            DSM_CORE_MAX_NUM_FT_GROUPS(obj), 
            sizeof(DSM_FtGroupNameResource));
    if (DSM_CORE_FT_GROUP_NAME_RESOURCES(obj) == NULL)
    {
        return ITS_ENOMEM;
    }

    for (i = 0; i < DSM_CORE_MAX_NUM_FT_GROUPS(obj); i++)
    {
        DSM_CORE_FT_GROUP_NAME_RESOURCES(obj)[i].ftGroupId = i;

        sprintf(buffer, "FTG%u", i);

        ftGroupName = strdup(buffer);
        if (ftGroupName == NULL)
        {
            ret = ITS_ENOMEM;
            break;
        }

        DSM_CORE_FT_GROUP_NAME_RESOURCES(obj)[i].ftGroupName = ftGroupName;
    }

    if (ret == ITS_ENOMEM)
    {
        for (i = 0; i < DSM_CORE_MAX_NUM_FT_GROUPS(obj); i++)
        {
            if (DSM_CORE_FT_GROUP_NAME_RESOURCES(obj)[i].ftGroupName != NULL)
            {
                free(DSM_CORE_FT_GROUP_NAME_RESOURCES(obj)[i].ftGroupName);
            }
        }

        free(DSM_CORE_FT_GROUP_NAME_RESOURCES(obj));
        DSM_CORE_FT_GROUP_NAME_RESOURCES(obj) = NULL;

        return ITS_ENOMEM;
    }

    return ITS_SUCCESS;
}

static int
FtGroupNameResourcesDestroy(
    DSM_CoreObject* obj)
{
    ITS_USHORT i;

    if (DSM_CORE_FT_GROUP_NAME_RESOURCES(obj) != NULL)
    {
        for (i = 0; i < DSM_CORE_MAX_NUM_FT_GROUPS(obj); i++)
        {
            if (DSM_CORE_FT_GROUP_NAME_RESOURCES(obj)[i].ftGroupName != NULL)
            {
                free(DSM_CORE_FT_GROUP_NAME_RESOURCES(obj)[i].ftGroupName);
            }
        }

        free(DSM_CORE_FT_GROUP_NAME_RESOURCES(obj));
        DSM_CORE_FT_GROUP_NAME_RESOURCES(obj) = NULL;
    }

    return ITS_SUCCESS;
}

static int
ImplClassesInitialize(
    DSM_CoreObject* obj)
{
    ITS_BOOLEAN implClassFound = ITS_FALSE;
    ITS_USHORT implClassIndex = 0;
    ITS_Class implClass;

    memset(&DSM_CORE_IMPL_CLASSES(obj), 0, sizeof(DSM_ImplClasses));

    /* TODO: review. */

    /* Note: need to retrieve all the DSM implementation classes from the list
     * of features (added using ITS_AddFeature). One way to do it would be to
     * have a function that allows to find classes with a partial match on the
     * class name (e.g. all DSM implementation class names must start with the
     * string "DSM Implementation Class"). There might be a better solution...
     */

    /* 
     * Temporary knowledge of the DSM Implementation class names is required.
     */

    #define DSM_STUB_IMPL_CLASS_NAME "DSM Implementation Class - STUB"
    #define DSM_GCS_IMPL_CLASS_NAME "DSM Implementation Class - GCS"
    #define DSM_SCI_IMPL_CLASS_NAME "DSM Implementation Class - SCI"

    implClass = ITS_FindFeature(DSM_STUB_IMPL_CLASS_NAME);

    if (implClass != NULL)
    {
        DSM_CORE_IMPL_CLASSES(obj).classes[implClassIndex++] = 
            (DSM_ImplClass)implClass;
        implClassFound = ITS_TRUE;
    }

    implClass = ITS_FindFeature(DSM_GCS_IMPL_CLASS_NAME);

    if (implClass != NULL)
    {
        DSM_CORE_IMPL_CLASSES(obj).classes[implClassIndex++] = 
            (DSM_ImplClass)implClass;
        implClassFound = ITS_TRUE;
    }
    
    implClass = ITS_FindFeature(DSM_SCI_IMPL_CLASS_NAME);

    if (implClass != NULL)
    {
        DSM_CORE_IMPL_CLASSES(obj).classes[implClassIndex++] = 
            (DSM_ImplClass)implClass;
        implClassFound = ITS_TRUE;
    }

    if (!implClassFound)
    {
        /* TODO: add trace. */
        return ITS_EMISSINGIMPL;
    }

    return ITS_SUCCESS;
}

static int
ImplClassesTerminate(
    DSM_CoreObject* obj)
{
    memset(&DSM_CORE_IMPL_CLASSES(obj), 0, sizeof(DSM_ImplClasses));
    return ITS_SUCCESS;
}

/*
 * CoreClassInitialize.
 */
static int
CoreClassInitialize(
    ITS_Class objClass)
{
    /* Dependency on socket subsystem. */
    return ITS_InitializeClass(itsSOCKET_Class);
}

/*
 * CoreClassTerminate.
 */
static void
CoreClassTerminate(
    ITS_Class objClass)
{
    /* Dependency on socket subsystem. */
    ITS_DestroyClass(itsSOCKET_Class);
}

/*
 * CoreCreateInstance.
 */
static int
CoreCreateInstance(
    ITS_Object obj, 
    va_list args)
{
    const char* configFileName = APPL_GetConfigFileName();
    ITS_USHORT maxNumNodes;
    ITS_USHORT maxNumProcesses;
    ITS_USHORT maxNumFtGroups;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    int ret;

    ITS_C_REQUIRE(!DSM_IsPreInitialized());

    maxNumNodes     = (ITS_USHORT)va_arg(args, int);
    maxNumProcesses = (ITS_USHORT)va_arg(args, int);
    maxNumFtGroups  = (ITS_USHORT)va_arg(args, int);
    nodeId          = (ITS_USHORT)va_arg(args, int);
    processId       = (ITS_USHORT)va_arg(args, int);

    if (DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }
    
    /* Set LOCKABLE sharedInstance. */
    LOCKABLE_SHARED_INSTANCE(itsDSM_CoreClass) = obj;

    DSM_CORE_MAX_NUM_NODES(obj)     = maxNumNodes;
    DSM_CORE_MAX_NUM_PROCESSES(obj) = maxNumProcesses;
    DSM_CORE_MAX_NUM_FT_GROUPS(obj) = maxNumFtGroups;

    if (nodeId >= maxNumNodes)
    {
        /* TODO: add trace. */
        return ITS_EINVNODE;
    }

    if (processId >= maxNumProcesses)
    {
        /* TODO: add trace. */
        return ITS_EINVPROCESS;
    }

    DSM_CORE_NODE_ID(obj)       = nodeId;
    DSM_CORE_PROCESS_ID(obj)    = processId;
    DSM_CORE_NUM_FT_GROUPS(obj) = 0; /* Initialization. */

    DSM_CORE_CONFIG_DB(obj) = RESFILE_CreateResourceManager(configFileName);
    if (DSM_CORE_CONFIG_DB(obj) == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    ret = ImplClassesInitialize((DSM_CoreObject*)obj);
    if (ret != ITS_SUCCESS)
    {
        RESFILE_DeleteResourceManager(DSM_CORE_CONFIG_DB(obj));
        return ret;
    }

    DSM_CORE_FT_GROUPS(obj) = calloc(maxNumFtGroups, sizeof(DSM_InstObject*));
    if (DSM_CORE_FT_GROUPS(obj) == NULL)
    {
        RESFILE_DeleteResourceManager(DSM_CORE_CONFIG_DB(obj));
        ImplClassesTerminate((DSM_CoreObject*)obj);
        return ITS_ENOMEM;
    }

    /* Node Name Resources create (default names). */
    ret = NodeNameResourcesCreate((DSM_CoreObject*)obj);
    if (ret != ITS_SUCCESS)
    {
        RESFILE_DeleteResourceManager(DSM_CORE_CONFIG_DB(obj));
        ImplClassesTerminate((DSM_CoreObject*)obj);
        free(DSM_CORE_FT_GROUPS(obj));
        ITS_TRACE_ERROR((
            "CoreCreateInstance: NodeNameResourcesCreate failed: %d\n",
            ret));
        return ret;
    }

    /* Process Name Resources create (default names). */
    ret = ProcessNameResourcesCreate((DSM_CoreObject*)obj);
    if (ret != ITS_SUCCESS)
    {
        RESFILE_DeleteResourceManager(DSM_CORE_CONFIG_DB(obj));
        ImplClassesTerminate((DSM_CoreObject*)obj);
        free(DSM_CORE_FT_GROUPS(obj));
        NodeNameResourcesDestroy((DSM_CoreObject*)obj);
        ITS_TRACE_ERROR((
            "CoreCreateInstance: ProcessNameResourcesCreate failed: %d\n",
            ret));
        return ret;
    }

    /* Fault Tolerance Group Name Resources create (default names). */
    ret = FtGroupNameResourcesCreate((DSM_CoreObject*)obj);
    if (ret != ITS_SUCCESS)
    {
        RESFILE_DeleteResourceManager(DSM_CORE_CONFIG_DB(obj));
        ImplClassesTerminate((DSM_CoreObject*)obj);
        free(DSM_CORE_FT_GROUPS(obj));
        NodeNameResourcesDestroy((DSM_CoreObject*)obj);
        ProcessNameResourcesDestroy((DSM_CoreObject*)obj);
        ITS_TRACE_ERROR((
            "CoreCreateInstance: FtGroupNameResourcesCreate failed: %d\n",
            ret));
        return ret;
    }

    DSM_CORE_CRITICAL_ERROR_NOTIFICATION_CALLBACKS(obj) = 
        CALLBACK_InitManager();
    if (DSM_CORE_CRITICAL_ERROR_NOTIFICATION_CALLBACKS(obj) == NULL)
    {
        RESFILE_DeleteResourceManager(DSM_CORE_CONFIG_DB(obj));
        ImplClassesTerminate((DSM_CoreObject*)obj);
        free(DSM_CORE_FT_GROUPS(obj));
        NodeNameResourcesDestroy((DSM_CoreObject*)obj);
        ProcessNameResourcesDestroy((DSM_CoreObject*)obj);
        FtGroupNameResourcesDestroy((DSM_CoreObject*)obj);
        ITS_TRACE_ERROR(("CoreCreateInstance: out of memory\n"));
        return ITS_ENOMEM;
    }

    /* Add pre-added critical error notification callbacks. */
    {
        PreAddedCriticalErrorNotificationCb** list =
            &preAddedCriticalErrorNotificationCbList;
        PreAddedCriticalErrorNotificationCb* element;
        CALLBACK_Manager* callbackManager = 
            DSM_CORE_CRITICAL_ERROR_NOTIFICATION_CALLBACKS(obj);

        while (*list != NULL)
        {
            element = *list;

            ITS_C_ASSERT(callbackManager != NULL);

            CALLBACK_AddCallback(
                callbackManager,
                element->cbFunction,
                element->userData);

            list = &(*list)->next;
        }
    }

    return ITS_SUCCESS;
}

/*
 * CoreDestroyInstance.
 */
static void
CoreDestroyInstance(
    ITS_Object obj)
{
    /* TODO: to be completed. */

    /* Free pre-added critical error notification callback list. */
    {
        PreAddedCriticalErrorNotificationCb* list =
            preAddedCriticalErrorNotificationCbList;
        PreAddedCriticalErrorNotificationCb* element;

        while (list != NULL)
        {
            element = list;

            list = list->next;

            free(element);
        }

        preAddedCriticalErrorNotificationCbList = NULL;
    }

    /* Free pre-added membership change callbacks. */
    {
        PreAddedMembershipChangeCb* list =
            preAddedMembershipChangeCbList;
        PreAddedMembershipChangeCb* element;

        while (list != NULL)
        {
            element = list;

            list = list->next;

            free(element);
        }

        preAddedMembershipChangeCbList = NULL;
    }

    /* Free pre-added event from Fault Tolerance Group callbacks. */
    {
        PreAddedEventFromFtGroupMemberCb* list =
            preAddedEventFromFtGroupMemberCbList;
        PreAddedEventFromFtGroupMemberCb* element;

        while (list != NULL)
        {
            element = list;

            list = list->next;

            free(element);
        }

        preAddedEventFromFtGroupMemberCbList = NULL;
    }

    if (DSM_CORE_CRITICAL_ERROR_NOTIFICATION_CALLBACKS(obj) != NULL)
    {
        CALLBACK_DestroyManager(
            DSM_CORE_CRITICAL_ERROR_NOTIFICATION_CALLBACKS(obj));
        DSM_CORE_CRITICAL_ERROR_NOTIFICATION_CALLBACKS(obj) = NULL;
    }

    NodeNameResourcesDestroy((DSM_CoreObject*)obj);
    ProcessNameResourcesDestroy((DSM_CoreObject*)obj);
    FtGroupNameResourcesDestroy((DSM_CoreObject*)obj);
    free(DSM_CORE_FT_GROUPS(obj));
    ImplClassesTerminate((DSM_CoreObject*)obj);

    if (DSM_CORE_CONFIG_DB(obj) != NULL)
    {
        RESFILE_DeleteResourceManager(DSM_CORE_CONFIG_DB(obj));
        DSM_CORE_CONFIG_DB(obj) = NULL;
    }

    /* Reset LOCKABLE sharedInstance. */
    LOCKABLE_SHARED_INSTANCE(itsDSM_CoreClass) = NULL;
}


ITSDLLAPI DSM_CoreClassRec itsDSM_CoreClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsLOCKABLE_ClassRec,   /* LOCKABLE is superclass   */
        sizeof(DSM_CoreObject),             /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_CORE_CLASS_NAME,                /* class name               */
        CoreClassInitialize,                /* class init               */
        CoreClassTerminate,                 /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        CoreCreateInstance,                 /* instance create          */
        CoreDestroyInstance,                /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* lockable part */
    {
        LOCKABLE_INHERIT,
        LOCKABLE_INHERIT,
        LOCKABLE_INHERIT,
        { 0 },
        NULL
    },
    /* dsm part */
    {
        NULL,
        NULL
    }
};

ITSDLLAPI ITS_Class itsDSM_CoreClass = (ITS_Class)&itsDSM_CoreClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM Init (initialization) class.
 **
 */

/*
 * InitClassInitialize.
 */
static int
InitClassInitialize(
    ITS_Class objClass)
{
    char ftGroupSectionName[DSM_MAX_CONFIG_SECTION_NAME_SIZE];
    char value[DSM_MAX_CONFIG_VALUE_SIZE];
    
    /* TODO: remove. */
    /*char key[DSM_MAX_CONFIG_KEY_SIZE];*/

    char buffer[16];
    DSM_CoreObject* coreObj;
    ITS_USHORT maxNumFtGroups;
    ITS_USHORT i, j;
    int ret;

    ret = DSM_PreInitializeFromConfig();
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL((
            "InitClassInitialize: DSM_PreInitializeFromConfig failed: %d\n",
            ret));;
        return ret;
    }

    ITS_C_ASSERT(DSM_IsPreInitialized());

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    maxNumFtGroups = DSM_CORE_MAX_NUM_FT_GROUPS(coreObj);

    for (i = 0; i < maxNumFtGroups; i++)
    {
        /* Build Fault Tolerance Group associated section name. */
        strcpy(ftGroupSectionName, DSM_FT_GROUP_STRING);
        sprintf(buffer, "%u", i);
        strcat(ftGroupSectionName, buffer);

        /* 
         * Check if there is a Fault Tolerance Group section with name in
         * Resource Manager (i.e. Configuration) Database.
         */

        /* TODO: config DB should be locked before following call. */
        /* Ideally might want to add a function to check if a section exists. */
        ret = RESFILE_Rewind(
                    DSM_CORE_CONFIG_DB(coreObj), 
                    ftGroupSectionName);
        if (ret == ITS_SUCCESS)
        {
            ITS_BOOLEAN dsmInitExplicit = ITS_FALSE;
            ITS_BOOLEAN dsmJoinExplicit = ITS_FALSE;

            if (RESFILE_GetKeyValueOf(
                                DSM_CORE_CONFIG_DB(coreObj),
                                ftGroupSectionName,
                                DSM_INIT_EXPLICIT_STRING,
                                value,
                                DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
            {
                dsmInitExplicit = (RESFILE_ParseNum(value) != 0);
            }

            if (RESFILE_GetKeyValueOf(
                                DSM_CORE_CONFIG_DB(coreObj),
                                ftGroupSectionName,
                                DSM_JOIN_EXPLICIT_STRING,
                                value,
                                DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
            {
                dsmJoinExplicit = (RESFILE_ParseNum(value) != 0);
            }

            if (dsmInitExplicit && !dsmJoinExplicit)
            {
                ITS_TRACE_WARNING((
                    "InitClassInitialize [FtGroupId: %u]: 'dsmInitExplicit' "
                    "implies 'dsmJoinExplicit' (automatically set)\n",
                    i));

                dsmJoinExplicit = ITS_TRUE;
            }

            if (!dsmInitExplicit)
            {
                ret = DSM_InitializeFromConfig(i);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_CRITICAL((
                        "InitClassInitialize [FtGroupId: %u]: "
                        "DSM_InitializeFromConfig failed: %d\n",
                        i,
                        ret));

                    /* Undo previous FtGroups. */
                    for (j = 0; j < i; j++)
                    {
                        if (DSM_IsInitialized(j))
                        {
                            if (DSM_IsFtGroupJoined(j))
                            {
                                DSM_LeaveFtGroup(j);
                            }

                            DSM_Terminate(j);
                        }
                    }

                    return ret;
                }

                ret = DSM_ConfigureFtGroupMembersFromConfig(i);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_CRITICAL((
                        "InitClassInitialize [FtGroupId: %u]: "
                        "DSM_ConfigureFtGroupMembersFromConfig failed: %d\n",
                        i,
                        ret));

                    DSM_Terminate(i);

                    /* Undo previous FtGroups. */
                    for (j = 0; j < i; j++)
                    {
                        if (DSM_IsInitialized(j))
                        {
                            if (DSM_IsFtGroupJoined(j))
                            {
                                DSM_LeaveFtGroup(j);
                            }

                            DSM_Terminate(j);
                        }
                    }

                    return ret;
                }

                ret = DSM_ConfigureMasterFtGroupMembersFromConfig(i);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_CRITICAL((
                        "InitClassInitialize [FtGroupId: %u]: "
                        "DSM_ConfigureMasterFtGroupMembersFromConfig failed: "
                        "%d\n",
                        i,
                        ret));

                    DSM_Terminate(i);

                    /* Undo previous FtGroups. */
                    for (j = 0; j < i; j++)
                    {
                        if (DSM_IsInitialized(j))
                        {
                            if (DSM_IsFtGroupJoined(j))
                            {
                                DSM_LeaveFtGroup(j);
                            }

                            DSM_Terminate(j);
                        }
                    }

                    return ret;
                }
            }

            if (!dsmJoinExplicit)
            {
                ret = DSM_JoinFtGroup(i);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_CRITICAL((
                        "InitClassInitialize [FtGroupId: %u]: DSM_JoinFtGroup "
                        "failed: %d\n",
                        i,
                        ret));

                    /* Undo. */
                    DSM_Terminate(i);

                    /* Undo previous FtGroups. */
                    for (j = 0; j < i; j++)
                    {
                        if (DSM_IsInitialized(j))
                        {
                            if (DSM_IsFtGroupJoined(j))
                            {
                                DSM_LeaveFtGroup(j);
                            }

                            DSM_Terminate(j);
                        }
                    }

                    return ret;
                }
            }
        }
        else
        {
            /* Nothing to do. */
        }
    }

    return ITS_SUCCESS;
}

/*
 * InitClassTerminate.
 */
static void
InitClassTerminate(
    ITS_Class objClass)
{
    char ftGroupSectionName[DSM_MAX_CONFIG_SECTION_NAME_SIZE];
    char value[DSM_MAX_CONFIG_VALUE_SIZE];
    char key[DSM_MAX_CONFIG_KEY_SIZE];
    char buffer[16];
    DSM_CoreObject* coreObj;
    ITS_USHORT maxNumFtGroups;
    ITS_USHORT i;
    int ret;

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    maxNumFtGroups = DSM_CORE_MAX_NUM_FT_GROUPS(coreObj);

    for (i = 0; i < maxNumFtGroups; i++)
    {
        /* Build Fault Tolerance Group associated section name. */
        strcpy(ftGroupSectionName, DSM_FT_GROUP_STRING);
        sprintf(buffer, "%u", i);
        strcat(ftGroupSectionName, buffer);

        /* 
         * Check if there is a Fault Tolerance Group section with name in
         * Resource Manager (i.e. Configuration) Database.
         */
    
        ret = RESFILE_GetKeyName(
                    DSM_CORE_CONFIG_DB(coreObj), 
                    ftGroupSectionName, 
                    key, 
                    DSM_MAX_CONFIG_KEY_SIZE);

        if (ret == ITS_SUCCESS)
        {
            ITS_BOOLEAN dsmInitExplicit = ITS_FALSE;
            ITS_BOOLEAN dsmJoinExplicit = ITS_FALSE;

            if (RESFILE_GetKeyValueOf(
                                DSM_CORE_CONFIG_DB(coreObj),
                                ftGroupSectionName,
                                DSM_INIT_EXPLICIT_STRING,
                                value,
                                DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
            {
                dsmInitExplicit = (RESFILE_ParseNum(value) != 0);
            }

            if (RESFILE_GetKeyValueOf(
                                DSM_CORE_CONFIG_DB(coreObj),
                                ftGroupSectionName,
                                DSM_JOIN_EXPLICIT_STRING,
                                value,
                                DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
            {
                dsmJoinExplicit = (RESFILE_ParseNum(value) != 0);
            }

            if (dsmInitExplicit && !dsmJoinExplicit)
            {
                /* 
                 * TODO: add warning trace.
                 * (dsmInitExplicit => dsmJoinExplicit). 
                 */

                dsmJoinExplicit = ITS_TRUE;
            }

            if (!dsmJoinExplicit)
            {
                if (DSM_IsFtGroupJoined(i))
                {
                    ret = DSM_LeaveFtGroup(i);
                    if (ret != ITS_SUCCESS)
                    {
                        /* TODO: add trace. */
                    }
                }
            }

            if (!dsmInitExplicit)
            {
                if (DSM_IsInitialized(i))
                {
                    DSM_Terminate(i);
                }
            }
        }
    }

    DSM_PostTerminate();
}


ITSDLLAPI DSM_InitClassRec itsDSM_InitClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,                  /* CORE is superclass       */
        0,                                  /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_INIT_CLASS_NAME,                /* class name               */
        InitClassInitialize,                /* class init               */
        InitClassTerminate,                 /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        ITS_INST_NO_CONST,                  /* instance create          */
        ITS_INST_NO_DEST,                   /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsDSM_InitClass = (ITS_Class)&itsDSM_InitClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** Configurable Fault Tolerance Groups (major IntelliSS7 subsystems).
 **
 */

ITSDLLAPI ITS_USHORT DSM_TcapFtGroupId        = 0;
ITSDLLAPI ITS_USHORT DSM_SccpFtGroupId        = 0;
ITSDLLAPI ITS_USHORT DSM_Mtp3FtGroupId        = 0;
ITSDLLAPI ITS_USHORT DSM_IsupFtGroupId        = 0;
ITSDLLAPI ITS_USHORT DSM_RoutingFtGroupId     = 0;
ITSDLLAPI ITS_USHORT DSM_TimersFtGroupId      = 0;
ITSDLLAPI ITS_USHORT DSM_MgmtDataFtGroupId    = 0;
ITSDLLAPI ITS_USHORT DSM_TcapTimersFtGroupId  = 2;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM API functions.
 **
 */

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Pre-initialize DSM subsystem from Resource Manager configuration.
 *      - Called automatically during Engine initialization.
 *      - Must be called only once per process.
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
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_PreInitializeFromConfig()
{
    const char* configFileName = APPL_GetConfigFileName();
    RESFILE_Manager* configDb;
    char value[DSM_MAX_CONFIG_VALUE_SIZE];
    ITS_USHORT maxNumNodes;
    ITS_USHORT maxNumProcesses;
    ITS_USHORT maxNumFtGroups;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    DSM_CoreObject* coreObj;

    ITS_C_REQUIRE(!DSM_IsPreInitialized());

    if (DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    configDb = RESFILE_CreateResourceManager(configFileName);

    if (configDb)
    {
        /* Retrieve maxNumNodes. */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_MAX_NUM_NODES_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            maxNumNodes = (ITS_USHORT)RESFILE_ParseNum(value);
        }
        else
        {
            /* TODO: add trace. */
            return ITS_EINVCONFIG;
        }

        /* Retrieve maxNumProcesses. */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_MAX_NUM_PROCESSES_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            maxNumProcesses = (ITS_USHORT)RESFILE_ParseNum(value);
        }
        else
        {
            /* TODO: add trace. */
            return ITS_EINVCONFIG;
        }

        /* Retrieve maxNumFtGroups. */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_MAX_NUM_FT_GROUPS_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            maxNumFtGroups = (ITS_USHORT)RESFILE_ParseNum(value);
        }
        else
        {
            /* TODO: add trace. */
            return ITS_EINVCONFIG;
        }

        /* Retrieve nodeId. */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_NODE_ID_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            nodeId = (ITS_USHORT)RESFILE_ParseNum(value);
        }
        else
        {
            /* TODO: add trace. */
            return ITS_EINVCONFIG;
        }

        /* Retrieve processId. */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_PROCESS_ID_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            processId = (ITS_USHORT)RESFILE_ParseNum(value);
        }
        else
        {
            /* TODO: add trace. */
            return ITS_EINVCONFIG;
        }

        /* Retrieve TcapFtGroupId (optional). */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_TCAP_FT_GROUP_ID_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_TcapFtGroupId = (ITS_USHORT)RESFILE_ParseNum(value);
        }

        /* Retrieve SccpFtGroupId (optional). */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_SCCP_FT_GROUP_ID_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_SccpFtGroupId = (ITS_USHORT)RESFILE_ParseNum(value);
        }

        /* Retrieve Mtp3FtGroupId (optional). */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_MTP3_FT_GROUP_ID_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_Mtp3FtGroupId = (ITS_USHORT)RESFILE_ParseNum(value);
        }

        /* Retrieve IsupFtGroupId (optional). */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_ISUP_FT_GROUP_ID_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_IsupFtGroupId = (ITS_USHORT)RESFILE_ParseNum(value);
        }

        /* Retrieve RoutingFtGroupId (optional). */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_ROUTING_FT_GROUP_ID_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_RoutingFtGroupId = (ITS_USHORT)RESFILE_ParseNum(value);
        }

        /* Retrieve TimersFtGroupId (optional). */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_TIMERS_FT_GROUP_ID_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_TimersFtGroupId = (ITS_USHORT)RESFILE_ParseNum(value);
        }

        /* Retrieve TcapTimersFtGroupId (optional). */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_TCAP_TIMERS_FT_GROUP_ID_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_TcapTimersFtGroupId = (ITS_USHORT)RESFILE_ParseNum(value);
        }

        /* Retrieve MgmtDataFtGroupId (optional). */
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            DSM_FAULT_TOLERANCE_STRING,
                            DSM_MGMT_DATA_FT_GROUP_ID_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_MgmtDataFtGroupId = (ITS_USHORT)RESFILE_ParseNum(value);
        }

    }
    else
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    coreObj = (DSM_CoreObject*)ITS_ConstructObject(
                                            itsDSM_CoreClass,
                                            (int)maxNumNodes,
                                            (int)maxNumProcesses,
                                            (int)maxNumFtGroups,
                                            (int)nodeId,
                                            (int)processId);

    RESFILE_DeleteResourceManager(configDb);

    if (coreObj == NULL)
    {
        /* TODO: add trace. */
        return ITS_EPREINITFAIL;
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Pre-initialize DSM subsystem with specified configuration.
 *      - Must be called only once per process.
 *
 *  Input Parameters:
 *      maxNumFtGroups - maximum number of Fault Tolerance Groups.
 *      maxNumProcesses - maximum number of processes.
 *      maxNumNodes - maximum number of nodes.
 *      nodeId - current node identifier.
 *      processId - current process identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_PreInitialize(
    ITS_USHORT maxNumFtGroups,
    ITS_USHORT maxNumProcesses,
    ITS_USHORT maxNumNodes,
    ITS_USHORT nodeId,
    ITS_USHORT processId)
{
    DSM_CoreObject* coreObj;

    ITS_C_REQUIRE(!DSM_IsPreInitialized());

    if (DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    /* TODO: add check consistency with RM DB and warnings if inconsistent? */

    coreObj = (DSM_CoreObject*)ITS_ConstructObject(
                                            itsDSM_CoreClass,
                                            (int)maxNumNodes,
                                            (int)maxNumProcesses,
                                            (int)maxNumFtGroups,
                                            (int)nodeId,
                                            (int)processId);

    if (coreObj == NULL)
    {
        /* TODO: add trace. */
        return ITS_EPREINITFAIL;
    }

    return ITS_SUCCESS; 
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Post-terminate DSM subsystem.
 *      - Called automatically during Engine termination.
 *      - Must be called only once per process.
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
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void 
DSM_PostTerminate()
{
    ITS_Object obj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return;
    }

    obj = LOCKABLE_GetShared(itsDSM_CoreClass);

    ITS_DestructObject(obj);

    return;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Initialize a Fault Tolerance Group from Resource Manager configuration.
 *      - Called automatically during Engine initialization unless explicit
 *        initialization/termination is specified (through 'dsmInitExplicit').
 *      - Must be called once per Fault Tolerance Group.
 *      - Explicit initialization/termination implies explicit join/leave.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_InitializeFromConfig(
    ITS_USHORT ftGroupId)
{
    char value[DSM_MAX_CONFIG_VALUE_SIZE];
    char ftGroupSectionName[DSM_MAX_CONFIG_SECTION_NAME_SIZE];
    char buffer[16];
    ITS_USHORT ftGroupIdFromConfig;
    ITS_UINT maxNumTables;
    ITS_UINT dsmSize;
    const void* dsmBaseAddress;
    char dsmType[DSM_MAX_CONFIG_DSM_TYPE_SIZE];
    ITS_UINT dsmJoinFtGroupTimeout;
    ITS_UINT dsmRowLockTimeout;
    ITS_BOOLEAN dsmSyncExplicit;
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(!DSM_IsInitialized(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    /* Build Fault Tolerance Group associated section name. */
    strcpy(ftGroupSectionName, DSM_FT_GROUP_STRING);
    sprintf(buffer, "%u", ftGroupId);
    strcat(ftGroupSectionName, buffer);
     
    /* Retrieve ftGroupIdFromConfig. */
    if (RESFILE_GetKeyValueOf(
                        DSM_CORE_CONFIG_DB(coreObj), 
                        ftGroupSectionName,
                        DSM_FT_GROUP_ID_STRING,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        ftGroupIdFromConfig = (ITS_USHORT)RESFILE_ParseNum(value);

        /* Consistency check. */
        if (ftGroupIdFromConfig != ftGroupId)
        {
            /* TODO: add trace. */
            return ITS_EINVCONFIG;
        }
    }
    else
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    /* Retrieve maxNumTables. */
    if (RESFILE_GetKeyValueOf(
                        DSM_CORE_CONFIG_DB(coreObj), 
                        ftGroupSectionName,
                        DSM_MAX_NUM_TABLES_STRING,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        maxNumTables = (ITS_UINT)RESFILE_ParseNum(value);
    }
    else
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    /* Retrieve dsmSize. */
    if (RESFILE_GetKeyValueOf(
                        DSM_CORE_CONFIG_DB(coreObj), 
                        ftGroupSectionName,
                        DSM_SIZE_STRING,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        dsmSize = (ITS_UINT)RESFILE_ParseNum(value);
    }
    else
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    /* Retrieve dsmBaseAddress. */
    if (RESFILE_GetKeyValueOf(
                        DSM_CORE_CONFIG_DB(coreObj), 
                        ftGroupSectionName,
                        DSM_BASE_ADDRESS_STRING,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        dsmBaseAddress = (const void*)RESFILE_ParseNum(value);
    }
    else
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    /* Retrieve dsmType. */
    if (RESFILE_GetKeyValueOf(
                        DSM_CORE_CONFIG_DB(coreObj), 
                        ftGroupSectionName,
                        DSM_TYPE_STRING,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        ITS_C_ASSERT(DSM_MAX_CONFIG_DSM_TYPE_SIZE > 1);
        strncpy(dsmType, value, DSM_MAX_CONFIG_DSM_TYPE_SIZE - 1);
        dsmType[DSM_MAX_CONFIG_DSM_TYPE_SIZE - 1] = '\0';
    }
    else
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    /* Retrieve dsmJoinFtGroupTimeout (if present). */
    if (RESFILE_GetKeyValueOf(
                        DSM_CORE_CONFIG_DB(coreObj), 
                        ftGroupSectionName,
                        DSM_JOIN_FT_GROUP_TIMEOUT_STRING,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        dsmJoinFtGroupTimeout = (ITS_UINT)RESFILE_ParseNum(value);
    }
    else
    {
        /* Default value. */
        dsmJoinFtGroupTimeout = DSM_DEFAULT_JOIN_FT_GROUP_TIMEOUT;
    }

    /* Retrieve dsmRowLockTimeout (if present). */
    if (RESFILE_GetKeyValueOf(
                        DSM_CORE_CONFIG_DB(coreObj), 
                        ftGroupSectionName,
                        DSM_ROW_LOCK_TIMEOUT_STRING,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        dsmRowLockTimeout = (ITS_UINT)RESFILE_ParseNum(value);
    }
    else
    {
        /* Default value. */
        dsmRowLockTimeout = DSM_DEFAULT_ROW_LOCK_TIMEOUT;
    }

    /* Retrieve dsmSyncExplicit (if present). */
    if (RESFILE_GetKeyValueOf(
                        DSM_CORE_CONFIG_DB(coreObj), 
                        ftGroupSectionName,
                        DSM_ROW_LOCK_TIMEOUT_STRING,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        dsmSyncExplicit = (RESFILE_ParseNum(value) != 0);
    }
    else
    {
        /* Default value. */
        dsmSyncExplicit = ITS_FALSE;
    }



    instObj = (DSM_InstObject*)ITS_ConstructObject(
                                            itsDSM_InstClass,
                                            ftGroupId,
                                            (int)maxNumTables,
                                            (int)dsmSize,
                                            dsmBaseAddress,
                                            dsmType,
                                            (int)dsmJoinFtGroupTimeout,
                                            (int)dsmRowLockTimeout,
                                            (int)dsmSyncExplicit);
    if (instObj == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINITFAIL;
    }
 
    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Initialize a Fault Tolerance Group with specified configuration.
 *      - Arguments that are specific to a DSM implementation (e.g. GCS/SCI/
 *        other) are passed as character strings of key/value pair through
 *        the variable argument list. For instance:
 *          - "dsmGcsDaemonName=3267"
 *          - "dsmGcsSyncMemUseTcp=1"
 *          - "dsmGcsSyncExplicit=1"
 *      - Must be called once per Fault Tolerance Group.
 *      - Last (mandatory) variable argument must be NULL (used as a
 *        terminator).
 *      - All variable arguments must be of type character string (char*).
 *      - Explicit initialization/termination implies explicit join/leave.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *      maxNumTables - maximum number of tables.
 *      dsmSize - sizeof Distributed Shared Memory in octets.
 *      dsmBaseAddress - Distributed Shared Memory base address.
 *      dsmType - type of DSM implementation (e.g. "GCS", "SCI", "STUB"...).
 *      
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_Initialize(
    ITS_USHORT  ftGroupId,
    ITS_UINT    maxNumTables,
    ITS_UINT    dsmSize,
    const void* dsmBaseAddress,
    const char* dsmType,
    ...)
{
    va_list alist;
    const char *str;
    DSM_InstObject* instObj;
    ITS_UINT dsmJoinFtGroupTimeout;
    ITS_UINT dsmRowLockTimeout;
    ITS_BOOLEAN dsmSyncExplicit;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(!DSM_IsInitialized(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    /* 
     * Retrieve and process variable arguments. 
     */

    va_start(alist, dsmType);

    while ((str = va_arg(alist, const char*)) != NULL)
    {
        /* TODO: add processing for each variable argument. They are
         * (key, value) pairs to be added to the RM DB. Warnings if
         * consistency conflicts.
         */
    }

    va_end(alist);

    /* If not retrieved as variable argument. */
    dsmJoinFtGroupTimeout = DSM_DEFAULT_JOIN_FT_GROUP_TIMEOUT;

    /* If not retrieved as variable argument. */
    dsmRowLockTimeout = DSM_DEFAULT_ROW_LOCK_TIMEOUT;

    /* If not retrieved as variable argument. */
    dsmSyncExplicit = ITS_FALSE;
    
    instObj = (DSM_InstObject*)ITS_ConstructObject(
                                            itsDSM_InstClass,
                                            (int)ftGroupId,
                                            (int)maxNumTables,
                                            (int)dsmSize,
                                            dsmBaseAddress,
                                            dsmType,
                                            (int)dsmJoinFtGroupTimeout,
                                            (int)dsmRowLockTimeout,
                                            (int)dsmSyncExplicit);
    if (instObj == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINITFAIL;
    }
 
    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Terminate a Fault Tolerance Group.
 *      - Called automatically during Engine termination unless explicit
 *        initialization/termination is specified (through 'dsmInitExplicit').
 *      - Must be called once per Fault Tolerance Group.
 *      - Explicit initialization/termination implies explicit join/leave.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
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
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void 
DSM_Terminate(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    ITS_DestructObject((ITS_Object)instObj);

    return;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Is DSM pre-initialized?
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
 *      ITS_TRUE if DSM is pre-initialized and ITS_FALSE if it is not.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_BOOLEAN 
DSM_IsPreInitialized()
{
    return LOCKABLE_GetShared(itsDSM_CoreClass) != NULL;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Is Fault Tolerance Group (implies DSM) initialized?
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if Fault Tolerance Group is initialized and ITS_FALSE if it is
 *      not.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_BOOLEAN 
DSM_IsInitialized(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_FALSE;
    }

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    if (instObj != NULL)
    {
        if (DSM_INST_FT_GROUP_ID(instObj) != DSM_INVALID_FT_GROUP_ID)
        {
            return ITS_TRUE;
        }
        else
        {
            return ITS_FALSE;
        }
    }
    else
    {
        return ITS_FALSE;
    }
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve maximum number of nodes (configuration specified).
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
 *      Maximum number of nodes on success or zero on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_USHORT 
DSM_GetMaxNumNodes()
{
    DSM_CoreObject* coreObj;

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    
    return DSM_CORE_MAX_NUM_NODES(coreObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve maximum number of processes (configuration specified).
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
 *      Maximum number of processes on success or zero on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_USHORT 
DSM_GetMaxNumProcesses()
{
    DSM_CoreObject* coreObj;

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    
    return DSM_CORE_MAX_NUM_PROCESSES(coreObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve maximum number of Fault Tolerance Groups (configuration
 *      specified).
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
 *      Maximum number of Fault Tolerance Groups on success or zero on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_USHORT 
DSM_GetMaxNumFtGroups()
{
    DSM_CoreObject* coreObj;

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    
    return DSM_CORE_MAX_NUM_FT_GROUPS(coreObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve maximum number of tables (configuration specified).
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
 *      Maximum number of tables on success or zero on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_UINT 
DSM_GetMaxNumTables(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    if (DSM_INST_FT_GROUP_ID(instObj) == DSM_INVALID_FT_GROUP_ID)
    {
        return 0;
    }

    return DSM_INST_MAX_NUM_TABLES(instObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Configure all the Fault Tolerance Group Members of a Fault Tolerance
 *      Group from Resource Manager configuration.
 *      - Called automatically during Engine initialization.
 *      - Must include self (in Resource Manager configuration).
 *      - Must be called for each Fault Tolerance Group.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_ConfigureFtGroupMembersFromConfig(
    ITS_USHORT ftGroupId)
{
    DSM_FtGroupMember ftGroupMembers[DSM_MAX_FT_GROUP_MEMBERS];
    char value[DSM_MAX_CONFIG_VALUE_SIZE];
    char key[DSM_MAX_CONFIG_KEY_SIZE];
    char ftGroupSectionName[DSM_MAX_CONFIG_SECTION_NAME_SIZE];
    char buffer[16];
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    ITS_USHORT memberNodeId = 0;
    ITS_USHORT memberProcessId;
    ITS_USHORT specifiedNumFtGroupMembers;
    ITS_USHORT numFtGroupMembers;
    ITS_USHORT i, j;
    int ret;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    nodeId = DSM_CORE_NODE_ID(coreObj);
    processId = DSM_CORE_PROCESS_ID(coreObj);

    /* Build Fault Tolerance Group associated section name. */
    strcpy(ftGroupSectionName, DSM_FT_GROUP_STRING);
    sprintf(buffer, "%u", ftGroupId);
    strcat(ftGroupSectionName, buffer);
     
    /* Retrieve numFtGroupMembers. */
    if (RESFILE_GetKeyValueOf(
                        DSM_CORE_CONFIG_DB(coreObj), 
                        ftGroupSectionName,
                        DSM_NUM_FT_GROUP_MEMBERS_STRING,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        specifiedNumFtGroupMembers = (ITS_USHORT)RESFILE_ParseNum(value);

        if (specifiedNumFtGroupMembers > DSM_MAX_FT_GROUP_MEMBERS)
        {
            /* TODO: add trace. */
            return ITS_EINVFTGROUPMEMBERS;
        }
    }
    else
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    ret = RESFILE_Lock(DSM_CORE_CONFIG_DB(coreObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_ConfigureFtGroupMembersFromConfig [FtGroupId: %u]: "
            "RESFILE_Lock failed: %d\n",
            ftGroupId,
            ret));
        return ret;
    }

    ret = RESFILE_Rewind(
                    DSM_CORE_CONFIG_DB(coreObj),
                    ftGroupSectionName);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_ConfigureFtGroupMembersFromConfig [FtGroupId: %u]: "
            "RESFILE_Rewind failed: %d\n",
            ftGroupId,
            ret));
        return ret;
    }

    i = 0;
    j = 0;
    numFtGroupMembers = 0;

    while (
        RESFILE_GetKeyName(
                        DSM_CORE_CONFIG_DB(coreObj),
                        ftGroupSectionName,
                        key,
                        DSM_MAX_CONFIG_KEY_SIZE) == ITS_SUCCESS &&
        RESFILE_GetKeyValue(
                        DSM_CORE_CONFIG_DB(coreObj),
                        ftGroupSectionName,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        if (strcmp(key, DSM_FT_GROUP_MEMBER_NODE_ID_STRING) == 0)
        {
            memberNodeId = (ITS_USHORT)RESFILE_ParseNum(value);
            i++;
        }

        if (strcmp(key, DSM_FT_GROUP_MEMBER_PROCESS_ID_STRING) == 0)
        {
            memberProcessId = (ITS_USHORT)RESFILE_ParseNum(value);
            j++;

            if (i == j)
            {
                ftGroupMembers[numFtGroupMembers].nodeId = 
                    memberNodeId;
                ftGroupMembers[numFtGroupMembers].processId = 
                    memberProcessId;
                numFtGroupMembers++;
            }
            else
            {
                ITS_TRACE_WARNING((
                    "DSM_ConfigureFtGroupMembersFromConfig [FtGroupId: %u]: "
                    "inconsistency: each node identifier MUST be followed by "
                    "a process identifier\n",
                    ftGroupId));
                break;
            }
        }
    }
              
    ret = RESFILE_Unlock(DSM_CORE_CONFIG_DB(coreObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_ConfigureFtGroupMembersFromConfig [FtGroupId: %u]: "
            "RESFILE_Unlock failed: %d\n",
            ftGroupId,
            ret));
        return ret;
    }

    if (numFtGroupMembers != specifiedNumFtGroupMembers)
    {
        ITS_TRACE_ERROR((
            "DSM_ConfigureFtGroupMembersFromConfig [FtGroupId: %u]: "
            "inconsistency between specified number of Fault Tolerance Group "
            "members and number of node or process identifiers\n",
            ftGroupId));
        return ITS_EINVCONFIG;
    }

    ret = DSM_ConfigureFtGroupMembers(
                ftGroupId,
                numFtGroupMembers,
                ftGroupMembers);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_ConfigureFtGroupMembersFromConfig [FtGroupId: %u]: "
            "DSM_ConfigureFtGroupMembers failed: %d\n",
            ftGroupId,
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Configure all the Fault Tolerance Group Members of a Fault Tolerance
 *      Group explicitly.
 *      - Must include self.
 *      - Must be called for each Fault Tolerance Group.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *      numFtGroupMembers - number of Fault Tolerance Group members.
 *      ftGroupMembers - Fault Tolerance Group members (array of).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_ConfigureFtGroupMembers(
    ITS_USHORT ftGroupId,
    ITS_USHORT numFtGroupMembers,
    const DSM_FtGroupMember* ftGroupMembers)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    ITS_USHORT      nodeId;
    ITS_USHORT      processId;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));
    ITS_C_REQUIRE(numFtGroupMembers > 0);
    ITS_C_REQUIRE(ftGroupMembers != NULL);

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (numFtGroupMembers > DSM_MAX_FT_GROUP_MEMBERS)
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUPMEMBERS;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    nodeId = DSM_CORE_NODE_ID(coreObj);
    processId = DSM_CORE_PROCESS_ID(coreObj);

    if (!HasFtGroupMember(
                    numFtGroupMembers, 
                    ftGroupMembers, 
                    nodeId, 
                    processId))
    {
        /* Must include self. */

        /* TODO: add trace. */
        return ITS_EINVFTGROUPMEMBERS;
    }

    if (DSM_INST_FT_GROUP_MEMBERS(instObj) != NULL)
    {
        /* Cannot be (dynamically) reconfigured (for one instance). */

        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    DSM_INST_FT_GROUP_MEMBERS(instObj) = 
        malloc(numFtGroupMembers * sizeof(DSM_FtGroupMember));
    if (DSM_INST_FT_GROUP_MEMBERS(instObj) == NULL)
    {
        return ITS_ENOMEM;
    }

    memcpy(
        DSM_INST_FT_GROUP_MEMBERS(instObj), 
        ftGroupMembers, 
        numFtGroupMembers * sizeof(DSM_FtGroupMember));

    DSM_INST_NUM_FT_GROUP_MEMBERS(instObj) = numFtGroupMembers;

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Configure all the Master Fault Tolerance Group Members of a Fault 
 *      Tolerance Group from Resource Manager configuration.
 *      - Called automatically during Engine initialization.
 *      - Must not include self (in Resource Manager configuration).
 *      - Must be called for each Fault Tolerance Group.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_ConfigureMasterFtGroupMembersFromConfig(
    ITS_USHORT ftGroupId)
{
    DSM_FtGroupMember masterFtGroupMembers[DSM_MAX_MASTER_FT_GROUP_MEMBERS];
    char value[DSM_MAX_CONFIG_VALUE_SIZE];
    char key[DSM_MAX_CONFIG_KEY_SIZE];
    char ftGroupSectionName[DSM_MAX_CONFIG_SECTION_NAME_SIZE];
    char buffer[16];
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    ITS_USHORT masterMemberNodeId = 0;
    ITS_USHORT masterMemberProcessId;
    ITS_USHORT specifiedNumMasterFtGroupMembers;
    ITS_USHORT numMasterFtGroupMembers;
    ITS_USHORT i, j;
    int ret;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    nodeId = DSM_CORE_NODE_ID(coreObj);
    processId = DSM_CORE_PROCESS_ID(coreObj);

    /* Build Fault Tolerance Group associated section name. */
    strcpy(ftGroupSectionName, DSM_FT_GROUP_STRING);
    sprintf(buffer, "%u", ftGroupId);
    strcat(ftGroupSectionName, buffer);
     
    /* Retrieve numMasterFtGroupMembers. */
    if (RESFILE_GetKeyValueOf(
                        DSM_CORE_CONFIG_DB(coreObj), 
                        ftGroupSectionName,
                        DSM_NUM_MASTER_FT_GROUP_MEMBERS_STRING,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        specifiedNumMasterFtGroupMembers = (ITS_USHORT)RESFILE_ParseNum(value);

        if (specifiedNumMasterFtGroupMembers > DSM_MAX_MASTER_FT_GROUP_MEMBERS)
        {
            /* TODO: add trace. */
            return ITS_EINVFTGROUPMEMBERS;
        }
    }
    else
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    ret = RESFILE_Lock(DSM_CORE_CONFIG_DB(coreObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_ConfigureMasterFtGroupMembersFromConfig [FtGroupId: %u]: "
            "RESFILE_Lock failed: %d\n",
            ftGroupId,
            ret));
        return ret;
    }

    ret = RESFILE_Rewind(
                    DSM_CORE_CONFIG_DB(coreObj),
                    ftGroupSectionName);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_ConfigureMasterFtGroupMembersFromConfig [FtGroupId: %u]: "
            "RESFILE_Rewind failed: %d\n",
            ftGroupId,
            ret));
        return ret;
    }

    i = 0;
    j = 0;
    numMasterFtGroupMembers = 0;

    while (
        RESFILE_GetKeyName(
                        DSM_CORE_CONFIG_DB(coreObj),
                        ftGroupSectionName,
                        key,
                        DSM_MAX_CONFIG_KEY_SIZE) == ITS_SUCCESS &&
        RESFILE_GetKeyValue(
                        DSM_CORE_CONFIG_DB(coreObj),
                        ftGroupSectionName,
                        value,
                        DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
    {
        if (strcmp(key, DSM_MASTER_FT_GROUP_MEMBER_NODE_ID_STRING) == 0)
        {
            masterMemberNodeId = (ITS_USHORT)RESFILE_ParseNum(value);
            i++;
        }

        if (strcmp(key, DSM_MASTER_FT_GROUP_MEMBER_PROCESS_ID_STRING) == 0)
        {
            masterMemberProcessId = (ITS_USHORT)RESFILE_ParseNum(value);
            j++;

            if (i == j)
            {
                masterFtGroupMembers[numMasterFtGroupMembers].nodeId = 
                    masterMemberNodeId;
                masterFtGroupMembers[numMasterFtGroupMembers].processId = 
                    masterMemberProcessId;
                numMasterFtGroupMembers++;
            }
            else
            {
                ITS_TRACE_WARNING((
                    "DSM_ConfigureMasterFtGroupMembersFromConfig "
                    "[FtGroupId: %u]: inconsistency: each node identifier MUST"
                    " be followed by a process identifier\n",
                    ftGroupId));
                break;
            }
        }
    }
              
    ret = RESFILE_Unlock(DSM_CORE_CONFIG_DB(coreObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_ConfigureMasterFtGroupMembersFromConfig [FtGroupId: %u]: "
            "RESFILE_Unlock failed: %d\n",
            ftGroupId,
            ret));
        return ret;
    }

    if (numMasterFtGroupMembers != specifiedNumMasterFtGroupMembers)
    {
        ITS_TRACE_ERROR((
            "DSM_ConfigureMasterFtGroupMembersFromConfig [FtGroupId: %u]: "
            "inconsistency between specified number of Master Fault Tolerance "
            "Group members and number of node or process identifiers\n",
            ftGroupId));
        return ITS_EINVCONFIG;
    }

    if (numMasterFtGroupMembers > 0)
    {
        ret = DSM_ConfigureMasterFtGroupMembers(
                    ftGroupId,
                    numMasterFtGroupMembers,
                    masterFtGroupMembers);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "DSM_ConfigureMasterFtGroupMembersFromConfig [FtGroupId: %u]: "
                "DSM_ConfigureMasterFtGroupMembers failed: %d\n",
            ftGroupId,
            ret));
            return ret;
        }
    }
    else
    {
        /* Nothing to do. */
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Configure all the Master Fault Tolerance Group Members of a Fault 
 *      Tolerance Group explicitly.
 *      - Must not include self.
 *      - Must be called for each Fault Tolerance Group.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *      numMasterFtGroupMembers - number of Master Fault Tolerance Group 
 *          members.
 *      masterFtGroupMembers - Master Fault Tolerance Group members (array of).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_ConfigureMasterFtGroupMembers(
    ITS_USHORT ftGroupId,
    ITS_USHORT numMasterFtGroupMembers,
    const DSM_FtGroupMember* masterFtGroupMembers)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    ITS_USHORT      nodeId;
    ITS_USHORT      processId;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));
    ITS_C_REQUIRE(numMasterFtGroupMembers > 0);
    ITS_C_REQUIRE(masterFtGroupMembers != NULL);

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (numMasterFtGroupMembers > DSM_MAX_MASTER_FT_GROUP_MEMBERS)
    {
        /* TODO: add trace. */
        return ITS_EINVMASTERFTGROUPMEMBERS;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    nodeId = DSM_CORE_NODE_ID(coreObj);
    processId = DSM_CORE_PROCESS_ID(coreObj);

    if (HasFtGroupMember(
                    numMasterFtGroupMembers, 
                    masterFtGroupMembers, 
                    nodeId, 
                    processId))
    {
        /* Must not include self. */

        /* TODO: add trace. */
        return ITS_EINVMASTERFTGROUPMEMBERS;
    }

    if (DSM_INST_MASTER_FT_GROUP_MEMBERS(instObj) != NULL)
    {
        /* Cannot be (dynamically) reconfigured (for one instance). */

        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    DSM_INST_MASTER_FT_GROUP_MEMBERS(instObj) =
        malloc(numMasterFtGroupMembers * sizeof(DSM_FtGroupMember));
    if (DSM_INST_MASTER_FT_GROUP_MEMBERS(instObj) == NULL)
    {
        return ITS_ENOMEM;
    }

    memcpy(
        DSM_INST_MASTER_FT_GROUP_MEMBERS(instObj),
        masterFtGroupMembers,
        numMasterFtGroupMembers * sizeof(DSM_FtGroupMember));

    DSM_INST_NUM_MASTER_FT_GROUP_MEMBERS(instObj) = numMasterFtGroupMembers;

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Join a Fault Tolerance Group.
 *      - Called automatically during Engine initialization unless explicit
 *        join/leave is specified (through 'dsmJoinExplicit').
 *      - Typically must be called once for each Fault Tolerance Group.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_JoinFtGroup(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));
    ITS_C_REQUIRE(!DSM_IsFtGroupJoined(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (DSM_IsFtGroupJoined(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVJOINSTATE;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_JOIN_FT_GROUP(implClass)(
                coreObj, 
                ftGroupId);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Leave a Fault Tolerance Group.
 *      - Called automatically during Engine termination unless explicit join/
 *        leave is specified (through 'dsmJoinExplicit').
 *      - Typically must be called once for each Fault Tolerance Group.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_LeaveFtGroup(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));
    ITS_C_REQUIRE(DSM_IsFtGroupJoined(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (!DSM_IsFtGroupJoined(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVJOINSTATE;
    }

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_LEAVE_FT_GROUP(implClass)(
                coreObj,
                ftGroupId);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Is Fault Tolerance Group joined?
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if Fault Tolerance Group joined and ITS_FALSE if it is not.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
DSM_IsFtGroupJoined(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;

    if (!DSM_IsPreInitialized())
    {
        return ITS_FALSE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        return ITS_FALSE;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        return ITS_FALSE;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    return DSM_INST_FT_GROUP_JOINED(instObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Synchronize DSM Instance with one of the specified Master Fault
 *      Tolerance Group members (according to their statuses).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *      msecs - timeout in milliseconds.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_SynchronizeDsm(
    ITS_USHORT ftGroupId,
    ITS_UINT msecs)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));
    ITS_C_REQUIRE(DSM_IsFtGroupJoined(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (!DSM_IsFtGroupJoined(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVJOINSTATE;
    }

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_SYNCHRONIZE_DSM(implClass)(
                coreObj, 
                ftGroupId,
                msecs);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve current node identifier (configuration specified).
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
 *      Current node identifier on success or DSM_INVALID_NODE_ID on failure
 *      (i.e. (ITS_USHORT)(-1)).
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_USHORT 
DSM_GetNodeId()
{
    DSM_CoreObject* coreObj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());

    if (!DSM_IsPreInitialized())
    {
        return DSM_INVALID_NODE_ID;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    return DSM_CORE_NODE_ID(coreObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve current process identifier (configuration specified).
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
 *      Current process identifier on success or DSM_INVALID_PROCESS_ID on 
 *      failure (i.e. (ITS_USHORT)(-1)).
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_USHORT
DSM_GetProcessId()
{
    DSM_CoreObject* coreObj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());

    if (!DSM_IsPreInitialized())
    {
        return DSM_INVALID_PROCESS_ID;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    return DSM_CORE_PROCESS_ID(coreObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve current node name.
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
 *      Current node name on success or "" on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI const char*
DSM_GetNodeName()
{
    DSM_CoreObject* coreObj;
    ITS_USHORT nodeId;

    ITS_C_REQUIRE(DSM_IsPreInitialized());

    if (!DSM_IsPreInitialized())
    {
        return "";
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    nodeId = DSM_CORE_NODE_ID(coreObj);

    return DSM_CORE_NODE_NAME_RESOURCES(coreObj)[nodeId].nodeName;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve current process name.
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
 *      Current process name on success or "" on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI const char*
DSM_GetProcessName()
{
    DSM_CoreObject* coreObj;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    ITS_USHORT maxNumProcesses;

    ITS_C_REQUIRE(DSM_IsPreInitialized());

    if (!DSM_IsPreInitialized())
    {
        return "";
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    nodeId          = DSM_CORE_NODE_ID(coreObj);
    processId       = DSM_CORE_PROCESS_ID(coreObj);
    maxNumProcesses = DSM_CORE_MAX_NUM_PROCESSES(coreObj);

    return DSM_CORE_PROCESS_NAME_RESOURCES(coreObj)[
                maxNumProcesses * nodeId + processId].processName;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Configure Fault Tolerance Group name. Default name is "FTGx" where x is
 *      the Fault Tolerance Group identifier (e.g. "FTG0", "FTG1"...).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *      ftGroupName - configured Fault Tolerance Group name.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_ConfigureFtGroupName(
    ITS_USHORT ftGroupId,
    const char* ftGroupName)
{
    DSM_CoreObject* coreObj;
    char* ftGroupNameDup;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    ftGroupNameDup = strdup(ftGroupName);
    if (ftGroupNameDup == NULL)
    {
        return ITS_ENOMEM;
    }

    if (DSM_CORE_FT_GROUP_NAME_RESOURCES(coreObj)
            [ftGroupId].ftGroupName != NULL)
    {
        free(DSM_CORE_FT_GROUP_NAME_RESOURCES(coreObj)
            [ftGroupId].ftGroupName);
    }

    DSM_CORE_FT_GROUP_NAME_RESOURCES(coreObj)
        [ftGroupId].ftGroupName = ftGroupNameDup;

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Configure node name. Default name is "Nx" where x is the node 
 *      identifier (e.g. "N0", "N1"...).
 *
 *  Input Parameters:
 *      nodeId - node identifier.
 *      nodeName - configured node name.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_ConfigureNodeName(
    ITS_USHORT nodeId,
    const char* nodeName)
{
    DSM_CoreObject* coreObj;
    char* nodeNameDup;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(nodeId < DSM_GetMaxNumNodes());

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (nodeId >= DSM_GetMaxNumNodes())
    {
        /* TODO: add trace. */
        return ITS_EINVNODE;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    nodeNameDup = strdup(nodeName);
    if (nodeNameDup == NULL)
    {
        return ITS_ENOMEM;
    }

    if (DSM_CORE_NODE_NAME_RESOURCES(coreObj)[nodeId].nodeName != NULL)
    {
        free(DSM_CORE_NODE_NAME_RESOURCES(coreObj)[nodeId].nodeName);
    }

    DSM_CORE_NODE_NAME_RESOURCES(coreObj)[nodeId].nodeName = nodeNameDup;

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Configure process name. Default name is "NxPy" where x is the node 
 *      identifier and y is the process identifier (e.g. "N0P0", "N1P2"...).
 *
 *  Input Parameters:
 *      nodeId - node identifier.
 *      processId - process identifier.
 *      processName - configured process name.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_ConfigureProcessName(
    ITS_USHORT nodeId,
    ITS_USHORT processId,
    const char* processName)
{
    DSM_CoreObject* coreObj;
    char* processNameDup;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(nodeId < DSM_GetMaxNumNodes());
    ITS_C_REQUIRE(processId < DSM_GetMaxNumProcesses());

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (nodeId >= DSM_GetMaxNumNodes())
    {
        /* TODO: add trace. */
        return ITS_EINVNODE;
    }

    if (processId >= DSM_GetMaxNumProcesses())
    {
        /* TODO: add trace. */
        return ITS_EINVPROCESS;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    processNameDup = strdup(processName);
    if (processNameDup == NULL)
    {
        return ITS_ENOMEM;
    }

    if (DSM_CORE_PROCESS_NAME_RESOURCES(coreObj)
            [DSM_CORE_MAX_NUM_PROCESSES(coreObj) * nodeId + processId].
                processName != NULL)
    {
        free(DSM_CORE_PROCESS_NAME_RESOURCES(coreObj)
                [DSM_CORE_MAX_NUM_PROCESSES(coreObj) * nodeId + processId].
                    processName);
    }

    DSM_CORE_PROCESS_NAME_RESOURCES(coreObj)
        [DSM_CORE_MAX_NUM_PROCESSES(coreObj) * nodeId + processId].
            processName = processNameDup;

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve Fault Tolerance Group name from Fault Tolerance Group
 *      identifier. 
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Fault Tolerance Group name on success or "" on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI const char*
DSM_GetFtGroupNameFromId(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());

    if (!DSM_IsPreInitialized())
    {
        return "";
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        return "";
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    return DSM_CORE_FT_GROUP_NAME_RESOURCES(coreObj)[ftGroupId].ftGroupName;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve node name from node identifier.
 *
 *  Input Parameters:
 *      nodeId - node identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Node name on success or "" on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI const char*
DSM_GetNodeNameFromId(
    ITS_USHORT nodeId)
{
    DSM_CoreObject* coreObj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(nodeId < DSM_GetMaxNumNodes());

    if (!DSM_IsPreInitialized())
    {
        return "";
    }

    if (nodeId >= DSM_GetMaxNumNodes())
    {
        return "";
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    return DSM_CORE_NODE_NAME_RESOURCES(coreObj)[nodeId].nodeName;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Retrieve process name from node identifier and process identifier.
 *
 *  Input Parameters:
 *      nodeId - node identifier.
 *      processId - process identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Process name on success or "" on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI const char*
DSM_GetProcessNameFromId(
    ITS_USHORT nodeId,
    ITS_USHORT processId)
{
    DSM_CoreObject* coreObj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(nodeId < DSM_GetMaxNumNodes());
    ITS_C_REQUIRE(processId < DSM_GetMaxNumProcesses());

    if (!DSM_IsPreInitialized())
    {
        return "";
    }

    if (nodeId >= DSM_GetMaxNumNodes())
    {
        return "";
    }

    if (processId >= DSM_GetMaxNumProcesses())
    {
        return "";
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    return DSM_CORE_PROCESS_NAME_RESOURCES(coreObj)
                [DSM_CORE_MAX_NUM_PROCESSES(coreObj) * nodeId + processId].
                    processName;
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Allocate a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM indentifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      size - size of row in octets.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      error - pointer to int to be initialized to ITS_SUCCESS on success or
 *          to an ITS error code on failure.
 *
 *  Return Value:
 *      Pointer to allocated row on success or NULL on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void*
DSM_Alloc(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (error == NULL)
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (key == NULL)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_ALLOC(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                size,
                error);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Allocate a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM indentifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      size - size of row in octets.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      error - pointer to int to be initialized to ITS_SUCCESS on success or
 *          to an ITS error code on failure.
 *
 *  Return Value:
 *      Pointer to allocated row on success or NULL on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void*
DSM_AllocLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (error == NULL)
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (key == NULL)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_ALLOC_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                size,
                error);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Find a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      error - pointer to int to be initialized to ITS_SUCCESS on success or
 *          to an ITS error code on failure.
 *
 *  Return Value:
 *      Pointer to found row on success or NULL on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void* 
DSM_Find(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (error == NULL)
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (key == NULL)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_FIND(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                error);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Find a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      error - pointer to int to be initialized to ITS_SUCCESS on success or
 *          to an ITS error code on failure.
 *
 *  Return Value:
 *      Pointer to found row on success or NULL on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void* 
DSM_FindLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (error == NULL)
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (key == NULL)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_FIND_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                error);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Free a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      object - row to free.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_Free(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (key == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_FREE(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Free a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      object - row to free.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_FreeLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (key == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_FREE_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Commit a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      object - row to commit.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_Commit(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (key == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_COMMIT(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Commit a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      object - row to commit.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_CommitLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (key == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_COMMIT_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
/*
    return DSM_CommitLocalImpl(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
*/
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Lock a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      object - row to lock.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_LockRow(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (key == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_LOCK_ROW(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Unlock a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      object - row to unlock.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_UnlockRow(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (key == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_UNLOCK_ROW(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Lock specified Fault Tolerance Group (i.e. DSM).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_LockDsm(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));
    ITS_C_REQUIRE(DSM_IsFtGroupJoined(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (!DSM_IsFtGroupJoined(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVJOINSTATE;
    }

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_LOCK_DSM(implClass)(
                coreObj, 
                ftGroupId);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Unlock specified Fault Tolerance Group (i.e. DSM).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_UnlockDsm(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));
    ITS_C_REQUIRE(DSM_IsFtGroupJoined(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (!DSM_IsFtGroupJoined(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVJOINSTATE;
    }

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_UNLOCK_DSM(implClass)(
                coreObj, 
                ftGroupId);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Lock specified table.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_LockTable(
    ITS_USHORT ftGroupId, 
    ITS_UINT tableId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_LOCK_TABLE(implClass)(
                coreObj, 
                ftGroupId,
                tableId);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Lock specified table.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int
DSM_LockTableLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_LOCK_TABLE_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId);
/*
    return DSM_LockTableLocalImpl(
                coreObj,
                ftGroupId,
                tableId);
*/
}



/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Unlock specified table.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_UnlockTable(
    ITS_USHORT ftGroupId, 
    ITS_UINT tableId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_UNLOCK_TABLE(implClass)(
                coreObj, 
                ftGroupId,
                tableId);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Unlock specified table.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int
DSM_UnlockTableLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_UNLOCK_TABLE_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId);
/*
    return DSM_UnlockTableLocalImpl(
                coreObj,
                ftGroupId,
                tableId);
*/
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Allocate a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key. No lock is hold on the row.
 *
 *      MUST be used only when specified table is locked or specified Fault
 *      Tolerance Group (i.e. DSM) is locked (see DSM_TableLock/Unlock and
 *      DSM_DsmLock/Unlock).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM indentifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      size - size of row in octets.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      error - pointer to int to be initialized to ITS_SUCCESS on success or
 *          to an ITS error code on failure.
 *
 *  Return Value:
 *      Pointer to allocated row on success or NULL on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void* 
DSM_AllocNoLock(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (error == NULL)
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (key == NULL)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_ALLOC_NO_LOCK(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                size,
                error);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Allocate a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key. No lock is hold on the row.
 *
 *      MUST be used only when specified table is locked or specified Fault
 *      Tolerance Group (i.e. DSM) is locked (see DSM_TableLock/Unlock and
 *      DSM_DsmLock/Unlock).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM indentifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      size - size of row in octets.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      error - pointer to int to be initialized to ITS_SUCCESS on success or
 *          to an ITS error code on failure.
 *
 *  Return Value:
 *      Pointer to allocated row on success or NULL on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void*
DSM_AllocNoLockLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key,
    ITS_UINT klen,
    ITS_UINT size,
    int* error)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (error == NULL)
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (key == NULL)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_ALLOC_NO_LOCK_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                size,
                error);
/*
    return DSM_AllocNoLockLocalImpl(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                size,
                error);
*/
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Find a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key. No lock is hold on the row.
 *
 *      MUST be used only when specified table is locked or specified Fault
 *      Tolerance Group (i.e. DSM) is locked (see DSM_TableLock/Unlock and
 *      DSM_DsmLock/Unlock).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      error - pointer to int to be initialized to ITS_SUCCESS on success or
 *          to an ITS error code on failure.
 *
 *  Return Value:
 *      Pointer to found row on success or NULL on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void* 
DSM_FindNoLock(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (error == NULL)
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (key == NULL)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_FIND_NO_LOCK(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                error);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Find a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key. No lock is hold on the row.
 *
 *      MUST be used only when specified table is locked or specified Fault
 *      Tolerance Group (i.e. DSM) is locked (see DSM_TableLock/Unlock and
 *      DSM_DsmLock/Unlock).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      error - pointer to int to be initialized to ITS_SUCCESS on success or
 *          to an ITS error code on failure.
 *
 *  Return Value:
 *      Pointer to found row on success or NULL on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void*
DSM_FindNoLockLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key,
    ITS_UINT klen,
    int* error)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (error == NULL)
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (key == NULL)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        *error = ITS_EINVALIDARGS;
        return NULL;
    }

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        *error = ITS_EINVALIDARGS;
        return NULL;
    }
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_FIND_NO_LOCK_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                error);
/*
    return DSM_FindNoLockLocalImpl(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                error);
*/
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Free a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key. No check that row is locked is 
 *      performed.
 *
 *      MUST be used only when specified table is locked or specified Fault
 *      Tolerance Group (i.e. DSM) is locked (see DSM_TableLock/Unlock and
 *      DSM_DsmLock/Unlock).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      object - row to free.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_FreeNoLock(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,           
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (key == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_FREE_NO_LOCK(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Free a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key. No check that row is locked is 
 *      performed.
 *
 *      MUST be used only when specified table is locked or specified Fault
 *      Tolerance Group (i.e. DSM) is locked (see DSM_TableLock/Unlock and
 *      DSM_DsmLock/Unlock).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      object - row to free.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_FreeNoLockLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,           
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (key == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_FREE_NO_LOCK_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
}
/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Commit a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key. No check that row is locked is 
 *      performed.
 *
 *      MUST be used only when specified table is locked or specified Fault
 *      Tolerance Group (i.e. DSM) is locked (see DSM_TableLock/Unlock and
 *      DSM_DsmLock/Unlock).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      object - row to commit.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_CommitNoLock(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (key == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_COMMIT_NO_LOCK(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Commit a row in specified Fault Tolerance Group (i.e. DSM) within
 *      specified table with specified key. No check that row is locked is 
 *      performed.
 *
 *      MUST be used only when specified table is locked or specified Fault
 *      Tolerance Group (i.e. DSM) is locked (see DSM_TableLock/Unlock and
 *      DSM_DsmLock/Unlock).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      key - key identifying row in table.
 *      klen - length of key.
 *      object - row to commit.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_CommitNoLockLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (key == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (klen == 0)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_COMMIT_NO_LOCK_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
/*
    return DSM_CommitNoLockLocalImpl(
                coreObj, 
                ftGroupId,
                tableId,
                key,
                klen,
                object);
*/
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Lock a row.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      object - row to lock.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_LockRowNoLock(
    ITS_USHORT ftGroupId,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_LOCK_ROW_NO_LOCK(implClass)(
                coreObj, 
                ftGroupId,
                object);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Unlock a row.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      object - row to lock.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_UnlockRowNoLock(
    ITS_USHORT ftGroupId,
    void* object)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (object == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_UNLOCK_ROW_NO_LOCK(implClass)(
                coreObj, 
                ftGroupId,
                object);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Iterate a table. Walks all the rows of the specified table calling for
 *      each row specified iterateEntryFn function with specified in and out
 *      arguments. Intended for general iteration purposes (high efficiency).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      in - general purpose input argument.
 *      out - general purpose output argument.
 *      iterateEntryFn - iterate entry function (called for each row).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_TableIterate(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    void* in, 
    void* out,
    DSM_IterateEntryProc iterateEntryFn)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (iterateEntryFn == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_TABLE_ITERATE(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                in,
                out,
                iterateEntryFn);
}

ITSDLLAPI int 
DSM_TableIterateLocal(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    void* in, 
    void* out,
    DSM_IterateEntryProc iterateEntryFn)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    if (iterateEntryFn == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    if (tableId >= DSM_INST_MAX_NUM_TABLES(instObj)) 
    {
        return ITS_EINVALIDARGS;
    }

    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_TABLE_ITERATE_LOCAL(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                in,
                out,
                iterateEntryFn);
}
/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Dump a table. Walks all the rows of the specified table calling for
 *      each row specified dumpEntryFn function. Intended for row dumping
 *      (medium efficiency due to realloc calls).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier (i.e. DSM identifier).
 *      tableId - table identifier.
 *      pStrDump - pointer to a character string. Allocated by DSM_TableDump
 *          and therefore must be deallocated by user after usage.
 *      dumpEntryFn - dump entry function (called for each row).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_TableDump(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    char** pStrDump,                            
    DSM_DumpEntryProc dumpEntryFn)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));
    ITS_C_REQUIRE(DSM_IsFtGroupJoined(ftGroupId));
    ITS_C_REQUIRE(tableId < DSM_GetMaxNumTables(ftGroupId));
    ITS_C_REQUIRE(pStrDump != NULL);
    ITS_C_REQUIRE(dumpEntryFn != NULL);

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (!DSM_IsFtGroupJoined(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVJOINSTATE;
    }

    if (tableId >= DSM_GetMaxNumTables(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVTABLE;
    }

    if (pStrDump == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }

    if (dumpEntryFn == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_TABLE_DUMP(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                pStrDump,
                dumpEntryFn);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Table size (i.e. number of rows).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *      tableId - table identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      size - pointer to ITS_UINT to be initialized to table size (i.e. number
 *          of rows) on success.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_TableGetSize(
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    ITS_UINT* size)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));
    ITS_C_REQUIRE(DSM_IsFtGroupJoined(ftGroupId));
    ITS_C_REQUIRE(tableId < DSM_GetMaxNumTables(ftGroupId));
    ITS_C_REQUIRE(size != NULL);

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (!DSM_IsFtGroupJoined(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVJOINSTATE;
    }

    if (tableId >= DSM_GetMaxNumTables(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVTABLE;
    }

    if (size == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVALIDARGS;
    }
    
    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_TABLE_GET_SIZE(implClass)(
                coreObj, 
                ftGroupId,
                tableId,
                size);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Retrieve membership change callbacks manager.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Membership change callbacks manager on success or NULL on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI CALLBACK_Manager* 
DSM_GetMembershipChangeCallbacks(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return NULL;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    return DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(instObj);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Pre-add (before a call to DSM_Initialize) a membership change
 *      callback.
 *      - Callbacks that are pre-added are added by DSM_Initialize (according
 *        to the specified Fault Tolerance Group).
 *      - Typically to be used in correlation with Engine to allow adding 
 *        callbacks as soon as a Fault Tolerance Group is initialized.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *      cbFunction - Callback function.
 *      userData - Callback user data.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_PreAddMembershipChangeCallback(
    ITS_USHORT ftGroupId,
    ITS_CALLBACK cbFunction,
    ITS_POINTER userData)
{
    PreAddedMembershipChangeCb** list = 
        &preAddedMembershipChangeCbList;
    PreAddedMembershipChangeCb* element;

    element = 
        (PreAddedMembershipChangeCb*)
            calloc(
                1, 
                sizeof(PreAddedMembershipChangeCb));
    if (element == NULL)
    {
        return ITS_ENOMEM;
    }

    element->ftGroupId = ftGroupId;
    element->cbFunction = cbFunction;
    element->userData = userData;

    while (*list != NULL)
    {
        list = &(*list)->next;
    }

    *list = element;

    return ITS_SUCCESS;
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Retrieve critical error notification callbacks callbacks manager.
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
 *      Critical error notification callbacks manager on success or NULL on 
 *      failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI CALLBACK_Manager* 
DSM_GetCriticalErrorNotificationCallbacks()
{
    DSM_CoreObject* coreObj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return NULL;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);

    return DSM_CORE_CRITICAL_ERROR_NOTIFICATION_CALLBACKS(coreObj);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Pre-add (before a call to DSM_PreInitialize) a critical error 
 *      notification callback.
 *      - Callbacks that are pre-added are added by DSM_PreInitialize.
 *      - Typically to be used in correlation with Engine to allow adding
 *        callbacks as soon as DSM subsystem is pre-initialized.
 *
 *  Input Parameters:
 *      cbFunction - Callback function.
 *      userData - Callback user data.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_PreAddCriticalErrorNotificationCallback(
    ITS_CALLBACK cbFunction,
    ITS_POINTER userData)
{
    PreAddedCriticalErrorNotificationCb** list = 
        &preAddedCriticalErrorNotificationCbList;
    PreAddedCriticalErrorNotificationCb* element;

    element = 
        (PreAddedCriticalErrorNotificationCb*)
            calloc(
                1, 
                sizeof(PreAddedCriticalErrorNotificationCb));
    if (element == NULL)
    {
        return ITS_ENOMEM;
    }

    element->cbFunction = cbFunction;
    element->userData = userData;

    while (*list != NULL)
    {
        list = &(*list)->next;
    }

    *list = element;

    return ITS_SUCCESS;
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Multicast an event to all members of a Fault Tolerance Group (self is
 *      included).
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *      event - event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_MulticastEventToFtGroupMembers(
    ITS_USHORT ftGroupId,
    const ITS_EVENT* event)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));
    ITS_C_REQUIRE(DSM_IsFtGroupJoined(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return ITS_EINVFTGROUP;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    if (!DSM_IsFtGroupJoined(ftGroupId))
    {
        /* TODO: add trace. */
        return ITS_EINVJOINSTATE;
    }

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_MULTICAST_EVENT_TO_FT_GROUP_MEMBERS(implClass)(
                coreObj,
                ftGroupId, 
                event);
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Multicast a stack event to all members of a Fault Tolerance Group.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *      event - event.
 *      source - The event source set by GCS after processing
 *      dest   - The destination thread after GCS processing
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_MulticastStackEventToFtGroupMembers(
    ITS_USHORT ftGroupId,
    ITS_EVENT event,
    ITS_USHORT source, 
    ITS_USHORT destination)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_ImplClass   implClass;

    coreObj     = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    if (ftGroupId >= DSM_CORE_MAX_NUM_FT_GROUPS(coreObj))
    {
        return ITS_EINVALIDARGS;
    }
    instObj     = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    implClass   = DSM_INST_IMPL_CLASS(instObj);

    return DSM_IMPL_CLASS_MULTICAST_STACK_EVENT_TO_FT_GROUP_MEMBERS(implClass)(
                coreObj,
                ftGroupId, 
                event,
                source,
                destination);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Retrieve event from Fault Tolerance Group member callbacks manager.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Event from Fault Tolerance Group callbacks manager on success or NULL
 *      on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI CALLBACK_Manager* 
DSM_GetEventFromFtGroupMemberCallbacks(
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(DSM_IsPreInitialized());
    ITS_C_REQUIRE(ftGroupId < DSM_GetMaxNumFtGroups());
    ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));

    if (!DSM_IsPreInitialized())
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (ftGroupId >= DSM_GetMaxNumFtGroups())
    {
        /* TODO: add trace. */
        return NULL;
    }

    if (!DSM_IsInitialized(ftGroupId))
    {
        /* TODO: add trace. */
        return NULL;
    }

    coreObj = (DSM_CoreObject*)LOCKABLE_GetShared(itsDSM_CoreClass);
    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    
    return DSM_INST_EVENT_FROM_FT_GROUP_MEMBER_CALLBACKS(instObj);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Pre-add (before a call to DSM_Initialize) an event from Fault 
 *      Tolerance Group Member callback.
 *      - Callbacks that are pre-added are added by DSM_Initialize (according
 *        to the specified Fault Tolerance Group).
 *      - Typically to be used in correlation with Engine to allow adding 
 *        callbacks as soon as a Fault Tolerance Group is initialized.
 *
 *  Input Parameters:
 *      ftGroupId - Fault Tolerance Group identifier.
 *      cbFunction - Callback function.
 *      userData - Callback user data.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
DSM_PreAddEventFromFtGroupMemberCallback(
    ITS_USHORT ftGroupId,
    ITS_CALLBACK cbFunction,
    ITS_POINTER userData)
{
    PreAddedEventFromFtGroupMemberCb** list = 
        &preAddedEventFromFtGroupMemberCbList;
    PreAddedEventFromFtGroupMemberCb* element;

    element = 
        (PreAddedEventFromFtGroupMemberCb*)
            calloc(
                1, 
                sizeof(PreAddedEventFromFtGroupMemberCb));
    if (element == NULL)
    {
        return ITS_ENOMEM;
    }

    element->ftGroupId = ftGroupId;
    element->cbFunction = cbFunction;
    element->userData = userData;

    while (*list != NULL)
    {
        list = &(*list)->next;
    }

    *list = element;

    return ITS_SUCCESS;
}
