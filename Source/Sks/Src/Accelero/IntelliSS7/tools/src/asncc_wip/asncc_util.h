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
//  ID: $Id: asncc_util.h,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#if !defined(_ASNCC_UTIL_H_)
#define _ASNCC_UTIL_H_

#include <asncc.h>

std::string StripPath(const std::string& fileName);

std::string LongToString(long l);

std::string IntToString(int i);

std::string AutoIndent(const std::string& str);

std::string AdaptName(const std::string& str);

std::string AdaptNameToUppercase(const std::string& str);

std::string AdaptNameToLowercase(const std::string& str);

std::string AdaptModuleName(const std::string& str);

void CreateDirectory(const std::string& directoryName);

void WriteTextToFile(
                const std::string& directoryName,
                const std::string& fileNameCore,
                const std::string& fileNameExtension,
                const std::string& text);

std::ostream& operator<<(std::ostream& os, const std::string& str);

#endif // !defined(_ASNCC_UTIL_H_)
