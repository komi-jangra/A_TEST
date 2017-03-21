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

//
//  Test Debug Console.
//


#if !defined(_TEST_DBC_H_)
#define _TEST_DBC_H_

#if _TEST_VER >= 1000
#pragma once
#endif // _TEST_VER >= 1000


#include <its++.h>
#include <dbc_server.h>

#if !defined(HPUX)
using namespace std;
using namespace its;
#endif

enum
{
    FIRST_DISPATCHER_THREAD  = 1,

    DBG_DISPATCHER_THREAD    = 1,

    NUMBER_DISPATCHER_THREAD = 1,

    LAST_DISPATCHER_THREAD   = 1
};


class TestDbcServer : public DbcServer
{
public:

    TestDbcServer(const std::string& nameParam, ITS_Worker& worker)
    : DbcServer(nameParam, worker)
    {};

    virtual ~TestDbcServer()
    {};

    virtual void DoCommand(std::istream& commandLine);

};



#endif    // !defined(_MSC_DBC_H_)

