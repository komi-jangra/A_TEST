///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//   Copyright 1997-2001 IntelliNet Technologies, Inc. All Rights Reserved.  //
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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:44  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:21  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:56  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:18  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:53:09  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:19  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:37  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:24  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.2  2001/07/25 19:59:13  hdivoux
// LOG: Review unit tester (Makefile and ...).
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:25  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.1  2000/08/16 00:08:40  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.1  2000/05/11 02:06:17  mmiers
// LOG:
// LOG:
// LOG: tools: warning removal.  Hubert needs to take over for the comps.
// LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
// LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
// LOG: perspective, but IMAL class needs implementation.
// LOG: config.vars: correct platform flags for Linux.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:30:32  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.8  1999/08/31 21:11:18  labuser
// LOG:
// LOG:
// LOG: Fix bug in unit tester where lack of input (more specifically,
// LOG: empty lines) could cause reuse of the string containing the
// LOG: last command (same stack location, two different invocations).
// LOG:
// LOG: Revision 1.7  1999/07/01 15:22:07  mmiers
// LOG:
// LOG:
// LOG: Use generic define for std namespace
// LOG:
// LOG: Revision 1.6  1998/10/01 02:08:01  mmiers
// LOG: HPUX doesn't support namespaces.
// LOG:
// LOG: Revision 1.5  1998/10/01 02:03:41  mmiers
// LOG: Add define for namespaces
// LOG:
// LOG: Revision 1.4  1998/09/26 15:49:57  mmiers
// LOG: Fix compile warning
// LOG:
// LOG: Revision 1.3  1998/06/16 00:12:56  hxing
// LOG: make changes to the output format
// LOG:
// LOG: Revision 1.2  1998/06/10 15:11:22  mmiers
// LOG: Small changes.
// LOG:
// LOG: Revision 1.1  1998/06/08 19:50:14  mmiers
// LOG: Add a unit tester.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: UnitTest.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $"

#include <UnitTest.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

///////////////////////////////////////////////////////////////////////////////
//
// Template getlinefixed.
//
// The getline template shipped with VC++ has a bug--it reads one extra
// character at the end. This is a copy of that macro with the bug fixed.
//
///////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)

template<class _E, class _TYPE, class _A> inline
	basic_istream<_E, _TYPE>& getlinefixed(basic_istream<_E, _TYPE>& _I,
		basic_string<_E, _TYPE, _A>& _X, const _E _D)
	{ios_base::iostate _St = ios_base::goodbit;
	bool _Chg = false;
	_X.erase();
	const basic_istream<_E, _TYPE>::sentry _Ok(_I, true);
	if (_Ok)
		{_TRY_IO_BEGIN
		_TYPE::int_type _C = _I.rdbuf()->sgetc();
		for (; ; _C = _I.rdbuf()->snextc())
			if (_TYPE::eq_int_type(_TYPE::eof(), _C))
				{_St |= ios_base::eofbit;
				break; }
			else if (_TYPE::eq(_C, _D))
				{_Chg = true;
                _I.rdbuf()->sbumpc(); // bug was here: used to call snextc().
				break; }
			else if (_X.max_size() <= _X.size())
				{_St |= ios_base::failbit;
				break; }
			else
				_X += _TYPE::to_char_type(_C), _Chg = true;
		_CATCH_IO_(_I); }
	if (!_Chg)
		_St |= ios_base::failbit;
	_I.setstate(_St);
	return (_I); }

#endif // defined(WIN32)

//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      UnitTest constructor: creates and initializes a UnitTest object.
//
//  Input Parameters:
//      p_name - name of the unit test
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.
//
//  Notes:
//
//  See Also:
///////////////////////////////////////////////////////////////////////////////
UnitTest::UnitTest(const string& p_name)
  : name(p_name),
    pInputStream(0),
    buildingMap(true)
{
}

//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      Display a command.
//
//  Input Parameters:
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.
//
//  Notes:
//
//  See Also:
///////////////////////////////////////////////////////////////////////////////
ostream&
operator<<(ostream& os, const UnitTest::Command& cmd)
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
    
    return os;
}

//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      Runs the unit test from the given stream by reading and executing
//      commands until "quit" or EOF is reached.
//
//  Input Parameters:
//      inputStream   - stream containing unit test script.
//      isInteractive - is the unit test being run from a script or is it
//                      interactive. When it is interactive, a prompt is
//                      presented reading each command. When it is not 
//                      interactive, each command is echoed to the output 
//                      script before being processed.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.
//
//  Notes:
//
//  See Also:
///////////////////////////////////////////////////////////////////////////////
void
UnitTest::ExecuteCommandsFromStream(istream& inputStream, bool isInteractive)
{
    // Remember the input stream.
    pInputStream = &inputStream;

    cout << name << " begin" << endl;

    for (bool active = true; active;)
    {
        // Stop if end of file.
        if (inputStream.eof())
        {
            cerr << "End of input, but no quit command." << endl;
            break;
        }

        // Prompt for command line if we are interactive.
        if (isInteractive)
        {
            cout << ">> ";
        }

        // Read command line.
        string commandLine;

#if defined(WIN32)
        getlinefixed(inputStream, commandLine, '\n');
#else
        getline(inputStream, commandLine, '\n');
#endif

        if (!inputStream)
        {
            break;
        }

        // Echo the command if we are in script mode.
        if (!isInteractive)
        {
            cout << commandLine << endl;
        }

        // Truncate line at # comment.
        string::size_type firstPound = commandLine.find('#');
        if (firstPound != string::npos)
        {
            commandLine.erase(firstPound);
        }

        // Execute command line as its own stream.
        istrstream commandStream(commandLine.c_str());

        active = ExecuteCommand(commandStream);        
    }

    cout << name << " done\n";

    // Reset the input stream to 0.
    pInputStream = 0;
}

//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      Executes a single unit test command.
//
//  Input Parameters:
//      None.
//
//  Input/Output Parameters:
//      commandStream   - The command line to process.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      TRUE if still active, FALSE if "quit" command
//
//  Notes:
//
//  See Also:
///////////////////////////////////////////////////////////////////////////////
bool
UnitTest::ExecuteCommand(istream& commandStream)
{
    // Build command table map if necessary.
    if (buildingMap)
    {
        istrstream tmp("");

        DoCommand(tmp);
        buildingMap = false;
    }

    return InternalExecuteCommand(commandStream);
}

//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      Reads in multiple lines from the command line.  Lines are read until
//      'END' is entered on a single line.
//
//  Input Parameters:
//      name - name of the field to display in the prompt.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      The string that has been read from the command line.
//
//  Notes:
//
//  See Also:
///////////////////////////////////////////////////////////////////////////////
string
UnitTest::ReadMultilineString(const string& strName) const
{
    if (pInputStream == 0)
    {
        cerr << "ReadMultilineString can only be called from "
             << "within the DoCommand method of classes derived "
             << "from UnitTest" << endl;
        exit(1);
    }

    cout << "Enter value for " << name << endl;
    cout << "Type END on a blank line to finish" << endl;

    // Start with an empty field.
    string result;


    while (true)
    {
        // Read in a command from the imput stream.
        string commandLine;

#if defined(WIN32)
        getlinefixed(*pInputStream, commandLine, '\n');
#else
        getline(*pInputStream, commandLine, '\n');
#endif
        // Stop if end of stream.
        if (pInputStream->eof())
        {
            cerr << "End of input, but no quit command." << endl;
            break;
        }


        // Exit the loop if END was entered.
        if (commandLine.compare("END") == 0)
        {
            break;
        }

        // Insert a newline if we are between lines.  
        // (getlinefixed removes them)
        if (!result.empty())
        {
            result.append("\n");
        }

        // Add the new line to the field.
        result.append(commandLine);
    }

    return result;
}

//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      Parses command text and executes the DoCommand() method if valid
//      command.
//
//  Input Parameters:
//      None.
//
//  Input/Output Parameters:
//      commandStream - stream with command line.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      TRUE if still active, FALSE if "quit" command
//
//  Notes:
//
//  See Also:
///////////////////////////////////////////////////////////////////////////////
bool
UnitTest::InternalExecuteCommand(istream& commandStream)
{
    // Start with a known value.
    currentCommand = "";

    // Read first word (command).
    commandStream >> currentCommand;

    if (commandStream.fail())
    {
        // Can't do anything, so might as well leave.
        return true;
    }

    string word(currentCommand);

    switch (word[0])
    {
    case '#':           // Comment.
    case '\0':          // Empty line.
	case '\n':
        break;

    case 'q':
        return false;

    case '?':
        Usage();
        break;

    default:
        // Look up command.
        CommandMap::iterator i = commandMap.find(word);

        // If command valid, run it.
        if (i != commandMap.end())
        {
            DoCommand(commandStream);
            if (commandStream.fail())
            {
                cerr << "Usage:\n";
                cerr << (*i).second << "\n\n";
            }
        }
        else
        {
            cerr << "Command "
                 << currentCommand 
                 << " not found.\n";
        }
        break;
    }

    return true;
}

//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      The programmer specifies in each Cmd method all the information
//      neccessary to specify a unit test command.
//
//      There are two forms: commands with arguments and commands without
//      arguments.
//
//      Cmd is automatically invoked once during the initialization phase to
//      build an internal table of all unit test commands. The Cmd method is
//      designed to be called from within an if-statement whose body contains
//      the actual unit test code. During the initialization phase each Cmd
//      method returns FALSE. When the unit test is actually being run, Cmd
//      returns TRUE on the matching command.
//
//  Input Parameters:
//      p_command       - the command name that the user types.
//      p_fullCommand   - full description of command.
//      p_argumentUsage - (optional) description of arguments for '?' help.
//
//  Input/Output Parameters:
//      commandStream   - stream with command line
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      True if the command is to be executed.
//
//  Notes:
//
//  See Also:
///////////////////////////////////////////////////////////////////////////////
bool
UnitTest::Cmd(
            const char* p_command,
            const char* p_fullCommand,
            const char* p_argumentUsage)
{
    string cmd(p_command);

    if (buildingMap)
    {
        CommandMap::iterator existingCommand =
            commandMap.find(cmd);

        if (existingCommand != commandMap.end())
        {
            cerr << "Command " << p_command << " is already defined.\n";
            exit(1);
        }

        // Register command.
        commandMap.insert(
            CommandMap::value_type(
                cmd,
                Command(
                    p_command,
                    p_fullCommand,
                    p_argumentUsage)));
    
        return false;
    }
    else
    {
        return (currentCommand == p_command);
    }
}

//.implementation:public
///////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      Display usage statement for each command.
//
//  Input Parameters:
//      None.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//
//  Notes:
//
//  See Also:
///////////////////////////////////////////////////////////////////////////////
void
UnitTest::Usage() const
{
    cout << "================ C O M M A N D S ===================\n";

    for (CommandMap::const_iterator i = commandMap.begin();
         i != commandMap.end(); ++i)
    {
        cout << (*i).second;
    }
    cout <<	"      quit                                   exit unit tester\n";
}


