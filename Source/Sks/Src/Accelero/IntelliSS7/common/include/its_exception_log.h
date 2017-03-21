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
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:45  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.3  2002/05/28 17:01:35  hdivoux
// LOG: Put back inline specifier (without CC or GCC linker says multiple defines).
// LOG:
// LOG: Revision 6.2  2002/05/24 20:52:34  hdivoux
// LOG: Removed inline specifier (hazardous if function has statics).
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.2  2001/06/16 00:03:42  mmiers
// LOG: Various fixes from PR4.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.8  2001/03/06 23:54:43  mmiers
// LOG: Shrink comment blocks for readability.
// LOG:
// LOG: Revision 3.7  2001/03/06 22:01:23  mmiers
// LOG: New statics file for CPP globals.  Down to one SUPPORT lib.
// LOG:
// LOG: Revision 3.6  2001/03/06 02:31:18  mmiers
// LOG: Correct formatting.
// LOG:
// LOG: Revision 3.5  2001/03/06 02:17:17  mmiers
// LOG: Work on circular dependencies, down to one cpp file.  Need to
// LOG: modify exception compiler to get rid of this last dependency.
// LOG: Then we get to eliminate two more lib copies.
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
// LOG: Revision 3.2  2001/01/30 18:11:33  mmiers
// LOG: Demo log at bottom of file.
// LOG:
// LOG: Revision 3.1  2000/08/16 00:03:12  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:25:33  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.6  1998/11/18 01:03:55  mmiers
// LOG: Build event log/exception log on UNIX
// LOG:
// LOG: Revision 1.5  1998/06/01 20:10:19  hdivoux
// LOG: Added documentation.
// LOG:
// LOG: Revision 1.4  1998/05/28 17:28:10  hdivoux
// LOG: Improved the way event log and exception log work.
// LOG: Improved the way event log and exception log are used by ITS_Service.
// LOG:
// LOG: Revision 1.3  1998/05/20 15:02:07  mmiers
// LOG: Minor tweaks for Solaris builds.
// LOG:
// LOG: Revision 1.2  1998/05/19 15:49:29  mmiers
// LOG: Fix the namespace problems.
// LOG:
// LOG: Revision 1.1  1998/05/14 20:40:27  hdivoux
// LOG: Added event log related files.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////

//
//
// Exception log header.
//
//

#if !defined(_ITS_EXCEPTION_LOG_H_)
#define _ITS_EXCEPTION_LOG_H_

#include <string>
#include <its++.h>    // For ITS_NAMESPACE.
#include <its_exception.h>
#include <its_event_log.h>

#ident "$Id: its_exception_log.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

// Namespaces.

#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)

// Forward declarations.
class GenericException;


//.interface:ExceptionLog
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      ExceptionLog
//
//  Purpose:
//	    Exception log abstract base class. All exception log concrete classes
//      inherit from this class which uses directly the services of the class
//      EventLog (client - supplier relationship). An exception is always
//      logged as an event of type error (i.e. LOG_ERROR_TYPE), see class 
//      EventLog for more information.
//
//  Usage:
//      Generally not used directly. However, can be used through inheritance to
//      implement a specialized exception log.
//
//
////////////////////////////////////////////////////////////////////////////////
class ExceptionLog
{

public:

    ExceptionLog() : eventLog(NULL)
    {
    }

    ExceptionLog(const ExceptionLog& rhs)
    { eventLog = rhs.eventLog; }

    virtual ~ExceptionLog() {};

    ExceptionLog&  operator=(const ExceptionLog& rhs)
    {
        if (this == &rhs) return *this;

        eventLog = rhs.eventLog;

        return *this;
    }

    //.implementation:public,abstract,ExceptionLog
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Deferred (i.e. pure virutal) member function to log an exception to
    //      the current exception log. To be implemented in all concrete heirs.
    //
    //  Input Parameters:
    //      genericException - generic exception to be logged.
    //
    //  Notes:
    //      Success assumed by default.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    Log(GenericException& genericException) = 0;

protected:

    EventLog* eventLog;
};


//
// NT specific code.
//

#if defined(WIN32)

//.interface:NtExceptionLog
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      NtExceptionLog
//
//  Purpose:
//      Represents the NT Exception Log, or more precisely a source on the NT
//      Event Log Application log file. Only exceptions can be logged via an
//      instance of this class (an exception is considered to be an event ofs
//      type error by definition, see class EventLog for more information).
//
//  Usage:
//      Recommended use is to create a static object at the begin of the
//      application:
//      
//          static NtExceptionLog exceptiontLog("Application name");
//
//      The installation procedure should create an entry for the "Application
//      name" source in the NT registry by calling the static member function
//      RegistryCreateSource of the class ITS_NtEventLog:
//            
//          RegistryCreateSource("Application name", "ItsMsgFile.dll");
//
//      As an alternative and temporary solution, the previous call can be done
//      by the application itself.
//
//      The application should also set the exception log for all exceptions:
//
//          GenericException::SetExceptionLog(exceptionLog);
//
//
//      Then to actually log an exception, just do something like:
//
//          ...
//          
//          catch(GenericException& exc)
//          {
//              exc.Log();
//          }
//      
//
////////////////////////////////////////////////////////////////////////////////
class NtExceptionLog : public ExceptionLog {

public:
    //.implementation:public,inline,NtExceptionLog
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      srcNameInit - name of the event source in the associated NT Event
    //      Log.
    //
    //  Notes:
    //      Success assumed by default.
    //
    ////////////////////////////////////////////////////////////////////////////
    NtExceptionLog(const std::string& srcNameInit)
        : ExceptionLog()
    {
        eventLog = new NtEventLog(srcNameInit);
    }

    NtExceptionLog(const NtExceptionLog& rhs)
        : ExceptionLog(rhs)
    {
    }

    //.implementation:public,inline,NtExceptionLog
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    //  Notes:
    //      Success assumed by default.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~NtExceptionLog()
    {
        delete eventLog;
    }

    NtExceptionLog& operator=(const NtExceptionLog& rhs)
    {
        if (this == &rhs) return *this;

        this->ExceptionLog::operator=(rhs);

        return *this;
    }

    //.implementation:public,inline,NtExceptionLog
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Log an exception to the NT Event Log "Application log file".
    //
    //  Input Parameters:
    //      genericException - generic exception to be logged.
    //
    //  Notes:
    //      An exception is always logged as an event of type error.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    Log(GenericException& genericException)
    {
        // A logged exception is always considered as an error.

        eventLog->Log(genericException.GetDescription(),
                      EventLog::LOG_ERROR_TYPE);
    }
};

#endif    // defined(WIN32)


//
// Unix specific code (should use syslog).
// 


#if defined(unix)

//.interface:UnixExceptionLog
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      UnixExceptionLog
//
//  Purpose:
//      Represents Unix Syslog to allow logging of exceptions.
//
//  Usage:
//      Not implemented yet.      
//
////////////////////////////////////////////////////////////////////////////////
class UnixExceptionLog : public ExceptionLog {

public:

    //
    //.implementation:public,inline,UnixExceptionLog
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      srcNameInit - name of the event log
    //
    //  Notes:
    //      Success assumed by default.
    //
    ////////////////////////////////////////////////////////////////////////////
    UnixExceptionLog(const std::string& srcNameInit)
        : ExceptionLog()
    {
        eventLog = new UnixEventLog(srcNameInit);
    }

    UnixExceptionLog(const UnixExceptionLog& rhs)
        : ExceptionLog(rhs)
    {
    }

    //.implementation:public,inline,UnixExceptionLog
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    //  Notes:
    //      Success assumed by default.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~UnixExceptionLog()
    {
        delete eventLog;
    }

    UnixExceptionLog& operator=(const UnixExceptionLog& rhs)
    {
        if (this == &rhs) return *this;

        this->ExceptionLog::operator=(rhs);

        return *this;
    }

    //.implementation:public,inline,UnixExceptionLog
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Log an exception to the syslog
    //
    //  Input Parameters:
    //      genericException - generic exception to be logged.
    //
    //  Notes:
    //      An exception is always logged as an event of type error.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    Log(GenericException& genericException)
    {
        // A logged exception is always considered as an error.

        eventLog->Log(genericException.GetDescription(),
                      EventLog::LOG_ERROR_TYPE);
    }
};

#endif    // defined(unix)

//
// This is a little weird.  In order to avoid a circular dependency, it's
// necessary though.
//
//.implementation:public,GenericException
////////////////////////////////////////////////////////////////////////////
//
//  Purpose:
//      Log the current exception to the preselected exception log (see
//      member function SetExceptionLog). If the exception log has not been
//      set, then a default exception log is used. Under NT, the name of
//      the NT Event Log source associated with the default exception log
//      is "ITS".
//
////////////////////////////////////////////////////////////////////////////
inline void
GenericException::Log()
{
    Format();

    if (its_intern_exceptionLog == NULL)
    {
#if defined(WIN32)
        NtEventLog::RegistryCreateSource("ITS", "ItsMsgFile.dll");

        static NtExceptionLog exceptionLogDefault("ITS");

        its_intern_exceptionLog = &exceptionLogDefault;
#elif defined(unix)
        static UnixExceptionLog exceptionLogDefault("ITS");

        its_intern_exceptionLog = &exceptionLogDefault;
#endif
        return;
    }

    if (its_intern_exceptionLog)
    {
        its_intern_exceptionLog->Log(*this);
    }
}

#if defined(ITS_NAMESPACE)
}
#endif    // defined(ITS_NAMESPACE)


#endif    // !defined(_ITS_EXCEPTION_LOG_H_)
