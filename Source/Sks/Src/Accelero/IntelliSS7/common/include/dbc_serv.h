/****************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:00  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:43  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1  2004/09/15 05:33:17  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/07/18 14:24:38  ngoel
 * LOG: add define for man path
 * LOG:
 * LOG: Revision 6.4  2002/06/20 15:54:23  mmiers
 * LOG: Let SetDo initialize the proc array
 * LOG:
 * LOG: Revision 6.3  2002/06/18 20:55:38  mmiers
 * LOG: Add deregister API
 * LOG:
 * LOG: Revision 6.2  2002/06/18 19:28:12  mmiers
 * LOG: Update DBC console to be able to take more than one
 * LOG: command procedure
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:04  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2002/02/20 21:25:17  mmiers
 * LOG: Make the debug console class record extern to avoid common
 * LOG: block linkage (unreport) errors on unix.
 * LOG:
 * LOG: Revision 5.4  2001/11/20 21:45:04  mmiers
 * LOG: Debug the debug console.  The client retains some termination
 * LOG: problems.
 * LOG:
 * LOG: Revision 5.3  2001/11/20 17:42:01  mmiers
 * LOG: Finish DBC conversion.
 * LOG:
 * LOG: Revision 5.2  2001/11/19 23:49:31  mmiers
 * LOG: twiddling.
 * LOG:
 * LOG: Revision 5.1  2001/11/19 22:51:57  mmiers
 * LOG: Convert DBC server to C.
 * LOG:
 *
 ****************************************************************************/

#if !defined(_DBC_SERV_H_)
#define _DBC_SERV_H_

#ident "$Id: dbc_serv.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#define INTELLISS7_MAN_DIR_VAR       "ITS_MAN_PATH"

enum DBC_EventTypes
{
    DBC_MORE_EVT,
    DBC_LAST_EVT,
    DBC_QUIT_EVT,
    DBC_HELP_EVT
};

/*
 * disable template warnings by having this first.
 */
#include <its.h>
#include <its_hash.h>
#include <its_transports.h>
#include <its_worker.h>
#include <its_mutex.h>
#include <its_lockable.h>

/*
 * hash table contents
 */
typedef struct _dbc_command
{
    struct _dbc_command *next;
    char                *command;
    char                *fullCommand;
    char                *argUsage;
    char                *fullArgUsage;
}
DBC_Command;

/*
 * the object part
 */
typedef struct
{
    char            *name;
    char            *currentCommand;
    char            *buffer;
    void            *back;
    unsigned        bsize;
    unsigned        curOffset;
    ITS_BOOLEAN     commandPartialResult;
    ITS_BOOLEAN     buildingMap;
    ITS_BOOLEAN     cmdFailed;
    HASH_Table      CommandMap;
}
DBC_ServerPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    DBC_ServerPart      dbc;
}
DBC_Server;

#define DBC_NAME(x) \
    (((DBC_Server *)(x))->dbc.name)

#define DBC_CUR_CMD(x) \
    (((DBC_Server *)(x))->dbc.currentCommand)

#define DBC_BUFFER(x) \
    (((DBC_Server *)(x))->dbc.buffer)

#define DBC_BACK(x) \
    (((DBC_Server *)(x))->dbc.back)

#define DBC_BSIZE(x) \
    (((DBC_Server *)(x))->dbc.bsize)

#define DBC_CUR_OFFSET(x) \
    (((DBC_Server *)(x))->dbc.curOffset)

#define DBC_PARTIAL_RESULT(x) \
    (((DBC_Server *)(x))->dbc.commandPartialResult)

#define DBC_BUILDING_MAP(x) \
    (((DBC_Server *)(x))->dbc.buildingMap)

#define DBC_CMD_FAILED(x) \
    (((DBC_Server *)(x))->dbc.cmdFailed)

#define DBC_CMD_MAP(x) \
    (((DBC_Server *)(x))->dbc.CommandMap)

#define DBC_GATE(x) \
    (((DBC_Server *)(x))->dbc.gate)

/*
 * class procs
 */
typedef void    (*DBC_CommandProc)(DBC_Server *dbc, const char *cmdLine);

/*
 * class record.
 */
typedef struct
{
    DBC_CommandProc *doCommand;
    ITS_UINT        numCommands;
    ITS_UINT        maxCommands;
}
DBC_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    LOCKABLE_ClassPart  lockableClass;
    DBC_ClassPart       dbcClass;
}
DBC_ClassRec, *DBC_Class;

#define DBC_CLASS_DO_COMMAND(x) \
    (((DBC_ClassRec *)(x))->dbcClass.doCommand)

#define DBC_CLASS_NUM_COMMANDS(x) \
    (((DBC_ClassRec *)(x))->dbcClass.numCommands)

#define DBC_CLASS_MAX_COMMANDS(x) \
    (((DBC_ClassRec *)(x))->dbcClass.maxCommands)

#define DBC_CLASS_NAME  "DBC Server Class"

/*
 * The API
 */
#if defined(__cplusplus)
extern "C"
{
#endif

ITSDLLAPI DBC_Server  *DBC_ServerCreate(const char *name, WORKER_Control *worker);
ITSDLLAPI void        DBC_ServerDestroy(DBC_Server *dbc);
ITSDLLAPI ITS_BOOLEAN DBC_Cmd(DBC_Server *dbc,
                              const char *command, const char *fullCommand,
                              const char *argUsage, const char *detailedArgUsage);
ITSDLLAPI int         DBC_SetDoCommand(DBC_CommandProc proc);
ITSDLLAPI int         DBC_AddDoCommand(DBC_CommandProc proc);
ITSDLLAPI void        DBC_RemDoCommand(DBC_CommandProc proc);
ITSDLLAPI void        DBC_ProcessCommandsLoop(DBC_Server *dbc,
                                              ITS_USHORT instance);
ITSDLLAPI void        DBC_ExecuteCommand(DBC_Server *dbc,
                                         ITS_USHORT instance,
                                         const char *cmdLine);
ITSDLLAPI void        DBC_SendCommandResult(DBC_Server *dbc,
                                            ITS_USHORT instance);
ITSDLLAPI void        DBC_SendCommandPartialResult(DBC_Server *dbc,
                                                   ITS_USHORT instance);
ITSDLLAPI void        DBC_SendCommandFinalResult(DBC_Server *dbc,
                                                 ITS_USHORT instance);
ITSDLLAPI void        DBC_CommandSetPartialResult(DBC_Server *dbc);
ITSDLLAPI void        DBC_UnsetCommandPartialResult(DBC_Server *dbc);
ITSDLLAPI ITS_BOOLEAN DBC_IsCommandPartialResult(DBC_Server *dbc);
ITSDLLAPI void        DBC_Lock(DBC_Server *dbc);
ITSDLLAPI void        DBC_Unlock(DBC_Server *dbc);
ITSDLLAPI void        DBC_AppendText(DBC_Server *dbc, const char *txt);
ITSDLLAPI void        DBC_SetCmdFailed(DBC_Server *dbc);

/*
 * class records
 */
ITSDLLAPI extern DBC_ClassRec  itsDBC_ServerClassRec;
ITSDLLAPI extern ITS_Class     itsDBC_ServerClass;

/*
 * optional glue to the engine.
 */
ITSDLLAPI extern int (*DBC_Commit)(char *, char **);

#if defined(__cplusplus)
}
#endif

#endif /* _DBC_SERV_H_ */
