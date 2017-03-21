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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:12  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:02  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1  2007/03/30 04:53:07  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.1.1.1  2006/12/22 13:34:21  cvsadmin
// LOG: Initialising sources in CVS
// LOG:
// LOG: Revision 8.3  2005/03/21 13:51:17  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.6  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.5  2002/01/10 00:09:56  hdivoux
// LOG: Update for first working XER encoding.
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

#ident "$Id: Asn.cpp,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $"

//
// ASN.1 runtime common and AsnOptions class implementation.
//

#include <its_mutex.h>
#include <its_support_exception.h>

#include <Asn.h>

using namespace std;

namespace its {

// Unique lock for ASN.1 Runtime.
static ITS_MUTEX _asnLock;

// Initialization toggle.
static int _asnInitialized = false;

//////////////////////////////////////////////////////////////////////
//
//  Asn.
//

void Asn::Initialize()
{
    if (_asnInitialized)
    {
        return;
    }

    int res = MUTEX_CreateMutex(&_asnLock, 0);
    if (res != ITS_SUCCESS)
    {
        throw ITS_Error(res, __FILE__, __LINE__);
    }

    _asnInitialized = true;
}


void Asn::Terminate()
{
    if (!_asnInitialized)
    {
        return;
    }

    MUTEX_DeleteMutex(&_asnLock);

    _asnInitialized = false;
}


void Asn::Lock()
{
    int res = MUTEX_AcquireMutex(&_asnLock);
    if (res != ITS_SUCCESS)
    {
        throw ITS_Error(res, __FILE__, __LINE__);
    }
}


void Asn::Unlock()
{
    int res = MUTEX_ReleaseMutex(&_asnLock);
    if (res != ITS_SUCCESS)
    {
        throw ITS_Error(res, __FILE__, __LINE__);
    }
}


//////////////////////////////////////////////////////////////////////
//
//  ASN.1 automatic initialization and termination.
//
//  Rely on the fact that a class static variable is initialized 
//  before main() is invoked.
//

class AutoInitializer
{
public:

    AutoInitializer()
    {
        Asn::Initialize();
    }

    ~AutoInitializer()
    {
        Asn::Terminate();
    }
};

// Constructor called before main() and destructor called after main().
static AutoInitializer _autoInitializer;


//////////////////////////////////////////////////////////////////////
//
//  AsnOptions.
//

AsnOptions::AsnEncodingRules 
    AsnOptions::_globalEncodingRules = 
        AsnOptions::ASN_BER_ENCODING_RULES;

bool AsnOptions::_globalDecodeSkipInvalidEnumeratedValue            = false;
bool AsnOptions::_globalEncodeSkipInvalidEnumeratedValue            = false;
bool AsnOptions::_globalDecodeSkipUnknownElementInSequence          = false;
bool AsnOptions::_globalDecodeSkipUnknownElementInSet               = false;
bool AsnOptions::_globalDecodeIgnoreOctetStringSizeConstraint       = false;
bool AsnOptions::_globalEncodeIgnoreOctetStringSizeConstraint       = false;
bool AsnOptions::_globalDecodeIgnoreIntegerSizeConstraint           = false;
bool AsnOptions::_globalEncodeIgnoreIntegerSizeConstraint           = false;
bool AsnOptions::_globalDecodeIgnoreSequenceOfSizeConstraint        = false;
bool AsnOptions::_globalEncodeIgnoreSequenceOfSizeConstraint        = false;
bool AsnOptions::_globalDecodeIgnoreSetOfSizeConstraint             = false;
bool AsnOptions::_globalEncodeIgnoreSetOfSizeConstraint             = false;
bool AsnOptions::_globalDecodeIgnoreBitStringSizeConstraint         = false;
bool AsnOptions::_globalEncodeIgnoreBitStringSizeConstraint         = false;
bool AsnOptions::_globalDecodeIgnoreBaseStringSizeConstraint        = false;
bool AsnOptions::_globalEncodeIgnoreBaseStringSizeConstraint        = false;
bool AsnOptions::_globalDecodeProcessUnknownElements                = false;
bool AsnOptions::_globalEncodeProcessUnknownElements                = false;
bool AsnOptions::_globalEncodeXmlWithoutSeparators                  = false;

vector<ReplaceTagCallback*> AsnOptions::_globalSetReplaceTagCallbacks;
vector<ReplaceTagCallback*> AsnOptions::_globalSequenceReplaceTagCallbacks;

const ReplaceTagCallback& 
AsnOptions::GlobalSetReplaceTagCallbackAt(size_t index)
{
    ITS_REQUIRE(index < GlobalGetSetReplaceTagCallbackSize());
    return *_globalSetReplaceTagCallbacks[index];
}

void 
AsnOptions::GlobalAddSetReplaceTagCallback(ReplaceTagCallback* callback)
{
    ITS_REQUIRE(callback != NULL);
    _globalSetReplaceTagCallbacks.push_back(callback);
}

void 
AsnOptions::GlobalRemoveSetReplaceTagCallback(size_t index)
{
    ITS_REQUIRE(index < GlobalGetSetReplaceTagCallbackSize());
    vector<ReplaceTagCallback*>::iterator iter = 
        _globalSetReplaceTagCallbacks.begin();
    for (size_t i = 0; i < index; i++)
    {
        iter++;
    }
    _globalSetReplaceTagCallbacks.erase(iter);
}

void 
AsnOptions::RemoveAllSetReplaceTagCallbacks()
{
    _globalSetReplaceTagCallbacks.erase(
        _globalSetReplaceTagCallbacks.begin(),
        _globalSetReplaceTagCallbacks.end());
}

const ReplaceTagCallback& 
AsnOptions::GlobalSequenceReplaceTagCallbackAt(size_t index)
{
    ITS_REQUIRE(index < GlobalGetSequenceReplaceTagCallbackSize());
    return *_globalSequenceReplaceTagCallbacks[index];
}

void 
AsnOptions::GlobalAddSequenceReplaceTagCallback(ReplaceTagCallback* callback)
{
    ITS_REQUIRE(callback != NULL);
    _globalSequenceReplaceTagCallbacks.push_back(callback);
}

void 
AsnOptions::GlobalRemoveSequenceReplaceTagCallback(size_t index)
{
    ITS_REQUIRE(index < GlobalGetSequenceReplaceTagCallbackSize());
    vector<ReplaceTagCallback*>::iterator iter = 
        _globalSequenceReplaceTagCallbacks.begin();
    for (size_t i = 0; i < index; i++)
    {
        iter++;
    }
    _globalSequenceReplaceTagCallbacks.erase(iter);
}

void 
AsnOptions::RemoveAllSequenceReplaceTagCallbacks()
{
    _globalSequenceReplaceTagCallbacks.erase(
        _globalSequenceReplaceTagCallbacks.begin(),
        _globalSequenceReplaceTagCallbacks.end());
}

//////////////////////////////////////////////////////////////////////
//
//  Other constants.
//

const int   ASN_BITS_PER_BYTE       = 8;
const int   ASN_BITS_PER_LONG       = 32;
const int   ASN_BYTES_PER_INT       = 4;
const int   ASN_BYTES_PER_LONG      = 4;
const int   ASN_BYTES_PER_DOUBLE    = 8;
const long  ASN_BYTE_MASK_IN_LONG   = 0x000000FF;
const long  ASN_SHORT_MASK_IN_LONG  = 0x0000FFFF;
const long  ASN_INT_MASK_IN_LONG    = 0xFFFFFFFF;
const int   ASN_BYTE_MASK_IN_INT    = 0x000000FF;
const int   ASN_SHORT_MASK_IN_INT   = 0x0000FFFF;
const short ASN_BYTE_MASK_IN_SHORT  = 0x00FF;
const byte  ASN_ALL_BITS_SET        = (byte)0xFFU;
const byte  ASN_SIGN_BIT            = (byte)0x80U;

} // namespace its.

