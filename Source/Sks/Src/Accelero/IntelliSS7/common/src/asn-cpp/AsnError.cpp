///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//          Copyright (c) 1999 - 2002 IntelliNet Technologies, Inc.          //
//                            All Rights Reserved.                           //
//              Manufactured in the United States of America.                //
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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:13  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:02  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1  2007/03/30 04:53:34  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.1.1.1  2006/12/22 13:34:22  cvsadmin
// LOG: Initialising sources in CVS
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:19  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.6  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.5  2002/01/10 22:51:34  hdivoux
// LOG: Start XER decoding.
// LOG:
// LOG: Revision 5.4  2002/01/04 15:58:32  hdivoux
// LOG: More update for XER support.
// LOG:
// LOG: Revision 5.3  2002/01/02 23:23:03  hdivoux
// LOG: Start update for XER support.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:27  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnError.cpp,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $"

//
// ASN.1 runtime AsnError class implementation.
//

#include <Asn.h>
#include <AsnError.h>

using namespace std;

namespace its {

//
// Error text from error.
//

string 
AsnErrorGetText(AsnError error)
{
    switch (error)
    {
    case ASN_E_INDEFINITE_LENGTH:
        return "indefinite length";

    case ASN_E_INVALID_BOOLEAN_LENGTH:
        return "invalid boolean length";

    case ASN_E_INVALID_CHOICE:
        return "invalid choice";

    case ASN_E_UNKNOWN_CHOICE:
        return "unknown choice";

    case ASN_E_INVALID_ENUMERATED_VALUE:
        return "invalid enumerated value";

    case ASN_E_INDEFINITE_ENUMERATED_LENGTH:
        return "indefinite enumerated length";

    case ASN_E_NULL_ENUMERATED_LENGTH:
        return "null enumerated length";

    case ASN_E_ENUMERATED_LENGTH_TOO_LARGE:
        return "enumerated length too large";

    case ASN_E_INVALID_ENUMERATED_LENGTH:
        return "invalid enumerated length";

    case ASN_E_INTEGER_VALUE_OUT_OF_RANGE:
        return "integer value out of range";

    case ASN_E_INDEFINITE_INTEGER_LENGTH:
        return "indefinite integer length";

    case ASN_E_NULL_INTEGER_LENGTH:
        return "null integer length";

    case ASN_E_INTEGER_LENGTH_TOO_LARGE:
        return "integer length too large";

    case ASN_E_INVALID_INTEGER_LENGTH:
        return "invalid integer length";

    case ASN_E_INVALID_NULL_LENGTH:
        return "invalid null length";

    case ASN_E_INVALID_OCTET_STRING_SIZE:
        return "invalid octet string size";

    case ASN_E_CONSTRUCTED_OCTET_STRING:
        return "constructed octet string";

    case ASN_E_INDEFINITE_OCTET_STRING_LENGTH:
        return "indefinite octet string length";

    case ASN_E_INVALID_OCTET_STRING_LENGTH:
        return "invalid octet string length";

    case ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE:
        return "unknown element in sequence";

    case ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE:
        return "invalid element length in sequence";

    case ASN_E_MISSING_MANDATORY_ELEMENT_IN_SEQUENCE:
        return "missing mandatory element in sequence";

    case ASN_E_INVALID_SEQUENCE_OF_SIZE:
        return "invalid sequence of size";

    case ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE_OF:
        return "unknown element in sequence of";

    case ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE_OF:
        return "invalid element length in sequence of";

    case ASN_E_UNKNOWN_ELEMENT_IN_SET:
        return "unknown element in set";

    case ASN_E_INVALID_ELEMENT_LENGTH_IN_SET:
        return "invalid element length in set";

    case ASN_E_MISSING_MANDATORY_ELEMENT_IN_SET:
        return "missing mandatory element in set";

    case ASN_E_INVALID_SET_OF_SIZE:
        return "invalid set of size";

    case ASN_E_UNKNOWN_ELEMENT_IN_SET_OF:
        return "unknown element in set of";

    case ASN_E_INVALID_ELEMENT_LENGTH_IN_SET_OF:
        return "invalid element length in set of";

    case ASN_E_NO_CHOICE_PRESENT:
        return "no choice present";

    case ASN_E_INVALID_BIT_STRING_SIZE:
        return "invalid bit string size";

    case ASN_E_CONSTRUCTED_BIT_STRING:
        return "constructed bit string";

    case ASN_E_INDEFINITE_BIT_STRING_LENGTH:
        return "indefinite bit string length";

    case ASN_E_NULL_BIT_STRING_LENGTH:
        return "null bit string length";

    case ASN_E_INVALID_BIT_STRING_LENGTH:
        return "invalid bit string length";

    case ASN_E_INVALID_BIT_STRING_UNUSED_BITS_NUMBER:
        return "invalid bit string unused bits number";

    case ASN_E_NO_ANY_PRESENT:
        return "no any present";

    case ASN_E_INDEFINITE_ANY_LENGTH:
        return "indefinite any length";

    case ASN_E_INVALID_ANY_LENGTH:
        return "invalid any length";

    case ASN_E_CONSTRUCTED_OID:
        return "constructed object identifier";

    case ASN_E_INDEFINITE_OID_LENGTH:
        return "indefinite object identifier length";

    case ASN_E_NULL_OID_LENGTH:
        return "null object identifier length";

    case ASN_E_INVALID_OID_LENGTH:
        return "invalid object identifier length";

    case ASN_E_OID_CPT_VALUE_OUT_OF_RANGE:
        return "object identifier component value out of range";

    case ASN_E_OID_CPT_VALUE_INVALID:
        return "object identifier component value invalid";

    case ASN_E_INVALID_NUMBER_OF_CPTS_IN_OID:
        return "invalid number of components in object identifier";

    case ASN_E_INVALID_FIRST_CPT_VALUE_IN_OID:
        return "invalid first component value in object identifier";

    case ASN_E_INVALID_SECOND_CPT_VALUE_IN_OID:
        return "invalid second component value in object identifier";

    case ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_OID:
        return "invalid negative component value in object identifier";

    case ASN_E_INDEFINITE_REAL_LENGTH:
        return "indefinite real length";

    case ASN_E_NULL_REAL_LENGTH:
        return "null real length";

    case ASN_E_REAL_VALUE_OUT_OF_RANGE:
        return "real value out of range";

    case ASN_E_REAL_LENGTH_TOO_LARGE:
        return "real length too large";

    case ASN_E_INVALID_REAL_LENGTH:
        return "invalid real length";

    case ASN_E_INVALID_BASE_STRING_SIZE:
        return "invalid base string size";

    case ASN_E_CONSTRUCTED_BASE_STRING:
        return "constructed base string";

    case ASN_E_INDEFINITE_BASE_STRING_LENGTH:
        return "indefinite base string length";

    case ASN_E_INVALID_BASE_STRING_LENGTH:
        return "invalid base string length";

    case ASN_E_NO_OPEN_TYPE_PRESENT:
        return "no open type present";

    case ASN_E_INDEFINITE_OPEN_TYPE_LENGTH:
        return "indefinite open type length";

    case ASN_E_INVALID_OPEN_TYPE_LENGTH:
        return "invalid open type length";

    case ASN_E_CONSTRUCTED_RELATIVE_OID:
        return "constructed relative oid";

    case ASN_E_INDEFINITE_RELATIVE_OID_LENGTH:
        return "indefinite relative oid length";

    case ASN_E_NULL_RELATIVE_OID_LENGTH:
        return "null relative oid length";

    case ASN_E_INVALID_RELATIVE_OID_LENGTH:
        return "invalid relative oid length";

    case ASN_E_RELATIVE_OID_CPT_VALUE_INVALID:
        return "relative oid component value invalid";

    case ASN_E_INVALID_NUMBER_OF_CPTS_IN_RELATIVE_OID:
        return "invalid number of components in relative oid";

    case ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_RELATIVE_OID:
        return "invalid negative component value in relative oid";

    case ASN_E_INVALID_TAG_LENGTH:
        return "invalid tag length";

    case ASN_E_INVALID_UNIVERSAL_NUMBER:
        return "invalid universal number";

    case ASN_E_INVALID_LENGTH_LENGTH:
        return "invalid length length";

    case ASN_E_INVALID_INDEFINITE_LENGTH_LENGTH:
        return "invalid indefinite length length";

    case ASN_E_XML_INVALID_START_TAG:
        return "xml invalid start tag";

    case ASN_E_XML_INVALID_END_TAG:
        return "xml invalid end tag";

    case ASN_E_XML_INVALID_EMPTY_ELEMENT_TAG:
        return "xml invalid empty element tag";

    case ASN_E_XML_INVALID_BASE_STRING_CONTENT:
        return "xml invalid base string content";

    case ASN_E_XML_INVALID_BIT_STRING_CONTENT:
        return "xml invalid bit string content";

    case ASN_E_XML_INVALID_BOOLEAN_CONTENT:
        return "xml invalid boolean content";

    case ASN_E_XML_INVALID_ENUMERATED_CONTENT:
        return "xml invalid enumerated content";

    case ASN_E_XML_INVALID_INTEGER_CONTENT:
        return "xml invalid integer content";

    case ASN_E_XML_INVALID_OID_CONTENT:
        return "xml invalid object identifier content";

    case ASN_E_XML_INVALID_OCTET_STRING_CONTENT:
        return "xml invalid octet string content";

    case ASN_E_XML_INVALID_REAL_CONTENT:
        return "xml invalid real content";

    case ASN_E_XML_INVALID_ANY_CONTENT:
        return "xml invalid any content";

    case ASN_E_XML_INVALID_OPEN_TYPE_CONTENT:
        return "xml invalid open type content";

    case ASN_E_XML_INVALID_RELATIVE_OID_CONTENT:
        return "xml invalid relative oid content";

    default:
        return "undefined error";
    }
}

} // namespace its.

