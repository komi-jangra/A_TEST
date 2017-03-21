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
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:23  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:07  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:51:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1  2004/09/15 05:35:49  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.12  2002/07/25 18:22:42  ngoel
 * LOG: add fclose for each fopen
 * LOG:
 * LOG: Revision 6.11  2002/07/18 14:29:50  ngoel
 * LOG: add help command
 * LOG:
 * LOG: Revision 6.10  2002/07/10 21:10:29  mmiers
 * LOG: Reformat command output
 * LOG:
 * LOG: Revision 6.9  2002/06/20 15:54:23  mmiers
 * LOG: Let SetDo initialize the proc array
 * LOG:
 * LOG: Revision 6.8  2002/06/18 20:55:38  mmiers
 * LOG: Add deregister API
 * LOG:
 * LOG: Revision 6.7  2002/06/18 19:41:12  mmiers
 * LOG: Merge error
 * LOG:
 * LOG: Revision 6.6  2002/06/18 19:31:08  mmiers
 * LOG: Update DBC to take more than one command proc
 * LOG:
 * LOG: Revision 6.5  2002/06/18 19:29:56  mmiers
 * LOG: Update DBC to take more than one command proc
 * LOG:
 * LOG: Revision 6.4  2002/06/18 19:28:12  mmiers
 * LOG: Update DBC console to be able to take more than one
 * LOG: command procedure
 * LOG:
 * LOG: Revision 6.3  2002/05/07 16:19:58  mmiers
 * LOG: Update hash, add test
 * LOG:
 * LOG: Revision 6.2  2002/04/12 18:35:29  hdivoux
 * LOG: Remove C++ comment.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.8  2002/01/10 16:51:35  mmiers
 * LOG: Finish the transport refcounting effort.  Move vframe from
 * LOG: vendors to here.
 * LOG:
 * LOG: Revision 5.7  2001/12/19 18:02:32  mmiers
 * LOG: ADAX testing on Solaris revealed several build flaws.
 * LOG:
 * LOG: Revision 5.6  2001/11/21 21:51:30  hdivoux
 * LOG: Change for iterate hashtable function name.
 * LOG:
 * LOG: Revision 5.5  2001/11/20 23:39:23  mmiers
 * LOG: Make sure the command buffer exists.
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

#include <dbc_serv.h>

#include <its_assertion.h>

#ident "$Id: dbc_serv.c,v 1.2 2007-12-05 04:11:17 bsccs2 Exp $"

#define DBC_MIN_COMMANDS    8

#if defined(_WIN32)
#define HLP_FILE_MODE   "rt"
#else
#define HLP_FILE_MODE   "r"
#endif

static char *manPath = NULL;

ITSDLLAPI int (*DBC_Commit)(char *, char **) = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create the DBC class object.
 *
 *  Input Parameters:
 *      objClass - class to init
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
 ****************************************************************************/
static int
ClassInit(ITS_Class objClass)
{
    if (DBC_CLASS_DO_COMMAND(objClass) == NULL)
    {
        DBC_CLASS_NUM_COMMANDS(objClass) = 1;
        DBC_CLASS_MAX_COMMANDS(objClass) = DBC_MIN_COMMANDS;

        DBC_CLASS_DO_COMMAND(objClass) =
            (DBC_CommandProc *)calloc(DBC_MIN_COMMANDS,
                                      sizeof(DBC_CommandProc));

        if (DBC_CLASS_DO_COMMAND(objClass) == NULL)
        {
            return (ITS_ENOMEM);
        }
    }

     manPath = getenv(INTELLISS7_MAN_DIR_VAR);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create the DBC class object.
 *
 *  Input Parameters:
 *      objClass - class to init
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
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
    if (DBC_CLASS_DO_COMMAND(objClass))
    {
        free(DBC_CLASS_DO_COMMAND(objClass));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create the DBC server object.
 *
 *  Input Parameters:
 *      name - server name
 *      worker - worker to attach to.
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
 ****************************************************************************/
static int
CreateServer(ITS_Object obj, va_list args)
{
    DBC_Server *serv = (DBC_Server *)obj;
    char *name;
    void *back;

    if (LOCKABLE_GetShared((LOCKABLE_Class)ITS_OBJ_CLASS(obj)))
    {
        return (ITS_EINUSE);
    }

    name = va_arg(args, char *);
    back = va_arg(args, void *);

    ITS_C_ASSERT(name != NULL);

    DBC_NAME(serv) = strdup(name);
    DBC_BACK(serv) = back;

    DBC_CUR_CMD(serv) = malloc(ITS_PATH_MAX);
    ITS_C_ASSERT(DBC_CUR_CMD(serv) != NULL);

    DBC_PARTIAL_RESULT(serv) = ITS_FALSE;
    DBC_BUILDING_MAP(serv) = ITS_TRUE;
    DBC_CMD_FAILED(serv) = ITS_FALSE;

    if ((DBC_CMD_MAP(serv) = HASH_CreateTable()) == NULL)
    {
        free(DBC_NAME(serv));
        free(DBC_CUR_CMD(serv));

        return (ITS_ENOMEM);
    }

    LOCKABLE_SHARED_INSTANCE(itsDBC_ServerClass) = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a DBC command.
 *
 *  Input Parameters:
 *      cmd - the command to print
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
 ****************************************************************************/
static int
DeleteCmd(ITS_INT ctxt, ITS_POINTER ent,
          void *in, void *out)
{
    DBC_Command *cmd = (DBC_Command *)ent;

    free(cmd->fullArgUsage);
    free(cmd->argUsage);
    free(cmd->fullCommand);
    free(cmd->command);
    free(cmd);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the DBC server object.
 *
 *  Input Parameters:
 *      obj - the server to destroy
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
 ****************************************************************************/
static void
DestroyServer(ITS_Object obj)
{
    DBC_Server *serv = (DBC_Server *)obj;

    HASH_VTableIterate(DBC_CMD_MAP(serv), 0, NULL, NULL, DeleteCmd);

    if (DBC_BUFFER(serv))
    {
        ITS_Free(DBC_BUFFER(serv));
    }

    free(DBC_NAME(serv));
    free(DBC_CUR_CMD(serv));

    HASH_DeleteTable(DBC_CMD_MAP(serv));
}

ITSDLLAPI DBC_ClassRec itsDBC_ServerClassRec =
{
    /* core */
    {
        (ITS_Class)&itsLOCKABLE_ClassRec,/* superclass */
        sizeof(DBC_Server),             /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        DBC_CLASS_NAME,                 /* class name */
        ClassInit,                      /* class init */
        ClassDestroy,                   /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        CreateServer,                   /* instantiate */
        DestroyServer,                  /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ITS_INST_EQUALS_INHERIT,        /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    },
    /* lockable */
    {
        LOCKABLE_INHERIT,
        LOCKABLE_INHERIT,
        LOCKABLE_INHERIT,
        { 0 },
        NULL
    },
    /* dbc */
    {
        NULL
    }
};

ITSDLLAPI ITS_Class itsDBC_ServerClass = (ITS_Class)&itsDBC_ServerClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create the DBC server object.
 *
 *  Input Parameters:
 *      name - server name
 *      worker - worker to attach to.
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
 ****************************************************************************/
ITSDLLAPI DBC_Server *
DBC_ServerCreate(const char *name, WORKER_Control *worker)
{
    return (DBC_Server *)ITS_ConstructObject(itsDBC_ServerClass,
                                             name, worker, NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Destroy the DBC server object.
 *
 *  Input Parameters:
 *      obj - the DBC to destroy
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
 ****************************************************************************/
ITSDLLAPI void
DBC_ServerDestroy(DBC_Server *dbc)
{
    ITS_DestructObject((ITS_Object)dbc);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Reset the text field.
 *
 *  Input Parameters:
 *      dbc - the server to reset
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
 ****************************************************************************/
static void
ResetText(DBC_Server *dbc)
{
    if (DBC_BUFFER(dbc))
    {
        DBC_BUFFER(dbc)[0] = 0;
    }

    DBC_CUR_OFFSET(dbc) = 0;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a DBC command.
 *
 *  Input Parameters:
 *      buf - the buffer to print into
 *      cmd - the command to print
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
 ****************************************************************************/
static int
PrintCmd(ITS_INT ctxt, ITS_POINTER ent,
         void *in, void *out)
{
    char buf[ITS_PATH_MAX<<1];
    DBC_Server *dbc = (DBC_Server *)in;
    DBC_Command *cmd = (DBC_Command *)ent;

    sprintf(buf, " %-20.20s   %-s\n", cmd->command, cmd->argUsage);
    DBC_AppendText(dbc, buf);

    sprintf(buf, " %-20.20s     %-s\n", " ", cmd->fullCommand);
    DBC_AppendText(dbc, buf);

    if (cmd->fullArgUsage)
    {
        sprintf(buf, " %-20.20s      %-s\n", " ", cmd->fullArgUsage);
        DBC_AppendText(dbc, buf);
    }

    DBC_AppendText(dbc, "\n");

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Send an empty response.
 *
 *  Input Parameters:
 *      dbc - this server
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
 *      Not thread safe but called only from a thread safe member function.
 *
 *  See Also:
 ****************************************************************************/
static void
Empty(ITS_USHORT instance)
{
    ITS_EVENT event;
    int res;

    ITS_EVENT_INIT(&event, DBC_LAST_EVT, 1);
    event.data[0] = 0;

    res = TRANSPORT_PutEvent(instance, &event);

    ITS_C_ASSERT(res == ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Send a usage response.
 *
 *  Input Parameters:
 *      dbc - this server
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
 *      Not thread safe but called only from a thread safe member function.
 *
 *  See Also:
 ****************************************************************************/
static void
Usage(DBC_Server *dbc, ITS_USHORT instance)
{
    char buf[ITS_PATH_MAX];

    sprintf(buf, "------------ Available Commands [ %s", DBC_NAME(dbc));
    DBC_AppendText(dbc, buf);
    sprintf(buf, " ] ------------\n\n");
    DBC_AppendText(dbc, buf);

    HASH_VTableIterate(DBC_CMD_MAP(dbc), 0, dbc, NULL, PrintCmd);

    sprintf(buf,
            " quit                     Exit Debug Console\n");
    DBC_AppendText(dbc, buf);

    DBC_SendCommandResult(dbc, instance);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Send a quit response.
 *
 *  Input Parameters:
 *      dbc - this server
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
 *      Not thread safe but called only from a thread safe member function.
 *
 *  See Also:
 ****************************************************************************/
static void
Quit(ITS_USHORT instance)
{
    ITS_EVENT event;
    int res;

    ITS_EVENT_INIT(&event, DBC_QUIT_EVT, 0);

    res = TRANSPORT_PutEvent(instance, &event);

    ITS_C_ASSERT(res == ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
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
 ****************************************************************************/
static void
DumpFile(DBC_Server *dbc, const char *name)
{
    FILE *output;
    char buf[MAX_LINE_LENGTH];

    output = fopen(name, HLP_FILE_MODE);

    if (output == NULL)
    {
        sprintf(buf, "No help available or ITS_MAN_PATH not set correctly\n");
        DBC_AppendText(dbc, buf);
        return;
    }

    while(fgets(buf, MAX_LINE_LENGTH, output) != NULL)
    {
        DBC_AppendText(dbc, buf);
    }

    fclose(output);

    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
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
 ****************************************************************************/
static void
MMLHelp(DBC_Server *dbc, const char *commandLine)
{
    char buf[ITS_PATH_MAX];
    char cmd[ITS_PATH_MAX];
    char fname[ITS_PATH_MAX];
    int ret;

    ret = sscanf(commandLine, "%s %s", buf, cmd);
    if(ret != 2 && ret != 1)
    {
        return;
    }

    
    if (manPath == NULL)
    {
         sprintf(buf, "Set ITS_MAN_PATH env variable to see help\n");
         DBC_AppendText(dbc, buf);
         return;
    }

    strcpy(fname, manPath);

    if (ret == 2)
    {
        strcat(fname, cmd);
        strcat(fname, ".hlp");
    }
    else
    {
        strcat(fname, "help");
        strcat(fname, ".hlp");
    }


    DumpFile(dbc, fname);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Process a command line.
 *
 *  Input Parameters:
 *      dbc - this server
 *      cmdLine - the command line to process
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
 *      Not thread safe but called only from a thread safe member function.
 *
 *  See Also:
 ****************************************************************************/
static void
InternalExecuteCommand(DBC_Server *dbc, ITS_USHORT instance,
                       const char *commandLine)
{
    int ret;
    ITS_INT hash;
    DBC_Command *cmd;
    char buf[ITS_PATH_MAX];

    /* reset the response buffer */
    ResetText(dbc);

    /* Make sure first word is empty */
    DBC_CUR_CMD(dbc)[0] = 0;

    /* Reset commandPartialResult boolean. */
    DBC_PARTIAL_RESULT(dbc) = ITS_FALSE;
    DBC_CMD_FAILED(dbc) = ITS_FALSE;

    /* Read first word (command). */
    ret = sscanf(commandLine, "%s", DBC_CUR_CMD(dbc));

    if (ret <= 0)
    {
        return;
    }

    switch (DBC_CUR_CMD(dbc)[0])
    {
    case '#':           /* Comment.    */
    case '\0':          /* Empty line. */
	case '\n':
        Empty(instance);
        break;

    case '?':
        Usage(dbc, instance);
        break;

    default:
        /* Special case for quit command. */
        if (strcmp(DBC_CUR_CMD(dbc), "quit") == 0 ||
            strcmp(DBC_CUR_CMD(dbc), "q") == 0)
        {
            Quit(instance);

            break;
        }

        /* Special case for help command. */
        if (strcmp(DBC_CUR_CMD(dbc), "help") == 0)
        {
            MMLHelp(dbc, commandLine);
            DBC_SendCommandResult(dbc, instance);

            break;
        }
        else if ((strcmp(DBC_CUR_CMD(dbc), "commit") == 0) ||
                 (strcmp(DBC_CUR_CMD(dbc), "COMMIT") == 0))
        {
            char filename[ITS_PATH_MAX];
            char buf[ITS_PATH_MAX*2];
            char* bakfile = NULL;

            memset(filename,0,ITS_PATH_MAX);
            sscanf(commandLine, "%s %s", buf, filename);

            if (DBC_Commit == NULL)
            {
                DBC_AppendText(dbc, "\nCommit procedure unavailable.\n");
            }
            else if (!(*DBC_Commit)(filename, &bakfile))
            {
                DBC_AppendText(dbc, "\nCommit Success\n");
                sprintf(buf,"Commit is performed on %s\n",filename);
                DBC_AppendText(dbc, buf);

                if (bakfile)
                {
                    sprintf(buf,
                            "The old contents are written "
                            "in the backup file %s\n",bakfile);
                    DBC_AppendText(dbc, buf);
                }
            }
            else
            {
                DBC_AppendText(dbc, "\nCommit failed \n");
                DBC_AppendText(dbc, "**** Invalid Command Arguments *******\n");
                DBC_AppendText(dbc, "Usage: commit <filename>\n");
            }

            if (bakfile)
            {
                free(bakfile);
            }

            DBC_SendCommandResult(dbc, instance);
            break;
        }

        /* Look up command. */
        cmd = NULL;
        hash = HASH_MakeKey(DBC_CUR_CMD(dbc), strlen(DBC_CUR_CMD(dbc)));
        if ((ret = HASH_FindEntry(DBC_CMD_MAP(dbc), 0, hash,
                                  (ITS_POINTER *)&cmd)) == ITS_SUCCESS)
        {
            while (cmd != NULL &&
                   strcmp(cmd->command, DBC_CUR_CMD(dbc)) != 0)
            {
                cmd = cmd->next;
            }
        }

        /* If command valid, run it. */
        if (ret == ITS_SUCCESS && cmd != NULL)
        {
            ITS_UINT i;

            ResetText(dbc);

            for (i = 0; i < DBC_CLASS_NUM_COMMANDS(ITS_OBJ_CLASS(dbc)); i++)
            {
                if (DBC_CLASS_DO_COMMAND(ITS_OBJ_CLASS(dbc))[i])
                {
                    DBC_CLASS_DO_COMMAND(ITS_OBJ_CLASS(dbc))[i](dbc, commandLine);
                }
            }

            if (!DBC_CMD_FAILED(dbc))
            {
                if (DBC_PARTIAL_RESULT(dbc))
                {
                    DBC_SendCommandPartialResult(dbc, instance);
                }
                else
                {
                    DBC_SendCommandResult(dbc, instance);
                }
            }
            else
            {
                sprintf(buf, "Usage:\n%s\n\n", cmd->fullArgUsage);
                DBC_AppendText(dbc, buf);

                DBC_SendCommandResult(dbc, instance);
            }
        }
        else
        {
            sprintf(buf, "Command %s not found.\n", DBC_CUR_CMD(dbc));
            DBC_AppendText(dbc, buf);

            DBC_SendCommandResult(dbc, instance);
        }

        break;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Send a command result.
 *
 *  Input Parameters:
 *      dbc - this server
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
 ****************************************************************************/
static void
InternalSendCommandResult(DBC_Server *dbc,
                          ITS_USHORT instance, ITS_BOOLEAN partial)
{
    int quotient, remainder, res, i;
    ITS_EVENT event;

    DBC_Lock(dbc);

    if (DBC_BUFFER(dbc) == NULL)
    {
        DBC_AppendText(dbc, "");
    }

    quotient = (strlen(DBC_BUFFER(dbc)) + 1) / ITS_MAX_EVENT_SIZE;
    remainder = (strlen(DBC_BUFFER(dbc)) + 1) % ITS_MAX_EVENT_SIZE;

    if (quotient == 0)
    {
        int length =  strlen(DBC_BUFFER(dbc)) + 1;

        ITS_EVENT_INIT(&event,
                       partial ? DBC_MORE_EVT : DBC_LAST_EVT,
                       length);

        memcpy(event.data, DBC_BUFFER(dbc), length);

        res = TRANSPORT_PutEvent(instance, &event);

        ITS_C_ASSERT(res == ITS_SUCCESS);
    }
    else
    {
        char* ptr = DBC_BUFFER(dbc);

        for (i = 0; i < quotient; i++)
        {
            int length = ITS_MAX_EVENT_SIZE;

            ITS_EVENT_INIT(&event, DBC_MORE_EVT, length);

            memcpy(event.data, (ITS_OCTET *)ptr, length);

            res = TRANSPORT_PutEvent(instance, &event);

            ITS_C_ASSERT(res == ITS_SUCCESS);

            ptr += ITS_MAX_EVENT_SIZE;
        }

        if (remainder != 0)
        {
            int length = remainder;

            ITS_EVENT_INIT(&event,
                           partial ? DBC_MORE_EVT : DBC_LAST_EVT,
                           length);

            memcpy(event.data, (unsigned char*)ptr, length);

            res = TRANSPORT_PutEvent(instance, &event);

            ITS_C_ASSERT(res == ITS_SUCCESS);
        }
        else
        {
            ITS_EVENT_INIT(&event,
                           partial ? DBC_MORE_EVT : DBC_LAST_EVT,
                           1);

            event.data[0] = 0;

            res = TRANSPORT_PutEvent(instance, &event);

            ITS_C_ASSERT(res == ITS_SUCCESS);
        }
    }

    DBC_Unlock(dbc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Lock the server.
 *
 *  Input Parameters:
 *      dbc - this server
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
 ****************************************************************************/
ITSDLLAPI void
DBC_Lock(DBC_Server *dbc)
{
    int ret;

    ret = LOCKABLE_Lock((LOCKABLE_Class)ITS_OBJ_CLASS(dbc));

    ITS_C_ASSERT(ret == ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Lock the server.
 *
 *  Input Parameters:
 *      dbc - this server
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
 ****************************************************************************/
ITSDLLAPI void
DBC_Unlock(DBC_Server *dbc)
{
    int ret;

    ret = LOCKABLE_Unlock((LOCKABLE_Class)ITS_OBJ_CLASS(dbc));

    ITS_C_ASSERT(ret == ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the command procedure.
 *
 *  Input Parameters:
 *      proc - the command procedure to set
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
 *      Not thread safe.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
DBC_SetDoCommand(DBC_CommandProc proc)
{
    if (DBC_CLASS_DO_COMMAND(itsDBC_ServerClass) == NULL)
    {
        /* we're being called before the instance is created.  We
         * can deal with that, but the user had better not screw up */
        DBC_CLASS_NUM_COMMANDS(itsDBC_ServerClass) = 1;
        DBC_CLASS_MAX_COMMANDS(itsDBC_ServerClass) = DBC_MIN_COMMANDS;

        DBC_CLASS_DO_COMMAND(itsDBC_ServerClass) =
            (DBC_CommandProc *)calloc(DBC_MIN_COMMANDS,
                                      sizeof(DBC_CommandProc));

        if (DBC_CLASS_DO_COMMAND(itsDBC_ServerClass) == NULL)
        {
            return (ITS_ENOMEM);
        }
    }

    DBC_CLASS_DO_COMMAND(itsDBC_ServerClass)[0] = proc;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a command proc.
 *
 *  Input Parameters:
 *      proc - the command procedure to add
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
 *      Thread safe.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
DBC_AddDoCommand(DBC_CommandProc proc)
{
    int ret;

    ret = LOCKABLE_Lock((LOCKABLE_Class)itsDBC_ServerClass);
    if (ret != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    DBC_CLASS_NUM_COMMANDS(itsDBC_ServerClass)++;
    if (DBC_CLASS_NUM_COMMANDS(itsDBC_ServerClass) >
        DBC_CLASS_MAX_COMMANDS(itsDBC_ServerClass))
    {
        DBC_CLASS_MAX_COMMANDS(itsDBC_ServerClass) *= 2;
        DBC_CLASS_DO_COMMAND(itsDBC_ServerClass) =
            (DBC_CommandProc *)realloc(DBC_CLASS_DO_COMMAND(itsDBC_ServerClass),
                                       DBC_CLASS_MAX_COMMANDS(itsDBC_ServerClass) *
                                        sizeof(DBC_CommandProc));

        if (DBC_CLASS_DO_COMMAND(itsDBC_ServerClass) == NULL)
        {
            DBC_CLASS_NUM_COMMANDS(itsDBC_ServerClass)--;

            LOCKABLE_Unlock((LOCKABLE_Class)itsDBC_ServerClass);

            return (ITS_ENOMEM);
        }
    }

    DBC_CLASS_DO_COMMAND(itsDBC_ServerClass)
        [DBC_CLASS_NUM_COMMANDS(itsDBC_ServerClass) - 1] = proc;

    LOCKABLE_Unlock((LOCKABLE_Class)itsDBC_ServerClass);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Remove a command proc.
 *
 *  Input Parameters:
 *      proc - the command procedure to remove
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
 *      Thread safe.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
DBC_RemDoCommand(DBC_CommandProc proc)
{
    int ret;
    ITS_UINT i;

    ret = LOCKABLE_Lock((LOCKABLE_Class)itsDBC_ServerClass);
    if (ret != ITS_SUCCESS)
    {
        return;
    }

    for (i = 0; i < DBC_CLASS_NUM_COMMANDS(itsDBC_ServerClass); i++)
    {
        if (DBC_CLASS_DO_COMMAND(itsDBC_ServerClass)[i] == proc)
        {
            if (i < DBC_CLASS_NUM_COMMANDS(itsDBC_ServerClass) - 1)
            {
                memmove(&DBC_CLASS_DO_COMMAND(itsDBC_ServerClass)[i],
                        &DBC_CLASS_DO_COMMAND(itsDBC_ServerClass)[i+1],
                        (DBC_CLASS_NUM_COMMANDS(itsDBC_ServerClass) - i - 1) *
                            sizeof(DBC_CommandProc));
            }

            DBC_CLASS_NUM_COMMANDS(itsDBC_ServerClass)--;

            break;
        }
    }

    LOCKABLE_Unlock((LOCKABLE_Class)itsDBC_ServerClass);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Append text to the dbc.
 *
 *  Input Parameters:
 *      buf - the buffer to print into
 *      txt - the text to append
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
 ****************************************************************************/
ITSDLLAPI void
DBC_AppendText(DBC_Server *dbc, const char *txt)
{
    unsigned co, bs;

    if (!DBC_BUFFER(dbc))
    {
        DBC_BUFFER(dbc) = ITS_Malloc(ITS_MAX_EVENT_SIZE);
        DBC_BUFFER(dbc)[0] = 0;

        DBC_BSIZE(dbc) = ITS_MAX_EVENT_SIZE;
        DBC_CUR_OFFSET(dbc) = 0;

        ITS_C_ASSERT(DBC_BUFFER(dbc) != NULL);
    }

    co = DBC_CUR_OFFSET(dbc) + strlen(txt) + 1;
    bs = DBC_BSIZE(dbc);
    while (DBC_CUR_OFFSET(dbc) + strlen(txt) + 1 > DBC_BSIZE(dbc))
    {
        DBC_BUFFER(dbc) = ITS_Realloc(DBC_BUFFER(dbc),
                                      DBC_BSIZE(dbc) + ITS_MAX_EVENT_SIZE);

        ITS_C_ASSERT(DBC_BUFFER(dbc) != NULL);

        DBC_BSIZE(dbc) += ITS_MAX_EVENT_SIZE;

        co = DBC_CUR_OFFSET(dbc) + strlen(txt) + 1;
        bs = DBC_BSIZE(dbc);
    }

    strcat(DBC_BUFFER(dbc), txt);
    DBC_CUR_OFFSET(dbc) += strlen(txt) + 1;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Process a command line.
 *
 *  Input Parameters:
 *      dbc - this server
 *      cmdLine - the command line to process
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
 ****************************************************************************/
ITSDLLAPI void
DBC_ExecuteCommand(DBC_Server *dbc, ITS_USHORT instance,
                   const char *commandLine)
{
    DBC_Lock(dbc);

    /* Build command map if required. */
    if (DBC_BUILDING_MAP(dbc))
    {
        ITS_UINT i;

        for (i = 0; i < DBC_CLASS_NUM_COMMANDS(ITS_OBJ_CLASS(dbc)); i++)
        {
            if (DBC_CLASS_DO_COMMAND(ITS_OBJ_CLASS(dbc))[i])
            {
                DBC_CLASS_DO_COMMAND(ITS_OBJ_CLASS(dbc))[i](dbc, "");
            }
        }

        DBC_BUILDING_MAP(dbc) = ITS_FALSE;
    }

    InternalExecuteCommand(dbc, instance, commandLine);

    DBC_Unlock(dbc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Process a command.
 *
 *  Input Parameters:
 *      dbc - this server
 *      cmdLine - the command line to process
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
 *      This is "clever" code.  Eeww.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
DBC_Cmd(DBC_Server *dbc,
        const char *command, const char *fullCommand,
        const char *argumentUsage, const char *detailedArgumentUsage)
{
    ITS_INT hash;
    DBC_Command *cmd, *tmp;
    int ret;

    if (DBC_BUILDING_MAP(dbc))
    {
        cmd = NULL;
        tmp = NULL;
        hash = HASH_MakeKey(command, strlen(command));
        if ((ret = HASH_FindEntry(DBC_CMD_MAP(dbc), 0, hash,
                                  (ITS_POINTER *)&cmd)) == ITS_SUCCESS)
        {
            tmp = cmd;
            while (cmd != NULL &&
                   strcmp(cmd->command, DBC_CUR_CMD(dbc)) != 0)
            {
                cmd = cmd->next;
            }
        }

        if (ret == ITS_SUCCESS && cmd != NULL)
        {
            /* the old code wasn't really doing anything */
            return (ITS_FALSE);
        }

        /* Register command. */
        if ((cmd = malloc(sizeof(DBC_Command))) == NULL)
        {
            return (ITS_FALSE);
        }

        /* allocate strings */
        if ((cmd->command = strdup(command)) == NULL)
        {
            free(cmd);

            return (ITS_FALSE);
        }
        if ((cmd->fullCommand = strdup(fullCommand)) == NULL)
        {
            free(cmd->command);
            free(cmd);

            return (ITS_FALSE);
        }
        if ((cmd->argUsage = strdup(argumentUsage)) == NULL)
        {
            free(cmd->fullCommand);
            free(cmd->command);
            free(cmd);

            return (ITS_FALSE);
        }
        if ((cmd->fullArgUsage = strdup(detailedArgumentUsage)) == NULL)
        {
            free(cmd->argUsage);
            free(cmd->fullCommand);
            free(cmd->command);
            free(cmd);

            return (ITS_FALSE);
        }

        /* link pointers */
        cmd->next = tmp;

        /* update entry (or add if not already present */
        if (HASH_AddEntry(DBC_CMD_MAP(dbc), 0, hash,
                          (ITS_POINTER)cmd) != ITS_SUCCESS)
        {
            free(cmd->fullArgUsage);
            free(cmd->argUsage);
            free(cmd->fullCommand);
            free(cmd->command);
            free(cmd);

            return (ITS_FALSE);
        }

        return (ITS_FALSE);
    }
    else
    {
        return strcmp(DBC_CUR_CMD(dbc), command) == 0
                        ? ITS_TRUE
                        : ITS_FALSE;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a command result.
 *
 *  Input Parameters:
 *      dbc - this server
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
 *      Thread safe.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
DBC_SendCommandResult(DBC_Server *dbc, ITS_USHORT instance)
{
    DBC_Lock(dbc);

    InternalSendCommandResult(dbc, instance, ITS_FALSE);

    DBC_Unlock(dbc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a partial command result.
 *
 *  Input Parameters:
 *      dbc - this server
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
 *      Thread safe.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
DBC_SendCommandPartialResult(DBC_Server *dbc, ITS_USHORT instance)
{
    DBC_Lock(dbc);

    InternalSendCommandResult(dbc, instance, ITS_TRUE);

    DBC_Unlock(dbc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a final command result.
 *
 *  Input Parameters:
 *      dbc - this server
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
 *      Thread safe.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
DBC_SendCommandFinalResult(DBC_Server *dbc, ITS_USHORT instance)
{
    DBC_SendCommandResult(dbc, instance);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Process commands.
 *
 *  Input Parameters:
 *      dbc - this server
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
 *      Thread safe.
 *
 *  See Also:
 ****************************************************************************/
ITS_USHORT SCM_instance =NULL;

ITSDLLAPI void
DBC_ProcessCommandsLoop(DBC_Server *dbc, ITS_USHORT instance)
{
    int res = ITS_SUCCESS;
    ITS_EVENT event;
    TRANSPORT_Control *tr;

    ITS_EVENT_INIT(&event, 0, 0);
    	
    tr = TRANSPORT_FindTransport(instance);
    SCM_instance = instance;   /* added  By  Anand  */	
    while (!TRANSPORT_GetExit(tr))
    {
        ITS_USHORT length;
        char *str;

        res = TRANSPORT_GetNextEvent(tr, &event);
        
        if (res != ITS_SUCCESS)
        {
            continue;
        }

        length = event.len;

        ITS_C_ASSERT(length <= ITS_MAX_EVENT_SIZE);

        str = (char *)ITS_Calloc(length + 1,
                                 sizeof(ITS_OCTET));

        memcpy(str, event.data, length);

        DBC_ExecuteCommand(dbc, instance, str);

        ITS_Free(str);
    }

    TRANSPORT_UnfindTransport(tr);
    SCM_instance =NULL;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Note when a command failed.
 *
 *  Input Parameters:
 *      dbc - this server
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
 *      Thread safe.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
DBC_SetCmdFailed(DBC_Server *dbc)
{
    DBC_CMD_FAILED(dbc) = ITS_TRUE;
}

