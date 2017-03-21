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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.46.1  2004/12/16 03:26:17  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.2.42.1  2004/10/25 20:39:57  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.2  2002/09/19 19:35:16  mmiers
 * LOG: Add redundant stack prototypes
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/05/08 20:23:56  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 1.2  2002/05/07 19:48:35  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 1.1  2002/04/11 20:38:02  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/

#if !defined(_ITS_FTM_H_)
#define _ITS_FTM_H_

#include <its.h>
#include <its_dsm.h>
#include <its_semaphore.h>

#ident "$Id: its_ftm.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif


/******************************************************************************
 ******************************************************************************
 **
 ** Configuration strings for Resource Manager database.
 **
 */

/*
 * Configuration strings for general 'FtmFaultTolerance' section.
 */

/* Section name. */
#define FTM_FAULT_TOLERANCE_STRING                  "FtmFaultTolerance"


/* Optional, by default FTM initialization is implicit. */
#define FTM_INIT_EXPLICIT_STRING                    "ftmInitExplicit"


/*
 * FTM maximum configuration sizes.
 */ 

#define FTM_MAX_CONFIG_VALUE_SIZE           (128)
#define FTM_MAX_CONFIG_KEY_SIZE             (128)
#define FTM_MAX_CONFIG_SECTION_NAME_SIZE    (128)


/*.interface:FTM_
 ******************************************************************************
 *
 *  Interface:
 *      FTM_*
 *
 *  Purpose:
 *      Fault Tolerance Manager API.
 *
 *  Usage:
 *      See individual function usages and associated documentation.
 *
 *****************************************************************************/

/*
 * Public data structures.
 */

typedef DSM_FtGroupMember FTM_FtGroupMember;

/******************************************************************************
 ******************************************************************************
 **
 ** Initialization/Termination.
 **
 */

/*****************************************************************************
 * Important note: IntelliSS7 Engine (if used) calls automatically all FTM   *
 * initialization and termination functions.                                 *
 *****************************************************************************/


/*
 * Initialize FTM subsystem from Resource Manager configuration.
 * - Called automatically during Engine initialization unless explicit
 *   initialization/termination is specified (through 'ftmInitExplicit').
 * - Must be called only once per process.
 */
ITSDLLAPI int FTM_InitializeFromConfig(void* ftmContext);

/*
 * Initialize FTM subsystem with specified configuration.
 * - Variable argument list is reserved for future extensions.
 * - Must be called only once per process.
 * - Last (mandatory) variable argument must be NULL (used as a terminator).
 * - All variable arguments must be of type character string (char*).
 */
ITSDLLAPI int FTM_Initialize(void* ftmContext, ...);

/*
 * Terminate FTM subsystem.
 * - Called automatically during Engine termination unless explicit
 *   initialization/termination is specified (through 'ftmInitExplicit').
 * - Must be called only once per process.
 */
ITSDLLAPI void FTM_Terminate();

/******************************************************************************
 ******************************************************************************
 **
 ** Initialization status information.
 **
 */

/*
 * Is FTM subsystem initialized?
 */
ITSDLLAPI ITS_BOOLEAN FTM_IsInitialized();


/******************************************************************************
 ******************************************************************************
 **
 ** FTM Context get/set.
 **
 */

/* Set FTM Context. */
ITSDLLAPI void FTM_SetContext(void* ftmContext);

/* Get FTM Context. NULL is returned if FTM Context has not been set. */
ITSDLLAPI void* FTM_GetContext();


/******************************************************************************
 ******************************************************************************
 **
 ** FTM execution logic related.
 **
 */

/*****************************************************************************
 * Important note: if IntelliSS7 Engine is used then execution logic related *
 * procedure names are specified in the Engine XML configuration file and    *
 * the associated procedures are explicitly dynamically linked during the    *
 * Engine initialization phase.                                              *
 *****************************************************************************/

/*
 * Pre-execute logic procedure signature definition.
 */
typedef void (*FTM_PreExecuteLogicProc)(void);

/* 
 * 'FTM_PreExecuteLogicProc' specified procedure is called by IntelliSS7 Engine
 * during Engine initialization (if Engine is used) before loop execute logic
 * procedure is called repetitively.
 */
ITSDLLAPI void FTM_SetPreExecuteLogic(FTM_PreExecuteLogicProc proc);


/*
 * Loop-execute logic procedure signature definition.
 */
typedef void (*FTM_LoopExecuteLogicProc)(void);

/* 
 * 'FTM_LoopExecuteLogicProc' specified procedure is called repetitively by
 * IntelliSS7 Engine (if Engine is used).
 */
ITSDLLAPI void FTM_SetLoopExecuteLogic(FTM_LoopExecuteLogicProc proc);


/*
 * Post-execute logic procedure signature definition.
 */
typedef void (*FTM_PostExecuteLogicProc)(void);

/*
 * 'FTM_PostExecuteLogicProc' specified procedure is called by IntelliSS7
 * Engine during Engine termination (if Engine is used) after loop execute 
 * logic procedure is called repetitively.
 */
ITSDLLAPI void FTM_SetPostExecuteLogic(FTM_PostExecuteLogicProc proc);


/*
 * Execute logic procedures retrieval.
 */

ITSDLLAPI FTM_PreExecuteLogicProc FTM_GetPreExecuteLogic();

ITSDLLAPI FTM_LoopExecuteLogicProc FTM_GetLoopExecuteLogic();

ITSDLLAPI FTM_PostExecuteLogicProc FTM_GetPostExecuteLogic();


/*
 * 'FTM_SignalTermination' is called by IntelliSS7 Engine during Engine
 * termination (if Engine is used).
 */
ITSDLLAPI int FTM_SignalTermination();

/*
 * Wait for termination functions to be called by loop execute logic procedure
 * (to avoid polling).
 */

/* Blocking call until 'FTM_SignalTermination' is called. */
ITSDLLAPI int FTM_WaitForTermination();

/* Blocking call until 'FTM_SignalTermination' is called or timeout. */
ITSDLLAPI int FTM_WaitForTerminationWithTimeout(ITS_UINT millisecs);


/******************************************************************************
 ******************************************************************************
 **
 ** All Fault Tolerance Groups Membership changes related.
 **
 */

typedef DSM_MembershipChangeType FTM_MembershipChangeType;

/*
 * Membership change callback (All Fault Tolerance Groups).
 */

/* Callback manager get function. */
ITSDLLAPI CALLBACK_Manager* FTM_GetMembershipChangeAllFtGroupsCallbacks();

/* Callback data definition. */
typedef struct
{
    ITS_USHORT ftGroupId;
    FTM_MembershipChangeType membershipChangeType;
    ITS_USHORT memberNodeId;
    ITS_USHORT memberProcessId;
    ITS_USHORT numFtGroupMembers;
    const FTM_FtGroupMember* ftGroupMembers;
} FTM_MembershipChangeAllFtGroupsCbData;

/* Callback function signature definition. */
typedef ITS_CALLBACK FTM_MembershipChangeAllFtGroupsCb;



/******************************************************************************
 ******************************************************************************
 **
 ** All Fault Tolerance Groups Multicast/Receive events to/from members.
 **
 */

ITSDLLAPI int FTM_MulticastEventToAllFtGroupMembers(
                                        const ITS_EVENT* event);

/*
 * Event from member callback (All Fault Tolerance Groups).
 */

/* Callback manager get function. */
ITSDLLAPI CALLBACK_Manager* FTM_GetEventFromAllFtGroupMembersCallbacks();

/* Callback data definition. */
typedef struct
{
    ITS_USHORT ftGroupId;
    const ITS_EVENT* event;
} FTM_EventFromAllFtGroupMembersCbData;

/* Callback function signature definition. */
typedef ITS_CALLBACK FTM_EventFromAllFtGroupMembersCb;


/******************************************************************************
 ******************************************************************************
 ******************************************************************************
 ***
 ***    Implementation related. NOT for typical FTM API end-users.
 ***
 ***/


/******************************************************************************
 ******************************************************************************
 **
 ** FTM Core class.
 **
 */

/*
 * Only one instance of FTM Core class per process (singleton using LOCKABLE).
 */

/*
 * FTM Core class definition.
 */

typedef struct
{
    void* reserved1;
    void* reverved2;
}
FTM_CoreClassPart;


typedef struct
{
    ITS_CoreClassPart   coreClass;
    LOCKABLE_ClassPart  lockClass;
    FTM_CoreClassPart   ftmClass;
}
FTM_CoreClassRec, *FTM_CoreClass;

#define FTM_CORE_CLASS_NAME  "FTM Core Class"



/*
 * FTM Core object definition.
 */ 

typedef struct
{
    void*                           ftmContext;
    RESFILE_Manager*                configDb;
    ITS_SEMAPHORE                   terminationSema;
    CALLBACK_Manager*               membershipChangeAllFtGroupsCallbacks;
    CALLBACK_Manager*               eventFromAllFtGroupMembersCallbacks;
    FTM_PreExecuteLogicProc         preExecuteLogicProc;
    FTM_LoopExecuteLogicProc        loopExecuteLogicProc;
    FTM_PostExecuteLogicProc        postExecuteLogicProc;
}
FTM_CoreObjectPart;


typedef struct
{
    ITS_CoreObjectPart  coreObject;
    FTM_CoreObjectPart  ftmObject;
}
FTM_CoreObject;

#define FTM_CORE_FTM_CONTEXT(x) \
    (((FTM_CoreObject*)(x))->ftmObject.ftmContext)

#define FTM_CORE_CONFIG_DB(x) \
    (((FTM_CoreObject*)(x))->ftmObject.configDb)

#define FTM_CORE_TERMINATION_SEMA(x) \
    (((FTM_CoreObject*)(x))->ftmObject.terminationSema)

#define FTM_CORE_MEMBERSHIP_CHANGE_ALL_FT_GROUPS_CALLBACKS(x) \
    (((FTM_CoreObject*)(x))->ftmObject.membershipChangeAllFtGroupsCallbacks)

#define FTM_CORE_EVENT_FROM_ALL_FT_GROUP_MEMBERS_CALLBACKS(x) \
    (((FTM_CoreObject*)(x))->ftmObject.eventFromAllFtGroupMembersCallbacks)

#define FTM_CORE_PRE_EXECUTE_LOGIC_PROC(x) \
    (((FTM_CoreObject*)(x))->ftmObject.preExecuteLogicProc)

#define FTM_CORE_LOOP_EXECUTE_LOGIC_PROC(x) \
    (((FTM_CoreObject*)(x))->ftmObject.loopExecuteLogicProc)

#define FTM_CORE_POST_EXECUTE_LOGIC_PROC(x) \
    (((FTM_CoreObject*)(x))->ftmObject.postExecuteLogicProc)


/******************************************************************************
 ******************************************************************************
 **
 ** FTM Init (initialization) class.
 **
 */
 
/*
 * Responsible for initializing/terminating the FTM subsystem. No objects. Only
 * Class Initialize and Class Terminate are implemented.
 */

typedef ITS_ClassRec    FTM_InitClassRec;
typedef ITS_ClassRec*   FTM_InitClass;

#define FTM_INIT_CLASS_NAME "FTM Initialization Class"



/******************************************************************************
 ******************************************************************************
 **
 ** Class records.
 **
 */

ITSDLLAPI extern FTM_CoreClassRec   itsFTM_CoreClassRec;
ITSDLLAPI extern ITS_Class          itsFTM_CoreClass;


ITSDLLAPI extern FTM_InitClassRec   itsFTM_InitClassRec;
ITSDLLAPI extern ITS_Class          itsFTM_InitClass;

/*
 * callbacks for the redundant stack
 */
ITSSS7DLLAPI void MTP3_MembershipChangeCallBack_ANSI(ITS_POINTER object,
                                                     ITS_POINTER userData,
                                                     ITS_POINTER callData);
ITSSS7DLLAPI void MTP3_MembershipChangeCallBack_CCITT(ITS_POINTER object,
                                                      ITS_POINTER userData,
                                                      ITS_POINTER callData);
ITSSS7DLLAPI void MTP3_MembershipChangeCallBack_PRC(ITS_POINTER object,
                                                    ITS_POINTER userData,
                                                    ITS_POINTER callData);
ITSSS7DLLAPI void MTP3_MembershipChangeCallBack_TTC(ITS_POINTER object,
                                                    ITS_POINTER userData,
                                                    ITS_POINTER callData);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_FTM_H_ */


