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
//  ID: $Id: asncc_assertion.h,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
// Assertion interface.
//

#if !defined(_ASNCC_ASSERTION_H_)
#define _ASNCC_ASSERTION_H_

#include <asncc.h>
#include <asncc_util.h>

#if defined(WIN32)                                       
#include <crtdbg.h>                    
#endif // defined(WIN32)



////////////////////////////////////////////////////////////
//
//  GenericException.
//

class GenericException : public std::exception 
{
public:

    GenericException();

    GenericException(const std::string& reasonParam);

    GenericException(const std::string& reasonParam, 
                     const std::string& fileParam,
                     unsigned long lineParam);

    ~GenericException() ITS_THROW_SPEC_NULL;

    void                    Register();
    const std::string&      Description();

    const std::string&      GetReason()     { return reason; }
    const std::string&      GetFile()       { return file;   }
    unsigned long           GetLine()       { return line;   }

protected:

    std::string             reason;
    std::string             file;
    unsigned long           line;
    std::list<std::string>  fields;

private:

    void                    Format();
    std::string             description;

};


////////////////////////////////////////////////////////////
//
//  Assert.
//

class Assert : public GenericException 
{
public:

    Assert(const std::string& reason,
           const std::string& fileParam,
           unsigned long lineParam) 
    :   GenericException(reason, fileParam, lineParam) {};

    ~Assert() ITS_THROW_SPEC_NULL {};

};


////////////////////////////////////////////////////////////
//
//  Precondition.
//

class Precondition : public GenericException 
{ 
public:

    Precondition(const std::string& reason,
                 const std::string& fileParam,
                 unsigned long lineParam)
    :   GenericException(reason, fileParam, lineParam) {};

    ~Precondition() ITS_THROW_SPEC_NULL {};

};


////////////////////////////////////////////////////////////
//
//  Postcondition.
//

class Postcondition : public GenericException 
{
public:

    Postcondition(const std::string& reason,
                  const std::string& fileParam,
                  unsigned long lineParam)
    :   GenericException(reason, fileParam, lineParam) {};

    ~Postcondition() ITS_THROW_SPEC_NULL {};

};


////////////////////////////////////////////////////////////
//
//  Invariant.
//

class Invariant : public GenericException
{
public:

    Invariant(const std::string& reason,
              const std::string& fileParam,
              unsigned long lineParam)
    :   GenericException(reason, fileParam, lineParam) {};

    ~Invariant() ITS_THROW_SPEC_NULL {};

};


#if defined(WIN32)

#define ASSERT(expression)                                                              \
    _ASSERTE(expression);                                                               \
    if (!(expression))                                                                  \
    {                                                                                   \
        throw Assert(#expression, StripPath(__FILE__), __LINE__);                       \
    }


#define REQUIRE(expression)                                                             \
    _ASSERTE(expression);                                                               \
    if (!(expression))                                                                  \
    {                                                                                   \
        throw Precondition(#expression, StripPath(__FILE__), __LINE__);                 \
    }


#define ENSURE(expression)                                                              \
    _ASSERTE(expression);                                                               \
    if (!(expression))                                                                  \
    {                                                                                   \
        throw Postcondition(#expression, StripPath(__FILE__), __LINE__);                \
    }
    

#define INVARIANT(expression)                                                           \
    _ASSERTE(expression);                                                               \
    if (!(expression))                                                                  \
    {                                                                                   \
        throw Invariant(#expression, StripPath(__FILE__), __LINE__);                    \
    }


#else // !defined(WIN32)

#define ASSERT(expression)                                                              \
    if (!(expression))                                                                  \
    {                                                                                   \
        throw Assert(#expression, StripPath(__FILE__), __LINE__);                       \
    }

#define REQUIRE(expression)                                                             \
    if (!(expression))                                                                  \
    {                                                                                   \
        throw Precondition(#expression, StripPath(__FILE__), __LINE__);                 \
    }

#define ENSURE(expression)                                                              \
    if (!(expression))                                                                  \
    {                                                                                   \
        throw Postcondition(#expression, StripPath(__FILE__), __LINE__);                \
    }

#define INVARIANT(expression)                                                           \
    if (!(expression))                                                                  \
    {                                                                                   \
        throw Invariant(#expression, StripPath(__FILE__), __LINE__);                    \
    }

#endif // defined(WIN32)


#endif // !defined(_ASSERTION_H_)

