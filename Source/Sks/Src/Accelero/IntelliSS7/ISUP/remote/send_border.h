//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.   //
//              Manufactured in the United States of America.               //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.      //
//                                                                          //
//    This product and related documentation is protected by copyright and  //
//    distributed under licenses restricting its use, copying, distribution //
//    and decompilation.  No part of this product or related documentation  //
//    may be reproduced in any form by any means without prior written      //
//    authorization of IntelliNet Technologies and its licensors, if any.   //
//                                                                          //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     //
//    government is subject to restrictions as set forth in subparagraph    //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software      //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// CONTRACT: INTERNAL                                                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: send_border.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
//
//////////////////////////////////////////////////////////////////////////////

#include <its++.h>
#include <its_thread.h>

/////////////////////////////////////////////////////////////////////////////
//
//  Border transport thread class
//

class BorderTransportThread : public its::ITS_Thread
{
public:

    BorderTransportThread()
        :   Thread(0, (ITS_THREAD_FUNC)DispatchFunction),
        stopRequested(false)
    {}

    virtual ~BorderTransportThread() {}

    void 
    StopRequested()
    { stopRequested = true; }

    bool 
    IsStopRequested() const
    { return stopRequested; }
  
    static THREAD_RET_TYPE DispatchFunction(void* arg);

protected:

    bool stopRequested;
};


