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
// LOG: Revision 8.3  2005/03/21 13:50:45  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2001/11/08 16:16:11  mmiers
// LOG: Make sure things compile without its_bc.h.  Fix MutexGuard.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.2  2001/06/16 00:03:42  mmiers
// LOG: Various fixes from PR4.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.13  2001/04/11 21:30:11  mmiers
// LOG: Apparently declspecs don't apply to static member variables.
// LOG:
// LOG: Revision 3.12  2001/03/14 22:06:44  mmiers
// LOG: Finalizing the engine.  Just need to do the thread pools.
// LOG:
// LOG: Revision 3.11  2001/03/09 18:33:24  mmiers
// LOG: Convert to DLL modifier.
// LOG:
// LOG: Revision 3.10  2001/03/06 23:54:43  mmiers
// LOG: Shrink comment blocks for readability.
// LOG:
// LOG: Revision 3.9  2001/03/06 22:01:23  mmiers
// LOG: New statics file for CPP globals.  Down to one SUPPORT lib.
// LOG:
// LOG: Revision 3.8  2001/03/06 15:59:21  mmiers
// LOG: Portability fixes.
// LOG:
// LOG: Revision 3.7  2001/03/06 02:28:38  mmiers
// LOG: Add dynamic link lib.  Straighten out include order.  Remove instance
// LOG: of CORE++.
// LOG:
// LOG: Revision 3.6  2001/03/06 02:17:17  mmiers
// LOG: Work on circular dependencies, down to one cpp file.  Need to
// LOG: modify exception compiler to get rid of this last dependency.
// LOG: Then we get to eliminate two more lib copies.
// LOG:
// LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
// LOG: Convert RCSID to ident.
// LOG:
// LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
// LOG: Move log back (more complaints than applause).
// LOG: Make C service take event log.
// LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
// LOG: bindings).
// LOG:
// LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
// LOG: Demo log at bottom of file.
// LOG:
// LOG: Revision 3.2  2001/01/17 16:04:03  mmiers
// LOG: Symbol collision on vxWorks
// LOG:
// LOG: Revision 3.1  2000/08/16 00:03:11  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.2  2000/05/01 19:57:38  hdivoux
// LOG: Correction.
// LOG:
// LOG: Revision 2.1  2000/05/01 19:53:31  hdivoux
// LOG: Update to use its_assertion.h macros.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:25:33  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.16  1999/08/18 16:47:39  hdivoux
// LOG: Added ITS_ASSERT_PRINT macro.
// LOG:
// LOG: Revision 1.15  1999/06/30 23:04:14  mmiers
// LOG:
// LOG:
// LOG: Make format string const for warning avoidance
// LOG:
// LOG: Revision 1.14  1999/06/29 23:20:06  mmiers
// LOG:
// LOG:
// LOG: Remove "using namespace std;" from here.
// LOG:
// LOG: Revision 1.13  1999/06/28 23:19:02  skarmakar
// LOG:
// LOG:
// LOG: Many many portability fixes.
// LOG:
// LOG: Revision 1.12  1999/06/28 19:13:26  skarmakar
// LOG:
// LOG:
// LOG: Update with awareness of throw specifiers.
// LOG:
// LOG: Revision 1.11  1999/06/28 18:58:38  skarmakar
// LOG:
// LOG:
// LOG: Add support for throw lists.  Add #defines for STD namespace,
// LOG: namespaces in general, and throw specifiers.
// LOG:
// LOG: Revision 1.10  1998/06/03 16:13:41  hdivoux
// LOG: Modification for doc generator.
// LOG:
// LOG: Revision 1.9  1998/06/02 00:18:42  hdivoux
// LOG: Added documentation.
// LOG:
// LOG: Revision 1.8  1998/05/19 22:48:20  hdivoux
// LOG: Added exception compiler.
// LOG:
// LOG: Revision 1.7  1998/05/19 16:37:18  hdivoux
// LOG: Fixed namespace related issues.
// LOG:
// LOG: Revision 1.6  1998/05/19 15:49:29  mmiers
// LOG: Fix the namespace problems.
// LOG:
// LOG: Revision 1.5  1998/05/19 02:36:13  mmiers
// LOG: A little oops here, I think.  While protecting code with
// LOG: #ifdef ITS_NAMESPACE
// LOG: it's probably a good idea to move code that uses its:: inside the namespace
// LOG: block, and remove the its::, isn't it?  Otherwise, compilers that don't
// LOG: understand namespaces will choke.  Umm, like g++.
// LOG:
// LOG: Revision 1.4  1998/05/14 20:40:27  hdivoux
// LOG: Added event log related files.
// LOG:
// LOG: Revision 1.3  1998/05/08 00:36:41  hdivoux
// LOG: Added files its_exception.h and its_exception.cpp.
// LOG:
//
//////////////////////////////////////////////////////////////////////////////// 

//////////////////////////////////////////////////////////////////////////////// 
//
// To include the exception classes generated
// by the exception compiler.

#include <its_support_exception.h>

//
//
// Geneneric exception header.
//
//

#if !defined(_ITS_EXCEPTION_H_)
#define _ITS_EXCEPTION_H_

#include <stdarg.h>
#include <exception>
#include <string>
#if defined(WIN32)
#pragma warning(disable : 4786)
#else // !defined(WIN32)
#include <stdio.h>

#include <its_assertion.h>

#ident "$Id: its_exception.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#define ITS_PRECONDITION_PRINT  ITS_C_PRECONDITION_PRINT
#define ITS_POSTCONDITION_PRINT ITS_C_POSTCONDITION_PRINT
#define ITS_INVARIANT_PRINT     ITS_C_INVARIANT_PRINT
#define ITS_ASSERT_PRINT        ITS_C_ASSERT_PRINT


#endif // defined(WIN32)

#include <list>
#include <its++.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)

#define EXC_MAX_FIELD_SIZE 32768

// forward (NT is silly)
class ExceptionLog;
extern ITSDLLAPI ExceptionLog*  its_intern_exceptionLog;// Initialized to NULL.

//.interface:GenericException
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      GenericException
//
//  Purpose:
//      Exception base class. All exceptions should inherit from this class.
//      Usually, each subsystem should include an exception definition file 
//      (extension is .exc). The exception C++ classes for a subsystem are
//      generated from its exception definition file by the exception compiler.
//      (See the exception compiler documentation for more information.) 
//
//      Each exception (generated or not) must be tagged by a unique identifier
//      (UID). The unique identifier is a 32 bits value and is composed of two
//      equal parts: the subsytem number and the exception number.
//      
//      The UID mapping is the following: 
//
//           31                16 15                 0
//          -------------------------------------------
//          |  subsystem number  |  exception number  |
//          -------------------------------------------
//
//      The subystem numbers from the interval [1, 2048] are reserved for 
//      IntelliSS7. Applications built on top of IntelliSS7 are free to use
//      the remaining numbers [2049, 65535]. Subsystem number 0 is reserved for
//      the class GenericException itself. Within each subsystem, an
//      exception is uniquely identified by its number [1, 65535]. Exception
//      number 0 is reserved for the class GenericException itself. The
//      subsystem numbers must be unique accross a whole application.
//
//      The GenericException class manages a list of strings (named fields).
//      Three predefined (but optional) fields exist:
//      o reason - describes the reason of the exception.
//      o file   - the file name where the exception has been thrown (to be used
//                 with the standard macro __FILE__).
//      o line   - the line where the exception has been thrown (to be used with
//                 the standard macro __LINE__).
// 
//      When the exception is formatted (before been logged or before getting 
//      the exception description), a relevant string (named description) is
//      built from the list of strings (fields). 
//
//  Usage:
//      Generally not used directly. The exception classes based on 
//      GenericException should be generated by the exception compiler. If 
//      a descendant class is hand written, then the UID must be very carefully
//      attributed.
//
////////////////////////////////////////////////////////////////////////////////
class GenericException : public std::exception {

public:
    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Default constructor.  Should never be used.  All attributes of the
    //      object are set to default values.
    //
    ////////////////////////////////////////////////////////////////////////////
    GenericException()
        : exception(), reason(""), file(""), line(0), uid(0)
    {
    }

    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor
    //
    //  Input Parameters:
    //      reasonParam - string that describes the reason of the exception.
    //
    ////////////////////////////////////////////////////////////////////////////
    GenericException(const std::string& reasonParam)
        : exception(), reason(reasonParam), file(""), line(0), uid(0)
    {
    }

    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor
    //
    //  Input Parameters:
    //      reasonParam - string that describes the reason of the exception.
    //      fileParam   - the file name where the exception has been thrown.
    //                    Usually the standard macro __FILE__.
    //      lineParam   - the file line where the exception has been thrown.
    //                    Usually the standard macro __LINE__.
    //
    ////////////////////////////////////////////////////////////////////////////
    GenericException(const std::string& reasonParam, 
                     const std::string& fileParam,
                     unsigned long lineParam)
        : exception(), reason(reasonParam),
          file(fileParam), line(lineParam), uid(0)
    {
    }

    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~GenericException() ITS_THROW_SPEC_NULL
    {
    }

    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Description of the exception (all the fields of the exception are
    //      concatenated in relevant string).
    //
    //  Return Value:
    //      const string& - reference to the description of the exception.
    //
    ////////////////////////////////////////////////////////////////////////////
    const std::string&
    GetDescription()
    {
        Format();
        return description;
    }

    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Reason of the exception.
    //
    //  Return Value:
    //      const std::string& - reference to the reason of the exception.
    //
    //  Notes:
    //      Default return value is "".
    //
    ////////////////////////////////////////////////////////////////////////////
    const std::string& 
    GetReason()
    { return reason; }


    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      File name where the exception has been thrown.
    //
    //  Return Value:
    //      const std::string& - reference to the file name where the exception
    //                           has been thrown.
    //
    //  Notes:
    //      Default return value is "".
    //
    //      The file name is stripped (i.e. not the full path). The full path
    //      is relevant only on the machine where the code has been built and
    //      usually irrelevant everywhere else.
    //
    ////////////////////////////////////////////////////////////////////////////
    const std::string&
    GetFile()
    { return file;   }


    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      File line where the exception has been thrown.
    //
    //  Return Value:
    //      unsigned long - file line where the exception has been thrown.
    //
    //  Notes:
    //      Default return value is 0 (invalid value for a file line).
    //
    ////////////////////////////////////////////////////////////////////////////
    unsigned long
    GetLine()
    { return line;   }


    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Unique identifier of the exception.
    //
    //  Return Value:
    //      unsigned long - unique identifier of the exception.
    //
    //  Notes:
    //      Default return value is 0 (class GenericException UID).
    //
    ////////////////////////////////////////////////////////////////////////////
    unsigned long
    GetUid()
    { return uid; }


    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Subsytem number of the exception (unique across a whole 
    //      application).
    //
    //  Return Value:
    //      unsigned short - subsystem number of the exception.
    //
    //  Notes:
    //      Default return value is 0 (class GenericException subsytem
    //      number).
    //
    ////////////////////////////////////////////////////////////////////////////
    unsigned short 
    GetSubsystemNumber()
    { return (unsigned short)(uid >> 16); }


    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Number of the exception (unique across a subsystem).
    //
    //  Return Value:
    //      unsigned short - number of the exception.
    //
    //  Notes:
    //      Default return value is 0 (class GenericException number).
    //
    ////////////////////////////////////////////////////////////////////////////
    unsigned short     
    GetNumber()
    { return (unsigned short)uid; }


    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Backwards compatibility method.  Same as log.  Use is deprecated.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    Register()
    {
        Log();
    }


    //.implementation:public,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Set the exception log used when an exception is actually logged.
    //      If the exception log is not set, a default exception log is used.
    //      Under NT, the name of the NT Event Log source associated with the
    //      default exception log is "ITS".
    //
    //  Input Parameters:
    //      exceptionLogParam - exception log to be set.
    //
    //  Notes:
    //      Success assumed.
    //
    ////////////////////////////////////////////////////////////////////////////
    static void   SetExceptionLog(ExceptionLog& exceptionLogParam)
    { its_intern_exceptionLog = &exceptionLogParam; }

    // This is actually implemented in its_exception_log.h
    void Log();

protected:

    std::string   reason;
    std::string   file;
    unsigned long line;

    std::list<std::string>      fields;

    //.implementation:protected,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Insert a field in the current exception. Generally called within the
    //      constructor of an heir. The corresponding code is also automatically
    //      generated by the exception compiler.
    //
    //  Input Parameters:
    //      format - a printf style format string.
    //       ...   - variable list of arguments compatible with what is
    //               specified by the format string.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    InsertField(const char* format, ...)
    {
        va_list argp;

        char *buffer = new char[EXC_MAX_FIELD_SIZE];

        va_start(argp, format);

        vsprintf(buffer, format, argp);

        va_end(argp);

        std::string field(buffer);

        delete [] buffer;

        fields.push_back(field);
    }

    //.implementation:protected,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Set the subsystem number of the current exception. Generally called
    //      within the constructor of an heir. The corresponding code is also
    //      automatically generated by the exception compiler.
    //
    //  Input Parameters:
    //      number - subsystem number (must belong to [2049, 65535] if is not a
    //               subsystem of IntelliSS7).
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetSubsystemNumber(unsigned short number)
    {
        uid = (unsigned long)number << 16 | uid & 0x0000FFFF;
    }

    //.implementation:protected,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Set the number of the current exception within its subsystem.
    //      Generally called within the constructor of an heir. The
    //      corresponding code is also automatically generated by the exception
    //      compiler.
    //
    //  Input Parameters:
    //      number - exception number (must belong to [1, 65535]).
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetNumber(unsigned short number)
    {
        uid = (unsigned long)number | uid & 0xFFFF0000;
    }

private:

    //.implementation:private,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Format the current exception by concatenating all the fields in a
    //      relevant string that describes the exception.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    Format()
    {
        description.erase(description.begin(), description.end());

        description.append("[ ");

        if (!reason.empty())
        {
            description.append(reason);
        }
        else
        {
            description.append("Reason not specified");
        }

        for (std::list<std::string>::iterator iter = fields.begin();
             iter != fields.end(); ++iter)
        {
            if (!(*iter).empty())
            {
                description.append(" | ");
                description.append((*iter));
            }
        }

        if (!file.empty() && line != 0)
        {
            char ulStr[16];

            description.append(" | File <");
            std::string fileStripped = StripPath(file);
            description.append(fileStripped);
            description.append("> | Line <");
            sprintf(ulStr, "%lu", line);
            description.append(ulStr);
            description.append(">");
        }

        if (true)
        {
            char ulStr[16];

            description.append(" | Uid <");
            sprintf(ulStr, "%lu", uid);
            description.append(ulStr);
            description.append(">");
        }

        description.append(" ]");
    }

    //.implementation:private,inline,GenericException
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Strip the path from a complete file name (e.g.
    //      "/dir1/dir2/fileName" --> "fileName").
    //
    //  Input Parameters:
    //      fileName - a complete (or incomplete file name).
    //
    //  Return Value:
    //      string - a stripped file name.
    //
    ////////////////////////////////////////////////////////////////////////////
    std::string
    StripPath(const std::string& fileName)
{
#if defined(WIN32)
        char separator = '\\';
#else
        char separator = '/';
#endif    // defined(WIN32)

        std::string::size_type position = fileName.find_last_of(separator);

        if (position == std::string::npos)
        {
            return fileName;
        }
        else
        {
            return fileName.substr(position + 1);
        }
    }

    unsigned long uid;

    std::string   description;
};

#if defined(ITS_NAMESPACE)
}
#endif    // defined(ITS_NAMESPACE)

#include <its_exception_log.h>

#endif    // !defined(_ITS_EXCEPTION_H_)

