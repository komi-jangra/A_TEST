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
// LOG: Revision 8.2  2005/03/21 13:52:59  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.3  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: asncc_generate_c_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"

#include <stdarg.h>

#include <asncc_generate_c_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  GenerateCVisitor implementation.
//

void 
GenerateCVisitor::VisitModuleBegin(Module* moduleParam)
{
    REQUIRE(moduleParam != NULL);

    string moduleName = moduleParam->GetName();

    if (cModuleNameG != "")
    {
        moduleName = cModuleNameG;
    }

    SetCurrentModuleName(moduleName);
}


void 
GenerateCVisitor::VisitModuleEnd(Module* moduleParam)
{
    REQUIRE(moduleParam != NULL);

    // Cleaning of contents (header and source).

    GetHdr().erase(GetHdr().begin(), GetHdr().end());
    GetSrc().erase(GetSrc().begin(), GetSrc().end());

    GenerateModuleItsFeatureClass();

    string directoryName    = "";
    string fileNameCore     = "";

    string moduleName = GetCurrentModuleName();

    if (bModuleDirectoryG)
    {
        directoryName = AdaptNameToLowercase(moduleName);
    }

    fileNameCore.append(GetCurrentModuleName());
    fileNameCore.append("_");
    fileNameCore.append("its_feature_class");
    fileNameCore = AdaptNameToLowercase(fileNameCore);

    WriteTextToFile(directoryName,
                    fileNameCore + "_c",
                    "h",
                    GetHdr());

    WriteTextToFile(directoryName,
                    fileNameCore + "_c",
                    "c",
                    GetSrc());

    // Cleaning of contents (header and source).

    GetHdr().erase(GetHdr().begin(), GetHdr().end());
    GetSrc().erase(GetSrc().begin(), GetSrc().end());

    ClearGetStaticDescriptionInstructionList();
    ClearDestructStaticDescriptionInstructionList();
}


void 
GenerateCVisitor::VisitImportedModule(ImportedModule* importedModule)
{
    REQUIRE(importedModule != NULL);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCVisitor::VisitTypeDefBegin(TypeDef* typeDef)
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
GenerateCVisitor::VisitTypeDefEnd(TypeDef* typeDef)
{
    GetHdr().insert(0, GetHdrHeaderString());
    GetHdr().append(GetHdrEndString());

    GetSrc().insert(0, GetSrcHeaderString());
    GetSrc().append(GetSrcEndString());

    string directoryName    = "";
    string fileNameCore     = "";

    string moduleName = GetCurrentModuleName();

    if (bModuleDirectoryG)
    {
        directoryName = AdaptNameToLowercase(moduleName);
    }

    fileNameCore.append(GetCurrentModuleName());
    fileNameCore.append("_");
    fileNameCore.append(AdaptName(GetCurrentTypeName()));
    fileNameCore = AdaptNameToLowercase(fileNameCore);

    WriteTextToFile(directoryName,
                    fileNameCore + "_c",
                    "h",
                    GetHdr());

    WriteTextToFile(directoryName,
                    fileNameCore + "_c",
                    "c",
                    GetSrc());
}


void 
GenerateCVisitor::VisitTypeBegin(Type* type)
{
    SetCurrentType(type);

    constraintInstructionList.clear();
}


void 
GenerateCVisitor::VisitTypeEnd(Type* type)
{
    // Nothing to do.
}


void
GenerateCVisitor::VisitTypeDefaultValue(Type* type, Value* value)
{   

}


void 
GenerateCVisitor::VisitBitStringTypeBegin(BitStringType* bitStringType)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitBitStringTypeEnd(BitStringType* bitStringType)
{
    InsertOnceBasicIncludeList("asn_bit_string");

    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetArray");
    asnTypeFunctionInherit.push_back("SetArray");
    asnTypeFunctionInherit.push_back("GetSize");
    asnTypeFunctionInherit.push_back("Set");
    asnTypeFunctionInherit.push_back("Reset");
    asnTypeFunctionInherit.push_back("IsSet");
    asnTypeFunctionInherit.push_back("IsDefined");
    asnTypeFunctionInherit.push_back("SetAll");
    asnTypeFunctionInherit.push_back("ResetAll");
    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "BitString", 
                                asnTypeFunctionInherit);

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back("NULL");
    actualArguments.push_back("0");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("const ITS_BOOLEAN* array");
    formalArguments.push_back("size_t size");

    actualArguments.push_back("array");
    actualArguments.push_back("size");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "WithArraySize", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescBitString description");

    actualArguments.push_back("NULL");
    actualArguments.push_back("0");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("const ITS_BOOLEAN* array");
    formalArguments.push_back("size_t size");
    formalArguments.push_back("ASN_DescBitString description");

    actualArguments.push_back("array");
    actualArguments.push_back("size");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithArraySizeDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();
    
    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    HdrPrint(0,
            "const ITS_BOOLEAN* %s_GetArray(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "const ITS_BOOLEAN*\n%s_GetArray(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_BIT_STRING_CLASS_GET_ARRAY(ITS_OBJ_CLASS(object))((ASN_BitString)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "size_t %s_GetSize(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "size_t\n%s_GetSize(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_BIT_STRING_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))((ASN_BitString)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "int %s_SetArray(%s object, const ITS_BOOLEAN* array, size_t size);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "int\n%s_SetArray(%s object, const ITS_BOOLEAN* array, size_t size)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_BIT_STRING_CLASS_SET_ARRAY(ITS_OBJ_CLASS(object))((ASN_BitString)object, array, size);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    NamedNumberList* namedNumberList = bitStringType->GetNamedNumberList();

    for (NamedNumberList::iterator iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string definedName = AdaptName(namedNumber->GetName());

        long value = namedNumber->GetNumber();

        HdrPrint(0,
                "void %s_Set%s(%s object, ITS_BOOLEAN value);\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "void\n%s_Set%s(%s object, ITS_BOOLEAN value)\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "{\n");

        SrcPrint(1,
                "ASN_BIT_STRING_CLASS_SET(ITS_OBJ_CLASS(object))((ASN_BitString)object, %d, value);\n",
                value);

        SrcPrint(0,
                "}\n");

        SrcNewLine();

        HdrPrint(0,
                "void %s_Reset%s(%s object);\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "void\n%s_Reset%s(%s object)\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "{\n");

        SrcPrint(1,
                "ASN_BIT_STRING_CLASS_RESET(ITS_OBJ_CLASS(object))((ASN_BitString)object, %d);\n",
                value);

        SrcPrint(0,
                "}\n");

        SrcNewLine();

        HdrPrint(0,
                "ITS_BOOLEAN %s_Is%sSet(const %s object);\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "ITS_BOOLEAN\n%s_Is%sSet(const %s object)\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "{\n");

        SrcPrint(1,
                "return ASN_BIT_STRING_CLASS_IS_SET(ITS_OBJ_CLASS(object))((ASN_BitString)object, %d);\n",
                value);

        SrcPrint(0,
                "}\n");

        SrcNewLine();

        HdrPrint(0,
                "ITS_BOOLEAN %s_Is%sDefined(const %s object);\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "ITS_BOOLEAN\n%s_Is%sDefined(const %s object)\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "{\n");

        SrcPrint(1,
                "return ASN_BIT_STRING_CLASS_IS_DEFINED(ITS_OBJ_CLASS(object))((ASN_BitString)object, %d);\n",
                value);

        SrcPrint(0,
                "}\n");

        SrcNewLine();
    }

    GenerateGetUniversalTagFunction("BitString");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("BitString");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "BitString");

    GenerateTagAddLevelInstructions("BitString");

    GenerateSetClauseOptionalInstructions("BitString");

    GenerateSetClauseSizeInstructions("BitString");

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "BitString");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();
}


void 
GenerateCVisitor::VisitBooleanType(BooleanType* booleanType)
{
    InsertOnceBasicIncludeList("asn_boolean");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetValue");
    asnTypeFunctionInherit.push_back("SetValue");
    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "Boolean", 
                                asnTypeFunctionInherit);

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back("ITS_FALSE");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ITS_BOOLEAN value");

    actualArguments.push_back("value");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "WithValue", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescBoolean description");

    actualArguments.push_back("ITS_FALSE");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ITS_BOOLEAN value");
    formalArguments.push_back("ASN_DescBoolean description");

    actualArguments.push_back("value");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithValueDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();
    
    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    HdrPrint(0,
            "ITS_BOOLEAN %s_GetValue(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "ITS_BOOLEAN\n%s_GetValue(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_BOOLEAN_CLASS_GET_VALUE(ITS_OBJ_CLASS(object))((ASN_Boolean)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "void %s_SetValue(%s object, ITS_BOOLEAN value);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "void\n%s_SetValue(%s object, ITS_BOOLEAN value)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ASN_BOOLEAN_CLASS_SET_VALUE(ITS_OBJ_CLASS(object))((ASN_Boolean)object, value);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    GenerateGetUniversalTagFunction("Boolean");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("Boolean");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "Boolean");

    GenerateTagAddLevelInstructions("Boolean");

    GenerateSetClauseOptionalInstructions("Boolean");

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "Boolean");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();
}


void 
GenerateCVisitor::VisitChoiceTypeBegin(ChoiceType* choiceType)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitChoiceTypeEnd(ChoiceType* choiceType)
{
    InsertOnceBasicIncludeList("asn_choice");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetChoice");
    asnTypeFunctionInherit.push_back("SetChoice");
    asnTypeFunctionInherit.push_back("Contains");
    asnTypeFunctionInherit.push_back("ContainsChoice");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "Choice", 
                                asnTypeFunctionInherit);

    HdrNewLine();
    HdrPrint(0, "/*-------- Begin Nested Type(s) --------*/\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, "/*-------- Begin Nested Type(s) --------*/\n");
    SrcNewLine();

    TypeList* typeList = choiceType->GetFlattenedTypeList();

    int choiceSize = 0;

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

        choiceSize = typeList->size();
    }

    HdrNewLine();
    HdrPrint(0, "/*-------- End Nested Type(s) --------*/\n");
    HdrNewLine();
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, "/*-------- End Nested Type(s) --------*/\n");
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    typeList = choiceType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            GenerateProtectedElementStaticDescription(namedType, adaptedName);

            GenerateElementStaticDescription(namedType, adaptedName);
        }
    }

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescChoice description");

    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

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
                string asnTypeNameLowercase = 
                    AdaptNameToLowercase(adaptedGenTypeName);

                InsertOnceBasicIncludeList(asnTypeNameLowercase);
            }
            else
            {
                InsertOnceReferenceIncludeList(adaptedGenTypeName);
            }

            string adaptedGenBaseTypeName =
                AdaptName(GetGeneratedBaseTypeName(namedType));

            if (IsAsnTypeName(adaptedGenBaseTypeName))
            {
                string asnTypeNameLowercase = 
                    AdaptNameToLowercase(adaptedGenBaseTypeName);

                InsertOnceBasicIncludeList(asnTypeNameLowercase);
            }

            string adaptedElementTypeName =
                AdaptName(GetGeneratedElementTypeName(namedType));

            string scopedElementTypeName = "";

            if (namedType->GetType() == TYPE_DEFINED)
            {
                // Typical case of TYPE_CHOICE, TYPE_SEQUENCE and TYPE_SET.

                if (!IsAsnUsefulTypeName(GetGeneratedElementTypeName(namedType)))
                {
                    scopedElementTypeName = moduleName;
                    scopedElementTypeName.append("_");
                    scopedElementTypeName.append(AdaptName(GetGeneratedElementTypeName(namedType)));
                }
                else
                {
                    scopedElementTypeName = "ASN_";
                    scopedElementTypeName.append(AdaptName(GetGeneratedElementTypeName(namedType)));
                }
            }
            else
            {
                // Typical case of TYPE_SEQUENCE_OF and TYPE_SET_OF.

                scopedElementTypeName = moduleName;
                scopedElementTypeName.append("_");
                scopedElementTypeName.append(GetScopeString());
                scopedElementTypeName.append(adaptedName);
            }

            HdrPrint(0, 
                    "void %s_SetChoice%s(%s object, %s choice);\n", 
                    scopedTypeName.c_str(),
                    adaptedName.c_str(), 
                    scopedTypeName.c_str(),
                    scopedElementTypeName.c_str());

            SrcPrint(0, 
                    "void\n%s_SetChoice%s(%s object, %s choice)\n", 
                    scopedTypeName.c_str(),
                    adaptedName.c_str(), 
                    scopedTypeName.c_str(),
                    scopedElementTypeName.c_str());

            SrcPrint(0, 
                    "{\n");

            SrcPrint(1,
                    "ASN_C_REQUIRE(object != NULL);\n");

            SrcPrint(1, 
                    "ASN_C_REQUIRE(choice != NULL);\n");

            SrcNewLine();

            SrcPrint(1,
                    "ASN_OBJECT_DESCRIPTION(choice) = (ASN_DescObject)_%s_Get%sStaticDescription();\n",
                    scopedTypeName.c_str(),
                    adaptedName.c_str());

            SrcNewLine();

            SrcPrint(1, 
                    "ASN_CHOICE_CLASS_SET_CHOICE(ITS_OBJ_CLASS(object))((ASN_Choice)object, (ASN_Object)choice);\n");

            SrcPrint(0, 
                    "}\n");

            SrcNewLine();

            HdrPrint(0, 
                    "ITS_BOOLEAN %s_Choice%s(const %s object);\n", 
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str());

            SrcPrint(0, 
                    "ITS_BOOLEAN %s_Choice%s(const %s object)\n", 
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str());

            SrcPrint(0, 
                    "{\n");

            SrcPrint(1,
                    "ASN_C_REQUIRE(object != NULL);\n");

            SrcNewLine();

            SrcPrint(1,
                    "return ASN_CHOICE_CLASS_CONTAINS(ITS_OBJ_CLASS(object))((ASN_Choice)object, ASN_DescObject_TagIdentity((ASN_DescObject)_%s_Get%sStaticDescription()));\n",
                    scopedTypeName.c_str(),
                    adaptedName.c_str());

            SrcPrint(0, 
                    "}\n");

            SrcNewLine();

            HdrPrint(0, 
                    "const %s %s_GetChoice%s(const %s object);\n", 
                    scopedElementTypeName.c_str(),
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str());

            SrcPrint(0, 
                    "const %s\n%s_GetChoice%s(const %s object)\n", 
                    scopedElementTypeName.c_str(),
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str());

            SrcPrint(0, 
                    "{\n");

            SrcPrint(1,
                    "ASN_C_REQUIRE(object != NULL);\n");

            SrcPrint(1, 
                    "ASN_C_REQUIRE(%s_Choice%s(object));\n", 
                    scopedTypeName.c_str(),
                    adaptedName.c_str());

            SrcNewLine();

            SrcPrint(1, 
                    "return (const %s)ASN_CHOICE_CLASS_GET_CHOICE(ITS_OBJ_CLASS(object))((ASN_Choice)object);\n",
                    scopedElementTypeName.c_str());

            SrcPrint(0, 
                    "}\n");

            SrcNewLine();
        }
    }

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("Choice");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "Choice");

    GenerateTagAddLevelInstructions("Choice");

    GenerateSetClauseOptionalInstructions("Choice");

    typeList = choiceType->GetFlattenedTypeList();

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
                    "ASN_DescChoice_AddChoice(description, %d, (ASN_DescObject)_%s_Get%sStaticDescription());\n",
                    index,
                    scopedTypeName.c_str(),
                    adaptedName.c_str());

            index++;
        }

        if (!(typeList->empty()))
        {
            SrcNewLine();
        }
    }

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                        scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                        scopedTypeName,
                                                        "Choice");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart(); 
    
    ClearDestructElementStaticDescInstructionList();
}


void
GenerateCVisitor::VisitChoiceTypeList(TypeList* typeList)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitEnumeratedTypeBegin(EnumeratedType* enumeratedType)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitEnumeratedTypeEnd(EnumeratedType* enumeratedType)
{
    InsertOnceBasicIncludeList("asn_enumerated");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetValue");
    asnTypeFunctionInherit.push_back("SetValue");
    asnTypeFunctionInherit.push_back("GetValueFromValueName");
    asnTypeFunctionInherit.push_back("GetValueNameFromValue");
    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "Enumerated", 
                                asnTypeFunctionInherit);

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back("0");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ITS_LONG value");

    actualArguments.push_back("value");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "WithValue", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescEnumerated description");

    actualArguments.push_back("0");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ITS_LONG value");
    formalArguments.push_back("ASN_DescEnumerated description");

    actualArguments.push_back("value");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithValueDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();
    
    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    HdrPrint(0,
            "ITS_LONG %s_GetValue(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "ITS_LONG\n%s_GetValue(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_ENUMERATED_CLASS_GET_VALUE(ITS_OBJ_CLASS(object))((ASN_Enumerated)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "void %s_SetValue(%s object, ITS_LONG value);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "void\n%s_SetValue(%s object, ITS_LONG value)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ASN_ENUMERATED_CLASS_SET_VALUE(ITS_OBJ_CLASS(object))((ASN_Enumerated)object, value);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "ITS_LONG %s_GetValueFromValueName(const %s object, const char* valueName);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "ITS_LONG\n%s_GetValueFromValueName(const %s object, const char* valueName)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_ENUMERATED_CLASS_GET_VALUE_FROM_VALUE_NAME(ITS_OBJ_CLASS(object))((ASN_Enumerated)object, valueName);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "const char* %s_GetValueNameFromValue(const %s object, ITS_LONG value);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "const char*\n%s_GetValueNameFromValue(const %s object, ITS_LONG value)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_ENUMERATED_CLASS_GET_VALUE_NAME_FROM_VALUE(ITS_OBJ_CLASS(object))((ASN_Enumerated)object, value);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    NamedNumberList* namedNumberList = enumeratedType->GetNamedNumberList();

    NamedNumberList::iterator iter;

    for (iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string definedName = AdaptName(namedNumber->GetName());

        long value = namedNumber->GetNumber();

        HdrPrint(0,
                "void %s_Set%s(%s object);\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "void\n%s_Set%s(%s object)\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "{\n");

        SrcPrint(1,
                "ASN_ENUMERATED_VALUE(object) = %d;\n",
                value);

        SrcPrint(0,
                "}\n");

        SrcNewLine();

        HdrPrint(0,
                "ITS_BOOLEAN %s_Is%s(const %s object);\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "ITS_BOOLEAN\n%s_Is%s(const %s object)\n",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str());

        SrcPrint(0,
                "{\n");

        SrcPrint(1,
                "return ASN_ENUMERATED_VALUE(object) == %d;\n",
                value);

        SrcPrint(0,
                "}\n");

        SrcNewLine();
    }

    GenerateGetUniversalTagFunction("Enumerated");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("Enumerated");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();

    namedNumberList = enumeratedType->GetNamedNumberList();

    bool first = true;

    HdrPrint(0, 
            "enum {\n");

    for (iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string scopedTypeNamePrefix = AdaptNameToUppercase(scopedTypeName);

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

        HdrPrint(1, 
                "%s_%s = %d", 
                scopedTypeNamePrefix.c_str(),
                definedName.c_str(), 
                value);
    }

    GetHdr().append("\n");

    HdrPrint(0, 
            "};\n");

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "Enumerated");

    GenerateTagAddLevelInstructions("Enumerated");

    GenerateSetClauseOptionalInstructions("Enumerated");

    namedNumberList = enumeratedType->GetNamedNumberList();

    int i = 0;

    for (iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        long value = namedNumber->GetNumber();

        SrcPrint(2,
                "ASN_DescEnumerated_AddValue(description, %d, %d);\n",
                i++,
                value);
    }

    if (!(namedNumberList->empty()))
    {
        SrcNewLine();
    }

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "Enumerated");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    SrcPrint(0, 
            "static ITS_LONG\n_%s_GetValueFromValueName(const ASN_Enumerated object, const char* valueName)\n",
            scopedTypeName.c_str());

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
            "ITS_BOOLEAN invalid_value_name = ITS_FALSE;\n");

    SrcPrint(2, 
            "ASN_C_ASSERT(invalid_value_name);\n");

    SrcNewLine();

    SrcPrint(2, 
            "return 0;\n");

    SrcPrint(1, 
            "}\n");

    SrcPrint(0, 
            "}\n");

    SrcNewLine();


    SrcPrint(0, 
            "static const char*\n_%s_GetValueNameFromValue(const ASN_Enumerated object, ITS_LONG value)\n",
            scopedTypeName.c_str());

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
                definedName.c_str());

        SrcPrint(1, 
                "}\n");
    }

    SrcPrint(1, 
            "else\n");

    SrcPrint(1, 
            "{\n");

    SrcPrint(2, 
            "ITS_BOOLEAN invalid_value = ITS_FALSE;\n");

    SrcPrint(2, 
            "ASN_C_ASSERT(invalid_value);\n");

    SrcNewLine();

    SrcPrint(2, 
            "return \"\";\n");

    SrcPrint(1, 
            "}\n");

    SrcPrint(0, 
            "}\n");

    SrcNewLine();

    GenerateTypeClassObjectEndPart();
}


void 
GenerateCVisitor::VisitIntegerTypeBegin(IntegerType* integerType)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitIntegerTypeEnd(IntegerType* integerType)
{
    InsertOnceBasicIncludeList("asn_integer");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetValue");
    asnTypeFunctionInherit.push_back("SetValue");
    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "Integer", 
                                asnTypeFunctionInherit);

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back("0");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ITS_LONG value");

    actualArguments.push_back("value");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "WithValue", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescInteger description");

    actualArguments.push_back("0");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ITS_LONG value");
    formalArguments.push_back("ASN_DescInteger description");

    actualArguments.push_back("value");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithValueDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();
    
    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    HdrPrint(0,
            "ITS_LONG %s_GetValue(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "ITS_LONG\n%s_GetValue(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_INTEGER_CLASS_GET_VALUE(ITS_OBJ_CLASS(object))((ASN_Integer)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "void %s_SetValue(%s object, ITS_LONG value);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "void\n%s_SetValue(%s object, ITS_LONG value)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ASN_INTEGER_CLASS_SET_VALUE(ITS_OBJ_CLASS(object))((ASN_Integer)object, value);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    GenerateGetUniversalTagFunction("Integer");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("Integer");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "Integer");

    GenerateTagAddLevelInstructions("Integer");

    GenerateSetClauseOptionalInstructions("Integer");

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "Integer");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();
}


void
GenerateCVisitor::VisitObjectIdentifierType(
                                ObjectIdentifierType* objectIdentifierType)
{
    InsertOnceBasicIncludeList("asn_object_identifier");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "ObjectIdentifier", 
                                asnTypeFunctionInherit);

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back("NULL");
    actualArguments.push_back("0");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("const ITS_LONG* array");
    formalArguments.push_back("size_t size");

    actualArguments.push_back("array");
    actualArguments.push_back("size");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "WithArraySize", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescObjectIdentifier description");

    actualArguments.push_back("NULL");
    actualArguments.push_back("0");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("const ITS_LONG* array");
    formalArguments.push_back("size_t size");
    formalArguments.push_back("ASN_DescObjectIdentifier description");

    actualArguments.push_back("array");
    actualArguments.push_back("size");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithArraySizeDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();
    
    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    HdrPrint(0,
            "const ITS_LONG* %s_GetArray(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "const ITS_LONG*\n%s_GetArray(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OBJECT_IDENTIFIER_CLASS_GET_ARRAY(ITS_OBJ_CLASS(object))((ASN_ObjectIdentifier)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "size_t %s_GetSize(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "size_t\n%s_GetSize(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OBJECT_IDENTIFIER_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))((ASN_ObjectIdentifier)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "int %s_SetArray(%s object, const ITS_LONG* array, size_t size);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "int\n%s_SetArray(%s object, const ITS_LONG* array, size_t size)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OBJECT_IDENTIFIER_CLASS_SET_ARRAY(ITS_OBJ_CLASS(object))((ASN_ObjectIdentifier)object, array, size);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    GenerateGetUniversalTagFunction("ObjectIdentifier");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("ObjectIdentifier");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "ObjectIdentifier");

    GenerateTagAddLevelInstructions("ObjectIdentifier");

    GenerateSetClauseOptionalInstructions("ObjectIdentifier");

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "ObjectIdentifier");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();
}


void
GenerateCVisitor::VisitNullType(NullType* nullType)
{
    InsertOnceBasicIncludeList("asn_null");

    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "Null", 
                                asnTypeFunctionInherit);

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescNull description");

    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();
    
    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    GenerateGetUniversalTagFunction("Null");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("Null");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "Null");

    GenerateTagAddLevelInstructions("Null");

    GenerateSetClauseOptionalInstructions("Null");

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "Null");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();
}


void
GenerateCVisitor::VisitRealType(RealType* realType)
{
    InsertOnceBasicIncludeList("asn_real");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetValue");
    asnTypeFunctionInherit.push_back("SetValue");
    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "Real", 
                                asnTypeFunctionInherit);

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back("0");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("double value");

    actualArguments.push_back("value");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "WithValue", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescReal description");

    actualArguments.push_back("0");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("double value");
    formalArguments.push_back("ASN_DescReal description");

    actualArguments.push_back("value");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithValueDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();
    
    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    HdrPrint(0,
            "double %s_GetValue(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "double\n%s_GetValue(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_REAL_CLASS_GET_VALUE(ITS_OBJ_CLASS(object))((ASN_Real)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "void %s_SetValue(%s object, double value);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "void\n%s_SetValue(%s object, double value)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ASN_REAL_CLASS_SET_VALUE(ITS_OBJ_CLASS(object))((ASN_Real)object, value);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    GenerateGetUniversalTagFunction("Real");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("Real");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "Real");

    GenerateTagAddLevelInstructions("Real");

    GenerateSetClauseOptionalInstructions("Real");

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "Real");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();
}


void 
GenerateCVisitor::VisitSequenceTypeBegin(SequenceType* sequenceType)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitSequenceTypeEnd(SequenceType* sequenceType)
{
    InsertOnceBasicIncludeList("asn_sequence");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetElements");
    asnTypeFunctionInherit.push_back("AddElement");
    asnTypeFunctionInherit.push_back("GetElementAt");
    asnTypeFunctionInherit.push_back("GetElementAtTag");
    asnTypeFunctionInherit.push_back("Contains");
    asnTypeFunctionInherit.push_back("ContainsTag");
    asnTypeFunctionInherit.push_back("RemoveElement");
    asnTypeFunctionInherit.push_back("RemoveElementTag");
    asnTypeFunctionInherit.push_back("RemoveAllElements");
    asnTypeFunctionInherit.push_back("GetSize");
    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "Sequence", 
                                asnTypeFunctionInherit);

    HdrNewLine();

    HdrPrint(0, 
            "/*-------- Begin Nested Type(s) --------*/\n");

    HdrNewLine();

    SrcNewLine();

    SrcPrint(0, 
            "/*-------- Begin Nested Type(s) --------*/\n");

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
            "/*-------- End Nested Type(s) --------*/\n");
    HdrNewLine();
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "/*-------- End Nested Type(s) --------*/\n");
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    typeList = sequenceType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            GenerateProtectedElementStaticDescription(namedType, adaptedName);

            GenerateElementStaticDescription(namedType, adaptedName);
        }
    }

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string sequenceSizeStr = GetVarArgsString("%d", sequenceSize);

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back(sequenceSizeStr);
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescSequence description");

    actualArguments.push_back(sequenceSizeStr);
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

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
                string asnTypeNameLowercase = 
                    AdaptNameToLowercase(adaptedGenTypeName);

                InsertOnceBasicIncludeList(asnTypeNameLowercase);
            }
            else
            {
                InsertOnceReferenceIncludeList(adaptedGenTypeName);
            }

            string adaptedGenBaseTypeName =
                AdaptName(GetGeneratedBaseTypeName(namedType));

            if (IsAsnTypeName(adaptedGenBaseTypeName))
            {
                string asnTypeNameLowercase = 
                    AdaptNameToLowercase(adaptedGenBaseTypeName);

                InsertOnceBasicIncludeList(asnTypeNameLowercase);
            }

            string adaptedElementTypeName =
                AdaptName(GetGeneratedElementTypeName(namedType));

            string scopedElementTypeName = "";

            if (namedType->GetType() == TYPE_DEFINED)
            {
                // Typical case of TYPE_CHOICE, TYPE_SEQUENCE and TYPE_SET.

                if (!IsAsnUsefulTypeName(GetGeneratedElementTypeName(namedType)))
                {
                    scopedElementTypeName = moduleName;
                    scopedElementTypeName.append("_");
                    scopedElementTypeName.append(AdaptName(GetGeneratedElementTypeName(namedType)));
                }
                else
                {
                    scopedElementTypeName = "ASN_";
                    scopedElementTypeName.append(AdaptName(GetGeneratedElementTypeName(namedType)));
                }
            }
            else
            {
                // Typical case of TYPE_SEQUENCE_OF and TYPE_SET_OF.

                scopedElementTypeName = moduleName;
                scopedElementTypeName.append("_");
                scopedElementTypeName.append(GetScopeString());
                scopedElementTypeName.append(adaptedName);
            }

            HdrPrint(0, 
                    "void %s_Set%s(%s object, %s element);\n", 
                    scopedTypeName.c_str(),
                    adaptedName.c_str(), 
                    scopedTypeName.c_str(),
                    scopedElementTypeName.c_str());

            SrcPrint(0, 
                    "void\n%s_Set%s(%s object, %s element)\n", 
                    scopedTypeName.c_str(),
                    adaptedName.c_str(), 
                    scopedTypeName.c_str(),
                    scopedElementTypeName.c_str());

            SrcPrint(0, 
                    "{\n");

            SrcPrint(1,
                    "ASN_C_REQUIRE(object != NULL);\n");

            SrcPrint(1, 
                    "ASN_C_REQUIRE(element != NULL);\n");

            SrcNewLine();

            SrcPrint(1,
                    "ASN_OBJECT_DESCRIPTION(element) = (ASN_DescObject)_%s_Get%sStaticDescription();\n",
                    scopedTypeName.c_str(),
                    adaptedName.c_str());

            SrcNewLine();

            SrcPrint(1, 
                    "ASN_SEQUENCE_CLASS_ADD_ELEMENT(ITS_OBJ_CLASS(object))((ASN_Sequence)object, %d, (ASN_Object)element);\n",
                    index);

            SrcPrint(0, 
                    "}\n");

            SrcNewLine();

            if (namedType->IsOptional())
            {
                HdrPrint(0, 
                        "ITS_BOOLEAN %s_Option%s(const %s object);\n", 
                        scopedTypeName.c_str(),
                        adaptedName.c_str(),
                        scopedTypeName.c_str());

                SrcPrint(0, 
                        "ITS_BOOLEAN %s_Option%s(const %s object)\n", 
                        scopedTypeName.c_str(),
                        adaptedName.c_str(),
                        scopedTypeName.c_str());

                SrcPrint(0, 
                        "{\n");

                SrcPrint(1,
                        "ASN_C_REQUIRE(object != NULL);\n");

                SrcNewLine();

                SrcPrint(1,
                        "return ASN_SEQUENCE_CLASS_CONTAINS(ITS_OBJ_CLASS(object))((ASN_Sequence)object, %d);\n",
                        index);

                SrcPrint(0, 
                        "}\n");

                SrcNewLine();
            }

            HdrPrint(0, 
                    "const %s %s_Get%s(const %s object);\n", 
                    scopedElementTypeName.c_str(),
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str());

            SrcPrint(0, 
                    "const %s\n%s_Get%s(const %s object)\n", 
                    scopedElementTypeName.c_str(),
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str());

            SrcPrint(0, 
                    "{\n");

            SrcPrint(1,
                    "ASN_C_REQUIRE(object != NULL);\n");

            if (namedType->IsOptional())
            {
            
                SrcPrint(1, 
                        "ASN_C_REQUIRE(%s_Option%s(object));\n", 
                        scopedTypeName.c_str(),
                        adaptedName.c_str());

                SrcNewLine();
            }

            SrcPrint(1, 
                    "return (const %s)ASN_SEQUENCE_CLASS_GET_ELEMENT_AT(ITS_OBJ_CLASS(object))((ASN_Sequence)object, %d);\n",
                    scopedElementTypeName.c_str(), 
                    index);
            SrcPrint(0, 
                    "}\n");
            SrcNewLine();

            index++;
        }
    }

    GenerateGetUniversalTagFunction("Sequence");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("Sequence");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "Sequence");

    GenerateTagAddLevelInstructions("Sequence");

    GenerateSetClauseOptionalInstructions("Sequence");

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
                    "ASN_DescSequence_AddElement(description, %d, (ASN_DescObject)_%s_Get%sStaticDescription());\n",
                    index, 
                    scopedTypeName.c_str(),
                    adaptedName.c_str());

            index++;
        }

        if (!(typeList->empty()))
        {
            SrcNewLine();
        }
    }

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                        scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                        scopedTypeName,
                                                        "Sequence");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();  

    ClearDestructElementStaticDescInstructionList();
}


void
GenerateCVisitor::VisitSequenceTypeList(TypeList* typeList)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitSequenceOfTypeBegin(SequenceOfType* sequenceOfType)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitSequenceOfTypeEnd(SequenceOfType* sequenceOfType)
{
    InsertOnceBasicIncludeList("asn_sequence_of");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetElements");
    asnTypeFunctionInherit.push_back("AddElement");
    asnTypeFunctionInherit.push_back("GetElementAt");
    asnTypeFunctionInherit.push_back("RemoveElement");
    asnTypeFunctionInherit.push_back("RemoveAllElements");
    asnTypeFunctionInherit.push_back("GetSize");
    asnTypeFunctionInherit.push_back("IsEmpty");
    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "SequenceOf", 
                                asnTypeFunctionInherit);

    HdrNewLine();
    HdrPrint(0, 
            "/*-------- Begin Nested Type --------*/\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "/*-------- Begin Nested Type --------*/\n");
    SrcNewLine();

    Type* type = sequenceOfType->GetSequenceOfType();

    string eltTypeName = AdaptName(GetGeneratedTypeName(type));

    if (IsAsnTypeName(eltTypeName))
    {
        string asnTypeNameLowercase = 
            AdaptNameToLowercase(eltTypeName);

        InsertOnceBasicIncludeList(asnTypeNameLowercase);
    }
    else
    {
        InsertOnceReferenceIncludeList(eltTypeName);
    }

    string eltBaseTypeName = AdaptName(GetGeneratedBaseTypeName(type));

    if (IsAsnTypeName(eltBaseTypeName))
    {
        string asnTypeNameLowercase = 
            AdaptNameToLowercase(eltBaseTypeName);

        InsertOnceBasicIncludeList(asnTypeNameLowercase);
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
            "/*-------- End Nested Type --------*/\n");
    HdrNewLine();
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "/*-------- End Nested Type --------*/\n");
    SrcNewLine();
    SrcNewLine();

    string scopedEltTypeName;

    if (type->GetType() == TYPE_DEFINED)
    {
        // Typical case of TYPE_CHOICE, TYPE_SEQUENCE and TYPE_SET.

        if (!IsAsnUsefulTypeName(GetGeneratedElementTypeName(type)))
        {
            scopedEltTypeName = moduleName;
            scopedEltTypeName.append("_");
            scopedEltTypeName.append(AdaptName(GetGeneratedElementTypeName(type)));
        }
        else
        {
            scopedEltTypeName = "ASN_";
            scopedEltTypeName.append(AdaptName(GetGeneratedElementTypeName(type)));
        }
    }
    else
    {
        // Typical case of TYPE_SEQUENCE_OF and TYPE_SET_OF.

        scopedEltTypeName = moduleName;
        scopedEltTypeName.append("_");
        scopedEltTypeName.append(GetScopeString());
        scopedEltTypeName.append(eltTypeName);
    }

    GenerateProtectedScopeComment();

    GenerateProtectedElementStaticDescription(type, eltTypeName);

    GenerateElementStaticDescription(type, eltTypeName);

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescSequenceOf description");

    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    HdrPrint(0,
            "int %s_AddElement(%s object, %s element);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedEltTypeName.c_str());

    SrcPrint(0,
            "int\n%s_AddElement(%s object, %s element)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedEltTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ASN_C_REQUIRE(object != NULL);\n");

    SrcPrint(1,
            "ASN_C_REQUIRE(element != NULL);\n");

    SrcNewLine();

    SrcPrint(1,
            "ASN_OBJECT_DESCRIPTION(element) = (ASN_DescObject)_%s_Get%sStaticDescription();\n",
            scopedTypeName.c_str(),
            eltTypeName.c_str());

    SrcNewLine();

    SrcPrint(1, 
            "return ASN_SEQUENCE_OF_CLASS_ADD_ELEMENT(ITS_OBJ_CLASS(object))((ASN_SequenceOf)object, (ASN_Object)element);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "const %s %s_GetElementAt(const %s object, size_t index);\n",
            scopedEltTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "const %s\n%s_GetElementAt(const %s object, size_t index)\n",
            scopedEltTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ASN_C_REQUIRE(object != NULL);\n");

    SrcNewLine();

    SrcPrint(1,
            "return (const %s)ASN_SEQUENCE_OF_CLASS_GET_ELEMENT_AT(ITS_OBJ_CLASS(object))((ASN_SequenceOf)object, index);\n",
            scopedEltTypeName.c_str());

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "size_t %s_GetSize(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "size_t\n%s_GetSize(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ASN_C_REQUIRE(object != NULL);\n");

    SrcNewLine();

    SrcPrint(1,
            "return ASN_SEQUENCE_OF_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))((ASN_SequenceOf)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    GenerateGetUniversalTagFunction("SequenceOf");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("SequenceOf");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "SequenceOf");

    GenerateTagAddLevelInstructions("SequenceOf");

    GenerateSetClauseOptionalInstructions("SequenceOf");

    GenerateSetClauseSizeInstructions("SequenceOf");

    SrcPrint(2,
            "ASN_DescSequenceOf_SetElement(description, (ASN_DescObject)_%s_Get%sStaticDescription());\n",
            scopedTypeName.c_str(),
            eltTypeName.c_str());
            
    SrcNewLine();

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                        scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                        scopedTypeName,
                                                        "SequenceOf");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();   

    ClearDestructElementStaticDescInstructionList();
}


void
GenerateCVisitor::VisitSequenceOfTypeType(Type* type)
{
    // Nothing to do.
}


void
GenerateCVisitor::VisitSequenceOfConstraint(Constraint* constraint)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitSetTypeBegin(SetType* setType)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitSetTypeEnd(SetType* setType)
{
    InsertOnceBasicIncludeList("asn_set");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetElements");
    asnTypeFunctionInherit.push_back("AddElement");
    asnTypeFunctionInherit.push_back("GetElementAt");
    asnTypeFunctionInherit.push_back("GetElementAtTag");
    asnTypeFunctionInherit.push_back("Contains");
    asnTypeFunctionInherit.push_back("ContainsTag");
    asnTypeFunctionInherit.push_back("RemoveElement");
    asnTypeFunctionInherit.push_back("RemoveElementTag");
    asnTypeFunctionInherit.push_back("RemoveAllElements");
    asnTypeFunctionInherit.push_back("GetSize");
    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "Set", 
                                asnTypeFunctionInherit);

    HdrNewLine();

    HdrPrint(0, 
            "/*-------- Begin Nested Type(s) --------*/\n");

    HdrNewLine();

    SrcNewLine();

    SrcPrint(0, 
            "/*-------- Begin Nested Type(s) --------*/\n");


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
            "/*-------- End Nested Type(s) --------*/\n");

    HdrNewLine();
    HdrNewLine();

    SrcNewLine();

    SrcPrint(0, 
            "/*-------- End Nested Type(s) --------*/\n");

    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    typeList = setType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            string adaptedName = AdaptName(namedType->GetName());

            GenerateProtectedElementStaticDescription(namedType, adaptedName);

            GenerateElementStaticDescription(namedType, adaptedName);
        }
    }

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string setSizeStr = GetVarArgsString("%d", setSize);

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back(setSizeStr);
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescSet description");

    actualArguments.push_back(setSizeStr);
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

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
                string asnTypeNameLowercase = 
                    AdaptNameToLowercase(adaptedGenTypeName);

                InsertOnceBasicIncludeList(asnTypeNameLowercase);
            }
            else
            {
                InsertOnceReferenceIncludeList(adaptedGenTypeName);
            }

            string adaptedGenBaseTypeName =
                AdaptName(GetGeneratedBaseTypeName(namedType));

            if (IsAsnTypeName(adaptedGenBaseTypeName))
            {
                string asnTypeNameLowercase = 
                    AdaptNameToLowercase(adaptedGenBaseTypeName);

                InsertOnceBasicIncludeList(asnTypeNameLowercase);
            }

            string adaptedElementTypeName =
                AdaptName(GetGeneratedElementTypeName(namedType));

            string scopedElementTypeName = "";

            if (namedType->GetType() == TYPE_DEFINED)
            {
                // Typical case of TYPE_CHOICE, TYPE_SEQUENCE and TYPE_SET.

                if (!IsAsnUsefulTypeName(GetGeneratedElementTypeName(namedType)))
                {
                    scopedElementTypeName = moduleName;
                    scopedElementTypeName.append("_");
                    scopedElementTypeName.append(AdaptName(GetGeneratedElementTypeName(namedType)));
                }
                else
                {
                    scopedElementTypeName = "ASN_";
                    scopedElementTypeName.append(AdaptName(GetGeneratedElementTypeName(namedType)));
                }
            }
            else
            {
                // Typical case of TYPE_SEQUENCE_OF and TYPE_SET_OF.

                scopedElementTypeName = moduleName;
                scopedElementTypeName.append("_");
                scopedElementTypeName.append(GetScopeString());
                scopedElementTypeName.append(adaptedName);
            }

            HdrPrint(0, 
                    "void %s_Set%s(%s object, %s element);\n", 
                    scopedTypeName.c_str(),
                    adaptedName.c_str(), 
                    scopedTypeName.c_str(),
                    scopedElementTypeName.c_str());

            SrcPrint(0, 
                    "void\n%s_Set%s(%s object, %s element)\n", 
                    scopedTypeName.c_str(),
                    adaptedName.c_str(), 
                    scopedTypeName.c_str(),
                    scopedElementTypeName.c_str());

            SrcPrint(0, 
                    "{\n");

            SrcPrint(1,
                    "ASN_C_REQUIRE(object != NULL);\n");

            SrcPrint(1, 
                    "ASN_C_REQUIRE(element != NULL);\n");

            SrcNewLine();

            SrcPrint(1,
                    "ASN_OBJECT_DESCRIPTION(element) = (ASN_DescObject)_%s_Get%sStaticDescription();\n",
                    scopedTypeName.c_str(),
                    adaptedName.c_str());

            SrcNewLine();

            SrcPrint(1, 
                    "ASN_SET_CLASS_ADD_ELEMENT(ITS_OBJ_CLASS(object))((ASN_Set)object, %d, (ASN_Object)element);\n",
                    index);

            SrcPrint(0, 
                    "}\n");

            SrcNewLine();

            if (namedType->IsOptional())
            {
                HdrPrint(0, 
                        "ITS_BOOLEAN %s_Option%s(const %s object);\n", 
                        scopedTypeName.c_str(),
                        adaptedName.c_str(),
                        scopedTypeName.c_str());

                SrcPrint(0, 
                        "ITS_BOOLEAN %s_Option%s(const %s object)\n", 
                        scopedTypeName.c_str(),
                        adaptedName.c_str(),
                        scopedTypeName.c_str());

                SrcPrint(0, 
                        "{\n");

                SrcPrint(1,
                        "ASN_C_REQUIRE(object != NULL);\n");

                SrcNewLine();

                SrcPrint(1,
                        "return ASN_SET_CLASS_CONTAINS(ITS_OBJ_CLASS(object))((ASN_Set)object, %d);\n",
                        index);

                SrcPrint(0, 
                        "}\n");

                SrcNewLine();
            }

            HdrPrint(0, 
                    "const %s %s_Get%s(const %s object);\n", 
                    scopedElementTypeName.c_str(),
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str());

            SrcPrint(0, 
                    "const %s\n%s_Get%s(const %s object)\n", 
                    scopedElementTypeName.c_str(),
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str());

            SrcPrint(0, 
                    "{\n");

            SrcPrint(1,
                    "ASN_C_REQUIRE(object != NULL);\n");

            if (namedType->IsOptional())
            {
            
                SrcPrint(1, 
                        "ASN_C_REQUIRE(%s_Option%s(object));\n", 
                        scopedTypeName.c_str(),
                        adaptedName.c_str());

                SrcNewLine();
            }

            SrcPrint(1, 
                    "return (const %s)ASN_SET_CLASS_GET_ELEMENT_AT(ITS_OBJ_CLASS(object))((ASN_Set)object, %d);\n",
                    scopedElementTypeName.c_str(), 
                    index);
            SrcPrint(0, 
                    "}\n");
            SrcNewLine();

            index++;
        }
    }

    GenerateGetUniversalTagFunction("Set");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("Set");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "Set");

    GenerateTagAddLevelInstructions("Set");

    GenerateSetClauseOptionalInstructions("Set");

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
                    "ASN_DescSet_AddElement(description, %d, (ASN_DescObject)_%s_Get%sStaticDescription());\n",
                    index, 
                    scopedTypeName.c_str(),
                    adaptedName.c_str());
            index++;
        }

        if (!(typeList->empty()))
        {
            SrcNewLine();
        }
    }

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                        scopedTypeName,
                                                        "Set");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();

    ClearDestructElementStaticDescInstructionList();
}


void
GenerateCVisitor::VisitSetTypeList(TypeList* typeList)
{


}


void 
GenerateCVisitor::VisitSetOfTypeBegin(SetOfType* setOfType)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitSetOfTypeEnd(SetOfType* setOfType)
{
    InsertOnceBasicIncludeList("asn_set_of");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetElements");
    asnTypeFunctionInherit.push_back("AddElement");
    asnTypeFunctionInherit.push_back("GetElementAt");
    asnTypeFunctionInherit.push_back("RemoveElement");
    asnTypeFunctionInherit.push_back("RemoveAllElements");
    asnTypeFunctionInherit.push_back("GetSize");
    asnTypeFunctionInherit.push_back("IsEmpty");
    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "SetOf", 
                                asnTypeFunctionInherit);

    HdrNewLine();
    HdrPrint(0, 
            "/*-------- Begin Nested Type --------*/\n");
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "/*-------- Begin Nested Type --------*/\n");
    SrcNewLine();

    Type* type = setOfType->GetSetOfType();

    string eltTypeName = AdaptName(GetGeneratedTypeName(type));

    if (IsAsnTypeName(eltTypeName))
    {
        string asnTypeNameLowercase = 
            AdaptNameToLowercase(eltTypeName);

        InsertOnceBasicIncludeList(asnTypeNameLowercase);
    }
    else
    {
        InsertOnceReferenceIncludeList(eltTypeName);
    }

    string eltBaseTypeName = AdaptName(GetGeneratedBaseTypeName(type));

    if (IsAsnTypeName(eltBaseTypeName))
    {
        string asnTypeNameLowercase = 
            AdaptNameToLowercase(eltBaseTypeName);

        InsertOnceBasicIncludeList(asnTypeNameLowercase);
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
            "/*-------- End Nested Type --------*/\n");
    HdrNewLine();
    HdrNewLine();

    SrcNewLine();
    SrcPrint(0, 
            "/*-------- End Nested Type --------*/\n");
    SrcNewLine();
    SrcNewLine();

    string scopedEltTypeName;

    if (type->GetType() == TYPE_DEFINED)
    {
        // Typical case of TYPE_CHOICE, TYPE_SEQUENCE and TYPE_SET.

        if (!IsAsnUsefulTypeName(GetGeneratedElementTypeName(type)))
        {
            scopedEltTypeName = moduleName;
            scopedEltTypeName.append("_");
            scopedEltTypeName.append(AdaptName(GetGeneratedElementTypeName(type)));
        }
        else
        {
            scopedEltTypeName = "ASN_";
            scopedEltTypeName.append(AdaptName(GetGeneratedElementTypeName(type)));
        }
    }
    else
    {
        // Typical case of TYPE_SEQUENCE_OF and TYPE_SET_OF.

        scopedEltTypeName = moduleName;
        scopedEltTypeName.append("_");
        scopedEltTypeName.append(GetScopeString());
        scopedEltTypeName.append(eltTypeName);
    }

    GenerateProtectedScopeComment();

    GenerateProtectedElementStaticDescription(type, eltTypeName);

    GenerateElementStaticDescription(type, eltTypeName);

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescSetOf description");

    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    HdrPrint(0,
            "int %s_AddElement(%s object, %s element);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedEltTypeName.c_str());

    SrcPrint(0,
            "int\n%s_AddElement(%s object, %s element)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedEltTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ASN_C_REQUIRE(object != NULL);\n");

    SrcPrint(1,
            "ASN_C_REQUIRE(element != NULL);\n");

    SrcNewLine();

    SrcPrint(1,
            "ASN_OBJECT_DESCRIPTION(element) = (ASN_DescObject)_%s_Get%sStaticDescription();\n",
            scopedTypeName.c_str(),
            eltTypeName.c_str());

    SrcNewLine();

    SrcPrint(1, 
            "return ASN_SET_OF_CLASS_ADD_ELEMENT(ITS_OBJ_CLASS(object))((ASN_SetOf)object, (ASN_Object)element);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "const %s %s_GetElementAt(const %s object, size_t index);\n",
            scopedEltTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "const %s\n%s_GetElementAt(const %s object, size_t index)\n",
            scopedEltTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ASN_C_REQUIRE(object != NULL);\n");

    SrcNewLine();

    SrcPrint(1,
            "return (const %s)ASN_SET_OF_CLASS_GET_ELEMENT_AT(ITS_OBJ_CLASS(object))((ASN_SetOf)object, index);\n",
            scopedEltTypeName.c_str());

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "size_t %s_GetSize(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "size_t\n%s_GetSize(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ASN_C_REQUIRE(object != NULL);\n");

    SrcNewLine();

    SrcPrint(1,
            "return ASN_SET_OF_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))((ASN_SetOf)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    GenerateGetUniversalTagFunction("SetOf");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("SetOf");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "SetOf");

    GenerateTagAddLevelInstructions("SetOf");

    GenerateSetClauseOptionalInstructions("SetOf");

    GenerateSetClauseSizeInstructions("SetOf");

    SrcPrint(2,
            "ASN_DescSetOf_SetElement(description, (ASN_DescObject)_%s_Get%sStaticDescription());\n",
            scopedTypeName.c_str(),
            eltTypeName.c_str());
            
    SrcNewLine();

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                        scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                        scopedTypeName,
                                                        "SetOf");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();   

    ClearDestructElementStaticDescInstructionList();
}


void
GenerateCVisitor::VisitSetOfTypeType(Type* type)
{
    // Nothing to do.
}


void
GenerateCVisitor::VisitSetOfConstraint(Constraint* constraint)
{
    // Nothing to do.
}


void 
GenerateCVisitor::VisitOctetStringType(OctetStringType* octetStringType)
{
    InsertOnceBasicIncludeList("asn_octet_string");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetArray");
    asnTypeFunctionInherit.push_back("SetArray");
    asnTypeFunctionInherit.push_back("GetSize");
    asnTypeFunctionInherit.push_back("GetUniversalTag");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "OctetString", 
                                asnTypeFunctionInherit);

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back("NULL");
    actualArguments.push_back("0");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("const ITS_OCTET* array");
    formalArguments.push_back("size_t size");

    actualArguments.push_back("array");
    actualArguments.push_back("size");
    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "WithArraySize", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescOctetString description");

    actualArguments.push_back("NULL");
    actualArguments.push_back("0");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("const ITS_OCTET* array");
    formalArguments.push_back("size_t size");
    formalArguments.push_back("ASN_DescOctetString description");

    actualArguments.push_back("array");
    actualArguments.push_back("size");
    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithArraySizeDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();
    
    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    HdrPrint(0,
            "const ITS_OCTET* %s_GetArray(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "const ITS_OCTET*\n%s_GetArray(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OCTET_STRING_CLASS_GET_ARRAY(ITS_OBJ_CLASS(object))((ASN_OctetString)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "size_t %s_GetSize(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "size_t\n%s_GetSize(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OCTET_STRING_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))((ASN_OctetString)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    HdrPrint(0,
            "int %s_SetArray(%s object, const ITS_OCTET* array, size_t size);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "int\n%s_SetArray(%s object, const ITS_OCTET* array, size_t size)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OCTET_STRING_CLASS_SET_ARRAY(ITS_OBJ_CLASS(object))((ASN_OctetString)object, array, size);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();

    GenerateGetUniversalTagFunction("OctetString");

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("OctetString");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "OctetString");

    GenerateTagAddLevelInstructions("OctetString");

    GenerateSetClauseOptionalInstructions("OctetString");

    GenerateSetClauseSizeInstructions("OctetString");

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "OctetString");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();
}


void
GenerateCVisitor::VisitDefinedType(DefinedType* definedType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string referenceTypeName = AdaptName(definedType->GetName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    SrcNewLine();

    InsertOnceReferenceIncludeList(referenceTypeName);

    string scopedReferenceTypeName = "";

    scopedReferenceTypeName.reserve(SIZE_TINY);

    if (!IsAsnUsefulTypeName(referenceTypeName))
    {
        scopedReferenceTypeName = moduleName;
        scopedReferenceTypeName.append("_");
        scopedReferenceTypeName.append(referenceTypeName);
    }
    else
    {
        scopedReferenceTypeName = "ASN_";
        scopedReferenceTypeName.append(referenceTypeName);
    }

    string typedefStr = "";

    typedefStr.reserve(SIZE_MEDIUM);

    typedefStr = GetLevelIndent(GetLevel());

    typedefStr += GetVarArgsString(
                            "typedef %s %s;\n",
                            scopedReferenceTypeName.c_str(),
                            scopedTypeName.c_str());

    vector<string> functionCoreNames;

    if (GetLevel() == 0)
    {
        functionCoreNames.push_back("ConstructDefault");
        functionCoreNames.push_back("ConstructWithDescription");
        functionCoreNames.push_back("Destruct");
        functionCoreNames.push_back("Clone");
        functionCoreNames.push_back("Equals");
        functionCoreNames.push_back("GetStaticDescription");
        functionCoreNames.push_back("DestructStaticDescription");
        functionCoreNames.push_back("Encode");
        functionCoreNames.push_back("Decode");
        functionCoreNames.push_back("GetName");
        functionCoreNames.push_back("GetBaseName");
        functionCoreNames.push_back("Print");
        functionCoreNames.push_back("ToString");
    }
    else
    {
        functionCoreNames.push_back("ConstructWithDescription");
    }

    Type* baseType = definedType->GetBaseType();

    switch (baseType->GetType())
    {
    case TYPE_BIT_STRING:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("ConstructWithArraySize");
            functionCoreNames.push_back("GetArray");
            functionCoreNames.push_back("SetArray");
            functionCoreNames.push_back("GetSize");
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_BOOLEAN:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("ConstructWithValue");
            functionCoreNames.push_back("GetValue");
            functionCoreNames.push_back("SetValue");
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }
 
        break;

    case TYPE_CHOICE:

        break;

    case TYPE_ENUMERATED:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("ConstructWithValue");
            functionCoreNames.push_back("GetValue");
            functionCoreNames.push_back("SetValue");
            functionCoreNames.push_back("GetValueFromValueName");
            functionCoreNames.push_back("GetValueNameFromValue");
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_INTEGER:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("ConstructWithValue");
            functionCoreNames.push_back("GetValue");
            functionCoreNames.push_back("SetValue");
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }
 
        break;

    case TYPE_NULL:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_OBJECT_IDENTIFIER:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("ConstructWithArraySize");
            functionCoreNames.push_back("GetArray");
            functionCoreNames.push_back("SetArray");
            functionCoreNames.push_back("GetSize");
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_OCTET_STRING:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("ConstructWithArraySize");
            functionCoreNames.push_back("GetArray");
            functionCoreNames.push_back("SetArray");
            functionCoreNames.push_back("GetSize");
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_BASE_STRING:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("ConstructWithArraySize");
            functionCoreNames.push_back("GetArray");
            functionCoreNames.push_back("SetArray");
            functionCoreNames.push_back("GetSize");
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_REAL:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("GetValue");
            functionCoreNames.push_back("SetValue");
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_SEQUENCE:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_SEQUENCE_OF:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_SET:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_SET_OF:

        if (GetLevel() == 0)
        {
            functionCoreNames.push_back("GetUniversalTag");
        }
        else
        {
            /* Nothing to do. */
        }

        break;

    case TYPE_ANY:

        break;

    case TYPE_ANY_DEFINED_BY:

        break;

    default:

        break;
    }

    typedefStr += GetTypedefDefineListString(
                            scopedTypeName,
                            scopedReferenceTypeName,
                            functionCoreNames);

    InsertOnceTypedefList(typedefStr);

    if (GetLevel() == 0)
    {
        GetHdr() += GetTypedefListString();

        GetTypedefList().clear();
    }

    SrcPrint(0, 
            "/* Type %s is a reference => no code generated. */\n",
            typeName.c_str());

    SrcNewLine();
}


void
GenerateCVisitor::VisitAnyType(AnyType* anyType)
{
    InsertOnceBasicIncludeList("asn_any");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetAny");
    asnTypeFunctionInherit.push_back("SetAny");
    asnTypeFunctionInherit.push_back("Contains");
    asnTypeFunctionInherit.push_back("ContainsAny");
    asnTypeFunctionInherit.push_back("IsDecoded");
    asnTypeFunctionInherit.push_back("GetDecodedTag");
    asnTypeFunctionInherit.push_back("GetDecodedLength");
    asnTypeFunctionInherit.push_back("GetDecodedOctets");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "Any", 
                                asnTypeFunctionInherit);

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescAny description");

    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();
    
    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("Any");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "Any");

    GenerateTagAddLevelInstructions("Any");

    GenerateSetClauseOptionalInstructions("Any");

    GenerateSetClauseAnyTagInstructions("Any");

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "Any");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();
}


void
GenerateCVisitor::VisitAnyDefinedByType(AnyDefinedByType* anyDefinedByType)
{
    InsertOnceBasicIncludeList("asn_any");

    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    vector<string> asnTypeFunctionInherit;

    asnTypeFunctionInherit.push_back("GetAny");
    asnTypeFunctionInherit.push_back("SetAny");
    asnTypeFunctionInherit.push_back("Contains");
    asnTypeFunctionInherit.push_back("ContainsAny");
    asnTypeFunctionInherit.push_back("IsDecoded");
    asnTypeFunctionInherit.push_back("GetDecodedTag");
    asnTypeFunctionInherit.push_back("GetDecodedLength");
    asnTypeFunctionInherit.push_back("GetDecodedOctets");

    GenerateTypeClassObjectBeginPart(
                                scopedTypeName, 
                                "Any", 
                                asnTypeFunctionInherit);

    GeneratePublicScopeComment();

    vector<string> formalArguments;
    vector<string> actualArguments;

    string getStaticDescriptionStr = 
        GetVarArgsString(
            "_%s_GetStaticDescription()", 
            scopedTypeName.c_str());

    actualArguments.push_back(getStaticDescriptionStr);

    GenerateConstructorFunction(
                            "Default", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();

    formalArguments.push_back("ASN_DescAny description");

    actualArguments.push_back("description");

    GenerateConstructorFunction(
                            "WithDescription", 
                            formalArguments, 
                            actualArguments);

    formalArguments.clear();
    actualArguments.clear();
    
    GenerateDestructorFunction();

    GenerateCloneFunction();

    GenerateEqualsFunction();

    GenerateEncodeFunction();

    GenerateDecodeFunction();

    GenerateGetNameFunction();

    GenerateGetBaseNameFunction();

    GeneratePrintFunction();

    GenerateToStringFunction();

    GenerateGetStaticDescriptionFunction("Any");

    GenerateDestructStaticDescriptionFunction();

    HdrNewLine();
    HdrNewLine();
    SrcNewLine();
    SrcNewLine();

    GenerateProtectedScopeComment();

    GenerateProtectedGetNameFunction();

    GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName, 
                                                    "Any");

    GenerateTagAddLevelInstructions("Any");

    GenerateSetClauseOptionalInstructions("Any");

    GenerateSetClauseAnyTagInstructions("Any");

    GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                    scopedTypeName);

    GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                    scopedTypeName,
                                                    "Any");

    GenerateProtectedDestructStaticDescriptionFunctionEndPart();

    GenerateTypeClassObjectEndPart();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GenerateCVisitor::VisitValueDefBegin(ValueDef* valueDef)
{

}


void
GenerateCVisitor::VisitValueDefMiddle(ValueDef* valueDef)
{

}


void
GenerateCVisitor::VisitValueDefEnd(ValueDef* valueDef)
{

}


void 
GenerateCVisitor::VisitValueDefType(ValueDef* valueDef, Type* type)
{
    // Must do nothing (i.e. must not generate code).
}


void 
GenerateCVisitor::VisitValueBegin(Value* value)
{

}


void 
GenerateCVisitor::VisitValueEnd(Value* value)
{

}


void
GenerateCVisitor::VisitBitStringValue(BitStringValue* bitStringValue)
{

}


void
GenerateCVisitor::VisitBooleanValue(BooleanValue* booleanValue)
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
GenerateCVisitor::VisitCharacterStringValue(
                            CharacterStringValue* characterStringValue)
{

}


void
GenerateCVisitor::VisitChoiceValue(ChoiceValue* choiceValue)
{

}


void
GenerateCVisitor::VisitEnumeratedValue(EnumeratedValue* enumeratedValue)
{

}


void
GenerateCVisitor::VisitIntegerValue(IntegerValue* integerValue)
{

}


void
GenerateCVisitor::VisitObjectIdentifierValue(
                            ObjectIdentifierValue* objectIdentifierValue)
{

}


void
GenerateCVisitor::VisitOctetStringValue(OctetStringValue* octetStringValue)
{

}


void
GenerateCVisitor::VisitMaxValue(MaxValue* maxValue)
{

}


void
GenerateCVisitor::VisitMinValue(MinValue* minValue)
{

}


void
GenerateCVisitor::VisitNullValue(NullValue* nullValue)
{

}


void
GenerateCVisitor::VisitRealValue(RealValue* realValue)
{

}


void 
GenerateCVisitor::VisitSequenceValueBegin(SequenceValue* sequenceValue)
{

}


void 
GenerateCVisitor::VisitSequenceValueEnd(SequenceValue* sequenceValue)
{

}


void 
GenerateCVisitor::VisitDefinedValue(DefinedValue* definedValue)
{

}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCVisitor::VisitNamedNumberBegin(NamedNumber* namedNumber)
{

}


void 
GenerateCVisitor::VisitNamedNumberEnd(NamedNumber* namedNumber)
{

}


void 
GenerateCVisitor::VisitTag(Tag* tag)
{

}


void 
GenerateCVisitor::VisitConstraintBegin(Constraint* constraint)
{

}


void 
GenerateCVisitor::VisitConstraintEnd(Constraint* constraint)
{

}


void
GenerateCVisitor::VisitSingleValueConstraintElementBegin(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{
    if (insideSizeConstraint)
    {
        string instruction = "SetClauseSize(description);\n";

        constraintInstructionList.push_back(instruction);

        Value* value = singleValueConstraintElement->GetValue();

        Value* baseValue = value->GetBaseValue();

        if (baseValue->GetValueType() == VALUE_INTEGER)
        {
            IntegerValue* integerValue =
                static_cast<IntegerValue*> (baseValue);

            instruction = "SetMinSize(description, ";
            instruction += LongToString(integerValue->GetValue());
            instruction += ");\n";

            constraintInstructionList.push_back(instruction);

            instruction = "SetMaxSize(description, ";
            instruction += LongToString(integerValue->GetValue());
            instruction += ");\n";

            constraintInstructionList.push_back(instruction);
        }
    }
}


void
GenerateCVisitor::VisitSingleValueConstraintElementEnd(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{

}


void
GenerateCVisitor::VisitValueRangeConstraintElementBegin(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{

}


void
GenerateCVisitor::VisitValueRangeConstraintElementMiddle(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{

}


void
GenerateCVisitor::VisitValueRangeConstraintElementEnd(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{
    if (insideSizeConstraint)
    {
        string instruction = "SetClauseSize(description);\n";

        constraintInstructionList.push_back(instruction);

        Value* lowerValue = valueRangeConstraintElement->GetLower();
        Value* upperValue = valueRangeConstraintElement->GetUpper();

        Value* lowerBaseValue = lowerValue->GetBaseValue();
        Value* upperBaseValue = upperValue->GetBaseValue();

        if (lowerBaseValue->GetValueType() == VALUE_INTEGER)
        {
            IntegerValue* integerValue =
                static_cast<IntegerValue*> (lowerBaseValue);

            instruction = "SetMinSize(description, ";
            instruction += LongToString(integerValue->GetValue());
            instruction += ");\n";

            constraintInstructionList.push_back(instruction);
        }

        if (lowerBaseValue->GetValueType() == VALUE_MIN)
        {
            instruction = "SetMinSize(description, LONG_MIN);\n";

            constraintInstructionList.push_back(instruction);
        }

        if (upperBaseValue->GetValueType() == VALUE_INTEGER)
        {
            IntegerValue* integerValue = 
                static_cast<IntegerValue*> (upperBaseValue);

            instruction = "SetMaxSize(description, ";
            instruction += LongToString(integerValue->GetValue());
            instruction += ");\n";

            constraintInstructionList.push_back(instruction);
        }

        if (upperBaseValue->GetValueType() == VALUE_MAX)
        {
            instruction = "SetMaxSize(description, LONG_MAX);\n";

            constraintInstructionList.push_back(instruction);
        }
    }
}


void GenerateCVisitor::VisitSizeConstraintElementBegin(
                            SizeConstraintElement* 
                                sizeConstraintElement)
{
    insideSizeConstraint = true;
}


void GenerateCVisitor::VisitSizeConstraintElementEnd(
                            SizeConstraintElement*
                                sizeConstraintElement)
{
    insideSizeConstraint = false;
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCVisitor::GenerateConstructorFunction(
                                            string nameSuffix,
                                            vector<string> formalArguments,
                                            vector<string> actualArguments)
{
    string scopedTypeName = GetScopeStringWithModule();


    string formalArgumentList = "";

    formalArgumentList.append("(");

    for (size_t i = 0; i < formalArguments.size(); i++)
    {
        formalArgumentList.append(formalArguments[i]);

        if (i + 1 >= formalArguments.size())
        {
            // Nothing to do.
        }
        else
        {
            formalArgumentList.append(", ");
        }
    }

    formalArgumentList.append(")");

    HdrPrint(0,
            "%s %s_Construct%s%s;\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            nameSuffix.c_str(),
            formalArgumentList.c_str());

    string actualArgumentList = "";

    for (size_t j = 0; j < actualArguments.size(); j++)
    {
        actualArgumentList.append(", ");

        actualArgumentList.append(actualArguments[j]);
    }

    SrcPrint(0,
            "%s\n%s_Construct%s%s\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            nameSuffix.c_str(),
            formalArgumentList.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "%s result = NULL;\n",
            scopedTypeName.c_str());

    SrcNewLine();

    for (size_t k = 0; k < actualArguments.size(); k++)
    {
        if (actualArguments[k] == "description")
        {
            SrcPrint(1,
                    "ASN_C_REQUIRE(description != NULL);\n");

            SrcNewLine();
        }
    }

    SrcPrint(1,
            "result = (%s)ITS_ConstructObject((ITS_Class)&its%s_ClassRec%s);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            actualArgumentList.c_str());

    SrcNewLine();

    SrcPrint(1,
            "ASN_C_ENSURE(result != NULL);\n");

    SrcNewLine();

    SrcPrint(1,
            "return result;\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateDestructorFunction()
{
    string scopedTypeName = GetScopeStringWithModule();

    HdrPrint(0,
            "void %s_Destruct(%s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "void\n%s_Destruct(%s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ITS_DestructObject((ITS_Object)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateCloneFunction()
{
    string scopedTypeName = GetScopeStringWithModule();

    HdrPrint(0,
            "%s %s_Clone(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "%s\n%s_Clone(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return (%s)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);\n",
            scopedTypeName.c_str());

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateEqualsFunction()
{
    string scopedTypeName = GetScopeStringWithModule();

    HdrPrint(0,
            "ITS_BOOLEAN %s_Equals(const %s object, const %s other);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "ITS_BOOLEAN\n%s_Equals(const %s object, const %s other)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateGetUniversalTagFunction(const string& asnTypeNameCore)
{
    string scopedTypeName = GetScopeStringWithModule();

    string asnTypeNameCoreUppercase =
        AdaptNameToUppercase(asnTypeNameCore);

    HdrPrint(0,
            "ASN_Tag %s_GetUniversalTag(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "ASN_Tag\n%s_GetUniversalTag(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_%s_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))((ASN_%s)object);\n",
            asnTypeNameCoreUppercase.c_str(),
            asnTypeNameCore.c_str());

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateEncodeFunction()
{
    string scopedTypeName = GetScopeStringWithModule();

    HdrPrint(0,
            "int %s_Encode(%s object, ASN_Octets* octets, ASN_EncodeError* encodeError);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "int\n%s_Encode(%s object, ASN_Octets* octets, ASN_EncodeError* encodeError)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateDecodeFunction()
{
    string scopedTypeName = GetScopeStringWithModule();

    HdrPrint(0,
            "int %s_Decode(%s object, ASN_Octets octets, ASN_DecodeError* decodeError);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "int\n%s_Decode(%s object, ASN_Octets octets, ASN_DecodeError* decodeError)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateGetNameFunction()
{
    string scopedTypeName = GetScopeStringWithModule();

    HdrPrint(0,
            "const char* %s_GetName(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "const char*\n%s_GetName(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateGetBaseNameFunction()
{
    string scopedTypeName = GetScopeStringWithModule();

    HdrPrint(0,
            "const char* %s_GetBaseName(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "const char*\n%s_GetBaseName(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GeneratePrintFunction()
{
    string scopedTypeName = GetScopeStringWithModule();

    HdrPrint(0,
            "void %s_Print(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "void\n%s_Print(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateToStringFunction()
{
    string scopedTypeName = GetScopeStringWithModule();

    HdrPrint(0,
            "char* %s_ToString(const %s object);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "char*\n%s_ToString(const %s object)\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);\n");

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void
GenerateCVisitor::GenerateGetStaticDescriptionFunction(const string& asnTypeNameCore)
{
    string scopedTypeName = GetScopeStringWithModule();

    string varArgsStr = "";

    varArgsStr = 
        GetVarArgsString(
            "ASN_Desc%s %s_GetStaticDescription()",
            asnTypeNameCore.c_str(),
            scopedTypeName.c_str());

    InsertGetStaticDescriptionInstructionList(varArgsStr);

    HdrPrint(0,
            "ASN_Desc%s %s_GetStaticDescription();\n",
            asnTypeNameCore.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "ASN_Desc%s\n%s_GetStaticDescription()\n",
            asnTypeNameCore.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return _%s_GetStaticDescription();\n",
            scopedTypeName.c_str());

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void
GenerateCVisitor::GenerateDestructStaticDescriptionFunction()
{
    string scopedTypeName = GetScopeStringWithModule();

    string varArgsStr = "";

    varArgsStr = 
        GetVarArgsString(
            "void %s_DestructStaticDescription()",
            scopedTypeName.c_str());

    InsertDestructStaticDescriptionInstructionList(varArgsStr);

    HdrPrint(0,
            "void %s_DestructStaticDescription();\n",
            scopedTypeName.c_str());

    SrcPrint(0,
            "void\n%s_DestructStaticDescription()\n",
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "_%s_DestructStaticDescription();\n",
            scopedTypeName.c_str());

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void
GenerateCVisitor::GenerateProtectedGetNameFunction()
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    SrcPrint(0,
            "static const char*\n_%s_GetName(const ASN_Object object)\n",
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return \"%s\";\n",
            scopedTypeName.c_str());

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateProtectedGetStaticDescriptionFunctionBeginPart(
                                                const string& scopedTypeName, 
                                                const string& asnTypeNameCore)
{
    string moduleName = AdaptName(GetCurrentModuleName());

    SrcPrint(0,
            "static ASN_Desc%s _%s_staticDescription = NULL;\n",
            asnTypeNameCore.c_str(),
            scopedTypeName.c_str());

    SrcNewLine();

    SrcPrint(0,
            "static ASN_Desc%s\n_%s_GetStaticDescription()\n",
            asnTypeNameCore.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0, 
            "{\n");

    SrcPrint(1, 
            "static ITS_BOOLEAN initialized = ITS_FALSE;\n");

    SrcPrint(1,
            "static ASN_Desc%s result = NULL;\n",
            asnTypeNameCore.c_str());

    SrcNewLine();

    SrcPrint(1,
            "ASN_Desc%s description = NULL;\n",
            asnTypeNameCore.c_str());

    SrcPrint(1,
            "%s cloneForFactory = NULL;\n",
            scopedTypeName.c_str());

    SrcNewLine();

    SrcPrint(1, 
            "if (initialized)\n");

    SrcPrint(1, 
            "{\n");

    SrcPrint(2, 
            "ASN_C_ENSURE(result != NULL);\n");

    SrcNewLine();

    SrcPrint(2, 
            "return result;\n");

    SrcPrint(1, 
            "}\n");

    SrcNewLine();

    SrcPrint(1, 
            "ASN_Lock();\n");

    SrcNewLine();

    SrcPrint(1, 
            "if (initialized)\n");

    SrcPrint(1, 
            "{\n");

    SrcPrint(2, 
            "ASN_Unlock();\n");

    SrcNewLine();

    SrcPrint(2, 
            "ASN_C_ENSURE(result != NULL);\n");

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
            "ASN_C_ASSERT(result == NULL);\n");

    SrcNewLine();

    Type* baseType = GetCurrentType()->GetBaseType();

    if (baseType->GetType() == TYPE_SEQUENCE ||
        baseType->GetType() == TYPE_SET)
    {
        // class SetType inherits from class SequenceType.

        SequenceType* sequenceType = 
            static_cast<SequenceType*> (baseType);

        TypeList* typeList = sequenceType->GetFlattenedTypeList();

        SrcPrint(2, 
                "_%s_staticDescription = ASN_Desc%s_ConstructWithSize(%d);\n", 
                scopedTypeName.c_str(),
                asnTypeNameCore.c_str(), 
                typeList->size());
    }
    else if (baseType->GetType() == TYPE_CHOICE)
    {
        ChoiceType* choiceType = 
            static_cast<ChoiceType*> (baseType);

        TypeList* typeList = choiceType->GetFlattenedTypeList();

        SrcPrint(2,
                "_%s_staticDescription = ASN_Desc%s_ConstructWithSize(%d);\n",
                scopedTypeName.c_str(),
                asnTypeNameCore.c_str(),
                typeList->size());
    }
    else if (baseType->GetType() == TYPE_ENUMERATED)
    {
        EnumeratedType* enumeratedType = 
            static_cast<EnumeratedType*> (baseType);

        NamedNumberList* namedNumberList = enumeratedType->GetNamedNumberList();

        SrcPrint(2,
                "_%s_staticDescription = ASN_Desc%s_ConstructWithSize(%d);\n",
                scopedTypeName.c_str(),
                asnTypeNameCore.c_str(),
                namedNumberList->size());
    }
    else
    {
        SrcPrint(2, 
                "_%s_staticDescription = ASN_Desc%s_ConstructDefault();\n",
                scopedTypeName.c_str(),
                asnTypeNameCore.c_str());
    }

    SrcNewLine();

    SrcPrint(2,
            "if (_%s_staticDescription == NULL)\n",
            scopedTypeName.c_str());

    SrcPrint(2,
            "{\n");

    SrcPrint(3,
            "ASN_Unlock();\n");

    SrcNewLine();

    SrcPrint(3,
            "return NULL;\n");

    SrcPrint(2,
            "}\n");

    SrcNewLine();

    SrcPrint(2,
            "cloneForFactory = %s_ConstructWithDescription(_%s_staticDescription);\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcNewLine();

    SrcPrint(2,
            "if (cloneForFactory == NULL)\n");

    SrcPrint(2,
            "{\n");

    SrcPrint(3,
            "ASN_Desc%s_Destruct(_%s_staticDescription);\n",
            asnTypeNameCore.c_str(),
            scopedTypeName.c_str());

    SrcPrint(3,
            "_%s_staticDescription = NULL;\n",
            scopedTypeName.c_str());

    SrcNewLine();

    SrcPrint(3,
            "ASN_Unlock();\n");

    SrcNewLine();

    SrcPrint(3,
            "return NULL;\n");

    SrcPrint(2,
            "}\n");

    SrcNewLine();

    SrcPrint(2,
            "ASN_Desc%s_SetCloneForFactory(_%s_staticDescription, (ASN_%s)cloneForFactory);\n",
            asnTypeNameCore.c_str(),
            scopedTypeName.c_str(),
            asnTypeNameCore.c_str());

    SrcNewLine();

    SrcPrint(2,
            "description = _%s_staticDescription;\n",
            scopedTypeName.c_str());

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateProtectedGetStaticDescriptionFunctionEndPart(
                                                const string& scopedTypeName)
{
    SrcNewLine();

    SrcPrint(2, 
            "result = _%s_staticDescription;\n",
            scopedTypeName.c_str());

    SrcNewLine();

    SrcPrint(2, 
            "initialized = ITS_TRUE;\n");

    SrcNewLine();

    SrcPrint(2, 
            "ASN_Unlock();\n");

    SrcNewLine();

    SrcPrint(2, 
            "ASN_C_ENSURE(result != NULL);\n");

    SrcNewLine();

    SrcPrint(2, 
            "return result;\n");

    SrcPrint(1, 
            "}\n");

    SrcPrint(0, 
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateTagAddLevelInstructions(
                                                const string& asnTypeNameCore)
{
    TagList* tagList = GetCurrentType()->GetAdjustedTagList();

    tagList->reverse();

    for (TagList::iterator tIter = tagList->begin();
         tIter != tagList->end();
         tIter++)
    {
        Tag* tag = *tIter;

        SrcPrint(2, 
                "ASN_Desc%s_TagAddLevel(description, ASN_Tag_ConstructWithClassTypeNumber(TAG_%s, TAG_%s, %d));\n",
                asnTypeNameCore.c_str(),
                tag->GetTagClassString().c_str(),
                tag->GetTagTypeString().c_str(),
                tag->GetNumber());
    }

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateSetClauseSizeInstructions(
                                                const string& asnTypeNameCore)
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
                "ASN_Desc%s_%s",
                asnTypeNameCore.c_str(),
                (*iter).c_str());
    }

    constraintInstructionList.clear();
}


void 
GenerateCVisitor::GenerateSetClauseOptionalInstructions(
                                                const string& asnTypeNameCore)
{
    if (GetCurrentType()->IsOptional())
    {
        SrcPrint(2, 
                "ASN_Desc%s_SetClauseOptional(description);\n",
                asnTypeNameCore.c_str());

        SrcNewLine();
    }
}


void 
GenerateCVisitor::GenerateSetClauseAnyTagInstructions(
                                                const string& asnTypeNameCore)
{
    TagList* tagList = GetCurrentType()->GetAdjustedTagList();

    if (tagList->empty())
    {
        SrcPrint(2, 
                "ASN_Desc%s_SetClauseAnyTag(description);\n",
                asnTypeNameCore.c_str());

        SrcNewLine();
    }
}


void 
GenerateCVisitor::GenerateProtectedDestructStaticDescriptionFunctionBeginPart(
                                                const string& scopedTypeName,
                                                const string& asnTypeNameCore)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());

    SrcPrint(0,
            "static void\n_%s_DestructStaticDescription()\n",
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "if (_%s_staticDescription != NULL)\n",
            scopedTypeName.c_str());

    SrcPrint(1,
            "{\n");

    SrcPrint(2,
            "ASN_Desc%s_Destruct(_%s_staticDescription);\n",
            asnTypeNameCore.c_str(),
            scopedTypeName.c_str());

    SrcPrint(2,
            "_%s_staticDescription = NULL;\n",
            scopedTypeName.c_str());

    SrcPrint(1,
            "}\n");

    SrcNewLine();

    //////////////////////////////////////////////////////////////////////////
    //
    // Begin printing of destruct element static description instruction list.
    //

    for (list<string>::iterator iter = 
         destructElementStaticDescInstructionList.begin();
         iter != destructElementStaticDescInstructionList.end();
         iter++)
    {
        string destructElementStaticDescInstruction = *iter;

        SrcPrint(0, destructElementStaticDescInstruction.c_str());
    }

    //
    // End printing of destruct element static description instruction list. 
    //
    ////////////////////////////////////////////////////////////////////////

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateProtectedDestructStaticDescriptionFunctionEndPart()
{

}


void 
GenerateCVisitor::GeneratePublicScopeComment()
{
    HdrPrint(0, 
            "/* Public interface. */\n");

    HdrNewLine();

    SrcPrint(0,
            "/* Public interface. */\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateProtectedScopeComment()
{
    HdrPrint(0, 
            "/* Protected interface. */\n");

    HdrNewLine();

    SrcPrint(0,
            "/* Protected interface. */\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateTypeClassObjectBeginPart(
                                const string& scopedTypeName, 
                                const string& asnTypeNameCore,
                                const vector<string>& asnTypeFunctionInherit)
{
    string moduleName = AdaptName(GetCurrentModuleName());

    HdrNewLine();
    HdrNewLine();

    HdrPrint(0,
            "/* Forward declarations. */\n");

    HdrNewLine();

    HdrPrint(0,
            "typedef struct _%s_ClassRec* %sClass;\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    HdrPrint(0,
            "typedef struct _%s_ObjectRec* %s;\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    HdrNewLine();
    HdrNewLine();

    HdrPrint(0,
            "/* %s class. */\n",
            scopedTypeName.c_str());

    HdrNewLine();

    HdrPrint(0,
            "typedef struct _%s_ClassRec\n",
            scopedTypeName.c_str());

    HdrPrint(0,
            "{\n");

    HdrPrint(1,
            "ITS_CoreClassPart coreClass;\n");

    HdrPrint(1,
            "ASN_Object_ClassPart asnObjectClass;\n");

    HdrPrint(1, 
            "ASN_%s_ClassPart asn%s;\n",
            asnTypeNameCore.c_str(),
            asnTypeNameCore.c_str());

    HdrPrint(0,
            "} %s_ClassRec;\n",
            scopedTypeName.c_str());

    HdrNewLine();
    HdrNewLine();

    HdrPrint(0,
            "/* %s object. */\n",
            scopedTypeName.c_str());

    HdrNewLine();

    HdrPrint(0,
            "typedef struct _%s_ObjectRec\n",
            scopedTypeName.c_str());

    HdrPrint(0,
            "{\n");

    HdrPrint(1,
            "ITS_CoreObjectPart core;\n");

    HdrPrint(1,
            "ASN_Object_ObjectPart asnObject;\n");

    HdrPrint(1, 
            "ASN_%s_ObjectPart asn%s;\n",
            asnTypeNameCore.c_str(),
            asnTypeNameCore.c_str());

    HdrPrint(0,
            "} %s_ObjectRec;\n",
            scopedTypeName.c_str());

    HdrNewLine();
    HdrNewLine();

    string scopedTypeNameUppercase = 
        AdaptNameToUppercase(scopedTypeName);

    HdrPrint(0,
            "#define %s_CLASS_NAME \"%s\"\n",
            scopedTypeNameUppercase.c_str(),
            scopedTypeName.c_str());

    HdrNewLine();
    HdrNewLine();

    SrcNewLine();
    SrcNewLine();

    SrcPrint(0,
            "/* Forward declarations. */\n");

    SrcNewLine();

    SrcPrint(0,
            "static const char* _%s_GetName(const ASN_Object object);\n",
            scopedTypeName.c_str());

    SrcPrint(0,
            "static ASN_Desc%s _%s_GetStaticDescription();\n",
            asnTypeNameCore.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "static void _%s_DestructStaticDescription();\n",
            scopedTypeName.c_str());

    Type* baseType = GetCurrentType()->GetBaseType();

    if (baseType->GetType() == TYPE_ENUMERATED)
    {
        SrcNewLine();

        SrcPrint(0,
                "static ITS_LONG _%s_GetValueFromValueName(const ASN_Enumerated object, const char* valueName);\n",
                scopedTypeName.c_str());

        SrcPrint(0,
                "static const char* _%s_GetValueNameFromValue(const ASN_Enumerated object, ITS_LONG value);\n",
                scopedTypeName.c_str());
    }

    SrcNewLine();
    SrcNewLine();

    SrcPrint(0,
            "/* %s class record. */\n",
            scopedTypeName.c_str());

    SrcNewLine();

    SrcPrint(0,
            "%s_ClassRec its%s_ClassRec =\n",
            scopedTypeName.c_str(),
            scopedTypeName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "/* Core class part. */\n");

    SrcNewLine();

    SrcPrint(1,
            "{\n");

    SrcPrint(2,
            "(ITS_Class)&itsASN_%s_ClassRec,\n",
            asnTypeNameCore.c_str());

    SrcPrint(2,
            "sizeof(%s_ObjectRec),\n",
            scopedTypeName.c_str());

    SrcPrint(2,
            "ITS_FALSE,\n");

    SrcPrint(2,
            "0,\n");

    SrcPrint(2,
            "%s_CLASS_NAME,\n",
            scopedTypeNameUppercase.c_str());

    SrcPrint(2,
            "ITS_CLASS_NO_INIT,\n");

    SrcPrint(2,
            "ITS_CLASS_NO_DEST,\n");

    SrcPrint(2,
            "ITS_CLASS_PART_NO_INIT,\n");

    SrcPrint(2,
            "ITS_CLASS_PART_NO_DEST,\n");

    SrcPrint(2,
            "ITS_INST_NO_CONST,\n");

    SrcPrint(2,
            "ITS_INST_NO_DEST,\n");

    SrcPrint(2,
            "ITS_INST_CLONE_INHERIT,\n");

    SrcPrint(2,
            "ITS_INST_PRINT_INHERIT,\n");

    SrcPrint(2,
            "ITS_INST_SERIAL_INHERIT,\n");

    SrcPrint(2,
            "ITS_INST_EQUALS_INHERIT,\n");

    SrcPrint(2,
            "ITS_INST_HASH_INHERIT,\n");

    SrcPrint(2,
            "NULL\n");

    SrcPrint(1,
            "},\n");

    SrcNewLine();

    SrcPrint(1,
            "/* ASN_Object class part. */\n");

    SrcNewLine();

    SrcPrint(1,
            "{\n");

    SrcPrint(2,
            "ASN_OBJECT_ENCODE_INHERIT,\n");

    SrcPrint(2,
            "ASN_OBJECT_DECODE_INHERIT,\n");

    SrcPrint(2,
            "_%s_GetName,\n",
            scopedTypeName.c_str());

    SrcPrint(2,
            "ASN_OBJECT_GET_BASE_NAME_INHERIT,\n");

    SrcPrint(2,
            "ASN_OBJECT_TO_STRING_INHERIT,\n");

    SrcPrint(2,
            "ASN_OBJECT_GET_ENCODE_EXTENDED_ERROR_TEXT_INHERIT,\n");

    SrcPrint(2,
            "ASN_OBJECT_GET_DECODE_EXTENDED_ERROR_TEXT_INHERIT,\n");

    SrcPrint(2,
            "ASN_OBJECT_ENCODE_TAG_LENGTH_VALUE_INHERIT,\n");

    SrcPrint(2,
            "ASN_OBJECT_DECODE_REMOVE_EXTRA_TAG_LENGTH_INHERIT,\n");

    SrcPrint(1,
            "},\n");

    SrcNewLine();

    SrcPrint(1,
            "/* ASN_%s class part. */\n",
            asnTypeNameCore.c_str());

    SrcNewLine();

    SrcPrint(1,
            "{\n");

    SrcPrint(2,
            "_%s_GetStaticDescription,\n",
            scopedTypeName.c_str());

    SrcPrint(2,
            "_%s_DestructStaticDescription,\n",
            scopedTypeName.c_str());

    for (size_t i = 0; i < asnTypeFunctionInherit.size(); i++)
    {
        string functionName = asnTypeFunctionInherit[i];

        string functionNameInherit = "";

        if (functionName == "GetValueFromValueName" || 
            functionName == "GetValueNameFromValue")
        {
            functionNameInherit = GetVarArgsString("_%s_", scopedTypeName.c_str());
            functionNameInherit.append(functionName);
        }
        else
        {
            string functionNameUppercase = AdaptNameToUppercase(functionName);

            string asnTypeNameCoreUppercase = AdaptNameToUppercase(asnTypeNameCore);

            functionNameInherit = 
                "ASN_" + 
                    asnTypeNameCoreUppercase + 
                        "_" + 
                            functionNameUppercase + 
                                "_INHERIT";
        }

        ASSERT(asnTypeFunctionInherit.size() > 0);

        if (i < asnTypeFunctionInherit.size() - 1)
        {
            SrcPrint(2, 
                    "%s,\n",
                    functionNameInherit.c_str());
        }
        else
        {
            SrcPrint(2,
                    "%s\n",
                    functionNameInherit.c_str());
        }
    }

    SrcPrint(1,
            "}\n");

    SrcPrint(0,
            "};\n");

    SrcNewLine();
    SrcNewLine();
}


void 
GenerateCVisitor::GenerateTypeClassObjectEndPart()
{
}


void 
GenerateCVisitor::GenerateElementStaticDescription(
                                        Type* elementType, 
                                        const string& elementName)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    Type* baseElementType = elementType->GetBaseType();

    string asnElementTypeName = GetGeneratedTypeName(baseElementType);

    string asnElementTypeNameCore = asnElementTypeName.substr(3);

    HdrPrint(0,
            "ASN_Desc%s %s_Get%sStaticDescription();\n",
            asnElementTypeNameCore.c_str(),
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcPrint(0,
            "ASN_Desc%s %s_Get%sStaticDescription()\n",
            asnElementTypeNameCore.c_str(),
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcPrint(0,
            "{\n");

    SrcPrint(1,
            "return _%s_Get%sStaticDescription();\n",
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcPrint(0,
            "}\n");

    SrcNewLine();
}


void 
GenerateCVisitor::GenerateProtectedElementStaticDescription(
                                        Type* elementType, 
                                        const string& elementName)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string scopedTypeName = GetScopeStringWithModule();

    Type* baseElementType = elementType->GetBaseType();

    string asnElementTypeName = GetGeneratedTypeName(baseElementType);

    string asnElementTypeNameCore = asnElementTypeName.substr(3);

    string asnDescElementTypeName = "ASN_Desc" + asnElementTypeNameCore;

    string elementTypeName = "";
    string scopedElementTypeName = "";

    if (elementType->GetType() == TYPE_DEFINED)
    {
        // Typical case of TYPE_CHOICE, TYPE_SEQUENCE and TYPE_SET.

        if (!IsAsnUsefulTypeName(GetGeneratedElementTypeName(elementType)))
        {
            elementTypeName = AdaptName(GetGeneratedElementTypeName(elementType));

            scopedElementTypeName = moduleName;
            scopedElementTypeName.append("_");
            scopedElementTypeName.append(AdaptName(GetGeneratedElementTypeName(elementType)));
        }
        else
        {
            elementTypeName = AdaptName(GetGeneratedElementTypeName(elementType));

            scopedElementTypeName = "ASN_";
            scopedElementTypeName.append(AdaptName(GetGeneratedElementTypeName(elementType)));
        }
    }
    else
    {
        // Typical case of TYPE_SEQUENCE_OF and TYPE_SET_OF.

        elementTypeName = elementName;

        scopedElementTypeName = moduleName;
        scopedElementTypeName.append("_");
        scopedElementTypeName.append(GetScopeString());
        scopedElementTypeName.append(elementName);
    }

    /////////////////////////////////////////////////
    //
    // Begin generation of destruct instruction list. 
    //

    string varArgsStr = "";
    string destructInstruction = "";

    varArgsStr = 
        GetVarArgsString(
            "    if (_%s_staticDescription%s != NULL)\n",
            scopedTypeName.c_str(),
            elementName.c_str());

    destructInstruction.append(varArgsStr);

    destructInstruction.append("    {\n");

    varArgsStr = 
        GetVarArgsString(
            "        ASN_Desc%s_Destruct(_%s_staticDescription%s);\n",
            asnElementTypeNameCore.c_str(),
            scopedTypeName.c_str(),
            elementName.c_str());

    destructInstruction.append(varArgsStr);

    varArgsStr =
        GetVarArgsString(
            "        _%s_staticDescription%s = NULL;\n",
            scopedTypeName.c_str(),
            elementName.c_str());

    destructInstruction.append(varArgsStr);

    destructInstruction.append("    }\n\n");


    InsertDestructElementStaticDescInstructionList(destructInstruction);

    //
    // End generation of destruct instruction list. 
    //
    ///////////////////////////////////////////////

    SrcPrint(0,
            "static ASN_Desc%s _%s_staticDescription%s = NULL;\n",
            asnElementTypeNameCore.c_str(),
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcNewLine();

    SrcPrint(0,
            "static ASN_Desc%s\n_%s_Get%sStaticDescription()\n",
            asnElementTypeNameCore.c_str(),
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcPrint(0, 
            "{\n");

    SrcPrint(1, 
            "static ITS_BOOLEAN initialized = ITS_FALSE;\n");

    SrcPrint(1,
            "static ASN_Desc%s result = NULL;\n",
            asnElementTypeNameCore.c_str());

    SrcNewLine();

    SrcPrint(1,
            "ASN_Desc%s description = NULL;\n",
            asnElementTypeNameCore.c_str());

    SrcPrint(1,
            "%s cloneForFactory = NULL;\n",
            scopedElementTypeName.c_str());

    SrcNewLine();

    SrcPrint(1, 
            "if (initialized)\n");

    SrcPrint(1, 
            "{\n");

    SrcPrint(2, 
            "ASN_C_ENSURE(result != NULL);\n");

    SrcNewLine();

    SrcPrint(2, 
            "return result;\n");

    SrcPrint(1, 
            "}\n");

    SrcNewLine();

    SrcPrint(1, 
            "ASN_Lock();\n");

    SrcNewLine();

    SrcPrint(1, 
            "if (initialized)\n");

    SrcPrint(1, 
            "{\n");

    SrcPrint(2, 
            "ASN_Unlock();\n");

    SrcNewLine();

    SrcPrint(2, 
            "ASN_C_ENSURE(result != NULL);\n");

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
            "ASN_C_ASSERT(result == NULL);\n");

    SrcNewLine();

    if (baseElementType->GetType() == TYPE_SEQUENCE ||
        baseElementType->GetType() == TYPE_SET)
    {
        // class SetType inherits from class SequenceType.

        SequenceType* sequenceType = 
            static_cast<SequenceType*> (baseElementType);

        TypeList* typeList = sequenceType->GetFlattenedTypeList();

        SrcPrint(2, 
                "_%s_staticDescription%s = ASN_Desc%s_ConstructWithSize(%d);\n", 
                scopedTypeName.c_str(),
                elementName.c_str(),
                asnElementTypeNameCore.c_str(), 
                typeList->size());
    }
    else if (baseElementType->GetType() == TYPE_CHOICE)
    {
        ChoiceType* choiceType = 
            static_cast<ChoiceType*> (baseElementType);

        TypeList* typeList = choiceType->GetFlattenedTypeList();

        SrcPrint(2,
                "_%s_staticDescription%s = ASN_Desc%s_ConstructWithSize(%d);\n",
                scopedTypeName.c_str(),
                elementName.c_str(),
                asnElementTypeNameCore.c_str(),
                typeList->size());
    }
    else if (baseElementType->GetType() == TYPE_ENUMERATED)
    {
        EnumeratedType* enumeratedType = 
            static_cast<EnumeratedType*> (baseElementType);

        NamedNumberList* namedNumberList = enumeratedType->GetNamedNumberList();

        SrcPrint(2,
                "_%s_staticDescription%s = ASN_Desc%s_ConstructWithSize(%d);\n",
                scopedTypeName.c_str(),
                elementName.c_str(),
                asnElementTypeNameCore.c_str(),
                namedNumberList->size());
    }
    else
    {
        SrcPrint(2, 
                "_%s_staticDescription%s = ASN_Desc%s_ConstructDefault();\n",
                scopedTypeName.c_str(),
                elementName.c_str(),
                asnElementTypeNameCore.c_str());
    }

    SrcNewLine();

    SrcPrint(2,
            "if (_%s_staticDescription%s == NULL)\n",
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcPrint(2,
            "{\n");

    SrcPrint(3,
            "ASN_Unlock();\n");

    SrcNewLine();

    SrcPrint(3,
            "return NULL;\n");

    SrcPrint(2,
            "}\n");

    SrcNewLine();

    SrcPrint(2,
            "cloneForFactory = %s_ConstructWithDescription(_%s_staticDescription%s);\n",
            scopedElementTypeName.c_str(),
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcNewLine();

    SrcPrint(2,
            "if (cloneForFactory == NULL)\n");

    SrcPrint(2,
            "{\n");

    SrcPrint(3,
            "ASN_Desc%s_Destruct(_%s_staticDescription%s);\n",
            asnElementTypeNameCore.c_str(),
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcPrint(3,
            "_%s_staticDescription%s = NULL;\n",
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcNewLine();

    SrcPrint(3,
            "ASN_Unlock();\n");

    SrcNewLine();

    SrcPrint(3,
            "return NULL;\n");

    SrcPrint(2,
            "}\n");

    SrcNewLine();

    SrcPrint(2,
            "ASN_Desc%s_SetCloneForFactory(_%s_staticDescription%s, (ASN_%s)cloneForFactory);\n",
            asnElementTypeNameCore.c_str(),
            scopedTypeName.c_str(),
            elementName.c_str(),
            asnElementTypeNameCore.c_str());

    SrcNewLine();

    SrcPrint(2,
            "description = _%s_staticDescription%s;\n",
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcNewLine();

    PushContext();

    // Do not want to change the level.
    SetLevel(GetLevel() - 1);

    SetCurrentType(elementType);

    switch (baseElementType->GetType())
    {
        case TYPE_SEQUENCE:
        case TYPE_SET:
        {
            if (baseElementType->GetType() == TYPE_SEQUENCE)
            {
                GenerateTagAddLevelInstructions("Sequence");

                GenerateSetClauseOptionalInstructions("Sequence");
            }
            else
            {
                GenerateTagAddLevelInstructions("Set");

                GenerateSetClauseOptionalInstructions("Set");
            }

            // Class SetType inherits from class SequenceType.

            SequenceType* sequenceType =
                static_cast<SequenceType*> (baseElementType);

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

                    if (baseElementType->GetType() == TYPE_SEQUENCE)
                    {
                        SrcPrint(2,
                                "ASN_DescSequence_AddElement(_%s_staticDescription%s, %d, (ASN_DescObject)%s_Get%sStaticDescription());\n",
                                scopedTypeName.c_str(),
                                elementName.c_str(),
                                index,
                                scopedElementTypeName.c_str(),
                                adaptedName.c_str());
                    }
                    else
                    {
                        SrcPrint(2,
                                "ASN_DescSet_AddElement(_%s_staticDescription%s, %d, (ASN_DescObject)%s_Get%sStaticDescription());\n",
                                scopedTypeName.c_str(),
                                elementName.c_str(),
                                index,
                                scopedElementTypeName.c_str(),
                                adaptedName.c_str());
                    }
                
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
            GenerateTagAddLevelInstructions("Choice");

            GenerateSetClauseOptionalInstructions("Choice");

            ChoiceType* choiceType =
                static_cast<ChoiceType*> (baseElementType);

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
                            "ASN_DescChoice_AddChoice(_%s_staticDescription%s, %d, (ASN_DescObject)%s_Get%sStaticDescription());\n",
                            scopedTypeName.c_str(),
                            elementName.c_str(),
                            index,
                            scopedElementTypeName.c_str(),
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

        case TYPE_SEQUENCE_OF:
        {
            GenerateTagAddLevelInstructions("SequenceOf");

            GenerateSetClauseOptionalInstructions("SequenceOf");

            // TODO: check if compiler should reapply sub-typing accross
            // references.

            SequenceOfType* sequenceOfType =
                static_cast<SequenceOfType*> (baseElementType);

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseElementType);

            GenerateSetClauseSizeInstructions("SequenceOf");

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
                    "ASN_DescSequenceOf_SetElement(_%s_staticDescription%s, (ASN_DescObject)%s_Get%sStaticDescription());\n",
                    scopedTypeName.c_str(),
                    elementName.c_str(),
                    scopedElementTypeName.c_str(),
                    typeName.c_str());
        
            SrcNewLine();
        }

        break;

        case TYPE_SET_OF:
        {
            GenerateTagAddLevelInstructions("SetOf");

            GenerateSetClauseOptionalInstructions("SetOf");

            // TODO: check if compiler should reapply sub-typing accross
            // references.

            SetOfType* setOfType = 
                static_cast<SetOfType*> (baseElementType);

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseElementType);

            GenerateSetClauseSizeInstructions("SetOf");

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
                    "ASN_DescSetOf_SetElement(_%s_staticDescription%s, (ASN_DescObject)%s_Get%sStaticDescription());\n",
                    scopedTypeName.c_str(),
                    elementName.c_str(),
                    scopedElementTypeName.c_str(),
                    typeName.c_str());
    
            SrcNewLine();
        }

        break;

        case TYPE_SELECTION:

            break;

        case TYPE_BOOLEAN:

            GenerateTagAddLevelInstructions("Boolean");

            GenerateSetClauseOptionalInstructions("Boolean");

            break;

        case TYPE_INTEGER:

            GenerateTagAddLevelInstructions("Integer");

            GenerateSetClauseOptionalInstructions("Integer");

            break;
 
        case TYPE_BIT_STRING:

            GenerateTagAddLevelInstructions("BitString");

            GenerateSetClauseOptionalInstructions("BitString");

            // TODO: check if compiler should reapply sub-typing accross
            // references.

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseElementType);

            GenerateSetClauseSizeInstructions("BitString");

            PopContext();
            SetLevel(GetLevel() + 1);

            break;

        case TYPE_OCTET_STRING:

            GenerateTagAddLevelInstructions("OctetString");

            GenerateSetClauseOptionalInstructions("OctetString");

            // TODO: check if compiler should reapply sub-typing accross
            // references.

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseElementType);

            GenerateSetClauseSizeInstructions("OctetString");

            PopContext();
            SetLevel(GetLevel() + 1);

            break;

        case TYPE_BASE_STRING:

            GenerateTagAddLevelInstructions("BaseString");

            GenerateSetClauseOptionalInstructions("BaseString");

            // TODO: check if compiler should reapply sub-typing accross
            // references.

            PushContext();
            SetLevel(GetLevel() - 1);
            SetCurrentType(baseElementType);

            GenerateSetClauseSizeInstructions("BaseString");

            PopContext();
            SetLevel(GetLevel() + 1);

            break;

        case TYPE_NULL:

            GenerateTagAddLevelInstructions("Null");

            GenerateSetClauseOptionalInstructions("Null");

            break;

        case TYPE_OBJECT_IDENTIFIER:

            GenerateTagAddLevelInstructions("ObjectIdentifier");

            GenerateSetClauseOptionalInstructions("ObjectIdentifier");

            break;

        case TYPE_REAL:

            GenerateTagAddLevelInstructions("Real");

            GenerateSetClauseOptionalInstructions("Real");

            break;

        case TYPE_ENUMERATED:
        {
            GenerateTagAddLevelInstructions("Enumerated");

            GenerateSetClauseOptionalInstructions("Enumerated");

            EnumeratedType* enumeratedType =
                static_cast<EnumeratedType*> (baseElementType);

            NamedNumberList* namedNumberList = enumeratedType->GetNamedNumberList();

            int index = 0;

            for (NamedNumberList::iterator iter = namedNumberList->begin();
                 iter != namedNumberList->end();
                 iter++)
            {
                NamedNumber* namedNumber = *iter;

                long value = namedNumber->GetNumber();

                SrcPrint(2,
                        "ASN_DescEnumerated_AddValue(_%s_staticDescription%s, %d, %d);\n",
                        scopedTypeName.c_str(),
                        elementName.c_str(),
                        index++,
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

            GenerateTagAddLevelInstructions("Any");

            GenerateSetClauseOptionalInstructions("Any");

            GenerateSetClauseAnyTagInstructions("Any");

            break;

        default:
            {
                bool must_not_be_reached = false;
                ASSERT(must_not_be_reached);
            }
    }

    SrcNewLine();

    SrcPrint(2, 
            "result = _%s_staticDescription%s;\n",
            scopedTypeName.c_str(),
            elementName.c_str());

    SrcNewLine();

    SrcPrint(2, 
            "initialized = ITS_TRUE;\n");

    SrcNewLine();

    SrcPrint(2, 
            "ASN_Unlock();\n");

    SrcNewLine();

    SrcPrint(2, 
            "ASN_C_ENSURE(result != NULL);\n");

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


void 
GenerateCVisitor::GenerateModuleItsFeatureClass()
{
    string moduleName = module->GetName();

    if (cModuleNameG != "")
    {
        moduleName = cModuleNameG;
    }

    string moduleNameAdapted = AdaptName(moduleName);

    string moduleNameUppercase = AdaptNameToUppercase(moduleName);

    string moduleNameLowercase = AdaptNameToLowercase(moduleName);

    string varArgsStr = "";

    ////////////////////////////////////////////////////////
    //
    // Header. 
    //

    HdrPrint(0, GetStandardHeaderString().c_str());

    HdrNewLine();

    HdrPrint(0, 
            "#if !defined(_C_%s_ITS_FEATURE_CLASS_H_)\n",
            moduleNameUppercase.c_str());

    HdrPrint(0, 
            "#define _C_%s_ITS_FEATURE_CLASS_H_\n",
            moduleNameUppercase.c_str());

    HdrPrint(0, "\n");
    HdrPrint(0, "#if _MSC_VER >= 1000\n");
    HdrPrint(0, "#pragma once\n");
    HdrPrint(0, "#endif // _MSC_VER >= 1000\n");
    HdrPrint(0, "\n");
    HdrPrint(0, "#include <asn_common.h>\n");
    HdrPrint(0, "\n");
    HdrPrint(0, "\n");
    HdrPrint(0, "#if defined(__cplusplus)\n");
    HdrPrint(0, "extern \"C\"\n");
    HdrPrint(0, "{\n");
    HdrPrint(0, "#endif /* defined(__cplusplus) */\n");
    HdrPrint(0, "\n");
    HdrPrint(0, "\n");

    HdrPrint(0, "/*\n");
    
    HdrPrint(0, 
            " *  Initialization/termination of %s module.\n",
            moduleNameUppercase.c_str());

    HdrPrint(0, " */\n");

    HdrNewLine();

    HdrPrint(0,
            "typedef ITS_ClassRec %s_ClassRec;\n",
            moduleNameUppercase.c_str());

    HdrNewLine();

    HdrPrint(0,
            "#define %s_CLASS_NAME \"its%s_Class\"\n",
            moduleNameUppercase.c_str(),
            moduleNameUppercase.c_str());

    HdrNewLine();

    HdrPrint(0,
            "extern %s_ClassRec its%s_ClassRec;\n",
            moduleNameUppercase.c_str(),
            moduleNameUppercase.c_str());

    HdrNewLine();

    HdrPrint(0,
            "extern ITS_Class its%s_Class;\n",
            moduleNameUppercase.c_str());

    HdrNewLine();
                   
    HdrPrint(0, "\n");
    HdrPrint(0, "\n");
    HdrPrint(0, "#if defined(__cplusplus)\n");
    HdrPrint(0, "}\n");
    HdrPrint(0, "#endif /* defined(__cplusplus) */\n");
    HdrPrint(0, "\n");
    HdrPrint(0, "\n");

    HdrPrint(0,
            "#endif /* !defined(_C_%s_ITS_FEATURE_CLASS_H_) */\n",
            moduleNameUppercase.c_str());

    HdrPrint(0, "\n");

    ////////////////////////////////////////////////////////
    //
    // Source. 
    //

    SrcPrint(0, GetStandardHeaderString().c_str());

    SrcNewLine();
    SrcNewLine();

    SrcPrint(0, "\n");

    SrcPrint(0, 
            "#include <%s_its_feature_class_c.h>\n",
            moduleNameLowercase.c_str());

    SrcPrint(0, "\n");
    SrcPrint(0, "#include <asn_desc_any.h>\n");
    SrcPrint(0, "#include <asn_desc_bit_string.h>\n");
    SrcPrint(0, "#include <asn_desc_boolean.h>\n");
    SrcPrint(0, "#include <asn_desc_choice.h>\n");
    SrcPrint(0, "#include <asn_desc_enumerated.h>\n");
    SrcPrint(0, "#include <asn_desc_integer.h>\n");
    SrcPrint(0, "#include <asn_desc_null.h>\n");
    SrcPrint(0, "#include <asn_desc_object_identifier.h>\n");
    SrcPrint(0, "#include <asn_desc_octet_string.h>\n");
    SrcPrint(0, "#include <asn_desc_real.h>\n");
    SrcPrint(0, "#include <asn_desc_sequence.h>\n");
    SrcPrint(0, "#include <asn_desc_sequence_of.h>\n");
    SrcPrint(0, "#include <asn_desc_set.h>\n");
    SrcPrint(0, "#include <asn_desc_set_of.h>\n");
    SrcPrint(0, "\n");
    SrcPrint(0, "\n");
    SrcPrint(0, "\n");

    SrcPrint(0, "/* Declarations. */\n");
    SrcPrint(0, "\n");

    list<string>::iterator iter;

    for (iter = getStaticDescriptionInstructionList.begin();
         iter != getStaticDescriptionInstructionList.end();
         iter++)
    {
        string getStaticDescriptionInstruction = *iter;

        SrcPrint(0,
                "%s;\n",
                getStaticDescriptionInstruction.c_str());
    }

    SrcNewLine();

    for (iter = destructStaticDescriptionInstructionList.begin();
         iter != destructStaticDescriptionInstructionList.end();
         iter++)
    {
        string destructStaticDescriptionInstruction = *iter;

        SrcPrint(0,
                "%s;\n",
                destructStaticDescriptionInstruction.c_str());
    }

    SrcNewLine();
    SrcNewLine();
    SrcNewLine();


    SrcPrint(0, "static int\n");
    SrcPrint(0, "ClassConstruct(ITS_Class objectClass)\n");
    SrcPrint(0, "{\n");
    SrcPrint(1, "void* result = ITS_SUCCESS;\n");
    SrcPrint(1, "\n");

    for (iter = getStaticDescriptionInstructionList.begin();
         iter != getStaticDescriptionInstructionList.end();
         iter++)
    {
        string getStaticDescriptionInstruction = *iter;

        string::size_type spacePos = getStaticDescriptionInstruction.find_first_of(' ');

        string getStaticDescriptionInstructionSubstr = 
            getStaticDescriptionInstruction.substr(spacePos + 1);

        SrcPrint(1,
                "result = %s;\n",
                getStaticDescriptionInstructionSubstr.c_str());

        SrcPrint(1, "\n");

        SrcPrint(1, "if (result == NULL)\n");
        SrcPrint(1, "{\n");
        SrcPrint(2, "return ITS_ENOMEM;\n");
        SrcPrint(1, "}\n");

        SrcPrint(1, "\n");
    }

    SrcPrint(1, "return ITS_SUCCESS;\n");

    SrcPrint(0, "}\n");

    SrcNewLine();

    SrcPrint(0, "static void\n");
    SrcPrint(0, "ClassDestruct(ITS_Class objectClass)\n");
    SrcPrint(0, "{\n");
    SrcPrint(1, "\n");

    for (iter = destructStaticDescriptionInstructionList.begin();
         iter != destructStaticDescriptionInstructionList.end();
         iter++)
    {
        string destructStaticDescriptionInstruction = *iter;

        string::size_type spacePos = destructStaticDescriptionInstruction.find_first_of(' ');

        string destructStaticDescriptionInstructionSubstr = 
            destructStaticDescriptionInstruction.substr(spacePos + 1);

        SrcPrint(1,
                "%s;\n",
                destructStaticDescriptionInstructionSubstr.c_str());

        SrcPrint(1, "\n");
    }

    SrcPrint(0, "}\n");

    SrcNewLine();
    SrcNewLine();

    SrcPrint(0, "/*\n");
 
    SrcPrint(0,
            " *  %s class record.\n",
            moduleNameUppercase.c_str());

    SrcPrint(0, " */\n");
    SrcPrint(0, "\n");

    SrcPrint(0, 
            "%s_ClassRec its%s_ClassRec =\n",
            moduleNameUppercase.c_str(),
            moduleNameUppercase.c_str());

    SrcPrint(0, "{\n");
    SrcPrint(1, "/* core part */\n");
    SrcPrint(1, "{\n");
    SrcPrint(2, "&itsCORE_ClassRec,\n");
    SrcPrint(2, "0,\n");
    SrcPrint(2, "ITS_FALSE,\n");
    SrcPrint(2, "0,\n");

    SrcPrint(2,
            "%s_CLASS_NAME,\n",
            moduleNameUppercase.c_str());

    SrcPrint(2, "ClassConstruct,\n");
    SrcPrint(2, "ClassDestruct,\n");
    SrcPrint(2, "ITS_CLASS_PART_NO_INIT,\n");
    SrcPrint(2, "ITS_CLASS_PART_NO_DEST,\n");
    SrcPrint(2, "ITS_INST_NO_CONST,\n");
    SrcPrint(2, "ITS_INST_NO_DEST,\n");
    SrcPrint(2, "ITS_INST_CLONE_INHERIT,\n");
    SrcPrint(2, "ITS_INST_PRINT_INHERIT,\n");
    SrcPrint(2, "ITS_INST_SERIAL_INHERIT,\n");
    SrcPrint(2, "ITS_INST_EQUALS_INHERIT,\n");
    SrcPrint(2, "NULL\n");
    SrcPrint(1, "}\n");
    SrcPrint(0, "};\n");

    SrcPrint(0, "\n");

    SrcPrint(0, 
            "ITS_Class its%s_Class = (ITS_Class)&its%s_ClassRec;\n",
            moduleNameUppercase.c_str(),
            moduleNameUppercase.c_str());

    SrcPrint(0, "\n");

    SrcNewLine();
    SrcNewLine();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCVisitor::HdrPrint(int n, const char* format, ...)
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
GenerateCVisitor::SrcPrint(int n, const char* format, ...)
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
GenerateCVisitor::GetVarArgsString(const char* format, ...)
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
GenerateCVisitor::GetLevelIndent(int level)
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
GenerateCVisitor::GetHdrHeaderString()
{
    string result;

    result.reserve(SIZE_MEDIUM);

    string moduleName = module->GetName();

    if (cModuleNameG != "")
    {
        moduleName = cModuleNameG;
    }

    string moduleNameAdapted = AdaptNameToUppercase(moduleName);

    string typeNameAdapted = AdaptNameToUppercase(GetCurrentTypeName());

    if (typeNameAdapted.size() == 0 || typeNameAdapted[0] != '_')
    {
        typeNameAdapted.insert(0, "_");
    }

    result.append(GetStandardHeaderString());
    result.append(GetVarArgsString("#if !defined(_C_%s%s_H_)\n",
                                   moduleNameAdapted.c_str(),
                                   typeNameAdapted.c_str()));
    result.append(GetVarArgsString("#define _C_%s%s_H_\n",
                                   moduleNameAdapted.c_str(),
                                   typeNameAdapted.c_str()));

    result.append("\n");
    result.append("#if _MSC_VER >= 1000\n");
    result.append("#pragma once\n");
    result.append("#endif // _MSC_VER >= 1000\n");
    result.append("\n");
    result.append("#include <asn_common.h>\n");
    result.append("#include <asn_object.h>\n");
    result.append("#include <asn_desc_object.h>\n");
    result.append("#include <asn_error.h>\n");
    result.append("\n");
    result.append(GetBasicIncludeListString());
    result.append(GetReferenceIncludeListString());
    result.append("\n");
    result.append("\n");
    result.append("#if defined(__cplusplus)\n");
    result.append("extern \"C\"\n");
    result.append("{\n");
    result.append("#endif /* defined(__cplusplus) */\n");
    result.append("\n");

    return result;
}


string 
GenerateCVisitor::GetHdrEndString()
{
    string result;

    result.reserve(SIZE_SMALL);

    string moduleName = module->GetName();

    if (cModuleNameG != "")
    {
        moduleName = cModuleNameG;
    }

    string moduleNameAdapted = AdaptNameToUppercase(moduleName);
    string typeNameAdapted = AdaptNameToUppercase(GetCurrentTypeName());

    if (typeNameAdapted.size() == 0 || typeNameAdapted[0] != '_')
    {
        typeNameAdapted.insert(0, "_");
    }

    result.append("\n");
    result.append("\n");
    result.append("#if defined(__cplusplus)\n");
    result.append("}\n");
    result.append("#endif /* defined(__cplusplus) */\n");
    result.append("\n");
    result.append("\n");
    result.append(GetVarArgsString("#endif /* !defined(_C_%s%s_H_) */\n",
                                   moduleNameAdapted.c_str(),
                                   typeNameAdapted.c_str()));
    result.append("\n");

    return result;
}


string 
GenerateCVisitor::GetSrcHeaderString()
{
    string result;

    result.reserve(SIZE_TINY);

    string moduleName = GetCurrentModuleName();

    string fileNameCore = "";

    fileNameCore.append(moduleName);
    fileNameCore.append("_");
    fileNameCore.append(AdaptName(GetCurrentTypeName()));
    fileNameCore = AdaptNameToLowercase(fileNameCore);
    fileNameCore.append("_c");

    result.append(GetStandardHeaderString());
    result.append(
            GetVarArgsString(
                    "#include <%s.h>\n", 
                    fileNameCore.c_str()));
    result.append("\n");
    result.append(GetBasicDescIncludeListString());
    result.append("\n");
    result.append("\n");

    return result;
}


string 
GenerateCVisitor::GetSrcEndString()
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
GenerateCVisitor::GetStandardHeaderString()
{
    string result;

    result.reserve(SIZE_SMALL);

    result.append("/*\n");
    result.append(
        " * Generated by IntelliAsnCC ASN.1 compiler (C, C++, Java).\n");
    result.append(" *\n");
    result.append(" * Do not edit!\n");
    result.append(" *\n");
    result.append(" *\n");
    result.append(" *\n");
    result.append(
        " * (C) 2000, 2001 IntelliNet Technologies Inc. All Rights Reserved.\n");
    result.append(" *\n");
    result.append(" */\n");
    result.append("\n");
    result.append("\n");

    return result;
}


string 
GenerateCVisitor::GetScopeString()
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
        result.append("_");
    }

    return result;
}


string
GenerateCVisitor::GetScopeStringWithModule()
{
    list<string> typeNameList(typeNameStack);

    typeNameList.push_front(GetCurrentTypeName());

    typeNameList.reverse();

    string moduleName = AdaptName(GetCurrentModuleName());

    string result = moduleName;

    for (list<string>::iterator iter = typeNameList.begin();
         iter != typeNameList.end();
         iter++)
    {
        string str = *iter;

        result.append("_");
        result.append(AdaptName(str));
    }

    return result;
}


string 
GenerateCVisitor::GetBasicIncludeListString()
{
    string result;

    result.reserve(SIZE_SMALL);

    for (list<string>::iterator iter = basicIncludeList.begin();
         iter != basicIncludeList.end();
         iter++)
    {
        string str = *iter;

        result.append("#include <");
        result.append(str);
        result.append(".h>\n");
    }

    if (!basicIncludeList.empty())
    {
        result.append("\n");
    }

    return result;
}


string 
GenerateCVisitor::GetBasicDescIncludeListString()
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
        string asnTypeName = str;

        if (asnTypeName.substr(0, 3) == "asn")
        {
            asnDescTypeName = asnTypeName;
            asnDescTypeName.insert(3, "_desc");
        }
        else
        {
            asnDescTypeName = "asn_desc_unknown";
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
GenerateCVisitor::GetReferenceIncludeListString()
{
    string result;

    result.reserve(SIZE_SMALL);

    string moduleName = GetCurrentModuleName();

    for (list<string>::iterator iter = referenceIncludeList.begin();
         iter != referenceIncludeList.end();
         iter++)
    {
        string str = *iter;

        string fileNameCore = "";

        if (IsAsnUsefulTypeName(str))
        {
            fileNameCore.append("asn_");
            fileNameCore.append(AdaptNameToLowercase(str));
            fileNameCore.append("_c");
        }
        else
        {
            fileNameCore.append(moduleName);
            fileNameCore.append("_");
            fileNameCore.append(AdaptName(str));
            fileNameCore = AdaptNameToLowercase(fileNameCore);
            fileNameCore.append("_c");
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
GenerateCVisitor::GetTypedefListString()
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


string 
GenerateCVisitor::GetTypedefDefineListString(
                    const string& scopedTypeName,
                    const string& scopedReferenceTypeName,
                    const vector<string>& functionCoreNames)
{
    string result;

    result.reserve(SIZE_MEDIUM);

    for (size_t i = 0; i < functionCoreNames.size(); i++)
    {
        string functionCoreName = functionCoreNames[i];

        result += GetLevelIndent(GetLevel());

        result += GetVarArgsString(
                        "#define %s_%s %s_%s\n",
                        scopedTypeName.c_str(),
                        functionCoreName.c_str(),
                        scopedReferenceTypeName.c_str(),
                        functionCoreName.c_str());
    }

    return result;
}


//
// Return generated type name (e.g. "AsnSequence", "AsnInteger") or name if
// DefinedType.
//

string 
GenerateCVisitor::GetGeneratedTypeName(Type* type)
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
GenerateCVisitor::GetGeneratedBaseTypeName(Type* type)
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
GenerateCVisitor::GetGeneratedElementTypeName(Type* type)
{
    REQUIRE(type != NULL);
    REQUIRE(type->IsNamed() || type->GetType() == TYPE_DEFINED);

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
// Return true if ASN type name.
//

bool 
GenerateCVisitor::IsAsnTypeName(const string& typeName)
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
GenerateCVisitor::IsAsnUsefulTypeName(const string& typeName)
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
GenerateCVisitor::InsertOnceBasicIncludeList(const string& str)
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
GenerateCVisitor::InsertOnceReferenceIncludeList(const string& str)
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
GenerateCVisitor::InsertOnceTypedefList(const string& str)
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
GenerateCVisitor::PushContext()
{
    typeStack.push_front(currentType);
    typeNameStack.push_front(currentTypeName);

    level = level + 1;
}


void 
GenerateCVisitor::PopContext()
{
    currentType     = typeStack.front();
    currentTypeName = typeNameStack.front();

    typeStack.pop_front();
    typeNameStack.pop_front();

    level = level - 1;
}
