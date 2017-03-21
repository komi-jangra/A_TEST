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
//  ID: $Id: asncc_generate_c_xml_doc_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>

#include <asncc_generate_c_xml_doc_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)



////////////////////////////////////////////////////////////////////////////////
//
//  GenerateCXmlDocVisitor implementation.
//

void 
GenerateCXmlDocVisitor::VisitModuleBegin(Module* moduleParam)
{
    REQUIRE(moduleParam != NULL);

    string moduleName = moduleParam->GetName();

    if (xmlModuleNameG != "")
    {
        moduleName = xmlModuleNameG;
    }

    SetCurrentModuleName(moduleName);
}


void 
GenerateCXmlDocVisitor::VisitModuleEnd(Module* moduleParam)
{
    REQUIRE(moduleParam != NULL);

    GenerateXmlAsnModuleSummary();

    GenerateXmlAsnModuleClassList();

    GenerateXmlAsnModuleMakeHtml();
}


void 
GenerateCXmlDocVisitor::VisitImportedModule(ImportedModule* importedModule)
{
    REQUIRE(importedModule != NULL);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCXmlDocVisitor::VisitTypeDefBegin(TypeDef* typeDef)
{
    // Cleaning of contents (xml source).

    GetXml().erase(GetXml().begin(), GetXml().end());


    SetCurrentTypeDef(typeDef);
    SetCurrentType(typeDef->GetType());
    SetCurrentTypeName(typeDef->GetDefinedName());
    SetLevel(0); // Module types are at level zero.
}


void 
GenerateCXmlDocVisitor::VisitTypeDefEnd(TypeDef* typeDef)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitTypeBegin(Type* type)
{
    SetCurrentType(type);

    constraintInstructionList.clear();
}


void 
GenerateCXmlDocVisitor::VisitTypeEnd(Type* type)
{
    switch (type->GetType())
    {
    case TYPE_BIT_STRING:
    case TYPE_BOOLEAN:
    case TYPE_CHARACTER_STRING:
    case TYPE_CHOICE:
    case TYPE_EMBEDDED_PDV:
    case TYPE_ENUMERATED:
    case TYPE_INTEGER:
    case TYPE_NULL:
    case TYPE_OBJECT_IDENTIFIER:
    case TYPE_OCTET_STRING:
    case TYPE_REAL:
    case TYPE_SEQUENCE:
    case TYPE_SEQUENCE_OF:
    case TYPE_SET:
    case TYPE_SET_OF:
    case TYPE_USEFUL:
    case TYPE_ANY:
    case TYPE_ANY_DEFINED_BY:
    {
        string moduleName = GetCurrentModuleName();

        moduleName = AdaptNameToLowercase(moduleName);

        string fileNameCore     = "";

        fileNameCore.append(moduleName);
        fileNameCore.append("_");
        fileNameCore.append(GetScopeUnderscoreString());

        fileNameCore = AdaptNameToLowercase(fileNameCore);

        string directoryName = moduleName + "_c_doc";

        WriteTextToFile(
                    directoryName,
                    fileNameCore,
                    "xml",
                    GetXml());

        break;
    }

    default:
        // Nothing to do.
        break;
    }
}


void
GenerateCXmlDocVisitor::VisitTypeDefaultValue(Type* type, Value* value)
{   

}


void 
GenerateCXmlDocVisitor::VisitBitStringTypeBegin(BitStringType* bitStringType)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitBitStringTypeEnd(BitStringType* bitStringType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnBitString",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    // Member functions XML doc generation.

    XmlNewLine();

    GenerateXmlBeginTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    NamedNumberList* namedNumberList = bitStringType->GetNamedNumberList();

    for (NamedNumberList::iterator iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string definedName = AdaptName(namedNumber->GetName());

        // Generate XML elements for "memberFunctionSet".

        GenerateXmlBeginTag("memberFunctionSet");

        XmlNewLine();

        GenerateXmlElement(
            "name", 
            GetVarArgsString(
                "%s_Set%s",
                scopedTypeName.c_str(),
                definedName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "void %s_Set%s(%s object, ITS_BOOLEAN value)",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "bitName",
            definedName);

        XmlNewLine();

        GenerateXmlEndTag("memberFunctionSet");

        XmlNewLine();
        XmlNewLine();

        // Generate XML elements for "memberFunctionReset".

        GenerateXmlBeginTag("memberFunctionReset");

        XmlNewLine();

        GenerateXmlElement(
            "name", 
            GetVarArgsString(
                "%s_Reset%s",
                scopedTypeName.c_str(),
                definedName.c_str()));


        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "void %s_Reset%s(%s object)",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "bitName",
            definedName);

        XmlNewLine();

        GenerateXmlEndTag("memberFunctionReset");

        XmlNewLine();
        XmlNewLine();

        // Generate XML elements for "memberFunctionIsSet".

        GenerateXmlBeginTag("memberFunctionIsSet");

        XmlNewLine();

        GenerateXmlElement(
            "name", 
            GetVarArgsString(
                "%s_Is%sSet",
                scopedTypeName.c_str(),
                definedName.c_str()));


        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "ITS_BOOLEAN %s_Is%sSet(const %s object)",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "bitName",
            definedName);

        XmlNewLine();

        GenerateXmlEndTag("memberFunctionIsSet");

        XmlNewLine();
        XmlNewLine();

        // Generate XML elements for "memberFunctionIsDefined".

        GenerateXmlBeginTag("memberFunctionIsDefined");

        XmlNewLine();

        GenerateXmlElement(
            "name", 
            GetVarArgsString(
                "%s_Is%sDefined",
                scopedTypeName.c_str(),
                definedName.c_str()));


        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "ITS_BOOLEAN %s_Is%sDefined(const %s object)",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "bitName",
            definedName);

        XmlNewLine();
    
        GenerateXmlEndTag("memberFunctionIsDefined");

        XmlNewLine();
        XmlNewLine();
    }

    GenerateXmlEndTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnBitString");
}


void 
GenerateCXmlDocVisitor::VisitBooleanType(BooleanType* booleanType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnBoolean",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnBoolean");
}


void 
GenerateCXmlDocVisitor::VisitChoiceTypeBegin(ChoiceType* choiceType)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitChoiceTypeEnd(ChoiceType* choiceType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnChoice",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    ////////// Begin Nested Type(s) //////////

    TypeList* typeList = choiceType->GetFlattenedTypeList();

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            PushContext();

            SetCurrentTypeName(namedType->GetName());

            SetCurrentType(namedType);

            // Generate subordinate type.

            namedType->Accept(this);

            PopContext();
        }
    }

    ////////// End Nested Type(s) //////////

    // Member functions XML doc generation.

    XmlNewLine();

    GenerateXmlBeginTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

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

            string adaptedGenBaseTypeName =
                AdaptName(GetGeneratedBaseTypeName(namedType));

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

            // Generate XML elements for "memberFunctionSetChoice".

            GenerateXmlBeginTag("memberFunctionSetChoice");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "%s_SetChoice%s",
                    scopedTypeName.c_str(),
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "void %s_SetChoice%s(%s object, %s choice)",
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str(),
                    scopedElementTypeName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "choiceName",
                adaptedName);

            XmlNewLine();

            GenerateXmlElement(
                "asnChoiceName",
                namedType->GetName());

            XmlNewLine();

            GenerateXmlElement(
                "choiceTypeName",
                scopedElementTypeName);

            XmlNewLine();

            GenerateXmlEndTag("memberFunctionSetChoice");

            XmlNewLine();
            XmlNewLine();

            // Generate XML elements for "memberFunctionGetChoice".

            GenerateXmlBeginTag("memberFunctionGetChoice");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "%s_GetChoice%s",
                    scopedTypeName.c_str(),
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "const %s %s_GetChoice%s(const %s object)",
                    scopedElementTypeName.c_str(),
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "choiceName",
                adaptedName);

            XmlNewLine();

            GenerateXmlElement(
                "asnChoiceName",
                namedType->GetName());

            XmlNewLine();

            GenerateXmlElement(
                "choiceTypeName",
                scopedElementTypeName);

            XmlNewLine();

            GenerateXmlEndTag("memberFunctionGetChoice");

            XmlNewLine();
            XmlNewLine();

            // Generate XML elements for "memberFunctionChoice".

            GenerateXmlBeginTag("memberFunctionChoice");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "%s_Choice%s",
                    scopedTypeName.c_str(),
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "ITS_BOOLEAN %s_Choice%s(const %s object)",
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "choiceName",
                adaptedName);

            XmlNewLine();

            GenerateXmlElement(
                "asnChoiceName",
                namedType->GetName());

            XmlNewLine();

            GenerateXmlElement(
                "choiceTypeName",
                scopedElementTypeName);

            XmlNewLine();

            GenerateXmlEndTag("memberFunctionChoice");

            XmlNewLine();
            XmlNewLine();
        }
    }

    GenerateXmlEndTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnChoice");
}


void
GenerateCXmlDocVisitor::VisitChoiceTypeList(TypeList* typeList)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitEnumeratedTypeBegin(EnumeratedType* enumeratedType)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitEnumeratedTypeEnd(EnumeratedType* enumeratedType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnEnumerated",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    // Member functions XML doc generation.

    XmlNewLine();

    GenerateXmlBeginTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    NamedNumberList* namedNumberList = enumeratedType->GetNamedNumberList();

    for (NamedNumberList::iterator iter = namedNumberList->begin();
         iter != namedNumberList->end();
         iter++)
    {
        NamedNumber* namedNumber = *iter;

        string definedName = AdaptName(namedNumber->GetName());

        // Generate XML elements for "memberFunctionSet".

        GenerateXmlBeginTag("memberFunctionSet");

        XmlNewLine();

        GenerateXmlElement(
            "name", 
            GetVarArgsString(
                "%s_Set%s",
                scopedTypeName.c_str(),
                definedName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "void %s_Set%s(%s object)",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "enumItemName",
            definedName);

        XmlNewLine();

        GenerateXmlEndTag("memberFunctionSet");

        XmlNewLine();
        XmlNewLine();

        // Generate XML elements for "memberFunctionIs".

        GenerateXmlBeginTag("memberFunctionIs");

        XmlNewLine();

        GenerateXmlElement(
            "name", 
            GetVarArgsString(
                "%s_Is%s",
                scopedTypeName.c_str(),
                definedName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "signature", 
            GetVarArgsString(
                "ITS_BOOLEAN %s_Is%s(const %s object)",
                scopedTypeName.c_str(),
                definedName.c_str(),
                scopedTypeName.c_str()));

        XmlNewLine();

        GenerateXmlElement(
            "enumItemName",
            definedName);

        XmlNewLine();

        GenerateXmlEndTag("memberFunctionIs");

        XmlNewLine();
        XmlNewLine();
    }

    GenerateXmlEndTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnEnumerated");
}


void 
GenerateCXmlDocVisitor::VisitIntegerTypeBegin(IntegerType* integerType)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitIntegerTypeEnd(IntegerType* integerType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnInteger",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnInteger");
}


void
GenerateCXmlDocVisitor::VisitObjectIdentifierType(
                                ObjectIdentifierType* objectIdentifierType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnObjectIdentifier",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnObjectIdentifier");
}


void
GenerateCXmlDocVisitor::VisitNullType(NullType* nullType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnNull",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnNull");
}


void
GenerateCXmlDocVisitor::VisitRealType(RealType* realType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnReal",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnReal");
}


void 
GenerateCXmlDocVisitor::VisitSequenceTypeBegin(SequenceType* sequenceType)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitSequenceTypeEnd(SequenceType* sequenceType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnSequence",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    ////////// Begin Nested Type(s) //////////

    TypeList* typeList = sequenceType->GetFlattenedTypeList();

    int sequenceSize = 0;

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            PushContext();

            SetCurrentTypeName(namedType->GetName());

            SetCurrentType(namedType);

            // Generate subordinate type.

            namedType->Accept(this);

            PopContext();
        }

        sequenceSize = typeList->size();
    }

    ////////// End Nested Type(s) //////////

    // Member functions XML doc generation.

    XmlNewLine();

    GenerateXmlBeginTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

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

            string adaptedGenBaseTypeName =
                AdaptName(GetGeneratedBaseTypeName(namedType));

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
                scopedElementTypeName.append("_");
                scopedElementTypeName.append(adaptedName);
            }

            // Generate XML elements for "memberFunctionSet".

            GenerateXmlBeginTag("memberFunctionSet");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "%s_Set%s",
                    scopedTypeName.c_str(),
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "void %s_Set%s(%s object, %s element)",
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str(),
                    scopedElementTypeName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "elmentName",
                adaptedName);

            XmlNewLine();

            GenerateXmlElement(
                "asnElementName",
                namedType->GetName());

            XmlNewLine();

            GenerateXmlElement(
                "elementTypeName",
                scopedElementTypeName);

            XmlNewLine();

            if (namedType->IsOptional())
            {
                GenerateXmlElement("optional", "yes");
            }
            else
            {
                GenerateXmlElement("optional", "no");
            }

            XmlNewLine();

            GenerateXmlEndTag("memberFunctionSet");

            XmlNewLine();
            XmlNewLine();

            // Generate XML elements for "memberFunctionGet".

            GenerateXmlBeginTag("memberFunctionGet");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "%s_Get%s",
                    scopedTypeName.c_str(),
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "const %s %s_Get%s(const %s object)",
                    scopedElementTypeName.c_str(),
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "elementName",
                adaptedName);

            XmlNewLine();

            GenerateXmlElement(
                "asnElementName",
                namedType->GetName());

            XmlNewLine();

            GenerateXmlElement(
                "elementTypeName",
                scopedElementTypeName);

            XmlNewLine();

            if (namedType->IsOptional())
            {
                GenerateXmlElement("optional", "yes");
            }
            else
            {
                GenerateXmlElement("optional", "no");
            }

            XmlNewLine();

            GenerateXmlEndTag("memberFunctionGet");

            XmlNewLine();
            XmlNewLine();

            if (namedType->IsOptional())
            {
                // Generate XML elements for "memberFunctionOption".

                GenerateXmlBeginTag("memberFunctionOption");

                XmlNewLine();

                GenerateXmlElement(
                    "name",
                    GetVarArgsString(
                        "%s_Option%s",
                        scopedTypeName.c_str(),
                        adaptedName.c_str()));

                XmlNewLine();

                GenerateXmlElement(
                    "signature", 
                    GetVarArgsString(
                        "ITS_BOOLEAN %s_Option%s(const %s object)",
                        scopedTypeName.c_str(),
                        adaptedName.c_str(),
                        scopedTypeName.c_str()));

                XmlNewLine();

                GenerateXmlElement(
                    "elementName",
                    adaptedName);

                XmlNewLine();

                GenerateXmlElement(
                    "asnElementName",
                    namedType->GetName());

                XmlNewLine();

                GenerateXmlElement(
                    "elementTypeName",
                    scopedElementTypeName);

                XmlNewLine();

                GenerateXmlEndTag("memberFunctionOption");

                XmlNewLine();
                XmlNewLine();
            }

            index++;
        }
    }

    GenerateXmlEndTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnSequence");
}


void
GenerateCXmlDocVisitor::VisitSequenceTypeList(TypeList* typeList)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitSequenceOfTypeBegin(SequenceOfType* sequenceOfType)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitSequenceOfTypeEnd(SequenceOfType* sequenceOfType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnSequenceOf",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    ////////// Begin Nested Type //////////

    Type* type = sequenceOfType->GetSequenceOfType();

    string eltTypeName = AdaptName(GetGeneratedTypeName(type));

    string eltBaseTypeName = AdaptName(GetGeneratedBaseTypeName(type));

    if (IsAsnTypeName(eltTypeName))
    {
        eltTypeName.erase(0, 3);   // Remove "Asn" prefix.

        for (size_t i = 0; i < eltTypeName.size(); i++)
        {
            eltTypeName[i] = toupper(eltTypeName[i]);
        }
    }

    PushContext();

    SetCurrentTypeName(eltTypeName);

    SetCurrentType(type);

    // Generate subordinate type.

    type->Accept(this);

    PopContext();

    ////////// End Nested Type //////////

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
        scopedEltTypeName.append("_");
        scopedEltTypeName.append(eltTypeName);
    }

    XmlNewLine();

    GenerateXmlBeginTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    // Generate XML elements for "memberFunctionAdd".

    GenerateXmlBeginTag("memberFunctionAdd");

    XmlNewLine();

    GenerateXmlElement(
        "name", 
        GetVarArgsString(
            "%s_AddElement",
            scopedTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement(
        "signature", 
        GetVarArgsString(
            "int %s_AddElement(%s object, %s element)",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedEltTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement(
        "elementTypeName", 
        scopedEltTypeName);

    XmlNewLine();

    GenerateXmlEndTag("memberFunctionAdd");

    XmlNewLine();
    XmlNewLine();

    // Generate XML elments for "memberFunctionAt".

    GenerateXmlBeginTag("memberFunctionAt");

    XmlNewLine();

    GenerateXmlElement(
        "name", 
        GetVarArgsString(
            "%s_GetElementAt",
            scopedTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement(
        "signature", 
        GetVarArgsString(
            "const %s %s_GetElementAt(const %s object, size_t index)",
            scopedEltTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement(
        "elementTypeName", 
        scopedEltTypeName);

    XmlNewLine();

    GenerateXmlEndTag("memberFunctionAt");

    XmlNewLine();
    XmlNewLine();

    GenerateXmlEndTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnSequenceOf");
}


void
GenerateCXmlDocVisitor::VisitSequenceOfTypeType(Type* type)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitSequenceOfConstraint(Constraint* constraint)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitSetTypeBegin(SetType* setType)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitSetTypeEnd(SetType* setType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnSet",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    ////////// Begin Nested Type(s) //////////

   TypeList* typeList = setType->GetFlattenedTypeList();

    int setSize = 0;

    if (!(typeList->empty()))
    {
        for (TypeList::iterator iter = typeList->begin();
             iter != typeList->end();
             iter++)
        {
            Type* namedType = *iter;

            PushContext();

            SetCurrentTypeName(namedType->GetName());

            SetCurrentType(namedType);

            // Generate subordinate type.

            namedType->Accept(this);

            PopContext();
        }

        setSize = typeList->size();
    }

    ////////// End Nested Type(s) //////////

    // Member functions XML doc generation.

    XmlNewLine();

    GenerateXmlBeginTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

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

            string adaptedGenBaseTypeName =
                AdaptName(GetGeneratedBaseTypeName(namedType));

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
                scopedElementTypeName.append("_");
                scopedElementTypeName.append(adaptedName);
            }

            // Generate XML elements for "memberFunctionSet".

            GenerateXmlBeginTag("memberFunctionSet");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "%s_Set%s",
                    scopedTypeName.c_str(),
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "void %s_Set%s(%s object, %s element)",
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str(),
                    scopedElementTypeName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "elmentName",
                adaptedName);

            XmlNewLine();

            GenerateXmlElement(
                "asnElementName",
                namedType->GetName());

            XmlNewLine();

            GenerateXmlElement(
                "elementTypeName",
                scopedElementTypeName);

            XmlNewLine();

            if (namedType->IsOptional())
            {
                GenerateXmlElement("optional", "yes");
            }
            else
            {
                GenerateXmlElement("optional", "no");
            }

            XmlNewLine();

            GenerateXmlEndTag("memberFunctionSet");

            XmlNewLine();
            XmlNewLine();

            // Generate XML elements for "memberFunctionGet".

            GenerateXmlBeginTag("memberFunctionGet");

            XmlNewLine();

            GenerateXmlElement(
                "name",
                GetVarArgsString(
                    "%s_Get%s",
                    scopedTypeName.c_str(),
                    adaptedName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "signature", 
                GetVarArgsString(
                    "const %s %s_Get%s(const %s object)",
                    scopedElementTypeName.c_str(),
                    scopedTypeName.c_str(),
                    adaptedName.c_str(),
                    scopedTypeName.c_str()));

            XmlNewLine();

            GenerateXmlElement(
                "elementName",
                adaptedName);

            XmlNewLine();

            GenerateXmlElement(
                "asnElementName",
                namedType->GetName());

            XmlNewLine();

            GenerateXmlElement(
                "elementTypeName",
                scopedElementTypeName);

            XmlNewLine();

            if (namedType->IsOptional())
            {
                GenerateXmlElement("optional", "yes");
            }
            else
            {
                GenerateXmlElement("optional", "no");
            }

            XmlNewLine();

            GenerateXmlEndTag("memberFunctionGet");

            XmlNewLine();
            XmlNewLine();

            if (namedType->IsOptional())
            {
                // Generate XML elements for "memberFunctionOption".

                GenerateXmlBeginTag("memberFunctionOption");

                XmlNewLine();

                GenerateXmlElement(
                    "name",
                    GetVarArgsString(
                        "%s_Option%s",
                        scopedTypeName.c_str(),
                        adaptedName.c_str()));

                XmlNewLine();

                GenerateXmlElement(
                    "signature", 
                    GetVarArgsString(
                        "ITS_BOOLEAN %s_Option%s(const %s object)",
                        scopedTypeName.c_str(),
                        adaptedName.c_str(),
                        scopedTypeName.c_str()));

                XmlNewLine();

                GenerateXmlElement(
                    "elementName",
                    adaptedName);

                XmlNewLine();

                GenerateXmlElement(
                    "asnElementName",
                    namedType->GetName());

                XmlNewLine();

                GenerateXmlElement(
                    "elementTypeName",
                    scopedElementTypeName);

                XmlNewLine();

                GenerateXmlEndTag("memberFunctionOption");

                XmlNewLine();
                XmlNewLine();
            }

            index++;
        }
    }

    GenerateXmlEndTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnSet");
}


void
GenerateCXmlDocVisitor::VisitSetTypeList(TypeList* typeList)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitSetOfTypeBegin(SetOfType* setOfType)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitSetOfTypeEnd(SetOfType* setOfType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnSetOf",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);


    ////////// Begin Nested Type //////////

    Type* type = setOfType->GetSetOfType();

    string eltTypeName = GetGeneratedTypeName(type);

    string eltBaseTypeName = AdaptName(GetGeneratedBaseTypeName(type));

    if (IsAsnTypeName(eltTypeName))
    {
        eltTypeName.erase(0, 3);   // Remove "Asn" prefix.

        for (size_t i = 0; i < eltTypeName.size(); i++)
        {
            eltTypeName[i] = toupper(eltTypeName[i]);
        }
    }

    PushContext();

    SetCurrentTypeName(eltTypeName);

    SetCurrentType(type);

    // Generate subordinate type.

    type->Accept(this);

    PopContext();

    ////////// End Nested Type //////////

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
        scopedEltTypeName.append("_");
        scopedEltTypeName.append(eltTypeName);
    }

    XmlNewLine();

    GenerateXmlBeginTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    // Generate XML elements for "memberFunctionAdd".

    GenerateXmlBeginTag("memberFunctionAdd");

    XmlNewLine();

    GenerateXmlElement(
        "name", 
        GetVarArgsString(
            "%s_AddElement",
            scopedTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement(
        "signature", 
        GetVarArgsString(
            "int %s_AddElement(%s object, %s element)",
            scopedTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedEltTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement("elementTypeName", eltTypeName);

    XmlNewLine();

    GenerateXmlEndTag("memberFunctionAdd");

    XmlNewLine();
    XmlNewLine();

    // Generate XML elments for "memberFunctionAt".

    GenerateXmlBeginTag("memberFunctionAt");

    XmlNewLine();

    GenerateXmlElement(
        "name", 
        GetVarArgsString(
            "%s_GetElementAt",
            scopedTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement(
        "signature", 
        GetVarArgsString(
            "const %s %s_GetElementAt(const %s object, size_t index)",
            scopedEltTypeName.c_str(),
            scopedTypeName.c_str(),
            scopedTypeName.c_str()));

    XmlNewLine();

    GenerateXmlElement(
        "elementTypeName", 
        scopedEltTypeName);

    XmlNewLine();

    GenerateXmlEndTag("memberFunctionAt");

    XmlNewLine();
    XmlNewLine();

    GenerateXmlEndTag("memberFunctions");

    XmlNewLine();
    XmlNewLine();

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnSetOf");
}


void
GenerateCXmlDocVisitor::VisitSetOfTypeType(Type* type)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitSetOfConstraint(Constraint* constraint)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitOctetStringType(OctetStringType* octetStringType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnOctetString",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnOctetString");
}


void
GenerateCXmlDocVisitor::VisitDefinedType(DefinedType* definedType)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitAnyType(AnyType* anyType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnAny",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnAny");
}


void
GenerateCXmlDocVisitor::VisitAnyDefinedByType(AnyDefinedByType* anyDefinedByType)
{
    string moduleName = AdaptName(GetCurrentModuleName());
    string typeName = AdaptName(GetCurrentTypeName());
    string scopedTypeName = GetScopeStringWithModule();

    GenerateTypeXmlBeginPart(
                        "asnAny",
                        GetScopeStringWithModule(),
                        GetAsnScopeString(),
                        moduleName);


    // Add to asnTypeInfoList.

    AsnTypeInfo asnTypeInfo(
                    GetScopeStringWithModule(), 
                    GetScopeUnderscoreString());

    asnTypeInfoList.push_back(asnTypeInfo);

    GenerateXmlAsnDefinition();

    GenerateTypeXmlEndPart("asnAny");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GenerateCXmlDocVisitor::VisitValueDefBegin(ValueDef* valueDef)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitValueDefMiddle(ValueDef* valueDef)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitValueDefEnd(ValueDef* valueDef)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitValueDefType(ValueDef* valueDef, Type* type)
{
    // Must do nothing (i.e. must not generate code).
}


void 
GenerateCXmlDocVisitor::VisitValueBegin(Value* value)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitValueEnd(Value* value)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitBitStringValue(BitStringValue* bitStringValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitBooleanValue(BooleanValue* booleanValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitCharacterStringValue(
                            CharacterStringValue* characterStringValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitChoiceValue(ChoiceValue* choiceValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitEnumeratedValue(EnumeratedValue* enumeratedValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitIntegerValue(IntegerValue* integerValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitObjectIdentifierValue(
                            ObjectIdentifierValue* objectIdentifierValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitOctetStringValue(OctetStringValue* octetStringValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitMaxValue(MaxValue* maxValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitMinValue(MinValue* minValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitNullValue(NullValue* nullValue)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitRealValue(RealValue* realValue)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitSequenceValueBegin(SequenceValue* sequenceValue)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitSequenceValueEnd(SequenceValue* sequenceValue)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitDefinedValue(DefinedValue* definedValue)
{
    // Nothing to do.
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCXmlDocVisitor::VisitNamedNumberBegin(NamedNumber* namedNumber)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitNamedNumberEnd(NamedNumber* namedNumber)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitTag(Tag* tag)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitConstraintBegin(Constraint* constraint)
{
    // Nothing to do.
}


void 
GenerateCXmlDocVisitor::VisitConstraintEnd(Constraint* constraint)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitSingleValueConstraintElementBegin(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitSingleValueConstraintElementEnd(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitValueRangeConstraintElementBegin(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitValueRangeConstraintElementMiddle(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{
    // Nothing to do.
}


void
GenerateCXmlDocVisitor::VisitValueRangeConstraintElementEnd(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{
    // Nothing to do.
}


void GenerateCXmlDocVisitor::VisitSizeConstraintElementBegin(
                            SizeConstraintElement* 
                                sizeConstraintElement)
{
    // Nothing to do.
}


void GenerateCXmlDocVisitor::VisitSizeConstraintElementEnd(
                            SizeConstraintElement*
                                sizeConstraintElement)
{
    // Nothing to do.
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void 
GenerateCXmlDocVisitor::GenerateTypeXmlBeginPart(
                                    const std::string& xmlType,
                                    const std::string& className, 
                                    const std::string& asnTypeName,
                                    const std::string& moduleName)
{
    GetXml().insert(0, GetXmlHeaderString());

    GenerateXmlBeginTag("asnType");

    XmlNewLine();
    XmlNewLine();

    GenerateXmlBeginTag(xmlType);

    XmlNewLine();
    XmlNewLine();

    GenerateXmlElement("className", className);

    XmlNewLine();

    GenerateXmlElement("asnTypeName", asnTypeName);

    XmlNewLine();

    GenerateXmlElement(
        "moduleName", 
        AdaptModuleName(GetCurrentModuleName()));

    XmlNewLine();
    XmlNewLine();
}


void 
GenerateCXmlDocVisitor::GenerateTypeXmlEndPart(const std::string& xmlType)
{
    XmlNewLine();
    XmlNewLine();

    GenerateXmlEndTag(xmlType);

    XmlNewLine();
    XmlNewLine();

    GenerateXmlEndTag("asnType");

    GetXml().append(GetXmlEndString());
}


void 
GenerateCXmlDocVisitor::GenerateXmlElement(
                                    const std::string& tagName, 
                                    const std::string& value)
{
    GenerateXmlBeginTag(tagName);

    string substituedValue =
        SubstituteXmlSpecialCharacters(value);

    XmlPrint(0, substituedValue.c_str());

    GenerateXmlEndTag(tagName);
}


void 
GenerateCXmlDocVisitor::GenerateXmlBeginTag(
                                    const std::string& tagName)
{
    XmlPrint(0,
            "<%s>",
            tagName.c_str());
}


void 
GenerateCXmlDocVisitor::GenerateXmlEndTag(
                                    const std::string& tagName)
{
    XmlPrint(0,
            "</%s>",
            tagName.c_str());
}


void
GenerateCXmlDocVisitor::GenerateXmlAsnDefinition()
{
    XmlNewLine();
    XmlNewLine();

    GenerateXmlBeginTag("asnDefinition");

    XmlNewLine();
    XmlNewLine();

    if (typeStack.size() > 1)
    {
        GenerateXmlBeginTag("line");

        XmlNewLine();

        GenerateXmlElement(
            "text", 
            "-- Note: the ASN.1 type definition containing the inner type is "
            "showed.");

        XmlNewLine();
       
        GenerateXmlEndTag("line");

        XmlNewLine();
    }

    // Process ASN.1 Definition (asnDef) to format it into XML format.

    string asnDef = GetCurrentTypeDef()->ToString();

    list<string> asnDefStrList;

    string line;

    line.reserve(asnDef.size());

    for (size_t i = 0; i < asnDef.size(); i++)
    {
        if (asnDef[i] == '\n')
        {
            asnDefStrList.push_back(line);
            
            line.erase(line.begin(), line.end());
        }
        else
        {
            line.append(1, asnDef[i]);
        }
    }

    for (list<string>::iterator iter = asnDefStrList.begin();
         iter != asnDefStrList.end();
         iter++)
    {
        GenerateXmlBeginTag("line");

        XmlNewLine();
        
        line = *iter;

        int numberOfShifts = 0;

        if (line.size() < 4)
        {
            numberOfShifts = 0;
        }
        else
        {
            size_t j = 0;

            bool stop = false;

            while (!stop)
            {
                if (line[j + 0] == ' ' &&
                    line[j + 1] == ' ' &&
                    line[j + 2] == ' ' &&
                    line[j + 3] == ' ')
                {
                    numberOfShifts++;

                    j += 4;

                    if (line.size() < j + 4)
                    {
                        stop = true;
                    }
                }
                else
                {
                    stop = true;
                }
            }
        }

        GenerateXmlElement("text", line);

        XmlNewLine();

        for (int k = 0; k < numberOfShifts; k++)
        {
            GenerateXmlElement("shift", "");

            XmlNewLine();
        }

        GenerateXmlEndTag("line");

        XmlNewLine();        
    }
        
    XmlNewLine();

    GenerateXmlEndTag("asnDefinition");

    XmlNewLine();
    XmlNewLine();
}


void 
GenerateCXmlDocVisitor::GenerateXmlAsnModuleSummary()
{
    // Cleaning of contents (xml source).

    GetXml().erase(GetXml().begin(), GetXml().end());

    GetXml().insert(0, GetXmlHeaderString());

    XmlNewLine();

    GenerateXmlBeginTag("asnModuleSummary");

    XmlNewLine();
    XmlNewLine();

    string moduleName = GetCurrentModuleName();

    moduleName = AdaptNameToLowercase(moduleName);

    string fileNamePrefix = moduleName;
    fileNamePrefix.append("_");

    GenerateXmlElement(
        "moduleName", 
        AdaptModuleName(GetCurrentModuleName()));

    XmlNewLine();
    XmlNewLine();

    asnTypeInfoList.sort();

    for (AsnTypeInfoList::const_iterator iter = asnTypeInfoList.begin();
         iter != asnTypeInfoList.end();
         iter++)
    {
        GenerateXmlBeginTag("asnType");

        XmlNewLine();

        GenerateXmlElement("className", (*iter).GetClassName());

        XmlNewLine();

        GenerateXmlElement("asnTypeName", (*iter).GetAsnTypeName());

        XmlNewLine();

        GenerateXmlElement(
            "asnTypeFileName",
            AdaptNameToLowercase(
                fileNamePrefix +
                    (*iter).GetAsnTypeName()));

        XmlNewLine();

        GenerateXmlEndTag("asnType");

        XmlNewLine();
        XmlNewLine();
    }

    GenerateXmlEndTag("asnModuleSummary");

    XmlNewLine();
    XmlNewLine();

    string directoryName = moduleName + "_c_doc";

    WriteTextToFile(
                directoryName,
                "AsnModuleSummary",
                "xml",
                GetXml());
}


void 
GenerateCXmlDocVisitor::GenerateXmlAsnModuleClassList()
{
    // Cleaning of contents (xml source).

    GetXml().erase(GetXml().begin(), GetXml().end());

    GetXml().insert(0, GetXmlHeaderString());

    XmlNewLine();

    GenerateXmlBeginTag("asnModuleClassList");

    XmlNewLine();
    XmlNewLine();

    asnTypeInfoList.sort();

    string moduleName = GetCurrentModuleName();

    moduleName = AdaptNameToLowercase(moduleName);

    string fileNamePrefix = moduleName;
    fileNamePrefix.append("_");

    for (AsnTypeInfoList::const_iterator iter = asnTypeInfoList.begin();
         iter != asnTypeInfoList.end();
         iter++)
    {
        GenerateXmlBeginTag("asnType");

        XmlNewLine();

        GenerateXmlElement("className", (*iter).GetClassName());

        XmlNewLine();

        GenerateXmlElement("asnTypeName", (*iter).GetAsnTypeName());

        XmlNewLine();

        GenerateXmlElement(
            "asnTypeFileName",
            AdaptNameToLowercase(
                fileNamePrefix +
                    (*iter).GetAsnTypeName()));

        XmlNewLine();

        GenerateXmlEndTag("asnType");

        XmlNewLine();
        XmlNewLine();
    }

    GenerateXmlEndTag("asnModuleClassList");

    XmlNewLine();
    XmlNewLine();

    string directoryName = moduleName + "_c_doc";

    WriteTextToFile(
                directoryName,
                "AsnModuleClassList",
                "xml",
                GetXml());
}


void 
GenerateCXmlDocVisitor::GenerateXmlAsnModuleMakeHtml()
{
    // Cleaning of contents (xml source use for bat generation).

    GetXml().erase(GetXml().begin(), GetXml().end());

    XmlPrint(0, 
        "Rem\n");
    XmlPrint(0, 
        "Rem Generated by IntelliAsnCC ASN.1 compiler (C, C++, Java).\n");
    XmlPrint(0, 
        "Rem\n");
    XmlPrint(0, 
        "Rem Do not edit!\n");
    XmlPrint(0, 
        "Rem\n");
    XmlPrint(0, 
        "Rem\n");
    XmlPrint(0, 
        "Rem (C) 2001 IntelliNet Technologies Inc. All Rights Reserved.\n");
    XmlPrint(0, 
        "Rem\n");
    XmlPrint(0, 
        "Rem\n");

    XmlNewLine();
    XmlNewLine();


    // Copy XML to HTML script to current directory (for bat file).

    XmlPrint(0,
        "cp -f %%ITS_ROOT%%/tools/src/asncc_doc/c/AsnccXml2Html.js .");

    XmlNewLine();
    XmlNewLine();

    // Copy XSL transformation files to current directory (for bat file).

    XmlPrint(0,
        "cp -f %%ITS_ROOT%%/tools/src/asncc_doc/c/*.xsl .");

    XmlNewLine();
    XmlNewLine();

    // Copy all HTML documents to current directory (for bat file).

    XmlPrint(0,
        "cp -f %%ITS_ROOT%%/tools/src/asncc_doc/c/*.html .");

    XmlNewLine();
    XmlNewLine();

    // Copy default IntelliSS7 icon to current directory (for bat file).

    XmlPrint(0,
        "cp -f %%ITS_ROOT%%/tools/src/asncc_doc/c/AsnModuleLogo.jpg .");

    XmlNewLine();
    XmlNewLine();


    XmlPrint(0,
        "cscript AsnccXml2Html.js AsnModuleSummary.xml");

    XmlNewLine();
    XmlNewLine();

    XmlPrint(0,
        "cscript AsnccXml2Html.js AsnModuleClassList.xml");

    XmlNewLine();
    XmlNewLine();

    asnTypeInfoList.sort();

    string moduleName = GetCurrentModuleName();

    moduleName = AdaptNameToLowercase(moduleName);

    string fileNamePrefix = moduleName;
    fileNamePrefix.append("_");

    for (AsnTypeInfoList::const_iterator iter = asnTypeInfoList.begin();
         iter != asnTypeInfoList.end();
         iter++)
    {
        XmlPrint(0, 
            "cscript AsnccXml2Html.js %s.xml", 
            AdaptNameToLowercase(
                fileNamePrefix + 
                    (*iter).GetAsnTypeName()).c_str());

        XmlNewLine();
        XmlNewLine();
    }

    string directoryName = moduleName + "_c_doc";

    WriteTextToFile(
                directoryName,
                "AsnModuleMakeHtml",
                "bat",
                GetXml());
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
GenerateCXmlDocVisitor::XmlPrint(int n, const char* format, ...)
{
    // No indentation for XML generation.

    static char buf[MaxBufferSize];

    va_list alist;

    va_start(alist, format);

    vsprintf(buf, format, alist);

    xml.append(buf);

    va_end(alist);
}


string
GenerateCXmlDocVisitor::SubstituteXmlSpecialCharacters(const string& str)
{
    string result;

    result.reserve(str.size() + SIZE_SMALL);

    for (size_t i = 0; i < str.size(); i++)
    {
        switch (str[i])
        {
        case '&':
            result.append("&amp;");
            break;

        case '<':
            result.append("&lt;");
            break;

        case '>':
            result.append("&gt;");
            break;

        case '"':
            result.append("&quot;");
            break;

        case '\'':
            result.append("&apos;");
            break;

        default:
            result.append(1, str[i]);
            break;
        }
    }

    ENSURE(result.size() >= str.size());

    return result;
}


string 
GenerateCXmlDocVisitor::GetXmlHeaderString()
{
    string result;

    result.reserve(SIZE_MEDIUM);

    result.append("<?xml version=\"1.0\"?>\n\n\n");

    result.append(
        "<!--                                                                  "
        "       -->\n");
    result.append(
        "<!-- Generated by IntelliAsnCC ASN.1 compiler (C, C++, Java).         "
        "       -->\n");
    result.append(
        "<!--                                                                  "
        "       -->\n");
    result.append(
        "<!-- Do not edit!                                                     "
        "       -->\n");
    result.append(
        "<!--                                                                  "
        "       -->\n");
    result.append(
        "<!--                                                                  "
        "       -->\n");
    result.append(
        "<!-- (C) 2000 IntelliNet Technologies Inc. All Rights Reserved.       "
        "       -->\n");
    result.append(
        "<!--                                                                  "
        "       -->\n");
    result.append(
        "<!--                                                                  "
        "       -->\n");

    result.append("\n");
    result.append("\n");

    return result;
}


string 
GenerateCXmlDocVisitor::GetXmlEndString()
{
    string result;

    result.reserve(SIZE_TINY);

    result.append("\n");
    result.append("\n");

    return result;
}


string 
GenerateCXmlDocVisitor::GetScopeString()
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

        if (++iter == typeNameList.end())
        {
            --iter;
        }
        else
        {
            --iter;

            result.append("_");
        }
    }

    return result;
}


string
GenerateCXmlDocVisitor::GetScopeStringWithModule()
{
    list<string> typeNameList(typeNameStack);

    typeNameList.push_front(GetCurrentTypeName());

    typeNameList.reverse();

    string moduleName = AdaptName(GetCurrentModuleName());

    string result = moduleName;

    result.append("_");

    for (list<string>::iterator iter = typeNameList.begin();
         iter != typeNameList.end();
         iter++)
    {
        string str = *iter;

        result.append(AdaptName(str));

        if (++iter == typeNameList.end())
        {
            --iter;
        }
        else
        {
            --iter;

            result.append("_");
        }
    }

    return result;
}


string 
GenerateCXmlDocVisitor::GetAsnScopeString()
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

        result.append(str);

        if (++iter == typeNameList.end())
        {
            --iter;
        }
        else
        {
            --iter;

            result.append("::");
        }
    }

    return result;
}


string 
GenerateCXmlDocVisitor::GetScopeUnderscoreString()
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

        if (++iter == typeNameList.end())
        {
            --iter;
        }
        else
        {
            --iter;

            result.append("_");
        }
    }

    return result;
}


string 
GenerateCXmlDocVisitor::GetAsnScopeUnderscoreString()
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

        result.append(str);

        if (++iter == typeNameList.end())
        {
            --iter;
        }
        else
        {
            --iter;

            result.append("_");
        }
    }

    return result;
}


void 
GenerateCXmlDocVisitor::PushContext()
{
    GenerateCVisitor::PushContext();   

    xmlStack.push_front(xml);

    xml.erase(xml.begin(), xml.end());
}


void 
GenerateCXmlDocVisitor::PopContext()
{
    xml = xmlStack.front();

    xmlStack.pop_front();

    GenerateCVisitor::PopContext();
}


