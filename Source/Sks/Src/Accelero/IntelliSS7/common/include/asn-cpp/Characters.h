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
// LOG: Revision 1.3  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 1.2  2002/01/07 22:59:02  hdivoux
// LOG: First shot at XER encoding.
// LOG:
// LOG: Revision 1.1  2002/01/02 23:37:11  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime Characters class definition.
//

#if !defined(_ASN_CHARACTERS_H_)
#define _ASN_CHARACTERS_H_

#ident "$Id: Characters.h,v 1.1.1.1 2007-10-08 11:11:36 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>

namespace its {

class Characters 
{
public:

    Characters() 
    :   _offset(0)
    {}

    Characters(const std::string& str) 
    :   _offset(0),
        _data(str)
    {
        // Nothing else to do.
    }

    Characters(const std::string& str, size_t size) 
    :   _offset(0),
        _data(str.begin(), str.begin() + size)
    {
        // Nothing else to do.
    }

    Characters(const Characters& rhs)
    :   _offset(rhs._offset),
        _data(rhs._data)
    {
        // Nothing else to do.
    }

    virtual ~Characters()
    {
        // Nothing to do.
    }

    Characters& operator=(const Characters& rhs)
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
    operator==(const Characters& rhs) const
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
    SetString(const std::string& str)
    {
        _data.erase(_data.begin(), _data.end());
        _data.insert(_data.end(), str.begin(), str.end());
    }

    void 
    SetString(const std::string& str, size_t size)
    {
        _data.erase(_data.begin(), _data.end());
        _data.insert(_data.begin(), str.begin(), str.begin() + size);
    }

    const std::string& 
    GetString()
    {
        return _data;
    }

    const std::string& 
    GetStringWithOffset()
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

    char 
    GetCharAt(size_t index) const
    {
        ITS_REQUIRE(IsIndexValid(index));
        return _data[index];
    }

    void 
    SetCharAt(size_t index, char c)
    {
        ITS_REQUIRE(IsIndexValid(index));
        _data[index] = c;
    }

    char 
    GetCharAtWithOffset(size_t index) const
    {
        ITS_REQUIRE(IsIndexWithOffsetValid(index));
        return _data[index + _offset];
    }

    void 
    SetCharAtWithOffset(size_t index, char c)
    {
        ITS_REQUIRE(IsIndexWithOffsetValid(index));
        _data[index + _offset] = c;
    }

    Characters 
    SubCharacters(size_t beginIndex, size_t endIndex)
    {
        ITS_REQUIRE(IsIndexValid(beginIndex));
        ITS_REQUIRE(IsIndexValid(endIndex - 1));
        ITS_REQUIRE(beginIndex < endIndex);
        std::string str;
        str.insert(
            str.begin(), 
            _data.begin() + beginIndex, 
            _data.begin() + endIndex);
        Characters result(str, str.size());
        return result;
    }

    void 
    Concat(const Characters& rhs)
    {
        size_t prevSize = GetSize();
        _data.insert(_data.end(), rhs._data.begin(), rhs._data.end());
        ITS_ENSURE(GetSize() == prevSize + rhs.GetSize());
    }

    Characters& 
    operator+=(const Characters& rhs)
    {
        Concat(rhs);
        return *this;
    }

    void 
    Concat(const std::string& str)
    {
        size_t prevSize = GetSize();
        _data += str;
        ITS_ENSURE(GetSize() == prevSize + str.size());
    }

    Characters&
    operator+=(const std::string& str)
    {
        Concat(str);
        return *this;
    }

    bool Equals(const Characters& rhs) const;

    void Print(std::ostream& os, size_t level = 0) const;

    void PrintWithOffset(std::ostream& os, size_t level = 0) const;

protected:

    static void PrintString(
                    const std::string& str, 
                    std::ostream& os,
                    size_t level = 0);

    static std::string GetLevelShift(size_t level);

    size_t      _offset;
    std::string _data;
    std::string _dataWithOffset;
};


// Characters ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, Characters& characters);

} // namespace its.

#endif // !defined(_ASN_CHARACTERS_H_) 

