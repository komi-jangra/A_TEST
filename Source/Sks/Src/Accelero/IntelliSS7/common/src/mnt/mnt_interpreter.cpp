///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     //
//             Manufactured in the United States of America.                 //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:27  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:18  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:31  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:52  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.3  2001/10/09 19:17:04  hdivoux
// LOG: Added GetArraySize command and allowed for empty arrays.
// LOG:
// LOG: Revision 5.2  2001/08/29 17:12:25  hdivoux
// LOG: Added Exit predefined command.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.9  2001/08/09 22:39:53  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 1.8  2001/08/09 21:03:15  hdivoux
// LOG: Port to GNU g++.
// LOG:
// LOG: Revision 1.7  2001/08/09 20:30:47  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 1.6  2001/08/09 20:06:26  hdivoux
// LOG: Port to Unix (Sun CC).
// LOG:
// LOG: Revision 1.5  2001/08/08 20:37:07  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.4  2001/08/07 23:25:23  hdivoux
// LOG: Update for debug related commands.
// LOG:
// LOG: Revision 1.3  2001/08/07 21:52:59  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.2  2001/08/06 21:55:52  hdivoux
// LOG: Added GCS related predefined commands.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_interpreter.cpp,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

//
//
// mnt_interpreter.cpp: MNT interpreter implementation.
//
//


#include <mnt_interpreter.h>
#include <mnt_mnt.h>
#include <mnt_constructs.h>
#include <mnt_parser.h>
#include <mnt_exception.h>
#include <mnt_errors.h>
#include <mnt_predefined_commands.h>
#include <mnt_evaluator.h>

///////////////////////////////////////////////////////////////////////////////
//
// Forward declarations.
//

extern FILE* yyin;
extern int yydebug;
extern size_t mntErrorLineNumberG;
extern mnt::Construct* mntParsedTreeG;

extern int yyparse();
extern void yyrestart(FILE* desc);


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)


#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif // defined(ITS_NAMESPACE)


///////////////////////////////////////////////////////////////////////////////
//
// Interpreter.
//

Interpreter::Interpreter()
{
    // Add all predefined (i.e. built-in) commands.

    InsertCommand(new CommandPrint());
    InsertCommand(new CommandSleep());
    InsertCommand(new CommandBreakpoint());
    InsertCommand(new CommandInitializeNodes());
    InsertCommand(new CommandInitializeNodesSyncPoints());
    InsertCommand(new CommandInitializeGcs());
    InsertCommand(new CommandTerminateNodes());
    InsertCommand(new CommandTerminateNodesSyncPoints());
    InsertCommand(new CommandTerminateGcs());
    InsertCommand(new CommandWaitForNodeJoinPoint());
    InsertCommand(new CommandWaitForNodeSyncPoint());
    InsertCommand(new CommandPublishNodeSyncPointReached());
    InsertCommand(new CommandSetInternalDebugOn());
    InsertCommand(new CommandSetInternalDebugOff());
    InsertCommand(new CommandSetInternalParserDebugOn());
    InsertCommand(new CommandSetInternalParserDebugOff());
    InsertCommand(new CommandSystem());
    InsertCommand(new CommandRedirectStdout());
    InsertCommand(new CommandPrintFile());
    InsertCommand(new CommandExit());
    InsertCommand(new CommandGetArraySize());
}

Interpreter::~Interpreter()
{
    for (
        Commands::iterator iter = _commands.begin();
        iter != _commands.end();
        iter++)
    {
        delete (*iter).second;
    }

    if (mntParsedTreeG != NULL)
    {
        delete mntParsedTreeG;
        mntParsedTreeG = NULL;
    }
}

void 
Interpreter::Execute(Mnt& mnt, FILE* stream)
{
    ITS_REQUIRE(stream != NULL);

    ////////////////////////////////////////////////////////
    //
    // Parsing.
    //

    yyrestart(stream);

    if (mnt.GetOptions().IsParserDebugOn())
    {
        yydebug = 1;
    }
    else
    {
        yydebug = 0;
    }

    // Cleanup. 
    if (mntParsedTreeG != NULL)
    {
        delete mntParsedTreeG;
        mntParsedTreeG = NULL;
    }

    int parseResult = yyparse();

    if (parseResult != 0)
    {
        MNT_THROW_ERROR(
            "parse syntax error",
            mntErrorLineNumberG,
            0,
            MNT_E_PARSE_SYNTAX_ERROR);
    }

    Construct* parsedTree = mntParsedTreeG;

    ITS_ASSERT(parsedTree != NULL);

    if (mnt.GetOptions().IsParserDebugOn())
    {
        mnt.GetPrintLock().Acquire();

        cout << "\n";
        cout << "\n";
        cout << "Parsed Tree:\n";
        cout << "============\n";
        cout << "\n";

        parsedTree->Print(cout);

        cout << "\n";

        mnt.GetPrintLock().Release();
    }


    ////////////////////////////////////////////////////////
    //
    // Execution.
    //

    ExecuteContext executeContext;
    Evaluator evaluator;

    executeContext.SetEvaluator(&evaluator);
    executeContext.SetInterpreter(this);
    executeContext.SetMnt(&mnt);

    parsedTree->Execute(executeContext);
}



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


