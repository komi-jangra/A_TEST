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
// LOG: Revision 1.1.1.1  2007/03/08 15:13:57  cvsadmin
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
// LOG: Revision 6.3  2002/08/15 19:09:47  mmiers
// LOG: Warning removal.
// LOG:
// LOG: Revision 6.2  2002/07/25 18:31:03  ngoel
// LOG: add support for command output redirection
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
// LOG: Revision 3.2  2001/02/15 15:58:23  mmiers
// LOG: Ident
// LOG:
// LOG: Revision 3.1  2000/08/16 00:04:53  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.1  2000/08/04 22:40:17  rsonak
// LOG:
// LOG: If putevent fails, ProcessCommandsFromStream doesnt block
// LOG:
// LOG: Revision 2.0  1999/12/03 23:27:12  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.4  1999/07/16 21:23:15  mmiers
// LOG:
// LOG:
// LOG: Update to work on UNIX.
// LOG:
// LOG: Revision 1.3  1999/07/14 19:52:35  hdivoux
// LOG: Improved synchronization for dbc client and console.
// LOG:
// LOG: Revision 1.2  1999/07/09 23:39:56  hdivoux
// LOG: General update for improved version.
// LOG:
// LOG: Revision 1.1  1999/07/02 16:56:18  mmiers
// LOG:
// LOG:
// LOG: Make this look like other subsystems to automate the NT build.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////

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
#include <its_semaphore.h>
#include <its_exception.h>
#include <its_support_exception.h>
#include <its_worker.h>

#ident "$Id: dbc_client.h,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

// Namespaces.

#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)


//
//  DbcClient.
//

class DbcClient
{
public:

    DbcClient(std::istream& inputStreamParam, bool isInteractiveParam = true)
    :   worker(NULL),
        inputStream(inputStreamParam),
        isInteractive(isInteractiveParam),
        isOutputRedirected(false),
        synchronizationEvent(0)
    {};

    virtual ~DbcClient()
    {};

    bool 
    IsWorkerNull() const
    { return worker == NULL; }

    bool 
    IsWorkerNotNull() const
    { return worker != NULL; }

    ITS_Worker*
    GetWorker() const
    { 
        ITS_REQUIRE(IsWorkerNotNull());

        return worker;
    }

    void 
    SetWorker(ITS_Worker* workerParam)
    {
        ITS_REQUIRE(workerParam != NULL);

        worker = workerParam;
    }

    void 
    ResetWorker()
    {
        worker = NULL;
    }

    virtual void ProcessCommandsFromStream();

    virtual void ProcessCommandsResult();


    void
    SynchronizationWait()
    {
        int res = synchronizationEvent.Wait();

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res);
        }
    }

    void
    SynchronizationRelease()
    {
        int res = synchronizationEvent.Post();

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res);
        }
    }

protected:

    virtual int SendCommand();

    ITS_Worker* worker;

    std::istream& inputStream;

    bool isInteractive;

    bool isOutputRedirected;

    char redirectFileName[ITS_PATH_MAX];

    std::string currentCommand;

    std::string currentCommandResult;

    ITS_Semaphore synchronizationEvent;
};


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


#endif // !defined(_DBC_CLIENT_)

