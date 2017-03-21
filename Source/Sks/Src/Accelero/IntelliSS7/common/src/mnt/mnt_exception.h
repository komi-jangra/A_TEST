///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     //
//             Manufactured in the United States of America.                 //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:27  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:18  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:31  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:52  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.2  2001/08/07 21:52:59  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_exception.h,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

//
//
// mnt_exception.h: MNT exception.
//
//


#if !defined(_MNT_EXCEPTION_H_)
#define _MNT_EXCEPTION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <mnt.h>
#include <mnt_helpers.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)


///////////////////////////////////////////////////////////////////////////////
//
// MntError.
//

class MntError : public its::GenericException 
{
public:

    MntError(
        const std::string& information,
        size_t lineNumber, 
        size_t columnNumber,
        int error) 
    :   its::GenericException("Mnt error")
    { 
        Initialize(information, lineNumber, columnNumber, error); 
    }

    MntError(
        const std::string& information, 
        size_t lineNumber, 
        size_t columnNumber,
        int error,
        const std::string& file, 
        size_t line) 
    :   its::GenericException("Mnt error", file, line)
    { 
        Initialize(information, lineNumber, columnNumber, error); 
    }

    virtual ~MntError() ITS_THROW_SPEC_NULL
    {}

    const std::string& 
    GetInformation() const 
    { 
        return _information; 
    }

    size_t 
    GetLineNumber() const
    { 
        return _lineNumber; 
    }

    size_t 
    GetColumnNumber() const
    { 
        return _columnNumber; 
    }

    int
    GetError() const
    {
        return _error;
    }

protected:

    void Initialize(
                const std::string& information, 
                size_t lineNumber, 
                size_t columnNumber, 
                int error);

    std::string _information;
    size_t      _lineNumber;
    size_t      _columnNumber;
    int         _error;

};


//
//  Helper macro to throw MNT error.
//

#define MNT_THROW_ERROR(                \
                    information,        \
                    lineNumber,         \
                    columnNumber,       \
                    error)              \
    throw mnt::MntError(                \
                (information),          \
                (lineNumber),           \
                (columnNumber),         \
                (error));


#define MNT_THROW_ERROR_VARARGS(                                    \
                    information,                                    \
                    lineNumber,                                     \
                    columnNumber,                                   \
                    error)                                          \
{                                                                   \
    std::string informationStr = mnt::GetVarArgsString information; \
    throw mnt::MntError(                                            \
                (informationStr),                                   \
                (lineNumber),                                       \
                (columnNumber),                                     \
                (error));                                           \
}
    


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_MNT_EXCEPTION_H_)
