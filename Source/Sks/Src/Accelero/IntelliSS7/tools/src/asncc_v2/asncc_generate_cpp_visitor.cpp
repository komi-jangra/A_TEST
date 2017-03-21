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
// LOG: Revision 1.1.1.1  2007/03/08 15:14:52  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.3  2005/06/07 11:03:58  adutta
// LOG: Changes for Nokia INAP/UMTS
// LOG:
// LOG: Revision 9.2  2005/06/06 13:33:39  mmanikandan
// LOG: NOKIA INAP is added.
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:14  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.8  2005/03/21 13:52:59  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1.4.2  2003/08/01 07:49:59  mmanikandan
// LOG: License warning generation for Asn Useful module is stopped.
// LOG:
// LOG: Revision 7.1.4.1  2003/07/07 12:32:36  mmanikandan
// LOG: License check for codec is added.
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.3  2002/06/18 15:39:17  hdivoux
// LOG: Correction: need to use base value and not value.
// LOG:
// LOG: Revision 6.2  2002/06/17 21:51:43  hdivoux
// LOG: Added processing for default ASN.1 values.
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.11  2002/02/21 15:41:47  hdivoux
// LOG: Update for extensibility clause generation if reference type.
// LOG:
// LOG: Revision 5.10  2002/01/10 00:11:49  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.9  2002/01/07 23:00:00  hdivoux
// LOG: Update for firt shot at XER encoding.
// LOG:
// LOG: Revision 5.8  2002/01/04 15:59:46  hdivoux
// LOG: More update related to XER support.
// LOG:
// LOG: Revision 5.7  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: asncc_generate_cpp_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"

#include <stdarg.h>

#include <asncc_generate_cpp_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


static bool _generateAssertionCode = false;
static bool _generateNamespaceDefineCode = false;

////////////////////////////////////////////////////////////////////////////////
//
//  GenerateCppVisitor implementation.
//

void 
GenerateCppVisitor::VisitModuleBegin(Module* moduleParam)
{
    REQUIRE(moduleParam != NULL);
}


void 
GenerateCppVisitor::VisitModuleEnd(Module* moduleParam)
{
    REQUIRE(moduleParam != NULL);
}


void 
GenerateCppVisitor::VisitImportedModule(ImportedModule* importedModule)
{
    REQUIRE(importedModule != NULL);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCppVisitor::VisitTypeDefBegin(TypeDef* typeDef)
{
    // Cleaning of contents (header and source).

    GetHdr().erase(GetHdr().begin(), GetHdr().end());
    GetSrc().erase(GetSrc().begin(), GetSrc().end());

    // Cleaning of contents (include lists).

    GetBasicIncludeList().clear();
    GetReferenceIncludeList().clear();


    SetCurrentTypeDef(typeDef);
    SetCurrentType(typeDef->GetType());
    SetCurrentTypeName(typeDef->GetDefinedName());
    SetLevel(0); // Module types are at level zero.
}


void 
GenerateCppVisitor::VisitTypeDefEnd(TypeDef* typeDef)
{
    GetHdr().insert(0, GetHdrHeaderString());
    GetHdr().append(GetHdrEndString());

    GetSrc().insert(0, GetSrcHeaderString());
    GetSrc().append(GetSrcEndString());

    string moduleName = module->GetName();

    if (cppModuleNameG != "")
    {
        moduleName = cppModuleNameG;
    }

    string directoryName    = "";
    string fileNameCore     = "";

    if (bModuleDirectoryG)
    {
        directoryName = AdaptNameToLowercase(moduleName);
    }

    if (!IsAsnUsefulTypeName(GetCurrentTypeName()))
    {
        if (!bCppFileNamesNoPrefixG)
        {
            fileNameCore.append(moduleName);
            fileNameCore.append("_");
        }
        else
        {
            // Do nothing => backward compatibility.
        }
    }
    else
    {
        // Do nothing.
    }

    fileNameCore.append(AdaptName(GetCurrentTypeName()));


    if (!IsAsnUsefulTypeName(GetCurrentTypeName()))
    {
        if (!bCppFileNamesMixedCaseG)
        {
            fileNameCore = AdaptNameToLowercase(fileNameCore);
        }
        else
        {
            // Do nothing => backward compatibility.
        }
    }
    else
    {
        // Do nothing.
    }

    WriteTextToFile(directoryName,
                    fileNameCore,
                    "h",
                    GetHdr());

    WriteTextToFile(directoryName,
                    fileNameCore,
                    "cpp",
                    GetSrc());
}


void 
GenerateCppVisitor::VisitTypeBegin(Type* type)
{
    SetCurrentType(type);

    constraintInstructionList.clear();
}


void 
GenerateCppVisitor::VisitTypeEnd(Type* type)
{
    // Nothing to do.
}


void
GenerateCppVisitor::VisitTypeDefaultValue(Type* type, Value* value)
{   

}


void 
GenerateCppVisitor::VisitBitStringTypeBegin(BitStringType* bitStringType)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitBitStringTypeEnd(BitStringType* bitStringType)
{
    InsertOnceBasicIncludeList("AsnBitString");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnBitString");

    HdrPrint(1, 
            "%s() : %sAsnBitString(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(const std::vector<bool>& array) : "
            "%sAsnBitString(array, false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets) : %sAsnBitString(false)\n",            
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnBitString(rhs)\n",
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnBitString(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description, "
            "const std::vector<bool>& array) : "
            "%sAsnBitString(description, array)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescBitString");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetClauseSizeInstructions();

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    NamedNumberList* namedNumberList = bitStringType->GetNamedNumberList();

    for (NamedNumberList::iterator iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string definedName = AdaptName(namedNumber->GetName());

        long value = namedNumber->GetNumber();

        HdrPrint(1, 
                "void Set%s()\n", 
                definedName.c_str());
        HdrPrint(1, 
                "{ Set(%d); }\n", 
                value);
        HdrNewLine();

        HdrPrint(1, 
                "void Reset%s()\n", 
                definedName.c_str());
        HdrPrint(1, 
                "{ Reset(%d); }\n", 
                value);
        HdrNewLine();

        HdrPrint(1, 
                "bool Is%sSet() const\n", 
                definedName.c_str());
        HdrPrint(1, 
                "{ return IsSet(%d); }\n", 
                value);
        HdrNewLine();

        HdrPrint(1, 
                "bool Is%sDefined() const\n", 
                definedName.c_str());
        HdrPrint(1, 
                "{ return %d < GetSize(); }\n", 
                value);
        HdrNewLine();
    }

    GenerateTypeClassEndPart();
}


void 
GenerateCppVisitor::VisitBooleanType(BooleanType* booleanType)
{
    InsertOnceBasicIncludeList("AsnBoolean");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnBoolean");

    HdrPrint(1, 
            "%s(bool value) : "
            "%sAsnBoolean(value, false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1, 
            "%s(%sOctets& octets) : "
            "%sAsnBoolean(false, false)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1, 
            "%s(const %s& rhs) : %sAsnBoolean(rhs)\n", 
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* description) : "
            "%sAsnBoolean(description)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* description, bool value) "
            ": %sAsnBoolean(description, value)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                typeName, 
                                                "AsnDescBoolean");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    GenerateTypeClassEndPart();
}


void 
GenerateCppVisitor::VisitChoiceTypeBegin(ChoiceType* choiceType)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitChoiceTypeEnd(ChoiceType* choiceType)
{
    InsertOnceBasicIncludeList("AsnChoice");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnChoice");

    HdrNewLine();
    HdrPrint(0, 
            "////////// Begin Nested Class(es) //////////\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "////////// Begin Nested Class(es) //////////\n");
    SrcNewLine();

    TypeList* typeList = choiceType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        typedefListStack.push_front(GetTypedefList());
        GetTypedefList().clear();

        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            PushContext();

            SetCurrentTypeName(GetGeneratedElementTypeName(namedType));

            SetCurrentType(namedType);

            // Generate subordinate type.

            namedType->Accept(this);

            PopContext();
        }

        GetHdr() += GetTypedefListString();

        typedefList = typedefListStack.front();
        typedefListStack.pop_front();
    }

    HdrNewLine();
    HdrPrint(0, 
            "////////// End Nested Class(es) //////////\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "////////// End Nested Class(es) //////////\n");
    SrcNewLine();

    HdrPrint(1, 
            "%s() : %sAsnChoice(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1,             
            "%s(%sOctets& octets) : %sAsnChoice(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnChoice(rhs)\n",
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnChoice(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description, %sAsnObject* choice) :"
            " %sAsnChoice(description, choice)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescChoice");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    typeList = choiceType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            SrcPrint(2,
                    "staticDesc._choiceList.push_back(Get%sStaticDescription());\n",
                    adaptedName.c_str());
        }
    }

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    typeList = choiceType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            GenerateElementStaticDescription(namedType, adaptedName);
        }

        HdrNewLine();
    }

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    typeList = choiceType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            string adaptedGenTypeName = 
                AdaptName(GetGeneratedTypeName(namedType));

            if (IsAsnTypeName(adaptedGenTypeName))
            {
                InsertOnceBasicIncludeList(adaptedGenTypeName);
            }
            else
            {
                InsertOnceReferenceIncludeList(adaptedGenTypeName);
            }

            string adaptedGenBaseTypeName =
                AdaptName(GetGeneratedBaseTypeName(namedType));

            if (IsAsnTypeName(adaptedGenBaseTypeName))
            {
                InsertOnceBasicIncludeList(adaptedGenBaseTypeName);
            }

            string adaptedElementTypeName =
                AdaptName(GetGeneratedElementTypeName(namedType));

            HdrPrint(1,
                    "void SetChoice%s(%s* choice)\n",
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str());
            HdrPrint(1,
                    "{\n");
            HdrPrint(2,
                    "ITS_REQUIRE(choice != NULL);\n");
            HdrPrint(2,
                    "choice->AsnObject::SetDescription"
                    "(Get%sStaticDescription());\n",
                    adaptedName.c_str());
            HdrPrint(2,
                    "SetChoice(choice);\n");
            HdrPrint(1,
                    "}\n");
            HdrNewLine();

            HdrPrint(1,
                    "void SetChoice%s(const %s& choice)\n",
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str());        
            HdrPrint(1,
                    "{\n");
            HdrPrint(2,
                    "%sAsnObject& asnObject = const_cast<%s&>(choice);\n",
                    GetItsNamespaceScope().c_str(),
                    adaptedElementTypeName.c_str()); 
            HdrPrint(2,
                    "asnObject.SetDescription(Get%sStaticDescription());\n",
                    adaptedName.c_str());
            HdrPrint(2,
                    "SetChoice(choice);\n");
            HdrPrint(1,
                    "}\n");
            HdrNewLine();

            HdrPrint(1,
                    "bool Choice%s() const\n",
                    adaptedName.c_str());            
            HdrPrint(1,
                    "{\n");
            HdrPrint(2,
                    "return Contains(Get%sStaticDescription()->"
                    "TagIdentity());\n",
                    adaptedName.c_str());
            HdrPrint(1,
                    "}\n");
            HdrNewLine();

            if (namedType->GetType() == TYPE_DEFINED)
            {
                HdrPrint(1,
                        "const %s& GetChoice%s() const\n",
                        adaptedElementTypeName.c_str(),
                        adaptedName.c_str());
            }
            else // Nested type.
            {
                HdrPrint(1,
                        "const %s& GetChoice%s() const\n",
                        adaptedElementTypeName.c_str(),
                        adaptedName.c_str());
            }

            HdrPrint(1,
                    "{\n");
            HdrPrint(2,
                    "ITS_REQUIRE(Choice%s());\n",
                    adaptedName.c_str());
            HdrPrint(2,
                    "return static_cast<const %s&> (GetChoice());\n",
                    adaptedElementTypeName.c_str());
            HdrPrint(1,
                    "}\n");
            HdrNewLine();
        }
    }

    GenerateTypeClassEndPart();
}


void
GenerateCppVisitor::VisitChoiceTypeList(TypeList* typeList)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitEnumeratedTypeBegin(EnumeratedType* enumeratedType)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitEnumeratedTypeEnd(EnumeratedType* enumeratedType)
{
    InsertOnceBasicIncludeList("AsnEnumerated");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnEnumerated");

    HdrPrint(1, 
            "%s() : %sAsnEnumerated(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1, 
            "%s(long value) : "
            "%sAsnEnumerated(value, false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets) : %sAsnEnumerated(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnEnumerated(rhs)\n",
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnEnumerated(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description, long value) : "
            "%sAsnEnumerated(description, value)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescEnumerated");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetClauseExtensibleInstructions();

    NamedNumberList* namedNumberList = enumeratedType->GetNamedNumberList();

    NamedNumberList::iterator iter;

    for (iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        long value = namedNumber->GetNumber();

        SrcPrint(2,
                "staticDesc._valueSet.insert(%d);\n",
                value);
    }

    SrcPrint(2,
            "static AsnDescEnumerated::NamedNumber namedNumberList[] = {");

    for (iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        const string& name = namedNumber->GetName();
        long value = namedNumber->GetNumber();

        SrcPrint(0, "{\"%s\", %d}, ", name.c_str(), value);
    }

    SrcPrint(0,
            "{NULL, 0}};\n");

    SrcPrint(2,
            "staticDesc.SetNamedNumberList(namedNumberList);\n");

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    HdrPrint(1, 
            "virtual long Get(const std::string& valueName) const;\n");
    HdrNewLine();

    SrcPrint(0, 
            "long %sGet(const std::string& valueName) const\n", 
            GetScopeString().c_str());
    SrcPrint(0, 
            "{\n");

    namedNumberList = enumeratedType->GetNamedNumberList();

    bool first = true;

    for (iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string name = namedNumber->GetName();

        long value = namedNumber->GetNumber();

        if (first)
        {
            first = false;

            SrcPrint(1, 
                    "if (valueName == \"%s\")\n", 
                    name.c_str());
        }
        else
        {
            SrcPrint(1, 
                    "else if (valueName == \"%s\")\n", 
                    name.c_str());
        }

        SrcPrint(1, 
                "{\n");
        SrcPrint(2, 
                "return %d;\n", value);
        SrcPrint(1, 
                "}\n");
    }

    SrcPrint(1, 
            "else\n");
    SrcPrint(1, 
            "{\n");
    SrcPrint(2, 
            "bool invalid_value_name = false;\n");
    SrcPrint(2, 
            "ITS_ASSERT(invalid_value_name);\n");
    SrcNewLine();
    SrcPrint(2, 
            "return 0;\n");
    SrcPrint(1, 
            "}\n");

    SrcPrint(0, 
            "}\n");
    SrcNewLine();

    HdrPrint(1, 
            "virtual std::string Get(long value) const;\n");
    HdrNewLine();

    SrcPrint(0, 
            "std::string %sGet(long value) const\n", GetScopeString().c_str());
    SrcPrint(0, 
            "{\n");

    namedNumberList = enumeratedType->GetNamedNumberList();

    first = true;

    for (iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string name = namedNumber->GetName();

        long value = namedNumber->GetNumber();

        if (first)
        {
            first = false;

            SrcPrint(1, 
                    "if (value == %d)\n", 
                    value);
        }
        else
        {
            SrcPrint(1, 
                    "else if (value == %d)\n", 
                    value);
        }

        SrcPrint(1, 
                "{\n");
        SrcPrint(2, 
                "return \"%s\";\n", 
                name.c_str());
        SrcPrint(1, 
                "}\n");
    }

    SrcPrint(1, 
            "else\n");
    SrcPrint(1, 
            "{\n");
    SrcPrint(2, 
            "bool invalid_value = false;\n");
    SrcPrint(2, 
            "ITS_ASSERT(invalid_value);\n");
    SrcNewLine();
    SrcPrint(2, 
            "return \"\";\n");
    SrcPrint(1, 
            "}\n");

    SrcPrint(0, 
            "}\n");
    SrcNewLine();

    namedNumberList = enumeratedType->GetNamedNumberList();

    first = true;

    HdrPrint(1, 
            "enum {\n");

    for (iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string typeNamePrefix = AdaptNameToUppercase(GetCurrentTypeName());

        string definedName = AdaptNameToUppercase(namedNumber->GetName());

        long value = namedNumber->GetNumber();

        if (first)
        {
            first = false;
        }
        else
        {
            GetHdr().append(",\n");
        }

        HdrPrint(2, 
                "%s_%s = %d", 
                typeNamePrefix.c_str(),
                definedName.c_str(), 
                value);
    }

    GetHdr().append("\n");

    HdrPrint(1, 
            "};\n");
    HdrNewLine();

    namedNumberList = enumeratedType->GetNamedNumberList();

    for (iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string definedName = AdaptName(namedNumber->GetName());

        long value = namedNumber->GetNumber();

        HdrPrint(1, 
                "void Set%s()\n", definedName.c_str());
        HdrPrint(1, 
                "{ _value = %d; }\n", value);
        HdrNewLine();


        HdrPrint(1, 
                "bool Is%s() const\n", definedName.c_str());
        HdrPrint(1, 
                "{ return _value == %d; }\n", value);
        HdrNewLine();
    }

    GenerateTypeClassEndPart();
}


void 
GenerateCppVisitor::VisitIntegerTypeBegin(IntegerType* integerType)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitIntegerTypeEnd(IntegerType* integerType)
{
    InsertOnceBasicIncludeList("AsnInteger");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnInteger");

    HdrPrint(1, 
            "%s() : %sAsnInteger(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(long value) : "
            "%sAsnInteger(value, false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets) : "
            "%sAsnInteger(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnInteger(rhs)\n",
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnInteger(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description, long value) : "
            "%sAsnInteger(description, value)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescInteger");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    GenerateTypeClassEndPart();
}


void
GenerateCppVisitor::VisitObjectIdentifierType(
                                ObjectIdentifierType* objectIdentifierType)
{
    InsertOnceBasicIncludeList("AsnObjectIdentifier");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnObjectIdentifier");

    HdrPrint(1, 
            "%s() : %sAsnObjectIdentifier(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(const std::vector<long>& array) : "
            "%sAsnObjectIdentifier(array, false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets) : "
            "%sAsnObjectIdentifier(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnObjectIdentifier(rhs)\n",
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnObjectIdentifier(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description, "
            "const std::vector<long>& array) : "
            "%sAsnObjectIdentifier(description, array)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescObjectIdentifier");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    GenerateTypeClassEndPart();
}


void
GenerateCppVisitor::VisitNullType(NullType* nullType)
{
    InsertOnceBasicIncludeList("AsnNull");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnNull");

    HdrPrint(1, 
            "%s() : %sAsnNull(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1,
            "%s(%sOctets& octets) : %sAsnNull(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnNull(rhs)\n",
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnNull(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescNull");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    GenerateTypeClassEndPart();
}


void
GenerateCppVisitor::VisitRealType(RealType* realType)
{
    InsertOnceBasicIncludeList("AsnReal");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnReal");

    HdrPrint(1, 
            "%s() : %sAsnReal(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(double value) : "
            "%sAsnReal(value, false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets) : %sAsnReal(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnReal(rhs)\n",
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnReal(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description, double value) : "
            "%sAsnReal(description, value)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescReal");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    GenerateTypeClassEndPart();
}


void 
GenerateCppVisitor::VisitSequenceTypeBegin(SequenceType* sequenceType)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitSequenceTypeEnd(SequenceType* sequenceType)
{
    InsertOnceBasicIncludeList("AsnSequence");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnSequence");

    HdrNewLine();
    HdrPrint(0, "////////// Begin Nested Class(es) //////////\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, "////////// Begin Nested Class(es) //////////\n");
    SrcNewLine();

    TypeList* typeList = sequenceType->GetFlattenedTypeList();

    int sequenceSize = 0;

    if (!(typeList->empty()))
    {
        typedefListStack.push_front(GetTypedefList());
        GetTypedefList().clear();

        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            PushContext();

            SetCurrentTypeName(GetGeneratedElementTypeName(namedType));

            SetCurrentType(namedType);

            // Generate subordinate type.

            namedType->Accept(this);

            PopContext();
        }

        GetHdr() += GetTypedefListString();

        typedefList = typedefListStack.front();
        typedefListStack.pop_front();

        sequenceSize = typeList->size();
    }

    HdrNewLine();
    HdrPrint(0, 
            "////////// End Nested Class(es) //////////\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "////////// End Nested Class(es) //////////\n");
    SrcNewLine();

    HdrPrint(1, 
            "%s() : %sAsnSequence(%d, false)\n", 
            typeName.c_str(), 
            GetItsNamespaceScope().c_str(),
            sequenceSize);

    GenerateDefaultConstructorBody();

    HdrPrint(1, 
            "%s(%sOctets& octets) : "
            "%sAsnSequence(%d, false)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str(),
            sequenceSize);

    GenerateDecodeConstructorBody();

    HdrPrint(1, 
            "%s(const %s& rhs) : %sAsnSequence(rhs)\n", 
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* description) : "
            "%sAsnSequence(%d, description)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str(),
            sequenceSize);

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                typeName, 
                                                "AsnDescSequence");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetClauseExtensibleInstructions();

    typeList = sequenceType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        int index = 0;

        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            SrcPrint(2, 
                    "staticDesc._elementVect[%d] = Get%sStaticDescription();\n",
                    index, 
                    adaptedName.c_str());

            index++;
        }
    }

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    typeList = sequenceType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            GenerateElementStaticDescription(namedType, adaptedName);
        }

        HdrNewLine();
    }

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    typeList = sequenceType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        int index = 0;

        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            string adaptedGenTypeName = 
                AdaptName(GetGeneratedTypeName(namedType));

            if (IsAsnTypeName(adaptedGenTypeName))
            {
                InsertOnceBasicIncludeList(adaptedGenTypeName);
            }
            else
            {
                InsertOnceReferenceIncludeList(adaptedGenTypeName);
            }

            string adaptedGenBaseTypeName =
                AdaptName(GetGeneratedBaseTypeName(namedType));

            if (IsAsnTypeName(adaptedGenBaseTypeName))
            {
                InsertOnceBasicIncludeList(adaptedGenBaseTypeName);
            }

            string adaptedElementTypeName =
                AdaptName(GetGeneratedElementTypeName(namedType));

            HdrPrint(1, 
                    "void Set%s(%s* element)\n", 
                    adaptedName.c_str(), 
                    adaptedElementTypeName.c_str());        
            HdrPrint(1, 
                    "{\n");
            HdrPrint(2, 
                    "ITS_REQUIRE(element != NULL);\n");
            HdrPrint(2, 
                    "element->AsnObject::SetDescription"
                    "(Get%sStaticDescription());\n",
                    adaptedName.c_str());
            HdrPrint(2, 
                    "AddElement(%d, element);\n", 
                    index);
            HdrPrint(1, 
                    "}\n");
            HdrNewLine();

            HdrPrint(1, 
                    "void Set%s(const %s& element)\n", 
                    adaptedName.c_str(), 
                    adaptedElementTypeName.c_str());        
            HdrPrint(1, 
                    "{\n");
            HdrPrint(2, 
                    "%sAsnObject& asnObject = const_cast<%s&>(element);\n",
                    GetItsNamespaceScope().c_str(),
                    adaptedElementTypeName.c_str()); 
            HdrPrint(2, 
                    "asnObject.SetDescription(Get%sStaticDescription());\n", 
                    adaptedName.c_str());
            HdrPrint(2, 
                    "AddElement(%d, element);\n", 
                    index);
            HdrPrint(1, 
                    "}\n");
            HdrNewLine();

            if (namedType->IsOptional())
            {
                HdrPrint(1, 
                        "bool Option%s() const\n", 
                        adaptedName.c_str());            
                HdrPrint(1, 
                        "{\n");
                HdrPrint(2, 
                        "return Contains(%d);\n", index);
                HdrPrint(1, 
                        "}\n");
                HdrNewLine();
            }

            if (namedType->GetType() == TYPE_DEFINED)
            {
                HdrPrint(1, 
                        "const %s& Get%s() const\n", 
                        adaptedElementTypeName.c_str(), 
                        adaptedName.c_str());        
            }
            else // Nested type.
            {
                HdrPrint(1, 
                        "const %s& Get%s() const\n", 
                        adaptedElementTypeName.c_str(), 
                        adaptedName.c_str());        
            }

            HdrPrint(1, 
                    "{\n");

            if (namedType->IsOptional())
            {
            
                HdrPrint(2, 
                        "ITS_REQUIRE(Option%s());\n", 
                        adaptedName.c_str());
            }

            HdrPrint(2, 
                    "return static_cast<const %s&> (ElementAt(%d));\n",
                    adaptedElementTypeName.c_str(), 
                    index);
            HdrPrint(1, 
                    "}\n");
            HdrNewLine();

            index++;
        }
    }

    GenerateTypeClassEndPart();  
}


void
GenerateCppVisitor::VisitSequenceTypeList(TypeList* typeList)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitSequenceOfTypeBegin(SequenceOfType* sequenceOfType)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitSequenceOfTypeEnd(SequenceOfType* sequenceOfType)
{
    InsertOnceBasicIncludeList("AsnSequenceOf");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnSequenceOf");

    HdrNewLine();
    HdrPrint(0, 
            "////////// Begin Nested Class //////////\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "////////// Begin Nested Class //////////\n");
    SrcNewLine();

    Type* type = sequenceOfType->GetSequenceOfType();

    string eltTypeName = AdaptName(GetGeneratedTypeName(type));

    if (IsAsnTypeName(eltTypeName))
    {
        InsertOnceBasicIncludeList(eltTypeName);
    }
    else
    {
        InsertOnceReferenceIncludeList(eltTypeName);
    }

    string eltBaseTypeName = AdaptName(GetGeneratedBaseTypeName(type));

    if (IsAsnTypeName(eltBaseTypeName))
    {
        InsertOnceBasicIncludeList(eltBaseTypeName);
    }

    if (IsAsnTypeName(eltTypeName))
    {
        eltTypeName.erase(0, 3);   // Remove "Asn" prefix.

        for (size_t i = 0; i < eltTypeName.size(); i++)
        {
            eltTypeName[i] = toupper(eltTypeName[i]);
        }
    }

    typedefListStack.push_front(GetTypedefList());
    GetTypedefList().clear();

    PushContext();

    SetCurrentTypeName(eltTypeName);

    SetCurrentType(type);

    // Generate subordinate type.

    type->Accept(this);

    PopContext();

    GetHdr() += GetTypedefListString();

    typedefList = typedefListStack.front();
    typedefListStack.pop_front();

    HdrNewLine();
    HdrPrint(0, 
            "////////// End Nested Class //////////\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "////////// End Nested Class //////////\n");
    SrcNewLine();

    HdrPrint(1,
            "%s() : %sAsnSequenceOf(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();

    HdrPrint(1,
            "%s(%sOctets& octets) : %sAsnSequenceOf(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnSequenceOf(rhs)\n",
            typeName.c_str(),
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnSequenceOf(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescSequenceOf");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetClauseSizeInstructions();

    SrcPrint(2,
            "staticDesc._element = Get%sStaticDescription();\n",
            eltTypeName.c_str());

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GenerateElementStaticDescription(type, eltTypeName);

    HdrNewLine();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    HdrPrint(1,
            "void AddElement(%s* element)\n",
            eltTypeName.c_str());
    HdrPrint(1,
            "{\n");
    HdrPrint(2,
            "ITS_REQUIRE(element != NULL);\n");
    HdrPrint(2,
            "element->AsnObject::SetDescription"
            "(Get%sStaticDescription());\n",
            eltTypeName.c_str());
    HdrPrint(2,
            "AsnSequenceOf::AddElement(element);\n");
    HdrPrint(1,
            "}\n");
    HdrNewLine();

    HdrPrint(1,
            "void AddElement(const %s& element)\n",
            eltTypeName.c_str());
    HdrPrint(1,
            "{\n");
    HdrPrint(2, 
            "%sAsnObject& asnObject = const_cast<%s&>(element);\n",
            GetItsNamespaceScope().c_str(),
            eltTypeName.c_str()); 
    HdrPrint(2, 
            "asnObject.SetDescription(Get%sStaticDescription());\n",
            eltTypeName.c_str());
    HdrPrint(2,
            "AsnSequenceOf::AddElement(element);\n");
    HdrPrint(1,
            "}\n");
    HdrNewLine();

    HdrPrint(1,
            "const %s& ElementAt(int index) const\n",
            eltTypeName.c_str());
    HdrPrint(1,
            "{\n");
    HdrPrint(2,
            "return static_cast<const %s&> "
            "(AsnSequenceOf::ElementAt(index));\n",
            eltTypeName.c_str());
    HdrPrint(1,
            "}\n");
    HdrNewLine();

    GenerateTypeClassEndPart();  
}


void
GenerateCppVisitor::VisitSequenceOfTypeType(Type* type)
{
    // Nothing to do.
}


void
GenerateCppVisitor::VisitSequenceOfConstraint(Constraint* constraint)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitSetTypeBegin(SetType* setType)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitSetTypeEnd(SetType* setType)
{
    InsertOnceBasicIncludeList("AsnSet");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnSet");

    HdrNewLine();
    HdrPrint(0, 
            "////////// Begin Nested Class(es) //////////\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "////////// Begin Nested Class(es) //////////\n");
    SrcNewLine();

   TypeList* typeList = setType->GetFlattenedTypeList();

    int setSize = 0;

    if (!(typeList->empty()))
    {
        typedefListStack.push_front(GetTypedefList());
        GetTypedefList().clear();

        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            PushContext();

            SetCurrentTypeName(GetGeneratedElementTypeName(namedType));

            SetCurrentType(namedType);

            // Generate subordinate type.

            namedType->Accept(this);

            PopContext();
        }

        GetHdr() += GetTypedefListString();

        typedefList = typedefListStack.front();
        typedefListStack.pop_front();

        setSize = typeList->size();
    }

    HdrNewLine();
    HdrPrint(0, 
            "////////// End Nested Class(es) //////////\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "////////// End Nested Class(es) //////////\n");
    SrcNewLine();

    HdrPrint(1,
            "%s() : %sAsnSet(%d, false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            setSize);

    GenerateDefaultConstructorBody();

    HdrPrint(1,
            "%s(%sOctets& octets) : "
            "%sAsnSet(%d, false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str(),
            setSize);

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnSet(rhs)\n",
            typeName.c_str(),
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnSet(%d, description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str(),
            setSize);

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescSet");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetClauseExtensibleInstructions();

    typeList = setType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        int index = 0;

        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            SrcPrint(2, 
                    "staticDesc._elementVect[%d] = Get%sStaticDescription();\n",
                    index,
                    adaptedName.c_str());

            index++;
        }
    }

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    typeList = setType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            GenerateElementStaticDescription(namedType, adaptedName);
        }

        HdrNewLine();
    }

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    typeList = setType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        int index = 0;

        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            string adaptedGenTypeName = 
                AdaptName(GetGeneratedTypeName(namedType));

            if (IsAsnTypeName(adaptedGenTypeName))
            {
                InsertOnceBasicIncludeList(adaptedGenTypeName);
            }
            else
            {
                InsertOnceReferenceIncludeList(adaptedGenTypeName);
            }

            string adaptedGenBaseTypeName =
                AdaptName(GetGeneratedBaseTypeName(namedType));

            if (IsAsnTypeName(adaptedGenBaseTypeName))
            {
                InsertOnceBasicIncludeList(adaptedGenBaseTypeName);
            }

            string adaptedElementTypeName = 
                AdaptName(GetGeneratedElementTypeName(namedType));

            HdrPrint(1,
                    "void Set%s(%s* element)\n",
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str());        
            HdrPrint(1,
                    "{\n");
            HdrPrint(2,
                    "ITS_REQUIRE(element != NULL);\n");
            HdrPrint(2,
                    "element->AsnObject::SetDescription"
                    "(Get%sStaticDescription());\n",
                    adaptedName.c_str());
            HdrPrint(2,
                    "AddElement(%d, element);\n",
                    index);
            HdrPrint(1,
                    "}\n");
            HdrNewLine();

            HdrPrint(1,
                    "void Set%s(const %s& element)\n",
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str());        
            HdrPrint(1,
                    "{\n");
            HdrPrint(2,
                    "%sAsnObject& asnObject = const_cast<%s&>(element);\n",
                    GetItsNamespaceScope().c_str(),
                    adaptedElementTypeName.c_str()); 
            HdrPrint(2,
                    "asnObject.SetDescription(Get%sStaticDescription());\n",
                    adaptedName.c_str());
            HdrPrint(2,
                    "AddElement(%d, element);\n",
                    index);
            HdrPrint(0,
                    "}\n");
            HdrNewLine();

            if (namedType->IsOptional())
            {
                HdrPrint(1,
                        "bool Option%s() const\n",
                        adaptedName.c_str());            
                HdrPrint(1,
                        "{\n");
                HdrPrint(2,
                        "return Contains(%d);\n",
                        index);
                HdrPrint(1,
                        "}\n");
                HdrNewLine();
            }

            if (namedType->GetType() == TYPE_DEFINED)
            {
                HdrPrint(1,
                        "const %s& Get%s() const\n",
                        adaptedElementTypeName.c_str(),
                        adaptedName.c_str());
            }
            else // Nested type.
            {
                HdrPrint(1,
                        "const %s& Get%s() const\n",
                        adaptedElementTypeName.c_str(),
                        adaptedName.c_str());
            }

            HdrPrint(1,
                    "{\n");

            if (namedType->IsOptional())
            {
            
                HdrPrint(2,
                        "ITS_REQUIRE(Option%s());\n",
                        adaptedName.c_str());
            }

            HdrPrint(2,
                    "return static_cast<const %s&> (ElementAt(%d));\n",
                    adaptedElementTypeName.c_str(),
                    index);
            HdrPrint(1,
                    "}\n");
            HdrNewLine();

            index++;
        }
    }

    GenerateTypeClassEndPart();  
}


void
GenerateCppVisitor::VisitSetTypeList(TypeList* typeList)
{


}


void 
GenerateCppVisitor::VisitSetOfTypeBegin(SetOfType* setOfType)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitSetOfTypeEnd(SetOfType* setOfType)
{
    InsertOnceBasicIncludeList("AsnSetOf");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnSetOf");

    HdrNewLine();
    HdrPrint(0, 
            "////////// Begin Nested Class //////////\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "////////// Begin Nested Class //////////\n");
    SrcNewLine();

    Type* type = setOfType->GetSetOfType();

    string eltTypeName = GetGeneratedTypeName(type);

    if (IsAsnTypeName(eltTypeName))
    {
        InsertOnceBasicIncludeList(eltTypeName);
    }
    else
    {
        InsertOnceReferenceIncludeList(eltTypeName);
    }

    string eltBaseTypeName = AdaptName(GetGeneratedBaseTypeName(type));

    if (IsAsnTypeName(eltBaseTypeName))
    {
        InsertOnceBasicIncludeList(eltBaseTypeName);
    }

    if (IsAsnTypeName(eltTypeName))
    {
        eltTypeName.erase(0, 3);   // Remove "Asn" prefix.

        for (size_t i = 0; i < eltTypeName.size(); i++)
        {
            eltTypeName[i] = toupper(eltTypeName[i]);
        }
    }

    typedefListStack.push_front(GetTypedefList());
    GetTypedefList().clear();

    PushContext();

    SetCurrentTypeName(eltTypeName);

    SetCurrentType(type);

    // Generate subordinate type.

    type->Accept(this);

    PopContext();

    GetHdr() += GetTypedefListString();

    typedefList = typedefListStack.front();
    typedefListStack.pop_front();

    HdrNewLine();
    HdrPrint(0, 
            "////////// End Nested Class //////////\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "////////// End Nested Class //////////\n");
    SrcNewLine();

    HdrPrint(1,
            "%s() : %sAsnSetOf(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();

    HdrPrint(1,
            "%s(%sOctets& octets) : %sAsnSetOf(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnSetOf(rhs)\n",
            typeName.c_str(),
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnSetOf(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescSetOf");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetClauseSizeInstructions();

    SrcPrint(2,
            "staticDesc._element = Get%sStaticDescription();\n",
            eltTypeName.c_str());            

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GenerateElementStaticDescription(type, eltTypeName);

    HdrNewLine();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    HdrPrint(1,
            "void AddElement(%s* element)\n",
            eltTypeName.c_str());
    HdrPrint(1,
            "{\n");
    HdrPrint(2,
            "ITS_REQUIRE(element != NULL);\n");
    HdrPrint(2,
            "element->AsnObject::SetDescription"
            "(Get%sStaticDescription());\n",
            eltTypeName.c_str());
    HdrPrint(2,
            "AsnSetOf::AddElement(element);\n");
    HdrPrint(1,
            "}\n");
    HdrNewLine();

    HdrPrint(1,
            "void AddElement(const %s& element)\n",
            eltTypeName.c_str());
    HdrPrint(1,
            "{\n");
    HdrPrint(2, 
            "%sAsnObject& asnObject = const_cast<%s&>(element);\n",
            GetItsNamespaceScope().c_str(),
            eltTypeName.c_str()); 
    HdrPrint(2, 
            "asnObject.SetDescription(Get%sStaticDescription());\n",
            eltTypeName.c_str());
    HdrPrint(2,
            "AsnSetOf::AddElement(element);\n");
    HdrPrint(1,
            "}\n");
    HdrNewLine();

    HdrPrint(1,
            "const %s& ElementAt(int index) const\n",
            eltTypeName.c_str());
    HdrPrint(1,
            "{\n");
    HdrPrint(2,
            "return static_cast<const %s&> (AsnSetOf::ElementAt(index));\n",
            eltTypeName.c_str());
    HdrPrint(1,
            "}\n");
    HdrNewLine();

    GenerateTypeClassEndPart();      
}


void
GenerateCppVisitor::VisitSetOfTypeType(Type* type)
{
    // Nothing to do.
}


void
GenerateCppVisitor::VisitSetOfConstraint(Constraint* constraint)
{
    // Nothing to do.
}


void 
GenerateCppVisitor::VisitOctetStringType(OctetStringType* octetStringType)
{
    InsertOnceBasicIncludeList("AsnOctetString");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnOctetString");

    HdrPrint(1, 
            "%s() : %sAsnOctetString(false)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();

    HdrPrint(1, 
            "%s(const std::vector<byte>& array) : "
            "%sAsnOctetString(array, false)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();

    HdrPrint(1,
            "%s(%sOctets& octets) : %sAsnOctetString(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1, 
            "%s(const %s& rhs) : %sAsnOctetString(rhs)\n", 
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* description) : "
            "%sAsnOctetString(description)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* description, "
            "const std::vector<byte>& array) : "
            "%sAsnOctetString(description, array)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName, 
                                                    "AsnDescOctetString");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetClauseSizeInstructions();

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    GenerateTypeClassEndPart();
}


void 
GenerateCppVisitor::VisitBaseStringType(BaseStringType* baseStringType)
{
    InsertOnceBasicIncludeList("AsnBaseString");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnBaseString");

    HdrPrint(1, 
            "%s() : %sAsnBaseString(false)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();

    HdrPrint(1, 
            "%s(const std::string& str) : "
            "%sAsnBaseString(str, false)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();

    HdrPrint(1,
            "%s(%sOctets& octets) : %sAsnBaseString(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1, 
            "%s(const %s& rhs) : %sAsnBaseString(rhs)\n", 
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* description) : "
            "%sAsnBaseString(description)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* description, "
            "const std::string& str) : "
            "%sAsnBaseString(description, str)\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName, 
                                                    "AsnDescBaseString");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetClauseSizeInstructions();

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    GenerateTypeClassEndPart();
}


void
GenerateCppVisitor::VisitDefinedType(DefinedType* definedType)
{
    string referenceTypeName = AdaptName(definedType->GetName());
    string typeName = AdaptName(GetCurrentTypeName());

    SrcNewLine();

    InsertOnceReferenceIncludeList(referenceTypeName);

    string typedefStr = "";

    typedefStr.reserve(SIZE_TINY);
    
    if (!IsAsnUsefulTypeName(referenceTypeName))
    {
        if (referenceTypeName != typeName)
        {
            typedefStr += GetLevelIndent(GetLevel());

            typedefStr += GetVarArgsString( 
                                "typedef %s %s;\n",
                                referenceTypeName.c_str(),
                                typeName.c_str()); 
        }
        else
        {
            if (_generateNamespaceDefineCode)
            {
                typedefStr += GetLevelIndent(GetLevel());

                typedefStr += GetVarArgsString(
                                    "#if defined(ITS_NAMESPACE)\n");
            }

            if (cppNamespaceG == "")
            {
                typedefStr += GetLevelIndent(GetLevel() + 1);

                typedefStr += GetVarArgsString(
                                "typedef its::%s %s;\n",
                                referenceTypeName.c_str(),
                                typeName.c_str());
            }
            else
            {
                typedefStr += GetLevelIndent(GetLevel() + 1);

                typedefStr += GetVarArgsString(
                                "typedef %s::%s %s;\n",
                                cppNamespaceG.c_str(),
                                referenceTypeName.c_str(),
                                typeName.c_str());
            }

            if (_generateNamespaceDefineCode)
            {
                typedefStr += GetLevelIndent(GetLevel());

                typedefStr += GetVarArgsString(
                                    "#else // !defined(ITS_NAMESPACE)\n");

                typedefStr += GetLevelIndent(GetLevel() + 1);

                typedefStr += GetVarArgsString(
                                    "typedef %s %s;\n",
                                    referenceTypeName.c_str(),
                                    typeName.c_str());

                typedefStr += GetLevelIndent(GetLevel());

                typedefStr += GetVarArgsString(
                                    "#endif // defined(ITS_NAMESPACE)\n");
            }
        }
    }
    else
    {
        typedefStr += GetLevelIndent(GetLevel());

        typedefStr += GetVarArgsString(
                                "typedef %s%s %s;\n",
                                GetItsNamespaceScope().c_str(),
                                referenceTypeName.c_str(),
                                typeName.c_str()); 
    }

    InsertOnceTypedefList(typedefStr);

    if (GetLevel() == 0)
    {
        GetHdr() += GetTypedefListString();

        GetTypedefList().clear();
    }

    SrcPrint(0, 
            "// Type %s is a reference => no code generated.\n",
            typeName.c_str());

}


void
GenerateCppVisitor::VisitAnyType(AnyType* anyType)
{
    InsertOnceBasicIncludeList("AsnAny");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnAny");

    HdrPrint(1, 
            "%s() : %sAsnAny(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(%sAsnObject* any) : %sAsnAny(any, false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets) : %sAsnAny(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnAny(rhs)\n",
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnAny(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description, %sAsnObject* any) "
            ": %sAsnAny(description, any)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescAny");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetClauseAnyTagInstructions();

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    GenerateTypeClassEndPart();
}


void
GenerateCppVisitor::VisitAnyDefinedByType(AnyDefinedByType* anyDefinedByType)
{
    InsertOnceBasicIncludeList("AsnAny");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnAny");

    HdrPrint(1, 
            "%s() : %sAsnAny(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(%sAsnObject* any) : %sAsnAny(any, false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets) : %sAsnAny(false)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs) : %sAsnAny(rhs)\n",
            typeName.c_str(), 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* description) : "
            "%sAsnAny(description)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    HdrPrint(0,
            "%s(%sAsnDescObject* description, %sAsnObject* any) "
            ": %sAsnAny(description, any)\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescAny");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(AdaptName(GetCurrentTypeName()));

    GenerateSetClauseAnyTagInstructions();

    GenerateSetNamedTypeNameInstructions();

    GenerateSetTypeNameInstructions();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    GenerateTypeClassEndPart();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GenerateCppVisitor::VisitValueDefBegin(ValueDef* valueDef)
{

}


void
GenerateCppVisitor::VisitValueDefMiddle(ValueDef* valueDef)
{

}


void
GenerateCppVisitor::VisitValueDefEnd(ValueDef* valueDef)
{

}


void 
GenerateCppVisitor::VisitValueDefType(ValueDef* valueDef, Type* type)
{
    // Must do nothing (i.e. must not generate code).
}


void 
GenerateCppVisitor::VisitValueBegin(Value* value)
{

}


void 
GenerateCppVisitor::VisitValueEnd(Value* value)
{

}


void
GenerateCppVisitor::VisitBitStringValue(BitStringValue* bitStringValue)
{

}


void
GenerateCppVisitor::VisitBooleanValue(BooleanValue* booleanValue)
{


    // Inside VisitBooleanTypeEnd call booleanType->SetAuxiliaryTypeName(...).
    // The typename must not be adapted if it is reused to build the #include <>.
    // The previous get function must contains an assertion if nothing has been set.
    // Now booleanType* contains typeName or typeName actually used for the generation.

    
    // Retrieve valueName. 
    
    // All ValueDef should be translated to a function that return a new XXXType object.
    // Since all the value names are unique within one module, that's easy. 
    // Can be a problem with the idea to generate only one file for all value. 
    // What happen if 2 values have the same name in 2 differents modules and some
    // value import export? => screwed up!!!. 

    // => Best 
    // Generate one file per value def, exactly like the TypeDef. Solve previous problem.
    // Agree, many files will be generated. 
    // Better to prefix all the files by Value_...So they can be isolated. 
    // This is not good for INTEGER def, but pretty good for OID defs. 

    // Only valueDef are generating functions. 



    // Create a value function name. Must include some kind of scoping mechanism, 
    // because local functions are forbidden in C++.





}


void
GenerateCppVisitor::VisitCharacterStringValue(
                            CharacterStringValue* characterStringValue)
{

}


void
GenerateCppVisitor::VisitChoiceValue(ChoiceValue* choiceValue)
{

}


void
GenerateCppVisitor::VisitEnumeratedValue(EnumeratedValue* enumeratedValue)
{

}


void
GenerateCppVisitor::VisitIntegerValue(IntegerValue* integerValue)
{

}


void
GenerateCppVisitor::VisitObjectIdentifierValue(
                            ObjectIdentifierValue* objectIdentifierValue)
{

}


void
GenerateCppVisitor::VisitOctetStringValue(OctetStringValue* octetStringValue)
{

}


void
GenerateCppVisitor::VisitMaxValue(MaxValue* maxValue)
{

}


void
GenerateCppVisitor::VisitMinValue(MinValue* minValue)
{

}


void
GenerateCppVisitor::VisitNullValue(NullValue* nullValue)
{

}


void
GenerateCppVisitor::VisitRealValue(RealValue* realValue)
{

}


void 
GenerateCppVisitor::VisitSequenceValueBegin(SequenceValue* sequenceValue)
{

}


void 
GenerateCppVisitor::VisitSequenceValueEnd(SequenceValue* sequenceValue)
{

}


void 
GenerateCppVisitor::VisitDefinedValue(DefinedValue* definedValue)
{

}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCppVisitor::VisitNamedNumberBegin(NamedNumber* namedNumber)
{

}


void 
GenerateCppVisitor::VisitNamedNumberEnd(NamedNumber* namedNumber)
{

}


void 
GenerateCppVisitor::VisitTag(Tag* tag)
{

}


void 
GenerateCppVisitor::VisitConstraintBegin(Constraint* constraint)
{

}


void 
GenerateCppVisitor::VisitConstraintEnd(Constraint* constraint)
{

}


void
GenerateCppVisitor::VisitSingleValueConstraintElementBegin(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{
    if (insideSizeConstraint)
    {
        string instruction = "staticDesc._clauseSize = true;\n";

        constraintInstructionList.push_back(instruction);

        Value* value = singleValueConstraintElement->GetValue();

        Value* baseValue = value->GetBaseValue();

        if (baseValue->GetValueType() == VALUE_INTEGER)
        {
            IntegerValue* integerValue =
                static_cast<IntegerValue*> (baseValue);

            instruction = "staticDesc._minSize = ";
            instruction += LongToString(integerValue->GetValue());
            instruction += ";\n";

            constraintInstructionList.push_back(instruction);

            instruction = "staticDesc._maxSize = ";
            instruction += LongToString(integerValue->GetValue());
            instruction += ";\n";

            constraintInstructionList.push_back(instruction);
        }
    }
}


void
GenerateCppVisitor::VisitSingleValueConstraintElementEnd(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{

}


void
GenerateCppVisitor::VisitValueRangeConstraintElementBegin(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{

}


void
GenerateCppVisitor::VisitValueRangeConstraintElementMiddle(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{

}


void
GenerateCppVisitor::VisitValueRangeConstraintElementEnd(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{
    if (insideSizeConstraint)
    {
        string instruction = "staticDesc._clauseSize = true;\n";

        constraintInstructionList.push_back(instruction);

        Value* lowerValue = valueRangeConstraintElement->GetLower();
        Value* upperValue = valueRangeConstraintElement->GetUpper();

        Value* lowerBaseValue = lowerValue->GetBaseValue();
        Value* upperBaseValue = upperValue->GetBaseValue();

        if (lowerBaseValue->GetValueType() == VALUE_INTEGER)
        {
            IntegerValue* integerValue =
                static_cast<IntegerValue*> (lowerBaseValue);

            instruction = "staticDesc._minSize = ";
            instruction += LongToString(integerValue->GetValue());
            instruction += ";\n";

            constraintInstructionList.push_back(instruction);
        }

        if (lowerBaseValue->GetValueType() == VALUE_MIN)
        {
            instruction = "staticDesc._minSize = LONG_MIN;\n";

            constraintInstructionList.push_back(instruction);
        }

        if (upperBaseValue->GetValueType() == VALUE_INTEGER)
        {
            IntegerValue* integerValue = 
                static_cast<IntegerValue*> (upperBaseValue);

            instruction = "staticDesc._maxSize = ";
            instruction += LongToString(integerValue->GetValue());
            instruction += ";\n";

            constraintInstructionList.push_back(instruction);
        }

        if (upperBaseValue->GetValueType() == VALUE_MAX)
        {
            instruction = "staticDesc._maxSize = LONG_MAX;\n";

            constraintInstructionList.push_back(instruction);
        }
    }
}


void GenerateCppVisitor::VisitSizeConstraintElementBegin(
                            SizeConstraintElement* 
                                sizeConstraintElement)
{
    insideSizeConstraint = true;
}


void GenerateCppVisitor::VisitSizeConstraintElementEnd(
                            SizeConstraintElement*
                                sizeConstraintElement)
{
    insideSizeConstraint = false;
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCppVisitor::GenerateDefaultConstructorBody()
{
    HdrPrint(1, 
            "{\n");
    HdrPrint(2, 
            "Initialize();\n");
    HdrPrint(1, 
            "}\n");
    HdrNewLine();
}


void 
GenerateCppVisitor::GenerateDecodeConstructorBody()
{
    HdrPrint(1, 
            "{\n");
    HdrPrint(2, 
            "Initialize();\n");
    HdrPrint(2, 
            "Decode(octets);\n");
    HdrPrint(1, 
            "}\n");
    HdrNewLine();
}


void 
GenerateCppVisitor::GenerateNothingToDoBody()
{
    HdrPrint(1, 
            "{\n");
    HdrPrint(2, 
            "// Nothing to do.\n");
    HdrPrint(1, 
            "}\n");
    HdrNewLine();
}


void 
GenerateCppVisitor::GenerateInitializeMemberFunction()
{
    HdrPrint(1, 
            "void Initialize()\n"); 
    HdrPrint(1, 
            "{\n");

    if (_generateAssertionCode)
    {
        HdrPrint(2, 
                "ITS_ASSERT(_description == NULL);\n");
    }

    HdrPrint(2, 
            "_description = GetStaticDescription();\n");
    HdrPrint(1, 
            "}\n");
    HdrNewLine();
}


void 
GenerateCppVisitor::GenerateDestructor(const string& typeName)
{
    HdrPrint(1, 
            "virtual ~%s()\n", 
            typeName.c_str());
    HdrPrint(1, 
            "{\n");
    HdrPrint(2, 
            "// Nothing to do.\n");
    HdrPrint(1, 
            "}\n");
    HdrNewLine();
}


void 
GenerateCppVisitor::GenerateCloneMemberFunction(const string& typeName)
{
    HdrPrint(1, 
            "virtual %sAsnObject* Clone() const\n", 
            GetItsNamespaceScope().c_str());
    HdrPrint(1, 
            "{\n");
    HdrPrint(2, 
            "return new %s(*this);\n", 
            typeName.c_str());
    HdrPrint(1, 
            "}\n");
    HdrNewLine();
}


void 
GenerateCppVisitor::GenerateGetNameMemberFunction(const string& typeName)
{
    HdrPrint(1, 
            "virtual std::string GetName() const\n");
    HdrPrint(1, 
            "{ return \"%s\"; }\n", 
            typeName.c_str());
    HdrNewLine();
}


void 
GenerateCppVisitor::GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                const string& typeName, 
                                                const string& asnDescTypeName)
{
    HdrPrint(1, 
            "static %sAsnDescObject* GetStaticDescription();\n",
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "AsnDescObject* %sGetStaticDescription()\n", 
            GetScopeString().c_str());
    SrcPrint(0, 
            "{\n");
    SrcPrint(1, 
            "static volatile bool initialized = false;\n");
    SrcPrint(1, 
            "static AsnDescObject* result = NULL;\n");

    Type* baseType = GetCurrentType()->GetBaseType();

    if (baseType->GetType() == TYPE_SEQUENCE ||
        baseType->GetType() == TYPE_SET)
    {
        // class SetType inherits from class SequenceType.

        SequenceType* sequenceType = 
            static_cast<SequenceType*> (baseType);

        TypeList* typeList = sequenceType->GetFlattenedTypeList();

        SrcPrint(1, 
                "static %s staticDesc(%d);\n", 
                asnDescTypeName.c_str(), 
                typeList->size());
    }
    else
    {
        SrcPrint(1, "static %s staticDesc;\n", asnDescTypeName.c_str());
    }
    SrcNewLine();

    SrcPrint(1, 
            "if (initialized)\n");
    SrcPrint(1, 
            "{\n");

    if (_generateAssertionCode)
    {
        SrcPrint(2, 
                "ITS_ENSURE(result != NULL);\n");
    }

    SrcPrint(2, 
            "return result;\n");
    SrcPrint(1, 
            "}\n");
    SrcNewLine();
    SrcPrint(1, 
            "Asn::Lock();\n");
    SrcNewLine();
    SrcPrint(1, 
            "if (initialized)\n");
    SrcPrint(1, 
            "{\n");
    SrcPrint(2, 
            "Asn::Unlock();\n");

    if (_generateAssertionCode)
    {
        SrcPrint(2, 
                "ITS_ENSURE(result != NULL);\n");
    }

    SrcPrint(2, 
            "return result;\n");
    SrcPrint(1, 
            "}\n");
    SrcPrint(1, 
            "else\n");
    SrcPrint(1, 
            "{\n");

    if (_generateAssertionCode)
    {
        SrcPrint(2, 
                "ITS_ASSERT(result == NULL);\n");
    }

    GenerateLicenseCheck();

    SrcPrint(2, 
            "staticDesc.SetCloneForFactory(new %s(&staticDesc));\n", 
            typeName.c_str());
}


void 
GenerateCppVisitor::GenerateGetStaticDescriptionMemberFunctionEndPart()
{
    SrcPrint(2, "result = &staticDesc;\n");
    SrcPrint(2, "initialized = true;\n");
    SrcPrint(2, "Asn::Unlock();\n");

    if (_generateAssertionCode)
    {
        SrcPrint(2, "ITS_ENSURE(result != NULL);\n");
    }

    SrcPrint(2, "return result;\n");
    SrcPrint(1, "}\n");
    SrcPrint(0, "}\n");
    SrcNewLine();
}


void 
GenerateCppVisitor::GenerateTagAddLevelInstructions()
{
    TagList* tagList = GetCurrentType()->GetAdjustedTagList();

    tagList->reverse();

    for (TagList::iterator tIter = tagList->begin();
         tIter != tagList->end();
         tIter++)
    {
        Tag* tag = *tIter;

        SrcPrint(2, 
                "staticDesc.TagAddLevel(new Tag(Tag::%s, Tag::%s, %d));\n",
                tag->GetTagClassString().c_str(),
                tag->GetTagTypeString().c_str(),
                tag->GetNumber());
    }
}


void 
GenerateCppVisitor::GenerateSetClauseSizeInstructions()
{
    constraintInstructionList.clear();

    Type* type = GetCurrentType();

    ConstraintList* constraintList = type->GetConstraintList();

    if (!(constraintList->empty()))
    {
        VisitTypeConstraintList(constraintList);
    }

    if (type->GetType() == TYPE_SEQUENCE_OF)
    {
        SequenceOfType* sequenceOfType =
            static_cast<SequenceOfType*> (type);

        if (sequenceOfType->HasConstraint())
        {
            Constraint* constraint = sequenceOfType->GetConstraint();

            constraint->Accept(this);
        }
    }

    if (type->GetType() == TYPE_SET_OF)
    {
        SetOfType* setOfType =
            static_cast<SetOfType*> (type);

        if (setOfType->HasConstraint())
        {
            Constraint* constraint = setOfType->GetConstraint();

            constraint->Accept(this);
        }
    }

    for (list<string>::iterator iter = constraintInstructionList.begin();
         iter != constraintInstructionList.end();
         iter++)
    {
        SrcPrint(2,
                "%s",
                (*iter).c_str());
    }

    constraintInstructionList.clear();
}


void 
GenerateCppVisitor::GenerateSetClauseOptionalInstructions()
{
    if (GetCurrentType()->IsOptional())
    {
        SrcPrint(2, 
                "staticDesc._clauseOptional = true;\n");
    }
}


void 
GenerateCppVisitor::GenerateSetClauseDefaultInstructions(const string& typeName)
{
    if (GetCurrentType()->HasDefaultValue())
    {
        SrcPrint(2, 
                "staticDesc._clauseDefault = true;\n");

        Value* value = GetCurrentType()->GetDefaultValue();

        if (value != NULL)
        {
            Value* baseValue = value->GetBaseValue();

            if (baseValue->GetValueType() == VALUE_BOOLEAN)
            {
                BooleanValue* booleanValue = 
                    static_cast<BooleanValue*> (baseValue);

                SrcPrint(2, "{\n");

                SrcPrint(3,
                        "%s* cloneForDefaultFactory = new %s(&staticDesc);\n",
                        typeName.c_str(),
                        typeName.c_str());
                SrcPrint(3,
                        "cloneForDefaultFactory->SetValue(%s);\n",
                        booleanValue->GetValue() ? "true" : "false");
                SrcPrint(3,
                        "staticDesc.SetCloneForDefaultFactory("
                        "cloneForDefaultFactory);\n");

                SrcPrint(2, "}\n");
            }
            else if (baseValue->GetValueType() == VALUE_INTEGER)
            {
                IntegerValue* integerValue = 
                    static_cast<IntegerValue*> (baseValue);

                SrcPrint(2, "{\n");

                SrcPrint(3,
                        "%s* cloneForDefaultFactory = new %s(&staticDesc);\n",
                        typeName.c_str(),
                        typeName.c_str());
                SrcPrint(3,
                        "cloneForDefaultFactory->SetValue((long)%ld);\n",
                        integerValue->GetValue());
                SrcPrint(3,
                        "staticDesc.SetCloneForDefaultFactory("
                        "cloneForDefaultFactory);\n");

                SrcPrint(2, "}\n");
            }
            else if (baseValue->GetValueType() == VALUE_ENUMERATED)
            {
                EnumeratedValue* enumeratedValue =
                    static_cast<EnumeratedValue*> (baseValue);

                Type* associatedType = enumeratedValue->GetAssociatedType();

                EnumeratedType* enumeratedType =
                    static_cast<EnumeratedType*> (associatedType);

                NamedNumber* 
                    namedNumber = 
                        enumeratedType->
                            RetrieveNamedNumber(
                                enumeratedValue->GetName());

                SrcPrint(2, "{\n");

                SrcPrint(3,
                        "%s* cloneForDefaultFactory = new %s(&staticDesc);\n",
                        typeName.c_str(),
                        typeName.c_str());
                SrcPrint(3,
                        "cloneForDefaultFactory->SetValue((long)%ld);\n",
                        namedNumber->GetNumber());
                SrcPrint(3,
                        "staticDesc.SetCloneForDefaultFactory("
                        "cloneForDefaultFactory);\n");

                SrcPrint(2, "}\n");
            }
            else if (baseValue->GetValueType() == VALUE_DEFINED)
            {
                DefinedValue* definedValue = 
                    static_cast<DefinedValue*> (value);

                Type* associatedType = definedValue->GetAssociatedType();

                EnumeratedType* enumeratedType =
                    static_cast<EnumeratedType*> (associatedType);

                NamedNumber* 
                    namedNumber = 
                        enumeratedType->
                            RetrieveNamedNumber(
                                definedValue->GetName());

                if (definedValue->IsEnumeratedValue())
                {
                    SrcPrint(2, "{\n");

                    SrcPrint(3,
                            "%s* cloneForDefaultFactory = "
                            "new %s(&staticDesc);\n",
                            typeName.c_str(),
                            typeName.c_str());
                    SrcPrint(3,
                            "cloneForDefaultFactory->SetValue((long)%ld);\n",
                            namedNumber->GetNumber());
                    SrcPrint(3,
                            "staticDesc.SetCloneForDefaultFactory("
                            "cloneForDefaultFactory);\n");

                    SrcPrint(2, "}\n");
                }
                else
                {
                    PrintErrLoc(
                        GetModule()->GetAsn1SrcFileName(), 
                        GetCurrentType()->GetLineNumber());
                    cerr << "ERROR - default value type not supported. ";
                    cerr << "Type \"";
                    cerr << typeName;
                    cerr << "\". ";
                    cerr << "Must use default value with code in ASN.1 ";
                    cerr << "module.";
                    cerr << endl;
                }
            }
            else
            {
                PrintErrLoc(
                    GetModule()->GetAsn1SrcFileName(), 
                    GetCurrentType()->GetLineNumber());
                cerr << "ERROR - default value type not supported. Type \"";
                cerr << typeName;
                cerr << "\". ";
                cerr << "Must use default value with code in ASN.1 module.";
                cerr << endl;
            }
        }
        else
        {
            if (GetCurrentType()->HasDefaultValueWithCode())
            {
                string valueWithCode = 
                    GetCurrentType()->GetDefaultValueWithCode();

                bool keepWS = true;
                string instruction = "";
                vector<string> instructions;

                for (size_t i = 0; i < valueWithCode.size(); i++)
                {
                    char c = valueWithCode[i];

                    switch (c)
                    {
                    case ' ':
                    case '\t':
                        if (keepWS)
                        {
                            instruction.append(1, c);
                        }
                        break;
                    case '\r':
                    case '\n':
                        keepWS = false;
                        break;
                    case ';': 
                        instruction.append(1, c);
                        instructions.push_back(instruction);
                        instruction = "";
                        keepWS = true;
                        break;
                    default:
                        instruction.append(1, c);
                        keepWS = true;
                        break;
                    }
                }

                SrcPrint(2, "{\n");

                for (size_t j = 0; j < instructions.size(); j++)
                {
                    SrcPrint(3, "%s\n", instructions[j].c_str());
                }

                SrcPrint(2, "}\n");
            }
            else
            {
                PrintErrLoc(
                    GetModule()->GetAsn1SrcFileName(), 
                    GetCurrentType()->GetLineNumber());
                cerr << "ERROR - missing default value. Type \"";
                cerr << typeName;
                cerr << "\". ";
                cerr << "Must use default value with code in ASN.1 module.";
                cerr << endl;
            }
        }
    }
}


void 
GenerateCppVisitor::GenerateSetClauseAnyTagInstructions()
{
    TagList* tagList = GetCurrentType()->GetAdjustedTagList();

    if (tagList->empty())
    {
        SrcPrint(2, 
                "staticDesc._clauseAnyTag = true;\n");
    }
}


void
GenerateCppVisitor::GenerateSetClauseExtensibleInstructions()
{
    Type* type = GetCurrentType();

    if (type->GetType() == TYPE_ENUMERATED)
    {
        EnumeratedType* enumeratedType =
            static_cast<EnumeratedType*> (type);

        if (enumeratedType->IsExtendable())
        {
            SrcPrint(2, 
                    "staticDesc._clauseExtensible = true;\n");
        }
    }

    if (type->GetType() == TYPE_SEQUENCE)
    {
        SequenceType* sequenceType = 
            static_cast<SequenceType*> (type);

        if (sequenceType->IsExtendable())
        {
            SrcPrint(2, 
                    "staticDesc._clauseExtensible = true;\n");
        }
    }

    if (type->GetType() == TYPE_SET)
    {
        SetType* setType = 
            static_cast<SetType*> (type);

        if (setType->IsExtendable())
        {
            SrcPrint(2, 
                    "staticDesc._clauseExtensible = true;\n");
        }
    }
}


void 
GenerateCppVisitor::GenerateSetNamedTypeNameInstructions()
{
    Type* type = GetCurrentType();

    if (type->IsNamed())
    {
        SrcPrint(2,
                "staticDesc.SetNamedTypeName(\"%s\");\n",
                type->GetName().c_str());
    }
}


void
GenerateCppVisitor::GenerateSetTypeNameInstructions()
{
    string typeName = GetCurrentTypeName();

    if (level == 0)
    {
        SrcPrint(2,
                "staticDesc.SetTypeName(\"%s\");\n",
                typeName.c_str());
    }
}


void 
GenerateCppVisitor::GeneratePublicScope()
{
    HdrPrint(0, 
            "public:\n");
    HdrNewLine();
}


void 
GenerateCppVisitor::GenerateProtectedScope()
{
    HdrPrint(0, 
            "protected:\n");
    HdrNewLine();
}


void 
GenerateCppVisitor::GenerateTypeClassBeginPart(
                                    const std::string& typeName, 
                                    const std::string& asnTypeName)
{
    HdrNewLine();
    HdrNewLine();

    SrcNewLine();
    SrcNewLine();

    HdrPrint(0, 
            "class %s : public %s%s\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            asnTypeName.c_str());
    HdrPrint(0,
            "{\n");
    HdrPrint(0, 
            "public:\n");
    HdrNewLine();
}


void 
GenerateCppVisitor::GenerateTypeClassEndPart()
{
    HdrPrint(0, 
            "};\n");
    HdrNewLine(); 
}


void 
GenerateCppVisitor::GenerateElementStaticDescription(
                                        Type* elementType, 
                                        const string& elementName)
{
    HdrPrint(1, 
            "static %sAsnDescObject* Get%sStaticDescription();\n",
            GetItsNamespaceScope().c_str(),
            elementName.c_str());

    SrcPrint(0, 
            "AsnDescObject* %sGet%sStaticDescription()\n",
            GetScopeString().c_str(), 
            elementName.c_str());        
    SrcPrint(0, 
            "{\n");
    SrcPrint(1, 
            "static volatile bool initialized = false;\n");
    SrcPrint(1, 
            "static AsnDescObject* result = NULL;\n");

    Type* baseType = elementType->GetBaseType();

    string asnTypeName = GetGeneratedTypeName(baseType);

    string asnDescTypeName = asnTypeName;
    asnDescTypeName.insert(3, "Desc");

    if (baseType->GetType() == TYPE_SEQUENCE ||
        baseType->GetType() == TYPE_SET)
    {
        // class SetType inherits from class SequenceType.

        SequenceType* sequenceType = 
            static_cast<SequenceType*> (baseType);

        TypeList* typeList = sequenceType->GetFlattenedTypeList();

        SrcPrint(1, 
                "static %s staticDesc(%d);\n", 
                asnDescTypeName.c_str(), 
                typeList->size());
    }
    else
    {
        SrcPrint(1, "static %s staticDesc;\n", asnDescTypeName.c_str());
    }
    SrcNewLine();

    SrcPrint(1, 
            "if (initialized)\n");
    SrcPrint(1, 
            "{\n");

    if (_generateAssertionCode)
    {
        SrcPrint(2, 
                "ITS_ENSURE(result != NULL);\n");
    }

    SrcPrint(2, 
            "return result;\n");
    SrcPrint(1, 
            "}\n");
    SrcNewLine();
    SrcPrint(1, 
            "Asn::Lock();\n");
    SrcNewLine();
    SrcPrint(1, 
            "if (initialized)\n");
    SrcPrint(1, 
            "{\n");
    SrcPrint(2, 
            "Asn::Unlock();\n");

    if (_generateAssertionCode)
    {
        SrcPrint(2, 
                "ITS_ENSURE(result != NULL);\n");
    }

    SrcPrint(2, 
            "return result;\n");
    SrcPrint(1, 
            "}\n");
    SrcPrint(1, 
            "else\n");
    SrcPrint(1, 
            "{\n");

    if (_generateAssertionCode)
    {
        SrcPrint(2, 
                "ITS_ASSERT(result == NULL);\n");
    }

    string elementTypeName;

    if (elementType->IsNamed())
    {
        // Case of TYPE_CHOICE, TYPE_SEQUENCE and TYPE_SET.

        elementTypeName = AdaptName(GetGeneratedElementTypeName(elementType));
    }
    else
    {
        // Case of TYPE_SEQUENCE_OF and TYPE_SET_OF.

        elementTypeName = elementName;
    }

    SrcPrint(2, 
            "staticDesc.SetCloneForFactory(new %s(&staticDesc));\n", 
            elementTypeName.c_str());

    PushContext();

    // Do not want to change the level.
    SetLevel(GetLevel() - 1);

    SetCurrentType(elementType);

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseDefaultInstructions(elementTypeName);

    GenerateSetClauseExtensibleInstructions();

    switch (baseType->GetType())
    {
        case TYPE_SEQUENCE:
        case TYPE_SET:
        {
            // Class SetType inherits from class SequenceType.

            SequenceType* sequenceType =
                static_cast<SequenceType*> (baseType);

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseType);

            GenerateSetClauseExtensibleInstructions();

            PopContext();
            SetLevel(GetLevel() + 1);

            TypeList* typeList = sequenceType->GetFlattenedTypeList();

            if (!(typeList->empty()))
            {
                int index = 0;

                for (TypeList::iterator iter = typeList->begin();
                     iter != typeList->end();
                     iter++)
                {
                    Type* namedType = *iter;

                    string adaptedName = AdaptName(namedType->GetName());

                    SrcPrint(2,
                            "staticDesc._elementVect[%d] = %s::"
                            "Get%sStaticDescription();\n",
                            index,
                            elementTypeName.c_str(),
                            adaptedName.c_str());
                    
                    index++;
                }
            }
        }

        break;

        case TYPE_CHOICE:
        {
            ChoiceType* choiceType =
                static_cast<ChoiceType*> (baseType);

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseType);

            GenerateSetClauseExtensibleInstructions();

            PopContext();
            SetLevel(GetLevel() + 1);

            TypeList* typeList = choiceType->GetFlattenedTypeList();

            if (!(typeList->empty()))
            {
                for (TypeList::iterator iter = typeList->begin();
                     iter != typeList->end();
                     iter++)
                {
                    Type* namedType = *iter;

                    string adaptedName = AdaptName(namedType->GetName());

                    SrcPrint(2, 
                            "staticDesc._choiceList.push_back(%s::"
                            "Get%sStaticDescription());\n",
                            elementTypeName.c_str(),
                            adaptedName.c_str());
                }
            }
        }

        break;

        case TYPE_SEQUENCE_OF:
        {
            // TODO: check if compiler should reapply sub-typing accross
            // references.

            SequenceOfType* sequenceOfType =
                static_cast<SequenceOfType*> (baseType);

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseType);

            GenerateSetClauseSizeInstructions();

            PopContext();
            SetLevel(GetLevel() + 1);

            Type* type = sequenceOfType->GetSequenceOfType();

            string typeName = AdaptName(GetGeneratedTypeName(type));

            if (IsAsnTypeName(typeName))
            {
                typeName.erase(0, 3);   // Remove "Asn" prefix.

                for (size_t i = 0; i < typeName.size(); i++)
                {
                    typeName[i] = toupper(typeName[i]);
                }
            }

            SrcPrint(2,
                    "staticDesc._element = %s::Get%sStaticDescription();\n",
                    elementTypeName.c_str(),
                    typeName.c_str());
        }

        break;

        case TYPE_SET_OF:
        {
            // TODO: check if compiler should reapply sub-typing accross
            // references.

            SetOfType* setOfType = 
                static_cast<SetOfType*> (baseType);

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseType);

            GenerateSetClauseSizeInstructions();

            PopContext();
            SetLevel(GetLevel() + 1);

            Type* type = setOfType->GetSetOfType();

            string typeName = AdaptName(GetGeneratedTypeName(type));

            if (IsAsnTypeName(typeName))
            {
                typeName.erase(0, 3);   // Remove "Asn" prefix.

                for (size_t i = 0; i < typeName.size(); i++)
                {
                    typeName[i] = toupper(typeName[i]);
                }
            }

            SrcPrint(2,
                    "staticDesc._element = %s::Get%sStaticDescription();\n",
                    elementTypeName.c_str(),
                    typeName.c_str());
        }

        break;

        case TYPE_SELECTION:

            break;

        case TYPE_BOOLEAN:

            break;

        case TYPE_INTEGER:

            break;
 
        case TYPE_BIT_STRING:

            // TODO: check if compiler should reapply sub-typing accross
            // references.

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseType);

            GenerateSetClauseSizeInstructions();

            PopContext();
            SetLevel(GetLevel() + 1);

            break;

        case TYPE_OCTET_STRING:

            // TODO: check if compiler should reapply sub-typing accross
            // references.

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseType);

            GenerateSetClauseSizeInstructions();

            PopContext();
            SetLevel(GetLevel() + 1);

            break;

        case TYPE_BASE_STRING:

            // TODO: check if compiler should reapply sub-typing accross
            // references.

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseType);

            GenerateSetClauseSizeInstructions();

            PopContext();
            SetLevel(GetLevel() + 1);

            break;

        case TYPE_NULL:

            break;

        case TYPE_OBJECT_IDENTIFIER:

            break;

        case TYPE_REAL:

            break;

        case TYPE_ENUMERATED:
        {
            EnumeratedType* enumeratedType =
                static_cast<EnumeratedType*> (baseType);

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseType);

            GenerateSetClauseExtensibleInstructions();

            PopContext();
            SetLevel(GetLevel() + 1);

            NamedNumberList* namedNumberList = enumeratedType->GetNamedNumberList();

            NamedNumberList::iterator iter;

            for (iter = namedNumberList->begin();
                 iter != namedNumberList->end();
                 iter++)
            {
                NamedNumber* namedNumber = *iter;

                long value = namedNumber->GetNumber();

                SrcPrint(2,
                        "staticDesc._valueSet.insert(%d);\n",
                        value);
            }

            SrcPrint(2,
                "static AsnDescEnumerated::NamedNumber namedNumberList[] = {");

            for (iter = namedNumberList->begin();
                 iter != namedNumberList->end();
                 iter++)
            {
                NamedNumber* namedNumber = *iter;

                const string& name = namedNumber->GetName();
                long value = namedNumber->GetNumber();

                SrcPrint(0, "{\"%s\", %d}, ", name.c_str(), value);
            }

            SrcPrint(0,
                    "{NULL, 0}};\n");

            SrcPrint(2,
                    "staticDesc.SetNamedNumberList(namedNumberList);\n");
        }

        break;

        case TYPE_ANY:
        case TYPE_ANY_DEFINED_BY:

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseType);

            GenerateSetClauseAnyTagInstructions();

            PopContext();
            SetLevel(GetLevel() + 1);

            break;

        default:
        {
            bool must_not_be_reached = false;
            ASSERT(must_not_be_reached);
        }
    }

    GenerateSetNamedTypeNameInstructions();

    SrcPrint(2, 
            "result = &staticDesc;\n");
    SrcPrint(2, 
            "initialized = true;\n");
    SrcPrint(2, 
            "Asn::Unlock();\n");

    if (_generateAssertionCode)
    {
        SrcPrint(2, 
                "ITS_ENSURE(result != NULL);\n");
    }

    SrcPrint(2, 
            "return result;\n");
    SrcPrint(1, 
            "}\n");
    SrcPrint(0, 
            "}\n");
    SrcNewLine();

    PopContext();

    // Do not want to change the level.
    SetLevel(GetLevel() + 1);
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCppVisitor::HdrPrint(int n, const char* format, ...)
{
    HdrIndent(n);

    static char buf[MaxBufferSize];

    va_list alist;

    va_start(alist, format);

    vsprintf(buf, format, alist);

    hdr.append(buf);

    va_end(alist);
}


void 
GenerateCppVisitor::SrcPrint(int n, const char* format, ...)
{
    SrcIndent(n);

    static char buf[MaxBufferSize];

    va_list alist;

    va_start(alist, format);

    vsprintf(buf, format, alist);

    src.append(buf);

    va_end(alist);
}


string 
GenerateCppVisitor::GetVarArgsString(const char* format, ...)
{
    static char buf[MaxBufferSize];

    string result;

    va_list alist;

    va_start(alist, format);

    vsprintf(buf, format, alist);

    result.append(buf);

    va_end(alist);

    return result;
}


string 
GenerateCppVisitor::GetLevelIndent(int level)
{
    string result = "";

    result.reserve(SIZE_TINY);

    for (int i = 0; i < level; i++)
    {
        result.append("    ");
    }

    return result;
}


string 
GenerateCppVisitor::GetHdrHeaderString()
{
    string result;

    result.reserve(SIZE_MEDIUM);

    string moduleName = module->GetName();

    if (cppModuleNameG != "")
    {
        moduleName = cppModuleNameG;
    }

    string moduleNameAdapted = AdaptNameToUppercase(moduleName);

    string typeNameAdapted = AdaptNameToUppercase(GetCurrentTypeName());

    if (typeNameAdapted.size() == 0 || typeNameAdapted[0] != '_')
    {
        typeNameAdapted.insert(0, "_");
    }

    result.append(GetStandardHeaderString());
    result.append(GetVarArgsString("#if !defined(_%s%s_H_)\n",
                                   moduleNameAdapted.c_str(),
                                   typeNameAdapted.c_str()));
    result.append(GetVarArgsString("#define _%s%s_H_\n",
                                   moduleNameAdapted.c_str(),
                                   typeNameAdapted.c_str()));
    result.append("\n");
    result.append("#if _MSC_VER >= 1000\n");
    result.append("#pragma once\n");
    result.append("#endif // _MSC_VER >= 1000\n");
    result.append("\n");
    result.append("#include <Asn.h>\n");
    result.append("#include <AsnObject.h>\n");
    result.append("#include <AsnDescObject.h>\n");
    result.append("#include <AsnError.h>\n");
    result.append("\n");
    result.append(GetBasicIncludeListString());
    result.append(GetReferenceIncludeListString());
    result.append("\n");
    result.append("\n");

    if (_generateNamespaceDefineCode)
    {
        result.append("#if defined(ITS_NAMESPACE)\n");
    }

    if (cppNamespaceG == "")
    {
        result.append("namespace its {\n");
    }
    else
    {
        result.append(GetVarArgsString("namespace %s {\n",
                                       cppNamespaceG.c_str()));
    }

    if (_generateNamespaceDefineCode)
    {
        result.append("{\n");
        result.append("#endif // defined(ITS_NAMESPACE)\n");  
    }

    result.append("\n");

    return result;
}


string 
GenerateCppVisitor::GetHdrEndString()
{
    string result;

    result.reserve(SIZE_SMALL);

    string moduleName = module->GetName();

    if (cppModuleNameG != "")
    {
        moduleName = cppModuleNameG;
    }

    string moduleNameAdapted = AdaptNameToUppercase(moduleName);
    string typeNameAdapted = AdaptNameToUppercase(GetCurrentTypeName());

    if (typeNameAdapted.size() == 0 || typeNameAdapted[0] != '_')
    {
        typeNameAdapted.insert(0, "_");
    }

    result.append("\n");
    result.append("\n");

    if (_generateNamespaceDefineCode)
    {
        result.append("#if defined(ITS_NAMESPACE)\n");
    }

    result.append("} // namespace.\n");

    if (_generateNamespaceDefineCode)
    {
        result.append("#endif // defined(ITS_NAMESPACE)\n");
    }

    result.append("\n");
    result.append(GetVarArgsString("#endif    // !defined(_%s%s_H_)\n",
                                   moduleNameAdapted.c_str(),
                                   typeNameAdapted.c_str()));
    result.append("\n");

    return result;
}


string 
GenerateCppVisitor::GetSrcHeaderString()
{
    string result;

    result.reserve(SIZE_TINY);

    string moduleName = module->GetName();

    if (cppModuleNameG != "")
    {
        moduleName = cppModuleNameG;
    }

    string fileNameCore = "";


    if (!IsAsnUsefulTypeName(GetCurrentTypeName()))
    {
        if (!bCppFileNamesNoPrefixG)
        {
            fileNameCore.append(moduleName);
            fileNameCore.append("_");
        }
        else
        {
            // Do nothing => backward compatibility.
        }
    }
    else
    {
        // Do nothing.
    }

    fileNameCore.append(AdaptName(GetCurrentTypeName()));

    if (!IsAsnUsefulTypeName(GetCurrentTypeName()))
    {
        if (!bCppFileNamesMixedCaseG)
        {
            fileNameCore = AdaptNameToLowercase(fileNameCore);
        }
        else
        {
            // Do nothing => backward compatibility.
        }
    }
    else
    {
        // Do nothing.
    }

    result.append(GetStandardHeaderString());
    result.append(
            GetVarArgsString(
                    "#include <%s.h>\n", 
                    fileNameCore.c_str()));
    result.append("\n");
    result.append(GetBasicDescIncludeListString());
    result.append("\n");

    if (_generateNamespaceDefineCode)
    {
        result.append("#if defined(ITS_NAMESPACE)\n");
    }

    if (cppNamespaceG == "")
    {
        result.append("using namespace its;\n");
    }
    else
    {
        result.append("using namespace its;\n");

        if (cppNamespaceG != "its")
        {
            result.append(
                GetVarArgsString(
                    "using namespace %s;\n",
                    cppNamespaceG.c_str()));
        }
    }

    if (_generateNamespaceDefineCode)
    {
        result.append("#endif // defined(ITS_NAMESPACE)\n"); 
    }

    result.append("\n");

    return result;
}


string 
GenerateCppVisitor::GetSrcEndString()
{
    string result;

    result.reserve(SIZE_TINY);

    result.append("\n");
    result.append("\n");
    result.append("\n");
    result.append("\n");

    return result;
}


string 
GenerateCppVisitor::GetStandardHeaderString()
{
    string result;

    result.reserve(SIZE_SMALL);

    result.append("//\n");
    result.append(
        "// Generated by IntelliAsnCC ASN.1 compiler (C, C++, Java).\n");
    result.append("//\n");
    result.append("// Do not edit!\n");
    result.append("//\n");
    result.append("//\n");
    result.append("//\n");
    result.append(
        "// (C) 2000, 2001 IntelliNet Technologies Inc. All Rights Reserved.\n");
    result.append("//\n");
    result.append("//\n");
    result.append("\n");
    result.append("\n");

    return result;
}


string 
GenerateCppVisitor::GetScopeString()
{
    list<string> typeNameList(typeNameStack);

    typeNameList.push_front(GetCurrentTypeName());

    typeNameList.reverse();

    string result;

    for (list<string>::iterator iter = typeNameList.begin();
         iter != typeNameList.end();
         iter++)
    {
        string str = *iter;

        result.append(AdaptName(str));
        result.append("::");
    }

    return result;
}


string 
GenerateCppVisitor::GetBasicIncludeListString()
{
    string result;

    result.reserve(SIZE_SMALL);

    for (list<string>::iterator iter = basicIncludeList.begin();
         iter != basicIncludeList.end();
         iter++)
    {
        string str = *iter;

        result.append("#include <");
        result.append(AdaptName(str));
        result.append(".h>\n");
    }

    if (!basicIncludeList.empty())
    {
        result.append("\n");
    }

    return result;
}


string 
GenerateCppVisitor::GetBasicDescIncludeListString()
{
    string result;

    result.reserve(SIZE_SMALL);

    for (list<string>::iterator iter = basicIncludeList.begin();
         iter != basicIncludeList.end();
         iter++)
    {
        string str = *iter;

        result.append("#include <");

        string asnDescTypeName;
        string asnTypeName = AdaptName(str);

        if (asnTypeName.substr(0, 3) == "Asn")
        {
            asnDescTypeName = asnTypeName;
            asnDescTypeName.insert(3, "Desc");
        }
        else
        {
            asnDescTypeName = "AsnDescUnknown";
        }

        result.append(asnDescTypeName);
        result.append(".h>\n");
    }

    if (!basicIncludeList.empty())
    {
        result.append("\n");
    }

    return result;
}


string 
GenerateCppVisitor::GetReferenceIncludeListString()
{
    string result;

    result.reserve(SIZE_SMALL);

    string moduleName = module->GetName();

    if (cppModuleNameG != "")
    {
        moduleName = cppModuleNameG;
    }

    for (list<string>::iterator iter = referenceIncludeList.begin();
         iter != referenceIncludeList.end();
         iter++)
    {
        string str = *iter;

        string fileNameCore = "";

        if (!IsAsnUsefulTypeName(str))
        {
            if (!bCppFileNamesNoPrefixG)
            {
                fileNameCore.append(moduleName);
                fileNameCore.append("_");
            }
            else
            {
                // Do nothing => backward compatibility.
            }
        }
        else
        {
            // Do nothing.
        }

        fileNameCore.append(AdaptName(str));

        if (!IsAsnUsefulTypeName(str))
        {
            if (!bCppFileNamesMixedCaseG)
            {
                fileNameCore = AdaptNameToLowercase(fileNameCore);
            }
            else
            {
                // Do nothing => backward compatibility.
            }
        }
        else
        {
            // Do nothing.
        }

        result.append("#include <");
        result.append(fileNameCore);
        result.append(".h>\n");
    }

    if (!referenceIncludeList.empty())
    {
        result.append("\n");
    }

    return result;
}


string 
GenerateCppVisitor::GetTypedefListString()
{
    string result;

    result.reserve(SIZE_SMALL);

    for (list<string>::iterator iter = typedefList.begin();
         iter != typedefList.end();
         iter++)
    {
        result += "\n";
        result += *iter;
        result += "\n";
    }

    return result;
}


//
// Return generated type name (e.g. "AsnSequence", "AsnInteger") or name if
// DefinedType.
//

string 
GenerateCppVisitor::GetGeneratedTypeName(Type* type)
{
    REQUIRE(type != NULL);

    switch(type->GetType())
    {
        case TYPE_DEFINED:
            {
                DefinedType* definedType =
                    static_cast<DefinedType*> (type);

                return definedType->GetName();
            }

        case TYPE_SEQUENCE:
            return "AsnSequence";

        case TYPE_SET:
            return "AsnSet";

        case TYPE_CHOICE:
            return "AsnChoice";

        case TYPE_SEQUENCE_OF:
            return "AsnSequenceOf";

        case TYPE_SET_OF:
            return "AsnSetOf";

        case TYPE_SELECTION:
            return "AsnTypeSelection";

        case TYPE_ANY_DEFINED_BY:
            return "AsnAny";

        case TYPE_BOOLEAN:
            return "AsnBoolean";

        case TYPE_INTEGER:
            return "AsnInteger";

        case TYPE_BIT_STRING:
            return "AsnBitString";

        case TYPE_OCTET_STRING:
            return "AsnOctetString";

        case TYPE_BASE_STRING:
            return "AsnBaseString";

        case TYPE_NULL:
            return "AsnNull";

        case TYPE_OBJECT_IDENTIFIER:
            return "AsnObjectIdentifier";

        case TYPE_REAL:
            return "AsnReal";

        case TYPE_ENUMERATED:
            return "AsnEnumerated";

        case TYPE_ANY:
            return "AsnAny";

        default:
            {
                bool must_not_be_reached = false;
                ASSERT(must_not_be_reached);

                return "AsnNotReached"; // Not reached.
            }
    }
}


//
// Return generated base type name (e.g. "AsnSequence", "AsnInteger") or name if
// DefinedType (should not be).
//

string 
GenerateCppVisitor::GetGeneratedBaseTypeName(Type* type)
{
    REQUIRE(type != NULL);

    Type* baseType = type->GetBaseType();

    return GetGeneratedTypeName(baseType);
} 


//
//  Returns Defined Type name if Defined Type or name if not (must be a named
//  type).
//

string
GenerateCppVisitor::GetGeneratedElementTypeName(Type* type)
{
    REQUIRE(type != NULL);
    REQUIRE(type->IsNamed());

    if (type->GetType() == TYPE_DEFINED)
    {
        DefinedType* definedType = static_cast<DefinedType*> (type);

        return definedType->GetName();
    }
    else
    {
        return type->GetName();
    }
}


//
//  Return "its::" or "" according to namespace option cppNamespaceG.
//

string
GenerateCppVisitor::GetItsNamespaceScope()
{
    if (cppNamespaceG == "")
    {
        return "";
    }
    else
    {
        return "its::";
    }
}


//
// Return true if ASN type name.
//

bool 
GenerateCppVisitor::IsAsnTypeName(const string& typeName)
{
    if (typeName == "AsnAny"                ||
        typeName == "AsnBitString"          ||
        typeName == "AsnBoolean"            ||
        typeName == "AsnChoice"             ||
        typeName == "AsnEnumerated"         ||
        typeName == "AsnInteger"            ||
        typeName == "AsnNull"               ||
        typeName == "AsnObjectIdentifier"   ||
        typeName == "AsnOctetString"        ||
        typeName == "AsnBaseString"         ||
        typeName == "AsnReal"               ||
        typeName == "AsnSequence"           ||
        typeName == "AsnSequenceOf"         ||
        typeName == "AsnSet"                ||
        typeName == "AsnSetOf"                )
    {
        return true;
    }
    else
    {
        return false;
    }
}


//
//  Return true is ASN-USEFUL type name.
//

bool 
GenerateCppVisitor::IsAsnUsefulTypeName(const string& typeName)
{
    if (typeName == "CHARACTER STRING"  ||
        typeName == "EMBEDDED PDV"      ||
        typeName == "ObjectDescriptor"  ||
        typeName == "BMPString"         ||
        typeName == "NumericString"     ||
        typeName == "PrintableString"   ||
        typeName == "TeletexString"     ||
        typeName == "T61String"         ||
        typeName == "VideotexString"    ||
        typeName == "IA5String"         ||
        typeName == "GraphicString"     ||
        typeName == "VisibleString"     ||
        typeName == "ISO646String"      ||
        typeName == "GeneralString"     ||
        typeName == "UniversalString"   ||
        typeName == "UTF8String"        ||
        typeName == "UTCTime"           ||
        typeName == "GeneralizedTime"   ||
        typeName == "EXTERNAL"            )
    {
        return true;
    }
    else
    {
        return false;
    }
}


void 
GenerateCppVisitor::InsertOnceBasicIncludeList(const string& str)
{
    for (list<string>::iterator iter = basicIncludeList.begin();
         iter != basicIncludeList.end();
         iter++)
    { 
        if (str == *iter)
        {
            return;
        }
    }

    basicIncludeList.push_back(str);
}


void 
GenerateCppVisitor::InsertOnceReferenceIncludeList(const string& str)
{
    for (list<string>::iterator iter = referenceIncludeList.begin();
         iter != referenceIncludeList.end();
         iter++)
    { 
        if (str == *iter)
        {
            return;
        }
    }

    referenceIncludeList.push_back(str);
}


void 
GenerateCppVisitor::InsertOnceTypedefList(const string& str)
{
    for (list<string>::iterator iter = typedefList.begin();
         iter != typedefList.end();
         iter++)
    { 
        if (str == *iter)
        {
            return;
        }
    }

    typedefList.push_back(str);
}


void 
GenerateCppVisitor::PushContext()
{
    typeStack.push_front(currentType);
    typeNameStack.push_front(currentTypeName);

    level = level + 1;
}


void 
GenerateCppVisitor::PopContext()
{
    currentType     = typeStack.front();
    currentTypeName = typeNameStack.front();

    typeStack.pop_front();
    typeNameStack.pop_front();

    level = level - 1;
}

std::string
GenerateCppVisitor::GetProtocol(std::string str)
{
    std::string ret = "";
   
    if ((str == "CAP-V2") ||
        (str == "CAP-V3") ||
        (str == "CAP-V4") ||
        (str == "CAP-V1")) 
    {
        ret = "ITS_LIC_CAP_CAMEL";
    }
    else if ((str == "IS41") ||
             (str == "AS-41D")  ||
             (str == "AS-41E"))  
         
    {
        ret = "ITS_LIC_CAP_IS41";
    }
    else if ((str == "AIN") ||
        (str == "AIN-02"))
    {
        ret = "ITS_LIC_CAP_AIN";
    }
    else if ((str == "GSMMAP") ||
        (str == "MAP-V1") ||
        (str == "MAP-V2") ||
        (str == "MAP-V3") ||
        (str == "MAP-V4") ||
        (str == "MAP-V5") ||
        (str == "MAP-V6") ||
        (str == "MAP-V7") ||
        (str == "MAP-V8"))
    {
        ret = "ITS_LIC_CAP_GSMMAP";
    }
    else if ((str == "INAP") ||
        (str == "INAP-CHINA-CS1") ||
        (str == "INAP-CS1") ||
        (str == "INAP-NOKIA-CS1") ||
        (str == "INAP-CS2") ||
        (str == "INAP-NOKIA-CS1") ||
        (str == "INAP-ETSI-CS1"))
    {
        ret = "ITS_LIC_CAP_INAP";
    }
    else if (str == "IS-826")
    {
        ret = "ITS_LIC_CAP_IS826";
    }
    else if (str == "JSTD-36")
    {
        ret = "ITS_LIC_CAP_JSTD";
    }
    else if (str == "LIDB")
    {
        ret = "ITS_LIC_CAP_LIDB";
    }
    else if (str == "TAP3")
    {
        ret = "ITS_LIC_CAP_TAP";
    }
    else if (str == "WIN")
    {
        ret = "ITS_LIC_CAP_WIN";
    }
    
    return ret;
}

void
GenerateCppVisitor::GenerateLicenseCheck()
{
    std::string str = GetProtocol(module->GetName());

    if (str != "")
    {
        SrcPrint(2,"if (CheckLicense(%s) != ITS_TRUE)\n",str.c_str());
        SrcPrint(2,"{\n");
        SrcPrint(3,"Asn::Unlock();\n");
        SrcPrint(3,"exit(0);\n");
        SrcPrint(2,"}\n\n");
    }
    else
    {
        if (module->GetName() != "ASN-USEFUL")
        {
            cerr << "\nGenerating ASN.1 Files without Intellinet License check.\n";
            cerr << "If License check required add the module name(Available in the asn file)";
            cerr << "and the license string (e.g.ITS_LIC_CAP_WIN) in the \n";
            cerr << "GenerateCppVisitor::GetProtocol function\n\n";
        }
    }
}
