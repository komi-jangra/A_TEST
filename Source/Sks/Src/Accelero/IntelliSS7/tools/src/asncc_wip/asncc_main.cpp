////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
//  ID: $Id: asncc_main.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////



#include <asncc.h>
#include <asncc_ast.h>
#include <asncc_parser.h>
#include <asncc_util.h>
#include <asncc_command_interpreter.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

////////////////////////////////////////////////////////////////////////////////

//
// IntelliAsnCC compiler version number.
//

string versionG = "2.2";


//
// Global variables declarations.
//

extern FILE* yyin;
extern char* yytext;
extern int yydebug;
extern int lexEchoG; 
extern Module* moduleG;



//
// Global variables definitions.
//

unsigned long       lineNumberG                     = 1;
string              asn1SrcFileNameG                = "";
bool                bModuleDirectoryG               = false;
bool                bForceExplicitChoiceG           = false;
bool                bForceExplicitAnyG              = false;
bool                bPrintG                         = false;
bool                bPrintFlattenedG                = false;
bool                bPrintTagsG                     = false;
bool                bCppFileNamesNoPrefixG          = false;
bool                bCppFileNamesMixedCaseG         = false;
bool                bCppMergeG                      = false;
bool                bCppMergeWithExtensionsG        = false;
bool                bCppMergeGenerateAllHeadersG    = false;
vector<string>      cppModuleNamesG;
vector<string>      cppNamespacesG;
string              cppMergeModuleNameG             = "Common";
string              cppMergeNamespaceG              = "common";
string              cModuleNameG                    = "";
string              javaPackageRootG                = "com.intellinet.sdk.protocol";
string              xmlModuleNameG                  = "";
string              commandFileNameG                = "";

CommandInterpreter* commandInterpreterG             = NULL;


//
// External function declarations.
//

extern int yyparse();



////////////////////////////////////////////////////////////////////////////////
//
//  yyerror() implementation (required for flex).
//

void 
yyerror(const char* str)
{
    cerr << asn1SrcFileNameG;
    cerr << "(";
    cerr << lineNumberG;
    cerr << ") : ERROR - ";
    cerr << str;
    cerr << " - at symbol \"";
    cerr << yytext;
    cerr << "\".";
    cerr << endl;
}

////////////////////////////////////////////////////////////////////////////////



void Usage(const string& prgName)
{
             // 80 characters wide <-->                                                    //
             ////////////////////////////////////////////////////////////////////////////////
             //                                                                            //

    cerr << "\nUsage: asncc_v2.exe ";
    cerr << "[Options] ASN.1 files...\n";  
    cerr << "\n";

    cerr << "Options:\n";
    cerr << "\n";

    cerr << "   o [-c | -cpp | -java]\n\n";
    cerr << "           Generate C, C++ or Java code.\n\n\n";

    cerr << "   o [-u <ASN.1 useful file>]\n\n";
    cerr << "           Specify an ASN.1 file containing useful types.\n\n\n";    
    
    cerr << "   o [-f]\n\n";
    cerr << "           Ignore semantic error(s) and force code generation.\n\n\n";

    cerr << "   o [-d]\n\n";
    cerr << "           Create one directory per module for code generation.\n\n\n";

    cerr << "   o [-h]\n\n";                 
    cerr << "           Display this help and exit.\n\n\n";

    cerr << "   o [-cmd <Command file>]\n\n";
    cerr << "           Specify a Command file (hints for parser...).\n\n\n";

    cerr << "   o [-debugL]\n\n";
    cerr << "           Debug lexer mode (print lexer information).\n\n\n";

    cerr << "   o [-debugP]\n\n";
    cerr << "           Debug parser mode (print parser information).\n\n\n";

    cerr << "   o [-print]\n\n";
    cerr << "           Print reconstructed ASN.1 module(s) to standard output.\n\n\n";

    cerr << "   o [-printFlat]\n\n";            
    cerr << "           Print option. Print flattened ASN.1 module(s).\n\n\n";

    cerr << "   o [-printTags]\n\n";            
    cerr << "           Print option. Print tag(s) information.\n\n\n";

    cerr << "   o [-explicitChoice]\n\n";
    cerr << "           Force all ASN.1 CHOICE types to be explicit.\n\n\n";

    cerr << "   o [-explicitAny]\n\n";
    cerr << "           Force all ASN.1 ANY types to be explicit.\n\n\n";

    cerr << "   o [-cppModuleName <string>]\n\n";
    cerr << "           Specify alternate module name(s) for C++ code generation.\n\n\n";

    cerr << "   o [-cppNamespace <string>]\n\n";
    cerr << "           Specify alternate namespace(s) for C++ code generation.\n\n\n";

    cerr << "   o [-cppFileNamesNoPrefix]\n\n";
    cerr << "           Specify no prefix (i.e. module name) for C++ code file names.\n";
    cerr << "           Backward compatibility option. Not compatible with merge options.\n\n\n";

    cerr << "   o [-cppFileNamesMixedCase]\n\n";
    cerr << "           Specify mixed case for C++ code file names. Backward compatibility\n";
    cerr << "           option. Not compatible with merge options.\n\n\n";

    cerr << "   o [-cppMerge]\n\n";
    cerr << "           Merge identical ASN.1 types (from different modules) in a common\n";
    cerr << "           (created) module.\n\n\n";

    cerr << "   o [-cppMergeWithExtensions]\n\n";
    cerr << "           Take into account extension markers (...) for merge.\n\n\n";

    cerr << "   o [-cppMergeModuleName <string>]\n\n";
    cerr << "           Specify alternate module name for merged module.\n\n\n";

    cerr << "   o [-cppMergeNamespace <string>]\n\n";
    cerr << "           Specify alternate namespace for C++ merged code generation.\n\n\n";

    cerr << "   o [-cppMergeGenerateAllHeaders]\n\n";
    cerr << "           Generate all headers during C++ merged code generation. To allow\n";
    cerr << "           backward compatibility with non-merged code.\n\n\n";

    cerr << "   o [-cModuleName <string>]\n\n";
    cerr << "           Specify alternate module name(s) for C code generation.\n\n\n";

    cerr << "   o [-javaPackageRoot <string>]\n\n";
    cerr << "           Specify package(s) root for Java code generation.\n\n\n";

    cerr << "   o [-xmlCppDoc]\n\n";
    cerr << "           Generate C++ XML documentation.\n\n\n";

    cerr << "   o [-xmlCDoc]\n\n";
    cerr << "           Generate C XML documentation.\n\n\n";

    cerr << "   o [-xmlModuleName <string>]\n\n";  
    cerr << "           Specify alternate module name(s) for XML doc generation.\n\n\n";

    cerr << "\n";
    cerr << "\n";

    cerr << "o If no generate option is chosen (-c, -cpp or -java),\n";
    cerr << "  the validity of the specified asn files is checked.\n";
    cerr << "\n";
    cerr << "o Use \"-\" instead of the asn files to parse from stdin.\n";
    cerr << "\n";
    cerr << "\n";

    cerr << "IntelliAsnCC ASN.1 compiler (C, C++, Java) version ";
    cerr << versionG;
    cerr << ".\n";
    cerr << "All rights reserved. (C) 2001 IntelliNet Technologies.\n";
    cerr << "\n";
}
    


int
main(int argc, char* argv[])
{
    /////////////////////////////////
    // Begin main function try block.
    /////////////////////////////////

    try
    {

    /////////////////////////////////


    if (argc <= 1)
    {
        Usage(argv[0]);
        exit(1);
    }


    list<string> asn1SrcFileNameList;

    bool bAsnUsefulFilePresent  = false;

    string asnUsefulFileName;

    bool bGenerateC             = false;
    bool bGenerateCpp           = false;
    bool bGenerateJava          = false;

    bool bForceCodeGeneration   = false;

    bool bDebugLexer            = false;
    bool bDebugParser           = false;

    bool bGenerateCppXmlDoc     = false;
    bool bGenerateCXmlDoc       = false;


    // Parse command line argument(s).

    for (int currArg = 1; currArg < argc;)
    { 
        if (argv[currArg][0] == '-' && argv[currArg][1] != '\0')
        {
            if (strcmp(argv[currArg], "-c") == 0)
            {
                if (bGenerateCpp || bGenerateJava)
                {
                    cerr << "AsnCC Command Line : Error - incompatible option ";
                    cerr << "-cpp or -java used with -c option.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    bGenerateC = true;
                    currArg++;
                }
            }
            else if (strcmp(argv[currArg], "-cpp") == 0)
            {
                if (bGenerateC || bGenerateJava)
                {
                    cerr << "AsnCC Command Line : Error - incompatible option ";
                    cerr << "-c or -java used with -cpp option.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    bGenerateCpp = true;
                    currArg++;
                }
            }
            else if (strcmp(argv[currArg], "-java") == 0)
            {
                if (bGenerateC || bGenerateCpp)
                {
                    cerr << "AsnCC Command Line : Error - incompatible option ";
                    cerr << "-c or -cpp used with -java option.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    bGenerateJava = true;
                    currArg++;
                }
            }
            else if (strcmp(argv[currArg], "-u") == 0)
            {
                if (currArg == argc - 1)
                {
                    cerr << "AsnCC Command Line : Error - missing ASN.1 useful";
                    cerr << " file required by -u option.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    cerr << "AsnCC Command Line : Error - missing ASN.1 useful";
                    cerr << " file required by -u option.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    asnUsefulFileName = argv[currArg + 1];
                    bAsnUsefulFilePresent = true;
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-f") == 0)
            {
                bForceCodeGeneration = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-d") == 0)
            {
                bModuleDirectoryG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-h") == 0)
            {
                Usage(argv[0]);
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(argv[currArg], "-cmd") == 0)
            {
                if (currArg == argc - 1)
                {
                    cerr << "AsnCC Command Line : Error - missing command";
                    cerr << " file required by option -cmd.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    cerr << "AsnCC Command Line : Error - missing command";
                    cerr << " file required by option -cmd.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    commandFileNameG = argv[currArg + 1];
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-debugL") == 0)
            {
                bDebugLexer = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-debugP") == 0)
            {
                bDebugParser = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-print") == 0)
            {
                bPrintG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-printFlat") == 0)
            {
                bPrintFlattenedG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-printTags") == 0)
            {
                bPrintTagsG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-explicitChoice") == 0)
            {
                bForceExplicitChoiceG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-explicitAny") == 0)
            {
                bForceExplicitAnyG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-cppModuleName") == 0)
            {
                if (currArg == argc - 1)
                {
                    cerr << "AsnCC Command Line : Error - missing module name";
                    cerr << " required by option -cppModuleName.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    cerr << "AsnCC Command Line : Error - missing module name";
                    cerr << " required by option -cppModuleName.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cppModuleNamesG.push_back(argv[currArg + 1]);
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-cppNamespace") == 0)
            {
                if (currArg == argc - 1)
                {
                    cerr << "AsnCC Command Line : Error - missing namespace ";
                    cerr << "name required by option -cppNamespace.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '_')
                {
                    cerr << "AsnCC Command Line : Error - missing namespace ";
                    cerr << "name required by option -cppNamespace.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cppNamespacesG.push_back(argv[currArg + 1]);
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-cppMerge") == 0)
            {
                bCppMergeG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-cppMergeWithExtensions") == 0)
            {
                bCppMergeWithExtensionsG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-cppMergeModuleName") == 0)
            {
                if (currArg == argc - 1)
                {
                    cerr << "AsnCC Command Line : Error - missing module name ";
                    cerr << "required by option -cppMergeModuleName.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    cerr << "AsnCC Command Line : Error - missing module name ";
                    cerr << "required by option -cppMergeModuleName.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cppMergeModuleNameG = argv[currArg + 1];
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-cppMergeNamespace") == 0)
            {
                if (currArg == argc - 1)
                {
                    cerr << "AsnCC Command Line : Error - missing namespace ";
                    cerr << "name required by option -cppMergeNamespace.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    cerr << "AsnCC Command Line : Error - missing namespace ";
                    cerr << "name required by option -cppMergeNamespace.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cppMergeNamespaceG = argv[currArg + 1];
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-cppMergeGenerateAllHeaders") == 0)
            {
                bCppMergeGenerateAllHeadersG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-cModuleName") == 0)
            {
                if (currArg == argc - 1)
                {
                    cerr << "AsnCC Command Line : Error - missing module name ";
                    cerr << "required by option -cModuleName.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    cerr << "AsnCC Command Line : Error - missing module name ";
                    cerr << "required by option -cModuleName.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cModuleNameG = argv[currArg + 1];
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-cppFileNamesNoPrefix") == 0)
            {
                bCppFileNamesNoPrefixG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-cppFileNamesMixedCase") == 0)
            {
                bCppFileNamesMixedCaseG = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-javaPackageRoot") == 0)
            {
                if (currArg == argc - 1)
                {
                    cerr << "AsnCC Command Line : Error - missing package ";
                    cerr << "name required by option -javaPackageRoot.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    cerr << "AsnCC Command Line : Error - missing package ";
                    cerr << "name required by option -javaPackageRoot.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    javaPackageRootG = argv[currArg + 1];
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-xmlCppDoc") == 0)
            {
                bGenerateCppXmlDoc = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-xmlCDoc") == 0)
            {
                bGenerateCXmlDoc = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-xmlModuleName") == 0)
            {
                if (currArg == argc - 1)
                {
                    cerr << "AsnCC Command Line : Error - missing module name ";
                    cerr << "required by option -xmlModuleName.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    cerr << "AsnCC Command Line : Error - missing module name ";
                    cerr << "required by option -xmlModuleName.";
                    cerr << endl;

                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    xmlModuleNameG = argv[currArg + 1];
                    currArg += 2;
                }
            }
            else 
            {
                cerr << "AsnCC Command Line : Error - invalid command line ";
                cerr << "argument <" << argv[currArg] << ">.";
                cerr << endl;

                Usage(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            asn1SrcFileNameList.push_back(argv[currArg++]);
        }
    }

    // Checks for incompatible options.

    if (bCppMergeG && (bCppFileNamesNoPrefixG || bCppFileNamesMixedCaseG))
    {
        cerr << "AsnCC Command Line : ERROR - incompatible options.";
        cerr << endl;

        Usage(argv[0]);
        exit(EXIT_FAILURE);
    }


    // General message before compilation.

    cerr << "\n";
    cerr << "IntelliAsnCC ASN.1 compiler (C, C++, Java) version ";
    cerr << versionG;
    cerr << ".\n";
    cerr << "All rights reserved. (C) 2001 IntelliNet Technologies.\n";
    cerr << "\n";
    cerr << "Compiling...\n\n";



    if (asn1SrcFileNameList.size() == 0)
    {
        cerr << "AsnCC Command Line : ERROR - no ASN.1 files were specified.";
        cerr << endl;

        Usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    // Debug lexer option.

    if (bDebugLexer)
    {
        lexEchoG = true;
    }
    else
    {
        lexEchoG = false;
    }

    // Debug parser option.

    if (bDebugParser)
    {
        yydebug = 1;
    }
    else
    {
        yydebug = 0;
    }

    // -------------------------------------------------------------------------
    // STEP (-1)
    // -------------------------------------------------------------------------

    // Initialize command interpreter if required (i.e. if a command file has
    // been specified).

    CommandInterpreter commandInterpreter(commandFileNameG);

    if (commandFileNameG != "")
    {
         commandInterpreter.Initialize();

         commandInterpreterG = &commandInterpreter;
    }


    // -------------------------------------------------------------------------
    // STEP 0
    // -------------------------------------------------------------------------

    // Create AsnCC object.

    AsnCC asnCC;


    // -------------------------------------------------------------------------
    // STEP 1
    // -------------------------------------------------------------------------

    // Parse useful type module for linking purpose only (if given). The useful
    // type encode, decode, print routines are already in the runtime libraries
    // (C, C++ or Java).

    if (bAsnUsefulFilePresent)
    {
        Module* 
            usefulModule = 
                asnCC.ParseAsn1SrcFile(asnUsefulFileName);

        if (usefulModule == NULL)
        {
            exit(EXIT_FAILURE);
        }

        asnCC.AddUsefulModule(usefulModule);
    }
    else
    {
        cerr << "AsnCC Command Line : WARNING - no ASN.1 file containing ";
        cerr << "useful types was specified.";
        cerr << endl;

        cerr << "AsnCC Command Line : WARNING - assumption that useful ";
        cerr << "types are not required...";
        cerr << endl;
    }


    // -------------------------------------------------------------------------
    // STEP 2
    // -------------------------------------------------------------------------

    // Parse each ASN.1 source file.

    for (list<string>::iterator iter = asn1SrcFileNameList.begin();
         iter != asn1SrcFileNameList.end();
         ++iter)
    {
        Module* module = asnCC.ParseAsn1SrcFile(*iter);

        if (module->HasParseErrors())
        {
            // Parser has printed exact error message(s) previously.

            cerr << "AsnCC Status : ERROR - parsing error(s), cannot proceed.";
            cerr << endl;

            exit(EXIT_FAILURE);
        }

        asnCC.AddModule(module);
    }


    // Adjust C++ specified name(s) and namespace(s) if required.

    if (!cppModuleNamesG.empty())
    {
        if (cppModuleNamesG.size() == asnCC.GetModuleList().size())
        {
            size_t i = 0;
            ModuleList::const_iterator iter = asnCC.GetModuleList().begin();

            while (iter != asnCC.GetModuleList().end())
            {
                Module* module = *iter;

                module->SetSpecifiedName(cppModuleNamesG[i]);

                iter++;
                i++;
            }
        }
        else if (bAsnUsefulFilePresent && 
                 cppModuleNamesG.size() == asnCC.GetModuleList().size() - 1)
        {
            size_t i = 0;
            ModuleList::const_iterator iter = asnCC.GetModuleList().begin();

            while (iter != asnCC.GetModuleList().end())
            {
                Module* module = *iter;

                if (module != &asnCC.GetUsefulModule())
                {
                    module->SetSpecifiedName(cppModuleNamesG[i]);

                    i++;
                }
                else
                {
                    // Do nothing.
                }

                iter++;
            }
        }
        else
        {
            cerr << "AsnCC Command Line : WARNING - inconsistency between ";
            cerr << "number of ASN.1 source file(s) and [-cppModuleName ";
            cerr << "<string>] option(s) (should be equal).";
            cerr << endl;

            size_t i = 0;
            ModuleList::const_iterator iter = asnCC.GetModuleList().begin();

            while (iter != asnCC.GetModuleList().end() &&
                   i < cppModuleNamesG.size())
            {
                Module* module = *iter;

                if (module != &asnCC.GetUsefulModule())
                {
                    module->SetSpecifiedName(cppModuleNamesG[i]);

                    i++;
                }
                else
                {
                    // Do nothing.
                }

                iter++;
            }
        }
    }

    if (!cppNamespacesG.empty())
    {
        if (cppNamespacesG.size() == asnCC.GetModuleList().size())
        {
            size_t i = 0;
            ModuleList::const_iterator iter = asnCC.GetModuleList().begin();

            while (iter != asnCC.GetModuleList().end())
            {
                Module* module = *iter;

                module->SetSpecifiedNamespace(cppNamespacesG[i]);

                iter++;
                i++;
            }
        }
        else if (bAsnUsefulFilePresent && 
                 cppNamespacesG.size() == asnCC.GetModuleList().size() - 1)
        {
            size_t i = 0;
            ModuleList::const_iterator iter = asnCC.GetModuleList().begin();

            while (iter != asnCC.GetModuleList().end())
            {
                Module* module = *iter;

                if (module != &asnCC.GetUsefulModule())
                {
                    module->SetSpecifiedNamespace(cppNamespacesG[i]);
                    i++;
                }
                else
                {
                    // Do nothing.
                }

                iter++;
            }
        }
        else
        {
            cerr << "AsnCC Command Line : WARNING - inconsistency between ";
            cerr << "number of ASN.1 source file(s) and [-cppNamespace ";
            cerr << "<string>] option(s) (should be equal).";
            cerr << endl;

            size_t i = 0;
            ModuleList::const_iterator iter = asnCC.GetModuleList().begin();

            while (iter != asnCC.GetModuleList().end() &&
                   i < cppNamespacesG.size())
            {
                Module* module = *iter;

                if (module != &asnCC.GetUsefulModule())
                {
                    module->SetSpecifiedNamespace(cppNamespacesG[i]);
                    i++;
                }
                else
                {
                    // Do nothing.
                }

                iter++;
            }
        }
    }



    // -------------------------------------------------------------------------
    // STEP 3
    // -------------------------------------------------------------------------

    // Make all tables.


    asnCC.MakeModuleTable();

    asnCC.MakeTablesAllModules();


    // -------------------------------------------------------------------------
    // STEP 4
    // ------------------------------------------------------------------------- 

    // Link all modules.

    asnCC.LinkAllModules();

    if (asnCC.HasLinkErrorsAllModules())
    {
        // Linker has printed exact error message(s) previously.

        cerr << "AsnCC Status : ERROR - linking error(s), cannot proceed.";
        cerr << endl;

        exit(EXIT_FAILURE);
    }


    // -------------------------------------------------------------------------
    // STEP 5
    // ------------------------------------------------------------------------- 

    // Mark recursive types.

    asnCC.MarkRecursiveAllModules();

    if (asnCC.HasRecursiveErrorsAllModules())
    {
        // Recursive visitor has printed exact error message(s) previously.

        cerr << "AsnCC Status : WARNING - recursive definition error(s), try ";
        cerr << "to proceed without.";
        cerr << endl;
    }


    // -------------------------------------------------------------------------
    // STEP 6
    // ------------------------------------------------------------------------- 

    // Normalize COMPONENTS OF constructs.

    asnCC.NormalizeComponentsOfAllModules();

    if (asnCC.HasNormalizeComponentsOfErrorsAllModules())
    {
        // ComponentsOfVisior has printed exact error message(s) previously.

        cerr << "AsnCC Status : ERROR - COMPONENTS OF construct related ";
        cerr << "error(s), cannot proceed.";
        cerr << endl;

        exit(EXIT_FAILURE);
    }


    // -------------------------------------------------------------------------
    // STEP 7
    // ------------------------------------------------------------------------- 

    // Check for semantic error(s).

    asnCC.CheckSemanticAllModules();

    if (asnCC.HasSemanticErrorsAllModules())
    {
        // CheckSemanticVisitor has printed exact error message(s) previously.

        if (bForceCodeGeneration)
        {
            cerr << "AsnCC Status : WARNING - attempt to proceed further with ";
            cerr << "semantic error(s).";
            cerr << endl;
        }
        else
        {
            cerr << "AsnCC Status : ERROR - semantic error(s), cannot proceed.";
            cerr << endl;

            exit(EXIT_FAILURE);
        }
    }


    // -------------------------------------------------------------------------
    // STEP 8
    // ------------------------------------------------------------------------- 

    // Normalize all modules.

    asnCC.NormalizeAllModules();

    if (asnCC.HasSemanticErrorsAllModules())
    {
        // NormalizeVisitor has printed exact error message(s) previously.

        if (bForceCodeGeneration)
        {
            cerr << "AsnCC Status : WARNING - attempt to proceed further with ";
            cerr << "semantic error(s).";
            cerr << endl;
        }
        else
        {
            cerr << "AsnCC Status : ERROR - semantic error(s), cannot proceed.";
            cerr << endl;

            exit(EXIT_FAILURE);
        }
    }


    // -------------------------------------------------------------------------
    // STEP 9
    // ------------------------------------------------------------------------- 

    // Evaluate all modules.

    asnCC.EvaluateAllModules();

    if (asnCC.HasEvaluateErrorsAllModules())
    {
        // EvaluateVisitor has printed exact error message(s) previously.

        if (bForceCodeGeneration)
        {
            cerr << "AsnCC Status : WARNING - attempt to proceed further with ";
            cerr << "evaluate error(s).";
            cerr << endl;
        }
        else
        {
            cerr << "AsnCC Status : ERROR - evaluate error(s), cannot proceed.";
            cerr << endl;

            exit(EXIT_FAILURE);
        }
    }

    // Check again for linking error(s).

    if (asnCC.HasLinkErrorsAllModules())
    {
        // EvaluateVisitor has printed exact error message(s) previously.

        cerr << "AsnCC Status : ERROR - linking error(s), cannot proceed.";
        cerr << endl;

        exit(EXIT_FAILURE);
    }

    // Check again for semantic error(s).

    if (asnCC.HasSemanticErrorsAllModules())
    {
        // CheckSemanticVisitor has printed exact error message(s) previously.

        if (bForceCodeGeneration)
        {
            cerr << "AsnCC Status : WARNING - attempt to proceed further with ";
            cerr << "semantic error(s).";
            cerr << endl;
        }
        else
        {
            cerr << "AsnCC Status : ERROR - semantic error(s), cannot proceed.";
            cerr << endl;

            exit(EXIT_FAILURE);
        }
    }


    // -------------------------------------------------------------------------
    // STEP N - 1
    // -------------------------------------------------------------------------
    
    // Merge all modules.

    if (bCppMergeG)
    {
        asnCC.MergeAllModules();
    }


    // -------------------------------------------------------------------------
    // STEP N
    // -------------------------------------------------------------------------

    // Print all modules to standard output.

    if (bPrintG)
    {
        if (bPrintFlattenedG)
        {
            asnCC.PrintFlattenedAllModules(cout);
        }
        else
        {
            asnCC.PrintAllModules(cout);
        }
    }



    // -------------------------------------------------------------------------
    // STEP N + 1
    // -------------------------------------------------------------------------

    // Generate Cpp code.

    if (bGenerateCpp)
    {
        asnCC.GenerateCppAllModules();
    }



    // -------------------------------------------------------------------------
    // STEP N + 2
    // -------------------------------------------------------------------------

    // Generate Cpp XML Documentation.

    if (bGenerateCppXmlDoc)
    {
        asnCC.GenerateCppXmlDocAllModules();
    }



    // -------------------------------------------------------------------------
    // STEP N + 3
    // -------------------------------------------------------------------------

    // Generate C code.

    if (bGenerateC)
    {
        asnCC.GenerateCAllModules();
    }



    // -------------------------------------------------------------------------
    // STEP N + 4
    // -------------------------------------------------------------------------

    // Generate C XML Documentation.

    if (bGenerateCXmlDoc)
    {
        asnCC.GenerateCXmlDocAllModules();
    }



    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////


    // TODO: other steps to be added here.


    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////




    // General message after compilation.

    cerr << "\nDone.\n";

    return(EXIT_SUCCESS);


    /////////////////////////////////
    // End main function try block.
    /////////////////////////////////

    }

    /////////////////////////////////

    catch (GenericException& exc)
    {
        PrintInternErrSpecificLoc(exc.GetFile(), exc.GetLine());
        cerr << "FATAL ERROR - internal assertion failed : [";
        cerr << exc.GetReason().c_str();
        cerr << "].";
        cerr << endl;
    }
    catch (exception& exc)
    {
        PrintInternErrSpecificLoc(__FILE__, __LINE__);
        cerr << "FATAL ERROR - C++ standard exception : [";
        cerr << exc.what();
        cerr << "].";
        cerr << endl;
    }

#if defined(NDEBUG)

    catch (...)
    {
        PrintInternErrSpecificLoc(__FILE__, __LINE__);
        cerr << "CRITICAL ERROR - crash.";
        cerr << endl;
    }   

#endif  // defined(NDEBUG)

    exit(EXIT_FAILURE);
}



////////////////////////////////////////////////////////////////////////////////
//
//  AsnCC implementation.
//

AsnCC::AsnCC()
:   hasUsefulModule(false),
    usefulModule(NULL)
{
}


//
// Calls the yacc/lex (or flex/bison) parser given an ASN.1 source file name.
// Returns a Module object for the given ASN.1 module. If the ASN.1 source file
// name is "-" then stdin is used.
//

Module* 
AsnCC::ParseAsn1SrcFile(const string& asn1SrcFileName)
{
    // Set global variable for ASN1 source file name (used by lexer and parser).

    asn1SrcFileNameG = asn1SrcFileName;


    FILE* fDesc = NULL; 

    //
    // Open input file for lexical analyzer/parser. Use stdin if the file name
    // is "-".
    //

    if (asn1SrcFileName == "-")
    {
        fDesc = stdin;
    }
    else
    {
        fDesc = fopen(asn1SrcFileName.c_str(), "r");

        if (fDesc == NULL)
        {
            cerr << "AsnCC Command Line : ERROR - ASN.1 file \"";
            cerr << asn1SrcFileName;
            cerr << "\" cannot be opened for reading.";
            cerr << endl;

            exit(EXIT_FAILURE);

            return NULL;    // Not reached.
        }
    }


    //
    // Initialize yyin.
    //

    yyin = fDesc;


    //
    //  Initialize lineNumberG.
    //

    lineNumberG = 1;

    
    // Parse the current ASN.1 source file.

    int parseResult = yyparse();

    Module* result = moduleG;
    
    if (parseResult != 0)
    {
        if (result == NULL)
        {
            // Parser has printed exact error message previously.

            cerr << "AsnCC Status : ERROR - fatal parsing error(s), cannot ";
            cerr << "proceed.";
            cerr << endl;

            exit(EXIT_FAILURE);

            return NULL;    // Not reached.
        }
        else
        {
            result->AddError(Module::MODULE_PARSE_ERROR);

            return result;
        }
    }

    if (fDesc != stdin)
    {
        fclose(fDesc);
    }

    return result;
}


void
AsnCC::AddModule(Module* module)
{ 
    moduleList.push_back(module); 
}


ModuleList&
AsnCC::GetModuleList()
{ 
    return moduleList;
}


void
AsnCC::AddUsefulModule(Module* module)
{ 
    REQUIRE(!HasUsefulModule());

    moduleList.push_back(module);

    hasUsefulModule = true;
    usefulModule = module;
}


bool
AsnCC::HasUsefulModule() const
{ 
    return hasUsefulModule;
}


Module&
AsnCC::GetUsefulModule()
{ 
    REQUIRE(HasUsefulModule());
    return *usefulModule;
}


void 
AsnCC::MakeModuleTable()
{
    for (ModuleList::iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        // Check for duplicate module names.

        if (HasModule(module->GetName()))
        {
            Module* moduleOther = 
                RetrieveModule(module->GetName());

            PrintErrLoc(module->GetAsn1SrcFileName(), 1);
            cerr << "ERROR - module \"";
            cerr << module->GetName();
            cerr << "\" already defined in file \"";
            cerr << moduleOther->GetAsn1SrcFileName();
            cerr << "\".";
            cerr << endl;

            cerr << "AsnCC Status : ERROR - conflicting module names,";
            cerr << "cannot proceed.";
            cerr << endl;

            exit(EXIT_FAILURE);
        }
        else
        {
            moduleTable.
                insert(
                    ModuleTable::
                        value_type(
                            module->GetName(),
                            module));
        }
    }
}


bool 
AsnCC::HasModule(const std::string& name) const
{ 
    return 
        moduleTable.find(name) != 
            moduleTable.end(); 
}


Module* 
AsnCC::RetrieveModule(const std::string& name) const
{
    REQUIRE(HasModule(name));

    ModuleTable::const_iterator iter = 
        moduleTable.find(name);

    return (*iter).second;
}


void
AsnCC::MakeTablesAllModules()
{
    for (ModuleList::iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        module->MakeTypeDefTable();
        module->MakeValueDefTable();
        module->MakeExportedTypeDefTable();
        module->MakeExportedValueDefTable();
        module->MakeImportedSymbolTable();
    }
}


void
AsnCC::LinkAllModules()
{
    for (ModuleList::iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        module->Link(*this);
    }
}


bool 
AsnCC::HasLinkErrorsAllModules() const
{
    for (ModuleList::const_iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (module->HasLinkErrors())
        {
            return true;
        }
    }

    return false;
}


void 
AsnCC::NormalizeComponentsOfAllModules()
{
    for (ModuleList::iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        module->NormalizeComponentsOf(*this);
    }
}


bool 
AsnCC::HasNormalizeComponentsOfErrorsAllModules() const
{
    for (ModuleList::const_iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (module->HasComponentsOfErrors())
        {
            return true;
        }
    }

    return false;
}


void
AsnCC::MarkRecursiveAllModules()
{
    for (ModuleList::iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        module->MarkRecursive(*this);
    }
}


bool 
AsnCC::HasRecursiveErrorsAllModules() const
{
    for (ModuleList::const_iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (module->HasRecursiveErrors())
        {
            return true;
        }
    }

    return false;
}


void 
AsnCC::CheckSemanticAllModules()
{
    for (ModuleList::iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        module->CheckSemantic(*this);
    }
}


bool 
AsnCC::HasSemanticErrorsAllModules() const
{
    for (ModuleList::const_iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (module->HasSemanticErrors())
        {
            return true;
        }
    }

    return false;
}


void 
AsnCC::NormalizeAllModules()
{
    for (ModuleList::iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        module->Normalize(*this);
    }
}


void 
AsnCC::EvaluateAllModules()
{
    for (ModuleList::iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        module->Evaluate(*this);
    }
}


bool 
AsnCC::HasEvaluateErrorsAllModules() const
{
    for (ModuleList::const_iterator iter = moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (module->HasEvaluateErrors())
        {
            return true;
        }
    }

    return false;
}


void
AsnCC::MergeAllModules()
{
    for (ModuleList::const_iterator iter = 
            moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (module->GetName() != "ASN-USEFUL")
        {
            module->Merge(*this);
        }
    }
}


void
AsnCC::PrintAllModules(ostream& os) const
{
    for (ModuleList::const_iterator iter = 
            moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (iter == moduleList.begin())
        {
            os << "\n\n\n-----------------------------------------------";
            os << "---------------------------------\n\n";
        }

        module->Print(cout);

        os << "\n\n\n-----------------------------------------------";
        os << "---------------------------------\n\n";
    }
}


    
void
AsnCC::PrintFlattenedAllModules(ostream& os) const
{
    for (ModuleList::const_iterator iter = 
            moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (iter == moduleList.begin())
        {
            os << "\n\n\n-----------------------------------------------";
            os << "---------------------------------\n\n";
        }

        module->PrintFlattened(cout);

        os << "\n\n\n-----------------------------------------------";
        os << "---------------------------------\n\n";
    }
}


void
AsnCC::GenerateCppAllModules()
{
    for (ModuleList::const_iterator iter = 
            moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (module->GetName() != "ASN-USEFUL")
        {
            module->GenerateCpp(*this);
        }

        // Special case of ASN.1 useful module generation.

        if (moduleList.size() == 1 && module->GetName() == "ASN-USEFUL")
        {
            module->GenerateCpp(*this);
        }
    }
}


void
AsnCC::GenerateCppXmlDocAllModules()
{
    for (ModuleList::const_iterator iter = 
            moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (module->GetName() != "ASN-USEFUL")
        {
            module->GenerateCppXmlDoc(*this);
        }

        // Special case of ASN.1 useful module generation.

        if (moduleList.size() == 1 && module->GetName() == "ASN-USEFUL")
        {
            module->GenerateCppXmlDoc(*this);
        }
    }
}


void
AsnCC::GenerateCAllModules()
{
    for (ModuleList::const_iterator iter = 
            moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (module->GetName() != "ASN-USEFUL")
        {
            module->GenerateC(*this);
        }

        // Special case of ASN.1 useful module generation.

        if (moduleList.size() == 1 && module->GetName() == "ASN-USEFUL")
        {
            module->GenerateC(*this);
        }
    }
}


void
AsnCC::GenerateCXmlDocAllModules()
{
    for (ModuleList::const_iterator iter = 
            moduleList.begin();
         iter != moduleList.end();
         iter++)
    {
        Module* module = *iter;

        if (module->GetName() != "ASN-USEFUL")
        {
            module->GenerateCXmlDoc(*this);
        }

        // Special case of ASN.1 useful module generation.

        if (moduleList.size() == 1 && module->GetName() == "ASN-USEFUL")
        {
            module->GenerateCXmlDoc(*this);
        }
    }
}






