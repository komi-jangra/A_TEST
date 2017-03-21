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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:14  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:03  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:58  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:07  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:22  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2001/11/19 22:51:57  mmiers
// LOG: Convert DBC server to C.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:04  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.3  2001/02/15 15:58:23  mmiers
// LOG: Ident
// LOG:
// LOG: Revision 3.2  2000/08/24 23:06:37  mmiers
// LOG:
// LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
// LOG:
// LOG: Revision 3.1  2000/08/16 00:04:55  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.1  2000/06/13 19:15:56  mmiers
// LOG:
// LOG: C++ assertion no longer throws exception by default.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:27:14  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.9  1999/11/03 17:43:22  labuser
// LOG:
// LOG:
// LOG: Avoid unused variable warning on NT.
// LOG:
// LOG: Revision 1.8  1999/11/03 17:26:14  labuser
// LOG:
// LOG:
// LOG: Don't throw all over the place, catching and leaving is ok.
// LOG:
// LOG: Revision 1.7  1999/10/16 19:59:07  labuser
// LOG:
// LOG: Back out the initialization changes.  This broke on DEC.
// LOG:
// LOG: Revision 1.6  1999/10/13 21:44:11  mmiers
// LOG:
// LOG:
// LOG: Try to work around weirdness on DEC.
// LOG:
// LOG: Revision 1.5  1999/09/01 14:08:06  mmiers
// LOG:
// LOG:
// LOG: Commit the UNIX fix.
// LOG:
// LOG: Revision 1.4  1999/08/02 20:24:18  mmiers
// LOG:
// LOG:
// LOG: Fix some cross-platform issues.
// LOG:
// LOG: Revision 1.3  1999/07/13 23:52:31  hdivoux
// LOG: Work in progress.
// LOG:
// LOG: Revision 1.2  1999/07/09 23:39:57  hdivoux
// LOG: General update for improved version.
// LOG:
// LOG: Revision 1.1  1999/07/02 16:56:20  mmiers
// LOG:
// LOG:
// LOG: Make this look like other subsystems to automate the NT build.
// LOG:
// LOG: Revision 1.6  1999/07/01 16:53:52  hdivoux
// LOG: (Re)Enable quit event mechanism.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////

//
//  DBC server.
//
#include <dbc_server.h>

#if 0
#include <dbc.h>
#include <dbc_server.h>

#ident "$Id: dbc_server.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

// Namespaces.

#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


DbcServer::DbcServer(const string& nameParam, ITS_Worker& workerParam)
:   name(nameParam),
    worker(workerParam),
    currentCommand(""),
    commandPartialResult(false),
    buildingMap(true),
    gate(0)
{
}


DbcServer::~DbcServer()
{
    // Nothing to do.
}


ostream&
operator<<(ostream& os, const DbcServer::Command& cmd)
{
    // Display command right-justified.

    os.setf(ios::right, ios::adjustfield);
    os.width(10);
    os << cmd.command.c_str();
    os.width(1);
    os << " ";

    // Display arguments left-justified.

    os.setf(ios::left, ios::adjustfield);
    os.width(30);
    os << cmd.argumentUsage.c_str() << " ";
    os << cmd.fullCommand << "\n";

    if (cmd.detailedArgumentUsage != "")
    {
        os << endl;
        os << cmd.detailedArgumentUsage.c_str();
        os << endl;
    }
    
    return os;
}


//
//  Thread safe.
//

void
DbcServer::ExecuteCommand(string& commandLine)
{
    Lock();

    try 
    {
        // Build command map if required.

        if (buildingMap)
        {
            istrstream tmp("");

            DoCommand(tmp);
            buildingMap = false;
        }

        istrstream issCommandLine(commandLine.c_str());

        InternalExecuteCommand(issCommandLine);
    }
    catch (exception& exc)
    {
        Unlock();

        throw exc;
    }

    Unlock();
}


//
//  Not thread safe but called only from a thread safe member function.
//

void
DbcServer::InternalExecuteCommand(std::istream& commandLine)
{
    // Make sure first word is empty

    currentCommand = "";

    // Reset commandPartialResult boolean.

    commandPartialResult = false;

    // Read first word (command).

    commandLine >> currentCommand;

    if (commandLine.fail())
    {
        return;
    }

    switch (currentCommand[0])
    {
    case '#':           // Comment.
    case '\0':          // Empty line.
	case '\n':
        Empty();
        break;

    case '?':
        Usage();
        break;

    default:

        // Special case for quit command.

        if (currentCommand == "quit" || currentCommand == "q")
        {
            Quit();

            break;
        }

        // Look up command.

        CommandMap::iterator iter = commandMap.find(currentCommand);

        // If command valid, run it.

        if (iter != commandMap.end())
        {
            DoCommand(commandLine);

            if (!commandLine.fail())
            {
                if (commandPartialResult)
                {
                    SendCommandPartialResult();
                }
                else
                {
                    SendCommandResult();
                }
            }
            else
            {
                oss << "Usage:" << endl
                    << (*iter).second << endl << endl;

                SendCommandResult();
            }
        }
        else
        {
            oss << "Command "
                << currentCommand
                << " not found." << endl;

            SendCommandResult();
        }

        break;
    }
}


bool
DbcServer::Cmd(const string& command,
               const string& fullCommand,
               const string& argumentUsage,
               const string& detailedArgumentUsage)
{
    if (buildingMap)
    {
        CommandMap::iterator iter = commandMap.find(command);

        if (iter != commandMap.end())
        {
            oss << "Command " 
                << command.c_str() 
                << " is not unique." 
                << endl;

            Quit();
        }

        // Register command.

        commandMap.insert(
            CommandMap::value_type(command, Command(command,
                                                    fullCommand,
                                                    argumentUsage,
                                                    detailedArgumentUsage)));
    
        return false;
    }
    else
    {
        return (currentCommand == command);
    }
}


//
//  Not thread safe but called only from a thread safe member function.
//

void
DbcServer::Usage()
{
    oss << "------------ Available Commands [ "
        << name
        << " ] ------------"
        << endl
        << endl;

    for (CommandMap::const_iterator iter = commandMap.begin();
         iter != commandMap.end(); ++iter)
    {
        oss << (*iter).second;
    }

    oss << "      quit                                Exit Debug Console"
        << endl;

    SendCommandResult();
}


//
//  Not thread safe but called only from a thread safe member function.
//

void
DbcServer::Quit()
{
    ITS_Event event;

    event.SetSource(DBC_QUIT_EVT);
    event.SetLength(0);

    int res = ITS_Transport::PutEvent(worker.GetInstance(), event);

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}


//
//  Thread safe.
//

void 
DbcServer::SendCommandResult()
{
    Lock();

    try
    {
        InternalSendCommandResult(false);
    }
    catch (exception& exc)
    {
        Unlock();

        exc=exc;
    }

    Unlock();
}


//
//  Thread safe.
//

void 
DbcServer::SendCommandPartialResult()
{
    Lock();

    try
    {
        InternalSendCommandResult(true);
    }
    catch (exception& exc)
    {
        Unlock();

        exc=exc;
    }

    Unlock();
}


//
// Thread safe.
//

void 
DbcServer::SendCommandFinalResult()
{
    try
    {
        SendCommandResult();
    }
    catch (exception& ex)
    {
        ex=ex;
    }

}


//
//  Not thread safe but called only from a thread safe member function.
//

void
DbcServer::Empty()
{
    ITS_Event event;

    event.SetSource(DBC_LAST_EVT);
    event.SetLength(1);
    event.SetData((unsigned char*)"", 1);

    int res = ITS_Transport::PutEvent(worker.GetInstance(), event);

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}


//
//  Not thread safe but called only from a thread safe member functions.
//

void
DbcServer::InternalSendCommandResult(bool partial)
{
    Lock();

    try
    {
        string commandResult(oss.str(), oss.pcount() + 1);

        commandResult[oss.pcount()] = 0;

        oss.rdbuf()->freeze(false);

#if defined(ITS_STD_NAMESPACE)

        oss.rdbuf()->pubseekpos(0);

#else // !defined(ITS_STD_NAMESPACE)

        oss.rdbuf()->seekpos(0);

#endif // defined(ITS_STD_NAMESPACE)

        int quotient = (commandResult.size() + 1) / ITS_MAX_EVENT_SIZE;

        int remainder = (commandResult.size() + 1) % ITS_MAX_EVENT_SIZE;

        ITS_Event event;

        if (quotient == 0)
        {
            int length =  commandResult.size() + 1;

            event.SetSource(partial ? DBC_MORE_EVT : DBC_LAST_EVT);
            event.SetLength(length);
            event.SetData((unsigned char*)commandResult.c_str(), length);

            int res = ITS_Transport::PutEvent(worker.GetInstance(), event);

            if (res != ITS_SUCCESS)
            {
                ITS_THROW_ERROR(res);
            }
        }
        else
        {
            const char* ptr = commandResult.c_str();

            for (int i = 0; i < quotient; i++)
            {
                int length = ITS_MAX_EVENT_SIZE;

                event.SetSource(DBC_MORE_EVT);
                event.SetLength(length);
                event.SetData((unsigned char*)ptr, length);

                int res = ITS_Transport::PutEvent(worker.GetInstance(), event);

                if (res != ITS_SUCCESS)
                {
                    ITS_THROW_ERROR(res);
                }

                ptr += ITS_MAX_EVENT_SIZE;
            }

            if (remainder != 0)
            {
                int length = remainder;

                event.SetSource(partial ? DBC_MORE_EVT : DBC_LAST_EVT);
                event.SetLength(length);
                event.SetData((unsigned char*)ptr, length);

                int res = ITS_Transport::PutEvent(worker.GetInstance(), event);

                if (res != ITS_SUCCESS)
                {
                    ITS_THROW_ERROR(res);
                }
            }
            else
            {
                event.SetSource(partial ? DBC_MORE_EVT : DBC_LAST_EVT);
                event.SetLength(1);
                event.SetData((unsigned char*)"", 1);

                int res = ITS_Transport::PutEvent(worker.GetInstance(), event);

                if (res != ITS_SUCCESS)
                {
                    ITS_THROW_ERROR(res);
                }
            }
        }
    }
    catch (exception& exc)
    {
        Unlock();

        throw exc;
    }

    Unlock();
}


//
//  Must be called by only one thread.
//

void
DbcServer::ProcessCommandsLoop()
{
    int res = ITS_SUCCESS;

    ITS_Event event;

    while (!worker.GetExit())
    {
        res = worker.GetNextEvent(event);
        
        if (res != ITS_SUCCESS)
        {
            ITS_THROW_ERROR(res);
        }

        ITS_USHORT length = event.GetLength();

        ITS_THROW_ASSERT(length <= ITS_MAX_EVENT_SIZE);

        char *str = (char *)ITS_Calloc(length + 1,
                                       sizeof(ITS_OCTET));

        memcpy(str, event.GetData(), length);

        string commandLine(str);

        ITS_Free(str);

        try
        {
            ExecuteCommand(commandLine);
        }
        catch (exception& ex)
        {
            // don't bail out, it might have been a
            // recoverable error.  Shut up the compiler.
            ex = ex;
        }
    }
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)  

#endif
