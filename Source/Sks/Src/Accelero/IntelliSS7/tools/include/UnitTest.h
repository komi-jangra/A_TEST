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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:38  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:17  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:34  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:07  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.3  2005/03/21 13:52:47  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:17  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:30  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:19  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.2  2001/07/25 19:59:13  hdivoux
// LOG: Review unit tester (Makefile and ...).
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:22  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.1  2000/08/16 00:07:04  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.2  2000/07/25 19:28:36  hxing
// LOG: Kill STL warnings.
// LOG:
// LOG: Revision 2.1  2000/07/24 18:55:24  hdivoux
// LOG: Change of header file includes for no warnings with VC++ 6.0.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:29:38  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.3  1999/06/30 16:55:41  mmiers
// LOG:
// LOG:
// LOG: Get the behavior controllers (its++.h)
// LOG:
// LOG: Revision 1.2  1998/09/30 17:11:51  jrao
// LOG: HPUX doesn't support the stdc++ file names.
// LOG:
// LOG: Revision 1.1  1998/06/08 19:49:58  mmiers
// LOG: Add a unit tester.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#if !defined _UNIT_TEST_H_
#define _UNIT_TEST_H_

#ident "$Id: UnitTest.h,v 1.1.1.1 2007-10-08 11:12:04 bsccs2 Exp $"

#include <its++.h>

#if !defined(HPUX)
#include <iostream>
#include <strstream>
#else
#include <iostream/iostream.h>
#include <iostream/strstream.h>
#endif
#include <string>
#include <map>

//
// Maximum length of a command.
//
const int MAXCOMMANDLEN = 256;

//.interface:UnitTest
///////////////////////////////////////////////////////////////////////////////
//
//  Interface:
//      UnitTest
//
//  Purpose:
//      The UnitTest class was written to shorten and simplify the amount of
//      "scaffolding" code neccessary to unit test a C++ class.
//
//      Traditionally, the unit test parses standard-input into commands which
//      instantiate and then exercise the public interface of the object. The
//      sequence of commands which exhaustively test the object are captured in
//      a script and the output of running the script is captured in a 
//      benchmark file for comparisons with later runs.
//
//      Using the UnitTest class has the following advantages over writing the
//      unit test from scratch:
//          - The command parser code is inside UnitTest instead of every unit
//            test. This simplifies the unit tester greatly. Because the parser
//            code is centralized, it is easier to maintain and can grow to be
//            more powerful.
//          - The UnitTest parser supports "# comments" and space/tab 
//            indentation.
//
//      All unit test commands are specified with the Cmd method:
//
//          Cmd("command-name",
//              "full-command-name",
//              "argument usage")
//
//      If Cmd() returns true, the command has been found.
//
//  Usage:
//
//      1.  #include <UnitTest.h>
//
//      2.  Declare a class derived from UnitTest to test a particular class:
//
//          class CarUnitTest : public UnitTest
//          {
//          public:
//              CarUnitTest() : UnitTest("CarUnitTest") { }
//
//              void DoCommand(std::istream& cmdLine);
//
//          private:
//              auto_ptr<Car> pCar; // Pointer to object under test.
//              ...
//              ...                 // Other instance data for test.
//          };
//
//      3.  Provide the implementation for DoCommand() which checks for each
//          command in turn by calling the Cmd() method. Here is an example
//          without run-time arguments:
//
//          void CarUnitTest::DoCommand(std::istream& cmdLine)
//          {
//              if (Cmd("c", "construct"))
//              {
//                  pCar = auto_ptr<Car>(new Car());
//              }
//
//              ...
//              ...
//          }
//
//          If the command does take run-time arguments, they can be read from
//          cmdLine with the usual >> shift operators.
//
//          if (Cmd("cn", "construct named car", "<name>"))
//          {
//              std::string name;
//
//              cmdLine >> name;
//
//              if (!cmdLine.fail())
//              {
//                  pCar = auto_ptr<Car>(new Car(name));
//              }
//          }
//
//          Notice the test for failure: you must manually check for failure
//          from retrieving the arguments of the command line. On the opposite
//          there is no need to provide a usage statement on failure: UnitTest
//          framework does that for you on returning from DoCommand().
//
//      4.  Inside main(), instantiate the specialized unit test:
//
//          CarUnitTest ut;
//
//      5.  Call the method ExecuteCommandsFromStream.  Input is taken from cin
//          by default but can be changed and output is sent to cout:
//
//          ut.ExecuteCommandsFromStream();
//
//          You can turn off isInteractive if you know you are running in batch
//          mode; this will keep prompts from being echoed to cout, but will 
//          echo each command to cout as it is encountered:
//
//          ut.ExecuteCommandsFromStream(cin, false);
//
///////////////////////////////////////////////////////////////////////////////

class UnitTest
{
public:
    UnitTest(const std::string& p_name);

    virtual ~UnitTest()
    {
    }

    virtual void DoCommand(std::istream& cmdLine) = 0;

    void    ExecuteCommandsFromStream(std::istream& inputStream = std::cin,
                                      bool isInteractive = true);

    bool    Cmd(const char* p_command,
                const char* p_fullCommand,
                const char* p_argumentUsage = "");


    class Command
    {
    public:
        Command(const std::string& p_command,
                const std::string& p_fullCommand,
                const std::string& p_argumentUsage)
            : command(p_command),
              fullCommand(p_fullCommand),
              argumentUsage(p_argumentUsage)
        {
        }

        Command()
        {
        }

        const std::string command;
        const std::string fullCommand;
        const std::string argumentUsage;
    };


    bool ExecuteCommand(std::istream& cmdLine);

protected:
    std::string ReadMultilineString(const std::string& name) const;

private:
    bool InternalExecuteCommand(std::istream& cmdLine);

    void Usage() const;

    const std::string name;

    std::string currentCommand;

    typedef  std::map<std::string, Command> CommandMap;

    CommandMap commandMap;

    std::istream* pInputStream;

    bool buildingMap;
};

std::ostream& operator<<(std::ostream& wos,
                    const UnitTest::Command& cmd);

#endif // !defined(_UNIT_TEST_H_)
