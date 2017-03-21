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
// LOG: Revision 8.3  2005/03/21 13:52:58  cvsadmin
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

#ident "$Id: asncc_command_file.cpp,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"



#include <asncc_command_file.h>

//
//  Disable warning 4503 for Visual C++ (WIN32 specific).
//

#if defined(WIN32)
#pragma warning(disable : 4503)
#endif // defined(WIN32)


#if !defined(HPUX)
using namespace std;
#endif


////////////////////////////////////////////////////////////////////////////////
//
//  Section.
//

bool 
Section::HasUniqueKey(const string& keyName) const
{
    TypeKeyValues::const_iterator iter = keyValues.find(keyName);

    if (iter != keyValues.end())
    {
        const TypeValues& values = (*iter).second;

        if (values.size() == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool 
Section::HasMultiKey(const string& keyName) const
{
    TypeKeyValues::const_iterator iter = keyValues.find(keyName);

    if (iter != keyValues.end())
    {
        const TypeValues& values = (*iter).second;

        if (values.size() >= 1)
        {
            return true;
        }
        else
        { 
            return false;
        }
    }
    else
    {
        return false;
    }
}


const string& 
Section::GetUniqueValue(const string& keyName) const
{
    REQUIRE(HasUniqueKey(keyName));

    TypeKeyValues::const_iterator iter = keyValues.find(keyName);

    const TypeValues& values = (*iter).second;

    return values[0];
}


const Section::TypeValues&
Section::GetMultiValues(const string& keyName) const
{
    REQUIRE(HasMultiKey(keyName));

    TypeKeyValues::const_iterator iter = keyValues.find(keyName);

    const TypeValues& values = (*iter).second;

    return values;
}


void 
Section::InsertKeyValue(const string& keyName, const string& value)
{
    TypeKeyValues::iterator iter = keyValues.find(keyName);

    if (iter != keyValues.end())
    {
        TypeValues& values = (*iter).second;

        values.push_back(value);
    }
    else
    {
        TypeValues values;

        values.push_back(value);

        keyValues.insert(pair<const string, TypeValues>(keyName, values));
    }
}


////////////////////////////////////////////////////////////////////////////////
//
//  CommandFile.
//

bool
CommandFile::HasSection(const string& sectionName) const 
{
    REQUIRE(IsParsed());

    TypeSections::const_iterator iter = sections.find(sectionName);

    if (iter != sections.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}


const Section&
CommandFile::GetSection(const string& sectionName) const
{
    REQUIRE(IsParsed());
    REQUIRE(HasSection(sectionName));

    TypeSections::const_iterator iter = sections.find(sectionName);

    const Section& section = (*iter).second;

    return section;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Line.
//

class Line
{
public:

    Line(string rawContentsParam,
         string filePathParam,
         unsigned long lineNumberParam)
    :   rawContents(rawContentsParam),
        filePath(filePathParam),
        lineNumber(lineNumberParam),
        parsed(false),
        empty(false),
        comment(false),
        sectionHeader(false),
        keyValuePair(false)
    {};

    // Default copy constructor ok.

    // Destructor must not be virtual.

    ~Line()
    {
        // Nothing to do.
    }

    // Default assignment operator ok.

    const string& 
    GetRawContents() const
    { return rawContents; }

    bool 
    IsParsed() const
    { return parsed; }

    bool
    IsEmpty() const
    { 
        REQUIRE(IsParsed());
        return empty;
    }

    bool
    IsComment() const
    { 
        REQUIRE(IsParsed());
        return comment;
    }

    bool
    IsSectionHeader() const
    { 
        REQUIRE(IsParsed());
        return sectionHeader;
    }

    bool
    IsKeyValuePair() const
    { 
        REQUIRE(IsParsed());
        return keyValuePair;
    }

    const string&
    GetSectionName() const
    {
        REQUIRE(IsParsed());
        REQUIRE(IsSectionHeader());

        return sectionName;
    }

    const string&
    GetKeyName() const
    {
        REQUIRE(IsParsed());
        REQUIRE(IsKeyValuePair());

        return keyName;
    }

    const string&
    GetValue() const
    {
        REQUIRE(IsParsed());
        REQUIRE(IsKeyValuePair());

        return value;
    }

    void Parse();

protected:

    void ThrowParseError();

    string          rawContents;
    string          filePath;
    unsigned long   lineNumber;

    string          sectionName;
    string          keyName;
    string          value;

    bool            parsed;

    bool            empty;
    bool            comment;
    bool            sectionHeader;
    bool            keyValuePair;

private:

    Line() {};

};


void
Line::Parse()
{
    parsed = true;

    string cleanedContents;

    cleanedContents.reserve(rawContents.size());

    // Remove ' ', '\t', '\r' ...

    for (size_t i = 0; i < rawContents.size(); i++)
    {
        switch(rawContents[i])
        {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            // Nothing to do.
            break;

        default:
            cleanedContents += rawContents[i];
            break;
        }
    }

    // Is the line empty?

    if (cleanedContents.size() == 0)
    {
        empty = true;
        return;
    }

    ASSERT(cleanedContents.size() >= 1);

    // Is the line only a comment?

    if (cleanedContents[0] == '#')
    {
        comment = true;
        return;
    }

    // Remove potential comment part.

    string usefulContents;

    usefulContents.reserve(cleanedContents.size());

    for (size_t j = 0; j < cleanedContents.size(); j++)
    {
        bool stop = false;

        switch (cleanedContents[j])
        {
        case '#':
            stop = true;
            break;

        default:
            usefulContents += cleanedContents[j];
            break;
        }

        if (stop)
        {
            break;
        }
    }

    // Is the line empty?

    if (usefulContents.size() == 0)
    {
        empty = true;
        return;
    }

    ASSERT(usefulContents.size() >= 1);

    // Is the line a section header?

    if (usefulContents[0] == '[')
    {
        if (usefulContents.size() < 3)
        {
            ThrowParseError();
        }

        if (usefulContents[usefulContents.size() - 1] != ']')
        {
            ThrowParseError();
        }

        sectionName = usefulContents.substr(1, usefulContents.size() - 2);
        
        sectionHeader = true;
        return;
    }

    // Is the line a key value pair?

    if (usefulContents.find('=') != string::npos)
    {
        if (usefulContents.find('[') != string::npos ||
            usefulContents.find(']') != string::npos)
        {
            ThrowParseError();
        }

        string::size_type pos = usefulContents.find('=');

        if (pos == 0)
        {
            ThrowParseError();
        }

        keyName = usefulContents.substr(0, pos);

        if (keyName.size() == 0)
        {
            ThrowParseError();
        }

        value = usefulContents.substr(pos + 1, usefulContents.size() - pos + 1);

        if (value.size() == 0)
        {
            ThrowParseError();
        }

        keyValuePair = true;
        return;
    }

    // All other cases.

    ThrowParseError();
}

void
Line::ThrowParseError()
{
    char lineNumberText[32];
    memset(lineNumberText, 0, 32);

    sprintf(lineNumberText, "%ld", lineNumber);

    string errorText = "Failed to parse line <";
    errorText += lineNumberText;
    errorText += "> in file <";
    errorText += filePath;
    errorText += ">.";

    ASNCC_COMMAND_FILE_THROW_ERROR_TEXT(errorText);
}


void
CommandFile::Parse()
{
    if (parsed)
    {
        // Clean up results of previous parsing.

        sections.clear();

        globalSection.Clear();
    }

    ////////////////////////////////////////////////////////
    // Retrieve all lines (to be parsed later).

    vector<Line> lines;

    // Open and read specified configuration file.

    string filePath = path;

    ifstream ifs(filePath.c_str());

#if defined(HPUX)
    if (!ifs.good())
#else
    if (!ifs.is_open() || !ifs.good())
#endif
    {
        string errorText = "Failed to open file <";
        errorText += filePath;
        errorText += ">.";

        ASNCC_COMMAND_FILE_THROW_ERROR_TEXT(errorText);
    }

    string rawContents;

    unsigned long countLine = 1;

    while (!(ifs.rdstate() & ios::eofbit))
    {
        // Will next read operation fail? (Should never happen.)
        
        if (ifs.rdstate() & ios::failbit)
        {
            string errorText = "Failed to read file <";
            errorText += filePath;
            errorText += ">.";

            ASNCC_COMMAND_FILE_THROW_ERROR_TEXT(errorText);
        }

        getline(ifs, rawContents, '\n');

        // Is stream corrupted? (Should never happen.)

        if (ifs.rdstate() & ios::badbit)
        {
            string errorText = "Failed to read file <";
            errorText += filePath;
            errorText += ">.";

            ASNCC_COMMAND_FILE_THROW_ERROR_TEXT(errorText);
        }

        lines.push_back(Line(rawContents, filePath, countLine++));
    }

#if !defined(HPUX)
    ifs.close();
#endif

    ////////////////////////////////////////////////////////
    // Parse all lines.

    Section* currentSection = &globalSection;

    for (size_t i = 0; i < lines.size(); i++)
    {
        Line& line = lines[i];

        line.Parse();

        if (line.IsEmpty())
        {
            // Nothing to do.
        }
        else if (line.IsComment())
        {
            // Nothing to do.
        }
        else if (line.IsSectionHeader())
        {
            string sectionName = line.GetSectionName();

            if (sections.find(sectionName) != sections.end())
            {
                TypeSections::iterator iter = sections.find(sectionName);

                currentSection = &(*iter).second;
            }
            else
            {
                Section section(sectionName);

                sections.insert(
                    pair<const string, Section>(sectionName, section));

                TypeSections::iterator iter = sections.find(sectionName);

                currentSection = &(*iter).second;
            }
        }
        else if (line.IsKeyValuePair())
        {
            string keyName  = line.GetKeyName();
            string value    = line.GetValue();

            currentSection->InsertKeyValue(keyName, value);
        }
        else
        {
            bool must_not_be_reached = false;

            ASSERT(must_not_be_reached);
        }
    }

    parsed = true;
}






