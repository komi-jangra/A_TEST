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
//  ID: $Id: asncc.h,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  Abstract syntax type interfaces.
//

#if !defined(_ASNCC_H_)
#define _ASNCC_H_

//
//  Disable warning 4786 for Visual C++ (WIN32 specific).
//

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif // defined(WIN32)

#include <its++.h>  // For portability.

#include <stdio.h>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <strstream>
#include <fstream>

typedef unsigned char byte;


// ASN.1 compiling error print location macro.

#define PrintErrLoc(fileName, lineNumber)                           \
    std::cerr << fileName.c_str() << "(" << lineNumber << ") : ";


// AsnCC internal compiling error print location macros.

#define PrintInternErrSpecificLoc(fileName, lineNumber)             \
    std::cerr << "AsnCC Compiler [" << StripPath(fileName).c_str(); \
    std::cerr << "(" << lineNumber << ")] : ";

#define PrintInternErrLoc() \
    PrintInternErrSpecificLoc(__FILE__, __LINE__)


// Global variable declarations.

extern std::string              versionG;
extern unsigned long            lineNumberG;
extern std::string              asn1SrcFileNameG;
extern bool                     bModuleDirectoryG;
extern bool                     bForceExplicitChoiceG;
extern bool                     bForceExplicitAnyG;
extern bool                     bPrintG;
extern bool                     bPrintFlattenedG;
extern bool                     bPrintTagsG;
extern bool                     bCppFileNamesNoPrefixG;
extern bool                     bCppFileNamesMixedCaseG;
extern bool                     bCppMergeG;
extern bool                     bCppMergeWithExtensionsG;
extern bool                     bCppMergeGenerateAllHeadersG;
extern std::vector<std::string> cppModuleNamesG;
extern std::vector<std::string> cppNamespacesG;
extern std::string              cppMergeModuleNameG;
extern std::string              cppMergeNamespaceG;
extern std::string              cModuleNameG;
extern std::string              javaPackageRootG;
extern std::string              xmlModuleNameG;  


class CommandInterpreter;

extern CommandInterpreter*  commandInterpreterG;




// Forward declarations.

class Module;


// Typedef for Module list.

typedef std::list<Module*> ModuleList;


////////////////////////////////////////////////////////////////////////////////
//
//  AsnCC interface.
//

class AsnCC
{
public:

    AsnCC();

    Module* ParseAsn1SrcFile(const std::string& asn1SrcFileName);

    void AddModule(Module* module);

    ModuleList& GetModuleList();

    void AddUsefulModule(Module* module);

    bool HasUsefulModule() const;

    Module& GetUsefulModule();

    void MakeModuleTable();

    bool HasModule(const std::string& name) const;

    Module* RetrieveModule(const std::string& name) const;

    void MakeTablesAllModules();

    void LinkAllModules();

    bool HasLinkErrorsAllModules() const;

    void NormalizeComponentsOfAllModules();

    bool HasNormalizeComponentsOfErrorsAllModules() const;

    void MarkRecursiveAllModules();

    bool HasRecursiveErrorsAllModules() const;

    void CheckSemanticAllModules();

    bool HasSemanticErrorsAllModules() const;

    void NormalizeAllModules();

    void EvaluateAllModules();

    bool HasEvaluateErrorsAllModules() const;

    void MergeAllModules();

    void PrintAllModules(std::ostream& os) const; 

    void PrintFlattenedAllModules(std::ostream& os) const;

    void GenerateCppAllModules();

    void GenerateCppXmlDocAllModules();

    void GenerateCAllModules();

    void GenerateCXmlDocAllModules();

protected:

    bool hasUsefulModule;
    Module* usefulModule;

    typedef std::map<std::string, Module*> ModuleTable;

    ModuleList    moduleList;
    ModuleTable   moduleTable;
};


#endif // !defined(_ASNCC_H_)
