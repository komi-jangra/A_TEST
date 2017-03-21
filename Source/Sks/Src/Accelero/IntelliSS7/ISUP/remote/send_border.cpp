////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
//  ID: $Id: send_border.cpp,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

#include <its++.h>
#include <its_timers.h>

#include <iostream>

#include <its_app.h>
#include <its_transports.h>
#include <its_semaphore.h>
#include <itu/isup.h>
#include <send_border.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  Synchronization object (semaphore) used to synchronize primary thread and
//  border transport thread.
//

ITS_Semaphore borderTransportSemaphore(0);


THREAD_RET_TYPE
BorderTransportThread::DispatchFunction(void* arg)
{
    BorderTransportThread* current =
        static_cast<BorderTransportThread*>(arg);

#if defined(USE_SOCKETS)

    ITS_HANDLE handle = ITS_Initialize(
                                ITS_ISUP                    |
                                ITS_TRANSPORT_CSOCKET       |
                                ITS_TRANSPORT_IMAL_SOCKET   |
                                ITS_TRANSPORT_SINGLE_USER,
                                2);

#else // !defined(USE_SOCKETS)

    ITS_HANDLE handle = ITS_Initialize(
                                ITS_ISUP                    |
                                ITS_TRANSPORT_FIFO          |
                                ITS_TRANSPORT_SINGLE_USER,
                                2);

#endif // defined(USE_SOCKETS)

    if (handle == NULL)
    {
        ITS_Error itsError(ITS_ENOTRANSPORT, __FILE__, __LINE__);

        cout << endl << itsError.GetDescription() << endl;

        THREAD_NORMAL_EXIT;
    }

    // To signal primary thread that the border transport thread is running and
    // that the associated transport is initialized.

    borderTransportSemaphore.Post();

    //ITS_Event event;

    cout << "Enter border: ITS_GetNextEvent loop" << endl;
    
    while (!current->stopRequested)
    {

        ITS_Event event;
        
        int res = ITS_GetNextEvent(handle, &event.GetEvent());

        if (res != ITS_SUCCESS)
        {
            ITS_Error itsError(res, __FILE__, __LINE__);

            cout << endl << itsError.GetDescription() << endl;
        }
        else
        {
            // Put event to main thread
            ITS_Transport::PutEvent(ITS_DEFAULT_USER_SRC, event);
        }
    }

    ITS_Terminate(handle);

    THREAD_NORMAL_EXIT;
}
