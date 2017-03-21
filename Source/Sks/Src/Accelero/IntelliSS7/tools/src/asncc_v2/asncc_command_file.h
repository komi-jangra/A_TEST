///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//            Copyright 1999 - 2002 IntelliNet Technologies, Inc.            //
//                          All Rights Reserved.                             //
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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:41  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:19  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:45  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:13  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:52:58  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(_ASNCC_COMMAND_FILE_H_)
#define _ASNCC_COMMAND_FILE_H_

#ident "$Id: asncc_command_file.h,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"

#include <asncc.h>
#include <asncc_assertion.h>


////////////////////////////////////////////////////////////////////////////////
//
//  CommandFileError.
//

class CommandFileError : public GenericException
{
public:

    CommandFileError(const std::string& errorText,
                     const std::string& fileParam,
                     unsigned long lineParam)
    :   GenericException("Command File Error", fileParam, lineParam)
    {
        fields.push_back(errorText);
    }

    // Default copy constructor ok.

    virtual ~CommandFileError() throw() 
    {
        // Nothing to do.
    }

    // Default assignment operator ok.

private:

    CommandFileError() {};
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Useful macros for exception.


#define ASNCC_COMMAND_FILE_THROW_ERROR_TEXT(text)           \
throw CommandFileError((text), __FILE__, __LINE__);



////////////////////////////////////////////////////////////////////////////////
//
//  Section.
//

class Section
{
public:

    explicit Section(const std::string& nameParam)
    :   name(nameParam)
    {};

    // Default copy constructor ok.

    virtual ~Section()
    {
        // Nothing to do.
    }

    // Default assignment operator ok.

    bool HasUniqueKey(const std::string& keyName) const;

    bool HasMultiKey(const std::string& keyName) const;

    const std::string& GetUniqueValue(const std::string& keyName) const;

    typedef std::vector<std::string> TypeValues;

    const TypeValues& GetMultiValues(const std::string& keyName) const;

    const std::string& 
    GetName() const
    { return name; }


    // Next two member functions to be used only by CommandFile class.

    void InsertKeyValue(const std::string& keyName, const std::string& value);

    void Clear()
    { keyValues.clear(); }

protected:

    std::string name;

    typedef std::map<std::string, TypeValues> TypeKeyValues;

    TypeKeyValues keyValues;

private:

    Section() {};

};


////////////////////////////////////////////////////////////////////////////////
//
//  CommandFile.
//

class CommandFile
{
public:

    explicit CommandFile(const std::string& pathParam)
    :   path(pathParam),
        parsed(false),
        globalSection("")
    {};

    bool HasSection(const std::string& sectionName) const;

    const Section& GetSection(const std::string& sectionName) const;

    const Section& 
    GetGlobalSection() const
    { 
        REQUIRE(IsParsed());

        return globalSection;
    }

    const std::string&
    GetPath() const
    { return path; }

    void Parse();

    bool IsParsed() const
    { return parsed; }

protected:

    std::string path;

    bool parsed;

    Section globalSection;

    typedef std::map<std::string, Section> TypeSections;

    TypeSections sections;

private:

    CommandFile() : globalSection("") {};
    CommandFile(const CommandFile&) : globalSection("") {};
    CommandFile& operator=(CommandFile&) { return *this; }

};

#endif  // !defined(_ASNCC_COMMAND_FILE_H_)

