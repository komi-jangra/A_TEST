//////////////////////////////////-*-C-*-////////////////////////////////////
//                                                                         //
//             Copyright 1997,1998 IntelliNet Technologies, Inc.           //
//                            All Rights Reserved.                         //
//             Manufactured in the United States of America.               //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.      //
//                                                                         //
//   This product and related documentation is protected by copyright and  //
//   distributed under licenses restricting its use, copying, distribution //
//   and decompilation.  No part of this product or related documentation  //
//   may be reproduced in any form by any means without prior written      //
//   authorization of IntelliNet Technologies and its licensors, if any.   //
//                                                                         //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     //
//   government is subject to restrictions as set forth in subparagraph    //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software      //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                       //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// CONTRACT: INTERNAL                                                      //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: dbc_command_client.h,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $
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
// LOG: Revision 9.1  2005/03/23 12:53:06  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.3  2005/03/21 13:51:22  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:04  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.1  2000/08/16 00:04:54  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 1.3  2000/03/29 18:20:43  ahanda
// LOG: Need them for HNS Vlr Cache Dump
// LOG:
// LOG: Revision 1.2  1999/02/08 17:07:53  rsonak
// LOG:
// LOG: Got DBC Command working
// LOG:
// LOG: Revision 1.1  1999/02/04 22:03:01  rsonak
// LOG:
// LOG: DBC Commandline Utility. Does the same work od DBC console through command line.
// LOG:
// LOG: Revision 1.1  1998/11/17 17:44:26  mmiers
// LOG: Move DBC into common to sanitize the build.
// LOG:
// LOG: Revision 1.3  1998/11/05 21:29:53  mmiers
// LOG: Build on HPUX.
// LOG:
// LOG: Revision 1.2  1998/11/05 21:20:51  mmiers
// LOG: Portability build.
// LOG:
//
/////////////////////////////////////////////////////////////////////////////

//
//  DBC client.
//

#if !defined(_DBC_CLIENT_)
#define _DBC_CLIENT_

#if defined(HPUX)
#include <iostream/iostream.h>
#include <iostream/strstream.h>
#else
#include <iostream>
#include <strstream>
#endif
#include <string>

#include <its++.h>
#include <its_mutex.h>
#include <its_exception.h>
#include <its_worker.h>


// Namespaces.

#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)


//
//  DbcClient.
//

class DbcClient
{
public:

    DbcClient(std::istream& inputStreamParam,
              bool isInteractiveParam = false)
    :   worker(NULL),
        inputStream(inputStreamParam),
        isInteractive(isInteractiveParam),
        coutLock(0),
		commandsResultCounter(0)
    {};

    virtual ~DbcClient()
    {};

    void SetWorker(ITS_Worker* workerParam)
    {
        ITS_REQUIRE(workerParam != NULL);

        worker = workerParam;
    }

	bool IsWorkerInitialized() const
	{ return worker != NULL; }

	unsigned long GetCommandsResultCounter() const
	{ return commandsResultCounter; }

    virtual void ProcessCommandsFromStream(std::istream& inputStream,
                                           bool isInteractive);

    virtual void ProcessCommandsResult();

protected:

    virtual void SendCommand();

    ITS_Worker* worker;

    std::istream& inputStream;

    bool isInteractive;

    std::string currentCommand;

    std::string currentCommandResult;

    ITS_Mutex coutLock;

	unsigned long commandsResultCounter;
};


#if defined(ITS_NAMESPACE)
}
#endif    // defined(ITS_NAMESPACE)


#endif  // !defined(_DBC_CLIENT_)

