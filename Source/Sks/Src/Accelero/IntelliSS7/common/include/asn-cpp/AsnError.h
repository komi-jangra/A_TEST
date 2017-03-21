///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//          Copyright (c) 1999 - 2002 IntelliNet Technologies, Inc.          //
//                            All Rights Reserved.                           //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
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
// Contract: Internal                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:07  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:58  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:52  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:53  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:57  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.5  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.4  2002/01/10 22:51:55  hdivoux
// LOG: Start XER decoding.
// LOG:
// LOG: Revision 5.3  2002/01/02 23:23:28  hdivoux
// LOG: Start update for XER support.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:53  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime AsnError class definition.
//

#if !defined(_ASN_ERROR_H_)
#define _ASN_ERROR_H_

#ident "$Id: AsnError.h,v 1.1.1.1 2007-10-08 11:11:36 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <string.h>

namespace its {

enum AsnError {

    // General errors.
    ASN_E_INDEFINITE_LENGTH,

    // Type releated errors.
    ASN_E_INVALID_BOOLEAN_LENGTH,
    ASN_E_INVALID_CHOICE,
    ASN_E_UNKNOWN_CHOICE,
    ASN_E_INVALID_ENUMERATED_VALUE,
    ASN_E_INDEFINITE_ENUMERATED_LENGTH,
    ASN_E_NULL_ENUMERATED_LENGTH,
    ASN_E_ENUMERATED_LENGTH_TOO_LARGE,
    ASN_E_INVALID_ENUMERATED_LENGTH,
    ASN_E_INTEGER_VALUE_OUT_OF_RANGE,
    ASN_E_INDEFINITE_INTEGER_LENGTH,
    ASN_E_NULL_INTEGER_LENGTH,
    ASN_E_INTEGER_LENGTH_TOO_LARGE,
    ASN_E_INVALID_INTEGER_LENGTH,
    ASN_E_INVALID_NULL_LENGTH,
    ASN_E_INVALID_OCTET_STRING_SIZE,
    ASN_E_CONSTRUCTED_OCTET_STRING,
    ASN_E_INDEFINITE_OCTET_STRING_LENGTH,
    ASN_E_INVALID_OCTET_STRING_LENGTH,
    ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE,
    ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE,
    ASN_E_MISSING_MANDATORY_ELEMENT_IN_SEQUENCE,
    ASN_E_INVALID_SEQUENCE_OF_SIZE,
    ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE_OF,
    ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE_OF,
    ASN_E_UNKNOWN_ELEMENT_IN_SET,
    ASN_E_INVALID_ELEMENT_LENGTH_IN_SET,
    ASN_E_MISSING_MANDATORY_ELEMENT_IN_SET,
    ASN_E_INVALID_SET_OF_SIZE,
    ASN_E_UNKNOWN_ELEMENT_IN_SET_OF,
    ASN_E_INVALID_ELEMENT_LENGTH_IN_SET_OF,
    ASN_E_NO_CHOICE_PRESENT,
    ASN_E_INVALID_BIT_STRING_SIZE,
    ASN_E_CONSTRUCTED_BIT_STRING,
    ASN_E_INDEFINITE_BIT_STRING_LENGTH,
    ASN_E_NULL_BIT_STRING_LENGTH,
    ASN_E_INVALID_BIT_STRING_LENGTH,
    ASN_E_INVALID_BIT_STRING_UNUSED_BITS_NUMBER,
    ASN_E_NO_ANY_PRESENT,
    ASN_E_INDEFINITE_ANY_LENGTH,
    ASN_E_INVALID_ANY_LENGTH,
    ASN_E_CONSTRUCTED_OID,
    ASN_E_INDEFINITE_OID_LENGTH,
    ASN_E_NULL_OID_LENGTH,
    ASN_E_INVALID_OID_LENGTH,
    ASN_E_OID_CPT_VALUE_OUT_OF_RANGE,
    ASN_E_OID_CPT_VALUE_INVALID,
    ASN_E_INVALID_NUMBER_OF_CPTS_IN_OID,
    ASN_E_INVALID_FIRST_CPT_VALUE_IN_OID,
    ASN_E_INVALID_SECOND_CPT_VALUE_IN_OID,
    ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_OID,
    ASN_E_INDEFINITE_REAL_LENGTH,
    ASN_E_NULL_REAL_LENGTH,
    ASN_E_REAL_VALUE_OUT_OF_RANGE,
    ASN_E_REAL_LENGTH_TOO_LARGE,
    ASN_E_INVALID_REAL_LENGTH,
    ASN_E_INVALID_BASE_STRING_SIZE,
    ASN_E_CONSTRUCTED_BASE_STRING,
    ASN_E_INDEFINITE_BASE_STRING_LENGTH,
    ASN_E_INVALID_BASE_STRING_LENGTH,
    ASN_E_NO_OPEN_TYPE_PRESENT,
    ASN_E_INDEFINITE_OPEN_TYPE_LENGTH,
    ASN_E_INVALID_OPEN_TYPE_LENGTH,
    ASN_E_CONSTRUCTED_RELATIVE_OID,
    ASN_E_INDEFINITE_RELATIVE_OID_LENGTH,
    ASN_E_NULL_RELATIVE_OID_LENGTH,
    ASN_E_INVALID_RELATIVE_OID_LENGTH,
    ASN_E_RELATIVE_OID_CPT_VALUE_INVALID,
    ASN_E_INVALID_NUMBER_OF_CPTS_IN_RELATIVE_OID,
    ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_RELATIVE_OID,

    // Tag related errors.
    ASN_E_INVALID_TAG_LENGTH,
    ASN_E_INVALID_UNIVERSAL_NUMBER,

    // Length related errors.
    ASN_E_INVALID_LENGTH_LENGTH,
    ASN_E_INVALID_INDEFINITE_LENGTH_LENGTH,

    // XER related errors.
    ASN_E_XML_INVALID_START_TAG,
    ASN_E_XML_INVALID_END_TAG,
    ASN_E_XML_INVALID_EMPTY_ELEMENT_TAG,
    ASN_E_XML_INVALID_BASE_STRING_CONTENT,
    ASN_E_XML_INVALID_BIT_STRING_CONTENT,
    ASN_E_XML_INVALID_BOOLEAN_CONTENT,
    ASN_E_XML_INVALID_ENUMERATED_CONTENT,
    ASN_E_XML_INVALID_INTEGER_CONTENT,
    ASN_E_XML_INVALID_OID_CONTENT,
    ASN_E_XML_INVALID_OCTET_STRING_CONTENT,
    ASN_E_XML_INVALID_REAL_CONTENT,
    ASN_E_XML_INVALID_ANY_CONTENT,
    ASN_E_XML_INVALID_OPEN_TYPE_CONTENT,
    ASN_E_XML_INVALID_RELATIVE_OID_CONTENT

};

std::string AsnErrorGetText(AsnError error);

} // namespace its.

#endif // !defined(_ASN_ERROR_H_)
