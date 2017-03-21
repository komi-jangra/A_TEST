////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:00  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.3  2005/03/21 13:50:43  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.5  2002/06/18 19:28:12  mmiers
// LOG: Update DBC console to be able to take more than one
// LOG: command procedure
// LOG:
// LOG: Revision 6.4  2002/05/07 16:20:27  mmiers
// LOG: Use right fields.
// LOG:
// LOG: Revision 6.3  2002/04/29 22:22:50  mmiers
// LOG: Try unfreezing oss.
// LOG:
// LOG: Revision 6.2  2002/04/26 22:15:30  mmiers
// LOG: Fix bug Henry found
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:04  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.4  2001/11/20 17:42:01  mmiers
// LOG: Finish DBC conversion.
// LOG:
// LOG: Revision 5.3  2001/11/19 23:49:31  mmiers
// LOG: twiddling.
// LOG:
// LOG: Revision 5.2  2001/11/19 22:51:57  mmiers
// LOG: Convert DBC server to C.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
// LOG: Convert RCSID to ident.
// LOG:
// LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
// LOG: Move log back (more complaints than applause).
// LOG: Make C service take event log.
// LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
// LOG: bindings).
// LOG:
// LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
// LOG: Demo log at bottom of file.
// LOG:
// LOG: Revision 3.2  2000/08/24 23:06:34  mmiers
// LOG:
// LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
// LOG:
// LOG: Revision 3.1  2000/08/16 00:03:07  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:25:29  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.3  1999/07/13 23:52:31  hdivoux
// LOG: Work in progress.
// LOG:
// LOG: Revision 1.2  1999/07/09 23:39:56  hdivoux
// LOG: General update for improved version.
// LOG:
// LOG: Revision 1.1  1998/11/17 17:44:25  mmiers
// LOG: Move DBC into common to sanitize the build.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////

//
//  DBC server.
//

#if !defined(_DBC_SERVER_)
#define _DBC_SERVER_

#ident "$Id: dbc_server.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

/*
 * disable template warnings by having this first.
 */
#include <its++.h>

#if defined(HPUX)
#include <iostream/iostream.h>
#include <iostream/strstream.h>
#else
#include <iostream>
#include <strstream>
#endif

#include <dbc_serv.h>

// Namespaces.

#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

/////////////////////////////////////////////////////////////////////
//
//  DbcServer.
//
/////////////////////////////////////////////////////////////////////
class DbcServer
{
public:
    DbcServer(const std::string& nameParam, Worker& worker)
        : inst(worker.GetInstance())
    {
        dbc = (DBC_Server *)ITS_ConstructObject(itsDBC_ServerClass,
                                                nameParam.c_str(),
                                                this);

        ITS_THROW_ASSERT(dbc != NULL);

        DBC_CLASS_DO_COMMAND(ITS_OBJ_CLASS(dbc))[0] = StaticDoCommand;
    }
    DbcServer(const std::string& nameParam, ITS_USHORT instance)
        : inst(instance)
    {
        dbc = (DBC_Server *)ITS_ConstructObject(itsDBC_ServerClass,
                                                nameParam.c_str(),
                                                this);

        ITS_THROW_ASSERT(dbc != NULL);

        DBC_CLASS_DO_COMMAND(ITS_OBJ_CLASS(dbc))[0] = StaticDoCommand;
    }
    DbcServer(const std::string& nameParam)
        : inst(0)
    {
        dbc = (DBC_Server *)ITS_ConstructObject(itsDBC_ServerClass,
                                                nameParam.c_str(),
                                                this);

        ITS_THROW_ASSERT(dbc != NULL);

        DBC_CLASS_DO_COMMAND(ITS_OBJ_CLASS(dbc))[0] = StaticDoCommand;
    }

    virtual ~DbcServer()
    {
        DBC_ServerDestroy(dbc);
    }

    static void StaticDoCommand(DBC_Server *dbc, const char *commandLine);

    virtual void DoCommand(std::istream& commandLine) = 0;

    bool    Cmd(const std::string& command,
                const std::string& fullCommand,
                const std::string& argumentUsage = "",
                const std::string& detailedArgumentUsage = "")
    {
        if (DBC_Cmd(dbc,
                    command.c_str(), fullCommand.c_str(),
                    argumentUsage.c_str(), detailedArgumentUsage.c_str()))
        {
            return (true);
        }

        return (false);
    }

    int AddDoCommand(DBC_CommandProc proc)
    {
        return DBC_AddDoCommand(proc);
    }

    void ProcessCommandsLoop()
    {
        DBC_ProcessCommandsLoop(dbc, inst);
    }

    void ExecuteCommand(std::string& commandLine)
    {
        DBC_ExecuteCommand(dbc, inst, commandLine.c_str());
    }

    void SendCommandResult()
    {
        DBC_SendCommandResult(dbc, inst);
    }

    void SendCommandPartialResult()
    {
        DBC_SendCommandPartialResult(dbc, inst);
    }

    void SendCommandFinalResult()
    {
        DBC_SendCommandFinalResult(dbc, inst);
    }

    void 
    SetCommandPartialResult()
    { DBC_PARTIAL_RESULT(dbc) = ITS_TRUE; }

    void 
    UnsetCommandPartialResult()
    { DBC_PARTIAL_RESULT(dbc) = ITS_FALSE; }

    bool
    IsCommandPartialResult() const
    { return DBC_PARTIAL_RESULT(dbc) ? true : false; }

    void
    SetCommandFailed()
    { DBC_CMD_FAILED(dbc) = ITS_TRUE; }

    bool
    IsCommandFailed() const
    { return DBC_CMD_FAILED(dbc) ? true : false; }

    void
    SetInstance(ITS_USHORT instance)
    {
        inst = instance;
    }
    ITS_USHORT
    GetInstance()
    {
        return (inst);
    }

    //
    //  Not thread safe. Should be used in conjunction with Lock() and Unlock().
    //
    std::ostrstream& 
    GetOss()
    {
        return oss;
    }

    void 
    Lock()
    {
        DBC_Lock(dbc);
    }

    void 
    Unlock()
    {
        DBC_Unlock(dbc);
    }

    // helper for the engine
    DBC_Server *
    GetServer()
    {
        return (dbc);
    }

protected:
    DBC_Server      *dbc;
    ITS_USHORT      inst;
    std::ostrstream oss;
};

inline void DbcServer::StaticDoCommand(DBC_Server *dbc, const char *commandLine)
{
    DbcServer *serv = (DbcServer *)DBC_BACK(dbc);

    std::istrstream iss(commandLine);

    serv->DoCommand(iss);

    if (serv->oss.pcount())
    {
        std::string commandResult(serv->oss.str(), serv->oss.pcount() + 1);

        commandResult[serv->oss.pcount()] = 0;

        DBC_AppendText(dbc, commandResult.c_str());

        serv->oss.rdbuf()->freeze(false);

#if defined(ITS_STD_NAMESPACE)

        serv->oss.rdbuf()->pubseekpos(0);

#else // !defined(ITS_STD_NAMESPACE)

        serv->oss.rdbuf()->seekpos(0);

#endif // defined(ITS_STD_NAMESPACE)
    }
}

#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


#endif // !defined(_DBC_SERVER_)
