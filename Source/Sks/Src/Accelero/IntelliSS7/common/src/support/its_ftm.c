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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:28  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:58:57  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:38  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:51:58  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 4.2  2002/05/07 19:48:08  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 4.1  2002/04/11 20:38:57  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/


#include <its_ftm.h>
#include <its_assertion.h>
#include <its_trace.h>
#include <its_app.h>


#ident "$Id: its_ftm.c,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $"


/*
 * Forward declarations (FTM redirect callbacks).
 */

static void FtmRedirectMembershipChangeCallback(
                         ITS_POINTER object,
                         ITS_POINTER userData,
                         ITS_POINTER callData);

static void FtmRedirectEventFromFtGroupMemberCallback(
                         ITS_POINTER object,
                         ITS_POINTER userData,
                         ITS_POINTER callData);


/******************************************************************************
 ******************************************************************************
 **
 ** FTM Core class.
 **
 */

/*
 * CoreClassInitialize.
 */
static int
CoreClassInitialize(
    ITS_Class objClass)
{
    /* Nothing to do. */
    return ITS_SUCCESS;
}

/*
 * CoreClassTerminate.
 */
static void
CoreClassTerminate(
    ITS_Class objClass)
{
    /* Nothing to do. */
    return;
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
    void* ftmContext;
    int ret;

    ITS_C_REQUIRE(!FTM_IsInitialized());

    ftmContext = va_arg(args, void*);

    if (FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    /* Set LOCKABLE sharedInstance. */
    LOCKABLE_SHARED_INSTANCE(itsFTM_CoreClass) = obj;

    FTM_CORE_FTM_CONTEXT(obj) = ftmContext;

    FTM_CORE_CONFIG_DB(obj) = RESFILE_CreateResourceManager(configFileName);
    if (FTM_CORE_CONFIG_DB(obj) == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    ret = SEMA_CreateSemaphore(&FTM_CORE_TERMINATION_SEMA(obj), 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "CoreCreateInstance: SEMA_CreateSemaphore failed: %d\n",
            ret));
        RESFILE_DeleteResourceManager(FTM_CORE_CONFIG_DB(obj));
        return ret;
    }

    FTM_CORE_MEMBERSHIP_CHANGE_ALL_FT_GROUPS_CALLBACKS(obj) = 
        CALLBACK_InitManager();
    if (FTM_CORE_MEMBERSHIP_CHANGE_ALL_FT_GROUPS_CALLBACKS(obj) == NULL)
    {
        SEMA_DeleteSemaphore(&FTM_CORE_TERMINATION_SEMA(obj));
        RESFILE_DeleteResourceManager(FTM_CORE_CONFIG_DB(obj));
        return ITS_ENOMEM;
    }

    FTM_CORE_EVENT_FROM_ALL_FT_GROUP_MEMBERS_CALLBACKS(obj) =
        CALLBACK_InitManager();
    if (FTM_CORE_EVENT_FROM_ALL_FT_GROUP_MEMBERS_CALLBACKS(obj) == NULL)
    {
        SEMA_DeleteSemaphore(&FTM_CORE_TERMINATION_SEMA(obj));
        RESFILE_DeleteResourceManager(FTM_CORE_CONFIG_DB(obj));
        CALLBACK_DestroyManager(
            FTM_CORE_MEMBERSHIP_CHANGE_ALL_FT_GROUPS_CALLBACKS(obj));
        return ITS_ENOMEM;
    }

    FTM_CORE_PRE_EXECUTE_LOGIC_PROC(obj)    = NULL;
    FTM_CORE_LOOP_EXECUTE_LOGIC_PROC(obj)   = NULL;
    FTM_CORE_POST_EXECUTE_LOGIC_PROC(obj)   = NULL;

    return ITS_SUCCESS;
}


/*
 * CoreDestroyInstance.
 */
static void
CoreDestroyInstance(
    ITS_Object obj)
{
    FTM_CORE_PRE_EXECUTE_LOGIC_PROC(obj)    = NULL;
    FTM_CORE_LOOP_EXECUTE_LOGIC_PROC(obj)   = NULL;
    FTM_CORE_POST_EXECUTE_LOGIC_PROC(obj)   = NULL;

    if (FTM_CORE_EVENT_FROM_ALL_FT_GROUP_MEMBERS_CALLBACKS(obj) != NULL)
    {
        CALLBACK_DestroyManager(
            FTM_CORE_EVENT_FROM_ALL_FT_GROUP_MEMBERS_CALLBACKS(obj));
        FTM_CORE_EVENT_FROM_ALL_FT_GROUP_MEMBERS_CALLBACKS(obj) = NULL;
    }

    if (FTM_CORE_MEMBERSHIP_CHANGE_ALL_FT_GROUPS_CALLBACKS(obj) != NULL)
    {
        CALLBACK_DestroyManager(
            FTM_CORE_MEMBERSHIP_CHANGE_ALL_FT_GROUPS_CALLBACKS(obj));
        FTM_CORE_MEMBERSHIP_CHANGE_ALL_FT_GROUPS_CALLBACKS(obj) = NULL;
    }

    SEMA_DeleteSemaphore(&FTM_CORE_TERMINATION_SEMA(obj));

    if (FTM_CORE_CONFIG_DB(obj) != NULL)
    {
        RESFILE_DeleteResourceManager(FTM_CORE_CONFIG_DB(obj));
        FTM_CORE_CONFIG_DB(obj) = NULL;
    }

    /* Reset LOCKABLE sharedInstance. */
    LOCKABLE_SHARED_INSTANCE(itsFTM_CoreClass) = NULL;
}

ITSDLLAPI FTM_CoreClassRec itsFTM_CoreClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsLOCKABLE_ClassRec,   /* LOCKABLE is superclass   */
        sizeof(FTM_CoreObject),             /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        FTM_CORE_CLASS_NAME,                /* class name               */
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
    /* ftm part */
    {
        NULL,
        NULL
    }
};

ITSDLLAPI ITS_Class itsFTM_CoreClass = (ITS_Class)&itsFTM_CoreClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** FTM Init (initialization) class.
 **
 */

/*
 * InitClassInitialize.
 */
static int
InitClassInitialize(
    ITS_Class objClass)
{
    const char* configFileName = APPL_GetConfigFileName();
    RESFILE_Manager* configDb;
    char value[FTM_MAX_CONFIG_VALUE_SIZE];
    ITS_BOOLEAN ftmInitExplicit;
    int ret;

    ITS_C_REQUIRE(!FTM_IsInitialized());

    configDb = RESFILE_CreateResourceManager(configFileName);

    if (configDb)
    {
        /* Retrieve ftmInitExplicit (if present). */
        if (RESFILE_GetKeyValueOf(
                            configDb,
                            FTM_FAULT_TOLERANCE_STRING,
                            FTM_INIT_EXPLICIT_STRING,
                            value,
                            FTM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            ftmInitExplicit = (RESFILE_ParseNum(value) != 0);
        }
        else
        {
            /* Default value. */
            ftmInitExplicit = ITS_FALSE;
        }
    }
    else
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

    if (!ftmInitExplicit)
    {
        FTM_CoreObject* coreObj;
        ITS_USHORT maxNumFtGroups;
        ITS_USHORT i;

        ret = FTM_InitializeFromConfig(NULL);
        if (ret != ITS_SUCCESS)
        {
            /* TODO: add trace. */
            return ret;
        }

        ITS_C_ASSERT(FTM_IsInitialized());

        /* 
         * Add relevant redirect callbacks for initialized FtGroups. 
         */

        coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

        maxNumFtGroups = DSM_GetMaxNumFtGroups();

        for (i = 0; i < maxNumFtGroups; i++)
        {
            if (DSM_IsInitialized(i))
            {
                ret = CALLBACK_AddCallback(
                        DSM_GetMembershipChangeCallbacks(i),
                        FtmRedirectMembershipChangeCallback,
                        (ITS_POINTER)coreObj);
                if (ret != ITS_SUCCESS)
                {
                    /* TODO: add trace. */
                }

                ret = CALLBACK_AddCallback(
                        DSM_GetEventFromFtGroupMemberCallbacks(i),
                        FtmRedirectEventFromFtGroupMemberCallback,
                        (ITS_POINTER)coreObj);
                if (ret != ITS_SUCCESS)
                {
                    /* TODO: add trace. */
                }
            }
        }
    }

    RESFILE_DeleteResourceManager(configDb);

    return ITS_SUCCESS;
}

/*
 * InitClassTerminate.
 */
static void
InitClassTerminate(
    ITS_Class objClass)
{
    const char* configFileName = APPL_GetConfigFileName();
    RESFILE_Manager* configDb;
    char value[FTM_MAX_CONFIG_VALUE_SIZE];
    ITS_BOOLEAN ftmInitExplicit;

    ITS_C_REQUIRE(FTM_IsInitialized());

    configDb = RESFILE_CreateResourceManager(configFileName);

    if (configDb)
    {
        /* Retrieve ftmInitExplicit (if present). */
        if (RESFILE_GetKeyValueOf(
                            configDb,
                            FTM_FAULT_TOLERANCE_STRING,
                            FTM_INIT_EXPLICIT_STRING,
                            value,
                            FTM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            ftmInitExplicit = (RESFILE_ParseNum(value) != 0);
        }
        else
        {
            /* Default value. */
            ftmInitExplicit = ITS_FALSE;
        }
    }
    else
    {
        /* TODO: add trace. */
        return;
    }

    if (!ftmInitExplicit)
    {
        FTM_Terminate();
    }

    RESFILE_DeleteResourceManager(configDb);

    return;
}

ITSDLLAPI FTM_InitClassRec itsFTM_InitClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,                  /* CORE is superclass       */
        0,                                  /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        FTM_INIT_CLASS_NAME,                /* class name               */
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

ITSDLLAPI ITS_Class itsFTM_InitClass = (ITS_Class)&itsFTM_InitClassRec;


/*
 * FTM redirect callback implementations.
 */

static void 
FtmRedirectMembershipChangeCallback(
                         ITS_POINTER object,
                         ITS_POINTER userData,
                         ITS_POINTER callData)
{
    FTM_MembershipChangeAllFtGroupsCbData membershipChangeAllFtGroupsCbData;
    DSM_MembershipChangeCbData* membershipChangeCbData;
    CALLBACK_Manager* callbackManager;
    FTM_CoreObject* coreObj;
    int ret;

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);
    if (coreObj == NULL)
    {
        /* TODO: add trace. */
        return;
    }

    callbackManager = 
        FTM_CORE_MEMBERSHIP_CHANGE_ALL_FT_GROUPS_CALLBACKS(coreObj);
    if (callbackManager == NULL)
    {
        /* TODO: add trace. */
        return;
    }

    membershipChangeCbData = (DSM_MembershipChangeCbData*)callData;
    if (membershipChangeCbData == NULL)
    {
        /* TODO: add trace. */
        return;
    }

    membershipChangeAllFtGroupsCbData.ftGroupId =
        membershipChangeCbData->ftGroupId;
    membershipChangeAllFtGroupsCbData.membershipChangeType =
        membershipChangeCbData->membershipChangeType;
    membershipChangeAllFtGroupsCbData.memberNodeId =
        membershipChangeCbData->memberNodeId;
    membershipChangeAllFtGroupsCbData.memberProcessId =
        membershipChangeCbData->memberProcessId;
    membershipChangeAllFtGroupsCbData.numFtGroupMembers =
        membershipChangeCbData->numFtGroupMembers;
    membershipChangeAllFtGroupsCbData.ftGroupMembers =
        membershipChangeCbData->ftGroupMembers;

    ret = CALLBACK_CallCallbackList(
            callbackManager,
            (ITS_POINTER)coreObj,
            (ITS_POINTER)&membershipChangeAllFtGroupsCbData);
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return;
    }
}

static void 
FtmRedirectEventFromFtGroupMemberCallback(
                         ITS_POINTER object,
                         ITS_POINTER userData,
                         ITS_POINTER callData)
{
    FTM_EventFromAllFtGroupMembersCbData eventFromAllFtGroupMembersCbData;
    DSM_EventFromFtGroupMemberCbData* eventFromFtGroupMemberCbData;
    CALLBACK_Manager* callbackManager;
    FTM_CoreObject* coreObj;
    int ret;

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);
    if (coreObj == NULL)
    {
        /* TODO: add trace. */
        return;
    }

    callbackManager = 
        FTM_CORE_EVENT_FROM_ALL_FT_GROUP_MEMBERS_CALLBACKS(coreObj);
    if (callbackManager == NULL)
    {
        /* TODO: add trace. */
       return;
    }

    eventFromFtGroupMemberCbData = (DSM_EventFromFtGroupMemberCbData*)callData;
    if (eventFromFtGroupMemberCbData == NULL)
    {
        /* TODO: add trace. */
        return;
    }

    eventFromAllFtGroupMembersCbData.ftGroupId =
        eventFromFtGroupMemberCbData->ftGroupId;
    eventFromAllFtGroupMembersCbData.event =
        eventFromFtGroupMemberCbData->event;

    ret = CALLBACK_CallCallbackList(
            callbackManager,
            (ITS_POINTER)coreObj,
            (ITS_POINTER)&eventFromAllFtGroupMembersCbData);
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return;
    }
}

/******************************************************************************
 ******************************************************************************
 **
 ** FTM API functions.
 **
 */

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Initialize FTM subsystem from Resource Manager configuration.
 *      - Called automatically during Engine initialization unless explicit
 *        initialization/termination is specified (through 'ftmInitExplicit').
 *      - Must be called only once per process.
 *
 *  Input Parameters:
 *      ftmContext - FTM context if any (can be NULL).
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
FTM_InitializeFromConfig(
    void* ftmContext)
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(!FTM_IsInitialized());

    if (FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    coreObj = (FTM_CoreObject*)ITS_ConstructObject(
                                            itsFTM_CoreClass,
                                            ftmContext);
    if (coreObj == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINITFAIL;
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Initialize FTM subsystem with specified configuration.
 *      - Variable argument list is reserved for future extensions.
 *      - Must be called only once per process.
 *      - Last (mandatory) variable argument must be NULL (used as a 
 *        terminator).
 *      - All variable arguments must be of type character string (char*).
 *
 *  Input Parameters:
 *      ftmContext - FTM context if any (can be NULL).
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
FTM_Initialize(
    void* ftmContext,
    ...)
{
    va_list alist;
    const char* str;
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(!FTM_IsInitialized());

    if (FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    /*
     * Retrieve and process variable arguments.
     */ 

    va_start(alist, ftmContext);

    while ((str = va_arg(alist, const char*)) != NULL)
    {
        /* TODO: add processing for each variable argument. They are
         * (key, value) pairs to be added to the RM DB. Warnings if 
         * consistency conflicts.
         */
    }

    va_end(alist);

    coreObj = (FTM_CoreObject*)ITS_ConstructObject(
                                            itsFTM_CoreClass,
                                            ftmContext);
    if (coreObj == NULL)
    {
        /* TODO: add trace. */
        return ITS_EINITFAIL;
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Terminate FTM subsystem.
 *      - Called automatically during Engine termination unless explicit
 *        initialization/termination is specified (through 'ftmInitExplicit').
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
FTM_Terminate()
{
    ITS_Object obj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return;
    }

    obj = LOCKABLE_GetShared(itsFTM_CoreClass);

    ITS_DestructObject(obj);

    return;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Is FTM initialized?
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
 *      ITS_TRUE if FTM is initialized and ITS_FALSE if it is not.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
FTM_IsInitialized()
{
    return LOCKABLE_GetShared(itsFTM_CoreClass) != NULL;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Set FTM context.
 *
 *  Input Parameters:
 *      ftmContext - FTM context if any (can be NULL).
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
FTM_SetContext(void* ftmContext)
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    FTM_CORE_FTM_CONTEXT(coreObj) = ftmContext;

    return; 
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Get FTM context if any (can be NULL).
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
 *      FTM context.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void* 
FTM_GetContext()
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return NULL;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    return FTM_CORE_FTM_CONTEXT(coreObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Set pre-execute logic procedure.
 *
 *  Input Parameters:
 *      proc - pre-execute logic procedure.
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
 *      'FTM_PreExecuteLogicProc' specified procedure is called by IntelliSS7 
 *      Engine during Engine initialization (if Engine is used) before loop 
 *      execute logic procedure is called repetitively.
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void 
FTM_SetPreExecuteLogic(
    FTM_PreExecuteLogicProc proc)
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    FTM_CORE_PRE_EXECUTE_LOGIC_PROC(coreObj) = proc;

    return;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Set loop-execute logic procedure.
 *
 *  Input Parameters:
 *      proc - loop-execute logic procedure.
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
 *      'FTM_LoopExecuteLogicProc' specified procedure is called repetitively
 *      by IntelliSS7 Engine (if Engine is used).
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void 
FTM_SetLoopExecuteLogic(
    FTM_LoopExecuteLogicProc proc)
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    FTM_CORE_LOOP_EXECUTE_LOGIC_PROC(coreObj) = proc;

    return;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Set post-execute logic procedure.
 *
 *  Input Parameters:
 *      proc - post-execute logic procedure.
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
 *      'FTM_PostExecuteLogicProc' specified procedure is called by IntelliSS7
 *      Engine during Engine termination (if Engine is used) after loop execute
 *      logic procedure is called repetitively.
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI void 
FTM_SetPostExecuteLogic(
    FTM_PostExecuteLogicProc proc)
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    FTM_CORE_POST_EXECUTE_LOGIC_PROC(coreObj) = proc;

    return;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Get pre-execute logic procedure if any (can be NULL).
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
 *      Pre-execute logic procedure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI FTM_PreExecuteLogicProc
FTM_GetPreExecuteLogic()
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return NULL;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    return FTM_CORE_PRE_EXECUTE_LOGIC_PROC(coreObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Get loop-execute logic procedure if any (can be NULL).
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
 *      Loop-execute logic procedure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI FTM_LoopExecuteLogicProc 
FTM_GetLoopExecuteLogic()
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return NULL;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    return FTM_CORE_LOOP_EXECUTE_LOGIC_PROC(coreObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Get post-execute logic procedure if any (can be NULL).
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
 *      Post-execute logic procedure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI FTM_PostExecuteLogicProc 
FTM_GetPostExecuteLogic()
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return NULL;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    return FTM_CORE_POST_EXECUTE_LOGIC_PROC(coreObj);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Signal FTM termination.
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
 *      'FTM_SignalTermination' is called by IntelliSS7 Engine during Engine
 *      termination (if Engine is used).
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int
FTM_SignalTermination()
{
    FTM_CoreObject* coreObj;
    int ret;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    ret = SEMA_PostSemaphore(&FTM_CORE_TERMINATION_SEMA(coreObj));
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return ret;
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Wait for FTM termination (blocking call until 'FTM_SignalTermination' 
 *      is called).
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
FTM_WaitForTermination()
{
    FTM_CoreObject* coreObj;
    int ret;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    ret = SEMA_WaitSemaphore(&FTM_CORE_TERMINATION_SEMA(coreObj));
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return ret;
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Wait for FTM termination (blocking call until 'FTM_SignalTermination' 
 *      is called or timeout).
 *
 *  Input Parameters:
 *      millsecs - timeout in milliseconds.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS or ITS_ETIMEOUT on success or an ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI int 
FTM_WaitForTerminationWithTimeout(
    ITS_UINT millisecs)
{
    FTM_CoreObject* coreObj;
    int ret;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return ITS_EINVINITSTATE;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    ret = SEMA_WaitSemaphoreWithTimeOut(
                    &FTM_CORE_TERMINATION_SEMA(coreObj),
                    millisecs);
    if (ret != ITS_SUCCESS && ret != ITS_ETIMEOUT)
    {
        /* TODO: add trace. */
        return ret;
    }
    else if (ret == ITS_ETIMEOUT)
    {
        /* TODO: add trace. */
        return ret;
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Retrieve all FtGroups membership changes callbacks manager.
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
 *      All FtGroups membership changes callbacks manager on success or NULL
 *      on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI CALLBACK_Manager* 
FTM_GetMembershipChangeAllFtGroupsCallbacks()
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return NULL;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    return FTM_CORE_MEMBERSHIP_CHANGE_ALL_FT_GROUPS_CALLBACKS(coreObj);
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Multicast an event to all members of all Fault Tolerance Group (self
 *      is included).
 *
 *  Input Parameters:
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
FTM_MulticastEventToAllFtGroupMembers(
    const ITS_EVENT* event)
{
    ITS_BOOLEAN not_implemented = ITS_FALSE;
    ITS_C_ASSERT(not_implemented);
    return ITS_SUCCESS;
}

/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Retrieve event from all FtGroup members callbacks manager.
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
 *      Event from all FtGroup members callbacks manager on success or NULL
 *      on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
ITSDLLAPI CALLBACK_Manager* 
FTM_GetEventFromAllFtGroupMembersCallbacks()
{
    FTM_CoreObject* coreObj;

    ITS_C_REQUIRE(FTM_IsInitialized());

    if (!FTM_IsInitialized())
    {
        /* TODO: add trace. */
        return NULL;
    }

    coreObj = (FTM_CoreObject*)LOCKABLE_GetShared(itsFTM_CoreClass);

    return FTM_CORE_EVENT_FROM_ALL_FT_GROUP_MEMBERS_CALLBACKS(coreObj);
}



