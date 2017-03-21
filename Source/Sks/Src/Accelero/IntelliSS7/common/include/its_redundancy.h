/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:08  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.2.4.4.3  2005/01/07 14:58:23  ssingh
 * LOG: Changes in connection with  enhancement of ACTIVE-BACKUP redundancy.
 * LOG:
 * LOG: Revision 1.1.2.4.4.2  2004/12/20 12:32:33  mmanikandan
 * LOG: Support for Windows compilation.
 * LOG:
 * LOG: Revision 1.1.2.4.4.1  2004/12/15 15:53:59  dsatish
 * LOG: changes propagated from SHIM branch
 * LOG:
 * LOG: Revision 1.1.2.4  2004/11/18 11:29:47  sjaddu
 * LOG: Configuration checks added.
 * LOG:
 * LOG: Revision 1.1.2.3  2004/02/09 05:46:24  sjaddu
 * LOG: Added extern C for c++.
 * LOG:
 * LOG: Revision 1.1.2.2  2004/01/30 06:23:34  sjaddu
 * LOG: Send notification event to app for active-active config.
 * LOG:
 * LOG: Revision 1.1.2.1  2004/01/27 13:40:02  sjaddu
 * LOG: Added file for active-back up redundancy.
 * LOG:
 *
 ****************************************************************************/

#ifndef  _ITS_REDUNDANCY_H_
#define  _ITS_REDUNDANCY_H_

#include <stdlib.h>
#include <its.h>
#include <its_types.h>
#include <its_transports.h>
#include <its_trace.h>

#if defined(WIN32)
#if defined(REDUNDANCY_IMPLEMENTATION)
#define REDDLLAPI __declspec(dllexport)
#else
#define REDDLLAPI __declspec(dllimport)
#endif
#else
#define REDDLLAPI
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#define REDUNDANCY_CLASS_NAME                   "Redundancy-Type"
#define REDUNDANCY_APP_OPTION_STRING            "redundancyType"
#define REDUNDANCY_ACTIVE_ACTIVE_STRING         "active-active"
#define REDUNDANCY_ACTIVE_BACKUP_STRING         "active-backup"
#define REDUNDANCY_NODE_STATE_ACTIVE_STRING     "active"
#define REDUNDANCY_NODE_STATE_BACKUP_STRING     "backup"
#define REDUNDANCY_NODE_STATE_STRING            "nodeState"
#define REDUNDANCY_APP_SELECT_ALL               "appSelectAll"
#define REDUNDANCY_APP_SELECT_NODE              "appSelectNode"


#define ITS_RED_MODULE_SRC                  (0X7FFEU)

#define ITS_STATE_CHANGE_EVENT              0xC7
#define ITS_NODE_LEFT_NOTIFICATION_EVENT    0xC8
#define ITS_NODE_JOIN_NOTIFICATION_EVENT    0xC9
#define ITS_PLATFORM_ACTIVE_NOTIFICATION_EVENT     0xCA
#define ITS_PLATFORM_BACKUP_NOTIFICATION_EVENT     0xCB
#define ITS_GET_STATE_FROM_EVENT(evt)       evt->data[1]

/*Node state, only for active-back*/
typedef enum
{
    ITS_STATE_PRIMARY = 0,
    ITS_STATE_BACKUP
}
ITS_NODE_STATE;

/*redundancy type*/
typedef enum
{
    ITS_ACTIVE_ACTIVE = 0,
    ITS_ACTIVE_STANDBY
}
ITS_REDUNDANCY_TYPE;


typedef ITS_NODE_STATE (*ITS_GetNodeStateProc)(void);
typedef CALLBACK_Manager* (*ITS_RedundancyCallBackMgr)(void);
typedef void (*ITS_ChangeNodeStateProc)(void);
 
typedef struct
{
    ITS_REDUNDANCY_TYPE              redundancyType;
    ITS_GetNodeStateProc             getNodeStateproc;   
    ITS_ChangeNodeStateProc          changeNodeStateProc; 
    ITS_RedundancyCallBackMgr        getRedundancyCallbackMgr; 
}
REDUNDANCY_ClassPart;

typedef struct
{
    ITS_CoreClassPart       coreClass;
    REDUNDANCY_ClassPart    redunClass;
}
REDUNDANCY_ClassRec, *REDUNDANCY_Class;

/* 
 * interface
 */
REDDLLAPI extern REDUNDANCY_ClassRec    its_REDUNDANCYClassRec;
REDDLLAPI extern ITS_Class              itsREDUNDANCY_Class;


#define REDUNDANCY_CALLBACK_MGR(x) \
    (((REDUNDANCY_Class)(x))->redunClass.getRedundancyCallbackMgr)()

#define REDUNDANCY_CONFIGURED_TYPE(x) \
    (((REDUNDANCY_Class)(x))->redunClass.redundancyType)

#define REDUNDANCY_GET_NODE_STATE(x)\
    (((REDUNDANCY_Class)(x))->redunClass.getNodeStateproc)()

#define REDUNDANCY_CHANGE_NODE_STATE_PROC(x)\
    (((REDUNDANCY_Class)(x))->redunClass.changeNodeStateProc)

typedef struct
{
   ITS_NODE_STATE state;
}
ITS_USR_PART_STATE;

/*public API*/
REDDLLAPI int
ITS_SendStateChangeEventToStack(ITS_NODE_STATE type);
REDDLLAPI ITS_INT REDUNDANCY_GetNodeStartUpFlagAndState(ITS_NODE_STATE *state);
REDDLLAPI ITS_INT ITS_GetNodeState(ITS_NODE_STATE *state);

/* Callback */
REDDLLAPI extern CALLBACK_Manager  *ITS_RedundancyMgmtCallbacks;

#ifdef  __cplusplus
}
#endif

#endif
