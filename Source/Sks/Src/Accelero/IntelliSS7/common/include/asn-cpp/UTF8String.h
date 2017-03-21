//
// Generated by IntelliAsnCC ASN.1 compiler (C, C++, Java).
//
// Do not edit!
//
//
//
// (C) 2000, 2001 IntelliNet Technologies Inc. All Rights Reserved.
//
//


#if !defined(_ASN_USEFUL_UTF8_STRING_H_)
#define _ASN_USEFUL_UTF8_STRING_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBaseString.h>



namespace its {



class UTF8String : public its::AsnBaseString
{
public:

    UTF8String() : its::AsnBaseString(false)
    {
        Initialize();
    }

    UTF8String(const std::string& str) : its::AsnBaseString(str, false)
    {
        Initialize();
    }

    UTF8String(its::Octets& octets) : its::AsnBaseString(false)
    {
        Initialize();
        Decode(octets);
    }

    UTF8String(const UTF8String& rhs) : its::AsnBaseString(rhs)
    {
        // Nothing to do.
    }

    UTF8String(its::AsnDescObject* description) : its::AsnBaseString(description)
    {
        // Nothing to do.
    }

    UTF8String(its::AsnDescObject* description, const std::string& str) : its::AsnBaseString(description, str)
    {
        // Nothing to do.
    }

protected:

    void Initialize()
    {
        _description = GetStaticDescription();
    }

public:

    static its::AsnDescObject* GetStaticDescription();

public:

    virtual ~UTF8String()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UTF8String(*this);
    }

    virtual std::string GetName() const
    { return "UTF8String"; }

};



} // namespace.

#endif    // !defined(_ASN_USEFUL_UTF8_STRING_H_)

