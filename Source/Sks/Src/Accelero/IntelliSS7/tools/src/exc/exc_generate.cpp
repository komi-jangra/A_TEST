////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: exc_generate.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:43  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:21  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:56  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:17  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:53:08  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:19  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:37  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.4  2001/11/21 21:16:07  hdivoux
// LOG: Updated compiler version and copyright dates.
// LOG:
// LOG: Revision 5.3  2001/11/15 22:23:32  hdivoux
// LOG: Update for comment in (now empty) generated source files.
// LOG:
// LOG: Revision 5.2  2001/08/21 21:01:26  hdivoux
// LOG: Added ctype.h as include.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:24  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:25  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.5  2001/03/26 16:47:24  mmiers
// LOG: For-scope problem with gcc.
// LOG:
// LOG: Revision 3.4  2001/03/14 22:06:44  mmiers
// LOG: Finalizing the engine.  Just need to do the thread pools.
// LOG:
// LOG: Revision 3.3  2001/02/05 22:12:43  mmiers
// LOG: Allow empty subsystem name.
// LOG:
// LOG: Revision 3.2  2000/09/07 19:45:40  hdivoux
// LOG: Update for namespaces other than its.
// LOG:
// LOG: Revision 3.1  2000/08/16 00:08:38  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.1  2000/05/11 02:06:17  mmiers
// LOG:
// LOG:
// LOG: tools: warning removal.  Hubert needs to take over for the comps.
// LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
// LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
// LOG: perspective, but IMAL class needs implementation.
// LOG: config.vars: correct platform flags for Linux.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:30:29  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.3  1999/06/28 19:13:59  skarmakar
// LOG:
// LOG:
// LOG: Update with awareness of throw specifier, behavior control defines
// LOG: in its++.h.
// LOG:
// LOG: Revision 1.2  1998/05/28 14:20:08  hdivoux
// LOG: Corrected minor code generation issue.
// LOG:
// LOG: Revision 1.1  1998/05/19 22:39:55  hdivoux
// LOG: Creation.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <string>

#include <exc_generate.h>
#include <exc_assert.h>


#define HDR_NEW_LINE    fprintf(fDescHdr, "\n");
#define HDR_INDENT_0    fprintf(fDescHdr, GetIndent(0));
#define HDR_INDENT_1    fprintf(fDescHdr, GetIndent(1));
#define HDR_INDENT_2    fprintf(fDescHdr, GetIndent(2));
#define HDR_INDENT_3    fprintf(fDescHdr, GetIndent(3));
#define HDR_INDENT_4    fprintf(fDescHdr, GetIndent(4));

#define SRC_NEW_LINE    fprintf(fDescSrc, "\n");
#define SRC_INDENT_0    fprintf(fDescSrc, GetIndent(0));
#define SRC_INDENT_1    fprintf(fDescSrc, GetIndent(1));
#define SRC_INDENT_2    fprintf(fDescSrc, GetIndent(2));
#define SRC_INDENT_3    fprintf(fDescSrc, GetIndent(3));
#define SRC_INDENT_4    fprintf(fDescSrc, GetIndent(4));


static FILE* fDescSrc = NULL;
static FILE* fDescHdr = NULL;

static const unsigned long bufferSize = 65536;

static void OpenSourceFile(string name)
{
    name.append(".cpp");

    fDescSrc = fopen(name.c_str(), "w");

    if (fDescSrc == NULL)
    {
        fprintf(stderr,
                "General: ERROR - Source file \"%s\""
                "cannot be opened for writing.\n",
                name.c_str());

        exit(EXIT_FAILURE);
    }
}

static void CloseSourceFile()
{
    fclose(fDescSrc);
}

static void OpenHeaderFile(string name)
{
    name.append(".h");

    fDescHdr = fopen(name.c_str(), "w");

    if (fDescHdr == NULL)
    {
        fprintf(stderr,
                "General: ERROR - Header file \"%s\""
                "cannot be opened for writing.\n",
                name.c_str());

        exit(EXIT_FAILURE);
    }
}

static void CloseHeaderFile()
{
    fclose(fDescHdr);
}


static void GenerateStandardHeader(FILE* fdesc)
{
    fprintf(fdesc, "//\n");
    fprintf(fdesc, "// Generated by IntelliExc Exception compiler (Exc -> C++).\n");
    fprintf(fdesc, "//\n");
    fprintf(fdesc, "// Do not edit!\n");
    fprintf(fdesc, "//\n");
    fprintf(fdesc, "//\n");
    fprintf(fdesc, "//\n");
    fprintf(fdesc, "// (C) 1998 - 2001 IntelliNet Technologies Inc. All Rights Reserved.\n");
    fprintf(fdesc, "//\n");
    fprintf(fdesc, "//\n");
    fprintf(fdesc, "\n");
    fprintf(fdesc, "\n");
}

static char* GetIndent(int level)
{
    int i = 0;
    static char indent[BUFSIZ];
    
    strcpy(indent, "");

    for (i = 0; i < level; i++)
    {
        strcat(indent, "    ");
    }

    return indent;
}

static string AddIndentLevel(string str, int level)
{
    string result;

    result += GetIndent(level);

    for (unsigned i = 0; i < str.size(); i++)
    {
        char curr = str[i];

        if (curr == '\n')
        {
            result += curr;
            result += GetIndent(level);
        }
        else
        {
            result += curr;
        }
    }

    return result;
}


// 
// String escape sequences are not processed by the lexical analyzer.
// Take only into account \\, \t and \n.
// 

static string ProcessEscapeSequences(string str)
{
    string result;

    char curr  = '\0';
    char prev  = '\0'; 

    for (unsigned i = 0; i < str.size(); i++)
    {
        if (prev == '\\' && curr == '\\')
        {
            prev = '\0';
        }
        else
        {
            prev = curr;
        }

        curr = str[i];

        if (prev == '\\')
        {
            switch (curr)
            {
                case '\\':
                    result += '\\';
                    break;
                case 't':
                    result += '\t';
                    break;
                case 'n':
                    result += '\n';
                    break;
                default:
                    result += prev;
                    result += curr;
                    break;
            }
        }
        else
        {
            if (curr != '\\')
            {
                result += curr;
            }
        }
    }

    return result;
}


//
//  Convert first character to upper case.
//

static string FirstCharacterToUpper(string str)
{
    string result;

    for (unsigned i = 0; i < str.size(); i++)
    {
        if (i == 0)
        {
            result += toupper(str[0]);
        }
        else
        {
            result += str[i];
        }
    }

    return result;
}


static string ToUpper(string str)
{
    string result;

    for (unsigned i = 0; i < str.size(); i++)
    {
        result += toupper(str[i]);
    }

    return result;
}


static void GenerateHeaderConditionalBefore(string name)
{
    fprintf(fDescHdr, "#if !defined(_%s_H_)\n",
            ToUpper(name).c_str());
    fprintf(fDescHdr, "#define _%s_H_\n", 
            ToUpper(name).c_str());
}


static void GenerateHeaderConditionalAfter(string name)
{
    fprintf(fDescHdr, "\n");
    fprintf(fDescHdr, "#endif // !defined(_%s_H_)\n", 
            ToUpper(name).c_str());
    fprintf(fDescHdr, "\n");
}


static void GenerateHeaderMandatoryIncludes(Subsystem* subsystem)
{
    fprintf(fDescHdr, "\n");
    fprintf(fDescHdr, "#include <its_exception.h>\n");
    fprintf(fDescHdr, "\n");
}


static void GenerateSourceMandatoryIncludes(Subsystem* subsystem)
{
    fprintf(fDescSrc, "\n");
    fprintf(fDescSrc, "#include <%s.h>\n", subsystem->fileName.c_str());
    fprintf(fDescSrc, "\n");

    fprintf(fDescSrc, "\n");
    fprintf(fDescSrc, "//\n");
    fprintf(fDescSrc, "// Nothing (everything in associated header).\n");
    fprintf(fDescSrc, "//\n");
    fprintf(fDescSrc, "\n");
}


static void GenerateHeaderAndSourceCode(Subsystem* subsystem)
{
    string prefix = subsystem->prefix;

    ExceptionList& exceptionList = subsystem->exceptionList;

    for (ExceptionList::iterator iterExc = exceptionList.begin();
         iterExc != exceptionList.end();
         iterExc++)
    {
        Exception& exception = **iterExc;

        // Class name.
        string className = prefix;
        className += exception.name;

        // Reason.
        string reason;

        if (exception.reason.size() != 0)
        {
            reason = exception.reason;
        }
        else
        {
            reason = "No reason specified";
        }

        // List of formal parameters.
        string formalParameters;

        // List of actual parameters.
        string actualParameters;

        AttributeList& attributeList = exception.attributeList;

        bool firstAttr = true;

        for (AttributeList::iterator iterAttr = attributeList.begin();
             iterAttr != attributeList.end();
             iterAttr++)
        {
            Attribute& attribute = **iterAttr;

            if (firstAttr == true)
            {
                firstAttr = false;
            }
            else
            {
                formalParameters += ", ";
                actualParameters += ", ";
            }

            formalParameters += attribute.parameterType;
            formalParameters += " ";
            formalParameters += attribute.name;
            formalParameters += "Param";

            actualParameters += attribute.name;
            actualParameters += "Param";
        }

        // Comma after parameters.

        string commaAfterParameters;

        if (attributeList.size() != 0)
        {
            commaAfterParameters = ",";
        }
        else
        {
            commaAfterParameters = "";
        }

        if (exception.codeSourceBefore.size() != 0)
        {
            SRC_NEW_LINE;

            string codeSourceBefore = 
                ProcessEscapeSequences(exception.codeSourceBefore);
            fprintf(fDescSrc, codeSourceBefore.c_str());
        }

        SRC_NEW_LINE;

        if (exception.codeHeaderBefore.size() != 0)
        {
            HDR_NEW_LINE;

            string codeHeaderBefore = 
                ProcessEscapeSequences(exception.codeHeaderBefore);
            fprintf(fDescHdr, codeHeaderBefore.c_str());
        }

        HDR_NEW_LINE;

        HDR_NEW_LINE;
        HDR_INDENT_0;
        fprintf(fDescHdr,
                "class %s : public its::GenericException {\n",
                className.c_str());

        HDR_NEW_LINE;
        HDR_INDENT_0;
        fprintf(fDescHdr, "public:\n");

        HDR_NEW_LINE;
        HDR_INDENT_1;
        fprintf(fDescHdr,
                "%s(%s) : its::GenericException(\"%s\")\n",
                className.c_str(),
                formalParameters.c_str(),
                reason.c_str());

        HDR_INDENT_1;
        fprintf(fDescHdr, "{ Initialize(%s); }\n", actualParameters.c_str());

        HDR_NEW_LINE;
        HDR_INDENT_1;
        fprintf(fDescHdr,
                "%s(%s%s const std::string& fileParam, unsigned long lineParam) :"
                " its::GenericException(\"%s\", fileParam, lineParam)\n",
                className.c_str(),
                formalParameters.c_str(),
                commaAfterParameters.c_str(),
                reason.c_str());

        HDR_INDENT_1;
        fprintf(fDescHdr, "{ Initialize(%s); }\n", actualParameters.c_str());

        HDR_NEW_LINE;
        HDR_INDENT_1;
        fprintf(fDescHdr, "virtual ~%s() ITS_THROW_SPEC_NULL\n",
                className.c_str());
        HDR_INDENT_1;
        fprintf(fDescHdr, "{};\n");

        for (AttributeList::iterator iterAttrBis = attributeList.begin();
             iterAttrBis != attributeList.end();
             iterAttrBis++)
        {
            Attribute& attribute = **iterAttrBis;

            HDR_NEW_LINE;
            HDR_INDENT_1;
            fprintf(fDescHdr, "%s Get%s()\n",
                    attribute.parameterType.c_str(),
                    FirstCharacterToUpper(attribute.name).c_str());

            HDR_INDENT_1;
            fprintf(fDescHdr, "{ return %s; }\n", attribute.name.c_str());
        }

        HDR_NEW_LINE;
        HDR_INDENT_0;
        fprintf(fDescHdr, "protected:\n");

        HDR_NEW_LINE;
        HDR_INDENT_1;
        fprintf(fDescHdr, "void Initialize(%s)\n", formalParameters.c_str());


        HDR_INDENT_1;
        fprintf(fDescHdr, "{\n");


        HDR_INDENT_2;
        fprintf(fDescHdr, "SetSubsystemNumber(%d);\n", subsystem->number);
        HDR_INDENT_2;
        fprintf(fDescHdr, "SetNumber(%d);\n", exception.number);

        AttributeList::iterator iterAttrTer;
        for (iterAttrTer = attributeList.begin();
             iterAttrTer != attributeList.end();
             iterAttrTer++)
        {
            Attribute& attribute = **iterAttrTer;

            HDR_INDENT_2;
            fprintf(fDescHdr, "%s = %sParam;\n",
                    attribute.name.c_str(),
                    attribute.name.c_str());
        }

        HDR_NEW_LINE;

        if (exception.codeBefore.size() != 0)
        {
            HDR_NEW_LINE;

            HDR_INDENT_2;
            string codeBefore = ProcessEscapeSequences(exception.codeBefore);
            fprintf(fDescHdr, codeBefore.c_str());

            HDR_NEW_LINE;
        }

        if (exception.codeBody.size() == 0)
        {
            DescriptionList& descriptionList = exception.descriptionList;

            for (DescriptionList::iterator iterDesc = descriptionList.begin();
                 iterDesc != descriptionList.end();
                 iterDesc++)
            {
                Description& description = **iterDesc;

                HDR_INDENT_2;
                fprintf(fDescHdr,
                        "InsertField(\"%s\", ",
                        description.value.c_str());

                bool firstArg = true;

                ArgumentList& argumentList = description.argumentList;

                for (ArgumentList::iterator iterArg = argumentList.begin();
                     iterArg != argumentList.end();
                     iterArg++)
                {
                    Argument& argument = **iterArg;

                    if (firstArg == true)
                    {
                        firstArg = false;
                    }
                    else
                    {
                        fprintf(fDescHdr, ", ");
                    }

                    fprintf(fDescHdr, "%s%s%s",
                            argument.codeBefore.c_str(),
                            argument.name.c_str(),
                            argument.codeAfter.c_str());

                }


                fprintf(fDescHdr, ");\n");

                HDR_NEW_LINE;

            }

        }
        else
        {
            string code = ProcessEscapeSequences(exception.codeBody);

            fprintf(fDescHdr, "%s\n",
            AddIndentLevel(code, 1).c_str());
        }

        if (exception.codeAfter.size() != 0)
        {
            HDR_NEW_LINE;

            string codeAfter = ProcessEscapeSequences(exception.codeAfter);
            fprintf(fDescHdr, codeAfter.c_str());

            HDR_NEW_LINE;
        }

        HDR_INDENT_1;
        fprintf(fDescHdr, "}\n");

        HDR_NEW_LINE;

        for (iterAttrTer = attributeList.begin();
             iterAttrTer != attributeList.end();
             iterAttrTer++)
        {
            Attribute& attribute = **iterAttrTer;

            HDR_NEW_LINE;
            HDR_INDENT_1;
            fprintf(fDescHdr, "%s %s;\n",
                    attribute.attributeType.c_str(),
                    attribute.name.c_str());

        }

        HDR_NEW_LINE;
        HDR_INDENT_0;
        fprintf(fDescHdr, "};\n");

        HDR_NEW_LINE;

        SRC_NEW_LINE;
        if (exception.codeSourceAfter.size() != 0)
        {
            string codeSourceAfter = 
                ProcessEscapeSequences(exception.codeSourceAfter);
            fprintf(fDescSrc, codeSourceAfter.c_str());

            SRC_NEW_LINE;
        }

        if (exception.codeHeaderAfter.size() != 0)
        {
            string codeHeaderAfter = 
                ProcessEscapeSequences(exception.codeHeaderAfter);
            fprintf(fDescHdr, codeHeaderAfter.c_str());

            HDR_NEW_LINE;
        }

    }

}



void GenerateSubsystemCode(Subsystem* subsystem)
{
    REQUIRE(subsystem != NULL);

    OpenSourceFile(subsystem->fileName);
    OpenHeaderFile(subsystem->fileName);

    GenerateStandardHeader(fDescHdr);
    GenerateStandardHeader(fDescSrc);

    GenerateHeaderConditionalBefore(subsystem->fileName);

    GenerateHeaderMandatoryIncludes(subsystem);

    string headerBefore = ProcessEscapeSequences(subsystem->codeHeaderBefore);
    fprintf(fDescHdr, headerBefore.c_str());

    GenerateSourceMandatoryIncludes(subsystem);

    string sourceBefore = ProcessEscapeSequences(subsystem->codeSourceBefore);
    fprintf(fDescSrc, sourceBefore.c_str());

    GenerateHeaderAndSourceCode(subsystem);
   
    string headerAfter = ProcessEscapeSequences(subsystem->codeHeaderAfter);
    fprintf(fDescHdr, headerAfter.c_str());

    GenerateHeaderConditionalAfter(subsystem->fileName);

    string sourceAfter = ProcessEscapeSequences(subsystem->codeSourceAfter);
    fprintf(fDescSrc, sourceAfter.c_str());

    CloseSourceFile();
    CloseHeaderFile();
}

    

