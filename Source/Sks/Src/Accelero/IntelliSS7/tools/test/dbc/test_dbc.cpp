////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
// CONTRACT: Hughes Network Systems                                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <its++.h>
#include <its_route.h>
#include <test_dbc.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

void
TestDbcServer::DoCommand(std::istream& commandLine)
{
    if (Cmd("test1", "This is Test 1", "<>"))
    {
        oss << "This is test 1 response from the server" << endl;  
    }
    else if (Cmd("test2", "This is Test 2", "<>"))
    {
        oss << "This is test 2 response from the server" << endl;  
    }
    else if (Cmd("tst_riii", "Test Read Int Int Int", "<int, int, int>"))
    {
        int param1;
        int param2;
		int param3;

        commandLine >> param1 >> param2 >> param3;

        if (!commandLine.fail())
        {
             oss << "First cmd param: <" << param1 << ">"
                 << " Second cmd param: <" << param2 << ">"
				 << " Third cmd param: <" << param3 << ">."
                 << endl;
        }
    }
    else if (Cmd("tst_risf", "Test Read Int String Float", "<int, string, float> "))
    {
        int param1;
        string param2;
        float param3;
		
        commandLine >> param1 >> param2 >> param3;

        if (!commandLine.fail())
        {
             oss << "First cmd param : <" << param1 << ">"
                 << " Second cmd param: <" << param2 << ">"
                 << " Third cmd param : <" << param3 << ">." 
                 << endl;
        }
    }
    else if (Cmd("tst_str", "Test Read String", "<string>"))
    {
        string param;

        commandLine >> param;

        if (!commandLine.fail())
        {
            oss << "Cmd param : <" << param << ">" << endl;
        }
    }
    else if (Cmd("tst_dc", "Test Dummy command", "<>"))
    {
        oss << "Dummy command." << endl;
    }
    else if (Cmd("tst_lo", "Test Long Output", "<>"))
    {
        for (int i = 0; i < 400; i++)
        {
            oss << i << " 0123456789" << endl;
        }

        oss << "." << endl;

    }
}

