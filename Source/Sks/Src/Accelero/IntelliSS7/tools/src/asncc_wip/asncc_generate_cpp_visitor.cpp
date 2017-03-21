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
//  ID: $Id: asncc_generate_cpp_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>

#include <asncc_generate_cpp_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)



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
    if (!typeDef->IsCommon() || 
        commonTypeDefTable.find(typeDef->GetDefinedName()) == 
        commonTypeDefTable.end())
    {
        GetHdr().insert(0, GetHdrHeaderString());
        GetHdr().append(GetHdrEndString());

        GetSrc().insert(0, GetSrcHeaderString());
        GetSrc().append(GetSrcEndString());

        string moduleName = module->GetName();

        if (module->GetSpecifiedName() != "")
        {
            moduleName = module->GetSpecifiedName();
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
                if (!typeDef->IsCommon())
                {
                    fileNameCore.append(moduleName);
                    fileNameCore.append("_");
                }
                else
                {
                    fileNameCore.append(cppMergeModuleNameG);
                    fileNameCore.append("_");
                }
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

        if (typeDef->IsCommon())
        {
            // Insert into common type definition table. 

            commonTypeDefTable.insert(
                TypeDefTable::value_type(
                    typeDef->GetDefinedName(), 
                    typeDef));
        }
    }
    else
    {
        // Nothing to do.
    }

    if (typeDef->IsCommon() && bCppMergeGenerateAllHeadersG)
    {
        // Generation of a single header file that contains typedef to common
        // type (according to namespace). To allow backward compatibility 
        // between merged and non-merged generated code.

        // Cleaning of contents (header only).

        GetHdr().erase(GetHdr().begin(), GetHdr().end());

        GetHdr().append(GetStandardHeaderString());

        string moduleName = module->GetName();

        if (module->GetSpecifiedName() != "")
        {
            moduleName = module->GetSpecifiedName();
        }

        string moduleNameAdaptedToUppercase = 
            AdaptNameToUppercase(moduleName);
        string typeNameAdaptedToUppercase = 
            AdaptNameToUppercase(GetCurrentTypeName());

        if (typeNameAdaptedToUppercase.size() == 0 || 
            typeNameAdaptedToUppercase[0] != '_')
        {
            typeNameAdaptedToUppercase.insert(0, "_");
        }

        HdrPrint(0,
            "#if !defined(_%s%s_H_)\n",
            moduleNameAdaptedToUppercase.c_str(),
            typeNameAdaptedToUppercase.c_str());
        HdrPrint(0,
            "#define _%s%s_H_\n",
            moduleNameAdaptedToUppercase.c_str(),
            typeNameAdaptedToUppercase.c_str());
        HdrNewLine();

        moduleName = cppMergeModuleNameG;

        string fileNameCore = "";

        fileNameCore.append(moduleName);
        fileNameCore.append("_");

        fileNameCore.append(AdaptName(GetCurrentTypeName()));

        fileNameCore = AdaptNameToLowercase(fileNameCore);

        HdrPrint(0,
            "#include <%s.h>\n",
            fileNameCore.c_str());
        HdrNewLine();

        if (module->GetSpecifiedNamespace() == "")
        {
            HdrPrint(0,
                "namespace its {\n");
            HdrNewLine();
        }
        else
        {
            HdrPrint(0,
                "namespace %s {\n",
                module->GetSpecifiedNamespace().c_str());
            HdrNewLine();
        }

        string typeName = AdaptName(GetCurrentTypeName());

        HdrPrint(0,
            "typedef %s::%s %s;\n",
            cppMergeNamespaceG.c_str(),
            typeName.c_str(),
            typeName.c_str());
        HdrNewLine();

        HdrPrint(0,
            "} // Namespace.\n");
        HdrNewLine();
        HdrPrint(0,
            "#endif // !defined(_%s%s_H_)\n",
            moduleNameAdaptedToUppercase.c_str(),
            typeNameAdaptedToUppercase.c_str());
        HdrNewLine();

        moduleName = module->GetName();

        if (module->GetSpecifiedName() != "")
        {
            moduleName = module->GetSpecifiedName();
        }

        string directoryName    = "";
        fileNameCore            = "";

        if (bModuleDirectoryG)
        {
            directoryName = AdaptNameToLowercase(moduleName);
        }

        fileNameCore.append(moduleName);
        fileNameCore.append("_");

        fileNameCore.append(AdaptName(GetCurrentTypeName()));

        fileNameCore = AdaptNameToLowercase(fileNameCore);

        WriteTextToFile(directoryName,
                        fileNameCore,
                        "h",
                        GetHdr());
    }
    else
    {
        //  Nothing to do.
    }
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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnBitString(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(const std::vector<bool>& array);\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(const std::vector<bool>& array) : "
            "AsnBitString(array, false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : AsnBitString(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnBitString(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnBitString(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam, "
            "const std::vector<bool>& array);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam, "
            "const std::vector<bool>& array) : "
            "AsnBitString(descriptionParam, array)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescBitString");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseSizeInstructions();

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
                "{ return %d < Size(); }\n", 
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
            "%s(bool valueParam = false);\n", 
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(bool valueParam) : "
            "AsnBoolean(valueParam, false)\n", 
            GetScopeString().c_str(), 
            typeName.c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1, 
            "%s(%sOctets& octets);\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(Octets& octets) : "
            "AsnBoolean(false, false)\n", 
            GetScopeString().c_str(), 
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1, 
            "%s(const %s& rhs);\n", 
            typeName.c_str(), 
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(const %s& rhs) : AsnBoolean(rhs)\n", 
            GetScopeString().c_str(), 
            typeName.c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* descriptionParam);\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnBoolean(descriptionParam)\n", 
            GetScopeString().c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* descriptionParam, bool valueParam);\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(AsnDescObject* descriptionParam, bool valueParam) "
            ": AsnBoolean(descriptionParam, valueParam)\n", 
            GetScopeString().c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                typeName, 
                                                "AsnDescBoolean");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnChoice(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,             
            "%s%s(Octets& octets) : AsnChoice(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnChoice(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnChoice(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam, %sAsnObject* choiceParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam, AsnObject* choiceParam) :"
            " AsnChoice(descriptionParam, choiceParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescChoice");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

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
                    "staticDesc.AddChoice(Get%sStaticDescription());\n",
                    adaptedName.c_str());
        }

        if (!(typeList->empty()))
        {
            SrcNewLine();
        }
    }

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

            string commonNamespaceScope = "";

            if (IsCommonType(namedType) && !IsCommonType(choiceType))
            {
                commonNamespaceScope = cppMergeNamespaceG + "::";
            }

            if (IsAsnTypeName(adaptedGenTypeName))
            {
                InsertOnceBasicIncludeList(adaptedGenTypeName);
            }
            else
            {
                if (!IsCommonType(namedType))
                {
                    InsertOnceReferenceIncludeList(adaptedGenTypeName);
                }
                else
                {
                    InsertOnceReferenceIncludeList("@" + adaptedGenTypeName);
                }
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
                    "void SetChoice%s(%s%s* choiceParam);\n",
                    adaptedName.c_str(),
                    commonNamespaceScope.c_str(),
                    adaptedElementTypeName.c_str());
            HdrNewLine();

            SrcPrint(0,
                    "void %sSetChoice%s(%s* choiceParam)\n",
                    GetScopeString().c_str(),
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str());
            SrcPrint(0,
                    "{\n");
            SrcPrint(1,
                    "ITS_THROW_REQUIRE(choiceParam != NULL);\n");
            SrcNewLine();
            SrcPrint(1,
                    "choiceParam->AsnObject::SetDescription"
                    "(Get%sStaticDescription());\n",
                    adaptedName.c_str());
            SrcNewLine();
            SrcPrint(1,
                    "SetChoice(choiceParam);\n");
            SrcPrint(0,
                    "}\n");
            SrcNewLine();

            HdrPrint(1,
                    "void SetChoice%s(const %s%s& choiceParam);\n",
                    adaptedName.c_str(),
                    commonNamespaceScope.c_str(),
                    adaptedElementTypeName.c_str());
            HdrNewLine();

            SrcPrint(0,
                    "void %sSetChoice%s(const %s& choiceParam)\n",
                    GetScopeString().c_str(),
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str());        
            SrcPrint(0,
                    "{\n");
            SrcPrint(1,
                    "AsnObject& asnObject = const_cast<%s&>(choiceParam);\n",
                    adaptedElementTypeName.c_str()); 
            SrcNewLine();
            SrcPrint(1,
                    "asnObject.SetDescription(Get%sStaticDescription());\n",
                    adaptedName.c_str());
            SrcNewLine();
            SrcPrint(1,
                    "SetChoice(choiceParam);\n");
            SrcPrint(0,
                    "}\n");
            SrcNewLine();

            HdrPrint(1,
                    "bool Choice%s() const;\n",
                    adaptedName.c_str());
            HdrNewLine();

            SrcPrint(0,
                    "bool %sChoice%s() const\n",
                    GetScopeString().c_str(),
                    adaptedName.c_str());            
            SrcPrint(0,
                    "{\n");
            SrcPrint(1,
                    "return Contains(Get%sStaticDescription()->"
                    "TagIdentity());\n",
                    adaptedName.c_str());
            SrcPrint(0,
                    "}\n");
            SrcNewLine();


            HdrPrint(1,
                    "const %s%s& GetChoice%s() const;\n",
                    commonNamespaceScope.c_str(),
                    adaptedElementTypeName.c_str(),
                    adaptedName.c_str());
            HdrNewLine();

            if (namedType->GetType() == TYPE_DEFINED)
            {
                SrcPrint(0,
                        "const %s& %sGetChoice%s() const\n",
                        adaptedElementTypeName.c_str(),
                        GetScopeString().c_str(),
                        adaptedName.c_str());
            }
            else // Nested type.
            {
                SrcPrint(0,
                        "const %s%s& %sGetChoice%s() const\n",
                        GetScopeString().c_str(),
                        adaptedElementTypeName.c_str(),
                        GetScopeString().c_str(),
                        adaptedName.c_str());
            }

            SrcPrint(0,
                    "{\n");
            SrcPrint(1,
                    "ITS_THROW_REQUIRE(Choice%s());\n",
                    adaptedName.c_str());
            SrcNewLine();
            SrcPrint(1,
                    "return static_cast<const %s&> (GetChoice());\n",
                    adaptedElementTypeName.c_str());
            SrcPrint(0,
                    "}\n");
            SrcNewLine();
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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnEnumerated(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1, 
            "%s(long valueParam);\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(long valueParam) : "
            "AsnEnumerated(valueParam, false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : AsnEnumerated(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnEnumerated(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnEnumerated(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam, long valueParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam, long valueParam) : "
            "AsnEnumerated(descriptionParam, valueParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescEnumerated");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

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
                "staticDesc.Put(%d);\n",
                value);
    }

    if (!(namedNumberList->empty()))
    {
        SrcNewLine();
    }

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

        string definedName = AdaptName(namedNumber->GetName());

        long value = namedNumber->GetNumber();

        if (first)
        {
            first = false;

            SrcPrint(1, 
                    "if (valueName == \"%s\")\n", 
                    definedName.c_str());
        }
        else
        {
            SrcPrint(1, 
                    "else if (valueName == \"%s\")\n", 
                    definedName.c_str());
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
            "ITS_THROW_ASSERT(invalid_value_name);\n");
    SrcNewLine();
    SrcPrint(2, 
            "return 0;\n");
    SrcPrint(1, 
            "}\n");

    SrcPrint(0, 
            "}\n");
    SrcNewLine();

    HdrPrint(1, 
            "virtual std::string Get(long valueParam) const;\n");
    HdrNewLine();

    SrcPrint(0, 
            "std::string %sGet(long valueParam) const\n", GetScopeString().c_str());
    SrcPrint(0, 
            "{\n");

    namedNumberList = enumeratedType->GetNamedNumberList();

    first = true;

    for (iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string definedName = AdaptName(namedNumber->GetName());

        long value = namedNumber->GetNumber();

        if (first)
        {
            first = false;

            SrcPrint(1, 
                    "if (valueParam == %d)\n", 
                    value);
        }
        else
        {
            SrcPrint(1, 
                    "else if (valueParam == %d)\n", 
                    value);
        }

        SrcPrint(1, 
                "{\n");
        SrcPrint(2, 
                "return \"%s\";\n", 
                definedName.c_str());
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
            "ITS_THROW_ASSERT(invalid_value);\n");
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
                "{ value = %d; }\n", value);
        HdrNewLine();


        HdrPrint(1, 
                "bool Is%s() const\n", definedName.c_str());
        HdrPrint(1, 
                "{ return value == %d; }\n", value);
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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnInteger(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(long valueParam);\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(long valueParam) : "
            "AsnInteger(valueParam, false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : "
            "AsnInteger(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnInteger(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnInteger(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam, long valueParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam, long valueParam) : "
            "AsnInteger(descriptionParam, valueParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescInteger");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnObjectIdentifier(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(const std::vector<long>& array);\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(const std::vector<long>& array) : "
            "AsnObjectIdentifier(array, false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : "
            "AsnObjectIdentifier(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnObjectIdentifier(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnObjectIdentifier(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam, "
            "const std::vector<long>& array);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam, "
            "const std::vector<long>& array) : "
            "AsnObjectIdentifier(descriptionParam, array)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescObjectIdentifier");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnNull(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : AsnNull(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnNull(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnNull(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescNull");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnReal(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(double valueParam);\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(double valueParam) : "
            "AsnReal(valueParam, false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : AsnReal(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnReal(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnReal(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam, double valueParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam, double valueParam) : "
            "AsnReal(descriptionParam, valueParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescReal");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

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
            "%s();\n", 
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnSequence(%d, false)\n", 
            GetScopeString().c_str(), 
            typeName.c_str(), 
            sequenceSize);

    GenerateDefaultConstructorBody();

    HdrPrint(1, 
            "%s(%sOctets& octets);\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(Octets& octets) : "
            "AsnSequence(%d, false)\n", 
            GetScopeString().c_str(), 
            typeName.c_str(), 
            sequenceSize);

    GenerateDecodeConstructorBody();

    HdrPrint(1, 
            "%s(const %s& rhs);\n", 
            typeName.c_str(), 
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(const %s& rhs) : AsnSequence(rhs)\n", 
            GetScopeString().c_str(), 
            typeName.c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* descriptionParam);\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnSequence(%d, descriptionParam)\n", 
            GetScopeString().c_str(), 
            typeName.c_str(), 
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
                    "staticDesc.AddElement(%d, Get%sStaticDescription());\n",
                    index, 
                    adaptedName.c_str());

            index++;
        }

        if (!(typeList->empty()))
        {
            SrcNewLine();
        }
    }

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

            string commonNamespaceScope = "";

            if (IsCommonType(namedType) && !IsCommonType(sequenceType))
            {
                commonNamespaceScope = cppMergeNamespaceG + "::";
            }

            if (IsAsnTypeName(adaptedGenTypeName))
            {
                InsertOnceBasicIncludeList(adaptedGenTypeName);
            }
            else
            {
                if (!IsCommonType(namedType))
                {
                    InsertOnceReferenceIncludeList(adaptedGenTypeName);
                }
                else
                {
                    InsertOnceReferenceIncludeList("@" + adaptedGenTypeName);
                }
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
                    "void Set%s(%s%s* element);\n", 
                    adaptedName.c_str(), 
                    commonNamespaceScope.c_str(),
                    adaptedElementTypeName.c_str());
            HdrNewLine();

            SrcPrint(0, 
                    "void %sSet%s(%s* element)\n", 
                    GetScopeString().c_str(), 
                    adaptedName.c_str(), 
                    adaptedElementTypeName.c_str());        
            SrcPrint(0, 
                    "{\n");
            SrcPrint(1, 
                    "ITS_THROW_REQUIRE(element != NULL);\n");
            SrcNewLine();
            SrcPrint(1, 
                    "element->AsnObject::SetDescription"
                    "(Get%sStaticDescription());\n",
                    adaptedName.c_str());
            SrcNewLine();
            SrcPrint(1, 
                    "AddElement(%d, element);\n", 
                    index);
            SrcPrint(0, 
                    "}\n");
            SrcNewLine();

            HdrPrint(1, 
                    "void Set%s(const %s%s& element);\n", 
                    adaptedName.c_str(),
                    commonNamespaceScope.c_str(),
                    adaptedElementTypeName.c_str());
            HdrNewLine();

            SrcPrint(0, 
                    "void %sSet%s(const %s& element)\n", 
                    GetScopeString().c_str(), 
                    adaptedName.c_str(), 
                    adaptedElementTypeName.c_str());        
            SrcPrint(0, 
                    "{\n");
            SrcPrint(1, 
                    "AsnObject& asnObject = const_cast<%s&>(element);\n", 
                    adaptedElementTypeName.c_str()); 
            SrcNewLine();
            SrcPrint(1, 
                    "asnObject.SetDescription(Get%sStaticDescription());\n", 
                    adaptedName.c_str());
            SrcNewLine();
            SrcPrint(1, 
                    "AddElement(%d, element);\n", 
                    index);
            SrcPrint(0, 
                    "}\n");
            SrcNewLine();

            if (namedType->IsOptional())
            {
                HdrPrint(1, 
                        "bool Option%s() const;\n", 
                        adaptedName.c_str());
                HdrNewLine();

                SrcPrint(0, 
                        "bool %sOption%s() const\n", 
                        GetScopeString().c_str(), 
                        adaptedName.c_str());            
                SrcPrint(0, 
                        "{\n");
                SrcPrint(1, 
                        "return Contains(%d);\n", index);
                SrcPrint(0, 
                        "}\n");
                SrcNewLine();
            }

            HdrPrint(1, 
                    "const %s%s& Get%s() const;\n", 
                    commonNamespaceScope.c_str(),
                    adaptedElementTypeName.c_str(), 
                    adaptedName.c_str());
            HdrNewLine();

            if (namedType->GetType() == TYPE_DEFINED)
            {
                SrcPrint(0, 
                        "const %s& %sGet%s() const\n", 
                        adaptedElementTypeName.c_str(), 
                        GetScopeString().c_str(), 
                        adaptedName.c_str());        
            }
            else // Nested type.
            {
                SrcPrint(0, 
                        "const %s%s& %sGet%s() const\n", 
                        GetScopeString().c_str(),
                        adaptedElementTypeName.c_str(), 
                        GetScopeString().c_str(), 
                        adaptedName.c_str());        
            }

            SrcPrint(0, 
                    "{\n");

            if (namedType->IsOptional())
            {
            
                SrcPrint(1, 
                        "ITS_THROW_REQUIRE(Option%s());\n", 
                        adaptedName.c_str());
                SrcNewLine();
            }

            SrcPrint(1, 
                    "return static_cast<const %s&> (ElementAt(%d));\n",
                    adaptedElementTypeName.c_str(), 
                    index);
            SrcPrint(0, 
                    "}\n");
            SrcNewLine();

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

    string commonNamespaceScope = "";

    if (IsCommonType(type) && !IsCommonType(sequenceOfType))
    {
        commonNamespaceScope = cppMergeNamespaceG + "::";
    }

    if (IsAsnTypeName(eltTypeName))
    {
        InsertOnceBasicIncludeList(eltTypeName);
    }
    else
    {
        if (!IsCommonType(type))
        {
            InsertOnceReferenceIncludeList(eltTypeName);
        }
        else
        {
            InsertOnceReferenceIncludeList("@" + eltTypeName);
        }
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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s() : AsnSequenceOf(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody();

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : AsnSequenceOf(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnSequenceOf(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnSequenceOf(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescSequenceOf");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseSizeInstructions();

    SrcPrint(2,
            "staticDesc.SetElement(Get%sStaticDescription());\n",
            eltTypeName.c_str());
            
    SrcNewLine();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GenerateElementStaticDescription(type, eltTypeName);

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    HdrPrint(1,
            "void AddElement(%s%s* element);\n",
            commonNamespaceScope.c_str(),
            eltTypeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "void %sAddElement(%s* element)\n",
            GetScopeString().c_str(),
            eltTypeName.c_str());
    SrcPrint(0,
            "{\n");
    SrcPrint(1,
            "ITS_THROW_REQUIRE(element != NULL);\n");
    SrcNewLine();
    SrcPrint(1,
            "element->AsnObject::SetDescription"
            "(Get%sStaticDescription());\n",
            eltTypeName.c_str());
    SrcPrint(1,
            "AsnSequenceOf::AddElement(element);\n");
    SrcPrint(0,
            "}\n");
    SrcNewLine();

    HdrPrint(1,
            "void AddElement(const %s%s& element);\n", 
            commonNamespaceScope.c_str(),
            eltTypeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "void %sAddElement(const %s& element)\n",
            GetScopeString().c_str(),
            eltTypeName.c_str());
    SrcPrint(0,
            "{\n");
    SrcPrint(1, 
            "AsnObject& asnObject = const_cast<%s&>(element);\n",
            eltTypeName.c_str()); 
    SrcNewLine();
    SrcPrint(1, 
            "asnObject.SetDescription(Get%sStaticDescription());\n",
            eltTypeName.c_str());
    SrcNewLine();
    SrcPrint(1,
            "AsnSequenceOf::AddElement(element);\n");
    SrcPrint(0,
            "}\n");
    SrcNewLine();

    HdrPrint(1,
            "const %s%s& ElementAt(size_t index) const;\n",
            commonNamespaceScope.c_str(),
            eltTypeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "const %s%s& %sElementAt(size_t index) const\n",
            GetScopeString().c_str(),
            eltTypeName.c_str(),
            GetScopeString().c_str());
    SrcPrint(0,
            "{\n");
    SrcPrint(1,
            "return static_cast<const %s&> "
            "(AsnSequenceOf::ElementAt(index));\n",
            eltTypeName.c_str());
    SrcPrint(0,
            "}\n");
    SrcNewLine();

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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s() : AsnSet(%d, false)\n",
            GetScopeString().c_str(),
            typeName.c_str(),
            setSize);

    GenerateDefaultConstructorBody();

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : "
            "AsnSet(%d, false)\n",
            GetScopeString().c_str(),
            typeName.c_str(),
            setSize);

    GenerateDecodeConstructorBody();

    HdrPrint(1, 
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnSet(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnSet(%d, descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str(),
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
                    "staticDesc.AddElement(%d, Get%sStaticDescription());\n",
                    index,
                    adaptedName.c_str());

            index++;
        }

        if (!(typeList->empty()))
        {
            SrcNewLine();
        }
    }

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

            string commonNamespaceScope = "";

            if (IsCommonType(namedType) && !IsCommonType(setType))
            {
                commonNamespaceScope = cppMergeNamespaceG + "::";
            }

            if (IsAsnTypeName(adaptedGenTypeName))
            {
                InsertOnceBasicIncludeList(adaptedGenTypeName);
            }
            else
            {
                InsertOnceReferenceIncludeList("@" + adaptedGenTypeName);
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
                    "void Set%s(%s%s* element);\n",
                    adaptedName.c_str(),
                    commonNamespaceScope.c_str(),
                    adaptedElementTypeName.c_str());
            HdrNewLine();

            SrcPrint(0,
                    "void %sSet%s(%s* element)\n",
                    GetScopeString().c_str(),
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str());        
            SrcPrint(0,
                    "{\n");
            SrcPrint(1,
                    "ITS_THROW_REQUIRE(element != NULL);\n");
            SrcNewLine();
            SrcPrint(1,
                    "element->AsnObject::SetDescription"
                    "(Get%sStaticDescription());\n",
                    adaptedName.c_str());
            SrcNewLine();
            SrcPrint(1,
                    "AddElement(%d, element);\n",
                    index);
            SrcPrint(0,
                    "}\n");
            SrcNewLine();

            HdrPrint(1,
                    "void Set%s(const %s%s& element);\n",
                    adaptedName.c_str(),
                    commonNamespaceScope.c_str(),
                    adaptedElementTypeName.c_str());
            HdrNewLine();

            SrcPrint(0,
                    "void %sSet%s(const %s& element)\n",
                    GetScopeString().c_str(),
                    adaptedName.c_str(),
                    adaptedElementTypeName.c_str());        
            SrcPrint(0,
                    "{\n");
            SrcPrint(1,
                    "AsnObject& asnObject = const_cast<%s&>(element);\n",
                    adaptedElementTypeName.c_str()); 
            SrcNewLine();
            SrcPrint(1,
                    "asnObject.SetDescription(Get%sStaticDescription());\n",
                    adaptedName.c_str());
            SrcNewLine();
            SrcPrint(1,
                    "AddElement(%d, element);\n",
                    index);
            SrcPrint(0,
                    "}\n");
            SrcNewLine();

            if (namedType->IsOptional())
            {
                HdrPrint(1,
                        "bool Option%s() const;\n",
                        adaptedName.c_str());
                HdrNewLine();

                SrcPrint(0,
                        "bool %sOption%s() const\n",
                        GetScopeString().c_str(),
                        adaptedName.c_str());            
                SrcPrint(0,
                        "{\n");
                SrcPrint(1,
                        "return Contains(%d);\n",
                        index);
                SrcPrint(0,
                        "}\n");
                SrcNewLine();
            }

            HdrPrint(1,
                    "const %s%s& Get%s() const;\n",
                    commonNamespaceScope.c_str(),
                    adaptedElementTypeName.c_str(),
                    adaptedName.c_str());
            HdrNewLine();

            if (namedType->GetType() == TYPE_DEFINED)
            {
                SrcPrint(0,
                        "const %s& %sGet%s() const\n",
                        adaptedElementTypeName.c_str(),
                        GetScopeString().c_str(),
                        adaptedName.c_str());
            }
            else // Nested type.
            {
                SrcPrint(0,
                        "const %s%s& %sGet%s() const\n",
                        GetScopeString().c_str(),
                        adaptedElementTypeName.c_str(),
                        GetScopeString().c_str(),
                        adaptedName.c_str());
            }

            SrcPrint(0,
                    "{\n");

            if (namedType->IsOptional())
            {
            
                SrcPrint(1,
                        "ITS_THROW_REQUIRE(Option%s());\n",
                        adaptedName.c_str());
                SrcNewLine();
            }

            SrcPrint(1,
                    "return static_cast<const %s&> (ElementAt(%d));\n",
                    adaptedElementTypeName.c_str(),
                    index);
            SrcPrint(0,
                    "}\n");
            SrcNewLine();

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

    string commonNamespaceScope = "";

    if (IsCommonType(type) && !IsCommonType(setOfType))
    {
        commonNamespaceScope = cppMergeNamespaceG + "::";
    }

    if (IsAsnTypeName(eltTypeName))
    {
        InsertOnceBasicIncludeList(eltTypeName);
    }
    else
    {
        if (!IsCommonType(type))
        {
            InsertOnceReferenceIncludeList(eltTypeName);
        }
        else
        {
            InsertOnceReferenceIncludeList("@" + eltTypeName);
        }
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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s() : AsnSetOf(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody();

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : AsnSetOf(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnSetOf(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnSetOf(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescSetOf");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseSizeInstructions();

    SrcPrint(2,
            "staticDesc.SetElement(Get%sStaticDescription());\n",
            eltTypeName.c_str());
            
    SrcNewLine();

    GenerateGetStaticDescriptionMemberFunctionEndPart();

    GenerateElementStaticDescription(type, eltTypeName);

    GeneratePublicScope();

    GenerateDestructor(typeName);

    GenerateCloneMemberFunction(typeName);

    GenerateGetNameMemberFunction(typeName);

    HdrPrint(1,
            "void AddElement(%s%s* element);\n",
            commonNamespaceScope.c_str(),
            eltTypeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "void %sAddElement(%s* element)\n",
            GetScopeString().c_str(),
            eltTypeName.c_str());
    SrcPrint(0,
            "{\n");
    SrcPrint(1,
            "ITS_THROW_REQUIRE(element != NULL);\n");
    SrcNewLine();
    SrcPrint(1,
            "element->AsnObject::SetDescription"
            "(Get%sStaticDescription());\n",
            eltTypeName.c_str());
    SrcPrint(1,
            "AsnSetOf::AddElement(element);\n");
    SrcPrint(0,
            "}\n");
    SrcNewLine();

    HdrPrint(1,
            "void AddElement(const %s%s& element);\n", 
            commonNamespaceScope.c_str(),
            eltTypeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "void %sAddElement(const %s& element)\n",
            GetScopeString().c_str(),
            eltTypeName.c_str());
    SrcPrint(0,
            "{\n");
    SrcPrint(1, 
            "AsnObject& asnObject = const_cast<%s&>(element);\n",
            eltTypeName.c_str()); 
    SrcNewLine();
    SrcPrint(1, 
            "asnObject.SetDescription(Get%sStaticDescription());\n",
            eltTypeName.c_str());
    SrcNewLine();
    SrcPrint(1,
            "AsnSetOf::AddElement(element);\n");
    SrcPrint(0,
            "}\n");
    SrcNewLine();

    HdrPrint(1,
            "const %s%s& ElementAt(size_t index) const;\n",
            commonNamespaceScope.c_str(),
            eltTypeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "const %s%s& %sElementAt(size_t index) const\n",
            GetScopeString().c_str(),
            eltTypeName.c_str(),
            GetScopeString().c_str());
    SrcPrint(0,
            "{\n");
    SrcPrint(1,
            "return static_cast<const %s&> (AsnSetOf::ElementAt(index));\n",
            eltTypeName.c_str());
    SrcPrint(0,
            "}\n");
    SrcNewLine();

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
            "%s();\n", 
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnOctetString(false)\n", 
            GetScopeString().c_str(), 
            typeName.c_str());

    GenerateDefaultConstructorBody();

    HdrPrint(1, 
            "%s(const std::vector<byte>& array);\n", 
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(const std::vector<byte>& array) : "
            "AsnOctetString(array, false)\n", 
            GetScopeString().c_str(), 
            typeName.c_str());

    GenerateDefaultConstructorBody();

    HdrPrint(1, 
            "%s(%sOctets& octets);\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(Octets& octets) : AsnOctetString(false)\n",
            GetScopeString().c_str(), 
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1, 
            "%s(const %s& rhs);\n", 
            typeName.c_str(), 
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(const %s& rhs) : AsnOctetString(rhs)\n", 
            GetScopeString().c_str(), 
            typeName.c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* descriptionParam);\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnOctetString(descriptionParam)\n", 
            GetScopeString().c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1, 
            "%s(%sAsnDescObject* descriptionParam, "
            "const std::vector<byte>& array);\n", 
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(AsnDescObject* descriptionParam, "
            "const std::vector<byte>& array) : "
            "AsnOctetString(descriptionParam, array)\n", 
            GetScopeString().c_str(), 
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName, 
                                                    "AsnDescOctetString");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseSizeInstructions();

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

    if (!IsCommonType(definedType))
    {
        InsertOnceReferenceIncludeList(referenceTypeName);
    }
    else
    {
        InsertOnceReferenceIncludeList("@" + referenceTypeName);
    }

    string typedefStr = "";

    typedefStr.reserve(SIZE_TINY);
    
    if (!IsAsnUsefulTypeName(referenceTypeName))
    {
        if (referenceTypeName != typeName)
        {
            typedefStr += GetLevelIndent(GetLevel());

            if (!IsCommonType(definedType))
            {
                typedefStr += GetVarArgsString( 
                                    "typedef %s %s;\n",
                                    referenceTypeName.c_str(),
                                    typeName.c_str()); 
            }
            else
            {
                typedefStr += GetVarArgsString(
                                    "typedef %s::%s %s;\n",
                                    cppMergeNamespaceG.c_str(),
                                    referenceTypeName.c_str(),
                                    typeName.c_str());
            }
        }
        else
        {
            if (module->GetSpecifiedNamespace() == "")
            {
                typedefStr += GetLevelIndent(GetLevel());

                if (!IsCommonType(definedType))
                {
                    typedefStr += GetVarArgsString(
                                        "typedef its::%s %s;\n",
                                        referenceTypeName.c_str(),
                                        typeName.c_str());
                }
                else
                {
                    typedefStr += GetVarArgsString(
                                        "typedef %s::%s %s;\n",
                                        cppMergeNamespaceG.c_str(),
                                        referenceTypeName.c_str(),
                                        typeName.c_str());
                }
            }
            else
            {
                typedefStr += GetLevelIndent(GetLevel());

                if (!IsCommonType(definedType))
                {
                    typedefStr += GetVarArgsString(
                                        "typedef %s::%s %s;\n",
                                        module->GetSpecifiedNamespace().c_str(),
                                        referenceTypeName.c_str(),
                                        typeName.c_str());
                }
                else
                {
                    typedefStr += GetVarArgsString(
                                        "typedef %s::%s %s;\n",
                                        cppMergeNamespaceG.c_str(),
                                        referenceTypeName.c_str(),
                                        typeName.c_str());
                }
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

    SrcNewLine();
}


void
GenerateCppVisitor::VisitAnyType(AnyType* anyType)
{
    InsertOnceBasicIncludeList("AsnAny");

    string typeName = AdaptName(GetCurrentTypeName());

    GenerateTypeClassBeginPart(typeName, "AsnAny");

    HdrPrint(1, 
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnAny(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(%sAsnObject* anyParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(AsnObject* anyParam) : AsnAny(anyParam, false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : AsnAny(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnAny(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(), typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnAny(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam, %sAsnObject* anyParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam, AsnObject* anyParam) "
            ": AsnAny(descriptionParam, anyParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescAny");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseAnyTagInstructions();

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
            "%s();\n",
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s() : AsnAny(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody(); 

    HdrPrint(1, 
            "%s(%sAsnObject* anyParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s%s(AsnObject* anyParam) : AsnAny(anyParam, false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDefaultConstructorBody();    

    HdrPrint(1,
            "%s(%sOctets& octets);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(Octets& octets) : AsnAny(false)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateDecodeConstructorBody();

    HdrPrint(1,
            "%s(const %s& rhs);\n",
            typeName.c_str(),
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(const %s& rhs) : AsnAny(rhs)\n",
            GetScopeString().c_str(),
            typeName.c_str(), typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam) : "
            "AsnAny(descriptionParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    HdrPrint(1,
            "%s(%sAsnDescObject* descriptionParam, %sAsnObject* anyParam);\n",
            typeName.c_str(),
            GetItsNamespaceScope().c_str(),
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0,
            "%s%s(AsnDescObject* descriptionParam, AsnObject* anyParam) "
            ": AsnAny(descriptionParam, anyParam)\n",
            GetScopeString().c_str(),
            typeName.c_str());

    GenerateNothingToDoBody();

    GenerateProtectedScope();

    GenerateInitializeMemberFunction();

    GeneratePublicScope();

    GenerateGetStaticDescriptionMemberFunctionBeginPart(
                                                    typeName,
                                                    "AsnDescAny");

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseAnyTagInstructions();

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
        string instruction = "staticDesc.SetClauseSize();\n";

        constraintInstructionList.push_back(instruction);

        Value* value = singleValueConstraintElement->GetValue();

        Value* baseValue = value->GetBaseValue();

        if (baseValue->GetValueType() == VALUE_INTEGER)
        {
            IntegerValue* integerValue =
                static_cast<IntegerValue*> (baseValue);

            instruction = "staticDesc.SetMinSize(";
            instruction += LongToString(integerValue->GetValue());
            instruction += ");\n";

            constraintInstructionList.push_back(instruction);

            instruction = "staticDesc.SetMaxSize(";
            instruction += LongToString(integerValue->GetValue());
            instruction += ");\n";

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
        string instruction = "staticDesc.SetClauseSize();\n";

        constraintInstructionList.push_back(instruction);

        Value* lowerValue = valueRangeConstraintElement->GetLower();
        Value* upperValue = valueRangeConstraintElement->GetUpper();

        Value* lowerBaseValue = lowerValue->GetBaseValue();
        Value* upperBaseValue = upperValue->GetBaseValue();

        if (lowerBaseValue->GetValueType() == VALUE_INTEGER)
        {
            IntegerValue* integerValue =
                static_cast<IntegerValue*> (lowerBaseValue);

            instruction = "staticDesc.SetMinSize(";
            instruction += LongToString(integerValue->GetValue());
            instruction += ");\n";

            constraintInstructionList.push_back(instruction);
        }

        if (lowerBaseValue->GetValueType() == VALUE_MIN)
        {
            instruction = "staticDesc.SetMinSize(LONG_MIN);\n";

            constraintInstructionList.push_back(instruction);
        }

        if (upperBaseValue->GetValueType() == VALUE_INTEGER)
        {
            IntegerValue* integerValue = 
                static_cast<IntegerValue*> (upperBaseValue);

            instruction = "staticDesc.SetMaxSize(";
            instruction += LongToString(integerValue->GetValue());
            instruction += ");\n";

            constraintInstructionList.push_back(instruction);
        }

        if (upperBaseValue->GetValueType() == VALUE_MAX)
        {
            instruction = "staticDesc.SetMaxSize(LONG_MAX);\n";

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
    SrcPrint(0, 
            "{\n");
    SrcPrint(1, 
            "Initialize();\n");
    SrcPrint(0, 
            "}\n");
    SrcNewLine();
}


void 
GenerateCppVisitor::GenerateDecodeConstructorBody()
{
    SrcPrint(0, 
            "{\n");
    SrcPrint(1, 
            "Initialize();\n");
    SrcNewLine();
    SrcPrint(1, 
            "Decode(octets);\n");
    SrcPrint(0, 
            "}\n");
    SrcNewLine();
}


void 
GenerateCppVisitor::GenerateNothingToDoBody()
{
    SrcPrint(0, 
            "{\n");
    SrcPrint(1, 
            "// Nothing to do.\n");
    SrcPrint(0, 
            "}\n");
    SrcNewLine();
}


void 
GenerateCppVisitor::GenerateInitializeMemberFunction()
{
    HdrPrint(1, 
            "void Initialize();\n");
    HdrNewLine();

    SrcPrint(0, 
            "void %sInitialize()\n", 
            GetScopeString().c_str());
    SrcPrint(0, 
            "{\n");
    SrcPrint(1, 
            "ITS_THROW_ASSERT(description == NULL);\n");
    SrcNewLine();
    SrcPrint(1, 
            "description = GetStaticDescription();\n");
    SrcPrint(1, 
            "description->IncRef();\n");
    SrcPrint(0, 
            "}\n");
    SrcNewLine();
}


void 
GenerateCppVisitor::GenerateDestructor(const string& typeName)
{
    HdrPrint(1, 
            "virtual ~%s();\n", 
            typeName.c_str());
    HdrNewLine();

    SrcPrint(0, 
            "%s~%s()\n", 
            GetScopeString().c_str(), 
            typeName.c_str());
    SrcPrint(0, 
            "{\n");
    SrcPrint(1, 
            "// Nothing to do.\n");
    SrcPrint(0, 
            "}\n");
    SrcNewLine();
}


void 
GenerateCppVisitor::GenerateCloneMemberFunction(const string& typeName)
{
    HdrPrint(1, 
            "virtual %sAsnObject* Clone() const;\n",
            GetItsNamespaceScope().c_str());
    HdrNewLine();

    SrcPrint(0, 
            "AsnObject* %sClone() const\n", 
            GetScopeString().c_str(), 
            typeName.c_str());
    SrcPrint(0, 
            "{\n");
    SrcPrint(1, 
            "return new %s(*this);\n", 
            typeName.c_str());
    SrcPrint(0, 
            "}\n");
    SrcNewLine();
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
            "static bool initialized = false;\n");
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
    SrcPrint(2, 
            "ITS_THROW_ENSURE(result != NULL);\n");
    SrcNewLine();
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
    SrcNewLine();
    SrcPrint(2, 
            "ITS_THROW_ENSURE(result != NULL);\n");
    SrcNewLine();
    SrcPrint(2, 
            "return result;\n");
    SrcPrint(1, 
            "}\n");
    SrcPrint(1, 
            "else\n");
    SrcPrint(1, 
            "{\n");
    SrcPrint(2, 
            "ITS_THROW_ASSERT(result == NULL);\n");
    SrcNewLine();
    SrcPrint(2, 
            "// To deny the reference counting mechanism.\n");
    SrcPrint(2, 
            "// (staticDesc is static.)\n");
    SrcPrint(2, 
            "staticDesc.IncRef();\n");
    SrcNewLine();
    SrcPrint(2, 
            "staticDesc.SetCloneForFactory(new %s(&staticDesc));\n", 
            typeName.c_str());
    SrcNewLine();
    SrcPrint(2, 
            "// One circular reference to remove.\n");
    SrcPrint(2, 
            "// (cloneForFactory is an attribute of staticDesc.)\n");
    SrcPrint(2, 
            "staticDesc.DecRef();\n");
    SrcNewLine();
}


void 
GenerateCppVisitor::GenerateGetStaticDescriptionMemberFunctionEndPart()
{
    SrcPrint(2, "result = &staticDesc;\n");
    SrcNewLine();
    SrcPrint(2, "initialized = true;\n");
    SrcNewLine();
    SrcPrint(2, "Asn::Unlock();\n");
    SrcNewLine();
    SrcPrint(2, "ITS_THROW_ENSURE(result != NULL);\n");
    SrcNewLine();
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

    SrcNewLine();
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
                "staticDesc.SetClauseOptional();\n");
        SrcNewLine();
    }
}


void 
GenerateCppVisitor::GenerateSetClauseAnyTagInstructions()
{
    TagList* tagList = GetCurrentType()->GetAdjustedTagList();

    if (tagList->empty())
    {
        SrcPrint(2, 
                "staticDesc.SetClauseAnyTag();\n");
        SrcNewLine();
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
                    "staticDesc.SetClauseExtensible();\n");
            SrcNewLine();
        }
    }

    if (type->GetType() == TYPE_SEQUENCE)
    {
        SequenceType* sequenceType = 
            static_cast<SequenceType*> (type);

        if (sequenceType->IsExtendable())
        {
            SrcPrint(2, 
                    "staticDesc.SetClauseExtensible();\n");
            SrcNewLine();
        }
    }

    if (type->GetType() == TYPE_SET)
    {
        SetType* setType = 
            static_cast<SetType*> (type);

        if (setType->IsExtendable())
        {
            SrcPrint(2, 
                    "staticDesc.SetClauseExtensible();\n");
            SrcNewLine();
        }
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
    HdrNewLine();

    SrcPrint(0, 
            "AsnDescObject* %sGet%sStaticDescription()\n",
            GetScopeString().c_str(), 
            elementName.c_str());        
    SrcPrint(0, 
            "{\n");
    SrcPrint(1, 
            "static bool initialized = false;\n");
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
    SrcPrint(2, 
            "ITS_THROW_ENSURE(result != NULL);\n");
    SrcNewLine();
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
    SrcNewLine();
    SrcPrint(2, 
            "ITS_THROW_ENSURE(result != NULL);\n");
    SrcNewLine();
    SrcPrint(2, 
            "return result;\n");
    SrcPrint(1, 
            "}\n");
    SrcPrint(1, 
            "else\n");
    SrcPrint(1, 
            "{\n");
    SrcPrint(2, 
            "ITS_THROW_ASSERT(result == NULL);\n");
    SrcNewLine();
    SrcPrint(2, 
            "// To deny the reference counting mechanism.\n");
    SrcPrint(2, 
            "// (staticDesc is static.)\n");
    SrcPrint(2, 
            "staticDesc.IncRef();\n");
    SrcNewLine();

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
    SrcNewLine();
    SrcPrint(2, 
            "// One circular reference to remove.\n");
    SrcPrint(2, 
            "// (cloneForFactory is an attribute of staticDesc.)\n");
    SrcPrint(2, 
            "staticDesc.DecRef();\n");
    SrcNewLine();

    PushContext();

    // Do not want to change the level.
    SetLevel(GetLevel() - 1);

    SetCurrentType(elementType);

    GenerateTagAddLevelInstructions();

    GenerateSetClauseOptionalInstructions();

    GenerateSetClauseExtensibleInstructions();

    switch (baseType->GetType())
    {
        case TYPE_SEQUENCE:
        case TYPE_SET:
        {
            // Class SetType inherits from class SequenceType.

            SequenceType* sequenceType =
                static_cast<SequenceType*> (baseType);

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
                            "staticDesc.AddElement(%d, %s::"
                            "Get%sStaticDescription());\n",
                            index,
                            elementTypeName.c_str(),
                            adaptedName.c_str());
                    
                    index++;
                }

                if (!(typeList->empty()))
                {
                    SrcNewLine();
                }
            }
        }

        break;

        case TYPE_CHOICE:
        {
            ChoiceType* choiceType =
                static_cast<ChoiceType*> (baseType);

            TypeList* typeList = choiceType->GetFlattenedTypeList();

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
                            "staticDesc.AddChoice(%s::"
                            "Get%sStaticDescription());\n",
                            elementTypeName.c_str(),
                            adaptedName.c_str());
                }

                if (!(typeList->empty()))
                {
                    SrcNewLine();
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
                    "staticDesc.SetElement(%s::Get%sStaticDescription());\n",
                    elementTypeName.c_str(),
                    typeName.c_str());
        
            SrcNewLine();
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
                    "staticDesc.SetElement(%s::Get%sStaticDescription());\n",
                    elementTypeName.c_str(),
                    typeName.c_str());
    
            SrcNewLine();
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

            NamedNumberList* namedNumberList = enumeratedType->GetNamedNumberList();

            for (NamedNumberList::iterator iter = namedNumberList->begin();
                 iter != namedNumberList->end();
                 iter++)
            {
                NamedNumber* namedNumber = *iter;

                long value = namedNumber->GetNumber();

                SrcPrint(2,
                        "staticDesc.Put(%d);\n",
                        value);
            }

            if (!(namedNumberList->empty()))
            {
                SrcNewLine();
            }
        }

        break;

        case TYPE_ANY:
        case TYPE_ANY_DEFINED_BY:

            GenerateSetClauseAnyTagInstructions();

            break;

        default:
            {
                bool must_not_be_reached = false;
                ASSERT(must_not_be_reached);
            }
    }

    SrcPrint(2, 
            "result = &staticDesc;\n");
    SrcNewLine();
    SrcPrint(2, 
            "initialized = true;\n");
    SrcNewLine();
    SrcPrint(2, 
            "Asn::Unlock();\n");
    SrcNewLine();
    SrcPrint(2, 
            "ITS_THROW_ENSURE(result != NULL);\n");
    SrcNewLine();
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

    if (module->GetSpecifiedName() != "")
    {
        moduleName = module->GetSpecifiedName();
    }


    // Overwrite if common type.

    if (GetCurrentType()->IsCommon())
    {
        moduleName = cppMergeModuleNameG;
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
    result.append("#if !defined(ITS_NAMESPACE)\n");
    result.append("#error ANSI C++ compiler required.\n");
    result.append("#endif // !defined(ITS_NAMESPACE)\n");
    result.append("\n");
    result.append(GetBasicIncludeListString());
    result.append(GetReferenceIncludeListString());
    result.append("\n");
    result.append("\n");

    if (!GetCurrentType()->IsCommon())
    {
        if (module->GetSpecifiedNamespace() == "")
        {
            result.append("namespace its {\n");
        }
        else
        {
            result.append(GetVarArgsString(
                                "namespace %s {\n",
                                module->GetSpecifiedNamespace().c_str()));
        }
    }
    else
    {
        if (bCppMergeG)
        {
            result.append(GetVarArgsString(
                                "namespace %s {\n",
                                cppMergeNamespaceG.c_str()));
        }
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

    if (module->GetSpecifiedName() != "")
    {
        moduleName = module->GetSpecifiedName();
    }


    // Overwrite if common type.

    if (GetCurrentType()->IsCommon())
    {
        moduleName = cppMergeModuleNameG;
    }

    string moduleNameAdapted = AdaptNameToUppercase(moduleName);
    string typeNameAdapted = AdaptNameToUppercase(GetCurrentTypeName());

    if (typeNameAdapted.size() == 0 || typeNameAdapted[0] != '_')
    {
        typeNameAdapted.insert(0, "_");
    }

    result.append("\n");
    result.append("\n");
    result.append("} // Namespace.\n");
    result.append("\n");
    result.append(GetVarArgsString("#endif // !defined(_%s%s_H_)\n",
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

    if (module->GetSpecifiedName() != "")
    {
        moduleName = module->GetSpecifiedName();
    }


    // Overwrite if common type.

    if (GetCurrentType()->IsCommon())
    {
        moduleName = cppMergeModuleNameG;
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


    if (!GetCurrentType()->IsCommon())
    {
        if (module->GetSpecifiedNamespace() == "")
        {
            result.append("using namespace its;\n");
        }
        else
        {
            result.append("using namespace its;\n");

            result.append(GetVarArgsString(
                                "using namespace %s;\n",
                                module->GetSpecifiedNamespace().c_str()));
        }


        //  Figure out if at least one common type is used.

        bool useCommonType = false;

        for (list<string>::iterator iter = referenceIncludeList.begin();
             iter != referenceIncludeList.end();
             iter++)
        {
            string str = *iter;

            ASSERT(str.size() >= 1);

            bool commonType = false;

            if (str[0] == '@')
            {
                useCommonType = true;
            }
        }

        if (useCommonType)
        {
            if (bCppMergeG)
            {
                result.append(GetVarArgsString(
                                    "using namespace %s;\n",
                                     cppMergeNamespaceG.c_str()));
            }
        }
    }
    else
    {
        result.append("using namespace its;\n");

        result.append(GetVarArgsString(
                            "using namespace %s;\n",
                            cppMergeNamespaceG.c_str()));
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
        GetVarArgsString(
            "// Generated by IntelliAsnCC ASN.1 compiler %s (C, C++, Java).\n",
            versionG.c_str()));
    result.append("//\n");
    result.append("// Do not edit!\n");
    result.append("//\n");
    result.append("//\n");
    result.append("//\n");
    result.append(
        "// (C) 2001 IntelliNet Technologies Inc. All Rights Reserved.\n");
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

    if (module->GetSpecifiedName() != "")
    {
        moduleName = module->GetSpecifiedName();
    }

    for (list<string>::iterator iter = referenceIncludeList.begin();
         iter != referenceIncludeList.end();
         iter++)
    {
        string str = *iter;

        ASSERT(str.size() >= 1);

        bool commonType = false;

        if (str[0] == '@')
        {
            str = str.erase(0, 1);

            commonType = true;
        }

        string fileNameCore = "";

        if (!IsAsnUsefulTypeName(str))
        {
            if (!bCppFileNamesNoPrefixG)
            {
                if (!commonType)
                {
                    fileNameCore.append(moduleName);
                    fileNameCore.append("_");
                }
                else
                {
                    fileNameCore.append(cppMergeModuleNameG);
                    fileNameCore.append("_");


                    // TODO: to be fixed. Temporary work around.

                    if (!bCppMergeG)
                    {
                        continue;
                    }
                }
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
//  Return "its::" or "" according to module namespace option.
//

string
GenerateCppVisitor::GetItsNamespaceScope()
{
    if (module->GetSpecifiedNamespace() == "" && !GetCurrentType()->IsCommon())
    {
        return "";
    }
    else
    {
        return "its::";
    }
}


bool
GenerateCppVisitor::IsCommonType(Type* type)
{
    REQUIRE(type != NULL);

    switch(type->GetType())
    {
        case TYPE_DEFINED:
            {
                DefinedType* definedType =
                    static_cast<DefinedType*> (type);

                return definedType->GetLink()->IsCommon();
            }
            
        default:
            
            return type->IsCommon();
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
    if (typeName == "ObjectDescriptor"  ||
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


GenerateCppVisitor::TypeDefTable GenerateCppVisitor::commonTypeDefTable;


