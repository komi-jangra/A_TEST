///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//          Copyright (c) 1999 - 2002 IntelliNet Technologies, Inc.          //
//                            All Rights Reserved.                           //
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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:06  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:58  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:51  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:52  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.3  2005/03/21 13:50:54  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:40  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.2  2002/05/22 20:35:35  hdivoux
// LOG: Typo in global encode ignore octet string size constraint.
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.6  2002/01/16 22:13:19  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.5  2002/01/10 00:09:24  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.4  2002/01/02 23:23:28  hdivoux
// LOG: Start update for XER support.
// LOG:
// LOG: Revision 5.3  2001/12/24 21:03:21  hdivoux
// LOG: General update for options.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:53  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime common and AsnOptions class definition.
//

#if !defined(_ASN_H_)
#define _ASN_H_

#ident "$Id: Asn.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(WIN32)
#include <windows.h>
#endif // defined(WIN32)

#if defined(WIN32)
#pragma warning(disable:4786) 
#endif // defined(WIN32)

#if !defined(WIN32)
typedef unsigned char byte;
#endif // !defined(WIN32)

#include <vector>
#include <list>
#include <set>
#include <strstream>
#include <iostream>
#include <string>

#include <its_exception.h>

#if !defined(ITS_NAMESPACE)
#error "ANSI C++ compiler required."
#endif // !defined(ITS_NAMESPACE).

namespace its {

////////////////////////////////////////////////////////////
//
//  Forward declaration (see Tag.h).
//

class ReplaceTagCallback;


class Asn
{
public:

    static void Initialize();
    static void Terminate();
    static void Lock();
    static void Unlock();

};


class AsnOptions
{
public:

    AsnOptions()
    :   _encodingRules
            (_globalEncodingRules),
        _decodeSkipInvalidEnumeratedValue        
            (_globalDecodeSkipInvalidEnumeratedValue),
        _encodeSkipInvalidEnumeratedValue        
            (_globalEncodeSkipInvalidEnumeratedValue),
        _decodeSkipUnknownElementInSequence      
            (_globalDecodeSkipUnknownElementInSequence),
        _decodeSkipUnknownElementInSet           
            (_globalDecodeSkipUnknownElementInSet),
        _decodeIgnoreOctetStringSizeConstraint   
            (_globalDecodeIgnoreOctetStringSizeConstraint),
        _encodeIgnoreOctetStringSizeConstraint   
            (_globalEncodeIgnoreOctetStringSizeConstraint),
        _decodeIgnoreIntegerSizeConstraint       
            (_globalDecodeIgnoreIntegerSizeConstraint),
        _encodeIgnoreIntegerSizeConstraint       
            (_globalEncodeIgnoreIntegerSizeConstraint),
        _decodeIgnoreSequenceOfSizeConstraint    
            (_globalDecodeIgnoreSequenceOfSizeConstraint),
        _encodeIgnoreSequenceOfSizeConstraint    
            (_globalEncodeIgnoreSequenceOfSizeConstraint),
        _decodeIgnoreSetOfSizeConstraint         
            (_globalDecodeIgnoreSetOfSizeConstraint),
        _encodeIgnoreSetOfSizeConstraint         
            (_globalEncodeIgnoreSetOfSizeConstraint),
        _decodeIgnoreBitStringSizeConstraint     
            (_globalDecodeIgnoreBitStringSizeConstraint),
        _encodeIgnoreBitStringSizeConstraint     
            (_globalEncodeIgnoreBaseStringSizeConstraint),
        _decodeIgnoreBaseStringSizeConstraint     
            (_globalDecodeIgnoreBaseStringSizeConstraint),
        _encodeIgnoreBaseStringSizeConstraint     
            (_globalEncodeIgnoreBaseStringSizeConstraint),
        _decodeProcessUnknownElements
            (_globalDecodeProcessUnknownElements),
        _encodeProcessUnknownElements
            (_globalEncodeProcessUnknownElements),
        _encodeXmlWithoutSeparators
            (_globalEncodeXmlWithoutSeparators)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    ~AsnOptions()
    {
        // Nothing to do.
    }

    enum AsnEncodingRules {
        ASN_BER_ENCODING_RULES                      = 0,
        ASN_PER_BASIC_ALIGNED_ENCODING_RULES        = 1,
        ASN_PER_CANONICAL_ALIGNED_ENCODING_RULES    = 2,
        ASN_PER_BASIC_UNALIGNED_ENCODING_RULES      = 3,
        ASN_PER_CANONICAL_UNALIGNED_ENCODING_RULES  = 4,
        ASN_XER_ENCODING_RULES                      = 5
    };


    ////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////

    // Local (dynamic) options.

    ////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////

    // Encoding Rules.

    AsnEncodingRules
    GetEncodingRules() const
    {
        return _encodingRules;
    }

    void 
    SetBerEncodingRules()
    { 
        _encodingRules = 
            ASN_BER_ENCODING_RULES; 
    }

    void 
    SetPerBasicAlignedEncodingRules()
    { 
        _encodingRules = 
            ASN_PER_BASIC_ALIGNED_ENCODING_RULES; 
    }

    void 
    SetPerCanonicalAlignedEncodingRules()
    { 
        _encodingRules = 
            ASN_PER_CANONICAL_ALIGNED_ENCODING_RULES; 
    }

    void 
    SetPerBasicUnalignedEncodingRules()
    { 
        _encodingRules = 
            ASN_PER_BASIC_UNALIGNED_ENCODING_RULES; 
    }

    void 
    SetPerCanonicalUnalignedEncodingRules()
    { 
        _encodingRules = 
            ASN_PER_CANONICAL_UNALIGNED_ENCODING_RULES; 
    }

    void 
    SetXerEncodingRules()
    { 
        _encodingRules = 
            ASN_XER_ENCODING_RULES; 
    }

    bool 
    IsBerEncodingRules() const
    { 
        return _encodingRules == 
            ASN_BER_ENCODING_RULES; 
    }

    bool 
    IsPerBasicAlignedEncodingRules() const
    { 
        return _encodingRules == 
            ASN_PER_BASIC_ALIGNED_ENCODING_RULES; 
    }

    bool 
    IsPerCanonicalAlignedEncodingRules() const
    { 
        return _encodingRules == 
            ASN_PER_CANONICAL_ALIGNED_ENCODING_RULES;
    }

    bool 
    IsPerBasicUnalignedEncodingRules() const
    { 
        return _encodingRules == 
            ASN_PER_BASIC_UNALIGNED_ENCODING_RULES; 
    }

    bool 
    IsPerCanonicalUnalignedEncodingRules() const
    { 
        return _encodingRules == 
            ASN_PER_CANONICAL_UNALIGNED_ENCODING_RULES; 
    }

    bool 
    IsXerEncodingRules() const
    { 
        return _encodingRules == 
            ASN_XER_ENCODING_RULES; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Skip Invalid Enumerated Value.

    void 
    SetDecodeSkipInvalidEnumeratedValue()
    { 
        _decodeSkipInvalidEnumeratedValue = true; 
    }

    void 
    UnsetDecodeSkipInvalidEnumeratedValue()
    { 
        _decodeSkipInvalidEnumeratedValue = false; 
    }

    bool 
    IsDecodeSkipInvalidEnumeratedValue() const
    { 
        return _decodeSkipInvalidEnumeratedValue; 
    }

    // Encode Skip Invalid Enumerated Value.

    void 
    SetEncodeSkipInvalidEnumeratedValue()
    { 
        _encodeSkipInvalidEnumeratedValue = true; 
    }

    void 
    UnsetEncodeSkipInvalidEnumeratedValue()
    { 
        _encodeSkipInvalidEnumeratedValue = false; 
    }

    bool 
    IsEncodeSkipInvalidEnumeratedValue() const
    { 
        return _encodeSkipInvalidEnumeratedValue; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Skip Unknown Element In Sequence.

    void 
    SetDecodeSkipUnknownElementInSequence()
    { 
        _decodeSkipUnknownElementInSequence = true; 
    }

    void 
    UnsetDecodeSkipUnknownElementInSequence()
    { 
        _decodeSkipUnknownElementInSequence = false; 
    }

    bool 
    IsDecodeSkipUnknownElementInSequence() const
    { 
        return _decodeSkipUnknownElementInSequence; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Skip Unknown Element In Set.

    void 
    SetDecodeSkipUnknownElementInSet()
    { 
        _decodeSkipUnknownElementInSet = true; 
    }

    void 
    UnsetDecodeSkipUnknownElementInSet()
    { 
        _decodeSkipUnknownElementInSet = false; 
    }

    bool 
    IsDecodeSkipUnknownElementInSet() const
    { 
        return _decodeSkipUnknownElementInSet; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Octet String Size Constraint.

    void 
    SetDecodeIgnoreOctetStringSizeConstraint()
    { 
        _decodeIgnoreOctetStringSizeConstraint = true; 
    }

    void 
    UnsetDecodeIgnoreOctetStringSizeConstraint()
    { 
        _decodeIgnoreOctetStringSizeConstraint = false; 
    }

    bool 
    IsDecodeIgnoreOctetStringSizeConstraint() const
    { 
        return _decodeIgnoreOctetStringSizeConstraint; 
    }

    // Encode Ignore Octet String Size Constraint.

    void 
    SetEncodeIgnoreOctetStringSizeConstraint()
    { 
        _encodeIgnoreOctetStringSizeConstraint = true; 
    }

    void 
    UnsetEncodeIgnoreOctetStringSizeConstraint()
    { 
        _encodeIgnoreOctetStringSizeConstraint = false; 
    }

    bool 
    IsEncodeIgnoreOctetStringSizeConstraint() const
    { 
        return _encodeIgnoreOctetStringSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Integer Size Constraint.

    void 
    SetDecodeIgnoreIntegerSizeConstraint()
    { 
        _decodeIgnoreIntegerSizeConstraint = true; 
    }

    void 
    UnsetDecodeIgnoreIntegerSizeConstraint()
    { 
        _decodeIgnoreIntegerSizeConstraint = false; 
    }

    bool 
    IsDecodeIgnoreIntegerSizeConstraint() const
    { 
        return _decodeIgnoreIntegerSizeConstraint; 
    }

    // Encode Ignore Integer Size Constraint.

    void 
    SetEncodeIgnoreIntegerSizeConstraint()
    { 
        _encodeIgnoreIntegerSizeConstraint = true; 
    }

    void 
    UnsetEncodeIgnoreIntegerSizeConstraint()
    { 
        _encodeIgnoreIntegerSizeConstraint = false; 
    }

    bool 
    IsEncodeIgnoreIntegerSizeConstraint() const
    { 
        return _encodeIgnoreIntegerSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Sequence of Size Constraint.

    void 
    SetDecodeIgnoreSequenceOfSizeConstraint()
    { 
        _decodeIgnoreSequenceOfSizeConstraint = true; 
    }

    void 
    UnsetDecodeIgnoreSequenceOfSizeConstraint()
    { 
        _decodeIgnoreSequenceOfSizeConstraint = false; 
    }

    bool 
    IsDecodeIgnoreSequenceOfSizeConstraint() const
    { 
        return _decodeIgnoreSequenceOfSizeConstraint; 
    }

    // Encode Ignore Sequence of Size Constraint.

    void 
    SetEncodeIgnoreSequenceOfSizeConstraint()
    { 
        _encodeIgnoreSequenceOfSizeConstraint = true; 
    }

    void 
    UnsetEncodeIgnoreSequenceOfSizeConstraint()
    { 
        _encodeIgnoreSequenceOfSizeConstraint = false; 
    }

    bool 
    IsEncodeIgnoreSequenceOfSizeConstraint() const
    { 
        return _encodeIgnoreSequenceOfSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Set of Size Constraint.

    void 
    SetDecodeIgnoreSetOfSizeConstraint()
    { 
        _decodeIgnoreSetOfSizeConstraint = true; 
    }

    void 
    UnsetDecodeIgnoreSetOfSizeConstraint()
    { 
        _decodeIgnoreSetOfSizeConstraint = false; 
    }

    bool 
    IsDecodeIgnoreSetOfSizeConstraint() const
    { 
        return _decodeIgnoreSetOfSizeConstraint; 
    }

    // Encode Ignore Set of Size Constraint.

    void 
    SetEncodeIgnoreSetOfSizeConstraint()
    { 
        _encodeIgnoreSetOfSizeConstraint = true; 
    }

    void 
    UnsetEncodeIgnoreSetOfSizeConstraint()
    { 
        _encodeIgnoreSetOfSizeConstraint = false; 
    }

    bool 
    IsEncodeIgnoreSetOfSizeConstraint() const
    { 
        return _encodeIgnoreSetOfSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Bit String Size Constraint.

    void 
    SetDecodeIgnoreBitStringSizeConstraint()
    { 
        _decodeIgnoreBitStringSizeConstraint = true; 
    }

    void 
    UnsetDecodeIgnoreBitStringSizeConstraint()
    { 
        _decodeIgnoreBitStringSizeConstraint = false; 
    }

    bool 
    IsDecodeIgnoreBitStringSizeConstraint() const
    { 
        return _decodeIgnoreBitStringSizeConstraint; 
    }

    // Encode Ignore Bit String Size Constraint.

    void 
    SetEncodeIgnoreBitStringSizeConstraint()
    { 
        _encodeIgnoreBitStringSizeConstraint = true; 
    }

    void 
    UnsetEncodeIgnoreBitStringSizeConstraint()
    { 
        _encodeIgnoreBitStringSizeConstraint = false; 
    }

    bool 
    IsEncodeIgnoreBitStringSizeConstraint() const
    { 
        return _encodeIgnoreBitStringSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Base String Size Constraint.

    void 
    SetDecodeIgnoreBaseStringSizeConstraint()
    { 
        _decodeIgnoreBaseStringSizeConstraint = true; 
    }

    void 
    UnsetDecodeIgnoreBaseStringSizeConstraint()
    { 
        _decodeIgnoreBaseStringSizeConstraint = false; 
    }

    bool 
    IsDecodeIgnoreBaseStringSizeConstraint() const
    { 
        return _decodeIgnoreBaseStringSizeConstraint; 
    }

    // Encode Ignore Base String Size Constraint.

    void 
    SetEncodeIgnoreBaseStringSizeConstraint()
    { 
        _encodeIgnoreBaseStringSizeConstraint = true; 
    }

    void 
    UnsetEncodeIgnoreBaseStringSizeConstraint()
    { 
        _encodeIgnoreBaseStringSizeConstraint = false; 
    }

    bool 
    IsEncodeIgnoreBaseStringSizeConstraint() const
    { 
        return _encodeIgnoreBaseStringSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Process Unknown Elements.

    void 
    SetDecodeProcessUnknownElements()
    { 
        _decodeProcessUnknownElements = true; 
    }

    void 
    UnsetDecodeProcessUnknownElements()
    { 
        _decodeProcessUnknownElements = false; 
    }

    bool 
    IsDecodeProcessUnknownElements() const
    { 
        return _decodeProcessUnknownElements; 
    }

    // Encode Process Unknown Elements.

    void 
    SetEncodeProcessUnknownElements()
    { 
        _encodeProcessUnknownElements = true; 
    }

    void 
    UnsetEncodeProcessUnknownElements()
    { 
        _encodeProcessUnknownElements = false; 
    }

    bool 
    IsEncodeProcessUnknownElements() const
    { 
        return _encodeProcessUnknownElements; 
    }

    ////////////////////////////////////////////////////////////

    // Encode XML without separators.

    void 
    SetEncodeXmlWithoutSeparators()
    { 
        _encodeXmlWithoutSeparators = true; 
    }

    void 
    UnsetEncodeXmlWithoutSeparators()
    { 
        _encodeXmlWithoutSeparators = false; 
    }

    bool 
    IsEncodeXmlWithoutSeparators() const
    { 
        return _encodeXmlWithoutSeparators; 
    }

    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////

    // Global (static) options.

    ////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////

    // Encoding Rules.

    AsnEncodingRules
    GlobalGetEncodingRules()
    {
        return _globalEncodingRules;
    }

    void 
    GlobalSetBerEncodingRules()
    { 
        _globalEncodingRules = 
            ASN_BER_ENCODING_RULES; 
    }

    void 
    GlobalSetPerBasicAlignedEncodingRules()
    { 
        _globalEncodingRules = 
            ASN_PER_BASIC_ALIGNED_ENCODING_RULES; 
    }


    void 
    GlobalSetPerCanonicalAlignedEncodingRules()
    { 
        _globalEncodingRules = 
            ASN_PER_CANONICAL_ALIGNED_ENCODING_RULES; 
    }

    void 
    GlobalSetPerBasicUnalignedEncodingRules()
    { 
        _globalEncodingRules = 
            ASN_PER_BASIC_UNALIGNED_ENCODING_RULES; 
    }

    void 
    GlobalSetPerCanonicalUnalignedEncodingRules()
    { 
        _globalEncodingRules = 
            ASN_PER_CANONICAL_UNALIGNED_ENCODING_RULES; 
    }

    void 
    GlobalSetXerEncodingRules()
    { 
        _globalEncodingRules = 
            ASN_XER_ENCODING_RULES; 
    }

    bool 
    GlobalIsBerEncodingRules()
    { 
        return _globalEncodingRules == 
            ASN_BER_ENCODING_RULES; 
    }

    bool 
    GlobalIsPerBasicAlignedEncodingRules()
    { 
        return _globalEncodingRules == 
            ASN_PER_BASIC_ALIGNED_ENCODING_RULES; 
    }

    bool 
    GlobalIsPerCanonicalAlignedEncodingRules()
    { 
        return _globalEncodingRules == 
            ASN_PER_CANONICAL_ALIGNED_ENCODING_RULES; 
    }

    bool 
    GlobalIsPerBasicUnalignedEncodingRules()
    { 
        return _globalEncodingRules == 
            ASN_PER_BASIC_UNALIGNED_ENCODING_RULES; 
    }

    bool 
    GlobalIsPerCanonicalUnalignedEncodingRules()
    { 
        return _globalEncodingRules == 
            ASN_PER_CANONICAL_UNALIGNED_ENCODING_RULES; 
    }

    bool 
    GlobalIsXerEncodingRules()
    { 
        return _globalEncodingRules == 
            ASN_XER_ENCODING_RULES; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Skip Invalid Enumerated Value.

    static void 
    GlobalSetDecodeSkipInvalidEnumeratedValue()
    { 
        _globalDecodeSkipInvalidEnumeratedValue = true; 
    }

    static void 
    GlobalUnsetDecodeSkipInvalidEnumeratedValue()
    { 
        _globalDecodeSkipInvalidEnumeratedValue = false; 
    }

    static bool 
    GlobalIsDecodeSkipInvalidEnumeratedValue()
    { 
        return _globalDecodeSkipInvalidEnumeratedValue; 
    }

    // Encode Skip Invalid Enumerated Value.

    static void 
    GlobalSetEncodeSkipInvalidEnumeratedValue()
    { 
        _globalEncodeSkipInvalidEnumeratedValue = true; 
    }

    static void 
    GlobalUnsetEncodeSkipInvalidEnumeratedValue()
    { 
        _globalEncodeSkipInvalidEnumeratedValue = false; 
    }

    static bool 
    GlobalIsEncodeSkipInvalidEnumeratedValue()
    { 
        return _globalEncodeSkipInvalidEnumeratedValue; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Skip Unknown Element In Sequence.

    static void 
    GlobalSetDecodeSkipUnknownElementInSequence()
    { 
        _globalDecodeSkipUnknownElementInSequence = true; 
    }

    static void 
    GlobalUnsetDecodeSkipUnknownElementInSequence()
    { 
        _globalDecodeSkipUnknownElementInSequence = false; 
    }

    static bool 
    GlobalIsDecodeSkipUnknownElementInSequence()
    { 
        return _globalDecodeSkipUnknownElementInSequence; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Skip Unknown Element In Set.

    static void 
    GlobalSetDecodeSkipUnknownElementInSet()
    { 
        _globalDecodeSkipUnknownElementInSet = true; 
    }

    static void 
    GlobalUnsetDecodeSkipUnknownElementInSet()
    { 
        _globalDecodeSkipUnknownElementInSet = false; 
    }

    static bool 
    GlobalIsDecodeSkipUnknownElementInSet()
    { 
        return _globalDecodeSkipUnknownElementInSet; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Octet String Size Constraint.

    static void 
    GlobalSetDecodeIgnoreOctetStringSizeConstraint()
    { 
        _globalDecodeIgnoreOctetStringSizeConstraint = true; 
    }

    static void 
    GlobalUnsetDecodeIgnoreOctetStringSizeConstraint()
    { 
        _globalDecodeIgnoreOctetStringSizeConstraint = false; 
    }

    static bool 
    GlobalIsDecodeIgnoreOctetStringSizeConstraint()
    { 
        return _globalDecodeIgnoreOctetStringSizeConstraint; 
    }

    // Encode Ignore Octet String Size Constraint.

    static void 
    GlobalSetEncodeIgnoreOctetStringSizeConstraint()
    { 
        _globalEncodeIgnoreOctetStringSizeConstraint = true; 
    }

    static void 
    GlobalUnsetEncodeIgnoreOctetStringSizeConstraint()
    { 
        _globalEncodeIgnoreOctetStringSizeConstraint = false; 
    }

    static bool 
    GlobalIsEncodeIgnoreOctetStringSizeConstraint()
    { 
        return _globalEncodeIgnoreOctetStringSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Integer Size Constraint.

    static void 
    GlobalSetDecodeIgnoreIntegerSizeConstraint()
    { 
        _globalDecodeIgnoreIntegerSizeConstraint = true; 
    }

    static void 
    GlobalUnsetDecodeIgnoreIntegerSizeConstraint()
    { 
        _globalDecodeIgnoreIntegerSizeConstraint = false; 
    }

    static bool 
    GlobalIsDecodeIgnoreIntegerSizeConstraint()
    { 
        return _globalDecodeIgnoreIntegerSizeConstraint; 
    }

    // Encode Ignore Integer Size Constraint.

    static void 
    GlobalSetEncodeIgnoreIntegerSizeConstraint()
    { 
        _globalEncodeIgnoreIntegerSizeConstraint = true; 
    }

    static void 
    GlobalUnsetEncodeIgnoreIntegerSizeConstraint()
    { 
        _globalEncodeIgnoreIntegerSizeConstraint = false; 
    }

    static bool 
    GlobalIsEncodeIgnoreIntegerSizeConstraint()
    { 
        return _globalEncodeIgnoreIntegerSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Sequence of Size Constraint.

    static void 
    GlobalSetDecodeIgnoreSequenceOfSizeConstraint()
    { 
        _globalDecodeIgnoreSequenceOfSizeConstraint = true; 
    }

    static void 
    GlobalUnsetDecodeIgnoreSequenceOfSizeConstraint()
    { 
        _globalDecodeIgnoreSequenceOfSizeConstraint = false; 
    }

    static bool 
    GlobalIsDecodeIgnoreSequenceOfSizeConstraint()
    { 
        return _globalDecodeIgnoreSequenceOfSizeConstraint; 
    }

    // Encode Ignore Sequence of Size Constraint.

    static void 
    GlobalSetEncodeIgnoreSequenceOfSizeConstraint()
    { 
        _globalEncodeIgnoreSequenceOfSizeConstraint = true; 
    }

    static void 
    GlobalUnsetEncodeIgnoreSequenceOfSizeConstraint()
    { 
        _globalEncodeIgnoreSequenceOfSizeConstraint = false; 
    }

    static bool 
    GlobalIsEncodeIgnoreSequenceOfSizeConstraint()
    { 
        return _globalEncodeIgnoreSequenceOfSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Set of Size Constraint.

    static void 
    GlobalSetDecodeIgnoreSetOfSizeConstraint()
    { 
        _globalDecodeIgnoreSetOfSizeConstraint = true; 
    }

    static void 
    GlobalUnsetDecodeIgnoreSetOfSizeConstraint()
    { 
        _globalDecodeIgnoreSetOfSizeConstraint = false; 
    }

    static bool 
    GlobalIsDecodeIgnoreSetOfSizeConstraint()
    { 
        return _globalDecodeIgnoreSetOfSizeConstraint; 
    }

    // Encode Ignore Set of Size Constraint.

    static void 
    GlobalSetEncodeIgnoreSetOfSizeConstraint()
    { 
        _globalEncodeIgnoreSetOfSizeConstraint = true; 
    }

    static void 
    GlobalUnsetEncodeIgnoreSetOfSizeConstraint()
    { 
        _globalEncodeIgnoreSetOfSizeConstraint = false; 
    }

    static bool 
    GlobalIsEncodeIgnoreSetOfSizeConstraint()
    { 
        return _globalEncodeIgnoreSetOfSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Bit String Size Constraint.

    static void 
    GlobalSetDecodeIgnoreBitStringSizeConstraint()
    { 
        _globalDecodeIgnoreBitStringSizeConstraint = true; 
    }

    static void 
    GlobalUnsetDecodeIgnoreBitStringSizeConstraint()
    { 
        _globalDecodeIgnoreBitStringSizeConstraint = false; 
    }

    static bool 
    GlobalIsDecodeIgnoreBitStringSizeConstraint()
    { 
        return _globalDecodeIgnoreBitStringSizeConstraint; 
    }

    // Encode Ignore Bit String Size Constraint.

    static void 
    GlobalSetEncodeIgnoreBitStringSizeConstraint()
    { 
        _globalEncodeIgnoreBitStringSizeConstraint = true; 
    }

    static void 
    GlobalUnsetEncodeIgnoreBitStringSizeConstraint()
    { 
        _globalEncodeIgnoreBitStringSizeConstraint = false; 
    }

    static bool 
    GlobalIsEncodeIgnoreBitStringSizeConstraint()
    { 
        return _globalEncodeIgnoreBitStringSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Ignore Base String Size Constraint.

    static void 
    GlobalSetDecodeIgnoreBaseStringSizeConstraint()
    { 
        _globalDecodeIgnoreBaseStringSizeConstraint = true; 
    }

    static void 
    GlobalUnsetDecodeIgnoreBaseStringSizeConstraint()
    { 
        _globalDecodeIgnoreBaseStringSizeConstraint = false; 
    }

    static bool 
    GlobalIsDecodeIgnoreBaseStringSizeConstraint()
    { 
        return _globalDecodeIgnoreBaseStringSizeConstraint; 
    }

    // Encode Ignore Base String Size Constraint.

    static void 
    GlobalSetEncodeIgnoreBaseStringSizeConstraint()
    { 
        _globalEncodeIgnoreBaseStringSizeConstraint = true; 
    }

    static void 
    GlobalUnsetEncodeIgnoreBaseStringSizeConstraint()
    { 
        _globalEncodeIgnoreBaseStringSizeConstraint = false; 
    }

    static bool 
    GlobalIsEncodeIgnoreBaseStringSizeConstraint()
    { 
        return _globalEncodeIgnoreBaseStringSizeConstraint; 
    }

    ////////////////////////////////////////////////////////////

    // Decode Process Unknown Elements.

    static void 
    GlobalSetDecodeProcessUnknownElements()
    { 
        _globalDecodeProcessUnknownElements = true; 
    }

    static void 
    GlobalUnsetDecodeProcessUnknownElements()
    { 
        _globalDecodeProcessUnknownElements = false; 
    }

    static bool 
    GlobalIsDecodeProcessUnknownElements()
    { 
        return _globalDecodeProcessUnknownElements; 
    }

    // Encode Process Unknown Elements.

    static void 
    GlobalSetEncodeProcessUnknownElements()
    { 
        _globalEncodeProcessUnknownElements = true; 
    }

    static void 
    GlobalUnsetEncodeProcessUnknownElements()
    { 
        _globalEncodeProcessUnknownElements = false;
    }

    static bool 
    GlobalIsEncodeProcessUnknownElements()
    { 
        return _globalEncodeProcessUnknownElements; 
    }

    ////////////////////////////////////////////////////////////

    // Encode XML without separators.

    static void 
    GlobalSetEncodeXmlWithoutSeparators()
    { 
        _globalEncodeXmlWithoutSeparators = true; 
    }

    static void 
    GlobalUnsetEncodeXmlWithoutSeparators()
    { 
        _globalEncodeXmlWithoutSeparators = false; 
    }

    static bool 
    GlobalIsEncodeXmlWithoutSeparators()
    { 
        return _globalEncodeXmlWithoutSeparators; 
    }

    ////////////////////////////////////////////////////////////

    // SET replace tag callbacks.

    static size_t
    GlobalGetSetReplaceTagCallbackSize()
    { 
        return _globalSetReplaceTagCallbacks.size(); 
    }

    static const ReplaceTagCallback& 
        GlobalSetReplaceTagCallbackAt(size_t index);

    static void 
        GlobalAddSetReplaceTagCallback(ReplaceTagCallback* callback);

    static void 
        GlobalRemoveSetReplaceTagCallback(size_t index);

    static void 
        RemoveAllSetReplaceTagCallbacks();

    ////////////////////////////////////////////////////////////

    // SEQUENCE replace tag callbacks.

    static size_t
    GlobalGetSequenceReplaceTagCallbackSize()
    { 
        return _globalSequenceReplaceTagCallbacks.size(); 
    }

    static const 
        ReplaceTagCallback& GlobalSequenceReplaceTagCallbackAt(size_t index);

    static void 
        GlobalAddSequenceReplaceTagCallback(ReplaceTagCallback* callback);

    static void 
        GlobalRemoveSequenceReplaceTagCallback(size_t index);

    static void 
        RemoveAllSequenceReplaceTagCallbacks();

    ////////////////////////////////////////////////////////////

protected:

    //
    // Local (dynamic) options.
    //

    AsnEncodingRules _encodingRules;

    bool _decodeSkipInvalidEnumeratedValue;
    bool _encodeSkipInvalidEnumeratedValue;
    bool _decodeSkipUnknownElementInSequence;
    bool _decodeSkipUnknownElementInSet;
    bool _decodeIgnoreOctetStringSizeConstraint;
    bool _encodeIgnoreOctetStringSizeConstraint;
    bool _decodeIgnoreIntegerSizeConstraint;
    bool _encodeIgnoreIntegerSizeConstraint;
    bool _decodeIgnoreSequenceOfSizeConstraint;
    bool _encodeIgnoreSequenceOfSizeConstraint;
    bool _decodeIgnoreSetOfSizeConstraint;
    bool _encodeIgnoreSetOfSizeConstraint;
    bool _decodeIgnoreBitStringSizeConstraint;
    bool _encodeIgnoreBitStringSizeConstraint;
    bool _decodeIgnoreBaseStringSizeConstraint;
    bool _encodeIgnoreBaseStringSizeConstraint;
    bool _decodeProcessUnknownElements;
    bool _encodeProcessUnknownElements;
    bool _encodeXmlWithoutSeparators;


    //
    // Global (static) options.
    //

    static AsnEncodingRules _globalEncodingRules;

    static bool _globalDecodeSkipInvalidEnumeratedValue;
    static bool _globalEncodeSkipInvalidEnumeratedValue;
    static bool _globalDecodeSkipUnknownElementInSequence;
    static bool _globalDecodeSkipUnknownElementInSet;
    static bool _globalDecodeIgnoreOctetStringSizeConstraint;
    static bool _globalEncodeIgnoreOctetStringSizeConstraint;
    static bool _globalDecodeIgnoreIntegerSizeConstraint;
    static bool _globalEncodeIgnoreIntegerSizeConstraint;
    static bool _globalDecodeIgnoreSequenceOfSizeConstraint;
    static bool _globalEncodeIgnoreSequenceOfSizeConstraint;
    static bool _globalDecodeIgnoreSetOfSizeConstraint;
    static bool _globalEncodeIgnoreSetOfSizeConstraint;
    static bool _globalDecodeIgnoreBitStringSizeConstraint;
    static bool _globalEncodeIgnoreBitStringSizeConstraint;
    static bool _globalDecodeIgnoreBaseStringSizeConstraint;
    static bool _globalEncodeIgnoreBaseStringSizeConstraint;
    static bool _globalDecodeProcessUnknownElements;
    static bool _globalEncodeProcessUnknownElements;
    static bool _globalEncodeXmlWithoutSeparators;


    //
    //  Global (static) related to replace tag callbacks.
    //

    static std::vector<ReplaceTagCallback*> _globalSetReplaceTagCallbacks;
    static std::vector<ReplaceTagCallback*> _globalSequenceReplaceTagCallbacks;

};

extern const int    ASN_BITS_PER_BYTE;
extern const int    ASN_BITS_PER_LONG;
extern const int    ASN_BYTES_PER_INT;
extern const int    ASN_BYTES_PER_LONG;
extern const int    ASN_BYTES_PER_DOUBLE;
extern const long   ASN_BYTE_MASK_IN_LONG;
extern const long   ASN_SHORT_MASK_IN_LONG;
extern const long   ASN_INT_MASK_IN_LONG;
extern const int    ASN_BYTE_MASK_IN_INT;
extern const int    ASN_SHORT_MASK_IN_INT;
extern const short  ASN_BYTE_MASK_IN_SHORT;
extern const byte   ASN_ALL_BITS_SET;
extern const byte   ASN_SIGN_BIT;

} // namespace its.

#endif // !defined(_ASN_H_)
