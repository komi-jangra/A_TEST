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
//  ID: $Id: exc_assert.h,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:43  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:21  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:56  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:17  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:53:08  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:19  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:37  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:24  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:25  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.1  2000/08/16 00:08:37  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:30:28  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.4  1999/06/28 19:56:45  mmiers
// LOG:
// LOG:
// LOG: Get the syntax of this right.
// LOG:
// LOG: Revision 1.3  1999/06/28 19:13:59  skarmakar
// LOG:
// LOG:
// LOG: Update with awareness of throw specifier, behavior control defines
// LOG: in its++.h.
// LOG:
// LOG: Revision 1.2  1998/09/22 23:56:35  jrao
// LOG: Changes made to accomodate HPUX code
// LOG:
// LOG: Revision 1.1  1998/05/19 22:39:54  hdivoux
// LOG: Creation.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////


// General (simple) assertion mechanism.

#if !defined(_EXC_ASSERT_H_)
#define _EXC_ASSERT_H_

#include <its++.h>

#include <exception>
#include <string>
#if defined(_WIN32)
#pragma warning(disable : 4786)
#endif
#include <list>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif


class GenericException : public exception {

public:
    GenericException();
    GenericException(const string& reasonParam);
    GenericException(const string& reasonParam, const string& fileParam, unsigned long lineParam);

    ~GenericException() ITS_THROW_SPEC_NULL;

    void          Register();
    const string& Description();

    const string& GetReason()    { return reason; }
    const string& GetFile()      { return file;   }
    unsigned long GetLine()      { return line;   }

protected:
    string        reason;
    string        file;
    unsigned long line;
    list<string>  fields;

private:
    void          Format();
    string        description;

};



class Assert : public GenericException {

public:
    Assert(const string& reason, const string& fileParam, unsigned long lineParam)
        : GenericException(reason, fileParam, lineParam) {};

    ~Assert() ITS_THROW_SPEC_NULL {};

};

class Precondition : public GenericException { 

public:
    Precondition(const string& reason, const string& fileParam, unsigned long lineParam)
        : GenericException(reason, fileParam, lineParam) {};

    ~Precondition() ITS_THROW_SPEC_NULL {};

};

class Postcondition : public GenericException {

public:
    Postcondition(const string& reason, const string& fileParam, unsigned long lineParam)
        : GenericException(reason, fileParam, lineParam) {};

    ~Postcondition() ITS_THROW_SPEC_NULL {};

};

class Invariant : public GenericException {

public:
    Invariant(const string& reason, const string& fileParam, unsigned long lineParam)
        : GenericException(reason, fileParam, lineParam) {};

    ~Invariant() ITS_THROW_SPEC_NULL {};

};


#define ASSERT(expression)    if (!(expression)) throw Assert(#expression, __FILE__, __LINE__);
#define REQUIRE(expression)   if (!(expression)) throw Precondition(#expression, __FILE__, __LINE__);
#define ENSURE(expression)    if (!(expression)) throw Postcondition(#expression, __FILE__, __LINE__);
#define INVARIANT(expression) if (!(expression)) throw Invariant(#expression, __FILE__, __LINE__);



#endif    // !defined(_EXC_ASSERT_H_)
