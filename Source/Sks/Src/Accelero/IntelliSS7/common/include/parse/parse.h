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
//  ID: $Id: parse.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//   parse.h: shared declarations for parse library.
//
//


#if !defined(_PARSE_H_)
#define _PARSE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>

#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>

#if !defined(__GNUC__) || (__GNUC__ >= 3)
#include <istream>
#else // defined(__GNUC__)
#include <iostream>
#endif // !defined(__GNUC__)


#include <its_exception.h>

#if !defined(WIN32)
typedef unsigned char byte;
#endif // !defined(WIN32)



#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)



typedef ITS_INT PrsResult;


////////////////////////////////////////////////////////////////////////////////
//
//  Parse error codes. 
//
//  Include errors for client libraries or applications. Since parsing related
//  error names are often generic, they can be reused across client libraries
//  or applications. See client libraries or applications for precise error 
//  significations.
//

enum PrsError
{
    PARSE_SUCCESS                                               = ITS_SUCCESS,
                                                                
    PARSE_ERROR_BASE                                            = -10000,
                                                                
    PARSE_ERROR                                                 = PARSE_ERROR_BASE - 1,
    PARSE_ERROR_STREAM_EOF                                      = PARSE_ERROR_BASE - 2,
    PARSE_ERROR_STREAM_FAIL                                     = PARSE_ERROR_BASE - 3,
    PARSE_ERROR_STREAM_BAD                                      = PARSE_ERROR_BASE - 4,
    PARSE_ERROR_STREAM_UNKNOWN                                  = PARSE_ERROR_BASE - 5,
    PARSE_ERROR_COMPARISON                                      = PARSE_ERROR_BASE - 6,
    PARSE_ERROR_KEYWORD_COMPARISON                              = PARSE_ERROR_BASE - 7,
    PARSE_ERROR_NOT_CONSUMED                                    = PARSE_ERROR_BASE - 8,
    PARSE_ERROR_COMMENT_COMPARISON                              = PARSE_ERROR_BASE - 9,
    PARSE_ERROR_EOL_COMPARISON                                  = PARSE_ERROR_BASE - 10,
    PARSE_ERROR_LWSP_COMPARISON                                 = PARSE_ERROR_BASE - 11,
    PARSE_ERROR_WSP_COMPARISON                                  = PARSE_ERROR_BASE - 12,
    PARSE_ERROR_SEP_COMPARISON                                  = PARSE_ERROR_BASE - 13,
    PARSE_ERROR_EQUAL_COMPARISON                                = PARSE_ERROR_BASE - 14,
    PARSE_ERROR_LBRKT_COMPARISON                                = PARSE_ERROR_BASE - 15,
    PARSE_ERROR_RBRKT_COMPARISON                                = PARSE_ERROR_BASE - 16,
    PARSE_ERROR_COMMA_COMPARISON                                = PARSE_ERROR_BASE - 17,
    PARSE_ERROR_NON_ESCAPE_CHAR_COMPARISON                      = PARSE_ERROR_BASE - 18,
    PARSE_ERROR_QUOTED_STRING_COMPARISON                        = PARSE_ERROR_BASE - 19,
    PARSE_ERROR_NAME_COMPARISON                                 = PARSE_ERROR_BASE - 20,
    PARSE_ERROR_VALUE_COMPARISON                                = PARSE_ERROR_BASE - 21,
    PARSE_ERROR_LSBRKT_COMPARISON                               = PARSE_ERROR_BASE - 22,
    PARSE_ERROR_RSBRKT_COMPARISON                               = PARSE_ERROR_BASE - 23,
    PARSE_ERROR_INEQUAL_COMPARISON                              = PARSE_ERROR_BASE - 24,
    PARSE_ERROR_UINT16_COMPARISON                               = PARSE_ERROR_BASE - 25,
    PARSE_ERROR_UINT32_COMPARISON                               = PARSE_ERROR_BASE - 26,
    PARSE_ERROR_TIME_COMPARISON                                 = PARSE_ERROR_BASE - 27,
    PARSE_ERROR_DATE_COMPARISON                                 = PARSE_ERROR_BASE - 28,
    PARSE_ERROR_VERSION_CODE_COMPARISON                         = PARSE_ERROR_BASE - 29,
    PARSE_ERROR_ERROR_CODE_COMPARISON                           = PARSE_ERROR_BASE - 30,
    PARSE_ERROR_TIMER_COMPARISON                                = PARSE_ERROR_BASE - 31,
    PARSE_ERROR_V4HEX_COMPARISON                                = PARSE_ERROR_BASE - 32,
    PARSE_ERROR_HEX4_COMPARISON                                 = PARSE_ERROR_BASE - 33,
    PARSE_ERROR_DOMAIN_NAME_COMPARISON                          = PARSE_ERROR_BASE - 34,
    PARSE_ERROR_PATH_DOMAIN_NAME_COMPARISON                     = PARSE_ERROR_BASE - 35,
    PARSE_ERROR_DIGIT_MAP_LETTER_COMPARISON                     = PARSE_ERROR_BASE - 36,
    PARSE_ERROR_ALPHA_DIGIT_RPT_COMPARISON                      = PARSE_ERROR_BASE - 37,
    PARSE_ERROR_HEXDIG_RPT_COMPARISON                           = PARSE_ERROR_BASE - 38,
    PARSE_ERROR_TWO_KEYWORDS_COMPARISON                         = PARSE_ERROR_BASE - 39,
    PARSE_ERROR_VBAR_COMPARISON                                 = PARSE_ERROR_BASE - 40,
    PARSE_ERROR_DIGIT_RPT_COMPARISON                            = PARSE_ERROR_BASE - 41,
    PARSE_ERROR_ALPHA_RPT_COMPARISON                            = PARSE_ERROR_BASE - 42,
    PARSE_ERROR_ALLOWED_RPT_COMPARISON                          = PARSE_ERROR_BASE - 43,
    PARSE_ERROR_SUITABLE_RPT_COMPARISON                         = PARSE_ERROR_BASE - 44,
    PARSE_ERROR_SUITABLE_WITHOUT_AT_RPT_COMPARISON              = PARSE_ERROR_BASE - 45,
    PARSE_ERROR_SUITABLE_WITHOUT_SEMICOLON_RPT_COMPARISON       = PARSE_ERROR_BASE - 46,
    PARSE_ERROR_ALPHA_DIGIT_DASH_RPT_COMPARISON                 = PARSE_ERROR_BASE - 47,
    PARSE_ERROR_ALPHA_DIGIT_DOT_DASH_RPT_COMPARISON             = PARSE_ERROR_BASE - 48,
    PARSE_ERROR_ALPHA_DIGIT_PLUS_SLASH_EQUAL_RPT_COMPARISON     = PARSE_ERROR_BASE - 49,
    PARSE_ERROR_X20_TO_X7E_RPT_COMPARISON                       = PARSE_ERROR_BASE - 50,
    PARSE_ERROR_X20_TO_X7F_RPT_COMPARISON                       = PARSE_ERROR_BASE - 51,
    PARSE_ERROR_R1WSP_COMPARISON                                = PARSE_ERROR_BASE - 52,
    PARSE_ERROR_DTMF_LETTER_COMPARISON                          = PARSE_ERROR_BASE - 53,
    PARSE_ERROR_LWS_COMPARISON                                  = PARSE_ERROR_BASE - 54,
    PARSE_ERROR_TEXT_UTF8_CHAR_COMPARISON                       = PARSE_ERROR_BASE - 55,
    PARSE_ERROR_UTF8_NONASCII_COMPARISON                        = PARSE_ERROR_BASE - 56,
    PARSE_ERROR_TOKEN_COMPARISON                                = PARSE_ERROR_BASE - 57,
    PARSE_ERROR_TEXT_UTF8_CHAR_NO_PARS_BACKSLASH_COMPARISON     = PARSE_ERROR_BASE - 58,
    PARSE_ERROR_QUOTED_PAIR_COMPARISON                          = PARSE_ERROR_BASE - 59,
    PARSE_ERROR_QUOTED_STRING_TEXT_COMPARISON                   = PARSE_ERROR_BASE - 60,
    PARSE_ERROR_ESCAPED_COMPARISON                              = PARSE_ERROR_BASE - 61,
    PARSE_ERROR_P_NAME_COMPARISON                               = PARSE_ERROR_BASE - 62,
    PARSE_ERROR_P_VALUE_COMPARISON                              = PARSE_ERROR_BASE - 63,
    PARSE_ERROR_H_NAME_COMPARISON                               = PARSE_ERROR_BASE - 64,
    PARSE_ERROR_DOMAIN_LABEL_COMPARISON                         = PARSE_ERROR_BASE - 65,
    PARSE_ERROR_TOP_LABEL_COMPARISON                            = PARSE_ERROR_BASE - 66,
    PARSE_ERROR_PHONE_DIGITS_COMPARISON                         = PARSE_ERROR_BASE - 67,
    PARSE_ERROR_CRLF_COMPARISON                                 = PARSE_ERROR_BASE - 68,
    PARSE_ERROR_COMMA_SEPARATOR_COMPARISON                      = PARSE_ERROR_BASE - 69,
    PARSE_ERROR_SP_RPT_COMPARISON                               = PARSE_ERROR_BASE - 70,
    PARSE_ERROR_URIC_NO_SLASH_RPT_COMPARISON                    = PARSE_ERROR_BASE - 71,
    PARSE_ERROR_URIC_RPT_COMPARISON                             = PARSE_ERROR_BASE - 72,
    PARSE_ERROR_REL_SEGMENT_CHAR_RPT_COMPARISON                 = PARSE_ERROR_BASE - 73,
    PARSE_ERROR_SCHEME_CHAR_RPT_COMPARISON                      = PARSE_ERROR_BASE - 74,
    PARSE_ERROR_USER_INFO_H_CHAR_RPT_COMPARISON                 = PARSE_ERROR_BASE - 75,
    PARSE_ERROR_SEGMENT_CHAR_RPT_COMPARISON                     = PARSE_ERROR_BASE - 76,
    PARSE_ERROR_REG_NAME_CHAR_RPT_COMPARISON                    = PARSE_ERROR_BASE - 77,
    PARSE_ERROR_Q_VALUE_COMPARISON                              = PARSE_ERROR_BASE - 78,
    PARSE_ERROR_SEMICOLON_SEPARATOR_COMPARISON                  = PARSE_ERROR_BASE - 79,
    PARSE_ERROR_COLON_SEPARATOR_COMPARISON                      = PARSE_ERROR_BASE - 80,
    PARSE_ERROR_SLASH_SEPARATOR_COMPARISON                      = PARSE_ERROR_BASE - 81,
    PARSE_ERROR_EQUAL_SEPARATOR_COMPARISON                      = PARSE_ERROR_BASE - 82,
    PARSE_ERROR_TEXT_UTF8_COMPARISON                            = PARSE_ERROR_BASE - 83,
    PARSE_ERROR_TEXT_UTF8_TRIM_COMPARISON                       = PARSE_ERROR_BASE - 84,
    PARSE_ERROR_INTEGER_COMPARISON                              = PARSE_ERROR_BASE - 85,
    PARSE_ERROR_DECIMAL_UCHAR_COMPARISON                        = PARSE_ERROR_BASE - 86,
    PARSE_ERROR_BYTE_STRING_COMPARISON                          = PARSE_ERROR_BASE - 87,
    PARSE_ERROR_TEXT_COMPARISON                                 = PARSE_ERROR_BASE - 88,
    PARSE_ERROR_PHONE_COMPARISON                                = PARSE_ERROR_BASE - 89,
    PARSE_ERROR_TYPED_TIME_COMPARISON                           = PARSE_ERROR_BASE - 90,
    PARSE_ERROR_URICS_COMPARISON                                = PARSE_ERROR_BASE - 91,
    PARSE_ERROR_PCHARS_COMPARISON                               = PARSE_ERROR_BASE - 92,
    PARSE_ERROR_USER_INFO_COMPARISON                            = PARSE_ERROR_BASE - 93,
    PARSE_ERROR_REG_NAME_COMPARISON                             = PARSE_ERROR_BASE - 94,
    PARSE_ERROR_SCHEME_COMPARISON                               = PARSE_ERROR_BASE - 95,
    PARSE_ERROR_REL_SEGMENT_COMPARISON                          = PARSE_ERROR_BASE - 96,
    PARSE_ERROR_URIC_NO_SLASH_COMPARISON                        = PARSE_ERROR_BASE - 97,
    PARSE_ERROR_OPAQUE_PART_COMPARISON                          = PARSE_ERROR_BASE - 98,
    PARSE_ERROR_EMAIL_COMPARISON                                = PARSE_ERROR_BASE - 99,
    PARSE_ERROR_SAFE_RPT_COMPARISON                             = PARSE_ERROR_BASE - 100,
    PARSE_ERROR_EMAIL_SAFE_RPT_COMPARISON                       = PARSE_ERROR_BASE - 101,
    PARSE_ERROR_POSDIGIT_RPT_COMPARISON                         = PARSE_ERROR_BASE - 102,
    PARSE_ERROR_DIGIT_SPACE_DASH_RPT_COMPARISON                 = PARSE_ERROR_BASE - 103,
    PARSE_ERROR_ALPHA_DIGIT_DOT_DASH                            = PARSE_ERROR_BASE - 104,
    PARSE_ERROR_SPACE_COMPARISON                                = PARSE_ERROR_BASE - 105

};


////////////////////////////////////////////////////////////////////////////////
//
//  PrsErrorGetText. Return a textual description of a parse error code.
//
//

std::string PrsErrorGetText(PrsResult error);



////////////////////////////////////////////////////////////////////////////////
//
//  PARSE_DEFINE_CLASS_GET_NAME. Macro to define "get name" classes.
//
//  Note: "get name" classes are required to be used in conjunction with the 
//  template classes AggregateTemplate, ChoiceTemplate and RepetitionTemplate
//  only because template parameters cannot be constant character strings.
//

//
//  MP_ClassName => name of class.
//  MP_Name => string returned by GetName member function.
//
//  MP = Macro Parameter.
//

#define PARSE_DEFINE_CLASS_GET_NAME(MP_ClassName, MP_Name)                  \
                                                                            \
class __##MP_ClassName##GetName                                             \
{                                                                           \
public:                                                                     \
                                                                            \
    static const char* GetName() { return MP_Name; }                        \
}

//
////////////////////////////////////////////////////////////////////////////////


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_PARSE_H_)
