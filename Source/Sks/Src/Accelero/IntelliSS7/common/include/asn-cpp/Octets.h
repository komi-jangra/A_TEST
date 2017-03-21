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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:07  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:59  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:53  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:55  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:58  cvsadmin
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
// LOG: Revision 5.4  2002/01/07 22:59:02  hdivoux
// LOG: First shot at XER encoding.
// LOG:
// LOG: Revision 5.3  2001/11/16 01:28:04  mmiers
// LOG: Warning avoidance (reordering member constructors).
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:53  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime Octets class definition.
//

#if !defined(_ASN_OCTETS_H_)
#define _ASN_OCTETS_H_

#ident "$Id: Octets.h,v 1.1.1.1 2007-10-08 11:11:37 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>

namespace its {

class Octets 
{
public:

    Octets() 
    :   _offset(0)
    {}

    Octets(const std::vector<byte>& array) 
    :   _offset(0),
        _data(array.begin(), array.end())
    {
        // Nothing else to do.
    }

    Octets(const std::vector<byte>& array, size_t size) 
    :   _offset(0),
        _data(array.begin(), array.begin() + size)
    {
        // Nothing else to do.
    }

    Octets(const Octets& rhs)
    :   _offset(rhs._offset),
        _data(rhs._data.begin(), rhs._data.end())
    {
        // Nothing else to do.
    }

    virtual ~Octets()
    {
        // Nothing to do.
    }

    Octets& operator=(const Octets& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            _data.erase(_data.begin(), _data.end());
            _data.insert(_data.end(), rhs._data.begin(), rhs._data.end());
            _offset = rhs._offset;
            return *this;
        }
    }

    bool 
    operator==(const Octets& rhs) const
    { 
        return Equals(rhs); 
    }

    size_t 
    GetSize() const
    { 
        return _data.size(); 
    }

    size_t
    GetOffset() const
    { 
        return _offset; 
    }

    void 
    SetOffset(size_t offset)
    { 
        _offset = offset; 
    }

    void 
    IncrementOffset()
    { 
        _offset++; 
    }

    void 
    IncrementOffset(size_t increment)
    {
        _offset = _offset + increment;
    }

    void 
    DecrementOffset()
    { 
        _offset--; 
    }

    void 
    DecrementOffset(size_t decrement)
    {
        ITS_REQUIRE(GetOffset() >= decrement);
        _offset = _offset - decrement;
    }

    bool 
    IsIndexValid(size_t index) const
    { 
        return index < GetSize(); 
    }

    bool 
    IsIndexWithOffsetValid(size_t index) const
    { 
        return (index + _offset) < GetSize(); 
    }

    bool 
    IsOffsetValid() const 
    { 
        return _offset < GetSize(); 
    }

    void 
    SetArray(const std::vector<byte>& array)
    {
        _data.erase(_data.begin(), _data.end());
        _data.insert(_data.end(), array.begin(), array.end());
    }

    void 
    SetArray(const std::vector<byte>& array, size_t size)
    {
        _data.erase(_data.begin(), _data.end());
        _data.insert(_data.begin(), array.begin(), array.begin() + size);
    }

    const std::vector<byte>& 
    GetArray()
    {
        return _data;
    }

    const std::vector<byte>& 
    GetArrayWithOffset()
    {
        ITS_REQUIRE(IsOffsetValid());
        _dataWithOffset.erase(
            _dataWithOffset.begin(),
            _dataWithOffset.end());
        _dataWithOffset.insert(
            _dataWithOffset.end(),
            _data.begin() + _offset, 
            _data.end());
        return _dataWithOffset;
    }

    byte 
    GetOctetAt(size_t index) const
    {
        ITS_REQUIRE(IsIndexValid(index));
        return _data[index];
    }

    void 
    SetOctetAt(size_t index, byte octet)
    {
        ITS_REQUIRE(IsIndexValid(index));
        _data[index] = octet;
    }

    byte 
    GetOctetAtWithOffset(size_t index) const
    {
        ITS_REQUIRE(IsIndexWithOffsetValid(index));
        return _data[index + _offset];
    }

    void 
    SetOctetAtWithOffset(size_t index, byte octet)
    {
        ITS_REQUIRE(IsIndexWithOffsetValid(index));
        _data[index + _offset] = octet;
    }

    Octets 
    SubOctets(size_t beginIndex, size_t endIndex)
    {
        ITS_REQUIRE(IsIndexValid(beginIndex));
        ITS_REQUIRE(IsIndexValid(endIndex - 1));
        ITS_REQUIRE(beginIndex < endIndex);
        std::vector<byte> array;
        array.insert(
            array.begin(), 
            _data.begin() + beginIndex, 
            _data.begin() + endIndex);
        Octets result(array, array.size());
        return result;
    }

    void 
    Concat(const Octets& rhs)
    {
        size_t prevSize = GetSize();
        _data.insert(_data.end(), rhs._data.begin(), rhs._data.end());
        ITS_ENSURE(GetSize() == prevSize + rhs.GetSize());
    }

    Octets& 
    operator+=(const Octets& rhs)
    {
        Concat(rhs);
        return *this;
    }

    bool Equals(const Octets& rhs) const;

    void Print(std::ostream& os, size_t level = 0) const;

    void PrintWithOffset(std::ostream& os, size_t level = 0) const;

    // Obsolete (for backward compatibility only).
    size_t 
    GetLength() const
    { 
        return _data.size(); 
    }

protected:

    static void PrintArray(
                    const std::vector<byte>& array, 
                    std::ostream& os,
                    size_t level = 0);

    static std::string GetLevelShift(size_t level);

    size_t              _offset;
    std::vector<byte>   _data;
    std::vector<byte>   _dataWithOffset;
};


// Octets ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, Octets& octets);

} // namespace its.

#endif // !defined(_ASN_OCTETS_H_) 

