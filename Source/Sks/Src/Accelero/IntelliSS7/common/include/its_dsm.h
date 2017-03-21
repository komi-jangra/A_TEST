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
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:31  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.1  2005/09/27 09:38:27  adutta
 * LOG: Added BSSAP DSM tables
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.2.6.2.10.1  2005/01/07 14:58:23  ssingh
 * LOG: Changes in connection with  enhancement of ACTIVE-BACKUP redundancy.
 * LOG:
 * LOG: Revision 7.3.2.2.6.2  2004/01/27 05:57:54  yranade
 * LOG: Porting SCCP-CO Message Based Redundancy Changes from Kineto Branch.
 * LOG:
 * LOG: Revision 7.3.2.2.6.1  2004/01/05 09:24:45  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.3.2.2.2.2  2003/09/11 06:20:04  akumar
 * LOG: Added few MACROS for ISUP to use DSM-GCS.
 * LOG:
 * LOG: Revision 7.3.2.2.2.1  2003/09/05 10:08:56  akumar
 * LOG: Message based redundancy commit.
 * LOG:
 * LOG: Revision 7.3.4.2  2003/08/30 17:00:39  randresol
 * LOG: Add Logic for message based redundancy
 * LOG:
 * LOG: Revision 7.3.4.1  2003/05/05 22:09:20  randresol
 * LOG: Add tag for ISUP GCS prototype
 * LOG:
 * LOG: Revision 7.3  2003/01/30 21:27:57  mmiers
 * LOG: Start adding table type.
 * LOG:
 * LOG: Revision 7.2.4.2  2003/04/15 21:20:56  randresol
 * LOG: Add an FT group for TCAP timers
 * LOG:
 * LOG: Revision 7.2.4.1  2003/04/08 17:47:56  randresol
 * LOG: Chages for GCS TCAP prototype
 * LOG:
 * LOG: Revision 7.2  2002/11/09 21:16:26  randresol
 * LOG: Add definitions for Route Reader/Writer lock in DSM
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.16  2002/06/28 18:36:26  ssharma
 * LOG: Changes for distributed ISUP.
 * LOG:
 * LOG: Revision 6.15  2002/05/15 14:56:51  randresol
 * LOG: Add CCITT_MTP3_BEHAVIORS and CCITT_MTP3_TIMERS mgmt keys
 * LOG:
 * LOG: Revision 6.14  2002/05/07 19:48:35  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 6.13  2002/05/01 19:25:16  hdivoux
 * LOG: Added DSM implementation class declarations (for convenience).
 * LOG:
 * LOG: Revision 6.12  2002/04/29 21:31:47  randresol
 * LOG: add DSM_MTP3_STATIC_BOOLS key for MTP3 booleans
 * LOG:
 * LOG: Revision 6.11  2002/04/19 22:09:36  hdivoux
 * LOG: Start adding pre-add callbacks mechanism (for Engine).
 * LOG: Revision 6.7.2.1  2002/04/18 19:24:21  randresol
 * LOG: Add changes for redundant MTP3
 * LOG:
 * LOG: Revision 6.7  2002/04/03 23:25:05  mmiers
 * LOG: Add keys for SCCP
 * LOG:
 * LOG: Revision 6.10  2002/04/16 21:20:30  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.9  2002/04/15 21:05:00  hdivoux
 * LOG: Added configurable FtGroups.
 * LOG:
 * LOG: Revision 6.8  2002/04/11 20:36:18  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/


#if !defined(_ITS_DSM_H_)
#define _ITS_DSM_H_

#include <its.h>
#include <its_lockable.h>
#include <its_callback.h>
#include <its_iniparse.h>

#ident "$Id: its_dsm.h,v 1.2 2008-02-07 04:30:26 bsccs2 Exp $"

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
 * Configuration strings for general 'DsmFaultTolerance' section.
 */

/* Section name. */
#define DSM_FAULT_TOLERANCE_STRING              "DsmFaultTolerance"

#define DSM_MAX_NUM_NODES_STRING                "dsmMaxNumNodes"
#define DSM_MAX_NUM_PROCESSES_STRING            "dsmMaxNumProcesses"
#define DSM_MAX_NUM_FT_GROUPS_STRING            "dsmMaxNumFtGroups"

#define DSM_NODE_ID_STRING                      "dsmNodeId"
#define DSM_PROCESS_ID_STRING                   "dsmProcessId"

#define DSM_TCAP_FT_GROUP_ID_STRING             "dsmTcapFtGroupId"
#define DSM_SCCP_FT_GROUP_ID_STRING             "dsmSccpFtGroupId"
#define DSM_MTP3_FT_GROUP_ID_STRING             "dsmMtp3FtGroupId"
#define DSM_ISUP_FT_GROUP_ID_STRING             "dsmIsupFtGroupId"
#define DSM_ROUTING_FT_GROUP_ID_STRING          "dsmRoutingFtGroupId"
#define DSM_TIMERS_FT_GROUP_ID_STRING           "dsmTimersFtGroupId"
#define DSM_MGMT_DATA_FT_GROUP_ID_STRING        "dsmMgmtDataFtGroupId"
#define DSM_TCAP_TIMERS_FT_GROUP_ID_STRING      "dsmTcapTimersFtGroupId"


/*
 * Configuration strings for 'DsmFtGroup[n]' sections. The index [n] of the
 * 'DsmFtGroup[n]' sections must be within [0, dsmMaxNumFtGroups - 1].
 */

/* Section name (index to be added at the end). */
#define DSM_FT_GROUP_STRING                     "DsmFtGroup"

#define DSM_FT_GROUP_ID_STRING                  "dsmFtGroupId"
#define DSM_TYPE_STRING                         "dsmType"
#define DSM_BASE_ADDRESS_STRING                 "dsmBaseAddress"
#define DSM_SIZE_STRING                         "dsmSize"
#define DSM_MAX_NUM_TABLES_STRING               "dsmMaxNumTables"

#define DSM_NUM_FT_GROUP_MEMBERS_STRING         "dsmNumFtGroupMembers"
#define DSM_FT_GROUP_MEMBER_NODE_ID_STRING      "dsmFtGroupMemberNodeId"
#define DSM_FT_GROUP_MEMBER_PROCESS_ID_STRING   "dsmFtGroupMemberProcessId"

#define DSM_NUM_MASTER_FT_GROUP_MEMBERS_STRING          \
    "dsmNumMasterFtGroupMembers"
#define DSM_MASTER_FT_GROUP_MEMBER_NODE_ID_STRING       \
    "dsmMasterFtGroupMemberNodeId"
#define DSM_MASTER_FT_GROUP_MEMBER_PROCESS_ID_STRING    \
    "dsmMasterFtGroupMemberProcessId"

/* Optional, default value is DSM_DEFAULT_JOIN_FT_GROUP_TIMEOUT. */
#define DSM_JOIN_FT_GROUP_TIMEOUT_STRING        "dsmJoinFtGroupTimeout"


/* Optional, default value is DSM_DEFAULT_ROW_LOCK_TIMEOUT. */
#define DSM_ROW_LOCK_TIMEOUT_STRING             "dsmRowLockTimeout"


/* Optional, by default DSM initialization is implicit. */
#define DSM_INIT_EXPLICIT_STRING                "dsmInitExplicit"


/* Optional, by default joining a Fault Tolerance Group is implicit. */
#define DSM_JOIN_EXPLICIT_STRING                "dsmJoinExplicit"


/* Optional, by default DSM synchronization is implicit. */
#define DSM_SYNC_EXPLICIT_STRING                "dsmSyncExplicit"


/*
 * Configuration strings for 'DsmNodeNameResources' section.
 */

/* Section name. */
#define DSM_NODE_NAME_RESOURCES_STRING          "DsmNodeNameResources"

#define DSM_NODE_NAME_RES_NODE_ID               "dsmNodeNameResNodeId"
#define DSM_NODE_NAME_RES_NODE_NAME             "dsmNodeNameResNodeName"


/*
 * Configuration strings for 'DsmProcessNameResources' section.
 */

/* Section name. */
#define DSM_PROCESS_NAME_RESOURCES_STRING       "DsmProcessNameResources"

#define DSM_PROCESS_NAME_RES_NODE_ID            "dsmProcessNameResNodeId"
#define DSM_PROCESS_NAME_RES_PROCESS_ID         "dsmProcessNameResProcessId"
#define DSM_PROCESS_NAME_RES_PROCESS_NAME       "dsmProcessNameResProcessName"


/*
 * Configuration strings for 'DsmFtGroupNameResources' section.
 */

/* Section name. */
#define DSM_FT_GROUP_NAME_RESOURCES_STRING      "DsmFtGroupNameResources"

#define DSM_FT_GROUP_NAME_RES_FT_GROUP_ID       "dsmFtGroupNameResFtGroupId"
#define DSM_FT_GROUP_NAME_RES_FT_GROUP_NAME     "dsmFtGroupNameResFtGroupName"


/*
 * DSM maximum configuration sizes.
 */ 

#define DSM_MAX_CONFIG_VALUE_SIZE           (128)
#define DSM_MAX_CONFIG_KEY_SIZE             (128)
#define DSM_MAX_CONFIG_SECTION_NAME_SIZE    (128)
#define DSM_MAX_CONFIG_DSM_TYPE_SIZE        (32)



/*.interface:DSM_
 ******************************************************************************
 *
 *  Interface:
 *      DSM_*
 *
 *  Purpose:
 *      Distributed Shared Memory API.
 *
 *  Usage:
 *      See individual function usages and associated documentation.
 *
 *****************************************************************************/

/**********************************************************
 *                                                        *
 * Public data structures.                                *
 *                                                        *
 **********************************************************/

/*
 * Table types.
 */
typedef enum
{
    DSM_TABLE_HASH,
    DSM_TABLE_REDBLACK,
    DSM_TABLE_SPLAY
}
DSM_TableType;

/* 
 * Fault Tolerance Group Member. 
 */
typedef struct
{
    ITS_USHORT nodeId;
    ITS_USHORT processId;
}
DSM_FtGroupMember;

/* 
 * Implicit object for each table row. 
 */
typedef struct _dsm_RowHeader
{
    ITS_BOOLEAN             locked;
    ITS_UINT                checkSum;
    ITS_TIME                lockTime;
    ITS_OCTET*              key;
    ITS_UINT                klen;
    struct _dsm_RowHeader*  next;
}
DSM_RowHeader;


/**********************************************************
 *                                                        *
 * Public definitions                                     *
 *                                                        *
 **********************************************************/

/*
 * DSM maximum Fault Tolerance Group members (MUST BE >= 1).
 * Note: DSM implementations have typically more restrictions.
 */
#define DSM_MAX_FT_GROUP_MEMBERS        (64)

/*
 * DSM maximum Master Fault Tolerance Group members.
 * Note: DSM implementations have typically more restrictions.
 */
#define DSM_MAX_MASTER_FT_GROUP_MEMBERS (DSM_MAX_FT_GROUP_MEMBERS - 1)

/*
 * Pre-claimed tables.
 */
#define DSM_TABLE_ANSI_TCAP_DLG         1
#define DSM_TABLE_ITU_TCAP_DLG          2
#define DSM_TABLE_ANSI_TCAP_INV         3
#define DSM_TABLE_ITU_TCAP_INV          4
#define DSM_TABLE_ANSI_DIDS             5
#define DSM_TABLE_ITU_DIDS              6
#define DSM_TABLE_ANSI_SCCP_CTXT        7
#define DSM_TABLE_ITU_SCCP_CTXT         8
#define DSM_TABLE_ANSI_SCMG             9
#define DSM_TABLE_ITU_SCMG              10
#define DSM_TABLE_ANSI_SCCP_CPC         11
#define DSM_TABLE_ANSI_SCCP_LPC         12
#define DSM_TABLE_ITU_SCCP_CPC          13
#define DSM_TABLE_ITU_SCCP_LPC          14
#define DSM_TABLE_ITU_SCCP_DUPS         15
#define DSM_TABLE_ANSI_SCCP_DUPS        16
#define DSM_TABLE_ANSI_ISUP_OPC_DPC     17
#define DSM_TABLE_ITU_ISUP_OPC_DPC      18
#define DSM_TABLE_ANSI_ISUP_VCIC        19
#define DSM_TABLE_ITU_ISUP_VCIC         20
#define DSM_TABLE_ANSI_ISUP_PCIC        21
#define DSM_TABLE_ITU_ISUP_PCIC         22
#define DSM_TABLE_RKEYS                 23
#define DSM_TABLE_RCONTEXTS             24
#define DSM_TABLE_DESTINATIONS          25
#define DSM_TABLE_ROUTE_ARRAYS          26
#define DSM_TABLE_ROUTES                27
#define DSM_TABLE_LINK_SETS             28
#define DSM_TABLE_LINK_ARRAYS           29
#define DSM_TABLE_LINKS                 30
#define DSM_TABLE_LINK_MAPS             31
#define DSM_TABLE_QUEUES                32
#define DSM_TABLE_QDATA                 33
/* Left to allocate: 29.        */
#define DSM_TABLE_TIMERS                34
#define DSM_TABLE_MGMT_DATA             35

#define DSM_TABLE_ITU_ISUP_CKGP_LIST            36
#define DSM_TABLE_ANSI_ISUP_CKGP_LIST           37
#define DSM_TABLE_ITU_ISUP_PCIC_CSC_MSG         38
#define DSM_TABLE_ANSI_ISUP_PCIC_CSC_MSG        39

#define RED_NODE_STARTUP_FLAG_TABLE_ID          40
#define DSM_TABLE_BSSAP_CIC_CTXT                41
#define DSM_TABLE_BSSAP_CALL_CTXT               42
#define DSM_TABLE_BSSAP_NWID_LIST               43
#define DSM_TABLE_BSSAP_RPC_LIST                44
#define DSM_TABLE_BSSAP_APPID_LIST              45 //Added by Amaresh 04-02-08
#define DSM_TABLE_MGMT_DATA_1           47

/* Middleware reserves: 1-47.   */
#define DSM_TABLE_FIRST_USER            48
#define DSM_TABLE_MGMT_DATA_SCCP_CTXT             49
#define DSM_TABLE_MGMT_DATA_SCCP_SST              46

/*
 * Pre-defined keys.
 */
#define DSM_MGMT_REC_TIMERS                         1
#define DSM_MGMT_REC_ANSI_MTP3_TIMERS               2
#define DSM_MGMT_REC_ANSI_MTP3_BEHAVIORS            3
#define DSM_MGMT_REC_ANSI_SCCP_SST_SERIAL           4
#define DSM_MGMT_REC_ANSI_SCCP_SOR_SERIAL           5
#define DSM_MGMT_REC_ANSI_SCCP_SST_IGNORE_SERIAL    6
#define DSM_MGMT_REC_CCITT_SCCP_SST_SERIAL          7
#define DSM_MGMT_REC_CCITT_SCCP_SOR_SERIAL          8
#define DSM_MGMT_REC_CCITT_SCCP_SST_IGNORE_SERIAL   9
#define DSM_MTP3_STATIC_BOOLS                       10 
#define DSM_MGMT_REC_CCITT_MTP3_BEHAVIORS           11
#define DSM_MGMT_REC_CCITT_MTP3_TIMERS              12
#define DSM_MGMT_REC_ROUTERWLOCK                    13
#define DSM_CCITT_SCCP_NEXT_REF_NUM                 14
#define DSM_ANSI_SCCP_NEXT_REF_NUM                  15

/*
 * Fault Tolerance Group join default timeout (milliseconds).
 */
#define DSM_DEFAULT_JOIN_FT_GROUP_TIMEOUT   30000

/*
 * Row lock auto-release default timeout (seconds).
 */
#define DSM_DEFAULT_ROW_LOCK_TIMEOUT        3


/******************************************************************************
 ******************************************************************************
 **
 ** Configurable Fault Tolerance Groups (major IntelliSS7 subsystems).
 **
 */

extern ITSDLLAPI ITS_USHORT DSM_TcapFtGroupId;
extern ITSDLLAPI ITS_USHORT DSM_SccpFtGroupId;
extern ITSDLLAPI ITS_USHORT DSM_Mtp3FtGroupId;
extern ITSDLLAPI ITS_USHORT DSM_IsupFtGroupId;
extern ITSDLLAPI ITS_USHORT DSM_RoutingFtGroupId;
extern ITSDLLAPI ITS_USHORT DSM_TimersFtGroupId;
extern ITSDLLAPI ITS_USHORT DSM_MgmtDataFtGroupId;
extern ITSDLLAPI ITS_USHORT DSM_TcapTimersFtGroupId;


/******************************************************************************
 ******************************************************************************
 **
 ** Initialization/Termination.
 **
 */

/*****************************************************************************
 * Important note: IntelliSS7 Engine (if used) calls automatically all DSM   *
 * initialization and termination functions.                                 *
 *****************************************************************************/

/*
 * Pre-initialize DSM subsystem from Resource Manager configuration.
 * - Called automatically during Engine initialization.
 * - Must be called only once per process.
 */
ITSDLLAPI int DSM_PreInitializeFromConfig();

/*
 * Pre-initialize DSM subsystem with specified configuration.
 * - Must be called only once per process.
 */
ITSDLLAPI int DSM_PreInitialize(
                        ITS_USHORT maxNumFtGroups,
                        ITS_USHORT maxNumProcesses,
                        ITS_USHORT maxNumNodes,
                        ITS_USHORT nodeId,
                        ITS_USHORT processId);

/*
 * Post-terminate DSM subsystem.
 * - Called automatically during Engine termination.
 * - Must be called only once per process.
 */
ITSDLLAPI void DSM_PostTerminate();

/* 
 * Initialize a Fault Tolerance Group from Resource Manager configuration.
 * - Called automatically during Engine initialization unless explicit
 *   initialization/termination is specified (through 'dsmInitExplicit').
 * - Must be called once per Fault Tolerance Group.
 * - Explicit initialization/termination implies explicit join/leave.
 */
ITSDLLAPI int DSM_InitializeFromConfig(ITS_USHORT ftGroupId);

/*
 * Initialize a Fault Tolerance Group with specified configuration.
 * - Arguments that are specific to a DSM implementation (e.g. GCS/SCI/other)
 *   are passed as character strings of key/value pair through the variable
 *   argument list. For instance:
 *     - "dsmGcsDaemonName=3267"
 *     - "dsmGcsSyncMemUseTcp=1"
 *     - "dsmSyncExplicit=1"
 * - Must be called once per Fault Tolerance Group.
 * - Last (mandatory) variable argument must be NULL (used as a terminator).
 * - All variable arguments must be of type character string (char*).
 */
ITSDLLAPI int DSM_Initialize(
                        ITS_USHORT  ftGroupId,
                        ITS_UINT    maxNumTables,
                        ITS_UINT    dsmSize,
                        const void* dsmBaseAddress,
                        const char* dsmType,
                        ...);

/*
 * Terminate a Fault Tolerance Group.
 * - Called automatically during Engine termination unless explicit
 *   initialization/termination is specified (through 'dsmInitExplicit').
 * - Must be called once per Fault Tolerance Group.
 */
ITSDLLAPI void DSM_Terminate(ITS_USHORT ftGroupId);


/******************************************************************************
 ******************************************************************************
 **
 ** Initialization status information.
 **
 */

/*
 * Is DSM subsystem pre-initialized?
 */
ITSDLLAPI ITS_BOOLEAN DSM_IsPreInitialized();

/*
 * Is Fault Tolerance Group initialized?
 */
ITSDLLAPI ITS_BOOLEAN DSM_IsInitialized(ITS_USHORT ftGroupId);


/******************************************************************************
 ******************************************************************************
 **
 ** Configuration information.
 **
 */

ITSDLLAPI ITS_USHORT DSM_GetMaxNumNodes();

ITSDLLAPI ITS_USHORT DSM_GetMaxNumProcesses();

ITSDLLAPI ITS_USHORT DSM_GetMaxNumFtGroups();

ITSDLLAPI ITS_UINT DSM_GetMaxNumTables(ITS_USHORT ftGroupId);


/******************************************************************************
 ******************************************************************************
 **
 ** Topology configuration.
 **
 */

/*****************************************************************************
 * Important note: IntelliSS7 Engine (if used) calls automatically the       *
 * relevant (i.e. 'FromConfig') topology configuration functions.            *
 *****************************************************************************/

/*
 * Configure all the Fault Tolerance Group Members of a Fault Tolerance Group
 * from Resource Manager configuration.
 * - Called automatically during Engine initialization.
 * - Must include self (in Resource Manager configuration).
 * - Must be called for each Fault Tolerance Group.
 */
ITSDLLAPI int DSM_ConfigureFtGroupMembersFromConfig(
                        ITS_USHORT ftGroupId);

/* 
 * Configure all the Fault Tolerance Group Members of a Fault Tolerance Group
 * explicitly.
 * - Must include self.
 * - Must be called for each Fault Tolerance Group.
 */
ITSDLLAPI int DSM_ConfigureFtGroupMembers(
                        ITS_USHORT ftGroupId,
                        ITS_USHORT numFtGroupMembers,
                        const DSM_FtGroupMember* ftGroupMembers);

/*
 * Configure all the Master Fault Tolerance Group Members of a Fault Tolerance
 * Group from Resource Manager configuration.
 * - Called automatically during Engine initialization.
 * - Must not include self (in Resource Manager configuration).
 * - Must be called for each Fault Tolerance Group.
 */
ITSDLLAPI int DSM_ConfigureMasterFtGroupMembersFromConfig(
                        ITS_USHORT ftGroupId);

/*
 * Configure all the Master Fault Tolerance Group Members of a Fault Tolerance
 * Group explicitly.
 * - Must not include self.
 * - Must be called for each Fault Tolerance Group.
 */
ITSDLLAPI int DSM_ConfigureMasterFtGroupMembers(
                        ITS_USHORT ftGroupId,
                        ITS_USHORT numMasterFtGroupMembers,
                        const DSM_FtGroupMember* masterFtGroupMembers);


/******************************************************************************
 ******************************************************************************
 **
 ** Join/Leave a Fault Tolerance Group.
 **
 */

/*****************************************************************************
 * Important note: IntelliSS7 Engine (if used) calls automatically DSM join  *
 * and leave functions unless explicit join/leave is specified.              *
 *****************************************************************************/

/*
 * Join a Fault Tolerance Group. 
 * - Called automatically during Engine initialization unless explicit
 *   join/leave is specified (through 'dsmJoinExplicit').
 * - Typically must be called once for each Fault Tolerance Group.
 */
ITSDLLAPI int DSM_JoinFtGroup(ITS_USHORT ftGroupId);


/*
 * Leave a Fault Tolerance Group.
 * - Called automatically during Engine termination unless explicit join/leave
 *   is specified (through 'dsmJoinExplicit').
 * - Typically must be called once for each Fault Tolerance Group.
 */
ITSDLLAPI int DSM_LeaveFtGroup(ITS_USHORT ftGroupId);


/******************************************************************************
 ******************************************************************************
 **
 ** Joining status information.
 **
 */

/*
 * Is Fault Tolerance Group joined?
 */
ITSDLLAPI ITS_BOOLEAN DSM_IsFtGroupJoined(ITS_USHORT ftGroupId);


/******************************************************************************
 ******************************************************************************
 **
 ** Synchronization of Distributed Shared Memory Instance.
 **
 */

/*****************************************************************************
 * Important note: Synchronization of a DSM Instance is automatically done   *
 * when joining a Fault Tolerance Group (if not first member of the group)   *
 * unless explicit synchronization is specified (through 'dsmSyncExplicit'). *
 *****************************************************************************/

/*
 * Synchronization is done with one of the specified Master Fault Tolerance
 * Group members (according to their status).
 */
ITSDLLAPI int DSM_SynchronizeDsm(
                        ITS_USHORT ftGroupId,
                        ITS_UINT msecs);


/******************************************************************************
 ******************************************************************************
 **
 ** Current Node/Process information.
 **
 */

ITSDLLAPI ITS_USHORT DSM_GetNodeId();
ITSDLLAPI ITS_USHORT DSM_GetProcessId();

ITSDLLAPI const char* DSM_GetNodeName();
ITSDLLAPI const char* DSM_GetProcessName();


/******************************************************************************
 ******************************************************************************
 **
 ** Name resources related (for others and self).
 **
 */

/*****************************************************************************
 * Important note: IntelliSS7 Engine (if used) calls automatically all DSM   *
 * name resources configuration functions.                                   *
 *****************************************************************************/

ITSDLLAPI int DSM_ConfigureFtGroupName(
                        ITS_USHORT ftGroupId,
                        const char* ftGroupName);

ITSDLLAPI int DSM_ConfigureNodeName(
                        ITS_USHORT nodeId,
                        const char* nodeName);

ITSDLLAPI int DSM_ConfigureProcessName(
                        ITS_USHORT nodeId,
                        ITS_USHORT processId,
                        const char* processName);


ITSDLLAPI const char* DSM_GetFtGroupNameFromId(
                        ITS_USHORT ftGroupId);

ITSDLLAPI const char* DSM_GetNodeNameFromId(
                        ITS_USHORT nodeId);

ITSDLLAPI const char* DSM_GetProcessNameFromId(
                        ITS_USHORT nodeId,
                        ITS_USHORT processId);


/******************************************************************************
 ******************************************************************************
 **
 ** Tables and rows related.
 **
 */

/* 
 * Notes:
 * - Alloc/Find implicitly lock the row (if created/found).  
 * - Free/Commit implicitly unlock the row.  
 * - Lock/Unlock operate on rows without changing their contents, but expect 
 *   the row to exist (otherwise Lock/Unlock will return an error).
 */

/*
 * Rows Alloc/Find/Free/Commit/LockRow/UnlockRow.
 */

ITSDLLAPI void* DSM_Alloc(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    ITS_UINT size, 
                    int* error);

ITSDLLAPI void* DSM_AllocLocal(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    ITS_UINT size, 
                    int* error);

ITSDLLAPI void* DSM_Find(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    int* error);

ITSDLLAPI void* DSM_FindLocal(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    int* error);

ITSDLLAPI int DSM_Free(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    void* object);

ITSDLLAPI int DSM_FreeLocal(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    void* object);

ITSDLLAPI int DSM_Commit(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    void* object);

ITSDLLAPI int DSM_CommitLocal(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    void* object);

ITSDLLAPI int DSM_LockRow(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    void* object);

ITSDLLAPI int DSM_UnlockRow(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    void* object);

/* 
 * For finer control:
 * - LockDsm/UnlockDsm. Lock the entire DSM (associated with the FtGroup).
 * - LockTable/UnlockTable. Lock a table.
 * - AllocNoLock. Either entire DSM or Table MUST be locked.
 * - FindNoLock. Either entire DSM or Table MUST be locked.
 * - FreeNoLock. Either entire DSM or Table MUST be locked.
 * - CommitNoLock. Either entire DSM or Table MUST be locked.
 * - LockRowNoLock. Either entire DSM or Table MUST be locked. Row Lock.
 * - UnlockRowNoLock. Either entire DSM or Table MUST be locked. Row Lock.
 */


/* 
 * Entire DSM Lock/Unlock. 
 */

ITSDLLAPI int DSM_LockDsm(
                    ITS_USHORT ftGroupId);

ITSDLLAPI int DSM_UnlockDsm(
                    ITS_USHORT ftGroupId);

/* 
 * Tables Lock/Unlock. 
 */

ITSDLLAPI int DSM_LockTable(
                    ITS_USHORT ftGroupId, 
                    ITS_UINT tableId);

ITSDLLAPI int DSM_LockTableLocal(
                    ITS_USHORT ftGroupId, 
                    ITS_UINT tableId);

ITSDLLAPI int DSM_UnlockTable(
                    ITS_USHORT ftGroupId, 
                    ITS_UINT tableId);

ITSDLLAPI int DSM_UnlockTableLocal(
                    ITS_USHORT ftGroupId, 
                    ITS_UINT tableId);

/*
 * Rows AllocNoLock/FindNoLock/FreeNoLock/CommitNoLock/LockRowNoLock/
 * UnlockRowNoLock.
 */

ITSDLLAPI void* DSM_AllocNoLock(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    ITS_UINT size, 
                    int* error);

ITSDLLAPI void* DSM_AllocNoLockLocal(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    ITS_UINT size, 
                    int* error);

ITSDLLAPI void* DSM_FindNoLock(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    int* error);

ITSDLLAPI void* DSM_FindNoLockLocal(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    int* error);

ITSDLLAPI int DSM_FreeNoLock(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,           
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    void* object);

ITSDLLAPI int DSM_FreeNoLockLocal(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,           
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    void* object);

ITSDLLAPI int DSM_CommitNoLock(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    void* object);

ITSDLLAPI int DSM_CommitNoLockLocal(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, 
                    ITS_UINT klen,
                    void* object);

ITSDLLAPI int DSM_LockRowNoLock(
                    ITS_USHORT ftGroupId,
                    void* object);

ITSDLLAPI int DSM_UnlockRowNoLock(
                    ITS_USHORT ftGroupId,
                    void* object);


/*
 * Entry iterate function signature definition.
 */
typedef int (*DSM_IterateEntryProc)(ITS_POINTER data, void* in, void* out);


/*
 * Walks all the rows of the specified table. Intended for general iteration
 * purposes (high efficiency).
 */
ITSDLLAPI int DSM_TableIterate(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId, 
                    void* in, 
                    void* out,
                    DSM_IterateEntryProc iterateEntryFn);

ITSDLLAPI int DSM_TableIterateLocal(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId, 
                    void* in, 
                    void* out,
                    DSM_IterateEntryProc iterateEntryFn);
/*
 * Entry dump function signature definition.
 */
typedef int (*DSM_DumpEntryProc)(ITS_POINTER data, char** pStrDump);


/*
 * Walks all the rows of the specified table. Intended for row dumping (medium
 * efficiency due to realloc calls).
 */
ITSDLLAPI int DSM_TableDump(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId, 
                    char** pStrDump,                            
                    DSM_DumpEntryProc dumpEntryFn);

/*
 * Size (number of entries) of the specified table.
 */
ITSDLLAPI int DSM_TableGetSize(
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId, 
                    ITS_UINT* size);


/******************************************************************************
 ******************************************************************************
 **
 ** Fault Tolerance Group Membership changes related.
 **
 */

/*
 * Membership possible changes.
 */

typedef enum
{
    DSM_FT_GROUP_MEMBER_ALIVE,
    DSM_FT_GROUP_MEMBER_JOIN,
    DSM_FT_GROUP_MEMBER_LEAVE,
    DSM_FT_GROUP_MEMBER_DEAD
}
DSM_MembershipChangeType;


/*
 * Membership change callback.
 */

/* Callback manager get function. */
ITSDLLAPI CALLBACK_Manager* DSM_GetMembershipChangeCallbacks(
                                        ITS_USHORT ftGroupId);

/* 
 * Pre-add (before a call to DSM_Initialize) a membership change callback.
 * - Callbacks that are pre-added are added by DSM_Initialize (according to the
 *   specified Fault Tolerance Group).
 * - Typically to be used in correlation with Engine to allow adding callbacks
 *   as soon as a Fault Tolerance Group is initialized.
 */
ITSDLLAPI int DSM_PreAddMembershipChangeCallback(
                                        ITS_USHORT ftGroupId,
                                        ITS_CALLBACK cbFunction,
                                        ITS_POINTER userData);

/* Callback data definition. */
typedef struct
{
    ITS_USHORT ftGroupId;
    DSM_MembershipChangeType membershipChangeType;
    ITS_USHORT memberNodeId;
    ITS_USHORT memberProcessId;
    ITS_USHORT numFtGroupMembers;               /* Valid for join and leave. */
    const DSM_FtGroupMember* ftGroupMembers;    /* Valid for join and leave. */
} DSM_MembershipChangeCbData;

/* Callback function signature definition. */
typedef ITS_CALLBACK DSM_MembershipChangeCb;


/******************************************************************************
 ******************************************************************************
 **
 ** Critical (unrecoverable for DSM subsystem) error notification related.
 **
 */

/*
 * Critical error notification callback.
 */

/* Callback manager get function. */
ITSDLLAPI CALLBACK_Manager* DSM_GetCriticalErrorNotificationCallbacks();

/* 
 * Pre-add (before a call to DSM_PreInitialize) a critical error notification 
 * callback.
 * - Callbacks that are pre-added are added by DSM_PreInitialize.
 * - Typically to be used in correlation with Engine to allow adding callbacks
 *   as soon as DSM subsystem is pre-initialized.
 */
ITSDLLAPI int DSM_PreAddCriticalErrorNotificationCallback(
                                        ITS_CALLBACK cbFunction,
                                        ITS_POINTER userData);

/* Callback data definition. */
typedef struct
{
    ITS_USHORT ftGroupId;
    const char* fileName;
    int lineNumber;
    const char* format;
    va_list alist;
} DSM_CriticalErrorNotificationCbData;

/* Callback function signature definition. */
typedef ITS_CALLBACK DSM_CriticalErrorNotificationCb;


/******************************************************************************
 ******************************************************************************
 **
 ** Fault Tolerance Group Multicast/Receive events to/from members.
 **
 */

ITSDLLAPI int DSM_MulticastEventToFtGroupMembers(
                                        ITS_USHORT ftGroupId,
                                        const ITS_EVENT* event);

ITSDLLAPI int DSM_MulticastStackEventToFtGroupMembers(
                                        ITS_USHORT ftGroupId,
                                        ITS_EVENT event,
                                        ITS_USHORT source,
                                        ITS_USHORT destination);
/*
 * Event from member callback.
 */

/* Callback manager get function. */
ITSDLLAPI CALLBACK_Manager* DSM_GetEventFromFtGroupMemberCallbacks(
                                        ITS_USHORT ftGroupId);

/* 
 * Pre-add (before a call to DSM_Initialize) an event from Fault Tolerance
 * Group Member callback.
 * - Callbacks that are pre-added are added by DSM_Initialize (according to the
 *   specified Fault Tolerance Group).
 * - Typically to be used in correlation with Engine to allow adding callbacks
 *   as soon as a Fault Tolerance Group is initialized.
 */
ITSDLLAPI int DSM_PreAddEventFromFtGroupMemberCallback(
                                        ITS_USHORT ftGroupId,
                                        ITS_CALLBACK cbFunction,
                                        ITS_POINTER userData);

/* Callback data definition. */
typedef struct
{
    ITS_USHORT ftGroupId;
    const ITS_EVENT* event;
} DSM_EventFromFtGroupMemberCbData;

/* Callback function signature definition. */
typedef ITS_CALLBACK DSM_EventFromFtGroupMemberCb;





/******************************************************************************
 ******************************************************************************
 ******************************************************************************
 ***
 ***    Implementation related. NOT for typical DSM API end-users.
 ***
 ***/

/**********************************************************
 *                                                        *
 * Protected data structures and defintions               *
 *                                                        *
 **********************************************************/

/*
 * Forward declarations.
 */

typedef struct _DSM_ImplClassRec* DSM_ImplClass;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM Inst (instance) class.
 **
 */

/*
 * One DSM Inst object per DSM instance (i.e. per Fault Tolerance Group).
 * Attribute 'implData' is an ITS_Object that contains per instance data 
 * specific to the underlying actual DSM implementation (e.g. DSM STUB).
 */

/*
 * DSM Inst class definition.
 */

typedef struct
{
    void* reserved1;
    void* reserved2;
}
DSM_InstClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    DSM_InstClassPart   dsmClass;

}
DSM_InstClassRec, *DSM_InstClass;

#define DSM_INST_CLASS_NAME  "DSM Instance Class"

/*
 * DSM Inst object definition.
 */

typedef struct
{
    ITS_USHORT          ftGroupId;
    ITS_BOOLEAN         ftGroupJoined;
    DSM_ImplClass       implClass;              /* DSM implementation class. */
    ITS_UINT            maxNumTables;
    ITS_UINT            dsmSize;
    const void*         dsmBaseAddress;
    const char*         dsmType;
    ITS_UINT            dsmJoinFtGroupTimeout;
    ITS_UINT            dsmRowLockTimeout;
    ITS_BOOLEAN         dsmSyncExplicit;
    ITS_USHORT          numFtGroupMembers;
    DSM_FtGroupMember*  ftGroupMembers;         /* Must include itself.      */
    ITS_USHORT          numMasterFtGroupMembers;
    DSM_FtGroupMember*  masterFtGroupMembers;   /* Must not include itself.  */
    CALLBACK_Manager*   membershipChangeCallbacks;
    CALLBACK_Manager*   eventFromFtGroupMemberCallbacks;
    ITS_Object          implData;               /* DSM implementation data.  */
}
DSM_InstObjectPart;

typedef struct
{
    ITS_CoreObjectPart  coreObject;
    DSM_InstObjectPart  dsmObject;
}
DSM_InstObject;

#define DSM_INST_FT_GROUP_ID(x) \
    (((DSM_InstObject*)(x))->dsmObject.ftGroupId)

#define DSM_INST_FT_GROUP_JOINED(x) \
    (((DSM_InstObject*)(x))->dsmObject.ftGroupJoined)

#define DSM_INST_IMPL_CLASS(x) \
    (((DSM_InstObject*)(x))->dsmObject.implClass)

#define DSM_INST_MAX_NUM_TABLES(x) \
    (((DSM_InstObject*)(x))->dsmObject.maxNumTables)

#define DSM_INST_DSM_SIZE(x) \
    (((DSM_InstObject*)(x))->dsmObject.dsmSize)

#define DSM_INST_DSM_BASE_ADDRESS(x) \
    (((DSM_InstObject*)(x))->dsmObject.dsmBaseAddress)

#define DSM_INST_DSM_TYPE(x) \
    (((DSM_InstObject*)(x))->dsmObject.dsmType)

#define DSM_INST_DSM_JOIN_FT_GROUP_TIMEOUT(x) \
    (((DSM_InstObject*)(x))->dsmObject.dsmJoinFtGroupTimeout)

#define DSM_INST_DSM_ROW_LOCK_TIMEOUT(x) \
    (((DSM_InstObject*)(x))->dsmObject.dsmRowLockTimeout)

#define DSM_INST_DSM_SYNC_EXPLICIT(x) \
    (((DSM_InstObject*)(x))->dsmObject.dsmSyncExplicit)

#define DSM_INST_NUM_FT_GROUP_MEMBERS(x) \
    (((DSM_InstObject*)(x))->dsmObject.numFtGroupMembers)

#define DSM_INST_FT_GROUP_MEMBERS(x) \
    (((DSM_InstObject*)(x))->dsmObject.ftGroupMembers)

#define DSM_INST_NUM_MASTER_FT_GROUP_MEMBERS(x) \
    (((DSM_InstObject*)(x))->dsmObject.numMasterFtGroupMembers)

#define DSM_INST_MASTER_FT_GROUP_MEMBERS(x) \
    (((DSM_InstObject*)(x))->dsmObject.masterFtGroupMembers)

#define DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(x) \
    (((DSM_InstObject*)(x))->dsmObject.membershipChangeCallbacks)

#define DSM_INST_EVENT_FROM_FT_GROUP_MEMBER_CALLBACKS(x) \
    (((DSM_InstObject*)(x))->dsmObject.eventFromFtGroupMemberCallbacks)

#define DSM_INST_IMPL_DATA(x) \
    (((DSM_InstObject*)(x))->dsmObject.implData)


/******************************************************************************
 ******************************************************************************
 **
 ** DSM Core class.
 **
 */

/*
 * Only one instance of DSM Core class per process (singleton using LOCKABLE).
 */

/*
 * DSM Core class definition.
 */

typedef struct
{
    void* reserved1;
    void* reverved2;
}
DSM_CoreClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    LOCKABLE_ClassPart  lockClass;
    DSM_CoreClassPart   dsmClass;
}
DSM_CoreClassRec, *DSM_CoreClass;

#define DSM_CORE_CLASS_NAME  "DSM Core Class"


/* 
 * Definitions used by DSM core object.
 */

#define DSM_INVALID_NODE_ID         ((ITS_USHORT)(-1))
#define DSM_INVALID_PROCESS_ID      ((ITS_USHORT)(-1))
#define DSM_INVALID_FT_GROUP_ID     ((ITS_USHORT)(-1))

typedef struct
{
    ITS_USHORT  nodeId;
    char*       nodeName;
}
DSM_NodeNameResource;

typedef struct
{
    ITS_USHORT  nodeId;
    ITS_USHORT  processId;
    char*       processName;
}
DSM_ProcessNameResource;

typedef struct
{
    ITS_USHORT  ftGroupId;
    char*       ftGroupName;
}
DSM_FtGroupNameResource;


/*
 * DSM maximum number of implementation classes.
 */

#define DSM_MAX_IMPL_CLASSES    (8)

typedef struct
{
    DSM_ImplClass classes[DSM_MAX_IMPL_CLASSES];
}
DSM_ImplClasses;


/*
 * DSM Core object definition.
 */ 

typedef struct
{
    ITS_USHORT                  maxNumNodes;
    ITS_USHORT                  maxNumProcesses;
    ITS_USHORT                  maxNumFtGroups;
    ITS_USHORT                  nodeId;
    ITS_USHORT                  processId;
    ITS_USHORT                  numFtGroups;
    DSM_InstObject**            ftGroups;
    DSM_NodeNameResource*       nodeNameResources;
    DSM_ProcessNameResource*    processNameResources;
    DSM_FtGroupNameResource*    ftGroupNameResources;
    CALLBACK_Manager*           criticalErrorNotificationCallbacks;
    RESFILE_Manager*            configDb;
    DSM_ImplClasses             implClasses;
}
DSM_CoreObjectPart;


typedef struct
{
    ITS_CoreObjectPart  coreObject;
    DSM_CoreObjectPart  dsmObject;
}
DSM_CoreObject;


#define DSM_CORE_MAX_NUM_NODES(x) \
    (((DSM_CoreObject*)(x))->dsmObject.maxNumNodes)

#define DSM_CORE_MAX_NUM_PROCESSES(x) \
    (((DSM_CoreObject*)(x))->dsmObject.maxNumProcesses)

#define DSM_CORE_MAX_NUM_FT_GROUPS(x) \
    (((DSM_CoreObject*)(x))->dsmObject.maxNumFtGroups)

#define DSM_CORE_NODE_ID(x) \
    (((DSM_CoreObject*)(x))->dsmObject.nodeId)

#define DSM_CORE_PROCESS_ID(x) \
    (((DSM_CoreObject*)(x))->dsmObject.processId)

#define DSM_CORE_NUM_FT_GROUPS(x) \
    (((DSM_CoreObject*)(x))->dsmObject.numFtGroups)

#define DSM_CORE_FT_GROUPS(x) \
    (((DSM_CoreObject*)(x))->dsmObject.ftGroups)

#define DSM_CORE_NODE_NAME_RESOURCES(x) \
    (((DSM_CoreObject*)(x))->dsmObject.nodeNameResources)

#define DSM_CORE_PROCESS_NAME_RESOURCES(x) \
    (((DSM_CoreObject*)(x))->dsmObject.processNameResources)

#define DSM_CORE_FT_GROUP_NAME_RESOURCES(x) \
    (((DSM_CoreObject*)(x))->dsmObject.ftGroupNameResources)

#define DSM_CORE_CRITICAL_ERROR_NOTIFICATION_CALLBACKS(x) \
    (((DSM_CoreObject*)(x))->dsmObject.criticalErrorNotificationCallbacks)

#define DSM_CORE_CONFIG_DB(x) \
    (((DSM_CoreObject*)(x))->dsmObject.configDb)

#define DSM_CORE_IMPL_CLASSES(x) \
    (((DSM_CoreObject*)(x))->dsmObject.implClasses)



/******************************************************************************
 ******************************************************************************
 **
 ** DSM Init (initialization) class.
 **
 */
 
/*
 * Responsible for initializing/terminating the DSM subsystem and all the 
 * DSM instances. No objects. Only Class Initialize and Class Terminate are
 * implemented.
 */

typedef ITS_ClassRec    DSM_InitClassRec;
typedef ITS_ClassRec*   DSM_InitClass;

#define DSM_INIT_CLASS_NAME "DSM Initialization Class"



/******************************************************************************
 ******************************************************************************
 **
 ** DSM Impl (implementation) class.
 **
 */

/*
 * One class per DSM implementation (e.g. DSM STUB). Defines the interface that
 * must be implemented by all DSM implementations. Follows philosophy of the
 * abstract factory design pattern. No objects. A DSM implementation is used
 * only through its DSM implementation class that is added as an ITS feature.
 */

/*
 * DSM implementation method definitions.
 */

typedef int (*DSM_ImplDataCreateInstanceProc)(
                        DSM_CoreObject* coreObj,
                        DSM_InstObject* instObj,
                        ITS_USHORT ftGroupId);


typedef int (*DSM_ImplDataDestroyInstanceProc)(
                        DSM_CoreObject* coreObj,
                        DSM_InstObject* instObj,
                        ITS_USHORT ftGroupId);

typedef int (*DSM_JoinFtGroupProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId);

typedef int (*DSM_LeaveFtGroupProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId);

typedef int (*DSM_SynchronizeDsmProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT msecs);

typedef void* (*DSM_AllocProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,
                        ITS_OCTET* key, 
                        ITS_UINT klen,
                        ITS_UINT size, 
                        int* error);

typedef void* (*DSM_FindProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,
                        ITS_OCTET* key, 
                        ITS_UINT klen,
                        int* error);

typedef int (*DSM_FreeProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,
                        ITS_OCTET* key, 
                        ITS_UINT klen,
                        void* object);

typedef int (*DSM_CommitProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,
                        ITS_OCTET* key, 
                        ITS_UINT klen,
                        void* object);

typedef int (*DSM_LockRowProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,
                        ITS_OCTET* key, 
                        ITS_UINT klen,
                        void* object);

typedef int (*DSM_UnlockRowProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,
                        ITS_OCTET* key, 
                        ITS_UINT klen,
                        void* object);

typedef int (*DSM_LockDsmProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId);

typedef int (*DSM_UnlockDsmProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId);

typedef int (*DSM_LockTableProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId, 
                        ITS_UINT tableId);

typedef int (*DSM_UnlockTableProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId, 
                        ITS_UINT tableId);

typedef void* (*DSM_AllocNoLockProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,
                        ITS_OCTET* key, 
                        ITS_UINT klen,
                        ITS_UINT size, 
                        int* error);

typedef void* (*DSM_FindNoLockProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,
                        ITS_OCTET* key, 
                        ITS_UINT klen,
                        int* error);

typedef int (*DSM_FreeNoLockProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,           
                        ITS_OCTET* key, 
                        ITS_UINT klen,
                        void* object);

typedef int (*DSM_CommitNoLockProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,
                        ITS_OCTET* key, 
                        ITS_UINT klen,
                        void* object);

typedef int (*DSM_LockRowNoLockProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        void* object);

typedef int (*DSM_UnlockRowNoLockProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        void* object);

typedef int (*DSM_TableIterateProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId, 
                        void* in, 
                        void* out,
                        DSM_IterateEntryProc iterateEntryFn);

typedef int (*DSM_TableDumpProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId, 
                        char** pStrDump,                            
                        DSM_DumpEntryProc dumpEntryFn);

typedef int (*DSM_TableGetSizeProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId, 
                        ITS_UINT* size);

typedef int (*DSM_MulticastEventToFtGroupMembersProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        const ITS_EVENT* event);

typedef int (*DSM_MulticastStackEventToFtGroupMembersProc)(
                        DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_EVENT event,
                        ITS_USHORT source,
                        ITS_USHORT destination);

/*
 * DSM Impl class definition.
 */

typedef struct
{
    const char*                             implName;
    DSM_ImplDataCreateInstanceProc          implDataCreateInstance;
    DSM_ImplDataDestroyInstanceProc         implDataDestroyInstance;
    DSM_JoinFtGroupProc                     joinFtGroup;
    DSM_LeaveFtGroupProc                    leaveFtGroup;
    DSM_SynchronizeDsmProc                  synchronizeDsm;
    DSM_AllocProc                           alloc;
    DSM_AllocProc                           allocLocal;
    DSM_FindProc                            find;
    DSM_FindProc                            findLocal;
    DSM_FreeProc                            free;
    DSM_FreeProc                            freeLocal;
    DSM_CommitProc                          commit;
    DSM_CommitProc                          commitLocal;
    DSM_LockRowProc                         lockRow;
    DSM_LockRowProc                         lockRowLocal;
    DSM_UnlockRowProc                       unlockRow;
    DSM_UnlockRowProc                       unlockRowLocal;
    DSM_LockDsmProc                         lockDsm;
    DSM_UnlockDsmProc                       unlockDsm;
    DSM_LockTableProc                       lockTable;
    DSM_LockTableProc                       lockTableLocal;
    DSM_UnlockTableProc                     unlockTable;
    DSM_UnlockTableProc                     unlockTableLocal;
    DSM_AllocNoLockProc                     allocNoLock;
    DSM_AllocNoLockProc                     allocNoLockLocal;
    DSM_FindNoLockProc                      findNoLock;
    DSM_FindNoLockProc                      findNoLockLocal;
    DSM_FreeNoLockProc                      freeNoLock;
    DSM_FreeNoLockProc                      freeNoLockLocal;
    DSM_CommitNoLockProc                    commitNoLock;
    DSM_CommitNoLockProc                    commitNoLockLocal;
    DSM_LockRowNoLockProc                   lockRowNoLock;
    DSM_LockRowNoLockProc                   lockRowNoLockLocal;
    DSM_UnlockRowNoLockProc                 unlockRowNoLock;
    DSM_UnlockRowNoLockProc                 unlockRowNoLockLocal;
    DSM_TableIterateProc                    tableIterate;
    DSM_TableDumpProc                       tableDump;
    DSM_TableGetSizeProc                    tableGetSize;
    DSM_MulticastEventToFtGroupMembersProc  multicastEventToFtGroupMembers;
    DSM_MulticastStackEventToFtGroupMembersProc  multicastStackEventToFtGroupMembers;
    DSM_TableIterateProc                    tableIterateLocal;
/*Itika changes start:Not used currently:Rel-BSC-2.5.5-Dt 5-Aug-10*/
    DSM_FindProc                            findBssapLocal;
    DSM_FreeProc                            freeBssapLocal;
    DSM_CommitProc                          commitBssapLocal;
    DSM_AllocProc                           allocBssapLocal;
/*Itika changes end*/
}
DSM_ImplClassPart;


typedef struct _DSM_ImplClassRec
{
    ITS_CoreClassPart   coreClass;
    DSM_ImplClassPart   dsmClass;
}
DSM_ImplClassRec;


#define DSM_IMPL_CLASS_IMPL_NAME(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.implName)

#define DSM_IMPL_CLASS_IMPL_DATA_CREATE_INSTANCE(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.implDataCreateInstance)

#define DSM_IMPL_CLASS_IMPL_DATA_DESTROY_INSTANCE(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.implDataDestroyInstance)

#define DSM_IMPL_CLASS_JOIN_FT_GROUP(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.joinFtGroup)

#define DSM_IMPL_CLASS_LEAVE_FT_GROUP(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.leaveFtGroup)

#define DSM_IMPL_CLASS_SYNCHRONIZE_DSM(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.synchronizeDsm)

#define DSM_IMPL_CLASS_ALLOC(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.alloc)

#define DSM_IMPL_CLASS_ALLOC_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.allocLocal)

#define DSM_IMPL_CLASS_FIND(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.find)


/*Itika changes Start*/
#define DSM_IMPL_CLASS_ALLOC_BSSAP_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.allocBssapLocal)

#define DSM_IMPL_CLASS_FIND_BSSAP_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.findBssapLocal)

#define DSM_IMPL_CLASS_FREE_BSSAP_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.freeBssapLocal)

#define DSM_IMPL_CLASS_COMMIT_BSSAP_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.commitBssapLocal)
/*Itika changes end*/
#define DSM_IMPL_CLASS_FIND_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.findLocal)

#define DSM_IMPL_CLASS_FREE(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.free)

#define DSM_IMPL_CLASS_FREE_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.freeLocal)

#define DSM_IMPL_CLASS_COMMIT(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.commit)

#define DSM_IMPL_CLASS_COMMIT_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.commitLocal)

#define DSM_IMPL_CLASS_LOCK_ROW(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.lockRow)

#define DSM_IMPL_CLASS_LOCK_ROW_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.lockRowLocal)

#define DSM_IMPL_CLASS_UNLOCK_ROW(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.unlockRow)

#define DSM_IMPL_CLASS_UNLOCK_ROW_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.unlockRowLocal)

#define DSM_IMPL_CLASS_LOCK_DSM(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.lockDsm)

#define DSM_IMPL_CLASS_UNLOCK_DSM(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.unlockDsm)

#define DSM_IMPL_CLASS_LOCK_TABLE(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.lockTable)

#define DSM_IMPL_CLASS_LOCK_TABLE_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.lockTableLocal)

#define DSM_IMPL_CLASS_UNLOCK_TABLE(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.unlockTable)

#define DSM_IMPL_CLASS_UNLOCK_TABLE_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.unlockTableLocal)

#define DSM_IMPL_CLASS_ALLOC_NO_LOCK(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.allocNoLock)

#define DSM_IMPL_CLASS_ALLOC_NO_LOCK_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.allocNoLockLocal)

#define DSM_IMPL_CLASS_FIND_NO_LOCK(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.findNoLock)

#define DSM_IMPL_CLASS_FIND_NO_LOCK_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.findNoLockLocal)

#define DSM_IMPL_CLASS_FREE_NO_LOCK(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.freeNoLock)

#define DSM_IMPL_CLASS_FREE_NO_LOCK_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.freeNoLockLocal)

#define DSM_IMPL_CLASS_COMMIT_NO_LOCK(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.commitNoLock)

#define DSM_IMPL_CLASS_COMMIT_NO_LOCK_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.commitNoLockLocal)

#define DSM_IMPL_CLASS_LOCK_ROW_NO_LOCK(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.lockRowNoLock)

#define DSM_IMPL_CLASS_LOCK_ROW_NO_LOCK_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.lockRowNoLockLocal)

#define DSM_IMPL_CLASS_UNLOCK_ROW_NO_LOCK(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.unlockRowNoLock)

#define DSM_IMPL_CLASS_UNLOCK_ROW_NO_LOCK_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.unlockRowNoLockLocal)

#define DSM_IMPL_CLASS_TABLE_ITERATE(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.tableIterate)

#define DSM_IMPL_CLASS_TABLE_ITERATE_LOCAL(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.tableIterateLocal)

#define DSM_IMPL_CLASS_TABLE_DUMP(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.tableDump)

#define DSM_IMPL_CLASS_TABLE_GET_SIZE(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.tableGetSize)

#define DSM_IMPL_CLASS_MULTICAST_EVENT_TO_FT_GROUP_MEMBERS(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.multicastEventToFtGroupMembers)

#define DSM_IMPL_CLASS_MULTICAST_STACK_EVENT_TO_FT_GROUP_MEMBERS(x) \
    (((DSM_ImplClassRec *)(x))->dsmClass.multicastStackEventToFtGroupMembers)

#define DSM_IMPL_CLASS_NAME "DSM Implementation Class"



/******************************************************************************
 ******************************************************************************
 **
 ** Class records.
 **
 */

ITSDLLAPI extern DSM_InstClassRec   itsDSM_InstClassRec;
ITSDLLAPI extern ITS_Class          itsDSM_InstClass;


ITSDLLAPI extern DSM_CoreClassRec   itsDSM_CoreClassRec;
ITSDLLAPI extern ITS_Class          itsDSM_CoreClass;


ITSDLLAPI extern DSM_InitClassRec   itsDSM_InitClassRec;
ITSDLLAPI extern ITS_Class          itsDSM_InitClass;



/******************************************************************************
 ******************************************************************************
 **
 ** DSMDLLAPI definition.
 **
 */

/*
 * DSM implemenatations are in separated DLLs, therefore this is required for
 * Windows. 
 */

#if defined(WIN32)

#if defined(DSM_IMPLEMENTATION)
#define DSMDLLAPI __declspec(dllexport)
#else /* !defined(DSM_IMPLEMENTATION) */
#define DSMDLLAPI __declspec(dllimport)
#endif /* defined(DSM_IMPLEMENTATION) */

#else /* !defined(WIN32) */

#define DSMDLLAPI

#endif /* defined(WIN32) */


/******************************************************************************
 ******************************************************************************
 **
 ** DSM STUB, GCS and SCI implementation class declarations.
 **
 */

DSMDLLAPI extern ITS_Class itsDSM_StubImplClass;
DSMDLLAPI extern ITS_Class itsDSM_GcsImplClass;
DSMDLLAPI extern ITS_Class itsDSM_SciImplClass;

DSMDLLAPI extern void
BroadCastEventNotificationCallback( ITS_POINTER object,
                                    ITS_POINTER userData,
                                    ITS_POINTER callData);


#if defined(__cplusplus)
}
#endif

#endif /* _ITS_DSM_H_ */


