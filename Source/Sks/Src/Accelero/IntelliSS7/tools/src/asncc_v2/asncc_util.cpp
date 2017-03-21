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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:42  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:20  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:53  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:15  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:53:01  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.4  2002/02/21 15:43:47  hdivoux
// LOG: Correction for vector of characters to string conversion.
// LOG:
// LOG: Revision 5.3  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: asncc_util.cpp,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $"


#if defined(WIN32)
#include <io.h>
#include <direct.h>
#elif defined(unix)
#include <unistd.h>
#include <sys/stat.h>
#endif  // defined(WIN32)

#include <stdio.h>
#include <stdarg.h>

#include <asncc_util.h>
#include <asncc_assertion.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  StripPath.
//

string StripPath(const string& fileName)
{
#if defined(WIN32)
    char separator = '\\';
#else
    char separator = '/';
#endif    // defined(WIN32)

    string::size_type position = fileName.find_last_of(separator);
    
    if (position == string::npos)
    {
        return fileName;
    }
    else
    {
        return fileName.substr(position + 1);
    }
}


////////////////////////////////////////////////////////////////////////////////
//
//  LongToString.
//

string
LongToString(long l)
{
    char buffer[32];
    memset(buffer, 0, 32);

    sprintf(buffer, "%ld", l);

    string result = buffer;

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  IntToString.
//

string
IntToString(int i)
{
    char buffer[32];
    memset(buffer, 0, 32);

    sprintf(buffer, "%d", i);

    string result = buffer;

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  AutoIndent.
//

string AutoIndent(const string& str)
{
    string result = str;

    result.insert(0, "    ");

    for (int i = 0; i < (int)result.size(); i++)
    {
        char c = result[i];

        if (c == '\n' && i < (int)(result.size() - 1))
        {
            result.insert(i + 1, "    ");
            i = i + 4;
        }
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  AdaptName.
//

//
// Adapt an ASN.1 name:
//
//  [1] Replace all occurrences of characters '-' and ' ' by character '_'.
//
//  [2] If first character is lowercase change to uppercase.
//

string 
AdaptName(const string& str)
{
    string result = str;

    for (size_t i = 0; i < result.size(); i++)
    {
        if (result[i] == '-' || result[i] == ' ')
        {
            result[i] = '_';
        }

        if (i == 0)
        {
            result[0] = (char)toupper(result[0]);
        }
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  AdaptNameToUppercase.
//

//
// Adapt an ASN.1 name:
//
//  [1] Replace all occurrences of characters '-' and ' ' by character '_'.
//
//  [2] Change all characters to uppercase and add character '_' if correct
//      alternation of lowercase and uppercase (i.e. fooBar -> FOO_BAR).

string 
AdaptNameToUppercase(const string& str)
{
    bool prevIsLower            = false;
    bool prevPrevIsLower        = true;
    bool prevIsUnderscore       = false;
    bool prevPrevIsUnderscore   = true;

    vector<char> vectorResult;

    vectorResult.reserve(str.size() * 2 + 1); // Maximum possible size.

    vectorResult.assign(str.size() * 2 + 1, '\0');

    int j = 0;
    
    for (size_t i = 0; i < str.size(); i++)
    {
        if (prevIsLower && 
            isupper(str[i]) && 
            i != 1 &&
            !prevIsUnderscore )
        {
            vectorResult[j++] = '_';
        }

        if (!prevPrevIsLower && 
            !prevIsLower && 
            islower(str[i]) &&
            i != 1 &&
            !prevIsUnderscore &&
            !prevPrevIsUnderscore)
        {
            ASSERT(j >= 1);

            vectorResult[j] = vectorResult[j - 1];
            j++;
            vectorResult[j - 2] = '_';  // Already incremented by one.
        }

        if (str[i] == '-')
        {
            vectorResult[j++] = '_';
        }
        else if (str[i] == ' ')
        {
            vectorResult[j++] = '_';
        }
        else
        {
            vectorResult[j++] = toupper(str[i]);
        }

        prevPrevIsLower = prevIsLower;

        if (islower(str[i]))
        {
            prevIsLower = true;
        }
        else
        {
            prevIsLower = false;
        }

        prevPrevIsUnderscore = prevIsUnderscore;

        ASSERT(j >= 1);

        if (vectorResult[j - 1] == '_')
        {
            prevIsUnderscore = true;
        }
        else
        {
            prevIsUnderscore = false;
        }
    }

    vectorResult[j++] = '\0';

    string result(&vectorResult[0]);

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  AdaptNameToLowercase.
//

//
// Adapt an ASN.1 name:
//
//  [1] Replace all occurrences of characters '-' and ' ' by character '_'.
//
//  [2] Change all characters to lowercase and add character '_' if correct
//      alternation of lowercase and uppercase (i.e. fooBar -> foo_bar).

string 
AdaptNameToLowercase(const string& str)
{
    string result = AdaptNameToUppercase(str);

    for (size_t i = 0; i < result.size(); i++)
    {
        result[i] = tolower(result[i]);
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  AdaptModuleName.  
//

//
// Adapt an ASN.1 module name:
//
//  [1] Replace all occurrences of characters '-' and ' ' by character '_'.
//

string 
AdaptModuleName(const string& str)
{
    string result = str;

    for (size_t i = 0; i < result.size(); i++)
    {
        if (result[i] == '-' || result[i] == ' ')
        {
            result[i] = '_';
        }
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  CreateDirectory.
//

void 
CreateDirectory(const string& directoryName)
{
    string directoryNameToCreate = "./";

    directoryNameToCreate.append(directoryName);

    bool exist = !access(directoryNameToCreate.c_str(), 0);

    if (!exist)
    {
#if defined(WIN32)
        if (mkdir(directoryNameToCreate.c_str()))
#elif defined(unix)
        if (mkdir(directoryNameToCreate.c_str(), S_IRWXU | S_IRWXG))
#endif  // defined(WIN32)
        {
            cerr << "AsnCC Status : Error - unable to create directory \"";
            cerr << directoryNameToCreate;
            cerr << "\".";
            cerr << endl;

            // TODO: is it a fatal error?
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
//
//  WriteTextToFile. 
//

void 
WriteTextToFile(
            const string& directoryName,
            const string& fileNameCore,
            const string& fileNameExtension,
            const string& text)
{
    string fileName = "./";

    if (directoryName != "")
    {
        // Try to create directory.

        CreateDirectory(directoryName);

        fileName.append(directoryName);
        fileName.append("/");
    }

    fileName.append(fileNameCore);
    fileName.append(".");
    fileName.append(fileNameExtension);

    FILE* fdesc = fopen(fileName.c_str(), "w");

    if (fdesc == NULL)
    {
        cerr << "AsnCC Status : ERROR - unable to open file \"";
        cerr << fileName;
        cerr << "\" for writing.";
        cerr << endl;

        return;
    }
        
    // Write in small chunks.

    const size_t CHUNK = 256;
    size_t sizeWritten = 0;

    string chunk;
    chunk.reserve(2 * CHUNK);   // To avoid too many reallocations.

    for (size_t i = 0; i < text.size(); i++)
    {
        chunk.append(1, text[i]);

        if (chunk.size() == CHUNK)
        {
            sizeWritten = fprintf(fdesc, "%s", chunk.c_str());

            if (sizeWritten != CHUNK)
            {
                cerr << "AsnCC Status : ERROR - invalid write operation to file \"";
                cerr << fileName;
                cerr << "\".";
                cerr << endl;

                fclose(fdesc);

                return;
            }
            
            chunk.erase(chunk.begin(), chunk.end());
        }
    }

    if (chunk.size() != 0)
    {
        sizeWritten = fprintf(fdesc, "%s", chunk.c_str());

        if (sizeWritten != chunk.size())
        {
            cerr << "AsnCC Status : ERROR - invalid write operation to file \"";
            cerr << fileName;
            cerr << "\".";
            cerr << endl;
        }
    }

    fclose(fdesc);
}


////////////////////////////////////////////////////////////////////////////////
//
//  std::string operator<<. 
//

ostream& operator<<(ostream& os, const string& str)
{
    os << str.c_str();
    return os;
}



