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
//  ID: $Id: parse.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//   parse.cpp: shared implementations for parse library.
//
//


#include <parse.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  PrsErrorGetText.
//

string 
PrsErrorGetText(PrsResult error)
{
    switch (error)
    {
    case PARSE_SUCCESS:
        return "success";

    case PARSE_ERROR:
        return "unspecified error";

    case PARSE_ERROR_STREAM_EOF:
        return "stream off";

    case PARSE_ERROR_STREAM_FAIL:
        return "stream fail";

    case PARSE_ERROR_STREAM_BAD:
        return "stream bad";

    case PARSE_ERROR_STREAM_UNKNOWN:
        return "stream unknown";

    case PARSE_ERROR_KEYWORD_COMPARISON:
        return "keyword comparison";

    // TODO: to be completed with other errors.

    default:
        return "undefined error";
    }
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

