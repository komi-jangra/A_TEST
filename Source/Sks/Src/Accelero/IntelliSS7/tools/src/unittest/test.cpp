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
// LOG: Revision 1.1.1.1  2007/03/08 15:14:57  cvsadmin
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
// LOG: Revision 4.3  2001/07/25 20:16:10  hdivoux
// LOG: Update of Makefile and remove warning in test.cpp.
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
// LOG: Revision 2.0  1999/12/03 23:30:33  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.3  1998/06/15 17:19:42  gkosasi
// LOG: My first-modification on unit test.
// LOG:
// LOG: Revision 1.2  1998/06/08 20:13:53  hxing
// LOG: Sample command.
// LOG:
// LOG: Revision 1.1  1998/06/08 19:50:14  mmiers
// LOG: Add a unit tester.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: test.cpp,v 1.1.1.1 2007-10-08 11:12:09 bsccs2 Exp $"

#include <UnitTest.h>

using namespace std;

class UnitTestUnitTest : public UnitTest
{
public:
    UnitTestUnitTest() : UnitTest("UnitTestUnitTest")
    {
    }

private:
    void DoCommand(istream& cmdLine);
};



void
UnitTestUnitTest::DoCommand(istream& cmdLine)
{
    if (Cmd("RIII", "Read Int Int Int", "<int, int, int>"))
    {
        int param1;
        int param2;
		int param3;

        cmdLine >> param1 >> param2 >> param3;

        if (!cmdLine.fail())
        {
             cout << "First cmd param: <" << param1 << ">"
                  << " Second cmd param: <" << param2 << ">"
				  << " Third cmd param: <" << param3 << ">."
                  << endl;
        }
    }
    else if (Cmd("RISF", "Read Int String Float", "<int, string, float> "))
    {
        int param1;
        string param2;
        float param3;
		
        cmdLine >> param1 >> param2 >> param3;

        if (!cmdLine.fail())
        {
             cout << " First cmd param : <" << param1 << ">"
                  << " Second cmd param: <" << param2 << ">"
                  << " Third cmd param : <" << param3 << ">." 
                  << endl;
        }
    }
    else if (Cmd("RML", "Read Multi Line", "<data>"))
    {
        string data;
        data = ReadMultilineString("<data>");
        cout << "\nMultiline data: <" << data << ">." << endl;
    }
    else if (Cmd("TEST_ONE", "Dummy command", "<no args>"))
    {
        cout << "Dummy command" << endl;
    }
	else if (Cmd("MY_NAME", "Read String (fill your first name)", "<string>"))
	{
		string myName;
		cmdLine >> myName;

		if (!cmdLine.fail())
		{
			cout << "Your first name is " << myName << ".";
			cout << endl;
		}

	}
}



int
main()
{
    UnitTestUnitTest test;

    test.ExecuteCommandsFromStream();

    return 0;
}

