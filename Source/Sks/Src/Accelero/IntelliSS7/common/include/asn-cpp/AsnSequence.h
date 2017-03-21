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
// LOG: Revision 1.1.1.1  2007/03/08 15:13:53  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:53  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.3  2005/03/21 13:50:57  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.7  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.6  2002/01/10 00:09:24  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.5  2002/01/02 23:23:28  hdivoux
// LOG: Start update for XER support.
// LOG:
// LOG: Revision 5.4  2001/12/24 21:03:21  hdivoux
// LOG: General update for options.
// LOG:
// LOG: Revision 5.3  2001/11/16 01:54:00  mmiers
// LOG: Warning avoidance.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:53  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime AsnSequence class definition.
//

#if !defined(_ASN_SEQUENCE_H_)
#define _ASN_SEQUENCE_H_

#ident "$Id: AsnSequence.h,v 1.1.1.1 2007-10-08 11:11:36 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <Tag.h>
#include <Length.h>
#include <AsnObject.h>
#include <AsnDescSequence.h>

namespace its {

class AsnSequence : public AsnObject
{
public:

    AsnSequence(size_t size, bool initialize = true)
    :   _elementVect(size)
    {
        ITS_REQUIRE(size >= 0);
        if (initialize)
        {
            Initialize();
        }
    }

    AsnSequence(
        size_t size, 
        Octets& octets,
        const AsnOptions& asnOptions = AsnOptions(),
        bool initialize = true)
    :   _elementVect(size) 
    {
        ITS_REQUIRE(size >= 0);
        if (initialize)
        {
            Initialize();
        }

        Decode(octets, asnOptions);
    }

    AsnSequence(const AsnSequence& rhs)
    :   AsnObject(rhs),
        _elementVect(rhs.GetSize())
    {
        ITS_ASSERT(GetSize() == rhs.GetSize());
        for (size_t i = 0; i < GetSize(); i++)
        {
            if (rhs._elementVect[i] != NULL)
            {
                AsnObject* element = rhs._elementVect[i];

                if (rhs._deleteSubcomponentsAutomatically)
                {
                    AsnObject* clonedElement = element->Clone();

                    _elementVect[i] = clonedElement;
                }
                else
                {
                    _elementVect[i] = element;
                }
            }
            else
            {
                _elementVect[i] = NULL;
            }
        }
    }

    AsnSequence(size_t size, AsnDescObject* description)
    :   _elementVect(size)
    {
        ITS_REQUIRE(size >= 0);
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

protected:

    void 
    Initialize()
    {
        ITS_ASSERT(_description == NULL);
        _description = GetStaticDescription();
    }

    static AsnDescObject* GetStaticDescription();

public:

    virtual ~AsnSequence()
    {
        RemoveAllElements();
    }

    AsnSequence& operator=(const AsnSequence& rhs);

    bool 
    operator==(const AsnSequence& rhs) const
    { 
        return Equals(rhs); 
    }

    const AsnDescSequence& 
    GetDescription() const
    {
        return *static_cast<AsnDescSequence*>(_description);
    }

    void 
    SetDescription(AsnDescSequence* description)
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

    static Tag* 
    GetUniversalTag()
    {
        return new Tag(
            Tag::ASN_CLASS_UNIVERSAL,
            Tag::ASN_CONSTRUCTED,
            Tag::ASN_SEQUENCE);
    }

    virtual AsnObject* 
    Clone() const
    { 
        return new AsnSequence(*this); 
    }

    virtual bool Equals(const AsnObject& rhs) const;

    size_t 
    GetSize() const
    { 
        return _elementVect.size(); 
    }

    const std::vector<AsnObject*>::const_iterator 
    ElementsBegin() const
    { 
        return _elementVect.begin(); 
    }

    const std::vector<AsnObject*>::const_iterator 
    ElementsEnd() const
    { 
        return _elementVect.end(); 
    }

    const std::vector<AsnObject*>& 
    Elements() const
    { 
        return _elementVect; 
    }

    const AsnObject& 
    ElementAt(size_t index) const
    {
        ITS_REQUIRE(index < GetSize());
        ITS_REQUIRE(Contains(index));
        return *_elementVect[index];
    }

    const AsnObject& 
    ElementAt(const Tag& tag) const
    {
        ITS_REQUIRE(Contains(tag));

        for (size_t i = 0; i < GetSize(); i++)
        {
            AsnObject* element = _elementVect[i];

            if (element != NULL && 
                element->GetPolymorphDescription().TagIdentify(tag))
            {
                return *element;
            }
        }

        bool must_not_be_reached = false;
        ITS_ASSERT(must_not_be_reached);
        AsnSequence *notReached = new AsnSequence(0);
        return *notReached;
    }

    bool 
    Contains(size_t index) const
    {
        ITS_REQUIRE(index < GetSize());
        return _elementVect[index] != NULL;
    }

    bool 
    Contains(const Tag& tag) const
    {
        for (size_t i = 0; i < GetSize(); i++)
        {
            AsnObject* element = _elementVect[i];

            if (element != NULL &&
                element->GetPolymorphDescription().TagIdentify(tag))
            {
                return true;
            }
        }

        return false;
    }

    void 
    AddElement(size_t index, AsnObject* element)
    {
        ITS_REQUIRE(index < GetSize());
        ITS_REQUIRE(element != NULL);
        if (_elementVect[index] != NULL)
        {
            if (_deleteSubcomponentsAutomatically)
            {
                delete _elementVect[index];
            }
        }

        _elementVect[index] = element;
    }

    void 
    AddElement(size_t index, const AsnObject& element)
    {
        ITS_REQUIRE(index < GetSize());
        if (_elementVect[index] != NULL)
        {
            if (_deleteSubcomponentsAutomatically)
            {
                delete _elementVect[index];
            }
        }

        if (_deleteSubcomponentsAutomatically)
        {
            AsnObject* clonedElement = element.Clone();
            ITS_ASSERT(clonedElement != NULL);
            _elementVect[index] = clonedElement;
        }
        else
        {
            _elementVect[index] = const_cast<AsnObject*>(&element);
        }
    }

    void 
    RemoveElement(size_t index)
    {
        ITS_REQUIRE(index < GetSize());
        ITS_REQUIRE(Contains(index));
        AsnObject* element = _elementVect[index];
        ITS_ASSERT(element != NULL);

        if (_deleteSubcomponentsAutomatically)
        {   
            delete element;
        }

        _elementVect[index] = NULL;
    }

    void 
    RemoveElement(const Tag& tag)
    {
        ITS_REQUIRE(Contains(tag));
        for (size_t i = 0; i < GetSize(); i++)
        {
            AsnObject* element = _elementVect[i];
            ITS_ASSERT(element != NULL);
            if (element->GetPolymorphDescription().TagIdentify(tag))
            {
                if (_deleteSubcomponentsAutomatically)
                {
                    delete element;
                }

                _elementVect[i] = NULL;
                break;
            }
        }            
    }

    void 
    RemoveAllElements()
    {
        for (size_t i = 0; i < GetSize(); i++)
        {
            AsnObject* element = _elementVect[i];

            if (element != NULL)
            {
                if (_deleteSubcomponentsAutomatically)
                {
                    delete element;
                }

                _elementVect[i] = NULL;
            }
        }
    }

    virtual std::string 
    GetName() const
    { 
        return "SEQUENCE"; 
    }

    virtual std::string 
    GetBaseName() const
    { 
        return "SEQUENCE"; 
    }

    virtual void Print(std::ostream& os, size_t level = 0) const;

    //
    // Unknown Elements related.
    //

    size_t
    GetUnknownElementSize() const
    { 
        return _unknownElementVect.size(); 
    }

    const Octets& 
    UnknownElementAt(size_t index) const
    {
        ITS_REQUIRE(index < GetUnknownElementSize());
        return _unknownElementVect[index];
    }

    void 
    AddUnknownElement(const Octets& octets)
    {
        ITS_REQUIRE(octets.GetSize() != 0);
        _unknownElementVect.push_back(octets);
    }

    void 
    RemoveUnknownElement(size_t index)
    {
        ITS_REQUIRE(index < GetUnknownElementSize());

        std::vector<Octets>::iterator iter = _unknownElementVect.begin();

        for (size_t i = 0; i < index; i++)
        {
            iter++;
        }

        _unknownElementVect.erase(iter);
    }

    void 
    RemoveAllUnknownElements()
    {
        _unknownElementVect.erase(
            _unknownElementVect.begin(), 
            _unknownElementVect.end());
    }

    // Obsolete (for backward compatibility only).
    size_t 
    Size() const
    { 
        return _elementVect.size(); 
    }

public: // Pseudo-protected.

    virtual Octets* InternalEncodeBer(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual void InternalDecodeBer(
                            Octets& octets,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual Octets* InternalEncodePer(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual void InternalDecodePer(
                            Octets& octets,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual Characters* InternalEncodeToXml(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual void InternalDecodeFromXml(
                            Characters& characters,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

protected:

    void EncodeCheck(const AsnOptions& asnOptions);
    Octets* EncodeReplaceElementTag(
                        Octets* elementOctets, 
                        const AsnOptions& asnOptions);
    void DecodeCheck(Octets& octets, const AsnOptions& asnOptions);
    void DecodeCheck(Characters& characters, const AsnOptions& asnOptions);
    void DecodeAddDefaults(const AsnOptions& asnOptions);
    Tag DecodeReplaceElementTag(
                        const Tag& elementTag, 
                        const Octets& octets,
                        const AsnOptions& asnOptions);

    std::vector<AsnObject*> _elementVect;
    std::vector<Octets>     _unknownElementVect;
};

} // namespace its.

#endif // !defined(_ASN_SEQUENCE_H_)
