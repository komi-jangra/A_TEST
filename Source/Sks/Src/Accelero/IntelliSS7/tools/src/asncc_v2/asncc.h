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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:40  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:19  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:39  cvsadmin
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
// LOG: Revision 6.1  2002/02/28 16:14:34  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
//  Abstract syntax type interfaces.
//

#if !defined(_ASNCC_H_)
#define _ASNCC_H_

#ident "$Id: asncc.h,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"

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
#if defined(HPUX)
#include <iostream/iostream.h>
#include <iostream/strstream.h>
#include <iostream/fstream.h>
#else
#include <iostream>
#include <strstream>
#include <fstream>
#endif

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

extern unsigned long        lineNumberG;
extern std::string          asn1SrcFileNameG;
extern bool                 bModuleDirectoryG;
extern bool                 bForceExplicitChoiceG;
extern bool                 bForceExplicitAnyG;
extern bool                 bPrintG;
extern bool                 bPrintFlattenedG;
extern bool                 bPrintTagsG;
extern bool                 bCppFileNamesNoPrefixG;
extern bool                 bCppFileNamesMixedCaseG;
extern std::string          cppModuleNameG;
extern std::string          cppNamespaceG;
extern std::string          cModuleNameG;
extern std::string          javaPackageRootG;
extern std::string          xmlModuleNameG;  


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
