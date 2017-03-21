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
// CONTRACT: Internal                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:49  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
// LOG: Convert RCSID to ident.
// LOG:
// LOG: Revision 3.3  2001/02/05 22:05:01  mmiers
// LOG: Move log back (more complaints than applause).
// LOG: Make C service take event log.
// LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
// LOG: bindings).
// LOG:
// LOG: Revision 3.2  2001/01/30 18:11:34  mmiers
// LOG: Demo log at bottom of file.
// LOG:
// LOG: Revision 3.1  2000/08/16 00:03:22  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.1  2000/06/13 19:15:54  mmiers
// LOG:
// LOG: C++ assertion no longer throws exception by default.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:25:44  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.3  1999/11/10 18:49:00  mmiers
// LOG:
// LOG:
// LOG: Don't need the namespace modifier, we're already in the its namespace.
// LOG:
// LOG: Revision 1.2  1999/07/07 16:39:43  hdivoux
// LOG: Minor update.
// LOG:
// LOG: Revision 1.1  1999/07/07 16:21:55  mmiers
// LOG:
// LOG:
// LOG: Add Hubert's singleton template to support.
// LOG:
// LOG: Revision 1.1  1999/06/25 20:55:51  hdivoux
// LOG: Creation.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////

#if !defined(_ITS_SINGLETON_H_)
#define _ITS_SINGLETON_H_

#include <its++.h>
#include <its_mutex.h>
#include <its_support_exception.h>

#ident "$Id: its_singleton.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

////////////////////////////////////////////////////////////////////////////////
//
//  Singleton.
//
template<class _T_>
class Singleton 
{
public:
    Singleton()
    {
        //
        // Note: Instance counter mechanism is not thread safe.
        //
        instanceCounter++;

        if (instanceCounter > 1)
        {
            bool only_one_instance_must_be_created = false;

            ITS_THROW_ASSERT(only_one_instance_must_be_created);
        }
    }

    virtual ~Singleton()
    {
        // Nothing to do.
    }

    static int Initialize();
    static int Terminate();

    static bool
    IsInitialized()
    {
        return initialized;
    }

    static _T_&
    GetShared()
    {
        ITS_REQUIRE(IsInitialized());

        return *shared;
    }

protected:
    static bool initialized;
    static _T_* shared;
    static long instanceCounter;

private:
    Singleton(const Singleton&) {};
    Singleton& operator=(const Singleton&) { return *this; }
};

//
//  Must be called only once.
//
template<class _T_>
int
Singleton<_T_>::Initialize()
{
    ITS_REQUIRE(!IsInitialized());

    shared = new _T_;

    initialized = true;

    ITS_ENSURE(shared != NULL);

    return ITS_SUCCESS;
}

//
//  Must be called only once.
//
template<class _T_>
int
Singleton<_T_>::Terminate()
{
    ITS_REQUIRE(IsInitialized());

    if (shared)
    {
        delete shared;

        shared = NULL;
    }

    initialized = false;

    return ITS_SUCCESS;
}

//
//  Definition of static members.
//
template<class _T_> bool Singleton<_T_>::initialized = false;
template<class _T_> _T_* Singleton<_T_>::shared = NULL;
template<class _T_> long Singleton<_T_>::instanceCounter = 0;


////////////////////////////////////////////////////////////////////////////////
//
//  SingletonMultithreaded.
//
template<class _T_>
class SingletonMultithreaded : public Singleton<_T_>
{
public:

    SingletonMultithreaded()
        : Singleton<_T_>()
    {}   

    virtual ~SingletonMultithreaded()
    {
        // Nothing to do.
    }

    static int Initialize();
    static int Terminate();

    static int Lock();
    static int Unlock();

protected:
    static Mutex* gate;

private:
    SingletonMultithreaded(const SingletonMultithreaded&) {}
    SingletonMultithreaded& operator=(const SingletonMultithreaded&)
    { return *this; }
};

//
//  Must be called only once.
//
template<class _T_> 
int
SingletonMultithreaded<_T_>::Initialize()
{
    int res = Singleton<_T_>::Initialize();

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    try 
    {
        gate = new Mutex(0);
    }
    catch (Error& exc)
    {
        return exc.GetErrorNumber();
    }

    return ITS_SUCCESS;
}

//
//  Must be called only once.
//
template<class _T_> 
int
SingletonMultithreaded<_T_>::Terminate()
{
    // Reverse order than Initialize().

    delete gate;

    gate = NULL;

    int res = Singleton<_T_>::Terminate();

    return res;
}

//
//  Lock singleton.
//
template<class _T_>
int
SingletonMultithreaded<_T_>::Lock()
{
    ITS_THROW_ASSERT(gate != NULL);

    int res = gate->Acquire();

    return res;
}

//
//  Unlock singleton.
//
template<class _T_>
int
SingletonMultithreaded<_T_>::Unlock()
{
    ITS_THROW_ASSERT(gate != NULL);

    int res = gate->Release();

    return res;
}

//
//  Definition of static members.
//
template<class _T_> Mutex* SingletonMultithreaded<_T_>::gate = NULL;


#if defined(ITS_NAMESPACE)
}
#endif

#endif  // !defined(_ITS_SINGLETON_H_)
