/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:45  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:12  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.10  2001/03/26 18:21:45  mmiers
 * LOG: Reversed operator.
 * LOG:
 * LOG: Revision 3.9  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 3.8  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.7  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.6  2001/03/06 02:17:17  mmiers
 * LOG: Work on circular dependencies, down to one cpp file.  Need to
 * LOG: modify exception compiler to get rid of this last dependency.
 * LOG: Then we get to eliminate two more lib copies.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2001/01/17 01:01:34  mmiers
 * LOG: Convert event log to C.  Add dispatch project.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:11  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:32  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.8  1998/11/18 15:14:46  mmiers
 * LOG: Correct for HPUX build.
 * LOG:
 * LOG: Revision 1.7  1998/11/18 00:50:40  mmiers
 * LOG: Implement UNIX versions of these.
 * LOG:
 * LOG: Revision 1.6  1998/06/01 19:06:23  mmiers
 * LOG: Fix minor formatting point.
 * LOG:
 * LOG: Revision 1.5  1998/06/01 18:56:37  hdivoux
 * LOG: Added documentation.
 * LOG:
 * LOG: Revision 1.4  1998/05/28 17:28:10  hdivoux
 * LOG: Improved the way event log and exception log work.
 * LOG: Improved the way event log and exception log are used by ITS_Service.
 * LOG:
 * LOG: Revision 1.3  1998/05/19 16:37:18  hdivoux
 * LOG: Fixed namespace related issues.
 * LOG:
 * LOG: Revision 1.2  1998/05/19 15:49:28  mmiers
 * LOG: Fix the namespace problems.
 * LOG:
 * LOG: Revision 1.1  1998/05/14 20:40:27  hdivoux
 * LOG: Added event log related files.
 * LOG:
 *
 ****************************************************************************/

#if !defined(_ITS_EVENT_LOG_H_)
#define _ITS_EVENT_LOG_H_

#include <its_object.h>

#ident "$Id: its_event_log.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

/*
 * duplicated below, stupid C++ compiler won't accept a typedef as a
 * namespace modifier.
 */
typedef enum
{
    LOG_EMERGENCY_TYPE     = 1,
    LOG_ALERT_TYPE         = 2,
    LOG_CRITICAL_TYPE      = 3,
    LOG_ERROR_TYPE         = 4,
    LOG_WARNING_TYPE       = 5,
    LOG_NOTICE_TYPE        = 6,
    LOG_INFORMATION_TYPE   = 7,
    LOG_DEBUG_TYPE         = 8,
    LOG_SUCCESS_AUDIT_TYPE = 9,
    LOG_FAILURE_AUDIT_TYPE = 10
}
ITS_EventType;

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * C API
 */
/*
 * object part
 */
typedef struct
{
    char  *srcName;
}
EVENTLOG_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    EVENTLOG_ObjectPart eventLog;
}
EVENTLOG_Manager;

#define EVENTLOG_SRC_NAME(x) \
    (((EVENTLOG_Manager *)(x))->eventLog.srcName)

/*
 * class part
 */
typedef void (*EVENTLOG_LogFuncPtr)(EVENTLOG_Manager *log,
                                    ITS_EventType type,
                                    const char *args);

typedef struct
{
    EVENTLOG_LogFuncPtr log;
}
EVENTLOG_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    EVENTLOG_ClassPart  eventLogClass;
}
EVENTLOG_ClassRec, *EVENTLOG_Class;

#define EVENTLOG_CLASS_LOG(x) \
    (((EVENTLOG_Class)(x))->eventLogClass.log)

#define EVENTLOG_NT_CLASSNAME   "NT Event Log"
#define EVENTLOG_UNIX_CLASSNAME "UNIX Event Log"

#if defined(WIN32)
ITSDLLAPI extern EVENTLOG_ClassRec    itsNT_EVENTLOG_ClassRec;
ITSDLLAPI extern ITS_Class            itsNT_EVENTLOG_Class;

ITSDLLAPI extern long NT_RegistryCreateSource(const char *srcName,
                                              const char *msgFileName);
ITSDLLAPI extern long NT_RegistryRemoveSource(const char *srcName);

#endif

#if defined(unix)
ITSDLLAPI extern EVENTLOG_ClassRec    itsUNIX_EVENTLOG_ClassRec;
ITSDLLAPI extern ITS_Class            itsUNIX_EVENTLOG_Class;
#endif

#if !defined(ITS_FASTCALL)

ITSDLLAPI EVENTLOG_Manager*   EVENTLOG_CreateLog(const char *srcName);
ITSDLLAPI void                EVENTLOG_DestroyLog(EVENTLOG_Manager *);

#else

#if defined(WIN32)

#define EVENTLOG_CreateLog(n)                                       \
    (EVENTLOG_Manager *)ITS_ConstructObject(itsNT_EVENTLOG_Class,   \
                                            (n));
#endif

#if defined(unix)

#define EVENTLOG_CreateLog(n)                                       \
    (EVENTLOG_Manager *)ITS_ConstructObject(itsUNIX_EVENTLOG_Class, \
                                            (n));

#endif

#define EVENTLOG_DestroyLog(x)                                      \
    ITS_DestructObject((ITS_Object)(x))

#endif /* ITS_FASTCALL */

ITSDLLAPI void    EVENTLOG_Log(EVENTLOG_Manager *, ITS_EventType, const char *string);

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#include <string>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:EventLog
 ****************************************************************************
 *  Interface:
 *      EventLog
 *
 *  Purpose:
 *         Event log abstract base class. All event log concrete classes inherit
 *      from this class. Contains the definition of all the event types that
 *      can be logged (e.g. LOG_ERROR_TYPE). Within the two straightforward
 *      descendants of this class (NtEventLog and UnixEventLog) the
 *      event types are mapped to their closest operating system equivalents.
 *      On NT, the event types must be matched with the ItsMsgFile DLL and
 *      therefore with the file MsgFile.mc. See the related directory named
 *      MsgFileDll.
 *
 *  Usage:
 *      Generally not used directly. However, can be used through inheritance to
 *      implement a specialized event log.
 *
 *
 ****************************************************************************/
class  EventLog
{
public:
    friend class Service;

    enum EventType
    {
        LOG_EMERGENCY_TYPE     = 1,
        LOG_ALERT_TYPE         = 2,
        LOG_CRITICAL_TYPE      = 3,
        LOG_ERROR_TYPE         = 4,
        LOG_WARNING_TYPE       = 5,
        LOG_NOTICE_TYPE        = 6,
        LOG_INFORMATION_TYPE   = 7,
        LOG_DEBUG_TYPE         = 8,
        LOG_SUCCESS_AUDIT_TYPE = 9,
        LOG_FAILURE_AUDIT_TYPE = 10
    };

    /*.implementation:public,abstract,EventLog
     ************************************************************************
     *  Purpose:
     *      Constructor
     *
     ************************************************************************/
    EventLog()
        : log(NULL)
    {
    }
    /*.implementation:public,abstract,EventLog
     ************************************************************************
     *  Purpose:
     *      Constructor
     *
     *  Input Parameters:
     *      logParam - log to use
     *
     ************************************************************************/
    EventLog(EVENTLOG_Manager *logParam)
        : log(logParam)
    {
    }


    /*.implementation:public,abstract,EventLog
     ************************************************************************
     *  Purpose:
     *      Constructor
     *
     *  Input Parameters:
     *      rhs - log to copy
     *
     ************************************************************************/
    EventLog(const EventLog& rhs)
    {
        log = rhs.log;
    }

    /*.implementation:public,abstract,EventLog
     ************************************************************************
     *  Purpose:
     *      Destructor
     *
     ************************************************************************/
    virtual ~EventLog()
    {
    }

    /*.implementation:public,abstract,EventLog
     ************************************************************************
     *  Purpose:
     *      assignment operator
     *
     *  Input Parameters:
     *      rhs - log to copy
     *
     ************************************************************************/
    EventLog&
    operator=(const EventLog& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
    
        return *this;
    }

    /*.implementation:public,abstract,EventLog
     ************************************************************************
     *
     *  Purpose:
     *      Get the event log's name
     *
     *  Return Value:
     *      string containing the name
     *
     ************************************************************************/
    const std::string
    GetSrcName()
    {
        return EVENTLOG_SRC_NAME(log);
    }

    /*.implementation:public,abstract,EventLog
     ************************************************************************
     *  Purpose:
     *      Deferred (i.e. pure virtual) member function to log an event to the
     *      current event log. To be implemented in all concrete heirs.
     *
     *  Input Parameters:
     *      text - text of the event to be logged.
     *      type - type of the event to be logged (see above EventType
     *             enumeration).
     *
     *  Notes:
     *      Success assumed by default.
     *
     ************************************************************************/
    virtual void 
    Log(const std::string& text, EventType type) = 0;

protected:
    EVENTLOG_Manager *log;
};



/*
 * NT specific code.
 */
#if defined(WIN32)

/*.interface:NtEventLog
 ****************************************************************************
 *  Interface:
 *      NtEventLog
 *
 *  Purpose:
 *      Represents the NT Event Log, or more precisely a source on the NT Event
 *      Log Application log file.
 *
 *  Usage:
 *      Recommended use is to create a static object at the begin of the
 *      application:
 *      
 *          static NtEventLog eventLog("Application name");
 *
 *      The installation procedure should create an entry for the "Application
 *      name" source in the NT registry by calling the static member function:
 *            
 *          RegistryCreateSource("Application name", "ItsMsgFile.dll");
 *
 *      As an alternative and temporary solution, the previous call can be done
 *      by the application itself.
 *
 *      To actually log an event, just do:
 *
 *          eventLog.Log("This is a warning event.", LOG_WARNING_TYPE);
 *      
 *
 ****************************************************************************/
class NtEventLog : public EventLog
{
public:
    /*.implementation:public,inline,NtEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Constructor.
     *
     *  Input Parameters:
     *      srcNameInit - name of the event source in the NT Event Log 
     *                    Application log file.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    NtEventLog(const std::string& srcNameInit)
        : EventLog()
    {
        log = (EVENTLOG_Manager *)ITS_ConstructObject(itsNT_EVENTLOG_Class,
                                                      srcNameInit.c_str());

        if (log == NULL)
        {
            throw GenericException();
        }
    }

    /*.implementation:public,inline,NtEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Constructor.
     *
     *  Input Parameters:
     *      copy to init from
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    NtEventLog(const NtEventLog& rhs)
        : EventLog(rhs)
    {
    }

    /*.implementation:public,inline,NtEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Constructor.
     *
     *  Input Parameters:
     *      manager to init from.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    NtEventLog(EVENTLOG_Manager *manager)
        : EventLog(manager)
    {
    }

    /*.implementation:public,inline,NtEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Destructor
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    virtual ~NtEventLog()
    {
    }

    /*.implementation:public,inline,NtEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Constructor.
     *
     *  Input Parameters:
     *      copy to duplicate
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    NtEventLog&
    operator=(const NtEventLog& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        this->EventLog::operator=(rhs);

        return *this;
    }

    /*.implementation:public,inline,NtEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Log a message
     *
     *  Input Parameters:
     *      type - event type
     *      text - text to log
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    virtual void
    Log(const std::string& text, EventType type)
    {
        EVENTLOG_CLASS_LOG(ITS_OBJ_CLASS(log))(log,
                                               (ITS_EventType)type,
                                               text.c_str());
    }

    /*.implementation:public,inline,NtEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Registry interface
     *
     *  Input Parameters:
     *      srcName - log name
     *      msgFileName - DLL name
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *
     *  See Also:
     *
     ************************************************************************/
    static long
    RegistryCreateSource(const std::string& srcName,
                         const std::string& msgFileName)
    {
        return NT_RegistryCreateSource(srcName.c_str(), msgFileName.c_str());
    }

    /*.implementation:public,inline,NtEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Registry interface
     *
     *  Input Parameters:
     *      srcName - log name
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *
     *  See Also:
     *
     ************************************************************************/
    static long
    RegistryRemoveSource(const std::string& srcName)
    {
        return NT_RegistryRemoveSource(srcName.c_str());
    }
};

#endif /* defined(WIN32) */

/*
 * Unix specific code.
 */
#if defined(unix)

/*.interface:UnixEventLog
 ****************************************************************************
 *  Interface:
 *      UnixEventLog
 *
 *  Purpose:
 *      Represents syslog.
 *
 *  Usage:
 *      Recommended use is to create a static object at the begin of the
 *      application:
 *      
 *          static UnixEventLog eventLog("Application name");
 *
 *      To actually log an event, just do:
 *
 *          eventLog.Log("This is a warning event.", LOG_WARNING_TYPE);
 *      
 *
 ****************************************************************************/
class UnixEventLog : public EventLog
{
public:
    /*.implementation:public,inline,UnixEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Constructor.
     *
     *  Input Parameters:
     *      srcNameInit - name of the event source in the syslog
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    UnixEventLog(const std::string& srcNameInit)
    {
        log = (EVENTLOG_Manager *)ITS_ConstructObject(itsUNIX_EVENTLOG_Class,
                                                      srcNameInit.c_str());


        if (log == NULL)
        {
            throw GenericException();
        }
    }

    /*.implementation:public,inline,UnixEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Constructor.
     *
     *  Input Parameters:
     *      copy to init from
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    UnixEventLog(const UnixEventLog& rhs)
        : EventLog(rhs)
    {
    }

    /*.implementation:public,inline,UnixEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Constructor.
     *
     *  Input Parameters:
     *      manager to init from
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    UnixEventLog(EVENTLOG_Manager *manager)
        : EventLog(manager)
    {
    }

    /*.implementation:public,inline,UnixEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Destructor.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    virtual ~UnixEventLog()
    {
    }

    /*.implementation:public,inline,UnixEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Assignment operator
     *
     *  Input Parameters:
     *      copy to duplicate
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    UnixEventLog&
    operator=(const UnixEventLog& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        this->EventLog::operator=(rhs);

        return *this;
    }

    /*.implementation:public,inline,UnixEventLog
     ************************************************************************
     *
     *  Purpose:
     *      Log a message
     *
     *  Input Parameters:
     *      type - event type
     *      text - text to log
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.       
     *
     *  Notes:
     *      Success assumed by default.
     *
     *  See Also:
     *
     ************************************************************************/
    virtual void
    Log(const std::string& text, EventType type)
    {
        EVENTLOG_CLASS_LOG(ITS_OBJ_CLASS(log))(log,
                                               (ITS_EventType)type,
                                               text.c_str());
    }
};

#endif /* defined(unix) */

#if defined(ITS_NAMESPACE)
}
#endif /* defined(ITS_NAMESPACE) */

#endif /* USE_CPLUSPLUS */

#endif /* !defined(_ITS_EVENT_LOG_H_) */
