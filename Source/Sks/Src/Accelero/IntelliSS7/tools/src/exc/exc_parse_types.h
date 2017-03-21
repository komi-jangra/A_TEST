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
//  ID: $Id: exc_parse_types.h,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
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
// LOG: Revision 9.1  2005/03/23 12:54:18  cvsadmin
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
// LOG: Revision 3.1  2000/08/16 00:08:39  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:30:30  mmiers
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
// LOG: Revision 1.2  1998/09/22 23:56:36  jrao
// LOG: Changes made to accomodate HPUX code
// LOG:
// LOG: Revision 1.1  1998/05/19 22:39:56  hdivoux
// LOG: Creation.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////


#if !defined(_EXC_PARSE_TYPES_H_)
#define _EXC_PARSE_TYPES_H_

#include <its++.h>

#include <list>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

class Option {

public:

    Option() {};

    string name;

};

typedef list<Option*> OptionList;


class Attribute {

public:
     
    Attribute() {};

    string name;
    string attributeType;
    string parameterType;
};

typedef list<Attribute*> AttributeList;

class Argument {

public:

    Argument() {};

    string name;
    string codeBefore;
    string codeAfter;
};

typedef list<Argument*> ArgumentList;


class Description {

public:

    Description() {};

    string       name;
    string       value;
    ArgumentList argumentList;

};

typedef list<Description*> DescriptionList;


class Exception {

public:

    Exception() {};

    string          name;
    int             number;
    string          reason;
    OptionList      optionList;
    string          codeHeaderBefore;
    string          codeHeaderAfter;
    string          codeSourceBefore;
    string          codeSourceAfter;
    string          codeBefore;
    string          codeBody;
    string          codeAfter;
    DescriptionList descriptionList;
    AttributeList   attributeList;

};

typedef list<Exception*> ExceptionList;


class Subsystem {

public:

    Subsystem() {};

    enum Status
    {
        OK,
        PARSE_ERRORS
    };

    Status        status;
    string        excSrcFileName;


    string        name;
    int           number;
    string        prefix;
    string        fileName;
    string        codeHeaderBefore;
    string        codeHeaderAfter;
    string        codeSourceBefore;
    string        codeSourceAfter;
    OptionList    optionList;
    ExceptionList exceptionList;

};

typedef list<Subsystem*> SubsystemList;





#endif    // !defined(_EXC_PARSE_TYPES_H_)
